import os
import sys
import json
from dbr import *

#you can change the following four variables' value to your own value.
license_key = "Input your own license"
#license_server = "Input the name/IP of the license server"

reader = BarcodeReader()

reader.init_license(license_key)
#reader.init_license_from_server(license_server, license_key)
#license_content = reader.output_license_to_string()
#reader.init_license_from_license_content(license_key, license_content)

settings = reader.get_runtime_settings()
print("Original BarcodeFormatIds : " + str(settings.barcode_format_ids))
print("Original ExpectedBarcodesCount : " + str(settings.expected_barcodes_count))

settings.barcode_format_ids = EnumBarcodeFormat.BF_ONED | EnumBarcodeFormat.BF_QR_CODE
settings.expected_barcodes_count = 10
try:
    reader.update_runtime_settings(settings)
    outputSettings = reader.get_runtime_settings()
    print("Modified BarcodeFormatIds : " + str(outputSettings.barcode_format_ids))
    print("Modified ExpectedBarcodesCount : " + str(outputSettings.expected_barcodes_count))
except BarcodeReaderError as bre:
    print(bre)
