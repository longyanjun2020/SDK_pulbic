//==============================================================================
//
//  File        : AHC_vibration.c
//  Description : AHC vibration function
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_vibration.h"

/*===========================================================================
 * Global varible
 *===========================================================================*/

/*===========================================================================
 * Extern varible
 *===========================================================================*/

/*===========================================================================
 * Main body
 *===========================================================================*/ 
#if 0
void ____Vibration_Function____(){ruturn;} //dummy
#endif

#if defined(DEVICE_GPIO_VIBRATION) && (DEVICE_GPIO_VIBRATION != MMP_GPIO_MAX)
static UINT8 vibrationTimerID = 0xFF;

static void Vibration_Timer_ISR(void *ptmr, void *parg)
{
    AHC_OS_StopTimer(vibrationTimerID, AHC_OS_TMR_OPT_NONE );	// must be
	AHC_GPIO_SetData(DEVICE_GPIO_VIBRATION, (0 == DEVICE_GPIO_VIBRATION_ON) ? 1 : 0);
	vibrationTimerID = 0xFF;
}
#endif

AHC_BOOL AHC_Vibration_Enable(UINT32 ulMs)
{
#if 0//defined(DEVICE_GPIO_VIBRATION) && (DEVICE_GPIO_VIBRATION != MMP_GPIO_MAX)
	#if defined MENU_GENERAL_MOTO_EN &&(MENU_GENERAL_MOTO_EN==1)
	if(!pf_GetMotoStatus()) return AHC_TRUE;
	#endif

	if ((UINT32) -1 > ulMs) {
	    if (vibrationTimerID < 0xFE) {
	        AHC_OS_StopTimer( vibrationTimerID, AHC_OS_TMR_OPT_NONE);
	        vibrationTimerID = 0xFF;
	    }

        AHC_GPIO_ConfigPad(DEVICE_GPIO_VIBRATION, PAD_OUT_DRIVING(0));
	    vibrationTimerID = AHC_OS_StartTimer( ulMs, AHC_OS_TMR_OPT_ONE_SHOT, Vibration_Timer_ISR, (void *) NULL );

	    if (0xFE <= vibrationTimerID) {
	        // Start timer error
			AHC_GPIO_SetOutputMode(DEVICE_GPIO_VIBRATION, AHC_TRUE);
			AHC_GPIO_SetData(DEVICE_GPIO_VIBRATION, DEVICE_GPIO_VIBRATION_ON);
	    	AHC_OS_SleepMs(ulMs);
			AHC_GPIO_SetData(DEVICE_GPIO_VIBRATION, (0 == DEVICE_GPIO_VIBRATION_ON) ? 1 : 0);

			return AHC_FALSE;
		}
		else {
			AHC_GPIO_SetOutputMode(DEVICE_GPIO_VIBRATION, AHC_TRUE);
			AHC_GPIO_SetData(DEVICE_GPIO_VIBRATION, DEVICE_GPIO_VIBRATION_ON);

			return AHC_TRUE;
		}
	}

	AHC_GPIO_SetOutputMode(DEVICE_GPIO_VIBRATION, AHC_TRUE);
	AHC_GPIO_SetData(DEVICE_GPIO_VIBRATION, DEVICE_GPIO_VIBRATION_ON);

	return AHC_TRUE;
#else
	return AHC_FALSE;
#endif
}

AHC_BOOL AHC_Vibration_Disable(void)
{
#if defined(DEVICE_GPIO_VIBRATION) && (DEVICE_GPIO_VIBRATION != MMP_GPIO_MAX)
    AHC_BOOL ret = 0;

	if (vibrationTimerID < 0xFE)
	{
	    ret = AHC_OS_StopTimer(vibrationTimerID, AHC_OS_TMR_OPT_NONE );
		vibrationTimerID = 0xFF;

	    if (0xFF == ret)
	 		ret = AHC_FALSE;
		else
			ret = AHC_TRUE;
	}

	AHC_GPIO_SetData(DEVICE_GPIO_VIBRATION, (0 == DEVICE_GPIO_VIBRATION_ON) ? 1 : 0);

	return ret;
#else
	return AHC_FALSE;
#endif
}
