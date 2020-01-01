#ifndef MTMGR_H
#define MTMGR_H


#include "cus_os.hc"
#include "vm_types.ht"
#include "mdl_vfs_struct.h"
#include "vm_msgof.hc"


/*
 * The enumeration is defined only for mount manager, don't use it anywhere else
 */
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
typedef enum {
#include "mdl_mtmgr_message_define__.hi"
} MtMgr_MsgType_e;

typedef enum {
  MTMGR_STATUS_HOST_MODE,
  MTMGR_STATUS_DEVICE_MODE, /* mass storage */
} MtMgr_Status_e;

s32 MtMgr_Mount(VFS_VOL_TYPE  vol, VFS_DevType_e dev);
s32 MtMgr_UnMount(VFS_VOL_TYPE  vol);
s32 MtMgr_FrcUnMount(VFS_VOL_TYPE  vol);
s32 MtMgr_FrcUnMountNoFlush(VFS_VOL_TYPE  vol);
s32 MtMgr_MassMount(void);
s32 MtMgr_MassUnMount(void);
MtMgr_Status_e MtMgr_StatusGet(void);

s32 MtMgr_MMI_MountDev(VFS_VOL_TYPE  vol, VFS_DevType_e dev);
s32 MtMgr_MMI_UnMountDev(VFS_VOL_TYPE  vol);
s32 MtMgr_MMI_Mount(VFS_VOL_TYPE  vol);
s32 MtMgr_MMI_UnMount(VFS_VOL_TYPE  vol);
s32 MtMgr_MMI_Vol2Dev(VFS_VOL_TYPE vol);
s32 MtMgr_MMI_Dev2Vol(VFS_DevType_e dev);

s32 MtMgr_FsMount(VFS_VOL_TYPE  vol, VFS_DevType_e dev);
s32 MtMgr_FsUnMount(VFS_VOL_TYPE  vol);

/* specific for gpd hotswap */
s32 MtMgr_GPD_Mount(VFS_VOL_TYPE vol, VFS_DevType_e dev);
s32 MtMgr_GPD_UnMount(VFS_VOL_TYPE vol, bool isAlias);
s32 MtMgr_GPD_UnMountLess(VFS_VOL_TYPE  vol);
bool MtMgr_GPD_TryRtDirList(VFS_VOL_TYPE vol);
void MtMgr_GPD_CheckNotCloseFile(U8 volType, U8 devType);

/* lock filesystem for mount/umount */
void MtMgr_GPD_LockFs(void);
void MtMgr_GPD_UnLockFs(void);

s32 MtMgr_Vol2Dev(VFS_VOL_TYPE vol);

#endif /* MTMGR_H */

