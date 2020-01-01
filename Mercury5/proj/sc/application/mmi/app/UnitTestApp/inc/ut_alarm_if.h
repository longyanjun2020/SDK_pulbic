/* ut_alarm_if.h */
#ifndef __UT_ALARM_IF_H__
#define __UT_ALARM_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getAlarm_If_UT();
int   noAlarm_If_UT(void);
void  releaseAlarm_If_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_ALARM_IF_H__ */
