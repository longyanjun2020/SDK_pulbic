//------------------------------------------------------------------------------
//
//  File        : remote_ctl_cansonic89.h
//  Description : 
//  Author      : scofield
//  Revision    : 1.0
//
//------------------------------------------------------------------------------
/**

NEC protocol

----------------
|    |    | 00 |
----------------
| 09 | 05 | 01 |
----------------
| 10 | 06 | 02 |
----------------
| 11 | 07 | 03 |
----------------
| 12 | 08 | 04 |
----------------

key 00 : 0x41F67887

key 01 : 0x41F6C03F
key 02 : 0x41F6609F
key 03 : 0x41F6906F
key 04 : 0x41F6F807

key 05 : 0x41F640BF
key 06 : 0x41F6A05F
key 07 : 0x41F610EF
key 08 : 0x41F6D827

key 09 : 0x41F6807F
key 10 : 0x41F620DF
key 11 : 0x41F6E01F
key 12 : 0x41F650AF

*/

#if 0		 
void _____HEADER_____(){}
#endif

#include "remote_ctl_cansonic89.h"

#if 0		 
void _____VARIABLES_____(){}
#endif

#if (RMT_CTL_TYPE == RMT_CTL_CANSONIC_89)
//------------------------------------------------------------------------------
//
//                              VARIABLES
//
//------------------------------------------------------------------------------

/**	
	 _ _
	|   |
   _     _ _

new signal : AGC(high) + space(low) = 9 + 4.5 = 13.5(ms)

data : 

logical 1 : 5xx + 1.6xx = 2.1xx (ms)

logical 0 : 5xx + 5xx = 10xx ~ 12xx(us)
repeated signal : AGC(high) + space(low) = 9 + 2.25 = 11.25(ms)
*/

RMT_CTL_TIME	m_RmtctlInterval;
MMPF_TIMER_ID	m_RmtctlTimer = MMPF_TIMER_3;

MMP_ULONG	m_ulKeyData[MAX_NUMBER_COMMAND] = {

			0x41F67887,	
			0,
			0x41F6C03F,
			0x41F6807F,
			0x41F650AF,
			
			0x41F6F807,
			0x41F610EF,
			0x41F6609F,
			0x41F620DF,
			0x41F6906F,
			
			0x41F6E01F,
			0x41F6A05F,
			0x41F6D827,
			0x41F640BF,
			0 };

MMP_ULONG	m_ulCurTime		= 0;
MMP_ULONG	m_ulLastTime	= 0;

MMP_ULONG	m_ulDataStream	= 0;
MMP_ULONG	m_ulCmdIndex	= 0;

MMP_USHORT	m_usBitOffset	= 31;

MMP_BOOL	m_bDataInterval			= MMP_FALSE;
MMP_BOOL	m_bStartReleaseTimer	= MMP_FALSE;
MMP_BOOL	m_bRepeatedSignal		= MMP_FALSE;


static RmtCtlCallBackFunc* PraseCmdBackFunc = NULL;

void RMT_CTL_CheckInterval_89(MMP_ULONG ulTimeInterval, MMP_ULONG ulPreviousTimeInterval);
void RMT_CTL_ParseCommand_89(MMP_ULONG ulDataStream);
void RMT_CTL_ResetStatus_89(void);

void RMT_CTL_TimerHandler_89(void);
void RMT_CTL_TimerOpen_89(void);
void RMT_CTL_TimerClose_89(void);

//------------------------------------------------------------------------------
//  Function    : RMT_CTL_ISR
//  Description : 
//------------------------------------------------------------------------------
void RMT_CTL_ISR_89(void)
{
	MMP_ULONG ulGetTime;
	MMP_ULONG ulTimeInterval;
	MMP_ULONG ulPreviousInterval;
	
	//MMPF_SYS_GetTimerCount(&ulGetTime);
    MMPF_OS_GetTime(&ulGetTime);
	ulTimeInterval	= ulGetTime - m_ulCurTime;
	ulPreviousInterval = ulGetTime - m_ulLastTime;
	
	if((ulGetTime >= m_ulCurTime) && (ulGetTime >= m_ulLastTime)){
		RMT_CTL_CheckInterval_89(ulTimeInterval, ulPreviousInterval);
	}
	
	m_ulLastTime	= m_ulCurTime;
	m_ulCurTime		= ulGetTime;
	
}

//------------------------------------------------------------------------------
//  Function    : RMT_CTL_Initalize_89
//  Description : 
//------------------------------------------------------------------------------

void RMT_CTL_Initalize_89( MMP_GPIO_PIN piopin, MMPF_TIMER_ID timerID, RmtCtlCallBackFunc* callBackFunc )
{

	m_RmtctlTimer		= timerID;
	PraseCmdBackFunc	= callBackFunc;
	
	m_ulCurTime			= 0;
	m_ulLastTime		= 0;

	m_ulDataStream		= 0;
	m_ulCmdIndex		= 0;

	m_usBitOffset		= 31;

	m_bDataInterval		= MMP_FALSE;

    //Set GPIO as input mode
    MMPF_PIO_EnableOutputMode(piopin, MMP_FALSE, MMP_TRUE);

    // Set the trigger mode.
    MMPF_PIO_EnableTrigMode(piopin, GPIO_H2L_EDGE_TRIG, MMP_TRUE, MMP_TRUE);
    
    //Enable Interrupt
    MMPF_PIO_EnableInterrupt(piopin, MMP_TRUE, 0, (GpioCallBackFunc *)RMT_CTL_ISR_89, MMP_TRUE);

}

//------------------------------------------------------------------------------
//  Function    : RMT_CTL_CheckInterval_89
//  Description : 
//------------------------------------------------------------------------------

void RMT_CTL_CheckInterval_89(MMP_ULONG ulTimeInterval, MMP_ULONG ulPreviousTimeInterval)
{

	if( (ulTimeInterval < (m_RmtctlInterval.ulPreemptiveSig + m_RmtctlInterval.ulSigTolerance)) &&
		(ulTimeInterval > (m_RmtctlInterval.ulPreemptiveSig - m_RmtctlInterval.ulSigTolerance)) ){
		
		RMT_CTL_ResetStatus_89();
		
	}else if(	(ulTimeInterval < (m_RmtctlInterval.ulLogical0Sig + m_RmtctlInterval.ulSigTolerance)) &&
				(ulTimeInterval > (m_RmtctlInterval.ulLogical0Sig - m_RmtctlInterval.ulSigTolerance)) ){
				
		if(m_bDataInterval){
		
			m_ulDataStream |= (0 << m_usBitOffset);
			
			if(m_usBitOffset == 0){
				RMT_CTL_ParseCommand_89(m_ulDataStream);
				m_bDataInterval 	= MMP_FALSE;
				m_bRepeatedSignal = MMP_TRUE;
				
			}else if( m_usBitOffset > 31 ){
				RTNA_DBG_Str(0, "RMT_CTL_CheckInterval_89 signal error 0... \r\n");
			
			}else{
				m_usBitOffset--;
			}
		}
		
	}else if (	(ulTimeInterval < (m_RmtctlInterval.ulLogical1Sig + m_RmtctlInterval.ulSigTolerance)) &&
				(ulTimeInterval > (m_RmtctlInterval.ulLogical1Sig - m_RmtctlInterval.ulSigTolerance)) ){
				
		if(m_bDataInterval){
			m_ulDataStream |= (1 << m_usBitOffset);
			
			if(m_usBitOffset == 0){
				RMT_CTL_ParseCommand_89(m_ulDataStream);
				m_bDataInterval		= MMP_FALSE;
				m_bRepeatedSignal	= MMP_TRUE;
			}else if( m_usBitOffset > 31 ){
				RTNA_DBG_Str(0, "RMT_CTL_CheckInterval_89 signal error 1... \r\n");
			
			}else{
				m_usBitOffset--;
			}
		}
	}else if (	(ulTimeInterval < (m_RmtctlInterval.ulRepeatedSig + m_RmtctlInterval.ulSigTolerance)) &&
				(ulTimeInterval > (m_RmtctlInterval.ulRepeatedSig - m_RmtctlInterval.ulSigTolerance)) ){
		
		if(ulPreviousTimeInterval > (m_RmtctlInterval.ulRepeatedInterval + m_RmtctlInterval.ulRepeatedIntervalTolerance)){

		 	RTNA_DBG_Str(0, "rmtctl signal skip\r\n");
			m_bRepeatedSignal = MMP_FALSE;
//			m_ulDataStream = 0;
		}else if( (m_ulDataStream != 0) && (m_bRepeatedSignal == MMP_TRUE) ){
			
			RMT_CTL_ParseCommand_89(m_ulDataStream);
			
		}else
			RTNA_DBG_Str(0, "rmtctl signal error\r\n");
	}
}

//------------------------------------------------------------------------------
//  Function    : RMT_CTL_InitailizeInterval_89
//  Description : 
//------------------------------------------------------------------------------
void RMT_CTL_InitailizeInterval_89(RMT_CTL_TIME *timeInterval)
{
	m_RmtctlInterval = *timeInterval;

}
 
//------------------------------------------------------------------------------
//  Function    : RMT_CTL_ParseCommand_89
//  Description : 
//------------------------------------------------------------------------------
void RMT_CTL_ParseCommand_89(MMP_ULONG ulDataStream)
{
	MMP_ULONG ulIndex;
	
	for(ulIndex = 0 ; ulIndex < MAX_NUMBER_COMMAND ; ulIndex++){
		/**	@brief	seek the command. */
		if(ulDataStream == m_ulKeyData[ulIndex]){

			m_ulCmdIndex = ulIndex;
			
			if(PraseCmdBackFunc)(*PraseCmdBackFunc)(ulIndex);
			
			if(m_bStartReleaseTimer == MMP_FALSE){
				m_bStartReleaseTimer = MMP_TRUE;
				RMT_CTL_TimerOpen_89();
			}else{
				RMT_CTL_TimerClose_89();
				RMT_CTL_TimerOpen_89();
			}
			break;
			
		}
	}
}

//------------------------------------------------------------------------------
//  Function    : RMT_CTL_ResetStatus_89
//  Description : 
//------------------------------------------------------------------------------
void RMT_CTL_ResetStatus_89(void)
{
	m_ulDataStream	= 0x0000;
	m_usBitOffset	= 31;
	m_bDataInterval = MMP_TRUE;
	m_bRepeatedSignal = MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : RMT_CTL_TimerHandler_89
//  Description : 
//------------------------------------------------------------------------------
/**	@brief	the API for releasing key. */
void RMT_CTL_TimerHandler_89(void)
{
	if(PraseCmdBackFunc)(*PraseCmdBackFunc)(m_ulCmdIndex + COMMAND_RELEASE_OFFSET);
	
	RMT_CTL_TimerClose_89();
	m_bStartReleaseTimer = MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : RMT_CTL_TimerOpen_89
//  Description : 
//------------------------------------------------------------------------------

void RMT_CTL_TimerOpen_89(void)
{
	MMP_ULONG ulInterval;
	MMPF_TIMER_ATTR TimerAttribute;
	ulInterval = (m_RmtctlInterval.ulRepeatedInterval + m_RmtctlInterval.ulRepeatedIntervalTolerance)/1000;
	
	TimerAttribute.TimePrecision = MMPF_TIMER_MILLI_SEC;
	TimerAttribute.ulTimeUnits   = ulInterval;
	TimerAttribute.Func          = RMT_CTL_TimerHandler_89;
	TimerAttribute.bIntMode      = MMPF_TIMER_PERIODIC;
	MMPF_Timer_Start(m_RmtctlTimer, &TimerAttribute);
}

//------------------------------------------------------------------------------
//  Function    : RMT_CTL_TimerClose_89
//  Description : 
//------------------------------------------------------------------------------
void RMT_CTL_TimerClose_89(void)
{
    MMPF_Timer_Stop(m_RmtctlTimer);
}

#endif //< #if (RMT_CTL_TYPE == RMT_CTL_CANSONIC_89)

