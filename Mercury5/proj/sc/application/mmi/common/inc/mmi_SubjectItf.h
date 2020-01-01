/**
 * @file SubjectItf.h
 *
 * @brief  The subject center will support the subject creating, deleting and handling.
 *         The subject can be subscribed by the object which is interested in this subject.
 *         When the status of subject is changed, the subject will notify all the listeners.
 *
 * @author Ted.lee@mstarsemi.com 
 *         jerry-hy.liu@mstarsemi.com
 */
//////////////////////////////////////////////////////////////////////////
//==========Includes=======================
#ifndef __MMI_SUBJECTITF_H__
#define __MMI_SUBJECTITF_H__

#include "mmi_mae_interface_def.h"
//////////////////////////////////////////////////////////////////////////
//The subject status is bit-aligned.
//bit28~bit31 is reserved for subject center used: default subject status.
#define SBJSTS(a) ( 1 << a)

#define SUBJECT_DEFAULT_STATUS_MASK 0xF0000000
#define SBJ_DEFAULT_STATUS_BIT_SHIFT 28

//The subject default status. All the subjects need to own these status.
enum
{
    SBJ_UNINIT = 1,
    SBJ_INIT,
    SBJ_BUSY
};
#define SUBJECT_UNINIT      (SBJ_UNINIT<<SBJ_DEFAULT_STATUS_BIT_SHIFT)
#define SUBJECT_INIT        (SBJ_INIT<<SBJ_DEFAULT_STATUS_BIT_SHIFT)
#define SUBJECT_BUSY        (SBJ_BUSY<<SBJ_DEFAULT_STATUS_BIT_SHIFT)
//For base applet used.
#define SUBJECT_NO_AUTO_HANDLE SUBJECT_UNINIT

//subject status: Whenever status change, subject will notify each listener.
typedef u32 SubjectStatus_e;

//subject's action which notifies the subject handler function
enum
{
    SBJ_ACT_CREATE = 0,
    SBJ_ACT_DELETE,
    SBJ_ACT_ACTIVATE,
    SBJ_ACT_REQUEST,
    SBJ_ACT_RELEASE
};
typedef u32 SubjectAction_e;

enum
{
    SBJ_NONE_REQ             = 0x00000000,
    SBJ_ALLOW_DUPLICATE_REQ  = 0x00000001, // allow request same reqId
    SBJ_ALLOW_QUEUE_NOTIFY   = 0x00000002, // allow recursive notify
    SBJ_ALLOW_QUERY_ONLY_REQ = 0x00000004  // allow request without release (query only)
};
typedef u32 SubjectAttribute_e;

typedef struct
{
    u32  reqId;
    void *pUser;
    u32 reqDesc;
    MAE_WChar *pReqDesc; // latest description about updating subject 
}SubjectRequest_t;

typedef void (*PfnSubjectListener)(char *pSbjName, SubjectStatus_e nSbjStatus, void *pUser);

typedef MAE_Ret (*PfnSubjectHandler)(SubjectAction_e nSubjectAction, u32 variable, void *pSubjectData, SubjectStatus_e* pSbjStatus);

typedef u32 (*PfnGetSubjectInfoHandler)(char *pSbjName, void *pUser);

typedef void (*PfnSubjectListenerEx)(char *pSbjName, SubjectStatus_e nSbjStatus, void *pUser, void *pData);

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
/** SubjectCenterInit
* @brief        
*
*/
void SubjectCenterInit(void);

/** SubjectCenterUnInit
* @brief        
*
*/
void SubjectCenterUnInit(void);

/** SubjectCreate
* @brief        
*
*/
MAE_Ret SubjectCreate(char *pSbjName, u32 nSbjDataSize, PfnSubjectHandler pSbjHandler, PfnSubjectListener defaultListener, PfnGetSubjectInfoHandler pfnInfoHandler);

/** SubjectDelete
* @brief        
*
*/
MAE_Ret SubjectDelete(char *pSbjName);

/** SubjectSetAttribute
* @brief        
*
*/
MAE_Ret SubjectSetAttribute(char *pSbjName, SubjectAttribute_e eAttr, boolean bSet);

/** SubjectGetAttribute
* @brief        
*
*/
SubjectAttribute_e SubjectGetAttribute(char *pSbjName);


/** SubjectGetData
* @brief        
*
*/
void* SubjectGetData(char *pSbjName);

/** SubjectGetInfo
* @brief        
* return COMMON_TXT_NULL_ID if not found
*/
u32 SubjectGetInfo(char *pSbjName, void *pUser);

/** SubjectGetStatus
* @brief        
*
*/
SubjectStatus_e SubjectGetStatus(char *pSbjName);

/** SubjectSubscribe
* @brief
*
*/
SubjectStatus_e SubjectSubscribe(char *pSbjName, void *pUser, PfnSubjectListener pfnListener);

/** SubjectUnSubscribe
* @brief        
*
*/
MAE_Ret SubjectUnSubscribe(char *pSbjName, void *pUser);

/** SubjectUnSubscribeAll
* @brief        
*
*/
MAE_Ret SubjectUnSubscribeAll(void *pUser);

/** SubjectRequest
* @brief        Duplicate request for the same reqId is Not allowed before the reqId is released. 
*               Caller will get MAE_RET_DUPLICATE_HANDLER. 
*               Different with the last one, this function allows the caller pass the text id as request description or any data.
* 
* Return values:
*    MAE_RET_SUCCESS           : Request is successfully made.
*    MAE_RET_DUPLICATE_HANDLER : Request is ignored because it is a duplicate request for the same reqId which is not released yet.
*    MAE_RET_NOT_FOUND         : Requested subject does not exist.
*
*    Other MAE_RET codes which depend on subject respectively. Please refer to subject header files
*
*/
MAE_Ret SubjectRequest(char *pSbjName, u32 reqId, void *pUser, u32 description, u32 variable, SubjectStatus_e* pSbjStatus);


/** SubjectRelease
* @brief        If a reqId does not exist(it maybe released before or is never requested).
*               Releasing the non-existing reqId will be ignored but caller still get MAE_RET_SUCCESS.
* 
* Return values:
*    MAE_RET_SUCCESS           : Release is successfully made.
*    MAE_RET_NOT_FOUND         : Subject for this release does not exist. 
*                                Or request is ignored because there is no corresponding request existing.
*
*    Other MAE_RET codes which depend on subject respectively. Pleaes refer to subject header files
*
*/
MAE_Ret SubjectRelease(char *pSbjName, u32 reqId, void *pUser, u32 variable, SubjectStatus_e* pSbjStatus);

/** SubjectRegisterAutoListener
* @brief   
*
*/
MAE_Ret SubjectRegisterAutoListener (char *pSbjName, void *pUser, SubjectStatus_e eAutoHandledStatus);

/** SubjectQuery
* @brief        query exists by redId. 
* Return values:
*    MAE_RET_SUCCESS           : Request is successfully made.
*    MAE_RET_NOT_FOUND         : Requested subject does not exist.
*
*    Other MAE_RET codes which depend on subject respectively. Please refer to subject header files
*
*/
MAE_Ret SubjectQuery(char *pSbjName, u32 reqId, SubjectRequest_t** pSubjectRequest);

#endif    //__MMI_SUBJECTITF_H__
