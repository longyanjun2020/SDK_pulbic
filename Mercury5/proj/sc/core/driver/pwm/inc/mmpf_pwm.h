#ifndef _MMPF_PWM_H_
#define _MMPF_PWM_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_pwm_inc.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define PWM_SEM_TIMEOUT			2000

#define PWM_MAX_NUM_P0          (8)
#define PWM_MAX_NUM_P1          (10)
#define PWM_MAX_NUM             (8)

#define PWN_GET_PIN_OFST(pin)   (PWM_GET_PAD(pin) == 0 ? \
                                 PWM_GET_ID(pin) : \
                                (PWM_GET_PAD(pin)*PWM_MAX_NUM) + PWM_GET_ID(pin) - 4)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPF_PWM_Initialize(void);
MMP_ERR MMPF_PWM_SetAttribe(MMP_PWM_ATTR *attr);
MMP_ERR MMPF_PWM_ControlSet(MMP_UBYTE ubID, MMP_UBYTE control);
MMP_ERR MMPF_PWM_EnableInterrupt(MMP_UBYTE ubID, MMP_BOOL bEnable,
                    PwmCallBackFunc *CallBackFunc, MMP_PWM_INT intr);
MMP_ERR MMPF_PWM_SetOutputPin(MMP_PWM_PIN pwm_pin, MMP_PWM_PAD_MODE pad_mode);
MMP_ERR MMPF_PWM_OutputPulse(MMP_PWM_PIN pwm_pin, MMP_ULONG shift,
                    MMP_ULONG ulFreq, MMP_ULONG ulDuty, MMP_BOOL bHigh2Low,
                    MMP_BOOL bEnableIntr, PwmCallBackFunc *cb,
                    MMP_ULONG ulNumOfPulse);

#endif // _MMPF_PWM_H_