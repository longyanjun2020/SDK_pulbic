//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "Customer_config.h"
#include "math.h"
#include "os_wrap.h"
#include "lib_retina.h"
#include "mmpf_i2cm.h"
#include "mmpf_pio.h"
#include "mmpf_eis.h"
#include "mmpf_timer.h"
#include "Customer_config.h"
#include "mmpf_gyrosensor.h"

#if (GYROSENSOR_CONNECT_ENABLE)
#if 1//(BIND_GYROSNR_ITG2020)
#include "Gyrosensor_202x.h"

//==============================================================================
//
//                              GLOBAL VARIABLE
//
//==============================================================================

static MMP_I2CM_ATTR 	gI2cmAttr_GyroSensor_16Bit = // For 16bits Data Access
{
    CFG_GYROSENSOR_I2C_ID,
    GYROSENSOR_SLAVE_ADDR,
    8,
    16,
    0x20,
    MMP_FALSE,
    MMP_FALSE,
    MMP_FALSE,
    MMP_FALSE,
    0x0,
    0x0,
    GYROSENSOR_I2C_PADSET,
    400000, /*400KHZ*/
    MMP_FALSE,
    NULL,
    NULL,
    MMP_FALSE,
    MMP_FALSE,
    MMP_FALSE,
    0
};

static MMP_I2CM_ATTR    gI2cmAttr_GyroSensor_8Bit = // For 8bits Data Access
{
    CFG_GYROSENSOR_I2C_ID,
    GYROSENSOR_SLAVE_ADDR,
    8,
    8,
    0x20,
    MMP_FALSE,
    MMP_FALSE,
    MMP_FALSE,
    MMP_FALSE,
    0x0,
    0x0,
    GYROSENSOR_I2C_PADSET,
    400000, /*400KHZ*/
    MMP_FALSE,
    NULL,
    NULL,
    MMP_FALSE,
    MMP_FALSE,
    MMP_FALSE,
    0
};

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

//MMPF_OS_FLAGID              GYROFlag;
gyro_param_t 				gyro_param, gyro_param_bak;
MMP_UBYTE 				    gubIntEnVal = 0;
MMP_ULONG                   gyro_scale[4] = {26200, 13100, 6550, 3280}; // multiply by 100

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
    //printc("Gyrosensor_WriteReg  0x%X  %d\r\n",  reg, val );
	return MMPF_I2cm_WriteReg(&gI2cmAttr_GyroSensor_8Bit, (MMP_USHORT)reg, (MMP_USHORT)val);
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_ReadReg
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Gyrosensor_ReadReg(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_UBYTE reg, MMP_UBYTE* pval)
{
	MMP_USHORT usData;

	MMPF_I2cm_ReadReg(&gI2cmAttr_GyroSensor_8Bit, (MMP_USHORT)reg, (MMP_USHORT*)&usData);	
	
	*pval = (usData & 0xFF);
	//printc("Gyrosensor_ReadReg  0x%X  %d\r\n",  reg, *pval );
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_SetRange
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Gyrosensor_SetRange(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_UBYTE ubFullScaleRange)
{
	MMP_UBYTE ubValue;
	
	pthis->MMPF_Gyrosensor_GetReg(pthis, GyroSensor_202x_CONFIG_1, &ubValue);
	
	ubValue &= ~(GYROSENSOR_202x_DYNAMIC_RANGE_MASK);
	
	switch(ubFullScaleRange)
	{
		case GYROSENSOR_DYNA_RANGE_31d25:
			ubValue |= GYROSENSOR_202x_DYNAMIC_RANGE_31d25;
		break;
		case GYROSENSOR_DYNA_RANGE_62d5:
			ubValue |= GYROSENSOR_202x_DYNAMIC_RANGE_62d5;
		break;
		case GYROSENSOR_DYNA_RANGE_125:
			ubValue |= GYROSENSOR_202x_DYNAMIC_RANGE_125;
		break;
		case GYROSENSOR_DYNA_RANGE_250:
			ubValue |= GYROSENSOR_202x_DYNAMIC_RANGE_250;
		break;
		default:
			ubValue |= GYROSENSOR_202x_DYNAMIC_RANGE_62d5;
		break;
	}
	printc("Gyrosensor_SetRange  %d\r\n",  ubValue);
	pthis->MMPF_Gyrosensor_SetReg(pthis, GyroSensor_202x_CONFIG_1, ubValue);
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_GetRange
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Gyrosensor_GetRange(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_UBYTE *ubDrange)
{
	MMP_UBYTE ubValue, ubRange;
	MMP_ERR 	status 		= MMP_ERR_NONE;
	
	pthis->MMPF_Gyrosensor_GetReg(pthis, GyroSensor_202x_CONFIG_1, &ubValue);
	
	ubRange = (ubValue & GYROSENSOR_202x_DYNAMIC_RANGE_MASK);
	
	switch(ubRange)
	{
		case GYROSENSOR_202x_DYNAMIC_RANGE_31d25:
			*ubDrange = GYROSENSOR_DYNA_RANGE_31d25;
		break;
		case GYROSENSOR_202x_DYNAMIC_RANGE_62d5:
			*ubDrange = GYROSENSOR_DYNA_RANGE_62d5;
		break;
		case GYROSENSOR_202x_DYNAMIC_RANGE_125:
			*ubDrange = GYROSENSOR_DYNA_RANGE_125;
		break;
		case GYROSENSOR_202x_DYNAMIC_RANGE_250:
			*ubDrange = GYROSENSOR_DYNA_RANGE_250;
		break;
		default:
			*ubDrange = GYROSENSOR_DYNA_RANGE_62d5;
		break; 
	}
	printc("Gyrosensor_GetRange  %d\r\n",  *ubDrange);
    return status;
}

MMP_ERR Gyrosensor_Set_SampleRate_Div(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_UBYTE div)
{
    pthis->MMPF_Gyrosensor_SetReg(pthis, GyroSensor_202x_SMPLRT_DIV, div);
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
	MMP_ERR 	status 		= MMP_ERR_NONE;

	if (GYRO_AD0_GPIO != MMP_GPIO_MAX)
	{
		MMPF_PIO_EnableOutputMode(GYRO_AD0_GPIO, MMP_TRUE, MMP_TRUE);
		MMPF_PIO_SetData(GYRO_AD0_GPIO, GYRO_AD0_GPIO_LEVEL, MMP_TRUE);
	}

	Gyrosensor_ReadDeviceID(pthis);
	
	#if (SUPPORT_EIS)
	pthis->MMPF_Gyrosensor_SetReg(pthis, GyroSensor_202x_SMPLRT_DIV, G_eis_obj.sample_time - 1);
	#endif
	pthis->MMPF_Gyrosensor_SetReg(pthis, GyroSensor_202x_CONFIG_1, GYROSENSOR_202x_DYNAMIC_RANGE_62d5);

#ifdef ENABLE_GYRO_INT
	GYRO_InitInterrupt();

	gubIntEnVal = GYROSENSOR_202x_INT_DATA_READY;
	
	#ifdef ENABLE_FSYNC
	pthis->MMPF_Gyrosensor_SetReg(pthis, GyroSensor_202x_CONFIG_0, 0x09);
	pthis->MMPF_Gyrosensor_SetReg(pthis, GyroSensor_202x_INT_CFG, GYROSENSOR_202x_LATCH_INT_EN | GYROSENSOR_202x_INT_READ_CLEAR | GYROSENSOR_202x_FSYNC_INT_LEVEL_L | GYROSENSOR_202x_FSYNC_INT_MODE_EN);
	gubIntEnVal |= GYROSENSOR_202x_INT_FSYNC;
	#else
	pthis->MMPF_Gyrosensor_SetReg(pthis, GyroSensor_202x_CONFIG_0, 0x01);
	pthis->MMPF_Gyrosensor_SetReg(pthis, GyroSensor_202x_INT_CFG, GYROSENSOR_202x_INT_READ_CLEAR);
	#endif
	
	#ifdef ENABLE_FIFO
	gubIntEnVal &= ~(GYROSENSOR_202x_INT_DATA_READY);
	gubIntEnVal |= GYROSENSOR_202x_INT_FIFO_FULL;
	#endif

#else
	pthis->MMPF_Gyrosensor_SetReg(pthis, GyroSensor_202x_CONFIG_0, 0x01);
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
	MMP_USHORT 	usDeviceID 	= 0;
	
	status |= MMPF_I2cm_ReadReg(&gI2cmAttr_GyroSensor_8Bit, GyroSensor_202x_GET_ID, &usDeviceID);
	
	if ((usDeviceID & 0x00FF) != GYROSENSOR_DEVICE_ID)
		printc("Gyrosensor Read Device ID 0x%x Error\r\n",usDeviceID);
	else
		printc("Gyrosensor Read Device ID 0x%x Success\r\n",usDeviceID);
	
	return status; 
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_ReadXY
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Gyrosensor_ReadXY(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_SLONG *Xout, MMP_SLONG *Yout)
{
	MMP_SSHORT  gyro[2];
	MMP_SLONG   sft = 1 << (gyro_info.adc_res - 1);

	MMPF_I2cm_ReadBurstData(&gI2cmAttr_GyroSensor_16Bit, GyroSensor_202x_XOUT_H, (MMP_USHORT *)gyro, 2);

	if (gyro_info.x_chan == GYRO_X_AXIS) {
		*Xout = (MMP_SLONG)gyro[0] + sft;
		*Yout = (MMP_SLONG)gyro[1] + sft;
	} 
	else if (gyro_info.x_chan == GYRO_Y_AXIS) {
		*Yout = (MMP_SLONG)gyro[0] + sft;
		*Xout = (MMP_SLONG)gyro[1] + sft;
	}
	
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_ReadXYT
//  Description :
//------------------------------------------------------------------------------
MMP_ERR Gyrosensor_ReadXYT(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_SLONG *Xout, MMP_SLONG *Yout, MMP_SLONG *Tout)
{
	MMP_SSHORT  gyro[3];
	MMP_SLONG   sft = 1 << (gyro_info.adc_res - 1);

	MMPF_I2cm_ReadBurstData(&gI2cmAttr_GyroSensor_16Bit, GyroSensor_202x_TOUT_H, (MMP_USHORT*)gyro, 3);

	*Tout = (MMP_SLONG)gyro[0] + sft;
	
	if (gyro_info.x_chan == GYRO_X_AXIS) {
		*Xout = (MMP_SLONG)gyro[1] + sft;
		*Yout = (MMP_SLONG)gyro[2] + sft;
	} 
	else if (gyro_info.x_chan == GYRO_Y_AXIS) {
		*Yout = (MMP_SLONG)gyro[1] + sft;
		*Xout = (MMP_SLONG)gyro[2] + sft;
	}
	
	return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_ReadOut_Temperature
//  Description :
//------------------------------------------------------------------------------
void Gyrosensor_ReadOut_Temperature(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_SHORT *sValue)
{
	MMP_UBYTE ubValue_H, ubValue_L;
	
	pthis->MMPF_Gyrosensor_GetReg(pthis, GyroSensor_202x_TOUT_H, &ubValue_H);
	pthis->MMPF_Gyrosensor_GetReg(pthis, GyroSensor_202x_TOUT_L, &ubValue_L);
	
	*sValue = (ubValue_H << 8) + ubValue_L;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_ReadOut_ADCXoutYout
//  Description :
//------------------------------------------------------------------------------
void Gyrosensor_ReadOut_ADCXoutYout(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_SHORT *sXout, MMP_SHORT *sYout)
{
	MMP_UBYTE ubValue_H, ubValue_L;
	
	pthis->MMPF_Gyrosensor_GetReg(pthis, GyroSensor_202x_XOUT_H, &ubValue_H);
	pthis->MMPF_Gyrosensor_GetReg(pthis, GyroSensor_202x_XOUT_L, &ubValue_L);
	*sXout = (ubValue_H << 8) + ubValue_L;
	
	pthis->MMPF_Gyrosensor_GetReg(pthis, GyroSensor_202x_YOUT_H, &ubValue_H);
	pthis->MMPF_Gyrosensor_GetReg(pthis, GyroSensor_202x_YOUT_L, &ubValue_L);
	*sYout = (ubValue_H << 8) + ubValue_L;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_ReadOut_ADCYoutZout
//  Description :
//------------------------------------------------------------------------------
void Gyrosensor_ReadOut_ADCYoutZout(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_SHORT *sYout, MMP_SHORT *sZout)
{
	MMP_UBYTE ubValue_H, ubValue_L;
	
	pthis->MMPF_Gyrosensor_GetReg(pthis, GyroSensor_202x_ZOUT_H, &ubValue_H);
	pthis->MMPF_Gyrosensor_GetReg(pthis, GyroSensor_202x_ZOUT_L, &ubValue_L);
	*sZout = (ubValue_H << 8) + ubValue_L;
	
	pthis->MMPF_Gyrosensor_GetReg(pthis, GyroSensor_202x_YOUT_H, &ubValue_H);
	pthis->MMPF_Gyrosensor_GetReg(pthis, GyroSensor_202x_YOUT_L, &ubValue_L);
	*sYout = (ubValue_H << 8) + ubValue_L;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_ReadOut_ValueXoutYout
//  Description :
//------------------------------------------------------------------------------
void Gyrosensor_ReadOut_ValueXoutYout(struct _3RD_PARTY_GYROSENSOR *pthis, float *fXout, float *fYout)
{
	MMP_UBYTE ubRange = 0;
	MMP_SHORT sXout, sYout;
	double	  fMutiplier = 0;
	
	pthis->MMPF_Gyrosensor_GetRange(pthis, &ubRange);
	Gyrosensor_ReadOut_ADCXoutYout(pthis, &sXout, &sYout);
	
	switch(ubRange)
	{
		case GYROSENSOR_DYNA_RANGE_31d25:
			fMutiplier = 62.5;
		break;
		case GYROSENSOR_DYNA_RANGE_62d5:
			fMutiplier = 125;
		break;
		case GYROSENSOR_DYNA_RANGE_125:
			fMutiplier = 250;
		break;
		case GYROSENSOR_DYNA_RANGE_250:
			fMutiplier = 500;
		break;
		default:
			fMutiplier = 62.5;
		break;
	}

	fMutiplier /= 65535;
	*fXout = fMutiplier * sXout;
	*fYout = fMutiplier * sYout;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_ReadOut_ValueYoutZout
//  Description :
//------------------------------------------------------------------------------
void Gyrosensor_ReadOut_ValueYoutZout(struct _3RD_PARTY_GYROSENSOR *pthis, float *fYout, float *fZout)
{
	MMP_UBYTE ubRange = 0;
	MMP_SHORT sZout, sYout;
	double	  fMutiplier = 0;
	
	pthis->MMPF_Gyrosensor_GetRange(pthis, &ubRange);
	Gyrosensor_ReadOut_ADCYoutZout(pthis, &sYout, &sZout);
	
	switch(ubRange)
	{
		case GYROSENSOR_DYNA_RANGE_31d25:
			fMutiplier = 62.5;
		break;
		case GYROSENSOR_DYNA_RANGE_62d5:
			fMutiplier = 125;
		break;
		case GYROSENSOR_DYNA_RANGE_125:
			fMutiplier = 250;
		break;
		case GYROSENSOR_DYNA_RANGE_250:
			fMutiplier = 500;
		break;
		default:
			fMutiplier = 62.5;
		break;
	}

	fMutiplier /= 65535;
	*fYout = fMutiplier * sYout;
	*fZout = fMutiplier * sZout;
}

//------------------------------------------------------------------------------
//  Function    : Gyrosensor_CalArea
//  Description :
//------------------------------------------------------------------------------
float Gyrosensor_CalArea(struct _3RD_PARTY_GYROSENSOR *pthis, float old_speed, float new_speed, float time_unit)
{
	float area, old_area, new_area;
	float speed_sum;

	speed_sum = old_speed - new_speed;
	
	if (speed_sum<0) {
		speed_sum = -speed_sum;
	}
	
	if ((old_speed >= 0 && new_speed >= 0) || (old_speed <= 0 && new_speed <= 0)) {
		area = (old_speed + new_speed) * time_unit * 0.5;
	}
	else {
		old_area = old_speed * time_unit * (old_speed / speed_sum);
		new_area = new_speed * time_unit * (new_speed / speed_sum);

		if (old_speed < 0)
			old_area = -old_area;
		else if (new_speed < 0)
			new_area = -new_area;

		area = old_area + new_area;
	}

	return area;
}

MMP_ERR Gyrosensor_IOControl(struct _3RD_PARTY_GYROSENSOR *pthis, GYROSENSOR_ATTRIBUTE *pgyrosnr_attr, MMP_UBYTE cmd, MMP_UBYTE* arg)
{
    MMP_ERR status = MMP_ERR_NONE;
    MMP_UBYTE val = 0;
        switch(cmd)
        {
            case GyroSensor_FIFO_EN:
                //printc("GyroSensor_FIFO_EN  %d\r\n",  *arg);
                if (*arg == GYROSENSOR_ALL_FIFO_DIS)
                {
                    pthis->MMPF_Gyrosensor_SetReg(pthis, GyroSensor_202x_FIFO_EN, GYROSENSOR_202x_ALL_FIFO_DIS);
                    pthis->MMPF_Gyrosensor_SetReg(pthis, GyroSensor_202x_USER_CTRL, GYROSENSOR_202x_RESET_FIFO);
                }
                else
                {
                    if ((*arg & GYROSENSOR_XG_FIFO_EN) == GYROSENSOR_XG_FIFO_EN)
                        val |=  GYROSENSOR_202x_XG_FIFO_EN;
                    if ((*arg & GYROSENSOR_YG_FIFO_EN) == GYROSENSOR_YG_FIFO_EN)
                        val |=  GYROSENSOR_202x_YG_FIFO_EN;
                    if ((*arg & GYROSENSOR_ZG_FIFO_EN) == GYROSENSOR_ZG_FIFO_EN)
                        val |=  GYROSENSOR_202x_ZG_FIFO_EN;
                    if ((*arg & GYROSENSOR_TEMP_FIFO_EN) == GYROSENSOR_TEMP_FIFO_EN)
                        val |=  GYROSENSOR_202x_TEMP_FIFO_EN;
                    printc("GyroSensor_FIFO_EN *arg  %d  val %d\r\n", *arg,  val);
                    pthis->MMPF_Gyrosensor_SetReg(pthis, GyroSensor_202x_FIFO_EN, val);
                    pthis->MMPF_Gyrosensor_SetReg(pthis, GyroSensor_202x_USER_CTRL, GYROSENSOR_202x_FIFO_RD_EN);
                }
                break;

            case GyroSensor_INT_EN:
//                printc("GyroSensor_INT_EN  %d\r\n",  *arg);
                if (*arg == GYROSENSOR_INT_NONE)
                {
                    pthis->MMPF_Gyrosensor_SetReg(pthis, GyroSensor_202x_INT_EN, GYROSENSOR_202x_INT_NONE);
                }
                else
                {
                    if ((*arg & GYROSENSOR_INT_FIFO_FULL) == GYROSENSOR_INT_FIFO_FULL)
                        val |=  GYROSENSOR_202x_INT_FIFO_FULL;
                    if ((*arg & GYROSENSOR_INT_FSYNC) == GYROSENSOR_INT_FSYNC)
                        val |=  GYROSENSOR_202x_INT_FSYNC;
                    if ((*arg & GYROSENSOR_INT_DATA_READY) == GYROSENSOR_INT_DATA_READY)
                        val |=  GYROSENSOR_202x_INT_DATA_READY;

                    printc("GyroSensor_INT_EN *arg  %d  val %d\r\n", *arg,  val);
                    pthis->MMPF_Gyrosensor_SetReg(pthis, GyroSensor_202x_INT_EN, val);
                }

                break;

            default :
                printc("[][][][][][][][][][][][][][][]\r\n");
                break;
        }

    return MMP_ERR_NONE;
}



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
    //10    
    //15    
    //20    
    //25   
};

int Gyrosensor_Module_Init(void)
{
    printc("[202x - Gyrosensor_Module_Init]\r\n");
    MMPF_3RDParty_Gyrosensor_Register(&Gyrosensor_Obj);
    return 0;    
}

#pragma arm section code = "initcall6", rodata = "initcall6", rwdata = "initcall6",  zidata = "initcall6" 
#pragma O0
ait_module_init(Gyrosensor_Module_Init);
#pragma
#pragma arm section rodata, rwdata ,  zidata 



#endif //BIND_GYROSNR_ITG2020
#endif //GYROSENSOR_CONNECT_ENABLE
