#ifndef DRV_SENSOR_IF_PUB_H__
#define DRV_SENSOR_IF_PUB_H__
#include "drv_ms_cus_sensor.h"

/*===========================================//
 //===========Sensor IF API=======================//
 //===========================================*/
#ifndef SUCCESS
#define FAIL        (-1)
#define SUCCESS     0
#endif

#ifdef __cplusplus
#define EXPORT_CUS  extern "C"
#else
#define EXPORT_CUS
#endif

typedef enum
{
    SENSORIF_SUCCESS = 0,
    SENSORIF_FAIL = -1,
    SENSORIF_CAMERA_LIST_ADD_FAIL = -2,
    SENSORIF_GET_SENSOR_HANDLE_FAIL = -3,
    SENSORIF_TABLE_ERROR = -4,
    SENSORIF_INIT_FAIL = -5,
    SENSORIF_SENSOR_SET_CFG_FAIL = -7,
    SENSORIF_POWER_ON_FAIL = -8,
    SENSORIF_SET_PATTERN_MODE_FAIL = -9,
    SENSORIF_GET_SENSOR_ID_FAIL = -10,
    SENSORIF_GET_SENSOR_CAP_FAIL = -11,
    SENSORIF_SET_FPS_FAIL = -12,
    SENSORIF_NOT_SUPPORT = -13,
    SENSORIF_SET_CSICLK_FAIL = -14,
} SensorIFErrorCode_e;

typedef struct SensorMapTable_t
{
    u32 ulisp_channel;
    int (*PfnInit)(struct __ms_cus_sensor*);
    int (*PfnDeInit)(struct __ms_cus_sensor*);
} SensorInitTable_t;

u32 _CameraIDGetSenHandleNumber(void);
s32 _CameraIDCheckHandle(u32 nCameraID);

/*------------------------------------------------*/
s32 DrvSensorIFInit(struct SensorMapTable_t ptTable[],u32 ulHandlerNum);

s32 DrvSensorIFDeInit(void);

s32 DrvSensorIFSensorPoweron(u32 nCameraID);

s32 DrvSensorIFSensorPoweroff(u32 nCameraID);

s32 DrvSensorIFSensorInit(u32 nCameraID);

s32 DrvSensorIFSensorRelease(u32 nCameraID);

s32 DrvSensorIFSensorSuspend(u32 nCameraID);

s32 DrvSensorIFSensorResume(u32 nCameraID);

s32 DrvSensorIFSetPatternMode(u32 nCameraID, u32 nMode);

s32 DrvSensorIFGetSensorID(u32 nCameraID, u32 *pnId);

s32 DrvSensorIFGetVideoResNum(u32 nCameraID, u32 *ulres_num);

s32 DrvSensorIFGetVideoRes(u32 nCameraID, cus_camsensor_res **pptRes);

s32 DrvSensorIFGetYuvOrder(u32 nCameraID, CUS_SENSOR_YUV_ORDER *order);

s32 DrvSensorIFGetI2CAddr(u32 nCameraID, u8 *u8I2CAddr);

s32 DrvSensorIFSetVideoRes(u32 nCameraID, u32 nResId);

s32 DrvSensorIFGetOrien(u32 nCameraID, CUS_CAMSENSOR_ORIT *peOri);

s32 DrvSensorIFSetOrien(u32 nCameraID, CUS_CAMSENSOR_ORIT eOri);

s32 DrvSensorIFGetSensorCap(u32 nCameraID, CUS_CAMSENSOR_CAP *ptCap);

/* AE*/
/* Unit : micro seconds*/
s32 DrvSensorIFAEStatusNotify(u32 nCameraID, CUS_CAMSENSOR_AE_STATUS_NOTIFY eStatus);

s32 DrvSensorIFGetAEUSecs(u32 nCameraID, u32 *pnUs);

s32 DrvSensorIFSetAEUSecs(u32 nCameraID, u32 nUs);

s32 DrvSensorIFGetAEGain(u32 nCameraID, u32* pnGain);

s32 DrvSensorIFSetAEGain(u32 nCameraID, u32 nGain);

s32 DrvSensorIFGetAEMinMaxUSecs(u32 nCameraID, u32 *pnMin, u32 *pnMax);

s32 DrvSensorIFGetAEMinMaxGain(u32 nCameraID, u32 *pnMin, u32 *pnMax);

s32 DrvSensorIFGetDGainRemainder(u32 nCameraID, u32 *DGainRemainder);

s32 DrvSensorIFGetFPS(u32 nCameraID);

s32 DrvSensorIFSetFPS(u32 nCameraID, u32 nFps);

/*[OPTIONAL] sensor calibration*/
s32 DrvSensorIFSetAEGainCal(u32 nCameraID, u32 nGain);

s32 DrvSensorIFsetCaliDataGainLinearity(u32 nCameraID, CUS_GAIN_GAP_ARRAY* ptArray, u32 nNum);

s32 DrvSensorIFGetShutterInfo(u32 nCameraID, CUS_SHUTTER_INFO *ptInfo);

s32 DrvSensorIFGetChannelMode(u32 nCameraID, CUS_SENSOR_CHANNEL_MODE *pch_mode);

s32 DrvSensorIFGetDataPrecision(u32 nCameraID, CUS_DATAPRECISION *pdata_prec);

s32 DrvSensorIFGetDataFormat(u32 nCameraID, CUS_SEN_INPUT_FORMAT *pdata_format);

s32 DrvSensorIFGetBT656SrcType(u32 nCameraID, CUS_SNR_ANADEC_SRC_TYPE *psrc_type);

s32 DrvSensorIFGetHDRMode(u32 nCameraID, CUS_HDR_MODE *phdr_mode);

s32 DrvSensorIFGetHDRVirtualChannelNum(u32 nCameraID, u32 *pulvc_num);

s32 DrvSensorIFSetChannelActiveCnt(u32 nCameraID, u32 nactive_cnt);

u32 DrvSensorIFGetChannelActiveCnt(u32 nCameraID);

s32 DrvSensorIFGetGainShutterDelay(u32 nCameraID, u32 *pngain_delay, u32 *pnshutter_delay);

/*----------------------------------------*/

int DrvSensorIFHWPowerOff(s32 nIdx, CUS_CLK_POL ePOL);

int DrvSensorIFHWReset(s32 nIdx, CUS_CLK_POL ePOL);

int DrvSensorIFHWMCLK(s32 ssensor_num, bool bONOFF, CUS_MCLK_FREQ eMclkSpeed);

int DrvSensorIFSWReset(u32 nCameraID, bool bONOFF);

int DrvSensorIFHWPCLK(CUS_SNR_PCLK ePclkSource);

int DrvSensorIFHWWaitVStart(s32 nMs);

int DrvSensorIFHWWaitVEnd(s32 nMs);

int DrvSensorIFHW3ATaskOrder(CUS_INT_TASK_ORDER eTasks);

int DrvSensorIFHWSetIOPad(u32 ulSnrPadNum, CUS_SENIF_BUS ulSnrType, u32 ulSnrPadCfg);

/*FOR CSI*/
int DrvSensorIFHWSetCSIClk(u16 usmipi_pad, CUS_CSI_CLK eClk, CUS_CLK_POL PclkPol);

int DrvSensorIFHWSetCSILane(u16 usmipi_pad, s32 nNumLan, u8 bon_off);

int DrvSensorIFHWSetCSILongPacketType(u64 nCtlFlag);

int DrvSensorIFHWSetCSIVC0HSmode(CUS_CSI_VC_HS_MODE eMode);

int DrvSensorIFHWSetCSIClkDataSkip(u8 nRxClkSkipNs, u8 nRxDataSkipNs);

void DrvSensorIFRDMASetChannelBayerID(u32 nCameraID);


#endif /*DRV_SENSOR_IF_PUB_H__*/

