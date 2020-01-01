/* ut_sim_if.h */
#ifndef __UT_SIM_IF_H__
#define __UT_SIM_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getSim_If_UT(void);
int   noSim_If_UT(void);
void  releaseSim_If_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_SIM_IF_H__ */
