/**
 * @file    mmi_wdg_caret.h
 * @brief   Implementation of caret widget. 
 *          The caret widget is held by input widget. 
 *          And it is used to indicate user the position where the next inputted character will be inserted.
 *          If the holder widget starts the blinking timer of caret widget, please cancel the timer when the holder loses focus.
 * @version $Id: mmi_wdg_caret.h 8917 2008-04-11 03:24:13Z steve.lee $ Author: Alison Chen
 */
#ifndef __MMI_WDG_CARET_H__
#define __MMI_WDG_CARET_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_widget.h"
#include "mmi_wdg_common_interface.h"
/*=============================================================*/
// type and define
/*=============================================================*/
/** PfnWdgCaretWidgetBlink
* @brief      CB register by "PfnWdgCaretWidgetBlink"
*             and will be trigger when the caret is blink.
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode         Widget Event Code, only useful for softkey event
* @param[in]  dwParam       The data word param (NOT use now)
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgCaretWidgetBlink) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam,IWidget *pCaretWidget);

/*=============================================================*/
// interface function
/*=============================================================*/
/** WdgCaretCreate
* @brief        Create Caret widget
*
* @retval       The pointer of Caret   Success.
* @retval       NULL                    Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgCaretCreate
(
    void
);
/** 
 *  WdgCaretSetColor
 *  @brief   Set caret color.
 *   
 *  @param  pIWidget      			Pointer to the IWidget object.
 *  @param  nColor     				rgbColor value.  ex. 0xFFFFFF --> white
  */
void WdgCaretSetColor(IWidget *pIWidget, RGBColor_t nColor);

/** 
 *  WdgCaretSetBlink
 *  @brief  Set blinking status of the caret.
 *   
 *  @param  pIWidget       			Pointer to the IWidget object.
 *  @param  bBlink     				if bBlink == TRUE, the caret will blink. Otherwise, the caret will stop blinking.
 *  @retval TRUE 	SUCCESS.
 */
void WdgCaretSetBlink(IWidget *pIWidget, boolean bBlink);

/** 
 *  WdgCaretIsShow
 *  @brief  check if cursor is shown.
 *   
 *  @param  pIWidget       			Pointer to the IWidget object.
  *  @retval TRUE / false .
 */
boolean WdgCaretIsShow(IWidget *pIWidget);

/** 
 *  WdgCaretSetHide
 *  @brief  set hide cursor or not
 *   
 *  @param  pIWidget       			Pointer to the IWidget object.
 *  @param  bHide     				TRUE/FALSE
 */
__INLINE void WdgCaretSetHide(IWidget *pIWidget, boolean bHide)
{
	WdgCommonSetProperty(pIWidget, PROP_CARET_WDG_HIDE, bHide);
}

/** WdgCaretRegisterBlinkCb
* @brief        Register caret blink callback; CB will be triggered while caret blink
*
* @param[in]    pWDGCaret        The Caret widget which want to set callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgCaretRegisterBlinkCb
(
    IWidget                 *pWDGCaret,
    PfnWdgCaretWidgetBlink   pfn,
    void                    *pUserData
);

/** WdgCaretDeregisterBlinkCb
* @brief        Deregister Caret blink callback
*
* @param[in]    pWDGCaret        The Caret widget which want to Deregister callback
* @param[in]    pfn               callback function
* @param[in]    pUserData          User Data can be got when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgCaretDeregisterBlinkCb
(
    IWidget                 *pWDGCaret,
    PfnWdgCaretWidgetBlink   pfn,
    void                    *pUserData
);
/*=============================================================*/
// functions
/*=============================================================*/

#endif //__MMI_WDG_CARET_H__
/*=============================================================*/
// end of file
