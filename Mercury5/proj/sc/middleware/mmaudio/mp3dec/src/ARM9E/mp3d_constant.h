

#ifndef MP3_DECODER_CONSTANT_INCLUDE_FILE_
#define MP3_DECODER_CONSTANT_INCLUDE_FILE_

#ifdef __ARM9E_GNU__
#define FORCEINLINE    static __attribute__((always_inline))
#define INLINE  __attribute__((always_inline))
typedef long long S64;
#elif defined(__ARM9E_RVDS22__)
#define FORCEINLINE    static __attribute__((always_inline))
#define INLINE  __inline
typedef long long S64;
#elif defined(__ARM9E_WINCE__)
typedef __int64 S64;
#define FORCEINLINE    __forceinline
#define INLINE  __inline
#elif defined(__GNUC__)
#include "vm_types.ht"
#define FORCEINLINE    __forceinline
#define INLINE  __inline
#else
typedef __int64 S64;
#define FORCEINLINE    __forceinline
#define INLINE  __inline
#endif



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

#define MIN_MP3_VBR_HEADER_OFFSET  (9+4)
#define MAX_MP3_VBR_HEADER_OFFSET  (4+32+2)

#define MAX_TOC_INT_SIZE   100   
#define VBR_CAL_FRAME_NUM  300
#define AVG_SLOT_FRACTION  1024
#define MP3_OK                0x00

#define MP3_HUFFMAN_FAIL      0x07
#define MP3_STEREO_FAIL       0x08
#define MP3_CRC_FAIL          0x09
#define MP3_HEADER_FAIL       0x0a
#define MP3_SIDE_FAIL         0x0b
#define MP3_Decode_ERR        0x09807
#define MP3_RESYNC_EOF        0x0e

#define BUF_REQ_ALIGN_BITS 9
#define BUF_REQ_ALIGN_BYTE ((1<<BUF_REQ_ALIGN_BITS)-1)
#define BUF_REQ_ALIGN_MASK (~BUF_REQ_ALIGN_BYTE)

#define FILTER_BUF_SIZE       (512*sizeof(int)) //int c_mp3_g_filter0[512] or int c_mp3_g_filter1[512]
#define L3_OVERLAP_BUF_SIZE    (1152*sizeof(int))
#define MAX_L3_MDB_SIZE  872 //872 = 512+10 * (32+6)
//#define NON_MP3_MAX_SIZE 2048*1024
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


