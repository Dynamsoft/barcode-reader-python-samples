import os
from dbr import *

def config_accuracy_first(dbr:BarcodeReader):

    # Obtain current runtime settings of instance.
    sts = dbr.get_runtime_settings()
    
    # 1. Set expected barcode format
    # The more precise the barcode format is set, the higher the accuracy.
    # Mostly, misreading only occurs on reading oneD barcode. So here we use OneD barcode format to demonstrate.
    sts.barcode_format_ids = EnumBarcodeFormat.BF_ONED
    sts.barcode_format_ids_2 = EnumBarcodeFormat.BF_NULL
    
    # 2. Set the minimal result confidence.
    # The greater the confidence, the higher the accuracy.
    # Filter by minimal confidence of the decoded barcode. We recommend using 30 as the default minimal confidence value
    sts.minResultConfidence = 30
    
    # 3. Sets the minimum length of barcode text for filtering.
    # The more precise the barcode text length is set, the higher the accuracy.
    sts.minBarcodeTextLength = 6
    
    # Apply the new settings to the instance
    dbr.update_runtime_settings(sts)

def config_accuracy_first_by_template(dbr:BarcodeReader):
    # Compared with PublicRuntimeSettings, parameter templates have a richer ability to control parameter details.
    # Please refer to the parameter explanation in "accuracy-first-template.json" to understand how to control accuracy first.
    template_path = os.path.dirname(os.path.abspath(__file__)) + os.path.sep + "accuracy-first-template.json"
    error = dbr.init_runtime_settings_with_file(template_path, EnumConflictMode.CM_OVERWRITE)
    if error[0] != EnumErrorCode.DBR_OK:
        print("init_runtime_settings_with_file error: " + error[1])

def output_results(results:TextResult):
    if results != None:
        i = 0
        for res in results:
            barcode_format = res.barcode_format_string_2 if res.barcode_format==0 else res.barcode_format_string

            print("Barcode " + str(i) + ":" + barcode_format + "," + res.barcode_text)
            i = i+1
    else:
        print("No data detected.")


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
        image_path = os.path.dirname(os.path.abspath(__file__)) + os.path.sep + "../../images/AllSupportedBarcodeTypes.png"

        # Accuracy = The number of correctly decoded barcodes/the number of all decoded barcodes
        # There are two ways to configure runtime parameters. One is through PublicRuntimeSettings, the other is through parameters template.
        print("Decode through PublicRuntimeSettings:")

        # 3.a config through PublicRuntimeSettings
        config_accuracy_first(dbr)
        
        # 4.a Decode barcodes from an image file by current runtime settings. The second parameter value "" means to decode through the current PublicRuntimeSettings.
        results = dbr.decode_file(image_path,"")
        
        # 5.a Output the barcode format and barcode text.
        output_results(results)
        
        print("\nDecode through parameters template:")
        # 3.b config through parameters template
        config_accuracy_first_by_template(dbr)
        
        # 4.b Decode barcodes from an image file by template. 
        results = dbr.decode_file(image_path, "")
        
        # 5.b Output the barcode format and barcode text.
        output_results(results)
            
    except BarcodeReaderError as bre:
        print(bre)