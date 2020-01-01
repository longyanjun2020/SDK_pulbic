#ifdef __TTS__

#ifndef __MMI_TTS_SRV_STGR_H__
#define __MMI_TTS_SRV_STGR_H__

#include "mmi_srvstgr.h"
#include "tts_itf.h"

typedef void* TtsSrvStgrHdl_t;

#define TTS_CMD_ATTR_INTERRUPTED (0X01)
#define TTS_CMD_ATTR_PURGED       (0X02)
#define TTS_CMD_ATTR_LOCKED      (0X04)

typedef struct
{
    SrvStgr_t sSrvStgr;
    void *pvSrv;
    void *pvData;
}TtsSrvStgr_t;

typedef enum
{
    TTSSRVSTGR_ErrorCode_Success = TTS_ERROR_SUCCESS,
    TTSSRVSTGR_ErrorCode_UnKnown = TTS_ERROR_UNKNOWN,
    TTSSRVSTGR_ErrorCode_InvalidVersion = TTS_ERROR_INVALIVERSION,
    TTSSRVSTGR_ErrorCode_GetBufferSizeFail = TTS_ERROR_GETBUFFERSIZE,
    TTSSRVSTGR_ErrorCode_GetMemoryFail = TTS_ERROR_GETMEMORY,
    TTSSRVSTGR_ErrorCode_KernelInitFail = TTS_ERROR_KERNELINIT,
    TTSSRVSTGR_ErrorCode_SetCodeFail = TTS_ERROR_SETCODE,
    TTSSRVSTGR_ErrorCode_SetLanguageFail = TTS_ERROR_SETLANGUAGE,
    TTSSRVSTGR_ErrorCode_SetFormatFail = TTS_ERROR_SETFORMAT,
    TTSSRVSTGR_ErrorCode_SetVolFail = TTS_ERROR_SETVOL,
    TTSSRVSTGR_ErrorCode_SetSpeakManFail = TTS_ERROR_SETSPEAKMAN,
    TTSSRVSTGR_ErrorCode_SetOutCallbackFail = TTS_ERROR_SETOUTCALLBACK,
    TTSSRVSTGR_ErrorCode_SetDecodeFail = TTS_ERROR_DECODE,
    TTSSRVSTGR_ErrorCode_SetInputParamFail = TTS_ERROR_INPUT_PARAM,
    TTSSRVSTGR_ErrorCode_NotInit = TTS_ERROR_NOT_INIT,
    TTSSRVSTGR_ErrorCode_InputModeFail = TTS_ERROR_INPUT_MODE,
    TTSSRVSTGR_ErrorCode_FileOpenFail = TTS_ERROR_FILEOPEN,
    TTSSRVSTGR_ErrorCode_GetSemaphoreFail = TTS_ERROR_GETSEMAPHORE,
    TTSSRVSTGR_ErrorCode_InitSemaphoreFail = TTS_ERROR_INITSEMAPHORE,
    TTSSRVSTGR_ErrorCode_StopDecodeFail = TTS_ERROR_STOPDECODE,
    TTSSRVSTGR_ErrorCode_Uninitialized = TTS_ERROR_UNINITIALIZED,
    TTSSRVSTGR_ErrorCode_Failed = TTS_ERROR_FAILED,
}TTSSRVSTGR_ERRORCODE_e;

typedef struct
{
    TTSSRVSTGR_ERRORCODE_e eErrorCode;
    SrvStgrCmdDataFreeCB pfnFreeRspCmdDataCb;
    void *pvRspCmdData;
}TtsSrvStgrRspCmdData_t;

TtsSrvStgrHdl_t TtsSrvStgr_Create(void *pvOwner);
void TtsSrvStgr_Destroy(TtsSrvStgrHdl_t hTtsSrvStgr);

SrvStgrCmdHdl_t TtsSrvStgrCmd_Create(TtsSrvStgrHdl_t hSrvStgr, u32 uCmdType, void *pvCmdData, SrvStgrCmdDataFreeCB pfnCmdDataFreeCb);
void TtsSrvStgrCmd_Destroy(SrvStgrCmdHdl_t hSrvStgrCmd);

TtsSrvStgrRspCmdData_t* TtsSrvStgrRspCmdDataAlloc(TTSSRVSTGR_ERRORCODE_e eErrorCode, void *pvRspCmdData, SrvStgrCmdDataFreeCB pfnFreeCmdDataCb);
void TtsSrvStgrRspCmdDataFreeCb(void *pvRspCmdData);

#endif/* __MMI_TTS_SRV_STGR_H__ */
#endif/* __TTS__ */
