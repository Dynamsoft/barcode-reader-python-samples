import cv2
from dbr import DynamsoftBarcodeReader
dbr = DynamsoftBarcodeReader()
import time
import os

import sys
sys.path.append('../')
# import config

results = None
# The callback function for receiving barcode results
def onBarcodeResult(data):
    global results
    results = data

def get_time():
    localtime = time.localtime()
    capturetime = time.strftime("%Y%m%d%H%M%S", localtime)
    return capturetime

def read_barcode():
    global results
    video_width = 640
    video_height = 480

    vc = cv2.VideoCapture(0)
    vc.set(3, video_width) #set width
    vc.set(4, video_height) #set height

    if vc.isOpened():  
        dbr.InitLicense('LICENSE-KEY')
        rval, frame = vc.read()
    else:
        return

    windowName = "Barcode Reader"

    max_buffer = 2
    max_results = 10
    image_format = 1 # 0: gray; 1: rgb888

    dbr.StartVideoMode(max_buffer, max_results, video_width, video_height, image_format, onBarcodeResult)

    while True:
        if results != None:
            thickness = 2
            color = (0,255,0)
            for result in results:
                print("barcode format: " + result["BarcodeFormatString"])
                print("barcode text: " + result["BarcodeText"])
                localizationResult = result["LocalizationResult"]
                x1 = localizationResult["X1"]
                y1 = localizationResult["Y1"]
                x2 = localizationResult["X2"]
                y2 = localizationResult["Y2"]
                x3 = localizationResult["X3"]
                y3 = localizationResult["Y3"]
                x4 = localizationResult["X4"]
                y4 = localizationResult["Y4"]

                cv2.line(frame, (x1, y1), (x2, y2), color, thickness)
                cv2.line(frame, (x2, y2), (x3, y3), color, thickness)
                cv2.line(frame, (x3, y3), (x4, y4), color, thickness)
                cv2.line(frame, (x4, y4), (x1, y1), color, thickness)

            results = None

        cv2.imshow(windowName, frame)
        rval, frame = vc.read()

        # start = time.time()
        try:
            ret = dbr.AppendVideoFrame(frame)
        except:
            pass

        # cost = (time.time() - start) * 1000
        # print('time cost: ' + str(cost) + ' ms')

        # 'ESC' for quit
        key = cv2.waitKey(1)
        if key == 27:
            break

    dbr.StopVideoMode()
    cv2.destroyWindow(windowName)


if __name__ == "__main__":
    print("OpenCV version: " + cv2.__version__)
    read_barcode()
