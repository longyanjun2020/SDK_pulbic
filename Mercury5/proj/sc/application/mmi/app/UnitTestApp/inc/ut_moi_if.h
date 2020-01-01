/* ut_moi_if.h */
#ifndef __UT_MOI_IF_H__
#define __UT_MOI_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getMoi_If_UT(void);
int   noMoi_If_UT(void);
void  releaseMoi_If_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_MOI_IF_H__ */
