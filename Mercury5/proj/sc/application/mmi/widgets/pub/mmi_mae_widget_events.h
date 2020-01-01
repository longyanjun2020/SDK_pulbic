/**
* @file    mmi_mae_widget_events.h
* @brief   This file is the collection of widget event definitions
*
* @version $Id: mmi_mae_widget_events.h 33531 2009-06-16 12:42:16Z william.lien $
*/
#ifndef __MMI_MAE_WIDGET_EVENTS_H__
#define __MMI_MAE_WIDGET_EVENTS_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_model_events.h"
#include "mmi_mae_model.h"

/*=============================================================*/
// type and define
/*=============================================================*/

typedef u32 WidgetEvtCode_t;

//#define EVT_WDG_RESERVED_BEGIN      0x10000

#define EVT_WDG_BC_BEGIN            0x3000
#define EVT_WDG_BEGIN               0x4000
#define EVT_CONTAINER_BEGIN         0x4400

#define EVT_VIEWMDL_GROUP           0x20000

#define EVT_VIEWMDL_COMMON_GROUP    0x20100
#define EVT_VIEWMDL_MENU_CMN_GROUP  0x20200
#define EVT_VIEWMDL_MENU_SK_GROUP   0x20300
//#define EVT_VIEWMDL_BEGIN           0x4800
//#define EVT_MENUWIDGET_BEGIN        0x4C00

/*************************************************************************
* Here define the "broadcast" event for all widget
* Range from 0x3000 to
*************************************************************************/
enum {
    EVT_WIDGET_BC_START = EVT_WDG_BC_BEGIN,
    EVT_WIDGET_ACTIVE,                ///< While AP resumed, send this event to widget.
    EVT_WIDGET_INACTIVE,              ///< While AP suspended, send this event to widget.
    EVT_WIDGET_DISPMODE_CHANGED,    ///< while the display mode (portrait / landscape) changed, send this event to widget
    EVT_WIDGET_BC_END
};

/*************************************************************************
* Here define the event for all widget
* Range from 0x4000 to 0x43FF
*************************************************************************/
enum {
    EVT_WIDGET_START = EVT_WDG_BEGIN,

    // !! Don't add event between EVT_WIDGET_CONSTRUCTOR and EVT_WIDGET_DECORATOR_SET_DECWDG
    EVT_WIDGET_CONSTRUCTOR = EVT_WIDGET_START,
    EVT_WIDGET_DESTRUCTOR,
    EVT_WIDGET_GET_SIZE,
    EVT_WIDGET_SET_SIZE,
    EVT_WIDGET_GET_PREFERREDSIZE,
    EVT_WIDGET_GET_PARENT,
    EVT_WIDGET_SET_PARENT,
    EVT_WIDGET_CHECK_INTERSECTOPAQUE,
    EVT_WIDGET_DRAW,
    EVT_WIDGET_SET_MODEL,
    EVT_WIDGET_GET_MODEL,
    EVT_WIDGET_GET_VIEWMODEL,
    EVT_WIDGET_ADD_NOTIFYCB,
    EVT_WIDGET_CANCEL_NOTIFYCB,
    EVT_WIDGET_CONTAINER_ADD_WDG,
    EVT_WIDGET_CONTAINER_DELETE_WDG,
    EVT_WIDGET_CONTAINER_MOVE_WDG,
    EVT_WIDGET_CONTAINER_GET_WDG,
    EVT_WIDGET_CONTAINER_SET_INVALID,
    EVT_WIDGET_CONTAINER_GET_WDGLOCATE,
    EVT_WIDGET_DECORATOR_GET_DECWDG,
    EVT_WIDGET_DECORATOR_SET_DECWDG,
    // !! Don't add event between EVT_WIDGET_CONSTRUCTOR and EVT_WIDGET_DECORATOR_SET_DECWDG

    EVT_WIDGET_SET_ALLNOTIFYCB,

    EVT_WIDGET_GET_PROPERTY, ///< to get property from widget. P1 is property id, P2 is returned property value.
    EVT_WIDGET_SET_PROPERTY,            ///< to set property to widget. P1 is property id, P2 is property value.
    EVT_WIDGET_SET_FOCUS,               ///< P1 is the boolean to set(TRUE)/cancel(FALSE) focus. This will cause child issue EVT_CNTNR_CHILD_SET_FOCUS to notify it's parent
    EVT_WIDGET_IS_ONFOCUS,
    EVT_WIDGET_CANBEFOCUSED,
    EVT_WIDGET_PARENT_SET_FOCUS,        ///< P1 is the boolean to set(TRUE)/cancel(FALSE) focus. internal use only. parent container use this to change child's focus
    EVT_WIDGET_MOVETO_NEXT_ITEM,        ///< For list/grid widget, to move to next item
    EVT_WIDGET_MOVETO_PRIV_ITEM,        ///< for list/grid widget, to move to privious item
    EVT_WIDGET_MENU_SELECT_FOCUS_ITEM,  ///< for menu widget, to select current focus item
    EVT_WIDGET_GET_COMPONENT_WDG,       ///< Get widget's component widget. P1 is component widget id, P2 is pointer of GetCompWgt_t structure.
    EVT_WIDGET_SET_PARENT_VIEWMODEL,    ///< Set parent's viewmodel to child, P1 is a pointer of viewmodel.
    EVT_WIDGET_INPUT_METHOD_CHANGE,     ///<
    EVT_WIDGET_SOFTKEYBOARD_CHANGE,     ///<
    EVT_WIDGET_TITLE_AP_ICON_PRESS,
    EVT_WIDGET_TITLE_INPUT_ICON_PRESS,
    EVT_WIDGET_FORCE_REMOVE,            ///< While a container try to remove a lifting widget, this event would be sent first.
/*    EVT_WIDGET_SELECTED,
    EVT_WIDGET_IS_SELECTED,
    EVT_WIDGET_CANBESELECTED,
    EVT_WIDGET_SELECTED_CANCEL,*/
    EVT_WIDGET_TOGGLE_INPUT_METHOD,
    EVT_WIDGET_SOFTKEY_PRESS,
    EVT_WIDGET_SET_MENU_ITEM_SIZE,
    EVT_WIDGET_DISPLAY_INVISIBLE,
    EVT_WIDGET_DISCONNECT_CHILD,    // if child is released abnormal, use this event to tell parent set its child's pointer as NULL
    EVT_WIDGET_INPUT_METHOD_POS_CHANGE,
    EVT_WIDGET_INPUT_TOOL_BOX_POS_CHANGE,
    EVT_WIDGET_END
};













/*************************************************************************
* Here define the event for all container.
* Range is from 0x4400 to 0x47FF
*************************************************************************/
enum {
    EVT_CNTNR_STAR = EVT_CONTAINER_BEGIN,
    EVT_CNTNR_SETLAYOUT = EVT_CNTNR_STAR,   ///< The container can disable/enable do-layout or force do-layout by this event
    EVT_CNTNR_MOVE_FOCUS,                   ///< P1 is flag, P2 is child widget's object instance
    EVT_CNTNR_GET_FOCUS_WDG,                ///< Get current focused widget. P1 (IBase*):caller instance, P2 (IWidget**):output widget pointer
    EVT_CNTNR_CHILD_SET_FOCUS,              /*!< For internal use only. P1 is a boolean to set(TRUE)/cancel(FALSE) focus,
                                                 P2 is child widget's object instance(IWidget*). Child use this to notify parent
                                                 the child is focused*/
    EVT_CNTNR_END
};

/**
* Flags for event EVT_CNTNR_SETLAYOUT as P1(parameter 1).
*/
enum {
    DISABLE_LAYOUT = 0,    ///< disable container's layout functionality
    ENABLE_LAYOUT,         ///< enable container's layout functionality
    FORCE_LAYOUT           ///< force container to do layout again
};


/**
* Flags for event EVT_CNTNR_MOVE_FOCUS as P1(parameter 1).
*/
enum {
    MOVE_FOCUS_REF_WIDGET = 0,
    MOVE_FOCUS_TO_NEXT,
    MOVE_FOCUS_TO_PREV,
    MOVE_FOCUS_TO_TOP,
    MOVE_FOCUS_TO_BOTTOM/*,
    SELECT_TO_NEXT,
    SELECT_TO_PREV*/
};

typedef enum
{
    MAE_ACTIVE_TYPE_NORMAL,
    MAE_ACTIVE_TYPE_PUSH_POP_VIEW
} MaeActiveType_e;


/*************************************************************************
* View model event for widget.
* Range is from 0x4800 to 0x4BFF
*************************************************************************/
enum {
    EVT_VIEWMDL_COMMON_BEGIN = EVT_VIEWMDL_COMMON_GROUP,

    EVT_VIEWMDL_SET_WIDGET_SIZE,                    ///< general widgets send this viewmodel event to notify size changed.
    EVT_VIEWMDL_SET_MODEL,                            ///< general widgets send this viewmodel event to notify model changed.
    EVT_VIEWMDL_ROOT_INVALIDATE,                    ///< while RootContainer invalidate
    EVT_VIEWMDL_SCROLL_CHANGE,                        ///< for widget change the visible range
    EVT_VIEWMDL_SCROLL_STEP_CHANGE,                            //for widget change the scroll step
    EVT_VIEWMDL_START_SCROLL,                               //for widget start scroll
    EVT_VIEWMDL_SCROLL_FINISHED,                            //for widget scroll finished
    EVT_VIEWMDL_FOCUS_CHANGE,                                //for widget change the focus item
    EVT_VIEWMDL_FOCUS_SELECT,                                //for item is selected
    EVT_VIEWMDL_FOCUS_LONGPRESS,                    		//for item is long pressed.    
    EVT_VIEWMDL_BOUNDS_TOP,                                    //for list widget, when the focus move to the top item and can't wrap
    EVT_VIEWMDL_BOUNDS_BTM,                                    //for list widget, when the focus move to the end item and can't wrap
    EVT_VIEWMDL_MFL_FOCUS_CHANGE,                            //for MFL change the focus item
    EVT_VIEWMDL_MFL_FOCUS_SELECT,                            //for MFL select item
    EVT_VIEWMDL_PROGRESS_CHANGE,                            //for widget change the progress
    EVT_VIEWMDL_SLIDE_CHANGE,                                //for text widget to notify the slide direction change, slide final( when user set not auto repeat the sliding), slide stop
    EVT_VIEWMDL_BLINK,                                        //for widget blink
    EVT_VIEWMDL_TITLE_DATA_CHANGE,                            //for widget change the title, dwParam : TitleDataChangeData_t*
    EVT_VIEWMDL_TITLE_LAYOUT_CHANGE,                        //for widget change the title, dwParam : TitleLayoutChangeData_t*
    EVT_VIEWMDL_TITLE_ELMNT_VIS_CHANGE,                        //for widget change the title, dwParam : TitleElmntVisibleChangeData_t*
    EVT_VIEWMDL_SKB_VIS_CHANGE,                                //for SKB widget change, dwParam : boolean bVisible
    EVT_VIEWMDL_MULTILINE_DISPLAY_CHANGE,                    //for Multiline display redraw
    EVT_VIEWMDL_DTMF,                                        //for DTMF
    EVT_VIEWMDL_SMS_LENGTH_ENCODING,                        //for SMS word count
    EVT_VIEWMDL_TAB_CHANGE,                                    //for Tab widget, when tab changes
    EVT_VIEWMDL_EXCEED_LIMITED_LENGTH,                        //for AP to know the inputted candidate can not be inserted into text model, because the limited length is exceeded.
    EVT_VIEWMDL_TOUCHED_POS,                                //for AP to know the touched cursor position.
    EVT_VIEWMDL_SCROLL_CHANGE_BY_TOUCH,                        //for AP to know user press scroll bar and changed the position of scroll indicator.
    EVT_VIEWMDL_BUTTON_CLICK,                                //Button widget send this event via viewmodel while user clicks this button widget.
    EVT_VIEWMDL_BUTTON_VALID,                                //Button widget send this event via viewmodel while user touches pressed on the button rectangle.
    EVT_VIEWMDL_BUTTON_INVALID,                                //Button widget send this event via viewmodel while user touches pressed but moving outside the button rectangle. Or touch released.
    EVT_VIEWMDL_BUTTON_LONG_PRESS,                            //Button widget send this event via viewmodel while user touches on the button widget for a long time.
    EVT_VIEWMDL_BUTTON_TOUCH_REPEAT,                        //Button widget send this event via viewmodel while user touches on the button widget for a long time.
    EVT_VIEWMDL_SWITCHING,                                    ///< For switch icon widget to notify switching.
    EVT_VIEWMDL_VOLUME_CHANGE,                                //for AP to know the volume is changed
    EVT_VIEWMDL_VOLUME_TIMEOUT,                                // for AP to know the key is not pressed for last 2 seconds
    EVT_VIEWMDL_INPUT_HELPER_COMPLETE,                        //for input helper widget to know to exit
    EVT_VIEWMDL_SLIDE_COMPLETE,                                //for SlideSwitch Widget to notify about slide complete
    EVT_VIEWMDL_TRANSIT_COMPLETE,                            //for transition widget to notify listener that the transition is done
    EVT_VIEWMDL_TRANSIT_CANCEL,
    EVT_VIEWMDL_TRANSIT_SLIP_CHANGE,
    EVT_VIEWMDL_START_ROLLING,                                //For RingList widget to notify rolling started.
    EVT_VIEWMDL_ROLLING_FINISHED,                            //For RingList widget to notify rolling finished.
    EVT_VIEWMDL_EVENT_FOCUS_SELECT,                            //for event widget select item
    EVT_VIEWMDL_INDICATOR_PRESSED,
    EVT_VIEWMDL_INDICATOR_MOVING,
    EVT_VIEWMDL_INDICATOR_RELEASED,
    EVT_VIEWMDL_SHORTCUT_CLICK,                                //Shortcut widget send this event via viewmodel while Shortcut widget is clicked.
    EVT_VIEWMDL_SHORTCUT_ICON_MOVEOUT,                    //Shortcut icon is moved out event
    EVT_VIEWMDL_SHORTCUTBAR_STATUS_CHANGE,                    //ShortcutBar widget send this event via viewmodel while ShortcutBar widget is activated or deactivated.
    EVT_VIEWMDL_STATUSPAGE_CLOSE_ANIM_DONE,                    //StatusPage widget send this event while StatusPage Close
    EVT_VIEWMDL_STATUSPAGE_LAUNCH_APP,                    //StatusPage need to recreate flag (bShowStatusPage)
    EVT_VIEWMDL_STATUSPAGE_AIRPLANE_MODE,                    //StatusPage notify airplane mode status
    EVT_VIEWMDL_TOOLBOX_CLICK,                                //inputcontroller send this event via viewmodel while Toolbox item is clicked, dwParam: ToolBoxItemType_t
    EVT_VIEWMDL_TIME_AMPM_CHANGE,                            //formatinputwidget send this event via viewmodel the AM/PM is changed, dwParam: ToolBoxItemType_t
    EVT_VIEWMDL_TEXT_LINK_CLICK,
    EVT_VIEWMDL_IMG_LINK_CLICK,
    EVT_VIEWMDL_FIELD_AUTO_CORRECT,                            //formatinputwidget send this event via viewmodel to notice holder AP that it keeps focus at original field after correcting the data.
    EVT_VIEWMDL_TEXTBUBBLE_PRESSED,
    EVT_VIEWMDL_TEXTBUBBLE_RELEASED,
    EVT_VIEWMDL_TEXTBUBBLE_CLICK,

    EVT_VIEWMDL_GADGETCONTAINER_EXIT,                        // GadgetContainer: Home button clicked
    EVT_VIEWMDL_GADGETCONTAINER_GADGET_CREATION_FAIL,        // GadgetContainer: Can not create new gadget
    EVT_VIEWMDL_ADJUST_VOLUME_REQ,                            // GadgetContainer: Request AP to do volume adjust
    EVT_VIEWMDL_NOTICE_PLUG_EARPIECE,
    EVT_VIEWMDL_NOTICE_AIR_PLANE_MODE,

    EVT_VIEWMDL_GLBOXLIST_BOX_CHANGE,
    EVT_VIEWMDL_GLBOXLIST_ITEM_OPENED,
    EVT_VIEWMDL_GLBOXLIST_BOX_LABEL_CLICK,
    EVT_VIEWMDL_GLBOXLIST_BUTTON_CLICK,
    EVT_VIEWMDL_GLBOXLIST_TOUCH_MOVE,

    EVT_VIEWMDL_GLFLIP_EFFECT_START,
    EVT_VIEWMDL_GLFLIP_EFFECT_OPEN_COMPLETE,
    EVT_VIEWMDL_GLFLIP_EFFECT_CLOSE_COMPLETE,
    EVT_VIEWMDL_GLFLIP_EFFECT_TOUCH,

    EVT_VIEWMDL_ROTATECUBE_WDG_FADEOUT_EFFECT_DONE,
    EVT_VIEWMDL_ROTATECUBE_WDG_FADEIN_EFFECT_DONE,
    EVT_VIEWMDL_ROTATECUBE_WDG_FLIP_EFFECT_START,      
    EVT_VIEWMDL_ROTATECUBE_WDG_FLIP_EFFECT_DONE,    

    EVT_VIEWMDL_GLALBUMSLIDE_EFFECT_COMPLETE,

    EVT_VIEWMDL_GLTRANSFORM_EFFECT_COMPLETE,

    EVT_VIEWMDL_GLCOVERFLOW_LAUNCH_PLAYLIST,
    EVT_VIEWMDL_GLCOVERFLOW_FOCUS_CHANGE,

    EVT_VIEWMDL_GLPHOTOSLIDE_LAUNCH,
    EVT_VIEWMDL_GLPHOTOSLIDE_EFFECT_COMPLETE,

    //glfotolist focus index notify.
    EVT_VIEWMDL_GLFOTOLISTPAGE_FOCUS_IDX,
    EVT_VIEWMDL_GLFOTOLISTPAGE_FILE_INFO,
    EVT_VIEWMDL_GLFOTOLISTPAGE_NO_ITEM,
    EVT_VIEWMDL_GLFOTOLISTPAGE_STATUS_CHANGE,

    EVT_VIEWMDL_GLMULTIIDLEPAGE_EFFECT_COMPLETE,
    EVT_VIEWMDL_GLMULTIIDLEPAGE_EFFECT_UPDATE_CFG,

    EVT_VIEWMDL_ANIMATIONCONTAINER_ANIMATION_DONE,

    EVT_VIEWMDL_MULTIPAGECONTAINER_ANIMATION_DONE,
    EVT_VIEWMDL_MULTIPAGECONTAINER_PAGE_UPDATE,
    //glmagnify
    EVT_VIEWMDL_GLMAGNIFY_EFFECT_COMPLETE,

    EVT_VIEWMDL_GLCLOTH_EFFECT_OPEN_COMPLETE,
    EVT_VIEWMDL_GLCLOTH_EFFECT_CLOSE_COMPLETE,
    EVT_VIEWMDL_GLCLOTH_EFFECT_CLOSE_START,    
    EVT_VIEWMDL_GLCLOTH_EFFECT_TOUCH_PRESS,
    EVT_VIEWMDL_GLCLOTH_EFFECT_TOUCH_RELEASE,
    //glcirclelist animation done notify.
    EVT_VIEWMDL_GLCIRCLELIST_SLIDE_ANIM_DONE,
    EVT_VIEWMDL_GLCIRCLELIST_ZOOM_ANIM_DONE,
    //glrotationmenu
    EVT_VIEWMDL_GLROTATIONMENU_FOCUS_IDX,
    //wallpaperwidget
    EVT_VIEWMDL_WALLPAPER_CONTENT_CHANGED,
    EVT_VIEWMDL_WALLPAPER_CONTENT_TOUCHED,
    EVT_VIEWMDL_WALLPAPER_PLAY_AUDIO,

#ifdef __IME_MMI_CSTAR__
    EVT_VIEWMDL_KMX_GETSEL,
    EVT_VIEWMDL_KMX_SETSEL,
    EVT_VIEWMDL_KMX_REPLACESEL,
    EVT_VIEWMDL_KMX_GETCARETCHAR,
#endif
    EVT_VIEWMDL_PRE_DRAW,
    EVT_VIEWMDL_END
};













/*************************************************************************
* Here define the event which menu widget interested.
* Range is from 0x4C00 to 0x4FFF
*************************************************************************/
enum {
    EVT_VIEWMDL_MENU_COMMON_BEGIN = EVT_VIEWMDL_MENU_CMN_GROUP,

    EVT_MENUWIDGET_ON_FOCUS,                                //for focus on any item
    EVT_MENUWIDGET_REQ_OPTION2,                                //for "Select" softkey in 1-layer of option menu
    EVT_MENUWIDGET_BACK_TO_OPTION1,                            //for "Back" softkey in 2-layer of option menu
    EVT_MENUWIDGET_MODEL_SIZE_CHANGE,                        //notify option menu that model size is changed
    EVT_MENUWIDGET_EXCEED_MARKED_BOUNDS_MIN,                //notify when total marked number is less than minimum mark number
    EVT_MENUWIDGET_EXCEED_MARKED_BOUNDS_MAX,                //notify when total marked number is more than maximum mark number
    EVT_MENUWIDGET_MARKED_NUMBER_CHANGED,                    //notify when total marked number is changed
    EVT_MENUWIDGET_TOUCH_NO_ITEM,                            //notify when no item is touched
    EVT_MENUWIDGET_BOUNDS_TOP,                              //notify when the focus move to the top item and can't wrap
    EVT_MENUWIDGET_BOUNDS_BTM,                              //notify when the focus move to the buttom item and can't wrap
    EVT_MENUWIDGET_WIDGET_IS_FOCUS,                            //notify when the menu is focus

    EVT_VIEWMDL_MENU_SK_BEGIN = EVT_VIEWMDL_MENU_SK_GROUP,

    EVT_MENUWIDGET_SELECT,                                    //for transfer "Select", "Change" or "OK"(middle softkey softkey event):
    EVT_MENUWIDGET_LONGPRESS,								//for transfer "Long press":    
    EVT_MENUWIDGET_BACK,                                    //for transfer "Back" softkey event
    EVT_MENUWIDGET_SCROLL_FINISHED,

    EVT_MENUWIDGET_SK_CANCEL,                                //for bypass "Cancel" softkey event
    EVT_MENUWIDGET_SK_CHANGE,                                //for bypass "Change" softkey event
    EVT_MENUWIDGET_SK_OPTION,                                //for bypass "Option" softkey event
    EVT_MENUWIDGET_SK_SEND,                                    //for bypass "Send" softkey event
    EVT_MENUWIDGET_SK_SAVE,                                    //for bypass "Save" softkey event
    EVT_MENUWIDGET_SK_EXIT,                                    //for bypass "Exit" softkey event
    EVT_MENUWIDGET_SK_ADD,                                    //for bypass "Add" softkey event
    EVT_MENUWIDGET_SK_CLOSE,                                //for bypass "Close" softkey event
    EVT_MENUWIDGET_SK_ANSWER,                                //for bypass "Answer" softkey event
    EVT_MENUWIDGET_SK_QUIET,                                //for bypass "Quiet" softkey event
    EVT_MENUWIDGET_SK_BUSY,                                    //for bypass "Busy" softkey event
    EVT_MENUWIDGET_SK_REDIAL,                                //for bypass "Redial" softkey event
    EVT_MENUWIDGET_SK_SET,                                    //for bypass "Set" softkey event
    EVT_MENUWIDGET_SK_SETTINGS,                                //for bypass "Settings" softkey event
    EVT_MENUWIDGET_SK_PLAY,                                    //for bypass "Play" softkey event (middle)
    EVT_MENUWIDGET_SK_PAUSE,                                //for bypass "Pause" softkey event (middle)
    EVT_MENUWIDGET_SK_STOP,                                    //for bypass "Stop" softkey event (middle)
    EVT_MENUWIDGET_SK_QUIT,                                    //for bypass "Quit" softkey event
    EVT_MENUWIDGET_SK_CALL,                                    //for bypass "Call" softkey event
    EVT_MENUWIDGET_SK_OK,                                    //for bypass "OK" softkey event
    EVT_MENUWIDGET_SK_CONT_SEL,                                //for bypass "Cont. Sel" softkey event
    EVT_MENUWIDGET_SK_MOVE,                                    //for bypass "Move" softkey event
    EVT_MENUWIDGET_SK_MOVE_TO,                                //for bypass "Move to" softkey event
    EVT_MENUWIDGET_SK_EDIT,                                    //for bypass "Edit" softkey event
    EVT_MENUWIDGET_SK_POWER_OFF,                            //for bypass "Power off" softkey event
    EVT_MENUWIDGET_SK_REPLACE,                                //for bypass "Replace" softkey event
    EVT_MENUWIDGET_SK_EXPORT,                                //for bypass "Export" softkey event
    EVT_MENUWIDGET_SK_VIEW,                                    //for bypass "View" softkey event
    EVT_MENUWIDGET_SK_SEARCH,                                //for bypass "Search" softkey event
    EVT_MENUWIDGET_SK_HELP,                                    //for bypass "Help" softkey event
    EVT_MENUWIDGET_SK_VOLUME,                                //for bypass "Volume" softkey event
    EVT_MENUWIDGET_SK_OPEN,                                    //for bypass "Open" softkey event
    EVT_MENUWIDGET_SK_PICK,                                    //for bypass "Pick" softkey event
    EVT_MENUWIDGET_SK_NEW,                                    //for bypass "New" softkey event
    EVT_MENUWIDGET_SK_COPY_TO,                                //for bypass "Copy to" softkey event
    EVT_MENUWIDGET_SK_DELETE,                                //for bypass "Delete" softkey event
    EVT_MENUWIDGET_SK_UPDATE,                                //for bypass "Update" softkey event
    EVT_MENUWIDGET_SK_MAP,                                  //for bypass "Map" softkey event
    EVT_MENUWIDGET_SK_CONNECT,                                //for bypass "Connect" softkey event
    EVT_MENUWIDGET_SK_QQMESSAGE,                            //for bypass "QQ"soft event
    EVT_MENUWIDGET_SK_PLAYLIST,                             //for bypass "Playlist" softkey event
    EVT_MENUWIDGET_FLIP_COMPLETE,
    EVT_MENUWIDGET_END
};


/*=============================================================*/
// structures for view model events
/*=============================================================*/

/***
* ToolBoxItemType_t is used for EVT_VIEWMDL_TOOLBOX_CLICK
*/
enum
{
    TOOLBOX_ITEM_TYPE_BEGIN = 0,
    TOOLBOX_ITEM_TYPE_BJX = TOOLBOX_ITEM_TYPE_BEGIN,
    TOOLBOX_ITEM_TYPE_END
};
typedef u32 ToolBoxItemType_t;

/***
* ScrollModelEvent_t and ScrollData_t are used for EVT_VIEWMDL_SCROLL_CHANGE
*/
enum
{
    SCROLL_DATA_TYPE_BEGIN = 0,
    SCROLL_DATA_TYPE_VIEW_RANGE = SCROLL_DATA_TYPE_BEGIN,
    SCROLL_DATA_TYPE_ITEM_NUMBER,
    SCROLL_DATA_TYPE_END
};
typedef u16 ScrollDataType_t;

typedef struct{
    u32 nTotal;        ///< Number of total items / Number of total pixels
    u32 nPos;          ///< A zero-based index for current position / Coordinate for current position
    u32 nVisible;      ///< Number of items in the visible range / Number of pixels in the visible range
    ScrollDataType_t nType;///< Indicate nTotal,nPos and nVisible are used for pixels or item number
    boolean bVertical; ///< Vertical or Horizontal. TRUE=> Vertical scroll data, FALSE => Horizontal scroll data
} ScrollData_t;

typedef struct{
    ModelEvent_t MEvtBase;  ///< Model event base
    ScrollData_t data;      ///< Information for scroll change.
} ScrollModelEvent_t;

/***
* FocusModelEvent_t and FocusChangeData_t are used for EVT_VIEWMDL_FOCUS_CHANGE
*/
typedef struct{
    u32 nTotal;     ///< Number of total items
    u32 nPos;       ///< A zero-based index for current position
} FocusChangeData_t;

typedef struct{
    ModelEvent_t MEvtBase;  ///< Model event base
    FocusChangeData_t data; ///< Information for focus change
} FocusModelEvent_t;


/***
* ScrollStepModelEvent_t and ScrollStep_t are used for EVT_VIEWMDL_SCROLL_STEP_CHANGE
*/
typedef struct{
    u16 nStep;         ///< Number of step item
    boolean bVertical; ///< Vertical or Horizontal. TRUE=> Vertical scroll change data, FALSE => Horizontal scroll change data
} ScrollStep_t;

typedef struct{
    ModelEvent_t MEvtBase;  ///< Model event base
    ScrollStep_t data;      ///< Information for scroll-step change
} ScrollStepModelEvent_t;


// for input widget view-only mode to know the current UI display.
typedef struct{
    u32 nStartPos;           ///< the start-displayed position of text
    u32 nEndPos;             ///< the end-displayed position of text
    u32 nStartLineEndPos;    ///< the End position of the last line of displayed text
}MultiLineViewData_t;

typedef struct{
    ModelEvent_t MEvtBase;
    MultiLineViewData_t data;
}MultiLineViewModelEvent_t;

// for input widget to notify AP DTMF.
typedef struct{
    MAE_EventId nEvent;      ///< key press/release event
    u32 nKey;                ///< key id
}DTMFData_t;

typedef struct{
    ModelEvent_t MEvtBase;
    DTMFData_t data;
}DTMFEvent_t;

// for input widget to notify AP SMS Bit Count.
#ifdef __SMS_3GPP_R8_SUPPORT__
typedef struct{
    u32 nEncoding;         ///< Encoding type:Please refer to input_controller.h type: SMSEnncode
    u32 nLockShift;
    u32 nSingleShift;
    u32 nSMSWordCount;     ///< word count
}SMSData_t;
#else //__SMS_3GPP_R8_SUPPORT__
typedef struct{
    u32 nEncoding;         ///< Encoding type:Please refer to input_controller.h type: SMSEnncode
    u32 nSMSWordCount;     ///< word count
}SMSData_t;
#endif //__SMS_3GPP_R8_SUPPORT__

typedef struct{
    ModelEvent_t MEvtBase;
    SMSData_t data;
}SMSDataEvent_t;

/*
param of EVT_VIEWMDL_TITLE_DATA_CHANGE
*/
typedef struct{
    u32 id;       ///< element id, such as TITLEWDG_ELMNT_ID_TITLE_ICON
    u32 type;     ///< data type of new data, such as TITLEWDG_ICON_TYPE_RESID
    u32 data;     ///< new data. id for RESID, u16* for FILENAME, etc.
#ifdef __SMALL_ROM__
    boolean bSmart;///< Smart input or not. ONLY for TITLEWDG_ELMNT_ID_INPUT_ICON!!!
#endif //__SMALL_ROM__
}TitleDataChangeData_t;

/*
param of EVT_VIEWMDL_TITLE_LAYOUT_CHANGE
*/
typedef struct{
    u32 type;     ///< use properties of title widget as type
    u32 value;    ///< use parameter of the property as value
}TitleLayoutChangeData_t;

/*
param of EVT_VIEWMDL_TITLE_ELMNT_VIS_CHANGE
*/
typedef struct{
    u32 id;       ///< element id, such as TITLEWDG_ELMNT_ID_TITLE_ICON
    u32 bVisible; ///< visibility of the element
}TitleElmntVisibleChangeData_t;

/**
* for EVT_VIEWMDL_MFL_FOCUS_CHANGE
* and EVT_VIEWMDL_MFL_FOCUS_SELECT
* The variable dwParam of ModelEvent_t is a pointer of structure MFLFocusData_t.
*/
typedef struct {
    u32     nIdx;     ///< A zero-base index to indicate the focused item or selected item
    u16     nWdgId;   ///< Widget Id to indicate the focused item(widget) or selected item(widget)
} MFLFocusData_t;

/**
* for EVT_VIEWMDL_TAB_CHANGE
* The variable dwParam of ModelEvent_t is a pointer of structure TabChangeData_t.
*/
typedef struct {
    u32     nIdx;         ///< A zero-base index to indicate the focused item
    boolean bDirToRight;  ///<
    boolean bTouchTrigger;///< Indicate this focus change cause for touch or not
} TabChangeData_t;

/*
param of EVT_VIEWMDL_SHORTCUT_CLICK
*/
typedef struct{
    u32 ItemId;              ///< element id, such as SHORTCUT_WDG_ITEM_FMR
    boolean IsActivated;     ///< status for SHORTCUT_WDG_ITEM_CLOCK and SHORTCUT_WDG_ITEM_PET.
} ShortClickData_t;

/*
param of EVT_VIEWMDL_SHORTCUT_ICON_MOVEOUT
*/
typedef struct{
    u32 ItemId;                ///< element id, such as SHORTCUT_WDG_ITEM_FMR
    s16 PosX;
    s16 PosY;
} ShortMoveData_t;

/*
param of EVT_MENUWIDGET_SELECT
*/
typedef struct {
    u32 nFirstIndex;            /* the absolutely index of first item on screen */
    u32 nHighlightedIndex;        /* the absolutely index of the highlighted item */
    u32 nSelectedID;            /* the item ID of the highlighted item */
} HistoryInfo_t;

/*
param of EVT_MENUWIDGET_ON_FOCUS
*/
typedef struct {
    u32 nFirstIndex;            /* the absolutely index of first item on screen */
    u32 nPreviousIndex;            /* the absolutely index of first item on screen */
    u32 nFocusIndex;            /* the absolutely index of the highlighted item */
} FocusInfo_t;

/**
* for EVT_VIEWMDL_GLBOXLIST_BOX_CHANGE
* The variable dwParam of ModelEvent_t is a pointer of structure BoxChangeData_t.
*/
typedef TabChangeData_t BoxChangeData_t;

/**
* for EVT_VIEWMDL_GLBOXLIST_BUTTON_CLICK
* The variable dwParam of ModelEvent_t is a pointer of structure BoxItemButtonClick_t.
*/
enum{
    BoxItemButton_Reply=0,
    BoxItemButton_Delete
};
typedef u8 BoxItemButtion_e;

typedef struct {
    u32 nFocusIndex;            /* the absolutely index of the highlighted item */
    BoxItemButtion_e Button;
} BoxItemButtonClick_t;


/***
* BoxListMoveDir_t is used for EVT_VIEWMDL_GLBOXLIST_TOUCH_MOVE
*/
enum
{
    BoxListMove_Left = 0,
    BoxListMove_Right,
};
typedef u32 BoxListMoveDir_t;

#endif //__MAE_WIDGET_EVENTS_H__
/*=============================================================*/
// end of file
