
#ifndef __MAE_COMMON_STORAGE_MGR_H__
#define __MAE_COMMON_STORAGE_MGR_H__
#include "mmi_common_storage_mgr_cfg.h"
#include "mdl_vfs_struct.h"
#include "mmi_cfgsrv_common_table.h"

//const MAE_WChar g_wszMMI_PHONE_SIG_FULLPATH[] = L"fs:/PHON/_msystem";
//const MAE_WChar g_wszMMI_CARD_SIG_FULLPATH[] = L"fs:/CARD/_msystem";
//const MAE_WChar g_wszMMI_COMMON_THUMB_CACHESTORAGE[] =	L"fs:/CARD/";
//const MAE_WChar g_wszMMI_COMMON_THUMB_CACHEDIR[] =		L"fs:/CARD/THUMB/";
//const MAE_WChar g_wszMMI_CDWAP_DOWNLOAD_FOLDER[] = L"fs:/CARD/Download/";

#define FOLDER_DELIMITER	L'/'
#define FOLDER_DELIMITER_S	L"/"
#define URL_PREFIX			L"fs:/"
#define HTTP_PREFIX			L"http://"
#define RTSP_PREFIX			L"rtsp://"

#define DIR_PHONE			L"fs:/PHON/"
#define DIR_CARD			L"fs:/CARD/"
#define DIR_CARD2			L"fs:/SD_2/"

#define DIR_SYSTEM          L".system"

#define DIR_PICTURE			L"Pictures/"
#define DIR_ALBUM			L"Pictures/Album/"
#define DIR_MUSIC			L"Music/"
#define DIR_VIDEO			L"Video/"
#define DIR_CAMCORDER		L"Video/Camcorder/"
#define DIR_VOICEMEMO		L"Music/Voicememo/"
#ifdef __APP_MMI_ANSWERING_MACHINE__
#define DIR_ANSWERING_MACHINE L"Music/AnsweringMachine/"
#endif
#define DIR_APP				L"Applications/"
#define DIR_GAME			L"Games/"
#define DIR_THEME			L"Themes/"
#ifdef __FEATURE_FONT_STYLE__
#define DIR_FONT			L"Fonts/"
#endif
#define DIR_CDWAP_ROOT		DIR_SYSTEM
#define DIR_CDWAP_EXPLORERE L".system/WapExplorer/"
#define DIR_CDWAP_BROWSER	L".system/WapExplorer/Browser/"
#define DIR_CDWAP_DOWNLOAD  L"Download/"

#define DIR_TV				L"Pictures/TV/"
#define DIR_EBOOK			L"eBook/"
#define DIR_DICTIONARY		L"Dictionary/"
#define DIR_MMS				L".system/MMS"
#define DIR_PHONEBOOK		L"Phonebook/"
#define DIR_RECEIVED		L"Received/"
#define DIR_KING_MOVIE      L"KingMovie/"
#define DIR_VIDEO_DOWNLOAD  L"Video/Download/"

#ifdef __CALLER_LOCATION__
#define DIR_CALLERLOCATION  L"CallerLocation/"
#endif

#define DIR_KMXUD		L"kmxud"
#define DIR_RAI_DUMP        L".system/RAI_Dbg"
#define DIR_SYSBT           L"sysbt"
#define DIR_CDWAP_BM        L".system/WapExplorer/Bookmark/"
#define DIR_CDWAP_LP        L".system/WapExplorer/History/"
#define DIR_CDWAP_INPUT     L".system/WapExplorer/Input.cdw"
#define CDWAP_URL_PREFIX    L"fs:"
#define THUMB_EXT           L"thu"


#define FILESIZE_FORMATSTR_INT          L"%d"
#define FILESIZE_FORMATSTR_FLOAT        L"%s%.2f"
#define WALLPAPER_CROP_TMP_FILENAME     L"My Wallpaper.tmp"
#define WALLPAPER_CROP_FILENAME         L"My Wallpaper.jpg"



#define ADURL_IMAGE         L"ad:/IMAGE/"
#define ADURL_MELODY        L"ad:/SOUND/"

#define CARD_DIR_KMXUD		    (DIR_CARD DIR_KMXUD)

#define CARD_DIR_SYSBT		    (DIR_CARD DIR_SYSBT)
#define CARD2_DIR_SYSBT	    (DIR_CARD2 DIR_SYSBT)

#define CARD_DIR_RAI_DUMP       (DIR_CARD DIR_RAI_DUMP)
#define CARD2_DIR_RAI_DUMP	    (DIR_CARD2 DIR_RAI_DUMP)

#define PHONE_DIR_SYSTEM        (DIR_PHONE DIR_SYSTEM)
#define CARD_DIR_SYSTEM         (DIR_CARD DIR_SYSTEM)
#define CARD2_DIR_SYSTEM	    (DIR_CARD2 DIR_SYSTEM)

#define PHONE_DIR_PICTURE		(DIR_PHONE DIR_PICTURE)
#define CARD_DIR_PICTURE		(DIR_CARD DIR_PICTURE)
#define CARD2_DIR_PICTURE	    (DIR_CARD2 DIR_PICTURE)

#define PHONE_DIR_ALBUM			(DIR_PHONE DIR_ALBUM)
#define CARD_DIR_ALBUM          (DIR_CARD DIR_ALBUM)
#define CARD2_DIR_ALBUM	    (DIR_CARD2 DIR_ALBUM)

#define PHONE_DIR_MUSIC         (DIR_PHONE DIR_MUSIC)
#define CARD_DIR_MUSIC          (DIR_CARD DIR_MUSIC)
#define CARD2_DIR_MUSIC	    (DIR_CARD2 DIR_MUSIC)

#define PHONE_DIR_VIDEO         (DIR_PHONE DIR_VIDEO)
#define CARD_DIR_VIDEO          (DIR_CARD DIR_VIDEO)
#define CARD2_DIR_VIDEO	    (DIR_CARD2 DIR_VIDEO)

#define PHONE_DIR_CAMCORDER     (DIR_PHONE DIR_CAMCORDER)
#define CARD_DIR_CAMCORDER      (DIR_CARD DIR_CAMCORDER)
#define CARD2_DIR_CAMCORDER	    (DIR_CARD2 DIR_CAMCORDER)

#define PHONE_DIR_VOICEMEMO     (DIR_PHONE DIR_VOICEMEMO)
#define CARD_DIR_VOICEMEMO      (DIR_CARD DIR_VOICEMEMO)
#define CARD2_DIR_VOICEMEMO	    (DIR_CARD2 DIR_VOICEMEMO)

#ifdef __APP_MMI_ANSWERING_MACHINE__
#define PHONE_DIR_ANSWERING_MACHINE     (DIR_PHONE DIR_ANSWERING_MACHINE)
#define CARD_DIR_ANSWERING_MACHINE      (DIR_CARD DIR_ANSWERING_MACHINE)
#define CARD2_DIR_ANSWERING_MACHINE	    (DIR_CARD2 DIR_ANSWERING_MACHINE)
#endif

#define PHONE_DIR_APP           (DIR_PHONE DIR_APP)
#define CARD_DIR_APP            (DIR_CARD DIR_APP)
#define CARD2_DIR_APP	    (DIR_CARD2 DIR_APP)

#define PHONE_DIR_GAME          (DIR_PHONE DIR_GAME)
#define CARD_DIR_GAME           (DIR_CARD DIR_GAME)
#define CARD2_DIR_GAME	    (DIR_CARD2 DIR_GAME)

#define PHONE_DIR_THEME         (DIR_PHONE DIR_THEME)
#define CARD_DIR_THEME          (DIR_CARD DIR_THEME)
#define CARD2_DIR_THEME	    (DIR_CARD2 DIR_THEME)

#ifdef __FEATURE_FONT_STYLE__
#define PHONE_DIR_FONT          (DIR_PHONE DIR_FONT)
#define CARD_DIR_FONT           (DIR_CARD DIR_FONT)
#define CARD2_DIR_FONT	        (DIR_CARD2 DIR_FONT)
#endif

#define PHONE_DIR_CDWAP_ROOT    (DIR_PHONE DIR_CDWAP_ROOT)
#define CARD_DIR_CDWAP_ROOT     (DIR_CARD DIR_CDWAP_ROOT)
#define CARD2_DIR_CDWAP_ROOT	    (DIR_CARD2 DIR_CDWAP_ROOT)

#define PHONE_DIR_CDWAP_EXPLORERE   (DIR_PHONE DIR_CDWAP_EXPLORERE)
#define CARD_DIR_CDWAP_EXPLORERE    (DIR_CARD DIR_CDWAP_EXPLORERE)
#define CARD2_DIR_CDWAP_EXPLORERE	    (DIR_CARD2 DIR_CDWAP_EXPLORERE)

#define PHONE_DIR_CDWAP_BROWSER (DIR_PHONE DIR_CDWAP_BROWSER)
#define CARD_DIR_CDWAP_BROWSER  (DIR_CARD DIR_CDWAP_BROWSER)
#define CARD2_DIR_CDWAP_BROWSER	    (DIR_CARD2 DIR_CDWAP_BROWSER)

#define PHONE_DIR_CDWAP_DOWNLOAD (DIR_PHONE DIR_CDWAP_DOWNLOAD)
#define CARD_DIR_CDWAP_DOWNLOAD  (DIR_CARD DIR_CDWAP_DOWNLOAD)
#define CARD2_DIR_CDWAP_DOWNLOAD	    (DIR_CARD2 DIR_CDWAP_DOWNLOAD)

#if defined(__ATV_MMI__) && !defined(__APP_MMI_SMALLROM__)
#define PHONE_DIR_TV            (DIR_PHONE DIR_TV)
#define CARD_DIR_TV             (DIR_CARD DIR_TV)
#define CARD2_DIR_TV	        (DIR_CARD2 DIR_TV)
#endif //__ATV_MMI__ && !__APP_MMI_SMALLROM__

#define PHONE_DIR_EBOOK         (DIR_PHONE DIR_EBOOK)
#define CARD_DIR_EBOOK          (DIR_CARD DIR_EBOOK)
#define CARD2_DIR_EBOOK	    (DIR_CARD2 DIR_EBOOK)

#define PHONE_DIR_DICTIONARY    (DIR_PHONE DIR_DICTIONARY)
#define CARD_DIR_DICTIONARY     (DIR_CARD DIR_DICTIONARY)
#define CARD2_DIR_DICTIONARY	    (DIR_CARD2 DIR_DICTIONARY)

#define PHONE_DIR_MMS           (DIR_PHONE DIR_MMS)
#define CARD_DIR_MMS            (DIR_CARD DIR_MMS)
#define CARD2_DIR_MMS	    (DIR_CARD2 DIR_MMS)

#define PHONE_DIR_PHONEBOOK     (DIR_PHONE DIR_PHONEBOOK)
#define CARD_DIR_PHONEBOOK      (DIR_CARD DIR_PHONEBOOK)
#define CARD2_DIR_PHONEBOOK	    (DIR_CARD2 DIR_PHONEBOOK)

#define PHONE_DIR_RECEIVED      (DIR_PHONE DIR_RECEIVED)
#define CARD_DIR_RECEIVED       (DIR_CARD DIR_RECEIVED)
#define CARD2_DIR_RECEIVED	    (DIR_CARD2 DIR_RECEIVED)

#define PHONE_DIR_CDWAP_BM      (DIR_PHONE DIR_CDWAP_BM)
#define CARD_DIR_CDWAP_BM       (DIR_CARD DIR_CDWAP_BM)
#define CARD2_DIR_CDWAP_BM	    (DIR_CARD2 DIR_CDWAP_BM)

#define PHONE_DIR_CDWAP_LP      (DIR_PHONE DIR_CDWAP_LP)
#define CARD_DIR_CDWAP_LP       (DIR_CARD DIR_CDWAP_LP)
#define CARD2_DIR_CDWAP_LP	    (DIR_CARD2 DIR_CDWAP_LP)

#define PHONE_DIR_CDWAP_INPUT   (DIR_PHONE DIR_CDWAP_INPUT)
#define CARD_DIR_CDWAP_INPUT    (DIR_CARD DIR_CDWAP_INPUT)
#define CARD2_DIR_CDWAP_INPUT	    (DIR_CARD2 DIR_CDWAP_INPUT)

#define PHONE_DIR_KING_MOVIE    (DIR_PHONE DIR_KING_MOVIE)
#define CARD_DIR_KING_MOVIE     (DIR_CARD DIR_KING_MOVIE)
#define CARD2_DIR_KING_MOVIE	    (DIR_CARD2 DIR_KING_MOVIE)

#define PHONE_DIR_VIDEO_DL      (DIR_PHONE DIR_VIDEO_DOWNLOAD)
#define CARD_DIR_VIDEO_DL       (DIR_CARD DIR_VIDEO_DOWNLOAD)
#define CARD2_DIR_VIDEO_DL      (DIR_CARD2 DIR_VIDEO_DOWNLOAD)

#ifdef __CALLER_LOCATION__
#define PHONE_DIR_CALLERLOCATION  (DIR_PHONE DIR_CALLERLOCATION)
#define CARD_DIR_CALLERLOCATION  (DIR_CARD DIR_CALLERLOCATION)
#define CARD2_DIR_CALLERLOCATION  (DIR_CARD2 DIR_CALLERLOCATION)
#endif

#ifndef MMI_COMMON_WALLPAPER_CROP_PATH
    #define MMI_COMMON_WALLPAPER_CROP_PATH       (CARD_DIR_PICTURE)
    #define MMI_COMMON_WALLPAPER_CROP_PATH2	    (CARD2_DIR_PICTURE)
#endif

#define DIR_BEAUTY_CLK_PICUTRES          L".beauty/0000.JPG"
#define DIR_BEAUTY_CLK_PICUTRES_BY_TIME L".beauty/%02d%02d.JPG"
#define CARD_DIR_BEAUTY_CLK_PICUTRES (DIR_CARD DIR_BEAUTY_CLK_PICUTRES)
#define CARD_DIR_BEAUTY_CLK_PICUTRES_BY_TIME (DIR_CARD DIR_BEAUTY_CLK_PICUTRES_BY_TIME)
#define CARD2_DIR_BEAUTY_CLK_PICUTRES (DIR_CARD2 DIR_BEAUTY_CLK_PICUTRES)
#define CARD2_DIR_BEAUTY_CLK_PICUTRES_BY_TIME (DIR_CARD2 DIR_BEAUTY_CLK_PICUTRES_BY_TIME)


typedef enum
{
    STORAGE_ENABLED,
    STORAGE_DISABLED,
} StorageStatus_e;

typedef enum
{
    MMI_DIR_PICTURE,
    MMI_DIR_ALBUM,
    MMI_DIR_MUSIC,
    MMI_DIR_VIDEO,
    MMI_DIR_CAMCORDER,
    MMI_DIR_VOICEMEMO,
#ifdef __APP_MMI_ANSWERING_MACHINE__
	MMI_DIR_ANSWERING_MACHINE,
#endif
    MMI_DIR_APP,
    MMI_DIR_GAME,
    MMI_DIR_THEME,
#ifdef __FEATURE_FONT_STYLE__
    MMI_DIR_FONT,
#endif
    MMI_DIR_CDWAP_ROOT,
    MMI_DIR_CDWAP_EXPLORERE,
    MMI_DIR_CDWAP_BROWSER,
#if defined(__ATV_MMI__) && !defined(__APP_MMI_SMALLROM__)
    MMI_DIR_TV,
#endif //__ATV_MMI__ && !__APP_MMI_SMALLROM__
    MMI_DIR_CDWAP_DOWNLOAD,
    MMI_DIR_EBOOK,
    MMI_DIR_DICTIONARY,
    MMI_DIR_MMS,
    MMI_DIR_PHONEBOOK,
    MMI_DIR_RECEIVED,
    MMI_DIR_KINGMOVIE,
    MMI_DIR_BT,
    MMI_DIR_WALLPAPER,
    MMI_DIR_VIDEO_DOWNLOAD,
#ifdef __CALLER_LOCATION__
    MMI_DIR_CALLERLOCATION,
#endif
    MAX_MMI_DIR_SIZE
}DirType_e;

typedef enum
{
    VOLUME_STORAGE_LIST,
    VOLUME_PICTURE_VIWER,
    VOLUME_VIDEO_PLAYER,
    VOLUME_VOICE_MEMO,
    VOLUME_GAME,
    VOLUME_MESSAGE_EDITOR,
#if defined(__ATV_MMI__) && !defined(__APP_MMI_SMALLROM__)
    VOLUME_ATV_VIEWER,
#endif //__ATV_MMI__ && !__APP_MMI_SMALLROM__
    VOLUME_CDWAP_DOWNLOAD,
    MAX_VOLUME_SIZE
}VirtualVolume_e;


typedef struct
{
    VFS_VOL_TYPE eStorageType;
    StorageStatus_e eStatus;
    boolean bAutoSwitch;
} StorageInfo_t;

typedef struct
{
    MAE_WChar *pwszFolder;
    u32        nImgId;
    u32        nTxtId;
} FileMgrVirtualVolumeItem_t;

typedef enum CommVolume_e_
{
#if defined(__NAND_MMI__)
    COMMON_VOLUME__NAND = 0,
#else
    COMMON_VOLUME__NOR = 0,
#endif
    COMMON_VOLUME__SD,
    COMMON_VOLUME__SD2,
    COMMON_VOLUME__NUM,
    COMMON_VOLUME__INVALID
} CommVolume_e;
typedef u8 CommonVolumeType_e;

typedef enum CommMedia_e_
{
    COMMON_MEDIA__NONE = 0,
    COMMON_MEDIA__RECORD_VIDEO,
    COMMON_MEDIA__PLAY_VIDEO,
    COMMON_MEDIA__CAPTURE_PICTURE,
    COMMON_MEDIA__PREVIEW_PICTURE,
    COMMON_MEDIA__INSTALL_JAVA,
    COMMON_MEDIA__PLAY_NES,
    COMMON_MEDIA__RECORD_AUDIO,
    COMMON_MEDIA__PLAY_AUDIO,
    COMMON_MEDIA__NUM,
    COMMON_MEDIA__INVALID
} CommMedia_e;
typedef u32 CommonMediaType_e;

u8 StorageMgrGetAvailStorageNum(void);
u8 StorageMgrGetAvailSettingStorageNum(void);
u8 StorageMgrGetAvailStorageNumWithMediaType(CommonMediaType_e eCommonMediaType);
u8 StorageMgrGetAvailSettingStorageNumWithMediaType(CommonMediaType_e eCommonMediaType);
MAE_Ret StorageMgrGetAvailFullPath(CFGItemID_e eId, DirType_e eDir, boolean bAutoCreate, MAE_WChar **pFullPath);
MAE_Ret StorageMgrGetFullPath(VFS_VOL_TYPE eStorageType, DirType_e eDir, boolean bAutoCreate, MAE_WChar **pFullPath);
MAE_Ret StorageMgrGetAvailStorage( CFGItemID_e eId, StorageInfo_t *pStorageInfo);
boolean StorageMgrShowStorageChangeNotify(CFGItemID_e eId);
__SLDPM_FREE__ boolean StorageMgrIsStorageAvailable(VFS_VOL_TYPE eType);
const FileMgrVirtualVolumeItem_t *StorageMgrGetVirtualVolume(VirtualVolume_e eType, u32 *pSize);
boolean StorageMgrIsDefaultDir(MAE_WChar *pFullPath);
boolean StorageMgrIsDefaultDirExist(StorageType_e eLocation);
void StorageMgrMakeDefaultDir(StorageType_e eLocation);
MAE_Ret StorageMgrSetCfgItem(CFGItemID_e eId, VFS_VOL_TYPE eStorageType);
MAE_Ret StorageMgrGetDefaultDir(MAE_WChar *pFolder, DirType_e eType, MAE_WChar **pRet, boolean bAutoCreate);
boolean StorageMgrIsAppDataOnPhone(void);
u32 StorageMgrGetTranslateTableNum(void);

#endif //__MAE_COMMON_STORAGE_MGR_H__

