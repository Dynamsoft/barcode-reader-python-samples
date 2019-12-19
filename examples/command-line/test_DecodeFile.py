import os
import cv2
import sys
sys.path.append('../')
from dbr import DynamsoftBarcodeReader
dbr = DynamsoftBarcodeReader()

def InitLicense(license):
    dbr.InitLicense(license)

def DecodeFile(fileName):
    try:
        results = dbr.DecodeFile(fileName)
        textResults = results["TextResults"]
        resultsLength = len(textResults)
        print("count: " + str(resultsLength))
        if resultsLength != 0:
            for textResult in textResults:
                print(textResult["BarcodeFormatString"])
                print(textResult["BarcodeText"])
                localizationResult = textResult["LocalizationResult"]
                x1 = localizationResult["X1"]
                y1 = localizationResult["Y1"]
                x2 = localizationResult["X2"]
                y2 = localizationResult["Y2"]
                x3 = localizationResult["X3"]
                y3 = localizationResult["Y3"]
                x4 = localizationResult["X4"]
                y4 = localizationResult["Y4"]
                localizationPoints = [(x1,y1),(x2,y2),(x3,y3),(x4,y4)]
                print(localizationPoints)
        else :
            print("No barcode detected")
    except Exception as err:
        print(err)


if __name__ == "__main__":

#you can change the following three variables' value to your own value.
    licenseKey = "Input your own license"
    fileName = r"Please input your own image path"
    inputFileName = r"Please input your own template path"

    InitLicense(licenseKey)
    errorCode = dbr.InitRuntimeSettingsByJsonFile(inputFileName)
    if errorCode != 0:
        print("Failed!")
    else:
        print("Successful")
    DecodeFile(fileName)