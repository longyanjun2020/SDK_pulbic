#include "mmp_lib.h"
#include "ait_utility.h"
#if (EXT_CODEC_SUPPORT == 1)
#include "lib_retina.h"
//#include "mmp_reg_gbl.h"
//#include "mmp_reg_vif.h"
#include "mmpd_system.h"
#include "mmps_audio.h"
#include "mmpf_i2cm.h"
#include "da7211.h"

MMP_ULONG glDA7211SampleRate;

static MMP_BOOL m_bCodecInitialized = MMP_FALSE;
static MMP_BOOL m_bCodecAsMaster = MMP_FALSE;
static AUDIO_EXTCODEC_PATH m_ulCodecPath = AUDIO_EXT_PATH_MAX;
#define DA7211_I2C_SLAVE_ADDR		0x1A
#define VI_GPIO_I2C					0

MMP_I2CM_ATTR gI2cmAttribute_DA7211 = {
    MMP_I2CM1,      // i2cmID
    DA7211_I2C_SLAVE_ADDR,  // ubSlaveAddr
    8,          // ubRegLen
    8,          // ubDataLen
    0x10,       // ubDelayTime
    MMP_FALSE,  // bDelayWaitEn
    MMP_FALSE,  // bInputFilterEn
    MMP_FALSE,  // b10BitModeEn
    MMP_FALSE,  // bClkStretchEn
    0,          // ubSlaveAddr1
    0,          // ubDelayCycle
    6,          // ubPadNum
    200000,     // ulI2cmSpeed 200KHZ
    MMP_TRUE,   // bOsProtectEn
    NULL,       // sw_clk_pin
    NULL,       // sw_data_pin
    MMP_FALSE,  // bRfclModeEn
    MMP_FALSE   // bWfclModeEn
);

//#define I2S_SLAVE_MODE  1
//Start
#if 0
//*----------------------------------------------------------------------------
//* Function Name       : SetI2CDelay
//* Input Parameters    : none
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void SetI2CDelay(void)
{
    int   j;

    for(j=0; j < I2C_DELAY ;j++);
}

//*----------------------------------------------------------------------------
//* Function Name       : SetI2CDir
//* Input Parameters    : <mask>   = bit mask identifying the PIOs
//*                     : <config> = mask identifying the PIOs configuration
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void SetI2CDir(MMP_UBYTE mask, MMP_UBYTE config)
{
    AITPS_VIF   pVIF    = AITC_BASE_VIF;

    if ((config & I2C_OUTPUT) == I2C_OUTPUT) {
        pVIF->VIF_0_SENSR_SIF_EN |= mask;
    }
    else {
        pVIF->VIF_0_SENSR_SIF_EN &= ~mask;
    }
}

//*----------------------------------------------------------------------------
//* Function Name       : SetI2COutput
//* Object              : Write a data on required PIOs
//* Input Parameters    : <mask>   = defines work pins
//*                     : <state>  = defines set ( =0) or clear ( #0)
//* Output Parameters   : none
//* Functions called    : none
//*----------------------------------------------------------------------------
void SetI2COutput(MMP_UBYTE mask, MMP_UBYTE state)
{
    AITPS_VIF   pVIF    = AITC_BASE_VIF;

    if ((state & I2C_CLEAR_OUT) == I2C_CLEAR_OUT) {
        pVIF->VIF_0_SENSR_SIF_DATA &= ~mask;
    }
    else {
        pVIF->VIF_0_SENSR_SIF_DATA |= mask;
    }
}

//*----------------------------------------------------------------------------
// function : GetI2CSDA
// input    : none
// output   : none
// descript :
//            Control Pin : P11 -> SCL (O), P8 -> SDA (I/O)
//*----------------------------------------------------------------------------
MMP_UBYTE GetI2CSDA(void)
{
    AITPS_VIF   pVIF    = AITC_BASE_VIF;

    if ((pVIF->VIF_0_SENSR_SIF_DATA & I2C_SDA) == I2C_SDA) {
        return I2C_HIGH;
    }
    else {
        return I2C_LOW;
    }
}

//*----------------------------------------------------------------------------
// function : StartI2C
// input    : none
// output   : none
// descript : I2C Start Condition
//            Control Pin : P11 -> SCL (O), P8 -> SDA (I/O)
//*----------------------------------------------------------------------------
void StartI2C(void)
{
    SetI2CDir(I2C_SDA, I2C_OUTPUT);
    SetI2COutput((I2C_SCL|I2C_SDA), I2C_SET_OUT);
    SetI2CDelay();
    SetI2COutput(I2C_SDA, I2C_CLEAR_OUT);
    SetI2CDelay();
}

//*----------------------------------------------------------------------------
// function : StopI2C
// input    : none
// output   : none
// descript : I2C Stop Condition
//            Control Pin : P11 -> SCL (O), P8 -> SDA (I/O)
//*----------------------------------------------------------------------------
void StopI2C()
{
    SetI2CDir(I2C_SDA, I2C_OUTPUT);
    SetI2COutput(I2C_SDA, I2C_CLEAR_OUT);
    SetI2CDelay();
    SetI2COutput(I2C_SCL, I2C_SET_OUT);
    SetI2CDelay();
    SetI2COutput(I2C_SDA, I2C_SET_OUT);
    SetI2CDelay();
}

//*----------------------------------------------------------------------------
// function : WriteI2C_DATA(MMP_UBYTE data)
// input    : one byte data to write
// output   : none
// descript : send device address write command
//            Control Pin : P11 -> SCL (O), P8 -> SDA (I/O)
//*----------------------------------------------------------------------------
void WriteI2C_DATA(MMP_UBYTE data)
{
    MMP_ULONG   i;
    MMP_UBYTE  cShift;

//----
#if 1
    SetI2COutput(I2C_SCL, I2C_CLEAR_OUT);
    SetI2CDelay();
#endif
//----

    SetI2CDir(I2C_SDA, I2C_OUTPUT);

    cShift = 0x80;
    for(i = 0; i < 8; i++) {
        if(data & cShift) {
            SetI2COutput(I2C_SDA, I2C_SET_OUT);
            SetI2COutput(I2C_SCL, I2C_CLEAR_OUT);
        }
        else {
            SetI2COutput(I2C_SDA | I2C_SCL, I2C_CLEAR_OUT);
        }

        SetI2CDelay();
        SetI2COutput(I2C_SCL, I2C_SET_OUT);
        SetI2CDelay();
        SetI2COutput(I2C_SCL, I2C_CLEAR_OUT);
        SetI2CDelay();
        cShift >>= 1;
    }
}

//*----------------------------------------------------------------------------
// function : ReadI2C_DATA
// input    : none
// output   : one byte data to read
// descript : get one byte data from device
//            Control Pin : P11 -> SCL (O), P8 -> SDA (I/O)
//*----------------------------------------------------------------------------
MMP_UBYTE  ReadI2C_DATA(void)
{
    int i;
    MMP_UBYTE  ReceiveData;
    MMP_UBYTE  bit_val;

    SetI2COutput(I2C_SCL, I2C_CLEAR_OUT);
    SetI2CDir(I2C_SDA, I2C_INPUT);

    ReceiveData = 0;
    for(i = 0; i < 8; i++) {
        SetI2CDelay();
        SetI2COutput(I2C_SCL, I2C_SET_OUT);
        bit_val = GetI2CSDA();
        ReceiveData |= bit_val;
        if(i < 7)
            ReceiveData <<= 1;
        SetI2CDelay();
        SetI2COutput(I2C_SCL, I2C_CLEAR_OUT);
    }
    return(ReceiveData);
}

//*----------------------------------------------------------------------------
// function : GetI2CACK
// input    : none
// output   : none
// descript : I2C Acknowledge Polling
//            Control Pin : P11 -> SCL (O), P8 -> SDA (I/O)
//*----------------------------------------------------------------------------
void GetI2CACK(void)
{
    MMP_UBYTE  bit_val;
    MMP_ULONG  try_cnt = 5;

    SetI2COutput(I2C_SCL, I2C_CLEAR_OUT);
    SetI2CDir(I2C_SDA, I2C_INPUT);
    SetI2CDelay();  //add by Leon
    SetI2COutput(I2C_SCL, I2C_SET_OUT);
    SetI2CDelay();

    do{
        bit_val = GetI2CSDA();
        SetI2CDelay();
        try_cnt--;
    }while(bit_val && try_cnt);

    SetI2CDelay();
    SetI2CDir(I2C_SDA, I2C_OUTPUT);
    SetI2COutput(I2C_SCL, I2C_CLEAR_OUT);
    SetI2CDelay();
}

//*----------------------------------------------------------------------------
// function : SendI2CNACK
// input    : none
// output   : none
// descript : I2C NotAcknowledge for read
//            Control Pin : P11 -> SCL (O), P8 -> SDA (I/O)
//*----------------------------------------------------------------------------
void SendI2CNACK(void)
{
    // set SDA to output
    SetI2CDir(I2C_SDA, I2C_OUTPUT);
    SetI2COutput(I2C_SDA, I2C_SET_OUT);
    SetI2COutput(I2C_SCL, I2C_CLEAR_OUT);
    SetI2CDelay();
    SetI2COutput(I2C_SCL, I2C_SET_OUT);
    SetI2CDelay();
    SetI2COutput(I2C_SCL, I2C_CLEAR_OUT);
    SetI2COutput(I2C_SDA, I2C_CLEAR_OUT);
    SetI2CDelay();
    SetI2COutput(I2C_SCL, I2C_SET_OUT);
    SetI2CDelay();
}

//*----------------------------------------------------------------------------
// function : SendI2CACK
// input    : none
// output   : none
// descript : I2C Acknowledge for read
//            Control Pin : P11 -> SCL (O), P8 -> SDA (I/O)
//*----------------------------------------------------------------------------
void SendI2CACK(void)
{
    // set SDA to output
    SetI2CDir(I2C_SDA, I2C_OUTPUT);
    SetI2COutput((I2C_SCL | I2C_SDA), I2C_CLEAR_OUT);
    SetI2CDelay();
    SetI2COutput(I2C_SCL, I2C_SET_OUT);
    SetI2CDelay();
    SetI2COutput(I2C_SCL, I2C_CLEAR_OUT);
}

//*----------------------------------------------------------------------------
// function : InitI2C
// input    : (address)
// output   : (data)
// descript : Initial I2C data and clock pin
//*----------------------------------------------------------------------------
void InitI2C(void)
{

    /// This function assume that host program using software I2C to control audio DAC.

    SetI2CDir(I2C_SDA, I2C_OUTPUT);
    SetI2COutput(I2C_SDA, I2C_SET_OUT);

    SetI2CDir(I2C_SCL, I2C_OUTPUT);
    SetI2COutput(I2C_SCL, I2C_SET_OUT);
}

#endif
//END

//*----------------------------------------------------------------------------
// function :MMPF_WriteCodecI2CReg
// input    : (Register address, Register data)
// output   : none
// descript : write codec register
//*----------------------------------------------------------------------------
void DA7211_Write(MMP_USHORT RegAddr, MMP_USHORT RegData)
{
	//If we need use the vi gpio set to 1
	#if VI_GPIO_I2C
	StartI2C();
	WriteI2C_DATA(WM8971_I2C_DEV_ADDR<<1);		// write device address
	GetI2CACK();

	//RegAddr:7 bits RegData: 1bit
	WriteI2C_DATA(RegAddr<<1|RegData>>8);			// write register address high byte
	GetI2CACK();
	//RegData: 8 bits
	WriteI2C_DATA(RegData&0xFF);			// write register data byte
	GetI2CACK();

	StopI2C();
	#else

	MMPF_I2cm_WriteReg(&gI2cmAttribute_DA7211, RegAddr, RegData);

	#endif
}

MMP_UBYTE GetSampleRate(void)
{	
	switch(glDA7211SampleRate)
	{
		case 8000:
			return DA7211_FS_8KHZ;
			break;
		case 11025:
			return DA7211_FS_11_025KHZ;
			break;
		case 12000:
			return DA7211_FS_12KHZ;
			break;
		case 16000:
			return DA7211_FS_16KHZ;
			break;
		case 22050:
			return DA7211_FS_22_05KHZ;
			break;
		case 24000:
			return DA7211_FS_24KHZ;
			break;
		case 32000:
			return DA7211_FS_32KHZ;
			break;
		case 44100:
			return DA7211_FS_44_1KHZ;
			break;
		case 48000:
			return DA7211_FS_48KHZ;
			break;
		case 81000:
			return DA7211_FS_88_1KHZ;
			break;
		case 96000:
			return DA7211_FS_96KHZ;
			break;
	}
	RTNA_DBG_Str(3, "Error sample rate\r\n");
	return 0;
}

//*----------------------------------------------------------------------------
// function : InitExtDac
// input    : none
// output   : none
// descript : Initial external dac
//*----------------------------------------------------------------------------
void InitExtDac(void)
{
    RTNA_DBG_Str(3, "InitExtDac \r\n");
	DA7211_Write(DA7211_SOFT_MUTE    ,DA7211_SOFTMUTE_START | DA7211_RAMP_RAMPING | DA7211_MUTE_RATE_1_SAMPLE);
	DA7211_Write(DA7211_CONTROL      ,DA7211_BIAS_EN | DA7211_REG_EN);
	
	if(m_bCodecAsMaster == MMP_FALSE){
		DA7211_Write(DA7211_DAI_CFG1     ,DA7211_DAI_MODE_SLAVE | DA7211_DAI_FRAME_2X_DAI_WORD | DA7211_DAI_WORD_16BITS);
		DA7211_Write(DA7211_PLL_DIV3     ,DA7211_PLL_BYP_EN | DA7211_PLL_MCLK_RANGE_10_20);
	}else{
		DA7211_Write(DA7211_DAI_CFG1	 ,DA7211_DAI_MODE_MASTER | DA7211_DAI_FRAME_2X_DAI_WORD | DA7211_DAI_WORD_16BITS);
		DA7211_Write(DA7211_PLL_DIV3	 ,DA7211_PLL_BYP_EN | DA7211_PLL_MCLK_RANGE_10_20);
	}
	
	DA7211_Write(DA7211_PLL          ,DA7211_PLL_DIS | DA7211_MCLK_DET_DIS | DA7211_FS_44_1KHZ);
	
	DA7211_Write(DA7211_DAC_HPF      ,DA7211_DAC_HPF_EN | DA7211_DAC_HPF_F0_8192);
	DA7211_Write(DA7211_DAC_L        ,0x10);//0x10 DAC Gain 0db
	DA7211_Write(DA7211_DAC_R        ,0x10);//0x10 DAC Gain 0db
	DA7211_Write(DA7211_DAC_SEL      ,DA7211_DAC_CH_EN | DA7211_DAC_R_SRC_DAI_R | DA7211_DAC_L_SRC_DAI_L);
	DA7211_Write(DA7211_HP_CFG       ,DA7211_HP_R_AMP_EN | DA7211_HP_L_AMP_EN | DA7211_HP_2CAP_MODE_ON);
	DA7211_Write(DA7211_ZEROX        ,0xFF);
	DA7211_Write(DA7211_DAI_CFG3     ,DA7211_DAI_EN | DA7211_DAI_OE_EN);
	
	DA7211_Write(DA7211_OUTMIX_L     ,DA7211_OUT_L_PGA_EN | DA7211_OUT_L_DAC_L_ADD);
	DA7211_Write(DA7211_OUTMIX_R     ,DA7211_OUT_R_PGA_EN | DA7211_OUT_R_DAC_R_ADD);
	DA7211_Write(DA7211_HP_L_VOL     ,0x10);//0x10 mute
	DA7211_Write(DA7211_HP_R_VOL     ,0x10);//0x10 mute

}
//*----------------------------------------------------------------------------
// function : PwUpExtDac
// input    : none
// output   : none
// descript : Poweron external dac
//*----------------------------------------------------------------------------
void PwUpExtDac(void)
{
    RTNA_DBG_Str(3, "PwUpExtDac \r\n");
   
	DA7211_Write(DA7211_STARTUP2      ,DA7211_DAC_NORMAL | DA7211_HP_NORMAL | DA7211_OUT1_STANDBY);
	DA7211_Write(DA7211_STARTUP3      ,DA7211_ADC_STANDBY | DA7211_AUX1_STANDBY | DA7211_MIC_STANDBY);
	DA7211_Write(DA7211_STARTUP1      ,DA7211_SC_MST_ACTIVE);
	RTNA_WAIT_MS(300);

	DA7211_Write(DA7211_SOFT_MUTE     ,DA7211_SOFTMUTE_DIS | DA7211_RAMP_RAMPING);
	DA7211_Write(DA7211_HP_L_VOL      ,0x30); //0db
	DA7211_Write(DA7211_HP_R_VOL      ,0x30); //0db
}
//*----------------------------------------------------------------------------
// function : PwDownExtDac
// input    : none
// output   : none
// descript : Power down external dac
//*----------------------------------------------------------------------------
void PwDownExtDac(void)
{
    RTNA_DBG_Str(3, "PwDownExtDac \r\n");

	DA7211_Write(DA7211_STARTUP2	 ,DA7211_DAC_STANDBY | DA7211_HP_STANDBY | DA7211_OUT1_STANDBY);
	DA7211_Write(DA7211_STARTUP3	 ,DA7211_ADC_STANDBY | DA7211_AUX1_STANDBY | DA7211_MIC_STANDBY);
	DA7211_Write(DA7211_STARTUP1	 ,DA7211_SC_MST_LOW_PWR);
	RTNA_WAIT_MS(300);

	DA7211_Write(DA7211_ZEROX        ,0x00);
	DA7211_Write(DA7211_DAC_SEL		 ,DA7211_DAC_CH_DIS);
	DA7211_Write(DA7211_DAC_HPF      ,DA7211_DAC_HPF_DIS);
	DA7211_Write(DA7211_OUTMIX_L	 ,DA7211_OUT_L_PGA_DIS);
	DA7211_Write(DA7211_OUTMIX_R	 ,DA7211_OUT_R_PGA_DIS);
	DA7211_Write(DA7211_HP_CFG       ,DA7211_HP_R_AMP_DIS);
	DA7211_Write(DA7211_DAI_CFG3     ,DA7211_DAI_DIS | DA7211_DAI_OE_DIS);
	DA7211_Write(DA7211_DAC_L        ,0x10);//0x10 DAC Gain 0db
	DA7211_Write(DA7211_DAC_R        ,0x10);//0x10 DAC Gain 0db
	DA7211_Write(DA7211_HP_L_VOL     ,0x10);//0x10 mute
	DA7211_Write(DA7211_HP_R_VOL     ,0x10);//0x10 mute
}
//*----------------------------------------------------------------------------
// function : InitExtMicIn
// input    : none
// output   : none
// descript : Initial external mic in
//*----------------------------------------------------------------------------
void InitExtMicIn(void)
{
    RTNA_DBG_Str(3, "InitExtMicIn \r\n");
    
	DA7211_Write(DA7211_SOFT_MUTE    ,DA7211_SOFTMUTE_START | DA7211_RAMP_RAMPING | DA7211_MUTE_RATE_1_SAMPLE);
	DA7211_Write(DA7211_CONTROL      ,DA7211_BIAS_EN | DA7211_REG_EN);
	
	if(m_bCodecAsMaster == MMP_FALSE){
		DA7211_Write(DA7211_DAI_CFG1 	,DA7211_DAI_MODE_SLAVE | DA7211_DAI_FRAME_2X_DAI_WORD | DA7211_DAI_WORD_16BITS);
		DA7211_Write(DA7211_PLL_DIV3    ,DA7211_PLL_BYP_EN | DA7211_PLL_MCLK_RANGE_10_20);
	}else{
		DA7211_Write(DA7211_DAI_CFG1	,DA7211_DAI_MODE_MASTER | DA7211_DAI_FRAME_2X_DAI_WORD | DA7211_DAI_WORD_16BITS);
		DA7211_Write(DA7211_PLL_DIV3	,DA7211_PLL_BYP_EN | DA7211_PLL_MCLK_RANGE_10_20);
	}
	//DA7211_Write(DA7211_PLL          ,DA7211_PLL_DIS | DA7211_MCLK_DET_DIS | DA7211_FS_44_1KHZ);
	DA7211_Write(DA7211_PLL          ,DA7211_PLL_DIS | DA7211_MCLK_DET_DIS | GetSampleRate());
	
	DA7211_Write(DA7211_MIC_L		 ,DA7211_MIC_L_AMP_EN | DA7211_MIC_BIAS_EN | DA7211_MIC_BIAS_SEL_1_6 | 0x01);
	DA7211_Write(DA7211_INMIX_L		 ,DA7211_IN_L_PGA_EN | DA7211_IN_L_MIC_L);
	DA7211_Write(DA7211_INMIX_R		 ,DA7211_IN_L_PGA_EN | DA7211_IN_L_MIC_R);
	DA7211_Write(DA7211_IN_GAIN      ,0xFF);
	DA7211_Write(DA7211_ADC_HPF      ,DA7211_ADC_HPF_EN);
	DA7211_Write(DA7211_ADC			 ,DA7211_ADC_R_CH_EN | DA7211_ADC_L_CH_EN);
	DA7211_Write(DA7211_ZEROX        ,0xFF);
	DA7211_Write(DA7211_DAI_CFG3     ,DA7211_DAI_EN | DA7211_DAI_OE_EN);
}
//*----------------------------------------------------------------------------
// function : PwUpExtMicIn
// input    : none
// output   : none
// descript : Poweron external mic in
//*----------------------------------------------------------------------------
void PwUpExtMicIn(void)
{
    RTNA_DBG_Str(3, "PwUpExtMicIn \r\n");

	DA7211_Write(DA7211_STARTUP2     ,DA7211_DAC_STANDBY | DA7211_HP_STANDBY | DA7211_OUT1_STANDBY);
	DA7211_Write(DA7211_STARTUP3     ,DA7211_ADC_NORMAL | DA7211_AUX1_STANDBY | DA7211_MIC_NORMAL);
	DA7211_Write(DA7211_STARTUP1     ,DA7211_SC_MST_ACTIVE);
	RTNA_WAIT_MS(300);

	DA7211_Write(DA7211_SOFT_MUTE    ,DA7211_SOFTMUTE_DIS | DA7211_RAMP_RAMPING);
}
//*----------------------------------------------------------------------------
// function : PwDownExtMicIn
// input    : none
// output   : none
// descript : Power down external mic in
//*----------------------------------------------------------------------------
void PwDownExtMicIn(void)
{
    RTNA_DBG_Str(3, "PwDownExtMicIn \r\n");

	DA7211_Write(DA7211_STARTUP2	 ,DA7211_DAC_STANDBY | DA7211_HP_STANDBY | DA7211_OUT1_STANDBY);
	DA7211_Write(DA7211_STARTUP3	 ,DA7211_ADC_STANDBY | DA7211_AUX1_STANDBY | DA7211_MIC_STANDBY);
	DA7211_Write(DA7211_STARTUP1	 ,DA7211_SC_MST_LOW_PWR);
	RTNA_WAIT_MS(300);
	
	DA7211_Write(DA7211_ZEROX		 ,0x00);
	DA7211_Write(DA7211_MIC_L		 ,DA7211_MIC_L_AMP_DIS | DA7211_MIC_BIAS_DIS);
	DA7211_Write(DA7211_MIC_R		 ,DA7211_MIC_R_AMP_DIS | DA7211_MIC_BIAS_DIS);
	DA7211_Write(DA7211_ADC			 ,DA7211_ADC_CH_DIS);
	DA7211_Write(DA7211_INMIX_L		 ,DA7211_IN_L_PGA_DIS);
	DA7211_Write(DA7211_INMIX_R		 ,DA7211_IN_R_PGA_DIS);
	DA7211_Write(DA7211_ADC_HPF		 ,DA7211_ADC_HPF_DIS);
	DA7211_Write(DA7211_DAI_CFG3	 ,DA7211_DAI_DIS | DA7211_DAI_OE_DIS);
}
//*----------------------------------------------------------------------------
// function : InitExtLineIn
// input    : none
// output   : none
// descript : Initial external line in
//*----------------------------------------------------------------------------
void InitExtLineIn(void)
{
    RTNA_DBG_Str(3, "InitExtLineIn \r\n");
    
	DA7211_Write(DA7211_SOFT_MUTE    ,DA7211_SOFTMUTE_START | DA7211_RAMP_RAMPING | DA7211_MUTE_RATE_1_SAMPLE);
	DA7211_Write(DA7211_CONTROL      ,DA7211_BIAS_EN | DA7211_REG_EN);
	
	if(m_bCodecAsMaster == MMP_FALSE){
		DA7211_Write(DA7211_DAI_CFG1     ,DA7211_DAI_MODE_SLAVE | DA7211_DAI_FRAME_2X_DAI_WORD | DA7211_DAI_WORD_16BITS);
		DA7211_Write(DA7211_PLL_DIV3     ,DA7211_PLL_BYP_EN | DA7211_PLL_MCLK_RANGE_10_20);
	}else{
		DA7211_Write(DA7211_DAI_CFG1	 ,DA7211_DAI_MODE_MASTER | DA7211_DAI_FRAME_2X_DAI_WORD | DA7211_DAI_WORD_16BITS);
		DA7211_Write(DA7211_PLL_DIV3	 ,DA7211_PLL_BYP_EN | DA7211_PLL_MCLK_RANGE_10_20);
	}
	
	DA7211_Write(DA7211_PLL          ,DA7211_PLL_DIS | DA7211_MCLK_DET_DIS | GetSampleRate());
	
	DA7211_Write(DA7211_INMIX_L		 ,DA7211_IN_L_PGA_EN | DA7211_IN_L_A1_L);
	DA7211_Write(DA7211_INMIX_R		 ,DA7211_IN_R_PGA_EN | DA7211_IN_R_A1_R);
	DA7211_Write(DA7211_AUX1_L       ,DA7211_AUX1_L_AMP_EN | 0x28); 
	DA7211_Write(DA7211_AUX1_R       ,DA7211_AUX1_R_AMP_EN | 0x28);
	DA7211_Write(DA7211_IN_GAIN      ,0x33);
	DA7211_Write(DA7211_ADC_HPF      ,DA7211_ADC_HPF_EN);
	DA7211_Write(DA7211_ADC			 ,DA7211_ADC_R_CH_EN | DA7211_ADC_L_CH_EN);
	DA7211_Write(DA7211_ZEROX        ,0xFF);
	DA7211_Write(DA7211_DAI_CFG3     ,DA7211_DAI_EN | DA7211_DAI_OE_EN);
	
}
//*----------------------------------------------------------------------------
// function : PwUpExtLineIn
// input    : none
// output   : none
// descript : Poweron external line in
//*----------------------------------------------------------------------------
void PwUpExtLineIn(void)
{
    RTNA_DBG_Str(3, "PwUpExtLineIn \r\n");
    
	DA7211_Write(DA7211_STARTUP2     ,DA7211_DAC_STANDBY | DA7211_HP_STANDBY | DA7211_OUT1_STANDBY);
	DA7211_Write(DA7211_STARTUP3     ,DA7211_ADC_NORMAL | DA7211_AUX1_NORMAL | DA7211_MIC_STANDBY);
	DA7211_Write(DA7211_STARTUP1     ,DA7211_SC_MST_ACTIVE);
	RTNA_WAIT_MS(300);

	DA7211_Write(DA7211_SOFT_MUTE    ,DA7211_SOFTMUTE_DIS | DA7211_RAMP_RAMPING);
	DA7211_Write(DA7211_STARTUP1	 ,DA7211_SC_CLK_DIS | DA7211_SC_MST_ACTIVE);
    
}
//*----------------------------------------------------------------------------
// function : PwDownExtLineIn
// input    : none
// output   : none
// descript : Power down external line in
//*----------------------------------------------------------------------------
void PwDownExtLineIn(void)
{
    RTNA_DBG_Str(3, "PwDownExtLineIn \r\n");

    #if 0
    WriteCodecI2CReg(WM8971_PWR_MGMT1,0x000);
    #endif
    
	DA7211_Write(DA7211_STARTUP2	 ,DA7211_DAC_STANDBY | DA7211_HP_STANDBY | DA7211_OUT1_STANDBY);
	DA7211_Write(DA7211_STARTUP3	 ,DA7211_ADC_STANDBY | DA7211_AUX1_STANDBY | DA7211_MIC_STANDBY);
	DA7211_Write(DA7211_STARTUP1	 ,DA7211_SC_MST_LOW_PWR);
	RTNA_WAIT_MS(300);
	
	DA7211_Write(DA7211_ZEROX		 ,0x00);
	DA7211_Write(DA7211_AUX1_L		 ,DA7211_AUX1_L_AMP_DIS);
	DA7211_Write(DA7211_AUX1_R		 ,DA7211_AUX1_R_AMP_DIS);
	DA7211_Write(DA7211_ADC			 ,DA7211_ADC_CH_DIS);
	DA7211_Write(DA7211_INMIX_L		 ,DA7211_IN_L_PGA_DIS);
	DA7211_Write(DA7211_INMIX_R		 ,DA7211_IN_R_PGA_DIS);
	DA7211_Write(DA7211_ADC_HPF		 ,DA7211_ADC_HPF_DIS);    
}
//*----------------------------------------------------------------------------
// function : InitExtLineInDac
// input    : none
// output   : none
// descript : Initial external dac and line in
//*----------------------------------------------------------------------------
void InitExtLineInDac(void)
{
    RTNA_DBG_Str(3, "InitExtLineInDac \r\n");

	DA7211_Write(DA7211_SOFT_MUTE    ,DA7211_SOFTMUTE_START | DA7211_RAMP_RAMPING | DA7211_MUTE_RATE_1_SAMPLE);
	DA7211_Write(DA7211_CONTROL      ,DA7211_BIAS_EN | DA7211_REG_EN);
	
	if(m_bCodecAsMaster == MMP_FALSE){
		DA7211_Write(DA7211_DAI_CFG1     ,DA7211_DAI_MODE_SLAVE | DA7211_DAI_FRAME_2X_DAI_WORD | DA7211_DAI_WORD_16BITS);
		DA7211_Write(DA7211_PLL_DIV3     ,DA7211_PLL_BYP_EN | DA7211_PLL_MCLK_RANGE_10_20);
	}else{
		DA7211_Write(DA7211_DAI_CFG1	 ,DA7211_DAI_MODE_MASTER | DA7211_DAI_FRAME_2X_DAI_WORD | DA7211_DAI_WORD_16BITS);
		DA7211_Write(DA7211_PLL_DIV3	 ,DA7211_PLL_BYP_EN | DA7211_PLL_MCLK_RANGE_10_20);
	}

	DA7211_Write(DA7211_PLL          ,DA7211_PLL_DIS | DA7211_MCLK_DET_DIS | GetSampleRate());
	
	DA7211_Write(DA7211_INMIX_L		 ,DA7211_IN_L_PGA_EN | DA7211_IN_L_A1_L);
	DA7211_Write(DA7211_INMIX_R		 ,DA7211_IN_R_PGA_EN | DA7211_IN_R_A1_R);
	DA7211_Write(DA7211_AUX1_L       ,DA7211_AUX1_L_AMP_EN | 0x28);
	DA7211_Write(DA7211_AUX1_R       ,DA7211_AUX1_R_AMP_EN | 0x28);
	DA7211_Write(DA7211_IN_GAIN      ,0x33);
	DA7211_Write(DA7211_ADC_HPF      ,DA7211_ADC_HPF_EN);
	DA7211_Write(DA7211_ADC			 ,DA7211_ADC_R_CH_EN | DA7211_ADC_L_CH_EN);
	DA7211_Write(DA7211_ZEROX        ,0xFF);
	DA7211_Write(DA7211_DAI_CFG3     ,DA7211_DAI_EN | DA7211_DAI_OE_EN);
	DA7211_Write(DA7211_HP_CFG       ,DA7211_HP_R_AMP_EN | DA7211_HP_L_AMP_EN | DA7211_HP_2CAP_MODE_ON);
	DA7211_Write(DA7211_OUTMIX_L     ,DA7211_OUT_L_PGA_EN | DA7211_OUT_L_A1_L_ADD);
	DA7211_Write(DA7211_OUTMIX_R     ,DA7211_OUT_R_PGA_EN | DA7211_OUT_R_A1_R_ADD);
	DA7211_Write(DA7211_HP_L_VOL     ,0x10);//0x10 mute
	DA7211_Write(DA7211_HP_R_VOL     ,0x10);//0x10 mute
}
//*----------------------------------------------------------------------------
// function : PwupExtLineInDac
// input    : none
// output   : none
// descript : Power up external dac and line in
//*----------------------------------------------------------------------------
void PwUpExtLineInDac(void)
{
	RTNA_DBG_Str(3, "PwUpExtLineInDac \r\n");
	
	DA7211_Write(DA7211_STARTUP2      ,DA7211_DAC_STANDBY | DA7211_HP_NORMAL | DA7211_OUT1_STANDBY);
	DA7211_Write(DA7211_STARTUP3      ,DA7211_ADC_NORMAL | DA7211_AUX1_NORMAL | DA7211_MIC_STANDBY);
	DA7211_Write(DA7211_STARTUP1      ,DA7211_SC_MST_ACTIVE);
	RTNA_WAIT_MS(300);
	
	DA7211_Write(DA7211_SOFT_MUTE     ,DA7211_SOFTMUTE_DIS | DA7211_RAMP_RAMPING);
	DA7211_Write(DA7211_HP_L_VOL      ,0x30); //0db
	DA7211_Write(DA7211_HP_R_VOL      ,0x30); //0db
}

//*----------------------------------------------------------------------------
// function : PwdownExtLineInDac
// input    : none
// output   : none
// descript : Power down external dac and line in
//*----------------------------------------------------------------------------
void PwDownExtLineInDac(void)
{
	RTNA_DBG_Str(3, "PwDownExtLineInDac \r\n");
	

	DA7211_Write(DA7211_STARTUP2	 ,DA7211_DAC_STANDBY | DA7211_HP_STANDBY | DA7211_OUT1_STANDBY);
	DA7211_Write(DA7211_STARTUP3	 ,DA7211_ADC_STANDBY | DA7211_AUX1_STANDBY | DA7211_MIC_STANDBY);
	DA7211_Write(DA7211_STARTUP1	 ,DA7211_SC_MST_LOW_PWR);
	RTNA_WAIT_MS(300);

	DA7211_Write(DA7211_OUTMIX_L	 ,DA7211_OUT_L_PGA_DIS);
	DA7211_Write(DA7211_OUTMIX_R	 ,DA7211_OUT_R_PGA_DIS);
	DA7211_Write(DA7211_ADC			 ,DA7211_ADC_CH_DIS);
	DA7211_Write(DA7211_INMIX_L		 ,DA7211_IN_L_PGA_DIS);
	DA7211_Write(DA7211_INMIX_R		 ,DA7211_IN_R_PGA_DIS);
	DA7211_Write(DA7211_ADC_HPF		 ,DA7211_ADC_HPF_DIS);
	DA7211_Write(DA7211_DAI_CFG3	 ,DA7211_DAI_DIS | DA7211_DAI_OE_DIS);
	DA7211_Write(DA7211_HP_CFG       ,DA7211_HP_R_AMP_DIS);
	DA7211_Write(DA7211_DAI_CFG3     ,DA7211_DAI_DIS | DA7211_DAI_OE_DIS);
	DA7211_Write(DA7211_AUX1_L		 ,DA7211_AUX1_L_AMP_DIS | DA7211_AUX1_L_GAIN_ZERO);
	DA7211_Write(DA7211_AUX1_R		 ,DA7211_AUX1_R_AMP_EN | DA7211_AUX1_R_GAIN_ZERO);
	DA7211_Write(DA7211_IN_GAIN      ,0x00);
	DA7211_Write(DA7211_DAC_L        ,0x10);//0x10 DAC Gain 0db
	DA7211_Write(DA7211_DAC_R        ,0x10);//0x10 DAC Gain 0db
	DA7211_Write(DA7211_HP_L_VOL     ,0x10);//0x10 mute
	DA7211_Write(DA7211_HP_R_VOL     ,0x10);//0x10 mute
	DA7211_Write(DA7211_ZEROX        ,0x00);
	
}


/** @brief Inhouse Wolfson audio CODEC initializer.

See @ref AudioInitializer for more information.
*/
MMP_BOOL AudioInitializer(MMP_USHORT cmd)
{
    if (cmd == AUDIO_INIT_LINEIN) {
        InitExtLineIn();
        PwUpExtLineIn();
    }
    if (cmd == AUDIO_INIT_MICIN) {
        InitExtMicIn();
        PwUpExtMicIn();
    }
    if (cmd == AUDIO_INIT_OUT) {
    	InitExtDac();
    	PwUpExtDac();
    }
    if (cmd == AUDIO_INIT_OUT_LINEIN) {
        InitExtLineInDac();
        PwUpExtLineInDac();
    }

    return MMP_TRUE;
}

//*----------------------------------------------------------------------------
// function : MMPC_AudioExtCodec_GetMClkFs
// input    : ulSamplerate: target samplerate for output/input
// output   : return the fs of MCLK according to external codec spec.
// descript : Config external codec PLL to specified sample rate,
//*----------------------------------------------------------------------------
MMP_ULONG MMPC_AudioExtCodec_GetMClkFs(MMP_ULONG ulSamplerate)
{
	switch(ulSamplerate)
	{
		case 8000:
		case 12000:
		case 16000:
		case 24000:
		case 32000:
		case 48000:
		case 96000:
			ulSamplerate = 48000;
			break;
		case 11025:
		case 22050:
		case 44100:
		case 88200:
			ulSamplerate = 44100;
			break;
	}
    return ulSamplerate;
}
//*----------------------------------------------------------------------------
// function : MMPC_AudioExtCodec_SetSampleRate
// input    : ulSamplerate: external codec runs in USB mode needs to change PLL 
//            according to sample rate
// output   : none
// descript : Config external codec PLL to specified sample rate,
//*----------------------------------------------------------------------------
MMP_ERR MMPC_AudioExtCodec_SetSampleRate(MMP_ULONG ulSamplerate)
{
	glDA7211SampleRate = ulSamplerate;
	DA7211_Write(DA7211_PLL, (DA7211_PLL_DIS | DA7211_MCLK_DET_DIS | GetSampleRate()));
    return MMP_ERR_NONE;
}
//*----------------------------------------------------------------------------
// function : MMPC_AudioExtCodec_SetMute
// input    : bMute: set MMP_TRUE to mute, MMP_FALSE to un-mute 
// output   : none
// descript : Config external codec mute/un-mute.
//*----------------------------------------------------------------------------
MMP_ERR MMPC_AudioExtCodec_SetMute(MMP_BOOL bMute)
{
    if (bMute) {
        //mute
    }
    else {
        //un-mute
    }

    return MMP_ERR_NONE;
}
//*----------------------------------------------------------------------------
// function : MMPC_AudioExtCodec_SetVolume
// input    : level: external codec volume level
// output   : none
// descript : Config external codec volume level,
//*----------------------------------------------------------------------------
MMP_ERR MMPC_AudioExtCodec_SetVolume(MMP_ULONG level)
{
    return MMP_ERR_NONE;
}
//*----------------------------------------------------------------------------
// function : MMPC_AudioExtCodec_SetPath
// input    : path: please refer MMPF_AUDIO_EXTCODEC_PATH for path can be set
// output   : none
// descript : Config external codec path if alreay iniialized, otherwise,
//            keep the path settings only.
//*----------------------------------------------------------------------------
MMP_ERR MMPC_AudioExtCodec_SetPath(MMP_ULONG path)
{
    m_ulCodecPath = path;

    return MMP_ERR_NONE;
}

//*----------------------------------------------------------------------------
// function : MMPC_AudioExtCodec_Init
// input    : samplerate: Sample rate
// output   : none
// descript : Initialize and power up codec according to path settings,
//            be careful, please call MMPC_AudioExtCodec_SetPath first to set path
//            Audio playback case:
// 			  In the line out mode, the sample rate setting is no use in Da7211. Da7211 always set the sample rate at 44.1k  .
//            It means the da7211 internal pll divider doesn't use. the sample rate depends on AIT
//            Audio encode case:
//            In the line in bypass, line in or mic mode, DA7211 must work in master mode, and master clock setting
//            should be 11.289 Mhz or 12.288 Mhz (because AIT I2S MCLK mode select(0x8000884c) can't support da7211)
//            The Da7211 master clock should be setting as below
//            11.289Mhz for sample rate 11.025k, 22.05k, 44.1km 88.2k
//            12.288Mhz for sample rate 8k, 16k,24k, 32k, 48k, 96k 
//*----------------------------------------------------------------------------
MMP_ERR MMPC_AudioExtCodec_Init(MMPS_AUDIO_I2S_CFG *I2SConfig, MMP_ULONG samplerate, MMP_ULONG ulFixedMclkFreq)
{
    if (m_ulCodecPath == AUDIO_EXT_PATH_MAX) {
        RTNA_DBG_Str0("Please set path first before init codec!\r\n");
        return MMP_AUDIO_ERR_INVALID_FLOW;
    }
    if (I2SConfig->workingMode == MMPS_AUDIO_I2S_MASTER_MODE) {
        //set AIT as master, set codec as slave
        m_bCodecAsMaster = MMP_FALSE;
    }
    else {
        //set AIT as slave, set codec as master
        m_bCodecAsMaster = MMP_TRUE;
    }
	glDA7211SampleRate = samplerate;
	#if VI_GPIO_I2C
	InitI2C();
	#endif
    switch (m_ulCodecPath) {
    case AUDIO_EXT_HP_OUT:
        AudioInitializer(AUDIO_INIT_OUT);
        break;
    case AUDIO_EXT_MIC_IN:
        AudioInitializer(AUDIO_INIT_MICIN);
        break;
    case AUDIO_EXT_AUX_IN:
        AudioInitializer(AUDIO_INIT_LINEIN);
        break;
    case AUDIO_EXT_AUX_BYPASS_HP:
        AudioInitializer(AUDIO_INIT_OUT_LINEIN);
        break;
    default:
        return MMP_AUDIO_ERR_PARAMETER;
        break;
    }
    m_bCodecInitialized = MMP_TRUE;

    return MMP_ERR_NONE;
}

//*----------------------------------------------------------------------------
// function : MMPC_AudioExtCodec_Uninit
// input    : none
// output   : none
// descript : Uninitialize and power down codec according to path settings.
//*----------------------------------------------------------------------------
MMP_ERR MMPC_AudioExtCodec_Uninit(void)
{
    if (m_bCodecInitialized) {
        switch (m_ulCodecPath) {
        case AUDIO_EXT_HP_OUT:
            PwDownExtDac();
            break;
        case AUDIO_EXT_MIC_IN:
            PwDownExtMicIn();
            break;
        case AUDIO_EXT_AUX_IN:
            PwDownExtLineIn();
            break;
        case AUDIO_EXT_AUX_BYPASS_HP:
			PwDownExtLineInDac();
            break;
        default:
            return MMP_AUDIO_ERR_PARAMETER;
            break;
        }
        m_bCodecInitialized = MMP_FALSE;
    }

    return MMP_ERR_NONE;
}
#endif
