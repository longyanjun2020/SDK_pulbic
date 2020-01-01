//==============================================================================
//
//  File        : MMPC_USB_MAX14577.c
//  Description : 
//  Author      : Bossino Huang
//  Revision    : 1.0
//
//==============================================================================

#include "MMPC_USB_MAX14577.h"
#include "mmpf_i2cm.h"
#include "lib_retina.h"
#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV2)
static MMP_I2CM_ATTR gI2cmAttribute_MAX14577 = {MMP_I2CM_GPIO, (MAX14577_ADDR<<1), 8, 8, 0x0, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, 0, 0, 0, 200000/*SW support max 200KHZ*/, MMP_TRUE, MMP_GPIO38, MMP_GPIO39, MMP_FALSE, MMP_FALSE, MMP_FALSE, 0};
#endif

MMP_ERR MMPC_USB_Initialize(void)
{
	#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV2)
	MMP_ERR retval;
	MMP_USHORT	 tempValue;
	static MMP_BOOL driverInit = MMP_FALSE;

	if (driverInit == MMP_FALSE) {  //Put the init code that should be called only once
		// Device ID check
		retval = MMPF_I2cm_ReadReg(&gI2cmAttribute_MAX14577, (MMPC_USB_Reg)MMPC_USB_Reg_DEVICEID, &tempValue);
		if(retval != MMP_ERR_NONE)
		{
			RTNA_DBG_Str(0, "---MAX14577 DeviceID fail---\r\n");
			return -1;
		}
		
		if(tempValue != MAX14577_DeviceID)
		{
			RTNA_DBG_Str(0, "MAX14577 get DeviceID:");
			RTNA_DBG_Long(0, tempValue);
			RTNA_DBG_Str(0, " \r\n ");
			return -1;
		}
		driverInit = MMP_TRUE;
	}
	// Register initial
	#endif
	return  MMP_ERR_NONE;
}

MMP_ERR MMPC_USB_SetReg(MMPC_USB_Reg reg_addr, MMP_UBYTE reg_val)
{
	#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV2)
	MMP_ERR retval;
	
	if(reg_addr < MAX14577_REG_MAX)
	{
		retval = MMPF_I2cm_WriteReg(&gI2cmAttribute_MAX14577, (MMP_USHORT)reg_addr, reg_val);
		if(retval != MMP_ERR_NONE)
		{
			RTNA_DBG_Str(0, "---MAX14577_SetRegister error---\r\n\r\n");		
		}
	}
	else
	{
		RTNA_DBG_Str(0, "---Set Register range error---\r\n\r\n");		
	}
	#endif
	return  MMP_ERR_NONE;
}


MMP_ERR MMPC_USB_GetReg(MMPC_USB_Reg reg_addr, MMP_USHORT *reg_val)
{
	#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV2)
	MMP_ERR retval;
	
	if(reg_addr < MAX14577_REG_MAX)
	{
		retval = MMPF_I2cm_ReadReg(&gI2cmAttribute_MAX14577, (MMP_USHORT)reg_addr, reg_val);
		if(retval != MMP_ERR_NONE)
		{
			RTNA_DBG_Str(0, "---MAX14577_GetRegister error---\r\n\r\n");
			return -1;		
		}
	}
	else
	{
		RTNA_DBG_Str(0, "---Get Register range error---\r\n\r\n");
		return -1;
	}
	#endif
	return  MMP_ERR_NONE;
}


MMP_ERR MMPC_USB_DetectVBus5V(MMP_USHORT *retVal){

	#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV2)
	MMP_USHORT value;
	
	MMPC_USB_GetReg((MMPC_USB_Reg)MMPC_USB_Reg_STATUS2, &value);
	if(value & 0x40)
	{
		*retVal = MMP_TRUE;
	}
	else
	{
		*retVal = MMP_FALSE;
	}
	#endif
	return MMP_ERR_NONE;
}

void MMPC_USB_RegTestFunc(MMP_GPIO_PIN piopin)
{
	#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV2)
	MMP_ERR retval;
	MMP_USHORT	 usData, i;
	
	retval = MMPC_USB_GetReg((MMPC_USB_Reg)MMPC_USB_Reg_DEVICEID, &usData);
	if(retval != MMP_ERR_NONE)
	{
		RTNA_DBG_Str(0, "---MAX14577 DeviceID fail---\r\n");
	}
	
	if(usData != MAX14577_DeviceID)
	{
		RTNA_DBG_Str(0, "MAX14577 temp DeviceID:");
		RTNA_DBG_Long(0, usData);
		RTNA_DBG_Str(0, " \r\n ");
	}

	RTNA_DBG_Str(0, "---MAX14577 Register---\r\n");
	for(i=0;i<MAX14577_REG_MAX;i++)
	{
		usData = 0;

		MMPC_USB_GetReg((MMPC_USB_Reg)i, &usData);
		
		RTNA_DBG_Byte(0, i);
		RTNA_DBG_Str(0, " reg: ");
		RTNA_DBG_Long(0, usData);
		RTNA_DBG_Str(0, " \r\n ");
	}
	
	RTNA_DBG_Str(0, "Write Test: \r\n");
	
	retval = MMPC_USB_SetReg((MMPC_USB_Reg)MMPC_USB_Reg_CONTROL3, 0xA5);
	retval = MMPC_USB_GetReg((MMPC_USB_Reg)MMPC_USB_Reg_CONTROL3, &usData);
	RTNA_DBG_Str(0, "MMPC_USB_Reg_CONTROL3 (0x0E):");
	RTNA_DBG_Long(0, usData);
	RTNA_DBG_Str(0, " \r\n ");
	#endif
}

