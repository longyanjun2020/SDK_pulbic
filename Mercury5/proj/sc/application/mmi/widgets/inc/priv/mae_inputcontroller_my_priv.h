/**
 * @file mae_inputcontroller_guobi_priv.h
 * @brief This file defines the data structure of InputWidget
 *
 * @version $Id: mae_inputcontroller_guobi_priv.h 12030 2008-06-26 06:22:26Z alison.chen $
 */
#ifndef __MAE_INPUTCONTROLLER_MY_PRIV_H__
#define __MAE_INPUTCONTROLLER_MY_PRIV_H__

#ifdef __IME_MMI_MY__
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_controller.h"
#include "mmi_mae_inputcontroller.h"
#include "mmi_mae_common_def.h"
#include "mae_widgetbase.h"
#include "mmi_mae_langcode.h"
#include "mmi_common_cfg.h"
#include "myapi.h"
#include "mae_ime.h"
#ifdef __QWERTY_KEYPAD_INPUTMETHOD__
#include "mae_inputcontroller_priv.h"
#endif
/*=============================================================*/
// type and define
/*=============================================================*/

typedef enum{
	IME_SPELLING,
	IME_ASSOCIATION
}CHINESE_IME_STATE_e;

typedef enum{
	IME_INPUT_KEY,
	IME_INPUT_CODE
}IME_INPUT_TYPE_e;

#define IME_CANDIDATE_BUFFER_SIZE   256
#define IME_ELEMENT_BUFFER_SIZE     32
#define IME_MAX_SUPPORTED_INPUT_LANGUAGES 3
#define IME_SMARTINPUT_MAX_NUM_CANDIDATE  10
#define IME_MY_CH_BREAK_IN_PHRASE	0x0027
#define	IME_MAX_SAME_SPELLING_NUM	16


typedef struct{
	IController *pIController;
	u32 nInputMode;
	MYSelection *pSel;							///< MY Selection: the buffer for MY input method
    MYRC rc;

	//for smart input mode
	u32 nCandidateOffest;
	//for Chinese input mode
	u32 nSpellingCount;
	MYWORD *pSpellingBuffer;					///< for whole available spelling.
	MYWORD *pConvertedSpellingBuffer;			///< for whole available spelling.
	MYWORD *pCandidatesBuffer;
	MYWORD *pAssociationBuffer;
	MYWORD *pValidWordListBuffer;
	MYBYTE nMaxCandidates;
	MYBYTE nCurLanguage;
	CHINESE_IME_STATE_e eState;
#ifdef __QWERTY_KEYPAD_INPUTMETHOD__
	MYBYTE InputKey[IME_ELEMENT_BUFFER_SIZE/2]; // save input keys
	MYWORD	nQwertySpellBuffer[IME_SMARTINPUT_MAX_CANDIDATE_NUM];   //save the smart latin candidate
	u8 SaveInputLen;
#endif

	// for touch input
	boolean bGetSpellingFromPrefixSpelling;
	u8 aryPrefixMatchSpellingIdx[IME_MAX_SAME_SPELLING_NUM];
	MYWORD *aryPrefixMatchSpellingPtr[IME_MAX_SAME_SPELLING_NUM];
	u8		nPrefixMatchSpellingCount;

	boolean bSmartNoCandidate;
	boolean bSmartNoNextCandidate;
	boolean bEnableNextFetch;
	boolean bInputTone;
	s8		nSpellCode;

	u8		nInputLen;
	Chinese_LayoutSetting_t sLayoutSetting;
} MYData_t;


typedef enum
{
	MY_PREV_PAGE,
	MY_NEXT_PAGE,
	MY_CURRENT_PAGE
}PageDirection_e;

typedef struct{
    u32       maeLangCode;          //Language code in MAE
    u32       maeInputMethod;       //Input method in MAE
    MYBYTE  	myLangCode;         //corresponding Language code for MY
    MYBYTE		myInputMode;		//corresponding input mode for MY
} MYLdbData_t;

#ifdef __QWERTY_KEYPAD_INPUTMETHOD__
#define MAX_CHAR_NUMS_TO_QWERTYKEY    (5)
typedef struct{
	u16  Ucs[MAX_CHAR_NUMS_TO_QWERTYKEY];          //the mapping char  unicode for every key
	u8   ActualChNums;                  //the mapping char actual numbers of every key
}MYLatinQwertykeyInfo_t;
#endif /*__QWERTY_KEYPAD_INPUTMETHOD__*/

#define		_CHINESE_IME_PHRASE_INPUT__		1

/*=============================================================*/
// functions
/*=============================================================*/

void InputController_TextEngine_FreeData(void *pData, IBase *pOwner);
boolean _InputController_TextEngine_SetLanguageTable(IBase *pThis);
boolean _InputController_TextEngine_Latin_GetCandidateAndSetAssociatedParameters(MYData_t *pMYData);
boolean _InputController_TextEngine_CHINESE_GetSpelling(MYData_t *pMYData);
void _InputController_TextEngine_ConvertSpellingCode2UCS2(u32 nLen, MAE_WChar *pDest, MAE_WChar *pSrc, u32 nInputMode);
void _InputController_TextEngine_InitLatinPDBS(IBase *pThis);
void _InputController_TextEngine_SaveLatinPDBS(IBase *pThis, MYData_t *pMYData);
void _InputController_TextEngine_SetSearchOrder(void);
boolean _InputController_TextEngine_CHINESE_GetCandidate(PageDirection_e ePageDirection);
boolean _InputController_TextEngine_CHINESE_GetAssociateion(PageDirection_e ePageDirection);
boolean _InputController_TextEngine_CHINESE_PreparePrefixMatchSpell(MAE_WChar *pSpelling, u8 spellingLen, u8 nArySize, u8 rstIdxAry[], u8* nPrefixMatchedSpellingCount);
boolean _InputController_TextEngine_AddKey(void*pHandler, u32 nKeyID, IME_INPUT_TYPE_e eType);
boolean  _InputController_TextEngine_CHINESE_PinYinSpell_WorkAround(MAE_WChar *pSpelling, u8 spellingLen);
#ifdef __QWERTY_KEYPAD_INPUTMETHOD__
boolean _InputController_TextEngine_AddLatinQwertykey(void*pHandler, u32 nKeyID);//add by luo ren 20100722
boolean _InputController_TextEngine_AddChTrBPMFQwertykey(void*pHandler, u32 nKeyID);//add by luo ren 20100820
#endif /*__QWERTY_KEYPAD_INPUTMETHOD__*/
#endif //__IME_MMI_MY__

#endif //__MAE_INPUTCONTROLLER_MY_PRIV_H__
/*=============================================================*/
// end of file
