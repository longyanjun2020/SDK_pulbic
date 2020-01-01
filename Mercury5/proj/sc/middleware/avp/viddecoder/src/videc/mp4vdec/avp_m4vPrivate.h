#ifndef M4VPRIVATE_H
#define M4VPRIVATE_H

#include "avp_mvc_decoder.h"
#include "avp_videc_s.h"
#include "avp_common.h"  //uchar
#include "avp_mi_stdlib.h"
#include "avp_copyblkf.h"

#ifdef SUPPORT_WMV
#include "avp_wmv3type.h"
#endif

#ifdef SUPPORT_H263PP
#include "avp_h263ppPrivate.h"
#endif

#define RESYNC_MARKER_FIX
//#define DST_8x8x6
#ifdef DST_8x8x6
#define MERGED_B_VOP_INTERPOLATION
#endif

#define RESYNC_MARKER_FIX
#define FIX_WMV3_BUG

#define _median3(a, b, c) MEDIAN3(a, b, c)
#define _median4(a, b, c, d) MEDIAN4(a, b, c, d)
#define _dual_median3(a, b, c) DUALIMIN(DUALIMAX(DUALIMIN((a), (b)), (c)), DUALIMAX((a), (b)))

#if defined(SUPPORT_WMV)
#define m4v_static
#else
#define m4v_static static
#endif

#define _div_div(a, b)    idiv(ADDSUB((a),(b>>1)),(b))

#define VO_START_CODE   0x8
#define VOL_START_CODE  0x12
#define M4V_GOP_START_CODE  0x1b3
#define VOP_START_CODE  0x1b6
#define SHV_START_CODE  0x020
#define SHV_END_MARKER  0x03f

#define DC_MARKER       0x6b001
#define MOTION_MARKER   0x1f001

#define RECTANGULAR             0
#define BINARY                  1
#define BINARY_SHAPE_ONLY       2
#define GRAY_SCALE              3

#define NO_SPRITE               0
#define STATIC_SPRITE           1
#define GMC_SPRITE              2
//#define RESERVED_SPRITE         3

#ifndef USER_DATA_START_CODE
#define USER_DATA_START_CODE    0x1B2
#endif

#define RESYNC_MARKER           1

#define NOT_VALID      ((char) -2)
#define NOT_CODED      ((char) -1)
#define MB_ERROOR      ((char) -3)
#define INTER           0
#define INTER_Q         1
#define INTER4V         2
#define INTRA           3
#define INTRA_Q         4
#define INTER4V_Q       5
#define STUFFING        7
#define IS_INTRA_OR_INTRA_Q(x) ((x==3) OR (x==4))//(((x-1) & ~1) == 2)
#define IS_INTER_OR_INTER_Q(x) (((x) >> 1) == 0)//(((x) & ~1) == 0)

#define mask(n)  (((CBP_TYPE)(32))>>(n))

#ifdef SUPPORT_WMV
#define ERR_WMV3_INVALID_HEADER     -64
#endif

/* MV mode */
#define    FORWARDMV        0    // cannot be changed, since it is used for indexing.
#define    BACKWARDMV       1    // cannot be changed, since it is used for indexing.
#define    BIDIRECTIONMV    2
#define    DIRECTMV         3    // direct mode, use latest reference mb's mv
#ifdef SUPPORT_WMV
#define    B_INTRA          4    // wmv supports Intra in B-VOP
#endif

/* Field and Frame. Used for indexing of MV buffers. */
#define SBC_TOP_FIELD       0       // Used as index: cannot be changed.
#define SBC_BOT_FIELD       1       // Used as index: cannot be changed.
#define FRAME               0       // Used as index: cannot be changed.

//#define MAKE_RUN_LEVEL_LAST(run, level, last) (((level) << 16) | ((run) << 8) | (last))
#define MAKE_RUN_LEVEL_LAST(run, level, last) PACK16LSB(level, PACK_2_U8(run, last))

typedef union {
    struct {
        uint1 last;
        uint8 run;
        int16 level;
    } a;
    int32 cmp;
} event_t;

//#define DEBUG_NEW_AC_PREDICT    //ken removed related code
//#define DEBUG_QUANT_STORE  // removed by tung

#define swap_int8(x, y) \
{   \
    int8 t;  \
    assert(sizeof(x)==1); \
    assert(sizeof(y)==1); \
    t = (int8) x;  \
    x = y;  \
    *(int8*)&y = t;  \
}

#define swap_int32(x, y) \
{   \
    int32 t;  \
    assert(sizeof(x)==4); \
    assert(sizeof(y)==4); \
    t = (int32) x;  \
    x = y;  \
    *(int32*)&y = t;  \
}

#define swap_frame(frame1, frame2)  \
{   \
    int i;  \
    uchar * tmp;    \
    for (i = 0; i < 3; i++) {   \
        tmp = frame1[i];    \
        frame1[i] = frame2[i];  \
        frame2[i] = tmp;    \
    }   \
}

#define decode012(bs, ret) {\
    ret = getbits(bs, 1);   \
    if (ret)   \
        ret = getbits(bs, 1) + 1;   \
}

#define SET_1_BIT(a, b, c) CLR_1_BIT(a, b) | ((c)<<(b)))
#define CLR_1_BIT(a, b) ((a) & (~(1<<(b))))
#define SET_2_BIT(a, b, c) CLR_2_BIT(a, b) | ((c)<<(b)))
#define CLR_2_BIT(a, b) ((a) & (~(3<<(b))))
#define SET_3_BIT(a, b, c) CLR_3_BIT(a, b) | ((c)<<(b)))
#define CLR_3_BIT(a, b) ((a) & (~(7<<(b))))

typedef struct {
    uchar blockXformmode[6];
    uchar codedblkpat[6];
} wmva_mbmode;

typedef void (*func_cpblk_p3)(const uchar *src, uchar *dst, int stride);
typedef void (*func_cpblk_p4)(const uchar *src, uchar *dst, int stride, int rounding_f_idx);
typedef void (*func_cpblk_p5)(const uchar *src, uchar *dst, int stride, int rounding, int f_idx);
typedef void (*func_cpblk_p6)(const uchar *src, const uchar *src2, uchar *dst, uchar *dst2, int stride, int type);
typedef void (*func_cpblk_p7)(const uchar *src, const uchar *src2, uchar *dst, uchar *dst2, int stride, int rounding, int f_idx);

// remove this
#ifdef SUPPORT_WMV
typedef struct {
    I8_WMV    chFlag[6];
} LOOPF_FLAG;
#endif

typedef struct _mp4_header
{
#ifdef SUPPORT_WMV
    // divx
    uint3 rl_luma_table_index;
    uint3 rl_chroma_table_index;
    uint1 dc_table_index;
    uint2 mv_table_index;
    int16 slice_mb_height;
    int16 slice_next_mb_ypos;

    uint32 fps;
    uint32 bitrate;
    uint1 use_skip_mb_code;
    uint1 flipflop_rounding;
    // wmv1
    uint1 per_mb_rl_table;
    uint1 inter_intra_pred;
    uint3 inter_intra_code;
    uint5 esc_level_len;
    uint4 esc_run_len;


    // wmv3 : sequence level
    // PROFILE
    uint2 wmv3_profile;
    // INTERLACE
    uint1 use_interlaced;
    // SPRITEMODE
    // alias to m4v->sprite_enabled
    // FRAMERATE
    // alias to divx3->fps
    // BITRATE
    // alias to divx3->bitrate
    // LOOPFILTER
    uint1 loop_filter;
    // X8INTRA    1
    uint1 wmv_x8intra;
    // MULTIRES    1
    // alias to m4v->rrv_enable
    // FASTTX    1
    uint1 fast_tx;
    // FASTUVMC    1
    uint1 fast_uvmc;
    // BROADCAST
    uint1 broadcast;
    // DQUANT    2
    uint2 wmv3_quantmode;
    // VSTRANSFORM
    uint1 use_vstransform;
    // DCTTABSWITCH
    uint1 dcttab_switch;
    // OVERLAP    1
    uint1 use_overlap_transform;
    // STARTCODE
    uint1 wmv3_startcode;
    // PREPROC
    uint1 use_pre_process;
    // NUMBFRAMES
    uint3 num_bframes;
    // QUANTIZER
    uint2 quantizer_mode;
    // FRAMEINTERP
    uint1 use_frame_interp;
    // RELEASECOONTENT
    uint1 rel_content;

    // wmv3 : vop level
    // INTERPFRM
    uint1 frame_interp;
    // FRMCNT
    uint8 frame_count;
    // PREPROCFRM
    uint1 pre_process;
    uint1 pre_process_p;
    uint1 pre_process_b;

    // PTYPE
    // alias to m4v->vop_coding_type
    // BFRACTION
    uint8 b_fraction;
    // BF
    // PQINDEX
    uint8 pqindex;
    // HALFQP
    // PQUANTIZER
    // MVRANGE
    uint8 mv_range;
    // RESPIC
    uint2 rrv_vop;
    // RESPIC2
    // INTERLCF
    // alias to m4v->interlaced
    // MVMODE
    uint3 wmv3_mvmode;
    // MVMODE2
    // INTCOMP
    uint1 wmv3_intcomp;
    // CBPTAB
    char wmv3_cbptab;
    // LUMSCALE
    uint7 wmv3_lumscale;  //GET_PUT_SYMBOL(hp->hdr4.wmv3_lumshift, 1);  unknown
    // LUMSHIFT
    uint7 wmv3_lumshift;
    // MVTAB
    // alias to divx3->mv_table_index
    // TTMBF
    uint1 wmv3_per_mb_vstransform;
    // TTMFRM
    uint2 wmv3_vstransform;
    // X8IF
    uint1 x8if;
    // DCTACMBF
    // alias to divx3->per_mb_rl_table
    // DCTACFRM
    // alias to divx3->rl_chroma_table_index
    // DCTACFRM2
    // alias to divx3->rl_luma_table_index
    // DCTDCTAB
    // alias to divx3->dc_table_index

    // DQUANTFRM
    uint1 wmv3_dquantfrm;

    uint1 wmv_3qp;

    uchar wmv3_ctinterlaced;
    char wmv3_ctmvmode;
    char wmv3_ctdirectmv;
    char wmv3_ctskipmb;
    CBP_TYPE intra_cbp;
    CBP_TYPE intra_cbp_prv;
    CBP_TYPE intra_cbp_m;
    CBP_TYPE intra_cbp_prv_m;

    //char wmv3_acpred_mb; // use ac_pred_flag instead.

    uint8 wmv3_ttmb; // 0~1:wmv3_subblk_pat, 2~3:wmv3_vstransform, 4:??? 7:wmv3_subblk_chx

    uint1 wmv3_subblk_chx;
    uint2 wmv3_subblk_pat;

    uint2 wmv3_ttmb_index;

    // wmv3 : vopdquant
    // DQUANTFRM
    // DQPROFILE
    uint1 wmv3_per_mb_dquant;
    // DQBILEVEL
    uint1 wmv3_dqbilevel;
    // PQDIFF
    // ABSPQ

    uint1 overlap_transform;
    char _align_1;
    // DQSBEDGE
    int wmv3_altedges;

    // for b-vop
    uchar wmv3_b_index;
    uchar wmv3_TRD;
    uchar wmv3_TRB;
    char _align_2;
    int8 wmv3_b_ivop;

    // wmv2 vol
    uint1 wmv2_vol_mixedpel;
    uint1 wmv2_vop_mixedpel;
    uint1 wmv2_mb_mixedpel;
    uint1 wmv2_vol_hybridmv;

    // wmv2 vop
    uint1 wmv2_nonflatquant;
    uint1 x8if_flatmode;
    uint1 x8if_vld_mode;
    uint1 x8if_vldused;
    uint8 x8if_vld_index[8];
    uint32 x8if_invdcstep;
    uint32 x8if_invdcstepc;

    // wmva vol
    uint16 wmva_max_width;
    uint16 wmva_max_height;
    uint3 wmva_level;
    uint1 wmva_use_postproc;
    uint1 wmva_use_frame_cnt;
    uint1 use_wmva_hrd;
    uint8 wmva_hrd_num_buckets;

    // wmva entry point layer
    uint1 wmva_use_panscan;
    uint1 wmva_extmv;
    uint1 wmva_extdmv;
    /* Here is 64 bype aligned */
    uint1 wmva_use_rangemapy;
    uint1 wmva_use_rangemapc;
    uint5 wmva_rangemapy_val;
    uint5 wmva_rangemapc_val;
    uint1 wmva_use_rangemapy_p;
    uint1 wmva_use_rangemapc_p;
    uint5 wmva_rangemapy_val_p;
    uint5 wmva_rangemapc_val_p;

    // wmva vop
    uint2 wmva_postproc;
    uint2 wmva_condover;
    char wmva_acpredmode;
    char wmv3_condovermode;
    uint1 vop_overlap_transform;

    // wmva for interlaced mode
    int1 wmva_refdist_flag;
    char wmva_fieldtxmode;
    int1 wmva_field_transform_flag;
    int8 wmva_dmv_range;
    char wmva_mbmode_table_index;
    int2 wmva_2mvbptab;
    int2 wmva_4mvbptab;
    int  wmva_reference_frame_dist;
    char wmva_first_b_ivop;
    char wmva_second_b_ivop;
    int1 repeat_first_field;
    int1 wmva_numref;
    int1 wmva_use_most_recent_field;
    int1 wmva_intcomp_top;
    int1 wmva_intcomp_bottom;
    char wmva_ctforwardmb;
    char wmva_frame_type;
    char wmva_current_field;
    char wmva_current_temporal_field;
    char wmva_prev_spatial_field;
    short wmva_lumscale_top;
    short wmva_lumshift_top;
    short wmva_lumscale_bottom;
    short wmva_lumshift_bottom;
    int  wmva_MaxZone1ScaledFarMVX;
    int  wmva_MaxZone1ScaledFarMVY;
    int  wmva_Zone1OffsetScaledFarMVX;
    int  wmva_Zone1OffsetScaledFarMVY;
    int  wmva_FarFieldScale1;
    /* Here is 64 byte aligned */
    int  wmva_FarFieldScale2;
    int  wmva_NearFieldScale;

    int  wmva_MaxZone1ScaledFarMVXB;
    int  wmva_MaxZone1ScaledFarMVYB;
    int  wmva_Zone1OffsetScaledFarMVXB;
    int  wmva_Zone1OffsetScaledFarMVYB;
    int  wmva_FarFieldScale1B;
    int  wmva_FarFieldScale2B;
    int  wmva_NearFieldScaleB;
    int8  _align1[36];
    int8  _align;
    wmva_mbmode mbmode;
#endif

    // vol
    uint2 shape;
    uint2 sprite_enable;
    uint4 quant_precision;
    int time_increment_resolution;
    int time_increment_bit;
    int fixed_vop_rate;
    int fixed_vop_time_increment;
    uint1 quant_type;
    uint1 quarter_sample;
    uint1 complexity_estimation_disable;
    uint1 resync_marker_disable;
    uint1 data_partitioning;
    uint1 reversible_vlc;
    uint1 rrv_enable; // reduced_resolution_vop_enable

    //sprite
    uint6 warping_points;
    uint6 s_warping_points;
    uint2 warping_accuracy;
    uint1 brightness_change;
    uint1 low_latency_sprite;
    uint1 mcsel;

    // svh
    uint8 temporal_reference;
    uint1 split_screen_indicator;
    uint1 document_camera_indicator;
    uint1 full_picture_freeze_release;

    // gob
    uint5 gob_number;
    uint5 gob_number_conceal_marker;
    uint16 first_row_in_gob;

    // gop
    int time_code;

    // vop
    uint3 intra_dc_vlc_thr;
    uint1 rounding_type;
    int time_base;

    int modulo_time_base;
    uint32 time_inc;

    uint1 top_field_first;
    uint1 alt_vertical_scan;    // alternate_vertical_scan_flag
    uint1 use_intra_dc_vlc;
    uint1 first_coded_mb;
    uint3 fcode_for;
    uint3 fcode_bak;

    // video packet
    MBINDEX_TYPE mb_number;

    /* Here is 64 byte aligned */

    // macroblock
    uint1 ac_pred_flag;
    uint8 predict_dir;
    CBP_TYPE cbp;
    int8 mvmode;

    // interlaced information
    uint1 dct_type;
    uint1 field_prediction;
#ifdef SUPPORT_M4VASP
    uint1 forward_top_field_ref;
    uint1 forward_bottom_field_ref;
    uint1 backward_top_field_ref;
    uint1 backward_bottom_field_ref;
#endif
    int8 resync_length;

    // extra/derived
    int16 num_mb_in_gob; // shv
    uint8 num_gobs_in_vop; // shv

#ifdef RESYNC_MARKER_FIX
    char resync_length_vp;
#endif

    uint1 modb1;   // for direct with no motion vector
    // for mp4v datapartitioning mode
    short *dp_store;
    QUANT_TYPE *dp_store_quant;
    DCTCOEFF_TYPE *dp_store_dc;

#ifdef SUPPORT_FLV1
#define H263_FLV_ESC_MODE hp->hdr4.h263_flv
    int1 h263_flv; // 0, 1: H.263 normoal mode, 2~: flv1 escape mode
    int1 dropable;
    int1 unlimited_unrestricted_motion_vectors;
#else
#define H263_FLV_ESC_MODE  0
#endif

    uchar *block_addr[6]; // to store each block address

    uint1 default_intra_quant;
    uint1 default_inter_quant;
    // in order to keep the end of this sturcute 64-byte aligned
#ifdef SUPPORT_WMV
    char _align_64[38];
#else
    char _align_64[6];
#endif
    uint8 intra_quant_matrix[64];
    uint8 inter_quant_matrix[64];
} mp4_header;


typedef struct {
    int1 mv_outside_frame;
    int1 long_vectors;
    int1 syntax_arith_coding;
    int1 adv_pred_mode;

    int1 overlapping_MC;
    int1 use_4mv;
    int1 pb_frame;
    int1 advanced_intra_coding;
    int1 deblocking_filter_mode;
    int1 slice_structured_mode;
    int1 reference_picture_selection_mode;
    int1 independently_segmented_decoding_mode;
    int1 alternative_inter_VLC_mode;
    int1 modified_quantization_mode;
    int1 reference_picture_resampling_mode;
    int1 reduced_resolution_update_mode;
    int1 unlimited_unrestricted_motion_vectors;
    int1 SSS_rectangular_slices;
    int1 SSS_arbitary_slice_ordering;
    int enhancement_layer_num;
    int reference_layer_number;
    int3 MF_of_reference_picture_selection;
    int1 TRPI;
    int16 temporal_reference_for_prediction;
    int2 BCI;
    int5 quant;

    // MB-level
    int INTRA_AC_DC_index;
    int INTRA_AC_DC;
    QUANT_TYPE quant_h[E_MAX_MBC+1];
    QUANT_TYPE quant_v[E_MAX_MBC+1];
    QUANT_TYPE quant_v_top[E_MAX_MBC+1];
} h263pp_header;

typedef struct _mvinfo {
    int16 fcode;
    MV_TYPE scale_fac;
    MV_TYPE high;
    MV_TYPE low;
    MV_TYPE range;
} mvinfo;

#if defined(SUPPORT_M4VASP) || defined(SUPPORT_H263PP)
#define _4MV_BVOP_
#endif
typedef struct _mbmode {
    int1 not_coded;
#ifdef _4MV_BVOP_
    int1 mb4mv;
#endif
#ifdef SUPPORT_M4VASP
    int1 field_mv;
    int1 forward_top;   // forward_top_field_ref
    int1 forward_bottom;  // forward_bottom_field_ref
#endif
} mbmode;

#define RESET_DC_STORE_LEFT(dc_reset) \
{ \
    uint32 *RESTRICT p2    = (uint32 *) &hp->dc_store_left[0]; \
    uint16 *RESTRICT p2_16 = (uint16 *) &hp->dc_store_left[0]; \
    p2[0] = \
    p2[2] = PACK16LSB(dc_reset, dc_reset); \
    p2_16[8] = p2_16[10] = dc_reset; \
}

#define RESET_DC_STORE_TOP(dc_reset) \
{ \
    int i; \
    uint32 *RESTRICT p1 = (uint32 *) &hp->dc_store_top[1][0]; \
    for (i = 0; i < hp->h.vinfo.mb_width; i++) { \
        p1[0] = \
        p1[1] = PACK16LSB(dc_reset, dc_reset); \
        p1 += 2; \
    } \
}

#define MOVE_DC_LEFT_TO_TOP(p_dc_store_top, p_dc_store_left) \
{ \
    uint32 *RESTRICT p1 = (uint32 *)(p_dc_store_top); \
    uint32 *RESTRICT p2 = (uint32 *)(p_dc_store_left); \
    uint16 *RESTRICT p2_16 = (uint16 *)(p_dc_store_left); \
    p1[0] = p2[2]; \
    p1[1] = PACK16LSB(p2[5], p2[4]); \
    p2_16[1] = p2_16[3]; \
    p2[2] = p2[3]; \
    p2_16[8]  = PACK16MSB(0, p2[4]); \
    p2_16[10] = PACK16MSB(0, p2[5]); \
}

#define MOVE_DC_NOW_TO_TOP(p_dc_store_top, p_dc_store_left) \
{ \
    uint32 *RESTRICT p1 = (uint32 *)(p_dc_store_top); \
    uint32 *RESTRICT p2 = (uint32 *)(p_dc_store_left); \
    p1[0] = p2[3]; \
    p1[1] = PACK16MSB(p2[5], p2[4]); \
}

#define RESET_AC_STORE_LEFT() \
    MY_MEMSET(hp->ac_store_left, 0, sizeof(hp->ac_store_left));

#define RESET_AC_STORE_TOP(element_num) \
    MY_MEMSET(hp->ac_store_top, 0, sizeof(DCTCOEFF_TYPE)*(element_num)*4*7);

#define RESET_MV_LEFT() SET_2_DWORD(&hp->MV_left.b4[FORWARDMV][0].cmp, 0)

#define RESET_B_PRED_MV() \
    MY_MEMSET(hp->pred_mv, 0, sizeof(hp->pred_mv));

#define MOVE_4_DWORD(dst, src) \
{ \
    uint32 *RESTRICT lsrc = src; \
    uint32 *RESTRICT ldst = dst; \
    ldst[0] = lsrc[0]; \
    ldst[1] = lsrc[1]; \
    ldst[2] = lsrc[2]; \
    ldst[3] = lsrc[3]; \
}

#define MOVE_3_DWORD(dst, src) \
{ \
    uint32 *RESTRICT lsrc = (uint32 *)src; \
    uint32 *RESTRICT ldst = (uint32 *)dst; \
    ldst[0] = lsrc[0]; \
    ldst[1] = lsrc[1]; \
    ldst[2] = lsrc[2]; \
}

#define MOVE_2_DWORD(dst, src) \
{ \
    uint32 *RESTRICT lsrc = (uint32 *)src; \
    uint32 *RESTRICT ldst = (uint32 *)dst; \
    ldst[0] = lsrc[0]; \
    ldst[1] = lsrc[1]; \
}

#define MOVE_1_DWORD(dst, src) \
{ \
    uint32 *RESTRICT lsrc = (uint32 *)src; \
    uint32 *RESTRICT ldst = (uint32 *)dst; \
    ldst[0] = lsrc[0]; \
}

#define SET_4_DWORD(dst, val) \
{ \
    uint32 *RESTRICT ldst = (uint32 *)dst; \
    ldst[0] = val; \
    ldst[1] = val; \
    ldst[2] = val; \
    ldst[3] = val; \
}

#define SET_3_DWORD(dst, val) \
{ \
    uint32 *RESTRICT ldst = (uint32 *)dst; \
    ldst[0] = val; \
    ldst[1] = val; \
    ldst[2] = val; \
}

#define SET_2_DWORD(dst, val) \
{ \
    uint32 *RESTRICT ldst = (uint32 *)dst; \
    ldst[0] = val; \
    ldst[1] = val; \
}


#ifdef _UAMEM_ACCESS_
#define SET_INLOOP_IMB_OMB(imb_val, omb_val) \
{ \
    uchar * RESTRICT wmv3_inloop_imb = hp->wmv3_inloop_imb; \
    uchar * RESTRICT wmv3_inloop_omb = hp->wmv3_inloop_omb; \
 \
    CONVUINTXTOUINT32(wmv3_inloop_imb[0]) = imb_val; \
    CONVUINTXTOUINT16(wmv3_inloop_omb[BLK0IDX]) = (uint16)omb_val; \
    CONVUINTXTOUINT16(wmv3_inloop_omb[BLK2IDX]) = (uint16)omb_val; \
    wmv3_inloop_omb[BLK4IDX] = wmv3_inloop_omb[BLK5IDX] = (uint8)omb_val; \
}
#else
#define SET_INLOOP_IMB_OMB(imb_val, omb_val) \
{ \
    uchar * RESTRICT wmv3_inloop_imb = hp->wmv3_inloop_imb; \
    uchar * RESTRICT wmv3_inloop_omb = hp->wmv3_inloop_omb; \
 \
    CONVUINTXTOUINT32(wmv3_inloop_imb[0]) = imb_val; \
    wmv3_inloop_omb[BLK0IDX] = wmv3_inloop_omb[BLK1IDX] = (uint8)omb_val; \
    CONVUINTXTOUINT16(wmv3_inloop_omb[BLK2IDX]) = (uint16)omb_val; \
    wmv3_inloop_omb[BLK4IDX] = wmv3_inloop_omb[BLK5IDX] = (uint8)omb_val; \
}
#endif

#define SET_MV_CUR_FORWARD(mv_val) \
{ \
    int32* RESTRICT p; \
    p = &hp->MV_now.b4[FORWARDMV][0].cmp; \
    p[0] = p[1] = p[2] = p[3]  = mv_val; \
}
#define SET_MV_CUR_BACKWARD(mv_val) \
{ \
    int32* RESTRICT p; \
    p = &hp->MV_now.b4[BACKWARDMV][0].cmp; \
    p[0] = p[1] = p[2] = p[3]  = mv_val; \
}

#define WMV_HANDLE  M4V_HANDLE

#define INDEX_MBR_MBC_4(idx1, idx2, idx3) ((idx1)*((MAX_MBC)<<2)+((idx2)<<2)+idx3)
#define INDEX_MBR_MBC(idx1, idx2) ((idx1)*(MAX_MBC)+(idx2))

typedef struct {

    VID_HANDLE h;

#if defined(SUPPORT_H263) || defined(SUPPORT_WMV)
    // 32 bit aligned point
    frameobj frames_aux1;
    frameobj frames_aux2;

    //it'd better to be 64-byte aligned
    // in order to keep block 64-byte aligned
    short block[384];   // 64*6

#ifdef DST_8x8x6
    uchar mcbuf1[8*8*6]; //for forward mc
    uchar mcbuf2[8*8*6]; //for backward mc
    uchar mcbuf3[16*17]; //tmp; alloc on stack or declared as local variables
#endif

    // 64 byte-aligned
    mp4_header hdr4;
#ifdef SUPPORT_H263PP
    h263pp_header hh263pp;
#endif

#if defined(SUPPORT_M4V) || defined(SUPPORT_WMV) || defined(SUPPORT_H263)
    char  *mbtype_prv; // used by mp4v/divx3/wmv1
    char  mbtype_left;
    char  mbtype;
    QUANT_TYPE quantizer;
#endif

#ifdef SUPPORT_WMV
    uint16     _2byte_align;
    // for wmv3
    QUANT_TYPE def_quantizer;
    QUANT_TYPE alt_quantizer;
    QUANT_TYPE d_quantizer;
    uint32  _4byte_align;
    uchar wmv3_mbtype[MAX_MBR*MAX_MBC];

    CBP_TYPE wmv3_intracbp[E_MAX_MBC+1]; // used by wmv2 and after
    CBP_TYPE wmva_intracbp_m[E_MAX_MBC+1];
    // 2erin: try to merge into mbmode
    wmva_mbmode interlace_mbmode[MAX_MBR*MAX_MBC];

    int _4byte_align_1;

    // overlapped transform buffer
    // line buffer for overlapped transform
    // 2 lines for even-index MB and 2 for odd-index MB, can be changed to one line only.
    short wmv3_oty[2*E_MAX_MBC*16];
    short wmv3_otc[2][2*E_MAX_MBC*8];

    // MB buffer for overlapped transform progressive and interlace field
    // Y-MB
    // OO | OOOOOOOO OOOOOOOO  <= wmv3_otmbl0y[0]
    // OO | OOOOOOOO OOOOOOOO  <= wmv3_otmbl0y[18]
    // ----------------------
    // OO | OOOOOOOO OOOOOOOO  <= wmv3_otmbl0y[18*2]
    // OO | OOOOOOOO OOOOOOOO  <= wmv3_otmbl0y[18*3]
    // XX | XX    XX XX    XX  <= wmv3_otmbl1y[0]
    // XX | XX    XX XX    XX  <= wmv3_otmbl1y[10]
    // XX | XX    XX XX    XX  <= wmv3_otmbl1y[10*2]
    // XX | XX    XX XX    XX  <= wmv3_otmbl1y[10*3]
    // OO | OOOOOOOO OOOOOOOO  <= wmv3_otmbl0y[18*4]
    // OO | OOOOOOOO OOOOOOOO  <= wmv3_otmbl0y[18*5]
    //    |
    // OO | OOOOOOOO OOOOOOOO  <= wmv3_otmbl0y[18*6]
    // OO | OOOOOOOO OOOOOOOO  <= wmv3_otmbl0y[18*7]
    // XX | XX    XX XX    XX  <= wmv3_otmbl1y[10*4]
    // XX | XX    XX XX    XX  <= wmv3_otmbl1y[10*5]
    // XX | XX    XX XX    XX  <= wmv3_otmbl1y[10*6]
    // XX | XX    XX XX    XX  <= wmv3_otmbl1y[10*7]


    // MB buffer for overlapped transform progressive and interlace frame
    // Y-MB
    // OO | OOXXXXOO OOXXXXOO  <= wmv3_otmbl0y[0]
    // OO | OO    OO OO    OO  <= wmv3_otmbl0y[10]
    // OO | OO    OO OO    OO  <= wmv3_otmbl0y[10*2]
    // OO | OO    OO OO    OO  <= wmv3_otmbl0y[10*3]
    // OO | OO    OO OO    OO  <= wmv3_otmbl0y[10*4]
    // OO | OO    OO OO    OO  <= wmv3_otmbl0y[10*5]
    // OO | OO    OO OO    OO  <= wmv3_otmbl0y[10*6]
    // OO | OO    OO OO    OO  <= wmv3_otmbl0y[10*7]
    // ---------------------------------------------
    // OO | OO    OO OO    OO  <= wmv3_otmbl0y[10*8]
    // OO | OO    OO OO    OO  <= wmv3_otmbl0y[10*9]
    // OO | OO    OO OO    OO  <= wmv3_otmbl0y[10*10]
    // OO | OO    OO OO    OO  <= wmv3_otmbl0y[10*11]
    // OO | OO    OO OO    OO  <= wmv3_otmbl0y[10*12]
    // OO | OO    OO OO    OO  <= wmv3_otmbl0y[10*13]
    // OO | OO    OO OO    OO  <= wmv3_otmbl0y[10*14]
    // OO | OO    OO OO    OO  <= wmv3_otmbl0y[10*15]
    //

    short wmv3_otmbl0y[10*16];
    short wmv3_otmbl1y[10*4*2];
    short wmv3_otmbl0c[2][6*8];
    short wmv3_otmbl1c[2][6*4];

    mvpair pMotionY[MAX_MBR*MAX_MBC*4];
    mvpair pMotionC[MAX_MBR*MAX_MBC];
    mvpair pMotionY_b[MAX_MBR*MAX_MBC*4];
    mvpair pMotionC_b[MAX_MBR*MAX_MBC];
    LOOPF_FLAG pLoopFilterFlags[MAX_MBR*MAX_MBC];
    char iNumBFrames;
    int iBFrameReciprocal;
    int iBDenominator;
    int iBNumerator;

#ifdef _WMVA_FILTER_OPT_
    uchar wmv3_inloop_ver_y_upper[E_MAX_MBC]; // to support WMVA
#endif
#ifndef _WMVA_FILTER_OPT_
    // FIXME: fails on rotated video
    int16 slice_next_mb_ypos_array[M4VDEC_MAX_MB_HEIGHT];
    int16 current_slice_num;
    MBINDEX_TYPE save_mb_ypos_array[M4VDEC_MAX_MB_HEIGHT];
#endif
    uint8 wmv2_orient_prv;
    uint8 wmv2_orient_diff;
    uint8 wmv2_orient_l[E_MAX_MBC*2+1];
    uint8 wmv2_orient_l12[E_MAX_MBC];
    uint8 wmv2_N_AC_prv;
    uint8 wmv2_N_AC_l[E_MAX_MBC*2+1];

    int _4byte_align_2;
    short wmv3_cmv_cur[2];
    short wmv3_cmv_line[E_MAX_MBC+1][2];

    uint8 wmva_rangemapy[256];
    uint8 wmva_rangemapc[256];
#endif // SUPPORT_WMV

#if defined(SUPPORT_WMV) || defined(SUPPORT_H263PP)
    // in-loop filter
    uchar wmv3_inloop_imb[3+1];  /*
                                    4 byte aligned point
                                    3 elements are necessary, the last one is for quick reset
                                    inner 8x8 Y:(0 1), Ch:(2)
                                    0: (blk_0 blk_1)
                                    1: (blk_2 blk_3)
                                    2: (blk_cb blk_cr)

                                         -----------------------------
                                         |      |b5    |      |b1    |
                                         |      |      |      |      |
                                         |  b7  |  b6  |  b3  |  b2  |
                                         -----------------------------
                                         |      |      |      |      |
                                         |      |b4    |      |b0    |
                                         |      |      |      |      |
                                         -----------------------------
                                 */
    uchar wmv3_inloop_omb[14];   /*
                                     b7   b8
                                    ---------
                                  b3|   |   |b1           0 1       8      11
                                    ---------           2 3 4    9 10   12 13
                                  b2|   |   |b0         5 6 7
                                    ---------
                                     b5   b4
                                 */
    uchar wmv3_inloop_ver_y[E_MAX_MBC*4+1];
    uchar wmv3_inloop_ver_c[E_MAX_MBC*2+1];
    uchar wmv3_inloop_hor_y_last[E_MAX_MBC];
    uchar wmv3_inloop_hor_y[E_MAX_MBC*2];
    uchar wmv3_inloop_hor_c_last[E_MAX_MBC];
    uchar wmv3_inloop_hor_c[E_MAX_MBC*1];
#endif // SUPPORT_WMV

#if defined(SUPPORT_M4V) || defined(SUPPORT_WMV) || defined(SUPPORT_H263)
    QUANT_TYPE  *quant_store_prv;
    QUANT_TYPE  quant_store_left;

    int _4byte_align_3;
    DCTCOEFF_TYPE ac_store_left[4][7]; // store AC coffs of the left MB.
    DCTCOEFF_TYPE (*ac_store_top)[4][7];

    // v1 <-- use this mode
    //  Y0  Y1 |   Y2  Y3
    //  Y4  Y5 |   Y6  Y7
    // Cb8 Cb9 | Cr10 Cr11
    // v2
    //  Y0  Y1 |   Y2  Y3
    //  Y4  Y5 |   Y4  Y5
    //     Cb4 |      Cr4
    //     Cb5 |      Cr5

    DCTCOEFF_TYPE dc_store_left[12];
    // 0: Y0, 1:Y1, 2:Cb, 3:Cr
    DCTCOEFF_TYPE (*dc_store_top)[4];

    /* motion vector related */
    mvinfo mvinfo_for, mvinfo_bak;    // store variables for diff mv decoding.

    union {
        mvpair b1[2];
        mvpair b4[2][4]; // may change to b4[1][MAX_MBC+1][4], check it by ken
    } MV_now;
    union {
        mvpair b1[2];
        mvpair b4[1][4]; // store forward mv only
    } MV_left;
    union {
        mvpair b1[2][E_MAX_MBC+1];
        mvpair b4[1][E_MAX_MBC+1][4]; // store forward mv only
    } MV_cur;
    // 1st index: forward, backward; 2nd index: top-, bottom-field.
    mvpair pred_mv[2][2];

    // Interlaced MV. 1st index: Forward ,backward; 2nd index: top-, bottom-field.
    // only used by field mb in mp4v for use by motion compensation.
    mvpair Mv16x8[2][2];
#endif

    // Co-located MV's.
    // 1st and 2nd index: mb position (x, y in mb unit).
    // 3nd index: block number in a macroblock. If field mv, indexed by
    //       TOP_FIELD and BOTTOM_FIELD.
#if defined(SUPPORT_M4V) || defined(SUPPORT_WMV) || defined(SUPPORT_H263PP)
    // for colocated mv in mpeg-4/h.263pp/wmv
    // for datapartitioning mode in mpeg-4
    union {
        mvpair *b1;
        mvpair (*b4)[4]; // only used by mp4v
    } CoMV;
#endif

#ifdef SUPPORT_WMV
    // wmv3
    mvinfo mvinfo_y_for;
#endif

#ifdef SUPPORT_M4VASP
    // Sprite related
    int32 du[4], dv[4];
    int32 voprp[4][2], sptrp[4][2], vsptp[3][2];
    int sptoff[2][2];   // 0: Y, 1: C
    int sptshift[2];    // 0: Y, 1: C
    int sptdelta[2][2]; // 0:0 (X:X), 0:1 (X:Y), 1:0 (Y:X), 1:1 (Y,Y)
    int32 BChgFactor;   // Brightness change factor
    int32 sptR, sptAlpha, sptBeta, sptRho;
    int32 p2W, p2H;
#endif

    int8    mb_in_vop_length;

#ifdef SUPPORT_WMV
    frameobj frames_for_r;
    frameobj frames_bak_r;

    void *packet_for_r;
#endif

    /*
    For B-VOP decoding.
    */
#if defined(SUPPORT_M4V) || defined(SUPPORT_WMV) || defined(SUPPORT_H263PP)
    mbmode *mbmd_buf; // TODO: packed into 1 byte
#endif

    /* Time information */
    // modulo time, in sec unit.
    int modulo_base_dec, modulo_base_dsp;    // of most recently decoded / displayed I- or P-VOP.
    //int old_modulo_base_dec, old_modulo_base_dsp;
    // time of forward ref, backward ref and current VOP, in clock tick unit.
    int time_for, time_bak, time_cur;

    /* For interlaced direct mode MC */
    int FirstBVop;
    int Tframe;

    event_t (* GetDCTCoeff_I)(BITSBUF *bs);
    event_t (* GetDCTCoeff_N)(BITSBUF *bs);

    // function pointers
#ifdef INDEX_ROUNDING
    CopyAreaProcPtr CopyFunctions[16];
    //(((rounding_type<<2) | (yh<<1) | (xh)) << 2) | align
    CopyAreaProcPtr Copy16x8Func[32];
    CopyAreaProcPtr Copy8x4Func[32];
#else
    CopyAreaProcPtr CopyFunctions[8];
    //(((yh<<1) | (xh)) << 2) | align
    CopyAreaProcPtr Copy16x8Func[16];
    CopyAreaProcPtr Copy8x4Func[16];
#endif

#ifdef SUPPORT_WMV

#if !defined(DST_8x8x6)
    // fake frame buffer for storing backward reference blocks, which is
    // to be interpolated with forward reference blocks to construct reference
    // blocks, when bidirection or direct mc mode is used.
    uchar *frame_fake[3];
#endif

    // for divx3, wmv3
    //      b3
    // |-------
    // |    b2
    // | b1 b0
    CBP_TYPE  cbp_store_row_new[E_MAX_MBC+1];

    Void_WMV (*g_8x8IDCTDec) (int16 * piDst, const int16 * piSrc);
    Void_WMV (*g_8x4IDCTDec) (int16 * piDstBuf, const int16 * rgiCoefReconBuf);
    Void_WMV (*g_4x8IDCTDec) (int16 * piDstBuf, const int16 * rgiCoefReconBuf);
    Void_WMV (*g_4x4IDCTDec) (int16 * piDstBuf, const int16 * rgiCoefReconBuf);
    Void_WMV (*g_8x8IDCTDec_addblock) (int16 * src, uint32 * lDst, int lStride);
    Void_WMV (*g_8x4IDCTDec_addblock) (int16 * piDstBuf, uint32 * lDst, int lStride);
    Void_WMV (*g_4x8IDCTDec_addblock) (int16 * piDstBuf, uint32 * lDst, int lStride);
    Void_WMV (*g_4x4IDCTDec_addblock) (int16 * piDstBuf, uint32 * lDst, int lStride);
#endif // SUPPORT_WMV

#endif // SUPPORT_H263 || SUPPORT_WMV

    int pb_packed;
} M4V_HANDLE;

/* Functions in mp4_recon.c */

extern err_type (* const MotionCompPVop[16])(M4V_HANDLE *hp, int bx, int by);
extern err_type (* const MotionCompBVop[16])(M4V_HANDLE *hp, int bx, int by);
extern err_type (* const TextureDecoding[])(M4V_HANDLE *hp);

err_type ATTR_INST16 MotionCompWithForRefFrame(M4V_HANDLE *hp, int bx, int by);
err_type MotionCompWithForRefField(M4V_HANDLE *hp, int bx, int by);
err_type MotionCompWithBakRefFrame(M4V_HANDLE *hp, int bx, int by);
err_type MotionCompWithBakRefField(M4V_HANDLE *hp, int bx, int by);
err_type MotionCompBiDirFrame(M4V_HANDLE *handle, int bx, int by);
err_type MotionCompBiDirField(M4V_HANDLE *handle, int bx, int by);
err_type MotionCompWith4MV(M4V_HANDLE *hp, int bx, int by);
err_type MotionCompFrameDirect(M4V_HANDLE *handle, int bx, int by);
err_type MotionCompFieldDirect(M4V_HANDLE *handle, int bx, int by);

#ifndef INDEX_ROUNDING
void ATTR_INST16 mcSetEngine(M4V_HANDLE *hp, int rounding_type);
#endif

void ATTR_INST16 init_block_address(M4V_HANDLE *hp);

void m4v_init_decoder(
    VID_HANDLE *handle,
    VID_SETUP *setup,
#ifndef DST_8x8x6
    void *mp4_fake_buffers
#endif
    );

/* Function in sprite.c */
err_type GlobalMotionComp(M4V_HANDLE *hp, int bx, int by);

#define DIVX_VER_BUILD(ver,build) (((ver)<<16)|(build))
int m4vSigDivx(VID_HANDLE * hp, int ver, int build);
//int m4vSigMsmpeg4(M4V_HANDLE * hp, int ver);
int determine_header_code_mode(VID_HANDLE * hp);

void DuplicateVOP(M4V_HANDLE *handle);  // For not-coded VOP.

int m4vDecVOP(M4V_HANDLE *hp, err_type err_skip);

err_type vid_vopskip_process(VID_HANDLE* hp, int skip_frame
#ifdef SUPPORT_AVC
                        , VID_SETUP* setup
#endif
                        );
err_type vid_vopskip_process_2(VID_HANDLE* hp);

#ifdef _UV_PLANAR_
void make_edge_new_planar(uchar *frame_pic, int width, int height, int edged_width, int left_top_edge_size);
#endif
// for wmva
void make_edge_new_tight(uchar *frame_pic, int width, int height, int edged_width, int top_edge_size, int left_edge_size, int right_edge_size, int bot_edge_size, int interlaced);

#endif /* M4VPRIVATE_H */
