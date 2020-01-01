/**
* @file    mmi_wdg_rootcontainer.h
* 
* @version $Id: mmi_wdg_rootcontainer.h 20863 2009-01-19 10:59:56Z paul.ouyang $
*/
#ifndef __MAE_ROOTCONTAINER_H__
#define __MAE_ROOTCONTAINER_H__


/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_abscontainer.h"
#include "mmi_mae_dispcanvas.h"

/*=============================================================*/
// interface functions
/*=============================================================*/
//set dispcanvas
void RootContainer_SetDispCanvas(IAbsContainer *pIRootContainer, IDispCanvas *pIDispCanvas, const Rect_t *pRect, IBase* pOwner);

//get dispcanvas
MAERet_t RootContainer_GetDispCanvas(IAbsContainer *pIRootContainer, IDispCanvas **ppIDispCanvas, Rect_t *pRect, IBase* pOwner);

//Add a lifting widget
MAERet_t RootContainer_AddLiftingWidget(IAbsContainer *pIRootContainer, IWidget *pWidget, WPos_t *pstWPos);

//Delete a lifting widget
MAERet_t RootContainer_DelLiftingWidget(IAbsContainer *pIRootContainer, IWidget *pWidget);


#endif	//__MAE_ROOTCONTAINER_H__
/*=============================================================*/
// end of file
