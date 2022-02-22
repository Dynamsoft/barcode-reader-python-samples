import os
from dbr import *

def config_speed_first(dbr:BarcodeReader):

    # Obtain current runtime settings of instance.
    sts = dbr.get_runtime_settings()
    
    # Parameter 1. Set expected barcode formats
    # The simpler barcode format, the faster decoding speed.
    # Here we use OneD barcode format to demonstrate.
    sts.barcode_format_ids = EnumBarcodeFormat.BF_EAN_13
    
    # Parameter 2. Set expected barcode count
    # The less barcode count, the faster decoding speed.
    sts.expected_barcodes_count = 1

    # Parameter 3. Set the threshold for the image shrinking for localization.
    # The smaller the threshold, the smaller the image shrinks.  The default value is 2300.
    sts.scale_down_threshold = 1200

    # Parameter 4. Set the binarization mode for convert grayscale image to binary image.
    # Mostly, the less binarization modes set, the faster decoding speed.
    sts.binarization_modes = [EnumBinarizationMode.BM_LOCAL_BLOCK,0,0,0,0,0,0,0]

    # Parameter 5. Set localization mode.
    # LM_SCAN_DIRECTLY: Localizes barcodes quickly. It is both for OneD and TweD barcodes. This mode is recommended in interactive scenario.
    sts.localization_modes = [EnumLocalizationMode.LM_SCAN_DIRECTLY,0,0,0,0,0,0,0]

    # LM_ONED_FAST_SCAN: Localizing barcodes quickly. However, it is only for OneD barcodes. It is also recommended in interactive scenario.
    # sts.localization_modes = [EnumLocalizationMode.LM_ONED_FAST_SCAN, 0,0,0,0,0,0,0]
    
    # Parameter 6. Reduce deblurModes setting
    # DeblurModes will improve the readability and accuracy but decrease the reading speed.
    # Please update your settings here if you want to enable different Deblurmodes.
    sts.deblur_modes = [EnumDeblurMode.DM_BASED_ON_LOC_BIN,EnumDeblurMode.DM_THRESHOLD_BINARIZATION,0,0,0,0,0,0,0,0]

    # Parameter 7. Set timeout(ms) if the application is very time sensitive.
    # If timeout, the decoding thread will exit at the next check point.
    sts.timeout = 100

    # Apply the new settings to the instance
    dbr.update_runtime_settings(sts)

    # Other potentially accelerated arguments of various modes.

    # Argument 4.a Disable the EnableFillBinaryVacancy argument.
    # Local block binarization process might cause vacant area in barcode. The barcode reader will fill the vacant black by default (default value 1). Set the value 0 to disable this process.
    dbr.set_mode_argument("BinarizationModes", 0, "EnableFillBinaryVacancy", "0")

    # Argument 5.a Sets the scan direction when searching barcode.
    # It is valid only when the type of LocalizationMode is LM_ONED_FAST_SCAN or LM_SCAN_DIRECTLY.
    # 0: Both vertical and horizontal direction.
    # 1: Vertical direction.
    # 2: Horizontal direction.
    # Read more about localization mode members: https://www.dynamsoft.com/barcode-reader/parameters/enum/parameter-mode-enums.html?ver=latest#localizationmode
    dbr.set_mode_argument("LocalizationModes",0,"ScanDirection","0")
    

def config_speed_first_by_template(dbr:BarcodeReader):
    # Compared with PublicRuntimeSettings, parameter templates have a richer ability to control parameter details.
    # Please refer to the parameter explanation in "speed-first-template.json" to understand how to control speed first.
    template_path = os.path.dirname(os.path.abspath(__file__)) + os.path.sep + "speed-first-template.json"
    error = dbr.init_runtime_settings_with_file(template_path, EnumConflictMode.CM_OVERWRITE)
    if error[0] != EnumErrorCode.DBR_OK:
        print("init_runtime_settings_with_file error: " + error[1])

def output_results(results:TextResult):
    if results != None:
        i = 0
        for res in results:
            barcode_format = res.barcode_format_string_2 if res.barcode_format==0 else res.barcode_format_string

            print("Barcode " + str(i) + ":" + barcode_format + "," + res.barcode_text)
            i = i+1
    else:
        print("No data detected.")


if __name__ == "__main__":
    try:
        # 1.Initialize license.
        # The organization id 200001 here will grant you a free public trial license. Note that network connection is required for this license to work.
        # If you want to use an offline license, please contact Dynamsoft Support: https://www.dynamsoft.com/company/contact/
        # You can also request a 30-day trial license in the customer portal: https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
        para = BarcodeReader.init_dls_connection_parameters()
        para.organization_id = "200001"
        error = BarcodeReader.init_license_from_dls(para)
        if error[0] != EnumErrorCode.DBR_OK:
            print("License error: "+ error[1])

        # 2.Create an instance of Barcode Reader.
        dbr = BarcodeReader()

        # Replace by your own image path
        image_path = os.path.dirname(os.path.abspath(__file__)) + os.path.sep + "../../images/AllSupportedBarcodeTypes.png"

        # Accuracy = The number of correctly decoded barcodes/the number of all decoded barcodes
        # There are two ways to configure runtime parameters. One is through PublicRuntimeSettings, the other is through parameters template.
        print("Decode through PublicRuntimeSettings:")

        # 3.a config through PublicRuntimeSettings
        config_speed_first(dbr)
        
        # 4.a Decode barcodes from an image file by current runtime settings. The second parameter value "" means to decode through the current PublicRuntimeSettings.
        results = dbr.decode_file(image_path,"")
        
        # 5.a Output the barcode format and barcode text.
        output_results(results)
        
        print("\nDecode through parameters template:")
        
        # 3.b config through parameters template
        config_speed_first_by_template(dbr)
        
        # 4.b Decode barcodes from an image file by template. 
        results = dbr.decode_file(image_path, "")
        
        # 5.b Output the barcode format and barcode text.
        output_results(results)
            
    except BarcodeReaderError as bre:
        print(bre)