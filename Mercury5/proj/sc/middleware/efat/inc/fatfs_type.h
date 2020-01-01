////////////////////////////////////////////////////////////////////////////////
/// @file   fatfs_type.h
/// @author MStar Semiconductor Inc.
/// @brief  EFat type define
////////////////////////////////////////////////////////////////////////////////
#ifndef FATFS_TYPE_H
#define FATFS_TYPE_H

#include "cus_msg.hc"
#include "newLS.h"
#include "fileio_dirent.h"
//------------------------------------------------------------------------------
//Local Defines
//------------------------------------------------------------------------------
#define JD_1970_1_1 2440588 // 1 Jan 1970 in Julian day number


#define MAX_WPATH_DEPTH     262
#define MAX_DELETE_SESSION  5    // actually 4, [0] not used
#define MAX_DELETE_NUM_ONCE 5

#define DOT             L"."
#define DDOT_LONG       L".."
#define SLASH           L"/"
#define NULLEND         L"\x00"
#define U16SEARCH       L'|'

#define ATR_NULL 0x00
#define ATR_RDO  0x01
#define ATR_HID  0x02
#define ATR_SYS  0x04
//#define ATR_VOL 0x08
#define ATR_DIR 0x10
#define ATR_ARC 0x20
//#define ATR_LON (ATR_RDO|ATR_HID|ATR_SYS|ATR_VOL)
#define r_num_lscache 0
#define w_num_lscache 1

extern U32 wstrlen(const char *pStr);
extern char *wstrcat(char *pStr1, const char *pStr2);
extern S32 wstrcmp(const char *pStr1, const char *pStr2 );
extern char * wstrcpy(char *pStr1, const char *pStr2);


#define fs_strcmp(x,y)   wstrcmp(x, y)
#define fs_strlen(x)     wstrlen(x)
#define fs_strcat(x, y)  wstrcat(x, y)
#define fs_strcpy(x, y)  wstrcpy(x, y)
#ifdef LS_DBG
#define LSDBG(x) x
#else
#define LSDBG(x) //x
#endif
#define pls_dbg(fmt, args...)  //efat_dialog(fmt, ##args)
#define pls_dbg1(fmt, args...)  //efat_dialog(fmt, ##args)

#define ASYNCDELDBG(x) //x

//------------------------------------------------------------------------------
// Type and Structure Declaration
//------------------------------------------------------------------------------

typedef struct
{
    u8  CacheHit;
    u8  fire_async_notify;
    LSCACHE * pLScache ;
    DIR * dir_pt;
    u32 cnt_threshold;
    u32 pre_entry_cluster;
    u32 cluster_diff_cnt;
    u32 curposInFileInfoBuf;
    u32 curposInCache;
    u32 req_num;
    u32 cur_num;
}loop_state_t;


typedef struct
{
    async_del_para_t async_del_para;

} vm_EfatAsyncDeleteReq_t;

typedef struct
{
    bool                                isForceDelete;
    u16                                 session;
    VFS_PartialListFilter_t*            pFilter;
    u16                                 Del_path[MAX_WPATH_DEPTH];

} vm_EfatDirDeleteReq_t;

typedef struct
{
    u16                                 session;
    VFS_PartialListFilter_t*            pFilter;
    u16                                 Del_path[MAX_WPATH_DEPTH];

} vm_EfatBatchDeleteReq_t;

typedef struct
{
    u16                                 session;
} vm_EfatDirDeleteCnf_t;

typedef struct
{
    loop_state_t lp;
} vm_EfatAsyncFileNumReq_t;


typedef struct
{
    u8 operation;
    u8 volume;
} vm_EfatAsyncChkdsk_t;

typedef struct
{
    u8 volume;
}vm_EfatAsyncFormat_t;

typedef struct
{
    u8 volume;
}vm_EfatAsyncFrPlScn_t;


typedef union{
    vm_osTimerMsgBody_t                 osTimerMsgBody;
    vm_EfatAsyncDeleteReq_t             EfatAsyncDeleteReq;
    vm_EfatDirDeleteReq_t               EfatDirDeleteReq;
    vm_EfatDirDeleteCnf_t               EfatDirDeleteCnf;
    vm_EfatAsyncFileNumReq_t            EfatAsyncFileNumReq;
    vm_EfatAsyncChkdsk_t                EfatAsyncChkdsk;
    vm_EfatAsyncFormat_t                EfatAsyncFormat;
    vm_EfatAsyncFrPlScn_t               EfatAsyncFrPlScn;
} vm_msgBody_t;

typedef enum
{
    EFAT_NOTIFY_MOUNT_CARD,
    EFAT_EFS_NOTIFY_UNMOUNT_CARD,
    EFAT_EFS_NOTIFY_CHKSUM_PROGRESS,
    EFAT_EFS_NOTIFY_FILE_NUM_UPDATE,
    EFAT_EFS_NOTIFY_ASYNC_DELETE_PROGRESS,
    EFAT_EFS_NOTIFY_MAX_EVENT
} Efat_NotifyEvent_e;


/* ------------------------ Messages identifiers -------------------------- */
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum
{
#include "fatfs_message_define__.hi"
};


/* ------------------------ Timers identifiers -------------------------- */
enum
{
    DEV_EFAT_TIMER_0 = DEV_EFTA_EXTERNAL_MESSAGE + 1,
#if DBG  // for test
    DEV_EFAT_TIMER_1,
    DEV_EFAT_TIMER_2
#endif
};

typedef struct
{
    u32 last_flag;
    u16 root_del_path[MAX_WPATH_DEPTH];
    u16 current_del_path[MAX_WPATH_DEPTH];
} del_path_session_t;


typedef enum
{
//    RM_FILE     =   0x0000,
//    RM_DIR      =   0x0001,
    ASYNC_MODE   =   0x0100,
    RECURSIVE   =   0x0200,
    FORCE_DEL   =   0x0400,
}_FS_RM_OPERATION;

typedef struct
{
    struct dirent efat_dir_entry;
    void* pNext_entry;
} efat_dir_entry_list_t;





#endif // #ifndef FATFS_TYPE_H
