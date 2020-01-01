/// @ait_only
//==============================================================================
//
//  File        : mmpf_mts.h
//  Description : Header mpeg transport stream
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_MTS_H_
#define _MMPF_MTS_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmpf_3gpmgr.h"

/** @addtogroup MMPF_MTS
 *  @{
*/

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define MTS_INSERT_PCR_EN               (1)

#define MMPF_MTS_MAX_PAYLOAD_SIZE       (64)            ///< for pat/pmt/pes
#define MMPF_MTS_MAX_HEADER_SIZE        (8)             ///< for ts level header
#define MMPF_MTS_PAT_MAX_PROG_NUM       (2)             ///< program num
#define MMPF_MTS_PMT_MAX_ES_NUM         (2)             ///< elementary streams: audio/video

#define MTS_TS_PACKET_SIZE              (188)

#define MTS_TS_SYNC_BYTE                (0x47)

#define MTS_TRANSPORT_STREAM_ID         (0x01)

#define MTS_PID_PAT                     (0x0000)
#define MTS_PID_NIT                     (0x001F)
#define MTS_PID_PMT                     (0x0100)
#define MTS_PID_ES_VIDEO_0              (0x1011)
#define MTS_PID_ES_AUDIO_0              (0x1100)
#define MTS_PID_PCR_0                   (0x1011)//(0x1001)

#define MTS_PID_PCR_STUFF               (0x1000)

#define MTS_PID_FILEINFO                (0x0008)
#define MTS_PID_VR_THUMBNAIL            (0x0009)
#define MTS_PID_VID_I_INFO              (0x0007)
#define MTS_PID_AUD_INFO                (0x000A)
#define MTS_PID_DUMMY                   (0x000F)
#define MTS_PID_PCR_PROT                (0x0040)
#define MTS_PID_SDT                     (0x0011)

#define MTS_PES_STREAM_ID_PCM           (0xBD)
#define MTS_PES_STREAM_ID_AAC           (0xC0)
#define MTS_PES_STREAM_ID_H264          (0xE0)

#define TS_PCR_PAYLOAD_OFFSET           (6)         //pcr field offset in TS header
#define PES_PTS_AUDIO_LENS_PAYLOAD_OFFSET      (4)  //pts offset in MtsPesPayload
#define PES_SID_PAYLOAD_OFFSET          (3)         //stream ID offset in MtsPesPayload
#define PES_PTS_PAYLOAD_OFFSET          (13)//9     //pts offset in MtsPesPayload
#define PES_DTS_PAYLOAD_OFFSET          (18)//14    //dts offset in MtsPesPayload

#define VID_MTS_I_FRM_CNT               (1300)
#define VID_MTS_AUD_FRM_CNT             (10000)

#define ADD_FLIE_INFO_PKT               (1)
#define ADD_VR_THUMBNAIL_PKT            (1)
#define MTS_VR_THUMBNAIL_SIZE           (64*1024) //unit: bytes
#define ADD_VID_I_FRM_INFO              (0)
#define ADD_AUD_FRM_INFO                (0)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum _MMPF_MTS_PSI_TABLE {
    MMPF_MTS_PSI_TABLE_PAT      = 0x00,
    MMPF_MTS_PSI_TABLE_PMT      = 0x02
} MMPF_MTS_PSI_TABLE;

typedef enum _MMPF_MTS_STREAM_TYPE {
    MMPF_MTS_STREAM_TYPE_H264   = 0x1B,
    MMPF_MTS_STREAM_TYPE_AAC    = 0x0F,
    MMPF_MTS_STREAM_TYPE_PCM    = 0x80
} MMPF_MTS_STREAM_TYPE;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

//H264 stream_type = 0x1B
//MPEG-2 stream_type = 0x02;
//H264 stream_id = MPEG-2 = 0xE0

typedef struct _MMPF_MTS_TS {
    MMP_USHORT  usPID;
    MMP_UBYTE   bPayloadUnitStart;
    MMP_UBYTE   ubContinuity;
    MMP_BOOL    bAdaptationCtl;
    MMP_BOOL    bHeaderSection;         ///< Header tables: PAT/PMT 1 more extra byte
    MMP_BOOL    bPcrFlag;
} MMPF_MTS_TS;

typedef struct _MMPF_MTS_PAT {
    MMP_UBYTE   ubNumProgram;
    MMP_USHORT  usProgramNum[MMPF_MTS_PAT_MAX_PROG_NUM];
    MMP_USHORT  usPmtPid[MMPF_MTS_PAT_MAX_PROG_NUM];
} MMPF_MTS_PAT;

typedef struct _MMPF_MTS_PMT {
    MMP_USHORT  usPCRPid;
    MMP_USHORT  usProgramInfoLen;
    void        *pProgramInfo;
    MMP_UBYTE   ubNumEs;
    MMP_UBYTE   ubStreamType[MMPF_MTS_PMT_MAX_ES_NUM];
    MMP_USHORT  usEsPid[MMPF_MTS_PMT_MAX_ES_NUM];
    MMP_USHORT  usEsInfoLen[MMPF_MTS_PMT_MAX_ES_NUM];
    void        *pEsInfo[MMPF_MTS_PMT_MAX_ES_NUM];
} MMPF_MTS_PMT;

typedef struct _MMPF_MTS_PSI {
    MMPF_MTS_PSI_TABLE  TableID;
    MMP_UBYTE   ubVersionNum;
    MMP_UBYTE   ubSectionNum;
    MMP_UBYTE   ubLastSectionNum;
    MMP_USHORT  usIdNum;    //program num, ts id
    union {
        MMPF_MTS_PAT    Pat;
        MMPF_MTS_PMT    Pmt;
        void            *PrivData;
    } Tab;
} MMPF_MTS_PSI;

typedef struct _MMPF_MTS_TIME_INFO {
    MMP_UBYTE   ubTimeMsb32;
    MMP_ULONG   ulTime;
    MMP_ULONG   ulTimeDelta;
    MMP_ULONG   ulTimeDecimal;
    MMP_ULONG   ulTimeDecimalDelta;
} MMPF_MTS_TIME_INFO;

typedef struct _MMPF_MTS_PAYLOAD {
    MMP_UBYTE   ubPatData[MMPF_MTS_MAX_PAYLOAD_SIZE];
    MMP_UBYTE   ubPmtData[MMPF_MTS_MAX_PAYLOAD_SIZE];
    MMP_UBYTE   ubPesVidHeader[1][MMPF_MTS_MAX_PAYLOAD_SIZE];
    MMP_UBYTE   ubPesAudHeader[1][MMPF_MTS_MAX_PAYLOAD_SIZE];
    MMP_UBYTE   ubTsHeader[MMPF_MTS_MAX_HEADER_SIZE];
} MMPF_MTS_PAYLOAD;

typedef struct _MMPF_VIDMGR_MTS_PAYLOAD {
    MMP_USHORT          usPesHeaderLen;
    MMP_USHORT          usTsHeaderLen;
    MMP_UBYTE           PesHeader[MMPF_MTS_MAX_PAYLOAD_SIZE];
    MMP_UBYTE           TsPacket[MTS_TS_PACKET_SIZE];
    MMP_UBYTE           PcrPacket[MTS_TS_PACKET_SIZE];
    MMP_ULONG           ulPts;
    MMP_ULONG           ulDts;
    MMP_UBYTE           ubPtsMsb32;
    MMP_UBYTE           ubDtsMsb32;
    MMP_UBYTE           ubContinuityCount;
    MMP_USHORT          usTsPktPos;
    MMPF_MTS_TIME_INFO  TimeInfo;
    MMPF_MTS_TIME_INFO  PcrInfo;
} MMPF_VIDMGR_MTS_PAYLAOD;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

///< __TS_SECTION__
MMP_ULONG   MMPF_MTS_GenerateTsHeader(MMP_UBYTE *pData, MMPF_MTS_TS *pTS);
void        MMPF_MTS_UpdateTsHeader(MMP_UBYTE *pData, MMP_BOOL bPayloadUnitStart, MMP_UBYTE ubContinuityCnt, MMP_UBYTE ubStuffingBytes);
void        MMPF_MTS_IncreamentTsPcr(MMPF_MTS_TIME_INFO *time_info);
void        MMPF_MTS_SetTsPcr(MMPF_MTS_TIME_INFO *time_info, MMP_ULONG time_ms);
void        MMPF_MTS_UpdateTsPcr(MMP_UBYTE *PcrPacket, MMPF_MTS_TIME_INFO *PcrInfo);

///< __PES_SECTION__
void        MMPF_MTS_UpdatePesTimestamp(MMP_UBYTE *pPesData, MMP_ULONG time_stamp_32, MMP_ULONG time_stamp_31_00);
void        MMPF_MTS_UpdatePesStreamId(MMP_UBYTE *pPesData, MMP_UBYTE ubStreamId);
void        MMPF_MTS_SetTsPesTimestamp(MMPF_MTS_TIME_INFO *time_info, MMP_ULONG time_ms);
void        MMPF_MTS_IncreamentPesTimestamp (MMPF_MTS_TIME_INFO *time_info);
MMP_ULONG   MMPF_MTS_GeneratePesVidHeader(MMP_UBYTE *pPesVidHdr);
MMP_ULONG   MMPF_MTS_GeneratePesAudHeader(MMP_UBYTE *pPesAudHdr);
MMP_ULONG   MMPF_MTS_GenerateSdtHeader(MMP_UBYTE *pPesSdtHdr);
MMP_ULONG   MMPF_MTS_GeneratePcrStuffHeader(MMP_UBYTE *pPesPcrStuffHdr);

///< __SIT_SECTION__
void        MMPF_MTS_GenerateSit(MMP_UBYTE *pData, MMP_ULONG *ulLength);
///< __PMT_SECTION__
void        MMPF_MTS_InitPmtConfig( MMPF_MTS_PSI    *pPsi,
                                    MMP_USHORT      usPcrPid,
                                    MMP_UBYTE       *pProgrameInfo,
                                    MMP_USHORT      usProgramInfoLen);
void        MMPF_MTS_GetPmtVidDesc(MMP_UBYTE **pDesc, MMP_ULONG *ulDescLen);
void        MMPF_MTS_GetPmtAudDesc(MMP_UBYTE **pDesc, MMP_ULONG *ulDescLen, MMPF_MTS_STREAM_TYPE type);
void        MMPF_MTS_GetPmtProgramDesc(MMP_UBYTE **pDesc, MMP_ULONG *ulDescLen);
void        MMPF_MTS_UpdatePmtVidDesc(MMP_UBYTE *pDesc, MMP_USHORT usProfile, MMP_USHORT usLevel);
void        MMPF_MTS_AddEsToPmt(MMPF_MTS_PSI    *pPsi,
                                MMPF_MTS_STREAM_TYPE EsType,
                                MMP_USHORT      usEsPid,
                                MMP_UBYTE       *pEsInfoDesc,
                                MMP_USHORT      usEsInfoLen);
///< __PAT_SECTION__
void        MMPF_MTS_InitPatConfig(MMPF_MTS_PSI *pPsi, MMP_USHORT usPmtPid[], MMP_USHORT usNumPmt);
///< __COMMON_SECTION__
MMP_ERR     MMPF_MTS_GeneratePsiTable(MMP_UBYTE *pData, MMP_ULONG *ulDataLen, MMPF_MTS_PSI *pPsi);
void        MMPF_MTS_UpdatePesAudioLens(MMP_UBYTE *pPesData, MMP_USHORT length);

/* TS Merger Function */
MMP_ERR     MMPF_MTS_Initialization(void);
void        MMPF_MTS_UpdateMTsHeader(MMP_USHORT PID, MMP_BOOL bPayloadUnitStart, MMP_UBYTE ubContinuityCnt, MMP_UBYTE ubStuffingBytes, MMPF_VID_MGR_INFO* pMerger);
MMP_ULONG   MMPF_MTS_GeneratePesStartCode(MMP_UBYTE *header_buf);
MMP_ULONG   MMPF_MTS_GenerateAudHeader(MMP_USHORT PID, MMP_UBYTE *header_buf, VIDENC_FRAME_TYPE FrameType, MMP_ULONG ulAudFrmSize);
MMP_ULONG   MMPF_MTS_GeneratePES(MMP_USHORT PID, MMP_ULONG dst_addr, MMP_ULONG ulCurTime, MMP_ULONG ulCurSize);
MMP_ULONG   MMPF_MTS_PackPcrVidHead(MMP_USHORT PID, MMP_ULONG dst_addr, MMP_ULONG ulCurTime, MMP_ULONG ulCurSize);
MMP_ERR     MMPF_VIDMGR_StartMtsRecd(MMP_UBYTE ubEncId);
MMP_ERR     MMPF_VIDMGR_InsertMtsPatPmt(/*MMP_UBYTE ubEncId,*/ MMP_ULONG dst_addr, MMP_ULONG dst_high, MMP_ULONG dst_low, MMP_ULONG *ulTotalSize);
MMP_ERR     MMPF_MTS_PreProcessFile(MMP_UBYTE storagemode, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR     MMPF_MTS_PostProcessFile(MMP_UBYTE storagemode, MMP_UBYTE * tmp_buf, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR     MMPF_MTS_GetSavedSize(MMP_ULONG AVSize, MMP_ULONG VideoCount, MMP_ULONG AudioSampleCount, MMP_ULONG AudioChunkCount, MMP_ULONG64 *total_size, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR     MMPF_MTS_GetRecordingSize(MMP_ULONG *ulSize, MMPF_VID_MGR_INFO* pContainer);
MMP_ERR     MMPF_MTS_UpdateMTsPcr(MMP_UBYTE *pData, MMPF_MTS_TIME_INFO *time_info);
MMP_ERR     MMPF_MTS_SetMTSPcr(MMP_ULONG dst_addr, MMP_ULONG ulframetime);
MMP_ULONG   MMPF_MTS_SetMTSPcrInVid(MMP_ULONG dst_addr, MMP_ULONG ulframetime);

MMP_ERR MMPF_MTSMUX_PostFillFileInfo(MMP_UBYTE storagemode, MMPF_VID_MGR_INFO* pMerger);
MMP_ERR MMPF_MTSMUX_PostFillVRThumb(MMP_UBYTE storagemode, MMPF_VID_MGR_INFO* pMerger);
MMP_ERR MMPF_MTSMUX_PostFillVidIInfo(MMP_UBYTE storagemode, MMPF_VID_MGR_INFO* pMerger);
MMP_ERR MMPF_MTSMUX_PostFillAudFrmInfo(MMP_UBYTE storagemode, MMPF_VID_MGR_INFO* pMerger);

/* Mux Function */
MMP_ERR     MMPF_MTSMUX_GetRecordingSize(MMP_ULONG *ulSize, MMPF_VID_MGR_INFO* pMerger);
MMP_ERR     MMPF_MTSMUX_FillTail(MMPF_VID_MGR_INFO* pMerger);
MMP_ERR     MMPF_MTSMUX_PreProcessFile(MMP_UBYTE storagemode, MMPF_VID_MGR_INFO* pMerger);
MMP_ERR     MMPF_MTSMUX_PostProcessFile(MMP_UBYTE storagemode, MMP_UBYTE * tmp_buf, MMPF_VID_MGR_INFO* pMerger);
MMP_ERR     MMPF_MTSMUX_GetSavedSize(MMP_ULONG AVSize, MMP_ULONG VideoCount, MMP_ULONG AudioSampleCount, MMP_ULONG AudioChunkCount, MMP_ULONG64 *total_size, MMPF_VID_MGR_INFO* pMerger);
MMP_ERR     MMPF_MTSMUX_AddChunkPrefix(MMP_UBYTE chunktype, MMP_ULONG framesize, MMPF_VID_MGR_INFO* pMerger);
MMP_ERR     MMPF_MTSMUX_AddChunkSuffix(MMP_UBYTE chunktype, MMP_ULONG framesize, MMPF_VID_MGR_INFO* pMerger);
MMP_ULONG   MMPF_MTSMUX_CalcChunkPrefixSize(MMP_UBYTE chunktype, MMP_ULONG framesize, MMPF_VID_MGR_INFO* pMerger);
MMP_ULONG   MMPF_MTSMUX_CalcChunkSuffixSize(MMP_UBYTE chunktype, MMP_ULONG framesize, MMPF_VID_MGR_INFO* pMerger);
MMP_ERR     MMPF_MTSMUX_InsertDupFrame(MMPF_VID_MGR_INFO* pMerger);
MMP_ERR     MMPF_MTSMUX_KeepIndexEntry(MMP_UBYTE chunktype, MMP_ULONG framesize, VIDENC_FRAME_TYPE frametype, MMPF_VID_MGR_INFO* pMerger);
MMP_ERR     MMPF_MTSMUX_AddIndexChunk(MMPF_VID_MGR_INFO* pMerger);
MMP_BOOL    MMPF_MTSMUX_IsTimeInfoNeeded(void);
MMP_BOOL    MMPF_MTSMUX_IsSizeInfoNeeded(void);

#endif // _MMPF_MTS_H_

/// @}
/// @end_ait_only
