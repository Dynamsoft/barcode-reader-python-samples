from dynamsoft_barcode_reader_bundle import *
import cv2
import os
class MyCapturedResultReceiver(CapturedResultReceiver):

    def __init__(self):
        super().__init__()

    def on_decoded_barcodes_received(self, result: DecodedBarcodesResult) -> None:
        if result.get_error_code() == EnumErrorCode.EC_UNSUPPORTED_JSON_KEY_WARNING:
            print("Warning:", result.get_error_string())
        elif result.get_error_code() != EnumErrorCode.EC_OK:
            print("Error:", result.get_error_string())
        items = result.get_items()
        if len(items) != 0:
            tag: ImageTag = result.get_original_image_tag()
            if tag is not None:
                print("ImageID:",tag.get_image_id())
            print("Decoded", len(items), "barcodes.")
            for index,item in enumerate(items):
                print("Result", index+1)
                print("Barcode Format:", item.get_format_string())
                print("Barcode Text:", item.get_text())
                print()
class MyVideoFetcher(ImageSourceAdapter):

    def __init__(self):
        super().__init__()

    def has_next_image_to_fetch(self) -> bool:
         return True

def decode_video(use_video_file: bool = False, video_file_path: str = "") -> None:
    cvr_instance = CaptureVisionRouter()

    fetcher = MyVideoFetcher()
    fetcher.set_max_image_count(100)
    fetcher.set_buffer_overflow_protection_mode(EnumBufferOverflowProtectionMode.BOPM_UPDATE)
    fetcher.set_colour_channel_usage_type(EnumColourChannelUsageType.CCUT_AUTO)
    cvr_instance.set_input(fetcher)

    filter = MultiFrameResultCrossFilter()
    filter.enable_result_cross_verification(EnumCapturedResultItemType.CRIT_BARCODE, True)
    filter.enable_result_deduplication(EnumCapturedResultItemType.CRIT_BARCODE, True)
    filter.set_duplicate_forget_time(EnumCapturedResultItemType.CRIT_BARCODE, 5000)
    cvr_instance.add_result_filter(filter)

    receiver = MyCapturedResultReceiver()
    cvr_instance.add_result_receiver(receiver)

    error_code, error_msg = cvr_instance.start_capturing(EnumPresetTemplate.PT_READ_BARCODES, False)
    if error_code != EnumErrorCode.EC_OK:
        print("Error:", error_msg)
    else:
        video_width = 0
        video_height = 0
        vc: cv2.VideoCapture = None
        if not use_video_file:
            # a. Decode video from camera
            vc = cv2.VideoCapture(0)
        else:
            # # b. Decode video file
            vc = cv2.VideoCapture(video_file_path)

        video_width  = int(vc.get(cv2.CAP_PROP_FRAME_WIDTH))
        video_height = int(vc.get(cv2.CAP_PROP_FRAME_HEIGHT))
        vc.set(3, video_width) #set width
        vc.set(4, video_height) #set height

        if not vc.isOpened():
            cvr_instance.stop_capturing(False, True)
            return

        windowName = "Video Barcode Reader"

        image_id = 0
        while True:
            image_id += 1
            rval, frame = vc.read()
            if rval == False:
                break
            tag = FileImageTag("",0,0)
            tag.set_image_id(image_id)
            image = ImageData(frame.tobytes(), frame.shape[1], frame.shape[0], frame.strides[0], EnumImagePixelFormat.IPF_RGB_888, 0, tag)
            fetcher.add_image_to_buffer(image)
            cv2.imshow(windowName, frame)
            # 'ESC' for quit
            key = cv2.waitKey(1)
            if key == 27:
                break

        cvr_instance.stop_capturing(False, True)
        cv2.destroyWindow(windowName)

def get_mode_and_path():
    use_video_file = False
    video_file_path = ""
    while True:
        try:
            mode = int(
                input(
                    ">> Choose a Mode Number:\n"
                    "1. Decode video from camera.\n"
                    "2. Decode video from file.\n"
                    ">> 1 or 2:\n"
                ))
            if mode == 1 or mode == 2:
                if mode == 1:
                    use_video_file = False
                    break

                use_video_file = True
                while True:
                    video_file_path = input(">> Input your video full path:\n").strip('\'"')
                    if not os.path.exists(video_file_path):
                        print("Error:File not found.\n")
                        continue
                    break
                break
            else:
                raise ValueError
        except ValueError:
            print("Error:Wrong input.\n")
            continue

    return use_video_file, video_file_path

if __name__ == "__main__":

    print("-------------------start------------------------")

    try:
        # Initialize license.
        # The string "DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9" here is a free public trial license. Note that network connection is required for this license to work.
        # You can also request a 30-day trial license in the customer portal: https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
        errorCode, errorMsg = LicenseManager.init_license("DLS2eyJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSJ9")
        if errorCode != EnumErrorCode.EC_OK and errorCode != EnumErrorCode.EC_LICENSE_CACHE_USED:
            print("License initialization failed: ErrorCode:", errorCode, ", ErrorString:", errorMsg)
        else:
            # Decode video from file or camera
            use_video_file, video_file_path = get_mode_and_path()
            decode_video(use_video_file, video_file_path)

    except Exception as e:
        print(e)

    print("-------------------over------------------------")