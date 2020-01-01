/*===========================================================================
 * Include file 
 *===========================================================================*/ 

#include "Config_SDK.h"
#include "config_fw.h"
#include "os_wrap.h"
#include "mmpf_pio.h"
#include "mmpf_timer.h"
#include "lib_retina.h"

//TODO: symbol "GSENSOR_MODULE_RT3000" should be defined somewhere.
#if (GSENSOR_CONNECT_ENABLE && GSENSOR_MODULE == GSENSOR_MODULE_RT3000)
#include "Gsensor_rt3000.h"
#include "mmpf_gsensor.h"
#include "GSensor_ctrl.h"
#include "AIT_Init.h"
#include "drv_bus_i2c.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/
#define GSENSOR_LOCK
#define GSENSOR_UNLOCK

#define	TO_NEGATIVE_VALUE(x)	( (~x + 0x01) | 0x0200 )
#define	TO_ABSOLUTE_VALUE(x)	( (x > 0x0200)? (0x0400 - x+1):(x) )

//#define	LOW_BOUND_1G(s)			((signed char)s->us1G - (signed char)s->ub1G_Err)
#define ABS(x) 					((x) > 0 ? (x) : -(x))

//#define	MAP2HW_G(g, s)			((g) * (s)->us1G) // Convert g to raw data

#define MG_TO_RAWDATA(g, s)			((g)*(s)) // mg to raw data
#define REALDATA_TO_RAWDATA(g)		MG_TO_RAWDATA(g, _gGsnrDevInfo.usSensitivity)
#define RAWDATA_TO_REALDATA(r)		Gsensor_RawData_To_mg((r), _gGsnrDevInfo.usSensitivity)

#define	STABLE_CNT				(0)

/* I2C attributes */
#define GSENSOR_I2C_ID			(0x19<<1)
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
static GSENSOR_DATA			m_GSensorOffset 		= {{0, 0, 0}};
static GSENSOR_DATA			m_GSensorShadow  		= {{0, 0, 0}};

#endif

static MMP_BOOL				_gbGsnrInit = MMP_FALSE;

static GSNR_DEV_INFO		_gGsnrDevInfo =
{
	GSENSOR_ID_RT3000,	// usDeviceID
	GSENSOR_DEFAULT_DYNAMIC_RANGE,	// usDynamicRange
	(1<<GSENSOR_VALID_ADC_BITS)/(GSENSOR_DEFAULT_DYNAMIC_RANGE<<1),	// usSensitivity
	200,	// usODR
};

static const I2COptions_t	_gI2CCfg = 
{
	GSENSOR_I2C_ID,				// Slave address
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
	
	i2c_err = DrvI2cOpen(&i2c_handle, &i2c_cfg);
	if (i2c_err != I2C_PROC_DONE) {
		RTNA_DBG_Str0("read err - 1\r\n");
		return MMP_PERIPHERAL_ERR_OPEN;
	}
	
	i2c_err = DrvI2cWrite(i2c_handle,(void*)&reg, 1, 0); // Set sub-address.
	if (i2c_err != I2C_PROC_DONE) {
		DrvI2cClose(i2c_handle);
		//RTNA_DBG_Str0("read err - 2\r\n");
		return MMP_PERIPHERAL_ERR_ACCESS;
	}
	
	i2c_err = DrvI2cRead(i2c_handle, (void*)pval, 1);
	if (i2c_err != I2C_PROC_DONE) {
		DrvI2cClose(i2c_handle);
		RTNA_DBG_Str0("read err - 3\r\n");
		return MMP_PERIPHERAL_ERR_ACCESS;
	}
	
	DrvI2cClose(i2c_handle);
	
	return MMP_ERR_NONE;
}

void Gsensor_DumpRegister(struct _3RD_PARTY_GSENSOR *pthis, GSNR_DEV_INFO *pgsnr_attr)
{
#if 1//(GSENSOR_DBG_MSG)

	MMP_LONG	i;
	MMP_UBYTE	rv;
	MMP_UBYTE	regs[] = {0x06,	0x0F, 0x20, 0x21, 0x22, 0x23, 
								0x24, 0x25, 0x28, 0x29, 0x2A, 
								0x2B, 0x2C, 0x2D, 0x30, 0x31,
								0x32, 0x33
							};

	DPRINT("====RT3000 Registers====\r\n");
							        
	for (i = 0; i < sizeof(regs); i++) 
	{
		pthis->MMPF_Gsensor_GetReg(pthis, regs[i], &rv);
		DPRINT("Reg: 0x%02x, 0x%02x\r\n", regs[i], rv);
	}
	
	DPRINT("PROPERTY id = 0x%x, Range = %d, Sens = %d, usODR = %d, sIntrThreshold = 0x%x , bEnableAutoCalibration = 0x%x\r\n",
	       pgsnr_attr->usDeviceID,
	       pgsnr_attr->usDynamicRange,
	       pgsnr_attr->usSensitivity,
	       pgsnr_attr->usODR,
	       pgsnr_attr->sIntrThreshold,
	       pgsnr_attr->bEnableAutoCalibration);
#endif
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
		RTNA_DBG_Str0("write err - 1\r\n");
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
	//float temp = 0;

	GSENSOR_LOCK
	
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
	
	GSENSOR_UNLOCK
		
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
		//RTNA_DBG_Str0("G-sensor calibration: ");
		//RTNA_DBG_Dec0(temp.acc_val[0]);
		//RTNA_DBG_Dec0(temp.acc_val[1]);
		//RTNA_DBG_Dec0(temp.acc_val[2]);
		//RTNA_DBG_Str0("\r\n");
		acc_avg.acc_val[0] += temp.acc_val[0];
		acc_avg.acc_val[1] += temp.acc_val[1];
		acc_avg.acc_val[2] += temp.acc_val[2];
		
		RTNA_WAIT_MS(10); // Wait for stable or wait data update???
  	}
	//RTNA_DBG_Str0("G-sensor calibration sum: ");
	//RTNA_DBG_Dec0(acc_avg.acc_val[0]);
	//RTNA_DBG_Dec0(acc_avg.acc_val[1]);
	//RTNA_DBG_Dec0(acc_avg.acc_val[2]);
	//RTNA_DBG_Str0("\r\n");
	acc_avg.acc_val[0] /= CALIBRATE_AVG_NUM;
	acc_avg.acc_val[1] /= CALIBRATE_AVG_NUM;
	acc_avg.acc_val[2] /= CALIBRATE_AVG_NUM;
	//RTNA_DBG_Str0("G-sensor calibration avg: ");
	//RTNA_DBG_Dec0(acc_avg.acc_val[0]);
	//RTNA_DBG_Dec0(acc_avg.acc_val[1]);
	//RTNA_DBG_Dec0(acc_avg.acc_val[2]);
	//RTNA_DBG_Str0("\r\n");
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
#if 0	//RT3000 does not support INT duration setup.
	pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INT1_DURATION, (arg & 0x7f));	
#endif
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
	value &= 0x0F;		//ODR = 0
	pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL1, value);
	_gGsnrDevInfo.usODR = 0;
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetNormalModeDataRate(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE rate)
{
	MMP_UBYTE value;
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_CTRL1, &value);
	value &= 0x0F;
	value |= 0x07;	//enable XYZ 3-axis
	switch (rate) {
		case 1:
			value |= 0x10;
			_gGsnrDevInfo.usODR = 1;
			break;
		case 10:
			value |= 0X20;
			_gGsnrDevInfo.usODR = 10;
			break;
		case 25:
			value |= 0x30;
			_gGsnrDevInfo.usODR = 25;
			break;
		case 50:
			value |= 0x40;
			_gGsnrDevInfo.usODR = 50;
			break;
		case 100:
			value |= 0x50;
			_gGsnrDevInfo.usODR = 100;
			break;
		case 200:
			value |= 0x60;
			_gGsnrDevInfo.usODR = 200;
			break;
		default:
			RTNA_DBG_Str0("Warning!! G-sensor not support ODR: ");
			RTNA_DBG_Dec0(rate);
			RTNA_DBG_Str0(" Switch ODR to 50Hz\r\n");
			value |= 40; // default 50 Hz
			_gGsnrDevInfo.usODR = 50;
			break;
	}
	pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL1, value);
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetInterruptSource(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE src)
{
    if (src == 0) {
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL6, 0x00); // Not mapping to INT_x
    }
    else if (src == 1)
    {
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL6, 0x40); // Mapping to INT_2
    }

	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetDataRate(struct _3RD_PARTY_GSENSOR *pthis, MMP_USHORT *wDataRate)
{
	*wDataRate = _gGsnrDevInfo.usODR;
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

#if 0 //<<< Driver only support baisc read/write functions. Anyother detect function should implement in middle-ware
MMP_ERR Gsensor_SetGroundAxis(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr, MMP_UBYTE arg)
{
	MMP_ERR status = MMP_ERR_NONE;

	pgsnr_attr->ubGroundAxis = arg;

	return status;
}
#endif

MMP_ERR Gsensor_Initial(struct _3RD_PARTY_GSENSOR *pthis)
{
	MMP_ERR		err = MMP_ERR_NONE;
	MMP_USHORT	usDevID = 0;
    MMP_UBYTE	status;

    err = pthis->MMPF_Gsensor_ReadDeviceID(pthis, &usDevID); 

	if (err != MMP_ERR_NONE) {
		return err;
	}
    
    if(usDevID == _gGsnrDevInfo.usDeviceID)
    {	
		GSENSOR_LOCK
			
        //Initial sequence listed in SP80G_fw_func_list_v0.3.pdf
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL1, 0x47);	//enable XYZ, ODR = 50hz...
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL2, 0x00);	//disable high pass filter...
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL3, 0x00); // No mapping to INT_1
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL4, 0xA8); // Set dynamic range 8G, BDU
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL5, 0x08);	// Latch INT1
        #ifdef GSENSOR_INT_LEVEL
			#if (GSENSOR_INT_LEVEL == GPIO_HIGH)
			pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL6, 0x00); // INT high active
			#else
			pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL6, 0x02); // INT low active
			#endif
        #else
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL6, 0x00); 	// INT high active
        #endif
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INT1_THD, 0x00);	// Set INT1 THD to MAX
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INT1_DURATION, 0x00); // INT1 duration
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INT1_CONFIG, 0x00);	// enable INT1 WAKEUP 

		// Set dynamic range.
		pthis->MMPF_Gsensor_SetDynamicRange(pthis, _gGsnrDevInfo.usDynamicRange);
		// Set ODR
		pthis->MMPF_Gsensor_SetNormalModeDataRate(pthis, _gGsnrDevInfo.usODR);
		
		GSENSOR_UNLOCK
			
		// Wait G-sensor stable.
		//MMPF_OS_SleepMs(200);
        pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_INT1_STATUS, &status); //Clear INT1 status
    } 
    else 
    {
        printc(FG_RED("Wrong G-Sensor ID for RT3000\r\n"));
		err = MMP_PERIPHERAL_ERR_ACCESS;
    }
    return err;
}

void Gsensor_Initial_PowerOff(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE ubPowerGsenOnValue)
{
    MMP_UBYTE	int_status;
	MMP_ERR		err = MMP_ERR_NONE;
	MMP_USHORT	usDevID = 0;
	
    //DPRINT("### %s - %d\r\n", __func__, ubPowerGsenOnValue);
	//Gsensor_DumpRegister(pthis,&_gGsnrDevInfo);
	
    err = pthis->MMPF_Gsensor_ReadDeviceID(pthis, &usDevID); 

	if (err != MMP_ERR_NONE) {
		return;
	}
    
    if(usDevID == _gGsnrDevInfo.usDeviceID)
	{	
	    pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL1, 0x67);	//ODR=200Hz
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL2, 0x09);	//HP on DATA out and AOI1

        if (0 == ubPowerGsenOnValue) {
			
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL3, 0x00);	//AOI INT1 off, 20171201
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL6, 0x00);	//AOI INT2 off
        }
        else {
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL3, 0x40);	//AOI INT1 on, 20171201
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL6, 0x40);	//AOI INT2 On
        }

        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL4, 0xA8); // Set dynamic range 8G, BDU on
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL5, 0x08);	// Latch Interrupt
        pthis->MMPF_Gsensor_SetReg(pthis, 0x06, 0x01); // AOI enable, 20171201

		#ifdef GSENSOR_INT_LEVEL
        	#if (GSENSOR_INT_LEVEL == GPIO_HIGH)
	        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL6, 0x40); // INT high active
			#else
			pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL6, 0x42); // INT low active
			#endif
        #else
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL6, 0x40); // INT high active
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
            MMPF_OS_Sleep(65);	// data stable, 20171204
			pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL1, 0x47);	//ODR=50Hz
			
			if (usThd > GR(_gGsnrDevInfo.usDynamicRange))
				usThd = GR(_gGsnrDevInfo.usDynamicRange);

			ubRegThd = usThd*0x80/GR(_gGsnrDevInfo.usDynamicRange);
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

        pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_INT1_STATUS, &int_status);	// clear INT1 status
        //MMPF_OS_Sleep(70);	// data stable, 20171201
		Gsensor_DumpRegister(pthis,&_gGsnrDevInfo);
	} 
}

MMP_ERR Gsensor_IOControl(struct _3RD_PARTY_GSENSOR *pthis, MMP_ULONG cmd, void* arg)
{
	MMP_ERR status = MMP_ERR_NONE;
	
	switch(cmd)
	{
		case GSNR_CMD_RESET:
			status = Gsensor_ResetDevice(pthis);
			status |= Gsensor_Initial(pthis);
		break;

		case GSNR_CMD_INITIALIZE:
			status = Gsensor_Initial(pthis);
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
    NULL,
    NULL,
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
    printc("[RT3000 - Gsensor_Module_Init]\r\n");
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


#endif //GSENSOR_CONNECT_ENABLE && GSENSOR_MODULE == GSENSOR_MODULE_RT3000)

