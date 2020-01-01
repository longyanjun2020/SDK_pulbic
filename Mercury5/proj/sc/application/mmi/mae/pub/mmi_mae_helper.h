/**
 * @file mmi_mae_helper.h
 *
 * This file includes helper function of MAE
 *
 * @version $Id: mmi_mae_helper.h 1809 2009-09-22 01:26:01Z kenny.wu $
 */

#ifndef __MMI_MAE_HELPER_H__
#define __MMI_MAE_HELPER_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"

/*-------------------------------------------------------------------------*/
/* Helper macro */

/*-------------------------------------------------------------------------*/
/* string helper function */


/******************************  Defines ************************************/

/* BCD Values for Dial Number storage */
#define DIALBCD_0             0x0
#define DIALBCD_1             0x1
#define DIALBCD_2             0x2
#define DIALBCD_3             0x3
#define DIALBCD_4             0x4
#define DIALBCD_5             0x5
#define DIALBCD_6             0x6
#define DIALBCD_7             0x7
#define DIALBCD_8             0x8
#define DIALBCD_9             0x9
#define DIALBCD_STAR          0xA
#define DIALBCD_HASH          0xB
#define DIALBCD_PAUSE         0xC
#define DIALBCD_WILD          0xD
#define DIALBCD_EXPANSION     0xE
#define DIALBCD_FILLER        0xF

#define MAE_PRINT_BUF_SIZE    350
/* BCD format:
       LSB first (1234 = 0x21, 0x43)
	   MSB first (1234 = 0x12, 0x34)
	   unpacked  (1 digit per byte)
*/
typedef enum
{
    BCD_PACKED_LSB_FIRST = 0,
    BCD_PACKED_MSB_FIRST = 1,
    BCD_UNPACKED         = 2,
    BCD_FORMAT           = BCD_PACKED_MSB_FIRST,
    NUM_OF_BCD_FORMAT
} ustr_BcdFormat_e;

/* EXTENDED GSM CODE TO UNICODE STRUCT */
typedef struct
{
	u8  nExtGsmCode;	/* the extended gsm code, for example, the extended code
					   of the gsm code 0x1B0A is 0x0A. */
	u16 nUnicode;	/* the corresponding nUnicode */
} ustr_ExtGsmCode_t;


/* SIM Encode Format */
typedef enum
{
    MMI_SIM_CODING_DEFAULT_ALPHABET = 0,	/*default GSM alphabet*/
    MMI_SIM_CODING_UCS2_FORMAT_1 	= 1,	/*0x80*/
    MMI_SIM_CODING_UCS2_FORMAT_2 	= 2,	/*0x81*/
    MMI_SIM_CODING_UCS2_FORMAT_3 	= 3		/*0x82*/
}mmiSimCodingScheme_e;

typedef enum
{
    MMI_GSM_CODING_7BITS,
	MMI_GSM_CODING_UCS2
}mmiGSMCodingType_e;

#define MMI_GSM_LOCK_SHIFT_NA 0xFFFF
#define MMI_GSM_SINGLE_SHIFT_NA 0xFFFE

typedef enum
{
    MMI_GSM_LOCK_SHIFT_DEFAULT,
	MMI_GSM_LOCK_SHIFT_TURKISH,
	MMI_GSM_LOCK_SHIFT_PORTUGUESE,
	MMI_GSM_LOCK_SHIFT_BENGALI,
	MMI_GSM_LOCK_SHIFT_GUJARATI,
	MMI_GSM_LOCK_SHIFT_HINDI,
	MMI_GSM_LOCK_SHIFT_KANNADA,
	MMI_GSM_LOCK_SHIFT_MALAYALAM,
	MMI_GSM_LOCK_SHIFT_ORIYA,
	MMI_GSM_LOCK_SHIFT_PUNJABI,
	MMI_GSM_LOCK_SHIFT_TAMIL,
	MMI_GSM_LOCK_SHIFT_TELUGU,
	MMI_GSM_LOCK_SHIFT_URDU
}mmiGsmLockShiftTable_e;

typedef enum
{
    MMI_GSM_SINGLE_SHIFT_DEFAULT,
	MMI_GSM_SINGLE_SHIFT_TURKISH,
	MMI_GSM_SINGLE_SHIFT_SPANISH,
	MMI_GSM_SINGLE_SHIFT_PORTUGUESE,
	MMI_GSM_SINGLE_SHIFT_BENGALI,
	MMI_GSM_SINGLE_SHIFT_GUJARATI,
	MMI_GSM_SINGLE_SHIFT_HINDI,
	MMI_GSM_SINGLE_SHIFT_KANNADA,
	MMI_GSM_SINGLE_SHIFT_MALAYALAM,
	MMI_GSM_SINGLE_SHIFT_ORIYA,
	MMI_GSM_SINGLE_SHIFT_PUNJABI,
	MMI_GSM_SINGLE_SHIFT_TAMIL,
	MMI_GSM_SINGLE_SHIFT_TELUGU,
	MMI_GSM_SINGLE_SHIFT_URDU
}mmiGsmSingleShiftTable_e;

typedef struct
{
	mmiGSMCodingType_e eCodingType;
 	mmiGsmLockShiftTable_e eLockShift;
 	mmiGsmSingleShiftTable_e eSingleShift;
} mmiGsmEncodeInf_t;


/******************************  Functions *******************************/

/**
 *  mae_wstrlen
 *  \brief  return nLength of string
 *
 *  \param  pStr                  Pointer to the MAE_WChar
 *  \retval u32                   Length of the pStr
 */
size_t mae_wstrlen(const MAE_WChar* pStr);

/**
 *  mae_wstrcpy
 *  \brief  copy string pSource to string pDest
 *
 *  \param  pDest                  Pointer to the MAE_WChar
 *  \param  pSource                Pointer to the MAE_WChar
 *  \retval MAE_WChar*             Pointer to the pDest
 */
MAE_WChar* mae_wstrcpy(MAE_WChar* pDest, const MAE_WChar* pSource);

/**
 *  mae_wstrncpy
 *  \brief  copy at most n characters of string pSource to string pDest,
 *          pad with '\0's if pSource has fewer than n characters
 *
 *  \param  pDest                  Pointer to the MAE_WChar
 *  \param  pSource                Pointer to the MAE_WChar
 *  \param  nCount                  number of n characters to be copied
 *  \retval MAE_WChar*             Pointer to the pDest
 */
MAE_WChar* mae_wstrncpy(MAE_WChar* pDest, const MAE_WChar* pSource, size_t nCount);

/**
 *  mae_wstrcat
 *  \brief  concatenate string pSource to end of string pDest
 *
 *  \param  pDest                  Pointer to the MAE_WChar
 *  \param  pSource                Pointer to the MAE_WChar
 *  \retval MAE_WChar*             Pointer to the pDest
 */
MAE_WChar* mae_wstrcat(MAE_WChar* pDest, const MAE_WChar* pSource);

/**
 *  mae_wstrncat
 *  \brief  concatenate at most n characters of string pSource to pDest,
 *          terminate pDest with '\0'
 *
 *  \param  pDest                  Pointer to the MAE_WChar
 *  \param  pSource                Pointer to the MAE_WChar
 *  \param  nCount                  number of n characters of pSource to be concatenate to pDest
 *  \retval MAE_WChar*             Pointer to the pDest
 */
 MAE_WChar* mae_wstrncat(MAE_WChar* pDest, const MAE_WChar* pSource, size_t nCount);

 /**
 *  mae_wstrcmp
 *  \brief  compare string pString1 to string pString2
 *
 *  \param  pString1               Pointer to the MAE_WChar
 *  \param  pString2               Pointer to the MAE_WChar
 *  \retval s16                    < 0 if pString1 < pString2
 *                                 = 0 if pString == pString2
 *                                 > 0 if pString > pString2
 */
s32 mae_wstrcmp(const MAE_WChar* pString1, const MAE_WChar* pString2);

 /**
 *  mae_wstrncmp
 *  \brief  compare at most n string pString1 to string pString2
 *
 *  \param  pString1               Pointer to the MAE_WChar
 *  \param  pString2               Pointer to the MAE_WChar
 *  \param  nCount                  number of n characters to be compared
 *  \retval s16                    < 0 if pString1 < pString2
 *                                 = 0 if pString == pString2
 *                                 > 0 if pString > pString2
 */
s32 mae_wstrncmp(const MAE_WChar* pString1, const MAE_WChar* pString2, size_t nCount);

/**
 *  mae_wstrstr
 *  \brief  Returns part of pString1 from the first occurrence of pString2 to the end of pString1
 *
 *  \param  pString1               Pointer to the MAE_WChar
 *  \param  pString2               Pointer to the MAE_WChar
 *  \retval MAE_WChar*             The pointer to the resulting MAE_WChar String
 */
MAE_WChar* mae_wstrstr(const MAE_WChar* pString1, const MAE_WChar* pString2);

/**
 *  mae_wstrtrim
 *  \brief  To trim the space characters in head and tail of string.
 *
 *  \param  pString1               Pointer to the MAE_WChar
 *  \param  pString2               Pointer to the MAE_WChar
 *  \retval MAE_WChar*             The pointer to the resulting MAE_WChar String
 */
MAE_WChar* mae_wstrtrim(MAE_WChar* pDest, const MAE_WChar* pSrc);

/**
 *  mae_swprintf
 *  @brief  swprintf is a wide-character version of sprintf; the pointer arguments to swprintf are wide-character strings.
 *
 *  @param  pBuf               Storage location for output
 *  @param  nCount              Maximum number of characters to store in the Unicode version of this function.
 *  @param  pFormat            Format-control string
 *  @retval u32                The number of characters written.
 */
u32 mae_swprintf( MAE_WChar *pBuf, int nCount, const MAE_WChar *pFormat, ...);

/**
 * Duplicate a wstring
 * @param pSrc the source string
 * @return NULL pStr is NULL, or no memory
 *         others the address of the new wstring
 */
MAE_WChar* mae_wstrdup(const MAE_WChar *pStrSource);

/**
 *
 * mae_watoi
 * @brief watoi is a wide-character conversion of string to integer.
 * @brief Please make sure that the parameter string is null-terminated.
 * @brief Note: This function only supports positive and negative decimal number format of string.
 *              It does not supports hex or oct number format of string, and it does not check if the number exceeds MAX or MIN value.
 *
 * @param  pString        Pointer to a MAE_WChar
 * @retval u32            The converted value
 *
 */
s32 mae_watoi(const MAE_WChar* pString);

/**
 *
 * mae_watof
 * @brief watof is a wide-character conversion of string to floating point number
 * @brief Please make sure that the parameter string is null-terminated.
 *
 * @param pString   Pointer to a MAE_WChar
 * @retval double   The converted value
 */
double mae_watof(const MAE_WChar* pString);


/**
 *  mae_mwprintf
 *  @brief  mwprintf acts like swprintf excepts the output memory is allocated automatically.
 *  @param  pFormat            Format-control string
 *  @retval u32                The number of characters written.
 */
MAE_WChar *mae_mwprintf(const MAE_WChar *pFormat, ...);

 /**
 *  mae_utf8strlen
 *  \brief  return the number of utf8 characters
 *
 *  \param  pUTF8                  Pointer to the u8
 *  \param  nTotalBytes             total nLength in bytes of utf8
 *  \retval u32                    number of utf8 characters
 */
u32 mae_utf8strlen(u8* pUTF8, size_t nTotalBytes);

/**
 *  mae_makeOneByteBCD
 *  \brief  convert a nBinary value to a BCD value 2x4bit nibbles network byte order
 *
 *  \param  nBinary                input value
 *  \retval u8                    bcd value
 */
u8 mae_makeOneByteBCD(u8 nBinary);

/**
 *  mae_makeTwoByteBCD
 *  \brief  convert a nBinary value to a BCD value 4x4bit nibbles network byte order
 *
 *  \param  nBinary                input value
 *  \retval u16                   bcd value
 */
u16 mae_makeTwoByteBCD(u16 nBinary);


/**
 *  mae_isdigit
 *  \brief  decimal digit
 *
 *  \param  ch                    MAE_WChar
 *  \retval u8                    true/false
 */
u8 mae_isdigit(MAE_WChar ch);

/**
 *  mae_isalpha
 *  \brief  mae_isupper(MAE_WChar) or mae_islower(MAE_WChar) is true
 *
 *  \param  ch                    MAE_WChar
 *  \retval u8                    true/false
 */
u8 mae_isalpha(MAE_WChar ch);

/**
 *  mae_islower
 *  \brief  lower-case letter
 *
 *  \param  ch                    MAE_WChar
 *  \retval u8                    true/false
 */
u8 mae_islower(MAE_WChar ch);

/**
 *  mae_isupper
 *  \brief  upper-case letter
 *
 *  \param  ch                    MAE_WChar
 *  \retval u8                    true/false
 */
u8 mae_isupper(MAE_WChar ch);

/**
 *  mae_isspace
 *  \brief  space, formfeed, newline, carriage return, tab, vertical tab
 *
 *  \param  ch                    MAE_WChar
 *  \retval u8                    true/false
 */
u8 mae_isspace(MAE_WChar ch);

/**
 *  mae_isnbsp
 *  \brief  no breaking space
 *
 *  \param  ch                    MAE_WChar
 *  \retval u8                    true/false
 */
u8 mae_isnbsp(MAE_WChar ch);

/**
 *  mae_isbreak
 *  \brief  CR or LF
 *
 *  \param  ch                    MAE_WChar
 *  \retval u8                    true/false
 */
u8 mae_isbreak(MAE_WChar ch);

/**
 *  mae_isCR
 *  \brief  CR
 *
 *  \param  ch                    MAE_WChar
 *  \retval u8                    true/false
 */
u8 mae_isCR(MAE_WChar ch);

/**
 *  mae_isLF
 *  \brief  LF
 *
 *  \param  ch                    MAE_WChar
 *  \retval u8                    true/false
 */
u8 mae_isLF(MAE_WChar ch);

/**
 *  mae_istab
 *  \brief  tab
 *
 *  \param  ch                    MAE_WChar
 *  \retval u8                    true/false
 */
u8 mae_istab(MAE_WChar ch);

/**
 *  mae_isprint
 *  \brief  undisplay char
 *
 *  \param  ch                    MAE_WChar
 *  \retval u8                    true/false
 */
u8 mae_isprint(MAE_WChar ch);

/**
 *  mae_toupper
 *  \brief  covert ch to upper case
 *
 *  \param  ch                    MAE_WChar
 *  \retval MAE_WChar             return upper case of ch
 */
MAE_WChar mae_toupper(MAE_WChar ch);

/**
 *  mae_tolower
 *  \brief  convert ch to lower case
 *
 *  \param  ch                    MAE_WChar
 *  \retval MAE_WChar             return lower case of ch
 */
MAE_WChar mae_tolower(MAE_WChar ch);

/**
 * \brief transform a wstr string to lower case
 * \param pSrc the source string
 */
void mae_wstrtolower(MAE_WChar *pSrc);

/**
 * \brief transform a u8 string to lower case
 * \param pSrc the source string
*/
void mae_strtolower(u8 *pSrc);

/**
 * \brief transform a u8 string to upper case
 * \param pSrc the source string
*/
void mae_strtoupper(u8 *pSrc);

/**
 *  mae_AsciiToUCS2
 *  \brief  convert Ascii code to nUnicode
 *
 *  \param  pUnicode              nUnicode
 *  \param  pAscii                ascii
 *  \retval u16*                  return nUnicode
 */
u16* mae_AsciiToUCS2(u16* pUnicode, const u8* pAscii);

/**
 *  mae_AsciiToUCS2WithAllocate - using this function MUST remember to free the result(pUnicode)
 *  \brief  Allocate memory to store the converted result. Using this function does not need to 
 *          allocate memory in advance, but MUST remember to free the result(pUnicode) to avoid memory leak.
 *  \param  pUnicode              Unicode
 *  \param  pAscii                Ascii
 *  \param  pOutStrLen            output string length of pAscii
 *  \retval MAE_Ret               MAE_RET_SUCCESS/MAE_RET_BAD_PARAM/MAE_RET_OUT_OF_MEMORY/MAE_RET_FAILED
 */
MAE_Ret mae_AsciiToUCS2WithAllocate(u16** ppUnicode, const u8* pAscii, u32* pOutStrLen);

/**
 *  mae_AsciiToUCS2Ex
 *  \brief  convert Ascii code to nUnicode
 *
 *  \param  pUnicode              nUnicode
 *  \param  pAscii                ascii
 *  \param  asciiLen              ascii nLen
 *  \retval u16*                  return nUnicode
 */
u16* mae_AsciiToUCS2Ex(u16* pUnicode, const u8* pAscii, size_t asciiLen);

/**
 *  mae_AsciiToUCS2WithAllocate - using this function MUST remember to free the result(pUnicode)
 *  \brief  Allocate memory to store the converted result. Using this function does not need to 
 *          allocate memory in advance, but MUST remember to free the result(pUnicode) to avoid memory leak.
 *  \param  pUnicode              Unicode
 *  \param  pAscii                Ascii
 *  \param  asciiLen              ascii nLen
 *  \param  pOutStrLen            output string length of pAscii
 *  \retval MAE_Ret               MAE_RET_SUCCESS/MAE_RET_BAD_PARAM/MAE_RET_OUT_OF_MEMORY/MAE_RET_FAILED
 */
MAE_Ret mae_AsciiToUCS2ExWithAllocate(u16** ppUnicode, const u8* pAscii, size_t nAsciiLen, u32* pOutStrLen);

/**
 *  mae_UCS2ToAscii
 *  \brief  convert nUnicode to Ascii
 *
 *  \param  pUnicode              ascii
 *  \param  pAscii                nUnicode
 *  \retval u16*                  return ascii
 */
u8* mae_UCS2ToAscii(u8* pAscii, const u16* pUnicode);

/**
 *  mae_UCS2ToAsciiWithAllocate - using this function MUST remember to free the result(pAscii)
 *  \brief  Allocate memory to store the converted result. Using this function does not need to 
 *          allocate memory in advance, but MUST remember to free the result(pAscii) to avoid memory leak.
 *  \param  pAscii                ascii
 *  \param  pUnicode              Unicode
 * \param   pOutStrLen            output string length of pUnicode
 *  \retval MAE_Ret               MAE_RET_SUCCESS/MAE_RET_BAD_PARAM/MAE_RET_OUT_OF_MEMORY/MAE_RET_FAILED
 */
MAE_Ret mae_UCS2ToAsciiWithAllocate(u8** ppAscii, const u16* pUnicode, u32* pOutStrLen);

/**
 *  mae_UCS2ToAsciiEx
 *  \brief  convert nUnicode to ascii by nUnicodeLen. If nUnicodeLen <=0 or nUnicodeLen =UINT_MAX,  converting will be stopped when encountering invalid Unicode or Unicode = 0
 *
 *  \param  pUnicode              nUnicode
 *  \param  pAscii                ascii
 *  \param  nUnicodeLen            nUnicode nLen
 *  \retval u8*                   return ascii
 */
u8* mae_UCS2ToAsciiEx(u8* pAscii, const u16* pUnicode, size_t nUnicodeLen);

/**
 *  mae_UCS2ToAsciiExWithAllocate - using this function MUST remember to free the result(pAscii)
 *  \brief  Allocate memory to store the converted result. Using this function does not need to 
 *          allocate memory in advance, but MUST remember to free the result(pAscii) to avoid memory leak.
 *  \param  pAscii                ascii
 *  \param  pUnicode              Unicode
 *  \param  nUnicodeLen           nUnicode nLen
 *  \param  pOutStrLen            output string length of pUnicode
 *  \retval MAE_Ret               MAE_RET_SUCCESS/MAE_RET_BAD_PARAM/MAE_RET_OUT_OF_MEMORY/MAE_RET_FAILED
 */
MAE_Ret mae_UCS2ToAsciiExWithAllocate(u8** ppAscii, const u16* pUnicode, size_t nUnicodeLen, u32* pOutStrLen);

/**
 *  mae_GSMToUCS2
 *  \brief  change the 03.38 gsm code to the standard nUnicode
 *
 *  \param  pUnicode              nUnicode
 *  \param  nGsmCode               nGsmCode
 *  \retval u8                    true/false
 */
u8 mae_GSMToUCS2(u16* pUnicode, u16 nGsmCode);

/**
 *  mae_UCS2ToGSM
 *  \brief  change nUnicode to the gsm 03.38 code
 *
 *  \param  pGsmCode              nGsmCode
 *  \param  nUnicode               nUnicode
 *  \retval u8                    true/false
 */
u8 mae_UCS2ToGSM(u16* pGsmCode, u16 nUnicode);

/**
 *  mae_GSMStrToUCS2Str
 *  \brief  change 03.38 gsm code string to standard nUnicode string
 *
 *  \param  pUnicode           nUnicode
 *  \param  nGsmCode               nGsmCode
 *  \param  nSrcLen                source nLength
 *  \param  pDstStrLen             pDest nLength
 *  \retval u8                    true/false
 */
u8 mae_GSMStrToUCS2Str(u16* pUnicode, u8* nGsmCode, size_t nSrcLen, size_t *pDstStrLen  );

/**
 *  mae_UCS2StrToGSMStr
 *  \brief  change nUnicode string to the gsm 03.38 string
 *
 *  \param  pGsmCode             output nGsmCode str
 *  \param  pUnicode          nUnicode str
 *  \param  nSrcStrLen            source nLength
 *  \param  pDstLen               pDest nLength
 *  \param  nMaxLen              pDest maximum str nLength
 *  \retval u8                   true/false
 */
u8 mae_UCS2StrToGSMStr(u8* pGsmCode, u16 *pUnicode, size_t nSrcStrLen, size_t *pDstLen, size_t nMaxLen);

/**
 *  mae_UCS2ToBCD
 *  \brief  convert nUnicode to BCD code
 *
 *  \param  eBcdFmt               BCD Format
 *  \param  pUnicode             nUnicode
 *  \param  pBcd                 BCD
 *  \retval
 */
void mae_UCS2ToBCD(ustr_BcdFormat_e eBcdFmt, u16* pUnicode, u8* pBcd );  //<-------------- need more modification

/**
 *  mae_UCS2ToBCD
 *  \brief  convert nUnicode to BCD code
 *
 *  \param  eBcdFmt               BCD Format
 *  \param  pBcd                 BCD
 *  \param  nBcdLen               nLength of BCD
 *  \param  pUnicode             nUnicode
 *  \retval
 */
void mae_BCDToUCS2(ustr_BcdFormat_e eBcdFmt, u8 *pBcd, size_t nBcdLen, u16* pUnicode ); //<----------- need more modification

/**
 *  mae_UCS2ToBCD
 *  \brief  get BCD number nLength
 *
 *  \param  eBcdFmt               BCD Format
 *  \param  pBcd                 BCD
 *  \retval u16                  bcd nLength
 */
u16 mae_getBCDLen(ustr_BcdFormat_e eBcdFmt, u8 *pBcd );

/**
 *  mae_UTF8ToUCS2
 *  \brief  convert string in pUTF8 to pUCS2
 *          The result of converted pUCS2 string will be stored at pwszOutStr, and
 *          the pOutStrByteLen will store the byte nLength of pUCS2 string.
 *          Client should malloc enough memory space for storing the result pUCS2 string.
 *          The space should no less than sizeof(MAE_WChar)*mae_utf8strlen(pUTF8).
 *          (should no less than sizeof(MAE_WChar)*(mae_utf8strlen(pUTF8)+1) if nUTF8Bytes
 *          includes a null terminate.)
 *          This function will convert a NULL from pUTF8 to a NULL to pUCS2Out and will not
 *          stop when meet NULL.
 *
 *  \param pUTF8			[in] pointer to utf8 string
 *  \param nUTF8Bytes		[in] nLength of utf8 in bytes
 *  \param pUCS2Out		[out] result of pUCS2 string converted from pUTF8
 *  \param pBytesWritten	[out] number of bytes written to pwszOutStr
 *  \retval
 */
void mae_UTF8ToUCS2(u8 *pUTF8, size_t nUTF8Bytes, u16 *pUCS2Out, size_t *pBytesWritten);

/**
 *  mae_UCS2ToUTF8
 *  \brief  convert string in pUCS2 to pUTF8
 *          The result of converted pUTF8 string will be stored at utf8, and
 *          the nByteLength will store the nLength of utf8 string.
 *          Client should malloc enough memory space for storing the result pUTF8 string.
 *          If you do not know how many spaces should be allocated. Use (nLen*3)+1 is safe
 *          because a pUTF8 character may need at most 3 bytes.
 *          Or you can use mae_getUTF8ByteFromUCS2() to get the number of bytes needed.
 *          (the space should no less than mae_getUTF8ByteFromUCS2()+1 if nLen includes a NULL
 *          terminate for soruce pUCS2 string)
 *
 *  \param  pUCS2		[in] pointer to pUCS2 string
 *  \param  nLen				[in] number of characters of source pUCS2 string
 *  \param  pUTF8Out		[out] result of pUTF8 string converted from pUCS2
 *  \param  pBytesWritten	[out] number of bytes written to pUTF8Out
 *  \retval
 */
void mae_UCS2ToUTF8(u16 *pUCS2, size_t nLen, u8 *pUTF8Out, size_t *pBytesWritten);

/**
 *  mae_UCS2ToUTF8
 *  \brief  convert string in pUCS2 to pUTF8
 *          The result of converted pUTF8 string will be stored at utf8, and
 *          the nByteLength will store the nLength of utf8 string.
 *
 *  \param  pUCS2		[in] pointer to pUCS2 string
 *  \param  nLen				[in] number of characters of source pUCS2 string
 *  \param  pUTF8Out		[out] result of pUTF8 string converted from pUCS2
 *  \param  nUTF8ByteLen    [in]  the byte nSize of the pUTF8 string buffer (not includes the NULL terminate)
 *  \param  pBytesWritten	[out] number of bytes written to pUTF8Out
 *  \retval
 */
void mae_UCS2ToUTF8Ex(u16 *pUCS2, size_t nLen, u8 *pUTF8Out, size_t nUTF8ByteLen, size_t *pBytesWritten);


#ifdef __SMS_3GPP_R8_SUPPORT__
MAERet_t mae_UCS2GetGSMNLEncodeInf( const u16 *pu16Str, u16 u16StrLen, mmiGsmEncodeInf_t *psInf, u16 *pu16Ucs2Count, u16 *pu16ExtCount );
u16 mae_strGSMNLToUCS2( const u8 *pu8Str, u16 u16Strlen, u16 *pu16Str, u16 u16BufferSize, mmiGsmLockShiftTable_e eLockShift, mmiGsmSingleShiftTable_e eSingleShift );
u16 mae_strUCS2ToGSMNL( const u16 *pu16Str, u16 u16Strlen, u8 *pu8Str, u16 u16BufferSize, mmiGsmLockShiftTable_e eLockShift, mmiGsmSingleShiftTable_e eSingleShift );
/**
 *  mae_GSMToUCS2 : change the 03.38 gsm nCode to the standard nUnicode
 */
u8 mae_GSMToUCS2byLang(u16* pUnicode, u16 nGsmCode, u16 langId);

/**
 *  mae_UCS2ToGSM : change nUnicode to the gsm 03.38 nCode
 */
u8 mae_UCS2ToGSMbyLang(u16* pGsmCode, u16 nUnicode, u16 langId);
#endif//__SMS_3GPP_R8_SUPPORT__

/**
 *  mae_strcatUCS2StrGSMStr
 *  \brief  concatenate one pUCS2 string and one GSM string to UCS2String
 *
 *  \param  pFrontStr             pUCS2 string
 *  \param  nFrontStrLen          pUCS2 string nLength
 *  \param  pBackStr              GSM string
 *  \param  nBackStrLen           GSM string nLength
 *  \retval size_t                  nLength of the concatenation
 */
size_t mae_strcatUCS2StrGSMStr(u16 *pFrontStr, size_t nFrontStrLen, u8 *pBackStr, size_t nBackStrLen);

/**
 *  mae_strcatGSMStrUCS2Str
 *  \brief  concatenate one GSM string and one pUCS2 string to UCS2String
 *
 *  \param  pFrontStr             GSM string
 *  \param  nFrontStrLen          GSM string nLength
 *  \param  pBackStr              pUCS2 string
 *  \param  nBackStrLen           pUCS2 string nLength
 *  \retval  size_t                  nLength of the concatenation
 */
size_t mae_strcatGSMStrUCS2Str(u8 *pFrontStr, size_t nFrontStrLen, u8 *pBackStr, size_t nBackStrLen);


/**
 *  mae_UCS2EndianCvrt
 *  \brief  convert the byte order when send/receive signal from network
 *          Allow source and destination the same
 *
 *  \param  pDst                  pDest pointer
 *  \param  pSrc                  pSrc pointer
 *  \param  nStrLen               nLength
 *  \retval
 */
void mae_UCS2EndianCvrt(u8* pDst, u8* pSrc, size_t nStrLen);

/**
 *  mae_isUCS2Str
 *  \brief  check whether a string is pUCS2 format only
 *
 *  \param  pUnicode           nUnicode
 *  \param  nSrcLen                nLength
 *  \retval u8                    1 means cannot be represented by defualt
 */
u8 mae_isUCS2Str(u16* pUnicode, size_t nSrcLen);

/**
 *  mae_getUTF8ByteFromUCS2
 *  \brief  get the number of total pUTF8 bytes for the specified pUCS2 string
 *
 *  \param  pUCS2                  ucs2
 *  \param  nCharNum               char number
 *  \retval u32                   number of total pUTF8 bytes
 */
u32 mae_getUTF8ByteFromUCS2(u16 *pUCS2, size_t nCharNum);


/**
 *  mae_utf8_getUCS2_Char
 *  \brief  converts the first pUTF8 character to a pUCS2 character
 *
 *  \param  pUTF8                  pUTF8 string
 *  \param  pUCS2Char             the converted pUCS2 char
 *  \retval u32                   0 - wrong pUTF8 char
 *                                1 - 1 byte-pUTF8 char
 *                                2 - 2 byte-pUTF8 char
 *                                3 - 3 byte-pUTF8 char
 */
u32 mae_utf8_getUCS2_Char(u8 *pUTF8, u16 *pUCS2Char);

/**
 *  mae_isUCS2NumberStr
 *  \brief  check whether the ucs2 is a number string
 *
 *  \param  pUCS2                  ucs2
 *  \param  nStrLen                strlen of ucs2
 *  \retval u8                    ture/false
 */
u8 mae_isUCS2NumberStr(u16 *pUCS2, size_t nStrLen);

/**
 *  mae_isUCS2AsciiOnlyStr
 *  \brief  check whether an pUCS2 string contains ASCII characters (0x00-0xFF) only
 *
 *  \param  pUCS2                  ucs2 string
 *  \param  nSrcLen                ucs2 string nLength
 *  \retval u8                    1 means the ucs2 string contains ASCII only
 */
u8 mae_isUCS2AsciiOnlyStr(u16 *pUCS2, size_t nStrLen);

/**
 *  mae_isAlphaNumeric
 *  \brief   Check whether a given UCS2 character is an alphanumeric char (Alphanumeric: a~z, A~Z, 0~9  mae_isalpha or mae_isdigit)
 *
 *  \param  chUcs2             ucs2 character
 *  \retval boolean            ture/false
 */
boolean mae_isAlphaNumeric(MAE_WChar chUcs2);

/**
 *  mae_isValidUCS2Email
 *  \brief  Check whether a given UCS2 string is a valid email
 *
 *  \param  pEmailStr             ucs2 e-mail string
 *  \param  nStrLen               ucs2 string length
 *  \retval boolean               ture/false
 */
boolean mae_isValidUCS2Email(MAE_WChar* pEmailStr,u32 nStrLen);

/**
 *  mae_UCS2ChangeSpecialCharTo
 *  \brief  change pUCS2 special character
 *
 *  \param  pUCS2                  ucs2
 *  \param  nUCS2Length         strlen of ucs2
 *  \param  nChar               special character
 *  \retval
 */
void mae_UCS2ChangeSpecialCharTo(u16 *pUCS2, size_t nUCS2Length, u16 nChar);

/**
 *  mae_decode_sim_alpha_id
 *  \brief  decode sim alpha id
 *
 *  \param  pSrc                  source pointer
 *  \param  nSrcLen                source nLength
 *  \param  pDest                 destination pointer
 *  \param  pDestLen              destination nLength
 *  \retval u8                    true/false
 */
u8 mae_decode_sim_alpha_id(u8* pSrc, size_t nSrcLen, u16* pDest, size_t* pDestLen);

/**
 *  mae_mmiEncodeSimUCS2
 *  \brief  encode nUnicode string with SIM format.
 *
 *  \param  eUcs2Mode              pUCS2 mode
 *  \param  pSrc                   source pointer
 *  \param  nSrcLen                source nLength
 *  \param  pDest                  destination pointer
 *  \param  pDestLen               destination nLength
 *  \param  nMaxLen                destination maximum nLength
 *  \retval u8                    true/false
 */
u8 mae_mmiEncodeSimUCS2(mmiSimCodingScheme_e eUcs2Mode, u16 *pSrc, size_t nSrcLen, u8 *pDest, size_t *pDestLen, size_t nMaxLen);

/**
 *  mae_mmiEncodeSimUCS2Type
 *  \brief  find out which encoding type should be appled for this input string
 *
 *  \param  pSrc                   input string
 *  \param  nSrcLen                input nLength
 *  \retval mmiSimCodingSchemeE   coding scheme
 */
mmiSimCodingScheme_e mae_mmiEncodeSimUCS2Type(u16 *pSrc, size_t nSrcLen);

/**
 *  mae_mmiEncodeSimUCS2AllFormat
 *  \brief   encode nUnicode string with SIM format
 *
 *  \param  pSrc                   input string
 *  \param  nSrcLen                input character nLength (number of words)
 *  \param  pDest                  output string
 *  \param  pDestLen               destination's output nLength in byte
 *  \param  nMaxLen                destination's maximum nLength in byte,
 *                                the recommended pDest buffer nLength is 2*(maximum source string nLength) + 1 //NULL terminator
 *                                                                      //For pUCS2 encoding, each word occupies 2 bytes.
 *  \retval mmiSimCodingSchemeE   coding scheme
 */
mmiSimCodingScheme_e mae_mmiEncodeSimUCS2AllFormat(u16 *pSrc, size_t nSrcLen, u8 *pDest, size_t *pDestLen, size_t nMaxLen);


void mae_initDevStr(size_t nSize, u8** pDevStr);

/** mae_releaseDevStr
 *	@brief Free DevStr.
 *  @param pDevStr
 */
void mae_releaseDevStr(u8* pDevStr);

/** mae_convertWStrToDevStr
 *  @brief Convert MAE_Char string to DevStr.
 *  Ex: 0x0041 0x0042 0x0043 0x0000 -> 0x90 0x00 0x03 0x00 0x41 0x00 0x42 0x00 0x43 0x00
 *  The function does not check memory boundary, user should check the nLength of pSrc string first
 *  and allocate enough space via mae_initDevStr().
 *  @param pSrc	Source string in u16 format
 *  @param pDest Dest string in Montage Device String format
 */
void mae_convertWStrToDevStr(const MAE_WChar *pSrc, u8* pDest);

/** mae_convertDevStrToWStr
 *  @brief Convert DevStr to MAE_Char string.
 *  Ex: 0x90 0x00 0x03 0x00 0x41 0x00 0x42 0x00 0x43 0x00 -> 0x0041 0x0042 0x0043 0x0000
 *  The function does not check memory boundary, user should check the nLength of pSrc string first
 *  @param pSrc	Source string in Montage Device String format
 *  @param pDest Dest string in u16 format
 */
void mae_convertDevStrToWStr(const u8 *pSrc, MAE_WChar* pDest);


/** mae_hexCharToInt
 *  @brief convert Hex char to integer
 *  Ex: "F" --> 15
 *  @param hex	Hex character
 */
u8 mae_hexCharToInt(u8 hex);


/** mae_hexStrToBytes
 *  @brief Convert Hex string to byte string.
 *  Ex: "76EE524D" --> 0x76 0xee 0x52 0x4d
 *  @param pStr	Source pointer
 *  @param pOut Dest pointer
 */
size_t mae_hexStrToBytes(const u8 *pStr, u8 *pOut);

/** mae_hexStrToBytesWithSize
 *  @brief Convert Hex string to byte string.
 *  Ex: "76EE524D" --> 0x76 0xee 0x52 0x4d
 *  @param pStr	Source pointer
 *  @param pOut Dest pointer
  *  @param nMaxLen max out str nLen
  */
size_t mae_hexStrToBytesWithSize(const u8 *pStr, u8 *pOut, size_t nMaxBytes)  ;

/** mae_bytesToHexStr
 *  @brief Convert bytes to Hex string.
 *  Ex:  0x76 0xee 0x52 0x4d --> "76EE524D"
 *  @param pStr	Source pointer
 *  @param pOut Dest pointer
 *  @param nByteLength bytes nLength
 */
u8* mae_bytesToHexStr(const u8 *pStr, u8 *pOut, size_t nByteLength);


 /** mae_U8StrToU16Str
 *  @brief Convert u8 array to u16 array.
 *  Ex: 0x76 0xee 0x52 0x4d --> 0x76ee 0x524d
 *  @param pU8Str  Source pointer
 *  @param pU16Out Dest pointer
 *  @param nLength  Source u8 nLength
 */
u16* mae_U8StrToU16Str(const u8 *pU8Str, u16 *pU16Out, size_t nLength);



u32  mae_CRC32Checksum(u32 crc32, const u8 *pBuf, size_t nLength);


const u8* mae_GetMimeType(u8 nMimeType);

/** mae_convertFullWidthToHalfWidth
 *  @brief Convert Full-Width Wide Character String to Half-Width Character String
 *  @param pSrc	Source wide string pointer
 */
MAE_Ret mae_convertFullWidthToHalfWidth(MAE_WChar *pSrc);

/**
*  mae_wstrnicmp
*  \brief  compare at most n string pString1 to string pString1 -- case insensitive version
*
*  \param  pString1               Pointer to the MAE_WChar
*  \param  pString2               Pointer to the MAE_WChar
*  \retval s16                    < 0 if pString1 < pString2
*                                 = 0 if pString == pString2
*                                 > 0 if pString > pString2
*/
s32 mae_wstricmp(const MAE_WChar *pStr1, const MAE_WChar *pStr2);

/**
 *  mae_wstrnicmp
 *  \brief  compare at most n string pString1 to string pString1 -- case insensitive version
 *
 *  \param  pString1               Pointer to the MAE_WChar
 *  \param  pString2               Pointer to the MAE_WChar
 *  \param  nCount                  number of n characters to be compared
 *  \retval s16                    < 0 if pString1 < pString2
 *                                 = 0 if pString == pString2
 *                                 > 0 if pString > pString2
 */
s32 mae_wstrnicmp(const MAE_WChar *pStr1, const MAE_WChar *pStr2, size_t nCount);

/**
 *  mae_wstrGetCombineCode
 *  \brief  try to combine character at string pTxt -- case insensitive version
 *
 *  \param  pTxt               	 Pointer to the MAE_WChar
 *  \param  nLen               	 nLen of pTxt
 *  \param  pOutChar            Return combined character
 *  \retval   u16                    = 0 no character combined
 *                                 	> 0 how many character at string pOutChar
 *
 *  Ex: input pTxt = ABCD, nLen = 4
 *        In Thai, ABC would be show as one character, but not combined
 *        => pOutChar = don't care, retval = 3
 *
 *        In Vietnam, AB would be combined as one character Z
 *        => pOutChar = Z, retval = 1
 *
 *        In normal case, no character would be combined
 *        => pOutChar = don't care, retval = 0
 */
u16 mae_wstrGetCombineCode(const MAE_WChar *pTxt, u16 nLen, MAE_WChar *pOutChar);
/*-------------------------------------------------------------------------*/

/*****************************************************************************
*!!! NOTICE !!!
* The followings are moved from mmi_common_encoding.h, for the purpose that
* MAE can not include any header file in app/srv/mmi_common level.
* This is just a temporary solution! It should be modified in the future!
******************************************************************************/
MAE_WChar * mmi_Common_ConvertToUCS2AccordingToDisplayLang(u8 *pInStr, size_t nInStrByteLen, MAE_WChar *pOutStr, size_t nOutStrByteLen, IBase *pOwner);
/**************
* End of NOTICE
**************/


/*
Compare characters of two strings without regard to case.

The characters from 91 to 96 in the ASCII table ('[', '\', ']', '^', '_', and '`') will evaluate as less than any alphabetic character. This ordering is identical to that of stricmp.

*/
s32 mae_strnicmp(const char *pStr1, const char *pStr2, size_t nSize);

/*
@brief strrstr - locate a substring

Synopsis

char* strrstr(const char* pHaystack, const char* pNeedle);

Description

The strrstr() function finds the last occurrence of the substring pNeedle in the string pHaystack. The terminating '\0' characters are not compared.

@return 	The strrstr() function returns a pointer to the beginning of the substring, or NULL if the substring is not found or one of pHaystack and pNeedle is NULL.

*/

char* mae_strrstr(const char* pHaystack, const char* pNeedle);

#endif // __MAE_HELPER_H__

