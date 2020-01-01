#ifndef VIDEC_S_H
#define VIDEC_S_H

#include "avp_common.h"
#include "avp_mvc_decoder.h"
#include "avp_plain.h"
#include "avp_bitsbuf.h"

// default frame buffer alignment
#ifdef _AG_S32_
#define FRAME_Y_START_ALIGN     16
#define FRAME_C_START_ALIGN     16
#define FRAME_Y_STRIDE_ALIGN    16      // must be multiple of 16
#define FRAME_C_STRIDE_ALIGN    16      // must be multiple of 8 and must be divisor of FRAME_Y_STRIDE_ALIGN
#else
#define FRAME_Y_START_ALIGN     64
#define FRAME_C_START_ALIGN     64
#define FRAME_Y_STRIDE_ALIGN    64      // must be multiple of 16
#define FRAME_C_STRIDE_ALIGN    64      // must be multiple of 8 and must be divisor of FRAME_Y_STRIDE_ALIGN
#endif
#ifdef __TCS__
#if FRAME_Y_START_ALIGN<64
#undef FRAME_Y_START_ALIGN
#define FRAME_Y_START_ALIGN 64
#endif

#if FRAME_C_START_ALIGN<64
#undef FRAME_C_START_ALIGN
#define FRAME_C_START_ALIGN 64
#endif
#endif


// for video, we can support mb_width up to E_MAX_MBC while mba_size <= MAX_MBC*MAX_MBR
#define MAX_MBC         M4VDEC_MAX_MB_WIDTH
#define MAX_MBR         M4VDEC_MAX_MB_HEIGHT
#define E_MAX_MBC       (MAX_MBC*5/4)

#define I_VOP       0
#define P_VOP       1
#define B_VOP       2
#define S_VOP       3
#define BI_VOP      4 // 2erin: do not use this, we have wmv3_b_ivop already

#define I_PICTURE   I_VOP
#define P_PICTURE   P_VOP
#define B_PICTURE   B_VOP
#define S_PICTURE   S_VOP

#if !defined(SUPPORT_WMV)
#define MERGED_AC_PREDICT
#endif

//#ifndef _AG_S32_
#define _ZIGZAG_SCAN_TRANSPOSE_
//#endif

#ifdef SUPPORT_AVCMP
#define HIERARCHICAL_B
#define HIERARCHICAL_B_REFINE
#endif

#define ALWAYS_INIT_REORDER_LISTS

// NEW_GET_STRENGTH and INTRA_LEFT_TOP should be enabled simultaneously
//#define NEW_GET_STRENGTH
//#define INTRA_LEFT_TOP

#ifndef SUPPORT_AVCMP
//#define MB_GETSTRENGTH
#endif

//#define _WMVA_FILTER_OPT_

//#define _REPLACE_WMVA_MBTYPE_ // always enabled
//#define COMB_MBTYPE_FIELDTX // always enabled

// if NO_NAL_PEEK is defined, the bitstream buffer will be only scanned once within ViDec
#define NO_NAL_PEEK

// store ref_idx/mv according to the block size, e.g. less than 16 pairs for 16x16 block size.
// now only work in H.264 baseline
#define OPT_GETSTRENGTH


#define QUANT_TYPE      uchar
#define MV_TYPE         int16
#define MV_TYPE_OP      int32

#define CBP_TYPE        uint8
#define PXINDEX_TYPE    short
#define MBINDEX_TYPE    short
#define DCTCOEFF_TYPE   short

#define err_type    int
//#define err_type    short

#define ERR_OK      0
#define ERR_OK_MB_STUFFING     0
#define ERR_OK_MB_SUCCESS      1
#define ERR_OK_NEW_PACKET      2
#define ERR_OK_USER_ABORT      3
#define ERR_SEMANTIC_FOUND    -6
#define ERR_VLC_RUN_LEVEL     -7
#define ERR_VLC_MCBPC         -8
#define ERR_VLC_CBPY          -9
#define ERR_VLC_REFIDX       -10
#define ERR_VLC_MBTYPE       -13
#define ERR_VLC_B8TYPE       -14
#define ERR_VLC_CBP          -15
#define ERR_VLC_CI8PRED      -16
#define ERR_VLC_TOO_MANY_MB  -17
#define ERR_VLC_PCM		     -18
#define ERR_VLD_OVERFLOW     -19
#define ERR_VLC_MV         -32767
#define ERR_SPS              -11
#define ERR_SEQUENCE         -11
#define ERR_PPS              -12
#define ERR_SLICE_HEADER          -21
#define ERR_SLICE_NUM_TOO_LARGE   -22
#define ERR_NAL_TYPE_INCONSISTENT -23
#define ERR_NAL_INVALID           -24
#define ERR_UNEXPECTED_STARTCODE  -25

typedef union _mvpair {
    struct {
        MV_TYPE x;
        MV_TYPE y;
    } a;
    int32 cmp;
} mvpair;

typedef union _u16pair {
    struct {
        uint16 x;
        uint16 y;
    } a;
    uint32 cmp;
} u16pair;

typedef union _u8pair {
    struct {
        uint8 x;
        uint8 y;
    } a;
    uint16 cmp;
} u8pair;

typedef long p2_int16;

typedef struct _PBUF
{
    uint32 bits;
    int32 len;
} PBUF;

#ifdef _AG_S32_
// for mips16
#define MVPAIR_ADD(s, t) ((ICLIPI(((s).a.y + (t).a.y),0x7fff) <<16) | (ICLIPI(((s).a.x + (t).a.x),0x7fff)&0xffff))
#define MVPAIR_SUB(s, t) ((ICLIPI(((s).a.y - (t).a.y),0x7fff) <<16) | (ICLIPI(((s).a.x - (t).a.x),0x7fff)&0xffff))
#define MVPAIR_ADD_PARA3(dst, s, t) \
{ \
    dst.a.y = (s.a.y + t.a.y); \
    dst.a.x = (s.a.x + t.a.x); \
}
//for mips32r2
//#define MVPAIR_ADD(s, t) PACK16LSB(ICLIPI(((s).a.y + (t).a.y),0x7fff), ICLIPI(((s).a.x + (t).a.x),0x7fff))
//#define MVPAIR_SUB(s, t) PACK16LSB(ICLIPI(((s).a.y + (t).a.y),0x7fff), ICLIPI(((s).a.x + (t).a.x),0x7fff))

#else
#define MVPAIR_ADD(a, b) DSPIDUALADD((a).cmp,(b).cmp)
#define MVPAIR_SUB(a, b) DSPIDUALSUB((a).cmp,(b).cmp)
#define MVPAIR_ADD_PARA3(dst, a, b) (dst.cmp = DSPIDUALADD((a).cmp,(b).cmp))
#endif

#define U8PAIR_ADD(a, b) ((a).cmp + (b).cmp)
#define U8PAIR_SUB(a, b) ((a).cmp - (b).cmp)

#define MSB_ASR_2(a) PACK16LSB((int32)(a)>>17, a)
#define LSB_MUL_2(a) (a+PACK16LSB(a, 0))
#define MVPAIR_Y_MUL_2(a) ((a).cmp+PACK16MSB((a).cmp, 0))
#define MVPAIR_Y_DIV_2(a) PACK16LSB(((int32)(a).cmp+MUX((int32)(a).cmp<0,0x10000,0))>>17, (a).cmp)
//#define MVPAIR_Y_DIV_2(a) PACK16LSB(idiv2((int32)(a).y), (int32)(a).x);
#define MVPAIR_Y_ASR_2(a) PACK16LSB((int32)(a).cmp>>17, (a).cmp)

#define U8PAIR_Y_MUL_2(a) ((a).cmp+PACKBYTES(UBYTESEL((a).cmp, 1), 0))
#define U8PAIR_Y_ASR_2(a) PACKBYTES((a).cmp>>9, (a).cmp)

#if defined(_TM5250_) && !defined(_AG_S32_)
#define GET_INT16_FROM_MVPAIR(x16, y16, xy32) x16 = SEX16((xy32).cmp); y16 = (xy32).cmp>>16;
#define GET_UINT16_FROM_PUINT32(x16, y16, pxy32) x16 = PACK16LSB(0, *(uint32*)(pxy32)); y16 = PACK16MSB(0, *(uint32*)(pxy32));
#define GET_UINT8_FROM_PUINT16(x8, y8, pxy16) x8 = UBYTESEL(*(uint16*)(pxy16), 0); y8 = UBYTESEL(*(uint16*)(pxy16), 1);
#else
#define GET_INT16_FROM_MVPAIR(x16, y16, xy32) x16 = (xy32).a.x; y16 = (xy32).a.y;
#define GET_UINT16_FROM_PUINT32(x16, y16, pxy32) x16 = *(uint16*)(pxy32); y16 = *(((uint16*)(pxy32))+1);
#define GET_UINT8_FROM_PUINT16(x8, y8, pxy16) x8 = *(uint8*)(pxy16); y8 = *(((uint8*)(pxy16))+1);
#endif
#define GET_INT16_FROM_INT32(x16, y16, xy32) x16 = SEX16(xy32); y16 = xy32>>16;
#define GET_UINT16_FROM_UINT32(x16, y16, xy32) x16 = PACK16LSB(0, xy32); y16 = PACK16MSB(0, xy32);

typedef struct _frameobj {
    uchar *comp[3]; // y/u/v
    void  *obj;
    uint64  pts;
    QUANT_TYPE *qmap;
    uint32 valid;
    int32 padding_type;
    int16 width;
    int16 height;
} frameobj;

#define setupframeobj(fobj, pic)                \
{                                               \
    (fobj)->comp[0]   = (uchar *)pic->y;        \
    (fobj)->comp[1]   = (uchar *)pic->u;        \
    (fobj)->comp[2]   = (uchar *)pic->v;        \
    (fobj)->pts       = pic->pts;               \
    (fobj)->qmap      = (uchar *)pic->aux_data; \
    (fobj)->obj       = pic->packet;            \
    (fobj)->valid     = pic->valid;             \
}

#define setupdecpicture(_pic, fobj)             \
{                                               \
    _pic->y          = (fobj)->comp[0];         \
    _pic->u          = (fobj)->comp[1];         \
    _pic->v          = (fobj)->comp[2];         \
    _pic->pts        = (fobj)->pts;             \
    _pic->aux_data   = (fobj)->qmap;            \
    _pic->packet     = (fobj)->obj;             \
    _pic->valid      = (fobj)->valid;           \
    _pic->width      = (fobj)->width;           \
    _pic->height     = (fobj)->height;          \
}

#define swap_frameobj(frame1, frame2)           \
{                                               \
    frameobj tmp;                               \
    tmp    = frame1;                            \
    frame1 = frame2;                            \
    frame2 = tmp;                               \
}

typedef struct {
    int16 width;
    int16 height;
    int16 width_in_m16;
    int16 height_in_m16;
    MBINDEX_TYPE   mb_width;
    MBINDEX_TYPE   mb_height;
    MBINDEX_TYPE   mba_size;
    MBINDEX_TYPE   mba;
    MBINDEX_TYPE   mb_xpos;
    MBINDEX_TYPE   mb_ypos;

    MBINDEX_TYPE   save_mb_xpos;
    MBINDEX_TYPE   save_mb_ypos;

    MBINDEX_TYPE   mba_start;
    //MBINDEX_TYPE   _make_32b;
    uint1   uv_packed;
    uint1   _make_32b;

    int16   luma_buf_width;   //coded_picture_width;
    int16   chrom_buf_width;  //chrom_width;
    int16   luma_buf_height;  //coded_picture_height;
    int16   chrom_buf_height; //chrom_height;
    int16   padding_size_y;
    int16   padding_size_uv;

    int16 c_width_in_m8;
    int16 c_height_in_m8;

    uint1 double_v_padding;
    uint8 interlaced;
    uint8 par_width;
    uint8 par_height;
    //uint8 _make_32b;
    // 32 bit aligned point

} vid_info;

typedef struct {

    // codec info
    int32 divx_ver;
    uint8 ms_ver;
    uint8 avc_ver;
    uint8 m2v_ver;
    uint8 rv_ver;
    uint8 m4v_ver;
    uint8 h263_ver;         // 1: H.263 baseline (P0), 2: H.263++ (now support P3 only)
    uint8 cavs_ver;
    uint8 vp_ver;           // 6: VP6, 7: VP7, 8: VP8

    uint8 flv1_ver;

    uint1 plain_mode;
    uint1 force_low_delay;
    uint2 low_delay_mode;
    // bit 0: low_delay_on/off,
    // bit 1: b-vop event
    // Example:
    //         I P P B B P B B P ...
    //         1 1 1 3 3 0 0 0 0 ...
    // Display V V V X X X V V V ...
    // Output  V V V V V X V V V ...

    BITSBUF bs;

    vid_info vinfo;

    int32   picnum;

    frameobj* frames_ref;    // pointer only
    frameobj frames_for;
    frameobj frames_bak;

    // for global buffer pool
    uint32 offsetFlag_Y;

    // for no header code codec
    uint1   no_header_code;

    uint1   skip_to_I;
    uint2   ip_count;       // reference frame count "down" from 2 after each reset
    uint1   broken_link;
    uint1   closed_gop;

    int8    vop_coding_type;
    int1    vop_coded;
    uint1   ts_type;        // 0: pts  1: dts
    uint1   overlap_framebuf;
    uint1   intra_only;
    uint1   use_frame_row_buffer;
    uchar   *row_buffer_y;
    uchar   *row_buffer_uv;
    uchar   use_row_buffer;
    uint32  extra_mbr_num;
    void    *cbctx;         // application context for callback functions
    uint32  reserved[9];
} VID_HANDLE;

void vidsGetFrame(VID_HANDLE *hp, VID_PICTURE *pic);

int log2ceil(int arg);

void ATTR_INST16 make_edge_new(uchar *frame_pic, int width, int height, int edged_width, int left_top_edge_size, int double_v_padding);

void copy_rec_to_ref(VID_HANDLE *hp, frameobj *ref, const frameobj *rec);

/*lint -emacro({514}, AND, OR) */

#define OR  |
#define AND &
#define ELSE    // may apply or not

err_type mvc_report_progress(VID_HANDLE *hp, int current, int total);
err_type mvc_videc_output(VID_HANDLE *hp);
void *mvc_videc_malloc(void *ctx, int size);
void mvc_videc_free(void *ctx, void *ptr);

#endif
