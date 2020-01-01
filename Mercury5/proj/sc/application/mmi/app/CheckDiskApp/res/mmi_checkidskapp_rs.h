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
* @file    mmi_checkdiskapp_rs.h
* @version
* @brief   CheckDisk applet RS header file
*
*/
#ifndef __MMI_CHECKDISKAPP_RS_H__
#define __MMI_CHECKDISKAPP_RS_H__

#include "mmi_rs_macro_struct.h"


#if defined(__PC_SIMULATOR__) && defined(__RS_USE_SCRIPT__)
//#ifdef __LCM_QVGA__ 
/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_checkdiskap.rs"
#include "mmi_rs_macro_val.h"
#include "mmi_checkdiskap.rs"
/*=============================================================*/
// Extern definition
/*=============================================================*/
//#endif

#else

//#ifdef __LCM_QVGA__ 
#include "mmi_checkdiskapp.rs"
/*=============================================================*/
// Macro definition
/*=============================================================*/
#endif 
/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif /* __MMI_CHECKDISKAPP_RS_H__ */

