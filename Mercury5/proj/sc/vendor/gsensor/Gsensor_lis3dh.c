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
//#include "dsc_Key.h"

#if 0//#if (GSENSOR_CONNECT_ENABLE && GSENSOR_MODULE == GSENSOR_MODULE_LIS3DH)
#include "Gsensor_lis3dh.h"
#include "mmpf_gsensor.h"
#include "GSensor_ctrl.h"
#include "AIT_Init.h"
#include "drv_bus_i2c.h"


/*===========================================================================
 * Macro define
 *===========================================================================*/

#define	TO_NEGATIVE_VALUE(x)	( (~x + 0x01) | 0x0200 )
#define	TO_ABSOLUTE_VALUE(x)	( (x > 0x0200)? (0x0400 - x+1):(x) )

//#define	LOW_BOUND_1G(s)			((signed char)s->ub1G - (signed char)s->ub1G_Err)
#define ABS(x) 					((x) > 0 ? (x) : -(x))

//#define	MAP2HW_G(g, s)			((g * s->ub1G) / SCALE_G)
#define MG_TO_RAWDATA(g, s)			((g)*(s)) // mg to raw data
#define REALDATA_TO_RAWDATA(g)		MG_TO_RAWDATA(g, _gGsnrDevInfo.usSensitivity)
#define RAWDATA_TO_REALDATA(r)		Gsensor_RawData_To_mg((r), _gGsnrDevInfo.usSensitivity)


#define	STABLE_CNT				(0)

/* I2C attributes */
#define GSENSOR_I2C_ID			(0x19)
#define GSENSOR_I2C_CHANNEL		(0x00)
#define GSENSOR_I2C_PAD_MODE	(I2C_PAD_MODE_1)
#define GSENSOR_I2C_SPEED		(I2C_HIGHSPEED_MODE_400KHZ)

/**/
#define GSENSOR_VALID_ADC_BITS			(16)
#define GSENSOR_DEFAULT_DYNAMIC_RANGE	(8)


/*===========================================================================
 * Global varible
 *===========================================================================*/

#if defined(ALL_FW)
static GSENSOR_DATA			m_GSensorOffset 		= {0, 0, 0};
static GSENSOR_DATA			m_GSensorShadow  		= {0, 0, 0};

//static int					kUpCnt 					= 0;
//static int					kDwCnt 					= 0;
//static int					kLastPosition 			= GSNR_POSITION_UNKNOWN;
#endif

static GSNR_DEV_INFO		_gGsnrDevInfo =
{
	GSENSOR_ID_LIS3DH,	// usDeviceID
	GSENSOR_DEFAULT_DYNAMIC_RANGE,	// usDynamicRange
	(1<<GSENSOR_VALID_ADC_BITS)/(GSENSOR_DEFAULT_DYNAMIC_RANGE<<1),	// usSensitivity
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
 *===========================================================================*/\
#ifdef ALL_FW

MMP_ERR Gsensor_ReadRegister(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE reg , MMP_UBYTE* pval)
{
	s32				i2c_handle = 0;
	I2COptions_t	i2c_cfg;
	I2CErrorCode_e	i2c_err = I2C_PROC_DONE;
	
	memcpy(&i2c_cfg, &_gI2CCfg, sizeof(I2COptions_t));
	
	i2c_err = DrvI2cOpen(&i2c_handle,&i2c_cfg);
	if (i2c_err != I2C_PROC_DONE) {
		return MMP_PERIPHERAL_ERR_OPEN;
	}
	
	i2c_err = DrvI2cWrite(i2c_handle,(void*)&reg, 1, 0); // Set sub-address.
	if (i2c_err != I2C_PROC_DONE) {
		DrvI2cClose(i2c_handle);
		return MMP_PERIPHERAL_ERR_ACCESS;
	}
	
	i2c_err = DrvI2cRead(i2c_handle, (void*)pval, 1);
	if (i2c_err != I2C_PROC_DONE) {
		DrvI2cClose(i2c_handle);
		return MMP_PERIPHERAL_ERR_ACCESS;
	}
	
	DrvI2cClose(i2c_handle);
	
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_WriteRegister(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE reg , MMP_UBYTE val)
{
	s32				i2c_handle = 0;
	u8				i2c_data[2];
	I2COptions_t	i2c_cfg;
	I2CErrorCode_e	i2c_err = I2C_PROC_DONE;
	
	memcpy(&i2c_cfg, &_gI2CCfg, sizeof(I2COptions_t));
	
	i2c_err = DrvI2cOpen(&i2c_handle,&i2c_cfg);
	if (i2c_err != I2C_PROC_DONE) {
		return MMP_PERIPHERAL_ERR_OPEN;
	}
	
	i2c_data[0] = reg; // Sub-address.
	i2c_data[1] = val;
	
	i2c_err = DrvI2cWrite(i2c_handle, (void*)i2c_data, 2, 0);
	if (i2c_err != I2C_PROC_DONE) {
		DrvI2cClose(i2c_handle);
		return MMP_PERIPHERAL_ERR_ACCESS;
	}
	
	DrvI2cClose(i2c_handle);
	
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_ResetDevice(struct _3RD_PARTY_GSENSOR *pthis) 
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_ReadDeviceID(struct _3RD_PARTY_GSENSOR *pthis, MMP_USHORT *pusDevID)
{
	MMP_ERR 	err 		= MMP_ERR_NONE;
	MMP_UBYTE	ubDevID 	= 0;
	
	err = pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_GetID, &ubDevID);

	if (err != MMP_ERR_NONE) {
		*pusDevID = 0x0000;
	}
	else {
		*pusDevID = ubDevID;
	}
	return err;
}

MMP_ERR	Gsensor_GetSensorOffset(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *offset)
{
	offset->acc_val[0] = m_GSensorOffset.acc_val[0];
	offset->acc_val[1] = m_GSensorOffset.acc_val[1];
	offset->acc_val[2] = m_GSensorOffset.acc_val[2];
	
	return MMP_ERR_NONE;
}

MMP_ERR	Gsensor_SetSensorOffset(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *offset)
{
	m_GSensorOffset.acc_val[0] = offset->acc_val[0];
	m_GSensorOffset.acc_val[1] = offset->acc_val[1];
	m_GSensorOffset.acc_val[2] = offset->acc_val[2];
	
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
	MMP_USHORT usRawData = 0;
	
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_XOUT_LSB, (MMP_UBYTE*)&usRawData);
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_XOUT_MSB, ((MMP_UBYTE*)&usRawData)+1);
	data->acc_val[0] = RAWDATA_TO_REALDATA(usRawData);	

	usRawData = 0;
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_YOUT_LSB, (MMP_UBYTE*)&usRawData);
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_YOUT_MSB, ((MMP_UBYTE*)&usRawData)+1);
	data->acc_val[1] = RAWDATA_TO_REALDATA(usRawData);

	usRawData = 0;
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_ZOUT_LSB, (MMP_UBYTE*)&usRawData);
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_ZOUT_MSB, ((MMP_UBYTE*)&usRawData)+1);
	data->acc_val[2] = RAWDATA_TO_REALDATA(usRawData);

	#if 0
	#ifdef GSENSOR_ROTATE
	temp = data->acc_val[0];
	data->acc_val[0] = data->acc_val[2];
	data->acc_val[1] *= -1;
	data->acc_val[2] = -1 * temp;
	#else
	temp = data->acc_val[0];
	data->acc_val[0] = -1 * data->acc_val[2];
	data->acc_val[1] *= -1;
	data->acc_val[2] = temp;
	#endif
	#endif
    memcpy( &m_GSensorShadow, data, sizeof(GSENSOR_DATA) );
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_Read_XYZ_WithCompensation(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *data)
{	
	GSENSOR_DATA temp_acc = {{0, 0, 0}};
		
	pthis->MMPF_Gsensor_Read_XYZ(pthis, &temp_acc);
		
	temp_acc.acc_val[0] -= m_GSensorOffset.acc_val[0];
	temp_acc.acc_val[1] -= m_GSensorOffset.acc_val[1];
	temp_acc.acc_val[2] -= m_GSensorOffset.acc_val[2];
		
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
	pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INT1_DURATION, (arg & 0x7f));	
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetIntStatus(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE* pstatus)
{
	MMP_UBYTE   ubStatus= 0;
	MMP_UBYTE   ubEn    = 0;

	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_INT1_CONFIG, &ubEn);
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_INT1_STATUS, &ubStatus);
	ubEn &= 0x3F;
	*pstatus = (ubStatus & ubEn);

	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetPowerSaveMode(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE mode)
{	
	MMP_UBYTE value;
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_CTRL1, &value);
	value &= 0x0F;
	pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL1, value);
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetNormalModeDataRate(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE rate)
{
	MMP_UBYTE value;
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_CTRL1, &value);
	value &= 0x9F;
	pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL1, value);
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetInterruptSource(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE src)
{
    if (src == 0) {
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL3, 0x00); // Not mapping to INT_x
    }
    else if (src == 1)
    {
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL3, 0x40); // Mapping to INT_1
    }

	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetDataRate(struct _3RD_PARTY_GSENSOR *pthis, MMP_USHORT *wDataRate)
{
	MMP_UBYTE ubValue1,ubValue2 ;
	MMP_UBYTE ubOpmode;

	pthis->MMPF_Gsensor_GetReg(pthis,GSensor_Reg_CTRL1,&ubValue1);
	
	ubOpmode = (ubValue1 & 0xF0);
	switch (ubOpmode)
	{
		case DATA_RATE_POWER_DOWN:
			*wDataRate = 0;
		break;
		case DATA_RATE_1HZ:
			*wDataRate = 1;
		break;
		case DATA_RATE_10HZ:
			*wDataRate = 10;
		break;
		case DATA_RATE_25HZ:
			*wDataRate = 25;
		break;
		case DATA_RATE_50HZ:
			*wDataRate = 50;
		break;
		case DATA_RATE_100HZ:
			*wDataRate = 100;
		break;
		case DATA_RATE_200HZ:
			*wDataRate = 200;
		break;
		case DATA_RATE_400HZ:
			*wDataRate = 400;
		break;
		case DATA_RATE_L_1_5KHZ:
			*wDataRate = 1500;
		break;
		case DATA_RATE_N_1_25_L_5KHZ:
			pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_CTRL1, &ubValue1);
			pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_CTRL4, &ubValue2);	    
		    if(ubValue1 & 0x08)
		    {
		    	if(!(ubValue2 & 0x08))
		    	{
		    		//low power mode
		    		*wDataRate = 5000;
		    	}
		    }else
		    {
		    	if(ubValue2 & 0x08)
		    	{
		    		//Normal mode
		    		*wDataRate = 1500;
		    	}
		    }
		break;
		
	}
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetDynamicRange(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE ubDrange)
{
	MMP_UBYTE ubRegVal;

	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_CTRL4, &ubRegVal);
	
	ubRegVal &= ~DYNAMIC_RANGE_MASK;
	
	switch(ubDrange)
	{
		case 2:
			ubRegVal |= DYNAMIC_RANGE_2;
		break;
		case 4:
			ubRegVal |= DYNAMIC_RANGE_4;
		break;
		case 8:
			ubRegVal |= DYNAMIC_RANGE_8;
		break;
		case 16:
			ubRegVal |= DYNAMIC_RANGE_16;
		break;
		
		default:
			return MMP_PERIPHERAL_ERR_ACCESS;
	}
	
	pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL4, ubRegVal);

	// Critical section
	// Update device info.
	_gGsnrDevInfo.usDynamicRange = ubDrange;
	_gGsnrDevInfo.usSensitivity = (1<<GSENSOR_VALID_ADC_BITS)/(ubDrange<<1);
	// Critical section
	
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetDynamicRange(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE *ubDrange)
{
	*ubDrange = (MMP_UBYTE)_gGsnrDevInfo.usDynamicRange;
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_Initial(struct _3RD_PARTY_GSENSOR *pthis)
{
	MMP_ERR err = MMP_ERR_NONE;
    MMP_UBYTE status;
	MMP_USHORT usDevID;
	
    pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_INT1_STATUS, &status);
    pthis->MMPF_Gsensor_ReadDeviceID(pthis, &usDevID); 
    
    if(usDevID == _gGsnrDevInfo.usDeviceID)
    {	
        //Initial sequence listed in SP80G_fw_func_list_v0.3.pdf
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL1, 0x97);
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL2, 0x00);
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL3, 0x00); // No mapping to INT_x
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL4, 0xA8); // Set dynamic range 8G
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL5, 0x08);
        #if defined(GSENSOR_INT_LEVEL)&&(GSENSOR_INT_LEVEL == GPIO_LOW)
		printc(FG_RED("set G-Sensor LIS3DH int low active\r\n"));
		pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL6, 0x02); // INT low active
        #else
		pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL6, 0x00); // INT high active
        #endif
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INT1_THD, 0x7F);
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INT1_DURATION, 0x03);
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INT1_CONFIG, 0x95);

		// Set dynamic range.
        pthis->MMPF_Gsensor_SetDynamicRange(pthis, GSENSOR_DEFAULT_DYNAMIC_RANGE);

        pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_INT1_STATUS, &status);
    } 
    else 
    {
        printc(FG_RED("Wrong G-Sensor ID for LIS3DH\r\n"));
		err = MMP_PERIPHERAL_ERR_ACCESS;
    }
    return err;
}

void Gsensor_Initial_PowerOff(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE ubPowerGsenOnValue)
{
    MMP_UBYTE status;
	MMP_USHORT usDevID;
	
    DPRINT("### %s - %d\r\n", __func__, ubPowerGsenOnValue);

	pthis->MMPF_Gsensor_ReadDeviceID(pthis, &usDevID); 
    
    if(usDevID == _gGsnrDevInfo.usDeviceID)
	{	
	    pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL1, 0xA7);
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL2, 0x09);

        if (0 == ubPowerGsenOnValue) {
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL3, 0x00);
        }
        else {
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL3, 0x40);
        }

        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL4, 0x00); // Set dynamic range 2G
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL5, 0x08);
		
        #if defined(GSENSOR_INT_LEVEL)&&(GSENSOR_INT_LEVEL == GPIO_LOW)
		printc(FG_RED("set G-Sensor LIS3DH int low active\r\n"));
		pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL6, 0x02); // INT low active
        #else
		pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL6, 0x00); // INT high active
        #endif

        if (0 == ubPowerGsenOnValue) {
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INT1_THD, 0x7F);  // OFF
        }
        else
		{
			MMP_USHORT usThd;
			MMP_UBYTE ubRegThd;
			
			usThd = ubPowerGsenOnValue;

            pthis->MMPF_Gsensor_SetDynamicRange(pthis, 2);      // 2G

			if (usThd > _gGsnrDevInfo.usDynamicRange)
				usThd = _gGsnrDevInfo.usDynamicRange;
			
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
					return;
			}
			
			pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INT1_THD, ubRegThd);
			//pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INT1_DURATION, (MMP_UBYTE)0x28);
			
			DPRINT("Set Threshold %d 0x%x\r\n", ubPowerGsenOnValue, ubRegThd);
        }

        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INT1_DURATION, 0x00);

        if (0 == ubPowerGsenOnValue) {
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INT1_CONFIG, 0x00);   // INT off
        }
        else {
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INT1_CONFIG, 0x2A);   // INT on
        }
        
        pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_INT1_STATUS, &status);
	} 
}

MMP_ERR Gsensor_IOControl(struct _3RD_PARTY_GSENSOR *pthis, MMP_ULONG cmd, void* arg)
{
	MMP_ERR status = MMP_ERR_NONE;
	
	switch(cmd)
	{
		case GSNR_CMD_RESET:
			status = pthis->MMPF_Gsensor_Initialize(pthis);
		break;

		case GSNR_CMD_CALIBRATION: 
			status = pthis->MMPF_Gsensor_Calibration(pthis);
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
			MMP_USHORT usThd;
			MMP_UBYTE ubRegThd;
			
			usThd = *(MMP_SHORT*)arg;

			if (usThd > _gGsnrDevInfo.usDynamicRange)
				usThd = _gGsnrDevInfo.usDynamicRange;

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
			
			status |= Gsensor_WriteRegister(pthis, GSensor_Reg_INT1_THD, ubRegThd & INT_THD_MASK);
			/* duration is how long to keep the HG */
			status |= Gsensor_WriteRegister(pthis, GSensor_Reg_INT1_DURATION, (MMP_UBYTE)0x28);
			
			DPRINT("Set Threshold %d 0x%x\r\n", *(int *) arg, thg);
		}
		break;
		
		case GSNR_CMD_SET_INT_DURATION:
			{
				MMP_UBYTE ubIntDuration = *((MMP_UBYTE*)arg);
				status = pthis->MMPF_Gsensor_SetIntDuration(pthis, ubIntDuration);
			}
		break;
		
		case GSNR_CMD_GET_INT_STATUS:
			{
				MMP_UBYTE* int_status = (MMP_UBYTE*)arg;
			    status = Gsensor_GetIntStatus(pthis, int_status);
			}
		break;
		
		case GSNR_CMD_SET_POWER_SAVE:
			{
				MMP_UBYTE ubMode = *((MMP_UBYTE*)arg);
				status = pthis->MMPF_Gsensor_SetPowerSaveMode(pthis, ubMode);
			}
		break;
		
		case GSNR_CMD_SET_NORMAL_MODE:
			{
				MMP_UBYTE ubMode = *((MMP_UBYTE*)arg);
				status = pthis->MMPF_Gsensor_SetNormalModeDataRate(pthis, ubMode);
			}
		break;
		
		case GSNR_CMD_SET_DATA_RATE:
			{
				MMP_UBYTE ubRate = *((MMP_UBYTE*)arg);
				status = pthis->MMPF_Gsensor_SetNormalModeDataRate(pthis, ubRate);
			}
		break;

		case GSNR_CMD_SET_INT_SOURCE:
			{
				MMP_UBYTE ubIntSrc = *((MMP_UBYTE*)arg);
				status = pthis->MMPF_Gsensor_SetInterruptSource(pthis, ubIntSrc);
			}
		break;
		
		case GSNR_CMD_GET_DATA_RATE:
			{
				MMP_USHORT* usRate = (MMP_USHORT*)arg;
				status = pthis->MMPF_Gsensor_GetDataRate(pthis, usRate);
			}
		break;
		
		case GSNR_CMD_SET_DYNA_RANGE:
			{
				MMP_UBYTE ubRange = *((MMP_UBYTE*)arg);
				status = pthis->MMPF_Gsensor_SetDynamicRange(pthis, ubRange);
			}
		break;
		
		case GSNR_CMD_GET_DYNA_RANGE:
			{
				MMP_UBYTE* ubRange = (MMP_UBYTE*)arg;
				status = pthis->MMPF_Gsensor_GetDynamicRange(pthis, ubRange);
			}
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
    Gsensor_Attached
};

int Gsensor_Module_Init(void)
{
    printc("[LIS3DH - Gsensor_Module_Init]\r\n");
    MMPF_3RDParty_Gsensor_Register(&Gsensor_Obj);
    return 0;    
}

#if defined(__RTK_OS__)
#if defined(__GNUC__)
__section__(initcall6)
#endif
ait_module_init(Gsensor_Module_Init);
#endif // #if defined(__RTK_OS__)


#endif		// ALL_FW

#ifdef MBOOT_FW
MMP_BOOL Gsensor_GetIntStatusForBoot(void)
{
	MMP_USHORT	value	= 0;
	MMP_USHORT	usEn	= 0;

	MMPF_I2cm_ReadReg(&m_I2cmAttr_gsensor, GSensor_Reg_INT1_CONFIG, (MMP_USHORT*)&usEn);
	MMPF_I2cm_ReadReg(&m_I2cmAttr_gsensor, GSensor_Reg_INT1_STATUS, (MMP_USHORT*)&value);
    value &= usEn & 0x3F;
    
    if (value) {
        RTNA_DBG_PrintLong(0, value);
        return MMP_TRUE;
    }

    return MMP_FALSE;
}
#endif

#endif //GSENSOR_CONNECT_ENABLE && GSENSOR_MODULE == GSENSOR_MODULE_LIS3DH)

