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
* @file    mcu2mmp_irq_ctrl_pub_api.h
* @version
* @brief   System interrupt controller (INTC) header file
*
*/
#if defined (__UPGRADE_SHARE_MEMORY__)

#ifndef __MCU2MMP_IRQ_CTRL_PUB_API_H__
#define __MCU2MMP_IRQ_CTRL_PUB_API_H__

#include "vm_types.ht"
#include "mcu2mmp_irq_ctrl_pub_forward.h"

#include "shmconn_typ.h"
#include "mux_shrd.h"

#if defined (__UPGRADE_NVRAM__) 
#include <mdl_gpd_pub.h>
#endif /*__UPGRADE_NVRAM__*/

extern void ShmMailboxInterrupt(void);
extern void ShmMailboxInterruptDsp(void);
extern MailboxStatus DriReturnMailboxStatus(TypeOfMailbox mailbox);
extern void DriInitShareMemory(ShareMemoryInitType type);
extern void DriSetMailboxEmpty(TypeOfMailbox mailbox);
extern void DriSendMuxFrameData(MuxFrame txMuxFrame);
extern void DriInformtoFreeData(u8 *dataAddress);  
extern void DriInitiateIrqsInt(void);
#if defined (__UPGRADE_NVRAM__) 
extern void DriSendAnrmUpdateRsp(MdlGpdNvramType_e dataType,bool updateStatus);
#endif /*__UPGRADE_NVRAM__*/
#if defined (__UPGRADE_GENIE_OVER_SHMCONN__)  
extern void DriInformSendTraceInd(void);
extern void DriInformRxDataInd(u32 dataLen, u8* dataAddr);
#endif

#endif // __MCU2MMP_IRQ_CTRL_PUB_API_H__

#endif /*__UPGRADE_SHARE_MEMORY__*/

