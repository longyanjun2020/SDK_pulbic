#ifndef MMPF_AMRDECAPI_API
#define MMPF_AMRDECAPI_API

#define AMR_DEC_OUTBUF_COUNT  	    5
#define AMR_DEC_MONO_OUTFRAMESIZE	160
#define AMR_DEC_STEREO_OUTFRAMESIZE	320
#define AMR_TIME_BUFFER_NUM         (AMR_DEC_OUTBUF_COUNT+2)
#if (AUDIO_MIXER_EN == 1)
#define AMRDEC_BUFFER_SIZE          ((AMR_DEC_MONO_OUTFRAMESIZE << 1) + \
                                    ((AMR_DEC_STEREO_OUTFRAMESIZE * AMR_DEC_OUTBUF_COUNT) << 1))
#else
#define AMRDEC_BUFFER_SIZE          ((AMR_DEC_MONO_OUTFRAMESIZE * AMR_DEC_OUTBUF_COUNT) << 1)
#endif

#define PROCESS_AMR_HEADER 1
#ifndef SIZEOF_AUDIO_HEADER
    #define SIZEOF_AUDIO_HEADER 12
#endif



typedef struct {
    unsigned short rd_index;
    unsigned short wr_index;
    unsigned short int_cnt;
    unsigned short frame_int_cnt[AMR_TIME_BUFFER_NUM];
    unsigned short current_frame_int_cnt;
    unsigned short small_frame_cnt;
    short           frame_size;
    unsigned int current_time;
    unsigned int time_scale;
    unsigned int dummy_wr_cnt;
    unsigned int dummy_rd_cnt;
    unsigned int sample_cnt;
    unsigned int time[AMR_TIME_BUFFER_NUM];
    unsigned int SRCRate;
}AMR_TIME_HANDLE;

extern unsigned short MMPF_GetAMRFileinfo(void);
extern unsigned int MMPF_GetAMRDecFramesInByte(void);
extern void MMPF_ResumeAMRDec(MMP_ULONG id);
extern void MMPF_PauseAMRDec(MMP_ULONG id);
extern void MMPF_StopAMRDec(MMP_ULONG id);
extern void MMPF_StartAMRDec(MMP_ULONG id);
extern MMP_ERR MMPF_PreDecAMRFrame(MMP_ULONG id);
extern void MMPF_DecodeAmrFrame(MMP_ULONG id, int decoder);
extern MMP_ULONG MMPF_GetAMRPlayTime(void);

#endif
