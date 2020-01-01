//==============================================================================
//
//  File        : ahc_video.h
//  Description : INCLUDE File for the AHC video function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_VIDEO_H_
#define _AHC_VIDEO_H_

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "Customer_config.h"
#include "ahc_common.h"
#include "AHC_Config_SDK.h"
#include "ahc_dcf.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/

#define AHC_VIDRECD_TIME_INCREMENT_BASE         (1001)      //29.97fps  stSnrFps.ulTimeIncre
#define AHC_VIDRECD_TIME_INCREMENT_BASE_NTSC    (1000)      //30fps
#define AHC_VIDRECD_TIME_INCREMENT_BASE_PAL     (1200)

/*===========================================================================
 * Enum define
 *===========================================================================*/

// Note that these enumerates must be group in video, audio and movie order.
// leave the naming such as AHC_CLIP for better comparison with CarDV code base.
typedef enum _AHC_MOVIE_CONFIG 
{
    /* Video Config */
    AHC_MAX_PFRAME_NUM = 0,
    AHC_MAX_BFRAME_NUM,
    AHC_MAX_BRC_QSCALE,
    AHC_VIDEO_RESOLUTION,
    AHC_FRAME_RATE,
    AHC_FRAME_RATEx10,
    AHC_VIDEO_BITRATE,
    AHC_VIDEO_2ND_BITRATE,
    AHC_VIDEO_CODEC_TYPE,
    AHC_VIDEO_CODEC_TYPE_SETTING,   // VIDENC_PROFILE
    AHC_VIDEO_COMPRESSION_RATIO,
    AHC_VIDEO_RESERVED_SIZE,
    AHC_VIDEO_STREAMING,            // AHC_STREAMING_MODE
    AHC_VIDEO_USAGE,
    AHC_VIDEO_CONFIG_MAX,
    /* Audio Config */
    AHC_AUD_MUTE_END = 100,
    AHC_AUD_SAMPLE_RATE,
    AHC_AUD_CHANNEL_CONFIG,         // AHC_AUDIO_CHANNEL_CONFIG, not number of channels
    AHC_AUD_BITRATE,
    AHC_AUD_CODEC_TYPE,
    AHC_AUD_PRERECORD_DAC,
    AHC_AUD_STREAMING,
    AHC_AUD_CONFIG_MAX,
    /* Movie Config */
    AHC_CLIP_CONTAINER_TYPE = 200,
    AHC_VIDEO_PRERECORD_LENGTH,
    AHC_VIDEO_PRERECORD_STATUS,
    AHC_MOVIE_CONFIG_MAX
} AHC_MOVIE_CONFIG;

typedef enum _AHC_MOVIE_CAPTURE_CMD 
{
    AHC_CAPTURE_CLIP_PAUSE = 0,
    AHC_CAPTURE_CLIP_RESUME,
    AHC_CAPTURE_SNAPSHOT
} AHC_MOVIE_CAPTURE_CMD;

typedef enum _AHC_MOVIE_CONFIG_PARAM 
{
    AHC_MOVIE_CONTAINER_3GP = 0,
    AHC_MOVIE_CONTAINER_AVI,
    AHC_MOVIE_CONTAINER_TS,
    
    AHC_MOVIE_VIDEO_CODEC_NONE,
    AHC_MOVIE_VIDEO_CODEC_MPEG4,
    AHC_MOVIE_VIDEO_CODEC_H264,
    AHC_MOVIE_VIDEO_CODEC_MJPEG,
    AHC_MOVIE_VIDEO_CODEC_YUV422,
    
    AHC_MOVIE_AUDIO_CODEC_START,
    AHC_MOVIE_AUDIO_CODEC_AAC,      ///< Video encode with AAC audio
    AHC_MOVIE_AUDIO_CODEC_ADPCM,    ///< Video encode with ADPCM audio
    AHC_MOVIE_AUDIO_CODEC_MP3,      ///< Video encode with MP3 audio
    AHC_MOVIE_AUDIO_CODEC_G711,     ///< Video encode with G.711 audio
    AHC_MOVIE_AUDIO_CODEC_PCM,      ///< Video encode with PCM audio
    AHC_MOVIE_AUDIO_CODEC_END
} AHC_MOVIE_CONFIG_PARAM;

typedef enum _AHC_VIDRECD_CMD
{
    AHC_VIDRECD_IDLE,               
    AHC_VIDRECD_INIT,               ///< Init the sensor and possible relevant previewing image flow pipe
    AHC_VIDRECD_START,
    AHC_VIDRECD_STOP,
    AHC_VIDRECD_PRERECD,
    AHC_VIDRECD_MAX
} AHC_VIDRECD_CMD;

typedef enum _AHC_VIDRECD_RESOL 
{
    AHC_VIDRECD_RESOL_640x360 = 0,
    AHC_VIDRECD_RESOL_640x480,
    AHC_VIDRECD_RESOL_720x480,
    AHC_VIDRECD_RESOL_848x480,
    AHC_VIDRECD_RESOL_960x720,
    AHC_VIDRECD_RESOL_1024x576,
    AHC_VIDRECD_RESOL_1280x720,
    AHC_VIDRECD_RESOL_1280x960,
    AHC_VIDRECD_RESOL_1472x736,
    AHC_VIDRECD_RESOL_1440x1088,
    AHC_VIDRECD_RESOL_1600x900,
    AHC_VIDRECD_RESOL_1920x960,
    AHC_VIDRECD_RESOL_1920x1088,
    AHC_VIDRECD_RESOL_2304x1296,
    AHC_VIDRECD_RESOL_2560x1280,
    AHC_VIDRECD_RESOL_2560x1440,
    AHC_VIDRECD_RESOL_2704x1536,
    AHC_VIDRECD_RESOL_3008x1504,
    AHC_VIDRECD_RESOL_3200x1808,
    AHC_VIDRECD_RESOL_3840x2160,
    AHC_VIDRECD_RESOL_AUTO,
    AHC_VIDRECD_RESOL_MAX
} AHC_VIDRECD_RESOL;

typedef enum _AHC_VIDEO_USAGE_e
{
    AHC_VIDEO_USAGE_RECD = 0,
    AHC_VIDEO_USAGE_STREAM,
    AHC_VIDEO_USAGE_NUM
} AHC_VIDEO_USAGE_e;

typedef enum _AHC_KERNAL_EMERGENCY_STOP_STEP{
    AHC_KERNAL_EMERGENCY_RECORD,
    AHC_KERNAL_EMERGENCY_STOP,
    AHC_KERNAL_EMERGENCY_AHC_DONE
} AHC_KERNAL_EMERGENCY_STOP_STEP;

typedef enum _AHC_VIDRECD_MODE_API 
{
    AHC_VIDRECD_MODE_API_CLOSE_PREVIOUS_FILE = 0,
    AHC_VIDRECD_MODE_API_CYCLIC_DELETE_FILES,
    AHC_VIDRECD_MODE_API_MISC_PREPROCESS,
    AHC_VIDRECD_MODE_API_SET_PROFILE,
    AHC_VIDRECD_MODE_API_SET_BITRATE,
    AHC_VIDRECD_MODE_API_SET_CONTAINER_TYPE,
    AHC_VIDRECD_MODE_API_SET_FRAMERATE,
    AHC_VIDRECD_MODE_API_SET_P_BFRAME_COUNT,
    AHC_VIDRECD_MODE_API_SET_AUDIO_ENCODE,
    AHC_VIDRECD_MODE_API_SET_TIME_LIMIT,
    AHC_VIDRECD_MODE_API_SET_DUALENCODE,
    AHC_VIDRECD_MODE_API_START_PRE_ENCODE,
    AHC_VIDRECD_MODE_API_PRESET_FILENAME,
    AHC_VIDRECD_MODE_API_REGISTER_CALLBACK,
    AHC_VIDRECD_MODE_API_SET_SEAMLESS,
    AHC_VIDRECD_MODE_API_SET_EMERGENCY,
    AHC_VIDRECD_MODE_API_PREADD_FILENAME,
    AHC_VIDRECD_MODE_API_START_RECORD,
    AHC_VIDRECD_MODE_API_POSTSET_FILENAME,
    AHC_VIDRECD_MODE_API_MISC_POSTPROCESS,
    AHC_VIDRECD_MODE_API_EXCEPTION_HANDLER, //Note: Must be the last.

    AHC_VIDRECD_MODE_API_MAX
} AHC_VIDRECD_MODE_API;

typedef enum _AHC_VIDRECD_FLOW_TYPE 
{
    AHC_VIDRECD_FLOW_TYPE_PREVIEW_TO_RECORD = 0, 
    AHC_VIDRECD_FLOW_TYPE_PREVIEW_TO_PRERECORD, 
    AHC_VIDRECD_FLOW_TYPE_PRERECORD_TO_RECORD, 
    AHC_VIDRECD_FLOW_TYPE_SEAMLESS_START_NEXT_RECORD, 
    
    AHC_VIDRECD_FLOW_TYPE_MAX
} AHC_VIDRECD_FLOW_TYPE;

typedef enum _AHC_VIDRECD_FILENAME_TYPE
{
    AHC_VIDRECD_FILENAME_PRMREC,
    AHC_VIDRECD_FILENAME_SCDREC,
    AHC_VIDRECD_FILENAME_USBREC,
    AHC_VIDRECD_FILENAME_PRMEMER,
    AHC_VIDRECD_FILENAME_SCDEMER,
    AHC_VIDRECD_FILENAME_USBEMER,
    AHC_VIDRECD_FILENAME_PRMSHARE,
    AHC_VIDRECD_FILENAME_MAX
} AHC_VIDRECD_FILENAME_TYPE;

/*===========================================================================
 * Structure define
 *===========================================================================*/

typedef UINT16 AHC_VIDEO_FORMAT;            // Maps to MMPS_3GPRECD_VIDEO_FORMAT
typedef UINT16 AHC_AUDIO_FORMAT;            // Maps to MMPS_3GPRECD_AUDIO_FORMAT
typedef UINT16 AHC_CONTAINER;               // Maps to VIDMGR_CONTAINER_TYPE
typedef UINT16 AHC_AUDIO_CHANNEL_CONFIG;    // Maps to AHC_AUDIO_CHANNEL_CONFI
typedef UINT16 AHC_VIDEO_FORMAT_SETTING;    // Maps to VIDENC_PROFILE or other format setting.

typedef AHC_BOOL (*pfAHC_VIDEO_SetRecordModeAPI)(void);

typedef struct _AHC_VIDRECD_MODE_ACTION_LIST {
    pfAHC_VIDEO_SetRecordModeAPI pfahcVidSetRecModeAPI[AHC_VIDRECD_MODE_API_MAX];
} AHC_VIDRECD_MODE_ACTION_LIST;

typedef struct _AHC_VIDEO_RECD_CMD_STATE {
    AHC_VIDRECD_CMD             ahcVidRecdCmdState;
    AHC_BOOL                    (* pfStateExec) (void* pthis, AHC_VIDRECD_CMD ahcNewVidRecdCmdState);    
    AHC_VIDRECD_CMD             (* pfGetCmdState) (void* pthis);
} AHC_VIDEO_RECD_CMD_STATE;

typedef struct _AHC_VIDEO_RECD_CONTEXT {
    AHC_VIDEO_RECD_CMD_STATE*   pAhcCurVidRecdCmdState;
    void                        (* pfSetState) (AHC_VIDEO_RECD_CMD_STATE *pNext);    
    AHC_VIDEO_RECD_CMD_STATE*   (* pfGetState) (void);
    AHC_BOOL                    (* pfSetRecordMode) (void* pthis, AHC_VIDRECD_CMD bStartRecord);
} AHC_VIDEO_RECD_CONTEXT;

typedef struct _AHC_VIDEO_FILENAME_MGR {
    UINT8 u8FileName[MAX_PURE_FILENAME_SIZE];
    UINT8 u8FullName[MAX_FULL_FILENAME_SIZE];
    UINT8 u8State;      // Useless, TBD
    UINT8 u8DeviceStatus;
    UINT8 (*pfGetCnntStatus)(void);
} AHC_VIDEO_FILENAME_MGR;

/*===========================================================================
 * Function prototype
 *===========================================================================*/

/* Movie Config Function */
AHC_BOOL    AHC_VIDEO_GetMovieCfg(UINT16 i, AHC_MOVIE_CONFIG wCommand, UINT32 *wOp);
AHC_BOOL    AHC_VIDEO_SetMovieCfg(UINT16 i, AHC_MOVIE_CONFIG wCommand, UINT32 wOp);
AHC_BOOL    AHC_VIDEO_CaptureClipCmd(UINT16 wCommand, UINT16 wOp);
UINT32      AHC_VIDEO_GetVideoBitrate(int type);
UINT32      AHC_VIDEO_GetVideoRealFpsX1000(UINT32 Frate);

/* Record Zoom Function */
AHC_BOOL    AHC_VIDEO_GetCurZoomStep(UINT16 *usZoomStepNum);
AHC_BOOL    AHC_VIDEO_GetMaxZoomStep(UINT16 *usMaxZoomStep);
AHC_BOOL    AHC_VIDEO_GetMaxZoomRatio(UINT16 *usMaxZoomRatio);
MMP_UBYTE   AHC_VIDEO_GetCurZoomStatus(void);
AHC_BOOL    AHC_VIDEO_GetDigitalZoomRatio(UINT32 *usZoomRatio);

/* Record Common Function */
AHC_BOOL    AHC_VIDEO_WaitVideoWriteFileFinish(void);
void        AHC_VIDEO_RecordStartWriteInfo(void);
void        AHC_VIDEO_RecordStopWriteInfo(void);
#if ( FS_FORMAT_FREE_ENABLE )
AHC_BOOL    AHC_FF_SetFileNameSlot(MMP_BYTE *byFilename, DCF_CAM_ID byCamID);
#endif
void        AHC_VIDEO_SetNightMode(MMP_UBYTE ubSnrSel, AHC_BOOL bEnable, MMP_ULONG ulMinFPS);
void        AHC_VIDEO_GetNightMode(AHC_BOOL *pbEnable);
void        AHC_VIDEO_SetSlowMotionFPS(AHC_BOOL bEnable, UINT32 usTimeIncrement, UINT32 usTimeIncrResol);
void        AHC_VIDEO_GetSlowMotionFPS(AHC_BOOL *pbEnable, UINT32 *pusTimeIncrement, UINT32 *pusTimeIncrResol);
#if (defined(VIDEO_REC_TIMELAPSE_EN) && VIDEO_REC_TIMELAPSE_EN == 1)
void        AHC_VIDEO_SetTimeLapseFPS(AHC_BOOL bEnable, UINT32 usTimeIncrement, UINT32 usTimeIncrResol);
void        AHC_VIDEO_GetTimeLapseFPS(AHC_BOOL *pbEnable, UINT32 *pusTimeIncrement, UINT32 *pusTimeIncrResol);
void        AHC_VIDEO_GetTimeLapseBitrate(UINT32 ulFrameRate, UINT32 ulTimeLapseSetting, UINT32 *pulVidBitRate, UINT32 *pulAudBitRate);
#endif

void        AHC_VIDEO_SetRecCardSlowStop(AHC_BOOL bState);
AHC_BOOL    AHC_VIDEO_GetRecCardSlowStop(void);
void        AHC_VIDEO_SetAPStopRecord(AHC_BOOL bState);
AHC_BOOL    AHC_VIDEO_GetAPStopRecord(void);
void        AHC_VIDEO_SetAPStopRecordTime(UINT32 ulLastRecdVidTime, UINT32 ulLastRecdAudTime);
AHC_BOOL    AHC_VIDEO_GetAPStopRecordTime(UINT32 *pulLastRecdVidTime, UINT32 *pulLastRecdAudTime);

void        AHC_VIDEO_SetRecdDeleteFileEn(AHC_BOOL bDeleteFile);
AHC_BOOL    AHC_VIDEO_GetRecdDeleteFileEn(void);
void        AHC_VIDEO_SetFirstTimeRecord(AHC_BOOL bFirstRecordSetFile);
AHC_BOOL    AHC_VIDEO_GetFirstTimeRecord(void);

UINT8*      AHC_VIDEO_GetPrevRecFullName(void);
AHC_BOOL    AHC_VIDEO_DeleteDcfMinKeyFile(AHC_BOOL bFirstTime, const char *ext);
void        AHC_VIDEO_GetRecStorageSpaceNeed(UINT32 ulVidBitRate, UINT32 ulAudBitRate, UINT32 ulTimelimit, UINT64 *pulSpaceNeeded);
void        AHC_VIDEO_SetVRSeamless(AHC_BOOL bSeamless);
AHC_BOOL    AHC_VIDEO_IsVRSeamless(void);
UINT16      AHC_VIDEO_GetCurRecDirKey(void);
UINT8*      AHC_VIDEO_GetCurPrmRecdFileName(AHC_BOOL bFullName);

/* Record Time Function */
void        AHC_VIDEO_AvailableRecTimeEx(UINT32 bitrate, UBYTE* Hour, UBYTE* Min, UBYTE* Sec);
AHC_BOOL    AHC_VIDEO_GetCurRecordingTime(UINT32 *ulTime);
UINT32      AHC_VIDEO_GetRecTimeLimitEx(void);
UINT32      AHC_VIDEO_SetRecTimeLimit(UINT32 ulTimeLimit);
AHC_BOOL    AHC_VIDEO_ChangeCurFileTimeLimit(UINT32 ulTimeLimitMs);

/* Record Audio Function */
AHC_BOOL    AHC_VIDEO_GetRecVolumeParam(UINT8* pubDgain, UINT8* pubAGain);
AHC_BOOL    AHC_VIDEO_GetRecVolume(ULONG* piDGain, ULONG* piLAGain, ULONG* piRAGain);
AHC_BOOL    AHC_VIDEO_SetRecVolumeParam(UINT8 ubDgain, UINT8 ubAGain);
AHC_BOOL    AHC_VIDEO_SetRecVolumeByMenuSetting(AHC_BOOL bEnable);
UINT32      AHC_VIDEO_GetAudioSamplingRate(UINT8 uiAudioType);
AHC_BOOL    AHC_VIDEO_SetRecVolumeToFW(AHC_BOOL bEnable);
UINT32      AHC_VIDEO_GetDefaultAudioSamplingRate(void);
AHC_BOOL    AHC_VIDEO_ConfigAudio(UINT16 stream, AHC_AUDIO_FORMAT aFormat, AHC_AUDIO_CHANNEL_CONFIG channelConfig);
void        AHC_VIDEO_SetRecWithWNR(AHC_BOOL bEnable);
      
/* Normal Record/Preview Function */
void        AHC_VIDEO_SetRecordModeAudioOn(UINT8 bAudioOn);
UINT8       AHC_VIDEO_GetRecordModeAudioOn(void);
void        AHC_VIDEO_SetRecordModeDeleteFile(AHC_BOOL bDeleteFile);
AHC_BOOL    AHC_VIDEO_GetRecordModeDeleteFile(void);

AHC_BOOL    AHC_VIDEO_SetRecordModeInitParameters(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeSetBitRate(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeSetProfile(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeSetContainerType(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeSetFrameRate(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeSetP_BFrameCount(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeSetAudioEncode(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeSetTimeLimit(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeSetDualEncode(void);
AHC_BOOL    AHC_VIDEO_SetRecordModePreSetFilename(void);
AHC_BOOL    AHC_VIDEO_SetRecordModePostSetFilename(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeRegisterCallback(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeMiscPreprocess(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeMiscPostprocess(void);
AHC_BOOL    AHC_VIDEO_SetRecordModePreAddFilename(void);
AHC_BOOL    AHC_VIDEO_SetRecordModePreAddFilenameFails(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeSetSeamless(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeSetEmergency(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeInitCommon(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeUnInitCommon(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeInit(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeUnInit(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeStartRecd(void);
AHC_BOOL    AHC_VIDEO_SetRecordEnterPreEncode(void);
AHC_BOOL    AHC_VIDEO_CyclicDeleteFiles(void);
AHC_BOOL    AHC_VIDEO_ClosePreviousFile(void);
AHC_BOOL    AHC_VIDEO_DelPreviousFile(void);
AHC_BOOL    AHC_VIDEO_RestartRecMode(void);
AHC_BOOL    AHC_VIDEO_SetRecordMode(AHC_VIDRECD_CMD bStartRecord);

AHC_BOOL    AHC_VIDEO_SetRecordExceptionHandler(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeRegisterInit(void *pfExternalAPI);
AHC_BOOL    AHC_VIDEO_SetRecordModeRegisterUnInit(void *pfExternalAPI);
AHC_BOOL    AHC_VIDEO_SetRecordModeRegisterAction(AHC_VIDRECD_FLOW_TYPE ahcVidRecFlowType, AHC_VIDRECD_MODE_API ahcVidRecModeAPI, void *pfExternalAPI);
AHC_BOOL    AHC_VIDEO_SetRecordModeExecActionList(AHC_VIDRECD_FLOW_TYPE ahcVidRecFlowType);

AHC_VIDRECD_CMD AHC_VIDEO_GetCmdState(void* pthis);
AHC_BOOL    AHC_VIDEO_RecdCmdStateExecIdle(void* pthis, AHC_VIDRECD_CMD ahcNewVidRecdCmdState);
AHC_BOOL    AHC_VIDEO_RecdCmdStateExecInit(void* pthis, AHC_VIDRECD_CMD ahcNewVidRecdCmdState);
AHC_BOOL    AHC_VIDEO_RecdCmdStateExecStart(void* pthis, AHC_VIDRECD_CMD ahcNewVidRecdCmdState);
AHC_BOOL    AHC_VIDEO_RecdCmdStateExecPreRecd(void* pthis, AHC_VIDRECD_CMD ahcNewVidRecdCmdState);
AHC_BOOL    AHC_VIDEO_RecdCmdStateExecStop(void* pthis, AHC_VIDRECD_CMD ahcNewVidRecdCmdState);

AHC_BOOL    AHC_VIDEO_StopRecordModeExStopRec(void);
AHC_BOOL    AHC_VIDEO_StopRecordModeExStopPreview(void);
AHC_BOOL    AHC_VIDEO_StopRecordModeExStopSensor(void);

void        AHC_VIDEO_RecdContextSetState(AHC_VIDEO_RECD_CMD_STATE *pNextState);
AHC_VIDEO_RECD_CMD_STATE* AHC_VIDEO_RecdContextGetState(void);
AHC_BOOL    AHC_VIDEO_RecdContextSetRecordMode(void* pthis, AHC_VIDRECD_CMD bStartRecord);    

/* Emergency Record Function */
AHC_BOOL    AHC_VIDEO_IsEmergRecStarted(void);
AHC_BOOL    AHC_VIDEO_SetEmergRecStarted(AHC_BOOL bEmerRecordStarted);
AHC_BOOL    AHC_VIDEO_IsEmergPostDone(void);
AHC_BOOL    AHC_VIDEO_SetEmergPostDone(AHC_BOOL);
AHC_BOOL    AHC_VIDEO_StartEmergRecord(void);
AHC_BOOL    AHC_VIDEO_GetEmergRecTime(UINT32 *uiTime);
AHC_BOOL    AHC_VIDEO_GetEmergRecTimeOffset(UINT32 *uiTime);
AHC_BOOL    AHC_VIDEO_GetEmergRecFileName(UINT8 ** filename, AHC_BOOL bFullFileName);
AHC_BOOL    AHC_VIDEO_SetEmergRecInterval(UINT32 uiInterval);
UINT32      AHC_VIDEO_GetEmergRecInterval(void);
AHC_BOOL    AHC_VIDEO_EmergRecPostProcess(void);
AHC_BOOL    AHC_VIDEO_EmergRecPostProcessMediaError(void);
AHC_BOOL    AHC_VIDEO_StopEmergRecord(void);
void        AHC_VIDEO_SetNormal2Emergency(AHC_BOOL bState);
void        AHC_VIDEO_SetDelNormFileAfterEmerg(UINT8 enable);
UINT8       AHC_VIDEO_NeedDeleteNormalAfterEmerg(void);

AHC_BOOL    AHC_VIDEO_GetNormal2Emergency(void);
AHC_BOOL    AHC_VIDEO_SetKernalEmergStopStep(AHC_KERNAL_EMERGENCY_STOP_STEP bKernalEmergencyStopStep);
AHC_KERNAL_EMERGENCY_STOP_STEP AHC_VIDEO_GetKernalEmergStopStep(void);

/* Share Record Function */
#if (AHC_SHAREENC_SUPPORT)
AHC_BOOL    AHC_VIDEO_SetShareRecdResIdx(MMP_USHORT usResIdx);
AHC_BOOL    AHC_VIDEO_SetShareRecdStarted(AHC_BOOL bStarted);
AHC_BOOL    AHC_VIDEO_IsShareRecdStarted(void);
AHC_BOOL    AHC_VIDEO_SetShareRecdFileName(UINT8 *pu8InFileName, AHC_BOOL bFullFileName);
AHC_BOOL    AHC_VIDEO_GetShareRecdFileName(UINT8** ppu8FileName, AHC_BOOL bFullFileName);
AHC_BOOL    AHC_VIDEO_SetShareRecdTimeLimit(UINT32 u32Interval);
AHC_BOOL    AHC_VIDEO_GetSharePreEncDuration(MMP_ULONG *pulDurationMs);
AHC_BOOL    AHC_VIDEO_StartSharePreRecord(void);
AHC_BOOL    AHC_VIDEO_StartShareRecord(void);
AHC_BOOL    AHC_VIDEO_StopShareRecord(void);
#endif

/* Dual Record Function */
UINT8       AHC_VIDEO_CheckScdRecdEnabled(UINT8 ubCamType, AHC_BOOL bChkConnect);

/* Parking Mode Function */
AHC_BOOL    AHC_VIDEO_SetRecordModeInitParkingMode(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeUnInitParkingMode(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeSetEmergencyParkingMode(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeSetAudioEncodeParkingMode(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeSetTimeLimitParkingMode(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeSetBitRateParkingMode(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeRegisterCallbackParkingMode(void);
AHC_BOOL    AHC_VIDEO_CyclicDeleteFilesParkingMode(void);
UINT32      AHC_VIDEO_GetRecTimeLimitParkingMode(void);
AHC_BOOL    AHC_VIDEO_SetRecordModeSetSeamlessParkingMode(void);
AHC_BOOL    AHC_VIDEO_ParkingModePostProcess(void);

#endif //_AHC_VIDEO_H_
