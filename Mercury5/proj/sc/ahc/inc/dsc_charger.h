#ifndef _DSC_CHARGER_
#define _DSC_CHARGER_

#include "ahc_common.h"

AHC_BOOL InitChargerPins(void);
AHC_BOOL SetChargerMode(UINT8 byMode);
AHC_BOOL SetChargerEnable(AHC_BOOL bEnable);
AHC_BOOL GetChargerStatus(void);
AHC_BOOL IsAdapter_Connect(void);
AHC_BOOL EnterChargerMode(int bWaitInt);
AHC_BOOL GetCharger_PGOOD(void);
AHC_BOOL Charger_Select_Enable(UINT8 byMode);

#endif