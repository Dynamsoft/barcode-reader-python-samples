from dynamsoft_barcode_reader_bundle import *
try:
    import cv2
except ModuleNotFoundError:
    raise SystemExit(
        "OpenCV is required for this sample.\n"
        "Install it with:\n"
        "   python -m pip install opencv-python\n"
    )
import numpy as np
import os
import threading
import time
from pathlib import Path
from enum import IntEnum
from concurrent.futures import ThreadPoolExecutor
from typing import Optional, Dict, List

BASE_DIR = Path(__file__).resolve().parent
SAMPLE_IMAGE_PATH = str(BASE_DIR.parent / "Images" / "sample_grid.png")
LIGHTWEIGHT_TEMPLATE_PATH = str(BASE_DIR.parent / "CustomTemplates" / "GridFastScan.json")
LIGHTWEIGHT_TEMPLATE_NAME = "GridFastScan"
DEEP_DECODE_TEMPLATE_PATH = str(BASE_DIR.parent / "CustomTemplates" / "GridDeepDecode.json")
DEEP_DECODE_TEMPLATE_NAME = "GridDeepDecode"
RESULT_DIR = str(BASE_DIR / "Result")
SCALE_FACTOR = 2.0


# region: Geometry helpers

def compute_center(quad: Quadrilateral):
    cx = sum(p.x for p in quad.points) / 4
    cy = sum(p.y for p in quad.points) / 4
    return cx, cy

def expand_quad(quad: Quadrilateral, scale: float) -> Quadrilateral:
    cx, cy = compute_center(quad)
    result = Quadrilateral()
    for i, p in enumerate(quad.points):
        result.points[i].x = int(cx + (p.x - cx) * scale)
        result.points[i].y = int(cy + (p.y - cy) * scale)
    return result

# endregion


class InputParams:
    def __init__(self):
        self.exit: bool = False
        self.image_path: str = ""


class CommonDecodeResult:
    def __init__(self, error: int = 0):
        self.locations: List[Quadrilateral] = []
        self.texts: List[str] = []
        self.error: int = error

    def prepare_for_layout_analysis(self):
        for i, loc in enumerate(self.locations):
            loc.id = i

    def get_text(self, idx: int) -> str:
        if idx < 0 or idx >= len(self.texts):
            raise IndexError(f"Invalid id: {idx}")
        return self.texts[idx]


class LayoutAnalysisAndDecodeTextResultType(IntEnum):
    LAADTRT_DECODE_FAILED = 0
    LAADTRT_DECODED       = 1
    LAADTRT_INFERRED      = 2


class LayoutAnalysisAndDecodeTextResultItem:
    def __init__(self, location: Quadrilateral = None, text: str = "",
                 rtype: LayoutAnalysisAndDecodeTextResultType = LayoutAnalysisAndDecodeTextResultType.LAADTRT_INFERRED):
        self.location: Optional[Quadrilateral] = location
        self.text: str = text
        self.type: LayoutAnalysisAndDecodeTextResultType = rtype

    @classmethod
    def from_element(cls, element) -> "LayoutAnalysisAndDecodeTextResultItem":
        """Construct an INFERRED item from a LayoutElement (LES_INFERRED)."""
        return cls(location=element.quad,
                   rtype=LayoutAnalysisAndDecodeTextResultType.LAADTRT_INFERRED)

    @classmethod
    def from_decoded(cls, quad: Quadrilateral,
                     text: str) -> "LayoutAnalysisAndDecodeTextResultItem":
        """Construct a DECODED item from a quad and its decoded text."""
        return cls(location=quad, text=text,
                   rtype=LayoutAnalysisAndDecodeTextResultType.LAADTRT_DECODED)


class MyLayoutAnalysisResult:
    """Wrapper around LayoutAnalysisResult, mirroring the C++ RAII wrapper."""

    def __init__(self, layout_result=None):
        self.layout_result_inner = layout_result

    def __bool__(self) -> bool:
        return self.layout_result_inner is not None


class LayoutAnalysisAndDecodeTextResult:
    """Sparse 2-D mapping: items[row][col] = LayoutAnalysisAndDecodeTextResultItem"""

    def __init__(self, common_result: CommonDecodeResult,
                 layout_result: MyLayoutAnalysisResult):
        self.items: Dict[int, Dict[int, LayoutAnalysisAndDecodeTextResultItem]] = {}
        lst = layout_result.layout_result_inner.elements
        for row_i, row_elems in enumerate(lst):
            for col_i, element in enumerate(row_elems):
                if element.source == EnumLayoutElementSource.LES_INPUT:
                    try:
                        text = common_result.get_text(element.quad.id)
                        self.items.setdefault(row_i, {})[col_i] = \
                            LayoutAnalysisAndDecodeTextResultItem.from_decoded(
                                element.quad, text)
                    except Exception as e:
                        print(f"Error retrieving text for quad id "
                              f"{element.quad.id}: {e}")
                elif element.source == EnumLayoutElementSource.LES_INFERRED:
                    self.items.setdefault(row_i, {})[col_i] = \
                        LayoutAnalysisAndDecodeTextResultItem.from_element(element)
                # LES_NONE -> skip

    def update_item(self, row: int, col: int, text: str, quad: Quadrilateral):
        self.items[row][col].text = text
        self.items[row][col].location = quad
        self.items[row][col].type = LayoutAnalysisAndDecodeTextResultType.LAADTRT_DECODED

    def update_item_with_decode_failed(self, row: int, col: int):
        self.items[row][col].text = ""
        self.items[row][col].type = LayoutAnalysisAndDecodeTextResultType.LAADTRT_DECODE_FAILED

    def to_json(self) -> str:
        total_decoded = 0
        total_inferred = 0
        grid_json = ""

        for row_idx in sorted(self.items):
            for col_idx in sorted(self.items[row_idx]):
                item = self.items[row_idx][col_idx]
                if item.type in (
                    LayoutAnalysisAndDecodeTextResultType.LAADTRT_DECODED,
                    LayoutAnalysisAndDecodeTextResultType.LAADTRT_INFERRED,
                ):
                    status = "Decoded"
                    total_decoded += 1
                elif item.type == \
                        LayoutAnalysisAndDecodeTextResultType.LAADTRT_DECODE_FAILED:
                    status = "Inferred"
                    total_inferred += 1
                else:
                    status = "Failed"

                if grid_json:
                    grid_json += ","
                grid_json += (
                    f'\n\t\t{{ "row": {row_idx + 1}, "col": {col_idx + 1},'
                    f' "status": "{status}",'
                    f' "text": "{self._escape_json_string(item.text)}" }}'
                )

        return (
            "{\n"
            f'\t"totalDecoded": {total_decoded},\n'
            f'\t"totalInferred": {total_inferred},\n'
            f'\t"grid": [{grid_json}\n\t]\n'
            "}"
        )

    @staticmethod
    def _escape_json_string(s: str) -> str:
        table = {'"': '\\"', '\\': '\\\\', '\b': '\\b', '\f': '\\f',
                 '\n': '\\n', '\r': '\\r', '\t': '\\t'}
        out = []
        for c in s:
            if c in table:
                out.append(table[c])
            elif ord(c) < 32:
                out.append(f'\\u{ord(c):04x}')
            else:
                out.append(c)
        return ''.join(out)


class ImageShower:
    """
    Singleton that displays images in a dedicated background thread.
    Mirrors the C++ ImageShower class structure exactly.

    Usage:
        ImageShower.instance().update(img, "Window Title")
        ImageShower.instance().stop()   # call once before exit
    """

    _instance: Optional["ImageShower"] = None
    _instance_lock = threading.Lock()

    @classmethod
    def instance(cls) -> "ImageShower":
        if cls._instance is None:
            with cls._instance_lock:
                if cls._instance is None:
                    obj = cls.__new__(cls)
                    obj._init("Grid Barcode Scanner [1/4] Fast Scan", 30)
                    cls._instance = obj
        return cls._instance

    def _init(self, window_name: str, delay_ms: int):
        self._win_name: str = window_name
        self._window_title: str = window_name
        self._delay_ms: int = delay_ms
        self._img: Optional[np.ndarray] = None
        self._mutex = threading.Lock()
        self._running: bool = True
        self._thread = threading.Thread(
            target=self._loop, daemon=True, name="ImageShower")
        self._thread.start()

    def update(self, img: np.ndarray, title: str):
        with self._mutex:
            self._img = img.copy()
            self._window_title = title

    def stop(self):
        if self._running:
            self._running = False
            if self._thread.is_alive():
                self._thread.join()

    def set_delay(self, ms: int):
        self._delay_ms = ms

    def _loop(self):
        try:
            cv2.namedWindow(self._win_name, cv2.WINDOW_NORMAL)
            cv2.resizeWindow(self._win_name, 800, 600)
            cv2.moveWindow(self._win_name, 100, 100)
        except Exception:
            self._running = False
            return
        last_title = self._window_title

        while self._running:
            img = None
            with self._mutex:
                if self._img is not None:
                    img = self._img.copy()
                    self._img = None
                title = self._window_title

            if img is not None:
                if title != last_title:
                    cv2.setWindowTitle(self._win_name, title)
                    last_title = title

                rect = cv2.getWindowImageRect(self._win_name)
                win_w, win_h = rect[2], rect[3]
                if win_w > 0 and win_h > 0:
                    scale = min(win_w / img.shape[1], win_h / img.shape[0])
                    new_w = int(img.shape[1] * scale)
                    new_h = int(img.shape[0] * scale)
                    cv2.resizeWindow(self._win_name, new_w, new_h)

                cv2.imshow(self._win_name, img)
            else:
                key = cv2.waitKey(self._delay_ms)
                if key == 27:
                    self._running = False
                time.sleep(0.001)
                continue

            key = cv2.waitKey(self._delay_ms)
            if key == 27:
                self._running = False
            time.sleep(0.001)


class Task:
    def __init__(self, row: int, col: int,
                 item: LayoutAnalysisAndDecodeTextResultItem):
        self.row = row
        self.col = col
        self.item = item


class ImageHelper:
    """
    Loads an image and provides methods for drawing results and saving them.
    Mirrors the C++ ImageHelper class structure.
    """

    def __init__(self, path: str):
        img = cv2.imread(path, cv2.IMREAD_COLOR)
        if img is None:
            raise RuntimeError(f"Failed to read image from file: {path}")
        self._img: np.ndarray = img
        self._image_path: Path = Path(path)

    def width(self) -> int:
        return self._img.shape[1]

    def height(self) -> int:
        return self._img.shape[0]

    def image(self) -> np.ndarray:
        return self._img

    @staticmethod
    def create_result_dir(img_path: str):
        p = Path(img_path)
        (Path(RESULT_DIR) / p.stem).mkdir(parents=True, exist_ok=True)

    def get_result_dir(self) -> str:
        return str(Path(RESULT_DIR) / self._image_path.stem)

    # region: save_result_image overloads (mirrors C++ function overloading)

    def save_result_image(self, result) -> bool:
        """
        Polymorphic save method mirroring C++ overloaded saveResultImage:
          - CommonDecodeResult                -> Phase 1 (fast scan)
          - MyLayoutAnalysisResult            -> Phase 2 (layout analysis)
          - LayoutAnalysisAndDecodeTextResult -> Phase 3 (deep decode)
        """
        if isinstance(result, CommonDecodeResult):
            img = self._draw_solid_quads(self._img, result.locations,
                                         color=(0, 255, 0), thickness=2)
            ImageShower.instance().update(
                img, "Grid Barcode Scanner [1/4] Fast Scan")
            return self._save_to_result_file(img, "_phase1")

        if isinstance(result, MyLayoutAnalysisResult):
            decoded_quads: List[Quadrilateral] = []
            inferred_quads: List[Quadrilateral] = []
            for row_elems in result.layout_result_inner.elements:
                for el in row_elems:
                    if el.source == EnumLayoutElementSource.LES_INPUT:
                        decoded_quads.append(el.quad)
                    elif el.source == EnumLayoutElementSource.LES_INFERRED:
                        inferred_quads.append(el.quad)
            img = self._draw_solid_quads(self._img, decoded_quads,
                                         color=(0, 255, 0), thickness=2)
            img = self._draw_dashed_quads(img, inferred_quads,
                                          color=(0, 0, 255),
                                          dash_length=10, thickness=4)
            ImageShower.instance().update(
                img, "Grid Barcode Scanner [2/4] Layout Analysis")
            return self._save_to_result_file(img, "_phase2")

        if isinstance(result, LayoutAnalysisAndDecodeTextResult):
            decoded_quads, inferred_quads, undecoded_quads = [], [], []
            for col_map in result.items.values():
                for item in col_map.values():
                    t = item.type
                    if t == LayoutAnalysisAndDecodeTextResultType.LAADTRT_DECODED:
                        decoded_quads.append(item.location)
                    elif t == LayoutAnalysisAndDecodeTextResultType.LAADTRT_INFERRED:
                        inferred_quads.append(item.location)
                    elif t == LayoutAnalysisAndDecodeTextResultType.LAADTRT_DECODE_FAILED:
                        undecoded_quads.append(
                            expand_quad(item.location, SCALE_FACTOR))
            img = self._draw_solid_quads(self._img, decoded_quads,
                                         color=(0, 255, 0), thickness=2)
            img = self._draw_solid_quads(img, inferred_quads,
                                         color=(0, 255, 0), thickness=2)
            img = self._draw_dashed_quads(img, undecoded_quads,
                                          color=(0, 0, 255),
                                          dash_length=10, thickness=4)
            ImageShower.instance().update(
                img, "Grid Barcode Scanner [3/4] Deep Decode")
            return self._save_to_result_file(img, "_phase3")

        return False

    def save_final_result_image(self,
                                result: LayoutAnalysisAndDecodeTextResult) -> bool:
        decoded_quads, inferred_quads, undecoded_quads = [], [], []
        for col_map in result.items.values():
            for item in col_map.values():
                t = item.type
                if t == LayoutAnalysisAndDecodeTextResultType.LAADTRT_DECODED:
                    decoded_quads.append(item.location)
                elif t == LayoutAnalysisAndDecodeTextResultType.LAADTRT_INFERRED:
                    inferred_quads.append(item.location)
                elif t == LayoutAnalysisAndDecodeTextResultType.LAADTRT_DECODE_FAILED:
                    undecoded_quads.append(expand_quad(item.location, SCALE_FACTOR))

        img = self._draw_solid_quads(self._img, decoded_quads,
                                     color=(0, 255, 0), thickness=2)
        img = self._draw_solid_quads(img, inferred_quads,
                                     color=(0, 255, 0), thickness=2)
        img = self._draw_dashed_quads(img, undecoded_quads,
                                      color=(0, 0, 255),
                                      dash_length=10, thickness=4)

        for col_map in result.items.values():
            for item in col_map.values():
                if item.type == \
                        LayoutAnalysisAndDecodeTextResultType.LAADTRT_DECODE_FAILED:
                    continue
                top_left = self._get_top_left(item.location)
                self._draw_text(img, item.text, top_left,
                                color=(0, 255, 0), scale=0.6)

        ImageShower.instance().update(
            img, "Grid Barcode Scanner [4/4] Final Result")
        return self._save_to_result_file(img, "_final")

    # endregion

    # region: Drawing helpers (static, each returns a new image)

    @staticmethod
    def _draw_solid_quads(base: np.ndarray, quads: List[Quadrilateral],
                          color=(0, 255, 0), thickness=2) -> np.ndarray:
        dst = base.copy()
        for quad in quads:
            pts = np.array([[p.x, p.y] for p in quad.points],
                           dtype=np.int32).reshape(-1, 1, 2)
            cv2.polylines(dst, [pts], True, color, thickness, cv2.LINE_8)
        return dst

    @staticmethod
    def _draw_dashed_quads(base: np.ndarray, quads: List[Quadrilateral],
                           color=(0, 0, 255), dash_length=10,
                           thickness=4) -> np.ndarray:
        dst = base.copy()
        half = max(1, thickness // 2)
        for quad in quads:
            pts = quad.points
            for i in range(4):
                x0, y0 = pts[i].x, pts[i].y
                x1, y1 = pts[(i + 1) % 4].x, pts[(i + 1) % 4].y
                seg_len = int(((x1 - x0) ** 2 + (y1 - y0) ** 2) ** 0.5)
                if seg_len == 0:
                    continue
                draw, count = True, 0
                for step in range(seg_len):
                    t = step / seg_len
                    x = int(x0 + t * (x1 - x0))
                    y = int(y0 + t * (y1 - y0))
                    if draw:
                        cv2.circle(dst, (x, y), half, color,
                                   cv2.FILLED, cv2.LINE_AA)
                    count += 1
                    if count == dash_length:
                        count = 0
                        draw = not draw
        return dst

    @staticmethod
    def _get_top_left(quad: Quadrilateral) -> tuple:
        return (min(p.x for p in quad.points),
                min(p.y for p in quad.points))

    @staticmethod
    def _draw_text(img: np.ndarray, text: str, org: tuple,
                   color=(0, 255, 0), scale=1.0):
        cv2.putText(img, text, org, cv2.FONT_HERSHEY_SIMPLEX,
                    scale, color, 2, cv2.LINE_AA)

    # endregion

    def _save_to_result_file(self, img: np.ndarray, suffix: str) -> bool:
        out_dir = Path(RESULT_DIR) / self._image_path.stem
        out_path = out_dir / (self._image_path.stem + suffix +
                              self._image_path.suffix)
        return cv2.imwrite(str(out_path), img)


# region: Top-level functions (mirror C++ free functions)

def welcome() -> InputParams:
    params = InputParams()
    print("Grid Barcode Scanner!")
    print("===========================")
    print()
    print("Image path: [press Enter to use sample image (sample_grid.png)]")
    print("'Q'/'q' to quit")
    user_input = input().strip()
    if user_input.lower() == 'q':
        params.exit = True
        return params
    if not user_input:
        params.image_path = SAMPLE_IMAGE_PATH
    else:
        if (len(user_input) >= 2 and
                user_input[0] == '"' and user_input[-1] == '"'):
            user_input = user_input[1:-1]
        params.image_path = user_input
    return params


def common_decode(image_helper: ImageHelper, template_path: str,
                  template_name: str = "") -> CommonDecodeResult:
    cvr = CaptureVisionRouter()
    err_code, err_msg = cvr.init_settings_from_file(template_path)
    if err_code != EnumErrorCode.EC_OK:
        print(f"Failed to initialize settings from file: "
              f"ErrorCode: {err_code}, ErrorString: {err_msg}")
        return CommonDecodeResult(err_code)

    t0 = time.time()
    result = cvr.capture(image_helper.image(),
                         EnumImagePixelFormat.IPF_BGR_888, template_name)
    elapsed = int((time.time() - t0) * 1000)

    ec = result.get_error_code()
    if ec == EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
        print(f"Common decode warning: {ec}, {result.get_error_string()}")
    elif ec not in (EnumErrorCode.EC_OK, EnumErrorCode.EC_TIMEOUT):
        print(f"Common decode error: {ec}, {result.get_error_string()}")
        return CommonDecodeResult(ec)

    decode_result = CommonDecodeResult()
    for item in result.get_items():
        if item.get_type() == EnumCapturedResultItemType.CRIT_BARCODE:
            decode_result.locations.append(item.get_location())
            decode_result.texts.append(item.get_text())

    print(f"[Phase 1] Fast scan: {len(decode_result.texts)} barcodes "
          f"decoded in {elapsed}ms.")
    return decode_result


def analyze(image_helper: ImageHelper,
            result: CommonDecodeResult) -> MyLayoutAnalysisResult:
    param = LayoutAnalysisParameter()
    param.pattern = EnumLayoutPattern.LP_MATRIX
    param.input_image_height = image_helper.height()
    param.input_image_width = image_helper.width()

    layout_result = LayoutAnalyzer.analyze(result.locations, param)
    if layout_result is None or layout_result.error_code != EnumErrorCode.EC_OK:
        err = layout_result.error_code if layout_result else -1
        print(f"Layout analysis failed: ErrorCode: {err}")
        return MyLayoutAnalysisResult()

    inferred_count = len(layout_result.inferred_quads)
    total = layout_result.row_count * layout_result.col_count
    print(f"\n[Phase 2] Layout analysis: {total} grid positions "
          f"({layout_result.row_count}x{layout_result.col_count}). "
          f"{inferred_count} inferred regions.")
    return MyLayoutAnalysisResult(layout_result)


def deep_decode_inner(image_helper: ImageHelper, template_path: str,
                      laadt_result: LayoutAnalysisAndDecodeTextResult,
                      task: Task, template_name: str = ""):
    cvr = CaptureVisionRouter()
    err_code, err_msg = cvr.init_settings_from_file(template_path)
    if err_code != EnumErrorCode.EC_OK:
        laadt_result.update_item_with_decode_failed(task.row, task.col)
        return

    err_code, err_msg, settings = cvr.get_simplified_settings(template_name)
    if err_code != EnumErrorCode.EC_OK:
        laadt_result.update_item_with_decode_failed(task.row, task.col)
        return

    settings.roi = expand_quad(task.item.location, SCALE_FACTOR)
    settings.roi_measured_in_percentage = 0
    err_code, err_msg = cvr.update_settings(template_name, settings)
    if err_code != EnumErrorCode.EC_OK:
        laadt_result.update_item_with_decode_failed(task.row, task.col)
        return

    result = cvr.capture(image_helper.image(),
                         EnumImagePixelFormat.IPF_BGR_888, template_name)
    if result.get_error_code() != EnumErrorCode.EC_OK:
        laadt_result.update_item_with_decode_failed(task.row, task.col)
        return

    for cap_item in result.get_items():
        if cap_item.get_type() == EnumCapturedResultItemType.CRIT_BARCODE:
            text = cap_item.get_text()
            if text:
                laadt_result.update_item(
                    task.row, task.col, text, cap_item.get_location())
            else:
                laadt_result.update_item_with_decode_failed(task.row, task.col)
            return

    laadt_result.update_item_with_decode_failed(task.row, task.col)


def deep_decode(image_helper: ImageHelper, template_path: str,
                laadt_result: LayoutAnalysisAndDecodeTextResult,
                template_name: str = ""):
    tasks = [
        Task(row_idx, col_idx, item)
        for row_idx, col_map in laadt_result.items.items()
        for col_idx, item in col_map.items()
        if item.type == LayoutAnalysisAndDecodeTextResultType.LAADTRT_INFERRED
    ]
    n = len(tasks)
    if n == 0:
        return

    t0 = time.time()
    num_threads = min(os.cpu_count() or 4, n)
    with ThreadPoolExecutor(max_workers=num_threads) as pool:
        futures = [
            pool.submit(deep_decode_inner, image_helper, template_path,
                        laadt_result, task, template_name)
            for task in tasks
        ]
        for f in futures:
            try:
                f.result()
            except Exception as e:
                print(f"Error in deep decode worker: {e}")

    elapsed = int((time.time() - t0) * 1000)
    decoded_count = sum(
        1 for task in tasks
        if laadt_result.items[task.row][task.col].type !=
        LayoutAnalysisAndDecodeTextResultType.LAADTRT_DECODE_FAILED
    )
    print(f"\n[Phase 3] Deep decode: {decoded_count} / {n} "
          f"inferred regions decoded in {elapsed}ms.")


def print_result(laadt_result: LayoutAnalysisAndDecodeTextResult, path: str):
    sep = "=" * 60
    print(sep)
    print(f" {'Row':<4} | {'Col':<5} | {'Status':<13} | Text")
    print(sep)
    total = decoded = 0
    for row_idx in sorted(laadt_result.items):
        for col_idx in sorted(laadt_result.items[row_idx]):
            item = laadt_result.items[row_idx][col_idx]
            total += 1
            if item.type in (
                LayoutAnalysisAndDecodeTextResultType.LAADTRT_DECODED,
                LayoutAnalysisAndDecodeTextResultType.LAADTRT_INFERRED,
            ):
                status = "Decoded"
                decoded += 1
            elif item.type == \
                    LayoutAnalysisAndDecodeTextResultType.LAADTRT_DECODE_FAILED:
                status = "Inferred"
            else:
                status = "Unknown"
            print(f"  {row_idx + 1:<3} | {col_idx + 1:<5} "
                  f"| {status:<13} | {item.text}")
    print(sep)
    print(f"[Done] Total decoded: {decoded} / {total}.")

    try:
        Path(path).parent.mkdir(parents=True, exist_ok=True)
        with open(path, 'w', encoding='utf-8') as f:
            f.write(laadt_result.to_json())
        print("Detailed results saved to result.json.")
    except Exception as e:
        print(f"Failed to save detailed results to result.json: {e}")

# endregion

if __name__ == "__main__":
    error_code = 0
    # 1. Initialize license.
    # You can request and extend a trial license from https://www.dynamsoft.com/customer/license/trialLicense?product=dcv&utm_source=samples&package=python
    # The string 'DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9' here is a free public trial license. Note that network connection is required for this license to work.
    error_code, error_msg = LicenseManager.init_license(
        "DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9")

    if (error_code != EnumErrorCode.EC_OK and
            error_code != EnumErrorCode.EC_LICENSE_WARNING):
        print(f"License initialization failed: "
              f"ErrorCode: {error_code}, ErrorString: {error_msg}")
    else:
        while True:
            try:
                temp = ""
                # input image path or exit
                params = welcome()
                if params.exit:
                    break

                image_helper = ImageHelper(params.image_path)
                ImageHelper.create_result_dir(params.image_path)

                # fast scan with lightweight template
                common_decode_result = common_decode(
                    image_helper, LIGHTWEIGHT_TEMPLATE_PATH,
                    LIGHTWEIGHT_TEMPLATE_NAME)
                if common_decode_result.error != EnumErrorCode.EC_OK:
                    continue
                common_decode_result.prepare_for_layout_analysis()
                image_helper.save_result_image(common_decode_result)

                input(" Press Enter for Layout Analysis...")

                # layout analysis
                layout_result = analyze(image_helper, common_decode_result)
                if not layout_result:
                    continue
                laadt_result = LayoutAnalysisAndDecodeTextResult(
                    common_decode_result, layout_result)
                image_helper.save_result_image(layout_result)

                input(" Press Enter for Deep Decode...")

                # deep decode with deep decode template
                deep_decode(image_helper, DEEP_DECODE_TEMPLATE_PATH,
                            laadt_result, DEEP_DECODE_TEMPLATE_NAME)
                image_helper.save_result_image(laadt_result)

                input(" Press Enter to view final result...")

                # print final result
                json_path = str(
                    Path(image_helper.get_result_dir()) / "result.json")
                print_result(laadt_result, json_path)
                image_helper.save_final_result_image(laadt_result)

                temp = input(
                    "Press Enter for next image (or 'Q'/'q' to quit)..."
                ).strip()
                if temp.lower() == 'q':
                    break
            except Exception as ex:
                print(f"An error occurred: {ex}")
                break

        ImageShower.instance().stop()
        cv2.destroyAllWindows()
