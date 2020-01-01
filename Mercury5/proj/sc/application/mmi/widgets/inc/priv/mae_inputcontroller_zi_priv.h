/**
 * @file mae_inputcontroller_zi_priv.h
 * @brief This file defines the data structure of InputWidget
 *
 * @version $Id: mae_inputcontroller_zi_priv.h 31865 2009-05-25 17:04:57Z sho.ding $
 */
#ifndef __MAE_INPUTCONTROLLER_ZI_PRIV_H__
#define __MAE_INPUTCONTROLLER_ZI_PRIV_H__

#ifdef __IME_MMI_ZI__
/*=============================================================*/
// include
/*=============================================================*/
#include "ezicmn.h"
#include "ezitext.h"
#include "mmi_mae_inputcontroller.h"
#include "mmi_mae_controller.h"
#include "mmi_mae_common_def.h"
#include "mae_widgetbase.h"
#include "mmi_mae_langcode.h"
#include "mmi_common_cfg.h"
#include "mae_ime.h"

/*=============================================================*/
// type and define
/*=============================================================*/

typedef enum{
	IME_SPELLING,
	IME_ASSOCIATION
}CHINESE_IME_STATE_e;

typedef struct {
    //for smart input
    //IController *pIController;
    ZI8GETPARAM zi8param;           ///< ZI parameter structure
    ZI8WCHAR *candidatesBuffer;     ///< candidate buffer
    ZI8WCHAR *elementBuffer;        ///< input key buffer
    ZI8UCHAR *myPUWD;	        ///< Reserved RAM for the Personal Used Word Dictionary
	ZI8UCHAR *myPD;		        ///< Reserved RAM for the Personal Dictionary
	ZI8UCHAR latinPUWDID;
	ZI8UCHAR latinPDID;
    int idxZiLdbData;               ///< the index of corresponding ZiLdbData
    ZI8WCHAR *validCandidatesBuffer;     ///< valid candidate buffer
	ZI8WCHAR *currentSpellingBuffer;		///< contain the spelling when setting Spelling
	ZI8WCHAR *currentCandidateBuffer;			///< Contain the candidate when setting candidate.

    //for normal candidate fetch
    u32 nInputLen;
    u32 nCurrentInputMode;
	int MinEnableCandidateOffset;
	int MaxEnableCandidateOffset;
    u32 nCandidatePageStartIdx;
    u32 nCandidatePageEndIdx;
	boolean bEnableNextFetch;
    boolean bInputTone;

	//for smart input
	boolean bNoCandidateWhenFirstCandidateIsZero;	///< There is no candidate if the first candidate is ZERO. ;

    //for Chinese input
    CHINESE_IME_STATE_e eState;
    ZI8WCHAR *spellingBuffer;       ///< spelling buffer
    ZI8WCHAR *toneSpellBuffer;       ///< spelling buffer with tone
    MAE_WChar *convertedSpellingBuffer;     ///< spelling buffer within converted text
    ZI8WCHAR tone;
    int nSpellingCount;
    Chinese_LayoutSetting_t sLayoutSetting;

    //ZiTextGlobal variables
    ZI8VOID ZI8RAMPOINTER peZiTextGlobals;

    MAE_LANG_CODE_e currentLangCode;
} ZiData_t;


typedef struct{
    u32       maeLangCode;          //Language code in MAE
    u32       maeInputMethod;       //Input method in MAE
    ZI8UCHAR  zi8LangCode;          //corresponding Language code for Zi8
    ZI8UCHAR  zi8SubLanguage;       //zi8 sub language
    ZI8UCHAR *ZiLdbAry;  //Zi8 LDB array
	//ZI8UCHAR ZI8ROMDATA *ZiLdbAry;  //Zi8 LDB array
    ZI8UCHAR  Spelling_GetMode;      //Zi8 mode for getting spelling
    ZI8UCHAR  Spelling_GetOptions;   //Zi8 option for getting spelling
    ZI8UCHAR  Candidate_GetMode;     //Zi8 mode for getting candidate
    ZI8UCHAR  Candidate_GetOptions;  //Zi8 option for getting candidate
} Zi8LdbData_t;

#define INPUT_LATIN_USED_WORD_DICTIONARY_SIZE   512
#define INPUT_LATIN_PERSONAL_DICTIONARY_SIZE	512

typedef struct {
	ZI8UCHAR PUWD[INPUT_LATIN_USED_WORD_DICTIONARY_SIZE];
	ZI8UCHAR PD[INPUT_LATIN_PERSONAL_DICTIONARY_SIZE];
}ZiPDRAI_t;

#define MAE_ZI_PREDICTIVE_INDICATOR_MORE  0x003E
#define MAE_ZI_PREDICTIVE_INDICATOR_STAR  0x002A

#define IME_SMART_CANDIDATE_BUFFER_SIZE	256
#define IME_CANDIDATE_BUFFER_SIZE   32
#define IME_SPELLING_BUFFER_SIZE	256
#define IME_ELEMENT_BUFFER_SIZE     32
#define IME_MAX_SUPPORTED_INPUT_LANGUAGES 8

#define IME_SMARTINPUT_MAX_NUM_CANDIDATE  10


extern ZI8UCHAR ZI8ROMDATA Zi8DatENPRC[];
extern ZI8UCHAR ZI8ROMDATA Zi8DatZHA[];
extern ZI8UCHAR ZI8ROMDATA Zi8DatZH_TW[];
extern  ZI8UCHAR ZI8ROMDATA Zi8DatZ1[];
extern ZI8UCHAR ZI8ROMDATA Zi8DatENABC[];
/*=============================================================*/
// functions
/*=============================================================*/

void InputController_TextEngine_FreeData(void *pData, IBase *pOwner);
boolean _InputController_TextEngine_SetLanguageTable(IBase *pThis, MAE_LANG_CODE_e nLang);
boolean _InputController_TextEngine_Latin_GetCandidateAndSetAssociatedParameters(ZiData_t *pZiData);
boolean _InputController_TextEngine_CHINESE_GetSpelling(ZiData_t *pZiData);
void _InputController_TextEngine_ConvertSpellingCode2UCS2(u32 nLen, MAE_WChar *pDest, MAE_WChar *pSrc);
void _InputController_TextEngine_InitLatinPDBS(IBase *pThis);
void _InputController_TextEngine_SaveLatinPDBS(IBase *pThis, ZiData_t *pZiData);
void _InputController_TextEngine_SetSearchOrder(void);

boolean _InputController_TextEngine_CHINESE_GetCandidate(u32 nFirstCandidate, u32 nMaxCandidate);
boolean _InputController_TextEngine_CHINESE_GetAssociateion(u32 nAssociatedStartIdx,  u32 nMaxCandidate);
#endif //__IME_MMI_ZI__

#endif //__MAE_INPUTCONTROLLER_ZI_PRIV_H__
/*=============================================================*/
// end of file
