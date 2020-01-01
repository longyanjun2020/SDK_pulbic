#ifndef _GSENSOR_DMARD06_H_
#define _GSENSOR_DMARD06_H_

#include "GSensor_ctrl.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

//HW I2C
#define GSENSOR_SLAVE_ADDR				(0x38)
#define GSENSOR_SCL						(MMP_GPIO16)
#define GSENSOR_SDA						(MMP_GPIO17)  

//General
#define GSENSOR_DATA_LEN				(3)
#define CALIBRATE_AVG_NUM				(10)
#define DEFAULT_SENSITIVITY				(64)

#define GSENSOR_ID_V06					(0x06)
#define GSENSOR_ID_V07					(0x07)
#define GSENSOR_ID_V10					(0x55)

//Calibration
#define GSNR_CALIBRATE_G_ON_Z_NEGATIVE 	(1)
#define GSNR_CALIBRATE_G_ON_Z_POSITIVE 	(2)
#define GSNR_CALIBRATE_G_ON_Y_NEGATIVE 	(3)
#define GSNR_CALIBRATE_G_ON_Y_POSITIVE 	(4)
#define GSNR_CALIBRATE_G_ON_X_NEGATIVE 	(5)
#define GSNR_CALIBRATE_G_ON_X_POSITIVE 	(6)

//Interupt Event Config [0x4A]
#define OR_ALL_EVENT         			(0x00)
#define ALL_6D_MOVEMENT         		(0x40)
#define AND_All_EVENT        			(0x80)
#define ALL_6D_POSITION         		(0xC0)

#define ENABLE_X_HIGH_G         		(0x20) 
#define ENABLE_X_LOW_G          		(0x10)
#define ENABLE_Y_HIGH_G    				(0x08)
#define ENABLE_Y_LOW_G     				(0x04)
#define ENABLE_Z_HIGH_G     			(0x02)
#define ENABLE_Z_LOW_G					(0x01)

#define All_DETECT           			(0xFF)
#define All_DISABLE           			(0x00)
#define ALL_6D_HIGH_LOW_G				(0x3F)
#define ALL_6D_HIGH_G					(0x2A)
#define ALL_6D_MOVE_HIGH_G				(0x6A)
#define ALL_6D_LOW_G					(0x15)

//Interrupt Threshold [0x4C]
#define	INT_THD_MAX						(0x7F)

//Power Save Mode [0x44]
#define	POWER_MODE_SHUTDOWN				(0x00)
#define	POWER_MODE_NORMAL				(0x20)
#define	POWER_MODE_LOW_32HZ				(0x40)
#define	POWER_MODE_LOW_16HZ				(0x60)
#define	POWER_MODE_LOW_8HZ				(0x80)
#define	POWER_MODE_LOW_4HZ				(0xA0)
#define	POWER_MODE_LOW_2HZ				(0xC0)
#define POWER_MODE_MASK         		(0xE0)
#define NORMAL_MODE_MASK        		(0x18)

//Data Rate [0x44]
#define DATA_RATE_342HZ					(0x00)
#define DATA_RATE_85HZ					(0x08)
#define DATA_RATE_42HZ					(0x10)
#define DATA_RATE_21HZ					(0x18)

//Dynaminc_Range [0x45]
#define DYNAMIC_RANGE_2 				(0x00)
#define DYNAMIC_RANGE_4 				(0x40)
#define DYNAMIC_RANGE_8 				(0xC0)
#define DYNAMIC_RANGE_MASK				(0xC0)

//Interrput Source Config [0x47]
#define INT1_SOURCE_GROUND				(0x00)
#define INT1_SOURCE_SRC1				(0x04)
#define INT1_SOURCE_SRC1_SRC2			(0x08)
#define INT1_SOURCE_DATA_READY			(0x0C)

/*===========================================================================
 * Enum define
 *===========================================================================*/

typedef enum
{
	GSensor_Reg_GetID 			= 0x0F,
	GSensor_Reg_TOUT 			= 0x40,	
	GSensor_Reg_XOUT 			= 0x41,
	GSensor_Reg_YOUT 			= 0x42,
	GSensor_Reg_ZOUT 			= 0x43,
	GSensor_Reg_CTRL1 			= 0x44,
	GSensor_Reg_CTRL2 			= 0x45,
	GSensor_Reg_CTRL3 			= 0x46,
	GSensor_Reg_CTRL4	 		= 0x47,
	GSensor_Reg_CTRL5	 		= 0x48,
	GSensor_Reg_STATUS	 		= 0x49,
	GSensor_Reg_INT1_CONFIG		= 0x4A,
	GSensor_Reg_INT1_STATUS 	= 0x4B,
	GSensor_Reg_INT1_THD 		= 0x4C,		
	GSensor_Reg_INT1_DURATION 	= 0x4D,	
	GSensor_Reg_SW_RESET 		= 0x53,
	GSensor_Reg_INVALID
}GSENSOR_REG;

#endif

