////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


/**
* @file    UriType.h
* @brief   define the basic type for uri parser
*          
*          
*/
#ifndef __MMI_URI_TYPE_H__
#define __MMI_URI_TYPE_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UrlSrvConfig.h"
#include "mmi_mae_helper.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

#undef URI_CHAR
#undef URI_STRLEN
#undef URI_STRCPY
#undef URI_STRCMP
#undef URI_STRNCMP
#undef URI_SNPRINTF
#undef URI_T
#undef URI_TRUE
#undef URI_FALSE

/// if define __URI_USE_UNICODE__ to use unicode
/// else use ascii code
typedef int URI_BOOL;

#ifdef _MAE_WCHAR_
#define URI_CHAR     MAE_WChar
#define URI_STRLEN   mae_wstrlen
#define URI_STRCPY   mae_wstrcpy
#define URI_STRCMP   mae_wstrcmp
#define URI_STRNCMP  mae_wstrncmp
#define URI_SNPRINTF mae_swprintf
#define URI_T(T)     L##T
#else
#ifdef __URI_USE_UNICODE__
#define URI_CHAR     wchar_t
#define URI_STRLEN   wcslen
#define URI_STRCPY   wcscpy
#define URI_STRCMP   wcscmp
#define URI_STRNCMP  wcsncmp
#define URI_SNPRINTF swprintf
#define URI_T(T)     L##T
#else
#define URI_CHAR     char
#define URI_STRLEN   strlen
#define URI_STRCPY   strcpy
#define URI_STRCMP   strcmp
#define URI_STRNCMP  strncpy
#define URI_SNPRINTF snprintf
#define URI_T(T) T
#endif/* __URI_USE_UNICODE_ */
#endif/* __MAE_WCHAR_ */



#define URI_TRUE     1
#define URI_FALSE    0

/*=============================================================*/
// Type Declarations
/*=============================================================*/




typedef enum
{
	URI_ERROR_SUCCESS = 0,
	URI_ERROR_SYNTAX,
	URI_ERROR_PARAM_NULL,
	URI_ERROR_NOT_ENOUGH_MEMORY,
	URI_ERROR_OUTPUT_TOO_LARGE,
	URI_ERROR_TOSTRING_TOO_LONG = URI_ERROR_OUTPUT_TOO_LARGE,
	URI_ERROR_ADDBASE_REL_BASE,
    URI_ERROR_REMOVEBASE_REL_BASE,
    URI_ERROR_REMOVEBASE_REL_SOURCE,
	URI_ERROR_NOT_SUPPORT,
	URI_ERROR_RANGE_INVALID,
    URI_ERROR_NUM,
    URI_ERROR_INVALID,
}URI_ErrCode_e;

typedef enum
{
	URI_BR_TO_LF,                       /// Convert to Unix line breaks "\\x0a"
	URI_BR_TO_CRLF,                     /// Convert to Windows line breaks "\\x0d\\x0a"
	URI_BR_TO_CR,                       /// Convert to Macintosh line breaks "\\x0d"
	URI_BR_TO_UNIX = URI_BR_TO_LF,      /// UriBreakConversionEnum URI_BR_TO_LF 
	URI_BR_TO_WINDOWS = URI_BR_TO_CRLF, /// UriBreakConversionEnum URI_BR_TO_CRLF
	URI_BR_TO_MAC = URI_BR_TO_CR,       /// UriBreakConversionEnum URI_BR_TO_CR
	URI_BR_DONT_TOUCH                   /// line breaks unmodified
}URI_BreakConversion_e;


/**
 * Specifies which component of a %URI has to be normalized.
 */
typedef enum
{
	URI_NORMALIZED = 0,	              /// Do not normalize anything 
	URI_NORMALIZE_SCHEME = 1 << 0,    /// Normalize scheme (fix uppercase letters) 
	URI_NORMALIZE_USER_INFO = 1 << 1, /// Normalize user info (fix uppercase percent-encodings) 
	URI_NORMALIZE_HOST = 1 << 2,      /// Normalize host (fix uppercase letters)
	URI_NORMALIZE_PATH = 1 << 3,      /// Normalize path (fix uppercase percent-encodings and redundant dot segments)
	URI_NORMALIZE_QUERY = 1 << 4,     /// Normalize query (fix uppercase percent-encodings)
	URI_NORMALIZE_FRAGMENT = 1 << 5   /// Normalize fragment (fix uppercase percent-encodings)
}URI_NormalizeMask_e; 

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif/* __MMI_URI_TYPE_H__ */
