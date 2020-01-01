/**
 * @file    mmi_common_alivewidget.h
 * @brief   This file defines the enum and struct of alivewidget.

 */
 
#ifndef __MMI_COMMON_ALIVEWIDGET_H__
#define __MMI_COMMON_ALIVEWIDGET_H__

/*=============================================================*/
// include
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_wdg_abscontainer.h"
#include "mmi_clstbl.h"

/*=============================================================*/
// type and define
/*=============================================================*/
#define ALIVEWIDGET_SWITCH_BETWEEN_STATES_TIMER	4000


enum
{
	/* Singleton ID can only have one instance and the state and behavior of the instance can be passed from one view to another one via AliveWidget Service even views are belong to different AP. */
	AliveWidgetID_Singleton_Begin = (CLSID_ALIVEWDGSRV << 16 | 0), //0
	AliveWidgetID_Singleton_Dog,
	AliveWidgetID_Singleton_Clock,
	AliveWidgetID_Singleton_End,	

	/* NonSingleton ID can have more than one instance in a view but their state and behavior can't pass between different views. */
	AliveWidgetID_NonSingleton_Begin = (CLSID_ALIVEWDGSRV << 16 | 0x100), //0x100	
	AliveWidgetID_NonSingleton_Background,
	AliveWidgetID_NonSingleton_DogHouse,
	AliveWidgetID_NonSingleton_CountDown,
	AliveWidgetID_NonSingleton_End
	//AliveWidgetID_All
};
typedef u32 AliveWidgetID_e;

enum
{
	AliveWidget_State_Begin = 0,
	AliveWidget_State_Invisible,
	AliveWidget_State_Standby_Idle,
	AliveWidget_State_Standby_SitDown,
	AliveWidget_State_Standby_Sleep,	
	AliveWidget_State_Standby_BG_MediaPlayer,	
	AliveWidget_State_Standby_BG_FMRadio,	
	AliveWidget_State_Moving_Right,
	AliveWidget_State_Moving_Left,
	AliveWidget_State_Moving_Up,
	AliveWidget_State_Moving_Down,	
	AliveWidget_State_Touch_Click,
	AliveWidget_State_Touch_Move,
	AliveWidget_State_Touch_FallDown,
	AliveWidget_State_Event_IncomingCall,
	AliveWidget_State_Event_Message,
	AliveWidget_State_Event_MissedCall,
	AliveWidget_State_Event_LowBattery,
    AliveWidget_State_Event_Charging,
	AliveWidget_State_End
};
typedef u16 AliveWidget_State_e; 

enum
{
	AliveWidget_InputEvent_None = 0,
	/* Event from parent AP */
	AliveWidget_InputEvent_Property_Begin,
	AliveWidget_InputEvent_Property_End,
	/* Touch events */
	AliveWidget_InputEvent_Touch_Begin,
	AliveWidget_InputEvent_Touch_Click,
	AliveWidget_InputEvent_Touch_Move,
	AliveWidget_InputEvent_Touch_Release,	
	AliveWidget_InputEvent_Touch_ReleaseIn,
	AliveWidget_InputEvent_Touch_ReleaseOut,
	AliveWidget_InputEvent_Touch_MoveToTop,
	AliveWidget_InputEvent_Touch_End,
	/* Interaction events*/
	AliveWidget_InputEvent_Interaction_Begin,
	AliveWidget_InputEvent_Interaction_End,
	/* Moving events */
	AliveWidget_InputEvent_Moving_Begin,
	AliveWidget_InputEvent_Moving_OverBoundary_None,
	AliveWidget_InputEvent_Moving_OverBoundary_Down,
	AliveWidget_InputEvent_Moving_End,
	/* Timer events */
	AliveWidget_InputEvent_Timer_Begin,
	AliveWidget_InputEvent_Timer_ChangeState,
	AliveWidget_InputEvent_Timer_SwitchMissedEvent,
	AliveWidget_InputEvent_Timer_Moving,
	AliveWidget_InputEvent_Timer_End,
	/* AliveWidgetModel events */
	AliveWidget_InputEvent_Model_Begin,
	AliveWidget_InputEvent_Model_Visible,
	AliveWidget_InputEvent_Model_Invisible,
	AliveWidget_InputEvent_Model_IncomingCall,
	AliveWidget_InputEvent_Model_NewSMS,
	AliveWidget_InputEvent_Model_NewAlarm,
	AliveWidget_InputEvent_Model_MediaPlayer_BG,
	AliveWidget_InputEvent_Model_FMRadion_BG,
	AliveWidget_InputEvent_Model_MissedCall,
	AliveWidget_InputEvent_Model_MissedSMS,
	AliveWidget_InputEvent_Model_LowBattery,
    AliveWidget_InputEvent_Model_Charging,
	AliveWidget_InputEvent_Model_CountDownOn,
	AliveWidget_InputEvent_Model_CountDownOff,
	AliveWidget_InputEvent_Model_NewMMS,
	AliveWidget_InputEvent_Model_MissedMMS,
	AliveWidget_InputEvent_Model_End,
	/* AliveWidget notify events */
	AliveWidget_InputEvent_Notify_Begin,
	AliveWidget_InputEvent_Notify_LaunchCallLog,
	AliveWidget_InputEvent_Notify_LaunchSMSViewer,
	AliveWidget_InputEvent_Notify_LaunchSMSInbox,
	AliveWidget_InputEvent_Notify_LaunchMMSViewer,
	AliveWidget_InputEvent_Notify_LaunchMMSInbox,
	AliveWidget_InputEvent_Notify_LaunchEventCenter,
	AliveWidget_InputEvent_Notify_LaunchMediaPlayer,
	AliveWidget_InputEvent_Notify_LaunchFMRadio,
	AliveWidget_InputEvent_Notify_LaunchTime,
	AliveWidget_InputEvent_Notify_End,	
	AliveWidget_InputEvent_End
};
typedef u16 AliveWidget_InputEvent_e; 

enum
{
	AliveWidget_MovingDirection_None = 0,
	AliveWidget_MovingDirection_Right,
	AliveWidget_MovingDirection_Left,
	AliveWidget_MovingDirection_Up,
	AliveWidget_MovingDirection_Down,
	AliveWidget_MovingDirection_End
};
typedef u8 AliveWidget_MovingDirection_e; 

enum
{
	AliveWidget_Resource_TextType_None = 0,
	AliveWidget_Resource_TextType_FromTextID ,
	AliveWidget_Resource_TextType_MissedCallCount,
	AliveWidget_Resource_TextType_IncomingSMSCount,
	AliveWidget_Resource_TextType_ChargingBatteryID
};
typedef u8 AliveWidget_Resource_TextType_e; 

enum
{
	AliveWidget_Resource_VibrateType_None = 0,
	AliveWidget_Resource_VibrateType_Once,
	AliveWidget_Resource_VibrateType_End
};
typedef u8 AliveWidget_Resource_VibrateType_e; 

typedef struct
{
	u32 nImageID;	/* image */	
	AliveWidget_Resource_TextType_e eTextType;		/* text */
	u32 nTextID; 							//used when AliveWidget_Resource_TextType_FromTextID == eTextType.
} AliveWidget_Resource_t;

typedef struct
{
	u32 nMovingDistance;	//in pixel
	u32 nTimerForMoving;	//in millisecond
} AliveWidget_Moving_Speed_t;

typedef struct
{
	AliveWidget_MovingDirection_e eDirection;
	AliveWidget_Moving_Speed_t stSpeed;
} AliveWidget_Moving_t;

typedef struct
{
	AliveWidgetID_e eID;
	AliveWidget_State_e eState;
	AliveWidget_Resource_t stResource;
	AliveWidget_Moving_t stMoving;
	u32 nTimerForChangeState;	//in millisecond, when timer is expired, change state.
} AliveWidget_Behavior_t;

typedef struct
{
	AliveWidgetID_e eID;
	AliveWidget_State_e eState;
	WPos_t stAliveWidgetPos;
	WPos_t stImageWidgetPos;
	WPos_t stTexWidgetPos;
}AliveWidget_Init_State_Info_t;

enum
{
	/*  The lower level, the higher priority. AliveWidget_State_Priority_Level_0 is the highest priority. */
	AliveWidget_State_Priority_Level_0 = 0,
	AliveWidget_State_Priority_Level_1,
	AliveWidget_State_Priority_Level_2,
	AliveWidget_State_Priority_Level_3,	
	AliveWidget_State_Priority_Level_4,
	AliveWidget_State_Priority_Level_5,
	AliveWidget_State_Priority_Level_6,
	AliveWidget_State_Priority_Level_7,
	AliveWidget_State_Priority_Level_8,
	AliveWidget_State_Priority_Level_9, 
	AliveWidget_State_Priority_Level_Lowest = 0xFFFF
};
typedef u16 AliveWidget_State_Priority_Level_e;

enum
{
	AliveWidget_Priority_Compare_Result_CanNotCompare = 0,
	AliveWidget_Priority_Compare_Result_Lower,
	AliveWidget_Priority_Compare_Result_Equal,
	AliveWidget_Priority_Compare_Result_Higher
};
typedef u8 AliveWidget_Priority_Compare_Result_e;

typedef struct
{
	AliveWidget_State_e eState;
	AliveWidget_State_Priority_Level_e	ePriorityLevel;	//nPriorityLevel: The lower value, the higher priority. nPriorityLevel 0 is the highest priority.
}AliveWidget_State_Priority_t;

enum
{
	AliveWidget_Anim_State_Pause,
	AliveWidget_Anim_State_Play
};
typedef u8 AliveWidget_Anim_State_e;


/*=============================================================*/
// functions
/*=============================================================*/

#endif //__MMI_COMMON_ALIVEWIDGET_H__
/*=============================================================*/
// end of file
