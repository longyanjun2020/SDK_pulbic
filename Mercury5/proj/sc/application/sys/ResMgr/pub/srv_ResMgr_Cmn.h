/**
* @file srv_ResMgr_Cmn.h
*
* Applicatoin Bridge Layer defines the bridge functions between
*	drivers and Resource Manager
*  This header file defines the declaration of operations of audio.
*
*/

#ifndef __SRV_RESMGR_CMN_H__
#define __SRV_RESMGR_CMN_H__

/*=============================================================*/
// Include Files
/*=============================================================*/
#include "ABL_CusParms.h"
#include "esl_aud_itf.h"
#include "ResMgr_CmdMgrItf.h"
#include "ResMgr_AppListenerItf.h"
#include "MediaTaskClientMgrItf.h"
#include "MediaCmn.h"
/*=============================================================*/
// Macro Definitions
/*=============================================================*/
/*=============================================================*/
// Type Declarations
/*=============================================================*/
typedef enum ABL_CmnErrCode_e_
{
    ABL_CMN_OK,
    ABL_CMN_FAIL,
    ABL_CMN_PARAM_ERROR,
    ABL_CMN_OUT_OF_MEMORY,
    ABL_CMN_REJECT,
    ABL_CMN_NUM = ABL_CMN_REJECT
} ABL_CmnErrCode_e;

typedef enum ABL_AudFormat_e_
{
    ABL_AUD_WAVE = 0,       //ESL_AUD_WAVE
    ABL_AUD_MIDI,           //ESL_AUD_MIDI
    ABL_AUD_IMY,            //ESL_AUD_IMY
    ABL_AUD_MP3,            //ESL_AUD_MP3
    ABL_AUD_MP2,			//ESL_AUD_MP2
    ABL_AUD_MP1,			//ESL_AUD_MP1
    ABL_AUD_AAC,            //ESL_AUD_AAC
    ABL_AUD_APE,            //ESL_AUD_APE
    ABL_AUD_AMR,            //ESL_AUD_AMR
    ABL_AUD_AWB,            //ESL_AUD_AWB
    ABL_AUD_RAM,            //ESL_AUD_RAM
    ABL_AUD_ASF,            //ESL_AUD_ASF
    ABL_AUD_WMA,            //ESL_AUD_WMA
    ABL_AUD_WMV,            //ESL_AUD_WMV
    ABL_AUD_MP4,            //ESL_AUD_MP4
    ABL_AUD_3GP,            //ESL_AUD_3GP
    ABL_AUD_WAVE_EXT,       //ESL_AUD_WAVE_EXT
    ABL_AUD_MIDI_EVENT,     //ESL_AUD_MIDI_EVENT
    ABL_AUD_PCM,            //ESL_AUD_PCM
    ABL_AUD_RA,				//ESL_AUD_RA,
    ABL_AUD_RM,				//ESL_AUD_RM,
  	ABL_AUD_AVI,			//ESL_AUD_AVI,
  	ABL_AUD_MFS,			//ESL_AUD_MFS
  	ABL_AUD_TS,				//ESL_AUD_TS
    ABL_AUD_M4A,            //ESL_AUD_M4A
    ABL_AUD_RMVB,           //ESL_AUD_RMVB,
    ABL_AUD_FLV,            //ESL_AUD_FLV,
    ABL_AUD_PS,             //ESL_AUD_PS,
    ABL_AUD_H324,           //ESL_AUD_H324,
    ABL_AUD_MPG,            //ESL_AUD_MPG,
    ABL_AUD_VOB,            //ESL_AUD_VOB,
    ABL_AUD_DAT,            //ESL_AUD_DAT,
    ABL_AUD_DIVX,           //ESL_AUD_DIVX,
    ABL_AUD_MOV,            //ESL_AUD_MOV,
    ABL_AUD_KMV,            //ESL_AUD_KMV,
    ABL_AUD_MKV,            //ESL_AUD_MKV,
    ABL_AUD_UNKNOW_FORMAT   //ESL_AUD_UNKNOW_FORMAT
} ABL_AudFormat_e;  //MediaSrvFileFormat_e Sync to esl_AudFormat_e,

typedef enum ABL_RingBuffInfo_e_
{
    ABL_RINGBUFF_INFO__BODY_SIZE = 0,
    ABL_RINGBUFF_INFO__FREE_SPACE,
    ABL_RINGBUFF_INFO__FILLED_SIZE,
    ABL_RINGBUFF_INFO__STREAMING_HDL
} ABL_RingBuffInfo_e;

typedef struct ABL_MemoryCapability_t_
{
    u16 nFlashType;                                              ///< Nand/Nor flash
    u16 nMemoryType;                                             ///< Flash-Dram combinations\n
                                                                 ///<     Type1: Nor(Page)+Psram(Page)/Nor(Burst)+Psram(Page)\n
                                                                 ///<     Type2: Nor(Page)+Psram(Burst)/Nor(Burst)+Psram(Burst)\n
                                                                 ///<     Type3: Nand+Sdram
    u16 nMemoryConfig;                                           ///< 128x32/64x32 configuration
    u16 nChipType;
} ABL_MemoryCapability_t;

//Sync definition with SysPlatformChipType_e (bsp.h)
typedef enum ABL_PlatformChipType_e_
{
    ABL_PLATFORM_CHIPTYPE_8533C = 0x0,
    ABL_PLATFORM_CHIPTYPE_8533C1,
    ABL_PLATFORM_CHIPTYPE_8533N,
    ABL_PLATFORM_CHIPTYPE_8536N,
    ABL_PLATFORM_CHIPTYPE_8830C,
    ABL_PLATFORM_CHIPTYPE_8830N,
    ABL_PLATFORM_CHIPTYPE_8533D,
    ABL_PLATFORM_CHIPTYPE_8532B,
    ABL_PLATFORM_CHIPTYPE_8532B2,
    ABL_PLATFORM_CHIPTYPE_8533BN,
    ABL_PLATFORM_CHIPTYPE_8533BD,
    ABL_PLATFORM_CHIPTYPE_8556,
    ABL_PLATFORM_CHIPTYPE_8556R,
    ABL_PLATFORM_CHIPTYPE_8556R2,
    ABL_PLATFORM_CHIPTYPE_8556M,
    ABL_PLATFORM_CHIPTYPE_8556M2,
    ABL_PLATFORM_CHIPTYPE_NUM
} ABL_PlatformChipType_e;

typedef enum ABL_CpuPerformance_e_
{
    ABL_CPU_PERFORMANCE_START = 0,
    ABL_CPU_PERFORMANCE_POOR = ABL_CPU_PERFORMANCE_START,
    ABL_CPU_PERFORMANCE_NORMAL,
    ABL_CPU_PERFORMANCE_GOOD,
    ABL_CPU_PERFORMANCE_INVALID
} ABL_CpuPerformance_e;

typedef struct ABL_CpuInfo_t_
{
    ABL_CpuPerformance_e eCpuPerformance;
} ABL_CpuInfo_t;

typedef void (*NotifyApp)(u32 uCusData, void *pEvtInfo);
/*=============================================================*/
// Function Declarations
/*=============================================================*/
esl_AudFormat_e ABL_RemapAudFormat(ABL_AudFormat_e eAudFormat);
void ABL_RegisterEvt(ResMgr_AppId_e eAppId, u16 uEvt, u32 uCusData, NotifyApp NotifyApp);
void ABL_DeregisterEvt(ResMgr_AppId_e eAppId, u16 uEvt);
ABL_CmnErrCode_e ABL_RegisterEvtGroup(ResMgr_AppId_e eAppId, u16 uEvtGroup, u32 uCusData, NotifyApp NotifyApp);
ABL_CmnErrCode_e ABL_DeregisterEvtGroup(ResMgr_AppId_e eAppId, u16 uEvtGroup);
ABL_CmnErrCode_e ABL_DeregisterEvtGroupCompareEntirely(ResMgr_AppId_e eAppId, u16 uEvtGroup, u32 uCusData, NotifyApp NotifyAppFunc);
void ABL_RegisterEvtByMask(ResMgr_AppId_e eAppId, u16 uEvtGroup, u32 uEvtMask, u32 uCusData, NotifyApp NotifyApp);
void ABL_DeregisterEvtByMask(ResMgr_AppId_e eAppId, u16 uEvtGroup, u32 uEvtMask);

void ABL_RegDeviceChangedCB(ResMgr_AppId_e eAppId, u32 uCusData, MediaCtrl_DeviceChanged pFn);
void ABL_RegBtStatusChangedCnfCb(ResMgr_AppId_e eAppId, BtStatusChangedCb pFn);
ABL_CmnErrCode_e ABL_ForceResume(ResMgr_AppId_e eAppId);
void ABL_Finalize(ResMgr_AppId_e eAppId);

void ABL_InitResMgr(ResMgr_TaskId_e eTaskId, u32 uMailBox);
void ABL_ConfigCmdMgr(ResMgr_TaskId_e eTaskId, ResMgr_CmdMgrConfig_t tCmdMgrConfig);
void ABL_UninitResMgr(ResMgr_TaskId_e eTaskId);
bool ABL_ParseResMgrMsg(void *pMessage);
bool ABL_IsFormatSupport(ResMgr_AppId_e eAppId, Media_FormatGroup_e eGroup, Media_Format_e eFormat, bool *pSupport);
bool ABL_IsPlaybackFormatSupport(ResMgr_AppId_e eAppId, Media_Format_e eFormat, bool *pSupport);
bool ABL_EmuMaxRomSize(ResMgr_AppId_e eAppId, u32 *pMaxSize);
/*
For video recording
*/
bool ABL_IsVdoCodecSupport(ResMgr_AppId_e eAppId, Media_VdoCodec_e eVdoCodec, bool *pSupport);
bool ABL_IsAudCodecSupport(ResMgr_AppId_e eAppId, Media_AudCodec_e eAudCodec, bool *pSupport);
bool ABL_IsVdoEncFpsSupport(ResMgr_AppId_e eAppId, Media_VdoEncodeFps_e eVdoEncFps, bool *pSupport);
bool ABL_IsVdoEncResSupport(ResMgr_AppId_e eAppId, Media_VdoCodec_e eVdoCodec, Media_VdoEncodeRes_e eVdoEncRes, bool *pSupport);

bool ABL_GetMmlConcurrntSectionTable(ResMgr_AppId_e eAppId, u32 *pAddr);
ABL_CmnErrCode_e ABL_GetMemoryCapability(ResMgr_AppId_e eAppId, ABL_MemoryCapability_t *pMemCapability);
ABL_CmnErrCode_e ABL_GetCpuPerformance(ResMgr_AppId_e eAppId, ABL_CpuInfo_t *pCpuPerformance);

/*
For ring buffer
*/
void ABL_RingBuffInit(ResMgr_AppId_e eAppId, u32 uBufferSize, ResMgr_RingBuff_t *pRingBuffInfo);
void ABL_RingBuffUninit(ResMgr_AppId_e eAppId, ResMgr_RingBuffHdl_t pRingBuffHdl);
ABL_CmnErrCode_e ABL_RingBuffPush(ResMgr_AppId_e eAppId, ResMgr_RingBuffHdl_t pRingBuffHdl, void *pUserData, u32 uDataSize);
ABL_CmnErrCode_e ABL_RingBuffPop(ResMgr_AppId_e eAppId, ResMgr_RingBuffHdl_t pRingBuffHdl, void *pUserData, u32 uDataSize);
ABL_CmnErrCode_e ABL_RingBuffGetInfo(ResMgr_AppId_e eAppId, ResMgr_RingBuffHdl_t pRingBuffHdl, ABL_RingBuffInfo_e eInfoType, u32 *pOutVal);
//This API only support B3 for now
void ABL_RingBuffSetDataEnd(ResMgr_AppId_e eAppId, ResMgr_RingBuffHdl_t pRingBuffHdl);
/*
To parse codec info from wave/mp3 header and remove it
*/
ABL_CmnErrCode_e ABL_RetrieveBuffInfo(ResMgr_AppId_e eAppId, Media_Format_e eDataFormat, void *pUserData, u32 uDataSize, u8 *pCacheBuf, Media_AudCodecInfo_t *pCodecInfo);

void ABL_Init(void);

#endif //__SRV_RESMGR_CMN_H__
