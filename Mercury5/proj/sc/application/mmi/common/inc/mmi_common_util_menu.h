/**
 * @file    mmi_common_util_menu.h
 * @brief
 *
 *
 * @author
 * @version $Id: mmi_common_util_menu.h 3696 2007-11-05 08:52:13Z eric.chen $
 */

#ifndef __MMI_COMMON_UTIL_MENU_H__
#define __MMI_COMMON_UTIL_MENU_H__

#include "mmi_mae_common_def.h"
#include "mmi_wdg_menu.h"
#include "mmi_mae_menumodel.h"
#include "mae_menulabel.h"

#include "mmi_common_thmid.h"
#include "mmi_shortcutssrv_cfg.h"
#include "mmi_view_id_range.h"
#include "mmi_wdg_headers.h"

/**
* MMI_Common_AddViewModelListener
* @brief	Add view model listener for given widget.
*
* @param	pIWidget				The pointer of IWidget to get view model from.
* @param	pViewModelListener		The pointer of ModelListener_t for view model listener.
* @param	pfnValueModelListener	Function pointer of pfnModelListenerWidget for view model listener.
* @param	pOwner					The pointer of caller object.
*
* @retVal	MAE_RET_BAD_PARAM		Invalid parameters.
* @retVal	MAE_RET_FAILED			Failed.
* @retVal	MAE_RET_SUCCESS			Success done.
*/
__SLDPM_FREE__ MAE_Ret MMI_Common_AddViewModelListener(IWidget *pIWidget, ModelListener_t *pViewModelListener, PfnModelListener pfnValueModelListener, IBase *pOwner);


/**
* SetImgDoubleTxtMenuItemData
* @brief		To add menu item data to menu model in dual SIM selection screen.
*
* @param	pThis	        The caller instance.
* @param	pIMenuModel	    The menu model pointer.
* @param	u32MenuItemID	The menu item ID.
* @param	u8DualID	    The dual ID.
* @param	nTextID	        The line1 text.
* @param	imgID	        The line1 image ID.


* @retVal	MAE_RET_SUCCESS			Success done.
*/

MAE_Ret SetImgDoubleTxtMenuItemData(IBase* pThis, IWidget * pIMenu,u32 u32MenuItemID, u8 u8DualID, u32 nTextID, u32 imgID);

/**
* UpdateSimSelectMenuItemData
* @brief		To update the menu item data for dual SIM selection screen.
*
* @param	pThis	        The caller instance.
* @param	pMenuItem	    The pointer of the menu item for the Dual SIM select menu.
* @param	u32MenuItemID	The menu item ID.
* @param	u8DualID	    The dual ID.
* @param	nTextID	        The line1 text.
* @param	imgID	        The line1 image ID.


* @retVal	MAE_RET_SUCCESS			Success done.
*/
MAE_WChar UpdateSimSelectMenuItemData(IBase* pThis, MenuModelData_t *pMenuItem, u32 u32MenuItemID, u8 u8DualID, u32 nTextID, u32 imgID);


/**
* _UpdateImgDoubleTxtMenuItemData
* @brief		To update the menu item data of CLSID_IMAGE_DOUBLE_TEXT_WIDGET for dual SIM selection screen.
*
* @param	pThis	        The caller instance.
* @param	pMenuItem	    The pointer of the menu item for the Dual SIM select menu.
* @param	u32MenuItemID	The menu item ID.
* @param	u8DualID	    The dual ID.
* @param	nTextID	        The line1 text.
* @param	imgID	        The line1 image ID.


* @retVal	MAE_RET_SUCCESS			Success done.
*/
MAE_WChar _UpdateImgDoubleTxtMenuItemData(IBase* pThis, WdgDynamicMenuItemPtr_t *pMenuItem, u32 u32MenuItemID, u8 u8DualID, u32 nTextID, u32 imgID);

/**
* MMI_Common_Dual_Select_Free_STextMenuItemData
* @brief		To free menu item data.
*
* @param	pData	The source data.
* @param	pOwner	The source owner.
* @retVal	        void.
*/
void _FreeTwoLineImageTextMenuItemData(void *pData, IBase *pOwner);


/**
* FreeImgDoubleTxtMenuItemData
* @brief		To free menu item data.
*
* @param	pData	The source data.
* @param	pOwner	The source owner.
* @retVal	        void.
*/
void FreeImgDoubleTxtMenuItemData(WdgDynamicMenuItemPtr_t *pItemDataPtr, HWIN hWin, WdgMenuItemType_e eItemType);

MAE_Ret MMI_Common_SetImgDoubleTxtMenuItemData(IBase* pThis, IWidget * pIMenu,u32 u32MenuItemID, u8 u8DualID, u32 nTextID, u32 imgID);
MAE_WChar MMI_Common_UpdateImgDoubleTxtMenuItemData(IBase* pThis, WdgDynamicMenuItemPtr_t *pMenuItem, u32 u32MenuItemID, u8 u8DualID, u32 nTextID, u32 imgID);

#endif /* __MMI_COMMON_UTIL_MENU_H__ */
