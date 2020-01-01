////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    mmi_kingmovieapp_priv.h
* @version
* @brief   KingMovie applet private header file
*
*/
#ifndef __MMI_KINGMOVIEAPP_PRIV_H__
#define __MMI_KINGMOVIEAPP_PRIV_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_baseapplet.h"
#include "mmi_kingmovieapp_id.h"
#include "kingmovieapp_resource.h"
#include "mmi_common_vtm.h"
#include "mmi_mediasrv_common.h"
#include "mmi_launcher_common.h"

/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define KMVAPP_PLAYLIST_ARRAYMODEL_INIT_SIZE        (3)
#define KMVAPP_PLAYLIST_ARRAYMODEL_GROW_SIZE        (3)
#define KMVAPP_MOVIE_IMAGE_SIZE                     (16 * 1024)
#define KMVAPP_MOVIE_NAME_LENGTH                    (120)
#define KMVAPP_MOVIE_STARRING_LENGTH                (200)
#define KMVAPP_MOVIE_SYNOPSIS_LENGTH                (800)
#define KMVAPP_MOVIE_ID_LENGTH                      (VIDEOPLAYER_MD5HASH_SIZE + 1)

#define KMVAPP_MOVIE_INFO_SCROLLBAR_VISIBLE_RANGE   (9)

#define KMVAPP_DIALOG_DELAY                         (200)
#define KMVAPP_FULLPATH_OFFSET                      (24)

#define KMVAPP_KB                                   (1024)
#define KMVAPP_MIN_SD_FREE_SPACE                    (18)

#define MMI_MAX_CARD_FILEPATH_LEN                   (265)   // for temporary

#define KMVAPP_CACHE_BASKET_COUNT                   (2)
#define KMVAPP_CACHE_BASKET_DEPTH                   (2)

#define KMVAPP_MAX_LAST_PLAY_NUM                    (5)
#define KMVAPP_MAX_MY_FAVORITES_NUM                 (5)

#define KMVAPP_NULL_LAST_PLAY_COUNT                 (0xff)
#define KMVAPP_NULL_ID_INDEX                        (0xff)
#define KMVAPP_NULL_TYPE_INDEX                      (0xffffffff)

#ifdef __MMI_KING_MOVIE_3D_APP_INDIE__
#define KMVAPP_3DPLAYLIST_PATH                      L"3d"
#endif
#define KMVAPP_PLAYLIST_PATH                        L"pls/"
#define KMVAPP_MOVIE_COUNT_FILE_PATH                (KMVAPP_PLAYLIST_PATH L"FileCount.pls")
#define KMVAPP_TEMP_PLAYLIST_FILE_PATH              (KMVAPP_PLAYLIST_PATH L"Temp.pls")
#define KMVAPP_LAST_PLAY_FILE_PATH                  (KMVAPP_PLAYLIST_PATH L"LastPlay.pls")
#define KMVAPP_ID_TABLE_FILE_PATH                   (KMVAPP_PLAYLIST_PATH L"IdTable.pls")

#define KMV_BREAK_IF_FAIL_TRACE(r,s)        \
{                                           \
    if(MAE_RET_SUCCESS != r)                \
    {                                       \
        LOG_TRACE(MMI_LEVEL_KMVAPP, s, r);  \
        break;                              \
    }                                       \
}

/*=============================================================*/
// Data type definition
/*=============================================================*/
typedef enum
{
    CategoryType_Action = 0,
    CategoryType_Adventure,
    CategoryType_Animation,
    CategoryType_Comedy,
    CategoryType_Documentary,
    CategoryType_Drama,
    CategoryType_FamilyKids,
    CategoryType_Fantasy,
    CategoryType_Horror,
    CategoryType_Music,
    CategoryType_Mystery,
    CategoryType_PerformingArts,
    CategoryType_Romance,
    CategoryType_SciFi,
    CategoryType_Sports,
    CategoryType_Suspense,
    CategoryType_War,
    CategoryType_Western,
    CategoryType_Others,
    CategoryType_MyFavorites,
    CategoryType_NumOfCategory,
    CategoryType_Invalid = 0xFFFF
} KMVCategoryType_e;

typedef struct
{
    IWidget *pTitleTextWdg;
    IWidget *pImgWdg;
    IWidget *pTextWdg;
    IWidget *pInputWdg;
    IWidget *pScrollBarWdg;
    IWidget *pSwitchContainer;
    IWidget *pMovieSwitchTextWdg;
    IWidget *pLeftArrowBtnWdg;
    IWidget *pRightArrowBtnWdg;
} KMVMovieInfoWdgList_t;

typedef struct
{
    KMVMovieInfoWdgList_t tWdgList;
    boolean bIsPasswordWnd;
} KMVMovieInfoWndData_t;

typedef struct
{
    MenuWdgList_t tWdgList;
    boolean bIsPasswordWnd;
} KMVMovieListWndData_t;

typedef struct
{
    MenuWdgList_t tWdgList;
} KMVCategoryListWndData_t;


typedef struct
{
    KMVCategoryType_e eCategoryID;
    //const MAE_WChar *pPlaylistFileName;
    MAE_WChar *pPlaylistFileName;
} KMVPlaylistFileName_t;

typedef struct
{
    u32 nStringId;
    u32 nItemId;
} KMVCategoryListMenuItem_t;

typedef enum
{
    FileMode_Read = 0,
    FileMode_Write,
    FileMode_Append
} KMVFileMode_e;

typedef struct
{
    FileMgr_Stream_t *pIFStream;
    KMVFileMode_e eFileMode;
    //IArrayModel *pPlaylistAryModel; // for cache movie info data
} KMVPlaylistFileStream_t;

typedef struct // Four bytes alignment
{
    u8 szMovieName[KMVAPP_MOVIE_NAME_LENGTH]; // UTF8 encoding
    u16 nMovieTime;
    u16 nMovieYear;
    u8 szMovieStarring[KMVAPP_MOVIE_STARRING_LENGTH];
    u8 szMovieSynopsis[KMVAPP_MOVIE_SYNOPSIS_LENGTH];
    KMVCategoryType_e eCategory;
    u32 nImageSize; // in bytes
    u8 anImageData[KMVAPP_MOVIE_IMAGE_SIZE];
} KMVMovieInfo_t;


typedef struct // Four bytes alignment
{
    u8 szMovieName[KMVAPP_MOVIE_NAME_LENGTH + 1]; // UTF8 encoding
    u8 szMovieStarring[KMVAPP_MOVIE_STARRING_LENGTH + 1];
    u8 szMovieSynopsis[KMVAPP_MOVIE_SYNOPSIS_LENGTH + 1];
} KMVDisplayMovieInfo_t;


typedef struct // Four bytes alignment
{
    MAE_WChar wszFilePath[MMI_MAX_CARD_FILEPATH_LEN + KMVAPP_FULLPATH_OFFSET]; // L"fs:/CARD/KingMovie/" (19) L"fs:/Phone/KingMovie/" (20)
    KMVMovieInfo_t tMovieInfo;
} KMVPlaylistMovieInfo_t;


typedef struct
{
    HistoryInfo_t tHistory; // History info of the category menu
    boolean bLastPlayed;
} KMVCategoryHistoryInfo_t;

typedef struct
{
    boolean bValid;
    u32 anPlaylistCount[CategoryType_NumOfCategory]; // Get movie count in each playlist.
} KMVPlaylistCount_t;


typedef struct
{
    KMVCategoryType_e aeCategoryType[KMVAPP_CACHE_BASKET_COUNT];
    u32 anMovieCount[KMVAPP_CACHE_BASKET_COUNT];
    KMVPlaylistMovieInfo_t atMovieInfo[KMVAPP_CACHE_BASKET_COUNT][KMVAPP_CACHE_BASKET_DEPTH];
} KMVMovieInfoCacheBasket_t;

typedef struct
{
    u8 nType;
    u32 nTypeIndex;
} KMVLastPlayInfo_t;

typedef struct
{
    StorageType_e eStorage;
    u8 nIndex;
} KMVIdIndex_t;

typedef struct
{
    u8 nId[KMVAPP_MOVIE_ID_LENGTH];
    u8 nType;
    u32 nTypeIndex;
} KMVIdMapping_t;

/**
* Application structure
*/
typedef struct
{
    APPLET_BASE_ELEMENTS;

    KMVCategoryHistoryInfo_t tCategoryMenuHistory; // Keep category menu history.
    HistoryInfo_t tMovieMenuHistory; // Keep movie menu history.
    //HistoryInfo_t tOptMenuHistory; // Keep option menu history.
    KMVPlaylistMovieInfo_t *pPlaylistMovieInfo; // Keep movie info.
    boolean bStarted; // Check if already receive Start Event.
    boolean bStopped; // Check if already receive Stop Event.
    boolean bVideoPlayerStarted; // Check if start Video plaer.
    boolean bSuspend; // Check if current view is a dialog.
    boolean bDeletingFile; // Check if already deleting file.
    boolean bMovieCountFileValid; // Check if movie count file is valid.
    boolean bUpdatingFile; // Decide if updating file.
    boolean bPauseUpdatingFile;
    boolean bSDHotSwap;
    boolean bBackFromSuspend; // Check if back from suspend mode.
    boolean bUpdatingPasswordTable; // Decide if updating password table.
    MediaSrvErrCode_e eMediaErrCode; // Keep get file info return code.
    KMVPlaylistFileStream_t atPlaylistData[CategoryType_NumOfCategory];
    boolean abAppend[CategoryType_NumOfCategory]; // Check if 1st dispatch file for overwrite or append playlist.
    KMVPlaylistCount_t tPlaylistCount; // Get playlist count.
    u32 nFileHandle; // Keep file handle for dispatch file.
    u32 nDispatchFileIndex; // Keep index for dispatch file.
    u32 nFileNum; // Keep total file num for dispatch.
    u16 nCurrentViewID; // Keep current View ID.
    StorageType_e eSrcStorage;
    const MAE_WChar *pSrcFullPath;
    KMVMovieInfoCacheBasket_t *pMovieInfoCacheBasket;

    u8 nLastPlayCount;
    KMVLastPlayInfo_t *pLastPlayInfo;
    u32 *pLastPlayPos;

    u8 nPasswordCount;
    VideoPlayerPasswordList_t *pPasswordTable;
    KMVIdIndex_t *pIdIndex;

    u8 anIdCount[MAX_STORAGE_NUM];
    KMVIdMapping_t *pIdTable[MAX_STORAGE_NUM];

    IWidget *pIProcessWdg; // Handle processing widget of processing dialog.
    
#if defined(__3D_UI_KINGMOVIE__)
    IWidget *pBGImgWdg;
    boolean bIgnoreClickToShowMovieList;
#endif
#if defined(__MMI_KING_MOVIE_3D_APP_INDIE__)
    boolean bIs3Dmode;
#endif
} KingMovieAppData_t;

/*=============================================================*/
// Local function definition
/*=============================================================*/
MAE_Ret KMVMovieListWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);
MAE_Ret KMVMovieInfoWndHdl(void *pCusHandle, const WindowMsg_t *pWndMsg, void *pWndData, u32 nWndInitParam);

void KMVCategoryMenuGetItemData(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void KMVCategoryMenuFreeItemData(WdgDynamicMenuItemPtr_t *pMenuItem, void *pOwner, WdgMenuItemType_e eItemType);

void KMVMovieMenuGetItemData(WdgDynamicMenuItemPtr_t *pMenuItem, HWIN hWin, WdgMenuItemType_e eItemType, IWidget *pMenu, u32 nIndex);
void KMVMovieMenuFreeItemData(WdgDynamicMenuItemPtr_t *pMenuItem, void *pOwner, WdgMenuItemType_e eItemType);

void KMVFreeImageSrcBuffer(void *pData);

void KMVMovieListMenuSelectCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, HistoryInfo_t *pHistoryInfo, IWidget *pWidget);

void KMVSwitchMovieInfoLeftButtonClickCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);
void KMVSwitchMovieInfoRightButtonClickCB(void *pApplet, void *pUsrData, WidgetEvtCode_t nEvtCode, u32 dwParam, IWidget *pWidget);

MAE_Ret KMVDeleteMovieConfirmCB(void *pIApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret KMVDeleteFavoriteMovieConfirmCB(void *pIApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret KMVDeleteLastPlayMovieConfirmCB(void *pIApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret KMVDeletePasswordConfirmCB(void *pIApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);
MAE_Ret KMVDeleteAllPasswordConfirmCB(void *pIApplet, MAEEvent_t nEvt, u32 nParam1, u32 nParam2);

void KMVTimerDeleteMovieCB(void *pHandler);
void KMVTimerDeleteFavoriteMovieCB(void *pHandler);
void KMVTimerDeleteLastPlayMovieCB(void *pHandler);
void KMVTimerDeletePasswordCB(void *pHandler);
void KMVTimerDeleteAllPasswordCB(void *pHandler);

void KMVTimerUpdatePlaylistCB(void *pHandler);

void KMVLastPlayedPosCB(void *pvUserData, MAE_Ret nRspCode, void *pvRspData, CmnRspDataFreeCb pfnRspFreeCb);

void KMVSrvAccessoryPlugStatusCB(void *pIApplet, ACCDeviceType_e eDevice, boolean bPlug, ExtCardAccInfo_e eCardinfo);

void _KMVStartVideoPlayer(KingMovieAppData_t *pThis, MAE_WChar *pFilePath, u32 nStartPos);
void _KMVPlayLastPlayedMovie(KingMovieAppData_t *pThis, boolean bContPlay);

MAE_Ret _KMVGetActiveMovieInfoFromPlaylist(KingMovieAppData_t *pThis, KMVPlaylistMovieInfo_t *pPlaylistMovieInfo);
MAE_Ret _KMVGetMovieInfoFromPlaylistByIndex(KingMovieAppData_t *pThis, StorageType_e eStorage, KMVCategoryType_e eCategoryType, u32 nIndex, KMVPlaylistMovieInfo_t *pPlaylistMovieInfo);

u32 _KMVGetMovieItemCountByPlaylist(KingMovieAppData_t *pThis, KMVCategoryType_e eCategoryType);
void _KMVGetMovieCountForAllCategory(KingMovieAppData_t *pThis);

MAE_Ret _KMVMapMovieIndex(KingMovieAppData_t *pThis, u32 nIndexInMenu, KMVCategoryType_e *pCategoryType, u32 *pIndexInList);
void _KMVUpdateMovieList(KingMovieAppData_t *pThis, boolean bStartFromFirstMovie);
void _KMVDeleteMovie(KingMovieAppData_t *pThis, u32 nCategoryMenuItemID);

boolean _KMVGetLastPlayConfigItem(KingMovieAppData_t *pThis);
void _KMVSetLastPlayConfigItem(KingMovieAppData_t *pThis, boolean bLastPlayed);

MAE_Ret _KMVGetLastPlay(KingMovieAppData_t *pThis);
MAE_Ret _KMVSetLastPlay(KingMovieAppData_t *pThis);

void _KMVAddToFavorite(KingMovieAppData_t *pThis);
MAE_Ret _KMVFinalize(KingMovieAppData_t *pThis);
void _KMVStop(KingMovieAppData_t *pThis);

#if defined(__APP_DATA_ON_PHONE__) || defined(__DUAL_CARD__)
void _KMVSelectSrcStorage(KingMovieAppData_t *pThis);
#endif

/*=============================================================*/
// Global function definition
/*=============================================================*/
MAE_Ret KingMovieConstructor
(
    IApplet *pApplet,
    u32 nEvt,
    u32 nParam1,
    u32 nParam2
);

MAE_Ret KingMovieDestructor
(
    IApplet *pApplet,
    u32 nEvt,
    u32 nParam1,
    u32 nParam2
);

boolean KingMovieStartCB
(
    IApplet *pApplet,
    u32 nEvt,
    u32 nParam1,
    u32 nParam2
);

boolean KingMovieStopCB
(
    IApplet *pApplet,
    u32 nEvt,
    u32 nParam1,
    u32 nParam2
);

boolean KingMovieKeyPressCB
(
    IApplet *pApplet,
    u32 nEvt,
    u32 nParam1,
    u32 nParam2
);

boolean KingMovieKeyLongPressCB
(
    IApplet *pApplet,
    u32 nEvt,
    u32 nParam1,
    u32 nParam2
);

boolean KingMovieSuspendCB
(
    IApplet *pApplet,
    u32 nEvt,
    u32 nParam1,
    u32 nParam2
);

boolean KingMovieResumeCB
(
    IApplet *pApplet,
    u32 nEvt,
    u32 nParam1,
    u32 nParam2
);

#endif /* __MMI_KINGMOVIEAPP_PRIV_H__ */
