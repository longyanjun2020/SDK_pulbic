//==============================================================================
//
//  File        :
//  Description :
//  Author      :
//  Revision    :
//
//==============================================================================


#ifndef _AHC_SD_H_
#define _AHC_SD_H_


#include "ahc_common.h"
//==============================================================================
//
//                              COMPILER OPTION
//
//==============================================================================


//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================
//==============================================================================
//
//                              DEFINE
//
//==============================================================================
//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================
typedef struct _SDIO_ISR_DATA{

	UINT32			uiDeviceId; ///< the id of device.
	AHC_BOOL		bIsSD;      ///< is SD or not.
	AHC_BOOL		bIsHC;      ///< high class.
	AHC_BOOL		bSDHCHsm;  ///< high speed.
	
	UINT8			bySdBusWidth;   ///< 1-bit or 4 bit mode.
	UINT32			uiCardAddr;     ///< card related address.
	UINT16			uwCurClkDiv;    ///< clock divide frequency.
	AHC_BOOL		bPwrOnFirst;    ///< power on or not.
	
	AHC_BOOL		bAccessFail;    ///< read or write is fail or not.
	UINT32			uiCardSize;     ///< the size of card.

}SDIO_ISR_DATA;
//==============================================================================
//
//                              VARIABLES
//
//==============================================================================
//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
typedef void SDIOISRCallBack(SDIO_ISR_DATA* psData);

void AHC_SDIO_RegSDIOISR(UINT32 uiDevID, SDIOISRCallBack *Func);
AHC_BOOL AHC_SDIO_SetDeviceID(UINT32 uiDevID);
AHC_BOOL AHC_SDIO_GetDeviceID(UINT32* puiDevID);
AHC_BOOL AHC_SDIO_InitializeDevice(UINT32 uiDevID);
AHC_BOOL AHC_SDIO_ResetDevice(UINT32 uiDevID);
AHC_BOOL AHC_SDIO_WriteReg(UINT32 uiDevID, UINT8 byFuncNum, UINT32 uiRegAddr, UINT8 bySrc);
AHC_BOOL AHC_SDIO_ReadReg(UINT32 uiDevID, UINT8 byFuncNum, UINT32 uiRegAddr, UINT8 *pbyDst);
AHC_BOOL AHC_SDIO_WriteMultiReg(UINT32 uiDevID,  UINT8 byFuncNum, UINT8 byBlkMode, UINT8 byOpCode, UINT32 uiRegAddr, UINT32 uiCount, UINT32  uiBlkSize, UINT8 *pbySrc);
AHC_BOOL AHC_SDIO_ReadMultiReg(UINT32 uiDevID, UINT8 byFuncNum, UINT8 byBlkMode, UINT8 byOpCode, UINT32 uiRegAddr, UINT32 uiCount, UINT32 uiBlkSize, UINT8 *pbyDst);
AHC_BOOL AHC_SDIO_SendCommand(UINT32 uiDevID, UINT8 byCommand, UINT32 uiArgument);
void AHC_SDIO_EnableISR(UINT32 uiDevID, AHC_BOOL bEnable);
AHC_BOOL AHC_SDIO_ConfigClock(UINT32 uiDevID, UINT32 uiOutputClock);
#endif