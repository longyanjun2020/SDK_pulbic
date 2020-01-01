/**
* @file    mmi_srv_core.h
* @brief   Core Service provide APIs for the basic control purpose.
*          For Example, to control the backlight, keytone, touch-behavior, etc.
*
*/

#ifndef __MMI_SRV_CORE_H__
#define __MMI_SRV_CORE_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_coresrv.h"


/* callback function type */
/** SrvCoreAppLaunchedCB
* @brief         The callback function to confirm the powering on/off request. (triggered by CORESRV_EVT_APP_*)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    nClsId             The class ID of the Resumed AP.
* @param[out]    nDParam             The address of the structure store related information, it should be cas as (MaeParam_t*).
*/
typedef void (* SrvCoreAppMonitorCB)(void *pThis, u32 nClsId, u32 nDParam);


/** SrvCoreAppLaunchedCB
* @brief         The callback function to confirm the powering on/off request. (triggered by CORESRV_EVT_APP_LAUNCHED)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    nClsId             The class ID of the launched AP.
*/
typedef void (* SrvCoreAppLaunchedCB)(void *pThis, MAE_ClsId nClsId);

/** SrvCoreAppClosedCB
* @brief         The callback function to confirm the powering on/off request. (triggered by CORESRV_EVT_APP_LAUNCHED)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    nClsId             The class ID of the launched AP.
*/
typedef void (* SrvCoreAppClosedCB)(void *pThis, MAE_ClsId nClsId);

/** SrvCoreBackLigh_OnOff_CB
* @brief         The callback function to confirm the powering on/off request. (triggered by CORESRV_EVT_BACKLIGHT_ON or CORESRV_EVT_BACKLIGHT_OFF)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    bBackLightOn       The status about backlight on/off.
*/
typedef void (* SrvCoreBackLigh_OnOff_CB)(void *pThis, boolean bBackLightOn);

/** SrvCoreFlash_OnOff_CB
* @brief         The callback function to confirm the flash on/off request. (triggered by CORESRV_EVT_FLASH_ON or CORESRV_EVT_FLASH_OFF)
*
* @param[out]    pThis              The pointer of the applet.
* @param[out]    bFlashOn           The status about flash on/off.
*/
typedef void (* SrvCoreFlash_OnOff_CB)(void *pThis, boolean bFlashOn);

#ifdef __CHECK_CPU_STATUS_BEFORE_SLEEP__

typedef void (* SrvCore_Find_High_CPU_Task_CB)(void *pThis, HighSpeedTaskStatus_e eStatus);

/** SrvCore_Find_High_CPU_Task_CB
* @brief         The callback function used to indicated AP that high speed sleep happened. (triggered by CORESRV_EVT_HIGH_SPEED_TASK)
*
* @param[out]    pThis              The pointer of the applet.
*/
MAE_Ret SrvCoreSetFindHighCPUSleepTaskCB(SrvCore_Find_High_CPU_Task_CB pfnCallBack);

MAE_Ret SrvCoreResetFindHighSpeedTask(void);
MAE_Ret SrvCoreIsFindHighSpeedTask(HighSpeedTaskStatus_e *eStatus);


#endif

/* APIs */
/** SrvCoreSetAppMonitorCB
@brief  Register/deregister a callback function to notify which AP's state to be change by APM
@       Currently, We just support Resume/Start/Restart/Stop event monitor.

@param[in]      pfnCallBack         SrvCoreSetAppMonitorCB, a callback function pointer

@retval MAE_RET_SUCCESS             If successful.
@return MAE_RET_OUT_OF_MEMORY       If Can not allocate memory from OS.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.

*/
MAE_Ret SrvCoreSetAppMonitorCB(u32 nCoreSrvEvt, SrvCoreAppMonitorCB pfnCallBack);



/** SrvCoreSetAppLaunchedCB
@brief  Register/deregister a callback function to notify which AP is launched by ClsId
        when an AP is launched(new one or restarted).

@param[in]      pfnCallBack         SrvCoreAppLaunchedCB, a callback function pointer

@retval MAE_RET_SUCCESS             If successful.
@return MAE_RET_OUT_OF_MEMORY       If Can not allocate memory from OS.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.

*/
MAE_Ret SrvCoreSetAppLaunchedCB(SrvCoreAppLaunchedCB pfnCallBack);

/** SrvCoreAppClosedCB
@brief  Register/deregister a callback function to notify which AP is closed by ClsId.

@param[in]      pfnCallBack         SrvCoreAppLaunchedCB, a callback function pointer

@retval MAE_RET_SUCCESS             If successful.
@return MAE_RET_OUT_OF_MEMORY       If Can not allocate memory from OS.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.

*/
MAE_Ret SrvCoreSetAppClosedCB(SrvCoreAppClosedCB pfnCallBack);

/** SrvCoreSetBackLightCB
@brief  Register/deregister a callback function to listen to the backlight On/Off

@param[in]      pfnCallBack         SrvCoreBackLigh_OnOff_CB, a callback function pointer

@retval MAE_RET_SUCCESS             If successful.
@return MAE_RET_OUT_OF_MEMORY       If Can not allocate memory from OS.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.

*/
MAE_Ret SrvCoreSetBackLightCB(SrvCoreBackLigh_OnOff_CB pfnCallBack);


typedef void (* SrvCoreBacklight_LevelChanged_CB)(void *pThis, u8 nCmdIdx);
/** SrvCoreSetBackLightLevelChangedCB
@brief  The interface of Service Client is use to set CB to listen the Back light ;evel changed

@param[in]      pfnCallBack         CORESRV_EVT_BACKLIGHT_LEVEL_CHANGED Callback function point

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_SUPPORTED       CORESrv is already terminated.
*/
MAE_Ret SrvCoreSetBackLightLevelChangedCB(SrvCoreBacklight_LevelChanged_CB pfnCallBack);



/** SrvCoreSetFlashCB
@brief  Register/deregister a callback function to listen to the flash On/Off.

@param[in]      pfnCallBack         SrvCoreFlash_OnOff_CB, a callback function pointer

@retval MAE_RET_SUCCESS             If successful.
@return MAE_RET_OUT_OF_MEMORY       If Can not allocate memory from OS.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.

*/
MAE_Ret SrvCoreSetFlashCB(SrvCoreFlash_OnOff_CB pfnCallBack);

#ifdef __PROXIMITY_SENSOR_MMI__

typedef void (* SrvCore_InfraredInd_CB)(void *pThis, u32 param1, u32 param2);
/** SrvCoreSetInfraredIndCB
@brief  The interface of Service Client is use to set CB to listen the Infrared Ind

@param[in]      pfnCallBack         SrvCore_InfraredInd_CB Call back function point

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_SUPPORTED       CORESrv is already terminated. 
*/
MAE_Ret SrvCoreSetInfraredIndCB(SrvCore_InfraredInd_CB pfnCallBack);
#endif

/** SrvCoreRequestBacklightON
@brief  Turn on backlight according to the proposed settings.

@param[in]      pSettings           Setting value about the backlight bright-level/duration and the auto-Off for keypad-light

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.
@retval MAE_RET_BAD_PARAM           If wrong parameters.

*/
MAE_Ret SrvCoreRequestBacklightON(BKLSettings *pSettings);

/** SrvCoreRequestBacklightOFF
@brief  Turn off the backlight.

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.

*/
MAE_Ret SrvCoreRequestBacklightOFF(void);

#ifdef __HALL_SWITCH_MMI__
/** SrvCoreEnableHallSwitchEffect
@brief  The interface is use to Enable/Disable Hall Switch Effect

@param[in]      bEnable             Enable/Disable the hall switch effect

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_SUPPORTED       CORESrv is already terminated.
*/
void SrvCoreEnableHallSwitchEffect(boolean bEnable);
#endif

/** SrvCoreRequest2LBacklightON
@brief  The interface is use to turn on back light by 2 level settings

@param[in]      pSettings           Setting value pointer about 2 level backlight brightness and duration

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_SUPPORTED       CORESrv is already terminated.
*/
MAE_Ret SrvCoreRequest2LBacklightON(BKL2LSettings *pSettings);


/** SrvCoreEnableKeyPressTone
@brief  Set key-press tone enable/disable.

@param[in]      bEnable             TRUE for enable the key-press tone and FALSE for disable.

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.

*/
MAE_Ret SrvCoreEnableKeyPressTone(boolean bEnable);

/** SrvCoreEnableKeyEvent
@brief  Set key-event enable/disable.

@param[in]      bEnable             TRUE for enable the key-event and FALSE for disable.

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.

*/
MAE_Ret SrvCoreEnableKeyEvent(boolean bEnable);

/** SrvCoreEnableKeyEvent
@brief  Set touch-event enable/disable and the behavior for enable.
        Currently, two behaviors are supported: alway or go-with-backlight

@param[in]      bOnOff              TRUE for enable the touch-event and FALSE for disable.
@Param[in]      eTouchBehavior      Let touch behavior as always on/off or follow the backlight behavior

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.

*/
MAE_Ret SrvCoreSetTouchBehavior(boolean bOnOff, TouchBehavior_e eTouchBehavior);

/** SrvCoreSetDefaultBacklight
@brief  Set default backlight settings.

@param[in]      Settings            backlight settings

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.

*/
MAE_Ret SrvCoreSetDefaultBacklight(BKLSettings Settings);

/** SrvCoreSetActiveBacklight
@brief  Set active backlight settings.

@param[in]      Settings            backlight settings

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.

*/
MAE_Ret SrvCoreSetActiveBacklight(BKLSettings Settings);


/** SrvCoreRequestDefaultBacklight
@brief  Turn on backlight according to its local default back light settings.

@retval MAE_RET_SUCCESS             If successful.

*/
MAE_Ret SrvCoreRequestDefaultBacklight(void);

/** SrvCoreIsBacklightOn
@brief  Check the current backlight information(on or off)

@retval TRUE           On.
@retval FALSE          Off.

*/
boolean SrvCoreIsBacklightOn(void);

/** SrvCoreIsKeyEnable
@brief  Check current key-event is enable or not.

@retval TRUE           Enable.
@retval FALSE          Disable.

*/
boolean SrvCoreIsKeyEnable(void);

/** SrvCoreIsTouchEnable
@brief  Check current touch-event is enable or not.

@retval TRUE           Enable.
@retval FALSE          Disable.

*/
boolean SrvCoreIsTouchEnable(void);

/** SrvCoreIsLeavingSleepMode
@brief  Check if system is running leave-sleep-mode process or not.

@retval TRUE           Yes.
@retval FALSE          No.

*/
boolean SrvCoreIsLeavingSleepMode(void);


/** SrvCoreEnableLaunchFunc
@brief  To enable/disable launch function by hotkeys.

@param[in]      eFuncType           Launch Function Type: CORESRV_LAUNCH_FUNC_POWERMODE
                                                          CORESRV_LAUNCH_FUNC_CAMERA
                                                          CORESRV_LAUNCH_FUNC_MP3
                                                          CORESRV_LAUNCH_FUNC_FM
                                                          CORESRV_LAUNCH_FUNC_MSG
                                                          CORESRV_LAUNCH_FUNC_MAIL
                                                          CORESRV_LAUNCH_FUNC_AUTO_KEYGUARD
                                                          CORESRV_LAUNCH_FUNC_SCREENSAVER
                                                          CORESRV_LAUNCH_FUNC_ATV

@param[in]      bEnable             TRUE for enable and FALSE for disable.

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.
@retval MAE_RET_BAD_PARAM           If wrong parameters.

*/
MAE_Ret SrvCoreEnableLaunchFunc(LaunchFuncType_e eFuncType, boolean bEnable);

/** SrvCoreIgnoreBacklightRequest
@brief  Set to ignore backlight on/off request or not

@param[in]      bIgnore             TRUE for ignore and FALSE for not ignore.
*/
void SrvCoreIgnoreBacklightRequest(boolean bIgnore);

/** SrvCoreRequestFlashON
@brief  Turn on the flash with the proposed setting.

@param[in]      pFlashSetting       the flash settings.

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.
@retval MAE_RET_BAD_PARAM           If wrong parameters.

*/
MAE_Ret SrvCoreRequestFlashON(FlashSetting_st *pFlashSetting);

/** SrvCoreRequestFlashOFF
@brief  Turn off the flash.

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.

*/
MAE_Ret SrvCoreRequestFlashOFF(void);

/** SrvCoreFlushAPToIdleBase
@brief  Flush all APs in stack and launch Idle/Main-menu according to current main menu style
*/
void SrvCoreFlushAPToIdleBase(void);

/** SrvCoreIsLaunchFuncEnable
@brief  Check some hotkey-triggered function is enable or disable.

@param[in]      eFuncType           LaunchFuncType_e

@retval TRUE           Enable.
@retval FALSE          Disable.

*/
boolean SrvCoreIsLaunchFuncEnable(LaunchFuncType_e eFuncType);

/** SrvCoreIsLaunchFuncEnable
@brief  Play keytone by keyID

@param[in]      nKeyId              KeyId which want to play key tone
                                    value like MAE_KEY_SEND (defined in mae_event.h)
*/
void SrvCorePlayKeyPressTone(u32 nKeyId);

/** SrvCoreUpdateDisplayWithBackLight
@brief  Set forcing display-update or not when turning backlight on.

@param[in]      bUpdate             TRUE for forcing display-update and FALSE for no force update.
*/
void SrvCoreUpdateDisplayWithBackLight(boolean bUpdate);

/** SrvCoreSetBacklightByInfo
@brief  Set backlight by the proposed information.

@param[in]      BKLInfomation       Backlight information

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.

*/
MAE_Ret SrvCoreSetBacklightByInfo(BKLInfo BKLInfomation);

/** SrvCoreGetCurrentBacklightInfo
@brief  Get the current backlight information.

@param[out]     pBKLInfomation      Backlight information

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.
@retval MAE_RET_BAD_PARAM           If wrong parameters.

*/
MAE_Ret SrvCoreGetCurrentBacklightInfo(BKLInfo *pBKLInfomation);

/** SrvCoreResetBackLightTimerByTouchEvent
@brief  Reset backlight timer when receiving touch event.

@param[in]      bEnable             TRUE for reseting backlight timer and FALSE for ignoring it.
*/
void SrvCoreResetBackLightTimerByTouchEvent(boolean bEnable);

/**
 SrvCoreResetBackLight
@brief  Reset backlight duration and set bright level to default.

@param[in]      none
*/
void SrvCoreResetBackLight(void);

/**
 SrvCoreGetFlashlightMode
@brief  Get Flashlight Mode

@param[out]   eFlashlightMode       Flashlight mode: FLASHLIGHT_MODE_OFF = 0,   < Turn off the device >
                                                     FLASHLIGHT_MODE_ON,        < Turn on the device >

@return MAE_RET_SUCCESS             If successful.
@return MAE_RET_FAILED              If an error happen.
@return MAE_RET_BAD_PARAM           If wrong parameters.
@return MAE_RET_OUT_OF_MEMORY       If Can not allocate memory from OS.
@return MAE_RET_REJECT              If other function's confliction.
@return MAE_RET_ABORT               If incorrect sequence.
@return MAE_RET_TIMEOUT             If request no response.
@return MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.

*/
MAE_Ret SrvCoreGetFlashlightMode(FlashlightMode_e *eFlashlightMode);

/**
 SrvCoreSetFlashlightMode
@brief  Set flash-light Mode

@param[in]   eFlashlightMode       Flashlight mode: FLASHLIGHT_MODE_OFF = 0,   < Turn off the device >
                                                    FLASHLIGHT_MODE_ON,        < Turn on the device >

@return MAE_RET_SUCCESS            If successful.
@return MAE_RET_FAILED             If an error happen.
@return MAE_RET_BAD_PARAM          If wrong parameters.
@return MAE_RET_OUT_OF_MEMORY      If Can not allocate memory from OS.
@return MAE_RET_REJECT             If other function's confliction.
@return MAE_RET_ABORT              If incorrect sequence.
@return MAE_RET_TIMEOUT            If request no response.
@return MAE_RET_NOT_SUPPORTED      If CORESrv is already terminated.

*/
MAE_Ret SrvCoreSetFlashlightMode(FlashlightMode_e eFlashlightMode);

/**
 SrvCoreGetFillLightMode
@brief  Get fill-light mode.

@param[out]   eFillLightMode        Fill Light mode: FILLLIGHT_MODE_OFF = 0,   < Turn off the device >
                                                     FILLLIGHT_MODE_ON,        < Turn on the device >

@return MAE_RET_SUCCESS             If successful.
@return MAE_RET_FAILED              If an error happen.
@return MAE_RET_BAD_PARAM           If wrong parameters.
@return MAE_RET_OUT_OF_MEMORY       If Can not allocate memory from OS.
@return MAE_RET_REJECT              If other function's confliction.
@return MAE_RET_ABORT               If incorrect sequence.
@return MAE_RET_TIMEOUT             If request no response.
@return MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.

*/
MAE_Ret SrvCoreGetFillLightMode(FillLightMode_e *eFillLightMode);

/**
 SrvCoreSetFillLightMode
@brief  The interface is to set fill light mode.

@param[in]   eFillLightMode         Fill Light mode: FILLLIGHT_MODE_OFF = 0,   < Turn off the device >
                                                     FILLLIGHT_MODE_ON,        < Turn on the device >

@return MAE_RET_SUCCESS             If successful.
@return MAE_RET_FAILED              If an error happen.
@return MAE_RET_BAD_PARAM           If wrong parameters.
@return MAE_RET_OUT_OF_MEMORY       If Can not allocate memory from OS.
@return MAE_RET_REJECT              If other function's confliction.
@return MAE_RET_ABORT               If incorrect sequence.
@return MAE_RET_TIMEOUT             If request no response.
@return MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.

*/
MAE_Ret SrvCoreSetFillLightMode(FillLightMode_e eFillLightMode);

#ifdef __PROXIMITY_SENSOR_MMI__
/**
 SrvCoreEnableInfrared
@brief  Enable Infrared
                
@param[in]      none
*/
MAE_Ret SrvCoreEnableInfrared(void);

/**
 SrvCoreDisableInfrared
@brief  Disable Infrared
                
@param[in]      none
*/
MAE_Ret SrvCoreDisableInfrared(void);
#endif

/**
 SrvCoreSetFillLightMode
@brief  Checkt the capability for the fill light.

@return TRUE                        Yes.
@return FALSE                       No.

*/
boolean SrvCoreIsFilllightSupport(void);

/**
 SrvCoreRequestMuiltiBacklightON
@brief  The interface is to set fill light mode.

*/
MAE_Ret SrvCoreRequestMuiltiBacklightON(MultiBKLSetting *pSettings);

/** SrvCoreEnableLongPressedLaunchFunc
@brief  To enable/disable launch function by long pressed hotkeys.

@param[in]      eFuncType           Launch Function Type: CORESRV_LAUNCH_FUNC_POWERMODE
                                                          CORESRV_LAUNCH_FUNC_CAMERA
                                                          CORESRV_LAUNCH_FUNC_MP3
                                                          CORESRV_LAUNCH_FUNC_FM
                                                          CORESRV_LAUNCH_FUNC_MSG
                                                          CORESRV_LAUNCH_FUNC_MAIL
                                                          CORESRV_LAUNCH_FUNC_AUTO_KEYGUARD
                                                          CORESRV_LAUNCH_FUNC_SCREENSAVER
                                                          CORESRV_LAUNCH_FUNC_ATV

@param[in]      bEnable             TRUE for enable and FALSE for disable.

@retval MAE_RET_SUCCESS             If successful.
@retval MAE_RET_NOT_SUPPORTED       If CORESrv is already terminated.
@retval MAE_RET_BAD_PARAM           If wrong parameters.

*/
MAE_Ret SrvCoreEnableLongPressedLaunchFunc(LaunchFuncType_e eFuncType, boolean bEnable);


//This is a temporary interface for vender app to clear it's local backlight setting
//This interface will be removed before 2011/06/30
MAE_Ret SrvCoreCleanLocalBacklightSetting(void);

/*-----------------------------------------------------*/
#endif //__MMI_SRV_CORE_H__


