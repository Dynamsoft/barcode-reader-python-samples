import os
import json
from dbr import DynamsoftBarcodeReader
dbr = DynamsoftBarcodeReader()
# print(dir(dbr))

import cv2

import sys
sys.path.append('../')
# import config

def InitLicense(license):
    dbr.InitLicense(license)

def DecodeFile(fileName, templateName = ""):
    try:
        
        # results is a dictionary object which includes TextResults and IntermediateResults. 
        results = dbr.DecodeFile(fileName, templateName)
        # textResults is a list object, the following program will output each whole text result.
        # if you just want some individual results in textResult, you can get all keys in text result and get the value by the key.
        textResults = results["TextResults"]
        intermediateResults = results["IntermediateResults"]
        for textResult in textResults:
            print(textResult)
            print(textResult.keys())
            # print(textResult["BarcodeFormat"])
            # print(textResult["BarcodeFormatString"])
            # print(textResult["BarcodeText"])
            # print(textResult["BarcodeBytes"])
            # # LocalizationResult is a dictionary object, you can use the same method as textResult to get the key-value. 
            # print(textResult["LocalizationResult"])
            # # DetailedResult is a dictionary object, you can use the same method as textResult to get the key-value. 
            # print(textResult["DetailedResult"])
            # # ExtendedResults is a list object , and each item of it is a dictionary object.
            # extendedResults = textResult["ExtendedResults"]
            # for extendedResult in extendedResults:
            #     print(extendedResult)
        # intermediateResults is a list object, the following program will output each whole intermediate result.
        # if you just want some individual results in intermediateResult, you can get all keys in intermediateResult and get the value by the key.
        for intermediateResult in intermediateResults:
            print(intermediateResult)
            print(intermediateResult.keys())
    except Exception as err:
        print(err)

def DecodeBuffer(image, templateName = ""):
    results = dbr.DecodeBuffer(image, templateName)
    textResults = results["TextResults"]
    thickness = 2
    color = (0,255,0)
    for textResult in textResults:
        print("barcode format: " + textResult["BarcodeFormatString"])
        print("barcode text: " + textResult["BarcodeText"])
        localizationResult = textResult["LocalizationResult"]
        x1 = localizationResult["X1"]
        y1 = localizationResult["Y1"]
        x2 = localizationResult["X2"]
        y2 = localizationResult["Y2"]
        x3 = localizationResult["X3"]
        y3 = localizationResult["Y3"]
        x4 = localizationResult["X4"]
        y4 = localizationResult["Y4"]

        cv2.line(image, (x1, y1), (x2, y2), color, thickness)
        cv2.line(image, (x2, y2), (x3, y3), color, thickness)
        cv2.line(image, (x3, y3), (x4, y4), color, thickness)
        cv2.line(image, (x4, y4), (x1, y1), color, thickness)

    cv2.imshow("Localization", image)
    cv2.waitKey(0)

def DecodeFileStream(imagePath, templateName = ""):
    with open(imagePath, "rb") as fread:
        total = fread.read()
        results = dbr.DecodeFileStream(bytearray(total), len(total))
        textResults = results["TextResults"]
        for textResult in textResults:
            print("barcode format: " + textResult["BarcodeFormatString"])
            print("barcode text: " + textResult["BarcodeText"])

if __name__ == "__main__":
    print("OpenCV version: " + cv2.__version__)
    import sys
    barcode_image = ""
    if sys.version_info < (3, 0):
        barcode_image = raw_input("Enter the barcode file: ")
    else:
        barcode_image = input("Enter the barcode file: ")

    if not os.path.isfile(barcode_image):
        print("It is not a valid file.")
    else:
        InitLicense("Input your license")        
        # Get default barcode params
        params = dbr.GetRuntimeSettings()
        params["BarcodeFormatIds"] = dbr.BF_ONED | dbr.BF_QR_CODE
        # Set parameters
        ret = dbr.UpdataRuntimeSettings(params)
        
        DecodeFile(barcode_image)
        image = cv2.imread(barcode_image, 1)
        DecodeBuffer(image)
