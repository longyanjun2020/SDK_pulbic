#if !defined(__MSMNOTIFY_H__)
#define __MSMNOTIFY_H__

#include "msmdrv.h"
#include "msmglobal.h"
#include "msmcomm.h"


#define MSM_NOTIFICATION_CONFIGS(devCh_sp)   (FALSE != checkNotifyConfigs(devCh_sp))
#define MSM_NOTIFICATION_CONFIGS_ADDR(devCh_sp)   getNotifyConfigsAddr(devCh_sp)
#define MSM_NOTIFICATION_CONFIGS_SIZE(devCh_sp)   getNotifyConfigsSize(devCh_sp)

struct DevNotify_s;
struct DevCallBack_s_;
struct DevNotify_s_;

typedef struct DevCallBack_s_
{
    struct DevCallBack_s_   *prev;   /* link field */
    struct DevCallBack_s_   *next;   /* link field */
    struct DevNotify_s      *ownerId_sp; /* pointer to Identifier */
    U32                     alloc_n;
    MSMNotify               notifyCallBack_fxp;
    U32                     userData_n;
    U32                     signature;
} DevCallBack_s;


typedef Boolean (*DevNotifyHandler)
(
    struct DevNotify_s_     *devNotify_sp,
    U16     *status_na
);

typedef struct DevNotify_s_
{
    DevCallBack_s           cbList_s;   /* head of the callback list */
    MSMNotification_e       notifyID_e;
    DevNotifyHandler        devNofity_fxp;
    U16                     intEvent_n;
    U16                     cause_n;
} DevNotify_s;


#endif /* __MSMNOTIFY_H__ */
