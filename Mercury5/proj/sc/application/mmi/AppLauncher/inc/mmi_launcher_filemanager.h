#ifndef __FILEMGR_APP_H__
#define __FILEMGR_APP_H__

#include "mmi_launcher_common.h"
#include "mmi_wdg_itf_menu.h"
#include "filemgr_data_types.h"
#include "mmi_filemgrapp_cfg.h"
#include "mmi_common_storage_mgr.h"
#include "mmi_common_filemgr_type.h"
/// 1. Alarm App,    APM_Mode = APM_LAUNCH_EMBEDDED,    param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_EMBEDDEDLIST,    FilterType = FILEMGRAPP_SOUND_FILE,     DefaultFolder = By FileId,
/// 2. Atv App,      APM_Mode = APM_LAUNCH_EMBEDDED,    param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_LISTDIR,         FilterType = FILEMGRAPP_PICTURE_FILE,   DefaultFolder = CATEID_CARDTV,
/// 3. Cam App,      APM_Mode = APM_LAUNCH_EMBEDDED,    param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_LISTDIR,         FilterType = FILEMGRAPP_PICTURE_FILE,   DefaultFolder = CATEID_PHONEALBUM | CATEID_CARDALBUM
///                  APM_Mode = APM_LAUNCH_EMBEDDED,    param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_LISTDIR,         FilterType = FILEMGRAPP_VIDEO_FILE,     DefaultFolder = CATEID_CARDCAMCORDER
/// 4. CdWap App,    APM_Mode = APM_LAUNCH_EMBEDDED,    param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_EXPRESS,         FilterType = input,                     DefaultFolder = input,
/// 5. Em App,       APM_Mode = APM_LAUNCH_NORMAL,      param = NULL,                      Mode = FILEMGRAPP_MODE_FULLBROWSING,    FilterType = NULL,                      DefaultFolder = NULL,                                  (it's equal to full browsing)
/// 6. JavaAms App,  APM_Mode = APM_LAUNCH_EMBEDDED,    param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_EMBEDDEDMEMINFO, FilterType = NULL,                      DefaultFolder = NULL,
/// 7. MPlayer App,  APM_Mode = APM_LAUNCH_EMBEDDED,    param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_MULTIPICK,       FilterType = FILEMGRAPP_SOUND_FOR_M3U,  DefaultFolder = NULL,                                  uMaxFileSize = 0, uMaxFileNum = PLAYLISTSRV_MAX_PALYLIST_ITEMS - nPlaylistSize
///                  APM_Mode = APM_LAUNCH_EMBEDDED,    param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_MULTIPICK,       FilterType = FILEMGRAPP_VIDEO_FILE,     DefaultFolder = NULL,                                  uMaxFileSize = 0, uMaxFileNum = PLAYLISTSRV_MAX_PALYLIST_ITEMS - nPlaylistSize
///                  APM_Mode = APM_LAUNCH_EMBEDDED,    param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_EMBEDDEDLIST,    FilterType = FILEMGRAPP_PICTURE_FILE,   DefaultFolder = By FileId,                             uMaxFileSize = 0,
/// 8. Phb App,      APM_Mode = APM_LAUNCH_EMBEDDED,    param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_EMBEDDEDLIST,    FilterType = input,                     DefaultFolder = By FileId,                             uMaxFileSize = 0,
///                  APM_Mode = APM_LAUNCH_EMBEDDED,    param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_MULTIPICK,       FilterType = input,                     DefaultFolder = NULL,                                  uMaxFileSize = 0, uMaxFileNum = MMI_PHB_ADR_SUPPORT_MAX
/// 9. Profile App,  APM_Mode = APM_LAUNCH_EMBEDDED,    param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_EMBEDDEDLIST,    FilterType = FILEMGRAPP_RINGTONES_FILE, DefaultFolder = By FileId,                             uMaxFileSize = 0
/// 10 Sea App,      APM_Mode = APM_LAUNCH_EMBEDDED,    param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_EMBEDDEDLIST,    FilterType = input,                     DefaultFolder = By FileId,                             uMaxFileSize = input
/// 11.Setting App,  APM_Mode = APM_LAUNCH_EMBEDDED,    param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_EMBEDDEDLIST,    FilterType = input,                     DefaultFolder = By FileId,                             uMaxFileSize = input
/// 12.Vendor App,   APM_Mode = APM_LAUNCH_EMBEDDED,    param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_EMBEDDEDLIST,    FilterType = input,                     DefaultFolder = By FileId,                             uMaxFileSize = input
///                  APM_Mode = APM_LAUNCH_EMBEDDED,    param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_MULTIPICK,       FilterType = input,                     DefaultFolder = NULL,                                  uMaxFileSize = 0, uMaxFileNum = pFileBrowseReq->maxMarkSize
/// 13.Shortcut Srv, APM_Mode = APM_LAUNCH_INTERRUPTIVE,param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_FULLBROWSING,    FilterType = NULL,                      DefaultFolder = NULL,                                  uMaxFileSize = 0
///                  APM_Mode = APM_LAUNCH_INTERRUPTIVE,param = FileMgrApp_EmbeddedData_t, Mode = FILEMGRAPP_MODE_LISTDIR,         FilterType = input,                     DefaultFolder = input,                                 uMaxFileSize = 0



/// 2.
/// 3.
/// 4.
/// 5.
/// "FileManager://FullBrowsing?APM_Mode=%d"
/// "FileManager://ListFile?APM_Mode=%d&DirPath=%s&DirTitle=%s"
/// "FileManager://SimpeListFile?APM_Mode=%d&DirPath=%s&DirTitle=%s"
/// "FileManager://ListDir?APM_Mode=%d&DirNum=%d&DirPath1=%s&DirTitle1=%s..."
void LaunchFileManagerApp
(
  AppLaunchMode_e eAppLaunchMode,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

/// "FileManager://ListDir?APM_Mode=%d&DirNum=%d&DirPath1=%s&DirTitle1=%s..."
void LaunchAppToListDir
(
  AppLaunchMode_e eAppLaunchMode,
  FileManagerLaunchData_t *psLaunchData,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

/// Interface to get predefined file

void LaunchAppToGetPredefinedFile
(
 AppLaunchMode_e eAppLaunchMode,
 AppGetPredefinedFileInputData_t *psInputData,
 LaunchAppTransParam_t *psTransParam,
 AppGetPredefinedFileRspCbInfo_t *psRspCbInfo
);

/// Interface to get files


/// 1.
/// 7.
/// 8.
/// 9.
/// 10.
/// 11.
/// 12.
/// "FileManager://GetFiles?APM_Mode=%d&Mode=%d&MaxFileSize=%d&FilterType=%d&DirPath=%s&DirTitle=%s"
/// "FileManager://GetFiles?APM_Mode=%d&Mode=%d&MaxFileSize=%d&MaxFileNum=%d&FilterType=%d&DirPath=%s&DirTitle=%s"
void LaunchAppToGetFiles
(
  AppLaunchMode_e eAppLaunchMode,
  AppGetFileInputData_t *psInputData,
  LaunchAppTransParam_t *psTransParam,
  AppGetFileRspCbInfo_t *psRspCbInfo
);


/// Interface to show storage information
/// 6.
/// "FileManager://ShowMemoryDetails?APM_Mode=%d"
void LaunchAppToShowMemoryDetails
(
  AppLaunchMode_e eAppLaunchMode,
  AppShowMemMode_e eShowMemMode,
  LaunchAppTransParam_t *psTransParam,
  CmnAppLaunchRspCbInfo_t *psRspCbInfo
);

/// Interface to get dir

void LaunchAppToGetDir
(
  AppLaunchMode_e eAppLaunchMode,
  AppGetDirInputData_t *psInputData,
  LaunchAppTransParam_t *psTransParam,
  AppGetDirRspCbInfo_t *psRspCbInfo
);


void FileMgrFilterGetPictureBaseCb(void *pUserData, VFS_PartialListFilter_t **tFilter);
void FileMgrFilterGetRingBaseCb(void *pUserData, VFS_PartialListFilter_t **tFilter);
void FileMgrFilterGetMusicBaseCb(void *pUserData, VFS_PartialListFilter_t **tFilter);
void FileMgrFilterGetMp3BaseCb(void *pUserData, VFS_PartialListFilter_t **tFilter);
void FileMgrFilterGetM3uBaseCb(void *pUserData, VFS_PartialListFilter_t **tFilter);
void FileMgrFilterGetWaveBaseCb(void *pUserData, VFS_PartialListFilter_t **tFilter);
void FileMgrFilterGetVideoBaseCb(void *pUserData, VFS_PartialListFilter_t **tFilter);
void FileMgrFilterGetVoiceBaseCb(void *pUserData, VFS_PartialListFilter_t **tFilter);
void FileMgrFilterGetEmuBaseCb(void *pUserData, VFS_PartialListFilter_t **tFilter);
void FileMgrFilterGetThemeBaseCb(void *pUserData, VFS_PartialListFilter_t **tFilter);
void FileMgrFilterGetVcardBaseCb(void *pUserData, VFS_PartialListFilter_t **tFilter);
void FileMgrFilterGetMMSVideoBaseCb(void *pUserData, VFS_PartialListFilter_t **tFilter);
void FileMgrFilterGetMMSMusicBaseCb(void *pUserData, VFS_PartialListFilter_t **tFilter);
#ifdef __APP_MMI_FM_RADIO_REC__
void FileMgrFilterGetFmRecBaseCb(void *pUserData, VFS_PartialListFilter_t **tFilter);
#endif
#if defined (__USER_DEFINE_POWERONOFF_ANIM__) || defined (__USER_DEFINE_POWERONOFF_VIDEO__)
void FileMgrFilterGetOnOffDisplayBaseCb(void *pUserData, VFS_PartialListFilter_t **tFilter);
#endif
#ifdef  __VIDEO_WALLPAPER__
void FileMgrFilterGetVideoWallpaperBaseCb(void *pUserData, VFS_PartialListFilter_t **tFilter);
#endif
#endif
