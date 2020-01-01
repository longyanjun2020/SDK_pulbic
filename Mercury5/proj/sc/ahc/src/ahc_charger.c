//==============================================================================
//
//  File        : AHC_charger.c
//  Description : AHC charger function
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/ 

#include "ahc_charger.h"

/*===========================================================================
 * Global varible
 *===========================================================================*/

/*===========================================================================
 * Extern varible
 *===========================================================================*/

/*===========================================================================
 * Main body
 *===========================================================================*/ 
#if 0
void _____Charger_Control_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_Charger_InitialIO
//  Description :
//------------------------------------------------------------------------------
void AHC_Charger_InitialIO(void)
{
#ifdef CHARGER_STATUS
    if (CHARGER_STATUS != MMP_PAD_MAX) {
        AHC_GPIO_ConfigPad(CHARGER_STATUS, PAD_NORMAL_TRIG);
        AHC_GPIO_SetOutputMode(CHARGER_STATUS, AHC_FALSE);
    }

    AHC_Charger_SetTempCtrlEnable(AHC_FALSE);
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_Charger_SetEnable
//  Description :
//------------------------------------------------------------------------------
void AHC_Charger_SetEnable(AHC_BOOL bEnable)
{
#if 0//defined(ENABLE_CHARGER_IC) && defined(CHARGER_ENABLE_GPIO)
    if (CHARGER_ENABLE_GPIO != MMP_PAD_MAX)
    {
        AHC_GPIO_ConfigPad(CHARGER_ENABLE_GPIO, PAD_OUT_DRIVING(0));
        AHC_GPIO_SetOutputMode(CHARGER_ENABLE_GPIO, AHC_TRUE);
        AHC_GPIO_SetData(CHARGER_ENABLE_GPIO, bEnable ? (CHARGER_ENABLE_GPIO_ACT_LEVEL) : !(CHARGER_ENABLE_GPIO_ACT_LEVEL));
    }
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_Charger_SetEnable
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Charger_GetEnable(void)
{
#if defined(ENABLE_CHARGER_IC) && defined(CHARGER_ENABLE_GPIO)
    AHC_BOOL bReturn = AHC_FALSE;

    if (CHARGER_ENABLE_GPIO != MMP_PAD_MAX)
    {
        UINT8 gpioState;

        AHC_GPIO_GetData(CHARGER_ENABLE_GPIO, &gpioState);
        bReturn = ((CHARGER_ENABLE_GPIO_ACT_LEVEL == gpioState) ? AHC_TRUE : AHC_FALSE);
    }

    return bReturn;
#else
    return AHC_FALSE;
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_Charger_SetTempCtrlEnable
//  Description :
//------------------------------------------------------------------------------
void AHC_Charger_SetTempCtrlEnable(AHC_BOOL bEnable)
{
#if 0//defined(ENABLE_CHARGER_IC) && defined(CHARGER_TEMP_CTL)
    if (CHARGER_TEMP_CTL != MMP_PAD_MAX)
    {
        AHC_GPIO_ConfigPad(CHARGER_TEMP_CTL, PAD_OUT_DRIVING(0));
        AHC_GPIO_SetOutputMode(CHARGER_TEMP_CTL, AHC_TRUE);
        AHC_GPIO_SetData(CHARGER_TEMP_CTL, bEnable);
    }
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_Charger_SetTempCtrlEnable
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Charger_GetTempCtrlStatus(void)
{
#if defined(ENABLE_CHARGER_IC) && defined(CHARGER_TEMP_CTL)
    AHC_BOOL bReturn = AHC_FALSE;

    if (CHARGER_TEMP_CTL != MMP_PAD_MAX)
    {
        AHC_GPIO_GetData(CHARGER_TEMP_CTL, &bReturn);
    }

    return bReturn;
#else
    return AHC_FALSE;
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_Charger_GetStatus
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_Charger_GetStatus(void)
{
#if defined(ENABLE_CHARGER_IC) && defined(CHARGER_STATUS)
    if (CHARGER_STATUS != MMP_PAD_MAX)
    {
        UINT8 state;

        AHC_GPIO_ConfigPad(CHARGER_STATUS, PAD_NORMAL_TRIG);
        AHC_GPIO_SetOutputMode(CHARGER_STATUS, AHC_FALSE);
        AHC_GPIO_GetData(CHARGER_STATUS, &state);

        if (CHARGER_STATUS_ACT_LEVEL == state) {
            return AHC_TRUE;
        }
    }
#endif

    if (AHC_IsDcCableConnect())
        return AHC_TRUE;
#if 0 // TBD
    if (AHC_IsUsbConnect())
        return AHC_TRUE;
#endif
    return AHC_FALSE;
}