/* ut_fdn_if.h */
#ifndef __UT_FDN_IF_H__
#define __UT_FDN_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getFdn_If_UT(void);
int   noFdn_If_UT(void);
void  releaseFdn_If_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_FDN_IF_H__ */
