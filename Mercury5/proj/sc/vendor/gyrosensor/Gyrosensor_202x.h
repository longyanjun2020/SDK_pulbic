#ifndef _GYROSENSOR_202X_H_
#define _GYROSENSOR_202X_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmpf_i2cm.h"
#include "mmpf_timer.h"
#include "mmpf_gyrosensor.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

// I2CM
#define CFG_GYROSENSOR_I2C_ID       (MMP_I2CM3)
#define CFG_GYROSENSOR_I2C_PADSET   (3)

#ifdef CFG_GYROSENSOR_I2C_ID
#define GYROSENSOR_I2C_ID           (CFG_GYROSENSOR_I2C_ID)
#else
#define GYROSENSOR_I2C_ID           (MMP_I2CM_GPIO)
#endif

#ifdef CFG_GYROSENSOR_I2C_PADSET
#define GYROSENSOR_I2C_PADSET       (CFG_GYROSENSOR_I2C_PADSET)
#else
#define GYROSENSOR_I2C_PADSET       (3)     // GPIO16/17
#endif

#ifdef CFG_GYROSENSOR_SCL
#define GYROSENSOR_SCL              (CFG_GYROSENSOR_SCL)
#else
#define GYROSENSOR_SCL              (MMP_GPIO16)
#endif

#ifdef CFG_GYROSENSOR_SDA
#define GYROSENSOR_SDA              (CFG_GYROSENSOR_SDA)
#else
#define GYROSENSOR_SDA              (MMP_GPIO17)
#endif

#ifdef CFG_GYROSENSOR_SLAVE_ADDR
#define GYROSENSOR_SLAVE_ADDR       (CFG_GYROSENSOR_SLAVE_ADDR << 1)
#else
#define GYROSENSOR_SLAVE_ADDR       (0x68) // 0x69 if GYRO AD0 is high
#endif

// MISC
//#define ENABLE_GYRO_INT
//#define ENABLE_FSYNC
//#define ENABLE_FIFO

//GPIO
#define CFG_GYRO_INTR_GPIO          (MMP_GPIO19)
#define CFG_GYRO_AD0_GPIO           (MMP_GPIO_MAX)

#ifdef ENABLE_GYRO_INT
#ifdef  CFG_GYRO_INTR_GPIO
#define GYRO_INTR_GPIO              (CFG_GYRO_INTR_GPIO)
#else
#define GYRO_INTR_GPIO              (MMP_GPIO18)
#endif

#else
#define GYRO_INTR_GPIO              (MMP_GPIO_MAX)
#endif

#ifdef  CFG_GYRO_AD0_GPIO
#define GYRO_AD0_GPIO				(CFG_GYRO_AD0_GPIO)
#else
#define GYRO_AD0_GPIO				(MMP_GPIO19)
#endif

#ifdef CFG_GYRO_AD0_GPIO_LEVEL
#define GYRO_AD0_GPIO_LEVEL			(CFG_GYRO_AD0_GPIO_LEVEL)
#else
#define GYRO_AD0_GPIO_LEVEL			(GPIO_LOW)
#endif

// Device
#define GYROSENSOR_DEVICE_ID		(0x68)

#define GYRO_TIMER_ID         		(MMPF_TIMER_3)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _GYROSENSOR_202x_REG
{
	GyroSensor_202x_SMPLRT_DIV   = 0x19,
    	/*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_202x_SAMP_RATE_DIV_MASK   0xFF
    	/*------------------------------------------------------------*/
	GyroSensor_202x_CONFIG_0	    = 0x1A,
    	/*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_202x_FIFO_FULL_STOP       0x40
        #define GYROSENSOR_202x_FIFO_FULL_OVERWRITE  0x00
    	#define GYROSENSOR_202x_EXT_SYNC_MASK        0x38
    	#define GYROSENSOR_202x_DLPF_CFG_MASK        0x07
    	/*------------------------------------------------------------*/
	GyroSensor_202x_CONFIG_1	    = 0x1B,
    	/*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_202x_XG_SELF_TEST         0x80
        #define GYROSENSOR_202x_YG_SELF_TEST         0x40
        #define GYROSENSOR_202x_ZG_SELF_TEST         0x20
        
        #define GYROSENSOR_202x_DYNAMIC_RANGE_31d25  0x00
        #define GYROSENSOR_202x_DYNAMIC_RANGE_62d5   0x08
        #define GYROSENSOR_202x_DYNAMIC_RANGE_125    0x10
        #define GYROSENSOR_202x_DYNAMIC_RANGE_250    0x18
        #define GYROSENSOR_202x_DYNAMIC_RANGE_MASK   0x18
        
        #define GYROSENSOR_202x_FCHOICE_B_MASK       0x03
    	/*------------------------------------------------------------*/
	GyroSensor_202x_FIFO_EN	    = 0x23,
    	/*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_202x_TEMP_FIFO_EN         0x80
        #define GYROSENSOR_202x_XG_FIFO_EN           0x40
        #define GYROSENSOR_202x_YG_FIFO_EN           0x20
        #define GYROSENSOR_202x_ZG_FIFO_EN           0x10
        #define GYROSENSOR_202x_ALL_FIFO_DIS         0x00
    	/*------------------------------------------------------------*/
	GyroSensor_202x_INT_CFG	    = 0x37,
    	/*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_202x_INT_LEVEL_L          0x80
        #define GYROSENSOR_202x_INT_LEVEL_H          0x00
        #define GYROSENSOR_202x_INT_OPEN_DRAIN       0x40
        #define GYROSENSOR_202x_INT_PUSH_PULL        0x00
        #define GYROSENSOR_202x_LATCH_INT_EN         0x20
    	#define GYROSENSOR_202x_INT_READ_CLEAR       0x10
        #define GYROSENSOR_202x_FSYNC_INT_LEVEL_L    0x08
        #define GYROSENSOR_202x_FSYNC_INT_LEVEL_H    0x00
        #define GYROSENSOR_202x_FSYNC_INT_MODE_EN    0x04
    	/*------------------------------------------------------------*/	
	GyroSensor_202x_INT_EN	    = 0x38,
	GyroSensor_202x_INT_STS 		= 0x3A,
    	/*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_202x_INT_NONE             0x00
        #define GYROSENSOR_202x_INT_FIFO_FULL        0x10
        #define GYROSENSOR_202x_INT_FSYNC            0x08
        #define GYROSENSOR_202x_INT_DATA_READY       0x01
    	/*------------------------------------------------------------*/	
	GyroSensor_202x_TOUT_H	    = 0x41,
	GyroSensor_202x_TOUT_L	    = 0x42,
	GyroSensor_202x_XOUT_H	    = 0x43,
	GyroSensor_202x_XOUT_L	    = 0x44,
	GyroSensor_202x_YOUT_H	    = 0x45,
	GyroSensor_202x_YOUT_L	    = 0x46,
	GyroSensor_202x_ZOUT_H	    = 0x47,
	GyroSensor_202x_ZOUT_L	    = 0x48,
	GyroSensor_202x_USER_CTRL    = 0x6A,
    	/*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_202x_FIFO_RD_EN           0x40
        #define GYROSENSOR_202x_SPI_INTERFACE_EN     0x10
        #define GYROSENSOR_202x_RESET_FIFO           0x04
        #define GYROSENSOR_202x_RESET_SIGNAL         0x01
    	/*------------------------------------------------------------*/
	GyroSensor_202x_PWR_MGMT1    = 0x6B,
    	/*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_202x_RESET_DEVICE         0x80
        #define GYROSENSOR_202x_SLEEP_EN             0x40
        #define GYROSENSOR_202x_TEMP_SENSOR_DIS      0x08
        #define GYROSENSOR_202x_CLK_SEL_MASK         0x07
    	/*------------------------------------------------------------*/
	GyroSensor_202x_PWR_MGMT2    = 0x6C,
    	/*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_202x_STANDBY_XG           0x04
        #define GYROSENSOR_202x_STANDBY_YG           0x02
        #define GYROSENSOR_202x_STANDBY_ZG           0x01
    	/*------------------------------------------------------------*/
	GyroSensor_202x_FIFO_CNT_H   = 0x72,
	GyroSensor_202x_FIFO_CNT_L   = 0x73,
    	/*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_202x_FIFO_CNT_MASK        0x03FF
    	/*------------------------------------------------------------*/
	GyroSensor_202x_FIFO_RW		= 0x74,
	GyroSensor_202x_GET_ID 		= 0x75,
	GyroSensor_202x_INVALID
} GYROSENSOR_202x_REG;



//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _GYRO_DATA_CONFIG {
	float           x_offset;
	float           y_offset;
	int             x_shift;	    // 刮sensor的位移
	int             y_shift;
	int             enable;
	int             cnt;
	int             x_weight;	    // 角位移轉pixel的倍率
	int             y_weight;		
	float           old_speedX;
	float           old_speedY;
	float           new_speedX;
	float           new_speedY;
	float           temp_rate_x;	// 溫度每一度使x y的偏差量
	float           temp_rate_y;
} GYRO_DATA_CONFIG;

typedef struct gyro_info_s {
	unsigned int 	x_chan;
	unsigned int 	y_chan;
	int 			x_polar;
	int 			y_polar;

	unsigned int	adc_res;        // ADC resolution bits
	unsigned int	max_sense;
	unsigned int	min_sense;
	unsigned int 	max_bias;
	unsigned int 	min_bias;
	int 			phs_dly;
} gyro_info_t;

typedef struct gyro_param_s {
	int             Offset_x;
	int             Offset_y;
	int             Deadband_x;
	int             Deadband_y;
} gyro_param_t;

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

void GYRO_InitInterrupt(void);
void GYRO_EnableInterrupt(MMP_BOOL bEnable);
MMP_ERR GYRO_OpenTimer(void);
MMP_ERR GYRO_CloseTimer(void);


MMP_ERR Gyrosensor_WriteReg(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_UBYTE reg, MMP_UBYTE val);
MMP_ERR Gyrosensor_ReadReg(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_UBYTE reg, MMP_UBYTE* pval);
MMP_ERR Gyrosensor_SetRange(struct _3RD_PARTY_GYROSENSOR *pthis,MMP_UBYTE ubFullScaleRange);
MMP_ERR Gyrosensor_GetRange(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_UBYTE *ubDrange);
MMP_ERR Gyrosensor_Set_SampleRate_Div(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_UBYTE div);
MMP_ERR Gyrosensor_IOControl(struct _3RD_PARTY_GYROSENSOR *pthis, GYROSENSOR_ATTRIBUTE *pgyrosnr_attr, MMP_UBYTE cmd, MMP_UBYTE* arg);

void Gyrosensor_Enable(struct _3RD_PARTY_GYROSENSOR *pthis,int enable);
void Gyrosensor_SetWeight(struct _3RD_PARTY_GYROSENSOR *pthis,int x_weight, int y_weight);
void Gyrosensor_SetGyroOffset(struct _3RD_PARTY_GYROSENSOR *pthis,float offset_x, float offset_y);
void Gyrosensor_GetGyroShift(struct _3RD_PARTY_GYROSENSOR *pthis,int *Xout_shift, int *Yout_shift);
void Gyrosensor_SetGyroShift(struct _3RD_PARTY_GYROSENSOR *pthis,int Xout_shift, int Yout_shift);

MMP_ERR Gyrosensor_Initial(struct _3RD_PARTY_GYROSENSOR *pthis);
MMP_ERR Gyrosensor_ReadDeviceID(struct _3RD_PARTY_GYROSENSOR *pthis);
MMP_ERR Gyrosensor_ReadXY(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_SLONG *Xout, MMP_SLONG *Yout);
MMP_ERR Gyrosensor_ReadXYT(struct _3RD_PARTY_GYROSENSOR *pthis, MMP_SLONG *Xout, MMP_SLONG *Yout, MMP_SLONG *Tout);
void Gyrosensor_ReadOut_Temperature(struct _3RD_PARTY_GYROSENSOR *pthis,MMP_SHORT *usValue);
void Gyrosensor_ReadOut_ADCXoutYout(struct _3RD_PARTY_GYROSENSOR *pthis,MMP_SHORT *usXout, MMP_SHORT *usYout);
void Gyrosensor_ReadOut_ADCYoutZout(struct _3RD_PARTY_GYROSENSOR *pthis,MMP_SHORT *usYout, MMP_SHORT *usZout);
void Gyrosensor_ReadOut_ValueXoutYout(struct _3RD_PARTY_GYROSENSOR *pthis,float *fXout, float *fYout);
void Gyrosensor_ReadOut_ValueYoutZout(struct _3RD_PARTY_GYROSENSOR *pthis,float *fYout, float *fZout);
float Gyrosensor_CalArea(struct _3RD_PARTY_GYROSENSOR *pthis, float old_speed, float new_speed, float time_unit);

#endif //_GYROSENSOR_202X_H_
