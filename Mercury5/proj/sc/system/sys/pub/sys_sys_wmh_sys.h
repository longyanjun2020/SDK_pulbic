/****************************************************************************/
/*  File    : sys_sys_wmh_sys.h                                                    */
/*--------------------------------------------------------------------------*/
/*  Description:  SYS Hidden API                                            */
/*                                                                          */
/*  Contents: Hidden API prototypes for SYS                                 */
/*                                                                          */
/****************************************************************************/

#ifndef __SYS_SYS_WMH_SYS_H__
#define __SYS_SYS_WMH_SYS_H__

#include "vm_types.ht"
#include "sys_sys_vm_sys.h"
#include "vm_msgof.hc"
#include "vm_app.ho"

/****************************************************************************/
/*  SYS functions                                                           */
/****************************************************************************/
/****************************************************************************/


/************************************************************/
/*                                                          */
/************************************************************/
#define VM_SYS_MEM_PROT_WAVECOM_RAM     2
#ifndef VM_MSG_DEF
#define VM_MSG_DEF(_ENUM_, _UNION_)		_ENUM_,
#endif
enum{
#include "sys_sys_wmh_message_define__.hi"
};
/************************************************************/
/*                     Features Management                  */
/************************************************************/

bool    vm_sysCheckCustomerFeatures(u8 *Imei, u32 FeaturesToCheck, u8 *Signature);
void    vm_sysBuildCustomerFeatures(u8 *Imei, u32 FeaturesToWrite);

/************************************************************/
/*                     Miscellaneous                        */
/************************************************************/
void    vm_sysHwlDwl(void);
void    vm_sysKeReset(void);
void    vm_sysCustomEnable32k(bool Enable);
void    vm_sysGetRamInfo(u32 * GlobalRamSize, u32 * CustRamSize);
void    vm_sysDelayWatchDogReset(void);
u8      vm_sysGetInfoReset(void);
void    vm_sysSetInfoReset(u8 i__u8_ScrValue);
void    vm_sysKeFullReset(void);
bool    vm_sysWatchDogRstOccured(void);

#endif // __SYS_SYS_WMH_SYS_H__
