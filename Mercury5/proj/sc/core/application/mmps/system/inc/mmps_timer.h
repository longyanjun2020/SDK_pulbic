//==============================================================================
//
//  File        : mmps_timer.h
//  Description : INCLUDE File for the system timer
//  Author      : Ben Lu
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmps_timer.h
 *  @brief Header File for the system timer.
 *  @author Ben Lu
 *  @version 1.0
 */

#ifndef _MMPS_TIMER_H_
#define _MMPS_TIMER_H_

//==============================================================================
//
//                              COMPILER OPTION
//
//==============================================================================


//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================
typedef enum _MMPS_TIMER_ID
{
	MMPS_TIMER_0 =0,
	MMPS_TIMER_1,
	MMPS_TIMER_2,
	MMPS_TIMER_3,
	MMPS_TIMER_4,
	MMPS_TIMER_5
} MMPS_TIMER_ID;

typedef enum _MMPS_TIMER_CMD {
	MMPS_TIMER_CMD_START = 0,
	MMPS_TIMER_CMD_START_ONESHOT,
	MMPS_TIMER_CMD_MAX	
} MMPS_TIMER_CMD;

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
//MMP_ERR MMPS_Timer_SetTimer(void* bTimerID, MMPS_TIMER_CMD bTimerCMD, MMP_USHORT usTime, void* pTimerIsrHandler, void* pMessage);

#endif // _MMPS_TIMER_H_