/**
* @file    mmi_srv_touch.h
* @brief
*
*/

#ifndef __MMI_SRV_TOUCHSERVICE_H__
#define __MMI_SRV_TOUCHSERVICE_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_mae_touchsrv.h"
#include "mmi_mae_touchsrv_forward.h"
#include "mmi_mae_event.h"


/** SrvHookMultiTouchEvent
**/
MAE_Ret SrvTouchHookMultiTouchEvent(s32 WdgPosX, s32 WdgPosY, u32 nPointId,IBase *pContext);
MAE_Ret SrvTouchUnHookMultiTouchEvent(u32 nPointId);
boolean SrvTouchIsHookedByPointId(u32 nPointId);
boolean SrvTouchIsHookedByPosition(s32 sPointX,s32 sPointY);
boolean SrvTouchUpdateHookerPosistion(s32 WdgRectX,s32 WdgRectY);
u32 SrvTouchQueryPointId(s32 sPointX, s32 sPointY);
u32 SrvTouchQueryNumOfFingerPressed(void);



/** SrvTouchHookEvent
* @brief  To hook touch screen events.
*         TouchSrv provides a registration mechanism for an IHandler object to
*         pass all touch screen events to this IHandler object. If this IHandler
*         object doesn't want to listen touch screen event anymore, call SrvTouchUnhookEvent()
*         to cancel registration.
*
* @param[in]  x(s32)                  x coordinate on the screen of pIHandler object.
* @param[in]  y(s32)                  y coordinate on the screen of pIHandler object.
* @param[in]  pContext(IBase*)        Context to handle touch event.
*
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_READY           If TouchSrv is already terminated.
* @retval MAE_RET_FAILED              If Object already registered.
**/
MAE_Ret SrvTouchHookEvent(s32 x, s32 y, IBase *pContext);

/** SrvTouchUnhookEvent
* @brief  Unhook touch screen events.
*         Pare with SrvTouchHookEvent()
*
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_READY           If TouchSrv is already terminated.
* @retval MAE_RET_NOT_FOUND           If Object to unhook not found.
**/
MAE_Ret SrvTouchUnhookEvent(void);

/** SrvTouchRegTsEvtRect
* @brief  To register a rectangle for waiting touch event.
*         Pare with SrvTouchDeregTsEvtRect()
*
* @param[in]  pRect(MAE_TS_Rect_t*)    rectangle.
*
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_READY           If TouchSrv is already terminated.
* @retval MAE_RET_FAILED              If Object already registered.
**/
MAE_Ret SrvTouchRegTsEvtRect(MAE_TS_Rect_t *pRect);

/** SrvTouchDeregTsEvtRect
* @brief  To deregister a rectangle for waiting touch event.
*		  Pare with SrvTouchRegTsEvtRect()
*
* @retval MAE_RET_SUCCESS             If successful.
* @retval MAE_RET_NOT_READY           If TouchSrv is already terminated.
* @retval MAE_RET_NOT_FOUND           If Object to unhook not found.
**/
MAE_Ret SrvTouchDeregTsEvtRect(void);

/** SrvTouchSetPollingTime
* @brief  Set touchscreen polling time.
*
* @param[in]  nPollTime(u16)            Polling time in msec.
*/
MAE_Ret SrvTouchSetPollingTime(u16 nPollTime);

MAE_Ret SrvTouchGetResistance(u32 *pxResistance, u32 *pyResistance);


/** SrvTouchSetPollingTimeFast
* @brief  Set touchscreen fast polling time, which time slot is MAE_TS_POLLING_TIME_FAST.
*/
MAE_Ret SrvTouchSetPollingTimeFast(void);

/** SrvTouchSetPollingTimeMedium
* @brief  Set touchscreen medium polling time, which time slot is MAE_TS_POLLING_TIME_MEDIUM.
*/
MAE_Ret SrvTouchSetPollingTimeMedium(void);

/** SrvTouchSetPollingTimeSlow
* @brief  Set touchscreen slow polling time, which time slot is MAE_TS_POLLING_TIME_SLOW.
*/
MAE_Ret SrvTouchSetPollingTimeSlow(void);

/** SrvTouchTurnOnCalibration
* @brief  Set touchscreen to calibration mode, the message type will be different!
*/
MAE_Ret SrvTouchTurnOnCalibration(void);

/** SrvTouchTurnOffCalibration
* @brief  Set touchscreen to normal mode, the message type will be different from calibration mode.
*/
MAE_Ret SrvTouchTurnOffCalibration(void);

/** SrvTouchSetCalibrationData
* @brief  Set touchscreen calibration data.
*
* @param[in]  pstMAETsCalibrationData(MAE_TS_Calibration_t*)   Touch calibration data .
*/
MAE_Ret SrvTouchSetCalibrationData(MAE_TS_Calibration_t *pstMAETsCalibrationData);

/** SrvTouchSetCoordinateMode
* @brief  To set the coordinate mode for touch service.
*         The touch coordinate will be converted by different mode
*
* @param[in]  eTsCoorMode(MAETouchCoorMode_e)  Touch coordiante mode
*
* @retval MAE_RET_SUCCESS           If successful.
*/
MAE_Ret SrvTouchSetCoordinateMode(MAETouchCoorMode_e eTsCoorMode);

/** SrvTouchDisableFingerCmdOnce
* @brief  Disable touch service to transfer finger command once.
*
* @param[in]  eCmdId_(MaeTsCmdId_et)     Touch Finger command id. Refer to MAETsCmdId_e.
*/
MAE_Ret SrvTouchDisableFingerCmdOnce(MaeTsCmdId_e eCmdId);


/** SrvTouchDisableFingerCmd
* @brief  Always disable touch service to transfer finger command.
*
* @param[in]  eCmdId_(MaeTsCmdId_et)     Touch Finger command id. Refer to MAETsCmdId_e.
*/
MAE_Ret SrvTouchDisableFingerCmd(MaeTsCmdId_e eCmdId);

/** SrvTouchEnableFingerCmd
* @brief  Always enable touch service to transfer finger command.
*/
MAE_Ret SrvTouchEnableFingerCmd(void);

/** SrvTouchEnableTS
* @brief  Stop touchscreen service
*/
MAE_Ret SrvTouchEnableTS(void);

/** SrvTouchDisableTS
* @brief  Start touchscreen service
*/
MAE_Ret SrvTouchDisableTS(void);

/** SrvTouchGetTscrType
* @brief        Get touch screen type
*
* @param[out]  pTscrType: pointer to touch screen type enum
*
* @retval MAE_RET_SUCCESS           If successful.
*/
MAE_Ret SrvTouchGetTscrType(MAETscrType_e *pTscrType);

#endif //__MMI_SRV_TOUCHSERVICE_H__
/*-----------------------------------------------------*/
