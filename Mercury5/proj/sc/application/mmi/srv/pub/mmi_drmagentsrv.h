/**
* @file mmi_drmagentsrv.h
*
*
* Class Id: CLSID_DRMAGENTSRV
*
*
* @version $Id$
*/

#ifndef __MMI_DRMAGENTSRV_H__
#define __MMI_DRMAGENTSRV_H__

/*-------------------------------------------------------------------------*/

#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
#include "mmi_mae_class.h"
#include "mmi_drmagentsrv_def.h"
#include "mmi_mae_rightsdb.h"
#include "mmi_base_util.h"

/*-------------------------------------------------------------------------*/
enum
{
    DrmAgentSrv_Notify_Mask_Timer        = 1 << 0,
};
typedef u8 DrmAgentSrv_Notify_Mask_e;
/*-------------------------------------------------------------------------*/

/**
 * External Events
 */


/**
 * ICOUNTDOWNTIMERSRV Interfaces
 */
#define INHERIT_IDRMAGENTSRV(IName) \
    INHERIT_IHandler(IName); \
    MAE_Ret     (*RegisterNotification)     (IName * , void *pInstance, DrmAgentSrv_Notify_Mask_e eMask);  \
    MAE_Ret     (*DeregisterNotification)   (IName * , void *pInstance, DrmAgentSrv_Notify_Mask_e eMask); \
    MAE_Ret     (*InstallRights)            (IName * , u8 *pCID, DrmRightsObject_t *pRightsObject); \
    MAE_Ret     (*GetRights)                (IName * , u8 *pCID, DrmRightsObject_t **ppRightsObject); \
    MAE_Ret     (*IsValidAction)            (IName * , u8 *pCID, DrmAction_e eAction); \
    MAE_Ret     (*ConsumeRights)            (IName * , u8 *pCID, DrmAction_e eAction);\
	MAE_Ret     (*GetRightsByUID)           (IName * , u32 nUID, DrmRightsObject_t **ppRightsObject);\
    MAE_Ret     (*GetRightsUIDList)         (IName * , ArrayClass_t** ppArray, IBase* pOwner);\
    MAE_Ret 	(*GetRightsLink)            (IName * , HashKey_t* pHashKey, ArrayClass_t** ppArray, IBase* pOwner);\
    MAE_Ret     (*DeleteRightsByUID)        (IName *, u32 nUID);\
    MAE_Ret     (*DeleteAll)                (IName *);\
    MAE_Ret     (*SweepInvalidRights)       (IName *, u32 *pSweepCnt);\
    s32         (*IsUnlimitedRights)        (IName *, u8 *pCID);\
    MAE_Ret     (*GetUsageInfo)             (IName *, u16 *pSize, u16 *pUsedNum);\
    MAE_Ret     (*UpdateRights)             (IName * , DrmRightsObject_t *pRightsObject)
DEFINE_INTERFACE(IDRMAGENTSRV);


#define IDRMAGENTSRV_QueryInterface(pICntlr, id, pp, po) GET_FUNCTBL((pICntlr), IDRMAGENTSRV)->QueryInterface(pICntlr, id, pp, po)
#define IDRMAGENTSRV_HandleEvent(pICntlr, e, p1, p2) GET_FUNCTBL((pICntlr), IDRMAGENTSRV)->HandleEvent(pICntlr, e, p1, p2)
/**

 */
#define IDRMAGENTSRV_RegisterNotification(pICntlr, p1, p2) GET_FUNCTBL((pICntlr), IDRMAGENTSRV)->RegisterNotification( pICntlr, p1, p2)
/**
  */
#define IDRMAGENTSRV_DeregisterNotification(pICntlr, p1, p2) GET_FUNCTBL((pICntlr), IDRMAGENTSRV)->DeregisterNotification( pICntlr, p1, p2)
/**
  */
#define IDRMAGENTSRV_InstallRights(pICntlr, p1, p2)         GET_FUNCTBL((pICntlr), IDRMAGENTSRV)->InstallRights( pICntlr, p1, p2)
#define IDRMAGENTSRV_GetRights(pICntlr, p1, p2)             GET_FUNCTBL((pICntlr), IDRMAGENTSRV)->GetRights( pICntlr, p1, p2)
#define IDRMAGENTSRV_IsValidAction(pICntlr, p1, p2)         GET_FUNCTBL((pICntlr), IDRMAGENTSRV)->IsValidAction( pICntlr, p1, p2)
#define IDRMAGENTSRV_ConsumeRights(pICntlr, p1, p2)         GET_FUNCTBL((pICntlr), IDRMAGENTSRV)->ConsumeRights( pICntlr, p1, p2)

#define IDRMAGENTSRV_GetRightsByUID(pICntlr, p1, p2)        GET_FUNCTBL((pICntlr), IDRMAGENTSRV)->GetRightsByUID( pICntlr, p1, p2)
#define IDRMAGENTSRV_GetRightsUIDList(pICntlr, p1, p2)      GET_FUNCTBL((pICntlr), IDRMAGENTSRV)->GetRightsUIDList( pICntlr, p1, p2)
#define IDRMAGENTSRV_GetRightsLink(pICntlr, p1, p2, p3)     GET_FUNCTBL((pICntlr), IDRMAGENTSRV)->GetRightsLink( pICntlr, p1, p2, p3)

#define IDRMAGENTSRV_DeleteRightsByUID(pICntlr, p1)         GET_FUNCTBL((pICntlr), IDRMAGENTSRV)->DeleteRightsByUID( pICntlr, p1)
#define IDRMAGENTSRV_DeleteAll(pICntlr)                     GET_FUNCTBL((pICntlr), IDRMAGENTSRV)->DeleteAll( pICntlr)
#define IDRMAGENTSRV_SweepInvalidRights(pICntlr, p1)        GET_FUNCTBL((pICntlr), IDRMAGENTSRV)->SweepInvalidRights( pICntlr, p1)
#define IDRMAGENTSRV_IsUnlimitedRights(pICntlr, p1)         GET_FUNCTBL((pICntlr), IDRMAGENTSRV)->IsUnlimitedRights( pICntlr, p1)
#define IDRMAGENTSRV_GetUsageInfo(pICntlr, p1, p2)          GET_FUNCTBL((pICntlr), IDRMAGENTSRV)->GetUsageInfo( pICntlr, p1, p2)
#define IDRMAGENTSRV_UpdateRights(pICntlr, p1)              GET_FUNCTBL((pICntlr), IDRMAGENTSRV)->UpdateRights( pICntlr, p1)



/**
  * Functions
  */
void DRMAGENTSRV_Init(void);

MAE_Ret DRMAGENTSRV_New(MAE_ClsId id, void **ppObj);

#endif /* __MMI_DRMAGENTSRV_H__ */
