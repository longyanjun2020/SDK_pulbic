/**
 * @file    mmi_wdg_doubleitem.h
 * @version $Id: mmi_wdg_doubleitem.h 34112 2009-06-23 02:31:10Z jorena.ku $
 * Support class id:1.CLSID_DOUBLE_TEXT_WIDGET,	the class id of a double text widget
 *					2.CLSID_TEXT_DATE_WIDGET,	the class id of a text date widget
 *					3.CLSID_TEXT_TIME_WIDGET,	the class id of a text time widget
 *					4.CLSID_IT_STEXT_WIDGET,
 * 					5.CLSID_IT_SIT_WIDGET,
 *                  6.CLSID_IT_STI_WIDGET,     
 *					7.CLSID_TEXT_INPUT_WIDGET,
 *					8.CLSID_TEXT_LINE2INFO_WIDGET,
 *
 *
 *  CLSID_DOUBLE_TEXT_WIDGET:
 *  ------------------------------------------
 *  | -------------------------------------- |
 *  | | Text                               | |
 *  | -------------------------------------- |
 *  | | Text                               | |
 *  | -------------------------------------- |
 *  ------------------------------------------
 *  typedef struct {
 *  	MAE_WChar		*pITextLine1;		///Pointer to UCS2 text buffer.
 *	    MAE_WChar		*pITextLine2;		///Pointer to UCS2 text buffer.
 *  }DoubleTextInfo;
 *
 *
 *  CLSID_TEXT_DATE_WIDGET
 *  ------------------------------------------
 *  | -------------------------------------- |
 *  | | Text                               | |
 *  | -------------------------------------- |
 *  | | 2007/10/10                         | |
 *  | -------------------------------------- |
 *  ------------------------------------------
 *  typedef struct {            
 *		MAE_WChar 		 *pITextLine1;
 *		MAE_DateTime_t	 *pIDateLine2;
 *	}TextDateInfo;            
 *
 *   
 *	CLSID_TEXT_TIME_WIDGET
 *  ------------------------------------------
 *  | -------------------------------------- |
 *  | | Text                               | |
 *  | -------------------------------------- |
 *  | | 15:31                              | |
 *  | -------------------------------------- |
 *  ------------------------------------------
 *  typedef struct {            
 *		MAE_WChar 		 *pITextLine1;
 *		MAE_DateTime_t	 *pITimeLine2;
 *	}TextTimeInfo;     
 *	
 *
 *  CLSID_IT_STEXT_WIDGET
 *  ------------------------------------------
 *  | -------------------------------------- |
 *  | | IMG |Text                          | |
 *  | -------------------------------------- |
 *  | space |Text                          | |
 *  | -------------------------------------- |	
 *  ------------------------------------------
 *  typedef struct {            
 *		ImageTextInfo	*pIMGTextLine1;
 *		MAE_WChar 		*pTextLine2;
 *	}ITSTextInfo;
 *
 *
 *  CLSID_IT_SINPUT_WIDGET
 *  ------------------------------------------
 *  | -------------------------------------- |
 *  | | IMG |Text                          | |
 *  | -------------------------------------- |
 *  | space |Input                         | |
 *  | -------------------------------------- |	
 *  ------------------------------------------
 *  typedef struct {            
 *		ImageTextInfo	*pIMGTextLine1;
 *		MAE_WChar 		*pTextLine2;
 *	}ITSInputInfo;
 *
 *
 *  CLSID_IT_SIT_WIDGET
 *  ------------------------------------------
 *  | -------------------------------------- |
 *  | | IMG |Text                          | |
 *  | -------------------------------------- |
 *  | space | IMG |Text                    | |
 *  | -------------------------------------- |
 *  ------------------------------------------
 *  typedef struct {            
 *		ImageTextInfo 	*pIMGTextLine1;
 *		ImageTextInfo 	*pIMGTextLine2;
 *	}ITSITInfo;
 *
 *
 *  CLSID_IT_STI_WIDGET
 *  ------------------------------------------
 *  | -------------------------------------- |
 *  | | IMG |Text                          | |
 *  | -------------------------------------- |
 *  | space |Text                      |IMG| |
 *  | -------------------------------------- |
 *  ------------------------------------------
 *  typedef struct {            
 *		ImageTextInfo 	    *pIMGTextLine1;
 *		TextImageInfo 	*pTextIMGLine2;
 *	}ITSTIInfo;
 *
 *
 *   CLSID_TEXT_INPUT_WIDGET
 *  ------------------------------------------
 *  | -------------------------------------- |
 *  | | Text                               | |
 *  | -------------------------------------- |
 *  | | 1231                              | |
 *  | -------------------------------------- |
 *  ------------------------------------------
 *
 * typedef struct {			  
 *	 	MAE_WChar		 *pITextLine1;		///Pointer to UCS2 text buffer.			 
 *	 	MAE_WChar		 *pITextLine2;		///Pointer to UCS2 text buffer.	  
 *  }TextInputInfo; 
 *
 *
 *   CLSID_TEXT_IP_WIDGET
 *  ------------------------------------------
 *  | -------------------------------------- |
 *  | | Text                               | |
 *  | -------------------------------------- |
 *  | | 255.255.255.255                    | |
 *  | -------------------------------------- |
 *  ------------------------------------------
 *
 * typedef struct {			  
 *	 	MAE_WChar		 *pITextLine1;		///Pointer to UCS2 text buffer.			 
 *      u32				 *pIIPLine2;		///Pointer to buffer of IP data.      
 *  }TextIPInfo; 
 *
 *
 *  CLSID_TEXT_LINE2INFO_WIDGET
 *  ------------------------------------------
 *  | -------------------------------------- |
 *  | |Text                                | |
 *  | -------------------------------------- |
 *  | |space|Theme Text(with BGcolor)|space| |
 *  | -------------------------------------- |
 *  ------------------------------------------
 *
 *  typedef struct {
 *  	MAE_WChar		*pITextLine1;		///Pointer to UCS2 text buffer.
 *	    MAE_WChar		*pITextLine2;		///Pointer to UCS2 text buffer.
 *  }DoubleTextInfo;
 *
 */
 
#ifndef __MMI_WDG_DOUBLEITEM_H__
#define __MMI_WDG_DOUBLEITEM_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_textmodel.h"
#include "mmi_mae_common_def.h"//for data & time widget
#include "mmi_wdg_image_text_image.h"//
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/** DoubleTextInfo_st
*
* @brief    pITextLine1:        Pointer to UCS2 text buffer.
*           pITextLine2:        Pointer to UCS2 text buffer.
*
*/
 typedef struct {
	MAE_WChar		*pITextLine1;	
	MAE_WChar		*pITextLine2;
}DoubleTextInfo;
typedef DoubleTextInfo DoubleTextInfo_st;

/** TextDateInfo_st
*
* @brief    pITextLine1:        Pointer to UCS2 text buffer.
*           pIDateLine2:        Pointer to buffer of MAE_DateTime_t.  
*
*/
 typedef struct {            
	MAE_WChar		*pITextLine1;	
	MAE_DateTime_t	*pIDateLine2;	
}TextDateInfo;
typedef TextDateInfo TextDateInfo_st;


/** TextTimeInfo_st
*
* @brief    pITextLine1:        Pointer to UCS2 text buffer.
*           pITimeLine2:        Pointer to buffer of MAE_DateTime_t.
*
*/
 typedef struct {            
	MAE_WChar		*pITextLine1;	   
	MAE_DateTime_t	*pITimeLine2;   
}TextTimeInfo;
typedef TextTimeInfo TextTimeInfo_st;

/** TextInputInfo_st
*
* @brief    pITextLine1:        Pointer to UCS2 text buffer.
*           pITextLine2:        Pointer to UCS2 text buffer.      
*
*/
 typedef struct {            
	MAE_WChar		*pITextLine1;          
	MAE_WChar		*pITextLine2;    
}TextInputInfo;
typedef TextInputInfo TextInputInfo_st;

/** TextIPInfo_st
*
* @brief    pITextLine1:        Pointer to UCS2 text buffer.
*           pIIPLine2:          Pointer to buffer of IP data.
*
*/
 typedef struct {            
	MAE_WChar		*pITextLine1;         
	u32				*pIIPLine2;     
}TextIPInfo;
typedef TextIPInfo TextIPInfo_st;

/** ITSTextInfo_st
*
* @brief    pIMGTextLine1:        Pointer to a buffer Image Text widget.
*           pTextLine2:           Pointer to UCS2 text buffer. 
*
*/
 typedef struct {            
	ImageTextInfo	*pIMGTextLine1;	          
	MAE_WChar		*pTextLine2;    
}ITSTextInfo;
typedef ITSTextInfo ITSTextInfo_st;

/** ITSInputInfo_st
*
* @brief    pIMGTextLine1:        Pointer to a buffer Image Text widget.
*           pTextLine2:           Pointer to UCS2 text buffer. 
*
*/
typedef struct {            
 	ImageTextInfo	*pIMGTextLine1;	
 	MAE_WChar 		*pTextLine2;	
 }ITSInputInfo;
typedef ITSInputInfo ITSInputInfo_st;

/** ITSITInfo_st
*
* @brief    pIMGTextLine1:        Pointer to a buffer Line1 Image Text widget.   
*           pIMGTextLine2:        Pointer to a buffer Line2 Image Text widget.
*
*/
 typedef struct {            
	ImageTextInfo	*pIMGTextLine1;	 
	ImageTextInfo 	*pIMGTextLine2;	
}ITSITInfo;
typedef ITSITInfo ITSITInfo_st;

/** ITSTIInfo_st
*
* @brief    pIMGTextLine1:        Pointer to a buffer Line1 Image Text widget.  
*           pTexIMGtLine2:        Pointer to a buffer Line2 Text Image widget.
*
*/
typedef struct {            
	ImageTextInfo	 *pIMGTextLine1;	
	TextImageInfo    *pTexIMGtLine2;	
}ITSTIInfo;
typedef ITSTIInfo ITSTIInfo_st;


/** DoubleItemInfo
*
* @brief    pLine1:        Pointer to a buffer for data of Line1 
*           pLine2:        Pointer to a buffer for data of Line2 
*
*/
typedef struct {
	void *pLine1;
	void *pLine2;
} DoubleItemInfo;

/** DoubleItemPaddingSize_t
*
* @brief    nLeft:         
*           nRight:         
*           nTop:         
*           nDown:
*
*/
typedef struct {
	u32 nLeft;
	u32 nRight;
	u32 nTop;
	u32 nDown;
} DoubleItemPaddingSize_t;


typedef u8 DoubleItemStyle_e;
enum{
    DOUBLEITEM_STYLE_DOUBLE_TEXT,
    DOUBLEITEM_STYLE_TEXT_LINE2INFO,
    DOUBLEITEM_STYLE_TEXT_DATE,
    DOUBLEITEM_STYLE_TEXT_TIME,
    DOUBLEITEM_STYLE_TEXT_INPUT,
    DOUBLEITEM_STYLE_TEXT_IP,
    DOUBLEITEM_STYLE_IT_SINPUT,
    DOUBLEITEM_STYLE_IT_STEXT,
    DOUBLEITEM_STYLE_IT_SIT,
    DOUBLEITEM_STYLE_IT_STI
};

/** WdgDoubleItemDBText_t
*
* @brief    For setting data by ID to DOUBLEITEM_STYLE_DOUBLE_TEXT or DOUBLEITEM_STYLE_TEXT_LINE2INFO or DOUBLEITEM_STYLE_TEXT_INPUT.
*
*/
typedef struct {
   u32  nUpStrID;               // Up Item text ID
   u32  nDownStrID;             // Down Item text ID
}WdgDoubleItemDBText_t;


/** WdgDoubleItemTextTime_t
*
* @brief    For setting data by ID to DOUBLEITEM_STYLE_TEXT_DATE or DOUBLEITEM_STYLE_TEXT_TIME.
*
*/
typedef struct {
   u32  nUpStrID;               // Up Item text ID
   MAE_DateTime_t  tDownTime;   // struct of MAE_DateTime_t.
}WdgDoubleItemTextTime_t;


/** WdgDoubleItemTextIP_t
*
* @brief    For setting data by ID to DOUBLEITEM_STYLE_TEXT_IP.
*
*/
typedef struct {
   u32  nUpStrID;               // Up Item text ID
   u32  *pIP;                   // The IP value, IP value.  ex. 0xFFFFFFFF --> 255.255.255.255   0x04030201 --> 4.3.2.1
}WdgDoubleItemTextIP_t;


/** WdgDoubleItemTIT_t
*
* @brief    For setting data by ID to DOUBLEITEM_STYLE_IT_SINPUT or DOUBLEITEM_STYLE_IT_STEXT.
*
*/
typedef struct {
   u32  nUpStrID;               // Up Item text ID
   u32  nUpImgID;               // Up Item image ID
   u32  nDownStrID;             // Down Item text ID
}WdgDoubleItemTIT_t;


/** WdgDoubleItemDBTextImage_t
*
* @brief    For setting data by ID to DOUBLEITEM_STYLE_IT_SIT or DOUBLEITEM_STYLE_IT_STI.
*
*/
typedef struct {
   u32  nUpStrID;               // Up Item text ID
   u32  nUpImgID;               // Up Item image ID
   u32  nDownStrID;             // Down Item text ID
   u32  nDownImgID;             // Down Item image ID
}WdgDoubleItemDBTextImage_t;

/*=============================================================*/
// functions
/*=============================================================*/
/** PfnWdgDoubleItemDataChange
* @brief      CB register by "WdgDoubleItemRegisterDataChangeCb"
*             and will be trigger when the data of widget is changed
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  dwParam       The data word param (NOT use now)
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgDoubleItemDataChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
/*=============================================================*/
// functions
/*=============================================================*/
/** WdgDoubleItemCreateForWnd
* @brief        DoubleItem widget create function for Window
*
* @param[in]    hWin             The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pSize               A pointer of widget size; NULL means default value.
* @param[in]    nWidgetID           The widget unique ID of window
* @param[in]    eDoubleItemStyle    DoubleItemWidget initial style
*
* @retval       The pointer of DoubleItem           Success.
* @retval       NULL                                Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgDoubleItemCreateForWnd
(
    HWIN         hWin,
    Pos_t               *pPos,
    WidgetSize_t        *pSize,
    u16                 nWidgetID,
    DoubleItemStyle_e   eDoubleItemStyle
);

/*=============================================================*/
/** WdgDoubleItemCreate
* @brief        Create DoubleItem widget
*
* @param[in]    hWin             The window handle
* @param[in]    eDoubleItemStyle    DoubleItemWidget initial style
*
* @retval       The pointer of DoubleItem   Success.
* @retval       NULL                        Failed.
*
*/
__SLDPM_FREE__ IWidget* WdgDoubleItemCreate
(
    HWIN         hWin,
    DoubleItemStyle_e   eDoubleItemStyle
);

/** WdgDoubleItemDBTextSetData
* @brief        Set display data for DOUBLEITEM_STYLE_DOUBLE_TEXT or DOUBLEITEM_STYLE_TEXT_LINE2INFO or DOUBLEITEM_STYLE_TEXT_INPUT style DoubleItem widget.
*               Specific data for DoubleItem widget.
*
* @param[in]    pWDGDoubleItem    Pointer to the DoubleItem widget
* @param[in]    pDispData         Display data of DoubleItem Widget, refer to DoubleTextInfo_st.
* @param[in]    pfFree            Free CB function for free data allocate by User while widget destroy.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgDoubleItemDBTextSetData
(
    IWidget                *pWDGDoubleItem,
    DoubleTextInfo_st      *pDispData,
    PfnDataFree            pfFree
);

/** WdgDoubleItemDBTextSetDataByID
* @brief        Set display data by resource ID for DOUBLEITEM_STYLE_DOUBLE_TEXT or DOUBLEITEM_STYLE_TEXT_LINE2INFO or DOUBLEITEM_STYLE_TEXT_INPUT style DoubleItem widget.
*               Specific data for DoubleItem widget.
*
* @param[in]    pWDGDoubleItem    Pointer to the DoubleItem widget
* @param[in]    pDispData         Display data of DoubleItem Widget, refer to WdgDoubleItemDBText_t.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgDoubleItemDBTextSetDataByID
(
    IWidget                 *pWDGDoubleItem,
    WdgDoubleItemDBText_t   *pDispData
);

/** WdgDoubleItemTextDateaSetData
* @brief        Set display data for DOUBLEITEM_STYLE_TEXT_DATE or DOUBLEITEM_STYLE_TEXT_TIME style DoubleItem widget.
*               Specific data for DoubleItem widget.
*
* @param[in]    pWDGDoubleItem    Pointer to the DoubleItem widget
* @param[in]    pDispData         Display data of DoubleItem Widget, refer to TextDateInfo_st.
* @param[in]    pfFree            Free CB function for free data allocate by User while widget destroy.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgDoubleItemTextDateSetData
(
    IWidget                 *pWDGDoubleItem,
    TextDateInfo_st         *pDispData,
    PfnDataFree             pfFree
);

/** WdgDoubleItemTextDateSetDataByID
* @brief        Set display data by resource ID for DOUBLEITEM_STYLE_TEXT_DATE or DOUBLEITEM_STYLE_TEXT_TIME style DoubleItem widget.
*               Specific data for DoubleItem widget.
*
* @param[in]    pWDGDoubleItem    Pointer to the DoubleItem widget
* @param[in]    pDispData         Display data of DoubleItem Widget, refer to WdgDoubleItemTextTime_t.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgDoubleItemTextDateSetDataByID
(
    IWidget                 *pWDGDoubleItem,
    WdgDoubleItemTextTime_t *pDispData
);

/** WdgDoubleItemTextIPSetData
* @brief        Set display data for DOUBLEITEM_STYLE_TEXT_IP style DoubleItem widget.
*               Specific data for DoubleItem widget.
*
* @param[in]    pWDGDoubleItem    Pointer to the DoubleItem widget
* @param[in]    pDispData         Display data of DoubleItem Widget, refer to TextIPInfo_st.
* @param[in]    pfFree            Free CB function for free data allocate by User while widget destroy.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgDoubleItemTextIPSetData
(
    IWidget                 *pWDGDoubleItem,
    TextIPInfo_st           *pDispData,
    PfnDataFree             pfFree
);

/** WdgDoubleItemTextIPSetDataByID
* @brief        Set display data by resource ID for DOUBLEITEM_STYLE_TEXT_IP style DoubleItem widget.
*               Specific data for DoubleItem widget.
*
* @param[in]    pWDGDoubleItem    Pointer to the DoubleItem widget
* @param[in]    pDispData         Display data of DoubleItem Widget, refer to WdgDoubleItemTextIP_t.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgDoubleItemTextIPSetDataByID
(
    IWidget                 *pWDGDoubleItem,
    WdgDoubleItemTextIP_t   *pDispData
);

/** WdgDoubleItemITSTextSetData
* @brief        Set display data for DOUBLEITEM_STYLE_IT_SINPUT or DOUBLEITEM_STYLE_IT_STEXT style DoubleItem widget.
*               Specific data for DoubleItem widget.
*
* @param[in]    pWDGDoubleItem    Pointer to the DoubleItem widget
* @param[in]    pDispData         Display data of DoubleItem Widget, refer to ITSTextInfo_st.
* @param[in]    pfFree            Free CB function for free data allocate by User while widget destroy.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgDoubleItemITSTextSetData
(
    IWidget                 *pWDGDoubleItem,
    ITSTextInfo_st          *pDispData,
    PfnDataFree             pfFree
);

/** WdgDoubleItemITSTextSetDataByID
* @brief        Set display data by resource ID for DOUBLEITEM_STYLE_IT_SINPUT or DOUBLEITEM_STYLE_IT_STEXT style DoubleItem widget.
*               Specific data for DoubleItem widget.
*
* @param[in]    pWDGDoubleItem    Pointer to the DoubleItem widget
* @param[in]    pDispData         Display data of DoubleItem Widget, refer to WdgDoubleItemTIT_t.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgDoubleItemITSTextSetDataByID
(
    IWidget                 *pWDGDoubleItem,
    WdgDoubleItemTIT_t      *pDispData
);

/** WdgDoubleItemITSITSetData
* @brief        Set display data for DOUBLEITEM_STYLE_IT_SIT style DoubleItem widget.
*               Specific data for DoubleItem widget.
*
* @param[in]    pWDGDoubleItem    Pointer to the DoubleItem widget
* @param[in]    pDispData         Display data of DoubleItem Widget, refer to ITSITInfo_st.
* @param[in]    pfFree            Free CB function for free data allocate by User while widget destroy.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgDoubleItemITSITSetData
(
    IWidget                 *pWDGDoubleItem,
    ITSITInfo_st            *pDispData,
    PfnDataFree             pfFree
);

/** WdgDoubleItemITSITSetDataByID
* @brief        Set display data by resource ID for DOUBLEITEM_STYLE_IT_SIT style DoubleItem widget.
*               Specific data for DoubleItem widget.
*
* @param[in]    pWDGDoubleItem    Pointer to the DoubleItem widget
* @param[in]    pDispData         Display data of DoubleItem Widget, refer to WdgDoubleItemDBTextImage_t.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgDoubleItemITSITSetDataByID
(
    IWidget                     *pWDGDoubleItem,
    WdgDoubleItemDBTextImage_t  *pDispData
);

/** WdgDoubleItemITSTISetData
* @brief        Set display data for DOUBLEITEM_STYLE_IT_STI style DoubleItem widget.
*               Specific data for DoubleItem widget.
*
* @param[in]    pWDGDoubleItem    Pointer to the DoubleItem widget
* @param[in]    pDispData         Display data of DoubleItem Widget, refer to ITSTIInfo_st.
* @param[in]    pfFree            Free CB function for free data allocate by User while widget destroy.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgDoubleItemITSTISetData
(
    IWidget                 *pWDGDoubleItem,
    ITSTIInfo_st            *pDispData,
    PfnDataFree             pfFree
);

/** WdgDoubleItemITSTISetDataByID
* @brief        Set display data by resource ID for DOUBLEITEM_STYLE_IT_STI style DoubleItem widget.
*               Specific data for DoubleItem widget.
*
* @param[in]    pWDGDoubleItem    Pointer to the DoubleItem widget
* @param[in]    pDispData         Display data of DoubleItem Widget, refer to WdgDoubleItemDBTextImage_t.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgDoubleItemITSTISetDataByID
(
    IWidget                     *pWDGDoubleItem,
    WdgDoubleItemDBTextImage_t  *pDispData
);

/** WdgDoubleItemSetDisableDownWidgetBG
* @brief         Set enable or disable down widget BG for "DOUBLEITEM_STYLE_TEXT_LINE2INFO"
*
* @param[in]     pWDGDoubleItem         The pointer of IWidget interface object
* @param[in]     bDisableLine2TextBg    TRUE: when Line2 Text length is 0, the BG will be disabled. when > 0, the BG will be enabled.
                                        FALSE: the Line2 text BG will always enable
*
* @retval        none
*
*/
__INLINE void WdgDoubleItemSetDisableDownWidgetBG
(
    IWidget                 *pWDGDoubleItem,
    boolean                 bDisableLine2TextBg
)
{
    WdgCommonSetProperty(pWDGDoubleItem, PROP_DOUBLEITEM_WDG_DISABLE_DOWNWDG_BG, (u32)bDisableLine2TextBg);
}

/** WdgDoubleItemSetFocusOnUpperWidget
* @brief         Set DoubleItem widget focus on upper widget
*
* @param[in]     pWDGDoubleItem         The pointer of IWidget interface object
* @param[in]     bFoucsOnUpperWidget    TRUE: the double item widget should focus on the upper widget, when it on focused.
*                                       FALSE: the double item widget should focus on the downh widget, when it on focused
*
* @retval        none
*
*/
__INLINE void WdgDoubleItemSetFocusOnUpperWidget
(
    IWidget                 *pWDGDoubleItem,
    boolean                 bFoucsOnUpperWidget
)
{
    WdgCommonSetProperty(pWDGDoubleItem, PROP_DOUBLEITEM_WDG_FOCUS_ON_UPPERWIDGET, (u32)bFoucsOnUpperWidget);
}

/** WdgDoubleItemSetSlideOnOff
* @brief         Turn On/Off The Text sliding animation.
*                (Text sliding : If the width of string is bigger than the width of width,
*                string would slide for seeing all the text)
*
* @param[in]     pWDGDoubleItem    The pointer of IWidget interface object
* @param[in]     bSliderOnOff      DoubleItem widget slide on / off, on = TRUE, off = FALSE
*
* @retval        none
*
*/
__INLINE void WdgDoubleItemSetSlideOnOff
(
    IWidget                 *pWDGDoubleItem,
    boolean                 bSliderOnOff
)
{
    WdgCommonSetProperty(pWDGDoubleItem, PROP_TEXT_WDG_SLIDE_ON_OFF, (u32)bSliderOnOff);
}

/** WdgDoubleItemSetTextOutlineColor
* @brief         Set DoubleItem widget text outline color
*
* @param[in]     pWDGDoubleItem    The pointer of IWidget interface object
* @param[in]     tTextOutlineColor The text outline color of DoubleItem widget
*
* @retval        none
*
*/
__INLINE void WdgDoubleItemSetTextOutlineColor
(
    IWidget                 *pWDGDoubleItem,
    RGBColor_t              tTextOutlineColor
)
{
    WdgCommonSetProperty(pWDGDoubleItem, PROP_WDG_TEXT_OUTLINE_COLOR, (u32)tTextOutlineColor);
}


/** WdgCommonPickSetHighLighted
* @brief        Set enable/disable highlight of DoubleItem widget
*
* @param[in]    pWDGDoubleItem      The DoubleItem widget which want to be set
* @param[in]    bEnable             Enable/Disable highlight of DoubleItem widget
*
* @retval       none
*
*/
__INLINE void WdgDoubleItemSetHighlighted
(
    IWidget                 *pWDGDoubleItem,
    boolean                 bEnable
)
{
    WdgCommonSetProperty(pWDGDoubleItem, PROP_WDG_HIGHLIGHTED, (u32)bEnable);
}

/** WdgDoubleItemSetHighlightedTextOutlineColor
* @brief         Set DoubleItem widget highlighted text outline color
*
* @param[in]     pWDGDoubleItem                  The pointer of IWidget interface object
* @param[in]     tHighlightedTextOutlineColor    The highlighted text outline color of DoubleItem widget
*
* @retval        none
*
*/
__INLINE void WdgDoubleItemSetHighlightedTextOutlineColor
(
    IWidget                 *pWDGDoubleItem,
    RGBColor_t              tHighlightedTextOutlineColor
)
{
    WdgCommonSetProperty(pWDGDoubleItem, PROP_WDG_HIGHLIGHT_TEXT_OUTLINE_COLOR, (u32)tHighlightedTextOutlineColor);
}

/** WdgDoubleItemSetEnableAnimate
* @brief        Turn on/off animation to widget
*
* @param[in]    pWDGDoubleItem    Pointer to the DoubleItem widget
* @param[in]    bEnableAnimate    TRUE, turn on,
*                                 FALSE, turn off.
*
* @retval       none
*
*/
__INLINE void WdgDoubleItemSetEnableAnimate
(
    IWidget                 *pWDGDoubleItem,
    boolean                 bEnableAnimate
)
{
    WdgCommonSetProperty(pWDGDoubleItem, PROP_WDG_ENABLE_ANIMATE, (u32)bEnableAnimate);
}

/** WdgDoubleItemGetObjUpperWdg
* @brief         Get Upper widget
*
* @param[in]     pWDGDoubleItem    The pointer of IWidget interface object
*
* @retval        UpperWidget
*
*/
__SLDPM_FREE__ IWidget* WdgDoubleItemGetObjUpperWdg
(
    IWidget                 *pWDGDoubleItem
);

/** WdgDoubleItemGetObjDownWdg
* @brief         Get Upper widget
*
* @param[in]     pWDGDoubleItem    The pointer of IWidget interface object
*
* @retval        DownWidget
*
*/
__SLDPM_FREE__ IWidget* WdgDoubleItemGetObjDownWdg
(
    IWidget                 *pWDGDoubleItem
);

/** WdgDoubleItemRegisterDataChangeCb
* @brief         Register data change callback; CB will be triggered while data changed.
*
* @param[in]     pWDGDoubleItem   The DoubleItem widget which want to set callback
* @param[in]     pfn              callback function
* @param[in]     pUserData         User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgDoubleItemRegisterDataChangeCb
(
    IWidget                         *pWDGDoubleItem,
    PfnWdgDoubleItemDataChange   pfn,
    void                            *pUserData
);

/** WdgDoubleItemDeregisterDataChangeCb
* @brief         Deregister data change callback; CB will be triggered while data changed.
*
* @param[in]     pWDGDoubleItem   The DoubleItem widget which want to deregister callback
* @param[in]     pfn              callback function
* @param[in]     pUserData         User Data can be got when CB trigger.
*
* @retval        MAE_RET_SUCCESS   Success
* @retval        others            Failed
*
*/
MAE_Ret WdgDoubleItemDeregisterDataChangeCb
(
    IWidget                         *pWDGDoubleItem,
    PfnWdgDoubleItemDataChange   pfn,
    void                            *pUserData
);

#endif //__MMI_WDG_DOUBLEITEM_H__
/*=============================================================*/
// end of file
