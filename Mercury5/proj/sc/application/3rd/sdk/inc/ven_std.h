/**
 *
 * @file    ven_std.h
 * @brief   This file defines the standard lib interface of SDK
 *
 * @author  Code.Lin
 * @version $Id: ven_std.h 47224 2009-12-17 15:14:15Z kenny.wu $
 *
 */

#ifndef __VEN_STD_H__
#define __VEN_STD_H__

#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "vm_stdio.ho"

#include "ven_types.h"

extern void sysUtil_AsciiStringToUCS2String(u16 *pstrDest, const u8 *pszSrc);
extern u16 sysUtil_UCS2StringAsciiCat(u16 *pstrDest, const u8 *pszSrc);
extern u16 *sysUtil_UCS2StrStr(const u16 *pstrDest, const u16 *pstrSrc);

extern void HELPER_UTF8ToUCS2(u8 *pUTF8, u16 inUTF8Bytes, u16 *pwszUCS2Out, u16 *pBytesWritten);
extern void HELPER_UCS2ToUTF8(u16 *pwszUCS2, u16 len, u8 *pUTF8Out, u16 *pBytesWritten);
extern u16 *ven_util_convertBIG5StrToUCS2Str(u8 *pInStr, u32 nInStrByteLen, u16 *pOutStr, u32 nOutStrByteLen);
extern u16 *ven_util_convertGBStrToUCS2Str(u8 *pInStr, u32 nInStrByteLen, u16 *pOutStr, u32 nOutStrByteLen);
extern u8 *ven_util_convertUCS2StrToBig5Str(u16 *pInStr, u32 nInStrByteLen, u8 *pOutStr, u32 nOutStrByteLen);
extern u8 *ven_util_convertUCS2StrToGBStr(u16 *pInStr, u32 nInStrByteLen, u8 *pOutStr, u32 nOutStrByteLen);

extern s32 ven_util_rand(void);
extern void ven_util_srand(u32 seed);
extern void ven_util_srandByTime(void);
extern u32 ven_util_randGetInteger(u32 nFrom, u32 nTo);

/*
Compare characters of two strings without regard to case.

The characters from 91 to 96 in the ASCII table ('[', '\', ']', '^', '_', and '`') will evaluate as less than any alphabetic character. This ordering is identical to that of stricmp.

*/
extern s16 HELPER_strnicmp(const char *pStr1, const char *pStr2, size_t nSize);

/*
@brief strrstr - locate a substring

Synopsis

char* strrstr(const char* haystack, const char* needle);

Description

The strstr() function finds the last occurrence of the substring needle in the string haystack. The terminating '\0' characters are not compared.

@return     The strstr() function returns a pointer to the beginning of the substring, or NULL if the substring is not found or one of haystack and needle is NULL.

*/

extern char* HELPER_strrstr(const char* haystack, const char* needle);

/**
 * @brief  mae_getUCS2LenFromUTF8 : get the number of UCS2 chars for the specified UTF8 string
 * @param   pUTF8   utf8 string
 * @param   charNum   number of bytes of utf8 string.
 * @retval   Number of UCS2 characters.
 */
extern u32 HELPER_getUCS2LenFromUTF8(u8 *pUTF8, u32 charNum);

/**
 *  char *ven_std_strcpy(char *pDest, const char *pSrc);
 *  @brief  Copies one string to another
 *
 *  @param  pDest           [in]Pointer to destination string
 *  @param  pSrc            [in]Pointer to source string
 *
 *  @retval Pointer to output string
 */
#define  ven_std_strcpy        strcpy

/**
 *  char *ven_std_strncpy(char *pDest, const char *pSrc, size_t n);
 *  @brief  Copies up to n characters from the string pointed to by pSrc to pDest.
 *
 *  @param  pDest           [in]Pointer to destination string
 *  @param  pSrc            [in]Pointer to source string
 *
 *  @retval Pointer to destination string
 */
#define  ven_std_strncpy       strncpy

/**
 *  size_t ven_std_strlen(const char *pStr);
 *  @brief  Computes the length of the string str up to but not including the terminating null character.
 *
 *  @param  pStr            [in]Pointer to input string
 *
 *  @retval The number of characters in the string
 */
#define  ven_std_strlen        strlen

/**
 *  char *ven_std_strcat(char *pDest, const char *pSrc);
 *  @brief  Appends the string pointed to by pSrc to the end of the string pointed to by pDest.
 *
 *  @param  pDest           [in]Pointer to destination string
 *  @param  pSrc            [in]Pointer to source string
 *
 *  @retval Pointer to destination string
 */
#define  ven_std_strcat        strcat

/**
 *  char *ven_std_strncat(char *pDest, const char *pSrc, size_t n);
 *  @brief  Appends the string pointed to by pSrc to the end of the string pointed to by pDest up to n characters long.
 *
 *  @param  pDest           [in]Pointer to destination string
 *  @param  pSrc            [in]Pointer to source string
 *
 *  @retval Pointer to destination string
 */
#define  ven_std_strncat       strncat

/**
 *  char *ven_std_strncat(char *pDest, const char *pSrc, size_t n);
 *  @brief  Appends the string pointed to by pSrc to the end of the string pointed to by pDest up to n characters long.
 *
 *  @param  pDest           [in]Pointer to destination string
 *  @param  pSrc            [in]Pointer to source string
 *
 *  @retval Pointer to destination string
 */
#define  ven_std_memset        memset


#define  ven_std_memcpy        memcpy

#define  ven_std_memcmp        memcmp

/**
 *  int ven_std_strcmp(const char *str1, const char *str2);
 *  @brief  Compares at most the first n bytes of str1 and str2.
 *
 *  @param  pStr1           [in]Pointer to string to compare
 *  @param  pStr2           [in]Pointer to string to compare
 *
 *  @retval Zero if str1 and str2 are equal.
 *          Less than zero or greater than zero if str1 is less than or greater than str2 respectively.
 */
#define  ven_std_strcmp        strcmp


#define  ven_std_stricmp       vm_stricmp

/**
 *  int ven_std_memcmp(const char *pStr1, const char *pStr2, size_t n);
 *  @brief  Compares at most the first n bytes of str1 and str2.
 *
 *  @param  pStr1           [in]Pointer to string to compare
 *  @param  pStr2           [in]Pointer to string to compare
 *
 *  @retval Zero if the first n bytes (or null terminated length) of str1 and str2 are equal
 *          Less than zero or greater than zero if str1 is less than or greater than str2 respectively.
 */
#define  ven_std_strncmp       strncmp

#define  ven_std_strnicmp      HELPER_strnicmp


/**
 *  char *ven_std_strtok(char *pStr1, const char *pStr2);
 *  @brief  Finds the next token in a string
 *
 *  @param  pStr1           [in]Pointer to string to strok
 *  @param  pStr2           [in]Pointer to the sctring containing the delimiters that determine the token
 *
 *  @retval Pointer to the first token in str1.
 *          NULL if no token is found
 */
#define  ven_std_strtok        strtok

/**
 *  int ven_std_strspn(const char *pStr1, const char *pStr2);
 *  @brief  Finds the first sequence of characters in the string str1 that contains any character specified in str2.
 *
 *  @param  pStr1           [in]Pointer to str1
 *  @param  pStr2           [in]Pointer to str2
 *
 *  @retval The length of this first sequence of characters found that match with str2
 */
#define  ven_std_strspn        strspn

/**
 *  char *ven_std_strstr(const char *pStr1, const char *pStr2);
 *  @brief  Finds the first occurrence of the entire string str2 (not including the terminating null character) which appears in the string str1.
 *
 *  @param  pStr1           [in]Pointer to str1
 *  @param  pStr2           [in]Pointer to str2
 *
 *  @retval Pointer to the first occurrence of str2 in str1
 *          NULL if no match was found
 *          Pointer to str1 if pStr2 points to a string of zero length
 */
#define  ven_std_strstr        strstr

#define  ven_std_strrstr       HELPER_strrstr

/**
 *  char *ven_std_strrchr(const char *pStr, int c);
 *  @brief  Searches for the last occurrence of the character c (an unsigned char) in the string pointed to by the argument str.
 *
 *  @param  pStr1           [in]Pointer to string
 *  @param  pStr2           [in]Unsigned char
 *
 *  @retval Pointer pointing to the last matching character
 *          NULL if no match was found
 */
#define  ven_std_strrchr       strrchr   //alpha added

/**
 *  int ven_std_strcspn(const char *pStr1, const char *pStr2);
 *  @brief  Finds the first sequence of characters in the string str1 that does not contain any character specified in str2.
 *
 *  @param  pStr1           [in]Pointer to str1
 *  @param  pStr2           [in]Pointer to str2
 *
 *  @retval Length of this first sequence of characters found that do not match with str2
 */
#define  ven_std_strcspn       strcspn

#define  ven_std_memmove       memmove
#define  ven_std_vsprintf      vsprintf

#define  ven_std_strchr        strchr
#define  ven_std_strtol        strtol

#define  ven_std_sprintf       sprintf
#define  ven_std_sscanf        sscanf
#define  ven_std_asciitoucs2   sysUtil_AsciiStringToUCS2String
#define  ven_std_ucs2asciicat  sysUtil_UCS2StringAsciiCat

#define  ven_std_ucs2toutf8    HELPER_UCS2ToUTF8
#define  ven_std_utf8toucs2    HELPER_UTF8ToUCS2
#define  ven_std_utf8strlen    HELPER_UTF8Strlen


/**
 *  u16 *ven_std_Big5ToUCS2(u8 *pInStr, u32 nInStrByteLen, u16 *pOutStr, u32 nOutStrByteLen)
 *  @brief  Convert BIG5 string to UCS2 string.
 *
 *  @param  pInStr          [in]Pointer to input string
 *  @param  nInStrByteLen   [in]Byte length of input string
 *  @param  pOutStr         [in]Pointer to output string
 *  @param  nOutStrByteLen  [in]Byte length of output string
 *
 *  @retval Pointer to output string
 */
#define  ven_std_Big5ToUCS2    ven_util_convertBIG5StrToUCS2Str

/**
 *  u16 *ven_std_GBToUCS2(u8 *pInStr, u32 nInStrByteLen, u16 *pOutStr, u32 nOutStrByteLen)
 *  @brief  Convert GB string to UCS2 string.
 *
 *  @param  pInStr          [in]Pointer to input string
 *  @param  nInStrByteLen   [in]Byte length of input string
 *  @param  pOutStr         [in]Pointer to output string
 *  @param  nOutStrByteLen  [in]Byte length of output string
 *
 *  @retval Pointer to output string
 */
#define  ven_std_GBToUCS2      ven_util_convertGBStrToUCS2Str

/**
 *  u8 *ven_std_UCS2ToBig5(u16 *pInStr, u32 nInStrByteLen, u8 *pOutStr, u32 nOutStrByteLen);
 *  @brief  Convert UCS2 string to BIG5 string.
 *
 *  @param  pInStr          [in]Pointer to input string
 *  @param  nInStrByteLen   [in]Byte length of input string
 *  @param  pOutStr         [in]Pointer to output string
 *  @param  nOutStrByteLen  [in]Byte length of output string
 *
 *  @retval Pointer to output string
 */
#define  ven_std_UCS2ToBig5    ven_util_convertUCS2StrToBig5Str

/**
 *  u8 *ven_std_UCS2ToGB(u16 *pInStr, u32 nInStrByteLen, u8 *pOutStr, u32 nOutStrByteLen);
 *  @brief  Convert UCS2 string to GB string.
 *
 *  @param  pInStr          [in]Pointer to input string
 *  @param  nInStrByteLen   [in]Byte length of input string
 *  @param  pOutStr         [in]Pointer to output string
 *  @param  nOutStrByteLen  [in]Byte length of output string
 *
 *  @retval Pointer to output string
 */
#define  ven_std_UCS2ToGB      ven_util_convertUCS2StrToGBStr

#define  ven_std_wstrcpy       wcscpy
#define  ven_std_wstrncpy      wcsncpy
#define  ven_std_wstrlen       wcslen
#define  ven_std_wstrcat       wcscat
#define  ven_std_wstrncat      wcsncat
#define  ven_std_wstrcmp       wcscmp
#define  ven_std_wstrncmp      wcsncmp
#define  ven_std_wstrspn       wcsspn
#define  ven_std_wstrcspn      wcscspn
#define  ven_std_vswprintf     vswprintf
#define  ven_std_wstrchr       wcschr
#define  ven_std_wstrrchr      wcsrchr
#define  ven_std_wstrtol       wcstol
#if defined(__aeon__) || defined(__mips__) || defined(__i686__)
extern u32 mae_swprintf( u16 *zBuf, int nCount, const u16 *pFormat, ...);
#define  ven_std_swprintf      mae_swprintf
#else //__aeon__
#define  ven_std_swprintf      swprintf
#endif //__aeon__
#define  ven_std_swscanf       swscanf
#define  ven_std_wstrstr       sysUtil_UCS2StrStr
#define	 ven_std_memchr		   memchr
#define  ven_std_vsnprintf	   _vsnprintf
#define  ven_std_snprintf	   _snprintf

#define  ven_std_itoa          vm_itoa
#define  ven_std_atoi          atoi
#define  ven_std_isascii       vm_isascii
#define  ven_std_isdigit       isdigit

#define  ven_std_atof          atof

/**
 *  s32 ven_std_rand(void);
 *  @brief  Generate random number
 *
 *  @param  None
 *
 *  @retval A pseudo-random integral number
 */
#define  ven_std_rand          ven_util_rand

/**
 *  void ven_std_srand(u32 seed);
 *  @brief  Initialize random number generator
 *
 *  @param  seed          [in]An integer value to be used as seed by the pseudo-random number generator algorithm.
 *
 *  @retval None
 */
#define  ven_std_srand         ven_util_srand

/**
 *  void ven_std_srandByTime(void);
 *  @brief  Initialize random number generator by system clock time
 *
 *  @param  None
 *
 *  @retval None
 */
#define  ven_std_srandByTime   ven_util_srandByTime

/**
 *  void ven_std_randGetInteger(u32 nFrom, u32 nTo);
 *  @brief  Get a random integer in a range [nFrom, nTo] inclusive
 *
 *  @param  nFrom        [in]Begin range
 *  @param  nTo          [in]End range
 *
 *  @retval A pseudo-random integral number
 */
#define  ven_std_randGetInteger   ven_util_randGetInteger

/**
 *  u16 ven_std_tolower(u16 nCh);
 *  @brief  Convert nCh to lower case
 *
 *  @param  nCh             [in]WChar witch want to convert to lower case
 *
 *  @retval The lower case of nChar
 */
#define  ven_std_tolower          mae_tolower

/**
 *  u16 ven_std_toupper(u16 nCh);
 *  @brief  Convert nCh to upper case
 *
 *  @param  nCh             [in]WChar witch want to convert to upper case
 *
 *  @retval The lower case of upper
 */
#define  ven_std_toupper          mae_toupper

#endif /* __VEN_STD_H__ */
