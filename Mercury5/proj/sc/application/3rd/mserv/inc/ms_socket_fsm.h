/**
* @file socketFsm.h
*
* This header file defines the interfaces of socket states
*
*/

#ifndef __MS_SOCKET_FSM_H__
#define __MS_SOCKET_FSM_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

typedef void *SocketFSMHdl_t;

/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum
{
	SOCKET_STATE_IDLE = 0,
	SOCKET_STATE_CONNECTING,
	SOCKET_STATE_CONNECTED,
	SOCKET_STATE_SENDING,
	SOCKET_STATE_DISCONNECTING,
	SOCKET_STATE_MMS,
	SOCKET_TOTAL_STATE_NO
}SocketStates_e;

typedef enum
{
	SOCKET_NOERR,
	SOCKET_CON_RETRY, //socket connection retry
	SOCKET_CON_FAIL,
}SocketErrorCode_e;

/*=============================================================*/
// Function Declarations
/*=============================================================*/
SocketFSMHdl_t SocketFSM_Init(void *pCusData);
void SocketFSM_Uninit(SocketFSMHdl_t pHandle);

#endif //__MS_SOCKET_FSM_H__

