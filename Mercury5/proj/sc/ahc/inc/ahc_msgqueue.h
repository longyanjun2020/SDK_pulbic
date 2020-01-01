//==============================================================================
//
//  File        : ahc_msgqueue.h
//  Description : INCLUDE File for the AHC message queue function.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_MSGQUEUE_H_
#define _AHC_MSGQUEUE_H_

/*===========================================================================
 * Include files
 *===========================================================================*/
 
#include "ahc_common.h"

/*===========================================================================
 * Structure define
 *===========================================================================*/ 

typedef struct _AHC_QUEUE_MESSAGE 
{
	UINT32 ulMsgID; 
	UINT32 ulParam1;
	UINT32 ulParam2;
} AHC_QUEUE_MESSAGE;

/*===========================================================================
 * Enum define
 *===========================================================================*/

/*===========================================================================
 * Function Prototype
 *===========================================================================*/
AHC_BOOL 	AIHC_InitMsgQueue(void);
AHC_BOOL    AHC_SendAHLMessageEnable(AHC_BOOL Enable);
AHC_BOOL 	AHC_SendAHLMessage(UINT32 ulMsgID, UINT32 ulParam1, UINT32 ulParam2);
AHC_BOOL 	AHC_SendAHLMessage_HP(UINT32 ulMsgID, UINT32 ulParam1, UINT32 ulParam2);
AHC_BOOL 	AHC_GetAHLMessage(UINT32* ulMsgID, UINT32* ulParam1, UINT32* ulParam2);
AHC_BOOL 	AHC_GetAHLMessage_HP(UINT32* ulMsgID, UINT32* ulParam1, UINT32* ulParam2);
void 		AHC_GetAHLMessageCount(UINT16 *usCount);
void 		AHC_GetAHLMessageCount_HP(UINT16 *usCount);
AHC_BOOL 	AIHC_InitAHLMessage(void);
AHC_BOOL 	AIHC_InitAHLMessage_HP(void);
#endif