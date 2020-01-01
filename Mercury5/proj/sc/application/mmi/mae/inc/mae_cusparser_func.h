#ifndef __MAE_CUSPARSER_FUNC_H__
#define __MAE_CUSPARSER_FUNC_H__

#ifdef __MMI_CUSVERIFIER_SUPPORT__

#include "mmi_mae_customization_forward.h"

extern u8 *g_pCusParserPointer;
extern u32 g_nCusParserTotalCusSize;

void MAE_SetCusInitData(u8 *pPointer, u32 nTotalCusSize);

void MAECusSetWholePackageSize(u32 nSize);
u32 MAECusGetWholePackageSize(void);


/**
*  MAECusGetTotalThemeNum
*  @brief  Get total number of Internal theme.
*
**  @return Total number of Internal theme.
*/
u16 MAECusGetTotalThemeNum(void);

/**
*  MAECusGetApAmount
*  @brief  Get Ap amount by Theme.
*
*  @param  [in ]u16Theme        The Theme ID.
*
**  @return Total number of AP by theme.
*/
u32 MAECusGetApAmount(void);

/**
 *  MAECusGetMaxMediaID
 *  @brief  Gets the max media ID
 *
 *  @param  [in ]u16ApId		The Ap ID.
 *  @param  [in ]nCusFormat		The Ap cus format.
 *
 *  @return the max media ID
 */
u32 MAECusGetMaxMediaID(u16 nAPId, CUS_FORMAT_TYPE_e nFormatType);

/**
 *  MAECusGetAPFormatSize
 *  @brief  Gets the Ap's cus data size
 *
 *  @param  [in ]u16ApId		The Ap ID.
 *  @param  [in ]pTheme		Pointer to the theme head.
 *  @param  [in ]nCusFormat		The Ap cus format.
 *
 *  @return the Ap's cus size
 */
u32 MAECusGetAPFormatSize(u16 u16ApId, u8 nCusFormat);
u32 MAECusGetAPStringDeCompressedSize(u16 u16ApId);


/**
 *  MAECusSetCurrentThemeByThemeIndex
 *  @brief  Change Current Theme by Theme index
 *
 *  @param  [in ]u16Theme		The Theme id.
 *
 *  @return none
 */
void MAECusSetCurrentThemeByThemeIndex(u16 u16Theme);

/**
 *  MAECusGetNTTextLabelNum
 *  @brief  Gets the number of no translated text label for the given AP idx
 *
 *  @param  [in ]nAPId      AP id
 *  @return u16				The number of text label
 */
u8 MAECusGetNTTextLabelNum(u16 nAPId);

/**
 *  MAECusGetBootDataSize
 *  @brief  Gets the Boot data size
 *
 *  @return the Boot data size
 */
u32 MAECusGetBootDataSize(void);

/**
 *  MAECusGetPlmnDataSize
 *  @brief  Gets the Plmn data size
 *
 *  @return the Plmn data size
 */
u32 MAECusGetPlmnDataSize(void);
u32 MAECusGetPlmnDeCompressedSize(void);
void MAECusSetPlmnDeCompressedSize(u32 nPlmnSize);

/**
 *  MAECusGetFontDataSize
 *  @brief  Gets the Font data size
 *
 *  @return the Font data size
 */
u32 MAECusGetFontDataSize(void);
u32 MAECusGetFontDecompressedDataSize(void);

/**
 *  MAECusGetHandWriteDataSize
 *  @brief  Gets the HandWrite data size
 *
 *  @return the HandWrite data size
 */
u32 MAECusGetHandWriteDataSize(void);
u32 MAECusGetHandWriteDeCompressedSize(void);
void MAECusSetHandWriteDeCompressedSize(u32 nHandWriteSize);

/**
 *  MAECusGetIMEDataSize
 *  @brief  Gets the IME data size
 *
 *  @return the IME data size
 */
u32 MAECusGetIMEDataSize(void);
u32 MAECusGetIMEDeCompressedSize(void);
void MAECusSetIMEDeCompressedSize(u32 nIMESize);


/**
 *  MAECusGetImgListDataSize
 *  @brief  Gets the System ImageList data size
 *
 *  @return the System ImageList data size
 */
u32 MAECusGetSysImgListDataSize(void);

/**
 *  MAECusGetMelodyListDataSize
 *  @brief  Gets the System MelodyList data size
 *
 *  @return the System MelodyList data size
 */
u32 MAECusGetSysMelodyListDataSize(void);

/**
 *  MAECusGetTxtListDataSize
 *  @brief  Gets the System TxtList data size
 *
 *  @return the System TxtList data size
 */
u32 MAECusGetSysTxtListDataSize(void);
u32 MAECusGetSysTxtListDecompressDataSize(void);

/**
 *  MAECusGetAppendDataSize
 *  @brief  Gets the Append data size
 *
 *  @return the Append data size
 */
u32 MAECusGetAppendDataSize(void);

/**
 *  MAECusGetThirdDataSize
 *  @brief  Gets the Third data size
 *
 *  @return the Third data size
 */
u32 MAECusGetThirdDataSize(void);

/**
 *  MAECusGetKMXFontDataSize
 *  @brief  Gets the KMXFont data size
 *
 *  @return the KMXFont data size
 */
u32 MAECusGetKMXFontDataSize(void);
u32 MAECusGetKMXFontDataDeCompressedSize(void);

/**
 *  MAECusSetDefaultLangCode
 *  @brief  Set the defautl language code
 *
 *  @param  [in ]nLangcode		Set nLangCode
 *
 *  @return MAE_RETURN_SUCCESS   Set successfully.
 *          MAE_RETURN_FAILED    Set failed.
 */
MAE_Ret MAECusSetDefaultLangCode(u8 nLangcode);


// mae_resource.c 

/**
*  MAECusGetTotalThemeNum
*  @brief  Get total number of Internal theme.
*
**  @return Total number of Internal theme.
*/
u16 MAE_GetTotalThemeNum(void);

/**
*  MAE_GetApAmount
*  @brief  Get Ap amount by Theme.
*
*  @param  [in ]u16Theme        The Theme ID.
*
**  @return Total number of AP by theme.
*/
u32 MAE_GetApAmount(void);

/**
 *  MAECusGetMaxMediaID
 *  @brief  Gets the max media ID
 *
 *  @param  [in ]u16ApId		The Ap ID.
 *  @param  [in ]nCusFormat		The Ap cus format.
 *
 *  @return the max media ID
 */
u32 MAE_GetMaxMediaID(u16 nAPId, CUS_FORMAT_TYPE_e nFormatType);

/**
 *  MAE_GetAPFormatSize
 *  @brief  Gets the Ap's cus data size
 *
 *  @param  [in ]u16ApId		The Ap ID.
 *  @param  [in ]pTheme		Pointer to the theme head.
 *  @param  [in ]nCusFormat		The Ap cus format.
 *
 *  @return the Ap's cus size
 */
u32 MAE_GetAPFormatSize(u16 u16ApId, u8 nCusFormat);
u32 MAE_GetAPStringDecompressedSize(u16 u16ApId);

/**
 *  MAE_SetCurrentThemeByThemeIndex
 *  @brief  Change Current Theme by Theme index
 *
 *  @param  [in ]u16Theme		The Theme id.
 *
 *  @return none
 */
void MAE_SetCurrentThemeByThemeIndex(u16 u16Theme);

/**
 *  mae_GetNTTextLabelNum
 *  @brief  Gets the number of no tranlated text label for the given AP id
 *
 *  @param  [in ]nAPId      AP id
 *  @return u16				The number of text label
 */
u8 mae_GetNTTextLabelNum(u16 nAPId);

/**
 *  mae_GetFontData
 *  @brief  Gets the Boot data size
 *
 *  @return the Boot data size
 */
u32 MAE_GetBootDataSize(void);

/**
 *  mae_GetFontData
 *  @brief  Gets the Plmn data size
 *
 *  @return the Plmn data size
 */
u32 MAE_GetPlmnDataSize(void);
u32 MAE_GetPlmnDataDeCompressedSize(void);


/**
 *  mae_GetFontData
 *  @brief  Gets the font data size
 *
 *  @return the font data size
 */
u32 MAE_GetFontDataSize(void);
u32 MAE_GetFontDataDecompressedSize(void);

/**
 *  mae_GetFontData
 *  @brief  Gets the HandWrite data size
 *
 *  @return the HandWrite data size
 */
u32 MAE_GetHandWriteDataSize(void);
u32 MAE_GetHandWriteDataDeCompressedSize(void);


/**
 *  mae_GetFontData
 *  @brief  Gets the IME data size
 *
 *  @return the IME data size
 */
u32 MAE_GetIMEDataSize(void);
u32 MAE_GetIMEDataDeCompressedSize(void);


/**
 *  mae_GetFontData
 *  @brief  Gets the System ImageList data size
 *
 *  @return the ImageList data size
 */
u32 MAE_GetSysImgListDataSize(void);

/**
 *  mae_GetFontData
 *  @brief  Gets the System MelodyList data size
 *
 *  @return the MelodyList data size
 */
u32 MAE_GetSysMelodyListDataSize(void);

/**
 *  mae_GetFontData
 *  @brief  Gets the System TextList data size
 *
 *  @return the TextList data size
 */
u32 MAE_GetSysTxtListDataSize(void);
u32 MAE_GetSysTxtListDataDecompressSize(void);

/**
 *  mae_GetFontData
 *  @brief  Gets the Append data size
 *
 *  @return the Append data size
 */
u32 MAE_GetAppendDataSize(void);

/**
 *  mae_GetFontData
 *  @brief  Gets the Third data size
 *
 *  @return the Third data size
 */
u32 MAE_GetThirdDataSize(void);

/**
 *  MAE_GetKMXFontSize
 *  @brief  Gets the KMXFont data size
 *
 *  @return the KMXfont data size
 */
u32 MAE_GetKMXFontDataSize(void);
u32 MAE_GetKMXFontDataDeCompressedSize(void);


/**
 *  MAE_CusReplaceImage
 *  @brief  Gets the Ap's cus data size
 *
 *  @param  [in ]nImageID		The image will be replaced.
 *  @param  [in ]pNewRawData    Pointer to the new image raw data.
 *  @param  [in ]nNewSize		New image's size.
 *
 *  @return MAE_RETURN_SUCCESS   replace successfully.
 *          MAE_RETURN_FAILED    replace failed.
 */
MAE_Ret MAE_ReplaceImage(u32 nImageID, u8 *pNewRawData, u32 nNewSize);

/**
 *  MAE_SetDefaultLangCode
 *  @brief  Gets the Ap's cus data size
 *
 *  @param  [in ]nLangCode		Set nLangCode
 *
 *  @return MAE_RETURN_SUCCESS   Set successfully.
 *          MAE_RETURN_FAILED    Set failed.
 */
MAE_Ret MAE_SetDefaultLangCode(u8 nLangCode);


u32 MAECusGetLangDecompressSize(CusTextLabel_t *TxtList, u16 nLangIndex);
static MAE_Ret _MAECusInitLanguage(CusTextLabel_t **ppTextLabel, u8* pPointer, u32 nSize, u8 nLangType, u32 *pDeCompSize);
u32 MAE_CusGetWholePackageSize(void);


#endif  //__MMI_CUSVERIFIER_SUPPORT__

#endif  //__MAE_CUSPARSER_FUNC_H__


