/* ut_mm_if.h */
#ifndef __UT_MM_IF_H__
#define __UT_MM_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getMm_If_UT(void);
int   noMm_If_UT(void);
void  releaseMm_If_UT(FILE *flog);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_MM_IF_H__ */
