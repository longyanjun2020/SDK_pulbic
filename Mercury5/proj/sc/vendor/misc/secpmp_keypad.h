#ifndef _SECPMP_KEYPAD_H_
#define _SECPMP_KEYPAD_H_
#include "config_fw.h"
#include "os_wrap.h"
#include "mmpf_pio.h"
//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

#define KEYPAD_SEM_TIMEOUT 100
#define SECPMP_KEYPAD_EVENT_QUEUE_SIZE        	64

#define SECPMP_KEYPAD_NUMBER						 9
//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef enum _SECPMP_KEYPAD_EVENT {
	SECPMP_KEYPAD_NONE,

	#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV2)
	SECPMP_KEYPAD_UP_PRESS,				//SECPMP_KEYPAD_REG_GPIO67
	SECPMP_KEYPAD_DOWN_PRESS,			//SECPMP_KEYPAD_REG_GPIO68
	SECPMP_KEYPAD_ENTER_PRESS,			//SECPMP_KEYPAD_REG_GPIO69
	SECPMP_KEYPAD_LEFT_PRESS,   		//SECPMP_KEYPAD_REG_GPIO70
	SECPMP_KEYPAD_RIGHT_PRESS,			//SECPMP_KEYPAD_REG_GPIO71
	SECPMP_KEYPAD_BACK_PRESS,			//SECPMP_KEYPAD_REG_GPIO72
	SECPMP_KEYPAD_USER_PRESS,			//SECPMP_KEYPAD_REG_GPIO73
	SECPMP_KEYPAD_MENU_PRESS,			//SECPMP_KEYPAD_REG_GPIO74
	SECPMP_KEYPAD_POWER_PRESS,			//SECPMP_KEYPAD_REG_GPIO35
	
	SECPMP_KEYPAD_UP_RELEASE,			//SECPMP_KEYPAD_REG_GPIO67
	SECPMP_KEYPAD_DOWN_RELEASE,			//SECPMP_KEYPAD_REG_GPIO68
	SECPMP_KEYPAD_ENTER_RELEASE,		//SECPMP_KEYPAD_REG_GPIO69
	SECPMP_KEYPAD_LEFT_RELEASE,   		//SECPMP_KEYPAD_REG_GPIO70
	SECPMP_KEYPAD_RIGHT_RELEASE,		//SECPMP_KEYPAD_REG_GPIO71
	SECPMP_KEYPAD_BACK_RELEASE,			//SECPMP_KEYPAD_REG_GPIO72
	SECPMP_KEYPAD_USER_RELEASE,			//SECPMP_KEYPAD_REG_GPIO73
	SECPMP_KEYPAD_MENU_RELEASE,			//SECPMP_KEYPAD_REG_GPIO74
	SECPMP_KEYPAD_POWER_RELEASE,		//SECPMP_KEYPAD_REG_GPIO35
	#endif
	SECPMP_KEYPAD_QUEUE_FULL,
	SECPMP_KEYPAD_UNKNOW
}SECPMP_KEYPAD_EVENT;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
MMP_ERR SECPMP_KEYPAD_SetSenseTime(MMP_ULONG ulTime_ms);
MMP_ERR SECPMP_KEYPAD_Initialize(void);
MMP_ERR SECPMP_KEYPAD_ReadFromQueue(MMP_USHORT *event);
MMP_ERR SECPMP_KEYPAD_InsertToQueue(MMP_USHORT *event);
MMP_ERR SECPMP_KEYPAD_ISR(MMP_GPIO_PIN piopin);
#endif