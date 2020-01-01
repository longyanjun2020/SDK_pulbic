#ifndef __H263_SEQ_H_
#define __H263_SEQ_H_

#ifdef WIN32
#include <windows.h>
#endif

#ifdef _DEBUG
//#define DEBUG_RUNLEVEL
#endif

// Q, IQ speedup options
#define CHECK_DC_ZERO


#ifdef _SUPPORT_DUMP_
    #include <stdio.h>
#endif // _SUPPORT_DUMP_

#include "swvenc_deftypes.h"
#include "swvenc_h263_me_mgr.h"
#include "swvenc_h263_outstrm.h"
#include "swvenc_h263_rc.h"
#include "swvenc_h263_cod.h"
#include "swvenc_IntraUpdate.h"

#define FORMAT_H263     0
#define FORMAT_MPEG4_SP 1

typedef enum
{
    SWVNEC_STATUS_CREATE=1,
    SWVNEC_STATUS_SETMEM,
    SWVNEC_STATUS_INIT,
    SWVNEC_STATUS_START,
    SWVNEC_STATUS_STOP,
    SWVNEC_STATUS_DESTROY,
} SWVENC_INIT_FLAG;


typedef struct SW263V_t {
    int nCodecType; // FORMAT_H263, FORMAT_MPEG4_SP

    // ------------------------------------------------------------------------
    // each buffer is 4 element ,
    // 0: Y value, IMAGESIZEX*IMAGESIZEY  uint8*
    // 1: Cb value, IMAGESIZEX/2 * IMAGESIZEY/2     uint8*
    // 2: Cr value, IMAGESIZEX/2 * IMAGESIZEY/2     uint8*
    // 3: Motion Vector, BLOCKNUMX * BLOCKNUMY    point_t*
    // notice you need to note that the difference between type...
    void *f_buffer[4]; // point to buffer of forward prediction frame
    void *c_buffer[4]; // point to buffer of current frame

    uint8 *CUR, *PRE,*InputFrame;
    point_t *cMV, *pMV;

    // Current frame
    char chFrameType;
    uint32 nCurFrameBitsCount;

    // For "continue" encoding
    int gi, mi, mj, mk;

    // For skip-frame frame-buffer handling
    Bool m_bPrevFrameSkipped;

    // ------------------------------------------------------------------------
    //
    // sequence level parameter
    //
    uint16 s_horizontal_size,s_vertical_size;
    int m_nPicRate, m_nMinPicRate;
    //    float s_pel_aspect_ratio;
    unsigned int s_bit_rate;    // unit : bps

    // picture level parameter
    uint8 p_temporal_reference;
    //     Bool p_split_screen_indicator;
    //     Bool p_document_camera_indicator;
    //     Bool p_full_picture_freeze_release;
    uint8 p_source_format;
    uint8 p_quantizer;
    //     Bool p_continuousPresenceMultipointMode;
    //     Bool p_extraInsertionInformation;

    //    static const uint16 p_forward_f_code = 1;
    Bool p_full_pel_forward_vector;

    Bool m_bShortHeader;
    // ------------------------------------------------------------------------
    //
    // GOP level parameter
    //
    uint16 m_nPCount;
    uint16 m_nCurPCount;
    uint16 m_nGOPSize; // how many pictures in a GOP
    //    unsigned int g_time_code;
    uint16 num_mb_in_gob, num_gobs_in_vop;
    uint16 first_row_in_gob;
    // ------------------------------------------------------------------------
    //
    // GOB level parameter
    //
    uint8 g_frameID;

    // ------------------------------------------------------------------------
    // Quantizer
    //
    uint8 m_nIqscale, m_nPqscale;

    // ------------------------------------------------------------------------
    // Quality control
    //
    int8 m_nSQ;  //!< Speed quality indicator. Valid range [0,4]
    // SQ-adaptive
    int16 m_nHalfPelMinErr, m_nHalfPelMaxErr; // Thresholds for halfME
    int16 m_nIntraDecisionThr;  // Perform intra/inter mode decision or not
    // DCT and Quantization shortcut
    int16 m_s4x4DctThr[32];   // 4x4 DCT threshold: Index by qscale
    int16 m_sZeroBlkThr[32];  // Zero-block threshold: Index by qscale
    int16 m_sDCTOnlyhr[32];   // DcOnly-block threshold: Index by qscale
    // DCT/Q/IQ/IDCT simplification thresholds
    int nGapSkipInter, nGapDcOnlyInter;
    int nGapZeroDC, nGapSkipBlockInter;

    // ------------------------------------------------------------------------
    // Rate control
    //
    RateCtrl_t m_RC;
    RC_METHOD m_rcMethod;

    // ------------------------------------------------------------------------
    // Motion Estimation
    //
    MotEstContext m_MotEstContext;
    //    int m_nMePixelLevel, m_nMeMVLevel;    // determine MV Estimation method
    uint8 m_HalfMEBuf[3][17][HALFMEBUF_STRIDE]; // [V,H,HV][Y][X]

    // ------------------------------------------------------------------------
    // Bit engine
    //
    OutStream_t m_OutStream;

    int64 m_nEncodedFrameCount;

#ifdef _SUPPORT_DUMP_
    // ------------------------------------------------------------------------
    // Output file
    //
    // For debugging purpose: Reconstructed YUV dumping
    Bool m_bDumpRecon;  // If E_TRUE, dump YUV file
    char m_strDumpFileName[256];    // YUV-dump filename
    FILE *m_hDumpFile;  // YUV-dump file handle
#endif

    PLIndication m_PLValue;
    // Framerate and time
    int m_nTimeIncrement, m_nTimeResolution, m_nTimeResBits;
    // Rounding control
    int m_nVopRoundingType;

    // DC prediction buffer
    int16 m_IntraDC[6]; // Below will store intra-DC's and run-level pairs for vlc coding.
    int16 m_LeftDC[6]; // Index: [Y0, Y1, Y2, Y3, Cb, Cr]
    int16* m_TopDC; // (MB_WIDTH+1)*6. Index: [Y0, Y1, Y2, Y3, Cb, Cr] for each MB from left to right
    int16* m_CurDC; // (MB_WIDTH+1)*6. Index: [Y0, Y1, Y2, Y3, Cb, Cr] for each MB from left to right
    int16 *m_pTopDC, *m_pCurDC;

    uint8 m_u8Lpos[6];
    int notzerocount[6];
    int cbp;

    // Run/Length data collected when quantization, for later VLC coding.
    RunLevelPair m_RunLevel[6][64];

    // MB context
    MBINFO_t m_MbInfo[2];

    //intra update
    IntraUpdateContext IntraUpdateCtx;

    //initial flag
    SWVENC_INIT_FLAG init_flag;
} SW263V_t;


// ---------------- start of Interface methods -----------

//////////////////////
// Initialization
//////////////////////
// Settings: All have default setting.
Bool sw263v_SetFormat(SW263V_t* ctx, int nFormat);
Bool sw263v_SetFrameSize(SW263V_t* ctx, int w, int h);
Bool sw263v_SetPictureRate(SW263V_t* ctx, int nMaxrate, int nMinrate);
Bool sw263v_SetBitrate(SW263V_t* ctx, int bitrate);
Bool sw263v_ResetBitrate(SW263V_t* ctx, int nBitrate);
Bool sw263v_SetBitrateMethod(SW263V_t* ctx, RC_METHOD rcMethod); // 1:CBR, 2:VBR
Bool sw263v_SetFrameQScale(SW263V_t* ctx, int Iqscale, int Pqscale, int Bqscale);
Bool sw263v_SetGOP(SW263V_t* ctx, int nICount, int nPCount, int nBCount);       // Set H263 GOP pattern, return E_TRUE if successful.
Bool sw263v_SetSpeedQuality(SW263V_t* ctx, int nSQ);
Bool sw263v_InitIntraUpdate(SW263V_t* ctx, int bFIR, int bAIR, int bCIR, int nAIRCount, int nCIRDuration);
// Mandatory: Housekeeping
int sw263v_Init(SW263V_t* ctx);   // Must be called after all parameters are set and ready to encode.
void sw263v_Finish(SW263V_t* ctx); // Must be called after encoding work is done.
// Reserved
Bool sw263v_SetAspectRatio(SW263V_t* ctx, int nXRatio, int nYRatio);

//////////////////////
// Encoding
//////////////////////
uint32 sw263v_EncodeSeqStart(SW263V_t* ctx, uint8 *pOutBuf, uint32 nOutBufSize);
// [Return value] 1--Frame done, 0--Need continue
uint32 sw263v_EncodeOneFrame(SW263V_t* ctx, uint8 *pOutBuf, uint32 nOutBufSize, Bool bContinue, uint32* pRtnByteCount, unsigned int nFlags);
uint32 sw263v_EncodeSeqEnd(SW263V_t* ctx, uint8 *pOutBuf, uint32 nOutBufSize);

//////////////////////
// Status
//////////////////////
uint32 sw263v_ReportStreamLength(SW263V_t* ctx);

#ifdef _SUPPORT_DUMP_
//////////////////////
// Debug dumping
//////////////////////
void sw263v_SetOutFileName(SW263V_t* ctx, const char*);    // Set YUV-dump filename
#endif

void sw263v_Create(SW263V_t* ctx);
void sw263v_Destroy(SW263V_t* ctx);

// ---------------- end of Interface methods -----------

// private:
void _sw263v_LoadDefaultSetting(SW263V_t* ctx);

// ------------------------------------------------------------------------
//
// Generate H263 (not used in frame level encoding)
//
void _sw263v_AddFrameHeader(SW263V_t* ctx, int nInter);
void _sw263v_AddGOBHeader(SW263V_t* ctx, int gob_num,int qscale, int mb_ypos);
void _sw263v_AddSeqEnd(SW263V_t* ctx);

// ------------------------------------------------------------------------
// generate I, P, B frames
//
// Return: -1-- buf-full; 0-- frame done.
int _sw263v_GenH263IFrame(SW263V_t* ctx, Bool bContinue);
// Return: -1-- buf-full; 0-- frame done.
int _sw263v_GenH263PFrame(SW263V_t* ctx, Bool bContinue);
// Return: -1-- buf-full; 0-- frame done.
int _sw263v_GenPDummyFrame(SW263V_t* ctx);
// ------------------------------------------------------------------------
// Handle buffer pointer exchange
void _sw263v_ExchangeFrameBuf(SW263V_t* ctx);
// ------------------------------------------------------------------------
// Re-order information
char _sw263v_GetFrameType(SW263V_t* ctx);

// ------------------------------------------------------------------------
// VLC routine
//
void _sw263v_AddIframeMB(SW263V_t* ctx, int MB_type, int dquant);
void _sw263v_AddPframeMB(SW263V_t* ctx, int MB_type, int dquant, Bool coded);
void _sw263v_put_inter_ac(SW263V_t* ctx, int run, int level);
void _sw263v_put_inter_ac_last(SW263V_t* ctx, int run, int level);
void _sw263v_put_ac_coeff_escape(SW263V_t* ctx, int run, int level, int last);
void _sw263v_AddIntraBlock(SW263V_t* ctx, MBINFO_t* pMbInfo, int block);
void _sw263v_AddInterBlock(SW263V_t* ctx, MBINFO_t* pMbInfo, int block);
//-----------------------------------------------------
// Image Pre-Processing
//
#ifndef _SMALLER_CODESIZE_
void _sw263v_NoiseRemoval(SW263V_t* ctx);
#endif
//-----------------------------------------------------
// Frame buffer allocation and releasing
//
int _sw263v_AllocFrameBuffer(SW263V_t* ctx, int QueryOnly, int* pReqSize, int nWidth, int nHeight, int nFormat);
void _sw263v_FreeFrameBuffer(SW263V_t* ctx);

void _sw263v_SetQpAdaptiveThr(SW263V_t* ctx, int nQP);

// ------------------------------------------------------------------------
// Quality control
//
void _sw263v_Cal4x4Threshold(SW263V_t* ctx, int qscale);

//////////////////////////////////////////////////////////////////////////
// 14496-2
//////////////////////////////////////////////////////////////////////////
void _sw263v_AddVOSHeader(SW263V_t* ctx);
void _sw263v_AddVOHeader(SW263V_t* ctx);
void _sw263v_AddVOLHeader(SW263V_t* ctx);

void _sw263v_IntraDC_DPCM(SW263V_t* ctx, int16 diff_dc, Bool bIsLuma);
void _sw263v_put_intra_ac (SW263V_t* ctx, int run, int level, int last); // Table B-16
// Escape coding: intra coefficient
void _sw263v_put_intra_ac_escape(SW263V_t* ctx, int run, int abslevel, int sign);
void _sw263v_put_intra_ac_escape_last(SW263V_t* ctx, int run, int abslevel, int sign);
int _sw263v_put_intra_level(SW263V_t* ctx, int run, int abslevel, int sign);
int _sw263v_put_intra_level_last(SW263V_t* ctx, int run, int abslevel, int sign);
int _sw263v_put_intra_run(SW263V_t* ctx, int run, int abslevel, int sign);
int _sw263v_put_intra_run_last(SW263V_t* ctx, int run, int abslevel, int sign);
// Escape coding: inter coefficient
void _sw263v_put_inter_ac_escape(SW263V_t* ctx, int run, int abslevel, int sign);
void _sw263v_put_inter_ac_escape_last(SW263V_t* ctx, int run, int abslevel, int sign);
int _sw263v_put_inter_level(SW263V_t* ctx, int run, int abslevel, int sign);
int _sw263v_put_inter_level_last(SW263V_t* ctx, int run, int abslevel, int sign);
int _sw263v_put_inter_run(SW263V_t* ctx, int run, int abslevel, int sign);
int _sw263v_put_inter_run_last(SW263V_t* ctx, int run, int abslevel, int sign);

#endif
