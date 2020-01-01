/**
* @file mmi_mae_retcode.h
*
* This header file defines all the error codes generated in MAE platform.
*
* @version $Id: mmi_mae_retcode.h 1736 2009-09-07 05:34:52Z allan.hsu $
*/

#ifndef __MMI_MAE_RETCODE_H__
#define __MMI_MAE_RETCODE_H__
/*=============================================================*/
// header files
/*=============================================================*/


/*=============================================================*/
// types and definitions
/*=============================================================*/
enum
{
    MAE_RET_SUCCESS                 = 0, ///< operation completed successfully
    MAE_RET_BAD_PARAM               = 1, ///< invalid input parameters
    MAE_RET_FAILED                  = 2, ///< WHAT? every code here is failed
    MAE_RET_OUT_OF_MEMORY           = 3, ///< memory is not enough to complete the operation
    MAE_RET_NOT_SUPPORTED           = 4, ///< the request is not supported
    // MAE_RET_IID_NOTSUPPORTED     = 5, // use MAE_RET_NOT_SUPPORTED instead
    // MAE_RET_CLSID_NOT_SUPPORTED  = 6, // use MAE_RET_NOT_SUPPORTED instead
    MAE_RET_NOT_READY               = 7,
    MAE_RET_NOT_FOUND               = 8, ///< the specified item is not found
    MAE_RET_NOT_EMPTY               = 9, ///< the content is not empty
    MAE_RET_BUSY                    = 10,
    MAE_RET_FS_FULL                 = 11,
    MAE_RET_ABORT                   = 12,
    MAE_RET_FLASH_FULL				= 13,

    MAE_RET_NO_MORE_INSTANCES       = 16, ///< the number of instances exceeds the system limit
    MAE_RET_EVENT_QUEUE_FULL        = 17, ///< shell's event queue is full
    MAE_RET_ILLEGAL_OPERATION       = 18, ///< the operation is not allowed; eg: posting events to an unrelated object,
    ///< or starting an embedded applet when it is not the focused applet
    MAE_RET_UNHANDLED_EVENT         = 19, ///< the event is not handled by the destination object
    MAE_RET_APM_QUEUE_FULL          = 20, ///< APM's action queue is full
    MAE_RET_NO_MORE_APPLETS         = 21, ///< the number of applets exceeds the limit
    MAE_RET_UNHANDLED_MESSAGE       = 22, ///< the rtk message doesn't have a registered handler
    MAE_RET_DUPLICATE_HANDLER       = 23, ///< trying to register an existing message handler again

    MAE_RET_FILE_EXISTS             = 32, ///< file exists
    MAE_RET_FS_PHYSICAL_ERROR       = 33, ///< physical error on file system
    MAE_RET_FOLDER_NOT_FOUND        = 34, ///< folder not found

    MAE_RET_MEDIA_ALREADY_PLAYING   = 48, ///< We cannot play a media file if it is already playing
    MAE_RET_MEDIA_ALREADY_STOPPED   = 49, ///< We cannot stop a media file if it is already stopped
    MAE_RET_MEDIA_REJECT            = 50, ///< There is other clients occupying media resousrce.
    MAE_RET_MEDIA_INVALID_CLIENT    = 51, ///< The client is invalid or already removed
    MAE_RET_RESCTRL_RESOURCE_OCCUPIED    = 52, ///< Cannot obtain the control of resource since there's someone use it with higer priority
    MAE_RET_CAMERA_REJECT           = 56,  ///< the giving camera command is rejected by EMA

    MAE_RET_STATUS_NOT_MATCH    =57, ///When the status is different between sorting table and contacts.
	MAE_RET_USE_MULTI_UNHOOK = 58,
	MAE_RET_EXCEED_1PNT_MAX_HOOK = 59,

    MMI_RET_OVERCAPACITY            = 100,

    MAE_RET_OVER_MAX_OPENED_FILES = 300,
    MAE_RET_OVER_MAXIMUM_LIST_NUMBER,
    MAE_RET_COMMAND_QUEUE_IS_EMPTY,
    MAE_RET_NO_THIS_COMMAND_LIST_ID,
    MAE_RET_CURRENT_CONTEXT_ILLEGAL,
    MAE_RET_FSTREAM_NOT_FOUND,
    MAE_RET_FILE_ERROR,
    MAE_RET_NO_FILE,
    MAE_RET_NO_CURRENT_CONTEXT,
    MAE_RET_NO_SOURCE_PATH,
    MAE_RET_NO_FILE_LIST,
    MAE_RET_NO_REGISTERED_PATH,
    MAE_RET_LISTING_ANOTHER_FOLDER,
    MAE_RET_IGONE_DATA,
    MAE_RET_CURRENT_COMMAND_IS_EMPTY,
    MAE_RET_NO_ERROR_PROGRESSING,
    MAE_RET_MOVE_COMPLETED,
    MAE_RET_FILESYSTEM_ERROR,
    MAE_RET_COMMAND_IS_RUNNING,
    MAE_RET_ERROR_GET_FREE_SPACE,
    MAE_RET_ERROR_GET_FILE_INFORMATION,
    MAE_RET_FILENAME_TOO_LONG,
    MAE_RET_NO_DIRECTORY,
    MAE_RET_ERROR_PATH_LEN,
    MAE_RET_LIST_QUEUE_IS_EMPTY,
    MAE_RET_HANDLE_NOT_FOUND,
    MAE_RET_FILE_NUMBER_UPDATE,
    MAE_RET_FILE_NUMBER_COMPLETED,
    MAE_RET_FILE_NUMBER_ABORTED,
    MAE_RET_FILE_NUMBER_NOTIFY_NUMBER,
    MAE_RET_FILE_NUMBER_IS_ZERO,
    MAE_RET_OVER_MAXIMUM_MARK_NUMBER,
    MAE_RET_OVER_UPBOUND_MARK_NUMBER,
    MAE_RET_NO_MARK_DATA,
    MAE_RET_CAN_NOT_ERASE,
    MAE_RET_ERROR_OPEN_COUNT,
    MAE_RET_NO_THIS_FSTREAM,
    MAE_RET_ERROE_COMMAND_TYPE,
    MAE_RET_FILE_NUMBER_OVER_CURRENT,
    MAE_RET_OVER_MAXIMUM_SORTING_NUMBER,
    MAE_RET_SORTING_NOT_READY,
    MAE_RET_WAITING_FOR_SORT_DATA,
    MAE_RET_MARK_NOT_FOUND,
    MAE_RET_MARK_EXIST,
    MAE_RET_DISABLE_MARK_FOLDER,
    MAE_RET_FILE_NOT_EXIST,
    MAE_RET_SAME_NAME_ERROR,
    MAE_RET_FILE_IS_USING,
    MAE_RET_ACCESS_DENY,
    MAE_RET_ACCESS_ALLOW,
    MAE_RET_FILE_SYSTEM_SPSPEND,
    MAE_RET_FILE_SYSTEM_RUNNING,
    MAE_RET_WRITE_LESS_THAN_REQUEST,
    MAE_RET_NOT_EOF,

    MAE_RET_CLOSE_ERROR,
    MAE_RET_STEP_IN_ERROR,
    MAE_RET_MOUNT_ERROR,
    MAE_RET_FRAGMENTATION_ERROR,
    MAE_RET_MEMORY_FULL_ERROR,
    MAE_RET_EMPTY_FILE_ERROR,
    MAE_RET_EXISTING_DIR_ERROR,
    MAE_RET_TOO_MUCH_FILES_ERROR,
    MAE_RET_NOT_EXISTING_DIR,
    MAE_RET_PHYSICAL_ERROR,
    MAE_RET_PROTECTED_FILE,
    MAE_RET_READ_ERROR,
    MAE_RET_WRITE_ERROR,
    MAE_RET_NOT_FORMATTED_ERROR,
    MAE_RET_NOT_EMPTY_DIR_ERROR,
    MAE_RET_INVALID_NAME_ERROR,
    MAE_RET_BAD_PARAM_ERROR,
    MAE_RET_NOT_EXISTING_VOL,
    MAE_RET_NOT_MOUNTED_ERROR,
    MAE_RET_EOF,
    MAE_RET_LIST_DIR_ERROR,
    MAE_RET_MEMORY_ERROR,
    MAE_RET_NOT_PRESENT_ERROR,
    MAE_RET_OPEN_ERROR,
    MAE_RET_UNMOUNT_ERROR,
    MAE_RET_INIT_ERROR,
    MAE_RET_ASYNC_ABORT,
    MAE_RET_ASYNC_COMPLETED,
    MAE_RET_VOLUME_FULL,
    MAE_RET_RESOURCE_BUS,
    MAE_RET_REJECT,
    MAE_RET_TIMEOUT,
    MAE_RET_NOT_DIR,
    MAE_RET_NOT_FILE,
    MAE_RET_EXISTING_FILE,
    MAE_RET_NO_FILE_HANDLE,
    MAE_RET_ERROR_FILE_HANDLE,
    MAE_RET_FILE_CORRUPTED,
    MAE_RET_INVALID_NAME_LEN,
    MAE_ALLOCATE_BUFFER_FAIL,  //v2.03 will change to "MAE_RET_ALLOCATE_BUFFER_FAIL"
    MAE_RET_ALLOCATE_BUFFER_FAIL,
    MAE_RET_FAT_FUNCTION_NOT_SUPPORT,
    MAE_RET_FAT_NO_DEVICE,
    MAE_RET_NO_AVAIL_STORAGE,
    MAE_RET_CREATE_FOLDER_FAIL,
    MAE_RET_LIST_END,
    MAE_RET_DISK_DIRTY,
    MAE_RET_TBL_NOTSAME,
    MAE_RET_CHECKDISK_ABORT,
    MAE_RET_ROOT_FULL,
    MAE_RET_DISK_LOCK,
    MAE_RET_NO_PARPATH,
    MAE_RET_NULL_SESSION,
    MAE_RET_DIR_CORRUPTED,
    MAE_RET_DEL_ALL_BATCH_CMD_FOR_ABORT,
    MAE_RET_ABORT_OK_FILE_LAST_OP_OK,
    MAE_RET_ABORT_OK_FILE_LAST_OP_FAIL,

    MAE_RET_CONFLICT_NOT_INDICATED,//Return code for Resource Conflict Subject
    MAE_RET_CONFLICT_BT_ON,
    MAE_RET_CONFLICT_OPP,
    MAE_RET_CONFLICT_EMU,
    MAE_RET_CONFLICT_VIDEO_PLAYBACK,
    MAE_RET_CONFLICT_FM_RECORDING,

    /// begin return code for network
	MAE_RET_DATALINK_ALREADY_ACTIVATED,
    /// end return code for network

	/// begin return code for WAP launcher
	MAE_RET_WAP_NETWORK_ERROR, 
	MAE_RET_WAP_DOWNLOAD_FAILED,
	MAE_RET_WAP_INIT_FAILED,
	MAE_RET_WAP_DOWNLOAD_FAILED_BY_ENDKEY,
	/// end return code for WAP launcher

	
    /// begin return code for DRM
    MAE_RET_DRM_RIGHTS_INVALID,
    MAE_RET_DRM_RIGHTS_NEED_INSTALL,
    MAE_RET_DRM_RIGHTS_INSTALL_FAIL,
    MAE_RET_DRM_RIGHTS_RAI_FULL,
    MAE_RET_DRM_FILE_ERROR,
    MAE_RET_DRM_FILE_UNSUPPORTED,
    /// end return code for DRM

    /// begin return code for Wi-Fi
    MAE_RET_CERT_FULL,
    MAE_RET_CERT_DUPLICATE,
    MAE_RET_CERT_FORMAT_ERROR,
    MAE_RET_CERT_EXPIRED,
    /// end return code for Wi-Fi

	MAE_RET_LICENSE_NOT_EXIST,
	MAE_RET_LICENSE_MISMATCH,
	MAE_RET_PASSWORD_MISMATCH,

    //MULTI-TOUCH
    MAE_RET_MULTI_FINGER,
    MAE_RET_NOT_FIRST_FINGER,
    MAE_RET_HOOKED,


    MAE_RET_UNKNOWN_ERROR = 0x1000,
    MAE_RET_FS_ERROR = (~0)
};

#endif // __MAE_RETCODE_H__
/*=============================================================*/
// end of file
