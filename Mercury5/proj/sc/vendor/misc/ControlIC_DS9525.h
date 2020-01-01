//==============================================================================
//
//  File        : ControlIC_DS9525.h
//  Description : 
//  Author      : Mark Chang
//  Revision    : 1.0
//
//==============================================================================
#ifndef _ControlIC_DS9525_
#define _ControlIC_DS9525_
#include "ahc_common.h"
typedef enum _CHARGER_MODE
{
	CHARGER_1500_MODE = 0,
	CHARGER_500_MODE
}CHARGER_MODE;

AHC_BOOL InitChargerPins_DS9525(void);
AHC_BOOL SetChargerMode_DS9525(CHARGER_MODE byMode);
AHC_BOOL SetChargerEnable_DS9525(AHC_BOOL bEnable);
AHC_BOOL GetChargerStatus_DS9525(void);
AHC_BOOL GetCharger_PGOOD_DS9525(void);
AHC_BOOL IsAdapter_Connect_DS9525(void);
#endif