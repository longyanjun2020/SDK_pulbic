/**
* @file    mmi_mmi_mae_widget_properties.h
* @brief   This file is the collection of widget property definitions.
*
* @version $Id: mmi_mmi_mae_widget_properties.h 39819 2009-09-09 13:16:22Z ryan.chou $
*/
#ifndef __MMI_MAE_WIDGET_PROPERTIES_H__
#define __MMI_MAE_WIDGET_PROPERTIES_H__

/*=============================================================*/
// include
/*=============================================================*/

/*=============================================================*/
// type and define
/*=============================================================*/

//reserved, range: 0x00000000(0)~0x00000FFF(4095)
#define WDG_PROP_RESERVED_START   0x00000000
#define WDG_PROP_RESERVED_END     0x00000FFF


/*=============================*/
// For all widgets
/*=============================*/
// common widget properties, range: 0x00001000(4096)~0x00001FFF(8191)
#define WDG_COMMON_PROP_START   0x00001000
#define WDG_COMMON_PROP_END     0x00001FFF

/*=============================*/
// For all containers
/*=============================*/
// common container properties, range: 0x00002000(8192)~0x00002FFF(12287)
#define CNTNR_COMMON_PROP_START  0x00002000
#define CNTNR_COMMON_PROP_END    0x00002FFF

/*=============================*/
// Individual widget porperties
/*=============================*/
// range: 0x00010000(65536)~0x0001FFFF(131071)
#define WDG_PROP_START  0x00010000
#define WDG_PROP_END    0x0001FFFF

/*=============================*/
// Individual container porperties
/*=============================*/
// range: 0x00020000(131072)~0x0002FFFF(196607)
#define CNTNR_PROP_START  0x00020000
#define CNTNR_PROP_END    0x0002FFFF


/*******************************************************
* Widget Properties Id :
*******************************************************/
// common widget properties
enum
{
    PROP_WIDGET_CMN_BEGIN = WDG_COMMON_PROP_START,
    PROP_WDG_VISIBLE = PROP_WIDGET_CMN_BEGIN,
    PROP_WDG_ALIGNMENT,         /*!< P2 => Set:(u8), Get:(u8 *), please refer to enum
                                HorizontalAlignment_tag & VerticalAlignment_tag */
    PROP_FLAG,                  ///< Set/get widget flag (an u32 variable)
    PROP_CLSID,                 ///< Widget Class ID
    PROP_LAYOUT_STYLE,          ///< widget's layout style

    PROP_PADDING_SIZE,          /*!< For set property only. P2 is padding size. Use MAKE_PADDING_SIZE to
                                compose an u32 as this parameter */
    PROP_PADDING_LEFT,          ///< Left padding, u8
    PROP_PADDING_RIGHT,         ///< Right padding, u8
    PROP_PADDING_TOP,           ///< Top padding, u8
    PROP_PADDING_BOTTOM,        ///< Bottom padding, u8
    PROP_BORDER_SIZE,           /*!< For set property only, P2 => border size, use MAKE_BORDER_SIZE to
                                compose an u32 as this parameter */
    PROP_BORDER_LEFT,           ///< Left border, P2 => Set:(u8), Get:(u8*)
    PROP_BORDER_RIGHT,          ///< Right border, P2 => Set:(u8), Get:(u8*)
    PROP_BORDER_TOP,            ///< Top border, P2 => Set:(u8), Get:(u8*)
    PROP_BORDER_BOTTOM,         ///< Bottom border P2 => Set:(u8), Get:(u8*)
    PROP_BORDER_COLOR,          ///< Border color, P2 => Set:(RGBColor_t), Get:(RGBColor_t*)

    PROP_WDG_CAN_BE_SELECTED,
    PROP_WDG_SELECTED_COLOR,

    PROP_WDG_FG_COLOR,          ///< Foreground color of widget, P2 => Set:(RGBColor_t), Get:(RGBColor_t*)
    PROP_WDG_BG_COLOR,          ///< Background color to widget, P2 => Set:(RGBColor_t), Get:(RGBColor_t*)
    PROP_WDG_BG_IMAGE,          ///< Background image to widget, set property only, P2=> Set:(IImage*)or(IBitmap*)
    //PROP_WDG_BG_TYPE,           ///< p2 => Set:(u32), Get:(u32*). WDG_BG_TYPE_COLOR/WDG_BG_TYPE_IMAGE
    PROP_WDG_BG_POSITION,       ///< Background position, P2 => Set:(u32), Get:(u32*). WDG_BG_POS_INNER/WDG_BG_POS_WHOLE
    PROP_WDG_BG_ENABLE,         ///< Enable or Disable background. P2 => Set:(boolean)
    PROP_WDG_BG_ALIGN,          /*!< Background image alignment. P2 => Set:(u8), please refer to enum
                                HorizontalAlignment_tag & VerticalAlignment_tag */
#ifdef __AP_USE_ML__
    PROP_WDG_TRANSP_BG_ENABLE,
#endif
    PROP_WDG_LANG_DIRECTION,    /*!< For widget which support language direction changed, please refer to
                                the enum e_Lang_Dir in mmi_mmi_mae_widget_properties.h, P2 => Set:(u8), Get:(u8 *) */
    PROP_WDG_FONT_CATE,         ///< Font category, refer to mae_font.h
    PROP_WDG_FONT_SIZE,         ///< Font size
    PROP_WDG_FONT_TYPE,         ///< Font type, normal, outline, underline, expand... refer to mae_font.h
    PROP_WDG_TEXT_COLOR,        ///< RGB color for text
    PROP_WDG_TEXT_OUTLINE_COLOR,///< RGB color for text outline
    PROP_WDG_TEXT_TOTAL_LINE,   ///Get the total line number by mae_text measure.

    PROP_DISABLE_HANDLE_KEY_EVT,///< P2 => Set:(boolean), Get:(*boolean), P2=TRUE to disable handle key event.
#ifdef __TOUCH_SCREEN_MMI__
    PROP_DISABLE_HANDLE_TOUCH_EVT,///< P2 => Set:(boolean), P2=TRUE to disable handle touch event.
#endif //__TOUCH_SCREEN_MMI__

    PROP_WDG_ROW_GAP,           ///< Row gap in pixel between every item.
    PROP_WDG_COL_GAP,           ///< Column gap in pixel between every item.
    PROP_WDG_ENABLE_ANIMATE,           ///< Turn on/off animation to widget, P2:TRUE, turn on, P2:FALSE, turn off.
    PROP_WDG_RESET_ANIMATE,        ///< To reset the status of animation

    PROP_WDG_BE_ITEM_WDG,       ///< P2:TRUE, set widget to be an item widget in list, P2:FALSE, not an item widget.
    PROP_WDG_HIGHLIGHTED,       ///< Set the item widget highlighted or not, P2:TRUE, highlighted, P2:FALSE, not highlighted.
    PROP_WDG_HIGHLIGHT_TEXT_COLOR,        ///< RGB color for text color while widget highlighted
    PROP_WDG_HIGHLIGHT_TEXT_OUTLINE_COLOR,///< RGB color for text outline color while widget highlighted.
    PROP_WDG_HIGHLIGHT_BG_COLOR,///< RGB color for background color while widget highlighted.
    PROP_WDG_ITEM_PRESSED,       ///< P2:TRUE OR FALSE

    PROP_WDG_SCROLL_DATA,                  //for widgets which support scrollwidget, Set/Get Property, P2 => (ScrollData_t *)
    PROP_WDG_SCROLL_STEP,                  //for widgets which support scrollwidget, only for Get Property, P2 => (ScrollStep_t *)
    PROP_WDG_H_SCROLL_NOTICE_MODE,/*!< for widgets which support scrollwidget for horizontal scroller, only for Get Property,
                                  P2 =>(boolean *) => TRUE: the scroll widget will listen Focus Change,
                                  FALSE: the scroll widget will listen Scroll Change */
    PROP_WDG_V_SCROLL_NOTICE_MODE,/*!< for widgets which support scrollwidget for vertical scroller, only for Get Property,
                                    P2 =>(boolean *) => TRUE: the scroll widget will listen Focus Change,
                                    FALSE: the scroll widget will listen Scroll Change */

    PROP_WDG_SK_DATA,            //set softkey data to widget, P2 => (ISoftkeyModel*)
    PROP_WDG_LOOKCTRL_TYPE,     //Set/Get the look control type. P2 => Set:(WdgLookCtrlType_t), Get(WdgLookCtrlType_t*)

    PROP_WDG_FOCUSABILITY,         ///to set/get the focusability from a widget. set, P2 is a boolean value. get, P2 is a pointer of boolean value.
    PROP_WDG_ENABLE_FOCUS_EFFECT,  ///to set/get the enability of focus effect from a widget. To set, P2 is a boolean value. To get, P2 is a pointer of boolean value.

    PROP_WDG_BE_ITEM_IN_GRID,   ///< P2:TRUE, set widget to be an item widget in grid widget, P2:FALSE, not an item widget in grid widget.
    PROP_WDG_BE_AUTO_ANIMATE,   ///< P2:TRUE, FALSE

#ifdef __TOUCH_SCREEN_MMI__
    PROP_WDG_CHANGEFOCUS_ON_TOUCH,///to determine if a widget need to set focus automatically while touch press. Set, P2 is a boolean value. Get, P2 is a pointer of boolean value.
#endif //__TOUCH_SCREEN_MMI__

    PROP_WDG_3D_ENABLE,         ///< Enable or Disable 3D. P2 => Set:(boolean), Get:(*boolean)
    PROP_WDG_MULTI_TOUCH,

    PROP_WIDGET_CMN_END
};

// common container properties
enum
{
    PROP_CONTAINER_CMN_BEGIN = CNTNR_COMMON_PROP_START,

    PROP_CHILD_WDG_VISIBLE = PROP_CONTAINER_CMN_BEGIN,
    PROP_CHILD_WDG_ACTION_ON_FOCUS,
    PROP_CHILD_WDG_SEND_TOUCH_FOCUS_EVENT,   ///to determine if send selected event while touch on a focus widget in container.
    PROP_LAYOUT_INVERSE_BY_LANGUAGE,
    PROP_CONTAINER_CMN_END
};


// individual widget properties
enum
{
    PROP_WIDGET_IDV_BEGIN = WDG_PROP_START,
    // For text widget
    PROP_TEXT_WDG_MIN_LINE_HEIGHT = PROP_WIDGET_IDV_BEGIN,  //P2 => Set:(u32) , Get:(u32 *) =>pixcel, The line height of the text widget will be MAX(min line height, font height)
    //PROP_TEXT_WDG_FONT_SIZE, //deprecated, use PROP_WDG_FONT_CATE instead.
    //PROP_TEXT_WDG_FONT_TYPE, //deprecated , use PROP_WDG_FONT_TYPE instead.
    //PROP_TEXT_WDG_FG_COLOR, //deprecated, use PROP_TEXT_WDG_TEXT_COLOR instead.
    //PROP_TEXT_WDG_TEXT_COLOR = PROP_TEXT_WDG_FG_COLOR, //deprecated, use PROP_WDG_TEXT_COLOR instead.
    //PROP_TEXT_WDG_OUTLINE_COLOR, // deprecated, use PROP_WDG_TEXT_OUTLINE_COLOR instead.
    PROP_TEXT_WDG_SLIDE_DIRECTION,
    PROP_TEXT_WDG_SLIDE_STEP_OFFSET,
    PROP_TEXT_WDG_SLIDE_STEP_TIME,
    PROP_TEXT_WDG_SLIDE_ON_OFF,         //Turn On/Off The Text sliding animation, P2 => Set:(boolean), Get:(boolean *), TRUE=>ON, FALSE=>OFF
    PROP_TEXT_WDG_SLIDE_AUTO_REPEAT,    //P2  => Set:(boolean), Get:(boolean *), TRUE=>The Text will auto repeat sliding, FALSE=>After the text slide to the end, the sliding will stop. And the text wdg view model listener will get a EVT_VIEWMDL_SLIDE_FINAL
    PROP_TEXT_WDG_SLIDE_STYLE,          //P2  => Set:(u8), Get:(u8 *), Ex:SLIDE_STYLE_NO_SLIDE_IN|SLIDE_STYLE_NO_SLIDE_OUT, please refer to enum e_Slide_Style in mae_textwidget.h
                                        //Slide In: set the text non-slide position, if SLIDE_STYLE_SLIDE_IN , and PROP_TEXT_WDG_SLIDE_ON_OFF is Off, then the string won't be show. after user set the PROP_TEXT_WDG_SLIDE_ON_OFF as TRUE, the string will slide into the visible area
                                        //Slide Out: set the text slide end condition, if SLIDE_STYLE_SLIDE_OUT, the slide end condition is slide all the text out of the widget
    PROP_TEXT_WDG_LAYOUT_FLAG,          //The Layout Flag, P2 => Set:(u8), Get:(u8 *), Ex:LAYOUT_ELLIPSIS, please refer to enum e_Text_Layout in mae_textwidget.h
    PROP_TEXT_WDG_ALIGN_PRIORITY,       //The Align priority, P2 => Set:(u8), Get:(u8 *), Ex:TEXTWDG_ALIGN_FIRST, please refer to enum e_Text_AlignAndBreak in mae_textwidget.h
                                            /*The TEXTWDG_ALIGN_FIRST only work if the text layout is single line. If the layout is multi-line, the priority will always be TEXTWDG_BREAK_THEN_ALIGN*/
    PROP_TEXT_WDG_PREFERRED_HEIGHT,     //Only for Get Property, P2=>(WidgetSize_t *), and the preferred width should be identified in the ((WidgetSize_t *)P2)->width, if the preferred width < TEXTWDG_MIN_PREFERRED_WIDTH (defined in mae_textwidget.h) => return FALSE
    PROP_TEXT_WDG_HIGHLIGHT_WIDTH,      //Text highlight widget highlight width
    PROP_TEXT_WDG_HIGHLIGHT_POS,        //Text highlight widget start position
    PROP_TEXT_WDG_TEXT_OFFSET,          //Draw the text string from offset value in the case of string length is larger than widget width
    PROP_TEXT_WDG_BIDI,                  ///<Enable/Disable bidi function, default is TRUE

    // For Text Label widget
    PROP_TEXT_WDG_TEXTCOLOR_THM_ID,     ///< Theme id for text color
    PROP_TEXT_WDG_OUTLINECOLOR_THM_ID,  ///< Theme id for text outline color
    PROP_TEXT_WDG_HIGHLIGHT_TEXTCOLOR_THM_ID,///< Theme id for highlight text color
    PROP_TEXT_WDG_HIGHLIGHT_OUTLINECOLOR_THM_ID,///< Theme id for highlight text outline color
    PROP_TEXT_WDG_LINK_ADDR,             //link text to object
    PROP_TEXT_WDG_LINKED_STATE,          //record the linked state
    PROP_TEXT_WDG_LINK_AUTO_UNDERLINE,   //P2  => Set:(boolean), Get:(boolean *), enable/disable auto use underline text when link addr set. Default is TRUE

    // For Image Widget
    ////// deprecated /////
    //PROP_IMG_WDG_IMAGE_AREA,            //P2 => (Rect *) for image draw area
    ////// deprecated /////
    //PROP_IMG_WDG_NEWIMG_FROM_FILE,      //Only for Set Property, P2 => (u8 *) file name
    ////// deprecated /////
    //PROP_IMG_WDG_NEWIMG_FROM_STREAM,    //Only for Set Property, P2 => (IAStream *)
    PROP_IMG_WDG_IMGINFO,               //Only for Get Property, P2 => (ImgWdg_ImgInfo_t *)
    PROP_IMG_WDG_IMAGE_SCALE_ROTATE,    //P2 => (ImgScaleRotate_t *) Scale Size

    /* for animation image */
    ////// deprecated use PROP_WDG_ENABLE_ANIMATE instead/////
    //PROP_IMG_WDG_IMAGE_ANIMATE,       //Only for Set Property, P2 => boolean (TRUE:ON/ FALSE:OFF)
    PROP_IMG_WDG_FRAME_WIDTH,           //Only for Set Property, P2 => (u32) the width of each frame
    PROP_IMG_WDG_FRAME_INTERVAL,        //Only for Set Property, P2 => (u16) Interval of frames in milliseconds

    PROP_IMG_WDG_AUTO_FIT,              //P2 => Set:(ImgWdgAutoFit_t), Get:(ImgWdgAutoFit_t*). ImgWdgAutoFit_t is defined in mae_imagewidget.h
    PROP_IMG_WDG_ENABLE_UPSCALE,        //P2 => Set:(boolean), Get:(boolean*)
    //not support yet
    //PROP_IMG_WDG_IMAGE_FRAME_NUM,     //P2 the number of frames (PROP_IMG_WDG_IMAGE_FRAME_WIDTH will be calculated)
    //PROP_IMG_WDG_DRAW_CALLBACK,       //P2 = PfnMAE_Notify, pUserData
    PROP_IMG_WDG_ENABLE_PARTIAL_DEC,    //P2 => Set:(boolean), Get:(boolean*), default is off
    PROP_IMG_WDG_ENABLE_DEF_IMAGE,      //P2 => Set:(boolean), Get:(boolean*), default is off
    PROP_IMG_WDG_DEF_IMAGE_ID,           //P2 => Set:(u32), Get:(u32*)
    PROP_IMG_WDG_LINK_ADDR,
    PROP_IMG_WDG_LINKED_STATE,
    PROP_IMG_WDG_ANIMATE_ONCE,
    PROP_IMG_WDG_KEEP_BUFFER,
    PROP_IMG_WDG_CAN_USE_PALETTE_DATA,

    // For Thm Image widget
    PROP_THM_IMG_WDG_THM_IMG_ID,        ///< theme image id

    // For Bitmap Widget
    PROP_BMP_WDG_BITMAP,                //P2 : pointer to IBitmap
    PROP_BMP_WDG_LINK_ADDR,
    PROP_BMP_WDG_LINKED_STATE,
    PROP_BMP_WDG_CONTENT_DIRTY,         //P2 : pointer to Rect_t

    // For Viewport Widget
    PROP_VIEWPORT_WDG_PANSTEP,          //P2 : pixels per moving
    PROP_VIEWPORT_WDG_XOFFSET,          //P2 : Current x offset
    PROP_VIEWPORT_WDG_YOFFSET,          //P2 : Current y offset
    PROP_VIEWPORT_WDG_KEEP_CENTER,      //P2 : boolean
    // the following 2 properties are deprecated, keep it for the purpose of compatibility
    // use  PROP_VIEWPORT_WDG_LOCK_HORZ_MOVE_EX, PROP_VIEWPORT_WDG_LOCK_VERT_MOVE_EX
    PROP_VIEWPORT_WDG_LOCK_HORZ_MOVE,   //deprecated //P2 : boolean
    PROP_VIEWPORT_WDG_LOCK_VERT_MOVE,   //deprecated //P2 : boolean
    PROP_VIEWPORT_ENABLE_H_SCROLL_ANIM,    //P2 : boolean
    PROP_VIEWPORT_ENABLE_V_SCROLL_ANIM,    //P2 : boolean
    PROP_VIEWPORT_WDG_RESET,
    PROP_VIEWPORT_WDG_ANIMATION_STOP,
    PROP_VIEWPORT_WDG_ANIMATION_PARAM,
    PROP_VIEWPORT_WDG_VERT_OVER_BOUNDARY,    //P2 : boolean
    PROP_VIEWPORT_WDG_HORZ_OVER_BOUNDARY,    //P2 : boolean
#ifdef __UI_STYLE_MMI_ANDROID_MAIN_MENU__
    PROP_VIEWPORT_ABLE_CHILD_HANDLE_TOUCH_EVT,///< P2 => Set: (boolean), P2 = FALSE to disable passing touch event to child widget  lin.wang modify in 2010-11-19
    // the following 3 properties are deprecated, keep it for the purpose of compatibility
    // use MMI_Common_SetViewportAnim to call View port Android animation
    PROP_VIEWPORT_CELL_MAINMENU_ANIMATE,
    PROP_VIEWPORT_TOUCH_SNAP_TO_GRID,
    PROP_VIEWPORT_TOUCH_GRID_Y_SIZE,
#endif
#ifdef __TOUCH_SCREEN_MMI__
    PROP_VIEWPORT_WDG_ENABLE_TOUCH_CHILD,    //P2 : boolean
    PROP_VIEWPORT_WDG_ENABLE_HOOK_POINT,
#endif //__TOUCH_SCREEN_MMI__
    // For Scrollbar Widget

    /*wait for theme -- start*/
    PROP_SCROLLBAR_WDG_H_BAR_IMGS,      //Only for Set Property, horizontal bar bmps, P2 =>(ScrollBarInd_Bmps_t *)
    PROP_SCROLLBAR_WDG_H_IND_IMGS,      //Only for Set Property, horizontal indicator bmps, P2 =>(ScrollBarInd_Bmps_t *)

    PROP_SCROLLBAR_WDG_V_BAR_IMGS,      //Only for Set Property, bar bar bmps, P2 =>(ScrollBarInd_Bmps_t *)
    PROP_SCROLLBAR_WDG_V_IND_IMGS,      //Only for Set Property, bar indicator bmps, P2 =>(ScrollBarInd_Bmps_t *)

    PROP_SCROLLBAR_WDG_H_ARROW_IMGS,    //Only for Set Property, horizontal arrow bmps, P2 =>(ScrollArrow_Bmps_t *)
    PROP_SCROLLBAR_WDG_V_ARROW_IMGS,    //Only for Set Property, vertical arrow bmps, P2 =>(ScrollArrow_Bmps_t *)
    /*wait for theme -- end*/
    PROP_SCROLLBAR_WDG_H_TS_SCROLL_ABILITY, //P2=> Set:(boolean), Get:(boolean *)  TRUE/FALSE => means that the child widget want to turn On/Off the ability of scroll bar to update the position of scroll indictor according to touched position.
    PROP_SCROLLBAR_WDG_V_TS_SCROLL_ABILITY,    //P2=> Set:(boolean), Get:(boolean *)

    PROP_SCROLLBAR_WDG_SCROLL_STYLE,    //P2=> Set:(u8), Get:(u8*), refer to mae_scrollbarwidget.h
    PROP_SCROLLBAR_WDG_H_TOTAL_RANGE,   //The Horizontal total range, P2=>Set:(u32), Get:(u32*)
    PROP_SCROLLBAR_WDG_H_VISIBLE_RANGE, //The Horizontal visible range, P2=>Set:(u32), Get:(u32*)
    PROP_SCROLLBAR_WDG_H_CURRENT_POS,   //The Horizontal current position, P2=>Set:(u32), Get:(u32*)
    PROP_SCROLLBAR_WDG_H_FOCUSE_ITEM,   //The Horizontal scroller is listen focuse change or scroll change event, P2=>Set:(boolean), Get:(boolean *) => TRUE:listen Focus Change, FALSE:listen Scroll Change
    PROP_SCROLLBAR_WDG_V_TOTAL_RANGE,   //The Vertical total range, P2=>Set:(u32), Get:(u32*)
    PROP_SCROLLBAR_WDG_V_VISIBLE_RANGE, //The Vertical visible range, P2=>Set:(u32), Get:(u32*)
    PROP_SCROLLBAR_WDG_V_CURRENT_POS,   //The Vertical current range, P2=>Set:(u32), Get:(u32*)
    PROP_SCROLLBAR_WDG_V_FOCUSE_ITEM,   //The Vertical scroller is listen focuse change or scroll change event, P2=>Set:(boolean), Get:(boolean *) => TRUE:listen Focus Change, FALSE:listen Scroll Change

    /* If the Bar image is empty, we draw Rect for the scroll bar */
    PROP_SCROLLBAR_WDG_BAR_BORDER_CLR,  //Scroll Bar Border Color, P2 => Set:(RGBColor_t), Get:(RGBColor_t *)
    PROP_SCROLLBAR_WDG_BAR_FILL_CLR,    //Scroll Bar Fill Color, P2 =>Set:(RGBColor_t), Get:(RGBColor_t *)
    PROP_SCROLLBAR_WDG_BAR_FLAG,        //Scroll Bar Rect Flag, P2=> Set:(u32), Get:(u32 *)    ex:DRAW_RECT_FILL_BORDER refer to mae_display.h
    PROP_SCROLLBAR_WDG_BAR_V_WIDTH,     //the width of Vertical Scroll Bar Rect => Set:(u16), Get:(u16 *)
    PROP_SCROLLBAR_WDG_BAR_H_HEIGHT,    //the height of Horizontal Scroll Bar Rect => Set:(u16), Get:(u16*)

    /* If the indicator image is empty, we draw Rect for the scroll indicator */
    PROP_SCROLLBAR_WDG_IND_BORDER_CLR,  //Scroll Indicator Border Color, P2 => Set:(RGBColor_t), Get:(RGBColor_t *)
    PROP_SCROLLBAR_WDG_IND_FILL_CLR,    //Scroll Indicator Fill Color, P2 => Set:(RGBColor_t), Get:(RGBColor_t *)
    PROP_SCROLLBAR_WDG_IND_FLAG,        //Scroll Indicator Rect Flag, P2=> Set:(u32), Get:(u32 *)    ex:DRAW_RECT_FILL_BORDER refer to mae_display.h
    PROP_SCROLLBAR_WDG_IND_V_WIDTH,     //the width of Vertical Scroll Indicator Rect => Set:(u16), Get:(u16 *)
    PROP_SCROLLBAR_WDG_IND_H_HEIGHT,    //the height of Horizontal Scroll Indicator Rect => Set:(u16), Get:(u16*)

    /*If the child widget don't need scroll bar, should scrollbar widget still keep the space */
    PROP_SCROLLBAR_WDG_V_KEEP_WIDTH,     //keep the width for the Vertical Scroller => Set:(boolean) True=>Keep, False=>don't keep
    PROP_SCROLLBAR_WDG_H_KEEP_HEIGHT,    //keep the height for the Horizontal Scroller => Set:(boolean) True=>Keep, False=>don't keep
    PROP_SCROLLBAR_WDG_UPDATE_SCROLL_DATA,    //Set the scroll bar data with ScrollData_t
    PROP_SCROLLBAR_WDG_STEP_CHANGE,      //Set the scroll bar modify step of each time

    // For Softkey widget
    PROP_LEFT_SOFTKEY,                  //P2 : softkey ID
    PROP_MIDDLE_SOFTKEY,                //P2 : softkey ID
    PROP_RIGHT_SOFTKEY,                 //P2 : softkey ID
    PROP_BG_IMAGE_MODE,
    PROP_LRKEY_BG_IMAGE,
    PROP_MIDDLE_BG_IMAGE,

    // For list/grid widget
    PROP_FIRST_INDEX,        //the index of first element on the screen
    PROP_FOCUS_INDEX,        //the index of focused element
    PROP_SEL_INDEX,            //the index of selected element
    PROP_ITEM_WIDTH,        //the width of item in pixels
    PROP_ITEM_HEIGHT,        //the height of item in pixels
    PROP_SEL_ITEMSIZE,        //the width/heigh of selected item in pixels
    PROP_FIRST_INDEX_ADJUST_RULE,      //the adjust rule when PROP_FIRST_INDEX is set. default is FIRST_INDEX_ADJRULE_FILL_PAGE
    //PROP_ROWS,                //the number of rows in the list
    //PROP_COLS,                //the number of columns in the list
    PROP_FIXED_DIRECTION,    //the direction(row or column) to be fixed
    PROP_FIXED_NUM,            //the fixed item number
    PROP_FCS_ITEM_BG_COLOR,        //the property to set/get selected/focused item widget's background color
    PROP_FCS_ITEM_BG_IMAGE,        //the property to set/get selected/focused item widget's background image(IBitmap*)
    PROP_UNFCS_ITEM_BG_COLOR,        //the property to set/get unfocused item widget's background color
    PROP_UNFCS_ITEM_BG_IMAGE,        //the property to set/get unfocused item widget's background image(IBitmap*)
#ifdef __TOUCH_SCREEN_MMI__
    PROP_GRID_WDG_TOUCH_MODE,        // The way dear with touch event. (Default=GridTouchMode_SELECTOR)
    PROP_GRID_WDG_TOUCH_MOVE_STYLE,    // The way dear with the touch moving ouside the hightlight item. (Default=GridTouchMoveStyle_HOLD_SELECTION)
    PROP_GRID_WDG_TOUCH_SELECTED,    // If NotifySelect after released at highlight item. (Default=TRUE)
#endif // __TOUCH_SCREEN_MMI__
    PROP_GRID_WDG_ITEMDRAW_NOTIFIER, ///set this property to set a notifier callback while drawing an item. P2 is a pointer of ItemDrawNotifier_st structure.
    PROP_GRID_WDG_ITEMDRAW_FUNC,
    PROP_GRID_WDG_HIGHLIGHT_ON_TOUCH,/// SET prop,P2 FALSE or TRUE, TRUE: ONLY display highlight item background while touched
    PROP_GRID_WDG_ENABLE_HIGHLIGHT_BG,/// SET prop,P2 FALSE or TRUE, FALSE:use the same background as un-highlight item. default is FALSE
#ifdef __TOUCH_SCREEN_MMI__
    PROP_GRID_WDG_TOUCH_AS_STYLE,    //the property to set the auto-scroll style
    PROP_GRID_WDG_TOUCH_AS_SPEEDUP,    //the property to set the speed up mode when auto-scroll is activated
    PROP_GRID_WDG_TOUCH_AS_THRESHOLD,    //the property to set the threshold to activate the auto-scroll feature
    PROP_GRID_WDG_TOUCH_AS_MOVING,    //the property to set the moving style of auto-scroll function
    PROP_GRID_WDG_TOUCH_SLIDING_DIRECTION,    // the property to set the touch sliding direction
#endif // __TOUCH_SCREEN_MMI__
    PROP_GRID_WDG_ITEM_POS,         // the property to indicate the position of each item of grid widget
    PROP_GRID_WDG_ITEM_EFFECT,
    PROP_GRID_WDG_ITEM_ANIM_ON_FOCUS, // Enable item animation when widget is on focused

//__IME_MMI_SG__
    PROP_GRID_WDG_VARIABLE_ITEM_SIZE,        // horz: width, vertical: height
//__IME_MMI_SG__

    // For ImageTextImage Widget
    PROP_IMGTEXTIMG_WDG_LAYOUT,    //The Layout of the ImageTextImage Widget, P2 => Set:(u8), Get:(u8 *), Ex:Layout_ImageTextImage_ShowAll, please refer to enum e_ImageTextImage_Layout in mae_imagetextimage.h
    PROP_IMGTEXTIMG_WDG_TEXT_LAYOUT_FLAG,    //The Layout Flag of the Text Widget in the ImageTextImage Widget, P2 => Set:(u8), Get:(u8 *), Ex:LAYOUT_ELLIPSIS, please refer to enum e_Text_Layout in mae_textwidget.h
    PROP_IMGTEXTIMG_WDG_PRE_IMAGEWIDTH,    //The width of the image widget prior to the text widget in the ImageTextImage Widget, P2 => Set:(u16), Get:(u16 *)  //P.S. the image height is decided by the height of whole ImageTextImage widget size
    PROP_IMGTEXTIMG_WDG_POST_IMAGEWIDTH,    //The width of the image widget posterior to the text widget in the ImageTextImage Widget, P2 => Set:(u16), Get:(u16 *) //P.S. the image height is decided by the height of whole ImageTextImage widget size
    PROP_IMGTEXTIMG_WDG_PRE_IMAGE_PRE_PADDING,      //The pre padding of the image widget prior to the text widget in the ImageTextImage Widget, P2 => Set:(u16)
    PROP_IMGTEXTIMG_WDG_POST_IMAGE_POST_PADDING,    //The post padding of the image widget posterior to the text widget in the ImageTextImage Widget, P2 => Set:(u16)
    PROP_IMGTEXTIMG_WDG_TEXT_PRE_PADDING,   //The pre padding of the text widget in the ImageTextImage Widget, P2 => Set:(u16)
    PROP_IMGTEXTIMG_WDG_TEXT_POST_PADDING,  //The post padding of the text widget in the ImageTextImage Widget, P2 => Set:(u16)

    PROP_IMGTEXTIMG_WDG_PRE_IMAGEWIDGET,        //for EVT_WIDGET_GET_COMPONENT_WDG: The image widget prior to the text widget in the ImageTextImage Widget, P2 => (GetCompWgt_t **)
    PROP_IMGTEXTIMG_WDG_POST_IMAGEWIDGET,       //for EVT_WIDGET_GET_COMPONENT_WDG: The image widget posterior to the text widget in the ImageTextImage Widget, P2 => (GetCompWgt_t **)
    PROP_IMGTEXTIMG_WDG_TEXTWIDGET,             //for EVT_WIDGET_GET_COMPONENT_WDG: The text widget in the ImageTextImage Widget, P2 => (GetCompWgt_t **)

    // For Title Widget
    PROP_TITLE_WDG_VISIBLE,         //Set/Get the title line visibility. P2 => Set:(boolean), Get:(boolean *), default is TRUE(visible)
    PROP_TITLE_WDG_FIXSIZE,         //Set/Get the fix size setting of title widget. P2 => Set:(boolean), Get:(boolean *), default is TRUE(visible)
    PROP_TITLE_WDG_LAYOUT,          //Set/Get the visibilities of elements in title widget. P2 => Set:(u32), Get:(u32*). See mae_titlewidget.h for more information.
    /*Only for Set Property*/
    PROP_TITLE_WDG_TITLETXT_ALIGNMENT,
    PROP_TITLE_WDG_TITLETXT_FONT_CATE,
    PROP_TITLE_WDG_TITLETXT_FONT_SIZE,
    PROP_TITLE_WDG_TITLETXT_FONT_TYPE,
    PROP_TITLE_WDG_TITLETXT_FG_COLOR,
    PROP_TITLE_WDG_TITLETXT_OUTLINE_COLOR,

    PROP_TITLE_WDG_SMSTXT_FONT_CATE,
    PROP_TITLE_WDG_SMSTXT_FONT_SIZE,
    PROP_TITLE_WDG_SMSTXT_FONT_TYPE,
    PROP_TITLE_WDG_SMSTXT_FG_COLOR,
    PROP_TITLE_WDG_SMSTXT_OUTLINE_COLOR,
    PROP_TITLE_WDG_ELEMENT_VISABLE,
    PROP_TITLE_WDG_ELEMENT_DATA,

    PROP_TITLE_WDG_LISTEN_VIEWMODEL,

    PROP_TITLE_WDG_AUTO_FIT_SMS_TEXT,   // Auto fit sms text widget to the size of the text.

    // For annunciator widget
    // For CaretWidget
    PROP_CARET_WDG_HIDE,                //Set property. P2: TRUE or FALSE (hide or not to hide)
    PROP_CARET_WDG_COLOR,               //Set/Get property. P2: RGBColor_t
    PROP_CARET_WDG_BLINK,               //Set property. P2: TRUE or FALSE (blink or not to blink)
    PROP_CARET_WDG_BLINK_ON_INTERVAL,   //Set/Get property. P2: blink on interval
    PROP_CARET_WDG_BLINK_OFF_INTERVAL,  //Set/Get property. P2: blink off internal

    // For InputWidget
    PROP_INPUT_WDG_TEXT_COLOR,
    PROP_INPUT_WDG_CURSOR_COLOR,
    PROP_INPUT_WDG_HIGHLIGHT_BG_COLOR,
    PROP_INPUT_WDG_HIGHLIGHT_TEXT_COLOR,
    PROP_INPUT_WDG_SMART_SHIFT_MODE,    //Set property. P2: SmartShiftMode_e
    PROP_INPUT_WDG_MULTILINE,           //Set property. P2: TRUE or FALSE (Multi-line or single line)
    PROP_INPUT_WDG_CURRENT_INPUT_MODE,  //Set property. P2: refer to mmi_mmi_mae_inputcontroller.h.
    PROP_INPUT_WDG_CURRENT_INPUT_LANGUAGE,  //Set property. P2: refer to mae_language.h.
    PROP_INPUT_WDG_FIRST_INPUT_KEY_PRESS,//Set property. P2: MAE_KEY ID
    PROP_INPUT_WDG_INSERT_SYMBOL,       //Set property. P2: the unicode of symbol
    PROP_INPUT_WDG_INSERT_TEXT,         //Set property. P2: the unicode of text
    PROP_INPUT_WDG_LINEGAP,             //Set property, P2: LineGap
    PROP_INPUT_WDG_CURRENT_SHIFTMODE,
    PROP_INPUT_WDG_LAUNCH_INPUT_MENU,   //Set property. P2: the pointer to Option Menu widget.
    PROP_INPUT_WDG_ENTRY_OPTION_MENU,   //Set property, when AP launches an option menu if focused widget is input widget,
    PROP_INPUT_WDG_EXIT_OPTION_MENU,    // Set property. When input menu is closed, AP informs input widget to cancel model listener and menu model to option menu.
    PROP_INPUT_WDG_SEND_DTMF_NOTIFY,    // Set property. For Numeric/Dialing only. P2: TRUE or FALSE
    PROP_INPUT_WDG_MAX_BYTE_LENGTH,
    PROP_INPUT_WDG_SMS_7BIT_MAX_WORD_COUNT,
    PROP_INPUT_WDG_SMS_UCS2_MAX_WORD_COUNT,
    PROP_INPUT_WDG_DUMMY_STRING_LENGTH,
    PROP_INPUT_WDG_ENCODING,
    PROP_INPUT_WDG_PASSWORD_STYLE,          //Set property. P2: TRUE or FALSE (PasswordStyle or not)
    PROP_INPUT_WDG_FILENAME,                // Set property, for inputting file name.
    PROP_INPUT_WDG_SCROLL_UP,                    //Set property. For ViewOnly mode.
    PROP_INPUT_WDG_SCROLL_DOWN,                  //Set property. For ViewOnly mode.
    PROP_INPUT_WDG_DISABLE_SYMBOL_TABLE,        //Set property. P2: TRUE/FALSE (Disable symbol table or enable symbol table.)
    PROP_INPUT_WDG_CANNOT_SWITCH_INPUT_MODE,    //Set property. P2: TRUE/FALSE (Can not switch input mode or Enable to switch input mode)
    PROP_INPUT_WDG_ENABLE_MARK_FUNCTIONS,
    PROP_INPUT_WDG_CHINESEINPUT_OFF,
    PROP_INPUT_WDG_SMARTINPUT_OFF,
    PROP_INPUT_WDG_DISABLE_LINEFEED,
    PROP_INPUT_WDG_DISABLE_PAUSE,
    PROP_INPUT_WDG_INSERT_MYWORD,
    PROP_INPUT_WDG_SET_INITTEXT,
    PROP_INPUT_WDG_SET_CURSORPOS,                //Set property, P2: Cursor pos, this event will set cursor position and exit current input mode.
    PROP_INPUT_WDG_ENABLE_DECIMALPOINT,            //Set property, P2: TRUE/FALSE (Can/Can not input decimal point in Rate input mode)
    PROP_INPUT_WDG_SWITCH_NEGATIVE_AND_POSITIVE,    //Set property if current value is negative, convert it to positive value. for Rate input mode only.
    PROP_INPUT_WDG_MAXLEN_AFTER_EXPONENT,            //Set property, max length after exponent
    PROP_INPUT_WDG_MAXLEN_AFTER_DECIMALPOINT,            //Set property, max length after decimal point
    PROP_INPUT_WDG_IME_ASST_MODEL,              ///< Set property, P2: pointer of IMEAssistModel
    PROP_INPUT_WDG_HANDWRITING_ENABLE,            ///< Set property, P2: TRUE/FALSE (Enable/Disable Handwriting)
    PROP_INPUT_WDG_SOFTKEYBOARD_ENABLE,            ///< Set property, P2: TRUE/FALSE (Enable/Disable soft-keyboard)
    PROP_INPUT_WDG_DIALLING_SHIFT_OLDEST,  ///< Set property, P2: TRUE/FALSE (Enable/Disable shift the oldest character when overflow in Dialling input widget)
    PROP_INPUT_WDG_SHOW_BORDER_WHEN_LOSE_FOCUS,
    PROP_INPUT_WDG_FORMAT_STR,    ///<Set property, P2:The format string pointer. This string must have null terminator.
    PROP_INPUT_WDG_LESS_INPUT_LEN_BY_FORMAT_STR, ///< Get property: P2: the less input length according to format string.
    PROP_INPUT_WDG_ADD_CUS_TOOLBOX, /// < Set property, P2: pointer of CusToolBoxItem_t
    PROP_INPUT_WDG_MODEMASK,
    PROP_INPUT_WDG_SOFTKEYBOARD_ALWAYS_ON,
    PROP_INPUT_WDG_SOFTKEYBOARD_VISIBLE_WHILE_INACTIVE,//softkey-board was visible/invisable while Input widget is NOT focus
    PROP_INPUT_WDG_DRAW_UNDER_LINE,
    PROP_INPUT_WDG_POPUP_STYLE,
    PROP_INPUT_WDG_SELECTION_MODE,
    PROP_INPUT_WDG_ASSIGN_FILTER,
    PROP_INPUT_WDG_SET_SELECTION,
    PROP_INPUT_WDG_RANDOM_COLOR_TEXT,
    PROP_INPUT_WDG_RANDOM_COLOR_ARY,
    PROP_INPUT_WDG_FONT_HEIGHT,
    PROP_INPUT_WDG_WORD_DISP_Y,
    PROP_INPUT_WDG_INPUT_ACTION,
    PROP_INPUT_WDG_ENABLE_TOUCH_SLIDING,        // enable touch sliding or not
#ifdef __TOUCH_SCREEN_MMI__
#ifdef __IME_MMI_SOFTKEYBOARD__
#ifdef __IME_MMI_SOFTKEYBOARD_7COL_UI__
	PROP_INPUT_WDG_7COL_SOFTKEYBOARD_NO_SOFTKEY, //When use 7Col soft-keyboard, that the UI style don't have "SoftKey",  set this property, the 7Col soft-keyboard high-light widget can show correct.
#endif //__IME_MMI_SOFTKEYBOARD_7COL_UI__
#endif //__IME_MMI_SOFTKEYBOARD__
#endif //__TOUCH_SCREEN_MMI__
#ifdef __IME_MMI_SG__
    //For InputCandidateWidget
    PROP_INPUTCANDIDATE_WDG_ENABLE_SPELL_FCS_ITEM_COLOR,
    PROP_INPUTCANDIDATE_WDG_ENABLE_CANDIDATE_FCS_ITEM_COLOR,
    PROP_INPUTCANDIDATE_WDG_SET_ONLY_ONE_PAGE_SPELL_LIST,  /// < Set property, P2:BOOLEAN, set only one page spell list (TRUE/FALSE)

    //For SG chinese input method, 待上屏顯示字串長度
    PROP_INPUT_WDG_SG_CHINESE_INPUT_METHOD_PRESELECT_STRING_LEN,
#endif
    // For FormatInputWidget
    PROP_FORMATINPUT_WDG_TEXT_COLOR,
    PROP_FORMATINPUT_WDG_HIGHLIGHT_BG_COLOR,
    PROP_FORMATINPUT_WDG_HIGHLIGHT_TEXT_COLOR,
    PROP_FORMATINPUT_WDG_DATE_VALUE,    //Get/Set property. P2: MAE_DateTime_t
    PROP_FORMATINPUT_WDG_TIME_VALUE,    //Get/Set property. P2: MAE_DateTime_t
    PROP_FORMATINPUT_WDG_IP_VALUE,      //Get/Set property. P2: u32
    PROP_FORMATINPUT_WDG_12HOURFORMAT,  //Get/Set property. P2: TRUE or FALSE (12 Hour format or 24 hour format)
    PROP_FORMATINPUT_WDG_TIMEPERIOD_AM_PM,  //Get/Set property P2 : P2 TimePeriod_t
    PROP_FORMATINPUT_WDG_SET_MAX_YEAR,      //Set property P2: u16, the max year
    PROP_FORMATINPUT_WDG_SET_MIN_YEAR,      //Set property P2: u16, the min year
    PROP_FORMATINPUT_WDG_ENABLE_ADJUST_VALUE_BY_NAVI_UP_DOWN,    //Set property P2: TRUE or FALSE
    PROP_FORMATINPUT_WDG_ENABLE_SECOND_FIELD,        //Set Property, P2: TRUE or FALSE
    PROP_FORMATINPUT_WDG_DATE_DISPLAY_FORMAT,        //Set Property, P2: DateWdgDisplayFormat_e

    // For MenuWidget
    PROP_MENU_WDG_HIGHLIGHTED_INDEX,
    PROP_MENU_WDG_SELECTED_ID,
    PROP_MENU_WDG_FIRST_INDEX,
    PROP_MENU_WDG_DEFAULT_LEFT_SOFTKEY,
    PROP_MENU_WDG_DEFAULT_MIDDLE_SOFTKEY,
    PROP_MENU_WDG_DEFAULT_RIGHT_SOFTKEY,
    PROP_MENU_WDG_TITLE_1_TEXT,
    PROP_MENU_WDG_TITLE_2_TEXT,
    PROP_MENU_WDG_SCROLL_STYLE,
    PROP_MENU_WDG_AUTO_UPDATE_TITLE,
    PROP_MENU_WDG_MAX_MARKED_SIZE,
    PROP_MENU_WDG_MIN_MARKED_SIZE,
    PROP_MENU_WDG_MARKED_ITEM_NUMBER,
    PROP_MENU_WDG_MAX_ITEMS_ON_SCREEN,
    PROP_MENU_WDG_TITLE_2_STATUS,
    PROP_MENU_WDG_HISTORY_INFO,
    PROP_MENU_WDG_ITEM_WIDGET_CLSID,
    PROP_MENU_WDG_ITEM_WIDGET,
    PROP_MENU_WDG_GRID_ITEM_NUM,
    PROP_MENU_WDG_GRID_ITEM_SIZE,
    PROP_MENU_WDG_OPTIONMENU_STYLE,
    PROP_MENU_WDG_ITEM_STYLE,
    PROP_MENU_WDG_BG_IMAGE_ID,
    PROP_MENU_WDG_FCS_ITEM_BG_IMAGE_ID,
    PROP_MENU_WDG_UNFCS_ITEM_BG_IMAGE_ID,
    PROP_MENU_WDG_SCLIND_LEFT_UNPRESSED_IMAGE_ID,
    PROP_MENU_WDG_SCLIND_LEFT_PRESSED_IMAGE_ID,
    PROP_MENU_WDG_SCLIND_RIGHT_UNPRESSED_IMAGE_ID,
    PROP_MENU_WDG_SCLIND_RIGHT_PRESSED_IMAGE_ID,
    PROP_MENU_WDG_SCLIND_UP_UNPRESSED_IMAGE_ID,
    PROP_MENU_WDG_SCLIND_UP_PRESSED_IMAGE_ID,
    PROP_MENU_WDG_SCLIND_DOWN_UNPRESSED_IMAGE_ID,
    PROP_MENU_WDG_SCLIND_DOWN_PRESSED_IMAGE_ID,
    PROP_MENU_WDG_NUMERIC_ACCESS_STATUS,
    PROP_MENU_WDG_AUTO_TOGGLE_ITEM,
    PROP_MENU_WDG_SHOW_MARKED_ITEM_NUMBER,
    PROP_MENU_WDG_SHOW_TOTAL_ITEM_NUMBER,
    PROP_MENU_WDG_EMPTY_TEXT_ID,
    PROP_MENU_WDG_EMPTY_TEXT_COLOR,
    PROP_MENU_WDG_SHOW_EMPTY_TEXT,
    PROP_MENU_WDG_UNAVAIL_ITEM_LEFT_SOFTKEY,
    PROP_MENU_WDG_UNAVAIL_ITEM_MIDDLE_SOFTKEY,
    PROP_MENU_WDG_UNAVAIL_ITEM_RIGHT_SOFTKEY,
    PROP_MENU_WDG_ITEM_UNDERLINE_STATUS,
    PROP_MENU_WDG_MENU_TYPE,
    PROP_MENU_WDG_USER_ACTION_SOFTKEY_ID,
    PROP_MENU_WDG_USER_BACK_SOFTKEY_ID,
    PROP_MENU_WDG_MENUTREE,
    PROP_MENU_WDG_ALLOW_TO_MODIFY_SOFTKEY,
    PROP_MENU_WDG_STARTUP_ANIM,                 //Set/Get property. for startup animation of menu. P2=>Set:(Menu_StartupAnimStyle_e), Get:(Menu_StartupAnimStyle_e *)

#if defined(__FEATURE_MGL__)
    PROP_MENU_WDG_FLIP_START_ANIM,
    PROP_MENU_WDG_FLIP_STOP_ANIM,
    PROP_MENU_WDG_FLIP_ANIM_STYLE,               //Set/Get property. for item flip animation of menu. P2=>Set:(Menu_FlipAnimStyle_e)
    PROP_MENU_WDG_SET_FLIP_ANIM_BITMAP,
#endif

#ifdef __TOUCH_SCREEN_MMI__
    PROP_MENU_WDG_TOUCH_SLIDING_DIRECTION,    // the property to set the touch sliding direction
#endif    //__TOUCH_SCREEN_MMI__

    // for MTSelection Widget
    PROP_MTSELECTION_WDG_SHOW,
    PROP_MTSELECTION_WDG_RESET_CANDIDATES,
    PROP_MTSELECTION_WDG_SELECT_NEXT_CANDIDATE,
    PROP_MTSELECTION_WDG_STYLE,

    // For Progress Widget
    PROP_PROGRESS_WDG_PROGRESS_REPEAT,          //Set/Get property. for auto repeat progress. P2=>Set:(boolean), Get:(boolean *)
    PROP_PROGRESS_WDG_FG_IIMAGE,                //Set property. the foreground IImage P2=>Set:(IImage *), if P2==NULL => draw rect instead of draw the image
    PROP_PROGRESS_WDG_BG_IIMAGE,                //Set property. the background IImage P2=>Set:(IImage *), if P2==NULL => draw rect instead of draw the image
    PROP_PROGRESS_WDG_FG_IMAGE_FILENAME,        //Set property. the foreground Image Filename P2 => (u8 *) file name, if P2==NULL => draw rect instead of using the foreground image
    PROP_PROGRESS_WDG_BG_IMAGE_FILENAME,        //Set property. the background Image Filename P2 => (u8 *) file name, if P2==NULL => draw rect instead of using the foreground image
    PROP_PROGRESS_WDG_FG_RECT_BORDER_CLR,       //Set/Get property, the foreground rect Border Color, P2 => Set:(RGBColor_t), Get:(RGBColor_t *)
    PROP_PROGRESS_WDG_BG_RECT_BORDER_CLR,       //Set/Get property, the background rect Border Color, P2 => Set:(RGBColor_t), Get:(RGBColor_t *)
    PROP_PROGRESS_WDG_FG_RECT_FILL_CLR,         //Set/Get property, the foreground rect Fill Color, P2 => Set:(RGBColor_t), Get:(RGBColor_t *)
    PROP_PROGRESS_WDG_BG_RECT_FILL_CLR,         //Set/Get property, the background rect Fill Color, P2 => Set:(RGBColor_t), Get:(RGBColor_t *)
    PROP_PROGRESS_WDG_FG_RECT_FLAG,             //Set/Get property, the foreground rect Flag, P2=> Set:(u32), Get:(u32 *) ex:DRAW_RECT_FILL_BORDER refer to mae_display.h
    PROP_PROGRESS_WDG_BG_RECT_FLAG,             //Set/Get property, the background rect Flag, P2=> Set:(u32), Get:(u32 *) ex:DRAW_RECT_FILL_BORDER refer to mae_display.h
    PROP_PROGRESS_WDG_TOTAL,                    //Set/Get property. Total Progress Number, P2=>Set:(u16), Get(u16*)
    PROP_PROGRESS_WDG_CURPOS,                   //Set/Get property. Current Progress Position, P2=>Set:(u16), Get(u16*)
    PROP_PROGRESS_WDG_PREFER_CELL_WIDTH,        //Set property. The prefer width of each cell rect in the progress bar, P2=>Set:(u16)
    PROP_PROGRESS_WDG_PREFER_CELL_TOTAL_NUM,    //Set property. The prefer total number of cell rect in the progress bar, P2=>Set:(u16)
    PROP_PROGRESS_WDG_PREFER_CELL_REPEAT_NUM,   //Set property. if the progress type is auto repeat, the prefer repeat cell number, P2=>Set:(u16)
    PROP_PROGRESS_WDG_CELL_WIDTH,               //Get property. The width of each cell rect in the progress bar, P2=>Get:(u16 *)
    PROP_PROGRESS_WDG_CELL_TOTAL_NUM,           //Get property. The total number of cell rect in the progress bar, P2=>Get:(u16 *)
    PROP_PROGRESS_WDG_CELL_REPEAT_NUM,          //Get property. if the progress type is auto repeat, the repeat cell number, P2=>Get:(u16 *)
    PROP_PROGRESS_WDG_AUTO_PROGRESS_ON_OFF,      //Set/Get property, Turn On/Off the auto progress, P2 => Set:(boolean), Get:(boolean *), TRUE=>ON, FALSE=>OFF

    //For OptionMenu Widget
    PROP_OPTMENU_WDG_ADD_L1_VIEW_MDL_LISTENER,
    PROP_OPTMENU_WDG_ADD_L2_VIEW_MDL_LISTENER,
    PROP_OPTMENU_WDG_CANCEL_L1_VIEW_MDL_LISTENER,
    PROP_OPTMENU_WDG_CANCEL_L2_VIEW_MDL_LISTENER,
    PROP_OPTMENU_WDG_SET_L1_MENUMODEL,
    PROP_OPTMENU_WDG_SET_L2_MENUMODEL,
    PROP_OPTMENU_WDG_L1_MENUWIDGET,
    PROP_OPTMENU_WDG_L2_MENUWIDGET,

    //For PopupSelect Widget
    PROP_POPUPSELECT_WDG_SET_MENUMODEL,

    //For Double Item Widget
    PROP_DOUBLEITEM_WDG_UPPERWIDGET,
    PROP_DOUBLEITEM_WDG_DOWNWIDGET,
    PROP_DOUBLEITEM_WDG_FOCUS_ON_UPPERWIDGET,   //Set property, P2=>(boolean), TRUE: the double item widget should focus on the upper widget, when it on focused.
    //FALSE: the double item widget should focus on the downh widget, when it on focused
    PROP_DOUBLEITEM_WDG_BG_COLOR,
    PROP_DOUBLEITEM_WDG_BG_IMAGE,
    PROP_DOUBLEITEM_WDG_DISABLE_DOWNWDG_BG,        // Set property, P2=>(boolean), TRUE: when Line2 Text length is 0, the BG will be disabled. when > 0, the BG will be enabled.
    //FALSE: the Line2 text BG will always enable.     !!Only work for CLSID_TEXT_LINE2INFO_WIDGET !!
    PROP_DOUBLEITEM_WDG_DISABLE_UPWDG_ANIM,                // Disable upper widget animation or not (default: enable)
    PROP_DOUBLEITEM_WDG_DISABLE_DOWNWDG_ANIM,            // Disable down widget animation or not (default: enable)

    //For Image Double Item widget
    PROP_IMGDOUBLEITEM_WDG_PREIMGWIDGET,
    PROP_IMGDOUBLEITEM_WDG_POSTUPPERWIDGET,
    PROP_IMGDOUBLEITEM_WDG_POSTDOWNWIDGET,
    PROP_IMGDOUBLEITEM_WDG_FOUSE_ON_CHILD_WIDGET,        //reference ImgDoubleItemWidgetChildWidget_e to set P2 value

#ifdef __APP_MMI_TUDOU_MENU_ITEM_WDG__
	PROP_IMG_DOUBLEITEM_MULTIFIELD_WDG_PREIMGWIDGET,
	PROP_IMG_DOUBLEITEM_MULTIFIELD_WDG_BACKUPWIDGET,
	PROP_IMG_DOUBLEITEM_MULTIFIELD_WDG_BACKDOWN_FIRST_WIDGET,
	PROP_IMG_DOUBLEITEM_MULTIFIELD_WDG_BACKDOWN_SECOND_WIDGET,
	PROP_IMG_DOUBLEITEM_MULTIFIELD_WDG_BACKDOWN_THIRD_WIDGET,
	PROP_IMG_DOUBLEITEM_MULTIFIELD_WDG_BACKDOWN_FOURTH_WIDGET,
    PROP_IMG_DOUBLEITEM_MULTIFIELD_WDG_FOUSE_ON_CHILD_WIDGET,   //reference ImgDoubleItemWidgetChildWidget_e to set P2 value
#endif
    //For Switch Icon widget
    PROP_SWITCH_WDG_ICON_STYLE,                //Set property, Set the icon style for SwitchIcon widget, P2(Set:u8) => refer to enum Icon_Style_e
    PROP_SWITCH_WDG_ACTIVE_ICON_IMG,        //Set property, Set the active icon bitmap, P2(Set:IBitmap*) => An IBitmap object instance.
    PROP_SWITCH_WDG_INACTIVE_ICON_IMG,        //Set property, Set the inactive icon bitmap, P2(Set:IBitmap*) => An IBitmap object instance.

    //For SwitchIconItem widget
    PROP_SII_WDG_ICON_VISIBLE,                //Set/Get property, Set the icon visible, P2 => boolean
    PROP_SII_WDG_ICON_WIDTH,                //Set/Get property, Set the icon width, P2 => u16 in pixels
    PROP_SII_WDG_ICON_HEIGHT,                //Set/Get property, Set the icon height, P2 => u16 in pixels
    PROP_SII_WDG_ICON_ALIGNMENT,            //Set property, set the icon alignment.
    PROP_SII_WDG_ICON_POS,                  //Set property, set the icon position

    //For Tab widget
    PROP_TABWDG_MODE,                        // u8 Set/Get property
    PROP_TABWDG_ACTIVE_WIDTH,                //u16
    PROP_TABWDG_INACTIVE_WIDTH,                //u16
    PROP_TABWDG_TAB_HEIGHT,                    //u16
    PROP_TABWDG_TAB_HEIGHT_OFFSET,            //u16
    PROP_TABWDG_TAB_LEFT_PADDING,           //u8
    PROP_TABWDG_TAB_RIGHT_PADDING,          //u8
    PROP_TABWDG_TAB_GAP,                    //u16
    PROP_TABWDG_COMP_WDG_SHEET,                // Component widget id
    PROP_TABWDG_TAB_ARROW_ON_OFF,           //Set/Get Prpoerty, to enable/disable the arrow indicator.
    PROP_TABWDG_TAB_WRAP,                   // To enable/disable the wrap Tab to first or last Tab.

    //For Scroll indicator widget
    //PROP_SCLIND_WDG_TYPE,            //P2:u8, the type of indicator , //deprecated
    //PROP_SCLIND_WDG_IND_SIZE,        //P2:u16, indicator size in pixels //deprecated? use PROP_SCLIND_WDG_ instead
    //PROP_SCLIND_WDG_DISPLAY_IND,    //P2:boolean, display indicator or not //deprecated
    //PROP_SCLIND_WDG_L_U_ACTIVE_IMG,   //P2:IImage* , left/up active image //deprecated
    //PROP_SCLIND_WDG_R_D_ACTIVE_IMG,   //P2:IImage* , right/down active image //deprecated
    //PROP_SCLIND_WDG_L_U_INACTIVE_IMG, //P2:IImage* , left/up inactive image //deprecated
    //PROP_SCLIND_WDG_R_D_INACTIVE_IMG, //P2:IImage* , right/down inactive image //deprecated
    PROP_SCLIND_WDG_ARROW_POSITION,    //P2:TRUE, arrow inside, FALSE, arrow outside
    PROP_SCLIND_WDG_INVISIBLE_IF_DISABLE,//P2:TRUE, ; FALSE,
    PROP_SCLIND_WDG_LEFT_ARROW_WIDTH,    //Width for left arrow, P2:u16 to set, *u16 to get
    PROP_SCLIND_WDG_LEFT_ARROW_HEIGHT,   //Height for left arrow, P2:u16 to set, *u16 to get
    PROP_SCLIND_WDG_RIGHT_ARROW_WIDTH,    //Width for right arrow, P2:u16 to set, *u16 to get
    PROP_SCLIND_WDG_RIGHT_ARROW_HEIGHT,   //Height for right arrow, P2:u16 to set, *u16 to get
    PROP_SCLIND_WDG_UP_ARROW_WIDTH,    //Width for up arrow, P2:u16 to set, *u16 to get
    PROP_SCLIND_WDG_UP_ARROW_HEIGHT,   //Height for up arrow, P2:u16 to set, *u16 to get
    PROP_SCLIND_WDG_DOWN_ARROW_WIDTH,    //Width for down arrow, P2:u16 to set, *u16 to get
    PROP_SCLIND_WDG_DOWN_ARROW_HEIGHT,   //Height for down arrow, P2:u16 to set, *u16 to get
    PROP_SCLIND_WDG_LEFT_ARROW_ACTIVE_IMG, //P2:IBitmap*, left active image
    PROP_SCLIND_WDG_LEFT_ARROW_INACTIVE_IMG, //P2:IBitmap*, left inactive image
    PROP_SCLIND_WDG_LEFT_ARROW_PRESSED_IMG, //P2:IBitmap*, left pressed image
    PROP_SCLIND_WDG_RIGHT_ARROW_ACTIVE_IMG, //P2:IBitmap*, right active image
    PROP_SCLIND_WDG_RIGHT_ARROW_INACTIVE_IMG, //P2:IBitmap*, right inactive image
    PROP_SCLIND_WDG_RIGHT_ARROW_PRESSED_IMG, //P2:IBitmap*, right pressed image
    PROP_SCLIND_WDG_UP_ARROW_ACTIVE_IMG, //P2:IBitmap*, up active image
    PROP_SCLIND_WDG_UP_ARROW_INACTIVE_IMG, //P2:IBitmap*, up inactive image
    PROP_SCLIND_WDG_UP_ARROW_PRESSED_IMG, //P2:IBitmap*, up pressed image
    PROP_SCLIND_WDG_DOWN_ARROW_ACTIVE_IMG, //P2:IBitmap*, down active image
    PROP_SCLIND_WDG_DOWN_ARROW_INACTIVE_IMG, //P2:IBitmap*, down inactive image
    PROP_SCLIND_WDG_DOWN_ARROW_PRESSED_IMG, //P2:IBitmap*, down pressed image

    // For PickWidget
    PROP_PICKWDG_DIRECT_TOGGLE,    //Set/Get property, P2=>Set(boolean), Get:(booean*). TRUE: When receive Action key it will toggle pick item directly, FALSE: Do Not direct toggle pick item.

    //For CommonPickItem Widget
    PROP_COMMONPICKITEM_WDG_TOPITEMWDG,
    PROP_COMMONPICKITEM_WDG_PICKWDG,
    PROP_COMMONPICKITEM_WDG_ITEMWDG,

    //For TimerFormat Widget
    PROP_TIMERFORMAT_WDG_FORMAT_LAYOUT,
    PROP_TIMERFORMAT_WDG_SEPARATOR_WIDTH,
    PROP_TIMERFORMAT_WDG_SEPARATER,
    PROP_TIMERFORMAT_WDG_SEPARATER_EXT,
    PROP_TIMERFORMAT_WDG_ALIGNMENT,         //Deprecated? use PROP_WDG_ALIGNMENT

    // For Button-widget
    PROP_BTN_WDG_UNPRESSED_TEXT_COLOR,        ///< Text color for unpressed status.
    PROP_BTN_WDG_UNPRESSED_TEXT_OUTLINE_COLOR,///< Text outline color for unpressed status.
    PROP_BTN_WDG_PRESSED_TEXT_COLOR,          ///< Text color for pressed status.
    PROP_BTN_WDG_PRESSED_TEXT_OUTLINE_COLOR,  ///< Text outline color for pressed status.
    PROP_BTN_WDG_DISABLE_DISPLAY_TEXT,
    PROP_BTN_WDG_DISPLAY_DISABLE_BIDI,

    //For Hand Writing Widget
    PROP_HW_RECOGNITION_MODE,
    PROP_HW_NUM_CANDIDATES,
    PROP_HW_WDG_LOCKSCR,               ///< Set/Get property. P2=>Set(boolean), Get:(booean*). TRUE:lock screen, FALSE:unlock screen
    PROP_HW_WDG_RESET_STROKE,          ///< Set property. P2=>X
    PROP_HW_WDG_FUNCTION,               ///< Set/Get property, P2=>Please refer to HW_Function_e in mae_handwritingwidget.h.

    //For Indicator Widget
    PROP_INDICATOR_WDG_DIRECTION,//deprecated   //Set/Get property. P2=>Set:(boolean), Get:(boolean *). TRUE=>Vertical, FALSE=>Horizontal (Default is FALSE:Horizontal)
    PROP_INDICATOR_FG_TOP_OFFSET,       //Set/Get property, P2=>Set:(u8), Get:(u8 *).
    PROP_INDICATOR_FG_BOTTOM_OFFSET,    //Set/Get property, P2=>Set:(u8), Get:(u8 *).
    PROP_INDICATOR_FG_LEFT_OFFSET,      //Set/Get property, P2=>Set:(u8), Get:(u8 *).
    PROP_INDICATOR_FG_RIGHT_OFFSET,     //Set/Get property, P2=>Set:(u8), Get:(u8 *).
    PROP_INDICATOR_IND_OFFSET,          //Set/Get property, P2=>Set:(u8), Get:(u8 *).
    PROP_INDICATOR_WDG_IND_IMG_ID,      //Set property. the indicator Bitmap Resource ID P2=>Set:(u32)
    PROP_INDICATOR_WDG_FG_IMG_ID,       //Set property. the foreground Bitmap Resource ID P2=>Set:(u32), foreground bitmap => for the range smaller than the indicator position
    PROP_INDICATOR_WDG_BG_IMG_ID,       //Set property. the background Bitmap Resource ID P2=>Set:(u32)
    PROP_INDICATOR_WDG_IND_IMG,         //Set property. the indicator Bitmap P2=>Set:(IBitmap *)
    PROP_INDICATOR_WDG_FG_IMG,          //Set property. the foreground Bitmap P2=>Set:(IBitmap *), foreground bitmap => for the range smaller than the indicator position
    PROP_INDICATOR_WDG_BG_IMG,          //Set property. the background Bitmap P2=>Set:(IBitmap *)
#ifdef __DOWNLOAD_PROGRESS__
    PROP_INDICATOR_DWN_TOP_OFFSET,      //Set/Get property, P2=>Set:(u8), Get:(u8 *).
    PROP_INDICATOR_DWN_BOTTOM_OFFSET,   //Set/Get property, P2=>Set:(u8), Get:(u8 *).
    PROP_INDICATOR_DWN_LEFT_OFFSET,     //Set/Get property, P2=>Set:(u8), Get:(u8 *).
    PROP_INDICATOR_DWN_RIGHT_OFFSET,    //Set/Get property, P2=>Set:(u8), Get:(u8 *).
    PROP_INDICATOR_DWN_END_OFFSET,      //Set/Get property, P2=>Set:(u8), Get:(u8 *).
    PROP_INDICATOR_WDG_DWN_IMG_ID,      //Set property. the download Bitmap Resource ID P2=>Set:(u32), download bitmap => for the range smaller than the indicator position
    PROP_INDICATOR_WDG_DWN_END_IMG_ID,  //Set property. the download-end Bitmap Resource ID P2=>Set:(u32), download-end bitmap => for the range smaller than the indicator position
    PROP_INDICATOR_WDG_DWN_IMG,         //Set property. the download Bitmap P2=>Set:(IBitmap *), download bitmap => for the range smaller than the indicator position
    PROP_INDICATOR_WDG_DWN_END_IMG,     //Set property. the download-end Bitmap P2=>Set:(IBitmap *), download-end bitmap => for the range smaller than the indicator position
    PROP_INDICATOR_DISABLE_IND_MOVE_DWN_BOUNDARY_CHK, //Set property. Disable indicator move download boundary check.
#endif    //__DOWNLOAD_PROGRESS__

    // For Volume widget
    PROP_VOLUME_WDG_INITIAL_VALUE,
    PROP_VOLUME_WDG_CURRENT_LEVEL,
    PROP_VOLUME_WDG_SILENT_MODE,        //Set property, P2: TRUE/FALSE (Is/Is not Silent Mode)
    PROP_VOLUME_WDG_DISABLE_MUTE_BUTTON,
    PROP_VOLUME_WDG_AUDIO_SETTING_ONLY,
    PROP_VOLUME_WDG_NOT_ALLOW_MUTE_LEVEL,  //Set property, P2: TRUE/FALSE (Is not/Is allow set to mute volume level)

    //For SKB widget
    PROP_SKB_WDG_INPUT_RESTRICTION,    //Set property. P2:Please refer to InputRestriction_t in mae_softkeyboardwidget.h
#ifdef __TOUCH_SCREEN_MMI__
#ifdef __IME_MMI_SOFTKEYBOARD__
#ifdef __IME_MMI_SOFTKEYBOARD_7COL_UI__
	PROP_SKB_WDG_7COL_SOFTKEYBOARD_NO_SOFTKEY, //When use 7Col soft-keyboard, that the UI style don't have "SoftKey",  set this property, the 7Col soft-keyboard high-light widget can show correct.
#endif //__IME_MMI_SOFTKEYBOARD_7COL_UI__
#endif //__IME_MMI_SOFTKEYBOARD__
#endif //__TOUCH_SCREEN_MMI__

    //For Fadeout widget
    PROP_FADEOUT_WDG_FO_LEVEL,      ///< Set/Get property. P2=>Set:(FadeoutLevel_t), Get:(FadeoutLevel_t*). reference to mae_graphic_def.h
    PROP_FADEOUT_WDG_ACTIVE_FO,   ///< Activate/inactivate fadeout effect. P2 =>Set:(boolean), Get:(boolean*).
    PROP_FAGEOUT_WDG_SOURCE_TYPE,

    //For Status Bar Widget
    PROP_STATUSBAR_WDG_BG_ENABLE,

    //For Status Page Widget
    PROP_STATUSPAGE_WDG_OPEN,
    PROP_STATUSPAGE_WDG_OPEN_ANIM,
    PROP_STATUSPAGE_WDG_CLOSE_ANIM,
    PROP_STATUSPAGE_WDG_DISABLE_LAUNCH_AP,
    PROP_STATUSPAGE_WDG_DISABLE_SCROLL,
    PROP_STATUSPAGE_WDG_TURN_ON_AIRPLANE_MODE,

    //For Slide Switch Widget
    PROP_SLIDESWITCH_WDG_SLIDERBG_IMAGE,
    PROP_SLIDESWITCH_WDG_SLIDERBG_POS,
    PROP_SLIDESWITCH_WDG_SLIDERBG_SIZE,
    PROP_SLIDESWITCH_WDG_SWITCH_IMAGE,
    PROP_SLIDESWITCH_WDG_SWITCH_POS,
    PROP_SLIDESWITCH_WDG_SWITCH_SIZE,
    PROP_SLIDESWITCH_WDG_SWITCH_MAX_X,
    PROP_SLIDESWITCH_WDG_SLIDERBG_TEXT_ID,

#ifdef __MMI_BALLSLIDE_WDG_SUPPORT__
	PROP_BALLSLIDE_WDG_MISSCALL,
	PROP_BALLSLIDE_WDG_UNREADMSG,
	PROP_WIDGET_RESET,
#endif // __MMI_BALLSLIDE_WDG_SUPPORT__
    //For Transition Widget
    PROP_TRANSITION_WDG_START,
    PROP_TRANSITION_WDG_STOP,
    PROP_TRANSITION_WDG_INTERVAL,     ///< Interval between frames, in ms
    PROP_TRANSITION_WDG_BLOCKSIZE,    ///< width/height of a block, in pixel
#if defined(__UI_STYLE_MMI_IFONE__) || defined(__UI_STYLE_MMI_ANDROID_IDLE__) || defined (__UI_STYLE_MMI_STYLE_SWITCH__)
    PROP_TRANSITION_WDG_START_IFONESET,
    PROP_TRANSITION_WDG_START_IFONEDRAW,
    PROP_TRANSITION_WDG_START_IFONEEND,
    PROP_TRANSITION_WDG_FAST_MOVE,
#endif
    PROP_TRANSITION_WDG_SLIP_START,
    PROP_TRANSITION_WDG_SLIP_MOVE,
    PROP_TRANSITION_WDG_SLIP_RELEASE,
    PROP_TRANSITION_WDG_ANIM_OFFSET,

    //For Ringlist widget
    PROP_RINGLIST_WDG_NO_WRAP,    // Set/Get property. P2=>Set:(boolean), Get(boolean*).
    PROP_RINGLIST_WDG_ENABLE_ROLLING,
    PROP_RINGLIST_WDG_TOUCH_MOVE_STYLE,
    //For Figure Command Date Widget
    PROP_FC_DATE_TIME_WDG_DATE_VALUE,
    PROP_FC_DATE_TIME_WDG_SET_MAX_YEAR,
    PROP_FC_DATE_TIME_WDG_SET_MIN_YEAR,

    //For Figure Command Time Widget
    PROP_FC_TIME_WDG_TIME_VALUE,
    PROP_FC_TIME_WDG_FOCUS_IND,
    //For Figure Command Date Widget
    PROP_FC_DATE_WDG_FOCUS_IND,
    PROP_FC_DATE_WDG_DATE_VALUE,
    PROP_FC_DATE_WDG_SET_MAX_YEAR,
    PROP_FC_DATE_WDG_SET_MIN_YEAR,

    //For Event Widget
    PROP_EVENT_WDG_START_TIME,
    PROP_EVENT_WDG_END_TIME,
    PROP_EVENT_WDG_EVENT_UID,
    PROP_EVENT_WDG_SUMMARY_INFO,
    PROP_EVENT_WDG_ALARM_EXIST,
    PROP_EVENT_WDG_OVERLAP_COUNT,
    PROP_EVENT_WDG_TIME_SLOT_POS_Y,
    PROP_EVENT_WDG_TIME_SLOT_BLOCK_SIZE,
    PROP_EVENT_WDG_EVENT_RANGE_COLOR,
    PROP_EVENT_WDG_SUMMARY_TEXT_COLOR,
    PROP_EVENT_WDG_SINGLE_EVENT_LAYOUT_INFO,
    PROP_EVENT_WDG_GROUP_EVENT_LAYOUT_INFO,
    PROP_EVENT_WDG_FOCUS_EVENT_LAYOUT_INFO,

    // For ShortcutBar widget
    PROP_SHORTCUT_CLOCK_ACTIVATION,
    PROP_SHORTCUT_PET_ACTIVATION,

    // For ShortcutBar widget
    PROP_SHORTCUTBAR_WDG_RELEASEIN,        // when an alive widget is dropped in shortcutbar widget
    PROP_SHORTCUTBAR_WDG_RELEASEOUT,    // when an alive widget is dropped out of shortcutbar widget
    PROP_SHORTCUTBAR_WDG_NETWORK_NAME,
    PROP_SHORTCUTBAR_WDG_SLAVE_NETWORK_NAME,
    PROP_SHORTCUTBAR_WDG_UPDATE_ICON,   //Set property. P2=>Set:(ShortCutBar_ItemIcon_t *). Widget will duplicate the data, AP need to free the ShortCutBar_ItemIcon_t memory by itself.
    PROP_SHORTCUTBAR_WDG_ICON_SLIDE_ANIM,
    PROP_PROPCIRCLECONTAINER_UP_ALIGNMENT,
    PROP_PROPCIRCLECONTAINER_DOWN_ALIGNMENT,

    //For Alive Widget
    PROP_ALIVE_WDG_ID,
    PROP_ALIVE_WDG_VISABLE,
    PROP_ALIVE_WDG_ALIVEWIDGET_SIZE,
    PROP_ALIVE_WDG_ALIVEWIDGET_POS,
    PROP_ALIVE_WDG_IMAGE_POS,
    PROP_ALIVE_WDG_TEXT_POS,
    PROP_ALIVE_WDG_CURRENT_STATE,
    PROP_ALIVE_WDG_CLOCK_MIN_LENGTH,
    PROP_ALIVE_WDG_CLOCK_HOUR_LENGTH,
    PROP_ALIVE_WDG_CLOCK_BRUSH_SIZE,
    PROP_ALIVE_WDG_CLOCK_HAND_COLOR,
    PROP_ALIVE_WDG_IME_ASS_WDG_PTR,
    PROP_ALIVE_WDG_ANIM_STATE,

    //For DateIcon widget
    PROP_DATEICON_WDG_MONTH_HEIGHT,
    //PROP_DATEICON_WDG_DAY_OFFSET,
    PROP_DATEICON_WDG_MONTH_TEXT_COLOR,
    PROP_DATEICON_WDG_MONTH_OUTLINE_COLOR,
    PROP_DATEICON_WDG_DAY_TEXT_COLOR,
    PROP_DATEICON_WDG_DAY_OUTLINE_COLOR,
    PROP_DATEICON_WDG_MONTH_FONT_TYPE,
    PROP_DATEICON_WDG_MONTH_FONT_SIZE,
    PROP_DATEICON_WDG_MONTH_FONT_CATE,
    PROP_DATEICON_WDG_DAY_FONT_TYPE,
    PROP_DATEICON_WDG_DAY_FONT_SIZE,
    PROP_DATEICON_WDG_DAY_FONT_CATE,
    PROP_DATEICON_WDG_AUTO_UPDATE,
    PROP_DATEICON_WDG_DISPLAY_DATETIME,
    PROP_DATEICON_WDG_TIME_FORMAT,

    //For PullDown widget
    PROP_PULLDOWN_WDG_LAYOUT_MODE,   ///< item layout mode, please refer to PullDownWdgMode_et in mae_pulldownwidget.h
    PROP_PULLDOWN_WDG_NAVI_UP_KEY,      ///< P2(u32),key value to move to previous item, default is MAE_KEY_UP
    PROP_PULLDOWN_WDG_NAVI_DOWN_KEY,    ///< P2(u32),key value to move to next item, default is MAE_KEY_DOWN
    PROP_PULLDOWN_WDG_TOGGLE_LIST_KEY,  ///< P2(u32),key value to enable/disable drop down list, default is MAE_KEY_ACTION
    PROP_PULLDOWN_WDG_ARROW_WIDTH,   ///< arrow width in pixels. P2 is a u16 to set, a u16* to get.
    PROP_PULLDOWN_WDG_ARROW_IMG,     ///< To set property only. P2:IBitmap*, down un-pressed image
#ifdef __TOUCH_SCREEN_MMI__
    PROP_PULLDOWN_WDG_PRESSED_ARROW_IMG,///< To set property only. P2:IBitmap*, down pressed image
#endif //__TOUCH_SCREEN_MMI__
    PROP_PULLDOWN_WDG_TEXT_COLOR,   ///< item text color.
    PROP_PULLDOWN_WDG_HL_TEXT_COLOR,///< item text highlighted color
    PROP_PULLDOWN_WDG_HL_BG_COLOR,  ///< item background color.
    PROP_PULLDOWN_WDG_BG_COLOR,     ///< item background color.
    PROP_PULLDOWN_WDG_LIST_BORDER_COLOR,///<

    //for basic bitmap widget
    PROP_BASICBMP_WDG_LINE_COLOR,
    PROP_BASICBMP_WDG_BRUSH,
    PROP_BASICBMP_WDG_FILL,
    PROP_BASICBMP_WDG_FILLED_COLOR,
    PROP_BASICBMP_WDG_ROTATE,
    PROP_BASICBMP_WDG_GRAPHIC_TYPE,

    //for statistics chart widget.....
    PROP_STATCHART_WDG_SET_COLOR_STYLE,
    PROP_STATCHART_WDG_SET_WIDGET_RECT,
    PROP_STATCHART_WDG_SET_SHOW_VERTICAL_LINE,
    PROP_STATCHART_WDG_SET_SHOW_AVERAGE_LINE,
    PROP_STATCHART_WDG_SET_SHOW_VALUE_DOT,
    PROP_STATCHART_WDG_SET_SHOW_BG_GRID,
    PROP_STATCHART_WDG_SET_VERTICAL_LINE_STEP,
    PROP_STATCHART_WDG_SET_REPAINT_CHART,
    PROP_STATCHART_WDG_GET_SUM,
    PROP_STATCHART_WDG_GET_AVERAGE,
    PROP_STATCHART_WDG_GET_MAX_VALUE,
    PROP_STATCHART_WDG_GET_MIN_VALUE,

#ifdef __MMI_SCRIPT_EASY_EDITOR__
    PROP_KMX_WDG_MOVE_CARET_LEFT,
    PROP_KMX_WDG_MOVE_CARET_RIGHT,
    PROP_KMX_WDG_MOVE_CARET_UP,
    PROP_KMX_WDG_MOVE_CARET_DOWN,
    PROP_KMX_WDG_DELETE,
#endif //__MMI_SCRIPT_EASY_EDITOR__
#ifdef __IME_MMI_CSTAR__
    PROP_KMX_INPUTCONTROLLER,
#ifndef __IME_MMI_SOFTKEYBOARD__
    PROP_KMX_DISPLAY_MODE,
#endif
#endif //__IME_MMI_CSTAR__
    PROP_GADGETCONTAINER_WDG_GADGET_INFO,
    PROP_GADGETCONTAINER_WDG_PLAY_START_ANIMATION,
    PROP_WDG_OP_MASTER,
    PROP_WDG_OP_SLAVE,

    // For mainmenu an widget
    PROP_MAINMENU_ANIMATION_STYLE,                  //P2 : style
    PROP_MAINMENU_ANIMATED_EFFECT_STYLE,                  //P2 : style

    // For ifone widget
    PROP_IFONE_WDG_DISPLAY_STYLE,
    PROP_IFONE_WDG_MAINIMAGEID,
    PROP_IFONE_WDG_FOCUSIMAGEID,
    PROP_IFONE_WDG_DRAGIMAGEID,
    PROP_IFONE_WDG_DOWNIMAGEID,
    PROP_IFONE_WDG_ANIM_STYLE,
    PROP_IFONE_WDG_SHOW_IMAGE,
    PROP_IFONE_WDG_SHOW_TEXT,
    PORP_IFONE_WDG_DOWNTEXT_STYLE,
    PROP_IFONE_WDG_CONSTRUCTING_FOLDER,
    PROP_IFONE_WDG_ADDIN_FOLDER,
    PROP_IFONE_WDG_CONSTRUCTING_FOLDER_FINISH,
    PROP_IFONE_WDG_ADDIN_FOLDER_CANCEL,
    PROP_IFONE_WDG_CHILDWDG_VECTOLMOLDEL,
    PROP_IFONE_WDG_SHOW_SHADOW,
    PROP_IFONE_WDG_WIDGETDATA,
    PROP_IFONE_WDG_ADDCHILD,
    PROP_IFONE_WDG_SETANIMTION,
    PROP_IFONE_WDG_FOLDERID,
#ifdef __UI_STYLE_MMI_ANDROID_IDLE__
    PROP_DRAG_WDG_DISPLAY_STYLE,
    PROP_DRAG_WDG_MAINIMAGEID,
    PROP_DRAG_WDG_FOCUSIMAGEID,
    PROP_DRAG_WDG_DRAGIMAGEID,
    PROP_DRAG_WDG_DOWNIMAGEID,
    PROP_DRAG_WDG_ENABLE_ANIM,
    PROP_DRAG_WDG_ANIM_STYLE,
    PROP_DRAG_WDG_SHOW_IMAGE,
    PROP_DRAG_WDG_SHOW_TEXT,
    PROP_DRAG_WDG_DOWNTEXT_IMAGE,
    PORP_DRAG_WDG_DOWNTEXT_STYLE,
	PROP_DRAG_WDG_ENABLE_RESIZE_ANIM,
#endif

    /// effect widgets
    PROP_SCREENSAVER_EFFECT_ID,
    PROP_SCREENSAVER_EFFECT_ANIM,

    PROP_WALLPAPER_3D_EFFECT_ID,
    PROP_WALLPAPER_3D_EFFECT_ANIM,
    PROP_WALLPAPER_3D_EFFECT_PAGE,
    PROP_WALLPAPER_3D_EFFECT_PAGE_TOTAL,
    PROP_WALLPAPER_3D_EFFECT_EDIT,
    PROP_WALLPAPER_3D_EFFECT_CONTENT_CHANGED,
    PROP_WALLPAPER_3D_EFFECT_CONTENT_TOUCHED,
    PROP_WALLPAPER_3D_EFFECT_CONFIGURE,
    PROP_WALLPAPER_3D_EFFECT_WITH_STATUS_BAR,
    PROP_WALLPAPER_3D_EFFECT_CREATEMODE,

    PROP_SPECTRUM_3D_EFFECT_ID,
    PROP_SPECTRUM_3D_EFFECT_ANIM,
    PROP_SPECTRUM_BG_OPAQUE,

    // For GLFotoListWdg
    PROP_GLFOTOLISTWDG_ACTIVE_EFFECT,        // effect when active widget
    PROP_GLFOTOLISTWDG_FOCUS_INDEX,         // get or set focus index.
    PROP_GLFOTOLISTWDG_ENABLE_IND_TXT,        // show indicator text about focused-idx
    PROP_GLFOTOLISTWDG_ENABLE_IND_TXT_TOTAL,// also display total item count on indicator text (when PROP_GLFOTOLISTWDG_ENABLE_IND_TXT is enabled)
    PROP_GLFOTOLISTWDG_ENABLE_MIRROR,        // show mirror of photo
    PROP_GLTYFOTOLISTPAGEWDG_SET_RING,
    PROP_GLTYFOTOLISTPAGEWDG_ITEM_SIZE,
    PROP_GLFOTOLISTWDG_3DLOADER_WDG_SETUP_RESOURCE,
    PROP_GLFOTOLISTWDG_TEXT_WDG_SETUP_RESOURCE,
    PROP_GLFOTOLISTWDG_FILE_INIT_STATUS,
    PROP_GLFOTOLISTWDG_WDG_EVENT_KEY_INPUT,
    PROP_GLFOTOLISTWDG_WDG_FILE_INFO,

    // For GL Contact Browser Widget
    PROP_GCB_WDG_HIGHLIGHTED_ID,
    PROP_GCB_WDG_TAB_STATUS,
    PROP_GCB_WDG_TAB_INDEX,

    PROP_EASE_FUNC,

    // For Rotate Cube Widget
    PROP_ROTATECUBE_WDG_START_FADEOUT,
    PROP_ROTATECUBE_WDG_START_FADEIN,
    PROP_ROTATECUBE_WDG_START_FLIPNEXT,
    PROP_ROTATECUBE_WDG_START_FLIPPRE,

    // For GlTimeInd widget
    PROP_GLTIMEIND_WDG_STYLE,
    PROP_GLTIMEIND_WDG_TIME_FORMAT,
    PROP_GLTIMEIND_WDG_DATE_FORMAT,
    PROP_GLTIMEIND_WDG_BG_IMG,
    PROP_GLTIMEIND_ANIMATION_TYPE,
    PROP_WDG_ALPHA_LEVEL,         // set widget alpha level 0~100.
    PROP_WDG_DRAW_BY_MGL,         // set widget draw by mgl

    // For Panel Widget
    PROP_PANEL_WDG_VISIBLE,         //Set/Get the title line visibility. P2 => Set:(boolean), Get:(boolean *), default is TRUE(visible)
    PROP_PANEL_WDG_FIXSIZE,         //Set/Get the fix size setting of title widget. P2 => Set:(boolean), Get:(boolean *), default is TRUE(visible)
    PROP_PANEL_WDG_LAYOUT,          //Set/Get the visibilities of elements in title widget. P2 => Set:(u32), Get:(u32*). See mae_titlewidget.h for more information.

    /*Only for Set Property*/
    PROP_PANEL_WDG_LISTEN_VIEWMODEL,
    PROP_PANEL_WDG_PANEL_WINDOW_INDEX,
    PROP_PANEL_WDG_PANEL_WINDOW_TOTALSIZE,
    PROP_PANEL_WDG_PANEL_LABEL_ID,
    PROP_PANEL_WDG_PANEL_FONT_CATE,

    /*For GLTransformWidget*/
    PROP_GLTRANSFORM_WDG_TRANSFORM_TYPE_ID,
    PROP_GLTRANSFORM_WDG_FRAME_INDEX,
    PROP_GLTRANSFORM_WDG_FRAME_CNT,
    PROP_GLTRANSFORM_WDG_TRANSFORM_STATE,

    // For GL Photo Slide Widget
    PROP_FOTOSLIDE_DIRECTION,
    // For GL Photo Flip Widget
    PROP_FOTOFLIP_ALL_ITEM_WIDTH,
    PROP_FOTOFLIP_ALL_ITEM_HEIGHT,
    PROP_FOTOFLIP_ITEM_ROTATE_OFFSET,
    PROP_FOTOFLIP_MIDDLE_ITEM_X_POS,
    PROP_FOTOFLIP_MIDDLE_ITEM_Y_POS,
    PROP_FOTOFLIP_MIDDLE_ITEM_WIDTH,
    PROP_FOTOFLIP_MIDDLE_ITEM_HEIGHT,
    PROP_FOTOFLIP_MIDDLE_ITEM_DISTANCE_X,
    PROP_FOTOFLIP_MIDDLE_ITEM_DISTANCE_Z,
    PROP_FOTOFLIP_OTHER_ITEM_ROTATION,
    PROP_FOTOFLIP_OTHER_ITEM_SCALE,
    PROP_FOTOFLIP_OTHER_ITEM_DISTANCE_X,
    PROP_FOTOFLIP_OTHER_ITEM_DISTANCE_Z,
    //For GL BoxList widget
    PROP_GLBOXLIST_WDG_SET_BOXDATA,
    PROP_GLBOXLIST_WDG_SET_DEFAULT_PREIMG_ID,// Set property. P2=>Set:(u32), if the pPreImage of GlBoxListWdgData_t is null, draw the default image.
    PROP_GLBOXLIST_WDG_ENTER_BOX_ANIMATION,  // Set property. P2=>Set:(boolean), TRUE: start the enter box animation. FALSE: stop the enter box animation.
    PROP_GLBOXLIST_WDG_OPEN_ITEM_ANIMATION,  // Set property. P2=>Set:(boolean), TRUE: start the open item animation, after the animation the opened item position won't be reset. FALSE: stop the open animation and reset the focus item position.
    PROP_GLBOXLIST_WDG_OPTION_BUTTON,
    PROP_GLBOXLIST_WDG_REPLY_BUTTON,
    PROP_GLBOXLIST_WDG_DELETE_BUTTON,
    PROP_GLBOXLIST_WDG_BACK_BUTTON,
    PROP_GLBOXLIST_WDG_SLIDE_UP,
    PROP_GLBOXLIST_WDG_SLIDE_DOWN,
    PROP_GLBOXLIST_WDG_SLIDE_LEFT,
    PROP_GLBOXLIST_WDG_SLIDE_RIGHT,
    PROP_GLBOXLIST_WDG_OPEN_ITEM,

    // For GL Rotation Menu Widget
    PROP_ROTATIONMENU_WDG_VIEWANGLE,             //Set/Get property. for camera view angle of  animation of menu. P2=>Set:(u32 angle, 0~360), Get:(u32 *angle, 0~360)
    PROP_ROTATIONMENU_WDG_RADIUS,                  //Set/Get property. for radius of the ring. P2=>Set:(u32 radius), Get:(u32 * radius)
    PROP_ROTATIONMENU_WDG_TEXT_EFFECT,                 //Set/Get property. for displaying text or not. P2=>Set:(boolean), Get:(boolean*)
    PROP_ROTATIONMENU_WDG_ITEMSIZE,                     //Set/Get property. for block size of the menu P2=>Set:(WidgetSize_t size), Get:(WidgetSize_t * size).
    PROP_ROTATIONMENU_WDG_ALPHA_EFFECT,            //Set/Get property. for displaying fading effect expect active one. Set alpha to 1.0 if we don't need fade out effect.P2=>Set:(float), Get:(float*)
    PROP_ROTATIONMENU_WDG_MIRROR_EFFECT,             //Set/Get property. for displaying mirror or not. Set alpha to 0.0 if we don't need mirror effectP2=>Set:(float), Get:(float*)
    PROP_ROTATIONMENU_WDG_LOCK_ITEM,            //Set/Get property. for displaying fading effect expect active one.  P2=>Set:(boolean), Get:(boolean*)

    // For Canvas Widget
    PROP_CANVAS_WDG_BRUSH_SIZE,    // the brush size for draw line
    PROP_CANVAS_WDG_LINE_TYPE,    // refer to DisplayDottedType_e
    PROP_CANVAS_WDG_LINE_COLOR,    // the line and border color

    //For GL FlipEffect widget
    PROP_FLIPEFFECT_WDG_OPEN_ANIM,
    PROP_FLIPEFFECT_WDG_CLOSE_ANIM,
    PROP_FLIPEFFECT_WDG_FLIP_EFFECT,
    PROP_FLIPEFFECT_WDG_FLIP_WEIGHT_RATIO,
    PROP_FLIPEFFECT_WDG_FLIP_BITMAP,
    PROP_FLIPEFFECT_WDG_BACKGROUND_BITMAP,
    PROP_FLIPEFFECT_WDG_BACK_IMGID,
    PROP_FLIPEFFECT_WDG_FLIP_TYPE,
    PROP_FLIPEFFECT_WDG_FLIP_DRAP_STATUS,
    PROP_FLIPEFFECT_WDG_FLIP_STOP,
    PROP_FLIPEFFECT_WDG_TICK_TIMER,
    PROP_FLIPEFFECT_WDG_FLIP_INCRESS_RATE,

	// for GL widgets
	PROP_GL_WDG_FILTER_LINEAR,
	PROP_GL_WDG_NICE_PERSPECTIVE,

    //For GL Magnify effect widget.
    PROP_MAGNIFYEFFECT_WDG_TARGET_BITMAP,
    PROP_MAGNIFYEFFECT_WDG_START_EFFECT,

    //For GL Multi idle page effect widget.
    PROP_GLMULTIIDLEPAGEEFFECT_WDG_FOCUS,
    PROP_GLMULTIIDLEPAGEEFFECT_WDG_START_EFFECT,
    PROP_GLMULTIIDLEPAGEEFFECT_WDG_PAGE_ORDER,
    PROP_GLMULTIIDLEPAGEEFFECT_WDG_EVENT_KEY_INPUT,
    PROP_GLMULTIIDLEPAGEEFFECT_WDG_TIMER,

    //For GL slide effect widget.
    PROP_ALBUMFLIPEFFECT_WDG_SET_START_POS,
    PROP_ALBUMFLIPEFFECT_WDG_CUR_BITMAP,
    PROP_ALBUMFLIPEFFECT_WDG_NEXT_BITMAP,
    PROP_ALBUMFLIPEFFECT_WDG_SLIDE_DIR,
    PROP_ALBUMFLIPEFFECT_WDG_START_ANIM,

    //For GL photo slide effect widget.
    PROP_GLPHOTOSLIDE_WDG_FOCUS_IDX,
    PROP_GLPHOTOSLIDE_WDG_IMAGELIST,
    PROP_GLPHOTOSLIDE_WDG_NEWIMAGE,
    PROP_GLPHOTOSLIDE_WDG_DEFAULT_IMAGEID,

    //For GL coverflow effect widget.
    PROP_GLCOVERFLOW_WDG_FOCUS_IDX,
    PROP_GLCOVERFLOW_WDG_FOCUS_TEXT_NAME,
    PROP_GLCOVERFLOW_WDG_IMAGELIST,
    PROP_GLCOVERFLOW_WDG_DEFAULT_IMAGEID,

    //For Glow Text Widget
    PROP_GLOWTEXT_WDG_TEXT_ID,
    PROP_GLOWTEXT_WDG_TEXT_POS,
    PROP_GLOWTEXT_WDG_TEXT_SIZE,

    //For Flip Text Widget
    PROP_FLIPTEXT_WDG_TEXT_STYLE,
    PROP_FLIPTEXT_WDG_TEXT_STRING,
    PROP_FLIPTEXT_WDG_TEXT_FLIP_TO_STRING,
    PROP_FLIPTEXT_WDG_TEXT_FLIP_CONTINUE,

    //For GL Cloth Modeling Effect widget
    PROP_CLOTHEFFECT_WDG_START_ANIM,
    PROP_CLOTHEFFECT_WDG_EFFECT_TYPE,
    PROP_CLOTHEFFECT_WDG_CLOTH_BITMAP,
    PROP_CLOTHEFFECT_WDG_CLOTH_INIT_POS,
    PROP_CLOTHEFFECT_WDG_MOVE_TYPE,
    PROP_CLOTHEFFECT_WDG_CLOTH_SIZE,
    PROP_CLOTHEFFECT_WDG_ENABLE_DROP,

    //For Text Bubble Widget
    PROP_TEXTBUBBLE_WDG_IMG_ID_TOP_LEFT,
    PROP_TEXTBUBBLE_WDG_IMG_ID_TOP_MID,
    PROP_TEXTBUBBLE_WDG_IMG_ID_TOP_RIGHT,
    PROP_TEXTBUBBLE_WDG_IMG_ID_CENTER_LEFT,
    PROP_TEXTBUBBLE_WDG_IMG_ID_CENTER_MID,
    PROP_TEXTBUBBLE_WDG_IMG_ID_CENTER_RIGHT,
    PROP_TEXTBUBBLE_WDG_IMG_ID_BOTTOM_LEFT,
    PROP_TEXTBUBBLE_WDG_IMG_ID_BOTTOM_MID,
    PROP_TEXTBUBBLE_WDG_IMG_ID_BOTTOM_RIGHT,
    PROP_TEXTBUBBLE_WDG_TXT_SIZE,
    PROP_TEXTBUBBLE_WDG_TXT_OFFSET,
    PROP_TEXTBUBBLE_WDG_TXT_ALIGNMENT,
    PROP_TEXTBUBBLE_WDG_TXT_COLOR,
    PROP_TEXTBUBBLE_WDG_TXT_LINE_HEIGHT,
    PROP_TEXTBUBBLE_WDG_TXT_FONT_CAT,
    PROP_TEXTBUBBLE_WDG_TXT_DATA,

    //For Viewport widget
    PROP_VIEWPORT_WDG_LOCK_HORZ_MOVE_EX,      //P2 : ViewportLockMoveParam_t
    PROP_VIEWPORT_WDG_LOCK_VERT_MOVE_EX,      //P2 : ViewportLockMoveParam_t

    //For Snapshot Widget
    PROP_SNAPSHOT_WDG_ENABLE_SNAPSHOT,        //P2 : boolean

    //  Flip DClock
    PROP_FLIPDCLOCK_FLIP_ENABLE,

    PROP_WIDGET_IDV_END
};

// individual container properties
enum
{
    PROP_CONTAINER_IDV_BEGIN = CNTNR_PROP_START,

    //For MFL container
    PROP_MFL_OFFSET_Y = PROP_CONTAINER_IDV_BEGIN,    //Set P2 is a s32 value, Get P2 is a pointer of s32
#ifdef __TOUCH_SCREEN_MMI__
    PROP_MFL_ENABLE_TOUCH_SLIDE,    // the property to set enable the touch sliding
#endif // __TOUCH_SCREEN_MMI__

    //For Sheet-container
    PROP_SHEETCNTR_ENABLE_SLIDE, //To enable or disable sliding effect. Set=>P2:a boolean value
    PROP_SHEETCNTR_SLIDE_STEP,   //To set the total steps of sliding effect, default is 3. Set=>P2:u8

    //For Viewer-container
    PROP_VIEWERCNTR_MOVE_NEXT_FOCUS_KEY, //P2(MAE_Key_t),key value to move focus to next widget
    PROP_VIEWERCNTR_MOVE_PREV_FOCUS_KEY, //P2(MAE_Key_t),key value to move focus to previous widget
    PROP_VIEWERCNTR_SCROLL_UP_KEY,       //P2(MAE_Key_t),key value scroll up, Default is MAE_KEY_UP
    PROP_VIEWERCNTR_SCROLL_DOWN_KEY,     //P2(MAE_Key_t),key value scroll down, Default is MAE_KEY_DOWN
    PROP_VIEWERCNTR_SCROLL_LEFT_KEY,     //P2(MAE_Key_t),key value scroll left, Default is MAE_KEY_LEFT
    PROP_VIEWERCNTR_SCROLL_RIGHT_KEY,    //P2(MAE_Key_t),key value scroll right, Default is MAE_KEY_RIGHT
    PROP_VIEWERCNTR_MOVINGSTEP,          //P2(u16) : pixels per moving by touching on scroll
    PROP_VIEWERCNTR_FOCUS_WDG_BORDER_COLOR,          ///< Border color for focused widget, P2 => Set:(RGBColor_t), Get:(RGBColor_t*)

    // for highlight widget
    PROP_SKBHIGHLIGHT_WDG_UPDATE,
    PROP_SKBHIGHLIGHT_WDG_TEXT,
    PROP_SKBHIGHLIGHT_WDG_CANDIDATE,
    PROP_SKBHIGHLIGHT_WDG_STYLE,

    // for Animation Container
    PROP_ANIMATIONCONTAINER_ANIMATION_FINISH_THEN_SUSPEND,
    PROP_ANIMATIONCONTAINER_TRANSFORM_TYPE,
    PROP_ANIMATIONCONTAINER_TRANSFORM_TRANSLATE_FRAME,
    PROP_ANIMATIONCONTAINER_TRANSFORM_TRANSLATE_MIN_POS,
    PROP_ANIMATIONCONTAINER_TRANSFORM_TRANSLATE_MAX_POS,
    PROP_ANIMATIONCONTAINER_TRANSFORM_ROTATE_ANGLE,
    PROP_ANIMATIONCONTAINER_TRANSFORM_SET_START_ANGLE,
    PROP_ANIMATIONCONTAINER_TRANSFORM_ROTATE_PIVOT,
    PROP_ANIMATIONCONTAINER_TRANSFORM_RELEASE_MGL_RESOURCE,

    // for Multipage Container
    PROP_MULTIPAGECONTAINER_PAGE_NUMBER,
    PROP_MULTIPAGECONTAINER_AUTO_ANIMATION,
    PROP_MULTIPAGECONTAINER_AUTO_ALIGNMENT,
    PROP_MULTIPAGECONTAINER_WDG_MOVEBEGIN_POS,
    PROP_MULTIPAGECONTAINER_SET_PAGE_CELLSIZE,
    PROP_MULTIPAGECONTAINER_SET_PAGE_ADD_REGION,

    PROP_MULTIPAGECONTAINER_GET_CANVAS,

    // For Screen Effect Widget
    PROP_SCREENEFFECT_WDG_EFFECT_TYPE,
    PROP_SCREENEFFECT_WDG_SNOW_BLOW_DIR,
    PROP_SCREENEFFECT_CLEAR_DATA,
    PROP_SCREENEFFECT_BKIMAGE,

    PROP_CONTAINER_IDV_END
};





/*******************************************************
* Define the enum for property value
*******************************************************/

//langeuage direction
typedef enum e_Lang_Dir
{
    //LANG_DIR_START=0x00,
    LANG_DIR_L_TO_R=0x00,  // left-to-right display layout
    LANG_DIR_R_TO_L,  // right-to-left display layout
    LANG_DIR_TOTAL
} WdgLangDirection_e;
typedef u8 WdgLangDirection_t;

// This enum definition is for PROP_LAYOUT_STYLE
typedef enum
{
    LAYOUT_STYLE_NONE = 0,
    LAYOUT_STYLE_VERTICAL,          //vertical layout style
    LAYOUT_STYLE_HORIZONTAL,        //horizontal layout style
    LAYOUT_STYLE_BOTH,               //both vertical and horizontal layout style
    LAYOUT_STYLE_END
} WdgLayoutStyle_e;
typedef u32 WdgLayoutStyle_t;

typedef enum Alignment_e
{
// Horizontal Alignment
    ALIGN_H_LEFT   = 0x00,
    ALIGN_H_RIGHT,
    ALIGN_H_CENTER,
    ALIGN_H_START, //The inline contents are aligned to the start edge of widget. the start edge is depend on display language.
                     //It will align to right if the display language is right-to-left direction.
    ALIGN_H_END,   //The inline contents are aligned to the end edge of widget. the end edge is depend on display language.
                     //It will align to right if the display language is right-to-left direction.
    ALIGN_H_TOTAL,
    ALIGN_H_MASK   = 0x0F,
// Vertical Alignment
    //ALIGN_V_START  = 0x00,
    ALIGN_V_TOP    = 0x00,
    ALIGN_V_BOTTOM = 0x10,
    ALIGN_V_MIDDLE = 0x20,
    ALIGN_V_TOTAL  = 0x30,
    ALIGN_V_MASK   = 0xF0,
} WdgAlignment_e;
typedef u8 WdgAlignment_t;
/**
* For the value of property PROP_SWITCH_WDG_ICON_STYLE
* A u8 value.
*/
typedef enum
{
    SWITCH_ICON_STYLE_CHECK = 0,
    SWITCH_ICON_STYLE_MARK,
    SWITCH_ICON_STYLE_ACTIVATE,
    SWITCH_ICON_STYLE_RADIO,
    SWITCH_ICON_STYLE_CAMERA_MARK,
    SWITCH_ICON_STYLE_HIDE_ICON,
    SWITCH_ICON_STYLE_GRIDMARK,
    SWITCH_ICON_STYLE_TOTAL,
    SWITCH_ICON_STYLE_MASK = 0x0F
} Icon_Style_e;
typedef u8 Icon_Style_et;

typedef enum
{
    // outer of the item widget
    SWITCH_ICON_POS_OUTER = 0,

    // inner
    // horizontal
    SWITCH_ICON_POS_INNER_H_LEFT    = 0x01,
    SWITCH_ICON_POS_INNER_H_CENTER    = 0x02,
    SWITCH_ICON_POS_INNER_H_RIGHT    = 0x03,
    SWITCH_ICON_POS_INNER_H_MASK    = 0x0F,
    // vertical
    SWITCH_ICON_POS_INNER_V_TOP        = 0x10,
    SWITCH_ICON_POS_INNER_V_MIDDLE    = 0x20,
    SWITCH_ICON_POS_INNER_V_BOTTOM    = 0x30,
    SWITCH_ICON_POS_INNER_V_MASK    = 0xF0
} Icon_Pos_e;
typedef u8 Icon_Pos_et;


typedef enum
{
    WDG_BG_TYPE_COLOR = 0,
    WDG_BG_TYPE_IMAGE
} WdgBackgroundType_t;

/**
* For property PROP_WDG_BG_POSITION.
*/
typedef enum
{
    WDG_BG_POS_INNER = 0,
    WDG_BG_POS_WHOLE
} WdgBackgroundPos_t;
typedef u8 WdgBackgroundPos_et;

typedef enum
{
    FORMAT_LAYOUT_HHMMSS = 0x00,// 00:00:01
    FORMAT_LAYOUT_MMSS,         // 00:01
    FORMAT_LAYOUT_HHMM,         // 00:01
    FORMAT_LAYOUT_HHMMSS_EXT,    // 00:00:01.0
    FORMAT_LAYOUT_HHMMSS_EXT2    // 00:00:01.00
} TimerFormatType_e;
typedef u8 TimerFormatType_t;

typedef enum
{
    WDG_LOOKCTRL_TYPE_THEME = 0,      ///< BG image/color and text color changed by theme
    WDG_LOOKCTRL_TYPE_MANUAL,         ///< BG image/color and text color changed by user

    WDG_LOOKCTRL_TYPE_TOTAL
} WdgLookCtrlType_e;   // Default is WDG_LOOKCTRL_TYPE_THEME

typedef u32 WdgLookCtrlType_t;
/**
* For property PROP_WDG_EASING.
*/
enum
{
    LINEAR_EASE_NONE,
    LINEAR_EASE_IN,
    LINEAR_EASE_OUT,
    LINEAR_EASE_INOUT,
    SINE_EASE_IN,
    SINE_EASE_OUT,
    SINE_EASE_INOUT,
    QUINT_EASE_IN,
    QUINT_EASE_OUT,
    QUINT_EASE_INOUT,
    QUART_EASE_IN,
    QUART_EASE_OUT,
    QUART_EASE_INOUT,
    QUAD_EASE_IN,
    QUAD_EASE_OUT,
    QUAD_EASE_INOUT,
    EXPO_EASE_IN,
    EXPO_EASE_OUT,
    EXPO_EASE_INOUT,
    ELASTIC_EASE_IN,
    ELASTIC_EASE_OUT,
    ELASTIC_EASE_INOUT,
    CUBIC_EASE_IN,
    CUBIC_EASE_OUT,
    CUBIC_EASE_INOUT,
    CIRC_EASE_IN,
    CIRC_EASE_OUT,
    CIRC_EASE_INOUT,
    BOUNCE_EASE_IN,
    BOUNCE_EASE_OUT,
    BOUNCE_EASE_INOUT,
    BACK_EASE_IN,
    BACK_EASE_OUT,
    BACK_EASE_INOUT,
    // integer function
    START_INTEGER_EASE_FUNC,
    BOUNCE_IEASE_OUT = START_INTEGER_EASE_FUNC,
    BACK_IEASE_IN,
    BACK_IEASE_OUT,
    BACK_IEASE_INOUT

};
typedef u32 WdgEasingType_t;


typedef struct
{
    u16 nIndex;
    s16 nPosX;
    s16 nPosY;
    u16 nWidth;
    u16 nHeight;
} WdgItemPos_t;

enum
{
    MENUWIDGET_STARTUP_ANIM_STYLE_NONE,
    MENUWIDGET_STARTUP_ANIM_STYLE_NORMAL,
    MENUWIDGET_STARTUP_ANIM_STYLE_RESTORE,

};
typedef u8 Menu_StartupAnimStyle_e;

#if defined(__FEATURE_MGL__)
enum
{
    MENUWIDGET_FLIP_ANIM_STYLE_NONE,
    MENUWIDGET_FLIP_ANIM_STYLE_VERTICAL,
    MENUWIDGET_FLIP_ANIM_STYLE_HORIZONTAL,
};
typedef u8 Menu_FlipAnimStyle_e;

enum
{
    MENUWIDGET_FLIP_ANIM_VIEW_TYPE_CURRENT = 0,
    MENUWIDGET_FLIP_ANIM_VIEW_TYPE_NEXT,
};
typedef u8 Menu_FlipAnimCatureType_e;

#endif

#endif //__MAE_WIDGET_PROPERTIES_H__
/*=============================================================*/
// end of file
