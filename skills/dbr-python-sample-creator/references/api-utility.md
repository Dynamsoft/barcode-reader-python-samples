# API Reference: utility module

Module: `dynamsoft_barcode_reader_bundle` (utility submodule)

This document reflects the API surface exposed by `C:\Users\Francis\Desktop\py\utility.py`.

## Enums

### EnumLayoutPattern (IntEnum)
| Member | Description |
|--------|-------------|
| `LP_UNKNOWN` | Auto-detect layout pattern |
| `LP_LINES` | Line-based layout |
| `LP_MATRIX` | Matrix/grid layout |

### EnumLayoutElementSource (IntEnum)
| Member | Description |
|--------|-------------|
| `LES_NONE` | Padding/empty element |
| `LES_INPUT` | Element comes from input quad |
| `LES_INFERRED` | Element inferred by analyzer |

### FilterType (IntEnum)
| Member | Description |
|--------|-------------|
| `FT_HIGH_PASS` | High-pass filter |
| `FT_SHARPEN` | Sharpen filter |
| `FT_SMOOTH` | Smooth filter |

## Layout Analysis

### LayoutAxis

Axis configuration used by `LayoutAnalysisParameter.axes`.

| Attribute | Type | Description |
|-----------|------|-------------|
| `element_count` | `int` | Expected element count on this axis (`-1` auto) |
| `is_staggered` | `bool` | Whether layout is staggered |
| `angle` | `int` | Target axis angle in [0, 180], `-1` auto |
| `is_equal_spacing` | `bool` | Whether equal spacing is enforced |
| `spacing` | `int` | Spacing value (`-1` auto) |
| `spacing_unit` | `EnumMeasureUnit` | `MU_PIXEL` or `MU_PERCENTAGE` |

### LayoutAnalysisParameter

Input parameters for layout analysis.

| Attribute | Type | Description |
|-----------|------|-------------|
| `pattern` | `EnumLayoutPattern` | Desired pattern (`LP_UNKNOWN` for auto) |
| `axes` | `List[LayoutAxis]` | Primary(0) / secondary(1) axis configs |
| `input_image_width` | `int` | Source image width for boundary checks |
| `input_image_height` | `int` | Source image height for boundary checks |

### LayoutElement

Single element in analyzed layout.

| Attribute | Type | Description |
|-----------|------|-------------|
| `quad` | `Quadrilateral` | Element geometry |
| `source` | `EnumLayoutElementSource` | Input / inferred / none |

### LayoutAnalysisResult

Result returned by `LayoutAnalyzer.analyze()`.

| Attribute | Type | Description |
|-----------|------|-------------|
| `inferred_quads` | `List[Quadrilateral]` | Newly inferred quadrilaterals |
| `elements` | `List[List[LayoutElement]]` | 2D layout grid |
| `row_count` | `int` | Number of rows |
| `col_count` | `int` | Max columns across rows |
| `detected_pattern` | `EnumLayoutPattern` | Pattern actually detected |
| `error_code` | `int` | `0` success, non-zero on failure |

### LayoutAnalyzer

Static utility for layout inference.

| Method | Signature | Returns |
|--------|-----------|---------|
| `analyze` | `(inputQuads: List[Quadrilateral], param: LayoutAnalysisParameter = None) -> LayoutAnalysisResult` | Layout analysis result or `None` |

## Streaming / Batch Helpers

### MultiFrameResultCrossFilter (extends CapturedResultFilter)

Filters and stabilizes continuous-capture results.

| Method | Signature | Returns |
|--------|-----------|---------|
| `__init__` | `(cvr: CaptureVisionRouter = None)` | instance |
| `enable_result_cross_verification` | `(result_item_types: int, enabled: bool) -> None` | - |
| `is_result_cross_verification_enabled` | `(type: int) -> bool` | enabled flag |
| `enable_result_deduplication` | `(result_item_types: int, enabled: bool) -> None` | - |
| `is_result_deduplication_enabled` | `(type: int) -> bool` | enabled flag |
| `set_duplicate_forget_time` | `(result_item_types: int, time: int) -> None` | - |
| `get_duplicate_forget_time` | `(type: int) -> int` | forget time (ms) |
| `set_max_overlapping_frames` | `(result_item_types: int, max_overlapping_frames: int) -> None` | - |
| `get_max_overlapping_frames` | `(type: int) -> int` | frame count |
| `enable_latest_overlapping` | `(result_item_types: int, enabled: bool) -> None` | - |
| `is_latest_overlapping_enabled` | `(type: int) -> bool` | enabled flag |
| `set_result_cross_verification_criteria` | `(result_item_types: int, frame_window: int, min_consistent_frames: int) -> None` | - |
| `get_result_cross_verification_criteria` | `(result_item_type: EnumCapturedResultItemType) -> Tuple[int, int]` | `(frame_window, min_consistent_frames)` |

### ProactiveImageSourceAdapter (extends ImageSourceAdapter, ABC)

| Method | Signature | Returns |
|--------|-----------|---------|
| `_fetch_image` | `()` (abstract) | supply image in subclass |
| `set_image_fetch_interval` | `(milliseconds: int) -> None` | - |
| `get_image_fetch_interval` | `() -> int` | interval (ms) |
| `has_next_image_to_fetch` | `() -> bool` | whether more images exist |
| `start_fetching` | `() -> None` | start background fetch |
| `stop_fetching` | `() -> None` | stop background fetch |

### DirectoryFetcher (extends ProactiveImageSourceAdapter)

| Method | Signature | Returns |
|--------|-----------|---------|
| `set_directory` | `(path: str, filter?: str, recursive?: bool) -> Tuple[int, str]` | error code/message |
| `set_pdf_reading_parameter` | `(para: PDFReadingParameter) -> Tuple[int, str]` | error code/message |
| `set_pages` | `(pages: List[int]) -> Tuple[int, str]` | error code/message |
| `has_next_image_to_fetch` | `() -> bool` | whether more images remain |

### FileFetcher (extends ImageSourceAdapter)

| Method | Signature | Returns |
|--------|-----------|---------|
| `set_file` | `(path: str | bytes | ImageData) -> Tuple[int, str]` | error code/message |
| `set_pdf_reading_parameter` | `(para: PDFReadingParameter) -> Tuple[int, str]` | error code/message |
| `set_pages` | `(pages: List[int]) -> Tuple[int, str]` | error code/message |
| `has_next_image_to_fetch` | `() -> bool` | whether more images remain |
| `get_image` | `() -> ImageData` | next image |

## Image I/O and Drawing

### ImageIO

| Method | Signature | Returns |
|--------|-----------|---------|
| `save_to_file` | `(image_data: ImageData, path: str, overwrite: bool = True) -> Tuple[int, str]` | error code/message |
| `read_from_file` | `(file_path: str) -> Tuple[int, ImageData]` | error code/image |
| `read_from_memory` | `(image_file_bytes: bytes) -> Tuple[int, ImageData]` | error code/image |
| `save_to_memory` | `(image_data: ImageData, image_format: EnumImageFileFormat) -> Tuple[int, bytes]` | error code/bytes |
| `read_from_numpy` | `(image: np.ndarray, image_pixel_format: EnumImagePixelFormat) -> Tuple[int, str, ImageData]` | code/msg/image |
| `save_to_numpy` | `(image_data: ImageData) -> Tuple[int, str, np.ndarray]` | code/msg/array |

### ImageDrawer

| Method | Signature | Returns |
|--------|-----------|---------|
| `draw_on_image` | `(image: ImageData, shapes: List[Quadrilateral|LineSegment|Contour|Corner|Edge], color: int = 0xFFFF0000, thickness: int = 1) -> ImageData` | modified image |

### ImageProcessor

| Method | Signature | Returns |
|--------|-----------|---------|
| `crop_image` | `(image_data: ImageData, crop_form: Rect|Quadrilateral) -> Tuple[int, ImageData]` | error code/image |
| `crop_and_deskew_image` | `(image_data: ImageData, crop_form: Quadrilateral, destination_width: int = 0, destination_height: int = 0, padding: int = 0) -> Tuple[int, ImageData]` | error code/image |
| `adjust_brightness` | `(image_data: ImageData, brightness: int) -> ImageData` | adjusted image |
| `adjust_contrast` | `(image_data: ImageData, contrast: int) -> ImageData` | adjusted image |
| `filter_image` | `(image_data: ImageData, filter_type: FilterType) -> ImageData` | filtered image |
| `convert_to_gray` | `(image_data: ImageData, r: float = 0.3, g: float = 0.59, b: float = 0.11) -> ImageData` | grayscale image |
| `convert_to_binary_global` | `(image_data: ImageData, threshold: int = -1, invert: bool = False) -> ImageData` | binary image |
| `convert_to_binary_local` | `(image_data: ImageData, block_size: int = 0, compensation: int = 10, invert: bool = False) -> ImageData` | binary image |

## Utility Module Info

### UtilityModule

| Method | Signature | Returns |
|--------|-----------|---------|
| `get_version` (static) | `() -> str` | module version string |
