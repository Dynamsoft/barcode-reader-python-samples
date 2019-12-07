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

def AppendTemplate(appendFileName, conflictMode):
    errorCode = dbr.AppendTplFileToRuntimeSettings(appendFileName, conflictMode)
    if errorCode != 0:
        print("Failed!")
    else:
        print("Successful")

def OutputAllTemplateName():
    allTemplateName = dbr.GetAllTemplateNames()
    print(allTemplateName)

def OutputRuntimeSettingsToFile(outputFileName):
    dbr.OutputSettingsToJsonFile(outputFileName)

if __name__ == "__main__":

#you can change the following five variables' value to your own value.
    licenseKey = "Input your own license"
    inputFileName = r"D:\Work\InputFile\Input20191206-1.json"
    appendFileName = r"D:\Work\InputFile\Input20191206-2.json"
    outputFileName = r"D:\Work\OutputFile\Output20191206-2.json"
    #conflictMode has two optional values : dbr.CM_OVERWRITE and dbr.CM_IGNORE
    conflictMode = dbr.CM_OVERWRITE

    InitLicense(licenseKey)
    InitRuntimeSettingsByJsonFile(inputFileName)
    AppendTemplate(appendFileName, dbr.CM_OVERWRITE)
    OutputAllTemplateName()
    OutputRuntimeSettingsToFile(outputFileName)