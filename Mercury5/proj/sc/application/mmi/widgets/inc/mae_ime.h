/**
 * \file    mae_input_common.h
 * \brief
 *
 * @version $Id: mae_input_common.h 35444 2009-07-09 04:52:44Z Mobile_CM $
 */
#ifndef __MAE_IME_H__
#define __MAE_IME_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mmi_mae_class.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_inputcontroller.h"
#include "mmi_mae_langcode.h"
//definition
typedef enum
{
	PERSONAL_USED_WORD_DICTIONARY = 0,
	PERSONAL_WORD_DICTIONARY,
}PersonalDB_e;

typedef struct{
	boolean bFirstPage;
	boolean bMorePage;
}Chinese_PageStatus_t;

typedef struct{
	u32 nMaxCandidatePerPage;
	u32 nPixelPerPage;
	u32 nGapBetweenCandidate;
	boolean bFixCandidateWidth;
}Chinese_LayoutSetting_t;

typedef enum
{
	FIRST_PAGE = 0,
	NEXT_PAGE,
	PREVIOUS_PAGE
}ChineseInputFetchType_e;

typedef enum
{
	CHINESE_CANDIDATE_TYPE_SPELL = 0,
	CHINESE_CANDIDATE_TYPE_CANDIDATE
} ChineseCandidatetype_e;


#define CHINESE_CANDIDATE_MAX_LEN 32
#define IME_SMART_MAX_CANDIDATE_LENGTH	32

//TextEngine

/** MaePl_InputEngine_Initialize
* @brief	 This function Initialize Input Engine for IME handler use.
*             It will return an interface object which you want to use in IME handler if successful.
*
* @param[in]   pThis(IBase*)     Shall be an IBase interface object to keep the return object.
*
* @retval         Function pointer for Input Engine to IME handler(pThis->pIMEPLHandler)
*/
__SLDPM_FREE__ void* MaePl_InputEngine_Initialize(IBase *pThis);

/** MaePl_InputEngine_Release
* @brief	 This function Release Input Engine for exit IME handler use.
*
* @param[in]   pHandler  Shall be a Function pointer for IME handler(pThis->pIMEPLHandler)
*
*/
void MaePl_InputEngine_Release(void* pHandler);

/** MaePl_InputEngine_ResetInputState
* @brief        Reset Input Engine state to default SPELL state
*
* @param[in]    pHandler         The pointer of IME handler (pThis->pIMEPLHandler)
*
*/
__SLDPM_FREE__ void MaePl_InputEngine_ResetInputState(void* pHandler);

/** MaePl_InputEngine_SwitchLangAndInputMethod
* @brief        Input Engine Switch Language And Input Method
*
* @param[in]    pHandler          The pointer of IME handler (pThis->pIMEPLHandler)
* @param[in]    nLang               The MAE Language code enm ID, ref. mae_langcode.h
* @param[in]    nInputMethod   The Input Method ID, ref. mae_inputcontroller.h input mode define
*
* @retval       MAE_RET_SUCCESS    Input Engine Switch Language And Input Method Success.
* @retval       MAE_RET_FAILED       Input Engine Switch Language And Input Method Failed.
*
*/
MAE_Ret MaePl_InputEngine_SwitchLangAndInputMethod(void *pHandler, MAE_LANG_CODE_e nLang, u32 nInputMethod);

/** MaePl_InputEngine_SwitchShiftMode
* @brief        Input Engine Switch Shift Mode for Abc, ABC or abc
*
* @param[in]    pHandler      The pointer of IME handler (pThis->pIMEPLHandler)
* @param[in]    nShiftMode   The Input Shift Mode ID. (ref.  mae_inputcontroller.h ShiftMode and mask define)
*                                          Current Input Shift status: IME_SHIFTMODE_Abc, IME_SHIFTMODE_ABC or IME_SHIFTMODE_abc
*
* @retval       MAE_RET_SUCCESS    Input Engine Switch Shift Mode for Abc, ABC or abc Success.
* @retval       MAE_RET_FAILED        Input Engine Switch Shift Mode for Abc, ABC or abc Failed.
*
*/
MAE_Ret MaePl_InputEngine_SwitchShiftMode(void *pHandler, u32 nShiftMode);

/** MaePl_InputEngine_AddKey
* @brief        Added Key & set input mode to Input Engine
*
* @param[in]    pHandler         The pointer of IME handler (pThis->pIMEPLHandler)
* @param[in]    nKeyID            The press Key ID number
*
* @retval          boolean            Add Key to Input Engine Sucess/Fail (TRUE or FALSE)
*
*/
boolean MaePl_InputEngine_AddKey(void* pHandler, u32 nKeyID);

/** MaePl_InputEngine_Latin_FetchCandidateString
* @brief     When use "SMART" input method, Fetch Candidate String from Input Engine for Latin(English) language
*
* @param[in]    pHandler              The pointer of IME handler (pThis->pIMEPLHandler)
* @param[in]    nCandidateOffset  The Candidate Offset, star from 0, this will accumulate when fetch 1 candidate done
*
* @param[out]  CandidateString    A pointer of Candidate String buffer for store candidate word
*
* @retval       MAE_RET_SUCCESS  Input Engine fetch Latin(English) language candidate Success.
* @retval       MAE_RET_FAILED     Input Engine fetch Latin(English) language candidate Failed.
*
*/
MAE_Ret MaePl_InputEngine_Latin_FetchCandidateString(void *pHandler, u32 nCandidateOffset, MAE_WChar *CandidateString);

/** MaePl_InputEngine_Latin_PredictNextWord
* @brief     When use "SMART" input method, input Committed String to Input Engine( Latin/English language) for Predict Next Candidate Word
*                This function is Zi input method support.
*
* @param[in]    pHandler               The pointer of IME handler (pThis->pIMEPLHandler)
* @param[in]    pCommittedString  A pointer of Committed String buffer for Predict Next Candidate Word
* @param[in]    nStrLen                 The String Length of pCommittedString
*
* @retval       MAE_RET_SUCCESS            Input Committed String to Input Engine( Latin/English language) for Predict Next Candidate Word Success.
* @retval       MAE_RET_FAILED                Input Committed String to Input Engine( Latin/English language) for Predict Next Candidate Word Failed.
* @retval       MAE_RET_NOT_SUPPORTED  Input Committed String to Input Engine( Latin/English language) for Predict Next Candidate Word is not Support.
*
*/
MAE_Ret MaePl_InputEngine_Latin_PredictNextWord(void *pHandler, MAE_WChar *pCommittedString, u32 nStrLen);

/** MaePl_InputEngine_Latin_AddWordIntoPDBS
* @brief     When use "SMART" input method, input Committed String to Input Engine( Latin/English language)
*                for Add Word Into PDBS(PersonalDB). ref. mae_ime.h PersonalDB_e structure
*                This function is Zi input method support.
*
* @param[in]    pHandler  The pointer of IME handler (pThis->pIMEPLHandler)
* @param[in]    pStr         A pointer of Committed String buffer for Add Word Into PDBS(PersonalDB)
* @param[in]    nStrLen    The String Length of pStr
* @param[in]    eID          The enm ID for  PERSONAL_USED_WORD_DICTIONARY or PERSONAL_WORD_DICTIONARY.
*
* @retval          boolean     Add Word Into PDBS(PersonalDB) Sucess/Fail (TRUE or FALSE)
*
*/
boolean MaePl_InputEngine_Latin_AddWordIntoPDBS(void *pHandler, MAE_WChar *pStr, u32 nStrLen, PersonalDB_e eID);

/** MaePl_InputEngine_CHINESE_FetchSpellString
* @brief        Fetch Spell String from Chinese Input Engine to input controller structure
*
* @param[in]    pHandler         The pointer of IME handler (pThis->pIMEPLHandler)
*
* @param[out]   pConvertedSpellAry       A pointer of Converted Spell Ary, it will put spelling word list to Spelling Buffer
* @param[out]   nSpellingNum               A pointer of Spelling Num, it will put total spelling word list number to Spelling Count
*
* @retval       MAE_RET_SUCCESS         Success.
* @retval       MAE_RET_FAILED            Failed.  pMYData is NULL.
*
*/
MAE_Ret MaePl_InputEngine_CHINESE_FetchSpellString(void *pHandler, MAE_WChar *pConvertedSpellAry[], u32 *nSpellingNum);

#ifdef __IME_MMI_MY_STROKE_T__
MAE_Ret MaePl_InputEngine_CHINESE_FetchComponentString(void *pHandler, MAE_WChar *pConvertedComponentAry, u32 *nComponentNum);
#endif
/** MaePl_InputEngine_CHINESE_SetSpellingIndex
* @brief        Set Spelling Index to Input Engine, it will "HighLight" spell index word
*
* @param[in]    pHandler         The pointer of IME handler (pThis->pIMEPLHandler)
* @param[in]    nSpellIdx         The Spell Index, this will set "HighLight" spell index word
*
* @retval       MAE_RET_SUCCESS         Success.
* @retval       MAE_RET_FAILED            Failed.
*
*/
MAE_Ret MaePl_InputEngine_CHINESE_SetSpellingIndex(void *pHandler, u32 nSpellIdx);

/** MaePl_InputEngine_CHINESE_SetSpelling
* @brief        Set Spelling word to Input Engine
*                   The function is genernal use for "SoftKeyboard" and "__TOUCH_SCREEN_MMI__" is define
*
* @param[in]    pHandler         The pointer of IME handler (pThis->pIMEPLHandler)
* @param[in]    pSpelling         A pointer of Spelling word buffer(from SoftKeyboard input), the Spelling word can use to fetch next candidate string
* @param[in]    nLen               The Length of pSpelling
*
* @retval       MAE_RET_SUCCESS         Success.
* @retval       MAE_RET_FAILED            Failed.
*
*/
MAE_Ret MaePl_InputEngine_CHINESE_SetSpelling(void *pHandler, MAE_WChar *pSpelling, u32 nLen);

/** MaePl_InputEngine_CHINESE_SetCandidate
* @brief        Set Candidate to Input Engine to fetch Association candidate and set Input Engin to IME_ASSOCIATION state
*
* @param[in]    pHandler         The pointer of IME handler (pThis->pIMEPLHandler)
* @param[in]    pCandidate      A pointer of Candidate buffer, the Candidate can use to fetch next association string
* @param[in]    nLen               The Length of pCandidate
*
*/
void MaePl_InputEngine_CHINESE_SetCandidate(void *pHandler, MAE_WChar *pCandidate, u32 nLen);

/** MaePl_InputEngine_CHINESE_SetCandidateIndex
* @brief        Set Candidate Index to Input Engine, the candidate word index form [0~5].
*                  When set Candidate index to Input Engine, it also fetch next association words and set state to IME_ASSOCIATION
*
* @param[in]    pHandler           The pointer of IME handler (pThis->pIMEPLHandler)
* @param[in]    nCandidateIdx   The Index of Candidate, it will set the candidate index to Input Engine
*
* @param[out]    eType              Return the Chinese Candidate type enm ID: CHINESE_CANDIDATE_TYPE_SPELL or CHINESE_CANDIDATE_TYPE_CANDIDATE
* @param[out]    nNewInputLen  Return the New Input Length of candidate
*
* @retval          boolean              Set Candidate Index to Input Engine Sucess/Fail (TRUE or FALSE)
*
*/
boolean MaePl_InputEngine_CHINESE_SetCandidateIndex(void *pHandler, u32 nCandidateIdx, ChineseCandidatetype_e* eType, u32* nNewInputLen);

/** MaePl_InputEngine_CHINESE_GetInputKeyFromSign
* @brief        Get Input Key(physical keypad ID) From Sign(Softkeyboard press key's ASCII code), use for input method=MAE_INPUTMODE_STROKE
*                   The function is genernal use for "SoftKeyboard" and "__TOUCH_SCREEN_MMI__" is define
*
* @param[in]    pHandler         The pointer of IME handler (pThis->pIMEPLHandler)
* @param[in]    nSign              The Softkeyboard press key's Sign ID(ASCII code)
* @param[in]    nInputMethod  The Input Method eum ID(MAE_INPUTMODE_STROKE), ref. mae_inputcontroller.h, input mode define.
*
* @retval          u32                  Mapping Softkeyboard press key to Physical keypad ID(ref. mae_event.h, MAE key codes used in keypad events).
*
*/
u32 MaePl_InputEngine_CHINESE_GetInputKeyFromSign(void *pHandler, MAE_WChar nSign, u32 nInputMethod);

/** MaePl_InputEngine_CHINESE_LayoutSetting
* @brief        Set layout setting to Input engine.
*
* @param[in]    tLayoutSetting    The pointer of Chinese Layout Setting structure: ref. Chinese_LayoutSetting_t
*
*/
__SLDPM_FREE__ void MaePl_InputEngine_CHINESE_LayoutSetting(Chinese_LayoutSetting_t* tLayoutSetting);

/** MaePl_InputEngine_CHINESE_FetchCandidateString
* @brief        Fetch Candidate String based on FIRST_PAGE, NEXT_PAGE or PREVIOUS_PAGE.
*                  1 page have 6 Candidate words (base on pMYData->sLayoutSetting.nMaxCandidatePerPage).
*
* @param[in]    pHandler         The pointer of IME handler (pThis->pIMEPLHandler)
* @param[in]    type                The  Chinese Input Fetch Type includes: FIRST_PAGE, NEXT_PAGE or PREVIOUS_PAGE
*
* @param[out]   pOutput               A pointer of Output buffer, it will put candidate list to Candidate Buffer
* @param[out]   nCandidateNum    A pointer of Candidate Num, it will put total candidate list numbers to Candidate Count
* @param[out]   pPageStatus         A pointer of Page Status, it will update bFirstPage, bMorePage status
*
* @retval       MAE_RET_SUCCESS         Success.
* @retval       MAE_RET_FAILED            Failed.  pMYData is NULL.
*
*/
MAE_Ret MaePl_InputEngine_CHINESE_FetchCandidateString(void *pHandler, ChineseInputFetchType_e type, MAE_WChar *pOutput[],u32 *nCandidateNum, Chinese_PageStatus_t *pPageStatus);

/** MaePl_InputEngine_CHINESE_GetSpellingWordSeparator
* @brief            Get the Spelling Word Separatorit from Input Engine
*
* @param[in]    pHandler   The pointer of IME handler (pThis->pIMEPLHandler)
*
* @param[out]  wChar       A pointer of Spelling Word Separator Char buffer.
*                                      It will get Spelling Word Separator from Input Engine to Char buffer, it can tell Input Engine to separate(break) phrase.
*                                      The Spelling Word Separator, Ex: in MY is IME_MY_CH_BREAK_IN_PHRASE(0x0027),  in Zi is 0.
*
*/
void MaePl_InputEngine_CHINESE_GetSpellingWordSeparator(void *pHandler, MAE_WChar *wChar);

/** MaePl_InputEngine_KeyToQwertykey
* @brief         When use Qwerty keypad, Mapping press KeyID To Qwerty keypad keyID.
*                   The function is genernal use for "__QWERTY_KEYPAD_INPUTMETHOD__" is define
*                   This function will mapping MAE_KEY_STAR->MAE_KEY_A, MAE_KEY_HASH->MAE_KEY_Q and other key doesn't need mapping.
*                   MAE_KEY_STAR is mean launch symbol table, MAE_KEY_HASH is mean switch input method.
*
* @param[in]    KeyId  The press Key Id.
*
* @retval          u32     Return Mapping Qwerty keypay KeyId.
*
*/
#ifdef __QWERTY_KEYPAD_INPUTMETHOD__
u32 MaePl_InputEngine_KeyToQwertykey(u32 KeyId);
#endif

//below function is not use now
boolean InputController_TextEngine_CHINESE_ResetTone(u32 nInputLen);
boolean InputController_TextEngine_CHINESE_SetTone(MAE_WChar *pCurrentSpell, MAE_WChar **pToneSpell);
boolean MaePl_InputEngine_CHINESE_ClearTone(void *pHandler);
MAE_Ret MaePl_InputEngine_CHINESE_SetTone(void *pHandler, u32 tone);

#if __IME_MMI_SG__
boolean MaePl_InputEngine_IsSpellFocus(void* pHandler);
boolean MaePl_InputEngine_IsCandidateFocus(void* pHandler);
boolean MaePl_InputEngine_IsAssociateFocus(void* pHandler);
boolean MaePl_InputEngine_ProcessKey(void* pHandler, u32 nKeyID);
MAE_Ret MaePl_InputEngine_CHINESE_FetchPreselectString(void *pHandler, MAE_WChar *PreselectString, u32 nMaxLen, boolean* bCommit);
u32 MaePl_InputEngine_GetInputElementLen(void* pHandler);
#endif

#endif /* __MAE_IME_H__ */

