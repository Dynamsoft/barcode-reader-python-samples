from dbr import *
import cv2

def text_results_callback_func(frame_id, t_results, user_data):
        print(frame_id)
        for result in t_results:
            text_result = TextResult(result)
            print("Barcode Format : ")
            print(text_result.barcode_format_string)
            print("Barcode Text : ")
            print(text_result.barcode_text)
            print("Localization Points : ")
            print(text_result.localization_result.localization_points)
            print("Exception : ")
            print(text_result.exception)
            print("-------------")

def intermediate_results_callback_func(frame_id, i_results, user_data):
        print(frame_id)
        for result in i_results:
            intermediate_result = IntermediateResult(result)
            print('Intermediate Result data type : {0}'.format(intermediate_result.result_type))
            print('Intermediate Result data : {0}'.format(intermediate_result.results))
            print("-------------")

def error_callback_func(frame_id, error_code, user_data):
        print(frame_id)
        error_msg = user_data.get_error_string(error_code)
        print('Error : {0} ; {1}'.format(error_code, error_msg))

def decode_video():
    video_width = 0
    video_height = 0
    
    # a. Decode video from camera
    vc = cv2.VideoCapture(0)

    # # b. Decode video file
    # video_file = "Put your video file path here."
    # vc = cv2.VideoCapture(video_file)
    
    video_width  = vc.get(cv2.CAP_PROP_FRAME_WIDTH)
    video_height = vc.get(cv2.CAP_PROP_FRAME_HEIGHT)
    vc.set(3, video_width) #set width
    vc.set(4, video_height) #set height

    stride = 0
    if vc.isOpened():  
        rval, frame = vc.read()
        stride = frame.strides[0]
    else:
        return

    windowName = "Video Barcode Reader"

    reader = BarcodeReader()

    parameters = reader.init_frame_decoding_parameters()
    parameters.max_queue_length = 30
    parameters.max_result_queue_length = 30
    parameters.width = video_width
    parameters.height = video_height
    parameters.stride = stride
    parameters.image_pixel_format = EnumImagePixelFormat.IPF_RGB_888
    parameters.region_top = 0
    parameters.region_bottom = 100
    parameters.region_left = 0
    parameters.region_right = 100
    parameters.region_measured_by_percentage = 1
    parameters.threshold = 0.01
    parameters.fps = 0
    parameters.auto_filter = 1

    # start video decoding. The callback function will receive the recognized barcodes.
    reader.start_video_mode(parameters, text_results_callback_func)

    # # start video decoding. Pass three callbacks at the same time.
    # reader.start_video_mode(parameters, text_results_callback_func, "", intermediate_results_callback_func, error_callback_func, reader)

    while True:
        cv2.imshow(windowName, frame)
        rval, frame = vc.read()
        if rval == False:
            break
        
        try:
            # append frame to video buffer cyclically
            ret = reader.append_video_frame(frame)
        except:
            pass
        
        # 'ESC' for quit
        key = cv2.waitKey(1)
        if key == 27:
            break

    reader.stop_video_mode()
    cv2.destroyWindow(windowName)


if __name__ == "__main__":

    print("-------------------start------------------------")

    try:
        # Initialize license.
        # The organization id 200001 here will grant you a public trial license good for 7 days. Note that network connection is required for this license to work.
        # If you want to use an offline license, please contact Dynamsoft Support: https://www.dynamsoft.com/company/contact/
        # You can also request a 30-day trial license in the customer portal: https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=samples&package=python
        para = BarcodeReader.init_dls_connection_parameters()
        para.organization_id = "200001"
        error = BarcodeReader.init_license_from_dls(para)
        if error[0] != EnumErrorCode.DBR_OK:
            print("License error: "+ error[1])

        # Decode video from file or camera
        decode_video()

    except BarcodeReaderError as bre:
        print(bre)

    print("-------------------over------------------------")