/**
* @file ut_taskdb_req.h
* @author wayne-cw.lin@mstarsemi.com
* @brief Unit Test for SrvWrapper of Task DB.
*/
#ifndef __UT_TASKDB_REQ_H__
#define __UT_TASKDB_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getTaskDB_UT(void);
int   noTaskDB_UT(void);
void  releaseTaskDB_UT(FILE *pFn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_TASKDB_REQ_H__ */
