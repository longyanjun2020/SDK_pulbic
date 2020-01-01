#ifndef _MS_MDL_CAMERA_API_H_
#define _MS_MDL_CAMERA_API_H_

//#include "typedef.h"
#include "drv_Scl.h"
#include "drv_SensorIF_pub.h"
#include "drv_disp.h"
//#include "Hal_disp.h"

#include "Drv_dynscl_pub.h"
//#include "Hal_dynscl.h"
#include "drv_Scl_color.h"
#include "drv_sensordriver_pub.h"

//#include "MML_Camera.h"
//#include "Mdl_Camera_main.h"
#include "Mdl_Camera_api_pub.h"
#include "Mdl_Camera_task_pub.h"
#include "Mdl_Camera_comm.h"
#include "Mdl_Camera_video.h"

//#include "drv_SensorDriver.h"



//#define MDL_CAM_TRC_NORM                           (_CUS1 | LEVEL_28)

/*
#define ENABLE_CAMMSG
#if defined(ENABLE_CAMMSG)
#define MDL_CAM_MSG   vm_dbgTrace
#else
#define MDL_CAM_MSG(fmt, args...)
#endif
*/
////////////////////////////
#ifndef __DISABLE_VDR__
#define _ENABLE_VDR_
#endif

typedef enum
{
	 CAM_NO_CALLBACK=0,
	 CAM_WITH_CALLBACK,
}CAM_CALLBACK_STATUS_e;

typedef enum
{
  eCAM_SOURCE_MAIN=0,
  eCAM_SOURCE_TV,
  eCAM_SOURCE_SUB,
  eCAM_SOURCE_SIZE,
}CAM_SENSOR_SOURCE_e;

typedef enum
{
  eCAM_POWER_OFF=0,
  eCAM_POWER_ON,
}CAM_POWER_e;

typedef enum
{
    MIDJPE_SPECIALEFFECT_NONE = 0,
    MIDJPE_SPECIALEFFECT_PANORAMA,         ///< Panorama
    MIDJPE_SPECIALEFFECT_LOMO_4LENS,       ///< LOMO 4 lens
    MIDJPE_SPECIALEFFECT_MIRROR,           ///< Mirror
    MIDJPE_SPECIALEFFECT_NUM
} MDLCapSpecialEffect_e;

typedef enum MdlCamStaId_e_
{
    MDL_CAMCPUSta_CAMERA_OPEN=0,
    MDL_CAMCPUSta_CAMERA_CLOSE,
    MDL_CAMCPUSta_START_PREVIEW_HEAD,
    MDL_CAMCPUSta_START_PREVIEW_TAIL,
    MDL_CAMCPUSta_STOP_PREVIEW,
    MDL_CAMCPUSta_GET_PREVIEW_FRAME,
}MdlCamStaId_e;

typedef enum
{
   CamBuf_0=0,
   CamBuf_1,
   CamBuf_2,
   CamBuf_3,
}CamBufId_e;

typedef struct _CAM_BUF_ADDR_
{
   u32 *pBuf;
   CamBufId_e eId;
}CAM_BUF_ADDR_t;

typedef struct  _CAMERAPARA
{
	u16     u16SclOutput_W;
	u16     u16SclOutput_H;

	u8      u8UVC;
	//Cam power on preset
	CAM_SENSOR_SOURCE_e     eSensorSource;           ///< Sensor source

	MmlCameraRotationAngle_e    eSLCRotationAngle;          ///< Rotation angle
	MmlCameraPreviewMode_e      ePreviewMode;            ///< Preview mode
	u16                         nSensorFlip;

	//display
	u16     u16Disp_X_Offset;
	u16     u16Disp_Y_Offset;
	u16     u16Disp_Width;
	u16     u16Disp_Height;
	u16     u16Disp_FullWidth;
	u16     u16Disp_FullHeight;
	u32     u32Disp_Addr[2];
	u32     u32Disp_FullAddr[2];
	u16     u16DefaultCropWidth;
	u16     u16DefaultCropHeight;

	u16     u16CropStartX;
	u16     u16CropStartY;
	u16     u16CropWidth;
	u16     u16CropHeight;

	//IP
	u32     u32SclBuffY0;
	u32     u32SclBuffC0;
	u32     u32SclBuffY1;
	u32     u32SclBuffC1;
	//Special Effect
	u32     u32PanoramaBuf;
	//function
	u8      u8SensorXYFlip;
	u8      u8AwbMode;
	u16     nZoomIdx;
	u16     nZoomRatio;
	// EV
	u8      u8EV_SensorStep;
	u8      u8EV_Status;
	u8      u8EV_Value;

	u8      u8EnvirCn;
	SEN_ANTI_FLICKER_e eAntiFlicker;

	u8      u8FrameRateTableSelect;
	u8      u8SensorReady;
	u8      u8AwbEnable;

	MmlCameraImageEffect_e      eImageEffect;
	MmlCameraImageEffect_e      ePreImageEffect;
	MmlImageCapturePanoramaParam_t tPanoramaParam;
    u8      u8SpecialCaptureRotate;

	u8      u8AEEnable;
	u8      u8AEMode;
	u8      u8DelayFrame;
	u8      u8Pwr_on_only;
	//JPEG
	u8      u8CaptureFromBuf;
	u8      u8CaptureFrameMode;
	u8      u8SpecialEffectMode;
    u8      u8CaptureRingMode;
    u8      u8CaptureRingNum;
    u8      u8JpgYUV420En;
}CAMERA_PARA;

#define EV_MIN_EV_Value	0
#define EV_MAX_EV_Value	40
#define EV_MIN_SENSOR_STEP  0
#define EV_MAX_SENSOR_STEP  14
#define EV_DEFAULT_SENSOR_STEP  7

enum EV_LEVEL
{
	EV_NOT_OUT_OF_LIMIT = 0,
	EV_BELOW_MIN = 1,
	EV_OVER_MAX = 2,
	EV_SET_DEFAULT_VALUE = 3,
};



typedef enum
{
   ML_NOT_COPY_TMPBUF,
   ML_DO_COPY_TMPBUF,
}ML_COPY_TMPBUF_STA_e;

typedef enum
{
  CAM_RECSTA_NOCHANGE,
  CAM_RECSTA_STOP,
}CAM_RECSTA_e;

typedef struct  _ML_DISP_t
{
	u32 *pnDispBuffAddr;
	u8  nDispFire;
} ML_DISP_t;


typedef struct  _IP_CONFIG_ML
{
	DrvSrif_CROPPara_t  tSIF_CROP;
	SIE_CTRL_t          tSIECtrl;
	SCL_CONFIG_t        tSclCfg;
	ML_DISP_t           tDispCfg;
	COLOR_INIT_t        tColorInit;
	u8                  bML_Crop;
	u8                  bML_SIE;
	u8                  bML_SCL;
	u8                  bML_Disp;
	u8                  bML_MACE_En;
	u8                  bML_IP_Rst;
} IP_CONFIG_ML;

typedef struct  _ML_BUFFER
{
	u32 *pnBufferAddr;
	u16 nBufferLength;
} ML_BUFFER;

typedef struct  _ML_SETTING
{
	DrvSrif_CROPPara_t  tSIF_CROP;
	SIE_CTRL_t tSIECtrl;
	SCL_CONFIG_t        tSclCfg;
	ML_DISP_t           tDispCfg;
	u8                  bML_Crop;
	u8                  bML_SIE;
	u8                  bML_SCL;
	u8                  bML_Disp;
	u32 *pnBufferAddr;
	u16 nBufferLength;
} tML_SETTING;
typedef struct  _ML_DyBUFF_UPDATE
{
	u32  ML_BufferAdd[4];
	u32  ML_TmpBufferAdd[4];
	u16  ML_Size[4];
	u16  ML_Buff_Idx;
	u8   ML_StartVDR;
} tML_DyBUFF_UPDATE;


enum
{
	NIGHT_MODE_ENABLE = 1,
};

enum
{
	_AF_ENABLE = 1,
};

/**
 *  @brief The enumeration defines the device camera.
 */
enum
{ // Need to sync "esl_cam_itf.h"
	CAM_ID_MAIN, /**< Main sensor / Primary sensor */
	CAM_ID_SUB,  /**< Sub sensor / Secondary sensor */
	CAM_ID_ATV,  /**< ATV device */
};


typedef enum
{
	STABLE_WAIT = 0,
	MOTION_DETECTION,
}eMOTION_STATE;


typedef struct  _MOTION_DETECT_PARA
{
	u16                         u16PreLuma;
	u8                          u8StableCount;
	eMOTION_STATE               eDetectState;
} MOTION_DETECT_PARA_t;

typedef enum MdlPvwDispBufOpt
{
	MDL_PVW_DISP_SUCCESS=0,
	MDL_PVW_DISP_FAIL,
} MdlPvwDispBufOpt_e;


typedef enum
{
	eSEN_W4StableCond_SENINIT = 0,
	eSEN_W4StableCond_PREVIEWML,
	eSEN_W4StableCond_VIDEOPREVIEWML,
	eSEN_W4StableCond_VIDEOCHATML,
	eSEN_W4StableCond_CAPML,
	eSEN_W4StableCond_SIEML,
	eSEN_W4StableCond_ATVPREVIEWML,
	eSEN_W4StableCond_UVC,
	eSEN_W4StableCond_END
} SEN_W4StableCond_e;

typedef enum
{
    ModulePwr_WithScl = 0,
    ModulePwr_NoScl,
}ModulePwr_Scl_e;

typedef enum
{
	Video_Pure = 0,
	Video_DigitalZoom,
}eVideoMode;


///////////////////////////////////////////////////////////////////
MmlCameraResult_e Cam_Set_ModulePower(u8 u8OnOff, ModulePwr_Scl_e eScl); // Add arg:"void" in order to avoid Warning:  #1295-D: Deprecated declaration Cam_Set_ModulePower - give arg types
void Cam_GetSensorDimension(u16* pWidth, u16* pHeight);
MmlCameraResult_e Cam_Set_MagicEye_MOD(u8 OnOff);
#ifndef __I_SW__
MmlCameraResult_e Cam_Set_Power(u8 OnOff);
#else
MmlCameraResult_e Cam_Set_Power(u8 Source,u8 OnOff);
#endif
MmlCameraResult_e ATV_ParaInit(MmlCameraStartPreview_t *pCam_PreSet,  AtvSpec_t *pAtvParaSet);
MmlCameraResult_e Cam_ParaInit(MmlCameraStartPreview_t *pCam_PreSet);
MmlCameraResult_e Cam_DispParaInit(MmlCameraStartPreview_t *pCam_PreSet);
void Cam_GetCaptureDimension(u16 *u16CaptureW ,u16 *u16CaptureH);
u16 Cam_SetMenuloadBuffer(ML_BUFFER *pML_Buff, IP_CONFIG_ML *pIP_Config);
void Cam_SetDigitalZoomPreview(void);
void Cam_SCLDisable(void);
MmlCameraResult_e ATV_PreviewMenuload(void);
void Cam_SetVideoChatParam(MmlCameraSetFrameBufferSize_t *PARA, u8 changesf);
MmlCameraResult_e Cam_PreviewMenuload(void);
MmlCameraResult_e Cam_SIEMenuload(u8 nSIEUpdate_Type,MmlCameraImageEffect_e nMML_SIE);
CAM_ZOOM_e Cam_ZoomRatioGet(u16 nZoomIdx);
void Cam_SetZoomIdx(u16 nZoomIdx);
CAM_ZOOM_e Cam_DigitalZoomPreview(u16 nZoomIdx);
#ifdef _ENABLE_VDR_
MmlCameraResult_e Cam_VideoMenuload(eVideoMode bVideoMode,u16 nZoomIdx);
#endif
u16 Cam_CheckDummyRegStatus(void);
void Cam_ZoomCaptureCrop(u16 u16ZoomRatio);
u16 Cam_GetEV(void);
MmlCameraResult_e Cam_SetEV(MmlCameraSetEV_t *pSetEV, MmlCameraState_e eMML_CameraState);
u16 Cam_GetEnvirCn(void);
MmlCameraResult_e Cam_SetEnvirCn(MmlCameraSetSceneMode_t *pSetEnvirCn, MmlCameraState_e eMML_CameraState);
SEN_ANTI_FLICKER_e Cam_GetAntiFlicker(void);
MmlCameraResult_e Cam_SetAntiFlicker(MmlCameraSetAntiFlicker_t *pSetAntiFlicker, MmlCameraState_e eMML_CameraState);
MmlCameraResult_e Cam_SetXYFlip(u8 u8Flip);
MmlCameraResult_e Cam_SetVideoPreview(u8 u8VideoPreview);
MmlCameraResult_e Cam_SetSensorReady(u8 u8SensorReady);
MmlCameraResult_e Cam_SetFrameRateTable(u8 u8FrameRateTable);
MmlCameraResult_e Cam_SetFrameRate(MmlCameraState_e eMML_CameraState);
MmlCameraResult_e Cam_SetAWBEnable(u8 u8AwbEnable);
MmlCameraResult_e Cam_SetAWBMode(u8 u8AwbMode);
MmlCameraResult_e Cam_SetNightMode(u16 bEnable, MmlCameraState_e eMML_CameraState);
MmlCameraResult_e Cam_SetAWB(MmlCameraSetWhiteBalance_t *pSetAWB, MmlCameraState_e eMML_CameraState);
MmlCameraResult_e Cam_SetImageEffect(MmlCameraSetImageEffect_t *pSetImageEffect, MmlCameraState_e eMML_CameraState);
MmlCameraResult_e Cam_SetExposure(MmlCameraSetExposure_t *pSetExposure, MmlCameraState_e eMML_CameraState);
MmlCameraResult_e Cam_GetCameraInfo(u16 u16SensorSource, MmlCameraCameraInfo_t *CameraInfo);
MmlCameraResult_e Cam_GetDigitalZoom(MmlCameraZoomStatus_t *DigitalZoom);
MmlCameraResult_e Cam_SetDigitalZoom(MmlCameraSetDigitalZoom_t *pSetDigitalZoom);
void Cam_SetPreSieStatus(MmlCameraImageEffect_e eSIE );
MmlCameraImageEffect_e Cam_GetPreSieStatus( void );
void Cam_SetSieStatus(MmlCameraImageEffect_e eSIE );
MmlCameraImageEffect_e Cam_GetSieStatus( void );
MmlCameraResult_e Cam_FixAAForPanorama(void);

#if defined(__MULTIPLE_SENSOR_TABLE_DETECTION__)
        #define _MEMORY_INSUFFICIENT_ (-1)
        #define _EMPTY_CUS_ (-2)
	u8 IsEmptySensorCUS(void);
	s32 Cam_Sensor_Detection(void);
	void Cam_SensorTbl_Release(void);
#endif
void Cam_Sensor_Para_Init(MmlCameraState_e eCameraState);
MmlCameraResult_e CAM_RECSTOP(void);
MmlCameraResult_e Cam_DispBufRelease(void);
MmlCameraResult_e Cam_DispBufAllocate(void);

u8 Cam_Motion_Detect(void);
MmlCameraResult_e Cam_Motion_Detect_Enable(MmlCameraSetMotionDetection_t *ptSetMotionDetection);
MmlCameraResult_e CAM_STOP_STEP1(SCL_UPDATE_TYPE_e  eUpdateType);
void Cam_DynamicUpdateML_Buffer(tML_DyBUFF_UPDATE *ptML_BufferUpdate);

void _MdlPvwDispBufOptSet(MdlPvwDispBufOpt_e eStatus);
MdlPvwDispBufOpt_e _MdlPvwDispBufOptGet(void);
void Cam_VideoSCLConfig(Mdl_CamTaskHSP_t  *ptCamTaskHSPl);
u32 VideoChatFrameHandle(u8 *pBuffer, u32 nBufferSize, u32 nDataSize);

void Cam_SclCallBackConfig(void);

MmlCameraResult_e Cam_Wait4Stable(u8 u8Cond);

MmlCameraResult_e MdlCam_Allocate_CamPara(void);
MmlCameraResult_e MdlCam_Release_CamPara(void);

////////////////test/////////////////////////////////

void CamDisplayConf_test(void);
void Cam_VideoMenuloadtest(void);
void Cam_GetMdlCamPara(CAMERA_PARA  *pCfg);

//u32 fn_Sensor_special_effect_bitmask(void);
#ifndef __SDK_SIMULATION__
u32 Cam_Specialeffect_Get(void);
#endif


void MdlCam_ShowOSTime(char *strmsg);
MmlCameraResult_e MdlCam_Sen_Init(u8 nUVC, u8 nWaitVsync);
MmlCameraResult_e Cam_Set_Power_UVC(UVC_CONFIG_t *pUVCConfig,u8 OnOff);
void MdlCam_Sen_SpecialEffect(u8 nMode, u8 nIsDelay);
void MdlCamVideoCfgGet(VS_VIDEO_CFG_t *pCfg);
void MdlCamBufAddrGet(CAM_BUF_ADDR_t *pBufAdr);



#endif   //_MS_MDL_CAMERA_API_H_

