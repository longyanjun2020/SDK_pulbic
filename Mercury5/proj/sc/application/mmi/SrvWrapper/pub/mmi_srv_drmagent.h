/**
* @file    mmi_srv_drmagent.h
* @brief
*
*/

#ifndef __MMI_SRV_DRMAGENT_H__
#define __MMI_SRV_DRMAGENT_H__

#include "mmi_srv_client_commondefine.h"
#include "mmi_drmagentsrv.h"
#include "mmi_drmagentsrv_def.h"
#include "mmi_mae_rightsdb.h"

MAE_Ret SrvDrmAgentInstallRights(u8 *pCID, DrmRightsObject_t *pRightsObject);
MAE_Ret SrvDrmAgentUpdateRights(DrmRightsObject_t *pRightsObject);
MAE_Ret SrvDrmAgentGetRights(u8 *pCID, DrmRightsObject_t **ppRightsObject);
boolean SrvDrmAgentIsValidAction(u8 *pCID, DrmAction_e eAction);
MAE_Ret SrvDrmAgentConsumeRights(u8 *pCID, DrmAction_e eAction);
MAE_Ret SrvDrmAgentGetRightsByUID(u32 nUID, DrmRightsObject_t **ppRightsObject);
MAE_Ret SrvDrmAgentGetRightsUIDList(ArrayClass_t** ppArray, IBase* pOwner);
MAE_Ret SrvDrmAgentGetRightsLink(HashKey_t* pHashKey, ArrayClass_t** ppArray, IBase* pOwner);
MAE_Ret SrvDrmAgentDeleteRightsByUID(u32 nUID);
MAE_Ret SrvDrmAgentDeleteAll(void);
MAE_Ret SrvDrmAgentSweepInvalidRights(u32 *pSweepCnt);
s32 SrvDrmAgentIsUnlimitedRights(u8 *pCID);
MAE_Ret SrvDrmAgentGetUsageInfo(u16 *pSize, u16 *pUsedNum);


#endif /*__MMI_SRV_DRMAGENT_H__*/
