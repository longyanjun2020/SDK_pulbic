//==============================================================================
//
//  File        : AHC_video.c
//  Description : AHC video function
//  Author      :
//  Revision    : 1.0
//
//==============================================================================

/*===========================================================================
 * Include files
 *===========================================================================*/

#include "Customer_config.h"
#include "AHC_Config_SDK.h"
#include "aihc_dcf.h"
#include "ahc_adas.h"
#include "ahc_video.h"
#include "ahc_audio.h"
#include "ahc_capture.h"
#include "ahc_datetime.h"
#include "ahc_gsensor.h"
#include "ahc_preview.h"
#include "ahc_message.h"
#include "ahc_stream.h"
#include "ahc_usb.h"
#include "ahc_usbhost.h"
#include "ahc_media.h"
#include "ahc_sensor.h"
#include "ahc_uf.h"
#include "ahc_dcf.h"
#include "ahc_gui.h"
#include "ahc_callback.h"
#include "ahc_general.h"
#include "ahc_menu.h"
#include "ahc_utility.h"
#include "ahc_warningmsg.h"
#include "aihc_protection_inc.h"
#include "ptz_cfg.h"
#include "snr_cfg.h"
#include "mdtc_cfg.h"
#include "mmps_iva.h"
#include "mmps_dsc.h"
#include "mmps_3gprecd.h"
#include "mmps_audio.h"
#include "mmps_aui.h"
#include "mmps_fs.h"
#include "mmps_sensor.h"
#include "mmpf_vr_thumb.h"
#include "mmpf_display.h"
#include "mmpf_usbh_uvc.h"

#if (GPS_CONNECT_ENABLE)
#include "gps_ctl.h"
#endif
#if (GSENSOR_CONNECT_ENABLE)
#include "GSensor_ctrl.h"
#endif
#include "MenuSetting.h"
#include "statevideofunc.h"
#include "drawstatevideofunc.h"
#include "parkingmodectrl.h"

#if defined(WIFI_PORT) && (WIFI_PORT == 1)
#include "netapp.h"
#endif
#include "mmp_component_ctl.h"
#include "mmp_vidrec_inc.h"
#include "component_cfg.h"
#include "component_jpe.h"
#include "cust_component_cfg.h"

/*===========================================================================
 * Macro Define
 *===========================================================================*/

// Max number of videos used in this code base
#define AHC_MAX_VIDEO           (AHC_VIDEO_USAGE_NUM)
#define AHC_MAX_AUDIO           (AHC_VIDEO_USAGE_NUM)

typedef UINT16 AHC_MEDIA_USAGE;

// Definition of AHC_MEDIA_USAGE. bit 0 is for switching the media on or off.
// bit 1 ~ 7 is for bit mapped configuration
// @Warning Be careful about the condition check, 0x40 still means this media is disabled.
#define AHC_MEDIA_DISABLE       ((AHC_MEDIA_USAGE)0x00)  // General disabling
#define AHC_MEDIA_ENABLE        ((AHC_MEDIA_USAGE)0x01)  // General enabling
#define AHC_MEDIA_STREAMING     ((AHC_MEDIA_USAGE)0x10)  // Output to network

//For Video Record
#define SIGNLE_FILE_SIZE_LIMIT_4G           (0xFFFFFFFF)
#define SIGNLE_FILE_SIZE_LIMIT_3_75G        (0xF0000000)
#define SIGNLE_FILE_SIZE_LIMIT_3_5G         (0xE0000000)

#define VR_GET_CPU_TEMP_EN                  (0)

#if (VR_GET_CPU_TEMP_EN)
#define SETREG16(addr, a)       ( (*(volatile u16 *)(addr)) |= a )
#define CLRREG16(addr, a)       ( (*(volatile u16 *)(addr)) &= ~a )
#define INREG16(addr)           (*(volatile u16 *)(addr))
#define mdelay(x)               MsOS_DelayTask(x)
#define BASE_REG_RIU_PA         0x1F000000
#define BK_REG(reg)             ((reg) << 2)
#define GET_BASE_ADDR_BY_BANK(x, y)         ((x) + ((y) << 1))
#define BASE_REG_PMSAR_PA       GET_BASE_ADDR_BY_BANK(BASE_REG_RIU_PA, 0x1400)
#define BASE_REG_PMSLEEP_PA     GET_BASE_ADDR_BY_BANK(BASE_REG_RIU_PA, 0x0E00)
#define REG_ID_00               BK_REG(0x00)
#define REG_ID_10               BK_REG(0x10)
#define REG_ID_19               BK_REG(0x19)
#define REG_ID_2F               BK_REG(0x2F)
#define REG_ID_46               BK_REG(0x46)
#define REG_ID_64               BK_REG(0x64)
#endif

#define AHC_VIDRECD_RESOL_TO_VIDRECD_RESOL(c) (\
                c == AHC_VIDRECD_RESOL_640x360    ? VIDRECD_RESOL_640x368    :    \
                c == AHC_VIDRECD_RESOL_640x480    ? VIDRECD_RESOL_640x480    :    \
                c == AHC_VIDRECD_RESOL_720x480    ? VIDRECD_RESOL_720x480    :    \
                c == AHC_VIDRECD_RESOL_848x480    ? VIDRECD_RESOL_848x480    :    \
                c == AHC_VIDRECD_RESOL_960x720    ? VIDRECD_RESOL_960x720    :    \
                c == AHC_VIDRECD_RESOL_1024x576   ? VIDRECD_RESOL_1024x576   :    \
                c == AHC_VIDRECD_RESOL_1280x720   ? VIDRECD_RESOL_1280x720   :    \
                c == AHC_VIDRECD_RESOL_1280x960   ? VIDRECD_RESOL_1280x960   :    \
                c == AHC_VIDRECD_RESOL_1472x736   ? VIDRECD_RESOL_1472x736   :    \
                c == AHC_VIDRECD_RESOL_1440x1088  ? VIDRECD_RESOL_1440x1088  :    \
                c == AHC_VIDRECD_RESOL_1600x900   ? VIDRECD_RESOL_1600x900   :    \
                c == AHC_VIDRECD_RESOL_1920x960   ? VIDRECD_RESOL_1920x960   :    \
                c == AHC_VIDRECD_RESOL_1920x1088  ? VIDRECD_RESOL_1920x1088  :    \
                c == AHC_VIDRECD_RESOL_2304x1296  ? VIDRECD_RESOL_2304x1296  :    \
                c == AHC_VIDRECD_RESOL_2560x1280  ? VIDRECD_RESOL_2560x1280  :    \
                c == AHC_VIDRECD_RESOL_2560x1440  ? VIDRECD_RESOL_2560x1440  :    \
                c == AHC_VIDRECD_RESOL_2704x1536  ? VIDRECD_RESOL_2704x1536  :    \
                c == AHC_VIDRECD_RESOL_3008x1504  ? VIDRECD_RESOL_3008x1504  :    \
                c == AHC_VIDRECD_RESOL_3200x1808  ? VIDRECD_RESOL_3200x1808  :    \
                c == AHC_VIDRECD_RESOL_3840x2160  ? VIDRECD_RESOL_3840x2160  :    \
                VIDRECD_RESOL_MAX_NUM)

/*===========================================================================
 * Structure
 *===========================================================================*/

// Properties of a single video
typedef struct _AHC_VIDEO_PROPERTY {
    AHC_MEDIA_USAGE                 Usage;
    AHC_VIDEO_FORMAT                CodecType;          // Map to MMPS_3GPRECD_VIDEO_FORMAT
    AHC_VIDEO_FORMAT_SETTING        sCodecTypeSetting;  // Map to VIDENC_PROFILE or other format setting.
    UINT32                          FrmRateIdx;         // FPS, e.g. VIDRECD_FRAMERATE_30FPS
    UINT32                          FPSx10;             // FPSx10, 75 means 7.5FPS
    UINT32                          Bitrate;            // Video[0] always uses 3GP config as bitrate. Only other videos use this field.
    UINT32                          nMaxP;              // Max number of P frames
    UINT32                          nMaxB;              // Max number of B frames
    UINT32                          nMaxQP;             // Max QP 51
    UINT32                          CompressRatio;      // Compression ratio, e.g. VIDRECD_QUALITY_HIGH
    UINT32                          ReservedSize;       // Reserved size
    UINT32                          ResolIdx;           // Encode resolution Index, e.g. VIDRECD_RESOL_1920x1088
    AHC_BOOL                        bStreaming;         // Back up the status only. for quicker status reference
} AHC_VIDEO_PROPERTY;

// Properties of a single audio
typedef struct _AHC_AUDIO_PROPERTY {
    AHC_MEDIA_USAGE                 Usage;
    AHC_AUDIO_FORMAT                CodecType;          // Map to MMPS_3GPRECD_AUDIO_FORMAT;
    UINT32                          SampleRate;
    UINT32                          Bitrate;
    UINT32                          ChannelType;
    AHC_BOOL                        bPreRecordDAC;
    AHC_BOOL                        bMute;
    AHC_BOOL                        bStreaming;         // Back up the status only. for quicker status reference
} AHC_AUDIO_PROPERTY;

// Property sets of the video used in this. This video includes audio information.
typedef struct _AHC_MOVIE {
    UINT16                          nVideo;             // Number of video
    UINT16                          nAudio;             // Number of audio
    AHC_CONTAINER                   ContainerType;      // Map to VIDMGR_CONTAINER_TYPE.
    AHC_BOOL                        PreRecordStatus;
    UINT32                          PreRecordLength;    // PreEncode length, Unit ms
    AHC_VIDEO_PROPERTY              v[AHC_MAX_VIDEO];
    AHC_AUDIO_PROPERTY              a[AHC_MAX_AUDIO];
} AHC_MOVIE;

/*===========================================================================
 * Structure define
 *===========================================================================*/

// This function type should aligned with MMPF_VIDMGR_WriteFile()
typedef MMP_ERR (VR_WRITEFUNC)(void *buf, MMP_ULONG size, MMP_ULONG *wr_size, MMP_ULONG u32FileID);

/*===========================================================================
 * Global variable
 *===========================================================================*/

static AHC_MOVIE m_sMovieConfig =
{
    0,                          // nVideo
    0,                          // nAudio
    VIDMGR_CONTAINER_3GP,       // ContainerType
    AHC_FALSE,                  // PreRecordStatus
    10000,                      // PreRecordLength
    {
        {   AHC_MEDIA_DISABLE,              // Usage
            MMPS_3GPRECD_VIDEO_FORMAT_H264, // CodecType
            H264ENC_BASELINE_PROFILE,       // sCodecTypeSetting
            VIDRECD_FRAMERATE_30FPS,        // SampleRate
            300,                            // FPSx10
            0,                              // Bitrate
            14,                             // nMaxP
            0,                              // nMaxB
            51,                             // nMaxQP
            VIDRECD_QUALITY_HIGH,           // CompressRatio
            2*1024*1024,                    // ReservedSize
            VIDRECD_RESOL_1920x1088,        // Resolution
            AHC_FALSE                       // bStreaming
        },
        #if (AHC_MAX_VIDEO >= 2)
        {   AHC_MEDIA_DISABLE,              // Usage
            MMPS_3GPRECD_VIDEO_FORMAT_MJPEG,// CodecType
            H264ENC_BASELINE_PROFILE,       // sCodecTypeSetting, No used
            VIDRECD_FRAMERATE_30FPS,        // SampleRate
            300,                            // FPSx10
            0,                              // Bitrate
            0,                              // nMaxP
            0,                              // nMaxB
            51,                             // nMaxQP
            VIDRECD_QUALITY_HIGH,           // CompressRatio
            1*1024*1024,                    // ReservedSize
            VIDRECD_RESOL_640x368,          // Resolution
            AHC_FALSE                       // bStreaming
        },
        #endif
    },
    {   AHC_MEDIA_DISABLE,                  // Usage
        MMPS_3GPRECD_AUDIO_FORMAT_AAC,      // CodecType
        16000,                              // SampleRate
        32000,                              // Bitrate
        1,                                  // ChannelType
        AHC_TRUE,                           // bPreRecordDAC
        AHC_FALSE,                          // bMute
        AHC_FALSE                           // bStreaming
    }
};

// FileName MGR
static UINT8 AHC_VIDEO_GetPrmCamCnntStatus(void);
static UINT8 AHC_VIDEO_GetScdCamCnntStatus(void);
static UINT8 AHC_VIDEO_GetUSBCamCnntStatus(void);

static AHC_VIDEO_FILENAME_MGR m_stAhcVRFileNameMgr[AHC_VIDRECD_FILENAME_MAX] =
{
    {{0}, {0}, 0, 0, AHC_VIDEO_GetPrmCamCnntStatus},
    {{0}, {0}, 0, 0, AHC_VIDEO_GetScdCamCnntStatus},
    {{0}, {0}, 0, 0, AHC_VIDEO_GetUSBCamCnntStatus},
    {{0}, {0}, 0, 0, AHC_VIDEO_GetPrmCamCnntStatus},
    {{0}, {0}, 0, 0, AHC_VIDEO_GetScdCamCnntStatus},
    {{0}, {0}, 0, 0, AHC_VIDEO_GetUSBCamCnntStatus},
    {{0}, {0}, 0, 0, AHC_VIDEO_GetPrmCamCnntStatus}
};

MMP_BOOL                        m_bTestSeamlessSlowCard = MMP_FALSE;

static MMPS_3GPRECD_FRAMERATE   m_stAhcSlowMotionMgrFps = {1000, 30000};
static MMP_BOOL                 m_bAhcSlowMotionEn = MMP_FALSE;
static MMPS_3GPRECD_FRAMERATE   m_stAhcTimeLapseEncFps = {1000, 30000};
static MMP_BOOL                 m_bAhcTimeLapseEn = MMP_FALSE;

#if (AHC_ENABLE_VIDEO_STICKER)
static UINT32                   m_u32AhcTimeStampBufIdx  = 0;
#endif

MMP_USHORT                      gsStillZoomIndex = 0xFFFF;

static AHC_BOOL                 m_bAhcNightModeEn = MMP_FALSE;
static AHC_BOOL                 m_bAhcSeamlessRecd = AHC_FALSE;

static AHC_RTC_TIME             m_stAhcVidRecdStartRtcTime = {0};
#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
static AHC_RTC_TIME             m_stAhcEmergRecdStartRtcTime = {0};
#endif

#if (VR_SLOW_CARD_DETECT)
static AHC_BOOL                 m_bAhcCardSlowDetected = AHC_FALSE;
#endif
static AHC_BOOL                 m_bAhcCardSlowStopRecd = AHC_FALSE;
static AHC_BOOL                 m_bAhcAPStopRecord = AHC_FALSE;
static UINT32                   m_u32AhcAPStopRecdVidTime = 0;
static UINT32                   m_u32AhcAPStopRecdAudTime = 0;

static AHC_BOOL                 m_bAhcFirstRecdSetFile = AHC_TRUE;
static AHC_BOOL                 m_bAhcDeleteFileEn = AHC_FALSE;
static AHC_BOOL                 m_bAhcVidRecdStateWhenDecSnrPlug = AHC_FALSE;

static UINT32                   m_u32VidRecordW[2] = {0, 0};
static UINT32                   m_u32VidRecordH[2] = {0, 0};

static VR_WRITEFUNC             *VR_WriteFunc = NULL;

/* FileName */
static MMP_BYTE                 m_bPrevPrmRecdFullName[MAX_FULL_FILENAME_SIZE];
static UINT16                   m_u16CurVideoDirKey = 0;

#if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE)
static UINT32                   glThumbFileId = NULL;
static UINT8                    m_ThumbJpgFileName[MAX_PURE_FILENAME_SIZE];
static MMP_BYTE                 m_CurThumbJpgFullName[MAX_FULL_FILENAME_SIZE];
static UINT8                    m_chEmerThumbFileName[MAX_PURE_FILENAME_SIZE];
static MMP_BYTE                 m_chEmerThumbFullName[MAX_FULL_FILENAME_SIZE];
static UINT8                    m_ThumbJpgFileName_Rear[MAX_PURE_FILENAME_SIZE];
static MMP_BYTE                 m_CurThumbJpgFullName_Rear[MAX_FULL_FILENAME_SIZE];
static UINT8                    m_chEmerThumbFileName_Rear[MAX_PURE_FILENAME_SIZE];
static MMP_BYTE                 m_chEmerThumbFullName_Rear[MAX_FULL_FILENAME_SIZE];
static UINT8                    m_ThumbJpgFileName_USBH[MAX_PURE_FILENAME_SIZE];
static MMP_BYTE                 m_CurThumbJpgFullName_USBH[MAX_FULL_FILENAME_SIZE];
static UINT8                    m_chEmerThumbFileName_USBH[MAX_PURE_FILENAME_SIZE];
static MMP_BYTE                 m_chEmerThumbFullName_USBH[MAX_FULL_FILENAME_SIZE];
#endif

#if (AHC_SHAREENC_SUPPORT)
static AHC_BOOL                 m_bStartShareVR = AHC_FALSE;
static AHC_BOOL                 m_bShareVRPostDone = AHC_TRUE;
MMP_BOOL                        m_bAhcFirstShareFile = AHC_FALSE;
static UINT32                   m_u32AhcShareRecdTimeLimit = 0;
static AHC_BOOL                 m_bAhcShareRecdStart = AHC_FALSE;
static MMP_USHORT               m_usAhcShareRecdResolIdx = VIDRECD_RESOL_640x480;
MMP_ULONG                       m_ulAhcSharePreEncTime = 0;
#endif

/* Emergency Record */
#if (EMER_RECORD_DUAL_WRITE_ENABLE == 1)
static AHC_KERNAL_EMERGENCY_STOP_STEP m_bKernalEmergencyStopStep = AHC_KERNAL_EMERGENCY_AHC_DONE;
static AHC_BOOL                 m_bEmerVRPostDone = AHC_TRUE;
static UINT32                   m_uiEmerRecordInterval;
static UINT16                   m_uwEmerVRDirKey;
#endif

MMP_BOOL                        m_bStartEmerVR = AHC_FALSE;
#if (AHC_EMERGENTRECD_SUPPORT)
static AHC_BOOL                 m_bNormal2Emergency = AHC_FALSE;
#endif
static UINT8                    m_bDelNormRecAfterEmr = AHC_FALSE;

/* Audio Record */
static UINT8                    m_bAhcVRAudioOn = 0;
static UINT8                    m_u8AhcAudioAGain = AHC_DEFAULT_VR_MIC_AGAIN;
static UINT8                    m_u8AhcAudioDGain = AHC_DEFAULT_VR_MIC_DGAIN;

/* Record Action */
static UINT32                   m_u32AhcVidRecdExceptionCode = AHC_VIDRECD_MODE_API_MAX;
pfAHC_VIDEO_SetRecordModeAPI    pfAhcVidSetRecModeInit = AHC_VIDEO_SetRecordModeInit;
pfAHC_VIDEO_SetRecordModeAPI    pfAhcVidSetRecModeUnInit = AHC_VIDEO_SetRecordModeUnInit;

AHC_VIDRECD_MODE_ACTION_LIST    gpfAhcVidSetRecModeActoinList[AHC_VIDRECD_FLOW_TYPE_MAX] =
{
    { //AHC_VIDRECD_FLOW_TYPE_PREVIEW_TO_RECORD
        NULL,                                       //AHC_VIDRECD_MODE_API_CLOSE_PREVIOUS_FILE = 0,
        NULL,                                       //AHC_VIDRECD_MODE_API_CYCLIC_DELETE_FILES,
        AHC_VIDEO_SetRecordModeMiscPreprocess,      //AHC_VIDRECD_MODE_API_MISC_PREPROCESS,
        AHC_VIDEO_SetRecordModeSetProfile,          //AHC_VIDRECD_MODE_API_SET_PROFILE,
        AHC_VIDEO_SetRecordModeSetBitRate,          //AHC_VIDRECD_MODE_API_SET_BITRATE,
        AHC_VIDEO_SetRecordModeSetContainerType,    //AHC_VIDRECD_MODE_API_SET_CONTAINER_TYPE,
        AHC_VIDEO_SetRecordModeSetFrameRate,        //AHC_VIDRECD_MODE_API_SET_FRAMERATE,
        AHC_VIDEO_SetRecordModeSetP_BFrameCount,    //AHC_VIDRECD_MODE_API_SET_P_BFRAME_COUNT,
        AHC_VIDEO_SetRecordModeSetAudioEncode,      //AHC_VIDRECD_MODE_API_SET_AUDIO_ENCODE,
        AHC_VIDEO_SetRecordModeSetTimeLimit,        //AHC_VIDRECD_MODE_API_SET_TIME_LIMIT,
        AHC_VIDEO_SetRecordModeSetDualEncode,       //AHC_VIDRECD_MODE_API_SET_DUALENCODE,
        NULL,                                       //AHC_VIDRECD_MODE_API_START_PRE_ENCODE
        AHC_VIDEO_SetRecordModePreSetFilename,      //AHC_VIDRECD_MODE_API_PRESET_FILENAME,
        AHC_VIDEO_SetRecordModeRegisterCallback,    //AHC_VIDRECD_MODE_API_REGISTER_CALLBACK,
        AHC_VIDEO_SetRecordModeSetSeamless,         //AHC_VIDRECD_MODE_API_SET_SEAMLESS,
        AHC_VIDEO_SetRecordModeSetEmergency,        //AHC_VIDRECD_MODE_API_SET_EMERGENCY,
        AHC_VIDEO_SetRecordModePreAddFilename,      //AHC_VIDRECD_MODE_API_PREADD_FILENAME,
        AHC_VIDEO_SetRecordModeStartRecd,           //AHC_VIDRECD_MODE_API_START_RECORD,
        AHC_VIDEO_SetRecordModePostSetFilename,     //AHC_VIDRECD_MODE_API_POSTSET_FILENAME,
        AHC_VIDEO_SetRecordModeMiscPostprocess,     //AHC_VIDRECD_MODE_API_MISC_POSTPROCESS,
        AHC_VIDEO_SetRecordExceptionHandler,        //AHC_VIDRECD_MODE_API_EXCEPTION_HANDLER
    },

    { //AHC_VIDRECD_FLOW_TYPE_PREVIEW_TO_PRERECORD
        NULL,                                       //AHC_VIDRECD_MODE_API_CLOSE_PREVIOUS_FILE = 0,
        NULL,                                       //AHC_VIDRECD_MODE_API_CYCLIC_DELETE_FILES,
        AHC_VIDEO_SetRecordModeMiscPreprocess,      //AHC_VIDRECD_MODE_API_MISC_PREPROCESS,
        AHC_VIDEO_SetRecordModeSetProfile,          //AHC_VIDRECD_MODE_API_SET_PROFILE,
        AHC_VIDEO_SetRecordModeSetBitRate,          //AHC_VIDRECD_MODE_API_SET_BITRATE,
        AHC_VIDEO_SetRecordModeSetContainerType,    //AHC_VIDRECD_MODE_API_SET_CONTAINER_TYPE,
        AHC_VIDEO_SetRecordModeSetFrameRate,        //AHC_VIDRECD_MODE_API_SET_FRAMERATE,
        AHC_VIDEO_SetRecordModeSetP_BFrameCount,    //AHC_VIDRECD_MODE_API_SET_P_BFRAME_COUNT,
        AHC_VIDEO_SetRecordModeSetAudioEncode,      //AHC_VIDRECD_MODE_API_SET_AUDIO_ENCODE,
        AHC_VIDEO_SetRecordModeSetTimeLimit,        //AHC_VIDRECD_MODE_API_SET_TIME_LIMIT,
        AHC_VIDEO_SetRecordModeSetDualEncode,       //AHC_VIDRECD_MODE_API_SET_DUALENCODE,
        AHC_VIDEO_SetRecordEnterPreEncode,          //AHC_VIDRECD_MODE_API_START_PRE_ENCODE
        NULL,                                       //AHC_VIDRECD_MODE_API_PRESET_FILENAME,
        NULL,                                       //AHC_VIDRECD_MODE_API_REGISTER_CALLBACK,
        AHC_VIDEO_SetRecordModeSetSeamless,         //AHC_VIDRECD_MODE_API_SET_SEAMLESS,
        AHC_VIDEO_SetRecordModeSetEmergency,        //AHC_VIDRECD_MODE_API_SET_EMERGENCY,
        NULL,                                       //AHC_VIDRECD_MODE_API_PREADD_FILENAME,
        NULL,                                       //AHC_VIDRECD_MODE_API_START_RECORD,
        NULL,                                       //AHC_VIDRECD_MODE_API_POSTSET_FILENAME,
        NULL,                                       //AHC_VIDRECD_MODE_API_MISC_POSTPROCESS,
        AHC_VIDEO_SetRecordExceptionHandler,        //AHC_VIDRECD_MODE_API_EXCEPTION_HANDLER
    },

    { //AHC_VIDRECD_FLOW_TYPE_PRERECORD_TO_RECORD
        NULL,                                       //AHC_VIDRECD_MODE_API_CLOSE_PREVIOUS_FILE = 0,
        NULL,                                       //AHC_VIDRECD_MODE_API_CYCLIC_DELETE_FILES,
        NULL,                                       //AHC_VIDRECD_MODE_API_MISC_PREPROCESS,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_PROFILE,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_BITRATE,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_CONTAINER_TYPE,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_FRAMERATE,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_P_BFRAME_COUNT,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_AUDIO_ENCODE,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_TIME_LIMIT,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_DUALENCODE,
        NULL,                                       //AHC_VIDRECD_MODE_API_START_PRE_ENCODE
        AHC_VIDEO_SetRecordModePreSetFilename,      //AHC_VIDRECD_MODE_API_PRESET_FILENAME,
        AHC_VIDEO_SetRecordModeRegisterCallback,    //AHC_VIDRECD_MODE_API_REGISTER_CALLBACK,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_SEAMLESS,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_EMERGENCY,
        AHC_VIDEO_SetRecordModePreAddFilename,      //AHC_VIDRECD_MODE_API_PREADD_FILENAME,
        AHC_VIDEO_SetRecordModeStartRecd,           //AHC_VIDRECD_MODE_API_START_RECORD,
        AHC_VIDEO_SetRecordModePostSetFilename,     //AHC_VIDRECD_MODE_API_POSTSET_FILENAME,
        AHC_VIDEO_SetRecordModeMiscPostprocess,     //AHC_VIDRECD_MODE_API_MISC_POSTPROCESS,
        AHC_VIDEO_SetRecordExceptionHandler,        //AHC_VIDRECD_MODE_API_EXCEPTION_HANDLER
    },

    { //AHC_VIDRECD_FLOW_TYPE_SEAMLESS_START_NEXT_RECORD
        AHC_VIDEO_ClosePreviousFile,                //AHC_VIDRECD_MODE_API_CLOSE_PREVIOUS_FILE = 0,
        AHC_VIDEO_CyclicDeleteFiles,                //AHC_VIDRECD_MODE_API_CYCLIC_DELETE_FILES,
        AHC_VIDEO_SetRecordModeMiscPreprocess,      //AHC_VIDRECD_MODE_API_MISC_PREPROCESS,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_PROFILE,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_BITRATE,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_CONTAINER_TYPE,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_FRAMERATE,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_P_BFRAME_COUNT,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_AUDIO_ENCODE,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_TIME_LIMIT,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_DUALENCODE,
        NULL,                                       //AHC_VIDRECD_MODE_API_START_PRE_ENCODE
        AHC_VIDEO_SetRecordModePreSetFilename,      //AHC_VIDRECD_MODE_API_PRESET_FILENAME,
        NULL,                                       //AHC_VIDRECD_MODE_API_REGISTER_CALLBACK,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_SEAMLESS,
        NULL,                                       //AHC_VIDRECD_MODE_API_SET_EMERGENCY,
        AHC_VIDEO_SetRecordModePreAddFilename,      //AHC_VIDRECD_MODE_API_PREADD_FILENAME,
        AHC_VIDEO_SetRecordModeStartRecd,           //AHC_VIDRECD_MODE_API_START_RECORD,
        AHC_VIDEO_SetRecordModePostSetFilename,     //AHC_VIDRECD_MODE_API_POSTSET_FILENAME,
        NULL,                                       //AHC_VIDRECD_MODE_API_MISC_POSTPROCESS,
        AHC_VIDEO_SetRecordExceptionHandler,        //AHC_VIDRECD_MODE_API_EXCEPTION_HANDLER
    }
};

AHC_VIDEO_RECD_CMD_STATE gAhcVidRecdCmdStateIdle =
{
    AHC_VIDRECD_IDLE,
    AHC_VIDEO_RecdCmdStateExecIdle,
    AHC_VIDEO_GetCmdState
};

AHC_VIDEO_RECD_CMD_STATE gAhcVidRecdCmdStateInit =
{
    AHC_VIDRECD_INIT,
    AHC_VIDEO_RecdCmdStateExecInit,
    AHC_VIDEO_GetCmdState
};

AHC_VIDEO_RECD_CMD_STATE gAhcVidRecdCmdStateStart =
{
    AHC_VIDRECD_START,
    AHC_VIDEO_RecdCmdStateExecStart,
    AHC_VIDEO_GetCmdState
};

AHC_VIDEO_RECD_CMD_STATE gAhcVidRecdCmdStatePreRecd =
{
    AHC_VIDRECD_PRERECD,
    AHC_VIDEO_RecdCmdStateExecPreRecd,
    AHC_VIDEO_GetCmdState
};

AHC_VIDEO_RECD_CMD_STATE gAhcVidRecdCmdStateStop =
{
    AHC_VIDRECD_STOP,
    AHC_VIDEO_RecdCmdStateExecStop,
    AHC_VIDEO_GetCmdState
};

AHC_VIDEO_RECD_CONTEXT gAhcVidRecdContext =
{
    NULL,
    AHC_VIDEO_RecdContextSetState,
    AHC_VIDEO_RecdContextGetState,
    AHC_VIDEO_RecdContextSetRecordMode
};

/*===========================================================================
 * Extern variable
 *===========================================================================*/

#if (SUPPORT_ADAS)
extern MMP_ULONG    gulADASTimeLimit;
#endif

extern AHC_BOOL     gbAhcDbgBrk;

/*===========================================================================
 * Extern function
 *===========================================================================*/

static void AHC_VIDEO_SetScdRecdSetting(void);
UINT32 AHC_VIDEO_RecordPostWriteInfo(UINT32 u32FileID, UINT16 u16StreamType);
AHC_BOOL AIHC_DCFDT_DeleteFileInFS(PSDATETIMEDCFDB pDB, char* szFullPath, AHC_BOOL bIsFileReadOnly );
AHC_BOOL AHC_VIDEO_GetRecdResol(UINT8 u8CamSel, UINT32 *pu32SizeX, UINT32 *pu32SizeY);

extern void VRMotionDetectCB(void);
extern MMP_BOOL pcam_usb_get_timeStamp_status(void);

/*===========================================================================
 * Main body
 *===========================================================================*/

#if 0
void _____Camera_Status_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetPrmCamCnntStatus
//  Description :
//------------------------------------------------------------------------------
static UINT8 AHC_VIDEO_GetPrmCamCnntStatus(void)
{
    return (!CAM_CHECK_PRM(PRM_CAM_NONE));
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetScdCamCnntStatus
//  Description :
//------------------------------------------------------------------------------
static UINT8 AHC_VIDEO_GetScdCamCnntStatus(void)
{
    return ((!CAM_CHECK_SCD(SCD_CAM_NONE)) && (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_SCD, AHC_TRUE) & VID_RECD_STORE_FILE));
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetUSBCamCnntStatus
//  Description :
//------------------------------------------------------------------------------
static UINT8 AHC_VIDEO_GetUSBCamCnntStatus(void)
{
    return ((!CAM_CHECK_USB(USB_CAM_NONE)) && (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_TRUE) & VID_RECD_STORE_FILE));
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_UpdateCurCnntStatusByType
//  Description :
//------------------------------------------------------------------------------
static void AHC_VIDEO_UpdateCurCnntStatusByType(AHC_VIDRECD_FILENAME_TYPE eType)
{
    m_stAhcVRFileNameMgr[eType].u8DeviceStatus = m_stAhcVRFileNameMgr[eType].pfGetCnntStatus();
}

AHC_VIDEO_FILENAME_MGR* AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_TYPE type)
{
    return (AHC_VIDEO_FILENAME_MGR*)(&m_stAhcVRFileNameMgr[type]);
}

#if 0
void _____Movie_Config_Functions_____(){}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetMovieCfg
//  Description :
//------------------------------------------------------------------------------
/**
 * Set the config parameter of the movie

 This API configures both record and playback movie files

 Parameters:

 @param[in] i index of the media track if required.
 @param[in] wCommand Config type.
 @param[in] wOp      config value.
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_VIDEO_SetMovieCfg(UINT16 i, AHC_MOVIE_CONFIG wCommand, UINT32 wOp)
{
    char *szErr = NULL;

    if (wCommand < AHC_VIDEO_CONFIG_MAX) {
        if (i >= AHC_MAX_VIDEO) {
            szErr = "Video Stream";
            goto config_error;
        }
    }
    else if (wCommand < AHC_AUD_CONFIG_MAX) {
        if (i >= AHC_MAX_AUDIO) {
            szErr = "Audio Stream";
            goto config_error;
        }
    }

    switch(wCommand){
    case AHC_MAX_PFRAME_NUM:
        m_sMovieConfig.v[i].nMaxP = wOp;
        break;
    case AHC_MAX_BFRAME_NUM:
        m_sMovieConfig.v[i].nMaxB = 0;
        break;
    case AHC_MAX_BRC_QSCALE:
        m_sMovieConfig.v[i].nMaxQP = wOp;
        break;
    case AHC_VIDEO_RESOLUTION:
        m_sMovieConfig.v[i].ResolIdx = wOp;
        break;
    case AHC_FRAME_RATE:
    case AHC_FRAME_RATEx10:
        if (wCommand == AHC_FRAME_RATEx10) {
            wOp /= 10;
        }

        m_sMovieConfig.v[i].FPSx10 = wOp * 10;

        switch (wOp) {
        case 7:
            m_sMovieConfig.v[i].FrmRateIdx = VIDRECD_FRAMERATE_7d5FPS;
            m_sMovieConfig.v[i].FPSx10 = 75;
            break;
        case 10:
            m_sMovieConfig.v[i].FrmRateIdx = VIDRECD_FRAMERATE_10FPS;
            break;
        case 12:
            m_sMovieConfig.v[i].FrmRateIdx = VIDRECD_FRAMERATE_12FPS;
            break;
        case 15:
            m_sMovieConfig.v[i].FrmRateIdx = VIDRECD_FRAMERATE_15FPS;
            break;
        case 20:
            m_sMovieConfig.v[i].FrmRateIdx = VIDRECD_FRAMERATE_20FPS;
            break;
        case 24:
            m_sMovieConfig.v[i].FrmRateIdx = VIDRECD_FRAMERATE_24FPS;
            break;
        case 25:
            m_sMovieConfig.v[i].FrmRateIdx = VIDRECD_FRAMERATE_25FPS;
            break;
        case 30:
            m_sMovieConfig.v[i].FrmRateIdx = VIDRECD_FRAMERATE_30FPS;
            break;
        case 50:
            m_sMovieConfig.v[i].FrmRateIdx = VIDRECD_FRAMERATE_50FPS;
            break;
        case 60:
            m_sMovieConfig.v[i].FrmRateIdx = VIDRECD_FRAMERATE_60FPS;
            break;
        case 100:
            m_sMovieConfig.v[i].FrmRateIdx = VIDRECD_FRAMERATE_100FPS;
            break;
        case 120:
            m_sMovieConfig.v[i].FrmRateIdx = VIDRECD_FRAMERATE_120FPS;
            break;
        default:
            m_sMovieConfig.v[i].FrmRateIdx = VIDRECD_FRAMERATE_30FPS;
            break;
        }
        break;
    case AHC_VIDEO_BITRATE:
        m_sMovieConfig.v[i].Bitrate = wOp;
        break;
    case AHC_VIDEO_CODEC_TYPE:
        switch (wOp) {
        case AHC_MOVIE_VIDEO_CODEC_H264:
            wOp = MMPS_3GPRECD_VIDEO_FORMAT_H264;
            break;
        case AHC_MOVIE_VIDEO_CODEC_MJPEG:
            wOp = MMPS_3GPRECD_VIDEO_FORMAT_MJPEG;
            break;
        case AHC_MOVIE_VIDEO_CODEC_YUV422:
            wOp = MMPS_3GPRECD_VIDEO_FORMAT_YUV422;
            break;
        case AHC_MOVIE_VIDEO_CODEC_NONE:
            wOp = MMPS_3GPRECD_VIDEO_FORMAT_OTHERS;
            break;
        default:
            return AHC_FALSE;
            break;
        }

        m_sMovieConfig.v[i].CodecType = wOp;
        break;
    case AHC_VIDEO_CODEC_TYPE_SETTING:
        switch (m_sMovieConfig.v[i].CodecType) {
        case MMPS_3GPRECD_VIDEO_FORMAT_H264:
            wOp = (VIDENC_PROFILE)wOp;
            break;
        case MMPS_3GPRECD_VIDEO_FORMAT_MJPEG:
            break;
        case MMPS_3GPRECD_VIDEO_FORMAT_YUV422:
            break;
        case MMPS_3GPRECD_VIDEO_FORMAT_YUV420:
            break;
        default:
            break;
        }

        m_sMovieConfig.v[i].sCodecTypeSetting = wOp;
        break;
    case AHC_VIDEO_COMPRESSION_RATIO:
        m_sMovieConfig.v[i].CompressRatio = wOp;
        break;
    case AHC_VIDEO_RESERVED_SIZE:
        m_sMovieConfig.v[i].ReservedSize = wOp;
        break;
    case AHC_VIDEO_STREAMING:
        m_sMovieConfig.v[i].bStreaming = wOp;
        break;
    case AHC_VIDEO_USAGE:
        m_sMovieConfig.v[i].Usage = wOp;
        break;
    /* Audio Config */
    case AHC_AUD_MUTE_END:
        // Always ignore this value
        break;
    case AHC_AUD_SAMPLE_RATE:
        if ((wOp == 16000) || (wOp == 22050) || (wOp == 32000) || (wOp == 44100) || (wOp == 48000)) {
            m_sMovieConfig.a[i].SampleRate = wOp;
        }
        else {
            AHC_DBG_ERR(1, "UnSupport Audio Sample Rate [%d]\r\n", wOp);
        }
        break;
    case AHC_AUD_CHANNEL_CONFIG:
        if (AHC_AUDIO_CHANNEL_STEREO == wOp) {
            m_sMovieConfig.a[i].ChannelType = MMPS_AUDIO_LINEIN_DUAL;
        }
        else if (AHC_AUDIO_CHANNEL_MONO_R == wOp) {
            m_sMovieConfig.a[i].ChannelType = MMPS_AUDIO_LINEIN_R;
        }
        else if (AHC_AUDIO_CHANNEL_MONO_L == wOp) {
            m_sMovieConfig.a[i].ChannelType = MMPS_AUDIO_LINEIN_L;
        }
        else {
            return AHC_FALSE;
        }
        break;
    case AHC_AUD_BITRATE:
        m_sMovieConfig.a[i].Bitrate = wOp;
        break;
    case AHC_AUD_CODEC_TYPE:
        if (AHC_MOVIE_AUDIO_CODEC_AAC == wOp) {
            m_sMovieConfig.a[i].CodecType = MMPS_3GPRECD_AUDIO_FORMAT_AAC;
        }
        else if (AHC_MOVIE_AUDIO_CODEC_ADPCM == wOp) {
            m_sMovieConfig.a[i].CodecType = MMPS_3GPRECD_AUDIO_FORMAT_ADPCM;
        }
        else if (AHC_MOVIE_AUDIO_CODEC_MP3 == wOp) {
            m_sMovieConfig.a[i].CodecType = MMPS_3GPRECD_AUDIO_FORMAT_MP3;
        }
        #if 0
        else if (AHC_MOVIE_AUDIO_CODEC_G711 == wOp) {
            m_sMovieConfig.a[i].CodecType = wOp;
        }
        #endif
        else if (AHC_MOVIE_AUDIO_CODEC_PCM == wOp) {
            m_sMovieConfig.a[i].CodecType = MMPS_3GPRECD_AUDIO_FORMAT_PCM;
        }
        else {
            AHC_DBG_ERR(1, FG_RED("Unknown Audio Format [%d]\r\n"), wOp);
            return AHC_FALSE;
        }
        break;
    case AHC_AUD_PRERECORD_DAC:
        m_sMovieConfig.a[i].bPreRecordDAC = wOp;
        break;
    case AHC_AUD_STREAMING:
        m_sMovieConfig.a[i].bStreaming = wOp;
        break;
    /* Movie Config */
    case AHC_CLIP_CONTAINER_TYPE:
        if (AHC_MOVIE_CONTAINER_AVI == wOp) {
            m_sMovieConfig.ContainerType = VIDMGR_CONTAINER_AVI;
        }
        else if (AHC_MOVIE_CONTAINER_TS == wOp) {
            m_sMovieConfig.ContainerType = VIDMGR_CONTAINER_TS;
        }
        else if (AHC_MOVIE_CONTAINER_3GP == wOp) {
            m_sMovieConfig.ContainerType = VIDMGR_CONTAINER_3GP;
        }
        else {
            return AHC_FALSE;
        }
        break;
    case AHC_VIDEO_PRERECORD_LENGTH:
        m_sMovieConfig.PreRecordLength = wOp;
        break;
    case AHC_VIDEO_PRERECORD_STATUS:
        m_sMovieConfig.PreRecordStatus = wOp;
        break;
    default:
        szErr = "Command";

config_error:
        AHC_DBG_ERR(1, FG_RED("Invalid config %s.") "stream:%d command:%d\r\n", szErr, i, wCommand);
        return MMP_FALSE;
        break;
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetMovieCfg
//  Description :
//------------------------------------------------------------------------------
/**
 * Get the config parameter of the movie
 * @param i[in] index of the media track if required.
 * @param wCommand[in] parameter to be get
 * @param wOp[out] The pointer of the parameter. Typically UINT32 type.
 * @return AHC_TRUE if supported
 */
AHC_BOOL AHC_VIDEO_GetMovieCfg(UINT16 i, AHC_MOVIE_CONFIG wCommand, UINT32 *pu32Op)
{
    AHC_BOOL    bCheckAudio = AHC_FALSE;
    AHC_BOOL    bCheckVideo = AHC_FALSE;
    UINT32      u32Value = 0;

    switch(wCommand) {
    case AHC_MAX_PFRAME_NUM:
        bCheckVideo = AHC_TRUE;
        u32Value = m_sMovieConfig.v[i].nMaxP;
        break;
    case AHC_MAX_BFRAME_NUM:
        bCheckVideo = AHC_TRUE;
        u32Value = m_sMovieConfig.v[i].nMaxB;
        break;
    case AHC_MAX_BRC_QSCALE:
        bCheckVideo = AHC_TRUE;
        u32Value = m_sMovieConfig.v[i].nMaxQP;
        break;
    case AHC_VIDEO_RESOLUTION:
        bCheckVideo = AHC_TRUE;
        u32Value = m_sMovieConfig.v[i].ResolIdx;
        break;
    case AHC_FRAME_RATE:
        bCheckVideo = AHC_TRUE;
        u32Value = m_sMovieConfig.v[i].FrmRateIdx;
        break;
    case AHC_FRAME_RATEx10:
        bCheckVideo = AHC_TRUE;
        u32Value = m_sMovieConfig.v[i].FPSx10;
        break;
    case AHC_VIDEO_BITRATE:
        if (i == AHC_VIDEO_USAGE_STREAM) {
            u32Value = m_sMovieConfig.v[i].Bitrate;
            break;
        }

        bCheckVideo = AHC_TRUE;

        {
            UINT32 ulBitrate = 0;

        #if (MENU_MOVIE_FRAME_RATE_EN)
            switch(MenuSettingConfig()->uiMOVFrameRate)
            {
            #if (MENU_MOVIE_FRAME_RATE_30_EN)
                case MOVIE_FRAME_RATE_30FPS:
                    ulBitrate = MMPS_3GPRECD_GetPresetCfg()->ulFps30BitrateMap[m_sMovieConfig.v[i].ResolIdx][m_sMovieConfig.v[i].CompressRatio];
                break;
            #endif
            #if (MENU_MOVIE_FRAME_RATE_20_EN)
                case MOVIE_FRAME_RATE_20FPS:
                    ulBitrate = MMPS_3GPRECD_GetPresetCfg()->ulFps30BitrateMap[m_sMovieConfig.v[i].ResolIdx][m_sMovieConfig.v[i].CompressRatio]*2/3;
                break;
            #endif
            #if (MENU_MOVIE_FRAME_RATE_15_EN)
                case MOVIE_FRAME_RATE_15FPS:
                    ulBitrate = MMPS_3GPRECD_GetPresetCfg()->ulFps30BitrateMap[m_sMovieConfig.v[i].ResolIdx][m_sMovieConfig.v[i].CompressRatio]/2;
                break;
            #endif
            #if (MENU_MOVIE_FRAME_RATE_10_EN)
                case MOVIE_FRAME_RATE_10FPS:
                    ulBitrate = MMPS_3GPRECD_GetPresetCfg()->ulFps30BitrateMap[m_sMovieConfig.v[i].ResolIdx][m_sMovieConfig.v[i].CompressRatio]/3;
                break;
            #endif
            }
        #else
            if (VIDRECD_FRAMERATE_30FPS == m_sMovieConfig.v[i].FrmRateIdx) {
                ulBitrate = MMPS_3GPRECD_GetPresetCfg()->ulFps30BitrateMap[m_sMovieConfig.v[i].ResolIdx][m_sMovieConfig.v[i].CompressRatio];
            }
            else {
                ulBitrate = MMPS_3GPRECD_GetPresetCfg()->ulFps60BitrateMap[m_sMovieConfig.v[i].ResolIdx][m_sMovieConfig.v[i].CompressRatio];
            }
        #endif

            if (MenuSettingConfig()->uiMOVPreRecord == MOVIE_PRE_RECORD_ON)
            {
                if (ulBitrate > AHC_VIDEO_MAXBITRATE_PRERECORD)
                {
                    ulBitrate = AHC_VIDEO_MAXBITRATE_PRERECORD;
                }
            }

            u32Value = ulBitrate;
        }
        break;
    #if (AHC_SHAREENC_SUPPORT)
    case AHC_VIDEO_2ND_BITRATE:
        bCheckVideo = AHC_TRUE;
        if (VIDRECD_FRAMERATE_30FPS == m_sMovieConfig.v[i].FrmRateIdx) {
            u32Value = MMPS_3GPRECD_GetPresetCfg()->ulFps30BitrateMap[m_sMovieConfig.v[i].ResolIdx][m_sMovieConfig.v[i].CompressRatio];
        }
        else {
            u32Value = MMPS_3GPRECD_GetPresetCfg()->ulFps60BitrateMap[m_sMovieConfig.v[i].ResolIdx][m_sMovieConfig.v[i].CompressRatio];
        }
        break;
    #endif
    case AHC_VIDEO_CODEC_TYPE:
        bCheckVideo = AHC_TRUE;
        u32Value = m_sMovieConfig.v[i].CodecType;
        break;
    case AHC_VIDEO_CODEC_TYPE_SETTING:
        bCheckVideo = AHC_TRUE;

        switch (m_sMovieConfig.v[i].CodecType) {
            case MMPS_3GPRECD_VIDEO_FORMAT_H264:
                u32Value = (UINT32)m_sMovieConfig.v[i].sCodecTypeSetting;
                break;
            case MMPS_3GPRECD_VIDEO_FORMAT_MJPEG:
                break;
            case MMPS_3GPRECD_VIDEO_FORMAT_YUV422:
                break;
            case MMPS_3GPRECD_VIDEO_FORMAT_YUV420:
                break;
            default:
                break;
        }
        break;
    case AHC_VIDEO_COMPRESSION_RATIO:
        bCheckVideo = AHC_TRUE;
        u32Value = m_sMovieConfig.v[i].CompressRatio;
        break;
    case AHC_VIDEO_RESERVED_SIZE:
        bCheckVideo = AHC_TRUE;
        u32Value= m_sMovieConfig.v[i].ReservedSize;
        break;
    case AHC_VIDEO_STREAMING:
        bCheckVideo = AHC_TRUE;
        u32Value = m_sMovieConfig.v[i].bStreaming;
        break;
    case AHC_VIDEO_USAGE:
        bCheckVideo = AHC_TRUE;
        u32Value = m_sMovieConfig.v[i].Usage;
        break;
    /* Audio Config */
    case AHC_AUD_MUTE_END:
        bCheckAudio = AHC_TRUE;
        u32Value = m_sMovieConfig.a[i].bMute;
        break;
    case AHC_AUD_SAMPLE_RATE:
        bCheckAudio = AHC_TRUE;
        u32Value = m_sMovieConfig.a[i].SampleRate;
        break;
    case AHC_AUD_CHANNEL_CONFIG:
        bCheckAudio = AHC_TRUE;
        u32Value = m_sMovieConfig.a[i].ChannelType;
        break;
    case AHC_AUD_BITRATE:
        bCheckAudio = AHC_TRUE;
        u32Value = m_sMovieConfig.a[i].Bitrate;
        break;
    case AHC_AUD_CODEC_TYPE:
        bCheckAudio = AHC_TRUE;
        u32Value = m_sMovieConfig.a[i].CodecType;
        break;
    case AHC_AUD_PRERECORD_DAC:
        bCheckAudio = AHC_TRUE;
        u32Value = m_sMovieConfig.a[i].bPreRecordDAC;
        break;
    case AHC_AUD_STREAMING:
        bCheckAudio = AHC_TRUE;
        u32Value = m_sMovieConfig.a[i].bStreaming;
        break;
    /* Movie Config */
    case AHC_CLIP_CONTAINER_TYPE:
        u32Value = m_sMovieConfig.ContainerType;
        break;
    case AHC_VIDEO_PRERECORD_LENGTH:
        u32Value = m_sMovieConfig.PreRecordLength;
        break;
    case AHC_VIDEO_PRERECORD_STATUS:
        u32Value = m_sMovieConfig.PreRecordStatus;
        break;
    default:
        return AHC_FALSE;
        break;
    }

    if (bCheckAudio) {
        if (i >= AHC_MAX_AUDIO) {
            return AHC_FALSE;
        }
    }
    if (bCheckVideo) {
        if (i >= AHC_MAX_VIDEO) {
            return AHC_FALSE;
        }
    }

    if (pu32Op)
        *pu32Op = u32Value;

    return AHC_TRUE;
}

#if defined(VIDEO_REC_TIMELAPSE_EN) && (VIDEO_REC_TIMELAPSE_EN)
//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetTimeLapseBitrate
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_GetTimeLapseBitrate(UINT32 u32FrameRate, UINT32 u32TimeLapseSetting, UINT32 *pu32VidBitRate, UINT32 *pu32AudBitRate)
{
    UINT32 u32TimeLapseRatio = 0;

    switch(u32TimeLapseSetting) {
    case COMMON_VR_TIMELAPSE_5SEC:
        u32TimeLapseRatio = 5;
        break;
    case COMMON_VR_TIMELAPSE_10SEC:
        u32TimeLapseRatio = 10;
        break;
    case COMMON_VR_TIMELAPSE_30SEC:
        u32TimeLapseRatio = 30;
        break;
    case COMMON_VR_TIMELAPSE_60SEC:
        u32TimeLapseRatio = 60;
        break;
    default:
    case COMMON_VR_TIMELAPSE_1SEC:
        u32TimeLapseRatio = 1;
        break;
    }

    u32FrameRate = u32FrameRate * u32TimeLapseRatio;

    *pu32VidBitRate = (*pu32VidBitRate + u32FrameRate - 1) / u32FrameRate;
    *pu32AudBitRate = 0;   // Mute
}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetVideoBitrate
//  Description :
//------------------------------------------------------------------------------
UINT32 AHC_VIDEO_GetVideoBitrate(int nMenuType)
{
    MMP_ULONG ulResIdx = 0;
    MMP_ULONG ulFps = 30;

    switch (nMenuType) {
    #if(MENU_MOVIE_SIZE_4K_24P_EN)
    case MOVIE_SIZE_4K_24P:
        ulResIdx    = VIDRECD_RESOL_3200x1808;
        ulFps       = 24;
        break;
    #endif
    #if(MENU_MOVIE_SIZE_1440_30P_EN)
    case MOVIE_SIZE_1440_30P:
        ulResIdx    = VIDRECD_RESOL_2560x1440;
        ulFps       = 30;
        break;
    #endif
    #if(MENU_MOVIE_SIZE_SHD_30P_EN)
    case MOVIE_SIZE_SHD_30P:
        ulResIdx    = VIDRECD_RESOL_2304x1296;
        ulFps       = 30;
        break;
    #endif
    #if(MENU_MOVIE_SIZE_SHD_25P_EN)
    case MOVIE_SIZE_SHD_25P:
        ulResIdx    = VIDRECD_RESOL_2304x1296;
        ulFps       = 25;
        break;
    #endif
    #if(MENU_MOVIE_SIZE_SHD_24P_EN)
    case MOVIE_SIZE_SHD_24P:
        ulResIdx    = VIDRECD_RESOL_2304x1296;
        ulFps       = 24;
        break;
    #endif
    #if (MENU_MOVIE_SIZE_1080_60P_EN)
    case MOVIE_SIZE_1080_60P:
        ulResIdx    = VIDRECD_RESOL_1920x1088;
        ulFps       = 60;
        break;
    #endif
    #if (MENU_MOVIE_SIZE_1080_24P_EN)
    case MOVIE_SIZE_1080_24P:
        ulResIdx    = VIDRECD_RESOL_1920x1088;
        ulFps       = 24;
        break;
    #endif
    #if (MENU_MOVIE_SIZE_1080P_EN)
    case MOVIE_SIZE_1080P:
        ulResIdx    = VIDRECD_RESOL_1920x1088;
        ulFps       = 30;
        break;
    #endif
    #if (MENU_MOVIE_SIZE_900P_30P_EN)
    case MOVIE_SIZE_900P_30P:
        ulResIdx    = VIDRECD_RESOL_1600x900;
        ulFps       = 30;
        break;
    #endif
    #if (MENU_MOVIE_SIZE_960P_30P_EN)
    case MOVIE_SIZE_960P_30P:
        ulResIdx    = VIDRECD_RESOL_1280x960;
        ulFps       = 30;
        break;
    #endif
    #if (MENU_MOVIE_SIZE_720_60P_EN)
    case MOVIE_SIZE_720_60P:
        ulResIdx    = VIDRECD_RESOL_1280x720;
        ulFps       = 60;
        break;
    #endif
    #if (MENU_MOVIE_SIZE_720_24P_EN)
    case MOVIE_SIZE_720_24P:
        ulResIdx    = VIDRECD_RESOL_1280x720;
        ulFps       = 24;
        break;
    #endif
    #if(MENU_MOVIE_SIZE_720P_EN)
    case MOVIE_SIZE_720P:
        ulResIdx    = VIDRECD_RESOL_1280x720;
        ulFps       = 30;
        break;
    #endif
    #if(MENU_MOVIE_SIZE_VGA30P_EN)
    case MOVIE_SIZE_VGA_30P:
        ulResIdx    = VIDRECD_RESOL_640x480;
        ulFps       = 30;
        break;
    #endif
    case MOVIE_SIZE_360_30P:
        ulResIdx    = VIDRECD_RESOL_640x368;
        ulFps       = 30;
        break;
    default:
        ulResIdx    = VIDRECD_RESOL_1920x1088;
        ulFps       = 30;
        AHC_DBG_ERR(1, "ERR : Movie size\r\n");
        break;
    }

    if (ulFps == 60) {
        return MMPS_3GPRECD_GetPresetCfg()->ulFps60BitrateMap[ulResIdx][MenuSettingConfig()->uiMOVQuality];
    }
    else {
        return MMPS_3GPRECD_GetPresetCfg()->ulFps30BitrateMap[ulResIdx][MenuSettingConfig()->uiMOVQuality];
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetVideoRealFpsX1000
//  Description :
//------------------------------------------------------------------------------
UINT32 AHC_VIDEO_GetVideoRealFpsX1000(UINT32 u32FrateIdx)
{
    UINT32 u32RealFrameRate = 0;

    switch(u32FrateIdx)
    {
    case VIDRECD_FRAMERATE_7d5FPS:
        u32RealFrameRate = 7500;
        break;
    case VIDRECD_FRAMERATE_10FPS:
        u32RealFrameRate = 10000;
        break;
    case VIDRECD_FRAMERATE_12FPS:
        u32RealFrameRate = 12000;
        break;
    case VIDRECD_FRAMERATE_15FPS:
        u32RealFrameRate = 15000;
        break;
    case VIDRECD_FRAMERATE_20FPS:
        u32RealFrameRate = 20000;
        break;
    case VIDRECD_FRAMERATE_24FPS:
        u32RealFrameRate = 24000;
        break;
    case VIDRECD_FRAMERATE_25FPS:
        u32RealFrameRate = 25000;
        break;
    case VIDRECD_FRAMERATE_30FPS:
        u32RealFrameRate = 30000;
        break;
    case VIDRECD_FRAMERATE_50FPS:
        u32RealFrameRate = 50000;
        break;
    case VIDRECD_FRAMERATE_60FPS:
        u32RealFrameRate = 60000;
        break;
    case VIDRECD_FRAMERATE_100FPS:
        u32RealFrameRate = 100000;
        break;
    case VIDRECD_FRAMERATE_120FPS:
        u32RealFrameRate = 120000;
        break;
    default:
        u32RealFrameRate = 30000;
        break;
    }

    return u32RealFrameRate;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecdResol
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set capture resolution

 This API configures the captured resolution in selected mode.
 Parameters:
 @param[in] wSizeX Width.
 @param[in] wSizeY Height
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_VIDEO_SetRecdResol(UINT8 u8CamSel, UINT16 u16SizeX, UINT16 u16SizeY)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    if ((u16SizeX * u16SizeY) < (MIN_VIDEO_ENC_WIDTH * MIN_VIDEO_ENC_HEIGHT))
        return AHC_FALSE;
    if ((u16SizeX * u16SizeY) > (MAX_VIDEO_ENC_WIDTH * MAX_VIDEO_ENC_HEIGHT))
        return AHC_FALSE;

    m_u32VidRecordW[u8CamSel] = u16SizeX;
    m_u32VidRecordH[u8CamSel] = u16SizeY;

    eRetErr = MMPS_3GPRECD_CustomedEncResol(u8CamSel, MMP_SCAL_FITMODE_OUT, u16SizeX, u16SizeY);

    return (eRetErr == MMP_ERR_NONE) ? AHC_TRUE : AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetRecdResol
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Get capture resolution

 This API gets the captured resolution in selected mode.
 Parameters:
 @param[out] pu32SizeX Width.
 @param[out] pu32SizeY Height
 @retval AHC_TRUE Success.
*/
AHC_BOOL AHC_VIDEO_GetRecdResol(UINT8 u8CamSel, UINT32 *pu32SizeX, UINT32 *pu32SizeY)
{
    if (pu32SizeX)
        *pu32SizeX = m_u32VidRecordW[u8CamSel];
    if (pu32SizeY)
        *pu32SizeY = m_u32VidRecordH[u8CamSel];

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetNightMode
//  Description : ulMinFPS: 30, 24, 12, 8 ,4 (for IQ Table)
//------------------------------------------------------------------------------
void AHC_VIDEO_SetNightMode(MMP_UBYTE ubSnrSel, AHC_BOOL bEnable, MMP_ULONG ulMinFPS)
{
    m_bAhcNightModeEn = bEnable;

    MMPS_Sensor_SetNightMode(ubSnrSel, bEnable, ulMinFPS);

    if (bEnable) {
        MMPS_3GPRECD_SetMuxerConstFps(MMP_FALSE);
    }
    else {
        MMPS_3GPRECD_SetMuxerConstFps(MMP_TRUE);
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetNightMode
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_GetNightMode(AHC_BOOL *pbEnable)
{
    if (pbEnable)
        *pbEnable = m_bAhcNightModeEn;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetSlowMotionFPS
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_SetSlowMotionFPS(AHC_BOOL bEnable, UINT32 usTimeIncrement, UINT32 usTimeResol)
{
    m_bAhcSlowMotionEn = bEnable;

    m_stAhcSlowMotionMgrFps.ulTimeIncre = usTimeIncrement;
    m_stAhcSlowMotionMgrFps.ulTimeResol = usTimeResol;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetSlowMotionFPS
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_GetSlowMotionFPS(AHC_BOOL *pbEnable, UINT32 *pusTimeIncrement, UINT32 *pusTimeResol)
{
    if (pbEnable)
        *pbEnable = m_bAhcSlowMotionEn;

    if (pusTimeIncrement)
        *pusTimeIncrement = m_stAhcSlowMotionMgrFps.ulTimeIncre;
    if (pusTimeResol)
        *pusTimeResol = m_stAhcSlowMotionMgrFps.ulTimeResol;
}

#if (defined(VIDEO_REC_TIMELAPSE_EN) && VIDEO_REC_TIMELAPSE_EN == 1)
//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetTimeLapseFPS
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_SetTimeLapseFPS(AHC_BOOL bEnable, UINT32 usTimeIncrement, UINT32 usTimeResol)
{
    m_bAhcTimeLapseEn = bEnable;

    m_stAhcTimeLapseEncFps.ulTimeIncre = usTimeIncrement;
    m_stAhcTimeLapseEncFps.ulTimeResol = usTimeResol;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetTimeLapseFPS
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_GetTimeLapseFPS(AHC_BOOL *pbEnable, UINT32 *pusTimeIncrement, UINT32 *pusTimeResol)
{
    if (pbEnable)
        *pbEnable = m_bAhcTimeLapseEn;

    if (pusTimeIncrement)
        *pusTimeIncrement = m_stAhcTimeLapseEncFps.ulTimeIncre;
    if (pusTimeResol)
        *pusTimeResol = m_stAhcTimeLapseEncFps.ulTimeResol;
}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_IsVRSeamless
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_SetVRSeamless(AHC_BOOL bSeamless)
{
    if (bSeamless == AHC_TRUE) {
        MMPS_3GPRECD_SetSeamlessEnable(MMP_TRUE);
    }
    else {
        MMPS_3GPRECD_SetSeamlessEnable(MMP_FALSE);
    }

    m_bAhcSeamlessRecd = bSeamless;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_IsVRSeamless
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_IsVRSeamless(void)
{
    return m_bAhcSeamlessRecd;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetVRThumbAttr
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetVRThumbAttr(UINT32 ulThumbW, UINT32 ulThumbH)
{
#if (SUPPORT_VR_THUMBNAIL)
    MMPS_3GPRECD_SetVRThumbResol(ulThumbW, ulThumbH);

    #if (AHC_VR_THUMBNAIL_JPG_ENABLE)
        #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE)
        MMPS_3GPRECD_SetVRThumbEn(VR_THUMB_SKIP_ATOM, MMP_TRUE);
        #else
        MMPS_3GPRECD_SetVRThumbEn(VR_THUMB_SKIP_ATOM, MMP_FALSE);
        #endif
        MMPS_3GPRECD_SetVRThumbRingBufNum((EMER_RECORD_DUAL_WRITE_PRETIME * 2) + 1); // RingBufferNum = PreEncTime * 2 + 1
    #else
        MMPS_3GPRECD_SetVRThumbEn(VR_THUMB_DISABLE, MMP_FALSE);
        MMPS_3GPRECD_SetVRThumbRingBufNum(0);
    #endif
#else
    MMPS_3GPRECD_SetVRThumbEn(VR_THUMB_DISABLE, MMP_FALSE);
    MMPS_3GPRECD_SetVRThumbRingBufNum(0);
#endif
    return AHC_TRUE;
}

#if 0
void _____VR_Callback_Function_________(){ruturn;} //dummy
#endif

#define VR_WRITE_FUNC_CACHE  (1)
//------------------------------------------------------------------------------
//  Function    : VR_WriteFunc_Ex
//  Description :
//------------------------------------------------------------------------------
void VR_WriteFunc_Ex(UINT8* pData, UINT32 u32NumBytes, UINT32 *pu32WrittenBytes, UINT32 u32FileID, AHC_BOOL bLastData)
{
#if (VR_WRITE_FUNC_CACHE == 1)

    #define VR_WRITE_BUFFER_LENGTH (64*1024)

    static UINT8 u8DataBuffer[VR_WRITE_BUFFER_LENGTH];
    static UINT32 u32DataNumInBuf = 0;
    UINT32 u32WrittenSize = 0;

    if (pu32WrittenBytes)
        *pu32WrittenBytes = 0;

    if (u32FileID == 0) {
        return;
    }

    if (((pData == NULL) || (u32NumBytes == 0)) &&
        (!bLastData)) {
        return;
    }

    if (bLastData == AHC_FALSE)
    {
        if (u32NumBytes > VR_WRITE_BUFFER_LENGTH) // Write all data to media
        {
            VR_WriteFunc((void *)u8DataBuffer, u32DataNumInBuf, &u32WrittenSize, u32FileID);
            *pu32WrittenBytes = u32WrittenSize;
            u32DataNumInBuf = 0;
            VR_WriteFunc(pData, u32NumBytes, &u32WrittenSize, u32FileID);
            *pu32WrittenBytes += u32WrittenSize;
        }
        else if ((u32DataNumInBuf + u32NumBytes) >= VR_WRITE_BUFFER_LENGTH) // Write 64KB data to media
        {
            UINT32 ulRemainingSegment = (u32DataNumInBuf + u32NumBytes) - VR_WRITE_BUFFER_LENGTH;
            UINT32 ulWriteSegment = u32NumBytes - ulRemainingSegment;

            memcpy((UINT8*)(u8DataBuffer + u32DataNumInBuf), pData, ulWriteSegment);
            VR_WriteFunc((void *)u8DataBuffer, VR_WRITE_BUFFER_LENGTH, &u32WrittenSize, u32FileID);
            *pu32WrittenBytes = u32WrittenSize;
            memcpy((UINT8*)u8DataBuffer, (UINT8*)(pData + ulWriteSegment), ulRemainingSegment);
            u32DataNumInBuf = ulRemainingSegment;
        }
        else  // Keep all data in buffer
        {
            memcpy((UINT8*)(u8DataBuffer + u32DataNumInBuf), pData, u32NumBytes);
            u32DataNumInBuf += u32NumBytes;
            *pu32WrittenBytes = 0;
        }
    }
    else // Write all data to media
    {
        if ((u32DataNumInBuf + u32NumBytes) > VR_WRITE_BUFFER_LENGTH)
        {
            VR_WriteFunc((void *)u8DataBuffer, u32DataNumInBuf, &u32WrittenSize, u32FileID);
            *pu32WrittenBytes = u32WrittenSize;
            u32DataNumInBuf = 0;

            if (pData != NULL && u32NumBytes != 0)
            {
                VR_WriteFunc(pData, u32NumBytes, &u32WrittenSize, u32FileID);
                *pu32WrittenBytes += u32WrittenSize;
            }
        }
        else
        {
            if (pData != NULL && u32NumBytes != 0)
            {
                memcpy((UINT8*)(u8DataBuffer + u32DataNumInBuf), pData, u32NumBytes);
                u32DataNumInBuf += u32NumBytes;
            }

            if (u32DataNumInBuf)
            {
                VR_WriteFunc((void *)u8DataBuffer, u32DataNumInBuf, &u32WrittenSize, u32FileID);
                *pu32WrittenBytes = u32WrittenSize;
                u32DataNumInBuf = 0;
            }
        }
    }
#else
    VR_WriteFunc(pData, u32NumBytes, pu32WrittenBytes, u32FileID);
#endif
}

//------------------------------------------------------------------------------
//  Function    : VRAnaDecSnrSrcTypeHandler
//  Description : This Callback function will be called once TV source is changed or removed.
//------------------------------------------------------------------------------
static void VRAnaDecSnrSrcTypeHandler(MMP_UBYTE ubSrcType, MMP_UBYTE ubCamSel)
{
    MMP_BOOL bPrmRecdEn = MMP_FALSE;
    MMP_BOOL bScdRecdEn = MMP_FALSE;

    if (!CAM_CHECK_PRM(PRM_CAM_ANA_DECODER) && ubCamSel == gsAhcPrmSensor) {
        return;
    }
    else if (!CAM_CHECK_SCD(SCD_CAM_ANA_DECODER) && ubCamSel == gsAhcScdSensor) {
        return;
    }

    AHC_DBG_MSG(1, FG_GREEN("<VRAnaTypeCB> Typ[%d]\r\n"), ubSrcType);

    // PreKeep Video Record State
    MMPS_3GPRECD_GetRecordPipeStatus(gsAhcPrmSensor, &bPrmRecdEn);
    MMPS_3GPRECD_GetRecordPipeStatus(gsAhcScdSensor, &bScdRecdEn);

    m_bAhcVidRecdStateWhenDecSnrPlug = ((AHC_BOOL)(bPrmRecdEn || bScdRecdEn));

    if ((ubSrcType == MMP_SNR_ANADEC_SRC_NO_READY) ||
        (ubSrcType == MMP_SNR_ANADEC_SRC_DISCNT)) {

        // If camera is disconnect, the recording should stop.
        AHC_VIDEO_SetVRSeamless(AHC_FALSE);

        MMPS_Display_EnableScdAnaDecSnrPreviewWindow(MMPS_PREVIEW_UI_MODE_VR, MMP_FALSE);

        MMPS_3GPRECD_ScdCamPreviewStop(gsAhcScdSensor);

        MMPS_Display_EnableScdAnaDecSnrPreview(MMPS_PREVIEW_UI_MODE_VR, MMP_FALSE);
    }
    else {

        AHC_VIDEO_SetScdRecdSetting();

        MMPS_3GPRECD_AdjustScdRecdPipe(gsAhcScdSensor);
        MMPS_3GPRECD_AdjustScdPrevwPipe(gsAhcScdSensor);

        MMPS_Display_EnableScdAnaDecSnrPreview(MMPS_PREVIEW_UI_MODE_VR, MMP_TRUE);

        MMPS_3GPRECD_ScdCamPreviewStart(gsAhcScdSensor, MMP_FALSE);
    }

    AHC_SetCurKeyEventID(BUTTON_TV_DECODER_SRC_TYPE);
    AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_TV_DECODER_SRC_TYPE, 0);
}

#if 0
//------------------------------------------------------------------------------
//  Function    : VRAPStopRecordCB
//  Description :
//------------------------------------------------------------------------------
static void VRAPStopRecordCB(MMP_ULONG ulLastRecdVidTime, MMP_ULONG ulLastRecdAudTime)
{
    AHC_DBG_MSG(1, "<VRAPStopRecordCB> LastRecdVidTime [%d] LastRecdAudTime[%d]\r\n", ulLastRecdVidTime, ulLastRecdAudTime);

    AHC_VIDEO_SetAPStopRecord(AHC_TRUE);
    AHC_VIDEO_SetAPStopRecordTime(ulLastRecdVidTime, ulLastRecdAudTime);

    #if (GPS_CONNECT_ENABLE)
    if (AHC_GPS_Module_Attached())
    {
        UINT8 bGPS_en;

        if ((AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bGPS_en) == AHC_TRUE) &&
            (bGPS_en != COMMON_GPS_REC_INFO_OFF)) {
            MMPF_OS_SetFlags(UartCtrlFlag, GPS_FLAG_SWITCHBUFFER_CLOSE, MMPF_OS_FLAG_SET);
        }
    }
    #endif

    AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_VRCB_AP_STOP_VIDEO_RECD, 0);
}
#endif

//------------------------------------------------------------------------------
//  Function    : VRMediaFullCB
//  Description :
//------------------------------------------------------------------------------
static void VRMediaFullCB(void)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    AHC_DBG_MSG(1, FG_GREEN("<VRMediaFullCB>\r\n"));

    ahcRet = AHC_KeyEventIDCheckConflict(BUTTON_VRCB_MEDIA_FULL);
    if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return;}

    AHC_SetCurKeyEventID(BUTTON_VRCB_MEDIA_FULL);
    AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_VRCB_MEDIA_FULL, 0);
}

//------------------------------------------------------------------------------
//  Function    : VRPrmFileFullCB
//  Description :
//------------------------------------------------------------------------------
static void VRPrmFileFullCB(void)
{
#if 0 // Instead by seamless CB
    AHC_DBG_MSG(1, FG_GREEN("<VRPrmFileFullCB>\r\n"));

    ahcRet = AHC_KeyEventIDCheckConflict(BUTTON_VRCB_FILE_FULL);
    if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return;}

    AHC_SetCurKeyEventID(BUTTON_VRCB_FILE_FULL);
    AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_VRCB_FILE_FULL, 0);
#endif
}

//------------------------------------------------------------------------------
//  Function    : VRScdFileFullCB
//  Description :
//------------------------------------------------------------------------------
static void VRScdFileFullCB(void)
{
    if (MMPS_3GPRECD_IsShareRecordEn()) {
        #if (AHC_SHAREENC_SUPPORT)
#if 1
        AHC_BOOL ahcRet = AHC_TRUE;

        AHC_DBG_MSG(1, FG_GREEN("<VRScdFileFullCB>\r\n"));

        ahcRet = AHC_KeyEventIDCheckConflict(BUTTON_VRCB_SHARE_FILE_FULL);
        if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return;}

        AHC_SetCurKeyEventID(BUTTON_VRCB_SHARE_FILE_FULL);
        AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_VRCB_SHARE_FILE_FULL, 0);
#else
        AHC_VIDEO_FILENAME_MGR  *pstShareFileNameMgr;
        DCF_DB_TYPE             eDBType = AHC_UF_GetDB();

        pstShareFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_PRMSHARE);

        AHC_UF_SelectDB(DCF_DB_FORMAT_FREE_DB);
        AHC_UF_SizeinFile_Update((INT8*)pstShareFileNameMgr->u8FileName);
        AHC_UF_PostAddFile(0, (INT8*)pstShareFileNameMgr->u8FileName);
        AHC_UF_SelectDB(eDBType);

        MEMSET(pstShareFileNameMgr->u8FileName, 0, sizeof(pstShareFileNameMgr->u8FileName));

        m_bAhcFirstShareFile = AHC_FALSE;

        AHC_VIDEO_SetShareRecdStarted(AHC_FALSE);

        #if defined(WIFI_PORT) && (WIFI_PORT == 1)
        ncgi_notify_fn(NCGI_SHORT_FN, (char*)pstShareFileNameMgr->u8FullName);
        #endif
#endif
        #endif

    }
    else {
        // TBD
    }
}

//------------------------------------------------------------------------------
//  Function    : VRLongTimeFileFullCB
//  Description :
//------------------------------------------------------------------------------
static void VRLongTimeFileFullCB(void)
{
    AHC_DBG_MSG(1, FG_GREEN("<VRLongTimeFileFullCB>\r\n"));

    AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_VRCB_LONG_TIME_FILE_FULL, 0);
}

//------------------------------------------------------------------------------
//  Function    : VRMediaSlowCB
//  Description :
//------------------------------------------------------------------------------
static void VRMediaSlowCB(void)
{
    AHC_DBG_MSG(1, FG_RED("<VRMediaSlowCB>\r\n"));

    AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_VRCB_MEDIA_SLOW, 0);
}

#if (VR_SLOW_CARD_DETECT)
//------------------------------------------------------------------------------
//  Function    : VRPreGetTimeWhenCardSlowCB
//  Description :
//------------------------------------------------------------------------------
static void VRPreGetTimeWhenCardSlowCB(AHC_BOOL bPrmRecdEn, UINT32 ulPrmRecdTime, AHC_BOOL bEmgRecdEn, UINT32 ulEmgRecdTime)
{
    AHC_DBG_MSG(1, FG_RED("<VRPreGetTimeWhenCardSlowCB>\r\n"));

    if (bPrmRecdEn)
        AHC_DBG_MSG(1, "# PrmRecdTime [%d] ms\r\n", ulPrmRecdTime);
    if (bEmgRecdEn)
        AHC_DBG_MSG(1, "# EmgRecdTime [%d] ms\r\n", ulEmgRecdTime);

    m_bAhcCardSlowDetected = AHC_TRUE;

#ifdef SLOW_CARD_RESTART
    AHC_WMSG_Draw(AHC_TRUE, WMSG_CARD_SLOW, 3);
    AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_VRCB_MEDIA_SLOW, 0);
#endif
}

//------------------------------------------------------------------------------
//  Function    : VRRecdStopWhenCardSlowCB
//  Description :
//------------------------------------------------------------------------------
static void VRRecdStopWhenCardSlowCB(void)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    AHC_DBG_MSG(1, FG_RED("<VRRecdStopWhenCardSlowCB>\r\n"));

    m_bAhcCardSlowDetected = AHC_FALSE;

    AHC_VIDEO_SetVRSeamless(AHC_FALSE);

    //AHC_VIDEO_SetRecCardSlowStop(AHC_TRUE);
    AHC_VIDEO_SetAPStopRecord(AHC_FALSE);

    if ((MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_DUAL_FILE)  ||
        (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)) {
        AHC_VIDEO_SetKernalEmergStopStep(AHC_KERNAL_EMERGENCY_AHC_DONE);
    }

    ahcRet = AHC_KeyEventIDCheckConflict(BUTTON_VRCB_RECDSTOP_CARDSLOW);
    if (ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return; }

    AHC_SetCurKeyEventID(BUTTON_VRCB_RECDSTOP_CARDSLOW);
    AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_VRCB_RECDSTOP_CARDSLOW, 0);
}

#else

//------------------------------------------------------------------------------
//  Function    : VRCardSlowStopEncCB
//  Description :
//------------------------------------------------------------------------------
static void VRCardSlowStopEncCB(void)
{
    AHC_DBG_MSG(1, FG_RED("<VRCardSlowStopEncCB>\r\n"));

    AHC_VIDEO_SetRecCardSlowStop(AHC_TRUE);

    #if (GPS_CONNECT_ENABLE)
    if (AHC_GPS_Module_Attached()) {
        UINT8 bGPS_en;

        if ((AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bGPS_en) == AHC_TRUE) &&
            (bGPS_en != COMMON_GPS_REC_INFO_OFF)) {
            MMPF_OS_SetFlags(UartCtrlFlag, GPS_FLAG_SWITCHBUFFER_CLOSE, MMPF_OS_FLAG_SET);
        }
    }
    #endif
}
#endif

//------------------------------------------------------------------------------
//  Function    : VRMediaErrorCB
//  Description :
//------------------------------------------------------------------------------
static void VRMediaErrorCB(MMP_ULONG ulMgrErrState, MMP_ULONG ulMgrFSErrCode)
{
    AHC_DBG_MSG(1, FG_RED("<VRMediaErrorCB>\r\n"));
    AHC_DBG_MSG(1, FG_RED("MgrErrStatus : 0x%x\r\n"), ulMgrErrState);
    AHC_DBG_MSG(1, FG_RED("MgrFSErrCode : 0x%x\r\n"), ulMgrFSErrCode);

    AHC_WMSG_Draw(AHC_TRUE, WMSG_INSERT_SD_AGAIN, 2);

    AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_VRCB_MEDIA_ERROR, 0);

#if (GPS_CONNECT_ENABLE) && (GPS_FUNC & FUNC_VIDEOSTREM_INFO) && (GPS_USE_FILE_AS_DATABUF)
    GPSCtrl_CloseInfoFile();
#endif

#if (GSENSOR_CONNECT_ENABLE) && (GSENSOR_FUNC & FUNC_VIDEOSTREM_INFO) && (GSNR_USE_FILE_AS_DATABUF)
    AHC_Gsensor_CloseInfoFile();
#endif
}

//------------------------------------------------------------------------------
//  Function    : VRStartEncCB
//  Description :
//------------------------------------------------------------------------------
static void VRStartEncCB(MMP_ULONG ulParam)
{
    AHC_DBG_MSG(0, FG_GREEN("<VRStartEncCB> ID[%d]\r\n"), ulParam);

    AHC_VIDEO_RecordStartWriteInfo();
}

//------------------------------------------------------------------------------
//  Function    : VRStopEncCB
//  Description :
//------------------------------------------------------------------------------
static void VRStopEncCB(MMP_ULONG ulParam)
{
    AHC_DBG_MSG(0, FG_GREEN("<VRStopEncCB> ID[%d]\r\n"), ulParam);

    #if (AHC_SHAREENC_SUPPORT)
    if ((AHC_VIDEO_IsEmergRecStarted() == AHC_TRUE) && (AHC_VIDEO_IsEmergPostDone() == AHC_FALSE))
    {
        m_bShareVRPostDone = AHC_TRUE;
        AHC_VIDEO_SetEmergRecStarted(AHC_FALSE);
    }
    #endif

    AHC_VIDEO_RecordStopWriteInfo();
}

//------------------------------------------------------------------------------
//  Function    : VRMuxPostProcCB
//  Description :
//------------------------------------------------------------------------------
static UINT32 VRMuxPostProcCB(MMP_ERR (*pfMuxWrite)(void *buf, MMP_ULONG size, MMP_ULONG *wr_size, MMP_ULONG ul_FileID),
                              MMP_ULONG ulBackFileID, MMP_USHORT usStreamType)
{
    extern UINT32 m_ulEventPreRecordTime;
    extern UINT32 m_ulEventHappenTime;
    extern AHC_BOOL m_bCurrentTimeLessThanPreRecord;

    MMP_UBYTE ubID = 0;

    if (usStreamType == VIDENC_STREAM_PRM_RECD)
        ubID = 0;
    else if (usStreamType == VIDENC_STREAM_SCD_RECD)
        ubID = 1;

    AHC_DBG_MSG(0, FG_GREEN("<VRMuxPostCB> StreamType[%d]\r\n"), usStreamType);

#if (VR_VIDEO_TYPE != COMMON_VR_VIDEO_TYPE_TS)

    // Add below code ( #if ~ #endif ) since VRStopEncCB() did not be called after Emergency recording finished
    // Remove it after VRStopEncCB() is called from driver
    #if (GPS_RAW_FILE_ENABLE == 0 && GSENSOR_RAW_FILE_ENABLE == 0)
    if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
    {
        #if (GPS_CONNECT_ENABLE && GSENSOR_CONNECT_ENABLE)
        if ((AHC_VIDEO_GetKernalEmergStopStep() == AHC_KERNAL_EMERGENCY_RECORD) &&
            (AHC_GPS_NeedToFlushBackupBuffer(ubID) == AHC_FALSE &&
             AHC_Gsensor_NeedToFlushBackupBuffer(ubID) == AHC_FALSE))
        {
            VRStopEncCB(0xff/* For compile error. TBD */);
        }
        #endif
    }
    #endif

    // Blocking action for 3gp merger task.
    VR_WriteFunc = pfMuxWrite;
    AHC_VIDEO_RecordPostWriteInfo(ulBackFileID, usStreamType);
#endif

#if (GPS_CONNECT_ENABLE) && (GPS_FUNC & FUNC_VIDEOSTREM_INFO) && (GPS_USE_FILE_AS_DATABUF)
    GPSCtrl_CloseInfoFile();

    if ((MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_DUAL_FILE) ||
        (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE) )
    {
        if (AHC_GPS_Module_Attached() == AHC_TRUE &&
            AHC_VIDEO_GetKernalEmergStopStep() == AHC_KERNAL_EMERGENCY_RECORD &&
            usStreamType == VIDENC_STREAM_PRM_RECD) {
            UINT32  ulTickCount = 0;
            MMPF_OS_GetTime(&ulTickCount);
            AHC_GPS_TriggerRestorePreRecordInfo(AHC_TRUE, m_ulEventPreRecordTime + ((ulTickCount - m_ulEventHappenTime)*1000)/ OS_TICKS_PER_SEC, m_bCurrentTimeLessThanPreRecord );
        }
    }
#endif

#if (GSENSOR_CONNECT_ENABLE) && (GSENSOR_FUNC & FUNC_VIDEOSTREM_INFO) && (GSNR_USE_FILE_AS_DATABUF)
    AHC_Gsensor_CloseInfoFile();

    if ((MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_DUAL_FILE)  ||
        (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE) )
    {
        if (AHC_Gsensor_Module_Attached() == AHC_TRUE &&
            AHC_VIDEO_GetKernalEmergStopStep() == AHC_KERNAL_EMERGENCY_RECORD &&
            usStreamType == VIDENC_STREAM_PRM_RECD) {
            UINT32 ulTickCount = 0;
            MMPF_OS_GetTime(&ulTickCount);
            AHC_Gsensor_TriggerRestorePreRecordInfo(AHC_TRUE, m_ulEventPreRecordTime + ((ulTickCount - m_ulEventHappenTime)*1000)/ OS_TICKS_PER_SEC, m_bCurrentTimeLessThanPreRecord );
        }
    }
#endif

    return 0;
}

//------------------------------------------------------------------------------
//  Function    : VRSeamlessCB
//  Description :
//------------------------------------------------------------------------------
static void VRSeamlessCB(void)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    if (AHC_VIDEO_IsVRSeamless() == AHC_FALSE) {
        AHC_DBG_MSG(1, FG_GREEN("<VRSeamlessCB> NOP\r\n"));
        return;
    }

    AHC_DBG_MSG(1, FG_GREEN("<VRSeamlessCB>\r\n"));

    ahcRet = AHC_KeyEventIDCheckConflict(BUTTON_VRCB_SEAM_LESS);
    if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return;}

    //m_bTestSeamlessSlowCard = MMP_TRUE;

    AHC_SetCurKeyEventID(BUTTON_VRCB_SEAM_LESS);
    AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_VRCB_SEAM_LESS, 0);
}

//------------------------------------------------------------------------------
//  Function    : VREmerDoneCB
//  Description :
//------------------------------------------------------------------------------
static void VREmerDoneCB(void)
{
    AHC_VIDEO_FILENAME_MGR  *pstPrmEmergFileNameMgr;

    pstPrmEmergFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_PRMEMER);

    AHC_DBG_MSG(1, FG_GREEN("<VREmerDoneCB>\r\n"));

    #if (VR_SLOW_CARD_DETECT)
    if (m_bAhcCardSlowDetected) {
        return;
    }
    #endif

    #if (EMER_RECORD_DUAL_WRITE_ENABLE == 1)
    if ((MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_DUAL_FILE) ||
        (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)) {
        AHC_VIDEO_SetKernalEmergStopStep(AHC_KERNAL_EMERGENCY_STOP);
    }

    AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_VRCB_EMER_DONE, 0);

    #if defined(WIFI_PORT) && (WIFI_PORT == 1)
    ncgi_notify_fn(NCGI_EMER_FN, (char*)pstPrmEmergFileNameMgr->u8FullName);
    #endif
    #endif
}

#if 0
void _____VR_Zoom_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetCurZoomStep
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetCurZoomStep(UINT16 *usZoomStepNum)
{
    MMP_UBYTE ubPipe = 0;

    if (!MMPS_3GPRECD_GetCurZoomStep(ubPipe, usZoomStepNum))
        return AHC_FALSE;
    else
        return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetMaxZoomStep
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetMaxZoomStep(UINT16 *usMaxZoomStep)
{
    *usMaxZoomStep = gsVidPtzCfg.usMaxZoomSteps;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetMaxZoomRatio
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetMaxZoomRatio(UINT16 *usMaxZoomRatio)
{
     *usMaxZoomRatio = gsVidPtzCfg.usMaxZoomRatio;

     return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetCurZoomStatus
//  Description :
//------------------------------------------------------------------------------
MMP_UBYTE AHC_VIDEO_GetCurZoomStatus(void)
{
    return MMPS_3GPRECD_GetCurZoomStatus();
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetDigitalZoomRatio
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetDigitalZoomRatio(UINT32 *usZoomRatio)
{
    UINT16 usMaxZoomRatio, usCurrentStep, usMaxZoomStep;

    AHC_VIDEO_GetMaxZoomRatio(&usMaxZoomRatio);

    AHC_VIDEO_GetCurZoomStep(&usCurrentStep);
    AHC_VIDEO_GetMaxZoomStep(&usMaxZoomStep);

    *usZoomRatio = ((usMaxZoomRatio > 1) && (usMaxZoomStep > 0)) ? (100 + (usCurrentStep * (usMaxZoomRatio - 1) * 100) / usMaxZoomStep) : 100;

    return AHC_TRUE;
}

#if 0
void _____VR_File_Operation_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetPrevRecFullName
//  Description :
//------------------------------------------------------------------------------
UINT8* AHC_VIDEO_GetPrevRecFullName(void)
{
    return (UINT8*)m_bPrevPrmRecdFullName;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetCurPrmRecdFileName
//  Description :
//------------------------------------------------------------------------------
UINT8* AHC_VIDEO_GetCurPrmRecdFileName(AHC_BOOL bFullName)
{
    AHC_VIDEO_FILENAME_MGR *pstPrmRecdFileNameMgr;

    pstPrmRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_PRMREC);

    if (bFullName) {
        return (UINT8*)pstPrmRecdFileNameMgr->u8FullName;
    }
    else {
        return (UINT8*)pstPrmRecdFileNameMgr->u8FileName;
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetCurScdRecdFileName
//  Description :
//------------------------------------------------------------------------------
UINT8* AHC_VIDEO_GetCurScdRecdFileName(AHC_BOOL bFullName)
{
    AHC_VIDEO_FILENAME_MGR *pstScdRecdFileNameMgr;

    pstScdRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_SCDREC);

    if (bFullName) {
        return (UINT8*)pstScdRecdFileNameMgr->u8FullName;
    }
    else {
        return (UINT8*)pstScdRecdFileNameMgr->u8FileName;
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetCurUsbhRecdFileName
//  Description :
//------------------------------------------------------------------------------
UINT8* AHC_VIDEO_GetCurUsbhRecdFileName(AHC_BOOL bFullName)
{
    AHC_VIDEO_FILENAME_MGR *pstUsbRecdFileNameMgr;

    pstUsbRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_USBREC);

    if (bFullName) {
        return (UINT8*)pstUsbRecdFileNameMgr->u8FullName;
    }
    else {
        return (UINT8*)pstUsbRecdFileNameMgr->u8FileName;
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetCurRecDirKey
//  Description :
//------------------------------------------------------------------------------
UINT16 AHC_VIDEO_GetCurRecDirKey(void)
{
    return m_u16CurVideoDirKey;
}

//------------------------------------------------------------------------------
//  Function    : AHC_FF_SetFileNameSlot
//  Description : Search a hidden / oldest filename slot for next recorded file
//------------------------------------------------------------------------------
/**
 * @brief           Search a hidden / oldest filename slot for next recorded file
 *                  Note: This API only uses for Format Free.
 * @param[in]       byFilename    New filename for next recorded file
 * @retval          AHC_TRUE      Success.
 */
#if ( FS_FORMAT_FREE_ENABLE )
AHC_BOOL AHC_FF_SetFileNameSlot(MMP_BYTE *byFilename, DCF_CAM_ID byCamID)
{
    UINT16              uwYear,uwMonth,uwDay,uwDayInWeek,uwHour,uwMinute,uwSecond;
    UINT8               ubAmOrPm, b_12FormatEn;
    MMPS_FS_FILETIME    sFsFileTime;
    AHC_BOOL            ahcRet;
    char byOldFilename[MAX_FULL_FILENAME_SIZE] = {0};

    ahcRet = AHC_UF_SearchAvailableFileSlot(byCamID, byOldFilename);
    if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,ahcRet); return ahcRet;}
    AHC_DBG_MSG(1, "--FF: Old File-- %s\r\n", byOldFilename);

    MMPS_FS_FileDirRename( (MMP_BYTE*)byOldFilename, strlen(byOldFilename), byFilename, strlen(byFilename) );

    AHC_GetClock(&uwYear, &uwMonth, &uwDay, &uwDayInWeek, &uwHour, &uwMinute, &uwSecond, &ubAmOrPm, &b_12FormatEn);
    sFsFileTime.usYear   = uwYear;
    sFsFileTime.usMonth  = uwMonth;
    sFsFileTime.usDay    = uwDay;
    sFsFileTime.usHour   = uwHour;
    sFsFileTime.usMinute = uwMinute;
    sFsFileTime.usSecond = uwSecond;
    MMPS_FS_FileDirSetTime((MMP_BYTE*)byFilename, strlen(byFilename), &sFsFileTime);

    // Set Non-hidden attribute to let recorded file can be seen.
    {
        AHC_FS_ATTRIBUTE sAttrib;

        AHC_FS_FileDirGetAttribute( byFilename, strlen(byFilename), &sAttrib );
        if (sAttrib & AHC_FS_ATTR_HIDDEN)
        {
            sAttrib &= ~AHC_FS_ATTR_HIDDEN;
            AHC_FS_FileDirSetAttribute( byFilename, strlen(byFilename), sAttrib );
        }
    }

    return AHC_TRUE;
}
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetFileName
//  Description : This function is used to set file name before video recording
//------------------------------------------------------------------------------
static MMP_ERR AHC_VIDEO_SetFileName(MMP_BYTE byFilename[], UINT16 u16Length, MMP_USHORT usStreamType, DCF_CAM_ID byCamID)
{
    #if (FS_FORMAT_FREE_ENABLE)
    MMPS_FORMATFREE_EnableWrite(1);
    AHC_FF_SetFileNameSlot(byFilename, byCamID);
    #endif

    if (usStreamType == VIDENC_STREAM_PRM_EMERG) {
        return MMPS_3GPRECD_SetEmergFileName(byFilename, u16Length);
    }
    else {
        return MMPS_3GPRECD_SetFileName(usStreamType, byFilename, u16Length);
    }

    return MMP_ERR_NONE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_WaitVideoWriteFileFinish
//  Description : CHECK
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_WaitVideoWriteFileFinish(void)
{
    UINT32              u32TimeOut = 200; // unit is 10ms
    VIDENC_FW_STATUS    eVidEncStatus = VIDENC_FW_STATUS_NONE;

    do {
        if (0 == u32TimeOut) {
            AHC_DBG_ERR(1, FG_RED("--E-- Waiting for video file write to SD Timeout\r\n"));
            break;
        }

        MMPS_3GPRECD_GetPrmEncoderStatus(&eVidEncStatus);

        AHC_OS_SleepMs(10);
        u32TimeOut--;

    } while ((eVidEncStatus != VIDENC_FW_STATUS_NONE) &&
             (eVidEncStatus != VIDENC_FW_STATUS_STOP) &&
             (eVidEncStatus != VIDENC_FW_STATUS_PREENCODE));

    AHC_OS_SleepMs(100);

    return (u32TimeOut ? AHC_TRUE : AHC_FALSE);
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_DeleteDcfMinKeyFile
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_DeleteDcfMinKeyFile(AHC_BOOL bFirstTime, const char *ext)
{
    AHC_BOOL    ahc_ret         = AHC_TRUE;
    UINT32      u32MaxObjIdx    = 0;
    UINT32      u32InitObjIdx   = 0;
    UINT32      u32CurObjIdx    = 0;
    UINT32      u32FileSize     = 0;
    AHC_BOOL    bReadOnly       = AHC_FALSE;
    AHC_BOOL    bCharLock       = AHC_FALSE;
    UINT64      u64FreeSpace    = 0;
    UINT32      ulAudBitRate    = 128000;//128K
    UINT32      ulVidBitRate    = 0;
    UINT32      u32Timelimit    = 0;
    UINT64      u64SpaceNeeded  = 0;

    AHC_UF_SetFreeChar(0, DCF_SET_ALLOWED, (UINT8 *) ext);

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_BITRATE, &ulVidBitRate);

    u32Timelimit = AHC_VIDEO_GetRecTimeLimitEx();

    if (u32Timelimit == NON_CYCLING_TIME_LIMIT)
    {
        u64SpaceNeeded = 0x24000000;/* 576MB */
    }
    else
    {
        #if (defined(VIDEO_REC_TIMELAPSE_EN) && VIDEO_REC_TIMELAPSE_EN)
        UINT32 u32VRTimelapse = 0;

        if ((AHC_Menu_SettingGetCB(COMMON_KEY_VR_TIMELAPSE, &u32VRTimelapse) == AHC_TRUE) &&
            (u32VRTimelapse != COMMON_VR_TIMELAPSE_OFF)) {

            UINT32 u32Framerate = 0;
            UINT32 u32FrateIdx = 0;

            AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, &u32FrateIdx);
            u32Framerate = AHC_VIDEO_GetVideoRealFpsX1000(u32FrateIdx) / AHC_VIDRECD_TIME_INCREMENT_BASE;

            AHC_VIDEO_GetTimeLapseBitrate(u32Framerate, u32VRTimelapse, &ulVidBitRate, &ulAudBitRate);
        }
        else
        #endif
        {
            if ((MenuSettingConfig()->uiMOVSoundRecord == MOVIE_SOUND_RECORD_OFF) || m_bAhcSlowMotionEn || m_bAhcTimeLapseEn) {
                ulAudBitRate = 0;
            }
        }

        AHC_VIDEO_GetRecStorageSpaceNeed(ulVidBitRate, ulAudBitRate, u32Timelimit, &u64SpaceNeeded);

        if (bFirstTime) {
            u64SpaceNeeded *= 2;
        }
    }

    AHC_DBG_MSG(1, "DelMinKeyFile BR[%d][%d] Limit[%d]\r\n", ulVidBitRate, ulAudBitRate, u32Timelimit);

    AHC_Media_GetFreeSpace(&u64FreeSpace);

    do {
        if (u64FreeSpace >= u64SpaceNeeded) {
            AHC_DBG_MSG(1, FG_BLUE("FreeSpace[%dKB] is Enough [SpaceNeeded %dKB]\r\n"),
                        (u64FreeSpace>>10),
                        (u64SpaceNeeded>>10));
            return AHC_TRUE;
        }

        AHC_UF_GetTotalFileCount(&u32MaxObjIdx);

        if (u32MaxObjIdx == 0) {
            AHC_DBG_ERR(1, "No More DCF File for Delete!\r\n");
            return AHC_FALSE;
        }

        if (u32InitObjIdx >= u32MaxObjIdx) {
            AHC_DBG_MSG(1, "All %d File Can't Delete!!\r\n", u32MaxObjIdx);
            return AHC_FALSE;
        }

        AHC_UF_SetCurrentIndex(u32InitObjIdx);
        AHC_UF_GetCurrentIndex(&u32CurObjIdx);

        if (AHC_UF_GetFileSizebyIndex(u32CurObjIdx, &u32FileSize) == AHC_FALSE)
        {
            AHC_DBG_ERR(1, "AHC_UF_GetFileSizebyIndex Error\r\n");
            return AHC_FALSE;
        }

        AHC_UF_IsReadOnlybyIndex(u32CurObjIdx, &bReadOnly);
        AHC_UF_IsCharLockbyIndex(u32CurObjIdx, &bCharLock);

        if (bReadOnly
            #if (PROTECT_FILE_TYPE == PROTECT_FILE_RENAME)
            || bCharLock
            #endif
            )
        {
            u32InitObjIdx++;
            continue;
        }

        ahc_ret = AHC_UF_FileOperation_ByIdx(u32CurObjIdx, DCF_FILE_DELETE_ALL_CAM, NULL, NULL);

        if (ahc_ret == AHC_FALSE) {
            AHC_DBG_ERR(1, FG_RED("UF_FileOperation_ByIdx Delete Error\r\n"));
            return AHC_FALSE;
        }
        else {
            u64FreeSpace += u32FileSize;
        }

    } while(1);

    return ahc_ret;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_CyclicDeleteFiles
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_CyclicDeleteFiles(void)
{
    AHC_BOOL ahcRet = AHC_TRUE;
    AHC_BOOL bDeleteFile = AHC_TRUE;

    bDeleteFile = AHC_VIDEO_GetRecdDeleteFileEn();

    /* Protect File Flow */
#ifdef CFG_CUS_VIDEO_PROTECT_PROC
    CFG_CUS_VIDEO_PROTECT_PROC();
#else
    if (AHC_Protect_GetType() != AHC_PROTECT_NONE) {
        AHC_Protect_SetVRFile(AHC_PROTECTION_CUR_FILE, AHC_Protect_GetType());
        AHC_Protect_SetType(AHC_PROTECT_NONE);
    }
#endif

    #if (FS_FORMAT_FREE_ENABLE)
    bDeleteFile = AHC_FALSE;
    #endif

    /* Delete File Flow */
    if (bDeleteFile) {
        if (AHC_Deletion_Romove(AHC_FALSE) == AHC_FALSE) {
            AHC_DBG_ERR(1, FG_RED("AHC_Deletion_Romove Error\r\n"));
            return AHC_FALSE;
        }
    }

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_ClosePreviousFile
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_ClosePreviousFile(void)
{
    AHC_FS_ATTRIBUTE        stFileAttr;
    AHC_FS_FILETIME         stFileTimeStruc;
    UINT32                  u32FileSize = 0;
    AHC_BOOL                ahc_ret = AHC_TRUE;
    AHC_VIDEO_FILENAME_MGR  *pstPrmRecdFileNameMgr, *pstScdRecdFileNameMgr, *pstUsbRecdFileNameMgr;

    pstPrmRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_PRMREC);
    pstScdRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_SCDREC);
    pstUsbRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_USBREC);

    if (pstPrmRecdFileNameMgr->u8DeviceStatus) {

        AHC_UF_PostAddFile(m_u16CurVideoDirKey, (INT8*)pstPrmRecdFileNameMgr->u8FileName);

        #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
        AHC_VIDEO_StoreJpgThumbnail(VIDENC_STREAM_PRM_RECD);
        #endif
    }

    #if (AHC_MULTI_TRACK_EN == 0)
    if (pstScdRecdFileNameMgr->u8DeviceStatus)
    {
        if (AHC_FS_FileDirGetInfo((INT8*)pstScdRecdFileNameMgr->u8FullName,
                                  STRLEN((INT8*)pstScdRecdFileNameMgr->u8FullName),
                                  &stFileAttr,
                                  &stFileTimeStruc,
                                  &u32FileSize) == AHC_ERR_NONE) {

            AHC_UF_PostAddFile(m_u16CurVideoDirKey, (INT8*)pstScdRecdFileNameMgr->u8FileName);

            #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
            AHC_VIDEO_StoreJpgThumbnail(VIDENC_STREAM_SCD_RECD);
            #endif
        }
    }

    if (pstUsbRecdFileNameMgr->u8DeviceStatus)
    {
        if (AHC_FS_FileDirGetInfo((INT8*)pstUsbRecdFileNameMgr->u8FullName,
                                  STRLEN((INT8*)pstUsbRecdFileNameMgr->u8FullName),
                                  &stFileAttr,
                                  &stFileTimeStruc,
                                  &u32FileSize) == AHC_ERR_NONE) {

            AHC_UF_PostAddFile(m_u16CurVideoDirKey, (INT8*)pstUsbRecdFileNameMgr->u8FileName);

            #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
            AHC_VIDEO_StoreJpgThumbnail(VIDENC_STREAM_UVC_RECD);
            #endif
        }
    }
    #endif

    if ((AHC_UF_GetDB() == DCF_DB_TYPE_DB0_NORMAL) &&
        (AHC_VIDEO_NeedDeleteNormalAfterEmerg())) {
        AHC_VIDEO_DeleteLatestNormalFile();
    }

#if 0 // (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
{
    AHC_RTC_TIME    stRtcTime;
    int             nSecondOffset = 0;

    AHC_RTC_GetTime(&stRtcTime);

    if ((m_stAhcVidRecdStartRtcTime.uwYear <= RTC_DEFAULT_YEAR) && (stRtcTime.uwYear > RTC_DEFAULT_YEAR)) {

        nSecondOffset = -1*AHC_VIDEO_GetRecTimeLimitEx();

        AHC_DT_ShiftRtc(&stRtcTime, nSecondOffset);

        AHC_DBG_ERR(1, "UF_Rename::Old:%d-%d-%d:%d-%d-%d New:%d-%d-%d:%d-%d-%d \r\n",
                    m_stAhcVidRecdStartRtcTime.uwYear,
                    m_stAhcVidRecdStartRtcTime.uwMonth,
                    m_stAhcVidRecdStartRtcTime.uwDay,
                    m_stAhcVidRecdStartRtcTime.uwHour,
                    m_stAhcVidRecdStartRtcTime.uwMinute,
                    m_stAhcVidRecdStartRtcTime.uwSecond,
                    stRtcTime.uwYear,
                    stRtcTime.uwMonth,
                    stRtcTime.uwDay,
                    stRtcTime.uwHour,
                    stRtcTime.uwMinute,
                    stRtcTime.uwSecond);

        if (m_stAhcVidRecdStartRtcTime.uwYear != 0)
            AHC_UF_Rename(AHC_UF_GetDB(), &m_stAhcVidRecdStartRtcTime, &stRtcTime);

        m_stAhcVidRecdStartRtcTime = stRtcTime;
    }
}
#endif

#if (AHC_EMERGENTRECD_SUPPORT)
    if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_MOVE_FILE)
    {
        if (AHC_VIDEO_GetNormal2Emergency()) {

            UINT16          DirKey;

            AHC_VIDEO_SetNormal2Emergency(AHC_FALSE);

            AHC_DBG_MSG(1, "Normal2Emerg File [%s]\r\n", pstPrmRecdFileNameMgr->u8FileName);

            AHC_UF_MoveFile(DCF_DB_TYPE_DB0_NORMAL, DCF_DB_TYPE_DB2_EVENT, DirKey, pstPrmRecdFileNameMgr->u8FileName, AHC_TRUE);
        }
    }
#endif
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetRecStorageSpaceNeed
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_GetRecStorageSpaceNeed(UINT32 u32VidBitRate, UINT32 u32AudBitRate, UINT32 u32Timelimit, UINT64 *pu64SpaceNeeded)
{
    UINT64      u64SpaceNeeded = 0;
    UINT64      u64PrmRecdSpaceNeeded = 0;
    UINT64      u64ScdRecdSpaceNeeded = 0;
    MMP_ULONG   ulScdRecdBitrate = 0;
    MMP_BOOL    bScdCamConnected = MMP_FALSE;
    MMP_BOOL    bUsbCamConnected = MMP_FALSE;

    u64PrmRecdSpaceNeeded = ((((UINT64)u32VidBitRate + (UINT64)u32AudBitRate) >> 3) * (UINT64)u32Timelimit >> 3) * 9; // More 1/8 bitstream size

    if (MMP_IsUSBCamExist()) {

        MMPF_USBH_GetUVCPrevwSts(&bUsbCamConnected); // CHECK

        if (bUsbCamConnected) {
            MMPS_3GPRECD_GetParameter(MMPS_VR_SCD_RECD, MMPS_3GPRECD_PARAMETER_BITRATE, &ulScdRecdBitrate);
            if (ulScdRecdBitrate != 0)
                u64ScdRecdSpaceNeeded = ((((UINT64)ulScdRecdBitrate + (UINT64)u32AudBitRate) >> 3) * (UINT64)u32Timelimit >> 3) * 9;
            else
                u64ScdRecdSpaceNeeded = u64PrmRecdSpaceNeeded;
        }
        else {
            u64ScdRecdSpaceNeeded = 0;
        }
    }

    bScdCamConnected = AHC_SNR_CheckScdCamConnectSts();

    if (bScdCamConnected) {
        MMPS_3GPRECD_GetParameter(MMPS_VR_SCD_RECD, MMPS_3GPRECD_PARAMETER_BITRATE, &ulScdRecdBitrate);
        if (ulScdRecdBitrate != 0)
            u64ScdRecdSpaceNeeded = ((((UINT64)ulScdRecdBitrate + (UINT64)u32AudBitRate) >> 3) * (UINT64)u32Timelimit >> 3) * 9;
        else
            u64ScdRecdSpaceNeeded = u64PrmRecdSpaceNeeded;
    }
    else {
        u64ScdRecdSpaceNeeded = 0;
    }

    u64SpaceNeeded = u64PrmRecdSpaceNeeded + u64ScdRecdSpaceNeeded;

    if (u64SpaceNeeded > SIGNLE_FILE_SIZE_LIMIT_3_75G) {
        u64SpaceNeeded = SIGNLE_FILE_SIZE_LIMIT_3_75G;
    }

    if (pu64SpaceNeeded) {
        *pu64SpaceNeeded = u64SpaceNeeded;
    }
}

#if 0
void _____VR_Common_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecCardSlowStop
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_SetRecCardSlowStop(AHC_BOOL bState)
{
    m_bAhcCardSlowStopRecd = bState;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetRecCardSlowStop
//  Description : CHECK
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetRecCardSlowStop(void)
{
    return m_bAhcCardSlowStopRecd;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetAPStopRecord
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_SetAPStopRecord(AHC_BOOL bState)
{
    m_bAhcAPStopRecord = bState;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetAPStopRecord
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetAPStopRecord(void)
{
    return m_bAhcAPStopRecord;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetAPStopRecordTime
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_SetAPStopRecordTime(UINT32 u32LastRecdVidTime, UINT32 u32LastRecdAudTime)
{
    m_u32AhcAPStopRecdVidTime = u32LastRecdVidTime;
    m_u32AhcAPStopRecdAudTime = u32LastRecdAudTime;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetAPStopRecordTime
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetAPStopRecordTime(UINT32 *pu32LastRecdVidTime, UINT32 *pu32LastRecdAudTime)
{
    if (pu32LastRecdVidTime)
        *pu32LastRecdVidTime = m_u32AhcAPStopRecdVidTime; // Unit: ms
    if (pu32LastRecdAudTime)
        *pu32LastRecdAudTime = m_u32AhcAPStopRecdAudTime; // Unit: ms

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecdDeleteFileEn
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_SetRecdDeleteFileEn(AHC_BOOL bDeleteFile)
{
    m_bAhcDeleteFileEn = bDeleteFile;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetRecdDeleteFileEn
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetRecdDeleteFileEn(void)
{
    return m_bAhcDeleteFileEn;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetFirstTimeRecord
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_SetFirstTimeRecord(AHC_BOOL bFirstRecordSetFile)
{
    m_bAhcFirstRecdSetFile = bFirstRecordSetFile;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetFirstTimeRecord
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetFirstTimeRecord(void)
{
    return m_bAhcFirstRecdSetFile;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_RecordStartWriteInfo
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_RecordStartWriteInfo( void )
{
    AHC_BOOL                bSlowMotionEn = AHC_FALSE;
    AHC_BOOL                bTimeLapseEn = AHC_FALSE;

    AHC_VIDEO_GetSlowMotionFPS(&bSlowMotionEn, NULL, NULL);
#if (defined(VIDEO_REC_TIMELAPSE_EN) && VIDEO_REC_TIMELAPSE_EN)
    AHC_VIDEO_GetTimeLapseFPS(&bTimeLapseEn, NULL, NULL);
#endif

    if (bSlowMotionEn || bTimeLapseEn) {
        return;
    }

#if (GPS_CONNECT_ENABLE && (GPS_FUNC & FUNC_VIDEOSTREM_INFO))
    if (AHC_GPS_Module_Attached()) {
        UINT8 bGPS_en = 0;

        if ((AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bGPS_en) == AHC_TRUE) &&
            (bGPS_en != COMMON_GPS_REC_INFO_OFF)) {
            GPSCtrl_StartRecord();
        }
    }
#endif

#if (GSENSOR_CONNECT_ENABLE && (GSENSOR_FUNC & FUNC_VIDEOSTREM_INFO))
    if (AHC_Gsensor_Module_Attached()) {
        AHC_Gsensor_StartRecord();
    }
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_RecordStopWriteInfo
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_RecordStopWriteInfo( void )
{
    AHC_BOOL                bSlowMotionEn = AHC_FALSE;
    AHC_BOOL                bTimeLapseEn = AHC_FALSE;

    AHC_VIDEO_GetSlowMotionFPS(&bSlowMotionEn, NULL, NULL);
#if (defined(VIDEO_REC_TIMELAPSE_EN) && VIDEO_REC_TIMELAPSE_EN)
    AHC_VIDEO_GetTimeLapseFPS(&bTimeLapseEn, NULL, NULL);
#endif

    if (bSlowMotionEn || bTimeLapseEn) {
        return;
    }

#if (GPS_CONNECT_ENABLE) && (GPS_FUNC & FUNC_VIDEOSTREM_INFO)
    if (AHC_GPS_Module_Attached())
    {
        UINT8 bGPS_en = 0;

        if ((AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bGPS_en) == AHC_TRUE) &&
            (bGPS_en != COMMON_GPS_REC_INFO_OFF)) {

            if (AHC_GPS_NeedToFlushBackupBuffer(0) == AHC_TRUE) {
                GPSCtrl_EndRecord_Backup();
            }
            #if (AHC_SHAREENC_SUPPORT)
            else if (AHC_VIDEO_IsShareRecdStarted()) {
                GPSCtrl_EndRecordEx();
            }
            #endif
            else {
                GPSCtrl_EndRecord();
            }
        }
    }
#endif

#if (GSENSOR_CONNECT_ENABLE) && (GSENSOR_FUNC & FUNC_VIDEOSTREM_INFO)
    if (AHC_Gsensor_Module_Attached())
    {
        if (AHC_Gsensor_NeedToFlushBackupBuffer(0) == AHC_TRUE) {
            AHC_Gsensor_EndRecord_Backup();
        }
        #if (AHC_SHAREENC_SUPPORT)
        else if (AHC_VIDEO_IsShareRecdStarted()) {
            AHC_Gsensor_EndRecordEx();
        }
        #endif
        else {
            AHC_Gsensor_EndRecord();
        }
    }
#endif

#if (VR_VIDEO_TYPE == COMMON_VR_VIDEO_TYPE_3GP)
    #if (GPS_CONNECT_ENABLE)
    if (AHC_GPS_Module_Attached())
    {
        UINT8 bGPS_en = 0;

        if ((AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bGPS_en) == AHC_TRUE) &&
            (bGPS_en != COMMON_GPS_REC_INFO_OFF)) {
            MMPF_OS_SetFlags(UartCtrlFlag, GPS_FLAG_SWITCHBUFFER, MMPF_OS_FLAG_SET);
        }
    }
    #endif
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_RecordPostWriteInfo
//  Description : CHECK
//------------------------------------------------------------------------------
UINT32 AHC_VIDEO_RecordPostWriteInfo(UINT32 u32FileID, UINT16 u16StreamType)
{
    UINT32 ulWriteSize = 0;
    UINT32 ulTotalWSize = 0;
#if (GPS_CONNECT_ENABLE) || (GSENSOR_CONNECT_ENABLE)
    UINT8  ubID = 0;
    if (u16StreamType == VIDENC_STREAM_PRM_RECD)
        ubID = 0;
    else if (u16StreamType == VIDENC_STREAM_SCD_RECD)
        ubID = 1;
#endif

#if ((GPS_CONNECT_ENABLE) && (GPS_FUNC & FUNC_VIDEOSTREM_INFO))
    #if (AVI_IDIT_CHUNK_EN == 1)
    {
        void            *ptr;
        unsigned int    cb;

        #if (VR_CONTAINER_TYPE == COMMON_VR_VIDEO_TYPE_3GP)
        cb = MMPS_3GPMUX_Build_IDIT(&ptr);
        #else //COMMON_VR_VIDEO_TYPE_AVI
        cb = MMPS_AVIMUX_Build_IDIT(&ptr);
        #endif

        VR_WriteFunc_Ex(ptr, cb, &ulWriteSize, u32FileID, AHC_FALSE);
        ulTotalWSize += ulWriteSize;
    }
    #endif

    if (AHC_GPS_Module_Attached())
    {
        UINT8 bGPS_en;

        if ((AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bGPS_en) == AHC_TRUE) &&
            (bGPS_en != COMMON_GPS_REC_INFO_OFF)) {

            GPSCtrl_SetHeaderForAviChuck_GPSConfig();
            VR_WriteFunc_Ex((void *)GPSCtrl_HeaderAddressForAviChuck(0), 8, &ulWriteSize, u32FileID, AHC_FALSE);
            ulTotalWSize += ulWriteSize;
            VR_WriteFunc_Ex((void *)GPSCtrl_AttributeAddressForAviChuck(), sizeof(GPS_ATTRIBUTE), &ulWriteSize, u32FileID, AHC_FALSE);
            ulTotalWSize += ulWriteSize;

            GPSCtrl_SetHeaderForAviChuck();
            VR_WriteFunc_Ex((void *)GPSCtrl_HeaderAddressForAviChuck(1), 8, &ulWriteSize, u32FileID, AHC_FALSE);
            ulTotalWSize += ulWriteSize;

            #if (GPS_USE_FILE_AS_DATABUF)
            {
                extern UINT32 ulGPSInfoFileByte, ulGPSInfoLastByte;
                extern UINT32 ulGPSInfoFileId;

                UINT8  temp[256];
                UINT32 ultotalRSize, ulReadCount;
                pGPSInfoChuck InfoAddr;

                if (ulGPSInfoFileId != 0)
                {
                    AHC_FS_FileSeek(ulGPSInfoFileId, 0, AHC_FS_SEEK_SET);

                    // Read data from temp file then write to AVI.
                    for (ultotalRSize = ulGPSInfoFileByte; (int)ultotalRSize > 0; )
                    {
                        if (AHC_FS_FileRead(ulGPSInfoFileId,
                                            (UINT8 *)temp,
                                            sizeof(temp) / sizeof(UINT8),
                                            &ulReadCount) != AHC_ERR_NONE ||
                            ulReadCount == 0) {
                            break;
                        }

                        VR_WriteFunc_Ex((void *)temp, ulReadCount, &ulWriteSize, u32FileID, AHC_FALSE);
                        ulTotalWSize += ulWriteSize;
                        ultotalRSize -= ulReadCount;
                    }
                }

                // Flush last data from ping-pong buffer
                if (AHC_GPS_NeedToFlushBackupBuffer(ubID) == AHC_TRUE) {
                    AHC_GPS_FlushBackupBuffer(ubID, AHC_FALSE);
                    InfoAddr = (pGPSInfoChuck)GPSCtrl_GetBackupDataAddr();
                }
                else {
                    InfoAddr = (pGPSInfoChuck)GPSCtrl_GetLastDataAddr();
                }

                if (InfoAddr != NULL) {
                    VR_WriteFunc_Ex((void *)InfoAddr, ulGPSInfoLastByte, &ulWriteSize, u32FileID, AHC_FALSE);
                    ulTotalWSize += ulWriteSize;
                }
            }
            #else
            VR_WriteFunc_Ex((void *)GPSCtrl_InfoAddressForAviChuck(), GPSCtrl_InfoSizeForAviChuck(), &ulWriteSize, u32FileID, AHC_FALSE);
            ulTotalWSize += ulWriteSize;
            #endif
        }
    }
#endif

#if (GSENSOR_CONNECT_ENABLE) && (GSENSOR_FUNC & FUNC_VIDEOSTREM_INFO)
    if (AHC_Gsensor_Module_Attached())
    {
        AHC_Gsensor_SetAttribChuckHeader();
        VR_WriteFunc_Ex((void *)AHC_Gsensor_GetChuckHeaderAddr(0), 8, &ulWriteSize, u32FileID, AHC_FALSE);
        ulTotalWSize += ulWriteSize;
        VR_WriteFunc_Ex((void *)AHC_Gsensor_GetAttributeAddr(), sizeof(GSNR_ATTRIBUTE), &ulWriteSize, u32FileID, AHC_FALSE);
        ulTotalWSize += ulWriteSize;

        AHC_Gsensor_SetInfoChuckHeader();
        VR_WriteFunc_Ex((void *)AHC_Gsensor_GetChuckHeaderAddr(1), 8, &ulWriteSize, u32FileID, AHC_FALSE);
        ulTotalWSize += ulWriteSize;

        #if (GSNR_USE_FILE_AS_DATABUF)
        {
            extern UINT32 m_ulInfoFileByte, m_ulInfoLastByte;
            extern UINT32 m_ulInfoFileId;

            UINT8  temp[256];
            UINT32 ultotalRSize, ulReadCount;
            PGSNR_INFOCHUCK InfoAddr;
            AHC_ERR eAhcErr = AHC_ERR_NONE;

            if (m_ulInfoFileId != 0)
            {
                AHC_FS_FileSeek(m_ulInfoFileId, 0, AHC_FS_SEEK_SET);

                // Read data from temp file then write to AVI.
                for (ultotalRSize = m_ulInfoFileByte; ultotalRSize > 0; )
                {
                    eAhcErr = AHC_FS_FileRead(  m_ulInfoFileId,
                                                (UINT8 *)temp,
                                                256,
                                                &ulReadCount);

                    if (eAhcErr != AHC_ERR_NONE || ulReadCount == 0) {
                        break;
                    }

                    VR_WriteFunc_Ex((void *)temp, ulReadCount, &ulWriteSize, u32FileID, AHC_FALSE);
                    ulTotalWSize += ulWriteSize;
                    ultotalRSize -= ulReadCount;
                }
            }

            // Flush last data from ping-pong buffer
            if (AHC_Gsensor_NeedToFlushBackupBuffer(ubID) == AHC_TRUE) {
                AHC_Gsensor_FlushBackupBuffer(ubID, AHC_FALSE);
                InfoAddr = (PGSNR_INFOCHUCK)AHC_Gsensor_GetBackupDataAddr();
            }
            else {
                InfoAddr = (PGSNR_INFOCHUCK)AHC_Gsensor_GetLastDataAddr();
            }

            if (InfoAddr != NULL) {
                VR_WriteFunc_Ex((void *)InfoAddr, m_ulInfoLastByte, &ulWriteSize, u32FileID, AHC_FALSE);
                ulTotalWSize += ulWriteSize;
            }
        }
        #else
        VR_WriteFunc_Ex((void *)AHC_Gsensor_GetInfoChuckAddr(), AHC_Gsensor_GetInfoChuckSize(), &ulWriteSize, u32FileID, AHC_FALSE);
        ulTotalWSize += ulWriteSize;
        #endif
    }
#endif

#if (FS_FORMAT_FREE_ENABLE == 1)
    // Add some dummy data to avoid some PC tools need a long time to parse the file (with lots of 0x00 data in the tail of file).
    // Root cause: Unknown
    {
        UINT8 byFormatFreeDummyData[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA};
        VR_WriteFunc_Ex((void *)byFormatFreeDummyData, sizeof(byFormatFreeDummyData), &ulWriteSize, u32FileID, AHC_FALSE);
        ulTotalWSize += ulWriteSize;
    }
#endif

    // Use below code to write all data from buffer to media
    VR_WriteFunc_Ex(NULL, 0, &ulWriteSize, u32FileID, AHC_TRUE);
    ulTotalWSize += ulWriteSize;

    // Close GPS Raw/KML File for normal record
#if (GPS_CONNECT_ENABLE == 1)
    if (AHC_GPS_Module_Attached())
    {
        #if (GPS_RAW_FILE_ENABLE == 1)
        UINT8 bGPS_en;

        if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bGPS_en) == AHC_TRUE) {
            switch (bGPS_en) {
            case RECODE_GPS_OFF:
            case RECODE_GPS_IN_VIDEO:
                // NOP
                break;
            default:
                GPSCtrl_GPSRawClose();
                break;
            }
        }
        #endif
        #if (GPS_KML_FILE_ENABLE == 1)
        GPSCtrl_KMLGen_Write_TailAndClose();
        #endif
    }
#endif

    #if (GSENSOR_RAW_FILE_ENABLE == 1 && GPS_CONNECT_ENABLE == 0)
    GPSCtrl_GPSRawClose();
    #endif

    // Close GPS Raw/KML File for emergency record
    #if (GPS_CONNECT_ENABLE == 1)
    if (AHC_GPS_Module_Attached() && !AHC_VIDEO_IsEmergRecStarted())
    {
        #if (GPS_RAW_FILE_EMER_EN == 1)
        UINT8 bGPS_en;

        if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bGPS_en) == AHC_TRUE) {
            switch (bGPS_en) {
            case RECODE_GPS_OFF:
            case RECODE_GPS_IN_VIDEO:
                // NOP
                break;
            default:
                GPSCtrl_GPSRawClose_Emer();
                break;
            }
        }
        #endif
    }
    #endif

    #if (GSENSOR_RAW_FILE_ENABLE == 1 && GPS_CONNECT_ENABLE == 0 && GPS_RAW_FILE_EMER_EN == 1)
    if (!AHC_VIDEO_IsEmergRecStarted())
        GPSCtrl_GPSRawClose_Emer();
    #endif

    #if ( ((GPS_CONNECT_ENABLE) && (GPS_FUNC & FUNC_VIDEOSTREM_INFO))     || \
          ((GSENSOR_CONNECT_ENABLE) && (GSENSOR_FUNC & FUNC_VIDEOSTREM_INFO)) )
    return ulTotalWSize;
    #else
    return 0;
    #endif
}

#if 0
void _____VR_Time_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_AvailableRecTimeEx
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_AvailableRecTimeEx(UINT32 u32Bitrate, UINT8* pu8Hour, UINT8* pu8Min, UINT8* pu8Sec)
{
    VIDMGR_CONTAINER_TYPE   eContainerType = VIDMGR_CONTAINER_3GP;
    MMP_BOOL                bScdCamConnected = MMP_FALSE;
    MMP_BOOL                bUsbCamConnected = MMP_FALSE;
    UINT32                  u32Param = 0;
    UINT64                  u64FreeSpace = 0;
    UINT32                  u32TotalTime = 0;
    UINT32                  u32VideoRsvdSize = 0;
    UINT32                  u32PrmRecdVidBitRate = 0, u32AudioBitRate = 0;
    UINT32                  u32ScdRecdVidBitRate = 0;
    UINT8                   u8Hour = 0;
    #if (AHC_SHAREENC_SUPPORT)
    UINT32                  u32ShareRecdBitRate = 0;
    #endif

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_CLIP_CONTAINER_TYPE, &u32Param);
    eContainerType = u32Param;

    MMPS_3GPRECD_SetContainerType(eContainerType);

    /* Get Media Free Space */
    AHC_Media_GetFreeSpace(&u64FreeSpace);

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_RESERVED_SIZE, &u32VideoRsvdSize);

    if (u32Bitrate == 0)
        AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_BITRATE, &u32PrmRecdVidBitRate);
    else
        u32PrmRecdVidBitRate = u32Bitrate;

    #if (AHC_SHAREENC_SUPPORT)
    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_2ND_BITRATE, &u32ShareRecdBitRate);
    u32PrmRecdVidBitRate += u32ShareRecdBitRate;
    #endif

    if (MMP_IsUSBCamExist()) {

        bUsbCamConnected = AHC_HostUVC_IsDevEnabled(); // CHECK

        if (bUsbCamConnected)
            MMPS_3GPRECD_GetParameter(MMPS_VR_SCD_RECD, MMPS_3GPRECD_PARAMETER_BITRATE, &u32ScdRecdVidBitRate);
        else
            u32ScdRecdVidBitRate = 0;
    }

    bScdCamConnected = AHC_SNR_CheckScdCamConnectSts();

    if (bScdCamConnected)
        MMPS_3GPRECD_GetParameter(MMPS_VR_SCD_RECD, MMPS_3GPRECD_PARAMETER_BITRATE, &u32ScdRecdVidBitRate);
    else
        u32ScdRecdVidBitRate = 0;

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_AUD_BITRATE, &u32AudioBitRate);

    if (u64FreeSpace <= u32VideoRsvdSize) {
        *pu8Hour = 0;
        *pu8Min  = 0;
        *pu8Sec  = 0;
        return;
    }

    u32TotalTime = MMPS_3GPRECD_GetExpectedRecordTime((u64FreeSpace - u32VideoRsvdSize), (u32PrmRecdVidBitRate + u32ScdRecdVidBitRate), u32AudioBitRate);

    u8Hour = u32TotalTime / (60*60);

    *pu8Hour = u8Hour;

    if (u8Hour < 100) {
        *pu8Min  = (u32TotalTime / 60) - (u8Hour * 60);
        *pu8Sec  = u32TotalTime % 60;
    }
    else {
        *pu8Hour = 99;
        *pu8Min  = 59;
        *pu8Sec  = 59;
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetCurRecordingTime
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetCurRecordingTime(UINT32 *pu32Time)
{
    if (!MMPS_3GPRECD_GetCurRecordingTime(pu32Time))
        return AHC_FALSE;
    else
        return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_ChangeCurFileTimeLimit
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_ChangeCurFileTimeLimit(UINT32 u32TimeLimitMs)
{
    DBG_AutoTestPrint(ATEST_ACT_EMERGENCY_0x0009, ATEST_STS_START_0x0001, 0, 0, gbAhcDbgBrk);

    if (MMP_ERR_NONE == MMPS_3GPRECD_ChangeCurFileTimeLimit(u32TimeLimitMs)) {
        return AHC_TRUE;
    }
    return AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetRecTimeLimitEx
//  Description :
//------------------------------------------------------------------------------
UINT32 AHC_VIDEO_GetRecTimeLimitEx(void)
{
    #define SEC_PER_MIN  (60)

    UINT32  u32VRTimeLimitInSec = 0;
    UINT32  u32ClipTime = 0;

    if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_VR_CLIP_TIME, &u32ClipTime) == AHC_FALSE) {
        AHC_DBG_ERR(1, FG_RED("Get COMMON_KEY_VR_CLIP_TIME error - using default\r\n"));
        u32ClipTime = MOVIE_CLIP_TIME_OFF;
    }

    switch (u32ClipTime)
    {
    case COMMON_MOVIE_CLIP_TIME_6SEC:
        u32VRTimeLimitInSec = 6;
        break;
    case COMMON_MOVIE_CLIP_TIME_1MIN:
        u32VRTimeLimitInSec = 1*SEC_PER_MIN;
        break;
    case COMMON_MOVIE_CLIP_TIME_2MIN:
        u32VRTimeLimitInSec = 2*SEC_PER_MIN;
        break;
    case COMMON_MOVIE_CLIP_TIME_3MIN:
        u32VRTimeLimitInSec = 3*SEC_PER_MIN;
        break;
    case COMMON_MOVIE_CLIP_TIME_5MIN:
        u32VRTimeLimitInSec = 5*SEC_PER_MIN;
        break;
    case COMMON_MOVIE_CLIP_TIME_10MIN:
        u32VRTimeLimitInSec = 10*SEC_PER_MIN;
        break;
    case COMMON_MOVIE_CLIP_TIME_25MIN:
        u32VRTimeLimitInSec = 25*SEC_PER_MIN;
        break;
    case COMMON_MOVIE_CLIP_TIME_30MIN:
        u32VRTimeLimitInSec = 30*SEC_PER_MIN;
        break;
    case COMMON_MOVIE_CLIP_TIME_OFF:
    default:
        u32VRTimeLimitInSec = NON_CYCLING_TIME_LIMIT;
        break;
    }

    #if (MOTION_DETECTION_EN)
    #if (SET_MOTION_DETECTION_MOVIE_CLIP_TIME)
    {
        extern AHC_BOOL m_ubMotionDtcEn;

        if (m_ubMotionDtcEn)
        {
            u32VRTimeLimitInSec = MOTION_DETECTION_MOVIE_CLIP_TIME;
        }
    }
    #endif
    #endif

#ifdef VIDEO_REC_TIMELAPSE_EN
    #if (0)//(VIDEO_REC_TIMELAPSE_EN) // CHECK
    {
        UINT32 ulTimeLapseSetting;
        UINT32 Frate;
        UINT64 ullFramerate_1000Times;

        AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, &Frate);
        ullFramerate_1000Times = (AHC_VIDEO_GetVideoRealFpsX1000(Frate)*1000) / AHC_VIDRECD_TIME_INCREMENT_BASE;

        if ((AHC_Menu_SettingGetCB(COMMON_KEY_VR_TIMELAPSE, &ulTimeLapseSetting) == AHC_TRUE) &&
            (ulTimeLapseSetting != COMMON_VR_TIMELAPSE_OFF) &&
            (u32VRTimeLimitInSec != NON_CYCLING_TIME_LIMIT)) {

            switch(ulTimeLapseSetting){
            case COMMON_VR_TIMELAPSE_5SEC:
                u32VRTimeLimitInSec = (UINT32)(((UINT64)u32VRTimeLimitInSec * ullFramerate_1000Times * 5)/1000);
                break;
            case COMMON_VR_TIMELAPSE_10SEC:
                u32VRTimeLimitInSec = (UINT32)(((UINT64)u32VRTimeLimitInSec * ullFramerate_1000Times * 10)/1000);
                break;
            case COMMON_VR_TIMELAPSE_30SEC:
                u32VRTimeLimitInSec = (UINT32)(((UINT64)u32VRTimeLimitInSec * ullFramerate_1000Times * 30)/1000);
                break;
            case COMMON_VR_TIMELAPSE_60SEC:
                u32VRTimeLimitInSec = (UINT32)(((UINT64)u32VRTimeLimitInSec * ullFramerate_1000Times * 60)/1000);
                break;
            case COMMON_VR_TIMELAPSE_1SEC:
            default:
                u32VRTimeLimitInSec = (UINT32)(((UINT64)u32VRTimeLimitInSec * ullFramerate_1000Times * 1)/1000);
                break;
            }
        }
    }
    #endif
#endif

    return u32VRTimeLimitInSec;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecTimeLimit
//  Description :
//------------------------------------------------------------------------------
UINT32 AHC_VIDEO_SetRecTimeLimit(UINT32 u32TimeLimit)
{
    if (u32TimeLimit < ((0x7FFFFFFF - VR_TIME_LIMIT_OFFSET) / 1000)) {
        u32TimeLimit = u32TimeLimit * 1000 + VR_TIME_LIMIT_OFFSET;
    }

    AHC_DBG_MSG(1, "Record Clip Time [%d] ms\r\n", u32TimeLimit);
    MMPS_3GPRECD_SetFileTimeLimit(u32TimeLimit);

    return 0;
}

#if 0
void _____VR_ScdRecd_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetScdRecdSetting
//  Description :
//------------------------------------------------------------------------------
static void AHC_VIDEO_SetScdRecdSetting(void)
{
    VIDENC_PROFILE              eProfile    = H264ENC_MAIN_PROFILE;
    MMP_USHORT                  usResoIdx   = VIDRECD_RESOL_720x480;
    MMP_ULONG                   ulEncW = 0, ulEncH = 0;
    MMP_ULONG                   ulBitRate = 0;
    MMPS_3GPRECD_FRAMERATE      stSnrFps    = {AHC_VIDRECD_TIME_INCREMENT_BASE_NTSC, 30000};
    MMPS_3GPRECD_FRAMERATE      stEncFps    = {AHC_VIDRECD_TIME_INCREMENT_BASE_NTSC, 30000};
    MMPS_3GPRECD_FRAMERATE      stMgrFps    = {AHC_VIDRECD_TIME_INCREMENT_BASE_NTSC, 30000};
    MMP_USHORT                  usQuality   = VIDRECD_QUALITY_LOW;
    MMP_USHORT                  usPFrameCount = 14, usBFrameCount = 0;
    MMP_SNR_ANADEC_SRC_TYPE     eAnaDecSrcType = MMP_SNR_ANADEC_SRC_NO_READY;
    MMP_SNR_YUV_SRC_TYPE        eYuvSrcType = MMP_SNR_YUV_SRC_DISCNT;
    MMP_ULONG                   ulVidTimeIncBase = AHC_VIDRECD_TIME_INCREMENT_BASE_NTSC;
    MMP_ERR                     eRetErr = MMP_ERR_NONE;
    MMP_UBYTE                   ubRecdSel = MMPS_VR_SCD_RECD;
    AHC_BOOL                    bSlowMotionEn = AHC_FALSE;
    AHC_BOOL                    bVideoTimeLapseEn = AHC_FALSE;
    UINT32                      u32SlowMotionTimeIncrement = 0, u32SlowMotionTimeResol = 0;
    UINT32                      u32TimeLapseTimeIncrement = 0, u32TimeLapseTimeResol = 0;

#if 0 // NEED CHECK  If scd cam plug in when prm cam is recording, it will cause prm cam to not stop recording.
    if ((AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_SCD, AHC_TRUE) & VID_RECD_ENCODE_H264) ||
        (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_TRUE) & VID_RECD_ENCODE_H264)) {
        eRetErr = MMPS_3GPRECD_EnableScdRecd(MMP_TRUE);
    }
    else {
        eRetErr = MMPS_3GPRECD_EnableScdRecd(MMP_FALSE);
    }
#endif

    switch (MenuSettingConfig()->uiMOVQuality) {
    case QUALITY_SUPER_FINE:
        usQuality = VIDRECD_QUALITY_HIGH;
        break;
    case QUALITY_FINE:
        usQuality = VIDRECD_QUALITY_MID;
        break;
    default:
        usQuality = VIDRECD_QUALITY_HIGH;
        break;
    }

    AHC_VIDEO_GetSlowMotionFPS(&bSlowMotionEn, &u32SlowMotionTimeIncrement, &u32SlowMotionTimeResol);
#if (defined(VIDEO_REC_TIMELAPSE_EN) && VIDEO_REC_TIMELAPSE_EN)
    AHC_VIDEO_GetTimeLapseFPS(&bVideoTimeLapseEn, &u32TimeLapseTimeIncrement, &u32TimeLapseTimeResol);
#endif

    /* Set 2nd Video Record Attribute */
    eRetErr |= MMPS_3GPRECD_SetProfile(ubRecdSel, eProfile);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return;}

    if (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {

        MMPS_Sensor_GetYUVSnrSrcType(&eYuvSrcType);

        if (eYuvSrcType == MMP_SNR_YUV_SRC_HD) {
            usResoIdx = VIDRECD_RESOL_1280x720;
            ulVidTimeIncBase = AHC_VIDRECD_TIME_INCREMENT_BASE;
        }
        else {
            usResoIdx = VIDRECD_RESOL_1920x1088;
            ulVidTimeIncBase = AHC_VIDRECD_TIME_INCREMENT_BASE;
        }
    }
    else if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
        MMP_ULONG ulFpsx10 = 0;

        MMPS_Sensor_GetAnaDecSrcType(&eAnaDecSrcType);
        MMPS_Sensor_GetCurFpsx10(gsAhcScdSensor, &ulFpsx10);

        if (eAnaDecSrcType == MMP_SNR_ANADEC_SRC_FHD) {
            usResoIdx = VIDRECD_RESOL_1920x1088;
            if (ulFpsx10 == 300) {
                ulVidTimeIncBase = AHC_VIDRECD_TIME_INCREMENT_BASE_NTSC;
            }
            else if (ulFpsx10 == 250) {
                ulVidTimeIncBase = AHC_VIDRECD_TIME_INCREMENT_BASE_PAL;
            }
        }
        else if (eAnaDecSrcType == MMP_SNR_ANADEC_SRC_HD) {
            usResoIdx = VIDRECD_RESOL_1280x720;
            if (ulFpsx10 == 300) {
                ulVidTimeIncBase = AHC_VIDRECD_TIME_INCREMENT_BASE_NTSC;
            }
            else if (ulFpsx10 == 250) {
                ulVidTimeIncBase = AHC_VIDRECD_TIME_INCREMENT_BASE_PAL;
            }
        }
        else if (eAnaDecSrcType == MMP_SNR_ANADEC_SRC_NTSC) {
            usResoIdx = VIDRECD_RESOL_720x480; // VIDRECD_RESOL_720x576
            ulVidTimeIncBase = AHC_VIDRECD_TIME_INCREMENT_BASE_NTSC;
        }
        else {
            usResoIdx = VIDRECD_RESOL_720x480;
            ulVidTimeIncBase = AHC_VIDRECD_TIME_INCREMENT_BASE_PAL;
        }
    }
    else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
        UINT32 u32Param;
        AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_RESOLUTION, &u32Param);
        usResoIdx = AHC_VIDRECD_RESOL_TO_VIDRECD_RESOL(u32Param);
        ulVidTimeIncBase = AHC_VIDRECD_TIME_INCREMENT_BASE;
    }
    else {
        return;
    }

    stSnrFps.ulTimeIncre = ulVidTimeIncBase;
    stSnrFps.ulTimeResol = 30000;
    stMgrFps.ulTimeIncre = stSnrFps.ulTimeIncre;
    stMgrFps.ulTimeResol = stSnrFps.ulTimeResol;

    if (bSlowMotionEn) {
        // Slow Motion Record
        stMgrFps.ulTimeIncre = stSnrFps.ulTimeIncre;
        stMgrFps.ulTimeResol = u32SlowMotionTimeResol;
        if ((stSnrFps.ulTimeIncre * stSnrFps.ulTimeResol) < (stMgrFps.ulTimeIncre * stMgrFps.ulTimeResol)){
            AHC_DBG_ERR(1, FG_RED("SlowMotion Error!%d,%d,%d,%d\r\n"),
                        stSnrFps.ulTimeIncre, stSnrFps.ulTimeResol, stMgrFps.ulTimeIncre, stMgrFps.ulTimeResol);
            stMgrFps.ulTimeIncre = stSnrFps.ulTimeIncre;
            stMgrFps.ulTimeResol = stSnrFps.ulTimeResol;
        }
    }
    else {
        // Normal Record (Non-Slow Motion)
        stMgrFps.ulTimeIncre = stSnrFps.ulTimeIncre;
        stMgrFps.ulTimeResol = stSnrFps.ulTimeResol;
    }

    if (bVideoTimeLapseEn) {
        // Time Lapse Record
        stEncFps.ulTimeIncre = stSnrFps.ulTimeIncre;
        stEncFps.ulTimeResol = u32TimeLapseTimeResol;
        if ((stSnrFps.ulTimeIncre * stSnrFps.ulTimeResol) < (stEncFps.ulTimeIncre * stEncFps.ulTimeResol)){
            AHC_DBG_ERR(1, FG_RED("VideoTimeLapse Error!%d,%d,%d,%d\r\n"),
                        stSnrFps.ulTimeIncre, stSnrFps.ulTimeResol, stEncFps.ulTimeIncre, stEncFps.ulTimeResol);
            stEncFps.ulTimeIncre = stSnrFps.ulTimeIncre;
            stEncFps.ulTimeResol = stSnrFps.ulTimeResol;
        }
    }
    else {
        // Normal Record (Non-VideoTimeLapse)
        stEncFps.ulTimeIncre = stSnrFps.ulTimeIncre;
        stEncFps.ulTimeResol = stSnrFps.ulTimeResol;
    }

    eRetErr = MMPS_3GPRECD_SetFrameRatePara(ubRecdSel, &stSnrFps, &stEncFps, &stMgrFps);

    ulBitRate = MMPS_3GPRECD_GetPresetCfg()->ulFps30BitrateMap[usResoIdx][usQuality];
    eRetErr |= MMPS_3GPRECD_SetBitrate(ubRecdSel, ulBitRate);

    eRetErr |= MMPS_3GPRECD_SetPFrameCount(ubRecdSel, usPFrameCount);
    eRetErr |= MMPS_3GPRECD_SetBFrameCount(ubRecdSel, usBFrameCount);

    ulEncW = MMPS_3GPRECD_GetPresetCfg()->usEncWidth[usResoIdx];
    ulEncH = MMPS_3GPRECD_GetPresetCfg()->usEncHeight[usResoIdx];

    // For RearCam_2In1, modify the encode size.
    // Note: Maybe a better way is to create a new resolution instead of this one.
    // Ex: For VGA 2In1, create VIDRECD_RESOL_1280x480.
    if (MMP_GetANACamType() == ANA_CAM_2I1O){
        ulEncW *= 2;
        if ( ulEncW > 2304 ) {// 2304 is max encode width
            ulEncW = 2304;
            ulEncH = 648;
        }
        UartSendTrace("RearCam_2In1: Modified Encode resolution as %d x %d\r\n", ulEncW, ulEncH);
    }

    AHC_VIDEO_SetRecdResol(gsAhcScdSensor, ulEncW, ulEncH);
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_ScdRecordStart
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AHC_VIDEO_ScdRecordStart(void)
{
    MMP_ERR eRetErr = MMP_ERR_NONE;

    AHC_VIDEO_SetScdRecdSetting();

    eRetErr = MMPS_3GPRECD_StartScdRecd();
    if (eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(0, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_CheckScdRecdEnabled
//  Description :
//------------------------------------------------------------------------------
UINT8 AHC_VIDEO_CheckScdRecdEnabled(UINT8 ubCamType, AHC_BOOL bChkConnect)
{
    if (CAM_CHECK_SCD(SCD_CAM_NONE) &&
        CAM_CHECK_USB(USB_CAM_NONE)) {
        #if (AHC_SHAREENC_SUPPORT)
        return VID_RECD_STORE_FILE | VID_RECD_ENCODE_H264;
        #else
        return VID_RECD_DISABLE;
        #endif
    }

    if (ubCamType == CAM_TYPE_SCD) {

        switch(CAM_GET_SCD)
        {
        case SCD_CAM_ANA_DECODER:
            if (bChkConnect) {
                if (AHC_TRUE == AHC_SNR_GetAnaDecSnrCnntStatus())
                    return VID_RECD_STORE_FILE | VID_RECD_ENCODE_H264;
                else
                    return VID_RECD_DISABLE;
            }
            else {
                return VID_RECD_STORE_FILE | VID_RECD_ENCODE_H264;
            }
        break;
        case SCD_CAM_BAYER_SENSOR:
            if (1)
                return VID_RECD_STORE_FILE | VID_RECD_ENCODE_H264;
            else
                return VID_RECD_DISABLE;
        break;
        case SCD_CAM_YUV_SENSOR:
            if (bChkConnect) {
                if (AHC_TRUE == AHC_SNR_GetYuvSnrCnntStatus())
                    return VID_RECD_STORE_FILE | VID_RECD_ENCODE_H264;
                else
                    return VID_RECD_DISABLE;
            }
            else {
                return VID_RECD_STORE_FILE | VID_RECD_ENCODE_H264;
            }
        break;
        default:
            return VID_RECD_DISABLE;
        break;
        }
    }
    else if (ubCamType == CAM_TYPE_USB) {

        switch(CAM_GET_USB)
        {
        case USB_CAM_AIT:
            if (bChkConnect) {
                if (AHC_TRUE == AHC_HostUVC_IsDevEnabled())
                    return VID_RECD_STORE_FILE;
                else
                    return VID_RECD_DISABLE;
            }
            else {
                return VID_RECD_STORE_FILE;
            }
        break;
        case USB_CAM_SONIX_MJPEG:
            if (bChkConnect) {
                if (AHC_TRUE == AHC_HostUVC_IsDevEnabled())
                    return VID_RECD_STORE_FILE;
                else
                    return VID_RECD_DISABLE;
            }
            else {
                return VID_RECD_STORE_FILE;
            }
        break;
        case USB_CAM_SONIX_MJPEG2H264:
            if (bChkConnect) {
                if (AHC_TRUE == AHC_HostUVC_IsDevEnabled())
                    return VID_RECD_STORE_FILE | VID_RECD_ENCODE_H264;
                else
                    return VID_RECD_DISABLE;
            }
            else {
                return VID_RECD_STORE_FILE | VID_RECD_ENCODE_H264;
            }
        break;
        default:
            return VID_RECD_DISABLE;
        break;
        }
    }

    return VID_RECD_DISABLE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetRecdStateWhenDecSnrPlug
//  Description : TBD
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetRecdStateWhenDecSnrPlug(void)
{
    return m_bAhcVidRecdStateWhenDecSnrPlug;
}

#if 0
void _____VR_EmergRec_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_IsEmergRecStarted
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_IsEmergRecStarted(void)
{
#if (EMER_RECORD_DUAL_WRITE_ENABLE)
    AHC_DBG_MSG(0, "IsEmergRecStarted [%d]\n", m_bStartEmerVR);
    return m_bStartEmerVR;
#elif (AHC_SHAREENC_SUPPORT)
    return m_bStartShareVR;
#else
    return AHC_FALSE;
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetEmergRecStarted
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetEmergRecStarted(AHC_BOOL bEmerRecordStarted)
{
#if (EMER_RECORD_DUAL_WRITE_ENABLE)
    AHC_DBG_MSG(0, "SetEmergRecStarted [%d]\n", bEmerRecordStarted);
    m_bStartEmerVR = bEmerRecordStarted;
    return AHC_TRUE;
#elif (AHC_SHAREENC_SUPPORT)
    m_bStartShareVR = bEmerRecordStarted;
    return AHC_TRUE;
#else
    return AHC_FALSE;
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_IsEmergPostDone
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_IsEmergPostDone(void)
{
#if (EMER_RECORD_DUAL_WRITE_ENABLE)
    AHC_DBG_MSG(0, "IsEmergPostDone [%d]\n", m_bEmerVRPostDone);
    return m_bEmerVRPostDone;
#elif (AHC_SHAREENC_SUPPORT)
    return m_bShareVRPostDone;
#else
    return AHC_FALSE;
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetEmergPostDone
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetEmergPostDone(AHC_BOOL bDone)
{
#if (EMER_RECORD_DUAL_WRITE_ENABLE)
    AHC_DBG_MSG(0, "SetEmergPostDone [%d]\n", bDone);
    m_bEmerVRPostDone = bDone;
    return AHC_TRUE;
#elif (AHC_SHAREENC_SUPPORT)
    m_bShareVRPostDone = bDone;
    return AHC_TRUE;
#else
    return AHC_FALSE;
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetKernalEmergStopStep
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetKernalEmergStopStep(AHC_KERNAL_EMERGENCY_STOP_STEP bKernalEmergencyStopStep)
{
    #if (EMER_RECORD_DUAL_WRITE_ENABLE)
    AHC_DBG_MSG(0, "SetKernalEmergStopStep [%d]\n", bKernalEmergencyStopStep);
    m_bKernalEmergencyStopStep = bKernalEmergencyStopStep;
    return AHC_TRUE;
    #else
    return AHC_FALSE;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetKernalEmergStopStep
//  Description :
//------------------------------------------------------------------------------
AHC_KERNAL_EMERGENCY_STOP_STEP AHC_VIDEO_GetKernalEmergStopStep(void)
{
    #if (EMER_RECORD_DUAL_WRITE_ENABLE)
    AHC_DBG_MSG(0, "GetKernalEmergStopStep [%d]\n", m_bKernalEmergencyStopStep);
    return m_bKernalEmergencyStopStep;
    #else
    return AHC_FALSE;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetEmergRecFileName
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetEmergRecFileName(UINT8 **ppu8FileName, AHC_BOOL bFullFileName)
{
#if (EMER_RECORD_DUAL_WRITE_ENABLE)
    AHC_VIDEO_FILENAME_MGR *pstPrmEmergFileNameMgr;

    pstPrmEmergFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_PRMEMER);

    if (ppu8FileName == NULL) {
        return AHC_FALSE;
    }

    if (bFullFileName) {
        *ppu8FileName = (UINT8*)pstPrmEmergFileNameMgr->u8FullName;
    }
    else {
        *ppu8FileName = (UINT8*)pstPrmEmergFileNameMgr->u8FileName;
    }
    return AHC_TRUE;
#else
    return AHC_FALSE;
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_StartEmergRecord
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_StartEmergRecord(void)
{
#if (EMER_RECORD_DUAL_WRITE_ENABLE)
    DCF_DB_TYPE             sCurType;
    MMP_BYTE                chDirName[16];
    UINT8                   u8CreateNewDir;
    VIDMGR_CONTAINER_TYPE   ContainerType;
    UINT32                  u32Param = 0;
    AHC_BOOL                ahc_ret = AHC_TRUE;
    #if (GPS_RAW_FILE_EMER_EN == 1 || GSENSOR_RAW_FILE_ENABLE == 1)
    MMP_BYTE                bGPSRawFileName_Emer[MAX_FULL_FILENAME_SIZE];
    #endif
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    AHC_VIDEO_FILENAME_MGR  *pstPrmEmergFileNameMgr, *pstScdEmergFileNameMgr, *pstUsbEmergFileNameMgr;

    AHC_VIDEO_UpdateCurCnntStatusByType(AHC_VIDRECD_FILENAME_PRMEMER);
    AHC_VIDEO_UpdateCurCnntStatusByType(AHC_VIDRECD_FILENAME_SCDEMER);
    AHC_VIDEO_UpdateCurCnntStatusByType(AHC_VIDRECD_FILENAME_USBEMER);

    pstPrmEmergFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_PRMEMER);
    pstScdEmergFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_SCDEMER);
    pstUsbEmergFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_USBEMER);

    #if (GPS_RAW_FILE_EMER_EN == 1)
    GPSCtrl_SetGPSRawStart_Emer(AHC_TRUE);
    GPSCtrl_SetGPSRawWriteFirst(AHC_FALSE);
    #endif


    #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
    MEMSET(m_chEmerThumbFileName, 0, sizeof(m_chEmerThumbFileName));
    MEMSET(m_chEmerThumbFullName, 0, sizeof(m_chEmerThumbFullName));
    MEMSET(m_chEmerThumbFileName_Rear, 0, sizeof(m_chEmerThumbFileName_Rear));
    MEMSET(m_chEmerThumbFullName_Rear, 0, sizeof(m_chEmerThumbFullName_Rear));
    MEMSET(m_chEmerThumbFileName_USBH, 0, sizeof(m_chEmerThumbFileName_USBH));
    MEMSET(m_chEmerThumbFullName_USBH, 0, sizeof(m_chEmerThumbFullName_USBH));
    #endif

    MEMSET(chDirName, 0, sizeof(chDirName));

    if (pstPrmEmergFileNameMgr->u8DeviceStatus) {
        MEMSET(pstPrmEmergFileNameMgr->u8FullName, 0, sizeof(pstPrmEmergFileNameMgr->u8FullName));
        MEMSET(pstPrmEmergFileNameMgr->u8FileName, 0, sizeof(pstPrmEmergFileNameMgr->u8FileName));
    }

    #if (AHC_MULTI_TRACK_EN == 0)
    if (pstScdEmergFileNameMgr->u8DeviceStatus) {
        MEMSET(pstScdEmergFileNameMgr->u8FullName, 0, sizeof(pstScdEmergFileNameMgr->u8FullName));
        MEMSET(pstScdEmergFileNameMgr->u8FileName, 0, sizeof(pstScdEmergFileNameMgr->u8FileName));
    }
    if (pstUsbEmergFileNameMgr->u8DeviceStatus) {
        MEMSET(pstUsbEmergFileNameMgr->u8FullName, 0, sizeof(pstUsbEmergFileNameMgr->u8FullName));
        MEMSET(pstUsbEmergFileNameMgr->u8FileName, 0, sizeof(pstUsbEmergFileNameMgr->u8FileName));
    }
    #endif

    sCurType = AHC_UF_GetDB();

    AHC_UF_SelectDB(DCF_DB_TYPE_DB2_EVENT);

#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)

    ahc_ret = AHC_UF_GetName(&m_uwEmerVRDirKey, (INT8*)chDirName, (INT8*)pstPrmEmergFileNameMgr->u8FileName, &u8CreateNewDir);

    if (ahc_ret == AHC_TRUE) {
        STRCPY(m_chEmerVRFullName, (INT8*)AHC_UF_GetRootDirName());
        STRCAT(m_chEmerVRFullName, "\\");
        STRCAT(m_chEmerVRFullName, chDirName);

        if (u8CreateNewDir) {
            MMPS_FS_DirCreate((INT8*)m_chEmerVRFullName, STRLEN(m_chEmerVRFullName));
            AHC_UF_AddDir(chDirName);
        }

        STRCAT(m_chEmerVRFullName, "\\");
        STRCAT(m_chEmerVRFullName, (INT8*)pstPrmEmergFileNameMgr->u8FileName);
    }
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
{
    MMP_ULONG   ulEmergentRecordingOffset;
    int         nSecondOffset = 0;
    UINT8       u8CamStatus = AHC_Capture_GetCamStatusForDCF();

    AHC_RTC_GetTime(&m_stAhcEmergRecdStartRtcTime);

    MMPS_3GPRECD_GetRemainFrmTimeOffset(VIDENC_STREAM_PRM_EMERG, &ulEmergentRecordingOffset);

    #if 1
    nSecondOffset = -1*(ulEmergentRecordingOffset/1000);
    #else
    nSecondOffset = -1*(EMER_RECORD_DUAL_WRITE_PRETIME);
    #endif

    AHC_DT_ShiftRtc(&m_stAhcEmergRecdStartRtcTime, nSecondOffset);

    if (pstPrmEmergFileNameMgr->u8DeviceStatus) {
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
        ahc_ret = AHC_UF_GetName2(&m_stAhcEmergRecdStartRtcTime, (INT8*)pstPrmEmergFileNameMgr->u8FullName, (INT8*)pstPrmEmergFileNameMgr->u8FileName, u8CamStatus);
    }

    #if (AHC_MULTI_TRACK_EN == 0)
    if (pstScdEmergFileNameMgr->u8DeviceStatus) {
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
        ahc_ret = AHC_UF_GetName2(&m_stAhcEmergRecdStartRtcTime, (INT8*)pstScdEmergFileNameMgr->u8FullName, (INT8*)pstScdEmergFileNameMgr->u8FileName, u8CamStatus);
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }

    if (pstUsbEmergFileNameMgr->u8DeviceStatus) {
        AHC_UF_SetRearCamPathFlag(AHC_TRUE);
        ahc_ret = AHC_UF_GetName2(&m_stAhcEmergRecdStartRtcTime, (INT8*)pstUsbEmergFileNameMgr->u8FullName, (INT8*)pstUsbEmergFileNameMgr->u8FileName, u8CamStatus);
        AHC_UF_SetRearCamPathFlag(AHC_FALSE);
    }
    #endif
}
#endif

    if (ahc_ret == AHC_TRUE) {

        AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_CLIP_CONTAINER_TYPE, &u32Param);
        ContainerType = u32Param;

        if (pstPrmEmergFileNameMgr->u8DeviceStatus) {
            STRCAT((INT8*)pstPrmEmergFileNameMgr->u8FullName, EXT_DOT);
            STRCAT((INT8*)pstPrmEmergFileNameMgr->u8FileName, EXT_DOT);
            #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
            MEMCPY(m_chEmerThumbFullName, pstPrmEmergFileNameMgr->u8FullName, sizeof(m_chEmerThumbFullName));
            MEMCPY(m_chEmerThumbFileName, pstPrmEmergFileNameMgr->u8FileName, sizeof(m_chEmerThumbFileName));
            #endif
        }

        #if (AHC_MULTI_TRACK_EN == 0)
        if (pstScdEmergFileNameMgr->u8DeviceStatus) {
            STRCAT((INT8*)pstScdEmergFileNameMgr->u8FullName, EXT_DOT);
            STRCAT((INT8*)pstScdEmergFileNameMgr->u8FileName, EXT_DOT);
            #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
            MEMCPY(m_chEmerThumbFullName_Rear, pstScdEmergFileNameMgr->u8FullName, sizeof(m_chEmerThumbFullName_Rear));
            MEMCPY(m_chEmerThumbFileName_Rear, pstScdEmergFileNameMgr->u8FileName, sizeof(m_chEmerThumbFileName_Rear));
            #endif
        }

        if (pstUsbEmergFileNameMgr->u8DeviceStatus) {
            STRCAT((INT8*)pstUsbEmergFileNameMgr->u8FullName, EXT_DOT);
            STRCAT((INT8*)pstUsbEmergFileNameMgr->u8FileName, EXT_DOT);
            #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
            MEMCPY(m_chEmerThumbFullName_USBH, pstUsbEmergFileNameMgr->u8FullName, sizeof(m_chEmerThumbFullName_USBH));
            MEMCPY(m_chEmerThumbFileName_USBH, pstUsbEmergFileNameMgr->u8FileName, sizeof(m_chEmerThumbFileName_USBH));
            #endif
        }
        #endif

        #if (GPS_CONNECT_ENABLE == 1)
        if (AHC_GPS_Module_Attached())
        {
            #if (GPS_RAW_FILE_ENABLE == 1)
            MEMSET(bGPSRawFileName_Emer, 0, sizeof(bGPSRawFileName_Emer));
            STRCPY(bGPSRawFileName_Emer, pstPrmEmergFileNameMgr->u8FullName);
            STRCAT(bGPSRawFileName_Emer, GPS_RAW_FILE_EXTENTION);
            #endif
        }
        #endif

        #if (GSENSOR_RAW_FILE_ENABLE == 1 && GPS_CONNECT_ENABLE == 0)
        MEMSET(bGPSRawFileName_Emer, 0, sizeof(bGPSRawFileName_Emer));
        STRCPY(bGPSRawFileName_Emer, pstPrmEmergFileNameMgr->u8FullName);
        STRCAT(bGPSRawFileName_Emer, GPS_RAW_FILE_EXTENTION);
        #endif

        if (ContainerType == VIDMGR_CONTAINER_3GP) {

            if (pstPrmEmergFileNameMgr->u8DeviceStatus) {
                #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
                STRCAT((INT8*)m_chEmerThumbFullName, PHOTO_JPG_EXT);
                STRCAT((INT8*)m_chEmerThumbFileName, PHOTO_JPG_EXT);
                #endif
                STRCAT((INT8*)pstPrmEmergFileNameMgr->u8FullName, MOVIE_3GP_EXT);
                STRCAT((INT8*)pstPrmEmergFileNameMgr->u8FileName, MOVIE_3GP_EXT);
            }

            #if (AHC_MULTI_TRACK_EN == 0)
            if (pstScdEmergFileNameMgr->u8DeviceStatus) {
                #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
                STRCAT((INT8*)m_chEmerThumbFullName_Rear, PHOTO_JPG_EXT);
                STRCAT((INT8*)m_chEmerThumbFileName_Rear, PHOTO_JPG_EXT);
                #endif
                STRCAT((INT8*)pstScdEmergFileNameMgr->u8FullName, MOVIE_3GP_EXT);
                STRCAT((INT8*)pstScdEmergFileNameMgr->u8FileName, MOVIE_3GP_EXT);
            }

            if (pstUsbEmergFileNameMgr->u8DeviceStatus) {
                #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
                STRCAT((INT8*)m_chEmerThumbFullName_USBH, PHOTO_JPG_EXT);
                STRCAT((INT8*)m_chEmerThumbFileName_USBH, PHOTO_JPG_EXT);
                #endif
                STRCAT((INT8*)pstUsbEmergFileNameMgr->u8FullName, MOVIE_3GP_EXT);
                STRCAT((INT8*)pstUsbEmergFileNameMgr->u8FileName, MOVIE_3GP_EXT);
            }
            #endif
        }
        else if (ContainerType == VIDMGR_CONTAINER_TS) {
            if (pstPrmEmergFileNameMgr->u8DeviceStatus) {
                #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
                STRCAT((INT8*)m_chEmerThumbFullName, PHOTO_JPG_EXT);
                STRCAT((INT8*)m_chEmerThumbFileName, PHOTO_JPG_EXT);
                #endif
                STRCAT((INT8*)pstPrmEmergFileNameMgr->u8FullName, MOVIE_TS_EXT);
                STRCAT((INT8*)pstPrmEmergFileNameMgr->u8FileName, MOVIE_TS_EXT);
            }

            #if (AHC_MULTI_TRACK_EN == 0)
            if (pstScdEmergFileNameMgr->u8DeviceStatus) {
                #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
                STRCAT((INT8*)m_chEmerThumbFullName_Rear, PHOTO_JPG_EXT);
                STRCAT((INT8*)m_chEmerThumbFileName_Rear, PHOTO_JPG_EXT);
                #endif
                STRCAT((INT8*)pstScdEmergFileNameMgr->u8FullName, MOVIE_TS_EXT);
                STRCAT((INT8*)pstScdEmergFileNameMgr->u8FileName, MOVIE_TS_EXT);
            }

            if (pstUsbEmergFileNameMgr->u8DeviceStatus) {
                #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
                STRCAT((INT8*)m_chEmerThumbFullName_USBH, PHOTO_JPG_EXT);
                STRCAT((INT8*)m_chEmerThumbFileName_USBH, PHOTO_JPG_EXT);
                #endif
                STRCAT((INT8*)pstUsbEmergFileNameMgr->u8FullName, MOVIE_TS_EXT);
                STRCAT((INT8*)pstUsbEmergFileNameMgr->u8FileName, MOVIE_TS_EXT);
            }
            #endif
        }
        else {
            if (pstPrmEmergFileNameMgr->u8DeviceStatus) {
                #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
                STRCAT((INT8*)m_chEmerThumbFullName, PHOTO_JPG_EXT);
                STRCAT((INT8*)m_chEmerThumbFileName, PHOTO_JPG_EXT);
                #endif
                STRCAT((INT8*)pstPrmEmergFileNameMgr->u8FullName, MOVIE_AVI_EXT);
                STRCAT((INT8*)pstPrmEmergFileNameMgr->u8FileName, MOVIE_AVI_EXT);
            }

            #if (AHC_MULTI_TRACK_EN == 0)
            if (pstScdEmergFileNameMgr->u8DeviceStatus) {
                #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
                STRCAT((INT8*)m_chEmerThumbFullName_Rear, PHOTO_JPG_EXT);
                STRCAT((INT8*)m_chEmerThumbFileName_Rear, PHOTO_JPG_EXT);
                #endif
                STRCAT((INT8*)pstScdEmergFileNameMgr->u8FullName, MOVIE_AVI_EXT);
                STRCAT((INT8*)pstScdEmergFileNameMgr->u8FileName, MOVIE_AVI_EXT);
            }

            if (pstUsbEmergFileNameMgr->u8DeviceStatus) {
                #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
                STRCAT((INT8*)m_chEmerThumbFullName_USBH, PHOTO_JPG_EXT);
                STRCAT((INT8*)m_chEmerThumbFileName_USBH, PHOTO_JPG_EXT);
                #endif
                STRCAT((INT8*)pstUsbEmergFileNameMgr->u8FullName, MOVIE_AVI_EXT);
                STRCAT((INT8*)pstUsbEmergFileNameMgr->u8FileName, MOVIE_AVI_EXT);
            }
            #endif
        }

        #if (GPS_CONNECT_ENABLE == 1)
        if (AHC_GPS_Module_Attached())
        {
            #if (GPS_RAW_FILE_ENABLE == 1)
            UINT8 bGPS_en;

            if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bGPS_en) == AHC_TRUE) {
                switch (bGPS_en) {
                case RECODE_GPS_OFF:
                case RECODE_GPS_IN_VIDEO:
                    // NOP
                    break;
                default:
                {
                    MMP_ULONG ulEmergentRecordingOffset = 0;

                    MMPS_3GPRECD_GetRemainFrmTimeOffset(VIDENC_STREAM_PRM_EMERG, &ulEmergentRecordingOffset);

                    GPSCtrl_SetGPSRawFileName_Emer(bGPSRawFileName_Emer, STRLEN(bGPSRawFileName_Emer));
                    #if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
                    GPSCtrl_SetGPSRawBufTime_Emer(ulEmergentRecordingOffset/1000);
                    #endif
                }
                    break;
                }
            }
            #endif
        }
        #endif

        #if (GSENSOR_RAW_FILE_ENABLE == 1 && GPS_CONNECT_ENABLE == 0)
        {
            MMP_ULONG ulEmergentRecordingOffset = 0;

            MMPS_3GPRECD_GetRemainFrmTimeOffset(VIDENC_STREAM_PRM_EMERG, &ulEmergentRecordingOffset);

            GPSCtrl_SetGPSRawFileName_Emer(bGPSRawFileName_Emer,STRLEN(bGPSRawFileName_Emer));
            #if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
            GPSCtrl_SetGPSRawBufTime_Emer(ulEmergentRecordingOffset/1000);
            #endif
        }
        #endif

        if (pstPrmEmergFileNameMgr->u8DeviceStatus) {
            AHC_VIDEO_SetFileName(pstPrmEmergFileNameMgr->u8FullName, STRLEN(pstPrmEmergFileNameMgr->u8FullName), VIDENC_STREAM_PRM_EMERG, DCF_CAM_FRONT);
        }

        #if (AHC_MULTI_TRACK_EN == 0)
        if (pstScdEmergFileNameMgr->u8DeviceStatus) {
            AHC_VIDEO_SetFileName(pstScdEmergFileNameMgr->u8FullName, STRLEN(pstScdEmergFileNameMgr->u8FullName), VIDENC_STREAM_SCD_EMERG, DCF_CAM_REAR);
        }
        if (pstUsbEmergFileNameMgr->u8DeviceStatus) {
            if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_TRUE) & VID_RECD_ENCODE_H264) {
                AHC_VIDEO_SetFileName(pstUsbEmergFileNameMgr->u8FullName, STRLEN(pstUsbEmergFileNameMgr->u8FullName), VIDENC_STREAM_SCD_EMERG, DCF_CAM_REAR);
            }
            else {
                AHC_VIDEO_SetFileName(pstUsbEmergFileNameMgr->u8FullName, STRLEN(pstUsbEmergFileNameMgr->u8FullName), VIDENC_STREAM_UVC_EMERG, DCF_CAM_REAR);
            }
        }
        #endif

        m_uiEmerRecordInterval = EMER_RECORD_DUAL_WRITE_INTERVAL;
        AHC_VIDEO_SetEmergRecInterval(m_uiEmerRecordInterval);

        if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
            eRetErr = MMPS_3GPRECD_StartEmergentRecd(AHC_TRUE);
        else
            eRetErr = MMPS_3GPRECD_StartEmergentRecd(AHC_FALSE);

        if (eRetErr == MMP_3GPMGR_ERR_INVLAID_STATE)
        {
            AHC_DBG_ERR(1, FG_RED("Failed to start Emergency record because it's not in video record mode (2)!!!\r\n"));
            // Wait a while, then trigger Emergency record again.
            AHC_OS_Sleep(300);
            AHC_VIDEO_SetEmergRecStarted(AHC_FALSE);
            AHC_VIDEO_SetEmergPostDone(AHC_TRUE);
            AHC_UF_SelectDB(sCurType);
            return AHC_FALSE;
        }

        /* Pre-Add File Here For Speed Up To Start Emerg Recording */
        if (pstPrmEmergFileNameMgr->u8DeviceStatus) {
            AHC_DBG_MSG(1, "[PRM_EMERG] PreAdd %s\r\n", pstPrmEmergFileNameMgr->u8FullName);
            AHC_UF_PreAddFile(m_uwEmerVRDirKey, (INT8*)pstPrmEmergFileNameMgr->u8FileName);
        }

        #if (AHC_MULTI_TRACK_EN == 0)
        if (pstScdEmergFileNameMgr->u8DeviceStatus) {
            AHC_DBG_MSG(1, "[SCD_EMERG] PreAdd %s\r\n", pstScdEmergFileNameMgr->u8FullName);
            AHC_UF_PreAddFile(m_uwEmerVRDirKey, (INT8*)pstScdEmergFileNameMgr->u8FileName);
        }
        if (pstUsbEmergFileNameMgr->u8DeviceStatus) {
            AHC_DBG_MSG(1, "[UVC_EMERG] PreAdd %s\r\n", pstUsbEmergFileNameMgr->u8FullName);
            AHC_UF_PreAddFile(m_uwEmerVRDirKey, (INT8*)pstUsbEmergFileNameMgr->u8FileName);
        }
        #endif

        if (eRetErr != MMP_ERR_NONE)
        {
            PSDATETIMEDCFDB pDB = AIHC_DCFDT_GetDbByType(AHC_DCFDT_GetDB());

            AHC_VIDEO_SetEmergRecStarted(AHC_FALSE);
            AHC_VIDEO_SetEmergPostDone(AHC_TRUE);

            #if (GPS_RAW_FILE_EMER_EN == 1)
            GPSCtrl_SetGPSRawStart_Emer(AHC_FALSE);
            #endif

            // Note: Below code should be also workable for Standard DCF
            AIHC_DCFDT_DeleteFileInFS(pDB, pstPrmEmergFileNameMgr->u8FullName, AHC_FALSE);
            #if (AHC_MULTI_TRACK_EN == 0)
            if (pstScdEmergFileNameMgr->u8DeviceStatus) {
                AIHC_DCFDT_DeleteFileInFS(pDB, (INT8*)pstScdEmergFileNameMgr->u8FileName, AHC_FALSE);
            }
            if (pstUsbEmergFileNameMgr->u8DeviceStatus) {
                AIHC_DCFDT_DeleteFileInFS(pDB, (INT8*)pstUsbEmergFileNameMgr->u8FileName, AHC_FALSE);
            }
            #endif

            if (eRetErr == MMP_3GPMGR_ERR_INVLAID_STATE)
            {
                AHC_DBG_ERR(1, FG_RED("Failed to start Emergency record because it's not in video record mode (2)!!!\r\n"));
                // Wait a while, then trigger Emergency record again.
                AHC_OS_Sleep(300);
                AHC_VIDEO_SetEmergRecStarted(AHC_FALSE);
                AHC_SendAHLMessage(AHLM_UI_NOTIFICATION, BUTTON_LOCK_FILE_G, 0);
            }
            AHC_UF_SelectDB(sCurType);
            return AHC_FALSE;
        }

        AHC_VIDEO_SetEmergRecStarted(AHC_TRUE);
        AHC_VIDEO_SetEmergPostDone(AHC_FALSE);
    }

    AHC_UF_SelectDB(sCurType);
#endif

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetEmergRecTime
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetEmergRecTime(UINT32 *uiTime)
{
    #if (EMER_RECORD_DUAL_WRITE_ENABLE)
    MMPS_3GPRECD_GetEmergentRecordingTime(uiTime);
    #endif
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetEmergRecTimeOffset
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetEmergRecTimeOffset(UINT32 *puiTime)
{
    #if (EMER_RECORD_DUAL_WRITE_ENABLE)
    MMPS_3GPRECD_GetRemainFrmTimeOffset(VIDENC_STREAM_PRM_EMERG, puiTime);
    #endif
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetEmergRecInterval
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetEmergRecInterval(UINT32 uiInterval)
{
    #if (EMER_RECORD_DUAL_WRITE_ENABLE)
    m_uiEmerRecordInterval = uiInterval;

    if (uiInterval < ((0x7FFFFFFF - EM_VR_TIME_LIMIT_OFFSET) / 1000))
        uiInterval = uiInterval * 1000 + EM_VR_TIME_LIMIT_OFFSET;

    MMPS_3GPRECD_SetEmergentFileTimeLimit(uiInterval);
    #endif
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetEmergRecInterval
//  Description :
//------------------------------------------------------------------------------
UINT32 AHC_VIDEO_GetEmergRecInterval(void)
{
    #if (EMER_RECORD_DUAL_WRITE_ENABLE)
    return m_uiEmerRecordInterval;
    #else
    return 0;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_EmergRecPostProcess
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_EmergRecPostProcess(void)
{
    AHC_VIDEO_FILENAME_MGR  *pstPrmEmergFileNameMgr, *pstScdEmergFileNameMgr, *pstUsbEmergFileNameMgr;

    pstPrmEmergFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_PRMEMER);
    pstScdEmergFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_SCDEMER);
    pstUsbEmergFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_USBEMER);

    #if (GPS_RAW_FILE_EMER_EN == 1)
    GPSCtrl_GPSRawWriteFlushBuf_Emer();
    #endif

    #if (GPS_RAW_FILE_ENABLE == 1)
    if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
    {
        if (GPSCtrl_GPSRawWriteFirst_Normal())
            GPSCtrl_GPSRawResetBuffer();
    }
    #endif

    #if (GPS_CONNECT_ENABLE == 1)
    if (AHC_GPS_Module_Attached())
    {
        #if (GPS_RAW_FILE_EMER_EN == 1)
        UINT8 bGPS_en;

        if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bGPS_en) == AHC_TRUE) {
            switch (bGPS_en) {
            case RECODE_GPS_OFF:
            case RECODE_GPS_IN_VIDEO:
                // NOP
                break;
            default:
                if (!AHC_VIDEO_IsEmergRecStarted())
                    GPSCtrl_GPSRawClose_Emer();
                break;
            }
        }
        #endif
    }
    #endif

    #if (GSENSOR_RAW_FILE_ENABLE == 1 && GPS_CONNECT_ENABLE == 0 && GPS_RAW_FILE_EMER_EN == 1)
    if (!AHC_VIDEO_IsEmergRecStarted())
        GPSCtrl_GPSRawClose_Emer();
    #endif

    #if (EMER_RECORD_DUAL_WRITE_ENABLE)
    if (AHC_VIDEO_IsEmergPostDone() == AHC_FALSE) {
        DCF_DB_TYPE sType;

        sType = AHC_UF_GetDB();

        AHC_UF_SelectDB(DCF_DB_TYPE_DB2_EVENT);

        if (pstPrmEmergFileNameMgr->u8DeviceStatus) {
            AHC_DBG_MSG(1, "[PRM_EMERG] PostAdd %s\r\n", pstPrmEmergFileNameMgr->u8FullName);
            AHC_UF_PostAddFile(m_uwEmerVRDirKey, (INT8*)pstPrmEmergFileNameMgr->u8FileName);

            #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
            AHC_VIDEO_StoreJpgThumbnail(VIDENC_STREAM_PRM_EMERG);
            #endif
        }

        #if (AHC_MULTI_TRACK_EN == 0)
        if (pstScdEmergFileNameMgr->u8DeviceStatus) {
            AHC_DBG_MSG(1, "[SCD_EMERG] PostAdd %s\r\n", pstScdEmergFileNameMgr->u8FullName);
            AHC_UF_PostAddFile(m_uwEmerVRDirKey,(INT8*)pstScdEmergFileNameMgr->u8FileName);
            #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
            AHC_VIDEO_StoreJpgThumbnail(VIDENC_STREAM_SCD_EMERG);
            #endif
        }

        if (pstUsbEmergFileNameMgr->u8DeviceStatus) {
            AHC_DBG_MSG(1, "[UVC_EMERG] PostAdd %s\r\n", pstUsbEmergFileNameMgr->u8FullName);
            AHC_UF_PostAddFile(m_uwEmerVRDirKey,(INT8*)pstUsbEmergFileNameMgr->u8FileName);
            #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
            AHC_VIDEO_StoreJpgThumbnail(VIDENC_STREAM_UVC_EMERG);
            #endif
        }
        #endif

        AHC_UF_SelectDB(sType);

        AHC_VIDEO_SetEmergPostDone(AHC_TRUE);

        #if 0 // (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
        {
            AHC_RTC_TIME    stRtcTime;
            int             nSecondOffset;
            MMP_ULONG       ulEmergentRecordingTime;

            AHC_RTC_GetTime(&stRtcTime);

            if ((m_stAhcEmergRecdStartRtcTime.uwYear <= RTC_DEFAULT_YEAR) && (stRtcTime.uwYear > RTC_DEFAULT_YEAR)) {

                ulEmergentRecordingTime = AHC_VIDEO_GetEmergRecInterval();
                AHC_DBG_ERR(1, "ulEmergentRecordingTime=%d\r\n", ulEmergentRecordingTime);

                nSecondOffset = -1*ulEmergentRecordingTime;
                AHC_DT_ShiftRtc(&stRtcTime, nSecondOffset);

                AHC_DBG_MSG(0, "AHC_VIDEO_EmergRecPostProcess:AHC_UF_Rename::Old:%d-%d-%d:%d-%d-%d New:%d-%d-%d:%d-%d-%d \r\n",
                            m_stAhcEmergRecdStartRtcTime.uwYear,
                            m_stAhcEmergRecdStartRtcTime.uwMonth,
                            m_stAhcEmergRecdStartRtcTime.uwDay,
                            m_stAhcEmergRecdStartRtcTime.uwHour,
                            m_stAhcEmergRecdStartRtcTime.uwMinute,
                            m_stAhcEmergRecdStartRtcTime.uwSecond,
                            stRtcTime.uwYear,
                            stRtcTime.uwMonth,
                            stRtcTime.uwDay,
                            stRtcTime.uwHour,
                            stRtcTime.uwMinute,
                            stRtcTime.uwSecond);

                if (m_stAhcEmergRecdStartRtcTime.uwYear != 0)
                    AHC_UF_Rename(AHC_UF_GetDB(), &m_stAhcEmergRecdStartRtcTime, &stRtcTime);
            }
        }
        #endif
    }
    #endif

    #if (GPS_RAW_FILE_EMER_EN == 1)
    GPSCtrl_SetGPSRawStart_Emer(AHC_FALSE);
    GPSCtrl_SetGPSRawWriteFirst(AHC_TRUE);
    #endif

    if (AHC_PostEmergencyDone != NULL) {
        AHC_PostEmergencyDone();
    }

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_EmergRecPostProcessMediaError
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_EmergRecPostProcessMediaError(void)
{
    AHC_VIDEO_FILENAME_MGR  *pstPrmEmergFileNameMgr, *pstScdEmergFileNameMgr, *pstUsbEmergFileNameMgr;

    pstPrmEmergFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_PRMEMER);
    pstScdEmergFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_SCDEMER);
    pstUsbEmergFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_USBEMER);

    #if (GPS_RAW_FILE_EMER_EN == 1)
    #if (EMER_RECORD_DUAL_WRITE_ENABLE)
    AHC_VIDEO_SetEmergRecStarted(AHC_FALSE);
    #endif
    GPSCtrl_GPSRawWriteFlushBuf_Emer();
    #endif

    #if (GPS_RAW_FILE_ENABLE == 1)
    if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
    {
        if (GPSCtrl_GPSRawWriteFirst_Normal())
            GPSCtrl_GPSRawResetBuffer();
    }
    #endif

    #if (GPS_CONNECT_ENABLE == 1)
    if (AHC_GPS_Module_Attached())
    {
        #if (GPS_RAW_FILE_EMER_EN == 1)
        UINT8 bGPS_en;

        if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bGPS_en) == AHC_TRUE) {
            switch (bGPS_en) {
            case RECODE_GPS_OFF:
            case RECODE_GPS_IN_VIDEO:
                // NOP
                break;
            default:
                GPSCtrl_GPSRawClose_Emer();
                GPSCtrl_SetGPSRawStart_Emer(AHC_FALSE);
                break;
            }
        }
        #endif
    }
    #endif

    #if (GSENSOR_RAW_FILE_ENABLE == 1 && GPS_CONNECT_ENABLE == 0 && GPS_RAW_FILE_EMER_EN == 1)
    GPSCtrl_GPSRawClose_Emer();
    #endif

    #if (EMER_RECORD_DUAL_WRITE_ENABLE)
    if (AHC_VIDEO_IsEmergPostDone() == AHC_FALSE) {
        DCF_DB_TYPE sType;

        sType = AHC_UF_GetDB();

        AHC_UF_SelectDB(DCF_DB_TYPE_DB2_EVENT);

        AHC_UF_PostAddFile(m_uwEmerVRDirKey,(INT8*)pstPrmEmergFileNameMgr->u8FileName);
        #if (AHC_MULTI_TRACK_EN == 0)
        if (pstScdEmergFileNameMgr->u8DeviceStatus) {
            AHC_UF_PostAddFile(m_uwEmerVRDirKey,(INT8*)pstScdEmergFileNameMgr->u8FileName);
        }
        if (pstUsbEmergFileNameMgr->u8DeviceStatus) {
            AHC_UF_PostAddFile(m_uwEmerVRDirKey,(INT8*)pstUsbEmergFileNameMgr->u8FileName);
        }
        #endif

        AHC_UF_SelectDB(sType);

        AHC_VIDEO_SetEmergPostDone(AHC_TRUE);
        AHC_VIDEO_SetEmergRecStarted(AHC_FALSE);

        if ((MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_DUAL_FILE) ||
            (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)) {
            AHC_VIDEO_SetKernalEmergStopStep(AHC_KERNAL_EMERGENCY_AHC_DONE);
        }
    }
    #endif

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_StopEmergRecord
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_StopEmergRecord(void)
{
    #if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    MMP_ULONG ulEmergentRecordingTime;

    MMPS_3GPRECD_GetEmergentRecordingTime(&ulEmergentRecordingTime);
    #endif

    #if (AHC_EMERGENTRECD_SUPPORT)
    MMPS_3GPRECD_StopEmergentRecd(AHC_TRUE);
    #endif

    #if (EMER_RECORD_DUAL_WRITE_ENABLE)
    AHC_VIDEO_SetEmergRecStarted(AHC_FALSE);
    #endif

    #if 0 // (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    {
        AHC_RTC_TIME    stRtcTime;
        int             nSecondOffset;

        AHC_RTC_GetTime(&stRtcTime);

        if ((m_stAhcEmergRecdStartRtcTime.uwYear <= RTC_DEFAULT_YEAR) && (stRtcTime.uwYear > RTC_DEFAULT_YEAR)) {

            nSecondOffset = -1*(ulEmergentRecordingTime/1000);
            AHC_DT_ShiftRtc(&stRtcTime, nSecondOffset);

            AHC_DBG_MSG(0, "AHC_VIDEO_StopEmergRecord:AHC_UF_Rename::Old:%d-%d-%d:%d-%d-%d New:%d-%d-%d:%d-%d-%d \r\n",
                        m_stAhcEmergRecdStartRtcTime.uwYear,
                        m_stAhcEmergRecdStartRtcTime.uwMonth,
                        m_stAhcEmergRecdStartRtcTime.uwDay,
                        m_stAhcEmergRecdStartRtcTime.uwHour,
                        m_stAhcEmergRecdStartRtcTime.uwMinute,
                        m_stAhcEmergRecdStartRtcTime.uwSecond,
                        stRtcTime.uwYear,
                        stRtcTime.uwMonth,
                        stRtcTime.uwDay,
                        stRtcTime.uwHour,
                        stRtcTime.uwMinute,
                        stRtcTime.uwSecond);

            if (m_stAhcEmergRecdStartRtcTime.uwYear != 0)
                AHC_UF_Rename(AHC_UF_GetDB(), &m_stAhcEmergRecdStartRtcTime, &stRtcTime);
        }
    }
    #endif

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetNormal2Emergency
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_SetNormal2Emergency(AHC_BOOL bState)
{
    #if (AHC_EMERGENTRECD_SUPPORT)
    m_bNormal2Emergency = bState;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetNormal2Emergency
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetNormal2Emergency(void)
{
    #if (AHC_EMERGENTRECD_SUPPORT)
    return m_bNormal2Emergency;
    #endif

    return AHC_FALSE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetDelNormFileAfterEmerg
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_SetDelNormFileAfterEmerg(UINT8 bEnable)
{
    m_bDelNormRecAfterEmr = bEnable;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_NeedDeleteNormalAfterEmerg
//  Description :
//------------------------------------------------------------------------------
UINT8 AHC_VIDEO_NeedDeleteNormalAfterEmerg(void)
{
    return m_bDelNormRecAfterEmr;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_DeleteLatestNormalFile
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_DeleteLatestNormalFile(void)
{
    UINT32 ulIndex = 0;

    AHC_UF_FileOperation_ByIdx(ulIndex, DCF_FILE_DELETE_ALL_CAM, NULL, NULL);
    AHC_VIDEO_SetDelNormFileAfterEmerg(0);
}

#if 0
void _____VR_ShareRec_Function_________(){ruturn;} //dummy
#endif

#if (AHC_SHAREENC_SUPPORT)
static void AHC_VIDEO_SetShareRecdSetting(void)
{
#if (AHC_SHAREENC_SUPPORT)
    MMP_ULONG                   ulBitRate = 0;
    MMPS_3GPRECD_FRAMERATE      stSnrFps, stEncFps, stMgrFps;
    MMPS_3GPRECD_PRESET_CFG     *pstVidPresetCfg = MMPS_3GPRECD_GetPresetCfg();
    MMP_USHORT                  usPFrmNum = 0, usBFrmNum = 0;
    MMP_USHORT                  usQuality = 0;
    MMP_UBYTE                   ubRecdSel = MMPS_VR_SCD_RECD;
    UINT32                      u32Param = 0;

    MMPS_3GPRECD_GetFrameRatePara(MMPS_VR_PRM_RECD, &stSnrFps, &stEncFps, &stMgrFps);

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_COMPRESSION_RATIO, &u32Param);
    usQuality = u32Param;

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_MAX_PFRAME_NUM, &u32Param);
    usPFrmNum = u32Param;

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_MAX_BFRAME_NUM, &u32Param);
    usBFrmNum = u32Param;

    MMPS_3GPRECD_SetH264EncUseMode(VIDENC_STREAM_SCD_RECD, VIDRECD_USEMODE_RECD);

    MMPS_3GPRECD_SetProfile(ubRecdSel, H264ENC_MAIN_PROFILE);

    MMPS_3GPRECD_SetFrameRatePara(ubRecdSel, &stSnrFps, &stEncFps, &stMgrFps);

    if (0)//(uiFrameRateType == VIDRECD_FRAMERATE_60FPS)
        ulBitRate = pstVidPresetCfg->ulFps60BitrateMap[m_usAhcShareRecdResolIdx][usQuality];
    else
        ulBitRate = pstVidPresetCfg->ulFps30BitrateMap[m_usAhcShareRecdResolIdx][usQuality];

    MMPS_3GPRECD_SetBitrate(ubRecdSel, ulBitRate);

    MMPS_3GPRECD_SetPFrameCount(ubRecdSel, usPFrmNum);
    MMPS_3GPRECD_SetBFrameCount(ubRecdSel, usBFrmNum);

    AHC_VIDEO_SetRecdResol( gsAhcScdSensor,
                            pstVidPresetCfg->usEncWidth[m_usAhcShareRecdResolIdx],
                            pstVidPresetCfg->usEncHeight[m_usAhcShareRecdResolIdx]);

    MMPS_3GPRECD_AdjustPrmShareRecdPipe();
#endif
 }

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetShareRecdResIdx
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetShareRecdResIdx(MMP_USHORT usResIdx)
{
    #if (AHC_SHAREENC_SUPPORT)
    m_usAhcShareRecdResolIdx = usResIdx;
    return AHC_TRUE;
    #else
    return AHC_FALSE;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetShareRecdStarted
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetShareRecdStarted(AHC_BOOL bStarted)
{
    #if (AHC_SHAREENC_SUPPORT)
    m_bAhcShareRecdStart = bStarted;
    return AHC_TRUE;
    #else
    return AHC_FALSE;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_IsShareRecdStarted
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_IsShareRecdStarted(void)
{
    #if (AHC_SHAREENC_SUPPORT)
    return m_bAhcShareRecdStart;
    #else
    return AHC_FALSE;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetShareRecdFileName
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetShareRecdFileName(UINT8 *pu8InFileName, AHC_BOOL bFullFileName)
{
#if (AHC_SHAREENC_SUPPORT)
    UINT8                   *pu8FileName = NULL;
    AHC_VIDEO_FILENAME_MGR  *pstShareFileNameMgr = NULL;

    pstShareFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_PRMSHARE);

    if (pu8InFileName == NULL) {
        return AHC_FALSE;
    }

    if (bFullFileName) {
        pu8FileName = pstShareFileNameMgr->u8FullName;
    }
    else {
        pu8FileName = pstShareFileNameMgr->u8FileName;
    }

    strncpy((char*)pu8FileName, (char*)pu8InFileName, MAX_FULL_FILENAME_SIZE);

    return AHC_TRUE;
#else
    return AHC_FALSE;
#endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetShareRecdFileName
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetShareRecdFileName(UINT8** ppu8FileName, AHC_BOOL bFullFileName)
{
#if (AHC_SHAREENC_SUPPORT)
    AHC_VIDEO_FILENAME_MGR *pstShareFileNameMgr = NULL;

    pstShareFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_PRMSHARE);

    if (ppu8FileName == NULL) {
        return AHC_FALSE;
    }

    if (bFullFileName) {
        *ppu8FileName = (UINT8*)pstShareFileNameMgr->u8FullName;
    }
    else {
        *ppu8FileName = (UINT8*)pstShareFileNameMgr->u8FileName;
    }

    if (ppu8FileName[0] == '\0') {
        return AHC_FALSE;
    }
#endif
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetShareRecdTimeLimit
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetShareRecdTimeLimit(UINT32 u32TimeLimit)
{
    #if (AHC_SHAREENC_SUPPORT)
    m_u32AhcShareRecdTimeLimit = u32TimeLimit;

    if (u32TimeLimit < ((0x7FFFFFFF - EM_VR_TIME_LIMIT_OFFSET) / 1000)) {
        u32TimeLimit = u32TimeLimit * 1000 + EM_VR_TIME_LIMIT_OFFSET;
    }

    MMPS_3GPRECD_SetShareFileTimeLimit(u32TimeLimit);
    #endif
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetSharePreEncDuration
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetSharePreEncDuration(MMP_ULONG *pulDurationMs)
{
    #if (AHC_SHAREENC_SUPPORT)
    MMPS_3GPRECD_GetSharePreEncDuration(pulDurationMs);
    return AHC_TRUE;
    #else
    return AHC_FALSE;
    #endif
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_StartSharePreRecord
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_StartSharePreRecord(void)
{
#if (AHC_SHAREENC_SUPPORT)
    MMPS_3GPRECD_StartScdPreEnc(&m_ulAhcSharePreEncTime);

    #if (GPS_CONNECT_ENABLE && (GPS_FUNC & FUNC_VIDEOSTREM_INFO))
    AHC_GPS_StartSHAREPreRec(m_ulAhcSharePreEncTime);
    #endif
    #if (GSENSOR_CONNECT_ENABLE && (GSENSOR_FUNC & FUNC_VIDEOSTREM_INFO))
    AHC_Gsensor_StartSHAREPreRec(m_ulAhcSharePreEncTime);
    #endif
#endif
    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_StartShareRecord
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_StartShareRecord(void)
{
    #if (AHC_SHAREENC_SUPPORT)
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    MMP_ULONG               ulShareRecordingOffset = 0;
    int                     nSecondOffset = 0;
    MMP_BYTE                bShareFullName[MAX_FULL_FILENAME_SIZE];
    MMP_BYTE                byOldFilename[MAX_FULL_FILENAME_SIZE];
    AHC_FS_ATTRIBUTE        stFsAttr;
    AHC_RTC_TIME            stRtcTime;
    UINT8                   u8CreateNewDir = 0;
    DCF_DB_TYPE             eDbType = AHC_UF_GetDB();
    AHC_BOOL                status = AHC_TRUE;
    AHC_VIDEO_FILENAME_MGR  *pstShareFileNameMgr = NULL;

    pstShareFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_PRMSHARE);

    AHC_VIDEO_SetShareRecdStarted(AHC_TRUE);

    if (m_bAhcFirstShareFile == AHC_FALSE)
    {
        AHC_UF_SelectDB(DCF_DB_FORMAT_FREE_DB);

        AHC_RTC_GetTime(&stRtcTime);

        MMPS_3GPRECD_GetRemainFrmTimeOffset(VIDENC_STREAM_SCD_RECD, &ulShareRecordingOffset);
        nSecondOffset = -1*(ulShareRecordingOffset/1000);
        AHC_DT_ShiftRtc(&stRtcTime, nSecondOffset);

        MEMSET(pstShareFileNameMgr->u8FileName, 0, sizeof(pstShareFileNameMgr->u8FileName));
        AHC_UF_GetName2(&stRtcTime, (INT8*)bShareFullName, (INT8*)pstShareFileNameMgr->u8FileName, AHC_Capture_GetCamStatusForDCF());

        STRCAT(bShareFullName, EXT_DOT);
        STRCAT((INT8*)bShareFullName, MOVIE_3GP_EXT);
        STRCAT((INT8*)pstShareFileNameMgr->u8FileName, EXT_DOT);
        STRCAT((INT8*)pstShareFileNameMgr->u8FileName, MOVIE_3GP_EXT);

        status = AHC_UF_SearchAvailableFileSlot(DCF_CAM_FRONT, byOldFilename);

        if (status == AHC_FALSE) {
            AHC_DBG_ERR(1, "%s, search avail file slot failed, %d.\r\n", __FUNCTION__, status);
            AHC_VIDEO_SetShareRecdStarted(AHC_FALSE);
            AHC_UF_SelectDB(eDbType);
            return AHC_FALSE;
        }

        MMPS_FS_FileDirRename(byOldFilename, strlen(byOldFilename), bShareFullName, strlen(bShareFullName));

        if (!AHC_UF_PreAddFile(0, (INT8*)pstShareFileNameMgr->u8FileName)) {
            AHC_DBG_ERR(1, "PreAdd failed\r\n");
        }

        AHC_FS_FileDirGetAttribute(bShareFullName, strlen(bShareFullName), &stFsAttr);

        if (stFsAttr & AHC_FS_ATTR_HIDDEN) {
            stFsAttr &= ~(AHC_FS_ATTR_HIDDEN);
            AHC_FS_FileDirSetAttribute(bShareFullName, strlen(bShareFullName), stFsAttr);
        }

        AHC_UF_SelectDB(eDbType);

        AHC_VIDEO_SetFileName(bShareFullName, STRLEN(bShareFullName), VIDENC_STREAM_SCD_RECD, DCF_CAM_REAR);
    }
    else {
        m_bAhcFirstShareFile = AHC_FALSE;
    }

    AHC_VIDEO_SetShareRecdTimeLimit(DUAL_RECORD_WRITE_INTERVAL);

    eRetErr = MMPS_3GPRECD_StartScdRecd();

    if (eRetErr != MMP_ERR_NONE) {
        AHC_VIDEO_SetShareRecdStarted(AHC_FALSE);
        return AHC_FALSE;
    }

    (void)AHC_VIDEO_SetShareRecdFileName((UINT8*)bShareFullName, AHC_TRUE);
    #endif

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_StopShareRecord
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_StopShareRecord(void)
{
#if (AHC_SHAREENC_SUPPORT)
    MMP_ULONG ulShareRecordingTime = 0;

    MMPS_3GPRECD_GetShareRecordingTime(&ulShareRecordingTime);

    MMPS_3GPRECD_StopScdRecord();

    AHC_DBG_MSG(1, "Share Recd Time [%d]\r\n", ulShareRecordingTime);

    AHC_VIDEO_SetShareRecdStarted(AHC_FALSE);
#endif
    return AHC_TRUE;
}
#endif

#if 0
void _____VR_Audio_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeAudioOn
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_SetRecordModeAudioOn(UINT8 bAudioOn)
{
    m_bAhcVRAudioOn = bAudioOn;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetRecordModeAudioOn
//  Description :
//------------------------------------------------------------------------------
UINT8 AHC_VIDEO_GetRecordModeAudioOn(void)
{
    return m_bAhcVRAudioOn;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecVolumeParam
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecVolumeParam(UINT8 u8Dgain, UINT8 u8AGain)
{
    m_u8AhcAudioDGain = u8Dgain;
    m_u8AhcAudioAGain = u8AGain;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetRecVolumeParam
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_GetRecVolumeParam(UINT8* pu8Dgain, UINT8* pu8AGain)
{
    if (pu8Dgain)
        *pu8Dgain = m_u8AhcAudioDGain;
    if (pu8AGain)
        *pu8AGain = m_u8AhcAudioAGain;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecVolumeToFW
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecVolumeToFW(AHC_BOOL bEnable)
{
    if (bEnable) {
        MMPS_AUDIO_SetRecordVolume(m_u8AhcAudioDGain, m_u8AhcAudioAGain);
    }
    else {
        AHC_DBG_MSG(1, "AHC_VIDEO_SetRecVolumeToFW - Mute\r\n");
        MMPS_AUDIO_SetRecordVolume(0, 0);
    }
    return MMP_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecVolumeByMenuSetting
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecVolumeByMenuSetting(AHC_BOOL bEnable)
{
    UINT32 u32DGain = 0;
    UINT32 u32AGain = 0;

    if (bEnable) {
        AHC_GetParam(PARAM_ID_AUDIO_IN_DIGITAL_GAIN, &u32DGain);
        AHC_GetParam(PARAM_ID_AUDIO_IN_GAIN, &u32AGain);
    }

    AHC_VIDEO_SetRecVolumeParam((UINT8)u32DGain, (UINT8)u32AGain);

    MMPS_AUDIO_SetRecordVolume((UINT8)u32DGain, (UINT8)u32AGain);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetAudioSamplingRate
//  Description :
//------------------------------------------------------------------------------
/** @brief Get the audio sampling rate
   Typically this is for UI or network so that they could know the setting of this build.
*/
UINT32 AHC_VIDEO_GetAudioSamplingRate(UINT8 u8AudioType)
{
    switch(u8AudioType)
    {
    case VR_AUDIO_TYPE_AAC:
        if ((AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_16K_32K) ||
            (AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_16K_64K))
            return 16000;
        else if ((AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_22d05K_64K) ||
                 (AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_22d05K_128K))
            return 22050;
        else if ((AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_32K_64K) ||
                 (AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_32K_128K))
            return 32000;
        else if (AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_48K_128K)
            return 48000;
        else if ((AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_44d1K_64K) ||
                 (AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_44d1K_128K))
            return 44100;
        else
        {
            AHC_DBG_ERR(1, FG_RED("WARNING !!! Un-considered AAC option (1)\r\n"));
            return 32000;
        }
    case VR_AUDIO_TYPE_MP3:
        if (AHC_MP3_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_MP3_32K_128K)
            return 32000;
        else if (AHC_MP3_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_MP3_44d1K_128K)
            return 44100;
        else
        {
            AHC_DBG_ERR(1, FG_RED("WARNING !!! Un-considered MP3 option (1)\r\n"));
            return 32000;
        }
    case VR_AUDIO_TYPE_ADPCM:
        if (AHC_ADPCM_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_ADPCM_16K_22K)
            return 16000;
        else if (AHC_ADPCM_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_ADPCM_32K_22K)
            return 32000;
        else if (AHC_ADPCM_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_ADPCM_44d1K_22K)
            return 44100;
        else
        {
            AHC_DBG_ERR(1, FG_RED("WARNING !!! Un-considered ADPCM option (1)\r\n"));
            return 32000;
        }
    case VR_AUDIO_TYPE_AMR:
        if (AHC_AMR_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AMR_4d75K)
            return 4750;
        else if (AHC_AMR_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AMR_5d15K)
            return 5150;
        else if (AHC_AMR_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AMR_12d2K)
            return 12200;
        else
        {
            AHC_DBG_ERR(1, FG_RED("WARNING !!! Un-considered AMR option (1)\r\n"));
            return 32000;
        }
    case VR_AUDIO_TYPE_PCM:
        if ( AHC_PCM_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_PCM_32K)
            return 32000;
        else if ( AHC_PCM_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_PCM_16K)
            return 16000;
        else
        {
            AHC_DBG_ERR(1, FG_RED("WARNING !!! Un-considered PCM option (1)\r\n"));
            return 32000;
        }
    default:
        AHC_DBG_ERR(1, FG_RED("WARNING !!! Un-supported audio type: %d (1)\r\n"), u8AudioType);
        return 32000;
    }

    return 32000;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetAudioBitRate
//  Description :
//------------------------------------------------------------------------------
/** @brief Get the audio bit rate
   Typically this is for UI or network so that they could know the setting of this build.
*/
UINT32 AHC_VIDEO_GetAudioBitRate(UINT8 u8AudioType)
{
    switch(u8AudioType)
    {
    case VR_AUDIO_TYPE_AAC:
        if (AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_16K_32K)
            return 32000;
        else if ((AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_16K_64K)       ||
                 (AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_22d05K_64K)    ||
                 (AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_32K_64K)       ||
                 (AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_44d1K_64K))
            return 64000;
        else if ((AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_22d05K_128K) ||
                 (AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_32K_128K)    ||
                 (AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_48K_128K)    ||
                 (AHC_AAC_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AAC_44d1K_128K))
            return 128000;
        else
        {
            AHC_DBG_ERR(1, FG_RED("WARNING !!! Un-considered AAC option (2)\r\n"));
            return 128000;
        }
    case VR_AUDIO_TYPE_MP3:
        if ((AHC_MP3_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_MP3_32K_128K) ||
            (AHC_MP3_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_MP3_44d1K_128K))
            return 128000;
        else
        {
            AHC_DBG_ERR(1, FG_RED("WARNING !!! Un-considered MP3 option (2)\r\n"));
            return 128000;
        }
    case VR_AUDIO_TYPE_ADPCM:
        if ((AHC_ADPCM_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_ADPCM_16K_22K) ||
            (AHC_ADPCM_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_ADPCM_32K_22K) ||
            (AHC_ADPCM_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_ADPCM_44d1K_22K))
            return 22000;
        else
        {
            AHC_DBG_ERR(1, FG_RED("WARNING !!! Un-considered ADPCM option (2)\r\n"));
            return 22000;
        }
    case VR_AUDIO_TYPE_PCM:
        if ((AHC_PCM_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_PCM_16K) ||
            (AHC_PCM_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_PCM_32K))
            return 22000;
        else
        {
            AHC_DBG_ERR(1, FG_RED("WARNING !!! Un-considered PCM option (2)\r\n"));
            return 22000;
        }
    case VR_AUDIO_TYPE_AMR:
        if ((AHC_ADPCM_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AMR_4d75K) ||
            (AHC_ADPCM_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AMR_5d15K) ||
            (AHC_ADPCM_AUDIO_OPTION == MMPS_3GPRECD_AUDIO_AMR_12d2K))
            return 8000;
        else
        {
            AHC_DBG_ERR(1, FG_RED("WARNING !!! Un-considered AMR option (2)\r\n"));
            return 8000;
        }
    default:
        AHC_DBG_ERR(1, FG_RED("WARNING !!! Un-supported audio type: %d (2)\r\n"), u8AudioType);
        return 128000;
    }
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetDefaultAudioSamplingRate
//  Description :
//------------------------------------------------------------------------------
/** @brief Get the default audio sampling rate
   Typically this is for UI or network so that they could know the default setting of this build.
   Example usage: RTSP default SDP for audio sampling rate. At that moment the audio parameters are not set.
*/
UINT32 AHC_VIDEO_GetDefaultAudioSamplingRate(void)
{
    return AHC_VIDEO_GetAudioSamplingRate(VR_AUDIO_TYPE);
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_ConfigAudio
//  Description :
//------------------------------------------------------------------------------
/** @brief Config audio stream

  @note Audio bitrate is defined in something like AHC_AAC_AUDIO_OPTION and AHC_MP3_AUDIO_OPTION
        so sampling rate and bit rate will be ignored. Those fields are for back up status only.

  @param stream[in] The audio stream ID
  @param aFormat[in] audio format
  @param channelConfig channel configuration
*/
AHC_BOOL AHC_VIDEO_ConfigAudio( UINT16                     u16StreamId,
                                AHC_AUDIO_FORMAT           tAudFormat,
                                AHC_AUDIO_CHANNEL_CONFIG   tChannelCfg)
{
    AHC_BOOL                    bMute = AHC_FALSE;
    INT32                       u32SoundRecord = 0;
    MMP_ULONG                   ulBitRate = 0, ulSamplingRate = 0;
    MMPS_3GPRECD_AUDIO_FORMAT   eAudFormat;

    // These 2 keeps the value of the setting for quicker reference only. The real settings
    // automatically applied in MMPS
    switch (tAudFormat) {
    case AHC_MOVIE_AUDIO_CODEC_AAC:
        AHC_VIDEO_SetMovieCfg(u16StreamId, AHC_AUD_BITRATE, AHC_VIDEO_GetAudioBitRate(VR_AUDIO_TYPE_AAC));
        AHC_VIDEO_SetMovieCfg(u16StreamId, AHC_AUD_SAMPLE_RATE, AHC_VIDEO_GetAudioSamplingRate(VR_AUDIO_TYPE_AAC));
        break;
    case AHC_MOVIE_AUDIO_CODEC_MP3:
        AHC_VIDEO_SetMovieCfg(u16StreamId, AHC_AUD_BITRATE, AHC_VIDEO_GetAudioBitRate(VR_AUDIO_TYPE_MP3));
        AHC_VIDEO_SetMovieCfg(u16StreamId, AHC_AUD_SAMPLE_RATE, AHC_VIDEO_GetAudioSamplingRate(VR_AUDIO_TYPE_MP3));
        break;
    case AHC_MOVIE_AUDIO_CODEC_ADPCM:
        AHC_VIDEO_SetMovieCfg(u16StreamId, AHC_AUD_BITRATE, AHC_VIDEO_GetAudioBitRate(VR_AUDIO_TYPE_ADPCM));
        AHC_VIDEO_SetMovieCfg(u16StreamId, AHC_AUD_SAMPLE_RATE, AHC_VIDEO_GetAudioSamplingRate(VR_AUDIO_TYPE_ADPCM));
        break;
    case AHC_MOVIE_AUDIO_CODEC_G711:
        (void)AHC_Audio_ParseOptions(AHC_AUDIO_OPTION, &eAudFormat, &ulSamplingRate, &ulBitRate);
        AHC_VIDEO_SetMovieCfg(u16StreamId, AHC_AUD_BITRATE, 8000);//TBD
        AHC_VIDEO_SetMovieCfg(u16StreamId, AHC_AUD_SAMPLE_RATE, ulSamplingRate);
        break;
    case AHC_MOVIE_AUDIO_CODEC_PCM:
        AHC_VIDEO_SetMovieCfg(u16StreamId, AHC_AUD_BITRATE, AHC_VIDEO_GetAudioBitRate(VR_AUDIO_TYPE_PCM));
        AHC_VIDEO_SetMovieCfg(u16StreamId, AHC_AUD_SAMPLE_RATE, AHC_VIDEO_GetAudioSamplingRate(VR_AUDIO_TYPE_PCM));
        break;
    default:
        return AHC_FALSE;
        break;
    }

    if (MMP_FALSE == AHC_VIDEO_SetMovieCfg(u16StreamId, AHC_AUD_CODEC_TYPE, tAudFormat)) {
        return AHC_FALSE;
    }

    AHC_VIDEO_SetMovieCfg(u16StreamId, AHC_AUD_CHANNEL_CONFIG, tChannelCfg);

    if (AHC_Menu_SettingGetCB(COMMON_KEY_RECD_SOUND, &u32SoundRecord) && u32SoundRecord == MOVIE_SOUND_RECORD_ON) {
        bMute = AHC_FALSE;
    }
    else {
        bMute = AHC_TRUE;
    }

    AHC_VIDEO_SetMovieCfg(u16StreamId, AHC_AUD_MUTE_END, bMute);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecWithWNR
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_SetRecWithWNR(AHC_BOOL bEnable)
{
#if (WNR_EN)
    if (bEnable) {
       MMPS_AUDIO_EnableWNR();
    }
    else {
       MMPS_AUDIO_DisableWNR();
    }
#endif
}

#if 0
void _____VR_Recd_Mode_API_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetRecordModeClearException
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_GetRecordModeClearException(void)
{
    m_u32AhcVidRecdExceptionCode = AHC_VIDRECD_MODE_API_MAX;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetRecordModeThrow
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_GetRecordModeThrow(UINT32 u32ExceptionCode)
{
    m_u32AhcVidRecdExceptionCode = u32ExceptionCode;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetRecordModeCatch
//  Description :
//------------------------------------------------------------------------------
UINT32 AHC_VIDEO_GetRecordModeCatch(void)
{
    return m_u32AhcVidRecdExceptionCode;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeInitParameters
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeInitParameters(void)
{
    MMPS_3GPRECD_PRESET_CFG *pVidRecdCfg = MMPS_3GPRECD_GetPresetCfg();
    UINT32                  u32EncWidth = 0, u32EncHeight = 0;
    UINT32                  i = 0, ulMinDiff = 0;
    UINT32                  ulCurDiff = 0;
    MMP_USHORT              usResolIdx = 0;
    AHC_BOOL                ahcRet = AHC_TRUE;

    #if (AHC_ENABLE_VIDEO_STICKER == 0)
    AHC_Capture_SetConfig(ACC_DATE_STAMP, AHC_ACC_TIMESTAMP_DISABLE);
    #endif

    /* Set Record Parameters */
    AHC_VIDEO_GetRecdResol(gsAhcPrmSensor, &u32EncWidth, &u32EncHeight);

    ulMinDiff = (UINT32)(-1);

    for (i = 0; i < VIDRECD_RESOL_MAX_NUM; i++) {
        ulCurDiff = 0;

        if ((u32EncWidth <= pVidRecdCfg->usEncWidth[i]) && (u32EncHeight <= pVidRecdCfg->usEncHeight[i])) {
            ulCurDiff = (pVidRecdCfg->usEncWidth[i] - u32EncWidth) + (pVidRecdCfg->usEncHeight[i] - u32EncHeight);
            if (ulCurDiff < ulMinDiff) {
                usResolIdx = i;
                ulMinDiff = ulCurDiff;
                break;
            }
        }
    }

    AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_RESOLUTION, usResolIdx);

    #if (SUPPORT_ADAS)
    gulADASTimeLimit = AHC_VIDEO_GetRecTimeLimitEx();
    #endif

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeSetBitRate
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeSetBitRate(void)
{
    MMPS_3GPRECD_PRESET_CFG *pVidRecdCfg = MMPS_3GPRECD_GetPresetCfg();
    MMP_USHORT              usResolIdx = 0;
    MMP_USHORT              usQuality = 0;
    UINT32                  u32FrameRateType = 0;
    UINT32                  u32Param = 0;
    AHC_BOOL                ahcRet = AHC_TRUE;
    MMP_ERR                 eRetErr = MMP_ERR_NONE;

    switch (MenuSettingConfig()->uiMOVQuality) {
    case QUALITY_SUPER_FINE:
        usQuality = VIDRECD_QUALITY_HIGH;
        break;
    case QUALITY_FINE:
        usQuality = VIDRECD_QUALITY_MID;
        break;
    default:
        usQuality = VIDRECD_QUALITY_HIGH;
        break;
    }

    AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_COMPRESSION_RATIO, usQuality);
    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_COMPRESSION_RATIO, &u32Param);
    usQuality = u32Param;

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_RESOLUTION, &u32Param);
    usResolIdx = (MMP_USHORT)u32Param;

    #if 0//(EMER_RECORD_DUAL_WRITE_ENABLE == 1)
    if (MenuSettingConfig()->uiGsensorSensitivity != GSENSOR_SENSITIVITY_OFF)
    {
        eRetErr = MMPS_3GPRECD_SetBitrate(MMPS_VR_PRM_RECD, AHC_VIDEO_MAXBITRATE_PRERECORD);
    }
    else
    #endif
    {
        AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, &u32FrameRateType);

        if (u32FrameRateType == VIDRECD_FRAMERATE_60FPS) {
            eRetErr = MMPS_3GPRECD_SetBitrate(MMPS_VR_PRM_RECD, pVidRecdCfg->ulFps60BitrateMap[usResolIdx][usQuality]);
        }
        else {
            eRetErr = MMPS_3GPRECD_SetBitrate(MMPS_VR_PRM_RECD, pVidRecdCfg->ulFps30BitrateMap[usResolIdx][usQuality]);
        }
    }

    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeSetProfile
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeSetProfile(void)
{
    MMP_ERR         eRetErr     = MMP_ERR_NONE;
    VIDENC_PROFILE  eProfile    = H264ENC_MAIN_PROFILE;

    AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_CODEC_TYPE_SETTING, eProfile);

    eRetErr = MMPS_3GPRECD_SetProfile(MMPS_VR_PRM_RECD, eProfile);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeSetContainerType
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeSetContainerType(void)
{
    VIDMGR_CONTAINER_TYPE   eContainerType;
    UINT32                  u32Param = 0;
    AHC_BOOL                ahcRet = AHC_TRUE;
    MMP_ERR                 eRetErr = MMP_ERR_NONE;

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_CLIP_CONTAINER_TYPE, &u32Param);
    eContainerType = u32Param;

    eRetErr = MMPS_3GPRECD_SetContainerType(eContainerType);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeSetFrameRate
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeSetFrameRate(void)
{
    AHC_BOOL                bSlowMotionEn = AHC_FALSE;
    AHC_BOOL                bTimeLapseEn = AHC_FALSE;
    UINT32                  u32SlowMotionTimeIncrement = 0, u32SlowMotionTimeResol = 0;
    UINT32                  u32TimeLapseTimeIncrement = 0, u32TimeLapseTimeResol = 0;
    UINT32                  u32FrameRateIdx = 0;
    UINT32                  u32FrameRateX1000 = 0;
    MMP_SNR_ANADEC_SRC_TYPE eAnaDecSrcType = MMP_SNR_ANADEC_SRC_NO_READY;
    MMPS_3GPRECD_FRAMERATE  stSnrFps, stEncFps, stMgrFps;
    UINT32                  u32Param = 0;
    AHC_BOOL                ahcRet = AHC_TRUE;
    MMP_ERR                 eRetErr = MMP_ERR_NONE;

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_FRAME_RATE, &u32Param);
    u32FrameRateIdx = u32Param;

    u32FrameRateX1000 = AHC_VIDEO_GetVideoRealFpsX1000(u32FrameRateIdx);

    if (CAM_CHECK_PRM(PRM_CAM_ANA_DECODER)) {
        MMPS_Sensor_GetAnaDecSrcType(&eAnaDecSrcType);

        if (eAnaDecSrcType == MMP_SNR_ANADEC_SRC_PAL)
            stSnrFps.ulTimeIncre = AHC_VIDRECD_TIME_INCREMENT_BASE_PAL;
        else if (eAnaDecSrcType == MMP_SNR_ANADEC_SRC_NTSC)
            stSnrFps.ulTimeIncre = AHC_VIDRECD_TIME_INCREMENT_BASE_NTSC;
        else
            stSnrFps.ulTimeIncre = AHC_VIDRECD_TIME_INCREMENT_BASE;
    }
    else {
        stSnrFps.ulTimeIncre = AHC_VIDRECD_TIME_INCREMENT_BASE;
    }

    stSnrFps.ulTimeResol = u32FrameRateX1000;

    DBG_AutoTestPrint(ATEST_ACT_REC_0x0001, ATEST_STS_FRAME_RATE_0x0006, 0, stSnrFps.ulTimeResol, gbAhcDbgBrk);

    AHC_VIDEO_GetSlowMotionFPS(&bSlowMotionEn, &u32SlowMotionTimeIncrement, &u32SlowMotionTimeResol);
    #if (defined(VIDEO_REC_TIMELAPSE_EN) && VIDEO_REC_TIMELAPSE_EN)
    AHC_VIDEO_GetTimeLapseFPS(&bTimeLapseEn, &u32TimeLapseTimeIncrement, &u32TimeLapseTimeResol);
    #endif

    if (bSlowMotionEn) {
        // Slow Motion Record
        stMgrFps.ulTimeIncre = u32SlowMotionTimeIncrement;
        stMgrFps.ulTimeResol = u32SlowMotionTimeResol;
        if ((stSnrFps.ulTimeIncre * stSnrFps.ulTimeResol) < (stMgrFps.ulTimeIncre * stMgrFps.ulTimeResol)){
            AHC_DBG_ERR(1, FG_RED("SlowMotion Error! %d,%d,%d,%d\r\n"), stSnrFps.ulTimeIncre, stSnrFps.ulTimeResol, stMgrFps.ulTimeIncre, stMgrFps.ulTimeResol);
            stMgrFps.ulTimeIncre = stSnrFps.ulTimeIncre;
            stMgrFps.ulTimeResol = stSnrFps.ulTimeResol;
        }
    }
    else {
        // Normal Record (Non-Slow Motion)
        stMgrFps.ulTimeIncre = stSnrFps.ulTimeIncre;
        stMgrFps.ulTimeResol = stSnrFps.ulTimeResol;
    }

    if (bTimeLapseEn) {
        // Time Lapse Record
        stEncFps.ulTimeIncre = u32TimeLapseTimeIncrement;
        stEncFps.ulTimeResol = u32TimeLapseTimeResol;
        if ((stSnrFps.ulTimeIncre * stSnrFps.ulTimeResol) < (stEncFps.ulTimeIncre * stEncFps.ulTimeResol)){
            AHC_DBG_ERR(1, FG_RED("TimeLapse Error! %d,%d,%d,%d\r\n"), stSnrFps.ulTimeIncre, stSnrFps.ulTimeResol, stEncFps.ulTimeIncre, stEncFps.ulTimeResol);
            stEncFps.ulTimeIncre = stSnrFps.ulTimeIncre;
            stEncFps.ulTimeResol = stSnrFps.ulTimeResol;
        }
    }
    else {
        // Normal Record (Non-VideoTimeLapse)
        stEncFps.ulTimeIncre = stSnrFps.ulTimeIncre;
        stEncFps.ulTimeResol = stSnrFps.ulTimeResol;
    }

    eRetErr = MMPS_3GPRECD_SetFrameRatePara(MMPS_VR_PRM_RECD, &stSnrFps, &stEncFps, &stMgrFps);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeSetP_BFrameCount
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeSetP_BFrameCount(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    UINT32      u32PFrmNum = 0, u32BFrmNum = 0;
    UINT32      u32Param = 0;

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_MAX_PFRAME_NUM, &u32Param);
    u32PFrmNum = u32Param;

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_MAX_BFRAME_NUM, &u32Param);
    u32BFrmNum = u32Param;

    eRetErr = MMPS_3GPRECD_SetBFrameCount(MMPS_VR_PRM_RECD, u32BFrmNum);

    eRetErr = MMPS_3GPRECD_SetPFrameCount(MMPS_VR_PRM_RECD, u32PFrmNum);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeSetAudioEncode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeSetAudioEncode(void)
{
    MMPS_3GPRECD_AUDIO_FORMAT   eAudioFmt = MMPS_3GPRECD_AUDIO_FORMAT_AAC;
    MMPS_AUDIO_LINEIN_CHANNEL   eAudioLineIn = MMPS_AUDIO_LINEIN_DUAL;
    MMP_UBYTE                   ubWMR = 0;
    MMP_UBYTE                   ubRecordWithAudio = 0;
    MMP_ULONG                   ulSampleRate = 0;
    UINT32                      u32Param = 0;
    UINT8                       bAudioOn = 1;
    AHC_BOOL                    ahcRet = AHC_TRUE;
    MMP_ERR                     eRetErr = MMP_ERR_NONE;

    bAudioOn = AHC_VIDEO_GetRecordModeAudioOn();

    if (bAudioOn) {
        AIHC_InitAudioExtDACIn();
    }

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_AUD_CODEC_TYPE, &u32Param);
    eAudioFmt = u32Param;

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_AUD_SAMPLE_RATE, &u32Param);
    ulSampleRate = u32Param;

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_AUD_CHANNEL_CONFIG, &u32Param);
    eAudioLineIn = u32Param;

    if (m_bAhcSlowMotionEn || m_bAhcTimeLapseEn) {
        eRetErr = MMPS_3GPRECD_SetAudioRecMode(MMPS_3GPRECD_NO_AUDIO_DATA);
    }
    else if (bAudioOn) {
        eRetErr = MMPS_3GPRECD_SetAudioRecMode(MMPS_3GPRECD_REC_AUDIO_DATA);
    }
    else {
        eRetErr = MMPS_3GPRECD_SetAudioRecMode(MMPS_3GPRECD_SILENCE_AUDIO_DATA);
    }

    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    eRetErr = MMPS_AUDIO_SetLineInChannel(eAudioLineIn);

    if (eAudioFmt == MMPS_3GPRECD_AUDIO_FORMAT_AMR) {
        eRetErr = MMPS_3GPRECD_SetAudioFormat(eAudioFmt, AHC_AMR_AUDIO_OPTION);
    }
    else if (eAudioFmt == MMPS_3GPRECD_AUDIO_FORMAT_AAC) {
        eRetErr = MMPS_3GPRECD_SetAudioFormat(eAudioFmt, AHC_AAC_AUDIO_OPTION);
    }
    else if (eAudioFmt == MMPS_3GPRECD_AUDIO_FORMAT_ADPCM) {
        eRetErr = MMPS_3GPRECD_SetAudioFormat(eAudioFmt, AHC_ADPCM_AUDIO_OPTION);
    }
    else if (eAudioFmt == MMPS_3GPRECD_AUDIO_FORMAT_MP3) {
        eRetErr = MMPS_3GPRECD_SetAudioFormat(eAudioFmt, AHC_MP3_AUDIO_OPTION);
    }
    else if (eAudioFmt == MMPS_3GPRECD_AUDIO_FORMAT_PCM) {
        eRetErr = MMPS_3GPRECD_SetAudioFormat(eAudioFmt, AHC_PCM_AUDIO_OPTION);
    }

    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    AHC_Menu_SettingGetCB((char *)COMMON_KEY_WNR_EN, &ubWMR);
    #ifdef COMMON_KEY_RECORD_WITH_AUDIO
    AHC_Menu_SettingGetCB((char *)COMMON_KEY_RECORD_WITH_AUDIO, &ubRecordWithAudio);
    #else
    AHC_Menu_SettingGetCB((char *)"RecordWithAudio", &ubRecordWithAudio);
    #endif

    if ((ubWMR == WNR_ON) && bAudioOn && (ubRecordWithAudio == MOVIE_SOUND_RECORD_ON)) {
        AHC_VIDEO_SetRecWithWNR(AHC_TRUE);
    }
    else {
        AHC_VIDEO_SetRecWithWNR(AHC_FALSE);
    }

#if (VIDEO_REC_WITH_MUTE_EN)
    #if ((MENU_MOVIE_EN && MENU_MOVIE_SOUND_RECORD_EN) || (MENU_SINGLE_EN))
    if ((MenuSettingConfig()->uiMOVSoundRecord == MOVIE_SOUND_RECORD_ON) && !m_bAhcSlowMotionEn && !m_bAhcTimeLapseEn)
    #else
    if (1)
    #endif
    #if (SETTING_VR_VOLUME_EVERYTIME)
    {
        AHC_VIDEO_SetRecVolumeToFW(AHC_TRUE);
    }
    else
    {
        AHC_VIDEO_SetRecVolumeToFW(AHC_FALSE);
    }
    #endif
#endif

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeSetTimeLimit
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeSetTimeLimit(void)
{
    UINT32      u32TimeLimit = 0;
    AHC_BOOL    ahcRet = AHC_TRUE;

    u32TimeLimit = AHC_VIDEO_GetRecTimeLimitEx();

    AHC_VIDEO_SetRecTimeLimit(u32TimeLimit);

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeSetDualEncode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeSetDualEncode(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    if ((AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_SCD, AHC_TRUE) & VID_RECD_ENCODE_H264) ||
        (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_TRUE) & VID_RECD_ENCODE_H264)) {
        eRetErr = MMPS_3GPRECD_EnableScdRecd(MMP_TRUE);
    }
    else {
        eRetErr = MMPS_3GPRECD_EnableScdRecd(MMP_FALSE);
    }

    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr);}

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModePreSetFilename
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModePreSetFilename(void)
{
    VIDMGR_CONTAINER_TYPE   eContainerType = VIDMGR_CONTAINER_3GP;
    UINT8                   u8CreateNewDir = 0;
    MMP_BYTE                DirName[16];
    UINT32                  u32Param = 0;
    AHC_BOOL                ahcRet = AHC_TRUE;
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    MMP_UBYTE               *pubExtName = NULL;
    AHC_VIDEO_FILENAME_MGR  *pstPrmRecdFileNameMgr, *pstScdRecdFileNameMgr, *pstUsbRecdFileNameMgr;
    #if (GPS_KML_FILE_ENABLE == 1)
    MMP_BYTE                bKMLFileName[MAX_FULL_FILENAME_SIZE];
    #endif
    #if (GPS_RAW_FILE_ENABLE == 1)
    MMP_BYTE                bGPSRawFileName[MAX_FULL_FILENAME_SIZE];
    #endif
    #if ((GSENSOR_RAW_FILE_ENABLE == 1) && (GPS_CONNECT_ENABLE == 0))
    MMP_BYTE                bGPSRawFileName[MAX_FULL_FILENAME_SIZE];
    #endif
    #if (AHC_SHAREENC_SUPPORT)
    UINT32                  uiFrameRateType = 0; //Need to check...
    MMP_UBYTE               *uByteTemp;
    #endif

    // Check current connect status, update only once when record flow starts
    AHC_VIDEO_UpdateCurCnntStatusByType(AHC_VIDRECD_FILENAME_PRMREC);
    AHC_VIDEO_UpdateCurCnntStatusByType(AHC_VIDRECD_FILENAME_SCDREC);
    AHC_VIDEO_UpdateCurCnntStatusByType(AHC_VIDRECD_FILENAME_USBREC);

    pstPrmRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_PRMREC);
    pstScdRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_SCDREC);
    pstUsbRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_USBREC);

    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_CLIP_CONTAINER_TYPE, &u32Param);
    eContainerType = (VIDMGR_CONTAINER_TYPE)u32Param;

    if (AHC_VIDEO_GetFirstTimeRecord() == MMP_TRUE) {
        eRetErr = MMPS_3GPRECD_SetStoragePath(VIDENC_OUT_MODE_CARD);
        if (eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

        // First record
        MEMSET(m_bPrevPrmRecdFullName, 0, sizeof(m_bPrevPrmRecdFullName));
    }
    else {
        // Restart record
        MEMCPY(m_bPrevPrmRecdFullName, pstPrmRecdFileNameMgr->u8FullName, sizeof(pstPrmRecdFileNameMgr->u8FullName));
    }

    /* Reset Dir/File Name/Full Name Array */
    MEMSET(DirName, 0, sizeof(DirName));

    if (pstPrmRecdFileNameMgr->u8DeviceStatus) {
        MEMSET(pstPrmRecdFileNameMgr->u8FullName, 0, sizeof(pstPrmRecdFileNameMgr->u8FullName));
        MEMSET(pstPrmRecdFileNameMgr->u8FileName, 0, sizeof(pstPrmRecdFileNameMgr->u8FileName));
        #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
        MEMSET(m_CurThumbJpgFullName, 0, sizeof(m_CurThumbJpgFullName));
        MEMSET(m_ThumbJpgFileName, 0, sizeof(m_ThumbJpgFileName));
        #endif
    }

    #if (AHC_MULTI_TRACK_EN == 0)
    if (pstScdRecdFileNameMgr->u8DeviceStatus) {
        MEMSET(pstScdRecdFileNameMgr->u8FullName, 0, sizeof(pstScdRecdFileNameMgr->u8FullName));
        MEMSET(pstScdRecdFileNameMgr->u8FileName, 0, sizeof(pstScdRecdFileNameMgr->u8FileName));
        #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
        MEMSET(m_CurThumbJpgFullName_Rear, 0, sizeof(m_CurThumbJpgFullName_Rear));
        MEMSET(m_ThumbJpgFileName_Rear, 0, sizeof(m_ThumbJpgFileName_Rear));
        #endif
    }

    if (pstUsbRecdFileNameMgr->u8DeviceStatus) {
        MEMSET(pstUsbRecdFileNameMgr->u8FullName, 0, sizeof(pstUsbRecdFileNameMgr->u8FullName));
        MEMSET(pstUsbRecdFileNameMgr->u8FileName, 0, sizeof(pstUsbRecdFileNameMgr->u8FileName));
        #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
        MEMSET(m_CurThumbJpgFullName_USBH, 0, sizeof(m_CurThumbJpgFullName_USBH));
        MEMSET(m_ThumbJpgFileName_USBH, 0, sizeof(m_ThumbJpgFileName_USBH));
        #endif
    }
    #endif

#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)

    ahc_ret = AHC_UF_GetName(&m_u16CurVideoDirKey, (INT8*)DirName, (INT8*)m_pu8CurPrmRecdFileName, &u8CreateNewDir);

    if (ahc_ret  == AHC_TRUE) {

        STRCPY(m_bCurPrmRecdFullName, (INT8*)AHC_UF_GetRootDirName());
        STRCAT(m_bCurPrmRecdFullName, "\\");
        STRCAT(m_bCurPrmRecdFullName, DirName);

        if (u8CreateNewDir) {
            MMPS_FS_DirCreate((INT8*)m_bCurPrmRecdFullName, STRLEN(m_bCurPrmRecdFullName));
            AHC_UF_AddDir(DirName);
        }

        STRCAT(m_bCurPrmRecdFullName, "\\");
        STRCAT(m_bCurPrmRecdFullName, (INT8*)m_pu8CurPrmRecdFileName);
    }
#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    {
        MMP_ULONG       ulRecordingOffset = 0;
        int             nSecondOffset = 0;
        AHC_RTC_TIME    stCurRtctime;
        DCF_DB_TYPE     eDBType = AHC_UF_GetDB();
        UINT8           u8CamStatus = AHC_Capture_GetCamStatusForDCF();

        AHC_RTC_GetTime(&stCurRtctime);

        #if 1 // For Pre-Encode
        {
            UINT16  uwYear = 0, uwMonth = 0, uwDay = 0, uwDayInWeek = 0;
            UINT16  uwHour = 0, uwMinute = 0, uwSecond = 0;
            UINT8   ubAmOrPm = 0, b_12FormatEn = 0;

            if (!AHC_DT_IsDateValid((stCurRtctime.uwYear - RTC_DEFAULT_YEAR), stCurRtctime.uwMonth, stCurRtctime.uwDay))
            {
                AHC_DBG_ERR(1, "Wrong RTC time %d:%d:%d:%d:%d:%d\r\n",
                            stCurRtctime.uwYear, stCurRtctime.uwMonth, stCurRtctime.uwDay,
                            stCurRtctime.uwHour, stCurRtctime.uwMinute, stCurRtctime.uwSecond);

                AHC_RestoreDefaultTime(&uwYear, &uwMonth, &uwDay, &uwDayInWeek, &uwHour, &uwMinute, &uwSecond, &ubAmOrPm, &b_12FormatEn);
                AHC_SetClock(uwYear, uwMonth, uwDay, uwDayInWeek, uwHour+1, uwMinute, uwSecond, ubAmOrPm, b_12FormatEn);
                AHC_OS_SleepMs(10);

                AHC_RTC_UpdateTime();
                AHC_RTC_GetTime(&stCurRtctime);
            }
        }
        #endif

        if (uiGetParkingModeEnable()) {
            AHC_UF_SelectDB(DCF_DB_TYPE_DB1_PARKING); // Make sure PARKING DB
        }
        else {
            AHC_UF_SelectDB(DCF_DB_TYPE_DB0_NORMAL); // Make sure NORMAL DB
        }

        m_stAhcVidRecdStartRtcTime = stCurRtctime;

        eRetErr = MMPS_3GPRECD_GetRemainFrmTimeOffset(VIDENC_STREAM_PRM_RECD, &ulRecordingOffset);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

        nSecondOffset = -1*(ulRecordingOffset/1000);
        ahcRet = AHC_DT_ShiftRtc(&m_stAhcVidRecdStartRtcTime, nSecondOffset);

        if (pstPrmRecdFileNameMgr->u8DeviceStatus) {
            AHC_UF_SetRearCamPathFlag(AHC_FALSE);
            ahcRet = AHC_UF_GetName2(&m_stAhcVidRecdStartRtcTime, (INT8*)pstPrmRecdFileNameMgr->u8FullName, (INT8*)pstPrmRecdFileNameMgr->u8FileName, u8CamStatus);
        }

        #if (AHC_MULTI_TRACK_EN == 0)
        if (pstScdRecdFileNameMgr->u8DeviceStatus) {
            AHC_UF_SetRearCamPathFlag(AHC_TRUE);
            ahcRet = AHC_UF_GetName2(&m_stAhcVidRecdStartRtcTime, (INT8*)pstScdRecdFileNameMgr->u8FullName, (INT8*)pstScdRecdFileNameMgr->u8FileName, u8CamStatus);
            AHC_UF_SetRearCamPathFlag(AHC_FALSE);
        }

        if (pstUsbRecdFileNameMgr->u8DeviceStatus) {
            AHC_UF_SetRearCamPathFlag(AHC_TRUE);
            ahcRet = AHC_UF_GetName2(&m_stAhcVidRecdStartRtcTime, (INT8*)pstUsbRecdFileNameMgr->u8FullName, (INT8*)pstUsbRecdFileNameMgr->u8FileName, u8CamStatus);
            AHC_UF_SetRearCamPathFlag(AHC_FALSE);
        }
        #endif

        AHC_UF_SelectDB(eDBType);
    }
#endif

    if (ahcRet != AHC_TRUE) {
        AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr);
        return AHC_FALSE;
    }

    if (pstPrmRecdFileNameMgr->u8DeviceStatus) {
        STRCAT(pstPrmRecdFileNameMgr->u8FullName, EXT_DOT);
        STRCAT(pstPrmRecdFileNameMgr->u8FileName, EXT_DOT);
        #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
        STRCPY(m_CurThumbJpgFullName, pstPrmRecdFileNameMgr->u8FullName);
        #endif
    }

    #if (AHC_MULTI_TRACK_EN == 0)
    if (pstScdRecdFileNameMgr->u8DeviceStatus) {
        STRCAT(pstScdRecdFileNameMgr->u8FullName, EXT_DOT);
        STRCAT(pstScdRecdFileNameMgr->u8FileName, EXT_DOT);
        #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
        STRCPY(m_CurThumbJpgFullName_Rear, pstScdRecdFileNameMgr->u8FullName);
        #endif
    }

    if (pstUsbRecdFileNameMgr->u8DeviceStatus) {
        STRCAT(pstUsbRecdFileNameMgr->u8FullName, EXT_DOT);
        STRCAT(pstUsbRecdFileNameMgr->u8FileName, EXT_DOT);
        #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
        STRCPY(m_CurThumbJpgFullName_USBH, pstUsbRecdFileNameMgr->u8FullName);
        #endif
    }
    #endif

    #if (GPS_CONNECT_ENABLE == 1)
    if (AHC_GPS_Module_Attached())
    {
        #if (GPS_KML_FILE_ENABLE == 1)
        MEMSET(bKMLFileName, 0, sizeof(bKMLFileName));
        STRCPY(bKMLFileName, pstPrmRecdFileNameMgr->u8FullName);
        STRCAT(bKMLFileName, GPS_KML_FILE_EXTENTION);
        #endif
        #if (GPS_RAW_FILE_ENABLE == 1)
        MEMSET(bGPSRawFileName, 0, sizeof(bGPSRawFileName));
        STRCPY(bGPSRawFileName, pstPrmRecdFileNameMgr->u8FullName);
        STRCAT(bGPSRawFileName, GPS_RAW_FILE_EXTENTION);
        #endif
    }
    #endif

    #if (GSENSOR_RAW_FILE_ENABLE == 1 && GPS_CONNECT_ENABLE == 0)
    MEMSET(bGPSRawFileName, 0, sizeof(bGPSRawFileName));
    STRCPY(bGPSRawFileName, pstPrmRecdFileNameMgr->u8FullName);
    STRCAT(bGPSRawFileName, GPS_RAW_FILE_EXTENTION);
    #endif

    if (eContainerType == VIDMGR_CONTAINER_3GP) {
        pubExtName = MOVIE_3GP_EXT;
    }
    else if (eContainerType == VIDMGR_CONTAINER_TS) {
        pubExtName = MOVIE_TS_EXT;
    }
    else {
        pubExtName = MOVIE_AVI_EXT;
    }

    if (pstPrmRecdFileNameMgr->u8DeviceStatus) {
        STRCAT(pstPrmRecdFileNameMgr->u8FullName, pubExtName);

        #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
        STRCAT(m_CurThumbJpgFullName, PHOTO_JPG_EXT);
        MEMCPY(m_ThumbJpgFileName, pstPrmRecdFileNameMgr->u8FileName, sizeof(pstPrmRecdFileNameMgr->u8FileName));
        STRCAT((INT8*)m_ThumbJpgFileName, PHOTO_JPG_EXT);
        #endif

        STRCAT((INT8*)pstPrmRecdFileNameMgr->u8FileName, pubExtName);
    }

    #if (AHC_MULTI_TRACK_EN == 0)
    if (pstScdRecdFileNameMgr->u8DeviceStatus) {
        STRCAT((UINT8*)pstScdRecdFileNameMgr->u8FullName, pubExtName);

        #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
        STRCAT(m_CurThumbJpgFullName_Rear, PHOTO_JPG_EXT);
        MEMCPY(m_ThumbJpgFileName_Rear, pstScdRecdFileNameMgr->u8FileName, sizeof(m_ThumbJpgFileName_Rear));
        STRCAT((INT8*)m_ThumbJpgFileName_Rear, PHOTO_JPG_EXT);
        #endif

        STRCAT((INT8*)pstScdRecdFileNameMgr->u8FileName, pubExtName);
    }

    if (pstUsbRecdFileNameMgr->u8DeviceStatus) {
        STRCAT(pstUsbRecdFileNameMgr->u8FullName, pubExtName);

        #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
        STRCAT(m_CurThumbJpgFullName_USBH, PHOTO_JPG_EXT);
        MEMCPY(m_ThumbJpgFileName_USBH, pstUsbRecdFileNameMgr->u8FileName, sizeof(m_ThumbJpgFileName_USBH));
        STRCAT((INT8*)m_ThumbJpgFileName_USBH, PHOTO_JPG_EXT);
        #endif

        STRCAT((INT8*)pstUsbRecdFileNameMgr->u8FileName, pubExtName);
    }
    #endif

    if (pstPrmRecdFileNameMgr->u8DeviceStatus) {
        eRetErr = AHC_VIDEO_SetFileName(pstPrmRecdFileNameMgr->u8FullName, STRLEN(pstPrmRecdFileNameMgr->u8FullName), VIDENC_STREAM_PRM_RECD, DCF_CAM_FRONT);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
    }

    #if (AHC_SHAREENC_SUPPORT)
    AHC_VIDEO_SetShareRecdSetting();
    #endif

    #if (AHC_MULTI_TRACK_EN == 0)
    if (pstScdRecdFileNameMgr->u8DeviceStatus) {
        eRetErr = AHC_VIDEO_SetFileName(pstScdRecdFileNameMgr->u8FullName, STRLEN(pstScdRecdFileNameMgr->u8FullName), VIDENC_STREAM_SCD_RECD, DCF_CAM_REAR);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
    }

    if (pstUsbRecdFileNameMgr->u8DeviceStatus) {
        if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_TRUE) & VID_RECD_ENCODE_H264) {
            eRetErr = AHC_VIDEO_SetFileName(pstUsbRecdFileNameMgr->u8FullName, STRLEN(pstUsbRecdFileNameMgr->u8FullName), VIDENC_STREAM_SCD_RECD, DCF_CAM_REAR);
        }
        else {
            eRetErr = AHC_VIDEO_SetFileName(pstUsbRecdFileNameMgr->u8FullName, STRLEN(pstUsbRecdFileNameMgr->u8FullName), VIDENC_STREAM_UVC_RECD, DCF_CAM_REAR);
        }
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
    }
    #endif

    #if (GPS_CONNECT_ENABLE == 1)
    if (AHC_GPS_Module_Attached())
    {
        #if (GPS_KML_FILE_ENABLE == 1)
        GPSCtrl_SetKMLFileName(bKMLFileName,STRLEN(bKMLFileName));
        #endif

        #if (GPS_RAW_FILE_ENABLE == 1)
        {
            UINT8 bGPS_en;

            if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bGPS_en) == AHC_TRUE) {
                switch (bGPS_en) {
                case RECODE_GPS_OFF:
                case RECODE_GPS_IN_VIDEO:
                    // NOP
                    break;
                default:
                    #if (SUPPORT_PARKINGMODE != PARKINGMODE_NONE)
                    if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
                    {
                        MMP_ULONG ulRecordingOffset = 0;

                        eRetErr = MMPS_3GPRECD_GetRemainFrmTimeOffset(VIDENC_STREAM_PRM_RECD, &ulRecordingOffset);
                        if (eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); return AHC_FALSE;}
                        #if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
                        GPSCtrl_SetGPSRawBufTime_Normal(ulRecordingOffset/1000);
                        #endif
                    }
                    #endif

                    GPSCtrl_SetGPSRawFileName(bGPSRawFileName, STRLEN(bGPSRawFileName));
                    break;
                }
            }
        }
        #endif
    }
    #endif

    #if (GSENSOR_RAW_FILE_ENABLE == 1 && GPS_CONNECT_ENABLE == 0)
    {
        #if (SUPPORT_PARKINGMODE != PARKINGMODE_NONE)
        if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
        {
            MMP_ULONG ulRecordingOffset = 0;

            eRetErr = MMPS_3GPRECD_GetRemainFrmTimeOffset(VIDENC_STREAM_PRM_RECD, &ulRecordingOffset);
            if (eRetErr != MMP_ERR_NONE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); return AHC_FALSE;}
            #if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
            GPSCtrl_SetGPSRawBufTime_Normal(ulRecordingOffset/1000);
            #endif
        }
        #endif

        GPSCtrl_SetGPSRawFileName(bGPSRawFileName,STRLEN(bGPSRawFileName));
    }
    #endif

    #if (SUPPORT_PARKINGMODE != PARKINGMODE_NONE)
    #if (GPS_RAW_FILE_ENABLE == 1)
    if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE)
    {
        GPSCtrl_GPSRawWriteFirst_Normal();
        GPSCtrl_GPSRawResetBuffer();
    }
    #endif
    #endif

    if (pstPrmRecdFileNameMgr->u8DeviceStatus) {
        AHC_DBG_MSG(1, "[PRM] %s\r\n", pstPrmRecdFileNameMgr->u8FullName);
    }
    #if (AHC_MULTI_TRACK_EN == 0)
    if (pstScdRecdFileNameMgr->u8DeviceStatus) {
        AHC_DBG_MSG(1, "[SCD] %s\r\n", pstScdRecdFileNameMgr->u8FullName);
    }
    if (pstUsbRecdFileNameMgr->u8DeviceStatus) {
        AHC_DBG_MSG(1, "[UVC] %s\r\n", pstUsbRecdFileNameMgr->u8FullName);
    }
    #endif

    #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
    AHC_DBG_MSG(1, "[Thumb] %s\r\n", m_CurThumbJpgFullName);
    #endif

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModePostSetFilename
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModePostSetFilename(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;
    AHC_ERR     ahcErr = AHC_ERR_NONE;

    /* Open GPS/Gsensor Temp File */
    #if (FS_FORMAT_FREE_ENABLE == 0) // Do NOT support GPS / Gsensor temp file in Format Free.
    #if (GPS_CONNECT_ENABLE && GPS_USE_FILE_AS_DATABUF)
    if (AHC_GPS_Module_Attached())
    {
        MMP_BYTE    bGpsInfoFileName[MAX_FULL_FILENAME_SIZE];
        MMP_ULONG   ulGpsInfoDirID = 0;

        STRCPY(bGpsInfoFileName, (INT8*)AHC_UF_GetRootName());
        STRCAT(bGpsInfoFileName, GPS_TEMP_INFOFILE_DIR);

        if (AHC_FS_DirOpen(bGpsInfoFileName, sizeof(bGpsInfoFileName), &ulGpsInfoDirID) != AHC_ERR_NONE) {
            ahcErr = AHC_FS_DirCreate(bGpsInfoFileName, sizeof(bGpsInfoFileName));
            ahcErr = AHC_FS_FileDirSetAttribute(bGpsInfoFileName, sizeof(bGpsInfoFileName), AHC_FS_ATTR_HIDDEN);
        }
        else {
            AHC_FS_DirClose(ulGpsInfoDirID);
        }

        STRCAT(bGpsInfoFileName, "\\");
        STRCAT(bGpsInfoFileName, (INT8*)GPS_TEMP_INFOFILE_NAME);

        GPSCtrl_OpenInfoFile(bGpsInfoFileName);
    }
    #endif

    #if ((GSENSOR_CONNECT_ENABLE) && (GSENSOR_FUNC & FUNC_VIDEOSTREM_INFO) && GSNR_USE_FILE_AS_DATABUF)
    if (AHC_Gsensor_Module_Attached())
    {
        MMP_BYTE    bGsensorInfoFileName[MAX_FULL_FILENAME_SIZE] = {0};
        MMP_ULONG   ulGsensorInfoDirID = 0;

        STRCPY(bGsensorInfoFileName, (INT8*)AHC_UF_GetRootName());
        STRCAT(bGsensorInfoFileName, GSNR_TEMP_INFOFILE_DIR);

        if (AHC_FS_DirOpen(bGsensorInfoFileName, sizeof(bGsensorInfoFileName), &ulGsensorInfoDirID) != AHC_ERR_NONE) {

            ahcErr = AHC_FS_DirCreate(bGsensorInfoFileName, sizeof(bGsensorInfoFileName));
            ahcErr = AHC_FS_FileDirSetAttribute(bGsensorInfoFileName, sizeof(bGsensorInfoFileName), AHC_FS_ATTR_HIDDEN);
        }
        else {
            ahcErr = AHC_FS_DirClose(ulGsensorInfoDirID);
        }

        STRCAT(bGsensorInfoFileName, "\\");
        STRCAT(bGsensorInfoFileName, (INT8*)GSNR_TEMP_INFOFILE_NAME);

        AHC_Gsensor_OpenInfoFile(bGsensorInfoFileName);
    }
    #endif
    #endif

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeRegisterCallback
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeRegisterCallback(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    #if (VR_SLOW_CARD_DETECT)
    eRetErr = MMPS_3GPRECD_SetNormalSkipFrmParam(VRCB_TOTAL_SKIP_FRAME, VRCB_CONTINUOUS_SKIP_FRAME);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
    eRetErr = MMPS_3GPRECD_SetSeamlessSkipFrmParam(VRCB_TOTAL_SKIP_FRAME, VRCB_CONTINUOUS_SKIP_FRAME*20);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
    #endif

    /* Register Callback Function */
    eRetErr = MMPS_3GPRECD_RegisterCallback(VIDMGR_EVENT_MEDIA_FULL,           (void*)VRMediaFullCB);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    eRetErr = MMPS_3GPRECD_RegisterCallback(VIDMGR_EVENT_PRM_RECD_FILE_FULL,   (void*)VRPrmFileFullCB);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    eRetErr = MMPS_3GPRECD_RegisterCallback(VIDMGR_EVENT_LONG_TIME_FILE_FULL,  (void*)VRLongTimeFileFullCB);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    eRetErr = MMPS_3GPRECD_RegisterCallback(VIDMGR_EVENT_MEDIA_ERROR,          (void*)VRMediaErrorCB);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    eRetErr = MMPS_3GPRECD_RegisterCallback(VIDMGR_EVENT_MEDIA_SLOW,           (void*)VRMediaSlowCB);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    #if (VR_SLOW_CARD_DETECT)
    eRetErr = MMPS_3GPRECD_RegisterCallback(VIDMGR_EVENT_PREGETTIME_CARDSLOW,  (void*)VRPreGetTimeWhenCardSlowCB);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    eRetErr = MMPS_3GPRECD_RegisterCallback(VIDMGR_EVENT_RECDSTOP_CARDSLOW,    (void*)VRRecdStopWhenCardSlowCB);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
    #else
    eRetErr = MMPS_3GPRECD_RegisterCallback (VIDMGR_EVENT_RECDSTOP_CARDSLOW,   (void*)VRCardSlowStopEncCB);
    if(eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,  eRetErr); return AHC_FALSE;}
    #endif

    eRetErr = MMPS_3GPRECD_RegisterCallback(VIDMGR_EVENT_SEAMLESS ,            (void*)VRSeamlessCB);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    eRetErr = MMPS_3GPRECD_RegisterCallback(VIDMGR_EVENT_ENCODE_START,         (void*)VRStartEncCB);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    eRetErr = MMPS_3GPRECD_RegisterCallback(VIDMGR_EVENT_ENCODE_STOP,          (void*)VRStopEncCB);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    eRetErr = MMPS_3GPRECD_RegisterCallback(VIDMGR_EVENT_MUX_POSTPROCESS,      (void*)VRMuxPostProcCB);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    eRetErr = MMPS_3GPRECD_RegisterCallback(VIDMGR_EVENT_EMERGFILE_FULL,       (void*)VREmerDoneCB);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    if ((AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_SCD, AHC_FALSE) & VID_RECD_ENCODE_H264) ||
        (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_FALSE) & VID_RECD_ENCODE_H264)) {

        eRetErr = MMPS_3GPRECD_RegisterCallback(VIDMGR_EVENT_SCD_RECD_FILE_FULL, (void *)VRScdFileFullCB);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
    }

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeMiscPreprocess
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeMiscPreprocess(void)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    if (AHC_VIDEO_GetFirstTimeRecord() == AHC_TRUE) {
        // Disable Fast AE/AWB when recording
        AHC_SetFastAeAwbMode(AHC_FALSE);
    }

    #if (AHC_ENABLE_VIDEO_STICKER)
    UpdateVideoCurrentTimeStamp(AHC_TRUE);
    #endif

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeMiscPostprocess
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeMiscPostprocess(void)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    // Refresh timestamp immediately after record start.
    #if (AHC_ENABLE_VIDEO_STICKER)
    UpdateVideoCurrentTimeStamp(AHC_TRUE);
    #endif

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModePreAddFilename
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModePreAddFilename(void)
{
    AHC_BOOL                ahcRet = AHC_TRUE;
    AHC_VIDEO_FILENAME_MGR  *pstPrmRecdFileNameMgr, *pstScdRecdFileNameMgr, *pstUsbRecdFileNameMgr;

    pstPrmRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_PRMREC);
    pstScdRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_SCDREC);
    pstUsbRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_USBREC);

    {
    #if (AHC_SHAREENC_SUPPORT)
        DCF_DB_TYPE eDBType = AHC_UF_GetDB();

        if ((uiGetParkingModeEnable()) && (!AHC_VIDEO_IsShareRecdStarted())) {
            AHC_DBG_MSG(1, FG_RED("[%s, %d] Change to DB%d\r\n"), __FUNCTION__, __LINE__, eDBType);
            AHC_UF_SelectDB(DCF_DB_TYPE_DB1_PARKING);
        }
        else  {
            if (eDBType != DCF_DB_TYPE_DB0_NORMAL) {
                AHC_DBG_MSG(1, FG_RED("[%s, %d] Change to DB%d\r\n"), __FUNCTION__, __LINE__, eDBType);
                AHC_UF_SelectDB(DCF_DB_TYPE_DB0_NORMAL);
            }
        }

        if (pstPrmRecdFileNameMgr->u8DeviceStatus) {
            AHC_UF_SetRearCamPathFlag(AHC_FALSE);
            ahcRet = AHC_UF_PreAddFile(m_u16CurVideoDirKey, (INT8*)pstPrmRecdFileNameMgr->u8FileName);
        }

        AHC_UF_SelectDB(eDBType);

        if (ahcRet == AHC_FALSE) {
            AHC_DBG_ERR(1, "[%s, %d] UF_PreAddFile Fail DB[%d]\r\n", __FUNCTION__, __LINE__, eDBType);
        }
    #else
        if (pstPrmRecdFileNameMgr->u8DeviceStatus) {
            AHC_UF_SetRearCamPathFlag(AHC_FALSE);
            ahcRet = AHC_UF_PreAddFile(m_u16CurVideoDirKey, (INT8*)pstPrmRecdFileNameMgr->u8FileName);
        }

        #if (AHC_MULTI_TRACK_EN == 0)
        if (pstScdRecdFileNameMgr->u8DeviceStatus) {
            AHC_UF_SetRearCamPathFlag(AHC_TRUE);
            ahcRet = AHC_UF_PreAddFile(m_u16CurVideoDirKey, (INT8*)pstScdRecdFileNameMgr->u8FileName);
            AHC_UF_SetRearCamPathFlag(AHC_FALSE);
        }

        if (pstUsbRecdFileNameMgr->u8DeviceStatus) {
            AHC_UF_SetRearCamPathFlag(AHC_TRUE);
            ahcRet = AHC_UF_PreAddFile(m_u16CurVideoDirKey, (INT8*)pstUsbRecdFileNameMgr->u8FileName);
            AHC_UF_SetRearCamPathFlag(AHC_FALSE);
        }
        #endif
    #endif
    }

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModePreAddFilenameFails
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModePreAddFilenameFails(void)
{
    AHC_BOOL                ahcRet = AHC_TRUE;
    INT8                    s8DirName[64];
    AHC_VIDEO_FILENAME_MGR  *pstPrmRecdFileNameMgr;

    pstPrmRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_PRMREC);

    if (GetPathDirStr(s8DirName, sizeof(s8DirName), pstPrmRecdFileNameMgr->u8FullName))
    {
        if (!AHC_UF_FileOperation((UINT8*)s8DirName, (UINT8*)pstPrmRecdFileNameMgr->u8FileName, DCF_FILE_DELETE_ALL_CAM, NULL, NULL)) {
            #if ((GSENSOR_RAW_FILE_ENABLE == 1) && (GPS_CONNECT_ENABLE == 0))
            AHC_FS_FileRemove(bGPSRawFileName, STRLEN(bGPSRawFileName));
            #endif
        }
    }

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeSetSeamless
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeSetSeamless(void)
{
    UINT64      u64StorageFreeSpace = 0;
    UINT32      u32TimeLimit = 0;
    AHC_BOOL    ahcRet = AHC_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    u32TimeLimit = AHC_VIDEO_GetRecTimeLimitEx();

    if (AHC_VIDEO_SetRecTimeLimit(u32TimeLimit) == 0) {

        /* Set File Size, Time Limit */
        eRetErr = MMPS_3GPRECD_SetFileSizeLimit(SIGNLE_FILE_SIZE_LIMIT_3_75G);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

        if (u32TimeLimit == NON_CYCLING_TIME_LIMIT/*Non cycle record*/) {

            AHC_Media_GetFreeSpace(&u64StorageFreeSpace);

            if (u64StorageFreeSpace < SIGNLE_FILE_SIZE_LIMIT_4G) {
                AHC_DBG_ERR(1, FG_RED("Free Space Not Enough to Enable Seamless-2\r\n"));
                AHC_VIDEO_SetVRSeamless(AHC_FALSE);
                return ahcRet;
            }
        }
    }

    AHC_VIDEO_SetVRSeamless(AHC_TRUE);

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeSetEmergency
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeSetEmergency(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    #if ((UVC_HOST_VIDEO_ENABLE) && (UVC_EMERGRECD_SUPPORT) && (AHC_UVC_EMERGRECD_SUPPORT))
    USB_DETECT_PHASE eUSBCurStates = 0;

    if (MMP_IsUSBCamExist() &&
        AHC_FALSE == MMP_IsUSBCamIsoMode()) {

        AHC_USBGetStates(&eUSBCurStates, AHC_USB_GET_PHASE_CURRENT);

        if ((eUSBCurStates == USB_DETECT_PHASE_REAR_CAM) &&
            (AHC_TRUE == AHC_HostUVC_IsDevEnabled())) {
            if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_DUAL_FILE ||
                MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE) {
                eRetErr = MMPS_3GPRECD_EnableUVCEmergentRecd(MMP_TRUE);
            }
            else {
                eRetErr = MMPS_3GPRECD_EnableUVCEmergentRecd(MMP_FALSE);
            }
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
        }
        else {
            eRetErr = MMPS_3GPRECD_EnableUVCEmergentRecd(MMP_FALSE);
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
        }
    }
    #endif

    #if (DUAL_EMERGRECD_SUPPORT) && (AHC_DUAL_EMERGRECD_SUPPORT)
    if (MMP_IsScdCamExist()) {
        if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_SCD, AHC_TRUE) & VID_RECD_ENCODE_H264) {
            if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_DUAL_FILE ||
                MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE) {
                eRetErr = MMPS_3GPRECD_EnableDualEmergentRecd(MMP_TRUE);
            }
            else {
                eRetErr = MMPS_3GPRECD_EnableDualEmergentRecd(MMP_FALSE);
            }
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
        }
        else {
            eRetErr = MMPS_3GPRECD_EnableDualEmergentRecd(MMP_FALSE);
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
        }
    }

    if (MMP_IsUSBCamExist() &&
        AHC_TRUE == MMP_IsUSBCamIsoMode()) {
        if (AHC_TRUE == AHC_HostUVC_IsDevEnabled()) {
            if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_DUAL_FILE ||
                MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE) {
                eRetErr = MMPS_3GPRECD_EnableDualEmergentRecd(MMP_TRUE);
            }
            else {
                eRetErr = MMPS_3GPRECD_EnableDualEmergentRecd(MMP_FALSE);
            }
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
        }
        else {
            eRetErr = MMPS_3GPRECD_EnableDualEmergentRecd(MMP_FALSE);
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
        }
    }
    #endif

    #if (AHC_EMERGENTRECD_SUPPORT)
    if (MMP_IsPrmCamExist()) {
        if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_DUAL_FILE ||
            MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_SWITCH_FILE) {
            eRetErr = MMPS_3GPRECD_EnableEmergentRecd(MMP_TRUE);
        }
        else {
            eRetErr = MMPS_3GPRECD_EnableEmergentRecd(MMP_FALSE);
        }
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
    }
    #endif

    #if (EMER_RECORD_DUAL_WRITE_PRETIME > 0)
    eRetErr = MMPS_3GPRECD_SetEmergPreEncTimeLimit(EMER_RECORD_DUAL_WRITE_PRETIME * 1000 + EM_VR_TIME_LIMIT_OFFSET);
    #endif
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    AHC_VIDEO_SetEmergRecInterval(EMER_RECORD_DUAL_WRITE_INTERVAL);

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeInitCommon
//  Description : Preview Start Flow
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeInitCommon(void)
{
    MMP_USHORT              usVideoPreviewMode = 0;
    AHC_DISPLAY_OUTPUTPANEL eOutputDev = AHC_DISPLAY_NONE;
    UINT32                  ulFlickerMode = COMMON_FLICKER_50HZ;
    UINT8                   ubEv = COMMON_EVVALUE_00;
    AHC_BOOL                ubSnrFlipEn = AHC_FALSE;
    AHC_BOOL                ahcRet = AHC_TRUE;
    MMP_UBYTE               ubHdrType;
    MMP_UBYTE               ubScdHdrType;
    MMP_ERR                 eRetErr = MMP_ERR_NONE;

    if ((ahcRet = AHC_VIDEO_SetRecordModeInitParameters()) == AHC_FALSE) {
        return ahcRet;
    }

    /* Stop Preview First */
    #if (UVC_HOST_VIDEO_ENABLE)
    if (MMP_IsUSBCamExist()) {
        ahcRet = AHC_HostUVC_PreviewStop(AHC_HUVC_UI_MODE_VR);
        ahcRet = AHC_HostUVC_ResetFBMemory();
    }
    #endif

    if (MMP_IsScdCamExist()) {
        if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
            MMPS_Sensor_EnableAnaDecSrcTypeDetect(MMP_FALSE);
            eRetErr |= MMPS_3GPRECD_ScdCamPreviewStop(gsAhcScdSensor);
        }
        else if (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {
            eRetErr |= MMPS_3GPRECD_ScdCamPreviewStop(gsAhcScdSensor);
        }
        else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
            eRetErr |= MMPS_3GPRECD_ScdCamPreviewStop(gsAhcScdSensor);
        }
    }

    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    /* Initial ISP and Channel Setting */
    eRetErr = MMPF_ISP_GlobalInit();
    ubHdrType = (MMP_UBYTE)MMP_GetVidHDRType(CAM_TYPE_PRM);
    ubScdHdrType = (MMP_UBYTE)MMP_GetVidHDRType(CAM_TYPE_SCD);

    if (MMP_IsPrmCamExist()) { // Only primary sensor can support HDR function.
        if (CAM_CHECK_PRM(PRM_CAM_BAYER_SENSOR)) {
            eRetErr = MMPF_ISP_AllocatePrmSensorChannel(ubHdrType);
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
        }
        else if ((CAM_CHECK_PRM(PRM_CAM_ANA_DECODER)) ||
                 (CAM_CHECK_PRM(PRM_CAM_YUV_SENSOR))) {
            eRetErr = MMPF_ISP_AllocatePrmRAWStoreSensorChannel();
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
        }
    }

    if (MMP_IsScdCamExist()) {
        if ((CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) ||
            (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) ||
            (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))) {
            eRetErr = MMPF_ISP_AllocateScdRAWStoreSensorChannel(ubScdHdrType);
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
        }
    }

    /* Check if Prm cam and SCD cam I2C Addr are equal or not? */
    if (MMP_IsPrmCamExist() && MMP_IsScdCamExist()) {
        MMP_UBYTE ubPrmI2CAddr, ubScdI2CAddr;
        eRetErr = MMPF_Sensor_GetSensorI2CAddr(gsAhcPrmSensor, &ubPrmI2CAddr);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
        eRetErr = MMPF_Sensor_GetSensorI2CAddr(gsAhcScdSensor, &ubScdI2CAddr);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
        if (ubPrmI2CAddr == ubScdI2CAddr) {
            AHC_DBG_ERR(1, FG_RED("[Warning!]Prm Sensor I2C Addr = Scd Sensor I2C Addr 0x%x\r\n"), ubPrmI2CAddr);
        }
    }

    AHC_VIDEO_SetRecWithWNR(AHC_FALSE);

    /* Disable sticker for sometimes abnormal issue */
    eRetErr = MMPS_3GPRECD_EnableSticker(MMP_STICKER_ID_0, MMP_FALSE);
    eRetErr = MMPS_3GPRECD_EnableSticker(MMP_STICKER_ID_1, MMP_FALSE);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    /* Set Display Device */
    AHC_GetDisplayOutputDev(&eOutputDev);
    eRetErr = MMPS_Display_SetOutputPanel(MMP_DISPLAY_PRM_CTL, eOutputDev);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    switch(eOutputDev){
    case MMP_DISPLAY_SEL_MAIN_LCD:
    case MMP_DISPLAY_SEL_SUB_LCD:
        usVideoPreviewMode = VIDRECD_NORMAL_PREVIEW_MODE;
        break;
    case MMP_DISPLAY_SEL_NTSC_TV:
        usVideoPreviewMode = VIDRECD_NTSC_PREVIEW_MODE;
        break;
    case MMP_DISPLAY_SEL_PAL_TV:
        usVideoPreviewMode = VIDRECD_PAL_PREVIEW_MODE;
        break;
    case MMP_DISPLAY_SEL_HDMI:
        usVideoPreviewMode = VIDRECD_HDMI_PREVIEW_MODE;
        break;
    case MMP_DISPLAY_SEL_CCIR:
        usVideoPreviewMode = VIDRECD_CCIR_PREVIEW_MODE;
        break;
    case MMP_DISPLAY_SEL_NONE:
    default:
        usVideoPreviewMode = VIDRECD_NORMAL_PREVIEW_MODE;
        AHC_DBG_ERR(1, "%s, %d  not support yet!", __FUNCTION__, __LINE__);
        break;
    }

    /* Set Preview Zoom Configuration */
    #if 0 // TBD
    {
        MMP_UBYTE   ubPipe = 0;
        MMP_USHORT  usZoomIdx = 0;

        if (gsStillZoomIndex == 0xFFFF) {
            MMPS_3GPRECD_GetCurZoomStep(ubPipe, &usZoomIdx);
        }
        else {
            usZoomIdx = gsStillZoomIndex;
            gsStillZoomIndex = 0xFFFF;
        }

        #if (VIDEO_CAMERA_DZOOM_SYNC)
        eRetErr = MMPS_3GPRECD_SetPreviewZoom(MMPS_3GPRECD_ZOOM_PATH_PREV, MMP_PTZ_ZOOMIN, usZoomIdx);
        #else
        eRetErr = MMPS_3GPRECD_SetPreviewZoom(MMPS_3GPRECD_ZOOM_PATH_PREV, MMP_PTZ_ZOOMOUT, 0);
        #endif
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
    }
    #endif

    /* Open Prm Script and Port */
    eRetErr = MMPS_3GPRECD_EnablePrmCamPreview(usVideoPreviewMode);
    if (eRetErr != MMP_ERR_NONE){
        AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr);
        return AHC_FALSE;
    }

    /* Initialize Sensor */
    if (MMP_IsScdCamExist()) {
        MMP_ULONG ulIqCfgIdx = 0;

        eRetErr = MMPS_Sensor_Initialize(gsAhcScdSensor, 0, MMP_SNR_VID_PRW_MODE, 0/*Second sensor does not support HDR*/, ulIqCfgIdx);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

        if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
            eRetErr = MMPS_Sensor_RegisterCallback(MMP_SNR_EVENT_ANADEC_SRC_TYPE, (void*)VRAnaDecSnrSrcTypeHandler);
            eRetErr |= MMPS_Sensor_EnableAnaDecSrcTypeDetectTimer(gsAhcScdSensor, NULL, SNR_R_CHECK_SIG_TYPE_PERIODIC, MMP_TRUE);
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
        }
    }

    if (MMP_IsPrmCamExist()) {
        MMP_ULONG ulIqCfgIdx = 0;

        #if defined(PCAM_UVC_MIX_MODE_ENABLE) && (PCAM_UVC_MIX_MODE_ENABLE == 1) // Temporary set mix mode here, need review.
        pcam_usb_set_mix_mode(MMP_TRUE);
        #endif
        eRetErr = MMPS_Sensor_SetPreviewMode(gsAhcPrmSensor, AHC_SNR_GetPresetPrmSnrMode());
        ulIqCfgIdx = (ubHdrType == 0) ? 0 : 1; // For iqcfg file
        eRetErr = MMPS_Sensor_Initialize(gsAhcPrmSensor, AHC_SNR_GetPresetPrmSnrMode(), MMP_SNR_VID_PRW_MODE, ubHdrType, ulIqCfgIdx);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE; }
    }

    // For parking mode pre-encode, wait for sensor stabilization
    if (uiGetParkingModeEnable()) {
        AHC_DBG_MSG(1, "## Parking Wait Snr Init\r\n");
        AHC_OS_SleepMs(150);
    }

    /* Set Sensor Flip Direction */
    ubSnrFlipEn = AHC_CheckSNRFlipEn(CTRL_BY_ALL) && AHC_SNR_GetSnrDirStatus();
    ahcRet = AHC_SetKitDirection(AHC_LCD_NOFLIP, AHC_FALSE, AHC_SNR_GetSnrDirStatus(), ubSnrFlipEn);

    /* Set Flicker Mode */
    if (AHC_Menu_SettingGetCB((char *)COMMON_KEY_FLICKER, &ulFlickerMode) == AHC_TRUE) {
        if (COMMON_FLICKER_60HZ == ulFlickerMode) {
            ahcRet = AHC_SNR_SetLightFreq(gsAhcPrmSensor, AHC_SENSOR_VIDEO_DEBAND_60HZ);
            if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                ahcRet = AHC_SNR_SetLightFreq(gsAhcScdSensor, AHC_SENSOR_VIDEO_DEBAND_60HZ);
        }
        else {
            ahcRet = AHC_SNR_SetLightFreq(gsAhcPrmSensor, AHC_SENSOR_VIDEO_DEBAND_50HZ);
            if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
                ahcRet = AHC_SNR_SetLightFreq(gsAhcScdSensor, AHC_SENSOR_VIDEO_DEBAND_50HZ);
        }
    }
    else {
        ahcRet = AHC_SNR_SetLightFreq(gsAhcPrmSensor, AHC_SENSOR_VIDEO_DEBAND_60HZ);
        if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
            ahcRet = AHC_SNR_SetLightFreq(gsAhcScdSensor, AHC_SENSOR_VIDEO_DEBAND_60HZ);
    }

    /* Set EV value */
    if (AHC_Menu_SettingGetCB((char *)COMMON_KEY_EV, &ubEv) == AHC_TRUE) {
        ahcRet = AHC_SetAeEvBiasMode(gsAhcPrmSensor, Menu_EV_To_AE_EV_BIAS(ubEv));
        if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR))
            ahcRet = AHC_SetAeEvBiasMode(gsAhcScdSensor, Menu_EV_To_AE_EV_BIAS(ubEv));
    }

    /* Check Prm Analog Decoder / YUV sensor source type */
    if (MMP_IsPrmCamExist()) {
        if (CAM_CHECK_PRM(PRM_CAM_ANA_DECODER)) {
            AHC_SNR_CheckAnaDecSrcType(MMPS_PREVIEW_UI_MODE_VR, gsAhcPrmSensor);
        }
        else if (CAM_CHECK_PRM(PRM_CAM_YUV_SENSOR)) {
            AHC_SNR_CheckYUVSnrSrcType(MMPS_PREVIEW_UI_MODE_VR, gsAhcPrmSensor);
        }
    }

    if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
        MMPF_Sensor_SetDualBayerSensor(MMP_TRUE);
    }
    else {
        MMPF_Sensor_SetDualBayerSensor(MMP_FALSE);
    }

    /* Start Prm Preview Flow (Open VIF) */
    if (MMP_IsPrmCamExist()) {
        eRetErr = MMPS_3GPRECD_PrmCamPreviewStart(gsAhcPrmSensor, MMP_FALSE);
        if (eRetErr != MMP_ERR_NONE) {
            AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr);
            return AHC_FALSE;
        }
    }

    /* Check Scd Preview / Record Pipe Attribute */
    if (MMP_IsScdCamExist()) {
        if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
            AHC_SNR_CheckAnaDecSrcType(MMPS_PREVIEW_UI_MODE_VR, gsAhcScdSensor);

            if (AHC_TRUE == AHC_SNR_GetAnaDecSnrCnntStatus()) {
                AHC_VIDEO_SetScdRecdSetting();

                eRetErr = MMPS_3GPRECD_AdjustScdRecdPipe(gsAhcScdSensor);
                eRetErr = MMPS_3GPRECD_AdjustScdPrevwPipe(gsAhcScdSensor);
            }
        }
        else if (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {
            AHC_SNR_CheckYUVSnrSrcType(MMPS_PREVIEW_UI_MODE_VR, gsAhcScdSensor);

            if (AHC_TRUE == AHC_SNR_GetYuvSnrCnntStatus()) {
                AHC_VIDEO_SetScdRecdSetting();

                eRetErr = MMPS_3GPRECD_AdjustScdRecdPipe(gsAhcScdSensor);
                eRetErr = MMPS_3GPRECD_AdjustScdPrevwPipe(gsAhcScdSensor);
            }
        }
        else if(CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)){
            AHC_VIDEO_SetScdRecdSetting();

            eRetErr = MMPS_3GPRECD_AdjustScdRecdPipe(gsAhcScdSensor);
            eRetErr = MMPS_3GPRECD_AdjustScdPrevwPipe(gsAhcScdSensor);
        }
    }

    /* Open Scd Script and Port */
    if (MMP_IsScdCamExist()) {
        if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)){
            if (AHC_FALSE == AHC_SNR_GetAnaDecSnrCnntStatus())
                MMPS_Display_EnableScdAnaDecSnrPreview(MMPS_PREVIEW_UI_MODE_VR, MMP_FALSE);
            else
                MMPS_Display_EnableScdAnaDecSnrPreview(MMPS_PREVIEW_UI_MODE_VR, MMP_TRUE);
        }
        else if (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {
            if (AHC_FALSE == AHC_SNR_GetYuvSnrCnntStatus())
                MMPS_Display_EnableScdAnaDecSnrPreview(MMPS_PREVIEW_UI_MODE_VR, MMP_FALSE);
            else
                MMPS_Display_EnableScdAnaDecSnrPreview(MMPS_PREVIEW_UI_MODE_VR, MMP_TRUE);
        }
        else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
            MMPS_Display_EnableScdBayerSnrPreview(MMPS_PREVIEW_UI_MODE_VR, MMP_TRUE);
        }
    }

    /* Start Scd Preview Flow (Open VIF) */
    if (MMP_IsScdCamExist()) {
        if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
            if (AHC_TRUE == AHC_SNR_GetAnaDecSnrCnntStatus()) {

                eRetErr = MMPS_3GPRECD_ScdCamPreviewStart(gsAhcScdSensor, MMP_FALSE);
                if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

                #if defined(WIFI_PORT) && (WIFI_PORT == 1)
                // Add this for WIFI APP need this for switch sensor
                ncam_set_rear_cam_ready(AHC_TRUE);
                #endif
            }
        }
        else if (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {
            if (AHC_TRUE == AHC_SNR_GetYuvSnrCnntStatus()) {

                eRetErr = MMPS_3GPRECD_ScdCamPreviewStart(gsAhcScdSensor, MMP_FALSE);
                if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

                #if defined(WIFI_PORT) && (WIFI_PORT == 1)
                // Add this for WIFI APP need this for switch sensor
                ncam_set_rear_cam_ready(AHC_TRUE);
                #endif
            }
        }
        else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {

            eRetErr = MMPS_3GPRECD_ScdCamPreviewStart(gsAhcScdSensor, MMP_FALSE);
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }

            #if defined(WIFI_PORT) && (WIFI_PORT == 1)
            // Add this for WIFI APP need this for switch sensor
            ncam_set_rear_cam_ready(AHC_TRUE);
            #endif
        }
    }

    /* Start USBH Cam Preview Flow */
    #if (UVC_HOST_VIDEO_ENABLE)
    if (MMP_IsUSBCamExist()) {
        AHC_HostUVC_PreviewStart(AHC_HUVC_UI_MODE_VR, ulFlickerMode);
    }
    #endif

    AHC_SetFastAeAwbMode(AHC_TRUE);

    AHC_Display_AdjustColorMatrix();

    #if (AHC_ENABLE_VIDEO_STICKER)
    UpdateVideoCurrentTimeStamp(AHC_TRUE);
    #endif

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeUnInitCommon
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeUnInitCommon(void)
{
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    AHC_BOOL    ahcRet = AHC_TRUE;

    if (MMP_GetANACamType() != ANA_CAM_2I1O && MMP_GetANACamType() != ANA_CAM_2I2O){
        eRetErr = MMPF_ISP_GlobalUnInit();
    }

    // Close script
    if (MMP_IsScdCamExist()) {
        if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
            eRetErr = MMPS_Display_EnableScdBayerSnrPreview(MMPS_PREVIEW_UI_MODE_VR, MMP_FALSE);
        }
        else {
            eRetErr = MMPS_Display_EnableScdAnaDecSnrPreview(MMPS_PREVIEW_UI_MODE_VR, MMP_FALSE);
        }
    }

    //TEST:GlobalUnInit after cameraPreviewSetChannel((u32)RAWS_COMP_IDX2,MMP_TRUE);
    if (MMP_GetANACamType() == ANA_CAM_2I1O || MMP_GetANACamType() == ANA_CAM_2I2O){
        eRetErr = MMPF_ISP_GlobalUnInit();
    }

    if (MMP_IsPrmCamExist()) {
        eRetErr = MMPS_3GPRECD_EnablePrmCamPreview((MMP_USHORT)(-1));
    }

    /* Disable SCD Sticker After SCD Cam Preview Stop */
    if (MMP_TRUE == MMPS_3GPRECD_IsStickerEnable(MMP_STICKER_ID_1)) {
        MMPS_3GPRECD_EnableSticker(MMP_STICKER_ID_1, MMP_FALSE);
    }

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeInit
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeInit(void)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    ahcRet = AHC_VIDEO_SetRecordModeInitCommon();

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeUnInit
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeUnInit(void)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    ahcRet = AHC_VIDEO_SetRecordModeUnInitCommon();

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeStartRecd
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeStartRecd(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    #if (AHC_ENABLE_VIDEO_STICKER)
    UpdateVideoCurrentTimeStamp(AHC_TRUE);
    #endif

    #if (AHC_MULTI_TRACK_EN)
    MMPS_3GPRECD_SetMgrMultiTrackEn(MMP_TRUE);
    #else
    MMPS_3GPRECD_SetMgrMultiTrackEn(MMP_FALSE);
    #endif

    #if (AHC_SHAREENC_SUPPORT)
    MMPS_3GPRECD_SetShareRecordEn(MMP_TRUE);
    #endif

    // Patch for AIT rear cam slow card issue. Open file for UVC here.
    // Seamless is ok because of TX start by m_container.
    #if (UVC_HOST_VIDEO_ENABLE) && (UVC_VIDRECD_SUPPORT)
    if ((AHC_VIDEO_GetFirstTimeRecord() == AHC_TRUE) &&
        (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_FALSE) == VID_RECD_STORE_FILE)) {

        USB_DETECT_PHASE eUSBCurStates = 0;

        AHC_USBGetStates(&eUSBCurStates, AHC_USB_GET_PHASE_CURRENT);

        if ((eUSBCurStates == USB_DETECT_PHASE_REAR_CAM) &&
            (AHC_TRUE == AHC_HostUVC_IsDevEnabled())) {
            eRetErr = MMPS_HUVC_OpenRecdFile();
        }
    }
    #endif

    /* Start Prm/Scd/UVC Record */
    if (MMP_IsPrmCamExist()) {
        eRetErr = MMPS_3GPRECD_StartPrmRecord();
        if (eRetErr != MMP_ERR_NONE) {
            AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr);
            AHC_VIDEO_GetRecordModeThrow(AHC_VIDRECD_MODE_API_START_RECORD);
            return AHC_FALSE;
        }
    }

    #if (AHC_SHAREENC_SUPPORT)
    if (AHC_VIDEO_GetFirstTimeRecord() == AHC_TRUE) {
        m_ulAhcSharePreEncTime = DUAL_RECORD_WRITE_PRETIME*1000 + EM_VR_TIME_LIMIT_OFFSET;

        AHC_VIDEO_StartSharePreRecord();
    }
    #endif

    if (MMP_IsScdCamExist()) {

        if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_SCD, AHC_TRUE) & VID_RECD_ENCODE_H264) {
            if (!AHC_VIDEO_ScdRecordStart()) {
                AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0);
                AHC_VIDEO_GetRecordModeThrow(AHC_VIDRECD_MODE_API_START_RECORD);
                return AHC_FALSE;
            }
        }
    }

    if (MMP_IsUSBCamExist()) {

        USB_DETECT_PHASE eUSBCurStates = 0;

        AHC_USBGetStates(&eUSBCurStates, AHC_USB_GET_PHASE_CURRENT);

        if ((AHC_VIDEO_GetFirstTimeRecord() == AHC_TRUE) &&
            (eUSBCurStates == USB_DETECT_PHASE_REAR_CAM) &&
            (AHC_TRUE == AHC_HostUVC_IsDevEnabled())) {

            if (!AHC_HostUVC_RecordStart()) {
                AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0);
                AHC_VIDEO_GetRecordModeThrow(AHC_VIDRECD_MODE_API_START_RECORD);
                return AHC_FALSE;
            }
        }
    }

    if (MMPS_3GPRECD_IsShareRecordEn() == MMP_FALSE) {
        // No matter rear cam is connected or not, MMPS_3GPRECD_StartAllRecord must be called in DUALENC_SUPPORT case.
        if ((AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_SCD, AHC_FALSE) & VID_RECD_ENCODE_H264) ||
            (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_FALSE) & VID_RECD_ENCODE_H264)) {

            eRetErr = MMPS_3GPRECD_StartAllRecord();
            if (eRetErr != MMP_ERR_NONE) {
                AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr);
                AHC_VIDEO_GetRecordModeThrow(AHC_VIDRECD_MODE_API_START_RECORD);
                return AHC_FALSE;
            }
        }
    }

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordWaitDCFDone
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AHC_VIDEO_SetRecordWaitDCFDone(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;
    UINT32      ulDCFInitTimeout = 0;
    AHC_BOOL    bDCFInited = AHC_FALSE;

    /* Initialize DCF DB */
    ulDCFInitTimeout = 600; // Timeout value is 6 sec.

    do {
        bDCFInited = AHC_UF_IsDBMounted();
        if (AHC_FALSE == bDCFInited) {
            AHC_OS_SleepMs(10);
        }
    } while ((AHC_FALSE == bDCFInited) && (--ulDCFInitTimeout > 0));

    if (0 == ulDCFInitTimeout) {
        AHC_DBG_ERR(1, FG_RED("Wait DCF init timeout!\r\n"));
    }

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordEnterPreEncode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordEnterPreEncode(void)
{
    UINT32      u32Param = 0;
    MMP_ULONG   ulDesirePreEncTime = 0;
    MMP_ULONG   ulRealPreEncTime = 0;
    MMP_ULONG   ulRealPreEncTimePrm = 0;
    MMP_ULONG   ulRealPreEncTimeScd = 0;
    MMP_ULONG   ulRealPreEncTimeUsb = 0;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    AHC_BOOL    ahcRet = AHC_TRUE;

    /* Enter PreEncode Flow */
    AHC_VIDEO_GetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_VIDEO_PRERECORD_LENGTH, &u32Param);

    if ((uiGetParkingCfg()->bParkingModeFuncEn == AHC_TRUE) &&
        (uiGetParkingModeEnable() == AHC_TRUE))
        ulDesirePreEncTime = uiGetParkingCfg()->ulPreRecordLengthInMs;
    else
        ulDesirePreEncTime = u32Param;

    if (MMP_IsScdCamExist()) {
        if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_SCD, AHC_TRUE) & VID_RECD_ENCODE_H264) {
            AHC_VIDEO_SetScdRecdSetting();
        }
    }

    if (MMP_IsUSBCamExist()) {
        if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_FALSE) & VID_RECD_ENCODE_H264) {

            USB_DETECT_PHASE eUSBCurStates = 0;

            AHC_USBGetStates(&eUSBCurStates, AHC_USB_GET_PHASE_CURRENT);

            if ((eUSBCurStates == USB_DETECT_PHASE_REAR_CAM) &&
                (AHC_TRUE == AHC_HostUVC_IsDevEnabled())) {

                AHC_HostUVC_SetScdRecdSetting();
            }
        }
    }

    MMPS_3GPRECD_GetAllEncPreRecordTime(ulDesirePreEncTime, &ulRealPreEncTime);
    AHC_DBG_MSG(1, "Max Video Pre-Enc [%d] ms\r\n", ulRealPreEncTime);

    if (MMP_IsPrmCamExist()) {
        ulRealPreEncTimePrm = ulRealPreEncTime;

        eRetErr = MMPS_3GPRECD_StartPrmPreEnc(&ulRealPreEncTimePrm);
        if (eRetErr != MMP_ERR_NONE) {
            AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr);
            AHC_VIDEO_GetRecordModeThrow(AHC_VIDRECD_MODE_API_START_PRE_ENCODE);
            return AHC_FALSE;
        }
    }

    if (MMP_IsScdCamExist()) {
        if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_SCD, AHC_TRUE) & VID_RECD_ENCODE_H264) {
            ulRealPreEncTimeScd = ulRealPreEncTime;

            eRetErr = MMPS_3GPRECD_StartScdPreEnc(&ulRealPreEncTimeScd);
            if (eRetErr != MMP_ERR_NONE) {
                AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0);
                AHC_VIDEO_GetRecordModeThrow(AHC_VIDRECD_MODE_API_START_PRE_ENCODE);
                return AHC_FALSE;
            }
        }
    }

    if (MMP_IsUSBCamExist()) {

        if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_USB, AHC_FALSE) & VID_RECD_ENCODE_H264)
        {
            USB_DETECT_PHASE eUSBCurStates = 0;

            AHC_USBGetStates(&eUSBCurStates, AHC_USB_GET_PHASE_CURRENT);

            if ((eUSBCurStates == USB_DETECT_PHASE_REAR_CAM) &&
                (AHC_TRUE == AHC_HostUVC_IsDevEnabled())) {

                ulRealPreEncTimeUsb = ulRealPreEncTime;

                if (MMPS_3GPRECD_StartScdPreEnc(&ulRealPreEncTimeUsb)) {
                    AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0);
                    AHC_VIDEO_GetRecordModeThrow(AHC_VIDRECD_MODE_API_START_PRE_ENCODE);
                    return AHC_FALSE;
                }
            }
        }
    }

    AHC_VIDEO_RecordStartWriteInfo();

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordExceptionHandler
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordExceptionHandler(void)
{
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    AHC_BOOL    ahcRet = AHC_TRUE;
    UINT32      u32ExceptionCode = 0;

    u32ExceptionCode = AHC_VIDEO_GetRecordModeCatch();

    switch(u32ExceptionCode) {
    case AHC_VIDRECD_MODE_API_START_RECORD:
        eRetErr = MMPS_3GPRECD_StopAllRecord();
        ahcRet = AHC_VIDEO_SetRecordModePreAddFilenameFails();
        break;
    case AHC_VIDRECD_MODE_API_START_PRE_ENCODE:
        eRetErr = MMPS_3GPRECD_StopAllRecord();
        break;
    default:
        AHC_DBG_ERR(1, FG_RED("No corresponding exception handler! [%d]\r\n"), u32ExceptionCode);
        break;
    }

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeRegisterInit
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeRegisterInit(void *pfExternalAPI)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    if (NULL == pfExternalAPI) {
        AHC_PRINT_RET_ERROR(0, 0);
        ahcRet = AHC_FALSE;
        return ahcRet;
    }

    pfAhcVidSetRecModeInit = (pfAHC_VIDEO_SetRecordModeAPI)pfExternalAPI;

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeRegisterUnInit
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeRegisterUnInit(void *pfExternalAPI)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    if (NULL == pfExternalAPI) {
        AHC_PRINT_RET_ERROR(0, 0);
        ahcRet = AHC_FALSE;
        return ahcRet;
    }

    pfAhcVidSetRecModeUnInit = (pfAHC_VIDEO_SetRecordModeAPI)pfExternalAPI;

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeRegisterAction
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeRegisterAction( AHC_VIDRECD_FLOW_TYPE   ahcVidRecFlowType,
                                                AHC_VIDRECD_MODE_API    ahcVidRecModeAPI,
                                                void*                   pfExternalAPI)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    if (ahcVidRecFlowType >= AHC_VIDRECD_FLOW_TYPE_MAX) {
        AHC_PRINT_RET_ERROR(0, 0);
        ahcRet = AHC_FALSE;
        return ahcRet;
    }

    if (NULL == pfExternalAPI) {
        AHC_PRINT_RET_ERROR(0, 0);
        ahcRet = AHC_FALSE;
        return ahcRet;
    }

    gpfAhcVidSetRecModeActoinList[ahcVidRecFlowType].pfahcVidSetRecModeAPI[ahcVidRecModeAPI] = (pfAHC_VIDEO_SetRecordModeAPI)pfExternalAPI;

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeExecActionList
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeExecActionList(AHC_VIDRECD_FLOW_TYPE ahcVidRecFlowType)
{
    AHC_BOOL    ahcRet = AHC_TRUE;
    UINT32      ulLoop = 0;
    pfAHC_VIDEO_SetRecordModeAPI pfahcCurVidSetRecModeAPI = NULL;

    if (ahcVidRecFlowType >= AHC_VIDRECD_FLOW_TYPE_MAX) {
        AHC_PRINT_RET_ERROR(0, 0);
        ahcRet = AHC_FALSE;
        return ahcRet;
    }

    AHC_VIDEO_GetRecordModeClearException();

    for (ulLoop = 0; ulLoop < AHC_VIDRECD_MODE_API_EXCEPTION_HANDLER; ++ulLoop) {

        pfahcCurVidSetRecModeAPI = gpfAhcVidSetRecModeActoinList[ahcVidRecFlowType].pfahcVidSetRecModeAPI[ulLoop];

        if (NULL == pfahcCurVidSetRecModeAPI) {
            continue;
        }

        ahcRet = pfahcCurVidSetRecModeAPI();

        if (ahcRet != AHC_TRUE) {

            pfahcCurVidSetRecModeAPI = gpfAhcVidSetRecModeActoinList[ahcVidRecFlowType].pfahcVidSetRecModeAPI[AHC_VIDRECD_MODE_API_EXCEPTION_HANDLER];

            if (NULL != pfahcCurVidSetRecModeAPI){
                // Exception handler.
                ahcRet = pfahcCurVidSetRecModeAPI();
            }

            ahcRet = AHC_FALSE;
            return ahcRet;
        }
    }

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetCmdState
//  Description : Member function of gAhcVidRecdCmdStateXXXX
//------------------------------------------------------------------------------
AHC_VIDRECD_CMD AHC_VIDEO_GetCmdState(void* pthis)
{
    AHC_VIDEO_RECD_CMD_STATE *pAhcVidRecdCmdState = (AHC_VIDEO_RECD_CMD_STATE *)pthis;

    return pAhcVidRecdCmdState->ahcVidRecdCmdState;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_RecdCmdStateExecIdle
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_RecdCmdStateExecIdle(void* pthis, AHC_VIDRECD_CMD ahcNewVidRecdCmdState)
{
    AHC_VIDEO_RECD_CONTEXT  *pVidRecdContext = (AHC_VIDEO_RECD_CONTEXT *)pthis;
    AHC_BOOL                ahcRet = AHC_TRUE;
    static UINT8            bStateIdleDone = 0;

    if (NULL == pthis) {
        AHC_PRINT_RET_ERROR(0, 0);
        return AHC_FALSE;
    }

    switch(ahcNewVidRecdCmdState) {
    case AHC_VIDRECD_IDLE:
        if (1 == bStateIdleDone) {
            AHC_PRINT_RET_ERROR(0, 0);
            return AHC_TRUE;
        }
        // Stop preview
        ahcRet = AHC_VIDEO_StopRecordModeExStopPreview();
        ahcRet = AHC_VIDEO_StopRecordModeExStopSensor();

        ahcRet = pfAhcVidSetRecModeUnInit();
        bStateIdleDone = 1;
        return AHC_TRUE;
        break;
    case AHC_VIDRECD_INIT:
        pVidRecdContext->pfSetState(&gAhcVidRecdCmdStateInit);
        bStateIdleDone = 0;
        break;
    case AHC_VIDRECD_START:
    case AHC_VIDRECD_PRERECD:
    case AHC_VIDRECD_STOP: // TBD
    default:
        AHC_PRINT_RET_ERROR(0, 0);
        return AHC_FALSE;
        break;
    }

    // Transfer to next state.
    return pVidRecdContext->pfSetRecordMode(pthis, ahcNewVidRecdCmdState);
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_RecdCmdStateExecInit
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_RecdCmdStateExecInit(void* pthis, AHC_VIDRECD_CMD ahcNewVidRecdCmdState)
{
    AHC_VIDEO_RECD_CONTEXT  *pVidRecdContext = (AHC_VIDEO_RECD_CONTEXT *)pthis;
    AHC_BOOL                ahcRet = AHC_TRUE;

    static UINT8            bStateInitDone = 0;

    if (NULL == pthis) {
        AHC_PRINT_RET_ERROR(0, 0);
        return AHC_FALSE;
    }

    switch(ahcNewVidRecdCmdState) {
    case AHC_VIDRECD_IDLE:
        pVidRecdContext->pfSetState(&gAhcVidRecdCmdStateIdle);
        bStateInitDone = 0;
        break;
    case AHC_VIDRECD_INIT:
        if (1 == bStateInitDone) {
            AHC_PRINT_RET_ERROR(0, 0);
            return AHC_TRUE;
        }

        ahcRet = pfAhcVidSetRecModeInit();
        bStateInitDone = 1;
        return AHC_TRUE;
        break;
    case AHC_VIDRECD_START:
        pVidRecdContext->pfSetState(&gAhcVidRecdCmdStateStart);
        bStateInitDone = 0;
        break;
    case AHC_VIDRECD_PRERECD:
        pVidRecdContext->pfSetState(&gAhcVidRecdCmdStatePreRecd);
        bStateInitDone = 0;
        break;
    case AHC_VIDRECD_STOP: // TBD
    default:
        AHC_PRINT_RET_ERROR(0, 0);
        return AHC_TRUE;
        break;
    }

    // Transfer to next state.
    return pVidRecdContext->pfSetRecordMode(pthis, ahcNewVidRecdCmdState);
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_RecdCmdStateExecStart
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_RecdCmdStateExecStart(void* pthis, AHC_VIDRECD_CMD ahcNewVidRecdCmdState)
{
    AHC_VIDEO_RECD_CONTEXT  *pVidRecdContext = (AHC_VIDEO_RECD_CONTEXT *)pthis;
    AHC_BOOL                ahcRet = AHC_TRUE;
    VIDENC_FW_STATUS        eEncFwStatus;

    static UINT8            bStateStartDone = 0;

    if (NULL == pthis) {
        AHC_PRINT_RET_ERROR(0, 0);
        return AHC_FALSE;
    }

    switch(ahcNewVidRecdCmdState) {
    case AHC_VIDRECD_START:
        switch(bStateStartDone) {
        case 0: // First time record.
            ahcRet = AHC_VIDEO_SetRecordWaitDCFDone();

            AHC_VIDEO_SetFirstTimeRecord(AHC_TRUE);

            MMPS_3GPRECD_GetPrmEncoderStatus(&eEncFwStatus);

            if (VIDENC_FW_STATUS_PREENCODE == eEncFwStatus) {
                ahcRet = AHC_VIDEO_SetRecordModeExecActionList(AHC_VIDRECD_FLOW_TYPE_PRERECORD_TO_RECORD);
            }
            else {
                ahcRet = AHC_VIDEO_SetRecordModeExecActionList(AHC_VIDRECD_FLOW_TYPE_PREVIEW_TO_RECORD);
            }

            bStateStartDone = 1;
            return AHC_TRUE;
            break;
        case 1: // Seamless record.
            AHC_VIDEO_SetFirstTimeRecord(AHC_FALSE);
            ahcRet = AHC_VIDEO_SetRecordModeExecActionList(AHC_VIDRECD_FLOW_TYPE_SEAMLESS_START_NEXT_RECORD);
            bStateStartDone = 1;
            return AHC_TRUE;
            break;
        default:
            AHC_PRINT_RET_ERROR(0, 0);
            return AHC_FALSE;
            break;
        }
        return AHC_TRUE;
        break;
    case AHC_VIDRECD_STOP:
        pVidRecdContext->pfSetState(&gAhcVidRecdCmdStateStop);
        bStateStartDone = 0;
        break;
    case AHC_VIDRECD_IDLE:
    case AHC_VIDRECD_INIT:
    case AHC_VIDRECD_PRERECD:
    default:
        AHC_PRINT_RET_ERROR(0, 0);
        return AHC_FALSE;
        break;
    }

    // Transfer to next state.
    return pVidRecdContext->pfSetRecordMode(pthis, ahcNewVidRecdCmdState);
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_RecdCmdStateExecPreRecd
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_RecdCmdStateExecPreRecd(void* pthis, AHC_VIDRECD_CMD ahcNewVidRecdCmdState)
{
    AHC_VIDEO_RECD_CONTEXT  *pVidRecdContext = (AHC_VIDEO_RECD_CONTEXT *)pthis;
    AHC_BOOL                ahcRet = AHC_TRUE;

    static UINT8            bStatePreRecdDone = 0;

    if (NULL == pthis) {
        AHC_PRINT_RET_ERROR(0, 0);
        return AHC_FALSE;
    }

    switch(ahcNewVidRecdCmdState) {
    case AHC_VIDRECD_PRERECD:
        if (1 == bStatePreRecdDone) {
            AHC_PRINT_RET_ERROR(0, 0);
            return AHC_TRUE;
        }

        AHC_VIDEO_SetFirstTimeRecord(AHC_TRUE);
        ahcRet = AHC_VIDEO_SetRecordModeExecActionList(AHC_VIDRECD_FLOW_TYPE_PREVIEW_TO_PRERECORD);
        bStatePreRecdDone = 1;
        return AHC_TRUE;
        break;
    case AHC_VIDRECD_START:
        pVidRecdContext->pfSetState(&gAhcVidRecdCmdStateStart);
        bStatePreRecdDone = 0;
        break;
    case AHC_VIDRECD_STOP:
        pVidRecdContext->pfSetState(&gAhcVidRecdCmdStateStop);
        bStatePreRecdDone = 0;
        break;
    case AHC_VIDRECD_IDLE:
    case AHC_VIDRECD_INIT:
    default:
        AHC_PRINT_RET_ERROR(0, 0);
        return AHC_FALSE;
        break;
    }

    // Transfer to next state.
    return pVidRecdContext->pfSetRecordMode(pthis, ahcNewVidRecdCmdState);
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_RecdCmdStateExecStop
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_RecdCmdStateExecStop(void* pthis, AHC_VIDRECD_CMD ahcNewVidRecdCmdState)
{
    AHC_VIDEO_RECD_CONTEXT  *pVidRecdContext = (AHC_VIDEO_RECD_CONTEXT *)pthis;
    AHC_BOOL                ahcRet = AHC_TRUE;

    static UINT8            bStateStopDone = 0;

    if (NULL == pthis) {
        AHC_PRINT_RET_ERROR(0, 0);
        return AHC_FALSE;
    }

    switch(ahcNewVidRecdCmdState) {
    case AHC_VIDRECD_STOP:
        if (1 == bStateStopDone) {
            AHC_PRINT_RET_ERROR(0, 0);
            return AHC_TRUE;
        }

        ahcRet = AHC_VIDEO_StopRecordModeExStopRec();
        bStateStopDone = 1;
        return AHC_TRUE;
        break;
    case AHC_VIDRECD_IDLE:
        pVidRecdContext->pfSetState(&gAhcVidRecdCmdStateIdle);
        bStateStopDone = 0;
        break;
    case AHC_VIDRECD_START:
        pVidRecdContext->pfSetState(&gAhcVidRecdCmdStateStart);
        bStateStopDone = 0;
        break;
    case AHC_VIDRECD_PRERECD:
        pVidRecdContext->pfSetState(&gAhcVidRecdCmdStatePreRecd);
        bStateStopDone = 0;
        break;
    case AHC_VIDRECD_INIT:
    default:
        AHC_PRINT_RET_ERROR(0, 0);
        return AHC_FALSE;
        break;
    }

    // Transfer to next state.
    return pVidRecdContext->pfSetRecordMode(pthis, ahcNewVidRecdCmdState);
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_RecdContextSetState
//  Description : Member function of gAhcVidRecdContext
//------------------------------------------------------------------------------
void AHC_VIDEO_RecdContextSetState(AHC_VIDEO_RECD_CMD_STATE *pNextState)
{
    gAhcVidRecdContext.pAhcCurVidRecdCmdState = pNextState;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_RecdContextGetState
//  Description : Member function of gAhcVidRecdContext
//------------------------------------------------------------------------------
AHC_VIDEO_RECD_CMD_STATE* AHC_VIDEO_RecdContextGetState(void)
{
    return gAhcVidRecdContext.pAhcCurVidRecdCmdState;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_RecdContextSetRecordMode
//  Description : Member function of gAhcVidRecdContext
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_RecdContextSetRecordMode(void* pthis, AHC_VIDRECD_CMD bStartRecord)
{
    AHC_VIDEO_RECD_CONTEXT *pVidRecdContext = (AHC_VIDEO_RECD_CONTEXT *)pthis;

    if (NULL == pthis) {
        AHC_PRINT_RET_ERROR(0, 0);
        return AHC_FALSE;
    }

    return pVidRecdContext->pAhcCurVidRecdCmdState->pfStateExec(pthis, bStartRecord);
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_RestartRecMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_RestartRecMode(void)
{
    AHC_VIDRECD_CMD ahcVidRecdCmd = AHC_VIDRECD_IDLE;
    AHC_BOOL        ahcRet = AHC_TRUE;

    #if (VR_GET_CPU_TEMP_EN)
    int temp = 0;

    CLRREG16(BASE_REG_PMSAR_PA + REG_ID_19, (1<<7)); //ch7 reference voltage select to 2.0V bit6 for I3
    CLRREG16(BASE_REG_PMSAR_PA + REG_ID_10, (1<<0)); //reg_pm_dmy
    SETREG16(BASE_REG_PMSLEEP_PA + REG_ID_64, (1<<10));
    SETREG16(BASE_REG_PMSLEEP_PA + REG_ID_2F, (1<<2));
    CLRREG16(BASE_REG_PMSAR_PA + REG_ID_00, (1<<4));
    SETREG16(BASE_REG_PMSAR_PA + REG_ID_00, (1<<5));
    SETREG16(BASE_REG_PMSAR_PA + REG_ID_00, (1<<9));
    CLRREG16(BASE_REG_PMSAR_PA + REG_ID_00, (1<<8));
    mdelay(1);
    CLRREG16(BASE_REG_PMSAR_PA + REG_ID_00, (1<<6));
    mdelay(1);
    SETREG16(BASE_REG_PMSAR_PA + REG_ID_00, (1<<14));
    temp = INREG16(BASE_REG_PMSAR_PA + REG_ID_46);
    //GF28LP equation to calculate temperature
    temp = (1250 * (400 - temp) + 26000)/1000;
    AHC_DBG_MSG(1, "CPU Temp [%d]\r\n", temp);
    #endif

    // Make sure Video record state is already in START.
    ahcVidRecdCmd = AHC_VIDEO_GetCmdState((void *)(AHC_VIDEO_RecdContextGetState()));
    if (AHC_VIDRECD_START != ahcVidRecdCmd) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, 0); return AHC_FALSE;}

    ahcRet = AHC_VIDEO_SetRecordMode(AHC_VIDRECD_START);

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordMode
//  Description :
//------------------------------------------------------------------------------
/**
 @brief Set VideoR previrw / record

 Set VideoR previrw / record

 @param[in] bAudioOn        encode audio or not
 @param[in] bStartRecord    Preview or record
 @retval AHC_BOOL
*/
AHC_BOOL AHC_VIDEO_SetRecordMode(AHC_VIDRECD_CMD eVidRecCmd)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    // Initiate pAhcCurVidRecdCmdState as gAhcVidRecdCmdStateIdle
    if (NULL == gAhcVidRecdContext.pfGetState()) {
        gAhcVidRecdContext.pfSetState(&gAhcVidRecdCmdStateIdle);
    }

    ahcRet = gAhcVidRecdContext.pfSetRecordMode((void *)(&gAhcVidRecdContext), eVidRecCmd);

    if (ahcRet != AHC_TRUE) {
        AHC_DBG_ERR(1, "[ERR] %s\r\n", __FUNCTION__);
        gAhcVidRecdContext.pfSetState(&gAhcVidRecdCmdStateIdle);
    }

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_StopRecordModeExStopRec
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_StopRecordModeExStopRec(void)
{
    #if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    MMP_ULONG               ulRecordingTime = 0;
    #endif
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    AHC_FS_ATTRIBUTE        stFileAttr;
    AHC_FS_FILETIME         stFsTimeStruc;
    UINT32                  u32FileSize = 0;
    AHC_BOOL                ahcRet = AHC_TRUE;
    AHC_VIDEO_FILENAME_MGR  *pstPrmRecdFileNameMgr, *pstScdRecdFileNameMgr, *pstUsbRecdFileNameMgr;

    pstPrmRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_PRMREC);
    pstScdRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_SCDREC);
    pstUsbRecdFileNameMgr = AHC_VIDEO_GetFileNameMgrByType(AHC_VIDRECD_FILENAME_USBREC);

    /* Stop Seamless */
    AHC_VIDEO_SetVRSeamless(AHC_FALSE);

    #if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    MMPS_3GPRECD_GetCurRecordingTime(&ulRecordingTime);
    #endif

    #if (SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_2)
    #if (MOTION_DETECTION_EN)
    Menu_SetMotionDtcSensitivity_Parking(PARKINGMODE_IMAGE_DETECTION_NUM);
    #endif
    #endif

    /* Stop Record Flow */
    if (MMP_IsPrmCamExist() ||
        MMP_IsScdCamExist()) {
        eRetErr = MMPS_3GPRECD_StopAllRecord();
    }

    AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_AUD_PRERECORD_DAC, AHC_TRUE);

    #if (UVC_HOST_VIDEO_ENABLE)
    if (MMP_IsUSBCamExist()) {
        AHC_HostUVC_RecordStop();
    }
    #endif

    /* Close GPS/Gsensor File */
    #if (GPS_CONNECT_ENABLE == 1)
    if (AHC_GPS_Module_Attached())
    {
        #if (GPS_RAW_FILE_ENABLE == 1)
        UINT8 bGps_En;

        if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bGps_En) == AHC_TRUE) {
            switch (bGps_En) {
            case RECODE_GPS_OFF:
            case RECODE_GPS_IN_VIDEO:
                // NOP
                break;
            default:
                GPSCtrl_GPSRawClose();
                break;
            }
        }
        #endif

        #if (GPS_KML_FILE_ENABLE == 1)
        GPSCtrl_KMLGen_Write_TailAndClose();
        #endif
    }
    #endif

    #if (GPS_RAW_FILE_ENABLE == 1)
    GPSCtrl_GPSRawWrite_Close();
    #endif
    #if (GSENSOR_RAW_FILE_ENABLE == 1 && GPS_CONNECT_ENABLE == 0)
    GPSCtrl_GPSRawClose();
    #endif

    #if (GPS_CONNECT_ENABLE == 1)
    if (AHC_GPS_Module_Attached())
    {
        #if (GPS_RAW_FILE_EMER_EN == 1)
        UINT8 bGps_En;

        if (AHC_Menu_SettingGetCB((char*)COMMON_KEY_GPS_RECORD_ENABLE, &bGps_En) == AHC_TRUE) {
            switch (bGps_En) {
            case RECODE_GPS_OFF:
            case RECODE_GPS_IN_VIDEO:
                // NOP
                break;
            default:
                GPSCtrl_GPSRawClose_Emer();
                break;
            }
        }
        #endif
    }
    #endif

    #if(GSENSOR_RAW_FILE_ENABLE == 1 && GPS_CONNECT_ENABLE == 0 && GPS_RAW_FILE_EMER_EN == 1)
    GPSCtrl_GPSRawClose_Emer();
    #endif

    #if 1 // for Pre-encode, TBD
    if ((pstPrmRecdFileNameMgr->u8DeviceStatus) && (pstPrmRecdFileNameMgr->u8FileName[0] == 0))
    {
        AHC_DBG_MSG(1, "## %s, %d.\r\n", __FUNCTION__, __LINE__);
        return ahcRet;
    }
    #endif

    /* Add File to DCF DB */
    if (!uiGetParkingModeEnable())
    {
        #if (DCF_DB_COUNT > 1)
        AHC_UF_SelectDB(DCF_DB_TYPE_DB0_NORMAL);
        #endif

        if (pstPrmRecdFileNameMgr->u8DeviceStatus)
        {
            if (AHC_FS_FileDirGetInfo((INT8*)pstPrmRecdFileNameMgr->u8FullName, STRLEN((INT8*)pstPrmRecdFileNameMgr->u8FullName), &stFileAttr, &stFsTimeStruc, &u32FileSize) == AHC_ERR_NONE) {
                AHC_UF_PostAddFile(m_u16CurVideoDirKey, (INT8*)pstPrmRecdFileNameMgr->u8FileName);
                #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
                AHC_VIDEO_StoreJpgThumbnail(VIDENC_STREAM_PRM_RECD);
                #endif
            }
        }

        #if (AHC_MULTI_TRACK_EN == 0)
        if (pstScdRecdFileNameMgr->u8DeviceStatus)
        {
            if (AHC_FS_FileDirGetInfo((INT8*)pstScdRecdFileNameMgr->u8FullName, STRLEN((INT8*)pstScdRecdFileNameMgr->u8FullName), &stFileAttr, &stFsTimeStruc, &u32FileSize) == AHC_ERR_NONE) {
                AHC_UF_PostAddFile(m_u16CurVideoDirKey, (INT8*)pstScdRecdFileNameMgr->u8FileName);
                #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
                AHC_VIDEO_StoreJpgThumbnail(VIDENC_STREAM_SCD_RECD);
                #endif
            }
        }

        if (pstUsbRecdFileNameMgr->u8DeviceStatus)
        {
            if (AHC_FS_FileDirGetInfo((INT8*)pstUsbRecdFileNameMgr->u8FullName, STRLEN((INT8*)pstUsbRecdFileNameMgr->u8FullName), &stFileAttr, &stFsTimeStruc, &u32FileSize) == AHC_ERR_NONE) {
                AHC_UF_PostAddFile(m_u16CurVideoDirKey, (INT8*)pstUsbRecdFileNameMgr->u8FileName);
                #if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
                AHC_VIDEO_StoreJpgThumbnail(VIDENC_STREAM_UVC_RECD);
                #endif
            }
        }
        #endif
    }

    /* Modify the RTC Time and FileName */
    #if 0 // (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    {
        AHC_RTC_TIME    stRtcTime;
        int             nSecondOffset = 0;

        AHC_RTC_GetTime(&stRtcTime);

        if ((m_stAhcVidRecdStartRtcTime.uwYear <= RTC_DEFAULT_YEAR) && (stRtcTime.uwYear > RTC_DEFAULT_YEAR)) {

            nSecondOffset = -1*(ulRecordingTime/1000);
            AHC_DT_ShiftRtc(&stRtcTime, nSecondOffset);

            AHC_DBG_MSG(1, "AHC_VIDEO_StopRecordMode:AHC_UF_Rename::Old:%d-%d-%d:%d-%d-%d New:%d-%d-%d:%d-%d-%d \r\n",
                        m_stAhcVidRecdStartRtcTime.uwYear,
                        m_stAhcVidRecdStartRtcTime.uwMonth,
                        m_stAhcVidRecdStartRtcTime.uwDay,
                        m_stAhcVidRecdStartRtcTime.uwHour,
                        m_stAhcVidRecdStartRtcTime.uwMinute,
                        m_stAhcVidRecdStartRtcTime.uwSecond,
                        stRtcTime.uwYear,
                        stRtcTime.uwMonth,
                        stRtcTime.uwDay,
                        stRtcTime.uwHour,
                        stRtcTime.uwMinute,
                        stRtcTime.uwSecond);

            if (m_stAhcVidRecdStartRtcTime.uwYear != 0)
                AHC_UF_Rename(AHC_UF_GetDB(), &m_stAhcVidRecdStartRtcTime, &stRtcTime);

            m_stAhcVidRecdStartRtcTime = stRtcTime;
        }
    }
    #endif

    #if (AHC_EMERGENTRECD_SUPPORT)
    if (MMPS_3GPRECD_GetEmergActionType() == MMP_3GPRECD_EMERG_MOVE_FILE)
    {
        if (AHC_VIDEO_GetNormal2Emergency())
        {
            UINT16          DirKey = 0;

            AHC_VIDEO_SetNormal2Emergency(AHC_FALSE);

            AHC_DBG_MSG(1, "Normal2Emer File: %s\r\n", pstPrmRecdFileNameMgr->u8FileName);

            AHC_UF_MoveFile(DCF_DB_TYPE_DB0_NORMAL, DCF_DB_TYPE_DB2_EVENT, DirKey, pstPrmRecdFileNameMgr->u8FileName, AHC_TRUE);
        }
    }
    #endif

    /* Protect File if Needed */
    if (AHC_Protect_GetType() != AHC_PROTECT_NONE)
    {
        #ifdef CFG_CUS_VIDEO_PROTECT_PROC
        CFG_CUS_VIDEO_PROTECT_PROC();
        #else
        AHC_Protect_SetVRFile(AHC_PROTECTION_CUR_FILE, AHC_Protect_GetType());
        AHC_Protect_SetType(AHC_PROTECT_NONE);
        #endif
    }

    #if (FS_FORMAT_FREE_ENABLE)
    // Note: Below setting must be set after MMPS_3GPRECD_StopAllRecord() which will return after finished writing video file.
    MMPS_FORMATFREE_EnableWrite(0); // Disable "Format Free Write" which will not update FAT table
    #endif

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_StopRecordModeExStopPreview
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_StopRecordModeExStopPreview(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    /* Disable PRM Sticker Before PRM Cam Preview Stop */
    if (MMP_TRUE == MMPS_3GPRECD_IsStickerEnable(MMP_STICKER_ID_0)) {
        MMPS_3GPRECD_EnableSticker(MMP_STICKER_ID_0, MMP_FALSE);
    }

    /* Stop Preview Flow */
    #if (UVC_HOST_VIDEO_ENABLE)
    if (MMP_IsUSBCamExist()) {

        USB_DETECT_PHASE eUSBCurStates = 0;

        AHC_USBGetStates(&eUSBCurStates, AHC_USB_GET_PHASE_CURRENT);

        if (eUSBCurStates == USB_DETECT_PHASE_REAR_CAM) {
            ahcRet = AHC_HostUVC_PreviewStop(AHC_HUVC_UI_MODE_VR);
        }

        ahcRet = AHC_HostUVC_ResetFBMemory();
    }
    #endif

    if (MMP_IsPrmCamExist()) {
        eRetErr = MMPS_3GPRECD_PrmCamPreviewStop(gsAhcPrmSensor);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
    }

    if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
        MMPS_Display_EnableScdAnaDecSnrPreviewWindow(MMPS_PREVIEW_UI_MODE_VR, MMP_FALSE);
        MMPS_Sensor_EnableAnaDecSrcTypeDetect(MMP_FALSE);
        eRetErr = MMPS_3GPRECD_ScdCamPreviewStop(gsAhcScdSensor);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
    }
    else if (CAM_CHECK_SCD(SCD_CAM_YUV_SENSOR)) {
        eRetErr = MMPS_3GPRECD_ScdCamPreviewStop(gsAhcScdSensor);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
    }
    else if (CAM_CHECK_SCD(SCD_CAM_BAYER_SENSOR)) {
        eRetErr = MMPS_3GPRECD_ScdCamPreviewStop(gsAhcScdSensor);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); }
    }

    AHC_VIDEO_SetRecWithWNR(AHC_FALSE);

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_StopRecordModeExStopSensor
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_StopRecordModeExStopSensor(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    /* Shut Down Sensor */
    if (MMP_IsPrmCamExist()) {
        eRetErr = MMPS_Sensor_PowerDown(gsAhcPrmSensor);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
    }

    if (MMP_IsScdCamExist()) {
        if (CAM_CHECK_SCD(SCD_CAM_ANA_DECODER)) {
            MMPS_Sensor_EnableAnaDecSrcTypeDetectTimer(gsAhcScdSensor, NULL, SNR_R_CHECK_SIG_TYPE_PERIODIC, MMP_FALSE);
        }
        eRetErr = MMPS_Sensor_PowerDown(gsAhcScdSensor);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
    }

    return ahcRet;
}

#if 0
void _____VR_Sticker_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_ConfigTimeStamp
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AHC_VIDEO_ConfigTimeStamp(UINT32 u32TimeStampOp, AHC_RTC_TIME* pstRtcTime, AHC_BOOL bScdCamConnected)
{
#if (AHC_ENABLE_VIDEO_STICKER)

    MMP_STICKER_ATTR    stStickerAttr;
    AUTL_DATETIME       stDateTime;
    UINT32              u32SrcAddr = 0;
    UINT16              u16SrcW = 0;
    UINT16              u16SrcH = 0;
    UINT16              u16TempColorFmt = MMP_ICON_COLOR_RGB565;
    UINT16              u16ColorFormat = MMP_ICON_COLOR_RGB565;
    UINT32              u32PrmStickerX = 0, u32PrmStickerY = 0;
    UINT32              u32ScdStickerX = 0, u32ScdStickerY = 0;
    MMP_ERR             eRetErr = MMP_ERR_NONE;
    UINT32              u32OSDid = DATESTAMP_PRIMARY_OSD_ID;
    static AHC_BOOL     bVRTimeStampRunning = AHC_FALSE;

    OS_CRITICAL_INIT();

    OS_ENTER_CRITICAL();

    // Add a protection to avoid this function is called by multi-task and make broken stamp
    if (bVRTimeStampRunning == AHC_TRUE) {
        OS_EXIT_CRITICAL();
        return AHC_FALSE;
    }

    bVRTimeStampRunning = AHC_TRUE;
    OS_EXIT_CRITICAL();

    AIHC_DrawReservedOSD(AHC_TRUE);

    m_u32AhcTimeStampBufIdx ^= 1;

    if (m_u32AhcTimeStampBufIdx == 0) {
        u32OSDid = DATESTAMP_PRIMARY_OSD_ID;
    }
    else {
        u32OSDid = DATESTAMP_PRIMARY_OSD_ID_SUB;
    }

    if (bScdCamConnected) {
        DrawVideo_GetTimeStampPosition(gsAhcScdSensor,
                                       u32OSDid,
                                       u32TimeStampOp,
                                       &u32SrcAddr,
                                       &u16SrcW,
                                       &u16SrcH,
                                       &u16TempColorFmt,
                                       &u32ScdStickerX,
                                       &u32ScdStickerY);
        AHC_DBG_ERR(0, "Src W %d H %d X %d Y %d\r\n", u16SrcW, u16SrcH, u32ScdStickerX, u32ScdStickerY);
    }
    #endif

    DrawVideo_TimeStamp(u32OSDid,
                        u32TimeStampOp,
                        pstRtcTime,
                        &u32SrcAddr,
                        &u16SrcW,
                        &u16SrcH,
                        &u16TempColorFmt,
                        &u32PrmStickerX,
                        &u32PrmStickerY);

    AIHC_DrawReservedOSD(AHC_FALSE);

    stDateTime.usYear       = pstRtcTime->uwYear;
    stDateTime.usMonth      = pstRtcTime->uwMonth;
    stDateTime.usDay        = pstRtcTime->uwDay;
    stDateTime.usDayInWeek  = pstRtcTime->uwDayInWeek;
    stDateTime.usHour       = pstRtcTime->uwHour;
    stDateTime.usMinute     = pstRtcTime->uwMinute;
    stDateTime.usSecond     = pstRtcTime->uwSecond;
    stDateTime.ubAmOrPm     = pstRtcTime->ubAmOrPm;
    stDateTime.b_12FormatEn = pstRtcTime->b_12FormatEn;

    stStickerAttr.ulBaseAddr       = u32SrcAddr;
    stStickerAttr.usWidth          = u16SrcW;
    stStickerAttr.usHeight         = u16SrcH;
    stStickerAttr.colorformat      = u16ColorFormat;
    stStickerAttr.ulTpColor        = GUI_BLACK;
    stStickerAttr.bTpEnable        = MMP_TRUE;
    stStickerAttr.bSemiTpEnable    = MMP_FALSE;
    stStickerAttr.ubAlphaWeight    = 16;
    stStickerAttr.eMirrorType      = MMP_ICON_MIRROR_NONE;
    memcpy(&(stStickerAttr.stDateTime), &stDateTime, sizeof(AUTL_DATETIME));

    if (MMP_IsPrmCamExist()) {
        UI_STATE_ID eCurUIState = uiGetCurrentState();
        if (UI_PCCAM_STATE == eCurUIState && pcam_usb_get_timeStamp_status() == MMP_TRUE) {
            stStickerAttr.ubStickerId   = MMP_STICKER_ID_1;
        }
        else {
            stStickerAttr.ubStickerId   = MMP_STICKER_ID_0;
        }

        stStickerAttr.usStartX      = (MMP_USHORT)u32PrmStickerX;
        stStickerAttr.usStartY      = (MMP_USHORT)u32PrmStickerY;
        MMPS_3GPRECD_SetStickerAttr(&stStickerAttr);
    }

    if (bScdCamConnected) {
        stStickerAttr.ubStickerId = MMP_STICKER_ID_1;
        stStickerAttr.usStartX    = (MMP_USHORT)u32ScdStickerX;
        stStickerAttr.usStartY    = (MMP_USHORT)u32ScdStickerY;
        MMPS_3GPRECD_SetStickerAttr(&stStickerAttr);
    }

    bVRTimeStampRunning = AHC_FALSE;

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_UpdateTimeStamp
//  Description :
//------------------------------------------------------------------------------
void AHC_VIDEO_UpdateTimeStamp(AHC_RTC_TIME* pstRtcTime, AHC_BOOL bSetStickerEnable)
{
#if (AHC_ENABLE_VIDEO_STICKER)
    AHC_BOOL    bScdCamConnected = AHC_FALSE;
    UINT32      u32TimeStampOp = 0;
    UI_STATE_ID eCurUIState = UI_STATE_UNSUPPORTED;
    UI_STATE_ID eParentUIState = UI_STATE_UNSUPPORTED;

    eCurUIState = uiGetCurrentState();
    StateModeGetParent(eCurUIState, &eParentUIState);

    if (UI_STATE_UNSUPPORTED != eParentUIState) {
        eCurUIState = eParentUIState;
    }

    if (UI_VIDEO_STATE  != eCurUIState &&
        UI_CAMERA_STATE != eCurUIState &&
        UI_PCCAM_STATE  != eCurUIState) {
        return;
    }

    AHC_Capture_GetConfig(ACC_DATE_STAMP, &u32TimeStampOp);

    if (MMP_IsScdCamExist()) {
        bScdCamConnected = AHC_SNR_CheckScdCamConnectSts();
    }

    // Warning: We should separate AIT MJPEG+H264 or NV12+H264
    if ((CAM_CHECK_USB(USB_CAM_SONIX_MJPEG2H264)) ||
        (CAM_CHECK_USB(USB_CAM_AIT) && MMP_GetAitCamStreamType() == AIT_REAR_CAM_STRM_MJPEG_H264)) {
        if (AHC_HostUVC_IsDevEnabled()) {
            bScdCamConnected = AHC_TRUE; // TBD
        }
    }

    if (u32TimeStampOp & AHC_ACC_TIMESTAMP_ENABLE_MASK) {

        AHC_VIDEO_ConfigTimeStamp(u32TimeStampOp, pstRtcTime, bScdCamConnected);

        if (bSetStickerEnable) {
            if (UI_PCCAM_STATE == eCurUIState && pcam_usb_get_timeStamp_status() == MMP_TRUE) {
                MMPS_3GPRECD_EnableSticker(MMP_STICKER_ID_1, MMP_TRUE);
            }
            else {
                if (MMP_FALSE == MMPS_3GPRECD_IsStickerEnable(MMP_STICKER_ID_0)) {
                    MMPS_3GPRECD_EnableSticker(MMP_STICKER_ID_0, MMP_TRUE);
                }
                if (MMP_FALSE == MMPS_3GPRECD_IsStickerEnable(MMP_STICKER_ID_1)) {
                    if (bScdCamConnected) {
                        MMPS_3GPRECD_EnableSticker(MMP_STICKER_ID_1, MMP_TRUE);
                    }
                }
            }
        }
    }
    else {
        if (MMP_TRUE == MMPS_3GPRECD_IsStickerEnable(MMP_STICKER_ID_0)) {
            MMPS_3GPRECD_EnableSticker(MMP_STICKER_ID_0, MMP_FALSE);
        }
        if (MMP_TRUE == MMPS_3GPRECD_IsStickerEnable(MMP_STICKER_ID_1)) {
            MMPS_3GPRECD_EnableSticker(MMP_STICKER_ID_1, MMP_FALSE);
        }
    }
#endif
}

#if 0
void _____VR_Capture_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_StillCapture
//  Description :
//------------------------------------------------------------------------------
static AHC_BOOL AHC_VIDEO_StillCapture(void)
{
    AHC_BOOL                ahc_ret = AHC_TRUE;
    MMP_BYTE                bPrmJpgFileName[MAX_FULL_FILENAME_SIZE] = {0};
    MMP_BYTE                bScdJpgFileName[MAX_FULL_FILENAME_SIZE] = {0};
    MMP_BYTE                bDirName[16];
    UINT16                  u16CaptureDirKey = 0;
    UINT8                   u8PrmCaptureFileName[32] = {0};
    UINT8                   u8ScdCaptureFileName[32] = {0};
    UINT8                   u8CreateNewDir = 0;
    AHC_BOOL                bAddPrmCamToDB = AHC_FALSE;
    AHC_BOOL                bAddScdCamToDB = AHC_FALSE;
    MMP_ERR                 eRetErr = MMP_ERR_NONE;
    MMPS_DSC_CAPTURE_INFO   stStillCaptInfo[DSC_CAPTURE_MAX_CAM_NUM] = {{0}, {0}, {0}};
    MMP_UBYTE               i = 0;
    MMP_BOOL                bPrmCamExist = MMP_FALSE;
    MMP_BOOL                bScdCamExist = MMP_FALSE;
    UINT32                  u32CaptureW = 0, u32CaptureH = 0;
    UINT32                  u32ThumbW = 0, u32ThumbH = 0;

    for (i = 0; i < DSC_CAPTURE_MAX_CAM_NUM; i++) {
        stStillCaptInfo[i].bCaptureEn = MMP_FALSE;
    }

    if (MMP_IsPrmCamExist()) {
        bPrmCamExist = MMP_TRUE;
    }

    if (MMP_IsScdCamExist() || MMP_IsUSBCamExist()) {
        bScdCamExist = AHC_Capture_IsScdCamConnect();
    }

    /* Configure EXIF Information */
    if (1/*MMP_TRUE == stStillCaptInfo[0].bExifEn*/) {

        AHC_Capture_ConfigSysInfoEXIF();
        AHC_Capture_ConfigRtcEXIF();
        AHC_Capture_ConfigMenuEXIF();
    }

    AHC_Capture_GetConfig(ACC_CUS_THUMB_W, &u32ThumbW);
    AHC_Capture_GetConfig(ACC_CUS_THUMB_H, &u32ThumbH);

    AHC_UF_SetFreeChar(0, DCF_SET_FREECHAR, (UINT8*)SNAP_DEFAULT_FILE_FREECHAR);

#if (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_NORMAL)
    MEMSET(bDirName, 0, sizeof(bDirName));

    ahc_ret = AHC_UF_GetName(&u16CaptureDirKey, (INT8*)bDirName, (INT8*)u8PrmCaptureFileName, &u8CreateNewDir);

    if (ahc_ret == AHC_TRUE) {
        AHC_DBG_MSG(0, "CaptureDirKey=%d  PrmCaptureFileName=%s\r\n", u16CaptureDirKey, u8PrmCaptureFileName);

        STRCPY(bPrmJpgFileName, (MMP_BYTE*)AHC_UF_GetRootName());
        STRCAT(bPrmJpgFileName, "\\");
        STRCAT(bPrmJpgFileName, bDirName);

        if (u8CreateNewDir) {
            MMPS_FS_DirCreate((INT8*)bPrmJpgFileName, STRLEN(bPrmJpgFileName));
            AHC_UF_AddDir(bDirName);
        }

        STRCAT(bPrmJpgFileName, "\\");
        STRCAT(bPrmJpgFileName, (INT8*)u8PrmCaptureFileName);
        STRCAT(bPrmJpgFileName, EXT_DOT);
        STRCAT(bPrmJpgFileName, PHOTO_JPG_EXT);

        VideoCaptureInfo.bFileName = bPrmJpgFileName;
        VideoCaptureInfo.ulFileNameLen = STRLEN(bPrmJpgFileName);

        eRetErr = MMPS_3GPRECD_StillCapture(&VideoCaptureInfo);

        if (MMP_ERR_NONE == eRetErr)
        {
            STRCAT((INT8*)u8PrmCaptureFileName, EXT_DOT);
            STRCAT((INT8*)u8PrmCaptureFileName, PHOTO_JPG_EXT);

            AHC_UF_PreAddFile(u16CaptureDirKey, (INT8*)u8PrmCaptureFileName);
            AHC_UF_PostAddFile(u16CaptureDirKey, (INT8*)u8PrmCaptureFileName);
        }
        else {
            AHC_DBG_ERR(1, "-E- MMPS_3GPRECD_StillCapture return 0x%X\r\n", eRetErr);
        }
    }
    else {
        eRetErr = MMP_3GPRECD_ERR_NOT_ENOUGH_SPACE;
    }

#elif (DCF_FILE_NAME_TYPE == DCF_FILE_NAME_TYPE_DATE_TIME)
    {
        AHC_RTC_TIME    stRtcTime;
        UINT8           u8CamStatus = AHC_Capture_GetCamStatusForDCF();

        AHC_RTC_GetTime(&stRtcTime);

        if (bPrmCamExist) {

            MEMSET(bPrmJpgFileName     , 0, sizeof(bPrmJpgFileName));
            MEMSET(u8PrmCaptureFileName, 0, sizeof(u8PrmCaptureFileName));

            AHC_VIDEO_GetRecdResol(gsAhcPrmSensor, &u32CaptureW, &u32CaptureH);

            stStillCaptInfo[0].usPrimaryW       = u32CaptureW;
            stStillCaptInfo[0].usPrimaryH       = u32CaptureH;
            stStillCaptInfo[0].usThumbWidth     = u32ThumbW;
            stStillCaptInfo[0].usThumbHeight    = u32ThumbH;

            stStillCaptInfo[0].stQualityCtl.bTargetCtl      = MMP_FALSE;
            stStillCaptInfo[0].stQualityCtl.bLimitCtl       = MMP_FALSE;
            stStillCaptInfo[0].stQualityCtl.ulTargetSize    = 400;
            stStillCaptInfo[0].stQualityCtl.ulLimitSize     = 420;
            stStillCaptInfo[0].stQualityCtl.usMaxTrialCnt   = 1;
            stStillCaptInfo[0].stQualityCtl.ubQualitySel    = MMP_JPGENC_RC_QUALITY_SEL_NORMAL;

            stStillCaptInfo[0].bCaptureEn       = MMP_TRUE;
            stStillCaptInfo[0].bExifEn          = MMP_TRUE;
            stStillCaptInfo[0].bThumbnailEn     = MMP_FALSE;
            stStillCaptInfo[0].bFirstShot       = MMP_TRUE;
            stStillCaptInfo[0].ubShotMode       = JPE_COMP_SINGLE_SHOT;
            stStillCaptInfo[0].usMaxShotNum     = 1;
            stStillCaptInfo[0].ubUiMode         = JPE_COMP_UI_MODE_VR;
            stStillCaptInfo[0].ubCamSel         = gsAhcPrmSensor;
            stStillCaptInfo[0].ubRawFmt         = JPE_COMP_FMT_NV12;
            stStillCaptInfo[0].ulExtraBufAddr   = 0;

        #if (AHC_CAPTURE_SYNC_STAMP_FILENAME == 0)
            AHC_UF_SetRearCamPathFlag(AHC_FALSE);

            ahc_ret = AHC_UF_GetName2(&stRtcTime, (INT8*)bPrmJpgFileName, (INT8*)u8PrmCaptureFileName, u8CamStatus);
            if (ahc_ret != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahc_ret)}

            STRCAT(bPrmJpgFileName, EXT_DOT);
            STRCAT(bPrmJpgFileName, PHOTO_JPG_EXT);
            STRCAT((INT8*)u8PrmCaptureFileName, EXT_DOT);
            STRCAT((INT8*)u8PrmCaptureFileName, PHOTO_JPG_EXT);

            stStillCaptInfo[0].bFileName      = bPrmJpgFileName;
            stStillCaptInfo[0].ulFileNameLen  = STRLEN(bPrmJpgFileName);

            AHC_DBG_MSG(1, "VR PrmJpeg [%s]\r\n", u8PrmCaptureFileName);

            #if (FS_FORMAT_FREE_ENABLE)
            AHC_FF_SetFileNameSlot(stStillCaptInfo[0].bFileName, DCF_CAM_FRONT);
            #endif
        #endif

            if (stStillCaptInfo[0].ubShotMode == JPE_COMP_SINGLE_SHOT)
                bAddPrmCamToDB = AHC_TRUE;
            else
                bAddPrmCamToDB = AHC_FALSE;
        }

        if (bScdCamExist) {

            MEMSET(bScdJpgFileName     , 0, sizeof(bScdJpgFileName));
            MEMSET(u8ScdCaptureFileName, 0, sizeof(u8ScdCaptureFileName));

            AHC_VIDEO_GetRecdResol(gsAhcScdSensor, &u32CaptureW, &u32CaptureH);

            stStillCaptInfo[1].usPrimaryW       = u32CaptureW;
            stStillCaptInfo[1].usPrimaryH       = u32CaptureH;
            stStillCaptInfo[1].usThumbWidth     = u32ThumbW;
            stStillCaptInfo[1].usThumbHeight    = u32ThumbH;

            stStillCaptInfo[1].stQualityCtl.bTargetCtl      = MMP_FALSE;
            stStillCaptInfo[1].stQualityCtl.bLimitCtl       = MMP_FALSE;
            stStillCaptInfo[1].stQualityCtl.ulTargetSize    = 400;
            stStillCaptInfo[1].stQualityCtl.ulLimitSize     = 420;
            stStillCaptInfo[1].stQualityCtl.usMaxTrialCnt   = 1;
            stStillCaptInfo[1].stQualityCtl.ubQualitySel    = MMP_JPGENC_RC_QUALITY_SEL_NORMAL;

            stStillCaptInfo[1].bCaptureEn       = MMP_TRUE;
            stStillCaptInfo[1].bExifEn          = MMP_TRUE;
            stStillCaptInfo[1].bThumbnailEn     = MMP_FALSE;
            stStillCaptInfo[1].bFirstShot       = MMP_TRUE;
            stStillCaptInfo[1].ubShotMode       = JPE_COMP_SINGLE_SHOT;
            stStillCaptInfo[1].usMaxShotNum     = 1;
            stStillCaptInfo[1].ubUiMode         = JPE_COMP_UI_MODE_VR;
            stStillCaptInfo[1].ubCamSel         = gsAhcScdSensor;
            stStillCaptInfo[1].ubRawFmt         = JPE_COMP_FMT_NV12;
            stStillCaptInfo[1].ulExtraBufAddr   = 0;

        #if (AHC_CAPTURE_SYNC_STAMP_FILENAME == 0)
            AHC_UF_SetRearCamPathFlag(AHC_TRUE);

            ahc_ret = AHC_UF_GetName2(&stRtcTime, (INT8*)bScdJpgFileName, (INT8*)u8ScdCaptureFileName, u8CamStatus);
            if (ahc_ret != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahc_ret);}

            STRCAT(bScdJpgFileName, EXT_DOT);
            STRCAT(bScdJpgFileName, PHOTO_JPG_EXT);
            STRCAT((INT8*)u8ScdCaptureFileName, EXT_DOT);
            STRCAT((INT8*)u8ScdCaptureFileName, PHOTO_JPG_EXT);

            stStillCaptInfo[1].bFileName      = bScdJpgFileName;
            stStillCaptInfo[1].ulFileNameLen  = STRLEN(bScdJpgFileName);

            AHC_DBG_MSG(1, "VR ScdJpeg [%s]\r\n", u8ScdCaptureFileName);

            #if (FS_FORMAT_FREE_ENABLE)
            AHC_FF_SetFileNameSlot(stStillCaptInfo[1].bFileName, DCF_CAM_REAR);
            #endif

        #endif

            if (stStillCaptInfo[1].ubShotMode == JPE_COMP_SINGLE_SHOT)
                bAddScdCamToDB = AHC_TRUE;
            else
                bAddScdCamToDB = AHC_FALSE;
        }

        /* Allocate buffer */
        MMPS_DSC_AllocFileNameBuf();
        MMPS_DSC_AllocExifEncBuf();

        /* Set Callback Function */
        #if (AHC_CAPTURE_SYNC_STAMP_FILENAME)
        AHC_Capture_SetCallBackFunc(AHC_CAPTURE_CALLBACK_STORECARD_START);
        AHC_Capture_SetCallBackFunc(AHC_CAPTURE_CALLBACK_STORECARD_END);
        #endif

        if (bPrmCamExist && bScdCamExist) {
            eRetErr = MMPS_3GPRECD_StillDualCapture(&stStillCaptInfo[0]);
        }
        else {
            if (bPrmCamExist)
                eRetErr = MMPS_3GPRECD_StillPrmCapture(&stStillCaptInfo[0]);
            if (bScdCamExist)
                eRetErr = MMPS_3GPRECD_StillScdCapture(&stStillCaptInfo[1]);
        }

        if (MMP_ERR_NONE == eRetErr)
        {
        #if (AHC_CAPTURE_SYNC_STAMP_FILENAME == 0)
            if (bAddPrmCamToDB) {

                AHC_UF_SetRearCamPathFlag(AHC_FALSE);

                ahc_ret = AHC_UF_PreAddFile(u16CaptureDirKey, (INT8*)u8PrmCaptureFileName);
                ahc_ret = AHC_UF_PostAddFile(u16CaptureDirKey, (INT8*)u8PrmCaptureFileName);
                if (ahc_ret != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahc_ret); }
            }

            if (bAddScdCamToDB) {

                AHC_UF_SetRearCamPathFlag(AHC_TRUE);

                ahc_ret = AHC_UF_PreAddFile(u16CaptureDirKey, (INT8*)u8ScdCaptureFileName);
                ahc_ret = AHC_UF_PostAddFile(u16CaptureDirKey, (INT8*)u8ScdCaptureFileName);
                if (ahc_ret != AHC_TRUE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahc_ret); }
            }
        #endif
        }
        else {
            AHC_DBG_ERR(1, "ERR : 3GPRECD_StillCapture [0x%X]\r\n", eRetErr);
        }
    }
#endif

    AHC_UF_SetFreeChar(0, DCF_SET_FREECHAR, (UINT8*)VIDEO_DEFAULT_FLIE_FREECHAR);

    /* Free buffer */
    MMPS_DSC_FreeFileNameBuf();
    MMPS_DSC_FreeExifEncBuf();

    return ahc_ret;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_CaptureClipCmd
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_CaptureClipCmd(UINT16 wCommand, UINT16 wOp)
{
    AHC_BOOL ahc_ret = AHC_TRUE;

    switch(wCommand) {

    case AHC_CAPTURE_SNAPSHOT:
        ahc_ret = AHC_VIDEO_StillCapture();
        break;
    default:
        break;
    }

    return ahc_ret;
}

#if (AHC_VR_THUMBNAIL_CREATE_JPG_FILE == 1)
//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_StoreJpgThumbnail
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_StoreJpgThumbnail(MMP_USHORT usStreamType)
{
#if (SUPPORT_VR_THUMBNAIL)
    if (usStreamType == VIDENC_STREAM_PRM_RECD) {
        AHC_DBG_MSG(1, FG_GREEN("[PRM] Store %s\r\n"), m_CurThumbJpgFullName);
        MMPS_3GPRECD_StoreVRThumbToFile(m_CurThumbJpgFullName, STRLEN(m_CurThumbJpgFullName), VIDENC_STREAM_PRM_RECD);
    }
    else if (usStreamType == VIDENC_STREAM_PRM_EMERG) {
        AHC_DBG_MSG(1, FG_GREEN("[EMG] Store %s\r\n"), m_chEmerThumbFullName);
        MMPS_3GPRECD_StoreVRThumbToFile(m_chEmerThumbFullName, STRLEN(m_chEmerThumbFullName), VIDENC_STREAM_PRM_EMERG);
    }
    else if (usStreamType == VIDENC_STREAM_UVC_RECD) {
        AHC_DBG_MSG(1, FG_GREEN("[UVC] Store %s\r\n"), m_CurThumbJpgFullName_USBH);
        MMPS_3GPRECD_StoreVRThumbToFile(m_CurThumbJpgFullName_USBH, STRLEN(m_CurThumbJpgFullName_USBH), VIDENC_STREAM_UVC_RECD);
    }
    else if (usStreamType == VIDENC_STREAM_UVC_EMERG) {
        AHC_DBG_MSG(1, FG_GREEN("[UVC_EMG] Store %s\r\n"), m_chEmerThumbFullName_USBH);
        MMPS_3GPRECD_StoreVRThumbToFile(m_chEmerThumbFullName_USBH, STRLEN(m_chEmerThumbFullName_USBH), VIDENC_STREAM_UVC_EMERG);
    }
    else if (usStreamType == VIDENC_STREAM_SCD_RECD) {
        AHC_DBG_MSG(1, FG_GREEN("[SCD] Store %s\r\n"), m_CurThumbJpgFullName_Rear);
        MMPS_3GPRECD_StoreVRThumbToFile(m_CurThumbJpgFullName_Rear, STRLEN(m_CurThumbJpgFullName_Rear), VIDENC_STREAM_SCD_RECD);
    }
    else if (usStreamType == VIDENC_STREAM_SCD_EMERG) {
        AHC_DBG_MSG(1, FG_GREEN("[SCD_EMG] Store %s\r\n"), m_chEmerThumbFullName_Rear);
        MMPS_3GPRECD_StoreVRThumbToFile(m_chEmerThumbFullName_Rear, STRLEN(m_chEmerThumbFullName_Rear), VIDENC_STREAM_SCD_EMERG);
    }
#endif
    return AHC_TRUE;
}

#endif // AHC_VR_THUMBNAIL_CREATE_JPG_FILE

#if 0
void _____VR_Parking_Mode_Function_________(){ruturn;} //dummy
#endif

//------------------------------------------------------------------------------
//  Function    : VRFileFullCBParkingMode
//  Description :
//------------------------------------------------------------------------------
void VRFileFullCBParkingMode(void)
{
    AHC_BOOL ahcRet = AHC_TRUE;

    AHC_DBG_MSG(1, FG_GREEN("<VRFileFullCBParkingMode>\r\n"));

    ahcRet = AHC_KeyEventIDCheckConflict(BUTTON_VRCB_FILE_FULL);
    if (ahcRet != AHC_TRUE) {
        AHC_DBG_MSG(1, " %s, Re-Check Src Type: %d.\r\n", __FUNCTION__, AHC_GetCurKeyEventID());
        AHC_SNR_CheckAnaDecSrcType(MMPS_PREVIEW_UI_MODE_VR, gsAhcScdSensor);
    }

    AHC_SetCurKeyEventID(BUTTON_VRCB_FILE_FULL);
    AHC_SendAHLMessage_HP(AHLM_UI_NOTIFICATION, BUTTON_VRCB_FILE_FULL, 0);
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_GetRecTimeLimitParkingMode
//  Description :
//------------------------------------------------------------------------------
UINT32 AHC_VIDEO_GetRecTimeLimitParkingMode(void)
{
    UINT32 u32TimeLimit = 60;

#if (SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_1)
    u32TimeLimit = 60;
#elif (SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_2)
    if (uiGetParkingModeEnable() ||
        uiGetParkingModeMenuState()) {
        u32TimeLimit = 60; // Set 16 to ensure the length is larger than 15.
    }
#elif (SUPPORT_PARKINGMODE == PARKINGMODE_STYLE_4)
    u32TimeLimit = AHC_GetVMDRecTimeLimit();
#endif

    return u32TimeLimit;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_CyclicDeleteFilesParkingMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_CyclicDeleteFilesParkingMode(void)
{
    UINT32      u32TimeLimit = 0;
    AHC_BOOL    ahcRet     = AHC_TRUE;
    AHC_BOOL    b_delete   = AHC_TRUE;

    b_delete = AHC_VIDEO_GetRecdDeleteFileEn();

    /* Protect File Flow */
    // NOP

    #if (FS_FORMAT_FREE_ENABLE)
    b_delete = AHC_FALSE;
    #endif

    /* Delete File Flow */
    if (b_delete){
        u32TimeLimit = AHC_VIDEO_GetRecTimeLimitParkingMode();
        if (AHC_Deletion_RemoveEx(DCF_DB_TYPE_DB1_PARKING, u32TimeLimit) == AHC_FALSE){
            if (AHC_Deletion_RemoveEx(DCF_DB_TYPE_DB1_PARKING, u32TimeLimit) == AHC_FALSE)
                return AHC_FALSE;
        }
    }

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeInitParkingMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeInitParkingMode(void)
{
    #if (MOTION_DETECTION_EN)
    UINT8       u8MvTh = 0, u8CntTh = 0;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    #endif
    AHC_BOOL    ahcRet = AHC_TRUE;

    // Exit ADAS mode first
    if (AHC_IsADASEnabled()) {
        #if (SUPPORT_ADAS)
        MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_LDWS, MMP_FALSE);
        MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_FCWS, MMP_FALSE);
        MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_SAG, MMP_FALSE);
        #endif
        AHC_EnableADAS(AHC_FALSE);
    }

    // It must be set before enter Preview mode
    MMPS_3GPRECD_SetYFrameType(MMPS_3GPRECD_Y_FRAME_TYPE_VMD);

    // Execute common init.
    ahcRet = AHC_VIDEO_SetRecordModeInitCommon();
    if (ahcRet != AHC_TRUE) { AHC_PRINT_RET_ERROR(0, 0); return ahcRet;}

    if (MenuSettingConfig()->uiMotionDtcSensitivity == MOTION_DTC_SENSITIVITY_OFF) {
        MenuSettingConfig()->uiMotionDtcSensitivity = MOTION_DTC_SENSITIVITY_LOW;
        Menu_SetMotionDtcSensitivity(MenuSettingConfig()->uiMotionDtcSensitivity);
    }

    #if (MOTION_DETECTION_EN)
    AHC_SetMotionDtcWinCfg(MDTC_WIN_W_DIV, MDTC_WIN_H_DIV);
    AHC_GetMotionDtcSensitivity(&u8MvTh, &u8CntTh);
    AHC_SetMotionDtcSensitivity(u8MvTh, u8CntTh);

    eRetErr = MMPS_Sensor_RegisterVMDCallback(MMPS_IVA_EVENT_MDTC, (void *)VRMotionDetectCB);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    AHC_EnableMotionDetection(AHC_TRUE);
    #endif

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeUnInitParkingMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeUnInitParkingMode(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;
    UINT8       u8YFrmType = MMPS_3GPRECD_Y_FRAME_TYPE_NONE;
    #if (SUPPORT_ADAS)
    UINT32      u32LDWS_En = COMMON_LDWS_EN_OFF;
    UINT32      u32FCWS_En = COMMON_FCWS_EN_OFF;
    UINT32      u32SAG_En  = COMMON_SAG_EN_OFF;
    UINT32      u32AdasFlag = 0;
    #endif

    #if (MOTION_DETECTION_EN)
    AHC_EnableMotionDetection(AHC_FALSE);
    #endif

    // Execute common uninit.
    ahcRet = AHC_VIDEO_SetRecordModeUnInitCommon();
    if (ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(0, 0); return ahcRet;}

    MMPS_3GPRECD_SetYFrameType(MMPS_3GPRECD_Y_FRAME_TYPE_NONE);

    AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_AUD_PRERECORD_DAC, AHC_TRUE);
#if (SUPPORT_ADAS)
    AHC_GetParam(PARAM_ID_ADAS, &u32AdasFlag);
#endif
#if (ENABLE_ADAS_LDWS)
    if (u32AdasFlag & AHC_ADAS_ENABLED_LDWS) {
        u32LDWS_En = COMMON_LDWS_EN_ON;
        MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_LDWS, MMP_TRUE);
    }
    else {
        MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_LDWS, MMP_FALSE);
    }
#endif
#if (ENABLE_ADAS_FCWS)
    if (u32AdasFlag & AHC_ADAS_ENABLED_FCWS) {
        u32FCWS_En = COMMON_FCWS_EN_ON;
        MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_FCWS, MMP_TRUE);
    }
    else {
        MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_FCWS, MMP_FALSE);
    }
#endif
#if (ENABLE_ADAS_SAG)
    if (u32AdasFlag & AHC_ADAS_ENABLED_SAG) {
        u32SAG_En = COMMON_SAG_EN_ON;
        MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_SAG, MMP_TRUE);
    }
    else {
        MMPS_Sensor_SetADASFeatureEn(MMPS_ADAS_SAG, MMP_FALSE);
    }
#endif

#if (SUPPORT_ADAS)
    if (u32LDWS_En == COMMON_LDWS_EN_ON ||
        u32FCWS_En == COMMON_FCWS_EN_ON ||
        u32SAG_En  == COMMON_SAG_EN_ON) {
        u8YFrmType = MMPS_3GPRECD_Y_FRAME_TYPE_ADAS;
    }
#endif

    // It must be set before enter Preview mode
    MMPS_3GPRECD_SetYFrameType(u8YFrmType);

#if (ENABLE_ADAS_LDWS || ENABLE_ADAS_FCWS || ENABLE_ADAS_SAG)

    #if (MOTION_DETECTION_EN)
    if (MMPS_Sensor_IsVMDEnable() == MMP_FALSE)
    #endif
    {
        if ((u32AdasFlag & AHC_ADAS_ENABLED_LDWS) ||
            (u32AdasFlag & AHC_ADAS_ENABLED_FCWS) ||
            (u32AdasFlag & AHC_ADAS_ENABLED_SAG )) {
            AHC_EnableADAS(AHC_TRUE);
        }
        else {
            AHC_EnableADAS(AHC_FALSE);
        }
    }
#endif

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeSetEmergencyParkingMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeSetEmergencyParkingMode(void)
{
    AHC_BOOL ahcRet = AHC_TRUE;
    MMP_ERR  eRetErr = MMP_ERR_NONE;

    #if ((UVC_HOST_VIDEO_ENABLE) && (UVC_EMERGRECD_SUPPORT) && (AHC_UVC_EMERGRECD_SUPPORT))
    eRetErr = MMPS_3GPRECD_EnableUVCEmergentRecd(MMP_FALSE);
    #endif
    #if (DUAL_EMERGRECD_SUPPORT) && (AHC_DUAL_EMERGRECD_SUPPORT)
    eRetErr = MMPS_3GPRECD_EnableDualEmergentRecd(MMP_FALSE);
    #endif
    #if (AHC_EMERGENTRECD_SUPPORT)
    eRetErr = MMPS_3GPRECD_EnableEmergentRecd(MMP_FALSE);
    #endif

    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk,eRetErr); return AHC_FALSE;}

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeSetAudioEncodeParkingMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeSetAudioEncodeParkingMode(void)
{
    UINT8       ubSoundEffectStatus = 0;
    AHC_BOOL    ahcRet = AHC_TRUE;

    AHC_GetSoundEffectStatus(&ubSoundEffectStatus);

    if (ubSoundEffectStatus == AHC_SOUND_EFFECT_STATUS_START) {
        MMPS_AUI_StopPlay();
    }

    AHC_VIDEO_SetMovieCfg(AHC_VIDEO_USAGE_RECD, AHC_AUD_PRERECORD_DAC, AHC_FALSE);

    ahcRet = AHC_VIDEO_SetRecordModeSetAudioEncode();
    if (ahcRet != AHC_TRUE){ AHC_PRINT_RET_ERROR(gbAhcDbgBrk, ahcRet); return ahcRet;}

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeSetTimeLimit
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeSetTimeLimitParkingMode(void)
{
    UINT32   u32TimeLimit = 0;
    AHC_BOOL ahcRet = AHC_TRUE;

    u32TimeLimit = AHC_VIDEO_GetRecTimeLimitParkingMode();
    AHC_VIDEO_SetRecTimeLimit(u32TimeLimit);

    AHC_DBG_MSG(1, "Parking TimeLimit [%d] ms\r\n", u32TimeLimit*1000);

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeSetBitRateParkingMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeSetBitRateParkingMode(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;
    MMP_ULONG   ulPrmBitRate = 0;
    MMP_ULONG   ulScdBitRate = 0;

    if (MMP_IsPrmCamExist()) {
        eRetErr = MMPS_3GPRECD_SetBitrate(MMPS_VR_PRM_RECD, AHC_VIDEO_MAXBITRATE_PRERECORD);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

        eRetErr = MMPS_3GPRECD_GetParameter(MMPS_VR_PRM_RECD, MMPS_3GPRECD_PARAMETER_BITRATE, &ulPrmBitRate);
        if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
    }

    if (MMP_IsScdCamExist()) {
        if (AHC_VIDEO_CheckScdRecdEnabled(CAM_TYPE_SCD, AHC_TRUE) & VID_RECD_ENCODE_H264) {
            eRetErr = MMPS_3GPRECD_SetBitrate(MMPS_VR_SCD_RECD, AHC_VIDEO_MAXBITRATE_PRERECORD_SCD);
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

            eRetErr = MMPS_3GPRECD_GetParameter(MMPS_VR_SCD_RECD, MMPS_3GPRECD_PARAMETER_BITRATE, &ulScdBitRate);
            if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}
        }
    }

    AHC_DBG_MSG(1, "Parking BitRate [%d][%d]\r\n", ulPrmBitRate, ulScdBitRate);

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeRegisterCallbackParkingMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeRegisterCallbackParkingMode(void)
{
    AHC_BOOL    ahcRet = AHC_TRUE;
    MMP_ERR     eRetErr = MMP_ERR_NONE;

    ahcRet = AHC_VIDEO_SetRecordModeRegisterCallback();

    eRetErr = MMPS_3GPRECD_RegisterCallback(VIDMGR_EVENT_PRM_RECD_FILE_FULL, (void*)VRFileFullCBParkingMode);
    if (eRetErr != MMP_ERR_NONE) { AHC_PRINT_RET_ERROR(gbAhcDbgBrk, eRetErr); return AHC_FALSE;}

    return ahcRet;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_SetRecordModeSetSeamlessParkingMode
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_SetRecordModeSetSeamlessParkingMode(void)
{
    AHC_VIDEO_SetVRSeamless(AHC_FALSE);

    return AHC_TRUE;
}

//------------------------------------------------------------------------------
//  Function    : AHC_VIDEO_ParkingModePostProcess
//  Description :
//------------------------------------------------------------------------------
AHC_BOOL AHC_VIDEO_ParkingModePostProcess(void)
{
    UINT16 u16CurVideoDirKey = 0;
    UINT8* pu8CurVideoFileName = NULL;
#if (AHC_MULTI_TRACK_EN == 0)
    UINT8 *pu8CurVideoRearFileName = NULL;
#endif

    u16CurVideoDirKey = AHC_VIDEO_GetCurRecDirKey();

    pu8CurVideoFileName = AHC_VIDEO_GetCurPrmRecdFileName(AHC_FALSE);

    #if (AHC_MULTI_TRACK_EN == 0)
    if (MMP_IsScdCamExist()) {
        pu8CurVideoRearFileName = AHC_VIDEO_GetCurScdRecdFileName(AHC_FALSE);
    }
    else if (MMP_IsUSBCamExist()) {
        pu8CurVideoRearFileName = AHC_VIDEO_GetCurUsbhRecdFileName(AHC_FALSE);
    }
    #endif

    #if(GPS_RAW_FILE_ENABLE == 1)
    GPSCtrl_SwitchRawFilePingPongBuffer();
    #endif

    AHC_UF_SelectDB(DCF_DB_TYPE_DB1_PARKING);

    if ((MMP_IsPrmCamExist()) && pu8CurVideoFileName[0] != 0) {
        AHC_UF_PostAddFile(u16CurVideoDirKey, (INT8*)pu8CurVideoFileName);
    }

    #if (AHC_MULTI_TRACK_EN == 0)
    if ((MMP_IsScdCamExist()) && (pu8CurVideoRearFileName[0] != 0)) {
        AHC_UF_PostAddFile(u16CurVideoDirKey, (INT8*)pu8CurVideoRearFileName);
    }
    else if ((MMP_IsUSBCamExist()) && (pu8CurVideoRearFileName[0] != 0)) {
        AHC_UF_PostAddFile(u16CurVideoDirKey, (INT8*)pu8CurVideoRearFileName);
    }
    #endif

    return AHC_TRUE;
}
