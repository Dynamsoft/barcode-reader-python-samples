# API Reference: dynamsoft_utility

Module: `dynamsoft_utility`

## Enums

### FilterType (IntEnum)
| Member | Description |
|--------|-------------|
| `FT_HIGH_PASS` | High-pass filter |
| `FT_SHARPEN` | Sharpen filter |
| `FT_SMOOTH` | Smooth filter |

## Classes

### DirectoryFetcher (extends ProactiveImageSourceAdapter)

Retrieves image files from a directory for batch processing. Use with `CaptureVisionRouter.set_input()`.

| Method | Signature | Returns |
|--------|-----------|---------|
| `set_directory` | `(path: str, filter?: str, recursive?: bool) -> Tuple[int, str]` | (error_code, error_message). Default filter: `"*.bmp;*.jpg;*.jpeg;*.tif;*.png;*.tiff;*.gif;*.pdf"`. Default recursive: `False` |
| `set_pdf_reading_parameter` | `(para: PDFReadingParameter) -> Tuple[int, str]` | (error_code, error_message) |
| `set_pages` | `(pages: List[int]) -> Tuple[int, str]` | (error_code, error_message). 0-based page indexes for .tiff/.pdf |
| `has_next_image_to_fetch` | `() -> bool` | Whether more images remain |

### FileFetcher (extends ImageSourceAdapter)

Partitions a multi-page image file into individual ImageData objects. Use with `CaptureVisionRouter.set_input()`.

| Method | Signature | Returns |
|--------|-----------|---------|
| `set_file` | `(path: str) -> Tuple[int, str]` | (error_code, error_message). Also accepts `bytes` or `ImageData` |
| `set_pdf_reading_parameter` | `(para: PDFReadingParameter) -> Tuple[int, str]` | (error_code, error_message) |
| `set_pages` | `(pages: List[int]) -> Tuple[int, str]` | (error_code, error_message). 0-based page indexes |
| `has_next_image_to_fetch` | `() -> bool` | Whether more images remain |
| `get_image` | `() -> ImageData` | Next image |

### MultiFrameResultCrossFilter (extends CapturedResultFilter)

Filters video streaming results for deduplication and cross-verification. Use with `CaptureVisionRouter.add_result_filter()`.

| Method | Signature | Returns |
|--------|-----------|---------|
| `__init__` | `(cvr?: CaptureVisionRouter)` | |
| `enable_result_cross_verification` | `(result_item_types: int, enabled: bool) -> None` | Enables multi-frame verification for accuracy |
| `is_result_cross_verification_enabled` | `(type: int) -> bool` | Check if verification enabled |
| `enable_result_deduplication` | `(result_item_types: int, enabled: bool) -> None` | Filters duplicate results within forget time |
| `is_result_deduplication_enabled` | `(type: int) -> bool` | Check if deduplication enabled |
| `set_duplicate_forget_time` | `(result_item_types: int, time: int) -> None` | Dedup window in ms. Default 3000. Range [1, 180000] |
| `get_duplicate_forget_time` | `(type: int) -> int` | Current forget time in ms |
| `enable_latest_overlapping` | `(result_item_types: int, enabled: bool) -> None` | Combines recent frames for better results |
| `is_latest_overlapping_enabled` | `(type: int) -> bool` | Check if overlapping enabled |
| `set_max_overlapping_frames` | `(result_item_types: int, max_overlapping_frames: int) -> None` | Max frames for overlapping |
| `get_max_overlapping_frames` | `(type: int) -> int` | Current max overlapping frames |
| `set_result_cross_verification_criteria` | `(result_item_types: int, frame_window: int, min_consistent_frames: int) -> None` | Custom verification params |
| `get_result_cross_verification_criteria` | `(result_item_type: EnumCapturedResultItemType) -> Tuple[int, int]` | (frame_window, min_consistent_frames) |

**Note:** `result_item_types` is a bitwise OR of `EnumCapturedResultItemType` values (e.g., `CRIT_BARCODE`).

### ProactiveImageSourceAdapter (extends ImageSourceAdapter, ABC)

Abstract base for image sources that proactively fetch images in a background thread.

| Method | Signature | Returns |
|--------|-----------|---------|
| `_fetch_image` | `()` (abstract) | Override to supply images |
| `set_image_fetch_interval` | `(milliseconds: int) -> None` | Wait between fetches. -1 = no proactive fetch |
| `get_image_fetch_interval` | `() -> int` | Current interval in ms |
| `has_next_image_to_fetch` | `() -> bool` | Whether more images exist |
| `start_fetching` | `() -> None` | Start background fetch thread |
| `stop_fetching` | `() -> None` | Stop background fetch thread |

### ImageIO

Read/write images to/from files, memory, and numpy arrays.

| Method | Signature | Returns |
|--------|-----------|---------|
| `save_to_file` | `(image_data: ImageData, path: str, overwrite?: bool) -> Tuple[int, str]` | (error_code, error_message). Default overwrite=True |
| `read_from_file` | `(file_path: str) -> Tuple[int, ImageData]` | (error_code, image_data). Reads first page for gif/pdf/tiff |
| `read_from_memory` | `(image_file_bytes: bytes) -> Tuple[int, ImageData]` | (error_code, image_data) |
| `save_to_memory` | `(image_data: ImageData, image_format: EnumImageFileFormat) -> Tuple[int, bytes]` | (error_code, image_bytes) |
| `read_from_numpy` | `(image: np.ndarray, image_pixel_format: EnumImagePixelFormat) -> Tuple[int, str, ImageData]` | (error_code, error_message, image_data) |
| `save_to_numpy` | `(image_data: ImageData) -> Tuple[int, str, np.ndarray]` | (error_code, error_message, ndarray) |

### ImageDrawer

Draw shapes on images.

| Method | Signature | Returns |
|--------|-----------|---------|
| `draw_on_image` | `(image: ImageData, shapes: List[Quadrilateral\|LineSegment\|Contour\|Corner\|Edge], color?: int, thickness?: int) -> ImageData` | Modified image. Default color=0xFFFF0000 (red), thickness=1 |

### ImageProcessor

Crop, deskew, and adjust images.

| Method | Signature | Returns |
|--------|-----------|---------|
| `crop_image` | `(image_data: ImageData, crop_form: Rect\|Quadrilateral) -> Tuple[int, ImageData]` | (error_code, cropped_image) |
| `crop_and_deskew_image` | `(image_data: ImageData, crop_form: Quadrilateral, destination_width?: int, destination_height?: int, padding?: int) -> Tuple[int, ImageData]` | (error_code, result_image). 0 = auto-calc size |
| `adjust_brightness` | `(image_data: ImageData, brightness: int) -> ImageData` | Adjusted image |
| `adjust_contrast` | `(image_data: ImageData, contrast: int) -> ImageData` | Adjusted image |
| `filter_image` | `(image_data: ImageData, filter_type: FilterType) -> ImageData` | Filtered image |
| `convert_to_gray` | `(image_data: ImageData, r?: float, g?: float, b?: float) -> ImageData` | Grayscale image. Defaults: r=0.3, g=0.59, b=0.11 |
| `convert_to_binary_global` | `(image_data: ImageData, threshold?: int, invert?: bool) -> ImageData` | Binary image. threshold=-1 = auto |
| `convert_to_binary_local` | `(image_data: ImageData, block_size?: int, compensation?: int, invert?: bool) -> ImageData` | Binary image (adaptive). Defaults: block_size=0, compensation=10 |

### UtilityModule

| Method | Signature | Returns |
|--------|-----------|---------|
| `get_version` (static) | `() -> str` | Module version string |
