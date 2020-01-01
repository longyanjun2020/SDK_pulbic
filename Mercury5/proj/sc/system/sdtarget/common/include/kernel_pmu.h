#ifndef __KERNEL_PMU_H__
#define __KERNEL_PMU_H__

//------------------------------------------------------------------------------
// Defines
//------------------------------------------------------------------------------
#define VIO1_2V8            0x00
#define VIO1_2V9            0x01
#define VIO1_1V8            0x02
#define VIO1_1V9            0x03
#define VIO2_1V8            0x00
#define VIO2_1V9            0x01
#define VIO2_2V8            0x02
#define VIO2_2V9            0x03

#define VOLT_OFF            0xFF
#define MAX_VOLT_SET_VAL    0x03

#define VOLT_SET(_type_, _val_)     _type_##_##_val_

#define PMULDO_PG_DELAY     300     /* in uSec */

#define SPARE1_LDO_LCM_EN_BIT   0x04


//------------------------------------------------------------------------------
// Typedef, PMU Register Bank
//------------------------------------------------------------------------------
typedef struct KePmu_s
{
    /* [0x00] */
    u32 :32; /// [0x00]
    /* [0x01] */
    u32 reg_ldovmem_a_en              :1 ; /// enable ldo_vmem in active mode, default = 0.
    u32 reg_ldovmem_a_lq              :1 ; /// enable ldo_vmem at LQ mode
    u32 reg_ldovmem_a_vset            :2 ; /// select output voltage level,
                                           /// when PAD_VMSEL =0
                                           /// [00] : 1.85V.(default)  [01] : 1.9V.  [10] : 1.8V.  [11] :1.75V.
                                           /// when PAD_VMSEL =1
                                           /// [00] : 2.8V.(default)  [01] : 2.9V.  [10] : 2.7V.  [11] :2.6V.
    u32 reg_ldovmem_s_en              :1 ; /// enable ldo_vmem in active mode, default = 0.
    u32 reg_ldovmem_s_lq              :1 ; /// enable ldo_vmem at LQ mode
    u32 reg_ldovmem_s_vset            :2 ; /// select output voltage level,
                                           /// when PAD_VMSEL =0
                                           /// [00] : 1.85V.(default)  [01] : 1.9V.  [10] : 1.8V.  [11] :1.75V.
                                           /// when PAD_VMSEL =1
                                           /// [00] : 2.8V.(default)  [01] : 2.9V.  [10] : 2.7V.  [11] :2.6V.
    u32 reg_ldovlcm_a_en              :1 ; /// enable ldo_lcm in active mode, default = 1.
    u32 reg_ldovlcm_a_lq              :1 ; /// enable ldo_lcm at LQ mode
    u32 reg_ldovlcm_a_vset            :2 ; /// select output voltage level,
                                           /// [00] : 2.8V.(default)
                                           /// [01] : 2.9V.
                                           /// [10] : 1.8V.
                                           /// [11] : 1.9V.
    u32 reg_ldovlcm_s_en              :1 ; /// enable ldo_lcm in standby mode, default = 1.
    u32 reg_ldovlcm_s_lq              :1 ; /// enable ldo_vlcm at LQ mode
    u32 reg_ldovlcm_s_vset            :2 ; /// select output voltage level, register inverse with io1
                                           /// [00] : 2.8V.(default)
                                           /// [01] : 2.9V.
                                           /// [10] : 1.8V.
                                           /// [11] : 1.9V.
    u32 :16; /// [0x01]
    /* [0x02] */
    u32 reg_ldovio1_a_en              :1 ; /// enable ldo_vio1 in active mode, default = 1.
    u32 reg_ldovio1_a_lq              :1 ; /// enable ldo_vio1 at LQ mode
    u32 reg_ldovio1_a_vset            :2 ; /// select output voltage level,
                                           /// [00] : 2.8V.(default)
                                           /// [01] : 2.9V.
                                           /// [10] : 1.8V.
                                           /// [11] : 1.9V.
    u32 reg_ldovio1_s_en              :1 ; /// enable ldo_vio1 in standby mode, default = 1.
    u32 reg_ldovio1_s_lq              :1 ; /// enable ldo_vio1 at LQ mode
    u32 reg_ldovio1_s_vset            :2 ; /// select output voltage level,
                                           /// [00] : 2.8V.(default)
                                           /// [01] : 2.9V.
                                           /// [10] : 1.8V.
                                           /// [11] : 1.9V
    u32 reg_ldovio2_a_en              :1 ; /// enable ldo_vio2 in active mode, default = 1.
    u32 reg_ldovio2_a_lq              :1 ; /// enable ldo_vio2 at LQ mode
    u32 reg_ldovio2_a_vset            :2 ; /// select output voltage level,
                                           /// [00] : 1.8V.(default)
                                           /// [01] : 1.9V.
                                           /// [10] : 2.8V.
                                           /// [11] : 2.9V.
    u32 reg_ldovio2_s_en              :1 ; /// enable ldo_vio2 in standby mode, default = 0.
    u32 reg_ldovio2_s_lq              :1 ; /// enable ldo_vio2 at LQ mode; standby mode
    u32 reg_ldovio2_s_vset            :2 ; /// select output voltage level, at standby
                                           /// [00] : 1.8V.(default)
                                           /// [01] : 1.9V.
                                           /// [10] : 2.8V.
                                           /// [11] : 2.9V.
    u32 :16; /// [0x02]
    /* [0x03] */
    u32 reg_ldovsim1_a_en             :1 ; /// enable ldo_vsim1 in active mode, default = 1.
    u32 reg_ldovsim1_a_lq             :1 ; /// enable ldo_vsim1 at LQ mode
    u32 reg_ldovsim1_a_vset           :2 ; /// select output voltage level,
                                           /// [00] : 1.8V.(default)
                                           /// [01] : 1.9V.
                                           /// [10] : 2.8V.
                                           /// [11] : 2.9V.
    u32 reg_ldovsim1_s_en             :1 ; /// enable ldo_vsim1 in standby mode, default = 1.
    u32 reg_ldovsim1_s_lq             :1 ; /// enable ldo_vsim1 at LQ mode
    u32 reg_ldovsim1_s_vset           :2 ; /// select output voltage level,
                                           /// [00] : 1.8V.(default)
                                           /// [01] : 1.9V.
                                           /// [10] : 2.8V.
                                           /// [11] : 2.9V.
    u32 reg_ldovsim1_sel              :1 ; /// ldo sim1 enable select
                                           /// 0: by reg_ldovsim1_a_en( active) ;
                                           ///           reg_ldovsim1_s_en(standby)
                                           /// 1: by dbb fsm control
    u32 :23; /// [0x03]
    /* [0x04] */
    u32 reg_ldovsim2_a_en             :1 ; /// enable ldo_vsim2 in active mode, default = 1.
    u32 reg_ldovsim2_a_lq             :1 ; /// enable ldo_vsim2 at LQ mode
    u32 reg_ldovsim2_a_vset           :2 ; /// select output voltage level,
                                           /// [00] : 2.8V.(default)
                                           /// [01] : 2.9V.
                                           /// [10] : 1.8V.
                                           /// [11] : 1.9V.
    u32 reg_ldovsim2_s_en             :1 ; /// enable ldo_vsim2 in standby mode,
    u32 reg_ldovsim2_s_lq             :1 ; /// enable ldo_vsim2 at LQ mode; standby mode
    u32 reg_ldovsim2_s_vset           :2 ; /// select output voltage level,
                                           /// [00] : 2.8V.(default)
                                           /// [01] : 2.9V.
                                           /// [10] : 1.8V.
                                           /// [11] : 1.9V.
    u32 reg_ldovsim2_sel              :1 ; /// ldo sim1 enable select
                                           /// 0: by reg_ldovsim2_a_en( active) ;
                                           ///           reg_ldovsim2_s_en(standby)
                                           /// 1: by dbb fsm control
    u32 :23; /// [0x04]
    /* [0x05] */
    u32 reg_ldovio1_pg                :1 ; /// LDO power good
    u32 reg_ldovio2_pg                :1 ; /// LDO power good
    u32 reg_ldovsim1_pg               :1 ; /// LDO power good
    u32 reg_ldovsim2_pg               :1 ; /// LDO power good
    u32 reg_ldovmem_pg                :1 ; /// LDO power good
    u32 reg_ldovlcm_pg                :1 ; /// LDO power good
    u32 reg_ldoaud25_pg               :1 ; /// LDO power good
    u32 reg_ldoaud12_pg               :1 ; /// LDO power good
    u32 reg_fm_rfp_pg                 :1 ; /// FM LDO power good
    u32 reg_fm_ifp_pg                 :1 ; /// FM LDO power good
    u32 reg_ldorf_pg                  :1 ; /// RF LDO power good
    u32 reg_pm_refok                  :1 ; /// refgen ok flag
    u32 reg_pm_bgok                   :1 ; /// bandgap ok
    u32 reg_ldo_err_int               :1 ; /// ldo vio1 vio2 sim1 sim2 mem lcm has error
    u32 :18; /// [0x05]
    /* [0x06] */
    u32 reg_batdet_debounce           :3 ; /// battery detecttion debounce time
                                           /// 000: 100us    100: 4ms
                                           /// 001: 500us    101: 8ms
                                           /// 010: 1ms       110: 16ms
                                           /// 011: 2ms       111: 32ms
    u32 reg_en_batdet                 :1 ; /// enable battery detecttion
                                           /// 0: disable 1: enable
    u32 reg_test_batdet               :2 ; /// battery detecttion test
    u32 reg_batdet                    :1 ; /// battery detecttion flag
    u32 reg_nobat_int                 :1 ; /// on battery detecttion interrupt
    u32 :24; /// [0x06]
    /* [0x07] */
    u32 reg_test_pm_0                 :16; /// test bias current, active high.
                                           /// [2:0]: Test POUT bias current
                                           /// [4:3]: Test NOUT bias current
                                           /// [5]: reserved
                                           /// [6]: reserved
                                           /// [17:7]: Reserved
    u32 :16; /// [0x07]
    u32 reg_test_pm_1                 :2 ; /// @see reg_test_pm_0
    u32 :30; /// [0x08]
    /* [0x09] */
    u32 reg_refgen_bias               :2 ; /// fine-tuning of bias current in refgen.
                                           /// 00: bias current ? 1
                                           /// 01: bias current ? 0.8
                                           /// 10: bias current ? 1.33
                                           /// 11: bias current ? 1
    u32 reg_en_iref2u_aud_rf          :1 ; /// 2u reference current for audio & rf enable. High active
    u32 reg_qs_en                     :1 ; /// quick-start enable. High active
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
    u32 reg_wait_time                 :10; /// set wait time for asura exit sleep mode
    u32 :22; /// [0x0C]
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
    u32 reg_en_rled                   :1 ; /// enable R PWM generation
                                           /// 0:disable 1: enable
    u32 reg_en_gled                   :1 ; /// f
    u32 reg_en_bled                   :1 ; /// enable B PWM generation
                                           /// 0:disable 1: enable
    u32 reg_repeat_rgb                :1 ; /// repeat rgb PWM pattern
                                           /// 0: no repeat  1: repeat
    u32 reg_en_key0                   :1 ; /// enable keypad0 PWM generation
                                           /// 0:disable 1: enable
    u32 reg_en_key1                   :1 ; /// enable keypad1 PWM generation
                                           /// 0:disable 1: enable
    u32 reg_mode_rgb                  :2 ; /// set the PWM  mode of RGB LED
                                           /// 00:pulse mode (default)
                                           /// 01: rotation mode
                                           /// 10-11: reserved
    u32 reserved                      :8 ; /// None
    u32 :16; /// [0x10]
    /* [0x11] */
    u32 reg_ton_rgb                   :2 ; /// RGB on time if bit reg_repeat_rgb =1. this bit wirks in conjunction with reg_mode_rgb
                                           /// reg_mode_rgb[1:0]=0
                                           /// 00: 102 ms (default)
                                           /// 01 203 ms
                                           /// 10: 406 ms
                                           /// 11: fully on(control with reg_en_rgb
                                           /// reg_mode_rgb[1:0]=1
                                           /// 00: 102 ms (default)
                                           /// 01 203 ms
                                           /// 10: 406 ms
                                           /// 11: 804 ms
    u32 reg_toff_rgb                  :2 ; /// RGB on time if bit reg_repeat_rgb =1. this bit wirks in conjunction with reg_mode_rgb
                                           /// reg_mode_rgb[1:0]=0
                                           /// 00: 406 ms (default)
                                           /// 01: 1602 ms
                                           /// 10: 3203 ms
                                           /// 11: 4804 ms
                                           /// reg_mode_rgb[1:0]=1
                                           /// 00: 0 ms (default)
                                           /// 01: 406 ms
                                           /// 10: 804 ms
                                           /// 11: 1602 ms
    u32 reg_ratio_r                   :4 ; /// set ratio of red LED PWM
                                           /// 0000: off (defalt)
                                           /// 0001: 1/15 on
                                           /// 0010: 2/15 on
                                           /// ?
                                           /// 1110: 14/15 on
                                           /// 1111: always on
    u32 reg_ratio_g                   :4 ; /// set ratio of green LED PWM
                                           /// 0000: off (defalt)
                                           /// 0001: 1/15 on
                                           /// 0010: 2/15 on
                                           /// ?
                                           /// 1110: 14/15 on
                                           /// 1111: always on
    u32 reg_ratio_b                   :4 ; /// set ratio of blue LED PWM
                                           /// 0000: off (defalt)
                                           /// 0001: 1/15 on
                                           /// 0010: 2/15 on
                                           /// ?
                                           /// 1110: 14/15 on
                                           /// 1111: always on
    u32 :16; /// [0x11]
    /* [0x12] */
    u32 reg_pwmp_key0                 :8 ; /// prescaler of keypad0 led PWM, input clock is 32KHz
                                           /// 00000000: divide by 1
                                           /// 00000001: divide by 2
                                           /// ????
                                           /// 11111111: divide by 256
    u32 reg_period_key0               :8 ; /// work with reg_pwmp_key0 set the PWM period
                                           /// Fkeypad0 = CLK/(reg_period_key0 * (reg_pwmp_key0+1)), CLK is 32KHz
                                           /// If reg_pwmp_key0 or reg_period_key0 is 0,the PWM output is 0
    u32 :16; /// [0x12]
    u32 :32; /// [0x13]
    /* [0x14] */
    u32 reg_cycle0_key0               :8 ; /// work with reg_cycle1_key0
                                           /// set the number of times a PWM shape is repeat.
                                           /// cycle0 and cycle1 are both 0 : PWM shape is repeat without iversion
                                           /// cycle0 and cycle1 is not 0  : a inverterd PWM shape is repeat
                                           /// cycle0 and cycle1 are both nonzero : PWM shape repeat cycle0 times the inverterd and repeated cycle1 times
    u32 reg_cycle1_key0               :8 ; /// same as cycle0
    u32 :16; /// [0x14]
    /* [0x15] */
    u32 reg_ratio_key0                :8 ; /// set the PWM output high ratio relative to reg_period_key0
                                           /// if ratio value >= period value ,PWM output is 1
                                           /// 00000000: PWM output 1
                                           /// 00000001: PWM output is high for 1 Fkeypad0 clock
                                           /// 00000010: PWM output is high for 2 Fkeypad0 clock
                                           /// ...............
                                           /// 11111111: PWM output is high for 255 Fkeypad0 clock
    u32 reg_ratio_key1                :8 ; /// set the PWM output high ratio relative to reg_period_key01
                                           /// if ratio value >= period value ,PWM output is 1
                                           /// 00000000: PWM output 1
                                           /// 00000001: PWM output is high for 1 Fkeypad0 clock
                                           /// 00000010: PWM output is high for 2 Fkeypad0 clock
                                           /// ...............
                                           /// 11111111: PWM output is high for 255 Fkeypad0 clock
    u32 :16; /// [0x15]
    /* [0x16] */
    u32 reg_pwmp_key1                 :8 ; /// prescaler of keypad0 led PWM, input clock is 32KHz
                                           /// 00000000: divide by 1
                                           /// 00000001: divide by 2
                                           /// ????
                                           /// 11111111: divide by 256
    u32 reg_period_key1               :8 ; /// work with reg_pwmp_key0 set the PWM period
                                           /// Fkeypad1 = CLK/(reg_period_key1 * (reg_pwmp_key1+1)), CLK is 32KHz
                                           /// If reg_pwmp_key1 or reg_period_key1 is 0,the PWM output is 0
    u32 :16; /// [0x16]
    /* [0x17] */
    u32 reg_cycle0_key1               :8 ; /// work with reg_cycle1_key0
                                           /// set the number of times a PWM shape is repeat.
                                           /// cycle0 and cycle1 are both 0 : PWM shape is repeat without iversion
                                           /// cycle0 and cycle1 is not 0  : a inverterd PWM shape is repeat
                                           /// cycle0 and cycle1 are both nonzero : PWM shape repeat cycle0 times the inverterd and repeated cycle1 times
    u32 reg_cycle1_key1               :8 ; /// same as cycle0
    u32 :16; /// [0x17]
    u32 :32; /// [0x18]
    u32 :32; /// [0x19]
    u32 :32; /// [0x1A]
    u32 :32; /// [0x1B]
    u32 :32; /// [0x1C]
    u32 :32; /// [0x1D]
    /* [0x1E] */
    u32 reg_pmu_spare0                :16; /// pmu spare register
    u32 :16; /// [0x1E]
    /* [0x1F] */
    u32 reg_pmu_spare1                :16; /// pmu spare register
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
                                           /// 1: power on
    u32 reg_mmp_piso                  :1 ; /// mmp_top power-fence isolation
    u32 reg_mmp_mtcmos_out            :1 ; /// mmp mtcmos out flag
    u32 :28; /// [0x30]
    /* [0x31] */
    u32 reg_imi_piso                  :8 ; /// imi_top power-fence isolation
    u32 reg_imi_mtcmos                :8 ; /// imi_top  mtcmos in
                                           /// 0: power off
                                           /// 1: power on
    u32 :16; /// [0x31]
    /* [0x32] */
    u32 reg_imi_mtcmos_out            :8 ; /// imi_top  mtcmos in
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
} KePmu_t;

#endif /*__KERNEL_PMU_H__*/
