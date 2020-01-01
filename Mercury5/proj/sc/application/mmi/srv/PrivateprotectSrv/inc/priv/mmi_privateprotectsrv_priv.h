/**
* @file mmi_privateprotectsrv_priv.h
*
* Class Id: CLSID_PRIVATEPROTECTSRV
*
* @version $Id:
*/
#ifndef __MMI_PRIVATEPROTECTSRV_PRIV_H__
#define __MMI_PRIVATEPROTECTSRV_PRIV_H__

#ifdef __APP_MMI_PRIVATEPROTECT__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_privateprotectsrv.h"
#include "mmi_mae_vectormodel.h"

/*=============================================================*/
// type and define
/*=============================================================*/

#define BREAKIF_DISPERROR(n,s) {\
	if(MAE_RET_SUCCESS != n) \
								{\
								LOG_ERROR(MMI_LEVEL_PRIVATEPROTECT, s,n);\
								ASSERT(MAE_RET_SUCCESS != n);\
								break; \
								}\
							  }
#define ARRAY_SIZE(a) (sizeof((a))/sizeof((a)[0]))
typedef struct
{
    MAE_ClsId nClsId;
    IBase *pUser;
    boolean bFocus; // TRUE if focused with authentication
} PrivateprotectAuthData_t;


typedef enum _ProtectedApGroupTag
{
    EN_PROTECTEDAP_GROUP_PRIVATEPROTECT = 0,
    EN_PROTECTEDAP_GROUP_CALLOG,
    EN_PROTECTEDAP_GROUP_PHB,
    EN_PROTECTEDAP_GROUP_MCA,
    EN_PROTECTEDAP_GROUP_UNKNOWN = 0xFF  //for error handling
}EN_PROTECTEDAP_GROUP;


typedef struct ProtectedApInfo_TAG
{
    MAE_ClsId CLSID;   	//protected ap class id
    boolean bPassedPW;	//is ap paas pw procedure
	u8 nGroupElementCnt;
    EN_PROTECTEDAP_GROUP enProtectedApGroup;
}ProtectedApInfo_t;

typedef struct PrivateprotectSrv_Tag
{
    DECLARE_FUNCTBL(IPRIVATEPROTECTSRV); // function table pointer
    u32 nRefCnt;     // reference count
    //Other Service Data
    ICFGSrv *pICFGSrv;
    
    IVectorModel *pIAuthVectorModel;    // Vecotr model to store registered Applet
    
    IModel *pIPrivateprotectActionModel;		//pwapp->srv , model listener will implement in pwapp

	IModel *pIPrivateprotectpwappKeyPressModel;	//srv->pwapp , model listener will implement in srv
	ModelListener_t PrivateprotectpwappKeyPressModelListener;			//after receive pwapp evt,need update srv vector
    MAE_ClsId TopProtectedApCLSID;
    boolean bIsTerminated;
    boolean bLaunchPwApp;
} PrivateprotectSrv_t;

/*-------------------------------------------------------------------------*/
#endif//#ifdef __APP_MMI_PRIVATEPROTECT__
#endif /* __MMI_PRIVATEPROTECTSRV_PRIV_H__ */


