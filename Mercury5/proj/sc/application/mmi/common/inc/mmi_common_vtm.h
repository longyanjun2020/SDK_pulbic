
#ifndef __MMI_COMMON_VTM_PRIV_H__
#define __MMI_COMMON_VTM_PRIV_H__
#include "mmi_wdg_headers.h"

//////////////////////////////////////////////////////////////////////////
#ifdef __APP_MMI_SMALLROM__
#define __COMMON_DIALOG_SMALLROM__
#endif	// __APP_MMI_SMALLROM__

#ifdef __APP_MMI_SMALLROM__
#define __CONTENT_SMALLROM__
#endif	// __APP_MMI_SMALLROM__

//////////////////////////////////////////////////////////////////////////
/*=============================================================*/
// Macro definition
/*=============================================================*/

enum //DateInput_enum
{
	DATE_INPUT_TITLE_WDG=TITLE_WDG_ID,
	DATE_INPUT_DATE_WDG=VTM_WDG_START,
#ifdef __WIDGET_DISABLE_FINGERCOMMAND__
	DATE_INPUT_TEXT_WDG,
#endif
}; //DateInput_enum

/** DateInputWdgList_t
*
* @brief    pTitleWdg:       used to get a Title Widget handle.
*              pDateWdg:      used to get a FCDate Widget handle. FCDate is a widget that composed of sevel Ring-List widgets.
*					   Each Ring-List display one of date value, and one of those Ring-List widgets is a focus widget that
*					   can change it's first display index of item when user press up/down navigation keys
*
*/
typedef struct DateInputWdgList
{
	IWidget *pTitleWdg;
	IWidget *pDateWdg;
#ifdef __WIDGET_DISABLE_FINGERCOMMAND__
	IWidget *pTextWdg;
#endif
}DateInputWdgList_t;

/** DateInputData_t
*
* @brief    nTitleImgId:       set the image id that defined in Img_data.h
*              nTitleTxtId:        set the id of text that defined in Mae_textlabel.h
*              nYear:  		      set hour, value is from 70 to 139 (1970 to 2039).
*              nMonth:              set month, value is from 1 to 12.
*		  nDay:        	      set day, value is from 1 to 31.
*/
typedef struct DateInputData
{
	u32 nTitleImgId;
	u32 nTitleTxtId;
	u8 nYear;
	u8 nMonth;
	u8 nDay;
}DateInputData_t;

/** VtmCreateDateInput
* @brief  create a screen with title and FCDate widget.  The date may show system date if the value, assign in DateInputData_t, out of range.
*
*
* @param[in]    hWin        	point to a window handle
* @param[out]  pWdgList         	return the widgets handle if creating success. It includes FCDateWidget and TitleWidget.
* @param[in]    pData 			set the default date. Refer to the sturct DateInputData_t
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
* @Note        The MAE limitation, year rang only 1970~2039
*/
MAE_Ret VtmCreateDateInput(HWIN hWin, DateInputWdgList_t *pWdgList, DateInputData_t *pData);

//////////////////////////////////////////////////////////////////////////
enum //ImageVtmenum
{
	IMG_IMG_WDG=VTM_WDG_START,
}; //ImageVtmenum

/** ImageVtmWdgList_t
*
* @brief    pImgWdg:       A IWidget pointer.  point to a ImageWidget when image created success.
*
*
*/
typedef struct ImageVtmWdgList
{
	IWidget *pImgWdg;
}ImageVtmWdgList_t;

/** ImageVtmData_t
*
* @brief    nImgId:       set the image id that defined in Img_data.h
*
*
*/
typedef struct ImageVtmData
{
	u32 nImgId;
}ImageVtmData_t;

/** VtmCreateImg
* @brief  show a image on screen
*
*
* @param[in]    hWin        	point to a window handle
* @param[out]  pWdgList         	return the widgets handle if creating success
* @param[in]    pData 			set the image id. Refer to the sturct ImageVtmData_t
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed

*
*/
MAE_Ret VtmCreateImg(HWIN hWin, ImageVtmWdgList_t *pWdgList, ImageVtmData_t *pData);

//////////////////////////////////////////////////////////////////////////
enum //InputVtm
{
	INPUT_TITLE_WDG=TITLE_WDG_ID,
	INPUT_SCROLL_WDG=VTM_WDG_START,
	INPUT_INPUT_WDG
}; //InputVtm

/** InputVtmWdgList_t
*
* @brief    pTitleWdg:       used to get a Title Widget handle.
*              pScrollWdg:     used to get a Scroll-bar Widget handle. Scroll-bar widget is a decorator widget,
*					   mainly to enhance the display of some widget (like List widget) to make up for lack of.
*		  pInputWdg:	   used to get a Inuput Widget handle. Input Widget provides not only Date/Time/IP
*					   those fixed format of input methods and also provides other input methods
*					   For example, PIN, SMS, phone numbers, names of persons etc.
*/
typedef struct InputVtmWdgList
{
	IWidget *pTitleWdg;
	IWidget *pScrollWdg;
	IWidget *pInputWdg;
}InputVtmWdgList_t;

/** InputVtmData_t
*
* @brief    nTitleImgId:       set the image id that defined in Img_data.h
*              nTitleTxtId:        set the id of text that defined in Mae_textlabel.h
*              nInputMaxByte:  specify the max of input bytes.
*              bReadOnly:        read only if set true. otherwise, writable.
*
*/
typedef struct InputVtmData
{
	u32 nTitleImgId;
	u32 nTitleTxtId;
	u32 nInputMaxByte;
	boolean bReadOnly;
}InputVtmData_t;

/** VtmCreateInput
* @brief  create a screen that can let user input text by hw/sw keyboard.
*            it supports multi-line input.
*
* @param[in]    hWin        	point to a window handle
* @param[out]  pWdgList         	return the widgets handle if creating success. It includes TitleWidget, ScrollWidget and InputWidget.
* @param[in]    pData 			set the properties of input screen. Refer to the sturct InputVtmData_t
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret VtmCreateInput(HWIN hWin, InputVtmWdgList_t *pWdgList, InputVtmData_t *pData);

//////////////////////////////////////////////////////////////////////////

enum //PromptInput_enum
{
	PROMPT_INPUT_TITLE_WDG=TITLE_WDG_ID,
	PROMPT_INPUT_TXT_WDG=VTM_WDG_START,
	PROMPT_INPUT_INPUT_WDG
}; //PromptInput_enum


/** InputVtmWdgList_t
*
* @brief    pTitleWdg:       used to get a Title Widget handle.
*              pTxtWdg:         used to get a text Widget handle.
*		  pInputWdg:	   used to get a Inuput Widget handle. Input Widget provides not only Date/Time/IP
*					   those fixed format of input methods and also provides other input methods
*					   For example, PIN, SMS, phone numbers, names of persons etc.
*/
typedef struct PromptInputWdgList
{
	IWidget *pTitleWdg;
	IWidget *pTxtWdg;
	IWidget *pInputWdg;
}PromptInputWdgList_t;

/** InputVtmData_t
*
* @brief    nTitleImgId:       set the image id that defined in Img_data.h
*              nTitleTxtId:        set the id of text that defined in Mae_textlabel.h
*              nInputTxtId:      set the id of text that defined in Mae_textlabel.h
*              nInputMaxByte:  specify the max of input bytes..
*
*/
typedef struct PromptInputData
{
	u32 nTitleImgId;
	u32 nTitleTxtId;
	u32 nInputTxtId;
	u32 nInputMaxByte;
}PromptInputData_t;

/** VtmCreatePromptInput
* @brief  create a prompt screen to ask user input something ( for example: pin code )
*
*
* @param[in]    hWin        	point to a window handle
* @param[out]  pWdgList         	return the widgets handle if creating success. It includes TitleWidget, TextWidget and InputWidget.
* @param[in]    pData 			set the properties of prompt screen. Refer to the sturct PromptInputData_t
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret VtmCreatePromptInput(HWIN hWin, PromptInputWdgList_t *pWdgList, PromptInputData_t *pData);

//////////////////////////////////////////////////////////////////////////

enum //TimeInput_enum
{
	TIME_INPUT_TITLE_WDG=TITLE_WDG_ID,
	TIME_INPUT_TIME_WDG=VTM_WDG_START,
#ifdef __WIDGET_DISABLE_FINGERCOMMAND__
	TIME_INPUT_TEXT_WDG,
#endif
}; //TimeInput_enum


/** TimeInputWdgList_t
*
* @brief    pTitleWdg:       used to get a Title Widget handle.
*              pTimeWdg:     used to get a FCTime Widget handle. FCTime is a widget that composed of sevel Ring-List widgets.
*					   Each Ring-List display one of time value, and one of those Ring-List widgets is a focus widget that
*					   can change it's first display index of item when user press up/down navigation keys
*
*/
typedef struct TimeInputWdgList
{
	IWidget *pTitleWdg;
	IWidget *pTimeWdg;
#ifdef __WIDGET_DISABLE_FINGERCOMMAND__
	IWidget *pTextWdg;
#endif
}TimeInputWdgList_t;

/** TimeInputData_t
*
* @brief    nTitleImgId:       set the image id that defined in Img_data.h
*              nTitleTxtId:        set the id of text that defined in Mae_textlabel.h
*              nHour:  		      set hour, value is from 0 to 23.
*              nMin:        	      set minute, value is from 0 to 59.
*		  nSec:        	      set second, value is from 0 to 59. This field is valid when FCTime Widget is set to CLSID_COUNTDOWNTIME_WIDGET.
*/
typedef struct TimeInputData
{
	u32 nTitleImgId;
	u32 nTitleTxtId;
	u8  nHour;
	u8  nMin;
	u8  nSec;
}TimeInputData_t;


/** VtmCreateTimeInput
* @brief   create a screen with title and FCTime widget. The default type of FCTime widget is CLSID_FCTIME_WIDGET.
*
* @param[in]    hWin        	point to a window handle
* @param[out]  pWdgList         	return the widgets handle if creating success. It includes FCTimeWidget and TitleWidget.
* @param[in]    pData 			set the default time. Refer to the sturct TimeInputData_t
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret VtmCreateTimeInput(HWIN hWin, TimeInputWdgList_t *pWdgList, TimeInputData_t *pData);

//////////////////////////////////////////////////////////////////////////
enum //VID_MENU_IMGGRID_enum
{
	IMG_GRID_MENU_TITLE_WDG=TITLE_WDG_ID,
	IMG_GRID_MENU_MENU_WDG=VTM_WDG_START
}; //VID_MENU_IMGGRID_enum

/** ImgGridWdgList_t
*
* @brief    pTitleWdg: 				used to get a Title Widget handle.
*						pMenuWdg:       	used to get a Menu Widget handle.
*/
typedef struct ImgGridWdgList_tag
{
	IWidget *pTitleWdg;
	IWidget *pMenuWdg;
}ImgGridWdgList_t;

/** ImgGridData_t
*
* @brief    nTitleImgId:			set the image id that defined in Img_data.h
*						nTitleTxtId:			set the id of text that defined in Mae_textlabel.h
*           nItemCount:  		  set the number of item. This value must <= pItemData
*           nFirstItem:  		  set the default selected page.
*           nSelectedItem:  	set the default selected item.
*           pItemData:  		  ponit to the struct WdgStaticMenuItem_t. Refer to Mmi_wdgwrap_menu.h
*/
typedef struct ImgGridData
{
	u32 nTitleImgId;
	u32 nTitleTxtId;

	u32 nItemCount;
	u32 nFirstItem;
	u32 nSelectedItem;

}ImgGridData_t;

/** ImgGridCB_t
*
* @brief    pfnGetItemData:
*
*/
typedef struct ImgGridCB
{
	/*PfnWdgDynamicMenuGetDataPtr pfnGetItemData;
	PfnWdgDynamicMenuFreeDataPtr pfnFreeItemData;*/
	PfnWdgDynamicMenuGetData pfnGetItemData;
}ImgGridCB_t;

/** VtmCreateImgGridMenu
* @brief
*
*
* @param[in]    hWin        	point to a window handle
* @param[out]   pWdgList        return the widgets handle if creating success. Refer to the struct ImgGridWdgList_t.
* @param[in]    pData 					set the default value. Refer to the sturct ImgGridData_t
* @param[in]    pCB							set the callback entry function. Refer to the struct ImgGridCB_t.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret VtmCreateImgGridMenu(HWIN hWin, ImgGridWdgList_t *pWdgList, ImgGridData_t *pData, WdgStaticMenuItem_t *pItemData, ImgGridCB_t *pCB);

//////////////////////////////////////////////////////////////////////////
enum //FILEMGRAPP_CNTGRID_THUMB_VIEW_enum
{
	IMG_THUMB_TITLE_WDG=TITLE_WDG_ID,
	IMG_THUMB_MENU_WDG=VTM_WDG_START
}; //FILEMGRAPP_CNTGRID_THUMB_VIEW_enum

/** ImgThumbWdgList_t
*
* @brief                pTitleWdg: 			used to get a Title Widget handle.
*						pMenuWdg:       	used to get a Menu Widget handle.
*/
typedef struct ImgThumbWdgList_tag
{
	IWidget *pTitleWdg;
	IWidget *pMenuWdg;
}ImgThumbWdgList_t;

/** ImgThumbData_t
*
* @brief    nTitleImgId:			set the image id that defined in Img_data.h
*						nTitleTxtId:			set the id of text that defined in Mae_textlabel.h
*           nItemCount:  		  set the number of item. This value must <= pItemData
*           pItemData:  		  ponit to the struct WdgStaticMenuItem_t. Refer to Mmi_wdgwrap_menu.h
*/
typedef struct ImgThumbData
{
	u32 nTitleImgId;
	u32 nTitleTxtId;

	u32 nItemCount;
}ImgThumbData_t;

/** ImgGridCB_t
*
* @brief    pfnGetItemData:
*						pfnFreeItemData:
*
*/
typedef struct ImgThumbCB
{
	PfnWdgDynamicMenuGetDataPtr pfnGetItemData;
	PfnWdgDynamicMenuFreeDataPtr pfnFreeItemData;
}ImgThumbCB_t;

/** VtmCreateImgThumb
* @brief
*
*
* @param[in]    hWin        	point to a window handle
* @param[out]   pWdgList        return the widgets handle if creating success. Refer to the struct ImgThumbWdgList_t.
* @param[in]    pData 					set the default value. Refer to the sturct ImgThumbData_t
* @param[in]    pCB							set the callback entry function. Refer to the struct ImgThumbCB_t.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret VtmCreateImgThumb(HWIN hWin, ImgThumbWdgList_t *pWdgList, ImgThumbData_t *pData, WdgStaticMenuItem_t *pItemData, ImgThumbCB_t *pCB);

//////////////////////////////////////////////////////////////////////////
enum //VID_MENU_NORMAL_enum
{
	VTM_CREATE_MENU_TITLE_WDG=TITLE_WDG_ID,
	VTM_CREATE_MENU_MENU_WDG=VTM_WDG_START
}; //VID_MENU_NORMAL_enum

/** MenuWdgList_t
*
* @brief    pTitleWdg: 				used to get a Title Widget handle.
*						pMenuWdg:       	used to get a Menu Widget handle.
*/
typedef struct MenuWdgList_tag
{
	IWidget *pTitleWdg;
	IWidget *pMenuWdg;
}MenuWdgList_t;

/** MenuData_t
*
* @brief    nTitleImgId:      set the image id that defined in Img_data.h
*						nTitleTxtId:      set the id of text that defined in Mae_textlabel.h
*						eMenuType:				WDG_MENU_TYPE_NORMAL or WDG_MENU_TYPE_NUMERIC
*						eItemType:        set the type of item. Refer to Mmi_wdgwrap_menu.h
*           eCheckStyle:      set the check style of item. Refer to Mmi_wdgwrap_menu.h
*           nItemCount:  		  set the number of item. This value must <= pItemData
*           nFirstItem:  		  set the default selected page.
*           nSelectedItem:  	set the default selected item.
*           pItemData:  		  ponit to the struct WdgStaticMenuItem_t. Refer to Mmi_wdgwrap_menu.h
*/
typedef struct MenuData
{
	u32 nTitleImgId;
	u32 nTitleTxtId;

	WdgMenuType_t eMenuType;//WDG_MENU_TYPE_NORMAL or WDG_MENU_TYPE_NUMERIC
	WdgMenuItemType_t eItemType;
	WdgMenuCheckStyle_t eCheckStyle;

	u32 nItemCount;
	u16 nFirstItem;
	u16 nSelectedItem;

}MenuData_t;

/** ImgGridCB_t
*
* @brief    pfnGetItemData:
*						pfnFreeItemData:
*
*/
typedef struct MenulCB
{
	PfnWdgDynamicMenuGetDataPtr pfnGetItemData;
	PfnWdgDynamicMenuFreeDataPtr pfnFreeItemData;
}MenuCB_t;

/** VtmCreateMenu
* @brief
*
*
* @param[in]    hWin        	point to a window handle
* @param[out]   pWdgList        return the widgets handle if creating success. Refer to the struct MenuWdgList_t.
* @param[in]    pData 					set the default value. Refer to the sturct MenuData_t
* @param[in]    pCB							set the callback entry function. Refer to the struct MenuCB_t.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret VtmCreateMenu(HWIN hWin, MenuWdgList_t *pWdgList, MenuData_t *pData, WdgStaticMenuItem_t *pItemData, MenuCB_t *pCB);

//////////////////////////////////////////////////////////////////////////
enum //SEA_DUALSIM_MENU_VIEW_enum
{
	SIM_SELECTION_TITLE_WDG=TITLE_WDG_ID,
	SIM_SELECTION_MENU_WDG=VTM_WDG_START
}; //SEA_DUALSIM_MENU_VIEW_enum

/** SimSelectionWdgList_t
*
* @brief    pTitleWdg: 				used to get a Title Widget handle.
*						pMenuWdg:       	used to get a Menu Widget handle.
*/
typedef struct SimSelectionWdgList_tag
{
	IWidget *pTitleWdg;
	IWidget *pMenuWdg;
}SimSelectionWdgList_t;


/** SimSelectionData_t
*
* @brief    nTitleImgId:			set the image id that defined in Img_data.h
*						nTitleTxtId:			set the id of text that defined in Mae_textlabel.h
*/
typedef struct SimSelectionData
{
	u32 nTitleImgId;
	u32 nTitleTxtId;
}SimSelectionData_t;


/** VtmCreateSimSelection
* @brief
*
*
* @param[in]    hWin        	point to a window handle
* @param[out]   pWdgList        return the widgets handle if creating success. Refer to the struct SimSelectionWdgList_t.
* @param[in]    pData 					set the default value. Refer to the sturct SimSelectionData_t
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret VtmCreateSimSelection(HWIN hWin, SimSelectionWdgList_t *pWdgList, SimSelectionData_t *pData);

//////////////////////////////////////////////////////////////////////////
enum //VID_MENU_TAB_enum
{
	TAB_MENU_TITLE_WDG=TITLE_WDG_ID,
	TAB_MENU_TAB_WDG=VTM_WDG_START,
	TAB_MENU_MENU_WDG_0,
	TAB_MENU_MENU_WDG_1,
	TAB_MENU_MENU_WDG_2,
	TAB_MENU_MENU_WDG_3,
	TAB_MENU_MENU_WDG_4
}; //VID_MENU_TAB_enum

/** TabMenuWdgList_t
*
* @brief    pTitleWdg: 			used to get a Title Widget handle.
*						pTabWdg:       	used to get a tab Widget handle. Tab widget is divided into Tab area and Content area.
*														Tab area will every time display an active tab, and the rest are inactive tabs
*						ppMenuWdgArray:	used to get a array handle of Menu Widget .
*/
typedef struct TabMenuWdgList_tag
{
	IWidget *pTitleWdg;
	IWidget *pTabWdg;
	IWidget** ppMenuWdgArray;
}TabMenuWdgList_t;

/** TabPageData_t
*
* @brief    nTabImageId:      set the image id that defined in Img_data.h
*						nTabTxtId:      	set the id of text that defined in Mae_textlabel.h
*						eItemType:        set the type of item. Refer to Mmi_wdgwrap_menu.h
*           eCheckStyle:      set the check style of item. Refer to Mmi_wdgwrap_menu.h
*           nItemCount:  		  set the number of item. This value must <= pItemData
*           nFirstItem:  		  set the default selected page.
*           nSelectedItem:  	set the default selected item.
*/
typedef struct TabPageData
{
	u32 nTabImageId;   //Image ID
	u32 nTabTxtId;    //Text ID

    WdgMenuType_t eMenuStyle;
	WdgMenuItemType_t eItemType;
	WdgMenuCheckStyle_t eCheckStyle;

	u32 nItemCount;
	u16 nFirstItem;
	u16 nSelectedItem;
}TabPageData_t;

/** TabMenuData_t
*
* @brief    nTitleImgId:      set the image id that defined in Img_data.h
*						nTitleTxtId:      set the id of text that defined in Mae_textlabel.h
*           nPageCount:  		  set the number of tab. This value must <= pPageDataArray
*           pPageDataArray:   ponit to the struct TabPageData_t. Refer to Mmi_common_vtmmenu.h
*/
typedef struct TabMenuData
{
	u32 nTitleImgId;
	u32 nTitleTxtId;

	u32 nPageCount;
}TabMenuData_t;

/** TabMenuCB_t
*
* @brief    pfnGetItemDataArray:
*						pfnFreeItemDataArray:
*
*/
typedef struct TabMenuCB
{
	PfnWdgDynamicMenuGetDataPtr* pfnGetItemDataArray;
	PfnWdgDynamicMenuFreeDataPtr* pfnFreeItemDataArray;
}TabMenuCB_t;


/** VtmCreateTabMenu
* @brief
*
*
* @param[in]    hWin        	point to a window handle
* @param[out]   pWdgList        return the widgets handle if creating success. Refer to the struct TabPageData_t
* @param[in]    pData 					set the default value. Refer to the sturct TabMenuData_t
* @param[in]    pCB							set the callback entry function. Refer to the struct TabMenuCB_t.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret VtmCreateTabMenu(HWIN hWin, TabMenuWdgList_t *pWdgList, TabMenuData_t *pData, TabPageData_t* pPageDataArray, TabMenuCB_t *pCB);

//////////////////////////////////////////////////////////////////////////
enum //VID_MENU_TXTGRID_enum
{
	TXT_GRID_MENU_TITLE_WDG=TITLE_WDG_ID,
	TXT_GRID_MENU_MENU_WDG=VTM_WDG_START
}; //VID_MENU_TXTGRID_enum

/** ImgGridWdgList_t
*
* @brief    pTitleWdg: 				used to get a Title Widget handle.
*						pMenuWdg:       	used to get a Menu Widget handle.
*/
typedef struct TxtGridWdgList_tag
{
	IWidget *pTitleWdg;
	IWidget *pMenuWdg;
}TxtGridWdgList_t;


/** TxtGridData_t
*
* @brief    nTitleImgId:      set the image id that defined in Img_data.h
*						nTitleTxtId:     	set the id of text that defined in Mae_textlabel.h
*						eItemType:        set the type of item. Refer to Mmi_wdgwrap_menu.h
*           nItemCount:  		  set the number of item. This value must <= pItemData
*           nFirstItem:  		  set the default selected page.
*           nSelectedItem:  	set the default selected item.
*           pItemData:  		  ponit to the struct WdgStaticMenuItem_t. Refer to Mmi_wdgwrap_menu.h
*/
typedef struct TxtGridData
{
	u32 nTitleImgId;
	u32 nTitleTxtId;

	WdgMenuItemType_t eItemType;

	u32 nItemCount;
	u32 nFirstItem;
	u32 nSelectedItem;

}TxtGridData_t;

/** TxtGridCB_t
*
* @brief    pfnGetItemData:
*						pfnFreeItemData:
*
*/
typedef struct TxtGridCB
{
	PfnWdgDynamicMenuGetDataPtr pfnGetItemData;
	PfnWdgDynamicMenuFreeDataPtr pfnFreeItemData;
}TxtGridCB_t;

/** VtmCreateTxtGridMenu
* @brief
*
*
* @param[in]    hWin        	point to a window handle
* @param[out]   pWdgList        return the widgets handle if creating success. Refer to the struct TxtGridWdgList_t
* @param[in]    pData 					set the default value. Refer to the sturct TxtGridData_t
* @param[in]    pCB							set the callback entry function. Refer to the struct TxtGridCB_t.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret VtmCreateTxtGridMenu(HWIN hWin, TxtGridWdgList_t *pWdgList, TxtGridData_t *pData, WdgStaticMenuItem_t *pItemData, TxtGridCB_t *pCB);

//////////////////////////////////////////////////////////////////////////
enum //VID_MENU_POPUP_SELECT_enum
{
	POP_UP_SELECT_MENU_WDG=VTM_WDG_START,
}; //VID_MENU_POPUP_SELECT_enum

/** InputVtmWdgList_t
*
* @brief    pMenuWdg:       	used to get a Menu Widget handle.
*/
typedef struct PopUpSelectWdgList_tag
{
	IWidget *pMenuWdg;
}PopUpSelectWdgList_t;

/** PopUpSelectData_t
*
* @brief    pTitleTxt:       	set the text of title.
*						eItemType:        set the type of item. Refer to Mmi_wdgwrap_menu.h
*           eCheckStyle:      set the check style of item. Refer to Mmi_wdgwrap_menu.h
*           nItemCount:  		  set the number of item. This value must <= pItemData
*           nFirstItem:  		  set the default selected page.
*           nSelectedItem:  	set the default selected item.
*           pItemData:  		  ponit to the struct WdgStaticMenuItem_t. Refer to Mmi_wdgwrap_menu.h
*/
typedef struct PopUpSelectData
{
	MAE_WChar *pTitleTxt;

	WdgMenuItemType_t eItemType;
	WdgMenuCheckStyle_t eCheckStyle;

	u32 nItemCount;
	u16 nFirstItem;
	u16 nSelectedItem;

}PopUpSelectData_t;

/** PopUpSelectCB_t
*
* @brief    pfnGetItemData:
*						pfnFreeItemData:
*
*/
typedef struct PopUpSelectCB
{
	PfnWdgDynamicMenuGetDataPtr pfnGetItemData;
	PfnWdgDynamicMenuFreeDataPtr pfnFreeItemData;
}PopUpSelectCB_t;

/** VtmCreatePopUpSelect
* @brief  create a pop up dialog with several items. For example, pop up a dialog let user select defult ring tone.
*
*
* @param[in]    hWin        	point to a window handle
* @param[out]   pWdgList        return the widgets handle if creating success. Refer to the struct PopUpSelectData_t.
* @param[in]    pData 					set the default value. Refer to the sturct PopUpSelectData_t
* @param[in]    pCB							set the callback entry function. Refer to the struct PopUpSelectCB_t.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
* @Note         You should using "VT_OPT_MENU" in ViewCreate() function to create the hWin before call VtmCreatePopUpSelect()
*               "VT_POPUP" maybe ok, but not suggest! It take more memory for a useless title widget.
*/
MAE_Ret VtmCreatePopUpSelect(HWIN hWin, PopUpSelectWdgList_t *pWdgList, PopUpSelectData_t *pData, WdgStaticMenuItem_t *pItemData, PopUpSelectCB_t *pCB);

//////////////////////////////////////////////////////////////////////////
enum //PopupInfo_enum
{
	POP_UP_PROMPT_TITLE_WDG=TITLE_WDG_ID,
	POP_UP_PROMPT_BG_IMG_WDG=VTM_WDG_START,
	POP_UP_PROMPT_INPUT_WDG,
	POP_UP_PROMPT_TXT_WDG
}; //PopupInfo_enum

/** InputVtmWdgList_t
*
* @brief    pTitleWdg:       	used to get a Title Widget handle.
*						pBgImgWdg:        used to get a Image Widget handle.
*		  			pInputWdg:	   		used to get a Inuput Widget handle. Input Widget provides not only Date/Time/IP
*					   									those fixed format of input methods and also provides other input methods
*					   									For example, PIN, SMS, phone numbers, names of persons etc.
*						pTxtWdg:         	used to get a text Widget handle.
*/
typedef struct PopUpPromptWdgList
{
	IWidget *pTitleWdg;
	IWidget *pBgImgWdg;
	IWidget *pInputWdg;
	IWidget *pTxtWdg;
}PopUpPromptWdgList_t;

/** PopUpPromptData_t
*
* @brief    nBgImgId:       	set the image id that defined in Img_data.h
*						nTitleImgId:      set the image id that defined in Img_data.h
*           nTitleTxtId:      set the id of text that defined in Mae_textlabel.h
*           nTxtId:  		      set the id of text that defined in Mae_textlabel.h
*/
typedef struct PopUpPromptData
{
	u32 nBgImgId;
	u32 nTitleImgId;
	u32 nTitleTxtId;
	u32 nTxtId;
}PopUpPromptData_t;

/** VtmCreatePopUpPrompt
* @brief  create a pop up prompt to ask user input something.
*
*
* @param[in]    hWin        	point to a window handle
* @param[out]   pWdgList        return the widgets handle if creating success. Refer to the struct PopUpPromptWdgList_t.
* @param[in]    pData 					set the default value. Refer to the sturct PopUpPromptData_t
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*
* @Note         You must using "VT_POPUP" in ViewCreate() function to create the hWin before call VtmCreatePopUpPrompt()
*/
MAE_Ret VtmCreatePopUpPrompt(HWIN hWin, PopUpPromptWdgList_t *pWdgList, PopUpPromptData_t *pData);

//////////////////////////////////////////////////////////////////////////
enum //COMMON_POPUP_INPUT_enum
{
	POP_UP_INPUT_TITLE_WDG=TITLE_WDG_ID,
	POP_UP_INPUT_BG_IMG_WDG=VTM_WDG_START,
	POP_UP_INPUT_INPUT_WDG
}; //COMMON_POPUP_INPUT_enum

/** PopUpInputWdgList_t
*
* @brief    pBgImgWdg:        used to get a Image Widget handle.
*						pTitleWdg:       	used to get a Title Widget handle.
*		  			pInputWdg:	   		used to get a Inuput Widget handle. Input Widget provides not only Date/Time/IP
*					   									those fixed format of input methods and also provides other input methods
*					   									For example, PIN, SMS, phone numbers, names of persons etc.
*/
typedef struct PopUpInputWdgList_tag
{
	IWidget *pBgImgWdg;
	IWidget *pTitleWdg;
	IWidget *pInputWdg;
}PopUpInputWdgList_t;

/** PopUpInputData_t
*
* @brief    nBgImgId:       	set the image id that defined in Img_data.h
*						nTitleImgId:      set the image id that defined in Img_data.h
*           nTitleTxtId:      set the id of text that defined in Mae_textlabel.h
*
*/
typedef struct PopUpInputData
{
	u32 nBgImgId;
	u32 nTitleImgId;
	u32 nTitleTxtId;
	u32 nInputMode;
}PopUpInputData_t;

/** VtmCreatePopUpInput
* @brief  create a pop up input to ask user input something. The different between VtmCreatePopUpInput and VtmCreatePopUpPrompt
*					is VtmCreatePopUpPrompt has an additional text widget can show more information
*
*
* @param[in]    hWin        	point to a window handle
* @param[out]   pWdgList        return the widgets handle if creating success. Refer to the struct PopUpInputWdgList_t.
* @param[in]    pData 					set the default value. Refer to the sturct PopUpInputData_t
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
* @Note         You must using "VT_POPUP" in ViewCreate() function to create the hWin before call VtmCreatePopUpInput()
*/
MAE_Ret VtmCreatePopUpInput(HWIN hWin, PopUpInputWdgList_t *pWdgList, PopUpInputData_t *pData );

//////////////////////////////////////////////////////////////////////////
enum //MP_DETAILS_VIEW_enum
{
    POP_UP_INFO_TITLE_WDG=TITLE_WDG_ID,
	POP_UP_INFO_BG_IMG_WDG=VTM_WDG_START,
	POP_UP_INFO_SCROLLBAR_WDG,
	POP_UP_INFO_VIEWPORT_WDG,
	POP_UP_INFO_THM_TXT_WDG
}; //MP_DETAILS_VIEW_enum
/** PopUpInfoWdgList_t
*
* @brief    pBgImgWdg:        used to get a Image Widget handle.
*						pTitleWdg:       	used to get a Title Widget handle.
*		  			pScrollbarWdg:	  used to get a Scroll-bar Widget handle. Scroll-bar widget is a decorator widget,
*					   									mainly to enhance the display of some widget (like List widget) to make up for lack of.
*						pViewportWdg:			used to get a Viewport Widget handle. It provide an area to display an object that may be large
*						pThmTxtWdg:				used to get a Theme-Text Widget handle. Theme-Text widget will follow the Theme to change the
*															text color, outline color, highlight text color, and highlight outline color
*/
typedef struct PopUpInfoWdgList_Tag
{
	IWidget *pBgImgWdg;
	IWidget *pTitleWdg;
	IWidget *pScrollbarWdg;
	IWidget *pViewportWdg;
	IWidget *pThmTxtWdg;
}PopUpInfoWdgList_t;

/** PopUpInputData_t
*
*	@brief		nTitleImgId:      set the image id that defined in Img_data.h
*           nTitleTxtId:      set the id of text that defined in Mae_textlabel.h
*
*/
typedef struct PopUpInfoData
{
	u32 nTitleImgId;
	u32 nTitleTxtId;

}PopUpInfoData_t;

/** VtmCreatePopUpInfo
* @brief  create a pop up text screen to show some ionformation. For example, system verion info.
*
*
* @param[in]    hWin        	point to a window handle
* @param[out]   pWdgList        return the widgets handle if creating success. Refer to the struct PopUpInfoWdgList_t.
* @param[in]    pData 					set the default value. Refer to the sturct PopUpInfoData_t
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
* @Note         You should using "VT_POPUP" in ViewCreate() function to create the hWin before call VtmCreatePopUpInfo()
*/
MAE_Ret VtmCreatePopUpInfo(HWIN hWin, PopUpInfoWdgList_t *pWdgList, PopUpInfoData_t *pData, MAE_WChar *pText);

//////////////////////////////////////////////////////////////////////////
enum //VID_MENU_OPTION_enum
{
	OPTION_MENU_MENU_WDG=VTM_WDG_START,
}; //VID_MENU_OPTION_enum

/** InputVtmWdgList_t
*
* @brief    pMenuWdg:       	used to get a Menu Widget handle.
*/
typedef struct OptionMenuWdgList_tag
{
	IWidget *pMenuWdg;
}OptionMenuWdgList_t;

/** OptionMenuData_t
*
*	@brief		eItemType:      	set the type of item. Refer to Mmi_wdgwrap_menu.h
*           nItemCount:       set the number of item. This value must <= pItemData
*						pItemData:				ponit to the struct WdgStaticMenuItem_t. Refer to Mmi_wdgwrap_menu.h
*
*/
typedef struct OptionMenuData
{
	WdgMenuItemType_t eItemType;
	u16 nItemCount;
}OptionMenuData_t;

typedef struct OptionMenuCB
{
	PfnWdgDynamicMenuGetDataPtr pfnGetItemData;
	PfnWdgDynamicMenuFreeDataPtr pfnFreeItemData;
}OptionMenuCB_t;

/** VtmCreateOptionMenu
* @brief  create a dialog with several items. For example, show a dialog with add, del, search items.
*
*
* @param[in]    hWin        	point to a window handle
* @param[out]   pWdgList        return the widgets handle if creating success. Refer to the struct OptionMenuData_t.
* @param[in]    pData 					set the default value. Refer to the sturct OptionMenuCB_t
* @param[in]    pCB							set the callback entry function. Refer to the struct OptionMenuCB_t.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*
* @Note         You should using "VT_OPT_MENU" in ViewCreate() function to create the hWin before call VtmCreateOptionMenu()
*               "VT_POPUP" maybe ok, but not suggest! It take more memory for a useless title widget.
*/
MAE_Ret VtmCreateOptionMenu(HWIN hWin, OptionMenuWdgList_t *pWdgList, OptionMenuData_t *pData, WdgStaticMenuItem_t *pItemData, OptionMenuCB_t *pCB);

//////////////////////////////////////////////////////////////////////////
enum //COMMON_POPUP_INPUT_IP_enum
{
	VTM_IP_INPUT_TITLE_WDG=TITLE_WDG_ID,
	VTM_IP_INPUT_BG_IMG_WDG=VTM_WDG_START,
	VTM_IP_INPUT_IP_WDG
}; //COMMON_POPUP_INPUT_IP_enum

/** IpInputWdgList_t
*
* @brief    pBgImgWdg:        used to get a Image Widget handle.
*						pTitleWdg:       	used to get a Title Widget handle.
*		  			pIpWdg:	   			  used to get a IP Widget handle. Provide the IP format information from the inputting data.
*															Format is ¡§NNN.NNN.NNN.NNN¡¨, and each field maximum value is 255
*/
typedef struct IpInputWdgList_tag
{
	IWidget *pTitleWdg;
	IWidget *pBgImgWdg;
	IWidget *pIpWdg;
}IpInputWdgList_t;

/** IpInputData_t
*
*	@brief		pBgImgWdg:        used to get a Image Widget handle.
*						nTitleImgId:      set the image id that defined in Img_data.h
*           nTitleTxtId:      set the id of text that defined in Mae_textlabel.h
*
*/
typedef struct IpInputData
{
	u32 nBgImgId;
	u32 nTitleImgId;
	u32 nTitleTxtId;
}IpInputData_t;

/** VtmCreateIpInput
* @brief  create a screen let user input IP address.
*
*
* @param[in]    hWin        	point to a window handle
* @param[out]   pWdgList        return the widgets handle if creating success. Refer to the struct IpInputWdgList_t.
* @param[in]    pData 					set the default value. Refer to the sturct IpInputData_t
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*
* @Note         You must using "VT_POPUP" in ViewCreate() function to create the hWin before call VtmCreateIpInput()
*/
MAE_Ret VtmCreateIpInput(HWIN hWin, IpInputWdgList_t *pWdgList, IpInputData_t *pData);


MAE_Ret VtmCreateMenu1(HWIN hWin, MenuWdgList_t *pWdgList);

MAE_Ret VtmSetInputLayout(HWIN hWin, InputVtmWdgList_t *pWdgList);
MAE_Ret VtmSetIpInputLayout(HWIN hWin, IpInputWdgList_t *pWdgList);
MAE_Ret VtmSetMenuLayout(HWIN hWin, MenuWdgList_t *pWdgList);
MAE_Ret VtmSetOptionMenuLayout(HWIN hWin, OptionMenuWdgList_t *pWdgList);
MAE_Ret VtmSetPopUpInputLayout(HWIN hWin, PopUpInputWdgList_t *pWdgList,u32 nInputMode);
MAE_Ret VtmSetPopUpPromptLayout(HWIN hWin, PopUpPromptWdgList_t *pWdgList);
MAE_Ret VtmSetPromptInputLayout(HWIN hWin, PromptInputWdgList_t *pWdgList);
MAE_Ret VtmSetTabMenuLayout(HWIN hWin, TabMenuWdgList_t *pWdgList, u32 uTabNum);

//
MAE_Ret VtmSetDateInputLayout(HWIN hWin, DateInputWdgList_t *pWdgList);
MAE_Ret VtmSetTimeInputLayout(HWIN hWin, TimeInputWdgList_t *pWdgList);
MAE_Ret VtmSetTxtGridMenuLayout(HWIN hWin, TxtGridWdgList_t *pWdgList);
MAE_Ret VtmSetImgGridMenuLayout(HWIN hWin, ImgGridWdgList_t *pWdgList, ImgGridData_t *pData, WdgStaticMenuItem_t *pItemData);
MAE_Ret VtmSetImgLayout(HWIN hWin, ImageVtmWdgList_t *pWdgList, ImageVtmData_t *pData);
MAE_Ret VtmSetImgThumbLayout(HWIN hWin, ImgThumbWdgList_t *pWdgList, ImgThumbData_t *pData, WdgStaticMenuItem_t *pItemData);
MAE_Ret VtmSetSimSelectionLayout(HWIN hWin, SimSelectionWdgList_t *pWdgList);
MAE_Ret VtmSetPopUpSelectLayout(HWIN hWin, PopUpSelectWdgList_t *pWdgList);
MAE_Ret VtmSetPopUpInfoLayout(HWIN hWin, PopUpInfoWdgList_t *pWdgList);

#endif // __MMI_COMMON_VTM_PRIV_H__

