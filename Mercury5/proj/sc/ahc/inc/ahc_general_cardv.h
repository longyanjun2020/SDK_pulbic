
#ifndef _AHC_GENERAL_CARDV_H_
#define _AHC_GENERAL_CARDV_H_

/*===========================================================================
 * Include file
 *===========================================================================*/

#include "ahc_common.h"
#include "ahc_warningmsg.h"
#include "aihc_protection_inc.h"
#include "ahc_isp.h"
#include "mmps_display.h"
#include "ctype.h"
#include "ahc_gui.h"
#if defined(_OEM_) && defined(ALL_FW)
#include "Oem.h"
#endif

/*===========================================================================
 * Macro definition
 *===========================================================================*/

/* For Video Lock File */
#define DEFAULT_LOCKED_FILENAME         "SOS_0000.AVI"

/* For Error Dialog */
#define MSG_PRESENT                     (1)
#define MSG_DISMISS                     (0)
#define ERROR_DIALOG_PRESENT(state)     (state == MSG_PRESENT)

/* For USB String */
#define VEN_LEN                         (8)
#define POD_LEN                         (16)
#define DESC_OFF                        (8)

/* For Movie Playback Status */
#define MOVIE_STATE_PAUSE               (0)
#define MOVIE_STATE_PLAY                (1)
#define MOVIE_STATE_FF                  (2)
#define MOVIE_STATE_REW                 (3)
#define MOVIE_STATE_STOP                (4)
#define MOVIE_STATE_PFF                 (5)
#define MOVIE_STATE_PFB                 (6)

/* For Audio Playback Status */
#define AUDIO_STATE_PAUSE               (0)
#define AUDIO_STATE_PLAY                (1)
#define AUDIO_STATE_FF                  (2)
#define AUDIO_STATE_REW                 (3)
#define AUDIO_STATE_STOP                (4)
#define AUDIO_STATE_PFF                 (5)
#define AUDIO_STATE_PFB                 (6)

/*===========================================================================
 * Structure definition
 *===========================================================================*/

typedef void (*TMHOOK)(void);

typedef struct
{
    const unsigned char     **strpool;
    const GUI_FONT          *fontmap;
} OSD_LANGSET;

/*===========================================================================
 * Enum definition
 *===========================================================================*/

typedef enum {
    PLAY_FIRST_FILE = 0,
    PLAY_CUR_FILE,
    PLAY_LAST_FILE
} PLAY_FILE_ORDER;

typedef enum {
    EDIT_OP_DELETE = 0,
    EDIT_OP_PROTECT,
    EDIT_OP_UNPROTECT
} EDIT_OP;

typedef enum {
    BOOTUP_CHARGER = 0,
    BOOTUP_USB,
    BOOTUP_MANUAL,
    BOOTUP_NONE
} BOOTUP_SELECT;

typedef enum {
    FILE_PHOTO = 0,
    FILE_MOVIE,
    FILE_PHOTO_MOVIE
} SEARCH_FILE_TYPE;

typedef enum {
    BROWSER_UP = 0,
    BROWSER_DOWN,
    BROWSER_LEFT,
    BROWSER_RIGHT,
    BROWSER_PLAY,
    BROWSER_PAGEUP,
    BROWSER_PAGEDOWN,
    BROWSER_HDMI,
    BROWSER_TVOUT
} BROWSER_SELECT;

typedef enum {
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
} DIRECTION;

extern TMHOOK   gTmKeypadHook;

/*===========================================================================
 * Function prototype
 *===========================================================================*/

/* Language */
UINT8           ShowOSD_GetLanguageEx(void);
void            ShowOSD_SetLanguageEx(UINT8 id, UINT8 nlang);

/* Motion Detection */
AHC_BOOL        AHC_GetMotionDtcSensitivity(UINT8 *pubMvTh, UINT8 *pubCntTh);
UINT32          AHC_GetVMDRecTimeLimit(void);
UINT32          AHC_GetVMDShotNumber(void);
void            AHC_AdjustVMDPreviewRes(int *w, int *h);

/* Timer Hook */
void            AHC_TmKeypadHook(void *cb);

/* Video Record */
UINT32          AHC_GetVideoPowerOffTime(void);
UINT32          AHC_GetVideoMaxLockFileTime(void);
INT8*           AHC_GetLockedFileName(UINT8 bSelect);
void            AHC_SetShutdownByChargerOut(AHC_BOOL bEnable);
AHC_BOOL        AHC_GetShutdownByChargerOut(void);
void            AHC_SetRecordByChargerIn(UINT8 ubDelay);
UINT8           AHC_GetRecordByChargerIn(void);
AHC_BOOL        AHC_GetAutoRec(void);
const char *    AHC_GetVideoExt(void);
AHC_BOOL        AHC_IsCurFileCharLock(void);

/* TV */
void            AHC_SwitchLCDandTVOUT(void);

/* LCD */
AHC_BOOL        AHC_SwitchLCDBackLight(void);

/* Menu Setting */
AHC_BOOL        Menu_SetFlashLEDMode(UINT8 val);
AHC_BOOL        Menu_SetLanguage(UINT8 val);
AHC_BOOL        Menu_SetFlickerHz(UINT8 val);
AHC_BOOL        Menu_SetSceneMode(UINT8 val);
AHC_BOOL        Menu_SetEV(UINT8 ubSnrSel, UINT8 val);
AHC_BOOL        Menu_SetISO(UINT8 ubSnrSel, UINT8 val);
AHC_BOOL        Menu_SetAWB(UINT8 ubSnrSel, UINT8 val);
AHC_BOOL        Menu_SetColor(UINT8 ubSnrSel, UINT8 val);
AHC_BOOL        Menu_SetEffect(UINT8 ubSnrSel, UINT8 val);
AHC_BOOL        Menu_SetMovieMode(UINT8 val);
AHC_BOOL        Menu_SetMovieQuality(UINT8 val);
AHC_BOOL        Menu_SetMICSensitivity(UINT8 val);
AHC_BOOL        Menu_SetVolume(UINT8 val);
AHC_BOOL        Menu_SetSoundRecord(UINT8 val);
AHC_BOOL        Menu_SetLCDDirectionEx(UINT8 val,UINT8 backupVal);
AHC_BOOL        Menu_RenewMenuSetting(UINT8 bReset);
AHC_BOOL        Menu_WriteLcdSnrTVHdmiStauts2SF(void);
AHC_BOOL        Menu_WriteSetting(void);
AHC_BOOL        Menu_ImportSetting(void);
AHC_AE_EV_BIAS  Menu_EV_To_AE_EV_BIAS(UINT8 val);
AHC_BOOL        Menu_SetContrast(UINT8 ubSnrSel, INT32 val);
AHC_BOOL        Menu_SetSaturation(UINT8 ubSnrSel, INT32 val);
AHC_BOOL        Menu_SetSharpness(UINT8 ubSnrSel, INT32 val);
AHC_BOOL        Menu_SetGamma(UINT8 ubSnrSel, INT32 val);

AHC_BOOL        AHC_ChangeEV(AHC_BOOL bCycle,UINT8 bDir);
AHC_BOOL        AHC_ChangeVolume(AHC_BOOL bCycle,UINT8 bDir);
AHC_BOOL        AHC_ToggleMute(void);
AHC_BOOL        AHC_ToggleTwilightMode(void);

/* LED */
void            AHC_SetMenuFlashLEDStatus(UINT8 ubLed);
UINT8           AHC_GetMenuFlashLEDStatus(void);
AHC_BOOL        AHC_ToggleFlashLED(UINT8 ubMode);
void            AHC_PreSetFlashLED(void);

/* Misc */
AHC_BOOL        AHC_PowerOn_Welcome(void);
AHC_BOOL        AHC_ShowErrorDialog(WMSG_INFO iInfo);
AHC_BOOL        AHC_CheckErrorDialog(UINT32 ulEvent);
AHC_BOOL        AHC_IsDialogPresent(void);
AHC_BOOL        AHC_ShowSoundWarning(void);
AHC_BOOL        AHC_CheckCurSysMode(UINT16 CheckMode);
AHC_BOOL        AHC_CheckCurFileLockStatus(void);
AHC_BOOL        AHC_SetPlayFileOrder(UINT8 ubOrder);
UINT32          AHC_GetMappingFileNum(UINT8 ubFileType);
AHC_BOOL        AHC_SetBootUpUIMode(void);

/* FileIO */
int             AHC_ReadlLine(UINT32 fd, char* buf, int size);
int             AHC_ReadLineMem(char *fbuf, int* fp, int fs, char* outl, int size);

/* SD MMC */
AHC_BOOL        AHC_SDMMC_BasicCheck(void);
UINT32          AHC_SDMMC_GetLockFileNum(void);

/* Power-On Option */
AHC_BOOL        AHC_SetButtonStatus(UINT32 keyId);
AHC_BOOL        AHC_PowerOnOption(void);
INT32           AHC_GetQuickKey(int qk);

/* USB */
void            AHC_CheckUSB_KeyFile(char *kf, int app);
AHC_BOOL        AHC_SetUSBLable(char *pszLable);

//MenuStateEditToolMenu.c
AHC_BOOL        DrawFileOperationResult(UINT8 status);
UINT8           QuickFileOperation(UINT8 Op);
AHC_BOOL        QuickMediaOperation(UINT8 Op);

/* Others */
extern int      sprintf(char * /*s*/, const char * /*format*/, ...);
extern int      snprintf(char * /*s*/, size_t /*n*/, const char * /*format*/, ...);

/* Pause Keypad input to protect some procedures that takes long time to run */
int             AHC_PauseKeyUI(void);
int             AHC_ResumeKeyUI(void);
int             AHC_KeyUIWorking(void);

/*Wi-fi*/
void            AHC_WiFi_Switch_Mode(void);
AHC_BOOL        AHC_Get_WiFi_Streaming_Status(void);
AHC_BOOL        AHC_SetButtonStatus(UINT32 keyId);

#if(SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN)
UINT32          AHC_GSNR_PWROn_MovieTimeReset(void);
#endif

#endif//_AHC_GENERAL_CARDV_H_
