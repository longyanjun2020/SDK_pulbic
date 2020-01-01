/**
 * \file sys_sys_tools.h
 * \brief System utilities interface
*/

#ifndef __SYS_SYS_TOOLS_H__
#define __SYS_SYS_TOOLS_H__

#include "vm_types.ht"
#include "sys_sys_vm_sys.h"
#ifdef __MSTAR_DUAL_SIM_E2P__
#include "e2p_stck.ho"
#endif

#ifdef __RTK_OVER_R2__
#define __SYS_OSTICK_EXTENSION__
#endif

#define SYS_FEATURE_JTAG_ENA						0x00000001
#define SYS_FEATURE_MCP_SYNC_ACCESS_ENA			0x00000002
#define SYS_FEATURE_ENHANCED_BACKTRACE_ENA		0x00000004
#define SYS_FEATURE_WDT_ISSUE_DBG_ENA			0x00000008 //disable during run-time and enable in Ke_FullReset
#define SYS_FEATURE_MALLOC_FAIL_FATAL_ENA		0x00000010
#define SYS_FEATURE_MALLOC_FAIL_DOWALK_ENA		0x00000020
#define SYS_FEATURE_NOT_FREE_RM_BUFFER1			0x00000040

#ifdef __SYS_OSTICK_EXTENSION__
#include "sys_rtk_ho.h"
#include "sys_MsWrapper_cus_os_timer.h"

rtk_ErrCode_e sys_RegisterOsTickExMonitor(void);
u64 sys_GetOsTickus(void);
#endif

extern u32 sys_CustomerRAMSize;

void sys_set_WDogRstFlag(u32 value);
u32 sys_get_WDogRstFlag(void);
void sys_set_WDogRstExtFlag(u32 value);
u32 sys_get_WDogRstExtFlag(void);

extern volatile bool sys_CustomerWDogRst;
extern u32  sys_CustomRomSize;
extern u8  CoreVersion[VM_SYS_CORE_VERSION_NB_CHAR];
extern u8  CusVersion[VM_SYS_CORE_VERSION_NB_CHAR];

void sys_DieByWatchDog(void);
void sys_StatusRegister(void);
void sys_SetJtagState(u8 value);
void sys_SetHwWdtDbgState(u8 value);
void sys_SetMallocFailState(u8 value);
u8 sys_GetMallocFailState(void);
bool sys_WatchDogRstOccured(void);
bool sys_SoftRstOccured (void);
bool sys_ExpectedWatchDogRstOccured (void);
bool sys_GetJtagState(void);
bool sys_GetHwWdtDbgState(void);
bool sys_GetSleepModeState(void);
void sys_SetSleepModeState(bool state);
ascii *sys_GetBinInfo(void);
void sys_BinaryInit(void);
u32  sys_GetHardwareId(void);
u32 sys_GetModuleROMsize(void);
u32 sys_GetModuleRAMsize(void);
void sys_GetInfoVersion(ascii *pSize, ascii *pDate, ascii *pTime);
#ifdef __MSTAR_DUAL_SIM_E2P__
bool sys_IsValidImei(vm_Imei_t imei);
#endif
void SysGetCoreVersion(char *pVersion);
void sys_UartPrintf(const char *fmt, ...);
u32 sys_Platform_Verify(void);
void sys_Delay( u32 i_u32_Delay_us );
void resetWatchdog(void);
bool sys_IsUserMode(void);
bool sys_CusLangPackDecompress(void);

#endif /* __SYS_SYS_TOOLS_H__ */


