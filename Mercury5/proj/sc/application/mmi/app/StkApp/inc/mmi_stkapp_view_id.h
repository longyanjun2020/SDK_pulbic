
/**
* @file    mmi_atkapp_view_id.h
* 
* @version $Id $
*/

#ifndef __MMI_STKAPPVIEW_ID_H__     
#define __MMI_STKAPPVIEW_ID_H__     

#include "mmi_view_id_range.h"

/* View ID */
enum
{                           
    VID_STK_INVALID_VIEW                = MMI_VIEW_ID_AP_BEGIN,

    VID_STK_SHOW_MAIN_MENU_VIEW,

    VID_STK_DISPLAY_TEXT_VIEW,

    VID_STK_INPUT_VIEW
};

typedef s32 MMI_STK_APP_VID_E;


/* Widget ID */
enum
{
    WID_STK_TITLEWIDGET         = 1, 
    WID_STK_MENUWIDGET,
    WID_STK_SCROLLBARWDG,
    WID_STK_INPUTWIDGET,
    MID_STK_INPUT_OPTION_MODEL
};

typedef s32 MMI_STK_AP_WID_E;

/* Constant */
#define VIEW_STK_DISPLAY_WIDTH    MAIN_LCD_WIDTH
#define VIEW_STK_DISPLAY_HEIGHT   (MAIN_DEFVIEW_HEIGHT-MAIN_TITLE_HEIGHT)


#endif /* __MMI_STKAPPVIEW_ID_H__ */
