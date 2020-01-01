/******************************************************************************/
/*  File    :   kernel_gpio.h                                                 */
/*----------------------------------------------------------------------------*/
/*  Scope   :   System GPIO related definitions                               */
/*                                                                            */
/******************************************************************************/

#ifndef __KERNEL_GPIO_H__
#define __KERNEL_GPIO_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "stdcomp.h"
#include "riubridge.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#define PAD_U0TXD_DWL_MODE      0x0
#define PAD_U0TXD_NORM_MODE     0x1


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
/************************************************/
/* GPIO registers definition                    */
/************************************************/
typedef struct KeEmiGpioNand_s
{
    /* [0x00] */
    u32 :32; /// [0x00]
    u32 :32; /// [0x01]
    u32 :32; /// [0x02]
    u32 :32; /// [0x03]
    u32 :32; /// [0x04]
    u32 :32; /// [0x05]
    u32 :32; /// [0x06]
    u32 :32; /// [0x07]
    u32 :32; /// [0x08]
    u32 :32; /// [0x09]
    u32 :32; /// [0x0A]
    u32 :32; /// [0x0B]
    u32 :32; /// [0x0C]
    u32 :32; /// [0x0D]
    u32 :32; /// [0x0E]
    u32 :32; /// [0x0F]
    /* [0x10] */
    u32 :8 ; /// [0x10]
    u32 reg_emi_gpio33_in             :1 ; /// None
    u32 reg_emi_gpio33_out            :1 ; /// None
    u32 reg_emi_gpio33_oen            :1 ; /// None
    u32 :1 ; /// [0x10]
    u32 reg_emi_gpio33_pe             :1 ; /// None
    u32 reg_emi_gpio33_ps             :1 ; /// None
    u32 :1 ; /// [0x10]
    u32 reg_emi_gpio33_mode           :1 ; /// None
    u32 :16; /// [0x10]
    u32 :32; /// [0x11]
    u32 :32; /// [0x12]
    u32 :32; /// [0x13]
    /* [0x14] */
    u32 reg_emi_gpio40_in             :1 ; /// None
    u32 reg_emi_gpio40_out            :1 ; /// None
    u32 reg_emi_gpio40_oen            :1 ; /// None
    u32 :1 ; /// [0x14]
    u32 reg_emi_gpio40_pe             :1 ; /// None
    u32 reg_emi_gpio40_ps             :1 ; /// None
    u32 :1 ; /// [0x14]
    u32 reg_emi_gpio40_mode           :1 ; /// None
    u32 reg_emi_gpio41_in             :1 ; /// None
    u32 reg_emi_gpio41_out            :1 ; /// None
    u32 reg_emi_gpio41_oen            :1 ; /// None
    u32 :1 ; /// [0x14]
    u32 reg_emi_gpio41_pe             :1 ; /// None
    u32 reg_emi_gpio41_ps             :1 ; /// None
    u32 :1 ; /// [0x14]
    u32 reg_emi_gpio41_mode           :1 ; /// None
    u32 :16; /// [0x14]
    /* [0x15] */
    u32 reg_emi_gpio42_in             :1 ; /// None
    u32 reg_emi_gpio42_out            :1 ; /// None
    u32 reg_emi_gpio42_oen            :1 ; /// None
    u32 :1 ; /// [0x15]
    u32 reg_emi_gpio42_pe             :1 ; /// None
    u32 reg_emi_gpio42_ps             :1 ; /// None
    u32 :1 ; /// [0x15]
    u32 reg_emi_gpio42_mode           :1 ; /// None
    u32 reg_emi_gpio43_in             :1 ; /// None
    u32 reg_emi_gpio43_out            :1 ; /// None
    u32 reg_emi_gpio43_oen            :1 ; /// None
    u32 :1 ; /// [0x15]
    u32 reg_emi_gpio43_pe             :1 ; /// None
    u32 reg_emi_gpio43_ps             :1 ; /// None
    u32 :1 ; /// [0x15]
    u32 reg_emi_gpio43_mode           :1 ; /// None
    u32 :16; /// [0x15]
    /* [0x16] */
    u32 reg_emi_gpio44_in             :1 ; /// None
    u32 reg_emi_gpio44_out            :1 ; /// None
    u32 reg_emi_gpio44_oen            :1 ; /// None
    u32 :1 ; /// [0x16]
    u32 reg_emi_gpio44_pe             :1 ; /// None
    u32 reg_emi_gpio44_ps             :1 ; /// None
    u32 :1 ; /// [0x16]
    u32 reg_emi_gpio44_mode           :1 ; /// None
    u32 reg_emi_gpio45_in             :1 ; /// None
    u32 reg_emi_gpio45_out            :1 ; /// None
    u32 reg_emi_gpio45_oen            :1 ; /// None
    u32 :1 ; /// [0x16]
    u32 reg_emi_gpio45_pe             :1 ; /// None
    u32 reg_emi_gpio45_ps             :1 ; /// None
    u32 :1 ; /// [0x16]
    u32 reg_emi_gpio45_mode           :1 ; /// None
    u32 :16; /// [0x16]
    /* [0x17] */
    u32 reg_emi_gpio46_in             :1 ; /// None
    u32 reg_emi_gpio46_out            :1 ; /// None
    u32 reg_emi_gpio46_oen            :1 ; /// None
    u32 :1 ; /// [0x17]
    u32 reg_emi_gpio46_pe             :1 ; /// None
    u32 reg_emi_gpio46_ps             :1 ; /// None
    u32 :1 ; /// [0x17]
    u32 reg_emi_gpio46_mode           :1 ; /// None
    u32 reg_emi_gpio47_in             :1 ; /// None
    u32 reg_emi_gpio47_out            :1 ; /// None
    u32 reg_emi_gpio47_oen            :1 ; /// None
    u32 :1 ; /// [0x17]
    u32 reg_emi_gpio47_pe             :1 ; /// None
    u32 reg_emi_gpio47_ps             :1 ; /// None
    u32 :1 ; /// [0x17]
    u32 reg_emi_gpio47_mode           :1 ; /// None
    u32 :16; /// [0x17]
    /* [0x18] */
    u32 reg_emi_gpio48_in             :1 ; /// None
    u32 reg_emi_gpio48_out            :1 ; /// None
    u32 reg_emi_gpio48_oen            :1 ; /// None
    u32 :1 ; /// [0x18]
    u32 reg_emi_gpio48_pe             :1 ; /// None
    u32 reg_emi_gpio48_ps             :1 ; /// None
    u32 :1 ; /// [0x18]
    u32 reg_emi_gpio48_mode           :1 ; /// None
    u32 reg_emi_gpio49_in             :1 ; /// None
    u32 reg_emi_gpio49_out            :1 ; /// None
    u32 reg_emi_gpio49_oen            :1 ; /// None
    u32 :1 ; /// [0x18]
    u32 reg_emi_gpio49_pe             :1 ; /// None
    u32 reg_emi_gpio49_ps             :1 ; /// None
    u32 :1 ; /// [0x18]
    u32 reg_emi_gpio49_mode           :1 ; /// None
    u32 :16; /// [0x18]
    /* [0x19] */
    u32 reg_emi_gpio50_in             :1 ; /// None
    u32 reg_emi_gpio50_out            :1 ; /// None
    u32 reg_emi_gpio50_oen            :1 ; /// None
    u32 :1 ; /// [0x19]
    u32 reg_emi_gpio50_pe             :1 ; /// None
    u32 reg_emi_gpio50_ps             :1 ; /// None
    u32 :1 ; /// [0x19]
    u32 reg_emi_gpio50_mode           :1 ; /// None
    u32 reg_emi_gpio51_in             :1 ; /// None
    u32 reg_emi_gpio51_out            :1 ; /// None
    u32 reg_emi_gpio51_oen            :1 ; /// None
    u32 :1 ; /// [0x19]
    u32 reg_emi_gpio51_pe             :1 ; /// None
    u32 reg_emi_gpio51_ps             :1 ; /// None
} KeEmiGpioNand_t;

typedef struct KeEmiGpioAdmux_s
{
    /* [0x00] */
    u32 :32; /// [0x00]
    u32 :32; /// [0x01]
    u32 :32; /// [0x02]
    u32 :32; /// [0x03]
    u32 :32; /// [0x04]
    u32 :32; /// [0x05]
    u32 :32; /// [0x06]
    u32 :32; /// [0x07]
    u32 :32; /// [0x08]
    u32 :32; /// [0x09]
    u32 :32; /// [0x0A]
    u32 :32; /// [0x0B]
    /* [0x0C] */
    u32 reg_emi_gpio24_in             :1 ; /// None
    u32 reg_emi_gpio24_out            :1 ; /// None
    u32 reg_emi_gpio24_oen            :1 ; /// None
    u32 :1 ; /// [0x0C]
    u32 reg_emi_gpio24_pe             :1 ; /// None
    u32 reg_emi_gpio24_ps             :1 ; /// None
    u32 :1 ; /// [0x0C]
    u32 reg_emi_gpio24_mode           :1 ; /// None
    u32 :24; /// [0x0C]
    /* [0x0D] */
    u32 :8 ; /// [0x0D]
    u32 reg_emi_gpio27_in             :1 ; /// None
    u32 reg_emi_gpio27_out            :1 ; /// None
    u32 reg_emi_gpio27_oen            :1 ; /// None
    u32 :1 ; /// [0x0D]
    u32 reg_emi_gpio27_pe             :1 ; /// None
    u32 reg_emi_gpio27_ps             :1 ; /// None
    u32 :1 ; /// [0x0D]
    u32 reg_emi_gpio27_mode           :1 ; /// None
    u32 :16; /// [0x0D]
    /* [0x0E] */
    u32 reg_emi_gpio28_in             :1 ; /// None
    u32 reg_emi_gpio28_out            :1 ; /// None
    u32 reg_emi_gpio28_oen            :1 ; /// None
    u32 :1 ; /// [0x0E]
    u32 reg_emi_gpio28_pe             :1 ; /// None
    u32 reg_emi_gpio28_ps             :1 ; /// None
} KeEmiGpioAdmux_t;

typedef struct KeEmiGpioNor_s
{
    /* [0x00] */
    u32 reg_emi_gpio0_in              :1 ; /// None
    u32 reg_emi_gpio0_out             :1 ; /// None
    u32 reg_emi_gpio0_oen             :1 ; /// None
    u32 :1 ; /// [0x00]
    u32 reg_emi_gpio0_pe              :1 ; /// None
    u32 :2 ; /// [0x00]
    u32 reg_emi_gpio0_mode            :1 ; /// None
    u32 reg_emi_gpio1_in              :1 ; /// None
    u32 reg_emi_gpio1_out             :1 ; /// None
    u32 reg_emi_gpio1_oen             :1 ; /// None
    u32 :1 ; /// [0x00]
    u32 reg_emi_gpio1_pe              :1 ; /// None
    u32 :2 ; /// [0x00]
    u32 reg_emi_gpio1_mode            :1 ; /// None
    u32 :16; /// [0x00]
    /* [0x01] */
    u32 reg_emi_gpio2_in              :1 ; /// None
    u32 reg_emi_gpio2_out             :1 ; /// None
    u32 reg_emi_gpio2_oen             :1 ; /// None
    u32 :1 ; /// [0x01]
    u32 reg_emi_gpio2_pe              :1 ; /// None
    u32 :2 ; /// [0x01]
    u32 reg_emi_gpio2_mode            :1 ; /// None
    u32 reg_emi_gpio3_in              :1 ; /// None
    u32 reg_emi_gpio3_out             :1 ; /// None
    u32 reg_emi_gpio3_oen             :1 ; /// None
    u32 :1 ; /// [0x01]
    u32 reg_emi_gpio3_pe              :1 ; /// None
    u32 :2 ; /// [0x01]
    u32 reg_emi_gpio3_mode            :1 ; /// None
    u32 :16; /// [0x01]
    /* [0x02] */
    u32 reg_emi_gpio4_in              :1 ; /// None
    u32 reg_emi_gpio4_out             :1 ; /// None
    u32 reg_emi_gpio4_oen             :1 ; /// None
    u32 :1 ; /// [0x02]
    u32 reg_emi_gpio4_pe              :1 ; /// None
    u32 :2 ; /// [0x02]
    u32 reg_emi_gpio4_mode            :1 ; /// None
    u32 reg_emi_gpio5_in              :1 ; /// None
    u32 reg_emi_gpio5_out             :1 ; /// None
    u32 reg_emi_gpio5_oen             :1 ; /// None
    u32 :1 ; /// [0x02]
    u32 reg_emi_gpio5_pe              :1 ; /// None
    u32 :2 ; /// [0x02]
    u32 reg_emi_gpio5_mode            :1 ; /// None
    u32 :16; /// [0x02]
    /* [0x03] */
    u32 reg_emi_gpio6_in              :1 ; /// None
    u32 reg_emi_gpio6_out             :1 ; /// None
    u32 reg_emi_gpio6_oen             :1 ; /// None
    u32 :1 ; /// [0x03]
    u32 reg_emi_gpio6_pe              :1 ; /// None
    u32 :2 ; /// [0x03]
    u32 reg_emi_gpio6_mode            :1 ; /// None
    u32 reg_emi_gpio7_in              :1 ; /// None
    u32 reg_emi_gpio7_out             :1 ; /// None
    u32 reg_emi_gpio7_oen             :1 ; /// None
    u32 :1 ; /// [0x03]
    u32 reg_emi_gpio7_pe              :1 ; /// None
    u32 :2 ; /// [0x03]
    u32 reg_emi_gpio7_mode            :1 ; /// None
    u32 :16; /// [0x03]
    /* [0x04] */
    u32 reg_emi_gpio8_in              :1 ; /// None
    u32 reg_emi_gpio8_out             :1 ; /// None
    u32 reg_emi_gpio8_oen             :1 ; /// None
    u32 :1 ; /// [0x04]
    u32 reg_emi_gpio8_pe              :1 ; /// None
    u32 :2 ; /// [0x04]
    u32 reg_emi_gpio8_mode            :1 ; /// None
    u32 reg_emi_gpio9_in              :1 ; /// None
    u32 reg_emi_gpio9_out             :1 ; /// None
    u32 reg_emi_gpio9_oen             :1 ; /// None
    u32 :1 ; /// [0x04]
    u32 reg_emi_gpio9_pe              :1 ; /// None
    u32 :2 ; /// [0x04]
    u32 reg_emi_gpio9_mode            :1 ; /// None
    u32 :16; /// [0x04]
    /* [0x05] */
    u32 reg_emi_gpio10_in             :1 ; /// None
    u32 reg_emi_gpio10_out            :1 ; /// None
    u32 reg_emi_gpio10_oen            :1 ; /// None
    u32 :1 ; /// [0x05]
    u32 reg_emi_gpio10_pe             :1 ; /// None
    u32 :2 ; /// [0x05]
    u32 reg_emi_gpio10_mode           :1 ; /// None
    u32 reg_emi_gpio11_in             :1 ; /// None
    u32 reg_emi_gpio11_out            :1 ; /// None
    u32 reg_emi_gpio11_oen            :1 ; /// None
    u32 :1 ; /// [0x05]
    u32 reg_emi_gpio11_pe             :1 ; /// None
    u32 :2 ; /// [0x05]
    u32 reg_emi_gpio11_mode           :1 ; /// None
    u32 :16; /// [0x05]
    /* [0x06] */
    u32 reg_emi_gpio12_in             :1 ; /// None
    u32 reg_emi_gpio12_out            :1 ; /// None
    u32 reg_emi_gpio12_oen            :1 ; /// None
    u32 :1 ; /// [0x06]
    u32 reg_emi_gpio12_pe             :1 ; /// None
    u32 :2 ; /// [0x06]
    u32 reg_emi_gpio12_mode           :1 ; /// None
    u32 reg_emi_gpio13_in             :1 ; /// None
    u32 reg_emi_gpio13_out            :1 ; /// None
    u32 reg_emi_gpio13_oen            :1 ; /// None
    u32 :1 ; /// [0x06]
    u32 reg_emi_gpio13_pe             :1 ; /// None
    u32 :2 ; /// [0x06]
    u32 reg_emi_gpio13_mode           :1 ; /// None
    u32 :16; /// [0x06]
    /* [0x07] */
    u32 reg_emi_gpio14_in             :1 ; /// None
    u32 reg_emi_gpio14_out            :1 ; /// None
    u32 reg_emi_gpio14_oen            :1 ; /// None
    u32 :1 ; /// [0x07]
    u32 reg_emi_gpio14_pe             :1 ; /// None
    u32 :2 ; /// [0x07]
    u32 reg_emi_gpio14_mode           :1 ; /// None
    u32 reg_emi_gpio15_in             :1 ; /// None
    u32 reg_emi_gpio15_out            :1 ; /// None
    u32 reg_emi_gpio15_oen            :1 ; /// None
    u32 :1 ; /// [0x07]
    u32 reg_emi_gpio15_pe             :1 ; /// None
    u32 :2 ; /// [0x07]
    u32 reg_emi_gpio15_mode           :1 ; /// None
    u32 :16; /// [0x07]
    /* [0x08] */
    u32 reg_emi_gpio16_in             :1 ; /// None
    u32 reg_emi_gpio16_out            :1 ; /// None
    u32 reg_emi_gpio16_oen            :1 ; /// None
    u32 :1 ; /// [0x08]
    u32 reg_emi_gpio16_pe             :1 ; /// None
    u32 :2 ; /// [0x08]
    u32 reg_emi_gpio16_mode           :1 ; /// None
    u32 reg_emi_gpio17_in             :1 ; /// None
    u32 reg_emi_gpio17_out            :1 ; /// None
    u32 reg_emi_gpio17_oen            :1 ; /// None
    u32 :1 ; /// [0x08]
    u32 reg_emi_gpio17_pe             :1 ; /// None
    u32 :2 ; /// [0x08]
    u32 reg_emi_gpio17_mode           :1 ; /// None
    u32 :16; /// [0x08]
    /* [0x09] */
    u32 reg_emi_gpio18_in             :1 ; /// None
    u32 reg_emi_gpio18_out            :1 ; /// None
    u32 reg_emi_gpio18_oen            :1 ; /// None
    u32 :1 ; /// [0x09]
    u32 reg_emi_gpio18_pe             :1 ; /// None
    u32 :2 ; /// [0x09]
    u32 reg_emi_gpio18_mode           :1 ; /// None
    u32 reg_emi_gpio19_in             :1 ; /// None
    u32 reg_emi_gpio19_out            :1 ; /// None
    u32 reg_emi_gpio19_oen            :1 ; /// None
    u32 :1 ; /// [0x09]
    u32 reg_emi_gpio19_pe             :1 ; /// None
    u32 :2 ; /// [0x09]
    u32 reg_emi_gpio19_mode           :1 ; /// None
    u32 :16; /// [0x09]
    /* [0x0A] */
    u32 reg_emi_gpio20_in             :1 ; /// None
    u32 reg_emi_gpio20_out            :1 ; /// None
    u32 reg_emi_gpio20_oen            :1 ; /// None
    u32 :1 ; /// [0x0A]
    u32 reg_emi_gpio20_pe             :1 ; /// None
    u32 :2 ; /// [0x0A]
    u32 reg_emi_gpio20_mode           :1 ; /// None
    u32 reg_emi_gpio21_in             :1 ; /// None
    u32 reg_emi_gpio21_out            :1 ; /// None
    u32 reg_emi_gpio21_oen            :1 ; /// None
    u32 :1 ; /// [0x0A]
    u32 reg_emi_gpio21_pe             :1 ; /// None
    u32 :2 ; /// [0x0A]
    u32 reg_emi_gpio21_mode           :1 ; /// None
    u32 :16; /// [0x0A]
    /* [0x0B] */
    u32 reg_emi_gpio22_in             :1 ; /// None
    u32 reg_emi_gpio22_out            :1 ; /// None
    u32 reg_emi_gpio22_oen            :1 ; /// None
    u32 :1 ; /// [0x0B]
    u32 reg_emi_gpio22_pe             :1 ; /// None
    u32 :2 ; /// [0x0B]
    u32 reg_emi_gpio22_mode           :1 ; /// None
    u32 reg_emi_gpio23_in             :1 ; /// None
    u32 reg_emi_gpio23_out            :1 ; /// None
    u32 reg_emi_gpio23_oen            :1 ; /// None
    u32 :1 ; /// [0x0B]
    u32 reg_emi_gpio23_pe             :1 ; /// None
    u32 :2 ; /// [0x0B]
    u32 reg_emi_gpio23_mode           :1 ; /// None
    u32 :16; /// [0x0B]
    /* [0x0C] */
    u32 :8 ; /// [0x0C]
    u32 reg_emi_gpio25_in             :1 ; /// None
    u32 reg_emi_gpio25_out            :1 ; /// None
    u32 reg_emi_gpio25_oen            :1 ; /// None
    u32 :1 ; /// [0x0C]
    u32 reg_emi_gpio25_pe             :1 ; /// None
    u32 :2 ; /// [0x0C]
    u32 reg_emi_gpio25_mode           :1 ; /// None
    u32 :16; /// [0x0C]
    /* [0x0D] */
    u32 reg_emi_gpio26_in             :1 ; /// None
    u32 reg_emi_gpio26_out            :1 ; /// None
    u32 reg_emi_gpio26_oen            :1 ; /// None
    u32 :1 ; /// [0x0D]
    u32 reg_emi_gpio26_pe             :1 ; /// None
    u32 :2 ; /// [0x0D]
    u32 reg_emi_gpio26_mode           :1 ; /// None
    u32 :24; /// [0x0D]
    /* [0x0E] */
    u32 :8 ; /// [0x0E]
    u32 reg_emi_gpio29_in             :1 ; /// None
    u32 reg_emi_gpio29_out            :1 ; /// None
    u32 reg_emi_gpio29_oen            :1 ; /// None
    u32 :1 ; /// [0x0E]
    u32 reg_emi_gpio29_pe             :1 ; /// None
    u32 :2 ; /// [0x0E]
    u32 reg_emi_gpio29_mode           :1 ; /// None
    u32 :16; /// [0x0E]
    /* [0x0F] */
    u32 reg_emi_gpio30_in             :1 ; /// None
    u32 reg_emi_gpio30_out            :1 ; /// None
    u32 reg_emi_gpio30_oen            :1 ; /// None
    u32 :1 ; /// [0x0F]
    u32 reg_emi_gpio30_pe             :1 ; /// None
    u32 :2 ; /// [0x0F]
    u32 reg_emi_gpio30_mode           :1 ; /// None
    u32 reg_emi_gpio31_in             :1 ; /// None
    u32 reg_emi_gpio31_out            :1 ; /// None
    u32 reg_emi_gpio31_oen            :1 ; /// None
    u32 :1 ; /// [0x0F]
    u32 reg_emi_gpio31_pe             :1 ; /// None
    u32 :2 ; /// [0x0F]
    u32 reg_emi_gpio31_mode           :1 ; /// None
    u32 :16; /// [0x0F]
    /* [0x10] */
    u32 reg_emi_gpio32_in             :1 ; /// None
    u32 reg_emi_gpio32_out            :1 ; /// None
    u32 reg_emi_gpio32_oen            :1 ; /// None
    u32 :1 ; /// [0x10]
    u32 reg_emi_gpio32_pe             :1 ; /// None
    u32 :2 ; /// [0x10]
    u32 reg_emi_gpio32_mode           :1 ; /// None
    u32 :24; /// [0x10]
    /* [0x11] */
    u32 reg_emi_gpio34_in             :1 ; /// None
    u32 reg_emi_gpio34_out            :1 ; /// None
    u32 reg_emi_gpio34_oen            :1 ; /// None
    u32 :1 ; /// [0x11]
    u32 reg_emi_gpio34_pe             :1 ; /// None
    u32 :2 ; /// [0x11]
    u32 reg_emi_gpio34_mode           :1 ; /// None
    u32 reg_emi_gpio35_in             :1 ; /// None
    u32 reg_emi_gpio35_out            :1 ; /// None
    u32 reg_emi_gpio35_oen            :1 ; /// None
    u32 :1 ; /// [0x11]
    u32 reg_emi_gpio35_pe             :1 ; /// None
    u32 :2 ; /// [0x11]
    u32 reg_emi_gpio35_mode           :1 ; /// None
    u32 :16; /// [0x11]
    /* [0x12] */
    u32 reg_emi_gpio36_in             :1 ; /// None
    u32 reg_emi_gpio36_out            :1 ; /// None
    u32 reg_emi_gpio36_oen            :1 ; /// None
    u32 :1 ; /// [0x12]
    u32 reg_emi_gpio36_pe             :1 ; /// None
    u32 :2 ; /// [0x12]
    u32 reg_emi_gpio36_mode           :1 ; /// None
    u32 reg_emi_gpio37_in             :1 ; /// None
    u32 reg_emi_gpio37_out            :1 ; /// None
    u32 reg_emi_gpio37_oen            :1 ; /// None
    u32 :1 ; /// [0x12]
    u32 reg_emi_gpio37_pe             :1 ; /// None
    u32 :2 ; /// [0x12]
    u32 reg_emi_gpio37_mode           :1 ; /// None
    u32 :16; /// [0x12]
    /* [0x13] */
    u32 reg_emi_gpio38_in             :1 ; /// None
    u32 reg_emi_gpio38_out            :1 ; /// None
    u32 reg_emi_gpio38_oen            :1 ; /// None
    u32 :1 ; /// [0x13]
    u32 reg_emi_gpio38_pe             :1 ; /// None
    u32 :2 ; /// [0x13]
    u32 reg_emi_gpio38_mode           :1 ; /// None
    u32 reg_emi_gpio39_in             :1 ; /// None
    u32 reg_emi_gpio39_out            :1 ; /// None
    u32 reg_emi_gpio39_oen            :1 ; /// None
    u32 :1 ; /// [0x13]
    u32 reg_emi_gpio39_pe             :1 ; /// None
} KeEmiGpioNor_t;

typedef struct KeGpioCtrl2_s
{
    KeEmiGpioNand_t     tGpioNand;
    KeEmiGpioAdmux_t    tGpioAdmux;
    KeEmiGpioNor_t      tGpioNor;
} KeGpioCtrl2_t;

typedef struct KeGpioCtrl1_s
{
    /* [0x00] */
    u32 reg_cmmb_gpio0_in             :1 ; /// None
    u32 reg_cmmb_gpio0_out            :1 ; /// None
    u32 reg_cmmb_gpio0_oen            :1 ; /// None
    u32 :1 ; /// [0x00]
    u32 reg_cmmb_gpio0_pe             :1 ; /// None
    u32 reg_cmmb_gpio0_ps             :1 ; /// None
    u32 reg_cmmb_gpio0_drv            :1 ; /// None
    u32 :1 ; /// [0x00]
    u32 reg_cmmb_gpio1_in             :1 ; /// None
    u32 reg_cmmb_gpio1_out            :1 ; /// None
    u32 reg_cmmb_gpio1_oen            :1 ; /// None
    u32 :1 ; /// [0x00]
    u32 reg_cmmb_gpio1_pe             :1 ; /// None
    u32 reg_cmmb_gpio1_ps             :1 ; /// None
    u32 reg_cmmb_gpio1_drv            :1 ; /// None
    u32 :17; /// [0x00]
    /* [0x01] */
    u32 reg_cmmb_gpio2_in             :1 ; /// None
    u32 reg_cmmb_gpio2_out            :1 ; /// None
    u32 reg_cmmb_gpio2_oen            :1 ; /// None
    u32 :1 ; /// [0x01]
    u32 reg_cmmb_gpio2_pe             :1 ; /// None
    u32 reg_cmmb_gpio2_ps             :1 ; /// None
    u32 reg_cmmb_gpio2_drv            :1 ; /// None
    u32 :1 ; /// [0x01]
    u32 reg_gpio_sp_in                :1 ; /// None
    u32 reg_gpio_sp_out               :1 ; /// None
    u32 reg_gpio_sp_oen               :1 ; /// None
    u32 :1 ; /// [0x01]
    u32 reg_gpio_sp_pe                :1 ; /// None
    u32 reg_gpio_sp_ps                :1 ; /// None
    u32 reg_gpio_sp_drv               :1 ; /// None
    u32 :17; /// [0x01]
    /* [0x02] */
    u32 reg_int_gpio0_in              :1 ; /// None
    u32 reg_int_gpio0_out             :1 ; /// None
    u32 reg_int_gpio0_oen             :1 ; /// None
    u32 :1 ; /// [0x02]
    u32 reg_int_gpio0_pe              :1 ; /// None
    u32 reg_int_gpio0_ps              :1 ; /// None
    u32 reg_int_gpio0_drv             :1 ; /// None
    u32 :1 ; /// [0x02]
    u32 reg_int_gpio1_in              :1 ; /// None
    u32 reg_int_gpio1_out             :1 ; /// None
    u32 reg_int_gpio1_oen             :1 ; /// None
    u32 :1 ; /// [0x02]
    u32 reg_int_gpio1_pe              :1 ; /// None
    u32 reg_int_gpio1_ps              :1 ; /// None
    u32 reg_int_gpio1_drv             :1 ; /// None
    u32 :17; /// [0x02]
    /* [0x03] */
    u32 reg_bt_gpio0_in               :1 ; /// None
    u32 reg_bt_gpio0_out              :1 ; /// None
    u32 reg_bt_gpio0_oen              :1 ; /// None
    u32 :1 ; /// [0x03]
    u32 reg_bt_gpio0_pe               :1 ; /// None
    u32 reg_bt_gpio0_ps               :1 ; /// None
    u32 reg_bt_gpio0_drv              :1 ; /// None
    u32 :1 ; /// [0x03]
    u32 reg_bt_gpio1_in               :1 ; /// None
    u32 reg_bt_gpio1_out              :1 ; /// None
    u32 reg_bt_gpio1_oen              :1 ; /// None
    u32 :1 ; /// [0x03]
    u32 reg_bt_gpio1_pe               :1 ; /// None
    u32 reg_bt_gpio1_ps               :1 ; /// None
    u32 reg_bt_gpio1_drv              :1 ; /// None
    u32 :17; /// [0x03]
    /* [0x04] */
    u32 reg_bt_gpio2_in               :1 ; /// None
    u32 reg_bt_gpio2_out              :1 ; /// None
    u32 reg_bt_gpio2_oen              :1 ; /// None
    u32 :1 ; /// [0x04]
    u32 reg_bt_gpio2_pe               :1 ; /// None
    u32 reg_bt_gpio2_ps               :1 ; /// None
    u32 reg_bt_gpio2_drv              :1 ; /// None
    u32 :1 ; /// [0x04]
    u32 reg_gpio_sp2_in               :1 ; /// None
    u32 reg_gpio_sp2_out              :1 ; /// None
    u32 reg_gpio_sp2_oen              :1 ; /// None
    u32 :1 ; /// [0x04]
    u32 reg_gpio_sp2_pe               :1 ; /// None
    u32 reg_gpio_sp2_ps               :1 ; /// None
    u32 reg_gpio_sp2_drv              :1 ; /// None
    u32 :17; /// [0x04]
    /* [0x05] */
    u32 reg_gpio_nc0_in               :1 ; /// None
    u32 reg_gpio_nc0_out              :1 ; /// None
    u32 reg_gpio_nc0_oen              :1 ; /// None
    u32 :1 ; /// [0x05]
    u32 reg_gpio_nc0_pe               :1 ; /// None
    u32 reg_gpio_nc0_ps               :1 ; /// NC pad; pull-up for bonding option usage
    u32 reg_gpio_nc0_drv              :1 ; /// None
    u32 reg_gpio_nc0_mode             :1 ; /// None
    u32 reg_gpio_nc1_in               :1 ; /// None
    u32 reg_gpio_nc1_out              :1 ; /// None
    u32 reg_gpio_nc1_oen              :1 ; /// None
    u32 :1 ; /// [0x05]
    u32 reg_gpio_nc1_pe               :1 ; /// None
    u32 reg_gpio_nc1_ps               :1 ; /// NC pad; pull-up for bonding option usage
    u32 reg_gpio_nc1_drv              :1 ; /// None
    u32 reg_gpio_nc1_mode             :1 ; /// None
    u32 :16; /// [0x05]
    /* [0x06] */
    u32 reg_gpio_nc2_in               :1 ; /// None
    u32 reg_gpio_nc2_out              :1 ; /// None
    u32 reg_gpio_nc2_oen              :1 ; /// None
    u32 :1 ; /// [0x06]
    u32 reg_gpio_nc2_pe               :1 ; /// None
    u32 reg_gpio_nc2_ps               :1 ; /// NC pad; pull-up for bonding option usage
    u32 reg_gpio_nc2_drv              :1 ; /// None
    u32 reg_gpio_nc2_mode             :1 ; /// None
    u32 reg_gpio_nc3_in               :1 ; /// None
    u32 reg_gpio_nc3_out              :1 ; /// None
    u32 reg_gpio_nc3_oen              :1 ; /// None
    u32 :1 ; /// [0x06]
    u32 reg_gpio_nc3_pe               :1 ; /// None
    u32 reg_gpio_nc3_ps               :1 ; /// NC pad; pull-up for bonding option usage
    u32 reg_gpio_nc3_drv              :1 ; /// None
    u32 reg_gpio_nc3_mode             :1 ; /// None
    u32 :16; /// [0x06]
    /* [0x07] */
    u32 reg_gpio_nc4_in               :1 ; /// None
    u32 reg_gpio_nc4_out              :1 ; /// None
    u32 reg_gpio_nc4_oen              :1 ; /// None
    u32 :1 ; /// [0x07]
    u32 reg_gpio_nc4_pe               :1 ; /// None
    u32 reg_gpio_nc4_ps               :1 ; /// NC pad; pull-up for bonding option usage
    u32 reg_gpio_nc4_drv              :1 ; /// None
    u32 reg_gpio_nc4_mode             :1 ; /// None
    u32 reg_gpio_nc5_in               :1 ; /// None
    u32 reg_gpio_nc5_out              :1 ; /// None
    u32 reg_gpio_nc5_oen              :1 ; /// None
    u32 :1 ; /// [0x07]
    u32 reg_gpio_nc5_pe               :1 ; /// None
    u32 reg_gpio_nc5_ps               :1 ; /// NC pad; pull-up for bonding option usage
    u32 reg_gpio_nc5_drv              :1 ; /// None
    u32 reg_gpio_nc5_mode             :1 ; /// None
    u32 :16; /// [0x07]
    u32 :32; /// [0x08]
    u32 :32; /// [0x09]
    u32 :32; /// [0x0A]
    u32 :32; /// [0x0B]
    u32 :32; /// [0x0C]
    u32 :32; /// [0x0D]
    u32 :32; /// [0x0E]
    u32 :32; /// [0x0F]
    u32 :32; /// [0x10]
    u32 :32; /// [0x11]
    u32 :32; /// [0x12]
    u32 :32; /// [0x13]
    u32 :32; /// [0x14]
    u32 :32; /// [0x15]
    u32 :32; /// [0x16]
    u32 :32; /// [0x17]
    u32 :32; /// [0x18]
    u32 :32; /// [0x19]
    u32 :32; /// [0x1A]
    u32 :32; /// [0x1B]
    u32 :32; /// [0x1C]
    u32 :32; /// [0x1D]
    u32 :32; /// [0x1E]
    u32 :32; /// [0x1F]
    u32 :32; /// [0x20]
    u32 :32; /// [0x21]
    /* [0x22] */
    u32 reg_rf_gpio0_in               :1 ; /// None
    u32 reg_rf_gpio0_out              :1 ; /// None
    u32 reg_rf_gpio0_oen              :1 ; /// None
    u32 :1 ; /// [0x22]
    u32 reg_rf_gpio0_pe               :1 ; /// None
    u32 reg_rf_gpio0_ps               :1 ; /// None
    u32 reg_rf_gpio0_drv              :1 ; /// None
    u32 reg_rf_gpio0_mode             :1 ; /// None
    u32 reg_rf_gpio1_in               :1 ; /// None
    u32 reg_rf_gpio1_out              :1 ; /// None
    u32 reg_rf_gpio1_oen              :1 ; /// None
    u32 :1 ; /// [0x22]
    u32 reg_rf_gpio1_pe               :1 ; /// None
    u32 reg_rf_gpio1_ps               :1 ; /// None
    u32 reg_rf_gpio1_drv              :1 ; /// None
    u32 reg_rf_gpio1_mode             :1 ; /// None
    u32 :16; /// [0x22]
    /* [0x23] */
    u32 reg_rf_gpio2_in               :1 ; /// None
    u32 reg_rf_gpio2_out              :1 ; /// None
    u32 reg_rf_gpio2_oen              :1 ; /// None
    u32 :1 ; /// [0x23]
    u32 reg_rf_gpio2_pe               :1 ; /// None
    u32 reg_rf_gpio2_ps               :1 ; /// None
    u32 reg_rf_gpio2_drv              :1 ; /// None
    u32 reg_rf_gpio2_mode             :1 ; /// None
    u32 reg_rf_gpio3_in               :1 ; /// None
    u32 reg_rf_gpio3_out              :1 ; /// None
    u32 reg_rf_gpio3_oen              :1 ; /// None
    u32 :1 ; /// [0x23]
    u32 reg_rf_gpio3_pe               :1 ; /// None
    u32 reg_rf_gpio3_ps               :1 ; /// None
    u32 reg_rf_gpio3_drv              :1 ; /// None
    u32 reg_rf_gpio3_mode             :1 ; /// None
    u32 :16; /// [0x23]
    /* [0x24] */
    u32 reg_rf_gpio4_in               :1 ; /// None
    u32 reg_rf_gpio4_out              :1 ; /// None
    u32 reg_rf_gpio4_oen              :1 ; /// None
    u32 :1 ; /// [0x24]
    u32 reg_rf_gpio4_pe               :1 ; /// None
    u32 reg_rf_gpio4_ps               :1 ; /// None
    u32 reg_rf_gpio4_drv              :1 ; /// None
    u32 reg_rf_gpio4_mode             :1 ; /// None
    u32 reg_rf_gpio5_in               :1 ; /// None
    u32 reg_rf_gpio5_out              :1 ; /// None
    u32 reg_rf_gpio5_oen              :1 ; /// None
    u32 :1 ; /// [0x24]
    u32 reg_rf_gpio5_pe               :1 ; /// None
    u32 reg_rf_gpio5_ps               :1 ; /// None
    u32 reg_rf_gpio5_drv              :1 ; /// None
    u32 reg_rf_gpio5_mode             :1 ; /// None
    u32 :16; /// [0x24]
    /* [0x25] */
    u32 reg_rf_gpio6_in               :1 ; /// None
    u32 reg_rf_gpio6_out              :1 ; /// None
    u32 reg_rf_gpio6_oen              :1 ; /// None
    u32 :1 ; /// [0x25]
    u32 reg_rf_gpio6_pe               :1 ; /// None
    u32 reg_rf_gpio6_ps               :1 ; /// None
    u32 reg_rf_gpio6_drv              :1 ; /// None
    u32 reg_rf_gpio6_mode             :1 ; /// None
    u32 reg_rf_gpio7_in               :1 ; /// None
    u32 reg_rf_gpio7_out              :1 ; /// None
    u32 reg_rf_gpio7_oen              :1 ; /// None
    u32 :1 ; /// [0x25]
    u32 reg_rf_gpio7_pe               :1 ; /// None
    u32 reg_rf_gpio7_ps               :1 ; /// None
    u32 reg_rf_gpio7_drv              :1 ; /// None
    u32 reg_rf_gpio7_mode             :1 ; /// None
    u32 :16; /// [0x25]
    u32 :32; /// [0x26]
    u32 :32; /// [0x27]
    u32 :32; /// [0x28]
    u32 :32; /// [0x29]
    u32 :32; /// [0x2A]
    u32 :32; /// [0x2B]
    u32 :32; /// [0x2C]
    u32 :32; /// [0x2D]
    u32 :32; /// [0x2E]
    u32 :32; /// [0x2F]
    /* [0x30] */
    u32 reg_force_gpio_pw             :16; /// FT test
    u32 :16; /// [0x30]
    /* [0x31] */
    u32 reg_force_hiz                 :1 ; /// FT test
    u32 reg_force_pe                  :1 ; /// FT test
    u32 reg_force_ps                  :1 ; /// FT test
    u32 reg_force_gpio_mode           :1 ; /// FT test
    u32 :28; /// [0x31]
    /* [0x32] */
    u32 reg_emi_gpio_pe_actual_0      :16; /// actual reg_emi_gpio_pe
    u32 :16; /// [0x32]
    u32 reg_emi_gpio_pe_actual_1      :16; /// @see reg_emi_gpio_pe_actual_0
    u32 :16; /// [0x32]
    u32 reg_emi_gpio_pe_actual_2      :16; /// @see reg_emi_gpio_pe_actual_0
    u32 :16; /// [0x32]
    u32 reg_emi_gpio_pe_actual_3      :4 ; /// @see reg_emi_gpio_pe_actual_0
    u32 :28; /// [0x35]
    /* [0x36] */
    u32 reg_emi_gpio_ps_actual        :16; /// actual reg_emi_gpio_ps
    u32 :16; /// [0x36]
    /* [0x37] */
    u32 reg_emi_gpio_pw               :16; /// debug use only; password to use emi gpio
    u32 :16; /// [0x37]
    /* [0x38] */
    u32 reg_mcp_test_eco_mode         :2 ; /// reg_mcp_test_eco_mode
    u32 reg_fuart_eco_mode            :2 ; /// reg_fuart_eco_mode
    u32 reg_dbg_uart_eco_mode         :2 ; /// reg_dbg_uart_eco_mode
    u32 reg_debug_use0                :2 ; /// debug use only
    u32 reg_pwm_in_eco_mode           :3 ; /// reg_pwm_in_eco_mode
    u32 reg_debug_use0_1              :4 ; /// debug use only
    u32 reg_uart_dl_high_speed        :1 ; /// PAD_U0TXD open-drain or push-pull
    u32 :16; /// [0x38]
    /* [0x39] */
    u32 reg_debug_use1                :16; /// debug use only
    u32 :16; /// [0x39]
    /* [0x3A] */
    u32 reg_arm_speed_binning0        :16; /// used for arm speed binning; debug use only
    u32 :16; /// [0x3A]
    /* [0x3B] */
    u32 reg_arm_speed_binning1        :16; /// used for arm speed binning; debug use only
    u32 :16; /// [0x3B]
    /* [0x3C] */
    u32 reg_arm_speed_binning2        :16; /// used for arm speed binning; debug use only
    u32 :16; /// [0x3C]
    /* [0x3D] */
    u32 reg_arm_speed_binning3        :16; /// used for arm speed binning; debug use only
    u32 :16; /// [0x3D]
    /* [0x3E] */
    u32 reg_debug_use2                :16; /// debug use only
    u32 :16; /// [0x3E]
    /* [0x3F] */
    u32 reg_pad_u0txd                 :1 ; /// u0txd pad status
    u32 :31; /// [0x3F]
} KeGpioCtrl1_t;

typedef struct KeGpioCtrl0_s
{
    /* [0x00] */
    u32 reg_btif_gpio0_in             :1 ; /// None
    u32 reg_btif_gpio0_out            :1 ; /// None
    u32 reg_btif_gpio0_oen            :1 ; /// None
    u32 :1 ; /// [0x00]
    u32 reg_btif_gpio0_pe             :1 ; /// None
    u32 reg_btif_gpio0_ps             :1 ; /// None
    u32 reg_btif_gpio0_drv            :1 ; /// None
    u32 reg_btif_gpio0_mode           :1 ; /// None
    u32 reg_btif_gpio1_in             :1 ; /// None
    u32 reg_btif_gpio1_out            :1 ; /// None
    u32 reg_btif_gpio1_oen            :1 ; /// None
    u32 :1 ; /// [0x00]
    u32 reg_btif_gpio1_pe             :1 ; /// None
    u32 reg_btif_gpio1_ps             :1 ; /// None
    u32 reg_btif_gpio1_drv            :1 ; /// None
    u32 reg_btif_gpio1_mode           :1 ; /// None
    u32 :16; /// [0x00]
    /* [0x01] */
    u32 reg_btif_gpio2_in             :1 ; /// None
    u32 reg_btif_gpio2_out            :1 ; /// None
    u32 reg_btif_gpio2_oen            :1 ; /// None
    u32 :1 ; /// [0x01]
    u32 reg_btif_gpio2_pe             :1 ; /// None
    u32 reg_btif_gpio2_ps             :1 ; /// None
    u32 reg_btif_gpio2_drv            :1 ; /// None
    u32 reg_btif_gpio2_mode           :1 ; /// None
    u32 reg_btif_gpio3_in             :1 ; /// None
    u32 reg_btif_gpio3_out            :1 ; /// None
    u32 reg_btif_gpio3_oen            :1 ; /// None
    u32 :1 ; /// [0x01]
    u32 reg_btif_gpio3_pe             :1 ; /// None
    u32 reg_btif_gpio3_ps             :1 ; /// None
    u32 reg_btif_gpio3_drv            :1 ; /// None
    u32 reg_btif_gpio3_mode           :1 ; /// None
    u32 :16; /// [0x01]
    /* [0x02] */
    u32 reg_btif_gpio4_in             :1 ; /// None
    u32 reg_btif_gpio4_out            :1 ; /// None
    u32 reg_btif_gpio4_oen            :1 ; /// None
    u32 :1 ; /// [0x02]
    u32 reg_btif_gpio4_pe             :1 ; /// None
    u32 reg_btif_gpio4_ps             :1 ; /// None
    u32 reg_btif_gpio4_drv            :1 ; /// None
    u32 reg_btif_gpio4_mode           :1 ; /// None
    u32 reg_btif_gpio5_in             :1 ; /// None
    u32 reg_btif_gpio5_out            :1 ; /// None
    u32 reg_btif_gpio5_oen            :1 ; /// None
    u32 :1 ; /// [0x02]
    u32 reg_btif_gpio5_pe             :1 ; /// None
    u32 reg_btif_gpio5_ps             :1 ; /// None
    u32 reg_btif_gpio5_drv            :1 ; /// None
    u32 reg_btif_gpio5_mode           :1 ; /// None
    u32 :16; /// [0x02]
    /* [0x03] */
    u32 reg_btif_gpio6_in             :1 ; /// None
    u32 reg_btif_gpio6_out            :1 ; /// None
    u32 reg_btif_gpio6_oen            :1 ; /// None
    u32 :1 ; /// [0x03]
    u32 reg_btif_gpio6_pe             :1 ; /// None
    u32 reg_btif_gpio6_ps             :1 ; /// None
    u32 reg_btif_gpio6_drv            :1 ; /// None
    u32 reg_btif_gpio6_mode           :1 ; /// None
    u32 reg_btif_gpio7_in             :1 ; /// None
    u32 reg_btif_gpio7_out            :1 ; /// None
    u32 reg_btif_gpio7_oen            :1 ; /// None
    u32 :1 ; /// [0x03]
    u32 reg_btif_gpio7_pe             :1 ; /// None
    u32 reg_btif_gpio7_ps             :1 ; /// None
    u32 reg_btif_gpio7_drv            :1 ; /// None
    u32 reg_btif_gpio7_mode           :1 ; /// None
    u32 :16; /// [0x03]
    /* [0x04] */
    u32 reg_mpif_gpio0_in             :1 ; /// None
    u32 reg_mpif_gpio0_out            :1 ; /// None
    u32 reg_mpif_gpio0_oen            :1 ; /// None
    u32 :1 ; /// [0x04]
    u32 reg_mpif_gpio0_pe             :1 ; /// None
    u32 reg_mpif_gpio0_ps             :1 ; /// None
    u32 reg_mpif_gpio0_drv            :1 ; /// None
    u32 reg_mpif_gpio0_mode           :1 ; /// None
    u32 reg_mpif_gpio1_in             :1 ; /// None
    u32 reg_mpif_gpio1_out            :1 ; /// None
    u32 reg_mpif_gpio1_oen            :1 ; /// None
    u32 :1 ; /// [0x04]
    u32 reg_mpif_gpio1_pe             :1 ; /// None
    u32 reg_mpif_gpio1_ps             :1 ; /// None
    u32 reg_mpif_gpio1_drv            :1 ; /// None
    u32 reg_mpif_gpio1_mode           :1 ; /// None
    u32 :16; /// [0x04]
    /* [0x05] */
    u32 reg_mpif_gpio2_in             :1 ; /// None
    u32 reg_mpif_gpio2_out            :1 ; /// None
    u32 reg_mpif_gpio2_oen            :1 ; /// None
    u32 :1 ; /// [0x05]
    u32 reg_mpif_gpio2_pe             :1 ; /// None
    u32 reg_mpif_gpio2_ps             :1 ; /// None
    u32 reg_mpif_gpio2_drv            :1 ; /// None
    u32 reg_mpif_gpio2_mode           :1 ; /// None
    u32 reg_mpif_gpio3_in             :1 ; /// None
    u32 reg_mpif_gpio3_out            :1 ; /// None
    u32 reg_mpif_gpio3_oen            :1 ; /// None
    u32 :1 ; /// [0x05]
    u32 reg_mpif_gpio3_pe             :1 ; /// None
    u32 reg_mpif_gpio3_ps             :1 ; /// None
    u32 reg_mpif_gpio3_drv            :1 ; /// None
    u32 reg_mpif_gpio3_mode           :1 ; /// None
    u32 :16; /// [0x05]
    /* [0x06] */
    u32 reg_mpif_gpio4_in             :1 ; /// None
    u32 reg_mpif_gpio4_out            :1 ; /// None
    u32 reg_mpif_gpio4_oen            :1 ; /// None
    u32 :1 ; /// [0x06]
    u32 reg_mpif_gpio4_pe             :1 ; /// None
    u32 reg_mpif_gpio4_ps             :1 ; /// None
    u32 reg_mpif_gpio4_drv            :1 ; /// None
    u32 reg_mpif_gpio4_mode           :1 ; /// None
    u32 reg_mpif_gpio5_in             :1 ; /// None
    u32 reg_mpif_gpio5_out            :1 ; /// None
    u32 reg_mpif_gpio5_oen            :1 ; /// None
    u32 :1 ; /// [0x06]
    u32 reg_mpif_gpio5_pe             :1 ; /// None
    u32 reg_mpif_gpio5_ps             :1 ; /// None
    u32 reg_mpif_gpio5_drv            :1 ; /// None
    u32 reg_mpif_gpio5_mode           :1 ; /// None
    u32 :16; /// [0x06]
    /* [0x07] */
    u32 reg_mpif_gpio6_in             :1 ; /// None
    u32 reg_mpif_gpio6_out            :1 ; /// None
    u32 reg_mpif_gpio6_oen            :1 ; /// None
    u32 :1 ; /// [0x07]
    u32 reg_mpif_gpio6_pe             :1 ; /// None
    u32 reg_mpif_gpio6_ps             :1 ; /// None
    u32 reg_mpif_gpio6_drv            :1 ; /// None
    u32 reg_mpif_gpio6_mode           :1 ; /// None
    u32 reg_mpif_gpio7_in             :1 ; /// None
    u32 reg_mpif_gpio7_out            :1 ; /// None
    u32 reg_mpif_gpio7_oen            :1 ; /// None
    u32 :1 ; /// [0x07]
    u32 reg_mpif_gpio7_pe             :1 ; /// None
    u32 reg_mpif_gpio7_ps             :1 ; /// None
    u32 reg_mpif_gpio7_drv            :1 ; /// None
    u32 reg_mpif_gpio7_mode           :1 ; /// None
    u32 :16; /// [0x07]
    /* [0x08] */
    u32 reg_sim1_gpio0_in             :1 ; /// None
    u32 reg_sim1_gpio0_out            :1 ; /// None
    u32 reg_sim1_gpio0_oen            :1 ; /// None
    u32 :3 ; /// [0x08]
    u32 reg_sim1_gpio0_drv            :1 ; /// None
    u32 reg_sim1_gpio0_mode           :1 ; /// None
    u32 reg_sim1_gpio1_in             :1 ; /// None
    u32 reg_sim1_gpio1_out            :1 ; /// None
    u32 reg_sim1_gpio1_oen            :1 ; /// None
    u32 :3 ; /// [0x08]
    u32 reg_sim1_gpio1_drv            :1 ; /// None
    u32 reg_sim1_gpio1_mode           :1 ; /// None
    u32 :16; /// [0x08]
    /* [0x09] */
    u32 reg_sim1_gpio2_in             :1 ; /// None
    u32 reg_sim1_gpio2_out            :1 ; /// None
    u32 reg_sim1_gpio2_oen            :1 ; /// None
    u32 :3 ; /// [0x09]
    u32 reg_sim1_gpio2_drv            :1 ; /// None
    u32 reg_sim1_gpio2_mode           :1 ; /// None
    u32 reg_sim2_gpio0_in             :1 ; /// None
    u32 reg_sim2_gpio0_out            :1 ; /// None
    u32 reg_sim2_gpio0_oen            :1 ; /// None
    u32 :3 ; /// [0x09]
    u32 reg_sim2_gpio0_drv            :1 ; /// None
    u32 reg_sim2_gpio0_mode           :1 ; /// None
    u32 :16; /// [0x09]
    /* [0x0A] */
    u32 reg_sim2_gpio1_in             :1 ; /// None
    u32 reg_sim2_gpio1_out            :1 ; /// None
    u32 reg_sim2_gpio1_oen            :1 ; /// None
    u32 :3 ; /// [0x0A]
    u32 reg_sim2_gpio1_drv            :1 ; /// None
    u32 reg_sim2_gpio1_mode           :1 ; /// None
    u32 reg_sim2_gpio2_in             :1 ; /// None
    u32 reg_sim2_gpio2_out            :1 ; /// None
    u32 reg_sim2_gpio2_oen            :1 ; /// None
    u32 :3 ; /// [0x0A]
    u32 reg_sim2_gpio2_drv            :1 ; /// None
    u32 reg_sim2_gpio2_mode           :1 ; /// None
    u32 :16; /// [0x0A]
    /* [0x0B] */
    u32 reg_col_gpio0_in              :1 ; /// None
    u32 reg_col_gpio0_out             :1 ; /// None
    u32 reg_col_gpio0_oen             :1 ; /// None
    u32 :1 ; /// [0x0B]
    u32 reg_col_gpio0_pe              :1 ; /// None
    u32 reg_col_gpio0_ps              :1 ; /// None
    u32 reg_col_gpio0_drv             :1 ; /// None
    u32 reg_col_gpio0_mode            :1 ; /// None
    u32 reg_col_gpio1_in              :1 ; /// None
    u32 reg_col_gpio1_out             :1 ; /// None
    u32 reg_col_gpio1_oen             :1 ; /// None
    u32 :1 ; /// [0x0B]
    u32 reg_col_gpio1_pe              :1 ; /// None
    u32 reg_col_gpio1_ps              :1 ; /// None
    u32 reg_col_gpio1_drv             :1 ; /// None
    u32 reg_col_gpio1_mode            :1 ; /// None
    u32 :16; /// [0x0B]
    /* [0x0C] */
    u32 reg_col_gpio2_in              :1 ; /// None
    u32 reg_col_gpio2_out             :1 ; /// None
    u32 reg_col_gpio2_oen             :1 ; /// None
    u32 :1 ; /// [0x0C]
    u32 reg_col_gpio2_pe              :1 ; /// None
    u32 reg_col_gpio2_ps              :1 ; /// None
    u32 reg_col_gpio2_drv             :1 ; /// None
    u32 reg_col_gpio2_mode            :1 ; /// None
    u32 reg_col_gpio3_in              :1 ; /// None
    u32 reg_col_gpio3_out             :1 ; /// None
    u32 reg_col_gpio3_oen             :1 ; /// None
    u32 :1 ; /// [0x0C]
    u32 reg_col_gpio3_pe              :1 ; /// None
    u32 reg_col_gpio3_ps              :1 ; /// None
    u32 reg_col_gpio3_drv             :1 ; /// None
    u32 reg_col_gpio3_mode            :1 ; /// None
    u32 :16; /// [0x0C]
    /* [0x0D] */
    u32 reg_col_gpio4_in              :1 ; /// None
    u32 reg_col_gpio4_out             :1 ; /// None
    u32 reg_col_gpio4_oen             :1 ; /// None
    u32 :1 ; /// [0x0D]
    u32 reg_col_gpio4_pe              :1 ; /// None
    u32 reg_col_gpio4_ps              :1 ; /// None
    u32 reg_col_gpio4_drv             :1 ; /// None
    u32 reg_col_gpio4_mode            :1 ; /// None
    u32 reg_col_gpio5_in              :1 ; /// None
    u32 reg_col_gpio5_out             :1 ; /// None
    u32 reg_col_gpio5_oen             :1 ; /// None
    u32 :1 ; /// [0x0D]
    u32 reg_col_gpio5_pe              :1 ; /// None
    u32 reg_col_gpio5_ps              :1 ; /// None
    u32 reg_col_gpio5_drv             :1 ; /// None
    u32 reg_col_gpio5_mode            :1 ; /// None
    u32 :16; /// [0x0D]
    /* [0x0E] */
    u32 reg_col_gpio6_in              :1 ; /// None
    u32 reg_col_gpio6_out             :1 ; /// None
    u32 reg_col_gpio6_oen             :1 ; /// None
    u32 :1 ; /// [0x0E]
    u32 reg_col_gpio6_pe              :1 ; /// None
    u32 reg_col_gpio6_ps              :1 ; /// None
    u32 reg_col_gpio6_drv             :1 ; /// None
    u32 reg_col_gpio6_mode            :1 ; /// None
    u32 :24; /// [0x0E]
    /* [0x0F] */
    u32 reg_row_gpio0_in              :1 ; /// None
    u32 reg_row_gpio0_out             :1 ; /// None
    u32 reg_row_gpio0_oen             :1 ; /// None
    u32 :1 ; /// [0x0F]
    u32 reg_row_gpio0_pe              :1 ; /// None
    u32 reg_row_gpio0_ps              :1 ; /// None
    u32 reg_row_gpio0_drv             :1 ; /// None
    u32 reg_row_gpio0_mode            :1 ; /// None
    u32 reg_row_gpio1_in              :1 ; /// None
    u32 reg_row_gpio1_out             :1 ; /// None
    u32 reg_row_gpio1_oen             :1 ; /// None
    u32 :1 ; /// [0x0F]
    u32 reg_row_gpio1_pe              :1 ; /// None
    u32 reg_row_gpio1_ps              :1 ; /// None
    u32 reg_row_gpio1_drv             :1 ; /// None
    u32 reg_row_gpio1_mode            :1 ; /// None
    u32 :16; /// [0x0F]
    /* [0x10] */
    u32 reg_row_gpio2_in              :1 ; /// None
    u32 reg_row_gpio2_out             :1 ; /// None
    u32 reg_row_gpio2_oen             :1 ; /// None
    u32 :1 ; /// [0x10]
    u32 reg_row_gpio2_pe              :1 ; /// None
    u32 reg_row_gpio2_ps              :1 ; /// None
    u32 reg_row_gpio2_drv             :1 ; /// None
    u32 reg_row_gpio2_mode            :1 ; /// None
    u32 reg_row_gpio3_in              :1 ; /// None
    u32 reg_row_gpio3_out             :1 ; /// None
    u32 reg_row_gpio3_oen             :1 ; /// None
    u32 :1 ; /// [0x10]
    u32 reg_row_gpio3_pe              :1 ; /// None
    u32 reg_row_gpio3_ps              :1 ; /// None
    u32 reg_row_gpio3_drv             :1 ; /// None
    u32 reg_row_gpio3_mode            :1 ; /// None
    u32 :16; /// [0x10]
    /* [0x11] */
    u32 reg_row_gpio4_in              :1 ; /// None
    u32 reg_row_gpio4_out             :1 ; /// None
    u32 reg_row_gpio4_oen             :1 ; /// None
    u32 :1 ; /// [0x11]
    u32 reg_row_gpio4_pe              :1 ; /// None
    u32 reg_row_gpio4_ps              :1 ; /// None
    u32 reg_row_gpio4_drv             :1 ; /// None
    u32 reg_row_gpio4_mode            :1 ; /// None
    u32 reg_row_gpio5_in              :1 ; /// None
    u32 reg_row_gpio5_out             :1 ; /// None
    u32 reg_row_gpio5_oen             :1 ; /// None
    u32 :1 ; /// [0x11]
    u32 reg_row_gpio5_pe              :1 ; /// None
    u32 reg_row_gpio5_ps              :1 ; /// None
    u32 reg_row_gpio5_drv             :1 ; /// None
    u32 reg_row_gpio5_mode            :1 ; /// None
    u32 :16; /// [0x11]
    /* [0x12] */
    u32 reg_sd_gpio0_in               :1 ; /// None
    u32 reg_sd_gpio0_out              :1 ; /// None
    u32 reg_sd_gpio0_oen              :1 ; /// None
    u32 :1 ; /// [0x12]
    u32 reg_sd_gpio0_pe               :1 ; /// None
    u32 reg_sd_gpio0_ps               :1 ; /// None
    u32 reg_sd_gpio0_drv              :1 ; /// None
    u32 reg_sd_gpio0_mode             :1 ; /// None
    u32 reg_sd_gpio1_in               :1 ; /// None
    u32 reg_sd_gpio1_out              :1 ; /// None
    u32 reg_sd_gpio1_oen              :1 ; /// None
    u32 :1 ; /// [0x12]
    u32 reg_sd_gpio1_pe               :1 ; /// None
    u32 reg_sd_gpio1_ps               :1 ; /// None
    u32 reg_sd_gpio1_drv              :1 ; /// None
    u32 reg_sd_gpio1_mode             :1 ; /// None
    u32 :16; /// [0x12]
    /* [0x13] */
    u32 reg_sd_gpio2_in               :1 ; /// None
    u32 reg_sd_gpio2_out              :1 ; /// None
    u32 reg_sd_gpio2_oen              :1 ; /// None
    u32 :1 ; /// [0x13]
    u32 reg_sd_gpio2_pe               :1 ; /// None
    u32 reg_sd_gpio2_ps               :1 ; /// None
    u32 reg_sd_gpio2_drv              :1 ; /// None
    u32 reg_sd_gpio2_mode             :1 ; /// None
    u32 reg_sd_gpio3_in               :1 ; /// None
    u32 reg_sd_gpio3_out              :1 ; /// None
    u32 reg_sd_gpio3_oen              :1 ; /// None
    u32 :1 ; /// [0x13]
    u32 reg_sd_gpio3_pe               :1 ; /// None
    u32 reg_sd_gpio3_ps               :1 ; /// None
    u32 reg_sd_gpio3_drv              :1 ; /// None
    u32 reg_sd_gpio3_mode             :1 ; /// None
    u32 :16; /// [0x13]
    /* [0x14] */
    u32 reg_sd_gpio4_in               :1 ; /// None
    u32 reg_sd_gpio4_out              :1 ; /// None
    u32 reg_sd_gpio4_oen              :1 ; /// None
    u32 :1 ; /// [0x14]
    u32 reg_sd_gpio4_pe               :1 ; /// None
    u32 reg_sd_gpio4_ps               :1 ; /// None
    u32 reg_sd_gpio4_drv              :1 ; /// None
    u32 reg_sd_gpio4_mode             :1 ; /// None
    u32 reg_sd_gpio5_in               :1 ; /// None
    u32 reg_sd_gpio5_out              :1 ; /// None
    u32 reg_sd_gpio5_oen              :1 ; /// None
    u32 :1 ; /// [0x14]
    u32 reg_sd_gpio5_pe               :1 ; /// None
    u32 reg_sd_gpio5_ps               :1 ; /// None
    u32 reg_sd_gpio5_drv              :1 ; /// None
    u32 reg_sd_gpio5_mode             :1 ; /// None
    u32 :16; /// [0x14]
    /* [0x15] */
    u32 reg_sd_gpio6_in               :1 ; /// None
    u32 reg_sd_gpio6_out              :1 ; /// None
    u32 reg_sd_gpio6_oen              :1 ; /// None
    u32 :1 ; /// [0x15]
    u32 reg_sd_gpio6_pe               :1 ; /// None
    u32 reg_sd_gpio6_ps               :1 ; /// None
    u32 reg_sd_gpio6_drv              :1 ; /// None
    u32 reg_sd_gpio6_mode             :1 ; /// None
    u32 :24; /// [0x15]
    /* [0x16] */
    u32 reg_i2s_gpio0_in              :1 ; /// None
    u32 reg_i2s_gpio0_out             :1 ; /// None
    u32 reg_i2s_gpio0_oen             :1 ; /// None
    u32 :1 ; /// [0x16]
    u32 reg_i2s_gpio0_pe              :1 ; /// None
    u32 reg_i2s_gpio0_ps              :1 ; /// None
    u32 reg_i2s_gpio0_drv             :1 ; /// None
    u32 reg_i2s_gpio0_mode            :1 ; /// None
    u32 reg_i2s_gpio1_in              :1 ; /// None
    u32 reg_i2s_gpio1_out             :1 ; /// None
    u32 reg_i2s_gpio1_oen             :1 ; /// None
    u32 :1 ; /// [0x16]
    u32 reg_i2s_gpio1_pe              :1 ; /// None
    u32 reg_i2s_gpio1_ps              :1 ; /// None
    u32 reg_i2s_gpio1_drv             :1 ; /// None
    u32 reg_i2s_gpio1_mode            :1 ; /// None
    u32 :16; /// [0x16]
    /* [0x17] */
    u32 reg_i2s_gpio2_in              :1 ; /// None
    u32 reg_i2s_gpio2_out             :1 ; /// None
    u32 reg_i2s_gpio2_oen             :1 ; /// None
    u32 :1 ; /// [0x17]
    u32 reg_i2s_gpio2_pe              :1 ; /// None
    u32 reg_i2s_gpio2_ps              :1 ; /// None
    u32 reg_i2s_gpio2_drv             :1 ; /// None
    u32 reg_i2s_gpio2_mode            :1 ; /// None
    u32 :24; /// [0x17]
    /* [0x18] */
    u32 reg_uart_gpio0_in             :1 ; /// None
    u32 reg_uart_gpio0_out            :1 ; /// None
    u32 reg_uart_gpio0_oen            :1 ; /// None
    u32 :1 ; /// [0x18]
    u32 reg_uart_gpio0_pe             :1 ; /// None
    u32 reg_uart_gpio0_ps             :1 ; /// None
    u32 reg_uart_gpio0_drv            :1 ; /// None
    u32 reg_uart_gpio0_mode           :1 ; /// None
    u32 reg_uart_gpio1_in             :1 ; /// None
    u32 reg_uart_gpio1_out            :1 ; /// None
    u32 reg_uart_gpio1_oen            :1 ; /// None
    u32 :1 ; /// [0x18]
    u32 reg_uart_gpio1_pe             :1 ; /// None
    u32 reg_uart_gpio1_ps             :1 ; /// None
    u32 reg_uart_gpio1_drv            :1 ; /// None
    u32 reg_uart_gpio1_mode           :1 ; /// None
    u32 :16; /// [0x18]
    /* [0x19] */
    u32 reg_sys_gpio0_in              :1 ; /// None
    u32 reg_sys_gpio0_out             :1 ; /// None
    u32 reg_sys_gpio0_oen             :1 ; /// None
    u32 :1 ; /// [0x19]
    u32 reg_sys_gpio0_pe              :1 ; /// None
    u32 reg_sys_gpio0_ps              :1 ; /// None
    u32 reg_sys_gpio0_drv             :1 ; /// None
    u32 reg_sys_gpio0_mode            :1 ; /// None
    u32 reg_sys_gpio1_in              :1 ; /// None
    u32 reg_sys_gpio1_out             :1 ; /// None
    u32 reg_sys_gpio1_oen             :1 ; /// None
    u32 :1 ; /// [0x19]
    u32 reg_sys_gpio1_pe              :1 ; /// None
    u32 reg_sys_gpio1_ps              :1 ; /// None
    u32 reg_sys_gpio1_drv             :1 ; /// None
    u32 reg_sys_gpio1_mode            :1 ; /// None
    u32 :16; /// [0x19]
    /* [0x1A] */
    u32 reg_sys_gpio2_in              :1 ; /// None
    u32 reg_sys_gpio2_out             :1 ; /// None
    u32 reg_sys_gpio2_oen             :1 ; /// None
    u32 :1 ; /// [0x1A]
    u32 reg_sys_gpio2_pe              :1 ; /// None
    u32 reg_sys_gpio2_ps              :1 ; /// None
    u32 reg_sys_gpio2_drv             :1 ; /// None
    u32 reg_sys_gpio2_mode            :1 ; /// None
    u32 reg_sys_gpio3_in              :1 ; /// None
    u32 reg_sys_gpio3_out             :1 ; /// None
    u32 reg_sys_gpio3_oen             :1 ; /// None
    u32 :1 ; /// [0x1A]
    u32 reg_sys_gpio3_pe              :1 ; /// None
    u32 reg_sys_gpio3_ps              :1 ; /// None
    u32 reg_sys_gpio3_drv             :1 ; /// None
    u32 reg_sys_gpio3_mode            :1 ; /// None
    u32 :16; /// [0x1A]
    /* [0x1B] */
    u32 reg_sys_gpio4_in              :1 ; /// None
    u32 reg_sys_gpio4_out             :1 ; /// None
    u32 reg_sys_gpio4_oen             :1 ; /// None
    u32 :1 ; /// [0x1B]
    u32 reg_sys_gpio4_pe              :1 ; /// None
    u32 reg_sys_gpio4_ps              :1 ; /// NC pad; pull-up for bonding option usage
    u32 reg_sys_gpio4_drv             :1 ; /// None
    u32 reg_sys_gpio4_mode            :1 ; /// None
    u32 reg_sys_gpio5_in              :1 ; /// None
    u32 reg_sys_gpio5_out             :1 ; /// None
    u32 reg_sys_gpio5_oen             :1 ; /// None
    u32 :1 ; /// [0x1B]
    u32 reg_sys_gpio5_pe              :1 ; /// None
    u32 reg_sys_gpio5_ps              :1 ; /// None
    u32 reg_sys_gpio5_drv             :1 ; /// None
    u32 reg_sys_gpio5_mode            :1 ; /// None
    u32 :16; /// [0x1B]
    /* [0x1C] */
    u32 reg_sys_gpio6_in              :1 ; /// None
    u32 reg_sys_gpio6_out             :1 ; /// None
    u32 reg_sys_gpio6_oen             :1 ; /// None
    u32 :1 ; /// [0x1C]
    u32 reg_sys_gpio6_pe              :1 ; /// None
    u32 reg_sys_gpio6_ps              :1 ; /// None
    u32 reg_sys_gpio6_drv             :1 ; /// None
    u32 reg_sys_gpio6_mode            :1 ; /// None
    u32 reg_sys_gpio7_in              :1 ; /// None
    u32 reg_sys_gpio7_out             :1 ; /// None
    u32 reg_sys_gpio7_oen             :1 ; /// None
    u32 :1 ; /// [0x1C]
    u32 reg_sys_gpio7_pe              :1 ; /// None
    u32 reg_sys_gpio7_ps              :1 ; /// None
    u32 reg_sys_gpio7_drv             :1 ; /// None
    u32 reg_sys_gpio7_mode            :1 ; /// None
    u32 :16; /// [0x1C]
    /* [0x1D] */
    u32 reg_sys_gpio8_in              :1 ; /// None
    u32 reg_sys_gpio8_out             :1 ; /// None
    u32 reg_sys_gpio8_oen             :1 ; /// None
    u32 :1 ; /// [0x1D]
    u32 reg_sys_gpio8_pe              :1 ; /// None
    u32 reg_sys_gpio8_ps              :1 ; /// None
    u32 reg_sys_gpio8_drv             :1 ; /// None
    u32 reg_sys_gpio8_mode            :1 ; /// None
    u32 reg_sys_gpio9_in              :1 ; /// None
    u32 reg_sys_gpio9_out             :1 ; /// None
    u32 reg_sys_gpio9_oen             :1 ; /// None
    u32 :1 ; /// [0x1D]
    u32 reg_sys_gpio9_pe              :1 ; /// None
    u32 reg_sys_gpio9_ps              :1 ; /// None
    u32 reg_sys_gpio9_drv             :1 ; /// None
    u32 reg_sys_gpio9_mode            :1 ; /// None
    u32 :16; /// [0x1D]
    /* [0x1E] */
    u32 reg_sys_gpio10_in             :1 ; /// None
    u32 reg_sys_gpio10_out            :1 ; /// None
    u32 reg_sys_gpio10_oen            :1 ; /// None
    u32 :1 ; /// [0x1E]
    u32 reg_sys_gpio10_pe             :1 ; /// None
    u32 reg_sys_gpio10_ps             :1 ; /// None
    u32 reg_sys_gpio10_drv            :1 ; /// None
    u32 reg_sys_gpio10_mode           :1 ; /// None
    u32 reg_sys_gpio11_in             :1 ; /// None
    u32 reg_sys_gpio11_out            :1 ; /// None
    u32 reg_sys_gpio11_oen            :1 ; /// None
    u32 :1 ; /// [0x1E]
    u32 reg_sys_gpio11_pe             :1 ; /// None
    u32 reg_sys_gpio11_ps             :1 ; /// None
    u32 reg_sys_gpio11_drv            :1 ; /// None
    u32 reg_sys_gpio11_mode           :1 ; /// None
    u32 :16; /// [0x1E]
    /* [0x1F] */
    u32 reg_sys_gpio12_in             :1 ; /// None
    u32 reg_sys_gpio12_out            :1 ; /// None
    u32 reg_sys_gpio12_oen            :1 ; /// None
    u32 :1 ; /// [0x1F]
    u32 reg_sys_gpio12_pe             :1 ; /// None
    u32 reg_sys_gpio12_ps             :1 ; /// None
    u32 reg_sys_gpio12_drv            :1 ; /// None
    u32 reg_sys_gpio12_mode           :1 ; /// None
    u32 reg_sys_gpio13_in             :1 ; /// None
    u32 reg_sys_gpio13_out            :1 ; /// None
    u32 reg_sys_gpio13_oen            :1 ; /// None
    u32 :4 ; /// [0x1F]
    u32 reg_sys_gpio13_mode           :1 ; /// None
    u32 :16; /// [0x1F]
    /* [0x20] */
    u32 reg_sys_gpio14_in             :1 ; /// None
    u32 reg_sys_gpio14_out            :1 ; /// None
    u32 reg_sys_gpio14_oen            :1 ; /// None
    u32 :4 ; /// [0x20]
    u32 reg_sys_gpio14_mode           :1 ; /// None
    u32 reg_sys_gpio15_in             :1 ; /// None
    u32 reg_sys_gpio15_out            :1 ; /// None
    u32 reg_sys_gpio15_oen            :1 ; /// None
    u32 :4 ; /// [0x20]
    u32 reg_sys_gpio15_mode           :1 ; /// None
    u32 :16; /// [0x20]
    /* [0x21] */
    u32 reg_sys_gpio16_in             :1 ; /// None
    u32 reg_sys_gpio16_out            :1 ; /// None
    u32 reg_sys_gpio16_oen            :1 ; /// None
    u32 :4 ; /// [0x21]
    u32 reg_sys_gpio16_mode           :1 ; /// None
    u32 reg_sys_gpio17_in             :1 ; /// None
    u32 reg_sys_gpio17_out            :1 ; /// None
    u32 reg_sys_gpio17_oen            :1 ; /// None
    u32 :4 ; /// [0x21]
    u32 reg_sys_gpio17_mode           :1 ; /// None
    u32 :16; /// [0x21]
    /* [0x22] */
    u32 reg_sys_gpio18_in             :1 ; /// None
    u32 reg_sys_gpio18_out            :1 ; /// None
    u32 reg_sys_gpio18_oen            :1 ; /// None
    u32 :4 ; /// [0x22]
    u32 reg_sys_gpio18_mode           :1 ; /// None
    u32 reg_sys_gpio19_in             :1 ; /// None
    u32 reg_sys_gpio19_out            :1 ; /// None
    u32 reg_sys_gpio19_oen            :1 ; /// None
    u32 :4 ; /// [0x22]
    u32 reg_sys_gpio19_mode           :1 ; /// None
    u32 :16; /// [0x22]
    /* [0x23] */
    u32 reg_sys_gpio20_in             :1 ; /// None
    u32 reg_sys_gpio20_out            :1 ; /// None
    u32 reg_sys_gpio20_oen            :1 ; /// None
    u32 :4 ; /// [0x23]
    u32 reg_sys_gpio20_mode           :1 ; /// None
    u32 reg_sys_gpio21_in             :1 ; /// None
    u32 reg_sys_gpio21_out            :1 ; /// None
    u32 reg_sys_gpio21_oen            :1 ; /// None
    u32 :4 ; /// [0x23]
    u32 reg_sys_gpio21_mode           :1 ; /// None
    u32 :16; /// [0x23]
    /* [0x24] */
    u32 reg_sys_gpio22_in             :1 ; /// None
    u32 reg_sys_gpio22_out            :1 ; /// None
    u32 reg_sys_gpio22_oen            :1 ; /// None
    u32 :4 ; /// [0x24]
    u32 reg_sys_gpio22_mode           :1 ; /// None
    u32 reg_sys_gpio23_in             :1 ; /// None
    u32 reg_sys_gpio23_out            :1 ; /// None
    u32 reg_sys_gpio23_oen            :1 ; /// None
    u32 :4 ; /// [0x24]
    u32 reg_sys_gpio23_mode           :1 ; /// None
    u32 :16; /// [0x24]
    u32 :32; /// [0x25]
    /* [0x26] */
    u32 reg_spi_rf_gpio0_in           :1 ; /// None
    u32 reg_spi_rf_gpio0_out          :1 ; /// None
    u32 reg_spi_rf_gpio0_oen          :1 ; /// None
    u32 :1 ; /// [0x26]
    u32 reg_spi_rf_gpio0_pe           :1 ; /// None
    u32 reg_spi_rf_gpio0_ps           :1 ; /// None
    u32 reg_spi_rf_gpio0_drv          :1 ; /// None
    u32 reg_spi_rf_gpio0_mode         :1 ; /// None
    u32 reg_spi_rf_gpio1_in           :1 ; /// None
    u32 reg_spi_rf_gpio1_out          :1 ; /// None
    u32 reg_spi_rf_gpio1_oen          :1 ; /// None
    u32 :1 ; /// [0x26]
    u32 reg_spi_rf_gpio1_pe           :1 ; /// None
    u32 reg_spi_rf_gpio1_ps           :1 ; /// None
    u32 reg_spi_rf_gpio1_drv          :1 ; /// None
    u32 reg_spi_rf_gpio1_mode         :1 ; /// None
    u32 :16; /// [0x26]
    /* [0x27] */
    u32 reg_spi_rf_gpio2_in           :1 ; /// None
    u32 reg_spi_rf_gpio2_out          :1 ; /// None
    u32 reg_spi_rf_gpio2_oen          :1 ; /// None
    u32 :1 ; /// [0x27]
    u32 reg_spi_rf_gpio2_pe           :1 ; /// None
    u32 reg_spi_rf_gpio2_ps           :1 ; /// None
    u32 reg_spi_rf_gpio2_drv          :1 ; /// None
    u32 reg_spi_rf_gpio2_mode         :1 ; /// None
    u32 :24; /// [0x27]
    /* [0x28] */
    u32 reg_sr_gpio0_in               :1 ; /// None
    u32 reg_sr_gpio0_out              :1 ; /// None
    u32 reg_sr_gpio0_oen              :1 ; /// None
    u32 :1 ; /// [0x28]
    u32 reg_sr_gpio0_pe               :1 ; /// None
    u32 reg_sr_gpio0_ps               :1 ; /// None
    u32 reg_sr_gpio0_drv              :1 ; /// None
    u32 reg_sr_gpio0_mode             :1 ; /// None
    u32 reg_sr_gpio1_in               :1 ; /// None
    u32 reg_sr_gpio1_out              :1 ; /// None
    u32 reg_sr_gpio1_oen              :1 ; /// None
    u32 :1 ; /// [0x28]
    u32 reg_sr_gpio1_pe               :1 ; /// None
    u32 reg_sr_gpio1_ps               :1 ; /// None
    u32 reg_sr_gpio1_drv              :1 ; /// None
    u32 reg_sr_gpio1_mode             :1 ; /// None
    u32 :16; /// [0x28]
    /* [0x29] */
    u32 reg_sr_gpio2_in               :1 ; /// None
    u32 reg_sr_gpio2_out              :1 ; /// None
    u32 reg_sr_gpio2_oen              :1 ; /// None
    u32 :1 ; /// [0x29]
    u32 reg_sr_gpio2_pe               :1 ; /// None
    u32 reg_sr_gpio2_ps               :1 ; /// None
    u32 reg_sr_gpio2_drv              :1 ; /// None
    u32 reg_sr_gpio2_mode             :1 ; /// None
    u32 reg_sr_gpio3_in               :1 ; /// None
    u32 reg_sr_gpio3_out              :1 ; /// None
    u32 reg_sr_gpio3_oen              :1 ; /// None
    u32 :1 ; /// [0x29]
    u32 reg_sr_gpio3_pe               :1 ; /// None
    u32 reg_sr_gpio3_ps               :1 ; /// None
    u32 reg_sr_gpio3_drv              :1 ; /// None
    u32 reg_sr_gpio3_mode             :1 ; /// None
    u32 :16; /// [0x29]
    /* [0x2A] */
    u32 reg_sr_gpio4_in               :1 ; /// None
    u32 reg_sr_gpio4_out              :1 ; /// None
    u32 reg_sr_gpio4_oen              :1 ; /// None
    u32 :1 ; /// [0x2A]
    u32 reg_sr_gpio4_pe               :1 ; /// None
    u32 reg_sr_gpio4_ps               :1 ; /// None
    u32 reg_sr_gpio4_drv              :1 ; /// None
    u32 reg_sr_gpio4_mode             :1 ; /// None
    u32 reg_sr_gpio5_in               :1 ; /// None
    u32 reg_sr_gpio5_out              :1 ; /// None
    u32 reg_sr_gpio5_oen              :1 ; /// None
    u32 :1 ; /// [0x2A]
    u32 reg_sr_gpio5_pe               :1 ; /// None
    u32 reg_sr_gpio5_ps               :1 ; /// None
    u32 reg_sr_gpio5_drv              :1 ; /// None
    u32 reg_sr_gpio5_mode             :1 ; /// None
    u32 :16; /// [0x2A]
    /* [0x2B] */
    u32 reg_sr_gpio6_in               :1 ; /// None
    u32 reg_sr_gpio6_out              :1 ; /// None
    u32 reg_sr_gpio6_oen              :1 ; /// None
    u32 :1 ; /// [0x2B]
    u32 reg_sr_gpio6_pe               :1 ; /// None
    u32 reg_sr_gpio6_ps               :1 ; /// None
    u32 reg_sr_gpio6_drv              :1 ; /// None
    u32 reg_sr_gpio6_mode             :1 ; /// None
    u32 reg_sr_gpio7_in               :1 ; /// None
    u32 reg_sr_gpio7_out              :1 ; /// None
    u32 reg_sr_gpio7_oen              :1 ; /// None
    u32 :1 ; /// [0x2B]
    u32 reg_sr_gpio7_pe               :1 ; /// None
    u32 reg_sr_gpio7_ps               :1 ; /// None
    u32 reg_sr_gpio7_drv              :1 ; /// None
    u32 reg_sr_gpio7_mode             :1 ; /// None
    u32 :16; /// [0x2B]
    /* [0x2C] */
    u32 reg_sr_gpio8_in               :1 ; /// None
    u32 reg_sr_gpio8_out              :1 ; /// None
    u32 reg_sr_gpio8_oen              :1 ; /// None
    u32 :1 ; /// [0x2C]
    u32 reg_sr_gpio8_pe               :1 ; /// None
    u32 reg_sr_gpio8_ps               :1 ; /// None
    u32 reg_sr_gpio8_drv              :1 ; /// None
    u32 reg_sr_gpio8_mode             :1 ; /// None
    u32 reg_sr_gpio9_in               :1 ; /// None
    u32 reg_sr_gpio9_out              :1 ; /// None
    u32 reg_sr_gpio9_oen              :1 ; /// None
    u32 :1 ; /// [0x2C]
    u32 reg_sr_gpio9_pe               :1 ; /// None
    u32 reg_sr_gpio9_ps               :1 ; /// None
    u32 reg_sr_gpio9_drv              :1 ; /// None
    u32 reg_sr_gpio9_mode             :1 ; /// None
    u32 :16; /// [0x2C]
    /* [0x2D] */
    u32 reg_sr_gpio10_in              :1 ; /// None
    u32 reg_sr_gpio10_out             :1 ; /// None
    u32 reg_sr_gpio10_oen             :1 ; /// None
    u32 :1 ; /// [0x2D]
    u32 reg_sr_gpio10_pe              :1 ; /// None
    u32 reg_sr_gpio10_ps              :1 ; /// None
    u32 reg_sr_gpio10_drv             :1 ; /// None
    u32 reg_sr_gpio10_mode            :1 ; /// None
    u32 reg_sr_gpio11_in              :1 ; /// None
    u32 reg_sr_gpio11_out             :1 ; /// None
    u32 reg_sr_gpio11_oen             :1 ; /// None
    u32 :1 ; /// [0x2D]
    u32 reg_sr_gpio11_pe              :1 ; /// None
    u32 reg_sr_gpio11_ps              :1 ; /// None
    u32 reg_sr_gpio11_drv             :1 ; /// None
    u32 reg_sr_gpio11_mode            :1 ; /// None
    u32 :16; /// [0x2D]
    /* [0x2E] */
    u32 reg_sr_gpio12_in              :1 ; /// None
    u32 reg_sr_gpio12_out             :1 ; /// None
    u32 reg_sr_gpio12_oen             :1 ; /// None
    u32 :1 ; /// [0x2E]
    u32 reg_sr_gpio12_pe              :1 ; /// None
    u32 reg_sr_gpio12_ps              :1 ; /// None
    u32 reg_sr_gpio12_drv             :1 ; /// None
    u32 reg_sr_gpio12_mode            :1 ; /// None
    u32 reg_sr_gpio13_in              :1 ; /// None
    u32 reg_sr_gpio13_out             :1 ; /// None
    u32 reg_sr_gpio13_oen             :1 ; /// None
    u32 :1 ; /// [0x2E]
    u32 reg_sr_gpio13_pe              :1 ; /// None
    u32 reg_sr_gpio13_ps              :1 ; /// None
    u32 reg_sr_gpio13_drv             :1 ; /// None
    u32 reg_sr_gpio13_mode            :1 ; /// None
    u32 :16; /// [0x2E]
    /* [0x2F] */
    u32 reg_i2c_gpio0_in              :1 ; /// None
    u32 reg_i2c_gpio0_out             :1 ; /// None
    u32 reg_i2c_gpio0_oen             :1 ; /// None
    u32 :4 ; /// [0x2F]
    u32 reg_i2c_gpio0_mode            :1 ; /// None
    u32 reg_i2c_gpio1_in              :1 ; /// None
    u32 reg_i2c_gpio1_out             :1 ; /// None
    u32 reg_i2c_gpio1_oen             :1 ; /// None
    u32 :4 ; /// [0x2F]
    u32 reg_i2c_gpio1_mode            :1 ; /// None
    u32 :16; /// [0x2F]
    /* [0x30] */
    u32 :4 ; /// [0x30]
    u32 reg_jtag_gpio0_pe             :1 ; /// None
    u32 reg_jtag_gpio0_ps             :1 ; /// None
    u32 reg_jtag_gpio0_drv            :1 ; /// None
    u32 :5 ; /// [0x30]
    u32 reg_jtag_gpio1_pe             :1 ; /// None
    u32 reg_jtag_gpio1_ps             :1 ; /// None
    u32 reg_jtag_gpio1_drv            :1 ; /// None
    u32 :17; /// [0x30]
    /* [0x31] */
    u32 :4 ; /// [0x31]
    u32 reg_jtag_gpio2_pe             :1 ; /// None
    u32 reg_jtag_gpio2_ps             :1 ; /// None
    u32 reg_jtag_gpio2_drv            :1 ; /// None
    u32 :5 ; /// [0x31]
    u32 reg_jtag_gpio3_pe             :1 ; /// None
    u32 reg_jtag_gpio3_ps             :1 ; /// None
    u32 reg_jtag_gpio3_drv            :1 ; /// None
    u32 :17; /// [0x31]
    /* [0x32] */
    u32 :4 ; /// [0x32]
    u32 reg_jtag_gpio4_pe             :1 ; /// None
    u32 reg_jtag_gpio4_ps             :1 ; /// None
    u32 reg_jtag_gpio4_drv            :1 ; /// None
    u32 :25; /// [0x32]
    /* [0x33] */
    u32 reg_lcd_gpio0_in              :1 ; /// None
    u32 reg_lcd_gpio0_out             :1 ; /// None
    u32 reg_lcd_gpio0_oen             :1 ; /// None
    u32 :1 ; /// [0x33]
    u32 reg_lcd_gpio0_pe              :1 ; /// None
    u32 reg_lcd_gpio0_ps              :1 ; /// None
    u32 reg_lcd_gpio0_drv             :1 ; /// None
    u32 reg_lcd_gpio0_mode            :1 ; /// None
    u32 reg_lcd_gpio1_in              :1 ; /// None
    u32 reg_lcd_gpio1_out             :1 ; /// None
    u32 reg_lcd_gpio1_oen             :1 ; /// None
    u32 :1 ; /// [0x33]
    u32 reg_lcd_gpio1_pe              :1 ; /// None
    u32 reg_lcd_gpio1_ps              :1 ; /// None
    u32 reg_lcd_gpio1_drv             :1 ; /// None
    u32 reg_lcd_gpio1_mode            :1 ; /// None
    u32 :16; /// [0x33]
    /* [0x34] */
    u32 reg_lcd_gpio2_in              :1 ; /// None
    u32 reg_lcd_gpio2_out             :1 ; /// None
    u32 reg_lcd_gpio2_oen             :1 ; /// None
    u32 :1 ; /// [0x34]
    u32 reg_lcd_gpio2_pe              :1 ; /// None
    u32 reg_lcd_gpio2_ps              :1 ; /// None
    u32 reg_lcd_gpio2_drv             :1 ; /// None
    u32 reg_lcd_gpio2_mode            :1 ; /// None
    u32 reg_lcd_gpio3_in              :1 ; /// None
    u32 reg_lcd_gpio3_out             :1 ; /// None
    u32 reg_lcd_gpio3_oen             :1 ; /// None
    u32 :1 ; /// [0x34]
    u32 reg_lcd_gpio3_pe              :1 ; /// None
    u32 reg_lcd_gpio3_ps              :1 ; /// None
    u32 reg_lcd_gpio3_drv             :1 ; /// None
    u32 reg_lcd_gpio3_mode            :1 ; /// None
    u32 :16; /// [0x34]
    /* [0x35] */
    u32 reg_lcd_gpio4_in              :1 ; /// None
    u32 reg_lcd_gpio4_out             :1 ; /// None
    u32 reg_lcd_gpio4_oen             :1 ; /// None
    u32 :1 ; /// [0x35]
    u32 reg_lcd_gpio4_pe              :1 ; /// None
    u32 reg_lcd_gpio4_ps              :1 ; /// None
    u32 reg_lcd_gpio4_drv             :1 ; /// None
    u32 reg_lcd_gpio4_mode            :1 ; /// None
    u32 reg_lcd_gpio5_in              :1 ; /// None
    u32 reg_lcd_gpio5_out             :1 ; /// None
    u32 reg_lcd_gpio5_oen             :1 ; /// None
    u32 :1 ; /// [0x35]
    u32 reg_lcd_gpio5_pe              :1 ; /// None
    u32 reg_lcd_gpio5_ps              :1 ; /// None
    u32 reg_lcd_gpio5_drv             :1 ; /// None
    u32 reg_lcd_gpio5_mode            :1 ; /// None
    u32 :16; /// [0x35]
    /* [0x36] */
    u32 reg_lcd_gpio6_in              :1 ; /// None
    u32 reg_lcd_gpio6_out             :1 ; /// None
    u32 reg_lcd_gpio6_oen             :1 ; /// None
    u32 :1 ; /// [0x36]
    u32 reg_lcd_gpio6_pe              :1 ; /// None
    u32 reg_lcd_gpio6_ps              :1 ; /// None
    u32 reg_lcd_gpio6_drv             :1 ; /// None
    u32 reg_lcd_gpio6_mode            :1 ; /// None
    u32 reg_lcd_gpio7_in              :1 ; /// None
    u32 reg_lcd_gpio7_out             :1 ; /// None
    u32 reg_lcd_gpio7_oen             :1 ; /// None
    u32 :1 ; /// [0x36]
    u32 reg_lcd_gpio7_pe              :1 ; /// None
    u32 reg_lcd_gpio7_ps              :1 ; /// None
    u32 reg_lcd_gpio7_drv             :1 ; /// None
    u32 reg_lcd_gpio7_mode            :1 ; /// None
    u32 :16; /// [0x36]
    /* [0x37] */
    u32 reg_lcd_gpio8_in              :1 ; /// None
    u32 reg_lcd_gpio8_out             :1 ; /// None
    u32 reg_lcd_gpio8_oen             :1 ; /// None
    u32 :1 ; /// [0x37]
    u32 reg_lcd_gpio8_pe              :1 ; /// None
    u32 reg_lcd_gpio8_ps              :1 ; /// None
    u32 reg_lcd_gpio8_drv             :1 ; /// None
    u32 reg_lcd_gpio8_mode            :1 ; /// None
    u32 reg_lcd_gpio9_in              :1 ; /// None
    u32 reg_lcd_gpio9_out             :1 ; /// None
    u32 reg_lcd_gpio9_oen             :1 ; /// None
    u32 :1 ; /// [0x37]
    u32 reg_lcd_gpio9_pe              :1 ; /// None
    u32 reg_lcd_gpio9_ps              :1 ; /// None
    u32 reg_lcd_gpio9_drv             :1 ; /// None
    u32 reg_lcd_gpio9_mode            :1 ; /// None
    u32 :16; /// [0x37]
    /* [0x38] */
    u32 reg_lcd_gpio10_in             :1 ; /// None
    u32 reg_lcd_gpio10_out            :1 ; /// None
    u32 reg_lcd_gpio10_oen            :1 ; /// None
    u32 :1 ; /// [0x38]
    u32 reg_lcd_gpio10_pe             :1 ; /// None
    u32 reg_lcd_gpio10_ps             :1 ; /// None
    u32 reg_lcd_gpio10_drv            :1 ; /// None
    u32 reg_lcd_gpio10_mode           :1 ; /// None
    u32 reg_lcd_gpio11_in             :1 ; /// None
    u32 reg_lcd_gpio11_out            :1 ; /// None
    u32 reg_lcd_gpio11_oen            :1 ; /// None
    u32 :1 ; /// [0x38]
    u32 reg_lcd_gpio11_pe             :1 ; /// None
    u32 reg_lcd_gpio11_ps             :1 ; /// None
    u32 reg_lcd_gpio11_drv            :1 ; /// None
    u32 reg_lcd_gpio11_mode           :1 ; /// None
    u32 :16; /// [0x38]
    /* [0x39] */
    u32 reg_lcd_gpio12_in             :1 ; /// None
    u32 reg_lcd_gpio12_out            :1 ; /// None
    u32 reg_lcd_gpio12_oen            :1 ; /// None
    u32 :1 ; /// [0x39]
    u32 reg_lcd_gpio12_pe             :1 ; /// None
    u32 reg_lcd_gpio12_ps             :1 ; /// None
    u32 reg_lcd_gpio12_drv            :1 ; /// None
    u32 reg_lcd_gpio12_mode           :1 ; /// None
    u32 reg_lcd_gpio13_in             :1 ; /// None
    u32 reg_lcd_gpio13_out            :1 ; /// None
    u32 reg_lcd_gpio13_oen            :1 ; /// None
    u32 :1 ; /// [0x39]
    u32 reg_lcd_gpio13_pe             :1 ; /// None
    u32 reg_lcd_gpio13_ps             :1 ; /// None
    u32 reg_lcd_gpio13_drv            :1 ; /// None
    u32 reg_lcd_gpio13_mode           :1 ; /// None
    u32 :16; /// [0x39]
    /* [0x3A] */
    u32 reg_lcd_gpio14_in             :1 ; /// None
    u32 reg_lcd_gpio14_out            :1 ; /// None
    u32 reg_lcd_gpio14_oen            :1 ; /// None
    u32 :1 ; /// [0x3A]
    u32 reg_lcd_gpio14_pe             :1 ; /// None
    u32 reg_lcd_gpio14_ps             :1 ; /// None
    u32 reg_lcd_gpio14_drv            :1 ; /// None
    u32 reg_lcd_gpio14_mode           :1 ; /// None
    u32 reg_lcd_gpio15_in             :1 ; /// None
    u32 reg_lcd_gpio15_out            :1 ; /// None
    u32 reg_lcd_gpio15_oen            :1 ; /// None
    u32 :1 ; /// [0x3A]
    u32 reg_lcd_gpio15_pe             :1 ; /// None
    u32 reg_lcd_gpio15_ps             :1 ; /// None
    u32 reg_lcd_gpio15_drv            :1 ; /// None
    u32 reg_lcd_gpio15_mode           :1 ; /// None
    u32 :16; /// [0x3A]
    /* [0x3B] */
    u32 reg_lcd_gpio16_in             :1 ; /// None
    u32 reg_lcd_gpio16_out            :1 ; /// None
    u32 reg_lcd_gpio16_oen            :1 ; /// None
    u32 :1 ; /// [0x3B]
    u32 reg_lcd_gpio16_pe             :1 ; /// None
    u32 reg_lcd_gpio16_ps             :1 ; /// None
    u32 reg_lcd_gpio16_drv            :1 ; /// None
    u32 reg_lcd_gpio16_mode           :1 ; /// None
    u32 reg_lcd_gpio17_in             :1 ; /// None
    u32 reg_lcd_gpio17_out            :1 ; /// None
    u32 reg_lcd_gpio17_oen            :1 ; /// None
    u32 :1 ; /// [0x3B]
    u32 reg_lcd_gpio17_pe             :1 ; /// None
    u32 reg_lcd_gpio17_ps             :1 ; /// None
    u32 reg_lcd_gpio17_drv            :1 ; /// None
    u32 reg_lcd_gpio17_mode           :1 ; /// None
    u32 :16; /// [0x3B]
    /* [0x3C] */
    u32 reg_lcd_gpio18_in             :1 ; /// None
    u32 reg_lcd_gpio18_out            :1 ; /// None
    u32 reg_lcd_gpio18_oen            :1 ; /// None
    u32 :1 ; /// [0x3C]
    u32 reg_lcd_gpio18_pe             :1 ; /// None
    u32 reg_lcd_gpio18_ps             :1 ; /// None
    u32 reg_lcd_gpio18_drv            :1 ; /// None
    u32 reg_lcd_gpio18_mode           :1 ; /// None
    u32 reg_lcd_gpio19_in             :1 ; /// None
    u32 reg_lcd_gpio19_out            :1 ; /// None
    u32 reg_lcd_gpio19_oen            :1 ; /// None
    u32 :1 ; /// [0x3C]
    u32 reg_lcd_gpio19_pe             :1 ; /// None
    u32 reg_lcd_gpio19_ps             :1 ; /// None
    u32 reg_lcd_gpio19_drv            :1 ; /// None
    u32 reg_lcd_gpio19_mode           :1 ; /// None
    u32 :16; /// [0x3C]
    /* [0x3D] */
    u32 reg_lcd_gpio20_in             :1 ; /// None
    u32 reg_lcd_gpio20_out            :1 ; /// None
    u32 reg_lcd_gpio20_oen            :1 ; /// None
    u32 :1 ; /// [0x3D]
    u32 reg_lcd_gpio20_pe             :1 ; /// None
    u32 reg_lcd_gpio20_ps             :1 ; /// None
    u32 reg_lcd_gpio20_drv            :1 ; /// None
    u32 reg_lcd_gpio20_mode           :1 ; /// None
    u32 reg_lcd_gpio21_in             :1 ; /// None
    u32 reg_lcd_gpio21_out            :1 ; /// None
    u32 reg_lcd_gpio21_oen            :1 ; /// None
    u32 :1 ; /// [0x3D]
    u32 reg_lcd_gpio21_pe             :1 ; /// None
    u32 reg_lcd_gpio21_ps             :1 ; /// None
    u32 reg_lcd_gpio21_drv            :1 ; /// None
    u32 reg_lcd_gpio21_mode           :1 ; /// None
    u32 :16; /// [0x3D]
    /* [0x3E] */
    u32 reg_lcd_gpio22_in             :1 ; /// None
    u32 reg_lcd_gpio22_out            :1 ; /// None
    u32 reg_lcd_gpio22_oen            :1 ; /// None
    u32 :1 ; /// [0x3E]
    u32 reg_lcd_gpio22_pe             :1 ; /// None
    u32 reg_lcd_gpio22_ps             :1 ; /// None
    u32 reg_lcd_gpio22_drv            :1 ; /// None
    u32 reg_lcd_gpio22_mode           :1 ; /// None
    u32 reg_lcd_gpio23_in             :1 ; /// None
    u32 reg_lcd_gpio23_out            :1 ; /// None
    u32 reg_lcd_gpio23_oen            :1 ; /// None
    u32 :1 ; /// [0x3E]
    u32 reg_lcd_gpio23_pe             :1 ; /// None
    u32 reg_lcd_gpio23_ps             :1 ; /// None
    u32 reg_lcd_gpio23_drv            :1 ; /// None
    u32 reg_lcd_gpio23_mode           :1 ; /// None
    u32 :16; /// [0x3E]
    /* [0x3F] */
    u32 reg_gps_gpio0_in              :1 ; /// None
    u32 reg_gps_gpio0_out             :1 ; /// None
    u32 reg_gps_gpio0_oen             :1 ; /// None
    u32 :1 ; /// [0x3F]
    u32 reg_gps_gpio0_pe              :1 ; /// None
    u32 reg_gps_gpio0_ps              :1 ; /// None
    u32 reg_gps_gpio0_drv             :1 ; /// None
    u32 reg_gps_gpio0_mode            :1 ; /// reserved; can't not used by S/W
    u32 reg_gps_gpio1_in              :1 ; /// None
    u32 reg_gps_gpio1_out             :1 ; /// None
    u32 reg_gps_gpio1_oen             :1 ; /// None
    u32 :1 ; /// [0x3F]
    u32 reg_gps_gpio1_pe              :1 ; /// None
    u32 reg_gps_gpio1_ps              :1 ; /// None
    u32 reg_gps_gpio1_drv             :1 ; /// None
    u32 reg_gps_gpio1_mode            :1 ; /// reserved; can't not used by S/W
} KeGpioCtrl0_t;

#endif //__KERNEL_GPIO_H__
