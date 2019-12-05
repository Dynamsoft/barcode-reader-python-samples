#include <Python.h>
#include "DynamsoftBarcodeReader.h"
#include <ndarraytypes.h>
#include <structmember.h>

#ifndef DEBUG
#define DEBUG 0
#endif

#if PY_MAJOR_VERSION >= 3
#ifndef IS_PY3K
#define IS_PY3K 1
#endif
#endif

struct module_state
{
    PyObject *error;
};

#if defined(IS_PY3K)
#define GETSTATE(m) ((struct module_state *)PyModule_GetState(m))
#else
#define GETSTATE(m) (&_state)
static struct module_state _state;
#endif

static PyObject * ErrorOut(PyObject *m)
{
    struct module_state *st = GETSTATE(m);
    PyErr_SetString(st->error, "something bad happened");
    return NULL;
}

#define DBR_NO_MEMORY 0
#define DBR_SUCCESS 1

// #define LOG_OFF

#ifdef LOG_OFF

#define printf(MESSAGE, __VA_ARGS__)

#endif

#define DEFAULT_MEMORY_SIZE 4096

typedef struct
{
    PyObject_HEAD
    PyObject *COLOR_CLUTERING_MODE;
    PyObject *COLOR_CONVERSION_MODE;
    PyObject *GRAY_SCALE_TRANSFORMATION_MODE;
    PyObject *REGION_PREDETECTION_MODE;
    PyObject *IMAGE_PREPROCESSING_MODE;
    PyObject *TEXTURE_DETECTION_MODE;
    PyObject *TEXTURE_FILTER_MODE;
    PyObject *TEXT_ASSISTED_CORRECTION_MODE;
    PyObject *DPM_CODE_READING_MODE;
    PyObject *DEFORMATION_RESISTING_MODE;
    PyObject *BARCODE_COMPLEMENT_MODE;
    PyObject *BARCODE_COLOR_MODE;

    // Enum:Barcode formats 
    int BF_ALL;
    int BF_ONED;
    int BF_GS1_DATABAR;
    int BF_POSTALCODE;
    int BF_CODE_39;
    int BF_CODE_128;
    int BF_CODE_93;
    int BF_CODABAR;
    int BF_ITF;
    int BF_EAN_13;
    int BF_EAN_8;
    int BF_UPC_A;
    int BF_UPC_E;
    int BF_INDUSTRIAL_25;
    int BF_CODE_39_EXTENDED;
    int BF_GS1_DATABAR_OMNIDIRECTIONAL;
    int BF_GS1_DATABAR_TRUNCATED;
    int BF_GS1_DATABAR_STACKED;
    int BF_GS1_DATABAR_STACKED_OMNIDIRECTIONAL;
    int BF_GS1_DATABAR_EXPANDED;
    int BF_GS1_DATABAR_EXPANDED_STACKED;
    int BF_GS1_DATABAR_LIMITED;
    int BF_PATCHCODE;
    int BF_USPSINTELLIGENTMAIL;
    int BF_POSTNET;
    int BF_PLANET;
    int BF_AUSTRALIANPOST;
    int BF_UKROYALMAIL;
    int BF_PDF417;
    int BF_QR_CODE;
    int BF_DATAMATRIX;
    int BF_AZTEC;
    int BF_MAXICODE;
    int BF_MICRO_QR;
    int BF_MICRO_PDF417;
    int BF_GS1_COMPOSITE;
    int BF_NULL;
    // EnumBarcodeReader_2
    int BF2_NULL;
    int BF2_NONSTANDARD_BARCODE;
    // EnumBarcodeComplementMode
    int BCM_AUTO;
    int BCM_GENERAL;
    int BCM_SKIP;
    // EnumImagePixelFormat
    int IPF_BINARY;
    int IPF_BINARYINVERTED;
    int IPF_GRAYSCALED;
    int IPF_NV21;
    int IPF_RGB_565;
    int IPF_RGB_555;
    int IPF_RGB_888;
    int IPF_ARGB_8888;
    int IPF_RGB_161616;
    int IPF_ARGB_16161616;
    // EnumResultType
    int RT_STANDARD_TEXT;
    int RT_RAW_TEXT;
    int RT_CANDIDATE_TEXT;
    int RT_PARTIAL_TEXT;
    // EnumTerminatePhase
    int TP_REGION_PREDETECTED;
    int TP_IMAGE_PREPROCESSED;
    int TP_IMAGE_BINARIZED;
    int TP_BARCODE_LOCALIZED;
    int TP_BARCODE_TYPE_DETERMINED;
    int TP_BARCODE_RECOGNIZED;
    // EnumBarcodeColourMode
    int BICM_DARK_ON_LIGHT;
    int BICM_LIGHT_ON_DARK;
    int BICM_DARK_ON_DARK;
    int BICM_LIGHT_ON_LIGHT;
    int BICM_DARK_LIGHT_MIXED;
    int BICM_DARK_ON_LIGHT_DARK_SURROUNDING;
    int BICM_SKIP;
    // EnumBinarizationMode
    int BM_AUTO;
    int BM_LOCAL_BLOCK;
    int BM_SKIP;
    // EnumColourClusteringMode
    int CCM_AUTO;
    int CCM_GENERAL_HSV;
    int CCM_SKIP;
    // EnumColourImageConvertMode
    int CICM_GENERAL;
    int CICM_SKIP;
    // EnumDPMCodeReadingMode
    int DPMCRM_AUTO;
    int DPMCRM_GENERAL;
    int DPMCRM_SKIP;
    // EnumRegionPredetectionMode
    int RPM_AUTO;
    int RPM_GENERAL;
    int RPM_GENERAL_RGB_CONTRAST;
    int RPM_GENERAL_GRAY_CONTRAST;
    int RPM_GENERAL_HSV_CONTRAST;
    int RPM_SKIP;
    // EnumTextFilterMode
    int TFM_AUTO;
    int TFM_GENERAL_CONTOUR;
    int TFM_SKIP;
    // EnumConflictMode
    int CM_IGNORE;
    int CM_OVERWRITE;
    // ImagePreprocessingMode
    int IPM_AUTO;
    int IPM_GENERAL;
    int IPM_GRAY_EQUALIZE;
    int IPM_GRAY_SMOOTH;
    int IPM_SHARPEN_SMOOTH;
    int IPM_SKIP;
    // EnumIntermediateResultType
    int IRT_NO_RESULT;
    int IRT_ORIGINAL_IMAGE;
    int IRT_COLOUR_CLUSTERED_IMAGE;
    int IRT_COLOUR_CONVERTED_GRAYSCALE_IMAGE;
    int IRT_TRANSFORMED_GRAYSCALE_IMAGE;
    int IRT_PREDETECTED_REGION;
    int IRT_PREPROCESSED_IMAGE;
    int IRT_BINARIZED_IMAGE;
    int IRT_TEXT_ZONE;
    int IRT_CONTOUR;
    int IRT_LINE_SEGMENT;
    int IRT_FORM;
    int IRT_SEGMENTATION_BLOCK;
    int IRT_TYPED_BARCODE_ZONE;
    // EnumLocalizationMode
    int LM_AUTO;
    int LM_CONNECTED_BLOCKS;
    int LM_STATISTICS;
    int LM_LINES;
    int LM_SCAN_DIRECTLY;
    int LM_STATISTICS_MARKS;
    int LM_SKIP;
    // EnumQRCodeErrorCorrectionLevel
    int QRECL_ERROR_CORRECTION_H;
    int QRECL_ERROR_CORRECTION_L;
    int QRECL_ERROR_CORRECTION_M;
    int QRECL_ERROR_CORRECTION_Q;
    // EnumDeformationResistingMode
    int DRM_AUTO;
    int DRM_GENERAL;
    int DRM_SKIP;
    // EnumTextAssistedCorrectionMode
    int TACM_AUTO;
    int TACM_VERIFYING;
    int TACM_VERIFYING_PATCHING;
    int TACM_SKIP;
    // EnumTextResultOrderMode
    int TROM_CONFIDENCE;
    int TROM_POSITION;
    int TROM_FORMAT;
    int TROM_SKIP;
    // EnumTextureDetectionMode
    int TDM_AUTO;
    int TDM_GENERAL_WIDTH_CONCENTRATION;
    int TDM_SKIP;
    // EnumGrayscaleTransformationMode
    int GTM_INVERTED;
    int GTM_ORIGINAL;
    int GTM_SKIP;
    // EnumResultCoordinateType
    int RCT_PIXEL;
    int RCT_PERCENTAGE;
    // EnumIMResultDataType
    int IMRDT_IMAGE;
    int IMRDT_CONTOUR;
    int IMRDT_LINESEGMENT;
    int IMRDT_LOCALIZATIONRESULT;
    int IMRDT_REGIONOFINTEREST;
    // EnumIntermediateResultSavingMode
    int IRSM_MEMORY;
    int IRSM_FILESYSTEM;
    int IRSM_BOTH;
    
    // Barcode reader handler
    void *hBarcode;
    // Callback function for video mode
    PyObject *py_callback;
} DynamsoftBarcodeReader;

void ToHexString(unsigned char* pSrc, int iLen, char* pDest)
{
	const char HEXCHARS[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

	int i;
	char* ptr = pDest;

	for(i = 0; i < iLen; ++i)
	{
		snprintf(ptr, 4, "%c%c ", HEXCHARS[ ( pSrc[i] & 0xF0 ) >> 4 ], HEXCHARS[ ( pSrc[i] & 0x0F ) >> 0 ]);
		ptr += 3;
	}
}

static PyObject * CreatePyRuntimeSettings(PublicRuntimeSettings pSettings)
{
    PyObject * pySettings = PyDict_New();
    if(pySettings == NULL)
    {
        printf("PublicRuntimeSettings:New Dict failure\n");   
        return NULL;     
    }

    PyObject * terminatePhase               = Py_BuildValue("i", pSettings.terminatePhase);
    PyObject * terminatePhaseKey            = Py_BuildValue("s", "TerminatePhase");
    PyDict_SetItem(pySettings, terminatePhaseKey,           terminatePhase);

    PyObject * timeout                      = Py_BuildValue("i", pSettings.timeout);
    PyObject * timeoutKey                   = Py_BuildValue("s", "Timeout");
    PyDict_SetItem(pySettings, timeoutKey, timeout);

    PyObject * maxAlgorithmThreadCount      = Py_BuildValue("i", pSettings.maxAlgorithmThreadCount );
    PyObject * maxAlgorithmThreadCountKey   = Py_BuildValue("s", "MaxAlgorithmThreadCount");
    PyDict_SetItem(pySettings, maxAlgorithmThreadCountKey,  maxAlgorithmThreadCount);

    PyObject * expectedBarcodesCount        = Py_BuildValue("i", pSettings.expectedBarcodesCount);
    PyObject * expectedBarcodesCountKey     = Py_BuildValue("s", "ExpectedBarcodesCount");
    PyDict_SetItem(pySettings, expectedBarcodesCountKey,    expectedBarcodesCount);

    PyObject * barcodeFormatIds             = Py_BuildValue("i", pSettings.barcodeFormatIds);
    PyObject * BarcodeFormatIdsKey          = Py_BuildValue("s", "BarcodeFormatIds");
    PyDict_SetItem(pySettings, BarcodeFormatIdsKey,         barcodeFormatIds);

    PyObject * barcodeFormatIds_2           = Py_BuildValue("i", pSettings.barcodeFormatIds_2);
    PyObject * barcodeFormatIds_2Key        = Py_BuildValue("s", "BarcodeFormatIds_2");
    PyDict_SetItem(pySettings, barcodeFormatIds_2Key,       barcodeFormatIds_2);

    PyObject * pdfRasterDPI                 = Py_BuildValue("i", pSettings.pdfRasterDPI);
    PyObject * pdfRasterDPIKey              = Py_BuildValue("s", "PDFRasterDPI");
    PyDict_SetItem(pySettings, pdfRasterDPIKey,             pdfRasterDPI);

    PyObject * scaleDownThreshold           = Py_BuildValue("i", pSettings.scaleDownThreshold);
    PyObject * scaleDownThresholdKey        = Py_BuildValue("s", "ScaleDownThreshold");
    PyDict_SetItem(pySettings, scaleDownThresholdKey,       scaleDownThreshold);

    PyObject * binarizationModes            = PyList_New(8);
    PyObject * localizationModes            = PyList_New(8);
    PyObject * colourClusteringModes        = PyList_New(8);
    PyObject * colourConversionModes        = PyList_New(8);
    PyObject * grayscaleTransformationModes = PyList_New(8);
    PyObject * regionPredetectionModes      = PyList_New(8);
    PyObject * imagePreprocessingModes      = PyList_New(8);
    PyObject * textureDetectionModes        = PyList_New(8);
    PyObject * textFilterModes              = PyList_New(8);
    PyObject * dpmCodeReadingModes          = PyList_New(8);
    PyObject * deformationResistingModes    = PyList_New(8);
    PyObject * barcodeComplementModes       = PyList_New(8);
    PyObject * barcodeColourModes           = PyList_New(8);
    PyObject * textResultOrderModes         = PyList_New(8);

    for(int i = 0; i < 8; ++i)
    {
        PyObject * tempBM                   = Py_BuildValue("i", pSettings.binarizationModes[i]);
        PyList_SetItem(binarizationModes,        i, tempBM);
        PyObject * tempLM                   = Py_BuildValue("i", pSettings.localizationModes[i]);
        PyList_SetItem(localizationModes,        i, tempLM);
        PyObject * tempCCM                  = Py_BuildValue("i", pSettings.furtherModes.colourClusteringModes[i]);
        PyList_SetItem(colourClusteringModes,    i, tempCCM);
        PyObject * tempCICM                 = Py_BuildValue("i", pSettings.furtherModes.colourConversionModes[i]);
        PyList_SetItem(colourConversionModes,    i, tempCICM);
        PyObject * tempGTM                  = Py_BuildValue("i", pSettings.furtherModes.grayscaleTransformationModes[i]);
        PyList_SetItem(grayscaleTransformationModes, i, tempGTM);
        PyObject * tempRPM                  = Py_BuildValue("i", pSettings.furtherModes.regionPredetectionModes[i]);
        PyList_SetItem(regionPredetectionModes,  i, tempRPM);
        PyObject * tempIPM                  = Py_BuildValue("i", pSettings.furtherModes.imagePreprocessingModes[i]);
        PyList_SetItem(imagePreprocessingModes,  i, tempIPM);
        PyObject * tempTDM                  = Py_BuildValue("i", pSettings.furtherModes.textureDetectionModes[i]);
        PyList_SetItem(textureDetectionModes,    i, tempTDM);
        PyObject * tempTFM                  = Py_BuildValue("i", pSettings.furtherModes.textFilterModes[i]);
        PyList_SetItem(textFilterModes,          i, tempTFM);
        PyObject * tempDPMCRM               = Py_BuildValue("i", pSettings.furtherModes.dpmCodeReadingModes[i]);
        PyList_SetItem(dpmCodeReadingModes,      i, tempDPMCRM);
        PyObject * tempDRM                  = Py_BuildValue("i", pSettings.furtherModes.deformationResistingModes[i]);
        PyList_SetItem(deformationResistingModes, i, tempDRM);
        PyObject * tempBCM                  = Py_BuildValue("i", pSettings.furtherModes.barcodeComplementModes[i]);
        PyList_SetItem(barcodeComplementModes,   i, tempBCM);
        PyObject * tempBICM                 = Py_BuildValue("i", pSettings.furtherModes.barcodeColourModes[i]);
        PyList_SetItem(barcodeColourModes,       i, tempBICM);
        PyObject * tempTROM                 = Py_BuildValue("i", pSettings.textResultOrderModes[i]);
        PyList_SetItem(textResultOrderModes,     i, tempTROM);
    }

    PyObject * binarizationModesKey         = Py_BuildValue("s", "BinarizationModes");
    PyDict_SetItem(pySettings, binarizationModesKey,        binarizationModes);

    PyObject * localizationModesKey         = Py_BuildValue("s", "LocalizationModes");
    PyDict_SetItem(pySettings, localizationModesKey,        localizationModes);

    PyObject * colourClusteringModesKey     = Py_BuildValue("s", "ColourClusteringModes");
    PyDict_SetItem(pySettings, colourClusteringModesKey,    colourClusteringModes);

    PyObject * colourConversionModesKey     = Py_BuildValue("s", "ColourConversionModes");
    PyDict_SetItem(pySettings, colourConversionModesKey,    colourConversionModes);

    PyObject * grayscaleTransformationModesKey = Py_BuildValue("s", "GrayscaleTransformationModes");
    PyDict_SetItem(pySettings, grayscaleTransformationModesKey, grayscaleTransformationModes);
    
    PyObject * regionPredetectionModesKey   = Py_BuildValue("s", "RegionPredetectionModes");
    PyDict_SetItem(pySettings, regionPredetectionModesKey,  regionPredetectionModes);

    PyObject * imagePreprocessingModesKey   = Py_BuildValue("s", "ImagePreprocessingModes");
    PyDict_SetItem(pySettings, imagePreprocessingModesKey,  imagePreprocessingModes);

    PyObject * textureDetectionModesKey     = Py_BuildValue("s", "TextureDetectionModes");
    PyDict_SetItem(pySettings, textureDetectionModesKey,    textureDetectionModes);

    PyObject * textFilterModesKey           = Py_BuildValue("s", "TextFilterModes");
    PyDict_SetItem(pySettings, textFilterModesKey,          textFilterModes);

    PyObject * dpmCodeReadingModesKey       = Py_BuildValue("s", "DPMCodeReadingModes");
    PyDict_SetItem(pySettings, dpmCodeReadingModesKey,      dpmCodeReadingModes);

    PyObject * deformationResistingModesKey = Py_BuildValue("s", "DeformationResistingModes");
    PyDict_SetItem(pySettings, deformationResistingModesKey, deformationResistingModes);

    PyObject * barcodeComplementModesKey    = Py_BuildValue("s", "BarcodeComplementModes");
    PyDict_SetItem(pySettings, barcodeComplementModesKey,   barcodeComplementModes);

    PyObject * barcodeColourModesKey        = Py_BuildValue("s", "BarcodeColourModes");
    PyDict_SetItem(pySettings, barcodeColourModesKey,       barcodeColourModes);

    PyObject * textResultOrderModesKey      = Py_BuildValue("s", "TextResultOrderModes");
    PyDict_SetItem(pySettings, textResultOrderModesKey,     textResultOrderModes);

    PyObject * textAssistedCorrectionMode   = Py_BuildValue("i", pSettings.furtherModes.textAssistedCorrectionMode);
    PyObject * textAssistedCorrectionModeKey =Py_BuildValue("s", "TextAssistedCorrectionMode");
    PyDict_SetItem(pySettings, textAssistedCorrectionModeKey, textAssistedCorrectionMode);

    PyObject * deblurLevel                  = Py_BuildValue("i", pSettings.deblurLevel);
    PyObject * deblurLevelKey               = Py_BuildValue("s", "DeblurLevel");
    PyDict_SetItem(pySettings, deblurLevelKey,              deblurLevel);

    PyObject * intermediateResultTypes      = Py_BuildValue("i", pSettings.intermediateResultTypes);
    PyObject * intermediateResultTypesKey   = Py_BuildValue("s", "IntermediateResultTypes");
    PyDict_SetItem(pySettings, intermediateResultTypesKey,  intermediateResultTypes);

    PyObject * intermediateResultSavingMode = Py_BuildValue("i", pSettings.intermediateResultSavingMode);
    PyObject * intermediateResultSavingModeKey = Py_BuildValue("s", "IntermediateResultSavingMode");
    PyDict_SetItem(pySettings, intermediateResultSavingModeKey, intermediateResultSavingMode);

    PyObject * resultCoordinateType         = Py_BuildValue("i", pSettings.resultCoordinateType);
    PyObject * resultCoordinateTypeKey      = Py_BuildValue("s", "ResultCoordinateType");
    PyDict_SetItem(pySettings, resultCoordinateTypeKey,     resultCoordinateType);

    PyObject * returnBarcodeZoneClarity     = Py_BuildValue("i", pSettings.returnBarcodeZoneClarity);
    PyObject * returnBarcodeZoneClarityKey  = Py_BuildValue("s", "ReturnBarcodeZoneClarity");
    PyDict_SetItem(pySettings, returnBarcodeZoneClarityKey, returnBarcodeZoneClarity);

    PyObject * regionTop                    = Py_BuildValue("i", pSettings.region.regionTop);
    PyObject * regionTopKey                 = Py_BuildValue("s", "RegionTop");
    PyDict_SetItem(pySettings, regionTopKey,                regionTop);

    PyObject * regionBottom                 = Py_BuildValue("i", pSettings.region.regionBottom);
    PyObject * regionBottomKey              = Py_BuildValue("s", "RegionBottom");
    PyDict_SetItem(pySettings, regionBottomKey,             regionBottom);

    PyObject * regionLeft                   = Py_BuildValue("i", pSettings.region.regionLeft);
    PyObject * regionLeftKey                = Py_BuildValue("s", "RegionLeft");
    PyDict_SetItem(pySettings, regionLeftKey,               regionLeft);

    PyObject * regionRight                  = Py_BuildValue("i", pSettings.region.regionRight);
    PyObject * regionRightKey               = Py_BuildValue("s", "RegionRight");
    PyDict_SetItem(pySettings, regionRightKey,              regionRight);

    PyObject * regionMeasuredByPercentage   = Py_BuildValue("i", pSettings.region.regionMeasuredByPercentage);
    PyObject * regionMeasuredByPercentageKey =Py_BuildValue("s", "RegionMeasuredByPercentage");
    PyDict_SetItem(pySettings, regionMeasuredByPercentageKey, regionMeasuredByPercentage);

    PyObject * minBarcodeTextLength         = Py_BuildValue("i", pSettings.minBarcodeTextLength);
    PyObject * minBarcodeTextLengthKey      = Py_BuildValue("s", "MinBarcodeTextLength");
    PyDict_SetItem(pySettings, minBarcodeTextLengthKey,     minBarcodeTextLength);

    PyObject * minResultConfidence          = Py_BuildValue("i", pSettings.minResultConfidence);
    PyObject * minResultConfidenceKey       = Py_BuildValue("s", "MinResultConfidence");
    PyDict_SetItem(pySettings, minResultConfidenceKey,      minResultConfidence);

    return pySettings;
}

PublicRuntimeSettings CreateCRuntimeSettings(PyObject *o)
{
    PublicRuntimeSettings pSettings;
    pSettings.terminatePhase            = (TerminatePhase)(PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "TerminatePhase"))));
    pSettings.timeout                   = PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "Timeout")));
    pSettings.maxAlgorithmThreadCount   = PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "MaxAlgorithmThreadCount")));
    pSettings.expectedBarcodesCount     = PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "ExpectedBarcodesCount")));
    pSettings.barcodeFormatIds          = PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "BarcodeFormatIds")));
    pSettings.barcodeFormatIds_2        = PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "BarcodeFormatIds_2")));
    pSettings.pdfRasterDPI              = PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "PDFRasterDPI")));
    pSettings.scaleDownThreshold        = PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "ScaleDownThreshold")));

    PyObject * binarizationModes            = PyDict_GetItem(o, Py_BuildValue("s", "BinarizationModes"));
    PyObject * localizationModes            = PyDict_GetItem(o, Py_BuildValue("s", "LocalizationModes"));
    PyObject * colourClusteringModes        = PyDict_GetItem(o, Py_BuildValue("s", "ColourClusteringModes"));
    PyObject * colourConversionModes        = PyDict_GetItem(o, Py_BuildValue("s", "ColourConversionModes"));
    PyObject * grayscaleTransformationModes = PyDict_GetItem(o, Py_BuildValue("s", "GrayscaleTransformationModes"));
    PyObject * regionPredetectionModes      = PyDict_GetItem(o, Py_BuildValue("s", "RegionPredetectionModes"));
    PyObject * imagePreprocessingModes      = PyDict_GetItem(o, Py_BuildValue("s", "ImagePreprocessingModes"));
    PyObject * textureDetectionModes        = PyDict_GetItem(o, Py_BuildValue("s", "TextureDetectionModes"));
    PyObject * textFilterModes              = PyDict_GetItem(o, Py_BuildValue("s", "TextFilterModes"));
    PyObject * dpmCodeReadingModes          = PyDict_GetItem(o, Py_BuildValue("s", "DPMCodeReadingModes"));
    PyObject * deformationResistingModes    = PyDict_GetItem(o, Py_BuildValue("s", "DeformationResistingModes"));
    PyObject * barcodeComplementModes       = PyDict_GetItem(o, Py_BuildValue("s", "BarcodeComplementModes"));
    PyObject * barcodeColourModes           = PyDict_GetItem(o, Py_BuildValue("s", "BarcodeColourModes"));
    PyObject * textResultOrderModes         = PyDict_GetItem(o, Py_BuildValue("s", "TextResultOrderModes"));


    for(int i = 0; i < 8; ++i)
    {
        pSettings.binarizationModes[i]                          = (BinarizationMode)(PyLong_AsLong(PyList_GetItem(binarizationModes, i)));
        pSettings.localizationModes[i]                          = (LocalizationMode)(PyLong_AsLong(PyList_GetItem(localizationModes, i)));
        pSettings.furtherModes.colourClusteringModes[i]         = (ColourClusteringMode)(PyLong_AsLong(PyList_GetItem(colourClusteringModes, i)));
        pSettings.furtherModes.colourConversionModes[i]         = (ColourConversionMode)(PyLong_AsLong(PyList_GetItem(colourConversionModes, i)));
        pSettings.furtherModes.grayscaleTransformationModes[i]  = (GrayscaleTransformationMode)(PyLong_AsLong(PyList_GetItem(grayscaleTransformationModes, i)));
        pSettings.furtherModes.regionPredetectionModes[i]       = (RegionPredetectionMode)(PyLong_AsLong(PyList_GetItem(regionPredetectionModes, i)));
        pSettings.furtherModes.imagePreprocessingModes[i]       = (ImagePreprocessingMode)(PyLong_AsLong(PyList_GetItem(imagePreprocessingModes, i)));
        pSettings.furtherModes.textureDetectionModes[i]         = (TextureDetectionMode)(PyLong_AsLong(PyList_GetItem(textureDetectionModes, i)));
        pSettings.furtherModes.textFilterModes[i]               = (TextFilterMode)(PyLong_AsLong(PyList_GetItem(textFilterModes, i)));
        pSettings.furtherModes.dpmCodeReadingModes[i]           = (DPMCodeReadingMode)(PyLong_AsLong(PyList_GetItem(dpmCodeReadingModes, i)));
        pSettings.furtherModes.deformationResistingModes[i]     = (DeformationResistingMode)(PyLong_AsLong(PyList_GetItem(deformationResistingModes, i)));
        pSettings.furtherModes.barcodeComplementModes[i]        = (BarcodeComplementMode)(PyLong_AsLong(PyList_GetItem(barcodeComplementModes, i)));
        pSettings.furtherModes.barcodeColourModes[i]            = (BarcodeColourMode)(PyLong_AsLong(PyList_GetItem(barcodeColourModes, i)));
        pSettings.textResultOrderModes[i]                       = (TextResultOrderMode)(PyLong_AsLong(PyList_GetItem(textResultOrderModes, i)));
    }

    pSettings.furtherModes.textAssistedCorrectionMode               = (TextAssistedCorrectionMode)(PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "TextAssistedCorrectionMode"))));
    pSettings.deblurLevel                                           = PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "DeblurLevel")));
    pSettings.intermediateResultTypes                               = PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "IntermediateResultTypes")));
    pSettings.intermediateResultSavingMode                          = (IntermediateResultSavingMode)(PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "IntermediateResultSavingMode"))));
    pSettings.resultCoordinateType                                  = (ResultCoordinateType)(PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "ResultCoordinateType"))));
    pSettings.returnBarcodeZoneClarity                              = PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "ReturnBarcodeZoneClarity")));
    pSettings.region.regionTop                                      = PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "RegionTop")));
    pSettings.region.regionBottom                                   = PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "RegionBottom")));
    pSettings.region.regionLeft                                     = PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "RegionLeft")));
    pSettings.region.regionRight                                    = PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "RegionRight")));
    pSettings.region.regionMeasuredByPercentage                     = PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "RegionMeasuredByPercentage")));
    pSettings.minBarcodeTextLength                                  = PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "MinBarcodeTextLength")));
    pSettings.minResultConfidence                                   = PyLong_AsLong(PyDict_GetItem(o, Py_BuildValue("s", "MinResultConfidence")));

    return pSettings;
}

static PyObject * CreatePySamplingImageData(SamplingImageData samplingImage)
{
    //create SamplingImage
    PyObject * pySamplingImage = PyDict_New();
    if(pySamplingImage == NULL)
    {
        printf("SamplingImageData:New Dict failure\n");   
        return NULL;     
    }

    if(samplingImage.bytes != NULL)
    {
        PyObject * pySamplingImageBytes     = PyByteArray_FromStringAndSize(samplingImage.bytes, samplingImage.width * samplingImage.height);
        PyObject * pySamplingImageBytesKey  = Py_BuildValue("s", "Bytes");
        PyDict_SetItem(pySamplingImage, pySamplingImageBytesKey, pySamplingImageBytes);
    }
    else
    {
        PyObject * pySamplingImageBytes     = Py_BuildValue("s", "NULL");
        PyObject * pySamplingImageBytesKey  = Py_BuildValue("s", "Bytes");
        PyDict_SetItem(pySamplingImage, pySamplingImageBytesKey, pySamplingImageBytes);
    }


    PyObject * pySamplingImageWidth     = Py_BuildValue("i", samplingImage.width);
    PyObject * pySamplingImageWidthKey  = Py_BuildValue("s", "Width");
    PyDict_SetItem(pySamplingImage, pySamplingImageWidthKey, pySamplingImageWidth);
    PyObject * pySamplingImageHeight    = Py_BuildValue("i", samplingImage.height);
    PyObject * pySamplingImageHeightKey = Py_BuildValue("s", "Height");
    PyDict_SetItem(pySamplingImage, pySamplingImageHeightKey, pySamplingImageHeight);

    return pySamplingImage;
}

static PyObject * CreatePyDetailedResult(void * pResult, int format)
{
    if (!pResult)
    {
        printf("No detailed result detected\n");
        return NULL;
    }

    PyObject * pyResult = PyDict_New();
    if(pyResult == NULL)
    {
        printf("DetailedResult:New Dict failure\n");   
        return NULL;     
    }

    if((format & BF_ONED) != 0)
    {
        PyObject * pyModuleSize         = Py_BuildValue("i", ((OneDCodeDetails *)pResult)->moduleSize);
        PyObject * pyModuleSizeKey      = Py_BuildValue("s", "ModuleSize");
        PyDict_SetItem(pyResult, pyModuleSizeKey, pyModuleSize);

        if(((OneDCodeDetails *)pResult)->startCharsBytes != NULL)
        {
            PyObject * pyStartCharsBytes    = PyByteArray_FromStringAndSize(((OneDCodeDetails *)pResult)->startCharsBytes, ((OneDCodeDetails *)pResult)->startCharsBytesLength);
            PyObject * pyStartCharsBytesKey = Py_BuildValue("s", "StartCharsBytes");
            PyDict_SetItem(pyResult, pyStartCharsBytesKey, pyStartCharsBytes);
        }
        else
        {
            PyObject * pyStartCharsBytes    = Py_BuildValue("s", "NULL");
            PyObject * pyStartCharsBytesKey = Py_BuildValue("s", "StartCharsBytes");
            PyDict_SetItem(pyResult, pyStartCharsBytesKey, pyStartCharsBytes);
        }

        if(((OneDCodeDetails *)pResult)->stopCharsBytes != NULL)
        {
            PyObject * pyStopCharsBytes     = PyByteArray_FromStringAndSize(((OneDCodeDetails *)pResult)->stopCharsBytes, ((OneDCodeDetails *)pResult)->stopCharsBytesLength);
            PyObject * pyStopCharsBytesKey  = Py_BuildValue("s", "StopCharsBytes");
            PyDict_SetItem(pyResult, pyStopCharsBytesKey, pyStopCharsBytes);
        }
        else
        {
            PyObject * pyStopCharsBytes     = Py_BuildValue("s", "NULL");
            PyObject * pyStopCharsBytesKey  = Py_BuildValue("s", "StopCharsBytes");
            PyDict_SetItem(pyResult, pyStopCharsBytesKey, pyStopCharsBytes);
        }
        

        if(((OneDCodeDetails *)pResult)->checkDigitBytes != NULL)
        {
            PyObject * pyCheckDigitBytes    = PyByteArray_FromStringAndSize(((OneDCodeDetails *)pResult)->checkDigitBytes, ((OneDCodeDetails *)pResult)->checkDigitBytesLength);
            PyObject * pyCheckDigitBytesKey = Py_BuildValue("s", "CheckDigitBytes");
            PyDict_SetItem(pyResult, pyCheckDigitBytesKey, pyCheckDigitBytes);
        }
        else
        {
            PyObject * pyCheckDigitBytes    = Py_BuildValue("s", "NULL");
            PyObject * pyCheckDigitBytesKey = Py_BuildValue("s", "CheckDigitBytes");
            PyDict_SetItem(pyResult, pyCheckDigitBytesKey, pyCheckDigitBytes);
        }
    }
    else if(format == BF_QR_CODE)
    {
        PyObject * pyModuleSize         = Py_BuildValue("i", ((QRCodeDetails *)pResult)->moduleSize);
        PyObject * pyModuleSizeKey      = Py_BuildValue("s", "ModuleSize");
        PyDict_SetItem(pyResult, pyModuleSizeKey, pyModuleSize);

        PyObject * pyRows               = Py_BuildValue("i", ((QRCodeDetails *)pResult)->rows);
        PyObject * pyRowsKey            = Py_BuildValue("s", "Rows");
        PyDict_SetItem(pyResult, pyRowsKey, pyRows);

        PyObject * pyColumns            = Py_BuildValue("i", ((QRCodeDetails *)pResult)->columns);
        PyObject * pyColumnsKey         = Py_BuildValue("s", "Columns");
        PyDict_SetItem(pyResult, pyColumnsKey, pyColumns);
        
        PyObject * pyErrorCorrectionLevel    = Py_BuildValue("i", ((QRCodeDetails *)pResult)->errorCorrectionLevel);
        PyObject * pyErrorCorrectionLevelKey = Py_BuildValue("s", "ErrorCorrectionLevel");
        PyDict_SetItem(pyResult, pyErrorCorrectionLevelKey, pyErrorCorrectionLevel);
        
        PyObject * pyVersion            = Py_BuildValue("i", ((QRCodeDetails *)pResult)->version);
        PyObject * pyVersionKey         = Py_BuildValue("s", "version");
        PyDict_SetItem(pyResult, pyVersionKey, pyVersion);
        
        PyObject * pyModel              = Py_BuildValue("i", ((QRCodeDetails *)pResult)->model);
        PyObject * pyModelKey           = Py_BuildValue("s", "model");
        PyDict_SetItem(pyResult, pyModelKey, pyModel);
    }
    else if(format == BF_DATAMATRIX)
    {
        PyObject * pyModuleSize         = Py_BuildValue("i", ((DataMatrixDetails *)pResult)->moduleSize);
        PyObject * pyModuleSizeKey      = Py_BuildValue("s", "ModuleSize");
        PyDict_SetItem(pyResult, pyModuleSizeKey, pyModuleSize);

        PyObject * pyRows               = Py_BuildValue("i", ((DataMatrixDetails *)pResult)->rows);
        PyObject * pyRowsKey            = Py_BuildValue("s", "Rows");
        PyDict_SetItem(pyResult, pyRowsKey, pyRows);

        PyObject * pyColumns            = Py_BuildValue("i", ((DataMatrixDetails *)pResult)->columns);
        PyObject * pyColumnsKey         = Py_BuildValue("s", "Columns");
        PyDict_SetItem(pyResult, pyColumnsKey, pyColumns); 

        PyObject * pyDataRegionRows     = Py_BuildValue("i", ((DataMatrixDetails *)pResult)->dataRegionRows);
        PyObject * pyDataRegionRowsKey  = Py_BuildValue("s", "DataRegionRows");
        PyDict_SetItem(pyResult, pyDataRegionRowsKey, pyDataRegionRows);

        PyObject * pyDataRegionColumns  = Py_BuildValue("i", ((DataMatrixDetails *)pResult)->dataRegionColumns);
        PyObject * pyDataRegionColumnsKey = Py_BuildValue("s", "DataRegionColumns");
        PyDict_SetItem(pyResult, pyDataRegionColumnsKey, pyDataRegionColumns);

        PyObject * pyDataRegionNumber   = Py_BuildValue("i", ((DataMatrixDetails *)pResult)->dataRegionNumber);
        PyObject * pyDataRegionNumberKey= Py_BuildValue("s", "DataRegionNumber");
        PyDict_SetItem(pyResult, pyDataRegionNumberKey, pyDataRegionNumber); 
    }
    else if(format == BF_PDF417)
    {
        PyObject * pyModuleSize         = Py_BuildValue("i", ((PDF417Details *)pResult)->moduleSize);
        PyObject * pyModuleSizeKey      = Py_BuildValue("s", "ModuleSize");
        PyDict_SetItem(pyResult, pyModuleSizeKey, pyModuleSize);

        PyObject * pyRows               = Py_BuildValue("i", ((PDF417Details *)pResult)->rows);
        PyObject * pyRowsKey            = Py_BuildValue("s", "Rows");
        PyDict_SetItem(pyResult, pyRowsKey, pyRows);

        PyObject * pyColumns            = Py_BuildValue("i", ((PDF417Details *)pResult)->columns);
        PyObject * pyColumnsKey         = Py_BuildValue("s", "Columns");
        PyDict_SetItem(pyResult, pyColumnsKey, pyColumns);
        
        PyObject * pyErrorCorrectionLevel    = Py_BuildValue("i", ((PDF417Details *)pResult)->errorCorrectionLevel);
        PyObject * pyErrorCorrectionLevelKey = Py_BuildValue("s", "ErrorCorrectionLevel");
        PyDict_SetItem(pyResult, pyErrorCorrectionLevelKey, pyErrorCorrectionLevel);
    }
    else if(format == BF_AZTEC)
    {
        PyObject * pyModuleSize         = Py_BuildValue("i", ((AztecDetails *)pResult)->moduleSize);
        PyObject * pyModuleSizeKey      = Py_BuildValue("s", "ModuleSize");
        PyDict_SetItem(pyResult, pyModuleSizeKey, pyModuleSize);

        PyObject * pyRows               = Py_BuildValue("i", ((AztecDetails *)pResult)->rows);
        PyObject * pyRowsKey            = Py_BuildValue("s", "Rows");
        PyDict_SetItem(pyResult, pyRowsKey, pyRows);

        PyObject * pyColumns            = Py_BuildValue("i", ((AztecDetails *)pResult)->columns);
        PyObject * pyColumnsKey         = Py_BuildValue("s", "Columns");
        PyDict_SetItem(pyResult, pyColumnsKey, pyColumns); 

        PyObject * pyLayerNumber        = Py_BuildValue("i", ((AztecDetails *)pResult)->layerNumber);
        PyObject * pyLayerNumberKey     = Py_BuildValue("s", "LayerNumber");
        PyDict_SetItem(pyResult, pyLayerNumberKey, pyLayerNumber);
    }
    return pyResult;
}

static PyObject * CreatePyLocalizationResult(LocalizationResult * pResult)
{
    if (!pResult)
    {
        printf("No localization result detected\n");
        return NULL;
    }

    PyObject * pyResult = PyDict_New();
    if(pyResult == NULL)
    {
        printf("LocalizationResult:New Dict failure\n");   
        return NULL;     
    }

    PyObject * pyTerminatePhase         = Py_BuildValue("i", pResult->terminatePhase);
    PyObject * pyTerminatePhaseKey      = Py_BuildValue("s", "TerminatePhase");
    PyDict_SetItem(pyResult, pyTerminatePhaseKey, pyTerminatePhase);

    PyObject * pyBarcodeFormat          = Py_BuildValue("i", pResult->barcodeFormat);
    PyObject * pyBarcodeFormatKey       = Py_BuildValue("s", "BarcodeFormat");
    PyDict_SetItem(pyResult, pyBarcodeFormatKey, pyBarcodeFormat);

    if(pResult->barcodeFormatString != NULL)
    {
        PyObject *pyBarcodeFormatString     = Py_BuildValue("s", pResult->barcodeFormatString);
        PyObject * pyBarcodeFormatStringKey = Py_BuildValue("s", "BarcodeFormatString");
        PyDict_SetItem(pyResult, pyBarcodeFormatStringKey, pyBarcodeFormatString);
    }
    else
    {
        PyObject *pyBarcodeFormatString     = Py_BuildValue("s", "NULL");
        PyObject * pyBarcodeFormatStringKey = Py_BuildValue("s", "BarcodeFormatString");
        PyDict_SetItem(pyResult, pyBarcodeFormatStringKey, pyBarcodeFormatString);
    }
    

    PyObject * pyBarcodeFormat_2        = Py_BuildValue("i", pResult->barcodeFormat_2);
    PyObject * pyBarcodeFormatKey_2     = Py_BuildValue("s", "BarcodeFormat_2");
    PyDict_SetItem(pyResult, pyBarcodeFormatKey_2, pyBarcodeFormat_2);

    if(pResult->barcodeFormatString_2 != NULL)
    {
        PyObject * pyBarcodeFormatString_2    = Py_BuildValue("s", pResult->barcodeFormatString_2);
        PyObject * pyBarcodeFormatStringKey_2 = Py_BuildValue("s", "BarcodeFormatString_2");
        PyDict_SetItem(pyResult, pyBarcodeFormatStringKey_2, pyBarcodeFormatString_2);
    }
    else
    {
        PyObject * pyBarcodeFormatString_2    = Py_BuildValue("s", "NULL");
        PyObject * pyBarcodeFormatStringKey_2 = Py_BuildValue("s", "BarcodeFormatString_2");
        PyDict_SetItem(pyResult, pyBarcodeFormatStringKey_2, pyBarcodeFormatString_2);
    }
    

    PyObject * pyX1                     = Py_BuildValue("i", pResult->x1);
    PyObject * pyX1Key                  = Py_BuildValue("s", "X1");
    PyDict_SetItem(pyResult, pyX1Key, pyX1);

    PyObject * pyY1                     = Py_BuildValue("i", pResult->y2);
    PyObject * pyY1Key                  = Py_BuildValue("s", "Y1");
    PyDict_SetItem(pyResult, pyY1Key, pyY1);

    PyObject * pyX2                     = Py_BuildValue("i", pResult->x2);
    PyObject * pyX2Key                  = Py_BuildValue("s", "X2");
    PyDict_SetItem(pyResult, pyX2Key, pyX2);

    PyObject * pyY2                     = Py_BuildValue("i", pResult->y2);
    PyObject * pyY2Key                  = Py_BuildValue("s", "Y2");
    PyDict_SetItem(pyResult, pyY2Key, pyY2);

    PyObject * pyX3                     = Py_BuildValue("i", pResult->x3);
    PyObject * pyX3Key                  = Py_BuildValue("s", "X3");
    PyDict_SetItem(pyResult, pyX3Key, pyX3);

    PyObject * pyY3                     = Py_BuildValue("i", pResult->y3);
    PyObject * pyY3Key                  = Py_BuildValue("s", "Y3");
    PyDict_SetItem(pyResult, pyY3Key, pyY3);

    PyObject * pyX4                     = Py_BuildValue("i", pResult->x4);
    PyObject * pyX4Key                  = Py_BuildValue("s", "X4");
    PyDict_SetItem(pyResult, pyX4Key, pyX4);

    PyObject * pyY4                     = Py_BuildValue("i", pResult->y4);
    PyObject * pyY4Key                  = Py_BuildValue("s", "Y4");
    PyDict_SetItem(pyResult, pyY4Key, pyY4);

    PyObject * pyAngle                  = Py_BuildValue("i", pResult->angle);
    PyObject * pyAngleKey               = Py_BuildValue("s", "Angle");
    PyDict_SetItem(pyResult, pyAngleKey, pyAngle);

    PyObject * pyModuleSize             = Py_BuildValue("i", pResult->moduleSize);
    PyObject * pyModuleSizeKey          = Py_BuildValue("s", "ModuleSize");
    PyDict_SetItem(pyResult, pyModuleSizeKey, pyModuleSize);

    PyObject * pyPageNumber             = Py_BuildValue("i", pResult->pageNumber);
    PyObject * pyPageNumberKey          = Py_BuildValue("s", "PageNumber");
    PyDict_SetItem(pyResult, pyBarcodeFormatKey, pyBarcodeFormat);

    if(pResult->regionName != NULL)
    {
        PyObject * pyRegionName             = Py_BuildValue("s", pResult->regionName);
        PyObject * pyRegionNameKey          = Py_BuildValue("s", "RegionName");
        PyDict_SetItem(pyResult, pyRegionNameKey, pyRegionName);
    }
    else
    {
        PyObject * pyRegionName             = Py_BuildValue("s", "NULL");
        PyObject * pyRegionNameKey          = Py_BuildValue("s", "RegionName");
        PyDict_SetItem(pyResult, pyRegionNameKey, pyRegionName);
    }
    

    if(pResult->documentName != NULL)
    {
        PyObject * pyDocumentName           = Py_BuildValue("s", pResult->documentName);
        PyObject * pyDocumentNameKey        = Py_BuildValue("s", "DocumentName");
        PyDict_SetItem(pyResult, pyDocumentNameKey, pyDocumentName);
    }
    else
    {
        PyObject * pyDocumentName           = Py_BuildValue("s", "NULL");
        PyObject * pyDocumentNameKey        = Py_BuildValue("s", "DocumentName");
        PyDict_SetItem(pyResult, pyDocumentNameKey, pyDocumentName);
    }
    

    PyObject * pyResultCoordinateType   = Py_BuildValue("i", pResult->resultCoordinateType);
    PyObject * pyResultCoordinateTypeKey= Py_BuildValue("s", "ResultCoordinateType");
    PyDict_SetItem(pyResult, pyResultCoordinateTypeKey, pyResultCoordinateType);

    if(!(pResult->accompanyingTextBytes == NULL || pResult->accompanyingTextBytesLength == 0))
    {
        PyObject * pyAccompanyingTextBytes    = PyByteArray_FromStringAndSize(pResult->accompanyingTextBytes, pResult->accompanyingTextBytesLength);
        PyObject * pyAccompanyingTextBytesKey = Py_BuildValue("s", "AccompanyingTextBytes");
        PyDict_SetItem(pyResult, pyAccompanyingTextBytesKey, pyAccompanyingTextBytes);
    }
    else
    {
        PyObject * pyAccompanyingTextBytes    = Py_BuildValue("s", "NULL");
        PyObject * pyAccompanyingTextBytesKey = Py_BuildValue("s", "AccompanyingTextBytes");
        PyDict_SetItem(pyResult, pyAccompanyingTextBytesKey, pyAccompanyingTextBytes);
    }
    

    PyObject * pyConfidence             = Py_BuildValue("i", pResult->confidence);
    PyObject * pyConfidenceKey          = Py_BuildValue("s", "Confidence");
    PyDict_SetItem(pyResult, pyConfidenceKey, pyConfidence);

    return pyResult;
}

static PyObject * CreatePyExtendedResult(ExtendedResult * pResult)
{
    if (!pResult)
    {
        printf("No extended result detected\n");
        return NULL;
    }

    PyObject * pyResult = PyDict_New();
    if(pyResult == NULL)
    {
        printf("ExtendedResult:New Dict failure\n");   
        return NULL;     
    }

    PyObject * pyResultType             = Py_BuildValue("i", pResult->resultType);
    PyObject * pyResultTypeKey          = Py_BuildValue("s", "ResultType");
    PyDict_SetItem(pyResult, pyResultTypeKey, pyResultType);

    PyObject * pyBarcodeFormat          = Py_BuildValue("i", pResult->barcodeFormat);
    PyObject * pyBarcodeFormatKey       = Py_BuildValue("s", "BarcodeFormat");
    PyDict_SetItem(pyResult, pyBarcodeFormatKey, pyBarcodeFormat);

    if(pResult->barcodeFormatString != NULL)
    {
        PyObject * pyBarcodeFormatString    = Py_BuildValue("s", pResult->barcodeFormatString);
        PyObject * pyBarcodeFormatStringKey = Py_BuildValue("s", "BarcodeFormatString");
        PyDict_SetItem(pyResult, pyBarcodeFormatStringKey, pyBarcodeFormatString);
    }
    else
    {
        PyObject * pyBarcodeFormatString    = Py_BuildValue("s", "NULL");
        PyObject * pyBarcodeFormatStringKey = Py_BuildValue("s", "BarcodeFormatString");
        PyDict_SetItem(pyResult, pyBarcodeFormatStringKey, pyBarcodeFormatString);
    }
    

    PyObject * pyBarcodeFormat_2        = Py_BuildValue("i", pResult->barcodeFormat_2);
    PyObject * pyBarcodeFormatKey_2     = Py_BuildValue("s", "BarcodeFormat_2");
    PyDict_SetItem(pyResult, pyBarcodeFormatKey_2, pyBarcodeFormat_2);

    if(pResult->barcodeFormatString_2 != NULL)
    {
        PyObject * pyBarcodeFormatString_2    = Py_BuildValue("s", pResult->barcodeFormatString_2);
        PyObject * pyBarcodeFormatStringKey_2 = Py_BuildValue("s", "BarcodeFormatString_2");
        PyDict_SetItem(pyResult, pyBarcodeFormatStringKey_2, pyBarcodeFormatString_2);
    }
    else
    {
        PyObject * pyBarcodeFormatString_2    = Py_BuildValue("s", "NULL");
        PyObject * pyBarcodeFormatStringKey_2 = Py_BuildValue("s", "BarcodeFormatString_2");
        PyDict_SetItem(pyResult, pyBarcodeFormatStringKey_2, pyBarcodeFormatString_2);
    }

    PyObject * pyConfidence             = Py_BuildValue("i",pResult->confidence);
    PyObject * pyConfidenceKey          = Py_BuildValue("s", "Confidence");
    PyDict_SetItem(pyResult, pyConfidenceKey, pyConfidence);

    if(pResult->bytes != NULL)
    {
        PyObject * pyBytes                  = PyByteArray_FromStringAndSize(pResult->bytes, pResult->bytesLength);
        PyObject * pyBytesKey               = Py_BuildValue("s", "Bytes");
        PyDict_SetItem(pyResult, pyBytesKey, pyBytes);
    }
    else
    {
        PyObject * pyBytes                  = Py_BuildValue("s", "NULL");
        PyObject * pyBytesKey               = Py_BuildValue("s", "Bytes");
        PyDict_SetItem(pyResult, pyBytesKey, pyBytes);
    }

    if(pResult->accompanyingTextBytes != NULL)
    {
        PyObject * pyAccompanyingTextBytes    = PyByteArray_FromStringAndSize(pResult->accompanyingTextBytes, pResult->accompanyingTextBytesLength);
        PyObject * pyAccompanyingTextBytesKey = Py_BuildValue("s", "AccompanyingTextBytes");
        PyDict_SetItem(pyResult, pyAccompanyingTextBytesKey, pyAccompanyingTextBytes);
    }
    else
    {
        PyObject * pyAccompanyingTextBytes    = Py_BuildValue("s", "NULL");
        PyObject * pyAccompanyingTextBytesKey = Py_BuildValue("s", "AccompanyingTextBytes");
        PyDict_SetItem(pyResult, pyAccompanyingTextBytesKey, pyAccompanyingTextBytes);
    }
    

    PyObject * pyDeformation            = Py_BuildValue("i", pResult->deformation);
    PyObject * pyDeformationKey         = Py_BuildValue("s", "Deformation");
    PyDict_SetItem(pyResult, pyDeformationKey, pyDeformation);

    if(pResult->detailedResult != NULL)
    {
        PyObject * pyDetailedResult         = CreatePyDetailedResult(pResult->detailedResult, pResult->barcodeFormat);
        PyObject * pyDetailedResultKey      = Py_BuildValue("s", "DetailedResult");
        PyDict_SetItem(pyResult, pyDetailedResultKey, pyDetailedResult);
    }
    else
    {
        PyObject * pyDetailedResult         = Py_BuildValue("s", "NULL");
        PyObject * pyDetailedResultKey      = Py_BuildValue("s", "DetailedResult");
        PyDict_SetItem(pyResult, pyDetailedResultKey, pyDetailedResult);
    }
    
    
    PyObject * pySamplingImage          = CreatePySamplingImageData(pResult->samplingImage);
    PyObject * pySamplingImageKey       = Py_BuildValue("s", "SamplingImage");
    PyDict_SetItem(pyResult, pySamplingImageKey, pySamplingImage);

    PyObject * pyClarity                = Py_BuildValue("i",pResult->clarity);
    PyObject * pyClarityKey             = Py_BuildValue("s", "Clarity");
    PyDict_SetItem(pyResult, pyClarityKey, pyClarity);

    return pyResult;
}

static PyObject * CreatePyTextResults(TextResultArray *pResults)
{
    if (!pResults)
    {
        printf("No barcode detected\n");
        return NULL;
    }
    // Get barcode results
    int count = pResults->resultsCount;

    // Create a Python object to store results
    PyObject *pyTextResults = PyList_New(count);

    for (int i = 0; i < count; i++)
    {
        PyObject * pyTextResult = PyDict_New();
        if(pyTextResult == NULL)
        {
            printf("TextResult:New Dict failure\n");   
            return NULL;     
        }

        PyObject * pyBarcodeFormat      = Py_BuildValue("i", pResults->results[i]->barcodeFormat);
        PyObject * pyBarcodeFormatKey   = Py_BuildValue("s", "BarcodeFormat");
        PyDict_SetItem(pyTextResult, pyBarcodeFormatKey, pyBarcodeFormat);

        if(pResults->results[i]->barcodeFormatString != NULL)
        {
            PyObject * pyBarcodeFormatString    = Py_BuildValue("s", pResults->results[i]->barcodeFormatString);
            PyObject * pyBarcodeFormatStringKey = Py_BuildValue("s", "BarcodeFormatString");
            PyDict_SetItem(pyTextResult, pyBarcodeFormatStringKey, pyBarcodeFormatString);
        }
        else
        {
            PyObject * pyBarcodeFormatString    = Py_BuildValue("s", "NULL");
            PyObject * pyBarcodeFormatStringKey = Py_BuildValue("s", "BarcodeFormatString");
            PyDict_SetItem(pyTextResult, pyBarcodeFormatStringKey, pyBarcodeFormatString);
        }
        

        PyObject * pyBarcodeFormat_2    = Py_BuildValue("i", pResults->results[i]->barcodeFormat_2);
        PyObject * pyBarcodeFormatKey_2 = Py_BuildValue("s", "BarcodeFormat_2");
        PyDict_SetItem(pyTextResult, pyBarcodeFormatKey_2, pyBarcodeFormat_2);

        if(pResults->results[i]->barcodeFormatString_2 != NULL)
        {
            PyObject * pyBarcodeFormatString_2    = Py_BuildValue("s", pResults->results[i]->barcodeFormatString_2);
            PyObject * pyBarcodeFormatStringKey_2 = Py_BuildValue("s", "BarcodeFormatString_2");
            PyDict_SetItem(pyTextResult, pyBarcodeFormatStringKey_2, pyBarcodeFormatString_2);
        }
        else
        {
            PyObject * pyBarcodeFormatString_2    = Py_BuildValue("s", "NULL");
            PyObject * pyBarcodeFormatStringKey_2 = Py_BuildValue("s", "BarcodeFormatString_2");
            PyDict_SetItem(pyTextResult, pyBarcodeFormatStringKey_2, pyBarcodeFormatString_2);
        }
        

        if(pResults->results[i]->barcodeText != NULL)
        {
            PyObject * pyBarcodeText        = Py_BuildValue("s", pResults->results[i]->barcodeText);
            PyObject * pyBarcodeTextKey     = Py_BuildValue("s", "BarcodeText");
            PyDict_SetItem(pyTextResult, pyBarcodeTextKey, pyBarcodeText);
        }
        else
        {
            PyObject * pyBarcodeText        = Py_BuildValue("s", "NULL");
            PyObject * pyBarcodeTextKey     = Py_BuildValue("s", "BarcodeText");
            PyDict_SetItem(pyTextResult, pyBarcodeTextKey, pyBarcodeText);
        }

        if(!(pResults->results[i]->barcodeBytes == NULL || pResults->results[i]->barcodeBytesLength == 0))
        {
            PyObject * pyBarcodeBytes       = PyByteArray_FromStringAndSize(pResults->results[i]->barcodeBytes, pResults->results[i]->barcodeBytesLength);
            PyObject * pyBarcodeBytesKey    = Py_BuildValue("s", "BarcodeBytes");
            PyDict_SetItem(pyTextResult, pyBarcodeBytesKey, pyBarcodeBytes);
        }
        else
        {
            PyObject * pyBarcodeBytes       = Py_BuildValue("s", "NULL");
            PyObject * pyBarcodeBytesKey    = Py_BuildValue("s", "BarcodeBytes");
            PyDict_SetItem(pyTextResult, pyBarcodeBytesKey, pyBarcodeBytes);
        }
        
        
        if(pResults->results[i]->localizationResult != NULL)
        {
            PyObject * pyLocalizationResult     = CreatePyLocalizationResult(pResults->results[i]->localizationResult);
            PyObject * pyLocalizationResultKey  = Py_BuildValue("s", "LocalizationResult");
            PyDict_SetItem(pyTextResult, pyLocalizationResultKey, pyLocalizationResult);
        }
        else
        {
            PyObject * pyLocalizationResult     = Py_BuildValue("s", "NULL");
            PyObject * pyLocalizationResultKey  = Py_BuildValue("s", "LocalizationResult");
            PyDict_SetItem(pyTextResult, pyLocalizationResultKey, pyLocalizationResult);
        }
        

        if(pResults->results[i]->detailedResult != NULL)
        {
            PyObject * pyDetailedResult     = CreatePyDetailedResult(pResults->results[i]->detailedResult, pResults->results[i]->barcodeFormat);
            PyObject * pyDetailedResultKey  = Py_BuildValue("s", "DetailedResult");
            PyDict_SetItem(pyTextResult, pyDetailedResultKey, pyDetailedResult);
        }
        else
        {
            PyObject * pyDetailedResult     = Py_BuildValue("s", "NULL");
            PyObject * pyDetailedResultKey  = Py_BuildValue("s", "DetailedResult");
            PyDict_SetItem(pyTextResult, pyDetailedResultKey, pyDetailedResult);
        }
        

        if(pResults->results[i]->resultsCount != 0)
        {
            PyObject * pyExtendedResults    = PyList_New(pResults->results[i]->resultsCount);
            for(int j = 0; j < pResults->results[i]->resultsCount; ++j)
            {
                PyObject * pyExtendedResult = CreatePyExtendedResult(pResults->results[i]->results[j]);
                PyList_SetItem(pyExtendedResults, j, pyExtendedResult);
            }
            PyObject * pyExtendedResultsKey = Py_BuildValue("s", "ExtendedResults");
            PyDict_SetItem(pyTextResult, pyExtendedResultsKey, pyExtendedResults);
        }
        else
        {
            PyObject * pyExtendedResults = Py_BuildValue("s", "NULL");
            PyObject * pyExtendedResultsKey = Py_BuildValue("s", "ExtendedResults");
            PyDict_SetItem(pyTextResult, pyExtendedResultsKey, pyExtendedResults);
        }
        

        PyList_SetItem(pyTextResults, i, pyTextResult);
    }

    // Release memory
    DBR_FreeTextResults(&pResults);

    return pyTextResults;
}

static PyObject * CreateIntermediateResultDatas(const void** ppResults, int count, IMResultDataType dataType)
{
    PyObject * pyResults = PyList_New(count);

    for(int i = 0; i < count; ++i)
    {
        if(dataType == IMRDT_IMAGE)
        {
            PyObject * pyImageData = PyDict_New();

            if(((ImageData *)(ppResults[i]))->bytes == NULL)
            {
                PyObject * pyBytes       = PyByteArray_FromStringAndSize(((ImageData *)(ppResults[i]))->bytes, ((ImageData *)(ppResults[i]))->bytesLength);
                PyObject * pyBytesKey    = Py_BuildValue("s", "Bytes");
                PyDict_SetItem(pyImageData, pyBytesKey, pyBytes);
            }
            else
            {
                PyObject * pyBytes       = Py_BuildValue("s", "NULL");
                PyObject * pyBytesKey    = Py_BuildValue("s", "Bytes");
                PyDict_SetItem(pyImageData, pyBytesKey, pyBytes);
            }
            

            PyObject * pyWidth      = Py_BuildValue("i", ((ImageData *)(ppResults[i]))->width);
            PyObject * pyWidthKey   = Py_BuildValue("s", "Width");
            PyDict_SetItem(pyImageData, pyWidthKey, pyWidth);

            PyObject * pyHeight      = Py_BuildValue("i", ((ImageData *)(ppResults[i]))->height);
            PyObject * pyHeightKey   = Py_BuildValue("s", "Height");
            PyDict_SetItem(pyImageData, pyHeightKey, pyHeight);

            PyObject * pyStride      = Py_BuildValue("i", ((ImageData *)(ppResults[i]))->stride);
            PyObject * pyStrideKey   = Py_BuildValue("s", "Stride");
            PyDict_SetItem(pyImageData, pyStrideKey, pyStride);

            PyList_SetItem(pyResults, i, pyImageData);
        }
        else if(dataType == IMRDT_CONTOUR)
        {
            PyObject * pyContour = PyDict_New();
            int pointCount = ((Contour *)(ppResults[i]))->pointsCount;
            if(pointCount != 0)
            {
                PyObject * pyPoints = PyList_New(pointCount);
                for(int j = 0; j < pointCount; ++j)
                {
                    PyObject * pyPoint = PyDict_New();

                    PyObject * pyPointX = Py_BuildValue("i",((Contour *)(ppResults[i]))->points[j].x);
                    PyObject * pyPointXKey   = Py_BuildValue("s", "X");
                    PyDict_SetItem(pyPoint, pyPointXKey, pyPointX);

                    PyObject * pyPointY = Py_BuildValue("i",((Contour *)(ppResults[i]))->points[j].y);
                    PyObject * pyPointYKey   = Py_BuildValue("s", "Y");
                    PyDict_SetItem(pyPoint, pyPointYKey, pyPointY);

                    PyList_SetItem(pyPoints, j, pyPoint);
                }
                PyObject * pyPointsKey   = Py_BuildValue("s", "Points");
                PyDict_SetItem(pyContour, pyPointsKey, pyPoints);
                PyList_SetItem(pyResults, i, pyContour);
            }
            else
            {
                PyObject * pyPoints   = Py_BuildValue("s", "NULL");
                PyObject * pyPointsKey   = Py_BuildValue("s", "Points");
                PyDict_SetItem(pyContour, pyPointsKey, pyPoints);
                PyList_SetItem(pyResults, i, pyContour);
            }
            
        }
        else if(dataType == IMRDT_LINESEGMENT)
        {
            PyObject * pyLineSegment = PyDict_New();

            PyObject * pyStartPoint = PyDict_New();
            PyObject * pyStartPointX = Py_BuildValue("i",((LineSegment *)(ppResults[i]))->startPoint.x);
            PyObject * pyStartPointXKey   = Py_BuildValue("s", "X");
            PyDict_SetItem(pyStartPoint, pyStartPointXKey, pyStartPointX);

            PyObject * pyStartPointY = Py_BuildValue("i",((LineSegment *)(ppResults[i]))->startPoint.y);
            PyObject * pyStartPointYKey   = Py_BuildValue("s", "Y");
            PyDict_SetItem(pyStartPoint, pyStartPointYKey, pyStartPointY);
            PyObject * pyStartPointKey   = Py_BuildValue("s", "StartPoint");
            PyDict_SetItem(pyLineSegment, pyStartPointKey, pyStartPoint);

            PyObject * pyEndPoint = PyDict_New();
            PyObject * pyEndPointX = Py_BuildValue("i",((LineSegment *)(ppResults[i]))->endPoint.x);
            PyObject * pyEndPointXKey   = Py_BuildValue("s", "X");
            PyDict_SetItem(pyEndPoint, pyEndPointXKey, pyEndPointX);

            PyObject * pyEndPointY = Py_BuildValue("i",((LineSegment *)(ppResults[i]))->endPoint.y);
            PyObject * pyEndPointYKey   = Py_BuildValue("s", "Y");
            PyDict_SetItem(pyEndPoint, pyEndPointYKey, pyEndPointY);
            PyObject * pyEndPointKey   = Py_BuildValue("s", "EndPoint");
            PyDict_SetItem(pyLineSegment, pyEndPointKey, pyEndPoint);

            if(((LineSegment *)(ppResults[i]))->linesConfidenceCoefficients != NULL)
            {
                PyObject * pyLinesConfidenceCoefficients = PyList_New(4);
                for(int j = 0; j < 4; ++j)
                {
                    PyList_SetItem(pyLinesConfidenceCoefficients, j, Py_BuildValue("i",((LineSegment *)(ppResults[i]))->linesConfidenceCoefficients[j]));
                }
                PyObject * pyLinesConfidenceCoefficientsKey   = Py_BuildValue("s", "LinesConfidenceCoefficients");
                PyDict_SetItem(pyLineSegment, pyLinesConfidenceCoefficientsKey, pyLinesConfidenceCoefficients);
            }
            else
            {
                PyObject * pyLinesConfidenceCoefficients   = Py_BuildValue("s", "NULL");
                PyObject * pyLinesConfidenceCoefficientsKey   = Py_BuildValue("s", "LinesConfidenceCoefficients");
                PyDict_SetItem(pyLineSegment, pyLinesConfidenceCoefficientsKey, pyLinesConfidenceCoefficients);
            }
            

            PyList_SetItem(pyResults, i, pyLineSegment);
        }
        else if(dataType == IMRDT_LOCALIZATIONRESULT)
        {
            PyObject * pyLR = PyDict_New();
            PyObject * pyLocalizationResult = CreatePyLocalizationResult((LocalizationResult *)(ppResults[i]));
            if(pyLocalizationResult != NULL)
            {
                PyObject * pyLRKey   = Py_BuildValue("s", "LocalizationRsult");
                PyDict_SetItem(pyLR, pyLRKey, pyLocalizationResult);
                PyList_SetItem(pyResults, i, pyLR);
            }
            else
            {
                PyObject * pyLocalizationResult   = Py_BuildValue("s", "NULL");
                PyObject * pyLRKey   = Py_BuildValue("s", "LocalizationRsult");
                PyDict_SetItem(pyLR, pyLRKey, pyLocalizationResult);
                PyList_SetItem(pyResults, i, pyLR);
            }
            
        }
        else if(dataType == IMRDT_REGIONOFINTEREST)
        {
            PyObject * pyRegionOfInterest = PyDict_New();

            PyObject * pyROIId      = Py_BuildValue("i", ((RegionOfInterest *)(ppResults[i]))->roiId);
            PyObject * pyROIIdKey   = Py_BuildValue("s", "ROIId");
            PyDict_SetItem(pyRegionOfInterest, pyROIIdKey, pyROIId);

            PyObject * pyPoint = PyDict_New();

            PyObject * pyPointX = Py_BuildValue("i", ((RegionOfInterest *)(ppResults[i]))->point.x);
            PyObject * pyPointXKey   = Py_BuildValue("s", "X");
            PyDict_SetItem(pyPoint, pyPointXKey, pyPointX);

            PyObject * pyPointY = Py_BuildValue("i", ((RegionOfInterest *)(ppResults[i]))->point.y);
            PyObject * pyPointYKey   = Py_BuildValue("s", "Y");
            PyDict_SetItem(pyPoint, pyPointYKey, pyPointY);
            PyObject * pyPointKey   = Py_BuildValue("s", "Point");
            PyDict_SetItem(pyRegionOfInterest, pyPointKey, pyPoint);

            PyObject * pyWidth      = Py_BuildValue("i", ((RegionOfInterest *)(ppResults[i]))->width);
            PyObject * pyWidthKey   = Py_BuildValue("s", "Width");
            PyDict_SetItem(pyRegionOfInterest, pyROIIdKey, pyROIId);

            PyObject * pyHeight      = Py_BuildValue("i", ((RegionOfInterest *)(ppResults[i]))->height);
            PyObject * pyHeightKey   = Py_BuildValue("s", "Height");
            PyDict_SetItem(pyRegionOfInterest, pyHeightKey, pyHeight);

            PyList_SetItem(pyResults, i, pyRegionOfInterest);
        }
    }

    return pyResults;
}

static PyObject * CreatePyIntermediateResults(IntermediateResultArray * pResults)
{
    if (!pResults)
    {
        printf("No Intermediate result detected\n");
        return NULL;
    }
    // Get barcode results
    int count = pResults->resultsCount;

    // Create a Python object to store results
    PyObject * pyIntermediateResults = PyList_New(count);

    for(int i = 0; i < count; ++i)
    {
        PyObject * pyIntermediateResult = PyDict_New();
        if(pyIntermediateResult == NULL)
        {
            printf("IntermediateResult:New Dict failure\n");   
            return NULL;     
        }

        PyObject * pyDataType      = Py_BuildValue("i", pResults->results[i]->dataType);
        PyObject * pyDataTypeKey   = Py_BuildValue("s", "DataType");
        PyDict_SetItem(pyIntermediateResult, pyDataTypeKey, pyDataType);

        if(pResults->results[i]->results != NULL)
        {
            PyObject * pyResults      = CreateIntermediateResultDatas(pResults->results[i]->results, pResults->results[i]->resultsCount, pResults->results[i]->dataType);
            PyObject * pyResultsKey   = Py_BuildValue("s", "IMResults");
            PyDict_SetItem(pyIntermediateResult, pyResultsKey, pyResults);
        }
        else
        {
            PyObject * pyResults   = Py_BuildValue("s", "NULL");
            PyObject * pyResultsKey   = Py_BuildValue("s", "IMResults");
            PyDict_SetItem(pyIntermediateResult, pyResultsKey, pyResults);
        }
        

        PyObject * pyResultType      = Py_BuildValue("i", pResults->results[i]->resultType);
        PyObject * pyResultTypeKey   = Py_BuildValue("s", "ResultType");
        PyDict_SetItem(pyIntermediateResult, pyResultTypeKey, pyResultType);

        PyObject * pyBarcodeComplementMode      = Py_BuildValue("i", pResults->results[i]->barcodeComplementMode);
        PyObject * pyBarcodeComplementModeKey   = Py_BuildValue("s", "BarcodeComplementMode");
        PyDict_SetItem(pyIntermediateResult, pyBarcodeComplementModeKey, pyBarcodeComplementMode);

        PyObject * pyBCMIndex      = Py_BuildValue("i", pResults->results[i]->bcmIndex);
        PyObject * pyBCMIndexKey   = Py_BuildValue("s", "BCMIndex");
        PyDict_SetItem(pyIntermediateResult, pyBCMIndexKey, pyBCMIndex);

        PyObject * pyDPMCodeReadingMode      = Py_BuildValue("i", pResults->results[i]->dpmCodeReadingMode);
        PyObject * pyDPMCodeReadingModeKey   = Py_BuildValue("s", "DPMCodeReadingMode");
        PyDict_SetItem(pyIntermediateResult, pyDPMCodeReadingModeKey, pyDPMCodeReadingMode);

        PyObject * pyDPMCRMIndex      = Py_BuildValue("i", pResults->results[i]->dpmcrmIndex);
        PyObject * pyDPMCRMIndexKey   = Py_BuildValue("s", "DPMCRMIndex");
        PyDict_SetItem(pyIntermediateResult, pyDPMCRMIndexKey, pyDPMCRMIndex);

        PyObject * pyRotationMatrix = PyList_New(9);
        for(int j = 0; j < 9; ++j)
        {
            PyList_SetItem(pyRotationMatrix, j, Py_BuildValue("d",pResults->results[i]->rotationMatrix[j]));
        }
        PyObject * pyRotationMatrixKey   = Py_BuildValue("s", "RotationMatrix");
        PyDict_SetItem(pyIntermediateResult, pyRotationMatrixKey, pyRotationMatrix);

        PyObject * pyTextFilterMode      = Py_BuildValue("i", pResults->results[i]->textFilterMode);
        PyObject * pyTextFilterModeKey   = Py_BuildValue("s", "TextFilterMode");
        PyDict_SetItem(pyIntermediateResult, pyTextFilterModeKey, pyTextFilterMode);

        PyObject * pyTFMIndex      = Py_BuildValue("i", pResults->results[i]->tfmIndex);
        PyObject * pyTFMIndexKey   = Py_BuildValue("s", "TFMIndex");
        PyDict_SetItem(pyIntermediateResult, pyTFMIndexKey, pyTFMIndex);

        PyObject * pyLocalizationMode      = Py_BuildValue("i", pResults->results[i]->localizationMode);
        PyObject * pyLocalizationModeKey   = Py_BuildValue("s", "LocalizationMode");
        PyDict_SetItem(pyIntermediateResult, pyLocalizationModeKey, pyLocalizationMode);

        PyObject * pyLMIndex      = Py_BuildValue("i", pResults->results[i]->lmIndex);
        PyObject * pyLMIndexKey   = Py_BuildValue("s", "LMIndex");
        PyDict_SetItem(pyIntermediateResult, pyLMIndexKey, pyLMIndex);

        PyObject * pyBinarizationMode      = Py_BuildValue("i", pResults->results[i]->binarizationMode);
        PyObject * pyBinarizationModeKey   = Py_BuildValue("s", "BinarizationMode");
        PyDict_SetItem(pyIntermediateResult, pyResultTypeKey, pyResultType);

        PyObject * pyBMIndex      = Py_BuildValue("i", pResults->results[i]->bmIndex);
        PyObject * pyBMIndexKey   = Py_BuildValue("s", "BMIndex");
        PyDict_SetItem(pyIntermediateResult, pyBMIndexKey, pyBMIndex);

        PyObject * pyImagePreprocessingMode      = Py_BuildValue("i", pResults->results[i]->imagePreprocessingMode);
        PyObject * pyImagePreprocessingModeKey   = Py_BuildValue("s", "ImagePreprocessingMode");
        PyDict_SetItem(pyIntermediateResult, pyImagePreprocessingModeKey, pyImagePreprocessingMode);

        PyObject * pyIPMIndex      = Py_BuildValue("i", pResults->results[i]->ipmIndex);
        PyObject * pyIPMIndexKey   = Py_BuildValue("s", "IPMIndex");
        PyDict_SetItem(pyIntermediateResult, pyIPMIndexKey, pyIPMIndex);

        PyObject * pyROIId      = Py_BuildValue("i", pResults->results[i]->roiId);
        PyObject * pyROIIdKey   = Py_BuildValue("s", "ROIId");
        PyDict_SetItem(pyIntermediateResult, pyROIIdKey, pyROIId);

        PyObject * pyRegionPredetectionMode      = Py_BuildValue("i", pResults->results[i]->regionPredetectionMode);
        PyObject * pyRegionPredetectionModeKey   = Py_BuildValue("s", "RegionPredetectionMode");
        PyDict_SetItem(pyIntermediateResult, pyRegionPredetectionModeKey, pyRegionPredetectionMode);

        PyObject * pyRPMIndex      = Py_BuildValue("i", pResults->results[i]->rpmIndex);
        PyObject * pyRPMIndexKey   = Py_BuildValue("s", "RPMIndex");
        PyDict_SetItem(pyIntermediateResult, pyRPMIndexKey, pyRPMIndex);

        PyObject * pyGrayscaleTransformationMode      = Py_BuildValue("i", pResults->results[i]->grayscaleTransformationMode);
        PyObject * pyGrayscaleTransformationModeKey   = Py_BuildValue("s", "GrayscaleTransformationMode");
        PyDict_SetItem(pyIntermediateResult, pyRegionPredetectionModeKey, pyRegionPredetectionMode);

        PyObject * pyGTMIndex      = Py_BuildValue("i", pResults->results[i]->gtmIndex);
        PyObject * pyGTMIndexKey   = Py_BuildValue("s", "GTMIndex");
        PyDict_SetItem(pyIntermediateResult, pyGTMIndexKey, pyGTMIndex);

        PyObject * pyColourConversionMode      = Py_BuildValue("i", pResults->results[i]->colourConversionMode);
        PyObject * pyColourConversionModeKey   = Py_BuildValue("s", "ColourConversionMode");
        PyDict_SetItem(pyIntermediateResult, pyColourConversionModeKey, pyColourConversionMode);

        PyObject * pyCICMIndex      = Py_BuildValue("i", pResults->results[i]->cicmIndex);
        PyObject * pyCICMIndexKey   = Py_BuildValue("s", "CICMIndex");
        PyDict_SetItem(pyIntermediateResult, pyCICMIndexKey, pyCICMIndex);

        PyObject * pyColourClusteringMode      = Py_BuildValue("i", pResults->results[i]->colourClusteringMode);
        PyObject * pyColourClusteringModeKey   = Py_BuildValue("s", "ColourClusteringMode");
        PyDict_SetItem(pyIntermediateResult, pyColourClusteringModeKey, pyColourClusteringMode);

        PyObject * pyCCMIndex      = Py_BuildValue("i", pResults->results[i]->ccmIndex);
        PyObject * pyCCMIndexKey   = Py_BuildValue("s", "CCMIndex");
        PyDict_SetItem(pyIntermediateResult, pyCCMIndexKey, pyCCMIndex);

        PyObject * pyScaleDownRatio      = Py_BuildValue("i", pResults->results[i]->scaleDownRatio);
        PyObject * pyScaleDownRatioKey   = Py_BuildValue("s", "ScaleDownRatio");
        PyDict_SetItem(pyIntermediateResult, pyScaleDownRatioKey, pyScaleDownRatio);

        PyObject * pyFrameId      = Py_BuildValue("i", pResults->results[i]->frameId);
        PyObject * pyFrameIdKey   = Py_BuildValue("s", "FrameId");
        PyDict_SetItem(pyIntermediateResult, pyFrameIdKey, pyFrameId);

        PyList_SetItem(pyIntermediateResults, i, pyIntermediateResult);
    }

    DBR_FreeIntermediateResults(&pResults);

    return pyIntermediateResults;
}

static PyObject * CreatePyFrameDecodingParameters(FrameDecodingParameters * pParameters)
{
    PyObject * pyParameters = PyDict_New();
    if(pyParameters == NULL)
    {
        printf("FrameDecodingParameters:New Dict failure\n");   
        return NULL;     
    }

    PyObject * pyMaxQueueLength             = Py_BuildValue("i", pParameters->maxQueueLength);
    PyObject * pyMaxQueueLengthKey          = Py_BuildValue("s", "MaxQueueLength");
    PyDict_SetItem(pyParameters, pyMaxQueueLengthKey, pyMaxQueueLength);

    PyObject * pyMaxResultQueueLength             = Py_BuildValue("i", pParameters->maxResultQueueLength);
    PyObject * pyMaxResultQueueLengthKey          = Py_BuildValue("s", "MaxResultQueueLength");
    PyDict_SetItem(pyParameters, pyMaxResultQueueLengthKey, pyMaxResultQueueLength);

    PyObject * pyWidth             = Py_BuildValue("i", pParameters->width);
    PyObject * pyWidthKey          = Py_BuildValue("s", "Width");
    PyDict_SetItem(pyParameters, pyWidthKey, pyWidth);

    PyObject * pyHeight             = Py_BuildValue("i", pParameters->height);
    PyObject * pyHeightKey          = Py_BuildValue("s", "Height");
    PyDict_SetItem(pyParameters, pyHeightKey, pyHeight);

    PyObject * pyStride             = Py_BuildValue("i", pParameters->stride);
    PyObject * pyStrideKey          = Py_BuildValue("s", "Stride");
    PyDict_SetItem(pyParameters, pyStrideKey, pyStride);

    PyObject * pyImagePixelFormat             = Py_BuildValue("i", pParameters->imagePixelFormat);
    PyObject * pyImagePixelFormatKey          = Py_BuildValue("s", "ImagePixelFormat");
    PyDict_SetItem(pyParameters, pyImagePixelFormatKey, pyImagePixelFormat);

    PyObject * pyRegionTop             = Py_BuildValue("i", pParameters->region.regionTop);
    PyObject * pyRegionTopKey          = Py_BuildValue("s", "RegionTop");
    PyDict_SetItem(pyParameters, pyRegionTopKey, pyRegionTop);

    PyObject * pyRegionLeft             = Py_BuildValue("i", pParameters->region.regionLeft);
    PyObject * pyRegionLeftKey          = Py_BuildValue("s", "RegionLeft");
    PyDict_SetItem(pyParameters, pyRegionLeftKey, pyRegionLeft);

    PyObject * pyRegionRight             = Py_BuildValue("i", pParameters->region.regionRight);
    PyObject * pyRegionRightKey          = Py_BuildValue("s", "RegionRight");
    PyDict_SetItem(pyParameters, pyRegionRightKey, pyRegionRight);

    PyObject * pyRegionBottom             = Py_BuildValue("i", pParameters->region.regionBottom);
    PyObject * pyRegionBottomKey          = Py_BuildValue("s", "RegionBottom");
    PyDict_SetItem(pyParameters, pyRegionBottomKey, pyRegionBottom);

    PyObject * pyRegionMeasuredByPercentage             = Py_BuildValue("i", pParameters->region.regionMeasuredByPercentage);
    PyObject * pyRegionMeasuredByPercentageKey          = Py_BuildValue("s", "RegionMeasuredByPercentage");
    PyDict_SetItem(pyParameters, pyRegionMeasuredByPercentageKey, pyRegionMeasuredByPercentage);

    PyObject * pyThreshold             = Py_BuildValue("f", pParameters->threshold);
    PyObject * pyThresholdKey          = Py_BuildValue("s", "Threshold");
    PyDict_SetItem(pyParameters, pyThresholdKey, pyThreshold);

    PyObject * pyFPS             = Py_BuildValue("i", pParameters->fps);
    PyObject * pyFPSKey          = Py_BuildValue("s", "FPS");
    PyDict_SetItem(pyParameters, pyFPSKey, pyFPS);

    return pyParameters;
}

FrameDecodingParameters CreateCFrameDecodingParameters(PyObject * pyParameters)
{
    FrameDecodingParameters parameters;
    parameters.maxQueueLength                       = PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "MaxQueueLength")));
    parameters.maxResultQueueLength                 = PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "MaxResultQueueLength")));
    parameters.width                                = PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "Width")));
    parameters.height                               = PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "Height")));
    parameters.stride                               = PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "Stride")));
    parameters.imagePixelFormat                     = PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "ImagePixelFormat")));
    parameters.region.regionBottom                  = PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "RegionBottom")));
    parameters.region.regionLeft                    = PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "RegionLeft")));
    parameters.region.regionRight                   = PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "RegionRight")));
    parameters.region.regionTop                     = PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "RegionTop")));
    parameters.region.regionMeasuredByPercentage    = PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "RegionMeasuredByPercentage")));
    parameters.threshold                            = (float)PyFloat_AsDouble(PyDict_GetItem(pyParameters, Py_BuildValue("s", "Threshold")));
    parameters.fps                                  = PyLong_AsLong(PyDict_GetItem(pyParameters, Py_BuildValue("s", "FPS")));

    return parameters;
}

#pragma region DeprecatedFunctions
/**
 * Set Dynamsoft Barcode Reader license. This API will be deprecated in a future version.
 * To get valid license, please contact support@dynamsoft.com
 * Invalid license is acceptable. With an invalid license, SDK will return an imcomplete result.
 */
static PyObject *
initLicense(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char *pszLicense;
    if (!PyArg_ParseTuple(args, "s", &pszLicense))
    {
        return NULL;
    }

    int ret = DBR_InitLicense(self->hBarcode, pszLicense);
    return Py_BuildValue("i", ret);
}

/**
 * This function will be deprecated in a future version.
*/
static PyObject *createPyResults(TextResultArray *pResults, const char* encoding)
{
    if (!pResults)
    {
        printf("No barcode detected\n");
        return NULL;
    }
    // Get barcode results
    int count = pResults->resultsCount;

    // Create a Python object to store results
    PyObject *list = PyList_New(count);
    // printf("count: %d\n", count);
    PyObject *result = NULL;
    int i = 0;
    for (; i < count; i++)
    {
        LocalizationResult *pLocalizationResult = pResults->results[i]->localizationResult;
        int x1 = pLocalizationResult->x1;
        int y1 = pLocalizationResult->y1;
        int x2 = pLocalizationResult->x2;
        int y2 = pLocalizationResult->y2;
        int x3 = pLocalizationResult->x3;
        int y3 = pLocalizationResult->y3;
        int x4 = pLocalizationResult->x4;
        int y4 = pLocalizationResult->y4;
        PyObject *pyObject = NULL;
        if (encoding) {
            pyObject = PyList_New(10);
        #ifdef IS_PY3K
            PyObject *format = PyUnicode_FromString(pResults->results[i]->barcodeFormatString);
        #else
            PyObject *format = PyString_FromString(pResults->results[i]->barcodeFormatString);
        #endif
            PyList_SetItem(pyObject, 0, format);
            
            PyObject *result = PyUnicode_Decode(pResults->results[i]->barcodeBytes, pResults->results[i]->barcodeBytesLength, encoding, "strict");
            if (result == NULL) 
            {
                char *hex = (char*)malloc(pResults->results[i]->barcodeBytesLength * 3 + 1);
                ToHexString(pResults->results[i]->barcodeBytes, pResults->results[i]->barcodeBytesLength, hex);
                printf("Hex Data: %s\n", hex);
                free(hex);

                PyErr_SetString(PyExc_TypeError, "Incorrect character set! Failed to decode barcode results!");
                DBR_FreeTextResults(&pResults);
                return NULL;
            }
            PyList_SetItem(pyObject, 1, result);

            PyObject *x1_pyobj = Py_BuildValue("i", x1);
            PyList_SetItem(pyObject, 2, x1_pyobj);

            PyObject *y1_pyobj = Py_BuildValue("i", y1);
            PyList_SetItem(pyObject, 3, y1_pyobj);

            PyObject *x2_pyobj = Py_BuildValue("i", x2);
            PyList_SetItem(pyObject, 4, x2_pyobj);

            PyObject *y2_pyobj = Py_BuildValue("i", y2);
            PyList_SetItem(pyObject, 5, y2_pyobj);

            PyObject *x3_pyobj = Py_BuildValue("i", x3);
            PyList_SetItem(pyObject, 6, x3_pyobj);

            PyObject *y3_pyobj = Py_BuildValue("i", y3);
            PyList_SetItem(pyObject, 7, y3_pyobj);

            PyObject *x4_pyobj = Py_BuildValue("i", x4);
            PyList_SetItem(pyObject, 8, x4_pyobj);

            PyObject *y4_pyobj = Py_BuildValue("i", y4);
            PyList_SetItem(pyObject, 9, y4_pyobj);

        }
        else
            pyObject = Py_BuildValue("ssiiiiiiii", pResults->results[i]->barcodeFormatString, pResults->results[i]->barcodeText, x1, y1, x2, y2, x3, y3, x4, y4);
        
        PyList_SetItem(list, i, pyObject); // Add results to list

        // Print out PyObject if needed
        if (DEBUG)
        {
#if defined(IS_PY3K)
            PyObject *objectsRepresentation = PyObject_Repr(list);
            const char *s = PyUnicode_AsUTF8(objectsRepresentation);
            printf("Results: %s\n", s);
#else
            PyObject *objectsRepresentation = PyObject_Repr(list);
            const char *s = PyString_AsString(objectsRepresentation);
            printf("Results: %s\n", s);
#endif
        }
    }

    // Release memory
    DBR_FreeTextResults(&pResults);

    return list;
}

/**
 * This function will deprecate in a future version.
*/
void updateFormat(DynamsoftBarcodeReader *self, int format)
{
    // Update DBR params
    PublicRuntimeSettings pSettings = {0};
    DBR_GetRuntimeSettings(self->hBarcode, &pSettings);
    pSettings.barcodeFormatIds = format;
    char szErrorMsgBuffer[256];
    DBR_UpdateRuntimeSettings(self->hBarcode, &pSettings, szErrorMsgBuffer, 256);
}

/**
 * Decode barcode from a file. This API will be deprecated in a future version.
 */
static PyObject *
decodeFile(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;
#if defined(_WIN32)
    printf("Windows\n");
#elif defined(__linux__)
    printf("Linux\n");
#elif defined(__APPLE__)
    printf("MacOS\n");
#else
    printf("Unknown Operating System.\n");
#endif

    char *pFileName; // File name
    int iFormat;     // Barcode formats
    char *templateName = NULL;
    char *encoding = NULL;
    if (!PyArg_ParseTuple(args, "si|ss", &pFileName, &iFormat, &templateName, &encoding))
    {
        return NULL;
    }

    updateFormat(self, iFormat);

    TextResultArray *pResults = NULL;

    // Barcode detection
    int ret = DBR_DecodeFile(self->hBarcode, pFileName, templateName ? templateName : "");
    if (ret)
    {
        printf("Detection error: %s\n", DBR_GetErrorString(ret));
    }
    DBR_GetAllTextResults(self->hBarcode, &pResults);

    // Wrap results
    PyObject *list = createPyResults(pResults, encoding);
    return list;
}

/**
 * Decode barcode from an image buffer. This API will be deprecated in a future version.
 */
static PyObject *
decodeBuffer(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    PyObject *o;
    int iFormat;
    char *templateName = NULL;
    char *encoding = NULL;
    int imagePixelFormat = IPF_RGB_888;
    if (!PyArg_ParseTuple(args, "Oi|iss", &o, &iFormat, &imagePixelFormat, &templateName, &encoding))
        return NULL;

    updateFormat(self, iFormat);

#if defined(IS_PY3K)
    //Refer to numpy/core/src/multiarray/ctors.c
    Py_buffer *view;
    int nd;
    PyObject *memoryview = PyMemoryView_FromObject(o);
    if (memoryview == NULL)
    {
        PyErr_Clear();
        return NULL;
    }

    view = PyMemoryView_GET_BUFFER(memoryview);
    char *buffer = (char *)(view->buf);
    nd = (int)(view->ndim);
    int len = (int)(view->len);
    int stride = (int)(view->strides[0]);
    int channels = (int)(view->strides[1]);
    int width = (int)(view->strides[0] / view->strides[1]);
    int height = len / stride;
#else

    PyObject *ao = PyObject_GetAttrString(o, "__array_struct__");

    if ((ao == NULL) || !PyCObject_Check(ao))
    {
        PyErr_SetString(PyExc_TypeError, "object does not have array interface");
        return NULL;
    }

    PyArrayInterface *pai = (PyArrayInterface *)PyCObject_AsVoidPtr(ao);

    if (pai->two != 2)
    {
        PyErr_SetString(PyExc_TypeError, "object does not have array interface");
        Py_DECREF(ao);
        return NULL;
    }

    // Get image information
    char *buffer = (char *)pai->data;  // The address of image data
    int width = (int)pai->shape[1];    // image width
    int height = (int)pai->shape[0];   // image height
    int channels = (int)pai->shape[2];
    int stride = (int)pai->strides[0]; // image stride
#endif

    // Initialize Dynamsoft Barcode Reader
    TextResultArray *pResults = NULL;

    PyObject *list = NULL;
    int ret = DBR_DecodeBuffer(self->hBarcode, buffer, width, height, stride, imagePixelFormat, templateName ? templateName : "");
    if (ret)
    {
        printf("Detection error: %s\n", DBR_GetErrorString(ret));
    }
    // Wrap results
    DBR_GetAllTextResults(self->hBarcode, &pResults);
    list = createPyResults(pResults, encoding);

#if defined(IS_PY3K)
    Py_DECREF(memoryview);
#else
    Py_DECREF(ao);
#endif

    return list;
}

/**
 * Decode file stream. This API will be deprecated in a future version.
 */
static PyObject *
decodeFileStream(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;
#if defined(_WIN32)
    printf("Windows\n");
#elif defined(__linux__)
    printf("Linux\n");
#elif defined(__APPLE__)
    printf("MacOS\n");
#else
    printf("Unknown Operating System.\n");
#endif

    PyObject *op; 
    int fileSize;
    int iFormat;     // Barcode formats
    char *templateName = NULL;
    char *encoding = NULL;
    if (!PyArg_ParseTuple(args, "Oii|ss", &op, &fileSize, &iFormat, &templateName, &encoding))
    {
        return NULL;
    }

    updateFormat(self, iFormat);

    TextResultArray *pResults = NULL;
    // https://docs.python.org/2/c-api/bytearray.html
    char *filestream = PyByteArray_AsString(op);
    // Barcode detection
    int ret = DBR_DecodeFileInMemory(self->hBarcode, filestream, fileSize, templateName ? templateName : "");
    if (ret)
    {
        printf("Detection error: %s\n", DBR_GetErrorString(ret));
    }
    DBR_GetAllTextResults(self->hBarcode, &pResults);

    // Wrap results
    PyObject *list = createPyResults(pResults, encoding);
    return list;
}

/**
 * Initializes barcode reader license from the license content on the client machine for offline verification. This API will be deprecated in a future version.
 *
 * @param pLicenseKey: The license key of Barcode Reader.
 * @param pLicenseContent: An encrypted string representing the license content (runtime number, expiry date, barcode type, etc.) obtained from the method DBR_OutputLicenseToString().
 *
 * @return Return 0 if the function operates successfully, otherwise call
 * 		   DBR_GetErrorString to get detail message.
 */
static PyObject *
initLicenseFromLicenseContent(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char *pszLicenseKey;
    char *pszLicenseContent;
    if (!PyArg_ParseTuple(args, "ss", &pszLicenseKey, &pszLicenseContent))
    {
        return NULL;
    }

    int ret = DBR_InitLicenseFromLicenseContent(self->hBarcode, pszLicenseKey, pszLicenseContent);
    return Py_BuildValue("i", ret);
}

/**
 * Outputs the license content as an encrypted string from the license server to be used for offline license verification. This API will be deprecated in a future version.
 *
 * @return if successful, return encypted string. Otherwise return error code. 
 */
static PyObject *
outputLicenseToString(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char content[512];
    int ret = DBR_OutputLicenseToString(self->hBarcode, content, 512);
    if (ret)
    {
        printf("%s\n", DBR_GetErrorString(ret));
        return Py_BuildValue("i", ret);
    }
    else
        return Py_BuildValue("s", content);
}

/**
 * Initializes barcode reader license from the license content on the client machine for offline verification. This API will be deprecated in a future version.
 *
 * @param pLicenseKey: The license key of Barcode Reader.
 * @param pLicenseContent: An encrypted string representing the license content (runtime number, expiry date, barcode type, etc.) obtained from the method DBR_OutputLicenseToString().
 *
 * @return Return 0 if the function operates successfully, otherwise call
 * 		   DBR_GetErrorString to get detail message.
 */
static PyObject *
initLicenseFromServer(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char *pszLicenseKey, *pLicenseServer;
    if (!PyArg_ParseTuple(args, "ss", &pLicenseServer, &pszLicenseKey))
    {
        return NULL;
    }

    int ret = DBR_InitLicenseFromServer(self->hBarcode, pLicenseServer, pszLicenseKey);
    return Py_BuildValue("i", ret);
}

/**
 * This function will be deprecated in a future version.
*/
static void setModeValue(DynamsoftBarcodeReader *self, PyObject *iter, char *mode)
{
    PublicRuntimeSettings pSettings = {0};
    DBR_GetRuntimeSettings(self->hBarcode, &pSettings);
    int index = 0;
    pSettings.furtherModes.grayscaleTransformationModes[0] = GTM_INVERTED;

    while (1)
    {
        PyObject *next = PyIter_Next(iter);
        if (!next)
        {
            break;
        }

        // Set attributes for different modes
        int attribute = PyLong_AsLong(next);
        if (!strcmp("grayscaleTransformationModes", mode))
        {
            // printf("Set grayscaleTransformationModes %d\n", attribute);
            pSettings.furtherModes.grayscaleTransformationModes[index] = attribute;
        }
        else if (!strcmp("colourClusteringModes", mode))
        {
            pSettings.furtherModes.colourClusteringModes[index] = attribute;
        }
        else if (!strcmp("colourConversionModes", mode))
        {
            pSettings.furtherModes.colourConversionModes[index] = attribute;
        }
        else if (!strcmp("regionPredetectionModes", mode))
        {
            pSettings.furtherModes.regionPredetectionModes[index] = attribute;
        }
        else if (!strcmp("imagePreprocessingModes ", mode))
        {
            pSettings.furtherModes.imagePreprocessingModes[index] = attribute;
        }
        else if (!strcmp("textureDetectionModes", mode))
        {
            pSettings.furtherModes.textureDetectionModes[index] = attribute;
        }
        else if (!strcmp("textFilterModes", mode))
        {
            pSettings.furtherModes.textFilterModes[index] = attribute;
        }
        else if (!strcmp("dpmCodeReadingModes", mode))
        {
            pSettings.furtherModes.dpmCodeReadingModes[index] = attribute;
        }
        else if (!strcmp("deformationResistingModes ", mode))
        {
            pSettings.furtherModes.deformationResistingModes[index] = attribute;
        }
        else if (!strcmp("barcodeComplementModes ", mode))
        {
            pSettings.furtherModes.barcodeComplementModes[index] = attribute;
        }
        else if (!strcmp("barcodeColourModes ", mode))
        {
            pSettings.furtherModes.barcodeColourModes[index] = attribute;
        }
        else if (!strcmp("textAssistedCorrectionMode", mode))
        {
            pSettings.furtherModes.textAssistedCorrectionMode = attribute;
        }

        ++index;
    }

    char szErrorMsgBuffer[256];
    DBR_UpdateRuntimeSettings(self->hBarcode, &pSettings, szErrorMsgBuffer, 256);
}

/**
 * Set modes for different scenarios. This API will be deprecated in a future version.
 *
 * @param mode: The mode name. E.g. dbr.GRAY_SCALE_TRANSFORMATION_MODE
 * @param values: A list of enumeration items. E.g. [dbr.GTM_INVERTED, dbr.GTM_ORIGINAL]
 *
 * @return Return NULL if failed.
 */
static PyObject *
setFurtherModes(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char *mode;
    PyObject *value;
    if (!PyArg_ParseTuple(args, "sO", &mode, &value))
    {
        return NULL;
    }

    PyObject *iter = PyObject_GetIter(value);
    if (!iter)
    {
        printf("Please input a list\n");
        return NULL;
    }

    setModeValue(self, iter, mode);
    return Py_BuildValue("i", 0);
}

/**
 * Set public settings with JSON object. This API will be deprecated in a future version.
 *
 * @param json: the stringified JSON object.
 * 
 * @return Return 0 if the function operates successfully.
 */
static PyObject *
setParameters(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char *json;
    if (!PyArg_ParseTuple(args, "s", &json))
    {
        return NULL;
    }

    char errorMessage[DEFAULT_MEMORY_SIZE];
    int ret = DBR_InitRuntimeSettingsWithString(self->hBarcode, json, CM_OVERWRITE, errorMessage, 256);
    if (ret) 
    {
        printf("Returned value: %d, error message: %s\n", ret, errorMessage);
        PyErr_SetString(PyExc_TypeError, "DBR_InitRuntimeSettingsWithString() failed");
        return NULL;
    }
    return Py_BuildValue("i", ret);
}

/**
 * Get public settings. This API will be deprecated in a future version.
 *
 * @return Return stringified JSON object.
 */
static PyObject *
getParameters(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char errorMessage[DEFAULT_MEMORY_SIZE];
    char pContent[DEFAULT_MEMORY_SIZE];

    int ret = DBR_OutputSettingsToString(self->hBarcode, pContent, DEFAULT_MEMORY_SIZE, "currentRuntimeSettings");
    // printf("pContent: %s\n, string len: %d", pContent, strlen(pContent));
    if (ret) 
    {
        printf("Returned value: %d, error message: %s\n", ret, errorMessage);
        PyErr_SetString(PyExc_TypeError, "DBR_OutputSettingsToString() failed");
        return NULL;
    }
    return Py_BuildValue("s", pContent);
}

/**
 * This function will deprecate in a future version.
*/
void onResultCallback(int frameId, TextResultArray *pResults, void *pUser)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)pUser;
    // Get barcode results
    int count = pResults->resultsCount;
    int i = 0;

    // https://docs.python.org/2/c-api/init.html
    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    PyObject *list = PyList_New(count);
    for (; i < count; i++)
    {
        LocalizationResult *pLocalizationResult = pResults->results[i]->localizationResult;
        int x1 = pLocalizationResult->x1;
        int y1 = pLocalizationResult->y1;
        int x2 = pLocalizationResult->x2;
        int y2 = pLocalizationResult->y2;
        int x3 = pLocalizationResult->x3;
        int y3 = pLocalizationResult->y3;
        int x4 = pLocalizationResult->x4;
        int y4 = pLocalizationResult->y4;

        PyObject *pyObject = Py_BuildValue("ssiiiiiiii", pResults->results[i]->barcodeFormatString, pResults->results[i]->barcodeText, x1, y1, x2, y2, x3, y3, x4, y4);
        PyList_SetItem(list, i, pyObject); // Add results to list
    }

    PyObject *result = PyObject_CallFunction(self->py_callback, "O", list);
    if (result == NULL)
        return;
    Py_DECREF(result);

    PyGILState_Release(gstate);
    /////////////////////////////////////////////

    // Release memory
    DBR_FreeTextResults(&pResults);
}

/**
 * Read barcodes from continuous video frames. This API will be deprecated in a future version.
 */
static PyObject *
startVideoMode(PyObject *obj, PyObject *args)
{
    printf("Start the video mode\n");
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    PyObject *callback = NULL;
    int maxListLength, maxResultListLength, width, height, stride, iFormat;
    int imagePixelFormat = IPF_RGB_888;
    if (!PyArg_ParseTuple(args, "iiiiiiO|i", &maxListLength, &maxResultListLength, &width, &height, &stride, &iFormat, &callback, &imagePixelFormat))
    {
        return NULL;
    }

    updateFormat(self, iFormat);

    if (!PyCallable_Check(callback))
    {
        PyErr_SetString(PyExc_TypeError, "parameter must be callable");
        return NULL;
    }
    else
    {
        Py_XINCREF(callback);    /* Add a reference to new callback */
        Py_XDECREF(self->py_callback); /* Dispose of previous callback */
        self->py_callback = callback;
    }


    DBR_SetTextResultCallback(self->hBarcode, onResultCallback, self);

    int ret = DBR_StartFrameDecoding(self->hBarcode, maxListLength, maxResultListLength, width, height, stride, imagePixelFormat, "");
    return Py_BuildValue("i", ret);
}

/**
 * This API will be deprecated in a future version.
*/
static PyObject *
stopVideoMode(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;
    printf("Stop the video mode\n");
    if (self->hBarcode)
    {
        int ret = DBR_StopFrameDecoding(self->hBarcode);
        return Py_BuildValue("i", ret);
    }

    return 0;
}

/**
 * This API will be deprecated in a future version.
*/
static PyObject *
appendVideoFrame(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    PyObject *o;
    if (!PyArg_ParseTuple(args, "O", &o))
        return NULL;

#if defined(IS_PY3K)
    //Refer to numpy/core/src/multiarray/ctors.c
    Py_buffer *view;
    PyObject *memoryview = PyMemoryView_FromObject(o);
    if (memoryview == NULL)
    {
        PyErr_Clear();
        return NULL;
    }

    view = PyMemoryView_GET_BUFFER(memoryview);
    unsigned char *buffer = (unsigned char *)(view->buf);

#else

    PyObject *ao = PyObject_GetAttrString(o, "__array_struct__");

    if ((ao == NULL) || !PyCObject_Check(ao))
    {
        PyErr_SetString(PyExc_TypeError, "object does not have array interface");
        return NULL;
    }

    PyArrayInterface *pai = (PyArrayInterface *)PyCObject_AsVoidPtr(ao);

    if (pai->two != 2)
    {
        PyErr_SetString(PyExc_TypeError, "object does not have array interface");
        Py_DECREF(ao);
        return NULL;
    }

    // Get image information
    unsigned char *buffer = (unsigned char *)pai->data; // The address of image data

#endif

    int frameId = DBR_AppendFrame(self->hBarcode, buffer);
    return 0;
}

#pragma endregion

/**
 * Set Dynamsoft Barcode Reader license.  
 * To get valid license, please contact support@dynamsoft.com
 * Invalid license is acceptable. With an invalid license, SDK will return an imcomplete result.
 *
 * @return Returns error code. Returns 0 if the function operates successfully.
 */
static PyObject * InitLicense(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char *pszLicense;
    if (!PyArg_ParseTuple(args, "s", &pszLicense))
    {
        return NULL;
    }

    int ret = DBR_InitLicense(self->hBarcode, pszLicense);
    const char* errorString = DBR_GetErrorString(ret);
    printf("%s\n", errorString);
    return Py_BuildValue("i", ret);
}

/**
 * Gets current settings and save them into a dictionary.
 *
 * @return Return current runtime settings.
 */
static PyObject * GetRuntimeSettings(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    PublicRuntimeSettings settings;
    int errorCode = DBR_GetRuntimeSettings(self->hBarcode, &settings);

    PyObject * pySettings = CreatePyRuntimeSettings(settings);

    return pySettings;
}

/**
 * Updates runtime settings with a given dictionary.
 *
 * @param [in] settings Dictionary The dictionary of template settings.
 * 
 * @return Returns error code. Returns 0 if the function operates successfully.
 */
static PyObject * UpdataRuntimeSettings(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;
    PyObject *pyParameters;
    if (!PyArg_ParseTuple(args, "O", &pyParameters))
    {
        return NULL;
    }
    if(!PyDict_Check(pyParameters))
    {
        printf("the parameter should be a dictionary.");
        return NULL;
    }
    PublicRuntimeSettings settings = CreateCRuntimeSettings(pyParameters);
    char szErrorMsgBuffer[256];
    int errorCode = DBR_UpdateRuntimeSettings(self->hBarcode, &settings, szErrorMsgBuffer, 256);
    if(errorCode != 0)
    {
        printf("Error:%s\n", szErrorMsgBuffer);
    }
    else
    {
        printf("Successful!\n");
    }
    return Py_BuildValue("i", errorCode);
}

/**
 * Resets all parameters to default values.
 *
 */
static PyObject * ResetRuntimeSettings(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    DBR_ResetRuntimeSettings(self->hBarcode);

    return NULL;
}

/**
 * Sets the optional argument for a specified mode in Modes parameters.
 *
 * @param [in] modesName String The mode parameter name to set argument.
 * @param [in] index LONG The array index of mode parameter to indicate a specific mode.
 * @param [in] argumentName String The name of the argument to set.
 * @param [in] argumentValue String The value of the argument to set.
 * 
 * @return Returns error code. Returns 0 if the function operates successfully.
 */
static PyObject * SetModeArgument(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;
    char * pModesName;
    int index;
    char * pArgumentName;
    char * pArgumentValue;
    if (!PyArg_ParseTuple(args, "siss", &pModesName, &index, &pArgumentName, &pArgumentValue))
    {
        return NULL;
    }
    char szErrorMsgBuffer[256];
    int errorCode = DBR_SetModeArgument(self->hBarcode, pModesName, index, pArgumentName, pArgumentValue, szErrorMsgBuffer, 256);
    if(errorCode != 0)
    {
        printf("Error:%s\n", szErrorMsgBuffer);
    }
    else
    {
        printf("Successful!\n");
    }
    return Py_BuildValue("i", errorCode);
}

/**
 * Gets the optional argument for a specified mode in Modes parameters.
 *
 * @param [in] modesName String The mode parameter name to set argument.
 * @param [in] index LONG The array index of mode parameter to indicate a specific mode.
 * @param [in] argumentName String The name of the argument to set.
 * 
 * @return Returns error code. Returns 0 if the function operates successfully.
 */
static PyObject * GetModeArgument(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;
    char * pModesName;
    int index;
    char * pArgumentName;
    if (!PyArg_ParseTuple(args, "sis", &pModesName, &index, &pArgumentName))
    {
        return NULL;
    }
    char szErrorMsgBuffer[256];
    char pArgumentValue[512];
    int errorCode = DBR_GetModeArgument(self->hBarcode, pModesName, index, pArgumentName, pArgumentValue, 512, szErrorMsgBuffer, 256);
    if(errorCode != 0)
    {
        printf("Error:%s\n", szErrorMsgBuffer);
        return NULL;
    }
    else
    {
        printf("Successful!\n");
    }
    return Py_BuildValue("s", pArgumentValue);
}

/**
 * Decode barcode from a file 
 * 
 * @param [in] filename String The file name.
 * @param [in] templateName String The template name.
 * 
 * @return Returns a dictionary which includes text results and intermediate results.
 */
static PyObject * DecodeFile(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char *pFileName; // File name
    char *templateName = NULL;
    // char *encoding = NULL;
    if (!PyArg_ParseTuple(args, "s|s", &pFileName, &templateName))
    {
        return NULL;
    }

    TextResultArray *pResults = NULL;
    if(templateName == NULL)
    {
        templateName = "";
    }

    // Barcode detection
    int ret = DBR_DecodeFile(self->hBarcode, pFileName, templateName);
    if (ret)
    {
        printf("Detection error: %s\n", DBR_GetErrorString(ret));
    }
    DBR_GetAllTextResults(self->hBarcode, &pResults);
    IntermediateResultArray * pIResults = NULL;
    DBR_GetIntermediateResults(self->hBarcode, &pIResults);

    // Wrap results
    PyObject * results = PyDict_New();

    PyObject * pyTextResults = CreatePyTextResults(pResults);
    PyObject * pyTextResultsKey = Py_BuildValue("s","TextResults");
    PyDict_SetItem(results, pyTextResultsKey, pyTextResults);
    PyObject * pyIntermediateResults = CreatePyIntermediateResults(pIResults);
    PyObject * pyIntermediateResultsKey = Py_BuildValue("s","IntermediateResults");
    PyDict_SetItem(results, pyIntermediateResultsKey, pyIntermediateResults);

    return results;
}

/**
 * Decode barcode from an image buffer. 
 * @param [in] frame-by-opencv-capture.
 * 
 * @return Returns a dictionary which includes text results and intermediate results.
 */
static PyObject * DecodeBuffer(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    PyObject *o;
    char *templateName = NULL;
    int width, height, stride;
    int imagePixelFormat = IPF_RGB_888;
    // char *encoding = NULL;
    if (!PyArg_ParseTuple(args, "Oiii|is", &o, &height, &width, &stride, &imagePixelFormat, &templateName))
        return NULL;


#if defined(IS_PY3K)
    //Refer to numpy/core/src/multiarray/ctors.c
    Py_buffer *view;
    // int nd;
    PyObject *memoryview = PyMemoryView_FromObject(o);
    if (memoryview == NULL)
    {
        PyErr_Clear();
        return NULL;
    }

    view = PyMemoryView_GET_BUFFER(memoryview);
    char *buffer = (char *)(view->buf);
    // nd = (int)(view->ndim);
    // int len = (int)(view->len);
    // int stride = (int)(view->strides[0]);
    // int width = (int)(view->strides[0] / view->strides[1]);
    // int height = len / stride;
#else

    PyObject *ao = PyObject_GetAttrString(o, "__array_struct__");

    if ((ao == NULL) || !PyCObject_Check(ao))
    {
        PyErr_SetString(PyExc_TypeError, "object does not have array interface");
        return NULL;
    }

    PyArrayInterface *pai = (PyArrayInterface *)PyCObject_AsVoidPtr(ao);

    if (pai->two != 2)
    {
        PyErr_SetString(PyExc_TypeError, "object does not have array interface");
        Py_DECREF(ao);
        return NULL;
    }

    // Get image information
    char *buffer = (char *)pai->data;  // The address of image data
    // int width = (int)pai->shape[1];    // image width
    // int height = (int)pai->shape[0];   // image height
    // int channels = (int)pai->shape[2];
    // int stride = (int)pai->strides[0]; // image stride
#endif

    // Initialize Dynamsoft Barcode Reader
    TextResultArray *pResults = NULL;

    if(templateName == NULL)
    {
        templateName = "";
    }
    int ret = DBR_DecodeBuffer(self->hBarcode, buffer, width, height, stride, imagePixelFormat, templateName);
    if (ret)
    {
        printf("Detection error: %s\n", DBR_GetErrorString(ret));
    }
    // Wrap results
    DBR_GetAllTextResults(self->hBarcode, &pResults);
    IntermediateResultArray * pIResults = NULL;
    DBR_GetIntermediateResults(self->hBarcode, &pIResults);

    // Wrap results
    PyObject * results = PyDict_New();

    PyObject * pyTextResults = CreatePyTextResults(pResults);
    PyObject * pyTextResultsKey = Py_BuildValue("s","TextResults");
    PyDict_SetItem(results, pyTextResultsKey, pyTextResults);
    // PyObject * pyIntermediateResults = CreatePyIntermediateResults(pIResults);
    // PyObject * pyIntermediateResultsKey = Py_BuildValue("s","IntermediateResults");
    // PyDict_SetItem(results, pyIntermediateResultsKey, pyIntermediateResults);

#if defined(IS_PY3K)
    Py_DECREF(memoryview);
#else
    Py_DECREF(ao);
#endif

    return results;
}

/**
 * Decode file stream.
 * @param [in] fileStream ByteArray The image file bytes in memory.
 * @param [in] fileSize LONG The length of the file bytes in memory.
 * 
 * @return Returns a dictionary which includes text results and intermediate results.
 */
static PyObject * DecodeFileStream(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    PyObject *op; 
    int fileSize;
    char *templateName = NULL;
    // char *encoding = NULL;
    if (!PyArg_ParseTuple(args, "Oi|s", &op, &fileSize, &templateName))
    {
        return NULL;
    }

    TextResultArray *pResults = NULL;
    // https://docs.python.org/2/c-api/bytearray.html
    char *filestream = PyByteArray_AsString(op);
    if(templateName == NULL)
    {
        templateName = "";
    }
    // Barcode detection
    int ret = DBR_DecodeFileInMemory(self->hBarcode, filestream, fileSize, templateName);
    if (ret)
    {
        printf("Detection error: %s\n", DBR_GetErrorString(ret));
    }
    DBR_GetAllTextResults(self->hBarcode, &pResults);
    IntermediateResultArray * pIResults = NULL;
    DBR_GetIntermediateResults(self->hBarcode, &pIResults);

    // Wrap results
    PyObject * results = PyDict_New();

    PyObject * pyTextResults = CreatePyTextResults(pResults);
    PyObject * pyTextResultsKey = Py_BuildValue("s","TextResults");
    PyDict_SetItem(results, pyTextResultsKey, pyTextResults);
    // PyObject * pyIntermediateResults = CreatePyIntermediateResults(pIResults);
    // PyObject * pyIntermediateResultsKey = Py_BuildValue("s","IntermediateResults");
    // PyDict_SetItem(results, pyIntermediateResultsKey, pyIntermediateResults);

    return results;
}


void OnResultCallback(int frameId, TextResultArray *pResults, void *pUser)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)pUser;
    // Get barcode results
    int count = pResults->resultsCount;
    int i = 0;

    // https://docs.python.org/2/c-api/init.html
    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();

    PyObject * pyTextResults = CreatePyTextResults(pResults);
    if(pyTextResults != NULL)
    {
        PyObject * result = PyObject_CallFunction(self->py_callback, "O", pyTextResults);
        if (result != NULL)
            Py_DECREF(result);
    }

    // PyObject *list = PyList_New(count);
    // for (; i < count; i++)
    // {
    //     LocalizationResult *pLocalizationResult = pResults->results[i]->localizationResult;
    //     int x1 = pLocalizationResult->x1;
    //     int y1 = pLocalizationResult->y1;
    //     int x2 = pLocalizationResult->x2;
    //     int y2 = pLocalizationResult->y2;
    //     int x3 = pLocalizationResult->x3;
    //     int y3 = pLocalizationResult->y3;
    //     int x4 = pLocalizationResult->x4;
    //     int y4 = pLocalizationResult->y4;

    //     PyObject *tempObject = Py_BuildValue("ssiiiiiiii", pResults->results[i]->barcodeFormatString, pResults->results[i]->barcodeText, x1, y1, x2, y2, x3, y3, x4, y4);
    //     PyList_SetItem(list, i, tempObject); // Add results to list
    // }
    

    // PyObject * result = PyObject_CallFunction(self->py_callback, "O", list);
    // if (result != NULL)
    //     Py_DECREF(result);

    PyGILState_Release(gstate);
    /////////////////////////////////////////////

    // Release memory
    // DBR_FreeTextResults(&pResults);
}

// static PyObject * SetErrorCallback(PyObject *obj, PyObject *args)
// {
//     DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

//     PyObject * callBackFunc = NULL;
//     PyObject * pyUserData = NULL;

//     if (!PyArg_ParseTuple(args, "OO", &callBackFunc, &pyUserData))
//     {
//         return NULL;
//     }

//     if (!PyCallable_Check(callBackFunc))
//     {
//         PyErr_SetString(PyExc_TypeError, "parameter must be callable");
//         return NULL;
//     }
//     else
//     {
//         Py_XINCREF(callBackFunc);    /* Add a reference to new callback */
//         Py_XDECREF(self->py_callback); /* Dispose of previous callback */
//         self->py_callback = callback;
//     }

//     DBR_SetTextResultCallback(self->hBarcode, OnResultCallback, (void*)pyUserData);
// }

// static PyObject * SetTextResultCallback(PyObject *obj, PyObject *args)
// {

// }

// static PyObject * SetIntermediateResultCallback(PyObject *obj, PyObject *args)
// {

// }

/**
* Init frame decoding parameters.
*/
static PyObject * InitFrameDecodingParameters(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;
    FrameDecodingParameters pSettings;
    DBR_InitFrameDecodingParameters(self->hBarcode, &pSettings);
    PyObject * frameParameters = CreatePyFrameDecodingParameters(&pSettings);
    return frameParameters;
}

/**
 * Read barcodes from continuous video frames
 */
static PyObject * StartVideoMode(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    PyObject *pyParameters = NULL;
    PyObject *callback = NULL;
    char * templateName = NULL;
    if (!PyArg_ParseTuple(args, "OO|s",&pyParameters, &callback, &templateName))
    {
        return NULL;
    }

    if(!PyDict_Check(pyParameters))
    {
        printf("the first parameter should be a dictionary.");
        return NULL;
    }
    if (!PyCallable_Check(callback))
    {
        PyErr_SetString(PyExc_TypeError, "parameter must be callable");
        return NULL;
    }
    else
    {
        Py_XINCREF(callback);    /* Add a reference to new callback */
        Py_XDECREF(self->py_callback); /* Dispose of previous callback */
        self->py_callback = callback;
    }

    DBR_SetTextResultCallback(self->hBarcode, OnResultCallback, self);
    FrameDecodingParameters parameters = CreateCFrameDecodingParameters(pyParameters);
    if(templateName == NULL)
    {
        templateName = "";
    }
    int ret = DBR_StartFrameDecodingEx(self->hBarcode, parameters, templateName);
    return Py_BuildValue("i", ret);
}

static PyObject * StopVideoMode(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;
    printf("Stop the video mode\n");
    if (self->hBarcode)
    {
        int ret = DBR_StopFrameDecoding(self->hBarcode);
        return Py_BuildValue("i", ret);
    }

    return 0;
}

static PyObject * AppendVideoFrame(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    PyObject *o;
    if (!PyArg_ParseTuple(args, "O", &o))
        return NULL;

#if defined(IS_PY3K)
    //Refer to numpy/core/src/multiarray/ctors.c
    Py_buffer *view;
    PyObject *memoryview = PyMemoryView_FromObject(o);
    if (memoryview == NULL)
    {
        PyErr_Clear();
        return NULL;
    }

    view = PyMemoryView_GET_BUFFER(memoryview);
    unsigned char *buffer = (unsigned char *)view->buf;

#else

    PyObject *ao = PyObject_GetAttrString(o, "__array_struct__");

    if ((ao == NULL) || !PyCObject_Check(ao))
    {
        PyErr_SetString(PyExc_TypeError, "object does not have array interface");
        return NULL;
    }

    PyArrayInterface *pai = (PyArrayInterface *)PyCObject_AsVoidPtr(ao);

    if (pai->two != 2)
    {
        PyErr_SetString(PyExc_TypeError, "object does not have array interface");
        Py_DECREF(ao);
        return NULL;
    }

    // Get image information
    unsigned char *buffer = (unsigned char *)pai->data; // The address of image data

#endif

    int frameId = DBR_AppendFrame(self->hBarcode, buffer);
    return 0;
}

/**
 * Initializes barcode reader license from the license content on the client machine for offline verification.
 *
 * @param pLicenseKey: The license key of Barcode Reader.
 * @param pLicenseContent: An encrypted string representing the license content (runtime number, expiry date, barcode type, etc.) obtained from the method DBR_OutputLicenseToString().
 *
 * @return Return 0 if the function operates successfully, otherwise call
 * 		   DBR_GetErrorString to get detail message.
 */
static PyObject * InitLicenseFromLicenseContent(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char *pszLicenseKey;
    char *pszLicenseContent;
    if (!PyArg_ParseTuple(args, "ss", &pszLicenseKey, &pszLicenseContent))
    {
        return NULL;
    }

    int ret = DBR_InitLicenseFromLicenseContent(self->hBarcode, pszLicenseKey, pszLicenseContent);
    const char* errorString = DBR_GetErrorString(ret);
    printf("%s",errorString);
    return Py_BuildValue("i", ret);
}

/**
 * Outputs the license content as an encrypted string from the license server to be used for offline license verification.
 *
 * @return if successful, return encypted string. Otherwise return error code. 
 */
static PyObject * OutputLicenseToString(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char* content = NULL;
    int ret = DBR_OutputLicenseToStringPtr(self->hBarcode, &content);
    if (ret)
    {
        printf("%s\n", DBR_GetErrorString(ret));
        return Py_BuildValue("i", ret);
    }
    else
    {
        PyObject * licenseString = Py_BuildValue("s", content);
        DBR_FreeLicenseString(&content);
        return licenseString;
    }
}

/**
 * Initializes barcode reader license from the license content on the client machine for offline verification.
 *
 * @param pLicenseKey: The license key of Barcode Reader.
 * @param pLicenseContent: An encrypted string representing the license content (runtime number, expiry date, barcode type, etc.) obtained from the method DBR_OutputLicenseToString().
 *
 * @return Return 0 if the function operates successfully, otherwise call
 * 		   DBR_GetErrorString to get detail message.
 */
static PyObject * InitLicenseFromServer(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char *pszLicenseKey, *pLicenseServer;
    if (!PyArg_ParseTuple(args, "ss", &pLicenseServer, &pszLicenseKey))
    {
        return NULL;
    }

    int ret = DBR_InitLicenseFromServer(self->hBarcode, pLicenseServer, pszLicenseKey);
    const char* errorString = DBR_GetErrorString(ret);
    printf("%s",errorString);
    return Py_BuildValue("i", ret);
}

/**
 * Set public settings with JSON object.
 *
 * @param json: the stringified JSON object.
 * 
 * @return Return 0 if the function operates successfully.
 */
static PyObject * InitRuntimeSettingsByJsonString(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char *json;
    if (!PyArg_ParseTuple(args, "s", &json))
    {
        return NULL;
    }

    char errorMessage[DEFAULT_MEMORY_SIZE];
    int ret = DBR_InitRuntimeSettingsWithString(self->hBarcode, json, CM_OVERWRITE, errorMessage, 256);
    if (ret) 
    {
        printf("Returned value: %d, error message: %s\n", ret, errorMessage);
        PyErr_SetString(PyExc_TypeError, "DBR_InitRuntimeSettingsWithString() failed");
        return Py_BuildValue("i", ret);
    }
    return Py_BuildValue("i", ret);
}

/**
 * Set public settings with JSON object.
 *
 * @param jsonPath: the JSON file's path.
 * 
 * @return Return 0 if the function operates successfully.
 */
static PyObject * InitRuntimeSettingsByJsonFile(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char *jsonPath;
    if (!PyArg_ParseTuple(args, "s", &jsonPath))
    {
        return NULL;
    }

    char errorMessage[512];
    int ret = DBR_InitRuntimeSettingsWithFile(self->hBarcode, jsonPath, CM_OVERWRITE, errorMessage, 512);
    if (ret) 
    {
        printf("Returned value: %d, error message: %s\n", ret, errorMessage);
        PyErr_SetString(PyExc_TypeError, "DBR_InitRuntimeSettingsWithFile() failed");
        return Py_BuildValue("i", ret);
    }
    return Py_BuildValue("i", ret);
}

/**
 * Get public settings.
 *
 * @return Return stringified JSON object.
 */
static PyObject * OutputSettingsToJsonString(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char errorMessage[DEFAULT_MEMORY_SIZE];
    char * pContent = NULL;

    int ret = DBR_OutputSettingsToStringPtr(self->hBarcode, &pContent, "CurrentRuntimeSettings");
    // printf("pContent: %s\n, string len: %d", pContent, strlen(pContent));
    if (ret) 
    {
        printf("Returned value: %d, error message: %s\n", ret, errorMessage);
        PyErr_SetString(PyExc_TypeError, "DBR_OutputSettingsToStringPtr() failed");
        return NULL;
    }
    PyObject * content = Py_BuildValue("s", pContent);
    DBR_FreeSettingsString(&pContent);
    return content;
}

/**
 * Get public settings to a json file.
 *
 */
static PyObject * OutputSettingsToJsonFile(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char * jsonPath;
    if (!PyArg_ParseTuple(args, "s", &jsonPath))
    {
        return NULL;
    }
    char errorMessage[DEFAULT_MEMORY_SIZE];

    int ret = DBR_OutputSettingsToFile(self->hBarcode, jsonPath, "CurrentRuntimeSettings");
    if (ret) 
    {
        printf("Returned value: %d, error message: %s\n", ret, errorMessage);
        PyErr_SetString(PyExc_TypeError, "DBR_OutputSettingsToFile() failed");
        return Py_BuildValue("i", ret);
    }
    return Py_BuildValue("i", ret);
}

static PyObject * AppendTplFileToRuntimeSettings(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char *jsonPath;
    int conflictMode;
    if (!PyArg_ParseTuple(args, "si", &jsonPath, &conflictMode))
    {
        return NULL;
    }

    char errorMessage[512];
    int ret = DBR_AppendTplFileToRuntimeSettings(self->hBarcode, jsonPath, conflictMode, errorMessage, 512);
    if (ret) 
    {
        printf("Returned value: %d, error message: %s\n", ret, errorMessage);
        PyErr_SetString(PyExc_TypeError, "DBR_AppendTplFileToRuntimeSettings() failed");
        return Py_BuildValue("i", ret);
    }
    return Py_BuildValue("i", ret);
}

static PyObject * AppendTplStringToRuntimeSettings(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    char *json;
    int conflictMode;
    if (!PyArg_ParseTuple(args, "si", &json, &conflictMode))
    {
        return NULL;
    }

    char errorMessage[512];
    int ret = DBR_AppendTplStringToRuntimeSettings(self->hBarcode, json, conflictMode, errorMessage, 512);
    if (ret) 
    {
        printf("Returned value: %d, error message: %s\n", ret, errorMessage);
        PyErr_SetString(PyExc_TypeError, "DBR_AppendTplStringToRuntimeSettings() failed");
        return Py_BuildValue("i", ret);
    }
    return Py_BuildValue("i", ret);
}

static PyObject * GetAllTemplateNames(PyObject *obj, PyObject *args)
{
    DynamsoftBarcodeReader *self = (DynamsoftBarcodeReader *)obj;

    int count = DBR_GetParameterTemplateCount(self->hBarcode);
    PyObject * nameList = PyList_New(count);
    for(int i = 0; i < count; ++i)
    {
        char templateName[256];
        DBR_GetParameterTemplateName(self->hBarcode, i, templateName, 256);
        PyObject * pyTemplateName = Py_BuildValue("s", templateName);
        PyList_SetItem(nameList, i, pyTemplateName);
    }
    return nameList;
}

static PyMemberDef dbr_members[] = {
    {"COLOR_CLUTERING_MODE",                    T_OBJECT_EX, offsetof(DynamsoftBarcodeReader, COLOR_CLUTERING_MODE), 0, NULL},
    {"COLOR_CONVERSION_MODE",                   T_OBJECT_EX, offsetof(DynamsoftBarcodeReader, COLOR_CONVERSION_MODE), 0, NULL},
    {"GRAY_SCALE_TRANSFORMATION_MODE",          T_OBJECT_EX, offsetof(DynamsoftBarcodeReader, GRAY_SCALE_TRANSFORMATION_MODE), 0, NULL},
    {"REGION_PREDETECTION_MODE",                T_OBJECT_EX, offsetof(DynamsoftBarcodeReader, REGION_PREDETECTION_MODE), 0, NULL},
    {"IMAGE_PREPROCESSING_MODE",                T_OBJECT_EX, offsetof(DynamsoftBarcodeReader, IMAGE_PREPROCESSING_MODE), 0, NULL},
    {"TEXTURE_DETECTION_MODE",                  T_OBJECT_EX, offsetof(DynamsoftBarcodeReader, TEXTURE_DETECTION_MODE), 0, NULL},
    {"TEXTURE_FILTER_MODE",                     T_OBJECT_EX, offsetof(DynamsoftBarcodeReader, TEXTURE_FILTER_MODE), 0, NULL},
    {"TEXT_ASSISTED_CORRECTION_MODE",           T_OBJECT_EX, offsetof(DynamsoftBarcodeReader, TEXT_ASSISTED_CORRECTION_MODE), 0, NULL},
    {"DPM_CODE_READING_MODE",                   T_OBJECT_EX, offsetof(DynamsoftBarcodeReader, DPM_CODE_READING_MODE), 0, NULL},
    {"DEFORMATION_RESISTING_MODE",              T_OBJECT_EX, offsetof(DynamsoftBarcodeReader, DEFORMATION_RESISTING_MODE), 0, NULL},
    {"BARCODE_COMPLEMENT_MODE",                 T_OBJECT_EX, offsetof(DynamsoftBarcodeReader, BARCODE_COMPLEMENT_MODE), 0, NULL},
    {"BARCODE_COLOR_MODE",                      T_OBJECT_EX, offsetof(DynamsoftBarcodeReader, BARCODE_COLOR_MODE), 0, NULL},
    {"GTM_INVERTED",                            T_INT, offsetof(DynamsoftBarcodeReader, GTM_INVERTED), 0, NULL},
    {"GTM_ORIGINAL",                            T_INT, offsetof(DynamsoftBarcodeReader, GTM_ORIGINAL), 0, NULL},
    {"GTM_SKIP",                                T_INT, offsetof(DynamsoftBarcodeReader, GTM_SKIP), 0, NULL},
    {"BF_ALL",                                  T_INT, offsetof(DynamsoftBarcodeReader, BF_ALL), 0, NULL},
    {"BF_ONED",                                 T_INT, offsetof(DynamsoftBarcodeReader, BF_ONED), 0, NULL},
    {"BF_GS1_DATABAR",                          T_INT, offsetof(DynamsoftBarcodeReader, BF_GS1_DATABAR), 0, NULL},
    {"BF_POSTALCODE",                           T_INT, offsetof(DynamsoftBarcodeReader, BF_POSTALCODE), 0, NULL},
    {"BF_CODE_39",                              T_INT, offsetof(DynamsoftBarcodeReader, BF_CODE_39), 0, NULL},
    {"BF_CODE_128",                             T_INT, offsetof(DynamsoftBarcodeReader, BF_CODE_128), 0, NULL},
    {"BF_CODE_93",                              T_INT, offsetof(DynamsoftBarcodeReader, BF_CODE_93), 0, NULL},
    {"BF_CODABAR",                              T_INT, offsetof(DynamsoftBarcodeReader, BF_CODABAR), 0, NULL},
    {"BF_ITF",                                  T_INT, offsetof(DynamsoftBarcodeReader, BF_ITF), 0, NULL},
    {"BF_EAN_13",                               T_INT, offsetof(DynamsoftBarcodeReader, BF_EAN_13), 0, NULL},
    {"BF_EAN_8",                                T_INT, offsetof(DynamsoftBarcodeReader, BF_EAN_8), 0, NULL},
    {"BF_UPC_A",                                T_INT, offsetof(DynamsoftBarcodeReader, BF_UPC_A), 0, NULL},
    {"BF_UPC_E",                                T_INT, offsetof(DynamsoftBarcodeReader, BF_UPC_E), 0, NULL},
    {"BF_INDUSTRIAL_25",                        T_INT, offsetof(DynamsoftBarcodeReader, BF_INDUSTRIAL_25), 0, NULL},
    {"BF_CODE_39_EXTENDED",                     T_INT, offsetof(DynamsoftBarcodeReader, BF_CODE_39_EXTENDED), 0, NULL},
    {"BF_GS1_DATABAR_OMNIDIRECTIONAL",          T_INT, offsetof(DynamsoftBarcodeReader, BF_GS1_DATABAR_OMNIDIRECTIONAL), 0, NULL},
    {"BF_GS1_DATABAR_TRUNCATED",                T_INT, offsetof(DynamsoftBarcodeReader, BF_GS1_DATABAR_TRUNCATED), 0, NULL},
    {"BF_GS1_DATABAR_STACKED",                  T_INT, offsetof(DynamsoftBarcodeReader, BF_GS1_DATABAR_STACKED), 0, NULL},
    {"BF_GS1_DATABAR_STACKED_OMNIDIRECTIONAL",  T_INT, offsetof(DynamsoftBarcodeReader, BF_GS1_DATABAR_STACKED_OMNIDIRECTIONAL), 0, NULL},
    {"BF_GS1_DATABAR_EXPANDED",                 T_INT, offsetof(DynamsoftBarcodeReader, BF_GS1_DATABAR_EXPANDED), 0, NULL},
    {"BF_GS1_DATABAR_EXPANDED_STACKED",         T_INT, offsetof(DynamsoftBarcodeReader, BF_GS1_DATABAR_EXPANDED_STACKED), 0, NULL},
    {"BF_GS1_DATABAR_LIMITED",                  T_INT, offsetof(DynamsoftBarcodeReader, BF_GS1_DATABAR_LIMITED), 0, NULL},
    {"BF_PATCHCODE",                            T_INT, offsetof(DynamsoftBarcodeReader, BF_PATCHCODE), 0, NULL},
    {"BF_USPSINTELLIGENTMAIL",                  T_INT, offsetof(DynamsoftBarcodeReader, BF_USPSINTELLIGENTMAIL), 0, NULL},
    {"BF_PLANET",                               T_INT, offsetof(DynamsoftBarcodeReader, BF_PLANET), 0, NULL},
    {"BF_AUSTRALIANPOST",                       T_INT, offsetof(DynamsoftBarcodeReader, BF_AUSTRALIANPOST), 0, NULL},
    {"BF_UKROYALMAIL",                          T_INT, offsetof(DynamsoftBarcodeReader, BF_UKROYALMAIL), 0, NULL},
    {"BF_PDF417",                               T_INT, offsetof(DynamsoftBarcodeReader, BF_PDF417), 0, NULL},
    {"BF_QR_CODE",                              T_INT, offsetof(DynamsoftBarcodeReader, BF_QR_CODE), 0, NULL},
    {"BF_DATAMATRIX",                           T_INT, offsetof(DynamsoftBarcodeReader, BF_DATAMATRIX), 0, NULL},
    {"BF_AZTEC",                                T_INT, offsetof(DynamsoftBarcodeReader, BF_AZTEC), 0, NULL},
    {"BF_MAXICODE",                             T_INT, offsetof(DynamsoftBarcodeReader, BF_MAXICODE), 0, NULL},
    {"BF_MICRO_QR",                             T_INT, offsetof(DynamsoftBarcodeReader, BF_MICRO_QR), 0, NULL},
    {"BF_MICRO_PDF417",                         T_INT, offsetof(DynamsoftBarcodeReader, BF_MICRO_PDF417), 0, NULL},
    {"BF_GS1_COMPOSITE",                        T_INT, offsetof(DynamsoftBarcodeReader, BF_GS1_COMPOSITE), 0, NULL},
    {"BF_NULL",                                 T_INT, offsetof(DynamsoftBarcodeReader, BF_NULL), 0, NULL},
    {"BF2_NULL",                                T_INT, offsetof(DynamsoftBarcodeReader, BF2_NULL), 0, NULL},
    {"BF2_NONSTANDARD_BARCODE",                 T_INT, offsetof(DynamsoftBarcodeReader, BF2_NONSTANDARD_BARCODE), 0, NULL},
    {"BCM_AUTO",                                T_INT, offsetof(DynamsoftBarcodeReader, BCM_AUTO), 0, NULL},
    {"BCM_GENERAL",                             T_INT, offsetof(DynamsoftBarcodeReader, BCM_GENERAL), 0, NULL},
    {"BCM_SKIP",                                T_INT, offsetof(DynamsoftBarcodeReader, BCM_SKIP), 0, NULL},
    {"IPF_BINARY",                              T_INT, offsetof(DynamsoftBarcodeReader, IPF_BINARY), 0, NULL},
    {"IPF_BINARYINVERTED",                      T_INT, offsetof(DynamsoftBarcodeReader, IPF_BINARYINVERTED), 0, NULL},
    {"IPF_GRAYSCALED",                          T_INT, offsetof(DynamsoftBarcodeReader, IPF_GRAYSCALED), 0, NULL},
    {"IPF_NV21",                                T_INT, offsetof(DynamsoftBarcodeReader, IPF_NV21), 0, NULL},
    {"IPF_RGB_565",                             T_INT, offsetof(DynamsoftBarcodeReader, IPF_RGB_565), 0, NULL},
    {"IPF_RGB_555",                             T_INT, offsetof(DynamsoftBarcodeReader, IPF_RGB_555), 0, NULL},
    {"IPF_RGB_888",                             T_INT, offsetof(DynamsoftBarcodeReader, IPF_RGB_888), 0, NULL},
    {"IPF_ARGB_8888",                           T_INT, offsetof(DynamsoftBarcodeReader, IPF_ARGB_8888), 0, NULL},
    {"IPF_RGB_161616",                          T_INT, offsetof(DynamsoftBarcodeReader, IPF_RGB_161616), 0, NULL},
    {"IPF_ARGB_16161616",                       T_INT, offsetof(DynamsoftBarcodeReader, IPF_ARGB_16161616), 0, NULL},
    {"RT_STANDARD_TEXT",                        T_INT, offsetof(DynamsoftBarcodeReader, RT_STANDARD_TEXT), 0, NULL},
    {"RT_RAW_TEXT",                             T_INT, offsetof(DynamsoftBarcodeReader, RT_RAW_TEXT), 0, NULL},
    {"RT_CANDIDATE_TEXT",                       T_INT, offsetof(DynamsoftBarcodeReader, RT_CANDIDATE_TEXT), 0, NULL},
    {"RT_PARTIAL_TEXT",                         T_INT, offsetof(DynamsoftBarcodeReader, RT_PARTIAL_TEXT), 0, NULL},
    {"TP_REGION_PREDETECTED",                   T_INT, offsetof(DynamsoftBarcodeReader, TP_REGION_PREDETECTED), 0, NULL},
    {"TP_IMAGE_PREPROCESSED",                   T_INT, offsetof(DynamsoftBarcodeReader, TP_IMAGE_PREPROCESSED), 0, NULL},
    {"TP_IMAGE_BINARIZED",                      T_INT, offsetof(DynamsoftBarcodeReader, TP_IMAGE_BINARIZED), 0, NULL},
    {"TP_BARCODE_LOCALIZED",                    T_INT, offsetof(DynamsoftBarcodeReader, TP_BARCODE_LOCALIZED), 0, NULL},
    {"TP_BARCODE_TYPE_DETERMINED",              T_INT, offsetof(DynamsoftBarcodeReader, TP_BARCODE_TYPE_DETERMINED), 0, NULL},
    {"TP_BARCODE_RECOGNIZED",                   T_INT, offsetof(DynamsoftBarcodeReader, TP_BARCODE_RECOGNIZED), 0, NULL},
    {"BICM_DARK_ON_LIGHT",                      T_INT, offsetof(DynamsoftBarcodeReader, BICM_DARK_ON_LIGHT), 0, NULL},
    {"BICM_LIGHT_ON_DARK",                      T_INT, offsetof(DynamsoftBarcodeReader, BICM_LIGHT_ON_DARK), 0, NULL},
    {"BICM_DARK_ON_DARK",                       T_INT, offsetof(DynamsoftBarcodeReader, BICM_DARK_ON_DARK), 0, NULL},
    {"BICM_LIGHT_ON_LIGHT",                     T_INT, offsetof(DynamsoftBarcodeReader, BICM_LIGHT_ON_LIGHT), 0, NULL},
    {"BICM_DARK_LIGHT_MIXED",                   T_INT, offsetof(DynamsoftBarcodeReader, BICM_DARK_LIGHT_MIXED), 0, NULL},
    {"BICM_DARK_ON_LIGHT_DARK_SURROUNDING",     T_INT, offsetof(DynamsoftBarcodeReader, BICM_DARK_ON_LIGHT_DARK_SURROUNDING), 0, NULL},
    {"BICM_SKIP",                               T_INT, offsetof(DynamsoftBarcodeReader, BICM_SKIP), 0, NULL},
    {"BM_AUTO",                                 T_INT, offsetof(DynamsoftBarcodeReader, BM_AUTO), 0, NULL},
    {"BM_LOCAL_BLOCK",                          T_INT, offsetof(DynamsoftBarcodeReader, BM_LOCAL_BLOCK), 0, NULL},
    {"BM_SKIP",                                 T_INT, offsetof(DynamsoftBarcodeReader, BM_SKIP), 0, NULL},
    {"CCM_AUTO",                                T_INT, offsetof(DynamsoftBarcodeReader, CCM_AUTO), 0, NULL},
    {"CCM_GENERAL_HSV",                         T_INT, offsetof(DynamsoftBarcodeReader, CCM_GENERAL_HSV), 0, NULL},
    {"CCM_SKIP",                                T_INT, offsetof(DynamsoftBarcodeReader, CCM_SKIP), 0, NULL},
    {"CICM_GENERAL",                            T_INT, offsetof(DynamsoftBarcodeReader, CICM_GENERAL), 0, NULL},
    {"CICM_SKIP",                               T_INT, offsetof(DynamsoftBarcodeReader, CICM_SKIP), 0, NULL},
    {"DPMCRM_AUTO",                             T_INT, offsetof(DynamsoftBarcodeReader, DPMCRM_AUTO), 0, NULL},
    {"DPMCRM_GENERAL",                          T_INT, offsetof(DynamsoftBarcodeReader, DPMCRM_GENERAL), 0, NULL},
    {"DPMCRM_SKIP",                             T_INT, offsetof(DynamsoftBarcodeReader, DPMCRM_SKIP), 0, NULL},
    {"RPM_AUTO",                                T_INT, offsetof(DynamsoftBarcodeReader, RPM_AUTO), 0, NULL},
    {"RPM_GENERAL",                             T_INT, offsetof(DynamsoftBarcodeReader, RPM_GENERAL), 0, NULL},
    {"RPM_GENERAL_RGB_CONTRAST",                T_INT, offsetof(DynamsoftBarcodeReader, RPM_GENERAL_RGB_CONTRAST), 0, NULL},
    {"RPM_GENERAL_GRAY_CONTRAST",               T_INT, offsetof(DynamsoftBarcodeReader, RPM_GENERAL_GRAY_CONTRAST), 0, NULL},
    {"RPM_GENERAL_HSV_CONTRAST",                T_INT, offsetof(DynamsoftBarcodeReader, RPM_GENERAL_HSV_CONTRAST), 0, NULL},
    {"RPM_SKIP",                                T_INT, offsetof(DynamsoftBarcodeReader, RPM_SKIP), 0, NULL},
    {"TFM_AUTO",                                T_INT, offsetof(DynamsoftBarcodeReader, TFM_AUTO), 0, NULL},
    {"TFM_GENERAL_CONTOUR",                     T_INT, offsetof(DynamsoftBarcodeReader, TFM_GENERAL_CONTOUR), 0, NULL},
    {"TFM_SKIP",                                T_INT, offsetof(DynamsoftBarcodeReader, TFM_SKIP), 0, NULL},
    {"CM_IGNORE",                               T_INT, offsetof(DynamsoftBarcodeReader, CM_IGNORE), 0, NULL},
    {"CM_OVERWRITE",                            T_INT, offsetof(DynamsoftBarcodeReader, CM_OVERWRITE), 0, NULL},
    {"IPM_AUTO",                                T_INT, offsetof(DynamsoftBarcodeReader, IPM_AUTO), 0, NULL},
    {"IPM_GENERAL",                             T_INT, offsetof(DynamsoftBarcodeReader, IPM_GENERAL), 0, NULL},
    {"IPM_GRAY_EQUALIZE",                       T_INT, offsetof(DynamsoftBarcodeReader, IPM_GRAY_EQUALIZE), 0, NULL},
    {"IPM_GRAY_SMOOTH",                         T_INT, offsetof(DynamsoftBarcodeReader, IPM_GRAY_SMOOTH), 0, NULL},
    {"IPM_SHARPEN_SMOOTH",                      T_INT, offsetof(DynamsoftBarcodeReader, IPM_SHARPEN_SMOOTH), 0, NULL},
    {"IPM_SKIP",                                T_INT, offsetof(DynamsoftBarcodeReader, IPM_SKIP), 0, NULL},
    {"IRT_NO_RESULT",                           T_INT, offsetof(DynamsoftBarcodeReader, IRT_NO_RESULT), 0, NULL},
    {"IRT_ORIGINAL_IMAGE",                      T_INT, offsetof(DynamsoftBarcodeReader, IRT_ORIGINAL_IMAGE), 0, NULL},
    {"IRT_COLOUR_CLUSTERED_IMAGE",              T_INT, offsetof(DynamsoftBarcodeReader, IRT_COLOUR_CLUSTERED_IMAGE), 0, NULL},
    {"IRT_COLOUR_CONVERTED_GRAYSCALE_IMAGE",    T_INT, offsetof(DynamsoftBarcodeReader, IRT_COLOUR_CONVERTED_GRAYSCALE_IMAGE), 0, NULL},
    {"IRT_TRANSFORMED_GRAYSCALE_IMAGE",         T_INT, offsetof(DynamsoftBarcodeReader, IRT_TRANSFORMED_GRAYSCALE_IMAGE), 0, NULL},
    {"IRT_PREDETECTED_REGION",                  T_INT, offsetof(DynamsoftBarcodeReader, IRT_PREDETECTED_REGION), 0, NULL},
    {"IRT_PREPROCESSED_IMAGE",                  T_INT, offsetof(DynamsoftBarcodeReader, IRT_PREPROCESSED_IMAGE), 0, NULL},
    {"IRT_BINARIZED_IMAGE",                     T_INT, offsetof(DynamsoftBarcodeReader, IRT_BINARIZED_IMAGE), 0, NULL},
    {"IRT_TEXT_ZONE",                           T_INT, offsetof(DynamsoftBarcodeReader, IRT_TEXT_ZONE), 0, NULL},
    {"IRT_CONTOUR",                             T_INT, offsetof(DynamsoftBarcodeReader, IRT_CONTOUR), 0, NULL},
    {"IRT_LINE_SEGMENT",                        T_INT, offsetof(DynamsoftBarcodeReader, IRT_LINE_SEGMENT), 0, NULL},
    {"IRT_FORM",                                T_INT, offsetof(DynamsoftBarcodeReader, IRT_FORM), 0, NULL},
    {"IRT_SEGMENTATION_BLOCK",                  T_INT, offsetof(DynamsoftBarcodeReader, IRT_SEGMENTATION_BLOCK), 0, NULL},
    {"IRT_TYPED_BARCODE_ZONE",                  T_INT, offsetof(DynamsoftBarcodeReader, IRT_TYPED_BARCODE_ZONE), 0, NULL},
    {"LM_AUTO",                                 T_INT, offsetof(DynamsoftBarcodeReader, LM_AUTO), 0, NULL},
    {"LM_CONNECTED_BLOCKS",                     T_INT, offsetof(DynamsoftBarcodeReader, LM_CONNECTED_BLOCKS), 0, NULL},
    {"LM_STATISTICS",                           T_INT, offsetof(DynamsoftBarcodeReader, LM_STATISTICS), 0, NULL},
    {"LM_LINES",                                T_INT, offsetof(DynamsoftBarcodeReader, LM_LINES), 0, NULL},
    {"LM_SCAN_DIRECTLY",                        T_INT, offsetof(DynamsoftBarcodeReader, LM_SCAN_DIRECTLY), 0, NULL},
    {"LM_STATISTICS_MARKS",                     T_INT, offsetof(DynamsoftBarcodeReader, LM_STATISTICS_MARKS), 0, NULL},
    {"LM_SKIP",                                 T_INT, offsetof(DynamsoftBarcodeReader, LM_SKIP), 0, NULL},
    {"QRECL_ERROR_CORRECTION_H",                T_INT, offsetof(DynamsoftBarcodeReader, QRECL_ERROR_CORRECTION_H), 0, NULL},
    {"QRECL_ERROR_CORRECTION_L",                T_INT, offsetof(DynamsoftBarcodeReader, QRECL_ERROR_CORRECTION_L), 0, NULL},
    {"QRECL_ERROR_CORRECTION_M",                T_INT, offsetof(DynamsoftBarcodeReader, QRECL_ERROR_CORRECTION_M), 0, NULL},
    {"QRECL_ERROR_CORRECTION_Q",                T_INT, offsetof(DynamsoftBarcodeReader, QRECL_ERROR_CORRECTION_Q), 0, NULL},
    {"DRM_AUTO",                                T_INT, offsetof(DynamsoftBarcodeReader, DRM_AUTO), 0, NULL},
    {"DRM_GENERAL",                             T_INT, offsetof(DynamsoftBarcodeReader, DRM_GENERAL), 0, NULL},
    {"DRM_SKIP",                                T_INT, offsetof(DynamsoftBarcodeReader, DRM_SKIP), 0, NULL},
    {"TACM_AUTO",                               T_INT, offsetof(DynamsoftBarcodeReader, TACM_AUTO), 0, NULL},
    {"TACM_VERIFYING",                          T_INT, offsetof(DynamsoftBarcodeReader, TACM_VERIFYING), 0, NULL},
    {"TACM_VERIFYING_PATCHING",                 T_INT, offsetof(DynamsoftBarcodeReader, TACM_VERIFYING_PATCHING), 0, NULL},
    {"TACM_SKIP",                               T_INT, offsetof(DynamsoftBarcodeReader, TACM_SKIP), 0, NULL},
    {"TROM_CONFIDENCE",                         T_INT, offsetof(DynamsoftBarcodeReader, TROM_CONFIDENCE), 0, NULL},
    {"TROM_POSITION",                           T_INT, offsetof(DynamsoftBarcodeReader, TROM_POSITION), 0, NULL},
    {"TROM_FORMAT",                             T_INT, offsetof(DynamsoftBarcodeReader, TROM_FORMAT), 0, NULL},
    {"TROM_SKIP",                               T_INT, offsetof(DynamsoftBarcodeReader, TROM_SKIP), 0, NULL},
    {"TDM_AUTO",                                T_INT, offsetof(DynamsoftBarcodeReader, TDM_AUTO), 0, NULL},
    {"TDM_GENERAL_WIDTH_CONCENTRATION",         T_INT, offsetof(DynamsoftBarcodeReader, TDM_GENERAL_WIDTH_CONCENTRATION), 0, NULL},
    {"TDM_SKIP",                                T_INT, offsetof(DynamsoftBarcodeReader, TDM_SKIP), 0, NULL},
    {"GTM_INVERTED",                            T_INT, offsetof(DynamsoftBarcodeReader, GTM_INVERTED), 0, NULL},
    {"GTM_ORIGINAL",                            T_INT, offsetof(DynamsoftBarcodeReader, GTM_ORIGINAL), 0, NULL},
    {"GTM_SKIP",                                T_INT, offsetof(DynamsoftBarcodeReader, GTM_SKIP), 0, NULL},
    {"RCT_PIXEL",                               T_INT, offsetof(DynamsoftBarcodeReader, RCT_PIXEL), 0, NULL},
    {"RCT_PERCENTAGE",                          T_INT, offsetof(DynamsoftBarcodeReader, RCT_PERCENTAGE), 0, NULL},
    {"IMRDT_IMAGE",                             T_INT, offsetof(DynamsoftBarcodeReader, IMRDT_IMAGE), 0, NULL},
    {"IMRDT_CONTOUR",                           T_INT, offsetof(DynamsoftBarcodeReader, IMRDT_CONTOUR), 0, NULL},
    {"IMRDT_LINESEGMENT",                       T_INT, offsetof(DynamsoftBarcodeReader, IMRDT_LINESEGMENT), 0, NULL},
    {"IMRDT_LOCALIZATIONRESULT",                T_INT, offsetof(DynamsoftBarcodeReader, IMRDT_LOCALIZATIONRESULT), 0, NULL},
    {"IMRDT_REGIONOFINTEREST",                  T_INT, offsetof(DynamsoftBarcodeReader, IMRDT_REGIONOFINTEREST), 0, NULL},
    {"IRSM_MEMORY",                             T_INT, offsetof(DynamsoftBarcodeReader, IRSM_MEMORY), 0, NULL},
    {"IRSM_FILESYSTEM",                         T_INT, offsetof(DynamsoftBarcodeReader, IRSM_FILESYSTEM), 0, NULL},
    {"IRSM_BOTH",                               T_INT, offsetof(DynamsoftBarcodeReader, IRSM_BOTH), 0, NULL},
    {NULL} /* Sentinel */
};

static PyMethodDef dbr_methods[] = {
    {"initLicense",                     initLicense,                        METH_VARARGS, NULL},
    {"decodeFile",                      decodeFile,                         METH_VARARGS, NULL},
    {"decodeBuffer",                    decodeBuffer,                       METH_VARARGS, NULL},
    {"startVideoMode",                  startVideoMode,                     METH_VARARGS, NULL},
    {"stopVideoMode",                   stopVideoMode,                      METH_VARARGS, NULL},
    {"appendVideoFrame",                appendVideoFrame,                   METH_VARARGS, NULL},
    {"initLicenseFromLicenseContent",   initLicenseFromLicenseContent,      METH_VARARGS, NULL},
    {"outputLicenseToString",           outputLicenseToString,              METH_VARARGS, NULL},
    {"initLicenseFromServer",           initLicenseFromServer,              METH_VARARGS, NULL},
    {"setFurtherModes",                 setFurtherModes,                    METH_VARARGS, NULL},
    {"setParameters",                   setParameters,                      METH_VARARGS, NULL},
    {"getParameters",                   getParameters,                      METH_VARARGS, NULL},
    {"decodeFileStream",                decodeFileStream,                   METH_VARARGS, NULL},
    {"InitLicense",                     InitLicense,                        METH_VARARGS, NULL},
    {"DecodeFile",                      DecodeFile,                         METH_VARARGS, NULL},
    {"DecodeBuffer",                    DecodeBuffer,                       METH_VARARGS, NULL},
    {"StartVideoMode",                  StartVideoMode,                     METH_VARARGS, NULL},
    {"StopVideoMode",                   StopVideoMode,                      METH_VARARGS, NULL},
    {"AppendVideoFrame",                AppendVideoFrame,                   METH_VARARGS, NULL},
    {"InitLicenseFromLicenseContent",   InitLicenseFromLicenseContent,      METH_VARARGS, NULL},
    {"OutputLicenseToString",           OutputLicenseToString,              METH_VARARGS, NULL},
    {"InitLicenseFromServer",           InitLicenseFromServer,              METH_VARARGS, NULL},
    {"InitRuntimeSettingsByJsonString", InitRuntimeSettingsByJsonString,    METH_VARARGS, NULL},
    {"OutputSettingsToJsonString",      OutputSettingsToJsonString,         METH_VARARGS, NULL},
    {"InitRuntimeSettingsByJsonFile",   InitRuntimeSettingsByJsonFile,      METH_VARARGS, NULL},
    {"OutputSettingsToJsonFile",        OutputSettingsToJsonFile,           METH_VARARGS, NULL},
    {"AppendTplFileToRuntimeSettings",  AppendTplFileToRuntimeSettings,     METH_VARARGS, NULL},
    {"AppendTplStringToRuntimeSettings",AppendTplStringToRuntimeSettings,   METH_VARARGS, NULL},
    {"GetAllTemplateNames",             GetAllTemplateNames,                METH_VARARGS, NULL},
    {"DecodeFileStream",                DecodeFileStream,                   METH_VARARGS, NULL},
    {"GetRuntimeSettings",              GetRuntimeSettings,                 METH_VARARGS, NULL},
    {"UpdataRuntimeSettings",           UpdataRuntimeSettings,              METH_VARARGS, NULL},
    {"ResetRuntimeSettings",            ResetRuntimeSettings,               METH_VARARGS, NULL},
    {"SetModeArgument",                 SetModeArgument,                    METH_VARARGS, NULL},
    {"GetModeArgument",                 GetModeArgument,                    METH_VARARGS, NULL},
    {"InitFrameDecodingParameters",     InitFrameDecodingParameters,        METH_VARARGS, NULL},
    {NULL,                              NULL,                               0,            NULL}
};

static PyMethodDef module_methods[] =
{
    {NULL}
};

static int DynamsoftBarcodeReader_clear(DynamsoftBarcodeReader *self)
{
    PyObject *tmp;

    tmp = self->COLOR_CLUTERING_MODE;
    self->COLOR_CLUTERING_MODE = NULL;
    Py_XDECREF(tmp);

    tmp = self->COLOR_CONVERSION_MODE;
    self->COLOR_CONVERSION_MODE = NULL;
    Py_XDECREF(tmp);

    tmp = self->GRAY_SCALE_TRANSFORMATION_MODE;
    self->GRAY_SCALE_TRANSFORMATION_MODE = NULL;
    Py_XDECREF(tmp);

    tmp = self->REGION_PREDETECTION_MODE;
    self->REGION_PREDETECTION_MODE = NULL;
    Py_XDECREF(tmp);

    tmp = self->IMAGE_PREPROCESSING_MODE;
    self->IMAGE_PREPROCESSING_MODE = NULL;
    Py_XDECREF(tmp);

    tmp = self->TEXTURE_DETECTION_MODE;
    self->TEXTURE_DETECTION_MODE = NULL;
    Py_XDECREF(tmp);

    tmp = self->TEXTURE_FILTER_MODE;
    self->TEXTURE_FILTER_MODE = NULL;
    Py_XDECREF(tmp);

    tmp = self->TEXT_ASSISTED_CORRECTION_MODE;
    self->TEXT_ASSISTED_CORRECTION_MODE = NULL;
    Py_XDECREF(tmp);

    tmp = self->DPM_CODE_READING_MODE;
    self->DPM_CODE_READING_MODE = NULL;
    Py_XDECREF(tmp);

    tmp = self->DEFORMATION_RESISTING_MODE;
    self->DEFORMATION_RESISTING_MODE = NULL;
    Py_XDECREF(tmp);

    tmp = self->BARCODE_COMPLEMENT_MODE;
    self->BARCODE_COMPLEMENT_MODE = NULL;
    Py_XDECREF(tmp);

    tmp = self->BARCODE_COLOR_MODE;
    self->BARCODE_COLOR_MODE = NULL;
    Py_XDECREF(tmp);

    DBR_DestroyInstance(self->hBarcode);

    return 0;
}

static void DynamsoftBarcodeReader_dealloc(DynamsoftBarcodeReader *self)
{
#if defined(IS_PY3K)
    DynamsoftBarcodeReader_clear(self);
    Py_TYPE(self)->tp_free((PyObject *)self);
#else
    DynamsoftBarcodeReader_clear(self);
    self->ob_type->tp_free((PyObject *)self);
#endif
}

static PyObject * DynamsoftBarcodeReader_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    DynamsoftBarcodeReader *self;

    self = (DynamsoftBarcodeReader *)type->tp_alloc(type, 0);
    if (self != NULL)
    {
        self->hBarcode = DBR_CreateInstance();
        const char *versionInfo = DBR_GetVersion();
        printf("Dynamsoft Barcode Reader %s\n", versionInfo);
        if (!self->hBarcode)
        {
            printf("Cannot allocate memory!\n");
            return NULL;
        }

#ifdef IS_PY3K
        self->COLOR_CLUTERING_MODE              = PyUnicode_FromString("colourClusteringModes");
        self->COLOR_CONVERSION_MODE             = PyUnicode_FromString("colourConversionModes");
        self->GRAY_SCALE_TRANSFORMATION_MODE    = PyUnicode_FromString("grayscaleTransformationModes");
        self->REGION_PREDETECTION_MODE          = PyUnicode_FromString("regionPredetectionMode");
        self->IMAGE_PREPROCESSING_MODE          = PyUnicode_FromString("imagePreprocessingModes");
        self->TEXTURE_DETECTION_MODE            = PyUnicode_FromString("textureDetectionModes");
        self->TEXTURE_FILTER_MODE               = PyUnicode_FromString("textFilterModes");
        self->TEXT_ASSISTED_CORRECTION_MODE     = PyUnicode_FromString("textAssistedCorrectionMode ");
        self->DPM_CODE_READING_MODE             = PyUnicode_FromString("dpmCodeReadingModes");
        self->DEFORMATION_RESISTING_MODE        = PyUnicode_FromString("deformationResistingModes");
        self->BARCODE_COMPLEMENT_MODE           = PyUnicode_FromString("barcodeComplementModes");
        self->BARCODE_COLOR_MODE                = PyUnicode_FromString("barcodeColourModes");
#else
        self->COLOR_CLUTERING_MODE              = PyString_FromString("colourClusteringModes");
        self->COLOR_CONVERSION_MODE             = PyString_FromString("colourConversionModes");
        self->GRAY_SCALE_TRANSFORMATION_MODE    = PyString_FromString("grayscaleTransformationModes");
        self->REGION_PREDETECTION_MODE          = PyString_FromString("regionPredetectionMode");
        self->IMAGE_PREPROCESSING_MODE          = PyString_FromString("imagePreprocessingModes");
        self->TEXTURE_DETECTION_MODE            = PyString_FromString("textureDetectionModes");
        self->TEXTURE_FILTER_MODE               = PyString_FromString("textFilterModes");
        self->TEXT_ASSISTED_CORRECTION_MODE     = PyString_FromString("textAssistedCorrectionMode ");
        self->DPM_CODE_READING_MODE             = PyString_FromString("dpmCodeReadingModes");
        self->DEFORMATION_RESISTING_MODE        = PyString_FromString("deformationResistingModes");
        self->BARCODE_COMPLEMENT_MODE           = PyString_FromString("barcodeComplementModes");
        self->BARCODE_COLOR_MODE                = PyString_FromString("barcodeColourModes");
#endif
        // Barcode formats
        self->BF_ALL                            = BF_ALL;
        self->BF_ONED                           = BF_ONED;
        self->BF_GS1_DATABAR                    = BF_GS1_DATABAR;
        self->BF_POSTALCODE                     = BF_POSTALCODE;
        self->BF_CODE_39                        = BF_CODE_39;
        self->BF_CODE_128                       = BF_CODE_128;
        self->BF_CODE_93                        = BF_CODE_93;
        self->BF_CODABAR                        = BF_CODABAR;
        self->BF_ITF                            = BF_ITF;
        self->BF_EAN_13                         = BF_EAN_13;
        self->BF_EAN_8                          = BF_EAN_8;
        self->BF_UPC_A                          = BF_UPC_A;
        self->BF_UPC_E                          = BF_UPC_E;
        self->BF_INDUSTRIAL_25                  = BF_INDUSTRIAL_25;
        self->BF_CODE_39_EXTENDED               = BF_CODE_39_EXTENDED;
        self->BF_GS1_DATABAR_OMNIDIRECTIONAL    = BF_GS1_DATABAR_OMNIDIRECTIONAL;
        self->BF_GS1_DATABAR_TRUNCATED          = BF_GS1_DATABAR_TRUNCATED;
        self->BF_GS1_DATABAR_STACKED            = BF_GS1_DATABAR_STACKED;
        self->BF_GS1_DATABAR_STACKED_OMNIDIRECTIONAL = BF_GS1_DATABAR_STACKED_OMNIDIRECTIONAL;
        self->BF_GS1_DATABAR_EXPANDED           = BF_GS1_DATABAR_EXPANDED;
        self->BF_GS1_DATABAR_EXPANDED_STACKED   = BF_GS1_DATABAR_EXPANDED_STACKED;
        self->BF_GS1_DATABAR_LIMITED            = BF_GS1_DATABAR_LIMITED;
        self->BF_PATCHCODE                      = BF_PATCHCODE;
        self->BF_USPSINTELLIGENTMAIL            = BF_USPSINTELLIGENTMAIL;
        self->BF_POSTNET                        = BF_POSTNET;
        self->BF_PLANET                         = BF_PLANET;
        self->BF_AUSTRALIANPOST                 = BF_AUSTRALIANPOST;
        self->BF_UKROYALMAIL                    = BF_UKROYALMAIL;
        self->BF_PDF417                         = BF_PDF417;
        self->BF_QR_CODE                        = BF_QR_CODE;
        self->BF_DATAMATRIX                     = BF_DATAMATRIX;
        self->BF_AZTEC                          = BF_AZTEC;
        self->BF_MAXICODE                       = BF_MAXICODE;
        self->BF_MICRO_QR                       = BF_MICRO_QR;
        self->BF_MICRO_PDF417                   = BF_MICRO_PDF417;
        self->BF_GS1_COMPOSITE                  = BF_GS1_COMPOSITE;
        self->BF_NULL                           = BF_NULL;
        // EnumBarcodeReader_2
        self->BF2_NULL                          = BF2_NULL;
        self->BF2_NONSTANDARD_BARCODE           = BF2_NONSTANDARD_BARCODE;
        // EnumBarcodeComplementMode
        self->BCM_AUTO                          = BCM_AUTO;
        self->BCM_GENERAL                       = BCM_GENERAL;
        self->BCM_SKIP                          = BCM_SKIP;
        // EnumImagePixelFormat
        self->IPF_BINARY                        = IPF_BINARY;
        self->IPF_BINARYINVERTED                = IPF_BINARYINVERTED;
        self->IPF_GRAYSCALED                    = IPF_GRAYSCALED;
        self->IPF_NV21                          = IPF_NV21;
        self->IPF_RGB_565                       = IPF_RGB_565;
        self->IPF_RGB_555                       = IPF_RGB_555;
        self->IPF_RGB_888                       = IPF_RGB_888;
        self->IPF_ARGB_8888                     = IPF_ARGB_8888;
        self->IPF_RGB_161616                    = IPF_RGB_161616;
        self->IPF_ARGB_16161616                 = IPF_ARGB_16161616;
        // EnumResultType
        self->RT_STANDARD_TEXT                  = RT_STANDARD_TEXT;
        self->RT_RAW_TEXT                       = RT_RAW_TEXT;
        self->RT_CANDIDATE_TEXT                 = RT_CANDIDATE_TEXT;
        self->RT_PARTIAL_TEXT                   = RT_PARTIAL_TEXT;
        // EnumTerminatePhase
        self->TP_REGION_PREDETECTED             = TP_REGION_PREDETECTED;
        self->TP_IMAGE_PREPROCESSED             = TP_IMAGE_PREPROCESSED;
        self->TP_IMAGE_BINARIZED                = TP_IMAGE_BINARIZED;
        self->TP_BARCODE_LOCALIZED              = TP_BARCODE_LOCALIZED;
        self->TP_BARCODE_TYPE_DETERMINED        = TP_BARCODE_TYPE_DETERMINED;
        self->TP_BARCODE_RECOGNIZED             = TP_BARCODE_RECOGNIZED;
        // EnumBarcodeColourMode
        self->BICM_DARK_ON_LIGHT                = BICM_DARK_ON_LIGHT;
        self->BICM_LIGHT_ON_DARK                = BICM_LIGHT_ON_DARK;
        self->BICM_DARK_ON_DARK                 = BICM_DARK_ON_DARK;
        self->BICM_LIGHT_ON_LIGHT               = BICM_LIGHT_ON_LIGHT;
        self->BICM_DARK_LIGHT_MIXED             = BICM_DARK_LIGHT_MIXED;
        self->BICM_DARK_ON_LIGHT_DARK_SURROUNDING = BICM_DARK_ON_LIGHT_DARK_SURROUNDING;
        self->BICM_SKIP                         = BICM_SKIP;
        // EnumBinarizationMode
        self->BM_AUTO                           = BM_AUTO;
        self->BM_LOCAL_BLOCK                    = BM_LOCAL_BLOCK;
        self->BM_SKIP                           = BM_SKIP;
        // EnumColourClusteringMode
        self->CCM_AUTO                          = CCM_AUTO;
        self->CCM_GENERAL_HSV                   = CCM_GENERAL_HSV;
        self->CCM_SKIP                          = CCM_SKIP;
        // EnumColourImageConvertMode
        self->CICM_GENERAL                      = CICM_GENERAL;
        self->CICM_SKIP                         = CICM_SKIP;
        // EnumDPMCodeReadingMode
        self->DPMCRM_AUTO                       = DPMCRM_AUTO;
        self->DPMCRM_GENERAL                    = DPMCRM_GENERAL;
        self->DPMCRM_SKIP                       = DPMCRM_SKIP;
        // EnumRegionPredetectionMode
        self->RPM_AUTO                          = RPM_AUTO;
        self->RPM_GENERAL                       = RPM_GENERAL;
        self->RPM_GENERAL_RGB_CONTRAST          = RPM_GENERAL_RGB_CONTRAST;
        self->RPM_GENERAL_GRAY_CONTRAST         = RPM_GENERAL_GRAY_CONTRAST;
        self->RPM_GENERAL_HSV_CONTRAST          = RPM_GENERAL_HSV_CONTRAST;
        self->RPM_SKIP                          = RPM_SKIP;
        // EnumTextFilterMode
        self->TFM_AUTO                          = TFM_AUTO;
        self->TFM_GENERAL_CONTOUR               = TFM_GENERAL_CONTOUR;
        self->TFM_SKIP                          = TFM_SKIP;
        // EnumConflictMode
        self->CM_IGNORE                         = CM_IGNORE;
        self->CM_OVERWRITE                      = CM_OVERWRITE;
        // ImagePreprocessingMode
        self->IPM_AUTO                          = IPM_AUTO;
        self->IPM_GENERAL                       = IPM_GENERAL;
        self->IPM_GRAY_EQUALIZE                 = IPM_GRAY_EQUALIZE;
        self->IPM_GRAY_SMOOTH                   = IPM_GRAY_SMOOTH;
        self->IPM_SHARPEN_SMOOTH                = IPM_SHARPEN_SMOOTH;
        self->IPM_SKIP                          = IPM_SKIP;
        // EnumIntermediateResultType
        self->IRT_NO_RESULT                     = IRT_NO_RESULT;
        self->IRT_ORIGINAL_IMAGE                = IRT_ORIGINAL_IMAGE;
        self->IRT_COLOUR_CLUSTERED_IMAGE        = IRT_COLOUR_CLUSTERED_IMAGE;
        self->IRT_COLOUR_CONVERTED_GRAYSCALE_IMAGE = IRT_COLOUR_CONVERTED_GRAYSCALE_IMAGE;
        self->IRT_TRANSFORMED_GRAYSCALE_IMAGE   = IRT_TRANSFORMED_GRAYSCALE_IMAGE;
        self->IRT_PREDETECTED_REGION            = IRT_PREDETECTED_REGION;
        self->IRT_PREPROCESSED_IMAGE            = IRT_PREPROCESSED_IMAGE;
        self->IRT_BINARIZED_IMAGE               = IRT_BINARIZED_IMAGE;
        self->IRT_TEXT_ZONE                     = IRT_TEXT_ZONE;
        self->IRT_CONTOUR                       = IRT_CONTOUR;
        self->IRT_LINE_SEGMENT                  = IRT_LINE_SEGMENT;
        self->IRT_FORM                          = IRT_FORM;
        self->IRT_SEGMENTATION_BLOCK            = IRT_SEGMENTATION_BLOCK;
        self->IRT_TYPED_BARCODE_ZONE            = IRT_TYPED_BARCODE_ZONE;
        // EnumLocalizationMode
        self->LM_AUTO                           = LM_AUTO;
        self->LM_CONNECTED_BLOCKS               = LM_CONNECTED_BLOCKS;
        self->LM_STATISTICS                     = LM_STATISTICS;
        self->LM_LINES                          = LM_LINES;
        self->LM_SCAN_DIRECTLY                  = LM_SCAN_DIRECTLY;
        self->LM_STATISTICS_MARKS               = LM_STATISTICS_MARKS;
        self->LM_SKIP                           = LM_SKIP;
        // EnumQRCodeErrorCorrectionLevel
        self->QRECL_ERROR_CORRECTION_H          = QRECL_ERROR_CORRECTION_H;
        self->QRECL_ERROR_CORRECTION_L          = QRECL_ERROR_CORRECTION_L;
        self->QRECL_ERROR_CORRECTION_M          = QRECL_ERROR_CORRECTION_M;
        self->QRECL_ERROR_CORRECTION_Q          = QRECL_ERROR_CORRECTION_Q;
        // EnumDeformationResistingMode
        self->DRM_AUTO                          = DRM_AUTO;
        self->DRM_GENERAL                       = DRM_GENERAL;
        self->DRM_SKIP                          = DRM_SKIP;
        // EnumTextAssistedCorrectionMode
        self->TACM_AUTO                         = TACM_AUTO;
        self->TACM_VERIFYING                    = TACM_VERIFYING;
        self->TACM_VERIFYING_PATCHING           = TACM_VERIFYING_PATCHING;
        self->TACM_SKIP                         = TACM_SKIP;
        // EnumTextResultOrderMode
        self->TROM_CONFIDENCE                   = TROM_CONFIDENCE;
        self->TROM_POSITION                     = TROM_POSITION;
        self->TROM_FORMAT                       = TROM_FORMAT;
        self->TROM_SKIP                         = TROM_SKIP;
        // EnumTextureDetectionMode
        self->TDM_AUTO                          = TDM_AUTO;
        self->TDM_GENERAL_WIDTH_CONCENTRATION   = TDM_GENERAL_WIDTH_CONCENTRATION;
        self->TDM_SKIP                          = TDM_SKIP;
        // EnumGrayscaleTransformationMode
        self->GTM_INVERTED                      = GTM_INVERTED;
        self->GTM_ORIGINAL                      = GTM_ORIGINAL;
        self->GTM_SKIP                          = GTM_SKIP;
        // EnumResultCoordinateType
        self->RCT_PIXEL                         = RCT_PIXEL;
        self->RCT_PERCENTAGE                    = RCT_PERCENTAGE;
        // EnumIMResultDataType
        self->IMRDT_IMAGE                       = IMRDT_IMAGE;
        self->IMRDT_CONTOUR                     = IMRDT_CONTOUR;
        self->IMRDT_LINESEGMENT                 = IMRDT_LINESEGMENT;
        self->IMRDT_LOCALIZATIONRESULT          = IMRDT_LOCALIZATIONRESULT;
        self->IMRDT_REGIONOFINTEREST            = IMRDT_REGIONOFINTEREST;
        // EnumIntermediateResultSavingMode
        self->IRSM_MEMORY                       = IRSM_MEMORY;
        self->IRSM_FILESYSTEM                   = IRSM_FILESYSTEM;
        self->IRSM_BOTH                         = IRSM_BOTH;

        if (self->GRAY_SCALE_TRANSFORMATION_MODE == NULL)
        {
            Py_DECREF(self);
            return NULL;
        }
    }

    return (PyObject *)self;
}

static int DynamsoftBarcodeReader_init(DynamsoftBarcodeReader *self, PyObject *args, PyObject *kwds)
{
    return 0;
}

static PyTypeObject DynamsoftBarcodeReaderType = {
    PyVarObject_HEAD_INIT(NULL, 0) "dbr.DynamsoftBarcodeReader", /* tp_name */
    sizeof(DynamsoftBarcodeReader),                              /* tp_basicsize */
    0,                                                           /* tp_itemsize */
    (destructor)DynamsoftBarcodeReader_dealloc,                  /* tp_dealloc */
    0,                                                           /* tp_print */
    0,                                                           /* tp_getattr */
    0,                                                           /* tp_setattr */
    0,                                                           /* tp_reserved */
    0,                                                           /* tp_repr */
    0,                                                           /* tp_as_number */
    0,                                                           /* tp_as_sequence */
    0,                                                           /* tp_as_mapping */
    0,                                                           /* tp_hash  */
    0,                                                           /* tp_call */
    0,                                                           /* tp_str */
    0,                                                           /* tp_getattro */
    0,                                                           /* tp_setattro */
    0,                                                           /* tp_as_buffer */
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,                    /*tp_flags*/
    "Dynamsoft Barcode Reader objects",                          /* tp_doc */
    0,                                                           /* tp_traverse */
    0,                                                           /* tp_clear */
    0,                                                           /* tp_richcompare */
    0,                                                           /* tp_weaklistoffset */
    0,                                                           /* tp_iter */
    0,                                                           /* tp_iternext */
    dbr_methods,                                                 /* tp_methods */
    dbr_members,                                                 /* tp_members */
    0,                                                           /* tp_getset */
    0,                                                           /* tp_base */
    0,                                                           /* tp_dict */
    0,                                                           /* tp_descr_get */
    0,                                                           /* tp_descr_set */
    0,                                                           /* tp_dictoffset */
    (initproc)DynamsoftBarcodeReader_init,                       /* tp_init */
    0,                                                           /* tp_alloc */
    DynamsoftBarcodeReader_new,                                  /* tp_new */
};

#if defined(IS_PY3K)
static int dbr_traverse(PyObject *m, visitproc visit, void *arg)
{
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int dbr_clear(PyObject *m)
{
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "dbr",
    "Extension with Dynamsoft Barcode Reader.",
    -1,
    NULL, NULL, NULL, NULL, NULL};

#define INITERROR return NULL

PyMODINIT_FUNC
PyInit_dbr(void)

#else
#define INITERROR return
void initdbr(void)
#endif
{
    if (PyType_Ready(&DynamsoftBarcodeReaderType) < 0)
        INITERROR;

#if defined(IS_PY3K)
    PyObject *module = PyModule_Create(&moduledef);
#else
    PyObject *module = Py_InitModule("dbr", module_methods);
#endif
    if (module == NULL)
        INITERROR;

    Py_INCREF(&DynamsoftBarcodeReaderType);
    PyModule_AddObject(module, "DynamsoftBarcodeReader", (PyObject *)&DynamsoftBarcodeReaderType);
#if defined(IS_PY3K)
    return module;
#endif
}