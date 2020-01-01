////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
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
* @file    drv_mem_tester.h
* @version
* @brief   A memory tester
*
*/

#ifndef __DRV_MEM_TESTER_H__
#define __DRV_MEM_TESTER_H__

/*=============================================================*/
// Include files
/*=============================================================*/

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    MEM_TESTER_SUCCESS,
    MEM_TESTER_FAIL,
    MEM_TESTER_UNKNOW_HANDLE,
    MEM_TESTER_PARAM_INVALID,
    MEM_TESTER_PARAM_NULL,
    MEM_TESTER_NOT_STARTED,
    MEM_TESTER_NOT_FINISHED,
} MemTesterErrorno_e;

typedef enum
{
    E_MEM_EMI0,
    E_MEM_EMI1,
    E_MEM_EMI2,
    E_MEM_EMI3,
    E_MEM_IMI2,
    E_MEM_DMC,

    // aliases
    E_MEM_SDRAM = E_MEM_EMI0,
    E_MEM_PSRAM = E_MEM_EMI1,
} MemRegion_e;

typedef enum
{
    MEM_TEST_MODE_ADDR_TOGGLE = 0x00,
    MEM_TEST_MODE_TEST_DATA   = 0x01,
    MEM_TEST_MODE_SHIFT_DATA  = 0x02,
    MEM_TEST_MODE_BOTH_TOGGLE = 0x03,
    
    MEM_TEST_INVERSE_DATA     = 0x08,
    MEM_TEST_LOOP             = 0x10,
    MEM_TEST_READ_ONLY        = 0x10,
    MEM_TEST_WRITE_ONLY       = 0x20,
} MemTestMode_e;

#define MEM_TEST_MODE_MASK  	0x03

#define MEM_SIZE_FULL   		0xFFFFFFFF

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MemTesterErrorno_e DrvMemTestStart(MemRegion_e eRegion, MemTestMode_e eMode, u8 nMask, u32 nStartAddr, u32 nSize, u32 *pHandle);
MemTesterErrorno_e DrvMemTestStop(u32 nHanlde);
MemTesterErrorno_e DrvMemTestIsFinished(u32 nHandle);
MemTesterErrorno_e DrvMemTestGetResult(u32 nHandle);

#endif //__DRV_MEM_TESTER_H__
