/* ut_mmstx_if.h */
#ifndef __UT_MMSTX_IF_H__
#define __UT_MMSTX_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getMmstx_If_UT(void);
int   noMmstx_If_UT(void);
void  releaseMmstx_If_UT(FILE *flog);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_MMSTX_IF_H__ */
