import os
from dbr import DynamsoftBarcodeReader
dbr = DynamsoftBarcodeReader()

import cv2
import sys
sys.path.append('../')

def InitLicense(license):
    dbr.InitLicense(license)

def UpdateRuntimeSettings(settings):
    dbr.UpdataRuntimeSettings(settings)

def GetRuntimeSettings():
    return dbr.GetRuntimeSettings()

if __name__ == "__main__":

#you can change the following two variables' value to your own value.
    licenseKey = "Input your own license"

    InitLicense(licenseKey)
    settings = GetRuntimeSettings()
    for key,value in settings.items():
        print(key + " : " + str(value))
    settings["BarcodeFormatIds"] = dbr.BF_ONED | dbr.BF_QR_CODE
    settings["ExpectedBarcodesCount"] = 10
    UpdateRuntimeSettings(settings)
    outputSettings = GetRuntimeSettings()
    for key,value in outputSettings.items():
        print(key + " : " + str(value))