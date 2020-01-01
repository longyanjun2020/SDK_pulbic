/**
* @file ut_sim_req.h
* @author wayne-cw.lin@mstarsemi.com
* @brief Unit Test for SrvWrapper of SIM.
*/
#ifndef __UT_SIM_REQ_H__
#define __UT_SIM_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getSIM_UT(void);
int   noSIM_UT(void);
void  releaseSIM_UT(FILE *pFn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_SIM_REQ_H__ */
