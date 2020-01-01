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
#include "dsc_Key.h"

#if (GSENSOR_CONNECT_ENABLE && GSENSOR_MODULE == GSENSOR_MODULE_MC3230)
#include "Gsensor_mc3230.h"
#include "mmpf_gsensor.h"
#include "GSensor_ctrl.h"
#include "AIT_Init.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define	TO_NEGATIVE_VALUE(x)	( (~x + 0x01) | 0x0200 )
#define	TO_ABSOLUTE_VALUE(x)	( (x > 0x0200)? (0x0400 - x+1):(x) )

#define	LOW_BOUND_1G(s)			((signed char)s->ub1G - (signed char)s->ub1G_Err)
#define ABS(x) 					((x) > 0 ? (x) : -(x))

#define	MAP2HW_G(g, s)			((g * s->ub1G) / SCALE_G)

#define	STABLE_CNT				(0)

/*===========================================================================
 * Global varible
 *===========================================================================*/

static GSENSOR_DATA			m_GSensorOffset 		= {0, 0, 0};
static GSENSOR_DATA			m_GSensorShadow  		= {0, 0, 0};
#if (GSENSOR_DETECT_MODE == GSNESOR_DETECT_DIFF)
static MMP_BOOL	 			bGsensorCalibrated   	= MMP_FALSE;
#endif

static int					kUpCnt 					= 0;
static int					kDwCnt 					= 0;
static int					kLastPosition 			= GSNR_POSITION_UNKNOWN;

// I2cm Attribute
static MMP_I2CM_ATTR m_I2cmAttr_gsensor = {
	MMP_I2CM1,			//i2cmID
	GSENSOR_SLAVE_ADDR,	//ubSlaveAddr
	8,//8, 					//ubRegLen
	8, 					//ubDataLen
	0x2, 				//ubDelayTime
	MMP_FALSE, 			//bDelayWaitEn
	MMP_FALSE, 			//bInputFilterEn
	MMP_FALSE, 			//b10BitModeEn
	MMP_FALSE, 			//bClkStretchEn
	0, 					//ubSlaveAddr1
	0, 					//ubDelayCycle
	1, 					//ubPadNum
	200000 /*200KHZ*/, 	//ulI2cmSpeed
	MMP_TRUE, 			//bOsProtectEn
	GSENSOR_SCL, 		//sw_clk_pin
	GSENSOR_SDA, 		//sw_data_pin
	MMP_FALSE,			//bRfclModeEn 
	MMP_FALSE,			//bWfclModeEn
	MMP_FALSE,			//bRepeatModeEn
	0                   //ubVifPioMdlId
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
		DPRINT("GsnrRead-->Wrong Register Address\r\n");
		return MMP_ERR_NONE;
	}

	MMPF_I2cm_ReadReg(&m_I2cmAttr_gsensor, (MMP_USHORT)reg, (MMP_USHORT*)&data);
	
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
	
	st = MMPF_I2cm_WriteReg(&m_I2cmAttr_gsensor, (MMP_USHORT)reg, (MMP_USHORT)val);
	//printc("Gsensor_WriteRegister:%d   \r\n",st);
	return MMP_ERR_NONE;
}

void Gsensor_DumpRegister(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr)
{
#if (GSENSOR_DBG_MSG)

	MMP_LONG	i;
	MMP_UBYTE	rv;
	MMP_UBYTE	regs[] = {GSensor_Reg_XOUT,
	GSensor_Reg_YOUT,GSensor_Reg_ZOUT,GSensor_Reg_TILT,
	GSensor_Reg_OPSTAT,GSensor_Reg_SC,GSensor_Reg_INTEN,
	GSensor_Reg_MODE,GSensor_Reg_SAMPR,GSensor_Reg_TAPEN,
	GSensor_Reg_TAPP,GSensor_Reg_DROP,GSensor_Reg_SHDB,
	//0X0D~0X17
	GSensor_Reg_CHIPID,
	//0X19~0X20
	GSensor_Reg_XOFFL,GSensor_Reg_XOFFH,GSensor_Reg_YOFFL,
	GSensor_Reg_YOFFH,GSensor_Reg_ZOFFL,GSensor_Reg_ZOFFH,
	GSensor_Reg_XGAIN,GSensor_Reg_YGAIN,GSensor_Reg_ZGAIN,
	//0X2A
	GSensor_Reg_SHAKE_TH,GSensor_Reg_UD_Z_TH,GSensor_Reg_UD_X_TH,
	GSensor_Reg_RL_Z_TH,GSensor_Reg_RL_Y_TH,GSensor_Reg_FB_Z_TH,
	GSensor_Reg_DROP_TH,GSensor_Reg_TAP_TH,
	//0X33~0X3A
	GSensor_Reg_PCODE};

	DPRINT("====mc3230 Registers====\r\n");
							        
	for (i = 0; i < sizeof(regs); i++) 
	{
		pthis->MMPF_Gsensor_GetReg(pthis, regs[i], &rv);
		DPRINT("Reg: 0x%02x, 0x%02x\r\n", regs[i], rv);
	}
	if(pgsnr_attr != NULL)
    {   
	    DPRINT("PROPERTY id = 0x%x, Range = %d, Sens = %d, GroundAxis = %d, 1G = 0x%x , ErrG = 0x%x, MaxG = %d\r\n",
	       pgsnr_attr->ubGsensorID,
	       pgsnr_attr->ubRange,
	       pgsnr_attr->ubSensitive,
	       pgsnr_attr->ubGroundAxis,
	       pgsnr_attr->ub1G,
	       pgsnr_attr->ub1G_Err,
	       pgsnr_attr->nMaxG);
   }
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
    printc("MC3230:%s...\r\n",__func__);

	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_WriteOffsetToFile(struct _3RD_PARTY_GSENSOR *pthis)
{
	//DramToFile(GSNR_OFFSET_FILENAME, (INT8*)&m_GSensorOffset,sizeof(GSENSOR_DATA));
    printc(("MC3230:%s...\r\n",__func__));
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
    printc(("MC3230:%s...\r\n",__func__));

	return status; 
}

MMP_ERR Gsensor_ReadDeviceID(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr)
{
	MMP_ERR 	status 		= MMP_ERR_NONE;
	MMP_UBYTE	usdeviceID 	= 0;
	
	status |= pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_CHIPID, &usdeviceID);
	
	if( (usdeviceID != GSENSOR_ID_MC3230) )
	{
		status = 1;	// ERROR
		DPRINT("Gsensor Read Device ID 0x%x %d Error\r\n", usdeviceID, status);
		pgsnr_attr->ubGsensorID = 0xFF;
	}
	else
	{
		status = 0;	// SUCCESS
		DPRINT("Gsensor Read Device ID 0x%x %d Success\r\n", usdeviceID, status);
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
	MMP_USHORT x_value = 0,y_value = 0,z_value = 0;
	//MMP_USHORT x_value_lsb = 0, x_value_msb = 0, y_value_lsb = 0, y_value_msb = 0, z_value_lsb = 0, z_value_msb = 0;

#if 1
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_XOUT, (MMP_UBYTE *)&x_value);
	x_value = (x_value & DATA_MASK);
	
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_YOUT, (MMP_UBYTE *)&y_value);
	y_value = (y_value & DATA_MASK);
	
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_ZOUT, (MMP_UBYTE *)&z_value);
	z_value = (z_value & DATA_MASK);
    
	//printc("MC3230:%s,x:%d y:%d z:%d\r\n",__func__,x_value,y_value,z_value);

    #ifdef GSENSOR_ROTATE
	data->acc_val[0] = (z_value);
	data->acc_val[1] = TO_NEGATIVE_VALUE(y_value);  
	data->acc_val[2] = TO_NEGATIVE_VALUE(x_value);
	#else
	data->acc_val[0] = TO_NEGATIVE_VALUE(z_value);
	data->acc_val[1] = TO_NEGATIVE_VALUE(y_value);  
	data->acc_val[2] = (x_value);
	#endif
	#endif
    memcpy( &m_GSensorShadow, data, sizeof(GSENSOR_DATA) );
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_Read_XYZ_WithCompensation(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *data) 
{	
	MMP_USHORT x_value = 0,y_value = 0,z_value = 0;
	MMP_USHORT x_value_lsb = 0, x_value_msb = 0, y_value_lsb = 0, y_value_msb = 0, z_value_lsb = 0, z_value_msb = 0;
	MMP_UBYTE  i;
	MMP_UBYTE  ubTempX, ubTempY, ubTempZ;
	#if 1
//	char       cx,cy,cz;
//    int        x,y,z;
	#endif
#if 1	
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_XOUT, (MMP_UBYTE *)&x_value);
	
	x_value = (x_value & DATA_MASK);
	//DPRINT("x_value : %d\r\n",x_value);
	
	
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_YOUT, (MMP_UBYTE *)&y_value);
	
	y_value = (y_value & DATA_MASK);
	//DPRINT("y_value : %d\r\n",y_value);
	
	
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_ZOUT, (MMP_UBYTE *)&z_value);
	
	z_value = (z_value & DATA_MASK);
	
	data->acc_val[0] = x_value;
	data->acc_val[1] = y_value;  
	data->acc_val[2] = z_value;
		
	ubTempX = data->acc_val[0];
	ubTempY = data->acc_val[1];
	ubTempZ = data->acc_val[2];
	
	#ifdef GSENSOR_ROTATE
	data->acc_val[0] = ubTempZ;//TO_NEGATIVE_VALUE(ubTempZ);
	data->acc_val[1] = TO_NEGATIVE_VALUE(ubTempY);//TO_NEGATIVE_VALUE(ubTempY);
	data->acc_val[2] = TO_NEGATIVE_VALUE(ubTempX);
	#else	
	data->acc_val[0] = TO_NEGATIVE_VALUE(ubTempZ);
	data->acc_val[1] = TO_NEGATIVE_VALUE(ubTempY);
	data->acc_val[2] = (ubTempX);
	#endif
	
	// val 現在量到的值
    // val2 Offset 值
    // val - val2 = 插補後的值
    #if 0
    DPRINT("GS==>");

    for( i=0 ; i<3; i++ )
    {
        int      val,val2;

        val = data->acc_val[i];
        if( data->acc_val[i]& 0x80 )
        {
            val = 0x100 - data->acc_val[i];
            val = val * (-1);
        }


        val2 = m_GSensorOffset.acc_val[i];
        if( m_GSensorOffset.acc_val[i] & 0x80)
        {
            val2 = 0x100 - m_GSensorOffset.acc_val[i];
            val2 = val2 * (-1);
        }

        val  = val * 1000/16;
        val2 = val2 * 1000/16;
		
        DPRINT( "[%d=(%d)-(%d)]", (val-val2), val, val2 );
    }
    DPRINT("\n");

    DPRINT("===");

	#endif
	
	for(i=0;i<GSENSOR_DATA_LEN;i++)
	{
		#if 0
		if(data->acc_val[i] > m_GSensorOffset.acc_val[i])
		data->acc_val[i] = data->acc_val[i] - m_GSensorOffset.acc_val[i];
		else
		data->acc_val[i] = m_GSensorOffset.acc_val[i] - data->acc_val[i];	
		#else
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
			}else
			{
				if(data->acc_val[i] >= m_GSensorOffset.acc_val[i])
				data->acc_val[i] = data->acc_val[i] - m_GSensorOffset.acc_val[i];
				else
				data->acc_val[i] = 0;
			}
				
		}
		#endif
			#if 0
		// print current value
            {
            int val;
            if( data->acc_val[i] & 0x80 )
            {
                val = 0x100 - data->acc_val[i];
                val = -val;
            }
            else
            {
                val = data->acc_val[i];
            }

            DPRINT(" %d ", val*1000/16  );
            }
            #endif

	}
    memcpy( &m_GSensorShadow, data, sizeof(GSENSOR_DATA) );
	
	#if 0
	DPRINT("\n");
	#endif
#endif	
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

MMP_ERR Gsensor_CalculateOffset(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE gAxis, GSENSOR_DATA avg)
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

MMP_ERR	Gsensor_Calibration(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE side)
{
	GSENSOR_DATA avg;
	
	pthis->MMPF_Gsensor_Read_Accel_Avg(pthis, &avg);
	
	pthis->MMPF_Gsensor_CalculateOffset(pthis, side, avg); 
	
	return MMP_ERR_NONE;
}

MMP_ERR	Gsensor_SetIntDuration(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE arg)
{
	
	//pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INT1_DURATION, (arg & 0x7f));	
    printc(("MC3230:%s...\r\n",__func__));

    return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetIntStatus(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE* pstatus)
{
	MMP_UBYTE   ubStatus= 0;
	MMP_UBYTE   ubEn    = 0;

	//pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_INTEN, &ubEn);
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_TILT, &ubStatus);

    //ubEn &= 0xE0;
	*pstatus = (ubStatus & (TILT_TAPD|TILT_DROPD|TILT_SHAKED));
    
	if((ubStatus & (TILT_TAPD|TILT_DROPD|TILT_SHAKED)) != 0x00 )
	{
		DPRINT("INT STS 0x%02x\r\n", ubStatus);
		Gsensor_DumpRegister(pthis,NULL);
	}

	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetPowerSaveMode(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE mode)
{	
#if 0
	MMP_UBYTE value;
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_CTRL1, &value);
	value &= 0x0F;
	pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL1, value);
#endif
    printc(("MC3230:%s...\r\n",__func__));
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetNormalModeDataRate(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE rate)
{
#if 0
	MMP_UBYTE value;
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_CTRL1, &value);
	value &= 0x9F;
	pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL1, value);
#endif
    printc(("MC3230:%s...\r\n",__func__));
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetInterruptSource(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE src)
{
#if 0
    if (src == 0) {
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL3, 0x00); // Not mapping to INT_x
    }
    else if (src == 1)
    {
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_CTRL3, 0x40); // Mapping to INT_1
    }
#endif
    printc(("MC3230:%s...\r\n",__func__));
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetDataRate(struct _3RD_PARTY_GSENSOR *pthis, MMP_USHORT *wDataRate)
{
	MMP_UBYTE ubValue1,ubValue2 ;
	MMP_UBYTE ubOpmode;
#if 0
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
#endif
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetDynamicRange(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr, MMP_UBYTE ubDrange)
{
	MMP_UBYTE ubFullSacleRange;
    printc(("MC3230:%s...\r\n",__func__));

#if 0
	pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_CTRL4,&ubFullSacleRange);
	
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
			return 1;	// ERROR!
	}
	pthis->MMPF_Gsensor_SetReg(pthis,GSensor_Reg_CTRL4, ubFullSacleRange);
#endif	
	switch (ubDrange) 
	{
		case 2:
		 	pgsnr_attr->nMaxG	    = MAX_2G;
		 	pgsnr_attr->ub1G	 	= 0x80;	/* the value is absolute for threshold, it needs divided by 2 for XYZ */
		 	pgsnr_attr->ub1G_Err    = 0x08;
		break;
		case 4:
		 	pgsnr_attr->nMaxG	    = MAX_4G;
		 	pgsnr_attr->ub1G	 	= 0x40;
		 	pgsnr_attr->ub1G_Err    = 0x04;
		break;
		case 8:
		 	pgsnr_attr->nMaxG	    = MAX_8G;
		 	pgsnr_attr->ub1G	 	= 0x20;
		 	pgsnr_attr->ub1G_Err    = 0x02;
		break;
		case 16:
		 	pgsnr_attr->nMaxG	    = MAX_16G;
		 	pgsnr_attr->ub1G	 	= 0x10;
		 	pgsnr_attr->ub1G_Err    = 0x01;
		break;
	}
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_GetDynamicRange(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr, MMP_UBYTE *ubDrange)
{
	MMP_UBYTE ubValue;
	MMP_UBYTE ubRange;

	if(pgsnr_attr->ubGsensorID != GSENSOR_ID_MC3230)
		return MMP_ERR_NONE;

	//pthis->MMPF_Gsensor_GetReg(pthis, GSensor_Reg_CTRL4,&ubValue);
    printc(("MC3230:%s...\r\n",__func__));

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
		case DYNAMIC_RANGE_16:
			*ubDrange = 16;
		break;
		default:
			*ubDrange = 1;
		break;
	}
	return MMP_ERR_NONE;
}

MMP_ERR Gsensor_SetGroundAxis(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr, MMP_UBYTE arg)
{
	MMP_ERR status = MMP_ERR_NONE;

	return status;
}

MMP_ERR Gsensor_Initial(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr)
{
    MMP_UBYTE u8temp = 0;

    pthis->MMPF_Gsensor_ReadDeviceID(pthis, pgsnr_attr); 
    
    if(pgsnr_attr->ubGsensorID == GSENSOR_ID_MC3230)
    {	
        #if 0
        //Initial sequence listed in MC3230 Datasheet (aps-048-0007v1.1).pdf
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_MODE, MODE_IPP|MODE_OPCON);
        //pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_SPCNT, 0x00);
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_TILT, 0x03); // No mapping to INT_x
        //pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_PDET, 0xE0); // Set dynamic range 8G
        //pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_SR, 0x34);
	    pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INTEN, TILT_TAPD|TILT_DROPD|TILT_SHAKED);
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_MODE, MODE_IPP|0x01); // INT high active
        #else
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_MODE, 0x43);
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_SC, 0x00);
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_SAMPR, 0x00);
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_TAPEN, 0x80);
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_DROP, 0x00);
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_DROP_TH, 0x80);
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_TAPP, 0x03);
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_TAP_TH, 0x5c);
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INTEN, 0x04);
        pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_MODE, 0x41);
        #endif
        
        //pthis->MMPF_Gsensor_SetDynamicRange(pthis, pgsnr_attr, pgsnr_attr->ubRange);

        Gsensor_DumpRegister(pthis,NULL);
        pgsnr_attr->nInited = 1;
    } 
    else 
    {
        printc(FG_RED("Wrong G-Sensor ID for MC3230\r\n"));

        pgsnr_attr->ubRange     = 2;
        pgsnr_attr->nMaxG	    = MAX_2G;
        pgsnr_attr->ub1G		= 0x40;	
        pgsnr_attr->ub1G_Err    = 0x08;
    }
    return MMP_ERR_NONE;
}

void Gsensor_Initial_PowerOff(struct _3RD_PARTY_GSENSOR *pthis, GSNR_ATTRIBUTE *pgsnr_attr, MMP_UBYTE ubPowerGsenOnValue)
{
    MMP_UBYTE status;

    DPRINT("### %s - %d\r\n", __func__, ubPowerGsenOnValue);

#if 1
	pthis->MMPF_Gsensor_ReadDeviceID(pthis, pgsnr_attr); 
    
    if(pgsnr_attr->ubGsensorID == GSENSOR_ID_MC3230)
	{	
        if (0 == ubPowerGsenOnValue) {
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_MODE, 0x43);
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_SC, 0x00);
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_SAMPR, 0x00);
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_TAPEN, 0x80);
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_DROP, 0x00);
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_DROP_TH, 0x80);
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_TAPP, 0x03);
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_TAP_TH, 0x5c);
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INTEN, 0x00);//disable all interrupt
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_MODE, 0x41);
        }
        else {
			int		thg;
			thg = ubPowerGsenOnValue;

            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_MODE, 0x43);
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_SC, 0x00);
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_SAMPR, 0x00);
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_TAPEN, 0x80);
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_DROP, 0x00);
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_DROP_TH, 0x80);
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_TAPP, 0x03);
            if(ubPowerGsenOnValue == POWER_ON_GSNR_SENS_LEVEL0)//high
                pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_TAP_TH, 0x10);
            else if(ubPowerGsenOnValue == POWER_ON_GSNR_SENS_LEVEL1)//middle
                pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_TAP_TH, 0x90);
            else//low
                pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_TAP_TH, 0xe0);
            
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INTEN, 0x04);//disable all interrupt
            pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_MODE, 0x41);

			//DPRINT("Set Threshold %d 0x%x\r\n", ubPowerGsenOnValue, thg);

		    pgsnr_attr->nInited = 1;
	    }
    }
	else 
	{
		pgsnr_attr->ubRange     = 2;
        pgsnr_attr->nMaxG       = MAX_2G;
        pgsnr_attr->ub1G        = 0x40;	
        pgsnr_attr->ub1G_Err    = 0x08;
	}
#endif
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
				
				//pgsnr_attr->nInited = 1;
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
			
			thg = *(int *) arg;

			if ((unsigned int)thg > (unsigned int)pgsnr_attr->nMaxG)
				thg = pgsnr_attr->nMaxG;
			
			thg 	= MAP2HW_G(thg, pgsnr_attr);
			//status 	= pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INT1_THD, (MMP_UBYTE)thg);
			/* duration is how long to keep the HG */
			//status 	= pthis->MMPF_Gsensor_SetReg(pthis, GSensor_Reg_INT1_DURATION, (MMP_UBYTE)0x28);
			
			DPRINT("Set Threshold %d 0x%x\r\n", *(int *) arg, thg);
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
    Gsensor_SetGroundAxis,
    Gsensor_IOControl,
    Gsensor_Attached,
    
    //25
    Gsensor_Config_I2CM,
   
};

int Gsensor_Module_Init(void)
{
    printc("[MC3230 - Gsensor_Module_Init]\r\n");
    MMPF_3RDParty_Gsensor_Register(&Gsensor_Obj);
    return 0;    
}

#pragma arm section code = "initcall6", rodata = "initcall6", rwdata = "initcall6",  zidata = "initcall6" 
#pragma O0
ait_module_init(Gsensor_Module_Init);
#pragma
#pragma arm section rodata, rwdata ,  zidata 

#endif		// ALL_FW

#ifdef MBOOT_FW
MMP_BOOL Gsensor_GetIntStatusForBoot(void)
{
	MMP_USHORT	value	= 0;
	MMP_USHORT	usEn	= 0;

	MMPF_I2cm_ReadReg(&m_I2cmAttr_gsensor, GSensor_Reg_INTEN, (MMP_USHORT*)&usEn);
	MMPF_I2cm_ReadReg(&m_I2cmAttr_gsensor, GSensor_Reg_TILT, (MMP_USHORT*)&value);
    //DPRINT("INTEN=0x%02x,TILT=0x%02x\r\n", usEn, value);

    value &= (TILT_TAPD|TILT_DROPD|TILT_SHAKED);
    
    if (value) {
        RTNA_DBG_PrintLong(0, value);
        return MMP_TRUE;
    }

    return MMP_FALSE;
}
#endif

#endif //GSENSOR_CONNECT_ENABLE && GSENSOR_MODULE == GSENSOR_MODULE_MC3230)

