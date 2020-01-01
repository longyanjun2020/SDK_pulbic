/****************************************************************************/
/*  File    : sys_sys_speed_profile.h                                           */
/*--------------------------------------------------------------------------*/
/*  Scope   : Management of Speed Profile for CPU and DSP frenquencies      */
/*                                                                          */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*  Historical:                                                             */
/*--------------------------------------------------------------------------*/
/*  Date    | Author | Err  |  Modfification                                */
/*----------+--------+------+-----------------------------------------------*/
/* 28.05.07 |  TPO   |      |  Creation                                     */
/****************************************************************************/

#ifndef __SYS_SYS_SPEED_PROFILE_H__
#define __SYS_SYS_SPEED_PROFILE_H__

#include "vm_types.ht"
#include "sys_sys_vm_sys.h"

void                  sys_changeSpeedProfileMmi(vm_sys_SpeedProfile_e speedProfile, vm_sys_SpeedProfileId_e speedProfileId);
void                  sys_changeSpeedProfile(vm_sys_SpeedProfile_e speedProfile, vm_sys_SpeedProfileId_e speedProfileId, vm_sys_SpeedProfileTarget_e speedProfileTarget);
void                  sys_initSpeedProfile(void);
vm_sys_SpeedProfile_e sys_getSpeedProfile(vm_sys_SpeedProfileTarget_e speedProfileTarget);
void                  sys_setSpeedProfile(vm_sys_SpeedProfile_e speedProfile, vm_sys_SpeedProfileTarget_e speedProfileTarget);
void                  sys_getSpeedProfileTable(void **eppProfileTab);
void                  sys_AutoCheckSpeedProfile(void);
void                  sys_InitCpuSpeed(void);

#endif /* __SYS_SYS_SPEED_PROFILE_H__ */

