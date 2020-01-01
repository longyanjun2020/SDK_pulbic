/* ut_moi_req.h */
#ifndef __UT_MOI_REQ_H__
#define __UT_MOI_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getMoi_UT(void);
int   noMoi_UT(void);
void  releaseMoi_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_MOI_REQ_H__ */
