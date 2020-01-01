/******************************************************************************/
/*  File    :   sys_reg.h                                                     */
/*----------------------------------------------------------------------------*/
/*  Scope   :   System related registers                                      */
/*                                                                            */
/******************************************************************************/
#ifndef __SYS_REG_H__
#define __SYS_REG_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "kernel_cmu.h"
#include "kernel_itctrl.h"
#include "kernel_pmu.h"
#include "kernel_padctrl.h"
#include "kernel_bbtop.h"
#include "kernel_gpio.h"
#include "kernel_sysreg.h"
#include "kernel_dsp.h"

//------------------------------------------------------------------------------
// Global Variable Declarations
//------------------------------------------------------------------------------
extern volatile KeCmu_t         *const KeCmu;
extern volatile W5IrqControl_t  *const W5IrqControl;
extern volatile KePmu_t         *const g_ptKePmu;
extern volatile KePadCtrl_t     *const g_ptKePadCtrl;
extern volatile BbTop_t         *const g_tBbTop;
extern volatile KeGpioCtrl0_t   *const g_ptKeGpioCtrl0;
extern volatile KeGpioCtrl1_t   *const g_ptKeGpioCtrl1;
extern volatile W5SysReg_t      *const W5SysReg;
extern volatile W5Dpram_t       *const g_ptW5Dpram;
extern volatile u16             *g_ptDspReset;


#endif //__SYS_REG_H__
