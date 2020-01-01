#ifndef _MMPF_USBPCCAM_H_
#define _MMPF_USBPCCAM_H_

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define USB_PCAM_DBG_MSG(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)
#define USB_PCAM_DBG_ERR(enable, format, args...) do{if (enable) UartSendTrace(format, ##args);}while(0)

#define PIPE0_EN            (1<<0)
#define PIPE1_EN            (1<<1)
#define PIPE_EN_MASK        (0x3)
#define PIPE_EN_SYNC        (1<<2)

#define PIPE_CFG_YUY2       (1<<0)
#define PIPE_CFG_MJPEG      (1<<1)
#define PIPE_CFG_H264       (1<<2)
#define PIPE_CFG_NV12       (1<<3)
#define PIPE_CFG_MASK       (0x7)

#define PIPE_CFG(pipe, cfg) ((cfg & PIPE_CFG_MASK) << (pipe << 2))

#define PIPE_PH_TYPE_NA     (0)
#define PIPE_PH_TYPE_1      (1)
#define PIPE_PH_TYPE_2      (2)

#if 1
#define VIDEO_MJPEG_SID         (3) //MJPEG(sid=0x20)
#else	//zk for this case change ID
#define VIDEO_MJPEG_SID         (1) //MJPEG(sid=0x20)
#endif 
#define VIDEO_GRAY_SID          (4) //GRAY(sid=0x40)
#define VIDEO_STILL_IMAGE_SID   (0x0100)
#define VIDEO_MJPEG_MODE        (0) //MJPEG(viewmode=0)
#define VIDEO_GRAY_MODE         (1) //GRAY(viewmode=2)
#define MAX_NUM_VIDEO_MODE      (2) //MJPEG+GRAY

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _H264_FORMAT_TYPE {
    INVALID_H264 = 0,
    FRAMEBASE_H264,
    UVC_H264,
    SKYPE_H264
} H264_FORMAT_TYPE;

typedef enum _PCAM_RESOL_ID {
    PCCAM_640_360 = 0,
    PCCAM_640_480,
    PCCAM_720_480,
    PCCAM_800_600,
    PCCAM_848_480,
    PCCAM_960_720,
    PCCAM_1024_576,
    PCCAM_1024_600,
    PCCAM_1024_768,
    PCCAM_1280_720,
    PCCAM_1280_960,
    PCCAM_1600_1200,
    PCCAM_1920_1080,
    PCCAM_2048_1536,
    PCCAM_2176_1224,
    PCCAM_2560_1440,
    PCCAM_2560_1920,
    PCCAM_RES_NUM
} PCAM_RESOL_ID;

//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

#if (ISP_IQ_SERVER)
typedef struct _PCAM_IQSVR_HANDLE
{
    MMP_USHORT      usCmdType;
        #define IQ_XU_CMD_NONE      0
        #define IQ_XU_CMD_SETAPI    1
        #define IQ_XU_CMD_GETAPI    2
    MMP_USHORT      usCmdLen;
    MMP_USHORT      usDataLen;
    MMP_USHORT      usCmdBufCurPos;
    MMP_USHORT      usDataBufCurPos;
    MMP_UBYTE       ubCmdHandling;
    MMP_UBYTE       ubCmdWaitAck;
    MMP_UBYTE       *pubCmdBuf;
        #define IQ_XU_CMDBUF_LEN   40960   // 40KB
    MMP_UBYTE       *pubDataBuf;
        #define IQ_XU_DATABUF_LEN  40960   // 40KB
} PCAM_IQSVR_HANDLE;
#endif

typedef struct _STREAM_BUF_CTL
{
    MMP_ULONG       rd_index;   // Buffer Read Pointer (0 ~ slot_size*slot_num-1)
    MMP_ULONG       wr_index;   // Buffer Write Pointer (0 ~ slot_size*slot_num-1)
    MMP_ULONG       total_rd;   // Total Read Buffer Count
    MMP_ULONG       total_wr;   // Total Write Buffer Count
    MMP_ULONG       buf_addr;
    MMP_ULONG       slot_size;
    MMP_USHORT      slot_num;
} STREAM_BUF_CTL;

typedef struct _STREAM_CFG
{
    MMP_UBYTE       ubPipeEn;
    MMP_UBYTE       ubPipeCfg;
    MMP_USHORT      usPipe0Width;
    MMP_USHORT      usPipe0Height;
    MMP_USHORT      usPipe1Width;
    MMP_USHORT      usPipe1Height;
    STREAM_BUF_CTL  stPipe0Buf;
    STREAM_BUF_CTL  stPipe1Buf;
} STREAM_CFG;

typedef struct _RES_TYPE_CFG
{
    PCAM_RESOL_ID   eResId;
    MMP_USHORT      usResW;
    MMP_USHORT      usResH;
} RES_TYPE_CFG;

typedef struct _STREAM_DMA_BLK
{
    MMP_USHORT      max_dsize;
    MMP_USHORT      header_len;
    MMP_ULONG       blk_addr;
    MMP_ULONG       blk_size;
    MMP_ULONG       next_blk;
    MMP_ULONG       cur_addr;
    MMP_ULONG       tx_len;
    MMP_ULONG       tx_packets;
    MMP_ULONG       dma_buf[2];
    MMP_ULONG       dummy_flag;
} STREAM_DMA_BLK;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMP_ULONG _MMPF_PCAM_GetYUY2FrameSize(MMP_UBYTE ubResIdx);
MMP_ULONG _MMPF_PCAM_GetMJPEGFrameSize(MMP_UBYTE ubResIdx);
MMP_ULONG _MMPF_PCAM_GetYUV420FrameSize(MMP_UBYTE ubResIdx);
MMP_ULONG _MMPF_PCAM_GetH264FrameSize(MMP_UBYTE ubResIdx);
MMP_USHORT _MMPF_PCAM_GetMaxFrameRate(MMP_UBYTE ubResIdx) ;

void MMPF_PCAM_InitStreamSetting(STREAM_CFG *pstStreamCfg, MMP_USHORT usStreamW, MMP_USHORT usStreamH);
STREAM_CFG *MMPF_PCAM_GetCurStreamCfg(void);
void MMPF_PCAM_SetCurStreamCfg(STREAM_CFG *pstStreamCfg);
MMP_USHORT MMPF_PCAM_GetJfifTag(MMP_USHORT *pTagID, MMP_USHORT *pTagLength, MMP_UBYTE **ppImgAddr, MMP_ULONG ulLength);

STREAM_BUF_CTL *MMPF_PCAM_GetStreamBufInfo(MMP_UBYTE ubPipeId);
MMP_BOOL MMPF_PCAM_IsStreamBufEmpty(MMP_UBYTE ubPipeId);
MMP_BOOL MMPF_PCAM_IsStreamBufFull(MMP_UBYTE ubPipeId);
MMP_UBYTE MMPF_PCAM_GetFreeSlotCnt(MMP_UBYTE ubPipeId);
void MMPF_PCAM_UpdateSlotWrPtr(MMP_UBYTE ubPipeId);
void MMPF_PCAM_UpdateSlotRdPtr(MMP_UBYTE ubPipeId);
MMP_UBYTE *MMPF_PCAM_GetCurSlotRdAddr(MMP_UBYTE ubPipeId);
MMP_UBYTE *MMPF_PCAM_GetCurSlotWrAddr(MMP_UBYTE ubPipeId);
void MMPF_PCAM_InitSlotBuf(void);
void MMPF_PCAM_UpdateSlotRdPtrByPayloadLeng(void);

void MMPF_Video_InitDMABlk(MMP_USHORT uvc_payload_size,MMP_ULONG dmabuf1,MMP_ULONG dmabuf2) ;
void MMPF_Video_AddDMABlk(MMP_ULONG header_len,MMP_ULONG blk_addr,MMP_ULONG blk_size,MMP_USHORT dummy_flag);
STREAM_DMA_BLK *MMPF_Video_CurBlk(void);
MMP_BOOL MMPF_Video_NextBlk(void);
MMP_UBYTE *MMPF_Video_GetBlkApp3Header(STREAM_DMA_BLK *dma_blk);

void MMPF_USBUVC_ReleaseDm(void);

#if (ISP_IQ_SERVER)
void pcam_usb_iqsvr_open(void);
void pcam_usb_iqsvr_close(void);
PCAM_IQSVR_HANDLE *pcam_usb_get_iqsvr_handle(void);
#endif

#endif //_MMPF_USBPCCAM_H_
