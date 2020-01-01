

#ifndef __MMI_FMSCH_CFG__H__
#define __MMI_FMSCH_CFG__H__

#include "mmi_alarmapp_cfg.h"
#include "mmi_fmradioapp_cfg.h"
#define FMRECSCH_RECORDS_MAX_NUM (6)
#define FMSCH_RECORDS_MAX_NUM (6)

typedef struct _FMRECSCH_ENTITY_t
{
    u32 nChannelFreq;
    ALARM_STATUS_e eStatus;
    u32 nAlarmSrvStartDatetime;  //for alarm srv
    u32 nStartDatetime;
    u32 nEndtime;
    ALARM_FREQUENCY_e eFrequency;
    VOICE_RECORD_Type_e eRecordType;
    FM_Record_Storage_e eStorage;
    boolean bAppendRecord;
    u32 urlHashId;
} FMRECSCH_ENTITY_t;

typedef struct _FMSCH_ENTITY_t
{
    u32 nChannelFreq;
    ALARM_STATUS_e eStatus;
    u32 nStartDatetime;
    ALARM_FREQUENCY_e eFrequency;
} FMSCH_ENTITY_t;

// NAMR : Not Allow Master Reset
//#define CONFIG_DEFINE(cfgId, type, name, value)
//alarm
#define CONFIG_NAMR_FMSCH_RECORD_LIST  CONFIG_DEFINE(CFGIT_FMSCH_RECORD_LIST, FMSCH_ENTITY_t, FMSCH_RECORDS_MAX_NUM, \
{{FMR_CHANNEL_FREQ_EMPTY/*nChannelFreq*/, ALARM_STATUS_OFF/*eStatus*/, 0/*nStartDatetime*/, ALARM_FREQUENCY_DAILY/*eFrequency*/},\
{FMR_CHANNEL_FREQ_EMPTY/*nChannelFreq*/, ALARM_STATUS_OFF/*eStatus*/, 0/*nStartDatetime*/, ALARM_FREQUENCY_DAILY/*eFrequency*/},\
{FMR_CHANNEL_FREQ_EMPTY/*nChannelFreq*/, ALARM_STATUS_OFF/*eStatus*/, 0/*nStartDatetime*/, ALARM_FREQUENCY_DAILY/*eFrequency*/},\
{FMR_CHANNEL_FREQ_EMPTY/*nChannelFreq*/, ALARM_STATUS_OFF/*eStatus*/, 0/*nStartDatetime*/, ALARM_FREQUENCY_DAILY/*eFrequency*/},\
{FMR_CHANNEL_FREQ_EMPTY/*nChannelFreq*/, ALARM_STATUS_OFF/*eStatus*/, 0/*nStartDatetime*/, ALARM_FREQUENCY_DAILY/*eFrequency*/},\
{FMR_CHANNEL_FREQ_EMPTY/*nChannelFreq*/, ALARM_STATUS_OFF/*eStatus*/, 0/*nStartDatetime*/, ALARM_FREQUENCY_DAILY/*eFrequency*/}}/*FMSCH_RecordList*/)

#define CONFIG_NAMR_FMRECSCH_RECORD_LIST  CONFIG_DEFINE(CFGIT_FMRECSCH_RECORD_LIST, FMRECSCH_ENTITY_t, FMRECSCH_RECORDS_MAX_NUM, \
{{FMR_CHANNEL_FREQ_EMPTY/*nChannelFreq*/, ALARM_STATUS_OFF/*eStatus*/, 0/*nAlarmSrvStartDatetime*/, 0/*nStartDatetime*/, 1199149200/*nEndtime*/, ALARM_FREQUENCY_DAILY/*eFrequency*/, VOICE_RECORD_NORMAL_QUALITY/*eRecordType*/, FM_RECORD_STORAGE_CARD/*eStorage*/, 0/*bAppendRecord*/, 0/*urlHashId*/},\
{FMR_CHANNEL_FREQ_EMPTY/*nChannelFreq*/, ALARM_STATUS_OFF/*eStatus*/, 0/*nAlarmSrvStartDatetime*/, 0/*nStartDatetime*/, 1199149200/*nEndtime*/, ALARM_FREQUENCY_DAILY/*eFrequency*/, VOICE_RECORD_NORMAL_QUALITY/*eRecordType*/, FM_RECORD_STORAGE_CARD/*eStorage*/, 0/*bAppendRecord*/,0/*urlHashId*/},\
{FMR_CHANNEL_FREQ_EMPTY/*nChannelFreq*/, ALARM_STATUS_OFF/*eStatus*/, 0/*nAlarmSrvStartDatetime*/, 0/*nStartDatetime*/, 1199149200/*nEndtime*/, ALARM_FREQUENCY_DAILY/*eFrequency*/, VOICE_RECORD_NORMAL_QUALITY/*eRecordType*/, FM_RECORD_STORAGE_CARD/*eStorage*/, 0/*bAppendRecord*/,0/*urlHashId*/},\
{FMR_CHANNEL_FREQ_EMPTY/*nChannelFreq*/, ALARM_STATUS_OFF/*eStatus*/, 0/*nAlarmSrvStartDatetime*/, 0/*nStartDatetime*/, 1199149200/*nEndtime*/, ALARM_FREQUENCY_DAILY/*eFrequency*/, VOICE_RECORD_NORMAL_QUALITY/*eRecordType*/, FM_RECORD_STORAGE_CARD/*eStorage*/, 0/*bAppendRecord*/,0/*urlHashId*/},\
{FMR_CHANNEL_FREQ_EMPTY/*nChannelFreq*/, ALARM_STATUS_OFF/*eStatus*/, 0/*nAlarmSrvStartDatetime*/, 0/*nStartDatetime*/, 1199149200/*nEndtime*/, ALARM_FREQUENCY_DAILY/*eFrequency*/, VOICE_RECORD_NORMAL_QUALITY/*eRecordType*/, FM_RECORD_STORAGE_CARD/*eStorage*/, 0/*bAppendRecord*/,0/*urlHashId*/},\
{FMR_CHANNEL_FREQ_EMPTY/*nChannelFreq*/, ALARM_STATUS_OFF/*eStatus*/, 0/*nAlarmSrvStartDatetime*/, 0/*nStartDatetime*/, 1199149200/*nEndtime*/, ALARM_FREQUENCY_DAILY/*eFrequency*/, VOICE_RECORD_NORMAL_QUALITY/*eRecordType*/, FM_RECORD_STORAGE_CARD/*eStorage*/, 0/*bAppendRecord*/,0/*urlHashId*/}}/*FMRECSCH_RecordList*/)

#ifdef __APP_MMI_FM_SCHEDULE__
#define FMSCHAPP_NAMR_ALL_CONFIG \
    CONFIG_NAMR_FMSCH_RECORD_LIST \
    CONFIG_NAMR_FMRECSCH_RECORD_LIST
#else
#define FMSCHAPP_NAMR_ALL_CONFIG
#endif

#endif /* __MMI_FMSCH_CFG__H__ */
