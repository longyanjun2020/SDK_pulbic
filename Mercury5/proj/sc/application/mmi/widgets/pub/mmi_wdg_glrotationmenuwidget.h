/**
 * @file    mae_glrorationmenuwidget.h
 * @brief   This file defines the interface of 3D rotation menu widget
*<Class Description>
*    Text Widget is a widget for display a string text. ...[NOT FINISHED]...
*
*    Additionally, Text Widget supports background color, background image, border and padding.
*    For background functionality, please refer to IWIDGET_SetBGColor(), IWIDGET_SetBGImage() and 
*    IWIDGET_SetBGPosition(). For border and padding functionalities, please refer to IWIDGET_SetBorder(),
*    IWIDGET_SetBorderColor() and IWIDGET_SetPadding().
*
*    Text widget also supports to record a linking information(u16 type string) using ITEXTWIDGET_SetLinkAddr().
*    A touch on this widget will trigger a notice event. Applet should register a listening handler to receive the event,
*    and to get the linking information(u16 type string) using ITEXTWIDGET_GetLinkAddr(). Applet also can change the
*    link state using ITEXTWIDGET_SetLinkState(). This Linked state property only for applet to keep the linked state.
*    Applet can use this property to keep the linked state and display different text color if applet need to defferent
*    the linking is be touched or not.
*
*<Class ID>
*    CLSID_GLROTATIONMENUWIDGET.
*
*<Supported Interface>
*    IWidget
*
*<Events Handle> The widget handles following events:
*<pre>
*    =======================
*    EVT_WIDGET_SET_PROPERTY:    The widget handles this event by attempting to set the following properties.
*        -----------------------
*        PROP_ROTATIONMENU_WDG_VIEWANGLE:...Camera angle along X axis...
*        -----------------------
*        PROP_MENU_WDG_STARTUP_ANIM:...Specify startup animation, normal or restore style
*        -----------------------
*        PROP_ROTATIONMENU_WDG_RADIUS ..Specify the radius of the ring.
*        -----------------------
*        PROP_ROTATIONMENU_WDG_TEXT_EFFECT ..Specify displaying text or not. 
*        -----------------------
*        PROP_ROTATIONMENU_WDG_ITEMSIZE ..Specify the size of the menu node.
*        -----------------------
*        PROP_ROTATIONMENU_WDG_ALPHA_EFFECT ..Specify the alpha paramter.
*        -----------------------
*        PROP_ROTATIONMENU_WDG_MIRROR_EFFECT ..Specify the mirror paramter.
*        -----------------------
*        PROP_ROTATIONMENU_WDG_LOCK_ITEM .. If locked, all menu faces to front.
*        -----------------------
*    EVT_WIDGET_GET_PROPERTY:    The widget handles this event by attempting to get the following properties
*        -----------------------
*        PROP_ROTATIONMENU_WDG_VIEWANGLE:... Get camera angle along X axis...
*        -----------------------
*        PROP_MENU_WDG_STARTUP_ANIM:... Read the setting of startup animation, normal or restore style
*        -----------------------
*        PROP_ROTATIONMENU_WDG_RADIUS .. Read the radius of the ring.
*        -----------------------
*        PROP_ROTATIONMENU_WDG_TEXT_EFFECT ..Specify displaying text or not. 
*        -----------------------
*        PROP_ROTATIONMENU_WDG_ITEMSIZE ..Specify the size of the menu node.
*        -----------------------
*        PROP_ROTATIONMENU_WDG_ALPHA_EFFECT ..Specify the alpha paramter
*        -----------------------
*        PROP_ROTATIONMENU_WDG_MIRROR_EFFECT ..Specify the mirror paramter.
*        -----------------------
*        PROP_ROTATIONMENU_WDG_LOCK_ITEM .. If locked, all menu faces to front.

*</pre>
*
*<View Model Event>
*<pre>
*    =======================
*    EVT_MENUWIDGET_SELECT: Item selected
*    ...[NOT FINISHED]...
*</pre>
*
*<Supported Model>
*    IVectorModel. 
*
*<Model Data>
*    ...[NOT FINISHED]...
* 
*/


#ifndef __MMI_WDG_GLROTATIONMENUWIDGET_H__
#define __MMI_WDG_GLROTATIONMENUWIDGET_H__

#include "mmi_mae_class.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_interfacemodel.h"
#include "mmi_mae_window.h"


/* 3DMENU: Add widget's user-defined interface here. */

#define PROP_ADD_ANGLE 0xFF000000
#define PROP_REDUCE_ANGLE 0xFF000001
#define PROP_ADD_OFFSET 0xFF000002
#define PROP_REDUCE_OFFSET 0xFF000003
#define PROP_PREV_ITEM 0xFF000004
#define PROP_NEXT_ITEM 0xFF000005
#define PROP_NEXT_EFFECT 0xFF000006
#define PROP_PREV_EFFECT 0xFF000007



/* For development use only.
#define IGLROTATIONMENUWIDGET_AddOffset(p_) \
		WdgCommonSetProperty((IWidget*)p_, PROP_ADD_OFFSET, 0)
	
#define IGLROTATIONMENUWIDGET_ReduceOffset(p_) \
		WdgCommonSetProperty((IWidget*)p_, PROP_REDUCE_OFFSET, 0)


#define IGLROTATIONMENUWIDGET_NEXT_EVENT(p_) \
		WdgCommonSetProperty((IWidget*)p_, PROP_NEXT_EFFECT, 0)
	
#define IGLROTATIONMENUWIDGET_PREV_EVENT(p_) \
		WdgCommonSetProperty((IWidget*)p_, PROP_PREV_EFFECT, 0)
// IGLROTATIONMENUWIDGET_ENABLE_STARTUP_ANIM EVT_WIDGET_ACTIVE

*/

#define IGLROTATIONMENUWIDGET_PREV_ITEM(p_) \
		WdgCommonSetProperty((IWidget*)p_, PROP_PREV_ITEM, 0)
	
#define IGLROTATIONMENUWIDGET_NEXT_ITEM(p_) \
		WdgCommonSetProperty((IWidget*)p_, PROP_NEXT_ITEM, 0)

#define IGLROTATIONMENUWIDGET_SetStartupAnimation(p_, value) \
		WdgCommonSetProperty((IWidget*)p_, PROP_MENU_WDG_STARTUP_ANIM, value)
	
#define IGLROTATIONMENUWIDGET_SetHighlightItem(p_, index) \
		WdgCommonSetProperty((IWidget*)p_, PROP_MENU_WDG_HIGHLIGHTED_INDEX, index)


/*! 
 *  @fn IGLROTATIONMENUWIDGET_SetViewAngle
 *  @brief  This function set the camera angle along X axis 
 *  @param p     Pointer to the IGlMenuWidget
 *  @param angle  A degree from 0~359
 *
 *  @return Always returns TRUE
 *
 */

#define IGLROTATIONMENUWIDGET_SetViewAngle(pWdg, angle) \
    WdgCommonSetProperty((IWidget*)pWdg, PROP_ROTATIONMENU_WDG_VIEWANGLE, angle)

/*!IGLROTATIONMENUWIDGET_GetViewAngle 
 *  @brief  This function set the camera angle along X axis 
 *  @param p     Pointer to the IGlRotationMenuWidget
 *  @param angle  Reference to u32, will obtain a degree from 0~359
 *
 *  @return Always returns TRUE
 *
 */

#define IGLROTATIONMENUWIDGET_GetViewAngle(pWdg, angle) \
    WdgCommonGetProperty((IWidget*)pWdg, PROP_ROTATIONMENU_WDG_VIEWANGLE, angle)


/*!IGLROTATIONMENUWIDGET_SetRingRadius 
 *  @brief  This function set the radius of the menu ring
 *  @param p     Pointer to the IGlRotationMenuWidget
 *  @param radius  U32 length
 *
 *  @return Always returns TRUE
 *
 */

#define IGLROTATIONMENUWIDGET_SetRingRadius(pWdg, radius) \
    WdgCommonSetProperty((IWidget*)pWdg, PROP_ROTATIONMENU_WDG_RADIUS, radius)


/*!IGLROTATIONMENUWIDGET_GetRingRadius 
 *  @brief  This function get the radius of the menu ring
 *  @param p     Pointer to the IGlRotationMenuWidget
 *  @param radius  Reference to u32, will obtain the radius length
 *
 *  @return Always returns TRUE
 *
 */
 

#define IGLROTATIONMENUWIDGET_GetRingRadius(pWdg, radius) \
		WdgCommonGetProperty((IWidget*)pWdg, PROP_ROTATIONMENU_WDG_RADIUS, radius)


/*! @brief  This function set the startup animation 
 *              If it is enabled before receiving EVT_WIDGET_ACTIVE, startup anim is shown.
 *  @param p     Pointer to the IGlRotationMenuWidget
 *  @param anim  MENUWIDGET_STARTUP_ANIM_STYLE_NORMAL: Normal startup animation when widget first launched.
 *                      MENUWIDGET_STARTUP_ANIM_STYLE_RESTORE: If user has made selection and it shows launching effects,
 *                                                                                       we need to show restoring animation.
 *
 *  @return Always returns TRUE
 *
 */


#define IGLROTATIONMENUWIDGET_SetStartupAnim(pWdg, anim) \
		WdgCommonSetProperty((IWidget*)pWdg, PROP_MENU_WDG_STARTUP_ANIM, anim)
	
#define IGLROTATIONMENUWIDGET_GetStartupAnim(pWdg, anim) \
		WdgCommonGetProperty((IWidget*)pWdg, PROP_MENU_WDG_STARTUP_ANIM, anim)


/*!@fn   IGLROTATIONMENUWIDGET_SetTextEffect
*   @brief  This function set the text effect of this menu
 *              If it is enabled before receiving EVT_WIDGET_ACTIVE, startup anim is shown.
 *  @param p     Pointer to the IGlRotationMenuWidget
 *  @param bOnOff  TRUE: Enable
 *                         FALSE: Disable
 *
 *  @return Always returns TRUE
 *
 */


#define IGLROTATIONMENUWIDGET_SetTextEffect(pWdg, bOnOff) \
		WdgCommonSetProperty((IWidget*)pWdg, PROP_ROTATIONMENU_WDG_TEXT_EFFECT, bOnOff)

/*!@fn   IGLROTATIONMENUWIDGET_GetTextEffect
*   @brief  This function set the text effect of this menu
 *              If it is enabled before receiving EVT_WIDGET_ACTIVE, startup anim is shown.
 *  @param p     Pointer to the IGlRotationMenuWidget
 *  @param bOnOff  Reference to boolean, will obtain the the value of this property.
 *
 *  @return Always returns TRUE
 *
 */
 
#define IGLROTATIONMENUWIDGET_GetTextEffect(pWdg, bOnOff) \
		WdgCommonGetProperty((IWidget*)pWdg, PROP_ROTATIONMENU_WDG_TEXT_EFFECT, bOnOff)


/*!@fn   IGLROTATIONMENUWIDGET_SetTextItemSize
*   @brief  This function set the size of menu node.
 *  @param p     Pointer to the IGlRotationMenuWidget
 *  @param pSize  A reference to WidgetSize_t
 *
 *  @return Always returns TRUE
 *
 */


#define IGLROTATIONMENUWIDGET_SetTextItemSize(pWdg, pSize) \
		WdgCommonSetProperty((IWidget*)pWdg, PROP_ROTATIONMENU_WDG_ITEMSIZE, pSize)

/*!@fn   IGLROTATIONMENUWIDGET_GetTextItemSize
*   @brief  This function get the size of menu node.
 *  @param p     Pointer to the IGlRotationMenuWidget
 *  @param pSize  A reference to WidgetSize_t
 *  @return Always returns TRUE
 *
 */
 
#define IGLROTATIONMENUWIDGET_GetTextItemSize(pWdg, pSize) \
		WdgCommonGetProperty((IWidget*)pWdg, PROP_ROTATIONMENU_WDG_ITEMSIZE, pSize)

/*!@fn   IGLROTATIONMENUWIDGET_SetAlphaEffect
*   @brief  This function set the parameter of alpha.
 *  @param p     Pointer to the IGlRotationMenuWidget
 *  @param alpha  (Float) A alpha value from 0.0 ~ 1.0. 
 *
 *  @return Always returns TRUE
 *
 */


#define IGLROTATIONMENUWIDGET_SetAlphaEffect(pWdg, alpha) \
		WdgCommonSetProperty((IWidget*)pWdg, PROP_ROTATIONMENU_WDG_ALPHA_EFFECT, alpha)

/*!@fn   IGLROTATIONMENUWIDGET_GetAlphaEffect
*   @brief  This function get the parameter of alpha.
 *  @param p     Pointer to the IGlRotationMenuWidget
 *  @param alpha  A reference to a alpha value with float type from 0.0 ~ 1.0. 
 *  @return Always returns TRUE
 *
 */
 
#define IGLROTATIONMENUWIDGET_GetAlphaEffect(pWdg, alpha) \
		WdgCommonGetProperty((IWidget*)pWdg, PROP_ROTATIONMENU_WDG_ALPHA_EFFECT, alpha)

/*!@fn   IGLROTATIONMENUWIDGET_SetMirrorEffect
*   @brief  This function set the parameter of mirror.
 *  @param p     Pointer to the IGlRotationMenuWidget
 *  @param alpha  (Float) A mirror value from 0.0 ~ 1.0. 
 *
 *  @return Always returns TRUE
 *
 */


#define IGLROTATIONMENUWIDGET_SetMirrorEffect(pWdg, mirror) \
		WdgCommonSetProperty((IWidget*)pWdg, PROP_ROTATIONMENU_WDG_MIRROR_EFFECT, mirror)

/*!@fn   IGLROTATIONMENUWIDGET_GetAlphaEffect
*   @brief  This function get the parameter of alpha.
 *  @param p     Pointer to the IGlRotationMenuWidget
 *  @param alpha  A reference to a mirror value with float type from 0.0 ~ 1.0. 
 *  @return Always returns TRUE
 *
 */
 
#define IGLROTATIONMENUWIDGET_GetMirrorEffect(pWdg, mirror) \
		WdgCommonGetProperty((IWidget*)pWdg, PROP_ROTATIONMENU_WDG_MIRROR_EFFECT, mirror)

/*!@fn   IGLROTATIONMENUWIDGET_SetLockItem
*   @brief  This function set the lock item paramter.
 *  @param p     Pointer to the IGlRotationMenuWidget
 *  @param bOnOff  TRUE: If locked, all menu faces to front.
 *                         FALSE: Make rotation together with the circle.
 *
 *  @return Always returns TRUE
 *
 */


#define IGLROTATIONMENUWIDGET_SetLockItem(pWdg, bOnOff) \
		WdgCommonSetProperty((IWidget*)pWdg, PROP_ROTATIONMENU_WDG_LOCK_ITEM, bOnOff)

/*!@fn   IGLROTATIONMENUWIDGET_GetLockItem
*   @brief  This function get the lock item paramter.
 *  @param p     Pointer to the IGlRotationMenuWidget
 *  @param bOnOff  Reference to boolean, will obtain the the value of this property.
 *
 *  @return Always returns TRUE
 *
 */
 
#define IGLROTATIONMENUWIDGET_GetLockItem(pWdg, bOnOff) \
		WdgCommonGetProperty((IWidget*)pWdg, PROP_ROTATIONMENU_WDG_LOCK_ITEM, bOnOff)
		

/* 3DMENU: End of user-defined interface */

IWidget* WdgGlRotationMenuCreate(void);
IWidget* WdgGlRotationMenuCreateForWnd(HWIN hWin,Pos_t *pPos,WidgetSize_t *pSize,u16 nWidgetID);

typedef void (*PfnWdgGlRotationMenuFocusChange) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

MAE_Ret WdgGlRorationMenuRegisterFocusChangedCb(IWidget *pWDGMenu, PfnWdgGlRotationMenuFocusChange pfn, void *pUserData);
MAE_Ret WdgGlRorationMenuDeregisterFocusChangedCb(IWidget *pWDGMenu, PfnWdgGlRotationMenuFocusChange pfn, void *pUserData);

#endif /* __MAE_GLROTATIONMENUWIDGET_H__ */
