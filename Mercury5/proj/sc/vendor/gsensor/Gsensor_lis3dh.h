#ifndef _GSENSOR_LIS3DH_H_
#define _GSENSOR_LIS3DH_H_

#include "Customer_config.h"	// CarDV
#include "mmpf_gsensor.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

//HW I2C
#ifndef GSENSOR_SLAVE_ADDR
#define GSENSOR_SLAVE_ADDR				(0x19)
#endif
#ifndef GSENSOR_SCL
#define GSENSOR_SCL						(MMP_GPIO0)
#endif
#ifndef GSENSOR_SDA
#define GSENSOR_SDA						(MMP_GPIO1)
#endif
#ifndef GSENSOR_INT
#define GSENSOR_INT						(MMP_GPIO99)
#endif

//General
#define GSENSOR_DATA_LEN				(3)
#define CALIBRATE_AVG_NUM				(10)
#define DEFAULT_SENSITIVITY				(64)

#define GSENSOR_ID_LIS3DH				(0x33)

//Calibration
#define GSNR_CALIBRATE_G_ON_Z_NEGATIVE 	(1)
#define GSNR_CALIBRATE_G_ON_Z_POSITIVE 	(2)
#define GSNR_CALIBRATE_G_ON_Y_NEGATIVE 	(3)
#define GSNR_CALIBRATE_G_ON_Y_POSITIVE 	(4)
#define GSNR_CALIBRATE_G_ON_X_NEGATIVE 	(5)
#define GSNR_CALIBRATE_G_ON_X_POSITIVE 	(6)

//Interupt Event Config [0x30]
#define OR_ALL_EVENT         			(0x00)
#define ALL_6D_MOVEMENT         		(0x40)
#define AND_All_EVENT        			(0x80)
#define ALL_6D_POSITION         		(0xC0)

#define ENABLE_X_HIGH_G         		(0x02) 
#define ENABLE_X_LOW_G          		(0x01)
#define ENABLE_Y_HIGH_G    				(0x08)
#define ENABLE_Y_LOW_G     				(0x04)
#define ENABLE_Z_HIGH_G     			(0x20)
#define ENABLE_Z_LOW_G					(0x10)

//Interrupt Threshold [0x32]
#define	INT_THD_MASK					(0x7F)

//Data Rate [0x20 bits[7:4]]
#define DATA_RATE_POWER_DOWN			(0x00)
#define DATA_RATE_1HZ					(0x10)
#define DATA_RATE_10HZ					(0x20)
#define DATA_RATE_25HZ					(0x30)
#define DATA_RATE_50HZ					(0x40)
#define DATA_RATE_100HZ					(0x50)
#define DATA_RATE_200HZ					(0x60)
#define DATA_RATE_400HZ					(0x70)
#define DATA_RATE_L_1_5KHZ				(0x80)
#define DATA_RATE_N_1_25_L_5KHZ			(0x90)


//Dynaminc_Range [0x23 bits[5:4]]
#define DYNAMIC_RANGE_2 				(0x00)
#define DYNAMIC_RANGE_4 				(0x10)
#define DYNAMIC_RANGE_8 				(0x20)
#define DYNAMIC_RANGE_16 				(0x30)
#define DYNAMIC_RANGE_MASK				(0x30)


/*===========================================================================
 * Enum define
 *===========================================================================*/

typedef enum
{
	GSensor_Reg_GetID 			= 0x0F,
	GSensor_Reg_CTRL0 			= 0x06,
	Gsensor_Reg_TEMP_CFG		= 0x1F,
	GSensor_Reg_CTRL1 			= 0x20,
	GSensor_Reg_CTRL2 			= 0x21,
	GSensor_Reg_CTRL3 			= 0x22,
	GSensor_Reg_CTRL4 			= 0x23,
	GSensor_Reg_CTRL5 			= 0x24,
	GSensor_Reg_CTRL6	 		= 0x25,
	GSensor_Reg_REFERENCE		= 0x26,
	GSensor_Reg_STATUS_REG2		= 0x27,
	GSensor_Reg_XOUT_LSB        = 0x28,
	GSensor_Reg_XOUT_MSB 	    = 0x29,
	GSensor_Reg_YOUT_LSB 		= 0x2A,
	GSensor_Reg_YOUT_MSB 		= 0x2B,
	GSensor_Reg_ZOUT_LSB 		= 0x2C,
	GSensor_Reg_ZOUT_MSB 		= 0x2D,
	
	GSensor_Reg_INT1_CONFIG		= 0x30,
	GSensor_Reg_INT1_STATUS 	= 0x31,		
	
	GSensor_Reg_INT1_THD 		= 0x32,		
	GSensor_Reg_INT1_DURATION 	= 0x33,		
	
	GSensor_Reg_INVALID			= 0x40
	
}GSENSOR_REG;
#if 0
MMP_ERR Gsensor_ReadRegister(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE reg , MMP_UBYTE* pval);
MMP_ERR Gsensor_WriteRegister(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE reg , MMP_UBYTE val);
MMP_ERR Gsensor_ReadOffsetFromFile(void);
MMP_ERR Gsensor_WriteOffsetToFile(void);
MMP_ERR Gsensor_ResetDevice(void); 
MMP_ERR Gsensor_ReadDeviceID(void);
MMP_ERR	Gsensor_GetSensorOffset(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE *data);
MMP_ERR	Gsensor_SetSensorOffset(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE *data);
MMP_ERR Gsensor_Read_XYZ(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *data);
MMP_ERR Gsensor_Read_XYZ_WithCompensation(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *data); 
MMP_ERR Gsensor_Read_Accel_Avg(struct _3RD_PARTY_GSENSOR *pthis, GSENSOR_DATA *data);
MMP_ERR Gsensor_CalculateOffset(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE gAxis, GSENSOR_DATA avg);
MMP_ERR	Gsensor_Calibration(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE side);
MMP_ERR	Gsensor_SetIntDuration(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE arg);
MMP_ERR Gsensor_GetIntStatus(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE* pstatus);
MMP_ERR Gsensor_SetPowerSaveMode(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE mode);
MMP_ERR Gsensor_SetNormalModeDataRate(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE rate);
MMP_ERR Gsensor_SetInterruptSource(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE src);
MMP_ERR Gsensor_GetDataRate(struct _3RD_PARTY_GSENSOR *pthis, MMP_USHORT *wDataRate);
MMP_ERR Gsensor_SetDynamicRange(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE ubDrange);
MMP_ERR Gsensor_GetDynamicRange(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE *ubDrange);
MMP_ERR Gsensor_SetGroundAxis(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE arg);
MMP_ERR Gsensor_Initial(void);
MMP_ERR Gsensor_IOControl(struct _3RD_PARTY_GSENSOR *pthis, MMP_UBYTE cmd, MMP_UBYTE* arg);
#endif
#endif

