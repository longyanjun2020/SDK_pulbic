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
* @file    mmi_cdwapapp_interface.h
* @version
* @brief   CDWAP interface file
*
*/

#ifdef __WAP_MMI_CDWAP__

#ifndef __MMI_CDWAPAPP_INTERFACE_H__
#define __MMI_CDWAPAPP_INTERFACE_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_mae_common_def.h"
#include "mmi_clstbl.h"
#include "ven_primitem.h"
#include "ven_prim_msg.h"
#include "vm_msgt.ht"
#include "ven_os.h"
#include "ven_common_def.h"
#include "ven_stc_msgt.h"
#include "cus_msg.hc"
#include "mmi_if_def.h"
#include "mmi_cdwapapp.h"
#include "wap_comm.hi"

/*=============================================================*/
// Extern definition
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
// Global function definition
/*=============================================================*/

//void WapMMI_msg_parser( IBase* pRecipient, vm_msg_t *pMsg);

//MAE_Ret WapSendEVentToKernel(WapEvent *WapEvt);

#endif // #define __MMI_CDWAPAPP_INTERFACE_H__
#endif // __WAP_MMI_CDWAP__
