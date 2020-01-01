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
#if defined(__GNUC__)
#include "vm_types.ht"
#endif
#if (GSENSOR_CONNECT_ENABLE && GSENSOR_MODULE == GSENSOR_MODULE_GMA301)
#include "Gsensor_gma301.h"
#include "AIT_Init.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define	TO_NEGATIVE_VALUE(x)	( (~x + 0x01) | 0x80 )
#define	TO_ABSOLUTE_VALUE(x)	( (x > 0x80)? (0x100 - x):(x) )

#define	LOW_BOUND_1G(s)			((signed char)s->ub1G - (signed char)s->ub1G_Err)
#define ABS(x) 					((x) > 0 ? (x) : -(x))

#define	MAP2HW_G(g, s)			((g * s->ub1G) / SCALE_G)

#define	STABLE_CNT				(0)

#define MOVING_STEP             3
#define SENSOR_DATA_SIZE 		3 

/*===========================================================================
 * Global varible
 *===========================================================================*/

static GSENSOR_DATA			m_GSensorOffset 		= {0, 0, 0};
static GSENSOR_DATA			m_GSensorShadow  		= {0, 0, 0};
static MMP_BOOL	 			bGsensorCalibrated   	= MMP_FALSE;

static int					kUpCnt 					= 0;
static int					kDwCnt 					= 0;
static int					kLastPosition 			= GSNR_POSITION_UNKNOWN;

MMP_BOOL	 				bGsensorinitialized 	= MMP_FALSE;

// I2cm Attribute
static MMP_I2CM_ATTR m_I2cmAttr_gsensor = {
	MMP_I2CM_GPIO,
    GSENSOR_SLAVE_ADDR << 1,
    8,
    8,
    0x02,
    MMP_FALSE,
    MMP_FALSE,
    MMP_FALSE,
    MMP_FALSE,
    0,
    0,
    1,
    50000,
    MMP_TRUE,
    GSENSOR_SCL,
    GSENSOR_SDA,
    MMP_FALSE,
    MMP_FALSE,
	MMP_FALSE,
	0
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
MMP_ERR Gsensor_Config_I2CM(struct _3RD_PARTY_GSENSOR *pthis, GSNR_I2CM_ATTRIBUTE *psI2cmattr)
{
	m_I2cmAttr_gsensor.i2cmID 		= psI2cmattr->i2cmID;
	m_I2cmAttr_gsensor.ubPadNum 	= psI2cmattr->ubPadNum;
	m_I2cmAttr_gsensor.ulI2cmSpeed  = psI2cmattr->ulI2cmSpeed;

    return MMP_ERR_NONE;
}

MMP_ERR Gsensor_ReadRegister(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE reg , MMP_UBYTE* pval)
{
	MMP_USHORT data;

	if (reg >= GSensor_Reg_INVALID)
	{
		RTNA_DBG_Str(0, FG_RED("GMA301: GsnrRead-->Wrong Register Address\r\n"));
		return MMP_ERR_NONE;
	}
    
	MMPF_I2cm_ReadReg(&m_I2cmAttr_gsensor, (MMP_USHORT)reg, (MMP_USHORT*)&data);
	
	*pval = (MMP_UBYTE)(data & 0x00FF);
	
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_WriteRegister(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE reg , MMP_UBYTE val)
{
	if (reg >= GSensor_Reg_INVALID)
	{
		RTNA_DBG_Str(0, FG_RED("GMA301: GsnrWrite-->Wrong Register Address\r\n"));
		return MMP_ERR_NONE;
	}
	
	MMPF_I2cm_WriteReg(&m_I2cmAttr_gsensor, (MMP_USHORT)reg, (MMP_USHORT)val);
	
	return MMP_ERR_NONE;
}

void Gsensor_DumpRegister(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr)
{

}

MMP_ERR Gsensor_ReadOffsetFromFile(struct _3RD_PARTY_GSENSOR *pthis)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_WriteOffsetToFile(struct _3RD_PARTY_GSENSOR *pthis)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_ResetDevice(struct _3RD_PARTY_GSENSOR *pthis) 
{
	MMP_ERR 	status 	= MMP_ERR_NONE;
	MMP_UBYTE 	value 	= 0x52;

    DPRINT(FG_GREEN("GMA301 Gsensor_ResetDevice -\r\n"));
	
	status |= pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_PD, value);
	
	bGsensorinitialized = (status == MMP_ERR_NONE)?(MMP_TRUE):(MMP_FALSE);

	return status; 
}

MMP_ERR Gsensor_ReadDeviceID(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr)
{
	MMP_ERR 	status 		= MMP_ERR_NONE;
	MMP_UBYTE	usdeviceID 	= 0;
	
	status |= pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_STADR, &usdeviceID);
	
	if (usdeviceID != GSENSOR_ID_GMA301)
	{
		status = 1;	// ERROR
		printc(FG_RED("GMA301 Gsensor Read Device ID 0x%x  %d Error\r\n"),usdeviceID, status);
		pgsnr_attr->ubGsensorID = 0xFF;
	}
	else
	{
		status = 0;	// SUCCESS
		printc(FG_GREEN("GMA301 Gsensor Read Device ID 0x%x %d Success\r\n"),usdeviceID, status);
		pgsnr_attr->ubGsensorID = (MMP_UBYTE)usdeviceID;
	}
	
	return status; 
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

MMP_ERR Gsensor_Read_XYZ(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *data) 
{
    static INT32	bufferave[SENSOR_DATA_SIZE][MOVING_STEP] = {0};	// 16 buffer
    static UINT8    pointer = 0;
    static INT32	avg[SENSOR_DATA_SIZE] = {0};    // moving average result
    INT32 sum[SENSOR_DATA_SIZE] = {0};	            //  sum of moving_step 

	MMP_UBYTE Regdata = 0;
    MMP_UBYTE g_X_Data_L=0,g_X_Data_H=0,g_Y_Data_L=0,g_Y_Data_H=0,g_Z_Data_L=0,g_Z_Data_H=0;
	INT32 GsXData=0,  GsYData=0, GsZData=0;
	int i,j;
	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x12, (MMP_UBYTE *)&Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x13, (MMP_UBYTE *)&Regdata);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x14, (MMP_UBYTE*)&g_X_Data_L);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x16, (MMP_UBYTE*)&g_Y_Data_L);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x18, (MMP_UBYTE*)&g_Z_Data_L);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x15, (MMP_UBYTE*)&g_X_Data_H);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x17, (MMP_UBYTE*)&g_Y_Data_H);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x19, (MMP_UBYTE*)&g_Z_Data_H);

	if((g_X_Data_H&0x03)>=0x02)
		GsXData =-(512 - ((g_X_Data_L +((g_X_Data_H&0x01)<<8))));
	else
		GsXData =(g_X_Data_L +((g_X_Data_H&0x01)<<8));

    if((g_Y_Data_H&0x3)>=0x02)
		GsYData =-(521 - (g_Y_Data_L +((g_Y_Data_H&0x01)<<8))) ;
	else
		GsYData =(g_Y_Data_L +((g_Y_Data_H&0x01)<<8));

      if((g_Z_Data_H&0x3)>=0x02)
		GsZData =-(512 - (g_Z_Data_L +((g_Z_Data_H&0x01)<<8)));
	else
		GsZData =(g_Z_Data_L +((g_Z_Data_H&0x01)<<8));

    /* for Simple Moving Average */
	pointer++;
	pointer %= MOVING_STEP;

	bufferave[0][pointer] = GsXData;
	bufferave[1][pointer] = GsYData;
	bufferave[2][pointer] = GsZData;

    for (i = 0; i < SENSOR_DATA_SIZE; ++i) {
		for(j = 0; j < MOVING_STEP; ++j) {
			sum[i] += bufferave[i][j];
		}

		avg[i] = sum[i] / MOVING_STEP;
	}

	data->acc_val[0] = ABS(GsXData - avg[0]);
	data->acc_val[1] = ABS(GsYData - avg[1]);
	data->acc_val[2] = ABS(GsZData - avg[2]);

    //DPRINT("Gs Data = %d, %d, %d\r\n", GsXData, GsYData, GsZData);
    //DPRINT("avg = %d, %d, %d\r\n", avg[0], avg[1], avg[2]);
    //DPRINT("data->acc_val = %d, %d, %d\r\n\n", data->acc_val[0], data->acc_val[1], data->acc_val[2]);

    memcpy( &m_GSensorShadow, data, sizeof(GSENSOR_DATA) );
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_Read_XYZ_WithCompensation(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *sd) 
{
	pthis->MMPF_Gsensor_Read_XYZ(pthis, sd);
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_Read_Accel_Avg(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *data)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_CalculateOffset(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE gAxis, GSENSOR_DATA avg)
{
	return MMP_ERR_NONE;
}

MMP_ERR	Gsensor_Calibration(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE side)
{
	GSENSOR_DATA avg;
	
	pthis->MMPF_Gsensor_Read_Accel_Avg(pthis, &avg);
	
	pthis->MMPF_Gsensor_CalculateOffset(pthis, side, avg); 
	
	return MMP_ERR_NONE;
}

MMP_ERR	Gsensor_SetIntDuration(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE arg)
{
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetIntStatus(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE* pstatus)
{
	MMP_UBYTE	value	= 0;

	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_STAINT, &value);
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_STAINT + 1, &value);
	
	*pstatus = (value & 0x3c);

	//DPRINT(FG_GREEN("Current Interrupt Status 0x%x\r\n"),*pstatus);

	//if(*pstatus)
	{
		MMP_UBYTE ucLoop = 0;
		MMP_UBYTE ucReadData = 0;

		//pthis->MMPF_Gsensor_Initialize(pthis, pgsnr_attr);//2014_1229 added.
		//pthis->MMPF_Gsensor_SetReg(pthis, 0x0E, 0x00);

		for(ucLoop = 0; ucLoop < 3; ucLoop++)
		{
			pthis->MMPF_Gsensor_GetReg(pthis, 0x1C,	&ucReadData);
			pthis->MMPF_Gsensor_GetReg(pthis, 0x1D,	&ucReadData);
		}
		
		//RTNA_WAIT_MS(200);
		//pthis->MMPF_Gsensor_SetReg(pthis, 0x0E, 0x1C);	//0x10 // by yoko
		//pthis->MMPF_Gsensor_GetReg(pthis, 0x0E,	&ucReadData);
		//DPRINT("Current 0x0E 0x%x\r\n",ucReadData);
	}

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

MMP_ERR Gsensor_SetDynamicRange(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr, MMP_UBYTE ubDrange)
{
	MMP_UBYTE ubFullSacleRange;

	ubFullSacleRange &= 0xFF;
	ubFullSacleRange |= DYNAMIC_RANGE_8;
	
 	pgsnr_attr->nMaxG	    = MAX_6G;
 	pgsnr_attr->ub1G        = 64;
 	pgsnr_attr->ub1G_Err    = 0x02;

	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetDynamicRange(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr, MMP_UBYTE *ubDrange)
{
	*ubDrange = 6;
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_EnableIntXYZ(int ex, int ey, int ez)
{
	MMP_ERR 	status 	= MMP_ERR_NONE;

    ex &= 0x01;
    ey &= 0x01;
    ez &= 0x01;
    
    if (ex | ey | ez) {
        MMPF_I2cm_WriteReg(&m_I2cmAttr_gsensor, 0x0E, 	(ex << 4) | (ey << 3) | (ez << 2));		// Enable X/Y/Z interrupt.
    	RTNA_WAIT_MS(100);
    }
    else
    {
    	MMPF_I2cm_WriteReg(&m_I2cmAttr_gsensor, 0x0E, 0x00);  // Disable interrupt
    }
    
	return status;
}

MMP_ERR Gsensor_SetGroundAxis(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr, MMP_UBYTE arg)
{
	MMP_ERR status = MMP_ERR_NONE;

	return status;
}

MMP_ERR Gsensor_Initial(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr)
{	
	MMP_UBYTE ucReadData = 0; 

    // From spec
	pthis->MMPF_Gsensor_SetReg(pthis, 0x21,		0x52);

	pthis->MMPF_Gsensor_SetReg(pthis, 0x00, 	0x02);  // Armed
	pthis->MMPF_Gsensor_SetReg(pthis, 0x00, 	0x12);  // Load OPT
	pthis->MMPF_Gsensor_SetReg(pthis, 0x00, 	0x02);  // Armed
	pthis->MMPF_Gsensor_SetReg(pthis, 0x00, 	0x82);  // Reset Data Path
	pthis->MMPF_Gsensor_SetReg(pthis, 0x00, 	0x02);  // Armed

	pthis->MMPF_Gsensor_SetReg(pthis, 0x0C, 	0x8F);  // Enable X/Y/Z/T
	pthis->MMPF_Gsensor_SetReg(pthis, 0x00,		0x06);  // Active
	RTNA_WAIT_MS(15);

	//interrupt setup
	//pthis->MMPF_Gsensor_SetReg(pthis, 0x11, 	0x05);  // INT push-pull, INT low, AUTOT=1, RTEN=0 
	pthis->MMPF_Gsensor_SetReg(pthis, 0x11, 	0x04);  // INT open-drain, INT low, AUTOT=1, RTEN=0 

	pthis->MMPF_Gsensor_SetReg(pthis, 0x38, 	0xff);  // Shake threshold
    //micro motion threshold
	pthis->MMPF_Gsensor_SetReg(pthis, 0x39, 	0x10);  // Micro motion threshold
    
    #if 1	// add by yoko	
	pthis->MMPF_Gsensor_SetReg(pthis, 0x0F, 	0x00);  // No filter
	pthis->MMPF_Gsensor_SetReg(pthis, 0x0E, 	0x00);  // Disable interrupt
	pthis->MMPF_Gsensor_SetReg(pthis, 0x1F, 	0x28);  // Select Calibrated data, Enable OSC calibration
    #endif

    // For AUTOT is 0     
	pthis->MMPF_Gsensor_GetReg(pthis, 0x12, 	&ucReadData);	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x13, 	&ucReadData);	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x14, 	&ucReadData);	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x15, 	&ucReadData);	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x16, 	&ucReadData);	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x17, 	&ucReadData);	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x18, 	&ucReadData);	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x19, 	&ucReadData);
	
	pthis->MMPF_Gsensor_SetReg(pthis, 0x1F, 	0x38);  // Select decimation filter, Enable OSC calibration  
	RTNA_WAIT_MS(2);

	//pthis->MMPF_Gsensor_SetReg(pthis, 0x0D, 	0x24);		//old is 1c
	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x1C,	    &ucReadData);	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x1D,	    &ucReadData);
	pthis->MMPF_Gsensor_SetReg(pthis, 0x0E, 	0x00);		//old is 1c

    pthis->MMPF_Gsensor_SetDynamicRange(pthis, pgsnr_attr, pgsnr_attr->ubRange);
    pgsnr_attr->nInited = 1;

	DPRINT("GMA301C Gsensor init finish\r\n");

	return MMP_ERR_NONE;
}

void Gsensor_Initial_PowerOff(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr, MMP_UBYTE ubPowerGsenOnValue)
{
    MMP_UBYTE ucReadData = 0; 

    DPRINT(FG_GREEN("### %s - TH = %d\r\n"), __func__, ubPowerGsenOnValue);

    //Gsensor_Initial(pthis, pgsnr_attr);
	pthis->MMPF_Gsensor_SetReg(pthis, 0x11, 	0x04);  // 
	pthis->MMPF_Gsensor_SetReg(pthis, 0x38, 	0xFF);  // Shak TH

    if (0 == ubPowerGsenOnValue) {
    	pthis->MMPF_Gsensor_SetReg(pthis, 0x39, 	0xFF);
    }
    else
	{
		int		thg;
        			
		thg = ubPowerGsenOnValue;

        pthis->MMPF_Gsensor_SetDynamicRange(pthis, pgsnr_attr, 6);      // 2G

		if ((unsigned int)thg > (unsigned int)pgsnr_attr->nMaxG)
			thg = pgsnr_attr->nMaxG;
		
		DPRINT("Max G is %d\r\n", pgsnr_attr->nMaxG);
		// INT TH is (64/4)LSB/G
		thg 	= MAP2HW_G(thg, pgsnr_attr) / 4;
    	pthis->MMPF_Gsensor_SetReg(pthis, 0x39, 	thg);  // Micro Motion
	    //pthis->MMPF_Gsensor_SetReg(pthis, 0x39, 	0x10);  // Test only for 1G
		
		DPRINT("Set Threshold %d 0x%x\r\n", ubPowerGsenOnValue, thg);
    }

	pthis->MMPF_Gsensor_SetReg(pthis, 0x0E, 	0x00);  // Disable interrupt
	pthis->MMPF_Gsensor_SetReg(pthis, 0x0F, 	0x00);
	pthis->MMPF_Gsensor_SetReg(pthis, 0x1F, 	0x28);  // Select Calibrated data, Enable OSC calibration
	pthis->MMPF_Gsensor_GetReg(pthis, 0x12, 	&ucReadData);	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x13, 	&ucReadData);	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x14, 	&ucReadData);	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x15, 	&ucReadData);	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x16, 	&ucReadData);	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x17, 	&ucReadData);	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x18, 	&ucReadData);	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x19, 	&ucReadData);
	
	pthis->MMPF_Gsensor_SetReg(pthis, 0x1F, 	0x38);  // Select decimation filter, Enable OSC calibration  
	RTNA_WAIT_MS(2);
	pthis->MMPF_Gsensor_GetReg(pthis, 0x1C,	    &ucReadData);	
	pthis->MMPF_Gsensor_GetReg(pthis, 0x1D,	    &ucReadData);

    if (0 == ubPowerGsenOnValue) {
	    pthis->MMPF_Gsensor_SetReg(pthis, 0x0E, 	0x00);		// Disable X, Y, and Z interrupt.
    }
    else {
    	pthis->MMPF_Gsensor_SetReg(pthis, 0x0E, 	0x1C);		// Enable X, Y, and Z interrupt.
    }

	pthis->MMPF_Gsensor_GetReg(pthis, 0x0E, 	&ucReadData);
	DPRINT(FG_GREEN("GMA301C Gsensor interrupt setup finish - 0x%X\r\n"), ucReadData);
	RTNA_WAIT_MS(100);
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
				pthis->MMPF_Gsensor_Initialize(pthis, pgsnr_attr);
				
				#if (GSENSOR_DETECT_MODE == GSNESOR_DETECT_DIFF)
				if(bGsensorCalibrated == AHC_FALSE)
				{
					pthis->MMPF_Gsensor_Calibration(pthis, 0);
					bGsensorCalibrated = AHC_TRUE;
				}
				#endif
			}
			else
			{
				pgsnr_attr->nInited = 0;
			}
		break;

		case GSNR_CMD_CALIBRATION: 
			status |= pthis->MMPF_Gsensor_Calibration(pthis, *arg);
		break;
		
		case GSNR_CMD_GET_OFFSET: 
			status |= pthis->MMPF_Gsensor_ReadOffsetFromFile(pthis);
			//status |= pthis->MMPF_Gsensor_GetSensorOffset(arg);
		break;
		
		case GSNR_CMD_SET_OFFSET: 
			status |= pthis->MMPF_Gsensor_SetSensorOffset(pthis, arg);
			status |= pthis->MMPF_Gsensor_WriteOffsetToFile(pthis);
		break;
		
		case GSNR_CMD_READ_ACCEL_XYZ:
			if(pgsnr_attr->nInited == 1)
    			status |= pthis->MMPF_Gsensor_Read_XYZ(pthis, (GSENSOR_DATA*)arg);
		break;

		case GSNR_CMD_READ_ACCEL_WITH_COMPENSATION:
			if(pgsnr_attr->nInited == 1)
    			status |= pthis->MMPF_Gsensor_Read_XYZ_WithCompensation(pthis, (GSENSOR_DATA*)arg);
		break;

		case GSNR_CMD_SET_PWR_ON_INT_THD: 
			Gsensor_Initial_PowerOff(pthis, pgsnr_attr, *arg);
		break;

		case GSNR_CMD_SET_INT_THD: 
		{
			int		thg;
			DPRINT("GSNR_CMD_SET_INT_THD: Set Threshold arg = %d\r\n", *(unsigned char*)arg);
			thg = *(unsigned char*)arg;
			
			if ((thg == 0) || (thg == 255))
			{
				Gsensor_EnableIntXYZ(0, 0, 0);
				break;
			}
            else {			
                pthis->MMPF_Gsensor_SetDynamicRange(pthis, pgsnr_attr, 6);      // 2G

        		if ((unsigned int)thg > (unsigned int)pgsnr_attr->nMaxG)
        			thg = pgsnr_attr->nMaxG;
        		
        		// INT TH is (64/4)LSB/G
        		thg 	= MAP2HW_G(thg, pgsnr_attr) / 4;
            	pthis->MMPF_Gsensor_SetReg(pthis, 0x39, 	thg);  // Micro Motion
        		
    			DPRINT("Set Threshold %d 0x%x\r\n", *(unsigned char*)arg, thg);
    			
    			Gsensor_EnableIntXYZ(1, 1, 1);
            }
		}
		break;
		
		case GSNR_CMD_SET_INT_DURATION:
			status |= pthis->MMPF_Gsensor_SetIntDuration(pthis, *arg);
		break;
		
		case GSNR_CMD_GET_INT_STATUS:
			if (pgsnr_attr->nInited) {
			    status |= pthis->MMPF_Gsensor_GetIntStatus(pthis, arg);
			} else {
				status = 1;	// ERROR!
				*arg   = 0;
			}
		break;
		
		case GSNR_CMD_SET_POWER_SAVE:
			status |= pthis->MMPF_Gsensor_SetPowerSaveMode(pthis, *arg);
		break;
		case GSNR_CMD_SET_NORMAL_MODE:
			status |= pthis->MMPF_Gsensor_SetNormalModeDataRate(pthis, *arg);
		break;	
		case GSNR_CMD_SET_DATA_RATE:
			status |= pthis->MMPF_Gsensor_SetNormalModeDataRate(pthis, *arg);
		break;

		case GSNR_CMD_SET_INT_SOURCE:
			status |= pthis->MMPF_Gsensor_SetInterruptSource(pthis, *arg);
		break;
		
		case GSNR_CMD_GET_DATA_RATE:
			status |= pthis->MMPF_Gsensor_GetDataRate(pthis, (MMP_USHORT*)arg);
		break;
		
		case GSNR_CMD_SET_DYNA_RANGE:
			status |= pthis->MMPF_Gsensor_SetDynamicRange(pthis, pgsnr_attr, *arg);
		break;
		
		case GSNR_CMD_GET_DYNA_RANGE:
			status |= pthis->MMPF_Gsensor_GetDynamicRange(pthis, pgsnr_attr, arg);
		break;
		
		case GSNR_CMD_SET_GROUND_AXIS:
			status |= pthis->MMPF_Gsensor_SetGroundAxis(pthis, pgsnr_attr, (int)arg);
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
    Gsensor_SetGroundAxis,
    Gsensor_IOControl,
    Gsensor_Attached,
    
    //25
    Gsensor_Config_I2CM,
   
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

