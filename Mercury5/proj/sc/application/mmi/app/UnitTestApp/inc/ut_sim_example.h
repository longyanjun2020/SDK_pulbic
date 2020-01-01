/* ut_sim_example.h */
#ifndef __UT_SIM_EXAMPLE_H__
#define __UT_SIM_EXAMPLE_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *GetSim_Example(void);
s32   NumSim_Example(void);
void  ReleaseSim_Example(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_SIM_EXAMPLE_H__ */

