/**
*     If AP wants to display the state on screen, Title widget will support this need.
*     Title widget can display an icon and a string to show the state or information
*     basically. It can also display additional information, such as to display the
*     SMS Text, tool icon, and input method icon in the right alignment which illustrated
*     below.
*
*     Title widget only shows the basic information on default state. In order to display
*     additional information, you need change the Title widget's layout first. Input Method
*     and tool icons are automatically controlled by Input widget. All that AP to do is
*     only enable the icon of the layout. If the AP would like to display additional text
*     messages, set the attributes in Title widget.
*
*
*       ex: Title Widget
*      +-------+--------------------------------+-------+---------+----------+
*      |  Title|             Title String       | SMS   |    Tool |   Input  |
*      |  Icon |                                | Text  |    Icon |   Icon   |
*      +-------+--------------------------------+-------+---------+----------+
*/

#ifndef __MMI_WDG_TITLE_H__
#define __MMI_WDG_TITLE_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_decorator.h"
#include "mmi_mae_textmodel.h"
#include "mmi_mae_window.h"
#include "mmi_mae_view_wrapper.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/

enum
{
#ifdef __UI_STYLE_MMI_IFONE__
	TITLEWDG_ELMNT_ID_LSK_ICON=0,//
#endif
	TITLEWDG_ELMNT_ID_TITLE_ICON,         ///< Title icon

	TITLEWDG_ELMNT_ID_TITLE_TEXT,           ///< Title text
	TITLEWDG_MDL_ELMNT_ID_SUM,

	TITLEWDG_ELMNT_ID_SMS_TEXT = TITLEWDG_MDL_ELMNT_ID_SUM,             ///< Text for SMS

	TITLEWDG_ELMNT_ID_ALT_ICON,
	TITLEWDG_ELMNT_ID_TOOL_ICON,            ///< Tool icon. if __TOUCH_SCREEN_MMI__ is not defined, this icon will be disabled.
	TITLEWDG_ELMNT_ID_INPUT_ICON,           ///< Input method icon
    TITLEWDG_ELMNT_ID_AP_ICON,
#ifdef __UI_STYLE_MMI_IFONE__
	TITLEWDG_ELMNT_ID_BACK_ICON,	//
#endif
	TITLEWDG_ELMNT_ID_TOTAL
};
typedef u32 WdgTitleStyle_t;
//deprecated
#define TITLEWDG_ELMNT_ID_SOFTKB_ICON  TITLEWDG_ELMNT_ID_TOOL_ICON


/** TitleInfo
*
* @brief    pTitleIcon:    title icon image
*           pTitleText:    title text
*
*/
typedef struct {
	IImage      *pTitleIcon;      ///< title icon image
	MAE_WChar   *pTitleText;      ///< title text
} TitleInfo;

/** MaeTitleElementVisible_t
*
* @brief    u32ElementId:    element id, such as TITLEWDG_ELMNT_ID_TITLE_ICON
*           bVisible:        visibility of the element
*
*/
typedef struct
{
    u32 u32ElementId; ///< element id, such as TITLEWDG_ELMNT_ID_TITLE_ICON
    boolean bVisible; ///< visibility of the element
} MaeTitleElementVisible_t;

/** MaeTitleElementData_t
*
* @brief    u32ElementId:
*           u32DataType:
*           u32Data:
*
*/
typedef struct
{
    u32 u32ElementId;
    u32 u32DataType;
    u32 u32Data;
} MaeTitleElementData_t;

/* TitleWidget element id, !!from left to right!! */
#ifdef __UI_STYLE_MMI_IFONE__
enum
{
	TITLEBUTTOM_BACK = 0,
	TITLEBUTTOM_OPTION,
	TITLEBUTTOM_TOTAL
};
typedef struct {
	MAEClsId_t	clsID;
	u32	iconID;
	u16	unpress_imgID;
	u16	press_imgID;
}CLS_BUTT_STRUCT;
#endif
/* Icon type*/
enum
{
	TITLEWDG_ICON_TYPE_FILENAME=0,      ///< data type: MAE_WChar*
	TITLEWDG_ICON_TYPE_RESID,           ///< data type: u32
	TITLEWDG_ICON_TYPE_IMAGE,           ///< data type: IImage*
	TITLEWDG_ICON_TYPE_TOTAL
};

/* Text type*/
enum
{
	TITLEWDG_TEXT_TYPE_STRING=0,        ///< data type: MAE_WChar*
	TITLEWDG_TEXT_TYPE_RESID,           ///< data type: u32
	TITLEWDG_TEXT_TYPE_TOTAL
};

#define TITLEWDG_ELMNT_MSK(_id)  ((u32)1<<_id)
#define TITLEWDG_ELMNT_MSK_ALL   0xFFFFFFFF

typedef enum
{
    WDG_TITLE_ELEMENT_TITLE_ICON = TITLEWDG_ELMNT_ID_TITLE_ICON,       ///< Title icon
    WDG_TITLE_ELEMENT_TITLE_TEXT = TITLEWDG_ELMNT_ID_TITLE_TEXT,       ///< Title text
    WDG_TITLE_ELEMENT_SMS_TEXT = TITLEWDG_ELMNT_ID_SMS_TEXT,           ///< Text for SMS
    WDG_TITLE_ELEMENT_TOOL_ICON = TITLEWDG_ELMNT_ID_TOOL_ICON,         ///< Tool icon. if __TOUCH_SCREEN_MMI__ is not defined, this icon will be disabled.
    WDG_TITLE_ELEMENT_INPUT_ICON = TITLEWDG_ELMNT_ID_INPUT_ICON,       ///< Input method icon
} WdgTitleElementId_e;

typedef enum
{
    WDG_TITLE_ELEMENT_DATA_TYPE_STRING = TITLEWDG_ICON_TYPE_FILENAME,    ///< data type: MAE_WChar*
    WDG_TITLE_ELEMENT_DATA_TYPE_ID = TITLEWDG_ICON_TYPE_RESID,           ///< data type: u32
    WDG_TITLE_ELEMENT_DATA_TYPE_IMAGE = TITLEWDG_ICON_TYPE_IMAGE,        ///< data type: IImage*
} WdgTitleElementDataType_e;

/** WdgTitleTitleText_t
*
* @brief    nTitletextAlignment:        The value of TitletextAlignment
*           nTitletextFontCate:         The value of font Category
*           nTitleTextFontType:         The value of Title text Font Type
*           nTitletextFontSize:         Title text FG Color
*           nTitleTextFontType:         Title text Outline Color
*
*/
typedef struct
{
    u32                     nTitletextAlignment;      //The value of TitletextAlignment
    u32                     nTitletextFontCate;       //The value of font Category
    u32                     nTitleTextFontType;       //The value of Title text Font Type
    RGBColor_t              nTitleTextFGColor;        //Title text FG Color
    RGBColor_t              nTitleTextOutlineColor;   //Title text Outline Color
}WdgTitleTitleText_t;

/** WdgTitleSMSText_t
*
* @brief    nFontCate:              The font Category
*           nFontType:              The font type
*           nSmsTextFGColor:        Sms text FG Color
*           nSmsTextOutlineColor:   Sms text outline color
*
*/
typedef struct
{
    FontCategory_t        nFontCate;                //The font size
    FontType_t            nFontType;                //The font type
    RGBColor_t            nSmsTextFGColor;          //Sms text FG Color
    RGBColor_t            nSmsTextOutlineColor;     //Sms text outline color
}WdgTitleSMSText_t;

/** WdgTitleDisplayData_t
* @brief        Display data of Title Widget, can be image and text.
*
* @brief        pImage      Image Display data of Title Widget.
* @brief        pText       Text Display data of Title Widget.
*
*/
typedef struct {
    IImage                  *pImage;
    MAE_WChar               *pText;
}WdgTitleDisplayData_t;

/** WdgTitleDisplayDataId_t
* @brief        Display data of Title Widget bi ID.
*
* @brief        nImageID    Image Display data ID of Title Widget.
* @brief        nTextID     Text Display data ID of Title Widget.
*
*/
typedef struct{
    u32 nImageID;
    u32 nTextID;
}WdgTitleDisplayDataId_t;

/** WdgTitleConfigData_t
*
* @brief    bVisible    Set the title line visibility.
*           nLayout     Set the visibilities of elements(ex, Title Icon, Title Image...) in title widget.
*
*/
typedef struct
{
    boolean                 bVisible;
    WdgTitleStyle_t         nLayout;
}WdgTitleConfigData_t;

typedef struct
{
    Point_t                 sRealPos;
    MAEEvent_t              evt;
}WdgTitleInputIconPressData_t;


/** PfnWdgTitleWidgetDataChange
* @brief      CB register by "WdgTitleRegisterDataChangeCb"
*             and will be trigger when the data of widget is changed
*
* @param[in]  pApplet       The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData      User data ap developer setting when register CB.
* @param[in]  nEvtCode      Widget Event Code, only useful for softkey event
* @param[in]  dwParam     The data word param (NOT use now)
* @param[in]  pIWidget      The widget instance
*
*/
typedef void (*PfnWdgTitleWidgetDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

/** PfnWdgTitleWidgetAPIconPress
* @brief      CB register by "WdgTitleRegisterAPIconPressCb"
*             and will be trigger while ap icon be pressed.
*
* @param[in]  pApplet               The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData              User data ap developer setting when register CB.
* @param[in]  nEvtCode              Widget Event Code, only useful for softkey event
* @param[in]  u32TitleIconId        The title icon id
* @param[in]  pIWidget              The widget instance
*
*/
typedef void (*PfnWdgTitleWidgetAPIconPress) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 u32TitleIconId, IWidget *pWidget);

/** PfnWdgTitleWidgetInputIconPress
* @brief      CB register by "WdgTitleRegisterInputIconPressCb"
*             and will be trigger while input toolbox and input method icon be pressed.
*
* @param[in]  pApplet               The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData              User data ap developer setting when register CB.
* @param[in]  nEvtCode              Widget Event Code, only useful for softkey event
* @param[in]  u32TitleIconId        The title icon id
* @param[in]  pIWidget              The widget instance
*
*/
typedef void (*PfnWdgTitleWidgetInputIconPress) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 pTitleInputIconPressData, IWidget *pWidget);

/*=============================================================*/
// functions
/*=============================================================*/
/** WdgTitleCreateForWnd
* @brief        Title widget create function for Window
*
* @param[in]    hWin         The window handle
* @param[in]    pPos            A pointer of widget position; can't be NULL.
* @param[in]    pSize           A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID       The widget unique ID of window
* @param[in]    pData           Widget Common Data, refer to WdgTitleConfigData_t.
*                               If set pSize = NULL : means you want Default Value;
*
* @retval       The pointer of Title      Success.
* @retval       NULL                      Failed.
*
*/
IWidget* WdgTitleCreateForWnd
(
    HWIN            hWin,
    Pos_t                  *pPos,
    WidgetSize_t           *pSize,
    u16                    nWidgetID,
    WdgTitleConfigData_t   *pData
);

/** WdgTitleCommonSetTitleText
* @brief        Set title text alignment, font size, font type, foreground color, and text outline color
*
* @param[in]    pWDGTitle              The Title widget which want to be set
* @param[in]    pTitleText             Pointer to WdgTitleTitleText_t
*
* @retval        MAE_RET_SUCCESS       Success.
* @retval        MAE_RET_BAD_PARAM     Failed. pTitleText is NULL
* @retval        MAE_RET_FAILED        Failed.
*
*/
MAE_Ret WdgTitleCommonSetTitleText
(
    IWidget                *pWDGTitle,
    WdgTitleTitleText_t    *pTitleText
);

/** WdgTitleCommonSetSMSText
* @brief        Set sms text font size, font type, foreground color, and outline color
*
* @param[in]    pWDGTitle           The Title widget which want to be set
* @param[in]    pSMSText            Pointer to WdgTitleSMSText_t
*
* @retval       MAE_RET_SUCCESS     Success.
* @retval       MAE_RET_BAD_PARAM   Failed. pSMSText is NULL
* @retval       MAE_RET_FAILED      Failed.
*
*/
MAE_Ret WdgTitleCommonSetSMSText
(
    IWidget                  *pWDGTitle,
    WdgTitleSMSText_t        *pSMSText
);

/** WdgTitleCommonSetSMSTextAutoFit
* @brief        Enable/disable sms text widget auto fit, when enabled, sms text widget will be automatically fit to the size of the text.
*
* @param[in]    pWDGTitle           The Title widget which want to be set
* @param[in]    bAutoFit            TRUE: enable, FALSE: disable. Default is enabled.
*
* @retval       MAE_RET_SUCCESS     Success.
* @retval       MAE_RET_FAILED      Failed.
*
*/
MAE_Ret WdgTitleCommonSetSMSTextAutoFit
(
    IWidget                 *pWDGTitle,
    boolean                 bAutoFit
);

/*=============================================================*/
/** WdgTitleCreate
* @brief        Create Title widget
*
* @retval       The pointer of Title pointer    Success.
* @retval       NULL                            Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgTitleCreate
(
    void
);
/*=============================================================*/
/** WdgTitleSetData
* @brief        Set display data for title widget.
*               Specific data for title widget.
*
* @param[in]    pWDGTitle         Pointer to the Title widget
* @param[in]    pDispData         Display data of Title Widget.
*                                 pDispData->pImage NULL, means no image display.
*                                 pDispData->pText NULL,  means no text display.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTitleSetData
(
    IWidget                  *pWDGTitle,
    WdgTitleDisplayData_t    *pDispData
);

/** WdgTitleSetDataByID
* @brief        Set display data for title widget.
*               Specific data for title widget.
*
* @param[in]    pWDGTitle         Pointer to the Title widget
* @param[in]    pDispData         Display data of Title Widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTitleSetDataByID
(
    IWidget                  *pWDGTitle,
    WdgTitleDisplayDataId_t  *pDispData
);

/** WdgTitleSetTextData
* @brief        Set text data for title widget.
*
* @param[in]    pWDGTitle         Pointer to the Title widget
* @param[in]    pTextData         Text display data of Title Widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgTitleSetTextData
(
    IWidget                 *pWDGTitle,
    MAE_WChar               *pTextData
);

/** WdgTitleSetTextDataByID
* @brief        Set text data by Text ID for title widget.
*
* @param[in]    pWDGTitle      Pointer to the Title widget
* @param[in]    nTextID        Text ID of Title Widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgTitleSetTextDataByID
(
    IWidget             *pWDGTitle,
    u32                 nTextID
);

/** WdgTitleSetImageData
* @brief        Set image data for title widget.
*
* @param[in]    pWDGTitle         Pointer to the Title widget
* @param[in]    pImageData        Image display data of Title Widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTitleSetImageData
(
    IWidget                 *pWDGTitle,
    IImage                  *pImageData
);

/** WdgTitleSetImageDataByID
* @brief        Set image data by Text ID for title widget.
*
* @param[in]    pWDGTitle       Pointer to the Title widget
* @param[in]    nImageID        Image ID of Title Widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTitleSetImageDataByID
(
    IWidget              *pWDGTitle,
    u32                  nImageID
);

/** WdgTitleSetSMSTextData
* @brief        Set SMS text data for title widget.
*
* @param[in]    pWDGTitle       Pointer to the Title widget
* @param[in]    pTextData       Text display data of Title Widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgTitleSetSMSTextData
(
    IWidget           *pWDGTitle,
    MAE_WChar         *pTextData
);

/** WdgTitleSetSMSTextDataByID
* @brief        Set SMS text data by Text ID for title widget.
*
* @param[in]    pWDGTitle      Pointer to the Title widget
* @param[in]    nTextID        Text ID of Title Widget.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTitleSetSMSTextDataByID
(
    IWidget             *pWDGTitle,
    u32                 nTextID
);

/** WdgTitleSetVisible
* @brief        Set the title line visibility
*
* @param[in]    pWDGTitle     Pointer to the Title widget
* @param[in]    bVisible      The boolean of visible
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTitleSetVisible
(
    IWidget                *pWDGTitle,
    boolean                 bVisible
)
{
    return WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_VISIBLE, (u32)bVisible);
}

/** WdgTitleSetElementVisible
* @brief        Set the title line visibility
*
* @param[in]    pWDGTitle     Pointer to the Title widget
* @param[in]    eElementId    Element ID
* @param[in]    bVisible      The boolean of visible
*
* @retval       None
*
*/
__INLINE void WdgTitleSetElementVisible( IWidget *pWDGTitle, WdgTitleElementId_e eElementId, boolean bVisible)
{
    MaeTitleElementVisible_t sElementData;

    sElementData.u32ElementId = eElementId;
    sElementData.bVisible = bVisible;
    WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_ELEMENT_VISABLE, (u32)&sElementData);
}

/** WdgTitleSetElementData
* @brief        Set the title element data
*
* @param[in]    pWDGTitle     Pointer to the Title widget
* @param[in]    eElementId    Element ID
* @param[in]    eDataType     Data type
* @param[in]    u32Data       Data
*
* @retval       None
*
*/
__INLINE void WdgTitleSetElementData( IWidget *pWDGTitle, WdgTitleElementId_e eElementId, WdgTitleElementDataType_e eDataType, u32 u32Data)
{
    MaeTitleElementData_t sElementData;

    sElementData.u32ElementId = eElementId;
    sElementData.u32DataType = eDataType;
    sElementData.u32Data = u32Data;
    WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_ELEMENT_DATA, (u32)&sElementData);
}



/** WdgTitleSetLayout
* @brief        Set the visibilities of elements(ex, Title Icon, Title Image...) in title widget.
*
* @param[in]    pWDGTitle     Pointer to the Title widget
* @param[in]    nLayout       The value of layout item visibilities
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTitleSetLayout
(
    IWidget                 *pWDGTitle,
    WdgTitleStyle_t         nLayout
)
{
    return WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_LAYOUT, (u32)nLayout);
}

/** WdgTitleSetTitleTextAlignment
* @brief        set title text alignment
*
* @param[in]    pWDGTitle         Pointer to the Title widget
* @param[in]    nTitleTextAlignment        The value of TitleTextAlignment
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTitleSetTitleTextAlignment
(
    IWidget           *pWDGTitle,
    WdgAlignment_e    nTitleTextAlignment
)
{
    return WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_TITLETXT_ALIGNMENT, (u32)nTitleTextAlignment);
}

/** WdgTitleSetTitleTextFontCategory
* @brief        set title text font Category
*
* @param[in]    pWDGTitle           Pointer to the Title widget
* @param[in]    nTitleTextFontSize  The value of font Category
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTitleSetTitleTextFontCategory
(
    IWidget                 *pWDGTitle,
    FontCategory_t          FC
)
{
    return WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_TITLETXT_FONT_CATE, (u32)FC);
}

__INLINE void WdgTitleSetTitleTextVectorFontSize
(
    IWidget                 *pWDGTitle,
    u32						nSize
)
{
#ifdef __FEATURE_VECTOR_FONT__
	if(FONTBASE_IsVectorFontExist())
	{
		WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_TITLETXT_FONT_CATE, (u32)FONT_CAT_VECTOR);
		WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_TITLETXT_FONT_SIZE, (u32)nSize);
	}
#endif
}


/** WdgTitleSetTitleTextFontSize
* @brief        set title text font size
*
* @param[in]    pWDGTitle           Pointer to the Title widget
* @param[in]    nFontSize      vector font size
*
* @retval       None
*
*/
__INLINE void WdgTitleSetTitleTextFontSize
(
    IWidget                 *pWDGTitle,
    u32						nFontSize
)
{
    WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_TITLETXT_FONT_SIZE, (u32)nFontSize);
}

/** WdgTitleSetTitleTextFontType
* @brief        set title text font type
*
* @param[in]    pWDGTitle           Pointer to the Title widget
* @param[in]    nTitleTextFontType  The value of Title text Font Type
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTitleSetTitleTextFontType
(
    IWidget               *pWDGTitle,
    FontType_t            nTitleTextFontType
)
{
    return WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_TITLETXT_FONT_TYPE, (u32)nTitleTextFontType);
}

/** WdgTitleSetTitleTextFGColor
* @brief        set title text foreground color
*
* @param[in]    pWDGTitle         Pointer to the Title widget
* @param[in]    nTitleTextFGColor Title text FG Color
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTitleSetTitleTextFGColor
(
    IWidget                 *pWDGTitle,
    RGBColor_t              nTitleTextFGColor
)
{
    return WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_TITLETXT_FG_COLOR, (u32)nTitleTextFGColor);
}

/** WdgTitleSetTitleTextOutlineColor
* @brief        set text outline color
*
* @param[in]    pWDGTitle               Pointer to the Title widget
* @param[in]    nTitleTextOutlineColor  Title text Outline Color
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTitleSetTitleTextOutlineColor
(
    IWidget                 *pWDGTitle,
    RGBColor_t              nTitleTextOutlineColor
)
{
    return WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_TITLETXT_OUTLINE_COLOR, (u32)nTitleTextOutlineColor);
}

/** WdgTitleSetSmsTextFontCategory
* @brief        set sms text font category
*
* @param[in]    pWDGTitle      Pointer to the Title widget
* @param[in]    nFontSize      font category
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTitleSetSmsTextFontCategory
(
    IWidget                 *pWDGTitle,
    FontCategory_t			FC
)
{
    return WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_SMSTXT_FONT_CATE, (u32)FC);
}

__INLINE void WdgTitleSetSmsTextVectorFontSize
(
    IWidget                 *pWDGTitle,
    u32						nSize
)
{
#ifdef __FEATURE_VECTOR_FONT__
	if (FONTBASE_IsVectorFontExist())
	{
		WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_SMSTXT_FONT_CATE, (u32)FONT_CAT_VECTOR);
		WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_SMSTXT_FONT_SIZE, (u32)nSize);
	}
#endif
}

/** WdgTitleSetSmsTextFontSize
* @brief        set sms text font size
*
* @param[in]    pWDGTitle      Pointer to the Title widget
* @param[in]    nFontSize      vector font size
*
* @retval       None
*
*/
__INLINE void WdgTitleSetSmsTextFontSize
(
    IWidget                 *pWDGTitle,
    u32						nFontSize
)
{
    WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_SMSTXT_FONT_SIZE, (u32)nFontSize);
}

/** WdgTitleSetSmsTextFontType
* @brief        set sms text font type
*
* @param[in]    pWDGTitle         Pointer to the Title widget
* @param[in]    nFontType         The font type
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTitleSetSmsTextFontType
(
    IWidget                 *pWDGTitle,
    FontType_t              nFontType
)
{
    return WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_SMSTXT_FONT_TYPE, (u32)nFontType);
}

/** WdgTitleSetSmsTextFGColor
* @brief        set sms text foreground color
*
* @param[in]    pWDGTitle         Pointer to the Title widget
* @param[in]    nSmsTextFGColor   Sms text FG Color
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTitleSetSmsTextFGColor
(
    IWidget             *pWDGTitle,
    RGBColor_t          nSmsTextFGColor
)
{
    return WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_SMSTXT_FG_COLOR, (u32)nSmsTextFGColor);
}

/** WdgTitleSetSmsTextOutlineColor
* @brief        set sms text outline color
*
* @param[in]    pWDGTitle            Pointer to the Title widget
* @param[in]    nSmsTextOutlineColor The sms text outline color
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTitleSetSmsTextOutlineColor
(
    IWidget                 *pWDGTitle,
    RGBColor_t              nSmsTextOutlineColor
)
{
    return WdgCommonSetProperty(pWDGTitle, PROP_TITLE_WDG_SMSTXT_OUTLINE_COLOR, (u32)nSmsTextOutlineColor);
}

/** WdgTitleSetAsTitle
* @brief        Set to be a Title to the child widget; the Title is combining with the child widget
*               Ex, Set to an abscontainer/text widget, the Title will be above the abscontainer/text widget.
*
* @param[in]    pWDGTitle     The Title widget
* @param[out]   pChild        The widget which is combining with the Title, Ex, an abscontainer/text widget
*
* @retval       None
*
*/
void WdgTitleSetAsTitle
(
    IWidget                 *pWDGTitle,
    IWidget                 *pChild
);
/*=============================================================*/
/** WdgTitleGetImageData
* @brief        Get image data for title widget.
*
* @param[in]    pWDGTitle       Pointer to the Title widget
*
* @retval       IImage          Success
* @retval       NULL            Failed
*
*/
IImage* WdgTitleGetImageData
(
    IWidget                 *pWDGTitle
);

/** WdgTitleGetVisible
* @brief        Get the title line visibility
*
* @param[in]    pWDGTitle         Pointer to the Title widget
*
* @retval        Visible
*
*/
boolean WdgTitleGetVisible
(
    IWidget                 *pWDGTitle
);

/** WdgTitleGetLayout
* @brief        Get the visibilities of elements(ex, Title Icon, Title Image...) in title widget.
*
* @param[in]    pWDGTitle         Pointer to the Title widget
* @param[out]   pLayout           The pointer of layout item visibilities
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__INLINE MAE_Ret WdgTitleGetLayout
(
    IWidget                 *pWDGTitle,
    WdgTitleStyle_t         *pLayout
)
{
    return WdgCommonGetProperty(pWDGTitle, PROP_TITLE_WDG_LAYOUT, (u32*)pLayout);
}

/** WdgTitleGetObj
* @brief        Get the widget from this Title; if the Title is combining with the widget
*               Ex, Set to a abscontainer/text widget, the Title will be above the abscontainer/text widget.
*                   Then you can get abscontainer/text widget from the Title.
*
* @param[in]    pWDGTitle   The Title widget which want to be set
*
* @retval       IWidget*    pChild    The widget which is combining with the Title
*
*/
IWidget* WdgTitleGetObj
(
    IWidget               *pWDGTitle
);

/** WdgTitleRegisterDataChangeCb
* @brief        Register data change callback; CB will be triggered while data changed.
*
* @param[in]    pWDGTitle       The Title widget which want to set callback
* @param[in]    pfn             callback function
* @param[in]    pUserData        User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTitleRegisterDataChangeCb
(
    IWidget                         *pWDGTitle,
    PfnWdgTitleWidgetDataChange  pfn,
    void                            *pUserData
);

/** WdgTitleRegisterAPIconPressCb
* @brief        Register data change callback; CB will be triggered while ap icon be pressed.
*
* @param[in]    pWDGTitle       The Title widget which want to set callback
* @param[in]    pfn             callback function
* @param[in]    pUserData        User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTitleRegisterAPIconPressCb
(
    IWidget                       *pWDGTitle,
    PfnWdgTitleWidgetAPIconPress  pfn,
    void                          *pUserData
);

/** WdgTitleRegisterInputIconPressCb
* @brief        Register data change callback; CB will be triggered while Input icon be pressed.
*
* @param[in]    pWDGTitle       The Title widget which want to set callback
* @param[in]    pfn             callback function
* @param[in]    pUserData        User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgTitleRegisterInputIconPressCb
(
    IWidget                       *pWDGTitle,
	PfnWdgTitleWidgetInputIconPress  pfn,
	void                          *pUserData
);

/** WdgTitleDeregisterDataChangeCb
* @brief        Deregister data change callback; CB will be triggered while data changed.
*
* @param[in]    pWDGTitle       The Title widget which want to set callback
* @param[in]    pfn             callback function
* @param[in]    pUserData        User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTitleDeregisterDataChangeCb
(
    IWidget                         *pWDGTitle,
    PfnWdgTitleWidgetDataChange  pfn,
    void                            *pUserData
);

/** WdgTitleDeregisterAPIconPressCb
* @brief        Deregister data change callback; CB will be triggered while ap icon be pressed.
*
* @param[in]    pWDGTitle       The Title widget which want to set callback
* @param[in]    pfn             callback function
* @param[in]    pUserData        User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgTitleDeregisterAPIconPressCb
(
    IWidget                       *pWDGTitle,
    PfnWdgTitleWidgetAPIconPress  pfn,
    void                          *pUserData
);


#endif //__MMI_WDG_TITLE_H__
/*=============================================================*/
// end of file
