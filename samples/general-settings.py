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

        # There are two ways to configure runtime parameters. One is through PublicRuntimeSettings, the other is through parameters template.
        # 3. General settings (including barcode format, barcode count and scan region) through PublicRuntimeSettings
        # 3.1 Obtain current runtime settings of instance.
        sts = dbr.get_runtime_settings()
        
        # 3.2 Set the expected barcode format you want to read.
        # The barcode format our library will search for is composed of BarcodeFormat group 1 and BarcodeFormat group 2.
        # So you need to specify the barcode format in group 1 and group 2 individually.
        sts.barcode_format_ids = EnumBarcodeFormat.BF_ONED | EnumBarcodeFormat.BF_QR_CODE | EnumBarcodeFormat.BF_PDF417 | EnumBarcodeFormat.BF_DATAMATRIX
        sts.barcode_format_ids_2 = EnumBarcodeFormat.BF_NULL
        
        # 3.3 Set the expected barcode count you want to read. 
        sts.expected_barcodes_count = 10
        
        # 3.4 Set the ROI(region of interest) to speed up the barcode reading process. 
        # Note: DBR supports setting coordinates by pixels or percentages. The origin of the coordinate system is the upper left corner point.
        sts.region_measured_by_percentage = 1
        sts.region_left = 0
        sts.region_right = 100
        sts.region_top = 0
        sts.region_bottom = 100
        
        # 3.5 Apply the new settings to the instance
        dbr.update_runtime_settings(sts)

        # 3. General settings (including barcode format, barcode count and scan region) through parameters template.
        # dbr.init_runtime_settings_with_string("{\"ImageParameter\":{\"BarcodeFormatIds\":[\"BF_ONED\",\"BF_PDF417\",\"BF_QR_CODE\",\"BF_DATAMATRIX\"],\"BarcodeFormatIds_2\":null,\"ExpectedBarcodesCount\":10,\"Name\":\"sts\",\"RegionDefinitionNameArray\":[\"region0\"]},\"RegionDefinition\":{\"Bottom\":100,\"Left\":0,\"MeasuredByPercentage\":1,\"Name\":\"region0\",\"Right\":100,\"Top\":0}}")

        # Replace by your own image path
        image_path = os.path.dirname(os.path.abspath(__file__)) + os.path.sep + "../images/AllSupportedBarcodeTypes.png"

        # 4.Decode barcodes from an image file.
        results = dbr.decode_file(image_path)

        # 5.Output the barcode text.
        if results != None:
            i = 0
            for res in results:
                barcode_format = res.barcode_format_string_2 if res.barcode_format==0 else res.barcode_format_string

                print("Barcode " + str(i) + ":" + barcode_format + "," + res.barcode_text)
                i = i+1
        else:
            print("No data detected.")
    except BarcodeReaderError as bre:
        print(bre)