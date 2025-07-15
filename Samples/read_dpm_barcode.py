import os
from dynamsoft_barcode_reader_bundle import *

if __name__ == "__main__":
    try:
        # 1 Initialize license.
        # The string "DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9" here is a free public trial license. Note that network connection is required for this license to work.
        # You can also request a 30-day trial license in the customer portal: https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
        errorCode, errorMsg = LicenseManager.init_license("DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9")
        if errorCode != EnumErrorCode.EC_OK and errorCode != EnumErrorCode.EC_LICENSE_WARNING:
            raise Exception("License initialization failed: ErrorCode: "+ str(errorCode) + ", ErrorString:" + errorMsg)
        else:
            cvr_instance = CaptureVisionRouter()
            template_path = os.path.dirname(os.path.abspath(__file__)) + os.path.sep +"ReadDPM.json"
            errorCode, errorMsg = cvr_instance.init_settings_from_file(template_path)
            if errorCode != EnumErrorCode.EC_OK:
                raise Exception("Init template failed: " + errorMsg)

            # 2 Replace with your own dpm barcode image path
            image_path = os.path.dirname(os.path.abspath(__file__)) + os.path.sep + "../images/DPM.png"

            # 3 Decode barcodes from the image file.
            result_array = cvr_instance.capture_multi_pages(image_path,"")

            # 4 Output the barcode format and barcode text.
            results = result_array.get_results()
            if results is None or len(results) == 0:
                print("No barcode detected.")
            else:
                for i, result in enumerate(results):
                    if result.get_error_code() == EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
                        print("Warning:", result.get_error_code(), result.get_error_string())
                    elif result.get_error_code() != EnumErrorCode.EC_OK:
                        print("Error:", result.get_error_code(), result.get_error_string())

                    barcode_result = result.get_decoded_barcodes_result()
                    if barcode_result is None or barcode_result.get_items() == 0:
                        print("Page-"+str(i+1), "No barcode detected.")
                    else:
                        items = barcode_result.get_items()
                        print("Page-"+str(i+1), "Decoded", len(items), "barcodes.")
                        for index,item in enumerate(items):
                            print()
                            print("Barcode", index)
                            print("Barcode Format:", item.get_format_string())
                            print("Barcode Text:", item.get_text())
                    print()
    except Exception as e:
        print(e)