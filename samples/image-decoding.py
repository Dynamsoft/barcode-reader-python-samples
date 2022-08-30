import os
import sys
from dbr import *
import cv2 

def choose_number() -> int: 
    print()
    print(">> Choose a number for different decoding interfaces:")
    print("   0: exit program")
    print("   1: decode_file")
    print("   2: decode_file_stream")
    print("   3: decode_buffer")
    print("   4: decode_buffer_manually")
    
    choose_num = -1
    line = sys.stdin.readline()

    try:
        choose_num = int(line)
    except Exception as exp:
        print(exp)

    return choose_num

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

        while True:
            while True:
                num = choose_number()
                if num < 0 or num > 4:
                    print("Please choose a valid number.")
                else:
                    break

            results = None

            # 3.Decode barcodes from an image file.
            if num == 0:
                # exit program
                break 
            elif num == 1:
                # 3.1 Decoding with file
                results = dbr.decode_file(image_path)
            elif num == 2:
                # 3.2 Decoding with file bytes array
                with open(image_path,"rb") as f:
                    bytes = f.read()

                results = dbr.decode_file_stream(bytearray(bytes))
            elif num == 3:
                # 3.3 Decoding with opencv image
                cv_buffer = cv2.imread(image_path)

                results = dbr.decode_buffer(cv_buffer)
            elif num == 4:
                # 3.4 Decoding with buffer manually
                cv_buffer = cv2.imread(image_path)
                buffer = cv_buffer.tobytes()
                height = cv_buffer.shape[0]
                width = cv_buffer.shape[1]
                stride = cv_buffer.strides[0]

                results = dbr.decode_buffer_manually(buffer, width, height, stride, EnumImagePixelFormat.IPF_RGB_888)
            else:
                break
            
            # 4.Output the barcode text.
            if results != None:
                i = 0
                for res in results:
                    barcode_format = res.barcode_format_string

                    print("Barcode " + str(i) + ":" + barcode_format + "," + res.barcode_text)
                    i = i+1
            else:
                print("No data detected.")
            
    except BarcodeReaderError as bre:
        print(bre)