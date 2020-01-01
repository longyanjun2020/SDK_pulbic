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
* @file    UriPort.h
* @brief   define porting interface  
*          for uriparser
*          
*/

#ifndef __MMI_URI_PORT_H__
#define __MMI_URI_PORT_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "mmi_UriType.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

void *URI_MALLOC(u32 uSize);
void *URI_MEMCPY(void *pvDst, const void *pvSrc, u32 uSize);
void URI_FREE(void *pvMem);
void URI_MEMSET(void *pvMem, s32 sValue, u32 uSize);

/*=============================================================*/
// Function Declarations
/*=============================================================*/

#endif/* __MMI_URI_PORT_H__ */
