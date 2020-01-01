#ifndef MODULE_REPORT_H
#define MODULE_REPORT_H

#include "avp_common.h"

//#define MV_RECON_DUMP
//#define DEBLOCK_v2_DUMP
//#define MC_DUMP
//#define IQ_DUMP
//#define IT_DUMP    //if you want to define IT_DUMP when testing wmv files, you should define IQ_DUMP
//#define IT_DUMP_NEW_GOLDEN
//#define _NO_ADDIT_
//#define DEBLOCK_DUMP
//#define IPR_DUMP
//#define ADB_COMMAND_DUMP
// ==================================//
//#define INTRA_PRED_DUMP
//#define IQ_COUNT 
//#define HADAMARD_COUNT 
//#define VLC_BITS_USED_COUNT
//#define IT_COUNT
//#define MC_COUNT
//#define DEBLOCK_COUNT
//#define DCT_COUNT

#define MAX_COUNT_FRAME 101
extern int dec_count;

#ifdef IQ_DUMP
extern FILE* test_iq;
#endif
#ifdef IQ_COUNT
extern uint32 iq_count[3];
#define iq_func(iq_type, coef_num) iq_count[iq_type]+=coef_num;
#else
#define iq_func(iq_type, coef_num)
#endif

#ifdef HADAMARD_COUNT
extern int dec_count;
extern hadamard_count[2]; //0: Y   1: Cb_Cr
#define hadamard_func(Y_Cb_Cr) hadamard_count[Y_Cb_Cr] += 1;
#else
#define hadamard_func(Y_Cb_Cr)
#endif

/*
Matrix LV_1 
0: intra_16x16 luma DC
1: luma AC
2: chroma DC
3: chroma AC
Matrix LV_2 
0: blocks of coef numbers = 0
1: blocks of coef numbers = 1
16: blocks of coef numbers = 16
Matrix LV_3 
0: blocks of consuming 1 bit for VLC
1: blocks of consuming 2 bits for VLC
31: blocks of consuming 32 bits for VLC
32: blocks of consuming more and equal to 33 bits for VLC
*/
#ifdef VLC_BITS_USED_COUNT
extern uint32 numcoeff_bitsused[4][17][33];
extern uint32 numcoeff_chroma_ac[2][16]; //0: CB   1: CR
#define VLC_BEFORE() { \
 \
    force_refill_bitsbuf(pbuf_inst.bits, pbuf_inst.len);
    ptr = ((BITSBUF*)bs)->rdptr - 8; \
    bitcnt = ((BITSBUF*)bs)->bitcnt; \
    vlc_b = ((int)ptr)*8 + 32-bitcnt; \
}

#define VLC_AFTER(Y_CbCr) { \
    force_refill_bitsbuf(pbuf_inst.bits, pbuf_inst.len); \
    ptr = ((BITSBUF*)bs)->rdptr - 8; \
    bitcnt = ((BITSBUF*)bs)->bitcnt; \
    vlc_a = ((int)ptr)*8 + 32-bitcnt; \
    /*numcoeff_total[Y_CbCr][numcoeff]++;*/ \
    if ((vlc_a-vlc_b-1)<32) \
        numcoeff_bitsused[Y_CbCr][numcoeff][vlc_a-vlc_b-1]++; \
    else \
        numcoeff_bitsused[Y_CbCr][numcoeff][32]++; \
}

#define CHROMA_AC_NUMCOEF_TYPE(input) { \
    numcoeff_chroma_ac[0][input[0]]++; \
    numcoeff_chroma_ac[1][input[1]]++; \
}

#else
#define VLC_BEFORE()
#define VLC_AFTER(Y_CbCr)
#define CHROMA_AC_NUMCOEF_TYPE(input)
#endif

#ifdef IT_COUNT
// H.264/AVC: (uses 5 elements)
// 0: 4x4 hadamard transform
// 1: 4x4 DC-only integer transform
// 2: 4x4 general integer transform
// 3: 8x8 DC-only integer transform
// 4: 8x8 general integer transform

// wmv use 10 element

extern int idct_func_count[10];
#define idct_func(i) idct_func_count[i]++;
#else
#define idct_func(i)
#endif

#ifdef MC_COUNT
extern int dec_count;
extern int mc_func_count[112+28];
extern int mc_func_b8dir[7];
#define mc_func(i) mc_func_count[i]++;
#define mc_func_b8dir_add(i) mc_func_b8dir[i]++;
#define mc_func_chroma(i) \
    if (d_xy_uv==0) { \
        mc_func(i); \
    } else if (PACK16LSB(0, d_xy_uv)==0) { \
        mc_func(i+7); \
    } else if (PACK16MSB(0, d_xy_uv)==0) { \
        mc_func(i+14); \
    } else { \
        mc_func(i+21); \
    }
#else
#define mc_func(i)
#define mc_func_b8dir_add(i)
#define mc_func_chroma(i)
#endif


#ifdef DEBLOCK_COUNT
#define DB_COUNT_SIZE 18
#define DB_DIR_H 0
#define DB_DIR_V 1
extern uint32 deblocking_func_count[DB_COUNT_SIZE];
/*  RVC
//horizontal  0: luma weak   1: luma normal 2: luma strong  3: chroma weak  4: chroma normal    5: chroma strong    6:weak delta==0     7:normal delta==0   8:strong delta==0
//vertical    9: luma weak   10: luma normal 11: luma strong  12: chroma weak  13: chroma normal    14: chroma strong    15:weak n>1  16:normal n>1    17: strong n>1
*/
//horizontal  0: luma s1_3   1: luma s4   2: chroma s1_3  3: chroma s4
//vertical    4: luma s1_3   5: luma s4   6: chroma s1_3  7: chroma s4
//extern uint32 Alpha_fail;
//extern uint32 Beta_fail;
extern uint32 aq_ap_[6][2];
#if 1
#define DEBLOCK_COUNT_FUNC_RVC(a) a+=1;
#define DEBLOCK_COUNT_FUNC_WMV(a) a+=4;

#define DEBLOCK_COUNT_FUNC(a, alpha, beta, four_flag3) \
{   int i; \
    for (i=0; i<32; i+=8) \
        if ((four_flag3>>i)&0xff) \
            a+=1; \
}
    /*if (alpha!=0 && beta!=0)*/ \
        /*a+=4;*/
//Luma_Chroma:  luma =0  chroma=1
#define DEBLOCK_JUDGE_ALPHA_BETA(four_flag1, four_flag2, four_flag3, four_strng_flag, Luma_Chroma) \
{ \
    int i; \
    for (i=0; i<32; i+=8) { \
        if ((four_strng_flag>>i) & 0x0ff) { \
            if ((four_flag1>>i) & 0x0ff) { \
                if (((four_flag2>>i) & 0x0ff) && ((four_flag3>>i) & 0x0ff)) \
                ; \
                else if (Luma_Chroma)\
                    /*Beta_fail*/aq_ap_[5][1]++; \
                else \
                    aq_ap_[4][1]++; \
            } else if (Luma_Chroma)\
                /*Alpha_fail*/aq_ap_[5][0]++; \
              else \
                aq_ap_[4][0]++; \
        } \
    } \
}
#define DEBLOCK_JUDGE_AQ_AP(four_aq, four_ap, bs, four_flag3) \
{ \
    int i; \
    for (i=0; i<32; i+=8) { \
        if (((four_flag3>>i)&0x0ff) != 0) \
            aq_ap_[(((four_aq>>i) & 0x0ff)<<1) + ((four_ap>>i) & 0x0ff)][bs]++; \
    } \
}
#else
#define DEBLOCK_COUNT_S4(Y, CbCr) \
    Y += 8 ;\
    CbCr += 4;

#define DEBLOCK_COUNT_S1_3_Y(Y) \
{             \
    int j; \
    int Strength_pool_ken = Strength_pool; \
    for (j=0; j<8; j++) { \
        Y += ((Strength_pool_ken&3)!=0)*2; \
        Strength_pool_ken>>=4; \
    } \
}
#define DEBLOCK_COUNT_S1_3_YCbCr(Y, CbCr, Strength_pool_1, Strength_pool, k) \
{ \
    int j=0; \
    int Strength_pool_ken = Strength_pool_1; \
    int Strength_pool_temp = Strength_pool; \
    for (j=0; j<8; j++) { \
        if (k) \
            Y += ((Strength_pool_ken & 0x3)!=0)*2; \
        CbCr += ((Strength_pool_temp & 0x3)!=0);    \
        Strength_pool_ken >>= 4; \
        Strength_pool_temp >>= 4; \
    }  \
}
#endif

#else
#define DEBLOCK_COUNT_FUNC_RVC(a)
#define DEBLOCK_COUNT_FUNC_WMV(a)
#define DEBLOCK_COUNT_FUNC(a, alpha, beta, four_flag3) 
#define DEBLOCK_JUDGE_ALPHA_BETA(four_flag1, four_flag2, four_flag3,  four_strng_flag, Luma_Chroma)
#define DEBLOCK_JUDGE_AQ_AP(four_aq, four_ap, bs, four_flag3)
#define DEBLOCK_COUNT_S4(Y, CbCr) 
#define DEBLOCK_COUNT_S1_3_Y(Y) 
#define DEBLOCK_COUNT_S1_3_YCbCr(Y, CbCr, Strength_pool_1, Strength_pool, k) 
#endif

#ifdef DCT_COUNT

#define CNT_IT_TYPE_NUM  5
#define CNT_IT_INTRA_8x8 0
#define CNT_IT_INTER_8x8 1
#define CNT_IT_INTER_8x4 2
#define CNT_IT_INTER_4x8 3
#define CNT_IT_INTER_4x4 4

#define CNT_IT_COUNTER_NUM   5
#define CNT_IT_COUNTER_SUM   0
#define CNT_IT_COUNTER_L0    1
#define CNT_IT_COUNTER_L1    2
#define CNT_IT_COUNTER_L2    3
#define CNT_IT_COUNTER_L3    4

extern uint32 cnt_it_stat[CNT_IT_TYPE_NUM][CNT_IT_COUNTER_NUM];

void countzero_block(int16* block, int stride, int type);
#endif

#endif // MODULE_REPORT_H
