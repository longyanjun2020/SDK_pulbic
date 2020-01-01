/**
* @file ut_touchshortcut_req.h
* @author wayne-cw.lin@mstarsemi.com
* @brief Unit Test for SrvWrapper of Touch ShortCut.
*/
#ifndef __UT_TOUCHSHORTCUT_REQ_H__
#define __UT_TOUCHSHORTCUT_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getTouchShortCut_UT(void);
int   noTouchShortCut_UT(void);
void  releaseTouchShortCut_UT(FILE *fn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_TOUCHSHORTCUT_REQ_H__ */
