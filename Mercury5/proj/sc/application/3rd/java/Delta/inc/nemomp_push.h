#ifndef __NEMOMP_PUSH_H__
#define __NEMOMP_PUSH_H__

#include "nemomp_time_alarm.h"
#include "nemomp_push_conn.h"

#define NM_PUSH_MAX_REGISTRY		(10)
#define NM_MAX_PUSH_LINE			(512)

#define ALARM_LIST_FILENAME	"alarmlist.txt"
#define PUSH_LIST_FILENAME		"pushlist.txt"

typedef enum
{
	NM_PUSH_ALARM_TYPE,
	NM_PUSH_SMS_TYPE,
	NM_PUSH_MMS_TYPE,
	NM_PUSH_TYPE_TOTAL
} nm_push_type_enum;

extern nm_int32 gPushLength;

extern void nemomp_alarm_timeout_callback(void *param_ptr);
extern nm_int32 nemomp_alarm_set_timer(nm_alarm_entry *entry_ptr, nm_int64 alarmtime);
extern void nemomp_alarm_cancel(nm_int32 timer_handle);

extern void nemomp_push_enable(nm_bool enable);

#endif /* __NEMOMP_PUSH_H__ */
