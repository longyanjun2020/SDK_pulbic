#ifndef _MS_MDL_CAMERA_VIDEO_PUB_H_
#define _MS_MDL_CAMERA_VIDEO_PUB_H_

//================for video stablizer ================================
#include "drv_sensordriver_pub.h"


typedef enum
{
  Cam_VS_Success =0,
  Cam_VS_Failed,
  Cam_VS_W_NOT_VALID,
  Cam_VS_H_NOT_VALID,
}VideoStableErrCode_e;

typedef struct _VS_REAL_BUF_CFG_
{
  u16 nStartX1;
  u16 nStartY1;
  u16 nStartX3;
  u16 nStartY3;
  ML_BUF_DUMMY_REG_e eId;
}VS_REAL_BUF_CFG_t;

//video stabilizer
u16 MdlCamGetVSBufW(u16 nOriBufW);
u16 MdlCamGetVSBufH(u16 nOriBufH);
u16 MdlCamGetVSBufCmpPixelW(u16 nOriBufW);
u16 MdlCamGetVSBufCmpPixelH(u16 nOriBufH);
u16 MdlCamGetVSPreviewW(u16 nOriBufW);
u16 MdlCamGetVSPreviewH(u16 nOriBufH);
VideoStableErrCode_e MdlCamVSRealBufCfgGet(VS_REAL_BUF_CFG_t *pRealBufCfg);
VideoStableErrCode_e MdlCamVSRealBufCfgSave(VS_REAL_BUF_CFG_t *pRealBufCfg);
u16 MdlCamGetVSPvwCropPercent(void);
void MdlCamSetVSPvwCropPercent(u16 nPercent);

void MdlCamVSSetCapability(u32 eSensorSource);
u16  MdlCamVSIsSupported(void);
void MdlCamSetVSEnable(u8 bEnable);
void MdlCamVSReset(void);

#endif   //_MS_MDL_CAMERA_VIDEO_PUB_H_
