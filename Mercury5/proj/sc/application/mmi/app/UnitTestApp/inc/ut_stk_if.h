/* ut_stk_if.h */
#ifndef __UT_STK_IF_H__
#define __UT_STK_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getStk_If_UT(void);
int   noStk_If_UT(void);
void  releaseStk_If_UT(FILE *flog);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_STK_IF_H__ */
