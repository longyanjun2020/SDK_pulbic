/* ut_alarm_req.h */
#ifndef __UT_ALARM_REQ_H__
#define __UT_ALARM_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getALARM_UT(void);
int   noALARM_UT(void);
void  releaseALARM_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_ALARM_REQ_H__ */
