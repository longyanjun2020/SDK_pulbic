/**
 * \file    mmi_mae_clock_pl.h
 * \brief   The document describes the clock base
 *
 */

#ifndef __MMI__MAE_CLOCK_PL_H__
#define __MMI__MAE_CLOCK_PL_H__

/******************************/
/*        INCLUDE             */
/******************************/
#include "mmi_mae_platform_def.h"
#include "mmi_mae_clock.h"
#include "mmi_mae_clock_base.h"
#include "mmi_mae_clock_types.h"

/******************************/
/*        DEFINITION          */
/******************************/

/******************************/
/*         VARIABLES          */
/******************************/

/******************************/
/*     LOCAL FUNCTIONS        */
/******************************/

/******************************/
/*     GLOBAL FUNCTIONS       */
/******************************/

/**
 * Clone data form MAE_DateTime_t to vm_rtcTimeFormat_t
 */
void MaePl_CloneMAEDateToRtc(MAE_DateTime_t *pMAETime, vm_rtcTimeFormat_t *pSysTime);

/**
 * Clone data form vm_rtcTimeFormat_t to MAE_DateTime_t
 */
void MaePl_CloneRtcToMAEDate(vm_rtcTimeFormat_t * pSysTime, MAE_DateTime_t *pMAETime);

#endif // __MMI_MAE__CLOCK_PL_H__

