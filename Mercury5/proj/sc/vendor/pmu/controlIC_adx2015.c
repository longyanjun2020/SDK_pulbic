#include "config_fw.h"
#include "controlIC_reg_ADX2015.h"
#include "controlIC_ADX2015.h"
#include "lib_retina.h"
#include "mmpf_i2cm.h"
#include "mmpf_rtc.h"
#include "os_wrap.h"
#include "mmpf_pio.h"
#include "mmpf_timer.h"

#define USE_ADC_SEMI (1)

#if defined(ALL_FW)
#define USE_ADX2015_SEMI (0)
#else
#define USE_ADX2015_SEMI (0)
#endif

#define APPLY_OTP		 (0)

#if (ADX2015_EN)

static const ADX2015_SEL_TABLE adx2015_bksel_table[] = {
    {0x00,  800,    50},
    {0x08,  1200,   25},
    {0x10,  1400,   50},
    {0x16,  1700,   25},
    {0x1E,  1900,   50},
    {0x3E,  3500,   00}
};

static const ADX2015_SEL_TABLE adx2015_ldosel_table[] = {
    {0x00,  800,    50},
    {0x0C,  1400,   25},
    {0x14,  1600,   50},
    {0x16,  1700,   25},
    {0x1E,  1900,   50},
    {0x23,  2700,   25},
    {0x33,  3100,   50},
    {0x35,  3200,   25},
    {0x3D,  3400,   50},
    {0x3E,  3500,   00}
};

#define DEFAULT_DC_DC1_VOLTAGE      0x0A        // 1.25V    => 1.4V, Core power
#define DEFAULT_DC_DC2_VOLTAGE      0x1A        // 1.8V     => DDR, Sensor DOVDD
#define DEFAULT_DC_DC3_VOLTAGE      0x3A        // 3.3V

#define DEFAULT_LDO1_VOLTAGE        0x27        // 2.8      => 3.3V Sensor AVDD
#define DEFAULT_LDO2_VOLTAGE        0x08        // 1.2      => 3.3V Backlight
#define DEFAULT_LDO3_VOLTAGE        0x27        // 2.8      => MIC 

#define DCDC_OPT_TABLE              0x03
#define LDO_OPT_TABLE               0x06

//#define ENABLE_PMU_INT_TIMER

#define ADX2015_ADC_VOLTAGE         ADC_REFERENCE_VOLTAGE

//Attention: Please note the SLAVE_ADDR is different among software and HW I2CM
//HW I2CM
MMP_I2CM_ATTR gI2cmAttribute_ADX2015 = {
	MMP_I2CM2,			//i2cmID
	ADX2015_SLAVE_ADDR, //ubSlaveAddr
	8, 					//ubRegLen
	8, 					//ubDataLen
	0x2, 				//ubDelayTime
	MMP_FALSE, 			//bDelayWaitEn
	MMP_FALSE, 			//bInputFilterEn
	MMP_FALSE, 			//b10BitModeEn
	MMP_FALSE, 			//bClkStretchEn
	0, 					//ubSlaveAddr1
	0, 					//ubDelayCycle
	4, 					//ubPadNum
	250000 /*250KHZ*/, 	//ulI2cmSpeed
#if !defined(MBOOT_FW)
	MMP_TRUE, 			//bOsProtectEn
#else
	MMP_FALSE,			//bOsProtectEn
#endif	
	NULL, 				//sw_clk_pin
	NULL, 				//sw_data_pin
	MMP_FALSE,			//bRfclModeEn 
	MMP_FALSE,			//bWfclModeEn
	MMP_FALSE,			//bRepeatModeEn
	0                   //ubVifPioMdlId
};

volatile MMP_BOOL m_alarmUse_A = MMP_FALSE, m_alarmUse_B = MMP_FALSE;
#pragma arm section code, rodata, rwdata, zidata
     
static MMPF_OS_SEMID    m_RtcAlamSemID;
#if (USE_ADC_SEMI)
static MMPF_OS_SEMID    m_ADCSemID;
#endif
#if (USE_ADX2015_SEMI)
static MMPF_OS_SEMID    m_ADX2015SemID;
#endif
static RTC_CallBackFunc *(m_RtcCallBack[ADX2015_ALARM_MAX - 1]);
#ifdef ENABLE_PMU_INT_TIMER
static MMP_USHORT   m_usTimerID[MMPF_OS_TMRID_MAX];
static MMP_USHORT   m_usTimerReadIndex = 0, m_usTimerWriteIndex = 0;
#endif
//static MMP_ULONG m_glADX2015AccessTime = 0x20;		//unit: ms
static MMP_BOOL     m_bADX2015 = MMP_FALSE;
//static MMP_ULONG m_glADX2015CleanWdtTime = 3000;  //Timer interval to clean ADX2015 watch-dog , unit: ms

MMP_USHORT glADX2015IntStatus = 0;
static ADX2015_IR_DATA m_ir_data = {0};

#if defined(MBOOT_FW)
static MMP_BOOL m_bBootTimeOut = MMP_FALSE;
#endif  

#if defined(MBOOT_FW) || defined(UPDATER_FW) 
#define printc(x, ...)
#else
extern void printc( char* szFormat, ... );
#endif

//------------------------------------------------------------------------------
//  Function    : ADX2015_BKXSEL_To_Voltage
//  Description : 
//------------------------------------------------------------------------------
MMP_USHORT ADX2015_BKXSEL_To_Voltage(MMP_USHORT regSetting)
{
    MMP_BYTE index;
    MMP_USHORT output;
    
    if (regSetting > 0x3E) regSetting = 0x3E;

    for (index = 0; index < sizeof(adx2015_bksel_table) / sizeof(ADX2015_SEL_TABLE); index++) {
        if (adx2015_bksel_table[index].bkxsel == regSetting) {
            return adx2015_bksel_table[index].output;
        }
        else if (adx2015_bksel_table[index].bkxsel > regSetting) {
            index--;
            output = adx2015_bksel_table[index].output + \
                     adx2015_bksel_table[index].offset * (regSetting - adx2015_bksel_table[index].bkxsel);
                     
            return output;
        }
    }

	RTNA_DBG_Str0("\r\n--E-- ADX2015_BKXSEL_To_Voltage: Out of range !!!\r\n");

    return 0;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_BKXSEL_To_Voltage
//  Description : 
//------------------------------------------------------------------------------
MMP_UBYTE ADX2015_Voltage_To_BKXSEL(MMP_USHORT voltage)
{
    MMP_UBYTE index, regSetting;

    if (voltage > 3500) voltage = 3500;

    for (index = 0; index < sizeof(adx2015_bksel_table) / sizeof(ADX2015_SEL_TABLE); index++) {
        if (adx2015_bksel_table[index].output == voltage) {
            return adx2015_bksel_table[index].bkxsel;
        }
        else if (adx2015_bksel_table[index].output > voltage) {
            index--;
            regSetting = adx2015_bksel_table[index].bkxsel + \
                         (voltage - adx2015_bksel_table[index].output) / adx2015_bksel_table[index].offset;

            return regSetting;
        }
    }

	RTNA_DBG_Str0("\r\n--E-- ADX2015_Voltage_To_BKXSEL: Out of range !!!\r\n");

    return 0;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_LDOXSEL_To_Voltage
//  Description : 
//------------------------------------------------------------------------------
MMP_USHORT ADX2015_LDOXSEL_To_Voltage(MMP_USHORT regSetting)
{
    MMP_BYTE index;
    MMP_USHORT output;
    
    if (regSetting > 0x3E) regSetting = 0x3E;

    for (index = 0; index < sizeof(adx2015_ldosel_table) / sizeof(ADX2015_SEL_TABLE); index++) {
        if (adx2015_ldosel_table[index].bkxsel == regSetting) {
            return adx2015_ldosel_table[index].output;
        }
        else if (adx2015_ldosel_table[index].bkxsel > regSetting) {
            index--;
            output = adx2015_ldosel_table[index].output + \
                     adx2015_ldosel_table[index].offset * (regSetting - adx2015_ldosel_table[index].bkxsel);
                     
            return output;
        }
    }

	RTNA_DBG_Str0("\r\n--E-- ADX2015_LDOXSEL_To_Voltage: Out of range !!!\r\n");

    return 0;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Voltage_To_LDOXSEL
//  Description : 
//------------------------------------------------------------------------------
MMP_UBYTE ADX2015_Voltage_To_LDOXSEL(MMP_USHORT voltage)
{
    MMP_UBYTE index, regSetting;

    if (voltage > 3500) voltage = 3500;

    for (index = 0; index < sizeof(adx2015_ldosel_table) / sizeof(ADX2015_SEL_TABLE); index++) {
        if (adx2015_ldosel_table[index].output == voltage) {
            return adx2015_ldosel_table[index].bkxsel;
        }
        else if (adx2015_ldosel_table[index].output > voltage) {
            index--;
            regSetting = adx2015_ldosel_table[index].bkxsel + \
                         (voltage - adx2015_ldosel_table[index].output) / adx2015_ldosel_table[index].offset;
                     
            return regSetting;
        }
    }

	RTNA_DBG_Str0("\r\n--E-- ADX2015_Voltage_To_LDOXSEL: Out of range !!!\r\n");

    return 0;
}

#if defined(ALL_FW)
//------------------------------------------------------------------------------
//  Function    : adx2015_int_cb_ptr
//  Description : 
//------------------------------------------------------------------------------
static ADX2015_INT_CB_PTR adx2015_int_cb_ptr = (ADX2015_INT_CB_PTR) NULL;

void ADX2015_INT_CB_Func_Register(void *func_ptr)
{
    adx2015_int_cb_ptr = (ADX2015_INT_CB_PTR) func_ptr;
}
#endif

#ifdef ENABLE_PMU_INT_TIMER
//------------------------------------------------------------------------------
//  Function    : ADX2015_Timer_TaskMode
//  Description : 
//------------------------------------------------------------------------------
static void ADX2015_Timer_TaskMode(void)
{
	if(MMPF_OS_StopTimer(m_usTimerID[m_usTimerReadIndex], OS_TMR_OPT_NONE) != 0) {
		RTNA_DBG_Str0("ADX2015 Stop OS Timer error !!\r\n");
	}
	m_usTimerID[m_usTimerReadIndex] = OS_TMR_OPT_NONE; //clean the timer id by writing one invalidate ID.
	m_usTimerReadIndex = ((m_usTimerReadIndex + 1) % MMPF_OS_TMRID_MAX);	
}


//------------------------------------------------------------------------------
//  Function    : ADX2015_IsrTimerCallBack
//  Description : 
//------------------------------------------------------------------------------
static void ADX2015_IsrTimerCallBack(OS_TMR *ptmr, void *p_arg)
{
	ADX2015_Timer_TaskMode();
}
#endif

//#if ((ADX2015_EN)&&(ADX2015_WDT_EN == 0x1))
extern MMPF_OS_MQID  	LowTaskWork_QId;

//------------------------------------------------------------------------------
//  Function    : ADX2015_read_reg
//  Description : This function is used for reading PMU chip's registers.
//------------------------------------------------------------------------------
/** @brief This function is used for reading PMU chip's registers.
@param[in] 	regNAME is main register.
@param[out] returnValue is the value get from the register.
@return 	It reports the status of the operation.
*/
MMP_ERR ADX2015_read_reg(ADX2015_REG regNAME, MMP_USHORT *returnValue) 
{
    return MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, regNAME, returnValue);
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_write_reg
//  Description : This function is used for writing PMU chip's registers.
//------------------------------------------------------------------------------
/** @brief This function is used for writing PMU chip's registers.
@param[in] 	regNAME is main register.
@param[out] nValue is the value set the register.
@return 	It reports the status of the operation.
*/
MMP_ERR ADX2015_write_reg(ADX2015_REG regNAME, MMP_UBYTE nValue) 
{
    return MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, (MMP_USHORT) regNAME, (MMP_USHORT) nValue);
}


//------------------------------------------------------------------------------
//  Function    : ADX2015_WDT_CleanStatus
//  Description :
//------------------------------------------------------------------------------
/** @brief The function is used to kick Watch dog one time.

The function is used to kick Watch dog one time.
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_WDT_CleanStatus(void) {
	MMP_USHORT regVal;
	
	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, (MMP_USHORT) ADX2015_WDT_CTL, &regVal);
	return MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, (MMP_USHORT) ADX2015_WDT_CTL, regVal | 0x20);
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_WDT_Reset
//  Description :
//------------------------------------------------------------------------------
/** @brief The function is used to reset watch dog counter.

The function is used to reset watch dog counter.
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_WDT_Reset(void) {
	MMP_ERR status = MMP_ERR_NONE;
	
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_WDT_CTL, 0x04);
	MMPF_OS_Sleep(1000);
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_WDT_CTL, 0x84);
	if(status != MMP_ERR_NONE) {
		return MMP_SYSTEM_ERR_PMU;
	}
	
	return MMP_ERR_NONE; 
}
/*static void ADX2015_WDT_TimerCallBack(OS_TMR *ptmr, void *p_arg)
{
	MMPF_OS_PutMessage(LowTaskWork_QId, (void *)(&ADX2015_WDT_CleanStatus));
}*/


//------------------------------------------------------------------------------
//  Function    : ADX2015_WDT_Reset
//  Description :
//------------------------------------------------------------------------------
/** @brief The function is used to enable/disable ADX2015 watch dog.

The function is used to enable/disable ADX2015 watch dog.
@param[in] bEnable : enable/diable watch dog.
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_WDT_Enable(MMP_BOOL bEnable) {
	MMP_ERR status = MMP_ERR_NONE;
	MMP_USHORT value = 0;
	
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_WDT_CTL, &value);
	RTNA_DBG_Long(0, value);
	
	if(bEnable) {
		status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_WDT_CTL, (value|0x80));
	}
	else {
		status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_WDT_CTL, (value&0x7F));
	}
	
	#if 0
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_WDT_CTL, &value);
	RTNA_DBG_Long(0, value);
	#endif
	if(status != MMP_ERR_NONE) {
		return MMP_SYSTEM_ERR_PMU;
	}
	return MMP_ERR_NONE; 
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_WDT_SetTimeOut
//  Description :
//------------------------------------------------------------------------------
/** @brief The function is used to enable/disable ADX2015 watch dog.

The function is used to enable/disable ADX2015 watch dog.
@param[in] ulMilleSec : Time out seting. The unit is "ms".
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_WDT_SetTimeOut(MMP_ULONG ulMilleSec) {
	MMP_ERR status = MMP_ERR_NONE;
	MMP_USHORT value = 0;
	
	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "ADX2015_WDT_SetTimeOut.........\r\n");
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_WDT_CTL, &value);
	switch (ulMilleSec) {
		case 3000:
			status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_WDT_CTL, (value | 0x40));
			//MMPF_OS_Sleep(1000);
			break;
		case 10000:
			status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_WDT_CTL, (value & 0xB0));
			//MMPF_OS_Sleep(1000);
			break;
		default:
			RTNA_DBG_Str0("--W-- Un-supported WDT timeout\r\n");
			break;
	}

	#if 0 //debug
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_WDT_CTL, &value);
	RTNA_DBG_Long(0, value);
	#endif

	if(status != MMP_ERR_NONE) {
		return MMP_SYSTEM_ERR_PMU;
	}

	return MMP_ERR_NONE; 
}
//#endif

#if defined(MBOOT_FW)
static void ADX2015_BOOT_TimerISR(void)
{
	m_bBootTimeOut = MMP_TRUE;
}
#endif

#if ADX2015_ACT_DISCHARGE
MMP_ERR ADX2015_ActiveDischarge_En(MMP_BOOL bEnable)
{
	MMP_ERR status = MMP_ERR_NONE;
 	MMP_USHORT nRegValue = 0;

	if (bEnable == MMP_TRUE) {

		status |=MMPF_I2cm_ReadReg( &gI2cmAttribute_ADX2015, ADX2015_DCDC_1_CTL2, &nRegValue);
		nRegValue |= ADX2015_DCDC_DISEN; // enable DC-DC1 active discharge
		status |=MMPF_I2cm_WriteReg( &gI2cmAttribute_ADX2015, ADX2015_DCDC_1_CTL2, nRegValue);

		status |=MMPF_I2cm_ReadReg( &gI2cmAttribute_ADX2015, ADX2015_DCDC_2_CTL2, &nRegValue);
		nRegValue |= ADX2015_DCDC_DISEN; // enable DC-DC2 active discharge
		status |=MMPF_I2cm_WriteReg( &gI2cmAttribute_ADX2015, ADX2015_DCDC_2_CTL2, nRegValue);

		status |=MMPF_I2cm_ReadReg( &gI2cmAttribute_ADX2015, ADX2015_LDO_DISCHARGE_EN, &nRegValue);
		nRegValue |= 0x0F; // enable LDO1-4 active discharge
		status |=MMPF_I2cm_WriteReg( &gI2cmAttribute_ADX2015, ADX2015_LDO_DISCHARGE_EN, nRegValue);

	} else {

		status |=MMPF_I2cm_ReadReg( &gI2cmAttribute_ADX2015, ADX2015_DCDC_1_CTL2, &nRegValue);
		nRegValue &= (~ADX2015_DCDC_DISEN); // disable DC-DC1 active discharge
		status |=MMPF_I2cm_WriteReg( &gI2cmAttribute_ADX2015, ADX2015_DCDC_1_CTL2, nRegValue);


		status |=MMPF_I2cm_ReadReg( &gI2cmAttribute_ADX2015, ADX2015_DCDC_2_CTL2, &nRegValue);
		nRegValue &= (~ADX2015_DCDC_DISEN); // disable DC-DC2 active discharge
		status |=MMPF_I2cm_WriteReg( &gI2cmAttribute_ADX2015, ADX2015_DCDC_2_CTL2, nRegValue);

		status |=MMPF_I2cm_ReadReg( &gI2cmAttribute_ADX2015, ADX2015_LDO_DISCHARGE_EN, &nRegValue);
		nRegValue &= (~0x0F); // disable LDO1-4 active discharge
		status |=MMPF_I2cm_WriteReg( &gI2cmAttribute_ADX2015, ADX2015_LDO_DISCHARGE_EN, nRegValue);

	}

	return status;
}
#endif

//------------------------------------------------------------------------------
//  Function    : ADX2015_PowerOff
//  Description :
//------------------------------------------------------------------------------
/** @brief The function is used to power off PMU.

The function is used to power off PMU.
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_PowerOff(void)
{
	MMP_ERR		status = MMP_ERR_NONE;
	MMP_USHORT	rb03, rb04;

#if (USE_ADX2015_SEMI)
    if(MMPF_OS_AcquireSem(m_ADX2015SemID, 0)) {
		RTNA_DBG_Str0("--E-- m_ADX2015SemID OSSemPost: Fail!! \r\n");
		return 1;//error
	}
#endif

    RTNA_DBG_Str(0, "ADX2015_PowerOff -\r\n");
    RTNA_WAIT_MS(200);
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, 0x7F);
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTB_STATUS, 0xFF);

	//Enable auto discharge
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_VDD_CTRL, &rb03);
	rb03 |= 0x0080;
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_PWR_ONOFF_SEQ_CTRL, &rb04);
	rb04 &= 0x007F;
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_VDD_CTRL, rb03);
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_PWR_ONOFF_SEQ_CTRL, rb04);

    while(1){
        RTNA_WAIT_MS(100);
        RTNA_DBG_Str0("--E-- ADX2015_PowerOff fail.\r\n");
    	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_VDD_CTRL, rb03);
    	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_PWR_ONOFF_SEQ_CTRL, rb04);
    }

#if (USE_ADX2015_SEMI)
    MMPF_OS_ReleaseSem(m_ADX2015SemID);
#endif
	
	if(status != MMP_ERR_NONE) {
		return MMP_SYSTEM_ERR_PMU;
	}

	return status;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_EnableLDO
//  Description :
//------------------------------------------------------------------------------
/** @brief The function is used to turn on/off PMU LDO.

The function is used to turn on/off PMU LDO.
@param[in] ADX2015_LDO_ID is the specific ID number.
@param[in] bEnable : MMP_TRUE to turn on and MMP_FALSE to turn off
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_EnableLDO(ADX2015_LDO_ID ldoID, MMP_BOOL bEnable)
{
	MMP_ERR status = MMP_ERR_NONE;
	MMP_USHORT usValue = 0;
	
	if (ADX2015_LDO_MAX <= ldoID)
	    return MMP_SYSTEM_ERR_PMU;
	    
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, (ADX2015_LDO_1_CTL + ldoID), &usValue);
	if (bEnable) {
		usValue |= 0x80;  
	}
	else {
		usValue &= 0x7F;
	}
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, (ADX2015_LDO_1_CTL + ldoID), usValue);
	
	if(status != MMP_ERR_NONE) {
		return MMP_SYSTEM_ERR_PMU;
	}
	return status;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_EnableDCDC
//  Description :
//------------------------------------------------------------------------------
/** @brief The function is used to turn on/off PMU DCDC.

The function is used to turn on/off PMU DCDC.
@param[in] ADX2015_DCDC_ID is the specific ID number.
@param[in] bEnable : MMP_TRUE to turn on and MMP_FALSE to turn off
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_EnableDCDC(ADX2015_DCDC_ID dcdcID, MMP_BOOL bEnable)
{
	MMP_ERR status = MMP_ERR_NONE;
	MMP_USHORT usValue = 0;
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, (ADX2015_DCDC_1_CTL2 + dcdcID*ADX2015_DCDC_REG_SIZE), &usValue);
	
	if (bEnable) {
		usValue |= 0x40;  
	}
	else {
		usValue &= ~(0x40);  
	}
	
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, (ADX2015_DCDC_1_CTL2 + dcdcID*ADX2015_DCDC_REG_SIZE), usValue);
	if(status != MMP_ERR_NONE) {
		return MMP_SYSTEM_ERR_PMU;
	}
	return status;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_CheckBootComplete
//  Description :
//------------------------------------------------------------------------------
/** @brief The function is used to check if system can initialize normally or not.

The function is used to check if system can initialize normally or not.
@param[in] ulMilliSecond : the time interval to check user press the power-key or not.
@param[in] pio_power_key : the PIO number, please reference the data structure of MMP_GPIO_PIN
@return It reports the status of the operation.
*/

MMP_ERR ADX2015_CheckBootComplete(MMP_ULONG ulMilliSecond, MMP_GPIO_PIN pio_power_key) {
	MMP_ERR status = MMP_ERR_NONE;
	
	#if defined(MBOOT_FW)
	MMP_USHORT value = 0x0;
	MMP_UBYTE ubPowerKeyStatus = 0x1;
	MMPF_TIMER_ATTR TimerAttribute;
	
	#if (ADX2015_WDT_EN == 0x1)
	ADX2015_WDT_Enable(MMP_FALSE);
	#endif

	if((glADX2015IntStatus & (ADX2015_INT_EVENT_PWRK_PRESS || ADX2015_INT_EVENT_PWRK2_PRESS)) != 0) {
		
		status |= MMPF_PIO_EnableOutputMode(pio_power_key, MMP_FALSE, MMP_TRUE);

    	TimerAttribute.TimePrecision = MMPF_TIMER_MILLI_SEC;
    	TimerAttribute.ulTimeUnits   = ulMilliSecond;
    	TimerAttribute.Func          = ADX2015_BOOT_TimerISR;
    	TimerAttribute.bIntMode      = MMPF_TIMER_PERIODIC;
    	status |= MMPF_Timer_Start(MMPF_TIMER_1, &TimerAttribute);

		while((!m_bBootTimeOut)&&(ubPowerKeyStatus == 1)) {
			status |= MMPF_PIO_GetData(pio_power_key, &ubPowerKeyStatus);
		}
		
		MMPF_Timer_Stop(MMPF_TIMER_1);

		if (ubPowerKeyStatus) {
			RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\nBoot Success!!\r\n");
		}
		else {
			RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\nBoot fail !!\r\n");
			
			//Power turn-off
			status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_POWERON_CTL, 0x83);
			status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_VDD_CTRL, 0x00);
		}
		
		//Note: In MBOOT_FW, we should not clean the status, because customer may ask power-on status in ALL_FW
	}
	else {
		#if defined(MBOOT_FW)
		//Turn-off Discharge
		status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, 0x85, 0x0);
			
		MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, 0x12, &value);
		status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, 0x12, (value & 0x7F));
		value = 0x0;
		MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, 0x0C, &value);
		status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, 0x0C, (value & 0x7F));
		value = 0x0;
		MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, 0x06, &value);
		status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, 0x06, (value & 0x7F));
		#endif
	
	}
	if(status != MMP_ERR_NONE) {
		return MMP_SYSTEM_ERR_PMU;
	}
	#endif //#if defined(MBOOT_FW)
	return status;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_GetBootStatus
//  Description :
//------------------------------------------------------------------------------
/** @brief The function is used to send back the boot-up events

The function is used to send back the boot-up events.
@param[out] usRetStatus : the bit 0 stands for ADX2015_INT_EVENT_WAKE, and bit 4 stands for ADX2015_INT_EVENT_POWERK...etc., please refer ADX2015_INT_EVENT
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_GetBootStatus(MMP_USHORT * usRetStatus)
{
	*usRetStatus = glADX2015IntStatus;
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_RTC_Initialize
//  Description :
//------------------------------------------------------------------------------
/** @brief The function is used to intial RTC driver
The function is used to intial RTC driver.
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_RTC_Initialize(void)
{
	static MMP_BOOL bRtcInitFlag = MMP_FALSE;
	MMP_ERR status = MMP_ERR_NONE;
	MMP_ULONG i = 0;
	if (bRtcInitFlag == MMP_FALSE) {
		m_RtcAlamSemID =  MMPF_OS_CreateSem(1);
		status |= MMPF_PIO_Initialize();
		for (i = 0; i < (ADX2015_ALARM_MAX - 1); i++) {
			m_RtcCallBack[i] = NULL;
		}
		bRtcInitFlag = MMP_TRUE;
	}
	
	if(status != MMP_ERR_NONE) {
		return MMP_SYSTEM_ERR_PMU;
	}
	return status;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_RTC_CheckTimeFormat
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used for checking the validation of Time format.

This function is used for checking the validation of Time format.
@param[in] pointer of structure AUTL_DATETIME.
@return It reports the status of the operation.
*/
static MMP_ERR ADX2015_RTC_CheckTimeFormat(AUTL_DATETIME *ptr)
{
	MMP_ULONG ulDates[13]={0,31,0,31,30,31,30,31,31,30,31,30,31};
	if ((ptr->usYear < ADX2015_RTC_START_YEAR) || (ptr->usYear > ADX2015_RTC_MAX_YEAR)) {
		RTNA_DBG_Str(ADX2015_RTC_DEBUG_LEVEL, "Time Year\r\n");
		return MMP_SYSTEM_ERR_FORMAT;
	}
	
	if (((ptr->usYear%4 == 0)&&(ptr->usYear%100 != 0)) || (ptr->usYear%400 == 0)) {
		ulDates[2] = 29;	
	}
	else {
		ulDates[2] = 28;	
	}
	
	if((ptr->usMonth > 12) || (ptr->usMonth == 0) || (ptr->usDay > ulDates[ptr->usMonth]) || (ptr->usDay == 0)) {
		RTNA_DBG_Str(ADX2015_RTC_DEBUG_LEVEL, "Time Month date\r\n");
		return MMP_SYSTEM_ERR_FORMAT;
	}
	
	
	if((ptr->usHour > 23) || (ptr->usMinute > 59) || (ptr->usSecond > 59)) {
		RTNA_DBG_Str(ADX2015_RTC_DEBUG_LEVEL, "Time Month ubHour Minute Second\r\n");
		return MMP_SYSTEM_ERR_FORMAT;
	}
	
	if((ptr->b_12FormatEn == MMP_TRUE)&&(ptr->usHour > 12)) {
		RTNA_DBG_Str(ADX2015_RTC_DEBUG_LEVEL, "Time 12 Hours\r\n");
		return MMP_SYSTEM_ERR_FORMAT;
	}
	
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_RTC_GetTime
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used for getting RTC information in ADX2015.

This function is used for getting RTC information in ADX2015.
@param[in] pointer of structure AUTL_DATETIME.
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_RTC_GetTime(AUTL_DATETIME *ptr)
{
	MMP_USHORT value = 0;
	MMP_ERR	status = MMP_ERR_NONE;
	
#if (USE_ADX2015_SEMI)
    if(MMPF_OS_AcquireSem(m_ADX2015SemID, 0)) {
		RTNA_DBG_Str0("--E-- m_ADX2015SemID OSSemPost: Fail!! \r\n");
		return 1;//error
	}
#endif
	
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_DAY, &value);
	ptr->usDayInWeek = value & 0x7;
	 
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_YEAR, &value);
	ptr->usYear = (value >> 4)*10 + (value & ADX2015_RTC_LMASK) + ADX2015_RTC_START_YEAR;
	
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_MON, &value);
	ptr->usMonth = ((value & 0x10) >> 4)*10 +  (value & ADX2015_RTC_LMASK);
	
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_DATE, &value);
	ptr->usDay = ((value & 0x30) >> 4)*10 +  (value & ADX2015_RTC_LMASK);
	
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_HOUR, &value);
	if (value & 0x80) {  //12-hour format
		ptr->usHour = (((value & 0x10) >> 4)*10 + (value & ADX2015_RTC_LMASK))%12;
		if(value & 0x20) { //Check if the time at P.M.
			ptr->ubAmOrPm = 0x1;
		}
	}
	else {	//24-hour format
		ptr->usHour = ((value & 0x30) >> 4)*10 + (value & ADX2015_RTC_LMASK);
	}
	
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_MIN, &value);
	ptr->usMinute = ((value & 0x70) >> 4)*10 +  (value & ADX2015_RTC_LMASK);
	
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_SEC, &value);
	ptr->usSecond = ((value & 0x70) >> 4)*10 +  (value & ADX2015_RTC_LMASK);
	
	RTNA_DBG_Str(ADX2015_RTC_DEBUG_LEVEL, "\r\n---------Read Time---------\r\n");
	RTNA_DBG_Long(ADX2015_RTC_DEBUG_LEVEL, ptr->usYear);
	RTNA_DBG_Long(ADX2015_RTC_DEBUG_LEVEL, ptr->usMonth);
	RTNA_DBG_Long(ADX2015_RTC_DEBUG_LEVEL, ptr->usDay);

	if(ptr->ubAmOrPm == 0x1) {
		RTNA_DBG_Str(ADX2015_RTC_DEBUG_LEVEL, "PM :");
	}
	else {
		RTNA_DBG_Str(ADX2015_RTC_DEBUG_LEVEL, "AM :");
	}

	RTNA_DBG_Long(ADX2015_RTC_DEBUG_LEVEL, ptr->usHour);
	RTNA_DBG_Long(ADX2015_RTC_DEBUG_LEVEL, ptr->usMinute);
	RTNA_DBG_Long(ADX2015_RTC_DEBUG_LEVEL, ptr->usSecond);
	RTNA_DBG_Str(ADX2015_RTC_DEBUG_LEVEL, "\r\n");
	
#if (USE_ADX2015_SEMI)
    MMPF_OS_ReleaseSem(m_ADX2015SemID);
#endif
	
	if(status != MMP_ERR_NONE) {
		return MMP_SYSTEM_ERR_PMU;
	}
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_RTC_SetTime
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used for setting time information to RTC in ADX2015.

This function is used for setting time information to RTC in ADX2015.
@param[in] pointer of structure AUTL_DATETIME.
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_RTC_SetTime(AUTL_DATETIME *ptr)
{
	MMP_ERR status;
	MMP_USHORT value = 0;
	status = ADX2015_RTC_CheckTimeFormat(ptr);
	if ( status != MMP_ERR_NONE) {
		return status;
	}
	
#if (USE_ADX2015_SEMI)
    if(MMPF_OS_AcquireSem(m_ADX2015SemID, 0)) {
		RTNA_DBG_Str0("--E-- m_ADX2015SemID OSSemPost: Fail!! \r\n");
		return 1;//error
	}
#endif
	
	value =  (((ptr->usYear - ADX2015_RTC_START_YEAR)/10) << 4)  + ((ptr->usYear - ADX2015_RTC_START_YEAR)%10);
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_YEAR, value);
	
	value = (((ptr->usMonth/10) << 4)&0x10) + (ptr->usMonth%10);
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_MON, value);
	
	value = (((ptr->usDay/10) << 4)&0x30) + (ptr->usDay%10);
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_DATE, value);
	
	if (ptr->usHour >= 10) {
		value = ((ptr->usHour/10) << 4) + (ptr->usHour % 10);
	}
	else {
		value = ptr->usHour;
	}
	
	if (ptr->b_12FormatEn == MMP_TRUE) {
		value = 0x80 | value;
		if(ptr->ubAmOrPm == 0x1) {//set as P.M.
			value = 0x20 | value;
		}
	}
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_HOUR, value);
	
	value = (((ptr->usMinute/10) << 4)&0x70) + (ptr->usMinute%10);
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_MIN, value);
	
	value = (((ptr->usSecond/10) << 4)&0x70) + (ptr->usSecond%10);
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_SEC, value);
	
	RTNA_DBG_Str(ADX2015_RTC_DEBUG_LEVEL, "---------Set Time---------\r\n\r\n");
	RTNA_DBG_Long(ADX2015_RTC_DEBUG_LEVEL, ptr->usYear);
	RTNA_DBG_Long(ADX2015_RTC_DEBUG_LEVEL, ptr->usMonth);
	RTNA_DBG_Long(ADX2015_RTC_DEBUG_LEVEL, ptr->usDay);
	RTNA_DBG_Long(ADX2015_RTC_DEBUG_LEVEL, ptr->usHour);
	RTNA_DBG_Long(ADX2015_RTC_DEBUG_LEVEL, ptr->usMinute);
	RTNA_DBG_Long(ADX2015_RTC_DEBUG_LEVEL, ptr->usSecond);
	RTNA_DBG_Long(ADX2015_RTC_DEBUG_LEVEL, ptr->usDayInWeek);
	
#if (USE_ADX2015_SEMI)
    MMPF_OS_ReleaseSem(m_ADX2015SemID);
#endif
	
	if(status != MMP_ERR_NONE) {
		return MMP_SYSTEM_ERR_PMU;
	}
	return status;
}


//------------------------------------------------------------------------------
//  Function    : ADX2015_RTC_AlarmCheckID
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used for check which alarm happens when we turn on 2 alarms.

This function is used for check which alarm happens when we turn on 2 alarms.
@param[out] alarm_id : the alarm ID which alarm expires.
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_RTC_AlarmCheckID(ADX2015_ALARM_ID* alarm_id)
{
	AUTL_DATETIME current_time, alarm_time;
	MMP_ERR status = MMP_ERR_NONE;
	status |= ADX2015_RTC_GetTime(&current_time);
	
	//Read Alarm1 settings first
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM1_H, (MMP_USHORT*)&(alarm_time.usHour));
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM1_DATE, (MMP_USHORT*)&(alarm_time.usDay));
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM1_M, (MMP_USHORT*)&(alarm_time.usMinute));
	
	//Because of ADX2015 alarm is "minute" level, 
	//so we assume that we can make sure that we can check alarm at "this minute"
	if((alarm_time.usDay == current_time.usDay)&&(alarm_time.usHour == current_time.usHour)&&(alarm_time.usMinute == current_time.usMinute)) {
		*alarm_id = ADX2015_ALARM_ID_A; 
	}
	else {
		status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM1_H, (MMP_USHORT*)&(alarm_time.usHour));
		status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM1_DATE, (MMP_USHORT*)&(alarm_time.usDay));
		status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM1_M, (MMP_USHORT*)&(alarm_time.usMinute));
		if((alarm_time.usDay == current_time.usDay)&&(alarm_time.usHour == current_time.usHour)&&(alarm_time.usMinute == current_time.usMinute)) {
			*alarm_id = ADX2015_ALARM_ID_B; 
		}
		else {
			*alarm_id = ADX2015_ALARM_ID_NONE;
		}
	}
	
	if(status != MMP_ERR_NONE) {
		return MMP_SYSTEM_ERR_PMU;
	}
	return status;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_RTC_SetAlarmEnable
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used to enable RTC alarm.

This function is used to enable RTC alarm.
@param[in] alarm_id : select which alarm to operate.
@param[in] bEnable : turn on or turn off.
@param[in] ptr : alarm time settings.
@param[in] p_callback : call-back function when alarm time expired.
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_RTC_SetAlarmEnable(ADX2015_ALARM_ID alarm_id, MMP_BOOL bEnable, AUTL_DATETIME *ptr, void* p_callback)
{
	MMP_USHORT ADX2015_value = 0;
	MMP_ULONG ulDates[13]={0,31,0,31,30,31,30,31,31,30,31,30,31};
	MMP_UBYTE ubRet = 0xFF;
	MMP_ERR status = MMP_ERR_NONE;
	
	//MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_EN, 0x1E);
	if (bEnable) {
		
		//Alarm time format checking
		if (((ptr->usYear%4 == 0)&&(ptr->usYear%100 != 0)) || (ptr->usYear%400 == 0)) {
				ulDates[2] = 29; //February days check	
		}
		else {
				ulDates[2] = 28;	//February days check
		}
		
		if((ptr->usDay > ulDates[ptr->usMonth]) || (ptr->usDay == 0)) {
			return MMP_SYSTEM_ERR_FORMAT;
		}
		
		if((ptr->usHour > 23) || (ptr->usMinute > 59)) {
			return MMP_SYSTEM_ERR_FORMAT;
		}
		if((ptr->ubAmOrPm == 0x1)&& (ptr->b_12FormatEn == 0x1)) {  //12-hours format check
			if((ptr->usHour > 12)) {
				return MMP_SYSTEM_ERR_FORMAT;
			}
		}
	
		ubRet = MMPF_OS_AcquireSem(m_RtcAlamSemID, ADX2015_SEM_TIMEOUT);
		if (alarm_id == ADX2015_ALARM_ID_A){
			if (m_alarmUse_A == MMP_FALSE) {
				ADX2015_value = (((ptr->usDay/10) << 4)&0x30) + (ptr->usDay%10);
				status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM1_DATE, ADX2015_value);
				
                status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_HOUR, &ADX2015_value);
                if (ADX2015_value & 0x80) { //RTC in 12-hour format
                    if (ptr->b_12FormatEn == 0x1) { //input in 12-hour format
                        ADX2015_value = ((ptr->usHour/10) << 4) + (ptr->usHour % 10);
                        if (ptr->ubAmOrPm == 0x1)
                            ADX2015_value |= 0x20; // PM
                    }
                    else { //input in 24-hour format
                        ADX2015_value = (ptr->usHour >= 12) ? 0x20 : 0; //set PM or AM
                        ptr->usHour = (ptr->usHour > 12) ? ptr->usHour - 12 : ptr->usHour;
                        ADX2015_value |= (((ptr->usHour/10) << 4) + (ptr->usHour % 10));
                    }
                }
				else { //RTC in 24-hour format
				    if (ptr->b_12FormatEn == 0x1) { //input in 12-hour format
				        if ((ptr->ubAmOrPm == 0x1) && (ptr->usHour != 12))
				            ptr->usHour += 12;
                    }
                    ADX2015_value = ((ptr->usHour/10) << 4) + (ptr->usHour % 10);
                }
				status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM1_H, ADX2015_value);
				
				ADX2015_value = 0;
				ADX2015_value = (((ptr->usMinute/10) << 4)&0x70) + (ptr->usMinute%10);
				status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM1_M, ADX2015_value);
				
				ADX2015_value = 0;
				//ADX2015_value = 1 << (ptr->usDay - 1);  //for ADX2015 alarm, Day and Date settings can "only" use one of them !!
				ADX2015_value |= 0x80;  //Alarm on
				
				status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM1_DAY, ADX2015_value);
				m_alarmUse_A = MMP_TRUE;
			}
			else {
				if (ubRet == 0) {
					MMPF_OS_ReleaseSem(m_RtcAlamSemID);
				}
				
				#if 0
				ADX2015_RTC_SetAlarmEnable(ADX2015_ALARM_ID_A, MMP_FALSE, NULL, NULL);
				ADX2015_RTC_SetAlarmEnable(ADX2015_ALARM_ID_A, MMP_TRUE, ptr, p_callback);
				return MMP_ERR_NONE;
				#else
				return MMP_SYSTEM_ERR_DOUBLE_SET_ALARM;
				#endif
			}
			
		}
		else if (alarm_id == ADX2015_ALARM_ID_B) {
			if(m_alarmUse_B == MMP_FALSE) {
				ADX2015_value = 0;
				ADX2015_value = (((ptr->usDay/10) << 4)&0x30) + (ptr->usDay%10);
				status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM2_DATE, ADX2015_value);
				
				ADX2015_value = 0;
				if (ptr->usHour > 10) {
					ADX2015_value = ((ptr->usHour/10) << 4) + (ptr->usHour % 10);
				}
				else {
					ADX2015_value = ptr->usHour;
				}
				status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_HOUR, &ADX2015_value);
                if (ADX2015_value & 0x80) { //RTC in 12-hour format
                    if (ptr->b_12FormatEn == 0x1) { //input in 12-hour format
                        ADX2015_value = ((ptr->usHour/10) << 4) + (ptr->usHour % 10);
                        if (ptr->ubAmOrPm == 0x1)
                            ADX2015_value |= 0x20; // PM
                    }
                    else { //input in 24-hour format
                        ADX2015_value = (ptr->usHour >= 12) ? 0x20 : 0; //set PM or AM
                        ptr->usHour = (ptr->usHour > 12) ? ptr->usHour - 12 : ptr->usHour;
                        ADX2015_value |= (((ptr->usHour/10) << 4) + (ptr->usHour % 10));
                    }
                }
				else { //RTC in 24-hour format
				    if (ptr->b_12FormatEn == 0x1) { //input in 12-hour format
				        if ((ptr->ubAmOrPm == 0x1) && (ptr->usHour != 12))
				            ptr->usHour += 12;
                    }
                    ADX2015_value = ((ptr->usHour/10) << 4) + (ptr->usHour % 10);
                }
				status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM2_DAY, ADX2015_value);
				
				m_alarmUse_B = MMP_TRUE;
			}
			else {			
				if (ubRet == 0) {
					MMPF_OS_ReleaseSem(m_RtcAlamSemID);
				}
				
				#if 0
				ADX2015_RTC_SetAlarmEnable(ADX2015_ALARM_ID_B, MMP_FALSE, NULL, NULL);
				ADX2015_RTC_SetAlarmEnable(ADX2015_ALARM_ID_B, MMP_TRUE, ptr, p_callback);
				return MMP_ERR_NONE;
				#else
				return MMP_SYSTEM_ERR_DOUBLE_SET_ALARM;
				#endif
			}
			
		}
		else {
			RTNA_DBG_Str0("--E-- Error RTC Alarm settings 1 !\r\n");
			if (ubRet == 0) {
				MMPF_OS_ReleaseSem(m_RtcAlamSemID);
			}
			return MMP_SYSTEM_ERR_FORMAT;
		}
		
		m_RtcCallBack[alarm_id - 1] = (RTC_CallBackFunc*)p_callback;
		status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_INT_CTL, &ADX2015_value);	
		RTNA_DBG_Long(0, ADX2015_value);
		
		if(m_bADX2015 == MMP_FALSE) {
			ADX2015_value |= (1 << (5 + alarm_id));
		}
		else {
			ADX2015_value |= 0xC0;   //Always turn-on Alarm A & Alarm B output in ADX2012
		}
		
		//Enable Interrupt
		status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_INT_CTL, ADX2015_value);
		
		/*if(m_alarmUse_A & m_alarmUse_B) {
			ADX2015_value = 0xC0;
		}
		RTNA_DBG_Long(0, (MMP_ULONG)ADX2015_RTC_INT_CTL);
		//ADX2015_value = 0x40;
		RTNA_DBG_Long(0, ADX2015_value);
		*/
		 
		#if 0 //waiting time for RTC alarm settings to work.
		MMPF_OS_Sleep(7000);  //For previous ADX2015, we need some time to let ADX2015 read and done the settings. 7(s) is experiments value.
		#endif
		
		#if 0//debug
		MMPF_OS_Sleep(5);
		status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_INT_CTL, &ADX2015_value);
		RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "ADX2015_RTC_INT_CTL :");
		RTNA_DBG_Long(ADX2015_DEBUG_LEVEL, ADX2015_value);
		RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\n");
		
		MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM1_DATE, &ADX2015_value);
		RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "ADX2015_RTC_ALARM1_DATE :");
		RTNA_DBG_Long(ADX2015_DEBUG_LEVEL, ADX2015_value);
		RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\n");
		
		MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM1_H, &ADX2015_value);
		RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "ADX2015_RTC_ALARM1_H :");
		RTNA_DBG_Long(ADX2015_DEBUG_LEVEL, ADX2015_value);
		RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\n");
		
		MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM1_M, &ADX2015_value);
		RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "ADX2015_RTC_ALARM1_M :");
		RTNA_DBG_Long(ADX2015_DEBUG_LEVEL, ADX2015_value);
		RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\n");
		
		
		MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM1_DAY, &ADX2015_value);
		RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "ADX2015_RTC_ALARM1_DAY :");
		RTNA_DBG_Long(ADX2015_DEBUG_LEVEL, ADX2015_value);
		RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\n");
		#endif
		
		
		if (ubRet == 0) {
			MMPF_OS_ReleaseSem(m_RtcAlamSemID);
		}
	}
	else {
		ubRet = MMPF_OS_AcquireSem(m_RtcAlamSemID, ADX2015_SEM_TIMEOUT);
		
		if((m_alarmUse_A == MMP_TRUE)&&(m_alarmUse_B == MMP_TRUE)) {
			if (alarm_id == ADX2015_ALARM_ID_A) {
				RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "Turn-off alram A\r\n");
				status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM1_DAY, 0x0);
				if(m_bADX2015 == MMP_FALSE) {
					status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_INT_CTL, 0x80);  //keep Alarm B on
				}
			}
			else if (alarm_id == ADX2015_ALARM_ID_B) {
				RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "Turn-off alram B\r\n");
				status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM2_DAY, 0x0);
				if(m_bADX2015 == MMP_FALSE) {
					status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_INT_CTL, 0x40);	//keep Alarm A on
				}
			}
			else {
				RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "ADX2015 Alarm Error alarm_ID !!\r\n");
				if (ubRet == 0) {
					MMPF_OS_ReleaseSem(m_RtcAlamSemID);
				}
				
				return MMP_SYSTEM_ERR_FORMAT;
			}
		}
		else if(m_alarmUse_A == MMP_TRUE) {
			alarm_id = ADX2015_ALARM_ID_A;
			RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "---------Turn-off alram A\r\n");
			status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM1_DAY, 0x0);
			if(m_bADX2015 == MMP_FALSE) {
				status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_INT_CTL, 0x00);
			}
		}
		else if(m_alarmUse_B == MMP_TRUE) {
			alarm_id = ADX2015_ALARM_ID_B;
			RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "---------Turn-off alram B\r\n");
			status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_ALARM2_DAY, 0x0);
			if(m_bADX2015 == MMP_FALSE) {
				status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_RTC_INT_CTL, 0x00);
			}
		}
		else {
			if (ubRet == 0) {
				MMPF_OS_ReleaseSem(m_RtcAlamSemID);
			}
			return MMP_ERR_NONE;
		}
	
		if ((alarm_id == ADX2015_ALARM_ID_A) && (m_alarmUse_A == MMP_TRUE)) {
			m_alarmUse_A = MMP_FALSE;
		}
		else if ((alarm_id == ADX2015_ALARM_ID_B) && (m_alarmUse_B == MMP_TRUE)) {
			m_alarmUse_B = MMP_FALSE;
		}
		else {
			RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "Error RTC Alarm settings 2 !\r\n");
			if (ubRet == 0) {
				MMPF_OS_ReleaseSem(m_RtcAlamSemID);
			}
			return MMP_SYSTEM_ERR_FORMAT;
		}
		
		if (ubRet == 0) {
			MMPF_OS_ReleaseSem(m_RtcAlamSemID);
		}
	}
	
	if(status != MMP_ERR_NONE) {
		return MMP_SYSTEM_ERR_PMU;
	}
	return status;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_LDO_SetV
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used for setting LDO voltage.

This function is used for setting LDO voltage.
@param[in] ADX2015_LDO_ID is the specific ID number.
@param[in] vLevel is between 0x00~0x3F, one level stands 0.05v, the minimum voltage(level 0) is 0.6V
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_LDO_SetVoltage(ADX2015_LDO_ID ldoID, MMP_USHORT vLevel) {
    MMP_USHORT opt_value;
    MMP_SHORT offset_value;

	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL,"### ADX2015_LDO_SetVoltage -\r\n");	

    if (ADX2015_LDO_MAX <= ldoID) {
	    RTNA_DBG_Str0("--E-- ADX2015_LDO_SetVoltage: Wrong LDO ID - ");
	    RTNA_DBG_Byte0(ldoID);
	    RTNA_DBG_Str0("\r\n");

		return MMP_SYSTEM_ERR_PMU;
	}

    vLevel &= ADX2015_LEVEL_BIT;

    if (ADX2015_DCDC_ID_1 == ldoID)
        offset_value = DEFAULT_LDO1_VOLTAGE;
    else if (ADX2015_DCDC_ID_2 == ldoID)
        offset_value = DEFAULT_LDO2_VOLTAGE;
    else //if (ADX2015_DCDC_ID_3 == ldoID)
        offset_value = DEFAULT_LDO3_VOLTAGE;

	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "Default setting is");	
	RTNA_DBG_Short(ADX2015_DEBUG_LEVEL, offset_value);	
	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\n");	

    if (MMP_ERR_NONE != ADX2015_OTP_Read(LDO_OPT_TABLE + ldoID, &opt_value)) {
	    RTNA_DBG_Str0("--E-- ADX2015_LDO_SetVoltage: Read OPT error !!!\r\n");

		return MMP_SYSTEM_ERR_PMU;
	}

    offset_value = ADX2015_LDOXSEL_To_Voltage(offset_value);
    opt_value = ADX2015_LDOXSEL_To_Voltage(opt_value);
    offset_value = (MMP_SHORT) opt_value - offset_value;
    vLevel = ADX2015_LDOXSEL_To_Voltage(vLevel);
    vLevel += offset_value;
    vLevel = ADX2015_Voltage_To_LDOXSEL(vLevel) & ADX2015_LEVEL_BIT;

	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "New setting is");	
	RTNA_DBG_Short(ADX2015_DEBUG_LEVEL, vLevel);	
	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\n");	

	if (MMP_ERR_NONE != MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_LDO_1_CTL + ldoID, ADX2015_LDO_EN | vLevel)) {
        RTNA_DBG_Str0("--E-- ADX2015_LDO_SetVoltage: Write LDO-");
        RTNA_DBG_Byte0(ldoID + 1);
        RTNA_DBG_Str0("error !!!\r\n");

		return MMP_SYSTEM_ERR_PMU;
	}

	return MMP_ERR_NONE;
}


//------------------------------------------------------------------------------
//  Function    : ADX2015_LDO_GetV
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used to get LDO voltage.

This function is used to get LDO voltage.
@param[in] ADX2015_LDO_ID is the specific ID number.
@param[in] returnVol is the return volage value, the unit is mV
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_LDO_GetVoltage(ADX2015_LDO_ID ldoID, MMP_USHORT *returnVoltage){
	MMP_ERR status = MMP_ERR_NONE;
	MMP_USHORT voltage = 0;
	
	if (ADX2015_LDO_MAX <= ldoID)
	    return MMP_SYSTEM_ERR_PMU;

	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, (ADX2015_LDO_1_CTL + ldoID), &voltage);
	voltage &= ADX2015_LEVEL_BIT;
	*returnVoltage = 600 + voltage*50;
	
	if(status != MMP_ERR_NONE) {
		return MMP_SYSTEM_ERR_PMU;
	}
	return status;
}
//------------------------------------------------------------------------------
//  Function    : ADX2015_DCDC_SetVoltage
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used for setting DCDC voltage.

This function is used for setting DCDC voltage.
@param[in] ADX2015_DCDC_ID is the specific ID number.
@param[in] vLevel is between 0x00~0x3F, one level stands 0.05v, the minimum voltage(level 0) is 0.8V
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_DCDC_SetVoltage(ADX2015_DCDC_ID dcdcID, MMP_USHORT vLevel) {
    MMP_USHORT opt_value;
    MMP_SHORT offset_value;

	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL,"### ADX2015_DCDC_SetVoltage -\r\n");	

    if (ADX2015_DCDC_MAX <= dcdcID) {
	    RTNA_DBG_Str0("--E-- ADX2015_DCDC_SetVoltage: Wrong DC/DC ID - ");
	    RTNA_DBG_Byte0(dcdcID);
	    RTNA_DBG_Str0("\r\n");

		return MMP_SYSTEM_ERR_PMU;
	}
 
    vLevel &= ADX2015_LEVEL_BIT;

    if (ADX2015_DCDC_ID_1 == dcdcID)
        offset_value = DEFAULT_DC_DC1_VOLTAGE;
    else if (ADX2015_DCDC_ID_2 == dcdcID)
        offset_value = DEFAULT_DC_DC2_VOLTAGE;
    else //if (ADX2015_DCDC_ID_3 == dcdcID)
        offset_value = DEFAULT_DC_DC3_VOLTAGE;

	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "Default setting is");	
	RTNA_DBG_Short(ADX2015_DEBUG_LEVEL, offset_value);	
	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\n");	

    if (MMP_ERR_NONE != ADX2015_OTP_Read(DCDC_OPT_TABLE + dcdcID, &opt_value)) {
	    RTNA_DBG_Str0("--E-- ADX2015_DCDC_SetVoltage: Read OPT error !!!\r\n");

		return MMP_SYSTEM_ERR_PMU;
	}

    offset_value = ADX2015_BKXSEL_To_Voltage(offset_value);
    opt_value = ADX2015_BKXSEL_To_Voltage(opt_value);
    offset_value = (MMP_SHORT) opt_value - offset_value;
    vLevel = ADX2015_BKXSEL_To_Voltage(vLevel);
    vLevel += offset_value;
    vLevel = ADX2015_Voltage_To_BKXSEL(vLevel) & ADX2015_LEVEL_BIT;

	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "New setting is");	
	RTNA_DBG_Short(ADX2015_DEBUG_LEVEL, vLevel);	
	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\n");	

	if (MMP_ERR_NONE != MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_DCDC_1_CTL2 + dcdcID * ADX2015_DCDC_REG_SIZE, ADX2015_DCDC_BUCK_EN | vLevel)) {
        RTNA_DBG_Str0("--E-- ADX2015_DCDC_SetVoltage: Write DCDC-");
        RTNA_DBG_Byte0(dcdcID + 1);
        RTNA_DBG_Str0("error !!!\r\n");

		return MMP_SYSTEM_ERR_PMU;
	}

	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_DCDC_GetVoltage
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used for Getting DCDC voltage.

This function is used for Getting DCDC voltage.
@param[in] ADX2015_DCDC_ID is the specific ID number.
@param[in] returnVol is the return volage value, the unit is mV
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_DCDC_GetVoltage(ADX2015_DCDC_ID dcdcID, MMP_USHORT* returnVoltage) {
	MMP_USHORT voltage = 0;
	MMP_ERR status = MMP_ERR_NONE;

	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, (ADX2015_DCDC_1_CTL2 + dcdcID*ADX2015_DCDC_REG_SIZE), &voltage);

	if(status != MMP_ERR_NONE) {
		return MMP_SYSTEM_ERR_PMU;
	}

	voltage &= ADX2015_LEVEL_BIT;
    *returnVoltage = ADX2015_BKXSEL_To_Voltage(voltage);

	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_CLASSG_En
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used to enable/disable Class G module(AMP).
@param[in] bEnable is true for enable and flase for disable Cleass G module (AMP).
This function is used to enable/disable AMP.
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_CLASSG_En(MMP_BOOL bEnable)
{
	MMP_ERR status = MMP_ERR_NONE;
	if(m_bADX2015 == MMP_FALSE) {
		if (bEnable == MMP_TRUE) {
			status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CLASSG_HEAD_SET2, 0x0C);
			MMPF_OS_Sleep(100);
			status |= ADX2015_CLASSG_SetVol(0x3A);
		}
		else {
			status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CLASSG_HEAD_SET2, 0x0F);
			status |= ADX2015_CLASSG_SetVol(0);
		}
		
		if(status != MMP_ERR_NONE) {
			return MMP_SYSTEM_ERR_PMU;
		}
	}
	return status;
}


//------------------------------------------------------------------------------
//  Function    : ADX2015_CLASSG_SetVol
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used to set out volume(in moudule class G ,AMP) as target value.
@param[in] vol_db stands for the volume gain output, 0 stands for mute(silent), 1~78 maps to -57~20 db.
This function is used to set out volume as target value.
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_CLASSG_SetVol(MMP_UBYTE vol_db)
{
	MMP_USHORT currentVol = 0;
	MMP_ERR status = MMP_ERR_NONE;
	if(m_bADX2015 == MMP_FALSE) {
		if (vol_db <= ADX2015_CLASSG_MAX_VOL) {
			status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CLASSG_VOL_CTL1, &currentVol);
			if(currentVol != vol_db) {
				status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CLASSG_VOL_CTL1, vol_db);
				status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CLASSG_VOL_CTL2, vol_db);
			}
		}
		
		if(status != MMP_ERR_NONE) {
			return MMP_SYSTEM_ERR_PMU;
		}
	}
	return status;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Set_ChargeI
//  Description : Set charge current to battery charger 4
//------------------------------------------------------------------------------
/** @brief Set charge current to battery charger 4 of ADX2015.

This function is used to set charge current to battery charger 4 of ADX2015.
@return operation status
*/
MMP_ERR ADX2015_Set_ChargeI(MMP_USHORT iset)
{
	MMP_ERR status = MMP_ERR_NONE;
	MMP_USHORT val;
	
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_BATCHR_BCCR4, &val);
	val = (val & 0xE3) | ((iset & 0x07) << 2);      //bit[4:2] represents charging current	
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_BATCHR_BCCR4, val);
	
	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "### ADX2015_Set_ChargeI -");
    RTNA_DBG_Byte(ADX2015_DEBUG_LEVEL, iset);
    RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "     ");
    RTNA_DBG_Byte(ADX2015_DEBUG_LEVEL, val);
    RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\n");

	return status;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Enable_DC_Path
//  Description : Enable current path from DC
//------------------------------------------------------------------------------
/** @brief Enable current path from DC.

This function is used to enable current path from DC. If bEnable is false, the current switches to VBAT
@return operation status
*/
MMP_ERR ADX2015_Enable_DC_Path(MMP_UBYTE bEnable)
{
	MMP_ERR status = MMP_ERR_NONE;
	MMP_USHORT val;
	
	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "### ADX2015_DC_PATH -");
    RTNA_DBG_Byte(ADX2015_DEBUG_LEVEL, bEnable);
    RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\n");
	
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_PPM_CTL1, &val);
	
	if (bEnable)
		val = val & (~0x0040);
	else
		val = val | (0x0040);
	
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_PPM_CTL1, (MMP_USHORT) val);	

	return status;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Set_I_Limit
//  Description : Set current limitation
//                x00: Using Default (default), x01:Default + 100mA, x10: Default + 300mA, x11: Default + 500mA
//------------------------------------------------------------------------------
/** @brief Set current limitation

This function is used to Set current limitation
@return operation status
*/
MMP_ERR ADX2015_Set_I_Limit(MMP_UBYTE bLimit)
{
	MMP_ERR status = MMP_ERR_NONE;
	MMP_USHORT val = 0x0000;

    RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "### ADX2015_Set_I_Limit -");
    RTNA_DBG_Byte(ADX2015_DEBUG_LEVEL, bLimit);
    RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\n");
    
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_PPM_CTL1, &val);
//	val = ((val>>4)<<4) | ((bLimit<<1) | (val&0x0001));//set bit [3:1] to value of bLimit 
	val = (val & 0xF1) | ((bLimit & 0x07) << 1);        //set bit [3:1] to value of bLimit 
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_PPM_CTL1, val);

	return status;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_CheckECOVersion
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used to check if 506 ECO2.
@param[in] bReturnECOVersion is the return flag value, indicate which ECO version or not.
This function is used to check if 506 ECO.
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_CheckECOVersion(MMP_UBYTE *bReturnECOVersion)
{
	MMP_ERR status = MMP_ERR_NONE;

	return status;
}

MMP_ERR ADX2015_OTP_Reset(void)
{
	#if (APPLY_OTP == 1)
	RTNA_DBG_Str(0,"ADX2015_OTP_Reset\r\n");	
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, 0xA4, 0x00);
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, 0xA4, 0x80);
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, 0xA4, 0x00);
	#endif
	return MMP_ERR_NONE;
}

MMP_ERR ADX2015_OTP_Read(MMP_UBYTE ubReg, MMP_USHORT *ubData)
{
    MMP_ERR status = MMP_ERR_NONE;

    // assign OTP address 0x05 to be read
    status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_OPT_ACCESS_ADDR, (MMP_USHORT) ubReg);
	RTNA_WAIT_MS(2);        // Need delay 1ms above
    // trigger one OTP reading cycle
    status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_OPT_CTRL_REG1, 0x02);
	RTNA_WAIT_MS(2);        // Need delay 1ms above
    // read DCx trimming value
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_OPT_READ_DATA, ubData);
    *ubData &= ADX2015_LEVEL_BIT;
	RTNA_WAIT_MS(2);        // Need delay 1ms above
    // restore OTP operation command register 
    status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_OPT_CTRL_REG1, 0x00);
	RTNA_WAIT_MS(2);        // Need delay 1ms above

	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "Read 2015 OTP addr/value :");
	RTNA_DBG_Byte(ADX2015_DEBUG_LEVEL, ubReg);
	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, " / ");
	RTNA_DBG_Byte(ADX2015_DEBUG_LEVEL, *ubData);
	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\n");
	
	return status;
}

MMP_BOOL ADX2015_OTP_CheckValid(void)
{
	#if (APPLY_OTP == 1)
	MMP_USHORT usValue;	
	ADX2015_OTP_Read(0x00, &usValue);
	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL,"OTP_CheckValid : ");
	RTNA_DBG_Byte(ADX2015_DEBUG_LEVEL,usValue);
	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL,"\r\n");
	
	if((usValue >> 6)&(0x01))
	{
		return MMP_TRUE;
	}else
	{
		return MMP_FALSE;
	}
	#else
	return MMP_FALSE;
	#endif
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Initialize
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used to init ADX2015 driver.

This function is used to init ADX2015 driver.
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_Initialize(void)
{
	MMP_ERR		status = MMP_ERR_NONE;

    RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "ADX2015_Initialize()\r\n");

#if defined(ALL_FW)
    #if (USE_ADC_SEMI)
	m_ADCSemID =  MMPF_OS_CreateSem(1);
    #endif
    #if (USE_ADX2015_SEMI)
    m_ADX2015SemID = MMPF_OS_CreateSem(1);
    #endif
    
    #ifdef ENABLE_PMU_INT_TIMER
	for(i = 0 ; i < MMPF_OS_TMRID_MAX; i++) {
		m_usTimerID[i] = MMPF_OS_TMRID_MAX;  //initial ID  as  invalid timer id.
	}
	m_usTimerReadIndex = 0;
	m_usTimerWriteIndex = 0;
	#endif
#endif

#ifdef UPDATER_FW
	{
		MMP_USHORT settingValue, targetVoltage;
 		// Change Buck1 DC/DC to 1.4V (for Core power, default is 1.2V)
    	RTNA_DBG_Str(0, "### Change Buck1 DC/DC to 1.4V\r\n");
    	for (targetVoltage = 1250; targetVoltage <= 1400; targetVoltage += 50) {
        	settingValue = ADX2015_Voltage_To_BKXSEL(targetVoltage);
            ADX2015_DCDC_SetVoltage(ADX2015_DCDC_ID_1, settingValue);
        	RTNA_WAIT_MS(2);
    	}
    	
    	// Changing Buck2 DC/DC from 1.8V to 1.9V needs adding 4 level(DCDC2 is 1.8V in OTP)
    	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_DCDC_2_CTL2, &settingValue);
    	settingValue = settingValue | (((settingValue & 0x3F) + 4) & 0x3F);
    	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_DCDC_2_CTL2, settingValue);
    }
#endif

#ifdef MBOOT_FW
    {
        // Adjust ADX2015 Output Voltage
        MMP_USHORT settingValue, targetVoltage;

        ADX2015_OTP_Reset();

        //Set VSYS to 4.8V
		status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, 0xAC, 0x80);
    	RTNA_WAIT_MS(2);
		status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, 0xA9, 0x50);  // DPPM enable
		status |= ADX2015_Set_I_Limit(ADX2015_I_Limit_DEFAULT);
		status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, 0x83, 0x80);  // Charge Pump Enable
		status |= ADX2015_Set_ChargeI(ADX2015_I_Charge_90mA);               // 90mA
        //Disable Watch Dog
		settingValue = 0;
		status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, 0x61, &settingValue);
		settingValue = settingValue & 0x7F | 0x20;
		status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, 0x61, settingValue);
        //Enable emergency shutdown
        settingValue = 0;
		status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, 0x04, &settingValue);
		settingValue |= 0x04;
		status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, 0x04, settingValue);

    	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "############################################################\r\n");
    	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "ADX2015 Voltage Adjust ...\r\n");

        // Change Buck1 DC/DC to 1.4V (for Core power, default is 1.2V)
    	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "### Change Buck1 DC/DC to 1.4V\r\n");
    	settingValue = 0;
		status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, 0xB1, &settingValue);
		settingValue = settingValue | 0x02;
		status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, 0xB1, settingValue);
    	for (targetVoltage = 1250; targetVoltage <= 1400; targetVoltage += 50) {
        	settingValue = ADX2015_Voltage_To_BKXSEL(targetVoltage);
            ADX2015_DCDC_SetVoltage(ADX2015_DCDC_ID_1, settingValue);
        	RTNA_WAIT_MS(2);
    	}
		
		// Changing Buck2 DC/DC from 1.8V to 1.9V needs adding 4 level(DCDC2 is 1.8V in OTP)
    	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_DCDC_2_CTL2, &settingValue);
    	settingValue = settingValue | (((settingValue & 0x3F) + 4) & 0x3F);
    	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_DCDC_2_CTL2, settingValue);
		
        // Change Buck3 DC/DC to 2.8V (for system GPIO power domain, default is 3.3V)  
    	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\n### Change Buck3 DC/DC to 2.8V\r\n");
		status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, 0x14, 0x5A);
		status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, 0xB9, 0x11);

    	for (targetVoltage = 3250; targetVoltage >= 2800; targetVoltage -= 50) {
        	settingValue = ADX2015_Voltage_To_BKXSEL(targetVoltage);
            ADX2015_DCDC_SetVoltage(ADX2015_DCDC_ID_3, settingValue);
        	RTNA_WAIT_MS(2);
    	}

    	#ifdef CFG_NON_STD_SENSOR_POWER
        // Change LDO1 to 3.3V (Sensor Power, OV2710 is 3.1V, AR0330 is 2.8V, IC default is 2.8V)
    	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\n### Change LDO1 to\r\n");
    	RTNA_DBG_Short(ADX2015_DEBUG_LEVEL, CFG_NON_STD_SENSOR_POWER);
    	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\n");
    	settingValue = ADX2015_Voltage_To_LDOXSEL(CFG_NON_STD_SENSOR_POWER);
        ADX2015_LDO_SetVoltage(ADX2015_LDO_ID_1, settingValue);
    	RTNA_WAIT_MS(2);
    	#endif

        // Change LDO2 to 3.3V (For LCD backlight , AIT8427 USB and HDMI power domain)
    	RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "\r\n### Change LDO2 to 3.3V\r\n");
    	settingValue = ADX2015_Voltage_To_LDOXSEL(3300);
        ADX2015_LDO_SetVoltage(ADX2015_LDO_ID_2, settingValue);
    	RTNA_WAIT_MS(2);

		#if (SUPPORT_IR_CONVERTER)
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_IR_PWR_CODE, IR_VALUE_POWER);
		#endif
    }
#endif      // #if defined(MBOOT_FW)

#ifdef ALL_FW
	{
		MMP_USHORT regVal;
		
		// Clear all interrupt status, must be
		RTNA_DBG_Str(0, "Clear ADX2015 all interrupt status -\r\n");
		MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, &regVal);	
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, 0x7F);	
		MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTB_STATUS, &regVal);
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTB_STATUS, 0xFF);
	
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_IR_CLR, 0x00);	
	}
#endif

	if(status != MMP_ERR_NONE) {
		return MMP_SYSTEM_ERR_PMU;
	}
	return status;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Get_DCIN_INT
//  Description : Get DC In interrupt status
//------------------------------------------------------------------------------
/** @brief This function is used to get the DC In interrupt of ADX2015.

This function is used to get the DC In interrupt of ADX2015.
@return It reports the status of the DC In interrupt.
*/
MMP_UBYTE ADX2015_Get_DCIN_INT(void)
{
	MMP_USHORT usADX2015IntStatus = 0;
	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, &usADX2015IntStatus);
	usADX2015IntStatus &= ADX2015_INT_EVENT_DCIN;

	if (usADX2015IntStatus)
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, ADX2015_INT_EVENT_DCIN);
	
	return usADX2015IntStatus;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Get_DCIN_Status
//  Description : Get DC In status
//------------------------------------------------------------------------------
/** @brief This function is used to get the DC In status of ADX2015.

This function is used to get the DC In status of ADX2015.
@return It reports the status of the DC In status.
*/
MMP_UBYTE ADX2015_Get_DCIN_Status(void)
{
	MMP_USHORT usStatus = 0;
	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_PPM_CTL3, &usStatus);
	
	return (usStatus & 0x10) ? MMP_TRUE : MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Get_IR_INT
//  Description : Get IR interrupt status
//------------------------------------------------------------------------------
/** @brief This function is used to get the IR interrupt of ADX2015.

This function is used to get the IR interrupt of ADX2015.
@return It reports the status of the IR interrupt.
*/
MMP_UBYTE ADX2015_Get_IR_INT(void)
{
	MMP_USHORT usADX2015IntStatus = 0;
	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, &usADX2015IntStatus);
	usADX2015IntStatus &= ADX2015_INT_EVENT_IR;

	if (usADX2015IntStatus)
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, ADX2015_INT_EVENT_IR);
	
	return usADX2015IntStatus ? 1 : 0;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Get_USBJIG_INT
//  Description : Get USB JIG interrupt status
//------------------------------------------------------------------------------
/** @brief This function is used to get the USB JIG interrupt of ADX2015.

This function is used to get the USB JIG interrupt of ADX2015.
@return It reports the status of the USB JIG interrupt.
*/
MMP_UBYTE ADX2015_Get_USBJIG_INT(void)
{
	MMP_USHORT usADX2015IntStatus = 0;
	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, &usADX2015IntStatus);
	usADX2015IntStatus &= ADX2015_INT_EVENT_USBJIG;

	if (usADX2015IntStatus)
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, ADX2015_INT_EVENT_USBJIG);
	
	return usADX2015IntStatus ? MMP_TRUE : MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Get_VBUS_INT
//  Description : Get VBUS interrupt status
//------------------------------------------------------------------------------
/** @brief This function is used to get the VBUS interrupt of ADX2015.

This function is used to get the VBUS interrupt of ADX2015.
@return It reports the status of the VBUS interrupt.
*/
MMP_UBYTE ADX2015_Get_VBUS_INT(void)
{
	MMP_USHORT usADX2015IntStatus = 0;
	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, &usADX2015IntStatus);
	usADX2015IntStatus &= ADX2015_INT_EVENT_VBUS;

	if (usADX2015IntStatus)
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, ADX2015_INT_EVENT_VBUS);
	
	return usADX2015IntStatus ? MMP_TRUE : MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Get_VBUS_Status
//  Description : Get VBUS status
//------------------------------------------------------------------------------
/** @brief This function is used to get the VBUS status of ADX2015.

This function is used to get the VBUS status of ADX2015.
@return It reports the status of the VBUS.
*/
MMP_UBYTE ADX2015_Get_VBUS_Status(void)
{
	MMP_USHORT usStatus = 0;
	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_POWER_ON_STATUS, &usStatus);

    printc("V0x%X\n", usStatus);	
	return (usStatus & ADX2015_VBUS_FLG) ? 0 : 1;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Get_PWRK2_PRESS_INT
//  Description : Get power key 2 pressed interrupt status
//------------------------------------------------------------------------------
/** @brief This function is used to get the power key 2 pressed interrupt of ADX2015.

This function is used to get the power key 2 pressed interrupt of ADX2015.
@return It reports the status of the power key 2 pressed interrupt.
*/
MMP_UBYTE ADX2015_Get_PWRK2_Press_INT(void)
{
	MMP_USHORT usADX2015IntStatus = 0;

	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, &usADX2015IntStatus);
	usADX2015IntStatus &= ADX2015_INT_EVENT_PWRK2_PRESS;

	if (usADX2015IntStatus)
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, ADX2015_INT_EVENT_PWRK2_PRESS);
	
	return usADX2015IntStatus ? MMP_TRUE : MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Get_PWRK_REL_INT
//  Description : Get power key 1 pressed interrupt status
//------------------------------------------------------------------------------
/** @brief This function is used to get the power key 1 released interrupt of ADX2015.

This function is used to get the power key 1 released interrupt of ADX2015.
@return It reports the status of the power key 1 released interrupt.
*/
MMP_UBYTE ADX2015_Get_PWRK_REL_INT(void)
{
	MMP_USHORT usADX2015IntStatus = 0;

	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, &usADX2015IntStatus);
	usADX2015IntStatus &= ADX2015_INT_EVENT_PWRK_REL;

	if (usADX2015IntStatus)
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, ADX2015_INT_EVENT_PWRK_REL);
	
	return usADX2015IntStatus ? MMP_TRUE : MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Get_PWRK_PRESS_INT
//  Description : Get power key 1 pressed interrupt status
//------------------------------------------------------------------------------
/** @brief This function is used to get the power key 1 pressed interrupt of ADX2015.

This function is used to get the power key 1 pressed interrupt of ADX2015.
@return It reports the status of the power key 1 pressed interrupt.
*/
MMP_UBYTE ADX2015_Get_PWRK_Press_INT(void)
{
	MMP_USHORT usADX2015IntStatus = 0;

	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, &usADX2015IntStatus);
	usADX2015IntStatus &= ADX2015_INT_EVENT_PWRK_PRESS;

	if (usADX2015IntStatus)
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, ADX2015_INT_EVENT_PWRK_PRESS);
	
	return usADX2015IntStatus ? MMP_TRUE : MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Get_BGroup_INT
//  Description : Get VBUS interrupt status
//------------------------------------------------------------------------------
/** @brief This function is used to get the B Group interrupt of ADX2015.

This function is used to get the B Group interrupt of ADX2015.
@return It reports the status of the B Group interrupt.
*/
MMP_UBYTE ADX2015_Get_BGroup_INT(void)
{
	MMP_USHORT usADX2015IntStatus = 0;

	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, &usADX2015IntStatus);
	usADX2015IntStatus &= ADX2015_INT_EVENT_BGROUP;
	
	if (usADX2015IntStatus)
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, ADX2015_INT_EVENT_BGROUP);
	
	return usADX2015IntStatus ? MMP_TRUE : MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Get_DCOUT_INT
//  Description : Get DC Out interrupt status
//------------------------------------------------------------------------------
/** @brief This function is used to get the DC Out interrupt of ADX2015.

This function is used to get the DC Out interrupt of ADX2015.
@return It reports the status of the DC Out interrupt.
*/
MMP_UBYTE ADX2015_Get_DCOUT_INT(void)
{
	MMP_USHORT usADX2015IntStatus = 0;

	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTB_STATUS, &usADX2015IntStatus);
	usADX2015IntStatus &= ADX2015_INT_EVENT_DCOUT;
	
	if (usADX2015IntStatus)
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTB_STATUS, ADX2015_INT_EVENT_DCOUT);
	
	return usADX2015IntStatus ? MMP_TRUE : MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Get_FirstOn_INT
//  Description : Get first on interrupt status
//------------------------------------------------------------------------------
/** @brief This function is used to get the first on interrupt of ADX2015.

This function is used to get the first on interrupt of ADX2015.
@return It reports the status of the first on interrupt.
*/
MMP_UBYTE ADX2015_Get_FirstOn_INT(void)
{
	MMP_USHORT usADX2015IntStatus = 0;

	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTB_STATUS, &usADX2015IntStatus);
	usADX2015IntStatus &= ADX2015_INT_EVENT_FIRST_ON;

	if (usADX2015IntStatus)
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTB_STATUS, ADX2015_INT_EVENT_FIRST_ON);
	
	return usADX2015IntStatus ? MMP_TRUE : MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Get_Wake_INT
//  Description : Get Wake interrupt status
//------------------------------------------------------------------------------
/** @brief This function is used to get the wake interrupt of ADX2015.

This function is used to get the wake interrupt of ADX2015.
@return It reports the status of the wake interrupt.
*/
MMP_UBYTE ADX2015_Get_Wake_INT(void)
{
	MMP_USHORT usADX2015IntStatus = 0;

	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTB_STATUS, &usADX2015IntStatus);
	usADX2015IntStatus &= ADX2015_INT_EVENT_WAKE;

	if (usADX2015IntStatus)
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTB_STATUS, ADX2015_INT_EVENT_WAKE);
	
	return usADX2015IntStatus ? MMP_TRUE : MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Get_RTC2_INT
//  Description : Get 2nd RTC interrupt status
//------------------------------------------------------------------------------
/** @brief This function is used to get the 2nd RTC interrupt of ADX2015.

This function is used to get the 2nd RTC interrupt of ADX2015.
@return It reports the status of the 2nd RTC interrupt.
*/
MMP_UBYTE ADX2015_Get_RTC2_INT(void)
{
	MMP_USHORT usADX2015IntStatus = 0;

	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTB_STATUS, &usADX2015IntStatus);
	usADX2015IntStatus &= ADX2015_INT_EVENT_RTC2;

	if (usADX2015IntStatus)
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTB_STATUS, ADX2015_INT_EVENT_RTC2);
	
	return usADX2015IntStatus ? MMP_TRUE : MMP_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_Get_RTC_INT
//  Description : Get 1st RTC interrupt status
//------------------------------------------------------------------------------
/** @brief This function is used to get the 1st RTC interrupt of ADX2015.

This function is used to get the 1st RTC interrupt of ADX2015.
@return It reports the status of the 1st RTC interrupt.
*/
MMP_UBYTE ADX2015_Get_RTC_INT(void)
{
	MMP_USHORT usADX2015IntStatus = 0;

	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTB_STATUS, &usADX2015IntStatus);
	usADX2015IntStatus &= ADX2015_INT_EVENT_RTC;

	if (usADX2015IntStatus)
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTB_STATUS, ADX2015_INT_EVENT_RTC);
	
	return usADX2015IntStatus ? MMP_TRUE : MMP_FALSE;
}

#ifdef ALL_FW
//------------------------------------------------------------------------------
//  Function    : ADX2015_IsrHandler
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used to handle the interrupt of ADX2015.

This function is used to handle the interrupt of ADX2015.
@return It reports the status of all interrupts.
*/
void ADX2015_IsrHandler(MMP_ULONG arg) {
//	MMP_UBYTE  ubRet = 0xFF;
//	ADX2015_ALARM_ID alarm_id = ADX2015_ALARM_ID_NONE;
	MMP_USHORT usADX2015IntStatus=0, usADX2015IntAStatus = 0, usADX2015IntBStatus = 0, usCleanStatus;
	
	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, &usADX2015IntAStatus);
	usADX2015IntAStatus &= 0x7F;
	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTB_STATUS, &usADX2015IntBStatus);
	usADX2015IntBStatus &= 0xFF;

	if (usADX2015IntAStatus)
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, usADX2015IntAStatus);

	if (usADX2015IntBStatus)
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTB_STATUS, usADX2015IntBStatus);
	
	usADX2015IntStatus = usADX2015IntAStatus | (usADX2015IntBStatus << 8);
	usCleanStatus = usADX2015IntStatus;
	
	if (usADX2015IntStatus) {
		RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "ADX2015 Int Status");
		RTNA_DBG_Short(ADX2015_ISR_DEBUG_LEVEL, usADX2015IntStatus);
		RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "\r\n");
	}
	
	while (usADX2015IntAStatus | (usADX2015IntBStatus << 8)) 
	{
		/////////////////////////////////////////////////////////////////////////////
		// ADX2015_INT_EVENT_RTC
		/////////////////////////////////////////////////////////////////////////////
		if (usADX2015IntBStatus & ADX2015_INT_EVENT_RTC)
		{	// TBD
    		RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "### ADX2015_INT_EVENT_RTC\r\n");
			usADX2015IntBStatus &= (~ADX2015_INT_EVENT_RTC);
#if 0
			ubRet = MMPF_OS_AcquireSem(m_RtcAlamSemID, ADX2015_SEM_TIMEOUT);

			if (m_bADX2015 == MMP_FALSE) { //for ADX2015
				if((m_alarmUse_A == MMP_TRUE)&&(m_alarmUse_B == MMP_TRUE)) {
					ADX2015_RTC_AlarmCheckID(&alarm_id);
				}
				else if(m_alarmUse_A == MMP_TRUE) {
					alarm_id = ADX2015_ALARM_ID_A;
				}
				else if(m_alarmUse_B == MMP_TRUE) {
					alarm_id = ADX2015_ALARM_ID_B;
				}
				else {
					//Because the Alarm continue about 1 minutes, althought we can stop it during 10 second,
					//But in this 10 s, we will continue receive the Alarm interrupt
					MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTB_STATUS, ADX2015_INT_EVENT_RTC);
					
					#ifdef ENABLE_PMU_INT_TIMER
					m_usTimerID[m_usTimerWriteIndex] = MMPF_OS_StartTimer(m_glADX2015AccessTime, MMPF_OS_TMR_OPT_ONE_SHOT, (MMPF_OS_TMR_CALLBACK)&ADX2015_IsrTimerCallBack, NULL);
					if (m_usTimerID[m_usTimerWriteIndex] >= MMPF_OS_TMRID_MAX) {
						RTNA_DBG_Str0("--E-- ADX2015 Get OS Timer error !\r\n");
						MMPF_OS_Sleep(m_glADX2015AccessTime);
					}
					else {
						m_usTimerWriteIndex = ((m_usTimerWriteIndex + 1) % MMPF_OS_TMRID_MAX);
					}
					#endif
					
					if (ubRet == 0) {
						MMPF_OS_ReleaseSem(m_RtcAlamSemID);
					}
				}
			}
			else {	//for ADX2012
				if(m_alarmUse_A == MMP_TRUE) {
					alarm_id = ADX2015_ALARM_ID_A;
				}
				else {
					//Because the Alarm continue about  1 minutes, althought we can stop it during 10 second,
					//But in this 10 s, we will continue receive the Alarm interrupt
					MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, usCleanStatus);
					
					#ifdef ENABLE_PMU_INT_TIMER
					m_usTimerID[m_usTimerWriteIndex] = MMPF_OS_StartTimer(m_glADX2015AccessTime, MMPF_OS_TMR_OPT_ONE_SHOT, (MMPF_OS_TMR_CALLBACK)&ADX2015_IsrTimerCallBack, NULL);
					if (m_usTimerID[m_usTimerWriteIndex] >= MMPF_OS_TMRID_MAX) {
						RTNA_DBG_Str0("--E--  ADX2015 Get OS Timer error !\r\n");
						MMPF_OS_Sleep(m_glADX2015AccessTime);
					}
					else {
						m_usTimerWriteIndex = ((m_usTimerWriteIndex + 1) % MMPF_OS_TMRID_MAX);
					}
					#endif
					
					if (ubRet == 0) {
						MMPF_OS_ReleaseSem(m_RtcAlamSemID);
					}
					
					#if defined(ALL_FW)
					if (adx2015_int_cb_ptr)
					    adx2015_int_cb_ptr(usADX2015IntStatus);
					#endif

					return usADX2015IntStatus;
				}
			}
			
			if (ubRet == 0) {
				MMPF_OS_ReleaseSem(m_RtcAlamSemID);
			}
			
			ADX2015_RTC_SetAlarmEnable(alarm_id, MMP_FALSE, NULL, NULL);
			
			if (m_RtcCallBack[alarm_id - 1] != NULL) {
				(*m_RtcCallBack[alarm_id - 1]) ();
			}
			
			//MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_EN, 0x1E);
			//MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, 0x2);
			if(m_bADX2015 == MMP_FALSE) {
				MMPF_OS_Sleep(1000);
			}
#endif
		}
		/////////////////////////////////////////////////////////////////////////////
		// ADX2015_INT_EVENT_DCIN
		/////////////////////////////////////////////////////////////////////////////
		else if(usADX2015IntAStatus & ADX2015_INT_EVENT_DCIN)
		{
    		RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "### ADX2015_INT_EVENT_DCIN\r\n");
			usADX2015IntAStatus &= (~ADX2015_INT_EVENT_DCIN);
		}
		/////////////////////////////////////////////////////////////////////////////
		// ADX2015_INT_EVENT_DCOUT
		/////////////////////////////////////////////////////////////////////////////
		else if(usADX2015IntBStatus & ADX2015_INT_EVENT_DCOUT) 
		{
    		RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "### ADX2015_INT_EVENT_DCOUT\r\n");
			usADX2015IntBStatus &= (~ADX2015_INT_EVENT_DCOUT);

		    // workaround about ADX2015 DC-OUT detect issue
		    if (AHC_IsUsbConnect()) {
		    	RTNA_DBG_Str(0, "\r\n--W-- ADX2015 DC-IN workaround\r\n");
		    	RTNA_DBG_Str(0, "--W-- ADX2015 DC-IN workaround\r\n");
		    	RTNA_DBG_Str(0, "--W-- ADX2015 DC-IN workaround\r\n\r\n");
		    	ADX2015_Enable_DC_Path(MMP_TRUE);
		    	
		    	// Cancel DC-OUT interrupt
		    	usADX2015IntStatus &= ~(ADX2015_INT_EVENT_DCOUT << 8);
		    }
		}
		/////////////////////////////////////////////////////////////////////////////
		// ADX2015_INT_EVENT_IR
		/////////////////////////////////////////////////////////////////////////////
		else if(usADX2015IntAStatus & ADX2015_INT_EVENT_IR)
		{
			MMP_USHORT val;

    		RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "### ADX2015_INT_EVENT_IR\r\n");
			usADX2015IntAStatus &= (~ADX2015_INT_EVENT_IR);
			
			MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_IR_DATA0, &val);
			m_ir_data.id = val & 0xFF;
			MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_IR_DATA1, &val);
			m_ir_data.id_bar = val & 0xFF;
			MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_IR_DATA2, &val);
			m_ir_data.key_code = val & 0xFF;
			MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_IR_DATA3, &val);
			m_ir_data.repeat_times = val & 0xFF;
			m_ir_data.data_updated = MMP_TRUE;

			MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_IR_CLR, 0x00);
#if 0
			RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, " ID:");
			RTNA_DBG_Byte(ADX2015_ISR_DEBUG_LEVEL, m_ir_data.id);
			RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, " #ID:");
			RTNA_DBG_Byte(ADX2015_ISR_DEBUG_LEVEL, m_ir_data.id_bar);
			RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, " Key Code:");
			RTNA_DBG_Byte(ADX2015_ISR_DEBUG_LEVEL, m_ir_data.key_code);
			RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, " Repeat:");
			RTNA_DBG_Byte(ADX2015_ISR_DEBUG_LEVEL, m_ir_data.repeat_times);
			RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "\r\n");
#endif
		}
		/////////////////////////////////////////////////////////////////////////////
		// ADX2015_INT_EVENT_USBJIG
		/////////////////////////////////////////////////////////////////////////////
		else if(usADX2015IntAStatus & ADX2015_INT_EVENT_USBJIG)
		{
    		RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "### ADX2015_INT_EVENT_USBJIG\r\n");
			usADX2015IntAStatus &= (~ADX2015_INT_EVENT_USBJIG);
			RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "ADX2015 USB JIG Event !!\r\n");
		}
		/////////////////////////////////////////////////////////////////////////////
		// ADX2015_INT_EVENT_VBUS
		/////////////////////////////////////////////////////////////////////////////
		else if(usADX2015IntAStatus & ADX2015_INT_EVENT_VBUS)
		{
    		RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "### ADX2015_INT_EVENT_VBUS\r\n");
			usADX2015IntAStatus &= (~ADX2015_INT_EVENT_VBUS);
			RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "ADX2015 USB VBUS event !!\r\n");
		}
		/////////////////////////////////////////////////////////////////////////////
		// ADX2015_INT_EVENT_PWRK2_PRESS
		/////////////////////////////////////////////////////////////////////////////
		else if(usADX2015IntAStatus & ADX2015_INT_EVENT_PWRK2_PRESS)
		{
    		RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "### ADX2015_INT_EVENT_PWRK2_PRESS\r\n");
			usADX2015IntAStatus &= (~ADX2015_INT_EVENT_PWRK2_PRESS);
			RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "ADX2015 Power Key 2 event !!\r\n");
		}
		/////////////////////////////////////////////////////////////////////////////
		// ADX2015_INT_EVENT_PWRK_REL
		/////////////////////////////////////////////////////////////////////////////
		else if(usADX2015IntAStatus & ADX2015_INT_EVENT_PWRK_REL)
		{
    		RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "### ADX2015_INT_EVENT_PWRK_REL\r\n");
			usADX2015IntAStatus &= (~ADX2015_INT_EVENT_PWRK_REL);
			RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "ADX2015 Power Key release event !!\r\n");
		}
		/////////////////////////////////////////////////////////////////////////////
		// ADX2015_INT_EVENT_PWRK_PRESS
		/////////////////////////////////////////////////////////////////////////////
		else if(usADX2015IntAStatus & ADX2015_INT_EVENT_PWRK_PRESS)
		{
    		RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "### ADX2015_INT_EVENT_PWRK_PRESS\r\n");
			usADX2015IntAStatus &= (~ADX2015_INT_EVENT_PWRK_PRESS);
			RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "ADX2015 Power Key event !!\r\n");
		}
		/////////////////////////////////////////////////////////////////////////////
		// ADX2015_INT_EVENT_FIRST_ON
		/////////////////////////////////////////////////////////////////////////////
		else if(usADX2015IntBStatus & ADX2015_INT_EVENT_FIRST_ON) 
		{
    		RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "### ADX2015_INT_EVENT_FIRST_ON\r\n");
			usADX2015IntBStatus &= (~ADX2015_INT_EVENT_FIRST_ON);
			RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "ADX2015 First On Event !!\r\n");
		}
		/////////////////////////////////////////////////////////////////////////////
		// ADX2015_INT_EVENT_WAKE
		/////////////////////////////////////////////////////////////////////////////
		else if(usADX2015IntBStatus & ADX2015_INT_EVENT_WAKE) 
		{
    		RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "### ADX2015_INT_EVENT_WAKE\r\n");
			usADX2015IntBStatus &=(~ADX2015_INT_EVENT_WAKE); 
			RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "ADX2015 Wake up Event !!\r\n");
		}
		/////////////////////////////////////////////////////////////////////////////
		// ADX2015_INT_EVENT_RTC2
		/////////////////////////////////////////////////////////////////////////////
		else if(usADX2015IntBStatus & ADX2015_INT_EVENT_RTC2) 
		{	// TBD
    		RTNA_DBG_Str(ADX2015_ISR_DEBUG_LEVEL, "### ADX2015_INT_EVENT_RTC2\r\n");
			usADX2015IntBStatus &= (~ADX2015_INT_EVENT_RTC2);
#if 0
			ubRet = MMPF_OS_AcquireSem(m_RtcAlamSemID, ADX2015_SEM_TIMEOUT);
			
			if(m_alarmUse_B == MMP_TRUE) {
				alarm_id = ADX2015_ALARM_ID_B;
			}
			else {
				//Because the Alarm continue about  1 minutes, althought we can stop it during 10 second,
				//But in this 10 s, we will continue receive the Alarm interrupt
				MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, usCleanStatus);
				
				#ifdef ENABLE_PMU_INT_TIMER
				m_usTimerID[m_usTimerWriteIndex] = MMPF_OS_StartTimer(m_glADX2015AccessTime, MMPF_OS_TMR_OPT_ONE_SHOT, (MMPF_OS_TMR_CALLBACK)&ADX2015_IsrTimerCallBack, NULL);
				if (m_usTimerID[m_usTimerWriteIndex] >= MMPF_OS_TMRID_MAX) {
					RTNA_DBG_Str(0, "Error !! : ADX2015 Get OS Timer error !\r\n");
					MMPF_OS_Sleep(m_glADX2015AccessTime);
				}
				else {
					m_usTimerWriteIndex = ((m_usTimerWriteIndex + 1) % MMPF_OS_TMRID_MAX);
				}
				#endif
				
				if (ubRet == 0) {
					MMPF_OS_ReleaseSem(m_RtcAlamSemID);
				}
				
				#if defined(ALL_FW)
				if (adx2015_int_cb_ptr)
				    adx2015_int_cb_ptr(usADX2015IntStatus);
				#endif

				return usADX2015IntStatus;
			}
			
			if (ubRet == 0) {
				MMPF_OS_ReleaseSem(m_RtcAlamSemID);
			}

			ADX2015_RTC_SetAlarmEnable(alarm_id, MMP_FALSE, NULL, NULL);
			
			if (m_RtcCallBack[alarm_id - 1] != NULL) {
				(*m_RtcCallBack[alarm_id - 1]) ();
			}
			//MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INT_EN, 0x1E);
			//MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INT_STATUS, 0x2);
			if(m_bADX2015 == MMP_FALSE) {
				MMPF_OS_Sleep(1000);
			}
#endif
		}
		/////////////////////////////////////////////////////////////////////////////
		//
		/////////////////////////////////////////////////////////////////////////////
		else {
			RTNA_DBG_Str(0, "ADX2015 Int processing error !\r\nusADX2015IntStatus =");
			RTNA_DBG_Short(0, usADX2015IntStatus);
			RTNA_DBG_Str(0, "\r\n");
		}
	}

#ifdef ENABLE_PMU_INT_TIMER	
	m_usTimerID[m_usTimerWriteIndex] = MMPF_OS_StartTimer(m_glADX2015AccessTime, MMPF_OS_TMR_OPT_ONE_SHOT, (MMPF_OS_TMR_CALLBACK)&ADX2015_IsrTimerCallBack, NULL);
	if (m_usTimerID[m_usTimerWriteIndex] >= MMPF_OS_TMRID_MAX) {
		RTNA_DBG_Str(0, "Error !! : ADX2015 Get OS Timer error !\r\n");
		MMPF_OS_Sleep(m_glADX2015AccessTime);
	}
	else {
		m_usTimerWriteIndex = ((m_usTimerWriteIndex + 1) % MMPF_OS_TMRID_MAX);
	}
#endif
	
	#if defined(ALL_FW)
	if (adx2015_int_cb_ptr)
	    adx2015_int_cb_ptr(usADX2015IntStatus);
	#endif
}
#endif		// #ifdef ALL_FW

//------------------------------------------------------------------------------
//  Function    : ADX2015_ADC_Measure
//  Description :
//------------------------------------------------------------------------------
/** @brief The function return the measured voltage.
The function return the measured voltage.
@param[out] level is the return value of voltage (unit: mV)
@return It reports the status of the operation.
*/
#if 0
MMP_ERR ADX2015_ADC_Measure(MMP_USHORT *level)
{
	MMP_ULONG timeout = 0;
	MMP_USHORT get_val = 0;
	MMP_USHORT get_measured_value_low = 0;
 	MMP_USHORT get_measured_value_high = 0;
 	MMP_USHORT VDD_LDO4 = 0;
 	MMP_USHORT voltage = 0; // unit : mV

#if (USE_ADC_SEMI)
    if(MMPF_OS_AcquireSem(m_ADCSemID, 0)) {
		RTNA_DBG_Str0("--E-- m_ADCSemID OSSemPost: Fail!! \r\n");
		return 1;//error
	}
#endif
#if (USE_ADX2015_SEMI)
    if(MMPF_OS_AcquireSem(m_ADX2015SemID, 0)) {
		RTNA_DBG_Str0("--E-- m_ADX2015SemID OSSemPost: Fail!! \r\n");
		return 1;//error
	}
#endif

 	//Enable Battery Measure
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_POWERON_CTL, 0x14);
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_7, 0x01);
	timeout = 0;
	do
	{
		MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_7, &get_val);
		MMPF_OS_Sleep(0x10);
		timeout ++;
	}while((get_val != 0x02) && (timeout < 500));
						
	if (get_val == 0x02)
 	{
		RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "ADC Initialize success\r\n");
 	}
	else
	{
		RTNA_DBG_Str0("--E-- ADC Initialize Fail\r\n");
#if (USE_ADC_SEMI)
    MMPF_OS_ReleaseSem(m_ADCSemID);
#endif		
#if (USE_ADX2015_SEMI)
    	MMPF_OS_ReleaseSem(m_ADX2015SemID);
#endif

		return MMP_SYSTEM_ERR_PMU;			
	}
	
	
	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_8, &get_measured_value_low);
	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_9, &get_measured_value_high);
	voltage = ((get_measured_value_high & 0x03) << 8) | get_measured_value_low;
	
	ADX2015_LDO_GetVoltage(ADX2015_CP_CTL, &VDD_LDO4);
	voltage = (voltage*3*VDD_LDO4)/1024;
	*level = voltage;
	
	#if 0
	RTNA_DBG_Short(ADX2015_DEBUG_LEVEL, get_measured_value_low);
	RTNA_DBG_Short(ADX2015_DEBUG_LEVEL, get_measured_value_high);
	RTNA_DBG_Short(ADX2015_DEBUG_LEVEL, VDD_LDO4);
	RTNA_DBG_Short(ADX2015_DEBUG_LEVEL, (MMP_USHORT)*level);
	#endif
	//Disable Battery Measure
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_POWERON_CTL, 0x03);

#if (USE_ADC_SEMI)
    MMPF_OS_ReleaseSem(m_ADCSemID);
#endif
#if (USE_ADX2015_SEMI)
	MMPF_OS_ReleaseSem(m_ADX2015SemID);
#endif

	return MMP_ERR_NONE;
}
#endif

MMP_ERR ADX2015_ADC_EnableAVDDCheck(MMP_UBYTE enable)
{
    MMP_USHORT get_val=0;

#if (USE_ADC_SEMI)
     if(MMPF_OS_AcquireSem(m_ADCSemID, 0)) {
		RTNA_DBG_Str(0, "m_ADCSemID OSSemPost: Fail!! \r\n");
		return 1;//error
	}
#endif

    MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_POWERON_CTL, &get_val);        
    if(enable){
        MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_POWERON_CTL, get_val | 0x07);
    }
    else{
        MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_POWERON_CTL, get_val & (~0x07));
    }
#if (USE_ADX2015_SEMI)
	MMPF_OS_ReleaseSem(m_ADX2015SemID);
#endif
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_ADC_Measure_key
//  Description : //Karl
//------------------------------------------------------------------------------
/** @brief The function return the measured voltage.
The function return the measured voltage.
@param[out] level is the return value of voltage (unit: mV)
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_ADC_Measure_Key( MMP_ULONG *level, MMP_UBYTE *source, ADX2015_ADC_TYPE type)
{
	MMP_ULONG  timeout = 0,voltage = 0,KeyVoltage = 0;
	MMP_USHORT get_val = 0;
	MMP_USHORT get_measured_value_low = 0,get_measured_value_high = 0,ADX_Value = 0;
	MMP_UBYTE  adc_sel;
#if defined(ALL_FW)
#if (USE_ADC_SEMI)
     if(MMPF_OS_AcquireSem(m_ADCSemID, 0)) {
		RTNA_DBG_Str(0, "m_ADCSemID OSSemPost: Fail!! \r\n");
		return 1;//error
	}
#endif
#endif
#if (USE_ADX2015_SEMI)
    if(MMPF_OS_AcquireSem(m_ADX2015SemID, 0)) {
		RTNA_DBG_Str(0, "m_ADX2015SemID OSSemPost: Fail!! \r\n");
		return 1;//error
	}
#endif

	switch(type)
	{
		case ADX2015_ADC_AUX1:
		adc_sel = 0x10;
		//Enable Battery Measure
	    MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_POWERON_CTL, &get_val);
	    MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_POWERON_CTL, get_val | 0x08);
	    MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_0, 0x03);
		break;
		case ADX2015_ADC_AUX2:
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_0, 0x05);
		adc_sel = 0x10;
		break;
		case ADX2015_ADC_AUX3:
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_0, 0x09);
		adc_sel = 0x10;
		break;
		case ADX2015_ADC_AUX4:
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_0, 0x11);
		adc_sel = 0x10;
		break;
		case ADX2015_ADC_WIPER:
		adc_sel = 0x40;
		break;
		case ADX2015_ADC_TP_PRE:
		adc_sel = 0x08;
		break;
		case ADX2015_ADC_X_CO:
		adc_sel = 0x04;
		break;
		case ADX2015_ADC_Y_CO:
		adc_sel = 0x02;
		break;
	}
	//MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_POWERON_CTL, 0x07); //Mark test
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_2, 0xB1);	
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_5, 0x8C);  //Enable ADC	
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, adc_sel); 
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_6, 0x01); 
	
	//MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_DCDC_1_CTL1, &get_val);
	//printc("ADX2015_DCDC_1_CTL1 : 0x%x\r\n",get_val);
	//MMPF_OS_Sleep(2);
	timeout = 0;
	do
	{
	    
		MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_6, &get_val);
		timeout ++;		
		
		get_val &= 0x03;
		
	}while(((get_val&0x02) != 0x00) && (timeout < 6));
	if(timeout>=6)
	{
		#if defined(ALL_FW)
		printc("TIMEOUT! read 2003 [0x%02X]=(0x%02X) type : %d\n\r", ADX2015_TP_6, get_val,type);
		#endif
	}	
	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_8, &get_measured_value_low);
	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_9, &get_measured_value_high);	
	*source = 0;
	*source |= (get_measured_value_high & 0x70) >> 4;
		
	//Transfer voltage to key
	voltage = ((get_measured_value_high & 0x03) << 8) | get_measured_value_low;	
	KeyVoltage =(MMP_ULONG)(((MMP_ULONG64)voltage*ADX2015_ADC_VOLTAGE)/1024); //mV
	*level = (MMP_ULONG)KeyVoltage;
	
    // Disable Keypad ADC measure   
	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, &ADX_Value);
	ADX_Value &= ~adc_sel;
	
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, ADX_Value);
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_5, 0x80);
	
	//Disable Battery Measure
    MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_POWERON_CTL, &get_val);
    MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_POWERON_CTL, get_val & (~0x08));
	
	//MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_POWERON_CTL, 0x03); //Mark test
#if defined(ALL_FW)
#if (USE_ADC_SEMI)
    MMPF_OS_ReleaseSem(m_ADCSemID);
#endif
#endif
#if (USE_ADX2015_SEMI)
    MMPF_OS_ReleaseSem(m_ADX2015SemID);
#endif

	return MMP_ERR_NONE;
}

#if 0
//------------------------------------------------------------------------------
//  Function    : ADX2015_ADC_Measure_WIPER
//  Description :
//------------------------------------------------------------------------------
/** @brief The function return the measured voltage.
The function return the measured voltage.
@param[out] level is the return value of voltage (unit: mV)
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_ADC_Measure_WIPER( MMP_ULONG *level, MMP_UBYTE *source)
{
	
	MMP_ULONG  timeout = 0,voltage = 0,KeyVoltage = 0;
	MMP_USHORT get_val = 0;
	MMP_USHORT get_measured_value_low = 0,get_measured_value_high = 0,ADX_Value = 0;
	//MMP_USHORT ADC_Not_Stable = 0;
	//MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_POWERON_CTL, 0x14); //Battery
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_2, 0xB1);
	//MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_2, &get_val);
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_5, 0x8C);  //Enable ADC
	//MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_5, &get_val);
	//MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, 0x60);  //aux2,WIPER
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, 0x40);  //WIPER
	//MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, 0x20);  //aux2
	//MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, 0x10);  //aux1
	//MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, &get_val);
	

	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_6, 0x01); 
	//MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_DCDC_2_CTL2, &get_val);
	//printc("ADX2015_DCDC_2_CTL2 : 0x%x\r\n",get_val);
	timeout = 0;
	do
	{
	    
		MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_6, &get_val);
		timeout ++;		
		
		get_val &= 0x03;
		
	}while(((get_val&0x02) != 0x00) && (timeout < 6));
	if(timeout>=6)
	{
		#if defined(ALL_FW)
		printc("TIMEOUT! read 2003 [0x%02X]=(0x%02X) ADX2015_ADC_Measure()\n\r", ADX2015_TP_6, get_val);
		#endif
	}
	
	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_8, &get_measured_value_low);
	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_9, &get_measured_value_high);
	//printc("get_measured_value_high : 0x%x\r\n",get_measured_value_high);
	*source = 0;
	*source |= (get_measured_value_high & 0x70) >> 4;
	//printc("source : 0x%x\r\n",*source);
	//Transfer voltage to key
	voltage = ((get_measured_value_high & 0x03) << 8) | get_measured_value_low;	
	KeyVoltage =(MMP_ULONG)(((MMP_ULONG64)voltage*ADX2015_ADC_VOLTAGE)/1024); //mV
	*level = (MMP_ULONG)KeyVoltage;
	//printc("voltage : 0x%x\r\n",*level);
	
    // Disable Keypad ADC measure   
	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, &ADX_Value);
	//ADX_Value &= 0xDF; //AUX2
	//ADX_Value &= 0x9F;   //AUX2,WIPER
	ADX_Value &= 0xBF; //WIPER
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, ADX_Value);
	MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_5, 0x80);
	return MMP_ERR_NONE;
}
#endif

//------------------------------------------------------------------------------
//  Function    : ADX2015_ADC_Measure_Lens_Temp
//  Description :
//------------------------------------------------------------------------------
/** @brief The function return the measured voltage.
The function return the measured voltage.
@param[out] level is the return value of voltage (unit: mV)
@return It reports the status of the operation.
*/
MMP_ERR ADX2015_ADC_Measure_Lens_Temp( MMP_ULONG *level, MMP_UBYTE *source)
{
	#define ADX2015_ADC_TEMP_VOLTAGE 3300
	MMP_ULONG  timeout = 0,voltage = 0,KeyVoltage = 0;
	MMP_USHORT get_val = 0;
	MMP_USHORT get_measured_value_low = 0,get_measured_value_high = 0,ADX_Value = 0;
	MMP_ERR		status = MMP_ERR_NONE;

#if USE_ADC_SEMI
     if(MMPF_OS_AcquireSem(m_ADCSemID, 0)) {
		#if defined(ALL_FW)
		printc("m_ADCSemID OSSemPost: Fail!! \r\n");
		#endif
		return 1;//error
	}
#endif

	//MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_POWERON_CTL, 0x14); //Battery
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_2, 0xB1);
	//MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_2, &get_val);
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_5, 0x8C);  //Enable ADC
	//MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_5, &get_val);
	
	#if (ADC_SETTINGS_FOR_EP2 == 1)
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, 0x40);  // wiper
	#else
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, 0x02);  // XP-BR
	#endif
	
	//MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, 0x40);  //WIPER
	//MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, 0x20);  //aux2
	//MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, 0x10);  //aux1
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, &get_val);
	//printc("ADX2015_TP_1 : 0x%x\r\n",get_val);

	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_6, 0x01); 
	//MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, &get_val);
	//printc("ADX2015_CHIP_INTA_STATUS : 0x%x\r\n",get_val);
	timeout = 0;
	do
	{
	    
		status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_6, &get_val);
		timeout ++;		
		
		get_val &= 0x03;
		
	}while(((get_val&0x02) != 0x00) && (timeout < 6));
	if(timeout>=6)
	{
		#if defined(ALL_FW)
		printc("TIMEOUT! read 2003 [0x%02X]=(0x%02X) ADX2015_ADC_Measure()\n\r", ADX2015_TP_6, get_val);
		#endif
#if USE_ADC_SEMI
    MMPF_OS_ReleaseSem(m_ADCSemID);
#endif
		
		return MMP_SYSTEM_ERR_CMDTIMEOUT;
	}
	
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_8, &get_measured_value_low);
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_9, &get_measured_value_high);
	//printc("get_measured_value_high : 0x%x\r\n",get_measured_value_high);
	*source = 0;
	*source |= (get_measured_value_high & 0x70) >> 4;
	// printc("source : 0x%x\r\n",*source);
	
	//Transfer digital value to voltage  
	voltage = ((get_measured_value_high & 0x03) << 8) | get_measured_value_low;	
	KeyVoltage =(MMP_ULONG)(((MMP_ULONG64)voltage*ADX2015_ADC_TEMP_VOLTAGE)/1024); //mV
	*level = (MMP_ULONG)KeyVoltage;
	// printc("voltage : 0x%x\r\n",*level);
	
    // Disable ADC measure   
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, &ADX_Value);
	//ADX_Value &= 0xDF; //AUX2
	//ADX_Value &= 0x9F;   //AUX2,WIPER
	
	#if (ADC_SETTINGS_FOR_EP2 == 1)
	ADX_Value &= ~0x40;
	#else
	ADX_Value &= 0xFD; //
	#endif
		
	//ADX_Value &= 0xBF; //WIPER
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_1, ADX_Value);
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_TP_5, 0x80);

#if USE_ADC_SEMI
    MMPF_OS_ReleaseSem(m_ADCSemID);
#endif

	// return MMP_ERR_NONE;
	return status;
}

MMP_USHORT ADX2015_Measure_Power_Key(void)
{
	MMP_USHORT get_val;

	MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, &get_val);
	get_val &= (ADX2015_INT_EVENT_PWRK_PRESS | ADX2015_INT_EVENT_PWRK_REL | ADX2015_INT_EVENT_PWRK2_PRESS | ADX2015_INT_EVENT_VBUS | ADX2015_INT_EVENT_IR);

	if (get_val)
		MMPF_I2cm_WriteReg(&gI2cmAttribute_ADX2015, ADX2015_CHIP_INTA_STATUS, get_val);

	return get_val;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_GetIntPinState
//  Description : Get the status of the 2003 inttrupt from the cpu side.
//------------------------------------------------------------------------------
/** @brief The function return the measured voltage.
Get the status of the 2003 inttrupt from the cpu side.

@param[in] bGetNewData -
        TRUE  - Getting the new data from the register.
        FALSE - Using the previous data keeped in memory.
@return The value of the status.
*/

MMP_UBYTE ADX2015_GetIntPinState(MMP_BOOL bGetNewData )
{
    #define REG_POC_INT_STATUS_FOR_CPU    0x80008F85
	static MMP_UBYTE ubIntState = 0x0;
    MMP_UBYTE * pIntData;

    if( bGetNewData )
    {
        pIntData = (MMP_UBYTE*)REG_POC_INT_STATUS_FOR_CPU;
        ubIntState = *pIntData;        
    }

	{
	    RTNA_DBG_Str(ADX2015_DEBUG_LEVEL,"----------------------->0x80008F85:");
		RTNA_DBG_Byte(ADX2015_DEBUG_LEVEL, ubIntState);
		RTNA_DBG_Str(ADX2015_DEBUG_LEVEL,"\r\n");
	}
    
    return ubIntState;
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_GetChargeState
//  Description :
//------------------------------------------------------------------------------
/** @brief The function is get the charge state.

The function is get the charge state.
@return 0: No charge (Full), 1: In charge.
*/
MMP_UBYTE ADX2015_GetChargeState(void)
{
	MMP_ERR		status = MMP_ERR_NONE;
	MMP_USHORT	chargeState;

    RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "ADX2015_GetChargeState -\r\n");
    
#if (USE_ADX2015_SEMI)
    if(MMPF_OS_AcquireSem(m_ADX2015SemID, 0)) {
		RTNA_DBG_Str(0, "--E-- m_ADX2015SemID OSSemPost: Fail!! \r\n");
		return 1;//error
	}
#endif

	status = MMPF_I2cm_ReadReg(&gI2cmAttribute_ADX2015, ADX2015_BATCHR_BCCR7, &chargeState);

#if (USE_ADX2015_SEMI)
    MMPF_OS_ReleaseSem(m_ADX2015SemID);
#endif
	
	if(status != MMP_ERR_NONE) {
		return 1;   // error
	}

#if 0
    if (chargeState & 0x01)
        RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "In Charge\r\n");
#endif

	return (chargeState & 0x01);
}

//------------------------------------------------------------------------------
//  Function    : ADX2015_GetIrdaData
//  Description :
//------------------------------------------------------------------------------
/** @brief The function is get the IRDA state.

The function is get the IRDA state.
IR data is valid when the member data_valid is true.
*/
MMP_ERR ADX2015_GetIrdaData(ADX2015_IR_DATA *ir_data)
{
    RTNA_DBG_Str(ADX2015_DEBUG_LEVEL, "ADX2015_GetIrdaData -\r\n");
    
	MEMCPY((void *) ir_data, (void *) &m_ir_data, sizeof(ADX2015_IR_DATA));
	m_ir_data.data_updated = MMP_FALSE;
	
	return MMP_ERR_NONE;
}
#endif //#if (ADX2015_EN)
