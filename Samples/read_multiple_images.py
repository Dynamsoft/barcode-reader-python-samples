from dynamsoft_barcode_reader_bundle import *
import os

class MyCapturedResultReceiver(CapturedResultReceiver):

    def __init__(self) -> None:
        super().__init__()
    def on_decoded_barcodes_received(self, result: "DecodedBarcodesResult") -> None:
        tag = result.get_original_image_tag()
        if isinstance(tag, FileImageTag):
            print("File:", tag.get_file_path())
        if result.get_error_code() == EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
            print("Warning:", result.get_error_string())
        elif result.get_error_code() != EnumErrorCode.EC_OK:
            print("Error:", result.get_error_string())
        items = result.get_items()
        print("Detected", len(items), "barcodes.")
        for index, item in enumerate(items):
            print("Result", index+1)
            print("Barcode Format:", item.get_format_string())
            print("Barcode Text:", item.get_text())

class MyImageSourceStateListener(ImageSourceStateListener):
    def __init__(self, cvr:CaptureVisionRouter) -> None:
        super().__init__()
        self.cvr = cvr
    def on_image_source_state_received(self, state: int) -> None:
        if state == EnumImageSourceState.ISS_EXHAUSTED:
            if self.cvr != None:
                self.cvr.stop_capturing()
if __name__ == '__main__':
    # Initialize license.
    # You can request and extend a trial license from https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
    # The string 'DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9' here is a free public trial license. Note that network connection is required for this license to work.
    errorCode, errorMsg = LicenseManager.init_license("DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9")
    if errorCode != EnumErrorCode.EC_OK and errorCode != EnumErrorCode.EC_LICENSE_CACHE_USED:
        print("License initialization failed: ErrorCode:", errorCode, ", ErrorString:", errorMsg)
    else:
        cvr = CaptureVisionRouter()

        fetcher = DirectoryFetcher()
        fetcher.set_directory("../Images")
        cvr.set_input(fetcher)

        receiver = MyCapturedResultReceiver()
        cvr.add_result_receiver(receiver)

        listener = MyImageSourceStateListener(cvr)
        cvr.add_image_source_state_listener(listener)

        errorCode, errorMsg = cvr.start_capturing("", True)
        if errorCode != EnumErrorCode.EC_OK:
            print("Error:", errorMsg)
    input("Press Enter to quit...")