/**
* @file    mmi_wdg_multipagecontainer.h
* @version $Id: mmi_wdg_multipagecontainer.h
* @brief   This file defines the interface of MultipageContainer
*/
#ifndef __MMI_WDG_MULTIPAGECONTAINER_H__
#define __MMI_WDG_MULTIPAGECONTAINER_H__

#if defined(__FEATURE_MGL__) && defined(__3D_UI_IDLE_MULTIPAGE__)
/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_wdg_common_interface.h"

typedef enum
{
    MULTIPAGECONTAINER_SHIFT_NONE,

    MULTIPAGECONTAINER_SHIFT_LEFT,
    MULTIPAGECONTAINER_SHIFT_RIGHT,
}MultipageContainerShiftDirect_e;

/** PfnWdgMultipageContainerEventCB
* @brief
*
* @param[in]  pApplet           The instance of widget "Owner"(AP instance)
* @param[in]  pUsrData          User data ap developer setting when register CB.
* @param[in]  nEvtCode          Widget Event Code, only useful for softkey event
* @param[in]  param             Relative info
* @param[in]  pIWidget          The widget instance
*
*/
typedef void (*PfnWdgMultipageContainerEventCB) (void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 param, IWidget *pWidget);

/** WdgMultipageContainerRegisterEventCb
* @brief        Register callback
*
* @param[in]    pMultipageContainer     Pointer to the MultipageContainer
* @param[in]    pfn                     callback function
* @param[in]    pUserData               User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMultipageContainerRegisterEventCb
(
    IWidget                         *pMultipageContainer,
    PfnWdgMultipageContainerEventCB pfn,
    void                            *pUserData
);

/** WdgMultipageContainerDeregisterEventCb
* @brief        Deregister callback
*
* @param[in]    pWMultipageContainer    Pointer to the MultipageContainer
* @param[in]    pfn                     callback function
* @param[in]    pUserData               User Data can be gotten when CB trigger.
*
* @retval       MAE_RET_SUCCESS   Success
* @retval       others            Failed
*
*/
MAE_Ret WdgMultipageContainerDeregisterEventCb
(
    IWidget                         *pMultipageContainer,
    PfnWdgMultipageContainerEventCB pfn,
    void                            *pUserData
);

/*=============================================================*/
// interface
/*=============================================================*/
/** WdgMultipageContainerCreateForWnd
* @brief        Create MultipageContainer Widget and set the MultipageContainer value for Window.
*
* @param[in]    hWin        The window handle
* @param[in]    pPos                A pointer of widget position; can't be NULL.
* @param[in]    pOnePageSize        A pointer of widget size; NULL means default value.
* @param[in]    nTotalPageNumber    The count of the page
* @param[in]    nWdgId              The widget unique ID of window

*
* @retval       The pointer of MultipageContainer     Success.
* @retval       NULL                                  Failed.
*
*/
IWidget* WdgMultipageContainerCreateForWnd
(
    HWIN               hWin,
    Pos_t              *pPos,
    WidgetSize_t       *pOnePageSize,
    u8                 nTotalPageNumber,
    u16                nWdgId
);

/*=============================================================*/
/** WdgMultipageContainerCreate
* @brief        Create MultipageContainer widget.
*
* @retval       The pointer of MultipageContainer  Success.
* @retval       NULL                               Failed.
*
*/
IWidget* WdgMultipageContainerCreate
(
    void
);



/*=============================================================*/

/** WdgMultipageContainerGetLayoutInverseByLanguage
* @brief        Get the widget layout in container right-to-left or left-to-right. (compatible to WdgAbsContainer)
*
* @param[in]    pMultipageContainer    The pointer of MultipageContainer
*
* @retval       boolean    Layout inverse by language (TRUE or FALSE)
*
*/
boolean WdgMultipageContainerGetLayoutInverseByLanguage
(
    IWidget             *pMultipageContainer
);

/**
* WdgMultipageContainerGetFocusedWdg
* @brief    This function can get the focused widget object instance in MultipageContainer. (compatible to WdgAbsContainer)
*
* @param    pMultipageContainer  The pointer of MultipageContainer.
*
* @retval   MAE_RET_SUCCESS     Success. The widget can handle this request.
* @retval   MAE_RET_FAILED      Failed. The widget can not handle this request.
* @retval   MAE_RET_BAD_PARAM   Failed. Invalid parameters.
*/
IWidget* WdgMultipageContainerGetFocusedWdg
(
    IWidget             *pMultipageContainer
);

void WdgMultipageContainerSetSize
(
    IWidget      *pMultipageContainer, 
    u8           nTotalPageNumber,
    WidgetSize_t *pOnePageSize
);

void WdgMultipageContainerStartAnimation
(
    IWidget     *pMultipageContainer,
    boolean     bFastAnimation
);

void WdgMultipageContainerStopAnimation
(
    IWidget     *pMultipageContainer
);

MultipageContainerShiftDirect_e WdgMultipageContainerGetAnimationDirection
(    
    IWidget     *pMultipageContainer
);

void WdgMultipageContainerAnimationManualSetFrame
(
    IWidget     *pMultipageContainer,
    u32         u32AnimationFrame
);

MAE_Ret WdgMultipageContainerGetFocusPageNumber
(
    IWidget     *pMultipageContainer,
    u8          *nCurrentPageNumber
);

MAE_Ret WdgMultipageContainerSetFocusPageNumber
(
    IWidget     *pMultipageContainer,
    u8          nCurrentPageNumber
);

MAE_Ret WdgMultipageContainerSetTurnPageDirection
(
    IWidget                         *pMultipageContainer,
    MultipageContainerShiftDirect_e eDirection
);

MAE_Ret WdgMultipageContainerCalcAlignedPos
(
    IWidget         *pMultipageContainer,
    IWidget         *pWidget,
    const WPos_t    *pPos,
    WPos_t          *pAlignedPos
);

MAE_Ret WdgMultipageContainerCalcAlignedPosOrigin
(
    IWidget         *pMultipageContainer,
    IWidget         *pWidget,
    const WPos_t    *pPos,
    WPos_t          *pAlignedPos
);

MAE_Ret WdgMultipageContainerCalcWdgSizeOnPage
(
    IWidget         *pMultipageContainer,
    IWidget         *pWidget,
    WidgetSize_t    *pWdgSize,
    WidgetSize_t    *pSizeOnPage
);

MAE_Ret WdgMultipageContainerCalcAbsolutePosInCurPage
(
    IWidget         *pMultipageContainer,
    IWidget         *pWidget,
    const WPos_t    *pPos,
    WPos_t          *pCurPagePos
);

MAE_Ret WdgMultipageContainerCalcNonOverlapPos
(
    IWidget         *pMultipageContainer,
    IWidget         *pWidget,
    const WPos_t    *pPos,
    boolean         bNeedToFind,
    WPos_t          *pNonOverlapPos
);
MAE_Ret WdgMultipageContainerSetAlignedPos
(
    IWidget         *pMultipageContainer,
    IWidget         *pWidget,
    const WPos_t    *pPos
);

MAE_Ret WdgMultipageContainerSetRelativePosToCurPage
(
    IWidget         *pMultipageContainer,
    IWidget         *pWidget,
    const WPos_t    *pPos
);

MAE_Ret WdgMultipageContainerGetRelativePos
(
    IWidget         *pMultipageContainer,
    IWidget         *pWidget,
    WPos_t          *pPos
);

MAE_Ret WdgMultipageContainerGetPageShiftOffset
(
    IWidget         *pMultipageContainer,
    u8              u8Page,
    WPos_t          *pPos
);

boolean WdgMultipageContainerIsEmptyForAddWdg
(
    IWidget         *pMultipageContainer,
    IWidget         *pWidget,
    const Rect_t    *pMoveWdgRect
);

boolean WdgMultipageContainerSearchEmptySlotOnPage
(
    IWidget         *pMultipageContainer,
    IWidget         *pWidget,
    u8              nPageIdx,
    Rect_t          *pMoveWdgRect,
    WPos_t          *pWPos
);

#endif    //__FEATURE_MGL__ && __3D_UI_IDLE_MULTIPAGE__
#endif    //__MMI_WDG_MULTIPAGECONTAINER_H__
/*=============================================================*/
// end of file
