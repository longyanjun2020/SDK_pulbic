///////////////////////////////////////////////////////////////////////////////////////////////////
// app_mount.h mount umount header
// create by jeffrey.chen@mstarsemi.com on 2010.03.19
// to define storage monitor mail box structure
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "vm_types.ht"

#include "cus_os.hc"
#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_MsWrapper_cus_os_msg.h"

typedef struct
{
    u16     u16Addr;
    u8      u8Data;

} Storage_t;

typedef union
{
    Storage_t   storage;
    u16         u16AnotherBody;

} vm_msgBody_t;

#include "vm_msgt.ht"


//void MAppMountDefaultStorage(void);
void MDrvSendMsg2StorageTask(void);
void MDrvNotifyStorageMonitorTask(U8 u8Disk);
void Mdl_Stg_SuspendCheckTimerCtrl(u8 u8Active);

