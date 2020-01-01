/**
* @file mmi_gsensor_msgdef.h
*
*
* @version $Id: mmi_gsensor_msgdef.h 15893 2008-11-04 14:51:24Z mark.yang $
*
*/

#ifndef __MMI_GSENSOR_MSGDEF_H__
#define __MMI_GSENSOR_MSGDEF_H__

#include "mmi_mae_common_def.h"
#include "mdl_gpd_pub.h"

typedef struct 
{
	u32 userValue;
	u16 senderID;
	MdlGpdErrCode_e errCode;
	MdlGpdGsensorOp_e gSensorOp;	/**< G-sensor ON/OFF */
	u32 gSensorPollingTime;			/**< G-sensor polling time */
	MdlGsensorCapability_t gSensorCapability;
} mmi_GpdGsensorCbMsgBody_t;

typedef struct 
{
	u32 userValue;
	u16 senderID;
	u16 x;        /**< X-axis data */
	u16 y;        /**< Y-axis data */
	u16 z;        /**< Z-axis data, reserved */
} mmi_GpdGsensorNotifyMsgBody_t;

#endif /* __MMI_GSENSOR_MSGDEF_H__ */

