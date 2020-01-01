/**
* @file mmi_ccapp.h
*
* Class Id: CLSID_CCAPP
*
*/
#ifndef __MMI_CCAPP_H__
#define __MMI_CCAPP_H__

#include "mmi_mae_common_def.h"
#include "mmi_ccsrv_def.h"
#include "mmi_srv_header.h"
#include "mmi_launcher_cc.h"
#include "mmi_common_cc_type.h"

/**
 * Functions
 */

MAE_Ret CCAPP_New(MAE_ClsId id, void **ppObj);
void CcAppFreeMakeCallReqData(IBase *pIssuer, u32 nParam);
void CcAppFreeIncomingCallIndData(IBase *pIssuer, u32 nParam);
void CcAppFreeEndSpecificCallData(IBase *pIssuer, u32 nParam);


#endif /* __MMI_CCAPP_H__ */
