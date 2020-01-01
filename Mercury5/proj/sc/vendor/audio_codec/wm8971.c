#include "mmp_lib.h"
#include "ait_utility.h"
#if (EXT_CODEC_SUPPORT == 1)
#include "lib_retina.h"
//#include "mmp_reg_gbl.h"
//#include "mmp_reg_vif.h"
#include "mmpd_system.h"
#include "mmps_audio.h"
#include "wm8971.h"

static MMP_BOOL m_bCodecInitialized = MMP_FALSE;
static MMP_BOOL m_bCodecAsMaster = MMP_FALSE;
static AUDIO_EXTCODEC_PATH m_ulCodecPath = AUDIO_EXT_PATH_MAX;

#define I2S_SLAVE_MODE  1
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
        pVIF->VIF_SENSR_SIF_EN |= mask;
    }
    else {
        pVIF->VIF_SENSR_SIF_EN &= ~mask;
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
        pVIF->VIF_SENSR_SIF_DATA &= ~mask;
    }
    else {
        pVIF->VIF_SENSR_SIF_DATA |= mask;
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

    if ((pVIF->VIF_SENSR_SIF_DATA & I2C_SDA) == I2C_SDA) {
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

//*----------------------------------------------------------------------------
// function :MMPF_WriteCodecI2CReg
// input    : (Register address, Register data)
// output   : none
// descript : write codec register
//*----------------------------------------------------------------------------
void WriteCodecI2CReg(MMP_USHORT RegAddr, MMP_USHORT RegData)
{
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
}
//*----------------------------------------------------------------------------
// function : InitExtDac
// input    : none
// output   : none
// descript : Initial external dac
//*----------------------------------------------------------------------------
void InitExtDac(void)
{
    InitI2C();

    PRINTF("InitExtDac \r\n");

    /*Headphone*/
    WriteCodecI2CReg(WM8971_RESET,0x000); //reset
    if (m_bCodecAsMaster == MMP_FALSE) { // slave
        WriteCodecI2CReg(WM8971_AUDIO_INTERFACE,0x000);//16 bit right-justified
    }
    else {
        WriteCodecI2CReg(WM8971_AUDIO_INTERFACE, 0x42|(3)<<2 );// master mode, I2S format, 20 bits word size
    }
    WriteCodecI2CReg(WM8971_L_OUT_MIX1,0x100);//left DAC to left mixer
    WriteCodecI2CReg(WM8971_R_OUT_MIX2,0x100);//right DAC to right mixer
}
//*----------------------------------------------------------------------------
// function : PwUpExtDac
// input    : none
// output   : none
// descript : Poweron external dac
//*----------------------------------------------------------------------------
void PwUpExtDac(void)
{
    PRINTF("PwUpExtDac \r\n");

    /*Headphone*/
    if (m_bCodecAsMaster == MMP_FALSE) { // slave
        WriteCodecI2CReg(WM8971_PWR_MGMT1, 0x1C0);//enable VREF
    }
    else {
        WriteCodecI2CReg( WM8971_PWR_MGMT1, 0x1FC);//enable VREF, power up ADC for master mode
    }
    WriteCodecI2CReg(WM8971_PWR_MGMT2,0x1E0);//power up LOUT1, ROUT2
    WriteCodecI2CReg(WM8971_ADC_DAC_CONTROL,0x000);//diable mute
}
//*----------------------------------------------------------------------------
// function : PwDownExtDac
// input    : none
// output   : none
// descript : Power down external dac
//*----------------------------------------------------------------------------
void PwDownExtDac(void)
{
    PRINTF("PwDownExtDac \r\n");

    /*Headphone*/
    WriteCodecI2CReg(WM8971_ADC_DAC_CONTROL,0x008);//Enable mute
    WriteCodecI2CReg(WM8971_PWR_MGMT2,0x0);//power down LOUT1,ROUT1
}
//*----------------------------------------------------------------------------
// function : InitExtMicIn
// input    : none
// output   : none
// descript : Initial external mic in
//*----------------------------------------------------------------------------
void InitExtMicIn(void)
{
    InitI2C();

    PRINTF("InitExtMicIn \r\n");

    /*Mic*/
    WriteCodecI2CReg(WM8971_RESET,0x000); //reset
    WriteCodecI2CReg(WM8971_AUDIO_INTERFACE,0x001);//16 bit left-justified
    WriteCodecI2CReg(WM8971_ADCR_SIGNAL_PATH,0x60);
    WriteCodecI2CReg(WM8971_L_INPUT_VOLUME,0x117);
    WriteCodecI2CReg(WM8971_R_INPUT_VOLUME,0x117);

    WriteCodecI2CReg(WM8971_L_ADC_VOLUME,0x1C3);
    WriteCodecI2CReg(WM8971_R_ADC_VOLUME,0x1C3);
}
//*----------------------------------------------------------------------------
// function : PwUpExtMicIn
// input    : none
// output   : none
// descript : Poweron external mic in
//*----------------------------------------------------------------------------
void PwUpExtMicIn(void)
{
    PRINTF("PwUpExtMicIn \r\n");

    /*Mic*/
    WriteCodecI2CReg(WM8971_PWR_MGMT1,0x0FE);
}
//*----------------------------------------------------------------------------
// function : PwDownExtMicIn
// input    : none
// output   : none
// descript : Power down external mic in
//*----------------------------------------------------------------------------
void PwDownExtMicIn(void)
{
    PRINTF("PwDownExtMicIn \r\n");

    /*Mic*/
    WriteCodecI2CReg(WM8971_PWR_MGMT1,0x000);
}
//*----------------------------------------------------------------------------
// function : InitExtLineIn
// input    : none
// output   : none
// descript : Initial external line in
//*----------------------------------------------------------------------------
void InitExtLineIn(void)
{
    InitI2C();

    PRINTF("InitExtLineIn \r\n");

    /*Line in*/
    WriteCodecI2CReg(WM8971_RESET,0x000); //reset
    if (m_bCodecAsMaster == MMP_FALSE) { // slave
        WriteCodecI2CReg(WM8971_AUDIO_INTERFACE,0x001);//16 bit left-justified
    }
    else {
        WriteCodecI2CReg(WM8971_AUDIO_INTERFACE,0x041);
        WriteCodecI2CReg(WM8971_SAMPLE_RATE,0x100);
    }    
    WriteCodecI2CReg(WM8971_L_INPUT_VOLUME,0x128);
    WriteCodecI2CReg(WM8971_R_INPUT_VOLUME,0x128);

    WriteCodecI2CReg(WM8971_L_ADC_VOLUME,0x1C3);
    WriteCodecI2CReg(WM8971_R_ADC_VOLUME,0x1C3);
}
//*----------------------------------------------------------------------------
// function : PwUpExtLineIn
// input    : none
// output   : none
// descript : Poweron external line in
//*----------------------------------------------------------------------------
void PwUpExtLineIn(void)
{
    PRINTF("PwUpExtLineIn \r\n");

    /*Line in*/
    if (m_bCodecAsMaster == MMP_FALSE) { // slave
        WriteCodecI2CReg(WM8971_PWR_MGMT1,0x0FE);
    }
    else {
        WriteCodecI2CReg( WM8971_PWR_MGMT1, 0x1FC );
        WriteCodecI2CReg(WM8971_PWR_MGMT2,0x1E0);//power up LOUT1, ROUT2
        WriteCodecI2CReg(WM8971_ADC_DAC_CONTROL,0x000);//diable mute
    }
}
//*----------------------------------------------------------------------------
// function : PwDownExtLineIn
// input    : none
// output   : none
// descript : Power down external line in
//*----------------------------------------------------------------------------
void PwDownExtLineIn(void)
{
    PRINTF("PwDownExtLineIn \r\n");

    /*Line in*/
    WriteCodecI2CReg(WM8971_PWR_MGMT1,0x000);
}
//*----------------------------------------------------------------------------
// function : InitExtLineInDac
// input    : none
// output   : none
// descript : Initial external dac and line in
//*----------------------------------------------------------------------------
void InitExtLineInDac(void)
{
    InitI2C();

    PRINTF("InitExtLineInDac \r\n");

    WriteCodecI2CReg(WM8971_RESET,0x000); //reset
    WriteCodecI2CReg(WM8971_AUDIO_INTERFACE,0x001);
    WriteCodecI2CReg(WM8971_L_INPUT_VOLUME,0x128);
    WriteCodecI2CReg(WM8971_R_INPUT_VOLUME,0x128);

    WriteCodecI2CReg(WM8971_L_ADC_VOLUME,0x1C3);
    WriteCodecI2CReg(WM8971_R_ADC_VOLUME,0x1C3);

    WriteCodecI2CReg(WM8971_L_OUT_MIX1,0x100);//left DAC to left mixer
    WriteCodecI2CReg(WM8971_R_OUT_MIX2,0x100);//right DAC to right mixer
}
//*----------------------------------------------------------------------------
// function : PwupExtLineInDac
// input    : none
// output   : none
// descript : Power up external dac and line in
//*----------------------------------------------------------------------------
void PwUpExtLineInDac(void)
{
    WriteCodecI2CReg(WM8971_PWR_MGMT1, 0x1FE); 
    WriteCodecI2CReg(WM8971_PWR_MGMT2, 0x1E0);
    WriteCodecI2CReg(WM8971_ADC_DAC_CONTROL, 0x000); //diable mute
}

/** @brief Inhouse Wolfson audio CODEC initializer.

See @ref AudioInitializer for more information.
*/
MMP_BOOL audioInitializer(MMP_USHORT cmd)
{
    if (cmd & AUDIO_INIT_LINEIN) {
        InitExtLineIn();
        PwUpExtLineIn();
    }
    if (cmd & AUDIO_INIT_MICIN) {
        InitExtMicIn();
        PwUpExtMicIn();
    }
    if (cmd & AUDIO_INIT_OUT) {
    	InitExtDac();
    	PwUpExtDac();
    }
    if (cmd & AUDIO_INIT_OUT_LINEIN) {
        InitExtLineInDac();
        PwUpExtLineInDac();
    }

    return MMP_TRUE;
}

MMP_ULONG MMPC_AudioExtCodec_GetMClkFs(MMP_ULONG ulSamplerate)
{	
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
    if (m_bCodecInitialized == MMP_TRUE) {
        //reset codec path
        switch (m_ulCodecPath) {
        case AUDIO_EXT_HP_OUT:
            audioInitializer(AUDIO_INIT_OUT);
            break;
        case AUDIO_EXT_MIC_IN:
            audioInitializer(AUDIO_INIT_MICIN);
            break;
        case AUDIO_EXT_AUX_IN:
            audioInitializer(AUDIO_INIT_LINEIN);
            break;
        case AUDIO_EXT_AUX_BYPASS_HP:
            audioInitializer(AUDIO_INIT_OUT_LINEIN);
            break;
        default:
            return MMP_AUDIO_ERR_PARAMETER;
            break;
        }
    }
    m_ulCodecPath = path;

    return MMP_ERR_NONE;
}

//*----------------------------------------------------------------------------
// function : MMPC_AudioExtCodec_Init
// input    : samplerate: Sample rate
//            bSetAsMaster: Set codec as master mode or slave mode
// output   : none
// descript : Initialize and power up codec according to path settings,
//            be careful, please call MMPC_AudioExtCodec_SetPath first to set path
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

    switch (m_ulCodecPath) {
    case AUDIO_EXT_HP_OUT:
        audioInitializer(AUDIO_INIT_OUT);
        break;
    case AUDIO_EXT_MIC_IN:
        audioInitializer(AUDIO_INIT_MICIN);
        break;
    case AUDIO_EXT_AUX_IN:
        audioInitializer(AUDIO_INIT_LINEIN);
        break;
    case AUDIO_EXT_AUX_BYPASS_HP:
        audioInitializer(AUDIO_INIT_OUT_LINEIN);
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
            PwDownExtDac();
            PwDownExtLineIn();
            break;
        default:
            return MMP_AUDIO_ERR_PARAMETER;
            break;
        }
        m_bCodecInitialized = MMP_FALSE;
        //m_ulCodecPath = MMPF_AUDIO_EXT_PATH_MAX;
    }

    return MMP_ERR_NONE;
}
#endif
