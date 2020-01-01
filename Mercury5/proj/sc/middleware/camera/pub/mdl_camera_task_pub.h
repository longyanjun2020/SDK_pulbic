#ifndef _MS_MDL_CAMERA_TASK_PUB_H_
#define _MS_MDL_CAMERA_TASK_PUB_H_

#ifndef __SDK_SIMULATION__

//#include "typedef.h"
//#include "MML_Camera.h"
#include "Vm_msgof.hc"
#include "mdl_camera_msg_enum.h"
#include "Mdl_Camera_api_pub.h"
#include "srv_resmgr_mmlcamera_types.h"

typedef enum MdlCameraCmd
{
	MDL_CMD_CAMERA_CLOSE,
	MDL_CMD_CAMERA_ON,
	MDL_CMD_CAMERA_SETTING,
	MDL_CMD_CAMERA_DIGITAL_ZOOM,
	MDL_CMD_CAMERA_RECORD,
	MDL_CMD_CAMERA_RECSTOP,
	MDL_CMD_CAMERA_OFF,
	MDL_CMD_CAMERA_SENSOR_DETECT,
	MDL_CMD_CAMERA_MOTION_DETECT,
	MDL_CMD_CAMERA_MOTION_DETECT_TIMER,

	MDL_CAM_MBOX_NONE        = 0xFFFEUL,
	MDL_CAM_MBOX_TIMEOUT     = 0xFFFFUL,
} MdlCameraCmd_e;

typedef enum MdlERROR_CODE
{
	MDL_CAM_SUCCESS=0,
	MDL_CAM_REJECT,
	MDL_CAM_IGNORE,
	MDL_CAM_ERROR,

} MdlCameraErrCode_e;

// define how the menu-load style is
#define MDL_CAM_MODE_PRV_REC           0
#define MDL_CAM_MODE_DISP_2_REC     1
#define MDL_CAM_MODE_REC_2_DISP     2

typedef struct
{
    u32  Msg;
	u16  eDSTFormat;
	u16 nVideoWidth ;
	u16 nVideoHeight ;
        u8  bRecMode;
        u8 reserved[1];
	u8* nAddrY0;
	u8* nAddrC0;
	u8* nAddrY1;
	u8* nAddrC1;
} Mdl_CamTaskHSP_t;
#define Mdl_CameraTaskHSP_t Mdl_CamTaskHSP_t

#if defined(__I_SW__)
#define MDLPREVIEW_MBX_BASE             5
#elif defined(__SDK_SIMULATION__)
#define MDLPREVIEW_MBX_BASE             VM_MBX_CUS36
#else
#define MDLPREVIEW_MBX_BASE             VM_MBX_CUS47
#endif
#define MDLPREVIEW_MBX_MAIN             MDLPREVIEW_MBX_BASE
#endif

#ifndef __SDK_SIMULATION__
MmlCameraResult_e MdlCamera_Set_Power_UVC(UVC_CONFIG_t *pUVCConfig,u8 OnOff);
MmlCameraResult_e MdlCamera_Set_ATV_Power(u8 OnOff, MmlCameraStartPreview_t *pCam_PreSet, AtvSpec_t *pAtvParaSet, u8 buffopt);
#endif

void Cam_PausePreview(u8);
u8 Cam_IsPausePreview(void);
MmlCameraResult_e Cam_GetMaxPreviewSize(u32 *pWidth, u32 *pHeight);


#endif   //_MS_MDL_CAMERA_TASK_PUB_H_

