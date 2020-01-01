//==============================================================================
//
//  File        : parkingmodectrl.h
//  Description : INCLUDE File for the Parking mode function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _PARKINGMODECTRL_H_
#define _PARKINGMODECTRL_

#define PARKING_MODE_TRIGGER_ENCODE_NONE	0x00
#define PARKING_MODE_TRIGGER_ENCODE_MOTION	0x01
#define PARKING_MODE_TRIGGER_ENCODE_GSENSOR	0x02
#define PARKING_MODE_TRIGGER_ENCODE_BOTH	(PARKING_MODE_TRIGGER_ENCODE_MOTION | PARKING_MODE_TRIGGER_ENCODE_GSENSOR)

typedef struct _PARKING_STATE_INFO
{
    AHC_BOOL           bParkingModeConfirmMenu;
	UINT8		       bParkingMode;
    AHC_BOOL           bRecordVideo;
    AHC_BOOL		   bParkingIdling;
    AHC_BOOL		   bParkingExitState;
    AHC_BOOL		   bAutoStopParkingMode;
    AHC_BOOL           bParkingMoveHintMenu;
    AHC_BOOL		   bParkingSpaceState;
	AHC_BOOL		   bParkingStartDrawed;

}PARKING_STATE_INFO;

typedef enum _PARKING_MODE_ID {
	PARKING_OFF,
	PARKING_NORMAL,
	PARKING_WITH_POWER,
	PARKING_WITHOUT_POWER
}PARKING_MODE_ID;



/*===========================================================================
 * Function prototype
 *===========================================================================*/

typedef struct _PARKLING_MODE_CFG {
	AHC_BOOL			bParkingModeFuncEn;			// Enable Parking mode function, replace of PARKING_TYPE
	UINT8				ubTriggerEncodeMethod;      // Parking mode trigger mode: Motion, Gsensor or Both.
	UINT32				ulPreRecordLengthInMs;      // Pre-record length in Parking mode which is restricted to the size of compress buffer..
	UINT32				ulTotalRecordLengthInMs;    // Total record length in Ms, pre-record length is included.
}PARKLING_MODE_CFG;

PARKLING_MODE_CFG* uiGetParkingCfg(void);
void uiSetParkingCfg(PARKLING_MODE_CFG *pConfig);

UINT8 uiGetParkingModeRecord(void);
void uiSetParkingModeRecord(AHC_BOOL recorded);

#endif
