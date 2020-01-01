#ifndef __FMS_E2P_ON_RAI_H__
#define __FMS_E2P_ON_RAI_H__

#ifdef __FMS_E2P_ON_RAI_C__
#define INTERFACE
#else
#define INTERFACE extern
#endif

#include "stdcomp.h"
#include "fms_defs.hm"
#include "fms_e2p_internal.ho" // for FMS_E2P_E2PSIZE

#define E2P_START_RAI_ID                         0xE2F00000
#define E2P_DEFAULT_RAI_ID                       (E2P_START_RAI_ID + 0x0001FFFF)

INTERFACE s32 fms_E2pOnRAI_EngineInit(void);
INTERFACE s32 fms_E2pOnRAI_RawWrite(u32 i__u32_ParamAddr, u32 i__u32_ParamSize);
INTERFACE s32 fms_E2pOnRAI_RawRead(u32 i__u32_ParamAddr, u32 i__u32_ParamSize, void *o__p_Buffer);
INTERFACE s32 fms_E2pOnRAI_MapOutMemory(void);
INTERFACE s32 fms_E2pOnRAI_MapInitMainServices(void);
INTERFACE bool fms_E2pOnRAI_Raw_RestoreDefault(void);
INTERFACE bool fms_E2pOnRAI_BuildDefault(void);
INTERFACE s32 fms_E2pOnRAI_SaveParameters(void *i__p_Parameters);
INTERFACE s32 fms_E2pOnRAI_ReadDefault(u32 i__u32_ParamAddr, u32 i__u32_ParamSize, void *o__p_Buffer);

INTERFACE void fms_E2pOnRAI_Cache_Init(void);
INTERFACE s32 fms_E2pOnRAI_Cache_Write(u32 addr, u32 size, void *buffer, e2p_write_t i__e_WriteMethod);
INTERFACE s32 fms_E2pOnRAI_Cache_Flush(void);

INTERFACE s32 fms_E2pOnRAI_Cleaner(void);
INTERFACE s32 fms_E2pOnRAI_BuildBackup(void);
INTERFACE s32 fms_E2pOnRAI_Restore2Backup(void);

#undef INTERFACE
#endif

