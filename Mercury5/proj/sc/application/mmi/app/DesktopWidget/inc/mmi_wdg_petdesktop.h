/**
* @file    mmi_wdg_petdesktop.h
* @brief   This file defines the interface of PetDesktopwidget.

*/

#ifndef __MMI_WDG_PETDESKTOP_H__
#define __MMI_WDG_PETDESKTOP_H__

#include "mmi_mae_class.h"
#include "mmi_wdg_petdesktop_priv.h"
#include "mmi_wdg_headers.h"

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)
#ifdef __GADGETS_MMI_PET__

/*************************************************************************/
/*   For IBase Interface                                                 */
/*************************************************************************/
static u32 PetDesktopWidget_Release(IAbsContainer*);

/*************************************************************************/
/*   For IWidget interface                                               */
/*************************************************************************/

/*************************************************************************/
/*   Other Local Functions                                               */
/*************************************************************************/
static MAE_Ret PetDesktopWidget_Ctor(PetDesktopWdg_t*);
static void PetDesktopWidget_Dtor(PetDesktopWdg_t*);

static boolean PetDesktopWidget_DefHandleEvent(IAbsContainer*, MAEEvent_t, u32, u32);
static boolean PetDesktopWidget_SetProperty(PetDesktopWdg_t*, u32, u32);
static boolean PetDesktopWidget_GetProperty(PetDesktopWdg_t*, u32, u32);
static boolean PetDesktopWidget_HandleTouchEvent(PetDesktopWdg_t*, MAE_EventId, u32, u32);

//static void PetDesktopWidget_ButtonModelListener(void*, ModelEvent_t*);
static void PetDesktopWidget_Init(PetDesktopWdg_t* pThis);
static void PetDesktopWidget_ShowLargeWdg(void *pData);
static void PetDesktopWidget_ShowSmallWdg(void *pData);

#endif //__GADGETS_MMI_PET__
#endif //defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)
#endif //__MMI_WDG_PETDESKTOP_H__
/*=============================================================*/
// end of file
