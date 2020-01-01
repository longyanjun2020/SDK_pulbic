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
* @file    mmi_dialergroupapp.h
* @version $Id: mmi_dialergroupapp.h  $
* @brief   dialer group applet header file
*/

#ifndef __MMI_DIALERGROUPAPP_H__
#define __MMI_DIALERGROUPAPP_H__

/*Include*/

/*-------------------------------------------------------------------------*/

/*Definitions*/


/*Structure*/
typedef enum
{
    AP_TYPE_DIALER= 0,
    AP_TYPE_CALLLOG,
    AP_TYPE_PHB,
    AP_TYPE_FAVORITE_PHB
} AppType_e;

u32 nAPClassID[]= 
{
	CLSID_DIALERAPP,		CLSID_CALLLOGAPP,	CLSID_PHBAP,		CLSID_FAVORITEPHB,
};


MAE_Ret DialerGroupAppNew(MAE_ClsId id, void **ppObj);

#endif /* __MMI_DIALERGROUPAPP_H__ */
