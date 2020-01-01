/**
* @file kmx_softkeyboardwidget.h
* @brief 
*
* @version 
*/
#ifndef __KMX_SOFTKEYBOARDWIDGET_H__
#define __KMX_SOFTKEYBOARDWIDGET_H__

#ifdef __IME_MMI_CSTAR__

/*=============================================================*/
// include
/*=============================================================*/
#include "mae_widgetbase.h"
#include "mae_inputcontroller_priv.h"

/*=============================================================*/
// type and define
/*=============================================================*/
typedef struct 
{
    WidgetBaseEx_t WdgBase;
    
    InputController_t   * piController;

	IBitmap* piBitmap; /* Last keyboard bitmap */
	int is_last_mode_landscape;

#ifdef __TOUCH_SCREEN_MMI__
    u8 bTouched;
    ITouchSrv *pITouchSrv;  //< Touch service
#endif //__TOUCH_SCREEN_MMI__
#ifdef __MMI_IME_CSTAR_FORMAT__
	boolean kmx_ime_formatinput_flag;
#endif
} Kmx_SoftkeyboardWidget_t;


/*=============================================================*/
// functions
/*=============================================================*/
MAE_Ret Kmx_SoftkeyboardWidget_New(MAE_ClsId ClsID, void **ppObj);

#endif //__MMI_CSTAR__

#endif //__KMX_SOFTKEYBOARDWIDGET_H__
/*=============================================================*/
// end of file
