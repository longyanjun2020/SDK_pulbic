#ifndef LIBCAMERA_MDL_H
#define LIBCAMERA_MDL_H
//#include <vm_types.ht>
#include "libcamera.h"
#include <drv_ms_cus_sensor.h>

typedef enum
{
    MS_WDMA_ICP,
    MS_WDMA_SIF,
    MS_WDMA_ISP,
    MS_WDMA_ISPDS,
    MS_WDMA_ISPSWAPYC,
    MS_WDMA_VDOS,
    MS_WDMA_DEFAULT_SIF,
    MS_WDMA_DEFAULT_YC
} MS_WDMA_PATH;

typedef struct
{
    u32 width;
    u32 height;
    u32 x;
    u32 y;
    MS_WDMA_PATH wdma_path;
    u32 buf_addr;

}__attribute__((packed, aligned(1))) MS_WDMA_ATTR;

int cameraInit(void); //Global init
void cameraUnInit(void); //Global uninit
int cameraOpen(u32 nChannel);
int cameraClose(u32 nChannel);

int cameraI2CWrite(u32 nChannel, u16 usreg, u16 usval);
int cameraI2CRead(u32 nChannel, u16 usreg, u16* pusval);
int cameraPreviewRealtimeMode(u32 nChannel, bool enable);
int cameraPreviewRawStoreMode(u32 nChannel, bool enable);
int cameraPreviewRawFetchMode(u32 nChannel, bool enable);
int cameraPreviewLIHdrRawFetchMode(u32 nChannel, bool enable);
int cameraPreviewSetChannel(u32 nChannel, bool enable);
int cameraPreviewGetVideoResNum(u32 nChannel, u32 *ulres_unm);
int cameraPreviewGetVideoRes(u32 nChannel, u32 *ulwidth, u32 *ulheight);
int cameraPreviewSetVideoRes(u32 nChannel, u32 ulVideoRes);
int cameraPreviewGetSensorOutputRes(u32 nChannel, u32 *ulwidth, u32 *ulheight);
int cameraPreview(u32 nChannel, bool enable);
int cameraPreviewDualBayerSensor(u32 nChannel, bool enable);
int cameraSetRAWStoreMode(u32 nChannel, int width, int height, unsigned int raw_addr);
int cameraSetRAWStoreStartCallBack(unsigned int channel, void *pCallBack);
int cameraSetRAWStoreDoneCallBack(unsigned int channel, void *pCallBack);
int cameraSetRAWStoreLineCntCallBack(unsigned int channel, void *pCallBack);
int cameraUpdateRAWStoreAddress(u32 nChannel, unsigned int raw_addr);
int cameraUpdateRAWFetchAddress(u32 nChannel, unsigned int raw_addr);
int cameraWdmaSave(u32 nChannel, MS_WDMA_ATTR wdma_attr);
int cameraGetBT656SrcType(u32 nChannel, u32 *psrc_type);
int cameraGetFPS(u32 nChannel, u32 *pfps);
int cameraPreviewGetChannelHDRMode(u32 nChannel, bool *phdr_enable);
int cameraPreviewGetChannelCombinedHDRMode(u32 nChannel, bool *pcombinedhdr_en);
int cameraPreviewGetChannelRAWStoreMode(u32 nChannel, bool *praw_enable);
int cameraPreviewGetChannelRAWStoreFetchMode(u32 nChannel, bool *praw_enable);
int cameraPreviewGetChannelISPEn(u32 nChannel, bool *pIsp_enable);
int cameraPreviewGetChannelRAWStoreISPCalibrationMode(u32 nChannel, bool *praw_isp_cali_enable);
int cameraPreviewSetChannelActiveCnt(u32 nChannel, u32 nactive_cnt);
int cameraPreviewGetGainShutterDelay(u32 nChannel, u32 *pngain_delay, u32 *pnshutter_delay);
void cameraSensorRegister(void *psensor_map);
void cameraSensorUnRegister(void *psensor_map);
int cameraGetSensorYuvOrder(u32 nCameraID, CUS_SENSOR_YUV_ORDER *order);
int cameraGetSensorI2CAddr(u32 nCameraID, u8 *ubI2CAddr);
int cameraRdmaCalHdrLineOffset(u32 nChannel, u32 *pulOffsetperline);
int cameraGetHDRRingBufNum(u32 nChannel);
void cameraSetHDRRingBufNum(u32 nChannel, u32 ulNum);
int cameraSetRawBufNumbyDcgHDRmode(CUS_SENSOR_DCGHDR_MODE DcgHDR_mode);
int cameraSetMirrorFlip(u32 nChannel, CUS_CAMSENSOR_ORIT NewOrit);

#endif //#ifndef LIBCAMERA_MDL_H
