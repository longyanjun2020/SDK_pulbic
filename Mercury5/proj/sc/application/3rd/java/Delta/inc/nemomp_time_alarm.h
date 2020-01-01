#ifndef __NEMOMP_TIME_ALARM_H__
#define __NEMOMP_TIME_ALARM_H__

typedef struct nm_alarm_entry_t
{
    struct nm_alarm_entry_t *next;

    nm_char *midlet;
    nm_char *storagename;
    nm_int32 midletid;
    nm_int64 wakeup;
    nm_int32 executed;
    nm_int32 timer_id;

} nm_alarm_entry;

extern nm_alarm_entry *gpAlarmList;
extern nm_int32 gAlarmCount;

extern nm_int32 nemomp_alarm_add(nm_char *str, nm_int64 alarm, nm_int64 *lastalarm);
extern nm_int32 nemomp_alarm_open(void);
extern void nemomp_alarm_free(void);
extern nm_int32 nemomp_alarm_del(nm_alarm_entry *del_alarm);
extern nm_int64 nemomp_alarm_check(nm_int64 time);
extern void nemomp_alarm_deletesuite(char *storge); // 20090114: Added

#endif /* __NEMOMP_TIME_ALARM_H__ */
