/**
* @file mmi_cb_acc.h
*
*
* @version $Id:$
*
*/

#ifndef __MMI_CB_ACC_H__
#define __MMI_CB_ACC_H__

#include "mmi_mae_common_def.h"
#include "mdl_gpd_pub.h"

 

/* mmi_gdp_acs_notify_cb
 * @brief	callback function of esl_GPD_RegAcsNodifyReq
 */
 
void mmi_gdp_acs_notify_cb(u16 senderID, u32 userValue, MdlGpdAcsInfo_t *pAcsInfo);



#endif /* __MMI_CB_ACC_H__ */


