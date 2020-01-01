/**
* @file    mae_glboxlistwidget.h
* @brief
* @version $Id: mae_glboxlistwidget.h 37664 2010-02-12 09:36:01Z Elvis.Chen $
*/

#ifndef __MMI_WDG_GLBOXLISTWIDGET_H__
#define __MMI_WDG_GLBOXLISTWIDGET_H__

/*=============================================================*/
// include
/*=============================================================*/

#include "mmi_wdg_image_doubleitem.h"
#include "mmi_mae_vectormodel.h"
#include "mmi_wdg_glfotolistwidget_def.h"

/**
* Support class id: CLSID_GLBOXLISTWIDGET
*
*
* The widget handles following events:
*
*
*     EVT_WIDGET_SET_PROPERTY:  The widget handle this event by attempting to set the following properties
*                           PROP_FIRST_INDEX : A zero-based index of item to indicate which element is the first element to display.
*                           PROP_FOCUS_INDEX : A zero-based index of item to indicate which element is on focus.
*                                              Glboxlist widget will auto set the first index as focus item, so if user set the first/focus index, it will become the first index too.
*
*                           PROP_GLBOXLIST_WDG_SET_BOXDATA: Set property. P2=>Set:(GlBoxData_t *). Set the box data.
*                           PROP_GLBOXLIST_WDG_ENTER_BOX_ANIMATION: Set property. P2=>Set:(boolean), TRUE: start the enter box animation. FALSE: stop the enter box animation.
*                           PROP_MENU_WDG_DEFAULT_LEFT_SOFTKEY
*                           PROP_MENU_WDG_DEFAULT_MIDDLE_SOFTKEY
*                           PROP_MENU_WDG_DEFAULT_RIGHT_SOFTKEY
*
*     EVT_WIDGET_GET_PROPERTY:
*                           PROP_FIRST_INDEX : A zero-based index of item to indicate which element is the first element to display.
*                           PROP_FOCUS_INDEX : A zero-based index of item to indicate which element is on focus.
*
*
* Supported Model:
*     IMenuModel.
*
* Model data:
*     MenuModelData_t with pItemData in format of GlFotoListWdgData_t.
*/


/*=============================================================*/
// type and define
/*=============================================================*/
enum
{
    GlBox_ButtonState_Invisible,
    GlBox_ButtonState_Visible,
    GlBox_ButtonState_Disable,
};
typedef u8 GlBox_ButtonState_e;

typedef struct
{
  MAE_WChar *pText;
  IImage *pPreImage;
  MAE_WChar *pInfoText1;
  MAE_WChar *pInfoText2;
  IImage *pInfoIcon1;
  IImage *pInfoIcon2;
  u8 bUnread;
    GlBox_ButtonState_e LeftButton;
    GlBox_ButtonState_e RightButton;
    boolean bMMS;
}GlBoxListWdgData_t;

typedef ImageTextInfo GlBoxInfo_t;

typedef struct {
    u32 nFocusIdx;            ///< The focus box index.
    IListModel *pListMdl; /// List Model of GlBoxInfo_t
} GlBoxData_t;

typedef struct {
    u32 nDisableImgID;
    u32 nUnPressedImgID;
    u32 nPressedImgID;
} GlBoxButton_t;

typedef void (*PfnWdgGlBoxListViewModelChanged) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, BoxChangeData_t *ptBoxData, void *pReserve);

MAE_Ret WdgGlBoxListRegisterViewModelChangedCb(IWidget *pWDGMenu, PfnWdgGlBoxListViewModelChanged pfn, void *pUserData);
MAE_Ret WdgGlBoxListDeregisterViewModelChangedCb(IWidget *pWDGMenu, PfnWdgGlBoxListViewModelChanged pfn, void *pUserData);


/*=============================================================*/
// functions
/*=============================================================*/

/**
* @brief
*
* @param    IWidgetPtr(IWidget*)            The pointer of IWidget interface object
* @param    pBoxData (GlBoxData_t *)        The pointer of the box data. BoxList widget will duplicate the box data,
*                                           so after calling this API user need to free the pBoxData and the release the pVectorMdl of the box data
*
* @retval   MAE_RET_SUCCESS     Success. The widget can handle this request.
* @retval   MAE_RET_FAILED      Failed.  The widget can not handle this request.
*/
MAE_INLINE MAE_Ret GlBoxListWdgHelper_SetBoxData(IWidget *IWidgetPtr, GlBoxData_t *pBoxData)
{
    return WdgCommonSetProperty(IWidgetPtr, PROP_GLBOXLIST_WDG_SET_BOXDATA, (u32)pBoxData);
}


#endif /* __MAE_GLBOXLISTWIDGET_H__ */
/*=============================================================*/
// end of file
