#ifndef __KERNEL_PADCTRL_H__
#define __KERNEL_PADCTRL_H__

/************************************************/
/* Pad Ctrl Register Bank                       */
/************************************************/

typedef struct KePadCtrl_s
{
    /* [0x00] */
    u32 reg_test_in_1st_mode          :3 ; /// test in mode
    u32 reg_test_in_2nd_mode          :3 ; /// test in mode
    u32 :2 ; /// [0x00]
    u32 reg_test_out_1st_mode         :4 ; /// test out mode
    u32 reg_test_out_2nd_mode         :4 ; /// test out mode
    u32 :16; /// [0x00]
    /* [0x01] */
    u32 reg_btif_mode                 :2 ; /// Bluetooth PAD Mode
    u32 reg_mpif_mode                 :2 ; /// MPIF PAD Mode
    u32 reg_sim1_en                   :1 ; /// Sim Card1 PAD enable
    u32 reg_sim2_en                   :1 ; /// Sim Card2 PAD enable
    u32 reg_dig_rf_test_en            :1 ; /// test in mode
    u32 :1 ; /// [0x01]
    u32 reg_pwm_in_mode               :3 ; /// PWM IN PAD selection
    u32 :1 ; /// [0x01]
    u32 reg_efuse_in_en               :1 ; /// EFUSE I/F input enable
    u32 :1 ; /// [0x01]
    u32 reg_wifi_antenna_mode         :2 ; /// WiFi Antenna Control PAD enable
    u32 :16; /// [0x01]
    /* [0x02] */
    u32 reg_key7x6_en                 :1 ; /// KeyPAD 7x6 PAD enable
    u32 :3 ; /// [0x02]
    u32 reg_col7_mode                 :3 ; /// Keypad COL[7] enable
    u32 :1 ; /// [0x02]
    u32 reg_row6_mode                 :3 ; /// Keypad ROW[6] enable
    u32 :1 ; /// [0x02]
    u32 reg_row7_mode                 :2 ; /// Keypad ROW[7] enable
    u32 :18; /// [0x02]
    /* [0x03] */
    u32 reg_sd_mode                   :3 ; /// Micro SD PAD Mode
    u32 :1 ; /// [0x03]
    u32 reg_sd_cdz_en                 :2 ; /// Micro SD CDZ enable
    u32 :2 ; /// [0x03]
    u32 reg_sd1_mode                  :3 ; /// 2nd Micro SD PAD Mode
    u32 :1 ; /// [0x03]
    u32 reg_sd1_cdz_en                :3 ; /// 2nd Micro SD CDZ Mode
    u32 :17; /// [0x03]
    /* [0x04] */
    u32 reg_pwm0_mode                 :3 ; /// PWM0 output PAD selection
    u32 :1 ; /// [0x04]
    u32 reg_pwm1_mode                 :3 ; /// PWM1 output PAD selection
    u32 :1 ; /// [0x04]
    u32 reg_pmupwm_en                 :1 ; /// PMU PWM PAD enable
    u32 :23; /// [0x04]
    /* [0x05] */
    u32 reg_rx_i2s_mode               :1 ; /// None
    u32 :3 ; /// [0x05]
    u32 reg_ext_codec_i2s_mode        :2 ; /// None
    u32 :2 ; /// [0x05]
    u32 reg_gps_clk_out_mode          :3 ; /// None
    u32 :1 ; /// [0x05]
    u32 reg_gps_clk_out2_mode         :3 ; /// None
    u32 :17; /// [0x05]
    /* [0x06] */
    u32 reg_dbg_uart_mode             :3 ; /// None
    u32 :1 ; /// [0x06]
    u32 reg_dbg_uart_rts_mode         :3 ; /// None
    u32 :1 ; /// [0x06]
    u32 reg_fuart_mode                :3 ; /// None
    u32 :1 ; /// [0x06]
    u32 reg_bt_pcm_mode               :2 ; /// None
    u32 :18; /// [0x06]
    /* [0x07] */
    u32 reg_qbsave_mode               :4 ; /// None
    u32 :1 ; /// [0x07]
    u32 reg_sr_en                     :1 ; /// None
    u32 reg_i2c_en                    :1 ; /// None
    u32 reg_spi_sr_en                 :1 ; /// None
    u32 :24; /// [0x07]
    /* [0x08] */
    u32 reg_lcd_mode                  :2 ; /// LCD PAD enable
    u32 reg_lcd_share_mode            :1 ; /// LCD share EMI IO enable
    u32 reg_lcd_rstz_opendrain        :1 ; /// 1:control lcd_rstz with open drain,0:control lcd_rstz with push-pull
    u32 reg_lcd_cs1_mode              :4 ; /// LCD CS1 PAD enable
    u32 reg_lcd_cs0_mode              :4 ; /// LCD CS0 PAD enable
    u32 reg_lcd_fmark_mode            :4 ; /// None
    u32 :16; /// [0x08]
    /* [0x09] */
    u32 :4 ; /// [0x09]
    u32 reg_serial_lcd_mode           :4 ; /// Serial LCD PAD enable
    u32 reg_serial_lcd_cs1_mode       :2 ; /// Serial LCD CS1 PAD enable
    u32 :2 ; /// [0x09]
    u32 reg_lcd_rs_mode               :3 ; /// serial LCM RS PAD enable
    u32 :17; /// [0x09]
    /* [0x0A] */
    u32 reg_mspi_mode                 :3 ; /// MSPI Mode
    u32 reg_mspi_cs0_mode             :3 ; /// MSPI CS0 Mode
    u32 reg_mspi_cs1_mode             :3 ; /// MSPI CS1 Mode
    u32 :23; /// [0x0A]
    /* [0x0B] */
    u32 reg_26mhz_out_mode            :4 ; /// 26MHz clock output PAD enable
    u32 reg_tbuo_en                   :1 ; /// TBUO PAD enable
    u32 :3 ; /// [0x0B]
    u32 reg_seth                      :1 ; /// set high to all PADs at test mode
    u32 reg_setl                      :1 ; /// set low to all PADs at test mode
    u32 :2 ; /// [0x0B]
    u32 reg_allpad_in                 :1 ; /// program all PADs to become input mode
    u32 :1 ; /// [0x0B]
    u32 reg_nand_8bit_mode            :1 ; /// None
    u32 :17; /// [0x0B]
    /* [0x0C] */
    u32 reg_ext_int0_sel              :7 ; /// [6]:1:enable external IRQ,0:disable external IRQ
    u32 :1 ; /// [0x0C]
    u32 reg_ext_int1_sel              :7 ; /// [6]:1:enable external IRQ,0:disable external IRQ
    u32 :17; /// [0x0C]
    /* [0x0D] */
    u32 reg_ext_int2_sel              :7 ; /// [6]:1:enable external IRQ,0:disable external IRQ
    u32 :1 ; /// [0x0D]
    u32 reg_ext_int3_sel              :7 ; /// [6]:1:enable external IRQ,0:disable external IRQ
    u32 :17; /// [0x0D]
    /* [0x0E] */
    u32 reg_ext_int4_sel              :7 ; /// [6]:1:enable external IRQ,0:disable external IRQ
    u32 :1 ; /// [0x0E]
    u32 reg_ext_int5_sel              :7 ; /// [6]:1:enable external IRQ,0:disable external IRQ
    u32 :17; /// [0x0E]
    /* [0x0F] */
    u32 reg_ext_int6_sel              :7 ; /// [6]:1:enable external IRQ,0:disable external IRQ
    u32 :1 ; /// [0x0F]
    u32 reg_ext_int7_sel              :7 ; /// [6]:1:enable external IRQ,0:disable external IRQ
    u32 :17; /// [0x0F]
    /* [0x10] */
    u32 reg_ext_int8_sel              :7 ; /// [6]:1:enable external IRQ,0:disable external IRQ
    u32 :1 ; /// [0x10]
    u32 reg_ext_int9_sel              :7 ; /// [6]:1:enable external IRQ,0:disable external IRQ
    u32 :17; /// [0x10]
    /* [0x11] */
    u32 reg_ext_int10_sel             :7 ; /// [6]:1:enable external IRQ,0:disable external IRQ
    u32 :1 ; /// [0x11]
    u32 reg_ext_int11_sel             :7 ; /// [6]:1:enable external IRQ,0:disable external IRQ
    u32 :17; /// [0x11]
    /* [0x12] */
    u32 reg_ext_int12_sel             :7 ; /// [6]:1:enable external IRQ,0:disable external IRQ
    u32 :1 ; /// [0x12]
    u32 reg_ext_int13_sel             :7 ; /// [6]:1:enable external IRQ,0:disable external IRQ
    u32 :17; /// [0x12]
    /* [0x13] */
    u32 reg_ext_int14_sel             :7 ; /// [6]:1:enable external IRQ,0:disable external IRQ
    u32 :1 ; /// [0x13]
    u32 reg_ext_int15_sel             :7 ; /// [6]:1:enable external IRQ,0:disable external IRQ
    u32 :17; /// [0x13]
    /* [0x14] */
    u32 reg_ext_int_en                :1 ; /// None
    u32 :31; /// [0x14]
    /* [0x15] */
    u32 reg_dbb_spi_mode              :3 ; /// Digital Baseband SPI PAD enable
    u32 :1 ; /// [0x15]
    u32 reg_dbb_spi_cs0_mode          :3 ; /// Digital Baseband SPI CS0 PAD enable
    u32 :1 ; /// [0x15]
    u32 reg_dbb_spi_cs1_mode          :3 ; /// Digital Baseband SPI CS1 PAD enable
    u32 :21; /// [0x15]
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
    u32 reg_clk_out_sel               :3 ; /// dbg_ctrl
    u32 :1 ; /// [0x20]
    u32 reg_single_clk_out_sel        :3 ; /// dbg_ctrl
    u32 :1 ; /// [0x20]
    u32 reg_test_rg                   :1 ; /// dbg_ctrl
    u32 reg_test_gb                   :1 ; /// dbg_ctrl
    u32 reg_test_rb                   :1 ; /// dbg_ctrl
    u32 reg_testclk_mode              :1 ; /// dbg_ctrl
    u32 reg_rosc_in_sel               :1 ; /// dbg_ctrl
    u32 reg_swaptest12bit             :1 ; /// dbg_ctrl
    u32 reg_rosc_out_sel              :2 ; /// dbg_ctrl
    u32 :16; /// [0x20]
    /* [0x21] */
    u32 reg_test_bus24b_sel           :6 ; /// dbg_ctrl
    u32 :2 ; /// [0x21]
    u32 reg_testbus_en                :1 ; /// dbg_ctrl
    u32 :3 ; /// [0x21]
    u32 reg_clk_calc_en               :1 ; /// dbg_ctrl
    u32 :19; /// [0x21]
    /* [0x22] */
    u32 reg_calc_cnt_report           :16; /// None
    u32 :16; /// [0x22]
    /* [0x23] */
    u32 reg_mcp_test_mode             :2 ; /// None
    u32 :30; /// [0x23]
    /* [0x24] */
    u32 reg_24bit_test_out_0          :16; /// None
    u32 :16; /// [0x24]
    u32 reg_24bit_test_out_1          :8 ; /// @see reg_24bit_test_out_0
    u32 :24; /// [0x25]
    /* [0x26] */
    u32 reg_boot_spi0_pad_en          :1 ; /// pad mux for QSPI0 enable
    u32 reg_boot_spi1_pad_en          :1 ; /// pad mux for QSPI1 enable
    u32 :30; /// [0x26]
    /* [0x27] */
    u32 reg_adc_ts1_pm0               :1 ; /// access right to ADC
                                           /// 0: AUX DTOP
                                           /// 1: PM SAR DTOP
    u32 :31; /// [0x27]
    /* [0x28] */
    u32 reg_wifi_clk_en_mode          :3 ; /// WIFI_CLK_EN pad enable
    u32 :29; /// [0x28]
    u32 :32; /// [0x29]
    u32 :32; /// [0x2A]
    u32 :32; /// [0x2B]
    u32 :32; /// [0x2C]
    u32 :32; /// [0x2D]
    u32 :32; /// [0x2E]
    u32 :32; /// [0x2F]
    /* [0x30] */
    u32 reg_pad_ctrl_reserved0        :16; /// pad ctrl reserved0 registers
                                           /// [0]: LCD_DCX mode output to PAD_LCD_D[1]
    u32 :16; /// [0x30]
    /* [0x31] */
    u32 reg_pad_ctrl_reserved1        :16; /// pad ctrl reserved1 registers
    u32 :16; /// [0x31]
    /* [0x32] */
    u32 reg_pad_ctrl_reserved2        :16; /// pad ctrl reserved2 registers
    u32 :16; /// [0x32]
    /* [0x33] */
    u32 reg_pad_ctrl_reserved3        :16; /// pad ctrl reserved3 registers
} KePadCtrl_t;


extern volatile KePadCtrl_t * const g_ptKePadCtrl;

#endif /*__KERNEL_PADCTRL_H__*/
