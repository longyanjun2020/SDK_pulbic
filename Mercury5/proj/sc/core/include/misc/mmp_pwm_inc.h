//------------------------------------------------------------------------------
//
//  File        : mmp_pwm_inc.h
//  Description : Header file of PWM common information
//  Author      : Alterman
//  Revision    : 1.0
//
//------------------------------------------------------------------------------
#ifndef _MMP_PWM_INC_H_
#define _MMP_PWM_INC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmpf_typedef.h"
#include "drv_pwm.h"
//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

//==============================================================================
//
//                              MACRO
//
//==============================================================================

#define PWM_SET_ID(id)          (id)
#define PWM_SET_PAD(pad)        (pad << 8)
#define PWM_GET_ID(pin)         (pin & 0x1F)
#define PWM_GET_PAD(pin)        ((pin & 0x0100) >> 8)

//==============================================================================
//
//                              DATA TYPES
//
//==============================================================================

typedef void PwmCallBackFunc(MMP_ULONG sr);

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

/* PWM clock is combined with two sets of pulse configurations, A & B */
typedef enum _MMP_PWM_PULSE_ID {
    MMP_PWM_PULSE_ID_A = 0,
    MMP_PWM_PULSE_ID_B
} MMP_PWM_PULSE_ID;

/* PWM interrupts */
typedef enum _MMP_PWM_INT {
    MMP_PWM_INT_PULSE_A = 0x0,  ///< one pulse of A
    MMP_PWM_INT_PULSE_B,        ///< one pulse of B
    MMP_PWM_INT_ONE_ROUND       ///< one round of A/B pulses
} MMP_PWM_INT;

/* PWM engine ID */
typedef enum _MMP_PWM_PIN {
    MMP_PWM0_PIN = DRV_PWM_0,
    MMP_PWM1_PIN,
    MMP_PWM2_PIN,
    MMP_PWM3_PIN,
    MMP_PWM4_PIN,
    MMP_PWM5_PIN,
	MMP_PWM6_PIN,
	MMP_PWM7_PIN,
    MMP_PWM_PIN_MAX
} MMP_PWM_PIN;

/* PWM pad mode */
typedef enum _MMP_PWM_PAD_MODE {
    MMP_PWM_PAD_MODE0 = DRV_PWM_PAD_MODE0,
	MMP_PWM_PAD_MODE1 = DRV_PWM_PAD_MODE1,
	MMP_PWM_PAD_MODE2 = DRV_PWM_PAD_MODE2,
	MMP_PWM_PAD_MODE3 = DRV_PWM_PAD_MODE3,
	MMP_PWM_PAD_MODE4 = DRV_PWM_PAD_MODE4,
	MMP_PWM_PAD_MODE_NOSUP = DRV_PWM_PAD_MODE_NOSUPPORT,
	MMP_PWM_PM_PAD_MODE0 = DRV_PWM_PM_PAD_MODE0,
	MMP_PWM_PM_PAD_MODE1 = DRV_PWM_PM_PAD_MODE1,
	MMP_PWM_PM_PAD_MODE2 = DRV_PWM_PM_PAD_MODE2,
	MMP_PWM_PM_PAD_MODE_NOSUP = DRV_PWM_PM_PAD_MODE_NOSUPPORT
} MMP_PWM_PAD_MODE;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

/* Pulse configuration for one set */
typedef struct _MMP_PWM_ATTR {
    MMP_UBYTE   ubID;           ///< PWM controller engine ID
    MMP_PWM_PULSE_ID uPulseID;  ///< attribute for PWM pulse ID (A/B)
    MMP_ULONG   ulClkDuty_T0;
    MMP_ULONG   ulClkDuty_T1;
    MMP_ULONG   ulClkDuty_T2;
    MMP_ULONG   ulClkDuty_T3;
    MMP_ULONG   ulClkDuty_Peroid;
    MMP_UBYTE   ubNumOfPulses;  ///< number of pulses
} MMP_PWM_ATTR;

#endif // _MMP_PWM_INC_H_

