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

def AppendTemplateString(appendString, conflictMode):
    errorCode = dbr.AppendTplStringToRuntimeSettings(appendString, conflictMode)
    if errorCode != 0:
        print("Failed!")
    else:
        print("Successful")

def OutputAllTemplateName():
    allTemplateName = dbr.GetAllTemplateNames()
    print(allTemplateName)

def OutputRuntimeSettingsToString():
    settings = dbr.OutputSettingsToJsonString()
    print(settings)

if __name__ == "__main__":

#you can change the following four variables' value to your own value.
    licenseKey = "Input your own license"
    inputString = '{"ImageParameter" : { "BarcodeFormatIds" : [ "BF_ALL" ], "DeblurLevel" : 9, "Description" : "", "ExpectedBarcodesCount" : 0, "MaxAlgorithmThreadCount" : 4, "Name" : "IP_1", "Timeout" : 10000}, "Version" : "3.0"}'
    appendString = '{"ImageParameter" : { "BarcodeFormatIds" : [ "BF_ALL" ], "DeblurLevel" : 9, "Description" : "", "ExpectedBarcodesCount" : 15, "MaxAlgorithmThreadCount" : 2, "Name" : "IP_2", "Timeout" : 20000}, "Version" : "3.0"}'
    #conflictMode has two optional values : dbr.CM_OVERWRITE and dbr.CM_IGNORE
    conflictMode = dbr.CM_OVERWRITE

    InitLicense(licenseKey)
    InitRuntimeSettingsByJsonString(inputString)
    AppendTemplateString(appendString, conflictMode)
    OutputAllTemplateName()
    OutputRuntimeSettingsToString()