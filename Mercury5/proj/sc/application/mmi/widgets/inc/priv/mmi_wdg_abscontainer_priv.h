
/*=============================================================
File name: mmi_wdg_abscontainer_priv.h
Description:
=============================================================*/
#ifndef __MMI_WDG_ABSCONTAINER_PRIV_H__
#define __MMI_WDG_ABSCONTAINER_PRIV_H__

/*=============================================================*/
// include
/*=============================================================*/
//#include "mmi_mae_common_def.h"
//#include "mmi_mae_interface_def.h"
#include "mae_abscontainerbase.h"


/*=============================================================*/
// type and define
/*=============================================================*/
//structure for a abs-container
typedef struct {
	AbsContainerBase_t AbsCntrBase;
} AbsContainer_t;

/*=============================================================*/
// functions
/*=============================================================*/

/*=============================================================*/
// New function and Event handler
/*=============================================================*/
MAE_Ret AbsContainer_New(MAE_ClsId ClsID, void **ppObj);
__SLDPM_FREE__ boolean WdgAbsContainerDefHandleEvent(IAbsContainer *pIAbsContainer, MAE_EventId evt, u32 P1, u32 P2);

/*=============================================================*/
// Non-interface functions
/*=============================================================*/
static MAE_Ret WdgAbsContainerCtor(AbsContainer_t *pThis);
static void WdgAbsContainerDtor(AbsContainer_t *pThis);

#endif //__MMI_WDG_ABSCONTAINER_PRIV_H__
/*=============================================================*/
// end of file

