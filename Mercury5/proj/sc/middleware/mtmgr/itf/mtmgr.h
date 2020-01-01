#ifndef MTMGR_H
#define MTMGR_H


#include "cus_os.hc"
#include "vm_types.ht"
#include "mdl_vfs_struct.h"
#include "vm_msgof.hc"

/*
 * The enumeration is defined only for mount manager, don't use it anywhere else
 */
typedef enum {
  MTMGR_MSGTYP_MOUNT = CUS_MBX_MTMGR,
  MTMGR_MSGTYP_UNMOUNT,
  MTMGR_MSGTYP_FORCE_UNMOUNT,
  MTMGR_MSGTYP_FORCE_UNMOUNT_WITHOUT_FLUSH,
  MTMGR_MSGTYP_RM_ALIAS,
  MTMGR_MSGTYP_UNMOUNTLESS,
  MTMGR_MSGTYP_MASS_MOUNT,
  MTMGR_MSGTYP_MASS_UNMOUNT,
  MTMGR_MSGTYP_MMI_MOUNT_DEV,
  MTMGR_MSGTYP_MMI_UNMOUNT_DEV,
  MTMGR_MSGTYP_MMI_MOUNT,
  MTMGR_MSGTYP_MMI_UNMOUNT,
} MtMgr_MsgType_e;

typedef enum {
  MTMGR_STATUS_HOST_MODE,
  MTMGR_STATUS_DEVICE_MODE, /* mass storage */
} MtMgr_Status_e;

/* common api */
s32 MtMgr_Mount(VFS_VOL_TYPE  vol, VFS_DevType_e dev);
s32 MtMgr_UnMount(VFS_VOL_TYPE  vol);
s32 MtMgr_FrcUnMount(VFS_VOL_TYPE  vol);
s32 MtMgr_FrcUnMountNoFlush(VFS_VOL_TYPE  vol);
s32 MtMgr_MassMount(void);
s32 MtMgr_MassUnMount(void);

MtMgr_Status_e MtMgr_StatusGet(void);

/* specific for mmi query */
s32 MtMgr_MMI_MountDev(VFS_VOL_TYPE  vol, VFS_DevType_e dev);
s32 MtMgr_MMI_UnMountDev(VFS_VOL_TYPE  vol);
s32 MtMgr_MMI_Mount(VFS_VOL_TYPE  vol);
s32 MtMgr_MMI_UnMount(VFS_VOL_TYPE  vol);
s32 MtMgr_MMI_Vol2Dev(VFS_VOL_TYPE vol);
s32 MtMgr_MMI_Dev2Vol(VFS_DevType_e dev);

/* specific for fs internal action */
s32 MtMgr_FsMount(VFS_VOL_TYPE  vol, VFS_DevType_e dev);
s32 MtMgr_FsUnMount(VFS_VOL_TYPE  vol);



#endif /* MTMGR_H */

