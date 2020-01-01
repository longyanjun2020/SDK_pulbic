//==============================================================================
//
//  File        : controlIC_AS3607.c
//  Description : 
//  Author      : Ben Lu
//  Revision    : 1.0
//
//==============================================================================
#include "mmp_err.h"
#include "mmpf_typedef.h"
#include "controlIC_AS3607.h"
#include "mmpf_pio.h"
#include "mmpf_i2cm.h"
#include "lib_retina.h"
//==============================================================================
//
//                              MACRO for different environment
//
//==============================================================================
extern MMP_UBYTE	m_bSlaveAddr[I2CM_SW_MAX_COUNT];
extern MMP_UBYTE	m_bI2CDelayTime[I2CM_SW_MAX_COUNT];
extern MMP_ERR MMPF_I2c_Start(MMP_I2CM_ATTR *i2cm_attribute);
extern MMP_ERR MMPF_I2c_Stop(MMP_I2CM_ATTR *i2cm_attribute);
extern MMP_ERR MMPF_I2c_WriteData(MMP_I2CM_ATTR *i2cm_attribute, MMP_UBYTE ubData);
extern MMP_UBYTE  MMPF_I2c_ReadData(MMP_I2CM_ATTR *i2cm_attribute);
extern MMP_ERR MMPF_I2c_GetACK(MMP_I2CM_ATTR *i2cm_attribute);
extern MMP_ERR MMPF_I2c_SendNACK(MMP_I2CM_ATTR *i2cm_attribute);

#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV1)
static MMP_I2CM_ATTR gI2cmAttribute_AS3607 = {MMP_I2CM_GPIO, I2C_AFE_SLAVE_ADDR, 8, 8, 0x2, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, 0, 0, 0, 200000/*SW support max 200KHZ*/, MMP_TRUE, MMP_GPIO29, MMP_GPIO30, MMP_FALSE, MMP_FALSE};


//------------------------------------------------------------------------------
//  Function    : as3607_read_subreg
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used for reading PMU chip's sub registers.

 This function is used for accesing PMU chip's sub registers.
@param[in] reg is main register.
@param[in] reg is sub register of main register.
@param[in] retrunVal is the value of sub-register.
@return It reports the status of the operation.
*/
#if 0
static MMP_ERR as3607_read_subreg(MMP_UBYTE reg, MMP_UBYTE subreg, MMP_UBYTE* returnVal)
{
	
	MMP_UBYTE data[2];
	MMP_UBYTE pmugate = 0;
	MMP_UBYTE	semStatus = 0xFF;
	if(reg > AS607_REG_MAX || !IS_SUBREG(reg))
		return -1;

	semStatus = MMPF_I2cm_StartSemProtect(&gI2cmAttribute_AS3607);
	MMPF_I2cm_Initialize(&gI2cmAttribute_AS3607);
	
	data[0] = AFE_PMU_ENABLE;
	MMPF_I2c_Start(&gI2cmAttribute_AS3607);
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, m_bSlaveAddr[gI2cmAttribute_AS3607.i2cmID - MMP_I2CM_GPIO]);
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
    
	
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, data[0]);
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
	MMPF_I2c_Stop(&gI2cmAttribute_AS3607);
	
	MMPF_I2c_Start(&gI2cmAttribute_AS3607);
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, m_bSlaveAddr[gI2cmAttribute_AS3607.i2cmID - MMP_I2CM_GPIO] + 1);
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
    
	data[1] = MMPF_I2c_ReadData(&gI2cmAttribute_AS3607);
	MMPF_I2c_SendNACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
	MMPF_I2c_Stop(&gI2cmAttribute_AS3607);
	
	
	pmugate = data[1] & 0x08;
	data[1] = pmugate | subreg;
	MMPF_I2c_Start(&gI2cmAttribute_AS3607);
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, m_bSlaveAddr[gI2cmAttribute_AS3607.i2cmID - MMP_I2CM_GPIO]);
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
    
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, data[0]);
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
    
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, data[1]);
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
	MMPF_I2c_Stop(&gI2cmAttribute_AS3607);
	
	
	data[0] = reg;
	MMPF_I2c_Start(&gI2cmAttribute_AS3607);
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, m_bSlaveAddr[gI2cmAttribute_AS3607.i2cmID - MMP_I2CM_GPIO]);
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, data[0]);
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
	MMPF_I2c_Stop(&gI2cmAttribute_AS3607);

	MMPF_I2c_Start(&gI2cmAttribute_AS3607);
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, m_bSlaveAddr[gI2cmAttribute_AS3607.i2cmID - MMP_I2CM_GPIO] + 1);
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
	*returnVal = MMPF_I2c_ReadData(&gI2cmAttribute_AS3607);
	MMPF_I2c_SendNACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
	MMPF_I2c_Stop(&gI2cmAttribute_AS3607);
	
	if (semStatus == MMPF_OS_ERR_NONE) {
		MMPF_I2cm_EndSemProtect(&gI2cmAttribute_AS3607);
	}
	return MMP_ERR_NONE;
}
#endif

//------------------------------------------------------------------------------
//  Function    : as3607_write_reg
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used for writing PMU chip's registers.

 This function is used for writing PMU chip's registers.
@param[in] reg is main register.
@param[in] val is the value set the register.
@return It reports the status of the operation.
*/
static MMP_ERR as3607_write_reg(MMP_UBYTE reg, MMP_UBYTE val)
{
	if(reg > AS3607_REG_MAX)
		return -1;

	MMPF_I2cm_WriteReg(&gI2cmAttribute_AS3607, reg, val);
	return  MMP_ERR_NONE;
}


//------------------------------------------------------------------------------
//  Function    : as3607_write_subreg
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used for writing PMU chip's sub registers.

 This function is used for accesing PMU chip's sub registers.
@param[in] reg is main register.
@param[in] reg is sub register of main register.
@param[in] retrunVal is the value to sub-register.
@return It reports the status of the operation.
*/
static MMP_ERR as3607_write_subreg(MMP_UBYTE reg, MMP_UBYTE subreg, MMP_UBYTE val)
{
	MMP_UBYTE data[2];
	MMP_UBYTE pmugate = 0;
	MMP_UBYTE semStatus = 0;
	if(reg > AS3607_REG_MAX || !IS_SUBREG(reg))
		return -1;

	if((subreg < 1) || (subreg > AFE_SUB_MASK))
		return -1;

	
	semStatus = MMPF_I2cm_StartSemProtect(&gI2cmAttribute_AS3607);
	MMPF_I2cm_Initialize(&gI2cmAttribute_AS3607);
	
	data[0] = AFE_PMU_ENABLE;
	MMPF_I2c_Start(&gI2cmAttribute_AS3607);
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, (m_bSlaveAddr[gI2cmAttribute_AS3607.i2cmID - MMP_I2CM_GPIO]));
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
    
	
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, data[0]);
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
	MMPF_I2c_Stop(&gI2cmAttribute_AS3607);
	
	MMPF_I2c_Start(&gI2cmAttribute_AS3607);
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, m_bSlaveAddr[gI2cmAttribute_AS3607.i2cmID - MMP_I2CM_GPIO] + 1);
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
    
	data[1] = MMPF_I2c_ReadData(&gI2cmAttribute_AS3607);
	MMPF_I2c_SendNACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
	MMPF_I2c_Stop(&gI2cmAttribute_AS3607);
	
	
	pmugate = data[1] & 0x08;
	data[1] = pmugate | subreg;
	MMPF_I2c_Start(&gI2cmAttribute_AS3607);
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, m_bSlaveAddr[gI2cmAttribute_AS3607.i2cmID - MMP_I2CM_GPIO]);
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
    
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, data[0]);
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
    
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, data[1]);
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
    
	MMPF_I2c_Stop(&gI2cmAttribute_AS3607);

	data[0] = reg;
	data[1] = val;
	MMPF_I2c_Start(&gI2cmAttribute_AS3607);
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, m_bSlaveAddr[gI2cmAttribute_AS3607.i2cmID - MMP_I2CM_GPIO]);
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
    
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, data[0]);
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
   
	MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, data[1]);
	MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
	RTNA_WAIT_US(m_bI2CDelayTime[0]);
    
	MMPF_I2c_Stop(&gI2cmAttribute_AS3607);

	if(pmugate != 0x08)
	{
		data[0] = AFE_PMU_ENABLE;
		data[1] = subreg | 0x08;
		MMPF_I2c_Start(&gI2cmAttribute_AS3607);
		MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, m_bSlaveAddr[gI2cmAttribute_AS3607.i2cmID - MMP_I2CM_GPIO]);
		MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
		RTNA_WAIT_US(m_bI2CDelayTime[0]);
    	
		MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, data[0]);
		MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
		RTNA_WAIT_US(m_bI2CDelayTime[0]);
    	
		MMPF_I2c_WriteData(&gI2cmAttribute_AS3607, data[1]);
		MMPF_I2c_GetACK(&gI2cmAttribute_AS3607);
		RTNA_WAIT_US(m_bI2CDelayTime[0]);
    	
		MMPF_I2c_Stop(&gI2cmAttribute_AS3607);
	}
	
	if (semStatus == MMPF_OS_ERR_NONE) {
		MMPF_I2cm_EndSemProtect(&gI2cmAttribute_AS3607);
	}
	return MMP_ERR_NONE;
} 


//------------------------------------------------------------------------------
//  Function    : afeInitBacklight
//  Description :
//------------------------------------------------------------------------------
/** @brief The function Initialize the PMU chip and turn on the backlight.

The function Initialize the PMU chip and turn on the backlight. 
@param[in] void
@return void.
*/
void afeInitBacklight(void)
{
    
	MMPF_I2cm_Initialize(&gI2cmAttribute_AS3607);  
	as3607_write_subreg(AFE_MUX_PMU_REG5, AFE_SUB_BOOST_CURR1, 0x47);
	as3607_write_subreg(AFE_MUX_PMU_REG5, AFE_SUB_BOOST_CURR2, 0x0);
	as3607_write_subreg(AFE_MUX_PMU_REG5, AFE_SUB_BOOST_CTRL2, 0x13);
	as3607_write_subreg(AFE_MUX_PMU_REG5, AFE_SUB_BOOST_CTRL1, 0x83);
}

void afeAdjustVoltage(void)
{
	MMPF_I2cm_Initialize(&gI2cmAttribute_AS3607);
    as3607_write_subreg(0x17, 0x02, 0x38);  
}



//------------------------------------------------------------------------------
//  Function    : afeSetBacklight
//  Description :
//------------------------------------------------------------------------------
/** @brief This function changes the backlight level.

This function changes the backlight level.
@param[in] level is the value between 0~255
@return void.
*/
void afeSetBacklight(MMP_ULONG level)
{
    if(level > 255)
        level = 255;
         
    as3607_write_subreg(AFE_MUX_PMU_REG5, AFE_SUB_BOOST_CURR1, level);
}




//------------------------------------------------------------------------------
//  Function    : afeInitCharger
//  Description :
//------------------------------------------------------------------------------
/** @brief This function initialize AFE charger

This function initialize AFE charger
@return void.
*/
void afeInitCharger(void)
{ 
	as3607_write_subreg(AFE_MUX_PMU_REG3, AFE_SUB_CHG1, 0x5C);	// CHG_I 350mA, CHG_V 4.20V
	as3607_write_subreg(AFE_MUX_PMU_REG3, AFE_SUB_CHG2, 0x00);	// EOC 10% CC
}

//------------------------------------------------------------------------------
//  Function    : afe_backlight_off
//  Description :
//------------------------------------------------------------------------------
/** @brief This function turn off the backlight.

This function turn off the backlight.
@param[in] void
@return void.
*/
void afe_backlight_off(void)
{
	as3607_write_subreg(AFE_MUX_PMU_REG5, AFE_SUB_BOOST_CTRL1, 0x00);
}

//------------------------------------------------------------------------------
//  Function    : afe_system_off
//  Description :
//------------------------------------------------------------------------------
/** @brief This function turn off the PMU chip power.

This function turn off the PMU chip power.
@param[in] void
@return void.
*/
void afe_system_off(void)
{
	as3607_write_reg(AFE_SYSTEM, 0x03);
}

//------------------------------------------------------------------------------
//  Function    : adcMeasure
//  Description :
//------------------------------------------------------------------------------
/** @brief This function is used by ADC device dirver to measure voltage.

 This function is used for accesing PMU chip's sub registers.
@param[in] src is the target to measure, please reference structure eAdc_source_t.
@param[in] result is the voltage value.
@return It reports the status of the operation.
*/
MMP_ERR adcMeasure(eAdc_source_t src, MMP_USHORT* result)
{
	MMP_USHORT val1 = 0;
	MMP_USHORT val2 = 0;
	MMP_UBYTE ch;
	MMP_USHORT val = 0;
	
    ch = src;

	/* Write ADC source.                                                    */
	/* On some chips this automatically starts the meassurement             */
    
	as3607_write_subreg(AFE_MUX_PMU_REG3, AFE_SUB_CHG1, 0x5C);	// CHG_I 350mA, CHG_V 4.20V
	as3607_write_subreg(AFE_MUX_PMU_REG3, AFE_SUB_CHG2, 0x00);	// EOC 10% CC
	as3607_write_reg(ADC_CFG_SRC_REG, ch << ADC_CFG_SRC_LSB);
	RTNA_WAIT_MS(1);
	MMPF_I2cm_ReadReg(&gI2cmAttribute_AS3607, ADC_CFG_RES_LSB_REG, &val1);
	MMPF_I2cm_ReadReg(&gI2cmAttribute_AS3607, ADC_CFG_RES_MSB_REG, &val2);
	/* Convert the result stored in the two registers                       */
	val = (val2 & ADC_CFG_MSB_MASK) << ADC_CFG_MSB_POS;
	*result = val1 | val;

	return MMP_ERR_NONE;
} 

#endif  //(HARDWARE_PLATFORM == SEC_PLATFORM_PV1)
