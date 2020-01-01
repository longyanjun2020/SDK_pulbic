#ifndef _MS_MDL_CAMERA_API_PUB_H_
#define _MS_MDL_CAMERA_API_PUB_H_

//#include "typedef.h"
#include "drv_SensorDriver_pub.h"
#include "drv_scl.h"
//#include "MML_Camera.h"
#include "srv_resmgr_mmlimage_types.h"
////UVC
typedef struct  _UVC_CONFIG
{
  u8                  tUVC_SensorSource;
  u16                 tUVC_Image_W;
  u16                 tUVC_Image_H;
  u32                 tUVC_RowBuffY0;
  u32                 tUVC_RowBuffC0;
  u32                 tUVC_RowBuffY1;
  u32                 tUVC_RowBuffC1;
  u32                 tUVC_OutputBuff;
  u16                 bXAxisMirrorEnable;      ///< Enable x-axis mirror
  u16                 bYAxisMirrorEnable;      ///< Enable y-axis mirror
  u8                  u8CaptureRingMode;
  u8                  u8CaptureRingNum;
  u8                  u8JPEGYUV420En;
} UVC_CONFIG_t;

// ic.hsu move
typedef enum
{
	CAMERA_SENSORBGT_0 = 0, // weakest
	CAMERA_SENSORBGT_1,
	CAMERA_SENSORBGT_2,
	CAMERA_SENSORBGT_3,
	CAMERA_SENSORBGT_4,
	CAMERA_SENSORBGT_5,
	CAMERA_SENSORBGT_6,
	CAMERA_SENSORBGT_7,
	CAMERA_SENSORBGT_8,
	CAMERA_SENSORBGT_9,
	CAMERA_SENSORBGT_10,
	CAMERA_SENSORBGT_END
} MmlCameraSensorBrightness_e;

typedef enum
{
	CAMERA_SENSORCONTRAST_0 = 0, // weakest
	CAMERA_SENSORCONTRAST_1,
	CAMERA_SENSORCONTRAST_2,
	CAMERA_SENSORCONTRAST_3,
	CAMERA_SENSORCONTRAST_4,
	CAMERA_SENSORCONTRAST_5,
	CAMERA_SENSORCONTRAST_6,
	CAMERA_SENSORCONTRAST_7,
	CAMERA_SENSORCONTRAST_8,
	CAMERA_SENSORCONTRAST_9,
	CAMERA_SENSORCONTRAST_10,
	CAMERA_SENSORCONTRAST_END
} MmlCameraSensorContrast_e;

//UVC
MmlCameraResult_e Cam_SetBrightness(MmlCameraSensorBrightness_e eBgtLevel, MmlCameraState_e eMML_CameraState);
MmlCameraResult_e Cam_SetContrast(MmlCameraSensorContrast_e eContrastLevel, MmlCameraState_e eMML_CameraState);
u32 Cam_Get_15FPS_VDR_Capability(MmlCameraRotationAngle_e eRotationAngle);


//menuload
typedef enum
{
	ML_Dummy_Init=0,//0
	ML_Pvw_buf0,   //1
	ML_Pvw_buf1,   //2
	ML_Pvw_buf2,   //3
	ML_Pvw_buf3,   //4
	ML_VideoChat_0, //5
	ML_VideoChat_1, //6
	ML_VideoChat_2, //7
	ML_VideoChat_3, //8
	ML_ATV_0,       //9
	ML_ATV_1,       //0xa
	ML_ATV_2,       //0xb
	ML_ATV_3,       //0xc
	ML_3G_VC_Encode_0,//0xd
	ML_3G_VC_Decode_0,//0xe
	ML_3G_VC_Display_0,//0xf
	ML_3G_VC_Encode_1,//0x10
	ML_3G_VC_Decode_1,//0x11
	ML_3G_VC_Display_1,//0x12
	ML_Disable     =0x20,//0x12
	ML_VideoRecPvw_0=0x101,
	ML_VideoRecScl_0=0x202,
	ML_VideoRecPvw_1=0x103,
	ML_VideoRecScl_1=0x204,
	ML_3G_VC_Decode_0_New=0x20e,
	ML_3G_VC_Decode_1_New=0x211,
	ML_SCLDisable=0x555,

} ML_BUF_DUMMY_REG_e;



////ATV

#ifdef __ATV_DRV__
#include "atv_drv_types.h"
#else
typedef struct
{
    u8             signalStrengthAvailable;
    u8             YC_ODER;
    u8             VSYNC_POLARITY;
    u8             HSYNC_POLARITY;
    u16              CropWidth;
    u16              CropHeight;
    u16              CropStartX;
    u16              CropStartY;
    u16            ATVSrc_Width;
    u16            ATVSrc_Height;
    u32            TVcrop_percentage;
    u8              frame_update_mode;
} AtvSpec_t;
#endif

MmlCameraResult_e Cam_Set_ATV_Power(u8 OnOff, MmlCameraStartPreview_t *pCam_PreSet,  AtvSpec_t *pAtvParaSet,  u8 buffopt);

///display
typedef struct  _PRE_DISPLAYINFO
{
	u16                         u16Disp_Pitch;
	u16                         u16Disp_X_Offset;
	u16                         u16Disp_Y_Offset;
	u16                         u16Disp_Width;
	u16                         u16Disp_Height;
	u16                         u16Disp_FullWidth;
	u16                         u16Disp_FullHeight;
	u32                         u32Disp_Addr[2];
	MmlCameraRotationAngle_e    eSLCRotationAngle;
    u16                         u16SensorFullW;
    u16                         u16SensorFullH;
} PRE_DISPLAYINFO_t;


void Cam_GetPrevDispParam(PRE_DISPLAYINFO_t *PARA);

////Capture
typedef void (*PfnSCLIrqCallBack)(void);
typedef struct  _CAPTURE_CONFIG
{
  u16   eDSTFormat;
  u16   tImage_W;
  u16   tImage_H;
  u32   tRowBuffY0;
  u32   tRowBuffC0;
  u32   tRowBuffY1;
  u32   tRowBuffC1;
  u32   tPanoramaBuf;
  u8    tEncodeFromBuf;
  u8    tEncodeFrameMode;
  u8    tSpecialEffectMode;
  u8    tSpecialCaptureRotate;
  u8    tEncodeRingMode;
  u8    tEncodeRingNum;
  u8	*pCaptureJpegBuffer;
  u8	tCaptureJpegQuality;
  MmlCameraImageEffect_e  eImageEffect;
  MmlImageCapturePanoramaParam_t tPanoramaParam;
  u8    u8JpgYUV420En;
  PfnSCLIrqCallBack PfnSCLCallBack;
} CAPTURE_CONFIG_t;

void Cam_CapturePreviewMenuload(u16 nBuff_idx);
void Cam_CaptureConfig(CAPTURE_CONFIG_t *ptCaptureConfig , u8 bWithFullSet);
void Cam_CaptureWaitVync(u16 u16FrameCount);

u32 Cam_GetJpegRealSize(CAPTURE_CONFIG_t *ptCaptureConfig);
SenDataFormat_e Cam_CaptureSensorFormat(u16 nWidth, u16 nHeight);


//////////video
//#define VDR_WITH_15FPS_SEN_METHOD3




typedef void (* CAM_SCL_DONE_IRQ_CALLBACK) (u16);

typedef struct
{
    SCLDST_FORMAT_e  eDSTFormat;
    u16 nVideoWidth ;
    u16 nVideoHeight ;
    u8  bRecMode;
    u8* nAddrY0;
    u8* nAddrC0;
    u8* nAddrY1;
    u8* nAddrC1;
} Mdl_VideoSCL_t;


void Cam_SclDone_CallbackAttach(CAM_SCL_DONE_IRQ_CALLBACK pCAM_SCL_DONE_IRQ_CALLBACK);
void Cam_SclDone_CallbackDisable(void);
typedef void (* CAM_DBUF_SCL_VBUF_BEGIN_CB)(u16);
typedef void (* CAM_DBUF_SCL_VBUF_END_CB)(u16);


#if defined(VDR_WITH_15FPS_DISP_2_REC)||defined(VDR_WITH_15FPS_REC_2_DISP)
  void Cam_DispBufSclToVBuf_Begin_CBAttach(CAM_DBUF_SCL_VBUF_BEGIN_CB nCallbackAdr);
  void Cam_DispBufSclToVBuf_Begin_CBDetach(void);
  void Cam_DispBufSclToVBuf_End_CBAttach(CAM_DBUF_SCL_VBUF_END_CB nCallbackAdr);
  void Cam_DispBufSclToVBuf_End_CBDetach(void);
#endif

MmlCameraResult_e Cam_SetSCL(u8 bOn , u8 bjpe_used);


///////////////////////////////////////////////////////////////////
//////////////for VT////////////////////////////////////////
#if defined(__VT_3G324M__)

void Cam_3G_VC_SclDone_CallbackAttach(CAM_SCL_DONE_IRQ_CALLBACK nCallbackAdr);
void Cam_3G_VC_SclDone_CallbackDisable(void);
MmlCameraResult_e Cam_3G_VC_ReloadEncBuffer( void );

typedef struct  _VT_DECODE_BUF_UPDATE
{
    u32 nDecode_SrcAddr[3];
    u16 nDecode_SrcPitch[3];
    u8  nDecode_SrcFormat;
    u8  nDecode_BuffIdx;

} VT_DECODE_BUF_UPDATE_t;
typedef struct  _VT_ENCODE_BUF_UPDATE
{
    u32 nAddrY0;
    u32 nAddrC0;
    u32 nAddrY1;
    u32 nAddrC1;
    u32 nEncWidth;
    u32 nEncHeight;
} VT_ENCODE_BUF_UPDATE_t;

typedef struct  _VT_DECODE
{
    u16 nDecode_SrcWidth ;
    u16 nDecode_SrcHeight ;
    SCLSRC_FORMAT_e nDecode_SrcFormat;
    u16 nDecode_SrcPitch[3];
    u32 nDecode_SrcAddr[3];
    u16 nDecode_DispWidth;
    u16 nDecode_DispHeight ;
    u16 nDecode_Disp_X_Offset ;
    u16 nDecode_Disp_Y_Offset ;
    u8  nDecode_Rotation;

} VT_DECODE_t;
typedef struct  _VT_ENCODE
{
    u16 nEncode_SrcWidth ;
    u16 nEncode_SrcHeight ;
    SCLSRC_FORMAT_e nEncode_SrcFormat;
    u16 nEncode_SrcPitch[3];
    u32 nEncode_SrcAddr[3];
    u16 nEncode_DstWidth ;
    u16 nEncode_DstHeight ;
    SCLDST_FORMAT_e  nEncode_DstFormat;
    u32 nEncode_DstAddr[3];
    u8  nEncode_Rotation;
   // u8  nEncode_MirrorFlip;

} VT_ENCODE_t;
typedef struct  _VT_Preview
{
    u16 nPreview_SrcWidth ;
    u16 nPreview_SrcHeight;
    SCLSRC_FORMAT_e nPreview_SrcFormat;
    u16 nPreview_SrcPitch[3];
    u32 nPreview_SrcAddr[3];
    u16 nPreview_DispWidth ;
    u16 nPreview_DispHeight ;
    u16 nPreview_Disp_X_Offset ;
    u16 nPreview_Disp_Y_Offset ;

    u8  nPreview_Rotation;

    //u8  nEncode_MirrorFlip;

} VT_Preview_t;
typedef enum
{
    VT_PrevBG=0,
    VT_DecodeBG,
    VT_NoBG,

}VT_DispBG_e;

typedef enum
{
    VT_MODE_BIG_PVW=0,
    VT_MODE_BIG_DEC,
    VT_MODE_ONLY_PVW,
    VT_MODE_ONLY_DEC,
}VT_Mode_e;

typedef enum
{
   VT_NOT_CHANGEMODE=0,
   VT_DO_CHANGEMODE,
}VT_ChangeMode_e;

typedef enum
{
 ZoomRatio_100=0,
 ZoomRatio_112,
 ZoomRatio_126,
 ZoomRatio_141,
 ZoomRatio_158,
 ZoomRatio_178,
 ZoomRatio_200,
 ZoomRatio_225,
 ZoomRatio_252,
 ZoomRatio_283,
 ZoomRatio_318,
 ZoomRatio_356,
 ZoomRatio_400,
}ZoomRatioIdx_e;

typedef enum
{
 VT_PicMode_On,
 VT_PicMode_Off,
}VT_PicMode_e;

typedef enum
{
 VT_Pvw_InScreen,
 VT_Pvw_OutScreen,
}VT_PvwPosition_e;


typedef struct  _VT_SETTING
{
    u32               VT_DispAddr[2];
    u8                VT_SensorSource;
    VT_DispBG_e       VT_Background ;
    u8                VT_SensorMirrorFlip;
    VT_Preview_t      tPrevieCfg;
    VT_ENCODE_t       tEncodeCfg;
    VT_DECODE_t       tDecodeCfg;
} VT_SETTING_t;



typedef struct _VT_PICMODE_CFG
{
    VT_PicMode_e      ePicModeOnOff;
    VT_DECODE_t       tDecodeCfg;

}VT_DEC_PICMODE_CFG_t;

typedef struct _VT_PVW_PICMODE_CFG
{
    VT_PicMode_e      ePicModeOnOff;
    VT_Preview_t      tPreviewCfg;

}VT_PVW_PICMODE_CFG_t;

typedef struct _VT_ENC_PICMODE_CFG
{
    VT_PicMode_e      ePicModeOnOff;
    VT_ENCODE_t       tEncodeCfg;

}VT_ENC_PICMODE_CFG_t;

typedef struct _VT_PVW_WIN_CFG
{
    u8 *nDstAddr;
    VT_PvwPosition_e ePvwPosition;
    u16 nPreview_Width ;
    u16 nPreview_Height ;
    u16 nPreview_Pitch;
}VT_PVW_WIN_CFG_t;

MmlCameraResult_e Cam_3G_VC_Set_Power(u8 OnOff,VT_SETTING_t *pVT_Setting);
u8 Cam_3G_VC_SetDecodeBuf2(void *u32VC_DecodeAddrY, void *u32VC_DecodeAddrU, void *u32VC_DecodeAddrV);
MmlCameraResult_e Cam_3G_VC_SetEncodeBuf(VT_ENCODE_BUF_UPDATE_t *pEncodeBuf);
MmlCameraResult_e Cam_3G_VC_Set15FPSDisplayBuf(VT_ENCODE_BUF_UPDATE_t *pDisplayBuf);

MmlCameraResult_e Cam_3G_VC_SwitchMode(VT_Mode_e eMode);
MmlCameraResult_e Cam_3G_VC_AdjSenContrast(u16 nLevel);
MmlCameraResult_e Cam_3G_VC_AdjSenBri(u16 nLevel);
u16 Cam_3G_VC_GeSenBri(void);
u16 Cam_3G_VC_GetSenContrast(void);
MmlCameraResult_e Cam_3G_VC_DigitalZoom(ZoomRatioIdx_e eZoomRatioIdx);
MmlCameraResult_e Cam_3G_VC_RemotePicMode(VT_DEC_PICMODE_CFG_t *pPicModeCfg);
MmlCameraResult_e Cam_3G_VC_LocalPicMode(VT_ENC_PICMODE_CFG_t *pEncPicModeCfg, VT_PVW_PICMODE_CFG_t *pPvwPicModeCfg);
MmlCameraResult_e Cam_3G_VC_PreviewWinPos(VT_PVW_WIN_CFG_t *pWinCfg);
MmlCameraResult_e Cam_3G_VC_SwitchSensor(int sensor_source, int win_rotation);


#endif

void Cam_PausePreview(u8);
u8 Cam_IsPausePreview(void);
MmlCameraResult_e Cam_AutoFocus(void);
u32 Cam_GetDispBufferSize(void);

#endif   //_MS_MDL_CAMERA_API_PUB_H_

