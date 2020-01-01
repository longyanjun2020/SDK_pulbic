/**
* @file    mmi_infodesktopwidget.h
* @brief   This file defines the interface of mp desktopwidget.

*/

#ifndef __MAE_INFODESKTOPWIDGET_H__
#define __MAE_INFODESKTOPWIDGET_H__

#include "mmi_mae_class.h"
#include "mmi_mae_widget.h"
#include "mmi_wdg_infodesktopwidget_priv.h"

#if defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)
/*************************************************************************/
/*   For IBase Interface                                                 */
/*************************************************************************/
static u32 InfoDesktopWidget_Release(IAbsContainer*);

/*************************************************************************/
/*   For IWidget interface                                               */
/*************************************************************************/
//static void DesktopWidget_Draw(IAbsContainer*, IDispCanvas*, s32, s32);

/*************************************************************************/
/*   Other Local Functions                                               */
/*************************************************************************/
static MAE_Ret InfoDesktopWidget_Ctor(InfoDesktopWdg_t*);
static void InfoDesktopWidget_Dtor(InfoDesktopWdg_t*);
static boolean InfoDesktopWidget_SetProperty(InfoDesktopWdg_t*, u32, u32);
static boolean InfoDesktopWidget_GetProperty(InfoDesktopWdg_t*, u32, u32);

static boolean InfoDesktopWidget_DefHandleEvent(IAbsContainer*, MAEEvent_t, u32, u32);

static MAE_Ret InfoDesktopWidget_UpdateTitle(InfoDesktopWdg_t*);

static void InfoDesktopWidget_ShowLargeWdg(void* pData);
static void InfoDesktopWidget_ShowSmallWdg(void* pData);
static MAE_Ret InfoDesktopWidget_SetStyle(InfoDesktopWdg_t *pThis);




#endif //defined(__GADGETS_MMI__) || defined(__3D_UI_IDLE_GADGETBAR__)
#endif //__MAE_INFODESKTOPWIDGET_H__
/*=============================================================*/
// end of file
