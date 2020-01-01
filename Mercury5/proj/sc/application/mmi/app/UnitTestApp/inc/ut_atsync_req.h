/* ut_atsync_req.h */
#ifndef __UT_ATSYNC_REQ_H__
#define __UT_ATSYNC_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getATSync_UT(void);
int   noATSync_UT(void);
void  releaseATSync_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_ATSYNC_REQ_H__ */
