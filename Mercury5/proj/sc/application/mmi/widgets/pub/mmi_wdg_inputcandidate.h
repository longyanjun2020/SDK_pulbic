/**
@version $Id: mmi_wdg_inputcandidate.h 21485 2009-02-02 12:02:05Z alison.chen $
 */
#ifndef __MMI_WDG_INPUTCANDIDATE_H__
#define __MMI_WDG_INPUTCANDIDATE_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_vectormodel.h"
#include "mmi_mae_inputcontroller.h"
/*=============================================================*/
// type and define
/*=============================================================*/
typedef enum{
	DISPLAY_MODE_CHINESE_ON_SPELL,
	DISPLAY_MODE_CHINESE_ON_CANDIDATE,
	DISPLAY_MODE_CHINESE_ON_ASSOCIATION,
	DISPLAY_MODE_CHINESE_ON_ASSOCIATION_WITH_NUM_INDICATION,
	DISPLAY_MODE_HANDWRITING_CANDIDATE,
	DISPLAY_MODE_SINGLE_CANDIDATE,
#ifdef __IME_MMI_SG__
	//for 2-state
	DISPLAY_MODE_SMART_CANDIDATE_WITH_NUM_IND,
#endif //__IME_MMI_SG__
    DISPLAY_MODE_SMART_CANDIDATE
#if defined(__IME_MMI_CSTAR__) && !defined(__IME_MMI_SOFTKEYBOARD__)
    ,DISPLAY_MODE_KMX_CANDIDATE
#endif
} CandidateDisplayMode_e;


typedef struct{
    CandidateDisplayMode_e eDisplayMode;
    u32 pSpellListIndex;
    u8  nSpellCount;
    u8  nSpellWordLength;
    u8  nCandidateCount;
    u32 pCandidateListIndex;
    u32 nInputElementLen;
    u32 nItemWidth;
    u32 pCandidateListFirstIndex;
    u32 nTotalWidth;
    boolean bFirstPageCandiadte;
    boolean bLastPageCandiadte;
	boolean bSetFirstItemOnScreenForSpellList;
    boolean bPopupStyle;
    IVectorModel *pSpellVectorModel;    ///< vector model for spelling list
    IVectorModel *pCandidateVectorModel; ///< vector model for candidate list
#ifdef __IME_MMI_MY_STROKE_T__
	IVectorModel *pComponentVectorModel;  ///< vector model for component list
#endif
	boolean bModifyingModel;
    MAE_WChar wPhraseInputChar;
} InputCandidateModel_t;



typedef enum{
	EVT_SPELLLIST_FOCUS_SELECT,
	EVT_SPELLLIST_LEFT_ARROW_PRESSED,
	EVT_SPELLLIST_RIGHT_ARROW_PRESSED,
#ifdef __IME_MMI_MY_STROKE_T__
	EVT_COMPONENTLIST_FOCUS_SELECT,
#endif
	EVT_CANDIDATELIST_FOCUS_SELECT,
	EVT_CANDIDATELIST_FOCUS_CHANGE,
	EVT_CANDIDATELIST_LEFT_ARROW_PRESSED,
	EVT_CANDIDATELIST_RIGHT_ARROW_PRESSED,
	EVT_HANDWRITING_CANDIDATELIST_FOCUS_SELECT,
	EVT_HANDWRITING_CANDIDATELIST_FOCUS_CHANGE
}InputCandidateWidgetEvtType_e;
/*=============================================================*/
// macro property interface
/*=============================================================*/
/*=============================================================*/
// functions
/*=============================================================*/

#endif //__MMI_WDG_INPUTCANDIDATE_H__
/*=============================================================*/
// end of file
