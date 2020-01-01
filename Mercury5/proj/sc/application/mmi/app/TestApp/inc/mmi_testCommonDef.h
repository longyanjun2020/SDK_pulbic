/**
* @file mmi_testCommonDef.h
*/
#ifndef __MMI_TESTCOMMONDEF_H__
#define __MMI_TESTCOMMONDEF_H__

/*-------------------------------------------------------------------------*/

#include "mmi_mae_common_def.h"
#include "mmi_mae_applet.h"
#include "mmi_mae_class.h"
#include "mmi_wdg_abscontainer.h"
#include "mmi_mae_datamodel.h"
#include "mmi_mae_log.h"
#include "mmi_log.h"
#include "mmi_wdg_basicdesktop.h"
#include "mmi_wdg_calendardesktop.h"
#include "mmi_wdg_dclockdesktop.h"
#include "mmi_wdg_fmdesktop.h"
#include "mmi_wdg_mpdesktop.h"
#include "mmi_wdg_notedesktop.h"
#include "mmi_wdg_opdesktop.h"
#include "mmi_wdg_searchdesktop.h"
#include "mmi_wdg_profile.h"
#include "mmi_wdg_headers.h"
#include "mmi_mae_window.h"
#include "img_data.h"

/*-------------------------------------------------------------------------*/
//typedef MAE_Ret (*UTWidget_Create) (IAbsContainer* , IWidget** , u32 , WidgetSize_t* , WPos_t*, HWIN, u16 );

typedef MAE_Ret (*UTWidget_Create) (IWidget**, u32, WidgetSize_t*, Pos_t*, HWIN, u16);
typedef MAE_Ret (*UTWidget_View) (IWidget*, u32, u32, IBase*);
typedef MAE_Ret (*UTWidget_ViewMenu) (IWidget**, u32, u32, IBase*);
typedef MAE_Ret (*UTWidget_Close) (IWidget*, u32, u32, IBase*);
#define MAX_TESTVIEW_NUM 7

#endif /* __MMI_TESTCOMMONDEF_H__ */
