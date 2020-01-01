/* ut_cbs_if.h */
#ifndef __UT_CBS_IF_H__
#define __UT_CBS_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getCbs_If_UT(void);
int   noCbs_If_UT(void);
void  releaseCbs_If_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CBS_IF_H__ */
