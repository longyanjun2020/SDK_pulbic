//==============================================================================
//
//  File        : MotorCtrlTask.c
//  Description : Motor Control function
//  Author      : Wayne Chang
//  Revision    : 1.0
//
//==============================================================================

#include "includes_fw.h"

#if defined(ALL_FW)
#include "os_wrap.h"
#include "MotorCtrlTask.h"
#include "MotorCtrlFunc.h"
#include "mmp_lib.h"
#include "mmpf_timingmark.h"
#include "isp_if.h"
#include "mmpf_hw_counter.h"

#define TIMING_MARK_ENABLE      1

#define MOTOR_TYPE_NO_QUE        	(1)
#define MOTOR_TYPE_QUE_1CMD      	(2)
#define MOTOR_TYPE_QUE_OVERWRITE 	(3)


#define MOTOR_QUE_TYPE MOTOR_TYPE_QUE_1CMD 

#if TIMING_MARK_ENABLE
#define TIM_MARK( ... ) MMPF_TimingMarkF(  __VA_ARGS__ )
#else
#define TIM_MARK( ... )
#endif


#if (AIT_LENS_TYPE==AIT_LENS_TYPE_ZM751)
	#define ZOOM_MECHA_HOME_INDEX    (5)
	#define FOCUS_MECHA_HOME_INDEX   (130)
	#define FOCUS_MECHA_MIN_INDEX    (FOCUS_MECHA_HOME_INDEX-125)
	#define FOCUS_MECHA_MAX_INDEX    (FOCUS_MECHA_HOME_INDEX+(750-70))
    #define FOCUS_MECHA_SEARCH_HOME_FWD_RANGE   500
	MMP_SHORT ZoomIndex_LUT[126] =
	{
		 54, 62, 70, 78, 86, 94, 102, 110, 118, 126, 
		134, 142, 150, 158, 166, 174, 182, 190, 198, 206, 
		214, 222, 230, 238, 246, 254, 262, 270, 278, 286, 
		294, 302, 310, 318, 326, 334, 342, 350, 358, 366, 
		374, 382, 390, 398, 406, 414, 422, 430, 438, 446, 
		454, 462, 470, 478, 486, 494, 502, 510, 518, 526, 
		534, 542, 550, 558, 566, 574, 582, 590, 598, 606, 
		614, 622, 630, 638, 646, 654, 662, 670, 678, 686, 
		694, 702, 710, 718, 726, 734, 742, 750, 758, 766, 
		774, 782, 790, 798, 806, 814, 822, 830, 838, 846, 
		854, 862, 870, 878, 886, 894, 902, 910, 918, 926, 
		934, 942, 950, 958, 966, 974, 982, 990, 998, 1006, 
		1014, 1022, 1030, 1038, 1046, 1054
	};
#elif (AIT_LENS_TYPE==AIT_LENS_TYPE_ZM726)
	#define ZOOM_MECHA_HOME_INDEX    21
	#define FOCUS_MECHA_HOME_INDEX   160
	#define FOCUS_MECHA_MIN_INDEX    (FOCUS_MECHA_HOME_INDEX-155)
	#define FOCUS_MECHA_MAX_INDEX    (FOCUS_MECHA_HOME_INDEX+(593))
    #define FOCUS_MECHA_SEARCH_HOME_FWD_RANGE   200
	MMP_SHORT ZoomIndex_LUT[126] =
	{
	     20,   31,   38,   45,   53,   60,   67,   74,   81,   89,
	     96,  103,  110,  117,  125,  132,  139,  146,  154,  161,
	    168,  175,  182,  189,  197,  204,  211,  218,  225,  233,
	    240,  247,  254,  261,  269,  276,  283,  290,  297,  305,
	    312,  319,  326,  334,  341,  348,  355,  363,  370,  377,
	    384,  391,  398,  405,  413,  420,  427,  434,  442,  449,
	    456,  463,  470,  478,  485,  492,  499,  507,  514,  521,
	    528,  535,  543,  550,  557,  564,  571,  579,  586,  593,
	    600,  607,  615,  622,  629,  636,  643,  651,  658,  665,
	    672,  679,  687,  694,  701,  708,  715,  723,  730,  737,
	    744,  751,  759,  766,  773,  780,  788,  795,  802,  809,
	    816,  824,  831,  838,  845,  852,  860,  867,  874,  881,
	    888,  896,  903,  910,  917,  924
	};

	
#elif (AIT_LENS_TYPE==AIT_LENS_TYPE_DUMMY)	
	#define ZOOM_MECHA_HOME_INDEX    21
	#define FOCUS_MECHA_HOME_INDEX   160
	#define FOCUS_MECHA_MIN_INDEX    (FOCUS_MECHA_HOME_INDEX-155)
	#define FOCUS_MECHA_MAX_INDEX    (FOCUS_MECHA_HOME_INDEX+(593))
    #define FOCUS_MECHA_SEARCH_HOME_FWD_RANGE   200
	MMP_SHORT ZoomIndex_LUT[126] =
	{
	     20,   31,   38,   45,   53,   60,   67,   74,   81,   89,
	     96,  103,  110,  117,  125,  132,  139,  146,  154,  161,
	    168,  175,  182,  189,  197,  204,  211,  218,  225,  233,
	    240,  247,  254,  261,  269,  276,  283,  290,  297,  305,
	    312,  319,  326,  334,  341,  348,  355,  363,  370,  377,
	    384,  391,  398,  405,  413,  420,  427,  434,  442,  449,
	    456,  463,  470,  478,  485,  492,  499,  507,  514,  521,
	    528,  535,  543,  550,  557,  564,  571,  579,  586,  593,
	    600,  607,  615,  622,  629,  636,  643,  651,  658,  665,
	    672,  679,  687,  694,  701,  708,  715,  723,  730,  737,
	    744,  751,  759,  766,  773,  780,  788,  795,  802,  809,
	    816,  824,  831,  838,  845,  852,  860,  867,  874,  881,
	    888,  896,  903,  910,  917,  924
	};

#endif
#define ZOOM_WIDE_INDEX           0
#define ZOOM_TELE_INDEX         125

//==============================================================================
//
//                              PROTOTYPE
//
//==============================================================================
extern void MotorCtrlTaskHandler(void *p_arg);
MMP_UBYTE   SearchLUT(MMP_SHORT ulVal, MMP_SHORT *Array, MMP_SHORT ArraySize);
MMP_UBYTE   MotorCtrl_SearchZoomLUT(MMP_SHORT ulVal);

void        FuncMotorCtrl_Configuration(void);
void        ZoomMotor_SetCurrIndex(MMP_SHORT ssIndex);
void        FocusMotor_SetCurrIndex(MMP_SHORT ssIndex);
void        MotorCtrl_DriveZoomWidePos(void);
void        MotorCtrl_DriveSetAFPosition(MMP_UBYTE ubMode, MMP_SHORT ssPos);
void        MotorCtrl_DriveFocssPos(MMP_UBYTE ubMode, MMP_SHORT ssPos, MMP_UBYTE uStep_En );

//==============================================================================
//
//                              STRUECTURE
//
//==============================================================================

typedef struct _MotorCtrl
{
    MMP_SHORT   ssCurrentStep;   // accumulated step counter , PI interrupt
    MMP_SHORT   ssTargetStep;    // 
    MMP_BOOL    bMotorInitDone;  
    MMP_BOOL    bSelfTest;       // 1: Selftest running, 0: Idle.
}MotorCtrl;

typedef struct _MotorReqState
{
    MMP_BOOL    ubIsCommandQue;   // is command que 
    MMP_SHORT  ssTargetStepQue;    // 
    MMP_UBYTE   ubSpeedModeQue;
}MotorReqState;


//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

static MMP_BOOL bZoomHomeFound = MMP_FALSE;
static MMP_BOOL bFocusHomeFound = MMP_FALSE;
MMPF_OS_FLAGID   MotorCtrlEventFlag;
MMPF_OS_SEMID    Sem_MotorCtrl;
MotorCtrl        ZoomMT;
MotorCtrl        FocusMT;
/**
@brief: FuncMotorCtrl_Configuration() will connect MotorFunc with MotorControlModule.

*/
MotorCtrl_FUNCTIION  *MotorFunc;
extern MotorCtrl_FUNCTIION  *MotorControlModule;
MotorReqState    FocusReqState;

extern void printc( char* szFormat, ... );
extern MMP_ULONG MMPF_OsCounterGetMs(void);
extern void OSD_Draw_TestMessage(MMP_ULONG Left, MMP_ULONG Top, char result,char*);

//******************************************************************************
//  Name :           FuncMotorCtrl_Wait_ticks
//
//  @Description : Motor Control delay ticks
//  @param[in]  number of ticks
//******************************************************************************
void
FuncMotorCtrl_Wait_ticks(unsigned int uiTicks)
{
    while(uiTicks--);

}

//******************************************************************************
//  Name :           FuncMotorCtrl_Initialize
//
//  @Description : Initialize Motor Control
//  @param[in]
//******************************************************************************
void 
FuncMotorCtrl_InitializeEx(void)
{
    MMP_SHORT    usZoomHomeIndex;
    MMP_SHORT    usFocusHomeIndex;

#if (AIT_LENS_TYPE==AIT_LENS_TYPE_DUMMY)
    printc("AIT_LENS_TYPE_DUMMY\n");

    return;
#endif //(AIT_LENS_TYPE==AIT_LENS_TYPE_DUMMY)


#if 0
    MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_INITIALIZE, MMPF_OS_FLAG_SET);

    while( !ZoomMT.bMotorInitDone )
    {
        MMPF_OS_Sleep(50);
    }

#else
    FuncMotorCtrl_Configuration();
    MotorFunc->MotorCtrl_Initialize();

//	MMPF_TimingInit(5000);
//	MMPF_TimingStart(TIMING_GROUP_MOTOR);

	if( MMP_TRUE == MotorFunc->MotorCtrl_ZoomExciteState() ||
        MMP_TRUE == MotorFunc->MotorCtrl_FocusExciteState()   )
	{
        printc("[ERR] Motor Board Error!!!\n");
    }
	else
	{
    #if 1
        if( MotorCtrl_SearchZoomMechaHome(&usZoomHomeIndex) )
        {
            ZoomMotor_SetCurrIndex(ZoomIndex_LUT[ZOOM_MECHA_HOME_INDEX]);
            printc("Search Zoom Mecha Home successfully\n"); 
            MotorCtrl_DriveZoomWidePos();
        }
        else
        {
            printc("ERR:Search Zoom Mecha Home fail.\n");
        }
		
        if( MotorCtrl_SearchFocusMechaHome(&usFocusHomeIndex) )
        {
            FocusMotor_SetCurrIndex(FOCUS_MECHA_HOME_INDEX);
            printc("Search Focus Mecha Home successfully\n");
        }
        else
        {
            printc("ERR:Search Focus Mecha Home fail.\n");
        }
    #endif
    }
#endif
}

void 
FuncMotorCtrl_Initialize(void)
{

}


//******************************************************************************
//  Name :           FuncMotorCtrl_Configuration
//
//  @Description : Get motor function ptr.
//  @param[in]
//******************************************************************************
void 
FuncMotorCtrl_Configuration(void)
{
    printc("Motor driver Init ------ ");
#if BIND_MOTOR_R2A30440NP
    printc("R2A30440NP\n");
#elif BIND_MOTOR_R2A30423NP
    printc("R2A30423NP\n");
#else
    printc("DummyMotor\n");
#endif
    MotorFunc = MotorControlModule;
}

//******************************************************************************
//  Name :           FuncMotorCtrl_EnterStandby
//
//  @Description : 
//  @param[in]
//******************************************************************************
void 
FuncMotorCtrl_EnterStandby(unsigned short af_pos)
{

}


//******************************************************************************
//  Name :           FuncMotorCtrl_ZoomHome
//
//  @Description : Set the Zoom Start event.
//  @param[in] ubDirection   Drive Direction.
//******************************************************************************

void 
FuncMotorCtrl_ZoomStart( MMP_UBYTE ubDirection )
{
    if( MotorFunc->MotorCtrl_ZoomExciteState() )
        return;

    if( MT_DRV_FORWARD == ubDirection )
    {
        ZoomMT.ssTargetStep = ZoomIndex_LUT[ZOOM_TELE_INDEX];
        MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_ZOOM_FORWARD, MMPF_OS_FLAG_SET);
    }
    else
    {
        ZoomMT.ssTargetStep = ZoomIndex_LUT[ZOOM_WIDE_INDEX];
        MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_ZOOM_BACKWARD, MMPF_OS_FLAG_SET);
    }
}

//******************************************************************************
//  Name :           FuncMotorCtrl_ZoomSetPosition
//
//  @Description : Set the Zoom Target Position.
//  @param[in] ubIndex   Drive Index in Zoom LUT.
//******************************************************************************
void 
FuncMotorCtrl_ZoomSetPosition( MMP_USHORT ubIndex )
{
    if( MotorFunc->MotorCtrl_ZoomExciteState() )
    {
        return;
	}


    if( ubIndex >= sizeof(ZoomIndex_LUT)/sizeof(MMP_SHORT) )
    {
        ubIndex = sizeof(ZoomIndex_LUT)/sizeof(MMP_SHORT) - 1;
        printc("Max Index %d is applied.\nIndex Range: 0 ~ 125\n",ubIndex);
    }

    ZoomMT.ssTargetStep = ZoomIndex_LUT[ubIndex];

    if( ZoomMT.ssCurrentStep > ZoomMT.ssTargetStep )
    {
        MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_ZOOM_BACKWARD, MMPF_OS_FLAG_SET);
    }
    else if( ZoomMT.ssCurrentStep < ZoomMT.ssTargetStep )
    {
        MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_ZOOM_FORWARD, MMPF_OS_FLAG_SET);
    }
    else // ZoomMT.ssCurrentStep == ZoomMT.ssTargetStep  
    { // Request ignored.
    } 
}

//******************************************************************************
//  Name :           FuncMotorCtrl_ZoomGetPosition
//
//  @Description : Get the Zoom Position.
//  @param[in] 
//******************************************************************************

MMP_SHORT 
FuncMotorCtrl_ZoomGetPosition( void )
{
    return ZoomMT.ssCurrentStep;
}

//******************************************************************************
//  Name :           FuncMotorCtrl_ZoomHome
//
//  @Description : Set the Zoom Return Home event.
//  @param[in]
//******************************************************************************
void 
FuncMotorCtrl_ZoomHome(void)
{
    if( MotorFunc->MotorCtrl_ZoomExciteState() )
        return;

    MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_ZOOM_HOME, MMPF_OS_FLAG_SET);
}


//******************************************************************************
//  Name :           FuncMotorCtrl_ZoomSelftest
//
//  @Description : Set the Zoom test event.
//  @param[in]
//******************************************************************************
void 
FuncMotorCtrl_ZoomSelftest(void)
{
    if( MotorFunc->MotorCtrl_ZoomExciteState() )
        return;
    
    ZoomMT.bSelfTest = MMP_TRUE;
    MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_ZOOM_SELFTEST, MMPF_OS_FLAG_SET);    
}

void 
FuncMotorCtrl_ZoomCalibration(void)
{
    #if 0
	UartExecuteCommandEx("zotest");
	AHC_OS_Sleep(5000);
	UartExecuteCommandEx("zostop");
	AHC_OS_Sleep(500);
	UartExecuteCommandEx("fotest");
	AHC_OS_Sleep(5000);
	UartExecuteCommandEx("fostop");
	AHC_OS_Sleep(500);
	#else
    MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_ZOOM_CALIB, MMPF_OS_FLAG_SET); 
	#endif
}
//******************************************************************************
//  Name :           FuncMotorCtrl_ZoomCurrentIndex
//
//  @Description : return current motor zoom index.
//  @param[in]
//******************************************************************************
MMP_USHORT 
FuncMotorCtrl_ZoomCurrentIndex(void)
{
    return MotorCtrl_SearchZoomLUT(ZoomMT.ssCurrentStep);
}

//******************************************************************************
//  Name :           FuncMotorCtrl_ZoomAdvIndex
//
//  @Description : return usAdvVDNum VD later motor zoom index.
//  @param[in]: ulMoveTime is moving time in ms (US16.16 format)
//******************************************************************************
MMP_USHORT 
FuncMotorCtrl_ZoomAdvIndex(MMP_ULONG ulMoveTime)
{
	MMP_SHORT ssAdvStep;
	MMP_SHORT ssZoomMoveStepsEsti=0;

	ssAdvStep = ZoomMT.ssCurrentStep;
	#if 1
	if( MotorFunc->MotorCtrl_ZoomExciteState() )
	{
		ssZoomMoveStepsEsti = MotorFunc->MotorCtrl_ZoomMoveStepsEsti(DRIVE_MOTOR_CLK_HZ,ulMoveTime);
		if( MT_DRV_BACKWARD == MotorFunc->MotorCtrl_ZoomDirection() )
			ssAdvStep -= ssZoomMoveStepsEsti;
		else
			ssAdvStep += ssZoomMoveStepsEsti;
	}
	#endif
	// printc("ZoomMT.ssCurrentStep=%d, %d usZoomMoveStepsEsti = %d \n",ZoomMT.ssCurrentStep,usAdvStep,usZoomMoveStepsEsti);
    return MotorCtrl_SearchZoomLUT(ssAdvStep);
}

//******************************************************************************
//  Name :           FuncMotorCtrl_ZoomStop
//
//  @Description : Set the Zoom Stop event.
//  @param[in]
//******************************************************************************
void 
FuncMotorCtrl_ZoomStop(void)
{
    if(MMP_TRUE == ZoomMT.bSelfTest)  
        ZoomMT.bSelfTest = MMP_FALSE;
    else
        MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_ZOOM_STOP, MMPF_OS_FLAG_SET);    
}

//******************************************************************************
//  Name :           FuncMotorCtrl_ZoomExcitationCtrl
//
//  @Description : Motor Excitation Control
//  @param[in] 
//  @retval        MMP_TRUE:  
//******************************************************************************
MMP_BOOL 
FuncMotorCtrl_ZoomExcitationCtrl(MMP_BOOL bEnable)
{
    MotorFunc->MotorCtrl_ZoomEnableExcite(bEnable);
    return MMP_TRUE;
}

//******************************************************************************
//  Name :           FuncMotorCtrl_FocusCheckPosCmd
//
//  @Description : Set Focus position.
//  @param[in]   ssPos     focus position.
//******************************************************************************
MMP_BOOL 
FuncMotorCtrl_FocusCheckUnacceptedPos(MMP_SHORT* pssPos)
{	
	if(*pssPos<(MMP_SHORT)FOCUS_MECHA_MIN_INDEX)
	{
		*pssPos=(MMP_SHORT)FOCUS_MECHA_MIN_INDEX;
		return MMP_TRUE;
	}
	else if(*pssPos>(MMP_SHORT)FOCUS_MECHA_MAX_INDEX)
	{
		*pssPos=(MMP_SHORT)FOCUS_MECHA_MAX_INDEX;
		return MMP_TRUE;
	}
	else
		return MMP_FALSE;
}


//******************************************************************************
//  Name :           FuncMotorCtrl_FocusSetPositionEx
//
//  @Description : Set Focus position.
//  @param[in]   ssPos     focus position.
//******************************************************************************
MMP_BOOL 
FuncMotorCtrl_FocusSetPositionEx(MMP_UBYTE usSpeedMode, MMP_SHORT ssPos_ori)
{
	MMP_SHORT ssPos = ssPos_ori;
	MMP_BOOL ubCheckPos = FuncMotorCtrl_FocusCheckUnacceptedPos(&ssPos);

    if( MotorFunc->MotorCtrl_FocusExciteState() )
        return ubCheckPos;

    FocusMT.ssTargetStep= ssPos;
    MotorCtrl_DriveSetAFPosition(usSpeedMode, FocusMT.ssTargetStep);

	return ubCheckPos;
}


//******************************************************************************
//  Name :           FuncMotorCtrl_FocusSetPositionExQue
//
//  @Description : Set Focus position.
//  @param[in]   ssPos     focus position.
//******************************************************************************
MMP_BOOL 
FuncMotorCtrl_FocusSetPositionExQue(MMP_UBYTE usSpeedMode, MMP_SHORT ssPos_ori)
{
	MMP_SHORT ssPos = ssPos_ori;
	MMP_BOOL ubCheckPos = FuncMotorCtrl_FocusCheckUnacceptedPos(&ssPos);
	
	if(FocusReqState.ubIsCommandQue == 1)
	{
		FocusReqState.ubSpeedModeQue = usSpeedMode;
		FocusReqState.ssTargetStepQue = ssPos;


		if((FocusMT.ssTargetStep == FocusMT.ssCurrentStep) |( !MotorFunc->MotorCtrl_FocusExciteState() ))
			MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_FOCUS_CHECK_CMD, MMPF_OS_FLAG_SET);

		// printc("Replace Que focus request: TargetStep:%d, SpeedMode:%d \n",FocusReqState.ssTargetStepQue,FocusReqState.ubSpeedModeQue);

		// return;
	}
	else
	{
	    if( MotorFunc->MotorCtrl_FocusExciteState() ) // let command into que
	    {
	    	FocusReqState.ubIsCommandQue = 1;
			FocusReqState.ubSpeedModeQue = usSpeedMode;
			FocusReqState.ssTargetStepQue = ssPos;

			if(FocusMT.ssTargetStep == FocusMT.ssCurrentStep)
				MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_FOCUS_CHECK_CMD, MMPF_OS_FLAG_SET);

			// printc("Que focus request: TargetStep:%d, SpeedMode:%d \n",FocusReqState.ssTargetStepQue,FocusReqState.ubSpeedModeQue);
		}
		else
		{
		    FocusMT.ssTargetStep= ssPos;
		    MotorCtrl_DriveSetAFPosition(usSpeedMode, FocusMT.ssTargetStep);
		}
	}

	return ubCheckPos;
}

//******************************************************************************
//  Name :           FuncMotorCtrl_FocusSetPosition
//
//  @Description : Set Focus position.
//  @param[in]   ssPos     focus position.
//******************************************************************************
MMP_BOOL 
FuncMotorCtrl_FocusSetPosition(MMP_SHORT ssPos_ori)
{
	MMP_SHORT ssPos = ssPos_ori;
	MMP_BOOL ubCheckPos = FuncMotorCtrl_FocusCheckUnacceptedPos(&ssPos);

    if( MotorFunc->MotorCtrl_FocusExciteState() )
        return ubCheckPos;

    FocusMT.ssTargetStep= ssPos;
    MotorCtrl_DriveSetAFPosition(MT_SPEED_ACC_MID, FocusMT.ssTargetStep);
	return ubCheckPos;
}

//******************************************************************************
//  Name :           FuncMotorCtrl_FocusGetState
//
//  @Description : Get the Zoom Position.
//  @param[in] 
//******************************************************************************

MMP_UBYTE 
FuncMotorCtrl_FocusCheckAFPos(MMP_SHORT ssPos)
{
    return 1;
}


//******************************************************************************
//  Name :           FuncMotorCtrl_FocusGetPosition
//
//  @Description : Get the Zoom Position.
//  @param[in] 
//******************************************************************************

MMP_SHORT 
FuncMotorCtrl_FocusGetPosition( void )
{
    return FocusMT.ssCurrentStep;
}

//******************************************************************************
//  Name :           FuncMotorCtrl_FocusSelftest
//
//  @Description : Set the Focus test event.
//  @param[in]
//******************************************************************************
void 
FuncMotorCtrl_FocusSelftest(void)
{
    if( MotorFunc->MotorCtrl_FocusExciteState() )
        return;
    
    FocusMT.bSelfTest = MMP_TRUE;
    MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_FOCUS_SELFTEST, MMPF_OS_FLAG_SET);    

}

//******************************************************************************
//  Name :           FuncMotorCtrl_FocusDone
//
//  @Description : Set the Zoom Start event.
//  @param[in] ubDirection   Drive Direction.
//******************************************************************************

MMP_BOOL 
FuncMotorCtrl_FocusDone( void )
{
    if( MMP_FALSE == MotorFunc->MotorCtrl_ZoomExciteState() )
        return MMP_TRUE;
    else
        return MMP_FALSE;
}
//******************************************************************************
//  Name :           FuncMotorCtrl_FocusHome
//
//  @Description : Set the Focus Return Home event.
//  @param[in]
//******************************************************************************
void 
FuncMotorCtrl_FocusHome(void)
{
    if( MotorFunc->MotorCtrl_FocusExciteState() )
        return;

    MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_FOCUS_HOME, MMPF_OS_FLAG_SET);

}


//******************************************************************************
//  Name :           FuncMotorCtrl_FocusStop
//
//  @Description : Set the Focus Stop event.
//  @param[in]
//******************************************************************************
void 
FuncMotorCtrl_FocusStop(void)
{
    if(MMP_TRUE == FocusMT.bSelfTest)  
        FocusMT.bSelfTest = MMP_FALSE;
    else
        MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_FOCUS_STOP, MMPF_OS_FLAG_SET);    
}


//******************************************************************************
//  Name :           FuncMotorCtrl_ZoomReady
//
//  @Description : Check Zoom Motor status
//  @param[in] 
//  @retval        MMP_TRUE:  Motor Ready.
//******************************************************************************
MMP_UBYTE 
FuncMotorCtrl_ZoomReady(void)
{
    if( MotorFunc->MotorCtrl_ZoomExciteState() )
        return MT_STATE_BUSY;
    else
        return MT_STATE_IDLE;
}


//******************************************************************************
//  Name :           MotorCtrl_Param_Reset
//
//  @Description : Reset MotorCtrl Parameter.
//  @param[in] 
//  @retval        MMP_TRUE:  Motor Ready.
//******************************************************************************
MMP_UBYTE 
FuncMotorCtrl_FocusReady(void)
{
    if( MotorFunc->MotorCtrl_FocusExciteState() )
        return MT_STATE_BUSY;
    else
        return MT_STATE_IDLE;
}

//******************************************************************************
//  Name :           FuncMotorCtrl_FocusReqStatus
//
//  @Description : 
//  @param[in] 
//  @retval       
//******************************************************************************
MMP_UBYTE 
FuncMotorCtrl_FocusReqStatus(void)
{
	MtCtrl_REQUEST request_stat;
#if (MOTOR_QUE_TYPE==MOTOR_TYPE_NO_QUE)
	if( MotorFunc->MotorCtrl_FocusExciteState() )
        request_stat = MT_REQ_NOT_READY;
    else
        request_stat = MT_REQ_READY;
#elif (MOTOR_QUE_TYPE==MOTOR_TYPE_QUE_OVERWRITE)
	request_stat = MT_REQ_READY;
#elif (MOTOR_QUE_TYPE==MOTOR_TYPE_QUE_1CMD)
    if(( FocusReqState.ubIsCommandQue == 1 ) && MotorFunc->MotorCtrl_FocusExciteState())
        request_stat = MT_REQ_NOT_READY;
    else
        request_stat = MT_REQ_READY;
#else
	request_stat = MT_REQ_NOT_READY;
#endif

	return request_stat;
}

//******************************************************************************
//  Name :           FuncMotorCtrl_ZoomHomeFound
//
//  @Description : Check zoom motor home position found
//  @param[in] 
//  @retval        MMP_TRUE:  Motor home found.
//******************************************************************************
MMP_BOOL 
FuncMotorCtrl_ZoomHomeFound(void)
{
	return bZoomHomeFound;
}

//******************************************************************************
//  Name :           FuncMotorCtrl_FocusHomeFound
//
//  @Description : Check focus motor home position found
//  @param[in] 
//  @retval        MMP_TRUE:  Motor home found.
//******************************************************************************
MMP_BOOL 
FuncMotorCtrl_FocusHomeFound(void)
{
	return bFocusHomeFound;
}


//******************************************************************************
//  Name :           FuncMotorCtrl_FocusExcitationCtrl
//
//  @Description : Motor Excitation Control
//  @param[in] 
//  @retval        MMP_TRUE:  
//******************************************************************************
MMP_BOOL 
FuncMotorCtrl_FocusExcitationCtrl(MMP_BOOL bEnable)
{
    MotorFunc->MotorCtrl_FocusEnableExcite(bEnable);
    return MMP_TRUE;
}

//******************************************************************************
//  Name :           FuncMotorCtrl_FocusExciteState
//
//  @Description : Return Focus Motor Excite state
//  @param[in] 
//  @retval        MMP_TRUE/MMP_FALSE:  
//******************************************************************************
MMP_BOOL 
FuncMotorCtrl_FocusExciteState(void)
{
    return MotorFunc->MotorCtrl_FocusExciteState();
}

//******************************************************************************
//  Name :           FuncMotorCtrl_ZoomExciteState
//
//  @Description : Return Zoom Motor Excite state
//  @param[in] 
//  @retval        MMP_TRUE/MMP_FALSE:  
//******************************************************************************
MMP_BOOL 
FuncMotorCtrl_ZoomExciteState(void)
{
    return MotorFunc->MotorCtrl_ZoomExciteState();
}

//******************************************************************************
//  Name :           ZoomMotor_PI_ISR
//
//  @Description : Record the stepping motor position.
//  @param[in] 
//******************************************************************************
void 
ZoomMotor_Step_ISR(void)
{
    if( MT_DRV_FORWARD == MotorFunc->MotorCtrl_ZoomDirection() )
        ZoomMT.ssCurrentStep++;
    else
        ZoomMT.ssCurrentStep--;


    TIM_MARK( TIMING_GROUP_MOTOR, "Zoom_Step_ISR, CurrStep: %d, Target: %d PR(%d)\n",ZoomMT.ssCurrentStep, ZoomMT.ssTargetStep, MotorFunc->MotorCtrl_ZoomDetectPR());

}


//******************************************************************************
//  Name :           ZoomMotor_PR_ISR
//
//  @Description : 
//  @param[in] 
//******************************************************************************
void 
ZoomMotor_PR_ISR(void)
{
    if( MT_DRV_FORWARD == MotorFunc->MotorCtrl_ZoomDirection() )
    {
        TIM_MARK( TIMING_GROUP_MOTOR,"ZoomStep PR INT %d\n", ZoomMT.ssCurrentStep);
    }
    else
    {
        TIM_MARK( TIMING_GROUP_MOTOR,"ZoomStep PR INT %d\n", ZoomMT.ssCurrentStep);
    }

}

//******************************************************************************
//  Name :           ZoomMotor_SetCurrIndex
//
//  @Description : 
//  @param[in] 
//******************************************************************************
void 
ZoomMotor_SetCurrIndex(MMP_SHORT ssIndex)
{
    ZoomMT.ssCurrentStep = ssIndex;
}

//******************************************************************************
//  Name :           FocusMotor_PI_ISR
//
//  @Description : Record the DC motor position.
//  @param[in] 
//******************************************************************************
void 
FocusMotor_Step_ISR(void)
{
    if( MT_DRV_FORWARD == MotorFunc->MotorCtrl_FocusDirection() )
        FocusMT.ssCurrentStep++;
    else
        FocusMT.ssCurrentStep--;

	if((FocusMT.ssTargetStep == FocusMT.ssCurrentStep) && (FocusReqState.ubIsCommandQue==1))
		MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_FOCUS_CHECK_CMD, MMPF_OS_FLAG_SET);

  TIM_MARK( TIMING_GROUP_MOTOR,"Focus_Step_ISR, CurrentStep: %d, Target: %d PR(%d)\n",FocusMT.ssCurrentStep, FocusMT.ssTargetStep, MotorFunc->MotorCtrl_FocusDetectPR());

}

//******************************************************************************
//  Name :           FocusMotor_PR_ISR
//
//  @Description : 
//  @param[in] 
//******************************************************************************
void 
FocusMotor_PR_ISR(void)
{
    if( MT_DRV_FORWARD == MotorFunc->MotorCtrl_FocusDirection() )
    {
        TIM_MARK( TIMING_GROUP_MOTOR,"Focus Forward, PR INT %d\n", FocusMT.ssCurrentStep);
    }
    else
    {
        TIM_MARK( TIMING_GROUP_MOTOR,"Focus Backward, PR INT %d\n", FocusMT.ssCurrentStep);
    }

}

//******************************************************************************
//  Name :           FocusMotor_SetCurrIndex
//
//  @Description : 
//  @param[in] 
//******************************************************************************
void 
FocusMotor_SetCurrIndex(MMP_SHORT ssIndex)
{
    FocusMT.ssCurrentStep = ssIndex;
}

//******************************************************************************
//  Name :           MotorCtrl_Param_Reset
//
//  @Description : Reset MotorCtrl Parameter.
//  @param[in] 
//******************************************************************************
void 
MotorCtrl_Param_Reset( void )
{
    memset(&ZoomMT, 0, sizeof(ZoomMT));
    memset(&FocusMT, 0, sizeof(FocusMT));
}


//******************************************************************************
//  Name :           MotorCtrl_DriveZoomWidePos
//
//  @Description : Move Zoom Motor to Wide Position.
//  @param[in] 
//  @retval      
//******************************************************************************
void 
MotorCtrl_DriveZoomWidePos(void)
{
    MMP_SHORT ssWideIdx = ZoomIndex_LUT[ZOOM_WIDE_INDEX];
    MMP_SHORT ssStep = 0;
    MMP_UBYTE  ubDir = 0;

//  MotorFunc->MotorCtrl_ZoomEnablePr(MMP_TRUE);
//  MMPF_OS_Sleep(100);
    MotorFunc->MotorCtrl_ZoomEnableExcite(MMP_TRUE);
    MMPF_OS_Sleep(200);

    if( ZoomMT.ssCurrentStep > ssWideIdx )
    {
        ssStep = ZoomMT.ssCurrentStep - ssWideIdx;
        ubDir  = MT_DRV_BACKWARD;
    }
    else
    {
        ssStep = ssWideIdx - ZoomMT.ssCurrentStep;
        ubDir  = MT_DRV_FORWARD;
    }

    TIM_MARK( TIMING_GROUP_MOTOR,"Move to Wide Pos %d\n", ssWideIdx);

    MotorFunc->MotorCtrl_ZoomSetParam( MT_SPEED_ACC_LOW, ubDir, ssStep );

    MotorFunc->MotorCtrl_ZoomDrive();
 
    FuncMotorCtrl_Wait_ticks(10);

    while( MotorFunc->MotorCtrl_ZoomExciteState() ) MMPF_OS_Sleep(5);

    MotorFunc->MotorCtrl_ZoomEnableExcite(MMP_FALSE);
//    MMPF_OS_Sleep(300);

}

//******************************************************************************
//  Name :           MotorCtrl_SearchZoomMechaHome
//
//  @Description : Move Zoom Motor to Home Position.
//  @param[in] 
//  @retval      
//******************************************************************************
MMP_BOOL
MotorCtrl_SearchZoomMechaHome( MMP_SHORT *ssIndex )
{
    MMP_BOOL   bFound = MMP_FALSE;
    MMP_SHORT ssStep = 0;
    MMP_UBYTE  ubOffset = 20;
    MMP_UBYTE  ubDir    = MT_DRV_FORWARD;
    MMP_SHORT HomeIndex = ZoomIndex_LUT[ZOOM_MECHA_HOME_INDEX];
    // MMP_ULONG  ulTimeStart = MMPF_OsCounterGetMs();

    TIM_MARK( TIMING_GROUP_MOTOR,"MotorCtrl_SearchZoomMechaHome start\n");

    bZoomHomeFound = MMP_FALSE;
    MotorFunc->MotorCtrl_ZoomEnableExcite(MMP_TRUE);
    MotorFunc->MotorCtrl_ZoomEnablePr(MMP_TRUE);
    MMPF_OS_Sleep(25);

    ubOffset = 20;
    if( ZoomMT.ssCurrentStep < (HomeIndex + ubOffset) &&
        ZoomMT.ssCurrentStep > (HomeIndex - ubOffset) )
    {
        TIM_MARK( TIMING_GROUP_MOTOR,"Zoom Motor In Home Range 155~195\n");
        TIM_MARK( TIMING_GROUP_MOTOR,"Move Forward step 50. \n");

        ssStep = 50;
		ubDir  = MT_DRV_FORWARD;
        MotorFunc->MotorCtrl_ZoomSetParam(MT_SPEED_CONST, ubDir, ssStep);
        MotorFunc->MotorCtrl_ZoomDrive();
        FuncMotorCtrl_Wait_ticks(10);
        while(MotorFunc->MotorCtrl_ZoomExciteState())MMPF_OS_Sleep(2);
        FuncMotorCtrl_Wait_ticks(50);
    }

    if( MMP_TRUE == MotorFunc->MotorCtrl_ZoomDetectPR() )
    {
        ubDir = MT_DRV_BACKWARD;
        ssStep = ZoomIndex_LUT[ZOOM_TELE_INDEX] - ZoomIndex_LUT[ZOOM_WIDE_INDEX];
        TIM_MARK( TIMING_GROUP_MOTOR,"PR Detected, Search Backward %d\n",ssStep);
        MotorFunc->MotorCtrl_ZoomSetParam( MT_SPEED_CONST, ubDir, ssStep );
        MotorFunc->MotorCtrl_ZoomDrive();
        FuncMotorCtrl_Wait_ticks(10);
        while(MMP_TRUE == MotorFunc->MotorCtrl_ZoomExciteState())
        {
            if(MMP_FALSE == MotorFunc->MotorCtrl_ZoomDetectPR())
            {
                MotorFunc->MotorCtrl_ZoomStop();
                HomeIndex = ZoomMT.ssCurrentStep;
                bFound = MMP_TRUE;
                break;
            }
        }
    }
    else
    {
      // Forward 200 step.
        ubDir = MT_DRV_FORWARD;
        ssStep = ZoomIndex_LUT[25];
        TIM_MARK( TIMING_GROUP_MOTOR,"PR Not Detected, Move Forward %d\n",ssStep);
        MotorFunc->MotorCtrl_ZoomSetParam(MT_SPEED_CONST, ubDir, ssStep);
        MotorFunc->MotorCtrl_ZoomDrive();
        FuncMotorCtrl_Wait_ticks(10);
        while(MotorFunc->MotorCtrl_ZoomExciteState())MMPF_OS_Sleep(2);

        FuncMotorCtrl_Wait_ticks(50);

      if(MMP_TRUE == MotorFunc->MotorCtrl_ZoomDetectPR())
      {
          // Backward 200 step for searching home.
            ubDir = MT_DRV_BACKWARD;
            TIM_MARK( TIMING_GROUP_MOTOR,"Search Backward %d\n",ssStep);
            MotorFunc->MotorCtrl_ZoomSetParam(MT_SPEED_CONST, ubDir, ssStep);
            MotorFunc->MotorCtrl_ZoomDrive();
            FuncMotorCtrl_Wait_ticks(10);
            while(MMP_TRUE == MotorFunc->MotorCtrl_ZoomExciteState())
            {
                if(MMP_FALSE == MotorFunc->MotorCtrl_ZoomDetectPR())
                {
                    MotorFunc->MotorCtrl_ZoomStop();
                    HomeIndex = ZoomMT.ssCurrentStep;
                    bFound = MMP_TRUE;
                    break;
                }
            }
      }
      else
      {
            printc("Zoom Mecha PI is abnormal!\n");
      }
      
    }
#if 0
    while(MotorFunc->MotorCtrl_ZoomExciteState());

    if( MMP_TRUE == bFound )
    {
        ubDir = MT_DRV_FORWARD;
        ssStep = 4; // Step should be > 347 = Focus Max(493) - Home(146) 
        MotorFunc->MotorCtrl_ZoomSetParam( MT_SPEED_CONST, ubDir, ssStep );
        MotorFunc->MotorCtrl_ZoomDrive();
        while(MotorFunc->MotorCtrl_ZoomExciteState());
    }
#endif
    MotorFunc->MotorCtrl_ZoomEnableExcite(MMP_FALSE);
    MotorFunc->MotorCtrl_ZoomEnablePr(MMP_FALSE);
    MMPF_OS_Sleep(20);

    if( MMP_TRUE == bFound )
    {
        bZoomHomeFound = MMP_TRUE;
        *ssIndex = HomeIndex;
        TIM_MARK( TIMING_GROUP_MOTOR,"XXXX Search Zoom Mecha Home successfully, %d\n",HomeIndex);
    }
    else
    {
        bZoomHomeFound = MMP_FALSE;
        *ssIndex = 0x7FFF;
         TIM_MARK( TIMING_GROUP_MOTOR,"ERR:Search Zoom Mecha Home fail, %d\n",ZoomMT.ssCurrentStep);
    }

    return bFound;

}


//******************************************************************************
//  Name :           MotorCtrl_SearchFocusMechaHome
//
//  @Description : Move Focus Motor to Home Position.
//  @param[in] 
//  @retval      
//******************************************************************************
MMP_BOOL 
MotorCtrl_SearchFocusMechaHome( MMP_SHORT *ssIndex )
{
    MMP_BOOL   bFound = MMP_FALSE;
    MMP_SHORT  ssStep = 0;
    MMP_UBYTE  ubOffset = 20;
    MMP_UBYTE  ubDir    = MT_DRV_FORWARD;

    MMP_SHORT  HomeIndex = FOCUS_MECHA_HOME_INDEX;
    MMP_ULONG  ulTimeStart = MMPF_OsCounterGet();
    MMP_ULONG  ulTime;
    MMP_BOOL   bFailedSearch = FALSE;
    MMP_SHORT  ssOrgPos;


    TIM_MARK( TIMING_GROUP_MOTOR,"MotorCtrl_SearchFocusMechaHome start\n");

    MotorFunc->MotorCtrl_FocusEnableExcite(MMP_TRUE);
    MotorFunc->MotorCtrl_FocusEnablePr(MMP_TRUE);
    MMPF_OS_Sleep(25);

    ssOrgPos = FocusMT.ssCurrentStep;

    bFocusHomeFound = MMP_FALSE;

    ubOffset = 20;
    if( FocusMT.ssCurrentStep < (HomeIndex + ubOffset) &&
        FocusMT.ssCurrentStep > (HomeIndex - ubOffset) && !bFailedSearch)
    {
        TIM_MARK( TIMING_GROUP_MOTOR,"Focus Motor In Home Range 140~180\n");
        TIM_MARK( TIMING_GROUP_MOTOR,"Move Forward step 50. \n");
        ssStep = 50;
        ubDir  = MT_DRV_FORWARD;
        MotorFunc->MotorCtrl_FocusSetParam(MT_SPEED_CONST, ubDir, ssStep);
        MotorFunc->MotorCtrl_FocusDrive();
        FuncMotorCtrl_Wait_ticks(1);
        while(MotorFunc->MotorCtrl_FocusExciteState())
        {
            ulTime = (MMPF_OsCounterGet() - ulTimeStart)/MMPF_OsCounterGetFreqKhz();
            if( ulTime > 10000 )
            {
                bFailedSearch = TRUE;
                break;
            }
        }

        if( FocusMT.ssCurrentStep  == ssOrgPos )
        {
            // Error
        }
            
        
        FuncMotorCtrl_Wait_ticks(50);
    }

    if( MotorFunc->MotorCtrl_FocusDetectPR() )
    {
        FocusMT.ssTargetStep = 0;
        ubDir = MT_DRV_BACKWARD;
        ssStep = 900; // Step should be > 347 = Focus Max(493) - Home(146) 
        TIM_MARK( TIMING_GROUP_MOTOR,"PR Detected, Search Backward %d\n",ssStep);
        MotorFunc->MotorCtrl_FocusSetParam( MT_SPEED_CONST, ubDir, ssStep );
        MotorFunc->MotorCtrl_FocusDrive();
        FuncMotorCtrl_Wait_ticks(10);

        while(MMP_TRUE == MotorFunc->MotorCtrl_FocusExciteState() && !bFailedSearch)
        {
            if(MMP_FALSE == MotorFunc->MotorCtrl_FocusDetectPR())
            {
                MotorFunc->MotorCtrl_FocusStop();
                TIM_MARK( TIMING_GROUP_MOTOR,"Focus Mecha Found 1 Stop\n");
                HomeIndex = FocusMT.ssCurrentStep;
                bFound = MMP_TRUE;
                break;
            }
            // If time out.
            ulTime = (MMPF_OsCounterGet() - ulTimeStart)/MMPF_OsCounterGetFreqKhz();
            if( ulTime > 10000 )
            {
                bFailedSearch = TRUE;
                break;
            }              
        }
    }
    else
    {
        int iOverSteps=0;
      // Forward 200 step.
        ssStep = FOCUS_MECHA_SEARCH_HOME_FWD_RANGE;

        ubDir  = MT_DRV_FORWARD;
        TIM_MARK( TIMING_GROUP_MOTOR,"PR Not Detected, Move Forward %d\n",ssStep);
        MotorFunc->MotorCtrl_FocusSetParam(MT_SPEED_CONST, ubDir, ssStep);
        MotorFunc->MotorCtrl_FocusDrive();
        FuncMotorCtrl_Wait_ticks(1);
        while(MotorFunc->MotorCtrl_FocusExciteState())
        {
            MMPF_OS_Sleep(2);
            if( MotorFunc->MotorCtrl_FocusDetectPR() )
            {
                iOverSteps++;
                if( iOverSteps > 20 )
                {
                    MotorFunc->MotorCtrl_FocusStop();
                    MMPF_OS_Sleep(10);
                    break;
                }
            }
        }

        FuncMotorCtrl_Wait_ticks(30);

        if(MotorFunc->MotorCtrl_FocusDetectPR())
        {
            // Backward 200 step for searching home.
              FocusMT.ssTargetStep = 0;
              ubDir = MT_DRV_BACKWARD;
              TIM_MARK( TIMING_GROUP_MOTOR,"Search Backward %d\n",ssStep);
              MotorFunc->MotorCtrl_FocusSetParam(MT_SPEED_CONST, ubDir, ssStep);
              MotorFunc->MotorCtrl_FocusDrive();
              FuncMotorCtrl_Wait_ticks(10);
              while( MotorFunc->MotorCtrl_FocusExciteState() && !bFailedSearch)
              {
                  if(!MotorFunc->MotorCtrl_FocusDetectPR())
                  {
                      MotorFunc->MotorCtrl_FocusStop();
                      TIM_MARK( TIMING_GROUP_MOTOR,"Focus Mecha Found 2 Stop\n");
                      HomeIndex = FocusMT.ssCurrentStep;
                      bFound = MMP_TRUE;
                      break;
                  }
                  // If time out.
                  ulTime = (MMPF_OsCounterGet() - ulTimeStart)/MMPF_OsCounterGetFreqKhz();
                  if( ulTime > 10000 )
                  {
                      bFailedSearch = TRUE;
                      break;
                  }            
              }
            
            
        }
        else
        {
            printc("Focus Mecha PI is abnormal!\n");
        }

    }
#if 0
    while( MotorFunc->MotorCtrl_FocusExciteState());

    if( MMP_TRUE == bFound )
    {
        ubDir = MT_DRV_FORWARD;
        ssStep = 4; // Step should be > 347 = Focus Max(493) - Home(146) 
        MotorFunc->MotorCtrl_FocusSetParam( MT_SPEED_CONST, ubDir, ssStep );
        MotorFunc->MotorCtrl_FocusDrive();
        while(MotorFunc->MotorCtrl_FocusExciteState());
    }
#endif
    MotorFunc->MotorCtrl_FocusEnableExcite(MMP_FALSE);
    MotorFunc->MotorCtrl_FocusEnablePr(MMP_FALSE);
    MMPF_OS_Sleep(10);

    if( MMP_TRUE == bFound )
    {
        bFocusHomeFound = MMP_TRUE;
        *ssIndex = HomeIndex;
        TIM_MARK( TIMING_GROUP_MOTOR,"Search Focus Mecha Home successfully, %d\n",HomeIndex);
    }
    else
    {
        bFocusHomeFound = MMP_FALSE;
        *ssIndex = 0x7FFF;
         TIM_MARK( TIMING_GROUP_MOTOR,"ERR:Search Focus Mecha Home fail, %d\n",FocusMT.ssCurrentStep);
    }

    if( bFailedSearch )
    {
        printc("Find focus home error\n");
    }

    TIM_MARK( TIMING_GROUP_MOTOR,"Focus Home search end\n");

	FocusReqState.ubIsCommandQue = 0;

    return bFound;
    
}


//******************************************************************************
//  Name :           MotorCtrl_SetFocssPos
//
//  @Description : Set Focus Position
//  @param[in] 
//  @retval      
//******************************************************************************
void 
MotorCtrl_DriveFocssPos(MMP_UBYTE ubMode, MMP_SHORT ssPos, MMP_UBYTE uStep_En )
{
    MMP_SHORT ssStep = 0;
    MMP_SHORT ssTargetStep = ssPos;
    MMP_UBYTE  ubDir    = MT_DRV_FORWARD;

#if 0
    MotorFunc->MotorCtrl_FocusEnablePr(MMP_TRUE);
    MMPF_OS_Sleep(200);
#endif

#if 1
    if( FocusMT.ssCurrentStep > ssTargetStep )
    {
        ssStep = FocusMT.ssCurrentStep - ssTargetStep;
        ubDir  = MT_DRV_BACKWARD;
    }
    else
    {
        ssStep = ssTargetStep - FocusMT.ssCurrentStep;
        ubDir  = MT_DRV_FORWARD;
    }
    MotorFunc->MotorCtrl_FocusSetParam(ubMode, ubDir, ssStep);
    MotorFunc->MotorCtrl_FocusDrive();
//  while(MotorFunc->MotorCtrl_FocusExciteState());

#else
    do
    {
        if( FocusMT.ssCurrentStep > ssTargetStep )
        {
            ssStep = FocusMT.ssCurrentStep - ssTargetStep;
            ubDir  = MT_DRV_BACKWARD;
        }
        else
        {
            ssStep = ssTargetStep - FocusMT.ssCurrentStep;
            ubDir  = MT_DRV_FORWARD;
        }
        MotorFunc->MotorCtrl_FocusSetParam(MT_SPEED_ACC_HIGH, ubDir, ssStep);
        MotorFunc->MotorCtrl_FocusDrive();

        while(MotorFunc->MotorCtrl_FocusExciteState())
        {
            MMPF_OS_Sleep(3);
        }

    }while(ssTargetStep != FocusMT.ssCurrentStep);
#endif

#if 0
    MotorFunc->MotorCtrl_FocusEnablePr(MMP_FALSE);
    MMPF_OS_Sleep(100);
#endif
}


//******************************************************************************
//  Name :           MotorCtrl_SetFocssPos
//
//  @Description : Set Focus Position
//  @param[in] 
//  @retval      
//******************************************************************************
void 
MotorCtrl_DriveSetAFPosition(MMP_UBYTE ubMode, MMP_SHORT ssPos)
{
    MMP_UBYTE  uStepEn = 1;  
    MotorCtrl_DriveFocssPos(ubMode, ssPos, uStepEn);

}

//******************************************************************************
//  Name :           MotorCtrl_ZoomRunIn
//
//  @Description : Move Zoom Motor to Home Position.
//  @param[in] 
//  @retval      
//******************************************************************************
extern MMP_BOOL BurninMode;
void 
MotorCtrl_ZoomRunIn( void )
{
    MMP_SHORT HomeIndex = 0;
    MMP_SHORT ssStep   = 0, i=0;
    //MMP_USHORT usRunInCounter = 0;

    ssStep = ZoomIndex_LUT[ZOOM_TELE_INDEX] - ZoomIndex_LUT[ZOOM_WIDE_INDEX];

    if( MotorCtrl_SearchZoomMechaHome(&HomeIndex) )
    {
        ZoomMotor_SetCurrIndex(ZoomIndex_LUT[ZOOM_MECHA_HOME_INDEX]);
        MotorCtrl_DriveZoomWidePos();
    }

    MotorFunc->MotorCtrl_ZoomEnablePr(MMP_TRUE);
    MMPF_OS_Sleep(200);

//    while( ZoomMT.bSelfTest )
    while(( ZoomMT.bSelfTest )&&(BurninMode == 1))
    {
        if( !MotorFunc->MotorCtrl_ZoomExciteState())
        {
            MMPF_OS_Sleep(300);

            if( MMP_FALSE == MotorFunc->MotorCtrl_ZoomDetectPR() )
            {
                ZoomMT.ssTargetStep = ZoomIndex_LUT[ZOOM_TELE_INDEX];
                MotorFunc->MotorCtrl_ZoomSetParam( MT_SPEED_ACC_MID, MT_DRV_FORWARD, ssStep );
                MotorFunc->MotorCtrl_ZoomDrive();
            }
            else
            {
                ZoomMT.ssTargetStep = ZoomIndex_LUT[ZOOM_WIDE_INDEX];
                MotorFunc->MotorCtrl_ZoomSetParam( MT_SPEED_ACC_MID, MT_DRV_BACKWARD, ssStep );
                MotorFunc->MotorCtrl_ZoomDrive();

                //while(MMP_TRUE == MotorFunc->MotorCtrl_ZoomDetectPR());
                //TIM_MARK( TIMING_GROUP_MOTOR,"RunIn %3d Times, Zoom HomeIndex: %d \n",++usRunInCounter, ZoomMT.ssCurrentStep);
            }
        }
        MMPF_OS_Sleep(10);
		i++;
		if(i>200)
			break;
    }

    MotorFunc->MotorCtrl_ZoomStop();
    MMPF_OS_Sleep(100);

    if( MotorCtrl_SearchZoomMechaHome(&HomeIndex) )
    {
        ZoomMotor_SetCurrIndex(ZoomIndex_LUT[ZOOM_MECHA_HOME_INDEX]);
        MotorCtrl_DriveZoomWidePos();
    }

    MotorFunc->MotorCtrl_ZoomEnablePr(MMP_FALSE);
    MotorFunc->MotorCtrl_ZoomEnableExcite(MMP_FALSE);
    MMPF_OS_Sleep(200);

}

//******************************************************************************
//  Name :           MotorCtrl_FocusRunIn
//
//  @Description : Move Focus Motor to Home Position.
//  @param[in] 
//  @retval      
//******************************************************************************
extern MMP_BOOL BurninMode;
void 
MotorCtrl_FocusRunIn( void )
{
    MMP_SHORT HomeIndex = 0,i=0;
    MMP_SHORT ssTargetIndex1 = 0;
    MMP_SHORT ssTargetIndex2 = 0;
    MMP_SHORT ssStep   = 0;
    //MMP_USHORT usRunInCounter = 0;

    ssTargetIndex1 = 100;//50;
    ssTargetIndex2 = 250;//850;
    ssStep = ssTargetIndex2 - ssTargetIndex1 ;

    if( MotorCtrl_SearchFocusMechaHome(&HomeIndex) )
    {
        FocusMotor_SetCurrIndex(FOCUS_MECHA_HOME_INDEX);
        printc("Search Focus Mecha Home successfully, %d\n",HomeIndex);
        MotorCtrl_DriveSetAFPosition(MT_SPEED_ACC_MID, ssTargetIndex1);
    }
    else
    {
        printc("ERR:Search Focus Mecha Home fail.\n");
    }

    MotorFunc->MotorCtrl_FocusEnablePr(MMP_TRUE);
    MMPF_OS_Sleep(100);

    while(( FocusMT.bSelfTest )&&(BurninMode == 1))
    {
        if( !MotorFunc->MotorCtrl_FocusExciteState())
        {
            MMPF_OS_Sleep(200);

            if( MMP_FALSE == MotorFunc->MotorCtrl_FocusDetectPR() )
            {
                FocusMT.ssTargetStep = ssTargetIndex2;
                MotorFunc->MotorCtrl_FocusSetParam( MT_SPEED_ACC_MID, MT_DRV_FORWARD, ssStep );
                MotorFunc->MotorCtrl_FocusDrive();
            }
            else
            {
            //  usRunInCounter++;
                FocusMT.ssTargetStep = ssTargetIndex1;
                MotorFunc->MotorCtrl_FocusSetParam( MT_SPEED_ACC_MID, MT_DRV_BACKWARD, ssStep );
                MotorFunc->MotorCtrl_FocusDrive();
                //while(MMP_TRUE == MotorFunc->MotorCtrl_FocusDetectPR());
				MMPF_OS_Sleep(1000);
            //  HomeIndex = FocusMT.ssCurrentStep;
                //TIM_MARK( TIMING_GROUP_MOTOR,"RunIn %3d Times, Focus HomeIndex: %d \n", ++usRunInCounter, FocusMT.ssCurrentStep);
            }

        }
        MMPF_OS_Sleep(10);
		i++;
		if(i>5)
			{
			i=0;
			break;
			}
    }
    MotorFunc->MotorCtrl_FocusStop();

    MMPF_OS_Sleep(50);
  // Back to Home position first.
    if( MotorCtrl_SearchFocusMechaHome(&HomeIndex) )
    {
        FocusMotor_SetCurrIndex(FOCUS_MECHA_HOME_INDEX);
        printc("Search Focus Mecha Home successfully, %d\n",HomeIndex);
    }
    else
    {
        printc("ERR:Search Focus Mecha Home fail.\n");
    }
}

void Burnin( void )
{
	//char dbgTxt[128];
	int i=0;
	
	if(BurninMode == 0)
	{
		ZoomMT.bSelfTest = MMP_FALSE; 
		FocusMT.bSelfTest = MMP_FALSE;
	}
	if(BurninMode == 1)	
	{			
		OSD_Draw_TestMessage(10,30,4,"Burnin.Doing");
	}
	
	while(BurninMode == 1)
	{
		ZoomMT.bSelfTest = MMP_TRUE;
		MotorCtrl_ZoomRunIn();
		//FuncMotorCtrl_ZoomSetPosition( 125 );
		//UartExecuteCommandEx("zoompos 125");
		MMPF_OS_Sleep(100);
		FuncMotorCtrl_ZoomStop();
		MMPF_OS_Sleep(100);
		if(0)//(BurninMode == 0)
			break;
			
		FocusMT.bSelfTest = MMP_TRUE;
		MotorCtrl_FocusRunIn();
		//FuncMotorCtrl_ZoomSetPosition( 0 );
		//UartExecuteCommandEx("zoompos 0");
		MMPF_OS_Sleep(100);
		FuncMotorCtrl_FocusStop();
		MMPF_OS_Sleep(100);
		if(0)//(BurninMode == 0)
			break;

		i++;
	}
	
	printc("@@  Burnin Exit  BurninMode = %d @@@@@\n",BurninMode);
	MMPF_OS_Sleep(3000);
	#if 0//get raw and warm pixel data
	UartExecuteCommandEx("getcsraw 0 1");
	MMPF_OS_Sleep(3000);
	#endif
	OSD_Draw_TestMessage(10,30,4,"Burnin Finish");
}

//******************************************************************************
//  Name :           MotorCtrl_SearchZoomLUT
//
//  @Description : Search Zoom Step in Look up table and return Zoom Index.
//  @param[in]      ulVal   Zoom Step 
//  @retval     ZoomIndex   Zoom Index
//******************************************************************************
MMP_UBYTE 
MotorCtrl_SearchZoomLUT(MMP_SHORT ulVal)
{
    MMP_UBYTE ZoomIndex = 0xFF;
    MMP_UBYTE ubLength = 0;

    ubLength = sizeof(ZoomIndex_LUT)/sizeof(MMP_SHORT);

    ZoomIndex = SearchLUT( ulVal, ZoomIndex_LUT, ubLength);
    
    if( ubLength != ZoomIndex )
        return ZoomIndex;
    else
        return (ubLength -1);
}


//******************************************************************************
//  Name :           SearchLUT
//
//  @Description : 
//  @param[in]      ulVal   Search value
//  @retval         Array   Look up table pointer.
//******************************************************************************
MMP_UBYTE 
SearchLUT(MMP_SHORT ulVal, MMP_SHORT *Array, MMP_SHORT ArraySize)
{
    MMP_UBYTE   LVal,RVal,rVal;
    MMP_UBYTE   MidVal;

    LVal = 0;
    RVal = ArraySize;

    while(LVal <= RVal)
    {
        rVal = (LVal+RVal) >> 1;

        if(Array[rVal] == ulVal)
        {
            return rVal;
        }
        else
        {
            if(LVal == RVal)
            {
                if(MidVal > LVal)
                {
                    if( (Array[MidVal] - ulVal) >(ulVal - Array[LVal]) )
                        rVal = LVal;
                    else
                        rVal = MidVal;
                }
                else
                {
                    if( (Array[LVal] - ulVal) > (ulVal - Array[MidVal]) )
                        rVal = MidVal;
                    else
                        rVal = LVal;
                }
                return rVal;
            }

			#if 0 // some points are not rounding
            if(Array[rVal] > ulVal)
                RVal = rVal - 1;
            else
                LVal = rVal + 1;
			#else // more closer to rounding
			if(Array[rVal] > ulVal)
			{
                RVal = rVal - 1;
				if(Array[RVal] < ulVal)
					LVal = RVal;
			}
            else
			{
                LVal = rVal + 1;
				if(Array[LVal] > ulVal)
					RVal = LVal;
			}
			#endif
            MidVal = rVal;
        }
    }

    return rVal;
}


//******************************************************************************
//  Name :           MotorCtrl_Process
//
//  @Description : 
//******************************************************************************
void 
MotorCtrl_Process(void *p_arg)
{
    MMPF_OS_FLAGS flags;
    MMPF_OS_FLAGS waitFlags;
    MMP_SHORT    ssStep;
    MMP_UBYTE     ubZoomLUTIndex;
    MMP_SHORT    usZoomHomeIndex;
    MMP_SHORT    usFocusHomeIndex;
    
    printc("MOTOR_Task()\n");

    MotorCtrlEventFlag = MMPF_OS_CreateEventFlagGrp(0);
    Sem_MotorCtrl = MMPF_OS_CreateSem(1); 
    
//    MotorCtrl_Param_Reset();

    waitFlags = MOTOR_FLAG_INITIALIZE | MOTOR_FLAG_ZOOM_FORWARD  | MOTOR_FLAG_ZOOM_STOP | MOTOR_FLAG_ZOOM_CALIB | 
                MOTOR_FLAG_ZOOM_HOME | MOTOR_FLAG_ZOOM_SELFTEST | MOTOR_FLAG_ZOOM_BACKWARD ;
                
    waitFlags |= MOTOR_FLAG_FOCUS_SET_POS | MOTOR_FLAG_FOCUS_STOP | MOTOR_FLAG_FOCUS_CALIB | 
                 MOTOR_FLAG_FOCUS_HOME | MOTOR_FLAG_FOCUS_SELFTEST ;

	waitFlags |= MOTOR_FLAG_FOCUS_CHECK_CMD;

    
#if (AIT_LENS_TYPE==AIT_LENS_TYPE_DUMMY)
            waitFlags = MOTOR_FLAG_FOCUS_FOREVER;
#endif //(AIT_LENS_TYPE==AIT_LENS_TYPE_DUMMY)

    while(1)
    {
        MMPF_OS_WaitFlags(MotorCtrlEventFlag, waitFlags, MMPF_OS_FLAG_WAIT_SET_ANY | MMPF_OS_FLAG_CONSUME, 0, &flags);
        
        if(flags & MOTOR_FLAG_INITIALIZE) 
        { // comes from host command
          
            FuncMotorCtrl_Configuration();

            MotorFunc->MotorCtrl_Initialize();
          
            if( MotorCtrl_SearchZoomMechaHome(&usZoomHomeIndex) )
            {
                ZoomMotor_SetCurrIndex(ZoomIndex_LUT[ZOOM_MECHA_HOME_INDEX]);
                printc("Search Zoom Mecha Home successfully\n"); 
                MotorCtrl_DriveZoomWidePos();
            }
            else
            {
                printc("ERR:Search Zoom Mecha Home fail.\n");
            }

          //ubZoomLUTIndex = MotorCtrl_SearchZoomLUT(ZoomMT.ssCurrentStep);
           
            if( MotorCtrl_SearchFocusMechaHome(&usFocusHomeIndex) )
            {
                FocusMotor_SetCurrIndex(FOCUS_MECHA_HOME_INDEX);
                printc("Search Focus Mecha Home successfully\n");
            }
            else
            {
                printc("ERR:Search Focus Mecha Home fail.\n");
            }
            MotorCtrl_DriveFocssPos(MT_SPEED_CONST, FocusMT.ssCurrentStep, 1);


            FocusMT.bMotorInitDone = MMP_TRUE;
            ZoomMT.bMotorInitDone = MMP_TRUE;
        }
        
        if(flags & MOTOR_FLAG_ZOOM_FORWARD) 
        { // Forward request
            if(MMP_TRUE == MotorFunc->MotorCtrl_ZoomExciteState() )
            {
                if( MT_DRV_FORWARD == MotorFunc->MotorCtrl_ZoomDirection() )
                { 
                    continue;
                }
                else
                { // Motor Stop and Reversed.
                    MotorFunc->MotorCtrl_ZoomStop();
                    MMPF_OS_Sleep(200);
                }
            }
            if( ZoomMT.ssCurrentStep < ZoomMT.ssTargetStep )
            {
                ssStep = ZoomMT.ssTargetStep - ZoomMT.ssCurrentStep;
                TIM_MARK( TIMING_GROUP_MOTOR,"ZOOM_FORWARD %d", ssStep );

                MotorFunc->MotorCtrl_ZoomSetParam( MT_SPEED_ACC_LOW, MT_DRV_FORWARD, ssStep );
                MotorFunc->MotorCtrl_ZoomDrive();

            }
        }

        if(flags & MOTOR_FLAG_ZOOM_BACKWARD) 
        { // comes from host command
            
            if(MMP_TRUE == MotorFunc->MotorCtrl_ZoomExciteState() )
            {
                if( MT_DRV_BACKWARD == MotorFunc->MotorCtrl_ZoomDirection() )
                { // Request ignored.
                    continue;
                }
                else
                { // Motor Stop and Reversed.
                    MotorFunc->MotorCtrl_ZoomStop();
                    MMPF_OS_Sleep(40);
                }
            }
            
            if( ZoomMT.ssCurrentStep > ZoomMT.ssTargetStep )
            {
                ssStep = ZoomMT.ssCurrentStep - ZoomMT.ssTargetStep;
                MotorFunc->MotorCtrl_ZoomSetParam( MT_SPEED_ACC_LOW, MT_DRV_BACKWARD, ssStep );
                MotorFunc->MotorCtrl_ZoomDrive();
            }

        }
        if(flags & MOTOR_FLAG_ZOOM_STOP) 
        { // comes from host command

            if( MMP_TRUE == MotorFunc->MotorCtrl_ZoomExciteState())
            {
                MotorFunc->MotorCtrl_ZoomStop();
                while(MotorFunc->MotorCtrl_ZoomExciteState());
                MotorFunc->MotorCtrl_ZoomEnableExcite(MMP_FALSE);
            }

            TIM_MARK( TIMING_GROUP_MOTOR,"Zoom Stop, CurrentStep: %d, Target: %d\n",ZoomMT.ssCurrentStep, ZoomMT.ssTargetStep);

            ubZoomLUTIndex = MotorCtrl_SearchZoomLUT(ZoomMT.ssCurrentStep);
        }

        if(flags & MOTOR_FLAG_ZOOM_CALIB) 
        { // comes from host command
			Burnin();
        }
        if(flags & MOTOR_FLAG_ZOOM_HOME) 
        { // comes from host command

            if( MotorCtrl_SearchZoomMechaHome(&usZoomHomeIndex) )
            {
                printc("Search Zoom Mecha Home successfully, %d\n",usZoomHomeIndex); 
                MotorCtrl_DriveZoomWidePos();
            }
            else
            {
                printc("ERR:Search Zoom Mecha Home fail.\n");
            }

            ubZoomLUTIndex = MotorCtrl_SearchZoomLUT(ZoomMT.ssCurrentStep);

        }

        if(flags & MOTOR_FLAG_ZOOM_SELFTEST) 
        { // comes from host command
            MotorCtrl_ZoomRunIn();
        }
 
        if(flags & MOTOR_FLAG_FOCUS_SET_POS) 
        { // comes from host command
        #if 0
            MotorCtrl_DriveSetAFPosition(MT_SPEED_ACC_MID, FocusMT.ssTargetStep);

            while( MotorFunc->MotorCtrl_FocusExciteState() )
            {
                MMPF_OS_Sleep(10);
            }
        #endif
        }

        if(flags & MOTOR_FLAG_FOCUS_STOP) 
        { // comes from host command

            if( MMP_TRUE == MotorFunc->MotorCtrl_FocusExciteState())
                MotorFunc->MotorCtrl_FocusStop();

            TIM_MARK( TIMING_GROUP_MOTOR,"Focus Stop, CurrentStep: %d, Target: %d\n",FocusMT.ssCurrentStep, FocusMT.ssTargetStep);
        }
        if(flags & MOTOR_FLAG_FOCUS_CALIB) 
        { // comes from host command

        }
        if(flags & MOTOR_FLAG_FOCUS_HOME) 
        { // comes from host command
            if( MotorCtrl_SearchFocusMechaHome(&usFocusHomeIndex) )
                printc("Search Focus Mecha Home successfully, %d\n",usFocusHomeIndex);
            else
                printc("ERR:Search Focus Mecha Home fail.\n");
        }
        if(flags & MOTOR_FLAG_FOCUS_SELFTEST) 
        { // comes from host command
            MotorCtrl_FocusRunIn();
        }

        if(flags & MOTOR_FLAG_ZOOM_BACK_HOME) 
        { // 

        }

        if(flags & MOTOR_FLAG_FOCUS_BACK_HOME) 
        { // 

        }

		if(flags & MOTOR_FLAG_FOCUS_CHECK_CMD) 
		{
			if(FocusReqState.ubIsCommandQue==1)
			{
				// printc("MOTOR_FLAG_FOCUS_CHECK_CMD, FocusMTState:%d \n",MotorFunc->MotorCtrl_FocusExciteState());
				if(MotorFunc->MotorCtrl_FocusExciteState()==0)
				{
					FuncMotorCtrl_FocusSetPositionEx(FocusReqState.ubSpeedModeQue,FocusReqState.ssTargetStepQue);
					FocusReqState.ubIsCommandQue = 0;
					// printc("Process Focus Que, Pos to:%d \n",FocusReqState.ssTargetStepQue);
				}
				else
					MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_FOCUS_CHECK_CMD, MMPF_OS_FLAG_SET);
			}
		}

    }
}




void MotorCtrl_RegWrite(MMP_UBYTE ch, MMP_UBYTE reg, MMP_USHORT wdata)
{
    MotorFunc->MotorCtrl_RegWrite(ch, reg, wdata);
}

MMP_UBYTE MotorCtrl_RegRead(MMP_UBYTE ch, MMP_UBYTE reg, MMP_UBYTE ch_rd, MMP_UBYTE BitSize)
{
    return MotorFunc->MotorCtrl_RegRead(ch, reg, ch_rd, BitSize);    
}

//******************************************************************************
//  Name :           FuncMotorCtrl_ZoomMove
//
//  @Description : Move Zoom Motor 
//  @param[in]   bForward, direction MMP_TRUE  -> Forward
//                                   MMP_FALSE -> Backward
//               usSteps ,  The steps to move
//******************************************************************************
MMP_BOOL
FuncMotorCtrl_ZoomMove( MMP_BOOL bForward, MMP_USHORT usSteps )
{
    if( MotorFunc->MotorCtrl_ZoomExciteState() )
    {
        return MMP_FALSE;
   	}

    MotorFunc->MotorCtrl_ZoomEnablePr(MMP_TRUE);

    if( bForward )
    {
       ZoomMT.ssTargetStep = ZoomMT.ssCurrentStep + usSteps;
        MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_ZOOM_FORWARD, MMPF_OS_FLAG_SET);
	}
	else
	{
       ZoomMT.ssTargetStep = ZoomMT.ssCurrentStep - usSteps;
        MMPF_OS_SetFlags(MotorCtrlEventFlag, MOTOR_FLAG_ZOOM_BACKWARD, MMPF_OS_FLAG_SET);
	}

    // Wait until done.
    while( MotorFunc->MotorCtrl_ZoomExciteState() ) MMPF_OS_Sleep(5);
    
	return MMP_TRUE;
}

//******************************************************************************
//  Name :           FuncMotorCtrl_FocusMove
//
//  @Description : Move Focus Motor 
//  @param[in]   bForward, direction MMP_TRUE  -> Forward
//                                   MMP_FALSE -> Backward
//               usSteps ,  The steps to move
//******************************************************************************
MMP_BOOL
FuncMotorCtrl_FocusMove( MMP_BOOL bForward, MMP_USHORT usSteps )
{

    MMP_UBYTE  ubDir    = MT_DRV_FORWARD;

    MotorFunc->MotorCtrl_FocusEnablePr(MMP_TRUE);
    
    if( bForward )
    {
        ubDir  = MT_DRV_FORWARD;
    }
    else
    {
        ubDir  = MT_DRV_BACKWARD;
    }

    MotorFunc->MotorCtrl_FocusSetParam(MT_SPEED_ACC_MID, ubDir, usSteps);
    MotorFunc->MotorCtrl_FocusDrive();

    // Wait until done.
    while(MotorFunc->MotorCtrl_FocusExciteState())MMPF_OS_Sleep(5);
    
    return MMP_TRUE; 
}

//******************************************************************************
//  Name :           MotorCtrl_ZoomParking
//
//  @Description : Park Zoom Motor around home 
//  @param[in]     N/A
//  @retval        MMP_TRUE:   Successful
//                 MMP_FALSE:  Failed
//******************************************************************************
MMP_BOOL
MotorCtrl_ZoomParking( void )
{
    MMP_BOOL   bFound = MMP_FALSE;
    MMP_SHORT  ssStep = 0;
    MMP_UBYTE  ubDir    = MT_DRV_FORWARD;
    //MMP_SHORT  HomeIndex = ZoomIndex_LUT[ZOOM_MECHA_HOME_INDEX];

    if( bZoomHomeFound == MMP_FALSE )
    {
        return MMP_FALSE;
    }

    TIM_MARK( TIMING_GROUP_MOTOR,"MotorCtrl_ZoomParking\n");
    
    MotorFunc->MotorCtrl_ZoomEnableExcite(MMP_TRUE);
    MotorFunc->MotorCtrl_ZoomEnablePr(MMP_TRUE);
    MMPF_OS_Sleep(25);

    if( MMP_TRUE == MotorFunc->MotorCtrl_ZoomDetectPR() )
    {
        ubDir = MT_DRV_BACKWARD;
        ssStep = ZoomIndex_LUT[ZOOM_TELE_INDEX] - ZoomIndex_LUT[ZOOM_WIDE_INDEX];

        TIM_MARK( TIMING_GROUP_MOTOR,"Zoom backward %d\n", ssStep);

        MotorFunc->MotorCtrl_ZoomSetParam( MT_SPEED_CONST, ubDir, ssStep );
        MotorFunc->MotorCtrl_ZoomDrive();
        FuncMotorCtrl_Wait_ticks(10);
        while(MMP_TRUE == MotorFunc->MotorCtrl_ZoomExciteState())
        {
            if(MMP_FALSE == MotorFunc->MotorCtrl_ZoomDetectPR())
            {
                MotorFunc->MotorCtrl_ZoomStop();
                bFound = MMP_TRUE;
                break;
            }
        }

        MotorFunc->MotorCtrl_ZoomSetParam( MT_SPEED_CONST, MT_DRV_FORWARD, 10 );
        FuncMotorCtrl_Wait_ticks(2);
        while(MMP_TRUE == MotorFunc->MotorCtrl_ZoomExciteState()) MMPF_OS_Sleep(2);
    }
    else
    {
        int iOverSteps=0;
      // Forward 200 step.
        ubDir = MT_DRV_FORWARD;
        ssStep = ZoomIndex_LUT[25];
        TIM_MARK( TIMING_GROUP_MOTOR,"PR Not Detected, Move Forward %d\n",ssStep);
        MotorFunc->MotorCtrl_ZoomSetParam(MT_SPEED_CONST, ubDir, ssStep);
        MotorFunc->MotorCtrl_ZoomDrive();
        FuncMotorCtrl_Wait_ticks(10);
        while(MotorFunc->MotorCtrl_ZoomExciteState())
        {
            MMPF_OS_Sleep(2);
            if( MotorFunc->MotorCtrl_ZoomDetectPR() )
            {
                iOverSteps++;
                if( iOverSteps > 5 )
                {
                    MotorFunc->MotorCtrl_ZoomStop();
                    MMPF_OS_Sleep(2);
                    bFound = MMP_TRUE;

                }
            }
        }

        FuncMotorCtrl_Wait_ticks(50);
      
    }

    MotorFunc->MotorCtrl_ZoomEnableExcite(MMP_FALSE);
    MotorFunc->MotorCtrl_ZoomEnablePr(MMP_FALSE);
    MMPF_OS_Sleep(10);

    return MMP_TRUE;

}

//******************************************************************************
//  Name :           MotorCtrl_FocusParking
//
//  @Description : Park Focus Motor around home 
//  @param[in]     N/A
//  @retval        MMP_TRUE:   Successful
//                 MMP_FALSE:  Failed
//******************************************************************************
MMP_BOOL 
MotorCtrl_FocusParking( void )
{
    MMP_BOOL   bFound = MMP_FALSE;
    MMP_SHORT  ssStep = 0;

    MMP_UBYTE  ubDir    = MT_DRV_FORWARD;

    if( bFocusHomeFound == MMP_FALSE )
    {
        return MMP_FALSE;
    }

    MotorFunc->MotorCtrl_FocusEnableExcite(MMP_TRUE);
    MotorFunc->MotorCtrl_FocusEnablePr(MMP_TRUE);
    MMPF_OS_Sleep(25);

    if( MotorFunc->MotorCtrl_FocusDetectPR() )
    {
        FocusMT.ssTargetStep = 0;
        ubDir = MT_DRV_BACKWARD;
        ssStep = 900;

        MotorFunc->MotorCtrl_FocusSetParam( MT_SPEED_CONST, ubDir, ssStep );
        MotorFunc->MotorCtrl_FocusDrive();
        FuncMotorCtrl_Wait_ticks(10);

        while(MMP_TRUE == MotorFunc->MotorCtrl_FocusExciteState())
        {
            if(MMP_FALSE == MotorFunc->MotorCtrl_FocusDetectPR())
            {
                MotorFunc->MotorCtrl_FocusStop();
                bFound = MMP_TRUE;
                break;
            }
            
        }
        MotorFunc->MotorCtrl_FocusSetParam(MT_SPEED_CONST, MT_DRV_FORWARD, 10);
        MotorFunc->MotorCtrl_FocusDrive();            
        FuncMotorCtrl_Wait_ticks(2);
        while(MotorFunc->MotorCtrl_FocusExciteState()) MMPF_OS_Sleep(2);
    }
    else
    {
        int iOverSteps=0;
      // Forward 200 step.
        ssStep = FOCUS_MECHA_SEARCH_HOME_FWD_RANGE;

        ubDir  = MT_DRV_FORWARD;
        TIM_MARK( TIMING_GROUP_MOTOR,"PR Not Detected, Move Forward %d\n",ssStep);
        MotorFunc->MotorCtrl_FocusSetParam(MT_SPEED_CONST, ubDir, ssStep);
        MotorFunc->MotorCtrl_FocusDrive();
        FuncMotorCtrl_Wait_ticks(1);
        while(MotorFunc->MotorCtrl_FocusExciteState())
        {
            MMPF_OS_Sleep(2);
            if( MotorFunc->MotorCtrl_FocusDetectPR() )
            {
                iOverSteps++;
                if( iOverSteps > 5 )
                {
                    MotorFunc->MotorCtrl_FocusStop();
                    MMPF_OS_Sleep(2);
                    break;
                }
            }
        }

    }
    MotorFunc->MotorCtrl_FocusEnableExcite(MMP_FALSE);
    MotorFunc->MotorCtrl_FocusEnablePr(MMP_FALSE);
    MMPF_OS_Sleep(2);

    return bFound;
    
}

/**
0x0 : OFF
0x1 : Forward
0x2 : Reverse
0x3 : Brake


*/
void FuncMotorCtl_IrisDirection(MMP_UBYTE ubDirection)
{
	MotorFunc->MotorCtl_IrisDirection(ubDirection);
}

void FuncMotorCtl_TriggerMechanicalShutter(MMP_BOOL bTrigger)
{
	MotorFunc->MotorCtl_TriggerMechanicalShutter(bTrigger);
}

void FuncMotorCtl_MechanicalShutterDirection(MMP_BOOL bForwardReverse)
{
	MotorFunc->MotorCtl_MechanicalShutterDirection(bForwardReverse);
}


void 
MotorCtrlTask(void *p_arg)
{   
    MotorCtrl_Param_Reset();

//    printc( "Motor init start %d\n", MMPF_OsCounterGet() /MMPF_OsCounterGetFreqKhz() );
    FuncMotorCtrl_InitializeEx();
//    printc( "Motor init end %d\n", MMPF_OsCounterGet() /MMPF_OsCounterGetFreqKhz() );   

    #if (!BIND_MOTOR_DUMMY)
    // Inform ISP until Home search finish   
    ISP_IF_AF_SetPos(FuncMotorCtrl_FocusGetPosition()); 
    ISP_IF_AF_SetZoomTarPos(FuncMotorCtrl_ZoomCurrentIndex()); 
    ISP_IF_AF_SetAFStyle(ISP_AF_STYLE_MOVIE);
	#endif 
    MotorCtrl_Process(p_arg);
}

#endif
/// @}
