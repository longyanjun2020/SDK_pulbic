

#ifndef MP3_DECODER_CONSTANT_INCLUDE_FILE_
#define MP3_DECODER_CONSTANT_INCLUDE_FILE_


#ifdef __aeon__
//#define FORCEINLINE    static __attribute__((always_inline))
//#define INLINE  __attribute__((always_inline))
#define FORCEINLINE    __forceinline
#define INLINE  __inline
typedef long long S64;
#else
typedef __int64 S64;
#define FORCEINLINE    __forceinline
#define INLINE  __inline
#endif


#define SF_14    14
#define SF_15    15
#define SF_16    16
#define SF_23    23
#define SF_24    24
#define SF_28    28
#define SF_29    29
#define SF_30    30
#define SF_31    31

#define SCALE_SF_14 (1 << SF_14)
#define SCALE_SF_15 (1 << SF_15)
#define SCALE_SF_16 (1 << SF_16)
#define SCALE_SF_23 (1 << SF_23)
#define SCALE_SF_24 (1 << SF_24)
#define SCALE_SF_28 (1 << SF_28)
#define SCALE_SF_29 (1 << SF_29)
#define SCALE_SF_30 (1 << SF_30)
#define SCALE_SF_31 ((unsigned int)(1 << SF_31))

#define SCALE_14(A) (((A) >= 0) ? ((int)((A)*(SCALE_SF_14)+0.5)) : ((int)((A)*(SCALE_SF_14)-0.5)))
#define SCALE_15(A) (((A) >= 0) ? ((int)((A)*(SCALE_SF_15)+0.5)) : ((int)((A)*(SCALE_SF_15)-0.5)))
#define SCALE_16(A) (((A) >= 0) ? ((int)((A)*(SCALE_SF_16)+0.5)) : ((int)((A)*(SCALE_SF_16)-0.5)))
#define SCALE_23(A) (((A) >= 0) ? ((int)((A)*(SCALE_SF_23)+0.5)) : ((int)((A)*(SCALE_SF_23)-0.5)))
#define SCALE_24(A) (((A) >= 0) ? ((int)((A)*(SCALE_SF_24)+0.5)) : ((int)((A)*(SCALE_SF_24)-0.5)))
#define SCALE_28(A) (((A) >= 0) ? ((int)((A)*(SCALE_SF_28)+0.5)) : ((int)((A)*(SCALE_SF_28)-0.5)))
#define SCALE_29(A) (((A) >= 0) ? ((int)((A)*(SCALE_SF_29)+0.5)) : ((int)((A)*(SCALE_SF_29)-0.5)))
#define SCALE_30(A) (((A) >= 0) ? ((int)((A)*(SCALE_SF_30)+0.5)) : ((int)((A)*(SCALE_SF_30)-0.5)))

#define SCALE_31_MAX 0x7FFFFFFF
#define SCALE_31_MIN 0x80000000
#define SCALE_31(A) (((A) == 1.00) ? ((int)SCALE_31_MAX) : (((A) >= 0) ? ((int)((A)*(SCALE_SF_31)+0.5)) : \
                                     ((int)((A)*(SCALE_SF_31)-0.5))))

                                     
#define SCALE_L12_SF(A) (((A) == 2.00) ? ((int)SCALE_31_MAX) : (((A) >= 0) ? ((int)((A)*(SCALE_SF_30)+0.5)) : \
                                     ((int)((A)*(SCALE_SF_30)-0.5))))


#define QC_SF     30
#define SCALE_L2_QC(A) (((A) == 2.00) ? ((int)SCALE_31_MAX) : (((A) >= 0) ? ((int)((A)*(SCALE_SF_30)+0.5)) : \
                                     ((int)((A)*(SCALE_SF_30)-0.5))))

#define SCALE_L1_LINEAR(A) (((A) == 2.00) ? ((int)SCALE_31_MAX) : (((A) >= 0) ? ((int)((A)*(SCALE_SF_30)+0.5)) : \
                                     ((int)((A)*(SCALE_SF_30)-0.5))))

#define MP3_BS_BUF_SIZE    4096
#define MP3_BS_HALF_BUF_SIZE   (MP3_BS_BUF_SIZE/2)
#define MP3_BS_QUANT_BUF_SIZE      (MP3_BS_BUF_SIZE/4)
#define MP3_BS_3QUANT_BUF_SIZE      (3*MP3_BS_BUF_SIZE/4)
//- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ; 

//--------------------------------------------
#define  UNKOWN_LAYER    0
#define  MP3_LAYER_I     1          /* Layer I */
#define  MP3_LAYER_II    2          /* Layer II */
#define  MP3_LAYER_III   3       /* Layer III */

//--------------------------------------------
#define  MP3_MODE_SINGLE_CHANNEL   0      /* single channel */
#define  MP3_MODE_DUAL_CHANNEL       1       /* dual channel */
#define  MP3_MODE_JOINT_STEREO       2       /* joint (MS/intensity) stereo */
#define  MP3_MODE_STEREO             3    /* normal LR stereo */

//--------------------------------------------
#define  MP3_EMPHASIS_NONE         0      /* no emphasis */
#define  MP3_EMPHASIS_50_15_US       1       /* 50/15 microseconds emphasis */
#define  MP3_EMPHASIS_CCITT_J_17   3      /* CCITT J.17 emphasis */
//--------------------------------------------
#define  MP3_COUNT1TABLE_SELECT   0x01 
#define  MP3_SCALEFAC_SCALE       0x02 
#define  MP3_PREFLAG              0x04 
#define  MP3_MIXED_BLOCK_FLAG     0x08

//--------------------------------------------
#define  I_STEREO    0x1 
#define  MS_STEREO   0x2

//--------------------------------------------
#define  MP3_FLAG_NPRIVATE_III    0x0007  /* number of Layer III private bits */
#define  MP3_FLAG_INCOMPLETE   0x0008  /* header but not data is decoded */

#define  MP3_FLAG_PROTECTION   0x0010  /* frame has CRC protection */
#define  MP3_FLAG_COPYRIGHT    0x0020  /* frame is copyright */
#define  MP3_FLAG_ORIGINAL  0x0040  /* frame is original (else copy) */
#define  MP3_FLAG_PADDING   0x0080  /* frame has additional slot */

#define  MP3_FLAG_I_STEREO  0x0100  /* uses intensity joint stereo */
#define  MP3_FLAG_MS_STEREO    0x0200  /* uses middle/side joint stereo */
#define  MP3_FLAG_FREEFORMAT   0x0400  /* uses free format bitrate */
//for MPEG 2.5 mode, MP3_FLAG_MPEG_2_5_EXT and MP3_FLAG_LSF_EXT are setting
#define  MP3_FLAG_LSF_EXT   0x1000  /* lower sampling freq. extension */
#define  MP3_FLAG_MC_EXT    0x2000  /* multichannel audio extension */
#define  MP3_FLAG_MPEG_2_5_EXT    0x4000  /* MPEG 2.5 (unofficial) extension */

//--------------------------------------------
#define  MP3_OPTION_IGNORECRC       0x0001   /* ignore CRC errors */
#define  MP3_OPTION_HALFSAMPLERATE  0x0002   /* generate PCM at 1/2 sample rate */
//--------------------------------------------
#define  MP3_PRIVATE_HEADER     0x0100    /* header private bit */
#define  MP3_PRIVATE_III        0x001f  /* Layer III private bits (up to 5) */


#define SBLIMIT      32
#define SSLIMIT      18

#define PEAK_LEN 10

#define MPEG1_BITSTREAM          0x00
#define MPEG2_BITSTREAM          0x01


#define ID3_LEN(b0,b1,b2,b3) (((b0 & 0x7F) << (3*7)) | ((b1 & 0x7F) << (2*7)) | \
                             ((b2 & 0x7F) << (1*7)) | ((b3 & 0x7F) << (0*7)))

#define FRAME_LEN(b0,b1,b2,b3) (((b0 & 0xFF) << (3*8)) | ((b1 & 0xFF) << (2*8)) | \
                                ((b2 & 0xFF) << (1*8)) | ((b3 & 0xFF) << (0*8)))

#define FRAME_COUNT(b0,b1,b2,b3) ((b0 << (3*8)) | (b1 << (2*8)) | (b2 << (1*8)) | (b3 << (0*8)))
#define MP3_FOURCC(a,b,c,d) ( ((a<<24) & 0xff000000)|((b<<16)&0xff0000)|((c<<8)&0xff00)| (d&0xff) )


#define MS_RESOLUTION_TOTAL_TIME
#define MAX_TOC_INT_SIZE   100   


#define MP3_OK                0x00

#define MP3_HUFFMAN_FAIL      0x07
#define MP3_STEREO_FAIL       0x08
#define MP3_CRC_FAIL          0x09
#define MP3_HEADER_FAIL       0x0a
#define MP3_SIDE_FAIL         0x0b

#define MP3_RESYNC_EOF        0x0e

#define SHORT_INT(x,y) (((unsigned int)(y))<<16|((unsigned int)(x)))

#define FILTER_BUF_SIZE       (512*sizeof(int)) //int c_mp3_g_filter0[512] or int c_mp3_g_filter1[512]
#define L3_OVERLAP_BUF_SIZE    (1152*sizeof(int))
#define MAX_L3_MDB_SIZE  872 //872 = 512+10 * (32+6)
#define NON_MP3_MAX_SIZE 2048*1024
#define ML2_FRACBITS 22
# define MAD_F_FRACBITS		22
# if MAD_F_FRACBITS == 28
#  define MAD_F(x)		((int) (x##L))
# else

#  if MAD_F_FRACBITS < 28
#   define MAD_F(x)		((int)  \
				 (((x##L) +  \
				   (1L << (28 - MAD_F_FRACBITS - 1))) >>  \
				  (28 - MAD_F_FRACBITS)))

#  elif MAD_F_FRACBITS > 28
#   define MAD_F(x)		((int)  \
				 ((x##L) << (MAD_F_FRACBITS - 28)))
#  endif
# endif

#endif


