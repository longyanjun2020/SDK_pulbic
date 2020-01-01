/*
 * drv_gpio.h
 *
 *  Created on: 2017/8/28
 *      Author: titan.huang
 */

#ifndef __DRV_GPIO_H__
#define __DRV_GPIO_H__

#include "hal_io_mercury5.h"

typedef enum
{
    //Non PM
    DRV_IO_SDIO_GPIO0,//D0
    DRV_IO_SDIO_GPIO1,//D1
    DRV_IO_SDIO_GPIO2,//D2
    DRV_IO_SDIO_GPIO3,//D3
    DRV_IO_SDIO_GPIO4,//CMD
    DRV_IO_SDIO_GPIO5,//5,CLK
    DRV_IO_SAR0_GPIO0,
    DRV_IO_SAR0_GPIO1,
    DRV_IO_SAR0_GPIO2,
    DRV_IO_SAR0_GPIO3,
    DRV_IO_SAR0_GPIO4,//10
    DRV_IO_SAR0_GPIO5,
    DRV_IO_SAR0_GPIO6,
    DRV_IO_FUART_GPIO0,
    DRV_IO_FUART_GPIO1,
    DRV_IO_FUART_GPIO2,//15
    DRV_IO_FUART_GPIO3,//RX
    DRV_IO_UART0_GPIO0,//TX
    DRV_IO_UART0_GPIO1,//RX
    DRV_IO_UART1_GPIO0,//TX
    DRV_IO_UART1_GPIO1,//20
    DRV_IO_SR0D_GPIO0,
    DRV_IO_SR0D_GPIO1,
    DRV_IO_SR0D_GPIO2,
    DRV_IO_SR0D_GPIO3,
    DRV_IO_SR0D_GPIO4,//25
    DRV_IO_SR0D_GPIO5,
    DRV_IO_SR0D_GPIO6,
    DRV_IO_SR0D_GPIO7,
    DRV_IO_SR0D_GPIO8,
    DRV_IO_SR0D_GPIO9,//30
    DRV_IO_SR0D_GPIO10,
    DRV_IO_SR0D_GPIO11,
    DRV_IO_SR1_GPIO0,
    DRV_IO_SR1_GPIO1,
    DRV_IO_SR1_GPIO2,//35
    DRV_IO_SR1_GPIO3,
    DRV_IO_SR1_GPIO4,
    DRV_IO_SR1D_GPIO0,//PAD_SNR1_DA0P
    DRV_IO_SR1D_GPIO1,//PAD_SNR1_DA0N
    DRV_IO_SR1D_GPIO2,//40,PAD_SNR1_CKP
    DRV_IO_SR1D_GPIO3,//PAD_SNR1_CKN
    DRV_IO_SR1D_GPIO4,//PAD_SNR1_DA1P
    DRV_IO_SR1D_GPIO5,//PAD_SNR1_DA1N
    DRV_IO_LCD_GPIO0,
    DRV_IO_LCD_GPIO1,//45
    DRV_IO_LCD_GPIO2,
    DRV_IO_LCD_GPIO3,
    DRV_IO_LCD_GPIO4,
    DRV_IO_LCD_GPIO5,
    DRV_IO_LCD_GPIO6,//50
    DRV_IO_LCD_GPIO7,
    DRV_IO_LCD_GPIO8,
    DRV_IO_LCD_GPIO9,
    DRV_IO_LCD_GPIO10,
    DRV_IO_LCD_GPIO11,//55
    DRV_IO_LCD_GPIO12,
    DRV_IO_LCD_GPIO13,
    DRV_IO_LCD_GPIO14,
    DRV_IO_LCD_GPIO15,
    DRV_IO_LCD_GPIO16,//60
    DRV_IO_LCD_GPIO17,
    DRV_IO_LCD_GPIO18,
    DRV_IO_LCD_GPIO19,
    DRV_IO_LCD_GPIO20,
    DRV_IO_LCD_GPIO21,//65
    DRV_IO_LCD_GPIO22,
    DRV_IO_LCD_GPIO23,
    DRV_IO_LCD_GPIO24,
    DRV_IO_LCD_GPIO25,
    DRV_IO_LCD_GPIO26,//70
    DRV_IO_LCD_GPIO27,
    DRV_IO_LCD_GPIO28,
    DRV_IO_LCD_GPIO29,
    DRV_IO_LCD_GPIO30,
    DRV_IO_LCD_GPIO31,//75
    DRV_IO_LCD_GPIO32,
    DRV_IO_LCD_GPIO33,
    DRV_IO_LCD_GPIO34,
    DRV_IO_SD_GPIO0,
    DRV_IO_SD_GPIO1,//80
    DRV_IO_SD_GPIO2,
    DRV_IO_SD_GPIO3,
    DRV_IO_SD_GPIO4,
    DRV_IO_I2C0_GPIO0,
    DRV_IO_I2C0_GPIO1,//85
    DRV_IO_SPI0_GPIO0,//CZ
    DRV_IO_SPI0_GPIO1,//CK
    DRV_IO_SPI0_GPIO2,//DI
    DRV_IO_SPI0_GPIO3,//DO
    DRV_IO_SPI0_GPIO4,//90,CZ1

    //PM
    DRV_IO_PM_GPIO0,
    DRV_IO_PM_GPIO1,
    DRV_IO_PM_GPIO2,
    DRV_IO_PM_GPIO3,
    DRV_IO_PM_GPIO4,//95
    DRV_IO_PM_GPIO5,
    DRV_IO_PM_GPIO6,
    DRV_IO_PM_GPIO7,
    DRV_IO_PM_GPIO8,
    DRV_IO_PM_GPIO9,//100
    DRV_IO_PM_GPIO10,
    DRV_IO_PM_GPIO11,
    DRV_IO_PM_GPIO12,
    DRV_IO_PM_GPIO13,
    DRV_IO_PM_GPIO14,//105
    DRV_IO_PM_GPIO15,
    DRV_IO_PM_IRIN,
    DRV_IO_PM_UART_RX,
//DRV_IO_PM_CEC,
    DRV_IO_PM_SPI_CZ,
    DRV_IO_PM_SPI_CK,//110
    DRV_IO_PM_SPI_DI,
    DRV_IO_PM_SPI_DO,
    DRV_IO_PM_SPI_WPZ,
    DRV_IO_PM_SPI_HOLDZ,
    DRV_IO_PM_SD_CDZ,//115
    DRV_IO_PM_LED0,
    DRV_IO_PM_LED1,

    DRV_IO_SAR_CH0,
    DRV_IO_SAR_CH1,
    DRV_IO_SAR_CH2,//120
    DRV_IO_SAR_CH3,

    DRV_IO_USB_DM,
    DRV_IO_USB_DP,
    DRV_IO_DM_P1,
    DRV_IO_DP_P1,//125

    DRV_IO_MAX,

} DrvGPIOSe;

/**
* @brief        DrvGPIOPadSet ,configuration multi-function IO mode, set enable to GPIO mode.
* @param[in]    eGPIOIndex           GPIO Index.
* @param[in]    bEnable              enable GPIO mode or not.
* @retval       None
 */
void DrvGPIOPadSet(DrvGPIOSe eGPIOIndex, bool bEnable);

/**
* @brief        DrvGPIOOutputEnable , Set GPIO output enable or disable
* @param[in]    eGPIOIndex      GPIO Index.
* @param[in]    bEnable         1 is enable.
* @retval       None
*/
void DrvGPIOOutputEnable(DrvGPIOSe eGPIOIndex,bool bEnable);

/**
* @brief        DrvGPIOGetLevel , Get input GPIO level
* @param[in]    eGPIOIndex      GPIO Index.
* @retval       High Level or Low Level
*/
bool DrvGPIOGetLevel(DrvGPIOSe eGPIOIndex);

/**
* @brief        DrvGPIOGetDirection , Get GPIO direction
* @param[in]    eGPIOIndex      GPIO Index.
* @retval       1 is input, 0 is output
*/
bool DrvGPIOGetDirection(DrvGPIOSe eGPIOIndex);

/**
* @brief        DrvGPIOGetDirection , Get GPIO direction
* @param[in]    eGPIOIndex      GPIO Index.
* @retval       1 is input, 0 is output
*/
void DrvGPIOSetOutputData(DrvGPIOSe eGPIOIndex,bool bHL);

/**
* @brief        DrvGPIOEnableINT , GPIO interrupt enable/disable.
* @param[in]    eGPIOIndex      GPIO Index.
* @param[in]    bEnable         enable/disable.
* @param[in]    pfCB            register callback function.
* @retval       TRUE is success, FALSE represent not support interrupt for specialized GPIO
*/
bool DrvGPIOEnableINT(DrvGPIOSe eGPIOIndex, bool bEnable, PfnIntcISR pfCB);
/**
* @brief        DrvGPIOSetPolarity , set input GPIO polarity
* @param[in]    eGPIOIndex      GPIO Index.
* @param[in]    reverse         0 is falling trigger,1 is raising trigger.
* @retval       TRUE is success, FALSE represent not support interrupt for specialized GPIO
*/
bool DrvGPIOSetPolarity(DrvGPIOSe eGPIOIndex,u8 reverse);

#endif /* __DRV_GPIO_H__ */
