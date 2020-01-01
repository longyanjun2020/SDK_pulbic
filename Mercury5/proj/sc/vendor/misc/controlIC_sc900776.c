//==============================================================================
//
//  File        : controlIC_sc900776.c
//  Description : 
//  Author      : Ben Lu
//  Revision    : 1.0
//
//==============================================================================


#include "mmpf_i2cm.h"

//==============================================================================
//
//                              MACRO for different environment
//
//==============================================================================
#include "mmpf_pio.h"  	
#include "mmpf_i2cm.h"  
#include "controlIC_sc900776.h"	
#include "lib_retina.h"
#include "config_fw.h"

#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV1)
static MMP_I2CM_ATTR gI2cmAttribute_uUsbSwitch = {MMP_I2CM_GPIO, SC900776_I2C_SLAVE_ADDR, 8, 8, 0x20, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, 0, 0, 0, 200000/*SW support max 200KHZ*/, MMP_TRUE, MMP_GPIO29, MMP_GPIO30, MMP_FALSE, MMP_FALSE, MMP_FALSE, 0};
#endif

void MMPF_PMP_USB_Debug(void)
{
	#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV1)
	 MMP_USHORT usData = 0, i = 0;
	 MMP_USHORT Array1[6] = {0x13,0x14,0x20,0x21,0x22,0x23};
	 
	 RTNA_DBG_Str(0, "====================\r\n");
	 for(i=0 ; i <0xE;i++) {
	 	MMPF_I2cm_ReadReg(&gI2cmAttribute_uUsbSwitch, i, &usData);
	 	RTNA_DBG_Str(0, "Reg address:");
	 	RTNA_DBG_Long(0,i);
	 	RTNA_DBG_Str(0, "   Value:");
	 	RTNA_DBG_Long(0,usData);
	 	RTNA_DBG_Str(0, "\r\n");
	 }
	
	
	 for(i=0 ; i <0x6;i++) {
	 	MMPF_I2cm_ReadReg(&gI2cmAttribute_uUsbSwitch, Array1[i], &usData);
	 	RTNA_DBG_Str(0, "Reg address:");
	 	RTNA_DBG_Long(0,Array1[i]);
	 	RTNA_DBG_Str(0, "   Value:");
	 	RTNA_DBG_Long(0,usData);
	 	RTNA_DBG_Str(0, "\r\n");
	 }
	  RTNA_DBG_Str(0, "====================\r\n\r\n");
	 #endif
}

//------------------------------------------------------------------------------
//  Function    : MMPF_PMP_USB_INIT
//  Description :
//------------------------------------------------------------------------------
/** @brief The function Initialize the USB switch chip by I2C.

The function Initialize the USB switch chip by I2C. 
@param[in] void
@return void.
*/
void scSwitchUSBPath(void)
{
	#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV1)
	MMPF_PIO_EnableOutputMode(MMP_GPIO29, MMP_TRUE, MMP_TRUE);
	MMPF_PIO_EnableOutputMode(MMP_GPIO30, MMP_TRUE, MMP_TRUE);
	MMPF_PIO_SetData(MMP_GPIO29, GPIO_LOW, MMP_TRUE);  
	MMPF_PIO_SetData(MMP_GPIO30, GPIO_LOW, MMP_TRUE);
	RTNA_WAIT_MS(30);
   
	MMPF_I2cm_Initialize(&gI2cmAttribute_uUsbSwitch);
	RTNA_WAIT_MS(120);
	MMPF_I2cm_WriteReg(&gI2cmAttribute_uUsbSwitch, SC900776_MANUAL_SWITCH1, 0x25);
	MMPF_I2cm_WriteReg(&gI2cmAttribute_uUsbSwitch, SC900776_MANUAL_SWITCH2, 0x14);
	MMPF_I2cm_WriteReg(&gI2cmAttribute_uUsbSwitch, SC900776_CONTROL, 0x1A);
	#endif
	//MMPF_PMP_USB_Debug();
	return;
}


