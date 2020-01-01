/* ut_eventdb_req.h */
#ifndef __UT_EVENTDB_REQ_H__
#define __UT_EVENTDB_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getEventDB_UT(void);
int   noEventDB_UT(void);
void  releaseEventDB_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_EVENTDB_REQ_H__ */
