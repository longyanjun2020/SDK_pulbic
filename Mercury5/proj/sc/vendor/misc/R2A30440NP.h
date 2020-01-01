#ifndef _R2A30440NP_H_
#define _R2A30440NP_H_
 
//******************************************************************************
//
//                             DEFINITION. in Register Guide
//
//******************************************************************************
#ifndef GPIO_HIGH
#define GPIO_HIGH                 0x01
#endif
#ifndef GPIO_LOW
#define GPIO_LOW                  0x00
#endif

//******************************************************************************
//
//                   REG ADDR DEFINITION.
//
//******************************************************************************

/***  FOR CHANNEL SELECTION ********************************/
#define REG_CH12                  0x00
#define REG_CH34                  0x01
#define REG_CH567                 0x02
#define REG_COMMON                0x03

/***  FOR CHANNEL 1,2. *************************************/
#define REG_DRV_CTRL              0x00
#define REG_N_PULSE1              0x01
#define REG_N_PULSE2              0x02
#define REG_PULSE_RATE0           0x03
#define REG_nPULSE_RANGE          0x04
#define REG_nPULSE_ACC_DEC        0x05
#define REG_PULSE_RATE1           0x06
#define REG_PULSE_RATE2           0x07
#define REG_PULSE_RATE3           0x08
#define REG_PULSE_RATE4           0x09
#define REG_PRE_PULSE_EXT         0x0A
#define REG_POST_PULSE_EXT        0x0B
#define REG_READ_PULSE_POS1       0x0C
#define REG_READ_PULSE_POS2       0x0D
#define REG_DRV_VOL_VAL           0x0E
#define REG_OP_CTRL               0x0F

/***  FOR CHANNEL 3,4. *************************************/
#define REG_DRV_DC_VOL            0x0C

/***  FOR CHANNEL 5,6,7 ************************************/
#define REG_PWM_CTRL              0x0C
#define REG_PWM_DUTY_CYC1         0x0D
#define REG_PWM_DUTY_CYC2         0x0E

/***  FOR COMMON REGISTER. *********************************/
#define REGC_ACTUATOR_SEL         0x00
#define REGC_BF1_TERMINAL_SETUP   0x01
#define REGC_FLL_CMP1_SETUP       0x02
#define REGC_FLL_CMP2_SETUP       0x03
#define REGC_PI_PS_SETUP          0x04
#define REGC_OUTPUT_SETUP         0x05
#define REGC_SW_RST               0x06
#define REGC_CH3_DC_DRV_CTRL      0x07
#define REGC_CH3_DC_VOL_SETUP     0x08
#define REGC_CH4_DC_DRV_CTRL      0x09
#define REGC_CH4_DC_VOL_SETUP     0x0A
#define REGC_CH3_CH4_OP_CTRL      0x0B
#define REGC_CH12_STATUS_FLAG     0x0C
#define REGC_CH34_STATUS_FLAG     0x0D
#define REGC_STM12_STATUS_FLAG    0x0E
#define REGC_STM12_OP_CTRL2       0x0F

//*********************************************************************************
// FOR REGISTER SETTING.
//*********************************************************************************

/*****************************************************
   FOR CHANNEL 1,2( REG_CH12 )
*****************************************************/
/*****************************************************
   FOR CHANNEL 3,4( REG_CH34 )
*****************************************************/
//--  REG00: REG_DRV_CTRL  -------------------
#define DRV_CTRL_DIR(x)          (x << 9)     // Range 
#define DRV_CTRL_MODE(x)         (x << 6)
#define DRV_CTRL_SPEED_TYPE(x)   (x << 4)
#define SET_INIT_POS_EXCITE(x)   (x << 1)   
#define DRV_INIT_POS_EXCITE(x)   (x)          // 0: DISABLE. 1:ENABLE.

//--  REG01: REG_N_PULSE1  -------------------
#define nPULSE1(x)               (x & 0x03FF)

//--  REG02: REG_N_PULSE2  -------------------
#define nPULSE2(x)               (x >> 10)& 0x03FF

//--  REG03: REG_PULSE_RATE0  ----------------
//--  REG06: REG_PULSE_RATE1  ----------------
//--  REG07: REG_PULSE_RATE2  ----------------
//--  REG08: REG_PULSE_RATE3  ----------------
//--  REG09: REG_PULSE_RATE4  ----------------
#define PULSE_RATE(x)            (x & 0x03FF)

//--  REG04: REG_nPULSE_RANGE  ---------------
#define PULSE_RATE_RANGE(x)      (x << 6)
#define SET_STOP_POS(x)          (x & 0x03)

//--  REG05: REG_nPULSE_ACC_DEC  -------------
#define nPULSE_ACCDEC(x)         (x & 0x03FF)

//--  REG10: REG_PRE_PULSE_EXT  --------------
#define nPRE_EXT_TIME(x)         ((x & 0x3F)<< 4)

//--  REG11: REG_POST_PULSE_EXT  -------------
#define nPOST_EXT_TIME(x)        ((x & 0x3F)<< 4)

//--  REG12: REG_READ_PULSE_POS1  ------------
#define DRV_PRE_EXCITE(x)        (x << 4)     // Range 0 ~ 63

//--  REG13: REG_READ_PULSE_POS2  ------------
#define DRV_POST_EXCITE(x)       (x << 4)     // Range 0 ~ 63
                
//--  REG14: REG_DRV_VOL_VAL  ----------------
// For Ch1 and CH2 Only          
#define DRV_VOL_VAL(x)           (x << 4)     // Range 0 ~ 63
#define DRV_VOL_GAIN(x)          (x << 3)     // 0: gain x1. 1: gain x2.
#define DRV_VOL_CHANGE(x)        (x)          // 0: Immediate Change. 1: Reserve.

//--  REG15: REG_OP_CTRL  --------------------
#define OP_CTRL_EN(x)            (x << 9)     // 0: DISABLE. 1:ENABLE.
#define OP_CTRL_HOLD_EN(x)       (x << 8)     // 0: RELEASE. 1:HOLD.
#define OP_CTRL_EXT_EN(x)        (x << 7)     // 0: DISABLE. 1:ENABLE.
#define OP_CTRL_DIR(x)           (x << 6)     // 0: FORWARD. 1:BACKWARD.
#define OP_CTRL_CONT_OP(x)       (x << 4)     // 
#define OP_CTRL_VD_STOP(x)       (x)          // 0: INVALID. 1:OPERATE STOP.



/*****************************************************
   FOR CHANNEL 5,6,7( REG_CH567 )
*****************************************************/
//--  REG00: REG_FLL_DRV_CTRL  ---------------

//--  REG01: REG_FLL_SPEED  ------------------

//--  REG02: REG_FLL_DRV_KP  -----------------

//--  REG03: REG_FLL_DRV_KI  -----------------

//--  REG04: REG_FLL_PULSE_SETUP  ------------

//--  REG05: REG_FLL_DUTY_TIME  --------------

//--  REG06: REG_FLL_BRAKE  ------------------

//--  REG07: REG_FLL_MOTION_SERIAL_CTRL  -----

//--  REG08: REG_CH5_DC_DRV_CTRL  ------------

//--  REG09: REG_CH5_DC_DRV_CURRENT  ---------

//--  REG10: REG_CH5_DC_PWM_SETUP  -----------

//--  REG11: REG_CH6_DC_DRV_CTRL  ------------

//--  REG12: REG_CH6_DC_DRV_CURRENT  ---------

//--  REG13: REG_CH7_DC_DRV_CTRL  ------------

//--  REG14: REG_TEST_MODE  ------------------

//--  REG15: REG_DC_OP_CTRL  -----------------

/*****************************************************
   FOR COMMON REG( REG_COMMON )
*****************************************************/
/*REG00: REGC_ACTUATOR_SEL */
//--  REG00: REGC_ACTUATOR_SEL  --------------
#define CH5_FS_RSP_TIME(x)       (x << 9)     // 0: RSP.TIME1 1:RSP.TIME2
#define CH6_FS_RSP_TIME(x)       (x << 8)     // 0: RSP.TIME1 1:RSP.TIME2
#define CH5_FLL_CMP_SEL(x)       (x << 6) 
#define OSCIN_CLK_FREQ(x)        (x << 4) 
#define IN4_TERMINAL_SETUP(x)    (x << 3)     // 
#define CH1234_CARRIES_FREQ(x)   (x << 1)     // 
#define CH34_ACTUATOR_SEL(x)     (x)          // 

//--  REG01: REGC_BF1_TERMINAL_SETUP  --------
#define BF1_CTRL(x)              (x << 8)     // 0: RSP.TIME1 1:RSP.TIME2
#define PI3_TERM_VD_SETUP(x)     (x << 6)     // 
#define PI2_TERM_VD_SETUP(x)     (x << 5)     // 
#define CH3_CH6_TERM_CTRL_SETUP(x) (x)

//--  REG02: REGC_FLL_CMP1_SETUP  ------------
//--  REG03: REGC_FLL_CMP2_SETUP  ------------
#define CMP_PD_R_SEL(x)          (x << 8)     // 0: RSP.TIME1 1:RSP.TIME2
#define CMP_THRES_VH(x)          (x << 4)     // 
#define CMP_THRES_VL(x)          (x << 0)     // 

//--  REG04: REGC_PI_PS_SETUP  ---------------
#define DRV_PS_SAFE(x)           (x << 9)     // 0: POWER SAFE ON.   1: POWER SAFE OFF.
#define DRV_PS12_SAFE(x)         (x << 8)     // 0: CH1,CH2 PS ON.   1: CH1,CH2  PS OFF.
#define DRV_PS34_SAFE(x)         (x << 6)     // 0: CH3,CH4 PS ON.   1: CH3,CH4  PS OFF.
#define DRV_PS5_SAFE(x)          (x << 5)     // 0: CH5 PS ON.       1: CH5 PS OFF.
#define DRV_PS6_SAFE(x)          (x << 4)     // 0: CH6 PS ON.       1: CH6 PS OFF.

#define DRV_PS_STATE(x)          ((x == PS_CH34)?(3 << x):(1 << x))


#define PS_CH1234_STATE          (DRV_PS_STATE(PS_CH12)|DRV_PS_STATE(PS_CH34))
#define PS_ALL_STATE             (DRV_PS_STATE(PS_CH12)|DRV_PS_STATE(PS_CH34)|DRV_PS_STATE(PS_CH5)|DRV_PS_STATE(PS_CH6))

#define DRV_PI3_CTRL(x)          (x << 2)     //
#define DRV_PI2_CTRL(x)          (x << 1)     // 0: PI DRIVER OFF.   1: PI DRIVER ON
#define DRV_PI1_CTRL(x)          (x)          // 0: PI DRIVER OFF.   1: PI DRIVER ON

//--  REG05: REGC_OUTPUT_SETUP  --------------
#define DRV_EXT_OUTPUT_SEL(x)    (x << 8)     // 0: DISABLE. 1:ENABLE.
#define DRV_MOB1_OUTPUT_SEL(x)   (x << 6)     // 0: RELEASE. 1:HOLD.
#define DRV_MOB2_OUTPUT_SEL(x)   (x << 4)     // 0: RELEASE. 1:HOLD.
#define DRV_EXT1_SEL(x)          (x << 2)     // 0: DISABLE. 1:ENABLE.
#define DRV_EXT2_SEL(x)          (x)          // 0: DISABLE. 1:ENABLE.


//--  REG06: REGC_SW_RST  --------------------
#define DRV_RST_CH12(x)          (x << 9)     // 0: 
#define DRV_RST_CH34(x)          (x << 8) 
#define DRV_RST_CH5(x)           (x << 7) 
#define DRV_STOP_CH34(x)         (x << 1)
#define DRV_STOP_CH12(x)         (x)

//--  REG07: REGC_CH3_DC_DRV_CTRL  -----------
//--  REG09: REGC_CH4_DC_DRV_CTRL  -----------
#define DRV_DC_MODE(x)           (x << 8)
#define DRV_DC_DIR(x)            (x << 4)
#define DRV_DC_OP_MODE(x)        (x)

//--  REG08: REGC_CH3_DC_VOL_SETUP  ----------
//--  REG10: REGC_CH4_DC_VOL_SETUP  ----------
#define DRV_DC_VOL(x)            ((x & 0x3F) << 4)
#define DRV_DC_GAIN(x)           (x << 3)

//--  REG11: REGC_CH3_CH4_OP_CTRL  -----------
#define DRV_CH4_DIR(x)           (x << 5)     // 0: FORWARD. 1:BACKWARD
#define DRV_CH4_OP(x)            (x << 4)     // 0: DISABLE. 1:ENABLE.
#define DRV_CH3_DIR(x)           (x << 1)     // 0: FORWARD. 1:BACKWARD
#define DRV_CH3_OP(x)            (x)          // 0: DISABLE. 1:ENABLE.

//--  REG12: REGC_CH12_STATUS_FLAG  ----------
//--  REG13: REGC_CH34_STATUS_FLAG  ----------
#define STATUS_OFF_MODE(x)       (x << 9)     // 0: NONE.    1:Output at turning point.
#define STATUS_PRE_PULS_GEN(x)   (x << 8)     // 0: NONE.    1:Output at pre-pulse Generation excitation mode.
#define STATUS_ACC_CONST_MODE(x) (x << 7)     // 0: NONE.    1:Output at Acc/Constant mode
#define STATUS_DEC_MODE(x)       (x << 6)     // 0: NONE.    1:Output at Dec mode
#define STATUS_POST_PULS_GEN(x)  (x << 5)     // 0: NONE.    1:Output at post-pulse Generation excitation mode
#define STATUS_EXT_MODE(x)       (x << 4)     // 0: NONE.    1:Output at excitation mode

//--  REG14: REGC_STM12_STATUS_FLAG  ---------
#define STATUS_OUTPUT_SEL(x)     (x << 9)
#define STATUS_INFO_SEL(x)       (x)

//--  REG15: REGC_STM12_OP_CTRL2  ------------
#define DRV_CH12_OP_EN(x)        (x << 9)     // 0: DISABLE. 1:ENABLE.
#define DRV_CH34_OP_EN(x)        (x << 8)     // 0: DISABLE. 1:ENABLE.
#define DRV_CH12_HOLD_EN(x)      (x << 7)     // 0: RELEASE. 1:HOLD.
#define DRV_CH34_HOLD_EN(x)      (x << 6)     // 0: RELEASE. 1:HOLD.
#define DRV_CH12_EXT_EN(x)       (x << 5)     // 0: DISABLE. 1:ENABLE.
#define DRV_CH34_EXT_EN(x)       (x << 4)     // 0: DISABLE. 1:ENABLE.
#define DRV_CH12_VD_OP_STOP(x)   (x << 3)     // 0: DISABLE. 1:ENABLE.
#define DRV_CH34_VD_OP_STOP(x)   (x << 2)     // 0: DISABLE. 1:ENABLE.
                                              
#define DRV_CH12_CALIBRAT(x)     (x << 1)     // 0: DISABLE. 1:ENABLE.
#define DRV_CH34_CALIBRAT(x)     (x)          // 0: DISABLE. 1:ENABLE.



//******************************************************************************
//
//                             STRUECTURE
//
//******************************************************************************
typedef enum _MOTOR_OP_CTRL {
    OP_DISABLE = 0 ,
    OP_ENABLE
}MOTOR_OP_CTRL;

typedef enum _MOTOR_DRV_DIR {
    DRV_FORWARD = 0 ,
    DRV_BACKWARD
}MOTOR_DRV_DIR;

/*****************************************************
   FOR CHANNEL 1,2( REG_CH12 )
*****************************************************/
//*********************************************************
// FOR CHANNEL 3,4.
//*********************************************************

//--  REG00: REG_DRV_CTRL  -------------------
typedef enum _MOTOR_DRV_MODE {  // for DRV_CTRL_MODE.
    DRV_MICRO_STEP_256STEP = 0 ,
    DRV_1_2PHASE_100,
    DRV_1_2PHASE_70,
    DRV_2_2PHASE,
    DRV_MICRO_STEP_512STEP,
    DRV_MICRO_STEP_1024STEP

}MOTOR_DRV_MODE;

typedef enum _MOTOR_DRV_SPEED_TYPE {  // for DRV_CTRL_SPEED_TYPE.
    DRV_CTRL_NO_ACC_DEC = 0 ,
    DRV_CTRL_DEC,
    DRV_CTRL_ACC,
    DRV_CTRL_ACC_DEC
}MOTOR_DRV_SPEED_TYPE;

typedef enum _MOTOR_DRV_INIT_POS {  // for SET_INIT_POS_EXCITE.
    DRV_P100_P100 = 0 ,
    DRV_0_P100,
    DRV_N100_P100,
    DRV_N100_0,
    DRV_N100_N100,
    DRV_0_N100,
    DRV_P100_N100,
    DRV_P100_0
}MOTOR_DRV_INIT_POS;

//--  REG01: REG_N_PULSE1  -------------------

//--  REG02: REG_N_PULSE2  -------------------

//--  REG03: REG_PULSE_RATE0  ----------------

//--  REG04: REG_nPULSE_RANGE  ---------------
typedef enum _MOTOR_DRV_PULSE_RATE_RANGE {  // for PULSE_RATE_RANGE.
    PULSE_RATE_RANGE_2048 = 0 ,
    PULSE_RATE_RANGE_1024,
    PULSE_RATE_RANGE_512 ,
    PULSE_RATE_RANGE_256 ,
    PULSE_RATE_RANGE_128 ,
    PULSE_RATE_RANGE_64  ,
    PULSE_RATE_RANGE_32  ,
    PULSE_RATE_RANGE_16  ,
    PULSE_RATE_RANGE_8   ,
    PULSE_RATE_RANGE_4   ,
    PULSE_RATE_RANGE_2
}MOTOR_DRV_PULSE_RATE_RANGE;

// FOR MICRO STEP ONLY
typedef enum _MOTOR_DRV_STOP_POS {  // for SET_STOP_POS.
    DRV_STOP_INVALID = 0 ,
    DRV_STOP_1_2PHASE,
    DRV_STOP_2_2PHASE ,
    DRV_STOP_SETTING_INVALID 
}MOTOR_DRV_STOP_POS;

//--  REG05: REG_nPULSE_ACC_DEC  -------------

//--  REG06: REG_PULSE_RATE1  ----------------
//--  REG07: REG_PULSE_RATE2  ----------------
//--  REG08: REG_PULSE_RATE3  ----------------
//--  REG09: REG_PULSE_RATE4  ----------------


//--  REG10: REG_PRE_PULSE_EXT  --------------

//--  REG11: REG_POST_PULSE_EXT  -------------

//--  REG12: REG_READ_PULSE_POS1  ------------

//--  REG13: REG_READ_PULSE_POS2  ------------

//--  REG14: REG_DRV_VOL_VAL  ----------------
typedef enum _MOTOR_DRV_VOL {  // for DRV_VOL_VAL.
    DRV_VOL_504 = 0x000000 ,
    DRV_VOL_496,
    DRV_VOL_488,
    DRV_VOL_480,
    DRV_VOL_472,
    DRV_VOL_464,
    DRV_VOL_456,
    DRV_VOL_448,
    DRV_VOL_440,
    DRV_VOL_432,
    DRV_VOL_424,
    DRV_VOL_416,
    DRV_VOL_408,
    DRV_VOL_400,
    DRV_VOL_392,
    DRV_VOL_384,
    DRV_VOL_376,
    DRV_VOL_368,
    DRV_VOL_360,
    DRV_VOL_352,
    DRV_VOL_344,
    DRV_VOL_336,
    DRV_VOL_328,
    DRV_VOL_320,
    DRV_VOL_312,
    DRV_VOL_304,
    DRV_VOL_296,
    DRV_VOL_288,
    DRV_VOL_280,
    DRV_VOL_272,
    DRV_VOL_264,
    DRV_VOL_256,
    DRV_VOL_248,
    DRV_VOL_240,
    DRV_VOL_232,
    DRV_VOL_224,
    DRV_VOL_216,
    DRV_VOL_208,
    DRV_VOL_200,
    DRV_VOL_192,
    DRV_VOL_184,
    DRV_VOL_176,
    DRV_VOL_168,
    DRV_VOL_160,
    DRV_VOL_152,
    DRV_VOL_144,
    DRV_VOL_136,
    DRV_VOL_128,
    DRV_VOL_120,
    DRV_VOL_112,
    DRV_VOL_104,
    DRV_VOL_096,
    DRV_VOL_088,
    DRV_VOL_080,
    DRV_VOL_072,
    DRV_VOL_064,
    DRV_VOL_056,
    DRV_VOL_048,
    DRV_VOL_040,
    DRV_VOL_032,
    DRV_VOL_024,
    DRV_VOL_016,
    DRV_VOL_008,
    DRV_VOL_000
}MOTOR_DRV_VOL;

typedef enum _MOTOR_DRV_GAIN {  // for DRV_VOL_GAIN.
    DRV_GAIN_ONE = 0,
    DRV_GAIN_HALF ,
    DRV_GAIN_TWICE 
}MOTOR_DRV_GAIN;

typedef enum _MOTOR_DRV_VOL_CHANGE { // for DRV_VOL_CHANGE.
    VOL_CHANGE_IMMEDIATE = 0,
    VOL_CHANGE_RESERVE
}MOTOR_DRV_VOL_CHANGE;

//--  REG15: REG_OP_CTRL  --------------------
typedef enum _MOTOR_DRV_OP_HOLD {  // for OP_CTRL_HOLD_EN.
    OP_RELEASE = 0,                       // Excitation off
    OP_HOLD                               // Excitation on, but pulse transition stop.
}MOTOR_DRV_OP_HOLD;

typedef enum _MOTOR_DRV_OP_CONT {  // for OP_CTRL_CONT_OP.
    CONT_OP_DISABLE = 0,
    CONT_OP_1_ENABLE,
    CONT_OP_2_ENABLE   
}MOTOR_DRV_OP_CONT;

typedef enum _MOTOR_DRV_OP_STOP {  // for OP_CTRL_VD_STOP.
    VD_INVALID = 0,                       // Operation invalid
    VD_STOP                               // Operation Stop
}MOTOR_DRV_OP_STOP;


/*****************************************************
   FOR CHANNEL 5,6,7( REG_CH567 )
*****************************************************/
//--  REG00: REG_FLL_DRV_CTRL  ---------------

//--  REG01: REG_FLL_SPEED  ------------------

//--  REG02: REG_FLL_DRV_KP  -----------------

//--  REG03: REG_FLL_DRV_KI  -----------------

//--  REG04: REG_FLL_PULSE_SETUP  ------------

//--  REG05: REG_FLL_DUTY_TIME  --------------

//--  REG06: REG_FLL_BRAKE  ------------------

//--  REG07: REG_FLL_MOTION_SERIAL_CTRL  -----

//--  REG08: REG_CH5_DC_DRV_CTRL  ------------

//--  REG09: REG_CH5_DC_DRV_CURRENT  ---------

//--  REG10: REG_CH5_DC_PWM_SETUP  -----------

//--  REG11: REG_CH6_DC_DRV_CTRL  ------------

//--  REG12: REG_CH6_DC_DRV_CURRENT  ---------

//--  REG13: REG_CH7_DC_DRV_CTRL  ------------

//--  REG14: REG_TEST_MODE  ------------------

//--  REG15: REG_DC_OP_CTRL  -----------------


//*********************************************************
// FOR COMMON REG
//*********************************************************
//---------------------------------------------------------
// REG00: REGC_ACTUATOR_SEL
//---------------------------------------------------------
typedef enum _MOTOR_FS_RSP {  // for CH5_FS_RSP_TIME, CH6_FS_RSP_TIME.
    DRV_RSP_TIME1 = 0 ,
    DRV_RSP_TIME2
}MOTOR_FS_RSP;

typedef enum _MOTOR_CH5_FLL_SETUP {  // for CH5_FLL_CMP_SEL.
    FLL_INVALID = 0 ,
    VALID_USE_COMP2 ,
    VALID_USE_COMP1
}MOTOR_CH5_FLL_SETUP;

typedef enum _MOTOR_OSCIN_CLK_FREQ {  // for OSCIN_CLK_FREQ.
    FREQ_1M_6_2M = 0 ,
    FREQ_12M     = 2 ,
    FREQ_27M     = 3 
}MOTOR_OSCIN_CLK_FREQ;

typedef enum _MOTOR_IN4_TERM_SETUP {  // for IN4_TERMINAL_SETUP.
    IN4_CTRL_INPUT = 0 ,
    COMP2_OUTPUT
}MOTOR_IN4_TERM_SETUP;

typedef enum _MOTOR_CARRIER_FREQ_SETUP {  // for CH1234_CARRIES_FREQ.
    FREQ_230K = 0 ,
    FREQ_400K
}MOTOR_CARRIER_FREQ_SETUP;

typedef enum _MOTOR_CH34_ACTUATOR_SETUP {  // for CH34_ACTUATOR_SEL.
    USE_STM2 = 0 ,
    USE_DC_COIL
}MOTOR_CH34_ACTUATOR_SETUP;

//---------------------------------------------------------
// REG01: REGC_BF1_TERMINAL_SETUP
//---------------------------------------------------------
typedef enum _MOTOR_SCHMITT_BUF_SETUP {  // for BF1_CTRL.
    SCHMITT_INVALID = 0 ,
    VALID_PD_33K_R,
    VALID_INPUT_OPEN
}MOTOR_SCHMITT_BUF_SETUP;

typedef enum _MOTOR_PI3_VD_SETUP {  // for PI3_TERM_VD_SETUP.
    PI3_INVALID = 0 ,
    VD1_VD2_RT_CTRL,
    VD1_CTRL
}MOTOR_PI3_VD_SETUP;

typedef enum _MOTOR_PI2_VD_SETUP {  // for PI2_TERM_VD_SETUP.
    PI2_INVALID = 0 ,
    VD2_CTRL
}MOTOR_PI2_VD_SETUP;

//---------------------------------------------------------
// REG04: REGC_PI_PS_SETUP
//---------------------------------------------------------
typedef enum _MOTOR_DRV_PS_STATE {  // for DRV_PS_SAFE, DRV_PS12_SAFE, DRV_PS5_SAFE, DRV_PS6_SAFE
    DRV_PS_ON = 0,
    DRV_PS_OFF
}MOTOR_DRV_PS_STATE;

// for PS34
typedef enum _MOTOR_DRV_PS34_STATE {  // for DRV_PS34_SAFE
    DRV_PS34_ON = 0,
    DRV_PS34_OFF = 3
}MOTOR_DRV_PS34_STATE;

// for PI1, PI2
typedef enum _MOTOR_DRV_PI_CTRL{  // for DRV_PI1_CTRL, DRV_PI2_CTRL
    DRV_PI_OFF = 0,
    DRV_PI_ON
}MOTOR_DRV_PI_CTRL;

// for PI3
typedef enum _MOTOR_DRV_PI3_CTRL{  // for DRV_PI3_CTRL
    DRV_PI3_OFF = 0,
    DRV_PI3_ON,
    DRV_BF1_OUT
}MOTOR_DRV_PI3_CTRL;


//---------------------------------------------------------
// REG05: REGC_OUTPUT_SETUP
//---------------------------------------------------------
typedef enum _MOTOR_EXT_DATA_SEL {  // for DRV_EXT_OUTPUT_SEL.
    DRV_H_IN_EXCITE = 0 ,
    DRV_H_IN_PULSE_TRANS
}MOTOR_EXT_DATA_SEL;

typedef enum _MOTOR_MOB1_OUTPUT_SEL {  // for DRV_MOB1_OUTPUT_SEL.
    DRV_MOB1_MOB12 = 0 ,
    DRV_MOB1_MOB34,
    DRV_MOB1_SDO_NORMAL,
    DRV_MOB1_SDO
}MOTOR_MOB1_OUTPUT_SEL;

typedef enum _MOTOR_MOB2_OUTPUT_SEL {  // for DRV_MOB2_OUTPUT_SEL.
    DRV_MOB2_MOB34 = 0 ,
    DRV_MOB2_CPOUT1
}MOTOR_MOB2_OUTPUT_SEL;

typedef enum _MOTOR_EXT1_OUTPUT_SEL {  // for DRV_EXT1_SEL.
    DRV_EXT1_EXT12 = 0 ,
    DRV_EXT1_EXT34   ,
    DRV_EXT1_ST12    ,
    DRV_EXT1_ST34    
}MOTOR_EXT1_OUTPUT_SEL;

typedef enum _MOTOR_EXT2_OUTPUT_SEL {  // for DRV_EXT2_SEL.
    DRV_EXT2_EXT34 = 0 ,
    DRV_EXT2_CPOUT2  ,
    DRV_EXT2_ST34
}MOTOR_EXT2_OUTPUT_SEL;

//---------------------------------------------------------
// REG06: REGC_SW_RST
//---------------------------------------------------------
typedef enum _MOTOR_DRV_RST_OP {  // for DRV_RST_CH12, DRV_RST_CH34, DRV_RST_CH5
    RST_OP_NONE = 0 ,
    RST_OP_INITIALIZE
}MOTOR_DRV_RST_OP;

typedef enum _MOTOR_DRV_DEC_OP {  // for DRV_STOP_CH34, DRV_STOP_CH12.
    DEC_NONE = 0 ,
    DEC_2_STOP
}MOTOR_DRV_DEC_OP;

//---------------------------------------------------------
// REG07: REGC_CH3_DC_DRV_CTRL
// REG09: REGC_CH4_DC_DRV_CTRL
//---------------------------------------------------------
typedef enum _MOTOR_DRV_DC_DRV_MODE {  // for DRV_DC_MODE.
    ONE_LINE_CTRL_CV_IN_IN = 0 ,
    ONE_LINE_CTRL_CV_EN_IN ,
    SERIAL_CTRL_CV
}MOTOR_DRV_DC_DRV_MODE;

typedef enum _MOTOR_DRV_DC_OP_MODE {  // for DRV_DC_OP_MODE.
    DC_BRAKE = 0 ,
    DC_FORWARD ,
    DC_REVERSE ,
    DC_BRAKE_PLUS
}MOTOR_DRV_DC_OP_MODE;

//---------------------------------------------------------
// REG08: REGC_CH3_DC_VOL_SETUP
// REG10: REGC_CH4_DC_VOL_SETUP
//---------------------------------------------------------
typedef enum _MOTOR_DRV_VOL_GAIN {  // for DRV_DC_GAIN.
    GAIN_ONE = 0 ,
    GAIN_TWO
}MOTOR_DRV_VOL_GAIN;

//---------------------------------------------------------
// REG11: REGC_CH3_CH4_OP_CTRL
//---------------------------------------------------------

//---------------------------------------------------------
// REG12: REGC_CH12_STATUS_FLAG
// REG13: REGC_CH34_STATUS_FLAG
//---------------------------------------------------------
/**/ // for STATUS_OFF_MODE, STATUS_PRE_PULS_GEN, STATUS_ACC_CONST_MODE,
/**/ //     STATUS_DEC_MODE, STATUS_POST_PULS_GEN, STATUS_EXT_MODE.
typedef enum _MOTOR_STATUS_CTRL {
     FLAG_OUTPUT_NONE = 0,
     FLAG_OUTPUT
}MOTOR_STATUS_CTRL;

//---------------------------------------------------------
// REG14: REGC_STM12_STATUS_FLAG
//---------------------------------------------------------
typedef enum _MOTOR_STATUS_OUTPUT_SEL { // for STATUS_OUTPUT_SEL.
     OUTPUT_STM1 = 0,
     OUTPUT_STM2
}MOTOR_STATUS_OUTPUT_SEL;

typedef enum _MOTOR_STATUS_INFO_SEL {  // for STATUS_INFO_SEL.
    STATUS_OFF = 0     ,
    STATUS_PRE_EXCITE  ,
    STATUS_ACC_CONST   ,
    STATUS_DEC         ,
    STATUS_POST_EXCITE ,
    STATUS_EXCITE_EXCLUDE
}MOTOR_STATUS_INFO_SEL;

//---------------------------------------------------------
// REG15: REGC_STM12_OP_CTRL2
//---------------------------------------------------------

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
    DRV_POWER_CH12 = 0,
    DRV_POWER_CH34,
    DRV_POWER_CH5,
    DRV_POWER_CH6
}MOTOR_DRV_POWER_MODE;

typedef enum _MOTOR_DRV_PS_MODE {  // for DRV_PS_STATE.
    PS_CH6 = 4,
    PS_CH5 = 5,
    PS_CH34 = 6,
    PS_CH12 = 8,
    PS_EN_IC = 9
}MOTOR_DRV_PS_MODE;

void R2A30440NP_FocusEnablePR(MMP_BOOL OnOff);
void R2A30440NP_ZoomEnablePR(MMP_BOOL OnOff);
void R2A30440NP_MechanicalShutterDirection(MMP_BOOL bForwardReverse);
#endif  // _R2A30440NP_H_


