/**
 * \file incense_reg.h
 * \brief Incense register definition
 */

#ifndef __INCENSE_REG_H__
#define __INCENSE_REG_H__

#include "stdcomp.h" 


#if 0
typedef struct {
    union {
        u16 u16_val;
        struct {
            u16 areg_en_vabbrf	: 1;    ///< ABBRF LDO enable bit in active mode, active high
            u16 areg_en_vaux	: 1;    ///< AUX LDO enable bit in active mode , active high
            u16 areg_en_vabbaud	: 1;    ///< ABBAUD LDO enable bit in active mode , active high
            u16 areg_en_va	    : 1;    ///< TCXO LDO enable bit in active mode , active high
            u16 areg_en_vdigrf	: 1;    ///< DIGRF LDO enable bit in active mode , active high
            u16 areg_en_vdbbio	: 1;    ///< DBBIO LDOenable bit in active mode , active high
            u16 areg_en_vmmpio	: 1;    ///< MMPIO LOD enable bit in active mode , active high
            u16 areg_en_per1    : 1;    ///< PERIPHERAL1 LDO enable bit in active mode , active high
            u16 areg_en_per2    : 1;    ///< PERIPHERAL2 LDO enable bit in active mode, active high
            u16 areg_en_per3    : 1;    ///< PERIPHERAL3 LDO enable bit in active mode, active high
            u16 areg_en_per4    : 1;    ///< PERIPHERAL4 LDO enable bit in active mode, active high
            u16 areg_en_mmp0    : 1;    ///< MMP0 in Athena enable bit in active mode , active high
            u16 areg_en_mmp1    : 1;    ///< MMP1 in Athena enable bit in active mode , active high
            u16 areg_en_rfdig	: 1;    ///< RF digital power gate enable bit in active mode , active high
            u16 areg_en_auddig	: 1;    ///< AUDIO digital power gate enable bit in active mode 
            u16 areg_en_auxdig	: 1;    ///< AUX digital power gate enable bit in active mode 
        } bits ;
    } ldo_en_act;
    union {
        u16 u16_val;
        struct {
            u16 sreg_en_vabbrf	: 1; ///< ABBRF LDO enable bit in standby mode, active high
            u16 sreg_en_vaux	: 1; ///< AUX LDO enable bit in standby mode , active high
            u16 sreg_en_vabbaud	: 1; ///< ABBAUD LDO enable bit in standby mode , active high
            u16 sreg_en_va	    : 1; ///< TCXO LDO enable bit in standby mode , active high
            u16 sreg_en_vdigrf	: 1; ///< DIGRF LDO enable bit in standby mode , active high
            u16 sreg_en_vdbbio	: 1; ///< DBBIO LDOenable bit in standby mode , active high
            u16 sreg_en_vmmpio	: 1; ///< MMPIO LOD enable bit in standby mode , active high
            u16 sreg_en_per1	: 1; ///< PERIPHERAL1 LDO enable bit in standby mode , active high
            u16 sreg_en_per2	: 1; ///< PERIPHERAL2 LDO enable bit in standby mode, active high
            u16 sreg_en_per3	: 1; ///< PERIPHERAL3 LDO enable bit in standby mode, active high
            u16 sreg_en_per4	: 1; ///< PERIPHERAL4 LDO enable bit in standby mode, active high
            u16 sreg_en_mmp0	: 1; ///< MMP0 in Athena enable bit in standby mode , active high
            u16 sreg_en_mmp1	: 1; ///< MMP1 in Athena enable bit in standby mode , active high
            u16 sreg_en_rfdig	: 1; ///< RF digital power gate enable bit in standby mode , active high
            u16 sreg_en_auddig	: 1; ///< AUDIO digital power gate enable bit in standby mode 
            u16 reserved        : 1;		
        } bits ;
    } ldo_en_sdb;
    union {
        u16 u16_val;
        struct {
           u16 areg_lvl1_vdig	: 2;  ///< Digital LDO level config in active mode. 00,1.2v; 01,1.25v;10,1.3v;11,1.1v
           u16 areg_lvl1_vabbrf : 2;  ///< ABBRF LDO level config in active mode. 00,1.8v; 01,2.28v; 10, 2.5v; 11,2.8v;
           u16 areg_lvl1_vaux	: 2;  ///< AUX LDO level config in active mode. 00,1.8v; 01,2.28v; 10, 2.5v; 11,2.8v;
           u16 areg_lvl1_vabbaud: 2;  ///< ABBAUD LDO level config in active mode. 00,1.8v; 01,2.28v; 10, 2.5v; 11,2.8v;
           u16 areg_lvl1_va	    : 2;  ///< TCXO LDO level config in active mode. 00,1.5v; 01,1.8v; 10, 2.8v; 11,2.9v;
           u16 areg_lvl1_vsim	: 2;  ///< SIM LDO level config in active mode.  00,1.5v; 01,1.8v; 10, 2.8v; 11,2.9v;
           u16 areg_lvl1_vper1	: 2;  ///< PERIPHERAL1 LDO  config in active mode.  00,1.5v;01,1.8v;10,2.5v;11,2.8v
           u16 areg_lvl1_vper2	: 2;  ///< PERIPHERAL2 LDO level config in active mode. 00,1.5v;01,1.8v;10,2.5v;11,2.8v
        } bits ;
    } ldo_lvl1_act;
    union {
        u16 u16_val;
        struct {
           u16 areg_lvl2_per3 : 2;    ///< PERIPHERAL3 level config in active mode. 00,1.5v;01,1.8v;10,2.5v;11,2.8v
           u16 areg_lvl2_per4 : 2;    ///< PERIPHERAL4 level config in active mode. 00,1.5v;01,1.8v;10,2.5v;11,2.8v
           u16 sreg_lvl2_per3 : 2;    ///< PERIPHERAL3 level config in standby mode
           u16 sreg_lvl2_per4 : 2;    ///< PERIPHERAL4 level config in standby mode
           u16 reserved	;		
        } bits ;
    } ldo_lvl2;
    union {
        u16 u16_val;
        struct {
           u16 sreg_lvl1_vdig	 : 2;   ///< Digital LDO level config in standby mode. 00,1.2v; 01,1.25v;10,1.3v;11,1.1v
           u16 sreg_lvl1_vabbrf  : 2;   ///< ABBRF LDO level config in standby mode. 00,1.8v; 01,2.28v; 10, 2.5v; 11,2.8v;
           u16 sreg_lvl1_vaux	 : 2;   ///< AUX LDO level config in standby mode. 00,1.8v; 01,2.28v; 10, 2.5v; 11,2.8v;
           u16 sreg_lvl1_vabbaud : 2;   ///< ABBAUD LDO level config in standby mode. 00,1.8v; 01,2.28v; 10, 2.5v; 11,2.8v;
           u16 sreg_lvl1_va	     : 2;   ///< TCXO LDO level config in standby mode. 00,1.5v; 01,1.8v; 10, 2.8v; 11,2.9v;
           u16 sreg_lvl1_vsim	 : 2;   ///< SIM LDO level config in standby mode.  00,1.5v; 01,1.8v; 10, 2.8v; 11,2.9v;
           u16 sreg_lvl1_vper1	 : 2;   ///< PERIPHERAL1 LDO  config in standby mode.  00,1.5v;01,1.8v;10,2.5v;11,2.8v
           u16 sreg_lvl1_vper2	 : 2;   ///< PERIPHERAL2 LDO level config in standby mode. 00,1.5v;01,1.8v;10,2.5v;11,2.8v
        } bits ;
    } ldo_lvl1_sdb;
    union {
        u16 u16_val;
        struct {
           u16 areg_lq_vdig     : 1;   ///< DIG LDO enter low quiesent mode in active mode,active high
           u16 areg_lq_vabbrf   : 1;   ///< ABBRF LDO enter low quiesent mode in active mode,active high
           u16 areg_lq_vaux	    : 1;   ///< AUX LDO enter low quiesent mode in active mode,active high
           u16 areg_lq_vabbaud	: 1;   ///< ABBADU LDO enter low quiesent mode in active mode,active high
           u16 areg_lq_va	    : 1;   ///< TCXO LDO enter low quiesent mode in active mode,active high
           u16 areg_lq_vdigrf   : 1;   ///< DIGRF LDO enter low quiesent mode in active mode,active high
           u16 areg_lq_vsim	    : 1;   ///< SIM LDO enter low quiesent mode in active mode,active high
           u16 areg_lq_vdbbio	: 1;   ///< DBBIO LDO enter low quiesent mode in active mode,active high
           u16 areg_lq_mmpio	: 1;   ///< MMPIO LDO enter low quiesent mode in active mode,active high
           u16 areg_lq_per1     : 1;   ///< PERIPHERAL1 LDO enter low quiesent mode in active mode,active high
           u16 areg_lq_per2	    : 1;   ///< PERIPHERAL2 LDO enter low quiesent mode in active mode,active high
           u16 areg_lq_per3	    : 1;   ///< PERIPHERAL3 LDO enter low quiesent mode in active mode,active high
           u16 areg_lq_per4     : 1;   ///< PERIPHERAL4 LDO enter low quiesent mode in active mode,active high
           u16 reserved	: 3;		
        } bits ;
    } ldo_lq_act;
    union {
        u16 u16_val;
        struct {
           u16 sreg_lq_vdig     : 1;  ///< DIG LDO enter low quiesent mode in active mode,active high
           u16 sreg_lq_vabbrf   : 1;  ///< ABBRF LDO enter low quiesent mode in active mode,active high
           u16 sreg_lq_vaux	    : 1;  ///< AUX LDO enter low quiesent mode in active mode,active high
           u16 sreg_lq_vabbaud	: 1;  ///< ABBADU LDO enter low quiesent mode in active mode,active high
           u16 sreg_lq_va       : 1;  ///< TCXO LDO enter low quiesent mode in active mode,active high
           u16 sreg_lq_vdigrf	: 1;  ///< DIGRF LDO enter low quiesent mode in active mode,active high
           u16 sreg_lq_vsim	    : 1;  ///< SIM LDO enter low quiesent mode in active mode,active high
           u16 sreg_lq_vdbbio	: 1;  ///< DBBIO LDO enter low quiesent mode in active mode,active high
           u16 sreg_lq_vmmpio	: 1;  ///< MMPIO LDO enter low quiesent mode in active mode,active high
           u16 sreg_lq_per1	    : 1;  ///< PERIPHERAL1 LDO enter low quiesent mode in active mode,active high
           u16 sreg_lq_per2	    : 1;  ///< PERIPHERAL2 LDO enter low quiesent mode in active mode,active high
           u16 sreg_lq_per3	    : 1;  ///< PERIPHERAL3 LDO enter low quiesent mode in active mode,active high
           u16 sreg_lq_per4	    : 1;  ///< PERIPHERAL4 LDO enter low quiesent mode in active mode,active high
           u16 reserved	: 3;		
        } bits ;
    } ldo_lq_sdb;
    union {
        u16 u16_val;
        struct {
           u16 gpio7in  : 1;  ///< GPIO7 INPUT REGISTER (READ ONLY)
           u16 gpio6in  : 1;  ///< GPIO6 INPUT REGISTER (READ ONLY)
           u16 gpio5in  : 1;  ///< GPIO5 INPUT REGISTER (READ ONLY)
           u16 gpio4in  : 1;  ///< GPIO4 INPUT REGISTER (READ ONLY)
           u16 gpio3in  : 1;  ///< GPIO3 INPUT REGISTER (READ ONLY)
           u16 gpio2in  : 1;  ///< GPIO2 INPUT REGISTER (READ ONLY)
           u16 gpio1in  : 1;  ///< GPIO1 INPUT REGISTER (READ ONLY)
           u16 gpio0in  : 1;  ///< GPIO0 INPUT REGISTER (READ ONLY)
           u16 gpio7out : 1;  ///< GPIO7 OUTPUT REGISTER
           u16 gpio6out : 1;  ///< GPIO6 OUTPUT REGISTER
           u16 gpio5out : 1;  ///< GPIO5 OUTPUT REGISTER
           u16 gpio4out : 1;  ///< GPIO4 OUTPUT REGISTER
           u16 gpio3out : 1;  ///< GPIO3 OUTPUT REGISTER
           u16 gpio2out : 1;  ///< GPIO2 OUTPUT REGISTER
           u16 gpio1out : 1;  ///< GPIO1 OUTPUT REGISTER
           u16 gpio0out : 1;  ///< GPIO0 OUTPUT REGISTER
        } bits ;
    } gpio_data;
    union {
        u16 u16_val;
        struct {
            u16 gpio7c         : 1; ///< GPIO7 IN/OUT CONTROL (0: OUTPUT, 1: INPUT)
            u16 gpio6c         : 1; ///< GPIO6 IN/OUT CONTROL (0: OUTPUT, 1: INPUT)
            u16 gpio5c         : 1; ///< GPIO5 IN/OUT CONTROL (0: OUTPUT, 1: INPUT)
            u16 gpio4c         : 1; ///< GPIO4 IN/OUT CONTROL (0: OUTPUT, 1: INPUT)
            u16 gpio3c         : 1; ///< GPIO3 IN/OUT CONTROL (0: OUTPUT, 1: INPUT)
            u16 gpio2c         : 1; ///< GPIO2 IN/OUT CONTROL (0: OUTPUT, 1: INPUT)
            u16 gpio1c         : 1; ///< GPIO1 IN/OUT CONTROL (0: OUTPUT, 1: INPUT)
            u16 gpio0c         : 1; ///< GPIO0 IN/OUT CONTROL (0: OUTPUT, 1: INPUT)
            u16 gpio7cfg       : 1; ///< GPIO7 CONFIGURATION (0: GENERAL, 1: KEYPAD1)
            u16 gpio6cfg       : 1; ///< GPIO6 CONFIGURATION (0: GENERAL, 1: KEYPAD0)
            u16 standbyen      : 1; ///< ENABLE STANDBYB port, active high
            u16 keyoff_en      : 1; ///< ENABLE KEY OFF (5s forced shut-down) OPERATION,active high
            u16 softstart_en   : 1; ///< softstart mode enable.  Active high.
            u16 reserved : 3;		
        } bits ;
    } gpio_cfg;
    union {
        u16 u16_val;
        struct {
            u16 ibattype    : 2; ///< "BATTERY TYPE DETECT CURRENT SELECT. 2'b00: 1uA, 2'b01: 5uA; 2'b10: 10uA; 2'b11: 20uA"
            u16 ibattemp    : 2; ///< "BATTERY TEMP DETECT CURRENT SELECT. 2'b00: 1uA, 2'b01: 5uA; 2'b10: 10uA; 2'b11: 20uA"
            u16 reftm       : 2; ///< TEST MODE OF REFERENCE GENERATOR. detail
            u16 regwr_en    : 1; ///< REGISTER WRITE ENABLE (FROM 26M TO 32K). 1, open 32k to 26M sync. 0, close
            u16 en_rgb      : 1; ///< ENABLE RGB LED, active high
            u16 repeat_rgb  : 1; ///< REPEAT RGB PWM OPERATION, active high
            u16 en_key0     : 1; ///< ENABLE KEYPAD 0, active high
            u16 en_key1     : 1; ///< ENABLE KEYPAD 1, active high
            u16 mode_rgb    : 2; ///< 00:pulse mode; 01:roation mode;10-11 reserved
            u16 bst_en      : 1; ///< boost enable, active high
            u16 reserved : 2;		
        } bits ;
    } misc1;
    union {
        u16 u16_val;
        struct {
            u16 wd_timeout : 12;  ///< WATCHDOG TIMEOUT THRESHOLD. 1LSB for 30 ms
            u16 wd_en      : 1;   ///< WATCHDOG ENABLE, active high
            u16 wd_clear   : 1;   ///< WATCHDOG CLEAR (WRITE 1 to clear watch dog counter). 
            u16 abbint_pol : 1;   ///< ABBINT POLARITY CONTROL.  0, interrupt pin is active high; 0, active low
            u16 reserved : 1;		
        } bits ;
    } wd;
    union {
        u16 u16_val;
        struct {
            u16 ton_rgb    : 2;  ///< W/R	"TON_RGB[1:0]: RGB on time if bit REPEAT_RGB=1. This bit works in conjunction with MODE_RGB bits.
                                 /*
                                 MODE_RGB[1:0]=0
                                 00: 102 ms (default)  01: 203 ms   10: 406 ms  11: fully on (control with EN_RGB bit)
                                 MODE_RGB[1:0]=1
                                 00: 102 ms  01: 203 ms   10: 406 ms   11: 804 ms  " 
                                 */
            u16 toff_rgb    : 2; ///< "TOFF_RGB[1:0]: RGB off time if bit REPEAT_RGB=1. This bit works in conjunction with MODE_RGB bits
                                 /*
                                 MODE_RGB[1:0]=0
                                 00: 406 ms (default)   01: 1602 ms  10: 3203 ms  11: 4804 ms
                                 MODE_RGB[1:0]=1
                                 00: 0 ms    01: 406 ms  10: 804 ms   11: 1602 ms"
                                 */
            u16 ratio_r    : 4;  ///< W/R	"ratio of red LED PWM
                                 /*
                                 0000: off (default)    0001: 1/15 on   0010: 2/15 on   0011: 3/15 on
                                 0100: 4/15 on            0101: 5/15 on    0110: 6/15 on  0111: 7/15 on
                                 1000: 8/15 on           1001: 9/15 on    1010: 10/15 on 1011: 11/15 on
                                 1100: 12/15 on         1101: 13/15 on   1110: 14/15 on  1111: always on"
                                 */
            u16 ratio_g    : 4;  ///< W/R	"ratio of green LED PWM
                                 /*
                                 0000: off (default)   0001: 1/15 on    0010: 2/15 on    0011: 3/15 on
                                 0100: 4/15 on           0101: 5/15 on    0110: 6/15 on    0111: 7/15 on
                                 1000: 8/15 on           1001: 9/15 on    1010: 10/15 on  1011: 11/15 on
                                 1100: 12/15 on         1101: 13/15 on  1110: 14/15 on  1111: always on"
                                 */
            u16 ratio_b    : 4;  ///< W/R	"ratio of blue LED PWM
                                 /*
                                 0000: off (default)    0001: 1/15 on    0010: 2/15 on     0011: 3/15 on
                                 0100: 4/15 on            0101: 5/15 on    0110: 6/15 on     0111: 7/15 on
                                 1000: 8/15 on            1001: 9/15 on    1010: 10/15 on   1011: 11/15 on
                                 1100: 12/15 on          1101: 13/15 on  1110: 14/15 on   1111: always on"
                                 */
        } bits ;
    } rgb_cfg;
    union {
        u16 u16_val;
        struct {
            u16 pwmp_key0 : 8;   ///< "PWMP_KEY0[7:0]: prescaler of KEYPAD0 LED PWM, input clock is 32KHz
                                 /*
                                 00000000: divide by 1
                                 00000001: divide by 2
                                 ??
                                 11111111: divide by 256"
                                 */
            u16 period_key0 : 8; ///< PERIOD_KEY0[7:0]: this register together with PWMP_KEY0 set the PWM period of KEYPAD0 LED.   Fkeypad0 = CLK/(PERIOD_KEY0*(PWMP_KEY0+1)), CLK is 32KHz. If PWMP_KEY0 or PERIOD_KEY0 is equal to 0, the PWM output is equal to 0.
                  } bits ;
    } pwd_cfg1;
    union {
        u16 u16_val;
        struct {
            u16 ratio_key0 : 8; ///< "RATIO_KEY0[7:0]: set the PWM output high ratio relative to PERIOD_KEY0 for KEYPAD0 LED
                                /*
                                If RATIO_KEY0 is equal to or greater than PERIOD_KEY0, PWM output is 1
                                00000000: PWM output is 0
                                00000001: PWM output is high for 1 Fkeypad0 clock (see PERIOD_KEY0 definition)
                                00000010: PWM output is high for 2 Fkeypad0 clocks
                                ??
                                11111111: PWM output is high for 255 Fkeypad0 clocks"
                                */
            u16 cycle0_key0 : 8;    ///< "CYCLE0_KEY0[7:0]: this register together with CYCLE1_KEY0 set the number of times a PWM shape is repeated.
                                    /*
                                    If CYCLE0_KEY0 and CYCLE1_KEY0 are both 0, then a PWM shape is repeated without inversion.
                                    If CYCLE0_KEY0 is 0 and CYCLE1_KEY0 is not 0, then an inverted PWM shape is repeated. If CYCLE0_KEY0 and
                                    CYCLE1_KEY0 are both nonzero, then a PWM shape is repeated CYCLE0_KEY0 times, then inverted and repeated
                                    CYCLE1_KEY0 times."
                                    */
        } bits ;
    } pwd_cfg2;
    union {
        u16 u16_val;
        struct {
            u16 cycle1_key0 : 8; ///< "CYCLE1_KEY0[7:0]: this register together with CYCLE0_KEY0 set the number of times a PWM shape is repeated.
                                 /*
                                    If CYCLE0_KEY0 and CYCLE1_KEY0 are both 0, then a PWM shape is repeated without inversion. If
                                    CYCLE0_KEY0 is 0 and CYCLE1_KEY0 is not 0, then an inverted PWM shape is repeated. If CYCLE0_KEY0 and
                                    CYCLE1_KEY0 are both nonzero, then a PWM shape is repeated CYCLE0_KEY0 times, then inverted and repeated
                                    CYCLE1_KEY0 times."
                                 */
            u16 pwmp_key1 : 8; ///< "PWMP_KEY1[7:0]: prescaler of KEYPAD1 LED PWM, input clock is 32KHz
                                 /*
                                    00000001: divide by 2
                                    ??
                                    11111111: divide by 256
                                                         */
        } bits ;
    } pwd_cfg3;
    union {
        u16 u16_val;
        struct {
            u16 period_key1 : 8; ///< "PERIOD_KEY1[7:0]: this register together with PWMP_KEY1 set the PWM period of KEYPAD1 LED
                                    /*
                                    Fkeypad1 = CLK/(PERIOD_KEY1*(PWMP_KEY1+1)), CLK is 32KHz. If PWMP_KEY1 or PERIOD_KEY1 is equal
                                    to 0, the PWM output is equal to 0."
                                    */
            u16 ratio_key1 : 8; ///< "RATIO_KEY1[7:0]: set the PWM output high ratio relative to PERIOD_KEY1 for KEYPAD1 LED
                                    /*
                                    If RATIO_KEY1 is equal to or greater than PERIOD_KEY1, PWM output is 1
                                    00000000: PWM output is 0
                                    00000001: PWM output is high for 1 Fkeypad1 clock (see PERIOD_KEY1 definition)
                                    00000010: PWM output is high for 2 Fkeypad1 clocks
                                    ??
                                    11111111: PWM output is high for 255 Fkeypad1 clocks
                                    */
        } bits ;
    } pwd_cfg4;
    union {
        u16 u16_val;
        struct {
            u16 cycle0_key1 : 8; ///< "CYCLE0_KEY1[7:0]: this register together with CYCLE1_KEY01set the number of times a PWM shape is repeated.
                                    /*
                                    If CYCLE0_KEY1 and CYCLE1_KEY1 are both 0, then a PWM shape is repeated without inversion. If
                                    CYCLE0_KEY1 is 0 and CYCLE1_KEY1 is not 0, then an inverted PWM shape is repeated. If CYCLE0_KEY1 and
                                    CYCLE1_KEY1 are both nonzero, then a PWM shape is repeated CYCLE0_KEY1 times, then inverted and repeated
                                    CYCLE1_KEY1 times.
                                    */
            u16 cycle1_key1 : 8; ///< W/R	CYCLE1_KEY1[7:0]: see CYCLE0_KEY1[7:0] description
        } bits ;
    } pwd_cfg5;
    union {
        u16 u16_val;
        struct {
            u16 gpio0_drv : 1; ///< Drive strength of GPIO0, 1 high, 0 low
            u16 gpio1_drv : 1; ///< Drive strength of GPIO1,1 high, 0 low
            u16 gpio2_drv : 1; ///< Drive strength of GPIO2,1 high, 0 low
            u16 gpio3_drv : 1; ///< Drive strength of GPIO3,1 high, 0 low
            u16 gpio4_drv : 1; ///< Drive strength of GPIO4,1 high, 0 low
            u16 gpio5_drv : 1; ///< Drive strength of GPIO5,1 high, 0 low
            u16 gpio6_drv : 1; ///< Drive strength of GPIO6,1 high, 0 low
            u16 gpio7_drv : 1; ///< Drive strength of GPIO7,1 high, 0 low
        } bits ;
    } gpio_drv;
    union {
        u16 u16_val;
        struct {
            u16 mcpls_prd : 2;  ///< "interval between turning on microphone bias for headset detection
                                /*
                                00: 64 ms 
                                01: 128 ms
                                10: 256 ms
                                11: 512 ms"
                                */
            u16 mcpls_en : 1;   ///< Enable headset detection, active high
            u16 mcpls_sel : 2;  ///< "duration to turn on microphone bias for headset detection
                                /*
                                00: 64 us 
                                01: 128 us
                                10: 256 us
                                11: 512 us"
                                */
            u16 rtcalarm_intmsk    : 1; ///< RTC ALARM INTERRUPT MASK,  1 don't mask. 0 mask
            u16 rtcpwrcut_intmsk   : 1; ///< RTC POWERCUT INTERRUPT MASK,1 don't mask. 0 mask
            u16 rtclosttime_intmsk : 1; ///< RTC LOSTTIME INTERRUPT MASK,1 don't mask. 0 mask
            u16 test_config  : 8;       ///< TEST BUS MUX SELECT (detail TBD)
        } bits ;
    } mcpls;
    union {
        u16 u16_val;
        struct {
            u16 vdig_pg    : 1; ///< VDIG LDO POWER GOOD STATUS (READ ONLY)
            u16 vabbrf_pg  : 1; ///< VABBRF LDO POWER GOOD STATUS (READ ONLY)
            u16 vaux_pg    : 1; ///< VAUX LDO POWER GOOD STATUS(READ ONLY)
            u16 vabbaud_pg : 1; ///< VABBAUD LDO POWER GOOD STATUS(READ ONLY)
            u16 va_pg      : 1; ///< VA LDO POWER GOOD STATUS(READ ONLY)
            u16 vdigrf_pg  : 1; ///< VDIGRF LDO POWER GOOD STATUS (READ ONLY)
            u16 vsim_pg    : 1; ///< VAUD LDO POWER GOOD STATUS (READ ONLY)
            u16 vdbbio_pg  : 1; ///< VDBBIO LDO POWER GOOD STATUS(READ ONLY)
            u16 vmmpio_pg  : 1; ///< VMMPIO1 LDO POWER GOOD STATUS(READ ONLY)
            u16 vper1_pg   : 1; ///< VPER1 LDO POWER GOOD STATUS(READ ONLY)
            u16 vper2_pg   : 1; ///< VPER2 LDO POWER GOOD STATUS(READ ONLY)
            u16 vper3_pg   : 1; ///< VPER3 LDO POWER GOOD STATUS(READ ONLY)
            u16 vper4_pg   : 1; ///< VPER4 LDO POWER GOOD STATUS(READ ONLY)
            u16 reserved : 3;		
        } bits ;
    } pg;
    union {
        u16 u16_val;
        struct {
            u16 wdexp_intmask    : 1;  ///< WATCHDOG RESET INTERRUPT MASK, 0:mask 1: don't mask
            u16 ldosterr_intmask : 1;  ///< LDO SOFTSTART ERROR INTERRUPT MASK, 0:mask 1: don't mask
            u16 keyon_intmask    : 1;  ///< KEYON INTERRUPT MASK(key keep low for 32ms), 0:mask 1: don't mask
            u16 keyonoff_intmask : 1;  ///< KEYON INTERRUPT MASK(key keep high for 32ms), 0:mask 1: don't mask
            u16 chrgdet_intmask  : 1;  ///< CHARGER DETECT INTERRUPT MASK,0:mask 1: don't mask
            u16 batdet_intmask   : 1;  ///< BATTERY DETECT INTERRUPT MASK, 0:mask 1: don't mask
            u16 pendet_intmask   : 1;  ///< PEN DETECT INTERRUPT MASK, 0:mask 1: don't mask
            u16 hsplugin_intmask : 1;  ///< HEADSET PLUG IN INTERRUPT MASK, , 0:mask 1: don't mask
            u16 hsgnd_intmask    : 1;  ///< HEADSET GROUNDING INTERRUPT MASK,  0:mask 1: don't mask
            u16 adcdone_intmask	 : 1;  ///< AUXILIARY ADC DONE INTERRUPT MASK , 0:mask 1: don't mask
            u16 rfovf_intmask    : 1;  ///< RF ADC OVERFLOW INTERRUPT MASK, 0:mask 1: don't mask
            u16 ath_intmask      : 1;  ///< INTERRUPT FROM ATHENA, 0:mask 1: don't mask
            u16 reserved : 3;	
        } bits ;
    } intmask;
    union {
        u16 u16_val;
        struct {
            u16 wdexp_irq	    : 1; ///< WATCHDOG RESET INTERRUPT, write  1 to clear interrupt
            u16 ldoerr_irq	    : 1; ///< LEO ERROR INTERRUPT, write  1 to clear interrupt
            u16 keyon_irq	    : 1; ///< KEYON INTERRUPT, write 1  to clear interrupt
            u16 keyoff_irq	    : 1; ///< KEYOFF INTERRUPT, write 1  to clear interrupt
            u16 chrgdet_irq	    : 1; ///< CHARGER DETECT INTERRUPT, write 1  to clear interrupt
            u16 batdet_irq	    : 1; ///< BATTERY DETECT INTERRUPT, write 1 to clear interrupt
            u16 pendet_irq	    : 1; ///< PEN DETECT INTERRUPT, write 1  to clear interrupt
            u16 hsplugin_irq    : 1; ///< HEADSET PLUG IN INTERRUPT, write 1  to clear interrupt
            u16 hsgnd_irq	    : 1; ///< HEADSET GROUNDING INTERRUPT, write 1  to clear interrupt
            u16 adcdone_irq	    : 1; ///< AUXILIARY ADC DONE INTERRUPT, write 1  to clear interrupt
            u16 rfovf_irq	    : 1; ///< ADC OVERFLOW INTERRUPT, write  1 to clear interrupt
            u16 ath_irq         : 1; ///< ATHENA INTERRUPT, write  1 to clear interrupt
            u16 reserved : 3;		
        } bits ;
    } irq;
    union {
        u16 u16_val;
        struct {
            u16 wdexp_sense    : 1; ///< WATCHDOG RESET STATUS 
            u16 ldoerr_sense   : 1; ///< LEO ERROR STATUS 
            u16 keyon_sense    : 1; ///< KEYON STATUS 
            u16 keyoff_sense   : 1; ///< KEYOFF STATUS 
            u16 chrgdet_sense  : 1; ///< CHARGER DETECT STATUS 
            u16 batdet_sense   : 1; ///< BATTERY DETECT STATUS
            u16 pendet_sense   : 1; ///< PEN DETECT STATUS 
            u16 hsplugin_sense : 1; ///< HEADSET PLUG IN STATUS
            u16 hsgnd_sense    : 1; ///< HEADSET GROUNDING STATUS
            u16 adcdone_sense  : 1; ///< AUXILIARY ADC DONE STATUS
            u16 rfovf_sense    : 1; ///< RF ADC OVERFLOW STATUS 
            u16 ath_sense      : 1; ///< ATHENA INTERRUPT STATUS 
            u16 reserved : 3;	
        } bits ;
    } irq_sense;
    union {
        u16 u16_val;
        struct {
            u16 pll0_lock_irq     : 1; ///< PLL0 LOCK edge detected, 
            u16 pll1_lock_irq     : 1; ///< PLL1 LOCK edge detected
            u16 pll21_lock_irq    : 1; ///< PLL21 LOCK edge detected
            u16 pll22_lock_irq    : 1; ///< PLL22 LOCK edge detected
            u16 pll0_unlock_irq   : 1; ///< PLL0 UNLOCK edge detected 
            u16 pll1_unlock_irq   : 1; ///< UNLOCK edge detected 
            u16 pll21_unlock_irq  : 1; ///< PLL21 UNLOCK edge detected 
            u16 pll22_unlock_irq  : 1; ///< PLL22 UNLOCK edge detected 
            u16 pll0_lockr_sense  : 1; ///< PLL0 LOCK raw bit
            u16 pll1_lockr_sense  : 1; ///< PLL1 LOCK raw bit
            u16 pll21_lockr_sense : 1; ///< PLL21 LOCK raw bit
            u16 pll22_lockr_sense : 1; ///< PLL22 LOCK raw bit
            u16 reserved : 3;	
        } bits ;
    } pll_irq;
    union {
        u16 u16_val;
        struct {
            u16 pll0_lock_intmask     : 1; ///<  PLL0 LOCK MASK, 1:mask 0: don't mask
            u16 pll1_lock_intmask     : 1; ///<  PLL1 LOCK MASK, 1:mask 0: don't mask
            u16 pll21_lock_intmask    : 1; ///<  PLL21 LOCK MASK, 1:mask 0: don't mask
            u16 pll22_lock_intmask    : 1; ///<  PLL22 LOCK MASK, 1:mask 0: don't mask
            u16 pll0_unlock_intmask   : 1; ///<  PLL0 UNLOCK MASK, 1:mask 0: don't mask
            u16 pll1_unlock_intmask   : 1; ///<  PLL1 UNLOCK MASK, 1:mask 0: don't mask
            u16 pll21_unlock_intmask  : 1; ///<  PLL21 UNLOCK MASK, 1:mask 0: don't mask
            u16 pll22_unlock_intmask  : 1; ///<  PLL22 UNLOCK MASK, 1:mask 0: don't mask
            u16 reserved : 8;		
        } bits ;
    } pll_mask;
    union {
        u16 u16_val;
        struct {
            u16 fuse_lockb_ref  : 1;        ///< if 0, REF trim bit is from EFUSE, if 1 from register EF_REGBIT.
            u16 fuse_reg_sel    : 1;        ///< if 0, REF trim bits is from overwrite register; if 1 from auto trim result register
            u16 ef_regbit       : 6;        ///< EFUSE REGISTER WRITE BIT
            u16 ref_trim_en	    : 1;        ///< "enable comparator for reference trim  ,active high. This bit must be set high when software trim."
            u16 fuse_read_en    : 1;        ///< "write 1 to this bit will generate two 32k pulse (self-clear). The 256 bits fuse data will be loaded to the efuse register bank."
            u16 fuse_auto_trim  : 1;        ///< write 1 to this bit will enable auto trim sequence. 
            u16 reserved : 5;			
        } bits ;
    } ref_fuse;
    union {
        u16 u16_val;
        struct {
            u16 pm_state : 5;           ///< PM STATE MACHINE STATE (READ ONLY)
            u16 efuse_trim_out : 1;     ///< "EFUSE comparator result (1: REF > EXT_REG; 0: EXT_REF > REF)
                                        /*
                                        if get 1, increase fuse bit value. If get 0, decrease fuse bit value.
                                        This bit can be used in software trim ."
                                        */
            u16 ef_trim_done : 1;       ///< "0, EFUSE auto trim is done; 1, EFUSE is auto-trimming.
                                        /*
                                        After enable EFUSE auto trim, this bit will be set to 1, and after auto trim is done, this bit wil be automaticly reset to 0. EF_TRIM_DATA is only valid when this bit is 0."
                                        */
            u16 ef_trim_data : 6;       ///< EFUSE auto trim result.
        } bits ;
    } pmstate;
    union {
        u16 u16_val;
        struct {
            u16 fuse_lockb_dbbio : 1; ///< If 0, DBBIO level select bit is from EFUSE, if 1 from register REG_LVL_VIO1
            u16 fuse_lockb_mmpio : 1; ///< If 0, MMPIO level select bit is from EFUSE, if 1 from register REG_LVL_VIO2
            u16 fuse_lockb_digrf : 1; ///< If 0, digrf level select bit is from EFUSE, if 1 from register EF_REGBIT.
            u16 reg_lvl_digrf    : 2; ///< DIGRF LDO level . 00,1.5v; 01,1.8v; 10, 2.8v; 11,2.9v;
            u16 reg_lvl_vio1     : 2; ///< VIO1 LDO level.  00,1.5v;01,1.8v;10,2.5v;11,2.8v
            u16 reg_lvl_vio2     : 2; ///< VIO2 LDO level. 00,1.5v;01,1.8v;10,2.5v;11,2.8v
        } bits ;
    } io_lvl;
} IncensePMReg_t;

#endif


typedef struct {
    union {
        u32 u32_val;
        struct {
            u32 areg_en_vabbrf  : 1;    ///< ABBRF LDO enable bit in active mode, active high
            u32 areg_en_vaux    : 1;    ///< AUX LDO enable bit in active mode , active high
            u32 areg_en_vabbaud : 1;    ///< ABBAUD LDO enable bit in active mode , active high
            u32 areg_en_va      : 1;    ///< TCXO LDO enable bit in active mode , active high
            u32 areg_en_vdigrf  : 1;    ///< DIGRF LDO enable bit in active mode , active high
            u32 areg_en_vmmpio  : 1;    ///< MMPIO LOD enable bit in active mode , active high(VIO2)
            u32 areg_en_vdbbio  : 1;    ///< DBBIO LDO enable bit in active mode , active high(VIO1)
            u32 areg_en_per1    : 1;    ///< PERIPHERAL1 LDO enable bit in active mode , active high
            u32 areg_en_per2    : 1;    ///< PERIPHERAL2 LDO enable bit in active mode, active high
            u32 areg_en_per3    : 1;    ///< PERIPHERAL3 LDO enable bit in active mode, active high
            u32 areg_en_per4    : 1;    ///< PERIPHERAL4 LDO enable bit in active mode, active high
            u32 areg_en_mmp0    : 1;    ///< MMP0 in Athena enable bit in active mode , active high
            u32 areg_en_mmp1    : 1;    ///< MMP1 in Athena enable bit in active mode , active high
            u32 areg_en_rfdig   : 1;    ///< RF digital power gate enable bit in active mode , active high
            u32 areg_en_auddig  : 1;    ///< AUDIO digital power gate enable bit in active mode 
            u32 areg_en_auxdig  : 1;    ///< AUX digital power gate enable bit in active mode 
            u32 reserved        : 16;        
        } bits ;
    } ldo_en_act;
    union {
        u32 u32_val;
        struct {
            u32 sreg_en_vabbrf  : 1; ///< ABBRF LDO enable bit in standby mode, active high
            u32 sreg_en_vaux    : 1; ///< AUX LDO enable bit in standby mode , active high
            u32 sreg_en_vabbaud : 1; ///< ABBAUD LDO enable bit in standby mode , active high
            u32 sreg_en_va      : 1; ///< TCXO LDO enable bit in standby mode , active high
            u32 sreg_en_vdigrf  : 1; ///< DIGRF LDO enable bit in standby mode , active high
            u32 sreg_en_vmmpio  : 1; ///< MMPIO LOD enable bit in standby mode , active high(VIO2)
            u32 sreg_en_vdbbio  : 1; ///< DBBIO LDO enable bit in standby mode , active high(VIO1)
            u32 sreg_en_per1    : 1; ///< PERIPHERAL1 LDO enable bit in standby mode , active high
            u32 sreg_en_per2    : 1; ///< PERIPHERAL2 LDO enable bit in standby mode, active high
            u32 sreg_en_per3    : 1; ///< PERIPHERAL3 LDO enable bit in standby mode, active high
            u32 sreg_en_per4    : 1; ///< PERIPHERAL4 LDO enable bit in standby mode, active high
            u32 sreg_en_mmp0    : 1; ///< MMP0 in Athena enable bit in standby mode , active high
            u32 sreg_en_mmp1    : 1; ///< MMP1 in Athena enable bit in standby mode , active high
            u32 sreg_en_rfdig   : 1; ///< RF digital power gate enable bit in standby mode , active high
            u32 sreg_en_auddig  : 1; ///< AUDIO digital power gate enable bit in standby mode 
            u32 reserved_1      : 1;   
            u32 reserved_2      : 16;                         
        } bits ;
    } ldo_en_sdb;
    union {
        u32 u32_val;
        struct {
           u32 areg_lvl1_vdig   : 2;  ///< Digital LDO level config in active mode. 00,1.2v; 01,1.25v;10,1.3v;11,1.1v
           u32 areg_lvl1_vabbrf : 2;  ///< ABBRF LDO level config in active mode. 00,1.8v; 01,2.28v; 10, 2.5v; 11,2.8v;
           u32 areg_lvl1_vaux   : 2;  ///< AUX LDO level config in active mode. 00,1.8v; 01,2.28v; 10, 2.5v; 11,2.8v;
           u32 areg_lvl1_vabbaud: 2;  ///< ABBAUD LDO level config in active mode. 00,1.8v; 01,2.28v; 10, 2.5v; 11,2.8v;
           u32 areg_lvl1_va     : 2;  ///< TCXO LDO level config in active mode. 00,1.5v; 01,1.8v; 10, 2.8v; 11,2.9v;
           u32 areg_lvl1_vsim   : 2;  ///< SIM LDO level config in active mode.  00,1.5v; 01,1.8v; 10, 2.8v; 11,2.9v;
           u32 areg_lvl1_vper1  : 2;  ///< PERIPHERAL1 LDO  config in active mode.  00,1.5v;01,1.8v;10,2.5v;11,2.8v
           u32 areg_lvl1_vper2  : 2;  ///< PERIPHERAL2 LDO level config in active mode. 00,1.5v;01,1.8v;10,2.5v;11,2.8v
           u32 reserved         : 16;        
        } bits ;
    } ldo_lvl1_act;
    union {
        u32 u32_val;
        struct {
           u32 areg_lvl2_per3 : 2;    ///< PERIPHERAL3 level config in active mode. 00,1.5v;01,1.8v;10,2.5v;11,2.8v
           u32 areg_lvl2_per4 : 2;    ///< PERIPHERAL4 level config in active mode. 00,1.5v;01,1.8v;10,2.5v;11,2.8v
           u32 sreg_lvl2_per3 : 2;    ///< PERIPHERAL3 level config in standby mode
           u32 sreg_lvl2_per4 : 2;    ///< PERIPHERAL4 level config in standby mode
           u32 reserved_1     : 8;  
           u32 reserved_2     : 16;                                         
        } bits ;
    } ldo_lvl2;
    union {
        u32 u32_val;
        struct {
           u32 sreg_lvl1_vdig    : 2;   ///< Digital LDO level config in standby mode. 00,1.2v; 01,1.25v;10,1.3v;11,1.1v
           u32 sreg_lvl1_vabbrf  : 2;   ///< ABBRF LDO level config in standby mode. 00,1.8v; 01,2.28v; 10, 2.5v; 11,2.8v;
           u32 sreg_lvl1_vaux    : 2;   ///< AUX LDO level config in standby mode. 00,1.8v; 01,2.28v; 10, 2.5v; 11,2.8v;
           u32 sreg_lvl1_vabbaud : 2;   ///< ABBAUD LDO level config in standby mode. 00,1.8v; 01,2.28v; 10, 2.5v; 11,2.8v;
           u32 sreg_lvl1_va      : 2;   ///< TCXO LDO level config in standby mode. 00,1.5v; 01,1.8v; 10, 2.8v; 11,2.9v;
           u32 sreg_lvl1_vsim    : 2;   ///< SIM LDO level config in standby mode.  00,1.5v; 01,1.8v; 10, 2.8v; 11,2.9v;
           u32 sreg_lvl1_vper1   : 2;   ///< PERIPHERAL1 LDO  config in standby mode.  00,1.5v;01,1.8v;10,2.5v;11,2.8v
           u32 sreg_lvl1_vper2   : 2;   ///< PERIPHERAL2 LDO level config in standby mode. 00,1.5v;01,1.8v;10,2.5v;11,2.8v
           u32 reserved          : 16;        
        } bits ;
    } ldo_lvl1_sdb;
    union {
        u32 u32_val;
        struct {
           u32 areg_lq_vdig     : 1;   ///< DIG LDO enter low quiesent mode in active mode,active high
           u32 areg_lq_vabbrf   : 1;   ///< ABBRF LDO enter low quiesent mode in active mode,active high
           u32 areg_lq_vaux     : 1;   ///< AUX LDO enter low quiesent mode in active mode,active high
           u32 areg_lq_vabbaud  : 1;   ///< ABBADU LDO enter low quiesent mode in active mode,active high
           u32 areg_lq_va       : 1;   ///< TCXO LDO enter low quiesent mode in active mode,active high
           u32 areg_lq_vdigrf   : 1;   ///< DIGRF LDO enter low quiesent mode in active mode,active high
           u32 areg_lq_vsim     : 1;   ///< SIM LDO enter low quiesent mode in active mode,active high
           u32 areg_lq_vdbbio   : 1;   ///< DBBIO LDO enter low quiesent mode in active mode,active high
           u32 areg_lq_mmpio    : 1;   ///< MMPIO LDO enter low quiesent mode in active mode,active high
           u32 areg_lq_per1     : 1;   ///< PERIPHERAL1 LDO enter low quiesent mode in active mode,active high
           u32 areg_lq_per2     : 1;   ///< PERIPHERAL2 LDO enter low quiesent mode in active mode,active high
           u32 areg_lq_per3     : 1;   ///< PERIPHERAL3 LDO enter low quiesent mode in active mode,active high
           u32 areg_lq_per4     : 1;   ///< PERIPHERAL4 LDO enter low quiesent mode in active mode,active high
           u32 reserved_1       : 3;  
           u32 reserved_2       : 16;                                                          
        } bits ;
    } ldo_lq_act;
    union {
        u32 u32_val;
        struct {
           u32 sreg_lq_vdig     : 1;  ///< DIG LDO enter low quiesent mode in active mode,active high
           u32 sreg_lq_vabbrf   : 1;  ///< ABBRF LDO enter low quiesent mode in active mode,active high
           u32 sreg_lq_vaux     : 1;  ///< AUX LDO enter low quiesent mode in active mode,active high
           u32 sreg_lq_vabbaud  : 1;  ///< ABBADU LDO enter low quiesent mode in active mode,active high
           u32 sreg_lq_va       : 1;  ///< TCXO LDO enter low quiesent mode in active mode,active high
           u32 sreg_lq_vdigrf   : 1;  ///< DIGRF LDO enter low quiesent mode in active mode,active high
           u32 sreg_lq_vsim     : 1;  ///< SIM LDO enter low quiesent mode in active mode,active high
           u32 sreg_lq_vdbbio   : 1;  ///< DBBIO LDO enter low quiesent mode in active mode,active high
           u32 sreg_lq_vmmpio   : 1;  ///< MMPIO LDO enter low quiesent mode in active mode,active high
           u32 sreg_lq_per1     : 1;  ///< PERIPHERAL1 LDO enter low quiesent mode in active mode,active high
           u32 sreg_lq_per2     : 1;  ///< PERIPHERAL2 LDO enter low quiesent mode in active mode,active high
           u32 sreg_lq_per3     : 1;  ///< PERIPHERAL3 LDO enter low quiesent mode in active mode,active high
           u32 sreg_lq_per4     : 1;  ///< PERIPHERAL4 LDO enter low quiesent mode in active mode,active high
           u32 reserved_1       : 3;  
           u32 reserved_2       : 16;                                                                           
        } bits ;
    } ldo_lq_sdb;
    union {
        u32 u32_val;
        struct {
           u32 gpio7in  : 1;  ///< GPIO7 INPUT REGISTER (READ ONLY)
           u32 gpio6in  : 1;  ///< GPIO6 INPUT REGISTER (READ ONLY)
           u32 gpio5in  : 1;  ///< GPIO5 INPUT REGISTER (READ ONLY)
           u32 gpio4in  : 1;  ///< GPIO4 INPUT REGISTER (READ ONLY)
           u32 gpio3in  : 1;  ///< GPIO3 INPUT REGISTER (READ ONLY)
           u32 gpio2in  : 1;  ///< GPIO2 INPUT REGISTER (READ ONLY)
           u32 gpio1in  : 1;  ///< GPIO1 INPUT REGISTER (READ ONLY)
           u32 gpio0in  : 1;  ///< GPIO0 INPUT REGISTER (READ ONLY)
           u32 gpio7out : 1;  ///< GPIO7 OUTPUT REGISTER
           u32 gpio6out : 1;  ///< GPIO6 OUTPUT REGISTER
           u32 gpio5out : 1;  ///< GPIO5 OUTPUT REGISTER
           u32 gpio4out : 1;  ///< GPIO4 OUTPUT REGISTER
           u32 gpio3out : 1;  ///< GPIO3 OUTPUT REGISTER
           u32 gpio2out : 1;  ///< GPIO2 OUTPUT REGISTER
           u32 gpio1out : 1;  ///< GPIO1 OUTPUT REGISTER
           u32 gpio0out : 1;  ///< GPIO0 OUTPUT REGISTER
           u32 reserved : 16;        
        } bits ;
    } gpio_data;
    union {
        u32 u32_val;
        struct {
            u32 gpio7c         : 1; ///< GPIO7 IN/OUT CONTROL (0: OUTPUT, 1: INPUT)
            u32 gpio6c         : 1; ///< GPIO6 IN/OUT CONTROL (0: OUTPUT, 1: INPUT)
            u32 gpio5c         : 1; ///< GPIO5 IN/OUT CONTROL (0: OUTPUT, 1: INPUT)
            u32 gpio4c         : 1; ///< GPIO4 IN/OUT CONTROL (0: OUTPUT, 1: INPUT)
            u32 gpio3c         : 1; ///< GPIO3 IN/OUT CONTROL (0: OUTPUT, 1: INPUT)
            u32 gpio2c         : 1; ///< GPIO2 IN/OUT CONTROL (0: OUTPUT, 1: INPUT)
            u32 gpio1c         : 1; ///< GPIO1 IN/OUT CONTROL (0: OUTPUT, 1: INPUT)
            u32 gpio0c         : 1; ///< GPIO0 IN/OUT CONTROL (0: OUTPUT, 1: INPUT)
            u32 gpio7cfg       : 1; ///< GPIO7 CONFIGURATION (0: GENERAL, 1: KEYPAD1)
            u32 gpio6cfg       : 1; ///< GPIO6 CONFIGURATION (0: GENERAL, 1: KEYPAD0)
            u32 standbyen      : 1; ///< ENABLE STANDBYB port, active high
            u32 keyoff_en      : 1; ///< ENABLE KEY OFF (5s forced shut-down) OPERATION,active high
            u32 softstart_en   : 1; ///< softstart mode enable.  Active high.
            u32 reserved_1     : 3;    
            u32 reserved_2     : 16;                                                                                          
        } bits ;
    } gpio_cfg;
    union {
        u32 u32_val;
        struct {
            u32 ibattype    : 2; ///< "BATTERY TYPE DETECT CURRENT SELECT. 2'b00: 1uA, 2'b01: 5uA; 2'b10: 10uA; 2'b11: 20uA"
            u32 ibattemp    : 2; ///< "BATTERY TEMP DETECT CURRENT SELECT. 2'b00: 1uA, 2'b01: 5uA; 2'b10: 10uA; 2'b11: 20uA"
            u32 reftm       : 2; ///< TEST MODE OF REFERENCE GENERATOR. detail
            u32 regwr_en    : 1; ///< REGISTER WRITE ENABLE (FROM 26M TO 32K). 1, open 32k to 26M sync. 0, close
            u32 en_rgb      : 1; ///< ENABLE RGB LED, active high
            u32 repeat_rgb  : 1; ///< REPEAT RGB PWM OPERATION, active high
            u32 en_key0     : 1; ///< ENABLE KEYPAD 0, active high
            u32 en_key1     : 1; ///< ENABLE KEYPAD 1, active high
            u32 mode_rgb    : 2; ///< 00:pulse mode; 01:roation mode;10-11 reserved
            u32 bst_en      : 1; ///< boost enable, active high
            u32 reserved_1  : 2; 
            u32 reserved_2  : 16;                                                                                                            
        } bits ;
    } misc1;
    union {
        u32 u32_val;
        struct {
            u32 wd_timeout : 12;  ///< WATCHDOG TIMEOUT THRESHOLD. 1LSB for 30 ms
            u32 wd_en      : 1;   ///< WATCHDOG ENABLE, active high
            u32 wd_clear   : 1;   ///< WATCHDOG CLEAR (WRITE 1 to clear watch dog counter). 
            u32 abbint_pol : 1;   ///< ABBINT POLARITY CONTROL.  0, interrupt pin is active high; 0, active low
            u32 reserved_1 : 1;    
            u32 reserved_2 : 16;                                                                                                                           
        } bits ;
    } wd;
    union {
        u32 u32_val;
        struct {
            u32 ton_rgb    : 2;  ///< W/R   "TON_RGB[1:0]: RGB on time if bit REPEAT_RGB=1. This bit works in conjunction with MODE_RGB bits.
                                 /*
                                 MODE_RGB[1:0]=0
                                 00: 102 ms (default)  01: 203 ms   10: 406 ms  11: fully on (control with EN_RGB bit)
                                 MODE_RGB[1:0]=1
                                 00: 102 ms  01: 203 ms   10: 406 ms   11: 804 ms  " 
                                 */
            u32 toff_rgb   : 2;  ///< "TOFF_RGB[1:0]: RGB off time if bit REPEAT_RGB=1. This bit works in conjunction with MODE_RGB bits
                                 /*
                                 MODE_RGB[1:0]=0
                                 00: 406 ms (default)   01: 1602 ms  10: 3203 ms  11: 4804 ms
                                 MODE_RGB[1:0]=1
                                 00: 0 ms    01: 406 ms  10: 804 ms   11: 1602 ms"
                                 */
            u32 ratio_r    : 4;  ///< W/R   "ratio of red LED PWM
                                 /*
                                 0000: off (default)    0001: 1/15 on   0010: 2/15 on   0011: 3/15 on
                                 0100: 4/15 on            0101: 5/15 on    0110: 6/15 on  0111: 7/15 on
                                 1000: 8/15 on           1001: 9/15 on    1010: 10/15 on 1011: 11/15 on
                                 1100: 12/15 on         1101: 13/15 on   1110: 14/15 on  1111: always on"
                                 */
            u32 ratio_g    : 4;  ///< W/R   "ratio of green LED PWM
                                 /*
                                 0000: off (default)   0001: 1/15 on    0010: 2/15 on    0011: 3/15 on
                                 0100: 4/15 on           0101: 5/15 on    0110: 6/15 on    0111: 7/15 on
                                 1000: 8/15 on           1001: 9/15 on    1010: 10/15 on  1011: 11/15 on
                                 1100: 12/15 on         1101: 13/15 on  1110: 14/15 on  1111: always on"
                                 */
            u32 ratio_b    : 4;  ///< W/R   "ratio of blue LED PWM
                                 /*
                                 0000: off (default)    0001: 1/15 on    0010: 2/15 on     0011: 3/15 on
                                 0100: 4/15 on            0101: 5/15 on    0110: 6/15 on     0111: 7/15 on
                                 1000: 8/15 on            1001: 9/15 on    1010: 10/15 on   1011: 11/15 on
                                 1100: 12/15 on          1101: 13/15 on  1110: 14/15 on   1111: always on"
                                 */
            u32 reserved   : 16;        
        } bits ;
    } rgb_cfg;
    union {
        u32 u32_val;
        struct {
            u32 pwmp_key0 : 8;   ///< "PWMP_KEY0[7:0]: prescaler of KEYPAD0 LED PWM, input clock is 32KHz
                                 /*
                                 00000000: divide by 1
                                 00000001: divide by 2
                                 ??
                                 11111111: divide by 256"
                                 */
            u32 period_key0 : 8; ///< PERIOD_KEY0[7:0]: this register together with PWMP_KEY0 set the PWM period of KEYPAD0 LED.   Fkeypad0 = CLK/(PERIOD_KEY0*(PWMP_KEY0+1)), CLK is 32KHz. If PWMP_KEY0 or PERIOD_KEY0 is equal to 0, the PWM output is equal to 0.
            u32 reserved  : 16;        
                  } bits ;
    } pwd_cfg1;
    union {
        u32 u32_val;
        struct {
            u32 ratio_key0 : 8; ///< "RATIO_KEY0[7:0]: set the PWM output high ratio relative to PERIOD_KEY0 for KEYPAD0 LED
                                /*
                                If RATIO_KEY0 is equal to or greater than PERIOD_KEY0, PWM output is 1
                                00000000: PWM output is 0
                                00000001: PWM output is high for 1 Fkeypad0 clock (see PERIOD_KEY0 definition)
                                00000010: PWM output is high for 2 Fkeypad0 clocks
                                ??
                                11111111: PWM output is high for 255 Fkeypad0 clocks"
                                */
            u32 cycle0_key0 : 8;    ///< "CYCLE0_KEY0[7:0]: this register together with CYCLE1_KEY0 set the number of times a PWM shape is repeated.
                                    /*
                                    If CYCLE0_KEY0 and CYCLE1_KEY0 are both 0, then a PWM shape is repeated without inversion.
                                    If CYCLE0_KEY0 is 0 and CYCLE1_KEY0 is not 0, then an inverted PWM shape is repeated. If CYCLE0_KEY0 and
                                    CYCLE1_KEY0 are both nonzero, then a PWM shape is repeated CYCLE0_KEY0 times, then inverted and repeated
                                    CYCLE1_KEY0 times."
                                    */
            u32 reserved   : 16;        
        } bits ;
    } pwd_cfg2;
    union {
        u32 u32_val;
        struct {
            u32 cycle1_key0 : 8; ///< "CYCLE1_KEY0[7:0]: this register together with CYCLE0_KEY0 set the number of times a PWM shape is repeated.
                                 /*
                                    If CYCLE0_KEY0 and CYCLE1_KEY0 are both 0, then a PWM shape is repeated without inversion. If
                                    CYCLE0_KEY0 is 0 and CYCLE1_KEY0 is not 0, then an inverted PWM shape is repeated. If CYCLE0_KEY0 and
                                    CYCLE1_KEY0 are both nonzero, then a PWM shape is repeated CYCLE0_KEY0 times, then inverted and repeated
                                    CYCLE1_KEY0 times."
                                 */
            u32 pwmp_key1 : 8; ///< "PWMP_KEY1[7:0]: prescaler of KEYPAD1 LED PWM, input clock is 32KHz
                                 /*
                                    00000001: divide by 2
                                    ??
                                    11111111: divide by 256
                                                         */
            u32 reserved  : 16;                                                    
        } bits ;
    } pwd_cfg3;
    union {
        u32 u32_val;
        struct {
            u32 period_key1 : 8; ///< "PERIOD_KEY1[7:0]: this register together with PWMP_KEY1 set the PWM period of KEYPAD1 LED
                                    /*
                                    Fkeypad1 = CLK/(PERIOD_KEY1*(PWMP_KEY1+1)), CLK is 32KHz. If PWMP_KEY1 or PERIOD_KEY1 is equal
                                    to 0, the PWM output is equal to 0."
                                    */
            u32 ratio_key1 : 8; ///< "RATIO_KEY1[7:0]: set the PWM output high ratio relative to PERIOD_KEY1 for KEYPAD1 LED
                                    /*
                                    If RATIO_KEY1 is equal to or greater than PERIOD_KEY1, PWM output is 1
                                    00000000: PWM output is 0
                                    00000001: PWM output is high for 1 Fkeypad1 clock (see PERIOD_KEY1 definition)
                                    00000010: PWM output is high for 2 Fkeypad1 clocks
                                    ??
                                    11111111: PWM output is high for 255 Fkeypad1 clocks
                                    */
            u32 reserved   : 16;        
        } bits ;
    } pwd_cfg4;
    union {
        u32 u32_val;
        struct {
            u32 cycle0_key1 : 8; ///< "CYCLE0_KEY1[7:0]: this register together with CYCLE1_KEY01set the number of times a PWM shape is repeated.
                                    /*
                                    If CYCLE0_KEY1 and CYCLE1_KEY1 are both 0, then a PWM shape is repeated without inversion. If
                                    CYCLE0_KEY1 is 0 and CYCLE1_KEY1 is not 0, then an inverted PWM shape is repeated. If CYCLE0_KEY1 and
                                    CYCLE1_KEY1 are both nonzero, then a PWM shape is repeated CYCLE0_KEY1 times, then inverted and repeated
                                    CYCLE1_KEY1 times.
                                    */
            u32 cycle1_key1 : 8; ///< W/R   CYCLE1_KEY1[7:0]: see CYCLE0_KEY1[7:0] description
            u32 reserved    : 16;        
        } bits ;
    } pwd_cfg5;
    union {
        u32 u32_val;
        struct {
            u32 gpio0_drv : 1; ///< Drive strength of GPIO0, 1 high, 0 low
            u32 gpio1_drv : 1; ///< Drive strength of GPIO1,1 high, 0 low
            u32 gpio2_drv : 1; ///< Drive strength of GPIO2,1 high, 0 low
            u32 gpio3_drv : 1; ///< Drive strength of GPIO3,1 high, 0 low
            u32 gpio4_drv : 1; ///< Drive strength of GPIO4,1 high, 0 low
            u32 gpio5_drv : 1; ///< Drive strength of GPIO5,1 high, 0 low
            u32 gpio6_drv : 1; ///< Drive strength of GPIO6,1 high, 0 low
            u32 gpio7_drv : 1; ///< Drive strength of GPIO7,1 high, 0 low
            u32 reserved_1 : 8;    
            u32 reserved_2 : 16;                                                                                                                           
        } bits ;
    } gpio_drv;
    union {
        u32 u32_val;
        struct {
            u32 mcpls_prd : 2;  ///< "interval between turning on microphone bias for headset detection
                                /*
                                00: 64 ms 
                                01: 128 ms
                                10: 256 ms
                                11: 512 ms"
                                */
            u32 mcpls_en : 1;   ///< Enable headset detection, active high
            u32 mcpls_sel : 2;  ///< "duration to turn on microphone bias for headset detection
                                /*
                                00: 64 us 
                                01: 128 us
                                10: 256 us
                                11: 512 us"
                                */
            u32 rtcalarm_intmsk    : 1; ///< RTC ALARM INTERRUPT MASK,  1 don't mask. 0 mask
            u32 rtcpwrcut_intmsk   : 1; ///< RTC POWERCUT INTERRUPT MASK,1 don't mask. 0 mask
            u32 rtclosttime_intmsk : 1; ///< RTC LOSTTIME INTERRUPT MASK,1 don't mask. 0 mask
            u32 test_config  : 8;       ///< TEST BUS MUX SELECT (detail TBD)
            u32 reserved     : 16;        
        } bits ;
    } mcpls;
    union {
        u32 u32_val;
        struct {
            u32 vdig_pg    : 1; ///< VDIG LDO POWER GOOD STATUS (READ ONLY)
            u32 vabbrf_pg  : 1; ///< VABBRF LDO POWER GOOD STATUS (READ ONLY)
            u32 vaux_pg    : 1; ///< VAUX LDO POWER GOOD STATUS(READ ONLY)
            u32 vabbaud_pg : 1; ///< VABBAUD LDO POWER GOOD STATUS(READ ONLY)
            u32 va_pg      : 1; ///< VA LDO POWER GOOD STATUS(READ ONLY)
            u32 vdigrf_pg  : 1; ///< VDIGRF LDO POWER GOOD STATUS (READ ONLY)
            u32 vsim_pg    : 1; ///< VAUD LDO POWER GOOD STATUS (READ ONLY)
            u32 vdbbio_pg  : 1; ///< VDBBIO LDO POWER GOOD STATUS(READ ONLY)
            u32 vmmpio_pg  : 1; ///< VMMPIO1 LDO POWER GOOD STATUS(READ ONLY)
            u32 vper1_pg   : 1; ///< VPER1 LDO POWER GOOD STATUS(READ ONLY)
            u32 vper2_pg   : 1; ///< VPER2 LDO POWER GOOD STATUS(READ ONLY)
            u32 vper3_pg   : 1; ///< VPER3 LDO POWER GOOD STATUS(READ ONLY)
            u32 vper4_pg   : 1; ///< VPER4 LDO POWER GOOD STATUS(READ ONLY)
            u32 reserved_1 : 3; 
            u32 reserved_2 : 16;                                                                                                                                             
        } bits ;
    } pg;
    union {
        u32 u32_val;
        struct {
            u32 wdexp_intmask    : 1;  ///< WATCHDOG RESET INTERRUPT MASK, 0:mask 1: don't mask
            u32 ldosterr_intmask : 1;  ///< LDO SOFTSTART ERROR INTERRUPT MASK, 0:mask 1: don't mask
            u32 keyon_intmask    : 1;  ///< KEYON INTERRUPT MASK(key keep low for 32ms), 0:mask 1: don't mask
            u32 keyonoff_intmask : 1;  ///< KEYON INTERRUPT MASK(key keep high for 32ms), 0:mask 1: don't mask
            u32 chrgdet_intmask  : 1;  ///< CHARGER DETECT INTERRUPT MASK,0:mask 1: don't mask
            u32 batdet_intmask   : 1;  ///< BATTERY DETECT INTERRUPT MASK, 0:mask 1: don't mask
            u32 pendet_intmask   : 1;  ///< PEN DETECT INTERRUPT MASK, 0:mask 1: don't mask
            u32 hsplugin_intmask : 1;  ///< HEADSET PLUG IN INTERRUPT MASK, , 0:mask 1: don't mask
            u32 hsgnd_intmask    : 1;  ///< HEADSET GROUNDING INTERRUPT MASK,  0:mask 1: don't mask
            u32 adcdone_intmask  : 1;  ///< AUXILIARY ADC DONE INTERRUPT MASK , 0:mask 1: don't mask
            u32 rfovf_intmask    : 1;  ///< RF ADC OVERFLOW INTERRUPT MASK, 0:mask 1: don't mask
            u32 ath_intmask      : 1;  ///< INTERRUPT FROM ATHENA, 0:mask 1: don't mask
            u32 reserved_1       : 3;  
            u32 reserved_2       : 16;                                                                                                                                                          
        } bits ;
    } intmask;
    union {
        u32 u32_val;
        struct {
            u32 wdexp_irq       : 1; ///< WATCHDOG RESET INTERRUPT, write  1 to clear interrupt
            u32 ldoerr_irq      : 1; ///< LEO ERROR INTERRUPT, write  1 to clear interrupt
            u32 keyon_irq       : 1; ///< KEYON INTERRUPT, write 1  to clear interrupt
            u32 keyoff_irq      : 1; ///< KEYOFF INTERRUPT, write 1  to clear interrupt
            u32 chrgdet_irq     : 1; ///< CHARGER DETECT INTERRUPT, write 1  to clear interrupt
            u32 batdet_irq      : 1; ///< BATTERY DETECT INTERRUPT, write 1 to clear interrupt
            u32 pendet_irq      : 1; ///< PEN DETECT INTERRUPT, write 1  to clear interrupt
            u32 hsplugin_irq    : 1; ///< HEADSET PLUG IN INTERRUPT, write 1  to clear interrupt
            u32 hsgnd_irq       : 1; ///< HEADSET GROUNDING INTERRUPT, write 1  to clear interrupt
            u32 adcdone_irq     : 1; ///< AUXILIARY ADC DONE INTERRUPT, write 1  to clear interrupt
            u32 rfovf_irq       : 1; ///< ADC OVERFLOW INTERRUPT, write  1 to clear interrupt
            u32 ath_irq         : 1; ///< ATHENA INTERRUPT, write  1 to clear interrupt
            u32 reserved_1      : 3;  
            u32 reserved_2      : 16;                                                                                                                                                                           
        } bits ;
    } irq;
    union {
        u32 u32_val;
        struct {
            u32 wdexp_sense    : 1; ///< WATCHDOG RESET STATUS 
            u32 ldoerr_sense   : 1; ///< LEO ERROR STATUS 
            u32 keyon_sense    : 1; ///< KEYON STATUS 
            u32 keyoff_sense   : 1; ///< KEYOFF STATUS 
            u32 chrgdet_sense  : 1; ///< CHARGER DETECT STATUS 
            u32 batdet_sense   : 1; ///< BATTERY DETECT STATUS
            u32 pendet_sense   : 1; ///< PEN DETECT STATUS 
            u32 hsplugin_sense : 1; ///< HEADSET PLUG IN STATUS
            u32 hsgnd_sense    : 1; ///< HEADSET GROUNDING STATUS
            u32 adcdone_sense  : 1; ///< AUXILIARY ADC DONE STATUS
            u32 rfovf_sense    : 1; ///< RF ADC OVERFLOW STATUS 
            u32 ath_sense      : 1; ///< ATHENA INTERRUPT STATUS 
            u32 reserved_1     : 3;   
            u32 reserved_2     : 16;                                                                                                                                                                           
        } bits ;
    } irq_sense;
    union {
        u32 u32_val;
        struct {
            u32 pll0_lock_irq     : 1; ///< PLL0 LOCK edge detected, 
            u32 pll1_lock_irq     : 1; ///< PLL1 LOCK edge detected
            u32 pll21_lock_irq    : 1; ///< PLL21 LOCK edge detected
            u32 pll22_lock_irq    : 1; ///< PLL22 LOCK edge detected
            u32 pll0_unlock_irq   : 1; ///< PLL0 UNLOCK edge detected 
            u32 pll1_unlock_irq   : 1; ///< UNLOCK edge detected 
            u32 pll21_unlock_irq  : 1; ///< PLL21 UNLOCK edge detected 
            u32 pll22_unlock_irq  : 1; ///< PLL22 UNLOCK edge detected 
            u32 spk_det_irq       : 1; ///< Speaker plugin detected. 1, speaker plugin
            u32 spk_undet_irq     : 1; ///< Speaker plugout detected.
            u32 pll0_lockr_sense  : 1; ///< PLL0 LOCK raw bit
            u32 pll1_lockr_sense  : 1; ///< PLL1 LOCK raw bit
            u32 pll21_lockr_sense : 1; ///< PLL21 LOCK raw bit
            u32 pll22_lockr_sense : 1; ///< PLL22 LOCK raw bit
            u32 spk_det_sense     : 1; ///< Speaker plugin sense.
            u32 spk_undet_sense   : 1; ///< Speaker plugout sense.
            u32 reserved_2        : 16;                                                                                                                                                                                         
        } bits ;
    } pll_irq;
    union {
        u32 u32_val;
        struct {
            u32 pll0_lock_intmask     : 1; ///<  PLL0 LOCK MASK, 1:mask 0: don't mask
            u32 pll1_lock_intmask     : 1; ///<  PLL1 LOCK MASK, 1:mask 0: don't mask
            u32 pll21_lock_intmask    : 1; ///<  PLL21 LOCK MASK, 1:mask 0: don't mask
            u32 pll22_lock_intmask    : 1; ///<  PLL22 LOCK MASK, 1:mask 0: don't mask
            u32 pll0_unlock_intmask   : 1; ///<  PLL0 UNLOCK MASK, 1:mask 0: don't mask
            u32 pll1_unlock_intmask   : 1; ///<  PLL1 UNLOCK MASK, 1:mask 0: don't mask
            u32 pll21_unlock_intmask  : 1; ///<  PLL21 UNLOCK MASK, 1:mask 0: don't mask
            u32 pll22_unlock_intmask  : 1; ///<  PLL22 UNLOCK MASK, 1:mask 0: don't mask
            u32 spk_det_intmask       : 1; ///<  Speaker plugin interrupt mask, 0:maks  1: don't mask
            u32 spk_undet_intmask     : 1; ///<  Speaker plugout interrupt mask, 0:maks  1: don't mask
            u32 reserved_1            : 6;   
            u32 reserved_2            : 16;                                                                                                                                                                                                         
        } bits ;
    } pll_mask;
    union {
        u32 u32_val;
        struct {
            u32 fuse_lockb_ref  : 1;        ///< if 0, REF trim bit is from EFUSE, if 1 from register EF_REGBIT.
            u32 fuse_reg_sel    : 1;        ///< if 0, REF trim bits is from overwrite register; if 1 from auto trim result register
            u32 ef_regbit       : 6;        ///< EFUSE REGISTER WRITE BIT
            u32 ref_trim_en     : 1;        ///< "enable comparator for reference trim  ,active high. This bit must be set high when software trim."
            u32 fuse_read_en    : 1;        ///< "write 1 to this bit will generate two 32k pulse (self-clear). The 256 bits fuse data will be loaded to the efuse register bank."
            u32 fuse_auto_trim  : 1;        ///< write 1 to this bit will enable auto trim sequence. 
            u32 reserved_1      : 5;    
            u32 reserved_2      : 16;                                                                                                                                                                                                                            
        } bits ;
    } ref_fuse;
    union {
        u32 u32_val;
        struct {
            u32 pm_state : 5;           ///< PM STATE MACHINE STATE (READ ONLY)
            u32 efuse_trim_out : 1;     ///< "EFUSE comparator result (1: REF > EXT_REG; 0: EXT_REF > REF)
                                        /*
                                        if get 1, increase fuse bit value. If get 0, decrease fuse bit value.
                                        This bit can be used in software trim ."
                                        */
            u32 ef_trim_done : 1;       ///< "0, EFUSE auto trim is done; 1, EFUSE is auto-trimming.
                                        /*
                                        After enable EFUSE auto trim, this bit will be set to 1, and after auto trim is done, this bit wil be automaticly reset to 0. EF_TRIM_DATA is only valid when this bit is 0."
                                        */
            u32 ef_trim_data : 6;       ///< EFUSE auto trim result.
            u32 ss_idle_done : 1;       ///< softstart fsm is in IDLE state.  Active high.  
            u32 no_batb_12   : 1;       ///< battery detection from analog 
            u32 reserved_1   : 1;    
            u32 reserved_2   : 16;                                                                                                                                                                                                                            
        } bits ;
    } pmstate;
    union {
        u32 u32_val;
        struct {
            u32 fuse_lockb_dbbio : 1; ///< If 0, DBBIO level select bit is from EFUSE, if 1 from register REG_LVL_VIO1
            u32 fuse_lockb_mmpio : 1; ///< If 0, MMPIO level select bit is from EFUSE, if 1 from register REG_LVL_VIO2
            u32 fuse_lockb_digrf : 1; ///< If 0, digrf level select bit is from EFUSE, if 1 from register EF_REGBIT.
            u32 reg_lvl_digrf    : 2; ///< DIGRF LDO level . 00,1.5v; 01,1.8v; 10, 2.8v; 11,2.9v;
            u32 reg_lvl_vio1     : 2; ///< VIO1 LDO level.  00,1.5v;01,1.8v;10,2.5v;11,2.8v
            u32 reg_lvl_vio2     : 2; ///< VIO2 LDO level. 00,1.5v;01,1.8v;10,2.5v;11,2.8v
            u32 fuse_lockb_va    : 1; ///< if 0, VA level select bit is from EFUSE, if 1 from register AREG_LVL1_VA or SREG_LVL1_VA depending on active state or standby state.
            u32 baton_force      : 1; ///< force BATON to high
            u32 baton_dbc_sel    : 1; ///< 0, 4ms debounce BATON, 1,16ms debounce BATON
            u32 hsgnd_mute_en    : 1; ///< 0, disable HSGND MUTE DAC, 1, enable HSGND MUTE DAC
            u32 reserved_1       : 3;    
            u32 reserved_2       : 16;                                                                                                                                                                                                                            
        } bits ;
    } io_lvl;
    union {
        u32 u32_val;
        struct {
            u32 aux_pwd_ack : 1; ///< AUX power down acknowledge; If 1, power down, if 0, power on.
            u32 aud_pwd_ack : 1; ///< AUDIO power down acknowledge; If 1, power down, if 0, power on.
            u32 rf_pwd_ack  : 1; ///< RF power down acknowledge; If 1, power down, if 0, power on.
            u32 mmp_pwd_ack : 1; ///< MMP power down acknowledge; If 1, power down, if 0, power on.
            u32 emi_pwd_ack : 1; ///< EMI power down acknowledge; If 1, power down, if 0, power on.
            u32 g3d_pwd_ack : 1; ///< G3D power down acknowledge; If 1, power down, if 0, power on.
            u32 disp_pwd_ack : 1; ///< DISP power down acknowledge; If 1, power down, if 0, power on.
            u32 reserved_1  : 9;    
            u32 reserved_2  : 16;                                                                                                                                                                                                                            
        } bits ;
    } pwrack;
    union {
        u32 u32_val;
        struct {
            u32 i2g_vdd_power_en_a : 1; ///< I2G power enable during Active Mode, 0: power off, 1, power on
            u32 i2d_vdd_power_en_a : 1; ///< I2D power enable during Active Mode, 0: power off, 1, power on
            u32 i2g_vdd_power_en_s : 1; ///< I2G power enable during Standby Mode, 0: power off, 1, power on
            u32 i2d_vdd_power_en_s : 1; ///< I2D power enable during Standby Mode, 0: power off, 1, power on
            u32 reserved_1  : 12;    
            u32 reserved_2  : 16;                                                                                                                                                                                                                            
        } bits ;
    } extpwren;
} IncensePMReg_t;



/****************************************************************************/
/*        RTC  registers                           */
/****************************************************************************/
typedef struct IncenseRtcReg_s
{
    u32 rtc_ctrl;
    u32 rtc_spare1;
    u32 rtc_tim1;
    u32 rtc_tim2;
    u32 rtc_cal1;
    u32 rtc_cal2;
    u32 rtc_timalr1;
    u32 rtc_timalr2;
    u32 rtc_calalr1;
    u32 rtc_calalr2;
    u32 rtc_sr;
    u32 rtc_spare2;
    u32 rtc_imr;
    u32 rtc_spare3;
    u32 rtc_pwr_en;
    u32 rtc_spare4;
    u32 u16_Cnt; //rtc_capture;
    u32 rtc_spare5;
    u32 rtc_lt;
} IncenseRtcReg_t; 

/* control register */
#define RTC_STOP_CNT                 (1 << 0)  // freeze the counter when highest
#define RTC_TIMEVTSEL_POS          1
#define RTC_TIMEVTSEL_MINUTE     (0 << RTC_TIMEVTSEL_POS)  
#define RTC_TIMEVTSEL_HOUR        (1 << RTC_TIMEVTSEL_POS)  
#define RTC_TIMEVTSEL_MIDNIGHT  (2 << RTC_TIMEVTSEL_POS)
#define RTC_TIMEVTSEL_NOON        (3 << RTC_TIMEVTSEL_POS)
#define RTC_TIMEVTSEL_MASK        (3 << RTC_TIMEVTSEL_POS) 

#define RTC_CALEVTSEL_POS       3
#define RTC_CALEVTSEL_WEEK        (0 << RTC_CALEVTSEL_POS)
#define RTC_CALEVTSEL_MONTH        (1 << RTC_CALEVTSEL_POS)
#define RTC_CALEVTSEL_YEAR        (2 << RTC_CALEVTSEL_POS)
#define RTC_CALEVTSEL_MASK        (3 << RTC_CALEVTSEL_POS)

#define RTC_ALRCLR                    (1 << 8)   /* alarm event status clear */
#define RTC_SECCLR                    (1 << 9)   /* second event status clear */
#define RTC_TIMCLR                    (1 << 10) /* time event status clear */
#define RTC_CALCLR                    (1 << 11) /* time event status clear */

/* register time */
#define RTC_SEC_POS     0 /* second */
#define RTC_SEC_MASK   (0x3f << RTC_SEC_POS)
#define RTC_MIN_POS     8 /* minute */
#define RTC_MIN_MASK   (0x3f << RTC_MIN_POS)
#define RTC_HOUR_POS          16 /* hour */
#define RTC_HOUR_MASK (0x01f << RTC_HOUR_POS)  

/* date register */
#define RTC_DATE_POS        0 /* 1 - 31 */
#define RTC_DATE_MASK        (0x1f << RTC_DATE_POS)     
#define RTC_DAY_POS         8 /* day 1 - 7 */
#define RTC_DAY_MASK        (0x07 << RTC_DAY_POS)     
#define RTC_MONTH_POS     12 /* month 1 - 12 */
#define RTC_MONTH_MASK        (0x0f << RTC_MONTH_POS)     
#define RTC_YEAR_POS        16 /* year */
#define RTC_YEAR_MASK        (0x7f << RTC_YEAR_POS)     
#define RTC_CENT_POS        24 /* century */
#define RTC_CENT_MASK        (0x1f << RTC_CENT_POS)     

/* time alarm register */

#define RTC_ALRM_SEC_POS     0 /* second */
#define RTC_ALRM_SEC_MASK   (0x3f << RTC_ALRM_SEC_POS)
#define RTC_ALRM_SEC_EN       (1 << 7) /* second alarm enable */
#define RTC_ALRM_MIN_POS     8 /* minute */
#define RTC_ALRM_MIN_MASK   (0x3f << RTC_ALRM_MIN_POS)
#define RTC_ALRM_MIN_EN       (1 << 15) /* minute alarm enable */
#define RTC_ALRM_HOUR_POS          16 /* hour */
#define RTC_ALRM_HOUR_MASK (0x1f << RTC_ALRM_HOUR_POS)  
#define RTC_ALRM_HOUR_EN       (1 << 23) /* hour alarm enable */

/* calendar alarm register */

#define RTC_ALRM_DATE_POS        0 /* 1 - 31 */
#define RTC_ALRM_DATE_MASK        (0x1f << RTC_DATE_POS)     
#define RTC_ALRM_DATE_EN          (1 << 8) /* date alarm enable */
#define RTC_ALRM_MONTH_POS     12 /* month 1 - 12 */
#define RTC_ALRM_MONTH_MASK        (0x0f << RTC_MONTH_POS)
#define RTC_ALRM_MONTH_EN       (1 << 16) /* month alarm enable */

/* status register */
#define RTC_STATUS_CIA          (1 << 0) /* CPU interface active */
#define RTC_STATUS_ACKUPD     (1 << 1) /* updating time & date register available */
#define RTC_STATUS_ALREVT     (1 << 2) /* alarm event status*/
#define RTC_STATUS_SECEVT     (1 << 3) /* second event status*/
#define RTC_STATUS_TIMEVT     (1 << 4) /* time event status */
#define RTC_STATUS_CALEVT     (1 << 5) /* calendar event status */
#define RTC_STATUS_CTRL_RESY     (1 << 6) /* control register resynchronization */
#define RTC_STATUS_TIME_RESY     (1 << 7) /* time register resynchronization */
#define RTC_STATUS_DATE_RESY     (1 << 8) /* date register resynchronization */
#define RTC_STATUS_IMR_RESY     (1 << 9) /* imr register resynchronization */
#define RTC_STATUS_PWR_RESY     (1 << 10) /* power register resynchronization */
#define RTC_STATUS_TIMEALR_RESY     (1 << 11) /* time alarm register resynchronization */
#define RTC_STATUS_CALALR_RESY     (1 << 12) /* calendar alarm register resynchronization */

/* imr register */
#define RTC_IMR_ALREN				(1 << 0)	/* enable alarm interrupt */
#define RTC_IMR_SECEN				(1 << 1) /* enable second interrupt */
#define RTC_IMR_TIMEEN			(1 << 2) /* enable time interrupt */
#define RTC_IMR_CALEN				(1 << 3) /* enable calendar interrupt */

/* power control register */
#define RTC_CPU_ITF_EN			( 1 << 0) /* CPU interface enable */
#define RTC_PWR_EN						( 1 << 1) /* power enable pads value for direct control */
#define RTC_ALR_SIG_EN			( 1 << 2) /* RTC_PWR_EN pads is controlled by the alarm output */
#define RTC_SW_RST						( 1 << 3) /* RTC module software reset */
#define RTC_CK32K_OUT_EN	( 1 << 4) /* clock 32 khz available to internal use */
#define RTC_LIFE_REG					( 1 << 8) 

#define INCENSE_AREG_EN_AUDDIG      (1<<14) ///< AUDIO digital power gate enable bit in active mode
#define INCENSE_AREG_EN_RFDIG       (1<<13) ///< RF digital power gate enable bit in active mode , active high
#define INCENSE_AREG_EN_EMI         (1<<12) ///< MMP1 in Athena enable bit in active mode , active high
#define INCENSE_AREG_EN_MMP         (1<<11) ///< MMP0 in Athena enable bit in active mode , active high
#define INCENSE_AREG_EN_PER4        (1<<10) ///< PERIPHERAL4 LDO enable bit in active mode, active high
#define INCENSE_AREG_EN_PER3        (1<<9) ///< PERIPHERAL3 LDO enable bit in active mode, active high
#define INCENSE_AREG_EN_PER2        (1<<8) ///< PERIPHERAL2 LDO enable bit in active mode, active high
#define INCENSE_AREG_EN_PER1        (1<<7) ///< PERIPHERAL1 LDO enable bit in active mode , active high
#define INCENSE_AREG_EN_VDBBIO      (1<<6) ///< DBBIO LDOenable bit in active mode , active high
#define INCENSE_AREG_EN_VMMPIO      (1<<5) ///< MMPIO LOD enable bit in active mode , active high
#define INCENSE_AREG_EN_VDIGRF      (1<<4) ///< DIGRF LDO enable bit in active mode , active high
#define INCENSE_AREG_EN_VA          (1<<3) ///< TCXO LDO enable bit in active mode , active high
#define INCENSE_AREG_EN_VABBAUD     (1<<2) ///< ABBAUD LDO enable bit in active mode , active high
#define INCENSE_AREG_EN_VAUX        (1<<1) ///< AUX LDO enable bit in active mode , active high
#define INCENSE_AREG_EN_VABBRF      (1<<0) ///< ABBRF LDO enable bit in active mode, active high


/****************************************************************************/
/*        AUX  registers                           */
/****************************************************************************/
typedef struct IncenseAuxReg_s
{
	u32		adc_cfg;				//0x00
	u32 	adc_test;				//0x04
	u32		adc_timing_cfg1;		//0x08
	u32		adc_timing_cfg2;		//0x0C
	u32		adc_timing_cfg_job;		//0x10
	u32		adc_job;				//0x14
	u32		adc_res0;				//0x18
	u32		adc_res1;				//0x1C
	u32		adc_res2;				//0x20
	u32		adc_res3;				//0x24
	u32		cycle_ctl;				//0x28
	u32		ts_ref1;				//0x2C
	u32		ts_ref2;				//0x30
	u32		free_run_tst;			//0x34
	u32		pll_set1;				//0x38
	u32		pll_set2;				//0x3C
	u32		pll_set3;				//0x40
	u32		pll_test1;				//0x44
	u32 	pll_test2;				//0x48
	u32		pll_test3;				//0x4C
	u32		bist_cfg;				//0x50
	u32		bist_status;			//0x54
	u32		bist_clear;				//0x58
	u32		device_id;				//0x5C
	u32		bist_sts_clear;			//0x60
} IncenseAuxReg_t;

//PLL_SET2 Register
#define PLL0_DIVFB_POS				0
#define PLL0_DIVFB_MSK				((u32)0x003F<<PLL0_DIVFB_POS) 
#define PLL21_DIVFB_POS				6
#define PLL21_DIVFB_MSK				((u32)0x003F<<PLL21_DIVFB_POS)
#define N_FDBACK_DIV_FACTOR_52      1  // N value permitting to set a core clock to 26 MHz
#define N_FDBACK_DIV_FACTOR_104     3  // N value permitting to set a core clock to 208 MHz
#define N_FDBACK_DIV_FACTOR_208     7  // N value permitting to set a core clock to 208 MHz
#define N_FDBACK_DIV_FACTOR_234	    8  // N value permitting to set a core clock to 234 MHz
#define N_FDBACK_DIV_FACTOR_260     9  // N value permitting to set a core clock to 260 MHz
#define N_FDBACK_DIV_FACTOR_312     11 // N value permitting to set a core clock to 312 MHz
#define N_FDBACK_DIV_FACTOR_364     13 // N value permitting to set a core clock to 364 MHz
#define N_FDBACK_DIV_FACTOR_416     15 // N value permitting to set a core clock to 416 MHz
#define PLL0_AUTO_PWD_EN			((u32)0x01<<12)
#define PLL1_AUTO_PWD_EN			((u32)0x01<<13)
#define PLL21_AUTO_PWD_EN			((u32)0x01<<14)
#define PLL22_AUTO_PWD_EN			((u32)0x01<<15)

#define AUDIO_BASE_OFFSET           0x00 
#define RTC_BASE_OFFSET             (0x40*2)
#define AUD_ANALOG_BASE_OFFSET      (0x70*2)
#define PM_BASE_OFFSET              (0x80*2)
#define AUX_BASE_OFFSET             (0xC0*2)

extern volatile IncensePMReg_t* const IncensePMReg;
extern volatile IncenseRtcReg_t* const IncenseRtcReg;
//extern volatile IncenseAuxReg_t* const IncenseAuxReg;

#endif // __INCENSE_REG_H__

