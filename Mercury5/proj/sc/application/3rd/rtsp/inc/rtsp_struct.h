/**
 * @file    rtsp_struct.h
  */
#ifndef __RTSP_STRUCT_H__
#define __RTSP_STRUCT_H__

#include "ven_std.h"
#include "cus_msg.hc"
#include "rtsp_event.h"
/*=============================================================*/
// type and define
/*=============================================================*/

typedef enum RTSP_Ret_
{
	RTSP_RETURN_OK = 0,
	RTSP_RETURN_INIT_FAILED,
	RTSP_RETURN_OPEN_FAILED,
	RTSP_RETURN_OPEN_PENDING,
	RTSP_RETURN_RECV_FAILED,
	RTSP_RETURN_RECV_PENDING,
	RTSP_RETURN_CONNECT_FAILED,
	RTSP_RETURN_INVALID_PARM,
	RTSP_RETURN_ERROR_NOMEMORY,
	RTSP_RETURN_ERROR_SETTING,
	RTSP_RETURN_ERROR_NETWORK,
	RTSP_RETURN_ERROR_TIMEOUT,
	RTSP_RETURN_ERROR_UNKOWN,
	RTSP_RETURN_NOT_HANDLE_REQ
}RTSP_Ret;

typedef enum rtspCntMode_e_
{
    RTSP_CONNECTION_NORMAL = 0,
    RTSP_CONNECTION_INTERLEAVING,

    RTSP_CONNECTION_NUM
} rtspCntMode_e;

typedef struct
{
    u32 nUser;
    u32 nBufferSize;
    u32 nNotifyThreshold;
} mmi_rtsp_download_init_req_t;

typedef struct
{
    u32 nUser;
} mmi_rtsp_download_uninit_req_t;

typedef struct
{
    u32 nUser;
    u8 *pUrlPath;
    u16 nUrlLen;
    u32 nStartTime;
    u32 nEndTime;
} mmi_rtsp_download_start_req_t;

typedef struct
{
    u32 nUser;
} mmi_rtsp_download_stop_req_t;

typedef struct
{
    u32 nUser;
    u32 nStartTime;
    u32 nEndTime;
} mmi_rtsp_download_suspend_req_t;

typedef struct
{
    u32 nUser;
    u32 nStartTime;
    u32 nEndTime;
} mmi_rtsp_download_resume_req_t;

typedef struct
{
    u32 nUser;
    void *pData;
    u32 nDataSize;
} mmi_rtsp_download_data_rsp_t;

typedef struct
{
    void *pData;
	u32 nDataSize;
	u32 nDataPos;
} mmi_rtsp_download_data_ind_t;

typedef u32 mmi_rtsp_evt_type_e;
typedef struct
{
    mmi_rtsp_evt_type_e evtType;
    void *pData;
    u32 nDatasize;
    union
    {
        u32 nFileSize;
        RTSP_Ret nErrorType;
        mmi_rtsp_download_data_ind_t tDataInd;
    } uData;
}rtsp2mmi_t;


int fake_rtsp_send_msg_to_avp_cb(int message_type, int data_size, void *data);
int fake_rtsp_send_msg_to_stm_cb(void *stm_ctx, int message_type, int data_size, void *data);

// MDL Sim
int MDLSim_rtsp_send_msg_to_stm_cb(void *stm_ctx, int message_type, int data_size, void *data);
int MDLSim_rtsp_send_msg_to_avp_cb(int message_type, int data_size, void *data);
#endif //__HTTP_STRUCT_H__
