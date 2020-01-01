/**
* @file ut_vendor_req.h
* @author wayne-cw.lin@mstarsemi.com
* @brief Unit Test for SrvWrapper of Vendor.
*/
#ifndef __UT_VENDOR_REQ_H__
#define __UT_VENDOR_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getVendor_UT(void);
int   noVendor_UT(void);
void  releaseVendor_UT(FILE *pFn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_VENDOR_REQ_H__ */
