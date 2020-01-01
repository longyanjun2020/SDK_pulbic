/**
* @file UT_profile_req.h
* @author wayne-cw.lin@mstarsemi.com
* @brief Unit Test for SrvWrapper of Profile.
*/
#ifndef __UT_PROFILE_REQ_H__
#define __UT_PROFILE_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getPROFILE_UT(void);
int   noPROFILE_UT(void);
void  releasePROFILE_UT(FILE *pFn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_PROFILE_REQ_H__ */
