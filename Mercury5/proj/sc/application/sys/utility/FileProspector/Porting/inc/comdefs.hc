/****************************************************************************/
/*  File    : comdefs.hc                                                    */
/*--------------------------------------------------------------------------*/
/*  Scope   : GSM project common define flags file                          */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/****************************************************************************/

#ifndef __COMDEFS_HC__
#define __COMDEFS_HC__

#if !defined(WIN32)
#include "sys_sys_vm_ftr.h"
#endif /* !defined(WIN32) */

/* ----------------- radio dependent flags ------------------ */
#define __L1C_PLL_PWR_CTRL__

#define __MS_CLASS10__



/* ----------------- WISMO dependent flags ------------------ */

#define __ALL_PATCHES__

/* ----------------- miscellaneous flags ------------------ */

#if defined(__DEBUG__)
#define __WATCH__
//#define __CPU_LOAD__ //! This flag, once set ON , allow to put CPU load on WATCH and hen monitoring it with TMT for example
#if defined(__CPU_LOAD__) && !defined(__WATCH__)
#error "Warning, __CPU_LOAD__ flags is unmeaningful without __WATCH__ flag"
#endif
#define __DIAGNOSE__
#define __RTK_DIAGNOSE__
#define __REMOTE_RTK__
// #define __CHECK_ACTIVITY__ /* Remove un-used E2P items: L1cNbWakeFrame, L1cNbSleepFrame, L1cNbTxFrame */
#ifndef __WIRTI_USE__
#define __L1C_WATCH__
#endif //__WIRTI_USE__
#define __HWL_WATCH__
#define __COMPACT_WATCH__
//#define __L1C_CNF__
#define __SPV_DEBUG__
#define __UTC_JOB_DEBUG__
#define  no__LOGIC_ANALYSER__
#define  no__LOGIC_ANALYSER_OPTION__
#endif

#if !defined(__NO_POWER_DOWN__)
#ifndef __I_SW__
    #define __HWL_PWDN__
#endif
    #define __TASK_PWDN__
    #define __SLEEP_MODE__
    #define __L1C_SYNC_PWDN__
    #define __TEMP_V24_SLEEP_MODE__
#endif
/* ----------- mandatory flag (to be removed from code) ------------ */

#define __CBCH__
#define __L1C_USE_DATA_DTX__

#endif /* __COMDEFS_HC__ */


