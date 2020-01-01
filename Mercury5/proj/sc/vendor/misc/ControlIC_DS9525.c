//==============================================================================
//
//  File        : ControlIC_DS9525.c
//  Description : 
//  Author      : Mark Chang
//  Revision    : 1.0
//
//==============================================================================
#include "ControlIC_DS9525.h"
#include "config_fw.h"
#include "ahc_general.h"
#include "mmpf_pio.h"

static UINT8 chargersataus = AHC_FALSE;
AHC_BOOL InitChargerPins_DS9525()
{
	AHC_BOOL tempValue; 
	#if(ENABLE_CHARGER_IC_DS9525 == 0)
	return 0;
	#endif 
	printc(" DS9525 Charger Init\n");
    //Set GPIO as input mode
    AHC_GPIO_SetOutputMode(CHARGER_PGOOD_GPIO,  AHC_FALSE);
    AHC_GPIO_SetOutputMode(CHARGER_CHG_GPIO,  AHC_FALSE);
    AHC_GPIO_SetOutputMode(USB_IN_DETECT_VBUS_PIN, AHC_FALSE);
    AHC_GPIO_SetOutputMode(USB_ADAPTER_GPIO,  AHC_FALSE);
    //Set GPIO as output mode
    AHC_GPIO_SetOutputMode(CHARGER_EN1_GPIO, AHC_TRUE);
    AHC_GPIO_SetOutputMode(CHARGER_EN2_GPIO, AHC_TRUE);
    AHC_GPIO_SetOutputMode(CHARGER_ENABLE_GPIO, AHC_TRUE);

    // PGOOD
    AHC_GPIO_GetData( CHARGER_PGOOD_GPIO , &tempValue);
    printc( " PGOOD = %d\n", tempValue );

    // CHG
    AHC_GPIO_GetData( CHARGER_CHG_GPIO , &tempValue);
    printc( " CHG = %d\n", tempValue );

    // USB VBUS
    AHC_GPIO_GetData( USB_IN_DETECT_VBUS_PIN , &tempValue);
    printc( " TODO:		USB VBUS = %d\n", tempValue );

    // USB adapter
    AHC_GPIO_GetData( USB_ADAPTER_GPIO , &tempValue);
    printc( " USB ID = %d\n", tempValue );
    
	return 0;
}
AHC_BOOL SetChargerMode_DS9525(CHARGER_MODE byMode)
{
	#if(ENABLE_CHARGER_IC_DS9525 == 0)
	return 0;
	#endif 
	switch (byMode)
	{
		case CHARGER_1500_MODE: //
	    AHC_GPIO_SetData( CHARGER_EN1_GPIO, AHC_FALSE );
		AHC_GPIO_SetData( CHARGER_EN2_GPIO, AHC_FALSE );
		printc("Set Charger IC 1.5A mode\r\n");
		break;
		case CHARGER_500_MODE:
		AHC_GPIO_SetData( CHARGER_EN1_GPIO, AHC_FALSE );
		AHC_GPIO_SetData( CHARGER_EN2_GPIO, AHC_FALSE );
		printc("Set Charger IC 500mA mode\r\n");
		break;
	}
	return 0;
}
AHC_BOOL SetChargerEnable_DS9525(AHC_BOOL bEnable)
{
	#if(ENABLE_CHARGER_IC_DS9525 == 0)
	return 0;
	#endif 
	if(bEnable)
	AHC_GPIO_SetData( CHARGER_ENABLE_GPIO, AHC_FALSE );
	else
	AHC_GPIO_SetData( CHARGER_ENABLE_GPIO, AHC_TRUE );
	return 0;
}
AHC_BOOL GetChargerStatus_DS9525()
{
	AHC_BOOL tempValue = 0;
	#if(ENABLE_CHARGER_IC_DS9525 == 0)
	return 0;
	#endif 
	 
	AHC_GPIO_GetData(CHARGER_CHG_GPIO,&tempValue);
	if(tempValue == 0)
	{
		printc("Charging\r\n");
		chargersataus = AHC_TRUE;
	}else
	{
		printc("Charger Suspend\r\n");
		chargersataus = AHC_FALSE;
	}
	
	return chargersataus;
}
AHC_BOOL GetCharger_PGOOD_DS9525()
{
	AHC_BOOL tempValue = 0;
	#if(ENABLE_CHARGER_IC_DS9525 == 0)
	return 0;
	#endif
	AHC_GPIO_GetData(CHARGER_PGOOD_GPIO,&tempValue);
	if(tempValue == 0)
	{
		printc("Vin>Vbat : Chargeable!\r\n");
		
	}else
	{
		printc("Vin<Vbat : Unchargeable!\r\n");
	}
	return !tempValue;
}

AHC_BOOL IsAdapter_Connect_DS9525(void)
{
	AHC_BOOL tempValue = 0;  
	
	if(USB_ADAPTER_GPIO != 0xFFF)
	{
		AHC_GPIO_GetData( USB_ADAPTER_GPIO , &tempValue); // 
		printc("USB_ADAPTER_GPIO : %d\r\n",tempValue);
		 //L ->USB CABLE , H-> ADAPTER
		return tempValue;
	}
	else
		return 0;	
}