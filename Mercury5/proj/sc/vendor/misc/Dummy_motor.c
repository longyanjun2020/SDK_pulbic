#include "config_fw.h"
#include "Customer_config.h"

#if BIND_MOTOR_DUMMY

#include "mmp_lib.h"
#include "includes_fw.h"
#include "MotorCtrlFunc.h"

void DummyMotor_Initialize(void)
{

}


MMP_BOOL DummyMotor_ZoomDetectPR()
{
    return MMP_TRUE;
}

void DummyMotor_ZoomEnablePR(MMP_BOOL OnOff)
{

}

void DummyMotor_ZoomEnableExcite(MMP_BOOL OnOff)
{

}

MMP_BOOL DummyMotor_FocusDetectPR(void)
{
    return MMP_TRUE;
}

void DummyMotor_FocusEnablePR(MMP_BOOL OnOff)
{

}

void DummyMotor_FocusEnableExcite(MMP_BOOL OnOff)
{

}

void DummyMotor_ZoomPowerOn(MMP_BOOL OnOFF)
{

}

MMP_USHORT DummyMotor_ZoomMoveStepsEsti(MMP_ULONG ulDrivingClkHz, MMP_ULONG ulMoveTime)  
{
	return 0;
}

void DummyMotor_ZoomSetParam(MMP_UBYTE ubMode, MMP_UBYTE ubDirection, MMP_USHORT ulStep )
{

}

void DummyMotor_ZoomDrive()
{

}

void DummyMotor_ZoomStop()
{

}

MMP_BOOL DummyMotor_ZoomExciteState(void)
{
    return MMP_FALSE;
}

MMP_UBYTE DummyMotor_ZoomDirection(void)
{
    return 0;
}

void DummyMotor_FocusPowerOn(MMP_BOOL OnOFF)
{

}

void DummyMotor_FocusSetParam(MMP_UBYTE ubMode, MMP_UBYTE ubDirection, MMP_USHORT ulStep )
{

}

void DummyMotor_FocusDrive()
{

}

void DummyMotor_FocusStop()
{

}

MMP_BOOL DummyMotor_FocusExciteState()
{
    return MMP_FALSE;
}

MMP_UBYTE DummyMotor_FocusDirection(void)
{
    return 0;
}

void DummyMotor_RegWrite(MMP_UBYTE ch, MMP_UBYTE reg, MMP_USHORT wdata)
{

}

MMP_UBYTE DummyMotor_RegRead(MMP_UBYTE ch, MMP_UBYTE reg, MMP_UBYTE ch_rd, MMP_UBYTE BitSize)
{
    return MMP_TRUE;
}

void DummyMotor_IrisDirection(MMP_UBYTE ubDirection)
{
}

void DummyMotor_TriggerMechanicalShutter(MMP_BOOL bTrigger)
{

}

void DummyMotor_MechanicalShutterDirection(MMP_BOOL bForwardReverse)
{

}

MotorCtrl_FUNCTIION Motor_DummyMotor_Func =  
{                                            
    DummyMotor_Initialize,                   
    DummyMotor_ZoomPowerOn,                  
    DummyMotor_ZoomSetParam,                 
    DummyMotor_ZoomDrive,                    
    DummyMotor_ZoomStop,                     
    DummyMotor_ZoomEnablePR,                 
    DummyMotor_ZoomEnableExcite,
    DummyMotor_ZoomMoveStepsEsti,             
    DummyMotor_ZoomDetectPR,                 
    DummyMotor_ZoomExciteState,              
    DummyMotor_ZoomDirection,                
    DummyMotor_FocusPowerOn,                 
    DummyMotor_FocusSetParam,                
    DummyMotor_FocusDrive,                   
    DummyMotor_FocusStop,                    
    DummyMotor_FocusEnablePR,                
    DummyMotor_FocusEnableExcite,            
    DummyMotor_FocusDetectPR,                
    DummyMotor_FocusExciteState,             
    DummyMotor_FocusDirection,  
    DummyMotor_RegWrite,
    DummyMotor_RegRead,
    DummyMotor_IrisDirection,
    DummyMotor_TriggerMechanicalShutter,
    DummyMotor_MechanicalShutterDirection 
};


MotorCtrl_FUNCTIION  *MotorControlModule = &Motor_DummyMotor_Func;

#endif
