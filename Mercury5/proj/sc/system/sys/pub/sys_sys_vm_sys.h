/**
 * \page SYSTEM System Management Public Interface
 *
 *
 * \section intro_sec Introduction
 *
 * This document describes the System Management Public Interface
 *
 *  <hr>
 * \section SectionMMI2System 1. MMI to System Interface
 *
 * \li \ref vm_sysGetCoreVersion
 * \li \ref vm_sysExtIntInitialize
 * \li \ref vm_sysExtIntMask
 * \li \ref vm_sysExtIntUnMask
 * \li \ref vm_sysExtIntClear
 * \li \ref vm_sysIsActiveFtr
 * \li \ref vm_sysGetBinInfo
 * \li \ref vm_sysGetHardwareId
 * \li \ref vm_sysWriteImei
 * \li \ref vm_sysGetROMsize
 * \li \ref vm_sysInitKeypadBuffer
 * \li \ref vm_sysKeyProcessed
 * \li \ref vm_sysKeypadSubscribe
 * \li \ref vm_sysParseIPCPOpt
 * \li \ref vm_sysGetCusTaskId
 * \li \ref vm_sysGetCusTaskNumber
 * \li \ref vm_sysSetCusVersion
 * \li \ref vm_sysDelay
 * \li \ref vm_sysChangeSpeedProfile
 * \li \ref vm_sysEnterNoPowerDownModeRegion
 * \li \ref vm_sysLeaveNoPowerDownModeRegion
 *
 *  <hr>
 * \section SectionAudio2MMI 2. System to MMI
 *
 *  \li \ref VM_SYS_INTR_DETECT      message sent when a subscribed External Interrupt is raised
 *
 *  <hr>
 * \section Usage 3. Usage
 *
 *
 */


/*!
 * \file  sys_sys_vm_sys.h
 * \brief MMI to System Public Interface
 *
 *  This file defines the System Management Public interface that is offered to the MMI
 *
 *  The interface allows to :
 *   \li configure an External Interrupt and get message when this one is raised
 *   \li get information about the handset (id, ram and rom sizes...).
 *   \li power off the handset.
 *   \li get information about resets.
 *   \li configure Key management and acknowledge key events (press or release)
 *   \li wait a given number of micro-seconds.
 *   \li manage Seep Profiles (CPU frequency).
 *   \li manage features(stack and customer).
 *   \li convert customer task ID into RTK tasks and vice and versa.
 *
 */
/**
 * \addtogroup Manager
 * @{
 */

#ifndef __SYS_SYS_VM_SYS_H__
#define __SYS_SYS_VM_SYS_H__

#include "vm_types.ht"
#include "sys_sys_vm_ftr.h"

#include "vm_msgof.hc"
#include "vm_kbd.h"

/**
 * \brief List of messages sent by System management to Customer tasks
 *
 */
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum
{
#include "sys_sys_vm_message_define__.hi"
};

/**
 * \brief Speed profile value
 *
 */
typedef enum
{
  VM_SYS_SPEED_PROFILE_SLOW      = 0x00,
  VM_SYS_SPEED_PROFILE_MEDIUM    = 0x01,
  VM_SYS_SPEED_PROFILE_FAST      = 0x02,
  VM_SYS_SPEED_PROFILE_SUPFAST   = 0x03,
  VM_SYS_SPEED_PROFILE_LAST      = 0x04,
  VM_SYS_SPEED_PROFILE_UNCHANGED = 0xFE,
  VM_SYS_SPEED_PROFILE_UNKNOWN   = 0xFF
} vm_sys_SpeedProfile_e;

/**
 * \brief Speed profile ID
 *
 */
typedef enum {
VM_SPEED_PROFILE_ID_CURRENT   = 0x00,
  VM_SPEED_PROFILE_ID_STACK   = 0x01,
  VM_SPEED_PROFILE_ID_APPLI   = 0x02,
  VM_SPEED_PROFILE_ID_EXTERN  = 0x03, /* External usage, ex: calibration. */
  VM_SPEED_PROFILE_ID_LAST    = 0x04
} vm_sys_SpeedProfileId_e;

/**
 * \brief Speed profile target
 *
 */
typedef enum {
  VM_SPEED_PROFILE_TARGET_CPU  = 0x00,
  VM_SPEED_PROFILE_TARGET_DSP  = 0x01,
  VM_SPEED_PROFILE_TARGET_LAST = 0x02
} vm_sys_SpeedProfileTarget_e;

/**
 * \brief ROM size
 *
 */
#define VM_ROM_SIZE_16M             0x200000  /* 16 Mbits */
#define VM_ROM_SIZE_32M             0x400000  /* 32 Mbits */
#define VM_ROM_SIZE_64M             0x800000  /* 64 Mbits */

/**
 * \brief Core and Cust version string size
 *
 */
#define VM_SYS_CORE_VERSION_NB_CHAR 16 ///< including NULL terminator
#define VM_SYS_CUST_VERSION_NB_CHAR 16 ///< including NULL terminator

/**
 * \brief System Function for decoding IPCP PCO
 *
 */
typedef struct {
	u32 dns1;       ///< IP address of Primary DNS
	u32 dns2;       ///< IP address of Secondary DNS
	u32 ip_addr;    ///< IP address of MS given by the network
} vm_sys_ipcp_params_t;

/**
 * \brief Power Down Critical section type
 *
 */
typedef enum
{
    VM_SYS_POWER_DOWN_REGION_NO_SLEEP = 0, ///< No sleep and no 26 MHz clock cut
    VM_SYS_POWER_DOWN_REGION_SLEEP_BUT_CLK  ///< sleep allowed but no 26 MHz clock cut
}  vm_sysPowerDownRegion_t;

typedef enum
{
    SYS_ENABLEDFTR_READ = 1,
    SYS_IMEI_READ,
    SYS_IMEI_2_READ,
    SYS_CUSTOMER_FEATURES_READ,
    SYS_SIGNATURE_CUSTOMER_FEATURES_READ,
    SYS_MPRELEASE_READ,
    SYS_DIRTYE2P_READ,
    SYS_NETMODE_BK_READ,
    SYS_NETMODE_2_BK_READ,
    SYS_SETTINGS_BK_READ,
    SYS_SETTINGS_2_BK_READ,
    SYS_STATUSREPORT_BK_READ,
    SYS_STATUSREPORT_2_BK_READ,
    SYS_SPEEDPROFILECONFIG_READ,
    SYS_IMEI_WRITE,
    SYS_IMEI_2_WRITE,
    SYS_SIGNATURE_CUSTOMER_FEATURES_WRITE,
    SYS_VM_NETMODE_WRITE,
    SYS_VM_NETMODE_2_WRITE,
    SYS_SETTINGS_WRITE,
    SYS_SETTINGS_2_WRITE,
    SYS_STATUSREPORT_WRITE,
    SYS_STATUSREPORT_2_WRITE,
    SYS_DIRTYE2P_WRITE,
} sysE2pType_e;

typedef enum
{
    SYS_TRC_DIAGLEVEL = 1,
    SYS_TRC_EXTENDED_DIAGLEVEL,
    SYS_TRC_GPRSDIAGLEVEL,
    SYS_TRC_EXTENDED2_DIAGLEVEL,
    SYS_TRC_DUALSIM_DIAGLEVEL,
    SYS_TRC_DUALSIM_EXT2_DIAGLEVEL,
    SYS_TRC_SDK_DIAGLEVEL,
    SYS_TRC_MIXED_DIAGLEVEL,
} sysE2pTrcLvl_e;

/****************************************************************************/
/*  SYS functions                                                           */
/****************************************************************************/

void    vm_sysGetCoreVersion(ascii * ps);
bool    vm_sysIsActiveFtr(u8 Feature, AllFtr_t AllFeatures);
ascii * vm_sysGetBinInfo(void);
u32     vm_sysGetHardwareId(void);
#ifdef __MSTAR_DUAL_SIM_E2P__
s32     vm_sysWriteImei(u8 *sys_pu8_ImeiToStore, u8 sys_u8_ModuleId);
#else
s32     vm_sysWriteImei(u8 *sys_pu8_ImeiToStore);
#endif
u32     vm_sysGetROMsize(void);
s32     vm_sysInitKeypadBuffer(u32 LowLimit, u32 UpLimit);
void    vm_sysKeyProcessed(void);
void    vm_sysKeypadSubscribe(u8 mailbox);
s32     vm_sysKeypadGetState(vm_kbdKey_t **pressed_keys);
void    vm_sysParseIPCPOpt(u8 *Buf, u16 Len, vm_sys_ipcp_params_t *result);
u32     vm_sysGetCusTaskId(u32 CusTaskNumber);
u32     vm_sysGetCusTaskNumber(u32 CusTaskId);
void    vm_sysSetCusVersion(char *pCusVersion);
void    vm_sysDelay(u32 i_u32_Delay);
void    vm_sysChangeSpeedProfile(vm_sys_SpeedProfile_e speedProfile, vm_sys_SpeedProfileId_e speedProfileId);
void    vm_sysEnterNoPowerDownModeRegion(vm_sysPowerDownRegion_t Mode);
void    vm_sysLeaveNoPowerDownModeRegion(vm_sysPowerDownRegion_t Mode);
s32     sys_E2pAccessWrapper(sysE2pType_e sysE2pType, void* o__p_Buffer);

/**
 *  @}
 */

#endif // __SYS_SYS_VM_SYS_H__
