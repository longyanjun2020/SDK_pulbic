#ifndef _R2A30423NP_H_
#define _R2A30423NP_H_
 
//******************************************************************************
//
//                             DEFINITION. in Register Guide
//
//******************************************************************************
#define GPIO_HIGH                 0x01
#define GPIO_LOW                  0x00

//******************************************************************************
//
//                             Zoom LUT , Conversion between index and micro step.
//
//******************************************************************************

//*********************************************************
// FOR CHANNEL SELECTION b14~b15.
//*********************************************************
#define REG_CH1_CH2               0x00
#define REG_CH3_CH4               0x01
#define REG_CH5_CH7               0x02
#define REG_COMMON                0x03

//*********************************************************
// FOR CHANNEL 1,2.
//*********************************************************
#define REG_DRV_CTRL              0x00
#define REG_N_PULSE1              0x01
#define REG_N_PULSE2              0x02
#define REG_PULSE_RATE            0x03
#define REG_nPULSE_RANGE          0x04
#define REG_nPULSE_ACC_DEC        0x05
#define REG_PULSE_RATE1           0x06
#define REG_PULSE_RATE2           0x07
#define REG_PULSE_RATE3           0x08
#define REG_PULSE_RATE4           0x09
#define REG_PRE_PULSE_EXT         0x0A
#define REG_POST_PULSE_EXT        0x0B
#define REG_PROHIBITED            0x0C
#define REG_DRV_VOL_AMP           0x0D
#define REG_POS_READ              0x0E
#define REG_OP_CTRL_REG           0x0F

//*********************************************************
// FOR CHANNEL 3,4.
//*********************************************************
#define REG_DRV_DC_VOL            0x0C

//*********************************************************
// FOR CHANNEL 5,7.
//*********************************************************
#define REG_PWM_CTRL              0x0C
#define REG_PWM_DUTY_CYC1         0x0D
#define REG_PWM_DUTY_CYC2         0x0E

//*********************************************************
// FOR COMMON REGISTER.
//*********************************************************
#define REGC_EXT_SETTING          0x01
#define REGC_PI_SETTING           0x02
#define REGC_PS_SETTING           0x03
#define REGC_INPUT_SETTING        0x05
#define REGC_CH5_SETTING          0x06
#define REGC_CH6_SETTING          0x07
#define REGC_SW_RST               0x08
#define REGC_EXCLUSIVE            0x09
#define REGC_STATUS_READ          0x0A
#define REGC_FLAG_CTRL1_CH12      0x0B
#define REGC_FLAG_CTRL2_CH34      0x0C
#define REGC_FLAG_CTRL3_CH57      0x0D
#define REGC_OP_SETTING           0x0F
// For Ch3 and CH4
#define REG_COM_uSTEP_POS         0x0E
// For Ch5 and CH7
#define REG_COM_CUR_POS           0x0E


//*********************************************************
// FOR REGISTER SETTING.
//*********************************************************
//*********************************************************
// FOR CHANNEL 1,2.
//*********************************************************
// REG00:  REG_DRV_CTRL
#define DRV_DIR(x)             (x << 9)   // Range 
#define DRV_MODE(x)            (x << 6)
#define DRV_CTRL(x)            (x << 4)
#define SET_INIT_POS_EXCITE(x) (x << 1)
#define DRV_INIT_POS_EXCITE(x) (x << 0)


// REG01:  REG_N_PULSE1
#define DRV_nPULSE1(x)         (x & 0x03FF)

// REG02:  REG_N_PULSE2
#define DRV_nPULSE2(x)         (x >> 10)

// REG03:  REG_PULSE_RATE0
#define PULSE_RATE(x)          (x & 0x03FF)

// REG04:  REG_PULSE_RATE
#define DRV_PULSE_RATE(x)      (x << 6)

#define DRV_uSTEP_nSTEP(x)     (x << 4)

// REG05:  REG_nPULSE_RANGE
#define nPULSE_ACCDEC(x)       (x & 0x03FF)

// REG06:  REG_nPULSE_ACC_DEC
#define DRV_nPULSE_ACC_DEC(x)  (x << 0)


#define DRV_PRE_EXCITE(x)      (x << 4)   // Range 0 ~ 63
#define DRV_PRE_EXCITE(x)      (x << 4)   // Range 0 ~ 63

// REG13:  REG_DRV_VOL_AMP
// For Ch1 and CH2 Only
#define DRV_VOL_AMP_CH1_2(x)   (x << 6)   // Range 0 ~15
#define DRV_VOL_GAIN_CH1_2(x)  (x << 4)

// REG15:  REG_OP_CTRL_REG



//*********************************************************
// FOR CHANNEL 3,4.
//*********************************************************
#define DRV_DC1_DIR(x)         (x << 9)
#define DRV_DC1_VOL(x)         (x << 5)   // Range 0 ~ 15
#define DRV_DC2_DIR(x)         (x << 4)
#define DRV_DC2_VOL(x)         (x << 0)   // Range 0 ~ 15
#define DRV_VOL_AMP_CH3(x)     (x << 6)   // Range 0 ~ 15
#define DRV_VOL_GAIN_CH4(x)    (x << 1)   // Range 0 ~ 15
#define DRV_VOL_GAIN_CH3_4(x)  (x << 5)

//*********************************************************
// FOR CHANNEL 5,7.
//*********************************************************
#define DRV_DC_DIR_CH5(x)      (x << 9)
#define DRV_DC_STOP_CH5(x)     (x << 8)   // 0: OFF.     1: BRAKE.
#define DRV_DC_PWM_CH5(x)      (x << 7)   // 0: BRAKE.   1: REVERSE.
#define DRV_DC_PWM_FREQ_CH5(x) (x << 6)
#define DRV_DC_DUTY_CH5_7(x)   (x << 4)   // Range 0 ~ 63

// For Ch7 Only
#define DRV_DC_DIR_CH7(x)      (x << 4)
#define DRV_DC_STOP_CH7(x)     (x << 3)   // 0: OFF.     1: BRAKE.
#define DRV_DC_PWM_CH7(x)      (x << 2)   // 0: BRAKE.   1: REVERSE.
#define DRV_DC_PWM_FREQ_CH7(x) (x << 1)


//*********************************************************
// FOR COMMON REG
//*********************************************************
//---------------------------------------------------------
// REG01: REG_COM_EXT_SETTING
//---------------------------------------------------------
#define DRV_EXT_OUTPUT_SEL(x)  (x << 8)   // 0: DISABLE. 1:ENABLE.
#define DRV_OUTPUT_PIN_SEL(x)  (x << 7)   // 0: RELEASE. 1:HOLD.
#define DRV_EXT1_SEL(x)        (x << 5)   // 0: DISABLE. 1:ENABLE.
#define DRV_EXT2_SEL(x)        (x << 3)   // 0: DISABLE. 1:ENABLE.

//---------------------------------------------------------
// REG02: REG_COM_PI_SETTING
//---------------------------------------------------------
#define DRV_PI1_STATE(x)       (x << 9)   // 0: HIGH Z.  1: LOW-LEVEL 
#define DRV_PI2_STATE(x)       (x << 8)   // 0: HIGH Z.  1: LOW-LEVEL.
#define DRV_PI3_STATE(x)       (x << 7)   // 0: HIGH Z.  1: LOW-LEVEL.

//---------------------------------------------------------
// REG03: REG_COM_PS_SETTING
//---------------------------------------------------------
#define DRV_PS_STATE(x)        (x << 9)   // 0: POWER OFF.   1: POWER ON.
#define DRV_PS12_STATE(x)      (x << 8)   // 0: CH1,CH2 OFF. 1: CH1,CH2 ON.
#define DRV_PS34_STATE(x)      (x << 6)   // 0: CH3,CH4 OFF. 3: CH3,CH4 ON. 


//---------------------------------------------------------
// REG08: REG_COM_SW_RST
//---------------------------------------------------------
#define DRV_RST_CH(x)          (1 << x) 
#define DRV_DEC2STOP_CH(x)     (1 << x)

//---------------------------------------------------------
// REG15: REG_OP_CTRL_REG
//---------------------------------------------------------
#define DRV_OP_EN(x)           (x << 9)   // 0: DISABLE. 1:ENABLE.
#define DRV_OP_STATE(x)        (x << 8)   // 0: RELEASE. 1:HOLD.
#define DRV_EXCITE_EN(x)       (x << 7)   // 0: DISABLE. 1:ENABLE.
#define DRV_OP_EN_CH4_7(x)     (x << 6)   // 0: DISABLE. 1:ENABLE.
#define DRV_CONT_OP_EN(x)      (x << 5)   // 0: DISABLE. 1:ENABLE.

//******************************************************************************
//
//                             STRUECTURE
//
//******************************************************************************
//*********************************************************
// FOR CHANNEL 1,2.
//*********************************************************
//---------------------------------------------------------
// REG00:  REG_DRV_CTRL
//---------------------------------------------------------
typedef enum _MOTOR_DRV_DIR {
    DRV_FORWARD = 0 ,
    DRV_BACKWARD
}MOTOR_DRV_DIR;

typedef enum _MOTOR_DRV_MODE {
    DRV_MICRO_STEP = 0 ,
    DRV_1_2PHASE_100,
    DRV_1_2PHASE_70,
    DRV_2_2PHASE,

  // FOR CH3 and CH4 Only
    DRV_DC_BTL_CH3,
    DRV_DC_PWM_CH4,
    DRV_DC_PWM_PARALLEL,    
    DRV_PROHIBITED

}MOTOR_DRV_MODE;

typedef enum _MOTOR_DRV_CTRL {
    DRV_CTRL_NO_ACC_DEC = 0 ,
    DRV_CTRL_DEC,
    DRV_CTRL_ACC,
    DRV_CTRL_ACC_DEC
}MOTOR_DRV_CTRL;

typedef enum _MOTOR_DRV_INIT_POS {
    DRV_p100_p100 = 0 ,
    DRV_0_p100,
    DRV_n100_p100,
    DRV_n100_0,
    DRV_n100_n100,
    DRV_0_n100,
    DRV_p100_n100,
    DRV_p100_0
}MOTOR_DRV_INIT_POS;

typedef enum _MOTOR_DRV_INIT_EXCITE {
    DRV_DISABLE = 0 ,
    DRV_ENABLE
}MOTOR_DRV_INIT_EXCITE;

//---------------------------------------------------------
// REG04:  DRV_PULSE_RATE RANGE
//---------------------------------------------------------
typedef enum _MOTOR_DRV_PULSE_RATE_RANGE {
    DRV_PULSE_RATE_RANGE_2048 = 0 ,
    DRV_PULSE_RATE_RANGE_1024,
    DRV_PULSE_RATE_RANGE_512 ,
    DRV_PULSE_RATE_RANGE_256 ,
    DRV_PULSE_RATE_RANGE_128 ,
    DRV_PULSE_RATE_RANGE_64  ,
    DRV_PULSE_RATE_RANGE_32  ,
    DRV_PULSE_RATE_RANGE_16  ,
    DRV_PULSE_RATE_RANGE_8   ,
    DRV_PULSE_RATE_RANGE_4   ,
    DRV_PULSE_RATE_RANGE_2
}MOTOR_DRV_PULSE_RATE_RANGE;

// FOR MICRO STEP ONLY
typedef enum _MOTOR_DRV_nSTEP {
    DRV_nSTEP_256 = 0 ,
    DRV_nSTEP_128,
    DRV_nSTEP_64 ,
    DRV_nSTEP_32 
}MOTOR_DRV_nSTEP;

//---------------------------------------------------------
// REG10:  REG_PRE_PULSE_EXT
//---------------------------------------------------------
//---------------------------------------------------------
// REG11:  REG_POST_PULSE_EXT
//---------------------------------------------------------

//---------------------------------------------------------
// REG13:  REG_DRV_VOL_AMP
//---------------------------------------------------------
typedef enum _MOTOR_DRV_AMP_VAL {
    DRV_AMP_FULL_SCALE = 0x00 ,
    DRV_AMP_VOL_48,
    DRV_AMP_VOL_46,
    DRV_AMP_VOL_44,
    DRV_AMP_VOL_42,
    DRV_AMP_VOL_40,  // in-valid in ch1 & ch2 mode.
    DRV_AMP_VOL_38,
    DRV_AMP_VOL_36,
    DRV_AMP_VOL_34,
    DRV_AMP_VOL_32,
    DRV_AMP_VOL_30,
    DRV_AMP_VOL_28,
    DRV_AMP_VOL_26,
    DRV_AMP_VOL_24,
    DRV_AMP_VOL_22,
    DRV_AMP_VOL_20
}MOTOR_DRV_AMP_VAL;

typedef enum _MOTOR_DRV_GAIN {
    DRV_GAIN_ONE = 0,
    DRV_GAIN_TWICE 
}MOTOR_DRV_GAIN;


//---------------------------------------------------------
// REG14:  REG_POS_READ
//---------------------------------------------------------

//---------------------------------------------------------
// REG15:  REG_OP_CTRL_REG
//---------------------------------------------------------
typedef enum _MOTOR_DRV_OP_CTRL {
    DRV_OP_DISABLE = 0,         // Excitation off
    DRV_OP_ENABLE               // Excitation on, pulse transition proceed.
}MOTOR_DRV_OP_CTRL;

typedef enum _MOTOR_DRV_OP_STATE {
    DRV_OP_RELEASE = 0,         // Excitation off
    DRV_OP_HOLD                 // Excitation on, but pulse transition stop.
}MOTOR_DRV_OP_STATE;


//*********************************************************
// FOR CHANNEL 3,4.
//*********************************************************
//---------------------------------------------------------
// REG12:  REG_DRV_DC_VOL
//---------------------------------------------------------
typedef enum _MOTOR_DRV_VOL_OUTPUT {
    DRV_DC_VOL_00_PERCENT = 0 ,
    DRV_DC_VOL_10_PERCENT     ,
    DRV_DC_VOL_20_PERCENT     ,
    DRV_DC_VOL_29_PERCENT     ,
    DRV_DC_VOL_38_PERCENT     ,
    DRV_DC_VOL_47_PERCENT     ,
    DRV_DC_VOL_56_PERCENT     ,
    DRV_DC_VOL_63_PERCENT     ,
    DRV_DC_VOL_71_PERCENT     ,
    DRV_DC_VOL_77_PERCENT     ,
    DRV_DC_VOL_83_PERCENT     ,
    DRV_DC_VOL_88_PERCENT     ,
    DRV_DC_VOL_92_PERCENT     ,
    DRV_DC_VOL_96_PERCENT     ,
    DRV_DC_VOL_98_PERCENT     ,
    DRV_DC_VOL_100_PERCENT
}MOTOR_DRV_VOL_OUTPUT;


//*********************************************************
// FOR CHANNEL 5,7.
//*********************************************************
//---------------------------------------------------------
// REG12:  REG_PWM_CTRL
//---------------------------------------------------------
typedef enum _MOTOR_DRV_STOP_MODE {
    MOTOR_DRV_STOP_OFF = 0 ,
    MOTOR_DRV_STOP_BRAKE
}MOTOR_DRV_STOP_MODE;

typedef enum _MOTOR_DRV_PWM_MODE {
    MOTOR_DRV_PWM_BRAKE = 0 ,
    MOTOR_DRV_PWM_REVERSE
}MOTOR_DRV_PWM_MODE;

typedef enum _MOTOR_DRV_PWM_FREQ {
    DRV_PWM_FREQ_32 = 0 ,
    DRV_PWM_FREQ_48
}MOTOR_DRV_PWM_FREQ;

//---------------------------------------------------------
// REG13:  REG_PWM_DUTY_CYC1
//---------------------------------------------------------

//---------------------------------------------------------
// REG14:  REG_PWM_DUTY_CYC2
//---------------------------------------------------------

//---------------------------------------------------------
// REG15:  REG_PWM_DUTY_CYC2
//---------------------------------------------------------




//*********************************************************
// FOR COMMON REG
//*********************************************************
//---------------------------------------------------------
// REG01: REG_COM_EXT_SETTING
//---------------------------------------------------------
typedef enum _MOTOR_EXT_DATA_SEL {
    DRV_EXT_HIGH_IN_EXCITE = 0 ,
    DRV_EXT_HIGH_IN_PULSE_TRANS
}MOTOR_EXT_DATA_SEL;

typedef enum _MOTOR_MOB_SDO_PIN_SEL {
    DRV_EXT_PIN_MOB = 0 ,
    DRV_EXT_PIN_SDO  
}MOTOR_MOB_SDO_PIN_SEL;

typedef enum _MOTOR_EXT1_PIN_SEL {
    DRV_EXT1_PIN_EXT12 = 0 ,
    DRV_EXT1_PIN_EXT34   ,
    DRV_EXT1_PIN_ST12    ,
    DRV_EXT1_PIN_ST34    
}MOTOR_EXT1_PIN_SEL;

typedef enum _MOTOR_EXT2_PIN_SEL {
    DRV_EXT2_PIN_EXT34 = 0 ,
    DRV_EXT2_PIN_EXT57  ,
    DRV_EXT2_PIN_ST34   ,
    DRV_EXT2_PIN_ST57
}MOTOR_EXT2_PIN_SEL;

//---------------------------------------------------------
// REG02: REG_COM_PI_SETTING
//---------------------------------------------------------
typedef enum _MOTOR_DRV_PI_STATE {
    DRV_PI_OUTPUT_HIGH_Z = 0,
    DRV_PI_OUTPUT_LOW_LEVEL
}MOTOR_DRV_PI_STATE;
//---------------------------------------------------------
// REG03: REG_COM_PS_SETTING
//---------------------------------------------------------
typedef enum _MOTOR_DRV_POWER_STATE {
    DRV_POWER_OFF = 0,
    DRV_POWER_ON
}MOTOR_DRV_POWER_STATE;

typedef enum _MOTOR_DRV_CH12_STATE {
    DRV_CH12_OFF = 0,
    DRV_CH12_ON = 1
}MOTOR_DRV_CH12_STATE;


typedef enum _MOTOR_DRV_CH34_STATE {
    DRV_CH34_OFF = 0,
    DRV_CH34_ON = 3
}MOTOR_DRV_CH34_STATE;
//---------------------------------------------------------
// REG04: REG_COM_INPUT_SETTING
//---------------------------------------------------------
typedef enum _MOTOR_DRV_EDGE_SEL {
    DRV_EDGE_ACTIVE_HIGH = 0,
    DRV_EDGE_ACTIVE_LOW
}MOTOR_DRV_EDGE_SEL;

//---------------------------------------------------------
// REG06: REG_COM_CH5_SETTING
//---------------------------------------------------------
//---------------------------------------------------------
// REG07: REG_COM_CH6_SETTING
//---------------------------------------------------------
typedef enum _MOTOR_DRV_CONST_CURRENT_SETTING {
    DRV_CONST_CURRENT_310mV = 0,
    DRV_CONST_CURRENT_300mV ,
    DRV_CONST_CURRENT_290mV ,
    DRV_CONST_CURRENT_280mV ,
    DRV_CONST_CURRENT_270mV ,
    DRV_CONST_CURRENT_260mV ,
    DRV_CONST_CURRENT_250mV ,
    DRV_CONST_CURRENT_240mV ,
    DRV_CONST_CURRENT_230mV ,
    DRV_CONST_CURRENT_220mV ,
    DRV_CONST_CURRENT_210mV ,
    DRV_CONST_CURRENT_200mV ,
    DRV_CONST_CURRENT_190mV ,
    DRV_CONST_CURRENT_180mV ,
    DRV_CONST_CURRENT_170mV ,
    DRV_CONST_CURRENT_160mV
}MOTOR_DRV_CONST_CURRENT_SETTING;


typedef enum _MOTOR_DRV_WEAK_EXCITATION {
    DRV_WEAK_EXCITATION_OFF = 0,
    DRV_WEAK_EXCITATION_ON 
}MOTOR_DRV_WEAK_EXCITATION;
//---------------------------------------------------------
// REG08: REG_COM_SW_RST
//---------------------------------------------------------
typedef enum _MOTOR_DRV_CH_RST {
    DRV_RST_CH5_CH7 = 7 ,
    DRV_RST_CH3_CH4     ,
    DRV_RST_CH1_CH2
    
}MOTOR_DRV_CH_RST;

typedef enum _MOTOR_DRV_CH_DEC2STOP {
    DRV_DEC_CH5_CH7 = 4 ,
    DRV_DEC_CH3_CH4     ,
    DRV_DEC_CH1_CH2
    
}MOTOR_DRV_CH_DEC2STOP;

//---------------------------------------------------------
// REG09: REG_COM_EXCLUSIVE
//---------------------------------------------------------
typedef enum _MOTOR_DRV_EXCLUSIVE_CTRL {
    DRV_MODE_NORMAL = 0 ,
    DRV_MODE_EXCLUSIVE  
    
}MOTOR_DRV_EXCLUSIVE_CTRL;

//---------------------------------------------------------
// REG10: REG_COM_STATUS_READ
//---------------------------------------------------------
typedef enum _MOTOR_DRV_OUTPUS_STATUS {
    DRV_STATUS_OFF = 0     ,
    DRV_STATUS_PRE_EXCITE  ,
    DRV_STATUS_ACC         ,
    DRV_STATUS_CONST       ,
    DRV_STATUS_DEC         ,
    DRV_STATUS_POST_EXCITE ,
    DRV_STATUS_EXCITE_EXCLUDE

}MOTOR_DRV_OUTPUS_STATUS;

//******************************************************************************
//
//                              VARIABLES
//
//******************************************************************************
typedef enum _MOTOR_DRV_SPEED_MODE {
    DRV_SPEED_CONST = 0    ,
    DRV_SPEED_ACC_LOW  ,
    DRV_SPEED_ACC_MID  ,
    DRV_SPEED_ACC_HIGH 
}MOTOR_DRV_SPEED_MODE;

typedef enum _MOTOR_DRV_POWSER_MODE {
    DRV_POWER_CH1_CH2 = 0,
    DRV_POWER_CH3_CH4   ,
    DRV_POWER_CH5_CH6  
}MOTOR_DRV_POWER_MODE;

#endif

