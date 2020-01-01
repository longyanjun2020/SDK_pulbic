#ifndef PARSING_H
#define PARSING_H

//#define FRAME_LIB

#ifdef FRAME_LIB

#define MAXSPS  32
#define MAXPPS  256//128

typedef struct
{
    uint8   pic_parameter_set_id;                           // ue(v)
    uint8   seq_parameter_set_id;                           // ue(v)
    
} pic_parameter_set_frame_lib;

typedef struct
{ 
    uint8   seq_parameter_set_id;                            // ue(v)
    uint8   log2_max_frame_num;                              // ue(v)
    uint8   pic_order_cnt_type;                              // ue(v)
    uint8   frame_mbs_only_flag;                             // u(1)
    uint8   num_ref_frames_in_pic_order_cnt_cycle;           // ue(v)    	
    uint8   profile_idc;                                     // u(8)
    uint8   seq_scaling_maxtrix_present_flag;
    
} seq_parameter_set_frame_lib;

extern seq_parameter_set_frame_lib FrameLib_SeqParSet[MAXSPS];
extern pic_parameter_set_frame_lib FrameLib_PicParSet[MAXPPS];
extern int bs;
extern int m2v_interlaced;

#define ue_v(bs)                uese_v_new(bs, 1)
#define se_v(bs)                uese_v_new(bs, 0)
#define getbits(bs, n)          MY_BSGETBITS(bs, n)
#define u_v(bs, len)            getbits(bs, len)
#define u_1(bs)                 getbits(bs, 1)
int uese_v_new(int bs, int u);

#define AND &
#define OR |
#define ELSE

void FrameLib_get_SPS(seq_parameter_set_frame_lib *sps);
void FrameLib_get_PPS(pic_parameter_set_frame_lib *pps);
void M2V_ParseSeq();

#endif // FRAME_LIB

#endif // PARSING_H
