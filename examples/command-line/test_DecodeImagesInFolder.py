import os
import random
import glob
import time
import cv2
import numpy as np

from dbr import DynamsoftBarcodeReader


LICENSE_KEY = "Input your own license"
PATH_TO_IMAGEs = r"Please input your own images library path"
              
def dynamsoftReader (fileName, key):
    
    dbr = DynamsoftBarcodeReader()
    dbr.InitLicense(key)

   
    # image = cv2.imread(fileName)  
    # results = dbr.DecodeBuffer(image, image.shape[0], image.shape[1], image.strides[0])
    try:
        results = dbr.DecodeFile(fileName)

        if results:
            textResults = results["TextResults"]
            textResultsLength = len(textResults)
            if textResultsLength != 0:
                for textResult in textResults:
                    print("BarcodeFormat : " + textResult["BarcodeFormatString"])
                    print("BarcodeText : " + textResult["BarcodeText"])
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
                    print("LocalizationPoints : " + str(localizationPoints))
            else:
                print('No Barcode Found.')
        else:
            print('No Barcode Found.')
    except Exception as err:
        print(err)


for idx, img in enumerate(glob.glob(os.path.join(PATH_TO_IMAGEs, "*.*"))):
    print(img)
    print('Test', idx+1)
    print(40*'#')
    dynamsoftReader(img, LICENSE_KEY)
    print(40*'#')