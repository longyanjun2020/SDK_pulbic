/**
* @file ut_sms_req.h
* @author wayne-cw.lin@mstarsemi.com
* @brief Unit Test for SrvWrapper of SMS.
*/
#ifndef __UT_SMS_REQ_H__
#define __UT_SMS_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getSMS_UT(void);
int   noSMS_UT(void);
void  releaseSMS_UT(FILE *pFn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_SMS_REQ_H__ */
