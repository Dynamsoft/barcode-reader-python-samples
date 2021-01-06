import os
import sys
from dbr import *

reader = BarcodeReader()

connection_paras = BarcodeReader.init_lts_connection_parameters()
# If DBR service is already built on your server, you can fill in the address of your server, or leave this property's default value.
connection_paras.main_server_url = "Input your own server url"
connection_paras.handshake_code = "Input your own handshake"
connection_paras.deployment_type = EnumDMDeploymentType.DM_DT_DESKTOP
connection_paras.uuid_generation_method = EnumDMUUIDGenerationMethod.DM_UUIDGM_RANDOM

try:
    error = BarcodeReader.init_license_from_lts(connection_paras)
    if error[0] != EnumErrorCode.DBR_OK:
        print(error[1])
except BarcodeReaderError as bre:
    print(bre)

