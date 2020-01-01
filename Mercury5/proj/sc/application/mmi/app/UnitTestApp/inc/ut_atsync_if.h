/* ut_atsync_if.h */
#ifndef __UT_ATSYNC_IF_H__
#define __UT_ATSYNC_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getAtsync_If_UT(void);
int   noAtsync_If_UT(void);
void  releaseAtsync_If_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_ATSYNC_IF_H__ */
