/**
 @file ahc_gpio.c
 @brief ahc gpio control Function
 @author 
 @version 1.0
*/
/*===========================================================================
 * Include files
 *===========================================================================*/ 
#include "ahc_gpio.h"
#include "mmps_pio.h"

/*===========================================================================
 * Global varible
 *===========================================================================*/ 

/*===========================================================================
 * Extern function
 *===========================================================================*/ 

/*===========================================================================
 * Main body
 *===========================================================================*/ 
 
#if 0
void ____GPIO_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_GPIO_ConfigPad
//  Description :
//  @brief This function configures the pull high or low of selected GPIO.
//  @param[in] ahc_piopin : PIO definition, please refer AHC_PIO_REG
//  @param[in] config :
/*
        #define PAD_NORMAL_TRIG             0x00
        #define PAD_SCHMITT_TRIG            0x01
        #define PAD_PULL_DOWN               0x02
        #define PAD_PULL_UP                 0x04
        #define PAD_FAST_SLEW               0x08
        #define PAD_SLOW_SLEW               0x00
        #define PAD_IDDQ_TEST_EN            0x10
        #define PAD_OUT_DRIVING(_a)         (((_a)&0x03)<<5)
*/
//------------------------------------------------------------------------------
AHC_BOOL AHC_GPIO_ConfigPad(MMP_GPIO_PIN piopin, MMP_UBYTE ubConfig)
{
    if (MMPS_PIO_PadConfig(piopin, ubConfig) == MMP_ERR_NONE) {
        return AHC_TRUE;
    }

    return AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GPIO_SetOutputMode
//  Description :
//------------------------------------------------------------------------------
/**
 @brief This function configures the direction of selected GPIO.

 This function configures the direction of selected GPIO.
 Parameters:
 @param[in] ahc_piopin : PIO definition, please refer AHC_PIO_REG
 @param[in] bDirection : Configures the pin is input or output.
 @retval TRUE or FALSE.
*/

AHC_BOOL AHC_GPIO_SetOutputMode(MMP_GPIO_PIN ahc_piopin, UINT8 bDirection)
{
    MMP_ERR status;

    if (ahc_piopin == MMP_PAD_MAX) {
        return AHC_FALSE;
    }

    if (bDirection == AHC_TRUE) {
        status = MMPS_PIO_EnableOutputMode(ahc_piopin, MMP_TRUE);
    }
    else {
        status = MMPS_PIO_EnableOutputMode(ahc_piopin, MMP_FALSE);
    }

    if (status != MMP_ERR_NONE) {
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GPIO_SetTrigMode
//  Description :
//------------------------------------------------------------------------------
/**
 @brief This API set a callback to be the handler of I/O actions.

 This API set a callback to be the handler of I/O actions.
 Parameters:
 @param[in] ahc_piopin : PIO definition, please refer AHC_PIO_REG
 @param[in] bPolarity : define when the function should be called.
 @param[in] phHandleFunc : Handler function.
 @retval TRUE or FALSE.
*/
AHC_BOOL AHC_GPIO_SetTrigMode(MMP_GPIO_PIN ahc_piopin, MMP_GPIO_TRIG bPolarity)
{
    MMP_ERR         status;
    MMP_GPIO_TRIG   trigmode = bPolarity;

    if (ahc_piopin == MMP_PAD_MAX) {
        return AHC_FALSE;
    }

    status = MMPS_PIO_EnableTrigMode(ahc_piopin, trigmode, MMP_TRUE);

    if (status != MMP_ERR_NONE) {
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GPIO_EnableInterrupt
//  Description :
//------------------------------------------------------------------------------
/**
 @brief This function enable or disable the handler in AHC_GPIO_SetTrigMode.

 This function enable or disable the handler in AHC_GPIO_SetTrigMode.
 Parameters:
 @param[in] ahc_piopin : PIO definition, please refer AHC_PIO_REG
 @param[in] bEnable : Configures the status of GPIO handler.
 @retval TRUE or FALSE.
*/
AHC_BOOL AHC_GPIO_EnableInterrupt(MMP_GPIO_PIN ahc_piopin, void* phHandleFunc, UINT8 bEnable)
{
    MMP_ERR status;

    if (ahc_piopin == MMP_PAD_MAX) {
        return AHC_FALSE;
    }

    status = MMPS_PIO_EnableInterrupt(ahc_piopin, bEnable, 0, (GpioCallBackFunc *)phHandleFunc);

    if (status != MMP_ERR_NONE) {
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GPIO_SetData
//  Description :
//------------------------------------------------------------------------------
/**
 @brief This function sets the state of a selected I/O pin.

 This function sets the state of a selected I/O pin.
 Parameters:
 @param[in] ahc_piopin : PIO definition, please refer AHC_PIO_REG
 @param[in] bState : Configures the output state of selected pin.
 @retval TRUE or FALSE.
*/
AHC_BOOL AHC_GPIO_SetData(MMP_GPIO_PIN ahc_piopin, UINT8 bState)
{
    MMP_ERR status;

    if (ahc_piopin == MMP_PAD_MAX) {
        return AHC_FALSE;
    }

    status = MMPS_PIO_SetData(ahc_piopin, bState);

    if (status != MMP_ERR_NONE) {
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_GPIO_GetData
//  Description :
//------------------------------------------------------------------------------
/**
 @brief This function gets the state of a selected I/O pin.

 This function gets the state of a selected I/O pin.
 Parameters:
 @param[in] ahc_piopin : PIO definition, please refer AHC_PIO_REG
 @param[out] pwState : Get the input state of selected pin.
 @retval TRUE or FALSE.
*/
AHC_BOOL AHC_GPIO_GetData(MMP_GPIO_PIN ahc_piopin, UINT8 *pwState)
{
    MMP_ERR status;

    if (ahc_piopin == MMP_PAD_MAX) {
        return AHC_FALSE;
    }

    status = MMPS_PIO_GetData(ahc_piopin, pwState);

    if (status != MMP_ERR_NONE) {
        return AHC_FALSE;
    }
    return AHC_TRUE;
}


