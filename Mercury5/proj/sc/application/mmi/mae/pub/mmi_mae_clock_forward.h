/**
 * @file mmi_mae_clock_forward.h
 *
 * 
 *
 * @version $Id: mmi_mae_clock_forward.h $
 */

#ifndef __MMI_MAE_CLOCK_FORWARD_H__
#define __MMI_MAE_CLOCK_FORWARD_H__

#include "mmi_mae_common_def.h"

typedef u32 MAEClkItemId_t; ///enum MAEClkItemId_t_
typedef u32 MAE_TimeZone_Field_e; ///enum MAE_TimeZone_Field_e_
typedef u8 MAE_TimeFormat_e; ///enum MAE_TimeFormat_e_
typedef struct ClockListener_t_ ClockListener_t;
typedef u32 MAE_TimeZone_e;
typedef void ClockBase_t;
typedef struct TimeZoneRule_t_ TimeZoneRule_t;
typedef struct _ClockBase_t_ _ClockBase_t;

typedef void (*PfnClkListener) (void *pUsrData, MAEClkItemId_t nId, void *pItemData);


#endif //__MMI_MAE_CLOCK_FORWARD_H__

