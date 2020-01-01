/**
* @file ut_sensormgr_if.h
* @author mickey.chiang@mstarsemi.com
* @brief Unit Test for SrvWrapper of Sensor Manager.
*/
#ifndef __UT_SENSORMGR_IF_H__
#define __UT_SENSORMGR_IF_H__

#include "ut_def.h"

#ifndef __ENABLE_DLM_SRVUT__
UT_t *getSensorMgr_If_UT(void);
int   noSensorMgr_If_UT(void);
void  releaseSensorMgr_If_UT(FILE *pFile);
#endif    /* __ENABLE_DLM_SRVUT__ */

#endif    /* __UT_SENSORMGR_IF_H__ */
