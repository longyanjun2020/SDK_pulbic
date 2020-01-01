/**
 * @file mmi_subjectcenter.h
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
#ifndef __MMI_SUBJECTCENTER_H__
#define __MMI_SUBJECTCENTER_H__

//////////////////////////////////////////////////////////////////////////
//==========Includes=======================
#include "mmi_SubjectItf.h"
//////////////////////////////////////////////////////////////////////////
//==========Types&Data=====================

//////////////////////////////////////////////////////////////////////////
// Subject Center API
void DoSubjectCenterInit(void);
void DoSubjectCenterUnInit(void);
MAE_Ret DoSubjectCreate(char *pSbjName, u32 nSbjDataSize, PfnSubjectHandler pSbjHandler, PfnSubjectListener defaultListener, PfnGetSubjectInfoHandler pfnInfoHandler);
MAE_Ret DoSubjectDelete(char *pSbjName);
MAE_Ret DoSubjectSetAttribute(char *pSbjName, SubjectAttribute_e eAttr, boolean bSet);
SubjectAttribute_e DoSubjectGetAttribute(char *pSbjName);
void* DoSubjectGetData(char *pSbjName);
u32 DoSubjectGetInfo(char *pSbjName, void *pUser);
SubjectStatus_e DoSubjectGetStatus(char *pSbjName);

SubjectStatus_e DoSubjectSubscribe(char *pSbjName, void *pUser, PfnSubjectListener pfnListener);
MAE_Ret DoSubjectUnSubscribe(char *pSbjName, void *pUser);
MAE_Ret DoSubjectUnSubscribeAll(void *pUser);
MAE_Ret DoSubjectRequestByStr(char *pSbjName, u32 reqId, void *pUser, MAE_WChar *pDescription, u32 variable, SubjectStatus_e* pSbjStatus);
MAE_Ret DoSubjectRequestByTextId(char *pSbjName, u32 reqId, void *pUser, u32 description, u32 variable, SubjectStatus_e* pSbjStatus);
MAE_Ret DoSubjectRelease(char *pSbjName, u32 reqId, void *pUser, u32 variable, SubjectStatus_e* pSbjStatus);
MAE_Ret DoSubjectRegisterAutoListener (char *pSbjName, void *pUser, SubjectStatus_e eAutoHandledStatus);

boolean DoGetSubjectRequest(const char *pSbjName, u32 reqId, SubjectRequest_t** pSubjectRequest);

#endif    //__MMI_SUBJECTCENTER_H__
