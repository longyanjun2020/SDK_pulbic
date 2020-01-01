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
* @file    mdl_gps_pub.h
* @version
* @brief   mdl gps header file.
*
*/

#ifndef __MDL_GPS_PUB_H__
#define __MDL_GPS_PUB_H__

/*=============================================================*/
//  Includes Files
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
//  Local function definition
/*=============================================================*/

/*=============================================================*/
// Global Function definition
/*=============================================================*/
void MdlGpsTaskInit(void);
void MdlGpsTaskParser (void *pMessage);

#endif /* __MDL_GPS_PUB_H__ */

