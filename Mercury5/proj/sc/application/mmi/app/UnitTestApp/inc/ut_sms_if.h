/**
* @file ut_sms_if.h
* @author mickey.chiang@mstarsemi.com
* @brief Unit Test for SrvWrapper of SMS.
*/
#ifndef __UT_SMS_IF_H__
#define __UT_SMS_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getSMS_If_UT(void);
int   noSMS_If_UT(void);
void  releaseSMS_If_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_SMS_IF_H__ */
