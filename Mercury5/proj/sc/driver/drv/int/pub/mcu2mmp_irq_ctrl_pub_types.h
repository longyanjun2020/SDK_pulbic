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
* @file    mcu2mmp_irq_ctrl_pub_types.h
* @version
* @brief   System interrupt controller (INTC) header file
*
*/
#if defined (__UPGRADE_SHARE_MEMORY__)
#ifndef __MCU2MMP_IRQ_CTRL_PUB_TYPES_H__
#define __MCU2MMP_IRQ_CTRL_PUB_TYPES_H__

#include "vm_types.ht"
#include "mcu2mmp_irq_ctrl_pub_forward.h"

/** CSQ data type */
struct AtCsqData_
{
  u8  receiveQuality;
  u8  receiveLevel;
};

/** CREG data type */
struct AtCregData_
{
  u8    accessTechnology;  
  u8    state;
  u16   lac;
  u32   cellId;
};

/** CGREG data type */
struct AtCgregData_
{
  u8    accessTechnology;  
  u8    state;
  u16   lac;
  u32   cellId;
};

/** Command Type */
opaque_enum(CmdType_)
{
  CSQ_CMD     =0,
  CREG_CMD    =1,
  CGREG_CMD   =2,
  INVALID_CMD =3
};

/** AT data*/
union UnionAtData_
{
  AtCsqData    csqData;
  AtCregData   cregData;
  AtCgregData  cgregData;
};

/* Data and Type*/
struct AtDataType_
{
  CmdType      cmdType;
  UnionAtData  atData;
};

#endif // __MCU2MMP_IRQ_CTRL_PUB_TYPES_H__

#endif /*__UPGRADE_SHARE_MEMORY__*/

