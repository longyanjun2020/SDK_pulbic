/* ut_camera_req.h */
#ifndef __UT_CAMERA_REQ_H__
#define __UT_CAMERA_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getCAMERA_UT(void);
int   noCAMERA_UT(void);
void  releaseCAMERA_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_CAMERA_REQ_H__ */
