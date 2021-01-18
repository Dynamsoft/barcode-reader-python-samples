# -*-coding:utf-8-*-

import os
import sys
import json
import time
import glob
from dbr import *

reader = BarcodeReader()

Barcode_Format_Dict = {
    '1': (EnumBarcodeFormat.BF_ALL, EnumBarcodeFormat_2.BF2_POSTALCODE | EnumBarcodeFormat_2.BF2_DOTCODE),
    '2': (EnumBarcodeFormat.BF_ONED, EnumBarcodeFormat_2.BF2_NULL),
    '3': (EnumBarcodeFormat.BF_QR_CODE, EnumBarcodeFormat_2.BF2_NULL),
    '4': (EnumBarcodeFormat.BF_CODE_39, EnumBarcodeFormat_2.BF2_NULL),
    '5': (EnumBarcodeFormat.BF_CODE_128, EnumBarcodeFormat_2.BF2_NULL),
    '6': (EnumBarcodeFormat.BF_CODE_93, EnumBarcodeFormat_2.BF2_NULL),
    '7': (EnumBarcodeFormat.BF_CODABAR, EnumBarcodeFormat_2.BF2_NULL),
    '8': (EnumBarcodeFormat.BF_ITF, EnumBarcodeFormat_2.BF2_NULL),
    '9': (EnumBarcodeFormat.BF_INDUSTRIAL_25, EnumBarcodeFormat_2.BF2_NULL),
    '10': (EnumBarcodeFormat.BF_EAN_13, EnumBarcodeFormat_2.BF2_NULL),
    '11': (EnumBarcodeFormat.BF_EAN_8, EnumBarcodeFormat_2.BF2_NULL),
    '12': (EnumBarcodeFormat.BF_UPC_A, EnumBarcodeFormat_2.BF2_NULL),
    '13': (EnumBarcodeFormat.BF_UPC_E, EnumBarcodeFormat_2.BF2_NULL),
    '14': (EnumBarcodeFormat.BF_PDF417, EnumBarcodeFormat_2.BF2_NULL),
    '15': (EnumBarcodeFormat.BF_DATAMATRIX, EnumBarcodeFormat_2.BF2_NULL),
    '16': (EnumBarcodeFormat.BF_AZTEC, EnumBarcodeFormat_2.BF2_NULL),
    '17': (EnumBarcodeFormat.BF_CODE_39_EXTENDED, EnumBarcodeFormat_2.BF2_NULL),
    '18': (EnumBarcodeFormat.BF_MAXICODE, EnumBarcodeFormat_2.BF2_NULL),
    '19': (EnumBarcodeFormat.BF_GS1_DATABAR, EnumBarcodeFormat_2.BF2_NULL),
    '20': (EnumBarcodeFormat.BF_PATCHCODE, EnumBarcodeFormat_2.BF2_NULL),
    '21': (EnumBarcodeFormat.BF_GS1_COMPOSITE, EnumBarcodeFormat_2.BF2_NULL),
    '22': (EnumBarcodeFormat.BF_NULL, EnumBarcodeFormat_2.BF2_POSTALCODE),
    '23': (EnumBarcodeFormat.BF_NULL, EnumBarcodeFormat_2.BF2_DOTCODE)
}

Template_Settings = {
    '1': '{"ImageParameter":{'
            '"Name":"BestCoverage",'
            '"DeblurLevel":9,'
            '"ExpectedBarcodesCount":512,'
            '"ScaleDownThreshold":100000,'
            '"LocalizationModes":['
                 '{"Mode":"LM_CONNECTED_BLOCKS"},'
                 '{"Mode":"LM_SCAN_DIRECTLY"},'
                 '{"Mode":"LM_STATISTICS"},'
                 '{"Mode":"LM_LINES"},'
                 '{"Mode":"LM_STATISTICS_MARKS"}],'
            '"GrayscaleTransformationModes":['
                 '{"Mode":"GTM_ORIGINAL"},'
                 '{"Mode":"GTM_INVERTED"}]'
            '}'
        '}',
    '2': '{"ImageParameter":{'
            '"Name":"BestSpeed",'
            '"DeblurLevel":3,'
            '"ExpectedBarcodesCount":512,'
            '"LocalizationModes":['
                '{"Mode":"LM_SCAN_DIRECTLY"}],'
            '"TextFilterModes":['
                '{"MinImageDimension":262144,"Mode":"TFM_GENERAL_CONTOUR"}]'
            '}'
        '}',
    '3': '{"ImageParameter":{'
            '"Name":"Balance",'
            '"DeblurLevel":5,'
            '"ExpectedBarcodesCount":512,'
            '"LocalizationModes":['
                '{"Mode":"LM_CONNECTED_BLOCKS"},'
                '{"Mode":"LM_STATISTICS"}]'
            '}'
        '}'
}


def init_runtime_settings():
    while True:
        print()
        print("Step 2: Choose a template settings : ")
        print("\t 1: Best Coverage Settings")
        print("\t 2: Best Speed Settings")
        print("\t 3: Balance Settings")
        item = input()

        if str(item) == 'q' or str(item) == 'Q':
            print('Bye, looking forward to your next use.')
            exit()

        if str(item) not in Template_Settings.keys():
            print('Please choose a valid number.')
            continue
        else:
            reader.init_runtime_settings_with_string(Template_Settings[item])
            break


def set_barcode_format():
    while True:
        print()
        print("Step 3: Choose a number for the format(s) of your barcode image: ")
        print("\t 1: All")
        print("\t 2: OneD")
        print("\t 3: QR Code")
        print("\t 4: Code 39")
        print("\t 5: Code 128")
        print("\t 6: Code 93")
        print("\t 7: Codabar")
        print("\t 8: Interleaved 2 of 5")
        print("\t 9: Industrial 2 of 5")
        print("\t 10: EAN-13")
        print("\t 11: EAN-8")
        print("\t 12: UPC-A")
        print("\t 13: UPC-E")
        print("\t 14: PDF417")
        print("\t 15: DATAMATRIX")
        print("\t 16: AZTEC")
        print("\t 17: Code 39 Extended")
        print("\t 18: Maxicode")
        print("\t 19: GS1 Databar")
        print("\t 20: PatchCode")
        print("\t 21: GS1 Composite")
        print("\t 22: Postal  Code")
        print("\t 23: DotCode")
        item = input()

        if str(item) == 'q' or str(item) == 'Q':
            print('Bye, looking forward to your next use.')
            exit()

        if str(item) not in Barcode_Format_Dict.keys():
            print('Please choose a valid number.')
            continue
        else:
            settings = reader.get_runtime_settings()
            settings.barcode_format_ids = Barcode_Format_Dict[item][0]
            settings.barcode_format_ids_2 = Barcode_Format_Dict[item][1]
            reader.update_runtime_settings(settings)
            break
    

def decode_file(path):
    try:
        start_time = time.time()
        text_results = reader.decode_file(path)
        end_time = time.time()

        spend_time = (end_time - start_time)*1000

        if text_results is not None:
            print('Total barcode(s) found : {0}. Total time spent: {1} ms.'.format(len(text_results), spend_time))
            i = 1
            for text_result in text_results:
                print("-------------")
                print('Barcode {0}'.format(i))
                print("Barcode Format : ")
                print(text_result.barcode_format_string)
                print("Barcode Text : ")
                print(text_result.barcode_text)
                print("Barcode Bytes : ")
                print(text_result.barcode_bytes)
                print("Localization Points : ")
                print(text_result.localization_result.localization_points)
                print("Exception : ")
                print(text_result.exception)
                print("-------------")
                i = i + 1
        else:
            print("-------------")
            print("No barcode found. Total time spent: {0} ms.".format(spend_time))
            print("-------------")
    except BarcodeReaderError as bre:
        print(bre)


def decode_files(path):
    for idx, img in enumerate(glob.glob(os.path.join(path, "*.*"))):
        print('Image', idx + 1)
        print(img)
        print(40 * '#')
        decode_file(img)
        print(40 * '#')


if __name__ == '__main__':

    license_key = "Input your own license"

    # Apply for a trial license: https://www.dynamsoft.com/CustomerPortal/Portal/Triallicense.aspx
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

    print("*************************************************")
    print("Welcome to Dynamsoft Barcode Reader Demo")
    print("*************************************************")
    print("Hints: Please input 'Q'or 'q' to quit the application.")
    print()
    while True:
        path = input("Step 1: Input your image path or folder path:")
        if path == 'q' or path == 'Q':
            print('Bye, looking forward to your next use.')
            exit()
        if not os.path.exists(path):
            print("The picture or folder path doesn't exist , please input a valid path.")
            continue

        init_runtime_settings()

        set_barcode_format()

        if os.path.isdir(path):
            decode_files(path)
        elif os.path.isfile(path):
            decode_file(path)
        else:
            print("The path is invalid , please input a valid path.")
            continue
