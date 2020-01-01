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
 * @file    drv_fmrx.h
 * @brief   This module defines the audio Service Host Driver API layer of
 *          Enhanced Media Agent (EMA)
 */
#ifndef __DRV_FMRX_H__
#define __DRV_FMRX_H__

#include "drv_fmrx_mstar_pub.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define __FMRX_AT_TEST__ 0

/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/

#define     CSL_FMR_US_BAND_START   875030  /**< US FM band lower limit 87.5MHz */
#define     CSL_FMR_US_BAND_END     1081468 /**< US FM band upper limit 108.1MHz */
#define     CSL_FMR_JAP_BAND_START  760000  /**< Jap FM band lower limit 76MHz */
#define     CSL_FMR_JAP_BAND_END    910000  /**< Jap FM band upper limit 91MHz */

/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/



typedef enum
{
    CSL_FMR_POWER_OFF,
    CSL_FMR_POWER_ON,
} csl_FmrPower_e;

typedef enum
{
    CSL_FMR_MUTE_OFF,
    CSL_FMR_MUTE_ON,
} csl_FmrMute_e;

typedef enum
{
    CSL_FMR_STEREO_OFF,
    CSL_FMR_STEREO_ON,
} csl_FmrStereo_e;

typedef enum
{
    CSL_FMR_US_BAND, /**< U.S. FM band */
    CSL_FMR_JAP_BAND
/**< JAPAN FM band */
} csl_FmrBand_e;



typedef struct
{
    u32 version;
    u16 manufactrId;
    u16 chipId;
} csl_FmrChipInfo_t;



typedef struct
{
    bool (* pfnFMrxPower)(u8);
    bool (* pfnFMrxTune)(u32);
    bool (* pfnFMrxSeek)(u8, u8);
    bool (* pfnFMrxBand)(u8);
    bool (* pfnFMrxMute)(u8);
    bool (* pfnFMrxStereo)(u8);
    bool (* pfnFMrxVolumeControl)(u8 vol, u8 volext);
    bool (* pfnFMrxGetChanInfo)(u32 *, u16 *, u8 *);
    bool (* pfnFMrxGetChipInfo)(u32 *, u16 *, u16 *);
    bool (* pfnFMrxSetArea)(csl_FmrArea_e);
} csl_FmrFuncTbl_t;

/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/
// csl_FmrErrCode_e DrvFmrxGetChipInfo(csl_FmrChipInfo_t *pChipInfo); // TODO: not used
// csl_FmrErrCode_e DrvFmrxSetBand(csl_FmrBand_e band); // TODO: not used


#endif //#ifndef __DRV_FMRX_H__
