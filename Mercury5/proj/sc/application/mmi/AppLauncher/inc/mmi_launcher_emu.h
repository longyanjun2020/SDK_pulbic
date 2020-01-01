#ifndef __LAUNCHER_EMU_H__
#define __LAUNCHER_EMU_H__

#include "mmi_launcher_common.h"
#include "mmi_common_emu.h"

/// 1. FileManager App,        APM_Mode = APM_LAUNCH_EMBEDDED,     param = SRV_CHAR[MAX_FILE_PATH]

typedef enum {
    LAUNCH_EMU_MODE_PLAY = 1,
    LAUNCH_EMU_MODE_MENU
} EmuLaunchMode_e;

typedef enum {
    LAUNCH_EMU_MENU_HELP = 1,
    LAUNCH_EMU_MENU_SETTINGS,
    LAUNCH_EMU_MENU_KEYPAD_SETTINGS
} EmuMenuType_e;

typedef struct
{
    u32 nGameType;
    EmuLaunchMode_e eMode;
    u32 nID;
    MAE_WChar *pUrlStr;
} EmuLaunchAppParam_t;

typedef struct
{
    EmuAppGameType_e eEmuLaunchGameType;
    AppLaunchMode_e eLaunchMode;
} EmuLaunchGameListParam_t;

/// URL Format: Emu://Launch?APM_Mode=%d&FilePath=%s
/// No data response callback
void LaunchEmuApp
(
    AppLaunchMode_e eAppLaunchMode,
    MAE_WChar *wStrUrl,
    LaunchAppTransParam_t *psTransParam,
    CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

void LaunchEmuAppEx
(
    AppLaunchMode_e eAppLaunchMode,
    EmuLaunchAppParam_t *pAppLaunchParam,
    LaunchAppTransParam_t *pTransParam,
    CmnAppLaunchRspCbInfo_t *pRspCbInfo
);

// Utility for launching File Manager App to do file listing
void EmuListFiles(void);

// APM_LAUNCH_EMBEDDED mode is used for Applet and APM_LAUNCH_INTERRUPTIVE mode is used for hot key
void EmuListFilesEx(EmuLaunchGameListParam_t *pParam);

#endif
