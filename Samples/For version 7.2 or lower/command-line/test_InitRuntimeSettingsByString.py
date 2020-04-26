import os
import json
from dbr import DynamsoftBarcodeReader
dbr = DynamsoftBarcodeReader()

import cv2
import sys
sys.path.append('../')

def InitLicense(license):
    dbr.InitLicense(license)

def InitRuntimeSettingsByJsonString(inputString):
    errorCode = dbr.InitRuntimeSettingsByJsonString(inputString)
    if errorCode != 0:
        print("Failed!")
    else:
        print("Successful")

def OutputRuntimeSettingsToString():
    settings = dbr.OutputSettingsToJsonString()
    print(settings)

if __name__ == "__main__":

#you can change the following two variables' value to your own value.
    licenseKey = "Input your own license"
    inputString = '{"ImageParameter" : { "BarcodeFormatIds" : [ "BF_ALL" ], "DeblurLevel" : 9, "Description" : "", "ExpectedBarcodesCount" : 0, "MaxAlgorithmThreadCount" : 4, "Name" : "CurrentRuntimeSettings", "Timeout" : 10000}, "Version" : "3.0"}'

    InitLicense(licenseKey)
    InitRuntimeSettingsByJsonString(inputString)
    OutputRuntimeSettingsToString()