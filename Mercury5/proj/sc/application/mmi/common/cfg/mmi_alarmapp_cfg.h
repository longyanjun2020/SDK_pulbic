

#ifndef __MMI_ALARMAPP_CFG__H__
#define __MMI_ALARMAPP_CFG__H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_filemgr.h"

#define ALARM_RECORDS_MAX_NUM (6)
#define ALARM_TITLE_TEXT_MAX_CHAR (21)
enum
{
    ALARM_FREQUENCY_DAILY=0x7F,
    ALARM_FREQUENCY_SUNDAY=0x40,
    ALARM_FREQUENCY_SATURDAY=0x20,
    ALARM_FREQUENCY_FRIDAY=0x10,
    ALARM_FREQUENCY_THURSDAY=0x08,
    ALARM_FREQUENCY_WEDNESDAY=0x04,
    ALARM_FREQUENCY_TUESDAY=0x02,
    ALARM_FREQUENCY_MONDAY=0x01,
    ALARM_FREQUENCY_ONCE=0x00
};
typedef u8 ALARM_FREQUENCY_e;
enum
{
    ALARM_STATUS_OFF=0,
    ALARM_STATUS_ON=1
};
typedef u8 ALARM_STATUS_e;
typedef struct _ALARM_RECORD_t
{
    u32 nTime;
    MAE_WChar Title[ALARM_TITLE_TEXT_MAX_CHAR];
    ALARM_STATUS_e eStatus;
    ALARM_FREQUENCY_e eFrequency;
    u8 nSnoozeCount;
    MAE_WChar stRingToneURL[FILEMGR_MAX_FILEPATH_SIZE];
} ALARM_RECORD_t;
#ifdef __APP_MMI_SOHU_UPDATER__
typedef enum ALARM_SOHU_FREQUENCY_TAG
{
    ALARM_SOHU_FREQUENCY_DAILY=0x08,
    ALARM_SOHU_FREQUENCY_WEEKLY=0x04,
    ALARM_SOHU_FREQUENCY_HALFMONTHLY=0x02,
    ALARM_SOHU_FREQUENCY_MONTHLY=0x01,
    ALARM_SOHU_FREQUENCY_NEVER=0x00
}ALARM_SOHU_FREQUENCY_e;


#define SOHU_RECORDS_MAX_NUM (1)
typedef struct _SOHU_ENTITY_t
{
    ALARM_STATUS_e eStatus;
    u32 nAlarmSrvStartDatetime;  //for alarm srv
    ALARM_SOHU_FREQUENCY_e eFrequency;
} SOHU_ENTITY_t;

#define CONFIG_NAMR_SOHU_UPDATE_LIST  CONFIG_DEFINE(CFGIT_SOHU_UPDATE_LIST, SOHU_ENTITY_t, SOHU_RECORDS_MAX_NUM, { ALARM_STATUS_OFF/*eStatus*/, 0/*nStartDatetime*/, ALARM_SOHU_FREQUENCY_NEVER/*eFrequency*/}/*FMSCH_RecordList*/)

#endif





// NAMR : Not Allow Master Reset
//#define CONFIG_DEFINE(cfgId, type, name, value)
//alarm
#define CONFIG_NAMR_ALARM_RECORD_LIST  CONFIG_DEFINE(CFGIT_ALARM_RECORD_LIST, ALARM_RECORD_t, ALARM_RECORDS_MAX_NUM, \
{{0/*nTime*/, {L""}/*Title*/, 0/*eStatus*/, ALARM_FREQUENCY_DAILY/*eFrequency*/, 0/*nSnoozeCount*/, {L""}/*stRingToneURL*/},\
 {0/*nTime*/, {L""}/*Title*/, 0/*eStatus*/, ALARM_FREQUENCY_DAILY/*eFrequency*/, 0/*nSnoozeCount*/, {L""}/*stRingToneURL*/},\
 {0/*nTime*/, {L""}/*Title*/, 0/*eStatus*/, ALARM_FREQUENCY_DAILY/*eFrequency*/, 0/*nSnoozeCount*/, {L""}/*stRingToneURL*/},\
 {0/*nTime*/, {L""}/*Title*/, 0/*eStatus*/, ALARM_FREQUENCY_DAILY/*eFrequency*/, 0/*nSnoozeCount*/, {L""}/*stRingToneURL*/},\
 {0/*nTime*/, {L""}/*Title*/, 0/*eStatus*/, ALARM_FREQUENCY_DAILY/*eFrequency*/, 0/*nSnoozeCount*/, {L""}/*stRingToneURL*/},\
 {0/*nTime*/, {L""}/*Title*/, 0/*eStatus*/, ALARM_FREQUENCY_DAILY/*eFrequency*/, 0/*nSnoozeCount*/, {L""}/*stRingToneURL*/}}/*AlarmRecordList*/)
//alarm end


#define ALARMAPP_NAMR_ALL_CONFIG \
                CONFIG_NAMR_ALARM_RECORD_LIST



#endif  //__MMI_ALARMAPP_CFG__H__




