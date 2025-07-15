import os
from dynamsoft_barcode_reader_bundle import *
if __name__ == "__main__":
    try:
        # 1. Initialize license.
        # The string "DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9" here is a free public trial license. Note that network connection is required for this license to work.
        # You can also request a 30-day trial license in the customer portal: https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
        err_code, err_str = LicenseManager.init_license("DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9")
        if err_code != EnumErrorCode.EC_OK and err_code != EnumErrorCode.EC_LICENSE_WARNING:
            print("License initialization failed: ErrorCode:", err_code, ", ErrorString:", err_str)
        else:
            # 2. Create an instance of CaptureVisionRouter.
            cvr_instance = CaptureVisionRouter()

            # 3. General settings (including barcode format, barcode count and scan region) through SimplifiedCaptureVisionSettings
            # 3.1 Obtain current runtime settings of instance.
            err_code, err_str, settings = cvr_instance.get_simplified_settings(EnumPresetTemplate.PT_READ_BARCODES)

            # 3.2 Set the expected barcode format you want to read.
            settings.barcode_settings.barcode_format_ids = EnumBarcodeFormat.BF_PDF417 | EnumBarcodeFormat.BF_QR_CODE

            # 3.3 Set the expected barcode count you want to read.
            settings.barcode_settings.expected_barcodes_count = 10

            # 3.4 Set the grayscale transformation modes.
            settings.barcode_settings.grayscale_transformation_modes[0] = EnumGrayscaleTransformationMode.GTM_AUTO

            # 3.5 Set the ROI(region of interest) to speed up the barcode reading process.
            # Note: DBR supports setting coordinates by pixels or percentages. The origin of the coordinate system is the upper left corner point.
            settings.roi_measured_in_percentage = 1
            points = settings.roi.points
            points[0].x = 0
            points[0].y = 0
            points[1].x = 100
            points[1].y = 0
            points[2].x = 100
            points[2].y = 100
            points[3].x = 0
            points[3].y = 100

            # 3.6 Apply the new settings to the instance.
            err_code, err_str = cvr_instance.update_settings(EnumPresetTemplate.PT_READ_BARCODES, settings)
            if err_code != EnumErrorCode.EC_OK:
                print("Update settings failed: ErrorCode:", err_code, ", ErrorString:", err_str)
            # 4.Replace by your own image path
            image_path = os.path.dirname(os.path.abspath(__file__)) + os.path.sep + "../images/GeneralBarcodes.png"

            # 5.Decode barcodes from an image file.
            result_array = cvr_instance.capture_multi_pages(image_path, EnumPresetTemplate.PT_READ_BARCODES)

            # 6.Output the barcode text.
            results = result_array.get_results()
            if results is None or len(results) == 0:
                print("No barcode detected.")
            else:
                for result in results:
                    if result.get_error_code() == EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
                        print("Warning:", result.get_error_code(), result.get_error_string())
                    elif result.get_error_code() != EnumErrorCode.EC_OK:
                        print("Error:", result.get_error_code(), result.get_error_string())

                    barcode_result = result.get_decoded_barcodes_result()
                    if barcode_result is None or barcode_result.get_items() == 0:
                        print("No barcode detected.")
                    else:
                        items = barcode_result.get_items()
                        print("Decoded", len(items), "barcodes.")
                        for index,item in enumerate(items):
                            print()
                            print("Barcode", index)
                            print("Barcode Format:", item.get_format_string())
                            print("Barcode Text:", item.get_text())
                    print()
    except Exception as e:
        print(e)
