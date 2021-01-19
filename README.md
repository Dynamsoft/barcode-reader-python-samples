# Welcome to Dynamsoft Barcode Reader - Python Edition
[![Current version number](https://img.shields.io/pypi/v/dbr?color=orange)](https://pypi.org/project/dbr/)
[![Supported Python versions](https://img.shields.io/badge/python-3.6%20%7C%203.7%20%7C%203.8-blue)](https://www.python.org/downloads/)
[![PyPI downloads](https://img.shields.io/pypi/dm/dbr)](https://pypistats.org/packages/dbr)

![Dynamsoft](https://dynamsoft.github.io/styleguide/assets/img-icon/logo-dynamsoft-whiteBg-190x47.png "Dynamsoft")  | ![dbr](https://dynamsoft.github.io/styleguide/assets/img-icon/logo-dbr-88x88.png "dbr")


**[Dynamsoft's Barcode Reader SDK](https://www.dynamsoft.com/Products/Dynamic-Barcode-Reader.aspx) enables you to efficiently embed barcode reading functionality in your web, desktop or mobile application using just a few lines of code. Saving you months of added development time and resources, our SDK can create high-speed and reliable barcode scanner software applications to meet your business needs.**

## Dynamsoft Barcode Reader - Python Edition

*Dynamsoft Barcode Reader's Python Edition comes with all the general features of Dynamsoft Barcode Reader, bringing convenience for customers who develop in Python. In addition, you could refer to the Python samples available in our [Github](https://github.com/dynamsoft-dbr/python-barcode) when building your own application. If you have any inquiries about our product, please contact us at support@dynamsoft.com. If you need more information, please check out our [documentation site](https://www.dynamsoft.com/barcode-reader/programming/python/).*

## Table Of Contents
- [Version](#version)
- [Supported Python Version](#supported-python-version)
- [Supported Platforms](#supported-platforms)
- [Installation](#installation)
- [License](#license)
- [Supported Symbologies](#supported-symbologies)
- [Release Notes](#release-notes)
- [Interfaces](#interfaces)
	- [Enumerations](#enum-interfaces)
	- [Classes](#Classes)
	- [Main Class Interface](#main-class-interface)
- [Appendix](#appendix)
	- [Code Snippet](#code-snippet)
- [Contact Us](#contact-us)

### Version

- **8.1**

### Supported Platforms
- **Windows x64**

- **Linux(x64, ARM32, ARM64)**

- **macOS(10.15+)**

### Supported Python Versions

- **Python3.6**

- **Python3.7**

- **Python3.8**

### Installation

>**pip install dbr** or **pip3 install dbr**

### License

Apply for a trial license: https://www.dynamsoft.com/customer/license/trialLicense

### Supported Symbologies
*We support all major barcodes symbologies across a variety of industries such as government, finance, retail, warehouse inventory, and healthcare.*

- **Linear Barcodes (1D)** :
    - Code 39 *(including Code 39 Extended)*
	- Code 93
	- Code 128
	- Codabar
	- Interleaved 2 of 5
	- EAN-8
	- EAN-13
	- UPC-A
	- UPC-E
	- Industrial 2 of 5
    - MSI Code
- **2D Barcodes** :
	- QR Code *(including Micro QR Code)*
	- Data Matrix
	- PDF417 *(including Micro PDF417)*
	- Aztec Code
	- MaxiCode *(mode 2-5)*
- **Patch Code**
- **GS1 Composite Code**
- **GS1 DataBar** :
	- Omnidirectional
	- Truncated
	- Stacked
	- Stacked Omnidirectional
	- Limited
	- Expanded
	- Expanded Stacked
- **Postal Codes** :
	- USPS Intelligent Mail
	- Postnet
	- Planet
	- Australian Post
	- UK Royal Mail

### Release Notes 

https://www.dynamsoft.com/barcode-reader/programming/python/?ver=latest#release-notes

### Interfaces

#### Enumerations
https://www.dynamsoft.com/barcode-reader/programming/python/api-reference/?ver=latest#enumerations

#### Classes
https://www.dynamsoft.com/barcode-reader/programming/python/api-reference/?ver=latest#classes

#### Main Class Interface
https://www.dynamsoft.com/barcode-reader/programming/python/api-reference/?ver=latest#barcodereader-methods

### Appendix

#### Code Snippet

```
import os
import sys
import cv2
import json
from typing import List
from dbr import *

# you can replace the following variables' value with yours.
license_key = "Input your own license"
#license_server = "Input the name/IP of the license server"
json_file = r"Please input your own template path"
image = r"Please input your own image path"

reader = BarcodeReader()

reader.init_license(license_key)
#reader.init_license_from_server(license_server, license_key)
#license_content = reader.output_license_to_string()
#reader.init_license_from_license_content(license_key, license_content)

error = reader.init_runtime_settings_with_file(json_file)
if error[0] != EnumErrorCode.DBR_OK:
    print(error[1])

if sys.version_info.major == 3 and sys.version_info.minor >= 6:

    try:
        text_results:List[TextResult] = reader.decode_file(image)

        if text_results != None:
            for text_result in text_results:
                print("Barcode Format : ")
                print(text_result.barcode_format_string)
                print("Barcode Text : ")
                print(text_result.barcode_text)
                print("Localization Points : ")
                print(text_result.localization_result.localization_points)
                print("Exception : ")
                print(text_result.exception)
                print("-------------")
    except BarcodeReaderError as bre:
        print(bre)

else:
    try:
        text_results = reader.decode_file(image)

        if text_results != None:
            for text_result in text_results:
                print("Barcode Format : ")
                print(text_result.barcode_format_string)
                print("Barcode Text :")
                print(text_result.barcode_text)
                print("Localization Points : ")
                print(text_result.localization_result.localization_points)
                print("Exception : ")
                print(text_result.exception)
                print("-------------")
    except BarcodeReaderError as bre:
        print(bre)
```

### Contact Us
<support@dynamsoft.com>
