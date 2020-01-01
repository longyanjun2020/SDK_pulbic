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
* @file    : arp_mgr.h
* @version :
* @author  : CA.Wang
* @brief   : Manage all pre-processing IPs.
*/

#ifndef __ARP_MGR_H__
#define __ARP_MGR_H__

/*============================================================================*/
// Include Files
/*============================================================================*/
#include "arp_mgr_interface.h"
#include "arp_datatype.h"

// include IPs
#if defined(ARP_SW_GAINCTR_ENABLE)
#include "arp_exp_vol.h"
#endif

#if defined(ARP_BIG3HW_AGC_ENABLE) || defined(ARP_G1HW_AGC_ENABLE)
#include "arp_hw_agc.h"
#endif

#if defined(ARP_SW_AGC_ENABLE)
#include "arp_sw_agc.h"
#endif

/*============================================================================*/
// Function Define
/*============================================================================*/
/*---------------- Print Message Switch -----------------*/
#define ENABLE_ARP_MGR_PARSER_PRINTF

/*---------- Sub-frame sample count per channel ---------*/
#define ARP_SUBFRAME_ALIG_BITS  (5)
#define ARP_SUBFRAME_ALIG_SIZE  (1 << ARP_SUBFRAME_ALIG_BITS)                // 1   << 5  = 32
#define ARP_SUBFRAME_NORM_SIZE  (ARP_SUBFRAME_ALIG_SIZE << 3)                // 32  << 3  = 256
#define ARP_SUBFRAME_EXT_SIZE   (ARP_SUBFRAME_NORM_SIZE >> 1)                // 256 >> 1  = 128
#define ARP_SUBFRAME_MAX_SIZE   (ARP_SUBFRAME_NORM_SIZE + ARP_SUBFRAME_EXT_SIZE) // 256 + 128 = 384

/*============================================================================*/
// Data type definition
/*============================================================================*/
/*--------------- IP paramater structure ----------------*/
typedef struct
{
   tS32 InValidData;
   tBOOL bMainEnable;

   #if defined(ARP_SW_GAINCTR_ENABLE)
   ARP_EXPVOL_PAR_s vol_exp_set;
   #endif

   #if defined(ARP_BIG3HW_AGC_ENABLE)
   ARP_HWAGC_PAR_s big3hw_agc_set;
   #endif

   #if defined(ARP_G1HW_AGC_ENABLE)
   ARP_HWAGC_PAR_s g1hw_agc_set;
   #endif

   #if defined(ARP_SW_AGC_ENABLE)
   ARP_SWAGC_PAR_s sw_agc_set;
   #endif

}ARP_SETTING_STRC_s;

/*------------------ IP Main structure ------------------*/
typedef struct
{
   tS32 InValidData;

   #if defined(ARP_SW_GAINCTR_ENABLE)
   ARP_EXPVOL_MAIN_s vol_control_exp_ip;
   #endif

   #if defined(ARP_BIG3HW_AGC_ENABLE)
   ARP_HWAGC_MAIN_s big3hw_agc_main_ip;
   #endif

   #if defined(ARP_G1HW_AGC_ENABLE)
   ARP_HWAGC_MAIN_s g1hw_agc_main_ip;
   #endif

    #if defined(ARP_SW_AGC_ENABLE)
   ARP_SWAGC_MAIN_s sw_agc_main_ip;
    #endif

}ARP_MAIN_IP_s;

/*------------ Memory controller structure --------------*/
typedef struct
{
    tU8* pu8ProcBuf;
    tU32 u32ProcBufByte;
    tU32 u32ProcBufByteIdx;

    tU8* pu8CmdBuf;
    tU32 u3CmdBufByte;
    tU32 u3CmdBufByteIdx;
}ARP_MEM_CONTROLLER_s;

/*============================================================================*/
// Variable definition
/*============================================================================*/
//...

/*============================================================================*/
// Global function definition
/*============================================================================*/
#ifdef __cplusplus
extern "C"
{
#endif
//...
#ifdef __cplusplus
}
#endif

#endif // __ARP_MGR_H__

