#ifndef __MMI_WDG_ITF_STATICMENU_H__
#define __MMI_WDG_ITF_STATICMENU_H__
/* ===========================================================*/
// Description
/* ===========================================================*/
/**
*     Menu widget, as its name implies, it shows the menu. The methodology of menu
*      is that on the menu for each item is a grid or to itemize on the two kinds
*     of display style to show. According to the menu widget to show on screen,
*     we can see the menu is composed of Item widget, List widget and Scroll-bar
*     widget. According to the size of the item style to display, when the putted items
*      number are more than the menu widget size, scroll bar will automatically
*     appear. Because there is only one entity item widget in Menu widget, so
*     in the menu widget every item must be of the same form.
*
*     In addition, the menu widget can set the softkeys. After the use of the AP
*     registers Model listener to menu widget, users touch/press key will be in the
*     model listener received by the call back function from the menu widget transponder
*     softkey event. In other words, if the AP through the menu settings no softkey
*     (directly to set softkey in view), the AP can not be in the model listener received
*     a call back of the menu transmitted softkey event.
*
*     Menu widgets can be categorized into several types: vertical, horizontal, numeric, image
*     grid, and text grid. The detail is described in the type and define section.
*
*          ex: image-grid menu widget
*           +---------------------------------+
*            | +------+  +------+  +------+   |
*            | | img  |  | img  |  | img  |   |
*            | +------+  +------+  +------+   |
*            | +------+  +------+  +------+   |
*            | | img  |  | img  |  | img  |   |
*            | +------+  +------+  +------+   |
*            | +------+  +------+  +------+   |
*            | | img  |  | img  |  | img  |   |
*            | +------+  +------+  +------+   |
*           +---------------------------------+
*
*/

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_itf_menu_common.h"
#include "mmi_wdg_itf_menu_item.h"

/*=============================================================*/
// type and define
/*=============================================================*/

/** WdgStaticMenuItemInf_t
*
* @brief Declare the common item information of item.
*              u32Flag: Descript the item attribute- WDG_MENU_ITEM_FLAG_HIDE
*                                                                    WDG_MENU_ITEM_FLAG_VISABLE
*                                                                    WDG_MENU_ITEM_FLAG_UNSELECTABLE
*                                                                    WDG_MENU_ITEM_FLAG_SELECTED
*                                                                    WDG_MENU_ITEM_FLAG_HAS_CHILD
*              au32Softkey: Descript the text id of softkeys when the item is be highlight 
*              u32ItemId: Descript the item ID; in menu tree, it is use to descript the next menu id 
*/
typedef struct
{
    u32 u32Flag;
    u32 au32Softkey[NUM_SK];
    u32 u32ItemId;
} WdgStaticMenuItemInf_t;

typedef struct
{
    WdgStaticMenuItemInf_t sInf;
    WdgMenuItem_t sData;
} WdgStaticMenuItem_t;

/* create static menu */
IWidget* WdgStaticMenuCreate(WdgMenuType_e eMenuType);
__SLDPM_FREE__ MAE_Ret WdgStaticMenuInit(IWidget *pMenu, WdgMenuItemType_e eItemType);
//MAE_Ret WdgStaticMenuInitItemWithId(IWidget *pMenu, u32 u32MenuDataId);
__SLDPM_FREE__ MAE_Ret WdgStaticMenuInitItemWithStruct(IWidget *pMenu, WdgMenuItemType_e eItemType, WdgStaticMenuItem_t *psMenuArrayData, u32 u32ItemNum);
//MAE_Ret WdgStaticMenuInitLayer2ItemWithId(IWidget *pMenu, u32 u32MenuDataId);
__SLDPM_FREE__ MAE_Ret WdgStaticMenuInitLayer2ItemWithStruct(IWidget *pMenu, WdgMenuItemType_e eItemType, WdgStaticMenuItem_t *psMenuArrayData, u32 u32ItemNum);
__SLDPM_FREE__ MAE_Ret WdgStaticMenuAddItemWithStruct(IWidget *pMenu, WdgStaticMenuItem_t sMenuData);
__SLDPM_FREE__ MAE_Ret WdgStaticMenuSetItemHide(IWidget *pMenu, u32 u32Index, boolean bHide);
__SLDPM_FREE__ MAE_Ret WdgStaticMenuGetItem(IWidget *pMenu, u32 u32Index, WdgMenuItemType_e *peItemType, WdgStaticMenuItem_t *psMenuItemData);
__SLDPM_FREE__ MAE_Ret WdgStaticMenuUpdateItem(IWidget *pMenu, u32 u32Index, WdgStaticMenuItem_t *psMenuItemData);

#endif //__MMI_WDG_ITF_STATICMENU_H__

