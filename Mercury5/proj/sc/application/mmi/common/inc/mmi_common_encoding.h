/**
 * @file    mmi_common_encoding.h
 * @brief   
 *          
 *
 * @author  
 * @version $Id: mmi_common_encoding.h 19675 2008-12-31 09:28:17Z otto.wu $
 */
 
#ifndef __MMI_COMMON_ENCODING_H__
#define __MMI_COMMON_ENCODING_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_langcode.h"

typedef enum
{
  Common_Encoding_StringType_UCS2 = 0,
  Common_Encoding_StringType_GB,  
  Common_Encoding_StringType_BIG5, 
  Common_Encoding_StringType_ASCII,
  Common_Encoding_StringType_UTF8,
#ifndef __SMALL_ROM__
  //8-bit CODEPAGE Begin
  Common_Encoding_StringType_CODEPAGE_BEGIN,
  Common_Encoding_StringType_CODEPAGE_WIN1250 = Common_Encoding_StringType_CODEPAGE_BEGIN,
  Common_Encoding_StringType_CODEPAGE_WIN1251,
  Common_Encoding_StringType_CODEPAGE_WIN1252,
  Common_Encoding_StringType_CODEPAGE_WIN1253,
  Common_Encoding_StringType_CODEPAGE_WIN1254,
  Common_Encoding_StringType_CODEPAGE_WIN1255,
  Common_Encoding_StringType_CODEPAGE_WIN1256,
  Common_Encoding_StringType_CODEPAGE_WIN1257,
  Common_Encoding_StringType_CODEPAGE_WIN1258,
  Common_Encoding_StringType_CODEPAGE_WIN874,
  Common_Encoding_StringType_CODEPAGE_END,
  //8-bit CODEPAGE End
#endif
  Common_Encoding_StringType_END
}Common_Encoding_StringType_e;

/* Code Page Table STRUCT */
typedef struct
{
    const Common_Encoding_StringType_e eEncodeType;
    const u32 uEncodeNameTextID;
} EncodingNameTable_t;

#ifndef __SMALL_ROM__

#define CODEPAGE_UNDEFINE_CONVERT_CODE 0xFFFF

/* Code Page Table STRUCT */
typedef struct
{
    const Common_Encoding_StringType_e eEncodeType;
    const u16* pMmiCodePageTable;
    const boolean bIsHalfAscii; //lower half (0¡V127) of the code page is plain ASCII
} MmiCodePageTable_t;
#endif

enum
{
  COMMON_ENCODING_QP_NORMAL,
  COMMON_ENCODING_QP_ATCMD,
  COMMON_ENCODING_QP_MAX
};
typedef u8 COMMON_ENCODING_QP_e;

#define MMI_COMMON_MAX_UCS2TOUTF8_BYTES 3
#define MMI_COMMON_MAX_UTF8TOQPST_BYTES 3
#define MMI_COMMON_MAX_UCS2TOQPST_BYTES (MMI_COMMON_MAX_UCS2TOUTF8_BYTES * MMI_COMMON_MAX_UTF8TOQPST_BYTES)

/*
@brief Encoding string to Unicode conversion according to the encode id of input encoding string. 
       Note: This function assume the last char of input string is 'end of str'
@param
    pInStr          :   input encoding string
    nInStrByteLen   :   byte length of input encoding string
    pOutStr(output) :   output string of the converted result from encoding string, pOutStr should be memory-allocated by users in advance.
    pOutStrLen(output): output string length
    nMaxOutStrByteLen:  max byte length of output string allocated by users
    eInStrEncode    :   encode id of input encoding string
@return: MAE_RET_SUCCESS/MAE_RET_BAD_PARAM/MAE_RET_NOT_SUPPORTED
*/
MAE_Ret mmi_Common_EncodeStrToUnicodeStr(u8 *pInStr, u32 nInStrByteLen, MAE_WChar *pOutStr, u32* pOutStrLen, u32 nMaxOutStrByteLen,  Common_Encoding_StringType_e eInStrEncode);
/*
@brief Unicode to Encoding string conversion according to the encode id of output encoding string. 
@param
    pInStr          :   input Unicode string
    nInStrByteLen   :   byte length of input Unicode string
    pOutStr(output) :   output string of the converted result from encoding string, pOutStr should be memory-allocated by users in advance.
    pOutStrLen(output): output string length
    nMaxOutStrByteLen:  max byte length of output string allocated by users
    eInStrEncode    :   encode id of output encoding string
@return: MAE_RET_SUCCESS/MAE_RET_BAD_PARAM/MAE_RET_NOT_SUPPORTED
*/
MAE_Ret mmi_Common_UnicodeStrToEncodeStr(MAE_WChar *pInStr, u32 nInStrByteLen, u8 *pOutStr, u32* pOutStrLen, u32 nMaxOutStrByteLen, Common_Encoding_StringType_e eOutStrEncode);

MAE_WChar * mmi_Common_ConvertGBStrToUCS2Str(u8 *pInStr, u32 nInStrByteLen, MAE_WChar *pOutStr, u32 nOutStrByteLen);
MAE_WChar * mmi_Common_ConvertBIG5StrToUCS2Str(u8 *pInStr, u32 nInStrByteLen, MAE_WChar *pOutStr, u32 nOutStrByteLen);
u8 * mmi_Common_ConvertUCS2StrToGBStr(MAE_WChar *pInStr, u32 nInStrByteLen, u8 *pOutStr, u32 nOutStrByteLen);
u8 * mmi_Common_ConvertUCS2StrToBig5Str(MAE_WChar *pInStr, u32 nInStrByteLen, u8 *pOutStr, u32 nOutStrByteLen);
/*****************************************************************************
*!!! NOTICE !!!
* The followings are moved to mae_helper.h, for the purpose that
* MAE can not include any header file in app/srv/mmi_common level.
* This is just a temporary solution! It should be modified in the future!
******************************************************************************/

/**************
* End of NOTICE
**************/
MAE_WChar* mmi_Common_GetPINYINStr(MAE_WChar	*pInStr, 
								   u32			nInStrLen, 
								   MAE_WChar	*pOutBuf, 
								   u32			nOutBufLen, 
								   boolean		bIsNeedInsertOriginalCode, 
								   boolean		bIncompletePINYINinStrIsValid, 
								   u32			*nParsedCharNum, 
								   u32			*nConvertedZHCharNum, 
								   u8			*pOutFirstChPYStrBuf, 
								   u32			nFirstChPYStrMaxLen);

void mmi_Common_QPDecode(u8 *dest, u8 *src, u16 *destLen, u16 srcLen);
void mmi_Common_QPEncode(u8 *dest, u8 *src, u16 *destLen, u16 srcLen, u16 MaxDesLen, COMMON_ENCODING_QP_e nType);

MAE_Ret mmi_Common_UCS2ToUTF8InQPStr(u8 *pQPSTDest, const MAE_WChar *pSrc, u16 *pnDestLen, const u16 nMaxDestBytes, COMMON_ENCODING_QP_e nType);
MAE_Ret mmi_Common_UTF8InQPStrToUCS2(MAE_WChar *pDest, const u8 *pQPSTSrc, u16 *pnDestLen, const u16 nMaxDestBytes);


#ifdef __UNICODE_TO_STROKE__
u16 mmi_Common_ConvertUCS2ToStroke(MAE_WChar wUCS2, u8 *pu8Buffer, u16 u16MaxBufferSize);

u16 mmi_Common_ConvertUCS2StrToStrokeStr(MAE_WChar	*pwInputStr, 
										 u8			*pu8StrokeBuf, 
										 u16		u16StrokeBufMax, 
										 u8			*pu8FirstCharBuf, 
										 u16		u16FirstCharBufMax);

void mmi_Common_ConvertStrokeValueToKey(MAE_WChar *pStrokeValue, u8 *pu8StrokeKey, u32 *pu32StrokeKeyLen);
#endif

/*
@brief Get encoding type according to language
@param
    eLangCode :   language  
@return: encoding type, if not found, Common_Encoding_StringType_UCS2 is returned as default.
*/
Common_Encoding_StringType_e mmi_Common_GetDefaultEncodingTypeByLang(MAE_LANG_CODE_e eLangCode);

/*
@brief Get encoding type name
@param
    eEncodeType:   encoding type
    pTextId   :    store the result of text ID
@return: MAE_RET_SUCCESS/MAE_RET_FAILED/MAE_RET_BAD_PARAM
*/
MAE_Ret mmi_Common_GetEncodingTypeName(u32* pTextId, Common_Encoding_StringType_e eEncodeType);

Common_Encoding_StringType_e* mmi_Common_getAllEncoding(u8* pSize);

#endif /* __MMI_COMMON_ENCODING_H__ */
