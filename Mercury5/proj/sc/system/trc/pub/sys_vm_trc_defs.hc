/**
 * \file vm_trc_defs.hc
 * \brief  Debug Screen Service header file
 *
 */

#ifndef __SYS_VM_TRC_DEFS_HC__
#define __SYS_VM_TRC_DEFS_HC__


#include "sys_vm_dbg.ho"

/****************/
/* Trace levels */
/****************/

/*
** Care ... Level 4, 5, 6
** Are reserved for cyclic Evts
** ie Paging, Meas, BattLev ...
*/
#define LEV_PROT_UP     LEVEL_7  /* Messages Dumps */
#define LEV_PROT_DWN    LEVEL_8  /* Messages Dumps */

#define MSR_QUAL        LEVEL_15

/*******************/
/* Flow Identifier */
/*******************/

#define RADIO_FLW        1
#define BSIC_FLW         2
#define MEAS_FLW         3
#define L2PROT_FLW       4
#define CBCH_FLW         5
#define SYSINF_FLW       6
#define CELENV_FLW       7
#define PLMNINF_FLW      8
#define PAGING_FLW       9
#define SCAN_FLW         10
#define SYSINF_SCAN_FLW  SCAN_FLW

#define MSSTA_FLW        11
#define BFI_FLW          12
#define TXP_FLW          13
#define SYNC_SCAN_FLW    14
#define RXLEV_SCAN_FLW   15
#define TST_TRANSMIT_FLW 16
#define RACH_FLW         17
#define IDLE_QUAL_FLW    18
#define DEDI_QUAL_FLW    19

/***********************************/
/* MSSTA_FLW : values for MS state */
/***********************************/
#define STA_ACCESS      3 /* RACHing                       */
#define STA_DEDI        4 /* RR Connection running         */


#endif /* __SYS_VM_TRC_DEFS_HC__ */
