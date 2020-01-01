////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (!¡±MStar Confidential Information!¡L) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    drv_fmrx_mstar_pub.h
* @version
* @brief   FMRX UDI head file
*
*/

#ifndef __DRV_FMRX_MSTAR_PUB_H__
#define __DRV_FMRX_MSTAR_PUB_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*=============================================================*/
// Include files
/*=============================================================*/
#include "vm_types.ht"

//#include "drv_fmrx.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/


/*=============================================================*/
// Macro definition
/*=============================================================*/
#define __FM_STEREO_AUTO

/*=============================================================*/
// Data type definition
/*=============================================================*/
/**
 * @brief   return error code
 */
typedef enum
{
    DRV_FMRX_OK = 0,
    DRV_FMRX_FAIL,
    DRV_FMRX_INVALID_PARAM,
} DrvFmrxRetCode_e;

/**
 * @brief   frequency band of FM radio
 */
typedef enum
{
    DRV_FMRX_AREA_INVALID = -1,
    DRV_FMRX_AREA_TAIWAN = 0,
    DRV_FMRX_AREA_CHINA,
} DrvFmrxArea_e;

/**
 * @brief   search channel direction
 */
typedef enum
{
    DRV_FMRX_SEARCH_DIR_DOWN = 0,
    DRV_FMRX_SEARCH_DIR_UP,
} DrvFmrxSearchDir_e;

/**
 * @brief   mute/un-mute
 */
typedef enum
{
    DRV_FMRX_UNMUTE = 0,
    DRV_FMRX_MUTE,
} DrvFmrxMute_e;

/**
 * @brief   mono/stereo
 */
typedef enum
{
    DRV_FMRX_MONO = 0,
    DRV_FMRX_STEREO,
} DrvFmrxStereo_e;

typedef struct
{
    u32 freq; /**< channel frequency */
    u16 RSSI; /**< Signal strength of current channel */
    u8 stereo; /**< Stereo/Mono status of current channel */
} csl_FmrChanInfo_t;

typedef enum
{
    CSL_FMR_OK,
    CSL_FMR_FAIL,
    CSL_FMR_REJECT,
    CSL_FMR_SEEK_FAIL
} csl_FmrErrCode_e;

typedef enum
{
    CSL_FMR_AREA_TAIWAN, /**< TAIWAN FM area */
    CSL_FMR_AREA_CHINA
/**< CHINA FM area */
} csl_FmrArea_e;
/*=============================================================*/
// Variable definition
/*=============================================================*/


/*=============================================================*/
// Global function definition
/*=============================================================*/

/**
 *
 * @fn          DrvFmrxRetCode_e DrvFmrxMstarPowerOnOff(bool bOn);
 * @brief       power on/off FMRX module
 * @param       bOn [in]    power on/off
 * @retval      DrvFmrxRetCode_e error code
 *
 */
DrvFmrxRetCode_e DrvFmrxMstarPowerOnOff(bool bOn);


/**
 *
 * @fn          DrvFmrxRetCode_e DrvFmrxMstarGetRssi(s32 *ps32Rssi);
 * @brief       get RSSI
 * @param       ps32Rssi [out]  RSSI
 * @retval      DrvFmrxRetCode_e error code
 *
 */
DrvFmrxRetCode_e DrvFmrxMstarGetRssi(s32 *ps32Rssi);


/**
 *
 * @fn          DrvFmrxRetCode_e DrvFmrxMstarSearchChannel(DrvFmrxSearchDir_e eSearchDir, u32 *pu32Freq);
 * @brief       search channel
 * @param       eSearchDir [in] channel search direction (up/down)
 * @param       pu32Freq [out]  frequency found (MHz/20)
 * @retval      DrvFmrxRetCode_e error code
 *
 */
DrvFmrxRetCode_e DrvFmrxMstarSearchChannel(DrvFmrxSearchDir_e eSearchDir, u32 *pu32Freq);


/**
 *
 * @fn          DrvFmrxRetCode_e DrvFmrxMstarSetArea(DrvFmrxArea_e eArea);
 * @brief       set area
 * @param       eArea [in]  frequency band of FM radio
 * @retval      DrvFmrxRetCode_e error code
 *
 */
DrvFmrxRetCode_e DrvFmrxMstarSetArea(DrvFmrxArea_e eArea);


/**
 *
 * @fn          DrvFmrxRetCode_e DrvFmrxMstarGetArea(DrvFmrxArea_e *peArea);
 * @brief       set area
 * @param       peArea [out]  frequency band of FM radio
 * @retval      DrvFmrxRetCode_e error code
 *
 */
DrvFmrxRetCode_e DrvFmrxMstarGetArea(DrvFmrxArea_e *peArea);


/**
 *
 * @fn          DrvFmrxRetCode_e DrvFmrxMstarSetFrequency(u32 u32Freq);
 * @brief       set frequency
 * @param       u32Freq [in]    frequency (MHz/20)
 * @retval      DrvFmrxRetCode_e error code
 *
 */
DrvFmrxRetCode_e DrvFmrxMstarSetFrequency(u32 u32Freq);


/**
 *
 * @fn          DrvFmrxRetCode_e DrvFmrxMstarGetFrequency(u32 *pu32Freq);
 * @brief       get frequency
 * @param       pu32Freq [out]  frequency (MHz/20)
 * @retval      DrvFmrxRetCode_e error code
 *
 */
DrvFmrxRetCode_e DrvFmrxMstarGetFrequency(u32 *pu32Freq);


/**
 *
 * @fn          DrvFmrxRetCode_e DrvFmrxMstarSetMute(DrvFmrxMute_e eMute);
 * @brief       set mute/un-mute
 * @param       eMute [in]  mute/un-mute
 * @retval      DrvFmrxRetCode_e error code
 *
 */
DrvFmrxRetCode_e DrvFmrxMstarSetMute(DrvFmrxMute_e eMute);


/**
 *
 * @fn          DrvFmrxRetCode_e DrvFmrxMstarSetForceMono(DrvFmrxStereo_e eStereo);
 * @brief       set mono/stereo
 * @param       eStereo [in]    stereo/mono
 * @retval      DrvFmrxRetCode_e error code
 *
 */
DrvFmrxRetCode_e DrvFmrxMstarSetForceMono(DrvFmrxStereo_e eStereo);


/**
 *
 * @fn          DrvFmrxRetCode_e DrvFmrxMstarGetStereo(DrvFmrxStereo_e *peStereo);
 * @brief       get mono/stereo
 * @param       peStereo [out]    stereo/mono
 * @retval      DrvFmrxRetCode_e error code
 *
 */
DrvFmrxRetCode_e DrvFmrxMstarGetStereo(DrvFmrxStereo_e *peStereo);


/**
 *
 * @fn          DrvFmrxRetCode_e DrvFmrxMstarSetCarryLockThreshold(u32 u32Threshold);
 * @brief       set carry lock threshold
 * @param       u32Threshold [in]   carry lock threshold
 *                                  [7:0]   carrier on NSR threshold (default: 0x20)
 *                                  [15:8]  carrier off NSR threshold (default: 0x40)
 * @retval      DrvFmrxRetCode_e error code
 *
 */
DrvFmrxRetCode_e DrvFmrxMstarSetCarryLockThreshold(u8 nLockOnThreshold, u8 nLockOffThreshold);


/**
 *
 * @fn          DrvFmrxRetCode_e DrvFmrxMstarSetAreaParameters(u32 u32Parameters);
 * @brief       set area parameters
 * @param       u32Parameters [in]  area parameters
 *                                  [15:12]     maximum frequency of the range band (MHz) (0: 68, 1: 73, 2: 74, 3: 87.5, 4: 90, 5: 100, 6: 108)
 *                                  [11:8]      minimum frequency of the range band (MHz) (0: 66, 1: 68, 2: 73, 3: 76, 4: 87.5, 5: 87.8, 6: 88, 7: 100)
 *                                  [7:5]       BPFIR (KHz) (0: 100, 1: 120, 2: 150, 3: 200)
 *                                  [4:2]       step space (KHz) (0: 50, 1: 100, 2: 200, 3: 30, 4: 300)
 *                                  [1]         De Emphasis (us) (0: 50, 1: 75)
 * @retval      DrvFmrxRetCode_e error code
 *
 */
DrvFmrxRetCode_e DrvFmrxMstarSetAreaParameters(u32 u32Parameters);


/**
 *
 * @fn          DrvFmrxRetCode_e DrvFmrxMstarUpdateSoundMode(void);
 * @brief       update sound mode
 * @param       void
 * @retval      DrvFmrxRetCode_e error code
 *
 */
DrvFmrxRetCode_e DrvFmrxMstarUpdateSoundMode(void);

/**
 *
 * @fn          DrvFmrxRetCode_e DrvFmrxMstarCheckPowerStatus(bool* drv_status, bool* hw_status)
 * @brief       check power status
 * @param       void
 * @retval      DrvFmrxRetCode_e error code
 *
 */
DrvFmrxRetCode_e DrvFmrxMstarCheckPowerStatus(bool* drv_status, bool* hw_status);

/**
 *
 * @fn          DrvFmrxRetCode_e DrvFmrxStopSearchChannel(void);
 * @brief       cancel channel search
 * @param       void
 * @retval      DrvFmrxRetCode_e error code
 *
 */
DrvFmrxRetCode_e DrvFmrxStopSearchChannel(void);

/**
 *
 * @fn          DrvFmrxRetCode_e DrvFmrxMstarGetChanInfo(csl_FmrChanInfo_t *pChanInfo, bool rssiAllowed);
 * @brief       get channel information
 * @param       pChanInfo   [out]   channel information
 * @param       rssiAllowed [in]    get RSSI or not
 * @retval      DrvFmrxRetCode_e error code
 */
DrvFmrxRetCode_e DrvFmrxMstarGetChanInfo(csl_FmrChanInfo_t *pChanInfo, bool rssiAllowed);

/**
 *
 * @fn          bool DrvFmrxMstarIsAntennaSupported(void)
 * @brief       return antenna supported or not
 * @param       void
 * @retval      bool    TRUE: supported, FALSE: not supported
 */
bool DrvFmrxMstarIsAntennaSupported(void);

/**
 *
 * @fn          bool DrvFmrxMstarIsRecordingSupported(void)
 * @brief       return recording supported or not
 * @param       void
 * @retval      bool    TRUE: supported, FALSE: not supported
 */
bool DrvFmrxMstarIsRecordingSupported(void);
/**
 *
 * @fn          bool DrvFmrxMstarIsStereoSupported(void)
 * @brief       return stereo supported or not
 * @param       void
 * @retval      bool    TRUE: supported, FALSE: not supported
 */
bool DrvFmrxMstarIsStereoSupported(void);
/**
 *
 * @fn          bool DrvFmrxMstarSetStereoSupported(void)
 * @brief       set stereo supported or not
 * @param       void
 * @retval      void    
 */
void DrvFmrxMstarSetStereoSupported(void);

csl_FmrErrCode_e DrvFmrxStopSeek(void);
csl_FmrErrCode_e DrvFmrxGetChanInfo(csl_FmrChanInfo_t *pChanInfo, bool rssiAllowed);
csl_FmrErrCode_e DrvFmrxSetArea(csl_FmrArea_e area);
csl_FmrErrCode_e DrvFmrxPowerOnOff(u8 on);
csl_FmrErrCode_e DrvFmrxSeek(u8 on, u8 direction);
csl_FmrErrCode_e DrvFmrxTune(u32 freq);
csl_FmrErrCode_e DrvFmrxSetMute(u8 on);
csl_FmrErrCode_e DrvFmrxSetStereo(u8 on);

csl_FmrErrCode_e DrvFmrxCheckPowerStatus(bool* drv_status, bool* hw_status);

#ifdef __cplusplus
}
#endif

#endif // __DRV_FMRX_MSTAR_PUB_H__
