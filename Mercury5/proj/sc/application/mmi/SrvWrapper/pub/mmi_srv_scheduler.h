/**
* @file    mmi_srv_scheduler.h
* @brief
*
*/

#ifndef __MMI_SRV_SCHEDULER_H__
#define __MMI_SRV_SCHEDULER_H__


#include "mmi_srv_client_commondefine.h"
#include "mmi_schedulersrv_common.h"
#include "mmi_schedulersrv_cb.h"

/** Call back prototyp
* @brief        Notify the confirm reason.
*
*
* @param[in]    pInstance(void *)                      Applet instance.
* @param[in]    eConfirm(SCHSRV_CONFIRM_CAUSE_e)       Confirm reason.
* @param[in]    nRemainConfirmNum(u32)                 Remain confirm numbers.
*
* @retval       MAE_RET_SUCCESS                        Succeed.
* @retval       MAE_RET_FAILED                         Failed.
*
*/
typedef void (*SrvSchExpiredConfirmCB)(void *pInstance, SCHSRV_CONFIRM_CAUSE_e eConfirm, u32 nRemainConfirmNum);

typedef void (*SrvSchExceptionCB)(void *pInstance, SCHSRV_EXCEPTION_CAUSE_e eException);

typedef void (*SrvSchAutoPowerOnAlarmExpiredCB)(void *pInstance);

//Notes: These Interfaces only are used by applet
// If services need these, please directly use scheduler service interface.
// For example, SCHSRV_SetSchedule()

/** SrvSchSetSchedule
* @brief        To set one schedule. It must replace the schedule with the same class id and customer id
*               The past datetime is not allowed.
*
*
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
MAE_Ret SrvSchSetSchedule(MAE_ClsId nClsId,
                            SCHSRV_CustomerID nCustomerID,
                            SCHSRV_SCHEDULE_TYPE_e eScheduleType,
                            MAE_DateTime_t *ptLocalDateTime,
                            SCHSRV_PeriodicType nPeriod,
                            SCHSRV_CALLBACK_ENUM_e eCallback);

/** SrvSchCancelSchedule
* @brief        To cancel the schedule.
*
*
* @param[in]    nClsId(MAE_ClsId)                      Class Id.
* @param[in]    nCustomerID(SCHSRV_CustomerID)         CustomerID.(User self maintains)
*
* @retval       MAE_RET_SUCCESS                        Succeed.
* @retval       MAE_RET_FAILED                         Failed.
*
*/
MAE_Ret SrvSchCancelSchedule(MAE_ClsId nClsId, SCHSRV_CustomerID nCustomerID);

/** SrvSchExpired
* @brief        To notify special cause for all expired schedules.
*
*
* @param[in]    eCauseReason(SCHSRV_CAUSE_REASON_e)    The specific cause.
*
* @retval       MAE_RET_SUCCESS                        Succeed.
* @retval       MAE_RET_FAILED                         Failed.
*
*/
MAE_Ret SrvSchExpired(SCHSRV_CAUSE_REASON_e eCauseReason);

/** SrvSchIsExpiredBySepcialType
* @brief        To check if this special type exists with expired schedule.
*
*
* @param[in]    eScheduleType(SCHSRV_SCHEDULE_TYPE_e)  The specific type.
*
* @retval       TRUE                                   Succeed.
* @retval       FALSE                                  Failed.
*
*/
boolean SrvSchIsExpiredBySepcialType(SCHSRV_SCHEDULE_TYPE_e eScheduleType);

/** SrvSchSuspendSchedule
* @brief        To suspend the schedule.
*
*
* @retval       MAE_RET_SUCCESS                        Succeed.
* @retval       MAE_RET_FAILED                         Failed.
*
*/
MAE_Ret SrvSchSuspendSchedule(void);

/** SrvSchResumeSchedule
* @brief        To resume the schedule.
*
*
* @retval       MAE_RET_SUCCESS                        Succeed.
* @retval       MAE_RET_FAILED                         Failed.
*
*/
MAE_Ret SrvSchResumeSchedule(void);

/** SrvSchResetScheduleDB
* @brief        To reset the database of the schedule.
*
*
* @retval       MAE_RET_SUCCESS                        Succeed.
* @retval       MAE_RET_FAILED                         Failed.
*
*/
MAE_Ret SrvSchResetScheduleDB(void);

/** SrvSchFireSpecialExpired
* @brief        To trigger special type in schedule which has expired.
*
*
* @param[in]    eCauseReason(SCHSRV_CAUSE_REASON_e)    Schedule cause.
* @param[in]    eScheduleType(SCHSRV_SCHEDULE_TYPE_e)  Schedule type.
*
* @retval       MAE_RET_SUCCESS                        Succeed.
* @retval       MAE_RET_FAILED                         Failed.
*
* @Notes        This API is specail; Now it is only for the cause SCHSRV_CAUSE_POWERON and support for SCHSRV_TYPE_AUTOPOWERON and SCHSRV_TYPE_FACTORYPOWERON
*/
MAE_Ret SrvSchFireSpecialExpired(SCHSRV_CAUSE_REASON_e eCauseReason, SCHSRV_SCHEDULE_TYPE_e eScheduleType);

/** SrvSchSetExpiredConfirmCB
* @brief        Register call back function to listen the confirm event which is triggered if all acknowleges are confirmed or high priority acknowlege is confirmed.
*
*
* @param[in]    pfnCallBack(SrvSchExpiredConfirmCB)                 Call back function.
*
* @retval       MAE_RET_SUCCESS                                     Succeed.
* @retval       MAE_RET_FAILED                                      Failed.
*
*/
MAE_Ret SrvSchSetExpiredConfirmCB(SrvSchExpiredConfirmCB pfnCallBack);

//no use
MAE_Ret SrvSchSetExceptionCB(SrvSchExceptionCB pfnCallBack);

/** SrvSchSetAutoPowerOnAlarmExpiredCB
* @brief        Register call back function to listen the expire event from auto power-on.
*
*
* @param[in]    pfnCallBack(SrvSchAutoPowerOnAlarmExpiredCB)        Call back function.
*
* @retval       MAE_RET_SUCCESS                                     Succeed.
* @retval       MAE_RET_FAILED                                      Failed.
*
*/
MAE_Ret SrvSchSetAutoPowerOnAlarmExpiredCB(SrvSchAutoPowerOnAlarmExpiredCB pfnCallBack);

/** SrvSchConfirmCause
* @brief        If we need to wait all response from app/service which is triggered by schedule,
*               App/Service can utilize this confirm mechanism to tell scheduler that he has done.
*
*
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
MAE_Ret SrvSchConfirmCause(SCHSRV_CONFIRM_CAUSE_e eConfirm);

#endif /*__MMI_SRV_SCHEDULER_H__*/
