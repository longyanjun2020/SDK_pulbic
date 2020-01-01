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
//#include "ahc_utility.h"
//#include "ahc_fs.h"
#if defined(__GNUC__)
#include "vm_types.ht"
#endif

#if 0//(GSENSOR_CONNECT_ENABLE && GSENSOR_MODULE == GSENSOR_MODULE_GMA305)

#include "Gsensor_gma305.h"
#include "AIT_Init.h"
#include "drv_bus_i2c.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define	TO_NEGATIVE_VALUE(x)	( (~x + 0x01) | 0x80 )
#define	TO_ABSOLUTE_VALUE(x)	( (x > 0x4000)? (0x4000 - (x&0x3FFF)):(x) )	

//#define	LOW_BOUND_1G(s)			((signed char)s->ub1G - (signed char)s->ub1G_Err)
#define ABS(x) 					((x) > 0 ? (x) : -(x))

//#define	MAP2HW_G(g, s)			((g * s->ub1G) / SCALE_G)
#define MG_TO_RAWDATA(g, s)			((g)*(s)) // mg to raw data
#define REALDATA_TO_RAWDATA(g)		MG_TO_RAWDATA(g, _gGsnrDevInfo.usSensitivity)
#define RAWDATA_TO_REALDATA(r)		Gsensor_RawData_To_mg((r), _gGsnrDevInfo.usSensitivity)

#define	STABLE_CNT				(0)

#define moving_step 8
#define SENSOR_DATA_SIZE 		3 

/* I2C attributes */
#define GSENSOR_I2C_ID			(0x19)
#define GSENSOR_I2C_CHANNEL		(0x00)
#define GSENSOR_I2C_PAD_MODE	(I2C_PAD_MODE_1)
#define GSENSOR_I2C_SPEED		(I2C_HIGHSPEED_MODE_400KHZ)

/**/
#define GSENSOR_VALID_ADC_BITS			(15)
#define GSENSOR_DEFAULT_DYNAMIC_RANGE	(16)


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
static GSENSOR_DATA			m_GSensorOffset 		= {0, 0, 0};
static GSENSOR_DATA			m_GSensorShadow  		= {0, 0, 0};
//GSNR_ATTRIBUTE       		gGsensor_Attribute 		= {2, 6, 2, NULL};
//UINT8						bGsensorID				= 0xFF;

//static int					kUpCnt 					= 0;
//static int					kDwCnt 					= 0;
//static int					kLastPosition 			= GSNR_POSITION_UNKNOWN;

static GSNR_DEV_INFO		_gGsnrDevInfo =
{
	GSENSOR_ID_GMA305,	// usDeviceID
	GSENSOR_DEFAULT_DYNAMIC_RANGE,	// usDynamicRange
	256,	// usSensitivity. GMA has 13-bit ADC + 1-bit sign bit. But it can only sensing +/- 16g
	128,	// usODR.
	0,	// sIntrThreshold
	MMP_TRUE, // bEnableAutoCalibration
};

static const I2COptions_t	_gI2CCfg = 
{
	GSENSOR_SLAVE_ADDR,			// Slave address
	GSENSOR_I2C_CHANNEL,		// Channel
	GSENSOR_I2C_PAD_MODE,		// Pad
	0,							// DMA enable
	0,							// DMA address
	1,							// support restart mode or not
	GSENSOR_I2C_SPEED,			// Speed
	I2C_CTRL_MODE_HW,			// Control Mode
	I2C_SEN_TYPE_OTHER,			// Sensor Type
	I2C_ONE_BYTE_DATA,			// Data Length
	I2C_ONE_BYTE_ADDR			// Address Length
};


/*===========================================================================
 * Extern function
 *===========================================================================*/

#if (GSENSOR_DBG_MSG && defined(ALL_FW))
extern void	printc( char* szFormat, ... );
#define	DPRINT( ... ) printc( __VA_ARGS__ )
#else
#define	DPRINT( ... ) {}
#endif

MMP_ERR Gsensor_EnableIntXYZ(int ex, int ey, int ez);

/*===========================================================================
 * Main body
 *===========================================================================*/
#ifdef ALL_FW

MMP_ERR Gsensor_ReadRegister(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE reg , MMP_UBYTE* pval)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_ReadRegister_2byte(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE reg , MMP_USHORT* pval)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_WriteRegister(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE reg , MMP_UBYTE val)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_ResetDevice(struct _3RD_PARTY_GSENSOR *pthis) 
{
	MMP_UBYTE ubRstReg = 1<<1;
	
	pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_PWDN, ubRstReg);
	return MMP_ERR_NONE; 
}

MMP_ERR Gsensor_ReadDeviceID(struct _3RD_PARTY_GSENSOR *pthis, MMP_USHORT *pusDevID)
{
	MMP_ERR 	err 		= MMP_ERR_NONE;
	MMP_USHORT	usdeviceID 	= 0;
	
#if 1	// by yoko 20150209
	err = Gsensor_ReadRegister_2byte(pthis, 0x04, &usdeviceID);
	
	usdeviceID &= 0x00FF;
	
#else
	err = pthis->MMPF_Gsensor_GetReg(pthis, 0x00, &usdeviceID);
	
	usdeviceID &= 0x00FF;
	
	if(usdeviceID != GSENSOR_ID_GMA305)
#endif

	if (err != MMP_ERR_NONE) {
		*pusDevID = 0x0000;
	}
	else {
		*pusDevID = usdeviceID;
	}
	
	return err; 
}

MMP_ERR	Gsensor_GetSensorOffset(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE *data)
{
	return MMP_ERR_NONE;
}

MMP_ERR	Gsensor_SetSensorOffset(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE *data)
{
	return MMP_ERR_NONE;
}

static MMP_SHORT Gsensor_RawData_To_mg(MMP_USHORT usRawData, MMP_USHORT usSensitivity)
{
	MMP_USHORT usBoundary = 1<<(GSENSOR_VALID_ADC_BITS-1);
	
	if (usRawData < usBoundary) {
		// Postive value.
		return (usRawData * 1000 / usSensitivity);
	}
	else {
		// Nagetive value.
		return -1* ((1<<GSENSOR_VALID_ADC_BITS)-usRawData) * 1000 / usSensitivity;
	}
}

MMP_ERR Gsensor_Read_XYZ(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *data) 
{
	MMP_USHORT Regdata = 0;
	
	Gsensor_ReadRegister_2byte(pthis, 0x04, &Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x05, (MMP_UBYTE*)&Regdata);

	pthis->MMPF_Gsensor_GetReg(pthis, 0x06, (MMP_UBYTE*)&Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x07, ((MMP_UBYTE*)&Regdata)+1);
	data->acc_val[0] = RAWDATA_TO_REALDATA(Regdata>>1);
	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x08, (MMP_UBYTE*)&Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x09, ((MMP_UBYTE*)&Regdata)+1);
	data->acc_val[1] = RAWDATA_TO_REALDATA(Regdata>>1);
	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x0A, (MMP_UBYTE*)&Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x0B, ((MMP_UBYTE*)&Regdata)+1);
    data->acc_val[2] = RAWDATA_TO_REALDATA(Regdata>>1);

    memcpy( &m_GSensorShadow, data, sizeof(GSENSOR_DATA) );
	//printc("x %d, y %d, c %d\n",(MMP_USHORT)data->acc_val[0], (MMP_USHORT)data->acc_val[1], (MMP_USHORT)data->acc_val[2]);
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_Read_XYZ_WithCompensation(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *data) 
{
	GSENSOR_DATA temp_acc = {{0, 0, 0}};
	
	pthis->MMPF_Gsensor_Read_XYZ(pthis, &temp_acc);
	if (_gGsnrDevInfo.bEnableAutoCalibration == MMP_FALSE) {
		temp_acc.acc_val[0] -= m_GSensorOffset.acc_val[0];
		temp_acc.acc_val[1] -= m_GSensorOffset.acc_val[1];
		temp_acc.acc_val[2] -= m_GSensorOffset.acc_val[2];
	}
	memcpy(data, &temp_acc, sizeof(GSENSOR_DATA));
    memcpy( &m_GSensorShadow, data, sizeof(GSENSOR_DATA) );	
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_Read_Accel_Avg(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *data)
{
	GSENSOR_DATA 	acc_avg = {{0, 0, 0}};
  	GSENSOR_DATA 	temp = {{0, 0, 0}};
	MMP_UBYTE		i;	
	
	for(i = 0; i < CALIBRATE_AVG_NUM; i++) 
	{      
		pthis->MMPF_Gsensor_Read_XYZ(pthis, &temp);

		acc_avg.acc_val[0] += temp.acc_val[0];
		acc_avg.acc_val[1] += temp.acc_val[1];
		acc_avg.acc_val[2] += temp.acc_val[2];
		
		RTNA_WAIT_MS(10); // Wait for stable or wait data update???
  	}
	acc_avg.acc_val[0] /= CALIBRATE_AVG_NUM;
	acc_avg.acc_val[1] /= CALIBRATE_AVG_NUM;
	acc_avg.acc_val[2] /= CALIBRATE_AVG_NUM;

	data->acc_val[0] = acc_avg.acc_val[0];
	data->acc_val[1] = acc_avg.acc_val[1];
	data->acc_val[2] = acc_avg.acc_val[2];
	
	DPRINT("=====Read Average======\r\n");
	DPRINT("x_avg: %d, y_avg: %d, z_avg: %d\r\n", acc_avg.acc_val[0], acc_avg.acc_val[1], acc_avg.acc_val[2]); 	

	return MMP_ERR_NONE;		
}

MMP_ERR Gsensor_CalculateOffset(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA avg)
{
	m_GSensorOffset.acc_val[0] =  avg.acc_val[0] ;    
	m_GSensorOffset.acc_val[1] =  avg.acc_val[1] ;
	m_GSensorOffset.acc_val[2] =  avg.acc_val[2] ;

	DPRINT("OFFSET Acceleration X = 0x%x, Y = 0x%x, Z = 0x%x\r\n",
	       m_GSensorOffset.acc_val[0],
	       m_GSensorOffset.acc_val[1],
	       m_GSensorOffset.acc_val[2]);

	return MMP_ERR_NONE;
}

MMP_ERR	Gsensor_Calibration(struct _3RD_PARTY_GSENSOR *pthis)
{
	GSENSOR_DATA avg;
	
	pthis->MMPF_Gsensor_Read_Accel_Avg(pthis, &avg);
	
	pthis->MMPF_Gsensor_CalculateOffset(pthis, avg); 
	
	return MMP_ERR_NONE;
}

MMP_ERR	Gsensor_SetIntDuration(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE arg)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetIntStatus(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE* pstatus)
{
#if 0
	MMP_USHORT Regdata = 0;

	Gsensor_WriteRegister(0x16,0x1B);//Configured motion detection to differential mode and latch reference.
	Gsensor_WriteRegister(0x03,0x01);//Micro motion threshold from 0x01 ~ 0x1F only. 1 LSB = 0.25G. 4:1G   1F:7.75G

	Gsensor_ReadRegister_2byte(0x04, &Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x05, (MMP_UBYTE*)&Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x06, (MMP_UBYTE*)&Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x07, (MMP_UBYTE*)&Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x08, (MMP_UBYTE*)&Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x09, (MMP_UBYTE*)&Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x0A, (MMP_UBYTE*)&Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x0B, (MMP_UBYTE*)&Regdata);

	Gsensor_WriteRegister(0x15,0x0C);//Enable motion interrupt and set INT pin to open-drain and active low.0x0C high

	printc("GMA301C Gsensor int init finish\r\n");
#endif
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetPowerSaveMode(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE mode)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetNormalModeDataRate(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE rate)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetInterruptSource(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE src)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetDataRate(struct _3RD_PARTY_GSENSOR *pthis, MMP_USHORT *wDataRate)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetDynamicRange(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE ubDrange)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetDynamicRange(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE *ubDrange)
{
	*ubDrange = _gGsnrDevInfo.usDynamicRange;
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_EnableIntXYZ(int ex, int ey, int ez)
{
	MMP_ERR 	status 	= MMP_ERR_NONE;
	return status;
}

MMP_ERR Gsensor_Initial(struct _3RD_PARTY_GSENSOR *pthis)
{		
#if 0
	pthis->MMPF_Gsensor_SetReg(pthis, 0x01,0x02);
	pthis->MMPF_Gsensor_SetReg(pthis, 0x03,0x1F);
	pthis->MMPF_Gsensor_SetReg(pthis, 0x38,0x9F);
	pthis->MMPF_Gsensor_SetReg(pthis, 0x15,0x08);
	pthis->MMPF_Gsensor_SetReg(pthis, 0x16,0x89);
#endif	

#if 1
{
    MMP_UBYTE Regdata = 0;
	
    pthis->MMPF_Gsensor_GetReg(pthis, 0x00, (MMP_UBYTE*)&Regdata);
	printc("Gsensor_Initial: Regdata = 0x%X\r\n", Regdata);
	
	pthis->MMPF_Gsensor_SetReg(pthis, 0x18, 0x40);
	pthis->MMPF_Gsensor_SetReg(pthis, 0x15, 0x2A);
	pthis->MMPF_Gsensor_SetReg(pthis, 0x16, 0x00);
	pthis->MMPF_Gsensor_SetReg(pthis, 0x38, 0x5F);
}	
#endif
	return MMP_ERR_NONE;
}

void Gsensor_Initial_PowerOff(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE ubPowerGsenOnValue)
{

}

void Gsensor_Int_Initial(void)
{
#if 0
	MMP_USHORT Regdata = 0;

	pthis->MMPF_Gsensor_SetReg(pthis, 0x16,0x1B);//Configured motion detection to differential mode and latch reference.
	pthis->MMPF_Gsensor_SetReg(pthis, 0x03,0x01);//Micro motion threshold from 0x01 ~ 0x1F only. 1 LSB = 0.25G. 4:1G   1F:7.75G

	Gsensor_ReadRegister_2byte(0x04, &Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x05, (MMP_UBYTE*)&Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x06, (MMP_UBYTE*)&Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x07, (MMP_UBYTE*)&Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x08, (MMP_UBYTE*)&Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x09, (MMP_UBYTE*)&Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x0A, (MMP_UBYTE*)&Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x0B, (MMP_UBYTE*)&Regdata);

	pthis->MMPF_Gsensor_SetReg(pthis, 0x15,0x4c);// 0x4c / 5d//Enable motion interrupt and set INT pin to open-drain and active low.0x0C high
#endif	
}

MMP_ERR Gsensor_IOControl(struct _3RD_PARTY_GSENSOR *pthis, MMP_ULONG cmd, void* arg)
{
	MMP_ERR status = MMP_ERR_NONE;
	
	switch(cmd)
	{
		case GSNR_CMD_RESET: 
			{
				MMP_USHORT usDevID = 0;
				status = pthis->MMPF_Gsensor_Reset(pthis);
				status |= pthis->MMPF_Gsensor_ReadDeviceID(pthis, &usDevID); 
				if (status == MMP_ERR_NONE && usDevID == _gGsnrDevInfo.usDeviceID)
				{
					pthis->MMPF_Gsensor_Initialize(pthis);
					return status;
				}
				else
				{
					return MMP_PERIPHERAL_ERR_ACCESS;
				}
			}
		break;

		case GSNR_CMD_CALIBRATION: 
			status |= pthis->MMPF_Gsensor_Calibration(pthis);
		break;
		
		case GSNR_CMD_GET_OFFSET: 
			status |= pthis->MMPF_Gsensor_ReadOffsetFromFile(pthis);
			//status |= pthis->MMPF_Gsensor_GetSensorOffset(arg);
		break;
		
		case GSNR_CMD_SET_OFFSET: 
			status |= pthis->MMPF_Gsensor_SetSensorOffset(pthis, (GSENSOR_DATA*)arg);
			status |= pthis->MMPF_Gsensor_WriteOffsetToFile(pthis);
		break;
		
		case GSNR_CMD_READ_ACCEL_XYZ:
    		status |= pthis->MMPF_Gsensor_Read_XYZ(pthis, (GSENSOR_DATA*)arg);
		break;

		case GSNR_CMD_READ_ACCEL_WITH_COMPENSATION:
    		status |= pthis->MMPF_Gsensor_Read_XYZ_WithCompensation(pthis, (GSENSOR_DATA*)arg);
		break;

		case GSNR_CMD_SET_PWR_ON_INT_THD: 
			Gsensor_Initial_PowerOff(pthis, *((MMP_UBYTE*)arg));
		break;

		case GSNR_CMD_SET_INT_THD: 
		#if 0
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
		#endif
		break;

		case GSNR_CMD_SET_INT_DURATION: 
			status |= pthis->MMPF_Gsensor_SetIntDuration(pthis, *((MMP_UBYTE*)arg));
		break;
		
		case GSNR_CMD_GET_INT_STATUS:
			status |= pthis->MMPF_Gsensor_GetIntStatus(pthis, (MMP_UBYTE*)arg);
		break;
		
		case GSNR_CMD_SET_POWER_SAVE:
			status |= pthis->MMPF_Gsensor_SetPowerSaveMode(pthis, *((MMP_UBYTE*)arg));
		break;
		case GSNR_CMD_SET_NORMAL_MODE:
			//status |= pthis->MMPF_Gsensor_SetNormalModeDataRate(pthis, *arg);
		break;	
		case GSNR_CMD_SET_DATA_RATE:
			status |= pthis->MMPF_Gsensor_SetNormalModeDataRate(pthis, *((MMP_UBYTE*)arg));
		break;

		case GSNR_CMD_SET_INT_SOURCE:
			status |= pthis->MMPF_Gsensor_SetInterruptSource(pthis, *((MMP_UBYTE*)arg));
		break;
		
		case GSNR_CMD_GET_DATA_RATE:
			status |= pthis->MMPF_Gsensor_GetDataRate(pthis, (MMP_USHORT*)arg);
		break;
		
		case GSNR_CMD_SET_DYNA_RANGE:
			status |= pthis->MMPF_Gsensor_SetDynamicRange(pthis, *((MMP_UBYTE*)arg));
		break;
		
		case GSNR_CMD_GET_DYNA_RANGE:
			status |= pthis->MMPF_Gsensor_GetDynamicRange(pthis, (MMP_UBYTE*)arg);
		break;

		#if 0
		case GSNR_CMD_GROUND_AXIS_STATUS: 
		{
			GSENSOR_DATA	sd;
			GSNR_SBYTE		g;

			if (pgsnr_attr->ubGroundAxis == MMP_GSENSOR_AXIS_ERR) {
				*arg = GSNR_POSITION_NOCHANGE;
				return MMP_ERR_NONE;
            }

			pthis->MMPF_Gsensor_Read_XYZ(pthis, &sd);
			
			g = (signed char)sd.acc_val[pgsnr_attr->ubGroundAxis];
			
			if (ABS(g) > LOW_BOUND_1G(pgsnr_attr)) 
			{
				if (g > 0) 
				{
					if ((kLastPosition != GSNR_POSITION_UP ||
						 kLastPosition == GSNR_POSITION_UNKNOWN) &&
						kUpCnt >= STABLE_CNT) 
					{
						kLastPosition = GSNR_POSITION_UP;
						*arg = kLastPosition;
						DPRINT("GSNR_POSITION_UP\r\n");
						return MMP_ERR_NONE;
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
						*arg = kLastPosition;
						DPRINT("GSNR_POSITION_DOWN\r\n");
						return MMP_ERR_NONE;
					}
					if (kDwCnt <= STABLE_CNT) 
					{
						kUpCnt = 0;
						kDwCnt++;
					}
				}
			}

			*arg = GSNR_POSITION_NOCHANGE;
			return MMP_ERR_NONE;
		}
		break;
		#endif
		
        case GSNR_CMD_READ_ACCEL_XYZ_SHADOW:
            memcpy( arg, &m_GSensorShadow, sizeof(GSENSOR_DATA) );
        break;
		
		default:
		break;
	}

	return status;
}

MMP_BOOL Gsensor_Attached(struct _3RD_PARTY_GSENSOR *pthis)
{
#if (GSENSOR_MODULE_ATT_COMPILER)
    #if(GSENSOR_CONNECT_ENABLE)
    return MMP_TRUE;
    #else
    return MMP_FALSE;
    #endif	
#elif (GSENSOR_MODULE_ATT_GPIO)
	MMP_UBYTE ubValue = MMP_FALSE;

	if(GSENSOR_MODULE_GPIO < MMP_GPIO_MAX)
	{
		MMPF_PIO_GetData(GSENSOR_MODULE_GPIO, &ubValue);
		return ubValue;
	}
	else
	{
		return AHC_FALSE;
	}
#endif

	return AHC_FALSE;
}

static struct _3RD_PARTY_GSENSOR Gsensor_Obj = 
{
    //0
    Gsensor_ResetDevice,
    Gsensor_ReadDeviceID,
    Gsensor_Initial,
    Gsensor_WriteRegister,
    Gsensor_ReadRegister,
	//Gsensor_ReadRegister_2byte,
	
    //5
    NULL,//Gsensor_ReadOffsetFromFile,
    NULL,//Gsensor_WriteOffsetToFile,
    Gsensor_GetSensorOffset,
    Gsensor_SetSensorOffset,
    Gsensor_Read_XYZ,
    
    //10
    Gsensor_Read_XYZ_WithCompensation,
    Gsensor_Read_Accel_Avg,
    Gsensor_CalculateOffset,
    Gsensor_Calibration,
    Gsensor_SetIntDuration,
    
    //15
    Gsensor_GetIntStatus,
    Gsensor_SetPowerSaveMode,
    Gsensor_SetNormalModeDataRate,
    Gsensor_SetInterruptSource,
    Gsensor_GetDataRate,
    
    //20
    Gsensor_SetDynamicRange,
    Gsensor_GetDynamicRange,
    NULL,//Gsensor_SetGroundAxis,
    Gsensor_IOControl,
    Gsensor_Attached,   
};

int Gsensor_Module_Init(void)
{
    printc(FG_GREEN("[GMA301 - Gsensor_Module_Init]\r\n"));
    MMPF_3RDParty_Gsensor_Register(&Gsensor_Obj);
    return 0;    
}
#if defined(__GNUC__)
__section__(initcall6)
#else //#if defined(__GNUC__)
#pragma arm section code = "initcall6", rodata = "initcall6", rwdata = "initcall6",  zidata = "initcall6" 
#pragma O0
#endif
ait_module_init(Gsensor_Module_Init);
#if defined(__GNUC__)
//NOP
#else //#if defined(__GNUC__)
#pragma
#pragma arm section rodata, rwdata ,  zidata 
#endif
#endif		// ALL_FW

#ifdef MBOOT_FW
MMP_BOOL Gsensor_GetIntStatusForBoot(void)
{
	MMP_USHORT	value	= 0;

	MMPF_I2cm_ReadReg(&m_I2cmAttr_gsensor, (MMP_USHORT) 0x12, (MMP_USHORT*)&value);
	MMPF_I2cm_ReadReg(&m_I2cmAttr_gsensor, (MMP_USHORT) 0x13, (MMP_USHORT*)&value);

    if (value & 0x20)
        return MMP_TRUE;

    return MMP_FALSE;
}
#endif

#endif //GSENSOR_CONNECT_ENABLE && GSENSOR_MODULE == GSENSOR_MODULE_GMA301)

