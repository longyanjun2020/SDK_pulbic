/******************************************************************************/
/*  File    :   kernel_padctrl.h                                              */
/*----------------------------------------------------------------------------*/
/*  Scope   :   System pad control related definitions                        */
/*                                                                            */
/******************************************************************************/

#ifndef __KERNEL_PADCTRL_H__
#define __KERNEL_PADCTRL_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "stdcomp.h"
#include "riubridge.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#define PAD_NCSYSTEM4_MSK       0x01
#define DBBSPI_MODE(_value_)    (_value_)   /* mode0 to mode4 */
#define UART1_PADS_USE_MPIF     0x01
#define UART1_PADS_USE_BTIF     0x02
#define UART1_PADS_TURN_OFF     0x00


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
/**********************************************/
/* Pad Ctrl Register Bank                     */
/**********************************************/
typedef struct KePadCtrl_s
{
    /* [0x00] */
    u32 reg_test_in_1st_mode          :3 ; /// test in mode
                                           ///
    u32 :1 ; /// [0x00]
    u32 reg_test_in_2nd_mode          :3 ; /// test in mode
                                           ///
    u32 :1 ; /// [0x00]
    u32 reg_test_out_mode             :3 ; /// test out mode
                                           ///
    u32 :1 ; /// [0x00]
    u32 reg_etm_trace_mode            :2 ; /// test in mode
                                           ///
    u32 reg_dig_rf_test_en            :1 ; /// test in mode
                                           ///
    u32 reg_spi_rf_test_in_en         :1 ; /// test in mode
                                           ///
    u32 :16; /// [0x00]
    /* [0x01] */
    u32 reg_btif_mode                 :2 ; /// None
    u32 reg_mpif_mode                 :2 ; /// None
    u32 reg_sdio_mode                 :2 ; /// None
    u32 reg_sim1_en                   :1 ; /// None
    u32 reg_sim2_en                   :1 ; /// None
    u32 reg_col7_mode                 :3 ; /// None
    u32 :1 ; /// [0x01]
    u32 reg_row6_mode                 :2 ; /// None
    u32 :18; /// [0x01]
    /* [0x02] */
    u32 reg_row7_mode                 :3 ; /// None
    u32 :1 ; /// [0x02]
    u32 reg_key7x6_en                 :1 ; /// None
    u32 reg_sd_mode                   :1 ; /// None
    u32 :2 ; /// [0x02]
    u32 reg_pwm0_mode                 :3 ; /// None
    u32 :1 ; /// [0x02]
    u32 reg_pwm1_mode                 :3 ; /// None
    u32 :17; /// [0x02]
    /* [0x03] */
    u32 reg_pwm2_mode                 :3 ; /// None
    u32 :1 ; /// [0x03]
    u32 reg_pwm3_mode                 :3 ; /// None
    u32 :1 ; /// [0x03]
    u32 reg_ext_codec_i2s_mode        :2 ; /// None
    u32 reg_bt_pcm_mode               :2 ; /// None
    u32 :2 ; /// [0x03]
    u32 reg_dbg_uart_rts_mode         :2 ; /// None
    u32 :16; /// [0x03]
    /* [0x04] */
    u32 reg_fuart_mode                :2 ; /// None
    u32 reg_rx_i2s_mode               :1 ; /// None
    u32 reg_tbuo_en                   :1 ; /// None
    u32 reg_spi_rf_en                 :1 ; /// None
    u32 reg_sr_en                     :1 ; /// None
    u32 reg_i2c_en                    :2 ; /// None
    u32 reg_lcd_fmark_mode            :4 ; /// None
    u32 reg_lcd_vs_mode               :4 ; /// None
    u32 :16; /// [0x04]
    /* [0x05] */
    u32 reg_lcd_clk_mode              :4 ; /// None
    u32 reg_ebi2lcd_en                :2 ; /// None
    u32 reg_lcd_mode                  :2 ; /// None
    u32 reg_dbb_spi_mode              :2 ; /// None
    u32 :3 ; /// [0x05]
    u32 reg_seth                      :1 ; /// None
    u32 reg_setl                      :1 ; /// None
    u32 reg_allpad_in                 :1 ; /// None
    u32 :16; /// [0x05]
    /* [0x06] */
    u32 reg_gps_clk_out_mode          :3 ; /// None
    u32 :1 ; /// [0x06]
    u32 reg_gps_clk_out2_mode         :3 ; /// None
    u32 :1 ; /// [0x06]
    u32 reg_lcd_cs1_mode              :4 ; /// None
    u32 reg_ebi2lcd_cs1_mode          :4 ; /// None
    u32 :16; /// [0x06]
    /* [0x07] */
    u32 reg_jtag_rtck_mode            :4 ; /// None
    u32 reg_tbuo_ncvio1_2_en          :1 ; /// None
    u32 :27; /// [0x07]
    /* [0x08] */
    u32 reg_arm_bist_en               :1 ; /// arm bist mode
                                           ///
    u32 reg_arm_bist_rst              :1 ; /// arm bist mode
                                           ///
    u32 reg_arm_bist_fail             :1 ; /// arm bist mode
                                           ///
    u32 reg_arm_bist_done             :1 ; /// arm bist mode
                                           ///
    u32 reg_arm_bist_sel              :1 ; /// arm bist mode
                                           ///
    u32 :27; /// [0x08]
    /* [0x09] */
    u32 reg_qbsave_mode               :4 ; /// None
    u32 reg_pm_use_boot_spi           :1 ; /// None
    u32 :3 ; /// [0x09]
    u32 reg_nand_8bit_mode            :1 ; /// None
    u32 :3 ; /// [0x09]
    u32 reg_26mhz_out_mode            :4 ; /// None
    u32 :16; /// [0x09]
    /* [0x0A] */
    u32 reg_ext_int0_sel              :8 ; /// None
    u32 reg_ext_int1_sel              :8 ; /// None
    u32 :16; /// [0x0A]
    /* [0x0B] */
    u32 reg_ext_int2_sel              :8 ; /// None
    u32 reg_ext_int3_sel              :8 ; /// None
    u32 :16; /// [0x0B]
    /* [0x0C] */
    u32 reg_ext_int4_sel              :8 ; /// None
    u32 reg_ext_int5_sel              :8 ; /// None
    u32 :16; /// [0x0C]
    /* [0x0D] */
    u32 reg_ext_int6_sel              :8 ; /// None
    u32 reg_ext_int7_sel              :8 ; /// None
    u32 :16; /// [0x0D]
    /* [0x0E] */
    u32 reg_ext_int8_sel              :8 ; /// None
    u32 reg_ext_int9_sel              :8 ; /// None
    u32 :16; /// [0x0E]
    /* [0x0F] */
    u32 reg_ext_int10_sel             :8 ; /// None
    u32 reg_ext_int11_sel             :8 ; /// None
    u32 :16; /// [0x0F]
    /* [0x10] */
    u32 reg_ext_int12_sel             :8 ; /// None
    u32 reg_ext_int13_sel             :8 ; /// None
    u32 :16; /// [0x10]
    /* [0x11] */
    u32 reg_ext_int14_sel             :8 ; /// None
    u32 reg_ext_int15_sel             :8 ; /// None
    u32 :16; /// [0x11]
    /* [0x12] */
    u32 reg_ext_int_en                :1 ; /// None
    u32 :31; /// [0x12]
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
    /* [0x1F] */
    u32 reg_pm_13mhz_en               :1 ; /// None
    u32 :31; /// [0x1F]
    /* [0x20] */
    u32 reg_bonding_option_pad_in     :5 ; /// bond to gnd or pull-up by default
                                           /// [0]:PAD_NCSYSTEM4
                                           /// [1]:PAD_NCTOP0
                                           /// [2]: PAD_NCTOP1
                                           /// [3]: PAD_NCTOP2
                                           /// [4]:PAD_NCTOP3
                                           ///
                                           ///
                                           ///
    u32 :27; /// [0x20]
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
    /* [0x3A] */
    u32 reg_clk_out_sel               :3 ; /// dbg_ctrl
    u32 :1 ; /// [0x3A]
    u32 reg_single_clk_out_sel        :3 ; /// dbg_ctrl
    u32 :1 ; /// [0x3A]
    u32 reg_test_rg                   :1 ; /// dbg_ctrl
    u32 reg_test_gb                   :1 ; /// dbg_ctrl
    u32 reg_test_rb                   :1 ; /// dbg_ctrl
    u32 reg_testclk_mode              :1 ; /// dbg_ctrl
    u32 reg_rosc_in_sel               :1 ; /// dbg_ctrl
    u32 reg_swaptest12bit             :1 ; /// dbg_ctrl
    u32 reg_rosc_out_sel              :2 ; /// dbg_ctrl
    u32 :16; /// [0x3A]
    /* [0x3B] */
    u32 reg_test_bus24b_sel           :6 ; /// dbg_ctrl
    u32 :2 ; /// [0x3B]
    u32 reg_testbus_en                :1 ; /// dbg_ctrl
    u32 :3 ; /// [0x3B]
    u32 reg_clk_calc_en               :1 ; /// dbg_ctrl
    u32 :19; /// [0x3B]
    /* [0x3C] */
    u32 reg_calc_cnt_report           :16; /// None
    u32 :16; /// [0x3C]
    /* [0x3D] */
    u32 reg_mcp_test_mode             :2 ; /// None
    u32 :30; /// [0x3D]
    /* [0x3E] */
    u32 reg_24bit_test_out_0          :16; /// None
    u32 :16; /// [0x3E]
    u32 reg_24bit_test_out_1          :8 ; /// @see reg_24bit_test_out_0
} KePadCtrl_t;

#endif /*__KERNEL_PADCTRL_H__*/
