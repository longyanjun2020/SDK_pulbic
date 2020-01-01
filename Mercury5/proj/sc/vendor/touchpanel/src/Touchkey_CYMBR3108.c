/*===========================================================================
 * Include files
 *===========================================================================*/

#include "Config_SDK.h"
#include "Touchkey_CYMBR3108.h"
#include "AIT_Init.h"
#include "mmpf_touchpanel.h"
#include "drv_bus_i2c.h"
#include "drv_i2c_common.h"
#include "hal_bus_i2c.h"

#if defined(SUPPORT_TOUCH_KEY)&&(SUPPORT_TOUCH_KEY)

#define APK_WAIT_FLG				MMP_FALSE//MMP_TRUE
#define APK_READ_ITEM_GROUP_NUM		(2)
#define TOUCH_POWER_OFF				0x01
#define TOUCH_POWER_ON				0X00
#define TOUCH_KEY_REPEAT_TIME		300
#define APK_NEW_TCH_FW				(1)
#define DBG_TOUCH_KEY				(1)

#if DBG_TOUCH_KEY
#define Touch_printc	printc
#else
#define Touch_printc(...)
#endif

TouchChipStatus		g_TouchKeyStatus = TOUCH_CHIP_STATUS_HWRST;
extern MMP_ULONG	glAhcBootComplete;

static const I2COptions_t	Touch_gI2CCfg = 
{
	TOUCH_PANEL_I2C_SLAVE_ADDRESS,  // nSlaveID
	HAL_HWI2C_PORT0,				//I2C Channel
	//HAL_HWI2C_PORT3, 			// nChannel		LCD_GPIO14 & LCD_GPIO15
	I2C_PAD_MODE_1,                 // ePadNum		I2C_PAD_MODE_2={LCD_D14~D15},	I2C_PAD_MODE_1={SR1_GPIO3~4}
	0,                              // bDMAenable
	0,                              // u32DMAAddr
	1,                              // bReStart
	I2C_SLOWSPEED_MODE_200KHZ,      // eClockSpeed
	I2C_CTRL_MODE_HW,               // eControlMode
	I2C_SEN_TYPE_OTHER,             // eSensorType
	I2C_ONE_BYTE_DATA,              // eDataLen
	I2C_ONE_BYTE_ADDR,              // eAddrLen
};

/* Project: C:\CY_project\APICAL_Projects\CY8CMBR3108_APK_20160921\CY8CMBR3108_APK_2016.cprj
 * Generated: 2016/9/21 22:37:41 +08:00 */
#if 0
const MMP_USHORT CY8CMBR3108_configuration[128] = {
    0xE4u, 0x00u, 0xE4u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x7Fu, 0x7Fu, 0x64u, 0x7Fu,
    0x7Fu, 0x64u, 0x64u, 0x64u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x03u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x80u,
    0x05u, 0x00u, 0x00u, 0x02u, 0x00u, 0x02u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x01u, 0x01u,
    0x04u, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x14u, 0x03u, 0x01u, 0x50u,
    0x00u, 0x37u, 0x01u, 0x00u, 0x00u, 0x0Au, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x82u, 0x3Eu
};
#else
const MMP_USHORT CY8CMBR3108_configuration[128] = {
    0xE4u, 0x00u, 0xE4u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x7Fu, 0x7Fu, 0xC8u, 0x7Fu,
    0x7Fu, 0xC8u, 0xC8u, 0xC8u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x03u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x80u,
    0x05u, 0x00u, 0x00u, 0x02u, 0x00u, 0x02u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x01u, 0x01u,
    0x04u, 0xFFu, 0xFFu, 0xFFu, 0xFFu, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x14u, 0x03u, 0x01u, 0x50u,
    0x00u, 0x37u, 0x01u, 0x00u, 0x00u, 0x0Au, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u,
    0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x00u, 0x55u, 0x2Au
};
#endif

MMP_ERR TouchPanel_Get_Reg_Data(MMP_USHORT RegStartAddr,MMP_UBYTE* RegData,MMP_UBYTE ReadLen)
{
	s32				i2c_handle = 0;
	I2COptions_t	i2c_cfg;
	I2CErrorCode_e	i2c_err = I2C_PROC_DONE;
	MMP_UBYTE AddrBuf[2];
		
    if(!RegData) 
        return MMP_HIF_ERR_PARAMETER;
	
	memcpy(&i2c_cfg, &Touch_gI2CCfg, sizeof(I2COptions_t));
	
	i2c_err = DrvI2cOpen(&i2c_handle, &i2c_cfg);
	if (i2c_err != I2C_PROC_DONE) {
		RTNA_DBG_Str0("read err - 1\r\n");
		return MMP_PERIPHERAL_ERR_OPEN;
	}

	AddrBuf[0] = RegStartAddr & 0xff;
	#if 1	
	i2c_err = DrvI2cWrite(i2c_handle,(void*)AddrBuf, 1, 0);
	if (i2c_err != I2C_PROC_DONE) {
		DrvI2cClose(i2c_handle);
		RTNA_DBG_Str0("read err - 2\r\n");
		return MMP_PERIPHERAL_ERR_ACCESS;
	}
	#endif

	i2c_err = DrvI2cRead(i2c_handle, (void*)RegData, ReadLen);
	if (i2c_err != I2C_PROC_DONE) {
		DrvI2cClose(i2c_handle);
		RTNA_DBG_Str0("read err - 3\r\n");
		return MMP_PERIPHERAL_ERR_ACCESS;
	}
	
	DrvI2cClose(i2c_handle);
	
	return MMP_ERR_NONE;                  
}

MMP_ERR TouchPanel_Set_Reg_Data(MMP_USHORT RegStartAddr,MMP_UBYTE* RegData,MMP_UBYTE WriteLen)
{
	s32				i2c_handle = 0;
	u8				i2c_data[250],i;
	I2COptions_t	i2c_cfg;
	I2CErrorCode_e	i2c_err = I2C_PROC_DONE;
	
    if(!RegData || !WriteLen) 
        return MMP_HIF_ERR_PARAMETER;
	
	memcpy(&i2c_cfg, &Touch_gI2CCfg, sizeof(I2COptions_t));
	
   i2c_err = DrvI2cOpen(&i2c_handle,&i2c_cfg);
	if (i2c_err != I2C_PROC_DONE) {
		return MMP_PERIPHERAL_ERR_OPEN;
	}

	i2c_data[0] = RegStartAddr&0XFF; // Sub-address.
	//i2c_data[0] = ((RegStartAddr>>8)&0XFF); // Sub-address.
	//i2c_data[1] = (RegStartAddr&0XFF);

	memcpy(&i2c_data[1],RegData,WriteLen);
	
	i2c_err = DrvI2cWrite(i2c_handle, (void*)i2c_data, WriteLen+1, 0);
	if (i2c_err != I2C_PROC_DONE) {
		DrvI2cClose(i2c_handle);
		RTNA_DBG_Str0("write err - 1\r\n");
		return MMP_PERIPHERAL_ERR_ACCESS;
	}
	
	DrvI2cClose(i2c_handle);
	
	return MMP_ERR_NONE;               
}

AHC_BOOL GetTouchKeyIntStatus(void)
{
	return AHC_FALSE;
}

MMP_UBYTE g_uRdData[128] = {0};

MMP_BOOL g_bIsInitDone = MMP_FALSE;

#if defined(APK_NEW_TCH_FW)&&(APK_NEW_TCH_FW)
MMP_BOOL ApkTchIcInitEx(void)
{
	g_bIsInitDone = MMP_TRUE;
	return MMP_TRUE;
}

#else
MMP_BOOL ApkTchIcInitEx(void)
{
	UINT8 uRet = 0;
	MMP_ERR eRet = MMP_ERR_NONE;
	MMP_UBYTE uRegVal[8] = {0};
	MMP_UBYTE uTemp = 0;
	UINT8 i = 0;
	UINT8 uCnt = 0;

	do
	{
		//通过读取IC  来唤醒IC
		do
		{
			//eRet = MMPF_I2cm_ReadReg(&m_I2cmAttr_TouchKey, 0x7E, &uTemp);
			eRet = TouchPanel_Get_Reg_Data(0x7E,&uTemp,1);
			if (eRet == MMP_ERR_NONE)
			{
				printc("[APK]ApkTchIcInitEx-Wake IC OK!Reg[7Eh]=0x%02X\r\n", uTemp);
				break;
			}
			uCnt++;
			//MMPC_System_WaitUs(100);
		}while(uCnt < 20);

		if (uCnt >= 20)
		{
			uRet = 1;
			break;
		}

#if 1
		//读取原有配置，看是否原来已经配置过
		for (i = 0; i < 8; i++)
		{
			//eRet = MMPF_I2cm_ReadReg(&m_I2cmAttr_TouchKey, (0x78 + i), (MMP_USHORT*)&(uRegVal[i]));
			eRet = TouchPanel_Get_Reg_Data((0x78 + i),&uRegVal[i],1);
			if (eRet != MMP_ERR_NONE)
			{
				//break;
			}
		}

		if (0 ==memcmp(uRegVal, &(CY8CMBR3108_configuration[0x78]), (sizeof(MMP_USHORT) * 8)))
		{
			break;
		}
#endif

		//原来没有配置过--开始配置
		printc("[APK]ApkTchIcInitEx--Start config IC!!!\r\n");
		for (i = 0; i < 128; i++)
		{
			//eRet = MMPF_I2cm_WriteReg(&m_I2cmAttr_TouchKey, i, (CY8CMBR3108_configuration[i]));
			eRet = TouchPanel_Set_Reg_Data(i,CY8CMBR3108_configuration[i],1);
			if (eRet != MMP_ERR_NONE)
			{
				break;
			}
		}

		if (i < 128)
		{
			uRet = 2;
			break;
		}

		//让IC  将配置写入内部FLASH
		uRegVal[0] = 0x02;
		//eRet = MMPF_I2cm_WriteReg(&m_I2cmAttr_TouchKey, 0x86, uRegVal[0]);
		eRet = TouchPanel_Set_Reg_Data(0x86,uRegVal[0],1);
		if (eRet != MMP_ERR_NONE)
		{
			uRet = 3;
			break;
		}
		MMPF_OS_Sleep(1000);

		//读取出来比对一下
		for (i = 0; i < 128; i++)
		{
			//eRet = MMPF_I2cm_ReadReg(&m_I2cmAttr_TouchKey, i, (MMP_USHORT*)&(g_uRdData[i]));
			eRet = TouchPanel_Get_Reg_Data(i,&g_uRdData[i],1);
		}
		for (i = 0; i < 16; i++)
		{
			printc("[%d]%02X %02X %02X %02X %02X %02X %02X %02X\r\n", i,
				g_uRdData[i*8 + 0], g_uRdData[i*8 + 1], g_uRdData[i*8 + 2], g_uRdData[i*8 + 3],
				g_uRdData[i*8 + 4], g_uRdData[i*8 + 5], g_uRdData[i*8 + 6], g_uRdData[i*8 + 7]);
		}

		//对期间进行Reset
		uRegVal[0] = 0xFF;
		//eRet = MMPF_I2cm_WriteReg(&m_I2cmAttr_TouchKey, 0x86, uRegVal[0]);
		eRet = TouchPanel_Set_Reg_Data(0x86,uRegVal[0],1);
		if (eRet != MMP_ERR_NONE)
		{
			uRet = 4;
			break;
		}

		//通过读取IC  来唤醒IC
		do
		{
			//eRet = MMPF_I2cm_ReadReg(&m_I2cmAttr_TouchKey,0x7E, &uTemp);
			eRet = TouchPanel_Get_Reg_Data(0x7E,&uTemp,1);
			if (eRet == MMP_ERR_NONE)
			{
				printc("[APK]Re_Wake IC OK!%02X\r\n", uTemp);
				break;
			}
			uCnt++;
			MMPF_OS_Sleep(10);
		}while(uCnt < 20);

		if (uCnt >= 20)
		{
			uRet = 5;
			break;
		}
	}while(0);

	if (uRet)
	{
		printc("[APK]ApkTchIcInitEx--Failed!uRet=%d\r\n", uRet);
		return MMP_FALSE;
	}
	else
	{
		printc("[APK]ApkTchIcInitEx--Success\r\n");
		g_bIsInitDone = MMP_TRUE;
		return MMP_TRUE;
	}
	
}
#endif

static void InitTouchKeyGpio( MMP_GPIO_PIN piopin,GpioCallBackFunc* CallBackFunc)
{
    if(piopin == MMP_GPIO_MAX)
		return;
	
	Touch_printc("%s,POWER OFF->ON\r\n",__func__);
	TouchKeySetStatus(TOUCH_CHIP_STATUS_POWERON);
	
	#if defined(CTRL_TOUCH_KEY_POWER)&&(CTRL_TOUCH_KEY_POWER)
	MMPF_PIO_EnableOutputMode(APK_TOUCH_KEY_PWR, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(APK_TOUCH_KEY_PWR, TOUCH_POWER_OFF, MMP_TRUE);
    MMPF_OS_Sleep(60);
	MMPF_PIO_SetData(APK_TOUCH_KEY_PWR, TOUCH_POWER_ON, MMP_TRUE);
	#endif
	
	TouchKeySetStatus(TOUCH_CHIP_STATUS_INIT);
	MMPF_OS_Sleep(100);
	ApkTchIcInitEx();
	
    //Set GPIO as input mode
    MMPF_PIO_Enable(piopin, MMP_TRUE);
    MMPF_PIO_EnableOutputMode(piopin, MMP_FALSE, MMP_TRUE);
	#if defined(APK_NEW_TCH_FW)&&(APK_NEW_TCH_FW)
	// Set the trigger mode.
    MMPF_PIO_EnableTrigMode(piopin, GPIO_L2H_EDGE_TRIG, MMP_TRUE, MMP_TRUE);
	#else
    // Set the trigger mode.
    MMPF_PIO_EnableTrigMode(piopin, GPIO_H2L_EDGE_TRIG, MMP_TRUE, MMP_TRUE);
	#endif
    //Enable Interrupt
    MMPF_PIO_EnableInterrupt(piopin, MMP_TRUE, 0, (GpioCallBackFunc *)CallBackFunc, MMP_TRUE);

}

#if defined(APK_NEW_TCH_FW)&&(APK_NEW_TCH_FW)
MMP_ULONG TouchKey_GetKeyEvent(void)
{
#define NEW_KEY_VALUE1 	0x08
#define NEW_KEY_VALUE2 	0x04
#define NEW_KEY_VALUE3 	0x02
#define NEW_KEY_VALUE4 	0x01

	MMP_ERR eRet = MMP_ERR_NONE;
	MMP_ULONG retEvent = KEYPAD_NONE;
	MMP_UBYTE uTchMode[4] = {0};
	static MMP_ULONG ulPre = 0;
	MMP_ULONG  ulNow = 0,uTickDelta = TOUCH_KEY_REPEAT_TIME,ulabs;
	
	MMPF_OS_GetTime(&ulNow);
	if(ulNow > ulPre)
		ulabs = ulNow - ulPre;
	else
		ulabs = (0xffffffff-ulPre)+ulNow;
	
	if (ulabs < uTickDelta)
	{
		//printc(FG_BLUE("[APK]Click too fast!\r\n"));
		return KEYPAD_NONE;
	}

	if (!g_bIsInitDone)
	{
		return retEvent;
	}

	//eRet = MMPF_I2cm_ReadBurstDataApk(&m_I2cmAttr_TouchKey,0,uTchMode,4);
	eRet = TouchPanel_Get_Reg_Data(0x00,uTchMode,4);
	if (eRet == MMP_ERR_NONE)
	{
		if(0 != uTchMode[0])
		{
			switch(uTchMode[0])
			{
			case NEW_KEY_VALUE1:
				retEvent = APK_FUNC_KEY1;
				break;

			case NEW_KEY_VALUE2:
				retEvent = APK_FUNC_KEY2;
				break;

			case NEW_KEY_VALUE3:
				retEvent = APK_FUNC_KEY3;
				break;

			case NEW_KEY_VALUE4:
				retEvent = APK_FUNC_KEY4;
				break;

			default:
				retEvent = KEYPAD_NONE;
				break;
			}

			printc("%s,send event %x\r\n",__func__,retEvent);
		}
	}
	else
	{
		printc("[APK]TouchKey_GetKeyEvent--Failed!!!\r\n");
	}

	if(retEvent != KEYPAD_NONE)
	{
		ulPre = ulNow;
	}
	
	return retEvent;
}
#else
MMP_ULONG TouchKey_GetKeyEvent(void)
{
#define KEY_VALUE1 	0x04
#define KEY_VALUE2 	0x80
#define KEY_VALUE3 	0x40
#define KEY_VALUE4 	0x20

	MMP_ERR eRet = MMP_ERR_NONE;
	MMP_ULONG retEvent = KEYPAD_NONE;
	MMP_UBYTE uTchFlg = 0;
	static MMP_ULONG ulPre = 0;
	MMP_ULONG  ulNow = 0,uTickDelta = TOUCH_KEY_REPEAT_TIME,ulabs;
	
	MMPF_OS_GetTime(&ulNow);
	if(ulNow > ulPre)
		ulabs = ulNow - ulPre;
	else
		ulabs = (0xffffffff-ulPre)+ulNow;
	
	if (ulabs < uTickDelta)
	{
		//printc(FG_BLUE("[APK]Click too fast!\r\n"));
		return KEYPAD_NONE;
	}

	if (!g_bIsInitDone)
	{
		return retEvent;
	}
	
	//eRet = MMPF_I2cm_ReadBurstDataApk(&m_I2cmAttr_TouchKey,0xAA,&uTchFlg,1);
	eRet = TouchPanel_Get_Reg_Data(0xaa,&uTchFlg,1);
	if (eRet == MMP_ERR_NONE)
	{
		if(0 != uTchFlg)
		{
			switch(uTchFlg)
			{
			case KEY_VALUE1:
				retEvent = APK_FUNC_KEY1;
				break;

			case KEY_VALUE2:
				retEvent = APK_FUNC_KEY2;
				break;

			case KEY_VALUE3:
				retEvent = APK_FUNC_KEY3;
				break;

			case KEY_VALUE4:
				retEvent = APK_FUNC_KEY4;
				break;

			default:
				retEvent = KEYPAD_NONE;
				break;
			}

			Touch_printc("%s,send event %x\r\n",__func__,retEvent);
		}
	}
	else
	{
		Touch_printc("%s,--Read Failed!\r\n",__func__);
	}
	
	if(retEvent != KEYPAD_NONE)
	{
		ulPre = ulNow;
	}
	
	return retEvent;
}
#endif

static void TOUCH_KEY_ISR(MMP_GPIO_PIN piopin)
{
	if(glAhcBootComplete == MMP_TRUE)
	{
    	SetKeyPadEvent(TOUCH_KEY_PRESS);
	}
	Touch_printc(FG_BLUE("### CYMBR3108 TOUCH_KEY_ISR.\r\n"));
}

void ApkWaitAtiBusyFlg(void)
{
	Touch_printc(FG_BLUE("ApkWaitAtiBusyFlg!\r\n"));
}

void TouchPanel_Config_SlaveAddr(int SlaveAddr)
{
    // Interrupt pin. Need to pull high to active.
    // Low   - Touch down
    // Hight - No touch

    MMPF_PIO_EnableOutputMode(TOUCH_RESET_GPIO, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_EnableOutputMode(TOUCH_PANEL_INT_GPIO, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(TOUCH_RESET_GPIO, 0x00, MMP_TRUE);
    MMPF_PIO_SetData(TOUCH_PANEL_INT_GPIO, 0x00, MMP_TRUE);
	
    MMPF_OS_Sleep(60);

    MMPF_PIO_SetData(TOUCH_RESET_GPIO, 0x01, MMP_TRUE);
    //MMPF_OS_Sleep(40);

    //MMPF_PIO_EnableOutputMode(TOUCH_RESET_GPIO, MMP_FALSE, MMP_TRUE);
    //MMPF_PIO_SetData(TOUCH_PANEL_INT_GPIO, 0x00, MMP_TRUE);
    MMPF_OS_Sleep(200);
    MMPF_PIO_EnableOutputMode(TOUCH_PANEL_INT_GPIO, MMP_FALSE, MMP_TRUE);
}

void TouchKeyI2cInit(void)
{	
	Touch_printc(FG_BLUE("TouchKeyI2cInit++\r\n"));
	
	TouchPanel_Config_SlaveAddr(TOUCH_PANEL_I2C_SLAVE_ADDRESS);
	InitTouchKeyGpio(TOUCH_PANEL_INT_GPIO, (GpioCallBackFunc*) TOUCH_KEY_ISR );
	TouchKeySetStatus(TOUCH_CHIP_STATUS_READVALUE);
	Touch_printc(FG_BLUE("TouchKeyI2cInit Init --\r\n"));
}

MMP_ERR TouchPanel_Init(struct _3RD_PARTY_TOUCHPANEL *pthis)
{   
	TouchKeyI2cInit();
    return MMP_ERR_NONE;
}

void TouchKeySetStatus(TouchChipStatus	TouchKeyStatus)
{
	g_TouchKeyStatus = TouchKeyStatus;
	Touch_printc(FG_BLUE("%s:%x\r\n"),__func__,TouchKeyStatus);
}

TouchChipStatus TouchKeyGetStatus(void)
{
	return g_TouchKeyStatus;
}

void ApkTpCheckUpdate(void)
{
	Touch_printc(FG_BLUE("ApkTpCheckUpdate!\r\n"));
}


void ApkTchDgb(UINT8 uStep)
{
	MMP_UBYTE uRegVal = 0x02;
	MMP_ERR eRet = MMP_ERR_NONE;
	if (uStep == 1)
	{
		uRegVal = 0xAF;
		//eRet = MMPF_I2cm_WriteReg(&m_I2cmAttr_TouchKey, 02, uRegVal);
		eRet = TouchPanel_Set_Reg_Data(0x02,uRegVal,1);
		if (eRet == MMP_ERR_NONE)
		{
			printc("[APK]ApkTchDgb--Write [0x02] 0xAF!Done!\r\n");
		}
	}
	else if (uStep == 2)
	{
		//eRet = MMPF_I2cm_ReadReg(&m_I2cmAttr_TouchKey, 0x86, (MMP_USHORT*)&uRegVal);
		eRet = TouchPanel_Get_Reg_Data(0x86,&uRegVal,1);
		if (eRet == MMP_ERR_NONE)
		{
			printc("[APK]ApkTchDgb--Read [0x86] 0x%02X!Done!\r\n", uRegVal);
		}
	}
	else if (uStep == 3)
	{
		uRegVal = 0x00;
		//eRet = MMPF_I2cm_WriteReg(&m_I2cmAttr_TouchKey, 0x08, uRegVal);
		eRet = TouchPanel_Set_Reg_Data(0x08,uRegVal,1);
		if (eRet == MMP_ERR_NONE)
		{
			printc("[APK]ApkTchDgb--Write [0x08] 0x00!Done!\r\n");
		}
	}
	else if (uStep == 4)
	{
		//eRet = MMPF_I2cm_ReadReg(&m_I2cmAttr_TouchKey, 0x01, (MMP_USHORT*)&uRegVal);
		eRet = TouchPanel_Get_Reg_Data(0x01,&uRegVal,1);
		if (eRet == MMP_ERR_NONE)
		{
			printc("[APK]ApkTchDgb--Read [0x01] 0x%02X!Done!\r\n", uRegVal);
		}
	}
	else if (uStep == 5)
	{
		//eRet = MMPF_I2cm_ReadReg(&m_I2cmAttr_TouchKey, 0x02, (MMP_USHORT*)&uRegVal);
		eRet = TouchPanel_Get_Reg_Data(0x02,&uRegVal,1);
		if (eRet == MMP_ERR_NONE)
		{
			printc("[APK]ApkTchDgb--Read [0x02] 0x%02X!Done!\r\n", uRegVal);
		}
	}
}
int TouchPanel_ReadPosition(struct _3RD_PARTY_TOUCHPANEL *pthis, MMP_USHORT* pX, MMP_USHORT* pY, MMP_UBYTE dir)
{
	MMP_ERR ret = MMP_ERR_NONE; 
	MMP_ULONG ulEvent;
	ulEvent = TouchKey_GetKeyEvent();
	*pX = (MMP_USHORT)(0x0000ffff & ulEvent);
	return ret;
}


MMP_ERR TouchPanel_ReadVBAT1(struct _3RD_PARTY_TOUCHPANEL *pthis, MMP_USHORT* pX, MMP_USHORT* pY, MMP_UBYTE dir )
{
	return MMP_ERR_NONE;
}


void TouchPanel_ResetCtrl(struct _3RD_PARTY_TOUCHPANEL *pthis, MMP_BOOL bOn)
{
    printc("TouchPanel_ResetCtrl : bon %d\r\n",bOn);
}

MMP_BOOL TouchPanel_Attached(struct _3RD_PARTY_TOUCHPANEL *pthis)
{
    return AHC_TRUE;
}

MMP_ERR TouchPanel_IOControl(struct _3RD_PARTY_TOUCHPANEL *pthis, TOUCHPANEL_ATTR *ptouchpanel_attr, MMP_UBYTE cmd, MMP_UBYTE* arg)
{
    return MMP_ERR_NONE;
}

struct _3RD_PARTY_TOUCHPANEL TouchPanel_Obj =
{
    TouchPanel_Init,
    TouchPanel_ReadPosition,
    TouchPanel_ReadVBAT1,
    TouchPanel_ResetCtrl,
    TouchPanel_IOControl,
    TouchPanel_Attached,
};

int Touch_Panel_Module_Init(void)
{
    printc("[Touch_Panel_Module_Init]\r\n");
    MMPF_3RDParty_TouchPanel_Register(&TouchPanel_Obj);
    return 0;
}

#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(Touch_Panel_Module_Init);

#endif	//#if defined(SUPPORT_TOUCH_KEY)&&(SUPPORT_TOUCH_KEY)

