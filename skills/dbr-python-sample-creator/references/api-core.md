# Core Module API Reference

Module: `dynamsoft_barcode_reader_bundle` (core submodule)

---

## Enums

### EnumErrorCode (IntEnum)
Common error codes returned by SDK operations.

| Member | Description |
|--------|-------------|
| `EC_OK` | Success |
| `EC_UNKNOWN` | Unknown error |
| `EC_NO_MEMORY` | Out of memory |
| `EC_NULL_POINTER` | Null pointer |
| `EC_LICENSE_INVALID` | Invalid license |
| `EC_LICENSE_EXPIRED` | License expired |
| `EC_FILE_NOT_FOUND` | File not found |
| `EC_FILE_TYPE_NOT_SUPPORTED` | File type not supported |
| `EC_BPP_NOT_SUPPORTED` | BPP not supported |
| `EC_INDEX_INVALID` | Invalid index |
| `EC_CUSTOM_REGION_INVALID` | Invalid custom region |
| `EC_IMAGE_READ_FAILED` | Image read failed |
| `EC_TIFF_READ_FAILED` | TIFF read failed |
| `EC_PDF_READ_FAILED` | PDF read failed |
| `EC_PDF_DLL_MISSING` | PDF DLL missing |
| `EC_TIMEOUT` | Operation timeout |
| `EC_JSON_PARSE_FAILED` | JSON parse failed |
| `EC_JSON_TYPE_INVALID` | Invalid JSON type |
| `EC_JSON_KEY_INVALID` | Invalid JSON key |
| `EC_JSON_VALUE_INVALID` | Invalid JSON value |
| `EC_JSON_NAME_KEY_MISSING` | JSON name key missing |
| `EC_JSON_NAME_VALUE_DUPLICATED` | Duplicated JSON name value |
| `EC_TEMPLATE_NAME_INVALID` | Invalid template name |
| `EC_PARAMETER_VALUE_INVALID` | Invalid parameter value |
| `EC_LICENSE_KEY_INVALID` | Invalid license key |
| `EC_LICENSE_DEVICE_RUNS_OUT` | License device limit reached |
| `EC_NO_IMAGE_SOURCE` | No image source set |
| `EC_MODULE_NOT_FOUND` | Module not found |
| `EC_IMAGE_DATA_INVALID` | Invalid image data |
| `EC_NO_LICENSE` | No license found |
| `EC_TRIAL_LICENSE` | Trial license |
| `EC_BARCODE_READER_LICENSE_NOT_FOUND` | Barcode reader license missing |
| `EC_LABEL_RECOGNIZER_LICENSE_NOT_FOUND` | Label recognizer license missing |
| `EC_DOCUMENT_NORMALIZER_LICENSE_NOT_FOUND` | Document normalizer license missing |
| `EC_CODE_PARSER_LICENSE_NOT_FOUND` | Code parser license missing |

*(Additional members exist for specific barcode formats, model files, resource paths, etc.)*

### EnumImagePixelFormat (IntEnum)

| Member | Description |
|--------|-------------|
| `IPF_BINARY` | 1-bit binary |
| `IPF_BINARYINVERTED` | 1-bit binary inverted |
| `IPF_GRAYSCALED` | 8-bit grayscale |
| `IPF_NV21` | NV21 (YUV) |
| `IPF_RGB_565` | 16-bit RGB 565 |
| `IPF_RGB_555` | 16-bit RGB 555 |
| `IPF_RGB_888` | 24-bit RGB |
| `IPF_ARGB_8888` | 32-bit ARGB |
| `IPF_RGB_161616` | 48-bit RGB |
| `IPF_ARGB_16161616` | 64-bit ARGB |
| `IPF_ABGR_8888` | 32-bit ABGR |
| `IPF_ABGR_16161616` | 64-bit ABGR |
| `IPF_BGR_888` | 24-bit BGR |
| `IPF_BINARY_8` | 8-bit binary |
| `IPF_NV12` | NV12 (YUV) |
| `IPF_BINARY_8_INVERTED` | 8-bit binary inverted |

### EnumGrayscaleTransformationMode (IntEnum)
`GTM_INVERTED`, `GTM_ORIGINAL`, `GTM_AUTO`, `GTM_REV`, `GTM_END`, `GTM_SKIP`

### EnumGrayscaleEnhancementMode (IntEnum)
`GEM_AUTO`, `GEM_GENERAL`, `GEM_GRAY_EQUALIZE`, `GEM_GRAY_SMOOTH`, `GEM_SHARPEN_SMOOTH`, `GEM_REV`, `GEM_END`, `GEM_SKIP`

### EnumPDFReadingMode (IntEnum)
`PDFRM_VECTOR`, `PDFRM_RASTER`, `PDFRM_REV`

### EnumRasterDataSource (IntEnum)
`RDS_RASTERIZED_PAGES`, `RDS_EXTRACTED_IMAGES`

### EnumCapturedResultItemType (IntEnum)

| Member | Description |
|--------|-------------|
| `CRIT_ORIGINAL_IMAGE` | Original image |
| `CRIT_BARCODE` | Barcode result |

### EnumBufferOverflowProtectionMode (IntEnum)
`BOPM_BLOCK`, `BOPM_UPDATE`

### EnumImageTagType (IntEnum)
`ITT_FILE_IMAGE`, `ITT_VIDEO_FRAME`

### EnumVideoFrameQuality (IntEnum)
`VFQ_HIGH`, `VFQ_LOW`, `VFQ_UNKNOWN`

### EnumImageCaptureDistanceMode (IntEnum)
`ICDM_NEAR`, `ICDM_FAR`

### EnumColourChannelUsageType (IntEnum)
`CCUT_AUTO`, `CCUT_FULL_CHANNEL`, `CCUT_Y_CHANNEL_ONLY`, `CCUT_RGB_R_CHANNEL_ONLY`, `CCUT_RGB_G_CHANNEL_ONLY`, `CCUT_RGB_B_CHANNEL_ONLY`

### EnumCornerType (IntEnum)
`CT_NORMAL_INTERSECTED`, `CT_T_INTERSECTED`, `CT_CROSS_INTERSECTED`, `CT_NOT_INTERSECTED`

### EnumSectionType (IntEnum)
`ST_NULL`, `ST_REGION_PREDETECTION`, `ST_BARCODE_LOCALIZATION`, `ST_BARCODE_DECODING`

### EnumIntermediateResultUnitType (IntEnum)
`IRUT_NULL`, `IRUT_COLOUR_IMAGE`, `IRUT_SCALED_COLOUR_IMAGE`, `IRUT_GRAYSCALE_IMAGE`, `IRUT_TRANSFORMED_GRAYSCALE_IMAGE`, `IRUT_ENHANCED_GRAYSCALE_IMAGE`, `IRUT_PREDETECTED_REGIONS`, `IRUT_BINARY_IMAGE`, `IRUT_TEXTURE_DETECTION_RESULT`, `IRUT_TEXTURE_REMOVED_GRAYSCALE_IMAGE`, `IRUT_TEXTURE_REMOVED_BINARY_IMAGE`, `IRUT_CONTOURS`, `IRUT_LINE_SEGMENTS`, `IRUT_TEXT_ZONES`, `IRUT_TEXT_REMOVED_BINARY_IMAGE`, `IRUT_CANDIDATE_BARCODE_ZONES`, `IRUT_LOCALIZED_BARCODES`, `IRUT_SCALED_BARCODE_IMAGE`, `IRUT_DEFORMATION_RESISTED_BARCODE_IMAGE`, `IRUT_COMPLEMENTED_BARCODE_IMAGE`, `IRUT_DECODED_BARCODES`, `IRUT_ALL`

### EnumRegionObjectElementType (IntEnum)
`ROET_PREDETECTED_REGION`, `ROET_LOCALIZED_BARCODE`, `ROET_DECODED_BARCODE`, `ROET_SOURCE_IMAGE`, `ROET_TARGET_ROI`, `ROET_AUXILIARY_REGION`

### EnumTransformMatrixType (IntEnum)
`TMT_LOCAL_TO_ORIGINAL_IMAGE`, `TMT_ORIGINAL_TO_LOCAL_IMAGE`, `TMT_ROTATED_TO_ORIGINAL_IMAGE`, `TMT_ORIGINAL_TO_ROTATED_IMAGE`, `TMT_LOCAL_TO_SECTION_IMAGE`, `TMT_SECTION_TO_LOCAL_IMAGE`

### EnumCrossVerificationStatus (IntEnum)
`CVS_NOT_VERIFIED`, `CVS_PASSED`, `CVS_FAILED`

### EnumImageFileFormat (IntEnum)
`IFF_JPEG`, `IFF_PNG`, `IFF_BMP`, `IFF_PDF`

---

## Constants

- `IDENTITY_MATRIX` — Default identity transformation matrix

---

## Geometry Classes

### Point
2D point with integer coordinates.
```
Point(x: int = 0, y: int = 0)
```
- **Attributes**: `x: int`, `y: int`
- `distance_to(pt: Point) -> float`
- `Point.transform_coordinates(original_point: Point, transformation_matrix: List[float]) -> Point` (static)

### Rect
Axis-aligned rectangle.
```
Rect()
```
- **Attributes**: `top: int`, `left: int`, `right: int`, `bottom: int`, `id: int`

### Quadrilateral
Four-point polygon.
```
Quadrilateral()
```
- **Attributes**: `points: List[Point]` (length 4), `id: int`
- `contains(point: Point) -> bool`
- `get_area() -> int`
- `get_bounding_rect() -> Rect`

### LineSegment
Line segment between two points.
```
LineSegment(start_point: Point, end_point: Point, line_id: int = 0)
```
- **Attributes**: `start_point: Point`, `end_point: Point`, `id: int`

### Corner
Intersection of two line segments.
```
Corner()
```
- **Attributes**: `type: int` (EnumCornerType), `intersection: Point`, `line1: LineSegment`, `line2: LineSegment`

### Edge
Two Corner endpoints.
```
Edge()
```
- **Attributes**: `start_corner: Corner`, `end_corner: Corner`

### Contour
Collection of points forming a contour.
```
Contour()
```
- `set_points(points: List[Point]) -> None`
- `get_points() -> List[Point]`

### Vector4
Four-component integer vector (used for contour hierarchies).
```
Vector4(v1: int, v2: int, v3: int, v4: int)
```
- **Attributes**: `value: List[int]`
- `Set(v1, v2, v3, v4) -> None`
- Supports `[]` indexing

### TextZone
Represents a detected text zone region.
```
TextZone(loc: Quadrilateral = ..., char_contours_indices: List[int] = ...)
```
- `get_location() -> Quadrilateral` / `set_location(loc: Quadrilateral) -> None`
- `get_char_contours_indices() -> List[int]` / `set_char_contours_indices(indices: List[int]) -> None`

---

## Image Classes

### ImageData
Container for raw image bytes and metadata.
```
ImageData(bytes: bytes, width: int, height: int, stride: int, format: int, orientation: int = 0, tag: ImageTag = None)
```
- `get_bytes() -> bytes`
- `get_width() -> int`
- `get_height() -> int`
- `get_stride() -> int`
- `get_image_pixel_format() -> EnumImagePixelFormat`
- `get_orientation() -> int`
- `get_image_tag() -> ImageTag` / `set_image_tag(tag: ImageTag) -> None`

### ImageTag (ABC)
Abstract base tag attached to images.
- `get_type() -> int` (abstract)
- `clone() -> ImageTag` (abstract)
- `get_image_id() -> int` / `set_image_id(imgId: int) -> None`
- `get_image_capture_distance_mode() -> int` / `set_image_capture_distance_mode(mode: int) -> None`

### FileImageTag(ImageTag)
Tag for file-sourced images.
```
FileImageTag(file_path: str, page_number: int, total_pages: int)
```
- `get_file_path() -> str`
- `get_page_number() -> int`
- `get_total_pages() -> int`

### VideoFrameTag(ImageTag)
Tag for video frame images.
```
VideoFrameTag(quality: int, is_cropped: bool, crop_region: Rect, original_width: int, original_height: int)
```
- `get_video_frame_quality() -> int`
- `is_cropped() -> bool`
- `get_crop_region() -> Rect`
- `get_original_width() -> int`
- `get_original_height() -> int`

---

## Result Classes

### CapturedResultItem
Base class for all captured result items (barcode, text line, quad, etc.). Not directly instantiated.
- `get_type() -> int` — Returns EnumCapturedResultItemType
- `get_reference_item() -> CapturedResultItem`
- `get_target_roi_def_name() -> str`
- `get_task_name() -> str`

### OriginalImageResultItem(CapturedResultItem)
Contains the original captured image.
- `get_image_data() -> ImageData`

### CapturedResultBase
Base class for aggregate captured results. Not directly instantiated.
- `get_original_image_hash_id() -> str`
- `get_original_image_tag() -> ImageTag`
- `get_rotation_transform_matrix() -> List[float]` — 3x3 matrix as 9-element list
- `get_error_code() -> int`
- `get_error_string() -> str`

---

## Image Source Classes

### ImageSourceErrorListener (ABC)
Override to receive errors from an image source.
- `on_error_received(error_code: int, error_message: str) -> None` (abstract)

### ImageSourceAdapter (ABC)
Abstract adapter for feeding images to the capture pipeline.
- `has_next_image_to_fetch() -> bool` (abstract — must implement)
- `add_image_to_buffer(image: ImageData) -> None`
- `start_fetching() -> None` / `stop_fetching() -> None`
- `get_image() -> ImageData`
- `set_max_image_count(count: int)` / `get_max_image_count() -> int`
- `set_buffer_overflow_protection_mode(mode: int)` / `get_buffer_overflow_protection_mode() -> int`
- `has_image(image_id: int) -> bool`
- `set_next_image_to_return(image_id: int, keep_in_buffer: bool = True) -> bool`
- `get_image_count() -> int`
- `is_buffer_empty() -> bool`
- `clear_buffer() -> None`
- `set_colour_channel_usage_type(type: int)` / `get_colour_channel_usage_type() -> int`
- `set_error_listener(listener: ImageSourceErrorListener) -> None`

---

## PDF Reading

### PDFReadingParameter
Parameters for PDF file reading.
```
PDFReadingParameter()
```
- **Attributes**: `mode: int` (EnumPDFReadingMode, default PDFRM_RASTER), `dpi: int` (default 300), `raster_data_source: int` (EnumRasterDataSource, default RDS_RASTERIZED_PAGES)

---

## Intermediate Result Classes

### IntermediateResultUnit
Base class for all intermediate result units.
- `get_hash_id() -> str`
- `get_original_image_hash_id() -> str`
- `get_original_image_tag() -> ImageTag`
- `get_transform_matrix(matrix_type: EnumTransformMatrixType) -> List[float]`
- `get_type() -> int` — Returns EnumIntermediateResultUnitType
- `clone() -> IntermediateResultUnit`
- `replace(unit: IntermediateResultUnit) -> int`
- `get_usage_count() -> int`

### IntermediateResult
Container for a collection of IntermediateResultUnit objects.
- `get_intermediate_result_units() -> List[IntermediateResultUnit]`

### Image-type Intermediate Units
All inherit from `IntermediateResultUnit` and share the same interface:
- `get_image_data() -> ImageData`
- `set_image_data(img_data: ImageData) -> int`

| Class | IRUT Type |
|-------|-----------|
| `ColourImageUnit` | IRUT_COLOUR_IMAGE |
| `ScaledColourImageUnit` | IRUT_SCALED_COLOUR_IMAGE |
| `GrayscaleImageUnit` | IRUT_GRAYSCALE_IMAGE |
| `TransformedGrayscaleImageUnit` | IRUT_TRANSFORMED_GRAYSCALE_IMAGE |
| `EnhancedGrayscaleImageUnit` | IRUT_ENHANCED_GRAYSCALE_IMAGE |
| `BinaryImageUnit` | IRUT_BINARY_IMAGE |
| `TextureRemovedGrayscaleImageUnit` | IRUT_TEXTURE_REMOVED_GRAYSCALE_IMAGE |
| `TextureRemovedBinaryImageUnit` | IRUT_TEXTURE_REMOVED_BINARY_IMAGE |
| `TextRemovedBinaryImageUnit` | IRUT_TEXT_REMOVED_BINARY_IMAGE |

### TextureDetectionResultUnit(IntermediateResultUnit)
Texture stripe spacing detection result.
- `get_x_spacing() -> int` / `set_x_spacing(x_spacing: int) -> None`
- `get_y_spacing() -> int` / `set_y_spacing(y_spacing: int) -> None`

### Collection-type Intermediate Units
These follow a get_count/get_item/add/set/remove pattern:

**PredetectedRegionsUnit(IntermediateResultUnit)**
- `get_count() -> int`
- `get_predetected_region(index: int) -> PredetectedRegionElement`
- `add_predetected_region(element, matrix_to_original_image=IDENTITY_MATRIX) -> int`
- `set_predetected_region(index, element, matrix_to_original_image=IDENTITY_MATRIX) -> int`
- `remove_predetected_region(index) -> int` / `remove_all_predetected_regions() -> None`

**LineSegmentsUnit(IntermediateResultUnit)**
- `get_count() -> int`
- `get_line_segment(index: int) -> LineSegment`
- `add_line_segment(line, matrix=IDENTITY_MATRIX) -> int`
- `set_line_segment(index, line, matrix=IDENTITY_MATRIX) -> int`
- `remove_line_segment(index) -> int` / `remove_all_line_segments() -> None`

**ShortLinesUnit(IntermediateResultUnit)** — Same pattern as LineSegmentsUnit but with `short_line` methods.

**TextZonesUnit(IntermediateResultUnit)**
- `get_count() -> int`
- `get_text_zone(index: int) -> Tuple[int, TextZone]` — Returns (error_code, text_zone)
- `add_text_zone(text_zone, matrix=IDENTITY_MATRIX) -> int`
- `set_text_zone(index, text_zone, matrix=IDENTITY_MATRIX) -> int`
- `remove_text_zone(index) -> int` / `remove_all_text_zones() -> None`

**ContoursUnit(IntermediateResultUnit)**
- `get_contours() -> Tuple[int, List[Contour], List[Vector4]]` — Returns (error_code, contours, hierarchies)
- `set_contours(contours, hierarchies, matrix=IDENTITY_MATRIX) -> int`

---

## Region Object Elements

### RegionObjectElement
Base class for region elements in intermediate results.
- `get_location() -> Quadrilateral`
- `get_referenced_element() -> RegionObjectElement`
- `get_element_type() -> int` — Returns EnumRegionObjectElementType
- `clone() -> RegionObjectElement`
- `get_image_data() -> ImageData`

### PredetectedRegionElement(RegionObjectElement)
A pre-detected region in an image.
- `get_mode_name() -> str`
- `set_location(loc: Quadrilateral) -> int`
- `get_label_id() -> int`
- `get_label_name() -> str`

### AuxiliaryRegionElement(RegionObjectElement)
Auxiliary region (e.g., portrait zone, signature area).
- `get_name() -> str` / `set_name(name: str) -> None`
- `get_confidence() -> int` / `set_confidence(confidence: int) -> None`
- `set_location(location: Quadrilateral) -> int`

---

## Observation/Filtering

### ObservationParameters
Filter conditions for IntermediateResultReceiver callbacks.
```
ObservationParameters()
```
- `set_observed_result_unit_types(types: int)` / `get_observed_result_unit_types() -> int`
- `is_result_unit_type_observed(type: int) -> bool`
- `add_observed_task(task_name: str)` / `remove_observed_task(task_name: str)`
- `is_task_observed(task_name: str) -> bool`
- `set_result_unit_types_only_for_input(types: int)` / `get_result_unit_types_only_for_input() -> int`
- `is_result_unit_type_only_for_input(type: int) -> bool`

### IntermediateResultExtraInfo
Extra metadata for intermediate results.
- **Attributes**: `target_roi_def_name: str`, `task_name: str`, `is_section_level_result: bool`, `section_type: int`

---

## Utility Classes

### CoreModule
- `CoreModule.get_version() -> str` (static) — Returns core module version string
