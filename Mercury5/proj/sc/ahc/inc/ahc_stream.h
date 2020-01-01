/*
 * AHC_Streaming.h
 */
#ifndef _AHC_STREAM_H_
#define _AHC_STREAM_H_

#if (defined(WIFI_PORT) && WIFI_PORT == 1)

#include "ahc_os.h"
#include "ahc_video.h"

#ifndef _MMP_MEDIA_DEF_H_
#include "mmp_media_def.h"
#endif

#define AHC_SMODE_is_streaming(uiSMode)  (uiSMode != AHC_STREAM_OFF)

typedef struct _AHC_VIDEO_2ND_CONFIG        // Move from ahc_stream.h
{
    AHC_VIDEO_FORMAT    vFormat;
    UINT16              FPS;    //As 2nd video, The FPS here now is for rate control only. The main FPS still depends on VIF.
                                //Typically usage. The sensor set to 1080P@30 or 720P@60.
                                //This field have to set to 30 or 60 accordingly. See Bitrate for further info.
    UINT32              FpsOutx1000;

    union {
        struct {
            AHC_VIDRECD_RESOL ahcRes; //Resolution is not supported in YUV now
            UINT32 Bitrate;//Note that it depends on FPS field to make this working right.
                           //If the streamer skipping is used, this field must set according to the ratio of skipping.
                           //For example, now the sensor is @30FPS.
                           //             the remote end wants to get 2Mbps,30FPS MJPEG bitstream.
                           //
                           //The settings should be:
                           //Set FPS field here and MJPEG source node input FPS must set to 30.
                           //Set 10 FPS as output of MJPEG source node.
                           //Set bitrate here to 6Mbps.
                           //
                           //Then, the image flow would be like this as intention:
                           //Sensor@30FPS -> (MJPEG_HW @ 6Mbps,30FPS) -> (Streamer source @ 2Mbps, 10FPS)
        } mj;
        struct {
            UINT16 mmpRes;
            UINT32 Bitrate;
            UINT16 cropR;
            UINT16 cropB;
        } h264;
        struct {
            UINT16 dummy;  //No further info could be set
        } yuv;
    } param;
} AHC_VIDEO_2ND_CONFIG;

typedef enum _AHC_STREAMING_MODE {
    // Streaming mode operation
    AHC_STREAM_OFF                  = 0x00000000,
    AHC_STREAM_PAUSE                = 0x00000008,
    AHC_STREAM_RESUME               = 0x00000080,
    // Stream configuration
    AHC_STREAM_TRANSCODE            = 0x00000004,
    AHC_STREAM_NONE                 = AHC_STREAM_OFF,
    AHC_STREAM_MJPEG                = 0x00000001,
    AHC_STREAM_H264                 = 0x00000002,
    AHC_STREAM_V_MAX                = 0x00000003,
    AHC_STREAM_V_MASK1              = 0x00000003,
    AHC_STREAM_PCM                  = 0x00000010,
    AHC_STREAM_MP3                  = 0x00000020,
    AHC_STREAM_AAC                  = 0x00000030,
    AHC_STREAM_G711                 = 0x00000040,
    AHC_STREAM_ADPCM                = 0x00000050,
    AHC_STREAM_A_MAX                = 0x00000050,
    AHC_STREAM_A_MASK               = 0x00000070,
    AHC_STREAM_MJPEG2               = 0x00000100,
    AHC_STREAM_V_MASK2              = 0x00000100,
    AHC_STREAM_V_MASK               = AHC_STREAM_V_MASK1 | AHC_STREAM_V_MASK2,
    // Extention for streaming operation
    AHC_STREAM_KEEP_TIMER_ALIVE     = 0x01000000,
    AHC_STREAM_EX_OP_MASK           = 0x7f000000
}AHC_STREAMING_MODE;

extern AHC_OS_SEMID m_AhcModeSemID;
#define LOCK_AHC_MODE_NOWAIT()  AHC_OS_AcquireSem(m_AhcModeSemID, 1)
#define LOCK_AHC_MODE()         AHC_OS_AcquireSem(m_AhcModeSemID, 0)
#define UNLOCK_AHC_MODE()       AHC_OS_ReleaseSem(m_AhcModeSemID)
#define AHC_SetStreamingMode(StreamingMode) \
                        _AHC_SetStreamingMode(StreamingMode, AHC_TRUE,  __FILE__, __LINE__)
#define AHC_SetStreamingModeNoWait(StreamingMode) \
                        _AHC_SetStreamingMode(StreamingMode, AHC_FALSE, __FILE__, __LINE__)


AHC_BOOL _AHC_SetStreamingMode(AHC_STREAMING_MODE streamingMode, AHC_BOOL bWait, char * str, int line);
AHC_BOOL AHC_IsRecorderControllable(AHC_MODE_ID ahcMode);
AHC_STREAMING_MODE AHC_GetStreamingMode(void);
AHC_BOOL AHC_IsMJPEGStreaming(void);
typedef UINT16 AHC_MEDIA_USAGE;

// Definition of AHC_MEDIA_USAGE. bit 0 is for switching the media on or off.
// bit 1 ~ 7 is for bit mapped configuration
// @warning Be careful about the condition check, 0x40 still means this media is disabled.
#define AHC_MEDIA_DISABLE    ((AHC_MEDIA_USAGE)0x00)  // General disabling
#define AHC_MEDIA_ENABLE     ((AHC_MEDIA_USAGE)0x01)  // General enabling
#define AHC_MEDIA_STREAMING  ((AHC_MEDIA_USAGE)0x10)  // Output to network

typedef enum _AHC_MOVIE_STREAMING_MODE
{
    AHC_STREAMING_OFF,
    AHC_STREAMING_ON,
    AHC_STREAMING_TRANSCODE,
    AHC_STREAMING_MAX
} AHC_MOVIE_STREAMING_MODE;

typedef enum _AHC_STREAM_ID
{
    AHC_STREAM_FRONT = 0,
    AHC_STREAM_REAR_VIF,
    AHC_STREAM_REAR_USBH,
    AHC_STREAM_MAX
} AHC_STREAM_ID;

void        AHC_StreamingTimer_Start(void);
void        AHC_StreamingTimer_Stop(void);
void        AHC_StreamingTimer_SetMs(MMP_ULONG ulMs);
MMP_ULONG   AHC_StreamingTimer_GetMs(void);
AHC_BOOL    AIHC_CalH264EncResolution(UINT16 *encW, UINT16 *encH, UINT16 *cropBottom, UINT16 *cropRight, UINT16 *mmpResIdx);
INT32       AIHC_OpenTranscode(void);
AHC_BOOL    VideoRecordStreamCallback(MMP_M_STREAMCB_ACTION cb_action, MMP_ULONG framesize, MMP_M_STREAM_INFO* moveinfo);
AHC_BOOL    AHC_ChangeH264StreamRes(UINT16 VidResIdx);

INT32       AIHC_CloseTranscode(void);
AHC_BOOL    AIHC_Video_MapResToIdx(UINT16 w, UINT16 h, UINT16 *ResIdx, UINT16 *cropBottom, UINT16 *cropRight);
void        AHC_AdjustMJpegStreamResFromSnr(UINT16 w, UINT16 h, UINT16* suggestedWidth, UINT16* suggestedHeight);
AHC_BOOL    AHC_GetMJpegStreamResolution(UINT16 stream, UINT16 *w, UINT16 *h);

#else   // WIFI_PORT

#define AHC_GetStreamingMode()  (AHC_STREAM_OFF)
#define AHC_SetStreamingMode(m) (AHC_FALSE)
#define LOCK_AHC_MODE()
#define UNLOCK_AHC_MODE()

#endif  // WIFI_PORT

#endif // _AHC_STREAM_H_
