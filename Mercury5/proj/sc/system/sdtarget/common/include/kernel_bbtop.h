/******************************************************************************/
/*  File    :   kernel_bbtop.h                                                */
/*----------------------------------------------------------------------------*/
/*  Scope   :   System pad control related definitions                        */
/*                                                                            */
/******************************************************************************/
#ifndef __KERNEL_BBTOP_H__
#define __KERNEL_BBTOP_H__

//------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------
#include "stdcomp.h"
#include "riubridge.h"


//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
/* TOP_READ */
#define TOP_READ_JTCK_STRAP_OFF     5
#define TOP_READ_JTCK_STRAP_MSK     (0x01 << TOP_READ_JTCK_STRAP_OFF)
#define STRAP_VDDIO_BY_VIO1         (0x00 << TOP_READ_JTCK_STRAP_OFF)
#define STRAP_VDDIO_BY_VIO2         (0x01 << TOP_READ_JTCK_STRAP_OFF)

/* CRU */
#define BBTOP_CRU_IP_RESET          (1 << 0)
#define BBTOP_CRU_CLOCK_GATING      (1 << 1)
#define BBTOP_CRU_CLOCK_INVERSE     (1 << 2)
#define BBTOP_CRU_FAST_CLOCK_ENABLE (1 << 3)

/* BOOT_STAT */
#define BOOT_CTRL_STRAP_OFF         0
#define BOOT_CTRL_STRAP_MSK         (0x0F << BOOT_CTRL_STRAP_OFF)
#ifdef __BRAVO__
#define ROM_BOOT_SRC_ROM_EXTNOR_SAMSUNG_BIG3   (0x0F << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTNOR_NUMORYX_BIG3   (0x0E << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTNOR_ADMUX          (0x0D << BOOT_CTRL_STRAP_OFF) /* big3 & big4*/
#define ROM_BOOT_SRC_ROM_EXTNOR_SAMSUNG_BIG4   (0x0C << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTNOR_NUMORYX_BIG4   (0x0B << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_SBUS                      (0x0A << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_JTAG                      (0x09 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_EXTNOR_ADMUX              (0x08 << BOOT_CTRL_STRAP_OFF) /*big3 & big4*/
#define ROM_BOOT_SRC_EXTNOR_SAMSUNG_BIG3       (0x07 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_EXTNOR_NUMORYX_BIG3       (0x06 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_QSP0                      (0x05 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_QSP1                      (0x04 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTSPI0               (0x03 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTSPI1               (0x02 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_EXTNOR_SAMSUNG_BIG4       (0x01 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_EXTNOR_NUMORYX_BIG4       (0x00 << BOOT_CTRL_STRAP_OFF)
#elif defined(__MSW8522__)
#define ROM_BOOT_SRC_ROM_EXTNOR_SPANSION       (0x0F << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTNOR_NUMORYX        (0x0E << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTNOR_ADMUX          (0x0D << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTNAND8_107          (0x0C << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTNAND8_149          (0x0B << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_SBUS                      (0x0A << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_JTAG                      (0x09 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTNOR_ADMUX_SPI      (0x08 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_EXTNOR_SPANSION           (0x07 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_NONE_1       			   (0x06 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_NONE_0                    (0x05 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_SPI_EXTNOR_ADMUX_SPI      (0x04 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTNAND8_130          (0x03 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTNAND16_107         (0x02 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTNAND16_149         (0x01 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTNAND16_130         (0x00 << BOOT_CTRL_STRAP_OFF)
#elif defined(__MSW8556__)
#define ROM_BOOT_SRC_ROM_EXTNOR_SPANSION        (0x0F << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTNOR_NUMORYX         (0x0E << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTNOR_ADMUX           (0x0D << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTNOR_ADMUX_EMBED_SPI (0x0C << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_NONE_5          		    (0x0B << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_SBUS                       (0x0A << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_JTAG                       (0x09 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_ROM_EXTNOR_ADMUX_SPI       (0x08 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_EXTNOR_SPANSION            (0x07 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_SBUS_JTAG     			    (0x06 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_NONE_4                     (0x05 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_SPI_EXTNOR_ADMUX_SPI       (0x04 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_NONE_3			            (0x03 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_NONE_2			            (0x02 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_NONE_1			            (0x01 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_SRC_NONE_0			            (0x00 << BOOT_CTRL_STRAP_OFF)
#else
#define ROM_BOOT_EXTNAND16_130BALL  (0x00 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_EXTNAND16_NOSWAP   (0x01 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_EXTNAND16_SWAP     (0x02 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_EXTNAND8_130BALL   (0x03 << BOOT_CTRL_STRAP_OFF)
#define SPI_BOOT_EXTNOR             (0x04 << BOOT_CTRL_STRAP_OFF)
#define SPI_BOOT_EXTNAND            (0x05 << BOOT_CTRL_STRAP_OFF)
#define NOR_BOOT_EXTNOR_SWAP        (0x06 << BOOT_CTRL_STRAP_OFF)
#define NOR_BOOT_EXTNOR_NOSWAP      (0x07 << BOOT_CTRL_STRAP_OFF)
#define NOR_BOOT_EXTNOR_ADMUX       (0x08 << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_EXTNAND8_NOSWAP    (0x0B << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_EXTNAND8_SWAP      (0x0C << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_EXTNOR_ADMUX       (0x0D << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_EXTNOR_SWAP        (0x0E << BOOT_CTRL_STRAP_OFF)
#define ROM_BOOT_EXTNOR_NOSWAP      (0x0F << BOOT_CTRL_STRAP_OFF)
#endif // __BRAVO__
#define BOOT_CTRL_U0TXD_OFF         4
#define BOOT_CTRL_U0TXD_MSK         (0x01 << BOOT_CTRL_U0TXD_OFF)
#define BOOT_CTRL_U0TXD_DWL         (0x00 << BOOT_CTRL_U0TXD_OFF)
#define BOOT_CTRL_U0TXD_NORM        (0x01 << BOOT_CTRL_U0TXD_OFF)
#define DWL_CHK_SET_COMPLETE        0xA5


/* CLKGENs */
#define CRU_IP_RESET_OFF            0
#define CRU_IP_RESET_MSK            (0x01 << CRU_IP_RESET_OFF)
#define CRU_CLK_GATING_OFF          1
#define CRU_CLK_GATING_MSK          (0x01 << CRU_CLK_GATING_OFF)
#define CRU_CLK_INVERSE_OFF         2
#define CRU_CLK_INVERSE_MSK         (0x01 << CRU_CLK_INVERSE_OFF)
#define CRU_FAST_CLKEN_OFF          3
#define CRU_FAST_CLKEN_MSK          (0x01 << CRU_FAST_CLKEN_OFF)
#define CRU_CLK_SEL_OFF             4
#define CRU_CLK_SEL_MSK             (0x0F << CRU_CLK_SEL_OFF)
#define CRU_CLK_DIVEN_OFF           8
#define CRU_CLK_DIVEN_MSK           (0x01 << CRU_CLK_DIVEN_OFF)
#define CRU_DIV_FACT1_OFF           9
#define CRU_DIV_FACT1_MSK           (0x7F << CRU_DIV_FACT1_OFF)
#define CRU_DIV_FACT2_OFF           0
#define CRU_DIV_FACT2_MSK           (0x03 << CRU_DIV_FACT2_OFF)

#define CRU_SEL_SLOW                0x10
#define CRU_SEL_NONE                0xFF

/* CRU_XIU */
#define XIU_SEL_312MHZ              7
#define XIU_SEL_156MHZ              6
#define XIU_SEL_96MHZ               5
#define XIU_SEL_89M14HZ             4
#define XIU_SEL_78MHZ               3
#define XIU_SEL_60MHZ               2
#define XIU_SEL_39MHZ               1
#define XIU_SEL_26MHZ               0

/* CRU_NFIE */
#define NFIE_SEL_SSC                12
#define NFIE_SEL_78MHZ              11
#define NFIE_SEL_52MHZ              10
#define NFIE_SEL_44M57HZ            9
#define NFIE_SEL_39MHZ              8
#define NFIE_SEL_26MHZ              7
#define NFIE_SEL_22M29HZ            6
#define NFIE_SEL_19M50HZ            5
#define NFIE_SEL_13MHZ              4
#define NFIE_SEL_10M40HZ            3
#define NFIE_SEL_6MHZ               2
#define NFIE_SEL_750KHZ             1
#define NFIE_SEL_190KHZ             0


//------------------------------------------------------------------------------
// Typedefs
//------------------------------------------------------------------------------
/**********************************************/
/* BB_TOP Register Bank                       */
/**********************************************/
typedef struct BbTop_s
{
    /* [0x00] */
    u32 reg_bist_en                   :1 ; /// Switch clkgen to bist_en mode
    u32 :31; /// [0x00]
    /* [0x01] */
    u32 reg_top_sdint_clear           :1 ; /// None
    u32 :31; /// [0x01]
    /* [0x02] */
    u32 reg_top_read                  :16; /// None
    u32 :16; /// [0x02]
    /* [0x03] */
    u32 reg_debug_sel                 :5 ; /// bb_top debug bus select
    u32 :3 ; /// [0x03]
    u32 reg_dbgclk_sel                :5 ; /// bb_top debug clock select
    u32 :19; /// [0x03]
    /* [0x04] */
    u32 reg_dbgclk_bit_sel            :5 ; /// bb_top debug clock bit select
    u32 reg_dbgclk_en                 :1 ; /// bb_top debug clock enable
    u32 reg_divclk_sel                :3 ; /// bb_top debug clock divide select
    u32 :23; /// [0x04]
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
    u32 reg_top_spare                 :16; /// spare register
    u32 :16; /// [0x10]
    /* [0x11] */
    u32 reg_top_spare1                :16; /// spare register
    u32 :16; /// [0x11]
    /* [0x12] */
    u32 reg_top_spare2                :16; /// spare register
    u32 :16; /// [0x12]
    /* [0x13] */
    u32 reg_top_spare3                :16; /// spare register
    u32 :16; /// [0x13]
    /* [0x14] */
    u32 reg_top_spare4                :16; /// spare register
    u32 :16; /// [0x14]
    /* [0x15] */
    u32 reg_top_spare5                :16; /// spare register
    u32 :16; /// [0x15]
    /* [0x16] */
    u32 reg_top_spare6                :16; /// spare register
    u32 :16; /// [0x16]
    /* [0x17] */
    u32 reg_top_spare7                :16; /// spare register
    u32 :16; /// [0x17]
    /* [0x18] */
    u32 reg_top_spare8                :16; /// spare register
    u32 :16; /// [0x18]
    /* [0x19] */
    u32 reg_top_spare9                :8; /// spare register
    u32 reg_dwl_chk                   :8;
    u32 :16; /// [0x19]
    /* [0x1A] */
    u32 reg_top_spare10               :16; /// spare register
    u32 :16; /// [0x1A]
    /* [0x1B] */
    u32 reg_top_spare11               :16; /// spare register
    u32 :16; /// [0x1B]
    /* [0x1C] */
    u32 reg_top_spare12               :16; /// spare register
    u32 :16; /// [0x1C]
    u32 :32; /// [0x1D]
    u32 :32; /// [0x1E]
    u32 :32; /// [0x1F]
    /* [0x20] */
    u32 reg_boot_status_raw           :7 ; /// boot control raw status
    u32 :25; /// [0x20]
    /* [0x21] */
    u32 reg_dec_status_raw            :11; /// decode value raw status
    u32 :21; /// [0x21]
    /* [0x22] */
    u32 reg_emi_status_raw            :5 ; /// EMI decode value raw status
    u32 :27; /// [0x22]
    /* [0x23] */
    u32 reg_keypad_row_status_raw     :6 ; /// keypad value raw status for row
    u32 reg_keypad_col_status_raw     :7 ; /// keypad value raw status for column
    u32 :19; /// [0x23]
    /* [0x24] */
    u32 reg_boot_ctrl_ow_key          :4 ; /// Only value 4h'a can be set as the key to select overwrite value of boot_ctrl[5:0].
    u32 :28; /// [0x24]
    /* [0x25] */
    u32 reg_dec_ctrl_ow_key           :4 ; /// Only value 4h'a can be set as the key to select overwrite value of boot_ctrl[5:0].
    u32 :28; /// [0x25]
    /* [0x26] */
    u32 reg_emi_ctrl_ow_key           :4 ; /// Only value 4h'a can be set as the key to select overwrite value of boot_ctrl[5:0].
    u32 :28; /// [0x26]
    /* [0x27] */
    u32 reg_keypad_ctrl_ow_key        :4 ; /// Only value 4h'a can be set as the key to select overwrite value of keypad_ctrl[5:0].
    u32 :28; /// [0x27]
    /* [0x28] */
    u32 reg_boot_owv_0                :16; /// overwrite value
    u32 :16; /// [0x28]
    u32 reg_boot_owv_1                :6 ; /// @see reg_boot_owv_0
    u32 :26; /// [0x29]
    /* [0x2A] */
    u32 reg_keypad_owv                :13; /// overwrite value
    u32 :19; /// [0x2A]
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
    u32 :32; /// [0x3C]
    u32 :32; /// [0x3D]
    u32 :32; /// [0x3E]
    u32 :32; /// [0x3F]
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
    /* [0x50] */
    u16 reg_cru_bist;                      /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
                                           /// [7:4] Clock select
                                           /// [8]: div_en
                                           /// [13:9]: div_factor
    u16 :16; /// [0x50]
    /* [0x51] */
    u16 reg_cru_sdio_0;                    /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
                                           /// [7:4] Clock select
                                           /// [8]: div_en
                                           /// [18:9]: div_factor
    u16 :16; /// [0x51]
    u32 reg_cru_sdio_1                :3 ; /// @see reg_cru_sdio_0
    u32 :29; /// [0x52]
    /* [0x53] */
    u16 reg_cru_nfie_0;                    /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
                                           /// [7:4] Clock select
                                           /// [8]: div_en
                                           /// [18:9]: div_factor
    u16 :16; /// [0x53]
    u32 reg_cru_nfie_1                :3 ; /// @see reg_cru_nfie_0
    u32 :29; /// [0x54]
    /* [0x55] */
    u16 reg_cru_icp;                       /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
                                           /// [6:4] Clock select
    u16 :16; /// [0x55]
    /* [0x56] */
    u16 reg_cru_scl;                       /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
                                           /// [6:4] Clock select
    u16 :16; /// [0x56]
    /* [0x57] */
    u16 reg_cru_jpde;                      /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
                                           /// [6:4] Clock select
    u16 :16; /// [0x57]
    /* [0x58] */
    u16 reg_gater_jpde;                    /// jpde clk gater
    u16 :16; /// [0x58]
    /* [0x59] */
    u16 reg_cru_mpif;                      /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
                                           /// [6:4] Clock select
                                           /// [8]: div_en
                                           /// [13:9]: div_factor
    u16 :16; /// [0x59]
    /* [0x5A] */
    u16 reg_cru_xiu;                       /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
                                           /// [7:4] Clock select
                                           /// [8]: div_en
                                           /// [13:9]: div_factor
    u16 :16; /// [0x5A]
    /* [0x5B] */
    u16 reg_cru_fmrx_312;                  /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x5B]
    /* [0x5C] */
    u16 reg_cru_fmrx;                      /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
                                           /// [4]: Clock select
    u16 :16; /// [0x5C]
    /* [0x5D] */
    u16 reg_cru_fmrx_i2s;                  /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x5D]
    /* [0x5E] */
    u16 reg_cru_miu;                       /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
                                           /// [6:4] Clock select
                                           /// [8]: div_en
                                           /// [13:9]: div_factor
    u16 :16; /// [0x5E]
    /* [0x5F] */
    u16 reg_cru_emi_32k;                   /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x5F]
    /* [0x60] */
    u16 reg_cru_aux;                       /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x60]
    /* [0x61] */
    u16 reg_cru_aux_32k;                   /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x61]
    /* [0x62] */
    u16 reg_cru_aux_16k;                   /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x62]
    /* [0x63] */
    u16 reg_cru_aux_128;                   /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x63]
    /* [0x64] */
    u16 reg_cru_audio_32k;                 /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x64]
    /* [0x65] */
    u16 reg_cru_audio_128;                 /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x65]
    /* [0x66] */
    u16 reg_cru_spi;                       /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
                                           /// [5:4] Clock select
                                           /// [8]: div_en
                                           /// [13:9]: div_factor
    u16 :16; /// [0x66]
    /* [0x67] */
    u16 reg_cru_au_src;                    /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x67]
    /* [0x68] */
    u16 reg_cru_au_mac;                    /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x68]
    /* [0x69] */
    u16 reg_cru_rf_26m;                    /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x69]
    /* [0x6A] */
    u32 reg_rf_sw_rst                 :1 ; /// RF module software reset
    u32 :31; /// [0x6A]
    /* [0x6B] */
    u16 reg_cru_gps_32k;                   /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x6B]
    /* [0x6C] */
    u16 reg_cru_db_bus;                    /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x6C]
    /* [0x6D] */
    u16 reg_cru_utmi_as_214;               /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x6D]
    /* [0x6E] */
    u16 reg_cru_utmi_as_192;               /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x6E]
    /* [0x6F] */
    u16 reg_cru_utmi_as_120;               /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x6F]
    /* [0x70] */
    u16 reg_cru_sr_m;                      /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
                                           /// [7:4]: Clock select
                                           /// [8]: div_en
                                           /// [13:9]: div_factor
    u16 :16; /// [0x70]
    /* [0x71] */
    u16 reg_cru_sr_p;                      /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
                                           /// [5:4]: Clock select
    u16 :16; /// [0x71]
    /* [0x72] */
    u16 reg_cru_adc_dma;                   /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
                                           /// [5:4]: Clock select
    u16 :16; /// [0x72]
    /* [0x73] */
    u16 reg_cru_rf_rx;                     /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
    u16 :16; /// [0x73]
    /* [0x74] */
    u16 reg_cru_disp;                      /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
                                           /// [6:4]: Clock select
                                           /// [8]: div_en
                                           /// [13:9]: div_factor
    u16 :16; /// [0x74]
    /* [0x75] */
    u16 reg_cru_padout_26m;                /// [0]: IP reset
                                           /// [1]: Clock gating
                                           /// [2]: Clock inverse
                                           /// [3]: Fast clock enable
} BbTop_t;

#endif  // __KERNEL_BBTOP_H__
