import os
import sys
import time
import io
import numpy as np
from picamera import PiCamera
from picamera.array import PiRGBArray
from dbr import *
import cv2

# you can change the following variables' value to your own value.
license_key = "Input your own license"
json_file = r"Please input your own template path"

reader = BarcodeReader()

def intermediate_results_callback_func(frame_id, i_results, user_data):
        print(frame_id)
        for result in i_results:
            intermediate_result = IntermediateResult(result)
            print('Intermediate Result data type : {0}'.format(intermediate_result.result_type))
            print('Intermediate Result data : {0}'.format(intermediate_result.results))
            print("-------------")
## Or you can inherit the abstract class IntermediateResultCallBack to implement the abstract method intermediate_results_callback_func.
# class SubIntermediateResultCallBack(IntermediateResultCallBack):
#     @staticmethod
#     def intermediate_results_callback_func(frame_id, i_results, user_data):
#         print(frame_id)
#         for result in i_results:
#             intermediate_result = IntermediateResult(result)
#             print('Intermediate Result data type : {0}'.format(intermediate_result.result_type))
#             print('Intermediate Result data : {0}'.format(intermediate_result.results))
#             print("-------------")


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
## Or you can inherit the abstract class TextResultResultCallBack to implement the abstract method text_results_callback_func.
# class SubTextResultResultCallBack(TextResultResultCallBack):
#     @staticmethod
#     def text_results_callback_func(frame_id, t_results, user_data):
#         print(frame_id)
#         for result in t_results:
#             text_result = TextResult(result)
#             print("Barcode Format : ")
#             print(text_result.barcode_format_string)
#             print("Barcode Text : ")
#             print(text_result.barcode_text)
#             print("Localization Points : ")
#             print(text_result.localization_result.localization_points)
#             print("Exception : ")
#             print(text_result.exception)
#             print("-------------")


def error_callback_func(frame_id, error_code, user_data):
        print(frame_id)
        error_msg = user_data.get_error_string(error_code)
        print('Error : {0} ; {1}'.format(error_code, error_msg))
## Or you can inherit the abstract class ErrorCallBack to implement the abstract method error_callback_func.
# class SubErrorCallBack(ErrorCallBack):
#     @staticmethod
#     def error_callback_func(frame_id, error_code, user_data):
#         print(frame_id)
#         error_msg = user_data.get_error_string(error_code)
#         print('Error : {0} ; {1}'.format(error_code, error_msg))


def get_time():
    localtime = time.localtime()
    capturetime = time.strftime("%Y%m%d%H%M%S", localtime)
    return capturetime

def read_barcode():
    video_width = 0
    video_height = 0
    
    # vc = cv2.VideoCapture(0)
    camera = PiCamera()
    camera.resolution = (1024, 1024) # Set image's width and height

    # SetPiCameraParameters(camera):
    #     camera.saturation = 80 # Video or Image saturation
    #     camera.brightness = 50 # Video or Image brightness
    #     camera.shutter_speed = 6000000 # The shutter speed
    #     camera.iso = 800 # ISO
    #     camera.sharpness = 0 # Image Sharpness
    #     camera.hflip = True # Whether to flip horizontally
    #     camera.vflip = True # Whether to flip vertically
    #     camera.rotation = 0 # Whether to rotate image
    #     camera.resolution = (280, 160) # Set image's width and height


    video_width = camera.resolution[0]
    video_height = camera.resolution[1]
    print(camera.resolution)

    stride = 0
    stream = io.BytesIO()
    camera.capture(stream, format='jpeg')
    # create numpy by stream
    data = np.frombuffer(stream.getvalue(), dtype=np.uint8)
    # decode numpy by opencv
    image = cv2.imdecode(data, 1)
    stride = image.strides[0]
    print(stride)
    rawCapture = PiRGBArray(camera, size=(video_width, video_height))

    windowName = "Barcode Reader"

    parameters = reader.init_frame_decoding_parameters()
    # you can modify these following parameters.
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

    reader.start_video_mode(parameters, text_results_callback_func)
    # reader.start_video_mode(parameters, SubTextResultResultCallBack.text_results_callback_func)
    ## You can use three callbacks at the same time.
    # reader.start_video_mode(parameters, text_results_callback_func, "", intermediate_results_callback_func, error_callback_func, reader)
    # reader.start_video_mode(parameters, SubTextResultResultCallBack.text_results_callback_func, "", SubIntermediateResultCallBack.intermediate_results_callback_func, SubErrorCallBack.error_callback_func, reader)

    for frame in camera.capture_continuous(rawCapture, format='bgr', use_video_port=True):
        image = frame.array

        try:
            ret = reader.append_video_frame(image)
        except:
            pass
        
        # 'ESC' for quit
        key = cv2.waitKey(1)
        # reset
        rawCapture.truncate(0)
        if key == 27:
            break

    reader.stop_video_mode()
    cv2.destroyWindow(windowName)
    camera.close()


print("-------------------start------------------------")

# Apply for a trial license: https://www.dynamsoft.com/customer/license/trialLicense?product=dbr&utm_source=github
reader.init_license(license_key)

## The code snippet below shows how to use the full license in DBR 8.x:
# connection_paras = BarcodeReader.init_lts_connection_parameters()
## If DBR service is already built on your server, you can fill in the address of your server, or leave this property's default value.
# connection_paras.main_server_url = "Input your own server url"
# connection_paras.handshake_code = "Input your own handshake"
# connection_paras.deployment_type = EnumDMDeploymentType.DM_DT_DESKTOP
# connection_paras.uuid_generation_method = EnumDMUUIDGenerationMethod.DM_UUIDGM_RANDOM
# try:
#     error = BarcodeReader.init_license_from_lts(connection_paras)
#     if error[0] != EnumErrorCode.DBR_OK:
#         print(error[1])
# except BarcodeReaderError as bre:
#     print(bre)

error = reader.init_runtime_settings_with_file(json_file)
if error[0] != EnumErrorCode.DBR_OK:
    print(error[1])

read_barcode()
print("-------------------over------------------------")