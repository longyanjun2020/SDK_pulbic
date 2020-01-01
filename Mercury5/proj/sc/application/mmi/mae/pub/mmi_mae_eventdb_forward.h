/**
 * @file mmi_mae_eventdb.h
 * @brief   The document describes the interface of IEventDB
 * IEventDB represent event record(s) in calendar application.
 *
 * @author  nick.chou@mstarsemi.com
 * @version $Id: mmi_mae_eventdb.h 1684 2009-08-29 16:28:08Z zinc.chen $
 */
#ifndef __MMI_MAE_EVENTDB_FORWARD_H__
#define __MMI_MAE_EVENTDB_FORWARD_H__
/*-------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
/*-------------------------------------------------------------------------*/

typedef struct VCALUTCDate_t_ VCALUTCDate_t;
typedef struct VCALAlarm_t_ VCALAlarm_t;
typedef struct VCALRRule_t_ VCALRRule_t;
typedef struct CalendarEvent_t_ CalendarEvent_t;
typedef struct VCALDateRange_t_ VCALDateRange_t;
typedef_opaque_enum(SortMode_e_, SortMode_e);
typedef_opaque_enum(MAE_EventDB_Notify_e_, MAE_EventDB_Notify_e);


#endif /* __MMI_MAE_EVENTDB_FORWARD_H__ */


