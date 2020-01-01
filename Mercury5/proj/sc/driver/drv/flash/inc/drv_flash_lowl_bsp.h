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
* @file    drv_flash_lowl_bsp.h
* @version
* @brief   Flash Memory Services - Board support definitions
*
*/

#ifndef __DRV_FLASH_LOWL_BSP_H__
#define __DRV_FLASH_LOWL_BSP_H__

/*=============================================================*/
// Include files
/*=============================================================*/

#include "kernel.h"
#ifdef __FPGA__
#include "drv_timer_types.h"
#include "drv_timer_api.h"
#endif

/*=============================================================*/
// Extern definition
/*=============================================================*/

//MST_CR_7899: prvent fetch data from flash during erasure
extern u32 *pnQbCntAddr;
//MST_CR_7899: prvent fetch data from flash during erasure

/*=============================================================*/
// Macro definition
/*=============================================================*/

/****************************************************************************/
/*                                                                          */
/*   COMMON SYSTEM INLINE FUNCTIONS                                         */
/*                                                                          */
/****************************************************************************/
/* Read TBU_QBCNT_REG */
// Be careful, the address can change

//MST_CR_7899: prvent fetch data from flash during erasure
#ifdef __FPGA__
#define DrvFlashLowLevelGetQbCnt() DrvTimerStdaTimerGetTick()
#else
#define DrvFlashLowLevelGetQbCnt() (*pnQbCntAddr)
#endif
//MST_CR_7899: prvent fetch data from flash during erasure

//#define DrvFlashLowLevelGetQbCnt() (*(volatile u16*)(TBU_BASE_ADD + MAIN_OFFSET+0x114+8)) //(g_ptW5TbuC->u16_QbCnt)

/****************************************************************************/
/* ERASE PROCESS INTERRUPTIONS MONITORING UTILITIES                         */
/****************************************************************************/

/*
 * Usage:
 * DRV_FLASH_ERASE_MONITOR_INIT at the beginning of the erase function
 * DRV_FLASH_ERASE_MONITOR_LEAVENOW is true when a suspend operation is needed
 * DRV_FLASH_ERASE_MONITOR_RELOAD to refresh some parameters (current time, etc...)
 */
#define DRV_FLASH_ERASE_MONITOR_INIT(_VALUE_) u32 nQbCntBackupValue = DrvFlashLowLevelGetQbCnt(); \
                                              u32 nQbCntValue; \
                                              u32 nIterationCnt = _VALUE_; \
                                              if(50 > nQbCntBackupValue) { return FLASH_RETRY; }

   /* a FINT is generated when QbCNT is reset */
   /* For WHAT2: If QBCNT has reached the reset value
    * (FRAME_CLK register) and has rolled over from 
    * 0x0000 or if the iteration count is elapsed */
                                          
#define DRV_FLASH_ERASE_MONITOR_LEAVENOW   (( nQbCntBackupValue > ( nQbCntValue = DrvFlashLowLevelGetQbCnt() ) )\
                                           || ( 0 == (--nIterationCnt) ))

/* Save QBCNT value for the next check iteration */
#define DRV_FLASH_ERASE_MONITOR_RELOAD        nQbCntBackupValue = nQbCntValue
   

#endif //__DRV_FLASH_LOWL_BSP_H__ 

