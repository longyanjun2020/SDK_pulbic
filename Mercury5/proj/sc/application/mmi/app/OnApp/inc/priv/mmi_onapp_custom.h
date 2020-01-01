/**
 * @file mmi_onapp_custom.h
 *
 * @version $Id: 
 */
#ifndef __MMI_ONAPP_CUSTOM_H__
#define __MMI_ONAPP_CUSTOM_H__

//<<Customize data begin>>
#ifdef _MSIM_	//For PC simulator
#define ONAPP_POWERON_ANIM_TIMER_ONE_SIM 3200	
#define ONAPP_POWERON_ANIM_TIMER_TWO_SIM 3200
#define ONAPP_NETWORK_ANIM_TIMER 800	 
#define ONAPP_STANDBY_MODE_TIMER 5000
#else	//For target
#define ONAPP_POWERON_ANIM_TIMER_ONE_SIM 8000
#define ONAPP_POWERON_ANIM_TIMER_TWO_SIM 8000	
#define ONAPP_NETWORK_ANIM_TIMER 1000
#define ONAPP_STANDBY_MODE_TIMER 5000
#endif
//<<Customize data end>>

#endif /* __MMI_ONAPP_CUSTOM_H__ */
