from dynamsoft_barcode_reader_bundle import *
import os
if __name__ == '__main__':
    # 1. Initialize license.
    # You can request and extend a trial license from https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
    # The string 'DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9' here is a free public trial license. Note that network connection is required for this license to work.
    errorCode, errorMsg = LicenseManager.init_license("DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9")
    if errorCode != EnumErrorCode.EC_OK and errorCode != EnumErrorCode.EC_LICENSE_WARNING:
        print("License initialization failed: ErrorCode:", errorCode, ", ErrorString:", errorMsg)
    else:
        # 2. Create an instance of CaptureVisionRouter.
        cvr_instance = CaptureVisionRouter()

        # 3. Replace by your own image path.
        image_path = os.path.dirname(os.path.abspath(__file__)) + os.path.sep + "../images/GeneralBarcodes.png"

        # 4. Decode barcodes from an image file.
        result_array = cvr_instance.capture_multi_pages(image_path, EnumPresetTemplate.PT_READ_BARCODES)

        # 5. Output the barcode text.
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
                        print("Result", index+1)
                        print("Barcode Format:", item.get_format_string())
                        print("Barcode Text:", item.get_text())
                print()
    input("Press Enter to quit...")