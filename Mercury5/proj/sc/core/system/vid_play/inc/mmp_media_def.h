/**
 @file mmp_media_def.h
 @brief Definition of media template
 @author SW.Yang
 @author Truman Yang
 @version 1.0 Original Version
*/
#ifndef _MMP_MEDIA_DEF_H_
#define _MMP_MEDIA_DEF_H_

#include "mmpf_typedef.h"

/** @name IPC
Inter Process Communication section. 
All definition and declaration here are used for host MMP inter process communication.
This section should be sync with the host.
@{
*/

// stream callback type
typedef enum _MMP_M_STREAMCB_ACTION {
    MMP_STREAM_VIDMOVE = 0,    // move video stream
    MMP_STREAM_VIDUPDATE,      // update video stream
    MMP_STREAM_AUDMOVE,        // move audio stream
    MMP_STREAM_AUDUPDATE,      // update audio stream
    MMP_STREAM_PUMP,           // pump the stream pipeline again
    MMP_STREAM_ACTION_MAX
} MMP_M_STREAMCB_ACTION;

typedef enum _MMP_M_STREAMCB_CODEC {
    MMP_STREAM_JPEG = 0,
    MMP_STREAM_H264,
    MMP_STREAM_CODEC_AUDIO,
    MMP_STREAM_JPEG2,
    MMP_STREAM_CODEC_MAX
}MMP_M_STREAMCB_CODEC;

// Make sure this sync with VIDENC_FRAME_TYPE
typedef enum _MMP_M_FRAME_TYPE {
    MMP_FRAME_TYPE_I = 0,
    MMP_FRAME_TYPE_P,
    MMP_FRAME_TYPE_B,
    MMP_FRAME_TYPE_MAX
} MMP_M_FRAME_TYPE;

typedef enum _MMP_M_AUD_CODEC {
    AUD_CODEC_NONE = 0,
    AUD_CODEC_AACP,
    AUD_CODEC_MP4A,
    AUD_CODEC_AMR,
    AUD_CODEC_MP3_1,
    AUD_CODEC_MP3_2,       //05
    AUD_CODEC_AC3,
    AUD_CODEC_PCM_1,
    AUD_CODEC_PCM_2,
    AUD_CODEC_PCM_ALAW,
    AUD_CODEC_PCM_ULAW,    //10
    AUD_CODEC_PCM_IMA_QT,
    AUD_CODEC_PCM_IMA_WAV,
    AUD_CODEC_MAX,         //13
}MMP_M_AUD_CODEC;

// stream callback buffer info
typedef struct _MMP_M_STREAM_INFO {
    MMP_ULONG  				baseaddr;   // Ring Buffer Base Address
    MMP_ULONG  				segsize;
    MMP_ULONG  				startaddr;  // Buffer Write Pointer
    MMP_ULONG 		 		availsize;  // Buffer Free Space for Write
    MMP_M_STREAMCB_CODEC 	codec;
    MMP_M_FRAME_TYPE 		frametype;
    MMP_ULONG  				timestamp;
    void*                   dbg;
} MMP_M_STREAM_INFO;
	
typedef struct MMP_M_VIDEO MMP_M_VIDEO, *MMP_M_VIDEO_HANDLE;
	
/** @} */ // end of IPC

#define MAKE_TAG(a,b,c,d)       (a | (b << 8) | (c << 16) | (d << 24 ))
#define MAKE_TAG_BE(a,b,c,d)    (d | (c << 8) | (b << 16) | (a << 24 ))

/* video codec */
#define CODEC_MJPG    		MAKE_TAG_BE('m','j','p','g') ///< MJPEG Video atom name in AVI
#define CODEC_MJPA          MAKE_TAG_BE('m','j','p','a') ///< MJPEG Video atom name in AVI
#define CODEC_MP4V    		MAKE_TAG_BE('m','p','4','v') ///< MPEG4 Video atom name in 3GP
#define CODEC_S263    		MAKE_TAG_BE('s','2','6','3') ///< S.263 atom name in 3GP
#define CODEC_H263    		MAKE_TAG_BE('h','2','6','3') ///< H.263 atom name in 3GP
#define CODEC_H264    		MAKE_TAG_BE('a','v','c','1') ///< H.264 / AVC
#define CODEC_WMVP    		MAKE_TAG_BE('w','m','v','p')
#define CODEC_RV      		MAKE_TAG_BE('.','R','M','F')  ///< Real Media

/* audio codec */
#define CODEC_AACP    		MAKE_TAG_BE('a','a','c','p')
#define CODEC_MP4A    		MAKE_TAG_BE('m','p','4','a') ///< AAC-LC atom name in 3GP
#define CODEC_AMR    	 	MAKE_TAG_BE('s','a','m','r') ///< AMR-NB atom name in 3GP
#define CODEC_MP3_1   		MAKE_TAG_BE('.','m','p','3')
#define CODEC_MP3_2   		0x6D730055
#define CODEC_AC3     		MAKE_TAG_BE('a','c','-','3')
#define CODEC_PCM_1   		MAKE_TAG_BE('s','o','w','t')
#define CODEC_PCM_2   		MAKE_TAG_BE('l','p','c','m')
#define CODEC_PCM_ALAW  	MAKE_TAG_BE('a','l','a','w')
#define CODEC_PCM_ULAW  	MAKE_TAG_BE('u','l','a','w')
#define CODEC_PCM_IMA_QT   	MAKE_TAG_BE('i','m','a','4')
#define CODEC_PCM_IMA_WAV   0x6D730011

#define FLUSH_DECODER_FRAME_BUFFER  (0x00000001)

#endif
