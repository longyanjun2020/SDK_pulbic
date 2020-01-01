#ifndef _WM8971_H
#define _WM8971_H

#include "ait_config.h"


#define	I2C_PORT_MODE		(0x80000050)
#define	I2C_PORT_DATA		(0x80000051)


#define I2C_SCL             (0x1<<1)
#define I2C_SDA             (0x1<<2)

#define I2C_DELAY           100

#define I2C_HIGH            1
#define I2C_LOW             0

#define I2C_INPUT           0x0
#define I2C_OUTPUT          0x1

#define I2C_SET_OUT         0x0
#define I2C_CLEAR_OUT       0x1

#define WM8971_L_INPUT_VOLUME                       0x00
#define WM8971_R_INPUT_VOLUME                       0x01
#define WM8971_LOUT1_VOLUME                         0x02
#define WM8971_RLOU1_VOLUME                         0x03
#define WM8971_ADC_DAC_CONTROL                      0x05
#define WM8971_AUDIO_INTERFACE                      0x07
#define WM8971_SAMPLE_RATE                          0x08
#define WM8971_L_DAC_VOLUME                         0x0A
#define WM8971_R_DAC_VOLUME                         0x0B
#define WM8971_BASS_CONTROL                         0x0C
#define WM8971_TREBLE_CONTROL                       0x0D
#define WM8971_RESET                                0x0F
#define WM8971_ALC1                                 0x11
#define WM8971_ALC2                                 0x12
#define WM8971_ALC3                                 0x13
#define WM8971_NOISE_GATE                           0x14
#define WM8971_L_ADC_VOLUME                         0x15
#define WM8971_R_ADC_VOLUME                         0x16
#define WM8971_ADDITIONAL_CONTROL1                  0x17
#define WM8971_ADDITIONAL_CONTROL2                  0x18
#define WM8971_PWR_MGMT1                            0x19                
#define WM8971_PWR_MGMT2                            0x1A    
#define WM8971_ADDITIONAL_CONTROL3                  0x1B             
#define WM8971_ADC_INPUT_MODE                       0x1F         
#define WM8971_ADCL_SIGNAL_PATH                     0x20           
#define WM8971_ADCR_SIGNAL_PATH                     0x21           
#define WM8971_L_OUT_MIX1                           0x22     
#define WM8971_L_OUT_MIX2                           0x23     
#define WM8971_R_OUT_MIX1                           0x24     
#define WM8971_R_OUT_MIX2                           0x25     
#define WM8971_MONO_OUT_MIX1                        0x26        
#define WM8971_MONO_OUT_MIX2                        0x27        
#define WM8971_LOUT2_VOLUME                         0x28      
#define WM8971_ROUT2_VOLUME                         0x29       
#define WM8971_MONOOUT_VOLUME                       0x2A      

//#define WM8971_I2C_DEV_ADDR						0x1B //CSB High
#define WM8971_I2C_DEV_ADDR						0x1A //CSB Low

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

extern void	InitExtDac(void);
extern void	PwUpExtDac(void);
extern void	PwDownExtDac(void);
extern void	InitExtMicIn(void);
extern void	PwUpExtMicIn(void);
extern void	PwDownExtMicIn(void);
extern void	InitExtLineIn(void);
extern void	PwUpExtLineIn(void);
extern void	PwDownExtLineIn(void);
extern void PwUpExtLineInDac(void);
extern void	InitExtLineInDac(void);
extern MMP_BOOL	audioInitializer(MMP_USHORT cmd);

extern MMP_ERR MMPC_AudioExtCodec_SetPath(MMP_ULONG path);
extern MMP_ERR MMPC_AudioExtCodec_Init(MMPS_AUDIO_I2S_CFG *I2SConfig, MMP_ULONG samplerate, MMP_ULONG ulFixedMclkFreq);
extern MMP_ERR MMPC_AudioExtCodec_Uninit(void);
extern MMP_ERR MMPC_AudioExtCodec_SetSampleRate(MMP_ULONG ulSamplerate);
extern MMP_ERR MMPC_AudioExtCodec_SetMute(MMP_BOOL bMute);
extern MMP_ERR MMPC_AudioExtCodec_SetVolume(MMP_ULONG level);
extern MMP_ULONG MMPC_AudioExtCodec_GetMClkFs(MMP_ULONG ulSamplerate);
#endif