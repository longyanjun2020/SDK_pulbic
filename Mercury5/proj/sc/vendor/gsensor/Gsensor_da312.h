#ifndef _GSENSOR_DA312_H_
#define _GSENSOR_DA312_H_

#include "Customer_config.h"	// CarDV
#include "mmpf_gsensor.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

//HW I2C
#ifndef GSENSOR_SLAVE_ADDR
#define GSENSOR_SLAVE_ADDR				(0x4E)
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

#define GSENSOR_ID_DA312				(0x13)

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
#define	INT_THD_MAX						(0x7F)

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
#define DYNAMIC_RANGE_2 				(0x0)
#define DYNAMIC_RANGE_4 				(0x1)
#define DYNAMIC_RANGE_8 				(0x2)
#define DYNAMIC_RANGE_16 				(0x3)
#define DYNAMIC_RANGE_MASK				(0x3)

#define DATA_MASK						(0xFF)
/*===========================================================================
 * Enum define
 *===========================================================================*/

typedef enum
{
	GSensor_Reg_Config 			= 0x00,
	GSensor_Reg_ChipID 			= 0x01,
	GSensor_Reg_XOUT_L		= 0x02,
	GSensor_Reg_XOUT_H 			= 0x03,//
	GSensor_Reg_YOUT_L			= 0x04,//
	GSensor_Reg_YOUT_H 			= 0x05,
	GSensor_Reg_ZOUT_L 		= 0x06,//
	GSensor_Reg_ZOUT_H		=0x07,
	GSensor_Reg_Motion_INT	 = 0x09,//
	GSensor_Reg_Data_INT	 = 0x0a,//
	GSensor_Reg_Tap_Active_Statu	 = 0x0b,//
	GSensor_Reg_Orientation_Statu	 = 0x0c,//	
	GSensor_Reg_Grange	 = 0x0f,//
	GSensor_Reg_ODR_Axis_DIS	 = 0x10,//
	GSensor_Reg_mode_BW	 = 0x11,//
	GSensor_Reg_Swap_Polarity	 = 0x12,//
	GSensor_Reg_INT_SET1	 = 0x16,//
	GSensor_Reg_INT_SET2	 = 0x17,//
	GSensor_Reg_INT_MAP1	 = 0x19,//
	GSensor_Reg_INT_MAP2	 = 0x1A,//
	GSensor_Reg_INT_MAP3	 = 0x1B,//
	GSensor_Reg_INT_pin_Cof	 = 0x20,//
	GSensor_Reg_INT_LTACH	 = 0x21,//
	GSensor_Reg_FF_DURA	 = 0x22,//
	GSensor_Reg_FF_TH	 = 0x23,//
	GSensor_Reg_FF_HYSTERESIS	 = 0x24,//
	GSensor_Reg_Active_DURA	 = 0x27,//
	GSensor_Reg_Active_TH	 = 0x28,//
	GSensor_Reg_Tap_DURA	 = 0x2a,//
	GSensor_Reg_Tap_TH	 = 0x2b,//
	GSensor_Reg_Orient_SET	 = 0x2C,//
	GSensor_Reg_Z_block	 = 0x2d,//
	GSensor_Reg_SelfTest	 = 0x32,//
	GSensor_Reg_CUST_Offset_x	 = 0x38,//
	GSensor_Reg_CUST_Offset_y	 = 0x39,//
	GSensor_Reg_CUST_Offset_z	 = 0x3a,//
	GSensor_Reg_CUST_OTP_Programed	 = 0x4e,//
	GSensor_Reg_CUST_OTP_Ready	 = 0x4f,//
	GSensor_Reg_z_cal_en	 = 0x50,//
	GSensor_Reg_z_rot_hold_time	 = 0x51,//
	GSensor_Reg_z_rot_dura	 = 0x52,//
	GSensor_Reg_rot_th_h	 = 0x53,//
	GSensor_Reg_rot_th_l	 = 0x54,//
	GSensor_Reg_engineer_mode = 0x7f,


	GSensor_Reg_INVALID
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

