/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      fw_unicode.h
 *
 * DESCRIPTION
 *      MStar Framework unicode string functions. 
 *
 * HISTORY
 *      2008.05.01       Mickey Chiang         Initial Version
 *      2008.10.03       Jimmy Hsu             Restructure
 *                                          
 *----------------------------------------------------------------------------- 
 */
#ifndef FW_UNICODE_H
#define FW_UNICODE_H

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "fw_std.h"

/*------------------------------------------------------------------------------
    EXTERN definition
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Constant
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Variable
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
    Global Function
-------------------------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    S32 mfUniStrlen(const PU16 pu16Str);
    PU16 mfUniStrcpy(PU16 pu16Dst,const PU16 pu16Src);
    PU16 mfUniStrncpy(PU16 pu16Dst,const PU16 pu16Src,S32 s32Maxlen);
    PU16 mfUniStrcat(PU16 pu16Dst,const PU16 pu16Src);
    PU16 mfUniStrdup(const PU16 pu16Str);
    S32 mfUniStrcmp(const PU16 pu16Str1,const PU16 pu16Str2);
    S32 mfUniStrncmp(const PU16 pu16Str1,const PU16 pu16Str2,S32 s32Len);
    PU16 mfUniStrchr(const PU16 pu16Str,U16 u16C);
    PU16 mfUniStrrchr(const PU16 pu16Str,U16 u16C);
    PU16 mfUniStrstr(const PU16 pu16Str1,const PU16 pu16Str2);
#ifdef linux
    PU16 mfUniWcharToUCS2(const wchar_t *pwszStr);
#endif
    MVOID mfCharStrCastUniStr(PU16 pu16Dst, PS8 sSrc);
    PS8 mfUniStrCastCharStr(PU16 pu16Src);

    PS8 mfUniStr2CharStr(S32 s32CodePage, const PU16 pwszStr, PS8 *ppszStr);
    PU16 mfCharStr2UniStr(S32 s32CodePage, const PS8 pszStr, PU16 *ppwszStr);
    PS8 mfUniUCS2ToUTF8(PU16 pwszStr);

    S32 mfUniAtoi(const PU16 pwszStr);
    PU16 mfUniItoa(S32 s32Value, PU16 pwszStr, S32 s32Base);

    MVOID mfUniPrintf(const PS8 sFormat,...);
    S32 mfUniSprintf(PU16 pu16Buffer,const PS8 sFormat,...);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* FW_UNICODE_H */

