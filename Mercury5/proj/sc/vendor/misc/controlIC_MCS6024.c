
#include "controlIC_MCS6024.h"
#include "lib_retina.h"
#include "mmpf_i2cm.h"

static MMP_UBYTE       			gbTouchQueueReadIndex = 0, gbTouchQueueWriteIndex = 0;
static sTouchScreenInfoType		TouchScreen_QUEUE[TOUTCH_QUEUE_SIZE];

//The MCS6024 module should run with I2C speed under 250 KB, please double check group 0 PLL settings.
#if (MCS6024_USE_SOFT_I2CM == 0x1)
#if ((HARDWARE_PLATFORM == AIT_PLATFORM_PV1)||(HARDWARE_PLATFORM == SEC_PLATFORM_PV1))
static MMP_I2CM_ATTR gI2cmAttribute_MCS6024; //To be implement;
#endif
#if (HARDWARE_PLATFORM == AIT_PLATFORM_PV2)
static MMP_I2CM_ATTR gI2cmAttribute_MCS6024 = {MMP_I2CM_GPIO, MFS_I2C_SLAVE_ADDR, 8, 8, 0x80, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, 0, 0, 0, 50000/*SW support max 200KHZ*/, MMP_TRUE, MMP_GPIO36, MMP_GPIO37, MMP_FALSE, MMP_FALSE};
#endif
#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV2)
static MMP_I2CM_ATTR gI2cmAttribute_MCS6024 = {MMP_I2CM_GPIO, MFS_I2C_SLAVE_ADDR, 8, 8, 0x80, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, 0, 0, 0, 50000/*SW support max 200KHZ*/, MMP_TRUE, MMP_GPIO38, MMP_GPIO39, MMP_FALSE, MMP_FALSE};
#endif
#else
#if ((HARDWARE_PLATFORM == AIT_PLATFORM_PV1)||(HARDWARE_PLATFORM == SEC_PLATFORM_PV1))
static MMP_I2CM_ATTR gI2cmAttribute_MCS6024; //To be implement;
#endif
#if (HARDWARE_PLATFORM == AIT_PLATFORM_PV2)
static MMP_I2CM_ATTR gI2cmAttribute_MCS6024 = {MMP_I2CM2, MFS_I2C_SLAVE_ADDR, 8, 8, 0x2, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_TRUE, 0, 0, 4, 50000, MMP_TRUE, NULL, NULL, MMP_FALSE, MMP_FALSE};
#endif
#if (HARDWARE_PLATFORM == SEC_PLATFORM_PV2)
static MMP_I2CM_ATTR gI2cmAttribute_MCS6024 = {MMP_I2CM2, MFS_I2C_SLAVE_ADDR, 8, 8, 0x2, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_TRUE, 0, 0, 5, 50000, MMP_TRUE, NULL, NULL, MMP_FALSE, MMP_FALSE};
#endif 
#endif


extern MMPF_OS_MQID  	MidTaskWork_QId;



static void MCS6024_SetRegister( MMP_UBYTE reg_addr, MMP_UBYTE *reg_val, MMP_UBYTE reg_len )
{
	MMP_UBYTE i;
	MMP_USHORT master_write_buf[MAX_BURST_REG_NUM];
	  
	if (reg_len > MAX_BURST_REG_NUM )
	{
		RTNA_DBG_Str(0, "MCS6024 driver SetReg error !\r\n");
	  	return;
	}
	  
	for( i = 0; i < reg_len; i++){
		master_write_buf[i] = (MMP_USHORT)reg_val[i];
	}
	  
	MMPF_I2cm_WriteBurstData(&gI2cmAttribute_MCS6024, reg_addr, master_write_buf, reg_len, MMP_TRUE);
}


static void MCS6024_GetRegister( MMP_UBYTE reg_addr, MMP_UBYTE *reg_val, MMP_UBYTE reg_len )
{
	MMP_UBYTE i = 0;	
	MMP_USHORT master_read_buf[MAX_BURST_REG_NUM]; 
  	
  	if (reg_len > MAX_BURST_REG_NUM )
	{
		RTNA_DBG_Str(0, "MCS6024 driver GetReg error !\r\n");
	  	return;
	}
	
	MMPF_I2cm_ReadBurstData(&gI2cmAttribute_MCS6024, reg_addr, master_read_buf, reg_len);
	for (i=0; i < reg_len; i++) {
		reg_val[i] = (MMP_UBYTE)master_read_buf[i];
	}
}

MMP_ERR MCS6024_GetPosition(void)
{
	sTouchScreenInfoType screen_info;	 
	MMP_UBYTE master_read_buf[TOUCHSCREEN_BURST_REG_NUM] = {0};
	
	MCS6024_GetRegister(0x9,  master_read_buf, 4);
	screen_info.z_posi = master_read_buf[0];
	screen_info.dev_status = master_read_buf[1] & MFS_DEV_STATUS_MASK;
	screen_info.x_coord = (master_read_buf[1] & MFS_XCOORD_MASK) << 3;
	screen_info.y_coord = (master_read_buf[1] & MFS_YCOORD_MASK) << 5;
	screen_info.x_coord += master_read_buf[2];
	screen_info.y_coord += master_read_buf[3];
	touchScreen_InsertToQueue(&screen_info);
	#if 1
	RTNA_DBG_PrintShort(0, screen_info.x_coord); 
	RTNA_DBG_PrintShort(0, screen_info.y_coord);
	#endif
	
	return MMP_ERR_NONE;		
}

void MCS6024_ISR(MMP_GPIO_PIN piopin)
{
	MMPF_OS_PutMessage(MidTaskWork_QId, (void *)(&MCS6024_GetPosition));
}


static void MCS6024_Initial(void)
{
	MMP_UBYTE mode1 = 0x02;
	volatile MMP_UBYTE *ptr_TSP_Int = (volatile MMP_UBYTE*)0x80009D37;
	
	ptr_TSP_Int[0] = 0x24;  //Touch panel interrupt pin pull high
	MMPF_I2cm_Initialize(&gI2cmAttribute_MCS6024);  
	MCS6024_SetRegister(TSI_RMI_ADDR_OPERATING_MODE, &(mode1), 1);

	MMPF_PIO_Initialize();
	MMPF_PIO_EnableOutputMode(MCS6024_INTR_GPIO, MMP_FALSE, MMP_TRUE);
	MMPF_PIO_EnableTrigMode(MCS6024_INTR_GPIO, GPIO_H2L_EDGE_TRIG, MMP_TRUE, MMP_TRUE);
	MMPF_PIO_EnableInterrupt(MCS6024_INTR_GPIO, MMP_TRUE, 0, (GpioCallBackFunc *)MCS6024_ISR, MMP_TRUE);
}



#if 0 // for IDE function name list by section
void __CUS_TSP_INTERFACE__(){}
#endif
void touchScreen_Initial(void) {
	MCS6024_Initial();
}
void touchScreen_GetRegister( MMP_UBYTE reg_addr, MMP_UBYTE *reg_val, MMP_UBYTE reg_len ) {
	MCS6024_GetRegister( reg_addr, reg_val, reg_len );
}
void touchScreen_SetRegister( MMP_UBYTE reg_addr, MMP_UBYTE *reg_val, MMP_UBYTE reg_len ) {
	MCS6024_SetRegister(reg_addr, reg_val, reg_len );
}

MMP_ERR touchScreen_ReadFromQueue( sTouchScreenInfoType *screenInfo) {

	if (((gbTouchQueueWriteIndex + 1) % TOUTCH_QUEUE_SIZE) == gbTouchQueueReadIndex) {
		screenInfo->queueStatus = TOUCH_QUEUE_FULL_DATA;
		
		//For customer's request, if the queue full, send back the latest position information
		screenInfo->dev_status  = TouchScreen_QUEUE[gbTouchQueueWriteIndex - 1].dev_status;
		screenInfo->x_coord 	= TouchScreen_QUEUE[gbTouchQueueWriteIndex - 1].x_coord;
		screenInfo->y_coord 	= TouchScreen_QUEUE[gbTouchQueueWriteIndex - 1].y_coord;
		screenInfo->z_posi 		= TouchScreen_QUEUE[gbTouchQueueWriteIndex - 1].z_posi;
		return MMP_ERR_NONE;
	}
	
	if (gbTouchQueueWriteIndex == gbTouchQueueReadIndex) {
		screenInfo->queueStatus = TOUCH_QUEUE_NO_DATA;
		return MMP_ERR_NONE;
	}
	
	screenInfo->queueStatus = TouchScreen_QUEUE[gbTouchQueueReadIndex].queueStatus;
	screenInfo->dev_status  = TouchScreen_QUEUE[gbTouchQueueReadIndex].dev_status;
	screenInfo->x_coord 	= TouchScreen_QUEUE[gbTouchQueueReadIndex].x_coord;
	screenInfo->y_coord 	= TouchScreen_QUEUE[gbTouchQueueReadIndex].y_coord;
	screenInfo->z_posi 		= TouchScreen_QUEUE[gbTouchQueueReadIndex].z_posi;
	
	gbTouchQueueReadIndex = ((gbTouchQueueReadIndex +1) % TOUTCH_QUEUE_SIZE);
	
	return MMP_ERR_NONE;
}


MMP_ERR touchScreen_InsertToQueue( sTouchScreenInfoType *screenInfo) {
	
	if (((gbTouchQueueWriteIndex + 1) % TOUTCH_QUEUE_SIZE) == gbTouchQueueReadIndex) {
		//Queue Full, Drop the information
		return MMP_ERR_NONE;
	}
	
	TouchScreen_QUEUE[gbTouchQueueWriteIndex].queueStatus  	= TOUCH_QUEUE_DADA;
	TouchScreen_QUEUE[gbTouchQueueWriteIndex].dev_status  	= screenInfo->dev_status;
	TouchScreen_QUEUE[gbTouchQueueWriteIndex].x_coord 		= screenInfo->x_coord;
	TouchScreen_QUEUE[gbTouchQueueWriteIndex].y_coord	 	= screenInfo->y_coord ;
	TouchScreen_QUEUE[gbTouchQueueWriteIndex].z_posi  		= screenInfo->z_posi;
	
	gbTouchQueueWriteIndex = ((gbTouchQueueWriteIndex +1) % TOUTCH_QUEUE_SIZE);
	return MMP_ERR_NONE;
}

MMP_ERR touchScreen_EmptyQueue(void) {
	
	gbTouchQueueReadIndex = 0;
	gbTouchQueueWriteIndex = 0;
	return MMP_ERR_NONE;
}

MMP_ERR touchScreen_EnterFwUpg(void) {
	return MMP_ERR_NONE;
}