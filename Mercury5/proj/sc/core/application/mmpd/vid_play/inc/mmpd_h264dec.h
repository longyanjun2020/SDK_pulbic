#ifndef _MMPD_H264DEC_H_
#define _MMPD_H264DEC_H_

/**
 @brief mem config type
*/
typedef enum
{
    MMPD_H264_INFO_MEM,
    MMPD_H264_VIDEO_BUF_MEM,
    MMPD_H264_VIDEO_DECODE_MEM
} MMPD_MDTV_MEM_TYPE;

/**
 @brief the display infomation of video frame
*/
typedef struct
{
    MMP_ULONG   format;             ///< video format, such as H263, MPEG4, H264...etc
    MMP_ULONG   bitrate;            ///< video bitrate, in Kbps
    MMP_USHORT  width;              ///< video width
    MMP_USHORT  height;             ///< video height
    MMP_USHORT  fps;                ///< Frame per second, 0 means unknown
    MMP_USHORT	cropping_left;      ///< the distance between the left boundary and video frame
	MMP_USHORT	cropping_right;     ///< the distance between the right boundary and video frame
	MMP_USHORT	cropping_top;       ///< the distance between the top boundary and video frame
	MMP_USHORT	cropping_bottom;    ///< the distance between the bottom boundary and video frame
	MMP_LONG    total_video_time;   ///< the duration of the whole video stream
} MMPD_H264_INFO;

MMP_ERR MMPD_H264_ConfigMem(MMP_ULONG type,MMP_ULONG *addr, MMP_ULONG size, MMP_ULONG align);
MMP_ERR MMPD_H264_ConfigCodec(void);
MMP_ERR MMPD_H264_DecodeData(MMP_ULONG dest_addr,MMP_ULONG length);
MMP_ERR MMPD_H264_IsDecodeDone(MMP_ULONG *decode_done);
MMP_ERR MMPD_H264_GetVideoInfo(MMPD_H264_INFO *info);
MMP_ERR MMPD_H264_GetVideoFrameAddr(MMP_ULONG *addr);
MMP_ERR MMPD_H264_RefreshFrame(void);
MMP_ERR MMPD_H264DEC_SetBitstreamAddr(const MMP_ULONG ulVideoBSAddr, const MMP_ULONG ulVideoBSSize);
#endif