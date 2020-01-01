
#ifndef _H264_ENC_H_
#define _H264_ENC_H_

typedef struct BitStream_t
{
    int     bits_pos;       /* Write Bit Count */
    int     length;         /* Buffer Length (Unit:Byte) */
    int     left_count;     /* Current FreeSpace for store code bits (Unit:Bit) */
    uint    code_bits;      /* Temporary Buffer for store code bits */
    uchar*  curr;           /* Current Buffer Address */
    uchar*  buffer;         /* Buffer Address */
    int     ebsp_zeros;     /* Current Continuous Zero Byte Count */
} bs_t;

int AvcReset(bs_t*,uchar*, int);
int AvcFlush(bs_t*);
int AvcCount(bs_t*);

#define NAL_SLICE           1
#define NAL_IDR             5
#define NAL_SPS             7
#define NAL_PPS             8
#define NAL_FILLER          12

#define NAL_PRIO_DISPOSED   0
#define NAL_PRIO_LOW        1
#define NAL_PRIO_HIGH       2
#define NAL_PRIO_HIGHEST    3

typedef struct Sps_t
{
    int i_sps_id;
    int i_profile_idc;          /* Indicate the profile and level to which the bitstream conforms */
    int i_level_idc;            /* Indicate the profile and level to which the bitstream conforms */
    int b_constraint_set0;      /* 1/0:Indicates that the bitstream obeys/may not obeys all constraints specified in Baseline profile */
    int b_constraint_set1;      /* 1/0:Indicates that the bitstream obeys/may not obeys all constraints specified in Main profile */
    int b_constraint_set2;      /* 1/0:Indicates that the bitstream obeys/may not obeys all constraints specified in Extend profile */
    int b_constraint_set3;      /* 1/0:Indicates that the bitstream obeys/may not obeys all constraints of special case of Level 1b */
    int i_log2_max_frame_num;   /* Specifies the value of the variable MaxFrameNum that is used in frame_num related derivations (0~12)+4 */
    int i_poc_type;             /* Specifies the method to decode picture order count (0~2) */
    int i_log2_max_poc_lsb;     /* Specifies the value of the variable MaxPicOrderCntLsb that is used in the decoding process for picture order count (0~12)+4 */
    int i_num_ref_frames;       /* Specifies the maximum number of short-term and long-term reference frames (0~MaxDpbSize) */
    int b_gaps_in_frame_num_value_allow; /* Specifies the allowed values of frame_num and the decoding process in case of an inferred gap */
    int i_mb_w;                 /* Specifies the width of each decoded picture in units of macroblocks */
    int i_mb_h;                 /* Specifies the height in slice group map units of a decoded frame or field */
    int b_direct8x8_inference;  /* Specifies the method used in the derivation process for luma motion vectors for B_Skip, B_Direct_16x16 and B_Direct_8x8 */
    int b_crop;                 /* Specifies that the frame cropping offset parameters follow next in the sequence parameter set */
    struct
    {
        int i_left, i_right;    /* Specify the samples of the pictures in the coded video sequence that are output from the decoding process */
        int i_top, i_bottom;
    } crop;
    int b_vui_param_pres;       /* Specifies that the vui_parameters( ) syntax structure is present */
    struct vui
    {
        int i_sar_w, i_sar_h;
        int b_video_signal_pres;/* Equal to 1 specifies that video_format, video_full_range_flag and colour_description_present_flag are present */
        int i_video_format;     /* Indicates the representation of the pictures, Ex : PAL, NTSC, SECAM... */
        int b_video_full_range; /* Indicates the black level and range of the luma and chroma signals */
        int b_timing_info_pres;
        uint i_num_units_in_tick;
        uint i_time_scale;
        int b_fixed_frame_rate;
        int b_colour_desc_pres; /* Equal to 1 specifies that colour_primaries, transfer_characteristics and matrix_coefficients are present */
        int i_colour_primaries; /* Indicates the chromaticity coordinates of the source primaries */
        int i_transf_character; /* Indicates the opto-electronic transfer characteristic of the source picture */
        int i_matrix_coeffs;    /* Describes the matrix coefficients used in deriving luma and chroma signals from the green, blue, and red primaries */
    } vui;
} sps_t;

typedef struct vui  vui_t;

typedef struct Pps_t
{
    sps_t*  sps;
    int i_pps_id;
    int b_cabac;                        /* Selects the entropy decoding method to be applied 0:CAVLC,1:CABAC */
    /* only support slice_groups == 1 */
    int i_num_ref_idx_l0_default_active;/* Specifies the maximum reference index for reference picture list 0 (0~31) */
    int i_num_ref_idx_l1_default_active;/* Specifies the maximum reference index for reference picture list 1 (0~31) */
    /* not support weighted prediction */
    int i_pic_init_qp;                  /* Specifies the initial value minus 26 of SliceQPY for each slice (-(26+QpBdOffsetY) ~ +25)+26 */
    int i_pic_init_qs;                  /* Specifies the initial value minus 26 of SliceQSY for all macroblocks in SP or SI slices (-26 ~ +25)+26 */
    int i_cqp_idx_offset;               /* Specifies the offset that shall be added to QPY and QSY for addressing the table of QPC value for the Cb chroma component (-12~+12) */
    int b_deblocking_filter_control;    /* Equal to 1 specifies that a set of syntax elements controlling the characteristics of the deblocking filter is present in the slice header */
    int b_constrained_intra_pred;       /* Equal to 1 specifies constrained intra prediction, in which case prediction of macroblocks coded using Intra macroblock prediction modes only uses residual data and decoded samples from I or SI macroblock types */
    int b_redundant_pic_cnt;            /* Equal to 1 specifies that the redundant_pic_cnt syntax element is present in all slice headers */
} pps_t;

typedef struct Slice_t
{
    int b_idr_pic;
#define NAL_PRIO_DISPOSED   0
#define NAL_PRIO_LOW        1
#define NAL_PRIO_HIGH       2
#define NAL_PRIO_HIGHEST    3
    int i_ref_idc;                      /* nal_ref_idc : Not equal to 0 specifies that the content of the NAL unit contains a SPS or a PPS or a slice of a reference picture or a slice data partition of a reference picture*/
    sps_t*  sps;
    pps_t*  pps;
#define SLICE_P 0
#define SLICE_B 1
#define SLICE_I 2
    int i_type;                         /* Specifies the coding type of the slice */
    int i_first_mb;                     /* Specifies the address of the first macroblock in the slice */
    int i_frm_num;                      /* Used as an identifier for pictures and shall be represented by log2_max_frame_num_minus4 + 4 bits in the bitstream */
    int i_idr_pid;                      /* Identifies an IDR picture. The values of idr_pic_id in all the slices of an IDR picture shall remain unchanged (0~65535) */
    int i_poc;                          /* Specifies the picture order count modulo MaxPicOrderCntLsb for the top field of a coded frame or for a coded field */
    int i_redundant_pic_cnt;            /* The value of redundant_pic_cnt shall be greater than 0 for coded slices or coded slice data partitions of a redundant coded picture */
    int b_direct_spatial_mv_pred;       /* Specifies the method used in the decoding process to derive motion vectors and reference indices for inter prediction */
    int b_num_ref_idx_override;         /* Equal to 1 specifies that the num_ref_idx_l0_active_minus1 and num_ref_idx_l1_active_minus1 specified in the referred picture parameter set are overridden for the current slice */
    int i_num_ref_idx_l0_active;        /* Specifies the maximum reference index for reference picture list 0 */
#define MAX_MULTI_REF_FRAME_PLUS1 3
    int i_num_ref_idx_l1_active;        /* Specifies the maximum reference index for reference picture list 1 */
    int i_cabac_init_idc;               /* Specifies the index for determining the initialization table used in the initialisation process for context variables. (0~2) */
    int i_qp;                           /* Specifies the initial value of QPY to be used for all the macroblocks in the slice until modified by the value of mb_qp_delta in the macroblock layer */
    int i_disable_deblocking_filter_idc;/* Specifies whether the operation of the deblocking filter shall be disabled across some block edges of the slice and specifies for which edges the filtering is disabled */
    int i_alpha_c0_offset_div2;         /* Specifies the offset used in accessing the �\ and tC0 deblocking filter tables for filtering operations */
    int i_beta_offset_div2;             /* Specifies the offset used in accessing the �] deblocking filter table for filtering operations */
} slice_t;

int AvcWriteNAL(bs_t*, uchar );
int AvcWriteSPS(bs_t*, sps_t*);
int AvcWritePPS(bs_t*, pps_t*);
int AvcWriteSliceHeader(bs_t*, slice_t*);

#endif /*_H264_ENC_H_*/
