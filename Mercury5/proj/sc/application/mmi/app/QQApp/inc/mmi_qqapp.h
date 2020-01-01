////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

// User Code Begin:APP:INFO
// User Code End

#ifndef __MMI_QQAPP_H__
#define __MMI_QQAPP_H__

#ifdef __cplusplus
extern "C" {
#endif

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_srv_header.h"



/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition

/**
* External Events
*/
#define QQAPP_EVT_ACTIVE_QQ_APP                (CLSID_QQAPP << 16 | 1)
#define QQAPP_EVT_SHOW_DUALSIM_MENU            (CLSID_QQAPP << 16 | 33)

/*=============================================================*/
// Global function definition
/*=============================================================*/
/** QQAppNew
* @brief        New function for create QQApp Applet

* @param[in]    nClsId              QQApp class id
* @param[in]    ppObj               The pointer of pointer of Applet

* @retval       MAE_RET_SUCCESS     Success.
* @retval       other               Fail

*/
MAE_Ret QQAppNew
(
    MAE_ClsId   nClsId,
    void    **ppObj
);

void QQApp_FocusedOnEditor(void *pApplet, MAE_EventId evt, u32 keycode);

#ifdef __cplusplus
}
#endif

#endif /* __MMI_QQAPP_H__ */

