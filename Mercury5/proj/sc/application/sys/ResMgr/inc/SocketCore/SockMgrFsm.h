#ifndef __SOCKMGR_FSM_H__
#define __SOCKMGR_FSM_H__

/*=============================================================*/
// Include Files
/*=============================================================*/

#include "SockMgrFsmItf.h"

/*=============================================================*/
// Macro Definitions
/*=============================================================*/

/*=============================================================*/
// Type Declarations
/*=============================================================*/

typedef struct _SockMgr_FSM_t_
{
	StateMachine_t sStateMachine;
	u16 uAcceptErrCode;
}SockMgr_FSM_t;

typedef enum
{
	SOCKMGR_FSM__REQ_E = 0,
	SOCKMGR_FSM__RSP_E,
	SOCKMGR_FSM__NUM_E,
}SockMgr_FSM_EventType_e;

typedef struct _SockMgr_FSM_Event_t_
{
	SockMgr_FSM_EventType_e eEventType;
	void *pvEvent;
}SockMgr_FSM_Event_t;

/*=============================================================*/
// Function Declarations
/*=============================================================*/


#endif/* __SOCKMGR_FSM_H__ */
