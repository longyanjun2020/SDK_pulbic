/* ut_motiondetect_req.h */
#ifndef __UT_MOTIONDETECTOR_REQ_H__
#define __UT_MOTIONDETECTOR_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getMotiondetect_UT(void);
int   noMotiondetect_UT(void);
void  releaseMotiondetect_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_MOTIONDETECTOR_REQ_H__ */
