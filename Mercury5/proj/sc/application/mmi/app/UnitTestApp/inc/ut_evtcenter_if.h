#ifndef __UT_EVTCENTER_IF_H__
#define __UT_EVTCENTER_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getEvtCenter_if_UT(void);
int   noEvtCenter_if_UT(void);
void  releaseEvtCenter_if_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_EVTCENTER_IF_H__ */
