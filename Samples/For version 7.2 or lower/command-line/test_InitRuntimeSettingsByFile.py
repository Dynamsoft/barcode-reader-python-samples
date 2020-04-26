import os
import json
from dbr import DynamsoftBarcodeReader
dbr = DynamsoftBarcodeReader()

import cv2
import sys
sys.path.append('../')

def InitLicense(license):
    dbr.InitLicense(license)

def InitRuntimeSettingsByJsonFile(inputFileName):
    errorCode = dbr.InitRuntimeSettingsByJsonFile(inputFileName)
    if errorCode != 0:
        print("Failed!")
    else:
        print("Successful")

def OutputRuntimeSettingsToFile(outputFileName):
    dbr.OutputSettingsToJsonFile(outputFileName)

if __name__ == "__main__":

#you can change the following three variables' value to your own value.
    licenseKey = "Input your own license"
    inputFileName = r"Please input your own template path"
    outputFileName = r"Please input your own output template path"

    InitLicense(licenseKey)
    InitRuntimeSettingsByJsonFile(inputFileName)
    OutputRuntimeSettingsToFile(outputFileName)