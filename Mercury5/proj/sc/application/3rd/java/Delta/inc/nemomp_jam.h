#ifndef __NEMOMP_JAM_H__
#define __NEMOMP_JAM_H__
#include "nemomp_jam_info.h"
#include "nemomp_suite_setting.h"
#include "JamlistMemPool.h" // 20090101: Added

#define MAX_FILENAME_LENGTH 		(256)
#define DEFAULT_FILE_LIST		(2)
#define MAX_WCHAR_FILENAME_LEN         (512)

#define J2ME_GET_NEXT_EVENT_ABORT                  (-0x1234567)

#define nemomp_jamlist_mempool_initialize	initializeJamlistMemoryPool  // 20090101: Changed
#define nemomp_jamlist_mempool_finalize	finalizeJamlistMemoryPool  // 20090101: Changed

#define nemomp_jamlist_mem_malloc(x)             jamlistMalloc(x)  // 20090101: Changed
#define nemomp_jamlist_mem_free(x)               jamlistFree(x)  // 20090101: Changed

#define nemomp_suites_mem_malloc(x)             jamlistMalloc(x)  // 20090101: Changed
#define nemomp_suites_mem_free(x)               jamlistFree(x)  // 20090101: Changed

extern int jam_install_suite_id;
extern int jam_update_removed_suite_id;
/*
 * I/O Modes
 *
 * These are the different I/O modes for opening a file.
 * From javax.microedition.io.Connector.java and
 * com.sun.midp.io.j2me.storage.RandomAccessStream.
 */
/* open for read only */
#define OPEN_READ 					(1)
/* open for write only, create the file if it does not exist */
#define OPEN_WRITE 					(2)
/* truncate file size to 0 */
#define OPEN_READ_WRITE_TRUNCATE 	(-OPEN_READ_WRITE)
/* open for read and write, create the file if it does not exist */
#define OPEN_READ_WRITE 			(OPEN_READ|OPEN_WRITE)

__inline nm_int32 TRANS_INT(nm_wchar *a)
{
    nm_uint8 *_temp = (nm_uint8*) (a);

    return ((_temp[0] << 24) + (_temp[1] << 16) + (_temp[2] << 8) + _temp[3]);
}

__inline nm_int16 TRANS_SHORT(nm_wchar *a)
{
    nm_uint8 *_temp = (nm_uint8*) (a);

    return ((_temp[0] << 8) + _temp[1]);
}

#define TRANS_INTVALUE(a)  \
   ((((a)&0xFF)<<24) + (((a>>8)&0xFF)<<16) + (((a>>16)&0xFF)<<8) + (((a>>24)&0xFF)))

typedef enum
{
    J2ME_NO_ERROR = 0,                      /* Success */
    J2ME_MIDS_NOT_EXIST,                    /* MIDlet suite does not exist */
    J2ME_INSUFFICIENT_MEMORY,
    J2ME_UNDEFINED_SETTING,                 /* Used in SET_SETTING message. */
    J2ME_FILE_NOT_FOUND,
    J2ME_FILE_DONWLOAD_FAILED,              /* general download fail */
    J2ME_FILE_DOWNLOAD_CANT_CREATE_FILE,    /* when file download , we can't open temp file to store data */
    J2ME_FILE_DOWNLOAD_CONNECTION_ABORT,    /* connection lost */
    J2ME_USER_CANCEL,                       /* User Cancel */
    J2ME_ACTION_FAILE,
    J2ME_INSTALL_FAIL,
    J2ME_INSTALL_NUM_OVER,
    J2ME_INVALID_REQUEST,
    J2ME_READ_SUITES_LIST_FAILURE,
    J2ME_PERMISSION_PUSH_EXCLUSIVE = 5000,
    J2ME_PERMISSION_NET_EXCLUSIVE = 5001,
    J2ME_ERROR_TOTAL
} java_error_code_enum;

typedef enum
{
    JAVA_IDLE_STATE,
    JAVA_ACTIVATED_STATE,
    JAVA_PAUSED_STATE,
    JAVA_STATE_TOTAL
} java_status;

// 20081209: Changed
typedef enum
{
    JAVA_NORMAL_MODE,
    JAVA_DIRECT_CLDC_MODE,
    JAVA_DIRECT_MIDP_MODE,
    JAVA_TRUSTED_TCK_MODE,
    JAVA_UNTRUSTED_TCK_MODE,
    JAVA_MODE_TOTAL
} java_mode_enum;

typedef enum
{
    JAM_HTTP_NO_ERROR,
    JAM_HTTP_MEMORY_NOT_ENOUGH,
    JAM_HTTP_OPEN_FILE_ERROR,
    JAM_HTTP_USER_CANCEL,
    JAM_HTTP_STORAGE_NOT_ENOUGH,
    JAM_HTTP_TOTAL
} jam_http_error;

extern nm_suites_list* actived_suites_list;
/*SJH*/
extern int SuiteCnt;
extern int jam_ams_getSuiteCnt(void);


extern int running_suite_id;
extern nm_bool j2me_in_tck_mode;
extern nm_bool is_in_critical_path;
extern nm_uint32 Java_State;

extern nm_char* java_all_filename;
extern nm_uint32 java_all_filename_length;

extern nm_wchar* java_install_download_url;

extern char* nemomp_jam_get_domain(char* storageName);
extern char* nemomp_jam_get_authority(char* storageName);
extern nm_int32 nemomp_jam_read_permission_settings(char* storageName);

extern int nemomp_jam_get_suiteid_from_name(char* storageName);
extern nm_char* nemomp_jam_get_dirpath_from_suiteid(nm_int32 suiteID);

extern int nemomp_jam_get_permission_mode(char* storageName, char* permissionName);
extern int nemomp_jam_get_user_permission_mode(char* storageName, char* permissionName);

extern void nemomp_jam_remove_all(void);
extern void nemomp_jam_recovery(void);

extern nm_suite_detail* nemomp_jam_find_suite_detail_by_suiteid(nm_int32 suiteID);
extern nm_int32 nemomp_jam_get_suites_list(nm_int32 list_start_index, nm_int32 list_count, 
					nm_suites_list** this_saved_mids_listfile_ptr);
extern void nemomp_jam_free_suites_list(void);

extern nm_int32 nemomp_jam_drm_copy_to_receive(nm_wchar *midletName, nm_wchar* sourcePath);

extern char* nemomp_jam_get_storagename_from_suiteid(nm_int32 suiteID);

extern nm_char *nemomp_jam_get_running_suite_storage_name(void);

extern void nemomp_jam_removd_midlet_by_storage_name(nm_char* storageName);

extern void nemomp_jam_touch_need_to_recover_file(char* storage_name);
extern nm_char* nemomp_jam_get_recover_storage_name(void);
extern void nemomp_jam_delete_need_to_recover_file(void);
extern nm_bool nemomp_jam_check_recover_file(void);

extern int nemomp_jam_storage_open(char* pszAsciiFilename, int ioMode);
extern int nemomp_jam_storage_close(int handle);
extern int nemomp_jam_storage_read(int handle, char* buffer, int length);
extern int nemomp_jam_storage_write(int handle, char* buffer, int length);
extern int nemomp_jam_storage_position(int handle, long absolutePosition);
extern int nemomp_jam_storage_getsize(int handle);
extern int nemomp_jam_storage_isexist(char* pszAsciiFilename);
extern int nemomp_jam_storage_delete(char* pszAsciiFilename);
extern int nemomp_jam_storage_rename(char* pszOldFilename, char* pszNewFilename);

extern void nemomp_jam_delete_temp_files(void);

extern nm_uint32 nemomp_jam_get_dec_len(nm_uint32 dec);

extern nm_int32 nemomp_jam_get_permission_settings(nm_int32 suiteID, nm_group_setting *currentSettings, nm_group_setting *maximumSettings);
extern nm_int32 nemomp_jam_set_permission_settings(nm_uint32 suiteID, nm_group_setting *currentSettings);

extern int nemomp_jam_get_suite_count(void); // 20081201: Added

extern int nemomp_jam_storage_check_and_recovery(void); // 20090213: Added

#endif /* __NEMOMP_JAM_H__ */

