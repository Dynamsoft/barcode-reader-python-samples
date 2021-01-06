import os
import sys
import json
from dbr import *

#you can change the following four variables' value to your own value.
license_key = "Input your own license"
input_json_string = '{"ImageParameter" : { "BarcodeFormatIds" : [ "BF_ALL" ], "DeblurLevel" : 9, "Description" : "", "ExpectedBarcodesCount" : 0, "MaxAlgorithmThreadCount" : 4, "Name" : "IP_1", "Timeout" : 10000}, "Version" : "3.0"}'
#conflict_mode should be a value which is in EnumConflictMode.
conflict_mode = EnumConflictMode.CM_OVERWRITE

reader = BarcodeReader()

# Apply for a trial license: https://www.dynamsoft.com/customer/license/trialLicense
reader.init_license(license_key)

## The code snippet below shows how to use the full license in DBR 8.x:
# connection_paras = BarcodeReader.init_lts_connection_parameters()
## If DBR service is already built on your server, you can fill in the address of your server, or leave this property's default value.
# connection_paras.main_server_url = "Input your own server url"
# connection_paras.handshake_code = "Input your own handshake"
# connection_paras.deployment_type = EnumDMDeploymentType.DM_DT_DESKTOP
# connection_paras.uuid_generation_method = EnumDMUUIDGenerationMethod.DM_UUIDGM_RANDOM
# try:
#     error = BarcodeReader.init_license_from_lts(connection_paras)
#     if error[0] != EnumErrorCode.DBR_OK:
#         print(error[1])
# except BarcodeReaderError as bre:
#     print(bre)

error = reader.init_runtime_settings_with_string(input_json_string)
if error[0] != EnumErrorCode.DBR_OK:
    print(error[1])

template_names = reader.get_all_template_names()
print(template_names)

save_json_string = reader.output_settings_to_json_string()
print(save_json_string)