#ifndef __MMI_SCHEDULERSRV_COMMON_H__
#define __MMI_SCHEDULERSRV_COMMON_H__

#include "mmi_mae_common_def.h"

#define MMI_LEVEL_SCHSRV MMI_LEVEL_TESTAPP
#define SCHRV_DELAY_SECS 30

typedef u8  SCHSRV_PeriodicType;
typedef u16 SCHSRV_CustomerID;

#define SCHSRV_SCHTYPE_RTC_KIND            0x0000
#define SCHSRV_SCHTYPE_CLOCK_KIND        0x0100
#define SCHSRV_SCHTYPE_KIND_MASK          0xff00

/**
 * External Events
 */
#define SCHSRV_EVT_PowerOnConfirmInd                    (CLSID_SCHEDULERSRV << 16 | 1)
#define SCHSRV_EVT_ExceptionInd                             (CLSID_SCHEDULERSRV << 16 | 2)
#define SCHSRV_EVT_AutoPowerOnAlarmExpiredInd    (CLSID_SCHEDULERSRV << 16 | 3)

/***************************************************************************************/
//use case:
// 1. Application can't receive SCHSRV_CAUSE_CLOCK cause until phone comes into idle App.
//
// 2. Application always receives SCHSRV_CAUSE_POWERON cause before phone comes into idle App.
//

//From the point of implement side

//** trigger reason **            ** call cb with these types **
//SCHSRV_CAUSE_POWERON            SCHSRV_TYPE_AUTOPOWERON, SCHSRV_TYPE_RTC
//SCHSRV_CAUSE_TIMECHANGE         SCHSRV_TYPE_AUTOPOWERON, SCHSRV_TYPE_RTC, SCHSRV_TYPE_CLOCK
//SCHSRV_CAUSE_RTC                SCHSRV_TYPE_AUTOPOWERON, SCHSRV_TYPE_RTC,
//SCHSRV_CAUSE_CLOCK              SCHSRV_TYPE_CLOCK
//SCHSRV_CAUSE_TIMEZONECHANGE     SCHSRV_TYPE_AUTOPOWERON, SCHSRV_TYPE_RTC, SCHSRV_TYPE_CLOCK


//From the point of user side
//** type **                      ** trigger by these reason **
//SCHSRV_TYPE_AUTOPOWERON         SCHSRV_CAUSE_POWERON, SCHSRV_CAUSE_TIMECHANGE, SCHSRV_CAUSE_RTC, SCHSRV_CAUSE_TIMEZONECHANGE
//SCHSRV_TYPE_RTC	                SCHSRV_CAUSE_POWERON, SCHSRV_CAUSE_TIMECHANGE, SCHSRV_CAUSE_RTC, SCHSRV_CAUSE_TIMEZONECHANGE
//SCHSRV_TYPE_CLOCK               SCHSRV_CAUSE_TIMECHANGE, SCHSRV_CAUSE_CLOCK, SCHSRV_CAUSE_TIMEZONECHANGE
/***************************************************************************************/

typedef enum SCHSRV_SCHEDULE_TYPE_TAG
{
    SCHSRV_TYPE_AUTOPOWERON = SCHSRV_SCHTYPE_RTC_KIND, /* Auto power on: special case*/
    SCHSRV_TYPE_FACTORYPOWERON,               /*trigger by rtc: special case for factory*/
    SCHSRV_TYPE_RTC,                                   /* trigger by rtc: it still works even if device is power-off */
    SCHSRV_TYPE_CLOCK = SCHSRV_SCHTYPE_CLOCK_KIND,     /* trigger by clock: it only works if system runs */
} SCHSRV_SCHEDULE_TYPE_e;

typedef enum SCHSRV_CAUSE_REASON_TAG
{
    SCHSRV_CAUSE_POWERON,               /* trigger by rtc from power-off status */
    SCHSRV_CAUSE_TIMECHANGE,          /* trigger by Time Change reason */
    SCHSRV_CAUSE_RTC,                       /* tringer by normal RTC */
    SCHSRV_CAUSE_CLOCK,                   /* trigger by clock event */
    SCHSRV_CAUSE_MAX
} SCHSRV_CAUSE_REASON_e;

#define SCHSRV_FREQUENCY_DAILY               (0x7F)
#define SCHSRV_FREQUENCY_SUNDAY             (0x40)  // 0x01 << 6
#define SCHSRV_FREQUENCY_SATURDAY          (0x20) // 0x01 << 5
#define SCHSRV_FREQUENCY_FRIDAY             (0x10)  // 0x01 << 4
#define SCHSRV_FREQUENCY_THURSDAY         (0x08)  // 0x01 << 3
#define SCHSRV_FREQUENCY_WEDNESDAY       (0x04)  // 0x01 << 2
#define SCHSRV_FREQUENCY_TUESDAY           (0x02)   // 0x01 << 1
#define SCHSRV_FREQUENCY_MONDAY             (0x01)   // 0x01 << 0
#define SCHSRV_FREQUENCY_ONCE                (0x00)

//pbNeedCofirm: FALSE(default value)
//If application want to wait user response, you can set pbNeedCofirm to TRUE.
//System will call the callback registered by App if all confirms are received from application.
//Currently we only implement confirm mechanism on power on procedure.
typedef boolean (*SrvSchScheduleCB)(SCHSRV_CustomerID nCustomerID, SCHSRV_CAUSE_REASON_e eCauseReason, boolean *pbNeedCofirm);

typedef void (*SrvSchTimeChangeCB) (void);
typedef void (*SrvSchTimeZoneChangeCB) (void);

typedef struct
{
    SrvSchScheduleCB pCB;
}SrvSchCBTable;

typedef struct
{
    SrvSchTimeChangeCB pCB;
}SrvSchTimeChangeCBTable;

typedef struct
{
    SrvSchTimeZoneChangeCB pCB;
}SrvSchTimeZoneChangeCBTable;

#define LOPRIORITY_BASE 0x10
#define HIPRIORITY_BASE 0x20

typedef enum
{
    SCHSRV_CONFIRM_DISABLE = 0, //disable confirm mechanism
    SCHSRV_CONFIRM_ENABLE,        //enable confirm mechanism
    SCHSRV_CONFIRM_POWEROFF = LOPRIORITY_BASE,
    SCHSRV_CONFIRM_POWERON,
    SCHSRV_CONFIRM_SHOWDIALOG,
    SCHSRV_CONFIRM_FORCE_POWEROFF = HIPRIORITY_BASE,
    SCHSRV_CONFIRM_FORCE_POWERON,
    SCHSRV_CONFIRM_FORCE_SHOWDIALOG,
}SCHSRV_CONFIRM_CAUSE_e;

typedef enum
{
    SCHSRV_EXCEPTION_NOAVAILABLE_SLOT,          //schedule slot is full
    SCHSRV_EXCEPTION_ILLEGAL_ARGUMENT,          //illegal argument
}SCHSRV_EXCEPTION_CAUSE_e;

typedef enum
{
    SCHSRV_Notify_Mask_PowerOnConfirm = 0x000001,
    SCHSRV_Notify_Mask_Exception = 0x000002,
    SCHSRV_Notify_Mask_AutoPowerOnAlarmExpired = 0x000003,
} SCHSRV_NOTIFY_MASK_e;

#endif /*__MMI_SCHEDULERSRV_COMMON_H__*/

