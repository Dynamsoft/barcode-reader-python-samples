# Dynamsoft Barcode Reader Samples for Python Edition

[![Current version number](https://img.shields.io/pypi/v/dynamsoft_barcode_reader_bundle?color=orange)](https://pypi.org/project/dynamsoft_barcode_reader_bundle/)
[![Supported Python versions](https://img.shields.io/badge/python-3.8%20%7C%203.9%20%7C%203.10%20%7C%203.11%20%7C%203.12%20%7C%203.13-blue)](https://www.python.org/downloads/)
[![PyPI downloads](https://img.shields.io/pypi/dm/dynamsoft_barcode_reader_bundle)](https://pypistats.org/packages/dynamsoft_barcode_reader_bundle)

![Dynamsoft](https://dynamsoft.github.io/styleguide/assets/images/icons/dynamsoft_logos/dynamsoft_logo_original.png "Dynamsoft")  

## Overview

This repository contains multiple samples that demonstrate how to use the [Dynamsoft Barcode Reader](https://www.dynamsoft.com/barcode-reader/overview/) Python Edition.

## Requirements

### Supported Platforms
- Windows x64
- Linux (x64, ARM64)
- macOS (10.15+)

### Supported Python Versions

- Python 3.13
- Python 3.12
- Python 3.11
- Python 3.10
- Python 3.9
- Python 3.8

## Installation

```
pip install dynamsoft_barcode_reader_bundle
```

or 

```
pip3 install dynamsoft_barcode_reader_bundle
```

## Samples

### Basic Barcode Reader Samples

| Sample Name | Description |
| ----------- | ----------- |
| [`ReadAnImage`](Samples/read_an_image.py) | Shows the simplest way to read barcodes from an image file and output barcode format and text. |
| [`ReadMultipleImages`](Samples/read_multiple_images.py) | Shows the simplest way to read barcodes from directory with image files and output barcode format and text. | 
| [`GeneralSettings`](Samples/general_settings.py) | Shows how to adjust general scan settings, e.g., barcode format, barcode count, scan region. | 
| [`ReadDPMBarcode`](Samples/read_dpm_barcode.py) | Shows how to read DPM (Direct Part Mark) barcodes. | 
| [`VideoDecoding`](Samples/video_decoding.py) | Shows how to decode barcodes from live video or video file. | 
| [`MultiFormatImageProcessing`](Samples/multi_format_image_processing.py) | Shows how to decode barcodes from various image format. | 

### Additional Samples using Capture Vision SDK

In addition to the classic barcode decoding samples listed above, the following samples go a step further by parsing the decoded results and showcasing more structured workflows.

> [!IMPORTANT]
> These samples use the `dynamsoft_capture_vision_bundle` package instead of `dynamsoft_barcode_reader_bundle`. If you're switching to these samples, make sure to install and use the correct package.

| Sample Name | Description |
| --- | --- |
| [`DriverLicenseScanner`](https://github.com/Dynamsoft/capture-vision-python-samples/blob/main/Samples/driver_license_scanner.py) | Shows how to capture and extract user's information from driver license/ID. |
| [`VINScanner`](https://github.com/Dynamsoft/capture-vision-python-samples/blob/main/Samples/vin_scanner.py) | Shows how to capture and extract vehicle's information from Vehicle Identification Number (VIN). |

## Documentation

https://www.dynamsoft.com/barcode-reader/docs/server/programming/python/?ver=latest&utm_source=samples

## License

The library requires a license to work, you use the API `LicenseManager.init_license` to initialize license key and activate the SDK.

These samples use a free public trial license which require network connection to function. You can request a 30-day free trial license via the <a href="https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=github&package=python" target="_blank">Request a Trial License</a> link which works offline.

## Contact Us

https://www.dynamsoft.com/company/contact/
