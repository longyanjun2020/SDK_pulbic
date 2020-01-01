#ifndef _MS_MDL_CAMERA_MAIN_H_
#define _MS_MDL_CAMERA_MAIN_H_

#if defined(__I_SW__)
//#include "typedef.h"
#include "vm_types.ht"

////////////////////////////
/*
typedef enum
{
  eCAM_POWER_OFF=0,
  eCAM_POWER_ON,
}CAM_POWER_e;
*/
typedef enum
{
  eMDL_CMD_PREVIEW_ON=0,
  eMDL_CMD_PREVIEW_OPEN,
  eMDL_CMD_PREVIEW_CLOSE,
  eMDL_CMD_PREVIEW_SETTING,
  eMDL_CMD_RECORD_START,
  eMDL_CMD_RECOR_STOP,
  eMDL_CMD_PREVIEW_OFF,
  eMDL_CMD_SENSOR_DETECT,

}CAM_MSG_e;


////////////////test//////////////////
typedef enum MdlCamCmd
{
    MDLVDR_CMD_PREVIEW_ON,
    MDLVDR_CMD_PREVIEW_OPEN,
    MDLVDR_CMD_PREVIEW_CLOSE,
    MDLVDR_CMD_PREVIEW_SETTING,
    MDLVDR_CMD_RECORD_START,
    MDLVDR_CMD_RECOR_STOP,
    MDLVDR_CMD_PREVIEW_OFF,
    MDLVDR_CMD_SENSOR_DETECT,


    MDLVDR_MBOX_NONE_CAM        = 0xFFFEUL,
    MDLVDR_MBOX_TIMEOUT_CAM     = 0xFFFFUL,

} MdlCamCmd_e;


#define MDLVDR_MBX_MENU         1
#define MDLVDR_MBX_CAM          5

#define MML_MESSAGE_CAMERA_EXECUTION    (MDLVDR_MBX_CAM)   // based on MBox??
/*
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
*/
////////////////////////

void MdlCameraMain(u32 u32UseCase);


///////test/////////////////////
u32 _MdlCamReceiveMsg(u16 Mbx, u32 *u32Msg );
u8 _MdlCamSendMsg(u16 MbxSrc, u16 MbxDst, u32 u32Msg);
void MdlCameraMainTest(void);

#endif //__I_SW__

#endif   //_MS_MDL_CAMERA_MAIN_H_
