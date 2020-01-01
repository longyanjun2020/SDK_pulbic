//==============================================================================
//
//  File        : AHC_SD.c
//  Description : 
//  Author      : 
//  Revision    : 
//
//==============================================================================

#include "ahc_sd.h"
#include "mmpd_system.h"
#include "mmpf_sd.h"

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

static SDIOISRCallBack *AHC_SDIO_ExtCallBack[MMPF_SD_DEV_NUM] = {NULL};
static UINT32 m_uiSDIODevID = 3;

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

void MMPF_MMU_FlushDCache(void);
void MMPF_MMU_FlushDCacheMVA(MMP_ULONG ulRegion, MMP_ULONG ulSize);

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void _____SDIO_Functions_____(){}
#endif

static void AHC_SDIO_CBDataMapping(stSDMMCHandler* SDMMCArg, SDIO_ISR_DATA* sData)
{
    sData->uiDeviceId   = SDMMCArg->id; 			///< the id of device.
    sData->bIsSD        = SDMMCArg->bIsSD;      	///< is SD or not.
    sData->bIsHC        = SDMMCArg->bIsHC;      	///< high class.
    sData->bSDHCHsm     = SDMMCArg->ubSDHCHsm;  	///< high speed.
	
    sData->bySdBusWidth = SDMMCArg->ubSdBusWidth;   ///< 1-bit or 4 bit mode.
    sData->uiCardAddr   = SDMMCArg->ulCardAddr;     ///< card related address.
    sData->uwCurClkDiv  = SDMMCArg->usCurClkDiv;    ///< clock divide frequency.
    sData->bPwrOnFirst  = SDMMCArg->bPwrOnFirst;    ///< power on or not.
	
    sData->bAccessFail  = SDMMCArg->bAccessFail;    ///< read or write is fail or not.
    sData->uiCardSize   = SDMMCArg->ulCardSize;
}

static void AHC_SDIO_InternalCallBack(stSDMMCHandler* SDMMCArg)
{
    SDIO_ISR_DATA sSDIOCallbackData;

    if (AHC_SDIO_ExtCallBack[SDMMCArg->id]) {

        AHC_SDIO_CBDataMapping(SDMMCArg, &sSDIOCallbackData);
        AHC_SDIO_ExtCallBack[sSDIOCallbackData.uiDeviceId](&sSDIOCallbackData);
    }
}

void AHC_SDIO_RegSDIOISR(UINT32 uiDevID, SDIOISRCallBack *Func)
{
    stSDMMCHandler* pHandler = (stSDMMCHandler*)MMPF_SDIO_GetHandler(uiDevID);                                                
    AHC_SDIO_ExtCallBack[uiDevID] = Func;
    
    MMPF_SDIO_RegSDIOCBFunc(pHandler, (void*)AHC_SDIO_InternalCallBack);
}

AHC_BOOL AHC_SDIO_SetDeviceID(UINT32 uiDevID)
{
    m_uiSDIODevID = uiDevID;
    
    return AHC_TRUE;
}

AHC_BOOL AHC_SDIO_GetDeviceID(UINT32* puiDevID)
{
    *puiDevID = m_uiSDIODevID;
    
    return AHC_TRUE;
}

AHC_BOOL AHC_SDIO_InitializeDevice(UINT32 uiDevID)
{
    stSDMMCHandler* pHandler = (stSDMMCHandler*)MMPF_SDIO_GetHandler(uiDevID);
    
    if (MMPF_SD_InitialInterface(pHandler) == MMP_ERR_NONE)
        return AHC_TRUE;
    else
        return AHC_FALSE;
}

AHC_BOOL AHC_SDIO_ResetDevice(UINT32 uiDevID)
{
    stSDMMCHandler* pHandler = (stSDMMCHandler*)MMPF_SDIO_GetHandler(uiDevID);
    
    if (MMPF_SDIO_Reset(pHandler) == MMP_ERR_NONE)
        return AHC_TRUE;
        
    return AHC_FALSE;
}

AHC_BOOL AHC_SDIO_WriteReg(UINT32 uiDevID, UINT8 byFuncNum, UINT32 uiRegAddr, UINT8 bySrc)
{
    stSDMMCHandler* pHandler = (stSDMMCHandler*)MMPF_SDIO_GetHandler(uiDevID);
    
    if (MMPF_SDIO_WriteReg(pHandler, byFuncNum, uiRegAddr, bySrc) == MMP_ERR_NONE)
        return AHC_TRUE;
    else 
        return AHC_FALSE;
}

AHC_BOOL AHC_SDIO_ConfigClock(UINT32 uiDevID, UINT32 uiOutputClock)
{
    stSDMMCHandler* pHandler = (stSDMMCHandler*)MMPF_SDIO_GetHandler(uiDevID);
    
    UINT32 uiG0Clock;
    
    //MMPD_System_GetGroupFreq(0, &uiG0Clock);

    MMPF_SD_ConfigClock(pHandler, uiG0Clock, uiOutputClock);
    
    return AHC_TRUE;
}

AHC_BOOL AHC_SDIO_ReadReg(UINT32 uiDevID, UINT8 byFuncNum, UINT32 uiRegAddr, UINT8 *pbyDst)
{
    stSDMMCHandler* pHandler = (stSDMMCHandler*)MMPF_SDIO_GetHandler(uiDevID);
    
    if (MMPF_SDIO_ReadReg(pHandler, byFuncNum, uiRegAddr, pbyDst) == MMP_ERR_NONE)
        return AHC_TRUE;
    else
        return AHC_FALSE;
}

AHC_BOOL AHC_SDIO_WriteMultiReg(UINT32 uiDevID,  UINT8 byFuncNum, UINT8 byBlkMode, UINT8 byOpCode, UINT32 uiRegAddr, UINT32 uiCount, UINT32  uiBlkSize, UINT8 *pbySrc)
{
    stSDMMCHandler* pHandler = (stSDMMCHandler*)MMPF_SDIO_GetHandler(uiDevID);
    UINT32 sz;

    if (byBlkMode) {
        sz = uiCount * uiBlkSize;
    } 
    else {
        sz = uiCount;
    }

    MMPF_MMU_FlushDCacheMVA((UINT32)pbySrc, sz);
    
    if (MMPF_SDIO_WriteMultiReg(pHandler, byFuncNum, byBlkMode, byOpCode, uiRegAddr, uiCount, uiBlkSize, pbySrc) != MMP_ERR_NONE)
	{
    	printc("%s %d ERROR!!\r\n", __FUNCTION__, __LINE__);
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

AHC_BOOL AHC_SDIO_ReadMultiReg(UINT32 uiDevID, UINT8 byFuncNum, UINT8 byBlkMode, UINT8 byOpCode, UINT32 uiRegAddr, UINT32 uiCount, UINT32 uiBlkSize, UINT8 *pbyDst)
{
    stSDMMCHandler* pHandler = (stSDMMCHandler*)MMPF_SDIO_GetHandler(uiDevID);
    UINT32 sz;
    
    if (byBlkMode) {
        sz = uiCount * uiBlkSize;
    } 
    else {
        sz = uiCount;
    }

    MMPF_MMU_FlushDCacheMVA((UINT32)pbyDst, sz);
    
    if (MMPF_SDIO_ReadMultiReg(pHandler, byFuncNum, byBlkMode, byOpCode, uiRegAddr, uiCount, uiBlkSize, pbyDst) == MMP_ERR_NONE)
        return AHC_TRUE;
    else
        return AHC_FALSE;
}

AHC_BOOL AHC_SDIO_SendCommand(UINT32 uiDevID, UINT8 byCommand, UINT32 uiArgument)
{
    stSDMMCHandler* pHandler = (stSDMMCHandler*)MMPF_SDIO_GetHandler(uiDevID);
    
    if (MMPF_SD_SendCommand(pHandler, byCommand, uiArgument) == MMP_ERR_NONE)
        return AHC_TRUE;
    else
        return AHC_FALSE;
}

void AHC_SDIO_EnableISR(UINT32 uiDevID, AHC_BOOL bEnable)
{
    stSDMMCHandler* pHandler = (stSDMMCHandler*)MMPF_SDIO_GetHandler(uiDevID);
    
    MMPF_SDIO_EnaISR(pHandler, bEnable);
}

#if 0
void _____SDMMC_Functions_____(){}
#endif
