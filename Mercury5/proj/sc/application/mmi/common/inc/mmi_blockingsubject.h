/**
 * @file mmi_blockingsubkect.h
 *
 * @brief  
 *         
 * @author 
 *         
 */
//////////////////////////////////////////////////////////////////////////


#ifndef __MMI_BLOCKINGSUBJECT_H__
#define __MMI_BLOCKINGSUBJECT_H__

//////////////////////////////////////////////////////////////////////////
//==========Includes=======================
#include "mmi_SubjectItf.h"
#include "mmi_subjectblockingtbl.h"

#define BLOCKING_SBJ "BlockingSBJ" // Blocking subject

typedef struct BlockingData_tag
{
    u32 reqBlockingId;
    u32 blockingCondition[MAX_BLOCKING_COND];
    u32 blockingDescr;
}BlockingData_t;

MAE_Ret BlockingSubjectHandler
(
    SubjectAction_e eSubjectAction,
    u32 nVariable, 
    void *pSubjectData, 
    SubjectStatus_e *pSbjStatus
);

void BlockingSubjectDefListener
(
    char *pSbjName, 
    SubjectStatus_e eSbjStatus, 
    void *pUser
);

MAE_Ret _RequestBlockingCondTble(u32 reqBlockingId, void *pSubjectData);

u32 BlockingSubjectGetInfoHandler(char* pSubjectName, void *pUser);

/*
7. MAE_RET code for subject request
MAE_RET_SUCCESS           : Request is successfully made.
MAE_RET_DUPLICATE_HANDLER : Request is ignored because it is a duplicate request for the same reqId which is not released yet.
MAE_RET_NOT_FOUND         : Requested subject does not exist.
MAE_RET_FAILED            : Request is not duplicate but fails.


8. MAE_RET code for subject release
MAE_RET_SUCCESS           : Release is successfully made.
MAE_RET_NOT_FOUND         : Subject for this release does not exist. 
                                                   Or request is ignored because there is no corresponding request existing.
*/

#endif //MMI_BLOCKINGSUBJECT_H__
