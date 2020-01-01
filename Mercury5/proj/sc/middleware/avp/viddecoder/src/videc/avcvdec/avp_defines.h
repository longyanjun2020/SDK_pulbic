#ifndef DEFINES_H
#define DEFINES_H

#include "avp_common.h"
#include "avp_mvc_decoder.h"

#define LIST_0 0
#define LIST_1 1

// CAVLC
#define LUMA              0
#define LUMA_INTRA16x16DC 1
#define LUMA_INTRA16x16AC 2

#define LEVEL_NUM      6
#define RUNBEFORE_NUM  7

#define TOTRUN_NUM    15

#define MAX_NO_POC_FRAMES  16

#define NONREFFRAME 0           // used with push_poc
#define REFFRAME 1

//--- block types for CABAC ----
#define LUMA_16DC       0
#define LUMA_16AC       1
//#define LUMA_8x4        3
//#define LUMA_4x8        4
#define LUMA_4x4        2 //5
#define CHROMA_DC       3 //6
#define CHROMA_AC       4 //7
#define LUMA_8x8        5 //2

#define CHROMA_DC_U     CHROMA_DC //6
#define CHROMA_AC_U     CHROMA_AC //7
#define CHROMA_DC_V     (CHROMA_DC/*6*/+16)
#define CHROMA_AC_V     (CHROMA_AC/*7*/+16)

//#define _ADAPT_LAST_GROUP_

//#define MAX_CODED_FRAME_SIZE 800000         //!< bytes for one frame
//#define MAXIMUM_UVLC_CODEWORD_PER_HEADER 20 //!< UVLC codewords per combined picture/slice header maximum

//#define _LEAKYBUCKET_

//#define Clip1(a)            ((a)>255?255:((a)<0?0:(a)))
//#define H264_CLIP3(Min, Max, Val) (((Val)<(Min))? (Min):(((Val)>(Max))? (Max):(Val)))
//#define H264_CLIP3(Min, Max, Val) myCLIP(Val, Min, Max)

#define P8x8    4
#define B8x8    4
#define I4MB    (64+9)   // I_4x4
// high profile
#define I8MB    (64+15)  // I_8x8

#define I16MB   (64+32+10)  // I_16x16_...
#define IPCM    (64+32+14)
#define IBLOCK  11
//#define SI4MB   12
#define MAXMODE 13

#define B8_DIRECT   0


#define IS_INTRA_I16(mb_type) (mb_type==I16MB)
//#define IS_INTRA(mb_type)     ((mb_type==I4MB) OR (mb_type==I16MB) OR (mb_type==IPCM))
#define IS_INTRA(mb_type)     ((mb_type & 64)!=0)
//#define IS_NEWINTRA(mb_type)  ((mb_type==I16MB) OR (mb_type==IPCM))
#define IS_NEWINTRA(mb_type)  ((mb_type & 32)!=0)
#define IS_OLDINTRA(mb_type)  (mb_type==I4MB)
#define IS_INTRA_I4(mb_type)  (mb_type==I4MB)
#define IS_INTRA_I8(mb_type)  (mb_type==I8MB)
#define IS_INTRA_IPCM(mb_type) (mb_type==IPCM)
//#define IS_INTER(mb_type)     ((mb_type!=I4MB) AND (mb_type!=I16MB) AND (mb_type!=IPCM))
#define IS_INTER(mb_type)     ((mb_type & 64)==0)
//#define IS_INTERMV(mb_type)   ((mb_type!=I4MB) AND (mb_type!=I16MB) AND (mb_type!=IPCM) AND (mb_type!=0))
#define IS_INTERMV(mb_type)   (((mb_type & 64)==0) AND (mb_type!=0))
#define IS_DIRECT(mb_type)    (mb_type==0)
#define IS_DIRECT_COPY(mb_type)    ((mb_type==0) AND (hdra->type==B_SLICE))
#define IS_COPY(mb_type)      ((mb_type==0) AND ((hdra->type==P_SLICE) /*OR (hdra->type==SP_SLICE)*/))
#define IS_P8x8(mb_type)      (mb_type==P8x8)
#define IS_B8x8(mb_type)      (mb_type==B8x8)
#define IS_DIRECT_B8(sub_mb_type)    (sub_mb_type==B8_DIRECT)

#define AVC1_P_MB_SKIP 0
#define AVC1_B_MB_SKIP (-1)
#define IS_P_SKIP(mb_type)      ((mb_type)==AVC1_P_MB_SKIP)
#define IS_B_SKIP(mb_type)      ((mb_type)==AVC1_B_MB_SKIP)

#ifdef SUPPORT_PAFF
#define FIELD_PIC_FLAG(hdra) _B1((hdra)->field_pic_flag)
#else
#define FIELD_PIC_FLAG(hdra) 0
#endif

#ifdef SUPPORT_AVCMP
#define FIELD_MB_FLAG(hdra) _B1((hdra)->field_mb)
#else
#define FIELD_MB_FLAG(hdra) 0
#endif

// Quantization parameter range

#define MIN_QP          0
#define MAX_QP          51

/* 4x4 intra prediction modes */
#define DC_PRED               2

// 8x8 chroma intra prediction modes
#define DC_PRED_8       0
#define PLANE_8         3

#define SLICE_MORE_DATA       0
#define SLICE_SOP             2                       //!< Start Of Picture
#define SLICE_SOSL            3                       //!< Start Of Slice
#define SLICE_EOP             4     // end of picture
#define SLICE_EOSL            5                       //!< End Of Slice


#define MAX_REFERENCE_PICTURES 32


#define MVPRED_MEDIAN   0
#define MVPRED_L        1
#define MVPRED_U        2
#define MVPRED_UR       3

//Start code and Emulation Prevention need this to be defined in identical manner at encoder and decoder
#define ZEROBYTES_SHORTSTARTCODE 2 //indicates the number of zero bytes in the short start-code prefix

typedef enum
{
    avcFRAME = 0,
    avcFIELD_TOP = 1,
    avcFIELD_BOT = 2,
} PictureStructure;           //!< New enum for field processing

//#define ref_fwd_pic_size 7

// check if MB(x, y) is available, x must be in [0, mb_width-1], y must be in [-infinite, mb_height-1]
#define IS_MB_AVAILABLE(x, y, save_x, save_y) (!(((y) < (save_y)) OR (((y) == (save_y)) AND ((x) < (save_x)))))
// check if MB(x, y) is available, x must be in [-infinite, mb_width-1], y must be in [-infinite, mb_height-1]
#define IS_MB_AVAILABLE_C_XL(x, y, save_x, save_y) (!(((y) < (save_y)) OR (((y) == (save_y)) AND ((x) < (save_x))) OR ((x)<0)))
// check if MB(x, y) is available, x must be in [0, infinite], y must be in [-infinite, mb_height-1]
#define IS_MB_AVAILABLE_C_XR(x, y, save_x, save_y, mb_width) (!(((y) < (save_y)) OR (((y) == (save_y)) AND ((x) < (save_x))) OR ((x)>=(mb_width))))

#define IS_MB_AVAILABLE_PAIR(xy, save_xy) (((int32)(xy)) >= ((int32)(save_xy)))
#define IS_MB_AVAILABLE_C_XL_PAIR(xy, save_xy) ((((int32)(xy)) >= ((int32)(save_xy))) AND (PACK16LSB(0, xy)!=0xffff))
#define IS_MB_AVAILABLE_C_XR_PAIR(xy, save_xy, mb_width) ((((int32)(xy)) >= ((int32)(save_xy))) AND (PACK16LSB(0, xy)!=(mb_width)))

//#define MEASURE_M_TIME
#ifdef MEASURE_M_TIME
extern clock_t start_time, end_time;
extern clock_t QMC_duration[16];
extern int QMC_count[16];
extern clock_t intra_end_time, intra_start_time, intra_duration[3];
extern clock_t emc_start_time, emc_end_time;
extern clock_t EMC_duration;
extern clock_t itrans_start_time, itrans_end_time, itrans_duration[2];

extern clock_t DeblockFrame_start_time, DeblockFrame_end_time;
extern clock_t DeblockFrame_duration;
extern int DeblockFrame_count;
#endif

#endif
