/**
 * @file    mmi_wdg_caret_priv.h
 * @brief   Private structure and definitions of caretwidget
 * @version $Id: mmi_wdg_caret_priv.h 34664 2009-06-29 14:37:52Z bill.pan $ Author: Alison Chen
 */
#ifndef __MMI_WDG_CARET_PRIV_H__
#define __MMI_WDG_CARET_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mae_widgetbase.h"
#include "mmi_mae_widget_custom.h"
/*=============================================================*/
// type and define
/*=============================================================*/

typedef struct {
    WidgetBaseEx_t WdgBase;
    RGBColor_t color;                     ///<  the caret's color
    u8 displayStatus;                   ///<  display the caret or not, if displayStatus == CAERT_DISPLAY_STATUS_HIDE, the caret will not be drawn.
    u8 blinkStatus;                     ///<  current blink status
    u32 blinkOnInterval;			    ///<  in msec, the interval to show the caret. 
    u32 blinkOffInterval;			    ///<  in msec, the interval to hide the caret. 
    WidgetSize_t PreffredSize;	
} CaretWidget_t;


enum Caret_Blink_Status_e
{
  CAERT_BLINK_STATUS_NOBLINK = 0x00,	 ///<  the caret will not blink
  CAERT_BLINK_STATUS_ON = 0x01,	         ///<  the caret is shown
  CAERT_BLINK_STATUS_OFF = 0x02          ///<  the caret is paused  
};


enum Caret_Display_Status_e
{
  CAERT_DISPLAY_STATUS_DISPLAY = 0x00,	  ///<  Display the caret
  CAERT_DISPLAY_STATUS_HIDE	= 0x01		  ///<  Hide the caret
};



#define	DEFAULT_COLOR			    (MAKE_RGB(96,96,96)) ///< Default cursor color

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
/** 
*  CaretWidget_New
*  @brief   Create Caret Widget.
*   
*  @param  ppObj       	Pointer to the IWidget object.
*  @param  ClsID    	ClsID of CaretWidget
*  @retval              MAE_RET_SUCCESS/MAE_RET_OUT_OF_MEMORY/MAE_RET_FAILED 	    Success/No More memory/Create Failed.
*/
__SLDPM_FREE__ MAE_Ret CaretWidget_New(MAE_ClsId ClsID, void **ppObj);

/** 
*  CaretWidget_HandleEvent
*  @brief   the handle event function of CaretWidget.
*   
*  @param  pIWidget      Pointer to the CaretWidget object.
*  @param  evt           Event ID.
*  @param  param1        the first parameter for the inputted event.
*  @param  param2        the second parameter for the inputted event.
*  @retval               TRUE/FALSE   the inputted event is handled/the event is not handled.
*/
__SLDPM_FREE__ boolean CaretWidget_HandleEvent(IWidget *pIWidget, MAE_EventId evt, u32 Param1, u32 Param2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
/** 
*  _WdgCaretConstructor
*  @brief   Set initial data and default handler for CaretWidget.
*   
*  @param  pThis        Pointer to the CaretWidget object.
*  @retval              MAE_RET_BAD_PARAM/MAE_RET_SUCCESS/MAE_RET_FAILED      Wrong parameter/Success/Widgtbase Construct failed.
*/
MAE_Ret _WdgCaretConstructor(CaretWidget_t *pThis);
void _WdgCaretDestructor(CaretWidget_t *pThis);

//for IWidget interface
/** 
*  CaretWidget_GetPreferredSize
*  @brief   To get the preferred size of caret widget.
*   
*  @param  pIWidget      Pointer to the CaretWidget object.
*  @param  pSize         Preferred widget size.
*  @retval               void
*/
void CaretWidget_GetPreferredSize(IWidget *pIWidget, WidgetSize_t *pSize);

/** 
*  CaretWidget_Draw
*  @brief   the draw function of caret widget.
*   
*  @param  pIWidget      Pointer to the CaretWidget object.
*  @param  pIDispCanvas  Pointer to the DispCanvas object, it contains the valid client area to draw in.
*  @param  x             Draw position X.
*  @param  y             Draw position Y.
*  @retval               void
*/
void CaretWidget_Draw(IWidget *pIWidget, IDispCanvas *pIDispCanvas, s32 x, s32 y);

//not interface function
/** 
*  CaretWidget_BlinkTimerCallBack
*  @brief   The callback function when Blink timer timeout. 
*           This function will switch the display-status of caret widget, start blink timer and ask to redraw the caret widget.
*  @param  pData         Pointer to the CaretWidget object.
*  @retval               void
*/
void CaretWidget_BlinkTimerCallBack(CaretWidget_t *pThis, void * pData);

/** 
*  CaretWidget_Invalidate
*  @brief   For caret widget to redraw itself.
*           Because input widget which is the holder of caret widget is not a container, caret widget has to 
*           notify the input widget to redraw the caret widget by sending notice.
*  @param  pData         Pointer to the CaretWidget object.
*  @retval               void
*/
void CaretWidget_Invalidate(CaretWidget_t *pThis);

#endif //__MMI_WDG_CARET_PRIV_H__
/*=============================================================*/
// end of file
