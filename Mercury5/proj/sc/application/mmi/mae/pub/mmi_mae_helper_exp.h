/**
 * \file    mmi_mae_helper_exp.h
 * \brief   The document describes the private data structure used in mae_display_base.c
 *
 * @version
 */

#ifndef __MMI_MAE_HELPER_EXP_H__
#define __MMI_MAE_HELPER_EXP_H__
#include "mmi_mae_common_def.h"


void HELPER_UTF8ToUCS2(u8 *pUTF8, u16 nUTF8Bytes, u16 *pUCS2Out, u16 *pBytesWritten);

void HELPER_UCS2ToUTF8(u16 *pUCS2, u16 nLen, u8 *pUTF8Out, u16 *pBytesWritten);
/*
Compare characters of two strings without regard to case.

The characters from 91 to 96 in the ASCII table ('[', '\', ']', '^', '_', and '`') will evaluate as less than any alphabetic character. This ordering is identical to that of stricmp.

*/
s16 HELPER_strnicmp(const char *pStr1, const char *pStr2, size_t nSize);

/*
@brief strrstr - locate a substring

Synopsis

char* strrstr(const char* pHaystack, const char* pNeedle);

Description

The strrstr() function finds the last occurrence of the substring pNeedle in the string pHaystack. The terminating '\0' characters are not compared.

@return 	The strrstr() function returns a pointer to the beginning of the substring, or NULL if the substring is not found or one of pHaystack and pNeedle is NULL.

*/

char* HELPER_strrstr(const char* pHaystack, const char* pNeedle);

/**
 * @brief  HELPER_UTF8Strlen : get the number of UCS2 chars for the specified UTF8 string
 * @param   pUTF8   utf8 string
 * @param   nCharNum   number of bytes of utf8 string.
 * @retval   Number of UCS2 characters.
 */
u32 HELPER_UTF8Strlen(u8 *pUTF8, u32 nCharNum);


#endif //__MAE_HELPER_EXP_H__
