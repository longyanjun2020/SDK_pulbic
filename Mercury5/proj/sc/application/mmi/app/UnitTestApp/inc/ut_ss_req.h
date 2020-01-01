/**
* @file ut_stk_req.h
* @author wayne-cw.lin@mstarsemi.com
* @brief Unit Test for SrvWrapper of SS.
*/
#ifndef __UT_SS_REQ_H__
#define __UT_SS_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getSS_UT(void);
int   noSS_UT(void);
void  releaseSS_UT(FILE *pFn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_SS_REQ_H__ */
