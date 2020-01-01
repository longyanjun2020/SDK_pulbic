#ifndef _MDL_VT_MEDIA_ITF_H_
#define _MDL_VT_MEDIA_ITF_H_

typedef enum{
    VT_MEDIA_ADUIO_AMRNB = 1,
    VT_MEDIA_ADUIO_AMRWB,
} vt_media_audio_t;

typedef enum{
    VT_MEDIA_VIDEO_H263 = 1,
    VT_MEDIA_VIDEO_M4V,
    VT_MEDIA_VIDEO_H264,
} vt_media_video_t;

typedef enum{
    VT_MEDIA_AUDIO = 1,
    VT_MEDIA_VIDEO,
    VT_MEDIA_EOS,
    VT_MEDIA_INIT_DATA,
} vt_media_data_t;


typedef struct {
    u32 skew;
    u32 vid_framerate;
    vt_media_video_t vid_codec;
    u32 aud_sample_rate;
    u32 aud_ch_num;
    vt_media_audio_t aud_codec;
} vt_media_info_t;


int MdlVtMedia_GetRemoteMediaInfo(vt_media_info_t *info);
int MdlVtMedia_SetRemoteMediaInfo(vt_media_info_t *info);
void MdlVtMedia_SetIncomingDump(int enable);
void MdlVtMedia_SetOutgoingDump(int enable);
void MdlVtMedia_Init(void);
void MdlVtMedia_Finalize(void);
int MdlVtMedia_PutInitData(void);

void MdlVtMedia_PutEosData(void);
int MdlVtMedia_GetData(u32 *buf, u32 *size, u32 *type);
int MdlVtMedia_PutData(u8 *Buf, u32 Size, u32 Type, int SeqNum);



#endif
