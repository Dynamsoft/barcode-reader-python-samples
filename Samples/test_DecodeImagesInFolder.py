import os
import random
import glob
import time
import cv2
import numpy as np
from typing import List
from dbr import *

# you can change the following variables' value to your own value.
license_key = "Input your own license"
#license_server = "Input the name/IP of the license server"
json_file = r"Please input your own template path"
image_folder = r"Please input your own image folder path"

reader = BarcodeReader()

reader.init_license(license_key)
#reader.init_license_from_server(license_server, license_key)
#license_content = reader.output_license_to_string()
#reader.init_license_from_license_content(license_key, license_content)

error = reader.init_runtime_settings_with_file(json_file)
if error[0] != EnumErrorCode.DBR_OK:
    print(error[1])

for idx, img in enumerate(glob.glob(os.path.join(image_folder, "*.*"))):
    print(img)
    print('Test', idx+1)
    print(40*'#')

    try:
        text_results = reader.decode_file(img)
# if your python version is equal to or higher than python3.6, you can use the following code to replace the above code
        text_results:List[TextResult] = reader.decode_file(img)

        if text_results != None:
            for text_result in text_results:
                print("Barcode Format :")
                print(text_result.barcode_format_string)
                print("Barcode Text :")
                print(text_result.barcode_text)
                print("Localization Points : ")
                print(text_result.localization_result.localization_points)
                print("-------------")
    except BarcodeReaderError as bre:
        print(bre)
        
    print(40*'#')



