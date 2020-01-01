/**
* @file ut_sensormgr_req.h
* @author wayne-cw.lin@mstarsemi.com
* @brief Unit Test for SrvWrapper of Sensor Manager.
*/
#ifndef __UT_SENSORMGR_REQ_H__
#define __UT_SENSORMGR_REQ_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getSensorMgr_UT(void);
int   noSensorMgr_UT(void);
void  releaseSensorMgr_UT(FILE *pFn);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_SENSORMGR_REQ_H__ */
