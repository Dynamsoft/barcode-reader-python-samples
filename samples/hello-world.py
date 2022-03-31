import os
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
        dbr = BarcodeReader()

        # Replace by your own image path
        image_path = os.path.dirname(os.path.abspath(__file__)) + os.path.sep + "../images/AllSupportedBarcodeTypes.png"

        # 3.Decode barcodes from an image file.
        results = dbr.decode_file(image_path)

        # 4.Output the barcode text.
        if results != None:
            i = 0
            for res in results:
                print("Barcode " + str(i) + ":" + res.barcode_text)
                i = i+1
        else:
            print("No data detected.")
    except BarcodeReaderError as bre:
        print(bre)