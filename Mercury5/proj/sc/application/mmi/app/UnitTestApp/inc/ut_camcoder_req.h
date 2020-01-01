/* ut_camcoder_req.h */
#ifndef __UT_CAMCODER_REQ_H__
#define __UT_CAMCODER_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getCAMCODER_UT(void);
int   noCAMCODER_UT(void);
void  releaseCAMCODER_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CAMCODER_REQ_H__ */
