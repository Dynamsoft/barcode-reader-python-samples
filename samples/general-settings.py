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
        reader = BarcodeReader()

        # There are two ways to configure runtime parameters. One is through PublicRuntimeSettings, the other is through parameters template.
        # 3. General settings (including barcode format, barcode count and scan region) through PublicRuntimeSettings
        # 3.1 Obtain current runtime settings of instance.
        settings = reader.get_runtime_settings()
        
        # 3.2 Set the expected barcode format you want to read.
        # The barcode format our library will search for is composed of BarcodeFormat group 1 and BarcodeFormat group 2.
        # So you need to specify the barcode format in group 1 and group 2 individually.
        settings.barcode_format_ids = EnumBarcodeFormat.BF_ALL
        settings.barcode_format_ids_2 = EnumBarcodeFormat.BF2_POSTALCODE | EnumBarcodeFormat_2.BF2_DOTCODE
        
        # 3.3 Set the expected barcode count you want to read. 
        settings.expected_barcodes_count = 10
        
        # 3.4 Set the ROI(region of interest) to speed up the barcode reading process. 
        # Note: DBR supports setting coordinates by pixels or percentages. The origin of the coordinate system is the upper left corner point.
        settings.region_measured_by_percentage = 1
        settings.region_left = 0
        settings.region_right = 100
        settings.region_top = 0
        settings.region_bottom = 100
        
        # 3.5 Apply the new settings to the instance
        reader.update_runtime_settings(settings)

        # 3. General settings (including barcode format, barcode count and scan region) through parameters template.
        # reader.init_runtime_settings_with_string("{\"ImageParameter\":{\"BarcodeFormatIds\":[\"BF_ONED\",\"BF_PDF417\",\"BF_QR_CODE\",\"BF_DATAMATRIX\"],\"BarcodeFormatIds_2\":null,\"ExpectedBarcodesCount\":10,\"Name\":\"sts\",\"RegionDefinitionNameArray\":[\"region0\"]},\"RegionDefinition\":{\"Bottom\":100,\"Left\":0,\"MeasuredByPercentage\":1,\"Name\":\"region0\",\"Right\":100,\"Top\":0}}")

        # Replace by your own image path
        image_path = os.path.dirname(os.path.abspath(__file__)) + os.path.sep + "../images/AllSupportedBarcodeTypes.png"

        # 4.Decode barcodes from an image file.
        results = reader.decode_file(image_path)

        # 5.Output the barcode text.
        if results != None:
            i = 0
            for res in results:
                print("Barcode " + str(i))
                print("Barcode Format : " + text_result.barcode_format_string)
                print("Barcode Text : " + text_result.barcode_text)
                i = i+1
        else:
            print("No data detected.")
        
        # 6.Release resource
        del reader
        
    except BarcodeReaderError as bre:
        print(bre)
