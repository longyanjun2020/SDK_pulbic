/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright Wavecom S.A. (c) 1994, 1995, 1996
*/

/****************************************************************************/
/*  File    : sys_sys_sig.h                                                    */
/*--------------------------------------------------------------------------*/
/*  Scope   :  Proto def for signatures                                     */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*  Historical :                                                            */
/*--------------------------------------------------------------------------*/
/*
$LogWavecom: G:\projet\gsm\pvcsarch\archives\sys\itf\sys_sig.hi-arc $
 *--------------------------------------------------------------------------
 * Date     | Author | Revision       | Description
 *----------+--------+----------------+-------------------------------------
 * 25.07.03 | kod    | 1.4            | Changed functions prototypes.   Res
 *          |        |                | olution for 11837: Same key for Ope
 *          |        |                | n AT activation and IP stack activa
 *          |        |                | tion                               
 *----------+--------+----------------+-------------------------------------
 * 15.04.03 | jlo    | 1.3            | Update EL SYS to be compliant with 
 *          |        |                | FMS (new flash handler)  Resolution
 *          |        |                |  for 9481: Update EL SYS to be comp
 *          |        |                | liant with FMS (new flash handler) 
 *----------+--------+----------------+-------------------------------------
 * 21.03.03 | rpi    | 1.2            | include stdcomp.h  Resolution for 8
 *          |        |                | 884: What Integration in sys files 
 *----------+--------+----------------+-------------------------------------
 * 18.10.02 | ddo    | 1.1            | Add customer features lock         
 *----------+--------+----------------+-------------------------------------
*/


#ifndef __SYS_SYS_SIG_H__
#define __SYS_SYS_SIG_H__

#include "stdcomp.h"

#include "e2p_stck.ho"
#include "e2p_cust.ho"

/* --------------------------------- signatures --------------------------- */
s32  sys_CheckCustomerFeatures ( u8 *Imei, u32 FeaturesToCheck, u8 *Signature);

s32 sys_BuildCustomerFeatures ( u8 *Imei, u32 FeaturesToWrite);

#ifdef __MSTAR_DUAL_SIM_E2P__
s32 sys_WriteImei (u8 *sys_pu8_ImeiToStore, u8 sys_u8_ModuleId);
#else
s32 sys_WriteImei (u8 *sys_pu8_ImeiToStore);
#endif

#endif /* __SYS_SYS_SIG_HI__ */


