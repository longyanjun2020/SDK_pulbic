/*
**  Important : This software is protected by Copyright and the information
**              contained herein is confidential. Distribution, reproduction
**              as well as exploitation and transmission of its contents is
**              not allowed except if expressly permitted. Infringments
**              result in damage claims.
**              Copyright Wavecom S.A. (c) 1994, 2002 
*/

/****************************************************************************/
/*  File    : sys_sys_vm_ftr.h                                                     */
/*--------------------------------------------------------------------------*/
/*  Scope   :  open embeded features definition.                            */
/*                                                                          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
/* Date     | Author | Modification                                         */
/*----------+--------+------------------------------------------------------*/
/* 26.07.02 | ECH    | Creation.                                            */
/*----------+--------+------------------------------------------------------
$log
***************************************************************************/

#ifndef __SYS_SYS_VM_FTR_H__
#define __SYS_SYS_VM_FTR_H__

#include "vm_types.ht"


/* SCB is a macro to set the right feature bit in the right double word. */
#define SCB(Wd, Feat, Status) (((Feat / 32) == Wd) ? (Status ? 0xFFFFFFFF : ~(1<<(Feat&31))) : 0xFFFFFFFF)

#define FTR_NOT_PROVIDED 0
#define FTR_PROVIDED     1


/* Enumeration of all features. Be carefull, a new feature must be added    */
/* only at the end of the enum.                                             */

enum
     {P900_FTR,
      E900_FTR,
      G850_FTR,
      G1800_FTR,
      G1900_FTR,
      EFR_FTR,
      HR_FTR,
      RTC_FTR,
      AMR_FTR,
      FAX_C1_FTR,
      FAX_C2_FTR,
      ECM_FTR,
      GSM_ALTERNATE_FTR,
      GPRS_CLASS_12_FTR,
      DATA_FTR,
      DTX_DATA_FTR,
      DATA_144_FTR,
      V42_FTR,
      V42_BIS_FTR,
      MNP2_FTR,
      IRCOM_FTR,
      IROBEX_FTR,
      NT_6K_FTR,
      FAST_SCAN_FTR,
      SIM_5V_FTR,
      SIM_3V_FTR,
      SIM_REMOVAL_FTR,
      SIM_TOOL_KIT_FTR,
      SMART_CARD_FTR,
      SIM_SPEED_ENH_FTR,
      QUICK_OFF_FTR,
      SWITCH_ATT_FTR,
      NUMERICAL_GAIN_FTR,
      OFF_WHEN_UNPLG_FTR,
      ECHO_WAVECOM_FTR,      
      CPHS_FTR,
      LOC_FTR,
      INT_DETECT_FTR,
      UART2_FTR,
      QUADRIBAND_AUTO_FTR,
      SIM_1V8_FTR,
      EGPRS_FTR,
      DATA_HR_FTR,
      /* WARNING : 16 last features are reserved for commercial ones. Add normal features before */
      /* COMMERCIAL FEATURES BEGIN AT 48 (COM_FEAT=48,) */
      /* WARNING : 16 last features are reserved for commercial ones. Add normal features before */
      OPEN_AT_FTR=48,
      GPRS_FTR,          /* if not set, revert to class CC */
      GPRS_CLASS_MAX_FTR, /* if not set, revert to class 2 */
      WAP_FTR,
      NB_FEATURES
     };

#define FTR_SIZE ((NB_FEATURES/32) + 1)
#define GPRS_CLASS_10_FTR  GPRS_CLASS_MAX_FTR   /* commercial feature GPRS_CLASS_MAX_FTR allows Class 10 or more */

typedef u32 AllFtr_t [FTR_SIZE];


/*
 * Ftr is devided in two parts: 
 *   - The 3 most significant bits are used to select the u32 in the AllFeatures table
 *   - The 5 less significant bits are used to select the wanted bit in the 
 *     previously selected u32.
 *   - this macro return 1 if the desired bit in the desired u32 is 1, 0 else
 */
#define IS_ACTIVE_FTR(Ftr, AllFeatures) ((AllFeatures [Ftr>>5] & (1L << (Ftr&31))) >> (Ftr&31))
#define MASK_FTR(Ftr, AllFeatures) (AllFeatures [Ftr>>5] &= ~(1L << (Ftr&31)))

void sys_InitFtrCtx (void);
bool sys_IsActiveFtr (u8 Feature, AllFtr_t AllFeatures);
bool sys_IsActiveFtrRemote (u8 Feature);

#endif // __SYS_SYS_VM_FTR_H__
