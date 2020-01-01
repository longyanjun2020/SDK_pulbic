/**
* @file mmi_fdnsrv.h
*
* State Machine Service - FDNSRV
* Generated by XFSM v1.0, CodeVer=v0.24
*
* Class Id: CLSID_FDNSRV
*
*
* @version $Id: mmi_fdnsrv.h 33461 2009-06-16 08:06:40Z mark.yang $
*/
#ifndef __MMI_FDNSRV_H__
#define __MMI_FDNSRV_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
#include "mmi_mae_class.h"
#include "mmi_phbsrv.h"

#define MMI_FDNSRV_MAX_PIN2_PASSWORD_LEN 8

typedef enum
{
    MMI_FDNSRV_FDN_STATUS_NONE = 0
,    // SIM inactive
    MMI_FDNSRV_FDN_STATUS_WAIT
,         // FDNSrv is busy to get FDN status
    MMI_FDNSRV_FDN_STATUS_ACTIVE
,       // FDN active
    MMI_FDNSRV_FDN_STATUS_INACTIVE      // FDN inactive
} MMI_FDNSRV_FDN_STATUS_E;

typedef enum
{
    MMI_FDNSRV_FDN_SET_INACTIVE = 0
,    // set FDN to inactive
    MMI_FDNSRV_FDN_SET_ACTIVE           // set FDN to active
} MMI_FDNSRV_FDN_SET_STATUS_E;

typedef enum
{
    MMI_FDNSRV_FDN_FID_NONE = 0
   ,MMI_FDNSRV_FDN_FID_GET_STORAGE_STATUS
   ,MMI_FDNSRV_FDN_FID_SET_FDN_STATUS
   ,MMI_FDNSRV_FDN_FID_READ_ONE_FDN
,
    //MMI_FDNSRV_FDN_FID_READ_ALL_FDN,
    MMI_FDNSRV_FDN_FID_READ_ALL_FDN_TO_PHONE
   ,MMI_FDNSRV_FDN_FID_WRITE_ONE_NEW_FDN
   ,MMI_FDNSRV_FDN_FID_WRITE_ONE_FDN
   ,MMI_FDNSRV_FDN_FID_DELETE_ONE_FDN
} MMI_FDNSRV_FDN_FID_E;

typedef enum
{
    MMI_FDNSRV_Notify_Mask_ContactReady = 1
,    // read the FDN contact to phone completed
    MMI_FDNSRV_Notify_Mask_StatusReady = 2
  , // get FDN status completed
    MMI_FDNSRV_Notify_Mask_StatusChange = 4     // FDN status change
} MMI_PHB_NOTIFY_MASK_E;


/* Data Structures */
/*Data structures for Callback to service wrapper's callback function*/
typedef void (*SRV_FDN_SrvCB)(IBase *pCaller, MAE_EventId nEventID, void *ptCnf);

typedef struct Fdn_cbdata_tag
{
    IBase *pCaller; // the Srv Client From caller AP
    SRV_FDN_SrvCB pfnSrvCB; //the callback function defined in wrapper
} FdnSrvCallbackData_t;

typedef struct
{
    MMI_FDNSRV_FDN_STATUS_E FDNStatus;
    u16 u16UsedContact;
    u16 u16MaxContact;
    u8 u8NameLen;
    u8 u8NumberLen;
} Mmi_FDNSrvFDNStatus_t;

typedef struct
{
    u8 u8NameLen;
    u8 au8Name[MMI_PHB_NAME_LEN];

    u8 u8NumberLen;
    u8 au8Number[MMI_PHB_NUMBER_LEN];
} MmiPhbDhFDNBackupData_t;  /* 84 bytes */

/************************************************************************/
/* Request and Confirmation Data                                        */
/************************************************************************/

/*Set FDN Status*/
typedef struct
{
    u8 u8SimID;
    MMI_FDNSRV_FDN_SET_STATUS_E Status;
    u8 u8PIN2[MMI_FDNSRV_MAX_PIN2_PASSWORD_LEN];
} Mmi_FDNSrvSetFDNStatusReq_t;

typedef struct
{
    u8 u8SimID;
    MMI_FDNSRV_FDN_SET_STATUS_E Status;
    MmiPhbResult_e s32PhbResult;
} Mmi_FDNSrvSetFDNStatusCnf_t;

/*Write One FDN*/
#ifdef __3G_RIL_MMI__
/*This is for USIM, TS 31.102 4.2.24 EF FDN can contain extension records just ADN on USIM */
/*We use this structure to store the extension data (not including default number/name, only extension part) */
typedef struct 
{
    boolean bInUse; // false if not in use
    // for old group id, i think it is better to modify in VM_MRL_PHB_WRITE_GROUP_ENTRY_REQ. So i remove here
    // for old name id, do we need to delete it?
	u16					au16NewGroupId[MMI_PHB_USIM_GROUP_ID_NUM];/*group name index, this field value will be set 0xffff when not return value or no use.*/ 
	u16					au16NewNameId[MMI_PHB_USIM_NAME_ID_NUM];/*additional name index, this field value will be set 0xffff when not return value or no use.*/
	u8					au8Num[MMI_PHB_USIM_NUMBER_NUM - 1][MMI_PHB_NUMBER_LEN] ;/* storage format is ASCII format.First element of this field is phone number, and other elements are additional  phone number. The element value will be padded 0x00 when not return value or no use */

    // fdn always use 129 for type of number, so remove here
	u8					au8Name[MMI_PHB_USIM_NAME_NUM - 1][MMI_PHB_NAME_LEN] ;/* indicates name ,second name and additional name. The storage format is ASCII or UCS2 format and end with 0xFF. First element of this field is name ,second element is second name and other elements are additional name. The second name store in second name entry EF. Additional name store in additional number alpha string EF. The element value will be padded 0xff when not return value or no use. */
	MMI_PHB_USIM_HIDDEN_MODE_E s32hidden; /*indicates the information of record entry to need hidden or not*/
	MMI_PHB_REQ_MAIL_t  stMail[MMI_PHB_USIM_MAIL_NUM];/*is to store length and pointer of mail string. The storage format of mail string is ASCII or UCS2 format. The element value will be padded 0x00 when not return value or no use. When this field value is not equal zero, MMI must release the allocated memory*/
	MMI_PHB_REQ_GROUP_t   stGroup[MMI_PHB_USIM_GROUP_NUM]; /* is to store length and pointer of group string. The storage format of group string is ASCII or UCS2 format. First group string does not set group name index. 2~10 group string need set group name index in au16GropId[9]. The element value will be padded 0x00 when not return value or no use */
} Mmi_FDNSrvWriteOneFDNReqEx_t;
#endif //#ifdef __3G_RIL_MMI__ 

typedef struct
{
    u8 u8SimID;
    u16 u16PhysicalIdx;  // only used for write existing FDN
    MmiPhbDhFDNBackupData_t tFDNContact;
} Mmi_FDNSrvWriteOneFDNReq_t;

typedef struct
{
    u8 u8SimID;
    MmiPhbResult_e s32PhbResult;
} Mmi_FDNSrvWriteOneFDNCnf_t;

/*Delete One FDN*/
typedef struct
{
    u8 u8SimID;
    u16 u16PhysicalIdx;
} Mmi_FDNSrvDeleteOneFDNReq_t;

typedef struct
{
    u8 u8SimID;
    MmiPhbResult_e s32PhbResult;
} Mmi_FDNSrvDeleteOneFDNCnf_t;

/*GetFDN Name ByNumber*/
typedef struct
{
    u8 u8SimID;
    u8 u8NumberLen;
    u8 au8Number[MMI_PHB_NUMBER_LEN];
} Mmi_FDNSrvGetFDNNameByNumberReq_t;

typedef struct
{
    u8 u8SimID;
    u8 u8NameLen;
    u8 au8Name[MMI_PHB_NAME_LEN];
} Mmi_FDNSrvGetFDNNameByNumberCnf_t;

/**
* External Events
*/
#define FDNSRV_EVT_ContactReady             (CLSID_FDNSRV << 16 | 1)
#define FDNSRV_EVT_StatusReady              (CLSID_FDNSRV << 16 | 2)
#define FDNSRV_EVT_StatusChange             (CLSID_FDNSRV << 16 | 3)

#define FDNSRV_IEVT_TO_SET_STATUS_END               (CLSID_FDNSRV << 16 | 9)
#define FDNSRV_IEVT_TO_WRITE_ONE_FDN_END                (CLSID_FDNSRV << 16 | 10)
#define FDNSRV_IEVT_TO_DELETE_ONE_FDN_END               (CLSID_FDNSRV << 16 | 11)

/**
* IFDNSRV Interfaces
*/
#define INHERIT_IFDNSRV(IName) \
    INHERIT_IHandler(IName); \
    MAE_Ret     (*SetFDNStatusAsync)      ( IName * , Mmi_FDNSrvSetFDNStatusReq_t *ptReq, FdnSrvCallbackData_t *pCallbackData);  \
    MAE_Ret     (*GetFDNNameByNumber)       ( IName * , Mmi_FDNSrvGetFDNNameByNumberReq_t *ptReq, Mmi_FDNSrvGetFDNNameByNumberCnf_t *ptCnf);  \
    MAE_Ret     (*GetFDNStatusFullInfo)     ( IName * , Mmi_FDNSrvFDNStatus_t *ptFDNStatus, u8 u8SimId);  \
    MAE_Ret     (*GetFDNContact)        ( IName * , MmiPhbDhFDNBackupData_t  *ptContact, u8 u8SimId, u8 u8Idx);  \
    MAE_Ret     (*WriteOneContactAsync)       ( IName * , Mmi_FDNSrvWriteOneFDNReq_t *ptReq, FdnSrvCallbackData_t *pCallbackData);  \
    MAE_Ret     (*DeleteOneContactAsync)      ( IName * , Mmi_FDNSrvDeleteOneFDNReq_t *ptReq, FdnSrvCallbackData_t *pCallbackData);  \
    MAE_Ret     (*WriteOneNewContactAsync)        ( IName * , Mmi_FDNSrvWriteOneFDNReq_t *ptReq, FdnSrvCallbackData_t *pCallbackData);  \
    boolean     (*IsFDNReady)       ( IName * );  \
    MMI_FDNSRV_FDN_STATUS_E     (*GetFDNStatus)     ( IName * , u8 u8SimId);  \
    MAE_Ret     (*Register_Notification)        ( IName * , void *instance, MMI_PHB_NOTIFY_MASK_E s32Mask);  \
    MAE_Ret     (*Deregister_Notification)      ( IName * , void *instance, MMI_PHB_NOTIFY_MASK_E s32Mask)

DEFINE_INTERFACE(IFDNSRV);


#define IFDNSRV_QueryInterface(pICntlr, id, pp, po)         GET_FUNCTBL((pICntlr), IFDNSRV)->QueryInterface(pICntlr, id, pp, po)
#define IFDNSRV_HandleEvent(pICntlr, e, p1, p2)             GET_FUNCTBL((pICntlr), IFDNSRV)->HandleEvent(pICntlr, e, p1, p2)
/**
Purpose: This external interface is provided to set FDN status (asynchronous function)
Parameter:
<ptReq>: Cannot be null.
<ptCnf>: Cannot be null.
*/
#define IFDNSRV_SetFDNStatusAsync(pICntlr, p1, p2)    GET_FUNCTBL((pICntlr), IFDNSRV)->SetFDNStatusAsync( pICntlr, p1, p2)

/**
Purpose: This external interface is provided to get the name of FDN contact (synchronous function)
Parameter:
<ptReq>: Cannot be null. Mallocate/Free by function caller.
<ptCnf>: Cannot be null. Mallocate/Free by function caller.
*/
#define IFDNSRV_GetFDNNameByNumber(pICntlr, p1, p2) GET_FUNCTBL((pICntlr), IFDNSRV)->GetFDNNameByNumber( pICntlr, p1, p2)
/**
Purpose: This external interface is provided to get the FDN status full info of specific SIM  (synchronous function)
Parameter:
<ptFDNStatus>: Cannot be null. Mallocate/Free by function caller.
<u8SimId>: Which SIM status you want to get
*/
#define IFDNSRV_GetFDNStatusFullInfo(pICntlr, p1, p2)   GET_FUNCTBL((pICntlr), IFDNSRV)->GetFDNStatusFullInfo( pICntlr, p1, p2)
/**
Purpose: This external interface is provided to get the FDN contact of specific SIM  (synchronous function)
Parameter:
<ptContact>: Cannot be null. Mallocate/Free by function caller.
<u8SimId>: Which SIM you want to get
<u8Idx>: Which contact in the SIM you want to get
*/
#define IFDNSRV_GetFDNContact(pICntlr, p1, p2, p3)  GET_FUNCTBL((pICntlr), IFDNSRV)->GetFDNContact( pICntlr, p1, p2, p3)
/**
Purpose: This external interface is provided to write a FDN contact (asynchronous function)
Parameter:
<ptReq>: Cannot be null.
<ptCnf>: Cannot be null.
*/
#define IFDNSRV_WriteOneContactAsync(pICntlr, p1, p2) GET_FUNCTBL((pICntlr), IFDNSRV)->WriteOneContactAsync( pICntlr, p1, p2)

/**
Purpose: This external interface is provided to delete one contact (asynchronous function)
Parameter:
<ptReq>: Cannot be null.
<ptCnf>: Cannot be null.
*/
#define IFDNSRV_DeleteOneContactAsync(pICntlr, p1, p2)    GET_FUNCTBL((pICntlr), IFDNSRV)->DeleteOneContactAsync( pICntlr, p1, p2)

/**
Purpose: This external interface is provided to write a FDN contact (asynchronous function)
Parameter:
<ptReq>: Cannot be null.
<ptCnf>: Cannot be null.
*/
#define IFDNSRV_WriteOneNewContactAsync(pICntlr, p1, p2)  GET_FUNCTBL((pICntlr), IFDNSRV)->WriteOneNewContactAsync( pICntlr, p1, p2)

/**
Purpose: Check the FDN contacts is ready or not.
*/
#define IFDNSRV_IsFDNReady(pICntlr) GET_FUNCTBL((pICntlr), IFDNSRV)->IsFDNReady( pICntlr)

/**
Purpose: This external interface is provided to get the FDN status of specific SIM  (synchronous function)
Parameter:
<u8SimId>: Which SIM status you want to get
*/
#define IFDNSRV_GetFDNStatus(pICntlr, p1)   GET_FUNCTBL((pICntlr), IFDNSRV)->GetFDNStatus( pICntlr, p1)

/**

*/
#define IFDNSRV_Register_Notification(pICntlr, p1, p2)  GET_FUNCTBL((pICntlr), IFDNSRV)->Register_Notification( pICntlr, p1, p2)
/**

*/
#define IFDNSRV_Deregister_Notification(pICntlr, p1, p2)    GET_FUNCTBL((pICntlr), IFDNSRV)->Deregister_Notification( pICntlr, p1, p2)




/**
* Functions
*/

void FDNSRV_Init(void);

__SLDPM_FREE__ MAE_Ret FDNSRV_New(MAE_ClsId id, void **ppObj);

#endif /* __MMI_FDNSRV_H__ */