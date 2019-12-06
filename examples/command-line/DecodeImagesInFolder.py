import os
import random
import glob
import time
import cv2
import numpy as np

from dbr import DynamsoftBarcodeReader
# from pylibdmtx.pylibdmtx import decode
# import matplotlib.pyplot as plt 
# import matplotlib.image as mpimg

# %matplotlib inline 

KEY = "t0068MgAAAE/JLbpY2i8Xz7pGt6NhN1wRL9QxaFE2kQRYi/5sq8P0uddejL4moxsvWxBAt3PmH+bxNQxnLt9AaBY+JTZOwy0="
PATH_TO_PARAM = r'D:\Work\test\template.txt'
PATH_TO_IMAGEs = r'D:\DBR\DBR7.2.2\DLL\Images'

# def pylibdmtxReader(fileName, shrink_max):
    
#     '''
#     Funtion that takes an image and shrink parameter
#     and returns the values decoded from barcodes.

#     Input Arguments:
#      - image: the image
#      - shrink: the shrink parameter
#         shrink the image so that cells become one or two pixels large,
#         the Data Matrix will stand-out as a highly textured area, 
#         and the gradient will strongly respond.

#     Returns:
#     - barcode
#     '''
    

#     image = cv2.imread(fileName, cv2.IMREAD_UNCHANGED)
#     shrink = np.arange(1, shrink_max)

#     for i in shrink:
#         # time.sleep(1)
#         barcode = decode(image, shrink = i)
#         while barcode!=[]:
#             if barcode[0].data.decode("utf-8").startswith("BF"):
#                 return print("Barcode: {0}".format(barcode[0].data.decode("utf-8")))
#                 break  
#             else:
#                 print('No Barcode Found.')
               
def dynamsoftReader (fileName,key, path_to_param):
    
    dbr = DynamsoftBarcodeReader()
    dbr.initLicense(key)
    
    # with open(path_to_param, 'r') as file:
    #     params = file.read().replace('\n', '')
    #     ret = dbr.setParameters(params)
    
    try:
        image = cv2.imread(fileName)

#         results = dbr.decodeFile(fileName, dbr.BF_ALL)
        results = dbr.DecodeBuffer(image, image.shape[0], image.shape[1], image.strides[0])

        if results:
            textResults = results["TextResults"]
            for textResult in textResults:
                print("BarcodeFormat: {0}".format(textResult["BarcodeFormatString"]))
                print("BarcodeText: {0}".format(textResult["BarcodeText"]))

        else:
            print('No Barcode Found.')
    except Exception as err:
        print(err)

# %time pylibdmtxReader(IMAGE,10)
# %time dynamsoftReader(IMAGE,KEY,PATH_TO_PARAM)

for idx, img in enumerate(glob.glob(os.path.join(PATH_TO_IMAGEs, "*.*"))):
    print('Test', idx+1)
    print(40*'#')
    #print p
    # image = mpimg.imread(img) # images are color images
    # plt.imshow(image)
    # plt.show()
    print('pylibdmtx 0.1.9:')
    # %time 
    # pylibdmtxReader(img,10)
    print()
    print('Dynamsoft Barcode Reader 7.2.0.09242:')
    # %time 
    dynamsoftReader(img,KEY,PATH_TO_PARAM)
    print(40*'#')
    print()