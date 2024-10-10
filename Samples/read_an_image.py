from dynamsoft_barcode_reader_bundle import *
import os

if __name__ == '__main__':
    # Initialize license.
    # You can request and extend a trial license from https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
    # The string 'DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9' here is a free public trial license. Note that network connection is required for this license to work.
    errorCode, errorMsg = LicenseManager.init_license("DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9")
    if errorCode != EnumErrorCode.EC_OK and errorCode != EnumErrorCode.EC_LICENSE_CACHE_USED:
        print("License initialization failed: ErrorCode:", errorCode, ", ErrorString:", errorMsg)
    else:
        cvr = CaptureVisionRouter()
        result = cvr.capture("../Images/GeneralBarcodes.png", EnumPresetTemplate.PT_READ_BARCODES.value)
        if result.get_error_code() != EnumErrorCode.EC_OK:
            print("Error:", result.get_error_code(), result.get_error_string())
        barcode_result = result.get_decoded_barcodes_result()
        if barcode_result is None or barcode_result.get_items() == 0:
            print("No barcode detected.")
        else:
            items = barcode_result.get_items()
            print("Decoded", len(items), "barcodes.")
            for index,item in enumerate(items):
                print("Result", index+1)
                print("Barcode Format:", item.get_format_string())
                print("Barcode Text:", item.get_text())
    input("Press Enter to quit...")