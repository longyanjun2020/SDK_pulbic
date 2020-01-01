/**
 * @file    mmi_mae_resource.h
 * @brief   The document describes the interface to obtain resourses like text and menu.
 * @author  sam.chen@mstarsemi.com
 * @page    Phone resource Interface
 * @version $Id: mmi_mae_resource.h 972 2009-05-25 17:07:19Z mark.yang $
 */
#ifndef __MMI_MAE_RESOURCE_H__
#define __MMI_MAE_RESOURCE_H__
#include "mmi_mae_resource_forward.h"
#include "mmi_mae_customization_forward.h"
#include "mmi_mae_langcode.h"

/**
 *  MAE_CusInitialize
 *  @brief  Initializes CUS
 *
 *  @return MAE_RETURN_SUCCESS if initialized successfully
 *          MAE_RETURN_FAILED  if failed to initialize
 */
MAE_Ret MAE_CusInitialize(void);

/**
 *  MAE_CusReleaseMem
 *  @brief  Releases memory used while parsing CUS.
 *
 */
void MAE_CusReleaseMem(void);

/**
 *  MAE_CusGetMediaInfo
 *  @brief  Gets the media info for the given id
 *
 *  @param  [in ]nMediaID       media id
 *  @param  [out]pMediaInfo    pMediaInfo
 *  @param  [in ]nFormatType    process image or melody cus
 *  @return MAE_RETURN_SUCCESS if retrieving info successfully
 *          MAE_RETURN_FAILED  if failed to retrieve info
 */
MAE_Ret MAE_CusGetMediaInfo(u32 nMediaID, CusMediaInfo_t* pMediaInfo, CUS_FORMAT_TYPE_e nFormatType);


/**
 *  MAE_CusGetMediaInfo
 *  @brief  Gets the media info for the given id
 *
 *  @param  [in ]nMediaID       media id
 *  @param  [out]pMediaInfo    pMediaInfo
 *  @param  [in ]nFormatType    process image or melody cus
 *  @return MAE_RETURN_SUCCESS if retrieving info successfully
 *          MAE_RETURN_FAILED  if failed to retrieve info
 */
MAE_Ret MAE_CusGetMediaInfo(u32 nMediaID, CusMediaInfo_t* pMediaInfo, CUS_FORMAT_TYPE_e nFormatType);

/**
 *  MAE_CusUrlToMediaId
 *  @brief  Gets the media id for the given url
 *
 *  @param  [in ]pUrl          pointer to a ad url
 *  @param  [out]pMediaID      pointer that stores the nMediaID
 *  @param  [in ]nFormatType    process image or melody cus
 *  @return MAE_RET_SUCCESS if retrieving info successfully
 */
MAE_Ret MAE_CusUrlToMediaId(const u16* pUrl, u32* pMediaID, CUS_FORMAT_TYPE_e* pFormatType);

/**
 *  MAE_CusUrlToMediaData
 *  @brief  Gets the nSize and raw data pointer for the given url
 *
 *  @param  [in ]pUrl          pointer to a ad url
 *  @param  [in ]pMimeType     pointer to media mime type
 *  @param  [out]pSize         pointer that stores the nSize
 *  @param  [out]ppRawData     pointer that stores the raw data
 *  @return MAE_RET_SUCCESS if retrieving info successfully
 */
MAE_Ret MAE_CusUrlToMediaData(const u16* pUrl, u8* pMimeType, u32* pSize, u8 **ppRawData, ThmHead_t **ppTheme);

/**
*  MAE_CusGetThemePreDefinedImg
*  @brief  Get the image index of predefined image.
*
*  @param  [in ]nMediaID	The image ID.
*
*  @return The image index.
*/
u32 MAE_CusGetThemePreDefinedImg(u32 nMediaID);

/**
*  MAE_CusGetDefaultLanguage
*  @brief  Gets the Default language
*
*  @return u16 the current language code
*/
u16 MAE_CusGetDefaultLanguage(void);

/**
*  MAE_CusGetMediaText
*  @brief  Get the text data of the media
*
*  @param  [in ]nMediaID			The image ID.
*  @param  [out]ppTextData			pointer to the text data.
*  @param  [in ]nFormatType			The format of the media.
*
*  @return MAE_RETURN_SUCCESS	Get the text successfully.
*          MAE_RETURN_FAILED	failed.
*/
MAE_Ret MAE_CusGetMediaText(u32 nMediaID, u16 **pTextData, CUS_FORMAT_TYPE_e nFormatType);

/**
 *  MAE_CusGetNumPLMN
 *  @brief  Gets the number of plmn records
 *
 *  @return u32 number of plmn records
 */
u32 MAE_CusGetNumPLMN(void);

/**
 *  MAE_CusGetPLMN
 *  @brief  Gets PLMN record for the given mcc and mnc
 *
 *  @param  [in ]mcc          mcc
 *  @param  [in ]mnc          mnc
 *  @param  [out]pPlmnRecord  pointer to the retrieved plmn record
 *
 *  @return MAE_RETURN_SUCCESS if retrieved successfully
 *          MAE_RETURN_FAILED  if retrieved unsucessfully
 */
MAE_Ret MAE_CusGetPLMN(u16 nMcc, u16 nMnc, CusPLMNRecord_t* pPlmnRecord);

/**
 *  MAE_CusGetMccMnc
 *  @brief  Gets mcc and mnc for the given number
 *
 *  @param  [in ]numeric     number
 *  @param  [out]Mcc         pointer to retrieved mcc
 *  @param  [out]Mnc         pointer to retrieved mnc
 *
 *  @return MAE_RETURN_SUCCESS if retrieved successfully
 *          MAE_RETURN_FAILED  if retrieved unsuccessfully
 */
void MAE_CusGetMccMnc(u32 nNumeric, u16* pMcc, u16* pMnc);


/**
 *  MAE_GetPLMNRecordByIdx
 *  @brief  Gets PLMN record with given index
 *
 *  @param  [in ]index        index
 *  @param	[out]pPlmnRecord  pointer to the retrieved plmn record
 *
 *  @return MAE_RETURN_SUCCESS if retrieved successfully
 *          MAE_RETURN_FAILED  if retrieved unsucessfully
 */
MAE_Ret MAE_GetPLMNRecordByIdx(u16 nIndex, CusPLMNRecord_t* pPlmnInfo);

/**
*  MAE_CusGetInputLanguageArrayNum
*  @brief  Gets array nSize for the given language code.
*
*  @param  [in ]nIMECode     ime code
*  @param  [in ]nLangCode      language code
*  @param  [out]pu16ArrayNum  language array num
*
*  @return u16 array nSize , 0 for not support lang
*/
MAE_Ret MAE_CusGetInputLanguageArrayNum(u8 nIMECode,u8 nLangCode,u16* pArrayNum);

/**
*  MAE_CusGetThemeDataAt
*  @brief  Get system theme append data at the offset.
*
*  @param  [in ]nOffset	The offset.
*  @param  [in ]nLen	The length of data needs to load
*
*  @return The data.
*/
u8 *MAE_CusGetThemeDataAt(u32 nOffset, u32 nLen);

/**
*  MAE_CusFreeThemeData
*  @brief  Free the data loaded previously.
*
*  @param  [in ]pData	The data
*
*  @return none.
*/
void MAE_CusFreeThemeData(void* pData);

/**
*  MAE_CusGetThirdDataAt
*  @brief  Get system theme third data.
*
*  @param  [in ]nIndex	The index of the third data.
*  @param  [in ]nOffset	The offset.
*  @param  [in ]nLen	The length of data needs to load
*
*  @return The data.
*/
u8 *MAE_CusGetThirdDataAt(u8 nIndex, u32 nOffset, u32 nLen);

/**
*  MAE_CusGetThirdSizeAt
*  @brief  Get third data size according to the index.
*
*  @param  [in ]nIndex	The index of the third data.
*
*  @return The size.
*/
u32 MAE_CusGetThirdSizeAt(u8 nIndex);

/**
*  MAE_CusFreeThirdData
*  @brief  Free the third data loaded previously.
*
*  @param  [in ]pData	The data
*
*  @return none.
*/
void MAE_CusFreeThirdData(void* pData);


/**
 *  MAE_ResInitialize
 *  @brief  Initializes RES
 */
void MAE_ResInitialize(void);

/**
*  mae_GetResourceID
*  @brief  Gets the resource id
*
*  @return u8*          pointer to the retrieved text data
*/
const u8* mae_GetResourceID(void);

/**
 *  mae_GetTextLabel
 *  @brief  Gets the textlabel data for the given text id
 *
 *  @param  [in ]nTextID       text id
 *  @return u16*          pointer to the retrieved text data
 */
const u16* mae_GetTextLabel(u32 nTextID);

/**
 *  mae_lang_GetTextLabel
 *  @brief  Gets the textlabel data for the given text id and language code
 *
 *  @param  [in ]nLangCode      language code
 *  @param  [in ]nTextID       text id
 *  @return u16*          pointer to the retrevied text data
 */
const u16* mae_lang_GetTextLabel(MAE_LANG_CODE_e nLangCode, u32 nTextID);

/**
 *  mae_GetTextLabelNum
 *  @brief  Gets the number of text label for the given AP id
 *
 *  @param  [in ]nAPId      AP id
 *  @return u16				The number of text label
 */
u16 mae_GetTextLabelNum(u16 nAPId);

/**
*  mae_GetDefaultLanguage
*  @brief  Gets the Default language
*
*  @param  [out]nLangCode      language code
*  @return MAE_RETURN_SUCCESS if set successfully
*          MAE_RETURN_FAILED  if set unsuccessfully
*/
MAE_Ret mae_GetDefaultLanguage(MAE_LANG_CODE_e *pLangCode);

/**
 *  mae_SetLanguage
 *  @brief  Sets the current language
 *
 *  @param  [in ]nLangCode      language code
 *  @return MAE_RETURN_SUCCESS if set successfully
 *          MAE_RETURN_FAILED  if set unsuccessfully
 */
MAE_Ret mae_SetLanguage(MAE_LANG_CODE_e nLangCode);

/**
 *  mae_GetLanguage
 *  @brief  Gets the current language
 *
 *  @param  [out]pLangCode      pointer to the retrieved language code
 *
 *  @return MAE_RETURN_SUCCESS if gets current language successfully
 *          MAE_RETURN_FAILED  if gets current language unsuccessfully
 */
MAE_Ret mae_GetLanguage(MAE_LANG_CODE_e *pLangCode);

/**
*  mae_GetLanguage
*  @brief  Gets the language number
*
*  @return u8 the the language number
*/
u8 mae_GetLanguageNum(void);

/**
*  mae_GetLanguageName
*  @brief  Gets the language name
*
*  @param  [in ]pLangCode      language code
*  @param  [out]ppLangName     pointer to the retrieved language name
*
*  @return MAE_RETURN_SUCCESS if gets language name successfully
*          MAE_RETURN_FAILED  if gets language name unsuccessfully
*/
MAE_Ret mae_GetLanguageName(MAE_LANG_CODE_e nLangCode,u16** ppLangName);

/**
*  mae_GetAllLanguageData
*  @brief  Gets All language data
*
*  @param  [out]pLangData      the MAE_LangData_t array
*  @param  [in ]u8Size		   the MAE_LangData_t array memory byte size
*
*  @return MAE_RETURN_SUCCESS if gets language data successfully
*          MAE_RETURN_FAILED  if gets language data unsuccessfully
*/
MAE_Ret mae_GetAllLanguageData(MAE_LangData_t *pLangData,u8 u8Size);

/**
 *  mae_LoadResImage
 *  @brief  Gets the image with given image id
 *
 *  @param  [in ]nImageID      image id
 *  @param  [out]pMimeType     pointer to image mime type
 *  @param  [out]pSize         pointer to image size
 *  @param  [out]ppRawData     pointer to image raw data
 *  @param  [out]ppTheme	   pointer to the theme
 *
 *  @return MAE_RETURN_SUCCESS if gets resource image successfully
 *          MAE_RETURN_FAILED  if gets resource image unsuccessfully
 */
MAE_Ret mae_LoadResImage(u32 nImageID, u8 *pMimeType, u32 *pSize, u8 **ppRawData, ThmHead_t **ppTheme);

/**
 *  mae_LoadResMelody
 *  @brief  Gets the melody with given melody id
 *
 *  @param  [in ]nMelodyID     melody id
 *  @param  [out]pMimeType     pointer to melody mime type
 *  @param  [out]pSize         pointer to melody size
 *  @param  [out]ppRawData     pointer to melody raw data
 *
 *  @return MAE_RETURN_SUCCESS if gets successfully
 *          MAE_RETURN_FAILED  if gets unsuccessfully
 */
MAE_Ret mae_LoadResMelody(u32 nMelodyID, u8 *pMimeType, u32* pSize, u8 **ppRawData);

/////////////////////////////////////////////////
// For MAE internal use only
/**
 *  mae_GetVdd
 *  @brief  Gets the vdd for the given vdd id
 *
 *  @param  nVddID        vdd id
 *
 *  @return u8*    pointer to the vdd raw data
 */
const u8* mae_GetVdd(u32 nVddID, u32 *pu32DataSize);

/**
 *  mae_FreeVdd
 *  @brief  Frees the vdd for the given vdd id
 *
 *  @param  nVddID        vdd id
 *
 *  @return u8*    pointer to the vdd raw data
 */
void mae_FreeVdd(u32 nVddID);

/**
 *  mae_GetFontData
 *  @brief  Gets the font data
 *
 *  @return u8*    pointer to the font data
 */
const u8* mae_GetFontData(void);

/**
 *  mae_LoadFontDataToMem
 *  @brief  Load the font data to Mem
 *
 @return MAE_RETURN_SUCCESS if Load successfully
 *          MAE_RETURN_FAILED  if Load unsuccessfully
 */
MAE_Ret MAE_LoadFontDataToMem(void);

/**
*  MAE_CusFreeFontData
*  @brief  Free the Font data loaded.
*
*  @param  [in ]pData	The data
*
*  @return none.
*/
void MAE_CusFreeFontData(void);

/**
 *  mae_GetKMXFontData
 *  @brief  Gets the KMXFont data
 *
 *  @return u8*    pointer to the KMXFont data
 */
const u8* MAE_GetKMXFontData(void);

/**
 *  mae_GetFontDataArray
 *  @brief  Gets the fornt data
 *
 *  @param  [in ]u32FontCat			Font category
 *  @param  [out]ppArrayData		pointer to font array data
 *  @param  [out]pu32ArrayFontSize  pointer to size of the font
 *  @param  [out]pu16ArraySize		pointer to total num of font array
 *  @param  [out]u16Size			pointer to max. size of the font array
 *
 *  @return MAE_RETURN_SUCCESS if gets successfully
 *          MAE_RETURN_FAILED  if gets unsuccessfully
 */
MAE_Ret mae_GetFontDataArray(u32 u32FontCat, const u8 **ppArrayData, u32 *pu32ArrayFontSize, u16 *pu16ArraySize, u16 u16Size);

/**
*  mae_GetDefaultInputIME
*  @brief  Gets the Default input ime
*
*  @param  [out]pIMECode      ime code
*  @return MAE_RETURN_SUCCESS if get successfully
*          MAE_RETURN_FAILED  if get unsuccessfully
*/
MAE_Ret mae_GetDefaultInputIME(MAE_InputIME_e *pIMECode);


/**
*  mae_GetDefaultInputLanguage
*  @brief  Gets the Default input language
*
*  @param  [out]nLangCode      language code
*  @return MAE_RETURN_SUCCESS if get successfully
*          MAE_RETURN_FAILED  if get unsuccessfully
*/
MAE_Ret mae_GetDefaultInputLanguage(MAE_LANG_CODE_e *pLangCode);

/**
*  mae_GetDefaultInputLanguageByIME
*  @brief  Gets the Default input language
*
*  @param  [in ]pIMECode      ime code
*  @param  [out]nLangCode      language code
*  @return MAE_RETURN_SUCCESS if get successfully
*          MAE_RETURN_FAILED  if get unsuccessfully
*/
MAE_Ret mae_GetDefaultInputLanguageByIME(MAE_InputIME_e IMECode,MAE_LANG_CODE_e *pLangCode);

/**
*  mae_GetInputLanguageNum
*  @brief  Gets the Input language number
*
*  @return u8 the the language number
*/
u16 mae_GetInputLanguageNum(void);

/**
*  mae_GetInputLanguageNumByIME
*  @brief  Gets the Input language number
*
*  @param  [in ]pIMECode      ime code
*  @return u8 the the language number
*/
u16 mae_GetInputLanguageNumByIME(MAE_InputIME_e IMECode);


/**
*  mae_GetInputLanguageNameByIME
*  @brief  Gets the input language name
*
*  @param  [in ]pIMECode		ime code
*  @param  [in ]pLangCode		language code
*  @param  [out]ppLangName		pointer to the retrieved language name
*  @param  [out]pLangNameLen    pointer to the retrieved language length
*
*  @return MAE_RETURN_SUCCESS if gets language name successfully
*          MAE_RETURN_FAILED  if gets language name unsuccessfully
*/
MAE_Ret mae_GetInputLanguageNameByIME(MAE_InputIME_e IMECode, MAE_LANG_CODE_e langCode, u16 **ppLangName, u16 *pLangNameLen);

/**
*  mae_GetAllInputLanguageData
*  @brief  Gets All Input language data
*
*  @param  [out]pLangData       the MAE_InputLangData_t array
*  @param  [in ]pSize           the MAE_InputLangData_t array size
*
*  @return MAE_RETURN_SUCCESS if gets language data successfully
*          MAE_RETURN_FAILED  if gets language data unsuccessfully
*/
MAE_Ret mae_GetAllInputLanguageData(MAE_InputLangData_t *pLangData, u16 nSize);

/**
*  mae_GetAllInputLanguageDataByIME
*  @brief  Gets All Input language data
*
*  @param  [in ]pIMECode       ime code
*  @param  [out]pLangData      the MAE_InputLangData_t array
*  @param  [in ]pSize          the MAE_InputLangData_t array size
*
*  @return MAE_RETURN_SUCCESS if gets language data successfully
*          MAE_RETURN_FAILED  if gets language data unsuccessfully
*/
MAE_Ret mae_GetAllInputLanguageDataByIME(MAE_InputIME_e IMECode,MAE_InputLangData_t *pLangData, u16 nSize);


/**
*  mae_GetInputDataByIME
*  @brief  Gets Input data by default lang
*
*  @param  [in ]pIMECode        ime code
*  @param  [out]ppArrayData     pointer to the input data
*  @param  [out]pArrayDataSize  pointer to the input size
*  @param  [in ]nSize			the input data array size
*
*  @return MAE_RETURN_SUCCESS if gets array data successfully
*          MAE_RETURN_FAILED  if gets array data unsuccessfully
*/
MAE_Ret mae_GetInputDataByIME(MAE_InputIME_e IMECode, u8 **ppArrayData, u32 *pArrayDataSize, u16 nSize);

/**
*  mae_GetInputDataByLang
*  @brief  Gets All Input array data by eLangCode
*
*  @param  [in ]eLangCode		eLangCode
*  @param  [out]ppArrayData     pointer to the input data
*  @param  [out]pArrayDataSize  pointer to the input size
*  @param  [in ]nSize			the input data array size
*
*  @return MAE_RETURN_SUCCESS if gets array data successfully
*          MAE_RETURN_FAILED  if gets array data unsuccessfully
*/
MAE_Ret mae_GetInputDataByLang(MAE_LANG_CODE_e LangCode,u8 **ppArrayData, u32 *pArrayDataSize, u16 nSize);

/**
*  MAE_FreeInputDataByLang
*  @brief  Free the input data.
*
*  @param  [in ]pMem	Pointer to the memory to be freed.
*
*  @return none.
*/
void MAE_FreeInputDataByLang(void *pMem);

/**
*  mae_GetInputDataByLangByIME
*  @brief  Gets All Input array data by eLangCode
*
*  @param  [in ]pIMECode			ime code
*  @param  [in ]eLangCode			eLangCode
*  @param  [out]ppArrayData			pointer to the input data
*  @param  [out]pArrayDataSize      pointer to the input size
*  @param  [in ]nSize				the input data array size
*
*  @return MAE_RETURN_SUCCESS if gets array data successfully
*          MAE_RETURN_FAILED  if gets array data unsuccessfully
*/
MAE_Ret mae_GetInputDataByLangByIME(MAE_InputIME_e IMECode,MAE_LANG_CODE_e LangCode,u8 **ppArrayData, u32 *pArrayDataSize, u16 nSize);


/**
*  mae_GetHandWriteNum
*  @brief  Gets the HandWrite number
*
*  @param  [out]pHWNum			HandWrite num
*  @return MAE_RETURN_SUCCESS	successfully
*          MAE_RETURN_FAILED	failed.
*/
MAE_Ret mae_GetHandWriteNum(u8 *pHWNum);

/**
*  mae_GetHandWriteData
*  @brief  Gets HandWrite data
*
*  @param  [out]ppArrayData				pointer to the HandWrite data
*  @param  [out]pArrayDataSize			pointer to the HandWrite size
*  @param  [in ]nSize					the HandWrite data array size
*
*  @return MAE_RETURN_SUCCESS		Get data successfully.
*          MAE_RETURN_FAILED		failed.
*/
MAE_Ret mae_GetHandWriteData(u8 **ppArrayData, u32 *pArrayDataSize, u16 nSize);

/**
*  MAE_LoadHandWriteData
*  @brief  Load default HandWrite data to ram
*
*  @param  [out]ppHWData		pointer to HandWrite data
*
*  @return MAE_RETURN_SUCCESS	Load default HandWrite data successfully.
*          MAE_RETURN_FAILED	failed.
*/
MAE_Ret MAE_LoadHandWriteData(u8 **ppHWData);

/**
*  MAE_FreeHandWriteData
*  @brief  free HandWrite data
*
*  @param  [in ]pHWRData		pointer to HandWrite data
*
*  @return MAE_RETURN_SUCCESS	Free HandWrite data successfully.
*          MAE_RETURN_FAILED	failed.
*/
MAE_Ret MAE_FreeHandWriteData(u8 *pHWRData);

/**
*  mae_GetHandWriteData
*  @brief  Gets HandWrite data
*
*  @param  [in ]pHWCode					HandWrite code
*  @param  [out]ppArrayData				pointer to the HandWrite data
*  @param  [out]pArrayDataSize			pointer to the HandWrite size
*  @param  [in ]nSize					the HandWrite data array size
*
*  @return MAE_RETURN_SUCCESS			Get HandWrite data successfully.
*          MAE_RETURN_FAILED			failed.
*/
MAE_Ret mae_GetHandWriteDataByHW(MAE_Handwrite_e HWCode ,u8 **ppArrayData, u32 *pArrayDataSize, u16 nSize);

/**
*  mae_GetActiveNumInstallMelody
*  @brief  Get real existing number of the predefine melody
*
*  @return The number of the predefine melody
*/
u32 mae_GetActiveNumInstallMelody(void);


/**
*  mae_GetActiveNumInstallImage
*  @brief  Get real existing number of the predefine image
*
*  @return The number of the predefine image
*/
u32 mae_GetActiveNumInstallImage(void);

/**
*  mae_GetPreDefinedMediaInfo
*  @brief  Get the predefined media information.
*
*  @param  [in ]nIndex				The index of the media.
*  @param  [out]pMediaInfo			pointer to the image info.
*  @param  [in ]nFormatType         The format of the media
*
*  @return MAE_RETURN_SUCCESS		Get the media information successfully.
*          MAE_RETURN_FAILED		failed.
*/
MAE_Ret mae_GetPreDefinedMediaInfo(u32 nIndex, CusMediaInfo_t* pMediaInfo, CUS_FORMAT_TYPE_e nFormatType);


/**
*  mae_GetPreDefinedImgId
*  @brief  Get the predefined image ID.
*
*  @param  [in ]nIndex				The index of the image.
*  @param  [out]pImageId			pointer to the image ID.
*
*  @return MAE_RETURN_SUCCESS		Get the ID successfully.
*          MAE_RETURN_FAILED		failed.
*/
MAE_Ret mae_GetPreDefinedImgId(u32 nIndex, u32 *pImageId);


/**
*  mae_GetPreDefinedMelodyId
*  @brief  Get the predefined melody ID.
*
*  @param  [in ]nIndex				The index of the image.
*  @param  [out]pMediaId			pointer to the melody ID.
*
*  @return MAE_RETURN_SUCCESS	Get the ID successfully.
*          MAE_RETURN_FAILED	failed.
*/
MAE_Ret mae_GetPreDefinedMelodyId(u32 nIndex, u32 *pMediaId);

/**
*  mae_IsSupportSmartInput
*  @brief  Check whether the language support smart input
*
*  @param  [in ]nLangCode			 Language code
*
*  @return TRUE Supports smart input.
*          FALSE  Don't support smart input.
*/
boolean mae_IsSupportSmartInput(MAE_LANG_CODE_e nLangCode);

/**
*  mae_LoadApRs
*  @brief  Load AP resource
*
*  @param  [in ]nAPResId		The AP resource ID.
*
*  @return MAE_RETURN_SUCCESS	Load AP resource successfully.
*          MAE_RETURN_FAILED	failed.
*/
MAE_Ret mae_LoadApRs(u16 nAPResId);

/**
*  mae_FreeApRs
*  @brief  Free AP resource
*
*  @param  [in ]nAPResId		The AP resource ID.
*
*  @return none.
*/
void mae_FreeApRs(u16 nAPResId);

/**
*  MAE_GetInputLanguageCode
*  @brief  Get input language code from language pack.
*
*  @param  [in ]nIndex			The index.
*  @param  [out]nLangCode		pointer to the language code.
*
*  @return MAE_RETURN_SUCCESS	Get input language code successfully.
*          MAE_RETURN_FAILED	failed.
*/
MAE_Ret MAE_GetInputLanguageCode(u8 nIndex, u8 *nLangCode);

/**
*  MAE_GetInputLanguageName
*  @brief  Get input language name from language pack.
*
*  @param  [in ]nIndex			The index.
*  @param  [out]ppLangName		pointer to language name.
*  @param  [out]nLangLen		pointer to length of language name.
*
*  @return MAE_RETURN_SUCCESS	Get input language name successfully.
*          MAE_RETURN_FAILED	failed.
*/
MAE_Ret MAE_GetInputLanguageName(u8 nIndex, u16 **ppLangName, u16 *nLangLen);


/**
*  MAE_CusFreeDynamicMediaData
*  @brief  Free dynamic load media data.
*
*  @param  [in ]nMediaID		The media ID.
*  @param  [in ]nFormatType		The format of the media.
*  @param  [in ]nLangLen		pointer to pTheme.
*
*  @return none.
*/
void MAE_CusFreeDynamicMediaData(u32 nMediaID, CUS_FORMAT_TYPE_e nFormatType, ThmHead_t *pTheme);

#endif /*__MAE_RESOURCE_H__*/

