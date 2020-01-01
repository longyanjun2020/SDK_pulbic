#ifndef __FS_TEST_CASE_H__
#define __FS_TEST_CASE_H__

#include <string.h>
#include "sys_rtk_vmoshi.h"
#include "sys_vm_dbg.ho"
#include "cus_os.hc"
#include "sys_MsWrapper_cus_os.h"
#include "sys_MsWrapper_cus_os_mem.h"
#include "mdl_vfs_fat.ho"

#define VFS_TEST_LOG (_CUS11 | LEVEL_1)
#define VFS_TEST_BUFFER_ALIGN 32
#define VFS_TEST_BACKUP_PATH L"backup"
#define VFS_TEST_PATH L"/CARD/test"
#define VFS_TEST_PATH_1 L"/CARD/sysbt"
#define VFS_TEST_PATH_2 L"/NOR0/test001"
#define VFS_TEST_PATH_3 L"/CARD/test001"
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum {
#include "srv_fs_test_message_define__.hi"
};

typedef struct FS_TEST_FILE_BUFFER {
    u32 curIndex;
    u32 total;
    u32 *pArrayBuffer;
    u32 *pArrayBuffer_align;
    s32 (*generate_buffer) (void* this);
    s32 (*fill_Array) (void* this, u32 number, VFS_PartialListFileInfo_t* pbuffer);
    s32 (*destroy_buffer) (void* this);
} fs_test_file_buffer;

typedef struct FS_TEST_FILE_LIST {
    u32 id;
    s32 sessionID;
    u16 curPath[255];
    u32 totalNumEntry;
    fs_test_file_buffer idList;
    fs_test_file_buffer fileInfoList;
    VFS_NotifyCb pfnNotifyCb;
} fs_test_file_list_t;

u32 fs_test_case_init(void);
u32 fs_test_case_parser(void *pReceivedMsg);

#endif
