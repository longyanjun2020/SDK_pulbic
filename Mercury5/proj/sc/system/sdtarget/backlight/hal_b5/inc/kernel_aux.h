/***************************************************************************
 *  kernel_aux.h
 *--------------------------------------------------------------------------
 *  Scope: AUX related definitions
 *
 ****************************************************************************/

#ifndef __KERNEL_AUX_H__
#define __KERNEL_AUX_H__

//#include "cpu_mem_map.hc"

/****************************************************************************/
/*        AUX  registers                           */
/****************************************************************************/
typedef struct AuxReg_s
{
    u32        adc_cfg;                //0x00
    u32        adc_test;               //0x04
    u32        adc_timing_cfg1;        //0x08
    u32        adc_timing_cfg2;        //0x0C
    u32        adc_timing_cfg_job;     //0x10
    u32        adc_job;                //0x14
    u32        adc_res0;               //0x18
    u32        adc_res1;               //0x1C
    u32        adc_res2;               //0x20
    u32        adc_res3;               //0x24
    u32        cycle_ctl;              //0x28
    u32        ts_ref1;                //0x2C
    u32        ts_ref2;                //0x30
    u32        free_run_tst;           //0x34
    u32        int_clear;              //0x38
    u32        int_mask;               //0x3C
    u32        int_force;              //0x40
    u32        int_source;             //0x44
    u32        int_sense;              //0x48
    u32        spare0;                 //0x4C
    u32        spare1;                 //0x50
    u32        spare2;                 //0x54
    u32        spare3;                 //0x58
    u32        pwm_trim_dim;           //0x5C
    u32        test_bus_cfg;           //0x60
    u32        spare_reg;              //0x64
    u32        spare_big3;             //0x68
    u32        pwm_wled_ctl;           //0x6C
    u32        pwm_wled_cnt;           //0x70
    u32        test_bus;               //0x74
    u32        sw_reset;               //0x78

} AuxReg_t;

#define INCENSE_ADC_CONFIG_AUXADC3_POS 12 ///< AUXADC3 Full Scale
#define INCENSE_ADC_CONFIG_AUXADC3_MSK (3<<INCENSE_ADC_CONFIG_AUXADC3_POS)
/*
00: 1.2V (default)
01: 1.5V
10: 2.0V
11: 2.8V
*/

#define INCENSE_ADC_CONFIG_AUXADC2_POS 10 ///< AUXADC1 Full Scale
#define INCENSE_ADC_CONFIG_AUXADC2_MSK (3<<INCENSE_ADC_CONFIG_AUXADC2_POS)
/*
00: 1.2V (default)
01: 1.5V
10: 2.0V
11: 2.8V
*/

#define INCENSE_ADC_CONFIG_AUXADC1_POS 8 ///< AUXADC1 Full Scale
#define INCENSE_ADC_CONFIG_AUXADC1_MSK (3<<INCENSE_ADC_CONFIG_AUXADC1_POS)
/*
00: 1.2V (default)
01: 1.5V
10: 2.0V
11: 2.8V
*/

#define INCENSE_ADC_CONFIG_AUXADC0_POS 6 ///< AUXADC0 Full Scale
#define INCENSE_ADC_CONFIG_AUXADC0_MSK (3<<INCENSE_ADC_CONFIG_AUXADC0_POS)
/*
00: 1.2V (default)
01: 1.5V
10: 2.0V
11: 2.8V
*/

#define INCENSE_ADC_CONFIG_AUXADC_PDZ (1<<5) ///< auxiliary ADC power down control

/**
 * @brief Register C6h, ADC_JOB_LIST (1)
 */
#define ADCJOB_0_POS                   10        /**< first ADC job channel selection */
#define ADCJOB_0_MSK                   (0x1F << ADCJOB_0_POS)

/**
 * @brief Register C8h, ADC_JOB_LIST (2)
 */
#define ADCJOB_3_POS                        10            /**< 4th ADC job channel selection */
#define ADCJOB_3_MSK                        (0x1F << ADCJOB_3_POS)

#define ADCJOB_2_POS                        5            /**< 3rd ADC job channel selection */
#define ADCJOB_2_MSK                        (0x1F << ADCJOB_2_POS)

#define ADCJOB_1_POS                        0            /**< 2nd ADC job channel selection */
#define ADCJOB_1_MSK                        (0x1F << ADCJOB_1_POS)

/**
 * @brief Register D2h, ...
 */
#define TSI_PDZ                             (1 << 6)    /**< power down touch screen driver */
/*
0: power down (default)
1: enable
*/
#define TSCURRCFG                           (1 << 5)    /**< set the touch screen measurement current */

#define INCENSE_AUX_CLK_SEL_POS                     3                    /**< select the aux_clk frequency */
#define INCENSE_AUX_CLK_SEL_MSK                     (3 << INCENSE_AUX_CLK_SEL_POS)

/**
 * @brief Register C0h, INCENSE_ADC_CONFIG
 */
#define AUX_ADC_CONFIG_EN_PEN_INTP  (1<<15) ///< enable touch screen pen interrupt
/*
1: disable (default)
0: enable
*/

#define AUX_ADC_CONFIG_EN_TOUCH_SCREEN (1<<14) ///< enable touch screen jobs
/*
If no touch screen is used, i.e. AUXADC 0-3 are normal ADC jobs, this bit applies to AUXADC 1-3 jobs. AUXADC0
job is always enabled. This bit has no effect on the ADC measurements of PM jobs.
0: no ADC conversion for touch screen jobs even if they are written in the job list
1: enable touch screen jobs if they are in the job list
*/

#define AUX_ADC_CONFIG_AUXADC3_POS 12 ///< AUXADC3 Full Scale
#define AUX_ADC_CONFIG_AUXADC3_MSK (3<<INCENSE_ADC_CONFIG_AUXADC3_POS)
/*
00: 1.2V (default)
01: 1.5V
10: 2.0V
11: 2.5V
*/

#define AUX_ADC_CONFIG_AUXADC2_POS 10 ///< AUXADC1 Full Scale
#define AUX_ADC_CONFIG_AUXADC2_MSK (3<<INCENSE_ADC_CONFIG_AUXADC2_POS)
/*
00: 1.2V (default)
01: 1.5V
10: 2.0V
11: 2.5V
*/

#define AUX_ADC_CONFIG_AUXADC1_POS 8 ///< AUXADC1 Full Scale
#define AUX_ADC_CONFIG_AUXADC1_MSK (3<<INCENSE_ADC_CONFIG_AUXADC1_POS)
/*
00: 1.2V (default)
01: 1.5V
10: 2.0V
11: 2.5V
*/

#define AUX_ADC_CONFIG_AUXADC0_POS 6 ///< AUXADC0 Full Scale
#define AUX_ADC_CONFIG_AUXADC0_MSK (3<<INCENSE_ADC_CONFIG_AUXADC0_POS)
/*
00: 1.2V (default)
01: 1.5V
10: 2.0V
11: 2.5V
*/

#define AUX_ADC_CONFIG_AUXADC_PDZ (1<<5) ///< auxiliary ADC power down control
/*
0: power down (default)
1: power up
*/

#define AUX_ADC_CONFIG_TS_INTERDLAY_EN (1<<4) ///< enable bit for touch screen inter delay
/*
0: do not wait inter delay after touch screen channel conversion (default)
1: wait inter delay after touch screen channel conversion
*/

#define AUX_ADC_CONFIG_CTN_INTERDLAY_EN (1<<3) ///< enable bit for CTN inter delay
/*
0: do not wait inter delay after CNT channel conversion (default)
1: wait inter delay after CNT channel conversion
*/

#define AUX_ADC_CONFIG_NORMAL_INTERDLAY_EN (1<<2) ///< enable bit for all ADC conversion jobs post delay other than touch screen and CTN, delay amount is set by ADC_CONV_INTER[7:0]
/*
0: do not wait inter delay after all ADC conversion (other than touch screen and CTN)
1: wait inter delay after all ADC conversion
*/

#define AUX_ADC_CONFIG_ADCSTARTEN (1<<1) ///< enable bit for ADCSTART bit
/*
0: start conversion immediately after jobs are written, no need to write ADCSTART bit (default)
1: wait for ADCSTART to initiate the conversion sequence
*/

#define AUX_ADC_CONFIG_ADCSTART (1<<0) ///< start bit for ADC conversion sequence, write a 1 to start. This bit is automatically cleared to 0 after all the ADC jobs are done.
/*
0: no conversion (default)
1: start a conversion sequence
*/

/**
 * @brief Register C4h, ADC_TIMING_CFG
 */
#define AUX_ADC_CONV_DELAY_POS         8         /**< ADC conversion delay register for temperature channel measurement with CTN */
#define AUX_ADC_CONV_DELAY_MSK         (0xFF<<AUX_ADC_CONV_DELAY_POS)

#define AUX_ADC_CONV_INTER_MSK         0x00FF    /**< ADC conversion internal control */

/**
 * @brief Register C8h, ADC_TIMING_CFG and ADC_JOB_LIST
 */
#define AUX_ADCJOB_0_POS                   10        /**< first ADC job channel selection */
#define AUX_ADCJOB_0_MSK                   (0x1F << ADCJOB_0_POS)

#ifdef __INCENSE_1__
#define AUX_TOUCH_SCRN_DELAY_MSK           0x03FF    /**< ADC conversion register for touch screen channel */
#else // __INCENSE_1__
#define AUX_TOUCH_SCRN_ADC_CONV_DELAY_MSK  0x03FF    /**< ADC conversion pre delay for touch screen channel
                                                    delay = TOUCH_SCRN_DELAY/ADC_CONVERSION_CLK */
#endif // __INCENSE_1__

/**
 * @brief Register CAh, ADC_JOB_LIST
 */
#define AUX_ADCJOB_3_POS                   10        /**< 4th ADC job channel selection */
#define AUX_ADCJOB_3_MSK                   (0x1F << ADCJOB_3_POS)

#define AUX_ADCJOB_2_POS                   5         /**< 3rd ADC job channel selection */
#define AUX_ADCJOB_2_MSK                   (0x1F << ADCJOB_2_POS)

#define AUX_ADCJOB_1_POS                   0         /**< 2nd ADC job channel selection */
#define AUX_ADCJOB_1_MSK                   (0x1F << ADCJOB_1_POS)


#define AUX_ADC_AUXADC0                    0x7  ///< Aux ADC 0
#define AUX_ADC_AUXADC1                    0x8  ///< Aux ADC 1
#define AUX_ADC_AUXADC2                    0x9  ///< Aux ADC 2
#define AUX_ADC_AUXADC3                    0xA ///< Aux ADC 3
#define AUX_ADC_TOUCH_SCREEN_X_RES         0xB ///< Touch Screen X resistance
#define AUX_ADC_TOUCH_SCREEN_Y_RES         0xC ///< Touch Screen Y resistance
#define AUX_ADC_TOUCH_SCREEN_X_LOC         0xD ///< Touch Screen X location
#define AUX_ADC_TOUCH_SCREEN_Y_LOC         0xE ///< Touch Screen Y location
#define AUX_ADC_TOUCH_SCREEN_Z1_LOC        0xF ///< Touch Screen Z1 location
#define AUX_ADC_TOUCH_SCREEN_Z2_LOC        0x10///< Touch Screen Z2 location


/**
 * @brief Register CCh, ADC_RES0
 */
#define AUX_ADCRES0_MSK                 0x03FF    /**< ADCJOB_0 result */

/**
 * @brief Register CEh, ADC_RES1
 */
#define AUX_ADCRES1_MSK                 0x03FF    /**< ADCJOB_1 result */

/**
 * @brief Register 10h, ADC_RES2
 */
#define AUX_ADCRES2_MSK                 0x03FF    /**< ADCJOB_2 result */

/**
 * @brief Register 12h, ADC_RES3
 */
#define AUX_ADCRES3_MSK                 0x03FF    /**< ADCJOB_3 result */


/**
 * @brief Register D2h, ...
 */
#define AUX_TSI_PDZ                         (1 << 6)    /**< power down touch screen driver */
/*
0: power down (default)
1: enable
*/
#define AUX_TSCURRCFG                       (1 << 5)    /**< set the touch screen measurement current */

#define INCENSE_AUX_CLK_SEL_POS                     3                    /**< select the aux_clk frequency */
#define INCENSE_AUX_CLK_SEL_MSK                     (3 << INCENSE_AUX_CLK_SEL_POS)

#define CYCLE_CONTROL_POS                   0                    /**< each one_shot pulse will keep (ONE_SHOT_CYCLE+1) aux_clk */
#define CYCLE_CONTROL_MSK                   (7 << CYCLE_CONTROL_POS)

//CYCLE_CTRL Register
#define CYCLE_CTRL_SHOT_CYCLE_POS           0
#define CYCLE_CTRL_SHOT_CYCLE_MSK           ((u32)7<<CYCLE_CTRL_SHOT_CYCLE_POS)
#define CYCLE_CTRL_AUX_CLK_SEL_POS          3
#define CYCLE_CTRL_AUX_CLK_SEL_MSK          ((u32)7<<CYCLE_CTRL_AUX_CLK_SEL_POS)
#define CYCLE_CTRL_TSI_IS                   ((u32)1<<5)
#define CYCLE_CTRL_PD_TSI                   ((u32)1<<6)
#define CYCLE_CTRL_CLK52_SEL_PLL21_DIV_6    ((u32)1<<7)
#define CYCLE_CTRL_CLK78_SEL_PLL21_DIV_4    ((u32)1<<8)
#define CYCLE_CTRL_CLK104_SEL_PLL21_DIV_3   ((u32)1<<9)
#define CYCLE_CTRL_DDRSEL_POS               10
#define CYCLE_CTRL_DDRSEL_MSK               ((u32)3<<CYCLE_CTRL_DDRSEL_POS)
#define CYCLE_CTRL_DDRSEL_PLL1_13M          0
#define CYCLE_CTRL_DDRSEL_PLL1_26M          1
#define CYCLE_CTRL_DDRSEL_PLL21_13M         2
#define CYCLE_CTRL_DDRSEL_PLL21_26M         3

//FREERUN_TST Register
#define FREE_RUN_CFG_POS                    0
#define FREE_RUN_CFG_MSK                    ((u32)0x007F<<FREE_RUN_CFG_POS)
#define FREE_RUN_MUXN_SEL_POS               7
#define FREE_RUN_MUXN_SEL_MSK               ((u32)0x0003<<FREE_RUN_MUXN_SEL_POS)
#define FREE_RUN_I2E_CLK_26M_EN             (0x01UL<<9)
#define FREE_RUN_I2E_CLK_52M_EN             (0x01UL<<10)
#define FREE_RUN_I2E_CLK_78M_EN             (0x01UL<<11)
#define FREE_RUN_I2E_CLK_104M_EN            (0x01UL<<12)
#define FREE_RUN_I2E_CLK_130M_EN            (0x01UL<<13)
#define FREE_RUN_I2E_CLK_DDR_EN             (0x01UL<<14)
#define FREE_RUN_I2E_CLK_RFID_REF           (0x01UL<<15)


#define AUX_CLK_SEL_POS                     3                    /**< select the aux_clk frequency */
#define AUX_CLK_SEL_MSK                     (3 << INCENSE_AUX_CLK_SEL_POS)

#define AUX_CYCLE_CONTROL_POS               0                    /**< each one_shot pulse will keep (ONE_SHOT_CYCLE+1) aux_clk */
#define AUX_CYCLE_CONTROL_MSK               (7 << CYCLE_CONTROL_POS)

//CYCLE_CTRL Register
#define AUX_CYCLE_CTRL_SHOT_CYCLE_POS       0
#define AUX_CYCLE_CTRL_SHOT_CYCLE_MSK       ((u32)7<<CYCLE_CTRL_SHOT_CYCLE_POS)
#define AUX_CYCLE_CTRL_AUX_CLK_SEL_POS      3
#define AUX_CYCLE_CTRL_AUX_CLK_SEL_MSK      ((u32)7<<CYCLE_CTRL_AUX_CLK_SEL_POS)
#define AUX_CYCLE_CTRL_TSI_IS               ((u32)1<<5)
#define AUX_CYCLE_CTRL_PD_TSI               ((u32)1<<6)

//FREERUN_TST Register
#define AUX_FREE_RUN_CFG_POS            0
#define AUX_FREE_RUN_CFG_MSK            ((u32)0x007F<<FREE_RUN_CFG_POS)
#define AUX_FREE_RUN_MUXN_SEL_POS       7
#define AUX_FREE_RUN_MUXN_SEL_MSK       ((u32)0x0003<<FREE_RUN_MUXN_SEL_POS)

//INT_CLEAR Register
#define AUX_INT_CLEAR_PENDET            ((u32)1<<0)
#define AUX_INT_CLEAR_ADCDONE           ((u32)1<<1)

//INT_MASK Register
#define AUX_INT_MASK_PENDET             ((u32)1<<0)
#define AUX_INT_MASK_ADCDONE            ((u32)1<<1)

//INT_FORCE Register
#define AUX_INT_FORCE_PENDET            ((u32)1<<0)
#define AUX_INT_FORCE_ADCDONE           ((u32)1<<1)

//INT_SOURCE Register
#define AUX_INT_SOURCE_PENDET           ((u32)1<<0)
#define AUX_INT_SOURCE_ADCDONE          ((u32)1<<1)

//INT_SENSE Register
#define AUX_INT_SENSE_PENDET            ((u32)1<<0)
#define AUX_INT_SENSE_ADCDONE           ((u32)1<<1)

//PWM_TRIM_DIM Register
#define AUX_PWM_TRIM
#define AUX_PWM_DIM
#define AUX_PWM_DIM_POS               5
#define AUX_PWM_DIM_MSK               (7 << AUX_PWM_DIM_POS)

//TEST_BUS_CFG Register
#define AUX_TEST_BUSEN
#define AUX_TEST_SEL
#define AUX_TEST_CLK_EN
#define AUX_TEST_REFSEL_LSB
#define AUX_TEST_REFSEL_BIT2
#define AUX_TEST_MUXN_BIT2

//spare_reg Register

//spare_big3 Register
#define AUX_RCTRL_POS                   8 
#define AUX_RCTRL_MASK                  (7 << AUX_RCTRL_POS)

//PWM_WLED_CTRL Register
#define AUX_PWM_WLED_CTRL

#define AUX_WLED_PWM_EN          1       // wled internal PWM enable
// 0: disable  1: enable

#define AUX_WLED_PWM_PERIOD_MASK      1<<1    // wled PWM Ferequence select (0:200Hz 1:100Hz)
#define AUX_WLED_PWM_PERIOD_100HZ     1<<1
#define AUX_WLED_PWM_PERIOD_200HZ     0<<1

#define AUX_WLED_PWM_RATIO_POS   2
#define AUX_WLED_PWM_RATIO_MSK   0x3F<<AUX_WLED_PWM_RATIO_POS
// wled PWM Duty Control
// 0000:OFF
// 0001:6.7%
// 001013.4%,........,1111:100%

#define AUX_WLED_THE_SAME_PERIOD 1<<13    // Use the same PWM from PWM1

// 0: Use seperated (default)  1: Use the same PWM from PWM1

#define AUX_WLED_USE_EXT_PWM     1<<14    // wled use external PWM
// 0: use internal   1:use external

#define AUX_WLED_FAST_SYNC_MODE 1<<15 //0: Disable / 1: Enable Fast synchronize switch for WLED ratio


#define AUX_WLED_1_EN            1<<8    // default : 1'b0

#define AUX_WLED_1_GPO_EN        1<<0    // default : 1'b0
#define AUX_WLED_2_GPO_EN        1<<9    // default : 1'b0
#define AUX_WLED_3_GPO_EN        1<<10   // default : 1'b0
#define AUX_WLED_4_GPO_EN        1<<11   // default : 1'b0

#define AUX_WLED_1_GPO_CTRL      1<<12   // default : 1'b0
#define AUX_WLED_2_GPO_CTRL      1<<13   // default : 1'b0
#define AUX_WLED_3_GPO_CTRL      1<<14   // default : 1'b0
#define AUX_WLED_4_GPO_CTRL      1<<15   // default : 1'b0

//PWM_WLED_CNT Register

extern volatile AuxReg_t* const g_ptAuxReg;

#endif // __KERNEL_AUX_H__

