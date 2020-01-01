/* ut_evtcenter_req.h */
#ifndef __UT_EVTCENTER_REQ_H__
#define __UT_EVTCENTER_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getEVTCENTER_UT(void);
int   noEVTCENTER_UT(void);
void  releaseEVTCENTER_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_EVTCENTER_REQ_H__ */
