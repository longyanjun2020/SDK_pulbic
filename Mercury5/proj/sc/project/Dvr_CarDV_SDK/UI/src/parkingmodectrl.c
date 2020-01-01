/*===========================================================================
 * Include file 
 *===========================================================================*/

#include "ahc_common.h"
#include "parkingmodectrl.h"
#include "AHC_Config_SDK.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

/*===========================================================================
 * Global varible
 *===========================================================================*/

static PARKING_STATE_INFO   ParkingModeInfo;

/*===========================================================================
 * Extern function
 *===========================================================================*/

/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void _____ParkingMode_Function_________(){ruturn;} //dummy
#endif

void uiSetParkingModeStateInit(void)
{
    ParkingModeInfo.bParkingModeConfirmMenu = AHC_FALSE;
    ParkingModeInfo.bParkingMode = AHC_FALSE;
    ParkingModeInfo.bRecordVideo = AHC_FALSE;
    ParkingModeInfo.bParkingIdling = AHC_FALSE;
    ParkingModeInfo.bParkingExitState = AHC_FALSE;
    ParkingModeInfo.bAutoStopParkingMode = AHC_FALSE;
    ParkingModeInfo.bParkingMoveHintMenu = AHC_FALSE;
    ParkingModeInfo.bParkingSpaceState = AHC_FALSE;
    ParkingModeInfo.bParkingStartDrawed = AHC_FALSE;
}

void uiSetParkingModeEnable(UINT8 enable)
{
    ParkingModeInfo.bParkingIdling = AHC_FALSE;
    ParkingModeInfo.bParkingMode   = enable;
    ParkingModeInfo.bParkingModeConfirmMenu = AHC_FALSE;
    ParkingModeInfo.bParkingExitState = AHC_FALSE;
    ParkingModeInfo.bParkingSpaceState = AHC_FALSE;
    ParkingModeInfo.bParkingMoveHintMenu = AHC_FALSE;
    ParkingModeInfo.bParkingStartDrawed = AHC_FALSE;
}

UINT8 uiGetParkingModeEnable(void)
{
    return ParkingModeInfo.bParkingMode;
}

UINT8 uiGetParkingModeRecord(void)
{
    return ParkingModeInfo.bRecordVideo;
}

void uiSetParkingModeRecord(AHC_BOOL recorded)
{
    ParkingModeInfo.bRecordVideo = recorded;
}

#if 0
void _____ParkingMode_Config_________(){ruturn;} //dummy
#endif

PARKLING_MODE_CFG sPatkingCfg = {AHC_TRUE, 
                                 PARKING_MODE_TRIGGER_ENCODE_BOTH,
                                 PARKING_RECORD_WRITE_PRETIME*1000,//10000,
                                 60000};

void uiSetParkingCfg(PARKLING_MODE_CFG *pConfig)
{
    memcpy(&sPatkingCfg, pConfig, sizeof(PARKLING_MODE_CFG));
}

PARKLING_MODE_CFG* uiGetParkingCfg(void)
{
    return (&sPatkingCfg);
}
