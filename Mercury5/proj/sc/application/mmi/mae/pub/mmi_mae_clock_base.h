/**
 * @file mmi_mae_clock_base.h
 *
 * @version $Id: mmi_mae_clock_base.h 726 2009-04-29 08:23:38Z code.lin $
 */
#ifndef __MMI_MAE_CLOCK_BASE_H__
#define __MMI_MAE_CLOCK_BASE_H__
/******************************/
/*        INCLUDE             */
/******************************/
#include "mmi_mae_common_def.h"
#include "mmi_mae_clock_forward.h"

/******************************/
/*        DEFINITION          */
/******************************/

MAE_Ret CLOCKBASE_New(void **ppClock);
MAE_Ret CLOCKBASE_Release(ClockBase_t *pClock);
/* Clock API */
MAE_Ret CLOCKBASE_GetTime(ClockBase_t *pClock, MAE_DateTime_t *pDateTime);
MAE_Ret CLOCKBASE_GetTimeRange(ClockBase_t *pClock, MAE_DateTime_t *pMinDateTime, MAE_DateTime_t *pMaxDateTime);
u32 CLOCKBASE_GetTimeInSeconds(ClockBase_t *pIClock);
MAE_Ret CLOCKBASE_GetTimeOffset(ClockBase_t *pClock, MAE_DateTime_t *pUTCTime, MAE_TimeZone_e nTimezone, s32 *pOffset, boolean *pDst);
MAE_Ret CLOCKBASE_ConvertToUTCTime(ClockBase_t *pClock, MAE_DateTime_t *pLocalTime, MAE_DateTime_t *pUTCTime);
MAE_Ret CLOCKBASE_ConvertToLocalTime(ClockBase_t *pClock, MAE_DateTime_t *pUTCTime, MAE_DateTime_t *pLocalTime);
MAE_Ret CLOCKBASE_SetTimeZone(ClockBase_t *pClock, MAE_TimeZone_e nTimeZone);
MAE_Ret CLOCKBASE_GetTimeZone(ClockBase_t *pClock, MAE_TimeZone_e *pTimeZone);
MAE_Ret CLOCKBASE_GetSysDefaultTime(ClockBase_t *pClock, MAE_DateTime_t *pDefaultTime);

#endif //__MAE_CLOCK_BASE_H__
