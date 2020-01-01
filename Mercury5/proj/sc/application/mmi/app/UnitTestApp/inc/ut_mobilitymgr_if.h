#ifndef __UT_MOBILITYMGR_IF_H__
#define __UT_MOBILITYMGR_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getMobilityMgr_if_UT(void);
int   noMobilityMgr_if_UT(void);
void  releaseMobilityMgr_if_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_MOBILITYMGR_IF_H__ */
