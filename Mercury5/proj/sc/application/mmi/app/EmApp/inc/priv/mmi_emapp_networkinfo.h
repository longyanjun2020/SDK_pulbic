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
* @file mmi_emapp_networkinfo.h
*
* @version $Id: mmi_em_networkinfo.h 18124 2008-12-11 15:42:54Z eric.chen $
*/

#ifndef __MMI_EMAPP_NETWORKINFO_H__
#define __MMI_EMAPP_NETWORKINFO_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_emapp_priv.h"

/*=============================================================*/
// Global function definition
/*=============================================================*/
u32 em_request_network_CE               (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
EmAppResRet_e em_response_network_CE    (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
u32 em_exit_network_CE                  (EmAppData_t *pThis, u32 param1);
u32 em_request_network_SC               (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
EmAppResRet_e em_response_network_SC    (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
u32 em_exit_network_SC                  (EmAppData_t *pThis, u32 param1);

u32 em_request_band                     (EmAppData_t *pThis, u32 param1, u32 param2, u32 Output);
EmAppResRet_e em_response_band          (EmAppData_t *pThis, u32 param1, EmAppEventInfo_t *pEventInfo, u32 Output);
u32 em_exit_band                        (EmAppData_t *pThis, u32 param1);

#endif//__MMI_EMAPP_NETWORKINFO_H__
