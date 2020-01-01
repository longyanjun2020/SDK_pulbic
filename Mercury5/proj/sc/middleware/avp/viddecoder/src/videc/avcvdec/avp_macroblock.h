#ifndef MACROBLOCK_H
#define MACROBLOCK_H

#include "avp_common.h"
#include "avp_videc_s.h"
#include "avp_avcPrivate.h"

// shared by macroblock.c macroblock1.c macroblock2.c
extern const uint8 BlkScanIdx[16];
extern const uint32 dequant_coef_cp[6];
#ifdef SUPPORT_AVC2
extern const uint32 dequant_coef_cp_b8[6][2];
#endif

//#define MEASURE_M_TIME

#ifdef MEASURE_M_TIME

extern clock_t QMC_duration[16];
extern int QMC_count[16];
extern clock_t intra_start_time, intra_end_time, intra_duration[3];
extern clock_t emc_start_time, emc_end_time;
extern clock_t EMC_duration;
extern clock_t itrans_start_time, itrans_end_time, itrans_duration[2];

#define QMC_TIMER_START	    start_time = MY_CLOCK();
#define QMC_TIMER_END(X)	      end_time = MY_CLOCK(); \
        QMC_duration[f_idx] += end_time-start_time; \
        QMC_count[f_idx] += X;

#define EMC_TIMER_START emc_start_time = MY_CLOCK();
#define EMC_TIMER_END emc_end_time = MY_CLOCK(); \
        EMC_duration += emc_end_time-emc_start_time;

#define SPAT_TIMER_START intra_start_time=MY_CLOCK();
#define SPAT_TIMER_END(X) intra_end_time=MY_CLOCK(); \
                intra_duration[X]+=intra_start_time-intra_end_time;

#define ITRANS_TIMER_START itrans_start_time=MY_CLOCK();
#define ITRANS_TIMER_END(X) itrans_end_time=MY_CLOCK(); \
                itrans_duration[X]+=itrans_end_time-itrans_start_time;

#else

#define QMC_TIMER_START
#define QMC_TIMER_END(X)

#define EMC_TIMER_START
#define EMC_TIMER_END

#define SPAT_TIMER_START
#define SPAT_TIMER_END(X)

#define ITRANS_TIMER_START
#define ITRANS_TIMER_END(X)

#endif

int32 ATTR_INST16_M2 avc_get_pmv(AVC_HANDLE *hp,
                  avc_header *hdra,
                  int        ref_frame,
                  int8      *refPic,
                  mvpair     *tmp_mv,
                  int        block_x,
                  int        block_y,
                  int        blockshape_x,
                  int        blockshape_y);

int32 avc_get_pmv_b(AVC_HANDLE *hp,
                   avc_header  *hdra,
                   int         *ref_frame,
                   uint8        *refPic,
                   mvpair      *tmp_mv,
                   int         block_x,
                   int         block_y,
                   int         blockshape_x,
                   int         blockshape_y);

int32 avc_get_pmv_mbaff(AVC_HANDLE *hp,
                  avc_header *hdra,
                  int        ref_frame,
                  int8      *refPic,
                  mvpair     *tmp_mv,
                  int        block_x,
                  int        block_y,
                  int        blockshape_x,
                  int        blockshape_y);

int32 avc_get_pmv_b_mbaff(AVC_HANDLE *hp,
                    avc_header  *hdra,
                    int         *ref_frame,
                    uint8        *refPic,
                    mvpair      *tmp_mv,
                    int         block_x,
                    int         block_y,
                    int         blockshape_x,
                    int         blockshape_y);

void avc_get_direct_spatial_mb_mv(AVC_HANDLE *hp, avc_header *hdra);
void avc_get_direct_spatial_b8_mv(AVC_HANDLE *hp, avc_header *hdra);
void avc_get_direct_temporal_mb_mv(AVC_HANDLE *hp, avc_header *hdra);
void avc_get_direct_temporal_b8_mv(AVC_HANDLE *hp, avc_header *hdra);

void avc_get_direct_spatial_mb_mv_mbaff(AVC_HANDLE *hp, avc_header *hdra);
void avc_get_direct_spatial_b8_mv_mbaff(AVC_HANDLE *hp, avc_header *hdra);
void avc_get_direct_temporal_mb_mv_mbaff(AVC_HANDLE *hp, avc_header *hdra);
void avc_get_direct_temporal_b8_mv_mbaff(AVC_HANDLE *hp, avc_header *hdra);

void avc_CopyBlkEFunc_8_00(const uchar *src, uchar *Dst, const uchar *src2, uchar *Dst2, int b_y, int stride);
void avc_CopyBlkEFunc_4_00(const uchar *src, uchar *Dst, const uchar *src2, uchar *Dst2, int b_y, int stride);
void avc_CopyBlkEFunc_2_00(const uchar *src, uchar *Dst, const uchar *src2, uchar *Dst2, int b_y, int stride);
void avc_CopyBlkEFunc_2(uchar *RESTRICT src, uchar *RESTRICT Dst, uchar *RESTRICT src2, uchar *RESTRICT Dst2, int p, int b_y, int stride);

#if defined(_AG_S32_) && !defined(_AG_V64_)
void avc_CopyBlkEFunc_m_n(uchar *RESTRICT src1, uchar *RESTRICT Dst1, uchar *RESTRICT src2, uchar *RESTRICT Dst2, int b_x, int b_y, int stride, int p);
#define avc_CopyBlkEFunc_8(src, Dst, src2, Dst2, b_y, stride, p) avc_CopyBlkEFunc_m_n(src, Dst, src2, Dst2, 8, b_y, stride, p)
#define avc_CopyBlkEFunc_4(src, Dst, src2, Dst2, b_y, stride, p) avc_CopyBlkEFunc_m_n(src, Dst, src2, Dst2, 4, b_y, stride, p)
#else
void avc_CopyBlkEFunc_4(uchar *RESTRICT src, uchar *RESTRICT Dst, uchar *RESTRICT src2, uchar *RESTRICT Dst2, int b_y, int stride, int p);
void avc_CopyBlkEFunc_8(uchar *RESTRICT src, uchar *RESTRICT Dst, uchar *RESTRICT src2, uchar *RESTRICT Dst2, int b_y, int stride, int p);
#endif
err_type readCBPandCoeffsFromNAL(AVC_HANDLE * RESTRICT hp, BITSBUF *bs);

#define init_macroblock_i16_ipcm_cavlc(hp) init_intra_macroblock_cavlc(hp, 1)
#define init_macroblock_i4_i8_cavlc(hp) init_intra_macroblock_cavlc(hp, 0)
void init_intra_macroblock_cavlc(AVC_HANDLE *hp, uint32 ip_reset);

err_type decode_i4_mode_cavlc(AVC_HANDLE *hp, BITSBUF *bs);
#ifdef SUPPORT_AVC2
err_type decode_i8_mode_cavlc(AVC_HANDLE *hp, BITSBUF *bs);
#endif
err_type decode_i16_mode_cavlc(AVC_HANDLE *hp, BITSBUF *bs);
err_type decode_ipcm_mode_cavlc(AVC_HANDLE *hp, BITSBUF *bs);
err_type decode_inter_mode_cavlc(AVC_HANDLE *hp, BITSBUF *bs);
err_type decode_direct_mode_cavlc(AVC_HANDLE *hp, avc_header *hdra, BITSBUF *bs);
err_type decode_inter_b_mode_cavlc(AVC_HANDLE *hp, avc_header *hdra, BITSBUF *bs);

err_type decode_i4_mode_cabac(AVC_HANDLE *hp, avc_header *hdra, PBUF* RESTRICT pbuf);
#ifdef SUPPORT_AVC2
err_type decode_i8_mode_cabac(AVC_HANDLE *hp, avc_header *hdra, PBUF* RESTRICT pbuf);
#endif
err_type decode_i16_mode_cabac(AVC_HANDLE *hp, avc_header *hdra, PBUF* RESTRICT pbuf);
err_type decode_ipcm_mode_cabac(AVC_HANDLE *hp, avc_header *hdra, PBUF* RESTRICT pbuf);
err_type decode_inter_mode_cabac(AVC_HANDLE *hp, avc_header *hdra, PBUF* RESTRICT pbuf);
err_type decode_direct_mode_cabac(AVC_HANDLE *hp, avc_header *hdra, PBUF* RESTRICT pbuf);
err_type decode_inter_b_mode_cabac(AVC_HANDLE *hp, avc_header *hdra, PBUF* RESTRICT pbuf);


err_type decode_i4_mode_cavlc_mbaff(AVC_HANDLE *hp, avc_header *hdra, BITSBUF *bs);
#ifdef SUPPORT_AVC2
err_type decode_i8_mode_cavlc_mbaff(AVC_HANDLE *hp, avc_header *hdra, BITSBUF *bs);
#endif

err_type decode_i4_mode_cabac_mbaff(AVC_HANDLE *hp, avc_header *hdra, PBUF* RESTRICT pbuf);
#ifdef SUPPORT_AVC2
err_type decode_i8_mode_cabac_mbaff(AVC_HANDLE *hp, avc_header *hdra, PBUF* RESTRICT pbuf);
#endif
err_type decode_i16_mode_cabac_mbaff(AVC_HANDLE *hp, avc_header *hdra, PBUF* RESTRICT pbuf);
err_type decode_ipcm_mode_cabac_mbaff(AVC_HANDLE *hp, avc_header *hdra, PBUF* RESTRICT pbuf);
err_type decode_inter_mode_cabac_mbaff(AVC_HANDLE *hp, avc_header *hdra, PBUF* RESTRICT pbuf);
err_type decode_direct_mode_cabac_mbaff(AVC_HANDLE *hp, avc_header *hdra, PBUF* RESTRICT pbuf);
err_type decode_inter_b_mode_cabac_mbaff(AVC_HANDLE *hp, avc_header *hdra, PBUF* RESTRICT pbuf);

void decode_direct_skip_mode(AVC_HANDLE *hp, avc_header *hdra);
void decode_direct_skip_mode_mbaff(AVC_HANDLE *hp, avc_header *hdra);

void scaling16xn_wp(uchar * Dst, int Stride, int n, int16 wx, int16 ox, uint8 logWD);
void scaling8xn_wp(uchar * Dst, int Stride, int n, int16 wx, int16 ox, uint8 logWD);
void scaling4xn_wp(uchar * Dst, int Stride, int n, int16 wx, int16 ox, uint8 logWD);

void set_intra_info(AVC_HANDLE *hp);

#define reset_i4pred(hdra) \
{ \
    uint32_t *i4predmode = CONVUINTXTOPUINT32((hdra)->i4predmode[0]); \
    i4predmode[0] = 0x22222222; \
    i4predmode[1] = 0x22222222; \
}

#define set_nzcoeff(hdra, Val) \
{ \
    uint32_t *nz_coeff = CONVUINTXTOPUINT32((hdra)->nz_coeff[0]); \
    nz_coeff[0] = Val; \
    nz_coeff[1] = Val; \
    nz_coeff[2] = Val; \
    nz_coeff[3] = Val; \
    nz_coeff[5] = Val; \
    nz_coeff[6] = Val; \
}

#define reset_i4pred_nzcoeff(hdra) \
{ \
    reset_i4pred(hdra); \
    set_nzcoeff(hdra, 0); \
}

#define IS_INTER16(mode) (((mode) == 0) | ((mode) == 1))

#ifdef MB_GETSTRENGTH
#define reset_mv_refidx(mvPtr, refidxPtr, mvVal, refidxVal16, mb_width) \
{ \
    (*(mvPtr+ 1)).cmp = (*(mvPtr+ 2)).cmp = (*(mvPtr+ 3)).cmp = (*(mvPtr+ 4)).cmp = \
    (*(mvPtr+ 6)).cmp = (*(mvPtr+ 7)).cmp = (*(mvPtr+ 8)).cmp = (*(mvPtr+ 9)).cmp = \
    (*(mvPtr+11)).cmp = (*(mvPtr+12)).cmp = (*(mvPtr+13)).cmp = (*(mvPtr+14)).cmp = \
    (*(mvPtr+16)).cmp = (*(mvPtr+17)).cmp = (*(mvPtr+18)).cmp = (*(mvPtr+19)).cmp = mvVal; \
    CONVUINTXTOUINT16(refidxPtr[2]) = CONVUINTXTOUINT16(refidxPtr[6]) = (uint16) refidxVal16; \
}

#elif defined(OPT_GETSTRENGTH) && !defined(SUPPORT_AVCMP)
#define reset_mv_refidx(mvPtr, refidxPtr, mvVal, refidxVal16, mb_width) \
{ \
    (*(mvPtr)).cmp                     = (*(mvPtr+1)).cmp                     = (*(mvPtr+2)).cmp                     = (*(mvPtr+3)).cmp = \
    (*(mvPtr+ FACTOR_4(mb_width))).cmp = (*(mvPtr+ FACTOR_4(mb_width)+3)).cmp = \
    (*(mvPtr+ FACTOR_8(mb_width))).cmp = (*(mvPtr+ FACTOR_8(mb_width)+3)).cmp = \
    (*(mvPtr+FACTOR_12(mb_width))).cmp = (*(mvPtr+FACTOR_12(mb_width)+1)).cmp = (*(mvPtr+FACTOR_12(mb_width)+2)).cmp = (*(mvPtr+FACTOR_12(mb_width)+3)).cmp = mvVal; \
    CONVUINTXTOUINT16(refidxPtr[0]) = CONVUINTXTOUINT16(refidxPtr[FACTOR_2(mb_width)]) = (uint16) refidxVal16; \
    assert(IS_INTRA(hp->hdra.mb_type) || hp->hdra.mb_type==1 || hp->hdra.mb_type==0); \
}
#else
#define reset_mv_refidx(mvPtr, refidxPtr, mvVal, refidxVal16, mb_width) \
{ \
    (*(mvPtr)).cmp                     = (*(mvPtr+1)).cmp                     = (*(mvPtr+2)).cmp                     = (*(mvPtr+3)).cmp = \
    (*(mvPtr+ FACTOR_4(mb_width))).cmp = (*(mvPtr+ FACTOR_4(mb_width)+1)).cmp = (*(mvPtr+ FACTOR_4(mb_width)+2)).cmp = (*(mvPtr+ FACTOR_4(mb_width)+3)).cmp = \
    (*(mvPtr+ FACTOR_8(mb_width))).cmp = (*(mvPtr+ FACTOR_8(mb_width)+1)).cmp = (*(mvPtr+ FACTOR_8(mb_width)+2)).cmp = (*(mvPtr+ FACTOR_8(mb_width)+3)).cmp = \
    (*(mvPtr+FACTOR_12(mb_width))).cmp = (*(mvPtr+FACTOR_12(mb_width)+1)).cmp = (*(mvPtr+FACTOR_12(mb_width)+2)).cmp = (*(mvPtr+FACTOR_12(mb_width)+3)).cmp = mvVal; \
    CONVUINTXTOUINT16(refidxPtr[0]) = CONVUINTXTOUINT16(refidxPtr[FACTOR_2(mb_width)]) = (uint16) refidxVal16; \
}
#endif

int readCoeff4x4_CAVLC(avc_header *hdra, int blk_x, int blk_y,
                       int cdc,
                       BITSBUF *bs, int max_coeff_num,
                       int16 *levarr, uint8 *runarr);

void ATTR_INST16 decode_one_macroblock(AVC_HANDLE *hp);

void macroblock_avc_ec(AVC_HANDLE *RESTRICT hp, avc_header *RESTRICT hdra);
void macroblock_avc_ec_mbaff(AVC_HANDLE *RESTRICT hp, avc_header *RESTRICT hdra);
    /*
    0: up-left
    1-5: up
    6 ,12,18,24: left
    11,17,23,29: (used when hdra->mbA_ff_code == FFC_FIELD_TO_FRAME)
    others: subblocks in current macroblock

    0   1    2    3   4    5
      ----------------------
    6 |  7   8 |  9  10 | 11
   12 | 13  14 | 15  16 | 17
      | ----------------|
   18 | 19  20 | 21  22 | 23
   24 | 25  26 | 27  28 | 29
     */
#define get_intra4x4_blk_availibility(hp, hdra) \
{ \
    int available;   /* raster scan, used bits: 0-29 */ \
    available  = (hdra)->mb_row[hp->h.vinfo.mb_xpos].b[4]; /* bit 0 */ \
    available |= MUX((hdra)->mb_row[hp->h.vinfo.mb_xpos+1].b[4]&1, 0x1e, 0); /* bit 1-4 */ \
    available |= MUX((hdra)->mb_row[hp->h.vinfo.mb_xpos+2].b[4]&1, 0x20, 0); /* bit 5 */ \
    available |= MUX((hdra)->intra_mb_prv&1, 0x1041040, 0); /* bit 6,12,18,24 */ \
    (hdra)->blk_available = available; \
}
#ifdef SUPPORT_MBAFF
#define get_intra4x4_blk_availibility_mbaff(hp, hdra) \
{ \
    int available = 0;   /*raster scan, used bits: 0-29 */ \
    /*int blk_avail = 0;*/   /*bit 0: up-left, bit 1: up, bit 2: up-right, bit 6: left */ \
    if ((hdra)->mbrPtrD!=0) \
        available  = (hdra)->mbrPtrD->b[4]; /* bit 0 */ \
    if ((hdra)->mbrPtrB!=0) \
        available |= MUX((hdra)->mbrPtrB->b[4]&1, 0x1e, 0); /* bit 1-4 */ \
    if ((hdra)->mbrPtrC!=0) \
        available |= MUX((hdra)->mbrPtrC->b[4]&1, 0x20, 0); /* bit 5 */ \
    if ((hdra)->mbrPtrA!=0) { \
        if ((hdra)->mbA_ff_code == FFC_FRAME_TO_FIELD) { \
            available |= MUX((hdra)->mbrPtrA->b[4]&1, 0x0001040, 0); /* bit 6,12 */ \
            available |= MUX(((hdra)->mbrPtrA+1)->b[4]&1, 0x1040000, 0); /* bit 18,24 */ \
        } else if ((hdra)->mbA_ff_code == FFC_FIELD_TO_FRAME) { \
                available |= MUX(((hdra)->mbrPtrA+1)->b[4]&1, 0x20820800, 0);  /* bit 11,17,23,29 */  \
            available |= MUX((hdra)->mbrPtrA->b[4]&1, 0x1041040, 0); /* bit 6,12,18,24 */ \
        } else \
            available |= MUX((hdra)->mbrPtrA->b[4]&1, 0x1041040, 0); /* bit 6,12,18,24 */ \
    } \
    (hdra)->blk_available = available; \
}
#endif

#endif
