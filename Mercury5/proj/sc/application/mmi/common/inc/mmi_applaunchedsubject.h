/**
 * @file mmi_blockingsubkect.h
 *
 * @brief  
 *         
 * @author 
 *         
 */
//////////////////////////////////////////////////////////////////////////


#ifndef __MMI_APPLAUNCHEDGSUBJECT_H__
#define __MMI_APPLAUNCHEDGSUBJECT_H__

//////////////////////////////////////////////////////////////////////////
//==========Includes=======================
#include "mmi_SubjectItf.h"
#include "mmi_subjectblockingtbl.h"


//////////////////////////////////////////////////////////////////////////
//[App Launched status subject]
//1.subject name
#define	APPLAUNCHED_STATUS_SBJ "AppLaunchedStatus"

//2.subject status: bit-aligned by using SBJSTS(a)
enum
{
    SBJ_APPLAUNCHED_NONE = SBJSTS(0),
    SBJ_APPLAUNCHED_START = SBJSTS(1),
    SBJ_APPLAUNCHED_STOP = SBJSTS(2),
    SBJ_APPLAUNCHED_RESUME = SBJSTS(3),
};

//3.request id
enum
{
    REQ_APPLAUNCHED
};

//4.variable
//The same as status enum

//5.Data type
typedef struct MonitorInfo_tag
{
    u32 nApmEvtMode;
    MAEEvent_t nEvt;
}MonitorInfo_t;

typedef struct AppLaunchedData_tag
{
    MonitorInfo_t tMonitorInfo;
    MAE_ClsId nClsId;
    u32 nApmStatus;          
}AppLaunchedData_t;




//6.handler function
MAE_Ret AppLaunchedSubjectHandler
(
    SubjectAction_e eSubjectAction,
    u32 variable, 
    void *pSubjectData, 
    SubjectStatus_e *pSbjStatus
);

void AppLaunchedSubjectDefListener
(
    char *pSbjName, 
    SubjectStatus_e eSbjStatus, 
    void *pUser
);

u32 AppLaunchedSubjectGetInfoHandler
(
    char* pSubjectName,
    void *pUser
);
//return value is a pointer that is a struct (AppClsId_t)

/*
7. MAE_RET code for subject request
MAE_RET_SUCCESS           : Request is successfully made.
MAE_RET_DUPLICATE_HANDLER : Request is ignored because it is a duplicate request for the same reqId which is not released yet.
MAE_RET_NOT_FOUND         : Requested subject does not exist.

8. MAE_RET code for subject release
MAE_RET_SUCCESS           : Release is successfully made.
MAE_RET_NOT_FOUND         : Subject for this release does not exist. 
                                                   Or request is ignored because there is no corresponding request existing.
*/

#endif //__MMI_APPLAUNCHEDGSUBJECT_H__
