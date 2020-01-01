#ifndef __MMI_WDG_ITF_DYNAMICMENU_H__
#define __MMI_WDG_ITF_DYNAMICMENU_H__
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

typedef struct
{
    u32 u32Flag;
    u32 au32Softkey[NUM_SK];
    u32 u32ItemId;
    u32 u32UserData;
} WdgDynamicMenuItemInf_t;

typedef struct
{
    WdgDynamicMenuItemInf_t sInf;
    WdgMenuItem_t sData;
} WdgDynamicMenuItem_t;

typedef struct
{
    WdgDynamicMenuItemInf_t sInf;
    WdgMenuItemPtr_t sData;
} WdgDynamicMenuItemPtr_t;

typedef void (*PfnWdgDynamicMenuGetData) (WdgDynamicMenuItem_t *pItemData, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
typedef void (*PfnWdgDynamicMenuGetDataPtr) (WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 u32Index);
typedef void (*PfnWdgDynamicMenuFreeDataPtr) (WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);
typedef void (*PfnWdgDynamicMenuExFreeUserData) (u32 u32UserData);

/* create dynamic menu */
IWidget* WdgDynamicMenuCreate(WdgMenuType_e eMenuType);
__SLDPM_FREE__ MAE_Ret WdgDynamicMenuInitEx(IWidget *pMenu, WdgMenuItemType_e eItemType, PfnWdgDynamicMenuGetData pfGetItemData, PfnWdgDynamicMenuExFreeUserData pfFreeUserData);
__SLDPM_FREE__ MAE_Ret WdgDynamicMenuInit(IWidget *pMenu, WdgMenuItemType_e eItemType, PfnWdgDynamicMenuGetDataPtr pfGetItemData, PfnWdgDynamicMenuFreeDataPtr pfFreeItemData);
MAE_Ret WdgDynamicMenuInitStaticToDynamic(IWidget *pMenu, PfnWdgDynamicMenuGetDataPtr pfGetItemData, PfnWdgDynamicMenuFreeDataPtr pfFreeItemData);
__SLDPM_FREE__ MAE_Ret WdgDynamicMenuSetMenuSize(IWidget *pMenu, u32 u32MenuSize);
MAE_Ret WdgDynamicMenuDeleteItem(IWidget *pMenu, u32 u32ItemIndex);
MAE_Ret WdgDynamicMenuDeleteAllItem(IWidget *pMenu);
MAE_Ret WdgDynamicMenuInsertItem(IWidget *pMenu, u32 u32Index, WdgDynamicMenuItemPtr_t sItemData);
MAE_Ret WdgDynamicMenuInsertItemEx(IWidget *pMenu, u32 u32Index, WdgDynamicMenuItem_t sItemData);
MAE_Ret WdgDynamicMenuAddItem(IWidget *pMenu, WdgDynamicMenuItemPtr_t sItemData);
MAE_Ret WdgDynamicMenuAddItemEx(IWidget *pMenu, WdgDynamicMenuItem_t sItemData);
__SLDPM_FREE__ MAE_Ret WdgDynamicMenuGetItem(IWidget *pMenu, u32 u32Index, WdgMenuItemType_e *peItemType, WdgDynamicMenuItemPtr_t *psMenuItemData);
MAE_Ret WdgDynamicMenuReplaceItem(IWidget *pMenu, u32 u32Index, WdgDynamicMenuItemPtr_t sItemData);
MAE_Ret WdgDynamicMenuUpdateItem(IWidget *pMenu, u32 u32Index, WdgDynamicMenuItemPtr_t *psMenuItemData);

/** WdgDynamicMenuClearCacheEntities
* @brief        Clear the cache data of dynamic menu widget
*
* @param[in]    pWDGMenu          The pointer of IWidget interface object
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
__SLDPM_FREE__ MAE_Ret WdgDynamicMenuClearCacheEntities(IWidget *pWDGMenu);

#endif //__MMI_WDG_ITF_DYNAMICMENU_H__


