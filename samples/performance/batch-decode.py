import os
import glob
from dbr import *


if __name__ == "__main__":
    try:
        # 1.Initialize license.
        # The string "DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9" here is a free public trial license. Note that network connection is required for this license to work.
        # You can also request a 30-day trial license in the customer portal: https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
        error = BarcodeReader.init_license("DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9")
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