/* ut_simsync_example.h */
#ifndef __UT_SIMSYNC_EXAMPLE_H__
#define __UT_SIMSYNC_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetSimSync_Example(void);
s32   NumSimSync_Example(void);
void  ReleaseSimSync_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_SIM_EXAMPLE_H__ */

