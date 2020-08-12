import os
import sys
import json
from dbr import *

# you can change the following variables' value to your own value.
license_key = "Input your own license"
#license_server = "Input the name/IP of the license server"

json_file = r"Please input your own template path"
append_json_file = r"Please input your own template path"
save_file_path = r"Please input your own output template path"

#conflict_mode should be a value which is in EnumConflictMode.
conflict_mode = EnumConflictMode.CM_OVERWRITE

reader = BarcodeReader()

# Apply for a trial license: https://www.dynamsoft.com/CustomerPortal/Portal/Triallicense.aspx
reader.init_license(license_key)

#reader.init_license_from_server(license_server, license_key)
#license_content = reader.output_license_to_string()
#reader.init_license_from_license_content(license_key, license_content)

error = reader.init_runtime_settings_with_file(json_file)
if error[0] != EnumErrorCode.DBR_OK:
    print(error[1])

error = reader.append_template_file_to_runtime_settings(append_json_file, conflict_mode)
if error[0] != EnumErrorCode.DBR_OK:
    print(error[1])

template_names = reader.get_all_template_names()
print(template_names)

reader.output_settings_to_json_file(save_file_path)