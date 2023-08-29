import os
from dbr import *

def config_readrate_first(dbr:BarcodeReader):

    # Obtain current runtime settings of instance.
    sts = dbr.get_runtime_settings()
    
    # Parameter 1. Set expected barcode formats
    # Here the barcode scanner will try to find the maximal barcode formats.
    sts.barcode_format_ids = EnumBarcodeFormat.BF_ALL
    sts.barcode_format_ids_2 = EnumBarcodeFormat_2.BF2_DOTCODE | EnumBarcodeFormat_2.BF2_POSTALCODE

    # Parameter 2. Set expected barcode count.
    # Here the barcode scanner will try to find 64 barcodes.
    # If the result count does not reach the expected amount, the barcode scanner will try other algorithms in the setting list to find enough barcodes.
    sts.expected_barcodes_count = 64

    # Parameter 3. Set more binarization modes.
    sts.binarization_modes = [EnumBinarizationMode.BM_LOCAL_BLOCK,EnumBinarizationMode.BM_THRESHOLD,0,0,0,0,0,0]

    # Parameter 4. Set more localization modes.
    # LocalizationModes are all enabled as default. Barcode reader will automatically switch between the modes and try decoding continuously until timeout or the expected barcode count is reached.
    # Please manually update the enabled modes list or change the expected barcode count to promote the barcode scanning speed.
    # Read more about localization mode members: https://www.dynamsoft.com/barcode-reader/parameters/enum/parameter-mode-enums.html?ver=latest#localizationmode
    sts.localization_modes = [EnumLocalizationMode.LM_CONNECTED_BLOCKS,EnumLocalizationMode.LM_SCAN_DIRECTLY,EnumLocalizationMode.LM_STATISTICS,
            EnumLocalizationMode.LM_LINES,EnumLocalizationMode.LM_STATISTICS_MARKS,EnumLocalizationMode.LM_STATISTICS_POSTAL_CODE,0,0]

    # Parameter 5. Set more deblur modes.
    # DeblurModes are all enabled as default. Barcode reader will automatically switch between the modes and try decoding continuously until timeout or the expected barcode count is reached.
    # Please manually update the enabled modes list or change the expected barcode count to promote the barcode scanning speed.
    # Read more about deblur mode members: https://www.dynamsoft.com/barcode-reader/parameters/enum/parameter-mode-enums.html#deblurmode
    sts.deblur_modes = [EnumDeblurMode.DM_DIRECT_BINARIZATION,EnumDeblurMode.DM_THRESHOLD_BINARIZATION,EnumDeblurMode.DM_GRAY_EQUALIZATION,
            EnumDeblurMode.DM_SMOOTHING,EnumDeblurMode.DM_MORPHING,EnumDeblurMode.DM_DEEP_ANALYSIS,EnumDeblurMode.DM_SHARPENING,0,0,0]

    # Parameter 6. Set scale up modes.
    # It is a parameter to control the process for scaling up an image used for detecting barcodes with small module size
    sts.scale_up_modes = [EnumScaleUpMode.SUM_AUTO,0,0,0,0,0,0,0]

    # Parameter 7. Set grayscale transformation modes.
    # By default, the library can only locate the dark barcodes that stand on a light background. "GTM_INVERTED":The image will be transformed into inverted grayscale.
    sts.grayscale_transformation_modes = [EnumGrayscaleTransformationMode.GTM_ORIGINAL,EnumGrayscaleTransformationMode.GTM_INVERTED,0,0,0,0,0,0]

    # Parameter 8. Enable dpm modes.
    # It is a parameter to control how to read direct part mark (DPM) barcodes.
    sts.dpm_code_reading_modes = [EnumDPMCodeReadingMode.DPMCRM_GENERAL,0,0,0,0,0,0,0]

    # Parameter 9. Increase timeout(ms). The barcode scanner will have more chances to find the expected barcode until it times out
    sts.timeout = 30000
    
    # Apply the new settings to the instance
    dbr.update_runtime_settings(sts)

def config_readrate_first_by_template(dbr:BarcodeReader):
    # Compared with PublicRuntimeSettings, parameter templates have a richer ability to control parameter details.
    # Please refer to the parameter explanation in "read-rate-first-template.json" to understand how to control read rate first.
    template_path = os.path.dirname(os.path.abspath(__file__)) + os.path.sep + "read-rate-first-template.json"
    error = dbr.init_runtime_settings_with_file(template_path, EnumConflictMode.CM_OVERWRITE)
    if error[0] != EnumErrorCode.DBR_OK:
        print("init_runtime_settings_with_file error: " + error[1])

def output_results(results:TextResult):
    if results != None:
        i = 0
        for res in results:
            barcode_format = res.barcode_format_string

            print("Barcode " + str(i) + ":" + barcode_format + "," + res.barcode_text)
            i = i+1
    else:
        print("No data detected.")


if __name__ == "__main__":
    try:
        # 1.Initialize license.
        # The string "DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9" here is a free public trial license. Note that network connection is required for this license to work.
        # You can also request a 30-day trial license in the customer portal: https://www.dynamsoft.com/customer/license/trialLicense?architecture=dcv&product=dbr&utm_source=samples&package=python
        error = BarcodeReader.init_license("DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9")
        if error[0] != EnumErrorCode.DBR_OK:
            print("License error: "+ error[1])

        # 2.Create an instance of Barcode Reader.
        dbr = BarcodeReader.get_instance()
        if dbr == None :
            raise BarcodeReaderError("Get instance failed")
        # Replace by your own image path
        image_path = os.path.dirname(os.path.abspath(__file__)) + os.path.sep + "../../images/AllSupportedBarcodeTypes.png"

        # Accuracy = The number of correctly decoded barcodes/the number of all decoded barcodes
        # There are two ways to configure runtime parameters. One is through PublicRuntimeSettings, the other is through parameters template.
        print("Decode through PublicRuntimeSettings:")

        # 3.a config through PublicRuntimeSettings
        config_readrate_first(dbr)
        
        # 4.a Decode barcodes from an image file by current runtime settings. The second parameter value "" means to decode through the current PublicRuntimeSettings.
        results = dbr.decode_file(image_path,"")
        
        # 5.a Output the barcode format and barcode text.
        output_results(results)
        
        print("\nDecode through parameters template:")
        # 3.b config through parameters template
        config_readrate_first_by_template(dbr)
        
        # 4.b Decode barcodes from an image file by template. 
        results = dbr.decode_file(image_path, "")
        
        # 5.b Output the barcode format and barcode text.
        output_results(results)
        dbr.recycle_instance()
    except BarcodeReaderError as bre:
        print(bre)