//------------------------------------------------------------------------------
//
//  File        : mmp_gpio_inc.h
//  Description : Header file of GPIO common information
//  Author      : Alterman
//  Revision    : 1.0
//
//------------------------------------------------------------------------------
#ifndef _MMP_GPIO_INC_H_
#define _MMP_GPIO_INC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_lib.h"

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

#define GPIO_LOW        (0)
#define GPIO_HIGH       (1)

//==============================================================================
//
//                              DATA TYPES
//
//==============================================================================

typedef void GpioCallBackFunc(void);

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

/*
 * [NOTE]
 * Please refer GPIO user/register guide to complete the following enum list.
 */
typedef enum _MMP_GPIO_PIN {
    MMP_GPIO0 = 0,
    MMP_GPIO1,
    MMP_GPIO2,
    MMP_GPIO3,
    MMP_GPIO4,
    MMP_GPIO5,
    MMP_GPIO6,
    MMP_GPIO7,
    MMP_GPIO8,
    MMP_GPIO9,
    MMP_GPIO10,
    MMP_GPIO11,
    MMP_GPIO12,
    MMP_GPIO13,
    MMP_GPIO14,
    MMP_GPIO15,
    MMP_GPIO16,
    MMP_GPIO17,
    MMP_GPIO18,
    MMP_GPIO19,
    MMP_GPIO20,
    MMP_GPIO21,
    MMP_GPIO22,
    MMP_GPIO23,
    MMP_GPIO24,
    MMP_GPIO25,
    MMP_GPIO26,
    MMP_GPIO27,
    MMP_GPIO28,
    MMP_GPIO29,
    MMP_GPIO30,
    MMP_GPIO31,
    MMP_GPIO32,
    MMP_GPIO33,
    MMP_GPIO34,
    MMP_GPIO35,
    MMP_GPIO36,
    MMP_GPIO37,
    MMP_GPIO38,
    MMP_GPIO39,
    MMP_GPIO40,
    MMP_GPIO41,
    MMP_GPIO42,
    MMP_GPIO43,
    MMP_GPIO44,
    MMP_GPIO45,
    MMP_GPIO46,
    MMP_GPIO47,
    MMP_GPIO48,
    MMP_GPIO49,
    MMP_GPIO50,
    MMP_GPIO51,
    MMP_GPIO52,
    MMP_GPIO53,
    MMP_GPIO54,
    MMP_GPIO55,
    MMP_GPIO56,
    MMP_GPIO57,
    MMP_GPIO58,
    MMP_GPIO59,
    MMP_GPIO60,
    MMP_GPIO61,
    MMP_GPIO62,
    MMP_GPIO63,
    MMP_GPIO64,
    MMP_GPIO65,
    MMP_GPIO66,
    MMP_GPIO67,
    MMP_GPIO68,
    MMP_GPIO69,
    MMP_GPIO70,
    MMP_GPIO71,
    MMP_GPIO72,
    MMP_GPIO73,
    MMP_GPIO74,
    MMP_GPIO75,
    MMP_GPIO76,
    MMP_GPIO77,
    MMP_GPIO78,
    MMP_GPIO79,
    MMP_GPIO80,
    MMP_GPIO81, // input only
    MMP_GPIO82, // input only
    MMP_GPIO83, // input only
    MMP_GPIO84, // input only
    MMP_GPIO85, // input only
    MMP_GPIO86, // input only
    MMP_GPIO87, // input only
    MMP_GPIO88, // input only
    MMP_GPIO89, // input only
    MMP_GPIO90, // input only
    MMP_GPIO91, // input only
    MMP_GPIO92, // input only
    MMP_GPIO93, // input only
    MMP_GPIO94, // input only
    MMP_GPIO95, // input only
    MMP_GPIO96, // input only
    MMP_GPIO97,
    MMP_GPIO98,
    MMP_GPIO99,
    MMP_GPIO100,
    MMP_GPIO101,
    MMP_GPIO102,
    MMP_GPIO103,
    MMP_GPIO104,
    MMP_GPIO105,
    MMP_GPIO106,
    MMP_GPIO107,
    MMP_GPIO108,
    MMP_GPIO109,
    MMP_GPIO110,
    MMP_GPIO111,
    MMP_GPIO112,
    MMP_GPIO113,
    MMP_GPIO114,
    MMP_GPIO115,
    MMP_GPIO116,
    MMP_GPIO117,
    MMP_GPIO118,
    MMP_GPIO119,
    MMP_GPIO120,
    MMP_GPIO121,
    MMP_GPIO122,
    MMP_GPIO123,
    MMP_GPIO124,
    MMP_GPIO125,
    MMP_GPIO126,
    MMP_GPIO127,
    MMP_GPIO_NUM,
    MMP_GPIO_MAX = 0xFFF
} MMP_GPIO_PIN;

/*
 * GPIO interrupt enable.
 */
typedef enum _MMP_GPIO_TRIG {
	GPIO_L2H_EDGE_TRIG  = 0,    ///< Low to high
    GPIO_H2L_EDGE_TRIG  = 1,    ///< High to low
    GPIO_H_LEVEL_TRIG   = 2,    ///< High level(MV5 Not support)
    GPIO_L_LEVEL_TRIG   = 3,    ///< Low level(MV5 Not support)
    GPIO_TRIG_INVALID
} MMP_GPIO_TRIG;

/*
 * GPIO output mode
 */
typedef enum _MMP_GPIO_MODE {
	GPIO_MODE_INPUT   = 0,
    GPIO_MODE_OUTPUT  = 1
} MMP_GPIO_MODE;

/*
 * Pad pin define
 */
typedef enum _MMP_PAD_PIN {
    MMP_PAD_PSTM_B0      = 0x5100,
    MMP_PAD_PSTM_B1      = 0x5101,
    MMP_PAD_PSTM_B2      = 0x5102,
    MMP_PAD_PSTM_B3      = 0x5103,
    MMP_PAD_PSTM_B4      = 0x5104,
    MMP_PAD_PSTM_B5      = 0x5105,
    MMP_PAD_PSTM_B6      = 0x5106,
    MMP_PAD_PSTM_B7      = 0x5107,
    MMP_PAD_PSTM_B8      = 0x5108,
    MMP_PAD_PSTM_B9      = 0x5109,
    MMP_PAD_PSTM_B10     = 0x510A,
    MMP_PAD_PSTM_B11     = 0x510B,
    MMP_PAD_PSTM_B12     = 0x510C,
    MMP_PAD_PSTM_B13     = 0x510D,
    MMP_PAD_PSTM_B14     = 0x510E,
    MMP_PAD_PSTM_B15     = 0x510F,
    MMP_PAD_PSTM_B16     = 0x5110,
    MMP_PAD_PSTM_B17     = 0x5111,
    MMP_PAD_PSTM_B18     = 0x5112,
    MMP_PAD_PSTM_B19     = 0x5113,
    MMP_PAD_PSTM_B20     = 0x5114,
    MMP_PAD_PSTM_B21     = 0x5115,
    MMP_PAD_PSTM_B22     = 0x5116,
    MMP_PAD_PSTM_B23     = 0x5117,
    MMP_PAD_PSTM_B24     = 0x5118,
    MMP_PAD_PSTM_B25     = 0x5119,
    MMP_PAD_PSTM_B26     = 0x511A,
    MMP_PAD_PSTM_B27     = 0x511B,
    MMP_PAD_PSTM_B28     = 0x511C,
    MMP_PAD_PSTM_B29     = 0x511D,
    MMP_PAD_PSTM_B30     = 0x511E,
    MMP_PAD_PSTM_B31     = 0x511F,
    
    MMP_PAD_PSTM_T0      = 0x5120,
    MMP_PAD_PSTM_T1      = 0x5121,
    MMP_PAD_PSTM_T2      = 0x5122,
    MMP_PAD_PSTM_T3      = 0x5123,
    MMP_PAD_PSTM_T4      = 0x5124,
    MMP_PAD_PSTM_T5      = 0x5125,
    MMP_PAD_PSTM_T6      = 0x5126,
    MMP_PAD_PSTM_T7      = 0x5127,
    MMP_PAD_PSTM_T8      = 0x5128,
    MMP_PAD_PSTM_T9      = 0x5129,
    MMP_PAD_PSTM_T10     = 0x512A,
    MMP_PAD_PSTM_T11     = 0x512B,
    MMP_PAD_PSTM_T12     = 0x512C,
    MMP_PAD_PSTM_T13     = 0x512D,
    MMP_PAD_PSTM_T14     = 0x512E,
    MMP_PAD_PSTM_T15     = 0x512F,
    MMP_PAD_PSTM_T16     = 0x5130,
    MMP_PAD_PSTM_T17     = 0x5131,
    MMP_PAD_PSTM_T18     = 0x5132,
    MMP_PAD_PSTM_T19     = 0x5133,
    MMP_PAD_PSTM_T20     = 0x5134,
    MMP_PAD_PSTM_T21     = 0x5135,
    MMP_PAD_PSTM_T22     = 0x5136,
    MMP_PAD_PSTM_T23     = 0x5137,
    MMP_PAD_PSTM_T24     = 0x5138,
    MMP_PAD_PSTM_T25     = 0x5139,
    MMP_PAD_PSTM_T26     = 0x513A,
    MMP_PAD_PSTM_T27     = 0x513B,
    MMP_PAD_PSTM_T28     = 0x513C,
    MMP_PAD_PSTM_T29     = 0x513D,
    MMP_PAD_PSTM_T30     = 0x513E,
    MMP_PAD_PSTM_T31     = 0x513F,
    MMP_PAD_PSTM_T32     = 0x5140,
    MMP_PAD_PSTM_T33     = 0x5141,
    MMP_PAD_PSTM_T34     = 0x5142,
    MMP_PAD_PSTM_T35     = 0x5143,
    MMP_PAD_PSTM_T36     = 0x5144,
    MMP_PAD_PSTM_T37     = 0x5145,
    MMP_PAD_PSTM_T38     = 0x5146,
    MMP_PAD_PSTM_T39     = 0x5147,
    MMP_PAD_PSTM_T40     = 0x5148,
    MMP_PAD_PSTM_T41     = 0x5149,
    MMP_PAD_PSTM_T42     = 0x514A,
    MMP_PAD_PSTM_T43     = 0x514B,
    MMP_PAD_PSTM_T44     = 0x514C,
    MMP_PAD_PSTM_T45     = 0x514D,
    MMP_PAD_PSTM_T46     = 0x514E,
    MMP_PAD_PSTM_T47     = 0x514F,
    MMP_PAD_PSTM_T48     = 0x5150,
    MMP_PAD_PSTM_T49     = 0x5151,
    MMP_PAD_PSTM_T50     = 0x5152,
    MMP_PAD_PSTM_T51     = 0x5153,
    MMP_PAD_PSTM_T52     = 0x5154,
    MMP_PAD_PSTM_T53     = 0x5155,
    
    MMP_PAD_PBGPIO0      = 0x5160,
    MMP_PAD_PBGPIO1      = 0x5161,
    MMP_PAD_PBGPIO2      = 0x5162,
    MMP_PAD_PBGPIO3      = 0x5163,
    MMP_PAD_PBGPIO4      = 0x5164,
    MMP_PAD_PBGPIO5      = 0x5165,
    MMP_PAD_PBGPIO6      = 0x5166,
    MMP_PAD_PBGPIO7      = 0x5167,
    MMP_PAD_PBGPIO8      = 0x5168,
    MMP_PAD_PBGPIO9      = 0x5169,
    MMP_PAD_PBGPIO10     = 0x516A,
    MMP_PAD_PBGPIO11     = 0x516B,
    MMP_PAD_PBGPIO12     = 0x516C,
    MMP_PAD_PBGPIO13     = 0x516D,
    MMP_PAD_PBGPIO14     = 0x516E,
    MMP_PAD_PBGPIO15     = 0x516F,
    
    MMP_PAD_PBGPIO16     = 0x51C0,
    MMP_PAD_PBGPIO17     = 0x51C1,
    MMP_PAD_PBGPIO18     = 0x51C2,
    MMP_PAD_PBGPIO19     = 0x51C3,
    MMP_PAD_PBGPIO20     = 0x51C4,
    MMP_PAD_PBGPIO21     = 0x51C5,
    
    MMP_PAD_PCGPIO0      = 0x5170,
    MMP_PAD_PCGPIO1      = 0x5171,
    MMP_PAD_PCGPIO2      = 0x5172,
    MMP_PAD_PCGPIO3      = 0x5173,
    MMP_PAD_PCGPIO4      = 0x5174,
    MMP_PAD_PCGPIO5      = 0x5175,
    MMP_PAD_PCGPIO6      = 0x5176,
    MMP_PAD_PCGPIO7      = 0x5177,
    MMP_PAD_PCGPIO8      = 0x5178,
    MMP_PAD_PCGPIO9      = 0x5179,
    MMP_PAD_PCGPIO10     = 0x517A,
    MMP_PAD_PCGPIO11     = 0x517B,
    MMP_PAD_PCGPIO12     = 0x517C,
    MMP_PAD_PCGPIO13     = 0x517D,
    MMP_PAD_PCGPIO14     = 0x517E,
    MMP_PAD_PCGPIO15     = 0x517F,
    MMP_PAD_PCGPIO16     = 0x5180,
    MMP_PAD_PCGPIO17     = 0x5181,
    MMP_PAD_PCGPIO18     = 0x5182,
    MMP_PAD_PCGPIO19     = 0x5183,
    MMP_PAD_PCGPIO20     = 0x5184,
    MMP_PAD_PCGPIO21     = 0x5185,
    MMP_PAD_PCGPIO22     = 0x5186,
    MMP_PAD_PCGPIO23     = 0x5187,
    MMP_PAD_PCGPIO24     = 0x5188,
    MMP_PAD_PCGPIO25     = 0x5189,
    MMP_PAD_PCGPIO26     = 0x518A,
    MMP_PAD_PCGPIO27     = 0x518B,
    MMP_PAD_PCGPIO28     = 0x518C,
    MMP_PAD_PCGPIO29     = 0x518D,
    MMP_PAD_PCGPIO30     = 0x518E,
    MMP_PAD_PCGPIO31     = 0x518F,
    
    MMP_PAD_PAGPIO0      = 0x5190,
    MMP_PAD_PAGPIO1      = 0x5191,
    MMP_PAD_PAGPIO2      = 0x5192,
    MMP_PAD_PAGPIO3      = 0x5193,
    MMP_PAD_PAGPIO4      = 0x5194,
    MMP_PAD_PAGPIO5      = 0x5195,
    MMP_PAD_PAGPIO6      = 0x5196,
    MMP_PAD_PAGPIO7      = 0x5197,
    
    MMP_PAD_PHI2C_SCL    = 0x5198,
    MMP_PAD_PHI2C_SDA    = 0x5199,
    MMP_PAD_PI2S_SDO     = 0x519A,
    MMP_PAD_PI2S_SCK     = 0x519B,
    MMP_PAD_PI2S_WS      = 0x519C,
    MMP_PAD_PI2S_SDI     = 0x519D,
    MMP_PAD_PI2S_MCLK    = 0x519E,
    MMP_PAD_PSNR_MCLK    = 0x51A0,
    MMP_PAD_PSNR_RST_N   = 0x51A1,
    MMP_PAD_PSNR_VSYNC   = 0x51A2,
    MMP_PAD_PSNR_HSYNC   = 0x51A3,
    MMP_PAD_PSNR_PCLK    = 0x51A4,
    MMP_PAD_PSNR_D15_6   = 0x51A5,
    MMP_PAD_PSNR_SCK     = 0x51A6,
    MMP_PAD_PSNR_SDA     = 0x51A7,
    MMP_PAD_PSNR_SEN     = 0x51A8,
    MMP_PAD_PSNR_D5_0    = 0x51A9,
    MMP_PAD_PSNR_RST_N_1 = 0x51AA,
    MMP_PAD_PSNR_MCLK_1  = 0x51AB,
    MMP_PAD_PSNR_SEN_1   = 0x51AC,
    
    MMP_PAD_PDGPIO0      = 0x51B0,
    MMP_PAD_PDGPIO1      = 0x51B1,
    MMP_PAD_PDGPIO2      = 0x51B2,
    MMP_PAD_PDGPIO3      = 0x51B3,
    MMP_PAD_PDGPIO4      = 0x51B4,
    MMP_PAD_PDGPIO5      = 0x51B5,
    
    MMP_PAD_PMCLK        = 0x51B8,
    MMP_PAD_PVER_ID0     = 0x51BA,
    MMP_PAD_PVER_ID1     = 0x51BB,
    MMP_PAD_PVER_ID2     = 0x51BC,
    MMP_PAD_PVER_ID3     = 0x51BD,
    MMP_PAD_PVER_ID4     = 0x51BE,
    MMP_PAD_PLCD_D15_0   = 0x51D0,
    MMP_PAD_PLCD_WE      = 0x51D1,
    MMP_PAD_PLCD_A0      = 0x51D2,
    MMP_PAD_PLCD_RD      = 0x51D3,
    MMP_PAD_PLCD_CS1     = 0x51D4,
    MMP_PAD_PLCD_CS2     = 0x51D5,
    MMP_PAD_PLCD_FLM     = 0x51D6,
    MMP_PAD_PLCD_GPIO    = 0x51D7,
    MMP_PAD_PHDMI_SCL    = 0x51D8,
    MMP_PAD_PHDMI_SDA    = 0x51D9,
    MMP_PAD_MAX          = 0xFFFF
} MMP_PAD_PIN;

#endif // _MMP_GPIO_INC_H_

