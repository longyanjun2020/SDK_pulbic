/******************************************************************************/
/*  File    :   kernel_pll.h                                                  */
/*----------------------------------------------------------------------------*/
/*  Scope   :   System PLL related definitions                                */
/*                                                                            */
/******************************************************************************/

#ifndef __KERNEL_PLL_H__
#define __KERNEL_PLL_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "stdcomp.h"
#include "riubridge.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#define PLL21_DIVFB_DEFAULT     0x18
#define PLL22_DIVFB_DEFAULT     0x30


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
/************************************************/
/* RIU PLL Bank                                 */
/************************************************/
typedef struct KePll_s {
    /* [0x00] */
    u32 reg_pll21_enable              :1 ; /// enable PLL21, high active
    u32 reg_pll21_enable_ovrw         :1 ; /// enable PLL21 overwrite
    u32 reg_pll21_reset_sw_en         :1 ; /// PLL21 software reset enable, high active
    u32 reg_pll21_sw_rst              :1 ; /// PLL21 software reset, high active
    u32 :28; /// [0x00]
    /* [0x01] */
    u32 reg_pll21_divfb               :6 ; /// PLL21 feedback divider, fout=fin*(N+1), fin=13MHz
    u32 :26; /// [0x01]
    /* [0x02] */
    u32 reg_pll21_test                :8 ; /// PLL21 test bits
    u32 :24; /// [0x02]
    /* [0x03] */
    u32 reg_pll22_enable              :1 ; /// enable PLL22, high active
    u32 reg_pll22_enable_ovrw         :1 ; /// enable PLL22 overwrite
    u32 reg_pll22_reset_sw_en         :1 ; /// PLL22 software reset enable, high active
    u32 reg_pll22_sw_rst              :1 ; /// PLL22 software reset, high active
    u32 :28; /// [0x03]
    /* [0x04] */
    u32 reg_pll22_divfb               :6 ; /// PLL22 feedback divider, fout=fin*(N), fin=13MHz
    u32 :26; /// [0x04]
    /* [0x05] */
    u32 reg_pll22_test                :8 ; /// PLL22 test bits
    u32 :24; /// [0x05]
    /* [0x06] */
    u32 reg_mpll_bypass               :1 ; /// bypass clock squarer, high active
    u32 reg_en_pll_reg                :1 ; /// enable pll internal 1.2V regulator , high active
    u32 :30; /// [0x06]
    /* [0x07] */
    u32 reg_pll_in_sel                :1 ; /// select MCLK frequency, 1'b0: 13MHz; 1'b1: 26MHz
    u32 reg_pll_in_sel_ovrw           :1 ; /// PLL_IN_SEL overwrite
    u32 reg_en_sqr                    :1 ; /// enable clock squarer, high active
    u32 reg_en_sqr_ovrw               :1 ; /// enable clock squarer overwrite
    u32 reg_clk_sqr_outen             :1 ; /// enable clock squarer output, high active
    u32 reg_clk_sqr_outen_ovrw        :1 ; /// enable clock squarer output overwrite
    u32 :26; /// [0x07]
    /* [0x08] */
    u32 reg_pll_test_0                :16; /// pll_top test bits
    u32 :16; /// [0x08]
    u32 reg_pll_test_1                :12; /// @see reg_pll_test_0
    u32 :20; /// [0x09]
    u32 :32; /// [0x0A]
    u32 :32; /// [0x0B]
    u32 :32; /// [0x0C]
    u32 :32; /// [0x0D]
    u32 :32; /// [0x0E]
    u32 :32; /// [0x0F]
    /* [0x10] */
    u32 reg_en_pll22_div2_dbb         :1 ; /// CLK_DBB_DIV2
    u32 reg_en_pll22_div3_dbb         :1 ; /// CLK_DBB_DIV3
    u32 reg_en_pll22_div5_dbb         :1 ; /// CLK_DBB_DIV5
    u32 reg_en_pll22_div6_dbb         :1 ; /// CLK_DBB_DIV6
    u32 reg_en_pll21_dbb              :1 ; /// CLK_PLL22_DBB
    u32 :27; /// [0x10]
    u32 :32; /// [0x11]
    u32 :32; /// [0x12]
    /* [0x13] */
    u32 reg_en_mmp_312m               :1 ; /// enable CLK_MMP_312M, high active
    u32 reg_en_mmp_156m               :1 ; /// enable CLK_MMP_156M, high active
    u32 reg_en_mmp_104m               :1 ; /// enable CLK_MMP_104M, high active
    u32 reg_en_mmp_62p4m              :1 ; /// enable CLK_MMP_62P4M, high active
    u32 reg_en_mmp_60m12m             :1 ; /// enable CLK_MMP_60M and CLK_MMP_12M, high active
    u32 reg_en_mmp_mclk               :1 ; /// enable CLK_MMP_MCLK, high active
    u32 :26; /// [0x13]
    /* [0x14] */
    u32 reg_en_rf_ana_26m             :1 ; /// CLK_RF_ANA_26M
    u32 :1 ; /// [0x14]
    u32 reg_en_rf_dig_26m             :1 ; /// CLK_RF_DIG_26M
    u32 reg_en_sar_2m                 :1 ; /// CLK_SAR_2M
    u32 :1 ; /// [0x14]
    u32 reg_en_usb_24m                :1 ; /// CLK_USB_24M
    u32 reg_en_ddr48m                 :1 ; /// CLK_DDR48M
    u32 reg_en_fm_26m                 :1 ; /// CLK_FM_26M
    u32 reg_en_audio_48m              :1 ; /// CLK_AUDIO_48M_3V
    u32 reg_mux_ddr48m                :1 ; /// CLK_DDR48M
    u32 :22; /// [0x14]
    /* [0x15] */
    u32 reg_en_emi_624md3             :1 ; /// EN_EMI_624MD3
    u32 reg_en_emi_624md5             :1 ; /// EN_EMI_624MD5
    u32 reg_en_emi_624md7             :1 ; /// EN_EMI_624MD7
    u32 reg_en_emi_624md9             :1 ; /// EN_EMI_624MD9
    u32 reg_en_emi_624md11            :1 ; /// EN_EMI_624MD11
    u32 reg_en_emi_624md13            :1 ; /// EN_EMI_624MD13
    u32 :26; /// [0x15]
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
    u32 reg_pll21_lock                :1 ; /// PLL21 lock status
    u32 reg_pll22_lock                :1 ; /// PLL22 lock status
    u32 :30; /// [0x20]
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
    /* [0x30] */
    u32 reg_debug_out_0               :16; /// debug output
    u32 :16; /// [0x30]
    u32 reg_debug_out_1               :8 ; /// @see reg_debug_out_0
    u32 :24; /// [0x31]
    /* [0x32] */
    u32 reg_debug_sel                 :4 ; /// debug selection
    u32 :28; /// [0x32]
    /* [0x33] */
    u32 reg_pll_dummy0                :16; /// PLL dummy register 0
    u32 :16; /// [0x33]
    /* [0x34] */
    u32 reg_pll_dummy1                :16; /// PLL dummy register 1
    u32 :16; /// [0x34]
    /* [0x35] */
    u32 reg_pll_dummy_r               :16; /// PLL dummy read register
} KePll_t;

extern volatile KePll_t * const g_ptKePll;


#endif /*__KERNEL_PLL_H__*/
