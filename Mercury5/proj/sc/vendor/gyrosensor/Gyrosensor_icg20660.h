
#ifndef _GYROSENSOR_ICG20660_H_
#define _GYROSENSOR_ICG20660_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmpf_gyrosensor.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

// MISC
#define ENABLE_GYRO_INT
//#define ENABLE_FSYNC
#define ENABLE_FIFO

// GPIO
#define CFG_GYRO_AD0_GPIO           (MMP_GPIO_MAX)
#define CFG_GYRO_INTR_GPIO          (MMP_GPIO116) // GS_INT 

#ifdef  CFG_GYRO_AD0_GPIO
#define GYRO_AD0_GPIO               (CFG_GYRO_AD0_GPIO)
#else
#define GYRO_AD0_GPIO               (MMP_GPIO19)
#endif

#ifdef CFG_GYRO_AD0_GPIO_LEVEL
#define GYRO_AD0_GPIO_LEVEL         (CFG_GYRO_AD0_GPIO_LEVEL)
#else
#define GYRO_AD0_GPIO_LEVEL         (GPIO_LOW)
#endif

#ifdef ENABLE_GYRO_INT
    #ifdef  CFG_GYRO_INTR_GPIO
    #define GYRO_INTR_GPIO          (CFG_GYRO_INTR_GPIO)
    #else
    #define GYRO_INTR_GPIO          (MMP_GPIO18)
    #endif
#else
    #define GYRO_INTR_GPIO          (MMP_GPIO_MAX)
#endif

#define GYRO_TIMER_ID               (MMPF_TIMER_3)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _GYROSENSOR_ICG20660_REG
{
    GSEN_ICG20660_SELF_TEST_X_GYRO = 0x00,
    GSEN_ICG20660_SELF_TEST_Y_GYRO = 0x01,
    GSEN_ICG20660_SELF_TEST_Z_GYRO = 0x02,

    GSEN_ICG20660_XG_OFFS_TC_H  = 0x04,
    GSEN_ICG20660_XG_OFFS_TC_L  = 0x05,
    GSEN_ICG20660_YG_OFFS_TC_H  = 0x06,
    GSEN_ICG20660_YG_OFFS_TC_L  = 0x07,
    GSEN_ICG20660_ZG_OFFS_TC_H  = 0x08,
    GSEN_ICG20660_ZG_OFFS_TC_L  = 0x09,
    GSEN_ICG20660_XG_OFFS_USRH  = 0x13,
    GSEN_ICG20660_XG_OFFS_USRL  = 0x14,
    GSEN_ICG20660_YG_OFFS_USRH  = 0x15,
    GSEN_ICG20660_YG_OFFS_USRL  = 0x16,
    GSEN_ICG20660_ZG_OFFS_USRH  = 0x17,
    GSEN_ICG20660_ZG_OFFS_USRL  = 0x18,
    GSEN_ICG20660_SMPLRT_DIV    = 0x19,
    GSEN_ICG20660_CONFIG        = 0x1A,
    GSEN_ICG20660_GYRO_CONFIG   = 0x1B,
        /*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_XG_SELF_TEST         0x80
        #define GYROSENSOR_YG_SELF_TEST         0x40
        #define GYROSENSOR_ZG_SELF_TEST         0x20

        #define GYROSENSOR_DYNAMIC_RANGE_125    0x00
        #define GYROSENSOR_DYNAMIC_RANGE_250    0x08
        #define GYROSENSOR_DYNAMIC_RANGE_500    0x10
        #define GYROSENSOR_DYNAMIC_RANGE_MASK   0x18
        /*------------------------------------------------------------*/
    GSEN_ICG20660_ACCEL_CONFIG  = 0x1C,
    GSEN_ICG20660_ACCEL_CONFIG2 = 0x1D,
    GSEN_ICG20660_FIFO_EN       = 0x23,
        /*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_ICG20660_TEMP_FIFO_EN         0x80
        #define GYROSENSOR_ICG20660_XG_FIFO_EN           0x40
        #define GYROSENSOR_ICG20660_YG_FIFO_EN           0x20
        #define GYROSENSOR_ICG20660_ZG_FIFO_EN           0x10
        #define GYROSENSOR_ICG20660_ALL_FIFO_DIS         0x00
        /*------------------------------------------------------------*/
    GSEN_ICG20660_FSYNC_INT_STATUS     = 0x36,
    GSEN_ICG20660_INT_PIN_CFG   = 0x37,
        /*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_ICG20660_INT_LEVEL_L          0x80
        #define GYROSENSOR_ICG20660_INT_LEVEL_H          0x00
        #define GYROSENSOR_ICG20660_INT_OPEN_DRAIN       0x40
        #define GYROSENSOR_ICG20660_INT_PUSH_PULL        0x00
        #define GYROSENSOR_ICG20660_LATCH_INT_EN         0x20
        #define GYROSENSOR_ICG20660_INT_READ_CLEAR       0x10
        #define GYROSENSOR_ICG20660_FSYNC_INT_LEVEL_L    0x08
        #define GYROSENSOR_ICG20660_FSYNC_INT_LEVEL_H    0x00
        #define GYROSENSOR_ICG20660_FSYNC_INT_MODE_EN    0x04
        /*------------------------------------------------------------*/
    GSEN_ICG20660_INT_ENABLE    = 0x38,
    GSEN_ICG20660_INT_STATUS    = 0x3A,
        /*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_ICG20660_INT_NONE             0x00
        #define GYROSENSOR_ICG20660_INT_FIFO_FULL        0x10
        #define GYROSENSOR_ICG20660_INT_DATA_READY       0x01
        /*------------------------------------------------------------*/
    GSEN_ICG20660_ACCEL_XOUT_H  = 0x3B,
    GSEN_ICG20660_ACCEL_XOUT_L  = 0x3C,
    GSEN_ICG20660_ACCEL_YOUT_H  = 0x3D,
    GSEN_ICG20660_ACCEL_YOUT_L  = 0x3E,
    GSEN_ICG20660_ACCEL_ZOUT_H  = 0x3F,
    GSEN_ICG20660_ACCEL_ZOUT_L  = 0x40,
    GSEN_ICG20660_TEMP_OUT_H    = 0x41,
    GSEN_ICG20660_TEMP_OUT_L    = 0x42,
    GSEN_ICG20660_GYRO_XOUT_H   = 0x43,
    GSEN_ICG20660_GYRO_XOUT_L   = 0x44,
    GSEN_ICG20660_GYRO_YOUT_H   = 0x45,
    GSEN_ICG20660_GYRO_YOUT_L   = 0x46,
    GSEN_ICG20660_GYRO_ZOUT_H   = 0x47,
    GSEN_ICG20660_GYRO_ZOUT_L   = 0x48,
    GSEN_ICG20660_SIGNAL_PATH_RESET = 0x68,
    GSEN_ICG20660_ACCEL_INTEL_CTRL  = 0x69,
    GSEN_ICG20660_USER_CTRL     = 0x6A,
        /*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_ICG20660_FIFO_RD_EN           0x40
        #define GYROSENSOR_ICG20660_SPI_INTERFACE_EN     0x10
        #define GYROSENSOR_ICG20660_RESET_FIFO           0x04
        /*------------------------------------------------------------*/
    GSEN_ICG20660_PWR_MGMT_1    = 0x6B,
    GSEN_ICG20660_PWR_MGMT_2    = 0x6C,
    GSEN_ICG20660_FIFO_COUNTH   = 0x72,
    GSEN_ICG20660_FIFO_COUNTL   = 0x73,
    GSEN_ICG20660_FIFO_R_W      = 0x74,
    GSEN_ICG20660_WHO_AM_I      = 0x75,
    GSEN_ICG20660_XA_OFFSET_H   = 0x77,
    GSEN_ICG20660_XA_OFFSET_L   = 0x78,
    GSEN_ICG20660_YA_OFFSET_H   = 0x7A,
    GSEN_ICG20660_YA_OFFSET_L   = 0x7B,
    GSEN_ICG20660_ZA_OFFSET_H   = 0x7D,
    GSEN_ICG20660_ZA_OFFSET_L   = 0x7E
} GYROSENSOR_ICG20660_REG;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _GYRO_DATA_CONFIG {
    float           x_offset;
    float           y_offset;
    int             x_shift;        // 刮sensor的位移
    int             y_shift;
    int             enable;
    int             cnt;
    int             x_weight;       // 角位移轉pixel的倍率
    int             y_weight;
    float           old_speedX;
    float           old_speedY;
    float           new_speedX;
    float           new_speedY;
    float           temp_rate_x;    // 溫度每一度使x y的偏差量
    float           temp_rate_y;
} GYRO_DATA_CONFIG;

typedef struct gyro_info_s {
    unsigned int    x_chan;
    unsigned int    y_chan;
    int             x_polar;
    int             y_polar;
    
    unsigned int    adc_res;        // ADC resolution bits
    unsigned int    max_sense;
    unsigned int    min_sense;
    unsigned int    max_bias;
    unsigned int    min_bias;
    int             phs_dly;
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

#endif // _GYROSENSOR_ICG20660_H_
