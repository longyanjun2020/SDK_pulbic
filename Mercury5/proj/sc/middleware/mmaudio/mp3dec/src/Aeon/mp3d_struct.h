#ifndef _MP3_DECODER_STRUCT_INCLUDE_FILE
#define _MP3_DECODER_STRUCT_INCLUDE_FILE 


//--------------------------------------------
union huffquad {
  struct {
    unsigned short final  :  1;
    unsigned short bits   :  3;
    unsigned short dbit   :  4;
    unsigned short offset :  8;
  } ptr;
  struct {
    unsigned short final  :  1;
    unsigned short hlen   :  3;
    unsigned short dbit   :  4;
    unsigned short v      :  1;
    unsigned short w      :  1;
    unsigned short x      :  1;
    unsigned short y      :  1;
  } value;
  unsigned short final    :  1;
};

union huffpair {
  struct {
    unsigned short final  :  1;
    unsigned short bits   :  3;
    unsigned short offset : 12;
  } ptr;
  struct {
    unsigned short final  :  1;
    unsigned short hlen   :  3;
    unsigned short x      :  4;
    unsigned short y      :  4;
  } value;
  unsigned short final    :  1;
};

struct hufftable {
  union huffpair *table;
  unsigned short linbits;
  unsigned short startbits;
};


typedef struct
{
   const unsigned char *l;
   const unsigned char *s;
   const unsigned char *m;
}mp3_sfbwidth;

typedef struct
{
   unsigned char allocation[2][32];
   unsigned char scfsi[2][32];
}mp3_l2sdi;
// bit allocation table 
typedef struct {
  unsigned short nbal;
  unsigned short offset;
}layer2_bitalloc;

//possible quantization per subband table 
typedef struct {
   unsigned int sblimit;
   unsigned char offsets[30];
} layer2_sbquant;

// quantization class table 
typedef struct {
  unsigned short nlevels;
  unsigned char group;
  unsigned char bits;
  int C;
  int D;
} layer2_quantclass;


#define DEQUANTIZE_LUT 0
#define DEQUANTIZE_ITP 1

typedef struct channel 
{
   // from side info 
   unsigned short part2_3_length;
   unsigned short big_values;
   unsigned short global_gain;
   unsigned short scalefac_compress;

   unsigned char flags;
   unsigned char block_type;
   unsigned char table_select[3];
   unsigned char subblock_gain[3];
   unsigned char region0_count;
   unsigned char region1_count;
   unsigned short region_width[3];
   unsigned char *sfbwidth;
   //from main_data 
   unsigned char scalefac[39];   /* scalefac_l and/or scalefac_s */
}gr_ch_struct;




typedef struct
{
   gr_ch_struct *granule;
   int mode;
   int mode_extension;         
   //int emphasis;
   int bitrate;   

   int sampleidx;
   unsigned short crc_check;    
   unsigned short crc_target;  
   int flags;        
   int head_crc_side;
   int slot_num;
   
   int samples_pf;
   int samples_psb;
   //-------------------------
   int pts_time;
   int buf_valid;
   unsigned char *bs_buf;
   //int buf_left;
   unsigned char *bs_ptr;
   //-------------------------
   //unsigned char *buf;     // input bitstream buffer 
   //int gnl_left;   //this buffer left byte numbers
   //unsigned char *mdb;
   int mdb_num;
   unsigned char *mdbptr;
   //int ado_gnl;
   unsigned char * ado_cache_ptr;  //the cache can be used for 8 bits or 16 bits or 32 bits
   unsigned int  ado_cache;  
   int ado_cache_left;  //the cache left bit numbers
   int frame_left_bytes;
   int freerate;     // free bitrate (fixed) 
   int syn_ofs[PEAK_LEN];
   int hcs_size[PEAK_LEN];
   int da_size[PEAK_LEN];

   unsigned char *hcs_cache_ptr;
   int hcs_cache_left;
   unsigned int hcs_cache;

   //side information
   unsigned int main_data_begin;
   unsigned int phase;        // current processing phase 
   unsigned char scfsi[2];
   //layer 1 and layer 2
   int sblimit;
   int bound;
   unsigned char *offsets;


   //unsigned char *host_bs_addr;
   //int blk_num;
   //int *host_pcm_addr;
   int gr_idx;
   int frame;
   int file_size;
   int MPEG2;
   int first_frame_offset;   
   //int error;
   int *fill_pcm[2];
   int layer;

   int nch;
   int samplerate;

   int mpeg2_1th;
   int layer_1th;
   int samplerate_1th;        
   int total_time;  //unit is ms
   int total_frame;
   int frame_time;
   int play_time;  //unit is 10^(-2) ms
   int fending;

   //int init_sync;
   unsigned int vbr_toc[MAX_TOC_INT_SIZE];
   int vbr_flag;
   int vbr_frame_num;
   int vbr_file_size;
   int vbr_exist;
   int vbr_bitrate;
   int vbri_table_size;
   int vbri_frames_per_entry;
   int vbri_real_table_size;
   int vbri_bytes_per_entry;
   int vbri_table_scale;
   
   int (*bs_read)(unsigned char *, int , int *,int *);
#ifdef MP3_DEBUG     
   unsigned char *next_syn;
   int debug_error;
#endif      
   unsigned char *mp3_dbuf;
   int *mp3_g_buf0;
   int *mp3_g_buf1;
   int *mp3_g_buf2;
   int *mp3_g_overlap[2];
   int *mp3_g_filter0;
   int *mp3_g_filter1;
   unsigned char *mp3_g_mdb;
   //unsigned char *mp3_g_bs_buf;
   gr_ch_struct *mp3_gr0_ch;
   gr_ch_struct *mp3_gr1_ch;
   int *mp3_sqrt_root32;
#if defined(CERAMAL_3) || defined(CERAMAL_5)
   short *mp3_D_win32_0;
   short *mp3_D_win32_16;
   short *mp3_D_win32;
   short *mp3_imdct_s_16;
   short *mp3_window_s_16;
   short *mp3_cs_16;
   short *mp3_ca_16;
   short *mp3_window_l_16;
#else
   int *mp3_D_win32_0;
   int *mp3_D_win32_16;
   int *mp3_D_win32;
   int *mp3_imdct_s_16;
   int *mp3_window_s_16;
   int *mp3_cs_ca_16;
   int *mp3_window_l_16;
#endif
   int *mp3_root_table_32;
   unsigned char *mp3_pretab;
   unsigned int *mp3_exponent;
   int *mp3_root_table;
   unsigned short *mp3_crc_table;
   unsigned char *mp3_mixed_l_num;
   unsigned char *mp3_sflen_table;
   unsigned char *mp3_nsfb_table;
   unsigned short ** mp3_huff_pair_table;
   unsigned char *mp3_huff_pair_linbits;
   unsigned char *mp3_huff_pair_startbits;
   short *mp3_is_table_16;
   short *mp3_is_lsf_table_16;
   int *g_imdct_buf;
   mp3_sfbwidth mp3_sfbwidth_table;
   //layer 2
   mp3_l2sdi *mp3_g_l2sdi;
   int *mp3_g_l2_buf[2];
   int *mp3_g_l2_sbsample[2];
   unsigned char *mp3_g_l2_scalefactor;
   int *mp3_mantissa;
   int *mp3_sf_table;
   int total_parser_byte;
   int vbr_avg_slot;
   int avg_bitrate;
   int consume_size;
   int old_total_time;
   int frame_num;
   S64 sum_bitrate;
} mp3dec;

//-----------------------------------------------------------------
//data structure extern definition


extern mp3dec *pmd;

//-----------------------------------------------------------------
//-----------------------------------------------------------------
//extern definition 
//--------------------------------------------------------------------
extern const mp3_sfbwidth c_mp3_sfbwidth_table[9];
extern const int c_mp3_sqrt_root32[7][7];
#if defined(CERAMAL_3) || defined(CERAMAL_5)
extern const short c_mp3_D_win32_0[2][32];
extern const short c_mp3_D_win32_16[2][14];
extern const short c_mp3_D_win32[15][32];
#else
extern const int c_mp3_D_win32_0[2][16];
extern const int c_mp3_D_win32_16[2][7];
extern const int c_mp3_D_win32[15][16];
#endif


extern const int c_mp3_root_table_32[7];
extern const unsigned char c_mp3_pretab[22];
extern const int c_mp3_mantissa[258];
extern const unsigned int c_mp3_exponent[33];
extern const int c_mp3_root_table[7];
extern const unsigned short c_mp3_crc_table[256];
extern const unsigned int c_mp3_bitrate_table[5][15];
extern const unsigned char c_mp3_sfb_48000_long[22];
extern const unsigned char c_mp3_sfb_44100_long[22];
extern const unsigned char c_mp3_sfb_32000_long[22];
extern const unsigned char c_mp3_sfb_48000_short[39];
extern const unsigned char c_mp3_sfb_44100_short[39];
extern const unsigned char c_mp3_sfb_32000_short[39];
extern const unsigned char c_mp3_sfb_48000_mixed[38];
extern const unsigned char c_mp3_sfb_44100_mixed[38];
extern const unsigned char c_mp3_sfb_32000_mixed[38];
extern const unsigned char c_mp3_sfb_24000_long[22];
extern const unsigned char c_mp3_sfb_22050_long[22];
extern const unsigned char c_mp3_sfb_24000_short[39];
extern const unsigned char c_mp3_sfb_22050_short[39];
extern const unsigned char c_mp3_sfb_16000_short[39];
extern const unsigned char c_mp3_sfb_24000_mixed[36];
extern const unsigned char c_mp3_sfb_22050_mixed[36];
extern const unsigned char c_mp3_sfb_16000_mixed[36];
extern const unsigned char c_mp3_sfb_8000_long[22];
extern const unsigned char c_mp3_sfb_8000_short[39];
extern const unsigned char c_mp3_sfb_8000_mixed[39];
extern const unsigned char c_mp3_mixed_l_num[9];
extern const unsigned char c_mp3_sflen_table[16];
extern const unsigned char c_mp3_nsfb_table[6][3][4];
extern const unsigned int c_mp3_samplerate_table[3];
extern const unsigned short *c_mp3_huff_pair_table[32];
extern const unsigned char c_mp3_huff_pair_linbits[32];
extern const unsigned char c_mp3_huff_pair_startbits[32];
extern const unsigned short c_mp3_hufftabA[28];
extern const unsigned short c_mp3_hufftabB[16];
extern const unsigned short *mp3_huff_quad_table[2];

#if defined(CERAMAL_3) || defined(CERAMAL_5)
extern const short c_mp3_imdct_s_16[6][6];
extern const short c_mp3_window_s_16[12];
extern const short c_mp3_cs_16[8];
extern const short c_mp3_ca_16[8];
extern const short c_mp3_window_l_16[36];
#else
extern const int c_mp3_imdct_s_16[6][3];
extern const int c_mp3_window_s_16[6];
extern const int c_mp3_cs_ca_16[8];
extern const int c_mp3_window_l_16[18];
#endif
extern const short c_mp3_is_table_16[7];
extern const short c_mp3_is_lsf_table_16[2][15];
extern const int c_mp3_sf_table[63];

extern S64 mp3d_macr_a0,mp3d_macr_a1;

extern unsigned char *mp3d_sram_ptr_save,*mp3d_heap_ptr_save;
extern int mp3d_sram_len_save,mp3d_heap_len_save;

#endif
