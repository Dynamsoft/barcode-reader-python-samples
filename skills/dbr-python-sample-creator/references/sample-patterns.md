# DBR Python SDK - Complete Sample Patterns Reference

This document contains the FULL working code for every sample pattern in the DBR Python SDK samples repository. Use these as authoritative templates when generating new samples.

---

## Table of Contents

1. [Single Image Processing (read_an_image.py)](#1-single-image-processing)
2. [Batch Directory Processing (read_multiple_images.py)](#2-batch-directory-processing)
3. [Video/Camera Barcode Decoding (video_decoding.py)](#3-videocamera-barcode-decoding)
4. [DPM Barcode Reader (read_dpm_barcode.py)](#4-dpm-barcode-reader)
5. [General Settings / Parameter Tuning (general_settings.py)](#5-general-settings)
6. [Parameter Tuner (parameter_tuner.py)](#6-parameter-tuner)
7. [Multi-Format Image Processing (multi_format_image_processing.py)](#7-multi-format-image-processing)
8. [Server-Side Barcode Decoder (server_side_barcode_decoder.py)](#8-server-side-barcode-decoder)
9. [Localized vs Decoded Barcodes Visualization (show_localized_vs_decoded_barcodes.py)](#9-localized-vs-decoded-barcodes)
10. [Custom Template JSON Files](#10-custom-template-json-files)

---

## 1. Single Image Processing

**File:** `Samples/read_an_image.py`

The simplest pattern: load one image, decode barcodes, print results. Uses `capture_multi_pages` for multi-page-capable processing of a single file.

```python
from dynamsoft_barcode_reader_bundle import *
import os
from pathlib import Path

BASE_DIR = Path(__file__).resolve().parent

if __name__ == '__main__':
    # 1. Initialize license.
    # You can request and extend a trial license from https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
    # The string 'DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==' here is a free public trial license. Note that network connection is required for this license to work.
    errorCode, errorMsg = LicenseManager.init_license("DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==")
    if errorCode != EnumErrorCode.EC_OK and errorCode != EnumErrorCode.EC_LICENSE_WARNING:
        print("License initialization failed: ErrorCode:", errorCode, ", ErrorString:", errorMsg)
    else:
        # 2. Create an instance of CaptureVisionRouter.
        cvr_instance = CaptureVisionRouter()

        # 3. Replace by your own image path.
        image_path = str(BASE_DIR.parent / "Images" / "GeneralBarcodes.png")

        # 4. Decode barcodes from an image file.
        result_array = cvr_instance.capture_multi_pages(image_path, EnumPresetTemplate.PT_READ_BARCODES)

        # 5. Output the barcode text.
        results = result_array.get_results()
        if results is None or len(results) == 0:
            print("No barcode detected.")
        else:
            for i, result in enumerate(results):
                page_number = i + 1
                tag = result.get_original_image_tag()
                if isinstance(tag, FileImageTag):
                    page_number = tag.get_page_number() + 1
                if result.get_error_code() == EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
                    print("Warning:", result.get_error_code(), result.get_error_string())
                elif result.get_error_code() != EnumErrorCode.EC_OK:
                    print("Error:", result.get_error_code(), result.get_error_string())
                barcode_result = result.get_decoded_barcodes_result()
                if barcode_result is None or barcode_result.get_items() == 0:
                    print("Page-"+str(page_number), "No barcode detected.")
                else:
                    items = barcode_result.get_items()
                    print("Page-"+str(page_number), "Decoded", len(items), "barcodes.")
                    for index,item in enumerate(items):
                        print("Result", index+1)
                        print("Barcode Format:", item.get_format_string())
                        print("Barcode Text:", item.get_text())
                print()
    input("Press Enter to quit...")
```

**Pattern Notes:**
- Uses `capture_multi_pages()` which returns a `CapturedResultArray` even for single images (handles multi-page files like PDF/TIFF).
- Iterates `result_array.get_results()` to get per-page `CapturedResult` objects, then calls `get_decoded_barcodes_result()`.
- Uses `EnumPresetTemplate.PT_READ_BARCODES` as the template name for barcode reading.

---

## 2. Batch Directory Processing

**File:** `Samples/read_multiple_images.py`

Processes all images in a directory using `DirectoryFetcher` + `CapturedResultReceiver` + `ImageSourceStateListener` pattern (asynchronous streaming).

```python
from dynamsoft_barcode_reader_bundle import *
import os

class MyCapturedResultReceiver(CapturedResultReceiver):

    def __init__(self) -> None:
        super().__init__()
    def on_decoded_barcodes_received(self, result: "DecodedBarcodesResult") -> None:
        tag = result.get_original_image_tag()
        if isinstance(tag, FileImageTag):
            print("File:", tag.get_file_path())
            print("Page:", tag.get_page_number() + 1)
        if result.get_error_code() == EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
            print("Warning:", result.get_error_string())
        elif result.get_error_code() != EnumErrorCode.EC_OK:
            print("Error:", result.get_error_string())
        items = result.get_items()
        print("Detected", len(items), "barcodes.")
        for index, item in enumerate(items):
            print("Result", index+1)
            print("Barcode Format:", item.get_format_string())
            print("Barcode Text:", item.get_text())

class MyImageSourceStateListener(ImageSourceStateListener):
    def __init__(self, cvr_instance:CaptureVisionRouter) -> None:
        super().__init__()
        self.cvr_instance = cvr_instance
    def on_image_source_state_received(self, state: int) -> None:
        if state == EnumImageSourceState.ISS_EXHAUSTED:
            if self.cvr_instance != None:
                self.cvr_instance.stop_capturing()
if __name__ == '__main__':
    # Initialize license.
    # You can request and extend a trial license from https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
    # The string 'DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==' here is a free public trial license. Note that network connection is required for this license to work.
    errorCode, errorMsg = LicenseManager.init_license("DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==")
    if errorCode != EnumErrorCode.EC_OK and errorCode != EnumErrorCode.EC_LICENSE_WARNING:
        print("License initialization failed: ErrorCode:", errorCode, ", ErrorString:", errorMsg)
    else:
        cvr_instance = CaptureVisionRouter()

        fetcher = DirectoryFetcher()
        fetcher.set_directory("../Images")
        cvr_instance.set_input(fetcher)

        receiver = MyCapturedResultReceiver()
        cvr_instance.add_result_receiver(receiver)

        listener = MyImageSourceStateListener(cvr_instance)
        cvr_instance.add_image_source_state_listener(listener)

        errorCode, errorMsg = cvr_instance.start_capturing(EnumPresetTemplate.PT_READ_BARCODES, True)
        if errorCode != EnumErrorCode.EC_OK:
            print("Error:", errorMsg)
    input("Press Enter to quit...")
```

**Pattern Notes:**
- Uses `DirectoryFetcher` to feed images from a folder, `CapturedResultReceiver` callback for async results, and `ImageSourceStateListener` to stop when all images are processed.
- `start_capturing(template, True)` — the `True` means "wait until done" (blocking call).
- The receiver's `on_decoded_barcodes_received` fires per-page with a `DecodedBarcodesResult` (not a `CapturedResult`).

---

## 3. Video/Camera Barcode Decoding

**File:** `Samples/video_decoding.py`

Real-time barcode decoding from camera or video file using OpenCV for frame capture and a custom `ImageSourceAdapter`.

```python
from dynamsoft_barcode_reader_bundle import *
try:
    import cv2
except ModuleNotFoundError:
    raise SystemExit(
        "OpenCV is required for this sample.\n"
        "Install it with:\n"
        "   python -m pip install opencv-python\n"
    )
import os

def silence_opencv():
    # OpenCV 4.5+
    if hasattr(cv2, "setLogLevel"):
        try:
            cv2.setLogLevel(0)  # LOG_LEVEL_SILENT
            return
        except Exception:
            pass

    if hasattr(cv2, "utils") and hasattr(cv2.utils, "logging"):
        try:
            cv2.utils.logging.setLogLevel(
                cv2.utils.logging.LOG_LEVEL_SILENT
            )
        except Exception:
            pass

class MyCapturedResultReceiver(CapturedResultReceiver):

    def __init__(self):
        super().__init__()

    def on_decoded_barcodes_received(self, result: DecodedBarcodesResult) -> None:
        if result.get_error_code() == EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
            print("Warning:", result.get_error_string())
        elif result.get_error_code() != EnumErrorCode.EC_OK:
            print("Error:", result.get_error_string())
        items = result.get_items()
        if len(items) != 0:
            tag: ImageTag = result.get_original_image_tag()
            if tag is not None:
                print("ImageID:",tag.get_image_id())
            print("Decoded", len(items), "barcodes.")
            for index,item in enumerate(items):
                print("Result", index+1)
                print("Barcode Format:", item.get_format_string())
                print("Barcode Text:", item.get_text())
                print()
class MyVideoFetcher(ImageSourceAdapter):

    def __init__(self):
        super().__init__()

    def has_next_image_to_fetch(self) -> bool:
         return True

def decode_video(use_video_file: bool = False, video_file_path: str = "") -> None:
    cvr_instance = CaptureVisionRouter()

    fetcher = MyVideoFetcher()
    fetcher.set_max_image_count(100)
    fetcher.set_buffer_overflow_protection_mode(EnumBufferOverflowProtectionMode.BOPM_UPDATE)
    fetcher.set_colour_channel_usage_type(EnumColourChannelUsageType.CCUT_AUTO)
    cvr_instance.set_input(fetcher)

    filter = MultiFrameResultCrossFilter()
    filter.enable_result_cross_verification(EnumCapturedResultItemType.CRIT_BARCODE, True)
    filter.enable_result_deduplication(EnumCapturedResultItemType.CRIT_BARCODE, True)
    filter.set_duplicate_forget_time(EnumCapturedResultItemType.CRIT_BARCODE, 5000)
    cvr_instance.add_result_filter(filter)

    receiver = MyCapturedResultReceiver()
    cvr_instance.add_result_receiver(receiver)

    error_code, error_msg = cvr_instance.start_capturing(EnumPresetTemplate.PT_READ_BARCODES, False)
    if error_code != EnumErrorCode.EC_OK:
        print("Error:", error_msg)
    else:
        video_width = 0
        video_height = 0
        vc: cv2.VideoCapture = None
        if not use_video_file:
            # a. Decode video from camera
            vc = cv2.VideoCapture(0)
            if not vc.isOpened():
                raise RuntimeError("Camera not found or cannot be opened")
        else:
            # # b. Decode video file
            vc = cv2.VideoCapture(video_file_path)
            if not vc.isOpened():
                raise RuntimeError("File not found or cannot be opened")

        video_width  = int(vc.get(cv2.CAP_PROP_FRAME_WIDTH))
        video_height = int(vc.get(cv2.CAP_PROP_FRAME_HEIGHT))
        vc.set(3, video_width) #set width
        vc.set(4, video_height) #set height

        if not vc.isOpened():
            cvr_instance.stop_capturing(False, True)
            return

        windowName = "Video Barcode Reader"

        image_id = 0
        while True:
            image_id += 1
            rval, frame = vc.read()
            if rval == False:
                break
            tag = FileImageTag("",0,0)
            tag.set_image_id(image_id)
            image = ImageData(frame.tobytes(), frame.shape[1], frame.shape[0], frame.strides[0], EnumImagePixelFormat.IPF_RGB_888, 0, tag)
            fetcher.add_image_to_buffer(image)
            cv2.imshow(windowName, frame)
            # 'ESC' for quit
            key = cv2.waitKey(1)
            if key == 27:
                break

        cvr_instance.stop_capturing(False, True)
        cv2.destroyWindow(windowName)

def get_mode_and_path():
    use_video_file = False
    video_file_path = ""
    while True:
        try:
            mode = int(
                input(
                    ">> Choose a Mode Number:\n"
                    "1. Decode video from camera.\n"
                    "2. Decode video from file.\n"
                    ">> 1 or 2:\n"
                ))
            if mode == 1 or mode == 2:
                if mode == 1:
                    use_video_file = False
                    break

                use_video_file = True
                while True:
                    video_file_path = input(">> Input your video full path:\n").strip(' \'"')
                    if not os.path.exists(video_file_path):
                        print("Error:File not found.\n")
                        continue
                    break
                break
            else:
                raise ValueError
        except ValueError:
            print("Error:Wrong input.\n")
            continue

    return use_video_file, video_file_path

if __name__ == "__main__":
    silence_opencv()

    print("-------------------start------------------------")

    try:
        # Initialize license.
        # The string "DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==" here is a free public trial license. Note that network connection is required for this license to work.
        # You can also request a 30-day trial license in the customer portal: https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
        errorCode, errorMsg = LicenseManager.init_license("DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==")
        if errorCode != EnumErrorCode.EC_OK and errorCode != EnumErrorCode.EC_LICENSE_WARNING:
            print("License initialization failed: ErrorCode:", errorCode, ", ErrorString:", errorMsg)
        else:
            # Decode video from file or camera
            use_video_file, video_file_path = get_mode_and_path()
            decode_video(use_video_file, video_file_path)

    except Exception as e:
        print(e)

    print("-------------------over------------------------")
```

**Pattern Notes:**
- Uses `ImageSourceAdapter` subclass (`MyVideoFetcher`) with `has_next_image_to_fetch() -> True` to create an infinite frame source.
- Constructs `ImageData` from OpenCV frames: `ImageData(frame.tobytes(), width, height, stride, EnumImagePixelFormat.IPF_RGB_888, 0, tag)`.
- Uses `MultiFrameResultCrossFilter` for cross-verification and deduplication with `set_duplicate_forget_time(5000)`.
- `start_capturing(template, False)` — `False` means non-blocking; the main loop feeds frames via `fetcher.add_image_to_buffer(image)`.

---

## 4. DPM Barcode Reader

**File:** `Samples/read_dpm_barcode.py`

Reads Direct Part Marking (DPM) barcodes using a custom template.

```python
from dynamsoft_barcode_reader_bundle import *
import os
from pathlib import Path

BASE_DIR = Path(__file__).resolve().parent

if __name__ == "__main__":
    try:
        # 1 Initialize license.
        # The string "DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==" here is a free public trial license. Note that network connection is required for this license to work.
        # You can also request a 30-day trial license in the customer portal: https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
        errorCode, errorMsg = LicenseManager.init_license("DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==")
        if errorCode != EnumErrorCode.EC_OK and errorCode != EnumErrorCode.EC_LICENSE_WARNING:
            raise Exception("License initialization failed: ErrorCode: "+ str(errorCode) + ", ErrorString:" + errorMsg)
        else:
            cvr_instance = CaptureVisionRouter()
            template_path = str(BASE_DIR.parent / "CustomTemplates" / "ReadDPM.json")
            errorCode, errorMsg = cvr_instance.init_settings_from_file(template_path)
            if errorCode != EnumErrorCode.EC_OK:
                raise Exception("Init template failed: " + errorMsg)

            # 2 Replace with your own dpm barcode image path
            image_path = str(BASE_DIR.parent / "Images" / "DPM.png")

            # 3 Decode barcodes from the image file.
            result_array = cvr_instance.capture_multi_pages(image_path,"")

            # 4 Output the barcode format and barcode text.
            results = result_array.get_results()
            if results is None or len(results) == 0:
                print("No barcode detected.")
            else:
                for i, result in enumerate(results):
                    page_number = i + 1
                    tag = result.get_original_image_tag()
                    if isinstance(tag, FileImageTag):
                        page_number = tag.get_page_number() + 1
                    if result.get_error_code() == EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
                        print("Warning:", result.get_error_code(), result.get_error_string())
                    elif result.get_error_code() != EnumErrorCode.EC_OK:
                        print("Error:", result.get_error_code(), result.get_error_string())

                    barcode_result = result.get_decoded_barcodes_result()
                    if barcode_result is None or barcode_result.get_items() == 0:
                        print("Page-"+str(page_number), "No barcode detected.")
                    else:
                        items = barcode_result.get_items()
                        print("Page-"+str(page_number), "Decoded", len(items), "barcodes.")
                        for index,item in enumerate(items):
                            print()
                            print("Barcode", index)
                            print("Barcode Format:", item.get_format_string())
                            print("Barcode Text:", item.get_text())
                    print()
    except Exception as e:
        print(e)
```

**Pattern Notes:**
- Loads custom DPM template via `init_settings_from_file()`, then passes `""` (empty string) as template name to `capture_multi_pages()` — this uses the first/default template in the loaded JSON.
- Uses try/except pattern instead of if/else for license errors (raises Exception).
- Same barcode result extraction pattern as read_an_image.py.

---

## 5. General Settings

**File:** `Samples/general_settings.py`

Demonstrates how to modify `SimplifiedCaptureVisionSettings` to configure barcode format, count, ROI, and grayscale transformation.

```python
import os
from dynamsoft_barcode_reader_bundle import *
from pathlib import Path
BASE_DIR = Path(__file__).resolve().parent
if __name__ == "__main__":
    try:
        # 1. Initialize license.
        # The string "DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==" here is a free public trial license. Note that network connection is required for this license to work.
        # You can also request a 30-day trial license in the customer portal: https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
        err_code, err_str = LicenseManager.init_license("DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==")
        if err_code != EnumErrorCode.EC_OK and err_code != EnumErrorCode.EC_LICENSE_WARNING:
            print("License initialization failed: ErrorCode:", err_code, ", ErrorString:", err_str)
        else:
            # 2. Create an instance of CaptureVisionRouter.
            cvr_instance = CaptureVisionRouter()

            # 3. General settings (including barcode format, barcode count and scan region) through SimplifiedCaptureVisionSettings
            # 3.1 Obtain current runtime settings of instance.
            err_code, err_str, settings = cvr_instance.get_simplified_settings(EnumPresetTemplate.PT_READ_BARCODES)

            # 3.2 Set the expected barcode format you want to read.
            settings.barcode_settings.barcode_format_ids = EnumBarcodeFormat.BF_PDF417 | EnumBarcodeFormat.BF_QR_CODE

            # 3.3 Set the expected barcode count you want to read.
            settings.barcode_settings.expected_barcodes_count = 10

            # 3.4 Set the grayscale transformation modes.
            settings.barcode_settings.grayscale_transformation_modes[0] = EnumGrayscaleTransformationMode.GTM_AUTO

            # 3.5 Set the ROI(region of interest) to speed up the barcode reading process.
            # Note: DBR supports setting coordinates by pixels or percentages. The origin of the coordinate system is the upper left corner point.
            settings.roi_measured_in_percentage = 1
            points = settings.roi.points
            points[0].x = 0
            points[0].y = 0
            points[1].x = 100
            points[1].y = 0
            points[2].x = 100
            points[2].y = 100
            points[3].x = 0
            points[3].y = 100

            # 3.6 Apply the new settings to the instance.
            err_code, err_str = cvr_instance.update_settings(EnumPresetTemplate.PT_READ_BARCODES, settings)
            if err_code != EnumErrorCode.EC_OK:
                print("Update settings failed: ErrorCode:", err_code, ", ErrorString:", err_str)
            # 4.Replace by your own image path
            image_path = str(BASE_DIR.parent / "Images" / "GeneralBarcodes.png")

            # 5.Decode barcodes from an image file.
            result_array = cvr_instance.capture_multi_pages(image_path, EnumPresetTemplate.PT_READ_BARCODES)

            # 6.Output the barcode text.
            results = result_array.get_results()
            if results is None or len(results) == 0:
                print("No barcode detected.")
            else:
                for i, result in enumerate(results):
                    page_number = i + 1
                    tag = result.get_original_image_tag()
                    if isinstance(tag, FileImageTag):
                        page_number = tag.get_page_number() + 1

                    if result.get_error_code() == EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
                        print("Warning:", result.get_error_code(), result.get_error_string())
                    elif result.get_error_code() != EnumErrorCode.EC_OK:
                        print("Error:", result.get_error_code(), result.get_error_string())

                    barcode_result = result.get_decoded_barcodes_result()
                    if barcode_result is None or barcode_result.get_items() == 0:
                        print("No barcode found in page", page_number)
                    else:
                        items = barcode_result.get_items()
                        print("Page", page_number, "decoded", len(items), "barcodes.")
                        for index,item in enumerate(items):
                            print()
                            print("Result", str(page_number) + "-" + str(index + 1))
                            print("Barcode Format:", item.get_format_string())
                            print("Barcode Text:", item.get_text())
                    print()
    except Exception as e:
        print(e)
```

**Pattern Notes:**
- Uses `cvr_instance.get_simplified_settings(template)` to get a `SimplifiedCaptureVisionSettings` object, modifies it, then applies with `cvr_instance.update_settings(template, settings)`.
- Key settings: `settings.barcode_settings.barcode_format_ids`, `settings.barcode_settings.expected_barcodes_count`, `settings.barcode_settings.grayscale_transformation_modes[0]`, `settings.roi_measured_in_percentage`, `settings.roi.points`.
- Demonstrates combining barcode formats with bitwise OR: `EnumBarcodeFormat.BF_PDF417 | EnumBarcodeFormat.BF_QR_CODE`.

---

## 6. Parameter Tuner

**File:** `Samples/parameter_tuner.py`

Interactive template/image selector that lets users try different templates on different images, with timing measurement.

```python
import time
import os
import dynamsoft_barcode_reader_bundle
from pathlib import Path
from dynamsoft_barcode_reader_bundle import *

BASE_DIR = Path(__file__).resolve().parent
PKG_DIR = Path(dynamsoft_barcode_reader_bundle.__file__).resolve().parent

class LoopInfo():
    def __init__(self,cvr_instance : CaptureVisionRouter, image_path: str = None,matched_template: str = None, description: str = None, template_path: str = None):
        self.cvr_instance = cvr_instance
        self.image_path = image_path
        self.template_path = template_path
        self.matched_template = matched_template
        self.description = description

sample_images = {
    "1": ("Images/blurry.png", "ReadBlurry1DBarcode.json", "Suitable for blurred 1D barcode"),
    "2": ("Images/GeneralBarcodes.png", "ReadMultipleBarcode.json", "Suitable for multiple barcodes"),
    "3": ("Images/inverted-barcode.png", "ReadInvertedBarcode.json", "Suitable for colour inverted barcode"),
    "4": ("Images/DPM.png", "ReadDPM.json", "Suitable for Direct Part Marking barcode"),
    "5": ("Images/EAN-13.jpg", "ReadOneDRetail.json", "Suitable for retail 1D barcode such as EAN13, UPC-A"),
    "6": ("Images/OneDIndustrial.jpg", "ReadOneDIndustrial.json", "Suitable for industrial 1D barcode such as Code128, Code39"),
}

def select_image():
    print("Available Sample Scenarios:")
    print("[1] Blurry 1D barcode")
    print("[2] Multiple barcodes")
    print("[3] Colour Inverted Barcode")
    print("[4] Direct Part Marking (DPM)")
    print("[5] Retail 1D barcode")
    print("[6] Industrial 1D barcode")
    print("[7] Custom Image")

    while True:
        choice = input("\nEnter the number of the image to test, or provide a full path to your own image:\n> ").strip(' \'"')
        image_path, matched_template, description = None, None, None
        if choice in sample_images:
            image_path, matched_template, description = sample_images[choice]
            image_path = str(BASE_DIR.parent / image_path)
        elif choice == "7":
            image_path = input("Enter full path to your custom image:\n> ").strip(' \'"')
            if not os.path.isfile(image_path):
                print("Invalid path input, please try again.")
                continue
        else:
            image_path = choice
            if not os.path.isfile(image_path):
                print("Invalid path input, please try again.")
                continue
        image_path = os.path.abspath(image_path)
        return image_path, matched_template, description

def select_template(matched_template, description):
    print("\nSelect template for this image:")

    options = []

    if matched_template:
        options.append((matched_template, description))
    options.append(("ReadBarcodes_Default.json", "General purpose settings"))
    options.append(("Custom template", "Use your own template"))

    for idx, (path, desc) in enumerate(options, start=1):
            print(f"[{idx}] {path} ({desc})")

    print("\nEnter the number of the template to test, or provide a full path to your own template:")

    while True:
        choice = input("> ").strip(' \'"')
        selected_path = None
        if choice.isdigit():
            index = int(choice) - 1
            if 0 <= index < len(options):
                selected_path = options[index][0]
                if selected_path == options[-1][0]:
                    selected_path = input("Enter full path to your custom template:\n> ").strip(' \'"')
                elif selected_path == options[-2][0]:
                    selected_path = str(PKG_DIR/"Templates"/"DBR-PresetTemplates.json")
                else:
                    selected_path = str(BASE_DIR.parent/"CustomTemplates"/selected_path)
            else:
                print("Invalid choice, please try again.")
                continue
        else:
            selected_path = choice
        if selected_path:
            selected_path = os.path.abspath(selected_path)
            if not os.path.isfile(selected_path):
                print("Invalid template path, please try again.")
                continue
            return selected_path
        else:
            print("Invalid input, please try again.")

def run(cvr_instance:CaptureVisionRouter, image_path:str, template_path:str):
    print("\nRunning with:")
    print(f"Image: {image_path}")
    print(f"Template: {template_path}")
    start_time = time.time()
    result_array = cvr_instance.capture_multi_pages(image_path,"")
    elapsed_ms = int((time.time() - start_time) * 1000)
    results = result_array.get_results()
    if results is None or len(results) == 0:
        print("No results.")
    else:
        for i, result in enumerate(results):
            page_number = i + 1
            total_pages = 0
            tag = result.get_original_image_tag()
            if isinstance(tag, FileImageTag):
                page_number = tag.get_page_number() + 1
                total_pages = tag.get_total_pages()
            print(f"\nResult{' Page-' + str(page_number) if total_pages > 0 else ''}:")
            error_code = result.get_error_code()
            if error_code != EnumErrorCode.EC_OK and error_code != EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
                print(f"Error: {error_code}, {result.get_error_string()}")
            barcode_result = result.get_decoded_barcodes_result()
            if barcode_result is not None:
                items = barcode_result.get_items()
                for j, item in enumerate(items):
                    if isinstance(item, BarcodeResultItem):
                        print(f"Barcode result [{i+1}-{j+1}]: {item.get_text()} (Format: {item.get_format_string()})")
            else:
                print("No barcode detected.")
    print(f"Time used: {elapsed_ms} ms...\n")

def loop_inner(loop_info : LoopInfo, get_image: bool = True, get_template: bool = True):
    if get_image:
        loop_info.image_path, loop_info.matched_template, loop_info.description = select_image()
    if get_template:
        loop_info.template_path = select_template(loop_info.matched_template, loop_info.description)
        error_code, error_string = loop_info.cvr_instance.init_settings_from_file(loop_info.template_path)
        if error_code != EnumErrorCode.EC_OK and error_code != EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
            print("Init template failed:", error_code, error_string)
            return

    run(loop_info.cvr_instance, loop_info.image_path, loop_info.template_path)

def main():

    print("Welcome to ParameterTuner!\n")

    # Initialize license.
    # The string "DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==" here is a free public trial license. Note that network connection is required for this license to work.
    # You can also request a 30-day trial license in the customer portal: https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
    error_code, error_string = LicenseManager.init_license("DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==")
    if error_code != EnumErrorCode.EC_OK and error_code != EnumErrorCode.EC_LICENSE_WARNING:
        print("License initialization failed: ErrorCode:", str(error_code) + ", ErrorString:", error_string)

    loop_info = LoopInfo(CaptureVisionRouter())
    loop_inner(loop_info)

    while True:
        print("What would you like to do next?")
        print("[1] Try a different template")
        print("[2] Load another image")
        print("[3] Exit")
        choice = input("Enter your choice:\n> ").strip()
        if choice == "1":
            loop_inner(loop_info, get_image=False, get_template=True)
        elif choice == "2":
            loop_inner(loop_info, get_image=True, get_template=False)
        elif choice == "3":
            print("Thank you for using ParameterTuner!")
            break
        else:
            print("Invalid input. Returning to main menu.")

if __name__ == "__main__":
    main()
```

**Pattern Notes:**
- Shows how to load templates dynamically via `init_settings_from_file()` and switch between them.
- Uses `tag.get_total_pages()` to check if the file has multiple pages.
- Demonstrates timing measurement with `time.time()`.

---

## 7. Multi-Format Image Processing

**File:** `Samples/multi_format_image_processing.py`

Demonstrates how to pass images in multiple formats: file path, `ImageData`, raw bytes, OpenCV ndarray, and PIL Image.

```python
from dynamsoft_barcode_reader_bundle import *
try:
    import cv2
except ModuleNotFoundError:
    raise SystemExit(
        "OpenCV is required for this sample.\n"
        "Install it with:\n"
        "   python -m pip install opencv-python\n"
    )
from PIL import Image
import numpy as np
from pathlib import Path

BASE_DIR = Path(__file__).resolve().parent

def silence_opencv():
    # OpenCV 4.5+
    if hasattr(cv2, "setLogLevel"):
        try:
            cv2.setLogLevel(0)  # LOG_LEVEL_SILENT
            return
        except Exception:
            pass

    if hasattr(cv2, "utils") and hasattr(cv2.utils, "logging"):
        try:
            cv2.utils.logging.setLogLevel(
                cv2.utils.logging.LOG_LEVEL_SILENT
            )
        except Exception:
            pass

if __name__ == "__main__":
    silence_opencv()

    try:
        # 1.Initialize license.
        # The string "DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==" here is a free public trial license. Note that network connection is required for this license to work.
        # You can also request a 30-day trial license in the customer portal: https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
        err_code, err_str = LicenseManager.init_license("DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==")
        if err_code != EnumErrorCode.EC_OK and err_code != EnumErrorCode.EC_LICENSE_WARNING:
            print("License initialization failed: ErrorCode:", err_code, ", ErrorString:", err_str)
        else:
            # 2. Create an instance of CaptureVisionRouter.
            cvr_instance = CaptureVisionRouter()
            options = [
                "exit program",
                "decode with file",
                "decode with buffer",
                "decode with bytes",
                "decode with opencv",
                "decode with PIL",
            ]
            file_path = str(BASE_DIR.parent / "Images" / "GeneralBarcodes.png")
            while True:
                # 3. Choose decode mode.
                for i, option in enumerate(options):
                    print(f"{i}. {option}")
                choice = input("Enter your choice: ")
                if not choice.isdigit() or int(choice) >= len(options) or int(choice) < 0:
                    print("Unsupported options.")
                    continue
                if int(choice) == 0:
                    break
                elif int(choice) == 1:
                    #decode image with file path.
                    image_data = file_path
                elif int(choice) == 2:
                    #decode image with dynamsoft_barcode_reader_bundle.core.ImageData
                    image_io = ImageIO()
                    err, image_data = image_io.read_from_file(file_path)
                elif int(choice) == 3:
                    #decode image with bytes
                    image_data = open(file_path, "rb").read()
                elif int(choice) == 4:
                    #decode image with opencv
                    image_data = cv2.imread(file_path)
                elif int(choice) == 5:
                    #decode image with PIL
                    image = Image.open(file_path)
                    image_data = np.array(image)
                else:
                    raise ValueError("An unexpected value.")

                # 4. Decode barcodes from the image.
                captured_result = cvr_instance.capture(image_data,EnumPresetTemplate.PT_READ_BARCODES)

                # 5. Output the barcode result.
                if captured_result.get_error_code() == EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
                    print("Warning:", captured_result.get_error_code(), captured_result.get_error_string())
                elif captured_result.get_error_code() != EnumErrorCode.EC_OK:
                    print("Error:", captured_result.get_error_code(), captured_result.get_error_string())

                barcode_result = captured_result.get_decoded_barcodes_result()
                if barcode_result is None or barcode_result.get_items() == 0:
                    print("No barcode detected.")
                else:
                    items = barcode_result.get_items()
                    print("Decoded", len(items), "barcodes.")
                    for index,item in enumerate(items):
                        print("Result", index+1)
                        print("Barcode Format:", item.get_format_string())
                        print("Barcode Text:", item.get_text())

                print()
    except Exception as e:
        print(e)
    input("Press Enter to quit...")
```

**Pattern Notes:**
- Uses `cvr_instance.capture()` (single-page) instead of `capture_multi_pages()`.
- Demonstrates 5 input formats: file path (str), `ImageData` via `ImageIO().read_from_file()`, raw bytes, OpenCV ndarray (`cv2.imread()`), PIL `np.array(Image.open())`.
- `capture()` returns a single `CapturedResult` directly (not a `CapturedResultArray`).

---

## 8. Server-Side Barcode Decoder

**File:** `Samples/server_side_barcode_decoder.py`

Flask-based REST API endpoint for barcode decoding, accepting file uploads, JSON with base64, or raw binary.

```python
from dynamsoft_barcode_reader_bundle import *
from flask import Flask, request, jsonify
from typing import List, Tuple
import base64
app = Flask(__name__)

def decode_barcode_inner(data) -> Tuple[int, str, List[str]]:
    cvr_instance = CaptureVisionRouter()
    ret = []
    error_code = None
    error_string = None
    result = cvr_instance.capture(data,EnumPresetTemplate.PT_READ_BARCODES)
    if result.get_error_code() != EnumErrorCode.EC_OK and result.get_error_code() != EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
        print("Error:", result.get_error_code(), result.get_error_string())
        error_code = result.get_error_code()
        error_string = result.get_error_string()
    else:
        error_code = EnumErrorCode.EC_OK
        error_string = "Successful."
    barcode_result = result.get_decoded_barcodes_result()
    if barcode_result is None or barcode_result.get_items() == 0:
        print("No barcode detected.")
    else:
        items = barcode_result.get_items()
        print("Decoded", len(items), "barcodes.")
        for item in items:
            ret.append(item.get_text())
    return error_code, error_string, ret

@app.route('/decode_barcode', methods=['POST'])
def decode_barcode():
    """
    Barcode decoding endpoint: Accepts barcode data and returns the decoded results.

    Request Method:
        POST

    Request Headers:
        - Content-Type: Can be one of the following:
            1. multipart/form-data
            2. application/json
            3. Other binary content types

    Request Body:
        - If Content-Type is multipart/form-data:
            Include a file field named 'file' containing the barcode image file.
        - If Content-Type is application/json:
            JSON format with a 'data' field containing the Base64-encoded barcode data.
        - If Content-Type is other:
            The request body should directly contain the binary barcode data.

    Response:
        - On success: Returns a JSON array of decoded barcodes.
        - On failure: Returns error code and error message with an appropriate HTTP status code.

    Examples:
        1. Using multipart/form-data to upload a file:
            curl -X POST -F "file=@barcode.png" http://<server_ip>:8000/decode_barcode
        2. Using application/json to send Base64 data:
            curl -X POST -H "Content-Type: application/json" -d '{"data": "base64_encoded_data"}' http://<server_ip>:8000/decode_barcode
        3. Sending binary data directly:
            curl -X POST --data-binary @barcode.png http://<server_ip>:8000/decode_barcode
    """
    try:
        # get data
        content_type = request.content_type
        data = None
        if content_type.startswith('multipart/form-data'):
            if 'file' in request.files:
                file = request.files['file']
                data = file.read()
            else:
                return "No file found in multipart data", 400

        elif content_type == 'application/json':
            json_data = request.get_json(silent=True)
            if json_data:
                data = json_data.get('data')
                if data is None:
                    return "No 'data' key found in JSON", 400
                data = base64.b64decode(data)
            else:
                return "Invalid JSON", 400

        else:
            data = request.get_data()

        # Decode the barcode
        error_code, error_string, barcodes = decode_barcode_inner(data)
        if error_code != EnumErrorCode.EC_OK:
            return jsonify({
                'error_string': error_string,
                'error_code': error_code
                }), 400
        return jsonify(barcodes), 200
    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':

    # Initialize license.
    # You can request and extend a trial license from https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
    # The string 'DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==' here is a free public trial license. Note that network connection is required for this license to work.
    error_code, error_string = LicenseManager.init_license("DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==")
    if error_code != EnumErrorCode.EC_OK and error_code != EnumErrorCode.EC_LICENSE_WARNING:
        print("License initialization failed: ErrorCode:", error_code, ", ErrorString:", error_string)
    else:
        app.run(host='0.0.0.0', port=8000)
```

**Pattern Notes:**
- Creates a new `CaptureVisionRouter()` per request (simple but not production-optimal).
- Shows that `capture()` accepts raw bytes (from `file.read()` or `base64.b64decode()`) directly.
- Uses Flask for HTTP serving; license is initialized once at startup.

---

## 9. Localized vs Decoded Barcodes

**File:** `Samples/show_localized_vs_decoded_barcodes.py`

Shows intermediate results: draws red outlines for localized-but-not-decoded barcodes and green outlines for successfully decoded ones.

```python
from dynamsoft_barcode_reader_bundle import *
import os
from pathlib import Path

BASE_DIR = Path(__file__).resolve().parent

class MyIntermediateResultReceiver(IntermediateResultReceiver):
    """
    A receiver class that records location and decoding information
    from intermediate barcode decoding results.

    Attributes:
        locations (list): Stores locations from localized barcodes.
        result_locs (list): Stores locations from decoded barcodes.
    """
    def __init__(self):
        self.locations = []
        super().__init__()
    def on_localized_barcodes_received(self, result: "LocalizedBarcodesUnit", info: IntermediateResultExtraInfo) -> None:
        if info.is_section_level_result:
            try:
                for i in range(result.get_count()):
                    element = result.get_localized_barcode(i)
                    self.locations.append(element.get_location())
            except Exception as e:
                print("on_localized_barcodes_received error:",e)

def is_within_10_percent(area1, area2):
    if area1 == 0 or area2 == 0:
        return False
    ratio = abs(area1 - area2) / max(area1, area2)
    return ratio <= 0.10

def seem_as_same_location(location: Quadrilateral, result_loc: Quadrilateral) -> bool:
    x = sum(p.x for p in location.points) / len(location.points)
    y = sum(p.y for p in location.points) / len(location.points)
    central_point = Point(int(x),int(y))
    if not result_loc.contains(central_point):
        return False
    if is_within_10_percent(location.get_area(), result_loc.get_area()):
        return True
    return False

def remove_if_loc_exists_in_result_locs(locations: List[Quadrilateral], result_locs:List[Quadrilateral]) -> Tuple[List[Quadrilateral], List[Quadrilateral]]:
    if not locations or not result_locs:
        return locations, result_locs
    ret_loc, ret_res_loc = [], []

    excluded_loc,include_res_locs = set(), set()

    for i in range(len(locations)):
        for j in range(len(result_locs)):
            if seem_as_same_location(locations[i], result_locs[j]):
                include_res_locs.add(j)
                excluded_loc.add(i)
                break

    for i in include_res_locs:
        ret_res_loc.append(result_locs[i])

    for i in range(len(locations)):
        if i not in excluded_loc:
            ret_loc.append(locations[i])
    return ret_loc, ret_res_loc

def draw_on_image(image: ImageData, locations: List[Quadrilateral], result_locs:List[Quadrilateral]) -> ImageData:
    drawer = ImageDrawer()
    loc, res_loc = remove_if_loc_exists_in_result_locs(locations, result_locs)
    if loc:
        image = drawer.draw_on_image(image, loc, 0xFFFF0000, 2)
    if res_loc:
        image = drawer.draw_on_image(image, res_loc, 0xFF00FF00, 2)
    return image

if __name__ == '__main__':
    # 1. Initialize license.
    # You can request and extend a trial license from https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
    # The string 'DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==' here is a free public trial license. Note that network connection is required for this license to work.
    errorCode, errorMsg = LicenseManager.init_license("DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==")
    if errorCode != EnumErrorCode.EC_OK and errorCode != EnumErrorCode.EC_LICENSE_WARNING:
        print("License initialization failed: ErrorCode:", errorCode, ", ErrorString:", errorMsg)
    else:
        # 2. Create an instance of CaptureVisionRouter.
        cvr_instance = CaptureVisionRouter()

        im = cvr_instance.get_intermediate_result_manager()
        irr = MyIntermediateResultReceiver()
        im.add_result_receiver(irr)

        # 3. Replace by your own image path.
        image_path = str(BASE_DIR.parent / "Images" / "GeneralBarcodes.png")

        # 4. Read image from file.
        io = ImageIO()
        err, image = io.read_from_file(image_path)
        if err != EnumErrorCode.EC_OK:
            print("Failed to read image:", err)
            exit()
        # 5. Update settings to get orginal image.
        _, _, settings = cvr_instance.get_simplified_settings(EnumPresetTemplate.PT_READ_BARCODES)
        settings.output_original_image = 1
        cvr_instance.update_settings(EnumPresetTemplate.PT_READ_BARCODES, settings)

        # 6. Decode barcodes from the image.
        result = cvr_instance.capture(image, EnumPresetTemplate.PT_READ_BARCODES)

        # 7. Check error code.
        if result.get_error_code() == EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
            print("Warning:", result.get_error_code(), result.get_error_string())
        elif result.get_error_code() != EnumErrorCode.EC_OK:
            print("Error:", result.get_error_code(), result.get_error_string())

        # 8. Get original image.
        for item in result.get_items():
            if isinstance(item, OriginalImageResultItem):
                image = item.get_image_data()
                break
        # 9. Extract the locations of decoded barcodes from the result.
        result_locs = []
        barcode_result = result.get_decoded_barcodes_result()
        if barcode_result:
            for i,item in enumerate(barcode_result.get_items()):
                result_locs.append(item.get_location())

        # 10. Draw the outline border of the barcodes on the image.
        # The barcodes that have been decode successfully are marked as green(0xFF00FF00)
        # The barcodes that only have been localized are marked as red(0xFFFF0000)
        if irr.locations or result_locs:
            image_complete = draw_on_image(image, irr.locations, result_locs)

            result_image_path = os.path.join(os.path.dirname(image_path),
                                        os.path.splitext(os.path.basename(image_path))[0] + "_result.png")

            # 11. Save the image.
            io.save_to_file(image_complete,result_image_path)
            import platform
            system = platform.system()
            if system == "Windows":
                os.startfile(result_image_path)
            elif system == "Darwin":
                os.system(f"open '{result_image_path}'")
            else:
                ret = os.system(f"xdg-open '{result_image_path}'")
                if ret != 0:
                    print("Failed to open the result image. Please check the file manually:", result_image_path)
        else:
            print("No barcode detected.")
    input("Press Enter to quit...")
```

**Pattern Notes:**
- Uses `IntermediateResultReceiver` with `on_localized_barcodes_received()` to capture localized barcode positions before decoding.
- Uses `ImageDrawer().draw_on_image(image, quads, color, thickness)` to draw colored outlines on the image.
- Sets `settings.output_original_image = 1` to include original image in results, retrieved via `OriginalImageResultItem`.
- Uses `ImageIO().read_from_file()` and `ImageIO().save_to_file()` for image I/O.

---

## 10. Custom Template JSON Files

### 10.1 ReadBlurryBarcode.json

Optimizes for blurry 1D barcode reading with multiple deblur modes including neural network.

```json
{

  "CaptureVisionTemplates": [
    {
      "Name": "ReadBlurryBarcode",
      "ImageROIProcessingNameArray": [
        "TA_0"
      ]
    }
  ],
  "TargetROIDefOptions": [
    {
      "Name": "TA_0",
      "TaskSettingNameArray": [
        "BR_0"
      ]
    }
  ],
  "BarcodeReaderTaskSettingOptions": [
    {
      "Name": "BR_0",
      "ExpectedBarcodesCount": 1,
      "BarcodeFormatIds": [
        "BF_ONED"
      ],
      "SectionArray": [
        {
          "Section": "ST_REGION_PREDETECTION"
        },
        {
          "Section": "ST_BARCODE_LOCALIZATION"
        },
        {
          "Section": "ST_BARCODE_DECODING",
          "StageArray": [
            {
              "Stage": "SST_DECODE_BARCODES",
              "DeblurModes": [
                { "Mode": "DM_BASED_ON_LOC_BIN" },
                { "Mode": "DM_THRESHOLD_BINARIZATION" },
                { "Mode": "DM_DIRECT_BINARIZATION" },
                { "Mode": "DM_SMOOTHING" },
                { "Mode": "DM_GRAY_EQUALIZATION" },
                { "Mode": "DM_DEEP_ANALYSIS" },
                {
                  "DeblurModelNameArray": ["OneDDeblur"],
                  "Mode": "DM_NEURAL_NETWORK"
                }
              ]
            }
          ]
        }
      ]
    }
  ],
  "CaptureVisionModelOptions": [
    {
      "Name": "OneDDeblur"
    }
  ]
}
```

**Template Notes:**
- Focuses on `BF_ONED` barcode format with extensive `DeblurModes` in the decoding section.
- Includes `DM_NEURAL_NETWORK` with `DeblurModelNameArray: ["OneDDeblur"]` and declares the model in `CaptureVisionModelOptions`.

---

### 10.2 ReadDPM.json

Configures for Direct Part Marking (DPM) DataMatrix barcode reading.

```json
{
    "CaptureVisionTemplates": [
        {
            "Name": "ReadDPM",
            "ImageROIProcessingNameArray": [
                "roi_read_dpm"
            ],
            "MaxParallelTasks": 0,
            "Timeout": 3000
        }
    ],
    "TargetROIDefOptions": [
        {
            "Name": "roi_read_dpm",
            "TaskSettingNameArray": [
                "task_read_dpm"
            ]
        }
    ],
    "BarcodeReaderTaskSettingOptions": [
        {
            "Name": "task_read_dpm",
            "ExpectedBarcodesCount": 1,
            "BarcodeFormatIds": [
                "BF_DATAMATRIX"
            ],
            "DPMCodeReadingModes": [
                {
                    "Mode": "DPMCRM_GENERAL"
                }
            ],
            "SectionArray": [
                {
                    "Section": "ST_REGION_PREDETECTION",
                    "ImageParameterName": "ip_default",
                    "StageArray": [
                        {
                            "Stage": "SST_PREDETECT_REGIONS"
                        }
                    ]
                },
                {
                    "Section": "ST_BARCODE_LOCALIZATION",
                    "ImageParameterName": "ip_default",
                    "StageArray": [
                        {
                            "Stage": "SST_LOCALIZE_CANDIDATE_BARCODES",
                            "LocalizationModes": [
                                {
                                    "Mode": "LM_STATISTICS_MARKS"
                                },
                                {
                                    "Mode": "LM_CONNECTED_BLOCKS"
                                }
                            ]
                        },
                        {
                            "Stage": "SST_LOCALIZE_BARCODES"
                        }
                    ]
                },
                {
                    "Section": "ST_BARCODE_DECODING",
                    "ImageParameterName": "ip_default",
                    "StageArray": [
                        {
                            "Stage": "SST_RESIST_DEFORMATION"
                        },
                        {
                            "Stage": "SST_COMPLEMENT_BARCODE"
                        },
                        {
                            "Stage": "SST_SCALE_BARCODE_IMAGE"
                        },
                        {
                            "Stage": "SST_DECODE_BARCODES"
                        }
                    ]
                }
            ]
        }
    ]
}
```

**Template Notes:**
- Targets `BF_DATAMATRIX` format with `DPMCodeReadingModes: [{"Mode": "DPMCRM_GENERAL"}]`.
- Uses `LM_STATISTICS_MARKS` localization mode, suitable for DPM marks.
- Sets `Timeout: 3000` ms at the template level.

---

### 10.3 ReadInvertedBarcode.json

Configures reading of colour-inverted barcodes by using inverted grayscale transformation.

```json
{

  "CaptureVisionTemplates": [
    {
      "Name": "ReadInvertedBarcode",
      "ImageROIProcessingNameArray": [
        "TA_0"
      ]
    }
  ],
  "TargetROIDefOptions": [
    {
      "Name": "TA_0",
      "TaskSettingNameArray": [
        "BR_0"
      ]
    }
  ],
  "BarcodeReaderTaskSettingOptions": [
    {
      "Name": "BR_0",
      "ExpectedBarcodesCount": 1,
      "BarcodeFormatIds": [
        "BF_DEFAULT"
      ],
      "SectionArray": [
        {
          "Section": "ST_REGION_PREDETECTION",
          "ImageParameterName": "IP_0"
        },
        {
          "Section": "ST_BARCODE_LOCALIZATION"
        },
        {
          "Section": "ST_BARCODE_DECODING"
        }
      ]
    }
  ],
  "ImageParameterOptions": [
    {
        "Name": "IP_0",
        "ApplicableStages": [
        {
            "Stage": "SST_TRANSFORM_GRAYSCALE",
            "GrayscaleTransformationModes": [
            {
              "Mode": "GTM_INVERTED"
            }
          ]
        }
      ]
    }
  ]
}
```

**Template Notes:**
- Key setting: `GrayscaleTransformationModes: [{"Mode": "GTM_INVERTED"}]` — inverts the image before processing.
- Links the custom `ImageParameterName: "IP_0"` to the `ST_REGION_PREDETECTION` section.

---

### 10.4 ReadMultipleBarcode.json

Optimized for reading many barcodes from a single image with a short timeout.

```json
{
    "CaptureVisionTemplates": [
        {
            "Name": "ReadMultipleBarcodes",
            "ImageROIProcessingNameArray": [
                "roi_read_multiple_barcodes"
            ],
            "Timeout": 650
        }
    ],
    "TargetROIDefOptions": [
        {
            "Name": "roi_read_multiple_barcodes",
            "TaskSettingNameArray": [
                "task_read_multiple_barcodes"
            ]
        }
    ],
    "BarcodeReaderTaskSettingOptions": [
        {
            "Name": "task_read_multiple_barcodes",
            "ExpectedBarcodesCount": 999,
            "BarcodeFormatIds": [
                "BF_DEFAULT"
            ],
            "SectionArray": [
                {
                    "Section": "ST_REGION_PREDETECTION",
                    "ImageParameterName": "ip_read_multiple_barcodes",
                    "StageArray": [
                        {
                            "Stage": "SST_PREDETECT_REGIONS"
                        }
                    ]
                },
                {
                    "Section": "ST_BARCODE_LOCALIZATION",
                    "ImageParameterName": "ip_read_multiple_barcodes",
                    "StageArray": [
                        {
                            "Stage": "SST_LOCALIZE_CANDIDATE_BARCODES",
                            "LocalizationModes": [
                                {
                                    "Mode": "LM_CONNECTED_BLOCKS"
                                },
                                {
                                    "Mode": "LM_LINES"
                                }
                            ]
                        },
                        {
                            "Stage": "SST_LOCALIZE_BARCODES"
                        }
                    ]
                },
                {
                    "Section": "ST_BARCODE_DECODING",
                    "ImageParameterName": "ip_read_multiple_barcodes",
                    "StageArray": [
                        {
                            "Stage": "SST_RESIST_DEFORMATION"
                        },
                        {
                            "Stage": "SST_COMPLEMENT_BARCODE"
                        },
                        {
                            "Stage": "SST_SCALE_BARCODE_IMAGE"
                        },
                        {
                            "Stage": "SST_DECODE_BARCODES",
                            "DeblurModes": [
                                {
                                    "Mode": "DM_BASED_ON_LOC_BIN"
                                },
                                {
                                    "Mode": "DM_THRESHOLD_BINARIZATION"
                                },
                                {
                                    "Mode": "DM_DIRECT_BINARIZATION"
                                }
                            ]
                        }
                    ]
                }
            ]
        }
    ],
    "ImageParameterOptions": [
        {
            "Name": "ip_read_multiple_barcodes",
            "ApplicableStages": [
                {
                    "Stage": "SST_SCALE_IMAGE",
                    "ImageScaleSetting": {
                        "ScaleType": "ST_SCALE_DOWN",
                        "ReferenceEdge": "RE_SHORTER_EDGE",
                        "EdgeLengthThreshold": 100000
                    }
                }
            ]
        }
    ]
}
```

**Template Notes:**
- Sets `ExpectedBarcodesCount: 999` to find as many barcodes as possible.
- Short `Timeout: 650` ms for fast processing.
- Uses `LM_CONNECTED_BLOCKS` and `LM_LINES` localization modes for multiple barcode detection.

---

## Quick Reference: API Patterns Summary

### Two main capture methods

| Method | Returns | Use Case |
|--------|---------|----------|
| `cvr.capture(image, template)` | `CapturedResult` | Single image/page processing |
| `cvr.capture_multi_pages(path, template)` | `CapturedResultArray` | File-based processing (handles multi-page PDF/TIFF) |

### Result extraction

| Result Type | How to Get | Item Class |
|-------------|-----------|------------|
| Barcodes | `result.get_decoded_barcodes_result()` | `BarcodeResultItem` -> `get_format_string()`, `get_text()` |
| All items | `result.get_items()` | Check with `isinstance()` |

### Preset template names (EnumPresetTemplate)

| Enum | Use |
|------|-----|
| `PT_READ_BARCODES` | General barcode reading |
| `PT_READ_BARCODES_SPEED_FIRST` | Fast barcode reading (sacrifices accuracy) |
| `PT_READ_BARCODES_READ_RATE_FIRST` | Max accuracy barcode reading |
| `PT_READ_SINGLE_BARCODE` | Optimized for exactly one barcode |

### Loading custom templates

```python
errorCode, errorMsg = cvr_instance.init_settings_from_file(json_file_path)
# Then use the template Name from the JSON:
result = cvr_instance.capture(image, "TemplateName")
# Or empty string for default:
result = cvr_instance.capture_multi_pages(image, "")
```

### Video/streaming pattern

```python
# 1. Subclass ImageSourceAdapter
class MyFetcher(ImageSourceAdapter):
    def has_next_image_to_fetch(self): return True

# 2. Set input source
cvr.set_input(fetcher)

# 3. Add result receiver (CapturedResultReceiver subclass)
cvr.add_result_receiver(receiver)

# 4. Optionally add cross filter
filter = MultiFrameResultCrossFilter()
filter.enable_result_cross_verification(CRIT_BARCODE, True)
filter.enable_result_deduplication(CRIT_BARCODE, True)
cvr.add_result_filter(filter)

# 5. Start non-blocking capture
cvr.start_capturing(template, False)

# 6. Feed frames in loop
image = ImageData(bytes, w, h, stride, pixel_format, orientation, tag)
fetcher.add_image_to_buffer(image)

# 7. Stop when done
cvr.stop_capturing(False, True)
```

### Image I/O

```python
image_io = ImageIO()
err, image_data = image_io.read_from_file(path)       # Read
err, msg = image_io.save_to_file(image_data, path)    # Write
```

### Settings modification

```python
err, msg, settings = cvr.get_simplified_settings(template)
settings.barcode_settings.barcode_format_ids = EnumBarcodeFormat.BF_QR_CODE
settings.barcode_settings.expected_barcodes_count = 10
settings.output_original_image = 1
err, msg = cvr.update_settings(template, settings)
```
