/* ut_imagemaker_req.h */
#ifndef __UT_IMAGEMAKER_REQ_H__
#define __UT_IMAGEMAKER_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getImageMaker_UT(void);
int   noImageMaker_UT(void);
void  releaseImageMaker_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_IMAGEMAKER_REQ_H__ */
