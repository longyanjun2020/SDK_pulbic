/****************************************************************************/
/*  $Workfile::   sys_sys_hwid.hi                                             $ */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Hardware ID related functions                                */
/*                                                                          */
/*  Contents:   sys_GetHardwareId                                           */
/*              sys_SetHardwareId                                           */
/*                                                                          */
/*                                                                          */
/****************************************************************************/



#ifndef __SYS_SYS_HWID_H__
#define __SYS_SYS_HWID_H__

#ifdef __ARMCC_VERSION
#define HWID_INLINE __inline
#else
#define HWID_INLINE static
#endif


/****************************************************************************/
/* COMPATIBILITY STUFF                                                      */
/****************************************************************************/

#define hwl_GetHardwareId() sys_GetHardwareId()

#endif /*  __SYS_SYS_HWID_H__  */

