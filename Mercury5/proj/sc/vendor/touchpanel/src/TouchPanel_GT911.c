/*===========================================================================
 * Include files
 *===========================================================================*/
#include "Config_SDK.h"
#include "TouchPanel_GT911.h"
#include "AIT_Init.h"
#include "mmpf_touchpanel.h"
#include "drv_bus_i2c.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 

#define MMPC_System_WaitMs(x)	AHC_OS_Sleep(x)//MsOS_DelayTask(x)

#if ( DSC_TOUCH_PANEL == TOUCH_PANEL_GT911 )

MMP_UBYTE                   Config[CONFIG_MAX_LENGTH];
extern MMP_ULONG            glAhcBootComplete;
static const I2COptions_t	Touch_gI2CCfg = 
{
	TOUCH_PANEL_I2C_SLAVE_ADDRESS,  // nSlaveID
	0x00,                           // nChannel
	I2C_PAD_MODE_1,                 // ePadNum
	0,                              // bDMAenable
	0,                              // u32DMAAddr
	1,                              // bReStart
	I2C_SLOWSPEED_MODE_200KHZ,      // eClockSpeed
	I2C_CTRL_MODE_HW,               // eControlMode
	I2C_SEN_TYPE_OTHER,             // eSensorType
	I2C_ONE_BYTE_DATA,              // eDataLen
	I2C_TWO_BYTE_ADDR,              // eAddrLen
};

static void TOUCH_ISR(MMP_GPIO_PIN piopin)
{
	if(glAhcBootComplete == MMP_TRUE)
    {
        SetKeyPadEvent(TOUCH_PANEL_PRESS);
	}
}

void InitTouchGpio( MMP_GPIO_PIN piopin,GpioCallBackFunc* CallBackFunc  )
{
    if(piopin == MMP_GPIO_MAX)
		return;
    
  //  printc("InitTouchGpio INT ...\r\n");
    //Set GPIO as input mode
    MMPF_PIO_Enable(piopin, MMP_TRUE);
    MMPF_PIO_EnableOutputMode(piopin, MMP_FALSE, MMP_TRUE);

    // Set the trigger mode.
    MMPF_PIO_EnableTrigMode(piopin, GPIO_H2L_EDGE_TRIG, MMP_TRUE, MMP_TRUE);

    //Enable Interrupt
    MMPF_PIO_EnableInterrupt(piopin, MMP_TRUE, 0, (GpioCallBackFunc *)CallBackFunc, MMP_TRUE);

	
   // printc("InitTouchGpio INT OK\r\n");
}

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

	AddrBuf[0] = (RegStartAddr>>8) & 0xff;	
	AddrBuf[1] = RegStartAddr & 0xff;
	
	i2c_err = DrvI2cWrite(i2c_handle,(void*)AddrBuf, 2, 0); // Set sub-address.
	if (i2c_err != I2C_PROC_DONE) {
		DrvI2cClose(i2c_handle);
		RTNA_DBG_Str0("read err - 2\r\n");
		return MMP_PERIPHERAL_ERR_ACCESS;
	}
	
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
	
	i2c_data[0] = ((RegStartAddr>>8)&0XFF); // Sub-address.
	i2c_data[1] = (RegStartAddr&0XFF);

	memcpy(&i2c_data[2],RegData,WriteLen);
	
	i2c_err = DrvI2cWrite(i2c_handle, (void*)i2c_data, WriteLen+2, 0);
	if (i2c_err != I2C_PROC_DONE) {
		DrvI2cClose(i2c_handle);
		RTNA_DBG_Str0("write err - 1\r\n");
		return MMP_PERIPHERAL_ERR_ACCESS;
	}
	
	DrvI2cClose(i2c_handle);
	
	return MMP_ERR_NONE;               
}

MMP_ERR TouchPanel_Get_IC_Version()
{
    MMP_ERR ret = MMP_ERR_NONE;
    MMP_UBYTE IcVersion[8] = {0};
                  
    ret = TouchPanel_Get_Reg_Data(REG_IC_VERSION,IcVersion,6);
    if(ret == MMP_ERR_NONE)
    {
        printc("TouchPanel_Get_IC_Version,firmware version = %x \r\n",(IcVersion[5]<<8 | IcVersion[4]));
        printc("TouchPanel_Get_IC_Version,IC version = %c%c%c%c_%02x%02x \r\n",
            IcVersion[0],IcVersion[1],IcVersion[2],IcVersion[3],IcVersion[5],IcVersion[4]);
    }
	else
	{
		 printc("Get IC version ERROR \r\n");
	}

    return ret;
}

void TouchPanel_Config_SlaveAddr(int SlaveAddr)
{
    // Interrupt pin. Need to pull high to active.
    // Low   - Touch down
    // Hight - No touch

    MMPF_PIO_EnableOutputMode(TOUCH_RESET_GPIO, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_EnableOutputMode(TOUCH_PANEL_INT_GPIO, MMP_TRUE, MMP_TRUE);
    MMPF_PIO_SetData(TOUCH_RESET_GPIO, 0x01, MMP_TRUE);
    MMPF_PIO_SetData(TOUCH_RESET_GPIO, 0x00, MMP_TRUE);
    MMPF_PIO_SetData(TOUCH_PANEL_INT_GPIO, 0x00, MMP_TRUE);
    MMPC_System_WaitMs(60);

    if(SlaveAddr == 0x14)
    {
        MMPF_PIO_SetData(TOUCH_PANEL_INT_GPIO, 0x01, MMP_TRUE);
    }
    else
    {
        MMPF_PIO_SetData(TOUCH_PANEL_INT_GPIO, 0x00, MMP_TRUE);
    }
    
    MMPC_System_WaitMs(2);

    MMPF_PIO_SetData(TOUCH_RESET_GPIO, 0x01, MMP_TRUE);

    MMPC_System_WaitMs(40);

    MMPF_PIO_EnableOutputMode(TOUCH_RESET_GPIO, MMP_FALSE, MMP_TRUE);
    MMPF_PIO_SetData(TOUCH_PANEL_INT_GPIO, 0x00, MMP_TRUE);
    MMPC_System_WaitMs(200);
    MMPF_PIO_EnableOutputMode(TOUCH_PANEL_INT_GPIO, MMP_FALSE, MMP_TRUE);
}

MMP_ERR TouchPanel_Send_Panel_Config()
{
    int i;
    MMP_ERR ret = MMP_ERR_NONE;

#if SEND_PANEL_CONFIG
    MMP_UBYTE  CheckSum = 0;
    MMP_UBYTE  CheckTemp;
    MMP_UBYTE SensorId;
    MMP_UBYTE *ConfigBuf[] = {CFG_GROUP1, CFG_GROUP2,CFG_GROUP3,CFG_GROUP4,CFG_GROUP5,CFG_GROUP6};
    MMP_UBYTE  ConfigLen[] =  {CFG_GROUP_LEN(CFG_GROUP1), 
                               CFG_GROUP_LEN(CFG_GROUP2),
                               CFG_GROUP_LEN(CFG_GROUP3),
                               CFG_GROUP_LEN(CFG_GROUP4), 
                               CFG_GROUP_LEN(CFG_GROUP5),
                               CFG_GROUP_LEN(CFG_GROUP6)};

    printc("Config Groups Lengths: %d, %d, %d, %d, %d, %d \r\n", 
        ConfigLen[0], ConfigLen[1], ConfigLen[2], ConfigLen[3],ConfigLen[4], ConfigLen[5]);

    if ((ConfigLen[1] == 1) && (ConfigLen[2] == 1) &&
        (ConfigLen[3] == 1) && (ConfigLen[4] == 1) &&
        (ConfigLen[5] == 1))
    {
        SensorId = 0; 
    }
    else
    {
        ret = TouchPanel_Get_Reg_Data(REG_SENSOR_ID,&SensorId,1);
        if(ret != MMP_ERR_NONE)
        {
            printc("failed to read SensorId, using DEFAULT config! \r\n");
            SensorId = 0; 
            if(ConfigLen[0] > 1)
            {
                ConfigBuf[0][0] = 0x00;
            }
        }
        SensorId = SensorId & 0x07;
    }

    printc("%s,SensorId=%d \r\n", __func__,SensorId);

    if(ConfigLen[SensorId] <= 1)
    {
        printc("matches with NULL config,please check!SensorId=%d \r\n", SensorId);
        return MMP_HIF_ERR_PARAMETER;
    }
    
    memset(Config, 0,CONFIG_MAX_LENGTH);
    memcpy(Config, ConfigBuf[SensorId],ConfigLen[SensorId]);

#if CUSTOM_CONFIG
    Config[RESOLUTION_INDEX]     =  MAX_WIDTH&0xff;
    Config[RESOLUTION_INDEX + 1] = (MAX_WIDTH>>8);
    Config[RESOLUTION_INDEX + 2] =  MAX_HEIGHT&0xff;
    Config[RESOLUTION_INDEX + 3] = (MAX_HEIGHT>>8);  
    
    if (INT_TRIGGER == 0)  //RISING
    {
        Config[TRIGGER_INDEX] &= 0xfe; 
    }
    else if (INT_TRIGGER == 1)  //FALLING
    {
        Config[TRIGGER_INDEX] |= 0x01;
    }
#endif  // GTP_CUSTOM_CFG
    
    for (i = 0; i < ConfigLen[SensorId]-2; i++)
    {
        CheckTemp = (MMP_UBYTE)Config[i];
        CheckSum += CheckTemp;
    }
    CheckTemp = (~CheckSum) + 1;
    printc("%s,check sum=%d,sum1=%d\r\n", __func__,Config[ConfigLen[SensorId] - 2],Config[ConfigLen[SensorId] - 1]);
    Config[ConfigLen[SensorId] - 2] = CheckTemp;
    printc("%s,check sum=%d\r\n", __func__,Config[ConfigLen[SensorId] - 2]);

    ret = TouchPanel_Set_Reg_Data(REG_CONFIG_VERSION,Config,ConfigLen[SensorId]);
    if (ret != MMP_ERR_NONE)
    {
        printc("%s,write config data failed \r\n", __func__);
    }  
#else // DRIVER NOT SEND CONFIG
    memset(Config,0,CONFIG_MAX_LENGTH);
    ret = TouchPanel_Get_Reg_Data(REG_CONFIG_VERSION,Config,CONFIG_MAX_LENGTH);
    if (ret != MMP_ERR_NONE)
    {
        printc("%s,read config data failed \r\n", __func__);
    }
    
#endif // GTP_DRIVER_SEND_CFG
    #if 0
    printc(" \r\n"); // here just print the first 24 bytes data
    for(i = 0;i < 24;i++)
    {
        printc("Config[%d] = %x \r\n", i,Config[i]);
    }
    printc(" \r\n");
    #endif
    MMPC_System_WaitMs(50);
    
    return MMP_ERR_NONE;
}

MMP_ERR TouchPanel_Init(struct _3RD_PARTY_TOUCHPANEL *pthis)
{   
    MMP_UBYTE ConfigVersion = 1;

	#if 1
    printc("[TouchPanel_Init]GT911\r\n");
    
    TouchPanel_Config_SlaveAddr(TOUCH_PANEL_I2C_SLAVE_ADDRESS);

    MMPC_System_WaitMs(100);

    TouchPanel_Get_Reg_Data(REG_CONFIG_VERSION,&ConfigVersion,1);
    printc(" TouchPanel_Init,ConfigVersion=%x \r\n",ConfigVersion);
    TouchPanel_Get_IC_Version();
    #endif
    //TouchPanel_Send_Panel_Config();
    
    InitTouchGpio(TOUCH_PANEL_INT_GPIO, (GpioCallBackFunc*) TOUCH_ISR );

    return MMP_ERR_NONE;
}

void TouchPanel_TransformPosition(MMP_USHORT* pX, MMP_USHORT* pY, MMP_UBYTE dir) // Set dir = 0 as lcd normal, 1: reverse.
{
	MMP_USHORT tpRefCenterX, tpRefCenterY,usPanelW,usPanelH;

	#if (TOUCH_IC_PLACEMENT_TYPE == TOUCH_PANEL_DIR_0)
	if(dir)//LCD reverse
	{
		*pX = GT911_ADC_STEPS_X-*pX;
		*pY = GT911_ADC_STEPS_Y-*pY;
	}
	#elif(TOUCH_IC_PLACEMENT_TYPE == TOUCH_PANEL_DIR_1)
	if(dir)
	{
    	*pX = GT911_ADC_STEPS_X-*pX;
	}
    else
    {
        *pY = GT911_ADC_STEPS_Y-*pY;
    }
	#elif(TOUCH_IC_PLACEMENT_TYPE == TOUCH_PANEL_DIR_2)
	if(dir)
	{
    	*pY = GT911_ADC_STEPS_Y-*pY;
	}
    else
    {
        *pX = GT911_ADC_STEPS_X-*pX;
    }
	#elif(TOUCH_IC_PLACEMENT_TYPE == TOUCH_PANEL_DIR_3)
	if(!dir)//LCD Normal
	{
		*pX = GT911_ADC_STEPS_X-*pX;
		*pY = GT911_ADC_STEPS_Y-*pY;
	}
	#endif

    //MAPPING TO RESOLUTION
    tpRefCenterX = *pX;
    tpRefCenterY = *pY;

#if (VERTICAL_LCD == VERTICAL_LCD_DEGREE_0)
    usPanelW = DISP_WIDTH;//RTNA_LCD_GetAttr()->usPanelW;
    usPanelH = DISP_HEIGHT;//RTNA_LCD_GetAttr()->usPanelH;
#elif (VERTICAL_LCD == VERTICAL_LCD_DEGREE_90) || (VERTICAL_LCD == VERTICAL_LCD_DEGREE_270)
    usPanelW = DISP_HEIGHT;//RTNA_LCD_GetAttr()->usPanelH;
    usPanelH = DISP_WIDTH;//RTNA_LCD_GetAttr()->usPanelW;
#endif

    *pX = (tpRefCenterX * usPanelW)/GT911_ADC_STEPS_X;
    *pY = (tpRefCenterY * usPanelH)/GT911_ADC_STEPS_Y;
    printc("%s,pX=%d,pY=%d \r\n", __func__,*pX,*pY);
}
	
int TouchPanel_ReadPosition(struct _3RD_PARTY_TOUCHPANEL *pthis, MMP_USHORT* pX, MMP_USHORT* pY, MMP_UBYTE dir)
{
    MMP_ERR ret = MMP_ERR_NONE; 
    MMP_UBYTE CoorStatus;
    MMP_USHORT i,TouchNum,CmdEndVal = 0x00;
    MMP_UBYTE TouchPoint[MAX_TOUCH_POINT * 8];
    MMP_ULONG  ulNow;
	static MMP_ULONG ulPre = 0;

    //printc("%s,get coordination enter \r\n", __func__);

    ret = TouchPanel_Get_Reg_Data(REG_COOR_STATUS,&CoorStatus,1);
    if(ret != MMP_ERR_NONE) 
    {
        printc("%s,get coordination failed,ret=%x \r\n", __func__,ret);
        goto exit_read; 
    }

    TouchNum = CoorStatus & 0x0f;
    if((CoorStatus & 0x80) == 0 || TouchNum == 0 || TouchNum > MAX_TOUCH_POINT)
    {
        //printc("%s,no touch point,CoorStatus=%x,TouchNum=%d \r\n", __func__,CoorStatus,TouchNum);
        goto exit_read;
    }

#if 1   //avoid int frequently
    MMPF_OS_GetTime(&ulNow);
	if(ulNow - ulPre < 200)
	{
        ulPre = ulNow;
		goto exit_read; 
	}
	ulPre = ulNow;
#endif
    
    ret = TouchPanel_Get_Reg_Data(REG_COOR_ADDR,TouchPoint,TouchNum * 8);
    if(ret != MMP_ERR_NONE) 
    {
        printc("%s,get touch point failed,ret=%x \r\n", __func__,ret);
        goto exit_read; 
    }

    printc(" TouchNum = %d \r\n",TouchNum);

    for (i = 0; i < TouchNum; i++)
    {
        *pX = TouchPoint[i*8+1] | (TouchPoint[i*8+2]<<8);
        *pY = TouchPoint[i*8+3] | (TouchPoint[i*8+4]<<8);
        printc(" point%d,pX=%d,pY=%d \r\n",i,*pX,*pY);
    }
    
    TouchPanel_TransformPosition(pX,pY,dir);

    TouchPanel_Set_Reg_Data(REG_COOR_STATUS,&CmdEndVal,1);

    return 1;
    
exit_read:

    *pX = 0;
	*pY = 0;
    
    TouchPanel_Set_Reg_Data(REG_COOR_STATUS,&CmdEndVal,1);
    
    return 0;
}


MMP_ERR TouchPanel_ReadVBAT1(struct _3RD_PARTY_TOUCHPANEL *pthis, MMP_USHORT* pX, MMP_USHORT* pY, MMP_UBYTE dir )
{
	return MMP_ERR_NONE;
}


void TouchPanel_ResetCtrl(struct _3RD_PARTY_TOUCHPANEL *pthis, MMP_BOOL bOn)
{
    printc("TouchPanel_ResetCtrl : bon %d\r\n",bOn);

#ifdef TOUCH_RESET_GPIO
	if (TOUCH_RESET_GPIO != MMP_GPIO_MAX)
	{
        //TouchPanel_Init(pthis);
		//MMPF_PIO_EnableOutputMode(TOUCH_RESET_GPIO, MMP_TRUE, MMP_TRUE);
		//MMPF_PIO_SetData(TOUCH_RESET_GPIO, (bOn ? TOUCH_RESET_GPIO_ACT_MODE : !TOUCH_RESET_GPIO_ACT_MODE), MMP_TRUE);
	}
#endif

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

#endif //TOUCH_PANEL_GT911