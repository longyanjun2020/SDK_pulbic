/* ut_smstx_if.h */
#ifndef __UT_SMSTX_IF_H__
#define __UT_SMSTX_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getSmstx_If_UT(void);
int   noSmstx_If_UT(void);
void  releaseSmstx_If_UT(FILE *flog);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_SMSTX_IF_H__ */
