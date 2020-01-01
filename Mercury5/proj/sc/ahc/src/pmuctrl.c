//******************************************************************************
//
//  File        : PMUCtrl.c
//  Description : Power management unit() Control 
//  Author      : .
//  Revision    : 1.0
//
//******************************************************************************

#include "Customer_config.h"
#include "config_fw.h"
#include "lib_retina.h"
#include "pmuctrl.h"
#include "mmpf_i2cm.h"
#include "mmpf_pio.h"
#include "mmpf_saradc.h"
#include "ahc_saradc.h"
#include "ahc_media.h"
#include "ahc_usb.h"
#include "ahc_general_cardv.h"

//******************************************************************************
//
//                              FUNCTION PROTOTYPES
//
//******************************************************************************

#if !defined(MINIBOOT_FW)

AHC_BOOL bPoweroffUsbStatus = AHC_FALSE;
AHC_BOOL bPoweroffAdapterStatus = AHC_FALSE;

extern MMP_ERR MMPF_SARADC_SetMeasMode(MMPF_SARADC_DELAY_CLOCK DEL, MMPF_SARADC_MEA_RATE CR, MMP_BOOL TPWaitenable);
extern void MMPF_RTC_ISOCtl(void);
#if (SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN && defined(ALL_FW))
extern AHC_BOOL AHC_Gsensor_GetCurIntStatus(AHC_BOOL* bObjMove);
#endif

//******************************************************************************
//
//                              Function API
//
//******************************************************************************
void PMUCtrl_ADC_Measure_Key( MMP_ULONG *level, MMP_UBYTE *source, PMU_ADC_TYPE type)
{
}

void PMUCtrl_Power_Gpio_En(MMP_BOOL bGPIOEnable) 
{
    if(bGPIOEnable){
        *(volatile MMP_UBYTE *)0x1F00683C |= 1;//PAD_POC_PWR_EN
    }
    else{
        *(volatile MMP_UBYTE *)0x1F00683C &= ~1;//PAD_POC_PWR_EN
    }

    MMPF_RTC_ISOCtl();
}	

void PMUCtrl_Power_Off(void)
{

    #if (SUPPORT_GSENSOR && POWER_ON_BY_GSENSOR_EN && defined(ALL_FW))
    AHC_Gsensor_SetPowerOnIntThreshold();
    #endif

    while (1) {
        RTNA_DBG_Str0(FG_BLUE("PMUCtrl_Power_Off\r\n"));
        MMPS_DSC_ExitJpegPlayback();
        PMUCtrl_Power_Gpio_En(MMP_FALSE);
        AHC_OS_SleepMs(100);
    }
}
#endif

void PMUCtrl_Write_Reg(MMP_UBYTE ubReg, MMP_UBYTE ubValue)
{
}

void PMUCtrl_Read_Reg(MMP_UBYTE ubReg, MMP_USHORT* ubValue)
{
}

void PMUCtrl_Enable_LDO(PMU_LDO_ID ldoID, MMP_BOOL bEnable)
{
}

MMP_ERR PMUCtrl_Initialize(void)
{
    return MMP_ERR_NONE;
}

void PMUCtrl_Power_Off_For_Exception(void)
{
}
