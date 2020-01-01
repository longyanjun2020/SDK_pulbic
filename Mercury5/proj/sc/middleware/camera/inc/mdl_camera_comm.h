#ifndef _MS_MDL_CAMERA_COMM_H_
#define _MS_MDL_CAMERA_COMM_H_


//#include "MML_Camera.h"
#include "sys_vm_dbg.ho"

#define ZOOM_IDX_MAX 12
#define ZOOM_IDX_MIN 0
#define MDL_CAM_TRC_NORM                           (_CUS1 | LEVEL_28)
#define ENABLE_CAMMSG
#if defined(ENABLE_CAMMSG)
#define MDL_CAM_MSG   vm_dbgTrace
#else
#define MDL_CAM_MSG(fmt, args...)
#endif


typedef enum
{
	NOT_OUT_OF_LIMIT = 0,
	OVER_LIMIT = 1,
	NO_CHANGE = 2,
	SET_DEFAULT_VALUE = 3,
	TIME_OUT = 0xff,
}CAM_ZOOM_e;

typedef enum
{
   ML_CAMCROP_DISABLE,
   ML_CAMCROP_EN,
}ML_CamCropOnOff_e;

typedef enum
{
   ML_SIFCROP_DISABLE,
   ML_SIFCROP_EN,
}ML_SifCropOnOff_e;


typedef enum
{
   ML_CROP_DISABLE,
   ML_CROP_EN,
}ML_CropOnOff;

typedef struct  _CAM_SENCROP
{
	u16     nCropStartX;
	u16     nCropStartY;
	u16     nCropWidth;
	u16     nCropHeight;
}Cam_SifCrop_t;

/*
typedef struct _CAM_DISPPARA
{
	u16     nDisp_Pitch;
	u16     nDisp_X_Offset;
	u16     nDisp_Y_Offset;
	u16     nDisp_Width;
	u16     nDisp_Height;
	u16     nDisp_FullWidth;
	u16     nDisp_FullHeight;
	u32     nDisp_Addr[2];
	u32     nDisp_FullAddr[2];
}Cam_DispPara_t;*/

typedef struct _CAM_PVWIMGSIZE
{
	u16     nImgPvwW;
	u16     nImgPvwH;
}Cam_PvwImgSize_t;

typedef struct _CAM_FULLIMGSIZE
{
	u16     nImgFullW;
	u16     nImgFullH;
}Cam_FullImgSize_t;

typedef struct _CAM_DFTCROP
{
	u16     nDefaultCropWidth;
	u16     nDefaultCropHeight;
}Cam_DftCrop_t;

typedef struct  _CAM_ZOOMCFG
{
    Cam_SifCrop_t tSifCrop;
    Cam_DftCrop_t tDftCrop;
	u16     nZoomIdx;
	u16     nZoomRatio;
}Cam_ZoomCfg_t;

/*typedef struct _CAM_SCLOUTSIZE
{
	u16     nSclOutSizeW;
	u16     nSclOutSizeH;
}Cam_SclOutSize_t;*/

/*typedef struct _CAM_SCLOUTBUFADDR
{
	u32     nSclBuffY0;
	u32     nSclBuffC0;
	u32     nSclBuffY1;
	u32     nSclBuffC1;
}Cam_SclOutBufAddr_t;*/




void MdlCamSifCropCfg(void);
CAM_ZOOM_e MdlCamZoomRatioGet(u16 nZoomIdx);
void MdlCamCropParaGet(Cam_SifCrop_t *pCfg);
void MdlCamCropParaSet(Cam_SifCrop_t *pCfg);
void MdlCamDftCropGet(Cam_DftCrop_t *pCfg );
void MdlCamDftCropSet(Cam_DftCrop_t *pCfg );
void MdlCamZoomCfgGet(Cam_ZoomCfg_t * pCfg);
void MdlCamZoomCfgSet(Cam_ZoomCfg_t * pCfg);
void MdlCamPvwImgSizeGet(Cam_PvwImgSize_t *pCfg );
void MdlCamPvwImgSizeSet(Cam_PvwImgSize_t *pCfg );
void MdlCamFullImgSizeGet(Cam_FullImgSize_t *pCfg );
void MdlCamFullImgSizeSet(Cam_FullImgSize_t *pCfg );
void MdlCam_Comm_para_Release(void);
u8 MdlCam_Comm_para_alloc(void);



#endif   //_MS_MDL_CAMERA_COMM_H_

