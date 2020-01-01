#ifndef __KERNEL_PMU_H__
#define __KERNEL_PMU_H__

/************************************************/
/* PMU Register Bank                       */
/************************************************/

typedef struct KePmu_s
{
    /* [0x00] */
    u32 reg_ldovrf1_pg                :1 ; /// LDO power good
    u32 reg_ldovrf2_pg                :1 ; /// LDO power good
    u32 reg_ldovsim1_pg               :1 ; /// LDO power good
    u32 reg_ldovsim2_pg               :1 ; /// LDO power good
    u32 reg_ldovmem_pg                :1 ; /// LDO power good
    u32 reg_ldovlcm_pg                :1 ; /// LDO power good
    u32 reg_ldovio_pg                 :1 ; /// LDO power good
    u32 reg_ldovper1_pg               :1 ; /// LDO power good
    u32 reg_ldovper2_pg               :1 ; /// LDO power good
    u32 reg_ldovper3_pg               :1 ; /// LDO power good
    u32 reg_ldovper4_pg               :1 ; /// LDO power good
    u32 reg_ldoaud25_pg               :1 ; /// LDO power good
    u32 reg_fm_rfp_pg                 :1 ; /// FM LDO power good
    u32 reg_fm_ifp_pg                 :1 ; /// FM LDO power good
    u32 reg_ldorf_pg                  :1 ; /// RF LDO power good
    u32 reg_ldo_err_int               :1 ; /// ldo vrf1 vrf2 vsim1 vsim2 vmem vlcm vio vper1/2/3 has error
    u32 :16; /// [0x00]
    /* [0x01] */
    u32 reg_ldovmem_a_en              :1 ; /// enable ldo_vmem in active mode, default = 0.
    u32 reg_ldovmem_a_lq              :1 ; /// enable ldo_vmem at LQ mode
    u32 reg_ldovmem_a_vset              :2 ; /// select output voltage level,
                                           /// when PAD_VMSEL =0 
                                           /// [00] : 1.85V(default)  [01] : 1.9V.  [10] : 1.8V.  [11] :1.75V.
                                           /// when PAD_VMSEL =1
                                           /// [00] : 2.8V(default)  [01] : 2.9V.  [10] : 2.7V.  [11] :2.6V.
    u32 reg_ldovmem_s_en              :1 ; /// enable ldo_vmem in standby mode, default = 0.
    u32 reg_ldovmem_s_lq              :1 ; /// enable ldo_vmem at LQ mode
    u32 reg_ldovmem_d_time            :2 ; /// standby mode turn-off delay time
                                           /// 00: 0us
                                           /// 01: 250us
                                           /// 10: 500us
                                           /// 11: 1ms
    u32 reg_ldovlcm_a_en              :1 ; /// enable ldo_lcm in active mode, default = 0.  //big5 remove LDO MEM
    u32 reg_ldovlcm_a_lq              :1 ; /// enable ldo_lcm at LQ mode
    u32 reg_ldovlcm_a_vset              :2 ; /// select output voltage level, // default from efuse[23:22], 
                                           /// can be over write by set reg_level_ov_en=1 ,  
                                           /// [00] :2.8V(default)
                                           /// [01] :2.9V.
                                           /// [10] :1.8V.
                                           /// [11] :1.9V.
    u32 reg_ldovlcm_s_en              :1 ; /// enable ldo_lcm in standby mode, default = 0.
    u32 reg_ldovlcm_s_lq              :1 ; /// enable ldo_vlcm at LQ mode
    u32 reg_ldovlcm_d_time            :2 ; /// standby mode turn-off delay time
                                           /// 00: 0us
                                           /// 01: 250us
                                           /// 10: 500us
                                           /// 11: 1ms
    u32 :16; /// [0x01]
    /* [0x02] */
    u32 reg_ldovio1_a_en               :1 ; /// enable ldo_vio in active mode, default = 1.
    u32 reg_ldovio1_a_lq               :1 ; /// enable ldo_vio at LQ mode
    u32 reg_ldovio1_a_vset               :2 ; /// select output voltage level, // default from efuse[17:16], 
                                           /// can be over write by set reg_level_ov_en=1 , 
                                           /// [00] :2.8V(default)
                                           /// [01] :2.9V.
                                           /// [10] :1.8V.
                                           /// [11] :1.9V.
    u32 reg_ldovio1_s_en               :1 ; /// enable ldo_vio in standby mode, default = 1.
    u32 reg_ldovio1_s_lq               :1 ; /// enable ldo_vio at LQ mode
    u32 reg_ldovio1_d_time             :2 ; /// standby mode turn-off delay time
                                           /// 00: 0us
                                           /// 01: 250us
                                           /// 10: 500us
                                           /// 11: 1ms
    u32 :24; /// [0x02]
    /* [0x03] */
    u32 reg_ldovsim1_a_en             :1 ; /// enable ldo_vsim1 in active mode, default = 1.
    u32 reg_ldovsim1_a_lq             :1 ; /// enable ldo_vsim1 at LQ mode
    u32 reg_ldovsim1_a_vset             :2 ; /// select output voltage level,
                                           /// [00] : 1.8V(default)
                                           /// [01] : 1.9V.
                                           /// [10] : 2.9V.
                                           /// [11] : 3.0V.
    u32 reg_ldovsim1_s_en             :1 ; /// enable ldo_vsim1 in standby mode, default = 1.
    u32 reg_ldovsim1_s_lq             :1 ; /// enable ldo_vsim1 at LQ mode
    u32 reg_ldovsim1_d_time           :2 ; /// standby mode turn-off delay time
                                           /// 00: 0us
                                           /// 01: 250us
                                           /// 10: 500us
                                           /// 11: 1ms
    u32 reg_ldovsim1_sel              :1 ; /// ldo sim1 enable select 
                                           /// 0: by reg_ldovsim1_a_en( active) ; 
                                           ///           reg_ldovsim1_s_en(standby) 
                                           /// 1: by dbb fsm control
    u32 :23; /// [0x03]
    /* [0x04] */
    u32 reg_ldovsim2_a_en             :1 ; /// enable ldo_vsim2 in active mode, default = 1.
    u32 reg_ldovsim2_a_lq             :1 ; /// enable ldo_vsim2 at LQ mode
    u32 reg_ldovsim2_a_vset           :2 ; /// select output voltage level,
                                           /// [00] : 1.8V(default)
                                           /// [01] : 1.9V.
                                           /// [10] : 2.9V.
                                           /// [11] : 3.0V.
    u32 reg_ldovsim2_s_en             :1 ; /// enable ldo_vsim2 in standby mode, 
    u32 reg_ldovsim2_s_lq             :1 ; /// enable ldo_vsim2 at LQ mode; standby mode
    u32 reg_ldovsim2_d_time           :2 ; /// standby mode turn-off delay time
                                           /// 00: 0us
                                           /// 01: 250us
                                           /// 10: 500us
                                           /// 11: 1ms
    u32 reg_ldovsim2_sel              :1 ; /// ldo sim1 enable select 
                                           /// 0: by reg_ldovsim2_a_en( active) ; 
                                           ///           reg_ldovsim2_s_en(standby) 
                                           /// 1: by dbb fsm control
    u32 :23; /// [0x04]
    /* [0x05] */
    u32 reg_ldovrf1_err_en            :1 ; /// enable LDO power good  error interrupt
    u32 reg_ldovrf2_err_en            :1 ; /// enable LDO power good  error interrupt
    u32 reg_ldovsim1_err_en           :1 ; /// enable LDO power good  error interrupt
    u32 reg_ldovsim2_err_en           :1 ; /// enable LDO power good  error interrupt
    u32 reg_ldovmem_err_en            :1 ; /// enable LDO power good  error interrupt
    u32 reg_ldovlcm_err_en            :1 ; /// enable LDO power good  error interrupt
    u32 reg_ldovio_err_en             :1 ; /// enable LDO power good  error interrupt
    u32 reg_ldovper1_err_en           :1 ; /// enable LDO power good  error interrupt
    u32 reg_ldovper2_err_en           :1 ; /// enable LDO power good  error interrupt
    u32 reg_ldovper3_err_en           :1 ; /// enable LDO power good  error interrupt
    u32 reg_ldovper4_err_en           :1 ; /// enable LDO power good  error interrupt
    u32 :21; /// [0x05]
    /* [0x06] */
    u32 reg_batdet_debounce           :3 ; /// battery detecttion debounce time
                                           /// 000: 0.1us    100: 5us
                                           /// 001: 0.6us    101: 10us
                                           /// 010: 1.2us       110: 20us
                                           /// 011: 2.4us       111: 40us
    u32 reg_en_batdet                 :1 ; /// enable battery detecttion
                                           /// 0: disable 1: enable
    u32 reg_test_batdet               :2 ; /// battery detecttion test
    u32 reg_batdet                    :1 ; /// battery detecttion flag
    u32 reg_nobat_int                 :1 ; /// on battery detecttion interrupt
    u32 :24; /// [0x06]
    /* [0x07] */
    u32 reg_en_i_tst                  :5 ; /// enable test current out //bravo no use
    u32 :27; /// [0x07]
    /* [0x08] */
    u32 reg_vref_tst                  :1 ; /// VREF test enable
                                           /// 0: disable (default)
                                           /// 1: enable
    u32 reg_en_otp                    :1 ; /// reference gen OTP enable control
                                           /// 0:OFF  1:ON
    u32 reg_otp_vth                   :2 ; /// reference gen OTP VTH selection
                                           /// 00:428mV, 150degC
                                           /// 01:448mV, 140degC
                                           /// 10:468mV, 130degC
                                           /// 11:408mV, 160degC
    u32 reg_ibias_tune                :2 ; /// reference gen bias current tuning
                                           /// 00:0%  01:-25%  10:-25%  11:+25% //bravo no use
    u32 reg_en_verfotp_tst            :1 ; /// VREF of OTP test enable
    u32 reg_ref_otp                   :1 ; /// refgen OTP flag
    u32 reg_temp_measure              :1 ; /// enable the test bench for OTP
    u32 reg_test_i                    :5 ; /// Register to mux test current to AUX
                                           /// enable test current out
                                           /// [9]: IBBG_TST_POUT2P1U
                                           /// [10]: IREF_TST_POUT2U
                                           /// [11]: IREF_TST_NOUT2U
                                           /// [12]: IB_TST_POUT2U
                                           /// [13]: IB_TST_NOUT2U
    u32 :18; /// [0x08]
    /* [0x09] */
    u32 reg_refgen_bias               :2 ; /// fine-tuning of bias current in refgen. //no use
                                           /// 00: bias current ¡Ñ 1
                                           /// 01: bias current ¡Ñ 0.8
                                           /// 10: bias current ¡Ñ 1.33
                                           /// 11: bias current ¡Ñ 1
    u32 reg_en_iref2u_aud_rf          :1 ; /// 2u reference current for audio & rf enable. High active//no use
    u32 :1 ; /// [0x09]
    u32 reg_ldo_rf_lq                 :1 ; /// set rf ldo LQ mode
    u32 reg_ldo_adu_lq                :1 ; /// set audio ldo LQ mode
    u32 :26; /// [0x09]
    /* [0x0A] */
    u32 reg_efusetrim_bit             :6 ; /// bandgap trimming bits
                                           /// big3 read efuse values from asura and load at this register
    u32 reg_autotrim_bit              :6 ; /// auto trimming bits result
                                           /// intial value : 6'b100000
    u32 reg_trimbit_sel               :1 ; /// trimming bit selection
                                           /// 0: reg_autotrim_bit
                                           /// 1: reg_efusetrim_bit
    u32 reg_en_reftrim                :1 ; /// bandgap trimming enable
    u32 reg_reftrim_out               :1 ; /// bandgap trimming out bit
    u32 :17; /// [0x0A]
    /* [0x0B] */
    u32 reg_pwrhld_passwd             :8 ; /// power hold passwd register : cpu need to set this passwd when the first power on 
                                           /// 8'h5A  : active to off
                                           /// 8'hA5 : power hold to active
    u32 reg_pmu_active_flag           :1 ; /// pmu active flag
    u32 reg_pmu_standby_flag          :1 ; /// pmu standby flag
    u32 :22; /// [0x0B]
    /* [0x0C] */
    u32 reg_wait_time                 :16; /// set wait time for exit sleep mode; count by 32k 
                                           /// default 120us = 4x30u
    u32 :16; /// [0x0C]
    /* [0x0D] */
    u32 reg_mclk_sel_passwd           :8 ; /// mclk select pass word
                                           /// != 8'hA5  : sel from reg_mclk_det_flag
                                           /// == 8'hA5 : sel from reg_mclk_26m
    u32 reg_mclk_26m                  :1 ; /// 0: mclk is 13 Mhz
                                           /// 1: mclk is 26 Mhz
    u32 reg_mclk_det_flag             :1 ; /// 0: mclk is 13 Mhz
                                           /// 1: mclk is 26 Mhz
    u32 :22; /// [0x0D]
    /* [0x0E] */
    u32 reg_pmu_state                 :16; /// pmu  fsm state
    u32 :16; /// [0x0E]
    /* [0x0F] */
    u32 reg_dbbus_sel                 :4 ; /// debug bus selection
    u32 :28; /// [0x0F]
    /* [0x10] */
    u32 reg_en_key0                   :1 ; /// enable KEYPAD0 generation
                                           /// 0:disable 1: enable
    u32 reg_sel_key0                  :1 ; /// KEYPAD0control selection 
                                           /// 0:control by HW PWM
                                           /// 1: control by reg_sw_key0
    u32 reg_sw_key0                   :1 ; /// control KEYPAD0 PWM 
                                           /// 0: send low to KEYPAD0 PWM pin 
                                           /// 1: send high to KEYPAD0 PWM pin
    u32 :5 ; /// [0x10]
    u32 reg_ratio_key0                :8 ; /// set the PWM output high ratio relative to reg_period_key0
                                           /// if ratio value >= period value ,PWM output is 1 
                                           /// 00000000: PWM output 1
                                           /// 00000001: PWM output is high for 1 Fkey0 clock
                                           /// 00000010: PWM output is high for 2 Fkey0 clock
                                           /// ...............
                                           /// 11111111: PWM output is high for 255 Fkey0 clock
    u32 :16; /// [0x10]
    /* [0x11] */
    u32 reg_pwmp_key0                 :8 ; /// prescaler of key0 PWM, input clock is 32KHz
                                           /// 00000000: divide by 1
                                           /// 00000001: divide by 2
                                           /// ¡K¡K¡K¡K¡K¡K¡K
                                           /// 11111111: divide by 256
    u32 reg_period_key0               :8 ; /// work with reg_pwmp_key0 set the PWM period
                                           /// Fkey0 = CLK/(reg_period_key0 * (reg_pwmp_key0+1)), CLK is 32KHz
                                           /// If reg_pwmp_key0 or reg_period_key0 is 0,the PWM output is 0
    u32 :16; /// [0x11]
    /* [0x12] */
    u32 reg_cycle0_key0               :8 ; /// work with reg_cycle1_key0
                                           /// set the number of times a PWM shape is repeat.
                                           /// cycle0 and cycle1 are both 0 : PWM shape is repeat without iversion
                                           /// cycle0 and cycle1 is not 0  : a inverterd PWM shape is repeat 
                                           /// cycle0 and cycle1 are both nonzero : PWM shape repeat cycle0 times the inverterd and repeated cycle1 times
    u32 reg_cycle1_key0               :8 ; /// same as cycle0
    u32 :16; /// [0x12]
    /* [0x13] */
    u32 reg_en_key1                   :1 ; /// enable KEYPAD1 generation
                                           /// 0:disable 1: enable
    u32 reg_sel_key1                  :1 ; /// KEYPAD1 PWM control selection 
                                           /// 0:control by HW PWM
                                           /// 1: control by reg_sw_key1
    u32 reg_sw_key1                   :1 ; /// control KEYPAD1 PWM 
                                           /// 0: send low to KEYPAD1 PWM pin 
                                           /// 1: send high to KEYPAD1 PWM pin
    u32 :5 ; /// [0x13]
    u32 reg_ratio_key1                :8 ; /// set the PWM output high ratio relative to reg_period_key1
                                           /// if ratio value >= period value ,PWM output is 1 
                                           /// 00000000: PWM output 1
                                           /// 00000001: PWM output is high for 1 Fkey1 clock
                                           /// 00000010: PWM output is high for 2 Fkey1 clock
                                           /// ...............
                                           /// 11111111: PWM output is high for 255 Fkey1 clock
    u32 :16; /// [0x13]
    /* [0x14] */
    u32 reg_pwmp_key1                 :8 ; /// prescaler of key1 PWM, input clock is 32KHz
                                           /// 00000000: divide by 1
                                           /// 00000001: divide by 2
                                           /// ¡K¡K¡K¡K¡K¡K¡K
                                           /// 11111111: divide by 256
    u32 reg_period_key1               :8 ; /// work with reg_pwmp_key1 set the PWM period
                                           /// Fkey1 = CLK/(reg_period_key1 * (reg_pwmp_key1+1)), CLK is 32KHz
                                           /// If reg_pwmp_key1 or reg_period_key1 is 0,the PWM output is 0
    u32 :16; /// [0x14]
    /* [0x15] */
    u32 reg_cycle0_key1               :8 ; /// work with reg_cycle1_key1
                                           /// set the number of times a PWM shape is repeat.
                                           /// cycle0 and cycle1 are both 0 : PWM shape is repeat without iversion
                                           /// cycle0 and cycle1 is not 0  : a inverterd PWM shape is repeat 
                                           /// cycle0 and cycle1 are both nonzero : PWM shape repeat cycle0 times the inverterd and repeated cycle1 times
    u32 reg_cycle1_key1               :8 ; /// same as cycle0
    u32 :16; /// [0x15]
    u32 :32; /// [0x16]
    u32 :32; /// [0x17]
    u32 :32; /// [0x18]
    u32 :32; /// [0x19]
    u32 :32; /// [0x1A]
    u32 :32; /// [0x1B]
    /* [0x1C] */
    u32 reg_pmu_spare0                :16; /// pmu spare register
    u32 :16; /// [0x1C]
    /* [0x1D] */
    u32 reg_pmu_spare1                :16; /// pmu spare register
    u32 :16; /// [0x1D]
    /* [0x1E] */
    u32 reg_pmu_spare2                :16; /// pmu spare register
                                           /// [0]: 0: disable bt_pmu clock
                                           ///       1: enable  bt_pmu clock
                                           /// [3:1]: reserved
                                           /// [6:4] : pmu_apll_pd delay select , this bit is valid when pmu_apll_select is high 
                                           ///    0 : mpll_pd delay 1T
                                           ///    1 : mpll_pd delay 2T
                                           ///    2 : mpll_pd delay 3T
                                           ///    3 : mpll_pd delay 4T
                                           ///    4 : mpll_pd delay 5T
                                           ///    5 : mpll_pd delay 6T
                                           ///    6 : mpll_pd delay 7T
                                           ///    7 : mpll_pd delay 8T
                                           /// [7] : pmu_apll_select 
                                           ///       0 : use mpll_pd
                                           ///       1 : mpll_pd delay 
                                           /// [8] : pmu_apll_rst en, this bit is valid when pmu_apll_pd_en is high
                                           /// [9] : pmu_apll_pd_en
                                           /// [12:10] reserved
                                           /// [13]:force OSCEN enable
                                           /// [15:14] reserved
                                           /// 
    u32 :16; /// [0x1E]
    /* [0x1F] */
    u32 reg_pmu_spare3                :16; /// pmu spare register
                                           /// [0]: btrf chip enable software reset
                                           /// [1]: 0: reg_ldorf_pg =btrf_chip_enable
                                           ///       1: reg_ldorf_pg =rf2pm_ldo_ok
                                           /// [2]: 0: LDO_LCM_EN control by pmu_fsm (reg_ldovlcm_a_en, reg_ldovlcm_s_en) 
                                           ///       1:  LDO_LCM_EN control by (PAD_VMSEL & ext_mem_nand)
                                           /// [3]: 0: dbbus15= efuse_dbbus
                                           ///       1: dbbus15 = rtc_testbus; 
                                           /// [15:4] reserved
                                           /// 
    u32 :16; /// [0x1F]
    /* [0x20] */
    u32 reg_bt_clock_backup_0         :16; /// None
    u32 :16; /// [0x20]
    u32 reg_bt_clock_backup_1         :12; /// @see reg_bt_clock_backup_0
    u32 :20; /// [0x21]
    /* [0x22] */
    u32 reg_bt_bit_cnt_backup         :11; /// None
    u32 :21; /// [0x22]
    /* [0x23] */
    u32 reg_bt_timer0_0               :16; /// set bt timer0 for interrupt 
    u32 :16; /// [0x23]
    u32 reg_bt_timer0_1               :4 ; /// @see reg_bt_timer0_0
    u32 :28; /// [0x24]
    /* [0x25] */
    u32 reg_bt_timer1_0               :16; /// set bt timer1 for interrupt
    u32 :16; /// [0x25]
    u32 reg_bt_timer1_1               :4 ; /// @see reg_bt_timer1_0
    u32 :28; /// [0x26]
    /* [0x27] */
    u32 reg_bt_timer0_en              :1 ; /// set bt timer0 enable
    u32 reg_bt_timer1_en              :1 ; /// set bt timer1 enable
    u32 reg_bt_timer0_int             :1 ; /// bt timer0 interrupt flag
    u32 reg_bt_timer1_int             :1 ; /// bt timer1 interrupt flag
    u32 reg_clk32k_flag               :1 ; /// 32k flag
    u32 :27; /// [0x27]
    u32 :32; /// [0x28]
    u32 :32; /// [0x29]
    u32 :32; /// [0x2A]
    u32 :32; /// [0x2B]
    u32 :32; /// [0x2C]
    u32 :32; /// [0x2D]
    u32 :32; /// [0x2E]
    u32 :32; /// [0x2F]
    /* [0x30] */
    u32 reg_mmp_rstn                  :1 ; /// reset mmp_top 
    u32 reg_mmp_mtcmos_in             :1 ; ///  mmp_top  mtcmos in
                                           /// 0: power off 
                                           /// 1: power on (default on)
    u32 reg_mmp_piso                  :1 ; /// mmp_top power-fence isolation
    u32 reg_mmp_mtcmos_out            :1 ; /// mmp mtcmos out flag
                                           /// 0: power off
                                           /// 1: power on
    u32 :28; /// [0x30]
    /* [0x31] */
    u32 reg_imi_piso                  :8 ; /// imi_top power-fence isolation  //blossom no use 
    u32 reg_imi_mtcmos                :8 ; /// imi_top  mtcmos in // //blossom no use 
                                           /// 0: power off
                                           /// 1: power on (default on)
    u32 :16; /// [0x31]
    /* [0x32] */
    u32 reg_imi_mtcmos_out            :8 ; /// imi_top  mtcmos in //blossom no use 
                                           /// 0: power off
                                           /// 1: power on
    u32 :24; /// [0x32]
    /* [0x33] */
    u32 reg_lcd_rstn                  :1 ; /// reset LCD 
    u32 reg_sw_arm_rstn               :1 ; /// when boot_sbus0| boot_sbus1| boot_jtag 
                                           /// arm resetn will stetting by this register  
                                           /// default is 0; need i2c or jtag release this register
    u32 reg_dbb2arm_rstn              :1 ; /// dbb2arm rstn flag
    u32 reg_dbb2arm_poff              :1 ; /// dbb2arm poweroff flag
    u32 reg_dbb2arm_piso              :1 ; /// dbb2arm power fence flag
    u32 :27; /// [0x33]
    /* [0x34] */
    u32 reg_en_rled                   :1 ; /// enable R PWM generation
                                           /// 0:disable 1: enable
    u32 reg_sel_rled                  :1 ; /// R LED PWM control selection 
                                           /// 0:control by HW PWM
                                 
    u32 reg_sw_rled                   :1 ; /// control R LED PWM 
                                           /// 0: send low to R LED PWM pin 
                                           /// 1: send high to R LED PWM pin
    u32 :5 ; /// [0x34]
    u32 reg_ratio_rled                :8 ; /// set the PWM output high ratio relative to reg_period_rled
                                           /// if ratio value >= period value ,PWM output is 1 
                                           /// 00000000: PWM output 1
                                           /// 00000001: PWM output is high for 1 Frled clock
                                           /// 00000010: PWM output is high for 2 Frled clock
                                           /// ...............
                                           /// 11111111: PWM output is high for 255 Frled clock
    u32 :16; /// [0x34]
    /* [0x35] */
    u32 reg_pwmp_rled                 :8 ; /// prescaler of rled PWM, input clock is 32KHz
                                           /// 00000000: divide by 1
                                           /// 00000001: divide by 2
                                           /// ¡K¡K¡K¡K¡K¡K¡K
                                           /// 11111111: divide by 256
    u32 reg_period_rled               :8 ; /// work with reg_pwmp_rled set the PWM period
                                           /// Frled = CLK/(reg_period_rled * (reg_pwmp_rled+1)), CLK is 32KHz
                                           /// If reg_pwmp_rled or reg_period_rled is 0,the PWM output is 0
    u32 :16; /// [0x35]
    /* [0x36] */
    u32 reg_cycle0_rled               :8 ; /// work with reg_cycle1_rled
                                           /// set the number of times a PWM shape is repeat.
                                           /// cycle0 and cycle1 are both 0 : PWM shape is repeat without iversion
                                           /// cycle0 and cycle1 is not 0  : a inverterd PWM shape is repeat 
                                           /// cycle0 and cycle1 are both nonzero : PWM shape repeat cycle0 times the inverterd and repeated cycle1 times
    u32 reg_cycle1_rled               :8 ; /// same as cycle0
    u32 :16; /// [0x36]
    /* [0x37] */
    u32 reg_en_gled                   :1 ; /// enable G PWM generation
                                           /// 0:disable 1: enable
    u32 reg_sel_gled                  :1 ; /// G LED PWM control selection 
                                           /// 0:control by HW PWM
                                           /// 1: control by reg_sw_gled
    u32 reg_sw_gled                   :1 ; /// control G LED PWM 
                                           /// 0: send low to G LED PWM pin 
                                           /// 1: send high to G LED PWM pin
    u32 :5 ; /// [0x37]
    u32 reg_ratio_gled                :8 ; /// set the PWM output high ratio relative to reg_period_gled
                                           /// if ratio value >= period value ,PWM output is 1 
                                           /// 00000000: PWM output 1
                                           /// 00000001: PWM output is high for 1 Fgled clock
                                           /// 00000010: PWM output is high for 2 Fgled clock
                                           /// ...............
                                           /// 11111111: PWM output is high for 255 Fgled clock
    u32 :16; /// [0x37]
    /* [0x38] */
    u32 reg_pwmp_gled                 :8 ; /// prescaler of gled PWM, input clock is 32KHz
                                           /// 00000000: divide by 1
                                           /// 00000001: divide by 2
                                           /// ¡K¡K¡K¡K¡K¡K¡K
                                           /// 11111111: divide by 256
    u32 reg_period_gled               :8 ; /// work with reg_pwmp_gled set the PWM period
                                           /// Fgled = CLK/(reg_period_gled * (reg_pwmp_gled+1)), CLK is 32KHz
                                           /// If reg_pwmp_gled or reg_period_gled is 0,the PWM output is 0
    u32 :16; /// [0x38]
    /* [0x39] */
    u32 reg_cycle0_gled               :8 ; /// work with reg_cycle1_gled
                                           /// set the number of times a PWM shape is repeat.
                                           /// cycle0 and cycle1 are both 0 : PWM shape is repeat without iversion
                                           /// cycle0 and cycle1 is not 0  : a inverterd PWM shape is repeat 
                                           /// cycle0 and cycle1 are both nonzero : PWM shape repeat cycle0 times the inverterd and repeated cycle1 times
    u32 reg_cycle1_gled               :8 ; /// same as cycle0
    u32 :16; /// [0x39]
    /* [0x3A] */
    u32 reg_en_bled                   :1 ; /// enable B PWM generation
                                           /// 0:disable 1: enable
    u32 reg_sel_bled                  :1 ; /// B LED PWM control selection 
                                           /// 0:control by HW PWM
                                           /// 1: control by reg_sw_bled
    u32 reg_sw_bled                   :1 ; /// control B LED PWM 
                                           /// 0: send low to B LED PWM pin 
                                           /// 1: send high to B LED PWM pin
    u32 :5 ; /// [0x3A]
    u32 reg_ratio_bled                :8 ; /// set the PWM output high ratio relative to reg_period_bled
                                           /// if ratio value >= period value ,PWM output is 1 
                                           /// 00000000: PWM output 1
                                           /// 00000001: PWM output is high for 1 Fbled clock
                                           /// 00000010: PWM output is high for 2 Fbled clock
                                           /// ...............
                                           /// 11111111: PWM output is high for 255 Fbled clock
    u32 :16; /// [0x3A]
    /* [0x3B] */
    u32 reg_pwmp_bled                 :8 ; /// prescaler of bled PWM, input clock is 32KHz
                                           /// 00000000: divide by 1
                                           /// 00000001: divide by 2
                                           /// ¡K¡K¡K¡K¡K¡K¡K
                                           /// 11111111: divide by 256
    u32 reg_period_bled               :8 ; /// work with reg_pwmp_bled set the PWM period
                                           /// Fbled = CLK/(reg_period_bled * (reg_pwmp_bled+1)), CLK is 32KHz
                                           /// If reg_pwmp_bled or reg_period_bled is 0,the PWM output is 0
    u32 :16; /// [0x3B]
    /* [0x3C] */
    u32 reg_cycle0_bled               :8 ; /// work with reg_cycle1_bled
                                           /// set the number of times a PWM shape is repeat.
                                           /// cycle0 and cycle1 are both 0 : PWM shape is repeat without iversion
                                           /// cycle0 and cycle1 is not 0  : a inverterd PWM shape is repeat 
                                           /// cycle0 and cycle1 are both nonzero : PWM shape repeat cycle0 times the inverterd and repeated cycle1 times
    u32 reg_cycle1_bled               :8 ; /// same as cycle0
    u32 :16; /// [0x3C]
    u32 :32; /// [0x3D]
    u32 :32; /// [0x3E]
    u32 :32; /// [0x3F]
    u32 :32; /// [0x40]
    u32 :32; /// [0x41]
    /* [0x42] */
    u32 reg_vl_a_en                   :1 ; /// VL enable in active mode
                                           /// VL need enable before buck enable 
    u32 reg_vl_s_en                   :1 ; /// VL enable in standby mode
    u32 reg_ldovabb_a_lq              :1 ; /// Low-Quiescent mode in active mode
    u32 reg_ldovabb_s_lq              :1 ; /// Low-Quiescent mode in standby 
    u32 :28; /// [0x42]
    /* [0x43] */
    u32 reg_ldovrf2_a_en              :1 ; /// enable ldo_vrf1 in active mode, default = 1
    u32 reg_ldovrf2_a_lq              :1 ; /// Low-Quiescent mode in standby 
    u32 reg_ldovrf2_s_en              :1 ; /// enable ldo_vrf1 in standby mode, default = 0.
    u32 reg_ldovrf2_s_lq              :1 ; /// Low-Quiescent mode in standby 
    u32 reg_ldovrf2_a_vset            :2 ; /// select output voltage level, (user ldo_150m_hv)
                                           /// [00] : 2.9V(default)
                                           /// [01] : 2.8V.
                                           /// [10] : 2.7V.
                                           /// [11] : 2.5V.
    u32 reg_ldovrf2_s_vset            :2 ; /// select output voltage level, (user ldo_150m_hv)
                                           /// [00] : 2.9V(default)
                                           /// [01] : 2.8V.
                                           /// [10] : 2.7V.
                                           /// [11] : 2.5V.
    u32 :24; /// [0x43]
    /* [0x44] */
    u32 reg_fro_clk_adj               :4 ; /// fro clock adjust //efuse[15:12]
    u32 reg_fro_a_en                  :1 ; /// FRO enable at active mode
    u32 reg_fro_s_en                  :1 ; /// FRO enable at standby mode
    u32 :2 ; /// [0x44]
    u32 reg_sw_sqren_sel              :1 ; /// software SQR enable selection
                                           /// 0: from dbb sqren control
                                           /// 1: by reg_sw_sqren
    u32 reg_sw_sqren                  :1 ; /// software SQR enable
                                           /// 0: disable 
                                           /// 1: enable
    u32 :22; /// [0x44]
    /* [0x45] */
    u32 reg_ldovper1_a_en             :1 ; /// enable ldo_vper1 in active mode
    u32 reg_ldovper1_a_lq             :1 ; /// Low-Quiescent mode in acitve mode
    u32 reg_ldovper1_vset             :2 ; /// select output voltage level, (user ldo_150m_hv)
                                           /// [00] : 1.5V(default)
                                           /// [01] : 1.8V.
                                           /// [10] : 2.8V.
                                           /// [11] : 2.9V.
    u32 reg_ldovper1_s_en             :1 ; /// enable ldo_vper1 in standby mode
    u32 reg_ldovper1_s_lq             :1 ; /// Low-Quiescent mode in standby mode
    u32 reg_ldovper1_d_time           :2 ; /// standby mode turn-off delay time
                                           /// 00: 0us
                                           /// 01: 250us
                                           /// 10: 500us
                                           /// 11: 1ms
    u32 reg_ldovper2_a_en             :1 ; /// enable ldo_vper2 in active mode
    u32 reg_ldovper2_a_lq             :1 ; /// Low-Quiescent mode in acitve mode
    u32 reg_ldovper2_vset             :2 ; /// select output voltage level, (user ldo_150m_hv)
                                           /// [00] : 2.8V(default)
                                           /// [01] : 2.9V.
                                           /// [10] : 1.8V.
                                           /// [11] : 1.9V.
    u32 reg_ldovper2_s_en             :1 ; /// enable ldo_vper2 in standby mode
    u32 reg_ldovper2_s_lq             :1 ; /// Low-Quiescent mode in standby mode
    u32 reg_ldovper2_d_time           :2 ; /// standby mode turn-off delay time
                                           /// 00: 0us
                                           /// 01: 250us
                                           /// 10: 500us
                                           /// 11: 1ms
    u32 :16; /// [0x45]
    /* [0x46] */
    u32 reg_ldovper3_a_en             :1 ; /// enable ldo_vper3 in active mode
    u32 reg_ldovper3_a_lq             :1 ; /// Low-Quiescent mode in acitve mode
    u32 reg_ldovper3_vset             :2 ; /// select output voltage level, (user ldo_150m_lv)
                                           /// [00] : 2.8V(default)
                                           /// [01] : 2.9V.
                                           /// [10] : 1.8V.
                                           /// [11] : 1.9V.
    u32 reg_ldovper3_s_en             :1 ; /// enable ldo_vper3 in standby mode
    u32 reg_ldovper3_s_lq             :1 ; /// Low-Quiescent mode in standby mode
    u32 reg_ldovper3_d_time           :2 ; /// standby mode turn-off delay time
                                           /// 00: 0us
                                           /// 01: 250us
                                           /// 10: 500us
                                           /// 11: 1ms
    u32 reg_ldovper4_a_en             :1 ; /// enable ldo_vper4 in active mode
    u32 reg_ldovper4_a_lq             :1 ; /// Low-Quiescent mode in acitve mode
    u32 reg_ldovper4_vset             :2 ; /// select output voltage level, (user ldo_150m_hv)
                                           /// [00] : 2.8V(default)
                                           /// [01] : 2.9V.
                                           /// [10] : 1.8V.
                                           /// [11] : 1.9V.
    u32 reg_ldovper4_s_en             :1 ; /// enable ldo_vper4 in standby mode
    u32 reg_ldovper4_s_lq             :1 ; /// Low-Quiescent mode in standby mode
    u32 reg_ldovper4_d_time           :2 ; /// standby mode turn-off delay time
                                           /// 00: 0us
                                           /// 01: 250us
                                           /// 10: 500us
                                           /// 11: 1ms
    u32 :16; /// [0x46]
    /* [0x47] */
    u32 reg_buck_test                 :2 ; /// buck test mode
    u32 reg_buck_ptest                :1 ; /// PMOS RON test mode
    u32 reg_buck_clk_ok               :1 ; /// BUCK clock OK flag
    u32 reg_bk1_ocp_flag              :1 ; /// BUCK short circuit flag, read only
    u32 :2 ; /// [0x47]
    u32 reg_buck_test1_active         :1 ; /// buck test1 active register
    u32 reg_buck_test1_standby        :1 ; /// buck test1 standby register
    u32 reg_buck_clkdiv2_active       :1 ; /// buck test1 active register
    u32 reg_buck_clkdiv2_standby      :1 ; /// buck test1 active register
    u32 :21; /// [0x47]
    /* [0x48] */
    u32 reg_buck_a_en                 :1 ; /// enable buck in active mode
    u32 reg_buck_s_en                 :1 ; /// enable buck in standby mode
    u32 reg_buck_clk_auto_en          :1 ; /// enable buck clock auto switch when entry/exit sleep
                                           /// 0: control by reg_buck_clk_sel
                                           /// 1: control by pm_fsm_buck_clk_sel (FRO will auto enable when exit sleep)
    u32 reg_buck_ss_off               :1 ; /// Buck soft_start off control //ECO U01 change to 0
    u32 reg_buck_clk_sel              :1 ; /// Buck clock select
                                           /// 0: buck clk from FRO
                                           /// 1: buck clk from MCLK 
    u32 reg_buck_fpwm                 :1 ; /// Buck operation mode control
    u32 reg_buck_sc                   :3 ; /// Buck Slop Compensation select
                                           /// 000: 0.2v/us  001: 0.3v/us  010: 0.4v/us  011: 0.5v/us
                                           /// 100: 0.6v/us  101: 0.7v/us  110: 0.8v/us  111: 0.9v/us
    u32 reg_buck_int_comp             :2 ; /// Buck internal compensation select
                                           /// 00: Ceq=200pF Req=40kohm
                                           /// 01: Ceq=400pF Req=40kohm
                                           /// 00: Ceq=200pF Req=60kohm
                                           /// 11: OFF Cboost
    u32 reg_buck_ocp_sel              :2 ; /// Buck OCP current select (over current protect level)
                                           /// 00: 600mA 01:700mA 10:800mA 11:900mA
    u32 reg_vbk_lvl                   :3 ; /// Buck voltage level control
                                           /// 000: 1.20v  001: 1.25v  010: 1.30v  011: 1.35v
                                           /// 100: x         101: 1.05v  110: 1.10v   111: 1.15v
    u32 :16; /// [0x48]
    /* [0x49] */
    u32 reg_a_pd_bk1ldo               :1 ; /// PD of buckldo in active mode //no use in bravo
    u32 reg_s_pd_bk1ldo               :1 ; /// PD of buckldo in standby mode //no use in bravo
    u32 reg_bkldo_a_lq                :1 ; /// Low-Quiescent mode in active mode
    u32 reg_bkldo_s_lq                :1 ; /// Low-Quiescent mode in standby 
    u32 :3 ; /// [0x49]
    u32 reg_std_ramp_step             :1 ; /// BUCK STD LDO ramping step 
                                           /// 0: 50mV 1: 100mV
    u32 reg_std_ramp_target           :5 ; /// BUCK1 STD LDO ramping target (when DRM=1)
                                           /// 00000: -100 mV
                                           /// 00001: -150 mV
                                           /// 00010: -200 mV
                                           /// 00011: -250 mV
                                           /// 00100: -300 mV
                                           /// 00101: -350 mV
                                           /// 00110: -400 mV
                                           /// 00111: -450 mV
                                           /// 01000: -500 mV
                                           /// 01001: -550 mV
                                           /// 01010: -600 mV
                                           /// others: -100 mV
    u32 reg_vrefstd_test              :1 ; /// Test mode select, output VREFSTD
    u32 reg_buck_td_ctrl              :2 ; /// Buck dead time control
                                           /// 00: 10 ns  01/10: 7 ns 11: 3ns
    u32 :16; /// [0x49]
    /* [0x4A] */
    u32 reg_auxi_tr_sar               :5 ; /// pm_saradc trim control
    u32 :27; /// [0x4A]
    /* [0x4B] */
    u32 reg_ext_1hz_compare           :16; /// ext 32k 1hz compare value (use 32k clock)
    u32 :16; /// [0x4B]
    /* [0x4C] */
    u32 reg_sub_cnt                   :16; /// ext 32k 1hz counter
    u32 :16; /// [0x4C]
    /* [0x4D] */
    u32 reg_ext_1hz_index             :1 ; /// ext 32k 1hz index
    u32 reg_ext_1hz_ready             :1 ; /// from pmu ext 32k 1hz ready
    u32 reg_rtc_xtal32k_sel           :1 ; /// ext 32k selection  from rtc power domain
    u32 reg_xtal32k_sel               :1 ; /// ext 32k selection foto clk_gen ; mux result by reg_xtal32k_sel_ow and reg_xtal32k_ow
    u32 reg_xtal32k_sel_ow            :1 ; /// ext 32k selection over write enable 
                                           /// 0: no over write
                                           /// 1: over write by reg_xtal32k_ow
    u32 reg_xtal32k_ow                :1 ; /// ext 32k selection  over write vaule
                                           /// 0: use 32k from 26Mhz
                                           /// 1: use XTAL 32K    (default 32K need come from RTC domain)
    u32 reg_rtc_ext_1hz_sel           :1 ; /// rtc start to use  ext 1hz 
    u32 :25; /// [0x4D]
    /* [0x4E] */
    u32 reg_wifi_clken_sw_sel         :1 ; /// wifi clk buffer enable soft ware selection
                                           /// 0: 0 (default) control by wifi pad
                                           /// 1: 1 control by reg_wifi_clken_sw_ow
    u32 reg_wifi_clken_sw_ow          :1 ; /// wifi clk buffer enable software overwrite 
                                           /// 0: 0 (default) 
                                           /// 1: 1
    u32 reg_wifi_clken_polarity       :1 ; /// wifi clk buffer enable software overwrite polarity
                                           /// 0: 0 (default) 
                                           /// 1: 1 (inverse polarity from pad)
    u32 :29; /// [0x4E]
    u32 :32; /// [0x4F]
    /* [0x50] */
    u32 reg_ldo2p5_a_en               :1 ; /// enable ldo_2p5 in active mode, default = 1
    u32 reg_ldo2p5_a_byp              :1 ; /// Low-Quiescent mode in active mode
    u32 reg_ldo2p5_s_en               :1 ; /// enable ldo_2p5 in standby mode, default = 0.
    u32 reg_ldo2p5_s_byp              :1 ; /// Low-Quiescent mode in standby 
    u32 reg_ldo2p5_lev                :2 ; /// voltage level
    u32 reg_ldo2p5_a_lq               :1 ; /// Low-Quiescent mode in active mode
    u32 reg_ldo2p5_s_lq               :1 ; /// Low-Quiescent mode in standby 
    u32 reg_dcxoldo_a_en              :1 ; /// enable ldo_dcxo in active mode, default = 1
    u32 reg_dcxoldo_a_tri             :1 ; /// enable ldo_dcxo tristate in  active mode
    u32 reg_dcxoldo_s_en              :1 ; /// enable ldo_dcxo in standby mode
    u32 reg_dcxoldo_s_tri             :1 ; /// enable ldo_dcxo tristate in standby mode
    u32 reg_dcxoldo_vset              :4 ; /// enable ldo_dcxo voltage level
    u32 :16; /// [0x50]
    /* [0x51] */
    u32 reg_en_a_cbc                  :1 ; /// enable CBC in active mode, default = 0.
    u32 reg_en_a_vrefldo              :1 ; /// enable Vref 1.2V for LDO_DCXO (active)
    u32 reg_en_a_dcxoldo_10u          :1 ; /// for LDO_DCXO bias current
    u32 :1 ; /// [0x51]
    u32 reg_en_s_cbc                  :1 ; /// enable CBC in standby mode, default = 0.
    u32 reg_en_s_vrefldo              :1 ; /// enable Vref 1.2V for LDO_DCXO (standby)
    u32 reg_en_s_dcxoldo_10u          :1 ; /// for LDO_DCXO bias current
    u32 :1 ; /// [0x51]
    u32 reg_en_qs                     :1 ; /// CBC quick start mode to reduce settling time
    u32 reg_en_qspbuf                 :1 ; /// CBC quick start buffer
    u32 reg_trim_vref                 :6 ; /// CBC trim vref
    u32 :16; /// [0x51]
    /* [0x52] */
    u32 reg_1v2_lqldo_a_en            :1 ; /// enable LQ LDO in active mode
    u32 reg_1v2_lqldo_s_en            :1 ; /// enable LQ LDO in standby mode
    u32 reg_1v2_lqldo_a_vset          :2 ; /// 1.2V LQ LDO voltage setting at active mode
    u32 reg_1v2_lqldo_s_vset          :2 ; /// 1.2V LQ LDO voltage setting at standby mode
    u32 :26; /// [0x52]
    /* [0x53] */
    u32 reg_dcxo_a_cur_sel            :4 ; /// DCXO active mode current select
    u32 reg_dcxo_s_cur_sel            :4 ; /// DCXO standby mode current select
    u32 :24; /// [0x53]
    /* [0x54] */
    u32 reg_cor_a_tune                :12; /// DCXO
    u32 :20; /// [0x54]
    /* [0x55] */
    u32 reg_cor_s_tune                :12; /// DCXO
    u32 :20; /// [0x55]
    /* [0x56] */
    u32 reg_dcxo_a_fine_tune          :10; /// DCXO
    u32 :22; /// [0x56]
    /* [0x57] */
    u32 reg_dcxo_s_fine_tune          :10; /// DCXO
    u32 :22; /// [0x57]
    u32 :32; /// [0x58]
    u32 :32; /// [0x59]
    u32 :32; /// [0x5A]
    /* [0x5B] */
    u32 reg_wd_en                     :1 ; /// enable wtach dog for reset host
    u32 reg_clear_wd                  :1 ; /// clear wtach dog
    u32 reg_wd_timeout                :12; /// set wtach dog time out value (128hz)
    u32 :18; /// [0x5B]
    /* [0x5C] */
    u32 reg_pmu_testbus_0             :16; /// pmu testbus : selection by reg_dbbus_sel
    u32 :16; /// [0x5C]
    u32 reg_pmu_testbus_1             :8 ; /// @see reg_pmu_testbus_0
    u32 :24; /// [0x5D]
    u32 :32; /// [0x5E]
    /* [0x5F] */
    u32 reg_reserved_status           :16; /// read only reserved status [15:0] = 16'b0
    u32 :16; /// [0x5F]
    /* [0x60] */
    u32 reg_en_cled                   :1 ; /// Enable Charger LED Driver
                                           /// //no use in bravo
    u32 reg_cled_pwm                  :1 ; /// PWM controlby CPU; when reg_cled_pwm_en =0
                                           /// //no use in bravo
    u32 reg_cled_pwm_en               :1 ; /// PWM controller enable
                                           /// //no use in bravo
    u32 reg_cled_blink                :2 ; /// Charger LED blinking rate ; work with reg_cled_pwm_en
                                           /// 00: staty on
                                           /// 01: ~0.5s
                                           /// 10: ~1s
                                           /// 11: ~2s
                                           /// //no use in bravo
    u32 reg_en_precharge              :1 ; /// enable pre-charger block
                                           /// //no use in asura
    u32 reg_envbat_meas               :1 ; /// enable measuring VBAT
    u32 reg_chrg_fb_sel               :1 ; /// charger feedback voltage selection 0: from VSYS; 1:fromVBAT
                                           /// //no use in asura
    u32 reg_cv_sel                    :1 ; /// CV level selection; 0: CV level = 3.8V; 1:CV level = 4.2V
                                           /// //no use in asura
    u32 reg_cctarget_sel              :1 ; /// cctarget selectio
                                           /// 0: cctarget will be force 500mA when PMTEST=1; cctarget = reg_cctarget when PMTEST=0
                                           /// 1:cctarget from reg_cctarget
    u32 reg_chrgoff                   :1 ; /// Disable Charger function; 0: enable 1:disable
    u32 reg_cctarget                  :3 ; /// Charging current selection
                                           /// 000 : 100mA
                                           /// 001 : 200mA(default)
                                           /// 010 : 300mA
                                           /// 011 : 400mA
                                           /// 100: 500mA
                                           /// 111: 1A
    u32 reg_cvtarget                  :2 ; /// CV level selection; 
                                           /// 00: 4.2V
                                           /// 01: 4.3V
                                           /// 10: 4.1V
                                           /// 11: 4.0V
    u32 :16; /// [0x60]
    /* [0x61] */
    u32 reg_charge_ctrl_pulse         :1 ; /// enable pulse for reg_chrgoff, reg_cctarget
    u32 reg_pd_auto                   :1 ; /// Power down auto-zero CS amplifier
                                           /// 0--> on, 1--> off
    u32 reg_ofst_tst                  :1 ; /// offset voltage test mode
    u32 reg_cs_gain                   :1 ; /// current source gain adjustment
    u32 reg_vbatok                    :1 ; /// battery ok flag from PM_logic
    u32 reg_ada_exist                 :1 ; /// Adapter plug-in flag
                                           /// 1. High : plug-in
                                           /// 2. Low: no plug-in
    u32 reg_vbat_lvl1                 :1 ; /// VBAT voltage level flag
                                           /// (VBAT>2.6V)
    u32 reg_vbat_lvl2                 :1 ; /// VBAT voltage level flag
                                           /// (VBAT>3.1V)
    u32 reg_chrg_over_v               :1 ; /// Adapter voltage over volatge flag 
                                           /// (Vadapter>6V)
    u32 reg_chrg_pgin                 :1 ; /// Charger plug-in interrupt (RTC domain)
                                           /// high: plug-in
                                           /// low plug-out
    u32 reg_vbat_v2p8_ok              :1 ; /// vbattery 2.8 v ok flag
    u32 reg_vbat_v3p0_ok              :1 ; /// vbattery 3.0 v ok flag
    u32 reg_vbat_v3p2_ok              :1 ; /// vbattery 3.2 v ok flag
    u32 :19; /// [0x61]
    /* [0x62] */
    u32 reg_abbreset_passwd           :8 ; /// PAD pass word for enable PAD_ABBRESET
                                           /// all zero is enable (from pad)
                                           /// not all zero ; PAD_ABBRESET will diable(ABBRESET = 0)
    u32 :24; /// [0x62]
    /* [0x63] */
    u32 reg_phone_off_passwd          :8 ; /// phone off pass word; with reg_phone_off and reg_phone_off_lockb
                                           /// all one is enable
                                           /// not all one is disable
    u32 reg_phone_off                 :1 ; /// enable turn off phone
    u32 reg_phone_off_lockb           :1 ; /// enable reg_PHONE_OFF funtion
                                           /// 0: disable  reg_PHONE_OFF
                                           /// 1: enable  reg_PHONE_OFF
    u32 :22; /// [0x63]
    /* [0x64] */
    u32 reg_master_stdby_en           :1 ; /// enable master standby function 
                                           /// need gating with  osc_en from DBB
    u32 reg_sw_stdbyn_en              :1 ; /// soft-ware control standby enable
                                           /// 0: disable
                                           /// 1: enable ; work with reg_sw_stdbyn
    u32 reg_sw_stdbyn                 :1 ; /// soft-ware control standby register
                                           /// 0: entry PMU sleep
                                           /// 1: no active
    u32 reg_bat_ok_time_sel           :1 ; /// select vbat ok debounce clock 
                                           /// 0: use 2ms  debounce
                                           /// 1: use 16ms debounce 
    u32 reg_bat_no_ok_turnoff         :1 ; /// when vbat <2.8v bat is not ok 
                                           /// 0: battery < 2.8v will not turn off phone
                                           /// 1: battery < 2.8v turn off phone
    u32 reg_ss_slew_rate              :2 ; /// to LDO soft_star slew rate selection
                                           /// 00: 125 us
                                           /// 01: 250 us
                                           /// 10: 500 us (default)
                                           /// 11: 1ms
    u32 reg_level_ov_en               :1 ; /// all level control override enable (0: disable; 1: enable)
    u32 reg_std_time_step             :2 ; /// standby mode entry/exit time step
                                           /// 00: 125 us(default)
                                           /// 01: 250 us
                                           /// 10: 500 us
                                           /// 11: (reserved)
    u32 :4 ; /// [0x64]
    u32 reg_pmu_dig_rstz              :1 ; /// pmu soft ware reset for irq. ldo soft start, pwm 
                                           /// 0: reset 
                                           /// 1: release
    u32 :17; /// [0x64]
    /* [0x65] */
    u32 reg_pmu_fsm_en                :1 ; /// PMU_FSM_EN from rtc_fsm to pmu_fsm
    u32 reg_onoff_appear              :1 ; /// ONOFF_APPEAR from rtc_fsm to pmu_fsm
    u32 reg_bat_on_debounce           :1 ; /// battery on flag
    u32 reg_chgdet_debounce           :1 ; /// chager plug in flag
    u32 reg_pin_stdbyn_m              :1 ; /// master standby_n flag
    u32 reg_pmu_off                   :1 ; /// pmu_off flag
    u32 reg_pin_pwrhld                :1 ; /// PAD PWRHLD flag to pmu_fsm
    u32 reg_pmtest                    :1 ; /// PAD PM_TEST flag to pmu_fsm
    u32 reg_ref_bkldook               :1 ; /// refgen and buck ldo ok flag
    u32 reg_bkrampctrl                :5 ; /// buck ramp control
    u32 :18; /// [0x65]
    /* [0x66] */
    u32 reg_pmu_fsm_status_0          :16; /// pmu_fsm state[23:8]
                                           /// [17:0] : pmu_state
                                           /// [31:18]:reserved
    u32 :16; /// [0x66]
    u32 reg_pmu_fsm_status_1          :16; /// @see reg_pmu_fsm_status_0
    u32 :16; /// [0x67]
    /* [0x68] */
    u32 reg_standby_status            :16; /// m standby fsm and status
                                           /// [8:0] : m_state
                                           /// [15:9] reseverd
    u32 :16; /// [0x68]
    /* [0x69] */
    u32 reg_keyoff_time_out           :11; ///  time out value for ON/OFF button shut-down 
    u32 reg_keyoff_timer_en           :1 ; /// enable press ON/OFF button for force shut-down
    u32 reg_keyoff_timer_clear        :1 ; /// clear timer of ON/OFF button
    u32 :19; /// [0x69]
    /* [0x6A] */
    u32 reg_sel_tmux                  :5 ; /// None
    u32 reg_en_tm_outbuf              :1 ; /// None
    u32 :26; /// [0x6A]
    /* [0x6B] */
    u32 reg_classd_tst                :8 ; /// classd test register
    u32 reg_classd_isel               :6 ; /// Select the bias current:
                                           /// ISEL[1:0] : PGA OP
                                           /// ISEL[3:2]:  Modulator OP
                                           /// ISEL[5:4]: Trigen OP
                                           /// 00: 20uA
                                           /// 01: 10uA
                                           /// 10: 40uA
                                           /// 11: 30uA
    u32 :18; /// [0x6B]
    /* [0x6C] */
    u32 reg_classd_en                 :1 ; /// classd enable
                                           /// 0:classd off
                                           /// 1: classd on
    u32 reg_classd_bias_sel           :2 ; /// (CLASSD_TRI_18_0 CLASSD_MOD_DRIVER_18_2)
                                           /// ClassD bias current ratio selection
                                           /// 00:1X
                                           /// 01:OFF
                                           /// 10:1.5X
                                           /// 11:0.5X
    u32 reg_classd_clk_div2           :1 ; /// (CLASSD_TRI_18_1)
                                           /// ClassD CLK DIV 2X
                                           /// 0:CLK/4 (2.4MHz, triangle wave: 1.2MHz)
                                           /// 1:CLK/8 (1.2MHz, triangle wave: 0.6MHz)
    u32 reg_dis_vcm_mod               :1 ; /// (CLASSD_MOD_18_1)
                                           /// disable classD modulator VCM modification resistor
                                           /// 0:On
                                           /// 1:disable
    u32 reg_classd_drv_slew           :1 ; /// (CLASSD_MOD_DRIVER_18_1)
                                           /// output driver slew rate control (No connect)
    u32 reg_classd_dis_ocp            :1 ; /// (CLASSD_MOD_DRIVER_18_0)
                                           /// ClassD Over current protection disable 
                                           /// 0:enable OCP
                                           /// 1:disable OCP
    u32 reg_classd_ocp_sel            :1 ; /// (CLASSD_MOD_18_2)
                                           /// enable ClassD OCP modification circuit 
                                           /// 0:off
                                           /// 1:enable
    u32 reg_classd_mute               :1 ; /// ClassD mute control
                                           /// 0:normal operation
                                           /// 1:mute
    u32 reg_rset_ocp_stat             :1 ; /// clear OCP flag
                                           /// 0:no action
                                           /// 1:Clear OCP flag, OCP_CLASSD_=0
    u32 reg_classd_byp_mod            :1 ; /// (CLASSD_TRI_18_2)
                                           /// bypass ClassD modulator (No connect)
                                           /// 0: normal operation
                                           /// 1:bypass modulator
    u32 reg_classd_mod_gain_sel       :1 ; /// classd gain selection
                                           /// 0:2X
                                           /// 1:4X
    u32 reg_pga_mute                  :1 ; /// None
    u32 reg_ocp_classd                :1 ; /// None
    u32 reg_pd_classd                 :1 ; /// None
    u32 :17; /// [0x6C]
    /* [0x6D] */
    u32 reg_en_drver_tot              :1 ; /// reserved
    u32 reg_line_drgn                 :3 ; /// gain setting for lineout driver gain
                                           /// 000: 0dB, gain=1
                                           /// 001: -4.4dB, gain=0.6
                                           /// 010: 1.6dB, gain=1.2
                                           /// 011: 3dB, gain= 1.4
                                           /// 100: 6dB, gain=2
                                           /// 101: 9dB, gain=2.8
                                           /// 110: 10dB, gain=3.4
                                           /// 111: 12dB, gain= 4
    u32 reg_line_mute                 :1 ; /// enable mute control of lineout amplifier
    u32 reg_en_mx_line                :1 ; /// enable lineout driver signal input
    u32 reg_en_line_byp               :1 ; /// enable lineout signal bypass to PADs
    u32 reg_pd_cd                     :1 ; /// reserved¡@
    u32 reg_en_drver                  :3 ; /// Enable control 
                                           /// EN_DRVER[0]: lineout amplifier to Class-D
                                           /// EN_DRVER[1]: RCV class-AB amplifier
                                           /// EN_DRVER[2]: R-string for VCM (1.4V)
    u32 reg_en_line_dis               :1 ; /// Lineout discharge path enable
    u32 :20; /// [0x6D]
    /* [0x6E] */
    u32 reg_analog_spare0             :8 ; /// analog spare register default 0
                                           /// [0]: sw contorl rtc_switch enable  // for debug only
                                           /// [1]: sw contorl rtc_switch; 0 use RTC power; 1: use core power 
    u32 reg_analog_spare1             :8 ; /// analog spare register default all 1
    u32 :16; /// [0x6E]
    u32 :32; /// [0x6F]
    /* [0x70] */
    u32 reg_irq_mask                  :16; /// Mask interrupt
    u32 :16; /// [0x70]
    /* [0x71] */
    u32 reg_irq_force                 :16; /// Force interrupt to be 1
    u32 :16; /// [0x71]
    /* [0x72] */
    u32 reg_irq_clr                   :16; /// Clear interrupt
    u32 :16; /// [0x72]
    /* [0x73] */
    u32 reg_irq_raw_status            :16; /// IRQ raw status
                                           /// [15]: reversed; default is 0
                                           /// [14]: reversed; default is 0
                                           /// [13]: irq_ocp_classd; CLASS-D over current protect
                                           /// [12]: irq_pga_mute;AUDIO receiver PGA mute
                                           /// [11]:  reversed; default is 0
                                           /// [10]: LDO_ERR_IRQ; LDO ERROR
                                           /// [9]: ONOFF_PULSE; ONOFF KEY press
                                           /// [8]: KEYOFF_PULSE; ONOFF KEY release
                                           /// [7]: reversed; default is 0
                                           /// [6]: bat_low_irq; battery <3.0V
                                           /// [5]: otp_debounce; refgen over temperature protect
                                           /// [4]: over_voltage_irq; charger over voltage
                                           /// [3]: adaptor_unplug_irq charger plug-out
                                           /// [2]: adaptor_plug_irq; charger plug-in  
                                           /// [1]: buck1ocp_debounce; buck Over Current Protect
                                           /// [0]: reversed; default is 0
    u32 :16; /// [0x73]
    /* [0x74] */
    u32 reg_irq_final_status          :16; /// IRQ final status
    u32 :16; /// [0x74]
    /* [0x75] */
    u32 reg_irq_polarity              :16; /// irq source polarity
} KePmu_t;

typedef struct AsuraPMUReg_s
{
    u16 ldo_vabb_vrf1_vrf2;     // 0x42
    u16 reserved42;
    u16 ldo_rf;                 // 0x43
    u16 reserved43;
    u16 mcp_fro_clk_adj;        // 0x44
    u16 reserved44;
    u16 ldo_vper1_vper2;        // 0x45
    u16 reserved45;
    u16 ldo_vper3_vper4;        // 0x46
    u16 reserved46;
    u16 buck;                   // 0x47
    u16 reserved47;
    u16 buck1;                  // 0x48
    u16 reserved48;
    u16 buck1_std_ldo;          // 0x49
    u16 reserved9;
    u32 reserved4a;             // 0x4A
    u32 reserved4b;             // 0x4B
    u32 reserved4c;             // 0x4C
    u16 buck1_extctrl;        // 0x4D
    u16 reserved4d;             
    u32 reserved4e;             // 0x4E
    u32 reserved4f;             // 0x4F
    u16 ldo_2p5_dcxo;        // 0x50
    u16 reserved50;
    u16 bg_cbc;	                    // 0x51
    u16 reserved51;
    u16 r1v2_lq_ldo;              // 0x52
    u16 reserved52;
    u16 dcxo_cur_Sel;         // 0x53
    u16 reserved53;
    u16 cor_a_tune;             // 0x54	
    u16 reserved54;
    u16 cor_s_tune;             // 0x55
    u16 reserved55;
    u16 dcxo_a_fine_tune; // 0x56
    u16 reserved56;
    u16 dcxo_s_fine_tune; // 0x57
    u16 reserved57;             
    u32 reserved58;             // 0x58
    u32 reserved59;             // 0x59
    u32 reserved5a;             // 0x5A
    u16 pmu_wd_reset;           // 0x5B
    u16 reserved5b;
    u16 pmu_test_bus1;          // 0x5C
    u16 reserved5c;
    u32 reserved5d;             // 0x5D
    u32 reserved5e;             // 0x5E
    u16 rsv_status;             // 0x5F
    u16 reserved5f;
    u16 charger_1;              // 0x60
    u16 reserved60;
    u16 charger_2;              // 0x61
    u16 reserved61;
    u16 abbresere_paswd;     	  // 0x62
    u16 reserved62;
    u16 phone_off_paswd;        // 0x63
    u16 reserved63;
    u16 pmu_top_1;              // 0x64
    u16 reserved64;
    u16 pmu_top_2;              // 0x65
    u16 reserved65;
    u16 reg_pmu_fsm_status_1;   // 0x66
    u16 reserved66;
    u16 reg_pmu_fsm_status_2;   // 0x67
    u16 reserved67;
    u16 reg_standy_status;     // 0x68
    u16 reserved68;
    u16 keyoff_timer;           // 0x69
    u16 reserved69;
    u16 reg6A;                  // 0x6A
    u16 reserved6a;
    u16 classd_1;               // 0x6B
    u16 reserved6b;
    u16 classd_2;               // 0x6C
    u16 reserved6c;
    u16 reg6D;                  // 0x6D
    u16 reserved6d;
    u16 analog_spare;           // 0x6E
    u16 reserved6e;
    u32 reserved6f;             // 0x6F
    u16 reg_irq_mask;           // 0x70
    u16 reserved70;
    u16 reg_irq_force;          // 0x71
    u16 reserved71;
    u16 reg_irq_clr;            // 0x72
    u16 reserved72;
    u16 reg_irq_raw_status;     // 0x73
    u16 reserved73;
    u16 reg_irq_final_status;   // 0x74
    u16 reserved74;
    u16 reg_irq_polarity;       // 0x75
    u16 reserved75;
} AsuraPMUReg_s;

extern volatile KePmu_t * const g_ptKePmu;
extern volatile AsuraPMUReg_s * const g_ptAsuraPMUReg;

//pwrhld_passwd (0x0B)
#define PWRHLD_PASSWD_ON           0xA5
#define PWRHLD_PASSWD_OFF          0x5A

//LDO_VABB_VRF1_VRF2 (0x42)
//#define reg_ldovabb_a_en(d)        (d<<0)
//#define reg_ldovabb_s_en(d)        (d<<1)
#define reg_vl_a_en(d)			   (d<<0)
#define reg_vl_s_en(d)			   (d<<1)
#define reg_ldovabb_a_lq(d)        (d<<2)
#define reg_ldovabb_s_lq(d)        (d<<3)

/*
#define reg_ldovabb_vset_1(d)      (d<<4)
#define reg_ldovabb_vset_2(d)      (d<<5)
#define reg_ldovtcxo_a_en(d)       (d<<6)
#define reg_ldovtcxo_s_en(d)       (d<<7)
#define reg_ldovtcxo_vset_1(d)     (d<<8)
#define reg_ldovtcxo_vset_2(d)     (d<<9)
*/
//LDO_RF (0x43)
#if 0
#define reg_ldovrf1_a_en(d)        (d<<0)
#define reg_ldovrf1_a_lq(d)        (d<<1)
#define reg_ldovrf1_vset_1(d)      (d<<2)
#define reg_ldovrf1_s_en(d)        (d<<4)
#define reg_ldovrf1_s_lq(d)        (d<<5)
//#define reg_ldovrf1_vset_2(d)      (d<<6)
#define reg_ldovrf1_d_time(d)      (d<<6)
#endif
#define reg_ldovrf2_a_en(d)        (d<<0)
#define reg_ldovrf2_a_lq(d)        (d<<1)
#define reg_ldovrf2_s_en(d)        (d<<2)
#define reg_ldovrf2_s_lq(d)        (d<<3)
#define reg_ldovrf2_vset_1(d)      (d<<4)
#define reg_ldovrf2_vset_2(d)      (d<<6)
//#define reg_ldovrf2_d_time(d)      (d<<14)

//FRO (0x44)
#define reg_fro_clk_adj(d)         (d<<0)
#define reg_ldofro_a_en(d)         (d<<4)
#define reg_ldofro_s_en(d)         (d<<5)
//#define reg_mcp_mode(d)            (d<<6)

//LDO_VPER1_2 (0x45)
#define reg_ldovper1_a_en(d)       (d<<0)
#define reg_ldovper1_a_lq(d)       (d<<1)
#define reg_ldovper1_vset_1(d)     (d<<2)
#define reg_ldovper1_s_en(d)       (d<<4)
#define reg_ldovper1_s_lq(d)       (d<<5)
#define reg_ldovper1_d_time(d)     (d<<6)
#define reg_ldovper2_a_en(d)       (d<<8)
#define reg_ldovper2_a_lq(d)       (d<<9)
#define reg_ldovper2_vset_1(d)     (d<<10)
#define reg_ldovper2_s_en(d)       (d<<12)
#define reg_ldovper2_s_lq(d)       (d<<13)
#define reg_ldovper2_d_time(d)     (d<<14)

//LDO_VPER3_4 (0x46)
#define reg_ldovper3_a_en(d)       (d<<0)
#define reg_ldovper3_a_lq(d)       (d<<1)
#define reg_ldovper3_vset_1(d)     (d<<2)
#define reg_ldovper3_s_en(d)       (d<<4)
#define reg_ldovper3_s_lq(d)       (d<<5)
#define reg_ldovper3_d_time(d)     (d<<6)
#define reg_ldovper4_a_en(d)       (d<<8)
#define reg_ldovper4_a_lq(d)       (d<<9)
#define reg_ldovper4_vset_1(d)     (d<<10)
#define reg_ldovper4_s_en(d)       (d<<12)
#define reg_ldovper4_s_lq(d)       (d<<13)
#define reg_ldovper4_d_time(d)     (d<<14)


//Buck (0x47)
#define reg_bk1_drm(d)             (d<<0)

//BUCK1 (0x48)
#define reg_a_buck1(d)             (d<<0)
#define reg_s_buck1(d)             (d<<1)
#define reg_buck_clk_auto_en(d)	   (d<<2)
#define reg_buck_clk_sel(d)        (d<<4)
#define reg_vbk1_ctrl(d)           (d<<13)

//STD_LDO (0x49)
#define reg_a_pd_bk1ldo(d)         (d<<0)
#define reg_s_pd_bk1ldo(d)         (d<<1)
#define reg_bk1ldo_a_lq(d)         (d<<2)
#define reg_bk1ldo_s_lq(d)         (d<<3)
#define reg_std_ramp_step(d)       (d<<7)
#define reg_std1_ramp_target(d)    (d<<8)
#define reg_vrefstd_test(d)        (d<<13)
#define reg_buck_td_ctrl           (d<<14)

//refgen (0x5A)
//#define reg_vref_tst               (d << 0)
#define OPT_EN_MASK                (1 << 1)// Invalid bit!!!
#define OPT_EN                     (1 << 1)// Invalid bit!!!
#define reg_en_trim1(d)            (d << 7)//Invalid bit!!!

//CHARGER CTRL (0x60)
#define reg_charger_func(d)         (d << 10)
#define reg_charger_cc(d)           (d << 11)
#define reg_charger_cv(d)           (d << 14)
#define CHAR_FUNC_CTRL              (1 << 10)
#define CHAR_CC_MASK                (7 << 11)
#define CHAR_CV_MASK                (7 << 14)
#define VBAT_MEASURE_ON             (1 << 6)
#define CHAR_VBAT_MEASURE_MASK      (1 << 6)

//PMU TOP (0x64)
#define reg_master_stdby_en(d)      (d << 0)
#define reg_bat_no_ok_turnoff(d)    (d << 4)
#define REG_BAT_NO_OK_TURNOFF_MASK  (1 << 4)
#define reg_level_ov_en(d)          (d << 7)
#define reg_std_time_step(d)		(d << 8)

//PMU TOP2 (0x65)
#define reg_key_press               (1 << 1)

// ASURA_IRQ_MAP (0x70)
#define ASURA_KEYON_IRQ             (1 << 9)
#define ASURA_KEYOFF_IRQ            (1 << 8)

//PMU IRQ (0x70)
//#define reg_rtc_int_d1(d)           (d<<0)
#define reg_buck1ocp_debounce(d)    (d<<1)
#define reg_adaptor_plug_irq(d)     (d<<2)
#define reg_adaptor_unplug_irq(d)   (d<<3)
#define reg_over_voltage_irq(d)     (d<<4)
#define reg_otp_debounce(d)         (d<<5)
#define reg_bat_low_irq(d)          (d<<6)
#define reg_irq_adc_done(d)         (d<<7)//Invalid bit!!!
#define reg_keyoff_pulse(d)         (d<<8)
#define reg_onoff_pulse(d)          (d<<9)
#define reg_ldo_err_irq(d)          (d<<10)
//#define reg_irq_ocprt(d)            (d<<11)
#define reg_irq_pga_mute(d)         (d<<12)
#define reg_irq_ocp_classd(d)       (d<<13)

#endif /*__KERNEL_PMU_H__*/
