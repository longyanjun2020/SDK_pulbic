#ifndef __MP3_ENC_STRUCT_INCLUDE_FILE__
#define __MP3_ENC_STRUCT_INCLUDE_FILE__


/***************************************************************************************
psycho 0 mem struct
****************************************************************************************/
#if 0
typedef struct psycho_0_mem_struct {
   int iath_min[SB_SIZE];   
} psycho_0_mem;
#endif


/***************************************************************************************
psycho 1 mem struct
****************************************************************************************/
#define DBTAB 1000


typedef struct {
   FLOAT x;
   int type, next, map;
} mask, *mask_ptr;

typedef struct
{
   int line;
   FLOAT bark;
   FLOAT hear;
}MaskingThreshold;


typedef struct psycho_1_mem_struct {
   int *cbound;
   int crit_band;
   int sub_size;
   mask power[HAN_SIZE];

   MaskingThreshold *ltg;
   FLOAT ltg_x[133];
   FLOAT dbtable[DBTAB];
} psycho_1_mem;


typedef struct 
{
   // Input PCM audio File Information
   int samplerate;            // mpeg1: 32000 [44100] 48000 
                           // mpeg2: 16000    22050   24000 
   int channels;       // Number of channels on the input stream
   
   // Output MP2 File Information
   int version; //  0 mpeg2  [1] mpeg1                        
   int bitrate;               // for mpeg1:32, 48, 56, 64, 80, 96,112,128,160,[192], 224, 256, 320, 384 
                              // for mpeg2: 8, 16, 24, 32, 40, 48, 56, 64, 80, [96], 112, 128, 144, 160 
   int st_mode; 
   // Psychoacoustic Model options
   int vbr;                // turn on VBR mode TRUE [0] 
   int error_protection;         // [0] 
   int bitrate_index;
   int samplerate_idx;   
   int header_st_mode;
   int mode_ext;   
   unsigned int header_flag;
#ifdef SUPPORT_CRC     
   unsigned int num_crc_bits;                // Number of bits CRC is calculated on
#endif
   unsigned char bit_alloc[2][SB_SIZE];
   unsigned char scfsi[2][SB_SIZE];
   unsigned char sf_index[2][SB_SIZE][3];

   int ismr[2][SB_SIZE];
   int *isb_sample;   
   // memory for subband
   int sam_buffer[2][MAX_FRAME_BUF/2];  //to sure it is 4 byte boundary
   short *buffer[2];
   // Frame info
   int jsbound;               // first band of joint stereo coding
   int sblimit;               // total number of sub bands
   int tablenum;
   unsigned char scale_diff_table[128];
 
}mp3e_data_struct;


/* bit stream structure */
typedef struct bit_stream_struc {
   unsigned char *buf;       /* bit stream buffer */
   //int buf_size;       /* size of buffer (in number of bytes) */
#if 0   
   int totbit;        /* bit counter of bit stream */
   int buf_byte_idx;   /* pointer to top byte in buffer */
   int buf_bit_idx;    /* pointer to top bit of top byte in buffer */
#endif   
   int ado_cache_left;
   unsigned int ado_cache;
   unsigned char *ado_cache_ptr;
} bit_stream;




extern const int SecondCriticalBand[6][28];
extern const int SecondFreqEntries[6];
extern const MaskingThreshold SecondFreqSubband[6][132+1];
extern const FLOAT costab[20];
extern const FLOAT sintab[20];
extern const short k1k2tab[8 * 62][2];

extern mp3e_data_struct *gp_mp3enc;

extern const FLOAT f_scalefactor[64];

#endif



