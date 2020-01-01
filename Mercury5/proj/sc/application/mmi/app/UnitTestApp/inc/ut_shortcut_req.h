/**
* @file ut_short_req.h
* @author wayne-cw.lin@mstarsemi.com
* @brief Unit Test for SrvWrapper of Shortcut.
*/
#ifndef __UT_SHORTCUT_REQ_H__
#define __UT_SHORTCUT_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getSHORTCUT_UT(void);
int   noSHORTCUT_UT(void);
void  releaseSHORTCUT_UT(FILE *pFn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_SHORTCUT_REQ_H__ */

