#ifndef __MMI_CAMERA_MSGDEF_H__
#define __MMI_CAMERA_MSGDEF_H__

typedef enum
{
	CAM_RSP_SUCCESS = 0,
	CAM_RSP_FAILURE,
	CAM_RSP_REJECT	
} CamRspCode_t;

typedef struct 
{
	//MAECamMsgId_t			MsgId;
	CamRspCode_t			RspCode;
	u16						*pData;
	u32						nDataSize;
	u32						UserData;
	MediaRspId_e            eTransRspId;	
} CamMsgBody_t;

#endif //__MMI_CAMERA_MSGDEF_H__
