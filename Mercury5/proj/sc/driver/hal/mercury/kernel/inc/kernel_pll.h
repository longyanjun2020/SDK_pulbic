#ifndef __KERNEL_PLL_H__
#define __KERNEL_PLL_H__

/************************************************/
/* RIU PLL Bank                                 */
/************************************************/

typedef struct KePll_s {
    /* [0x00] */
    u32 reg_pll22_resetb              :1 ; /// PLL22 software reset, low active
    u32 reg_pll22_resetb_ovrw         :1 ; /// PLL22 software reset overwrite
    u32 :30; /// [0x00]
    /* [0x01] */
    u32 reg_pll22_enable              :1 ; /// enable PLL22, high active
    u32 reg_pll22_enable_ovrw         :1 ; /// enable PLL22 overwrite
    u32 :30; /// [0x01]
    /* [0x02] */
    u32 reg_pll_in_sel                :1 ; /// select MCLK frequency, 1'b0: 13MHz; 1'b1: 26MHz
    u32 reg_pll_in_sel_ovrw           :1 ; /// PLL_IN_SEL overwrite
    u32 :30; /// [0x02]
    /* [0x03] */
    u32 reg_en_sqr                    :1 ; /// enable clock squarer, high active
    u32 reg_en_sqr_ovrw               :1 ; /// enable clock squarer overwrite
    u32 :30; /// [0x03]
    /* [0x04] */
    u32 reg_clk_sqr_outen             :1 ; /// enable clock squarer output, high active
    u32 reg_clk_sqr_outen_ovrw        :1 ; /// enable clock squarer output overwrite
    u32 :30; /// [0x04]
    /* [0x05] */
    u32 reg_pll22_test                :8 ; /// PLL22 test bits
                                           /// TEST[7:5]: Icp Current
                                           /// 3'b000: 2.5uA
                                           /// 3'b001: 5uA
                                           /// 3'b010: 7.5uA
                                           /// 3'b011: 10uA
                                           /// 3'b100: 12.5uA
                                           /// 3'b101: 15uA
                                           /// 3'b110: 17.5uA
                                           /// 3'b111: 20uA
                                           /// TEST[4]: VCO ENFRUNZ
                                           /// TEST[3:2]: PORST & PORST selected
                                           /// TEST[1]: TEST CLK OUT selected
                                           /// TEST[0]: EN lock detect
    u32 :24; /// [0x05]
    /* [0x06] */
    u32 reg_pll_test                  :16; /// pll_top test bits
    u32 :16; /// [0x06]
    u32 :32; /// [0x07]
    /* [0x08] */
    u32 reg_mpll_bypass               :1 ; /// bypass clock squarer, high active
    u32 reg_en_pll_reg                :1 ; /// enable pll internal 1.2V regulator , high active
    u32 :30; /// [0x08]
    /* [0x09] */
    u32 reg_mux_ddr48m                :1 ; /// enable CLK_DDR48M , high active
    u32 :31; /// [0x09]
    /* [0x0A] */
    u32 reg_en_rf_ana_26m             :1 ; /// enable CLK_RF_ANA_26M , high active
    u32 reg_en_rf_dig_26m             :1 ; /// enable CLK_RF_DIG_26M , high active
    u32 reg_en_ddr48m                 :1 ; /// enable CLK_DDR48M , high active
    u32 reg_en_fm_26m                 :1 ; /// enable CLK_FM_26M , high active
    u32 reg_en_audio_48m              :1 ; /// enable CLK_AUDIO_48M_3V , high active
    u32 reg_en_fmpll_39m              :1 ; /// enable CLK_FMPLL_39M, high acitve
    u32 :26; /// [0x0A]
    /* [0x0B] */
    u32 reg_en_pll_312m               :1 ; /// enable CLK_PLL_312M , high active
    u32 reg_en_pll_156m               :1 ; /// enable CLK_PLL_156M , high active
    u32 reg_en_pll_104m               :1 ; /// enable CLK_PLL_104M , high active
    u32 reg_en_pll_62p4m              :1 ; /// enable CLK_PLL_62P4M , high active
    u32 reg_en_pll_60m12m             :1 ; /// enable CLK_PLL_60M CLK_PLL_12M  , high active
    u32 reg_en_pll_mclk               :1 ; /// enable CLK_PLL_MCLK , high active
    u32 reg_en_pll_208m               :1 ; /// enable CLK_PLL_208M , high active
    u32 reg_en_pll_124p8m             :1 ; /// enable CLK_PLL_124P8M , high active
    u32 reg_en_pll_89p1m              :1 ; /// enable CLK_PLL_89P1M , high active
    u32 reg_en_pll_69p3m              :1 ; /// enable CLK_PLL_69P3M , high active
    u32 reg_en_pll_56p7m              :1 ; /// enable CLK_PLL_56P7M , high active
    u32 reg_en_pll_48m                :1 ; /// enable CLK_PLL_48M , high active
    u32 :20; /// [0x0B]
    /* [0x0C] */
    u32 reg_pll22_divfb_1st           :2 ; /// PLL22 loop divider first stage div 2^N
    u32 :30; /// [0x0C]
    /* [0x0D] */
    u32 reg_pll22_divfb_2nd           :8 ; /// PLL22 loop divider second stage div N
    u32 :24; /// [0x0D]
    /* [0x0E] */
    u32 reg_pll22_lock                :1 ; /// PLL22 lock status
    u32 :31; /// [0x0E]
    /* [0x0F] */
    u32 reg_debug_out_0               :16; /// debug output
    u32 :16; /// [0x0F]
    u32 reg_debug_out_1               :8 ; /// @see reg_debug_out_0
    u32 :24; /// [0x10]
    /* [0x11] */
    u32 reg_debug_sel                 :4 ; /// debug selection
    u32 :28; /// [0x11]
    /* [0x12] */
    u32 reg_pll_dummy0                :16; /// PLL dummy register 0
    u32 :16; /// [0x12]
    /* [0x13] */
    u32 reg_pll_dummy1                :16; /// PLL dummy register 1
    u32 :16; /// [0x13]
    /* [0x14] */
    u32 reg_pll_dummy_r               :16; /// PLL dummy read register
    u32 :16; /// [0x14]
    /* [0x15] */
    u32 reg_dis_mmp_312m              :1 ; /// disable MMP 312MHZ clock
    u32 reg_dis_dbb_312m              :1 ; /// disable DBB 312MHZ clock
    u32 reg_dis_mmp_208m              :1 ; /// disable MMP 208MHZ clock
    u32 reg_dis_dbb_208m              :1 ; /// disable DBB 208MHZ clock
    u32 reg_dis_mmp_124p8m            :1 ; /// disable MMP 124.8MHZ clock
    u32 reg_dis_dbb_124p8m            :1 ; /// disable DBB 124.8MHZ clock
    u32 reg_dis_mmp_26m               :1 ; /// disable DBB 26M
    u32 reg_dis_dbb_26m               :1 ; /// disable MMP 26M
    u32 :24; /// [0x15]
    /* [0x16] */
    u32 reg_312m_to_dbb_sel_ssc       :1 ; /// to DBB 312M clock with SSC 
    u32 reg_208m_to_dbb_sel_ssc       :1 ; /// to DBB 208M clock with SSC 
    u32 reg_124p8m_to_dbb_sel_ssc     :1 ; /// to DBB 124P8M clock with SSC 
    u32 reg_dbb_26m_sel               :1 ; /// 0 : raw 26Mhz
                                           /// 1 : FN PLL 26M
    u32 reg_mmp_26m_sel               :2 ; /// 2'b0x : raw 26Mhz
                                           /// 2'b10 : FN PLL 26M without SSC
                                           /// 2'b11 : FNPLL 26M with SSC
    u32 :26; /// [0x16]
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
    u32 reg_ssc_en                    :1 ; /// None
    u32 reg_ssc_rstz                  :1 ; /// reset for cmu_pll_synth, low active
    u32 reg_ssc_vco_offset            :1 ; /// None
    u32 reg_ssc_clkin_sel             :1 ; /// None
    u32 reg_ssc_dften                 :1 ; /// None
    u32 reg_ssc_clksrc_sel            :1 ; /// ssc synthesis clock soruce select
                                           /// 0 : 156Mhz
                                           /// 1 : 312Mhz
    u32 reg_en_ssc_by_pmu             :1 ; /// enable ssc_pll by pmu 
    u32 :25; /// [0x20]
    /* [0x21] */
    u32 reg_ssc_loop_div_2nd          :3 ; /// None
    u32 :1 ; /// [0x21]
    u32 reg_ssc_loop_div_1st          :2 ; /// None
    u32 :2 ; /// [0x21]
    u32 reg_ssc_input_div_1st         :2 ; /// None
    u32 :2 ; /// [0x21]
    u32 reg_ssc_ictrl                 :3 ; /// None
    u32 :17; /// [0x21]
    /* [0x22] */
    u32 reg_ssc_test                  :7 ; /// None
    u32 :25; /// [0x22]
    /* [0x23] */
    u32 reg_ssc_en_ddr48              :1 ; /// None
    u32 reg_ssc_en_pll_312m           :1 ; /// None
    u32 reg_ssc_en_pll_208m           :1 ; /// None
    u32 reg_ssc_en_pll_156m           :1 ; /// None
    u32 reg_ssc_en_pll_104m           :1 ; /// None
    u32 reg_ssc_en_pll_48m            :1 ; /// None
    u32 reg_ssc_en_pll_124p8m         :1 ; /// None
    u32 reg_ssc_en_pll_89p1m          :1 ; /// None
    u32 reg_ssc_en_pll_69p3m          :1 ; /// None
    u32 reg_ssc_en_pll_62p4m          :1 ; /// None
    u32 reg_ssc_en_pll_56p7m          :1 ; /// None
    u32 reg_ssc_en_pll_60m12m         :1 ; /// None
    u32 :20; /// [0x23]
    /* [0x24] */
    u32 reg_ssc_set_0                 :16; /// None
    u32 :16; /// [0x24]
    u32 reg_ssc_set_1                 :8 ; /// @see reg_ssc_set_0
    u32 :24; /// [0x25]
    /* [0x26] */
    u32 reg_ssc_sld                   :1 ; /// write one to update reg_ssc_set, must toggle after reg_ssc_set  ready
    u32 :31; /// [0x26]
    /* [0x27] */
    u32 reg_ssc_step                  :10; /// None
    u32 :22; /// [0x27]
    /* [0x28] */
    u32 reg_ssc_span                  :14; /// None
    u32 :1 ; /// [0x28]
    u32 reg_ssc_mode                  :1 ; /// None
    u32 :16; /// [0x28]
    /* [0x29] */
    u32 reg_ssc_testd                 :8 ; /// None
    u32 :24; /// [0x29]
    u32 :32; /// [0x2A]
    u32 :32; /// [0x2B]
    u32 :32; /// [0x2C]
    u32 :32; /// [0x2D]
    u32 :32; /// [0x2E]
    u32 :32; /// [0x2F]
    /* [0x30] */
    u32 reg_bbtop_rst0_ow             :1 ; /// reg_bigblue reset selection
    u32 reg_bbtop_rst1_ow             :1 ; /// reg_bigblue reset selection
    u32 reg_bbtop_rst2_ow             :1 ; /// reg_bigblue reset selection
    u32 reg_bbtop_rst3_ow             :1 ; /// reg_bigblue reset selection
    u32 reg_bbtop_rst4_ow             :1 ; /// reg_bigblue reset selection
    u32 :27; /// [0x30]
    /* [0x31] */
    u32 reg_pad_rst0_ow               :1 ; /// PAD reset selection
    u32 reg_pad_rst1_ow               :1 ; /// PAD reset selection
    u32 :30; /// [0x31]
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
    /* [0x40] */
    u32 reg_fnpll_rstz                :1 ; /// synpll reset, low active
    u32 :3 ; /// [0x40]
    u32 reg_fnpll_testd               :2 ; /// None
    u32 :2 ; /// [0x40]
    u32 reg_fnpll_dither_amp          :2 ; /// dither amplitude control
                                           /// 2'b00: no dither
                                           /// 2'b01: 1X (default)
                                           /// 2'b10: 2X
                                           /// 2'b11: 0.5X
    u32 :22; /// [0x40]
    /* [0x41] */
    u32 reg_fnpll_set_0               :16; /// N.f (5.27) setting of synthesizer divider ratio, 16 < N.f < 32 ,
                                           /// DIN[31] always=1'b1
    u32 :16; /// [0x41]
    u32 reg_fnpll_set_1               :16; /// @see reg_fnpll_set_0
    u32 :16; /// [0x42]
    /* [0x43] */
    u32 reg_fnpll_sld                 :1 ; /// write one 1 updaet reg_fnpll_set, must toggle after reg_fnpll_set ready
    u32 :31; /// [0x43]
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
    u32 :32; /// [0x7C]
    u32 :32; /// [0x7D]
    u32 :32; /// [0x7E]
    /* [0x7F] */
    u32 reg_efuse_passwd1             :8 ; /// Efuse password 1
} KePll_t;

extern volatile KePll_t * const g_ptKePll;

#endif /*__KERNEL_PLL_H__*/
