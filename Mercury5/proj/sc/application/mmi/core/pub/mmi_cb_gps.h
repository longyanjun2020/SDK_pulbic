/**
* @file mmi_cb_gps.h
*
*
* @version $Id: mmi_cb_gps.h 14013 2008-12-11 16:23:04Z william.wang $
*/

#ifndef __MMI_CB_GPS_H__
#define __MMI_CB_GPS_H__

#include "esl_gps_itf.h"

void Gps_Open_Cb(u16 senderID, u32 userValue, esl_GpsErrCode_e errCode, esl_GpsInfo_t *pGpsInfo);
void Gps_Close_Cb(u16 senderID, u32 userValue, esl_GpsErrCode_e errCode, esl_GpsInfo_t *pGpsInfo);
void Gps_GetData_Cb(u16 senderID, u32 userValue, esl_GpsErrCode_e errCode, esl_GpsInfo_t *pGpsInfo);

#endif //__MMI_CB_GPS_H__
