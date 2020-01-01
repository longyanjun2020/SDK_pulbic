#ifndef __MP3_L3_ENCODER_STRUCT_INCLUDE_FILE__
#define __MP3_L3_ENCODER_STRUCT_INCLUDE_FILE__




#define STEREO          0
#define JOINT_STEREO    1
#define DUAL_CHANNEL    2
#define MONO            3
   
#define MAX_MP3_SIZE        2880
typedef struct {
        unsigned char buf[MAX_MP3_SIZE];  
        int     totbit;  
#ifdef NEW_BITSTREAM
        unsigned int  bs_cache;
        int           bs_cache_left;
        unsigned char *bs_cache_ptr;
#else        
        int     buf_byte_idx; 
        int     buf_bit_idx;
#endif        
} III_Bit_stream;


#define SFBMAX SBMAX_l 

typedef struct {
    int     l[1 + SBMAX_l];
} scalefac_struct;



typedef struct {
    int     *xr;
    int     scalefac[SBMAX_l];
    int     xrpow_max;

    int     part2_3_length;
    int     big_values;  //big_values 程spectral line index(2计)
    int     count1;  //count1 程spectral line index (2计)
    int     global_gain;
    int     scalefac_compress;
    int     table_select[3];
    int     region0_count;
    int     region1_count;
    int     preflag;

    int     scalefac_scale;
    int     count1table_select;

    int     part2_length;
    int     sfbmax;
    int     count1bits;    //count1 ノ奔bit 计ヘ
    const int *sfb_partition_table;
    int     slen[4];

    int     max_nonzero_coeff;
} gr_info;

typedef struct {
    gr_info tt[2][2];
    int     main_data_begin;

    int     resvDrain_post;
    int     scfsi[2][4];
} III_side_info_t;


typedef struct {
    int region0_count;
    int region1_count;
}subdv;
                                      


#define MFSIZE (528+1152)
//#define MAX_HEADER_BUF 256
#define MAX_HEADER_BUF 9
#define MAX_HEADER_LEN 40    /* max size of header is 38 */
typedef struct {
 int     write_timing;
 unsigned char *write_ptr; 
 int     ptr;
 unsigned char    buf[MAX_HEADER_LEN];
}header_struct;

typedef struct {

   int   num_channels;  
   int   in_samplerate;  
   int   mode;
   int   brate; 
   int   error_protection; 
   int   disable_reservoir; 
   int   lowpassfreq;  
   int   version;  
   int   framesize;
   int   frameNum;    
   int   frame_bits;

   //------------------------------------------------------------------

   int full_bitrate_index;
   short mfbuf[2][MFSIZE];

   int     mode_gr;  
   int     resvLimit;
   int     maxmp3buf;
   int     mf_samples_to_encode;
   int     mf_size;
   int     bitrate_index;
   int     samplerate_index;
   int     mode_ext;
   int     last_mode_ext;
   int last_sum_ms,last_sum_lr;


   //float   lowpass1, lowpass2; 

   III_Bit_stream bs;
   III_side_info_t l3_side;

   int     padding;   
   int     frac_SpF;
   int     slot_lag;

   int     OldValue[2];
   int     CurrentStep[2];


   int     sideinfo_len;  //include 4 byte header, 2 byte crc and sideinfo

   int   *sb_sample[3][2];
   //int   amp_filter[32];
   header_struct header[MAX_HEADER_BUF];
   int     h_ptr;
   int     w_ptr;

   int     ResvSize;  
   int     ResvMax;    

   //int scalefac_band_l[1 + SBMAX_l];
   int *scalefac_band_l;
   int thm_l[4][SBMAX_l];

   int total_frame_bits;
   int old_index;
   int reservoir_old[8];
   int pe_old[8];
   int use_preflag_scale;
   int data_bits;
   int num_header;
   int start_header;
   int sb_flag;    
   schar bv_scf[576];    
   int *l3_enc;
   int *xrpow[3];
   int sfb_width[SFBMAX];    
   int last_mask[2][SBMAX_l];    

   int xr_sqrt_sum[SBMAX_l];
   int scale[SBMAX_l];
   int upperbound[SBMAX_l];
   int scalefac[SBMAX_l];  
#if (PAM_SOLUTION==1)
   schar exp_buf[4][22]; 
   schar last_mask_exp[2][22];
#endif
   int *g_xr[2];

   int *g_buffer0;
   int *g_buffer1;
   int *g_buffer2;
   int *g_buffer3;
   unsigned int sync_header;
}mp3e_global_struct;



#define HTN	34

struct huffcodetab {
    int xlen;    
    int linmax;  
    const short *table;  
    const schar *hlen;    
};


#define IXMAX_VAL 8206  

#define PRECALC_SIZE (IXMAX_VAL+2)



extern const struct huffcodetab mp3e_l3_ht[HTN];
extern const schar mp3e_l3_hlen_t32[];
extern const schar mp3e_l3_hlen_t33[];

extern const unsigned int mp3e_huff_bigtbl[256];
extern const unsigned int mp3e_huff_table23[9];
extern const unsigned int mp3e_huff_table56[16];

extern const int mp3e_scfsi_sfb[5];

extern const int      mp3e_l3_bitrate_table[3][16];


extern const int mp3e_l3_nr_of_sfb_block[6][3][4];
extern const int mp3e_l3_pretab[SBMAX_l];
extern const int mp3e_slen1_tab[16];
extern const int mp3e_slen2_tab[16];

extern const scalefac_struct mp3e_l3_sfBandIndex[9];

extern const subdv mp3e_l3_subdv_table[23];

extern const int mp3e_l3_istep_tab[16];
extern const int mp3e_l3_ilog_tab[513];
extern const int mp3e_l3_isqrt_tab[513];

//extern int frame_num;

#endif

