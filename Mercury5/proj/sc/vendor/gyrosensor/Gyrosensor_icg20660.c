/*===========================================================================
 * Include files
 *===========================================================================*/

#include "mmph_hif.h"
#include "mmpf_pio.h"
#include "mmpf_spi.h"

#include "mmpf_eis.h"
#include "mmpf_timer.h"
#include "Customer_config.h"

#if (GYROSENSOR_CONNECT_ENABLE)
#if 1//(BIND_GYROSNR_ICG20660)
#include "Gyrosensor_icg20660.h"

/*===========================================================================
 * Global varible
 *===========================================================================*/

#define	GYRO_ICG20660_ID        (0x91)

MMPF_SPI_ID m_GyroSpiID;

//static MMPF_SPI_ATTRIBUTE  m_GyrosensorSpi = {MMPF_SPI_MASTER_MODE, 0, 24, 65, 0, 0, 0, 0, 0, MMPF_SPI_PAD_1};
//20:CLK=6.5MHz
static MMPF_SPI_ATTRIBUTE  m_GyrosensorSpi = {MMPF_SPI_MASTER_MODE, 0, 16, 20, 0, 0, 0, 0, 0, MMPF_SPI_PAD_2};

/*
UART:
initial:GyrosensorTest 0
write:GyrosensorTest 1 reg val
read:GyrosensorTest 2 reg
*/

static GYRO_DATA_CONFIG m_GYConfig =
{
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

gyro_info_t gyro_info = 
{
    GYRO_Y_AXIS,
    GYRO_X_AXIS,
    GYRO_POSITIVE,
    GYRO_NEGATIVE,
    16,
    0,
    0,
    0,
    0,
    3
};

gyro_param_t                gyro_param, gyro_param_bak;
MMP_UBYTE                   gubIntEnVal = 0;
MMP_ULONG                   gyro_scale[GYROSENSOR_DYNA_RANGE_NUM] = {26200, 26200, 26200, 13100, 6550}; // multiply by 100

//==============================================================================
//
//                              EXTERNAL VARIABLE
//
//==============================================================================

extern eis_t G_eis_obj;

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

#if 0
void ____Gyro_Function____(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_WriteReg
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Gyrosensor_WriteReg(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_UBYTE reg, MMP_UBYTE val)
{
    MMP_UBYTE 	usWriteData[2] = {0};
    
    //printc("Gyrosensor_WriteReg  0x%X  %d\r\n",  reg, val );

    usWriteData[1]= reg;
    usWriteData[0]= val;
    
    return MMPF_SPI_Write(m_GyroSpiID, (MMP_ULONG)usWriteData, 2);
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_ReadReg
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Gyrosensor_ReadReg(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_UBYTE usReg , MMP_UBYTE* usReadData)
{
    MMP_ERR     status = MMP_ERR_NONE;  
    MMP_UBYTE 	usWriteData[2] = {0};

    usWriteData[1]= usReg | 0x80;//Read
    usWriteData[0]= 0x00;

    status = MMPF_SPI_Read(m_GyroSpiID, (MMP_ULONG)usReadData, 2 , (MMP_ULONG)usWriteData, 2);
    //printc("Gyrosensor_ReadReg  0x%X  0x%x 0x%x\r\n",  usReg, usReadData[1], usReadData[0] );
    return status;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_SetRange
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Gyrosensor_SetRange(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_UBYTE ubFullScaleRange)
{
	MMP_UBYTE ubValue;
	MMP_ERR     status      = MMP_ERR_NONE;

	status |= pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_CONFIG, &ubValue);

	ubValue &= ~(GYROSENSOR_DYNAMIC_RANGE_MASK);

	switch(ubFullScaleRange)
	{
		case GYROSENSOR_DYNA_RANGE_125:
			ubValue |= GYROSENSOR_DYNAMIC_RANGE_125;
		break;

		case GYROSENSOR_DYNA_RANGE_250:
			ubValue |= GYROSENSOR_DYNAMIC_RANGE_250;
		break;

		case GYROSENSOR_DYNA_RANGE_500:
			ubValue |= GYROSENSOR_DYNAMIC_RANGE_500;
		break;

		default:
			ubValue |= GYROSENSOR_DYNAMIC_RANGE_125;
		break;
	}
	
	status |= pthis->MMPF_Gyrosensor_SetReg(pthis, GSEN_ICG20660_GYRO_CONFIG, ubValue);
	return status;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_GetRange
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Gyrosensor_GetRange(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_UBYTE *ubDrange)
{
	MMP_UBYTE ubValue, ubRange;
    MMP_ERR     status      = MMP_ERR_NONE;

	status = pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_CONFIG, &ubValue);
	
	ubRange = (ubValue & GYROSENSOR_DYNAMIC_RANGE_MASK);
	
	switch(ubRange)
	{
		case GYROSENSOR_DYNAMIC_RANGE_125:
			*ubDrange = GYROSENSOR_DYNA_RANGE_125;
		break;
		case GYROSENSOR_DYNAMIC_RANGE_250:
			*ubDrange = GYROSENSOR_DYNA_RANGE_250;
		break;
		case GYROSENSOR_DYNAMIC_RANGE_500:
			*ubDrange = GYROSENSOR_DYNA_RANGE_500;
		break;
		default:
			*ubDrange = GYROSENSOR_DYNA_RANGE_125;
		break; 
	}
    printc("Gyrosensor_GetRange  %d\r\n",  *ubDrange);
    return status;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_Set_SampleRate_Div
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Gyrosensor_Set_SampleRate_Div(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_UBYTE div)
{
    pthis->MMPF_Gyrosensor_SetReg(pthis, GSEN_ICG20660_SMPLRT_DIV, div);
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_Enable
//  Description :
//------------------------------------------------------------------------------
void Gyrosensor_Enable(struct _3RD_PARTY_GYROSENSOR *pthis, int enable)
{
    m_GYConfig.enable   = enable;
    m_GYConfig.x_shift  = 0;
    m_GYConfig.y_shift  = 0;
    m_GYConfig.cnt      = 0;
    m_GYConfig.x_weight = 380;
    m_GYConfig.y_weight = 380;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_SetWeight
//  Description :
//------------------------------------------------------------------------------
void Gyrosensor_SetWeight(struct _3RD_PARTY_GYROSENSOR *pthis, int x_weight, int y_weight)
{
    m_GYConfig.x_weight = x_weight;
    m_GYConfig.y_weight = y_weight;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_SetGyroOffset
//  Description :
//------------------------------------------------------------------------------
void Gyrosensor_SetGyroOffset(struct _3RD_PARTY_GYROSENSOR *pthis, float offset_x, float offset_y)
{
    m_GYConfig.x_offset = offset_x;
    m_GYConfig.y_offset = offset_y;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_GetGyroShift
//  Description :
//------------------------------------------------------------------------------
void Gyrosensor_GetGyroShift(struct _3RD_PARTY_GYROSENSOR *pthis, int* Xout_shift, int* Yout_shift)
{
    *Xout_shift = m_GYConfig.x_shift;
    *Yout_shift = m_GYConfig.y_shift;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_SetGyroShift
//  Description :
//------------------------------------------------------------------------------
void Gyrosensor_SetGyroShift(struct _3RD_PARTY_GYROSENSOR *pthis, int Xout_shift, int Yout_shift)
{
    m_GYConfig.x_shift = Xout_shift;
    m_GYConfig.y_shift = Yout_shift;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_Initial
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Gyrosensor_Initial(struct _3RD_PARTY_GYROSENSOR *pthis)
{
    MMP_ERR status = MMP_ERR_NONE;

    printc(FG_BLUE(">>>>> Gyrosensor_Initial <<<<<\r\n"));

    if (GYRO_AD0_GPIO != MMP_GPIO_MAX)
    {
        MMPF_PIO_EnableOutputMode(GYRO_AD0_GPIO, MMP_TRUE, MMP_TRUE);
        MMPF_PIO_SetData(GYRO_AD0_GPIO, GYRO_AD0_GPIO_LEVEL, MMP_TRUE);
    }
    
    m_GyroSpiID                  =   0; // SPI set 1
    MMPF_SPI_Initialize();   
    MMPF_SPI_SetAttributes(m_GyroSpiID, &m_GyrosensorSpi);
    
//	status = Gyrosensor_WriteReg(0x1f,0x80); //FS = +/- 200dsp
//	status = Gyrosensor_WriteReg(0x0b,0x03); //Normal Mode

    pthis->MMPF_Gyrosensor_SetReg(pthis, GSEN_ICG20660_PWR_MGMT_1, 0x80); // DEVICE RESET +++
    MMPF_OS_Sleep(2);
    pthis->MMPF_Gyrosensor_SetReg(pthis, GSEN_ICG20660_PWR_MGMT_1, 0x01); // CLKSEL[2:0] +++

    Gyrosensor_ReadDeviceID(pthis);

    #if (SUPPORT_EIS)
    pthis->MMPF_Gyrosensor_SetReg(pthis, GSEN_ICG20660_SMPLRT_DIV, G_eis_obj.sample_time - 1);
    #endif
    pthis->MMPF_Gyrosensor_SetReg(pthis, GSEN_ICG20660_GYRO_CONFIG, GYROSENSOR_DYNAMIC_RANGE_125);

#ifdef ENABLE_GYRO_INT
    GYRO_InitInterrupt();
    
    gubIntEnVal = GYROSENSOR_ICG20660_INT_DATA_READY;
    
    Gyrosensor_WriteReg(pthis, GSEN_ICG20660_CONFIG, 0x01);
    Gyrosensor_WriteReg(pthis, GSEN_ICG20660_INT_PIN_CFG, GYROSENSOR_ICG20660_INT_READ_CLEAR);
    
    #ifdef ENABLE_FIFO
    gubIntEnVal &= ~(GYROSENSOR_ICG20660_INT_DATA_READY);
    gubIntEnVal |= GYROSENSOR_ICG20660_INT_FIFO_FULL;
    #endif

#else
    pthis->MMPF_Gyrosensor_SetReg(pthis, GSEN_ICG20660_CONFIG, 0x01);
#endif

    return status;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_ReadDeviceID
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Gyrosensor_ReadDeviceID(struct _3RD_PARTY_GYROSENSOR *pthis)
{
    MMP_ERR 	status 		= MMP_ERR_NONE;
    MMP_UBYTE 	usDeviceID 	= 0;

    status = pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_WHO_AM_I,&usDeviceID); //Reg = 0x75(who am i)

    if ((usDeviceID == GYRO_ICG20660_ID)&&(status == MMP_ERR_NONE))
        printc(">>>>> GyroSensor ID=0x%x. Initial success <<<<<\r\n",usDeviceID);		
    else
        printc(">>>>> GyroSensor error ret=%d Reg(0x75)=0x%x <<<<<\r\n\n",status,usDeviceID);

    return status; 
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_ReadXY
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Gyrosensor_ReadXY(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_SLONG *Xout, MMP_SLONG *Yout)
{
    MMP_UBYTE   ubValue_H, ubValue_L;
    MMP_SSHORT  gyro[2];
    MMP_SLONG   sft = 1 << (gyro_info.adc_res - 1);

    //MMPF_I2cm_ReadBurstData(&gI2cmAttr_GyroSensor_16Bit, GyroSensor_XOUT_H, (MMP_USHORT *)gyro, 2);

    if (gyro_info.x_chan == GYRO_X_AXIS) {
        pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_XOUT_H, &ubValue_H);
	    pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_XOUT_L, &ubValue_L);
		gyro[0] = (ubValue_H << 8) + ubValue_L;
		*Xout = gyro[0] + sft;

		pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_YOUT_H, &ubValue_H);
		pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_YOUT_L, &ubValue_L);
		gyro[1] = (ubValue_H << 8) + ubValue_L;
		*Yout = gyro[1] + sft;
	} 
	else if (gyro_info.x_chan == GYRO_Y_AXIS) {
	    pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_XOUT_H, &ubValue_H);
	    pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_XOUT_L, &ubValue_L);
		gyro[0] = (ubValue_H << 8) + ubValue_L;
		*Yout = gyro[0] + sft;

		pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_YOUT_H, &ubValue_H);
		pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_YOUT_L, &ubValue_L);
		gyro[1] = (ubValue_H << 8) + ubValue_L;
		*Xout = gyro[1] + sft;
	}

    //printc(FG_BLUE("[Gyrosensor_ReadXY] x=%d  y=%d \n\r"),*Xout,*Yout);

	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_ReadXYT
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Gyrosensor_ReadXYT(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_SLONG *Xout, MMP_SLONG *Yout, MMP_SLONG *Tout)
{
    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_ReadOut_ADCXoutYout
//  Description :
//------------------------------------------------------------------------------
void Gyrosensor_ReadOut_ADCXoutYout(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_SHORT *sXout, MMP_SHORT *sYout)
{
    MMP_UBYTE ubValue_H, ubValue_L;
    
    pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_XOUT_H, &ubValue_H);
    pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_XOUT_L, &ubValue_L);
    *sXout = (ubValue_H << 8) + ubValue_L;
    
    pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_YOUT_H, &ubValue_H);
    pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_YOUT_L, &ubValue_L);
    *sYout = (ubValue_H << 8) + ubValue_L;

    //printc(FG_BLUE("[Gyrosensor_ReadOut_ADCXoutYout] x=%d y=%d\n\r"),*sXout,*sYout); 
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_ReadOut_ADCYoutZout
//  Description :
//------------------------------------------------------------------------------
void Gyrosensor_ReadOut_ADCYoutZout(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_SHORT *sYout, MMP_SHORT *sZout)
{
    MMP_UBYTE ubValue_H, ubValue_L;

    pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_ZOUT_H, &ubValue_H);
    pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_ZOUT_L, &ubValue_L);
    *sZout = (ubValue_H << 8) + ubValue_L;
    
    pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_YOUT_H, &ubValue_H);
    pthis->MMPF_Gyrosensor_GetReg(pthis, GSEN_ICG20660_GYRO_YOUT_L, &ubValue_L);
    *sYout = (ubValue_H << 8) + ubValue_L;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_IOControl
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Gyrosensor_IOControl(struct _3RD_PARTY_GYROSENSOR *pthis, GYROSENSOR_ATTRIBUTE *pgyrosnr_attr, MMP_UBYTE cmd, MMP_UBYTE* arg)
{
    MMP_UBYTE val = 0;
    
    switch(cmd)
    {
        case GyroSensor_FIFO_EN:
            //printc("GyroSensor_FIFO_EN  %d\r\n",  *arg);
            if (*arg == GYROSENSOR_ALL_FIFO_DIS)
            {
                pthis->MMPF_Gyrosensor_SetReg(pthis, GSEN_ICG20660_FIFO_EN, GYROSENSOR_ICG20660_ALL_FIFO_DIS);
                pthis->MMPF_Gyrosensor_SetReg(pthis, GSEN_ICG20660_USER_CTRL, GYROSENSOR_ICG20660_RESET_FIFO);
            }
            else
            {
                if ((*arg & GYROSENSOR_XG_FIFO_EN) == GYROSENSOR_XG_FIFO_EN)
                    val |=  GYROSENSOR_ICG20660_XG_FIFO_EN;
                if ((*arg & GYROSENSOR_YG_FIFO_EN) == GYROSENSOR_YG_FIFO_EN)
                    val |=  GYROSENSOR_ICG20660_YG_FIFO_EN;
                if ((*arg & GYROSENSOR_ZG_FIFO_EN) == GYROSENSOR_ZG_FIFO_EN)
                    val |=  GYROSENSOR_ICG20660_ZG_FIFO_EN;
                if ((*arg & GYROSENSOR_TEMP_FIFO_EN) == GYROSENSOR_TEMP_FIFO_EN)
                    val |=  GYROSENSOR_ICG20660_TEMP_FIFO_EN;
                printc("GyroSensor_FIFO_EN *arg  %d  val %d\r\n", *arg,  val);
                pthis->MMPF_Gyrosensor_SetReg(pthis, GSEN_ICG20660_FIFO_EN, val);
                pthis->MMPF_Gyrosensor_SetReg(pthis, GSEN_ICG20660_USER_CTRL, GYROSENSOR_ICG20660_FIFO_RD_EN);
            }
            break;

        case GyroSensor_INT_EN:
//                printc("GyroSensor_INT_EN  %d\r\n",  *arg);
            if (*arg == GYROSENSOR_INT_NONE)
            {
                pthis->MMPF_Gyrosensor_SetReg(pthis, GSEN_ICG20660_INT_ENABLE, GYROSENSOR_ICG20660_INT_NONE);
            }
            else
            {
                if ((*arg & GYROSENSOR_INT_FIFO_FULL) == GYROSENSOR_INT_FIFO_FULL)
                    val |=  GYROSENSOR_ICG20660_INT_FIFO_FULL;
//                    if ((*arg & GYROSENSOR_INT_FSYNC) == GYROSENSOR_INT_FSYNC)
//                        val |=  GYROSENSOR_ICG20660_INT_FSYNC;
                if ((*arg & GYROSENSOR_INT_DATA_READY) == GYROSENSOR_INT_DATA_READY)
                    val |=  GYROSENSOR_ICG20660_INT_DATA_READY;

                printc("GyroSensor_INT_EN *arg  %d  val %d\r\n", *arg,  val);
                pthis->MMPF_Gyrosensor_SetReg(pthis, GSEN_ICG20660_INT_ENABLE, val);
            }

            break;

        default :
            printc("[][][][][][][][][][][][][][][]\r\n");
            break;
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_Attached
//  Description :
//------------------------------------------------------------------------------
MMP_BOOL Gyrosensor_Attached(struct _3RD_PARTY_GYROSENSOR *pthis)
{
    return MMP_TRUE;
}

struct _3RD_PARTY_GYROSENSOR Gyrosensor_Obj =
{
    //0
    Gyrosensor_Initial,
    Gyrosensor_WriteReg,
    Gyrosensor_ReadReg,
    Gyrosensor_ReadXY,
    Gyrosensor_ReadXYT,

    //5
    Gyrosensor_GetRange,
    Gyrosensor_SetRange,
    Gyrosensor_Set_SampleRate_Div,
    Gyrosensor_IOControl,
    Gyrosensor_Attached
};

int Gyrosensor_Module_Init(void)
{
    printc("[20660 - Gyrosensor_Module_Init]\r\n");
    MMPF_3RDParty_Gyrosensor_Register(&Gyrosensor_Obj);
    return 0;
}

#pragma arm section code = "initcall6", rodata = "initcall6", rwdata = "initcall6",  zidata = "initcall6"
#pragma O0
ait_module_init(Gyrosensor_Module_Init);
#pragma
#pragma arm section rodata, rwdata ,  zidata

#endif // BIND_GYROSNR_ICG20660
#endif // GYROSENSOR_CONNECT_ENABLE
