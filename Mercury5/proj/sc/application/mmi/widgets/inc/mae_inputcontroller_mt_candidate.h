/**
 * @file    mae_inputcontroller_mt_candidate.h
 * @brief   mae_inputcontroller_mt_candidate.h
 * @version $Id: mae_inputcontroller_mt_candidate.h 16064 2008-11-07 03:40:16Z alison.chen $
 */
#ifndef __MAE_INPUTCONTROLLER_MT_CANDIDATE_H__
#define __MAE_INPUTCONTROLLER_MT_CANDIDATE_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"

/*=============================================================*/
// type and define
/*=============================================================*/

#define MAX_MT_CANDIDATE_SIZE 40

#define __DYNAMIC_MULTITAP_CANDIDATE__
/*=============================================================*/
// macro property interface
/*=============================================================*/

/*=============================================================*/
// functions
/*=============================================================*/

__SLDPM_FREE__ MAE_Ret InputController_MT_Candidate_Init(IBase *pThis);
void InputController_MT_Candidate_FreeData(void *pData, IBase *pOwner);
__SLDPM_FREE__ void InputController_MT_Candidate_SetLanguage(u32 nInLngCode);
#ifdef __DYNAMIC_MULTITAP_CANDIDATE__
void InputController_MT_Candidate_GetDynamicCandidate_EN(MAE_WChar wPrecedingChr, MAE_WChar** ppUpperCaseStr, MAE_WChar** ppLowerCaseStr, MAE_WChar** ppPhoneBookStr);
void InputController_MT_Candidate_UpdateDynamicMTCandidateData(IBase *pThis);
#endif //__DYNAMIC_MULTITAP_CANDIDATE__
MAE_Ret InputController_MT_Candidate_GetByKey(u32 ShiftMode, u8 nKeyID, MAE_WChar *aryWCandidate, u8 nArySize, u8 *nCandidateSize);
void InputController_MT_Candidate_Release(IBase *pThis);

#endif //__MAE_INPUTCONTROLLER_TEXTENGINE_H__
/*=============================================================*/
// end of file
