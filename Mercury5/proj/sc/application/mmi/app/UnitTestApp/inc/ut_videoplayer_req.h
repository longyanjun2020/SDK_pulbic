/* ut_videoplayer_req.h */
#ifndef __UT_VIDEOPLAYER_REQ_H__
#define __UT_VIDEOPLAYER_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getVideoplayer_UT(void);
int   noVideoplayer_UT(void);
void  releaseVideoplayer_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_VIDEOPLAYER_REQ_H__ */
