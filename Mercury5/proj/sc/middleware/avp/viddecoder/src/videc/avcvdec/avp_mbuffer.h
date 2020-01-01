#ifndef MBUFFER_H
#define MBUFFER_H

#include "avp_videc_s.h"
#include "avp_defines.h"

//#ifdef HIERARCHICAL_B
// known bug: need to add 1 for \\testing\clips\avc\elecard\video\_1280x720_0_BikeShow_HD_3500kbps.264
#define ADDITIONAL_STORABLE_PIC_SIZE (1+1+1/*+1+1+1+1*/)
#define MAX_STOREABLE_PIC_POOL (MAX_NO_POC_FRAMES + ADDITIONAL_STORABLE_PIC_SIZE + MAX_NO_POC_FRAMES +1+1)
//#endif

typedef struct collocated_info
{
    uint8 *field_mb_col;

/*  direct_8x8_inference = 1                direct_8x8_inference = 0

    +--------+--------+                    +-------+-------+
    | 0   x  |  x   1 |                    | 0   1 | 2   3 |
    | 2   x  |  x   3 |                    | 4   5 | 6   7 |
    +--------+--------+                    +-------+-------+
    | 4   x  |  x   5 |                    | 8   9 | 10 11 |
    | 6   x  |  x   7 |                    | 12 13 | 14 15 |
    +--------+--------+                    +-------+-------+

    */
    mvpair *mv_col;
    uint8 *ref_idx_col;
    uint8 *ZeroFlag_col;
    // 1st dim: 0: frame/top field, 1: bot field
    // 2nd dim: 0: forward, 1: backward
    int pic_total_pic_num[2][2];
    // 1st dim: 0: forward, 1: backward
    // 2nd dim: 0: top field, 1: bot field
    // 3rd dim: 0: frame/top field, 1: bot field
    int pic_poc_col[2][2][MAX_NO_POC_FRAMES*2];
    char is_used;
} ColInfo;


//! definition a picture (field or frame)
typedef struct storable_picture
{
    frameobj obj;
    uint8    structure;
    uint8    code_structure;
    uint8    idx;
    int      poc;

    // for frame use
    int      pic_num[2]; // 0: short term, 1: long term
    int      long_term_frame_idx;

    uint8    is_long_term;
    uint8    used_for_reference;
    uint8    non_existing;
    uint8    is_used;  // 3:frame or complementary fields, 2: bottom field, 1:top filed
    int8     chroma_vector_adjustment[2];  // 0: list[0], 1: list[1]

    uint8 padding;    // 0: no padding, 1: frame padding, 2: field paddings

#ifdef HIERARCHICAL_B
    ColInfo *col_info;
#endif
} StorablePicture;

//! Frame Stores for Decoded Picture Buffer
typedef struct frame_store
{
    int2   is_used;                //<! 0=empty; 1=top; 2=bottom; 3=both fields (or frame)
    int2   is_reference;           //<! 0=not used for ref; 1=top used; 2=bottom used; 3=both fields (or frame) used
    int2   is_long_term;           //<! 0=not used for ref; 1=top used; 2=bottom used; 3=both fields (or frame) used
    int1   is_output;
    int1   is_non_existing_output;

    //int       is_non_existent;

    uint32 frame_num;
    int    frame_num_wrap;
    int    long_term_frame_idx;
    int    poc;

    StorablePicture *frame;
    StorablePicture field[2]; // 0: top field, 1: bottom field
} FrameStore;


typedef struct m_storable_picture
{
    StorablePicture* pic;
    int used;
} M_STORABLE_PIC;

#define ST_REF 0 // val cannot be changed.
#define LT_REF 1 // val cannot be changed.

//! Decoded Picture Buffer
typedef struct decoded_picture_buffer
{
    FrameStore  **fs;    // valid frame list
    FrameStore  **fs_ref[2]; // 0: short term, 1: long term
    //FrameStore  **fs_st; // short-term list
    //FrameStore  **fs_lt; // long-term list
    uint8         size;
    uint8         used_size;
    uint8         ref_frames_in_buffer[2];  // 0: short term, 1: long term
    //uint8         ltref_frames_in_buffer;
    int           last_output_poc;
    int           max_long_term_pic_idx;

    M_STORABLE_PIC store_pool[MAX_STOREABLE_PIC_POOL];

    uint8 storable_pic_used;
    uint8 storable_pic_idx;
    uint8 storable_idx;
    uint8 storable_pic_used_non_existing;
    uint8 storable_pic_idx_non_existing;
#if 1//def HIERARCHICAL_B
    uint8 storable_pic_used_max;
#endif
} DecodedPictureBuffer;

#ifdef _DEBUG
void check_dpb_consistency(DecodedPictureBuffer *pdpb, uint8 num_ref_frames);
#endif

#endif
