/* ut_motiondetector_if.h */
#ifndef __UT_MOTIONDETECTOR_IF_H__
#define __UT_MOTIONDETECTOR_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getMotiondetect_IF_UT(void);
int   noMotiondetect_IF_UT(void);
void  releaseMotiondetect_IF_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_MOTIONDETECTOR_IF_H__ */
