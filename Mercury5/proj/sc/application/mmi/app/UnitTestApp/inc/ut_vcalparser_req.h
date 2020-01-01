/**
* @file ut_vcalparser_req.h
* @author wayne-cw.lin@mstarsemi.com
* @brief Unit Test for SrvWrapper of VCAL Parser.
*/
#ifndef __UT_VCALPARSER_REQ_H__
#define __UT_VCALPARSER_REQ_H__

#ifdef __CALENDAR_SUPPORT_VCS_MMI__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getVCalParser_UT(void);
int   noVCalParser_UT(void);
void  releaseVCalParser_UT(FILE *pFn);
#endif    /* __ENABLE_DLM_SRVUT__ */
#endif    /* __CALENDAR_SUPPORT_VCS_MMI__ */
#endif    /* __UT_VCALPARSER_REQ_H__ */
