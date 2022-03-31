# Dynamsoft Barcode Reader samples for Python edition

[![Current version number](https://img.shields.io/pypi/v/dbr?color=orange)](https://pypi.org/project/dbr/)
[![Supported Python versions](https://img.shields.io/badge/python-3.6%20%7C%203.7%20%7C%203.8%20%7C%203.9%20%7C%203.10-blue)](https://www.python.org/downloads/)
[![PyPI downloads](https://img.shields.io/pypi/dm/dbr)](https://pypistats.org/packages/dbr)

![Dynamsoft](https://dynamsoft.github.io/styleguide/assets/images/icons/dynamsoft_logos/dynamsoft_logo_original.png "Dynamsoft")  

## Overview

This repository contains multiple samples that demonstrates how to use the [Dynamsoft Barcode Reader](https://www.dynamsoft.com/barcode-reader/overview/) Python Edition.

## Requirements

### Supported Platforms
- Windows x64
- Linux(x64, ARM32, ARM64)
- macOS(10.15+)

### Supported Python Versions

- Python3.6
- Python3.7
- Python3.8
- Python3.9
- Python3.10

## Installation

>**pip install dbr** or **pip3 install dbr**

## Samples

| Sample Name | Description |
| ----------- | ----------- |
| [`hello-world`](samples/hello-world.py) | This is a python sample that illustrates the simplest way to recognize barcodes from images with Dynamsoft Barcode Reader SDK. |
| [`general-settings`](samples/general-settings.py) | This is a python sample that illustrates how to make general settings (including barcode format/barcode count/scan region) when using Dynamsoft Barcode Reader. | 
| [`image-decoding`](samples/image-decoding.py) | This is a python sample that illustrates how to decode images in various format (including file bytes/opencv image/image raw buffer) when using Dynamsoft Barcode Reader. | 
| [`video-decoding`](samples/video-decoding.py) | This is a python sample that illustrates how to decode video from a file or camera when using Dynamsoft Barcode Reader. | 
| [`video-decoding-for-picamera`](samples/video-decoding-for-picamera.py) | This is a python sample that illustrates how to decode videos from PiCamera in the Raspberry Pi when using Dynamsoft Barcode Reader. | 
| [`batch-decode`](samples/performance/batch-decode.py) | This is a python sample that shows how to decode image files in a specified folder. |
| [`speed-first-settings`](samples/performance/speed-first-settings.py) | This is a python sample that shows how to configure Dynamsoft Barcode Reader to read barcodes as fast as possible. The downside is that read-rate and accuracy might be affected. |
| [`read-rate-first-settings`](samples/performance/read-rate-first-settings.py) | This is a python sample that shows how to configure Dynamsoft Barcode Reader to read as many barcodes as possible at one time. The downside is that speed and accuracy might be affected. It is recommended to apply these configurations when decoding multiple barcodes from a single image. |
| [`accuracy-first-settings`](samples/performance/accuracy-first-settings.py) | This is a python sample that shows how to configure Dynamsoft Barcode Reader to read barcodes as accurately as possible. The downside is that speed and read-rate might be affected. It is recommended to apply these configurations when misreading is unbearable. |
| [`read-dpm-barcode`](samples/use-case/read-dpm-barcode.py) | This is a python sample that shows how to configure Dynamsoft Barcode Reader to read DPM barcodes. |

## Documentation

https://www.dynamsoft.com/barcode-reader/programming/python/?ver=latest&utm_source=samples

## License

The library requires a license to work, you use the API init_license to initialize license key and activate the SDK.

These samples use a <a href="https://www.dynamsoft.com/license-server/docs/about/terms.html?ver=latest&product=dbr&utm_source=samples&package=python#public-trial-license" target="_blank">free public trial license</a>. Note that network connection is required for this license to work.

You can also request a 30-day trial license from <a href="https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python" target="_blank">Customer Portal</a>

For more information, please refer to https://www.dynamsoft.com/license-server/docs/about/licensefaq.html.

## Contact Us

https://www.dynamsoft.com/company/contact/
