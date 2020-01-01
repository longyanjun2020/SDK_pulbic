#ifndef MMPF_AMRENCAPI_API
#define MMPF_AMRENCAPI_API

#define AMRENC_INBUF_FRAME_NUM  5
#define AMRENC_INBUF_SIZE       (160*AMRENC_INBUF_FRAME_NUM)//160*5
#define AMRENC_BUFFER_SIZE      (AMRENC_INBUF_SIZE << 1)

typedef struct {
    MMP_ULONG rd_cnt;
    MMP_ULONG wr_cnt;
    MMP_ULONG total_rd;
    MMP_ULONG total_wr;
}NR_BUF_HANDLE;

extern void	MMPF_EncodeAmrFrame(void);
extern void	MMPF_InitAMREncoder(void);
extern void MMPF_GetAMRRecParameter(MMP_ULONG *bitrate, MMP_ULONG *samplerate);
extern unsigned int MMPF_GetAMRRecFrameCntInSeconds(MMP_ULONG seconds);
#endif
