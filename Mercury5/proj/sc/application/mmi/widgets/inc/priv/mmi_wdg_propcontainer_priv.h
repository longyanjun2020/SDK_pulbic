/**
* @file    mmi_wdg_propcontainer_priv.h
* @version $Id: mmi_wdg_propcontainer_priv.h 11657 2008-06-14 11:51:29Z paul.ouyang $
* @brief   This is the private header file for mmi_wdg_propcontainer.c
*/
#ifndef __MMI_WDG_PROPCONTAINER_PRIV_H__
#define __MMI_WDG_PROPCONTAINER_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_mae_interface_def.h"
#include "mae_propcontainerbase.h"
#include "mmi_wdg_propcontainer.h"


/*=============================================================*/
// type and define
/*=============================================================*/
///structure for a Proportional container
typedef struct {
	PropContainerBase_t    PropCntrBase;
} PropContainer_t;

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
//new function
MAE_Ret PropContainer_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ boolean WdgPropContainerDefHandleEvent(IPropContainer *pIPropContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
MAE_Ret WdgPropContainerConstructor(PropContainer_t *pThis);
void WdgPropContainerDestructor(PropContainer_t *pThis);
#endif //__MMI_WDG_PROPCONTAINER_PRIV_H__
/*=============================================================*/
// end of file

