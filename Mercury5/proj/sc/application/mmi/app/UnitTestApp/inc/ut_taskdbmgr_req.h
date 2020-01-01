/**
* @file ut_taskdbmgr_req.h
* @author wayne-cw.lin@mstarsemi.com
* @brief Unit Test for SrvWrapper of Task DB Manager.
*/
#ifndef __UT_TASKDBMGR_REQ_H__
#define __UT_TASKDBMGR_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getTaskDBMgr_UT(void);
int   noTaskDBMgr_UT(void);
void  releaseTaskDBMgr_UT(FILE *pFn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_TASKDBMGR_REQ_H__ */
