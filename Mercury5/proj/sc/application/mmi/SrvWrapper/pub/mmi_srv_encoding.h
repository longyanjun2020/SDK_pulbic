/**
* @file    mmi_srv_encoding.h
* @brief   
*          
*/

#ifndef __MMI_SRV_ENCODING_H__
#define __MMI_SRV_ENCODING_H__


/*-----------------------------------------------------*/
#include "mmi_srv_client_commondefine.h"
#include "mmi_encodingsrv.h"


/** SrvEncodingGetMultitapCandidate
@brief Get multitap candidates. 

@param[in]      nShiftMode              Set IME mode. value like IME_SHIFTMODE_ABC (defined in mae_inputcontroller.h)
@param[in]      nKeyID                  input key. value like MAE_KEY_0 (defined in mae_event.h, should be between MAE_KEY_1 and MAE_KEY_0)
@param[in]      nKeyRepeatTimes         Key repeat times.
@param[in]      pOutFocusedCandidate    Focused candidate.

@retval MAE_RET_SUCCESS                 If successful.
@retval MAE_RET_FAIL                    If an error happen. 
*/
MAE_Ret SrvEncodingGetMultitapCandidate(u32 nShiftMode,
                                        u8 nKeyID,
                                        u8 nKeyRepeatTimes,
                                        MAE_WChar *pOutFocusedCandidate);

/** SrvEncodingSetMultitapCandidateLanguage
@brief Set language for multitap candidate.

@param[in]      eLangCode               Language code. (defined in mae_langcode.h)
*/
void SrvEncodingSetMultitapCandidateLanguage(MAE_LANG_CODE_e eLangCode);

#endif //__MMI_SRV_ENCODING_H__
/*-----------------------------------------------------*/
