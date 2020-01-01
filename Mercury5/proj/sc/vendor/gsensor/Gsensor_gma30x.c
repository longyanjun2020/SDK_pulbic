/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "Customer_config.h"
#include "config_fw.h"
#include "mmpf_i2cm.h"
#include "os_wrap.h"
#include "mmpf_pio.h"
#include "mmpf_timer.h"
#include "lib_retina.h"
#include "ahc_utility.h"
#include "ahc_fs.h"

#if (GSENSOR_CONNECT_ENABLE && GSENSOR_MODULE == GSENSOR_MODULE_GMA302)

#include "Gsensor_gma30x.h"
#include "AIT_Init.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define	TO_NEGATIVE_VALUE(x)	( (~x + 0x01) | 0x80 )
#define	TO_ABSOLUTE_VALUE(x)	( (x > 0x4000)? (0x4000 - (x&0x3FFF)):(x) )	

#define	LOW_BOUND_1G(s)			((signed char)s.ub1G - (signed char)s.ub1G_Err)
#define ABS(x) 					((x) > 0 ? (x) : -(x))

#define	MAP2HW_G(g, s)			((g * s.ub1G) / SCALE_G)

#define	STABLE_CNT				(0)

#define moving_step 8
#define SENSOR_DATA_SIZE 		3 


/*===========================================================================
 * Global varible
 *===========================================================================*/
INT32	bufferave[3][moving_step];	// 16 buffer
INT32	sum[3];		//  sum of moving_step 
INT32	avg[3];		// moving average result
INT32 OldGsXData = 0;
INT32 OldGsYData = 0;
INT32 OldGsZData = 0;
UINT8 pointer = 0;
static MMPF_I2CM_ATTRIBUTE 	gI2cmAttribute_gSensor 	= {MMPF_I2CM_ID_SW, GSENSOR_SLAVE_ADDR, 8, 8, 0x2, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_FALSE, 0, 0, 0, 50000/*SW support max 200KHZ*/, MMP_TRUE, GSENSOR_SCL, GSENSOR_SDA, MMP_FALSE, MMP_FALSE, MMP_FALSE, MMP_TRUE};
static GSENSOR_DATA			m_GSensorOffset 		= {0, 0, 0};
static GSENSOR_DATA			m_GSensorShadow  		= {0, 0, 0};
GSNR_ATTRIBUTE       		gGsensor_Attribute 		= {2, 6, 2, NULL};
MMP_BOOL	 				bGsensorinitialized 	= MMP_FALSE;
UINT8						bGsensorID				= 0xFF;

static int					kUpCnt 					= 0;
static int					kDwCnt 					= 0;
static int					kLastPosition 			= GSNR_POSITION_UNKNOWN;

/*===========================================================================
 * Extern function
 *===========================================================================*/

extern void printc( char* szFormat, ... );

#if (GSENSOR_DBG_MSG)
#define	DPRINT( ... ) printc( __VA_ARGS__ )
#else
#define	DPRINT( ... ) {}
#endif

MMP_ERR Gsensor_EnableIntXYZ(int ex, int ey, int ez);

/*===========================================================================
 * Main body
 *===========================================================================*/

MMP_ERR Gsensor_ReadRegister(MMP_UBYTE reg, MMP_UBYTE* pval)
{
	MMP_USHORT data;

	if(reg >= GSensor_Reg_INVALID)
	{
		DPRINT("GsnrRead-->Wrong Register Address\r\n");
		return MMP_ERR_NONE;
	}

	MMPF_I2cm_ReadReg(&gI2cmAttribute_gSensor, (MMP_USHORT)reg, (MMP_USHORT*)&data);
		
	*pval = (MMP_UBYTE)(data & 0x00FF);

	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_ReadRegister_2byte(MMP_UBYTE reg, MMP_USHORT* pval)
{
	MMP_USHORT data;

	if(reg >= GSensor_Reg_INVALID)
	{
		DPRINT("GsnrRead-->Wrong Register Address\r\n");
		return MMP_ERR_NONE;
	}

	MMPF_I2cm_ReadReg(&gI2cmAttribute_gSensor, (MMP_USHORT)reg, (MMP_USHORT*)&data);
		
	*pval = data;

	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_WriteRegister(MMP_UBYTE reg, MMP_UBYTE val)
{
	if(reg >= GSensor_Reg_INVALID)
	{	
		DPRINT("GsnrWrite-->Wrong Register Address\r\n");
		return MMP_ERR_NONE;
	}
	
	MMPF_I2cm_WriteReg(&gI2cmAttribute_gSensor, (MMP_USHORT)reg, (MMP_USHORT)val);
	
	return MMP_ERR_NONE;
}

void Gsensor_DumpRegister(void)
{
}

MMP_ERR Gsensor_ReadOffsetFromFile(void)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_WriteOffsetToFile(void)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_ResetDevice(void) 
{
	MMP_ERR 	status 	= MMP_ERR_NONE;
	MMP_USHORT 	value 	= 0x02;
	
	status |= MMPF_I2cm_WriteReg(&gI2cmAttribute_gSensor, 0x01, value);
	bGsensorinitialized = (status == MMP_ERR_NONE)?(MMP_TRUE):(MMP_FALSE);
	
	return status; 
}

MMP_ERR Gsensor_ReadDeviceID(void)
{
	MMP_ERR 	status;
	MMP_USHORT 	usdeviceID 	= 0;
	
#if 1	// by yoko 20150209
	status = Gsensor_ReadRegister_2byte(0x04, &Regdata);
	
	usdeviceID &= 0x00FF;
	
	if(usdeviceID != GSENSOR_ID_GMA30x)
#else
	status = MMPF_I2cm_ReadReg(&gI2cmAttribute_gSensor, 0x00, &usdeviceID);
	
	usdeviceID &= 0x00FF;
	
	if(usdeviceID != GSENSOR_ID_GMA302)
#endif
	{
		status = 1;	// ERROR
		DPRINT("Gsensor Read Device ID 0x%x  %d Error\r\n",usdeviceID, status);
		bGsensorID = 0xFF;
	}
	else
	{
		status = 0;	// SUCCESS
		DPRINT("Gsensor Read Device ID 0x%x %d Success\r\n",usdeviceID, status);
		bGsensorID = (MMP_UBYTE)usdeviceID;
	}
	
	return status; 
}

MMP_ERR	Gsensor_GetSensorOffset(MMP_UBYTE *data)
{
	return MMP_ERR_NONE;
}

MMP_ERR	Gsensor_SetSensorOffset(MMP_UBYTE *data)
{
	return MMP_ERR_NONE;
}

static MMP_SHORT KeepGsensorValue[3] = {0};
MMP_ERR Gsensor_Read_XYZ(GSENSOR_DATA *data) 
{
	MMP_UBYTE	i = 0;
	MMP_USHORT Regdata = 0;
    MMP_USHORT g_Data_L=0,g_Data_H=0;
	
	Gsensor_ReadRegister_2byte(0x04, &Regdata);
	Gsensor_ReadRegister(0x05, (MMP_UBYTE*)&Regdata);

	Gsensor_ReadRegister(0x06, (MMP_UBYTE*)&g_Data_L);
	Gsensor_ReadRegister(0x07, (MMP_UBYTE*)&g_Data_H);
	g_Data_L &= 0x00FE;
	g_Data_H &= 0x00FF;
	data->acc_val[0] = (g_Data_H<<8) | (g_Data_L);
	data->acc_val[0] = data->acc_val[0]>>1;
	data->acc_val[0] = TO_ABSOLUTE_VALUE(data->acc_val[0]);

	Gsensor_ReadRegister(0x08, (MMP_UBYTE*)&g_Data_L);
	Gsensor_ReadRegister(0x09, (MMP_UBYTE*)&g_Data_H);
	g_Data_L &= 0x00FE;
	g_Data_H &= 0x00FF;
	data->acc_val[1] = (g_Data_H<<8) | (g_Data_L);
	data->acc_val[1] = data->acc_val[1]>>1;
	data->acc_val[1] = TO_ABSOLUTE_VALUE(data->acc_val[1]);

	Gsensor_ReadRegister(0x0A, (MMP_UBYTE*)&g_Data_L);
	Gsensor_ReadRegister(0x0B, (MMP_UBYTE*)&g_Data_H);
	g_Data_L &= 0x00FE;
	g_Data_H &= 0x00FF;
	data->acc_val[2] = (g_Data_H<<8) | (g_Data_L);
	data->acc_val[2] = data->acc_val[2]>>1;
	data->acc_val[2] = TO_ABSOLUTE_VALUE(data->acc_val[2]);

	for(i = 0; i < 3; i++)
	{ 
		if(KeepGsensorValue[i])
		{
			MMP_USHORT tempValue = 0;

			tempValue = data->acc_val[i];

			if(data->acc_val[i] > KeepGsensorValue[i])
				data->acc_val[i] = data->acc_val[i] - KeepGsensorValue[i];
			else
				data->acc_val[i] = KeepGsensorValue[i] - data->acc_val[i];

			KeepGsensorValue[i] = tempValue;
		}
		else
		{
			KeepGsensorValue[i] = data->acc_val[i];
		}
	} 

    memcpy( &m_GSensorShadow, data, sizeof(GSENSOR_DATA) );
	//printc("x %d, y %d, c %d\n",(MMP_USHORT)data->acc_val[0], (MMP_USHORT)data->acc_val[1], (MMP_USHORT)data->acc_val[2]);
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_Read_XYZ_WithCompensation(GSENSOR_DATA *sd) 
{
	Gsensor_Read_XYZ(sd);	
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_Read_Accel_Avg(GSENSOR_DATA *data)
{
	return MMP_ERR_NONE;		
}

MMP_ERR Gsensor_CalculateOffset(MMP_UBYTE gAxis, GSENSOR_DATA avg)
{
	return MMP_ERR_NONE;
}

MMP_ERR	Gsensor_Calibration(MMP_UBYTE side)
{
	GSENSOR_DATA avg;
	
	Gsensor_Read_Accel_Avg(&avg);
	
	Gsensor_CalculateOffset(side, avg); 
	
	return MMP_ERR_NONE;
}

MMP_ERR	Gsensor_SetIntDuration(MMP_UBYTE arg)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetIntStatus(MMP_UBYTE* pstatus)
{
#if 0
	MMP_USHORT Regdata = 0;

	Gsensor_WriteRegister(0x16,0x1B);//Configured motion detection to differential mode and latch reference.
	Gsensor_WriteRegister(0x03,0x01);//Micro motion threshold from 0x01 ~ 0x1F only. 1 LSB = 0.25G. 4:1G   1F:7.75G

	Gsensor_ReadRegister_2byte(0x04, &Regdata);
	Gsensor_ReadRegister(0x05, (MMP_UBYTE*)&Regdata);
	Gsensor_ReadRegister(0x06, (MMP_UBYTE*)&Regdata);
	Gsensor_ReadRegister(0x07, (MMP_UBYTE*)&Regdata);
	Gsensor_ReadRegister(0x08, (MMP_UBYTE*)&Regdata);
	Gsensor_ReadRegister(0x09, (MMP_UBYTE*)&Regdata);
	Gsensor_ReadRegister(0x0A, (MMP_UBYTE*)&Regdata);
	Gsensor_ReadRegister(0x0B, (MMP_UBYTE*)&Regdata);

	Gsensor_WriteRegister(0x15,0x0C);//Enable motion interrupt and set INT pin to open-drain and active low.0x0C high

	printc("GMA301C Gsensor int init finish\r\n");
#endif
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetNormalModeDataRate(MMP_UBYTE rate)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetInterruptSource(MMP_UBYTE src)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetDataRate(MMP_USHORT *wDataRate)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetDynamicRange(MMP_UBYTE ubDrange)
{
	MMP_UBYTE ubFullSacleRange;

	ubFullSacleRange &= 0xFF;
	ubFullSacleRange |= DYNAMIC_RANGE_8;
	
 	gGsensor_Attribute.nMaxG	= MAX_16G;
 	gGsensor_Attribute.ub1G	 	= 64;	//0x10 * 4 = 64LSB (1G)
 	gGsensor_Attribute.ub1G_Err = 0x02;

	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetDynamicRange(MMP_UBYTE *ubDrange)
{
	*ubDrange = 6;
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_EnableIntXYZ(int ex, int ey, int ez)
{
	MMP_ERR 	status 	= MMP_ERR_NONE;
	return status;
}

MMP_ERR Gsensor_SetGroundAxis(int arg)
{
	MMP_ERR status = MMP_ERR_NONE;

	return status;
}

void Gsensor_Initial(void)
{		
	Gsensor_WriteRegister(0x01,0x02);
	Gsensor_WriteRegister(0x03,0x1F);
	Gsensor_WriteRegister(0x38,0x9F);
	Gsensor_WriteRegister(0x15,0x08);
	Gsensor_WriteRegister(0x16,0x09);
}

void Gsensor_Int_Initial(void)
{
	MMP_USHORT Regdata = 0;

	Gsensor_WriteRegister(0x16,0x1B);//Configured motion detection to differential mode and latch reference.
	Gsensor_WriteRegister(0x03,0x01);//Micro motion threshold from 0x01 ~ 0x1F only. 1 LSB = 0.25G. 4:1G   1F:7.75G

	Gsensor_ReadRegister_2byte(0x04, &Regdata);
	Gsensor_ReadRegister(0x05, (MMP_UBYTE*)&Regdata);
	Gsensor_ReadRegister(0x06, (MMP_UBYTE*)&Regdata);
	Gsensor_ReadRegister(0x07, (MMP_UBYTE*)&Regdata);
	Gsensor_ReadRegister(0x08, (MMP_UBYTE*)&Regdata);
	Gsensor_ReadRegister(0x09, (MMP_UBYTE*)&Regdata);
	Gsensor_ReadRegister(0x0A, (MMP_UBYTE*)&Regdata);
	Gsensor_ReadRegister(0x0B, (MMP_UBYTE*)&Regdata);

	Gsensor_WriteRegister(0x15,0x4c);// 0x4c / 5d//Enable motion interrupt and set INT pin to open-drain and active low.0x0C high
}

MMP_ERR Gsensor_IOControl(MMP_UBYTE cmd, void* arg)
{
	MMP_ERR status = MMP_ERR_NONE;
	
	switch(cmd)
	{
		case GSNR_CMD_RESET: 
			status |= Gsensor_ResetDevice();
			status |= Gsensor_ReadDeviceID();
			if (status == MMP_ERR_NONE)
			{
				// Init default setting
				gGsensor_Attribute.ubGroundAxis = MMP_GSENSOR_AXIS_Z;
				Gsensor_Initial();
				gGsensor_Attribute.nInited = 1;
			}
			else
			{
				gGsensor_Attribute.nInited = 0;
			}
		break;

		case GSNR_CMD_CALIBRATION: 
			status |= Gsensor_Calibration(*(MMP_UBYTE*)arg);
		break;
		
		case GSNR_CMD_GET_OFFSET: 
 			status |= Gsensor_ReadOffsetFromFile();
			status |= Gsensor_GetSensorOffset(arg);
		break;
		
		case GSNR_CMD_SET_OFFSET: 
 			status |= Gsensor_SetSensorOffset(arg);
 			status |= Gsensor_WriteOffsetToFile();
		break;
		
		case GSNR_CMD_READ_ACCEL_XYZ: 
			status |= Gsensor_Read_XYZ((GSENSOR_DATA*)arg);
		break;

		case GSNR_CMD_READ_ACCEL_WITH_COMPENSATION:
			status |= Gsensor_Read_XYZ_WithCompensation((GSENSOR_DATA*)arg);		
		break;
								
		case GSNR_CMD_SET_INT_THD: 
		{
			status |= Gsensor_ResetDevice();
			status |= Gsensor_ReadDeviceID();
			if (status == MMP_ERR_NONE)			
			{
				printc("GSNR_CMD_SET_INT_THD \n");
				Gsensor_Int_Initial();
			}
			break;
		}

		case GSNR_CMD_SET_INT_DURATION: 
			status |= Gsensor_SetIntDuration(*(int*)arg);
		break;
		
		case GSNR_CMD_GET_INT_STATUS:
			if (gGsensor_Attribute.nInited) 
			{
				status |= Gsensor_GetIntStatus(arg);
			} 
			else 
			{				
				status = 1;	// ERROR!
				*(unsigned char*)arg   = 0;
			}
		break;
		
		case GSNR_CMD_SET_POWER_SAVE:
		break;
			
		case GSNR_CMD_SET_DATA_RATE:
			status |= Gsensor_SetNormalModeDataRate(*(MMP_UBYTE*)arg);
		break;

		case GSNR_CMD_SET_INT_SOURCE:
			status |= Gsensor_SetInterruptSource(*(MMP_UBYTE*)arg);
		break;
		
		case GSNR_CMD_GET_DATA_RATE:
			status |= Gsensor_GetDataRate((MMP_USHORT*)arg);
		break;
		
		case GSNR_CMD_SET_DYNA_RANGE:
			status |= Gsensor_SetDynamicRange(*(MMP_UBYTE*)arg);
		break;
		
		case GSNR_CMD_GET_DYNA_RANGE:
			status |= Gsensor_GetDynamicRange(arg);
		break;
		
		case GSNR_CMD_SET_GROUND_AXIS:
			status |= Gsensor_SetGroundAxis((int)arg);
		break;		

		#if 0
		case GSNR_CMD_GROUND_AXIS_STATUS: 
		{
			GSENSOR_DATA	sd;
			GSNR_SBYTE		g;

			if (gGsensor_Attribute.ubGroundAxis == MMP_GSENSOR_AXIS_ERR)
				return GSNR_POSITION_NOCHANGE;
				
			Gsensor_Read_XYZ(&sd);
			
			g = (signed char)sd.acc_val[gGsensor_Attribute.ubGroundAxis];
			
			if (ABS(g) > LOW_BOUND_1G(gGsensor_Attribute)) 
			{
				if (g > 0) 
				{
					if ((kLastPosition != GSNR_POSITION_UP ||
						 kLastPosition == GSNR_POSITION_UNKNOWN) &&
						kUpCnt >= STABLE_CNT) 
					{
						kLastPosition = GSNR_POSITION_UP;
						*(MMP_UBYTE*)arg = kLastPosition;
						return kLastPosition;
					}
					if (kUpCnt < STABLE_CNT) 
					{
						kDwCnt = 0;
						kUpCnt++;
					}
				} 
				else 
				{
					if ((kLastPosition != GSNR_POSITION_DOWN ||
						 kLastPosition == GSNR_POSITION_UNKNOWN) &&
						 kDwCnt >= STABLE_CNT) 
					{
						kLastPosition = GSNR_POSITION_DOWN;
						*(MMP_UBYTE*)arg = kLastPosition;
						return kLastPosition;
					}
					if (kDwCnt <= STABLE_CNT) 
					{
						kUpCnt = 0;
						kDwCnt++;
					}
				}
			}
			*(MMP_UBYTE*)arg = GSNR_POSITION_NOCHANGE;
			return GSNR_POSITION_NOCHANGE;
		break;		
		}
		#endif
		
        case GSNR_CMD_READ_ACCEL_XYZ_SHADOW:
            memcpy( arg, &m_GSensorShadow, sizeof(GSENSOR_DATA) );
        break;
		default:
		break;
	}

	return status;
}

#endif
