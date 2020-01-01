//==============================================================================
//
//  File        : mmps_pio.c
//  Description : PIO Functions.
//  Author      : Ben Lu
//  Revision    : 1.0
//
//==============================================================================
/**
 *  @file mmps_pio.c
 *  @brief The pio control functions
 *  @author Ben Lu
 *  @version 1.0
 */

//==============================================================================
//
//                              INCLUDE FILE
//
//============================================================================== 
 
#include "mmp_lib.h"
#include "mmps_pio.h"
#include "mmpd_pio.h"

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

//------------------------------------------------------------------------------
//  Function    : MMPS_PIO_PadConfig
//  Description :
//------------------------------------------------------------------------------
MMP_ERR MMPS_PIO_PadConfig(MMP_GPIO_PIN piopin, MMP_UBYTE ubConfig)
{
	return MMPD_PIO_PadConfig(piopin, ubConfig);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_PIO_EnableOutputMode
//  Description :
//------------------------------------------------------------------------------
/** @brief The function set the PIN as Output mode (bEnable = MMP_TRUE) or Input mode.

The function set the PIN as Output mode (bEnable = MMP_TRUE) or Input mode. 
@param[in] piopin is the PIO number, please reference the data structure of MMP_GPIO_PIN
@param[in] bEnable is the choice of output mode or input mode
@return It reports the status of the operation.
*/
MMP_ERR MMPS_PIO_EnableOutputMode(MMP_GPIO_PIN piopin, MMP_BOOL bEnable)
{
	return MMPD_PIO_EnableOutputMode(piopin, bEnable);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_PIO_EnableTrigMode
//  Description :
//------------------------------------------------------------------------------
/** @brief The function get the PIO pin's singal. (When the pin is at input mode).

The function get the PIO pin's singal. (When the pin is at input mode).
@param[in] piopin is the PIO number, please reference the data structure of MMP_GPIO_PIN
@param[in] trigmode set the pio pin as edge trigger (H2L or L2H) or level trigger (H or L)
@param[out] bEnable make the tirgger settings work or not.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_PIO_EnableTrigMode(MMP_GPIO_PIN piopin, MMP_GPIO_TRIG trigmode, MMP_BOOL bEnable) 
{
	return MMPD_PIO_EnableTrigMode(piopin, trigmode, bEnable);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_PIO_EnableInterrupt
//  Description :
//------------------------------------------------------------------------------
/** @brief The function set the PIO pin's interrupt actions.

The function set the PIO pin's interrupt actions.
@param[in] piopin is the PIO number, please reference the data structure of MMP_GPIO_PIN
@param[in] bEnable stands for enable interrupt or not.
@param[in] boundingTime is used for advanced interrupt settings.
@param[in] CallBackFunc is used by interrupt handler.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_PIO_EnableInterrupt(MMP_GPIO_PIN piopin, MMP_BOOL bEnable, MMP_ULONG boundingTime, GpioCallBackFunc *cb)
{
	return MMPD_PIO_EnableInterrupt(piopin, bEnable, boundingTime, cb);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_PIO_SetData
//  Description :
//------------------------------------------------------------------------------
/** @brief The function set the PIO pin as High or Low (When the pin is at output mode).

The function set the PIO pin as High or Low (When the pin is at output mode).
@param[in] piopin is the PIO number, please reference the data structure of MMP_GPIO_PIN
@param[in] outputValue is 0 stands for Low, otherwise it stands for High
@return It reports the status of the operation.
*/
MMP_ERR MMPS_PIO_SetData(MMP_GPIO_PIN piopin, MMP_UBYTE outputValue) 
{
	return MMPD_PIO_SetData(piopin, outputValue);
}

//------------------------------------------------------------------------------
//  Function    : MMPS_PIO_GetData
//  Description :
//------------------------------------------------------------------------------
/** @brief The function get the PIO pin's singal. (When the pin is at input mode).

The function get the PIO pin's singal. (When the pin is at input mode).
@param[in] piopin is the PIO number, please reference the data structure of MMP_GPIO_PIN
@param[out] returnValue is standing for the High or Low signal.
@return It reports the status of the operation.
*/
MMP_ERR MMPS_PIO_GetData(MMP_GPIO_PIN piopin, MMP_UBYTE* returnValue) 
{
	return MMPD_PIO_GetData(piopin, returnValue);
}
