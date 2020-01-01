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
* @file    mdl_gpd_core_pub.h
* @version
* @brief   This module defines General Peripheral Device Driver core API layer
*
*/
#ifndef __MDL_GPD_CORE_PUB_H__
#define __MDL_GPD_CORE_PUB_H__


/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "mdl_gpd_pub.h"


/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/


/**
 *  @brief The structure defines the device ctrl pattern
 */
typedef struct {
  u16                   PatternCtlEnable;
  u16                   Cycle;
  u16                   PatternInx;
  MdlGpdLedPattern_t   *pPattern;
} MdlGpdDevpattern_t;


/**
 * @brief The structure defines the device toggle cycle control
 */
typedef struct
{
    u16 nOnTime;       /**< On time (ms) */
    u16 nOffTime;      /**< Off time (ms) */
    u16 nCycle;        /**< total cycle */
} MdlGpdCycleCtrl_t;


/**
 *  @brief The enumeration defines the headset type.
 */
typedef enum
{
    MDL_THREE_SEGMENT_HEADSET,       /**< Three segment headset */
    MDL_FOUR_SEGMENT_HEADSET,        /**< Four segment headset */
    MDL_UNKNOWN_SEGMENT_HEADSET      /**< Unknown segment headset */
} MdlGpdHeadsetType_e;

/**
 *  @brief The structure defines the notification type
 */
typedef struct MdlGpdNotifyNode_t
{
    MdlGpdAcsNotifyCb_t        tAcsNotifyCb;
    MdlGsensorNotifyCb_t       tGsensorNotifyCb;
#ifdef __PROXIMITY_SENSOR_DRV__
    MdlProximitySensorNotifyCb_t       tProximitySensorNotifyCb;
#endif
    struct MdlGpdNotifyNode_t  *pNext;
} MdlGpdNotifyNode_t;


/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/

/**
 * @brief Device toggle cycle
 *
 * @param eDevType                     : [in] Device type
 *
 * @return                             : NONE
 */
void  MdlGpdDevToggleCycle(MdlGpdDevType_e eDevType);


/**
 * @brief Set vibrator level before switch on vibrator
 *
 * @param nLevel                        : Set vibrator level
 * @param ptDurSetting                  : If Operation is MDL_GPD_OP_DURATION, user should provide the duration setting. Otherwise, it shell be NULL.
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdVibratorSetLevel(u8 nLevel);


/**
 * @brief Switch vibrator
 *
 * @param eOperation                    : Switch on, off, or periodically
 * @param ptDurSetting                  : If Operation is ESL_GPD_OP_DURATION, user should provide the duration setting. Otherwise, it shell be NULL.
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdVibratorSwitch(MdlGpdOp_e eOperation, MdlGpdDuration_t *ptDurSetting);


/**
 * @brief Switch led
 *
 * @param eLedId                        : LED ID
 * @param eOperation                    : Switch on, off, or periodically
 * @param ptDurSetting                  : If eOperation is ESL_GPD_OP_DURATION, user should provide the duration setting. Otherwise, it shell be NULL.
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdLedSwitch(MdlGpdLedId_e eLedId, MdlGpdOp_e eOperation, MdlGpdDuration_t *ptDurSetting);


/**
 * @brief Switch backlight
 *
 * @param eBlId                         : Backlight ID
 * @param nRange                        : Maximum range of the brightness
 * @param nLevel                        : Level of the brightness
 * @param ptDurSetting                  : If user want to switch brightness periodically, user should provide the duration setting. Otherwise, it shell be NULL.
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdBacklightSwitch(MdlGpdBlId_e eBlId, u8 nRange, u8 nLevel, MdlGpdDuration_t *ptDurSetting);


/**
 * @brief Set backlight flash
 *
 * @param eBlId                         : Backlight ID
 * @param Range                         : Maximum range of the brightness
 * @param nLevel_1                      : Level 1 of the brightness
 * @param nLevel_2                      : Level 2 of the brightness
 * @param pDurSetting                   : If user want to switch brightness periodically, user should provide the duration setting. Otherwise, it shell be NULL.
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdBacklightFlash(MdlGpdBlId_e eBlId, u8 nRange, u8 nLevel_1, u8 nLevel_2, MdlGpdDuration_t *ptDurSetting);


/**
 * @brief Restore backlight flash
 *
 * @param eBlId                         : Backlight ID
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdBacklightRestore(MdlGpdBlId_e eBlId);


#ifdef __FLASHLIGHT_DRV__
/**
 * @brief Switch flash light
 *
 * @param eOperation                     : Switch on, off, or periodically
 * @param ptDurSetting                   : If eOperation is MDL_GPD_OP_DURATION, user should provide the duration setting. Otherwise, it shell be NULL.
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdFlashlightSwitch(MdlGpdOp_e eOperation, MdlGpdDuration_t *ptDurSetting);
#endif


#ifdef __FILLLIGHT_DRV__
/**
 * @brief Switch fill light
 *
 * @param eOperation                     : Switch on, off, or periodically
 * @param ptDurSetting                   : If eOperation is MDL_GPD_OP_DURATION, user should provide the duration setting. Otherwise, it shell be NULL.
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdFilllightSwitch(MdlGpdOp_e eOperation, MdlGpdDuration_t *ptDurSetting);
#endif


/**
 * @brief Get plug device status
 *
 * @param eAcsType                      : Device type
 * @param peAcsStatus                   : [out] Current status of the accessory
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdGetAcsStatus(MdlGpdAcsType_e eAcsType, MdlGpdAcsStatus_e *peAcsStatus);


/**
 * @brief Get device status
 *
 * @param eDevType                      : Device type
 * @param peDevStatus                   : [out] Current status of the device
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdGetDevStatus(MdlGpdDevType_e eDevType, MdlGpdDevStatus_e *peDevStatus);


/**
 * @brief Register notification for plug device. MMI will receive the notification if device status change.
 *
 * @param eAcsType                      : Device type
 * @param tNotifyCb                     : Notification for device status change
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdRegAcsNotify(MdlGpdAcsType_e eAcsType, MdlGpdAcsNotifyCb_t tNotifyCb);


/**
 * @brief Get the power on cause.
 *
 * @param pePwrOnCause                  : [out] Power on cause
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdPowerOnCause(MdlGpdPwrOnCause_e *pePwrOnCause);


/**
 * @brief Get the version.
 *
 * @param eVerType                      : Version type
 * @param pVersion                      : [out] Version string
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdGetVersion(MdlGpdVerType_e eVerType, char *pVersion);


/**
 * @brief Get the version.
 *
 * @param eAcsType                      : Accessory type
 * @param eAcsStatus                    : Accessory status
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdAcsIndication(MdlGpdAcsType_e eAcsType, MdlGpdAcsStatus_e eAcsStatus);


/**
 * @brief Headset hook indication
 *
 * @param                               : NONE
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdHeadsetHookIndication(void);


/**
 * @brief Register service ON/OFF callback function.
 *        The callback function will be called when system want to sleep, and it should return service ON/OFF status.
 *        If any one of services which retuned ON status, system will not enter sleep mode.
 *
 * @param eSrvType                       : Service type
 * @param tSrvCb                         : Callback function which return service status
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdRegServiceOnOffCallback(MdlGpdSrvType_e eSrvType, MdlGpdSrvCb_t tSrvCb);


/**
 * @brief  This function is used to set device on/off status and counter the total device on/off
 *
 * @param  eDevice                      : Input device (only 1 bit is 1 per device)
 * @param  isON                         : TRUE: set the device on, FALSE: set the device off
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 * @retval MDL_GPD_REJECT               : Function request reject
 */
MdlGpdErrCode_e MdlGpdSetDeviceOnOff(MdlGpdDevice_e eDevice, bool bIsON);

/**
 * @brief  This function is used to get device on/off status
 *
 * @param  NONE
 *
 */
u32 MdlGpdGetDeviceOnOff(void);


/**
 * @brief  This function is used to get service on/off status
 *
 * @param  void
 *
 * @retval Service status
 */
u32 MdlGpdGetServiceOnOff(void);


/**
 * @brief Switch device power for MMI use case.
 *
 * @param eDevPowerType                  : Device power which need to switch for MMI use case.
 * @param eOperation                     : Switch on, off device power. Not periodically.
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdDevicePowerSwitch(MdlGpdDevPowerType_e eDevPowerType, MdlGpdOp_e eOperation);


#if defined(__BREATHLIGHT_DRV__)
/**
 * @brief Switch gpd device with pattern
 *
 * @param DevType                       : Device Type
 * @param Operation                     : Switch on, off
 * @param pPattern                      : Switch pattern
 *
 * @retval CSL_GPD_OK                   : Function request success
 * @retval CSL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdDevPatternSwitch(MdlGpdDevType_e DevType, MdlGpdOp_e Operation, u16 Cycle, MdlGpdLedPattern_t *pPattern);

/**
 * @brief Device toggle with pattern
 *
 * @param DevType       : [in] Device type
 * @param Operation     : Switch on, off, or periodically
 *
 * @retval GPD_DRV_OK   : Operation success
 * @retval GPD_DRV_FAIL : Operation fail
 */
MdlGpdErrCode_e MdlGpdDevPatternToggleCycle(MdlGpdDevType_e DevType, MdlGpdOp_e Operation);
#endif

/**
 * @brief Get the status of 3 segment headset.
 *
 * @param peHeadsetType                 : [Out] pointer to Headset type
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpdGet3SegmentHeadsetStatus(MdlGpdHeadsetType_e *peHeadsetType);


/**
 * @brief Indicate that the status of 3 segment headset.
 *
 * @param None
 *
 * @retval MDL_GPD_OK                   : Function request success
 * @retval MDL_GPD_FAIL                 : Function request fail
 */
MdlGpdErrCode_e MdlGpd3SegmentHeadsetIndication(void);

#ifndef __SDK_SIMULATION__
#ifdef __UPGRADE_NVRAM__
MdlGpdErrCode_e MdlGpdNvramUpdate(MdlGpdNvramType_e eNvramType, u8 *pAddr, u32 nLen);
MdlGpdErrCode_e MdlGpdNvramBackup(void);
#ifdef __UPGRADE_NVRAM_ENHANCED__
MdlGpdErrCode_e MdlGpdNvramRestore(MdlGpdNvramType_e eNvramType, u8 **ppAddr, u16* nLen);
MdlGpdErrCode_e MdlGpdNvramComplete(MdlGpdNvramType_e eNvramType, MdlGpdNvramCause_e causeValue, u16 nLen, u8* pAddr, u16 nUpdateLen, u8* pUpdateAddr);
#endif  // __UPGRADE_NVRAM_ENHANCED__
#endif  // __UPGRADE_NVRAM__
#endif  // !__SDK_SIMULATION__



#endif /* __MDL_GPD_CORE_PUB_H__ */

