#ifndef __MAE_INPUTCONTROLLER_KMX_PRIV_H__
#define __MAE_INPUTCONTROLLER_KMX_PRIV_H__

#ifdef __IME_MMI_CSTAR__
#include "kmximeapi.h"
#include "mae_widget.h"
#include "mmi_mae_display.h"
#include "mae_ime.h"

//for handwriting

#include "mae_controller.h"
#include "mae_inputcontroller.h"
#include "mae_inputcontroller_priv.h"
#include "mmi_mae_common_def.h"
#include "mae_widgetbase.h"
#include "mmi_mae_langcode.h"
#include "mmi_common_cfg.h"

#ifdef __cplusplus 
extern "C"{ 
#endif 


#define IME_ELEMENT_BUFFER_SIZE     32
#define	IME_MAX_SAME_SPELLING_NUM	16

#define MYCHAR    char
#define MYSHORT   short
#define MYLONG    long
#define MYBYTE  unsigned char
#define MYWORD  unsigned short
#define MYDWORD unsigned long
#define MYBOOL  unsigned char
#define MYTRUE      1
#define MYFALSE     0
#define CHAR_NULL   '\0'
#define CHAR_SPACE  ' '
#define MYNULL      0
#define MYRC                            MYWORD
#define MYRC_OK                         ((MYWORD)0X0000)
#define MYRC_NONE                       ((MYWORD)0X0001)
#define MYRC_DEFINE_MODE                ((MYWORD)0X0002)
#define MAX_PINYIN_CODE			15
#define MAX_SELECTION_LEN		30
#define MAX_PINYIN_BUF_LEN		(MAX_PINYIN_CODE*15)
#define	MY_STAT_MORE			(MYWORD) 0X0001
typedef struct MYSelection_s {
    MYBYTE  bLangID;
    MYBYTE  bInputMode;
    MYBYTE  bKeyBufLen;
    MYBYTE  bSpellCode;
    MYBYTE  bCurCharIndex;
    MYWORD  pwComponent[5];
    MYBYTE  bSelectionNum;
    MYBYTE  bPageIndex;
    MYBYTE  bEntryLen;
    MYWORD  pwSelection[MAX_SELECTION_LEN];
    MYWORD  wState;
} MYSelection;
typedef enum{
	IME_SPELLING,
	IME_ASSOCIATION
}CHINESE_IME_STATE_e;

typedef enum{
	IME_INPUT_KEY,
	IME_INPUT_CODE
}IME_INPUT_TYPE_e;

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
		MYBYTE InputKey[IME_ELEMENT_BUFFER_SIZE]; // save input keys
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

#ifdef __cplusplus 
} 
#endif 

#endif //__IME_MMI_CSTAR__
#endif //__MAE_INPUTCONTROLLER_KMX_PRIV_H__
