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
    inputFileName = r"D:\Work\InputFile\Input20191206-1.json"
    outputFileName = r"D:\Work\OutputFile\Output20191206-1.json"

    InitLicense(licenseKey)
    InitRuntimeSettingsByJsonFile(inputFileName)
    OutputRuntimeSettingsToFile(outputFileName)