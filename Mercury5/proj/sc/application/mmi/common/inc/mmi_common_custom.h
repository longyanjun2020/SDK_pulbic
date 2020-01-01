/**
 * @file mmi_common_custom.h
 *
 * Common customization file
 *
 * @version $Id: mmi_common_custom.h 39985 2009-09-11 07:24:33Z miya.chien $
 */
#ifndef __MMI_COMMON_CUSTOM_H__
#define __MMI_COMMON_CUSTOM_H__

/**
** Common Dialog Customization Data
**
**/
//Common Dialog auto close timer for unurgent information
#define COMMON_DIALOG_AUTOCLOSE_TIME 2000


/**
** Media Player Customization Data
**
**/
// Media Player \ Playlist uses for the max number of items for a user-defined playlist.
#define PLAYLISTSRV_MAX_PALYLIST_ITEMS (300)

/**
** This variable is used when Playlistsrv retrieves the pre-defined (All music \ All video) play list.
** It defines the max number of items in a pre-defined playlist.
**/
#define PLAYLISTSRV_MAX_PREDEFINED_PLAYLIST_ITEMS (1000)//sync to FILEMGR_MAXIMUM_MARK_NUMBER

/**
** This variable is used when Playlistsrv retrieves the playlist in the specified folder.
** It defines the max number of playlists retrieved in the folder
** It could be set more than 100. However, it consumes more memory and more time to retrieve all playlists in the folder
** If you want to set this value more than 100, you have to exam it very carefully.
**/
#define PLAYLISTSRV_MAX_PALYLISTS_NUM (100)

/**
** BT Customization Data
**
**/
// BT SRV & AP \ "# of paired bluetooth device(Data range 1 ~ 20)"
#define BTSRV_DEVICE_MAX_NUM (20)
#define BTOBEXSRV_FILE_NAME_FOR_DIALOG_MAX 16 //Max str length of OPP file name displayed in dialog
#define BTOBEXSRV_DEV_NAME_FOR_DIALOG_MAX 10  //Max str length of OPP device name displayed in dialog

/**
** Calllog Customization Data
**
**/
// Calllog \ This variable defines the maximum number of logs can be record. The max value is 100
#define MMI_CALLLOG_MAX_NUM_LOGS (20)
// Calllog \ This variable defines the maximum number of time records in each log record.
#define MMI_CALLLOG_MAX_NUM_TIME_LIST (10)

/**
** FMRadio Customization Data
**
**/
//#define FMR_NAME_MAX_BYTE_SIZE      30  //15 characters, ex: MyChannel1
#define FMR_FREQ_MAX_BYTE_SIZE      10  //5 characters, ex: 100.7
//#define FMR_NAME_MAX_WORD_SIZE      FMR_NAME_MAX_BYTE_SIZE/2
#define FMR_FREQ_MAX_WORD_SIZE      FMR_FREQ_MAX_BYTE_SIZE/2

#define FMR_CHANNEL_NAME_EMPTY_DISP    L"---"
#define MMI_FMRADIOSRV_DEFAULT_FREQ     10070


/**
** Notepad Customization Data
**
**/
// NotepadApp \ This variable defines the maximum number of characters for each record name.
#define MMI_NOTEPAD_MAX_NOTE 100

/**
** PHB Customization Data
**
**/
#if defined(__TINY_RAI_STORAGE_SIZE__)
#define MMI_PHB_ADR_SUPPORT_MAX		100
#elif defined(__LOW_RAI_STORAGE_SIZE__)
#define MMI_PHB_ADR_SUPPORT_MAX		300
#else
#define MMI_PHB_ADR_SUPPORT_MAX		2000 //Gax 3000
#endif

#define MMI_PHB_IMPORT_MAX_FILES    300
#define MMI_PHB_NAME_LEN			41
#define MMI_PHB_NUMBER_LEN			40
#define MMI_PHB_COMPANY_LEN			40
#define MMI_PHB_DEPARTMENT_LEN		40
#define MMI_PHB_POSITION_LEN		40
#define MMI_PHB_HOME_ADDRESS_LEN	100
#define MMI_PHB_OFFICE_ADDRESS_LEN	100
#define MMI_PHB_EMAIL_LEN			100
#define MMI_PHB_URL_LEN				100
#define MMI_PHB_NOTE_LEN			100

/* MAX default pre num   by Robin 2010-08-06  */
#define MMI_PHB_MAX_CUS_POHNE_NUM   5

#ifdef __3G_RIL_MMI__
#define MMI_PHB_USIM_MAIL_LEN       206 // RIL return UCS2, so actually the length is 100 + (80, FF FF)
#define MMI_PHB_USIM_GROUP_LEN      82 // Have to check mmi group name len

#define MMI_PHB_USIM_GROUP_ID_NUM   9 // MRL_PHB_GROUPID_NUM
#define MMI_PHB_USIM_NAME_ID_NUM    3 // MRL_PHB_NAMEID_NUM
#define MMI_PHB_USIM_NUMBER_NUM     4 //MRL_PHB_NUMBER_NUM
#define MMI_PHB_USIM_NAME_NUM       5 //MRL_PHB_NAME_NUM
#define MMI_PHB_USIM_MAIL_NUM       4 // MRL_PHB_MAIL_NUM
#define MMI_PHB_USIM_GROUP_NUM      10//MRL_PHB_GROUP_NUM
#endif  //#ifdef __3G_RIL_MMI__

//MSZ_GARY added 09-07-03 for blacklist
#ifdef __APP_MMI_SMALLROM__
#define MMI_PHB_BLACKLIST_SUPPORT_MAX   20
#else
#define MMI_PHB_BLACKLIST_SUPPORT_MAX   100
#endif
//MSZ_GARY end

/**
*  SEA Customization Data
*/
//define the max number of recipients of one editing SMS
#define MIN_RECIPEINS_SIZE                          0

/*
*  SMS Customization Data
*/
/*
*  SMS Customization Data
*/
#if defined(__TINY_RAI_STORAGE_SIZE__)
#define MAX_MSG_ID 50
#define MAX_PHONE_SMS_AMOUNT 50
#elif defined(__LOW_RAI_STORAGE_SIZE__)
#define MAX_MSG_ID 100
#define MAX_PHONE_SMS_AMOUNT 100
#else
#define MAX_MSG_ID 500
#define MAX_PHONE_SMS_AMOUNT 500
#endif

#define MAX_CONCATENATE_PACKAGE 9

/**
** Common Alarm Timer Customization Data
**
**/
// the waiting timer of an auto-snooze alert
#define AUTOSNOOZE_INIT_WAITING_IN_SEC  300

// the max. expired times of an auto-snoozed alarm
#define AUTOSNOOZE_RETRY_MAX    5

/**
** Common StopWatch Customization Data
**
**/
#define MAX_STOPWATCH_ITEM_NUM 20

/**
** File Manager Customization Data
**
**/
//  abort the progress of deletion once any error occurs when users try to delete multiple files (or one folder)
//#define __FILEMGRAPP_MULTIDEL_ERRBREAK__
#define RES_NO_LIMIT 0xFFFF // Huge value
#define FILESIZE_NO_LIMIT 0xFFFFFFFF // Huge value
// These values is maximum support of display. Basically followed by hardware support.

#define COMMON_IMG_MAX_RESOLUTION_JPG_W 4096
#define COMMON_IMG_MAX_RESOLUTION_JPG_H 4096
#define COMMON_IMG_SMALL_MAX_RESOLUTION_JPG_W 1280
#define COMMON_IMG_SMALL_MAX_RESOLUTION_JPG_H 1280


#define COMMON_IMG_MAX_RESOLUTION_JPG_PROG_W 1024
#define COMMON_IMG_MAX_RESOLUTION_JPG_PROG_H 1024
#define COMMON_IMG_MAX_RESOLUTION_BMP_W 1024
#define COMMON_IMG_MAX_RESOLUTION_BMP_H 1024

#define COMMON_IMG_MAX_RESOLUTION_PNG_W  1024
#define COMMON_IMG_MAX_RESOLUTION_PNG_H  1024
#define COMMON_IMG_MAX_RESOLUTION_WBMP_W 1600
#define COMMON_IMG_MAX_RESOLUTION_WBMP_H 1600

#define COMMON_IMG_MAX_FILESIZE_GIF (250 * 1024) // 250 KB
#define COMMON_IMG_MAX_FILESIZE_PNG (800 * 1024) // 800 KB
#define COMMON_IMG_MAX_FILESIZE_WBMP (200 * 1024) // 200 KB
#define COMMON_IMG_MAX_FILESIZE_JPG_PROG (150 * 1024) // 150 KB

// This value is maximum support of display for caller photo.
#define COMMON_IMG_MAX_RESOLUTION_GIF_IMGID_W 240
#define COMMON_IMG_MAX_RESOLUTION_GIF_IMGID_H 320

#define COMMON_IMG_MAX_FILESIZE_JPG_PROG_IMGID   (80*1024)   // prograssive JPG, 80 KB

#define COMMON_IMG_MAX_FILESIZE_JPG_BASE_IMGID   (2*1024*1024)   // baseline JPG, 2 MB
#define COMMON_IMG_ONOFF_MAX_FILESIZE_JPG_BASE_IMGID   (800*1024)   // for on_off, baseline JPG, 800 KB
#ifdef __MMI_SMALL_CALLER_PHOTO__
#define COMMON_IMG_SMALL_MAX_FILESIZE_JPG_BASE_IMGID   (450*1024)   // baseline JPG, 450 KB
#endif

#define COMMON_IMG_MAX_FILESIZE_BMP_IMGID   (1*1024*1024)   // 1 MB
#define COMMON_IMG_MAX_FILESIZE_PNG_IMGID   (150*1024)   // 150 KB
#define COMMON_IMG_MAX_FILESIZE_GIF_IMGID   (150*1024)   // 150 KB

#define COMMON_IMG_MAX_FILESIZE_GIF_WALLPAPER (150 * 1024) // 150 KB

#define COMMON_FOLDER_ITEMCOUNT_MAX     2048

/**
** Hashmap Customization Data
**
**/

// COMMON_STORE_MAX references the upper bound of ADR (MMI_PHB_ADR_SUPPORT_MAX)

#ifdef __APP_MMI_SMALLROM__
#define COMMON_STORE_MAX	(200)
#else
#define COMMON_STORE_MAX	(2000)
#endif

/**
** Common Show Media Name (MP3 Name) when MPlayer background playing in IdleApp and KeyguardApp
**
**/
#if !defined(__GADGETS_MMI__) && !defined(__3D_UI_IDLE_GADGETBAR__) & !defined(__3D_UI_IDLE_MULTIPAGE__)
#define __MMI_COMMON_SHOW_MEDIA_NAME__
#endif

/**
** Calendar Customization Data
**
**/
/* The maximum number of calendar events can be created. */
#ifdef __APP_MMI_SMALLROM__
#define CALENDAR_MAX_EVENTS_LIMITATION 50
#else
#define CALENDAR_MAX_EVENTS_LIMITATION 500
#endif

/**
** ToDoList Customization Data
**
**/
/* The maximum number of ToDoList tasks can be created. */
#ifdef __APP_MMI_SMALLROM__
#define TODOLIST_TASKNUM_MAX            50
#ifdef __APP_MMI_TODOLIST_VTODO__
#endif
#else
#define TODOLIST_TASKNUM_MAX            100
#endif
#define TODOLIST_CONTENTSTR_MAX_CHARS       25
#define TODOLIST_DESCRIPTIONSTR_MAX_CHARS   25
#define TODOLIST_LOCATIONSTR_MAX_CHARS      25
#define MMI_TODOLIST_SETALARM_INDEEDTIME   60
#define MMI_TODOLIST_TASK_SNOOZE_TIME      5


/**
** MAE DataMgr Customization Data
**
**/
// MAE_DATAMGR_EVENT_TABLE_SIZE / MAE_DATAMGR_EVENT_EXCEPTION_TABLE_SIZE must be equal to CALENDAR_MAX_EVENTS_LIMITATION
#define MAE_DATAMGR_EVENT_TABLE_SIZE            CALENDAR_MAX_EVENTS_LIMITATION
#define MAE_DATAMGR_EVENT_EXCEPTION_TABLE_SIZE  CALENDAR_MAX_EVENTS_LIMITATION
// MAE_DATAMGR_TASK_TABLE_SIZE must be equal to TODOLIST_TASKNUM_MAX
#define MAE_DATAMGR_TASK_TABLE_SIZE             TODOLIST_TASKNUM_MAX
#ifdef __APP_MMI_SMALLROM__
#define MAE_DATAMGR_LOG_TABLE_SIZE              100
#else
#define MAE_DATAMGR_LOG_TABLE_SIZE              500
#endif


//DRM Rights Object
#define MAE_DATAMGR_DRM_RO_TABLE_SIZE             (MMI_DRM_RO_RAI_SIZE)



#endif /* __MMI_COMMON_CUSTOM_H__ */
