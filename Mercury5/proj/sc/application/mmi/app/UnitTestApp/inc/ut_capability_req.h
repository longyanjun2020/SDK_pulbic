/* ut_capabilty_req.h */

#ifndef __UT_CAPABILITY_REQ_H__
#define __UT_CAPABILITY_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getCAPABILITY_UT(void);
int   noCAPABILITY_UT(void);
void  releaseCAPABILITY_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CAPABILITY_REQ_H__ */
