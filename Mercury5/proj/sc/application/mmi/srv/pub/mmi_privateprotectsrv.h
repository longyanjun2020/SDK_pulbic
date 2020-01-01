/**
* @file mmi_privateprotectsrv.h
*
* Class Id: CLSID_PRIVATEPROTECTSRV
*
* @version $Id$
*/
#ifndef __MMI_PRIVATEPROTECTSRV_H__
#define __MMI_PRIVATEPROTECTSRV_H__

#ifdef __APP_MMI_PRIVATEPROTECT__

/*-------------------------------------------------------------------------*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
#include "mmi_mae_model.h"
#include "mmi_base_util.h"
#include "mmi_cfgsrv.h"

/*-------------------------------------------------------------------------*/

#define PRIVATEPROTECTSRV_EVT_STATUS_CHANGE (CLSID_PRIVATEPROTECTSRV << 16 | 1)

enum
{
    PRIVATEPROTECTSRV_AUTH_ACTIVATED = 0,
    PRIVATEPROTECTSRV_AUTH_PASSED,
    PRIVATEPROTECTSRV_AUTH_FAILED,
    PRIVATEPROTECTSRV_AUTH_CANCELED,
};
typedef u8 PrivateProtectAuthResult_e;  // Authentication result for registered AP

enum
{
    PrivateprotectSrv_EVT_Protect_CalllogApp = 0 	//top ap is calllog,need check pw to protect
   ,PrivateprotectSrv_EVT_Protect_MessagecenterApp  //top ap is messagecenter,need check pw to protect
   ,PrivateprotectSrv_EVT_Protect_PhbApp			//top ap is phb,need check pw to protect
   ,PrivateprotectSrv_EVT_Protect_PrivateprotectApp	//top ap is privateprotect,need check pw to protect
   ,PrivateprotectSrv_EVT_Close_PrivateprotectpwApp	//close PrivateprotectpwApp

};
typedef u8 PrivateprotectSrv_ProtectType_e;	//pass evt to  privateprotectpwapp,in order to protect mentioned ap

enum
{
    PrivateprotectpwAPP_PW_Passed = 0
   ,PrivateprotectpwAPP_PW_Failed     
   ,PrivateprotectpwAPP_PW_Cancel
   ,PrivateprotectpwAPP_PW_ENDPressed
};
typedef u32 PrivateprotectApp_PwResult_e;   // Passwork verification result from password AP

typedef struct PrivateprotectpwApp_Info_tag
{
	PrivateprotectSrv_ProtectType_e eLaunchType;
	IModel *pIModel;
}PrivateprotectpwApp_Info_t;


/**
 * IPRIVATEPROTECTSRV Interfaces
 */
#define INHERIT_IPRIVATEPROTECTSRV(IName) \
    INHERIT_IHandler(IName); \
    MAE_Ret     (*GetActionModel)     ( IName * , IModel** ppActionModel, IBase* pOwner); \
    MAE_Ret     (*RegAuth)            ( IName * , IBase *pUser); \
    MAE_Ret     (*DeregAuth)          ( IName * , IBase *pUser); \
    MAE_Ret     (*GetItemProtectStatus)            ( IName * , MAE_ClsId id, boolean *bNeedVerifyPwProcedure)

DEFINE_INTERFACE(IPRIVATEPROTECTSRV);

#define IPRIVATEPROTECT_QueryInterface(pICntlr, id, pp, po)         GET_FUNCTBL((pICntlr), IPRIVATEPROTECTSRV)->QueryInterface(pICntlr, id, pp, po)

#define IPRIVATEPROTECT_HandleEvent(pICntlr, e, p1, p2)             GET_FUNCTBL((pICntlr), IPRIVATEPROTECTSRV)->HandleEvent(pICntlr, e, p1, p2)

/**
 Get action model for privateprotectpwapp
 */

#define IPRIVATEPROTECTSRV_GetActionModel(pICntlr, p1, p2) GET_FUNCTBL((pICntlr), IPRIVATEPROTECTSRV)->GetActionModel( pICntlr, p1, p2)

/**
 Register authentication with PrivateProtectSrv
 */
#define IPRIVATEPROTECTSRV_RegAuth(pICntlr, p1) GET_FUNCTBL((pICntlr), IPRIVATEPROTECTSRV)->RegAuth(pICntlr, p1)

/**
 Deregister authentication with PrivateProtectSrv
 */
#define IPRIVATEPROTECTSRV_DeregAuth(pICntlr, p1) GET_FUNCTBL((pICntlr), IPRIVATEPROTECTSRV)->DeregAuth(pICntlr, p1)

/**
Get class privateprotect protect data 
 */

#define IPRIVATEPROTECTSRV_GetItemProtectStatus(pICntlr, id, bNeedVerifyPwProcedure) GET_FUNCTBL((pICntlr),IPRIVATEPROTECTSRV)->GetItemProtectStatus(pICntlr,id, bNeedVerifyPwProcedure)


MAE_Ret PrivateProtectSrvNew(MAE_ClsId nId, void **ppObj);

/////////////////////////////////////////////////////////////////////////////////////////////////////////
//  Privateprotect Service interface
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif//#ifdef __APP_MMI_PRIVATEPROTECT__
#endif /* __MMI_PRIVATEPROTECTSRV_H__ */

