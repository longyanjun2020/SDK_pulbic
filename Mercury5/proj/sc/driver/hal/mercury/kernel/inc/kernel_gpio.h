/***************************************************************************
 *  kernel_gpio.h
 *--------------------------------------------------------------------------
 *  Scope: GPIO register description
 *
 ****************************************************************************/

#ifndef __KERNEL_GPIO_H__
#define __KERNEL_GPIO_H__

/* B2 registers definition */

#include "vm_types.ht"
#include "cpu_mem_map.hc"

/************************************************/
/* GPIO registers definition                    */
/************************************************/

typedef struct KeGpioCtrl2_s
{
    /* [0x00] */
    u32 reg_emi_gpio0_in              :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio0_out             :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio0_oen             :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x00]
    u32 reg_emi_gpio0_pe              :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio0_ps              :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x00]
    u32 reg_emi_gpio0_mode            :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio1_in              :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio1_out             :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio1_oen             :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x00]
    u32 reg_emi_gpio1_pe              :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio1_ps              :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x00]
    u32 reg_emi_gpio1_mode            :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x00]
    /* [0x01] */
    u32 reg_emi_gpio2_in              :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio2_out             :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio2_oen             :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x01]
    u32 reg_emi_gpio2_pe              :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio2_ps              :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x01]
    u32 reg_emi_gpio2_mode            :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio3_in              :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio3_out             :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio3_oen             :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x01]
    u32 reg_emi_gpio3_pe              :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio3_ps              :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x01]
    u32 reg_emi_gpio3_mode            :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x01]
    /* [0x02] */
    u32 reg_emi_gpio4_in              :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio4_out             :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio4_oen             :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x02]
    u32 reg_emi_gpio4_pe              :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio4_ps              :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x02]
    u32 reg_emi_gpio4_mode            :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio5_in              :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio5_out             :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio5_oen             :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x02]
    u32 reg_emi_gpio5_pe              :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio5_ps              :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x02]
    u32 reg_emi_gpio5_mode            :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x02]
    /* [0x03] */
    u32 reg_emi_gpio6_in              :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio6_out             :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio6_oen             :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x03]
    u32 reg_emi_gpio6_pe              :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio6_ps              :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x03]
    u32 reg_emi_gpio6_mode            :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio7_in              :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio7_out             :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio7_oen             :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x03]
    u32 reg_emi_gpio7_pe              :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio7_ps              :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x03]
    u32 reg_emi_gpio7_mode            :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x03]
    /* [0x04] */
    u32 reg_emi_gpio8_in              :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio8_out             :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio8_oen             :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x04]
    u32 reg_emi_gpio8_pe              :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio8_ps              :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x04]
    u32 reg_emi_gpio8_mode            :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio9_in              :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio9_out             :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio9_oen             :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x04]
    u32 reg_emi_gpio9_pe              :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio9_ps              :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x04]
    u32 reg_emi_gpio9_mode            :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x04]
    /* [0x05] */
    u32 reg_emi_gpio10_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio10_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio10_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x05]
    u32 reg_emi_gpio10_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio10_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x05]
    u32 reg_emi_gpio10_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio11_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio11_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio11_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x05]
    u32 reg_emi_gpio11_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio11_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x05]
    u32 reg_emi_gpio11_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x05]
    /* [0x06] */
    u32 reg_emi_gpio12_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio12_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio12_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x06]
    u32 reg_emi_gpio12_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio12_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x06]
    u32 reg_emi_gpio12_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio13_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio13_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio13_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x06]
    u32 reg_emi_gpio13_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio13_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x06]
    u32 reg_emi_gpio13_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x06]
    /* [0x07] */
    u32 reg_emi_gpio14_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio14_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio14_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x07]
    u32 reg_emi_gpio14_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio14_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x07]
    u32 reg_emi_gpio14_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio15_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio15_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio15_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x07]
    u32 reg_emi_gpio15_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio15_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x07]
    u32 reg_emi_gpio15_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x07]
    /* [0x08] */
    u32 reg_emi_gpio16_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio16_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio16_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x08]
    u32 reg_emi_gpio16_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio16_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x08]
    u32 reg_emi_gpio16_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio17_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio17_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio17_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x08]
    u32 reg_emi_gpio17_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio17_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x08]
    u32 reg_emi_gpio17_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x08]
    /* [0x09] */
    u32 reg_emi_gpio18_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio18_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio18_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x09]
    u32 reg_emi_gpio18_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio18_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x09]
    u32 reg_emi_gpio18_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio19_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio19_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio19_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x09]
    u32 reg_emi_gpio19_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio19_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x09]
    u32 reg_emi_gpio19_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x09]
    /* [0x0A] */
    u32 reg_emi_gpio20_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio20_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio20_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x0A]
    u32 reg_emi_gpio20_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio20_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x0A]
    u32 reg_emi_gpio20_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio21_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio21_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio21_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x0A]
    u32 reg_emi_gpio21_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio21_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x0A]
    u32 reg_emi_gpio21_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x0A]
    /* [0x0B] */
    u32 reg_emi_gpio22_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio22_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio22_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x0B]
    u32 reg_emi_gpio22_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio22_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x0B]
    u32 reg_emi_gpio22_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio23_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio23_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio23_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x0B]
    u32 reg_emi_gpio23_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio23_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x0B]
    u32 reg_emi_gpio23_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x0B]
    /* [0x0C] */
    u32 reg_emi_gpio24_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio24_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio24_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x0C]
    u32 reg_emi_gpio24_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio24_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x0C]
    u32 reg_emi_gpio24_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio25_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio25_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio25_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x0C]
    u32 reg_emi_gpio25_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio25_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x0C]
    u32 reg_emi_gpio25_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x0C]
    /* [0x0D] */
    u32 reg_emi_gpio26_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio26_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio26_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x0D]
    u32 reg_emi_gpio26_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio26_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x0D]
    u32 reg_emi_gpio26_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio27_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio27_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio27_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x0D]
    u32 reg_emi_gpio27_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio27_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x0D]
    u32 reg_emi_gpio27_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x0D]
    /* [0x0E] */
    u32 reg_emi_gpio28_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio28_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio28_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x0E]
    u32 reg_emi_gpio28_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio28_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x0E]
    u32 reg_emi_gpio28_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio29_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio29_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio29_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x0E]
    u32 reg_emi_gpio29_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio29_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x0E]
    u32 reg_emi_gpio29_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x0E]
    /* [0x0F] */
    u32 reg_emi_gpio30_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio30_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio30_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x0F]
    u32 reg_emi_gpio30_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio30_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x0F]
    u32 reg_emi_gpio30_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio31_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio31_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio31_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x0F]
    u32 reg_emi_gpio31_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio31_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x0F]
    u32 reg_emi_gpio31_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x0F]
    /* [0x10] */
    u32 reg_emi_gpio32_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio32_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio32_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x10]
    u32 reg_emi_gpio32_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio32_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x10]
    u32 reg_emi_gpio32_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio33_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio33_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio33_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x10]
    u32 reg_emi_gpio33_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio33_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x10]
    u32 reg_emi_gpio33_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x10]
    /* [0x11] */
    u32 reg_emi_gpio34_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio34_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio34_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x11]
    u32 reg_emi_gpio34_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio34_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x11]
    u32 reg_emi_gpio34_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio35_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio35_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio35_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x11]
    u32 reg_emi_gpio35_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio35_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x11]
    u32 reg_emi_gpio35_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x11]
    /* [0x12] */
    u32 reg_emi_gpio36_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio36_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio36_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x12]
    u32 reg_emi_gpio36_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio36_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x12]
    u32 reg_emi_gpio36_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio37_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio37_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio37_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x12]
    u32 reg_emi_gpio37_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio37_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x12]
    u32 reg_emi_gpio37_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x12]
    /* [0x13] */
    u32 reg_emi_gpio38_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio38_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio38_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x13]
    u32 reg_emi_gpio38_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio38_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x13]
    u32 reg_emi_gpio38_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio39_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio39_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio39_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x13]
    u32 reg_emi_gpio39_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio39_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x13]
    u32 reg_emi_gpio39_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x13]
    /* [0x14] */
    u32 reg_emi_gpio40_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio40_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio40_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x14]
    u32 reg_emi_gpio40_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio40_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x14]
    u32 reg_emi_gpio40_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio41_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio41_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio41_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x14]
    u32 reg_emi_gpio41_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio41_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x14]
    u32 reg_emi_gpio41_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x14]
    /* [0x15] */
    u32 reg_emi_gpio42_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio42_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio42_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x15]
    u32 reg_emi_gpio42_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio42_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x15]
    u32 reg_emi_gpio42_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio43_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio43_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio43_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x15]
    u32 reg_emi_gpio43_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio43_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x15]
    u32 reg_emi_gpio43_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x15]
    /* [0x16] */
    u32 reg_emi_gpio44_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio44_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio44_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x16]
    u32 reg_emi_gpio44_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio44_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x16]
    u32 reg_emi_gpio44_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio45_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio45_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio45_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x16]
    u32 reg_emi_gpio45_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio45_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x16]
    u32 reg_emi_gpio45_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x16]
    /* [0x17] */
    u32 reg_emi_gpio46_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio46_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio46_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x17]
    u32 reg_emi_gpio46_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio46_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x17]
    u32 reg_emi_gpio46_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio47_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio47_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio47_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x17]
    u32 reg_emi_gpio47_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio47_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x17]
    u32 reg_emi_gpio47_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x17]
    /* [0x18] */
    u32 reg_emi_gpio48_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio48_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio48_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x18]
    u32 reg_emi_gpio48_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio48_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x18]
    u32 reg_emi_gpio48_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio49_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio49_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio49_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x18]
    u32 reg_emi_gpio49_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio49_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x18]
    u32 reg_emi_gpio49_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x18]
    /* [0x19] */
    u32 reg_emi_gpio50_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio50_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio50_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x19]
    u32 reg_emi_gpio50_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio50_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x19]
    u32 reg_emi_gpio50_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_emi_gpio51_in             :1 ; /// EMI_GPIO[51:0]'s input value in gpio mode
    u32 reg_emi_gpio51_out            :1 ; /// EMI_GPIO[51:0]'s output value in gpio mode
    u32 reg_emi_gpio51_oen            :1 ; /// EMI_GPIO[51:0]'s output enable(active low) in gpio mode
    u32 :1 ; /// [0x19]
    u32 reg_emi_gpio51_pe             :1 ; /// EMI_GPIO[51:0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_emi_gpio51_ps             :1 ; /// EMI_GPIO[51:0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 :1 ; /// [0x19]
    u32 reg_emi_gpio51_mode           :1 ; /// EMI_GPIO[51:0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x19]
    u32 :32; /// [0x1A]
    u32 :32; /// [0x1B]
    u32 :32; /// [0x1C]
    u32 :32; /// [0x1D]
    u32 :32; /// [0x1E]
    u32 :32; /// [0x1F]
    u32 :32; /// [0x20]
    u32 :32; /// [0x21]
    u32 :32; /// [0x22]
    u32 :32; /// [0x23]
    u32 :32; /// [0x24]
    u32 :32; /// [0x25]
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
    u32 :32; /// [0x30]
    u32 :32; /// [0x31]
    u32 :32; /// [0x32]
    u32 :32; /// [0x33]
    u32 :32; /// [0x34]
    u32 :32; /// [0x35]
    u32 :32; /// [0x36]
    u32 :32; /// [0x37]
    u32 :32; /// [0x38]
    u32 :32; /// [0x39]
    u32 :32; /// [0x3A]
    u32 :32; /// [0x3B]
    /* [0x3C] */
    u32 reg_emi_gpio_reserved0        :16; /// emi gpio reserved0 registers
    u32 :16; /// [0x3C]
    /* [0x3D] */
    u32 reg_emi_gpio_reserved1        :16; /// emi gpio reserved1 registers
    u32 :16; /// [0x3D]
    /* [0x3E] */
    u32 reg_emi_gpio_reserved2        :16; /// emi gpio reserved2 registers
    u32 :16; /// [0x3E]
    /* [0x3F] */
    u32 reg_emi_gpio_reserved3        :16; /// emi gpio reserved3 registers
} KeGpioCtrl2_t;

typedef struct KeGpioCtrl1_s
{
    /* [0x00] */
    u32 reg_force_gpio_pw             :16; /// FT test
    u32 :16; /// [0x00]
    /* [0x01] */
    u32 reg_force_hiz                 :1 ; /// FT test
    u32 reg_force_pe                  :1 ; /// FT test
    u32 reg_force_ps                  :1 ; /// FT test
    u32 reg_force_gpio_mode           :1 ; /// FT test
    u32 :28; /// [0x01]
    /* [0x02] */
    u32 reg_debug_use                 :14; /// debug use only,
    u32 reg_uart_dl_high_speed        :1;  /// [14]:0: PAD_U0TXD use open-drain. DBG tool and DBB uart2 could work simultaneously. But uart baud rate is limited below 400kbps.

    u32 reg_dbg_i2c_sda_pad_in        :1 ; /// PAD_U0TXD's status ( usb download indication)
    u32 :16; /// [0x02]
    /* [0x03] */
    u32 reg_uart_gpio_drv1            :2 ; /// [0]:PAD_U0TXD's drive strength1
                                           /// [1]:PAD_U0RXD's drive strength1
    u32 :30; /// [0x03]
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
    /* [0x20] */
    u32 reg_emi_gpio_pw               :16; /// debug use only; password to use emi gpio
    u32 :16; /// [0x20]
    /* [0x21] */
    u32 reg_emi_gpio_pe_actual_0      :16; /// actual reg_emi_gpio_pe
    u32 :16; /// [0x21]
    u32 reg_emi_gpio_pe_actual_1      :16; /// @see reg_emi_gpio_pe_actual_0
    u32 :16; /// [0x21]
    u32 reg_emi_gpio_pe_actual_2      :16; /// @see reg_emi_gpio_pe_actual_0
    u32 :16; /// [0x21]
    u32 reg_emi_gpio_pe_actual_3      :4 ; /// @see reg_emi_gpio_pe_actual_0
    u32 :28; /// [0x24]
    /* [0x25] */
    u32 reg_emi_gpio_ps_actual_0      :16; /// actual reg_emi_gpio_ps
    u32 :16; /// [0x25]
    u32 reg_emi_gpio_ps_actual_1      :16; /// @see reg_emi_gpio_ps_actual_0
    u32 :16; /// [0x25]
    u32 reg_emi_gpio_ps_actual_2      :16; /// @see reg_emi_gpio_ps_actual_0
    u32 :16; /// [0x25]
    u32 reg_emi_gpio_ps_actual_3      :4 ; /// @see reg_emi_gpio_ps_actual_0
    u32 :28; /// [0x28]
    u32 :32; /// [0x29]
    u32 :32; /// [0x2A]
    u32 :32; /// [0x2B]
    u32 :32; /// [0x2C]
    u32 :32; /// [0x2D]
    u32 :32; /// [0x2E]
    u32 :32; /// [0x2F]
    /* [0x30] */
    u32 reg_emi_gpio_mode_emi_raw_0   :16; /// force EMI IO to GPIO mode in EMI side
    u32 :16; /// [0x30]
    u32 reg_emi_gpio_mode_emi_raw_1   :16; /// @see reg_emi_gpio_mode_emi_raw_0
    u32 :16; /// [0x30]
    u32 reg_emi_gpio_mode_emi_raw_2   :16; /// @see reg_emi_gpio_mode_emi_raw_0
    u32 :16; /// [0x30]
    u32 reg_emi_gpio_mode_emi_raw_3   :4 ; /// @see reg_emi_gpio_mode_emi_raw_0
    u32 :28; /// [0x33]
    /* [0x34] */
    u32 reg_emi_spi_pad_disable       :1 ; /// disable EMI GPIO PAD PAD_IO[38], [44], [46], [47], [49], and [51] for QSPI
    u32 :31; /// [0x34]
    u32 :32; /// [0x35]
    u32 :32; /// [0x36]
    u32 :32; /// [0x37]
    u32 :32; /// [0x38]
    u32 :32; /// [0x39]
    u32 :32; /// [0x3A]
    u32 :32; /// [0x3B]
    /* [0x3C] */
    u32 reg_gpio_ctrl1_reserved0      :16; /// gpio ctrl1 reserved0 registers
    u32 :16; /// [0x3C]
    /* [0x3D] */
    u32 reg_gpio_ctrl1_reserved1      :16; /// gpio ctrl1 reserved1 registers
    u32 :16; /// [0x3D]
    /* [0x3E] */
    u32 reg_gpio_ctrl1_reserved2      :16; /// gpio ctrl1 reserved2 registers
    u32 :16; /// [0x3E]
    /* [0x3F] */
    u32 reg_gpio_ctrl1_reserved3      :16; /// gpio ctrl1 reserved3 registers
} KeGpioCtrl1_t;

typedef struct KeGpioCtrl0_s
{
    /* [0x00] */
    u32 reg_btif_gpio0_in             :1 ; /// PAD_BTIF_GPIO1's input value in gpio mode
    u32 reg_btif_gpio0_out            :1 ; /// PAD_BTIF_GPIO1's output value in gpio mode
    u32 reg_btif_gpio0_oen            :1 ; /// PAD_BTIF_GPIO1's output enable(active low) in gpio mode
    u32 reg_btif_gpio0_drv1           :1 ; /// PAD_BTIF_GPIO1's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_btif_gpio0_pe             :1 ; /// PAD_BTIF_GPIO1's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_btif_gpio0_ps             :1 ; /// PAD_BTIF_GPIO1's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_btif_gpio0_drv            :1 ; /// PAD_BTIF_GPIO1's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_btif_gpio0_mode           :1 ; /// PAD_BTIF_GPIO1's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_btif_gpio1_in             :1 ; /// PAD_BTIF_GPIO2's input value in gpio mode
    u32 reg_btif_gpio1_out            :1 ; /// PAD_BTIF_GPIO2's output value in gpio mode
    u32 reg_btif_gpio1_oen            :1 ; /// PAD_BTIF_GPIO2's output enable(active low) in gpio mode
    u32 reg_btif_gpio1_drv1           :1 ; /// PAD_BTIF_GPIO2's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_btif_gpio1_pe             :1 ; /// PAD_BTIF_GPIO2's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_btif_gpio1_ps             :1 ; /// PAD_BTIF_GPIO2's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_btif_gpio1_drv            :1 ; /// PAD_BTIF_GPIO2's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_btif_gpio1_mode           :1 ; /// PAD_BTIF_GPIO2's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x00]
    /* [0x01] */
    u32 reg_btif_gpio2_in             :1 ; /// PAD_WL_STATE's input value in gpio mode
    u32 reg_btif_gpio2_out            :1 ; /// PAD_WL_STATE's output value in gpio mode
    u32 reg_btif_gpio2_oen            :1 ; /// PAD_WL_STATE's output enable(active low) in gpio mode
    u32 :1 ; /// [0x01]
    u32 reg_btif_gpio2_pe             :1 ; /// PAD_WL_STATE's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_btif_gpio2_ps             :1 ; /// PAD_WL_STATE's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_btif_gpio2_drv            :1 ; /// PAD_WL_STATE's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_btif_gpio2_mode           :1 ; /// PAD_WL_STATE's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_btif_gpio3_in             :1 ; /// PAD_WL_PRIOR's input value in gpio mode
    u32 reg_btif_gpio3_out            :1 ; /// PAD_WL_PRIOR's output value in gpio mode
    u32 reg_btif_gpio3_oen            :1 ; /// PAD_WL_PRIOR's output enable(active low) in gpio mode
    u32 :1 ; /// [0x01]
    u32 reg_btif_gpio3_pe             :1 ; /// PAD_WL_PRIOR's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_btif_gpio3_ps             :1 ; /// PAD_WL_PRIOR's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_btif_gpio3_drv            :1 ; /// PAD_WL_PRIOR's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_btif_gpio3_mode           :1 ; /// PAD_WL_PRIOR's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x01]
    /* [0x02] */
    u32 reg_btif_gpio4_in             :1 ; /// PAD_WL_FREQ's input value in gpio mode
    u32 reg_btif_gpio4_out            :1 ; /// PAD_WL_FREQ's output value in gpio mode
    u32 reg_btif_gpio4_oen            :1 ; /// PAD_WL_FREQ's output enable(active low) in gpio mode
    u32 :1 ; /// [0x02]
    u32 reg_btif_gpio4_pe             :1 ; /// PAD_WL_FREQ's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_btif_gpio4_ps             :1 ; /// PAD_WL_FREQ's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_btif_gpio4_drv            :1 ; /// PAD_WL_FREQ's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_btif_gpio4_mode           :1 ; /// PAD_WL_FREQ's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_btif_gpio5_in             :1 ; /// PAD_WL_ACT's input value in gpio mode
    u32 reg_btif_gpio5_out            :1 ; /// PAD_WL_ACT's output value in gpio mode
    u32 reg_btif_gpio5_oen            :1 ; /// PAD_WL_ACT's output enable(active low) in gpio mode
    u32 :1 ; /// [0x02]
    u32 reg_btif_gpio5_pe             :1 ; /// PAD_WL_ACT's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_btif_gpio5_ps             :1 ; /// PAD_WL_ACT's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_btif_gpio5_drv            :1 ; /// PAD_WL_ACT's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_btif_gpio5_mode           :1 ; /// PAD_WL_ACT's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x02]
    u32 :32; /// [0x03]
    u32 :32; /// [0x04]
    /* [0x05] */
    u32 reg_int_gpio0_in              :1 ; /// PAD_INT0's input value in gpio mode
    u32 reg_int_gpio0_out             :1 ; /// PAD_INT0's output value in gpio mode
    u32 reg_int_gpio0_oen             :1 ; /// PAD_INT0's output enable(active low) in gpio mode
    u32 reg_int_gpio0_drv1            :1 ; /// PAD_INT0's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_int_gpio0_pe              :1 ; /// PAD_INT0's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_int_gpio0_ps              :1 ; /// PAD_INT0's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_int_gpio0_drv             :1 ; /// PAD_INT0's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_int_gpio0_mode            :1 ; /// PAD_INT0's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_int_gpio1_in              :1 ; /// PAD_INT1's input value in gpio mode
    u32 reg_int_gpio1_out             :1 ; /// PAD_INT1's output value in gpio mode
    u32 reg_int_gpio1_oen             :1 ; /// PAD_INT1's output enable(active low) in gpio mode
    u32 reg_int_gpio1_drv1            :1 ; /// PAD_INT1's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_int_gpio1_pe              :1 ; /// PAD_INT1's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_int_gpio1_ps              :1 ; /// PAD_INT1's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_int_gpio1_drv             :1 ; /// PAD_INT1's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_int_gpio1_mode            :1 ; /// PAD_INT1's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x05]
    /* [0x06] */
    u32 reg_cmmb_gpio0_in             :1 ; /// PAD_CMMB_GPIO1's input value in gpio mode
    u32 reg_cmmb_gpio0_out            :1 ; /// PAD_CMMB_GPIO1's output value in gpio mode
    u32 reg_cmmb_gpio0_oen            :1 ; /// PAD_CMMB_GPIO1's output enable(active low) in gpio mode
    u32 reg_cmmb_gpio0_drv1           :1 ; /// PAD_CMMB_GPIO1's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_cmmb_gpio0_pe             :1 ; /// PAD_CMMB_GPIO1's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_cmmb_gpio0_ps             :1 ; /// PAD_CMMB_GPIO1's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_cmmb_gpio0_drv            :1 ; /// PAD_CMMB_GPIO1's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_cmmb_gpio0_mode           :1 ; /// PAD_CMMB_GPIO1's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_cmmb_gpio1_in             :1 ; /// PAD_CMMB_GPIO2's input value in gpio mode
    u32 reg_cmmb_gpio1_out            :1 ; /// PAD_CMMB_GPIO2's output value in gpio mode
    u32 reg_cmmb_gpio1_oen            :1 ; /// PAD_CMMB_GPIO2's output enable(active low) in gpio mode
    u32 reg_cmmb_gpio1_drv1           :1 ; /// PAD_CMMB_GPIO2's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_cmmb_gpio1_pe             :1 ; /// PAD_CMMB_GPIO2's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_cmmb_gpio1_ps             :1 ; /// PAD_CMMB_GPIO2's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_cmmb_gpio1_drv            :1 ; /// PAD_CMMB_GPIO2's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_cmmb_gpio1_mode           :1 ; /// PAD_CMMB_GPIO2's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x06]
    /* [0x07] */
    u32 reg_cmmb_gpio2_in             :1 ; /// PAD_CMMB_GPIO3's input value in gpio mode
    u32 reg_cmmb_gpio2_out            :1 ; /// PAD_CMMB_GPIO3's output value in gpio mode
    u32 reg_cmmb_gpio2_oen            :1 ; /// PAD_CMMB_GPIO3's output enable(active low) in gpio mode
    u32 reg_cmmb_gpio2_drv1           :1 ; /// PAD_CMMB_GPIO3's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_cmmb_gpio2_pe             :1 ; /// PAD_CMMB_GPIO3's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_cmmb_gpio2_ps             :1 ; /// PAD_CMMB_GPIO3's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_cmmb_gpio2_drv            :1 ; /// PAD_CMMB_GPIO3's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_cmmb_gpio2_mode           :1 ; /// PAD_CMMB_GPIO3's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :24; /// [0x07]
    /* [0x08] */
    u32 reg_mpif_gpio0_in             :1 ; /// PAD_MPIF_GPIO1's input value in gpio mode
    u32 reg_mpif_gpio0_out            :1 ; /// PAD_MPIF_GPIO1's output value in gpio mode
    u32 reg_mpif_gpio0_oen            :1 ; /// PAD_MPIF_GPIO1's output enable(active low) in gpio mode
    u32 reg_mpif_gpio0_drv1           :1 ; /// PAD_MPIF_GPIO1's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio0_pe             :1 ; /// PAD_MPIF_GPIO1's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_mpif_gpio0_ps             :1 ; /// PAD_MPIF_GPIO1's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_mpif_gpio0_drv            :1 ; /// PAD_MPIF_GPIO1's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio0_mode           :1 ; /// PAD_MPIF_GPIO1's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_mpif_gpio1_in             :1 ; /// PAD_MPIF_GPIO2's input value in gpio mode
    u32 reg_mpif_gpio1_out            :1 ; /// PAD_MPIF_GPIO2's output value in gpio mode
    u32 reg_mpif_gpio1_oen            :1 ; /// PAD_MPIF_GPIO2's output enable(active low) in gpio mode
    u32 reg_mpif_gpio1_drv1           :1 ; /// PAD_MPIF_GPIO2's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio1_pe             :1 ; /// PAD_MPIF_GPIO2's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_mpif_gpio1_ps             :1 ; /// PAD_MPIF_GPIO2's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_mpif_gpio1_drv            :1 ; /// PAD_MPIF_GPIO2's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio1_mode           :1 ; /// PAD_MPIF_GPIO2's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x08]
    /* [0x09] */
    u32 reg_mpif_gpio2_in             :1 ; /// PAD_MPIF_CS0N's input value in gpio mode
    u32 reg_mpif_gpio2_out            :1 ; /// PAD_MPIF_CS0N's output value in gpio mode
    u32 reg_mpif_gpio2_oen            :1 ; /// PAD_MPIF_CS0N's output enable(active low) in gpio mode
    u32 reg_mpif_gpio2_drv1           :1 ; /// PAD_MPIF_CS0N's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio2_pe             :1 ; /// PAD_MPIF_CS0N's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_mpif_gpio2_ps             :1 ; /// PAD_MPIF_CS0N's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_mpif_gpio2_drv            :1 ; /// PAD_MPIF_CS0N's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio2_mode           :1 ; /// PAD_MPIF_CS0N's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_mpif_gpio3_in             :1 ; /// PAD_MPIF_CLK's input value in gpio mode
    u32 reg_mpif_gpio3_out            :1 ; /// PAD_MPIF_CLK's output value in gpio mode
    u32 reg_mpif_gpio3_oen            :1 ; /// PAD_MPIF_CLK's output enable(active low) in gpio mode
    u32 reg_mpif_gpio3_drv1           :1 ; /// PAD_MPIF_CLK's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio3_pe             :1 ; /// PAD_MPIF_CLK's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_mpif_gpio3_ps             :1 ; /// PAD_MPIF_CLK's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_mpif_gpio3_drv            :1 ; /// PAD_MPIF_CLK's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio3_mode           :1 ; /// PAD_MPIF_CLK's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x09]
    /* [0x0A] */
    u32 reg_mpif_gpio4_in             :1 ; /// PAD_MPIF_BUSY's input value in gpio mode
    u32 reg_mpif_gpio4_out            :1 ; /// PAD_MPIF_BUSY's output value in gpio mode
    u32 reg_mpif_gpio4_oen            :1 ; /// PAD_MPIF_BUSY's output enable(active low) in gpio mode
    u32 reg_mpif_gpio4_drv1           :1 ; /// PAD_MPIF_BUSY's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio4_pe             :1 ; /// PAD_MPIF_BUSY's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_mpif_gpio4_ps             :1 ; /// PAD_MPIF_BUSY's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_mpif_gpio4_drv            :1 ; /// PAD_MPIF_BUSY's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio4_mode           :1 ; /// PAD_MPIF_BUSY's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_mpif_gpio5_in             :1 ; /// PAD_MPIF_D0's input value in gpio mode
    u32 reg_mpif_gpio5_out            :1 ; /// PAD_MPIF_D0's output value in gpio mode
    u32 reg_mpif_gpio5_oen            :1 ; /// PAD_MPIF_D0's output enable(active low) in gpio mode
    u32 reg_mpif_gpio5_drv1           :1 ; /// PAD_MPIF_D0's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio5_pe             :1 ; /// PAD_MPIF_D0's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_mpif_gpio5_ps             :1 ; /// PAD_MPIF_D0's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_mpif_gpio5_drv            :1 ; /// PAD_MPIF_D0's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio5_mode           :1 ; /// PAD_MPIF_D0's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x0A]
    /* [0x0B] */
    u32 reg_mpif_gpio6_in             :1 ; /// PAD_MPIF_D1's input value in gpio mode
    u32 reg_mpif_gpio6_out            :1 ; /// PAD_MPIF_D1's output value in gpio mode
    u32 reg_mpif_gpio6_oen            :1 ; /// PAD_MPIF_D1's output enable(active low) in gpio mode
    u32 reg_mpif_gpio6_drv1           :1 ; /// PAD_MPIF_D1's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio6_pe             :1 ; /// PAD_MPIF_D1's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_mpif_gpio6_ps             :1 ; /// PAD_MPIF_D1's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_mpif_gpio6_drv            :1 ; /// PAD_MPIF_D1's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio6_mode           :1 ; /// PAD_MPIF_D1's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_mpif_gpio7_in             :1 ; /// PAD_MPIF_D2's input value in gpio mode
    u32 reg_mpif_gpio7_out            :1 ; /// PAD_MPIF_D2's output value in gpio mode
    u32 reg_mpif_gpio7_oen            :1 ; /// PAD_MPIF_D2's output enable(active low) in gpio mode
    u32 reg_mpif_gpio7_drv1           :1 ; /// PAD_MPIF_D2's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio7_pe             :1 ; /// PAD_MPIF_D2's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_mpif_gpio7_ps             :1 ; /// PAD_MPIF_D2's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_mpif_gpio7_drv            :1 ; /// PAD_MPIF_D2's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio7_mode           :1 ; /// PAD_MPIF_D2's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x0B]
    /* [0x0C] */
    u32 reg_mpif_gpio8_in             :1 ; /// PAD_MPIF_D3's input value in gpio mode
    u32 reg_mpif_gpio8_out            :1 ; /// PAD_MPIF_D3's output value in gpio mode
    u32 reg_mpif_gpio8_oen            :1 ; /// PAD_MPIF_D3's output enable(active low) in gpio mode
    u32 reg_mpif_gpio8_drv1           :1 ; /// PAD_MPIF_D3's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio8_pe             :1 ; /// PAD_MPIF_D3's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_mpif_gpio8_ps             :1 ; /// PAD_MPIF_D3's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_mpif_gpio8_drv            :1 ; /// PAD_MPIF_D3's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_mpif_gpio8_mode           :1 ; /// PAD_MPIF_D3's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :24; /// [0x0C]
    /* [0x0D] */
    u32 reg_sim1_gpio0_in             :1 ; /// PAD_USIM1DATA's input value in gpio mode
    u32 reg_sim1_gpio0_out            :1 ; /// PAD_USIM1DATA's output value in gpio mode
    u32 reg_sim1_gpio0_oen            :1 ; /// PAD_USIM1DATA's output enable(active low) in gpio mode
    u32 :3 ; /// [0x0D]
    u32 reg_sim1_gpio0_drv            :1 ; /// PAD_USIM1DATA's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sim1_gpio0_mode           :1 ; /// PAD_USIM1DATA's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_sim1_gpio1_in             :1 ; /// PAD_USIM1RST's input value in gpio mode
    u32 reg_sim1_gpio1_out            :1 ; /// PAD_USIM1RST's output value in gpio mode
    u32 reg_sim1_gpio1_oen            :1 ; /// PAD_USIM1RST's output enable(active low) in gpio mode
    u32 :3 ; /// [0x0D]
    u32 reg_sim1_gpio1_drv            :1 ; /// PAD_USIM1RST's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sim1_gpio1_mode           :1 ; /// PAD_USIM1RST's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x0D]
    /* [0x0E] */
    u32 reg_sim1_gpio2_in             :1 ; /// PAD_USIM1CLK's input value in gpio mode
    u32 reg_sim1_gpio2_out            :1 ; /// PAD_USIM1CLK's output value in gpio mode
    u32 reg_sim1_gpio2_oen            :1 ; /// PAD_USIM1CLK's output enable(active low) in gpio mode
    u32 :3 ; /// [0x0E]
    u32 reg_sim1_gpio2_drv            :1 ; /// PAD_USIM1CLK's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sim1_gpio2_mode           :1 ; /// PAD_USIM1CLK's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :24; /// [0x0E]
    /* [0x0F] */
    u32 reg_sim2_gpio0_in             :1 ; /// PAD_USIM2DATA's input value in gpio mode
    u32 reg_sim2_gpio0_out            :1 ; /// PAD_USIM2DATA's output value in gpio mode
    u32 reg_sim2_gpio0_oen            :1 ; /// PAD_USIM2DATA's output enable(active low) in gpio mode
    u32 :3 ; /// [0x0F]
    u32 reg_sim2_gpio0_drv            :1 ; /// PAD_USIM2DATA's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sim2_gpio0_mode           :1 ; /// PAD_USIM2DATA's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_sim2_gpio1_in             :1 ; /// PAD_USIM2RST's input value in gpio mode
    u32 reg_sim2_gpio1_out            :1 ; /// PAD_USIM2RST's output value in gpio mode
    u32 reg_sim2_gpio1_oen            :1 ; /// PAD_USIM2RST's output enable(active low) in gpio mode
    u32 :3 ; /// [0x0F]
    u32 reg_sim2_gpio1_drv            :1 ; /// PAD_USIM2RST's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sim2_gpio1_mode           :1 ; /// PAD_USIM2RST's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x0F]
    /* [0x10] */
    u32 reg_sim2_gpio2_in             :1 ; /// PAD_USIM2CLK's input value in gpio mode
    u32 reg_sim2_gpio2_out            :1 ; /// PAD_USIM2CLK's output value in gpio mode
    u32 reg_sim2_gpio2_oen            :1 ; /// PAD_USIM2CLK's output enable(active low) in gpio mode
    u32 :3 ; /// [0x10]
    u32 reg_sim2_gpio2_drv            :1 ; /// PAD_USIM2CLK's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sim2_gpio2_mode           :1 ; /// PAD_USIM2CLK's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :24; /// [0x10]
    /* [0x11] */
    u32 reg_col_gpio0_in              :1 ; /// PAD_COL[0]'s input value in gpio mode
    u32 reg_col_gpio0_out             :1 ; /// PAD_COL[0]'s output value in gpio mode
    u32 reg_col_gpio0_oen             :1 ; /// PAD_COL[0]'s output enable(active low) in gpio mode
    u32 reg_col_gpio0_drv1            :1 ; /// PAD_COL[0]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_col_gpio0_pe              :1 ; /// PAD_COL[0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_col_gpio0_ps              :1 ; /// PAD_COL[0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_col_gpio0_drv             :1 ; /// PAD_COL[0]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_col_gpio0_mode            :1 ; /// PAD_COL[0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_col_gpio1_in              :1 ; /// PAD_COL[1]'s input value in gpio mode
    u32 reg_col_gpio1_out             :1 ; /// PAD_COL[1]'s output value in gpio mode
    u32 reg_col_gpio1_oen             :1 ; /// PAD_COL[1]'s output enable(active low) in gpio mode
    u32 reg_col_gpio1_drv1            :1 ; /// PAD_COL[1]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_col_gpio1_pe              :1 ; /// PAD_COL[1]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_col_gpio1_ps              :1 ; /// PAD_COL[1]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_col_gpio1_drv             :1 ; /// PAD_COL[1]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_col_gpio1_mode            :1 ; /// PAD_COL[1]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x11]
    /* [0x12] */
    u32 reg_col_gpio2_in              :1 ; /// PAD_COL[2]'s input value in gpio mode
    u32 reg_col_gpio2_out             :1 ; /// PAD_COL[2]'s output value in gpio mode
    u32 reg_col_gpio2_oen             :1 ; /// PAD_COL[2]'s output enable(active low) in gpio mode
    u32 reg_col_gpio2_drv1            :1 ; /// PAD_COL[2]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_col_gpio2_pe              :1 ; /// PAD_COL[2]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_col_gpio2_ps              :1 ; /// PAD_COL[2]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_col_gpio2_drv             :1 ; /// PAD_COL[2]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_col_gpio2_mode            :1 ; /// PAD_COL[2]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_col_gpio3_in              :1 ; /// PAD_COL[3]'s input value in gpio mode
    u32 reg_col_gpio3_out             :1 ; /// PAD_COL[3]'s output value in gpio mode
    u32 reg_col_gpio3_oen             :1 ; /// PAD_COL[3]'s output enable(active low) in gpio mode
    u32 reg_col_gpio3_drv1            :1 ; /// PAD_COL[3]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_col_gpio3_pe              :1 ; /// PAD_COL[3]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_col_gpio3_ps              :1 ; /// PAD_COL[3]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_col_gpio3_drv             :1 ; /// PAD_COL[3]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_col_gpio3_mode            :1 ; /// PAD_COL[3]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x12]
    /* [0x13] */
    u32 reg_col_gpio4_in              :1 ; /// PAD_COL[4]'s input value in gpio mode
    u32 reg_col_gpio4_out             :1 ; /// PAD_COL[4]'s output value in gpio mode
    u32 reg_col_gpio4_oen             :1 ; /// PAD_COL[4]'s output enable(active low) in gpio mode
    u32 reg_col_gpio4_drv1            :1 ; /// PAD_COL[4]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_col_gpio4_pe              :1 ; /// PAD_COL[4]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_col_gpio4_ps              :1 ; /// PAD_COL[4]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_col_gpio4_drv             :1 ; /// PAD_COL[4]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_col_gpio4_mode            :1 ; /// PAD_COL[4]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_col_gpio5_in              :1 ; /// PAD_COL[5]'s input value in gpio mode
    u32 reg_col_gpio5_out             :1 ; /// PAD_COL[5]'s output value in gpio mode
    u32 reg_col_gpio5_oen             :1 ; /// PAD_COL[5]'s output enable(active low) in gpio mode
    u32 reg_col_gpio5_drv1            :1 ; /// PAD_COL[5]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_col_gpio5_pe              :1 ; /// PAD_COL[5]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_col_gpio5_ps              :1 ; /// PAD_COL[5]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_col_gpio5_drv             :1 ; /// PAD_COL[5]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_col_gpio5_mode            :1 ; /// PAD_COL[5]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x13]
    /* [0x14] */
    u32 reg_col_gpio6_in              :1 ; /// PAD_COL[6]'s input value in gpio mode
    u32 reg_col_gpio6_out             :1 ; /// PAD_COL[6]'s output value in gpio mode
    u32 reg_col_gpio6_oen             :1 ; /// PAD_COL[6]'s output enable(active low) in gpio mode
    u32 reg_col_gpio6_drv1            :1 ; /// PAD_COL[6]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_col_gpio6_pe              :1 ; /// PAD_COL[6]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_col_gpio6_ps              :1 ; /// PAD_COL[6]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_col_gpio6_drv             :1 ; /// PAD_COL[6]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_col_gpio6_mode            :1 ; /// PAD_COL[6]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :24; /// [0x14]
    /* [0x15] */
    u32 reg_row_gpio0_in              :1 ; /// PAD_ROW[0]'s input value in gpio mode
    u32 reg_row_gpio0_out             :1 ; /// PAD_ROW[0]'s output value in gpio mode
    u32 reg_row_gpio0_oen             :1 ; /// PAD_ROW[0]'s output enable(active low) in gpio mode
    u32 reg_row_gpio0_drv1            :1 ; /// PAD_ROW[0]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_row_gpio0_pe              :1 ; /// PAD_ROW[0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_row_gpio0_ps              :1 ; /// PAD_ROW[0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_row_gpio0_drv             :1 ; /// PAD_ROW[0]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_row_gpio0_mode            :1 ; /// PAD_ROW[0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_row_gpio1_in              :1 ; /// PAD_ROW[1]'s input value in gpio mode
    u32 reg_row_gpio1_out             :1 ; /// PAD_ROW[1]'s output value in gpio mode
    u32 reg_row_gpio1_oen             :1 ; /// PAD_ROW[1]'s output enable(active low) in gpio mode
    u32 reg_row_gpio1_drv1            :1 ; /// PAD_ROW[1]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_row_gpio1_pe              :1 ; /// PAD_ROW[1]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_row_gpio1_ps              :1 ; /// PAD_ROW[1]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_row_gpio1_drv             :1 ; /// PAD_ROW[1]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_row_gpio1_mode            :1 ; /// PAD_ROW[1]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x15]
    /* [0x16] */
    u32 reg_row_gpio2_in              :1 ; /// PAD_ROW[2]'s input value in gpio mode
    u32 reg_row_gpio2_out             :1 ; /// PAD_ROW[2]'s output value in gpio mode
    u32 reg_row_gpio2_oen             :1 ; /// PAD_ROW[2]'s output enable(active low) in gpio mode
    u32 reg_row_gpio2_drv1            :1 ; /// PAD_ROW[2]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_row_gpio2_pe              :1 ; /// PAD_ROW[2]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_row_gpio2_ps              :1 ; /// PAD_ROW[2]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_row_gpio2_drv             :1 ; /// PAD_ROW[2]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_row_gpio2_mode            :1 ; /// PAD_ROW[2]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_row_gpio3_in              :1 ; /// PAD_ROW[3]'s input value in gpio mode
    u32 reg_row_gpio3_out             :1 ; /// PAD_ROW[3]'s output value in gpio mode
    u32 reg_row_gpio3_oen             :1 ; /// PAD_ROW[3]'s output enable(active low) in gpio mode
    u32 reg_row_gpio3_drv1            :1 ; /// PAD_ROW[3]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_row_gpio3_pe              :1 ; /// PAD_ROW[3]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_row_gpio3_ps              :1 ; /// PAD_ROW[3]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_row_gpio3_drv             :1 ; /// PAD_ROW[3]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_row_gpio3_mode            :1 ; /// PAD_ROW[3]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x16]
    /* [0x17] */
    u32 reg_row_gpio4_in              :1 ; /// PAD_ROW[4]'s input value in gpio mode
    u32 reg_row_gpio4_out             :1 ; /// PAD_ROW[4]'s output value in gpio mode
    u32 reg_row_gpio4_oen             :1 ; /// PAD_ROW[4]'s output enable(active low) in gpio mode
    u32 reg_row_gpio4_drv1            :1 ; /// PAD_ROW[4]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_row_gpio4_pe              :1 ; /// PAD_ROW[4]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_row_gpio4_ps              :1 ; /// PAD_ROW[4]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_row_gpio4_drv             :1 ; /// PAD_ROW[4]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_row_gpio4_mode            :1 ; /// PAD_ROW[4]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_row_gpio5_in              :1 ; /// PAD_ROW[5]'s input value in gpio mode
    u32 reg_row_gpio5_out             :1 ; /// PAD_ROW[5]'s output value in gpio mode
    u32 reg_row_gpio5_oen             :1 ; /// PAD_ROW[5]'s output enable(active low) in gpio mode
    u32 reg_row_gpio5_drv1            :1 ; /// PAD_ROW[5]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_row_gpio5_pe              :1 ; /// PAD_ROW[5]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_row_gpio5_ps              :1 ; /// PAD_ROW[5]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_row_gpio5_drv             :1 ; /// PAD_ROW[5]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_row_gpio5_mode            :1 ; /// PAD_ROW[5]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x17]
    /* [0x18] */
    u32 reg_sd_gpio0_in               :1 ; /// PAD_SD_D[0]'s input value in gpio mode
    u32 reg_sd_gpio0_out              :1 ; /// PAD_SD_D[0]'s output value in gpio mode
    u32 reg_sd_gpio0_oen              :1 ; /// PAD_SD_D[0]'s output enable(active low) in gpio mode
    u32 reg_sd_gpio0_drv1             :1 ; /// PAD_SD_D[0]'s drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sd_gpio0_pe               :1 ; /// PAD_SD_D[0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sd_gpio0_ps               :1 ; /// PAD_SD_D[0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sd_gpio0_drv              :1 ; /// PAD_SD_D[0]'s drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sd_gpio0_mode             :1 ; /// PAD_SD_D[0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_sd_gpio1_in               :1 ; /// PAD_SD_D[1]'s input value in gpio mode
    u32 reg_sd_gpio1_out              :1 ; /// PAD_SD_D[1]'s output value in gpio mode
    u32 reg_sd_gpio1_oen              :1 ; /// PAD_SD_D[1]'s output enable(active low) in gpio mode
    u32 reg_sd_gpio1_drv1             :1 ; /// PAD_SD_D[1]'s drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sd_gpio1_pe               :1 ; /// PAD_SD_D[1]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sd_gpio1_ps               :1 ; /// PAD_SD_D[1]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sd_gpio1_drv              :1 ; /// PAD_SD_D[1]'s drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sd_gpio1_mode             :1 ; /// PAD_SD_D[1]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x18]
    /* [0x19] */
    u32 reg_sd_gpio2_in               :1 ; /// PAD_SD_D[2]'s input value in gpio mode
    u32 reg_sd_gpio2_out              :1 ; /// PAD_SD_D[2]'s output value in gpio mode
    u32 reg_sd_gpio2_oen              :1 ; /// PAD_SD_D[2]'s output enable(active low) in gpio mode
    u32 reg_sd_gpio2_drv1             :1 ; /// PAD_SD_D[2]'s drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sd_gpio2_pe               :1 ; /// PAD_SD_D[2]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sd_gpio2_ps               :1 ; /// PAD_SD_D[2]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sd_gpio2_drv              :1 ; /// PAD_SD_D[2]'s drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sd_gpio2_mode             :1 ; /// PAD_SD_D[2]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_sd_gpio3_in               :1 ; /// PAD_SD_D[3]'s input value in gpio mode
    u32 reg_sd_gpio3_out              :1 ; /// PAD_SD_D[3]'s output value in gpio mode
    u32 reg_sd_gpio3_oen              :1 ; /// PAD_SD_D[3]'s output enable(active low) in gpio mode
    u32 reg_sd_gpio3_drv1             :1 ; /// PAD_SD_D[3]'s drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sd_gpio3_pe               :1 ; /// PAD_SD_D[3]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sd_gpio3_ps               :1 ; /// PAD_SD_D[3]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sd_gpio3_drv              :1 ; /// PAD_SD_D[3]'s drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sd_gpio3_mode             :1 ; /// PAD_SD_D[3]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x19]
    /* [0x1A] */
    u32 reg_sd_gpio4_in               :1 ; /// PAD_SD_CDZ's input value in gpio mode
    u32 reg_sd_gpio4_out              :1 ; /// PAD_SD_CDZ's output value in gpio mode
    u32 reg_sd_gpio4_oen              :1 ; /// PAD_SD_CDZ's output enable(active low) in gpio mode
    u32 reg_sd_gpio4_drv1             :1 ; /// PAD_SD_CDZ's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sd_gpio4_pe               :1 ; /// PAD_SD_CDZ's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sd_gpio4_ps               :1 ; /// PAD_SD_CDZ's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sd_gpio4_drv              :1 ; /// PAD_SD_CDZ's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sd_gpio4_mode             :1 ; /// PAD_SD_CDZ's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_sd_gpio5_in               :1 ; /// PAD_SD_CLK's input value in gpio mode
    u32 reg_sd_gpio5_out              :1 ; /// PAD_SD_CLK's output value in gpio mode
    u32 reg_sd_gpio5_oen              :1 ; /// PAD_SD_CLK's output enable(active low) in gpio mode
    u32 reg_sd_gpio5_drv1             :1 ; /// PAD_SD_CLK's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sd_gpio5_pe               :1 ; /// PAD_SD_CLK's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sd_gpio5_ps               :1 ; /// PAD_SD_CLK's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sd_gpio5_drv              :1 ; /// PAD_SD_CLK's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sd_gpio5_mode             :1 ; /// PAD_SD_CLK's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x1A]
    /* [0x1B] */
    u32 reg_sd_gpio6_in               :1 ; /// PAD_SD_CMD's input value in gpio mode
    u32 reg_sd_gpio6_out              :1 ; /// PAD_SD_CMD's output value in gpio mode
    u32 reg_sd_gpio6_oen              :1 ; /// PAD_SD_CMD's output enable(active low) in gpio mode
    u32 reg_sd_gpio6_drv1             :1 ; /// PAD_SD_CMD's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sd_gpio6_pe               :1 ; /// PAD_SD_CMD's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sd_gpio6_ps               :1 ; /// PAD_SD_CMD's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sd_gpio6_drv              :1 ; /// PAD_SD_CMD's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_sd_gpio6_mode             :1 ; /// PAD_SD_CMD's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :24; /// [0x1B]
    /* [0x1C] */
    u32 reg_i2s_gpio0_in              :1 ; /// PAD_I2SBCLK's input value in gpio mode
    u32 reg_i2s_gpio0_out             :1 ; /// PAD_I2SBCLK's output value in gpio mode
    u32 reg_i2s_gpio0_oen             :1 ; /// PAD_I2SBCLK's output enable(active low) in gpio mode
    u32 reg_i2s_gpio0_drv1            :1 ; /// PAD_I2SBCLK's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_i2s_gpio0_pe              :1 ; /// PAD_I2SBCLK's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_i2s_gpio0_ps              :1 ; /// PAD_I2SBCLK's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_i2s_gpio0_drv             :1 ; /// PAD_I2SBCLK's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_i2s_gpio0_mode            :1 ; /// PAD_I2SBCLK's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_i2s_gpio1_in              :1 ; /// PAD_I2SDIO's input value in gpio mode
    u32 reg_i2s_gpio1_out             :1 ; /// PAD_I2SDIO's output value in gpio mode
    u32 reg_i2s_gpio1_oen             :1 ; /// PAD_I2SDIO's output enable(active low) in gpio mode
    u32 reg_i2s_gpio1_drv1            :1 ; /// PAD_I2SDIO's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_i2s_gpio1_pe              :1 ; /// PAD_I2SDIO's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_i2s_gpio1_ps              :1 ; /// PAD_I2SDIO's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_i2s_gpio1_drv             :1 ; /// PAD_I2SDIO's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_i2s_gpio1_mode            :1 ; /// PAD_I2SDIO's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x1C]
    /* [0x1D] */
    u32 reg_i2s_gpio2_in              :1 ; /// PAD_I2SWS's input value in gpio mode
    u32 reg_i2s_gpio2_out             :1 ; /// PAD_I2SWS's output value in gpio mode
    u32 reg_i2s_gpio2_oen             :1 ; /// PAD_I2SWS's output enable(active low) in gpio mode
    u32 reg_i2s_gpio2_drv1            :1 ; /// PAD_I2SWS's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_i2s_gpio2_pe              :1 ; /// PAD_I2SWS's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_i2s_gpio2_ps              :1 ; /// PAD_I2SWS's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_i2s_gpio2_drv             :1 ; /// PAD_I2SWS's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_i2s_gpio2_mode            :1 ; /// PAD_I2SWS's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :24; /// [0x1D]
    u32 :32; /// [0x1E]
    /* [0x1F] */
    u32 reg_uart_gpio0_in             :1 ; /// PAD_U0TXD's input value in gpio mode
    u32 reg_uart_gpio0_out            :1 ; /// PAD_U0TXD's output value in gpio mode
    u32 reg_uart_gpio0_oen            :1 ; /// PAD_U0TXD's output enable(active low) in gpio mode
    u32 :1 ; /// [0x1F]
    u32 reg_uart_gpio0_pe             :1 ; /// PAD_U0TXD's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_uart_gpio0_ps             :1 ; /// PAD_U0TXD's PU selection
                                           /// 1:pull-up disable
                                           /// 0:pull-up enable
    u32 reg_uart_gpio0_drv            :1 ; /// PAD_U0TXD's drive strength.  (DRV0)
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_uart_gpio0_mode           :1 ; /// PAD_U0TXD's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_uart_gpio1_in             :1 ; /// PAD_U0RXD's input value in gpio mode
    u32 reg_uart_gpio1_out            :1 ; /// PAD_U0RXD's output value in gpio mode
    u32 reg_uart_gpio1_oen            :1 ; /// PAD_U0RXD's output enable(active low) in gpio mode
    u32 :1 ; /// [0x1F]
    u32 reg_uart_gpio1_pe             :1 ; /// PAD_U0RXD's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_uart_gpio1_ps             :1 ; /// PAD_U0RXD's PU selection
                                           /// 1:pull-up disable
                                           /// 0:pull-up enable
    u32 reg_uart_gpio1_drv            :1 ; /// PAD_U0RXD's drive strength.  (DRV0)
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_uart_gpio1_mode           :1 ; /// PAD_U0RXD's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x1F]
    /* [0x20] */
    u32 reg_sys_gpio0_in              :1 ; /// PAD_BOOT_CTRL[0]'s input value in gpio mode
    u32 :2 ; /// [0x20]
    u32 reg_sys_gpio0_drv1            :1 ; /// PAD_BOOT_CTRL[0]'s drive strength. (DRV0)
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sys_gpio0_pe              :1 ; /// PAD_BOOT_CTRL[0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sys_gpio0_ps              :1 ; /// PAD_BOOT_CTRL[0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sys_gpio0_drv             :1 ; /// PAD_BOOT_CTRL[0]'s drive strength. (DRV0)
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 :1 ; /// [0x20]
    u32 reg_sys_gpio1_in              :1 ; /// PAD_BOOT_CTRL[1]'s input value in gpio mode
    u32 :2 ; /// [0x20]
    u32 reg_sys_gpio1_drv1            :1 ; /// PAD_BOOT_CTRL[1]'s drive strength. (DRV0)
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sys_gpio1_pe              :1 ; /// PAD_BOOT_CTRL[1]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sys_gpio1_ps              :1 ; /// PAD_BOOT_CTRL[1]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sys_gpio1_drv             :1 ; /// PAD_BOOT_CTRL[1]'s drive strength. (DRV0)
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 :17; /// [0x20]
    /* [0x21] */
    u32 reg_sys_gpio2_in              :1 ; /// PAD_BOOT_CTRL[2]'s input value in gpio mode
    u32 :2 ; /// [0x21]
    u32 reg_sys_gpio2_drv1            :1 ; /// PAD_BOOT_CTRL[2]'s drive strength. (DRV0)
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sys_gpio2_pe              :1 ; /// PAD_BOOT_CTRL[2]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sys_gpio2_ps              :1 ; /// PAD_BOOT_CTRL[2]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sys_gpio2_drv             :1 ; /// PAD_BOOT_CTRL[2]'s drive strength. (DRV0)
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 :1 ; /// [0x21]
    u32 reg_sys_gpio3_in              :1 ; /// PAD_BOOT_CTRL[3]'s input value in gpio mode
    u32 :2 ; /// [0x21]
    u32 reg_sys_gpio3_drv1            :1 ; /// PAD_BOOT_CTRL[3]'s drive strength. (DRV0)
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sys_gpio3_pe              :1 ; /// PAD_BOOT_CTRL[3]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sys_gpio3_ps              :1 ; /// PAD_BOOT_CTRL[3]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sys_gpio3_drv             :1 ; /// PAD_BOOT_CTRL[3]'s drive strength. (DRV0)
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 :17; /// [0x21]
    /* [0x22] */
    u32 :8 ; /// [0x22]
    u32 reg_sys_gpio5_in              :1 ; /// PAD_VMSEL's input value in gpio mode
    u32 :2 ; /// [0x22]
    u32 reg_sys_gpio5_drv1            :1 ; /// PAD_VMSEL's drive strength. (DRV0)
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sys_gpio5_pe              :1 ; /// PAD_VMSEL's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sys_gpio5_ps              :1 ; /// PAD_VMSEL's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sys_gpio5_drv             :1 ; /// PAD_VMSEL's drive strength. (DRV0)
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 :17; /// [0x22]
    u32 :32; /// [0x23]
    /* [0x24] */
    u32 reg_rf_gpio0_in               :1 ; /// PAD_TBUO0's input value in gpio mode
    u32 reg_rf_gpio0_out              :1 ; /// PAD_TBUO0's output value in gpio mode
    u32 reg_rf_gpio0_oen              :1 ; /// PAD_TBUO0's output enable(active low) in gpio mode
    u32 reg_rf_gpio0_drv1             :1 ; /// PAD_TBUO0's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_rf_gpio0_pe               :1 ; /// PAD_TBUO0's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_rf_gpio0_ps               :1 ; /// PAD_TBUO0's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_rf_gpio0_drv              :1 ; /// PAD_TBUO0's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_rf_gpio0_mode             :1 ; /// PAD_TBUO0's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :24; /// [0x24]
    /* [0x25] */
    u32 reg_rf_gpio2_in               :1 ; /// PAD_TBUO2's input value in gpio mode
    u32 reg_rf_gpio2_out              :1 ; /// PAD_TBUO2's output value in gpio mode
    u32 reg_rf_gpio2_oen              :1 ; /// PAD_TBUO2's output enable(active low) in gpio mode
    u32 reg_rf_gpio2_drv1             :1 ; /// PAD_TBUO2's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_rf_gpio2_pe               :1 ; /// PAD_TBUO2's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_rf_gpio2_ps               :1 ; /// PAD_TBUO2's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_rf_gpio2_drv              :1 ; /// PAD_TBUO2's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_rf_gpio2_mode             :1 ; /// PAD_TBUO2's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_rf_gpio3_in               :1 ; /// PAD_TBUO3's input value in gpio mode
    u32 reg_rf_gpio3_out              :1 ; /// PAD_TBUO3's output value in gpio mode
    u32 reg_rf_gpio3_oen              :1 ; /// PAD_TBUO3's output enable(active low) in gpio mode
    u32 reg_rf_gpio3_drv1             :1 ; /// PAD_TBUO3's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_rf_gpio3_pe               :1 ; /// PAD_TBUO3's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_rf_gpio3_ps               :1 ; /// PAD_TBUO3's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_rf_gpio3_drv              :1 ; /// PAD_TBUO3's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_rf_gpio3_mode             :1 ; /// PAD_TBUO3's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x25]
    /* [0x26] */
    u32 reg_rf_gpio4_in               :1 ; /// PAD_TBUO4's input value in gpio mode
    u32 reg_rf_gpio4_out              :1 ; /// PAD_TBUO4's output value in gpio mode
    u32 reg_rf_gpio4_oen              :1 ; /// PAD_TBUO4's output enable(active low) in gpio mode
    u32 reg_rf_gpio4_drv1             :1 ; /// PAD_TBUO4's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_rf_gpio4_pe               :1 ; /// PAD_TBUO4's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_rf_gpio4_ps               :1 ; /// PAD_TBUO4's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_rf_gpio4_drv              :1 ; /// PAD_TBUO4's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_rf_gpio4_mode             :1 ; /// PAD_TBUO4's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_rf_gpio5_in               :1 ; /// PAD_TBUO5's input value in gpio mode
    u32 reg_rf_gpio5_out              :1 ; /// PAD_TBUO5's output value in gpio mode
    u32 reg_rf_gpio5_oen              :1 ; /// PAD_TBUO5's output enable(active low) in gpio mode
    u32 reg_rf_gpio5_drv1             :1 ; /// PAD_TBUO5's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_rf_gpio5_pe               :1 ; /// PAD_TBUO5's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_rf_gpio5_ps               :1 ; /// PAD_TBUO5's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_rf_gpio5_drv              :1 ; /// PAD_TBUO5's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_rf_gpio5_mode             :1 ; /// PAD_TBUO5's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x26]
    /* [0x27] */
    u32 reg_rf_gpio6_in               :1 ; /// PAD_TBUO6's input value in gpio mode
    u32 reg_rf_gpio6_out              :1 ; /// PAD_TBUO6's output value in gpio mode
    u32 reg_rf_gpio6_oen              :1 ; /// PAD_TBUO6's output enable(active low) in gpio mode
    u32 reg_rf_gpio6_drv1             :1 ; /// PAD_TBUO6's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_rf_gpio6_pe               :1 ; /// PAD_TBUO6's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_rf_gpio6_ps               :1 ; /// PAD_TBUO6's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_rf_gpio6_drv              :1 ; /// PAD_TBUO6's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_rf_gpio6_mode             :1 ; /// PAD_TBUO6's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :24; /// [0x27]
    u32 :32; /// [0x28]
    u32 :32; /// [0x29]
    /* [0x2A] */
    u32 reg_sr_gpio0_in               :1 ; /// PAD_SR_GPIO's input value in gpio mode
    u32 reg_sr_gpio0_out              :1 ; /// PAD_SR_GPIO's output value in gpio mode
    u32 reg_sr_gpio0_oen              :1 ; /// PAD_SR_GPIO's output enable(active low) in gpio mode
    u32 reg_sr_gpio0_drv1             :1 ; /// PAD_SR_GPIO's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio0_pe               :1 ; /// PAD_SR_GPIO's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sr_gpio0_ps               :1 ; /// PAD_SR_GPIO's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sr_gpio0_drv              :1 ; /// PAD_SR_GPIO's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio0_mode             :1 ; /// PAD_SR_GPIO's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_sr_gpio1_in               :1 ; /// PAD_SR_D[0]'s input value in gpio mode
    u32 reg_sr_gpio1_out              :1 ; /// PAD_SR_D[0]'s output value in gpio mode
    u32 reg_sr_gpio1_oen              :1 ; /// PAD_SR_D[0]'s output enable(active low) in gpio mode
    u32 reg_sr_gpio1_drv1             :1 ; /// PAD_SR_D[0]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio1_pe               :1 ; /// PAD_SR_D[0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sr_gpio1_ps               :1 ; /// PAD_SR_D[0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sr_gpio1_drv              :1 ; /// PAD_SR_D[0]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio1_mode             :1 ; /// PAD_SR_D[0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x2A]
    /* [0x2B] */
    u32 reg_sr_gpio2_in               :1 ; /// PAD_SR_D[1]'s input value in gpio mode
    u32 reg_sr_gpio2_out              :1 ; /// PAD_SR_D[1]'s output value in gpio mode
    u32 reg_sr_gpio2_oen              :1 ; /// PAD_SR_D[1]'s output enable(active low) in gpio mode
    u32 reg_sr_gpio2_drv1             :1 ; /// PAD_SR_D[1]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio2_pe               :1 ; /// PAD_SR_D[1]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sr_gpio2_ps               :1 ; /// PAD_SR_D[1]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sr_gpio2_drv              :1 ; /// PAD_SR_D[1]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio2_mode             :1 ; /// PAD_SR_D[1]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_sr_gpio3_in               :1 ; /// PAD_SR_D[2]'s input value in gpio mode
    u32 reg_sr_gpio3_out              :1 ; /// PAD_SR_D[2]'s output value in gpio mode
    u32 reg_sr_gpio3_oen              :1 ; /// PAD_SR_D[2]'s output enable(active low) in gpio mode
    u32 reg_sr_gpio3_drv1             :1 ; /// PAD_SR_D[2]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio3_pe               :1 ; /// PAD_SR_D[2]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sr_gpio3_ps               :1 ; /// PAD_SR_D[2]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sr_gpio3_drv              :1 ; /// PAD_SR_D[2]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio3_mode             :1 ; /// PAD_SR_D[2]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x2B]
    /* [0x2C] */
    u32 reg_sr_gpio4_in               :1 ; /// PAD_SR_D[3]'s input value in gpio mode
    u32 reg_sr_gpio4_out              :1 ; /// PAD_SR_D[3]'s output value in gpio mode
    u32 reg_sr_gpio4_oen              :1 ; /// PAD_SR_D[3]'s output enable(active low) in gpio mode
    u32 reg_sr_gpio4_drv1             :1 ; /// PAD_SR_D[3]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio4_pe               :1 ; /// PAD_SR_D[3]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sr_gpio4_ps               :1 ; /// PAD_SR_D[3]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sr_gpio4_drv              :1 ; /// PAD_SR_D[3]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio4_mode             :1 ; /// PAD_SR_D[3]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_sr_gpio5_in               :1 ; /// PAD_SR_D[4]'s input value in gpio mode
    u32 reg_sr_gpio5_out              :1 ; /// PAD_SR_D[4]'s output value in gpio mode
    u32 reg_sr_gpio5_oen              :1 ; /// PAD_SR_D[4]'s output enable(active low) in gpio mode
    u32 reg_sr_gpio5_drv1             :1 ; /// PAD_SR_D[4]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio5_pe               :1 ; /// PAD_SR_D[4]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sr_gpio5_ps               :1 ; /// PAD_SR_D[4]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sr_gpio5_drv              :1 ; /// PAD_SR_D[4]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio5_mode             :1 ; /// PAD_SR_D[4]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x2C]
    /* [0x2D] */
    u32 reg_sr_gpio6_in               :1 ; /// PAD_SR_D[5]'s input value in gpio mode
    u32 reg_sr_gpio6_out              :1 ; /// PAD_SR_D[5]'s output value in gpio mode
    u32 reg_sr_gpio6_oen              :1 ; /// PAD_SR_D[5]'s output enable(active low) in gpio mode
    u32 reg_sr_gpio6_drv1             :1 ; /// PAD_SR_D[5]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio6_pe               :1 ; /// PAD_SR_D[5]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sr_gpio6_ps               :1 ; /// PAD_SR_D[5]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sr_gpio6_drv              :1 ; /// PAD_SR_D[5]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio6_mode             :1 ; /// PAD_SR_D[5]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_sr_gpio7_in               :1 ; /// PAD_SR_D[6]'s input value in gpio mode
    u32 reg_sr_gpio7_out              :1 ; /// PAD_SR_D[6]'s output value in gpio mode
    u32 reg_sr_gpio7_oen              :1 ; /// PAD_SR_D[6]'s output enable(active low) in gpio mode
    u32 reg_sr_gpio7_drv1             :1 ; /// PAD_SR_D[6]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio7_pe               :1 ; /// PAD_SR_D[6]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sr_gpio7_ps               :1 ; /// PAD_SR_D[6]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sr_gpio7_drv              :1 ; /// PAD_SR_D[6]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio7_mode             :1 ; /// PAD_SR_D[6]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x2D]
    /* [0x2E] */
    u32 reg_sr_gpio8_in               :1 ; /// PAD_SR_D[7]'s input value in gpio mode
    u32 reg_sr_gpio8_out              :1 ; /// PAD_SR_D[7]'s output value in gpio mode
    u32 reg_sr_gpio8_oen              :1 ; /// PAD_SR_D[7]'s output enable(active low) in gpio mode
    u32 reg_sr_gpio8_drv1             :1 ; /// PAD_SR_D[7]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio8_pe               :1 ; /// PAD_SR_D[7]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sr_gpio8_ps               :1 ; /// PAD_SR_D[7]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sr_gpio8_drv              :1 ; /// PAD_SR_D[7]'s drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio8_mode             :1 ; /// PAD_SR_D[7]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_sr_gpio9_in               :1 ; /// PAD_SR_HSYNC's input value in gpio mode
    u32 reg_sr_gpio9_out              :1 ; /// PAD_SR_HSYNC's output value in gpio mode
    u32 reg_sr_gpio9_oen              :1 ; /// PAD_SR_HSYNC's output enable(active low) in gpio mode
    u32 reg_sr_gpio9_drv1             :1 ; /// PAD_SR_HSYNC's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio9_pe               :1 ; /// PAD_SR_HSYNC's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sr_gpio9_ps               :1 ; /// PAD_SR_HSYNC's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sr_gpio9_drv              :1 ; /// PAD_SR_HSYNC's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio9_mode             :1 ; /// PAD_SR_HSYNC's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x2E]
    /* [0x2F] */
    u32 reg_sr_gpio10_in              :1 ; /// PAD_SR_MCLK's input value in gpio mode
    u32 reg_sr_gpio10_out             :1 ; /// PAD_SR_MCLK's output value in gpio mode
    u32 reg_sr_gpio10_oen             :1 ; /// PAD_SR_MCLK's output enable(active low) in gpio mode
    u32 :1 ; /// [0x2F]
    u32 reg_sr_gpio10_pe              :1 ; /// PAD_SR_MCLK's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sr_gpio10_ps              :1 ; /// PAD_SR_MCLK's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sr_gpio10_drv             :1 ; /// PAD_SR_MCLK's drive strength.
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio10_mode            :1 ; /// PAD_SR_MCLK's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_sr_gpio11_in              :1 ; /// PAD_SR_VSYNC's input value in gpio mode
    u32 reg_sr_gpio11_out             :1 ; /// PAD_SR_VSYNC's output value in gpio mode
    u32 reg_sr_gpio11_oen             :1 ; /// PAD_SR_VSYNC's output enable(active low) in gpio mode
    u32 reg_sr_gpio11_drv1            :1 ; /// PAD_SR_VSYNC's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio11_pe              :1 ; /// PAD_SR_VSYNC's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sr_gpio11_ps              :1 ; /// PAD_SR_VSYNC's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sr_gpio11_drv             :1 ; /// PAD_SR_VSYNC's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio11_mode            :1 ; /// PAD_SR_VSYNC's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x2F]
    /* [0x30] */
    u32 reg_sr_gpio12_in              :1 ; /// PAD_SR_RST's input value in gpio mode
    u32 reg_sr_gpio12_out             :1 ; /// PAD_SR_RST's output value in gpio mode
    u32 reg_sr_gpio12_oen             :1 ; /// PAD_SR_RST's output enable(active low) in gpio mode
    u32 reg_sr_gpio12_drv1            :1 ; /// PAD_SR_RST's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio12_pe              :1 ; /// PAD_SR_RST's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sr_gpio12_ps              :1 ; /// PAD_SR_RST's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sr_gpio12_drv             :1 ; /// PAD_SR_RST's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio12_mode            :1 ; /// PAD_SR_RST's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_sr_gpio13_in              :1 ; /// PAD_SR_PWRDN's input value in gpio mode
    u32 reg_sr_gpio13_out             :1 ; /// PAD_SR_PWRDN's output value in gpio mode
    u32 reg_sr_gpio13_oen             :1 ; /// PAD_SR_PWRDN's output enable(active low) in gpio mode
    u32 reg_sr_gpio13_drv1            :1 ; /// PAD_SR_PWRDN's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio13_pe              :1 ; /// PAD_SR_PWRDN's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sr_gpio13_ps              :1 ; /// PAD_SR_PWRDN's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sr_gpio13_drv             :1 ; /// PAD_SR_PWRDN's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio13_mode            :1 ; /// PAD_SR_PWRDN's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x30]
    /* [0x31] */
    u32 reg_sr_gpio14_in              :1 ; /// PAD_SR_PCLK's input value in gpio mode
    u32 reg_sr_gpio14_out             :1 ; /// PAD_SR_PCLK's output value in gpio mode
    u32 reg_sr_gpio14_oen             :1 ; /// PAD_SR_PCLK's output enable(active low) in gpio mode
    u32 reg_sr_gpio14_drv1            :1 ; /// PAD_SR_PCLK's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio14_pe              :1 ; /// PAD_SR_PCLK's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0: disable
    u32 reg_sr_gpio14_ps              :1 ; /// PAD_SR_PCLK's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_sr_gpio14_drv             :1 ; /// PAD_SR_PCLK's drive strength. 
                                           /// 1: 8mA
                                           /// 0: 4mA
    u32 reg_sr_gpio14_mode            :1 ; /// PAD_SR_PCLK's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :24; /// [0x31]
    /* [0x32] */
    u32 reg_i2c_gpio0_in              :1 ; /// PAD_I2CCLK's input value in gpio mode
    u32 reg_i2c_gpio0_out             :1 ; /// PAD_I2CCLK's output value in gpio mode
    u32 reg_i2c_gpio0_oen             :1 ; /// PAD_I2CCLK's output enable(active low) in gpio mode
    u32 :4 ; /// [0x32]
    u32 reg_i2c_gpio0_mode            :1 ; /// PAD_I2CCLK's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_i2c_gpio1_in              :1 ; /// PAD_I2CDATA's input value in gpio mode
    u32 reg_i2c_gpio1_out             :1 ; /// PAD_I2CDATA's output value in gpio mode
    u32 reg_i2c_gpio1_oen             :1 ; /// PAD_I2CDATA's output enable(active low) in gpio mode
    u32 :4 ; /// [0x32]
    u32 reg_i2c_gpio1_mode            :1 ; /// PAD_I2CDATA's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x32]
    /* [0x33] */
    u32 reg_lcd_gpio0_in              :1 ; /// PAD_LCD_D[0]'s input value in gpio mode
    u32 reg_lcd_gpio0_out             :1 ; /// PAD_LCD_D[0]'s output value in gpio mode
    u32 reg_lcd_gpio0_oen             :1 ; /// PAD_LCD_D[0]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio0_drv1            :1 ; /// PAD_LCD_D[0]'s drive strength. 
    u32 reg_lcd_gpio0_pe              :1 ; /// PAD_LCD_D[0]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio0_ps              :1 ; /// PAD_LCD_D[0]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio0_drv0            :1 ; /// PAD_LCD_D[0]'s drive strength. 
    u32 reg_lcd_gpio0_mode            :1 ; /// PAD_LCD_D[0]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_lcd_gpio1_in              :1 ; /// PAD_LCD_D[1]'s input value in gpio mode
    u32 reg_lcd_gpio1_out             :1 ; /// PAD_LCD_D[1]'s output value in gpio mode
    u32 reg_lcd_gpio1_oen             :1 ; /// PAD_LCD_D[1]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio1_drv1            :1 ; /// PAD_LCD_D[1]'s drive strength. 
    u32 reg_lcd_gpio1_pe              :1 ; /// PAD_LCD_D[1]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio1_ps              :1 ; /// PAD_LCD_D[1]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio1_drv0            :1 ; /// PAD_LCD_D[1]'s drive strength. 
    u32 reg_lcd_gpio1_mode            :1 ; /// PAD_LCD_D[1]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x33]
    /* [0x34] */
    u32 reg_lcd_gpio2_in              :1 ; /// PAD_LCD_D[2]'s input value in gpio mode
    u32 reg_lcd_gpio2_out             :1 ; /// PAD_LCD_D[2]'s output value in gpio mode
    u32 reg_lcd_gpio2_oen             :1 ; /// PAD_LCD_D[2]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio2_drv1            :1 ; /// PAD_LCD_D[2]'s drive strength. 
    u32 reg_lcd_gpio2_pe              :1 ; /// PAD_LCD_D[2]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio2_ps              :1 ; /// PAD_LCD_D[2]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio2_drv0            :1 ; /// PAD_LCD_D[2]'s drive strength. 
    u32 reg_lcd_gpio2_mode            :1 ; /// PAD_LCD_D[2]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_lcd_gpio3_in              :1 ; /// PAD_LCD_D[3]'s input value in gpio mode
    u32 reg_lcd_gpio3_out             :1 ; /// PAD_LCD_D[3]'s output value in gpio mode
    u32 reg_lcd_gpio3_oen             :1 ; /// PAD_LCD_D[3]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio3_drv1            :1 ; /// PAD_LCD_D[3]'s drive strength. 
    u32 reg_lcd_gpio3_pe              :1 ; /// PAD_LCD_D[3]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio3_ps              :1 ; /// PAD_LCD_D[3]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio3_drv0            :1 ; /// PAD_LCD_D[3]'s drive strength. 
    u32 reg_lcd_gpio3_mode            :1 ; /// PAD_LCD_D[3]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x34]
    /* [0x35] */
    u32 reg_lcd_gpio4_in              :1 ; /// PAD_LCD_D[4]'s input value in gpio mode
    u32 reg_lcd_gpio4_out             :1 ; /// PAD_LCD_D[4]'s output value in gpio mode
    u32 reg_lcd_gpio4_oen             :1 ; /// PAD_LCD_D[4]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio4_drv1            :1 ; /// PAD_LCD_D[4]'s drive strength. 
    u32 reg_lcd_gpio4_pe              :1 ; /// PAD_LCD_D[4]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio4_ps              :1 ; /// PAD_LCD_D[4]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio4_drv0            :1 ; /// PAD_LCD_D[4]'s drive strength. 
    u32 reg_lcd_gpio4_mode            :1 ; /// PAD_LCD_D[4]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_lcd_gpio5_in              :1 ; /// PAD_LCD_D[5]'s input value in gpio mode
    u32 reg_lcd_gpio5_out             :1 ; /// PAD_LCD_D[5]'s output value in gpio mode
    u32 reg_lcd_gpio5_oen             :1 ; /// PAD_LCD_D[5]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio5_drv1            :1 ; /// PAD_LCD_D[5]'s drive strength. 
    u32 reg_lcd_gpio5_pe              :1 ; /// PAD_LCD_D[5]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio5_ps              :1 ; /// PAD_LCD_D[5]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio5_drv0            :1 ; /// PAD_LCD_D[5]'s drive strength. 
    u32 reg_lcd_gpio5_mode            :1 ; /// PAD_LCD_D[5]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x35]
    /* [0x36] */
    u32 reg_lcd_gpio6_in              :1 ; /// PAD_LCD_D[6]'s input value in gpio mode
    u32 reg_lcd_gpio6_out             :1 ; /// PAD_LCD_D[6]'s output value in gpio mode
    u32 reg_lcd_gpio6_oen             :1 ; /// PAD_LCD_D[6]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio6_drv1            :1 ; /// PAD_LCD_D[6]'s drive strength. 
    u32 reg_lcd_gpio6_pe              :1 ; /// PAD_LCD_D[6]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio6_ps              :1 ; /// PAD_LCD_D[6]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio6_drv0            :1 ; /// PAD_LCD_D[6]'s drive strength. 
    u32 reg_lcd_gpio6_mode            :1 ; /// PAD_LCD_D[6]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_lcd_gpio7_in              :1 ; /// PAD_LCD_D[7]'s input value in gpio mode
    u32 reg_lcd_gpio7_out             :1 ; /// PAD_LCD_D[7]'s output value in gpio mode
    u32 reg_lcd_gpio7_oen             :1 ; /// PAD_LCD_D[7]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio7_drv1            :1 ; /// PAD_LCD_D[7]'s drive strength. 
    u32 reg_lcd_gpio7_pe              :1 ; /// PAD_LCD_D[7]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio7_ps              :1 ; /// PAD_LCD_D[7]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio7_drv0            :1 ; /// PAD_LCD_D[7]'s drive strength. 
    u32 reg_lcd_gpio7_mode            :1 ; /// PAD_LCD_D[7]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x36]
    /* [0x37] */
    u32 reg_lcd_gpio8_in              :1 ; /// PAD_LCD_D[8]'s input value in gpio mode
    u32 reg_lcd_gpio8_out             :1 ; /// PAD_LCD_D[8]'s output value in gpio mode
    u32 reg_lcd_gpio8_oen             :1 ; /// PAD_LCD_D[8]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio8_drv1            :1 ; /// PAD_LCD_D[8]'s drive strength. 
    u32 reg_lcd_gpio8_pe              :1 ; /// PAD_LCD_D[8]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio8_ps              :1 ; /// PAD_LCD_D[8]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio8_drv0            :1 ; /// PAD_LCD_D[8]'s drive strength. 
    u32 reg_lcd_gpio8_mode            :1 ; /// PAD_LCD_D[8]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_lcd_gpio9_in              :1 ; /// PAD_LCD_D[9]'s input value in gpio mode
    u32 reg_lcd_gpio9_out             :1 ; /// PAD_LCD_D[9]'s output value in gpio mode
    u32 reg_lcd_gpio9_oen             :1 ; /// PAD_LCD_D[9]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio9_drv1            :1 ; /// PAD_LCD_D[9]'s drive strength. 
    u32 reg_lcd_gpio9_pe              :1 ; /// PAD_LCD_D[9]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio9_ps              :1 ; /// PAD_LCD_D[9]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio9_drv0            :1 ; /// PAD_LCD_D[9]'s drive strength. 
    u32 reg_lcd_gpio9_mode            :1 ; /// PAD_LCD_D[9]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x37]
    /* [0x38] */
    u32 reg_lcd_gpio10_in             :1 ; /// PAD_LCD_D[10]'s input value in gpio mode
    u32 reg_lcd_gpio10_out            :1 ; /// PAD_LCD_D[10]'s output value in gpio mode
    u32 reg_lcd_gpio10_oen            :1 ; /// PAD_LCD_D[10]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio10_drv1           :1 ; /// PAD_LCD_D[10]'s drive strength. 
    u32 reg_lcd_gpio10_pe             :1 ; /// PAD_LCD_D[10]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio10_ps             :1 ; /// PAD_LCD_D[10]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio10_drv0           :1 ; /// PAD_LCD_D[10]'s drive strength. 
    u32 reg_lcd_gpio10_mode           :1 ; /// PAD_LCD_D[10]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_lcd_gpio11_in             :1 ; /// PAD_LCD_D[11]'s input value in gpio mode
    u32 reg_lcd_gpio11_out            :1 ; /// PAD_LCD_D[11]'s output value in gpio mode
    u32 reg_lcd_gpio11_oen            :1 ; /// PAD_LCD_D[11]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio11_drv1           :1 ; /// PAD_LCD_D[11]'s drive strength. 
    u32 reg_lcd_gpio11_pe             :1 ; /// PAD_LCD_D[11]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio11_ps             :1 ; /// PAD_LCD_D[11]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio11_drv0           :1 ; /// PAD_LCD_D[11]'s drive strength. 
    u32 reg_lcd_gpio11_mode           :1 ; /// PAD_LCD_D[11]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x38]
    /* [0x39] */
    u32 reg_lcd_gpio12_in             :1 ; /// PAD_LCD_D[12]'s input value in gpio mode
    u32 reg_lcd_gpio12_out            :1 ; /// PAD_LCD_D[12]'s output value in gpio mode
    u32 reg_lcd_gpio12_oen            :1 ; /// PAD_LCD_D[12]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio12_drv1           :1 ; /// PAD_LCD_D[12]'s drive strength. 
    u32 reg_lcd_gpio12_pe             :1 ; /// PAD_LCD_D[12]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio12_ps             :1 ; /// PAD_LCD_D[12]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio12_drv0           :1 ; /// PAD_LCD_D[12]'s drive strength. 
    u32 reg_lcd_gpio12_mode           :1 ; /// PAD_LCD_D[12]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_lcd_gpio13_in             :1 ; /// PAD_LCD_D[13]'s input value in gpio mode
    u32 reg_lcd_gpio13_out            :1 ; /// PAD_LCD_D[13]'s output value in gpio mode
    u32 reg_lcd_gpio13_oen            :1 ; /// PAD_LCD_D[13]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio13_drv1           :1 ; /// PAD_LCD_D[13]'s drive strength. 
    u32 reg_lcd_gpio13_pe             :1 ; /// PAD_LCD_D[13]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio13_ps             :1 ; /// PAD_LCD_D[13]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio13_drv0           :1 ; /// PAD_LCD_D[13]'s drive strength. 
    u32 reg_lcd_gpio13_mode           :1 ; /// PAD_LCD_D[13]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x39]
    /* [0x3A] */
    u32 reg_lcd_gpio14_in             :1 ; /// PAD_LCD_D[14]'s input value in gpio mode
    u32 reg_lcd_gpio14_out            :1 ; /// PAD_LCD_D[14]'s output value in gpio mode
    u32 reg_lcd_gpio14_oen            :1 ; /// PAD_LCD_D[14]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio14_drv1           :1 ; /// PAD_LCD_D[14]'s drive strength. 
    u32 reg_lcd_gpio14_pe             :1 ; /// PAD_LCD_D[14]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio14_ps             :1 ; /// PAD_LCD_D[14]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio14_drv0           :1 ; /// PAD_LCD_D[14]'s drive strength. 
    u32 reg_lcd_gpio14_mode           :1 ; /// PAD_LCD_D[14]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_lcd_gpio15_in             :1 ; /// PAD_LCD_D[15]'s input value in gpio mode
    u32 reg_lcd_gpio15_out            :1 ; /// PAD_LCD_D[15]'s output value in gpio mode
    u32 reg_lcd_gpio15_oen            :1 ; /// PAD_LCD_D[15]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio15_drv1           :1 ; /// PAD_LCD_D[15]'s drive strength. 
    u32 reg_lcd_gpio15_pe             :1 ; /// PAD_LCD_D[15]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio15_ps             :1 ; /// PAD_LCD_D[15]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio15_drv0           :1 ; /// PAD_LCD_D[15]'s drive strength. 
    u32 reg_lcd_gpio15_mode           :1 ; /// PAD_LCD_D[15]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x3A]
    /* [0x3B] */
    u32 reg_lcd_gpio16_in             :1 ; /// PAD_LCD_D[16]'s input value in gpio mode
    u32 reg_lcd_gpio16_out            :1 ; /// PAD_LCD_D[16]'s output value in gpio mode
    u32 reg_lcd_gpio16_oen            :1 ; /// PAD_LCD_D[16]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio16_drv1           :1 ; /// PAD_LCD_D[16]'s drive strength. 
    u32 reg_lcd_gpio16_pe             :1 ; /// PAD_LCD_D[16]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio16_ps             :1 ; /// PAD_LCD_D[16]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio16_drv0           :1 ; /// PAD_LCD_D[16]'s drive strength. 
    u32 reg_lcd_gpio16_mode           :1 ; /// PAD_LCD_D[16]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_lcd_gpio17_in             :1 ; /// PAD_LCD_D[17]'s input value in gpio mode
    u32 reg_lcd_gpio17_out            :1 ; /// PAD_LCD_D[17]'s output value in gpio mode
    u32 reg_lcd_gpio17_oen            :1 ; /// PAD_LCD_D[17]'s output enable(active low) in gpio mode
    u32 reg_lcd_gpio17_drv1           :1 ; /// PAD_LCD_D[17]'s drive strength. 
    u32 reg_lcd_gpio17_pe             :1 ; /// PAD_LCD_D[17]'s pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio17_ps             :1 ; /// PAD_LCD_D[17]'s pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio17_drv0           :1 ; /// PAD_LCD_D[17]'s drive strength. 
    u32 reg_lcd_gpio17_mode           :1 ; /// PAD_LCD_D[17]'s GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x3B]
    /* [0x3C] */
    u32 reg_lcd_gpio18_in             :1 ; /// PAD_LCD_CS0_N's input value in gpio mode
    u32 reg_lcd_gpio18_out            :1 ; /// PAD_LCD_CS0_N's output value in gpio mode
    u32 reg_lcd_gpio18_oen            :1 ; /// PAD_LCD_CS0_N's output enable(active low) in gpio mode
    u32 reg_lcd_gpio18_drv1           :1 ; /// PAD_LCD_CS0_N's drive strength. 
    u32 reg_lcd_gpio18_pe             :1 ; /// PAD_LCD_CS0_N's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio18_ps             :1 ; /// PAD_LCD_CS0_N's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio18_drv0           :1 ; /// PAD_LCD_CS0_N's drive strength. 
    u32 reg_lcd_gpio18_mode           :1 ; /// PAD_LCD_CS0_N's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_lcd_gpio19_in             :1 ; /// PAD_LCD_RSTZ's input value in gpio mode
    u32 reg_lcd_gpio19_out            :1 ; /// PAD_LCD_RSTZ's output value in gpio mode
    u32 reg_lcd_gpio19_oen            :1 ; /// PAD_LCD_RSTZ's output enable(active low) in gpio mode
    u32 reg_lcd_gpio19_drv1           :1 ; /// No Use
    u32 reg_lcd_gpio19_pe             :1 ; /// PAD_LCD_RSTZ's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio19_ps             :1 ; /// PAD_LCD_RSTZ's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio19_drv0           :1 ; /// PAD_LCD_RSTZ's drive strength. 
                                           /// 1: 16mA
                                           /// 0: 8mA
    u32 reg_lcd_gpio19_mode           :1 ; /// PAD_LCD_RSTZ's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x3C]
    /* [0x3D] */
    u32 reg_lcd_gpio20_in             :1 ; /// PAD_LCD_RD's input value in gpio mode
    u32 reg_lcd_gpio20_out            :1 ; /// PAD_LCD_RD's output value in gpio mode
    u32 reg_lcd_gpio20_oen            :1 ; /// PAD_LCD_RD's output enable(active low) in gpio mode
    u32 reg_lcd_gpio20_drv1           :1 ; /// PAD_LCD_RD's drive strength. 
    u32 reg_lcd_gpio20_pe             :1 ; /// PAD_LCD_RD's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio20_ps             :1 ; /// PAD_LCD_RD's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio20_drv0           :1 ; /// PAD_LCD_RD's drive strength. 
    u32 reg_lcd_gpio20_mode           :1 ; /// PAD_LCD_RD's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 reg_lcd_gpio21_in             :1 ; /// PAD_LCD_CMD's input value in gpio mode
    u32 reg_lcd_gpio21_out            :1 ; /// PAD_LCD_CMD's output value in gpio mode
    u32 reg_lcd_gpio21_oen            :1 ; /// PAD_LCD_CMD's output enable(active low) in gpio mode
    u32 reg_lcd_gpio21_drv1           :1 ; /// PAD_LCD_CMD's drive strength. 
    u32 reg_lcd_gpio21_pe             :1 ; /// PAD_LCD_CMD's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio21_ps             :1 ; /// PAD_LCD_CMD's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio21_drv0           :1 ; /// PAD_LCD_CMD's drive strength. 
    u32 reg_lcd_gpio21_mode           :1 ; /// PAD_LCD_CMD's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :16; /// [0x3D]
    /* [0x3E] */
    u32 reg_lcd_gpio22_in             :1 ; /// PAD_LCD_WR's input value in gpio mode
    u32 reg_lcd_gpio22_out            :1 ; /// PAD_LCD_WR's output value in gpio mode
    u32 reg_lcd_gpio22_oen            :1 ; /// PAD_LCD_WR's output enable(active low) in gpio mode
    u32 reg_lcd_gpio22_drv1           :1 ; /// PAD_LCD_WR's drive strength. 
    u32 reg_lcd_gpio22_pe             :1 ; /// PAD_LCD_WR's pull enable; only valid when this PAD is set input mode
                                           /// 1: enable 
                                           /// 0:disable
    u32 reg_lcd_gpio22_ps             :1 ; /// PAD_LCD_WR's pull up/down; only valid when this PAD's pe=1
                                           /// 1:pull-up
                                           /// 0:pull-down
    u32 reg_lcd_gpio22_drv0           :1 ; /// PAD_LCD_WR's drive strength. 
    u32 reg_lcd_gpio22_mode           :1 ; /// PAD_LCD_WR's GPIO mode ( priority > other function but < test mode)
                                           /// 1: this PAD is set GPIO mode
                                           /// 0: this PAD is not in GPIO mode
    u32 :24; /// [0x3E]
    /* [0x3F] */
    u32 reg_boot_spi_cs_passwd        :8 ; /// Password of CS control mode for boot_spi
    u32 reg_boot_spi_cs_out           :1 ; /// CS control out for boot_spi
    u32 :23; /// [0x3F]
    u32 :32; /// [0x40]
    u32 :32; /// [0x41]
    u32 :32; /// [0x42]
    u32 :32; /// [0x43]
    u32 :32; /// [0x44]
    u32 :32; /// [0x45]
    u32 :32; /// [0x46]
    u32 :32; /// [0x47]
    u32 :32; /// [0x48]
    u32 :32; /// [0x49]
    u32 :32; /// [0x4A]
    u32 :32; /// [0x4B]
    u32 :32; /// [0x4C]
    u32 :32; /// [0x4D]
    u32 :32; /// [0x4E]
    u32 :32; /// [0x4F]
    u32 :32; /// [0x50]
    u32 :32; /// [0x51]
    u32 :32; /// [0x52]
    u32 :32; /// [0x53]
    u32 :32; /// [0x54]
    u32 :32; /// [0x55]
    u32 :32; /// [0x56]
    u32 :32; /// [0x57]
    u32 :32; /// [0x58]
    u32 :32; /// [0x59]
    u32 :32; /// [0x5A]
    u32 :32; /// [0x5B]
    u32 :32; /// [0x5C]
    u32 :32; /// [0x5D]
    u32 :32; /// [0x5E]
    u32 :32; /// [0x5F]
    u32 :32; /// [0x60]
    u32 :32; /// [0x61]
    u32 :32; /// [0x62]
    u32 :32; /// [0x63]
    u32 :32; /// [0x64]
    u32 :32; /// [0x65]
    u32 :32; /// [0x66]
    u32 :32; /// [0x67]
    u32 :32; /// [0x68]
    u32 :32; /// [0x69]
    u32 :32; /// [0x6A]
    u32 :32; /// [0x6B]
    u32 :32; /// [0x6C]
    u32 :32; /// [0x6D]
    u32 :32; /// [0x6E]
    u32 :32; /// [0x6F]
    u32 :32; /// [0x70]
    u32 :32; /// [0x71]
    u32 :32; /// [0x72]
    u32 :32; /// [0x73]
    u32 :32; /// [0x74]
    u32 :32; /// [0x75]
    u32 :32; /// [0x76]
    u32 :32; /// [0x77]
    u32 :32; /// [0x78]
    u32 :32; /// [0x79]
    u32 :32; /// [0x7A]
    u32 :32; /// [0x7B]
    /* [0x7C] */
    u32 reg_gpio_ctrl_reserved0       :16; /// gpio ctrl reserved0 registers
    u32 :16; /// [0x7C]
    /* [0x7D] */
    u32 reg_gpio_ctrl_reserved1       :16; /// gpio ctrl reserved1 registers
    u32 :16; /// [0x7D]
    /* [0x7E] */
    u32 reg_gpio_ctrl_reserved2       :16; /// gpio ctrl reserved2 registers
    u32 :16; /// [0x7E]
    /* [0x7F] */
    u32 reg_gpio_ctrl_reserved3       :16; /// gpio ctrl reserved3 registers
} KeGpioCtrl0_t;

extern volatile KeGpioCtrl0_t* const g_ptKeGpioCtrl0;
extern volatile KeGpioCtrl1_t* const g_ptKeGpioCtrl1;
extern volatile KeGpioCtrl2_t* const g_ptKeGpioCtrl2;

#define PAD_U0TXD_DWL_MODE      0x0
#define PAD_U0TXD_NORM_MODE     0x1

#endif //__KERNEL_GPIO_H__
