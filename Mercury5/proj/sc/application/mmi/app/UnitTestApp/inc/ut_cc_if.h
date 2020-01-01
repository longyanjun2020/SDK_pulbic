/* ut_cc_if.h */
#ifndef __UT_CC_IF_H__
#define __UT_CC_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getCC_if_UT(void);
int   noCC_if_UT(void);
void  releaseCC_if_UT(FILE *flog);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CC_IF_H__ */
