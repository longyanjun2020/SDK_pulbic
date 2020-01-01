/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "config_fw.h"
#include "mmpf_i2cm.h"
#include "os_wrap.h"
#include "mmpf_pio.h"
#include "mmpf_timer.h"
#include "lib_retina.h"
#include "ahc_utility.h"
#include "ahc_fs.h"
#include "dsc_Key.h"

#if (GSENSOR_CONNECT_ENABLE && GSENSOR_MODULE == GSENSOR_MODULE_DMARD) 
#include "Gsensor_dmard06.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define	TO_NEGATIVE_VALUE(x)	( (~x + 0x01) | 0x80 )
#define	TO_ABSOLUTE_VALUE(x)	( (x > 0x80)? (0x100 - x):(x) )

#define	LOW_BOUND_1G(s)			((signed char)s.ub1G - (signed char)s.ub1G_Err)
#define ABS(x) 					((x) > 0 ? (x) : -(x))

#define	MAP2HW_G(g, s)			((g * s.ub1G) / SCALE_G)

#define	STABLE_CNT				(0)

/*===========================================================================
 * Global varible
 *===========================================================================*/

static MMP_I2CM_ATTR gI2cmAttribute_gSensor = {
	MMP_I2CM_GPIO,		//i2cmID
	GSENSOR_SLAVE_ADDR,	//ubSlaveAddr
	8, 					//ubRegLen
	8, 					//ubDataLen
	0x2, 				//ubDelayTime
	MMP_FALSE, 			//bDelayWaitEn
	MMP_FALSE, 			//bInputFilterEn
	MMP_FALSE, 			//b10BitModeEn
	MMP_FALSE, 			//bClkStretchEn
	0, 					//ubSlaveAddr1
	0, 					//ubDelayCycle
	0, 					//ubPadNum
	50000 /*50KHZ*/, 	//ulI2cmSpeed
	MMP_TRUE, 			//bOsProtectEn
	GSENSOR_SCL, 		//sw_clk_pin
	GSENSOR_SDA, 		//sw_data_pin
	MMP_FALSE,			//bRfclModeEn 
	MMP_FALSE,			//bWfclModeEn
	MMP_FALSE			//bRepeatModeEn
};

static GSENSOR_DATA			m_GSensorOffset 		= {0, 0, 0};
static GSENSOR_DATA			m_GSensorShadow  		= {0, 0, 0};
GSNR_ATTRIBUTE       		gGsensor_Attribute 		= {4, 8, 2, NULL, 0x10, 0x02, 8, 0};
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
#if (GSENSOR_DBG_MSG)	

	MMP_LONG	i;
	MMP_UBYTE	rv;
	MMP_UBYTE	regs[] = {		0x0f, 0x40, 0x41, 0x42, 0x43, 
								0x44, 0x45, 0x46, 0x47, 0x48, 
								0x49, 0x4a, 0x4b, 0x4c, 0x4d};
							        
	printc("====DMARD06/07 Registers====\r\n");
	
	for (i = 0; i < sizeof(regs); i++) 
	{
		Gsensor_ReadRegister(regs[i], &rv);
		printc("Reg: 0x%02x, 0x%02x\r\n", regs[i], rv);
	}
	
	printc("PROPERTY id = 0x%x, Range = %d, Sens = %d, GroundAxis = %d, 1G = 0x%x , ErrG = 0x%x, MaxG = %d\r\n",
			 bGsensorID,
			 gGsensor_Attribute.ubRange,
			 gGsensor_Attribute.ubSensitive,
			 gGsensor_Attribute.ubGroundAxis,
			 gGsensor_Attribute.ub1G,
			 gGsensor_Attribute.ub1G_Err,
			 gGsensor_Attribute.nMaxG);
#endif
}

MMP_ERR Gsensor_ReadOffsetFromFile(void)
{
#if 0
	AHC_ERR err;
	UINT32 	ulFileId, ulFileSize, ulActualSize;
	
	err |= AHC_FS_FileOpen(GSNR_OFFSET_FILENAME,AHC_StrLen(GSNR_OFFSET_FILENAME),"rb",AHC_StrLen("rb"),&ulFileId);
		
	err |= AHC_FS_FileGetSize(ulFileId, &ulFileSize);
	
	err |= AHC_FS_FileRead(ulFileId, (UINT8*)&m_GSensorOffset, sizeof(GSENSOR_DATA), &ulActualSize);
	
	err |= AHC_FS_FileClose(ulFileId);

	if(err)
		DPRINT("Gsensor_ReadOffsetFromFile Error\r\n");
	else
		DPRINT("Gsensor_ReadOffsetFromFile Success\r\n");		
#endif	
	
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_WriteOffsetToFile(void)
{
	//DramToFile(GSNR_OFFSET_FILENAME, (INT8*)&m_GSensorOffset,sizeof(GSENSOR_DATA));
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_ResetDevice(void) 
{
	MMP_ERR 	status 	= MMP_ERR_NONE;
	MMP_USHORT 	value 	= 0;
	
	status |= MMPF_I2cm_ReadReg(&gI2cmAttribute_gSensor, GSensor_Reg_SW_RESET, &value);
	
	bGsensorinitialized = (status == MMP_ERR_NONE)?(MMP_TRUE):(MMP_FALSE);

	return status; 
}

MMP_ERR Gsensor_ReadDeviceID(void)
{
	MMP_ERR 	status;
	MMP_USHORT 	usdeviceID 	= 0;
	
	status = MMPF_I2cm_ReadReg(&gI2cmAttribute_gSensor, GSensor_Reg_GetID, &usdeviceID);
	
	usdeviceID &= 0x00FF;
	
	if( (usdeviceID != GSENSOR_ID_V06) &&
		(usdeviceID != GSENSOR_ID_V07) )
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
	int i;

	for(i=0;i<GSENSOR_DATA_LEN;i++)
	{
		data[i] = m_GSensorOffset.acc_val[i];
	}

	return MMP_ERR_NONE;
}

MMP_ERR	Gsensor_SetSensorOffset(MMP_UBYTE *data)
{
	int i;

	for(i=0;i<GSENSOR_DATA_LEN;i++)
	{
		m_GSensorOffset.acc_val[i] = data[i];
	}

	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_Read_XYZ(GSENSOR_DATA *data) 
{
	MMP_USHORT x_value = 0,y_value = 0,z_value = 0;
  
	// [7:1] sign bit 7 = 0 POSITIVE , bit7 = 1 NEGATIVE
	// X,Y,Z is 2'complement
	MMPF_I2cm_ReadReg(&gI2cmAttribute_gSensor, GSensor_Reg_XOUT, &x_value);
	MMPF_I2cm_ReadReg(&gI2cmAttribute_gSensor, GSensor_Reg_YOUT, &y_value);
	MMPF_I2cm_ReadReg(&gI2cmAttribute_gSensor, GSensor_Reg_ZOUT, &z_value);

	data->acc_val[0] = (MMP_UBYTE)x_value;
	data->acc_val[1] = (MMP_UBYTE)y_value;
	data->acc_val[2] = (MMP_UBYTE)z_value;

	DPRINT("I2C OUT Acceleration X = %d,Y = %d, Z = %d\r\n",
	       data->acc_val[0],
	       data->acc_val[1],
	       data->acc_val[2]);
    memcpy( &m_GSensorShadow, data, sizeof(GSENSOR_DATA) );
	
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_Read_XYZ_WithCompensation(GSENSOR_DATA *sd) 
{
	//int				v;

	Gsensor_Read_XYZ(sd);	
#if 0
	DPRINT("BEFORE COMPENSATION Acceleration X = 0x%x, Y = 0x%x, Z = 0x%x\r\n",
	       sd->acc_val[0],
	       sd->acc_val[1],
	       sd->acc_val[2]);

	//Offset Compensation
	v = ((signed char)sd->acc_val[0] - (signed char)m_GSensorOffset.acc_val[0]);
	if (v > 0x7F) 
		v = 0x7F;
	else if (v < -0x7F) 
	 	v = 0x80;
	sd->acc_val[0] = v;
	
	v = ((signed char)sd->acc_val[1] - (signed char)m_GSensorOffset.acc_val[1]);
	if (v > 0x7F) 
		v = 0x7F;
	else if (v < -0x7F) 
		v = 0x80;
	sd->acc_val[1] = v;
	
	v = ((signed char)sd->acc_val[2] - (signed char)m_GSensorOffset.acc_val[2]);
	if (v > 0x7F) 
		v = 0x7F;
	else if (v < -0x7F) 
		v = 0x80;
	sd->acc_val[2] = v;

	DPRINT("ABSOLUTE OUT Acceleration X = 0x%x, Y = 0x%x, Z = 0x%x\r\n",
	       sd->acc_val[0],
	       sd->acc_val[1],
	       sd->acc_val[2]);
#endif
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_Read_Accel_Avg(GSENSOR_DATA *data)
{
   	MMP_LONG 		xyz_acc_pos[GSENSOR_DATA_LEN];   
   	MMP_LONG 		xyz_acc_neg[GSENSOR_DATA_LEN];
   	MMP_LONG 		xyz_acc_sum[GSENSOR_DATA_LEN];
  	GSENSOR_DATA 	temp;
	MMP_UBYTE		i, j;

	memset(&xyz_acc_pos[0], 0, GSENSOR_DATA_LEN);
	memset(&xyz_acc_neg[0], 0, GSENSOR_DATA_LEN);
	memset(&xyz_acc_sum[0], 0, GSENSOR_DATA_LEN);	

	for(i = 0; i < CALIBRATE_AVG_NUM; i++) 
	{      
		Gsensor_Read_XYZ((GSENSOR_DATA *)&temp);
		
		for(j = 0; j < GSENSOR_DATA_LEN; ++j)
		{ 
			if(temp.acc_val[j] & 0x80)
				xyz_acc_neg[j] += (temp.acc_val[j] & 0x7F);
			else
				xyz_acc_pos[j] += (temp.acc_val[j] & 0x7F);
		}
			
		RTNA_WAIT_MS(5);	
  	}

  	for(i = 0; i < GSENSOR_DATA_LEN; ++i) 
	{
		if( xyz_acc_pos[i] >= xyz_acc_neg[i] )
		{
			xyz_acc_sum[i] = xyz_acc_pos[i] - xyz_acc_neg[i];
			data->acc_val[i] = (xyz_acc_sum[i] / CALIBRATE_AVG_NUM);
		}
		else
		{
			xyz_acc_sum[i] = xyz_acc_neg[i] - xyz_acc_pos[i];	
			data->acc_val[i] = (TO_NEGATIVE_VALUE(xyz_acc_sum[i] / CALIBRATE_AVG_NUM)) & 0xFF;
		}
	}

	return MMP_ERR_NONE;		
}

MMP_ERR Gsensor_CalculateOffset(MMP_UBYTE gAxis, GSENSOR_DATA avg)
{
#if 0//TBD
	switch(gAxis)
	{
		case GSNR_CALIBRATE_G_ON_Z_NEGATIVE:  
			m_GSensorOffset.acc_val[0] =  avg.acc_val[0];    
			m_GSensorOffset.acc_val[1] =  avg.acc_val[1] ;
			m_GSensorOffset.acc_val[2] =  avg.acc_val[2] + DEFAULT_SENSITIVITY;
		break;
		case GSNR_CALIBRATE_G_ON_X_POSITIVE:  
			m_GSensorOffset.acc_val[0] =  avg.acc_val[0] + DEFAULT_SENSITIVITY;//Check
			m_GSensorOffset.acc_val[1] =  avg.acc_val[1] ;
			m_GSensorOffset.acc_val[2] =  avg.acc_val[2] ;
		break;
		case GSNR_CALIBRATE_G_ON_Z_POSITIVE:  
			m_GSensorOffset.acc_val[0] =  avg.acc_val[0] ;    
			m_GSensorOffset.acc_val[1] =  avg.acc_val[1] ;
			m_GSensorOffset.acc_val[2] =  avg.acc_val[2] - DEFAULT_SENSITIVITY;
		break;
		case GSNR_CALIBRATE_G_ON_X_NEGATIVE:  
			m_GSensorOffset.acc_val[0] =  avg.acc_val[0] - DEFAULT_SENSITIVITY;//Check    
			m_GSensorOffset.acc_val[1] =  avg.acc_val[1] ;
			m_GSensorOffset.acc_val[2] =  avg.acc_val[2] ;
		break;
		case GSNR_CALIBRATE_G_ON_Y_NEGATIVE:
			m_GSensorOffset.acc_val[0] =  avg.acc_val[0] ;    
			m_GSensorOffset.acc_val[1] =  avg.acc_val[1] + DEFAULT_SENSITIVITY;
			m_GSensorOffset.acc_val[2] =  avg.acc_val[2] ;
		break;
		case GSNR_CALIBRATE_G_ON_Y_POSITIVE: 
			m_GSensorOffset.acc_val[0] =  avg.acc_val[0] ;    
			m_GSensorOffset.acc_val[1] =  avg.acc_val[1] - DEFAULT_SENSITIVITY;
			m_GSensorOffset.acc_val[2] =  avg.acc_val[2] ;
		break;
		default:  
			return MMP_HIF_ERR_PARAMETER;
		break;	
	}

#else

	m_GSensorOffset.acc_val[0] =  avg.acc_val[0] ;    
	m_GSensorOffset.acc_val[1] =  avg.acc_val[1] ;
	m_GSensorOffset.acc_val[2] =  avg.acc_val[2] ;

	DPRINT("OFFSET Acceleration X = 0x%x, Y = 0x%x, Z = 0x%x\r\n",
	       m_GSensorOffset.acc_val[0],
	       m_GSensorOffset.acc_val[1],
	       m_GSensorOffset.acc_val[2]);

#endif
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
	MMPF_I2cm_WriteReg(&gI2cmAttribute_gSensor, GSensor_Reg_INT1_DURATION, (arg & 0x7f));
		
	return MMP_ERR_NONE;
}

#if (POWER_ON_BY_GSENSOR_EN)
MMP_ERR Gsensor_GetIntGpioStatus(MMP_UBYTE* pstatus)
{
	MMP_UBYTE 	value 	= 0;

	MMPF_PIO_EnableOutputMode(GSENSOR_INT, MMP_FALSE, MMP_TRUE);
	MMPF_PIO_GetData(GSENSOR_INT, &value);
	
	*pstatus = (value & 0xFF);
	
	return MMP_ERR_NONE;
}
#endif

MMP_ERR Gsensor_GetIntStatus(MMP_UBYTE* pstatus)
{
	MMP_USHORT 	value 	= 0;

	MMPF_I2cm_ReadReg(&gI2cmAttribute_gSensor, GSensor_Reg_INT1_STATUS, &value);
	
	*pstatus = (value & 0xFF);

	if( (value & 0xFF) != 0x00 )
	{
		DPRINT("INT STS 0x%02x\r\n", value);
		Gsensor_DumpRegister();
	}

	//DPRINT("Current Interrupt Status 0x%x\r\n",*pstatus);
	
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetPowerSaveMode(MMP_UBYTE mode)
{
	MMPF_I2cm_WriteReg(&gI2cmAttribute_gSensor, GSensor_Reg_CTRL1, (mode & 0xE0) /* Bit7~5 */);

	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetNormalModeDataRate(MMP_UBYTE rate)
{
	MMPF_I2cm_WriteReg(&gI2cmAttribute_gSensor, GSensor_Reg_CTRL1, (rate & 0x18) /* Bit4~3 */);
	
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetInterruptSource(MMP_UBYTE src)
{
	MMP_USHORT usdata;

	MMPF_I2cm_ReadReg(&gI2cmAttribute_gSensor, GSensor_Reg_CTRL4, &usdata);
	
	usdata = (usdata & 0x00FF) | src;

	MMPF_I2cm_WriteReg(&gI2cmAttribute_gSensor, GSensor_Reg_CTRL4, usdata);
	
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetDataRate(MMP_USHORT *wDataRate)
{
	MMP_UBYTE ubValue;
	MMP_UBYTE ubPowerMode, ubNormalMode;

	Gsensor_ReadRegister(GSensor_Reg_CTRL1, &ubValue);

	ubPowerMode  = (ubValue & POWER_MODE_MASK);
	ubNormalMode = (ubValue & NORMAL_MODE_MASK);

	switch(ubPowerMode)
	{
		case POWER_MODE_SHUTDOWN:
			*wDataRate = 0;
		break;
		case POWER_MODE_NORMAL:
			switch(ubNormalMode)
			{
				case DATA_RATE_342HZ:
					*wDataRate = 342;
				break;
				case DATA_RATE_85HZ:
					*wDataRate = 85;
				break;
				case DATA_RATE_42HZ:
					*wDataRate = 42;
				break;
				case DATA_RATE_21HZ:
					*wDataRate = 21;
				break;
			}
		break;
		case POWER_MODE_LOW_32HZ:
			*wDataRate = 32;
		break;
		case POWER_MODE_LOW_16HZ:
			*wDataRate = 16;
		break;
		case POWER_MODE_LOW_8HZ:
			*wDataRate = 8;
		break;
		case POWER_MODE_LOW_4HZ:
			*wDataRate = 4;
		break;
		case POWER_MODE_LOW_2HZ:
			*wDataRate = 2;
		break;
	}
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetDynamicRange(MMP_UBYTE ubDrange)
{
	MMP_UBYTE ubFullSacleRange;

	if(bGsensorID != GSENSOR_ID_V07)
		return MMP_ERR_NONE;

	Gsensor_ReadRegister(GSensor_Reg_CTRL2, &ubFullSacleRange);

	switch(ubDrange)
	{
		case 2:
			ubFullSacleRange &= ~DYNAMIC_RANGE_MASK;	
			ubFullSacleRange |= DYNAMIC_RANGE_2;
		break;
		case 4:
			ubFullSacleRange &= 0x7F;
			ubFullSacleRange |= DYNAMIC_RANGE_4;
		break;
		case 8:
			ubFullSacleRange &= 0xFF;
			ubFullSacleRange |= DYNAMIC_RANGE_8;
		break;
		default:
			return 1;	// ERROR!
	}
	Gsensor_WriteRegister(GSensor_Reg_CTRL2, ubFullSacleRange);
	
	switch (ubDrange) 
	{
		case 2:
		 	gGsensor_Attribute.nMaxG	= MAX_2G;
		 	gGsensor_Attribute.ub1G	 	= 0x40;
		 	gGsensor_Attribute.ub1G_Err = 0x08;
		break;
		case 4:
		 	gGsensor_Attribute.nMaxG	= MAX_4G;
		 	gGsensor_Attribute.ub1G	 	= 0x20;
		 	gGsensor_Attribute.ub1G_Err = 0x04;
		break;
		case 8:
		 	gGsensor_Attribute.nMaxG	= MAX_8G;
		 	gGsensor_Attribute.ub1G	 	= 0x10;
		 	gGsensor_Attribute.ub1G_Err = 0x02;
		break;
	}
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetDynamicRange(MMP_UBYTE *ubDrange)
{
	MMP_UBYTE ubValue;
	MMP_UBYTE ubRange;

	if(bGsensorID != GSENSOR_ID_V07)
		return MMP_ERR_NONE;

	Gsensor_ReadRegister(GSensor_Reg_CTRL2, &ubValue);

	ubRange = (ubValue & DYNAMIC_RANGE_MASK);

	switch(ubRange)
	{
		case DYNAMIC_RANGE_2:
			*ubDrange = 2;
		break;
		case DYNAMIC_RANGE_4:
			*ubDrange = 4;
		break;
		case DYNAMIC_RANGE_8:
			*ubDrange = 8;
		break;
		default:
			*ubDrange = 1;
		break;
	}
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_EnableIntXYZ(int ex, int ey, int ez)
{
	MMP_ERR 	status 	= MMP_ERR_NONE;
	MMP_UBYTE	arg 	= 0;
	
	if (ex)	arg |= ENABLE_X_HIGH_G;
	if (ey)	arg |= ENABLE_Y_HIGH_G;
	if (ez)	arg |= ENABLE_Z_HIGH_G;
	
	status = Gsensor_WriteRegister(GSensor_Reg_INT1_CONFIG, arg); //Enale INT for XYZ direction
	
	return status;
}

MMP_ERR Gsensor_SetGroundAxis(int arg)
{
	MMP_ERR status = MMP_ERR_NONE;

	if ((arg != 0) &&
	    (arg != 1) &&
	    (arg != 2))
		status = 1;		// ERROR!
	else
		gGsensor_Attribute.ubGroundAxis = (MMP_UBYTE)arg;

	return status;
}

void Gsensor_Initial(void)
{
	if(bGsensorID==GSENSOR_ID_V07)
	{
		Gsensor_SetDynamicRange(gGsensor_Attribute.ubRange);
#if (POWER_ON_BY_GSENSOR_EN)
		Gsensor_WriteRegister(GSensor_Reg_CTRL4, 0x38);
#else
		Gsensor_WriteRegister(GSensor_Reg_CTRL4, 0x48); //Link INT source
#endif
		Gsensor_WriteRegister(GSensor_Reg_INT1_DURATION, 0xA);
		
		Gsensor_WriteRegister(GSensor_Reg_INT1_CONFIG, ALL_6D_HIGH_G); //Enale INT for XYZ direction	
	} 
	else 
	{
		gGsensor_Attribute.ubRange  = 2;
		gGsensor_Attribute.nMaxG	= MAX_2G;
		gGsensor_Attribute.ub1G		= 0x40;	
		gGsensor_Attribute.ub1G_Err = 0x08;
	}
}

MMP_ERR Gsensor_IOControl(MMP_UBYTE cmd, MMP_UBYTE* arg)
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
			status |= Gsensor_Calibration(*arg);
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
			int		thg;
			
			thg = (int)arg;

			if (thg == 0) 
			{
				Gsensor_EnableIntXYZ(0, 0, 0);
				break;
			}
			
			if ((unsigned int)arg > (unsigned int)gGsensor_Attribute.nMaxG)
				thg = gGsensor_Attribute.nMaxG;
			
			thg 	= MAP2HW_G(thg, gGsensor_Attribute);
			status 	= MMPF_I2cm_WriteReg(&gI2cmAttribute_gSensor, GSensor_Reg_INT1_THD, (MMP_UBYTE)thg);
			
			DPRINT("Set Threshold %d 0x%x\r\n", arg, thg);
			
			Gsensor_EnableIntXYZ(gGsensor_Attribute.ubGroundAxis != MMP_GSENSOR_AXIS_X,
								 gGsensor_Attribute.ubGroundAxis != MMP_GSENSOR_AXIS_Y,
								 gGsensor_Attribute.ubGroundAxis != MMP_GSENSOR_AXIS_Z);
			break;
		}

		case GSNR_CMD_SET_INT_DURATION: 
			status |= Gsensor_SetIntDuration(*arg);
		break;
		
		case GSNR_CMD_GET_INT_STATUS:
			if (gGsensor_Attribute.nInited) {
				status |= Gsensor_GetIntStatus(arg);
			} else {
				status = 1;	// ERROR!
				*arg   = 0;
			}
		break;
		
		case GSNR_CMD_SET_POWER_SAVE:
			status |= Gsensor_SetPowerSaveMode(*arg);
		break;
			
		case GSNR_CMD_SET_DATA_RATE:
			status |= Gsensor_SetNormalModeDataRate(*arg);
		break;

		case GSNR_CMD_SET_INT_SOURCE:
			status |= Gsensor_SetInterruptSource(*arg);
		break;
		
		case GSNR_CMD_GET_DATA_RATE:
			status |= Gsensor_GetDataRate((MMP_USHORT*)arg);
		break;
		
		case GSNR_CMD_SET_DYNA_RANGE:
			status |= Gsensor_SetDynamicRange(*arg);
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
						*arg = kLastPosition;
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
						*arg = kLastPosition;
						return kLastPosition;
					}
					if (kDwCnt <= STABLE_CNT) 
					{
						kUpCnt = 0;
						kDwCnt++;
					}
				}
			}
			*arg = GSNR_POSITION_NOCHANGE;
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

#endif//GSENSOR_CONNECT_ENABLE

