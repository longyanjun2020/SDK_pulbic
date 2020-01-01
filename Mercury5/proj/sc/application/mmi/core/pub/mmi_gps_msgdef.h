#ifndef __MMI_GPS_MSGDEF_H__
#define __MMI_GPS_MSGDEF_H__

#include "esl_gps_itf.h"

typedef enum
{
	GPS_RSP_SUCCESS = 0,
	GPS_RSP_FAILURE
}GpsRspCode_t;

typedef struct 
{
	GpsRspCode_t			RspCode;	
	u32						UserData;
	esl_GpsInfo_t                      *pGpsInfo;
} mmi_GpsMsgBody_t;

#endif /* __MMI_GPS_MSGDEF_H__ */

