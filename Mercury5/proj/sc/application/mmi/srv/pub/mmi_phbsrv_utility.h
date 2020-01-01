
/**
 * @file    mmi_phb_utility.h
 * @brief   The file is contain some utilities for PHB_SRV.
 * @author  ryb.chen@mstarsemi.com
 * 
 * @version $Id: mmi_phb_utility.h 39925 2009-09-10 14:17:52Z otto.wu $
 */

#ifndef __MMI_PHB_UTILITY_H__
#define __MMI_PHB_UTILITY_H__

/*
    Include
*/

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_phbsrv_def.h"

/*
    Constant
*/

enum
{
    MMI_PHB_UTIL_UCS2_CODING_0 = 0x80
   ,MMI_PHB_UTIL_UCS2_CODING_1 = 0x81
   ,MMI_PHB_UTIL_UCS2_CODING_2 = 0x82
};

#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__

/*
    For vCard START.
*/
#define MMI_PHB_VCARD_END_STRING "END:VCARD"
#define MMI_PHB_VCARD_TAG_PHOTO "PHOTO"
#define MMI_PHB_VCARD_TAG_SEPARATOR ':'
#define MMI_PHB_TEXT_LINE_END_STRING "\r\n"

enum
{
    MAX_VCARDVCAL_TAG_LEN = 152
   ,MAX_VCARDVCAL_BUFFER_SIZE = 4096
};

typedef enum
{
    MMI_PHB_VCARD_REQ_RSLT_UNKNOWN = 0
   ,MMI_PHB_VCARD_REQ_RSLT_OK
   ,MMI_PHB_VCARD_REQ_RSLT_INVALID_ID
   ,MMI_PHB_VCARD_REQ_RSLT_INVALID_PARAM
   ,MMI_PHB_VCARD_REQ_RSLT_FULL
   ,MMI_PHB_VCARD_REQ_RSLT_BUFFER_TOO_SMALL
   ,MMI_PHB_VCARD_REQ_RSLT_INVALID_VCARDCAL
} MMI_PHB_VCARD_REQ_RSLT_E;

typedef enum
{
    MMI_PHB_VCARD_CHARSET_ASCII = 0
   ,MMI_PHB_VCARD_CHARSET_UTF8
   ,MMI_PHB_VCARD_CHARSET_UCS2
   ,MMI_PHB_VCARD_CHARSET_BIG5
   ,MMI_PHB_VCARD_CHARSET_GB2312
} MMI_PHB_VCARD_CHARSET_TYPE_E;

typedef enum
{
    MMI_PHB_PC_VCARD_ENCODING = 0
   ,MMI_PHB_PC_VCAL_ENCODING
   ,MMI_PHB_HS_VCARD_ENCODING
   ,MMI_PHB_HS_VCAL_ENCODING
   ,MMI_PHB_HS_QP_UTF8
   ,MMI_PHB_ENCODING_UNKNOWN
   ,MMI_PHB_ENCODING_QP
   ,MMI_PHB_ENCODING_BASE64
} MMI_PHB_VCARD_ENCODING_TYPE_E;

/*
    For vCard END.
*/

#ifdef __MMI_PHB_IMPORT_EXPORT_MULTI_FORMAT__

/*
    For CSV START
*/

#define MMI_PHB_CSV_SEPARATOR L','
#define MMI_PHB_CSV_SEPARATOR_SPACE L' '
#define MMI_PHB_CSV_DOUBLE_QUOTE L'"'
#define MMI_PHB_CSV_TAB_CHAR L'\t' //The tab is used to make excel to treat a column as normal text.

#define MMI_PHB_CSV_SEPARATOR_SIZE 1
#define MMI_PHB_CSV_DOUBLE_QUOTE_SIZE 2
#define MMI_PHB_CSV_NUMBER_TYPE_SIZE 1
#define MMI_PHB_CSV_NUMBER_TYPE_STR_SIZE 5

#define MMI_PHB_CSV_UNICODE_CAPITAL_A         65
#define MMI_PHB_CSV_UNICODE_CAPITAL_Z         90
#define MMI_PHB_CSV_UNICODE_LOWERCASE_A       97
#define MMI_PHB_CSV_UNICODE_LOWERCASE_Z      122

typedef enum
{
	MMI_PHB_CSV_RSLT_OK = MMI_PHB_VCARD_REQ_RSLT_OK,
	MMI_PHB_CSV_RSLT_INVALID_PARAM = MMI_PHB_VCARD_REQ_RSLT_INVALID_PARAM,
	MMI_PHB_CSV_RSLT_OUT_OF_MEM = MMI_PHB_VCARD_REQ_RSLT_FULL,
	MMI_PHB_CSV_RSLT_INVALID_FILE_FORMAT = MMI_PHB_VCARD_REQ_RSLT_INVALID_VCARDCAL,
	MMI_PHB_CSV_RSLT_BUFFER_NOT_ENOUGH = MMI_PHB_VCARD_REQ_RSLT_BUFFER_TOO_SMALL,
} MMI_PHB_CSV_RSLT_E;

typedef enum
{
    MMI_PHB_CSV_STR_TRANS_TYPE_NONE =0,
    MMI_PHB_CSV_STR_TRANS_TYPE_SIM_TEXT,
    MMI_PHB_CSV_STR_TRANS_TYPE_PHONE_NUM
} MMI_PHB_CSV_STR_TRANS_TYPE_E;

/*
    For CSV END
*/
#endif

#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
/*
    Function
*/

/*
    Check the input string is chinese or not, TBD.
*/

static boolean MMI_PHB_UTIL_Is_Chinese_Str(const u8 *pu8Str, u8  u8StrLen, u8 *pu8FirstStr);

/*
    Convert SMS 7 bit string to the UCS2 string, TBD.
*/

MmiPhbReturn_e MMI_PHB_UTIL_Convert7bitStrToUcs2Str(const u8 *pu8InputStr, const u8   u8InputStrLen, u8 *pu8OutputStr, u8 *pu8OutputStrLen);


/*
    Convert SIM alpha fields (GSM, 0x80, 0x81 or 0x82) to lower case.
    Please refer to GSM 11.11 Annex B (normative): Coding of Alpha fields in the SIM for UCS2.
*/

MmiPhbReturn_e MMI_PHB_UTIL_ConvertSIMAlphaToLowerCase(const u8 *pu8InputStr, const u8    u8InputStrLen, u8 *pu8OutputStr);

/*
    Convert UCS2 string to lower case.
*/

MmiPhbReturn_e MMI_PHB_UTIL_ConvertUcs2StrToLowerCase(const u8 *pu8InputStr, const u8     u8InputStrLen, u8 *pu8OutputStr);              


/*
    Get length of UCS2 string.
*/

u8 MMI_PHB_UTIL_GetUcs2StrLen(const u8 *pu8Str, const u8    u8MaxLen);


/*
    Get length of SIM alpha fields (GSM, 0x80, 0x81 or 0x82).
*/

u8 MMI_PHB_UTIL_GetSIMAlphaLen(const u8 *pu8Str, const u8   u8MaxLen);


u8 MMI_PHB_UTIL_GetASCIIStrLen(const u8 *pu8Str, const u8   u8MaxLen);

/*
    Get eNumberCompareMax
*/

u8 MMI_PHB_UTIL_GetNumberCompareMax(void);

extern void base64_decode(u8 *dest, u8 *src, u16 srcLen, u16 maxDestSize, u16 *destLen);

#ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__
/*
    For vCard START.
*/

/* 
Return the pointer to the first occurrence of char u8Char in string pu8StrBuf. 
If not found before the end of the string or first \n is encountered, return NULL 
*/
u8* MMI_PHB_UTIL_CheckFirstLineForChar(u8 *pu8StrBuf, u8 u8Char);

extern void MMI_PHB_UTIL_ParseVCalendarString(u8 *destStr, u8 *srcStr, u16 srcStrLen, u16 maxDestStr, u16 *destStrLen, MMI_PHB_VCARD_CHARSET_TYPE_E nVCalCharSet, MMI_PHB_VCARD_ENCODING_TYPE_E nVCalEncoding, u8 needEncodeWithSIMCoding);

extern u8 MMI_PHB_UTIL_GetVCalTagCtntPosn(u8 *u8VCalBuffer, u16 u16BufferLen, u8 *u8Tag, u16 u16TagLen, u16 *u16TagInfoStartPosn, u16 *u16TagInfoLen, u16 *u16CtntStartPosn, u16 *u16CtntLen, MMI_PHB_VCARD_CHARSET_TYPE_E *nCharSet, MMI_PHB_VCARD_ENCODING_TYPE_E *nEncoding);

extern u8 MMI_PHB_UTIL_SearchTagInfo(u8 *u8TagInfo, u16 u16TagInfoLen, u8 *u8SearchStr, u16 u16SearchStrLen);

extern MMI_PHB_VCARD_REQ_RSLT_E MMI_PHB_UTIL_VCardCalTxtCtntEncode(u8 *au8EncodeStr, u16 *u16EncodeStrLen, u16 u16MaxEncodeStrLen, u8 *au8EncodeCtnt, u16 u16EncodeCtntLen, u8 *au8EncodeTag, u16 u16EncodeTagLen, MMI_PHB_VCARD_ENCODING_TYPE_E nNonAsciiEncoding);

extern void MMI_PHB_UTIL_VCardCalTxtCtntDecode(u8 *au8DecodeStr, u16 *u16DecodeStrLen, u16 u16MaxDecodeStrLen, u8 *au8VCardCal, u16 u16CardCalLen, u8 *au8CardCalTag, u16 u16CardCalTagLen, u8 needEncodeWithSIMCoding);

u32 MMI_PHB_UTIL_RemoveLeadingWChar(u16 *u16Str, u32 pu32StrLen, u16 u16Char);
u32 MMI_PHB_UTIL_RemoveLeadingWhiteSpace(u8 *u8ParseBuffer, u32 pu32BufSize);
u32 MMI_PHB_UTIL_CSVGetContactString(u8 *u8ParseBuffer, u32 pu32BufSize, u8 bIsUCS2);
u32 MMI_PHB_UTIL_VCardGetContactString(u8 *u8ParseBuffer, u32 *u32BufSize);

extern void base64_encode(u8 *dest, u8 *src, u16 srcLen, u16 maxDestSize, u16 *destLen);

MMI_PHB_VCARD_REQ_RSLT_E MMI_PHB_UTIL_VCardEncode(u8 *au8VCardBuffer, u16 *u16VCardLen, u16                                u16MaxVCardBuffer, MmiPhbContactContent_t           sPbRecCtnt, MMI_PHB_VCARD_ENCODING_TYPE_E   nNonAsciiEncoding);

MMI_PHB_VCARD_REQ_RSLT_E MMI_PHB_UTIL_VCardDecode(MmiPhbContactContent_t *sPbRecCtnt, u8 *au8VCardBuffer, u16                      u16VCardLen);

/*
    For vCard END.
*/

#ifdef __MMI_PHB_IMPORT_EXPORT_MULTI_FORMAT__

/*
    For CSV START.
*/
MMI_PHB_CSV_RSLT_E MMI_PHB_UTIL_CSVEncode (MAE_WChar *paWCharCSVBuffer, 
                                           u16 *pu16CsvLen, 
                                           u16 u16MaxCSVBuffer, 
                                           MmiPhbContactContent_t *ptEncodeContact);

MMI_PHB_CSV_RSLT_E MMI_PHB_UTIL_CSVDecode ( MAE_WChar *paWCharStringBuffer, 
                                            u16 u16StringLen,
                                            MmiPhbContactContent_t *ptDecodeContact);

boolean MMI_PHB_UTIL_CheckNeedNextLine(MAE_WChar    *pWCharBuf);

void MMI_PHB_UTIL_GetCSVType( u8 *pu8Str, u16 u16Size, u8 *u8TypeOut, u8 bIsUCS2);

/*
    For CSV END.
*/
#endif

#endif // #ifndef __MMI_PHB_DISABLE_IMPORT_EXPORT__

void MMI_PHB_UTIL_GetItemFromCfgSrv(void *pThis);

__SLDPM_FREE__ boolean MMI_PHB_UTIL_IsNumberEqual(const u8 *pu8NumStr1, u8 u8NumLen1, const u8 *pu8NumStr2, u8 u8NumLen2);

#endif /* __MMI_PHB_UTILITY_H__ */

