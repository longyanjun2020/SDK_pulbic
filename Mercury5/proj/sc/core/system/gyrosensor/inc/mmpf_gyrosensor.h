//==============================================================================
//
//  File        : mmpf_gyrosensor.h
//  Description : INCLUDE File for the gyrosensor Driver Function
//  Author      : Andy Liu
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_GYROSENSOR_H_
#define _MMPF_GYROSENSOR_H_

#include "lib_retina.h"
#include "mmpf_typedef.h"

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================


/** @addtogroup MMPF_gyrosensor
@{
*/

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _GYROSENSOR_DATA
{
	MMP_UBYTE 	acc_val[3];	//X,Y,Z axis acceleration value
} GYROSENSOR_DATA;

typedef struct  _GYROSENSOR_ATTRIBUTE
{
    MMP_UBYTE ubStoreFreq;
    MMP_UBYTE ubRange;
    MMP_UBYTE ubSensitive;
    MMP_UBYTE ubGroundAxis;
    MMP_UBYTE ub1G;
    MMP_UBYTE ub1G_Err;
    int		  nMaxG;
    int		  nInited;
    MMP_UBYTE ubGyrosensorID;    // CarDV: Move ubGyrosensorID to tail of GYROSNR_ATTRIBUTE to be compatible with GVP player
} GYROSENSOR_ATTRIBUTE, *PGYROSENSOR_ATTRIBUTE;

#if 0
typedef enum _GYROSENSOR_REG
{
    GyroSensor_FIFO_EN,
        /*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_TEMP_FIFO_EN         0x80
        #define GYROSENSOR_XG_FIFO_EN           0x40
        #define GYROSENSOR_YG_FIFO_EN           0x20
        #define GYROSENSOR_ZG_FIFO_EN           0x10
        #define GYROSENSOR_ALL_FIFO_DIS         0x00
        /*------------------------------------------------------------*/

    GyroSensor_INT_EN,
    GyroSensor_INT_STS,
        /*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_INT_NONE             0x00
        #define GYROSENSOR_INT_FIFO_FULL        0x10
        #define GYROSENSOR_INT_FSYNC            0x08
        #define GYROSENSOR_INT_DATA_READY       0x01
        /*------------------------------------------------------------*/

    GyroSensor_INT_CFG      
    /*-DEFINE-----------------------------------------------------*/
        #define GYROSENSOR_INT_LEVEL_L          0x80
        #define GYROSENSOR_INT_LEVEL_H          0x00
        #define GYROSENSOR_INT_OPEN_DRAIN       0x40
        #define GYROSENSOR_INT_PUSH_PULL        0x00
        #define GYROSENSOR_LATCH_INT_EN         0x20
        #define GYROSENSOR_INT_READ_CLEAR       0x10
        #define GYROSENSOR_FSYNC_INT_LEVEL_L    0x08
        #define GYROSENSOR_FSYNC_INT_LEVEL_H    0x00
        #define GYROSENSOR_FSYNC_INT_MODE_EN    0x04
    /*------------------------------------------------------------*/

//        GyroSensor_TOUT_H       ,
//        GyroSensor_TOUT_L      ,
//        GyroSensor_XOUT_H       ,
//        GyroSensor_XOUT_L      ,
//        GyroSensor_YOUT_H      ,
//        GyroSensor_YOUT_L      ,
//        GyroSensor_ZOUT_H       ,
//        GyroSensor_ZOUT_L      ,
//
//    GyroSensor_SMPLRT_DIV   ,
//        /*-DEFINE-----------------------------------------------------*/
//        #define GYROSENSOR_SAMP_RATE_DIV_MASK   0xFF
        /*------------------------------------------------------------*/
//    GyroSensor_CONFIG_0      ,
//        /*-DEFINE-----------------------------------------------------*/
//        #define GYROSENSOR_FIFO_FULL_STOP       0x40
//        #define GYROSENSOR_FIFO_FULL_OVERWRITE  0x00
//        #define GYROSENSOR_EXT_SYNC_MASK        0x38
//        #define GYROSENSOR_DLPF_CFG_MASK        0x07
//        /*------------------------------------------------------------*/
//    GyroSensor_CONFIG_1      ,
//        /*-DEFINE-----------------------------------------------------*/
//        #define GYROSENSOR_XG_SELF_TEST         0x80
//        #define GYROSENSOR_YG_SELF_TEST         0x40
//        #define GYROSENSOR_ZG_SELF_TEST         0x20
//
//        #define GYROSENSOR_DYNAMIC_RANGE_31d25  0x00
//        #define GYROSENSOR_DYNAMIC_RANGE_62d5   0x08
//        #define GYROSENSOR_DYNAMIC_RANGE_125    0x10
//        #define GYROSENSOR_DYNAMIC_RANGE_250    0x18
//        #define GYROSENSOR_DYNAMIC_RANGE_MASK   0x18
//
//        #define GYROSENSOR_FCHOICE_B_MASK       0x03
//        /*------------------------------------------------------------*/
//
//

//    GyroSensor_USER_CTRL   ,
//        /*-DEFINE-----------------------------------------------------*/
//        #define GYROSENSOR_FIFO_RD_EN           0x40
//        #define GYROSENSOR_SPI_INTERFACE_EN     0x10
//        #define GYROSENSOR_RESET_FIFO           0x04
//        #define GYROSENSOR_RESET_SIGNAL         0x01
//        /*------------------------------------------------------------*/
//    GyroSensor_PWR_MGMT1    ,
//        /*-DEFINE-----------------------------------------------------*/
//        #define GYROSENSOR_RESET_DEVICE         0x80
//        #define GYROSENSOR_SLEEP_EN             0x40
//        #define GYROSENSOR_TEMP_SENSOR_DIS      0x08
//        #define GYROSENSOR_CLK_SEL_MASK         0x07
//        /*------------------------------------------------------------*/
//    GyroSensor_PWR_MGMT2    ,
//        /*-DEFINE-----------------------------------------------------*/
//        #define GYROSENSOR_STANDBY_XG           0x04
//        #define GYROSENSOR_STANDBY_YG           0x02
//        #define GYROSENSOR_STANDBY_ZG           0x01
//        /*------------------------------------------------------------*/
//    GyroSensor_FIFO_CNT_H   ,
//    GyroSensor_FIFO_CNT_L   ,
//        /*-DEFINE-----------------------------------------------------*/
//        #define GYROSENSOR_FIFO_CNT_MASK        0x03FF
//        /*------------------------------------------------------------*/
//    GyroSensor_FIFO_RW      ,
//    GyroSensor_GET_ID       ,
//    GyroSensor_INVALID
} GYROSENSOR_REG;
#endif
typedef enum _GYROSENSOR_DYNA_RANGE
{
    GYROSENSOR_DYNA_RANGE_31d25 = 0,
    GYROSENSOR_DYNA_RANGE_62d5,
    GYROSENSOR_DYNA_RANGE_125,
    GYROSENSOR_DYNA_RANGE_250,
    GYROSENSOR_DYNA_RANGE_500,
    GYROSENSOR_DYNA_RANGE_NUM
} GYROSENSOR_DYNA_RANGE;

typedef enum _GYRO_LOG_TYPE
{
    GYRO_LOG_NONE = 0,
    GYRO_LOG_VIDEO,
    GYRO_LOG_CALIB,
    GYRO_LOG_TEST
} GYRO_LOG_TYPE;

typedef enum _GYRO_AXIS
{
    GYRO_X_AXIS = 0,
    GYRO_Y_AXIS,
    GYRO_Z_AXIS
} GYRO_AXIS;

typedef enum _GYRO_POLAR
{
    GYRO_NEGATIVE = -1,
    GYRO_POSITIVE = 1
} GYRO_POLAR;

typedef struct _3RD_PARTY_GYROSENSOR 
{
    //0
    MMP_ERR (*MMPF_Gyrosensor_Initialize)(struct _3RD_PARTY_GYROSENSOR *);
    MMP_ERR (*MMPF_Gyrosensor_SetReg)(struct _3RD_PARTY_GYROSENSOR *, MMP_UBYTE usAddr, MMP_UBYTE usData);
    MMP_ERR (*MMPF_Gyrosensor_GetReg)(struct _3RD_PARTY_GYROSENSOR *, MMP_UBYTE usAddr, MMP_UBYTE *usData);
    MMP_ERR (*MMPF_Gyrosensor_ReadXY)(struct _3RD_PARTY_GYROSENSOR *, MMP_SLONG *Xout, MMP_SLONG *Yout);
    MMP_ERR (*MMPF_Gyrosensor_ReadXYT)(struct _3RD_PARTY_GYROSENSOR *, MMP_SLONG *Xout, MMP_SLONG *Yout, MMP_SLONG *Tout);

    //5
    MMP_ERR (*MMPF_Gyrosensor_GetRange)(struct _3RD_PARTY_GYROSENSOR *, MMP_UBYTE *ubDrange);
    MMP_ERR (*MMPF_Gyrosensor_SetRange)(struct _3RD_PARTY_GYROSENSOR *, MMP_UBYTE ubDrange);
    MMP_ERR (*MMPF_Gyrosensor_Set_SampleRate_Div)(struct _3RD_PARTY_GYROSENSOR *, MMP_UBYTE div);
    MMP_ERR (*MMPF_Gyrosensor_IOControl)(struct _3RD_PARTY_GYROSENSOR *, GYROSENSOR_ATTRIBUTE * attr, MMP_UBYTE cmd, MMP_UBYTE* arg);
    MMP_BOOL (*MMPF_Gyrosensor_ModuleAttached)(struct _3RD_PARTY_GYROSENSOR *pthis);

} THIRD_PARTY_GYROSENSOR;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ERR MMPF_3RDParty_Gyrosensor_Initial(void);
MMP_ERR MMPF_3RDParty_Gyrosensor_ReadRegister(MMP_UBYTE reg , MMP_UBYTE* pval);
MMP_ERR MMPF_3RDParty_Gyrosensor_WriteRegister(MMP_UBYTE reg , MMP_UBYTE val);
MMP_ERR MMPF_3RDParty_Gyrosensor_ReadXY(MMP_SLONG *Xout, MMP_SLONG *Yout);
MMP_ERR MMPF_3RDParty_Gyrosensor_ReadXYT(MMP_SLONG *Xout, MMP_SLONG *Yout, MMP_SLONG *Tout);
MMP_ERR MMPF_3RDParty_Gyrosensor_GetRange(MMP_UBYTE *ubDrange);
MMP_ERR MMPF_3RDParty_Gyrosensor_SetRange(MMP_UBYTE ubDrange);
MMP_ERR MMPF_3RDParty_Gyrosensor_Set_SampleRate_Div(MMP_UBYTE div);
MMP_ERR MMPF_3RDParty_Gyrosensor_IOControl(MMP_UBYTE cmd, MMP_UBYTE* arg);
MMP_BOOL MMPF_3RDParty_Gyrosensor_Attached(void);
void MMPF_3RDParty_Gyrosensor_Register(struct _3RD_PARTY_GYROSENSOR *pdev_obj);
void MMPF_3RDParty_Gyrosensor_Unregister(void);
void MMPF_3RDParty_Gyrosensor_initiated(MMP_BOOL *bgsnr_inited);
GYROSENSOR_ATTRIBUTE *MMPF_3RDParty_Gyrosensor_GetAttribute(void);

#endif // _MMPF_GYROSENSOR_H_

/// @}
