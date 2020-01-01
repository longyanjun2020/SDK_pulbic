#ifndef __FMS_E2P_BACKUP_H__
#define __FMS_E2P_BACKUP_H__

#ifdef __FMS_E2P_BACKUP_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

INTERFACE s32 fms_E2PBackup_Try2BuildDefault(void);
INTERFACE s32 fms_E2pBackup_Detect(void);

#undef INTERFACE
#endif

