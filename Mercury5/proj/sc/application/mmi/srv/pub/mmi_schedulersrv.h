/**
* @file mmi_schedulersrv.h
*
* Class Id: CLSID_SCHEDULERSRV
*
* @version $Id$
*/

#ifndef __MMI_SCHEDULERSRV_H__
#define __MMI_SCHEDULERSRV_H__

/*-------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
#include "mmi_schedulersrv_common.h"
#include "mmi_schedulersrv_cb.h"

/**
 * ISCHEDULERSRV Interfaces
 */
#define INHERIT_ISCHEDULERSRV(IName) \
    INHERIT_IHandler(IName)

DEFINE_INTERFACE(ISCHEDULERSRV);

//#define ISCHEDULER_QueryInterface(pICntlr, id, pp, po)         GET_FUNCTBL((pICntlr), ISCHEDULERSRV)->QueryInterface(pICntlr, id, pp, po)
//#define ISCHEDULER_HandleEvent(pICntlr, e, p1, p2)             GET_FUNCTBL((pICntlr), ISCHEDULERSRV)->HandleEvent(pICntlr, e, p1, p2)

MAE_Ret SCHSRV_New(MAE_ClsId nId, void **ppObj);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Scheduler Service interface
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/** SCHSRV_Expired
* @brief        To notify special cause for all expired schedules.
*
*
* @param[in]    pISchSrvObj(ISCHEDULERSRV*)            A pointer of ISCHEDULERSRV object.
* @param[in]    eCauseReason(SCHSRV_CAUSE_REASON_e)    The specific cause.
*
* @retval       MAE_RET_SUCCESS                        Succeed.
* @retval       MAE_RET_FAILED                         Failed.
*
*/
MAE_Ret SCHSRV_Expired(ISCHEDULERSRV *pISchSrvObj, SCHSRV_CAUSE_REASON_e eCauseReason);

/** SCHSRV_IsExpiredBySepcialType
* @brief        To check if this special type exists with expired schedule.
*
*
* @param[in]    pISchSrvObj(ISCHEDULERSRV*)            A pointer of ISCHEDULERSRV object.
* @param[in]    eScheduleType(SCHSRV_SCHEDULE_TYPE_e)  The specific type.
*
* @retval       TRUE                                   Succeed.
* @retval       FALSE                                  Failed.
*
*/
boolean SCHSRV_IsExpiredBySepcialType(ISCHEDULERSRV *pISchSrvObj, SCHSRV_SCHEDULE_TYPE_e eScheduleType);

/** SCHSRV_SetSchedule
* @brief        To set one schedule. It must replace the schedule with the same class id and customer id
*               The past datetime is not allowed.
*
*
* @param[in]    pISchSrvObj(ISCHEDULERSRV*)            A pointer of ISCHEDULERSRV object.
* @param[in]    nClsId(MAE_ClsId)                      Class Id.
* @param[in]    nCustomerID(SCHSRV_CustomerID)         CustomerID.(User self maintains)
* @param[in]    eScheduleType(SCHSRV_SCHEDULE_TYPE_e)  The specific type that user registers.
* @param[in]    ptLocalDateTime(MAE_DateTime_t)        The datetime that scheduler notify user on.
* @param[in]    nPeriod(SCHSRV_PeriodicType)           The periodic schedule.
* @param[in]    eCallback(SCHSRV_CALLBACK_ENUM_e)      The callback function.
*
* @retval       MAE_RET_SUCCESS                        Succeed.
* @retval       MAE_RET_FAILED                         Failed.
*
*/
MAE_Ret SCHSRV_SetSchedule(ISCHEDULERSRV *pISchSrvObj,
                            MAE_ClsId nClsId,
                            SCHSRV_CustomerID nCustomerID,
                            SCHSRV_SCHEDULE_TYPE_e eScheduleType,
                            MAE_DateTime_t *ptLocalDateTime,
                            SCHSRV_PeriodicType nPeriod,
                            SCHSRV_CALLBACK_ENUM_e eCallback);

/** SCHSRV_CancelSchedule
* @brief        To cancel the schedule.
*
*
* @param[in]    pISchSrvObj(ISCHEDULERSRV*)            A pointer of ISCHEDULERSRV object.
* @param[in]    nClsId(MAE_ClsId)                      Class Id.
* @param[in]    nCustomerID(SCHSRV_CustomerID)         CustomerID.(User self maintains)
*
* @retval       MAE_RET_SUCCESS                        Succeed.
* @retval       MAE_RET_FAILED                         Failed.
*
*/
MAE_Ret SCHSRV_CancelSchedule(ISCHEDULERSRV* pISchSrvObj, MAE_ClsId nClsId, SCHSRV_CustomerID nCustomerID);

/** SCHSRV_SuspendSchedule
* @brief        To suspend the schedule.
*
*
* @param[in]    pISchSrvObj(ISCHEDULERSRV*)            A pointer of ISCHEDULERSRV object.
*
* @retval       MAE_RET_SUCCESS                        Succeed.
* @retval       MAE_RET_FAILED                         Failed.
*
*/
MAE_Ret SCHSRV_SuspendSchedule(ISCHEDULERSRV* pISchSrvObj);

/** SCHSRV_ResumeSchedule
* @brief        To resume the schedule.
*
*
* @param[in]    pISchSrvObj(ISCHEDULERSRV*)            A pointer of ISCHEDULERSRV object.
*
* @retval       MAE_RET_SUCCESS                        Succeed.
* @retval       MAE_RET_FAILED                         Failed.
*
*/
MAE_Ret SCHSRV_ResumeSchedule(ISCHEDULERSRV* pISchSrvObj);

/** SCHSRV_ResetScheduleDB
* @brief        To reset the database of the schedule.
*
*
* @param[in]    pISchSrvObj(ISCHEDULERSRV*)            A pointer of ISCHEDULERSRV object.
*
* @retval       MAE_RET_SUCCESS                        Succeed.
* @retval       MAE_RET_FAILED                         Failed.
*
*/
MAE_Ret SCHSRV_ResetScheduleDB(ISCHEDULERSRV* pISchSrvObj);

/** SCHSRV_FireSpecialExpired
* @brief        To trigger special type in schedule which has expired.
*
*
* @param[in]    pISchSrvObj(ISCHEDULERSRV*)            A pointer of ISCHEDULERSRV object.
* @param[in]    eCauseReason(SCHSRV_CAUSE_REASON_e)    Schedule cause.
* @param[in]    eScheduleType(SCHSRV_SCHEDULE_TYPE_e)  Schedule type.
*
* @retval       MAE_RET_SUCCESS                        Succeed.
* @retval       MAE_RET_FAILED                         Failed.
*
* @Notes        This API is specail; Now it is only for the cause SCHSRV_CAUSE_POWERON and support for SCHSRV_TYPE_AUTOPOWERON and SCHSRV_TYPE_FACTORYPOWERON
*/
MAE_Ret SCHSRV_FireSpecialExpired(ISCHEDULERSRV *pISchSrvObj, SCHSRV_CAUSE_REASON_e eCauseReason, SCHSRV_SCHEDULE_TYPE_e eScheduleType);

/** SCHSRV_RegisterNotification
* @brief        To register the notificatin.
*
*
* @param[in]    pISchSrvObj(ISCHEDULERSRV*)            A pointer of ISCHEDULERSRV object.
* @param[in]    pInstance(void*)                       An instance to listen for notification.
* @param[in]    mask(SCHSRV_NOTIFY_MASK_e)             Special mask for the notification.
*
* @retval       MAE_RET_SUCCESS                        Succeed.
* @retval       MAE_RET_FAILED                         Failed.
*
*/
MAE_Ret SCHSRV_RegisterNotification(ISCHEDULERSRV *pISchSrvObj, void *pInstance, SCHSRV_NOTIFY_MASK_e mask);

/** SCHSRV_DeRegisterNotification
* @brief        To de-register the notificatin.
*
*
* @param[in]    pISchSrvObj(ISCHEDULERSRV*)            A pointer of ISCHEDULERSRV object.
* @param[in]    pInstance(void*)                       An instance to listen for notification.
* @param[in]    mask(SCHSRV_NOTIFY_MASK_e)             Special mask for the notification.
*
* @retval       MAE_RET_SUCCESS                        Succeed.
* @retval       MAE_RET_FAILED                         Failed.
*
*/
MAE_Ret SCHSRV_DeRegisterNotification(ISCHEDULERSRV *pISchSrvObj, void *pInstance, SCHSRV_NOTIFY_MASK_e mask);

/** SCHSRV_ConfirmCause
* @brief        If we need to wait all response from app/service which is triggered by schedule,
*               App/Service can utilize this confirm mechanism to tell scheduler that he has done.
*
*
* @param[in]    pISchSrvObj(ISCHEDULERSRV*)            A pointer of ISCHEDULERSRV object.
* @param[in]    eConfirm(SCHSRV_CONFIRM_CAUSE_e)       Confirm cuase.
*
* @retval       MAE_RET_SUCCESS                        Succeed.
* @retval       MAE_RET_FAILED                         Failed.
*
* @note         Currently this mechanism only uses during Power-On state.
*               App/Service must notify scheduler that he need to wait the response in call back function.
*               Please see the description of the callback prototype in mmi_schedulersrv_cb.h
*
*/
MAE_Ret SCHSRV_ConfirmCause(ISCHEDULERSRV *pISchSrvObj, SCHSRV_CONFIRM_CAUSE_e eConfirm);

/*-------------------------------------------------------------------------*/
#endif /* __MMI_SCHEDULERSRV_H__ */
