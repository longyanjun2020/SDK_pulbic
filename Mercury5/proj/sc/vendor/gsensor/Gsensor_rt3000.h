#ifndef _GSENSOR_LIS3DH_H_
#define _GSENSOR_LIS3DH_H_

//#include "Customer_config.h"	// CarDV
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

#define GSENSOR_ID_RT3000				(0x33)

//Calibration
#define GSNR_CALIBRATE_G_ON_Z_NEGATIVE 	(1)
#define GSNR_CALIBRATE_G_ON_Z_POSITIVE 	(2)
#define GSNR_CALIBRATE_G_ON_Y_NEGATIVE 	(3)
#define GSNR_CALIBRATE_G_ON_Y_POSITIVE 	(4)
#define GSNR_CALIBRATE_G_ON_X_NEGATIVE 	(5)
#define GSNR_CALIBRATE_G_ON_X_POSITIVE 	(6)

//Interupt Event Config [0x30]
#define WAKEUP							(0x00)
#define MOVEMENT						(0x40)
#define FREE_FALL        				(0x80)
#define POSITION         				(0xC0)

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
	GSensor_Reg_STATUS			= 0x27,
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


#endif // #ifndef _GSENSOR_LIS3DH_H_

