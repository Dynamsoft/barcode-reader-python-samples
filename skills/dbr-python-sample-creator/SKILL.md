---
name: dbr-python-sample-creator
description: >
  Use when implementing Python sample code using the Dynamsoft Barcode Reader SDK
  (`dynamsoft_barcode_reader_bundle` package). This skill covers all barcode reading
  use cases including 1D barcodes, QR codes, PDF417, DataMatrix, DPM barcodes,
  and any other barcode decoding scenario built on the DBR Python Edition.
  Use this skill whenever the user mentions Dynamsoft Barcode Reader, DBR,
  `dynamsoft_barcode_reader_bundle`, `CaptureVisionRouter` for barcode reading,
  barcode scanning with Dynamsoft, barcode decoding, or wants to create a Python
  sample that processes images to extract barcodes.
---

# DBR Python Sample Creator

This skill helps you write Python sample code using the `dynamsoft_barcode_reader_bundle` SDK. The SDK provides a pipeline for barcode reading — orchestrated through a single central class called `CaptureVisionRouter`.

## Before you start

read the appropriate reference files from the `references/` directory alongside this SKILL.md to understand the API you're working with. The references are organized by module — only read what you need for the task at hand:

| Reference file | When to read |
|---|---|
| `references/api-core.md` | Always — contains foundational types, enums, geometry, ImageData, error codes |
| `references/api-cvr.md` | Always — CaptureVisionRouter, templates, settings, result receivers |
| `references/api-dbr.md` | Always — barcode reading API, barcode formats, result items, settings |
| `references/api-utility.md` | When the task involves batch processing, video, cross-frame filtering, or image I/O |
| `references/api-license.md` | Always — license initialization |
| `references/sample-patterns.md` | Always — canonical code patterns extracted from existing samples |

## SDK Architecture Overview

The SDK follows a **pipeline architecture** centered around `CaptureVisionRouter`:

```
Image Input → CaptureVisionRouter (with template) → CapturedResult
                                                      └── DecodedBarcodesResult
```

**Key concepts:**
- **CaptureVisionRouter** — The central orchestrator. Create an instance, optionally configure settings/templates, then call `capture()` or `capture_multi_pages()` to process images.
- **Templates** — Define what the pipeline does. Use `EnumPresetTemplate` constants for common tasks, or load custom JSON templates for specialized scenarios.
- **Results** — Processing returns a `CapturedResult` (single image) or `CapturedResultArray` (multi-page). Extract barcode results using `get_decoded_barcodes_result()`.

## Writing Samples: Step by Step

Every DBR Python sample follows this structure. Understanding this flow is essential because deviating from it leads to subtle bugs — for instance, forgetting to check the license error code will cause silent failures.

### Step 1: Import

Always use the wildcard import — the package re-exports everything from all submodules:

```python
from dynamsoft_barcode_reader_bundle import *
```

For additional libraries (os, sys, cv2, Flask, etc.), import them separately as needed.

### Step 2: Initialize License

License initialization must happen once, before creating any `CaptureVisionRouter` instance. The SDK returns a tuple of `(error_code, error_message)`.

**License string priority**: Default hard-coded license string is `"DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTEwNTI2NzQwMSJ9"`.

**Required comment block**: Every sample must include this 3-line comment block immediately before the `init_license` call. This comment is mandatory — never omit it. Adjust the quoted license string in the third line to match whichever license string is actually used in the code:

```python
    # 1. Initialize license.
    # You can request and extend a trial license from https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
    # The string 'DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTEwNTI2NzQwMSJ9' here is a free public trial license. Note that network connection is required for this license to work.
```

Full license initialization pattern:

```python
    # 1. Initialize license.
    # You can request and extend a trial license from https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
    # The string 'DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTEwNTI2NzQwMSJ9' here is a free public trial license. Note that network connection is required for this license to work.
    error_code, error_msg = LicenseManager.init_license("DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTEwNTI2NzQwMSJ9")
    if error_code != EnumErrorCode.EC_OK and error_code != EnumErrorCode.EC_LICENSE_WARNING:
        print("License initialization failed: ErrorCode:", error_code, ", ErrorString:", error_msg)
    else:
        # proceed with the rest of the sample
        ...
```

Check against both `EC_OK` and `EC_LICENSE_WARNING` (warnings are non-fatal).

### Step 3: Create CaptureVisionRouter

```python
cvr_instance = CaptureVisionRouter()
```

No arguments needed. If using a custom JSON template, load it right after:

```python
error_code, error_msg = cvr_instance.init_settings_from_file("path/to/template.json")
if error_code != EnumErrorCode.EC_OK:
    print("Init template failed:", error_msg)
```

### Step 4: Process Images

There are three processing paradigms. Choose based on the use case:

#### A. Single-shot capture (simplest, for one image at a time)

```python
result = cvr_instance.capture(image_path, EnumPresetTemplate.PT_READ_BARCODES)
```

The `capture()` method accepts multiple input types:
- `str` — file path
- `bytes` — file bytes in memory
- `ImageData` — SDK's own image class
- `numpy.ndarray` — OpenCV/PIL array (BGR format from OpenCV, RGB from PIL)

#### B. Multi-page capture (for PDFs, TIFFs, or any file)

```python
result_array = cvr_instance.capture_multi_pages(image_path, EnumPresetTemplate.PT_READ_BARCODES)
results = result_array.get_results()
for i, result in enumerate(results):
    # process each page's result
    ...
```

This is the preferred method for file-based processing because it handles multi-page files correctly. Even for single-page images it works fine — you'll just get one result.

#### C. Continuous/streaming capture (for video or batch directories)

This uses the observer pattern with `ImageSourceAdapter`, `CapturedResultReceiver`, and optionally `ImageSourceStateListener`:

```python
# Set up image source
fetcher = DirectoryFetcher()  # or custom ImageSourceAdapter subclass
fetcher.set_directory("path/to/images")
cvr_instance.set_input(fetcher)

# Set up result receiver
receiver = MyCapturedResultReceiver()  # subclass of CapturedResultReceiver
cvr_instance.add_result_receiver(receiver)

# Set up state listener (to know when processing is done)
listener = MyImageSourceStateListener(cvr_instance)
cvr_instance.add_image_source_state_listener(listener)

# Start processing
cvr_instance.start_capturing(EnumPresetTemplate.PT_READ_BARCODES, True)
```

### Step 5: Extract Results

After capturing, extract barcode results. Always check for errors first:

```python
if result.get_error_code() != EnumErrorCode.EC_OK:
    print("Error:", result.get_error_code(), result.get_error_string())
```

Note: `EC_UNSUPPORTED_JSON_KEY_WARNING` is a warning, not a fatal error — print a warning but continue processing.

**Barcode results:**
```python
barcode_result = result.get_decoded_barcodes_result()
if barcode_result is not None and barcode_result.get_items() != 0:
    for item in barcode_result.get_items():
        print("Format:", item.get_format_string())
        print("Text:", item.get_text())
```

## Preset Templates Quick Reference

| Template | Use for |
|---|---|
| `PT_READ_BARCODES` | General barcode reading |
| `PT_READ_BARCODES_SPEED_FIRST` | Fast barcode reading (sacrifices accuracy) |
| `PT_READ_BARCODES_READ_RATE_FIRST` | Max accuracy barcode reading |
| `PT_READ_SINGLE_BARCODE` | Optimized for exactly one barcode |

## Custom JSON Templates

When preset templates don't meet requirements, create a custom JSON template. The template structure has these top-level arrays:

```json
{
    "CaptureVisionTemplates": [...],       // Main entry: names, ROI refs, timeout
    "TargetROIDefOptions": [...],          // ROI definitions → task references
    "BarcodeReaderTaskSettingOptions": [...], // Barcode reading config
    "ImageParameterOptions": [...],        // Image processing parameters
    "BarcodeFormatSpecificationOptions": [...] // Barcode-format-specific settings
}
```

Load custom templates with:
```python
cvr_instance.init_settings_from_file("path/to/template.json")
# Then use the template name from the JSON:
result = cvr_instance.capture(image, "TemplateName")
```

## Settings Customization via API

For simpler adjustments (without JSON templates), use the simplified settings API:

```python
err_code, err_str, settings = cvr_instance.get_simplified_settings(EnumPresetTemplate.PT_READ_BARCODES)

# Adjust barcode settings
settings.barcode_settings.barcode_format_ids = EnumBarcodeFormat.BF_QR_CODE | EnumBarcodeFormat.BF_PDF417
settings.barcode_settings.expected_barcodes_count = 10
settings.barcode_settings.grayscale_transformation_modes[0] = EnumGrayscaleTransformationMode.GTM_AUTO

# Adjust ROI
settings.roi_measured_in_percentage = 1
points = settings.roi.points
points[0].x, points[0].y = 0, 0
points[1].x, points[1].y = 100, 0
points[2].x, points[2].y = 100, 100
points[3].x, points[3].y = 0, 100

# Apply
cvr_instance.update_settings(EnumPresetTemplate.PT_READ_BARCODES, settings)
```

## Multi-page Result Handling

When using `capture_multi_pages()`, results come as a `CapturedResultArray`. Use this pattern to handle page numbers correctly:

```python
result_array = cvr_instance.capture_multi_pages(image_path, template)
results = result_array.get_results()
if results is None or len(results) == 0:
    print("No results.")
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

        # ... extract barcode results here
```

## Advanced Patterns

### Video/Camera Decoding

For real-time video, subclass `ImageSourceAdapter` to feed frames, and use `CapturedResultReceiver` for async results. Also consider `MultiFrameResultCrossFilter` for deduplication:

```python
class MyVideoFetcher(ImageSourceAdapter):
    def has_next_image_to_fetch(self) -> bool:
        return True

# Setup
fetcher = MyVideoFetcher()
fetcher.set_max_image_count(100)
fetcher.set_buffer_overflow_protection_mode(EnumBufferOverflowProtectionMode.BOPM_UPDATE)
fetcher.set_colour_channel_usage_type(EnumColourChannelUsageType.CCUT_AUTO)
cvr_instance.set_input(fetcher)

# Add cross-frame filter for dedup
filter = MultiFrameResultCrossFilter()
filter.enable_result_cross_verification(EnumCapturedResultItemType.CRIT_BARCODE, True)
filter.enable_result_deduplication(EnumCapturedResultItemType.CRIT_BARCODE, True)
filter.set_duplicate_forget_time(EnumCapturedResultItemType.CRIT_BARCODE, 5000)
cvr_instance.add_result_filter(filter)

# Feed frames from OpenCV
tag = FileImageTag("", 0, 0)
tag.set_image_id(image_id)
image = ImageData(frame.tobytes(), width, height, stride, EnumImagePixelFormat.IPF_RGB_888, 0, tag)
fetcher.add_image_to_buffer(image)
```

### Intermediate Results

For advanced scenarios like visualizing barcode localization vs decoding, use `IntermediateResultReceiver`:

```python
class MyIRR(IntermediateResultReceiver):
    def on_localized_barcodes_received(self, result, info):
        if info.is_section_level_result:
            for i in range(result.get_count()):
                element = result.get_localized_barcode(i)
                location = element.get_location()

irm = cvr_instance.get_intermediate_result_manager()
irr = MyIRR()
irm.add_result_receiver(irr)
```

### Image I/O and Drawing

```python
# Read image
io = ImageIO()
err, image = io.read_from_file("input.png")

# Save image
io.save_to_file(image_data, "output.png")

# Draw on image
drawer = ImageDrawer()
image = drawer.draw_on_image(image, quadrilaterals, 0xFF00FF00, 2)  # green, thickness 2
```

### Server-Side (Flask)

For web service integration, create a new `CaptureVisionRouter()` per request (or use a singleton with thread safety). Accept images via multipart, JSON (base64), or raw binary:

```python
from flask import Flask, request, jsonify

@app.route('/decode', methods=['POST'])
def decode():
    data = request.files['file'].read()  # or request.get_data()
    cvr = CaptureVisionRouter()
    result = cvr.capture(data, EnumPresetTemplate.PT_READ_BARCODES)
    # extract and return results as JSON
```

## Code Style Conventions

Follow these conventions to produce samples consistent with the existing codebase:

- Use `if __name__ == '__main__':` as the entry point
- Use numbered comments like `# 1. Initialize license.` for major steps
- Print informative messages including error codes and descriptions
- End with `input("Press Enter to quit...")` for interactive CLI samples
- Use `Path(__file__).resolve().parent` for relative path resolution
- Handle both `EC_OK` and `EC_LICENSE_WARNING` / `EC_UNSUPPORTED_JSON_KEY_WARNING` where appropriate
- For interactive samples, support loop with quit option (`'Q'/'q'`)
