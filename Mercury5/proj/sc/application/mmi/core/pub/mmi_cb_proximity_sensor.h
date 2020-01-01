/**
* @file mmi_cb_paisensor.h
*
*
* @version $Id: mmi_cb_paisensor.h 15856 2008-11-04 04:59:02Z mark.yang $
*
*/

#ifndef __MMI_CB_PAISENSOR_H__
#define __MMI_CB_PAISENSOR_H__

#include "mmi_mae_common_def.h"
#include "mdl_gpd.h"

//#include "esl_gpd_itf.h"

/**
* regular callback function of esl_GPD_RegGsensorNodifyReq
*/
void mmi_gpd_Infrared_Ind_cb(u16 senderID, u32 userValue, MdlProximitySensorNotifyInfo_t *pGpdGsensorNotifyInfo);

#endif /* __MMI_CB_PAISENSOR_H__ */


