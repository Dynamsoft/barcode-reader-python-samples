# Dynamsoft Barcode Reader samples for Python edition

[![Current version number](https://img.shields.io/pypi/v/dbr?color=orange)](https://pypi.org/project/dbr/)
[![Supported Python versions](https://img.shields.io/badge/python-3.6%20%7C%203.7%20%7C%203.8%20%7C%203.9%20%7C%203.10%20%7C%203.11%20%7C%203.12-blue)](https://www.python.org/downloads/)
[![PyPI downloads](https://img.shields.io/pypi/dm/dbr)](https://pypistats.org/packages/dbr)

![Dynamsoft](https://dynamsoft.github.io/styleguide/assets/images/icons/dynamsoft_logos/dynamsoft_logo_original.png "Dynamsoft")  

## Overview

This repository contains multiple samples that demonstrate how to use the [Dynamsoft Barcode Reader](https://www.dynamsoft.com/barcode-reader/overview/) Python Edition.

## Requirements

### Supported Platforms
- Windows x64
- Linux (x64, ARM32, ARM64)
- macOS (10.15+)

### Supported Python Versions

- Python 3.6
- Python 3.7
- Python 3.8
- Python 3.9
- Python 3.10
- Python 3.11
- Python 3.12


## Installation

```
pip install dbr
```

or 

```
pip3 install dbr
```

## Samples

| Sample Name | Description |
| ----------- | ----------- |
| [`hello-world`](samples/hello-world.py) | Shows the simplest way to recognize barcodes from images in Python using Dynamsoft Barcode Reader SDK. |
| [`general-settings`](samples/general-settings.py) | Shows how to adjust general scan settings, e.g., barcode format, barcode count, scan region. | 
| [`image-decoding`](samples/image-decoding.py) | Shows how to decode images in various formats, e.g., file bytes, opencv image, raw image  buffer. | 
| [`video-decoding`](samples/video-decoding.py) | Shows how to decode barcodes from a video from a file or camera. | 
| [`video-decoding-for-picamera`](samples/video-decoding-for-picamera.py) | Shows how to scan barcodes from videos from a Raspberry Pi camera (PiCamera). | 
| [`batch-decode`](samples/performance/batch-decode.py) | Shows how to batch decode image files from a specified folder. |
| [`speed-first-settings`](samples/performance/speed-first-settings.py) | Shows how to configure the scan settings for best barcode reading speed. |
| [`read-rate-first-settings`](samples/performance/read-rate-first-settings.py) | Shows how to configure the scan settings to read as many barcodes as possible at one time. Recommended when decoding multiple barcodes from a single image. |
| [`accuracy-first-settings`](samples/performance/accuracy-first-settings.py) | Shows how to configure the scan settings for best barcode reading accuracy. |
| [`read-dpm-barcode`](samples/use-case/read-dpm-barcode.py) | Shows how to read DPM (Direct Part Mark) barcodes. |

## Documentation

https://www.dynamsoft.com/barcode-reader/docs/server/programming/python/?ver=latest&utm_source=samples

## License

The barcode reader library requires a license to work. You can use the API `init_license` to initialize the license key and activate the SDK.

These samples use a free public trial license which requires a network connection to function. You can request a 30-day free trial license key from <a href="https://www.dynamsoft.com/customer/license/trialLicense?architecture=dcv&product=dbr&utm_source=samples&package=python" target="_blank">Customer Portal</a> which works offline.

## Contact Us

https://www.dynamsoft.com/company/contact/
