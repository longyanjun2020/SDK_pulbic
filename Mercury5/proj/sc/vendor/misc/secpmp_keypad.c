//==============================================================================
//
//  File        : secpmp_keypad.c
//  Description : Keypad Control Interface
//  Author      : Ben Lu
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file secpmp_keypad.c
 *  @brief The keypad control functions
 *  @author Ben Lu
 *  @version 1.1
 */
 
 

#include "os_wrap.h"
#include "config_fw.h"
#include "mmpf_typedef.h"
#include "lib_retina.h"
#include "mmp_err.h"
#include "mmpf_pio.h"
#include "mmpf_timer.h"
#include "secpmp_keypad.h"
#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV2)
/** @addtogroup MMPF_KEYPAD
@{
*/

MMP_BOOL		gbKEYPAD_QUEUE_FULL;
MMP_ULONG       gbKeypadQueueReadIndex, gbKeypadQueueWriteIndex;
MMP_USHORT		KEYPAD_EVENT_QUEUE[SECPMP_KEYPAD_EVENT_QUEUE_SIZE];
MMP_UBYTE		m_gbKeypadCheck[SECPMP_KEYPAD_NUMBER];
static MMP_ULONG m_ulSecSenseTime;
static MMP_ULONG m_ulKeyFirstTime[SECPMP_KEYPAD_NUMBER];
static MMP_BOOL  m_bKeypadCounter[SECPMP_KEYPAD_NUMBER];

//------------------------------------------------------------------------------
//  Function    : SECPMP_KEYPAD_Initialize
//  Description :
//------------------------------------------------------------------------------
/** @brief The function Initialize the PIO pins of keypad

The function Initialize the PIO pins of keypad 
@return It reports the status of the operation.
*/
MMP_ERR SECPMP_KEYPAD_Initialize(void)
{
	#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV2)
	MMP_UBYTE i=0;
	#endif
	gbKeypadQueueReadIndex = 0;
	gbKeypadQueueWriteIndex = 0;
	gbKEYPAD_QUEUE_FULL = MMP_FALSE;
	
	MEMSET0(m_gbKeypadCheck);

	#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV2)
	for(i=0 ; i < (SECPMP_KEYPAD_NUMBER - 1); i++) {
		//Set GPIO as input mode
		MMPF_PIO_EnableOutputMode(MMP_GPIO67 + i, MMP_FALSE, MMP_TRUE);
		
		//Set Trigger Mode
		MMPF_PIO_EnableTrigMode(MMP_GPIO67 + i, GPIO_H2L_EDGE_TRIG, MMP_TRUE, MMP_TRUE);
		
		MMPF_PIO_EnableTrigMode(MMP_GPIO67 + i, GPIO_L2H_EDGE_TRIG, MMP_TRUE, MMP_TRUE);
		//Enable Interrupt
		MMPF_PIO_EnableInterrupt(MMP_GPIO67 + i, MMP_TRUE, 0, (GpioCallBackFunc *)SECPMP_KEYPAD_ISR, MMP_TRUE);
		
	}
	
	//Set GPIO as input mode
	MMPF_PIO_EnableOutputMode(MMP_GPIO35, MMP_FALSE, MMP_TRUE);
	
	//Power-key
	//Set Trigger Mode
	MMPF_PIO_EnableTrigMode(MMP_GPIO35, GPIO_H2L_EDGE_TRIG, MMP_TRUE, MMP_TRUE);
		
	MMPF_PIO_EnableTrigMode(MMP_GPIO35, GPIO_L2H_EDGE_TRIG, MMP_TRUE, MMP_TRUE);
	//Enable Interrupt
	MMPF_PIO_EnableInterrupt(MMP_GPIO35, MMP_TRUE, 0, (GpioCallBackFunc *)SECPMP_KEYPAD_ISR, MMP_TRUE);
	
	
	for(i=0 ; i < (SECPMP_KEYPAD_NUMBER); i++) {
		m_ulKeyFirstTime[i] = 0;
	}
	SECPMP_KEYPAD_SetSenseTime(100);
	#endif
	
	
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : SECPMP_KEYPAD_ReadFromQueue
//  Description :
//------------------------------------------------------------------------------
/** @brief The function is the API to get keypad event that user pressed before.

The function is the API to get keypad event that user pressed before.
@param[out] event pointer will feedback the oldest event in the evenet queue, about 
the event meaning, please reference the structure SECPMP_KEYPAD_EVENT
@return It reports the status of the operation.
*/
MMP_ERR SECPMP_KEYPAD_ReadFromQueue( MMP_USHORT *event)
{
	*event = 0;
	
	
	if(gbKEYPAD_QUEUE_FULL == MMP_TRUE) {   //for Event Queue Full, sent one special event back
		*event = SECPMP_KEYPAD_QUEUE_FULL;
		return MMP_ERR_NONE;
	}
	
	if(gbKeypadQueueReadIndex == gbKeypadQueueWriteIndex) { //for Evenet Queue Empty, the *event will be zero
		return MMP_ERR_NONE;
	}
	else{
		*event = KEYPAD_EVENT_QUEUE[gbKeypadQueueReadIndex];
	}
	
	gbKeypadQueueReadIndex++;
	if(gbKeypadQueueReadIndex == SECPMP_KEYPAD_EVENT_QUEUE_SIZE) {
		gbKeypadQueueReadIndex = 0;
	}
	
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : SECPMP_KEYPAD_InsertToQueue
//  Description :
//------------------------------------------------------------------------------
/** @brief The function is the API to insert keypad event into event queue.

The function is the API to insert keypad event into event queue.
@param[in] event pointer will be inserted into the evenet queue, about 
the event meaning, please reference the structure SECPMP_KEYPAD_EVENT
@return It reports the status of the operation.
*/

MMP_ERR SECPMP_KEYPAD_InsertToQueue(MMP_USHORT *event)
{
	
	if(((gbKeypadQueueWriteIndex+1)%SECPMP_KEYPAD_EVENT_QUEUE_SIZE) == gbKeypadQueueReadIndex) {
		gbKEYPAD_QUEUE_FULL = MMP_TRUE;
		return MMP_ERR_NONE;
	}
	KEYPAD_EVENT_QUEUE[gbKeypadQueueWriteIndex] = *event; 
	
	gbKeypadQueueWriteIndex++;
	if(gbKeypadQueueWriteIndex == SECPMP_KEYPAD_EVENT_QUEUE_SIZE) {
		gbKeypadQueueWriteIndex = 0;
	}
	return MMP_ERR_NONE;
}


/*static MMP_ERR SECPMP_KEYPAD_TimerIsrHandler(void* parameter1, void* ulParam)
{
	m_bKeypadGetIsr[(MMP_ULONG)ulParam] = MMP_FALSE;
	
	MMPF_Timer_EnableInterrupt(MMPF_TIMER_2, MMP_FALSE);
    MMPF_Timer_Close(MMPF_TIMER_2);
	return MMP_ERR_NONE;
}*/


//------------------------------------------------------------------------------
//  Function    : SECPMP_KEYPAD_SetSenseTime
//  Description :
//------------------------------------------------------------------------------
/** @brief The function set the time for keypad sensitive control.

The function set the time for keypad sensitive control.
@param[in] ulTime : The same keypad ISR during this ulTime will be ignore ! (unit: ms)
@return It reports the status of the operation.
*/
MMP_ERR SECPMP_KEYPAD_SetSenseTime(MMP_ULONG ulTime_ms)
{
	m_ulSecSenseTime = ulTime_ms;
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : SECPMP_KEYPAD_ISR
//  Description :
//------------------------------------------------------------------------------
/** @brief The function handle the ISR operations of keypad.

The function handle the ISR operations of keypad.
@param[in] about piopin ,please reference the structure MMP_GPIO_PIN
@return It reports the status of the operation.
*/
MMP_ERR  SECPMP_KEYPAD_ISR(MMP_GPIO_PIN piopin)
{
	#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV2)
	MMP_USHORT event = 0;
	MMP_UBYTE  tempValue = 0, arrayIndex = 0;
	//MMP_ULONG  ulOsTimerID = 0;
	MMP_ULONG  ulOsTime = 0;
	#endif
	
	
	//For SEC keypad Debouncing issue
	#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV2)
	if(piopin == MMP_GPIO35) {
		arrayIndex = (MMP_GPIO74 + 1) - MMP_GPIO67;
	}
	else if((piopin >= MMP_GPIO67) && (piopin <= MMP_GPIO74)) {
		arrayIndex = piopin - MMP_GPIO67;	
	}
	else {
		RTNA_DBG_Str(0, "Error keypad GPIO detect !\r\n");
	}
	
	
	MMPF_OS_GetTime(&ulOsTime);
	if (m_ulKeyFirstTime[arrayIndex] != 0) {
		m_bKeypadCounter[arrayIndex] ++;
		if ((ulOsTime > m_ulKeyFirstTime[arrayIndex]) && (m_bKeypadCounter[arrayIndex] > 2)) {   
			if((ulOsTime - m_ulKeyFirstTime[arrayIndex]) < m_ulSecSenseTime) {
				return MMP_ERR_NONE;
			}
			else {
				m_bKeypadCounter[arrayIndex] = 1;
				m_ulKeyFirstTime[arrayIndex] = ulOsTime;
			}
		}
		else if(ulOsTime < m_ulKeyFirstTime[arrayIndex]) {
			 m_ulKeyFirstTime[arrayIndex] = 0;
			 m_bKeypadCounter[arrayIndex] = 1;
			 return MMP_ERR_NONE;
		}
		else{
		
		}
	}
	else {
		m_ulKeyFirstTime[arrayIndex] = ulOsTime;
		m_bKeypadCounter[arrayIndex] ++;
	}
	#endif
	
	
	switch(piopin) {
		#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV2)
		case MMP_GPIO67:
		    tempValue = 0;
		    MMPF_PIO_GetData(MMP_GPIO67, &tempValue);
		    arrayIndex = MMP_GPIO67 - MMP_GPIO67;
			m_gbKeypadCheck[arrayIndex] = (m_gbKeypadCheck[arrayIndex] + 1)%2;
		    if(!tempValue) {
		    	if(m_gbKeypadCheck[arrayIndex] == 1) { //Release-event-loss detected
		    		RTNA_DBG_Str(0, "UP Press-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_UP_PRESS;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_UP_RELEASE;
			}
			else{
				if(m_gbKeypadCheck[arrayIndex] == 0) { //Press-event-loss detected
					RTNA_DBG_Str(0, "UP Release-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_UP_RELEASE;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_UP_PRESS;
			}
			
			//Double-Check before insert event
			MMPF_PIO_GetData(MMP_GPIO67, &tempValue);
			if(event == SECPMP_KEYPAD_UP_PRESS) {
				if(tempValue != 0x1) {
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
			}
			else {
				if(tempValue != 0x0) {
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
			}
			SECPMP_KEYPAD_InsertToQueue(&event);
			break;
		case MMP_GPIO68:
			tempValue = 0;
		    MMPF_PIO_GetData(MMP_GPIO68, &tempValue);
		    arrayIndex = MMP_GPIO68 - MMP_GPIO67;
			m_gbKeypadCheck[arrayIndex] = (m_gbKeypadCheck[arrayIndex] + 1)%2;
		    if(!tempValue) {
		    	if(m_gbKeypadCheck[arrayIndex] == 1) { //Release-event-loss detected
		    		RTNA_DBG_Str(0, "DW Press-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_DOWN_PRESS;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_DOWN_RELEASE;
			}
			else{
				if(m_gbKeypadCheck[arrayIndex] == 0) { //Press-event-loss detected
					RTNA_DBG_Str(0, "DW Release-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_DOWN_RELEASE;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_DOWN_PRESS;
			}
			
			//Double-Check before insert event
			MMPF_PIO_GetData(MMP_GPIO68, &tempValue);
			if(event == SECPMP_KEYPAD_DOWN_PRESS) {
				if(tempValue != 0x1) {
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
			}
			else {
				if(tempValue != 0x0) {
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
			}
			SECPMP_KEYPAD_InsertToQueue(&event);
			break;
		case MMP_GPIO69:
			tempValue = 0;
		    MMPF_PIO_GetData(MMP_GPIO69, &tempValue);
		    arrayIndex = MMP_GPIO69 - MMP_GPIO67;
			m_gbKeypadCheck[arrayIndex] = (m_gbKeypadCheck[arrayIndex] + 1)%2;
		    if(!tempValue) {
		    	if(m_gbKeypadCheck[arrayIndex] == 1) { //Release-event-loss detected
		    		RTNA_DBG_Str(0, "Press-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_ENTER_PRESS;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_ENTER_RELEASE;
			}
			else{
				if(m_gbKeypadCheck[arrayIndex] == 0) { //Press-event-loss detected
					RTNA_DBG_Str(0, "Release-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_ENTER_RELEASE;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_ENTER_PRESS;
			}
			
			//Double-Check before insert event
			MMPF_PIO_GetData(MMP_GPIO69, &tempValue);
			if(event == SECPMP_KEYPAD_ENTER_PRESS) {
				if(tempValue != 0x1) {
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
			}
			else {
				if(tempValue != 0x0) {
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
			}
			
			SECPMP_KEYPAD_InsertToQueue(&event);
			break;
		case MMP_GPIO70:
			tempValue = 0;
		    MMPF_PIO_GetData(MMP_GPIO70, &tempValue);
		    arrayIndex = MMP_GPIO70 - MMP_GPIO67;
			m_gbKeypadCheck[arrayIndex] = (m_gbKeypadCheck[arrayIndex] + 1)%2;
		    if(!tempValue) {
		    	if(m_gbKeypadCheck[arrayIndex] == 1) { //Release-event-loss detected
		    		RTNA_DBG_Str(0, "Press-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_LEFT_PRESS;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_LEFT_RELEASE;
			}
			else{
				if(m_gbKeypadCheck[arrayIndex] == 0) { //Press-event-loss detected
					RTNA_DBG_Str(0, "Release-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_LEFT_RELEASE;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_LEFT_PRESS;
			}
			
			
			//Double-Check before insert event
			MMPF_PIO_GetData(MMP_GPIO70, &tempValue);
			if(event == SECPMP_KEYPAD_LEFT_PRESS) {
				if(tempValue != 0x1) {
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
			}
			else {
				if(tempValue != 0x0) {
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
			}
			SECPMP_KEYPAD_InsertToQueue(&event);
			break;
		case MMP_GPIO71:
			tempValue = 0;
		    MMPF_PIO_GetData(MMP_GPIO71, &tempValue);
		    arrayIndex = MMP_GPIO71 - MMP_GPIO67;
			m_gbKeypadCheck[arrayIndex] = (m_gbKeypadCheck[arrayIndex] + 1)%2;
		    if(!tempValue) {
		    	if(m_gbKeypadCheck[arrayIndex] == 1) { //Release-event-loss detected
		    		RTNA_DBG_Str(0, "Press-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_RIGHT_PRESS;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_RIGHT_RELEASE;
			}
			else{
				if(m_gbKeypadCheck[arrayIndex] == 0) { //Press-event-loss detected
					RTNA_DBG_Str(0, "Release-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_RIGHT_RELEASE;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_RIGHT_PRESS;
			}
			
			//Double-Check before insert event
			MMPF_PIO_GetData(MMP_GPIO71, &tempValue);
			if(event == SECPMP_KEYPAD_RIGHT_PRESS) {
				if(tempValue != 0x1) {
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
			}
			else {
				if(tempValue != 0x0) {
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
			}
			SECPMP_KEYPAD_InsertToQueue(&event);
			break;
		case MMP_GPIO72:
			tempValue = 0;
		    MMPF_PIO_GetData(MMP_GPIO72, &tempValue);
		    arrayIndex = MMP_GPIO72 - MMP_GPIO67;
			m_gbKeypadCheck[arrayIndex] = (m_gbKeypadCheck[arrayIndex] + 1)%2;
		    if(!tempValue) {   
		    	if(m_gbKeypadCheck[arrayIndex] == 1) { //Release-event-loss detected
		    		RTNA_DBG_Str(0, "Press-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_BACK_PRESS;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_BACK_RELEASE;
			}
			else{
				if(m_gbKeypadCheck[arrayIndex] == 0) { //Press-event-loss detected
					RTNA_DBG_Str(0, "Release-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_BACK_RELEASE;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_BACK_PRESS;
			}
			
			//Double-Check before insert event
			MMPF_PIO_GetData(MMP_GPIO72, &tempValue);
			if(event == SECPMP_KEYPAD_BACK_PRESS) {
				if(tempValue != 0x1) {
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
			}
			else {
				if(tempValue != 0x0) {
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
			}
			
			SECPMP_KEYPAD_InsertToQueue(&event);
			break;
		case MMP_GPIO73:
			tempValue = 0;
		    MMPF_PIO_GetData(MMP_GPIO73, &tempValue);
		    arrayIndex = MMP_GPIO73 - MMP_GPIO67;
			m_gbKeypadCheck[arrayIndex] = (m_gbKeypadCheck[arrayIndex] + 1)%2;
		    if(!tempValue) {
		    	if(m_gbKeypadCheck[arrayIndex] == 1) { //Release-event-loss detected
		    		RTNA_DBG_Str(0, "Press-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_USER_PRESS;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_USER_RELEASE;
			}
			else{
				if(m_gbKeypadCheck[arrayIndex] == 0) { //Press-event-loss detected
					RTNA_DBG_Str(0, "Release-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_USER_RELEASE;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_USER_PRESS;
			}
			
			//Double-Check before insert event
			MMPF_PIO_GetData(MMP_GPIO73, &tempValue);
			if(event == SECPMP_KEYPAD_USER_PRESS) {
				if(tempValue != 0x1) {
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
			}
			else {
				if(tempValue != 0x0) {
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
			}
			SECPMP_KEYPAD_InsertToQueue(&event);
			break;
		case MMP_GPIO74:
			tempValue = 0;
		    MMPF_PIO_GetData(MMP_GPIO74, &tempValue);
		    arrayIndex = MMP_GPIO74 - MMP_GPIO67;
			m_gbKeypadCheck[arrayIndex] = (m_gbKeypadCheck[arrayIndex] + 1)%2;
		    if(!tempValue) {
		    	if(m_gbKeypadCheck[arrayIndex] == 1) { //Release-event-loss detected
		    		RTNA_DBG_Str(0, "Press-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_MENU_PRESS;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_MENU_RELEASE;
			}
			else{
				if(m_gbKeypadCheck[arrayIndex] == 0) { //Press-event-loss detected
					RTNA_DBG_Str(0, "Release-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_MENU_RELEASE;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_MENU_PRESS;
			}
			
			//Double-Check before insert event
			MMPF_PIO_GetData(MMP_GPIO74, &tempValue);
			if(event == SECPMP_KEYPAD_MENU_PRESS) {
				if(tempValue != 0x1) {
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
			}
			else {
				if(tempValue != 0x0) {
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
			}
			SECPMP_KEYPAD_InsertToQueue(&event);
			break;
		case MMP_GPIO35:
			tempValue = 0;
		    MMPF_PIO_GetData(MMP_GPIO35, &tempValue);
		    arrayIndex = (MMP_GPIO74 + 1) - MMP_GPIO67;
			m_gbKeypadCheck[arrayIndex] = (m_gbKeypadCheck[arrayIndex] + 1)%2;
		    if(!tempValue) {
		    	if(m_gbKeypadCheck[arrayIndex] == 1) { //Release-event-loss detected
		    		RTNA_DBG_Str(0, "Release-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_POWER_PRESS;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_POWER_RELEASE;
			}
			else{
				if(m_gbKeypadCheck[arrayIndex] == 0) { //Press-event-loss detected
					RTNA_DBG_Str(0, "Press-Event-Loss Detected\r\n");
					//event = SECPMP_KEYPAD_POWER_RELEASE;
					//SECPMP_KEYPAD_InsertToQueue(&event);
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
				event = SECPMP_KEYPAD_POWER_PRESS;
			}
			
			//Double-Check before insert event
			MMPF_PIO_GetData(MMP_GPIO35, &tempValue);
			if(event == SECPMP_KEYPAD_POWER_PRESS) {
				if(tempValue != 0x1) {
					m_gbKeypadCheck[arrayIndex] = 0;
					return MMP_ERR_NONE;
				}
			}
			else {
				if(tempValue != 0x0) {
					m_gbKeypadCheck[arrayIndex] = 1;
					return MMP_ERR_NONE;
				}
			}
			SECPMP_KEYPAD_InsertToQueue(&event);
			break;
		#endif
		default:
			RTNA_DBG_Str(0, "Error !! Unknown keypad\r\n");
			break;
		}
	return MMP_ERR_NONE;
}

#endif