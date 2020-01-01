#ifndef __UT_MOBILITYMGR_REQ_H__
#define __UT_MOBILITYMGR_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getMobilitymgr_UT(void);
int   noMobilitymgr_UT(void);
void  releaseMobilitymgr_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_MOBILITYMGR_REQ_H__ */
