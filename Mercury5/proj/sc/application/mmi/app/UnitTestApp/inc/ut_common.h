/* ut_common.h */
#ifndef __UT_COMMON_H__
#define __UT_COMMON_H__

#include <stdlib.h>
#include <time.h>
#include "ut_def.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_util.h"
#include "mmi_mae_event.h"
#include "mmi_mae_bitmap.h"
#include "mmi_mae_clock_base.h"
#include "mmi_mae_clock_types.h"
#include "mmi_mae_config_forward.h"
#include "mmi_mae_config_types.h"
#include "mmi_mae_graphic.h"
#include "mmi_mae_graphic_types.h"
#include "mmi_mae_eventdb_types.h"
#ifdef __ENABLE_DLM_SRVUT__
#include "ut_share_data.h"

void  UT_InitGlobalData(UT_GlobalData_t *pGlobalData);
UT_t *UT_GetFnTbl(void);
int   UT_GetNumOfFun(void);
void  UT_Release(FILE *pFn);
void  UT_GetTestSuitName(char **ppSrvName);

#endif    /* __ENABLE_DLM_SRVUT__ */
#endif    /* __UT_COMMON_H__ */
