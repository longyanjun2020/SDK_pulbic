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
* @file    mmi_networkapp_custom.h
* @version
* @brief   Network setting applet custom header file
*
*/

#ifndef __MMI_NETWORKAPP_CUSTOM_H__
#define __MMI_NETWORKAPP_CUSTOM_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Extern definition
/*=============================================================*/
#ifdef __BAND_SELECTION_MMI__
#define NETWORKAPP_CFG_ALLOW_BAND_SELECT    TRUE  //Set "FALSE" to enable band selection UI.
#else
#define NETWORKAPP_CFG_ALLOW_BAND_SELECT    FALSE  //Set "FALSE" to disable band selection UI.
#endif
#ifdef __GPRS_MMI__
/* For PR: 60463, this interface is temporarily removed, so set to FALSE. */
#define NETWORKAPP_ALLOW_NET_ACCESS_SELECT  FALSE  // Set "TRUE" to enable net access interface.
#endif //__GPRS_MMI__
/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

#endif /* __MMI_NETWORKAPP_CUSTOM_H__ */
