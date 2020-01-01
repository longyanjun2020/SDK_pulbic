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
* @file    : app_mgr.h
* @version :
* @author  : CA.Wang
* @brief   : Manage all post-processing IPs.
*/

#ifndef __APP_MGR_H__
#define __APP_MGR_H__

/*============================================================================*/
// Include Files
/*============================================================================*/
#include "app_mgr_interface.h"
#include "app_datatype.h"

// include IPs
#if defined(ENABLE_TIME_STRETCH)
#include "time_stretch.h"
#endif

#if defined(ENABLE_TIMEPITCH_STRETCH)
#include "timepitch_stretch.h"
#endif

#if defined(ENABLE_3D_SURROUND)
#include "mstarsurround.h"
#endif

#if defined(ENABLE_USER_PEQ) || defined(ENABLE_SPEAKER_PEQ)
#include "p_eq.h"
#endif

#if defined(ENABLE_BIG3HW_GEQ) || defined(ENABLE_G1HW_GEQ)
#include "hw_g_eq.h"
#endif

#if defined(ENABLE_BIG3HW_PEQ) || defined(ENABLE_G1HW_PEQ)
#include "hw_p_eq.h"
#endif

#if defined(ENABLE_VOL_CONTROL_EXP)
#include "exp_vol.h"
#endif

#if defined(ENABLE_DRC_LIMITER)
#include "drc_limiter.h"
#endif

#if defined(ENABLE_DRC_LIMITER_V2)
#include "drc_limiter_v2.h"
#endif

#if defined(ENABLE_LOOKAHEAD_DRC_LIMITER)
#include "drclookahead_limiter.h"
#endif

#if defined (ENABLE_HARD_LIMITER)
#include "hard_limiter.h"
#endif

#if defined (ENABLE_BIG3HW_DRC) || defined(ENABLE_G1HW_DRC)
#include "hw_drc.h"
#endif

#if defined (ENABLE_SC_FADE)
#include "sc_fade.h"
#endif

#if defined(ENABLE_DM2)
#include "dm2.h"
#endif

#if defined(ENABLE_REVERB)
#include "reverb.h"
#endif

#if defined(ENABLE_BASS)
#include "bass.h"
#endif

#if defined(ENABLE_SRSWOWHD)
#include "srswowhd.h"
#endif

/*============================================================================*/
// Function Define
/*============================================================================*/
/*---------------- Print Message Switch -----------------*/
#define ENABLE_POSTPROC_MGR_PARSER_PRINTF

/*---------- Sub-frame sample count per channel ---------*/
#define SUBFRAME_ALIG_BITS  (5)
#define SUBFRAME_ALIG_SIZE  (1 << SUBFRAME_ALIG_BITS)                // 1   << 5  = 32
#define SUBFRAME_NORM_SIZE  (SUBFRAME_ALIG_SIZE << 3)                // 32  << 3  = 256
#define SUBFRAME_EXT_SIZE   (SUBFRAME_NORM_SIZE >> 1)                // 256 >> 1  = 128
#define SUBFRAME_MAX_SIZE   (SUBFRAME_NORM_SIZE + SUBFRAME_EXT_SIZE) // 256 + 128 = 384

/*============================================================================*/
// Data type definition
/*============================================================================*/
/*--------------- IP paramater structure ----------------*/
typedef struct
{
   tS32 InValidData;
   tBOOL bMainEnable;
   tU8  u8SLDLM_ON;
   tU8  u8SRSSLDLM_ON;

   #if defined(ENABLE_TIME_STRETCH)
   M_TIME_STRETCH_PAR_s time_stretch_set;
   #endif

   #if defined(ENABLE_TIMEPITCH_STRETCH)
   M_TIMEPITCH_STRETCH_PAR_s timepitch_stretch_set;
   #endif

   #if defined(ENABLE_3D_SURROUND)
   M_MSTARSURROUND_PAR_s surround_set;
   #endif

   #if defined(ENABLE_USER_PEQ)
   M_PEQ_PAR_s usr_peq_set;
   #endif

   #if defined(ENABLE_BIG3HW_GEQ)
   M_HWGEQ_PAR_s big3hw_geq_set;
   #endif

   #if defined(ENABLE_G1HW_GEQ)
   M_HWGEQ_PAR_s g1hw_geq_set;
   #endif

   #if defined(ENABLE_SPEAKER_PEQ)
   M_PEQ_PAR_s spk_peq_set;
   #endif

   #if defined(ENABLE_BIG3HW_PEQ)
   M_HWPEQ_PAR_s big3hw_peq_set;
   #endif

   #if defined(ENABLE_G1HW_PEQ)
   M_HWPEQ_PAR_s g1hw_peq_set;
   #endif

   #if defined(ENABLE_VOL_CONTROL_EXP)
   M_VOL_EXP_PAR_s vol_exp_set;
   #endif

   #if defined(ENABLE_DRC_LIMITER)
   M_DRC_LIMITER_PAR_s drc_limiter_set;
   #endif

   #if defined(ENABLE_DRC_LIMITER_V2)
   M_DRC_LIMITER_V2_PAR_s drc_limiter_v2_set;
   #endif

   #if defined(ENABLE_LOOKAHEAD_DRC_LIMITER)
   M_DRCLOOKAHEAD_LIMITER_PAR_s drclookahead_limiter_set;
   #endif

   #if defined(ENABLE_HARD_LIMITER)
   M_HARD_LIMITER_PAR_s hard_limiter_set;
   #endif

   #if defined(ENABLE_BIG3HW_DRC)
   M_HWDRC_PAR_s big3hw_drc_set;
   #endif

   #if defined(ENABLE_G1HW_DRC)
   M_HWDRC_PAR_s g1hw_drc_set;
   #endif

   #if defined(ENABLE_SC_FADE)
   M_FADER_PAR_s fading_set;
   #endif

   #if defined(ENABLE_DM2)
   M_DM2_PAR_s dm2_set;
   #endif

   #if defined(ENABLE_REVERB)
   STR_SETREVERB reverb_set;
   #endif

   #if defined(ENABLE_BASS)
   STR_SETBASS bass_set;
   #endif

   #if defined(ENABLE_SRSWOWHD)
   	M_WOWHD_PAR_s wowhd_set;
   #endif

}M_POSTPROC_SETTING_STRC ;

/*------------------ IP Main structure ------------------*/
typedef struct
{
   tS32 InValidData;
   //tBOOL bMainEnable;
   // IPs
   #if defined(ENABLE_TIME_STRETCH)
   M_TIME_STRETCH_MAIN_s time_stretch_main_ip;
   #endif


   #if defined(ENABLE_TIMEPITCH_STRETCH)
   M_TIMEPITCH_STRETCH_MAIN_s timepitch_stretch_main_ip;
   #endif

   #if defined(ENABLE_3D_SURROUND)
   M_MSTARSURROUND_MAIN_s surround_main_ip;
   #endif

   #if defined(ENABLE_USER_PEQ)
   M_PEQ_MAIN_s usr_peq_main_ip;
   #endif

   #if defined(ENABLE_BIG3HW_GEQ)
   M_HWGEQ_MAIN_s big3hw_geq_main_ip;
   #endif

   #if defined(ENABLE_G1HW_GEQ)
   M_HWGEQ_MAIN_s g1hw_geq_main_ip;
   #endif

   #if defined(ENABLE_SPEAKER_PEQ)
   M_PEQ_MAIN_s spk_peq_main_ip;
   #endif

   #if defined(ENABLE_BIG3HW_PEQ)
   M_HWPEQ_MAIN_s big3hw_peq_main_ip;
   #endif

   #if defined(ENABLE_G1HW_PEQ)
   M_HWPEQ_MAIN_s g1hw_peq_main_ip;
   #endif

   #if defined(ENABLE_VOL_CONTROL_EXP)
   M_VOL_EXP_MAIN_s vol_control_exp_ip;
   #endif

   #if defined(ENABLE_DRC_LIMITER)
   M_DRC_LIMITER_MAIN_s drc_limiter_main_ip;
   #endif

   #if defined(ENABLE_DRC_LIMITER_V2)
   M_DRC_LIMITER_V2_MAIN_s drc_limiter_v2_main_ip;
   #endif

   #if defined(ENABLE_LOOKAHEAD_DRC_LIMITER)
   M_DRCLOOKAHEAD_LIMITER_MAIN_s drclookahead_limiter_main_ip;
   #endif

   #if defined(ENABLE_HARD_LIMITER)
   M_HARD_LIMITER_MAIN_s hard_limiter_main_ip;
   #endif

   #if defined(ENABLE_BIG3HW_DRC)
   M_HWDRC_MAIN_s big3hw_drc_main_ip;
   #endif

   #if defined(ENABLE_G1HW_DRC)
   M_HWDRC_MAIN_s g1hw_drc_main_ip;
   #endif

   #if defined(ENABLE_SC_FADE)
   M_FADER_MAIN_s fading_main_ip;
   #endif

   #if defined(ENABLE_DM2)
   M_DM2_MAIN_s dm2_main_ip;
   #endif

   #if defined(ENABLE_REVERB)
   STR_REVERB reverb_main_ip;
   #endif

   #if defined(ENABLE_BASS)
   STR_BASS bass_main_ip;
   #endif

   #if defined(ENABLE_SRSWOWHD)
   M_WOWHD_MAIN_s wowhd_main_ip;
   #endif
}M_POSTPROC_MAIN_IP;

typedef struct
{
    tS8* wowhdobj_buf;
    tS8* cshpobj_buf;
    tU8* pu8mem;
    tS16* queue_buf;
}M_memcell;
typedef struct
{
	tS32 *Left;
	tS32 *Right;
} M_SRSStereoCh;


typedef struct
{
    tU8*  APP_MainProcBuf;

    #if defined(ENABLE_TIME_STRETCH)
    M_memcell time_stretch_mem;
    M_memcell time_stretch_IOmem;
    #endif

    #if defined(ENABLE_TIMEPITCH_STRETCH)
    M_memcell timepitch_stretch_mem;
    M_memcell timepitch_stretch_IOmem;
    #endif

    #if defined(ENABLE_REVERB)
    M_memcell reverb_mem;
    #endif

    #if defined(ENABLE_LOOKAHEAD_DRC_LIMITER)
    M_memcell lookahead_drc_limiter_mem;
    #endif

    #if defined(ENABLE_3D_SURROUND)
    M_memcell surround_mem;
    #endif

	#if defined(ENABLE_BASS)
    M_memcell bass_mem;
    #endif

    #if defined(ENABLE_SRSWOWHD)
    M_memcell wow_hd_mem;
    M_SRSStereoCh APP_SRSIO;
    #endif

}M_POSTPROC_MEMCTRL;



/*------------ Memory controller structure --------------*/
typedef struct
{
    tU8* pu8ProcBuf;
    tU32 u32ProcBufByte;
    tU32 u32ProcBufByteIdx;

    tU8* pu8CmdBuf;
    tU32 u3CmdBufByte;
    tU32 u3CmdBufByteIdx;
}M_POSTPROC_MEM_CONTROLLER;

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

#endif // __APP_MGR_H__

