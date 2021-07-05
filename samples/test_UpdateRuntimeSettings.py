import os
import sys
import json
from dbr import *

#you can change the following four variables' value to your own value.
license_key = "Input your own license"

reader = BarcodeReader()

# Apply for a trial license: https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=github
reader.init_license(license_key)

## The code snippet below shows how to use the full license in DBR 8.x:
# connection_paras = BarcodeReader.init_dls_connection_parameters()
## If DBR service is already built on your server, you can fill in the address of your server, or leave this property's default value.
# connection_paras.main_server_url = "Input your own server url"
# connection_paras.handshake_code = "Input your own handshake"
# connection_paras.deployment_type = EnumDMDeploymentType.DM_DT_DESKTOP
# connection_paras.uuid_generation_method = EnumDMUUIDGenerationMethod.DM_UUIDGM_RANDOM
# try:
#     error = BarcodeReader.init_license_from_dls(connection_paras)
#     if error[0] != EnumErrorCode.DBR_OK:
#         print(error[1])
# except BarcodeReaderError as bre:
#     print(bre)

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
