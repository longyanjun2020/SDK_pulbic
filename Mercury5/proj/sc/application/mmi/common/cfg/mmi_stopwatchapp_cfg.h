
#ifndef __MMI_STOPWATCHAPP_CFG__H__
#define __MMI_STOPWATCHAPP_CFG__H__

#include "mmi_mae_common_def.h"
#include "mmi_wdg_timerformat.h"

typedef struct
{
    u8 nRecordNum;
    u32 nStartTimeInSec;
    u16 nStartTick;
    u32 nPauseTimeInSec;
    u16 nPauseTick;
    boolean bStopped;
    boolean bPaused;
    boolean bReachedMax;
} StopwatchRecordStatus_t;

#define CONFIG_AMR_STOPWATCH_RECORD_STATUS   CONFIG_DEFINE(CFGIT_STOPWATCH_RECORD_STATUS, StopwatchRecordStatus_t, 1, {0} )
#define CONFIG_AMR_STOPWATCH_RECORD_ITEMS    CONFIG_DEFINE(CFGIT_STOPWATCH_RECORD_ITEMS, TimerFomatData_t, MAX_STOPWATCH_ITEM_NUM, {0})

#ifdef __APP_MMI_STOPWATCH__
#define STOPWATCH_AMR_APP_CONFIG \
                        CONFIG_AMR_STOPWATCH_RECORD_STATUS \
                        CONFIG_AMR_STOPWATCH_RECORD_ITEMS
#else
#define STOPWATCH_AMR_APP_CONFIG
#endif

#endif //__MMI_STOPWATCHAPP_CFG__H__
