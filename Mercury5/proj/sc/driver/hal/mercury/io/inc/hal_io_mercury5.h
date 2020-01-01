/*
 * hal_io_mv5.h
 *
 *  Created on: 2017/8/27
 *      Author: titan.huang
 */

#ifndef _HAL_IO_PUB_MV5_H_
#define _HAL_IO_PUB_MV5_H_

#include "vm_types.ht"
#include "hal_int_ctrl_pub.h"

#define PMS_BANK_A                          0x000E00        //PM Sleep
#define CT_BANK_A                           0x101E00        //Chip Top
#define PAD_BANK_A                          0x103C00        //Pad Top
#define PM_BANK_A                           0x000F00        //PM GPIO
#define SAR_BANK_A                          0x001400        //SAR
#define UTMI0_BANK_A                        0x002200        //UTMI0
#define UTMI1_BANK_A                        0x142900        //UTMI1

#define _RIUA(bank , offset)                GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, bank) + (((offset) & ~1)<<1) + ((offset) & 1)
#define _RIUAW(bank , offset)               GET_BASE_ADDR_BY_BANK(MS_BASE_REG_RIU_PA, bank) + ((offset)<<2)
#define _GPIORD(addr)                       (*(volatile u8*)(addr))

typedef enum
{
    //Non PM
    HAL_IO_SDIO_GPIO0 = 0,//D0
    HAL_IO_SDIO_GPIO1,//D1
    HAL_IO_SDIO_GPIO2,//D2
    HAL_IO_SDIO_GPIO3,//D3
    HAL_IO_SDIO_GPIO4,//CMD
    HAL_IO_SDIO_GPIO5,//5,CLK
    HAL_IO_SAR0_GPIO0,
    HAL_IO_SAR0_GPIO1,
    HAL_IO_SAR0_GPIO2,
    HAL_IO_SAR0_GPIO3,
    HAL_IO_SAR0_GPIO4,//10
    HAL_IO_SAR0_GPIO5,
    HAL_IO_SAR0_GPIO6,
    HAL_IO_FUART_GPIO0,
    HAL_IO_FUART_GPIO1,
    HAL_IO_FUART_GPIO2,//15
    HAL_IO_FUART_GPIO3,//RX
    HAL_IO_UART0_GPIO0,//TX
    HAL_IO_UART0_GPIO1,//RX
    HAL_IO_UART1_GPIO0,//TX
    HAL_IO_UART1_GPIO1,//20
    HAL_IO_SR0D_GPIO0,
    HAL_IO_SR0D_GPIO1,
    HAL_IO_SR0D_GPIO2,
    HAL_IO_SR0D_GPIO3,
    HAL_IO_SR0D_GPIO4,//25
    HAL_IO_SR0D_GPIO5,
    HAL_IO_SR0D_GPIO6,
    HAL_IO_SR0D_GPIO7,
    HAL_IO_SR0D_GPIO8,
    HAL_IO_SR0D_GPIO9,//30
    HAL_IO_SR0D_GPIO10,
    HAL_IO_SR0D_GPIO11,
    HAL_IO_SR1_GPIO0,
    HAL_IO_SR1_GPIO1,
    HAL_IO_SR1_GPIO2,//35
    HAL_IO_SR1_GPIO3,
    HAL_IO_SR1_GPIO4,
    HAL_IO_SR1D_GPIO0,//PAD_SNR1_DA0P
    HAL_IO_SR1D_GPIO1,//PAD_SNR1_DA0N
    HAL_IO_SR1D_GPIO2,//40,PAD_SNR1_CKP
    HAL_IO_SR1D_GPIO3,//PAD_SNR1_CKN
    HAL_IO_SR1D_GPIO4,//PAD_SNR1_DA1P
    HAL_IO_SR1D_GPIO5,//PAD_SNR1_DA1N
    HAL_IO_LCD_GPIO0,
    HAL_IO_LCD_GPIO1,//45
    HAL_IO_LCD_GPIO2,
    HAL_IO_LCD_GPIO3,
    HAL_IO_LCD_GPIO4,
    HAL_IO_LCD_GPIO5,
    HAL_IO_LCD_GPIO6,//50
    HAL_IO_LCD_GPIO7,
    HAL_IO_LCD_GPIO8,
    HAL_IO_LCD_GPIO9,
    HAL_IO_LCD_GPIO10,
    HAL_IO_LCD_GPIO11,//55
    HAL_IO_LCD_GPIO12,
    HAL_IO_LCD_GPIO13,
    HAL_IO_LCD_GPIO14,
    HAL_IO_LCD_GPIO15,
    HAL_IO_LCD_GPIO16,//60
    HAL_IO_LCD_GPIO17,
    HAL_IO_LCD_GPIO18,
    HAL_IO_LCD_GPIO19,
    HAL_IO_LCD_GPIO20,
    HAL_IO_LCD_GPIO21,//65
    HAL_IO_LCD_GPIO22,
    HAL_IO_LCD_GPIO23,
    HAL_IO_LCD_GPIO24,
    HAL_IO_LCD_GPIO25,
    HAL_IO_LCD_GPIO26,//70
    HAL_IO_LCD_GPIO27,
    HAL_IO_LCD_GPIO28,
    HAL_IO_LCD_GPIO29,
    HAL_IO_LCD_GPIO30,
    HAL_IO_LCD_GPIO31,//75
    HAL_IO_LCD_GPIO32,
    HAL_IO_LCD_GPIO33,
    HAL_IO_LCD_GPIO34,
    HAL_IO_SD_GPIO0,
    HAL_IO_SD_GPIO1,//80
    HAL_IO_SD_GPIO2,
    HAL_IO_SD_GPIO3,
    HAL_IO_SD_GPIO4,
    HAL_IO_I2C0_GPIO0,
    HAL_IO_I2C0_GPIO1,//85
    HAL_IO_SPI0_GPIO0,//CZ
    HAL_IO_SPI0_GPIO1,//CK
    HAL_IO_SPI0_GPIO2,//DI
    HAL_IO_SPI0_GPIO3,//DO
    HAL_IO_SPI0_GPIO4,//90,CZ1

    //PM
    HAL_IO_PM_GPIO0,
    HAL_IO_PM_GPIO1,
    HAL_IO_PM_GPIO2,
    HAL_IO_PM_GPIO3,
    HAL_IO_PM_GPIO4,//95
    HAL_IO_PM_GPIO5,
    HAL_IO_PM_GPIO6,
    HAL_IO_PM_GPIO7,
    HAL_IO_PM_GPIO8,
    HAL_IO_PM_GPIO9,//100
    HAL_IO_PM_GPIO10,
    HAL_IO_PM_GPIO11,
    HAL_IO_PM_GPIO12,
    HAL_IO_PM_GPIO13,
    HAL_IO_PM_GPIO14,//105
    HAL_IO_PM_GPIO15,
    HAL_IO_PM_IRIN,
    HAL_IO_PM_UART_RX,
//HAL_IO_PM_CEC,
    HAL_IO_PM_SPI_CZ,
    HAL_IO_PM_SPI_CK,//110
    HAL_IO_PM_SPI_DI,
    HAL_IO_PM_SPI_DO,
    HAL_IO_PM_SPI_WPZ,
    HAL_IO_PM_SPI_HOLDZ,
    HAL_IO_PM_SD_CDZ,//115
    HAL_IO_PM_LED0,
    HAL_IO_PM_LED1,

    HAL_IO_SAR_CH0,
    HAL_IO_SAR_CH1,
    HAL_IO_SAR_CH2,//120
    HAL_IO_SAR_CH3,

    HAL_IO_USB_DM,
    HAL_IO_USB_DP,
    HAL_IO_DM_P1,
    HAL_IO_DP_P1,//125

    HAL_IO_MAX,

} HalGPIOSe;

/**
* @brief        HalGPIOPadSet ,configuration multi-function IO mode, set enable to GPIO mode.
* @param[in]    eGPIOIndex           GPIO Index.
* @param[in]    bEnable              enable GPIO mode or not.
* @retval       None
 */
void HalGPIOPadSet(HalGPIOSe eGPIOIndex,bool bEnable);

/**
* @brief        HalGPIOOutputEnable , Set GPIO output enable or disable
* @param[in]    eGPIOIndex      GPIO Index.
* @param[in]    bEnable         1 is enable.
* @retval       None
*/
void HalGPIOOutputEnable(HalGPIOSe eGPIOIndex,bool bEnable);
/**
* @brief        HalGPIOGetLevel , Get input GPIO level
* @param[in]    eGPIOIndex      GPIO Index.
* @retval       High Level or Low Level
*/
bool HalGPIOGetLevel(HalGPIOSe eGPIOIndex);

/**
* @brief        HalGPIOGetDirection , Get GPIO direction
* @param[in]    eGPIOIndex      GPIO Index.
* @retval       1 is input, 0 is output
*/
bool HalGPIOGetDirection(HalGPIOSe eGPIOIndex);

/**
* @brief        HalGPIOGetDirection , Get GPIO direction
* @param[in]    eGPIOIndex      GPIO Index.
* @retval       1 is input, 0 is output
*/
void HalGPIOSetOutputData(HalGPIOSe eGPIOIndex,bool bHL);

/**
* @brief        HalGPIOEnableINT , GPIO interrupt enable/disable.
* @param[in]    eGPIOIndex      GPIO Index.
* @param[in]    bEnable         enable/disable.
* @param[in]    pfCB            register callback function.
* @retval       TRUE is success, FALSE represent not support interrupt for specialized GPIO
*/
bool HalGPIOEnableINT(HalGPIOSe eGPIOIndex, bool bEnable, PfnIntcISR pfCB);

/**
* @brief        HalGPIOSetPolarity , set input GPIO polarity
* @param[in]    eGPIOIndex      GPIO Index.
* @param[in]    reverse         1 is falling trigger,0 is raising trigger.
* @retval       TRUE is success, FALSE represent not support interrupt for specialized GPIO
*/
bool HalGPIOSetPolarity(HalGPIOSe eGPIOIndex,u8 reverse);

#endif /* _HAL_IO_PUB_MV5_H_ */
