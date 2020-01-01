/**
* @file ut_touch_req.h
* @author wayne-cw.lin@mstarsemi.com
* @brief Unit Test for SrvWrapper of Touch.
*/
#ifndef __UT_TOUCH_REQ_H__
#define __UT_TOUCH_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getTOUCH_UT(void);
int   noTOUCH_UT(void);
void  releaseTOUCH_UT(FILE *pFn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_TOUCH_REQ_H__ */
