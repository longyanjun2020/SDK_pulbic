//==============================================================================
//
//  File        : MotorCtrlFunc.h
//  Description : INCLUDE File for the Motor Driver Function
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================


#ifndef _MOTORCTRLFUNC_H_
#define _MOTORCTRLFUNC_H_

//==============================================================================
//
//                              COMPILER OPTION
//
//==============================================================================

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct MotorCtrl_FUNCTIION {
    void (*MotorCtrl_Initialize)(void);

    void (*MotorCtrl_ZoomPowerOn)(MMP_BOOL OnOFF);
    void (*MotorCtrl_ZoomSetParam)(MMP_UBYTE ubMode, MMP_UBYTE ubDirection, MMP_USHORT usStep);
    void (*MotorCtrl_ZoomDrive)(void);
    void (*MotorCtrl_ZoomStop)(void);
    void (*MotorCtrl_ZoomEnablePr)(MMP_BOOL OnOFF);
    void (*MotorCtrl_ZoomEnableExcite)(MMP_BOOL OnOFF);
	MMP_USHORT (*MotorCtrl_ZoomMoveStepsEsti)(MMP_ULONG ulDrivingClkHz, MMP_ULONG ulMoveTime);
    MMP_BOOL (*MotorCtrl_ZoomDetectPR)(void);
    MMP_BOOL (*MotorCtrl_ZoomExciteState)(void);
    MMP_UBYTE (*MotorCtrl_ZoomDirection)(void);

    void (*MotorCtrl_FocusPowerOn)(MMP_BOOL OnOFF);
    void (*MotorCtrl_FocusSetParam)(MMP_UBYTE ubMode, MMP_UBYTE ubDirection, MMP_USHORT usStep);
    void (*MotorCtrl_FocusDrive)(void);
    void (*MotorCtrl_FocusStop)(void);
    void (*MotorCtrl_FocusEnablePr)(MMP_BOOL OnOFF);
    void (*MotorCtrl_FocusEnableExcite)(MMP_BOOL OnOFF);
    MMP_BOOL (*MotorCtrl_FocusDetectPR)(void);
    MMP_BOOL (*MotorCtrl_FocusExciteState)(void);
    MMP_UBYTE (*MotorCtrl_FocusDirection)(void);
    void (*MotorCtrl_RegWrite)(MMP_UBYTE ch, MMP_UBYTE reg, MMP_USHORT wdata);
    MMP_UBYTE (*MotorCtrl_RegRead)(MMP_UBYTE ch, MMP_UBYTE reg, MMP_UBYTE ch_rd, MMP_UBYTE BitSize);

    void (*MotorCtl_IrisDirection)(MMP_UBYTE ubDirection);
    
    void (*MotorCtl_TriggerMechanicalShutter)(MMP_BOOL bTrigger);
    void (*MotorCtl_MechanicalShutterDirection)(MMP_BOOL bForwardReverse);
} MotorCtrl_FUNCTIION;

#endif // _MOTORCTRLFUNC_H_

