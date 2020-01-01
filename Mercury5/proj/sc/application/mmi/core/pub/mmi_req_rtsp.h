/**
 * @file    mmi_req_rtsp.h
 * @brief   The file handles the rtsp event with rtsp task
  *
  */
#ifndef __MMI_REQ_RTSP_H__
#define __MMI_REQ_RTSP_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "mmi_mae_common_def.h"
#include "mmi_event.h"
#include "mmi_mae_applet.h"
#include "mmi_if_rtsp.h"
/*=============================================================*/
// Function Declaration
/*=============================================================*/
MAE_Ret mmi_rtsp_download_init_req(u32 nUser, u32 nBufferSize, u32 nNotifyThreshold);
MAE_Ret mmi_rtsp_download_uninit_req(u32 nUser);
MAE_Ret mmi_rtsp_download_start_req(u32 nUser, u8 *pUrlPath, u16 nUrlLen, u32 nStartTime);
MAE_Ret mmi_rtsp_download_stop_req(u32 nUser);
MAE_Ret mmi_rtsp_download_suspend_req(u32 nUser);
MAE_Ret mmi_rtsp_download_resume_req(u32 nUser, u32 nStartTime);
MAE_Ret mmi_rtsp_download_data_rsp(u32 nUser, void *pData, u32 nDataSize);

#if 1 //defined(__PC_SIMULATOR__)
#define __RTSP_MDL_SIM__
//#define __RTSP_MDL_CENTRAL_SIM__ // for MDL centraliztion or RTSP Srv simulation
#endif

#if defined(__RTSP_MDL_SIM__)

enum
{
    RTSP_MDL_SIM_TEST_PLAY_NORMAL = 0,
    RTSP_MDL_SIM_TEST_PLAY_5S,
    RTSP_MDL_SIM_TEST_PLAY_PAUSE_RESUME,
    RTSP_MDL_SIM_TEST_PLAY_SEEK,

    RTSP_MDL_SIM_TEST_CASE_01,
    RTSP_MDL_SIM_TEST_CASE_02,
    RTSP_MDL_SIM_TEST_CASE_03,
    RTSP_MDL_SIM_TEST_CASE_04,
    RTSP_MDL_SIM_TEST_CASE_05,
    RTSP_MDL_SIM_TEST_CASE_06,
    RTSP_MDL_SIM_TEST_CASE_07,
    RTSP_MDL_SIM_TEST_CASE_08,
    RTSP_MDL_SIM_TEST_CASE_09,
    RTSP_MDL_SIM_TEST_CASE_10,

    RTSP_MDL_SIM_TEST_CASE_11,
    RTSP_MDL_SIM_TEST_CASE_12,
    RTSP_MDL_SIM_TEST_CASE_13,
    RTSP_MDL_SIM_TEST_CASE_14,
    RTSP_MDL_SIM_TEST_CASE_15,
    RTSP_MDL_SIM_TEST_CASE_16,
    RTSP_MDL_SIM_TEST_CASE_17,
    RTSP_MDL_SIM_TEST_CASE_18,
    RTSP_MDL_SIM_TEST_CASE_19,
    RTSP_MDL_SIM_TEST_CASE_20,

    RTSP_MDL_SIM_TEST_CASE_21,
    RTSP_MDL_SIM_TEST_CASE_22,
    RTSP_MDL_SIM_TEST_CASE_23,

    RTSP_MDL_SIM_TEST_CASE_ERROR,

    RTSP_MDL_SIM_TEST_MAX
};

enum
{
    LOG_MSG_NORMAL_EXIT = 0,

    LOG_MSG_SEND_CMD_OPEN,
    LOG_MSG_SEND_CMD_CLOSE,
    LOG_MSG_SEND_CMD_INIT,
    LOG_MSG_SEND_CMD_UNINIT,
    LOG_MSG_SEND_CMD_PLAY,
    LOG_MSG_SEND_CMD_STOP,
    LOG_MSG_SEND_CMD_PAUSE,
    LOG_MSG_SEND_CMD_RESUME,
    LOG_MSG_SEND_CMD_SEEK,
    LOG_MSG_SEND_CMD_DATA_CONSUMED,
#if 0
    MDL_SIM_EVT_SEND_CMD_GET_DATA,
    MDL_AVP_STREAMING_CMD_SEND_RTCP,
#endif

#if 0 //AVP -> MDL streaming
    LOG_MSG_SEND_AVP_CMD_PLAY,
    LOG_MSG_SEND_AVP_CMD_PAUSE,
    LOG_MSG_SEND_AVP_CMD_RESUME,
    LOG_MSG_SEND_AVP_CMD_SEEK,
    LOG_MSG_SEND_AVP_CMD_STOP,
#endif

    LOG_MSG_RSP_OPEN,
    LOG_MSG_RSP_CLOSE,
    LOG_MSG_RSP_INIT,
    LOG_MSG_RSP_UNINIT,
    LOG_MSG_RSP_PLAY,
    LOG_MSG_RSP_STOP,
    LOG_MSG_RSP_PAUSE,
    LOG_MSG_RSP_RESUME,
    LOG_MSG_RSP_SEEK,
    //LOG_MSG_RSP_GET_DATA,

    LOG_MSG_RECV_OPEN_FAIL,
    LOG_MSG_RECV_OPEN_COMPLETE,
    LOG_MSG_RECV_CLOSE_FAIL,
    LOG_MSG_RECV_CLOSE_COMPLETE,
    LOG_MSG_RECV_INIT_FAIL,
    LOG_MSG_RECV_INIT_COMPLETE,
    LOG_MSG_RECV_UNINIT_FAIL,
    LOG_MSG_RECV_UNINIT_COMPLETE,
    LOG_MSG_RECV_PLAY_FAIL,
    LOG_MSG_RECV_PLAY_COMPLETE,
    LOG_MSG_RECV_STOP_FAIL,
    LOG_MSG_RECV_STOP_COMPLETE,
    LOG_MSG_RECV_PAUSE_FAIL,
    LOG_MSG_RECV_PAUSE_COMPLETE,
    LOG_MSG_RECV_RESUME_FAIL,
    LOG_MSG_RECV_RESUME_COMPLETE,
    LOG_MSG_RECV_SEEK_FAIL,
    LOG_MSG_RECV_SEEK_COMPLETE,

    LOG_MSG_RECV_DATA_IN,
    LOG_MSG_RECV_DATA_EOS,
    LOG_MSG_RECV_STORAGE_FULL,
    LOG_MSG_RECV_NETWORK_DISCONNECTED,
    LOG_MSG_RECV_NETWORK_CONNECTION_FAIL,

//Other
    LOG_MSG_INTERNAL_CHANGE_STATE,
    LOG_MSG_INTERNAL_MAY_SDP,
    LOG_MSG_INTERNAL_USER_ACTION_TIMER,
    LOG_MSG_INTERNAL_RSP_ABORT,
    LOG_MSG_INTERNAL_PLAY_FAIL_AND_RETRY,

    LOG_MSG_RECV_ERROR,

    LOG_MSG_MAX
};

enum
{
    MDL_SIM_EVT_NULL = MAE_EVT_RTSP_MDLSIM_BASE,

    MDL_SIM_EVT_SEND_CMD_OPEN,
    MDL_SIM_EVT_SEND_CMD_CLOSE,
    MDL_SIM_EVT_SEND_CMD_PLAY,
    MDL_SIM_EVT_SEND_CMD_STOP,
    MDL_SIM_EVT_SEND_CMD_INIT,
    MDL_SIM_EVT_SEND_CMD_UNINIT,
    MDL_SIM_EVT_SEND_DATA_IND_RSP, //CMD_DATA_CONSUMED
    MDL_SIM_EVT_SEND_CMD_PAUSE,
    MDL_SIM_EVT_SEND_CMD_RESUME,
    MDL_SIM_EVT_SEND_CMD_SEEK,
    //MDL_SIM_EVT_SEND_CMD_GET_DATA,

    MDL_SIM_EVT_RECV_OPEN_RSP,
    MDL_SIM_EVT_RECV_CLOSE_RSP,
    MDL_SIM_EVT_RECV_PLAY_RSP,
    MDL_SIM_EVT_RECV_STOP_RSP,
    MDL_SIM_EVT_RECV_INIT_RSP,
    MDL_SIM_EVT_RECV_UNINIT_RSP,
    MDL_SIM_EVT_RECV_PAUSE_RSP,
    MDL_SIM_EVT_RECV_RESUME_RSP,
    MDL_SIM_EVT_RECV_SEEK_RSP,
    //MDL_SIM_EVT_RECV_GET_DATA_RSP,

    MDL_SIM_EVT_RECV_OPEN_FAIL,
    MDL_SIM_EVT_RECV_OPEN_COMPLETE,
    MDL_SIM_EVT_RECV_CLOSE_FAIL,
    MDL_SIM_EVT_RECV_CLOSE_COMPLETE,
    MDL_SIM_EVT_RECV_PLAY_FAIL,
    MDL_SIM_EVT_RECV_PLAY_COMPLETE,
    MDL_SIM_EVT_RECV_STOP_FAIL,
    MDL_SIM_EVT_RECV_STOP_COMPLETE,
    MDL_SIM_EVT_RECV_INIT_FAIL,
    MDL_SIM_EVT_RECV_INIT_COMPLETE,
    MDL_SIM_EVT_RECV_UNINIT_FAIL,
    MDL_SIM_EVT_RECV_UNINIT_COMPLETE,
    MDL_SIM_EVT_RECV_PAUSE_FAIL,
    MDL_SIM_EVT_RECV_PAUSE_COMPLETE,
    MDL_SIM_EVT_RECV_RESUME_FAIL,
    MDL_SIM_EVT_RECV_RESUME_COMPLETE,
    MDL_SIM_EVT_RECV_SEEK_FAIL,
    MDL_SIM_EVT_RECV_SEEK_COMPLETE,

    //MDL_SIM_EVT_RECV_DATA_IN, //MDL_SIM_EVT_RECV_DATA_IND
    //MDL_SIM_EVT_RECV_DATA_EOS, //MDL_SIM_EVT_RECV_FINISH_IND

    MDL_SIM_EVT_RECV_WAIT_FREE_SIZE,
    MDL_SIM_EVT_RECV_STORAGE_FULL,
    MDL_SIM_EVT_RECV_SEND_RTCP,
    MDL_SIM_EVT_RECV_NETWORK_DISCONNECTED,
    MDL_SIM_EVT_RECV_NETWORK_CONNECTION_FAIL,

    MDL_SIM_EVT_RECV_DATA_IND,
    MDL_SIM_EVT_RECV_FINISH_IND,
    MDL_SIM_EVT_RECV_ABORT_IND,

    MDL_SIM_EVT_QUEUE_ACTION_SET_QUEUE_MIN_MAX,
    MDL_SIM_EVT_QUEUE_ACTION_MOVE_INDEX,
};

typedef u32 eMDLEvent;

enum
{
    MDL_SIM_CMD_RESULT_NULL = 0,

    MDL_SIM_CMD_RESULT_OPEN,
    MDL_SIM_CMD_RESULT_PLAY,
    MDL_SIM_CMD_RESULT_STOP,
    MDL_SIM_CMD_RESULT_CLOSE,
    MDL_SIM_CMD_RESULT_INIT,
    MDL_SIM_CMD_RESULT_UNINIT,
    MDL_SIM_CMD_RESULT_PAUSE,
    MDL_SIM_CMD_RESULT_RESUME,
    MDL_SIM_CMD_RESULT_SEEK,

    MDL_SIM_CMD_RESULT_MAX
};

typedef u32 eMDLCmdResult;
typedef enum
{
    MDLSIM_STATE_START = 0,
    MDLSIM_STATE_IDLE,

    MDLSIM_STATE_OPEN,
    MDLSIM_STATE_INIT,
    MDLSIM_STATE_PLAY,
    MDLSIM_STATE_STOP,
    MDLSIM_STATE_UNINIT,
    MDLSIM_STATE_CLOSE,
    MDLSIM_STATE_PAUSE,

    MDLSIM_STATE_END

} eMdlSimState;


typedef struct QueueData_t_
{
    RtspDownloadDataInd_t tDataInd;
    void *pNextDataPtr;
} QueueData_t;

// Simulation by file manipulation
typedef struct _RtspMdlSim
{
    u16                 nTestCaseId;
    void                *pAppHandle;
    MAE_WChar           *pwPath;
    boolean             bWaitingEvent;

    eMDLEvent           eRecvEvent; //MAE event
    u32                 nRecvParm1;
    u32                 nRecvParm2;

    eMdlSimState        eSimState;
    boolean             bIsEndState;
    boolean             bCancelTimer;

    boolean             bWaitOpenRsp;
    boolean             bWaitPlayRsp;
    boolean             bWaitStopRsp;
    boolean             bWaitCloseRsp;
    boolean             bWaitInitRsp;
    boolean             bWaitUninitRsp;
    boolean             bWaitPauseRsp;
    boolean             bWaitResumeRsp;
    boolean             bWaitSeekRsp;
    boolean             bOpened;
    boolean             bInited;
    boolean             bReadyToPlay;

    eMDLCmdResult       eWaitCmdResult;

    QueueData_t         *pQueueFront;
    QueueData_t         *pQueueRear;
    u16                 nQueueCount;
    u16                 nStartConsumingCountMin;
    u16                 nStartConsumingCountMax;
    boolean             bRunQueueAction;

}_RtspMdlSim_t;

MAE_Ret RtspMdlSim_Start(void *pThis, MAE_WChar *pwPath, u16 nTestCaseId);
MAE_Ret RtspMdlSim_End(void *pThis);
boolean RtspMDLSim_HandleEvt(IApplet *pThis, u32 nEventId, u32 nParam1, u32 nParam2);

#endif //__RTSP_MDL_SIM__

#endif /* __MMI_REQ_RTSP_H__ */
