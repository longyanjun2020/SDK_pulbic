/**
 * @file    mae_inputcontroller_textengine.h
 * @brief   Implementation of textengine
 * @version $Id: mae_inputcontroller_textengine.h 24903 2009-03-05 03:47:12Z steve.lee $
 */
#ifndef __MAE_INPUTCONTROLLER_TEXTENGINE_H__
#define __MAE_INPUTCONTROLLER_TEXTENGINE_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/*=============================================================*/
// macro property interface
/*=============================================================*/

/*=============================================================*/
// functions
/*=============================================================*/

MAE_Ret InputController_TextEngine_Initialize(IBase *pThis);
void InputController_TextEngine_Release(IBase *pThis);
MAE_WChar InputController_TextEngine_Big5ToUnicode(MAE_WChar nBig5Code);
MAE_WChar InputController_TextEngine_GBToUnicode(MAE_WChar nGBCode);
MAE_WChar InputController_TextEngine_UnicodeToBig5(MAE_WChar nUCode);
MAE_WChar InputController_TextEngine_UnicodeToGB(MAE_WChar nUCode);

#ifdef __IME_MMI_ZI__
u32 InputController_TextEngine_GetPINYINStr(MAE_WChar nUCode, MAE_WChar *pOutBuf, u32 nMaxOutBifLen, MAE_LANG_CODE_e nInputLanguage);
#else
u32 InputController_TextEngine_GetPINYINStr(MAE_WChar nUCode, MAE_WChar *pOutBuf, u32 nMaxOutBifLen);
#endif

MAE_Ret InputController_TextEngine_GetMultitapCandidatesFromTextEngine(u32 nInLngCode, u32 nInputMode, u8 nKeyID, u8 nKeyRepeatTimes, u8 nCandidateStrMaxLen, MAE_WChar *pOutCandidates, MAE_WChar *pOutFocusedCandidate);

#endif //__MAE_INPUTCONTROLLER_TEXTENGINE_H__
/*=============================================================*/
// end of file
