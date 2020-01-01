/**
* @file ut_stk_req.h
* @author wayne-cw.lin@mstarsemi.com
* @brief Unit Test for SrvWrapper of STK.
*/
#ifndef __UT_STK_REQ_H__
#define __UT_STK_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getSTK_UT(void);
int   noSTK_UT(void);
void  releaseSTK_UT(FILE *pFn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_STK_REQ_H__ */
