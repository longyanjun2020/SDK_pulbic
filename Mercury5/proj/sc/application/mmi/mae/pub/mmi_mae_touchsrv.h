/**
* @file mmi_mae_touchsrv.h
* @version $Id: mmi_mae_touchsrv.h 1533 2009-08-05 08:41:01Z steve.lee $
*
* @brief This header file defines the api of ITouchSrv
*/

#ifndef __MMI_MAE_TOUCHSRV_H__
#define __MMI_MAE_TOUCHSRV_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_handler.h"
#include "mmi_mae_touchsrv_forward.h"
/**
* Property id
*/
#define TOUCHSRV_PROP_ENABLE_FINGER_CMD         0x0101 ///< To enable all finger command
#define TOUCHSRV_PROP_DISABLE_FINGER_CMD        0x0102 ///< To disable finger command, P2 is command id mask
#define TOUCHSRV_PROP_DISABLE_FINGER_CMD_ONCE   0x0103 ///< To disable finger command Once, P2 is command id mask
#define TOUCHSRV_PROP_ENABLE_TOUCH   0x0104 ///< To enable touch service
#define TOUCHSRV_PROP_DISABLE_TOUCH   0x0105 ///< To disable touch service, all touch evt will be disabled

#define MAE_TS_POLLING_TIME_FAST    10 //msec.
#define MAE_TS_POLLING_TIME_MEDIUM  20 //msec.
#define MAE_TS_POLLING_TIME_SLOW    40 //msec.

/**********************************************************
* Here defines the interface for ITouchSrv
****/
#define INHERIT_ITouchSrv(IName) \
	INHERIT_IHandler(IName); \
	MAERet_t (*HookEvent) (IName*, IHandler*, s32, s32, IBase*); \
	MAERet_t (*UnhookEvent) (IName*, IHandler*); \
	MAERet_t (*RegTsEvtRc) (IName*, IHandler*, MAE_TS_Rect_t*); \
	MAERet_t (*DeregTsEvtRc) (IName*, IHandler*); \
	void (*SetPollingTime) (IName*, u16); \
	void (*TurnOnCalibration) (IName*, boolean); \
	void (*SetCalibrationData) (IName*, MAE_TS_Calibration_t*); \
	MAERet_t (*SetCoordinateMode) (IName*, MAETouchCoorMode_e); \
    MAERet_t (*HookMultiTouchEvent)(IName* , IHandler*, s32 , s32 , u32 ,IBase *); \
    MAERet_t (*UnHookMultiTouchEvent)(IName*, IHandler *, u32 );\
    u32 (*QueryPointId)(IName*, s32 , s32 ); \
    boolean (*IsHookedByPointId)(IName*, IHandler*,u32); \
    boolean (*IsHookedByPosition)(ITouchSrv *, IHandler*,s32, s32);\
    boolean (*UpdateHookerPosistion)(ITouchSrv *, IHandler*,s32,s32);\
	u32 (*QueryNumOfFingerPressed)(ITouchSrv *)
DEFINE_INTERFACE(ITouchSrv);

#define ITOUCHSRV_UpdateHookerPosistion(ITouchSrvPtr,_pIHandler,_RectaglePosX,_RectaglePosY) \
    GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->UpdateHookerPosistion(ITouchSrvPtr,_pIHandler,_RectaglePosX,_RectaglePosY)
#define ITOUCHSRV_QueryPointId(ITouchSrvPtr, x, y) \
    GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->QueryPointId(ITouchSrvPtr, x, y)

#define ITOUCHSRV_IsHookedByPosition(ITouchSrvPtr, pHandler, x, y) \
    GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->IsHookedByPosition(ITouchSrvPtr, pHandler,x, y)

#define ITOUCHSRV_IsHookedByPointId(ITouchSrvPtr, pHandler, nPointId) \
    GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->IsHookedByPointId(ITouchSrvPtr, pHandler,nPointId)

#define ITOUCHSRV_HookMultiTouochEvent(ITouchSrvPtr, pIHandler, x, y, nPointId,pContext) \
    GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->HookMultiTouchEvent(ITouchSrvPtr, pIHandler, x, y, nPointId, pContext)

#define ITOUCHSRV_UnHookMultiTouchEvent(ITouchSrvPtr, pIHandler, nPointId) \
    GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->UnHookMultiTouchEvent(ITouchSrvPtr, pIHandler, nPointId)

#define ITOUCHSRV_QueryNumOfFingerPressed(ITouchSrvPtr) \
	GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->QueryNumOfFingerPressed(ITouchSrvPtr)


/** ITOUCHSRV_QueryInterface
** @brief	This function queries another interface from ITouchSrv object.
**          It will return an interface object which you want to query if successful.
**
** @param[in]   ITouchSrvPtr(ITouchSrv*)    A pointer of ITouchSrv interface object.
** @param[in]   iid(MAE_IId)                An interface id to be queried.
** @param[out]  ppObj(void**)               A pointer of void pointer to retrieve an interface object which you want to query.
** @param[in]   pOwner(IBase*)              Shall be an IBase interface object to keep the return object.
**
** @retval	MAE_RET_SUCCESS         Success.
** @retval	MAE_RET_NOT_SUPPORTED   Failed. The queried interface id is not supported.
**/
#define ITOUCHSRV_QueryInterface(ITouchSrvPtr, iid, ppObj, pOwner) \
	GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->QueryInterface(ITouchSrvPtr,iid,ppObj,pOwner)

/** ITOUCHSRV_HandleEvent
** @brief	This function handles events which passed to this ITouchSrv object.
**
** @param[in]	ITouchSrvPtr(ITouchSrv*)  A pointer of ITouchSrv interface object.
** @param[in]	eid(MAE_EventId)          Event Id sent to the object.
** @param[in]	p1(u32)                   Parameter 1 of 32-bits specific data.
** @param[in]	p2(u32)                   Parameter 2 of 32-bits specific data.
**
** @retval	TRUE		The object handled this event.
** @retval	FALSE		The object did NOT handle this event.
**/
#define ITOUCHSRV_HandleEvent(ITouchSrvPtr,eid,p1,p2) \
	GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->HandleEvent(ITouchSrvPtr,eid,p1,p2)

/** ITOUCHSRV_HookEvent
** @brief	To hook touch screen events.
**          TouchSrv provides a registration mechanism for an IHandler object to
**          pass all touch screen events to this IHandler object. If this IHandler
**          object doesn't want to listen touch screen event anymore, call ITOUCHSRV_UnhookEvent()
**          to cancel registration.
**
** @param[in]	ITouchSrvPtr(ITouchSrv*)  A pointer of ITouchSrv interface object.
** @param[in]	pIHandler(IHandler*)      An IHandler object who want to hook touch screen events.
** @param[in]	x(s32)                    x coordinate on the screen of pIHandler object.
** @param[in]	y(s32)                    y coordinate on the screen of pIHandler object.
** @param[in]	pContext(IBase*)          Context to handle touch event.
**
** @retval
** @retval
**/
#define ITOUCHSRV_HookEvent(ITouchSrvPtr, pIHandler, x, y, pContext) \
	GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->HookEvent(ITouchSrvPtr, pIHandler, x, y, pContext)

/** ITOUCHSRV_UnhookEvent
** @brief	Unhook touch screen events.
**
** @param[in]	ITouchSrvPtr(ITouchSrv*)  A pointer of ITouchSrv interface object.
** @param[in]	pIHandler(IHandler*)      An IHandler object who want to cancel hooking touch screen events.
**
** @retval
** @retval
**/
#define ITOUCHSRV_UnhookEvent(ITouchSrvPtr, pIHandler) \
	GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->UnhookEvent(ITouchSrvPtr, pIHandler)


/** ITOUCHSRV_RegTsEventRect
** @brief	To register a rectangle for waiting touch event.
**
** @param[in]	ITouchSrvPtr(ITouchSrv*)  A pointer of ITouchSrv interface object.
** @param[in]	pRecipient(IHandler*)     A IHandler object to register rectangle.
** @param[in]	pRect(MAE_TS_Rect_st*)    rectangle.
**
** @retval
** @retval
**/
#define ITOUCHSRV_RegTsEventRect(ITouchSrvPtr, pRecipient, pRect) \
	GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->RegTsEvtRc(ITouchSrvPtr, pRecipient, pRect)

/** ITOUCHSRV_DeregTsEventRect
** @brief	To deregister a rectangle for waiting touch event.
**
** @param[in]	ITouchSrvPtr(ITouchSrv*)  A pointer of ITouchSrv interface object.
** @param[in]	pRecipient(IHandler*)     A IHandler object to register rectangle.
**
** @retval
** @retval
**/
#define ITOUCHSRV_DeregTsEventRect(ITouchSrvPtr, pRecipient) \
	GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->DeregTsEvtRc(ITouchSrvPtr, pRecipient)

/** ITOUCHSRV_SetPollingTime
** @brief	Set touchscreen polling time.
**
** @param[in]	ITouchSrvPtr(ITouchSrv*)  A pointer of ITouchSrv interface object.
** @param[in]	MSec(u16)                 Polling time in msec.
**
** @retval	None.
** @retval
**/
#define ITOUCHSRV_SetPollingTime(ITouchSrvPtr, MSec) \
	GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->SetPollingTime(ITouchSrvPtr, MSec)

#define ITOUCHSRV_SetPollingTimeFast(ITouchSrvPtr) \
	GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->SetPollingTime(ITouchSrvPtr, MAE_TS_POLLING_TIME_FAST)

#define ITOUCHSRV_SetPollingTimeMedium(ITouchSrvPtr) \
	GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->SetPollingTime(ITouchSrvPtr, MAE_TS_POLLING_TIME_MEDIUM)

#define ITOUCHSRV_SetPollingTimeSlow(ITouchSrvPtr) \
	GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->SetPollingTime(ITouchSrvPtr, MAE_TS_POLLING_TIME_SLOW)

/** ITOUCHSRV_TurnOnCalibration
** @brief	Set touchscreen to calibration mode, the message type will be different!
**
** @param[in]	ITouchSrvPtr(ITouchSrv*)      A pointer of ITouchSrv interface object.
**
** @retval	None.
** @retval
**/
#define ITOUCHSRV_TurnOnCalibration(ITouchSrvPtr) \
	GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->TurnOnCalibration(ITouchSrvPtr, TRUE)

/** ITOUCHSRV_TurnOffCalibration
** @brief	Set touchscreen to normal mode, the message type will be different from calibration mode.
**
** @param[in]	ITouchSrvPtr(ITouchSrv*)      A pointer of ITouchSrv interface object.
**
** @retval	None.
** @retval
**/
#define ITOUCHSRV_TurnOffCalibration(ITouchSrvPtr) \
	GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->TurnOnCalibration(ITouchSrvPtr, FALSE)

/** ITOUCHSRV_SetCalibrationData
** @brief	Set touchscreen calibration data.
**
** @param[in]	ITouchSrvPtr(ITouchSrv*)      A pointer of ITouchSrv interface object.
** @param[in]	pstCalbrData(MAE_TS_Calibration_st*)   Polling time in msec.
**
** @retval	None.
** @retval
**/
#define ITOUCHSRV_SetCalibrationData(ITouchSrvPtr, pstCalbrData) \
	GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->SetCalibrationData(ITouchSrvPtr, pstCalbrData)


/** ITOUCHSRV_SetCoordinateMode
** @brief	To set the coordinate mode for touch service.
**          The touch coordinate will be converted by different mode
**
** @param[in]	ITouchSrvPtr(ITouchSrv*)         A pointer of ITouchSrv interface object.
** @param[in]	TsCoorMode(MAETouchCoorMode_e)  Touch coordiante mode
**
** @retval  MAE_RET_SUCCESS
** @retval
**/
#define ITOUCHSRV_SetCoordinateMode(ITouchSrvPtr, TsCoorMode) \
	GET_FUNCTBL((ITouchSrvPtr),ITouchSrv)->SetCoordinateMode(ITouchSrvPtr, TsCoorMode)

/** ITOUCHSRV_DisableFingerCmdOnce
** @brief	Disable touch service to transfer finger command once.
**
** @param[in]	ITouchSrvPtr(ITouchSrv*)  A pointer of ITouchSrv interface object.
** @param[in]	CmdId_(MaeTsCmdId_e)     Touch Finger command id. Refer to MAETsCmdId_e.
**
** @retval
** @retval
**/
#define ITOUCHSRV_DisableFingerCmdOnce(ITouchSrvPtr, CmdId_) \
	ITOUCHSRV_HandleEvent(ITouchSrvPtr, MAE_EVT_SET_PROPERTY, TOUCHSRV_PROP_DISABLE_FINGER_CMD_ONCE, (MaeTsCmdId_e)(CmdId_))

/** ITOUCHSRV_DisableFingerCmd
** @brief	Always disable touch service to transfer finger command.
**
** @param[in]	ITouchSrvPtr(ITouchSrv*)  A pointer of ITouchSrv interface object.
** @param[in]	CmdId_(MaeTsCmdId_e)     Touch Finger command id. Refer to MAETsCmdId_e.
**
** @retval
** @retval
**/
#define ITOUCHSRV_DisableFingerCmd(ITouchSrvPtr, CmdId_) \
	ITOUCHSRV_HandleEvent(ITouchSrvPtr, MAE_EVT_SET_PROPERTY, TOUCHSRV_PROP_DISABLE_FINGER_CMD, (MaeTsCmdId_e)(CmdId_))

/** ITOUCHSRV_EnableFingerCmd
** @brief	Always enable touch service to transfer finger command.
**
** @param[in]	ITouchSrvPtr(ITouchSrv*)  A pointer of ITouchSrv interface object.
**
** @retval
** @retval
**/
#define ITOUCHSRV_EnableFingerCmd(ITouchSrvPtr) \
	ITOUCHSRV_HandleEvent(ITouchSrvPtr, MAE_EVT_SET_PROPERTY, TOUCHSRV_PROP_ENABLE_FINGER_CMD, 0)

/** ITOUCHSRV_EnableTS
** @brief	Stop touchscreen service
**
** @param[in]	ITouchSrvPtr(ITouchSrv*)  A pointer of ITouchSrv interface object.
**
** @retval
** @retval
**/
#define ITOUCHSRV_EnableTS(ITouchSrvPtr) \
	ITOUCHSRV_HandleEvent(ITouchSrvPtr, MAE_EVT_SET_PROPERTY, TOUCHSRV_PROP_ENABLE_TOUCH, 0)

/** ITOUCHSRV_DisableTS
** @brief	Start touchscreen service
**
** @param[in]	ITouchSrvPtr(ITouchSrv*)  A pointer of ITouchSrv interface object.
**
** @retval
** @retval
**/
#define ITOUCHSRV_DisableTS(ITouchSrvPtr) \
	ITOUCHSRV_HandleEvent(ITouchSrvPtr, MAE_EVT_SET_PROPERTY, TOUCHSRV_PROP_DISABLE_TOUCH, 0)

/** TOUCHSRV_GetTscrType
** @brief       Get touch screen type
**
** @param[out]  pTscrType: pointer to touch screen type enum
**
** @retval MAE_RET_SUCCESS   If successful.
**/
MAERet_t TOUCHSRV_GetTscrType(MAETscrType_e *pTscrType);

/** TOUCHSRV_GetResistance
** @brief       Get touch screen resistance
**
** @param[out]  pxResistance: x-axis resistance
** @param[out]  pyResistance: y-axis resistance
**
** @retval MAE_RET_SUCCESS   If successful.
**/
MAERet_t TOUCHSRV_GetResistance(u32 *pxResistance, u32 *pyResistance);
#endif /*__MMI_MAE_TOUCHSRV_H__*/

