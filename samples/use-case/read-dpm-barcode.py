import os
import sys
from dbr import *

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
        # You can also request a 30-day trial license in the customer portal: https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
        error = BarcodeReader.init_license("DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9")
        if error[0] != EnumErrorCode.DBR_OK:
            print("License error: "+ error[1])

        # 2.Create an instance of Barcode Reader.
        dbr = BarcodeReader()

        # 3.Config runtime settings for dmp
        sts = dbr.get_runtime_settings()
        
        # 3.1. Set expected barcode formats. 
        # Generally, the most common dpm barcode is datamatrix or qrcode
        sts.barcode_format_ids = EnumBarcodeFormat.BF_DATAMATRIX | EnumBarcodeFormat.BF_QR_CODE

        # 3.2. Set grayscale transformation modes.
        # DPM barcodes may be dark and printed on the light background, or it may be light and printed on the dark background.
        # By default, the library can only locate the dark barcodes that stand on a light background. "GTM_INVERTED":The image will be transformed into inverted grayscale.
        sts.grayscale_transformation_modes = [EnumGrayscaleTransformationMode.GTM_ORIGINAL,EnumGrayscaleTransformationMode.GTM_INVERTED,0,0,0,0,0,0]

        # 3.3. Enable dpm modes.
        # It is a parameter to control how to read direct part mark (DPM) barcodes.
        sts.dpm_code_reading_modes = [EnumDPMCodeReadingMode.DPMCRM_GENERAL,0,0,0,0,0,0,0]

        dbr.update_runtime_settings(sts)

        # Replace with your own dpm barcode image path
        image_path = os.path.dirname(os.path.abspath(__file__)) + os.path.sep + "../../images/dpm.jpg"

        # 3 Decode barcodes from an image file by current runtime settings. The second parameter value "" means to decode through the current PublicRuntimeSettings.
        results = dbr.decode_file(image_path,"")
        
        # 4 Output the barcode format and barcode text.
        output_results(results)
        
            
    except BarcodeReaderError as bre:
        print(bre)