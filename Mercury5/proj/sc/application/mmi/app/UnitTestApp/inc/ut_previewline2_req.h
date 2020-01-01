/**
* @file ut_previewline2_req.h
* @author wayne-cw.lin@mstarsemi.com
* @brief Unit Test for SrvWrapper of Sensor Manager.
*/
#ifndef __UT_PREVIEWLINE2_REQ_H__
#define __UT_PREVIEWLINE2_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getPreviewline2_UT(void);
int   noPreviewline2_UT(void);
void  releasePreviewline2_UT(FILE *pFn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_PREVIEWLINE2_REQ_H__ */
