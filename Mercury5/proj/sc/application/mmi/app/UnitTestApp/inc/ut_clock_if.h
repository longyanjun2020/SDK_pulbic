/* ut_clock_if.h */
#ifndef __UT_CLOCK_IF_H__
#define __UT_CLOCK_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getClock_If_UT(void);
int   noClock_If_UT(void);
void  releaseClock_If_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CLOCK_IF_H__ */
