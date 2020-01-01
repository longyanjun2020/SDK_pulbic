/* ut_acc_if.h */
#ifndef __UT_ACC_IF_H__
#define __UT_ACC_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getACC_if_UT(void);
int   noACC_if_UT(void);
void  releaseACC_if_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_ACC_IF_H__ */
