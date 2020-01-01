#ifndef __KERNEL_DMC_H__
#define __KERNEL_DMC_H__

/************************************************/
/* RIU DMC Bank                                 */
/************************************************/

typedef struct KeDmc_s
{
    /* [0x00] */
    u32 reg_init_miu                  :1 ; /// auto initial dram cycle
    u32 reg_cke                       :1 ; /// enable cke
    u32 reg_cs                        :1 ; /// dram chip select
    u32 reg_rstz                      :1 ; /// dram reset
    u32 reg_odt                       :1 ; /// turn on odt(only for ddr2/ddr3)
    u32 reg_auto_ref_off              :1 ; /// turn off auto refresh
    u32 :2 ; /// [0x00]
    u32 reg_single_cmd_en             :1 ; /// issue single cmd
    u32 reg_single_cmd                :3 ; /// single cmd = {rasz,casz,wez}
    u32 reg_dpd                       :1 ; /// enter deep power down mode(mobile dram only)
    u32 reg_self_refresh              :1 ; /// enter self refresh mode
    u32 reg_r_single_cmd_done         :1 ; /// single cmd done flag
    u32 reg_r_init_done               :1 ; /// auto initial dram cycle done flag
    u32 :16; /// [0x00]
    /* [0x01] */
    u32 reg_dram_type                 :2 ; /// 00 : sdr, 01 : ddr, 10 : ddr2, 11 : ddr3
    u32 reg_dram_bus                  :2 ; /// 00 : 16bit, 01 : 32bit, 10 : 64bit, 11 : reserved
    u32 reg_ba_size                   :2 ; /// 00 : 2ba, 01 : 4ba, 10 : 8ba, 11 : reserved
    u32 reg_ca_size                   :2 ; /// 00 : 8col, 01 : 9col, 10 : 10col, 11 : reserved
    u32 reg_data_ratio                :2 ; /// 00 : 1x, 01 : 2x, 10 : 4x, 11 : 8x
    u32 reg_data_swap                 :1 ; /// 0 : [15:0], 1 : [31:16]
    u32 reg_mobile_dram               :1 ; /// 0 : Normal DRAM ; 1 : Mobile DRAM
    u32 reg_cke_oenz                  :1 ; /// cke output enable
    u32 reg_dq_oenz                   :1 ; /// data output enable
    u32 reg_adr_oenz                  :1 ; /// address ouput enable
    u32 reg_cko_oenz                  :1 ; /// ck output enable
    u32 :16; /// [0x01]
    /* [0x02] */
    u32 reg_rd_timing                 :4 ; /// read back data delay timing
    u32 reg_rd_comb_data_sel          :1 ; /// rd_data combinational data output select. 1 : not sync ; 0 : sync
    u32 :3 ; /// [0x02]
    u32 reg_sdr_rx_bypass             :1 ; /// Receiving data =>  0:sync by fbclk ; 1 not sync by fbclk
    u32 reg_rd_comb_lat_sel           :1 ; /// rd_data combinational output select. 1 : not sync ; 0 : sync
    u32 reg_tx_iom_comb_sel           :1 ; /// pkg_mux combinational output select. 1 : no sync ; 0 : sync
    u32 :4 ; /// [0x02]
    u32 reg_rd_in_phase               :1 ; /// 0:positive edge ; 1:negative edge 
    u32 :16; /// [0x02]
    /* [0x03] */
    u32 reg_trefperiod                :8 ; /// refresh cycle period, unit 16 mclk
    u32 reg_tcke                      :3 ; /// dram tCKE timing
    u32 :1 ; /// [0x03]
    u32 reg_dynamic_cke               :1 ; /// 0:off ; 1:on
    u32 reg_dynamic_odt               :1 ; /// 0:off ; 1:on
    u32 reg_dynamic_csz               :1 ; /// 0:off ; 1:on
    u32 reg_dynamic_ck                :1 ; /// reserved in G2
    u32 :16; /// [0x03]
    /* [0x04] */
    u32 reg_trcd                      :4 ; /// dram tRCD tming counter
    u32 reg_trp                       :4 ; /// dram tRP timing counter
    u32 reg_tras                      :5 ; /// dram tRAS timing
    u32 :19; /// [0x04]
    /* [0x05] */
    u32 reg_trrd                      :4 ; /// dram tRRD timing
    u32 reg_trtp                      :4 ; /// dram tRTP timing
    u32 reg_trc                       :6 ; /// dram tRC timing
    u32 :18; /// [0x05]
    /* [0x06] */
    u32 reg_twl                       :4 ; /// dram tWL timing : write latency
    u32 reg_twr                       :4 ; /// dram tWR timing counter : write recovery time
    u32 reg_twtr                      :4 ; /// dram tWTR timing : write to read delay
    u32 reg_trtw                      :4 ; /// read to write delay
    u32 :16; /// [0x06]
    /* [0x07] */
    u32 reg_trfc                      :8 ; /// dram tRFC timing
    u32 :4 ; /// [0x07]
    u32 reg_tccd                      :3 ; /// dram tCCD timing
    u32 :17; /// [0x07]
    /* [0x08] */
    u32 reg_mr0                       :16; /// mode register 0
    u32 :16; /// [0x08]
    /* [0x09] */
    u32 reg_mr1                       :16; /// mode register 1
    u32 :16; /// [0x09]
    /* [0x0A] */
    u32 reg_mr2                       :16; /// mode register 2
    u32 :16; /// [0x0A]
    /* [0x0B] */
    u32 reg_mr3                       :16; /// mode register 3
    u32 :16; /// [0x0B]
    /* [0x0C] */
    u32 reg_mrx                       :16; /// single command mode register
    u32 :16; /// [0x0C]
    /* [0x0D] */
    u32 reg_deb_sel                   :16; /// for internal test only, select debug result
    u32 :16; /// [0x0D]
    /* [0x0E] */
    u32 reg_r_deb_bus                 :16; /// debug port
    u32 :16; /// [0x0E]
    /* [0x0F] */
    u32 reg_sw_rst_miu                :1 ; /// miu software reset
    u32 :3 ; /// [0x0F]
    u32 reg_sw_rst_g0                 :1 ; /// reserved
    u32 reg_sw_rst_g1                 :1 ; /// reserved
    u32 reg_sw_rst_g2                 :1 ; /// reserved
    u32 reg_sw_rst_g3                 :1 ; /// reserved
    u32 :24; /// [0x0F]
    /* [0x10] */
    u32 reg_reserved_10               :16; /// reserved
    u32 :16; /// [0x10]
    /* [0x11] */
    u32 reg_ddfspan                   :14; /// DDR clock Spread spectrum Period.
                                           /// DDR_SPREAD (DDR spread period) =
                                           /// (4* LOOP_DIV1*LOOP_DIV2*DDFSPAN )/ (DDR_FREQ*IN_DIV1*IN_DIV2).
                                           /// 
    u32 reg_ddft                      :2 ; /// DDR clock generator test mode.
                                           /// 00: Normal operation. (default)
                                           /// 01: Synthesizer truncate to integer divide.
                                           /// 10: Synthesizer bypass (equivalent to divide =1 ).
                                           /// 11: Reserved.
    u32 :16; /// [0x11]
    /* [0x12] */
    u32 reg_ddfstep                   :10; /// DDR Clock Spread Spectrum Step.
                                           /// DDR_SWB (DDR spread bandwidth)
                                           /// = DDR_FREQ* (2*DDFSPAN*DDFSTEP) / (DDFSET*1024).
                                           /// 
    u32 reg_ddrpll_porst              :1 ; /// DDR PLL Power On Reset.
    u32 reg_ddrpll_reset              :1 ; /// PLL reset signal. APLL_RESET =1 -> Reset PLL DFF
    u32 reg_ddrpll_input_div_first    :2 ; /// PLL first stage of input divider.
                                           /// 2'b00 -> div1, 2'b01 -> div2, 2'b10 -> div4, 2'b11-> div8
    u32 reg_ddrpll_loop_div_first     :2 ; /// PLL first stage of loop divider.
                                           /// 2'b00 -> div1, 2'b01 -> div2, 2'b10 -> div4, 2'b11-> div8
    u32 :16; /// [0x12]
    /* [0x13] */
    u32 reg_ddrpll_input_div_second   :8 ; /// PLL second stage of input divider.
                                           /// 2'h00 ->div1, 2'h01 -> div1, 2'h02 ->div2, 2'h03 ->div3, 2'h04 ->div4
    u32 reg_ddrpll_loop_div_second    :8 ; /// PLL second stage of loop divider.
                                           /// 2'h00 ->div1, 2'h01 -> div1, 2'h02 ->div2, 2'h03 ->div3, 2'h04 ->div4
    u32 :16; /// [0x13]
    /* [0x14] */
    u32 reg_reserved_14               :16; /// reserved
    u32 :16; /// [0x14]
    /* [0x15] */
    u32 reg_apll_pd12_pdiv            :9 ; /// Power down PLL level shift. For power saving concern, when PLL is locked and output clock phase is selected,
                                           /// we can power down the level shifter which phase is not selected. APLL_PD12_PDIV =1 -> power down level shift
    u32 reg_ddr_ssc_mode              :1 ; /// clock spread spectrum mode
    u32 reg_apll_clkin_sel            :1 ; /// Select PLL reference clock from synthesizer or from MPLL clock output.
    u32 :1 ; /// [0x15]
    u32 reg_apll_ictrl                :3 ; /// PLL charge pump current control. The charge pump current influence bandwidth and stability of PLL.
    u32 reg_ddr_ssc_en                :1 ; /// clock spread spectrum enable
    u32 :16; /// [0x15]
    u32 :32; /// [0x16]
    /* [0x17] */
    u32 :4 ; /// [0x17]
    u32 reg_syn_deb_bus_sel           :2 ; /// syn_deb_bus select  00 : SSC_OFFSET ;  01 : Other synthesizer signals ; 10 : {APLL_TEST_CLK_IN, APLL_TEST_CLK_OUT, 22'h0};
    u32 :5 ; /// [0x17]
    u32 reg_ddrpll_pd                 :1 ; /// Power down PLL. APLL_PD =1 -> power down PLL
    u32 reg_trig_lvl                  :4 ; /// trigger level, default 7
    u32 :16; /// [0x17]
    /* [0x18] */
    u32 reg_clkph_clkpad              :4 ; /// Adjust clock phase for PAD_MCLK and PAD_MCLKZ to DRAM
    u32 :28; /// [0x18]
    /* [0x19] */
    u32 reg_clkph_mclk                :4 ; /// Adjust clock phase for digital MIU_TOP
    u32 reg_clkph_fbclk               :4 ; /// Adjust internal clock phase to latch SDR DQ[31:0] receiving data
    u32 :24; /// [0x19]
    /* [0x1A] */
    u32 :14; /// [0x1A]
    u32 reg_ana_bist_en               :1 ; /// internal DRAM test signal
    u32 :17; /// [0x1A]
    u32 :32; /// [0x1B]
    u32 :32; /// [0x1C]
    /* [0x1D] */
    u32 reg_miu_stall_en              :1 ; /// miu stall signal
    u32 reg_apll_stop_mclk            :1 ; /// Set to 1 to force APLL_MCLK_DIG=0. This is used to prevent glitch if APLL_MCLK_DIG frequency is changed.
    u32 reg_reserved_1d               :11; /// reserved
    u32 reg_r_miu_busy                :1 ; /// read only : check miu is busy or not (including fifo2)  
    u32 reg_r_ctrl_busy               :1 ; /// read only : check miu is busy or not
    u32 reg_r_switch_clk_rdy          :1 ; /// read only
    u32 :16; /// [0x1D]
    /* [0x1E] */
    u32 reg_apll_fastload             :6 ; /// [1:0] = 00, APLL_CLK1X = 100MHz ~ 200MHz (1 ddr data eye 9 phase)
                                           /// [1:0] = 01, APLL_CLK1X = 50MHz ~ 100MHz (1 ddr data eye 9 phase)
                                           /// [1:0] = 10, APLL_CLK1X = 25MHz ~ 50MHz (1 ddr data eye 9 phase)
                                           /// [1:0] = 11, APLL_CLK1X = 25MHz ~ 50MHz (1 ddr data eye 9 phase)
                                           /// [3:2] ->01, APLL_CLK1X = 25MHz ~ 50MHz  for ultra low frequency enable (1 ddr data eye 8 phase, used in DFT mode)
                                           /// [3:2] ->11, APLL_CLK1X = 12.5MHz ~ 25MHz  for ultra low frequency enable (1 ddr data eye 8 phase, used in DFT mode)
                                           /// [7:4]: Not used.
    u32 reg_ac_ratio_sel              :2 ; /// select clk frequency ratio
    u32 :24; /// [0x1E]
    /* [0x1F] */
    u32 :12; /// [0x1F]
    u32 reg_dqsm_rd_timing            :4 ; /// dqsm rd timing select
    u32 :16; /// [0x1F]
    /* [0x20] */
    u32 reg_ddrat_0                   :16; /// PLL testmode register:
                                           /// [7],[4:0]: used for test mode control.
     
                                           /// [6],[9],[13:14]: used to set clock phase for APLL_TEST_CLK_OUT
                                           /// [12:10],[16]: used for APLL_ATOP test feature
                                           /// [15]: testclk select for loop divider
                                           /// [17]: DFT clock select for low frequency clock divider and phase generator
                                           /// [18]: FF reset for low frequency clock divider and phase generator
                                           /// [19]: DFT clock select for input clock source
                                           /// [20]: FF reset for APLL_MCLK_DIG clock divider
    u32 :16; /// [0x20]
    u32 reg_ddrat_1                   :5 ; /// @see reg_ddrat_0
    u32 :27; /// [0x21]
    /* [0x22] */
    u32 reg_ddfset_0                  :16; /// PLL testmode register:
                                           /// [7],[4:0]: used for test mode control.
                                           /// [5]: used to enable resamping source clock with APLL_CLK200
                                           /// [6],[9],[13:14]: used to set clock phase for APLL_TEST_CLK_OUT
                                           /// [12:10],[16]: used for APLL_ATOP test feature
                                           /// [15]: testclk select for loop divider
                                           /// [17]: DFT clock select for low frequency clock divider and phase generator
                                           /// [18]: FF reset for low frequency clock divider and phase generator
                                           /// [19]: DFT clock select for input clock source
                                           /// [20]: FF reset for APLL_MCLK_DIG clock divider
    u32 :16; /// [0x22]
    u32 reg_ddfset_1                  :8 ; /// @see reg_ddfset_0
    u32 :24; /// [0x23]
    /* [0x24] */
    u32 :12; /// [0x24]
    u32 reg_gpio_oenz                 :1 ; /// gpio oenz ctrl
    u32 reg_sel_gpio                  :1 ; /// gpio path select
    u32 reg_apll_fastload_7           :2 ; /// reserved
    u32 :16; /// [0x24]
    u32 :32; /// [0x25]
    /* [0x26] */
    u32 :14; /// [0x26]
    u32 reg_r_ddrpll_ssc_off          :1 ; /// synthesizer SSC OFFSET vaule
    u32 reg_r_ddrpll_lock             :1 ; /// when PLL is lock, APLL_LOCK will be stable at high.
    u32 :16; /// [0x26]
    /* [0x27] */
    u32 :14; /// [0x27]
    u32 reg_reset_gpiod               :1 ; /// reset GPIO
    u32 reg_set_gpiod                 :1 ; /// set GPIO
    u32 :16; /// [0x27]
    /* [0x28] */
    u32 reg_sel_gpio_dmy_0            :16; /// dummy gpio select
    u32 :16; /// [0x28]
    u32 reg_sel_gpio_dmy_1            :4 ; /// @see reg_sel_gpio_dmy_0
    u32 reg_gpio_oenz_dmy_0           :12; /// dummy gpio oenz
    u32 :16; /// [0x29]
    u32 reg_gpio_oenz_dmy_1           :8 ; /// @see reg_gpio_oenz_dmy_0
    u32 reg_set_gpiod_dmy_0           :8 ; /// dummy gpio set
    u32 :16; /// [0x2A]
    u32 reg_set_gpiod_dmy_1           :12; /// @see reg_set_gpiod_dmy_0
    u32 reg_reset_gpiod_dmy_0         :4 ; /// dummy gpio reset
    u32 :16; /// [0x2B]
    u32 reg_reset_gpiod_dmy_1         :16; /// @see reg_reset_gpiod_dmy_0
    u32 :16; /// [0x2C]
    u32 :32; /// [0x2D]
    u32 :32; /// [0x2E]
    u32 :32; /// [0x2F]
    u32 :32; /// [0x30]
    u32 :32; /// [0x31]
    u32 :32; /// [0x32]
    u32 :32; /// [0x33]
    /* [0x34] */
    u32 reg_reserved_dig_0            :16; /// reserved register miu_dig
    u32 :16; /// [0x34]
    u32 reg_reserved_dig_1            :16; /// @see reg_reserved_dig_0
    u32 :16; /// [0x34]
    u32 reg_reserved_dig_2            :16; /// @see reg_reserved_dig_0
    u32 :16; /// [0x34]
    u32 reg_reserved_dig_3            :16; /// @see reg_reserved_dig_0
    u32 :16; /// [0x34]
    u32 reg_reserved_dig_4            :16; /// @see reg_reserved_dig_0
    u32 :16; /// [0x38]
    /* [0x39] */
    u32 reg_reserved_atop_0           :16; /// reserved register miu_atop
    u32 :16; /// [0x39]
    u32 reg_reserved_atop_1           :16; /// @see reg_reserved_atop_0
    u32 :16; /// [0x39]
    u32 reg_reserved_atop_2           :16; /// @see reg_reserved_atop_0
    u32 :16; /// [0x39]
    u32 reg_reserved_atop_3           :16; /// @see reg_reserved_atop_0
    u32 :16; /// [0x39]
    u32 reg_reserved_atop_4           :16; /// @see reg_reserved_atop_0
    u32 :16; /// [0x3D]
    u32 :32; /// [0x3E]
    u32 :32; /// [0x3F]
    /* [0x40] */
    u32 reg_pst_round_robin           :1 ; /// set pst_arb round robin
    u32 reg_pst_set_priority          :1 ; /// set pst_arb group fix priority
    u32 reg_pst_rq_limit_en           :1 ; /// limit enable
    u32 :1 ; /// [0x40]
    u32 reg_pst_rq_timeout_en         :1 ; /// time out enable
    u32 :3 ; /// [0x40]
    u32 reg_pst_rq_cnt0_ctrl_en       :1 ; /// flow control enable
    u32 reg_pst_rq_cnt1_ctrl_en       :1 ; /// flow control enable
    u32 :5 ; /// [0x40]
    u32 reg_pst_rq_arbiter_skip_on    :1 ; /// arbiter skip on
    u32 :16; /// [0x40]
    /* [0x41] */
    u32 reg_pst_rq_member_max         :8 ; /// limit pst arbiter client request number
    u32 :24; /// [0x41]
    /* [0x42] */
    u32 reg_pst_rq_timeout            :16; /// limit pst arbiter timeout number
    u32 :16; /// [0x42]
    /* [0x43] */
    u32 reg_pst_rq_mask               :16; /// limit pst arbiter client request mask
    u32 :16; /// [0x43]
    /* [0x44] */
    u32 reg_pst_rq_hpmask             :16; /// limit pst_arbiter client high priority request mask
    u32 :16; /// [0x44]
    /* [0x45] */
    u32 reg_pst_rq0_priority          :4 ; /// limit pst_arb client 0 fix priority number
    u32 reg_pst_rq1_priority          :4 ; /// limit pst_arb client 1 fix priority number
    u32 reg_pst_rq2_priority          :4 ; /// limit pst_arb client 2 fix priority number
    u32 reg_pst_rq3_priority          :4 ; /// limit pst_arb client 3 fix priority number
    u32 :16; /// [0x45]
    /* [0x46] */
    u32 reg_pst_rq4_priority          :4 ; /// limit pst_arb client 4 fix priority number
    u32 reg_pst_rq5_priority          :4 ; /// limit pst_arb client 5 fix priority number
    u32 reg_pst_rq6_priority          :4 ; /// limit pst_arb client 6 fix priority number
    u32 reg_pst_rq7_priority          :4 ; /// limit pst_arb client 7 fix priority number
    u32 :16; /// [0x46]
    u32 :32; /// [0x47]
    u32 :32; /// [0x48]
    u32 :32; /// [0x49]
    /* [0x4A] */
    u32 reg_pst_rq_cnt0_id0           :3 ; /// ID0 for group0 flow control counter0
    u32 :1 ; /// [0x4A]
    u32 reg_pst_rq_cnt0_id1           :3 ; /// ID1 for group0 flow control counter0
    u32 :1 ; /// [0x4A]
    u32 reg_pst_rq_cnt0_period        :8 ; /// pst_arb group flow control counter0
    u32 :16; /// [0x4A]
    /* [0x4B] */
    u32 reg_pst_rq_cnt1_id0           :3 ; /// ID0 for group0 flow control counter1
    u32 :1 ; /// [0x4B]
    u32 reg_pst_rq_cnt1_id1           :3 ; /// ID1 for group0 flow control counter1
    u32 :1 ; /// [0x4B]
    u32 reg_pst_rq_cnt1_period        :8 ; /// pst_arb group flow control counter1
    u32 :16; /// [0x4B]
    /* [0x4C] */
    u32 reg_pst_rq_cut_in_en          :16; /// pst_arb cut_in enavle
    u32 :16; /// [0x4C]
    /* [0x4D] */
    u32 reg_pst_rq_limit_mask         :16; /// limit mask
    u32 :16; /// [0x4D]
    u32 :32; /// [0x4E]
    u32 :32; /// [0x4F]
    /* [0x50] */
    u32 :4 ; /// [0x50]
    u32 reg_fix_sdr_tx_dly_sel        :3 ; /// SDR TX clock delay control
    u32 reg_fix_sdr_tx_clk_inv        :1 ; /// SDR TX clock invert control
    u32 reg_fix_sdr_rx_dly_sel        :3 ; /// SDR RX clock delay control
    u32 reg_fix_sdr_rx_clk_inv        :1 ; /// SDR RX clock invert control
    u32 :2 ; /// [0x50]
    u32 reg_pll_tx_clk_sel            :1 ; /// SDR TX cko source select (from pll)
    u32 :17; /// [0x50]
    /* [0x51] */
    u32 :8 ; /// [0x51]
    u32 reg_apll_lockdiv              :4 ; /// VCO will divide by this 4-bits control divider and compare it to 48MHz to determine whether PLL is lock or not.
                                           /// For example, when the clock rate is 200MHz, VCO frequency is 400MHz, and we set APLL_LOCKDIV = 4'b1000 to divide 8, then the lock detector will compare 400MHz/8=50MHz and 48MHz to see if the frequency difference is in the +/-15%. if it is locked, the APLL_LOCK=1
    u32 :20; /// [0x51]
    /* [0x52] */
    u32 reg_loopback_dig_en           :1 ; /// LOOPBACK enable
    u32 :12; /// [0x52]
    u32 reg_debug_gpio42tx            :1 ; /// reserved
    u32 reg_debug_sel                 :2 ; /// reserved
    u32 :16; /// [0x52]
    /* [0x53] */
    u32 reg_sdr_fb_clk_sel            :2 ; /// SDR feedback select
    u32 :30; /// [0x53]
    /* [0x54] */
    u32 reg_apll_en_clk2x             :1 ; /// apll clk 2x enable control
    u32 reg_mempll_switch             :1 ; /// 0 : select 1X ; 1:select 2X
    u32 :30; /// [0x54]
    /* [0x55] */
    u32 reg_bypass_cke_sel            :1 ; /// reserved
    u32 reg_bypass_cke                :1 ; /// reserved
    u32 reg_bypass_cke_oenz           :1 ; /// reserved
    u32 :1 ; /// [0x55]
    u32 reg_client_sel_0              :4 ; /// debug use
    u32 reg_client_sel_1              :4 ; /// debug use
    u32 reg_client_sel_2              :4 ; /// debug use
    u32 :16; /// [0x55]
    /* [0x56] */
    u32 reg_mempll_pd                 :1 ; /// pll power down
    u32 :31; /// [0x56]
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
    /* [0x62] */
    u32 reg_trts                      :3 ; /// dram tRTS timing
    u32 reg_trts_dis                  :1 ; /// disable tRTS timing check
    u32 :4 ; /// [0x62]
    u32 reg_inst_pdn_pra              :1 ; /// insert power down precharge all
    u32 :5 ; /// [0x62]
    u32 reg_rq_order_ctrl_ratio       :2 ; /// arbiter order control ratio
    u32 :16; /// [0x62]
    /* [0x63] */
    u32 :8 ; /// [0x63]
    u32 reg_arb_busy_en               :1 ; /// consider arbiter busy for 2cke function
    u32 :3 ; /// [0x63]
    u32 reg_2cke_sel                  :1 ; /// enable 2cke
    u32 :19; /// [0x63]
    /* [0x64] */
    u32 reg_rq_order_ctrl_en_0        :16; /// arbiter order control enable
    u32 :16; /// [0x64]
    u32 reg_rq_order_ctrl_en_1        :16; /// @see reg_rq_order_ctrl_en_0
    u32 :16; /// [0x64]
    u32 reg_rq_order_ctrl_en_2        :16; /// @see reg_rq_order_ctrl_en_0
    u32 :16; /// [0x64]
    u32 reg_rq_order_ctrl_en_3        :16; /// @see reg_rq_order_ctrl_en_0
    u32 :16; /// [0x67]
    /* [0x68] */
    u32 reg_multi_act_ctrl_id1        :6 ; /// multiple bank active ID1
    u32 :2 ; /// [0x68]
    u32 reg_multi_act_ctrl_id2        :6 ; /// multiple bank active ID2
    u32 :18; /// [0x68]
    /* [0x69] */
    u32 reg_multi_act_ctrl_id3        :6 ; /// multiple bank active ID3
    u32 :6 ; /// [0x69]
    u32 reg_multi_act_ctrl_id1_en     :1 ; /// multiple bank active ID1 enable
    u32 reg_multi_act_ctrl_id2_en     :1 ; /// multiple bank active ID2 enable
    u32 reg_multi_act_ctrl_id3_en     :1 ; /// multiple bank active ID3 enable
    u32 reg_multi_act_ctrl_all_en     :1 ; /// multiple bank active all enable
    u32 :16; /// [0x69]
    u32 :32; /// [0x6A]
    u32 :32; /// [0x6B]
    u32 :32; /// [0x6C]
    u32 :32; /// [0x6D]
    u32 :32; /// [0x6E]
    /* [0x6F] */
    u32 reg_miu_div_2top              :5 ; /// None
    u32 :27; /// [0x6F]
    /* [0x70] */
    u32 reg_test_en                   :1 ; /// miu self test enable
    u32 reg_test_mode                 :2 ; /// miu self test mode
                                           /// 00 : address mode
                                           /// 01 : from reg_test_data
                                           /// 10 : shift data
                                           /// 11 : address mode + data toggle
    u32 reg_inv_data                  :1 ; /// invers test data
    u32 reg_test_loop                 :1 ; /// loop mode
    u32 reg_force_out                 :1 ; /// force write data to reg_test_data
    u32 reg_force_in                  :1 ; /// force read data to reg_test_data
    u32 reg_addr_toggle_mode          :1 ; /// address toggle mode test
    u32 reg_read_only                 :1 ; /// only issue read command
    u32 reg_write_only                :1 ; /// only issue write command
    u32 reg_test_byte                 :2 ; /// read back data byte switch
    u32 :1 ; /// [0x70]
    u32 reg_test_flag                 :1 ; /// test fail indicator
    u32 reg_test_fail                 :1 ; /// test fail indicator
    u32 reg_test_finish               :1 ; /// test finish indicator
    u32 :16; /// [0x70]
    /* [0x71] */
    u32 reg_test_base                 :16; /// test base address
    u32 :16; /// [0x71]
    /* [0x72] */
    u32 reg_test_length_l             :16; /// test length
    u32 :16; /// [0x72]
    u32 reg_test_length_h             :12; /// @see reg_test_length_0
    u32 reg_addr_ratio                :4 ; /// test length shift ratio
    u32 :16; /// [0x73]
    /* [0x74] */
    u32 reg_test_data                 :16; /// test data
    u32 :16; /// [0x74]
    /* [0x75] */
    u32 reg_test_status               :16; /// for internal test only
    u32 :16; /// [0x75]
    /* [0x76] */
    u32 reg_test_byte_fail            :16; /// for internal test only
    u32 :16; /// [0x76]
    /* [0x77] */
    u32 reg_test_bit_fail             :16; /// for internal test only
    u32 :16; /// [0x77]
    u32 :32; /// [0x78]
    u32 :32; /// [0x79]
    /* [0x7A] */
    u32 reg_test_base_31to16          :16; /// test base address
    u32 :16; /// [0x7A]
    /* [0x7B] */
    u32 reg_switch_last_en            :1 ; /// Switch to cmd client when the end of arbiter burst transmitting
    u32 :31; /// [0x7B]
    u32 :32; /// [0x7C]
    /* [0x7D] */
    u32 reg_test_mask                 :8 ; /// test data mask
    u32 :24; /// [0x7D]
    /* [0x7E] */
    u32 reg_idle_ctrl                 :10; /// random test idle parameter
    u32 :5 ; /// [0x7E]
    u32 reg_idle_random_en            :1 ; /// random test idle enable
    u32 :16; /// [0x7E]
    /* [0x7F] */
    u32 reg_busy_ctrl                 :10; /// random test busy parameter
    u32 :4 ; /// [0x7F]
    u32 reg_2cs_ddr32                 :1 ; /// 2cs type select ; 1: check addr[25]  ; 0 : check addr[24]
    u32 reg_busy_random_en            :1 ; /// random test busy enable
} KeDmc_t;

/// the value is matched to register setting
typedef enum
{
    E_DMC_TEST_MODE_ADDR_TOGGLE    = 0,
    E_DMC_TEST_MODE_TEST_DATA      = 1,
    E_DMC_TEST_MODE_SHIFT_DATA     = 2,
    E_DMC_TEST_MODE_BOTH_TOGGLE    = 3,
} eDmcTestMode;


extern volatile KeDmc_t * const g_ptKeDmc;

#endif /*__KERNEL_DMC_H__*/
