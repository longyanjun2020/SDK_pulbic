/* ut_tv_req.h */
#ifndef __UT_TV_REQ_H__
#define __UT_TV_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getTv_UT(void);
int   noTv_UT(void);
void  releaseTv_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_TV_REQ_H__ */
