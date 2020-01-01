//==============================================================================
//
//  File        : AHC_SARADC.c
//  Description : SAR ADC Functions.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file AHC_SARADC.c
 *  @brief The SAR ADC control functions
 *  @author 
 *  @version 1.0
 */

//==============================================================================
//
//                              INCLUDE FILE
//
//============================================================================== 
#include "Customer_config.h"
 
#include "mmp_lib.h"
#include "ahc_os.h"
#include "ahc_saradc.h"
#include "mmpf_saradc.h"
#include "mmp_err.h"

//==============================================================================
//
//                              LOCAL VARIABLES
//
//==============================================================================
#ifdef ALL_FW
static MMPF_OS_SEMID sSARADCSemID = 0xFF;
#endif
MMP_USHORT m_ulPollADCIntervalInMs=20;
MMP_SHORT  m_sADCAccumulateDiff=0;
MMP_SHORT  m_sPreADCAccumulateDiff=0;
MMP_SHORT  m_sPreADCVal=0;
MMP_SHORT  m_sCurADCVal=0;
MMP_USHORT m_usSuccessCount=0;

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : AHC_SARADC_Init
//  Description :
//------------------------------------------------------------------------------
/**
 @brief ADC Initial

 @return the status of the operation.
*/
AHC_BOOL AHC_SARADC_Init(void)
{
    MMPF_SARADC_ATTR sar_att = {0};

#ifdef ALL_FW    
    if (sSARADCSemID == 0xFF) {
        sSARADCSemID = AHC_OS_CreateSem(1);
    }
#endif
    
    sar_att.TPWait = MMP_TRUE;
    MMPF_SARADC_Init(&sar_att);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_SARADC_ReadData
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get ADC Data

 @return the status of the operation.
*/
AHC_BOOL AHC_SARADC_ReadData(UINT16 channel, UINT16 *psaradc_data)
{
    UINT16 saradc_data = 0;

    if (psaradc_data)
        *psaradc_data = 0;

#ifdef ALL_FW    
    if (0 != MMPF_OS_AcquireSem(sSARADCSemID, 1000)) {
        printc(FG_RED("--E-- %s:%d Acquire sSARADCSemID Semaphore fail\r\n"), __FUNCTION__, __LINE__);
        return AHC_FALSE;
    }
#endif

    MMPF_SARADC_GetData(&saradc_data, channel);

    if (psaradc_data)
        *psaradc_data =  saradc_data;

#ifdef ALL_FW    
    MMPF_OS_ReleaseSem(sSARADCSemID);
#endif

    return AHC_TRUE;
}
//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================
//------------------------------------------------------------------------------
//  Function    : AHC_SARADC_SetPollingFreq
//  Description :
//------------------------------------------------------------------------------

void AHC_SARADC_SetPollingFreq(UINT16 intervalInMs)
{
#if 0
    m_ulPollADCIntervalInMs = intervalInMs;
#else
    if(intervalInMs<10)
        m_ulPollADCIntervalInMs = 10;
    else
        m_ulPollADCIntervalInMs = intervalInMs;
#endif
}


