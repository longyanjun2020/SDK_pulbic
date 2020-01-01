/* ut_fdn_req.h */
#ifndef __UT_FDN_REQ_H__
#define __UT_FDN_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getFDN_UT(void);
int   noFDN_UT(void);
void  releaseFDN_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_FDN_REQ_H__ */
