//==============================================================================
//
//  File        : AHC_PMU.c
//  Description : AHC PMU function
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_pmu.h"
//#include "ahc_general.h"
#include "pmuctrl.h"
#include "ledcontrol.h"
#include "mmps_pio.h"
#include "MenuSetting.h"

/*===========================================================================
 * Main body
 *===========================================================================*/ 

//------------------------------------------------------------------------------
//  Function    : AHC_PMU_PowerOffEx
//  Description :
//------------------------------------------------------------------------------
void AHC_PMU_PowerOffEx(AHC_BOOL bSound)
{	
    MMP_ULONG	ulPowerOffCnt = 0;
    AHC_BOOL	ahc_ret = AHC_FALSE;
    UINT8 		ubSoundStatus;

	if (bSound) 
	{
		#ifdef CFG_CUS_POWEROFF_SOUNDEFFECT
        CFG_CUS_POWEROFF_SOUNDEFFECT();
		#else
	    ahc_ret = AHC_PlaySoundEffect(AHC_SOUNDEFFECT_POWEROFF);
		#endif

		if (AHC_TRUE != ahc_ret) {
			goto L_PMUoff;
		}

	    do {
	        AHC_GetSoundEffectStatus(&ubSoundStatus);
	        AHC_OS_SleepMs(500); 
	        ++ulPowerOffCnt;
	    } while((AHC_SOUND_EFFECT_STATUS_STOP != ubSoundStatus) && (AHC_SOUND_EFFECT_STATUS_INVALID != ubSoundStatus) && (ulPowerOffCnt<16/* Max 8 sec.*/));
	}
	
L_PMUoff:

	// Clean screen as black, it needed for some panel like as SP25P00,
	// otherwise there is a shadow of goodbye bitmap after power off
	AHC_PowerOff_ShowPicture("SF:0:\\black.jpg");

    LedCtrl_LcdBackLight(AHC_FALSE);
    //AHC_OS_SleepMs(200);
    PMUCtrl_Power_Off();
}

//------------------------------------------------------------------------------
//  Function    : AHC_PMU_PowerOff
//  Description :
//------------------------------------------------------------------------------
void AHC_PMU_PowerOff(void)
{
    AHC_PMU_PowerOffEx(AHC_TRUE);
}

//------------------------------------------------------------------------------
//  Function    : PMUCtrl_ADC_Measure_Key
//  Description :
//------------------------------------------------------------------------------
void AHC_PMUCtrl_ADC_Measure_Key(UINT32 *level, UINT8 *source, AHC_PMU_ADC_TYPE type)
{
	PMUCtrl_ADC_Measure_Key(level, source, (PMU_ADC_TYPE)type);
}

//------------------------------------------------------------------------------
//  Function    : AHC_PMUCtrl_Write_Reg
//  Description :
//------------------------------------------------------------------------------
void AHC_PMUCtrl_Write_Reg(UINT8 ubReg, UINT8 ubValue)
{
	PMUCtrl_Write_Reg(ubReg, ubValue);
}

//------------------------------------------------------------------------------
//  Function    : AHC_PMUCtrl_Write_Reg
//  Description :
//------------------------------------------------------------------------------
void AHC_PMUCtrl_Read_Reg(UINT8 ubReg, UINT16* ubValue)
{
	PMUCtrl_Read_Reg(ubReg, ubValue);
}

//------------------------------------------------------------------------------
//  Function    : AHC_PMUCtrl_LDO
//  Description :
//------------------------------------------------------------------------------
void AHC_PMUCtrl_LDO(AHC_PMU_LDO_ID ldoID, AHC_BOOL bEnable)
{
	PMUCtrl_Enable_LDO(ldoID, bEnable);
}