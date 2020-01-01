/**
* @file ut_vcalstore_req.h
* @author wayne-cw.lin@mstarsemi.com
* @brief Unit Test for SrvWrapper of VCAL Store.
*/
#ifndef __UT_VCALSTORE_REQ_H__
#define __UT_VCALSTORE_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getVCALSTORE_UT(void);
int   noVCALSTORE_UT(void);
void  releaseVCALSTORE_UT(FILE *pFn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_VCALSTORE_REQ_H__ */
