#ifndef AVCPRIVATE_H
#define AVCPRIVATE_H

#include "avp_videc_s.h"
#include "avp_mbuffer.h"
#include "avp_defines.h"
#include "avp_nalucommon.h"
#ifdef SUPPORT_AVCMP
#include "avp_ctx.h"
#endif
#include "avp_parsetcommon.h"

typedef enum {
    UVLC = 0,
    CABAC = 1,
} SymbolMode;


typedef enum {
    P_SLICE = 0,
    B_SLICE,
    I_SLICE,
    SP_SLICE,
    SI_SLICE
} SliceType;

#define AVC_BASELINE    66
#define AVC_MAIN        77
#define AVC_EXTENDED    88
#define AVC_HIGH       100
#define AVC_HIGH_10    110
#define AVC_HIGH_422   122
#define AVC_HIGH_444   144

#define AVC_MB_EC_HEIGHT 6
/**********************************************************************
 * C O N T E X T S   F O R   T M L   S Y N T A X   E L E M E N T S
 **********************************************************************
 */

typedef struct
{
    int8    qp;
    int8    _align;
    MBINDEX_TYPE     start_mb_nr;   //!< MUST be set by NAL even in case of ei_flag == 1

#ifdef SUPPORT_AVCMP
    MotionTextureInfoContexts  mt_ctx;
#endif
} Slice;

// TODO: 1. change mbAvailN:0-1 to cbp_blk:27-28
//       2. use single 32-bit access when retrieving multiple fields from macroblock structure
//! Macroblock
typedef struct macroblock
{
    int8 qp;
    uint8 slice_nr;  // 255 stands for invalid

    // some storage of macroblock syntax elements for global access
    uint8 mb_type;

    uint2 mbAvailN;  // (mbALoc<<6) | (mbBLoc<<4) | (mbAvailA<<1) | mbAvailB

    // for cabac, consider to be combined
    int32 cbp_blk;    // for cavlc, 0-15, Y blk
                      // for cabac, 0-15, Y blk, 16-19, U blk, 20-23 V blk, 24-26, Y dc, U dc, V dc
                      // 30 field mb
                      // for high profile, 31 transform_size_8x8_flag
} Macroblock;

// avc\allwell\1500K\23509.mp4 has slice number larger than 64
#define MAX_SLICE_NUM_IN_FRAME  128

#define PACK_DEBLOCK_PARA(alpha, beta, disable_idc) PACKBYTES(alpha,((beta)<<2) | (disable_idc))
#define UNPACK_DEBLOCK_PARA_ALPHA(LFAlphaBetaDisableIdc) IBYTESEL(LFAlphaBetaDisableIdc, 1)
#define UNPACK_DEBLOCK_PARA_BETA(LFAlphaBetaDisableIdc) (IBYTESEL(LFAlphaBetaDisableIdc, 0)>>2)
#define UNPACK_DEBLOCK_PARA_DISABLE_IDC(LFAlphaBetaDisableIdc) (LFAlphaBetaDisableIdc&3)

typedef struct slice_deblocking_para
{
    // packing format
    int16 LFAlphaBetaDisableIdc; // LFAlphaC0Offset << 8 | LFBetaOffset << 2 | LFDisableIdc
    u16pair start_mbpos;
    u16pair end_mbpos;
} Slice_DeBlocking_Para;

/*! Buffer structure for decoded referenc picture marking commands */
typedef struct DecRefPicMarking_s
{
    uint8 memory_management_control_operation;
    uint8 _align[3];
    int difference_of_pic_nums;
    int long_term_pic_num;
    int long_term_frame_idx;
    int max_long_term_frame_idx_plus1;
} DecRefPicMarking_t;

typedef union _DecodingEnvironment
{
    struct {
        uint16 Dvalue;
        uint16 Drange;
    } a;
    int32 cmp;
} DecodingEnvironment;

typedef DecodingEnvironment *DecodingEnvironmentPtr;

#ifdef SUPPORT_AVCMP
#define AVC_REF_LIST_NUM    (2+4) // first 2 for FRAME/FILED/PAFF, the last 4 for MBAFF
                                  // 0: frame list0/field list0
                                  // 1: frame list1/field list1
                                  // 2: top field list0
                                  // 3: top field list1
                                  // 4: bottom field list0
                                  // 5: bottom field list1
#else
#define AVC_REF_LIST_NUM    2
#endif

#define MAX_DEC_REF_PIC_MARKING_BUFFER  30

typedef struct _avc_parser_mb_row_memory
{
    uchar  b[6];
    uchar  i4predmode_row[2];
    union {
        uint5  nz_coeff_row[8];  // must be 32-bit aligned
#ifdef SUPPORT_AVCMP
        struct {
            u8pair mvd_cabac_row[4];
            u8pair mvd_b_cabac_row[4];
        } a;
#endif
    } u;
} avc_parser_mb_row_memory;

typedef struct _avc_parser_mb_prv_memory
{
    uint8 i4predmode_left[4];
    union {
        uint8 nz_coeff_left[12+4];   // V0 V0 V0 V0       V3 V3 V3 V3
                                     // V1 V1 V1 V1       X  X  X  X
                                     // V2 V2 V2 V2
                                     // X  X  X  X
        struct {
            u8pair mvd[4];
            u8pair mvd_b[4];
            uint8 b8_direct_l;       // store at 4 MSB bits
            uint8 _padding[3];
        } a;
    } u;
} avc_parser_mb_prv_memory;

typedef struct
{
    uint32 idc;
    int32 para;
} mcRemappedCommand;

#define FFC_ONE_TO_ONE         0
#define FFC_FRAME_TO_FIELD     1
#define FFC_FIELD_TO_FRAME     2

#define ALLOC_STOREABLE_PIC_POOL 32//(2*MAX_STOREABLE_PIC_POOL+1)
// image parameters
typedef struct _avc_header
{
    Slice_DeBlocking_Para slice_deblock[MAX_SLICE_NUM_IN_FRAME];
    /* Here is 64 byte aligned */
    StorablePicture *dec_picture;
    StorablePicture *listX[AVC_REF_LIST_NUM][ALLOC_STOREABLE_PIC_POOL];
    unsigned listXsize[AVC_REF_LIST_NUM];
#ifdef SUPPORT_AVCMP
    unsigned listXsize_Valid[2]; // forward/backward is enough
#endif
    /* Here is 64 byte aligned */
    MBINDEX_TYPE blk_x; // maximal 1920/4 = 480
    MBINDEX_TYPE blk_y; // maximal 1088/4 = 272
    PXINDEX_TYPE pix_x;
    PXINDEX_TYPE pix_y;
    PXINDEX_TYPE pix_c_x;
    PXINDEX_TYPE pix_c_y;
    uchar* PixXPtr[3];
    DecodedPictureBuffer dpb;

    uint1 direct_type;                            //<! 1 for Spatial Direct, 0 for Temporal
    uint8 type;                                   //<! image type INTER/INTRA

    // macroblock level
#ifdef SUPPORT_AVCMP // should be removed
    uint8 cbp_cabac_row[MAX_MBC+1];
#endif
    uint8 cbp;
    uint8 cbp_y; // for intra16 mode

    int b8_offset;
    int b4_offset;

    uint8 b8mode[4];    // 4 byte aligned
    uint8 b8dir[4];     // 4 byte aligned

    uint8 current_slice_nr;  // 255 stands for invalid
    uint8 slice_nr_count; // total slice number
    uint1 allrefzero;  // P-VOP: P8x8 refidx=0
                       // B-VOP: skip mb

    int8 qp;                                      //<! quant for the current frame
    uint8 mb_type;
    uint8 i16predmode;
    uint2 i8predmode;
    int32 cbp_blk;    // for cavlc, 0-15, Y blk
                      // for cabac, 0-15, Y blk, 16-19, U blk, 20-23 V blk, 24-26, Y dc, U dc, V dc

    //TODO: pack mbAvailA, mbAvailB, mbAvailC and mbAvailD into 4-byte aligned 32-bit symbol
    uint1 mbAvailA;   // left // 4 byte aligned
    uint1 mbAvailB;   // top
    uint1 mbAvailC;   // top right
    uint1 mbAvailD;   // top left
#ifdef SUPPORT_MBAFF
    uint2 mbALoc;     // left, 0: top mb of left mb_pair,
                      //       1: bottom mb of left mb_pair
    uint2 mbBLoc;     // top,  0: top mb of current mb_pair,
                      //       1: invalid,
                      //       2: top mb of above mb_pair
                      //       3: bottom mb of above mb_pair
#endif
    uint1 intra_mb_prv;
    uint1 _intra_mb_prv_mbaff;

#ifdef SUPPORT_MBAFF
    avc_parser_mb_row_memory* mbrPtrA;
    avc_parser_mb_row_memory* mbrPtrD;
    avc_parser_mb_row_memory* mbrPtrB;
    avc_parser_mb_row_memory* mbrPtrC;
    avc_parser_mb_row_memory* mbrPtrX;

    avc_parser_mb_prv_memory* mblPtrA;
    avc_parser_mb_prv_memory* mblPtrX;

    Macroblock* mbfPtrA;
    Macroblock* mbfPtrD;
    Macroblock* mbfPtrB;
    Macroblock* mbfPtrC;
    Macroblock* mbfPtrX;
#endif

#ifdef NEW_GET_STRENGTH
    uint32 Strength_pool[MAX_MBR*MAX_MBC][4];   //0: H  1: V  2: V mbaff  3: bit0: Top is S4
                                                //                           bit1: Left is S4
                                                //                           bit2: filterTopMbEdgeFlag
                                                //                           bit3: filterLeftMbEdgeFlag
                                                //                           bit4: MbQ_LFDisableIdc
                                                //                           bit5: MbQ_cbp_blk>=0
#endif

#ifdef SUPPORT_AVCMP
    uint8 b8_direct_l;    // b4 b5    b0 b1
                          // b6 b7    b2 b3
    int8 l_dquant_cabac; // last decoded dquant
#endif

    // YYYY <= m1 to m4
    // YYYY (0-3)
    // YYYY (4-7)
    // YYYY (8-11)
    // YYYY (12-15)
    // UUVV <= m1 to m4 (16-19)
    // UUVV (20-23)
    // UUVV (24-27)
    uint32 _nz_coeff_y_m1_to_m4; // necessary for nz_coeff_y index -1 to -4
    uint8 nz_coeff[28];

#ifdef SUPPORT_AVCMP
    u8pair _mvd_m1_to_m4[4]; // necessary for mvd index -1 to -4
    u8pair mvd[16]; // for cabac
#endif

    // 4byte align
    uint32 _i4predmode_m1_to_m4;  // necessary for i4predmode index -1 to -4
    uint8 i4predmode[8];   //  00/01 10/11 02/03 12/13 20/21 30/31 22/23 32/33
#ifdef SUPPORT_AVCMP
    u8pair _mvd_b_m1_to_m4[4]; // necessary for mvd index -1 to -4
    u8pair mvd_b[16]; // for cabac
#endif
    int16 mb_skip_run;                            //<! Current count of number of skipped macroblocks in a row

    PictureStructure structure;                               //<! Identify picture structure type

    Slice       slice;                   //<! pointer to current Slice data struct
    Macroblock  *mb_data;                //<! array containing all MBs of a whole frame

#ifdef SUPPORT_MBAFF
    // frame-field structure
    // 0: same structure, FRAME=>FRAME or FIELD=>FIELD
    // 1: FRAME=>FIELD
    // 2: FIELD=>FRAME
    uint2 mbA_ff_code; // ff_code from left MB to current MB
    uint2 mbB_ff_code; // ff_code from top MB to current MB
    uint2 mbC_ff_code; // ff_code from top-right MB to current MB
    uint2 mbD_ff_code; // ff_code from top-left MB to current MB
    uint2 mbX_ff_code; // ff_code from colocated MB to current MB
#endif
    // For MB level frame/field coding
    uint1 mbaff_frame;
    uint1 field_mb;

    uint1 adaptive_ref_pic_buffering_flag;
    DecRefPicMarking_t dec_ref_pic_marking_buffer[MAX_DEC_REF_PIC_MARKING_BUFFER];

    uint8 num_ref_idx_active[2];            //!< 0: number of forward reference, 1: number of backward reference

    int slice_group_change_cycle;
    int redundant_pic_cnt;
    uint32 pre_frame_num;           //!< store the frame_num in the last decoded slice. For detecting gap in frame_num.
    int framepoc;    //poc of this frame
    int toppoc;      //poc for this top field
    int bottompoc;   //poc of bottom field of frame
    uint32 frame_num;   //frame_num for this frame
    uint1 field_pic_flag;
    uint1 bottom_field;

    //the following is for slice header syntax elements of poc
    // for poc mode 0.
    uint32 pic_order_cnt_lsb;
    int delta_pic_order_cnt_bottom;
    // for poc mode 1.
    int delta_pic_order_cnt[2];

    // ////////////////////////
    // for POC mode 0:
    int32  PicOrderCntMsb;
    uint32 PrevPicOrderCntLsb;
    int32  CurrPicOrderCntMsb;
    // for POC mode 1:
    uint32 AbsFrameNum;
    uint32 PreviousFrameNum, FrameNumOffset;
    int ThisPOC;
    int PreviousFrameNumOffset;
    // /////////////////////////

    //weighted prediction
    uint1 apply_weights;
    uint8 luma_log2_weight_denom;
    uint8 chroma_log2_weight_denom;
    uint8 _align32;
#ifdef SUPPORT_AVCMP
    int16 wp_wo[2][MAX_REFERENCE_PICTURES][3][2];  // weight in [list][index][component][weight/offset] order
                                                   // ??? if need to support frame/topfield/bottomfield
    int16 wp_td_scale[3][MAX_REFERENCE_PICTURES][MAX_REFERENCE_PICTURES][2]; // offset in [frame/topfield/bottomfield][list0][list1][td/scale] order
#endif

    uint2 idr_flag;                                 // 0: not an IDR, 1: an IDR, 2: a fake IDR
    uint2 nal_reference_idc;                       //!< nal_reference_idc from NAL unit

    uint1 no_output_of_prior_pics_flag;
    uint1 long_term_reference_flag;

    uint1 last_has_mmco_5;
    uint1 cabac_enable;
    uint16 idr_pic_id;

    int MaxFrameNum;

    int last_pic_bottom_field;

#ifdef SUPPORT_AVCMP
    uint8 model_number;
    DecodingEnvironment de_cabac;
#endif

    /*   mv:
    +--------+---------+
    | 0   1  | 2   3   |
    |4w 4w+1 |4w+2 4w+3|
    +--------+---------+
    |8w 8w+1 |8w+2 8w+3|
    |12w               |
    +--------+---------+
    */
#ifdef SUPPORT_AVCMP
#define HYPOTHESIS 2
#else
#define HYPOTHESIS 1
#endif

#ifdef MB_GETSTRENGTH
    uint32 Strength_pool[MAX_MBR*MAX_MBC][2]; // DIR_HORI and DIR_VERT
    // to store the bottom-most line
    uint8   ref_idx_row[2*MAX_MBC+1];   // -1 (255) stands for intra
    mvpair  mv_row[4*MAX_MBC+1];

#define MV_WIDTH 5
#define REF_IDX_WIDTH 4
    //    +------+------+
    //  0 | 1  2 | 3  4 |
    //  5 | 6  7 | 8  9 |
    //    +------+------+
    // 10 |11 12 |13 14 |
    // 15 |16 17 |18 19 |
    mvpair cur_mv[20];
    mvpair up_left_mv;
    //      +------+
    // 0  1 | 2  3 |
    // 4  5 | 6  7 |
    //      +------+
    // cur_ref_idx[0] and cur_ref_idx[4] will not be used.
    uint8 cur_ref_idx[8];
    uint8 up_left_ref_idx;
#elif defined(INTRA_ONLY)
    mvpair *mv[HYPOTHESIS];
    uint8 *ref_idx[HYPOTHESIS];  // -1 (255) stands for intra
#else
    mvpair *mv[HYPOTHESIS];
    uint8 *ref_idx[HYPOTHESIS];
#endif
    /*  p_mv_col
    direct_8x8_inference_flag = 1            direct_8x8_inference_flag = 0
    +--------+--------+                     +--------+--------+
    | 0   X  |  X   1 |                     | 0   1  |  2   3 |
    | X   X  |  X   X |                     | 4   5  |  6   7 |
    +--------+--------+                     +--------+--------+
    | X   X  |  X   X |                     | 8   9  | 10  11 |
    | 2   X  |  X   3 |                     | 12  13 | 14  15 |
    +--------+--------+                     +--------+--------+
    */
#ifdef SUPPORT_AVCMP
    mvpair *p_mv_col;
    uint8 *p_ref_idx_col;
    uint8 *p_ZeroFlag_col;
#ifdef INTRA_ONLY
    mvpair mv_col_scale[1];  // field/frame scaling use
    uint8 ref_idx_col_scale[4];  // -1 (255) stands for intra
    uint8 ZeroFlag_col_scale[4];
#else
    mvpair mv_col_scale[16*MAX_MBR*MAX_MBC];  // field/frame scaling use
    uint8 ref_idx_col_scale[4*MAX_MBR*MAX_MBC];  // -1 (255) stands for intra
    uint8 ZeroFlag_col_scale[16*MAX_MBR*MAX_MBC];
#endif
#endif

#ifdef HIERARCHICAL_B
    ColInfo **col_info;
#endif
    int first_poc_since_idr;
    int is_first_frame;
    int valid_output_poc;

    uint32 _align_point;
#ifdef SUPPORT_MBAFF
    avc_parser_mb_row_memory _mb_row_m1[2]; // for sentinel use
    avc_parser_mb_row_memory mb_row[(E_MAX_MBC+2)*2]; // Some field starts from -1, some from 0. So, we need E_MAX_MBC+2
    avc_parser_mb_row_memory mb_row_BD[2*2];
    avc_parser_mb_prv_memory mb_prv[2*2];
#else
    avc_parser_mb_row_memory _mb_row_m1[1]; // for sentinel use
    avc_parser_mb_row_memory mb_row[(E_MAX_MBC+2)];
#endif

#ifdef SUPPORT_AVCMP
    // temporal direct mode
    // index: FRAME 0
    //        FIELD top:0 bottom;1
    //        MBAFF frame:0, top:1, bottom:2
#ifndef HIERARCHICAL_B
    int pic_total_pic_num[2];
    int pic_poc_col[2][MAX_NO_POC_FRAMES*2];
    int pic_poc_col_bot[2][MAX_NO_POC_FRAMES*2];
#endif

    // index: frame, field 0
    //        MBAFF frame-to-frame:0 top-to-top:1 bottom-to-bottom:2
    //              frame-to=top:3 frame-to-bottom:4
    //              nearest-field-to-frame:5

    // 1st dim: 0: forward, 1: backward
    // 2nd dim: 0: frame/top field, 1: bot field
    int8 refidx_col[2][2][MAX_NO_POC_FRAMES*2];
    uint1 colFieldisBottom; // 0: top field is near than bottom field from current frame picture.
                            // 1: bottom field is near than top field from current frame picture.
#endif

    seq_parameter_set_rbsp_t SeqParSet[MAXSPS];
    pic_parameter_set_rbsp_t PicParSet[MAXPPS];

#ifdef SUPPORT_AVC2
    uint1 transform_size_8x8_flag;
    uint1 NoSmallThan8x8;
#endif
    int blk_available;
#ifdef INTRA_LEFT_TOP
    uint32 intra_left[8*2]; // Save rightmost pixels when addblock is called.
                            // These pixels can be used by intra prediction.
                            // y:0~3 cb:4~5 cr:6~7, and MBAFF needs double
    uchar intra_top_y[M4VDEC_MAX_WIDTH<<1]; // Save the last row of each decoded MB, and MBAFF needs double
    uchar intra_top_u[M4VDEC_MAX_WIDTH]; // Save the last row of each decoded MB, and MBAFF needs double
    uchar intra_top_v[M4VDEC_MAX_WIDTH]; // Save the last row of each decoded MB, and MBAFF needs double
    uint32 intra_upper_left[3]; // [3]: y/u/v
#endif

    uint8 active_pps_id;
    uint8 active_sps_id;
    pic_parameter_set_rbsp_t active_pps;
    seq_parameter_set_rbsp_t active_sps;
#ifndef NO_NAL_PEEK
    uchar *endptr;
#endif
    // for ER
    uint1 fake_flag[AVC_REF_LIST_NUM][MAX_NO_POC_FRAMES*2];
    frameobj last_decoded_frame;
    int nal_wo_startcode;
    int nal_unit_size;
    uint8_t *p_next_nal;
    int32_t nal_4byte_backup;
    int32_t next_nal_len;
#if defined(AVC_ROW_DEBLOCK2) && defined(USE_ROW_BUFFER)
    uchar currow_slice_id;
#endif
    int loopfilter_level;
} avc_header;

typedef struct {
    VID_HANDLE h;
    frameobj frames_aux1; // FIXME: remove
    frameobj frames_aux2; // FIXME: remove
    // 64-byte aligned
    short block[384];
    avc_header hdra;
    uchar *frame_fake[3];
} AVC_HANDLE;

void free_frame_store(DecodedPictureBuffer *pdpb, FrameStore* f);

StorablePicture* get_largest_pts(avc_header *hdra);

StorablePicture* alloc_storable_picture_from_pool (avc_header* hdra, PictureStructure structure, uint8 num_ref_frames);

void free_storable_picture(DecodedPictureBuffer *pdpb, StorablePicture* p);
void flush_dpb(DecodedPictureBuffer *pdpb, int offsetFlag_Y, avc_header* hdra);

int avc_decode_picture(VID_HANDLE *hp, err_type err_skip, VID_SETUP *setup);

void update_frame_store(StorablePicture* p, avc_header* hdra, AVC_HANDLE *hp);
void store_picture_in_dpb(StorablePicture* p, avc_header* hdra, AVC_HANDLE *hp);

#endif /* AVCPRIVATE_H */
