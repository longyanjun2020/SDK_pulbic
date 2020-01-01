
#ifndef __DISP_CTRL_H__
#define __DISP_CTRL_H__

#include "msgdidef.h"

#ifdef INTERFACE
#undef INTERFACE
#endif

#ifdef __DISP_CTRL_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif


//# Feature_Name = Using double buffer in OSD layer.
//# Description = If this option is set, double buffer is used in OSD layer.
#ifdef __LCM_ROTATE_MDL__
#define __DISP_CTRL_DB__
#else
//#define __DISP_CTRL_DB__
#endif

INTERFACE void DispCtrlInit(void);
INTERFACE s32  DispUpdateScreenMdl(u32 nPanelID, PMSUPDATELAYER pParam);
INTERFACE s32  DispUpdateScreenAppEx(u32 nPanelID, PMSUPDATE pParam);
INTERFACE s32  DispUpdateScreenApp(u32 nPanelID, PMSUPDATELAYER pParam);
INTERFACE u32  DispEnableMdlScreenLayer(u32 nPanelID, bool bEnable);
INTERFACE u32  DispSetMdlScreenCtrl(u32 nPanelID, bool bCtrlByMdl);
INTERFACE u32  DispDisableMdlScreenOSD(u32 nPanelID, bool bDisable);
INTERFACE bool DispIsMdlScreenLayerEnable(u32 nPanelID);
INTERFACE bool DispIsMdlScreenCtrl(u32 nPanelID);
INTERFACE bool DispIsMdlScreenDisableOSD(u32 nPanelID);
INTERFACE void DispLCDTest(u8 refresh_mmi, u16 color);
INTERFACE void DispLCDOnOff(bool OnOff);
INTERFACE void DispLCDPartialUpdateScreen(u16 x, u16 y, u16 w, u16 h, u16 *pixel, u32 len);

#endif//__DISP_CTRL_H__
