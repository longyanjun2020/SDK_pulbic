#ifndef _MDL_VT_STATE_H_
#define _MDL_VT_STATE_H_

#include <mdl_vt_internal.h>

#if VT_DBG_UART
    //#define VT_STATE_MSG(fmt, ...) UartSendTrace("[VT_STATE] "fmt, ##__VA_ARGS__)
    #define VT_STATE_MSG(fmt, ...) DrvUartDebugTrace("[VT_STATE] "fmt, ##__VA_ARGS__)
    #define VT_STATE_MSG_ERROR(fmt, ...) DrvUartDebugTrace("[VT_STATE]Error: "fmt, ##__VA_ARGS__)
#else
    #define VT_STATE_MSG(fmt, ...) mdl_vt_printf(1, "[VT_STATE] "fmt, ##__VA_ARGS__)
    #define VT_STATE_MSG_ERROR(fmt, ...) mdl_vt_printf(2, "[VT_STATE]Error: "fmt, ##__VA_ARGS__)
#endif

typedef enum {
    VT_State_Unknown = 0,
    VT_State_Close,
    VT_State_WaitingToOpen,
    VT_State_Stop,
    VT_State_WaitingToPlay,
    VT_State_Play,
    VT_State_WaitingToStop,
    VT_State_WaitingToClose,
    VT_State_ErrorHanle,
    VT_State_Error,

    VT_SubState_Unknown = 0x0100,
    VT_PlaySubState_Camera,
    VT_PlaySubState_Picture,
    VT_PlaySubState_LocalSmall,
    VT_PlaySubState_LocalLarge,
    VT_PlaySubState_LocalOnly,
    VT_PlaySubState_RemoteOnly,
    VT_WaitPlaySubState_Init = 0x0110,
    VT_WaitPlaySubState_VdrDone,
    VT_WaitPlaySubState_AvpDone,
    VT_WaitPlaySubState_AllDone,
    VT_WaitPlaySubState_VdrFail,
    VT_WaitPlaySubState_AvpFail,
    VT_WaitStopSubState_Init = 0x0120,
    VT_WaitStopSubState_VdrDone,
    VT_WaitStopSubState_AvpDone,
    VT_WaitStopSubState_AllDone,
    VT_PlaySubState_Ok = 0x0130,
    VT_PlaySubState_VdrStopDone,
    VT_PlaySubState_AvpStopDone,
    VT_PlaySubState_AllStopDone,
    VT_PlaySubState_RemotePicDisabled = 0x0140,
    VT_PlaySubState_RemotePicEnabled,
    VT_PlaySubState_RecordStopped = 0x0150,
    VT_PlaySubState_RecordStarting,
    VT_PlaySubState_Recording,
    VT_PlaySubState_RecordStopping,
    VT_PlaySubState_RecordSaving,
    VT_PlaySubState_RecordFileSaving,
    VT_PlaySubState_RecordFileDiscarding,
    VT_PlaySubState_RecordSaveFileAborting,
    VT_PlaySubState_RecordSaveFileFail,
    VT_PlaySubState_BlankPreviewDisabled = 0x0160,
    VT_PlaySubState_BlankPreviewEnabled,
} vt_state_et;


typedef enum{
    VT_Event_Unknown = 0,
    VT_Event_Error,
    VT_Event_ErrorHanlded,
    VT_Event_Play,
    VT_Event_Stop,
    VT_Event_Open,
    VT_Event_Close,
    VT_Event_LocalVideoSrcCamera,
    VT_Event_LocalVideoSrcPicture,
    VT_Event_ScreenLocalSmall,
    VT_Event_ScreenLocalLarge,
    VT_Event_ScreenLocalOnly,
    VT_Event_ScreenRemoteOnly,
    VT_Event_ScreenSensorDigitalZoom,
    VT_Event_ScreenSensorBrightness,
    VT_Event_ScreenSensorContrast,
    VT_Event_ReadyToPlay,/* 0x10 */
    VT_Event_ReadyToStop,
    VT_Event_ReadyToStop_1,
    VT_Event_ReadyToOpen,
    VT_Event_ReadyToClose,
    VT_Event_StartVdrDone,
    VT_Event_StartAvpDone,
    VT_Event_StartAllDone,
    VT_Event_StopVdrDone,
    VT_Event_StopAvpDone,
    VT_Event_StopAllDone,
    VT_Event_EnableRemotePicture,
    VT_Event_DisableRemotePicture,
    VT_Event_RecordStart,
    VT_Event_RecordStartOk,
    VT_Event_RecordStartFail,
    VT_Event_RecordStop, /* 0x20 */
    VT_Event_RecordStopOk,
    VT_Event_RecordSaveFile,
    VT_Event_RecordSaveFileOk,
    VT_Event_RecordSaveFileFail,
    VT_Event_RecordDiscardFile,
    VT_Event_RecordDiscardFileOk,
    VT_Event_RecordAbortSavingFile,
    VT_Event_RecordAbortSavingFileOk,
    VT_Event_RecordDiskFull,
    VT_Event_RecordRunTimeError,
    VT_Event_EnableBlankPreview,
    VT_Event_DisableBlankPreview,
} vt_event_t;

typedef enum {
    VT_STATE_OK = 0,
    VT_STATE_ERR_TRANSITION,
    VT_STATE_ERR_HANDLER,
} vt_state_err_et;

typedef struct {
    vt_state_et Top;
    vt_state_et Play_Sub_LocalSrc;
    vt_state_et Play_Sub_ScreenMode;
    vt_state_et Play_Sub_AvpVdr;
    vt_state_et Play_Sub_RemotePic;
    vt_state_et Play_Sub_BlankPreview;
    vt_state_et Play_Sub_Record;
    vt_state_et WaitingToPlay_Sub_AvpVdr;
    vt_state_et WaitingToStop_Sub_AvpVdr;
    vt_state_et before_error;
} vt_state_t;

typedef vt_state_err_et (*vt_event_handler)(vt_state_t *state, vt_event_t e, void *data);
typedef vt_state_err_et (*vt_state_post_handler)(vt_state_t *state, vt_event_t e, void *data);

typedef struct {
    vt_state_et cur_state;
    vt_event_t event;
    vt_event_handler pre_handler;
    vt_state_et next_state;
    vt_state_post_handler post_handler;
} vt_state_trasition_t;

void vt_state_init(vt_state_t *cur_state);
vt_state_err_et
vt_state_transition (vt_state_et cur_state,
                     vt_event_t e,
                     vt_state_et
                     *next_state,
                     vt_state_t *state,
                     void *data);

#endif
