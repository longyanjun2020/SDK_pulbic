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
* @brief   define the interfaces for 
*          communicating with applications
*          
*/

#ifndef __MMI_URI_P_H__
#define __MMI_URI_P_H__

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

/*=============================================================*/
// Function Declarations
/*=============================================================*/

__SLDPM_FREE__ URI_ErrCode_e URI_ParseIpFourAddress
(
  unsigned char *pchOctetOutput,
  const URI_CHAR *pchTextStart, 
  const URI_CHAR *pchAfterTextEnd
);

#endif/* __MMI_URI_P_H__ */
