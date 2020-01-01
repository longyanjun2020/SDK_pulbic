/**
 * @file    mmi_wdg_inputcandidate_priv.h
 * @brief   Private structure and definitions of ChineseSelectionWidget
 * @version $Id: mmi_wdg_inputcandidate_priv.h 25372 2009-03-11 08:10:22Z mark.yang $
 */
#ifndef __MMI_WDG_INPUTCANDIDATE_PRIV_H__
#define __MMI_WDG_INPUTCANDIDATE_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_forward.h"
#include "mae_propcontainerbase.h"
#include "img_data.h"
#include "mmi_mae_inputcontroller.h"
#ifdef __TOUCH_SCREEN_MMI__
#include "mmi_wdg_button.h"
#endif
#ifdef __IME_MMI_CSTAR__
#include "mae_inputcontroller_priv.h"
#endif

/*=============================================================*/
// type and define
/*=============================================================*/


typedef struct{
	u32 fontCate;
	u32 fontType;
	RGBColor_t rgbTextColor;
}TextFont;

#ifdef __TOUCH_SCREEN_MMI__

typedef struct {
    ButtonData_t pButtonData;
    u8 nButtonId;
} InputCandidateWidget_ButtonData_t;

typedef enum {
    INPUTCANDIDATE_CANDIDATE_BUTTON_UPPER,
    INPUTCANDIDATE_CANDIDATE_BUTTON_DOWN,
    INPUTCANDIDATE_SPELL_BUTTON_LEFT,
    INPUTCANDIDATE_SPELL_BUTTON_RIGHT
} InputCandidateWidget_Button_e;

#endif

typedef struct {
    PropContainerBase_t PCntrBase;
	IShell *pIShell;
	IFONT  *pIFont;
	ModelListener_t	MdlListener;        ///> model listener for Data Model
	CandidateDisplayMode_e eDisplayMode;
	u32 nSpellFontHeight;
	u32 nCandidateFontHeight;
#ifdef __IME_MMI_MY_STROKE_T__
	u32 nComponentFontHeight;
#endif
	u32 nSpellNumPerPage;

    IWidget *pSpellList;
    IWidget *pCandidateList;
    IDATAMODEL  *pCandidateDataModel;
    IWidget *pSpellItemWidget;       ///< the item widget for list widget, it is a text widget.
    IWidget *pCandidateItemWidget;       ///< the item widget for list widget, it is a text widget.

    IWidget*	pSpellLeftImage;
    IWidget*	pSpellRightImage;
    IWidget*	pSpellBGImage;

    IWidget*	pCandidateLeftImage;
    IWidget*	pCandidateRightImage;
    IWidget*	pCandidateUpImage;
    IWidget*	pCandidateDownImage;
    IWidget*	pCandidateBGImage;
#ifdef __IME_MMI_MY_STROKE_T__
	IWidget*	pComponentList;
	IWidget*	pComponentBGImage;
	IWidget*	pComponentItemWidget;
#endif //__MMI_CHINESE_STROKE_T__
    u32 nCandidateCount;
    u32 nSpellCount;
    boolean bNumberAssociation;
    boolean bPopupStyle;
#ifdef __IME_MMI_MY_STROKE_T__
	boolean bIsShowComponent;
	IContainer *pComponentContainer;
#endif //__MMI_CHINESE_STROKE_T__

    IContainer *pSpellContainer;
    IContainer *pCandidateContainer;
	TextFont selNoTextFont;
	boolean  bImgloaded;
#ifdef __IME_MMI_SG__
	boolean bOnlyOnePageSpellList;  /// < BOOLEAN, set only one page spell list (TRUE/FALSE)
#endif
#ifdef __IME_MMI_CSTAR__
#ifndef __IME_MMI_SOFTKEYBOARD__
    InputController_t *piController;
#endif
#endif
} InputCandidateWidget_t;


/* FONT_TYPE 0 ==> Normal type */
#define INPUTCANDIDATE_DEFAULT_FONT_TYPE FONT_TYPE_NORMAL     ///< default font type
/* font size */
#define INPUTCANDIDATE_SPELLLIST_FONT_SIZE FONT_CAT_IME_NORMAL       ///< default font size for spell list
#define INPUTCANDIDATE_CANDIDATELIST_FONT_CATE FONT_CAT_NORMAL       ///< default font size for candidate list

#ifdef __IME_MMI_MY_STROKE_T__
#define INPUTCANDIDATE_COMPONENTLIST_FONT_CATE FONT_CAT_NORMAL           ///< default font size for component list	
#endif //__IME_MMI_MY_STROKE_T__
#define INPUTCANDIDATE_SPELLING_DEFAULT_FONT_COLOR RGBCOLOR_BLACK ///< Default text color
#define INPUTCANDIDATE_SPELLING_DEFAULT_HIGHLIGHT_COLOR RGBCOLOR_BLACK ///< Default text color
#define INPUTCANDIDATE_SPELLING_DEFAULT_FOCUSED_BG_COLOR COLOR_BLUE_7
#define INPUTCANDIDATE_SPELLING_DEFAULT_NOT_FOCUSED_BG_COLOR COLOR_GREY_3
#define INPUTCANDIDATE_CANDIDATE_DEFAULT_FONT_COLOR RGBCOLOR_WHITE ///< Default text color
#define INPUTCANDIDATE_CANDIDATE_DEFAULT_HIGHLIGHT_COLOR RGBCOLOR_BLACK ///< Default text color
#ifdef __IME_MMI_MY_STROKE_T__
#define INPUTCANDIDATE_COMPONENT_DEFAULT_FONT_COLOR RGBCOLOR_WHITE ///<Default text color
#define INPUTCANDIDATE_COMPONENT_DEFAULT_HIGHLIGHT_COLOR RGBCOLOR_BLACK  ///<Default text color
#define INPUTCANDIDATE_COMPONENT_DEFAULT_FOCUSED_BG_COLOR COLOR_BLUE_7
#endif
#define INPUTCANDIDATE_HANDWRITING_CANDIDATE_DEFAULT_FONT_COLOR RGBCOLOR_BLACK ///< Default text color


#define INPUTCANDIDATE_DEFAULT_SELECTITEM_COLOR (MAKE_RGB(255,255,51))

/* Font properties for select no.*/
#define INPUTCANDIDATE_DEFAULT_SELECTNO_COLOR (MAKE_RGB(240,135,32))    ///< default bg color for selected item
#define INPUTCANDIDATE_DEFAULT_SELECTNO_FONT_CATE FONT_CAT_SUPERSMALL       ///< default font size for selected item

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
/**
*  MTSelectionWidget_New
*  @brief   Create MT-Selection Widget.
*
*  @param  ppObj       	Pointer to the IWidget object.
*  @param  ClsID    	ClsID of MTSelectionWidget
*  @retval              MAE_RET_SUCCESS/MAE_RET_OUT_OF_MEMORY/MAE_RET_FAILED 	    Success/No More memory/Create Failed.
*/
__SLDPM_FREE__ MAE_Ret InputCandidateWidget_New(MAE_ClsId ClsID, void **ppObj);

/**
*  InputCandidateWidget_HandleEvent
*  @brief   the handle event function of ChineseSelectionWidget.
*
*  @param  pIWidget      Pointer to the ChineseSelection widget.
*  @param  evt           Event ID.
*  @param  P1            the first parameter for the inputted event. It's usually the event ID.
*  @param  P2            the second parameter for the inputted event. It might be a pointer address point to the inputted data.
*  @retval               TRUE/FALSE   the inputted event is handled/the event is not handled.
*/
__SLDPM_FREE__ boolean InputCandidateWidget_HandleEvent(IContainer *pIContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
/**
*  _WdgInputCandidateConstructor
*  @brief   Set initial data and default handler for ChineseSelectionWidget.
*
*  @param  pThis        Pointer to the ChineseSelection widget.
*  @retval              MAE_RET_BAD_PARAM/MAE_RET_SUCCESS/MAE_RET_FAILED      Wrong parameter/Success/Widget base Construct failed.
*/
__SLDPM_FREE__ MAE_Ret _WdgInputCandidateConstructor(InputCandidateWidget_t *pThis);

/**
*  _WdgInputCandidateDestructor
*  @brief   Release all resources which is created by ChineseSelection Widget.
*
*  @param  pThis       	Pointer to the ChineseSelection widget
*  @retval              void
*/
void _WdgInputCandidateDestructor(InputCandidateWidget_t *pThis);

//for IWidget interface
/**
*  InputCandidateWidget_Draw
*  @brief   the draw function of ChineseSelection widget.
*
*  @param  pIWidget      Pointer to the ChineseSelectionWidget.
*  @param  pIDispCanvas  Pointer to the DispCanvas object, it contains the valid client area to draw in.
*  @param  x             Draw position X.
*  @param  y             Draw position Y.
*  @retval               void
*/
void InputCandidateWidget_Draw(IContainer *pIPropContainer, IDispCanvas *pIDispCanvas, s32 x, s32 y);

MAE_Ret InputCandidateWidget_Move(IContainer *pIContainer, IWidget *WidgetPtr, IWidget *RefWidgetPtr, boolean isAbove);
__SLDPM_FREE__ MAE_Ret InputCandidateWidget_SetModel(IContainer *pIContainer, IModel *pIModel, IBase *pOwner);
void InputCandidateWidget_FreeModelData(void *pData, IBase *pOwner);
__SLDPM_FREE__ void InputCandidateWidget_GetFontInfo(InputCandidateWidget_t *pThis);
void InputCandidateWidget_ChangeDisplayStyle(InputCandidateWidget_t *pThis, CandidateDisplayMode_e eOldDisplayMode, CandidateDisplayMode_e eNewDisplayMode);
void InputCandidateWidget_ReloadCandidateImage(InputCandidateWidget_t *pThis);

//__IME_MMI_SG__
u32 InputCandidateWidget_GetCandidateItemWidth(void *pUsrData, s32 nIndex);
//__IME_MMI_SG__

#ifdef __TOUCH_SCREEN_MMI__
void InputCandidateWidget_SpellListWdgFocusChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusChangeData_t *data, IWidget *pListWidget);
void InputCandidateWidget_SpellListWdgFocusSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nFocusIdx, IWidget *pListWidget);
void InputCandidateWidget_CandidateListWdgFocusChangeCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, FocusChangeData_t *data,IWidget *pListWidget);
void InputCandidateWidget_CandidateListWdgFocusSelectCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, s32 nFocusIdx, IWidget *pListWidget);
#ifdef __IME_MMI_MY_STROKE_T__
void InputCandidateWidget_ComponentListWdgFocusChangeCb(void * pApplet, void * pUsrData, WidgetEvtCode_t nEvtCode, FocusChangeData_t * data, IWidget * pListWidget);
void InputCandidateWidget_ComponentListWdgFocusSelectCb(void * pApplet, void * pUsrData, WidgetEvtCode_t nEvtCode, s32 nFocusIdx, IWidget * pListWidget);
#endif
void InputCandidateWidget_ViewModel_EvtNotify(InputCandidateWidget_t *pThis, InputCandidateWidgetEvtType_e nEvtType, u32 nParam);
void InputCandidateWidget_FreeButtonModel(void *pData, IBase *pOwner);
MAE_Ret InputCandidateWidget_CreateButtonWidget(InputCandidateWidget_t *pThis, IWidget** ppIButtonWidget, u32 nImgIDUnpressed, u32 nImgIDPressed, ModelListener_t* pMdlListener, u8 nButtonId);
__SLDPM_FREE__ void InputCandidateWidget_ButtonClickCb(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pButtonWidget);
MAE_Ret _InputCandidateWidget_InitAllButtonWidget(InputCandidateWidget_t *pThis);
MAE_Ret _InputCandidateWidget_InitButtonWidget(InputCandidateWidget_t *pThis, IWidget* pIButtonWidget, u32 nImgIDUnpressed, u32 nImgIDPressed, u8 nButtonId);
MAE_Ret InputCandidateWidget_initCandidateImage(InputCandidateWidget_t *pThis);
#endif

#endif //__MMI_WDG_INPUTCANDIDATE_PRIV_H__
/*=============================================================*/
// end of file
