#ifndef __UT_EVENTDB_IF_H__
#define __UT_EVENTDB_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getEventDB_if_UT(void);
int   noEventDB_if_UT(void);
void  releaseEventDB_if_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_EVENTDB_IF_H__ */
