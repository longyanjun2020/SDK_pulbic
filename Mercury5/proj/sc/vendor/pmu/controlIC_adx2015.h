
#ifndef _CONTROLIC_ADX2015_H_
#define _CONTROLIC_ADX2015_H_

#include "config_fw.h"

#if (ADX2015_EN)
#include "mmpf_pio.h"
#include "mmpf_i2cm.h"
#include "controlIC_reg_ADX2015.h"
#include "aitu_calendar.h"

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================
//Software I2CM
//#define ADX2015_SLAVE_ADDR		0x24

//HW I2CM
#define ADX2015_SLAVE_ADDR		0x12

#define ADX2015_LEVEL_BIT		0x3F
#define ADX2015_RTC_LMASK		0x0F
#define ADX2015_RTC_START_YEAR	2000
#define ADX2015_RTC_MAX_YEAR	2089

#define ADX2015_LDO_EN			0xC0
#define ADX2015_LDO_MAX_LEVEL	0x1F
#define ADX2015_DCDC_BUCK_EN	0x40
#define ADX2015_DCDC_REG_SIZE	0x06
#define ADX2015_CLASSG_MAX_VOL	0x4E
#define ADX2015_DCDC_DISEN		0x80

#define ADX2015_OPT_CTRL_REG1	0xA4
#define ADX2015_OPT_CTRL_REG2	0xA5
#define ADX2015_OPT_ACCESS_ADDR	0xA6
#define ADX2015_OPT_WRITE_DATA	0xA7
#define ADX2015_OPT_READ_DATA	0xA8

#define ADX2015_SEM_TIMEOUT   	0x0
#define ADX2015_WDT_EN 			0x1  // 1: To turn-on watch-dog timer,  0: turn-off
#define ADX2015_DEBUG_LEVEL	   		0x3
#define ADX2015_ISR_DEBUG_LEVEL		0x3
#define ADX2015_RTC_DEBUG_LEVEL		0x3

#define ADX2015_ACT_DISCHARGE	0x1

typedef MMP_USHORT (*ADX2015_INT_CB_PTR)(MMP_USHORT);

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================


typedef enum _ADX2015_DCDC_ID
{
	ADX2015_DCDC_ID_1 = 0x0,
	ADX2015_DCDC_ID_2,
	ADX2015_DCDC_ID_3,
	ADX2015_DCDC_MAX
} ADX2015_DCDC_ID;

typedef enum _ADX2015_LDO_ID
{
	ADX2015_LDO_ID_1 = 0x0,
	ADX2015_LDO_ID_2,
	ADX2015_LDO_ID_3,
//	ADX2015_LDO_ID_4,
//	ADX2015_LDO_ID_5,
	ADX2015_LDO_MAX
} ADX2015_LDO_ID;

typedef enum _ADX2015_ALARM_ID
{
	ADX2015_ALARM_ID_NONE = 0x0,
	ADX2015_ALARM_ID_A,
	ADX2015_ALARM_ID_B,
	ADX2015_ALARM_MAX
} ADX2015_ALARM_ID;

typedef enum _ADX2015_INTA_EVENT
{	
	ADX2015_INT_EVENT_NONE			= 0x00,
	ADX2015_INT_EVENT_DCIN			= 0x01,
	ADX2015_INT_EVENT_IR			= 0x02,
	ADX2015_INT_EVENT_USBJIG		= 0x04,
	ADX2015_INT_EVENT_VBUS			= 0x08,
	ADX2015_INT_EVENT_PWRK2_PRESS 	= 0x10,
	ADX2015_INT_EVENT_PWRK_REL 		= 0x20,
	ADX2015_INT_EVENT_PWRK_PRESS 	= 0x40,
	ADX2015_INT_EVENT_BGROUP 		= 0x80,
	ADX2015_INT_EVENT_MAX
} ADX2015_INTA_EVENT;

typedef enum _ADX2015_INTB_EVENT
{
	ADX2015_INT_EVENT_DCOUT			= 0x08,
	ADX2015_INT_EVENT_FIRST_ON		= 0x10,
	ADX2015_INT_EVENT_WAKE 			= 0x20,
	ADX2015_INT_EVENT_RTC2			= 0x40,		//In ADX2012, for alarm B only
	ADX2015_INT_EVENT_RTC			= 0x80		//In ADX2012, for alarm A only
} ADX2015_INTB_EVENT;

typedef enum _ADX2015_POWER_ON_STATUS_FLG
{	
	ADX2015_OCP1_FLG    			= 0x01,
	ADX2015_OCP2_FLG			    = 0x02,
	ADX2015_OCP3_FLG			    = 0x04,
	ADX2015_USBJIG_FLG      		= 0x08,
	ADX2015_VBUS_FLG	    		= 0x10,
	ADX2015_POWERKEY2_DIG        	= 0x20,
	ADX2015_POWERKEY1_DIG 		    = 0x40,
	ADX2015_NPOR 	                = 0x80
} ADX2015_POWER_ON_STATUS_FLG;

typedef struct _ADX2015_SEL_TABLE
{	
    MMP_USHORT  bkxsel;
    MMP_USHORT  output;
    MMP_USHORT  offset;	
} ADX2015_SEL_TABLE;

typedef struct _ADX2015_IR_DATA
{	
    MMP_UBYTE	data_updated;
    MMP_UBYTE	id;
    MMP_UBYTE	id_bar;
    MMP_UBYTE	key_code;
    MMP_UBYTE	repeat_times;
    MMP_UBYTE	reserved[3];
} ADX2015_IR_DATA;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================
MMP_ERR ADX2015_Initialize(void);
MMP_ERR ADX2015_LDO_SetVoltage(ADX2015_LDO_ID ldoID, MMP_USHORT vLevel);
MMP_ERR ADX2015_LDO_GetVoltage(ADX2015_LDO_ID ldoID, MMP_USHORT* returnVoltage);
MMP_ERR ADX2015_DCDC_SetVoltage(ADX2015_DCDC_ID dcdcID, MMP_USHORT vLevel);
MMP_ERR ADX2015_DCDC_GetVoltage(ADX2015_DCDC_ID dcdcID, MMP_USHORT* returnVoltage);
MMP_ERR ADX2015_CLASSG_En(MMP_BOOL bEnable);
MMP_ERR ADX2015_CLASSG_SetVol(MMP_UBYTE vol_db);
MMP_ERR ADX2015_Set_ChargeI(MMP_USHORT iset);
MMP_ERR ADX2015_RTC_Initialize(void);
MMP_ERR ADX2015_RTC_SetTime(AUTL_DATETIME *ptr);
MMP_ERR ADX2015_RTC_GetTime(AUTL_DATETIME *ptr);
MMP_ERR ADX2015_RTC_SetAlarmEnable(ADX2015_ALARM_ID id, MMP_BOOL bEnable, AUTL_DATETIME *ptr, void* p_callback);
MMP_ERR ADX2015_CheckBootComplete(MMP_ULONG ulMilliSecond, MMP_GPIO_PIN pio_power_key);
void 	ADX2015_IsrHandler(MMP_ULONG arg);
MMP_ERR ADX2015_PowerOff(void);
MMP_ERR ADX2015_EnableLDO(ADX2015_LDO_ID ldoID, MMP_BOOL bEnable);
MMP_ERR ADX2015_EnableDCDC(ADX2015_DCDC_ID dcdcID, MMP_BOOL bEnable);
//MMP_ERR ADX2015_ADC_Measure(MMP_USHORT *level);
MMP_ERR ADX2015_ActiveDisaharge_En(MMP_BOOL bEnable);

#if (ADX2015_WDT_EN == 0x1)
MMP_ERR ADX2015_WDT_CleanStatus(void);
MMP_ERR ADX2015_WDT_Reset(void);
MMP_ERR ADX2015_WDT_Enable(MMP_BOOL bEnable);
MMP_ERR ADX2015_WDT_SetTimeOut(MMP_ULONG ulMilleSec);
#endif

MMP_USHORT ADX2015_Measure_Power_Key(void);
MMP_ERR ADX2015_write_reg(ADX2015_REG regNAME, MMP_UBYTE nValue);
MMP_ERR ADX2015_read_reg(ADX2015_REG regNAME, MMP_USHORT *returnValue);
MMP_ERR ADX2015_ADC_Measure_Key( MMP_ULONG *level, MMP_UBYTE *source, ADX2015_ADC_TYPE type);
MMP_ERR ADX2015_ADC_Measure_Lens_Temp( MMP_ULONG *level, MMP_UBYTE *source);
MMP_UBYTE ADX2015_GetIntPinState(MMP_BOOL bGetNewData );
MMP_UBYTE ADX2015_GetChargeState(void);
MMP_UBYTE ADX2015_Get_DCIN_INT(void);
MMP_UBYTE ADX2015_Get_DCIN_Status(void);
MMP_UBYTE ADX2015_Get_IR_INT(void);

MMP_ERR ADX2015_OTP_Read(MMP_UBYTE ubReg, MMP_USHORT *ubData);

void ADX2015_INT_CB_Func_Register(void *func_ptr);

MMP_UBYTE ADX2015_Get_VBUS_Status(void);

MMP_ERR ADX2015_Set_I_Limit(MMP_UBYTE bLimit);
MMP_ERR ADX2015_Enable_DC_Path(MMP_UBYTE bEnable);

MMP_USHORT ADX2015_BKXSEL_To_Voltage(MMP_USHORT regSetting);
MMP_UBYTE ADX2015_Voltage_To_BKXSEL(MMP_USHORT voltage);
MMP_USHORT ADX2015_LDOXSEL_To_Voltage(MMP_USHORT regSetting);
MMP_UBYTE ADX2015_Voltage_To_LDOXSEL(MMP_USHORT voltage);

MMP_ERR ADX2015_GetIrdaData(ADX2015_IR_DATA *ir_data);

#endif      // #if (ADX2015_EN)

#endif      // #ifndef _CONTROLIC_ADX2015_H_
