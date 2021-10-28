import os
import glob
from dbr import *


if __name__ == "__main__":
    try:
        # 1.Initialize license.
        # The organization id 200001 here will grant you a public trial license good for 7 days. Note that network connection is required for this license to work.
        # If you want to use an offline license, please contact Dynamsoft Support: https://www.dynamsoft.com/company/contact/
        # You can also request a 30-day trial license in the customer portal: https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
        para = BarcodeReader.init_dls_connection_parameters()
        para.organization_id = "200001"
        error = BarcodeReader.init_license_from_dls(para)
        if error[0] != EnumErrorCode.DBR_OK:
            print("License error: "+ error[1])

        # 2.Create an instance of Barcode Reader.
        reader = BarcodeReader()

        # Replace by your own image path
        image_folder = os.path.dirname(os.path.abspath(__file__)) + os.path.sep + "../../images"

        for idx, img in enumerate(glob.glob(os.path.join(image_folder, "*.*"))):
            print('Test', idx+1, img)

            # 3. Decode barcodes from an image file
            text_results = reader.decode_file(img)

            # 4.Output the barcode text.
            if text_results != None:
                for text_result in text_results:
                    print("Barcode Format : ", text_result.barcode_format_string)
                    print("Barcode Text : ", text_result.barcode_text)
                    print("Localization Points : ", text_result.localization_result.localization_points)
                    print("Exception : ", text_result.exception)
                    print("-------------")
                
            print(40*'#')

    except BarcodeReaderError as bre:
        print(bre)