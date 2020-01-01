/**
* @file ut_smstx_req.h
* @author wayne-cw.lin@mstarsemi.com
* @brief Unit Test for SrvWrapper of SMSTX.
*/
#ifndef __UT_SMSTX_REQ_H__
#define __UT_SMSTX_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getSMSTX_UT(void);
int   noSMSTX_UT(void);
void  releaseSMSTX_UT(FILE *pFn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_SMSTX_REQ_H__ */
