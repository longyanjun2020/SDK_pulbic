#ifndef __DA7211_H__
#define __DA7211_H__

/*
 * - Author : 	aitdark.park@samsung.com
 * - Date: 		2010.04.26
 *
 * - History : 	2010.04.26 First version.
 */

#include "includes_fw.h"
#include "mmps_audio.h"

#define ALL_OFF		0
#define DAC_ON		1
#define ADC_ON		2
#define FM_ON		3



typedef struct _DA7211_SETTING
{
	MMP_USHORT digitVolume;
	MMP_UBYTE mOutput_Path;
}da7211_setting;

typedef enum
{
	DA7211_PAGE0,							// 0x00
	DA7211_CONTROL,							// 0x01
	DA7211_STATUS,							// 0x02
	DA7211_STARTUP1,						// 0x03
	DA7211_STARTUP2,						// 0x04
	DA7211_STARTUP3,						// 0x05
	DA7211_DUMMY_0x06,						// 0x06
	DA7211_MIC_L,							// 0x07
	DA7211_MIC_R,							// 0x08
	DA7211_AUX1_L,							// 0x09
	DA7211_AUX1_R,							// 0x0A
	DA7211_DUMMY_0x0B,						// 0x0B
	DA7211_IN_GAIN,							// 0x0C
	DA7211_INMIX_L,							// 0x0D
	DA7211_INMIX_R,							// 0x0E
	DA7211_ADC_HPF,							// 0x0F
	DA7211_ADC,								// 0x10
	DA7211_ADC_EQ1_2,						// 0x11
	DA7211_ADC_EQ3_4,						// 0x12
	DA7211_ADC_EQ5,							// 0x13
	DA7211_DAC_HPF,							// 0x14
	DA7211_DAC_L,							// 0x15
	DA7211_DAC_R,							// 0x16
	DA7211_DAC_SEL,							// 0x17
	DA7211_SOFT_MUTE,						// 0x18
	DA7211_DAC_EQ1_2,						// 0x19
	DA7211_DAC_EQ3_4,						// 0x1A
	DA7211_DAC_EQ5,							// 0x1B
	DA7211_OUTMIX_L,						// 0x1C
	DA7211_OUTMIX_R,						// 0x1D
	DA7211_OUT1_L,							// 0x1E
	DA7211_OUT1_R,							// 0x1F
	DA7211_DUMMY_0x20,						// 0x20
	DA7211_HP_L_VOL,						// 0x21
	DA7211_HP_R_VOL,						// 0x22
	DA7211_HP_CFG,							// 0x23
	DA7211_ZEROX,							// 0x24
	DA7211_DAI_SRC_SEL,						// 0x25
	DA7211_DAI_CFG1,						// 0x26
	DA7211_DAI_CFG2,						// 0x27
	DA7211_DAI_CFG3,						// 0x28
	DA7211_PLL_DIV1,						// 0x29
	DA7211_PLL_DIV2,						// 0x2A
	DA7211_PLL_DIV3,						// 0x2B
	DA7211_PLL,								// 0x2C
	DA7211_DUMMY_0x2D,						// 0x2D
	DA7211_DUMMY_0x2E,						// 0x2E
	DA7211_DUMMY_0x2F,						// 0x2F
	DA7211_DUMMY_0x30,						// 0x30
	DA7211_DUMMY_0x31,						// 0x31
	DA7211_DUMMY_0x32,						// 0x32
	DA7211_DUMMY_0x33,						// 0x33
	DA7211_DUMMY_0x34,						// 0x34
	DA7211_DUMMY_0x35,						// 0x35
	DA7211_DUMMY_0x36,						// 0x36
	DA7211_DUMMY_0x37,						// 0x37
	DA7211_DUMMY_0x38,						// 0x38
	DA7211_DUMMY_0x39,						// 0x39
	DA7211_DUMMY_0x3A,						// 0x3A
	DA7211_DUMMY_0x3B,						// 0x3B
	DA7211_DUMMY_0x3C,						// 0x3C
	DA7211_DUMMY_0x3D,						// 0x3D
	DA7211_DUMMY_0x3E,						// 0x3E
	DA7211_DUMMY_0x3F,						// 0x3F

	DA7211_DUMMY_0x40,						// 0x40
	DA7211_DUMMY_0x41,						// 0x41
	DA7211_DUMMY_0x42,						// 0x42
	DA7211_DUMMY_0x43,						// 0x43
	DA7211_DUMMY_0x44,						// 0x44
	DA7211_DUMMY_0x45,						// 0x45
	DA7211_DUMMY_0x46,						// 0x46
	DA7211_DUMMY_0x47,						// 0x47
	DA7211_DUMMY_0x48,						// 0x48
	DA7211_DUMMY_0x49,						// 0x49
	DA7211_DUMMY_0x4A,						// 0x4A
	DA7211_DUMMY_0x4B,						// 0x4B
	DA7211_DUMMY_0x4C,						// 0x4C
	DA7211_DUMMY_0x4D,						// 0x4D
	DA7211_DUMMY_0x4E,						// 0x4E
	DA7211_DUMMY_0x4F,						// 0x4F

	DA7211_DUMMY_0x50,						// 0x50
	DA7211_DUMMY_0x51,						// 0x51
	DA7211_DUMMY_0x52,						// 0x52
	DA7211_DUMMY_0x53,						// 0x53
	DA7211_DUMMY_0x54,						// 0x54
	DA7211_DUMMY_0x55,						// 0x55
	DA7211_DUMMY_0x56,						// 0x56
	DA7211_DUMMY_0x57,						// 0x57
	DA7211_DUMMY_0x58,						// 0x58
	DA7211_DUMMY_0x59,						// 0x59
	DA7211_DUMMY_0x5A,						// 0x5A
	DA7211_DUMMY_0x5B,						// 0x5B
	DA7211_DUMMY_0x5C,						// 0x5C
	DA7211_DUMMY_0x5D,						// 0x5D
	DA7211_DUMMY_0x5E,						// 0x5E
	DA7211_DUMMY_0x5F,						// 0x5F

	DA7211_DUMMY_0x60,						// 0x60
	DA7211_DUMMY_0x61,						// 0x61
	DA7211_DUMMY_0x62,						// 0x62
	DA7211_DUMMY_0x63,						// 0x63
	DA7211_DUMMY_0x64,						// 0x64
	DA7211_DUMMY_0x65,						// 0x65
	DA7211_DUMMY_0x66,						// 0x66
	DA7211_DUMMY_0x67,						// 0x67
	DA7211_DUMMY_0x68,						// 0x68
	DA7211_DUMMY_0x69,						// 0x69
	DA7211_DUMMY_0x6A,						// 0x6A
	DA7211_DUMMY_0x6B,						// 0x6B
	DA7211_DUMMY_0x6C,						// 0x6C
	DA7211_DUMMY_0x6D,						// 0x6D
	DA7211_DUMMY_0x6E,						// 0x6E
	DA7211_DUMMY_0x6F,						// 0x6F

	DA7211_DUMMY_0x70,						// 0x70
	DA7211_DUMMY_0x71,						// 0x71
	DA7211_DUMMY_0x72,						// 0x72
	DA7211_DUMMY_0x73,						// 0x73
	DA7211_DUMMY_0x74,						// 0x74
	DA7211_DUMMY_0x75,						// 0x75
	DA7211_DUMMY_0x76,						// 0x76
	DA7211_DUMMY_0x77,						// 0x77
	DA7211_DUMMY_0x78,						// 0x78
	DA7211_DUMMY_0x79,						// 0x79
	DA7211_DUMMY_0x7A,						// 0x7A
	DA7211_DUMMY_0x7B,						// 0x7B
	DA7211_DUMMY_0x7C,						// 0x7C
	DA7211_DUMMY_0x7D,						// 0x7D
	DA7211_DUMMY_0x7E,						// 0x7E
	
	DA7211_DSP_CFG,							// 0x7F
	DA7211_PAGE1,							// 0x80
	DA7211_CHIP_ID,							// 0x81
	DA7211_INTERFACE,						// 0x82
	DA7211_ALC_MAX,							// 0x83
	DA7211_ALC_MIN,							// 0x84
	DA7211_ALC_NOIS,						// 0x85
	DA7211_ALC_ATT,							// 0x86
	DA7211_ALC_REL,							// 0x87
	DA7211_ALC_DEL,							// 0x88
	DA7211_DUMMY_0x89,						// 0x89
	DA7211_A_HID_UNLOCK,					// 0x8A
	DA7211_A_TST_UNLOCK,					// 0x8B
	DA7211_DUMMY_0x8C,						// 0x8C
	DA7211_DUMMY_0x8D,						// 0x8D
	DA7211_DUMMY_0x8E,						// 0x8E
	DA7211_DUMMY_0x8F,						// 0x8F
	DA7211_A_PLL1,							// 0x90

	DA7211_DUMMY_0x91,						// 0x91
	DA7211_DUMMY_0x92,						// 0x92
	DA7211_DUMMY_0x93,						// 0x93
	DA7211_DUMMY_0x94,						// 0x94
	DA7211_DUMMY_0x95,						// 0x95
	DA7211_DUMMY_0x96,						// 0x96
	DA7211_DUMMY_0x97,						// 0x97
	DA7211_DUMMY_0x98,						// 0x98
	DA7211_DUMMY_0x99,						// 0x99
	DA7211_DUMMY_0x9A,						// 0x9A
	DA7211_DUMMY_0x9B,						// 0x9B
	DA7211_DUMMY_0x9C,						// 0x9C
	DA7211_DUMMY_0x9D,						// 0x9D
	DA7211_DUMMY_0x9E,						// 0x9E
	DA7211_DUMMY_0x9F,						// 0x9F

	DA7211_DUMMY_0xA0,						// 0xA0
	DA7211_DUMMY_0xA1,						// 0xA1
	
	DA7211_A_CP_CONFIG,						// 0xA2

	DA7211_DUMMY_0xA3,						// 0xA3
	DA7211_DUMMY_0xA4,						// 0xA4
	DA7211_DUMMY_0xA5,						// 0xA5
	DA7211_DUMMY_0xA6,						// 0xA6
	
	DA7211_A_CP_MODE,						// 0xA7

	DA7211_DUMMY_0xA8,						// 0xA8
	DA7211_DUMMY_0xA9,						// 0xA9
	DA7211_DUMMY_0xAA,						// 0xAA
	DA7211_DUMMY_0xAB,						// 0xAB
	DA7211_DUMMY_0xAC,						// 0xAC
	DA7211_DUMMY_0xAD,						// 0xAD
	DA7211_DUMMY_0xAE,						// 0xAE
	DA7211_DUMMY_0xAF,						// 0xAF
	
	DA7211_A_CP_LEVELMODE_LEV0,				// 0xB0
	DA7211_A_CP_LEVELMODE_LEV1,				// 0xB1
	DA7211_A_CP_LEVELMODE_LEV2,				// 0xB2

	DA7211_DUMMY_0xB3,						// 0xB3
	DA7211_DUMMY_0xB4,						// 0xB4
	DA7211_DUMMY_0xB5,						// 0xB5
	DA7211_DUMMY_0xB6,						// 0xB6
	
	DA7211_A_BGAP,							// 0xB7
	DA7211_REGS_MAX

} DA7211_REGS;

// DA7211_PAGE0 (0x00)
#define DA7211_REG_PAGE0					0x00	// R1 ~ R127
#define DA7211_REG_PAGE1					0x80	// R129 ~ R255

// DA7211_CONTROL (0x01)
#define DA7211_WRITEMODE_PAGE_WRITE			0x00	// 2-WIRE multiple write mode: page Write Mode
#define DA7211_WRITEMODE_REPEATED_WRITE		0X80	// 2-WIRE multiple write mode: repeated Write Mode
#define DA7211_WRITEMODE_MASK				0X80
#define DA7211_NOISE_SUP					0x08	// Enable noise suppression mode
#define DA7211_BIAS_DIS						0x00	// stop supplying current  (device power down)
#define DA7211_BIAS_EN						0x04	// supply bias current (device in operation)
#define DA7211_BIAS_MASK					0x04
#define DA7211_REG_DIS						0x00	// Internal regulator for the digital block disabled
#define DA7211_REG_EN						0x01	// Internal regulator for the digital block enabled
#define DA7211_REG_MASK						0x01

// DA7211_STATUS (0x02)
#define DA7211_MUTE_ON						0x08	// in Mute
#define DA7211_MUTE_OFF						0x00	// not muted
#define DA7211_MUTE_MASK					0x08
#define DA7211_MUTETYPE_SOFT				0x04	// soft mute
#define DA7211_MUTETYPE_NORMAL				0x00	// normal mute
#define DA7211_MUTETYPE_MASK				0x04

// DA7211_STARTUP1 (0x03)
#define DA7211_SC_CLK_DIS					0x80	// System Controller Disbale: clock is disabled
#define DA7211_SC_CLK_EN					0x00	// System Controller Disbale: clock is enabled
#define DA7211_SC_CLK_MASK					0x80
#define DA7211_SC_MST_LOW_PWR				0x00	// LOW POWER (EVERYTHING OFF)
#define DA7211_SC_MST_ACTIVE				0x01	// ACTIVE (ALL ENABLED SUBSYSTEMS ACTIVE)
#define DA7211_SC_MST_MASK					0x01

// DA7211_STARTUP2 (0x04)
#define DA7211_OUT1L_NORMAL					0x00
#define DA7211_OUT1L_STANDBY				0x01
#define DA7211_OUT1L_MASK					0x01
#define DA7211_OUT1R_NORMAL					0x00
#define DA7211_OUT1R_STANDBY				0x02
#define DA7211_OUT1R_MASK					0x02
#define DA7211_HP_L_NORMAL					0x00
#define DA7211_HP_L_STANDBY					0x08
#define DA7211_HP_L_MASK					0x08
#define DA7211_HP_R_NORMAL					0x00
#define DA7211_HP_R_STANDBY					0x10
#define DA7211_HP_R_MASK					0x10
#define DA7211_DAC_L_NORMAL					0x00
#define DA7211_DAC_L_STANDBY				0x20
#define DA7211_DAC_L_MASK					0x20
#define DA7211_DAC_R_NORMAL					0x00
#define DA7211_DAC_R_STANDBY				0x40
#define DA7211_DAC_R_MASK					0x40
#define DA7211_OUT1_NORMAL					(DA7211_OUT1L_NORMAL | DA7211_OUT1R_NORMAL)
#define DA7211_OUT1_STANDBY					(DA7211_OUT1L_STANDBY | DA7211_OUT1R_STANDBY)
#define DA7211_OUT1_MASK					(DA7211_OUT1L_MASK | DA7211_OUT1R_MASK)
#define DA7211_HP_NORMAL					(DA7211_HP_L_NORMAL | DA7211_HP_R_NORMAL)
#define DA7211_HP_STANDBY					(DA7211_HP_L_STANDBY | DA7211_HP_R_STANDBY)
#define DA7211_HP_MASK						(DA7211_HP_L_MASK | DA7211_HP_R_MASK)
#define DA7211_DAC_NORMAL					(DA7211_DAC_L_NORMAL | DA7211_DAC_R_NORMAL)
#define DA7211_DAC_STANDBY					(DA7211_DAC_L_STANDBY | DA7211_DAC_R_STANDBY)
#define DA7211_DAC_MASK						(DA7211_DAC_L_MASK | DA7211_DAC_R_MASK)

// DA7211_STARTUP3 (0x05)
#define DA7211_MIC_L_NORMAL					0x00
#define DA7211_MIC_L_STANDBY				0x01
#define DA7211_MIC_L_MASK					0x01
#define DA7211_MIC_R_NORMAL					0x00
#define DA7211_MIC_R_STANDBY				0x02
#define DA7211_MIC_R_MASK					0x02
#define DA7211_AUX1_L_NORMAL				0x00
#define DA7211_AUX1_L_STANDBY				0x04
#define DA7211_AUX1_L_MASK					0x04
#define DA7211_AUX1_R_NORMAL				0x00
#define DA7211_AUX1_R_STANDBY				0x08
#define DA7211_AUX1_R_MASK					0x08
#define DA7211_ADC_L_NORMAL					0x00
#define DA7211_ADC_L_STANDBY				0x20
#define DA7211_ADC_L_MASK					0x20
#define DA7211_ADC_R_NORMAL					0x00
#define DA7211_ADC_R_STANDBY				0x40
#define DA7211_ADC_R_MASK					0x40
#define DA7211_MIC_NORMAL					(DA7211_MIC_L_NORMAL | DA7211_MIC_R_NORMAL)
#define DA7211_MIC_STANDBY					(DA7211_MIC_L_STANDBY | DA7211_MIC_R_STANDBY)
#define DA7211_MIC_MASK						(DA7211_MIC_L_MASK | DA7211_MIC_R_MASK)
#define DA7211_AUX1_NORMAL					(DA7211_AUX1_L_NORMAL | DA7211_AUX1_R_NORMAL)
#define DA7211_AUX1_STANDBY					(DA7211_AUX1_L_STANDBY | DA7211_AUX1_R_STANDBY)
#define DA7211_AUX1_MASK					(DA7211_AUX1_L_MASK | DA7211_AUX1_R_MASK)
#define DA7211_ADC_NORMAL					(DA7211_ADC_L_NORMAL | DA7211_ADC_R_NORMAL)
#define DA7211_ADC_STANDBY					(DA7211_ADC_L_STANDBY | DA7211_ADC_R_STANDBY)
#define DA7211_ADC_MASK						(DA7211_ADC_L_MASK | DA7211_ADC_R_MASK)

// DA7211_MIC_L (0x07)
#define DA7211_MIC_L_AMP_EN					0x80	// MIC amplifier enable
#define DA7211_MIC_L_AMP_DIS				0x00
#define DA7211_MIC_L_AMP_MASK				0x80
#define DA7211_MIC_BIAS_EN					0x40	// MIC bias enable
#define DA7211_MIC_BIAS_DIS					0x00
#define DA7211_MIC_BIAS_MASK				0x40
#define DA7211_MIC_BIAS_SEL_1_5				0x00	// MIC bias voltage selection: 1.5V
#define DA7211_MIC_BIAS_SEL_1_6				0x10	// MIC bias voltage selection: 1.6V
#define DA7211_MIC_BIAS_SEL_2_2				0x20	// MIC bias voltage selection: 2.2V
#define DA7211_MIC_BIAS_SEL_2_3				0x30	// MIC bias voltage selection: 2.3V
#define DA7211_MIC_BIAS_SEL_MASK			0x30
#define DA7211_MIC_L_MUTE_ON				0x08	// Muted
#define DA7211_MIC_L_MUTE_OFF				0x00	// Unuted
#define DA7211_MIC_L_MUTE_MASK				0x08	// Muted
#define DA7211_MIC_L_VOL_MASK				0x07	// -6dB, 0dB, 6dB, 12dB

// DA7211_MIC_R (0x08)
#define DA7211_MIC_R_AMP_EN					0x80
#define DA7211_MIC_R_AMP_DIS				0x00
#define DA7211_MIC_R_AMP_MASK				0x80
#define DA7211_MIC_R_MUTE_ON				0x08	// Muted
#define DA7211_MIC_R_MUTE_OFF				0x00	// Unuted
#define DA7211_MIC_R_MUTE_MASK				0x08	// Muted
#define DA7211_MIC_R_VOL_MASK				0x07	// -6dB, 0dB, 6dB, 12dB

// DA7211_AUX1_L (0x09)
#define DA7211_AUX1_L_AMP_EN				0x80
#define DA7211_AUX1_L_AMP_DIS				0x00
#define DA7211_AUX1_L_AMP_MASK				0x80
#define DA7211_AUX1_L_VOL_MASK				0x3F	// (0x00 ~ 0x0F: Reserved) mute(0x10), -48dB(0x11), -46.5dB(0x12), ..., 21dB(0x3F)
#define DA7211_AUX1_L_GAIN_ZERO				0x10

// DA7211_AUX1_R (0x0A)
#define DA7211_AUX1_R_AMP_EN				0x80
#define DA7211_AUX1_R_AMP_DIS				0x00
#define DA7211_AUX1_R_AMP_MASK				0x80
#define DA7211_AUX1_R_VOL_MASK				0x3F	// (0x00 ~ 0x0F: Reserved) mute(0x10), -48dB(0x11), -46.5dB(0x12), ..., 21dB(0x3F)
#define DA7211_AUX1_R_GAIN_ZERO				0x10

// DA7211_IN_GAIN (0x0C)
#define DA7211_INPGA_L_VOL_MASK				0xF0	// -4.5B(0x00), -3dB(0x10), ..., 18dB(0xF0)
#define DA7211_INPGA_R_VOL_MASK				0x0F	// -4.5B(0x00), -3dB(0x01), ..., 18dB(0x0F)

// DA7211_INMIX_L (0x0D)
#define DA7211_IN_L_PGA_EN					0x80
#define DA7211_IN_L_PGA_DIS					0x00
#define DA7211_IN_L_PGA_MASK				0x80
#define DA7211_IN_L_OUTMIX_L				0x10	// Add OUTMIX_L  into Input Mixer L
#define DA7211_IN_L_A1_L					0x04	// Add AUX1_L into Input Mixer L
#define DA7211_IN_L_MIC_R					0x02	// Add MIC_R into Input Mixer L
#define DA7211_IN_L_MIC_L					0x01	// Add MIC_L into Input Mixer L
#define DA7211_IN_L_MASK					0x1F

// DA7211_INMIX_R (0x0E)
#define DA7211_IN_R_PGA_EN					0x80
#define DA7211_IN_R_PGA_DIS					0x00
#define DA7211_IN_R_PGA_MASK				0x80
#define DA7211_IN_R_IN_L					0x20	// Add INPGA_L  (stereo to mono)
#define DA7211_IN_R_OUTMIX_R				0x10	// Add OUTMIX_R  into Input Mixer R
#define DA7211_IN_R_A1_R					0x04	// Add AUX1_L into Input Mixer R
#define DA7211_IN_R_MIC_L					0x02	// Add MIC_L into Input Mixer L
#define DA7211_IN_R_MIC_R					0x01	// Add MIC_R into Input Mixer L
#define DA7211_IN_R_MASK					0x3F

// DA7211_ADC_HPF (0x0F)
#define DA7211_ADC_VOICE_EN					0x80	// ADC Voice Filter
#define DA7211_ADC_VOICE_DIS				0x00
#define DA7211_ADC_VOICE_MASK				0x80
#define DA7211_ADC_VOICE_F0_2_5HZ			0x00	// ADC Voice (8kHz) High pass 3dB cutoff at:
#define DA7211_ADC_VOICE_F0_25HZ			0x10
#define DA7211_ADC_VOICE_F0_50HZ			0x20
#define DA7211_ADC_VOICE_F0_100HZ			0x30
#define DA7211_ADC_VOICE_F0_150HZ			0x40
#define DA7211_ADC_VOICE_F0_200HZ			0x50
#define DA7211_ADC_VOICE_F0_300HZ			0x60
#define DA7211_ADC_VOICE_F0_400HZ			0x70
#define DA7211_ADC_VOICE_F0_MASK			0x70
#define DA7211_ADC_HPF_EN					0x08	// ADC High Pass Filter
#define DA7211_ADC_HPF_DIS					0x00
#define DA7211_ADC_HPF_MASK					0x08
#define DA7211_ADC_HPF_F0_8192				0x00	// ADC High Pass Filter f0 is at:
#define DA7211_ADC_HPF_F0_4096				0x01
#define DA7211_ADC_HPF_F0_2048				0x02
#define DA7211_ADC_HPF_F0_1024				0x03
#define DA7211_ADC_HPF_F0_MASK				0x03

// DA7211_ADC (0x10)
#define DA7211_ADC_R_CH_EN					0x80	// Enable right ADC channel
#define DA7211_ADC_R_CH_DIS					0x00
#define DA7211_ADC_R_CH_MASK				0x80
#define DA7211_ADC_R_MUTE_ON				0x40	// Mute right ADC channel
#define DA7211_ADC_R_MUTE_OFF				0x00
#define DA7211_ADC_R_MUTE_MASK				0x40
#define DA7211_ADC_L_CH_EN					0x08	// Enable left ADC channel
#define DA7211_ADC_L_CH_DIS					0x00
#define DA7211_ADC_L_CH_MASK				0x08
#define DA7211_ADC_L_MUTE_ON				0x04	// Mute left ADC channel
#define DA7211_ADC_L_MUTE_OFF				0x00
#define DA7211_ADC_L_MUTE_MASK				0x04
#define DA7211_ADC_ALC_EN					0x01	// ALC enable
#define DA7211_ADC_ALC_DIS					0x00
#define DA7211_ADC_ALC_MASK					0x01
#define DA7211_ADC_CH_EN					(DA7211_ADC_R_CH_EN | DA7211_ADC_L_CH_EN)
#define DA7211_ADC_CH_DIS					(DA7211_ADC_R_CH_DIS | DA7211_ADC_L_CH_DIS)
#define DA7211_ADC_CH_MASK					(DA7211_ADC_R_CH_MASK | DA7211_ADC_L_CH_MASK)
#define DA7211_ADC_MUTE_ON					(DA7211_ADC_R_MUTE_ON | DA7211_ADC_L_MUTE_ON)
#define DA7211_ADC_MUTE_OFF					(DA7211_ADC_R_MUTE_OFF | DA7211_ADC_L_MUTE_OFF)
#define DA7211_ADC_MUTE_MASK				(DA7211_ADC_R_MUTE_MASK | DA7211_ADC_L_MUTE_MASK)


// DA7211_ADC_EQ1_2 (0x11)

// DA7211_ADC_EQ3_4 (0x12)

// DA7211_ADC_EQ5 (0x13)

// DA7211_DAC_HPF (0x14)
#define DA7211_DAC_VOICE_EN					0x80	// DAC Voice Filter
#define DA7211_DAC_VOICE_DIS				0x00
#define DA7211_DAC_VOICE_EN					0x80
#define DA7211_DAC_VOICE_F0_2_5HZ			0x00	// DAC Voice (8kHz) High pass 3dB cutoff at:
#define DA7211_DAC_VOICE_F0_25HZ			0x10
#define DA7211_DAC_VOICE_F0_50HZ			0x20
#define DA7211_DAC_VOICE_F0_100HZ			0x30
#define DA7211_DAC_VOICE_F0_150HZ			0x40
#define DA7211_DAC_VOICE_F0_200HZ			0x50
#define DA7211_DAC_VOICE_F0_300HZ			0x60
#define DA7211_DAC_VOICE_F0_400HZ			0x70
#define DA7211_DAC_VOICE_F0_MASK			0x70
#define DA7211_DAC_HPF_EN					0x08	// DAC High Pass Filter
#define DA7211_DAC_HPF_DIS					0x00
#define DA7211_DAC_HPF_MASK					0x08
#define DA7211_DAC_MUTE_ON					0x04	// Mute DAC (both channels)
#define DA7211_DAC_MUTE_OFF					0x00
#define DA7211_DAC_MUTE_MASK				0x04
#define DA7211_DAC_HPF_F0_8192				0x00	// DAC High Pass Filter f0 is at:
#define DA7211_DAC_HPF_F0_4096				0x01
#define DA7211_DAC_HPF_F0_2048				0x02
#define DA7211_DAC_HPF_F0_1024				0x03
#define DA7211_DAC_HPF_F0_MASK				0x03

// DA7211_DAC_L (0x15)
#define DA7211_DAC_L_INV_NORMAL				0x00	// Left DAC channel inversion
#define DA7211_DAC_L_INV_INVERTED			0x80
#define DA7211_DAC_L_INV_MASK				0x80
#define DA7211_DAC_L_GAIN_MASK				0x7F	// DAC left channel digital volume
#define DA7211_DAC_L_GAIN_ZERO				0x7F

// DA7211_DAC_R (0x16)
#define DA7211_DAC_R_INV_NORMAL				0x00	// Right DAC channel inversion
#define DA7211_DAC_R_INV_INVERTED			0x80
#define DA7211_DAC_R_INV_MASK				0x80
#define DA7211_DAC_R_GAIN_MASK				0x7F	// DAC right channel digital volume
#define DA7211_DAC_R_GAIN_ZERO				0x7F

// DA7211_DAC_SEL (0x17)
#define DA7211_DAC_R_CH_EN					0x80	// Enable right DAC channel
#define DA7211_DAC_R_CH_DIS					0x00
#define DA7211_DAC_R_CH_MASK				0x80
#define DA7211_DAC_R_SRC_1AB				0x00	// DAC_R input source selection:
#define DA7211_DAC_R_SRC_2AB				0x10
#define DA7211_DAC_R_SRC_1CD				0x20
#define DA7211_DAC_R_SRC_2CD				0x30
#define DA7211_DAC_R_SRC_DAI_L				0x40
#define DA7211_DAC_R_SRC_DAI_R				0x50
#define DA7211_DAC_R_SRC_ADC_L				0x60
#define DA7211_DAC_R_SRC_ADC_R				0x70
#define DA7211_DAC_R_SRC_MASK				0x70
#define DA7211_DAC_L_CH_EN					0x08	// Enable left DAC channel
#define DA7211_DAC_L_CH_DIS					0x00
#define DA7211_DAC_L_CH_MASK				0x08
#define DA7211_DAC_L_SRC_1AB				0x00	// DAC_L input source selection:
#define DA7211_DAC_L_SRC_2AB				0x01
#define DA7211_DAC_L_SRC_1CD				0x02
#define DA7211_DAC_L_SRC_2CD				0x03
#define DA7211_DAC_L_SRC_DAI_L				0x04
#define DA7211_DAC_L_SRC_DAI_R				0x05
#define DA7211_DAC_L_SRC_ADC_L				0x06
#define DA7211_DAC_L_SRC_ADC_R				0x07
#define DA7211_DAC_L_SRC_MASK				0x07
#define DA7211_DAC_CH_EN					(DA7211_DAC_R_CH_EN | DA7211_DAC_L_CH_EN)
#define DA7211_DAC_CH_DIS					(DA7211_DAC_R_CH_DIS | DA7211_DAC_L_CH_DIS)
#define DA7211_DAC_CH_MASK					(DA7211_DAC_R_CH_MASK | DA7211_DAC_L_CH_MASK)


// DA7211_SOFT_MUTE (0x18)
#define DA7211_SOFTMUTE_START				0x80	// Softmute trigger
#define DA7211_SOFTMUTE_DIS					0x00
#define DA7211_SOFTMUTE_MASK				0x80
#define DA7211_RAMP_RAMPING					0x40	// Digital gain ramping
#define DA7211_RAMP_IMMEDIATE				0x00
#define DA7211_RAMP_MASK					0x40
#define DA7211_MUTE_RATE_1_SAMPLE			0x00	// Mute rate
#define DA7211_MUTE_RATE_2_SAMPLE			0x01
#define DA7211_MUTE_RATE_4_SAMPLE			0x02
#define DA7211_MUTE_RATE_8_SAMPLE			0x03
#define DA7211_MUTE_RATE_16_SAMPLE			0x04
#define DA7211_MUTE_RATE_32_SAMPLE			0x05
#define DA7211_MUTE_RATE_64_SAMPLE			0x06
#define DA7211_MUTE_RATE_128_SAMPLE			0x07
#define DA7211_MUTE_RATE_MASK				0x07

// DA7211_DAC_EQ1_2 (0x19)

// DA7211_DAC_EQ3_4 (0x1A)

// DA7211_DAC_EQ5 (0x1B)

// DA7211_OUTMIX_L (0x1C)
#define DA7211_OUT_L_PGA_EN					0x80	// Enable left output PGA
#define DA7211_OUT_L_PGA_DIS				0x00
#define DA7211_OUT_L_PGA_MASK				0x80
#define DA7211_OUT_L_INV_INVERT				0x40	// OUTMIX left channel inversion
#define DA7211_OUT_L_INV_NORMAL				0x00
#define DA7211_OUT_L_INV_MASK				0x40
#define DA7211_OUT_L_DAC_L_ADD				0x10	// Add DAC_L
#define DA7211_OUT_L_DAC_L_DEL				0x00
#define DA7211_OUT_L_DAC_L_MASK				0x10
#define DA7211_OUT_L_IN_R_ADD				0x08	// Add IN_R
#define DA7211_OUT_L_IN_R_DEL				0x00
#define DA7211_OUT_L_IN_R_MASK				0x08
#define DA7211_OUT_L_IN_L_ADD				0x04	// Add IN_L
#define DA7211_OUT_L_IN_L_DEL				0x00
#define DA7211_OUT_L_IN_L_MASK				0x04
#define DA7211_OUT_L_A1_L_ADD				0x01	// Add AUX1_L
#define DA7211_OUT_L_A1_L_DEL				0x00
#define DA7211_OUT_L_A1_L_MASK				0x01
#define DA7211_OUT_L_MIX_MASK				0x1F

// DA7211_OUTMIX_R (0x1D)
#define DA7211_OUT_R_PGA_EN					0x80	// Enable right output PGA
#define DA7211_OUT_R_PGA_DIS				0x00
#define DA7211_OUT_R_PGA_MASK				0x80
#define DA7211_OUT_R_INV_INVERT				0x40	// OUTMIX right channel inversion
#define DA7211_OUT_R_INV_NORMAL				0x00
#define DA7211_OUT_R_INV_MASK				0x40
#define DA7211_OUT_R_DAC_R_ADD				0x10	// Add DAC_R
#define DA7211_OUT_R_DAC_R_DEL				0x00
#define DA7211_OUT_R_DAC_R_MASK				0x10
#define DA7211_OUT_R_IN_R_ADD				0x08	// Add IN_R
#define DA7211_OUT_R_IN_R_DEL				0x00
#define DA7211_OUT_R_IN_R_MASK				0x08
#define DA7211_OUT_R_IN_L_ADD				0x04	// Add IN_L
#define DA7211_OUT_R_IN_L_DEL				0x00
#define DA7211_OUT_R_IN_L_MASK				0x04
#define DA7211_OUT_R_A1_R_ADD				0x01	// Add AUX1_R
#define DA7211_OUT_R_A1_R_DEL				0x00
#define DA7211_OUT_R_A1_R_MASK				0x01
#define DA7211_OUT_R_MIX_MASK				0x1F

// DA7211_OUT1_L (0x1E)
#define DA7211_OUT1_L_AMP_EN				0x80	// Enable left OUT1 amplifier
#define DA7211_OUT1_L_AMP_DIS				0x00
#define DA7211_OUT1_L_AMP_MASK				0x80
#define DA7211_OUT1_L_SEL_DIFFERENTIAL		0x00	// OUT1 L-ch single-ended mode selection
#define DA7211_OUT1_L_SEL_SINGLE_ENDED		0x40
#define DA7211_OUT1_L_SEL_MASK				0x40
#define DA7211_OUT1_L_VOL_MASK				0x3F	// OUT1 left channel volume control
#define DA7211_OUT1_VOL_ZERO				0x10

// DA7211_OUT1_R (0x1F)
#define DA7211_OUT1_R_AMP_EN				0x80	// Enable right OUT1 amplifier
#define DA7211_OUT1_R_AMP_DIS				0x00
#define DA7211_OUT1_R_AMP_MASK				0x80
#define DA7211_OUT1_R_SEL_DIFFERENTIAL		0x00	// OUT1 R-ch single-ended mode selection
#define DA7211_OUT1_R_SEL_SINGLE_ENDED		0x40
#define DA7211_OUT1_R_SEL_MASK				0x40
#define DA7211_OUT1_R_VOL_MASK				0x3F	// OUT1 right channel volume control

// DA7211_HP_L_VOL (0x21)
#define DA7211_HP_L_VOL_MASK				0x3F	// Haedphone left channel volume control
#define DA7211_HP_VOL_ZERO					0x10

// DA7211_HP_R_VOL (0x22)
#define DA7211_HP_R_VOL_MASK				0x3F	// Haedphone right channel volume control

// DA7211_HP_CFG (0x23)
#define DA7211_HP_R_AMP_EN					0x80	// Enable right headphone ampliier
#define DA7211_HP_R_AMP_DIS					0x00
#define DA7211_HP_R_AMP_MASK				0x80
#define DA7211_STEREO_TRACK_ON				0x20	// HP_R volume also control HP_L
#define DA7211_STEREO_TRACK_OFF				0x00
#define DA7211_STEREO_TRACK_MASK			0x20
#define DA7211_HP_L_AMP_EN					0x08	// Enable left headphone ampliier
#define DA7211_HP_L_AMP_DIS					0x00
#define DA7211_HP_L_AMP_MASK				0x08
#define DA7211_HP_2CAP_MODE_ON				0x02	// Set charge pump to 2 capacitor mode
#define DA7211_HP_2CAP_MODE_OFF				0x00
#define DA7211_HP_2CAP_MODE_MASK			0x02
#define DA7211_HP_HIGHZ_L_ON				0x01	// Set left headphone out to high impendance
#define DA7211_HP_HIGHZ_L_OFF				0x00
#define DA7211_HP_HIGHZ_L_MASK				0x01
#define DA7211_HP_AMP_EN					(DA7211_HP_R_AMP_EN | DA7211_HP_L_AMP_EN)
#define DA7211_HP_AMP_DIS					(DA7211_HP_R_AMP_DIS | DA7211_HP_L_AMP_DIS)
#define DA7211_HP_AMP_MASK					(DA7211_HP_R_AMP_MASK | DA7211_HP_L_AMP_MASK)

// DA7211_ZEROX H (0x24)
#define DA7211_HPZX_R_EN					0x80	// Enable zero crossing for right HP gain update
#define DA7211_HPZX_R_DIS					0x00
#define DA7211_HPZX_R_MASK					0x80
#define DA7211_HPZX_L_EN					0x40	// Enable zero crossing for left HP gain update
#define DA7211_HPZX_L_DIS					0x00
#define DA7211_HPZX_L_MASK					0x40
#define DA7211_OUTZX_R_EN					0x20	// Enable zero crossing for right OUT1 gain update
#define DA7211_OUTZX_R_DIS					0x00
#define DA7211_OUTZX_R_MASK					0x20
#define DA7211_OUTZX_L_EN					0x10	// Enable zero crossing for left OUT1 gain update
#define DA7211_OUTZX_L_DIS					0x00
#define DA7211_OUTZX_L_MASK					0x10
#define DA7211_INZX_R_EN					0x08	// Enable zero crossing for right PGA gain update
#define DA7211_INZX_R_DIS					0x00
#define DA7211_INZX_R_MASK					0x08
#define DA7211_INZX_L_EN					0x04	// Enable zero crossing for left PGA gain update
#define DA7211_INZX_L_DIS					0x00
#define DA7211_INZX_L_MASK					0x04
#define DA7211_A1ZX_R_EN					0x02	// Enable zero crossing for right A1 amp gain update
#define DA7211_A1ZX_R_DIS					0x00
#define DA7211_A1ZX_R_MASK					0x02
#define DA7211_A1ZX_L_EN					0x01	// Enable zero crossing for right A1 amp gain update
#define DA7211_A1ZX_L_DIS					0x00
#define DA7211_A1ZX_L_MASK					0x01

// DA7211_DAI_SRC_SEL (0x25)
#define DA7211_DAI_IN_R_MIX_ON				0x80	// DAI receive right channel is mixed from L+R data
#define DA7211_DAI_IN_R_MIX_OFF				0x00
#define DA7211_DAI_IN_R_MIX_MASK			0x80
#define DA7211_DAI_OUT_R_SRC_1AB			0x00	// DAI_R transimit source selection
#define DA7211_DAI_OUT_R_SRC_2AB			0x10
#define DA7211_DAI_OUT_R_SRC_1CD			0x20
#define DA7211_DAI_OUT_R_SRC_2CD			0x30
#define DA7211_DAI_OUT_R_SRC_DAI_L			0x40
#define DA7211_DAI_OUT_R_SRC_DIA_R			0x50
#define DA7211_DAI_OUT_R_SRC_ADC_L			0x60
#define DA7211_DAI_OUT_R_SRC_ADC_R			0x70
#define DA7211_DAI_OUT_R_SRC_MASK			0x70
#define DA7211_DAI_IN_L_MIX_ON				0x08	// DAI receive left channel is mixed from L+R data
#define DA7211_DAI_IN_L_MIX_OFF				0x00
#define DA7211_DAI_IN_L_MIX_MASK			0x08
#define DA7211_DAI_OUT_L_SRC_1AB			0x00	// DAI_L transimit source selection
#define DA7211_DAI_OUT_L_SRC_2AB			0x01
#define DA7211_DAI_OUT_L_SRC_1CD			0x02
#define DA7211_DAI_OUT_L_SRC_2CD			0x03
#define DA7211_DAI_OUT_L_SRC_DAI_L			0x04
#define DA7211_DAI_OUT_L_SRC_DIA_R			0x05
#define DA7211_DAI_OUT_L_SRC_ADC_L			0x06
#define DA7211_DAI_OUT_L_SRC_ADC_R			0x07
#define DA7211_DAI_OUT_L_SRC_MASK			0x07

// DA7211_DAI_CFG1 (0x26)
#define DA7211_DAI_MODE_SLAVE				0x00	// DA7211 clock mode
#define DA7211_DAI_MODE_MASTER				0x80
#define DA7211_DAI_MODE_MASK				0x80
#define DA7211_DAI_TDM_MONO_MONO			0x10	// TDM transmits/receives left channel left DAI channel only
#define DA7211_DAI_TDM_MONO_STEREO			0x00
#define DA7211_DAI_TDM_MONO_MASK			0x10
#define DA7211_DAI_FRAME_2X_DAI_WORD		0x00	// Data transmission frame Length:
#define DA7211_DAI_FRAME_64_BITCLOCKS		0x04
#define DA7211_DAI_FRAME_128_BITCLOCKS		0x08
#define DA7211_DAI_FRAME_256_BITCLOCKS		0x0C
#define DA7211_DAI_FRAME_MAKS				0x0C
#define DA7211_DAI_WORD_16BITS				0x00	// Data word lengh:
#define DA7211_DAI_WORD_20BITS				0x01
#define DA7211_DAI_WORD_24BITS				0x02
#define DA7211_DAI_WORD_32BITS				0x03
#define DA7211_DAI_WORD_MASK				0x03

// DA7211_DAI_CFG2 (0x27)
#define DA7211_DAI_TDM_OFFS_MASK			0xFF	// TDM data for device is valid at this offset from beginning of frame

// DA7211_DAI_CFG3 (0x28)
#define DA7211_DAI_EN						0x80	// Enable digital audio interface
#define DA7211_DAI_DIS						0x00
#define DA7211_DAI_MASK						0x80
#define DA7211_DAI_OE_EN					0x08	// DATOUT Enable:
#define DA7211_DAI_OE_DIS					0x00
#define DA7211_DAI_OE_MASK					0x08
#define DA7211_DAI_FORMAT_I2S				0x00	// Digital audio interface format selection
#define DA7211_DAI_FORMAT_L_JUSTIFIED		0x01
#define DA7211_DAI_FORMAT_R_JUSTIFIED		0x02
#define DA7211_DAI_FORMAT_DSP				0x03
#define DA7211_DAI_FORMAT_MASK				0x03

// DA7211_PLL_DIV1 (0x29)
#define DA7211_PLL_DIV_H_MASK				0xFF

// DA7211_PLL_DIV2 (0x2A)
#define DA7211_PLL_DIV_M_MASK				0xFF

// DA7211_PLL_DIV3 (0x2B)
#define DA7211_PLL_BYP_EN					0x40	// Bypass PLL
#define DA7211_PLL_BYP_DIS					0x00
#define DA7211_PLL_BYP_MASK					0x40
#define DA7211_PLL_MCLK_RANGE_32_768		0x00	// MCLK frequency range: 32.768kHz
#define DA7211_PLL_MCLK_RANGE_10_20			0x10	// MCLK frequency range: < 10 ~ 20MHz
#define DA7211_PLL_MCLK_RANGE_20_40			0x20	// MCLK frequency range: < 20 ~ 40MHz
#define DA7211_PLL_MCLK_RANGE_40_80			0x30	// MCLK frequency range: < 40 ~ 80MHz
#define DA7211_PLL_MCLK_RANGE_MASK			0x30
#define DA7211_PLL_DIV_L_MASK				0x0F

// DA7211_PLL (0x2C)
#define DA7211_PLL_EN						0x80	// Enable PLL
#define DA7211_PLL_DIS						0x00	// Diabale and bypass PLL
#define DA7211_PLL_MASK						0x80
#define DA7211_MCLK_SRM_EN					0x40	// Sample rate tracking
#define DA7211_MCLK_SRM_DIS					0x00
#define DA7211_MCLK_SRM_MASK				0x40
#define DA7211_MCLK_DET_EN					0x20	// Enable automatic detection of sample rate
#define DA7211_MCLK_DET_DIS					0x00
#define DA7211_MCLK_DET_MASK				0x20
#define DA7211_MCLK_SHAPE_EN				0x10	// Enable MCLK shaper for low level non TTL signals
#define DA7211_MCLK_SHAPE_DIS				0x00
#define DA7211_MCLK_SHAPE_MASK				0x10
#define DA7211_FS_8KHZ						0x01	// 8kHz
#define DA7211_FS_11_025KHZ					0x02	// 11.025kHz
#define DA7211_FS_12KHZ						0x03	// 12kHz
#define DA7211_FS_16KHZ						0x05	// 16kHz
#define DA7211_FS_22_05KHZ					0x06	// 22.050kHz
#define DA7211_FS_24KHZ						0x07	// 24kHz
#define DA7211_FS_32KHZ						0x09	// 32kHz
#define DA7211_FS_44_1KHZ					0x0A	// 44.1kHz
#define DA7211_FS_48KHZ						0x0B	// 48kHz
#define DA7211_FS_88_1KHZ					0x0D	// 88.1kHz
#define DA7211_FS_96KHZ						0x0F	// 96kHz
#define DA7211_FS_MASK						0x0F

// DA7211_DSP_CFG (0x7F)
#define DA7211_DSP_MIX_3_ON					0x40	// Output of section 2AB is mixed with 2CD
#define DA7211_DSP_MIX_3_OFF				0x00
#define DA7211_DSP_MIX_3_MASK				0x40
#define DA7211_DSP_MIX_2_ON					0x20	// Output of section 1CD is mixed with 2AB
#define DA7211_DSP_MIX_2_OFF				0x00
#define DA7211_DSP_MIX_2_MASK				0x20
#define DA7211_DSP_MIX_1_ON					0x10	// Output of section 1AB is mixed with 1CD
#define DA7211_DSP_MIX_1_OFF				0x00
#define DA7211_DSP_MIX_1_MASK				0x10
#define DA7211_GP2CD_EN						0x08	// Enable GP section 2CD
#define DA7211_GP2CD_DIS					0x00
#define DA7211_GP2CD_MASK					0x08
#define DA7211_GP1CD_EN						0x04	// Enable GP section 1CD
#define DA7211_GP1CD_DIS					0x00
#define DA7211_GP1CD_MASK					0x04
#define DA7211_GP2AB_EN						0x02	// Enable GP section 2AB
#define DA7211_GP2AB_DIS					0x00
#define DA7211_GP2AB_MASK					0x02
#define DA7211_GP1AB_EN						0x01	// Enable GP section 1AB
#define DA7211_GP1AB_DIS					0x00
#define DA7211_GP1AB_MASK					0x01

// DA7211_PAGE1 (0x80)

// DA7211_CHIP_ID (0x81)

// DA7211_INTERFACE (0x82)

// DA7211_ALC_MAX (0x83)
#define DA7211_ALC_MERGE_EN					0x40	// ALC joined stereo mode
#define DA7211_ALC_MERGE_DIS				0x00
#define DA7211_ALC_MERGE_MASK				0x40
#define DA7211_ALC_MAX_MASK					0x3F	// ALC Max control level

// DA7211_ALC_MIN (0x84)
#define DA7211_ALC_MIN_MASK					0x3F	// ALC Min control level

// DA7211_ALC_NOIS (0x85)
#define DA7211_ALC_NOIS_MASK				0x3F	// ALC noise gate level

// DA7211_ALC_ATT (0x86)
#define DA7211_ALC_ATT_MASK					0xFF	// ALC attack rate:

// DA7211_ALC_REL (0x87)
#define DA7211_ALC_REL_MASK					0xFF	// ALC release rate:

// DA7211_ALC_DEL (0x88)
#define DA7211_ALC_DEL_MASK					0xFF	// ALC release delay:

// DA7211_A_HID_UNLOCK (0x8A)
#define DA7211_A_HID_REG_UNLOCK				0x8B	// Register unlock: 8B
#define DA7211_A_HID_REG_LOCK				0x00
#define DA7211_A_HID_REG_MASK				0xFF

// DA7211_A_TST_UNLOCK (0x8B)
#define DA7211_A_TST_REG_UNLOCK				0xB4	// Register unlock: B4
#define DA7211_A_TST_REG_LOCK				0x00
#define DA7211_A_TST_REG_MASK				0xFF

// DA7211_A_PLL1 (0x90)
#define DA7211_A_PLL1_EN					0x80	// PLL enable
#define DA7211_A_PLL1_DIS					0x00
#define DA7211_A_PLL1_MASK					0x80

// DA7211_A_CP_CONFIG (0xA2)
#define DA7211_A_CP_CONFIG_EN				0x84

// DA7211_A_CP_MODE (0xA7)
#define DA7211_A_CP_MODE_EN					0x7C	// Headphone charge pump enable
#define DA7211_A_CP_MODE_DIS				0x00
#define DA7211_A_CP_MODE_MASK				0xFF

// DA7211_A_CP_LEVELMODE_LEV0 (0xB0)
#define DA7211_A_CP_LEVELMODE_LEV0_MASK		0xF0	// Headphone charge detection level 0:

// DA7211_A_CP_LEVELMODE_LEV1 (0xB1)
#define DA7211_A_CP_LEVELMODE_LEV1_MASK		0xF0	// Headphone charge detection level 1:

// DA7211_A_CP_LEVELMODE_LEV2 (0xB2)
#define DA7211_A_CP_LEVELMODE_LEV2_MASK		0xF0	// Headphone charge detection level 2:

// DA7211_A_BGAP (0xB7)
#define DA7211_DIGREG_CNTL_1_5				0x00	// Voltage regulator output: 1.5V
#define DA7211_DIGREG_CNTL_1_4				0x10	// Voltage regulator output: 1.4V
#define DA7211_DIGREG_CNTL_1_3				0x20	// Voltage regulator output: 1.3V
#define DA7211_DIGREG_CNTL_1_2				0x30	// Voltage regulator output: 1.2V
#define DA7211_DIGREG_CNTL_MASK				0x30

#define	AUDIO_INIT_MICIN 	0x01   ///<Initialize the CODEC mic input
#define	AUDIO_INIT_LINEIN	0x02  ///<Initialize the CODEC line input
#define	AUDIO_INIT_IN		0x03      ///<Initialize the CODEC both line in and mic in
#define	AUDIO_INIT_OUT		0x04     ///<Initialize the CODEC output
#define	AUDIO_INIT_CUS		0x08     ///<Initialize the CODEC custom IO, reserved for special audio I/O
#define	AUDIO_UNINIT_MICIN	0x10 ///<Uninitialize the CODEC mic input
#define	AUDIO_UNINIT_LINEIN	0x20///<Uninitialize the CODEC line input
#define	AUDIO_UNINIT_IN		0x30    ///<Uninitialize the CODEC both line in and mic in
#define	AUDIO_UNINIT_OUT	0x40   ///<Uninitialize the CODEC output
#define	AUDIO_UNINIT_CUS	0x80    ///<Uninitialize the CODEC custom IO, reserved for special audio I/O
#define	AUDIO_INIT_OUT_LINEIN	0x100///<Initialize the CODEC output and line input

typedef enum _AUDIO_EXTCODEC_PATH
{
    AUDIO_EXT_SPK_OUT = 0,     ///< speaker output path
    AUDIO_EXT_HP_OUT,          ///< headphone output path
    AUDIO_EXT_MIC_IN,          ///< mic in path
    AUDIO_EXT_AUX_IN,          ///< AUX in path
    AUDIO_EXT_MIC_BYPASS_SPK,  ///< mic in bypass to speaker out
    AUDIO_EXT_MIC_BYPASS_HP,   ///< mic in bypass to headphone out
    AUDIO_EXT_AUX_BYPASS_SPK,  ///< AUX in bypass to speaker out
    AUDIO_EXT_AUX_BYPASS_HP,   ///< AUX in bypass to headphone out
    AUDIO_EXT_MIC_IN_SPK_OUT,  ///< mic in and speaker out
    AUDIO_EXT_MIC_IN_HP_OUT,   ///< mic in and headphone out
    AUDIO_EXT_AUX_IN_SPK_OUT,  ///< AUX in and speaker out
    AUDIO_EXT_AUX_IN_HP_OUT,   ///< AUX in and headphone out
    AUDIO_EXT_PATH_MAX
} AUDIO_EXTCODEC_PATH;


MMP_ERR MMPC_AudioExtCodec_Init(MMPS_AUDIO_I2S_CFG *I2SConfig, MMP_ULONG samplerate, MMP_ULONG ulFixedMclkFreq);
MMP_ERR MMPC_AudioExtCodec_Uninit(void);
MMP_ERR MMPC_AudioExtCodec_SetPath(MMP_ULONG path);
MMP_ERR MMPC_AudioExtCodec_SetVolume(MMP_ULONG volume);
extern MMP_ULONG MMPC_AudioExtCodec_GetMClkFs(MMP_ULONG ulSamplerate);
//void AD_In_Mic(void);
//void Mic_Mute(unsigned char ucMute);
//void DA7211_SetMasterMode(MMP_BOOL bMaster);
//void DA7211_SetActiveMode(MMP_BOOL bActive);
//void CODEC_Init(void);
//void CODEC_Power(unsigned char pd);
//void CODEC_Mute(unsigned char ucMute);
#endif // __DA7211_H__
