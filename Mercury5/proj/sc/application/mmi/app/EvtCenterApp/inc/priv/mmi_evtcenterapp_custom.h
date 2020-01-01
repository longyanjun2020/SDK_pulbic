/**
 * @file mmi_evtcenterapp_custom.h
 *
 * @version $Id$
 */
#ifndef __MMI_EVTCENTERAPP_CUSTOM_H__
#define __MMI_EVTCENTERAPP_CUSTOM_H__

//<<Customize data begin>>
#define EVTCENTERAPP_TRANSITION_TIMER 200
typedef enum
{
	EvtCenterApp_Transition_Level_Start = 0,
	EvtCenterApp_Transition_Level_1, 
	EvtCenterApp_Transition_Level_2,
	EvtCenterApp_Transition_Level_3,
	EvtCenterApp_Transition_Level_4,
	EvtCenterApp_Transition_Level_5,
	EvtCenterApp_Transition_Level_6,
	EvtCenterApp_Transition_Level_End = EvtCenterApp_Transition_Level_2	//define transition levels
}EvtCenterApp_Transition_Level_e;

//<<Customize data end>>

#endif /* __MMI_EVTCENTERAPP_CUSTOM_H__ */
