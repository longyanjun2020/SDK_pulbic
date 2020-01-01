/**
 * @file    mmi_wdg_softkeyboard.h
 * @author  christoph.kuo@mstarsemi.com
 *
 * @version $Id: mmi_wdg_softkeyboard.h 34540 2009-06-26 11:47:20Z william.lien $
 *
 *
 */
#ifndef __MAE_SOFTKEYBOARDWIDGET_H__
#define __MAE_SOFTKEYBOARDWIDGET_H__


#ifdef __TOUCH_SCREEN_MMI__
#ifdef __IME_MMI_SOFTKEYBOARD__
#include "mmi_wdg_common_interface.h"

#ifdef __IME_MMI_MY__
	#define	__STROKE_WITHOUT_WILDCHAR__
#endif

#ifdef __IME_MMI_SOFTKEYBOARD_7COL_UI__
#define GRID_IDX_NOT_FOUND 				(0xff)
#endif //__IME_MMI_SOFTKEYBOARD_7COL_UI__

#ifdef __IME_MMI_SOFTKEYBOARD_7COL_UI__
#ifdef __IME_MMI_MY__
	#define IMG_SOFTKEYBOARD_STROKE_BG_ID INPUT_IMG_SOFTKEYBOARD_STROKE_WITHOUT_WILDCHAR_BG
#elif defined __IME_MMI_SG__
	#define IMG_SOFTKEYBOARD_STROKE_BG_ID	INPUT_IMG_SOFTKEYBOARD_STROKE_SG_BG
#else
	#define IMG_SOFTKEYBOARD_STROKE_BG_ID	INPUT_IMG_SOFTKEYBOARD_STROKE_BG
#endif //__IME_MMI_MY__

#else //no__IME_MMI_SOFTKEYBOARD_7COL_UI__
#ifdef __IME_MMI_MY__
	#define IMG_SOFTKEYBOARD_STROKE_BG_ID INPUT_IMG_SOFTKEYBOARD_STROKE_WITHOUT_WILDCHAR_BG
#elif defined __IME_MMI_SG__
	#define IMG_SOFTKEYBOARD_STROKE_BG_ID	INPUT_IMG_SOFTKEYBOARD_STROKE_SG_BG
#else
	#define IMG_SOFTKEYBOARD_STROKE_BG_ID	INPUT_IMG_SOFTKEYBOARD_STROKE_BG
#endif //__IME_MMI_MY__
#endif //__IME_MMI_SOFTKEYBOARD_7COL_UI__

typedef struct {
    MAE_WChar nChar;
    u8 SKBCodeType_e; //MAE_SKB_CODE_TYPE_e
#ifdef __IME_MMI_SOFTKEYBOARD_7COL_UI__
	u32 xPosition;
	u32 yPosition;
	u8 nIndex;
	u8 nColumn;
#endif //__IME_MMI_SOFTKEYBOARD_7COL_UI__
} SoftKeyBoardWidget_NotifyData_t;

//input mode for soft-keyboard widget only
#define MAE_INPUTMODE_SKB_DATETIME	0x00000100
#define MAE_INPUTMODE_SKB_PIN		0x00000200


typedef struct
{
	u32 nSKBID;
	u32 nSKBFileterMask;

} InputRestriction_t;

/*Using input mode to get default SKB widget height*/
u16 WdgSoftkeyboardGetDefaultHeight(u32 nInputMode,void* pThis/*HWIN hWin*/);

/** PfnWdgButtonWidgetButtonClick
* @brief      CB register by "PfnWdgButtonWidgetButtonClick"
*             and will be trigger when the button is clicked by user.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data  developer setting when register CB.
* @param[in]  nEvtCode         Widget Event Code, only useful for softkey event
* @param[in]  dwParam       The data word param (NOT use now)
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgSoftkeyBoardWidgetButtonClick) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, SoftKeyBoardWidget_NotifyData_t *SoftKeyboardData, IWidget *pWDGSoftkeyBoard);

/*=============================================================*/
// functions
/*=============================================================*/
/** WdgSoftKeyBoardSetInputRestriction
* @brief        Set input restriction
*
* @param[in]    pWDGSoftkeyBoard          The Time widget which want to be set
* @param[in]    pRestriction				restriction value. (A pointer of InputRestriction_t structure.)
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgSoftkeyBoardSetInputRestriction
(
    IWidget                 *pWDGSoftkeyBoard,
    InputRestriction_t          *pRestriction
)
{
    return WdgCommonSetProperty(pWDGSoftkeyBoard, PROP_SKB_WDG_INPUT_RESTRICTION, (u32)pRestriction);
}

/** WdgSoftkeyBoardRegisterButtonClickCb
* @brief        Register button click callback; CB will be triggered while SoftkeyBoard button be clicked.
*
* @param[in]    pWDGSoftkeyBoard        The SoftkeyBoard widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgSoftkeyBoardRegisterButtonClickCb
(
    IWidget                 *pWDGSoftkeyBoard,
    PfnWdgSoftkeyBoardWidgetButtonClick   pfn,
    void                    *pUserData
);

/** WdgSoftkeyBoardDeregisterButtonClickCb
* @brief        Deregister button click callback
*
* @param[in]    pWDGSoftkeyBoard        The SoftkeyBoard widget which want to Deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgSoftkeyBoardDeregisterButtonClickCb
(
    IWidget                 *pWDGSoftkeyBoard,
    PfnWdgSoftkeyBoardWidgetButtonClick   pfn,
    void                    *pUserData
);

#endif //__IME_MMI_SOFTKEYBOARD__
#endif //__TOUCH_SCREEN_MMI__
#endif /*__MAE_SOFTKEYBOARDWIDGET_H__ */
