/* ut_ss_if.h */
#ifndef __UT_SS_IF_H__
#define __UT_SS_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getSS_if_UT(void);
int   noSS_if_UT(void);
void  releaseSS_if_UT(FILE *flog);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_SS_IF_H__ */
