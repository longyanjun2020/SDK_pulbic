
#ifndef __MMI_MAE_CUSTOMIZATION_H__
#define __MMI_MAE_CUSTOMIZATION_H__
#define CUS_VERSION_NUM 0x01010101
//cus version format : xx.xx.xx.xx , XRG read this define and put it into CUS file
#include "mmi_mae_common_def.h"
#include "mmi_core_forward.h"
#include "mmi_mae_customization_forward.h"

//////////////////////////////////////////////////////////////////
//Initialization and Free Functions

/**
 *  MAECusInitialize
 *  @brief  Initializes CUS
 *
 *  @return MAE_RETURN_SUCCESS if initialized successfully
 *          MAE_RETURN_FAILED  if failed to initialize
 */
MAE_Ret MAECusInitialize(void);

/**
 *  MAECusReleaseMem
 *  @brief  Releases memory used while parsing CUS.
 *
 */
void MAECusReleaseMem(void);

//////////////////////////////////////////////////////////////////
/**
*  MAECusGetID
*  @brief  Retrieves version number of the cus
*
*  @return  u8 cusid
*/
u8* MAECusGetID(void);

//////////////////////////////////////////////////////////////////
/**
 *  MAECusGetLangData
 *  @brief  Gets the text data for the current language
 *
 *  @param  [in ]textID      text id
 *  @param  [out]ppTextData  pointer to the data result
 *
 *  @return MAE_RETURN_SUCCESS if text data is retrieved successfully
 *          MAE_RETURN_FAILED  if text data is retrieved unsuccessfully
 */
MAE_Ret MAECusGetLangData(u32 nTextID, u16** ppTextData);

/**
 *  MAECusGetLangDataWithIdx
 *  @brief  Gets the text data for the given language idx
 *
 *  @param  [in ]textID      text id
 *  @param  [in ]langIdx     language idx
 *  @param  [out]ppTextData  pointer to the data result
 *
 *  @return MAE_RETURN_SUCCESS if text data is retrieved successfully
 *          MAE_RETURN_FAILED  if text data is retrieved unsuccessfully
 */
MAE_Ret MAECusGetLangDataWithIdx(u32 nTextID, u16 nLangIdx, u16** ppTextData);

/**
 *  MAECusGetTextLabelNum
 *  @brief  Gets the number of text label for the given AP idx
 *
 *  @param  [in ]nAPId			text id
 *  @param  [out]pNumLabels		pointer to the data result
 *
 *  @return MAE_RETURN_SUCCESS if text label is retrieved successfully
 *          MAE_RETURN_FAILED  if text label is retrieved unsuccessfully
 */
MAE_Ret MAECusGetTextLabelNum(u16 nAPId, u16 *pNumLabels);

/**
 *  MAECusGetIndexFromLangCode
 *  @brief  Gets language id for the given language code.  Default idx is returned for language not supported
 *
 *  @param  [in ]nLangCode    language code
 *  @param  [out]pIndex      pointer of result language idx stored
 *
 *  @return MAE_RETURN_SUCCESS if language is supported
 *          MAE_RETURN_FAILED  if language is not support, but pIndex will store the default language idx
 */
MAE_Ret MAECusGetIndexFromLangCode(u8 nLangCode, u16 *pIndex);  //return default if lang is not supported

/**
*  MAECusGetLanguageName
*  @brief  Gets language Display Name for the given language code.  Default language Display Name is returned for language not supported
*
*  @param  [in ]nLangCode      language code
*  @param  [out]ppTextData    pointer to the data result
*
*  @return MAE_RETURN_SUCCESS if language is supported
*          MAE_RETURN_FAILED  if language is not support, but pplangName will store the language Display Name
*/
MAE_Ret MAECusGetLanguageName(u8 nLangCode,u16** pplangName);

/**
*  MAECusGetDefaultLanguage
*  @brief  Gets the Default language
*
*  @return u16 the current language code
*/
u16 MAECusGetDefaultLanguage(void);

/**
 *  MAECusSetLanguage
 *  @brief  Sets the current language
 *
 *  @param  [in ]nLangCode    language code
 *
 *  @return MAE_RETURN_SUCCESS if language is set successfully
 *          MAE_RETURN_FAILED  if language is not set successfully
 */
MAE_Ret MAECusSetLanguage(u8 nLangCode);

/**
 *  MAECusGetLanguage
 *  @brief  Gets the current language
 *
 *  @return u16 the current language code
 */
u16 MAECusGetLanguage(void);

/**
*  MAECusGetLanguageNum ( include no-trans )
*  @brief  Gets the language number
*
*  @return u8 the the language number
*/
u8 MAECusGetLanguageNum(void);

/**
*  MAECusGetAllLanguage ( include no-trans )
*  @brief  Gets the all language data
*
*  @return MAE_RETURN_SUCCESS if languages are get successfully
*          MAE_RETURN_FAILED  if languages are not get successfully
*/
MAE_Ret MAECusGetAllLanguage(CusLangCodeIndexMapping_t** ppCusLangCodeIndexMapping_t);


/**
 *  MAECusIsSupportSmartInput
 *  @brief  Check whether the language supports smart input.
 *
 *  @param  [in ]nLangCode    language code
 *
 *  @return TRUE It supports smart input.
 *          FALSE  It doesn't support smart input.
 */
boolean MAECusIsSupportSmartInput(u16 nLangCode);

//////////////////////////////////////////////////////////////////

/**
 *  MAECusGetMediaInfo
 *  @brief  Gets the media info for the given id
 *
 *  @param  [in ]nMediaID       media id
 *  @param  [out]pMediaInfo    pMediaInfo
 *  @param  [in ]nFormatType    process image or melody cus
 *  @return MAE_RETURN_SUCCESS if retrieving info successfully
 *          MAE_RETURN_FAILED  if failed to retrieve info
 */
MAE_Ret MAECusGetMediaInfo(u32 nMediaID, CusMediaInfo_t* pMediaInfo, CUS_FORMAT_TYPE_e nFormatType);

/**
 *  MAE_CusMediaIdToUrl
 *  @brief  Gets the media url for the given media id
 *
 *  @param  [in ]nMediaID       media id
 *  @param  [out]pUrl          pointer that stores the url
 *  @param  [in ]nFormatType    process image or melody cus
 *  @return MAE_RET_SUCCESS if retrieving info successfully
 *          MAE_RET_FAILED  if failed to retrieve info
 */
MAE_Ret MAE_CusMediaIdToUrl(u32 nMediaID, u16** ppUrl, CUS_FORMAT_TYPE_e eFormatType);

/**
 *  MAECusUrlToMediaId
 *  @brief  Gets the media id for the given url
 *
 *  @param  [in ]pUrl          pointer to a ad url
 *  @param  [out]pMediaID      pointer that stores the nMediaID
 *  @param  [in ]nFormatType    process image or melody cus
 *  @return MAE_RET_SUCCESS if retrieving info successfully
 */
MAE_Ret MAECusUrlToMediaId(const u16* pUrl, u32* pMediaID, CUS_FORMAT_TYPE_e* pFormatType);


/**
 *  MAECusUrlToMediaData
 *  @brief  Gets the nSize and raw data pointer for the given url
 *
 *  @param  [in ]pUrl          pointer to a ad url
 *  @param  [in ]pMimeType     pointer to media mime type
 *  @param  [out]pSize         pointer that stores the nSize
 *  @param  [out]ppRawData     pointer that stores the raw data
 *  @return MAE_RET_SUCCESS if retrieving info successfully
 */
MAE_Ret MAECusUrlToMediaData(const u16* pUrl, u8* pMimeType, u32* pSize, u8 **ppRawData, ThmHead_t **ppTheme);

/**
 *  MAECusGetMediaData
 *  @brief  Gets the pointer to the media data, along with its informat for the given media ID
 *
 *  @param  [in ]nMediaID       media ID
 *  @param  [in ]pMimeType     pointer to media mime type
 *  @param  [out]pSize         pointer of media nSize
 *  @param  [out]ppRawData     pointer of media raw data
 *  @param  [in ]nFormatType    media's format type: image or melody

 *  @return MAE_RET_SUCCESS if retrieving media data successfully
 *          MAE_RET_FAILED if retrieving media data unsuccessfully
 */
MAE_Ret MAECusGetMediaData(u32 nMediaID, u8 *pMimeType, u32 *pSize, u8 **ppRawData, CUS_FORMAT_TYPE_e nFormatType, ThmHead_t **ppTheme);


/**
*  MAECusGetPreDefinedImgStartIndex
*  @brief  Get the starting index of predefined image.
*
*  @param  [in ]pTheme			the theme
*  @param  [in ]nAPID			AP ID
*  @param  [out]pStartIndex		pointer to the start index
*
*  @return MAE_RETURN_SUCCESS Get the start index successfully.
*          MAE_RETURN_FAILED  failed.
*/
MAE_Ret MAECusGetPreDefinedImgStartIndex(const ThmHead_t *pTheme, u32 nAPID, u32 *pStartIndex);

/**
*  MAECusGetPredefinedImageTextID
*  @brief  Get the text ID of the predefined image
*
*  @param  [in ]nMediaID		The image ID.
*  @param  [out]pTextID			pointer to the text ID.
*
*  @return MAE_RETURN_SUCCESS	Get the text ID successfully.
*          MAE_RETURN_FAILED	failed.
*/
MAE_Ret MAECusGetPredefinedImageTextID(u32 nMediaID, u32 *pTextID);

/**
*  MAECusIsDefaultMediaExist
*  @brief  Check if the predefined media exists or not
*
*  @param  [in ]nMediaID		The image ID.
*  @param  [in ]nFormatType		The format of the media.
*
*  @return TRUE		Get the text ID successfully.
*          FALSE	failed.
*/
boolean MAECusIsDefaultMediaExist(u32 nMediaID, CUS_FORMAT_TYPE_e nFormatType);

/**
*  MAECusGetMediaText
*  @brief  Get the text data of the media
*
*  @param  [in ]nMediaID			The image ID.
*  @param  [out]ppTextData			pointer to the text data.
*  @param  [in ]nFormatType			The format of the media.
*
*  @return MAE_RETURN_SUCCESS	Get the text successfully.
*          MAE_RETURN_FAILED	failed.
*/
MAE_Ret MAECusGetMediaText(u32 nMediaID, u16 **ppTextData, CUS_FORMAT_TYPE_e nFormatType);

/**
 *  MAECusGetNumInstallImage
 *  @brief  Gets the number install images
 *
 *  @return u32  number of install images
 */
u32 MAECusGetNumInstallImage(void);

/**
 *  MAECusGetNumInstallMelody
 *  @brief  Gets the number install melody
 *
 *  @return u32  number of install melody
 */
u32 MAECusGetNumInstallMelody(void);

//////////////////////////////////////////////////////////////////
/**
 *  MAECusGetNumPLMN
 *  @brief  Gets the number of plmn records
 *
 *  @return u32 number of plmn records
 */
u32 MAECusGetNumPLMN(void);

/**
 *  MAECusGetPLMN
 *  @brief  Gets plmn record for the given mcc and mnc
 *
 *  @param  [in ]mcc          mcc
 *  @param  [in ]mnc          mnc
 *  @param  [out]pPlmnRecord  pointer to the retrieved plmn record
 *
 *  @return MAE_RETURN_SUCCESS if retrieved successfully
 *          MAE_RETURN_FAILED  if retrieved unsucessfully
 */
MAE_Ret MAECusGetPLMN(u16 nMcc, u16 nMnc, CusPLMNRecord_t* pPlmnRecord);

/**
 *  MAEGetPLMNRecordByIdx
 *  @brief  Gets plmn record with given index
 *
 *  @param  [in ]index        index
 *  @param	[out]pPlmnRecord  pointer to the retrieved plmn record
 *
 *  @return MAE_RETURN_SUCCESS if retrieved successfully
 *          MAE_RETURN_FAILED  if retrieved unsucessfully
 */
MAE_Ret MAEGetPLMNRecordByIdx(u16 nIndex, CusPLMNRecord_t* pPlmnInfo);

/**
 *  MAECusGetMccMnc
 *  @brief  Gets mcc and mnc for the given number
 *
 *  @param  [in ]numeric     number
 *  @param  [out]Mcc         pointer to retrieved mcc
 *  @param  [out]Mnc         pointer to retrieved mnc
 *
 *  @return MAE_RETURN_SUCCESS if retrieved successfully
 *          MAE_RETURN_FAILED  if retrieved unsuccessfully
 */
void MAECusGetMccMnc(u32 nNumeric, u16* Mcc, u16* Mnc);

//////////////////////////////////////////////////////////////////
//Font Functions
/**
 *  MAECusGetFontData
 *  @brief  Gets font data
 *
 *  @return u8*  pointer to the font data
 */
const u8* MAECusGetFontData(void);

//////////////////////////////////////////////////////////////////
//Font Functions
/**
 *  MAECusLoadFontDataToMem
 *  @brief  Load font data from Cus to Mem
 *
 *  @return MAE_RETURN_SUCCESS if Load successfully
 *          MAE_RETURN_FAILED  if Load unsuccessfully
*/
MAE_Ret MAECusLoadFontDataToMem(void);

/**
*  MAECusFreeFontData
*  @brief  Free the Font data loaded.
*
*  @param  [in ]pData	The data
*
*  @return none.
*/
void MAECusFreeFontData(void);

//////////////////////////////////////////////////////////////////
//Font Functions
/**
 *  MESCusGetKMXFontData
 *  @brief  Gets KMXfont data
 *
 *  @return u8*  pointer to the font data
 */
const u8* MAECusGetKMXFontData(void);


//////////////////////////////////////////////////////////////////
/**
*  MAECusGetInputInfo
*  @brief  Gets input info
*
*  @return CusInput_t input info
*/
CusInput_t* MAECusGetInputInfo(void);

/**
*  MAECusGetDefaultInputLanguage
*  @brief  Gets the Default input language
*  @param  [in ]nIMECode			ime code
*  @param  [out]pu8DefLangCode       pointer of default language code
*
*  @return MAE_RETURN_SUCCESS if ime is supported
*          MAE_RETURN_FAILED  if ime is not support
*/
MAE_Ret MAECusGetDefaultInputLanguage(u8 nIMECode,u8 *nDefLangCode);

/**
*  MAECusGetInputLanguageNum
*  @brief  Gets the language number
*  @param  [in ]nIMECode		  ime code
*  @param  [out]pu16LangNum		  pointer of language num
*
*  @return MAE_RETURN_SUCCESS if ime is supported
*          MAE_RETURN_FAILED  if ime is not support
*/
MAE_Ret MAECusGetInputLanguageNum(u8 nIMECode,u16 *pLangNum);

/**
*  MAECusGetAllInputLanguage
*  @brief  Gets the all input language data
*  @param  [in ]nIMECode			    ime code
*  @param  [out]ppCusInputLangData_t    pointer of CusInputLangData_t
*
*  @return MAE_RETURN_SUCCESS if languages are get successfully
*          MAE_RETURN_FAILED  if languages are not get sucessfully
*/
MAE_Ret MAECusGetAllInputLanguage(u8 nIMECode,CusInputLangData_t** ppCusInputLangData_t);

/**
*  MAECusGetInputLanguageName
*  @brief  Gets language Display Name for the given language code.  Default language Display Name is returned for language not supported
*
*  @param  [in ]nIMECode		ime code
*  @param  [in ]nLangCode		language code
*  @param  [out]pplangName		language Display Name
*  @param  [out]pNameLen		language Display length
*
*  @return MAE_RETURN_SUCCESS if language is supported
*          MAE_RETURN_FAILED  if language is not support, but pplangName will store the language Display Name
*/
MAE_Ret MAECusGetInputLanguageName(u8 u8IMECode,u8 langCode,u16** pplangName, u16 *pNameLen);

/**
*  MAECusGetInputLanguageArrayNum
*  @brief  Gets array nSize for the given language code.
*
*  @param  [in ]nIMECode     ime code
*  @param  [in ]nLangCode      language code
*  @param  [out]pu16ArrayNum  language array num
*
*  @return u16 array nSize , 0 for not support lang
*/
MAE_Ret MAECusGetInputLanguageArrayNum(u8 nIMECode,u8 nLangCode,u16* pArrayNum);

/**
*  MAECusGetOnlyInputArrayDataWithIdx
*  @brief  Gets the array data for the given language idx
*
*  @param  [in ]nIMECode			ime code
*  @param  [in ]nLangIdx			language code
*  @param  [out]ppArrayData			pointer to the data result
*  @param  [out]pArrayDataSize		pointer to the data size
*  @param  [in ]nSize				The number of the array
*
*  @return MAE_RETURN_SUCCESS if text data is retrieved successfully
*          MAE_RETURN_FAILED  if text data is retrieved unsuccessfully
*/
MAE_Ret MAECusGetOnlyInputArrayDataWithIdx(u8 nIMECode, u16 nLangIdx, u8** ppArrayData, u32 *pArrayDataSize, u16 nSize);

/**
*  MAECusGetInputIndexFromLangCode
*  @brief  Gets language id for the given language code.  Default idx is returned for language not supported
*
*  @param  [in ]nIMECode     ime code
*  @param  [in ]nLangCode      language code
*  @param  [out]pIndex        pointer to the data result
*
*  @return MAE_RETURN_SUCCESS if language is supported
*          MAE_RETURN_FAILED  if language is not support, but pIndex will store the defualt languague idx
*/
MAE_Ret MAECusGetInputIndexFromLangCode(u8 nIMECode,u8 nLangCode, u16 *pIndex);  //return default if lang is not supported

//////////////////////////////////////////////////////////////////
//HandWrite Functions

/**
*  MAECusGetHandWrite
*  @brief  Gets handwrite info
*
*  @return CusHandwrite_t handwrite info
*/
CusHandwrite_t* MAECusGetHandWrite(void);


/**
*  MAECusGetOnlyHandWriteArrayData
*  @brief  Gets the array data for the given language idx
*
*  @param  [in ]nHWCode			hw code
*  @param  [out]ppArrayData		pointer to the data result
*  @param  [out]pArrayDataSize  pointer to the data size
*  @param  [in ]nArraySize		Array size
*
*  @return MAE_RETURN_SUCCESS	Get the data successfully
*          MAE_RETURN_FAILED	failed
*/
MAE_Ret MAECusGetOnlyHandWriteArrayData(u8 nHWCode, u8** ppArrayData, u32 *pArrayDataSize, u16 nArraySize);

//////////////////////////////////////////////////////////////////
/**
*  MAECusGetRC
*  @brief  Get the RS data of AP/window
*
*  @param  [in ]apid			The AP ID.
*  @param  [in ]wndid			The window ID
*
*  @return The RS data.
*/
void* MAECusGetRC(u16 apid, u16 wndid);

/**
*  MAECusChangeThm
*  @brief  Change theme according to the theme ID.
*
*  @param  [in ]nThmNameId		The theme ID.
*
*  @return TRUE		Found and change the theme.
*          FALSE	Don't change to the specified theme.
*/
boolean MAECusChangeThm(u32 nThmNameId);

/**
*  MAECusGetCurrentThm
*  @brief  Get current theme ID.
*
*  @return Current theme ID.
*/
u32 MAECusGetCurrentThm(void);

/**
*  MAECusGetThemesNum
*  @brief  Get total number of theme.
*
**  @return Total number of theme.
*/
u16 MAECusGetThemesNum(void);

/**
*  MAECusGetThemesID
*  @brief  Get all theme IDs.
*
*  @param  [out]pId		Pointer to the array to save the theme ID.
*  @param  [in ]nNum	Total num of theme.
*
*  @return TRUE		Get the theme ID successfully.
*          FALSE	failed.
*/
MAE_Ret MAECusGetThemesID(u32 *pId, u16 nNum);

/**
*  MAECusSetRsLayout
*  @brief  Set RS layout according to the theme
*
*  @param  [in ]pThm	The theme.
*
*  @return TRUE		Set RS layout successfully.
*          FALSE	failed.
*/
MAE_Ret MAECusSetRsLayout(ThmHead_t* pThm);

/**
*  MAECusGetCurrAngle
*  @brief  Get angle of current theme.
*
*  @return The angle of current theme
*/
u16 MAECusGetCurrAngle(void);

/**
*  MAECusGetDefaultThmAngle
*  @brief  Get angle of default theme.
*
*  @return TRUE		The angle of default theme.
*/
u16 MAECusGetDefaultThmAngle(void);

/**
*  MAECusGetThemeDataAt
*  @brief  Get system theme append data at the offset.
*
*  @param  [in ]nOffset	The offset.
*  @param  [in ]nLen	The length of data needs to load
*
*  @return The data.
*/
u8 *MAECusGetThemeDataAt(u32 nOffset, u32 nLen);

/**
*  MAECusFreeThemeData
*  @brief  Free the data loaded previously.
*
*  @param  [in ]pData	The data
*
*  @return none.
*/
void MAECusFreeThemeData(void* pData);

/**
*  MAECusGetThirdDataAt
*  @brief  Get system theme third data.
*
*  @param  [in ]nIndex	The index of the third data.
*  @param  [in ]nOffset	The offset.
*  @param  [in ]nLen	The length of data needs to load
*
*  @return The data.
*/
u8 *MAECusGetThirdDataAt(u8 nIndex, u32 nOffset, u32 nLen);

/**
*  MAECusGetThirdSizeAt
*  @brief  Get third data size according to the index.
*
*  @param  [in ]nIndex	The index of the third data.
*
*  @return The size.
*/
u32 MAECusGetThirdSizeAt(u8 nIndex);

/**
*  MAECusFreeThirdData
*  @brief  Free the third data loaded previously.
*
*  @param  [in ]pData	The data
*
*  @return none.
*/
void MAECusFreeThirdData(void* pData);

/**
*  MAECusGetThemePreDefinedImg
*  @brief  Get the image index of predefined image.
*
*  @param  [in ]nMediaID	The image ID.
*
*  @return The image index.
*/
u32 MAECusGetThemePreDefinedImg(u32 nMediaID);

/**
*  MAECusGetPrjHead
*  @brief  Get the global variable "_g_pPrjHead" of CUS.
*
*  @return _g_pPrjHead.
*/
const PrjHead_t* MAECusGetPrjHead(void);

/**
*  MAECusGetCurrThm
*  @brief  Get the current theme of CUS.
*
*  @return Current theme.
*/
const ThmHead_t* MAECusGetCurrThm(void);

/**
*  MAECusSetThemeColor
*  @brief  Set theme color according to the specified theme.
*
*  @param  [in ]pThm	The theme.
*
*  @return TRUE		Set theme color successfully.
*          FALSE	failed.
*/
MAE_Ret MAECusSetThemeColor(ThmHead_t* pThm);


/**
*  MAECusGetIndexFromImageID
*  @brief  Get the relative index of the image ID.
*
*  @param  [in ]pImageData	The image data structure.
*  @param  [in ]nImageID	The image ID.
*  @param  [out]pIndex		Pointer to image index.
*
*  @return TRUE		Get the image index successfully.
*          FALSE	failed.
*/
MAE_Ret MAECusGetIndexFromImageID(CusImageData_t *pImageData, u32 nImageID, u32 *pIndex);


/**
*  MAECusGetIndexFromMediaID
*  @brief  Get the relative index of the media ID.
*
*  @param  [in ]pThm		The theme.
*  @param  [in ]nMediaID	The media ID.
*  @param  [in ]nFormatType	The format of the media.
*  @param  [out]pIndex		Pointer to media index.
*
*  @return TRUE		Get the media index successfully.
*          FALSE	failed.
*/
MAE_Ret MAECusGetIndexFromMediaID(ThmHead_t *pThm, u32 nMediaID, CUS_FORMAT_TYPE_e nFormatType, u32 *pIndex);


/**
*  MAECusLoadThmAP
*  @brief  Load theme data of the specified AP.
*
*  @param  [in ]u16ApId		The AP ID.
*  @param  [in ]pThmHeader	The theme.
*
*  @return TRUE		Load the theme of the AP successfully.
*          FALSE	Others.
*/
boolean MAECusLoadThmAP(u16 u16ApId, ThmHead_t *pThmHeader);

/**
*  MAECusReleaseThmAP
*  @brief  Release the theme data (memory) of the AP loaded previously.
*
*  @param  [in ]nApId		The AP ID.
*  @param  [in ]pThmHeader	The theme.
*
*  @return none.
*/
void MAECusReleaseThmAP(u16 nApId, ThmHead_t *pThmHeader);

/**
*  MAECusSetCurrentRsLayout
*  @brief  Set current RS layout
*
*  @param  [in ]pRSLayout		Pointer to the RS layout.
*
*  @return none.
*/
void MAECusSetCurrentRsLayout(u16 *pRSLayout);

/**
*  MAECusGetCurrentRsLayout
*  @brief  Get current RS layout
*
*  @return Pointer to the RS layout.
*/
u16* MAECusGetCurrentRsLayout(void);

/**
*  MAECusGetImageResByTheme
*  @brief  Get image resource according to the image ID.
*
*  @param  [in ]pThm			The theme.
*  @param  [in ]nImageID		The image ID.
*
*  @return The pointer to the image data structure.
*/
CusImageData_t *MAECusGetImageResByTheme(ThmHead_t *pThm, u32 nImageID);

/**
*  MAECusFreeInputArrayDataWithIdx
*  @brief  Free the input data.
*
*  @param  [in ]pMem	Pointer to the memory to be freed.
*
*  @return none.
*/
void MAECusFreeInputArrayDataWithIdx(void *pMem);

/**
*  MAECusSetCurrentTheme
*  @brief  Set current theme.
*
*  @param  [in ]pThm	Pointer to the theme.
*
*  @return none.
*/
void MAECusSetCurrentTheme(const ThmHead_t *pThm);

/**
*  MAECusDefaultIMGIfExist
*  @brief  Search the predefined images and save the existing image ID.
*
*  @return none.
*/
void MAECusDefaultIMGIfExist(void);

/**
*  MAECusApLoadRc
*  @brief  Load AP resource.
*
*  @param  [in ]nAPResId		The AP resource ID.
*
*  @return	MAE_RET_SUCCESS		Load the AP resource successfully.
*			MAE_RET_FAILED		failed.
*/
MAERet_t MAECusApLoadRc( u16 nAPResId );

/**
*  MAECusApReleaseRc
*  @brief  Release AP resource.
*
*  @param  [in ]nAPResId		The AP resource ID.
*
*  @return	none.
*/
void MAECusApReleaseRc( u16 nAPResId );

/**
*  MAECusReleaseCustomizationThemeRc
*  @brief  Release all AP resource.
*
*  @param  [in ]pThm			The theme
*
*  @return	none.
*/
void MAECusReleaseCustomizationThemeRc(ThmHead_t *pThm);


#endif //__MAE_CUSTOMIZATION_H__
