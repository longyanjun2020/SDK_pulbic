/**
* @file    mmi_wdg_propcontainer_priv.h
* @version $Id: mmi_wdg_propcontainer_priv.h 11657 2008-06-14 11:51:29Z paul.ouyang $
* @brief   This is the private header file for mmi_wdg_propcontainer.c
*/
#ifndef __MMI_WDG_PROPCIRCLECONTAINER_PRIV_H__
#define __MMI_WDG_PROPCIRCLECONTAINER_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mae_propcontainerbase.h"
#include "mmi_wdg_propcirclecontainer.h"

#include "mgl_Scene_NodeMgr.h"
#include "mgl_Core_shape.h"
#include "mgl_Scene_Environment.h"
#include "mgl_Egl.h"
#include "mgl_core_types.h"
#include "mgl_utility_common.h"

#include "mmi_common_util.h"
#include "mmi_cfgsrv.h"
//#include "mmi_cfgsrv_shortcuts.h"

/*=============================================================*/
// type and define
/*=============================================================*/
///structure for a Proportional container
typedef struct {
	PropContainerBase_t    PropCntrBase;

	mgl_u16 u16SceneHandleId;
	mgl_u32 u32ShortcutNodeID;

} PropCircleContainer_t;

///structure of widget cell used in PropContainer
typedef struct PropCircleWidgetCell_Tag {
	WidgetCell_t    WCellBase;
	s16             Proportion;         //> keep the proportion of this widget
	u16             nBeforePadding;     //> padding pixels before this widget
	u16             nAfterPadding;      //> padding pixels after this widget

    u32             u32ItemTextureId; // a MGL texture id
} PropCirlceWidgetCell_t;

enum
{
    PROPCIRCLECONTAINER_ALIGNMENT_UP,
    PROPCIRCLECONTAINER_ALIGNMENT_DOWN,
};
typedef u16 PropCircleContainer_Alignment_e;


/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
//new function
MAE_Ret PropContainer_New(MAE_ClsId ClsID, void **ppObj);
boolean WdgPropCircleContainerDefHandleEvent(IPropContainer *pIPropContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret WdgPropCircleContainerConstructor(PropCircleContainer_t *pThis);
void WdgPropCircleContainerDestructor(PropCircleContainer_t *pThis);
#endif //__MMI_WDG_PROPCIRCLECONTAINER_PRIV_H__
/*=============================================================*/
// end of file

