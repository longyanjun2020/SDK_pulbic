#ifndef __MMI_WDG_ITF_MENU_H__
#define __MMI_WDG_ITF_MENU_H__

#include "mmi_wdg_itf_dynamicmenu.h"
#include "mmi_wdg_itf_staticmenu.h"

//No next menu id of menu tree
#define WDG_MENUTREE_NO_MENU_ID 0xFFFFFFFF

//The root menu id of menu tree
#define WDG_MENUTREE_ROOT_MENU_ID 0xFFFFFFFE

typedef void (*PfnWdgMenuTreeMenuInit) (IWidget *pMenu, u32 u32MenuId, u32 u32Layer, u32 u32MenuSize, WdgMenuItemType_e eItemType);
typedef void (*PfnWdgMenuTreeMenuExit) (IWidget *pMenu, u32 u32MenuId, u32 u32Layer, u32 u32MenuSize, WdgMenuItemType_e eItemType);

/** WdgMenuTreeMenuInf_t
*
* @brief Declare a menu information in menu tree.
*              u32MenuId: Descript the menu ID
*              u32MenuAddr: Descript the text id of softkeys when the item is highlight. If the value is 0,
*                                    the menu is empty item menu in static menu. 
*              u32MenuSize: Descript the number of items in this menu
*              eItemType: Descript Item type of menu, ref.  WdgMenuItemType_e
*              pfGetItemData: a pointer of function to get the item data. If the value is not NULL, 
*                                     the menu will be created as a dynamic menu
*              pfFreeItemData:: a pointer of function to free a item data. If the value is not NULL,
*                                        the menu will be created as a dynamic menu
*/
typedef struct
{
    u32 u32MenuId;
    u32 u32MenuAddr;
    u32 u32MenuSize;
    WdgMenuItemType_e eItemType;
    PfnWdgDynamicMenuGetDataPtr pfGetItemData;
    PfnWdgDynamicMenuFreeDataPtr pfFreeItemData;
    PfnWdgMenuTreeMenuInit pfMenuInit;
    PfnWdgMenuTreeMenuInit pfMenuExit;
} WdgMenuTreeMenuInf_t;

/** WdgMenuTreeInit
* @brief To setup a group of menu information to menu widget, 
*           and mean the menu can be action as a menu tree.
*
* @param[in]    pMenu The menu widget
* @param[in]    psMenuInfArray A array of menu information, can't be NULL.
* @param[in]    u32ArraySize The size of menu information array
* @param[in]    u32RootMenuId The first entry menu id of menu tree
*
* @retval       MAE_RET_SUCCESS Success.
* @retval       Others Failed.
*
*/
MAE_Ret WdgMenuTreeInit(IWidget *pMenu, WdgMenuTreeMenuInf_t *psMenuInfArray, u32 u32ArraySize, u32 u32RootMenuId);
__SLDPM_FREE__ void WdgMenuImageGridSetImage(IWidget *pMenu, u32 u32Index, IImage *pImage);

#endif //__MMI_WDG_ITF_MENU_H__

