/**
* @file    mae_abscontainerbase.h
*
* @brief   This file defines IAbsContainer interface.
**/

#ifndef __MAE_ABSCONTAINERBASE_H__
#define __MAE_ABSCONTAINERBASE_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_abscontainer.h"
#include "mae_containerbase.h"

/*=============================================================*/
// type and define
/*=============================================================*/
// For new-style widget
// This structure is used for send Set/Get pos parameters
typedef struct WPosParam_Tag {
	MAE_Ret nRet;
    WPos_t wPos;
} WPosParam_t;

//structure for a abs-container
typedef struct {
	ContainerBase_t CntrBase;
} AbsContainerBase_t;

typedef struct AbsWidgetCell_Tag
{
    WidgetCell_t    WCellBase;
    s32  OriginalX;   
} AbsWidgetCell_t;

/*=============================================================*/
// functions
/*=============================================================*/
__SLDPM_FREE__ MAE_Ret AbsContainerBaseConstructor(AbsContainerBase_t *pThis, LAYOUT_FUNC_PTR pfnLayout);
void    AbsContainerBaseDestructor(AbsContainerBase_t *pThis);
__SLDPM_FREE__ boolean AbsContainerBaseDefHandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 P1, u32 P2);

/** AbsContainerBaseSetPos
* @brief        Set a widget to a position in the AbsContainer. 
*
* @param[in]    pIAbsContainer       The pointer of AbsContainer
* @param[in]    pWidget              A pointer of IWidget interface object to add
* @param[in]    WPosPtr              The position of widget
*
* @retval       MAE_RET_SUCCESS      Success.
* @retval       others               Failed.
*
*/
MAE_Ret AbsContainerBaseSetPos(IAbsContainer *pIAbsContainer, IWidget *pIWidget, const WPos_t *WPosPtr);

/** AbsContainerBaseGetPos
* @brief        Get a widget's position in the AbsContainer. 
*
* @param[in]    pIAbsContainer       The pointer of AbsContainer
* @param[in]    pWidget              A pointer of IWidget interface object to add
* @param[in]    WPosPtr              The position of widget
*
* @retval       MAE_RET_SUCCESS      Success.
* @retval       others               Failed.
*
*/
MAE_Ret AbsContainerBaseGetPos(IAbsContainer *pIAbsContainer, IWidget *pIWidget, WPos_t *WPosPtr);

/** AbsContainerBaseAddToTopMost
* @brief        Add a widget to top in the AbsContainer. 
*
* @param[in]    pIAbsContainer       The pointer of AbsContainer
* @param[in]    pWidget              A pointer of IWidget interface object to add
* @param[in]    pWPos                The position of widget
*
* @retval       MAE_RET_SUCCESS      Success.
* @retval       others               Failed.
*
*/
MAE_Ret AbsContainerBaseAddToTopMost
(
    IAbsContainer   *pIAbsContainer,
    IWidget         *pWidget,
    WPos_t          *pWPos
);

/** AbsContainerBaseAddToBottomMost
* @brief        Add a widget to top in the AbsContainer. 
*
* @param[in]    pIAbsContainer       The pointer of AbsContainer
* @param[in]    pWidget              A pointer of IWidget interface object to add
* @param[in]    pWPos                The position of widget
*
* @retval       MAE_RET_SUCCESS      Success.
* @retval       others               Failed.
*
*/
MAE_Ret AbsContainerBaseAddToBottomMost
(
    IAbsContainer   *pIAbsContainer,
    IWidget         *pWidget,
    WPos_t          *pWPos
);

/*=============================================================*/
// For backward compatibility functions
/*=============================================================*/
//These functions are open for old interface style widgets, please do not use in new event style widgets
MAE_Ret AbsContainerBaseQueryInterface (IAbsContainer *pIAbsContainer, MAE_IId iId, void **ppObj, IBase *pOwner);
void AbsContainerBaseGetPreferredSize(IAbsContainer *pIAbsContainer, WidgetSize_t *pSize);

#endif	//__MAE_ABSCONTAINERBASE_H__
/*=============================================================*/
// end of file
