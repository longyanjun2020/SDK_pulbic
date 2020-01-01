#ifndef _MS_MDL_CAMERA_TASK_H_
#define _MS_MDL_CAMERA_TASK_H_
#include "sys_vm_dbg.ho"
#define  vm_msg_t  vm_msg_t
#define MDL_PVW_TRC_NORM                           (_CUS1 | LEVEL_28)

#ifndef __SDK_SIMULATION__
#include "Mdl_camera_task_pub.h"
#else
#include "Vm_msgof.hc"
#endif
#include "Sys_sys_mbx_def.h"

#define ENABLE_PVWMSG
#if defined(ENABLE_PVWMSG)
#define MDL_PVW_MSG   vm_dbgTrace
#else
#define MDL_PVW_MSG
#endif

#if 0
typedef enum
{
    CAMERA_ON = 0,
    CAMERA_SETTING = 1,
    CAMERA_RECORD = 2,
    CAMERA_OFF = 3,
} CAMERAMODE_t;
#endif

typedef enum PMainTaskState
{
    MAIN_TASK_CAMERA_CLOSE,
    MAIN_TASK_CAMERA_ON,
    MAIN_TASK_CAMERA_SETTING,
    MAIN_TASK_CAMERA_RECORD,
    MAIN_TASK_CAMERA_RECSTOP,
    MAIN_TASK_CAMERA_OFF,
    MAIN_TASK_CAMERA_SENSOR_DETECT,
    MAIN_TASK_CAMERA_MOTION_DETECT,
    MAIN_TASK_CAMERA_MOTION_DETECT_TIMMER,
} PMainTaskState_e;
static PMainTaskState_e _g_eNewMainTaskState = MAIN_TASK_CAMERA_CLOSE;
static PMainTaskState_e _g_ePMainTaskState = MAIN_TASK_CAMERA_CLOSE;


#ifdef __SDK_SIMULATION__

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

typedef enum MdlCameraMsgType
{
    MDL_MSG_CAMERA_USECASE = VM_CUS47_BASE, // to communicate with other tasks
    MDL_MSG_CAMERA_RESPONSE, // notify results to other tasks

} MdlCameraMsgType_e;


typedef struct
{
    u32  Msg;
	u16  eDSTFormat;
	u16 nVideoWidth ;
	u16 nVideoHeight ;
	u8* nAddrY0;
	u8* nAddrC0;
	u8* nAddrY1;
	u8* nAddrC1;

} Mdl_CamTaskHSP_t;
#define Mdl_CameraTaskHSP_t Mdl_CamTaskHSP_t

#if defined(__I_SW__)
#define MDLPREVIEW_MBX_BASE             5
#else
#define MDLPREVIEW_MBX_BASE             VM_MBX_CUS47
#endif
#define MDLPREVIEW_MBX_MAIN             MDLPREVIEW_MBX_BASE


#endif
// Message Type
//#define MDLVDR_MSG_TYPE_TIMEOUT    0
//#define MDLVDR_MSG_TYPE_INTERNAL   1
//#define MDLVDR_MSG_TYPE_EXTERNAL   2

#define MDLPREVIEW_TIMER_MOTION_DETECT   (MDLPREVIEW_MBX_BASE + 0x10) // timer to check Luma
#define MDLPREVIEW_TIMER_INTERVAL_100MS      (VM_RTK_MS_TO_TICK(100))
#define MDLPREVIEW_TIMER_INTERVAL_2000MS      (VM_RTK_MS_TO_TICK(2000))

void MdlCamMainTaskInitEntry(void);
void MdlCamMainTaskEntry(void * arg);


#endif   //_MS_MDL_PREVIEW_MAIN_H_

