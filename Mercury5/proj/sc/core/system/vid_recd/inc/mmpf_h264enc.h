//==============================================================================
//
//  File        : mmpf_h264enc.h
//  Description : Header function of video codec
//  Author      : Will Tseng
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_H264ENC_H_
#define _MMPF_H264ENC_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mmp_vidrec_inc.h"
#include "drv_mfe_kernel.h"

/** @addtogroup MMPF_VIDEO
@{
*/

//==============================================================================
//
//                              COMPILER OPTION
//
//==============================================================================

#define FPS_RC_CTL                      (0) // Comment: Suggest to close it if no need to dynamic change FPS.
#define H264E_COMPRESS_BUF_NEAR_RING_EN (1) // 1:Single NearRing Buffer, 0:Double Ring Buffer

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

// VUI Control
#if (SUPPORT_VUI_INFO)
#define VUI_HRD_MAX_CPB_CNT     (1)
#define SUPPORT_POC_TYPE_1      (0)
#define MAX_PARSET_BUF_SIZE     (256)
#define H264E_STARTCODE_LEN     (4)
#endif

// Frame Types
#define I_FRAME                 (VIDENC_I_FRAME)
#define P_FRAME                 (VIDENC_P_FRAME)
#define B_FRAME                 (VIDENC_B_FRAME)

// H264 Profile IDC
#define BASELINE_PROFILE        (66)
#define MAIN_PROFILE            (77)

// FREXT Profile IDC
#define FREXT_HP                (100)      ///< YUV 4:2:0/8 "High"
#define FREXT_Hi10P             (110)      ///< YUV 4:2:0/10 "High 10"
#define FREXT_Hi422             (122)      ///< YUV 4:2:2/10 "High 4:2:2"
#define FREXT_Hi444             (244)      ///< YUV 4:4:4/12 "High 4:4:4"

// The default threshold of accumulate skip frames within one second.
// While the number of accumulate skip frames in 1 second is over the
// threshold, card_slow event will be triggered by callback.
#define CARD_SLOW_THRESHOLD     (6)

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

typedef enum {
    MMPF_H264ENC_INSERT_SPS_PPS_ENC_ST      = 0,
    MMPF_H264ENC_INSERT_SPS_PPS_ENC_DONE    = 1,
    MMPF_H264ENC_INSERT_SPS_PPS_RST         = 0xFF,
} MMPF_H264ENC_SEI_TYPE;

#if (SUPPORT_VUI_INFO)
typedef enum {
    MMPF_H264ENC_SEI_TYPE_BUF_PERIOD      = 0x0001,
    MMPF_H264ENC_SEI_TYPE_PIC_TIMING      = 0x0002,
    MMPF_H264ENC_SEI_TYPE_USER_DATA_UNREG = 0x0020,
    MMPF_H264ENC_SEI_TYPE_MAX             = 0x0040
} MMPF_H264ENC_SEI_TYPE;

typedef enum {
    MMPF_H264ENC_BYTESTREAM_ANNEXB= 0,
    MMPF_H264ENC_BYTESTREAM_NALU_EBSP,
    MMPF_H264ENC_BYTESTREAM_NALU_RBSP
} MMPF_H264ENC_BYTESTREAM_TYPE;

typedef enum {
    H264_NALU_TYPE_SLICE    = 1,
    H264_NALU_TYPE_DPA      = 2,
    H264_NALU_TYPE_DPB      = 3,
    H264_NALU_TYPE_DPC      = 4,
    H264_NALU_TYPE_IDR      = 5,
    H264_NALU_TYPE_SEI      = 6,
    H264_NALU_TYPE_SPS      = 7,
    H264_NALU_TYPE_PPS      = 8,
    H264_NALU_TYPE_AUD      = 9,
    H264_NALU_TYPE_EOSEQ    = 10,
    H264_NALU_TYPE_EOSTREAM = 11,
    H264_NALU_TYPE_FILL     = 12,
    H264_NALU_TYPE_SPSEXT   = 13,
    H264_NALU_TYPE_PREFIX   = 14,
    H264_NALU_TYPE_SUBSPS   = 15
} MMPF_H264ENC_NALU_TYPE;

typedef enum {
    H264_NALU_PRIORITY_HIGHEST     = 3,
    H264_NALU_PRIORITY_HIGH        = 2,
    H264_NALU_PRIORITY_LOW         = 1,
    H264_NALU_PRIORITY_DISPOSABLE  = 0
} MMPF_H264ENC_NAL_REF_IDC;
#endif

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

// VUI Information
#if (SUPPORT_VUI_INFO)
typedef struct _MMPF_H264ENC_SEI_PARAM {
    struct {
        MMP_ULONG init_cpb_removal_delay[2][VUI_HRD_MAX_CPB_CNT];
        MMP_ULONG init_cpb_removal_delay_offset[2][VUI_HRD_MAX_CPB_CNT];
    } BUF_PERIOD;
    struct {
        MMP_ULONG cpb_removal_delay;
        MMP_ULONG dpb_output_delay; 
    } PIC_TIMING;
} MMPF_H264ENC_SEI_PARAM;

typedef struct _MMPF_H264ENC_SYNTAX_ELEMENT {
    MMP_LONG    type;           //!< type of syntax element for data part.
    MMP_LONG    value1;         //!< numerical value of syntax element
    MMP_LONG    value2;         //!< for blocked symbols, e.g. run/level
    MMP_LONG    len;            //!< length of code
    MMP_LONG    inf;            //!< info part of UVLC code
    MMP_ULONG   bitpattern;     //!< UVLC bitpattern
    MMP_LONG    context;        //!< CABAC context
    //!< for mapping of syntaxElement to UVLC
    //void    (*mapping)(int value1, int value2, int* len_ptr, int* info_ptr);
} MMPF_H264ENC_SYNTAX_ELEMENT;

typedef struct _MMPF_H264ENC_NALU_INFO {
    MMPF_H264ENC_NALU_TYPE      nal_unit_type;
    MMPF_H264ENC_NAL_REF_IDC    nal_ref_idc;
    MMP_UBYTE                   temporal_id;    ///< SVC extension
} MMPF_H264ENC_NALU_INFO;

typedef struct _MMPF_H264ENC_BS_INFO {     
    MMP_LONG    byte_pos;           ///< current position in bitstream;
    MMP_LONG    bits_to_go;         ///< current bitcounter
    MMP_UBYTE   byte_buf;           ///< current buffer for last written byte
    MMP_UBYTE   *streamBuffer;      ///< actual buffer for written bytes
} MMPF_H264ENC_BS_INFO;

typedef struct _MMPF_H264ENC_HRD_INFO {
    MMP_ULONG   cpb_cnt_minus1;                                 // ue(v)
    MMP_ULONG   bit_rate_scale;                                 // u(4)
    MMP_ULONG   cpb_size_scale;                                 // u(4)
    MMP_ULONG   bit_rate_value_minus1 [VUI_HRD_MAX_CPB_CNT];  	// ue(v)
    MMP_ULONG   cpb_size_value_minus1 [VUI_HRD_MAX_CPB_CNT];  	// ue(v)
    MMP_ULONG   cbr_flag              [VUI_HRD_MAX_CPB_CNT];  	// u(1)
    MMP_ULONG   initial_cpb_removal_delay_length_minus1;        // u(5)
    MMP_ULONG   cpb_removal_delay_length_minus1;                // u(5)
    MMP_ULONG   dpb_output_delay_length_minus1;                 // u(5)
    MMP_ULONG   time_offset_length;                             // u(5)
} MMPF_H264ENC_HRD_INFO;

typedef struct _MMPF_H264ENC_VUI_INFO {
    MMP_BOOL    aspect_ratio_info_present_flag;               	// u(1)
    MMP_ULONG   aspect_ratio_idc;                             	// u(8)
    MMP_ULONG   sar_width;                                		// u(16)
    MMP_ULONG   sar_height;                               		// u(16)
    MMP_BOOL    overscan_info_present_flag;                   	// u(1)
    MMP_BOOL    overscan_appropriate_flag;                		// u(1)
    MMP_BOOL    video_signal_type_present_flag;               	// u(1)
   	MMP_ULONG   video_format;                                   // u(3) 0:component, 1:PAL, 2:NTSC, 3:SECAM, 4:MAC 5:Unspecified video format
    MMP_BOOL    video_full_range_flag;                        	// u(1)
    MMP_BOOL    colour_description_present_flag;              	// u(1)
    MMP_ULONG   colour_primaries;                             	// u(8)
    MMP_ULONG   transfer_characteristics;                     	// u(8)
    MMP_ULONG   matrix_coefficients;                          	// u(8)
    MMP_BOOL    chroma_location_info_present_flag;              // u(1)
    MMP_ULONG   chroma_sample_loc_type_top_field;               // ue(v)
    MMP_ULONG   chroma_sample_loc_type_bottom_field;            // ue(v)
    MMP_BOOL    timing_info_present_flag;                       // u(1)
    MMP_ULONG   num_units_in_tick;                              // u(32)
    MMP_ULONG   time_scale;                                     // u(32)
    MMP_BOOL    fixed_frame_rate_flag;                          // u(1)
    MMP_BOOL    nal_hrd_parameters_present_flag;                // u(1)
    MMPF_H264ENC_HRD_INFO nal_hrd_parameters;                   // hrd_paramters_t
    MMP_BOOL    vcl_hrd_parameters_present_flag;                // u(1)
    MMPF_H264ENC_HRD_INFO vcl_hrd_parameters;                   // hrd_paramters_t
    MMP_BOOL    low_delay_hrd_flag;                             // u(1)
    MMP_BOOL    pic_struct_present_flag;                        // u(1)
    MMP_BOOL    bitstream_restriction_flag;                     // u(1)
    MMP_BOOL    motion_vectors_over_pic_boundaries_flag;        // u(1)
    MMP_ULONG   max_bytes_per_pic_denom;                        // ue(v)
    MMP_ULONG   max_bits_per_mb_denom;                          // ue(v)
    MMP_ULONG   log2_max_mv_length_vertical;                    // ue(v)
    MMP_ULONG   log2_max_mv_length_horizontal;                  // ue(v)
    MMP_ULONG   num_reorder_frames;                             // ue(v)
    MMP_ULONG   max_dec_frame_buffering;                        // ue(v)
} MMPF_H264ENC_VUI_INFO;

typedef struct _MMPF_H264ENC_SPS_INFO {
    MMP_BOOL    Valid; // indicates the parameter set is valid
    MMP_ULONG   profile_idc;                                    // u(8)
    MMP_BOOL    constrained_set0_flag;                          // u(1)
    MMP_BOOL    constrained_set1_flag;                          // u(1)
    MMP_BOOL    constrained_set2_flag;                          // u(1)
    MMP_BOOL    constrained_set3_flag;                          // u(1)
    MMP_BOOL    constrained_set4_flag;                          // u(1)
    MMP_BOOL    constrained_set5_flag;                          // u(1)
    MMP_BOOL    constrained_set6_flag;                          // u(1)
    MMP_ULONG   level_idc;                                      // u(8)
    MMP_ULONG   seq_parameter_set_id;                           // ue(v)
    MMP_ULONG   chroma_format_idc;                              // ue(v)

    MMP_BOOL    seq_scaling_matrix_present_flag;                // u(1) => always 0
    MMP_ULONG   bit_depth_luma_minus8;                          // ue(v)
    MMP_ULONG   bit_depth_chroma_minus8;                        // ue(v)
    MMP_ULONG   log2_max_frame_num_minus4;                      // ue(v)
    MMP_ULONG   pic_order_cnt_type;
    MMP_ULONG   log2_max_pic_order_cnt_lsb_minus4;              // ue(v)
    #if (SUPPORT_POC_TYPE_1 == 1)
    MMP_BOOL delta_pic_order_always_zero_flag;                  // u(1)
    MMP_LONG    offset_for_non_ref_pic;                     	// se(v)
    MMP_LONG    offset_for_top_to_bottom_field;             	// se(v)
    MMP_ULONG   num_ref_frames_in_pic_order_cnt_cycle;      	// ue(v)
    MMP_LONG    offset_for_ref_frame[MAX_REF_FRAME_IN_POC_CYCLE];// se(v)
    #endif
    MMP_ULONG   num_ref_frames;                                 // ue(v)
    MMP_BOOL    gaps_in_frame_num_value_allowed_flag;           // u(1)
    MMP_ULONG   pic_width_in_mbs_minus1;                        // ue(v)
    MMP_ULONG   pic_height_in_map_units_minus1;                 // ue(v)
    MMP_BOOL    frame_mbs_only_flag;                            // u(1)
    MMP_BOOL    mb_adaptive_frame_field_flag;                   // u(1)
    MMP_BOOL    direct_8x8_inference_flag;                      // u(1)
    MMP_BOOL    frame_cropping_flag;                            // u(1)
    MMP_ULONG   frame_cropping_rect_left_offset;                // ue(v)
    MMP_ULONG   frame_cropping_rect_right_offset;               // ue(v)
    MMP_ULONG   frame_cropping_rect_top_offset;                 // ue(v)
    MMP_ULONG   frame_cropping_rect_bottom_offset;              // ue(v)
    MMP_BOOL    vui_parameters_present_flag;                    // u(1)
    MMPF_H264ENC_VUI_INFO vui_seq_parameters;
} MMPF_H264ENC_SPS_INFO;
#endif

// H264 Module Status
typedef struct _MMPF_H264ENC_FUNC_STATES {
    MMP_USHORT                  ProfileIdc;         // Encoder profile
    VIDENC_ENTROPY              EntropyMode;        // VLC mode
} MMPF_H264ENC_FUNC_STATES;

// H264 Module
typedef struct _MMPF_H264ENC_MODULE {
    MMP_BOOL                        bWorking;       // The module is working or not
    struct _MMPF_H264ENC_ENC_INFO   *pH264Inst;     // Pointer to instance
    MMPF_H264ENC_FUNC_STATES        HwState;        // HW status
} MMPF_H264ENC_MODULE;

// Encode Instance
typedef struct _MMPF_H264ENC_ENC_INFO {

    /* General Configuration */
    MMP_ULONG                   ulCamType;          // Cam Type
    MMP_ULONG                   ulInstId;           // Instance ID
    MMPF_H264ENC_MODULE         *pModule;           // Pointer to connected module
    void                        *pPrivData;         // Pointer to connected private data
    void                        *pMerger;           // Pointer to connected merger
    void                        *pCompHandle;       // Pointer to connected component
    mmfe_dev                    *pMfeDev;           // Pointer to mmfe_dev structure
    mmfe_ctx                    *pMfeCtx;           // Pointer to mmfe_ctx structure

    MMP_USHORT                  usMB_W;             // The width of frame (Unit:MB)
    MMP_USHORT                  usMB_H;             // The height of frame (Unit:MB)
    MMP_ULONG                   ulConusIFrmNum;     // The contiguous I-frame count
    MMP_ULONG                   ulGopFrameNum;      // Set zero if sync frame is output
    MMP_BOOL                    bInsertSkipFrame;   // Insert skip frame to prevent overflow
    MMP_UBYTE                   ubInsertSpsPps;     // Insert SPS/PPS or not
    VIDENC_DUMMY_DROP_INFO      stDummyDropInfo;    // The dummy/drop frame information
    MMP_ULONG                   ulTotalEncSize;     // Total encoded size
    MMP_ULONG                   ulTotalEncFrames;   // Total encoded frames
    MMP_ULONG                   ulTotalInputFrms;   // Total input frames
    MMP_ULONG                   ulTimeStamp;        // The current frame timestamp
    VIDENC_FRAME_TYPE           eCurFrmType;        // The current frame type (I/P/B)
    MMP_UBYTE                   ubMaxFrameNumAndPoc;// The max reference frame number and POC number
    MMP_ULONG                   ulSpsLen;           // The current SPS length
    MMP_ULONG                   ulRcMode;           // The rate control mode
    MMP_ULONG                   ulMaxPreEncTimeMs;  // The max pre-enc time limit (Unit:ms)

    MMP_USHORT                  usOperation;        // The operation from host command
    MMP_USHORT                  usStatus;           // The status of video engine
    MMP_UBYTE                   ubVidCaptureStart;  // The flag of execute encode function (MMPF_VIDENC_InputFrameReady)

    /* Encode Attribute Configuration */
    VIDENC_BITRATE_CTL          stBrCtl;
    VIDENC_LEAKYBUCKET_CTL      stLeakyBufCtl;
    VIDENC_RC_SKIP_CTL          stSkipCtl;
    VIDENC_RESRC_CTL            stResrcCtl;
    VIDENC_MOT_CTL              stMotCtl;
    VIDENC_AVC_CTL              stAvcCtl;
    VIDENC_VUI_CTL              stVuiCtl;
    VIDENC_ROI_CTL              stRoiCtl;
    VIDENC_SPL_CTL              stSplCtl;
    VIDENC_GOP_CTL              stGopCtl;

    VIDENC_QP_CTL               stQPCtl;
    VIDENC_QP_BOUND_CTL         stFrmQPBoundCtl;
    VIDENC_QP_BOUND_CTL         stMBQPBoundCtl;

    VIDENC_FPS_CTL              stSnrFps;
    VIDENC_FPS_CTL              stEncFps;
    VIDENC_FPS_CTL              stMaxFps;

    /* Buffer Configuration */    
    #if (SUPPORT_VUI_INFO)
    MMP_UBYTE                   *glVidRecdTmpSPSAddr;// The temp SPS address
    MMP_ULONG                   glVidRecdTmpSPSSize;// The temp SPS size
    MMP_UBYTE                   sps_buf[MAX_PARSET_BUF_SIZE]; // The SPS buffer
    MMP_UBYTE                   pps_buf[MAX_PARSET_BUF_SIZE]; // The PPS buffer
    MMP_UBYTE                   sei_buf[MAX_PARSET_BUF_SIZE]; // The SEI buffer
    #endif
    
    MMP_UBYTE                   *pubVidEncSPSAddr;  // The current SPS address
    MMP_ULONG                   ulVidEncSPSSize;    // The current SPS size
    MMP_UBYTE                   *pubVidEncPPSAddr;  // The current PPS address
    MMP_ULONG                   ulVidEncPPSSize;    // The current PPS size
    VIDENC_FRAME_INFO           stCurOutBs[2];      // The current bitstream buffer addr information
    VIDENC_FRAME_INFO           stCurOutBsAlign[2]; // The current aligned bitstream buffer addr information
    
    /* VUI Configuration */
    #if (SUPPORT_VUI_INFO)
    MMPF_H264ENC_SPS_INFO       sps;                // The temp SPS information
    MMPF_H264ENC_SEI_CTL        SeiCtl;             // SEI control
    MMPF_H264ENC_SEI_PARAM      sei_param;          // Parameter for supported sei message
    MMPF_H264ENC_NALU_INFO      nalu;               // The NALU information
    #endif

    /* RunTime Update Parameter */
    MMP_ULONG                   ulParamQRdWrapIdx;  // The parameter queue read index (MS3Byte wrap, LSByte idx)
    MMP_ULONG                   ulParamQWrWrapIdx;  // The parameter queue write index (MS3Byte wrap, LSByte idx)
    VIDENC_PARAM_CTL            stParamQueue[VIDENC_MAX_PARAM_SET_NUM];  // The parameter queue
    
    /* Frame Rate Control */
#if (FPS_RC_CTL)
    MMP_ULONG                   ulFpsInputRes;      // Input frame rate resolution
    MMP_ULONG                   ulFpsInputInc;      // Input frame rate increment
    MMP_ULONG                   ulFpsInputAcc;      // Input frame rate accumulation
    MMP_ULONG                   ulFpsOutputRes;     // Encode frame rate resolution
    MMP_ULONG                   ulFpsOutputInc;     // Encode frame rate increment
    MMP_ULONG                   ulFpsOutputAcc;     // Encode frame rate accumulation
#endif
    MMP_BOOL                    bShareBuffer;       // Share current buffer mode.
} MMPF_H264ENC_ENC_INFO;

// Record File Instance
typedef struct _MMPF_VIDENC_RECD_FILE_INFO {

    /* General Configuration */
    void                        *pMerger;           // Pointer to connected merger
    void                        *pCompHandle;       // Pointer to connected component

    MMP_USHORT                  usMB_W;             // The width of frame (Unit:MB)
    MMP_USHORT                  usMB_H;             // The height of frame (Unit:MB)
    MMP_BOOL                    bInsertSkipFrame;   // Insert skip frame to prevent overflow
    MMP_UBYTE                   ubInsertSpsPps;     // Insert SPS/PPS or not
    VIDENC_DUMMY_DROP_INFO      stDummyDropInfo;    // The dummy/drop frame information
    MMP_ULONG                   ulTotalEncSize;     // Total encoded size
    MMP_ULONG                   ulTotalEncFrames;   // Total encoded frames
    MMP_ULONG                   ulTotalInputFrms;   // Total input frames
    MMP_ULONG                   ulTimeStamp;        // The current frame timestamp
    VIDENC_FRAME_TYPE           eCurFrmType;        // The current frame type (I/P/B)
    MMP_ULONG                   ulMaxPreEncTimeMs;  // The max pre-enc time limit (Unit:ms)

    MMP_USHORT                  usOperation;        // The operation from host command
    MMP_USHORT                  usStatus;           // The status of video engine
    MMP_UBYTE                   ubVidCaptureStart;  // The flag of execute encode function (MMPF_VIDENC_InputFrameReady)

    /* Encode Attribute Configuration */
    VIDENC_BITRATE_CTL          stBrCtl;
    VIDENC_RC_SKIP_CTL          stSkipCtl;
    VIDENC_AVC_CTL              stAvcCtl;
    VIDENC_GOP_CTL              stGopCtl;
    VIDENC_FPS_CTL              stSnrFps;
    VIDENC_FPS_CTL              stEncFps;
    VIDENC_FPS_CTL              stMaxFps;

    /* Buffer Configuration */
    MMP_UBYTE                   *pubVidEncSPSAddr;  // The current SPS address
    MMP_ULONG                   ulVidEncSPSSize;    // The current SPS size
    MMP_UBYTE                   *pubVidEncPPSAddr;  // The current PPS address
    MMP_ULONG                   ulVidEncPPSSize;    // The current PPS size
} MMPF_VIDENC_RECD_FILE_INFO;

//==============================================================================
//
//                              FUNCTION PROTOTYPES
//
//==============================================================================

MMPF_H264ENC_ENC_INFO *MMPF_H264ENC_GetHandle(MMP_ULONG ulEncId);
MMP_USHORT MMPF_H264ENC_GetStreamTypeFromId(MMP_ULONG ulEncId);

MMP_ERR MMPF_H264ENC_GetHeaderBuf(   MMPF_H264ENC_ENC_INFO   *pEncInfo,
                                     MMP_ULONG*              pulSPSStart,
                                     MMP_ULONG*              pulPPSStart,
                                     MMP_ULONG*              pulTmpSPSStart);
MMP_ERR MMPF_H264ENC_SetHeaderBuf(   MMPF_H264ENC_ENC_INFO   *pEncInfo,
                                     MMP_ULONG               ulSPSStart,
                                     MMP_ULONG               ulPPSStart,
                                     MMP_ULONG               ulTmpSPSStart);

MMP_ERR MMPF_H264ENC_SetUVCCompHandle(void* pvCompHandle);
MMP_ERR MMPF_H264ENC_GetUVCHeaderBuf(MMP_ULONG *pulSPSStart,
                                     MMP_ULONG *pulPPSStart);
MMP_ERR MMPF_H264ENC_SetUVCHeaderBuf(MMP_ULONG ulSPSStart,
                                     MMP_ULONG ulPPSStart);
MMP_ERR MMPF_H264ENC_GetUVCCompressBuf(MMP_ULONG *pulBufAddr, MMP_ULONG *pulBufSize);
MMP_ERR MMPF_H264ENC_SetUVCCompressBuf(MMP_ULONG ulBufAddr, MMP_ULONG ulBufSize);

MMP_ERR MMPF_H264ENC_SetNormalFrmSkipCountThd(MMP_ULONG ulTotalCount, MMP_ULONG ulContiCount);
MMP_ERR MMPF_H264ENC_SetSeamlessFrmSkipCountThd(MMP_ULONG ulTotalCount, MMP_ULONG ulContiCount);
MMP_ERR MMPF_H264ENC_ChangeFrmSkipCountThd(MMPF_H264ENC_ENC_INFO *pEncInfo, MMP_BOOL bSeamless);

MMP_ERR MMPF_H264ENC_SetParameter(  MMPF_H264ENC_ENC_INFO   *pEncInfo,
                                    VIDENC_ATTRIBUTE        attrib,
                                    void                    *arg);
MMP_ERR MMPF_H264ENC_GetParameter(  MMPF_H264ENC_ENC_INFO   *pEncInfo,
                                    VIDENC_ATTRIBUTE        attrib,
                                    void                    *ulValue);

MMP_ERR MMPF_H264ENC_InitModule(MMPF_H264ENC_MODULE *pModule);
MMP_ERR MMPF_H264ENC_DeinitModule (MMPF_H264ENC_MODULE *pModule);
MMP_ERR MMPF_H264ENC_InitInstance(MMPF_H264ENC_ENC_INFO *pEncInfo,
                                  MMPF_H264ENC_MODULE   *attached_mod,
                                  void                  *priv,
                                  MMP_USHORT            usStreamType,
                                  MMP_USHORT            usRcMode,
                                  void*                 pCompHandle);
MMP_ERR MMPF_H264ENC_DeinitInstance(MMPF_H264ENC_ENC_INFO *pEncInfo, MMP_BOOL bSeamless);

MMP_ERR MMPF_H264ENC_Open(MMPF_H264ENC_ENC_INFO *pEncInfo, MMP_BOOL bSeamless);
MMP_ERR MMPF_H264ENC_Resume(MMPF_H264ENC_ENC_INFO *pEncInfo);
MMP_ERR MMPF_H264ENC_TriggerEncode(MMPF_H264ENC_ENC_INFO    *pEncInfo,
                                   VIDENC_FRAME_TYPE        FrameType,
                                   MMP_ULONG                ulFrameTime,
                                   VIDENC_FRAME_INFO        *pInFrameInfo,
                                   VIDENC_FRAME_INFO        *pGenFrameInfo,
                                   VIDENC_FRAME_INFO        *pOutBuf0Info,
                                   VIDENC_FRAME_INFO        *pOutBuf1Info,
                                   void*                    pCompHandle);

#endif // _MMPF_H264ENC_H_
