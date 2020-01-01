#ifndef __MMI_SCHEDULERSRV_CB_H__
#define __MMI_SCHEDULERSRV_CB_H__

#include "mmi_schedulersrv_common.h"

/** call back prototype
* @brief        The call back function is registered when user sets one schedule.
*               Schedule will notify user by this call back function when the datetime expired.
*
*
* @param[in]    nCustomerID(SCHSRV_CustomerID)       CustomerID(user maintains).
* @param[in]    eCauseReason(SCHSRV_CAUSE_REASON_e)  Expired Cause.
* @param[Out]   pbNeedCofirm(boolean *)              Wait confirm or not.
*
* @retval       TRUE                                 Succeed.
* @retval       FALSE                                Failed.
*
*/

#if defined __MMI_SCHEDUERSRV_CB_C__
//for normal scheduler
#define DEFINE_DECLARE_BASE(a, b) \
	const SrvSchCBTable gSchSrv_CB_table[] = { b,
#define DEFINE_DECLARE(a, b) b,
#define DEFINE_DECLARE_END() };
#define DECLARE_NEW_SCHCB(_func_) extern boolean  _func_(SCHSRV_CustomerID nCustomerID, SCHSRV_CAUSE_REASON_e eCauseReason, boolean *pbNeedCofirm);

//for time change
#define DEFINE_TIMECHANGE_BASE(a) \
    const SrvSchTimeChangeCBTable gSchSrv_TC_CB_table[] = {  a,
#define DEFINE_TIMECHANGE(a) a,
#define DEFINE_TIMECHANGE_END() };
#define DECLARE_TIMECHANGE_CB(_func_) extern void _func_(void);

//for timezone change
#define DEFINE_TIMEZONECHANGE_BASE(a) \
    const SrvSchTimeZoneChangeCBTable gSchSrv_TZC_CB_table[] = {  a,
#define DEFINE_TIMEZONECHANGE(a) a,
#define DEFINE_TIMEZONECHANGE_END() };
#define DECLARE_TIMEZONECHANGE_CB(_func_) extern void _func_(void);

#else
//for normal scheduler
extern const SrvSchCBTable gSchSrv_CB_table[];

#define DEFINE_DECLARE_BASE(a, b) \
    typedef enum \
    { \
        a,

#define DEFINE_DECLARE(a, b) a,
#define DEFINE_DECLARE_END() }SCHSRV_CALLBACK_ENUM_e;
#define DECLARE_NEW_SCHCB(_func_)

//for time change
extern const SrvSchTimeChangeCBTable gSchSrv_TC_CB_table[];
#define DEFINE_TIMECHANGE_BASE(a) typedef enum { SCHSRV_##a = 0,
#define DEFINE_TIMECHANGE(a) SCHSRV_##a,
#define DEFINE_TIMECHANGE_END() SCHSRV_TIMECHANGE_CB_MAX} SCHSRV_TIMECHANGE_CB_e;
#define DECLARE_TIMECHANGE_CB(_func_)

//for timezone change
extern const SrvSchTimeZoneChangeCBTable gSchSrv_TZC_CB_table[];
#define DEFINE_TIMEZONECHANGE_BASE(a) typedef enum { SCHSRV_##a = 0,
#define DEFINE_TIMEZONECHANGE(a) SCHSRV_##a,
#define DEFINE_TIMEZONECHANGE_END() SCHSRV_TIMEZONECHANGE_CB_MAX} SCHSRV_TIMEZONECHANGE_CB_e;
#define DECLARE_TIMEZONECHANGE_CB(_func_)

#endif

/***************     Normal Scheduler    ********************/
DECLARE_NEW_SCHCB(Alarmsrv_HandleSchedule_CB)
DECLARE_NEW_SCHCB(Fmsrv_HandleSchedule_CB)
DECLARE_NEW_SCHCB(Offapp_HandleSchedule_CB)
DECLARE_NEW_SCHCB(Settingapp_HandleSchedule_CB)
//DECLARE_NEW_SCHCB(Test_Expire_CB)

DEFINE_DECLARE_BASE(SCHSRV_CB_ALARM, Alarmsrv_HandleSchedule_CB)
DEFINE_DECLARE(SCHSRV_CB_FMREC, Fmsrv_HandleSchedule_CB)
DEFINE_DECLARE(OFFAPP_CB_FACTORYPOWERON, Offapp_HandleSchedule_CB)
DEFINE_DECLARE(SETTINGAPP_CB_POWERONOFF, Settingapp_HandleSchedule_CB)
//DEFINE_DECLARE(SCHSRV_CB_TEST, Test_Expire_CB, SCHSRV_CB_FOR_ALL)
DEFINE_DECLARE_END()
/************************************************************/


/***************  Listen for time change  ********************/
DECLARE_TIMECHANGE_CB(FmSchSettingApp_TimeChange_CB)
DECLARE_TIMECHANGE_CB(SettingApp_TimeChange_CB)

//Notes: forbid to use NULL point
DEFINE_TIMECHANGE_BASE(FmSchSettingApp_TimeChange_CB)
DEFINE_TIMECHANGE(SettingApp_TimeChange_CB)
DEFINE_TIMECHANGE_END()
/************************************************************/

/***************  Listen for timezone change  ********************/
DECLARE_TIMEZONECHANGE_CB(FmSchSettingApp_TimeZoneChange_CB)
DECLARE_TIMEZONECHANGE_CB(SettingApp_TimeZoneChange_CB)

//Notes: forbid to use NULL point
DEFINE_TIMEZONECHANGE_BASE(FmSchSettingApp_TimeZoneChange_CB)
DEFINE_TIMEZONECHANGE(SettingApp_TimeZoneChange_CB)
DEFINE_TIMEZONECHANGE_END()
/************************************************************/

#undef DEFINE_DECLARE_BASE
#undef DEFINE_DECLARE
#undef DEFINE_DECLARE_END
#undef DECLARE_NEW_SCHCB
#undef DEFINE_TIMECHANGE_BASE
#undef DEFINE_TIMECHANGE
#undef DEFINE_TIMECHANGE_END
#undef DECLARE_TIMECHANGE_CB
#undef DEFINE_TIMEZONECHANGE_BASE
#undef DEFINE_TIMEZONECHANGE
#undef DEFINE_TIMEZONECHANGE_END
#undef DECLARE_TIMEZONECHANGE_CB

#endif /*__MMI_SCHEDULERSRV_CB_H__*/
