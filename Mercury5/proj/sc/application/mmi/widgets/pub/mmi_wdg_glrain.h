/**
 * @file    mae_glmenuwidget.h
 * @brief   This file defines the interface of 3D demo widget
 * @version $Id$
 */

#ifndef __MMI_WDG_GLRAIN_H__
#define __MMI_WDG_GLRAIN_H__

#include "mmi_mae_class.h"
#include "mmi_mae_widget.h"

#define IGLRAIN_QueryInterface(p,id,pp,pOwner)	IWIDGET_QueryInterface((IWidget*)p,id,pp,pOwner)
#define IGLRAIN_HandleEvent(p,e,p1,p2)			IWIDGET_HandleEvent((IWidget*)p,e,p1,p2)
#define IGLRAIN_SetHandler(p,pHD)				IWIDGET_SetHandler((IWidget*)p,pHD)

/*! @brief This function sets bitmap to given IGLRAIN
 *
 *  @param p     Pointer to the IGLRAIN
 *  @param p1    Pointer to the IBitmap to set to IGLRAIN
 *
 *  @return Always returns TRUE
 */
#define IGLRAIN_SetBitmap(p,p1) \
	WdgCommonSetProperty((IWidget*)p, PROP_BMP_WDG_BITMAP, (u32)p1)
	//IWIDGET_HandleEvent((IWidget*)p,EVT_WIDGET_SET_PROPERTY,PROP_BMP_WDG_BITMAP,(u32)p1)

/*! @brief This function sets alignment to the bitmap widget
 *
 *  @param p     Pointer to the IGLRAIN
 *  @param AF    alignment flag
 *
 *  @return Always returns TRUE
 *
 *  Note: pAF => u8
 */
#define IGLRAIN_SetAlignment(p,AF) \
	WdgCommonSetAlignment((IWidget*)p, AF)
	//IWIDGET_HandleEvent((IWidget *)p,EVT_WIDGET_SET_PROPERTY,PROP_WDG_ALIGNMENT,(u32)AF)

/*! @brief This function gets the alignment flag of the given bitmap widget
 *
 *  @param p     Pointer to the IGLRAIN
 *  @param pAF   Pointer to the memory to fill with alignment flag
 *
 *  @return Always returns TRUE
 *
 *  Note: pAF => u8 pointer
 */
#define IGLRAIN_GetAlignment(p,pAF) \
	WdgCommonGetAlignment((IWidget *)p, pAF)
	//IWIDGET_HandleEvent((IWidget *)p,EVT_WIDGET_GET_PROPERTY,PROP_WDG_ALIGNMENT,(u32)pAF)

#define IGLRAIN_SetLinkAddr(p_,pS) \
    WdgCommonSetProperty((IWidget*)p_, PROP_BMP_WDG_LINK_ADDR, (u32)pS)

#define IGLRAIN_GetLinkAddr(p_,pS) \
    WdgCommonGetProperty(p_, PROP_BMP_WDG_LINK_ADDR, (u32*)pS)

#define IGLRAIN_SetLinkState(p_,pS) \
    WdgCommonSetProperty((IWidget*)p_, PROP_BMP_WDG_LINKED_STATE, (u32)pS)

#define IGLRAIN_GetLinkState(p_,pS) \
    WdgCommonGetProperty(p_, PROP_BMP_WDG_LINKED_STATE, (u32*)pS)

IWidget* WdgGlRainCreate(void);

#endif /* __MAE_GLRAIN_H__ */
