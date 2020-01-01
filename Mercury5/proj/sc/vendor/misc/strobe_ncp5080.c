//==============================================================================
//
//  File        : strobe_ncp5080.c
//  Description : 
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================
#if 0		 
void _____HEADER_____(){}
#endif


#include "mmpf_pio.h"
#include "mmpf_pwm.h"
#include "mmpf_timer.h"
#include "strobe_ncp5080.h"
#include "includes_fw.h"
#include "lib_retina.h"


#if 0		 
void _____VARIABLES_____(){}
#endif
//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

MMP_GPIO_PIN m_strobeChargeOn    = MMP_GPIO_MAX;
MMP_GPIO_PIN m_strobeChargeReady = MMP_GPIO_MAX;
MMPF_PWMPIN  m_strobeTrigger	 = MMP_PWM_PIN_MAX;
MMP_PWM_PAD_MODE  m_strobeTriggerPadMode = MMP_PWM_PAD_MODE_NOSUP;
MMP_BOOL	 m_bChargeOnStatus	 = MMP_FALSE;
MMP_BOOL	 m_bTriggerStatus	 = MMP_FALSE;

MMPF_TIMER_ID m_timerID			 = MMPF_TIMER_3;
MMP_BOOL	 m_bTurnOnTimer		 = MMP_FALSE;
MMP_BOOL	 m_bForceTimerClosed = MMP_FALSE;
MMP_ULONG	 m_ulHardwareTime	 = 0;//(ms)
//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
void STROBE_PWMISRCallBack_5080(MMP_ULONG ulStatus);
void STROBE_TimerISRCallBack_5080(void);

/**	@brief	initialize the parameter of strobe. */
MMP_ERR STROBE_Initialize_5080(	MMP_GPIO_PIN 	strobeChargeOn, 
								MMP_GPIO_PIN 	strobeChargeReady, 
								MMP_PWM_PIN		strobeTrigger,
								MMPF_TIMER_ID	timerID)
{

	m_strobeChargeOn	= strobeChargeOn;
	MMPF_PIO_EnableOutputMode(strobeChargeOn, MMP_TRUE, MMP_TRUE);
	
	m_strobeChargeReady = strobeChargeReady;
	MMPF_PIO_EnableOutputMode(strobeChargeReady, MMP_FALSE, MMP_TRUE);
	
	MMPF_I2C_PWM_Initialize();
	MMPF_PWM_Initialize();
	m_strobeTrigger		= strobeTrigger;
	MMPF_PWM_SetOutputPin(strobeTrigger, m_strobeTriggerPadMode);
	
	m_timerID = timerID;
	
	return MMP_ERR_NONE;

}

MMP_ERR STROBE_GetTimerStatus_5080(MMP_BOOL* bTimerStatus, MMP_ULONG* ulHardwareTime, TimerCallBackFunc* FuncPtr)
{

	*bTimerStatus   = m_bTurnOnTimer;
	*ulHardwareTime =  m_ulHardwareTime;
	FuncPtr         = STROBE_TimerISRCallBack_5080;
	return MMP_ERR_NONE;

}

MMP_ERR STROBE_ForceTimerClosed_5080(MMP_BOOL bForce)
{
	m_bForceTimerClosed = bForce;
	return MMP_ERR_NONE;
}
/**	@brief	ulBlankDuration(us), ulTriggerDuration(us)
*/
MMP_ERR STROBE_TriggerInitialization_5080(	MMP_ULONG	ulBlankDuration,
											MMP_ULONG	ulTriggerDuration)
{
	MMP_ULONG ulTempDuration;
	MMPF_PWM_ATTRIBUTE pwm_attribute = { MMPF_PWM_ID_1, MMPF_PWM_PULSE_ID_B, 0,0,0,0,0,0 };
	MMPF_PWM_SetAttribe(&pwm_attribute);///< clear the pulse B.
	m_bForceTimerClosed = MMP_FALSE;

	if(	ulTriggerDuration > PWM_MAX_TIME ){
		RTNA_DBG_Str(0, "PWM Limit 1... \r\n");
		return 1;//error
	}

	if( (ulBlankDuration + ulTriggerDuration) > PWM_MAX_TIME){
		/**	@brief the case to enable the hardware timer. */
		ulTempDuration = ulBlankDuration % 1000; ///< the time of hardware should be the unit of ms.
		
		//RTNA_DBG_Str(0, "STROBE_TriggerInitialization_5080\r\n");
		if( (ulTempDuration + ulTriggerDuration) > PWM_MAX_TIME){
			RTNA_DBG_Str(0, "PWM Limit 2... \r\n");
			return 1;//error
		}
		
		m_ulHardwareTime = ulBlankDuration - ulTempDuration;
		m_ulHardwareTime = m_ulHardwareTime/1000;
		ulBlankDuration	 = ulTempDuration;
		m_bTurnOnTimer	 = MMP_TRUE;
		
		//RTNA_DBG_PrintLong(0, ulBlankDuration);
		//RTNA_DBG_PrintLong(0, ulTempDuration);
		//RTNA_DBG_PrintLong(0, ulTriggerDuration);
		//RTNA_DBG_PrintLong(0, m_ulHardwareTime);
	}else{
		m_ulHardwareTime = 0;
		m_bTurnOnTimer	 = MMP_FALSE;
	}
	
	/**	@brief setup the pulse A. */
	pwm_attribute.uID			= MMPF_PWM_ID_1;
	pwm_attribute.uPulseID 		= MMPF_PWM_PULSE_ID_A;
	pwm_attribute.usClkDuty_T0	= ulBlankDuration * EXT_CLK_HZ;
	pwm_attribute.usClkDuty_T1	= pwm_attribute.usClkDuty_T0 + ulTriggerDuration * EXT_CLK_HZ;
	pwm_attribute.usClkDuty_T2	= pwm_attribute.usClkDuty_T1;
	pwm_attribute.usClkDuty_T3	= pwm_attribute.usClkDuty_T2;
	pwm_attribute.usClkDuty_Peroid = pwm_attribute.usClkDuty_T3;

	pwm_attribute.ubNumOfPulses = 0x01;
	MMPF_PWM_SetAttribe(&pwm_attribute);

	MMPF_PWM_EnableInterrupt(MMPF_PWM_ID_1, MMP_TRUE, &STROBE_PWMISRCallBack_5080, MMPF_PWM_INT_PulseA);
	return MMP_ERR_NONE;
}

MMP_ERR STROBE_EanbleCharge_5080(MMP_BOOL bEnable)
{
	if(bEnable){
		//RTNA_DBG_Str(0, "open charge... \r\n");
		m_bChargeOnStatus = MMP_TRUE;
		MMPF_PIO_SetData(m_strobeChargeOn, 0x1, MMP_FALSE);
	}else{
		//RTNA_DBG_Str(0, "close charge... \r\n");
		m_bChargeOnStatus = MMP_FALSE;
		MMPF_PIO_SetData(m_strobeChargeOn, 0x0, MMP_FALSE);
	}
	return MMP_ERR_NONE;
}

/**	@brief	check the status of charge ready. You must enable the pin of charge on,
			when you wanna check the pin of charge ready.
			TRUE	=> ready.
			FALSE	=> being charged. */
MMP_ERR STROBE_CheckChargeReady_5080(MMP_BOOL *bEnable)
{
	MMP_UBYTE ubReady;
	
	if(m_bChargeOnStatus){
		MMPF_PIO_GetData(m_strobeChargeReady, &ubReady);
	}else{
//		STROBE_EanbleCharge_5080(MMP_TRUE);
		MMPF_PIO_SetData(m_strobeChargeOn, 0x1, MMP_FALSE);
		MMPF_PIO_GetData(m_strobeChargeReady, &ubReady);
		MMPF_PIO_SetData(m_strobeChargeOn, 0x0, MMP_FALSE);
//		STROBE_EanbleCharge_5080(MMP_FALSE);
	}
	
	if(ubReady == 0){
		//RTNA_DBG_Str(0, "STROBE_CheckChargeReady_5080 true");
		*bEnable = MMP_TRUE;
	}else{
		//RTNA_DBG_Str(0, "STROBE_CheckChargeReady_5080 false");
		*bEnable = MMP_FALSE;
	}
		
	return MMP_ERR_NONE;
}

void STROBE_Trigger_5080(void)
{
	
	//RTNA_DBG_Str(0, "STROBE_Trigger_5080\r\n");
	m_bTriggerStatus = MMP_TRUE;
	STROBE_EanbleCharge_5080(MMP_TRUE);
	/**	@brief	two path: 
				path 1, use the hardware timer to wait part of flash time, 
				and use the interrupt of hardware timer to enable the trigger of flash.
				path 2, use the PWM to trigger.*/
	if(m_bTurnOnTimer){
		if(m_bForceTimerClosed == MMP_FALSE){
			MMPF_TIMER_ATTR TimerAttribute;			
			TimerAttribute.TimePrecision = MMPF_TIMER_MILLI_SEC;
			TimerAttribute.ulTimeUnits   = m_ulHardwareTime;
			TimerAttribute.Func          = STROBE_TimerISRCallBack_5080;
			TimerAttribute.bIntMode      = MMPF_TIMER_PERIODIC;
			MMPF_Timer_Start(m_timerID, &TimerAttribute);
			
    	}
	}else{
		MMPF_PWM_ImmediateControlSet(MMPF_PWM_ID_1, PWM_PULSE_A_FIRST|PWM_PULSE_A_NEG|PWM_ONE_ROUND|PWM_PULSE_B_POS|PWM_EN);
	}
}

void STROBE_PWMISRCallBack_5080(MMP_ULONG ulStatus)
{
	//RTNA_DBG_Str(0, "STROBE_PWMISRCallBack_5080 \r\n");
	STROBE_EanbleCharge_5080(MMP_FALSE);
	m_bTriggerStatus = MMP_FALSE;
}


void STROBE_TimerISRCallBack_5080(void)
{
	//RTNA_DBG_Str(0, "STROBE_TimerISR_5080\r\n");
	MMPF_PWM_ImmediateControlSet(MMPF_PWM_ID_1, PWM_PULSE_A_FIRST|PWM_PULSE_A_NEG|PWM_ONE_ROUND|PWM_PULSE_B_POS|PWM_EN);
	MMPF_Timer_Stop(m_timerID);
}