//==============================================================================
//
//  File        : mmpf_sensor.h
//  Description : INCLUDE File for the Sensor Driver Function
//  Author      : Penguin Torng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_SENSOR_H_
#define _MMPF_SENSOR_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_err.h"
#include "mmpf_typedef.h"
#include "mmpf_vif.h"
#include "mmp_i2c_inc.h"
#include "mmp_snr_inc.h"


/** @addtogroup MMPF_Sensor
@{
*/

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MAX_SENSOR_RES_MODE     (28)
#define SENSOR_DELAY_REG        (0xFFFF)

#define MAX_SENSOR_BIN_TABLE    (5)

#ifndef SUPPORT_AUTO_FOCUS
#define SUPPORT_AUTO_FOCUS      (0)
#endif

#ifndef VR_MAX
#define VR_MAX(a,b)             (((a) > (b)) ? (a) : (b))
#endif

#ifndef VR_MIN
#define VR_MIN(a,b)             (((a) < (b)) ? (a) : (b))
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(ar)          (sizeof(ar)/sizeof((ar)[0]))
#endif

#define SENSOR_IF_PARALLEL      (0)
#define SENSOR_IF_MIPI_1_LANE   (1)
#define SENSOR_IF_MIPI_2_LANE   (2)
#define SENSOR_IF_MIPI_4_LANE   (3)

#define SENSOR_MIPI_DBG_EN      (0)
#define SENSOR_I2CM_DBG_EN      (0)

#ifndef MAX_INIT_ERR_CNT
#define MAX_INIT_ERR_CNT        (3)
#endif

#ifndef MAX_SET_RES_ERR_CNT
#define MAX_SET_RES_ERR_CNT     (20)
#endif

#define STATISTIC_AWB_ACC_SIZE  (8*4)

#define MMPF_ISP_MAX_QUEUE_SIZE (20)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

/* Sensor Parameter */
typedef enum _MMPF_SENSOR_PARAM
{
    MMPF_SENSOR_ISP_FRAME_COUNT = 0,
    MMPF_SENSOR_VIF_FRAME_COUNT,
    MMPF_SENSOR_CURRENT_PREVIEW_MODE,
    MMPF_SENSOR_CURRENT_CAPTURE_MODE,
    MMPF_SENSOR_PARAM_NUM
} MMPF_SENSOR_PARAM;

/* Sensor Rotate type */
typedef enum _MMPF_SENSOR_ROTATE_TYPE
{
    MMPF_SENSOR_ROTATE_NO_ROTATE        = 0,
    MMPF_SENSOR_ROTATE_RIGHT_90,
    MMPF_SENSOR_ROTATE_RIGHT_180,
    MMPF_SENSOR_ROTATE_RIGHT_270
} MMPF_SENSOR_ROTATE_TYPE;

/* Sensor Flip Mode */
typedef enum _MMPF_SENSOR_FLIP_TYPE
{
    MMPF_SENSOR_NO_FLIP = 0,
    MMPF_SENSOR_COLUMN_FLIP,
    MMPF_SENSOR_ROW_FLIP,
    MMPF_SENSOR_COLROW_FLIP
} MMPF_SENSOR_FLIP_TYPE;

/* Frame end Flag */
typedef enum _MMPF_SENSOR_FRAME_END_FLAG
{
    MMPF_SENSOR_FRAME_END_NONE          = 0,
    MMPF_SENSOR_ISP_FRAME_END           = 1,
    MMPF_SENSOR_VIF_FRAME_END           = 2
} MMPF_SENSOR_FRAME_END_FLAG;

/* ISP Mode */
typedef enum _MMPF_SENSOR_ISP_MODE
{
    MMPF_SENSOR_MODE_INIT               = 0,
    MMPF_SENSOR_PREVIEW                 = 1,
    MMPF_SENSOR_SNAPSHOT                = 2,
    MMPF_SENSOR_OTHERS                  = 3
} MMPF_SENSOR_ISP_MODE;

/* Fast Do 3A Mode */
typedef enum _MMPF_SENSOR_FAST_3A_OPERATION
{
    MMPF_SENSOR_FAST_3A_RESERVE_SETTING = 0,
    MMPF_SENSOR_FAST_3A_CHANGE_MODE,
    MMPF_SENSOR_FAST_3A_RESTORE_SETTING,
    MMPF_SENSOR_FAST_3A_CHANGE_ISP_SETTING
} MMPF_SENSOR_FAST_3A_OPERATION;

/* Statistic status */
typedef enum _MMPF_SENSOR_STATISTIC_STATE
{
    MMPF_SENSOR_STATISTIC_STATE_NONE    = 0,    // Nothing updated
    MMPF_SENSOR_STATISTIC_STATE_FETCH   = 1,    // Acc data are feteched
    MMPF_SENSOR_STATISTIC_STATE_PROC    = 2     // Statistic data is processed but not update the seneor setting yet
} MMPF_SENSOR_STATISTIC_STATE;

/* Sensor Event */
typedef enum _MMPF_SENSOR_EVENT {
    MMPF_SENSOR_EVENT_NONE = 0,
    MMPF_SENSOR_EVENT_TV_SRC_TYPE,
    MMPF_SENSOR_EVENT_TV_SRC_CHECK
} MMPF_SENSOR_EVENT;
/* YUV sensor data input order*/
typedef enum
{
    MMPF_SENSOR_YUV_ORDER_CY = 0,
    MMPF_SENSOR_YUV_ORDER_YC = 1,
} MMPF_SENSOR_YUV_ORDER; //sync with CUS_SENSOR_YUV_ORDER

typedef enum {
    ANA_CAM_1I1O = 0,
    ANA_CAM_2I1O,       //AHD dual 720P input.
    ANA_CAM_2I2O,       //AHD dual 1080P input, One input use as front cam, an other use as rear cam.
    ANA_CAM_NONE,
} ANA_CAM_TYPE;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

// Sensor event callback functions
typedef void (MMPF_SENSOR_EventCallback) (MMP_ULONG ulPara1, MMP_ULONG ulPara2);

typedef struct _MMPF_SENSOR_RESOLUTION {
    MMP_UBYTE   ubSensorModeNum;
    MMP_UBYTE   ubDefPreviewMode;
    MMP_UBYTE   ubDefCaptureMode;
    MMP_USHORT  usPixelSize;                        // Unit:nm
    MMP_USHORT  usVifGrabStX[MAX_SENSOR_RES_MODE];
    MMP_USHORT  usVifGrabStY[MAX_SENSOR_RES_MODE];
    MMP_USHORT  usVifGrabW[MAX_SENSOR_RES_MODE];
    MMP_USHORT  usVifGrabH[MAX_SENSOR_RES_MODE];
    #if (1)
    MMP_USHORT  usBayerInGrabX[MAX_SENSOR_RES_MODE];
    MMP_USHORT  usBayerInGrabY[MAX_SENSOR_RES_MODE];
    MMP_USHORT  usBayerInDummyX[MAX_SENSOR_RES_MODE];
    MMP_USHORT  usBayerInDummyY[MAX_SENSOR_RES_MODE];
    MMP_USHORT  usBayerOutW[MAX_SENSOR_RES_MODE];
    MMP_USHORT  usBayerOutH[MAX_SENSOR_RES_MODE];
    #endif
    MMP_USHORT  usScalInputW[MAX_SENSOR_RES_MODE];
    MMP_USHORT  usScalInputH[MAX_SENSOR_RES_MODE];
    MMP_USHORT  usTargetFpsx10[MAX_SENSOR_RES_MODE];
    MMP_USHORT  usVsyncLine[MAX_SENSOR_RES_MODE];
    MMP_UBYTE   ubWBinningN[MAX_SENSOR_RES_MODE]; // N/M pixels to 1 pixel in X direction.
    MMP_UBYTE   ubWBinningM[MAX_SENSOR_RES_MODE];
    MMP_UBYTE   ubHBinningN[MAX_SENSOR_RES_MODE]; // N/M pixels to 1 pixel in Y direction.
    MMP_UBYTE   ubHBinningM[MAX_SENSOR_RES_MODE];
    MMP_UBYTE   ubCustIQmode[MAX_SENSOR_RES_MODE];
    MMP_UBYTE   ubCustAEmode[MAX_SENSOR_RES_MODE];
} MMPF_SENSOR_RESOLUTION;

typedef struct _MMPF_SENSOR_OPR_TABLE {
    /* Initial Table */
    MMP_USHORT  usInitSize;
    MMP_USHORT* uspInitTable;
    /* Binary Table (Use I2cm DMA) */
    MMP_BOOL    bBinTableExist;
    MMP_USHORT  usBinTableNum;
    MMP_USHORT  usBinRegAddr[MAX_SENSOR_BIN_TABLE];
    MMP_USHORT  usBinSize[MAX_SENSOR_BIN_TABLE];
    MMP_UBYTE*  ubBinTable[MAX_SENSOR_BIN_TABLE];
    /* Initial Done Table */
    MMP_BOOL    bInitDoneTableExist;
    MMP_USHORT  usInitDoneSize;
    MMP_USHORT* uspInitDoneTable;
    /* Resolution Table */
    MMP_USHORT  usSize[MAX_SENSOR_RES_MODE];
    MMP_USHORT* uspTable[MAX_SENSOR_RES_MODE];
} MMPF_SENSOR_OPR_TABLE;

typedef struct _MMPF_SENSOR_AWBTIMIMG {
    MMP_UBYTE   ubPeriod;
    MMP_UBYTE   ubDoAWBFrmCnt;
    MMP_UBYTE   ubDoCaliFrmCnt;
} MMPF_SENSOR_AWBTIMIMG;

typedef struct _MMPF_SENSOR_AETIMIMG {
    MMP_UBYTE   ubPeriod;
    MMP_UBYTE   ubFrmStSetShutFrmCnt;
    MMP_UBYTE   ubFrmStSetGainFrmCnt;
} MMPF_SENSOR_AETIMIMG;

typedef struct _MMPF_SENSOR_AFTIMIMG {
    MMP_UBYTE   ubPeriod;
    MMP_UBYTE   ubDoAFFrmCnt;
} MMPF_SENSOR_AFTIMIMG;

typedef struct _MMPF_SENSOR_POWER_ON {
    MMP_BOOL    bTurnOnExtPower;
    MMP_USHORT  usExtPowerPin;
    MMP_BOOL    bExtPowerPinHigh;
    MMP_USHORT  usExtPowerPinDelay;

    MMP_BOOL    bFirstEnPinHigh;
    MMP_UBYTE   ubFirstEnPinDelay;      //Uint:ms
    MMP_BOOL    bNextEnPinHigh;
    MMP_UBYTE   ubNextEnPinDelay;       //Uint:ms
    MMP_BOOL    bTurnOnClockBeforeRst;
    MMP_BOOL    bFirstRstPinHigh;
    MMP_UBYTE   ubFirstRstPinDelay;     //Uint:ms
    MMP_BOOL    bNextRstPinHigh;
    MMP_UBYTE   ubNextRstPinDelay;      //Uint:ms
} MMPF_SENSOR_POWER_ON;

typedef struct _MMPF_SENSOR_POWER_OFF {
    MMP_BOOL    bEnterStandByMode;
    MMP_USHORT  usStandByModeReg;
    MMP_USHORT  usStandByModeMask;
    MMP_BOOL    bEnPinHigh;
    MMP_UBYTE   ubEnPinDelay;           //Uint:ms
    MMP_BOOL    bTurnOffMClock;
    MMP_BOOL    bTurnOffExtPower;
    MMP_USHORT  usExtPowerPin;
} MMPF_SENSOR_POWER_OFF;

typedef struct _MMPF_CUSTOM_COLOR_ID {
    MMP_BOOL                bUseCustomId;
    MMPF_VIF_COLOR_ID       Rot0d_Id[MAX_SENSOR_RES_MODE];
    MMPF_VIF_COLOR_ID       Rot90d_Id[MAX_SENSOR_RES_MODE];
    MMPF_VIF_COLOR_ID       Rot180d_Id[MAX_SENSOR_RES_MODE];
    MMPF_VIF_COLOR_ID       Rot270d_Id[MAX_SENSOR_RES_MODE];
    MMPF_VIF_COLOR_ID       H_Flip_Id[MAX_SENSOR_RES_MODE];
    MMPF_VIF_COLOR_ID       V_Flip_Id[MAX_SENSOR_RES_MODE];
    MMPF_VIF_COLOR_ID       HV_Flip_Id[MAX_SENSOR_RES_MODE];
} MMPF_CUSTOM_COLOR_ID;

typedef struct _MMPF_SENSOR_COLOR_ID {
    MMPF_VIF_COLOR_ID       VifColorId;
    MMPF_CUSTOM_COLOR_ID    CustomColorId;
} MMPF_SENSOR_COLOR_ID;

typedef struct _MMPF_SENSOR_VIF_SETTING {
    MMPF_VIF_SNR_TYPE       SnrType;
    MMPF_VIF_IF             OutInterface;
    MMPF_VIF_MDL_ID         VifPadId;
    MMPF_SENSOR_POWER_ON    powerOnSetting;
    MMPF_SENSOR_POWER_OFF   powerOffSetting;
    MMPF_VIF_MCLK_ATTR      clockAttr;
    MMPF_VIF_PARAL_ATTR     paralAttr;
    MMPF_MIPI_RX_ATTR       mipiAttr;
    MMPF_SENSOR_COLOR_ID    colorId;
    MMPF_MIPI_VC_ATTR       vcAttr;
    MMPF_VIF_YUV_ATTR       yuvAttr;
} MMPF_SENSOR_VIF_SETTING;

typedef struct _MMPF_SENSOR_STATISTIC_DATA_AE {
    MMPF_SENSOR_STATISTIC_STATE ulState;
    MMP_ULONG                   ulFrameCount;
    MMP_ULONG                   ulAcc;
    MMP_ULONG                   ulGain;
    MMP_ULONG                   ulShutter;
} MMPF_SENSOR_STATISTIC_DATA_AE;

typedef struct _MMPF_SENSOR_STATISTIC_DATA_AWB {
    MMPF_SENSOR_STATISTIC_STATE ulState;
    MMP_ULONG                   pulAcc[STATISTIC_AWB_ACC_SIZE];
    MMP_ULONG                   ulGainR;
    MMP_ULONG                   ulGainG;
    MMP_ULONG                   ulGainB;
    MMP_ULONG                   ulCaliIndex;
    MMP_ULONG                   ulCaliWeight;
} MMPF_SENSOR_STATISTIC_DATA_AWB;

typedef struct _MMPF_SENSOR_STATISTIC_DATA {
    MMPF_SENSOR_STATISTIC_DATA_AE   AE;
    MMPF_SENSOR_STATISTIC_DATA_AWB  AWB;
} MMPF_SENSOR_STATISTIC_DATA;

typedef struct _MMPF_SENSOR_CUSTOMER {

    void (*MMPF_Cust_InitConfig)(void);
    void (*MMPF_Cust_DoAEOperation_ST)(MMP_UBYTE ubSnrSel, MMP_ULONG ulFrameCnt);
    void (*MMPF_Cust_DoAEOperation_END)(MMP_UBYTE ubSnrSel, MMP_ULONG ulFrameCnt);
    void (*MMPF_Cust_DoAWBOperation_ST)(MMP_UBYTE ubSnrSel, MMP_ULONG ulFrameCnt);
    void (*MMPF_Cust_DoAWBOperation_END)(MMP_UBYTE ubSnrSel, MMP_ULONG ulFrameCnt);
    void (*MMPF_Cust_DoIQOperation)(MMP_UBYTE ubSnrSel, MMP_ULONG ulFrameCnt);
    void (*MMPF_Cust_SetGain)(MMP_UBYTE ubSnrSel, MMP_ULONG ulGain);
    void (*MMPF_Cust_SetShutter)(MMP_UBYTE ubSnrSel, MMP_ULONG ulShutter, MMP_ULONG ulVsync);
    void (*MMPF_Cust_SetExposure)(MMP_UBYTE ubSnrSel, MMP_ULONG ulGain, MMP_ULONG ulShutter, MMP_ULONG ulVsync);
    void (*MMPF_Cust_SetFlip)(MMP_UBYTE ubSnrSel, MMP_UBYTE ubMode);
    void (*MMPF_Cust_SetRotate)(MMP_UBYTE ubSnrSel, MMP_UBYTE ubMode);
    void (*MMPF_Cust_CheckVersion)(MMP_UBYTE ubSnrSel, MMP_ULONG *pulVersion);
    const MMP_UBYTE* (*MMPF_Cust_GetIqCompressData)(MMP_UBYTE ubSnrSel);
    void (*MMPF_Cust_StreamEnable)(MMP_UBYTE ubSnrSel, MMP_BOOL bEnable);

    MMPF_SENSOR_RESOLUTION*     ResTable;
    MMPF_SENSOR_OPR_TABLE*      OprTable;
    MMPF_SENSOR_VIF_SETTING*    VifSetting;
    MMP_I2CM_ATTR*              i2cmAttr;
    MMPF_SENSOR_AWBTIMIMG*      pAwbTime;
    MMPF_SENSOR_AETIMIMG*       pAeTime;
    MMPF_SENSOR_AFTIMIMG*       pAfTime;
    MMP_SNR_PRIO                sPriority;

    void (*MMPF_Cust_CheckSnrTVSrcType)(MMP_UBYTE ubSnrSel, MMP_SNR_ANADEC_SRC_TYPE *TVSrcType);
    void (*MMPF_Cust_GetSnrID)(MMP_UBYTE ubSnrSel, MMP_ULONG *SensorID);
    void (*MMPF_Cust_GetSnrOddEvenState)(MMP_UBYTE ubSnrSel, MMP_UBYTE  *State);
} MMPF_SENSOR_CUSTOMER;

typedef struct _MMPF_SENSOR_FUNCTIION
{
    // 0
    MMP_ERR (*MMPF_Sensor_Register)(MMP_UBYTE ubSnrSel, MMPF_SENSOR_CUSTOMER* pCust);
    MMP_ERR (*MMPF_Sensor_InitCustFunc)(MMP_UBYTE ubSnrSel);
    MMP_ERR (*MMPF_Sensor_Initialize)(MMP_UBYTE ubSnrSel);
    MMP_ERR (*MMPF_Sensor_InitializeVIF)(MMP_UBYTE ubSnrSel);
    MMP_ERR (*MMPF_Sensor_InitializeISP)(MMP_UBYTE ubSnrSel);

    // 5
    MMP_ERR (*MMPF_Sensor_PowerDown)(MMP_UBYTE ubSnrSel);
    MMP_ERR (*MMPF_Sensor_ChangeMode)(MMP_UBYTE ubSnrSel, MMP_USHORT usNewMode, MMP_USHORT usWaitFrames);
    MMP_ERR (*MMPF_Sensor_SetPreviewMode)(MMP_UBYTE ubSnrSel, MMP_USHORT usPreviewMode);
    MMP_ERR (*MMPF_Sensor_SetReg)(MMP_UBYTE ubSnrSel, MMP_USHORT usAddr, MMP_USHORT usData);
    MMP_ERR (*MMPF_Sensor_GetReg)(MMP_UBYTE ubSnrSel, MMP_USHORT usAddr, MMP_USHORT *usData);

    // 10
    MMP_ERR (*MMPF_Sensor_SetRegArray)(MMP_UBYTE ubSnrSel, const MMP_USHORT *pusArray, MMP_USHORT usSetCnt);
    MMP_ERR (*MMPF_Sensor_DoAWBOperation_ST)(MMP_UBYTE ubSnrSel);
    MMP_ERR (*MMPF_Sensor_DoAWBOperation_END)(MMP_UBYTE ubSnrSel);
    MMP_ERR (*MMPF_Sensor_DoAEOperation_ST)(MMP_UBYTE ubSnrSel);
    MMP_ERR (*MMPF_Sensor_DoAEOperation_END)(MMP_UBYTE ubSnrSel);

    // 15
    MMP_ERR (*MMPF_Sensor_DoAFOperation)(MMP_UBYTE ubSnrSel);
    MMP_ERR (*MMPF_Sensor_DoIQOperation)(MMP_UBYTE ubSnrSel);
    MMP_ERR (*MMPF_Sensor_SetExposureLimit)(MMP_ULONG ulBufaddr, MMP_ULONG ulDataTypeByByte, MMP_ULONG ulSize);
    MMP_ERR (*MMPF_Sensor_SetGain)(MMP_UBYTE ubSnrSel, MMP_ULONG ulGain);
    MMP_ERR (*MMPF_Sensor_SetShutter)(MMP_UBYTE ubSnrSel, MMP_ULONG ulShutter, MMP_ULONG ulVsync);

    // 20
    MMP_ERR (*MMPF_Sensor_SetExposure)(MMP_UBYTE ubSnrSel, MMP_ULONG ulGain, MMP_ULONG ulShutter, MMP_ULONG ulVsync);
    MMP_ERR (*MMPF_Sensor_SetSensorFlip)(MMP_UBYTE ubSnrSel, MMP_USHORT usMode, MMPF_SENSOR_FLIP_TYPE ubFlipType);
    MMP_ERR (*MMPF_Sensor_SetSensorRotate)(MMP_UBYTE ubSnrSel, MMP_USHORT usMode, MMPF_SENSOR_ROTATE_TYPE RotateType);
    MMP_USHORT (*MMPF_Sensor_GetRealFPS)(MMP_UBYTE ubSnrSel);
    MMP_UBYTE (*MMPF_Sensor_GetCurVifPad)(MMP_UBYTE ubSnrSel);

    // 25
    MMP_ERR (*MMPF_Sensor_GetScalInputRes)(MMP_UBYTE ubSnrSel, MMP_USHORT usResIdx,
                                           MMP_ULONG *ulWidth, MMP_ULONG *ulHeight);
    MMP_ERR (*MMPF_Sensor_GetBayerRes)(MMP_UBYTE ubSnrSel, MMP_USHORT usResIdx,
                                       MMP_ULONG *pulInWidth, MMP_ULONG *pulInHeight,
                                       MMP_ULONG *pulOutWidth, MMP_ULONG *pulOutHeight);
    MMP_ERR (*MMPF_Sensor_GetTargetFpsx10)(MMP_UBYTE ubSnrSel, MMP_USHORT usResIdx, MMP_ULONG *pulFpsx10);
    MMPF_SENSOR_RESOLUTION* (*MMPF_Sensor_GetResTable)(MMP_UBYTE ubSnrSel);
    MMPF_VIF_SNR_TYPE (*MMPF_Sensor_GetSnrType)(MMP_UBYTE ubSnrSel);

    // 30
    MMP_ERR (*MMPF_Sensor_FastDo3AOperation)(MMP_UBYTE ubSnrSel, MMPF_SENSOR_FAST_3A_OPERATION sOp);
    MMP_ERR (*MMPF_Sensor_LinkISPSelect)(MMP_UBYTE ubSnrSel, MMP_BOOL bLinkISP);
    MMP_ERR (*MMPF_Sensor_CheckSnrTVSrcType)(MMP_UBYTE ubSnrSel, MMP_SNR_ANADEC_SRC_TYPE *TVSrcType);
    MMP_ULONG (*MMPF_Sensor_GetSnrID)(MMP_UBYTE ubSnrSel);
    MMP_ERR (*MMPF_Sensor_GetSnrOddEvenState)(MMP_UBYTE ubSnrSel, MMP_UBYTE *State);

    // 35
    MMPF_SENSOR_FLIP_TYPE (*MMPF_Sensor_GetSensorFlip)(MMP_UBYTE ubSnrSel);
    MMPF_SENSOR_ROTATE_TYPE (*MMPF_SensorDrv_GetSensorRotate)(MMP_UBYTE ubSnrSel);
    const MMP_UBYTE* (*MMPF_Sensor_GetIqCompressData)(MMP_UBYTE ubSnrSel);
    MMP_ERR (*MMPF_Sensor_EnableStream)(MMP_UBYTE ubSnrSel, MMP_BOOL bEnable);
    MMPF_SENSOR_VIF_SETTING* (*MMPF_Sensor_GetVifSetting)(MMP_UBYTE ubSnrSel);

} MMPF_SENSOR_FUNCTION;

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

extern MMP_USHORT           gsSensorMode[];
extern MMPF_SENSOR_RESOLUTION m_SensorRes;
extern MMPF_SENSOR_FUNCTION *gsSensorFunction;
extern MMPF_SENSOR_CUSTOMER SensorCustFunc;
extern MMPF_SENSOR_CUSTOMER SubSensorCustFunc;
extern MMP_ULONG            gSnrLineCntPerSec[];
extern MMP_BOOL             m_bLinkISPSel[];

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

/* VIF Function */
void MMPF_VIF_CheckESD(void *ptmr, void *parg);

/* ISP Function */
void MMPF_ISP_ClosePreviewHandler(void);
void MMPF_ISP_DualSnrTrigRawFetch(void);

MMP_ERR MMPF_ISP_GetEV(MMP_LONG* plEv);
MMP_ERR MMPF_ISP_GetEVBias(MMP_LONG* plEvBias, MMP_ULONG* pulEvBiasBase);
MMP_ERR MMPF_ISP_GetShutter(MMP_ULONG* pulShutter);
MMP_ERR MMPF_ISP_GetShutterBase(MMP_ULONG* pulShutterBase);
MMP_ERR MMPF_ISP_GetGain(MMP_ULONG* pulGain);
MMP_ERR MMPF_ISP_GetGainBase(MMP_ULONG* pulGainBase);
MMP_ERR MMPF_ISP_GetGainDB(MMP_ULONG* pulGainDB);
MMP_ERR MMPF_ISP_GetExposureTime(MMP_ULONG ulchannel, MMP_ULONG* pulExpTime);
MMP_ERR MMPF_ISP_GetExposureInfo(MMP_ULONG* pulLVx10);
MMP_ERR MMPF_ISP_GetISOSpeed(MMP_ULONG* pulIso);
MMP_ERR MMPF_ISP_GetWBMode(MMP_UBYTE* pubMode);
MMP_ERR MMPF_ISP_GetColorTemp(MMP_ULONG* pulTemp);
MMP_ERR MMPF_ISP_Set3AFunction(MMP_ULONG ulchannel, MMP_ISP_3A_FUNC sFunc, int pParam);
MMP_ERR MMPF_ISP_SetIQFunction(MMP_ULONG ulchannel, MMP_ISP_IQ_FUNC sFunc, int pParam);
MMP_ERR MMPF_ISP_UpdateInputSize(MMP_USHORT usWidth, MMP_USHORT usHeight);
MMP_ERR MMPF_ISP_AllocateBuffer(MMP_ULONG ulStartAddr, MMP_ULONG *ulSize);
MMP_ERR MMPF_ISP_GetHWBufferSize(MMP_ULONG *ulSize);
MMP_ERR MMPF_ISP_EnableInterrupt(MMP_ULONG ulFlag, MMP_BOOL bEnable);
MMP_ERR MMPF_ISP_OpenInterrupt(MMP_BOOL bEnable);
MMP_BOOL MMPF_ISP_IsFrameEndStage(void);
MMP_ERR MMPF_ISP_ResetFrameEndSem(void);
MMP_ERR MMPF_ISP_GlobalInit(void);
MMP_ERR MMPF_ISP_GlobalUnInit(void);
MMP_ERR MMPF_ISP_SetPrmSnrChannel(MMP_ULONG ulindex, MMP_ULONG ulchannel);
MMP_ERR MMPF_ISP_GetPrmSnrChannel(MMP_ULONG ulindex, MMP_ULONG *pulchannel);
MMP_ERR MMPF_ISP_SetScdSnrChannel(MMP_ULONG ulindex, MMP_ULONG ulchannel);
MMP_ERR MMPF_ISP_GetScdSnrChannel(MMP_ULONG ulindex, MMP_ULONG *pulchannel);
MMP_ERR MMPF_ISP_GetSnrMapChannel(MMP_UBYTE ubSnrSel, MMP_ULONG ulindex, MMP_ULONG *pulchannel);
MMP_ERR MMPF_ISP_AllocatePrmSensorChannel(MMP_ULONG ulhdr_type);
MMP_ERR MMPF_ISP_AllocatePrmRAWStoreSensorChannel(void);
MMP_ERR MMPF_ISP_AllocateScdRAWStoreSensorChannel(MMP_ULONG ulhdr_type);

/* Sensor Function */
MMP_UBYTE MMPF_Sensor_GetVIFPad(MMP_UBYTE ubSnrSel);
MMP_ERR MMPF_Sensor_GetParam(MMP_UBYTE ubSnrSel, MMPF_SENSOR_PARAM param_type, void* param);
MMP_ERR MMPF_Sensor_SetParam(MMP_UBYTE ubSnrSel, MMPF_SENSOR_PARAM param_type, void* param);
MMP_ERR MMPF_Sensor_Set3AInterrupt(MMP_UBYTE ubSnrSel, MMP_BOOL bEnable);
MMP_ERR MMPF_Sensor_LinkFunctionTable(void);
MMP_ERR MMPF_Sensor_RegisterCallback(MMP_UBYTE ubEvent, void *pCallback);

void MMPF_Sensor_SetAnaDecSrcType(MMP_SNR_ANADEC_SRC_TYPE sSnrTVSrc);
void MMPF_Sensor_GetAnaDecSrcType(MMP_SNR_ANADEC_SRC_TYPE *peSrcType);
void MMPF_Sensor_CheckAnaDecSrcType(MMP_UBYTE ubSnrSel, MMP_SNR_ANADEC_SRC_TYPE *peSrcType);
void MMPF_Sensor_EnableAnaDecSrcTypeDetect(MMP_BOOL bEnable);
void MMPF_Sensor_SetDualBayerSensor(MMP_BOOL bEnable);
MMP_BOOL MMPF_Sensor_GetDualBayerSensor(void);
void MMPF_Sensor_GetNightModeInfo(MMP_ULONG ulchannel, MMP_LONG* plEnable, MMP_ULONG* pulMinFPS);
MMP_ERR MMPF_Sensor_GetSensorYuvOrder(MMP_UBYTE ubSnrSel, MMPF_SENSOR_YUV_ORDER *order);
MMP_ERR MMPF_Sensor_GetSensorI2CAddr(MMP_UBYTE ubSnrSel, MMP_UBYTE *ubI2CAddr);

extern MMP_ERR MMPF_SensorDrv_Register(MMP_UBYTE ubSnrSel, MMPF_SENSOR_CUSTOMER* pCust);

ANA_CAM_TYPE MMPF_GetANACamType(void);
void MMPF_SetANACamType(ANA_CAM_TYPE type);
void MMPF_SetRawStoreNum(MMP_BYTE bNum);
MMP_BYTE MMPF_GetRawStoreNum(void);
MMP_ERR MMPF_Sensor_SetMirrorFlip(MMP_UBYTE ubSnrSel, MMP_SNR_ORIT Orit);

#endif // _MMPF_SENSOR_H_

/// @}
