/**
 *
 * @brief   OptionMenu Widget is an AbsContainer which contains two MenuWidget for the double layer requirement.
 *          However, we do not wish to allow user to change the layout and containt, one can only query its widget
 *          interface. Currently OptionMenu widget only supports 12 items in each layer by the request of UI team.
 *          Only 5 items can be displayed simultaneously in Layer 1 and 3 items for Layer 2. The exceeding items will
 *          be accessable via scroll bar. Items will be automatically numbered in sequence for shortcut purpose.
 *          
 *          Layout:
 *          
 *          -------------
 *          |1         ||
 *          |2     ----------
 *          |3     |1      ||
 *          |4     |2      ||
 *          |5     |3      ||
 *          |----------------
 *          
 *          Steps to create a double layer OptionMenu:
 *
 *
 */
#ifndef __MMI_WDG_OPTIONMENU_H__
#define __MMI_WDG_OPTIONMENU_H__


/** 
*  WdgOptionMenuAddL1ViewMdlListener
*  \brief  Attach the Layer 1 ViewModelListener to OptionMenuWidget
*   
*  \param  pIOptionMenuWidget		Pointer to the IMenuWidget interface
*  \param  pMdlListener				Pointer to MdlListener
*
*  \retval 0			            Not handled
*  \retval 1			            Handled
*/
boolean WdgOptionMenuAddL1ViewMdlListener(IWidget *pIOptionMenuWidget, u32 pMdlListener);

/** 
*  WdgOptionMenuAddL2ViewMdlListener
*  \brief  Attach the Layer 2 ViewModelListener to OptionMenuWidget
*   
*  \param  pIOptionMenuWidget		Pointer to the IMenuWidget interface
*  \param  pMdlListener				Pointer to MdlListener
*
*  \retval 0			            Not handled
*  \retval 1			            Handled
*/ 
boolean WdgOptionMenuAddL2ViewMdlListener(IWidget *pIOptionMenuWidget, u32 pMdlListener);

/** 
*  WdgOptionMenuSetL1MenuModel
*  \brief  Set the Layer 1 MenuModel to OptionMenuWidget
*   
*  \param  pIOptionMenuWidget		Pointer to the IMenuWidget interface
*  \param  pMenuModel				Pointer to Layer 1 MenuModel
*
*  \retval 0			            Not handled
*  \retval 1			            Handled
*/
boolean WdgOptionMenuSetL1MenuModel(IWidget *pIOptionMenuWidget, u32 pMenuModel);

/** 
*  WdgOptionMenuSetL2MenuModel
*  \brief  Set the Layer 2 MenuModel to OptionMenuWidget
*   
*  \param  pIOptionMenuWidget		Pointer to the IMenuWidget interface
*  \param  pMenuModel				Pointer to Layer 2 MenuModel
*
*  \retval 0			            Not handled
*  \retval 1			            Handled
*/
boolean WdgOptionMenuSetL2MenuModel(IWidget *pIOptionMenuWidget, u32 pMenuModel);

#endif /*__MMI_WDG_OPTIONMENU_H__ */
