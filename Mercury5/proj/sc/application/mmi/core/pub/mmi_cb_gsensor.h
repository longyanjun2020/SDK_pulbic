/**
* @file mmi_cb_gsensor.h
*
*
* @version $Id: mmi_cb_gsensor.h 15856 2008-11-04 04:59:02Z mark.yang $
*
*/

#ifndef __MMI_CB_GSENSOR_H__
#define __MMI_CB_GSENSOR_H__

#include "mmi_mae_common_def.h"
#include "mdl_gpd_pub.h"


/**
* callback function of MdlGpdGsensorSwitchReq
*/
void mmi_gpd_GsensorOp_cb(u16 senderID, u32 userValue, MdlGpdErrCode_e errCode, MdlGpdInfo_t *pGpdInfo);

/**
 * callback function of MdlGpdRegGsensorNodifyReq
 */
void mmi_gpd_GsensorRegNotify_cb(u16 senderID, u32 userValue, MdlGpdErrCode_e errCode, MdlGpdInfo_t *pGpdInfo);

/**
* regular callback function of MdlGpdRegGsensorNodifyReq
*/
void mmi_gpd_GsensorNofify_cb(u16 senderID, u32 userValue, MdlGsensorNotifyInfo_t *pGpdGsensorNotifyInfo);


#endif /* __MMI_CB_GSENSOR_H__ */


