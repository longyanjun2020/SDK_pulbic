#ifndef _MMPF_USB_H264_H_
#define _MMPF_USB_H264_H_

#include "mmpf_typedef.h"

// 3.4.1.1 Encoder Video Format Control
#define UT_DEFAULT              (0x00)
#define UT_REAL_TIME_STREAMING  (0x01)
#define UT_REAL_TIME_STREAMING_INTEROP  (0x02)
#define UT_BROADCAST            (0x03)
#define UT_STORAGE              (0x04)

#define DUAL_STREAM_EN          (1<<0)
#define DUAL_MJPEG_H264         (1<<1)
#define DUAL_MJPEG_YUY2         (1<<2)

typedef struct __attribute__((packed)) _H264_ENCODER_VFC_CFG 
{
    MMP_USHORT wWidth ;
    MMP_USHORT wHeight;
    MMP_ULONG  dwFramePeriod;
    MMP_UBYTE  bUsageTarget ;
    MMP_UBYTE  bStreamMuxOption;
} H264_ENCODER_VFC_CFG ;

// 3.4.1.2 Encoder Configuration Control
// Slice Format
#define SF_NAL  (0x00) // NAL
#define SF_BYTE (0x01) // Byte Stream
// Profile
#define PROFILE_BASELINE    (66)
#define PROFILE_MAIN        (77)
#define PROFILE_HIGH        (100)
// Rate Control Mode
#define RCM_CBR (0) // CBR
#define RCM_VBR (1) // VBR

#define QM_USER_DEF (0 )
#define QM_LIMIT    (51)

typedef struct __attribute__((packed)) _H264_ENCODER_CC_CFG 
{
    MMP_ULONG   dwBitRate ;
    MMP_ULONG   dwBitRateMax;
    MMP_ULONG   dwRateControlDelay ;
    MMP_USHORT  wIDRFrequency ;
    MMP_USHORT  wAirrate ;
    MMP_USHORT  wSliceSize ;
    MMP_USHORT  wSliceMode ;
    MMP_UBYTE   bSliceFormat;
    MMP_UBYTE   bProfile ;
    MMP_UBYTE   bRateControlMode ;
    MMP_UBYTE   bQuantizerMin;
    MMP_UBYTE   bQuantizerMax;    
} H264_ENCODER_CC_CFG ;


// 3.4.1.3 Rate Control
typedef struct __attribute__((packed)) _H264_ENCODER_RC_CFG 
{
    MMP_ULONG   dwFramePeriod ;
    MMP_ULONG   dwBitRate ;
} H264_ENCODER_RC_CFG ;
// 3.4.1.4 Frame Type Control

#define FT_IVIDEO_NA_FRAME  (0)
#define FT_IVIDEO_I_FRAME   (1)
#define FT_IVIDEO_IDR_FRAME (2)
// 3.4.1.5 Camera Delay Control

// 3.4.1.6 Filter Control
typedef struct __attribute__((packed)) _H264_ENCODER_FILTER_CFG 
{
    MMP_UBYTE   bTemporalFilterStrength ;
    MMP_UBYTE   bSpatialFilterStrength ; 
} H264_ENCODER_FILTER_CFG ;

// 3.5.1 Payload header, 28 bytes for current implementation.
#define ST_UNDEF    (0 )
#define ST_YUY2     (41)
#define ST_NV12     (42)
#define ST_H264     (43)
#define ST_MJPEG    (44) // not in spec.
#define ST_MD		(56) // AIT motion detection type

// 32 bytes
typedef union __attribute__((packed)) _FRAME_PAYLOAD_HEADER 
{
    struct __attribute__((packed)) _UVC_H264_PH
    {
        MMP_USHORT wVersion;
        MMP_USHORT wHeaderLen;
        MMP_USHORT wStreamType; // 41,42,43,44
        MMP_USHORT wImageWidth;
        MMP_USHORT wImageHeight;
        MMP_USHORT wFrameRate;
        /*------Vendor info------*/
        MMP_ULONG  dwFrameSeq;
        MMP_ULONG  dwTimeStamp;
        MMP_ULONG  dwFlag;
        MMP_ULONG  dwReserved; 
        /*------Vendor Info-------*/
        MMP_ULONG  dwPayloadSize;
    } UVC_H264_PH;
    
    struct __attribute__((packed)) _SKYPE_H264_PH
    {
        MMP_ULONG  dwFrameSizeWithId;
        MMP_ULONG  dwFrameSeq;
        MMP_ULONG  dwFlag;
        MMP_ULONG  dwPayloadOffset;
        MMP_ULONG  dwTimeStamp;
        /*------Vendor info------*/
        MMP_USHORT wStreamType;
        MMP_USHORT wImageWidth;
        MMP_USHORT wImageHeight;
        MMP_USHORT wFrameRate;
        /*------Vendor info------*/
        MMP_ULONG  dwPayloadSize;
    } SKYPE_H264_PH;
    
} FRAME_PAYLOAD_HEADER ;

#define SKYPE_PAYLOAD_ID    0x000000EE
#define UVC_H264_VER        0x0090 // 0.9F
#define FRAME_PAYLOAD_HEADER_SZ  sizeof(FRAME_PAYLOAD_HEADER)
#define UVC_H264_PH_LEN (FRAME_PAYLOAD_HEADER_SZ - 4)

#endif //_MMPF_USB_H264_H_
