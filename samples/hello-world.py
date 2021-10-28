import os
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