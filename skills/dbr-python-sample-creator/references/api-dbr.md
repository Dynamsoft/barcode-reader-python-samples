# Dynamsoft Barcode Reader (DBR) — Python API Reference

Module: `dynamsoft_barcode_reader_bundle` or `dynamsoft_capture_vision_bundle` (submodule `dbr`)

---

## Enums

### EnumBarcodeFormat (IntEnum)

Combinable bit-flag values. Use `|` to combine.

| Member | Category |
|---|---|
| `BF_NULL` | None |
| `BF_ALL` | All formats |
| `BF_DEFAULT` | Default set |
| **1D — General** | |
| `BF_ONED` | All 1D codes |
| `BF_CODE_39` | Code 39 |
| `BF_CODE_39_EXTENDED` | Code 39 Extended |
| `BF_CODE_128` | Code 128 |
| `BF_CODE_93` | Code 93 |
| `BF_CODE_32` | Code 32 |
| `BF_CODE_11` | Code 11 |
| `BF_CODABAR` | Codabar |
| `BF_ITF` | Interleaved 2 of 5 |
| `BF_EAN_13` | EAN-13 |
| `BF_EAN_8` | EAN-8 |
| `BF_UPC_A` | UPC-A |
| `BF_UPC_E` | UPC-E |
| `BF_INDUSTRIAL_25` | Industrial 2 of 5 |
| `BF_MSI_CODE` | MSI Code |
| `BF_MATRIX_25` | Matrix 2 of 5 |
| `BF_TELEPEN` | Telepen |
| `BF_TELEPEN_NUMERIC` | Telepen Numeric |
| `BF_TWO_DIGIT_ADD_ON` | 2-digit add-on |
| `BF_FIVE_DIGIT_ADD_ON` | 5-digit add-on |
| `BF_PATCHCODE` | Patch Code |
| **1D — GS1 DataBar** | |
| `BF_GS1_DATABAR` | All GS1 DataBar |
| `BF_GS1_DATABAR_OMNIDIRECTIONAL` | Omnidirectional |
| `BF_GS1_DATABAR_TRUNCATED` | Truncated |
| `BF_GS1_DATABAR_STACKED` | Stacked |
| `BF_GS1_DATABAR_STACKED_OMNIDIRECTIONAL` | Stacked Omnidirectional |
| `BF_GS1_DATABAR_EXPANDED` | Expanded |
| `BF_GS1_DATABAR_EXPANDED_STACKED` | Expanded Stacked |
| `BF_GS1_DATABAR_LIMITED` | Limited |
| **1D — Pharmacode** | |
| `BF_PHARMACODE` | All Pharmacode |
| `BF_PHARMACODE_ONE_TRACK` | One Track |
| `BF_PHARMACODE_TWO_TRACK` | Two Track |
| **2D** | |
| `BF_PDF417` | PDF417 |
| `BF_MICRO_PDF417` | Micro PDF417 |
| `BF_QR_CODE` | QR Code |
| `BF_MICRO_QR` | Micro QR |
| `BF_DATAMATRIX` | DataMatrix |
| `BF_AZTEC` | Aztec |
| `BF_MAXICODE` | MaxiCode |
| `BF_DOTCODE` | DotCode |
| `BF_GS1_COMPOSITE` | GS1 Composite |
| **Postal** | |
| `BF_POSTALCODE` | All postal codes |
| `BF_USPSINTELLIGENTMAIL` | USPS Intelligent Mail |
| `BF_POSTNET` | POSTNET |
| `BF_PLANET` | PLANET |
| `BF_AUSTRALIANPOST` | Australian Post |
| `BF_RM4SCC` | Royal Mail 4-State (RM4SCC) |
| `BF_KIX` | KIX |
| **Other** | |
| `BF_NONSTANDARD_BARCODE` | Non-standard |

### EnumLocalizationMode (IntEnum)

| Member | Description |
|---|---|
| `LM_AUTO` | Auto |
| `LM_CONNECTED_BLOCKS` | Connected blocks |
| `LM_STATISTICS` | Statistics |
| `LM_LINES` | Lines |
| `LM_SCAN_DIRECTLY` | Scan directly |
| `LM_STATISTICS_MARKS` | Statistics marks |
| `LM_STATISTICS_POSTAL_CODE` | Statistics postal code |
| `LM_CENTRE` | Centre |
| `LM_ONED_FAST_SCAN` | 1D fast scan |
| `LM_NEURAL_NETWORK` | Neural network |
| `LM_REV` | Reserved |
| `LM_END` | End marker |
| `LM_SKIP` | Skip |

### EnumDeblurMode (IntEnum)

| Member |
|---|
| `DM_DIRECT_BINARIZATION`, `DM_THRESHOLD_BINARIZATION`, `DM_GRAY_EQUALIZATION`, `DM_SMOOTHING`, `DM_MORPHING`, `DM_DEEP_ANALYSIS`, `DM_SHARPENING`, `DM_BASED_ON_LOC_BIN`, `DM_SHARPENING_SMOOTHING`, `DM_NEURAL_NETWORK`, `DM_REV`, `DM_END`, `DM_SKIP` |

### EnumQRCodeErrorCorrectionLevel (IntEnum)

`QRECL_ERROR_CORRECTION_H`, `QRECL_ERROR_CORRECTION_L`, `QRECL_ERROR_CORRECTION_M`, `QRECL_ERROR_CORRECTION_Q`

### EnumExtendedBarcodeResultType (IntEnum)

`EBRT_STANDARD_RESULT`, `EBRT_CANDIDATE_RESULT`, `EBRT_PARTIAL_RESULT`

---

## Core Result Classes

### DecodedBarcodesResult (CapturedResultBase)

Top-level result from barcode reading. Returned by `CaptureVisionRouter.capture(...)`.

| Method | Returns | Description |
|---|---|---|
| `get_error_code()` | `int` | Error code (0 = success) |
| `get_error_string()` | `str` | Error message |
| `get_items()` | `List[BarcodeResultItem]` | All decoded barcode items |
| `get_original_image_hash_id()` | `str` | Hash ID of source image |
| `get_original_image_tag()` | `ImageTag` | Tag of source image |
| `get_rotation_transform_matrix()` | `List[float]` | 3x3 rotation matrix |

### BarcodeResultItem (CapturedResultItem)

Individual barcode result. Obtained from `DecodedBarcodesResult.get_items()`.

| Method | Returns | Description |
|---|---|---|
| `get_format()` | `int` | Format as `EnumBarcodeFormat` value |
| `get_format_string()` | `str` | Format as human-readable string |
| `get_text()` | `str` | Decoded text content |
| `get_bytes()` | `bytes` | Raw decoded bytes |
| `get_location()` | `Quadrilateral` | Bounding quadrilateral |
| `get_confidence()` | `int` | Result confidence (0-100) |
| `get_angle()` | `int` | Rotation angle |
| `get_module_size()` | `int` | Module size in pixels |
| `get_details()` | `BarcodeDetails` | Format-specific details |
| `is_dpm()` | `bool` | Is Direct Part Marking |
| `is_mirrored()` | `bool` | Is mirrored barcode |
| `get_eci_segments()` | `List[ECISegment]` | ECI segments in barcode |

---

## Settings

### SimplifiedBarcodeReaderSettings

Sub-parameter of `SimplifiedCaptureVisionSettings`. Get/set via `CaptureVisionRouter`.

| Attribute | Type | Description |
|---|---|---|
| `barcode_format_ids` | `int` | Target barcode formats (combine `EnumBarcodeFormat` with `\|`) |
| `expected_barcodes_count` | `int` | Expected count (0 = auto, default: 0) |
| `grayscale_transformation_modes` | `List[int]` | List of 8 `EnumGrayscaleTransformationMode` values |
| `grayscale_enhancement_modes` | `List[int]` | List of 8 `EnumGrayscaleEnhancementMode` values |
| `localization_modes` | `List[int]` | List of 8 `EnumLocalizationMode` values |
| `deblur_modes` | `List[int]` | List of 8 `EnumDeblurMode` values |
| `min_result_confidence` | `int` | Min confidence threshold (default: 30) |
| `min_barcode_text_length` | `int` | Min text length filter |
| `barcode_text_regex_pattern` | `str` | Regex filter for barcode text |
| `max_threads_in_one_task` | `int` | Max threads per task |
| `scale_down_threshold` | `int` | Image shrinking threshold |

---

## Barcode Detail Classes

All inherit from `BarcodeDetails` (abstract base). Returned by `BarcodeResultItem.get_details()`.

### OneDCodeDetails (BarcodeDetails)

| Attribute | Type |
|---|---|
| `start_chars_bytes` | `bytes` |
| `stop_chars_bytes` | `bytes` |
| `check_digit_bytes` | `bytes` |
| `start_pattern_range` | `List[float]` |
| `middle_pattern_range` | `List[float]` |
| `end_pattern_range` | `List[float]` |

### QRCodeDetails (BarcodeDetails)

| Attribute | Type |
|---|---|
| `rows`, `columns` | `int` |
| `error_correction_level` | `int` (EnumQRCodeErrorCorrectionLevel) |
| `version`, `model`, `mode` | `int` |
| `page`, `total_page`, `parity_data` | `int` |
| `data_mask_pattern` | `int` |
| `codewords` | `bytes` |

### PDF417Details (BarcodeDetails)

| Attribute | Type |
|---|---|
| `rows`, `columns` | `int` |
| `error_correction_level` | `int` |
| `has_left_row_indicator`, `has_right_row_indicator` | `int` |
| `codewords` | `List[int]` |

### DataMatrixDetails (BarcodeDetails)

| Attribute | Type |
|---|---|
| `rows`, `columns` | `int` |
| `data_region_rows`, `data_region_columns`, `data_region_number` | `int` |

### AztecDetails (BarcodeDetails)

| Attribute | Type |
|---|---|
| `rows`, `columns`, `layer_number` | `int` |

---

## ECI Support

### ECISegment

| Attribute | Type | Description |
|---|---|---|
| `eci_value` | `int` | ECI assignment number (ISO/IEC 15424) |
| `charset_encoding` | `str` | Charset name (e.g. "UTF-8") |
| `start_index` | `int` | Start index in decoded bytes |
| `length` | `int` | Length in bytes |

---

## Intermediate Result Classes

Used with `IntermediateResultReceiver` for pipeline-level access.

### LocalizedBarcodeElement (RegionObjectElement)

| Method | Returns |
|---|---|
| `get_possible_formats()` | `int` |
| `get_possible_formats_string()` | `str` |
| `get_angle()` | `int` |
| `get_module_size()` | `int` |
| `get_confidence()` | `int` |
| `set_possible_formats(formats: int)` | `None` |
| `set_location(location: Quadrilateral)` | `int` |

### DecodedBarcodeElement (RegionObjectElement)

Same methods as `BarcodeResultItem` plus:

| Method | Returns |
|---|---|
| `get_extended_barcode_results_count()` | `int` |
| `get_extended_barcode_result(index: int)` | `ExtendedBarcodeResult` |
| `set_format(format: int)` | `None` |
| `set_text(text: str)` | `None` |
| `set_bytes(bytes: bytes)` | — |
| `set_confidence(confidence: int)` | `None` |
| `set_location(location: Quadrilateral)` | `int` |

### ExtendedBarcodeResult (DecodedBarcodeElement)

| Method | Returns | Description |
|---|---|---|
| `get_extended_barcode_result_type()` | `int` | `EnumExtendedBarcodeResultType` |
| `get_deformation()` | `int` | Deformation level |
| `get_clarity()` | `int` | Clarity score |
| `get_sampling_image()` | `ImageData` | Sampling image |

### Intermediate Result Units

| Class | Parent | Key Methods |
|---|---|---|
| `LocalizedBarcodesUnit` | `IntermediateResultUnit` | `get_count()`, `get_localized_barcode(index)` |
| `DecodedBarcodesUnit` | `IntermediateResultUnit` | `get_count()`, `get_decoded_barcode(index)` |
| `CandidateBarcodeZonesUnit` | `IntermediateResultUnit` | `get_count()`, `get_candidate_barcode_zone(index)` |
| `ScaledBarcodeImageUnit` | `IntermediateResultUnit` | `get_image_data()`, `set_image_data(img)` |
| `DeformationResistedBarcodeImageUnit` | `IntermediateResultUnit` | `get_deformation_resisted_barcode()` |
| `ComplementedBarcodeImageUnit` | `IntermediateResultUnit` | `get_image_data()`, `get_location()` |

### CandidateBarcodeZone

| Method | Returns |
|---|---|
| `get_location()` / `set_location(loc)` | `Quadrilateral` / `None` |
| `get_possible_formats()` / `set_possible_formats(formats)` | `int` / `None` |

### DeformationResistedBarcode

| Method | Returns |
|---|---|
| `get_image_data()` / `set_image_data(img)` | `ImageData` / `None` |
| `get_location()` / `set_location(loc)` | `Quadrilateral` / `None` |
| `get_format()` / `set_format(format)` | `int` / `None` |

---

## Utility

### BarcodeReaderModule

| Method | Returns |
|---|---|
| `BarcodeReaderModule.get_version()` (static) | `str` — module version |
