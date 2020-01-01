/* ut_battery_if.h */
#ifndef __UT_BATTERY_IF_H__
#define __UT_BATTERY_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getBATTERY_if_UT(void);
int   noBATTERY_if_UT(void);
void  releaseBATTERY_if_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_BATTERY_IF_H__ */
