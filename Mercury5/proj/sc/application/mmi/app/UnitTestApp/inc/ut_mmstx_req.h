/* ut_mmstx_req.h */
#ifndef __UT_MMSTX_REQ_H__
#define __UT_MMSTX_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getMmstx_UT(void);
int   noMmstx_UT(void);
void  releaseMmstx_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_MMSTX_REQ_H__ */
