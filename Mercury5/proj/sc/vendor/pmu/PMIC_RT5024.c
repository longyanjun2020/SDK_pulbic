#include "PMIC_RT5024.h"
#include "mmpf_i2cm.h"
#include "mmpf_pio.h"
#include "lib_retina.h"

static MMP_I2CM_ATTR gI2cmAttribute_PMIC_RT5024 = {MMP_I2CM2, 0x12, 8, 8, 0, MMP_FALSE, MMP_TRUE, MMP_FALSE, MMP_FALSE, 0, 0, 2, 250000/*250KHZ*/, MMP_TRUE, NULL, NULL};

MMP_ERR RT5024_ReadReg(MMP_UBYTE ubReg, MMP_USHORT* ubValue)
{
	return MMPF_I2cm_ReadReg(&gI2cmAttribute_PMIC_RT5024, ubReg, ubValue);
}

MMP_ERR RT5024_WriteReg(MMP_UBYTE ubReg, MMP_USHORT ubValue)
{
	return MMPF_I2cm_WriteReg(&gI2cmAttribute_PMIC_RT5024, ubReg, ubValue);
}

MMP_ERR RT5024_Initialize(void)
{
		MMP_USHORT	usRb = 0;
		MMP_ERR		returnvalue = MMP_ERR_NONE;
		
		//Current Limit
		usRb = 0;
		returnvalue = MMPF_I2cm_ReadReg(&gI2cmAttribute_PMIC_RT5024, 0x07, &usRb);
		usRb |= 0x03;
		returnvalue = MMPF_I2cm_WriteReg(&gI2cmAttribute_PMIC_RT5024, 0x07, usRb);
		
		//Charging Current. Default: 200mA
		usRb = 0;
		returnvalue = MMPF_I2cm_ReadReg(&gI2cmAttribute_PMIC_RT5024, 0x08, &usRb);
		usRb &= 0xF0;
		usRb |= 0x01;
		returnvalue = MMPF_I2cm_WriteReg(&gI2cmAttribute_PMIC_RT5024, 0x08, usRb);
		
		//Charging LED low active
		usRb = 0;
		returnvalue = MMPF_I2cm_ReadReg(&gI2cmAttribute_PMIC_RT5024, 0x00, &usRb);
		usRb &= 0xF7;
		usRb &= 0xFE;
		returnvalue = MMPF_I2cm_WriteReg(&gI2cmAttribute_PMIC_RT5024, 0x00, usRb);
			
		//Clear INT Status
		returnvalue = RT5024_ReadReg(0x09, &usRb);
		usRb &= 0xFD;
		returnvalue = RT5024_WriteReg(0x09, usRb);
		
		//CH1
		usRb = 0;
		returnvalue = MMPF_I2cm_ReadReg(&gI2cmAttribute_PMIC_RT5024, 0x04, &usRb);
		usRb &= CH1_MASK;
		usRb |= CH1_5V;
		returnvalue = MMPF_I2cm_WriteReg(&gI2cmAttribute_PMIC_RT5024, 0x04, usRb);

        //CH3
        usRb = 0;
        returnvalue = MMPF_I2cm_ReadReg(&gI2cmAttribute_PMIC_RT5024, 0x05, &usRb);
        usRb |= 0x70;
        returnvalue = MMPF_I2cm_WriteReg(&gI2cmAttribute_PMIC_RT5024, 0x05, usRb);

		//CH8
		usRb = 0;
		returnvalue = MMPF_I2cm_ReadReg(&gI2cmAttribute_PMIC_RT5024, 0x03, &usRb);
		#if (C006_P001_TEST_FLOW)
		usRb &= 0xF0;
		usRb |= 0x02;
		#else
		usRb |= 0x0F;
		#endif
		returnvalue = MMPF_I2cm_WriteReg(&gI2cmAttribute_PMIC_RT5024, 0x03, usRb);
		
		usRb = 0;
		returnvalue = MMPF_I2cm_ReadReg(&gI2cmAttribute_PMIC_RT5024, 0x02, &usRb);
		usRb |= 0x20;
		returnvalue = MMPF_I2cm_WriteReg(&gI2cmAttribute_PMIC_RT5024, 0x02, usRb);

		//CH6
		usRb = 0;
		returnvalue = MMPF_I2cm_ReadReg(&gI2cmAttribute_PMIC_RT5024, 0x06, &usRb);
		usRb &= 0xF0;
		#if (C006_P001_TEST_FLOW)
		usRb |= 0x0A;
		#endif
		returnvalue = MMPF_I2cm_WriteReg(&gI2cmAttribute_PMIC_RT5024, 0x06, usRb);
		
		usRb = 0;
		returnvalue = MMPF_I2cm_ReadReg(&gI2cmAttribute_PMIC_RT5024, 0x02, &usRb);
		usRb |= 0x40;
		returnvalue = MMPF_I2cm_WriteReg(&gI2cmAttribute_PMIC_RT5024, 0x02, usRb);
		
		//CH7
		usRb = 0;
		returnvalue = MMPF_I2cm_ReadReg(&gI2cmAttribute_PMIC_RT5024, 0x02, &usRb);
		usRb |= 0x1F;
		returnvalue = MMPF_I2cm_WriteReg(&gI2cmAttribute_PMIC_RT5024, 0x02, usRb);

		return returnvalue;
}

MMP_ERR RT5024_EnterSuspendMode(void)
{
	MMP_UBYTE	ubReg = 0x07;
	MMP_USHORT	ubValue = 0;
	
	RT5024_ReadReg(ubReg, &ubValue);
	ubValue |= 0x40;
	return RT5024_WriteReg(ubReg, ubValue);
}

MMP_ERR RT5024_ExitSuspendMode(void)
{
	MMP_UBYTE	ubReg = 0x07;
	MMP_USHORT	ubValue = 0;
	
	RT5024_ReadReg(ubReg, &ubValue);
	ubValue &= 0xFB;
	return RT5024_WriteReg(ubReg, ubValue);
}

MMP_ERR RT5024_DisableCharger(void)
{
	MMP_UBYTE	ubReg = 0x07;
	MMP_USHORT	ubValue = 0;
	
	RT5024_ReadReg(ubReg, &ubValue);
	ubValue |= 0x08;
	return RT5024_WriteReg(ubReg, ubValue);
}

MMP_ERR RT5024_EnableCharger(void)
{
	MMP_UBYTE	ubReg = 0x07;
	MMP_USHORT	ubValue = 0;
	
	RT5024_ReadReg(ubReg, &ubValue);
	ubValue &= 0xF7;
	return RT5024_WriteReg(ubReg, ubValue);
}

MMP_BOOL RT5024_CheckBatteryStatus(void)
{
	MMP_UBYTE	ubReg = 0x0A;
	MMP_USHORT	ubValue = 0;
	MMP_USHORT	usRetVal = 0;
	
	//RT5024 Reg0x0A[4] is Battery Status
	RT5024_ReadReg(ubReg, &ubValue);
	
	RTNA_DBG_Str(0, "PMIC 0x0A: ");
	RTNA_DBG_Short(0, ubValue);
	RTNA_DBG_Str(0, "\r\n");
	
	usRetVal = (ubValue & 0x10)	?	0	:	1;
	
	//Clear INT Status
	if(!ubValue)
	{
		ubReg = 0x09;
		RT5024_ReadReg(ubReg, &ubValue);
		ubValue &= 0xFD;
		RT5024_WriteReg(ubReg, ubValue);
	}
	 
	return	usRetVal;
}

MMP_ERR RT5024_SetChargerTimer(MMP_UBYTE ubHour)
{
	MMP_UBYTE	ubReg = 0x07;
	MMP_USHORT	ubValue = 0;
	
	ubHour = (ubHour - 1) & 0x0F;
	
	RT5024_ReadReg(ubReg, &ubValue);
	ubValue &= 0x0F;
	ubValue |= ubHour << 4;
	return RT5024_WriteReg(ubReg, ubValue);
}

MMP_UBYTE RT5024_GetChargerTimer(void)
{
	MMP_UBYTE	ubReg = 0x07;
	MMP_USHORT	ubValue = 0;
	MMP_UBYTE	ubHour = 0;
	
	RT5024_ReadReg(ubReg, &ubValue);
	ubHour = ((ubValue) & 0xF0) >> 4;
	ubHour +=1;

	return ubHour;
}

MMP_BOOL RT5024_GetChargerPGood(void)
{
	MMP_UBYTE	ubReg = 0x0A;
	MMP_USHORT	ubValue = 0;
	RT5024_ReadReg(ubReg, &ubValue);
	
	return (ubValue & 0x04);
}

MMP_ERR RT5024_ChangeCH1(MMP_UBYTE ubCH1Val)
{
	MMP_USHORT	usRb = 0;
	MMP_ERR		returnvalue = 0;

	usRb = 0;
	returnvalue |= MMPF_I2cm_ReadReg(&gI2cmAttribute_PMIC_RT5024, 0x04, &usRb);
	usRb &= CH1_MASK;
	usRb |= ubCH1Val;
	returnvalue |= MMPF_I2cm_WriteReg(&gI2cmAttribute_PMIC_RT5024, 0x04, usRb);
	
	return returnvalue;
}