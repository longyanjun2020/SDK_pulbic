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
* @file    UriCommon.h
* @brief   
*          
*          
*/

#ifndef __MMI_URI_COMMON_H__
#define __MMI_URI_COMMON_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UriType.h"
#include "mmi_UriParserExport.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

/*=============================================================*/
// Function Declarations
/*=============================================================*/

u8 URI_HexdigToInt
(
  URI_CHAR hexdig
);

void URI_ResetUri
(
  URI_Uri_t *pUri
);

void URI_FixEmptyTrailSegment
(
  URI_Uri_t *pUri
);

URI_BOOL URI_IsHostSet
(
  const URI_Uri_t *pUri
);

URI_CHAR URI_HexToLetter
(
  u32 uValue
);

URI_CHAR URI_HexToLetterEx
(
  u32 uValue, 
  URI_BOOL bUpperCase
);

const URI_CHAR *URI_UnescapeInPlaceEx
(
  URI_CHAR * inout,
  URI_BOOL bPlusToSpace, 
  URI_BreakConversion_e eBreakConversion
); 

URI_CHAR* URI_EscapeEx
(
  const URI_CHAR * inFirst,
  const URI_CHAR * inAfterLast, 
  URI_CHAR * out,
  URI_BOOL bSpaceToPlus, 
  URI_BOOL bNormalizeBreaks
); 
#endif/* __MMI_URI_COMMON_H__ */
