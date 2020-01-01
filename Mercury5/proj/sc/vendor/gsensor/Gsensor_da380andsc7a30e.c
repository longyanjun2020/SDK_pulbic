/*===========================================================================
 * Include file 
 *===========================================================================*/ 
#include "Config_SDK.h"
#include "config_fw.h"
#include "os_wrap.h"
#include "mmpf_pio.h"
#include "mmpf_timer.h"
#include "lib_retina.h"
#include "mmpf_gsensor.h"
#include "GSensor_ctrl.h"
#include "AIT_Init.h"
#include "drv_bus_i2c.h"
#include "ahc_utility.h"

#if defined(__GNUC__)
#include "vm_types.ht"
#endif

#if (GSENSOR_CONNECT_ENABLE && GSENSOR_MODULE == GSENSOR_MODULE_DA380ANDSC7A30E)
#include "Gsensor_da380andsc7a30e.h"




typedef unsigned short u16;
typedef short i16;
typedef unsigned char u8;

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define	TO_NEGATIVE_VALUE(x)	( (~x + 0x01) | 0x200 )
#define	TO_ABSOLUTE_VALUE(x)	( (x > 0x200)? (0x400 - x):(x) )
#define	TO_XXXX_VALUE(x)		(((x)> 0x20)?((~((x)&(~0x20)))^0x1f):((x)))
#define	LOW_BOUND_1G(s)			((signed char)s->us1G - (signed char)s->ub1G_Err)
#define ABS(x) 					((x) > 0 ? (x) : -(x))
#define	MAP2HW_G(g, s)			((g * s->us1G) / SCALE_G)
#define	STABLE_CNT				(0)
#define GET_DIFF(x,y)			((x) > (y))?((x) -(y)):((y)-(x))

/*===========================================================================
 * Global varible
 *===========================================================================*/

static GSENSOR_DATA			m_GSensorOffset 		= {0, 0, 0};
#if (GSENSOR_DETECT_MODE == GSNESOR_DETECT_DIFF)
static MMP_BOOL	 			bGsensorCalibrated   	= MMP_FALSE;
#endif
MMP_USHORT					ApicalDeviceID = 0x00;
static int					kfirstread 				= 0;
static int					kUpCnt 					= 0;
static int					kDwCnt 					= 0;
static int					kLastPosition 			= GSNR_POSITION_UNKNOWN;

static GSNR_DEV_INFO		_gGsnrDevInfo =
{
	GSENSOR_ID_SC7A30E,	// usDeviceID
	8,					// usDynamicRange
	DEFAULT_SENSITIVITY,	// usSensitivity
	200,	// usODR
};

static I2COptions_t	_gI2CCfg_sc7a30e = 
{
	GSENSOR_SLAVE_ADDR_SC7A30E,	// Slave address
	MMP_I2CM0,					// Channel
	I2C_PAD_MODE_1,				// Pad
	0,							// DMA enable
	0,							// DMA address
	1,							// support restart mode or not
	I2C_SLOWSPEED_MODE_200KHZ,	// Speed
	I2C_CTRL_MODE_HW,			// Control Mode
	I2C_SEN_TYPE_OTHER,			// Sensor Type
	I2C_ONE_BYTE_DATA,			// Data Length
	I2C_ONE_BYTE_ADDR			// Address Length
};

static const I2COptions_t	_gI2CCfg_DA312 = 
{
	GSENSOR_SLAVE_ADDR, 		// Slave address
	MMP_I2CM0,					// Channel
	I2C_PAD_MODE_1, 			// Pad
	0,							// DMA enable
	0,							// DMA address
	1,							// support restart mode or not
	I2C_SLOWSPEED_MODE_200KHZ,	// Speed
	I2C_CTRL_MODE_HW,			// Control Mode
	I2C_SEN_TYPE_OTHER, 		// Sensor Type
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

//#define	DPRINT( ... ) {}
#define	DPRINT( ... ) printc( __VA_ARGS__ )
#endif

MMP_ERR Gsensor_EnableIntXYZ(int ex, int ey, int ez);




/*===========================================================================
 * Main body
 *===========================================================================*/\
#ifdef ALL_FW

MMP_BOOL SC7A30E_Gsensor_Probe(void)
{
	MMP_ERR 		status = -1;
	MMP_USHORT 	usdeviceID 	= 0;

	MMPF_I2cm_ReadReg(&_gI2CCfg_sc7a30e, GSensor_Sc7a30e_Reg_ChipID, (MMP_USHORT*)&usdeviceID);
    	if(usdeviceID == GSENSOR_ID_SC7A30E)
        	return MMP_TRUE;

	return MMP_FALSE;
}
 MMP_BOOL DA312_Gsensor_Probe(void)
{
	MMP_ERR		status = -1;
	MMP_USHORT	usdeviceID 	= 0;

	MMPF_I2cm_ReadReg(&_gI2CCfg_DA312, GSensor_Reg_ChipID, (MMP_USHORT*)&usdeviceID);
	if(usdeviceID == GSENSOR_ID_DA312)
    	return MMP_TRUE;

	return MMP_FALSE;
}
/*
MMP_ERR Gsensor_Config_I2CM(struct _3RD_PARTY_GSENSOR *pthis, GSNR_I2CM_ATTRIBUTE *psI2cmattr)
{
	_gI2CCfg_DA312.i2cmID 		= psI2cmattr->i2cmID;
	_gI2CCfg_DA312.ubPadNum 	= psI2cmattr->ubPadNum;
	_gI2CCfg_DA312.ulI2cmSpeed  = psI2cmattr->ulI2cmSpeed;

    return MMP_ERR_NONE;
}
*/
MMP_ERR Gsensor_ReadRegister(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE reg , MMP_UBYTE* pval)
{
	MMP_USHORT data;

	if (reg >= GSensor_Reg_INVALID)
	{
		DPRINT("GsnrRead-->Wrong Register Address\r\n");
		return MMP_ERR_NONE;
	}
	if(ApicalDeviceID == GSENSOR_ID_DA312)
	{
		MMPF_I2cm_ReadReg(&_gI2CCfg_DA312, (MMP_USHORT)reg, (MMP_USHORT*)&data);
	}
	else
	{
		MMPF_I2cm_ReadReg(&_gI2CCfg_sc7a30e, (MMP_USHORT)reg, (MMP_USHORT*)&data);
	}
	*pval = (MMP_UBYTE)(data & 0x00FF);
	
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_WriteRegister(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE reg , MMP_UBYTE val)
{
	MMP_ERR st= MMP_ERR_NONE;
	if (reg >= GSensor_Reg_INVALID)
	{
		DPRINT("GsnrWrite-->Wrong Register Address\r\n");
		return MMP_ERR_NONE;
	}
	if(ApicalDeviceID == GSENSOR_ID_DA312)
	{
		st = MMPF_I2cm_WriteReg(&_gI2CCfg_DA312, (MMP_USHORT)reg, (MMP_USHORT)val);
	}
	else
	{
		st = MMPF_I2cm_WriteReg(&_gI2CCfg_sc7a30e, (MMP_USHORT)reg, (MMP_USHORT)val);
	}
	return MMP_ERR_NONE;
}

void Gsensor_DumpRegister(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr)
{
#if (GSENSOR_DBG_MSG)

	MMP_LONG	i;
	MMP_UBYTE	rv;
	MMP_UBYTE	regs[] = {		0x0F, 0x20, 0x21, 0x22, 0x23, 
								0x24, 0x25, 0x28, 0x29, 0x2A, 
								0x2B, 0x2C, 0x2D, 0x30, 0x31,
								0x32, 0x33
							};

	DPRINT("====LIS3DH Registers====\r\n");
							        
	for (i = 0; i < sizeof(regs); i++) 
	{
		pthis->MMPF_Gsensor_GetReg(pthis, regs[i], &rv);
		DPRINT("Reg: 0x%02x, 0x%02x\r\n", regs[i], rv);
	}
	
	DPRINT("PROPERTY id = 0x%x, Range = %d, Sens = %d, GroundAxis = %d, 1G = 0x%x , ErrG = 0x%x, MaxG = %d\r\n",
	       pgsnr_attr->ubGsensorID,
	       pgsnr_attr->ubRange,
	       pgsnr_attr->usSensitive,
	       pgsnr_attr->ubGroundAxis,
	       pgsnr_attr->us1G,
	       pgsnr_attr->ub1G_Err,
	       pgsnr_attr->nMaxG);
#endif
}

MMP_ERR Gsensor_ReadOffsetFromFile(struct _3RD_PARTY_GSENSOR *pthis)
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

MMP_ERR Gsensor_WriteOffsetToFile(struct _3RD_PARTY_GSENSOR *pthis)
{
	//DramToFile(GSNR_OFFSET_FILENAME, (INT8*)&m_GSensorOffset,sizeof(GSENSOR_DATA));
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_ResetDevice(struct _3RD_PARTY_GSENSOR *pthis) 
{
	MMP_ERR 	status 	= MMP_ERR_NONE;
	MMP_UBYTE	reg;

	#if 0	
	for (reg = 0x1F; reg < 0x28; reg++) 
	status |= pthis->MMPF_Gsensor_SetReg(pthis, reg, 0);
	#endif
	return status; 
}
MMP_ERR Gsensor_ReadDeviceID_DA380(struct _3RD_PARTY_GSENSOR *pthis, MMP_USHORT *pusDevID)
{
	MMP_ERR 	err 		= MMP_ERR_NONE;
	MMP_UBYTE	ubDevID 	= 0;
	
	err = pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_ChipID, &ubDevID);

	if (err != MMP_ERR_NONE) {
		*pusDevID = 0x0000;
	}
	else {
		*pusDevID = ubDevID;
	}
	return err; 
}

MMP_ERR Gsensor_ReadDeviceID_SC7A30E(struct _3RD_PARTY_GSENSOR *pthis, MMP_USHORT *pusDevID)
{
	MMP_ERR 	err 		= MMP_ERR_NONE;
	MMP_UBYTE	ubDevID 	= 0;
	
	err = pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Sc7a30e_Reg_ChipID, &ubDevID);

	if (err != MMP_ERR_NONE) {
		*pusDevID = 0x0000;
	}
	else {
		*pusDevID = ubDevID;
	}
	return err; 
}

MMP_ERR Gsensor_ReadDeviceID(struct _3RD_PARTY_GSENSOR *pthis, MMP_USHORT *pusDevID)
{
	if(ApicalDeviceID == GSENSOR_ID_SC7A30E)
		return Gsensor_ReadDeviceID_SC7A30E(pthis, pusDevID);
	else if(ApicalDeviceID == GSENSOR_ID_DA312)
		return Gsensor_ReadDeviceID_DA380(pthis, pusDevID);

	return MMP_ERR_NONE;
}

MMP_ERR	Gsensor_GetSensorOffset(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE *data)
{
	int i;

	for(i=0;i<GSENSOR_DATA_LEN;i++)
	{
		data[i] = m_GSensorOffset.acc_val[i];
	}

	return MMP_ERR_NONE;
}

MMP_ERR	Gsensor_SetSensorOffset(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE *data)
{
	int i;

	for(i=0;i<GSENSOR_DATA_LEN;i++)
	{
		m_GSensorOffset.acc_val[i] = data[i];
	}

	return MMP_ERR_NONE;
}
MMP_ERR Gsensor_Read_XYZ_DA380(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *data) 
{
	MMP_USHORT x_value = 0,y_value = 0,z_value = 0,SR;
	MMP_USHORT x_value_lsb = 0, x_value_msb = 0, y_value_lsb = 0, y_value_msb = 0, z_value_lsb = 0, z_value_msb = 0;
	MMP_USHORT  tempdata[6] = {0};
	int i = 0;

	MMPF_I2cm_ReadBurstData(&_gI2CCfg_DA312,GSensor_Reg_XOUT_L,&tempdata[0],6);
	x_value = (tempdata[1])>>2;//HIGH 8bit 
	y_value = (tempdata[3])>>2;
	z_value = (tempdata[5])>>2;

	data->acc_val[0] = TO_XXXX_VALUE(x_value);
	data->acc_val[1] = TO_XXXX_VALUE(y_value);  
	data->acc_val[2] = TO_XXXX_VALUE(z_value)-0xf;

	return MMP_ERR_NONE;
}
MMP_ERR Gsensor_Read_XYZ_SC7A30E(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *data) 
{
	u16 x_value = 0, y_value = 0, z_value = 0,SR;
	u16 tempdata[6] = {0};
	i16 temp_value = 0;
	int i = 0;
	
	for(i=0; i<6; i++) {
		pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Sc7a30e_Reg_XOUT_L+i, (u8*)(tempdata+i));
	}
	
	x_value = (((tempdata[1] << 8) | (tempdata[0] & 0xff)) >> 4);
	y_value = (((tempdata[3] << 8) | (tempdata[2] & 0xff)) >> 4);
	z_value = (((tempdata[5] << 8) | (tempdata[4] & 0xff)) >> 4);

	temp_value = (x_value & 0x800/*为负值*/) ? (x_value | 0xF000) : (x_value);
	x_value = (u16)(temp_value + 2048);
	temp_value = (y_value & 0x800/*为负值*/) ? (y_value | 0xF000) : (y_value);
	y_value = (u16)(temp_value + 2048);
	temp_value = (z_value & 0x800/*为负值*/) ? (z_value | 0xF000) : (z_value);
	z_value = (u16)(temp_value + 2048);

	printc(FG_GREEN("GXYZ:%d\t%d\t%d\r\n"),x_value,y_value,z_value);
	
	data->acc_val[0] = x_value>>4;
	data->acc_val[1] = y_value>>4;
	data->acc_val[2] = z_value>>4;
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_Read_XYZ(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *data) 
{
	if(ApicalDeviceID == GSENSOR_ID_DA312)
	{
		Gsensor_Read_XYZ_DA380(pthis,data);
	}
	else if(ApicalDeviceID == GSENSOR_ID_SC7A30E)
	{   
		Gsensor_Read_XYZ_SC7A30E(pthis,data);
	}

	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_Read_XYZ_WithCompensation_SC7A30E(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *data)
{
    static GSENSOR_DATA prev;
    GSENSOR_DATA cur;

    Gsensor_Read_XYZ(pthis,&cur);
	if(kfirstread == 0)
	{
		kfirstread = 1;
		data->acc_val[0] = 0;
		data->acc_val[1] = 0;
		data->acc_val[2] = 0;
	}
	else
	{
	    data->acc_val[0] = GET_DIFF(cur.acc_val[0],prev.acc_val[0]);
	    data->acc_val[1] = GET_DIFF(cur.acc_val[1],prev.acc_val[1]);
	    data->acc_val[2] = GET_DIFF(cur.acc_val[2],prev.acc_val[2]);
	}
    prev=cur;
    return MMP_ERR_NONE;

}

MMP_ERR Gsensor_Read_XYZ_WithCompensation_DA380(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *data) 
{	
	MMP_USHORT x_value = 0,y_value = 0,z_value = 0;
	MMP_USHORT x_value_lsb = 0, x_value_msb = 0, y_value_lsb = 0, y_value_msb = 0, z_value_lsb = 0, z_value_msb = 0;
	MMP_UBYTE  i;
	MMP_UBYTE  ubTempX, ubTempY, ubTempZ;
	MMP_USHORT	tempdata[6] = {0};

	MMPF_I2cm_ReadBurstData(&_gI2CCfg_DA312,GSensor_Reg_XOUT_L,&tempdata[0],6);

	x_value = (tempdata[1])>>2;//HIGH 8bit 
	y_value = (tempdata[3])>>2;
	z_value = (tempdata[5])>>2;
	
	data->acc_val[0] = x_value;
	data->acc_val[1] = y_value;  
	data->acc_val[2] = z_value;
		
	ubTempX = data->acc_val[0];
	ubTempY = data->acc_val[1];
	ubTempZ = data->acc_val[2];

	data->acc_val[0] = TO_XXXX_VALUE(x_value);
	data->acc_val[1] = TO_XXXX_VALUE(y_value);  
	data->acc_val[2] = TO_XXXX_VALUE(z_value)-0xf;

	for(i=0;i<GSENSOR_DATA_LEN;i++)
	{
		if(m_GSensorOffset.acc_val[i] >= 0x80)
		{
			if(data->acc_val[i] >= 0x80)
			{
				data->acc_val[i] = data->acc_val[i] + (0x100 - m_GSensorOffset.acc_val[i]);
				if(data->acc_val[i] >= 0xFF)
				data->acc_val[i] = 0xFF;
			}else
			{
				data->acc_val[i] = data->acc_val[i] + (0x100 - m_GSensorOffset.acc_val[i]);
				//if(data->acc_val[i] <= 0x00)
				//data->acc_val[i] = 0x00;
			}
		}
		else
		{
			if(data->acc_val[i] >= 0x80)
			{
				data->acc_val[i] = data->acc_val[i] + m_GSensorOffset.acc_val[i];
				if(data->acc_val[i] >= 0xFF)
				data->acc_val[i] = 0xFF;
			}
			else
			{
				if(data->acc_val[i] >= m_GSensorOffset.acc_val[i])
				data->acc_val[i] = data->acc_val[i] - m_GSensorOffset.acc_val[i];
				else
				data->acc_val[i] = 0;
			}
		}
	}
	
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_Read_XYZ_WithCompensation(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *data) 
{
	if(ApicalDeviceID == GSENSOR_ID_DA312)
	{
		Gsensor_Read_XYZ_WithCompensation_DA380(pthis,data);
	}
	else
	{
		Gsensor_Read_XYZ_WithCompensation_SC7A30E(pthis,data);
	}
	
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_Read_Accel_Avg(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *data)
{
#if 1
   	MMP_LONG 		xyz_acc_pos[GSENSOR_DATA_LEN];   
   	MMP_LONG 		xyz_acc_neg[GSENSOR_DATA_LEN];
   	MMP_ULONG 		xyz_acc_sum[GSENSOR_DATA_LEN];
  	GSENSOR_DATA 	temp;
	MMP_UBYTE		i, j;

	memset(&xyz_acc_pos[0], 0, GSENSOR_DATA_LEN * sizeof(MMP_LONG));
	memset(&xyz_acc_neg[0], 0, GSENSOR_DATA_LEN * sizeof(MMP_LONG));
	memset(&xyz_acc_sum[0], 0, GSENSOR_DATA_LEN * sizeof(MMP_ULONG));	
	
	for(i = 0; i < CALIBRATE_AVG_NUM; i++) 
	{      
		pthis->MMPF_Gsensor_Read_XYZ(pthis, (GSENSOR_DATA *)&temp);
		
		for(j = 0; j < GSENSOR_DATA_LEN; j++)
		{ 	 
			if(temp.acc_val[j] & 0x80)
				xyz_acc_neg[j] += (0x100 - temp.acc_val[j]);
			else
				xyz_acc_pos[j] += (temp.acc_val[j] & 0x7F);		
		}
			
		RTNA_WAIT_MS(10);	   
  	}	
	DPRINT("=====Read Average======\r\n");  	
  	for(i = 0; i < GSENSOR_DATA_LEN; i++) 
	{
			if( xyz_acc_pos[i] >= xyz_acc_neg[i] )
			{
				xyz_acc_sum[i] = xyz_acc_pos[i] - xyz_acc_neg[i];
				data->acc_val[i] = (xyz_acc_sum[i] / CALIBRATE_AVG_NUM);
			}
			else
			{
				xyz_acc_sum[i] = xyz_acc_neg[i] - xyz_acc_pos[i];	
				data->acc_val[i] = (0x100 - ((xyz_acc_sum[i] / CALIBRATE_AVG_NUM)));
			}
					
			DPRINT("xyz_acc_sum[i] : %d\r\n",xyz_acc_sum[i]); 	
			//data->acc_val[i] = (xyz_acc_sum[i] / CALIBRATE_AVG_NUM);	
	}
#endif
	return MMP_ERR_NONE;		
}


MMP_ERR Gsensor_CalculateOffset(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA avg)
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
MMP_ERR Gsensor_GetIntStatus_SC7A30E(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE* pstatus)
{
    MMP_UBYTE   ubStatus= 0,ubStatus1 = 0;
    MMP_UBYTE   ubEn    = 0;

    *pstatus = (ubStatus |ubEn | ubStatus1);
    return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetIntStatus_DA380(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE* pstatus)
{
	MMP_UBYTE   ubStatus= 0,ubStatus1 = 0;
	MMP_UBYTE   ubEn    = 0;

	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_Motion_INT, &ubEn);
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_Data_INT, &ubStatus);
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_Tap_Active_Statu, &ubStatus1);

	printc("Gsensor_GetIntStatus:%x  \r\n",(ubStatus & ubEn ));
	*pstatus = (ubStatus |ubEn | ubStatus1);

	return MMP_ERR_NONE;
}
MMP_ERR Gsensor_GetIntStatus(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE* pstatus)
{
	if(ApicalDeviceID == GSENSOR_ID_DA312)
	{
		Gsensor_GetIntStatus_DA380(pthis,pstatus);
	}
	else if(ApicalDeviceID == GSENSOR_ID_SC7A30E)
	{   
		Gsensor_GetIntStatus_SC7A30E(pthis,pstatus);
	}
}
MMP_ERR Gsensor_SetPowerSaveMode(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE mode)
{	
#if 0
	MMP_UBYTE value;
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_CTRL1, &value);
	value &= 0x0F;
	pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL1, value);
#endif
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
	MMP_UBYTE ubFullSacleRange;
	
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_Grange,&ubFullSacleRange);
	
	ubFullSacleRange &= ~DYNAMIC_RANGE_MASK;	
	switch(ubDrange)
	{
		
		case 2:
			ubFullSacleRange |= DYNAMIC_RANGE_2;
		break;
		case 4:
			ubFullSacleRange |= DYNAMIC_RANGE_4;
		break;
		case 8:
			ubFullSacleRange |= DYNAMIC_RANGE_8;
		break;
		case 16:
			ubFullSacleRange |= DYNAMIC_RANGE_16;
		break;
		
		default:
			return MMP_PERIPHERAL_ERR_ACCESS;
	}
	
	pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_Grange, ubFullSacleRange);

#define GSENSOR_VALID_ADC_BITS			(16)

	// Critical section
	// Update device info.
	_gGsnrDevInfo.usDynamicRange = ubDrange;
	_gGsnrDevInfo.usSensitivity = (1<<GSENSOR_VALID_ADC_BITS)/(ubDrange<<1);
	// Critical section
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetDynamicRange_DA380(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE *ubDrange)
{
	*ubDrange = (MMP_UBYTE)_gGsnrDevInfo.usDynamicRange;
	return MMP_ERR_NONE;
}
MMP_ERR Gsensor_GetDynamicRange_SC7A30E(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE *ubDrange)
{
	*ubDrange = (MMP_UBYTE)_gGsnrDevInfo.usDynamicRange;
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetDynamicRange(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE *ubDrange)
{
	if(ApicalDeviceID == GSENSOR_ID_DA312)
	{
		Gsensor_GetDynamicRange_DA380(pthis,ubDrange);
	}
	else if(ApicalDeviceID == GSENSOR_ID_SC7A30E)
	{   
		Gsensor_GetDynamicRange_SC7A30E(pthis,ubDrange);
	}
    return MMP_ERR_NONE;
}
MMP_ERR Gsensor_SetGroundAxis(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr, MMP_UBYTE arg)
{
	MMP_ERR status = MMP_ERR_NONE;
	return status;
}
static void G_SC7A30E_open_interrupt(struct _3RD_PARTY_GSENSOR *pthis, int sensitivity)
{
	MMP_UBYTE uTmp = 0;
	MMP_UBYTE uIntSens[4] = {0x0c/*192mg*/, 0x18/*384mg*/, 0x30/*768mg*/,0x6c/*960mg*/};

#if 0
	m_I2cmAttr_gsensor_sc7a30e.nSlaveID = 0x32 >> 1;
	pthis->MMPF_Gsensor_SetReg(pthis,0x24, 0x80);
#endif

	_gI2CCfg_sc7a30e.nSlaveID = GSENSOR_SLAVE_ADDR_SC7A30E >> 1;

	//pthis->MMPF_Gsensor_SetReg(pthis,0x24, 0, 0x80);
	pthis->MMPF_Gsensor_SetReg(pthis,0x25,  0x02);//0x02==>LOW Valid￡?0x00==>High Valid
	pthis->MMPF_Gsensor_SetReg(pthis,0x20,0x47);//DR 0x37:25hz,0x47:50hz,
	pthis->MMPF_Gsensor_GetReg(pthis, 0x26,&uTmp);
	pthis->MMPF_Gsensor_SetReg(pthis,0x21, 0x0D/*0x0C*/);//高通使能
	pthis->MMPF_Gsensor_SetReg(pthis,0x23, 0x80);//量程+-2g
	//pthis->MMPF_Gsensor_SetReg(pthis,0x23, 0x90);//量程+-4g
	
	switch(sensitivity)
	{
		case 1:
			pthis->MMPF_Gsensor_SetReg(pthis,0x3A,  uIntSens[0]);//触发阈值,越高越不灵敏
			break;
		case 2:
			pthis->MMPF_Gsensor_SetReg(pthis,0x3A,  uIntSens[1]);//触发阈值
			break;
		case 3:
			pthis->MMPF_Gsensor_SetReg(pthis,0x3A,  uIntSens[2]);//触发阈值
			break;
		case 4:
			pthis->MMPF_Gsensor_SetReg(pthis,0x3A,  uIntSens[3]);//触发阈值
			break;
		default:
			pthis->MMPF_Gsensor_SetReg(pthis,0x3A,  uIntSens[1]);//触发阈值
			break;
	}
	
	//pthis->MMPF_Gsensor_SetReg(pthis,0x3A, 0, uIntSens[2]);
	pthis->MMPF_Gsensor_SetReg(pthis,0x3B,  0x7F);
	pthis->MMPF_Gsensor_SetReg(pthis,0x3C, 0x64);//
	//pthis->MMPF_Gsensor_SetReg(pthis,0x25, 0, 0x00);//0x02==>LOW Valid￡?0x00==>High Valid
	pthis->MMPF_Gsensor_SetReg(pthis,0x38,  0x15);
	
	pthis->MMPF_Gsensor_SetReg(pthis,0x22,  0x80);//enable interrupt
	//clear latch and set latch mode
	pthis->MMPF_Gsensor_GetReg(pthis, 0x39,&uTmp);
}

MMP_ERR Gsensor_Initial_DA380(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr)
{
    MMP_UBYTE u8temp = 0;
    int i;

    pthis->MMPF_Gsensor_ReadDeviceID(pthis, pgsnr_attr); 
    if(pgsnr_attr->ubGsensorID == GSENSOR_ID_DA312)
    {	
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_Config, 0x24);
		MMPF_OS_Sleep(10);
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_Grange, 0x00);
		pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_mode_BW, 0x5e);
		pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_ODR_Axis_DIS, 0x06);
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_INT_pin_Cof, 0x00);

		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_INT_SET1, 0x07);
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_Active_DURA, 0x03);
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_Active_TH, 0x1b);
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_INT_MAP1, 0x04);
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_INT_LTACH, 0x06);
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_engineer_mode, 0x83);
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_engineer_mode, 0x69);
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_engineer_mode, 0xBD);
		
        pgsnr_attr->nInited = 1;
   		printc(FG_GREEN("Gsensor_Initial  Succes  ID %x \r\n"),pgsnr_attr->ubGsensorID );
    } 
    else 
    {
        printc(FG_RED("Wrong G-Sensor ID for DA312\r\n"));

        pgsnr_attr->ubRange     = 2;
        pgsnr_attr->nMaxG	    = MAX_2G;
        pgsnr_attr->us1G		= 0x40;	
        pgsnr_attr->ub1G_Err    = 0x08;
    }
    return MMP_ERR_NONE;
}

MMP_ERR Gsensor_Initial_SC7A30E(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr)
{
	MMP_UBYTE u8temp = 0;
	int i;

	_gI2CCfg_sc7a30e.nSlaveID=GSENSOR_SLAVE_ADDR_SC7A30E >> 1;
	pthis->MMPF_Gsensor_ReadDeviceID(pthis, pgsnr_attr);

    if(pgsnr_attr->ubGsensorID == GSENSOR_ID_SC7A30E)
    {
		printc("Gsensor_Initial SC7A30E\r\n");

		pthis->MMPF_Gsensor_SetReg(pthis,0x22, 0x00);//Close Interrupt
		pthis->MMPF_Gsensor_SetReg(pthis,0x38, 0x00);
		pthis->MMPF_Gsensor_SetReg(pthis,0x24, 0x80);//reboot ic
		pthis->MMPF_Gsensor_SetReg(pthis,0x20, 0x47);//DR 50hz
		pthis->MMPF_Gsensor_GetReg(pthis, 0x20, &u8temp);
		//printc("reg 0x20 %x\r\n",u8temp);
		//pthis->MMPF_Gsensor_SetReg(pthis,0x23, 0x80);//á?3ì+-2g
		//pthis->MMPF_Gsensor_SetReg(pthis,0x23, 0x90);//á?3ì+-4g
		pthis->MMPF_Gsensor_SetReg(pthis,0x23, 0x80);//á?3ì+-8g
		pthis->MMPF_Gsensor_SetReg(pthis,0x25,  0x02);//0x02==>LOW Valid￡?0x00==>High Valid
		//SC7A30E_open_interrupt(pthis,2);//gaoc
		pgsnr_attr->nInited = 1;
	}
	else
	{
		//printc(FG_RED("Wrong G-Sensor ID for GSENSOR_ID_SC7A30E\r\n"));
		pgsnr_attr->ubRange     = 2;
		pgsnr_attr->nMaxG	    = MAX_4G;
		pgsnr_attr->us1G	    = 0x40;
		pgsnr_attr->ub1G_Err    = 0x08;
	}
	
	return MMP_ERR_NONE;
}
MMP_ERR Gsensor_Initial(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr)
{
	if(ApicalDeviceID == GSENSOR_ID_DA312)
	{
		Gsensor_Initial_DA380(pthis,pgsnr_attr);
	}
	else if(ApicalDeviceID == GSENSOR_ID_SC7A30E)
	{   
		Gsensor_Initial_SC7A30E(pthis,pgsnr_attr);
	}
    return MMP_ERR_NONE;
}
void Gsensor_Initial_PowerOff_DA380(struct _3RD_PARTY_GSENSOR *pthis,MMP_UBYTE ubPowerGsenOnValue)
{
    MMP_UBYTE	int_status;
	MMP_ERR		err = MMP_ERR_NONE;
	MMP_USHORT	usDevID = 0;

    //DPRINT("### %s - %d\r\n", __func__, ubPowerGsenOnValue);
	Gsensor_DumpRegister(pthis,&_gGsnrDevInfo);
	
    err = pthis->MMPF_Gsensor_ReadDeviceID(pthis, &usDevID); 

	if (err != MMP_ERR_NONE) {
		return;
	}
    
    if(usDevID == GSENSOR_ID_DA312)
	{	

		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_Config, 0x24);
		MMPF_OS_Sleep(10);
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_Grange, 0x00);
		pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_mode_BW, 0x5e);
		pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_ODR_Axis_DIS, 0x06);
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_INT_pin_Cof, 0x00); //Low

		if(ubPowerGsenOnValue == 0)
			pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_INT_SET1, 0x00);  //disable
		//else if(AHC_IsUsbConnect())
		//	pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_INT_SET1, 0x00);  //disable
		else
		{
			MMP_UBYTE thg,ubRegThd;
		
			thg = ubPowerGsenOnValue;

            pthis->MMPF_Gsensor_SetDynamicRange(pthis, 2);      // 2G
			if (thg > GR(_gGsnrDevInfo.usDynamicRange))
				thg = GR(_gGsnrDevInfo.usDynamicRange);

			ubRegThd = thg*0x80/GR(_gGsnrDevInfo.usDynamicRange);
			pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_Active_TH, (MMP_UBYTE)ubRegThd);
			
			DPRINT("Set Threshold %d 0x%x\r\n", ubPowerGsenOnValue, thg);

			pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_INT_SET1, 0x07);  //enable
		}
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_Active_DURA, 0x03);
	//	pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_Active_TH, 0x1b);
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_INT_MAP1, 0x04); //enable int1
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_INT_LTACH, 0x06);
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_engineer_mode, 0x83);
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_engineer_mode, 0x69);
		pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_engineer_mode, 0xBD);
    }
}

void Gsensor_Initial_PowerOff_SC7A30E(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE ubPowerGsenOnValue)
{
	MMP_UBYTE status;

	printc("### %s - %d\r\n", __func__, ubPowerGsenOnValue);
	G_SC7A30E_open_interrupt(pthis,3);
}

void Gsensor_Initial_PowerOff(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE ubPowerGsenOnValue)
{
	if(ApicalDeviceID == GSENSOR_ID_DA312)
	{
		Gsensor_Initial_PowerOff_DA380(pthis,ubPowerGsenOnValue);
	}
	else if(ApicalDeviceID == GSENSOR_ID_SC7A30E)
	{   
		Gsensor_Initial_PowerOff_SC7A30E(pthis,ubPowerGsenOnValue);
	}
}
MMP_ERR Gsensor_IOControl(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr, MMP_UBYTE cmd, MMP_UBYTE* arg)
{
	MMP_ERR status = MMP_ERR_NONE;
	
	switch(cmd)
	{
		case GSNR_CMD_RESET: 
			status |= pthis->MMPF_Gsensor_Reset(pthis);
			status |= pthis->MMPF_Gsensor_ReadDeviceID(pthis, pgsnr_attr); 
			if (status == MMP_ERR_NONE)
			{
				// Init default setting
				pgsnr_attr->ubGroundAxis = MMP_GSENSOR_AXIS_Z;
				pthis->MMPF_Gsensor_Initialize(pthis);
				
				#if (GSENSOR_DETECT_MODE == GSNESOR_DETECT_DIFF)
				if(bGsensorCalibrated == AHC_FALSE)
				{
					pthis->MMPF_Gsensor_Calibration(pthis, 0);
					bGsensorCalibrated = AHC_TRUE;
				}
				#endif
				
				//pgsnr_attr->nInited = 1;
			}
			else
			{
				pgsnr_attr->nInited = 0;
			}
		break;

		case GSNR_CMD_CALIBRATION: 
			status = Gsensor_Calibration(pthis);
		break;
		
		case GSNR_CMD_GET_OFFSET: 
			{
				GSENSOR_DATA* offset = (GSENSOR_DATA*)arg;
				status = Gsensor_GetSensorOffset(pthis, offset);
			}
		break;
		
		case GSNR_CMD_SET_OFFSET: 
			{
				GSENSOR_DATA* offset = (GSENSOR_DATA*)arg;
				status = Gsensor_SetSensorOffset(pthis, offset);
			}
		break;
		
		case GSNR_CMD_READ_ACCEL_XYZ:
			{
				GSENSOR_DATA* acc = (GSENSOR_DATA*)arg;
				status = Gsensor_Read_XYZ(pthis, acc);
			}
		break;

		case GSNR_CMD_READ_ACCEL_WITH_COMPENSATION:
			{
				GSENSOR_DATA* acc = (GSENSOR_DATA*)arg;
				status = Gsensor_Read_XYZ_WithCompensation(pthis, acc);
			}
		break;

		case GSNR_CMD_SET_PWR_ON_INT_THD:
			{
				MMP_UBYTE thd = *((MMP_UBYTE*)arg);
				Gsensor_Initial_PowerOff(pthis, thd);
			}
		break;

		case GSNR_CMD_SET_INT_THD: 
		{
			MMP_SHORT usThd;
			MMP_UBYTE ubRegThd;
			
			usThd = *(MMP_SHORT*)arg;

			if (ABS(usThd) > (_gGsnrDevInfo.usDynamicRange*1000))
				usThd = (_gGsnrDevInfo.usDynamicRange*1000);

			switch (_gGsnrDevInfo.usDynamicRange)
			{
				case 2:
					ubRegThd = usThd/16;
					break;
				case 4:
					ubRegThd = usThd/31;
					break;
				case 8:
					ubRegThd = usThd/63;
					break;
				case 16:
					ubRegThd = usThd/125;
					break;
				default:
					return MMP_PERIPHERAL_ERR_ACCESS;
			}
			
			status |= Gsensor_WriteRegister(pthis, GSensor_Reg_INT1_THD, ubRegThd & 0x7F);
			/* duration is how long to keep the HG */
			status |= Gsensor_WriteRegister(pthis, GSensor_Reg_INT1_DURATION, (MMP_UBYTE)0x28);
			
			DPRINT("Set Threshold %d 0x%x\r\n", *(int *) arg, ubRegThd);
		}
		break;
		
		case GSNR_CMD_SET_INT_DURATION:
			status |= pthis->MMPF_Gsensor_SetIntDuration(pthis, *arg);
		break;
		
		case GSNR_CMD_GET_INT_STATUS:
			{
				MMP_UBYTE* int_status = (MMP_UBYTE*)arg;
			    status = Gsensor_GetIntStatus(pthis, int_status);
			}
		break;
		
		case GSNR_CMD_SET_POWER_SAVE:
			{
				MMP_UBYTE mode = *((MMP_UBYTE*)arg);
				status = Gsensor_SetPowerSaveMode(pthis, mode);
			}
		break;
		
		case GSNR_CMD_SET_NORMAL_MODE:
			{
				MMP_UBYTE rate = *((MMP_UBYTE*)arg);
				status = Gsensor_SetNormalModeDataRate(pthis, rate);
			}
		break;	
		
		case GSNR_CMD_SET_DATA_RATE:
			{
				MMP_UBYTE rate = *((MMP_UBYTE*)arg);
				status = Gsensor_SetNormalModeDataRate(pthis, rate);
			}
		break;

		case GSNR_CMD_SET_INT_SOURCE:
			{
				MMP_UBYTE int_src = *((MMP_UBYTE*)arg);
				status = Gsensor_SetInterruptSource(pthis, int_src);
			}
		break;
		
		case GSNR_CMD_GET_DATA_RATE:
			{
				MMP_USHORT* rate = (MMP_USHORT*)arg;
				status = Gsensor_GetDataRate(pthis, rate);
			}
		break;
		
		case GSNR_CMD_SET_DYNA_RANGE:
			{
				MMP_UBYTE dynamic_range = *((MMP_UBYTE*)arg);
				status = Gsensor_SetDynamicRange(pthis, dynamic_range);
			}
		break;
		
		case GSNR_CMD_GET_DYNA_RANGE:
			{
				MMP_UBYTE* dynamic_range = (MMP_UBYTE*)arg;
				status = Gsensor_GetDynamicRange(pthis, dynamic_range);
			}
		break;

		#if 0 //<<< Driver only support baisc read/write functions. Anyother detect function should implement in middle-ware
		case GSNR_CMD_SET_GROUND_AXIS:
			{
				MMP_UBYTE ground_axis = *((MMP_UBYTE*)arg);
				status = Gsensor_SetGroundAxis(pthis, pgsnr_attr, ground_axis);
			}
		break;		
		#endif //>>> Driver only support baisc read/write functions. Anyother detect function should implement in middle-ware
		
		#if 0 //<<< Driver only support baisc read/write functions. Anyother detect function should implement in middle-ware
		case GSNR_CMD_GROUND_AXIS_STATUS: 
		{
			
			GSENSOR_DATA	sd;
			GSNR_SBYTE		g;
			MMP_UBYTE*		ground_axis = (MMP_UBYTE*)arg;
			
			if (pgsnr_attr->ubGroundAxis == MMP_GSENSOR_AXIS_ERR) {
				*ground_axis = GSNR_POSITION_NOCHANGE;
				return MMP_ERR_NONE;
            }

			Gsensor_Read_XYZ(pthis, &sd);
			
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
						*ground_axis = kLastPosition;
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
						*ground_axis = kLastPosition;
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

			*ground_axis = GSNR_POSITION_NOCHANGE;
			return MMP_ERR_NONE;
		}
		break;
		#endif//>>> Driver only support baisc read/write functions. Anyother detect function should implement in middle-ware
		
        case GSNR_CMD_READ_ACCEL_XYZ_SHADOW:
			{
				GSENSOR_DATA* data = (GSENSOR_DATA*)arg;
            	memcpy( data, &m_GSensorShadow, sizeof(GSENSOR_DATA) );
        	}
        break;

		case GSNR_CMD_READ_ACCEL_AVG:
			{
				GSENSOR_DATA* data = (GSENSOR_DATA*)arg;
				status = Gsensor_Read_Accel_Avg(pthis, data);
			}
		break;
		
		default:
			//Command not support by this device.
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

struct _3RD_PARTY_GSENSOR Gsensor_Obj = 
{
    //0
    Gsensor_ResetDevice,
    Gsensor_ReadDeviceID,
    Gsensor_Initial,
    Gsensor_WriteRegister,
    Gsensor_ReadRegister,
    
    //5
    Gsensor_ReadOffsetFromFile,
    Gsensor_WriteOffsetToFile,
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
    printc("[DA380 and SC7A30E - Gsensor_Module_Init]\r\n");
	if(SC7A30E_Gsensor_Probe())
		ApicalDeviceID = GSENSOR_ID_SC7A30E;
	else if(DA312_Gsensor_Probe())
		ApicalDeviceID = GSENSOR_ID_DA312;
	else
		ApicalDeviceID = GSENSOR_ID_SC7A30E;
	
	printc("[APK]Gsensor_Module_Init....ApicalDeviceID=0x%08X\r\n", ApicalDeviceID);	
    MMPF_3RDParty_Gsensor_Register(&Gsensor_Obj);
    return 0;    
}

#if defined(__RTK_OS__)
#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(Gsensor_Module_Init);
#endif // #if defined(__RTK_OS__)

#endif

#endif //GSENSOR_CONNECT_ENABLE && GSENSOR_MODULE == GSENSOR_MODULE_MC3230)

