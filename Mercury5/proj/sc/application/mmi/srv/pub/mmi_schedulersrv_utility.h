#ifndef __MMI_SCHEDULERSRV_UTILITY_H__
#define __MMI_SCHEDULERSRV_UTILITY_H__

#include "mmi_mae_common_def.h"
#include "mmi_schedulersrv_common.h"

typedef enum
{
    TYPE_AUTOPOWERON = 0,
    TYPE_AUTOPOWEROFF,
}SCHSRV_APP_TYPE;

extern u32 SchSrv_Utility_GetWeekDay(MAE_DateTime_t *pDate);
extern SCHSRV_PeriodicType SchSrv_Utility_GetFrequencyByWeekDay(u8 nDayOfWeek);
extern SCHSRV_PeriodicType SchSrv_Utility_GetNextFrequency(SCHSRV_PeriodicType nCurFeq);
extern u8 SchSrv_Utility_GetWeekDayByFrequency(SCHSRV_PeriodicType eFrequency);
extern MAE_Ret SchSrv_Utility_GetNextDateTime(MAE_DateTime_t *pDate, SCHSRV_APP_TYPE eType);

#endif /*__MMI_SCHEDULERSRV_UTILITY_H__*/
