#ifndef _GSENSOR_GMA30x_H_
#define _GSENSOR_GMA30x_H_

#include "Customer_config.h"	// CarDV
#include "mmpf_gsensor.h"
#include "GSensor_ctrl.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

//HW I2C
#ifndef GSENSOR_SLAVE_ADDR
#define GSENSOR_SLAVE_ADDR				(0x30)
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

#define GSENSOR_ID_GMA301				(0x55)
#define GSENSOR_ID_GMA30x				(0x55)

//Calibration
#define GSNR_CALIBRATE_G_ON_Z_NEGATIVE 	(1)
#define GSNR_CALIBRATE_G_ON_Z_POSITIVE 	(2)
#define GSNR_CALIBRATE_G_ON_Y_NEGATIVE 	(3)
#define GSNR_CALIBRATE_G_ON_Y_POSITIVE 	(4)
#define GSNR_CALIBRATE_G_ON_X_NEGATIVE 	(5)
#define GSNR_CALIBRATE_G_ON_X_POSITIVE 	(6)

//Action Mode [0x00]
#define MODE_Off						(0x00)
#define MODE_ResetAtOff					(0x01)
#define MODE_Standby					(0x02)
#define MODE_ResetAtStandby				(0x03)
#define MODE_Active						(0x06)
#define MODE_Trigger					(0x0A)
#define MODE_ReadOTP					(0x12)
#define MODE_WriteOTP					(0x22)
#define MODE_WriteOTPBuf				(0x42)
#define MODE_ResetDataPath				(0x82)

//AFE Mode [0x0C]
#define VALUE_AFEM_AFEN_Normal			(0x8F)// AFEN set 1 , ATM[2:0]=b'000(normal),EN_Z/Y/X/T=1
#define VALUE_AFEM_Normal				(0x0F)// AFEN set 0 , ATM[2:0]=b'000(normal),EN_Z/Y/X/T=1

//Output Date Rate [0x0D]
#define VALUE_CKSEL_ODR_0_204			(0x04)// ODR[3:0]=b'0000 (0.78125Hz), 	CCK[3:0]=b'0100 (204.8kHZ)
#define VALUE_CKSEL_ODR_1_204			(0x14)// ODR[3:0]=b'0001 (1.5625Hz), 	CCK[3:0]=b'0100 (204.8kHZ)
#define VALUE_CKSEL_ODR_3_204			(0x24)// ODR[3:0]=b'0010 (3.125Hz), 	CCK[3:0]=b'0100 (204.8kHZ)
#define VALUE_CKSEL_ODR_6_204			(0x34)// ODR[3:0]=b'0011 (6.25Hz), 		CCK[3:0]=b'0100 (204.8kHZ)
#define VALUE_CKSEL_ODR_12_204			(0x44)// ODR[3:0]=b'0100 (12.5Hz), 		CCK[3:0]=b'0100 (204.8kHZ)
#define VALUE_CKSEL_ODR_25_204			(0x54)// ODR[3:0]=b'0101 (25Hz), 		CCK[3:0]=b'0100 (204.8kHZ)
#define VALUE_CKSEL_ODR_50_204			(0x64)// ODR[3:0]=b'0110 (50Hz), 		CCK[3:0]=b'0100 (204.8kHZ)
#define VALUE_CKSEL_ODR_100_204			(0x74)// ODR[3:0]=b'0111 (100Hz), 		CCK[3:0]=b'0100 (204.8kHZ)

//Interrupt Control [0x0E]
#define VALUE_INTC						(0x00)// INTC[6:5]=b'00 
#define VALUE_INTC_Interrupt_En			(0x13)// INTC[6:5]=b'01 (Data ready interrupt enable, active high at INT0)
#define VALUE_INTC_Interrupt_En1		(0x20)// INTC[6:5]=b'01 (Data ready interrupt enable, active high at INT0)

//Tap Number [0x0F]
#define VALUE_TAPNS_NoFilter			(0x00)	// TAP1/TAP2	NO FILTER
#define VALUE_TAPNS_Ave_2				(0x11)	// TAP1/TAP2	Average 2
#define VALUE_TAPNS_Ave_4				(0x22)	// TAP1/TAP2	Average 4
#define VALUE_TAPNS_Ave_8				(0x33)	// TAP1/TAP2	Average 8
#define VALUE_TAPNS_Ave_16				(0x44)	// TAP1/TAP2	Average 16
#define VALUE_TAPNS_Ave_32				(0x55)	// TAP1/TAP2	Average 32

//Oscillator Calibration [0x1F]
#define VALUE_MISC2_OSCA_EN				(0x08)

//Power Down Control [0x21]
#define VALUE_PD_RST					(0x52)

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
	GSensor_Reg_ACTR 			= 0x00,
	GSensor_Reg_AFEM 			= 0x0C,	
	GSensor_Reg_CKSEL 			= 0x0D,
	GSensor_Reg_INTC 			= 0x0E,
	GSensor_Reg_TAPNS 			= 0x0F,
	GSensor_Reg_MISC1 			= 0x11,
	GSensor_Reg_STADR 			= 0x12,
	GSensor_Reg_TILT 			= 0x13,
	GSensor_Reg_DATA_X	 		= 0x14,
	GSensor_Reg_DATA_X_MSB	 	= 0x15,	
	GSensor_Reg_DATA_Y	 		= 0x16,
	GSensor_Reg_DATA_Y_MSB	 	= 0x17,	
	GSensor_Reg_DATA_Z	 		= 0x18,
	GSensor_Reg_DATA_Z_MSB	 	= 0x19,	
	GSensor_Reg_DATA_T			= 0x1A,
	GSensor_Reg_DATA_T_MSB		= 0x1B,	
	GSensor_Reg_STAINT 			= 0x1C,
	GSensor_Reg_MISC2 			= 0x1F,		
	GSensor_Reg_PD				= 0x21,
	GSensor_Reg_INVALID			= 0x40
}GSENSOR_REG;

#endif

