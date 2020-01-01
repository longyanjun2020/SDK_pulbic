/**
 * @file mmi_alarmsrv_cls.h
 *
 * This header file defines the class definition of AlarmSrv
 *
 * @version $Id: mmi_alarmsrv_cls.h 13300 2008-08-15 08:19:15Z johnson.yeh $ 
 */

#ifndef __MMI_ALARMSRV_CLS_H__
#define __MMI_ALARMSRV_CLS_H__

#include "mmi_mae_common_def.h"
#include "mmi_alarmsrv.h"

typedef enum
{
    MMI_ALARM_NORMAL = 0
  , ///< Normal alarm, means that the phone is already power on and receives an alarm message 
    MMI_ALARM_POWERON     ///< The phone is off, and it is turned on because of the alarm message 
} ALARMSRV_TYPE_e;

/**
 *  @brief  When timer expired, post MAE_EVT_ALARM to the applet which set alarm before. If the applet is not started yet,
 *          it would be started. Afterward, trigger next alarm.
 *  @param  pAlarm  The instance of IAlarm
 *  @param  alarmType MAE_ALARM_NORMAL  Normal alarm, means that the phone is already power on and receives an alarm message 
 *                    MAE_ALARM_POWERON The phone is off, and it is turned on because of the alarm message.
 *  @param  usercode  Only valid if alarmType = MAE_ALARM_POWERON. It is used for passing event code out. Caller could take it
 *                    and send to the poweron application.
 *  @retval MAE_RET_FAILED      The entry number in MAEAlarm is 0.
 *  @retval MAE_RET_BAD_PARAM   Unknown alarmType or usercode is NULL.
 */
MAE_Ret ALARMSRV_Expired(IALARMSRV *pIALARMSRV, ALARMSRV_TYPE_e alarmType, u32 *usercode);


#endif /* __MMI_ALARMSRV_CLS_H__ */
