//==============================================================================
//
//  File        : AHC_PWM.c
//  Description : AHC PWM function
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_pwm.h"
#include "mmps_pwm.h"
/*===========================================================================
 * Main body
 *===========================================================================*/ 
#if 0
void _____PWM_Function_________(){ruturn;} //dummy
#endif
#define	DUTY_LEVEL_NUM		(5)
#define	DUTY_PERLEVEL_VAL	(100/DUTY_LEVEL_NUM)
#define PwmUartSendTrace	UartSendTrace


MMP_ULONG			g_ulDuty = 0;
CustRemoterWorkMode	g_ulMode = STOP_ALL;
MMP_ULONG			g_ulAngle = 0;

//------------------------------------------------------------------------------
//  Function    : AHC_PWM_Initialize
//  Description :
//------------------------------------------------------------------------------
/** @brief Driver init

Driver init
@retval TRUE or FALSE.
*/
AHC_BOOL AHC_PWM_Initialize(void)
{
    MMP_ERR status;

    status = MMPS_PWM_Initialize();

    if (status != MMP_ERR_NONE) {
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_PWM_OutputPulse
//  Description :
//------------------------------------------------------------------------------
/** @brief Simplely output some pulses (According to the parameters)

Simplely output some pulses (According to the parameters)
@param[in] pwm_pin : PWM I/O pin selection, please refer MMP_PWM_PIN
@param[in] bEnableIoPin : enable/disable the specific PWM pin
@param[in] ulFrquency : the pulse frequency.
@param[in] bHigh2Low : MMP_TRUE: High to Low pulse, MMP_FALSE: Low to High pulse
@param[in] bEnableInterrupt : enable interrupt or not
@param[in] pwm_callBack : call back function when interrupt occurs
@param[in] ulNumOfPulse : number of pulse, 0 stand for using PWM auto mode to generate infinite pulse.
@return It reports the status of the operation.
*/
AHC_BOOL AHC_PWM_OutputPulse(MMP_PWM_PIN pwm_pin, AHC_BOOL bEnableIoPin, UINT32 ulFrquency, AHC_BOOL bHigh2Low, AHC_BOOL bEnableInterrupt, void* pwm_callBack, UINT32 ulNumOfPulse)
{
    MMP_ERR status;

    status = MMPS_PWM_OutputPulse(pwm_pin, 0, ulFrquency, 50, bHigh2Low, bEnableInterrupt, (PwmCallBackFunc*)pwm_callBack, ulNumOfPulse);

    if (status != MMP_ERR_NONE) {
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_PWM_OutputPulseEx
//  Description :
//------------------------------------------------------------------------------
/** @brief Simplely output some pulses (According to the parameters)

Simplely output some pulses (According to the parameters)
@param[in] pwm_pin : PWM I/O pin selection, please refer MMP_PWM_PIN
@param[in] bEnableIoPin : enable/disable the specific PWM pin
@param[in] ulFrquency : the pulse frequency.
@param[in] ulDuty : percentage of signal = high in 1 PWM cycle
@param[in] bHigh2Low : MMP_TRUE: High to Low pulse, MMP_FALSE: Low to High pulse
@param[in] bEnableInterrupt : enable interrupt or not
@param[in] pwm_callBack : call back function when interrupt occurs
@param[in] ulNumOfPulse : number of pulse, 0 stand for using PWM auto mode to generate infinite pulse.
@return It reports the status of the operation.
*/
AHC_BOOL AHC_PWM_OutputPulseEx(MMP_PWM_PIN pwm_pin, AHC_BOOL bEnableIoPin, UINT32 ulFrquency, UINT32 ulDuty, AHC_BOOL bHigh2Low, AHC_BOOL bEnableInterrupt, void* pwm_callBack, UINT32 ulNumOfPulse)
{
    MMP_ERR status;

    status = MMPS_PWM_OutputPulse(pwm_pin, 0, ulFrquency, ulDuty, bHigh2Low, bEnableInterrupt, (PwmCallBackFunc*)pwm_callBack, ulNumOfPulse);

    if (status != MMP_ERR_NONE) {
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

typedef enum{
	//direct
	ACTION_MUP,
	ACTION_MDOWN,
	ACTION_MLEFT,
	ACTION_MRIGHT,
	//wire ctrl
	ACTION_MRELEASE,
	ACTION_MCLIPS,
	//speed ctrl
	ACTION_MSPEEDUP,
	ACTION_MSPEEDDOWN,
	
	ACTION_NONE,
}MOTOR_ACTION;

CustRemoterWorkMode ubSTOP_ALL[ACTION_NONE]={DEAD_AHEAD,DEAD_ASTERN,FRONT_LEFT,FRONT_RIGHT, STOP_ALL,STOP_ALL,STOP_ALL,STOP_ALL};

CustRemoterWorkMode ubDEAD_AHEAD[ACTION_NONE]={DEAD_AHEAD,STOP_ALL,FRONT_LEFT,FRONT_RIGHT, STOP_ALL,STOP_ALL,STOP_ALL,STOP_ALL};
CustRemoterWorkMode ubFRONT_LEFT[ACTION_NONE]={DEAD_AHEAD,STOP_ALL,FRONT_LEFT,DEAD_AHEAD, STOP_ALL,STOP_ALL,STOP_ALL,STOP_ALL};
CustRemoterWorkMode ubFRONT_RIGHT[ACTION_NONE]={DEAD_AHEAD,STOP_ALL,DEAD_AHEAD,FRONT_RIGHT, STOP_ALL,STOP_ALL,STOP_ALL,STOP_ALL};

CustRemoterWorkMode ubDEAD_ASTERN[ACTION_NONE]={STOP_ALL,DEAD_ASTERN,LEFT_REAR,RIGHT_REAR, STOP_ALL,STOP_ALL,STOP_ALL,STOP_ALL};
CustRemoterWorkMode ubLEFT_REAR[ACTION_NONE]={STOP_ALL,DEAD_ASTERN,LEFT_REAR,DEAD_ASTERN, STOP_ALL,STOP_ALL,STOP_ALL,STOP_ALL};
CustRemoterWorkMode ubRIGHT_REAR[ACTION_NONE]={STOP_ALL,DEAD_ASTERN,DEAD_ASTERN,RIGHT_REAR, STOP_ALL,STOP_ALL,STOP_ALL,STOP_ALL};

AHC_BOOL AHC_PWM_ParamAdj(MMP_ULONG ulParam, MMP_ULONG *ulDuty, MMP_ULONG *ulMode, MMP_ULONG *ulAngle)
{	
	if(ulParam < 4){	//ACTION_MUP~ACTION_MRIGHT
		MMP_UBYTE	ubNextAction = ulParam;
		switch(g_ulMode){
			case STOP_ALL:
				*ulMode = ubSTOP_ALL[ubNextAction];
				if(*ulMode != STOP_ALL)
					g_ulDuty = DUTY_PERLEVEL_VAL;
				break;
			case DEAD_AHEAD:
				*ulMode = ubDEAD_AHEAD[ubNextAction];
				if(*ulMode == DEAD_ASTERN)
					g_ulDuty = DUTY_PERLEVEL_VAL;
				break;
			case FRONT_LEFT:
				*ulMode = ubFRONT_LEFT[ubNextAction];break;
			case FRONT_RIGHT:
				*ulMode = ubFRONT_RIGHT[ubNextAction];break;
			case DEAD_ASTERN:
				*ulMode = ubDEAD_ASTERN[ubNextAction];
				if(*ulMode == DEAD_AHEAD)
					g_ulDuty = DUTY_PERLEVEL_VAL;
				break;
			case LEFT_REAR:
				*ulMode = ubLEFT_REAR[ubNextAction];break;
			case RIGHT_REAR:
				*ulMode = ubRIGHT_REAR[ubNextAction];break;
			default:
				break;
		}
		g_ulMode = *ulMode;//backup
	}
	else{
		MOTOR_ACTION action = (MOTOR_ACTION)ulParam;
		switch(action){
	
			case ACTION_MRELEASE:
				*ulMode = RELEASE_WIRE;
				break;
			case ACTION_MCLIPS:
				*ulMode = CLIP_WIRE;
				break;
			case ACTION_MSPEEDUP:
				*ulMode = g_ulMode;
				g_ulDuty += (g_ulDuty<=(100-DUTY_PERLEVEL_VAL))?DUTY_PERLEVEL_VAL:0;//5level
				break;
			case ACTION_MSPEEDDOWN:
				*ulMode = g_ulMode;
				g_ulDuty -= (g_ulDuty>=DUTY_PERLEVEL_VAL)?DUTY_PERLEVEL_VAL:0;
				break;
			default:
				break;
		}
	}
	*ulDuty = g_ulDuty;

	return MMP_TRUE;
}

AHC_BOOL AHC_PWM_MotorCtrl(UINT32 ulEvent, UINT32 ulParam)
{
//#if defined(DEBUG_PWM_CTL_BY_APP)&&(DEBUG_PWM_CTL_BY_APP)
	
	MMP_ULONG	ulDuty;
	CustRemoterWorkMode	ulMode = PWM_ACTION_NONE;
	MMP_ULONG	ulAngle;
	
	UartSendTrace("%s:%d",__FUNCTION__,ulParam);
	MMPS_PWM_Initialize();

	AHC_PWM_ParamAdj(ulParam,&ulDuty,&ulMode,&ulAngle);	
	switch(ulMode){
		case DEAD_AHEAD:
			MOTOR1_FORWARD(ulDuty);
			MOTOR2_FORWARD(ulDuty);
			PwmUartSendTrace("DEAD_AHEAD\r\n");
			break;
		case FRONT_LEFT:
			MOTOR1_FORWARD(ulDuty);
			MOTOR2_STOP(ulDuty);
			PwmUartSendTrace("FRONT_LEFT\r\n");
			break;
		case FRONT_RIGHT:
			MOTOR1_STOP(ulDuty);
			MOTOR2_FORWARD(ulDuty);
			PwmUartSendTrace("FRONT_RIGHT\r\n");
			break;
		case DEAD_ASTERN:
			MOTOR1_REAR(ulDuty);
			MOTOR2_REAR(ulDuty);
			PwmUartSendTrace("DEAD_ASTERN\r\n");
			break;
		case LEFT_REAR:
			MOTOR1_STOP(ulDuty);
			MOTOR2_REAR(ulDuty);
			PwmUartSendTrace("LEFT_REAR\r\n");
			break;
		case RIGHT_REAR:
			MOTOR1_REAR(ulDuty);
			MOTOR2_STOP(ulDuty);
			PwmUartSendTrace("RIGHT_REAR\r\n");
			break;
		case STOP_ALL:
			MOTOR1_STOP(ulDuty);
			MOTOR2_STOP(ulDuty);
			PwmUartSendTrace("STOP_ALL\r\n");
			break;
		case STOP_MOT1:
			MOTOR1_STOP(ulDuty);
			break;
		case STOP_MOT2:
			MOTOR2_STOP(ulDuty);
			break;
		case FLAP_CAM2:
			GPIO_OUTPUT(LCD_D15_PWM7_DRV3_CAM2_FLAP_IO,MMP_FALSE);//LOW
			MMPS_PWM_SetOutputPin(LCD_D14_PWM6_PWMD3_CAM2_SPD,DRV_PWM_PAD_MODE3);
			MMPS_PWM_OutputPulse(LCD_D14_PWM6_PWMD3_CAM2_SPD,0,1000,ulDuty, MMP_TRUE, MMP_FALSE, NULL, 0);
			PwmUartSendTrace("FLAP_CAM2\r\n");
			break;
		case RELEASE_CAM2:
			GPIO_OUTPUT(LCD_D15_PWM7_DRV3_CAM2_FLAP_IO,MMP_TRUE);//HI
			MMPS_PWM_SetOutputPin(LCD_D14_PWM6_PWMD3_CAM2_SPD,DRV_PWM_PAD_MODE3);
			MMPS_PWM_OutputPulse(LCD_D14_PWM6_PWMD3_CAM2_SPD,0,1000,ulDuty, MMP_TRUE, MMP_FALSE, NULL, 0);
			PwmUartSendTrace("RELEASE_CAM2\r\n");
			break;

		case CLIP_WIRE:
			GPIO_OUTPUT(DRV_PM_PWM0_DRV4_WIRE_FLAP_IO,MMP_FALSE);//LOW
			GPIO_OUTPUT(DRV_PM_PWM2_DRV5_WIRE_REL_IO,MMP_TRUE);//HI
			PwmUartSendTrace("CLIP_WIRE\r\n");
			break;
		case RELEASE_WIRE:
			GPIO_OUTPUT(DRV_PM_PWM0_DRV4_WIRE_FLAP_IO,MMP_FALSE);//LOW
			GPIO_OUTPUT(DRV_PM_PWM2_DRV5_WIRE_REL_IO,MMP_TRUE);//HI
			PwmUartSendTrace("RELEASE_WIRE\r\n");
			break;
		case NET_LED_EN:
		default:
			PwmUartSendTrace("action none\r\n");
			//GPIO_OUTPUT(DRV_PM_PWM1_LED_EN_IO,(ulDuty? MMP_TRUE : MMP_FALSE));//LOW
			break;

	}
//#endif
	return MMP_TRUE;
}