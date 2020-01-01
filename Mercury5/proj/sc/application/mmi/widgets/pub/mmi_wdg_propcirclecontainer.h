/**
* @file    mmi_wdg_propcontainer.h
* @version $Id: mmi_wdg_propcontainer.h 38890 2009-08-29 16:22:38Z zinc.chen $
* @brief   This file defines the interface of IPropContainer
*/
#ifndef __MMI_WDG_PROPCIRCLECONTAINER_H__
#define __MMI_WDG_PROPCIRCLECONTAINER_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_window.h"
#include "mmi_mae_propcontainer.h"
#include "mmi_wdg_common_interface.h"

/*=============================================================*/
// interface
/*=============================================================*/
/** WdgPropCircleContainerCreateForWnd
* @brief        Create PropContainer Widget and set the PropContainer value for Window
*
* @param[in]    hWin        The window handle
* @param[in]    pPos           A pointer of widget position; can't be NULL.
* @param[in]    pSize          A pointer of widget size; NULL means default value.
* @param[in]    nWdgId         The widget unique ID of window
* @param[in]    nLayoutStyle   Layout Style

*
* @retval       The pointer of PropContainer     Success.
* @retval       NULL                             Failed.
*
*/
IWidget* WdgPropCircleContainerCreateForWnd
(
    HWIN               hWin,
    Pos_t                     *pPos,
    WidgetSize_t              *pSize,
    u16                        nWdgId,
    WdgLayoutStyle_t           nLayoutStyle
);

/*=============================================================*/
/** WdgPropCircleContainerCreate
* @brief        Create PropContainer widget
*
* @retval       The pointer of PropContainer  Success.
* @retval       NULL                          Failed.
*
*/
IWidget* WdgPropCircleContainerCreate
(
    void
);



#endif    //__MMI_WDG_PROPCIRCLECONTAINER_H__
/*=============================================================*/
// end of file
