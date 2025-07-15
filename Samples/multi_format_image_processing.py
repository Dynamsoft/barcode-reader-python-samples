from dynamsoft_barcode_reader_bundle import *
import cv2
from PIL import Image
import numpy as np
if __name__ == "__main__":
    try:
        # 1.Initialize license.
        # The string "DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9" here is a free public trial license. Note that network connection is required for this license to work.
        # You can also request a 30-day trial license in the customer portal: https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
        err_code, err_str = LicenseManager.init_license("DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9")
        if err_code != EnumErrorCode.EC_OK and err_code != EnumErrorCode.EC_LICENSE_WARNING:
            print("License initialization failed: ErrorCode:", err_code, ", ErrorString:", err_str)
        else:
            # 2. Create an instance of CaptureVisionRouter.
            cvr_instance = CaptureVisionRouter()
            options = [
                "exit program",
                "decode with file",
                "decode with buffer",
                "decode with bytes",
                "decode with opencv",
                "decode with PIL",
            ]
            file_path = "../images/GeneralBarcodes.png"
            while True:
                # 3. Choose decode mode.
                for i, option in enumerate(options):
                    print(f"{i}. {option}")
                choice = input("Enter your choice: ")
                if not choice.isdigit() or int(choice) >= len(options) or int(choice) < 0:
                    print("Unsupported options.")
                    continue
                if int(choice) == 0:
                    break
                elif int(choice) == 1:
                    #decode image with file path.
                    image_data = file_path
                elif int(choice) == 2:
                    #decode image with dynamsoft_barcode_reader_bundle.core.ImageData
                    image_io = ImageIO()
                    err, image_data = image_io.read_from_file(file_path)
                elif int(choice) == 3:
                    #decode image with bytes
                    image_data = open(file_path, "rb").read()
                elif int(choice) == 4:
                    #decode image with opencv
                    image_data = cv2.imread(file_path)
                elif int(choice) == 5:
                    #decode image with PIL
                    image = Image.open(file_path)
                    image_data = np.array(image)
                else:
                    raise ValueError("An unexpected value.")

                # 4. Decode barcodes from the image.
                captured_result = cvr_instance.capture(image_data,EnumPresetTemplate.PT_READ_BARCODES)

                # 5. Output the barcode result.
                if captured_result.get_error_code() == EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
                    print("Warning:", captured_result.get_error_code(), captured_result.get_error_string())
                elif captured_result.get_error_code() != EnumErrorCode.EC_OK:
                    print("Error:", captured_result.get_error_code(), captured_result.get_error_string())

                barcode_result = captured_result.get_decoded_barcodes_result()
                if barcode_result is None or barcode_result.get_items() == 0:
                    print("No barcode detected.")
                else:
                    items = barcode_result.get_items()
                    print("Decoded", len(items), "barcodes.")
                    for index,item in enumerate(items):
                        print("Result", index+1)
                        print("Barcode Format:", item.get_format_string())
                        print("Barcode Text:", item.get_text())

                print()
    except Exception as e:
        print(e)
    input("Press Enter to quit...")

