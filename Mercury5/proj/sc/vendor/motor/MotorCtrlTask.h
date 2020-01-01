//==============================================================================
//
//  File        : MotorCtrlTask.h
//  Description : INCLUDE File for the Motor Driver Function
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================


#ifndef _MOTORCTRLTASK_H_
#define _MOTORCTRLTASK_H_

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================
#define MOTOR_FLAG_INITIALIZE       0x00000001
#define MOTOR_FLAG_ZOOM_FORWARD     0x00000002
#define MOTOR_FLAG_ZOOM_BACKWARD    0x00000004
#define MOTOR_FLAG_ZOOM_STOP        0x00000008
#define MOTOR_FLAG_ZOOM_HOME        0x00000010
#define MOTOR_FLAG_ZOOM_SELFTEST    0x00000020
#define MOTOR_FLAG_ZOOM_CALIB       0x00000040

//#define MOTOR_FLAG_FOCUS_INIT      0x00000100
#define MOTOR_FLAG_FOCUS_SET_POS    0x00000100
#define MOTOR_FLAG_FOCUS_STOP       0x00000200
#define MOTOR_FLAG_FOCUS_HOME       0x00000400
#define MOTOR_FLAG_FOCUS_SELFTEST   0x00000800
#define MOTOR_FLAG_FOCUS_CALIB      0x00001000
#define MOTOR_FLAG_ZOOM_BACK_HOME   0x00002000
#define MOTOR_FLAG_FOCUS_BACK_HOME  0x00004000

#define MOTOR_FLAG_FOCUS_CHECK_CMD  0x00008000

#define MOTOR_FLAG_FOCUS_FOREVER    0xffffffff

	#define DRIVE_MOTOR_CLK_HZ 6000000

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================
typedef enum _MOTOR_STATE{
    MT_STATE_IDLE,
    MT_STATE_BUSY
} MtCtrl_STATE;

typedef enum _MtCtrl_DRV_DIR {
    MT_DRV_FORWARD = 0 ,
    MT_DRV_BACKWARD
} MtCtrl_DRV_DIR;

typedef enum _MtCtrl_SPEED_MODE {
    MT_SPEED_CONST = 0 ,
    MT_SPEED_ACC_LOW   ,
    MT_SPEED_ACC_MID   ,
    MT_SPEED_ACC_HIGH  
} MtCtrl_SPEED_MODE;

typedef enum _MOTOR_REQUEST{
    MT_REQ_READY,
    MT_REQ_NOT_READY
} MtCtrl_REQUEST;


//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
void FuncMotorCtrl_Initialize(void);
void FuncMotorCtrl_ZoomStart( MMP_UBYTE ubDirection );
void FuncMotorCtrl_ZoomSetPosition( MMP_USHORT ubIndex );
void FuncMotorCtrl_ZoomSelftest(void);
void FuncMotorCtrl_ZoomStop(void);
void FuncMotorCtrl_ZoomHome(void);

void FuncMotorCtrl_FocusHome(void);
MMP_BOOL FuncMotorCtrl_FocusSetPosition(MMP_SHORT ssPos);
void FuncMotorCtrl_FocusStop(void);
void FuncMotorCtrl_FocusSelftest(void);
MMP_BOOL FuncMotorCtrl_FocusExciteState(void);
MMP_BOOL FuncMotorCtrl_ZoomExciteState(void);

MMP_BOOL   MotorCtrl_SearchFocusMechaHome( MMP_SHORT *ssIndex );
MMP_BOOL   MotorCtrl_SearchZoomMechaHome( MMP_SHORT *ssIndex );
MMP_UBYTE  FuncMotorCtrl_ZoomReady(void);
MMP_UBYTE  FuncMotorCtrl_FocusReady(void);
MMP_UBYTE  FuncMotorCtrl_FocusReqStatus(void);
MMP_BOOL   FuncMotorCtrl_ZoomDone( void );
MMP_SHORT FuncMotorCtrl_ZoomGetPosition( void );
MMP_USHORT FuncMotorCtrl_ZoomCurrentIndex(void);
MMP_SHORT FuncMotorCtrl_FocusGetPosition( void );
MMP_BOOL FuncMotorCtrl_ZoomHomeFound(void);
MMP_BOOL FuncMotorCtrl_FocusHomeFound(void);
MMP_BOOL FuncMotorCtrl_ZoomExcitationCtrl(MMP_BOOL bEnable);
MMP_BOOL FuncMotorCtrl_FocusExcitationCtrl(MMP_BOOL bEnable);
MMP_USHORT FuncMotorCtrl_ZoomAdvIndex(MMP_ULONG ulMoveTime);
void MotorCtrl_RegWrite(MMP_UBYTE ch, MMP_UBYTE reg, MMP_USHORT wdata);
MMP_UBYTE MotorCtrl_RegRead(MMP_UBYTE ch, MMP_UBYTE reg, MMP_UBYTE ch_rd, MMP_UBYTE BitSize);
MMP_BOOL FuncMotorCtrl_ZoomMove( MMP_BOOL bForward, MMP_USHORT usSteps );
MMP_BOOL FuncMotorCtrl_FocusMove( MMP_BOOL bForward, MMP_USHORT usSteps );
void FuncMotorCtl_IrisDirection(MMP_UBYTE ubDirection);
void FuncMotorCtl_TriggerMechanicalShutter(MMP_BOOL bTrigger);
void FuncMotorCtl_MechanicalShutterDirection(MMP_BOOL bForwardReverse);
MMP_BOOL MotorCtrl_ZoomParking( void );
MMP_BOOL MotorCtrl_FocusParking( void );

#endif // _MOTORCTRLTASK_H_
