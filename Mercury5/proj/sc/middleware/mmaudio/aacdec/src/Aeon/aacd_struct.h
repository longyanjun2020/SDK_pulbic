#ifndef __STRUCTS1_H__
#define __STRUCTS1_H__


#define INLINE __inline
#define ALIGN

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#define ALLOW_SMALL_FRAMELENGTH

#define ADDR_INT_ALIGN(x) (((x)+3) & (~0x3))
#define ADDR_CACHE_LINE_ALIGN(x) (((x)+15) & (~0xf))

#ifdef LC_ONLY_DECODER
  #undef LTP_DEC
  #undef MAIN_DEC
  #undef DRM
  #undef ALLOW_SMALL_FRAMELENGTH
  #undef ERROR_RESILIENCE
#endif

#ifdef DRM
# ifndef SCALABLE_DEC
#  define SCALABLE_DEC
# endif
#endif

#ifdef __aeon__
typedef unsigned long long uint64_t;
typedef long long int64_t;
typedef long long S64;
#else
typedef unsigned __int64 uint64_t;
typedef __int64 int64_t;
typedef __int64 S64;
#endif   
#ifndef __aeon__
extern S64 aad_macr_a0,aad_macr_a1,aad_macr_a2;
#endif
#define FALSE   0
#define TRUE    1


//#define NON_AAC_MAX_SIZE (2048*1024)

/* Bitstream */
#define LEN_BYTE  8
#define LEN_TAG   4
#define LEN_SE_ID 3


#define INVALID_SBR_ELEMENT 255


#define ZERO_HCB       0
#define FIRST_PAIR_HCB 5
#define ESC_HCB        11
#define QUAD_LEN       4
#define PAIR_LEN       2
#define NOISE_HCB      13
#define INTENSITY_HCB2 14
#define INTENSITY_HCB  15

#define ONLY_LONG_SEQUENCE   0x0
#define LONG_START_SEQUENCE  0x1
#define EIGHT_SHORT_SEQUENCE 0x2
#define LONG_STOP_SEQUENCE   0x3
/* Syntax elements */
#define ID_SCE 0x0
#define ID_CPE 0x1
#define ID_CCE 0x2
#define ID_LFE 0x3
#define ID_DSE 0x4
#define ID_PCE 0x5
#define ID_FIL 0x6
#define ID_END 0x7


#define EXT_FIL            0
#define EXT_FILL_DATA      1
#define EXT_DATA_ELEMENT   2
#define EXT_DYNAMIC_RANGE 11
#define ANC_DATA           0


#define MAX_SFB             51
#define MAX_LTP_SFB         40
#define MAX_LTP_SFB_S        8

#define MAX_CHANNELS        2
#define MAX_SYNTAX_ELEMENTS 6
#define MAX_WINDOW_GROUPS    8

#define COEF_BITS 28
#define COEF_PRECISION (1 << COEF_BITS)
#define REAL_BITS 14 // MAXIMUM OF 14 FOR FIXED POINT SBR
#define REAL_PRECISION (1 << REAL_BITS)

/* FRAC is the fractional only part of the fixed point number [0.0..1.0) */
#define FRAC_SIZE 32 /* frac is a 32 bit integer */
#define FRAC_BITS 31
#define FRAC_PRECISION ((unsigned int)(1 << FRAC_BITS))
#define FRAC_MAX 0x7FFFFFFF



#define COEF_BITS_30    30
#define COEF_PRECISION_30 (1 << COEF_BITS_30)
#define COEF_BITS_29    29
#define COEF_PRECISION_29 (1 << COEF_BITS_29)
#define COEF_BITS_28    28
#define COEF_PRECISION_28 (1 << COEF_BITS_28)
#define REAL_BITS_14    14 // MAXIMUM OF 14 FOR FIXED POINT SBR
#define REAL_PRECISION_14 (1 << REAL_BITS_14)

#define REAL_CONST_14(A) (((A) >= 0) ? ((int)((A)*(REAL_PRECISION_14)+0.5)) : ((int)((A)*(REAL_PRECISION_14)-0.5)))
#define COEF_CONST_28(A) (((A) >= 0) ? ((int)((A)*(COEF_PRECISION_28)+0.5)) : ((int)((A)*(COEF_PRECISION_28)-0.5)))
#define COEF_CONST_29(A) (((A) >= 0) ? ((int)((A)*(COEF_PRECISION_29)+0.5)) : ((int)((A)*(COEF_PRECISION_29)-0.5)))
#define COEF_CONST_30(A) (((A) >= 0) ? ((int)((A)*(COEF_PRECISION_30)+0.5)) : ((int)((A)*(COEF_PRECISION_30)-0.5)))

#define FRAC_BITS_31 31
#define FRAC_PRECISION_31 ((unsigned int)(1 << FRAC_BITS_31))
#define SCALE_31(A) (((A) == 1.00) ? ((int)FRAC_MAX) : (((A) >= 0) ? ((int)((A)*(FRAC_PRECISION_31)+0.5)) : ((int)((A)*(FRAC_PRECISION_31)-0.5))))

#define FRAC_CONST(A) (((A) == 1.00) ? ((int)FRAC_MAX) : (((A) >= 0) ? ((int)((A)*(FRAC_PRECISION)+0.5)) : ((int)((A)*(FRAC_PRECISION)-0.5))))
#define LOG2_MIN_INF REAL_CONST_14(-10000)


#define SHORT_WIN_SIZE     128
#define LONG_WIN_SIZE      1024

#define TNS_MAX_ORDER 12
#define TNS_MAX_ORDER_LONG 12
#define TNS_MAX_ORDER_SHORT 7
#define MAX_FILT_LONG 3
#define MAX_FILT_SHORT 1
#define WLOOP_INC_LONG 36  //max_filt_long(3) * max_order_long(12)
#define WLOOP_INC_SHORT 7  //max_filt_short(1) * max_order_short(7)
#define FLOOP_INC_LONG 12  //max_order_long(12)
#define FLOOP_INC_SHORT 7  //max_order_short(7)

#define CDW(a,b) ((b << 16) | (a & 0x0000ffff))

#define SCAN_AAC_MAX_FILE_SIZE (16*1024*1024)

typedef struct
{
    unsigned char number_pulse;
    unsigned char pulse_start_sfb;
    unsigned char pulse_offset[4];
    unsigned char pulse_amp[4];
} pulse_info;

typedef struct
{
    unsigned char n_filt[8];
    unsigned char coef_res[8];
    unsigned char length[8];
    unsigned char order[8];
    unsigned char direction[8];
    unsigned char coef_compress[8];
    unsigned char coef[56];
} tns_info;


typedef struct
{
    unsigned char max_sfb;
    unsigned char num_swb;
    unsigned char num_window_groups;
    unsigned char num_windows;
    unsigned char window_sequence;
    unsigned char window_group_length[8];
    unsigned char window_shape;
    unsigned char scale_factor_grouping;
   //----------------------------------
    unsigned short *swb_offset;
    unsigned short sect_sfb_offset[128];
    unsigned char sect_cb[128];
    unsigned char sect_start[128];
    unsigned char sfb_cb[128];
    short scale_factors[128];    //must 
    unsigned char ms_used[128];
    //---------------------------------
    unsigned char sect_num_group[8]; // number of sections in a group 
    short zero_size_group[8];

    unsigned char global_gain;
    unsigned char ms_mask_present;
    unsigned char noise_used;
    unsigned char is_used;
    unsigned char pulse_data_present;
    unsigned char tns_data_present;
    unsigned char gain_control_data_present;
    unsigned char predictor_data_present;

    pulse_info pul;
    tns_info tns;

} ic_stream; // individual channel stream 


#define AAC_BITSTREAM_SIZE (1536+16) //1536 is stereo frame max byte

#define HALF_AAC_BITSTREAM_SIZE ( AAC_BITSTREAM_SIZE/2)

#define GRANULE_NUM 8
#define GRANULE_SIZE 128



//------drc.cpp
#define DRC_REF_LEVEL 20*4 /* -20 dB */

typedef struct
{
    unsigned char present;

    unsigned char num_bands;
    unsigned char pce_instance_tag;
    unsigned char excluded_chns_present;
    unsigned char band_top[17];
    unsigned char prog_ref_level;
    unsigned char dyn_rng_sgn[17];
    unsigned char dyn_rng_ctl[17];
    unsigned char exclude_mask[MAX_CHANNELS];
    unsigned char additional_excluded_chns[MAX_CHANNELS];

    int ctrl1;
    int ctrl2;
} drc_info;


typedef struct
{
    unsigned short syncword;
    unsigned char id;
    unsigned char layer;
    unsigned char protection_absent;
    unsigned char profile;
    unsigned char sf_index;
    unsigned char private_bit;
    unsigned char channel_configuration;
    unsigned char original;
    unsigned char home;
    unsigned char emphasis;
    unsigned char copyright_identification_bit;
    unsigned char copyright_identification_start;
    unsigned short aac_frame_length;
    unsigned short adts_buffer_fullness;
    unsigned char no_raw_data_blocks_in_frame;
    unsigned short crc_check;

    /* control param */
    unsigned char old_format;
} adts_header;


typedef struct
{
    unsigned char element_instance_tag;
    unsigned char object_type;
    unsigned char sf_index;
    unsigned char num_front_channel_elements;
    unsigned char num_side_channel_elements;
    unsigned char num_back_channel_elements;
    unsigned char num_lfe_channel_elements;
    unsigned char num_assoc_data_elements;
    unsigned char num_valid_cc_elements;
    unsigned char mono_mixdown_present;
    unsigned char mono_mixdown_element_number;
    unsigned char stereo_mixdown_present;
    unsigned char stereo_mixdown_element_number;
    unsigned char matrix_mixdown_idx_present;
    unsigned char pseudo_surround_enable;
    unsigned char matrix_mixdown_idx;
    unsigned char front_element_is_cpe[16];
    unsigned char front_element_tag_select[16];
    unsigned char side_element_is_cpe[16];
    unsigned char side_element_tag_select[16];
    unsigned char back_element_is_cpe[16];
    unsigned char back_element_tag_select[16];
    unsigned char lfe_element_tag_select[16];
    unsigned char assoc_data_element_tag_select[16];
    unsigned char cc_element_is_ind_sw[16];
    unsigned char valid_cc_element_tag_select[16];
    unsigned char channels;
    unsigned char comment_field_bytes;
    unsigned char comment_field_data[257];
    unsigned char num_front_channels;
    unsigned char num_side_channels;
    unsigned char num_back_channels;
    unsigned char num_lfe_channels;
    unsigned char sce_channel[16];
    unsigned char cpe_channel[16];
} program_config;

//================================================================================
// LATM/LOAS header
typedef struct 
{
    unsigned int samplingFrequencyIndex;
    unsigned int samplingFrequency;
    unsigned int channelsConfiguration;
    int objectTypeIndex;
    int sbr_present_flag;
    int forceUpSampling;
    int downSampledSBR;
} mp4AudioSpecificConfig;  

typedef struct
{
   mp4AudioSpecificConfig mp4asc;
   program_config pce;
}mp4_data_struct;

typedef struct {
    int nFrameLength ; /*!< length in sample frames at core coder rate */
    unsigned int  nCoreCoderDelay ; /*!< core coder delay in sample frames at core coder rate */
    unsigned char bDependsOnCoreCoder ; /*!< */
    unsigned char ucExtensionFlag ; /*!< */
    unsigned char bPCEPresent ; /*!< signals the presence/validity of the PCE. */
    //tProgramConfigElement pce; /*!< a program config element, describing a single program */
} tGeneralAudioSpecificConfig ;

typedef struct {
             int  eAudioObjectType ; /*!< the core coder audio object type. \note <b>The type of this member has changed after release 4.0.6</b> */
    unsigned int  eExtensionAOT ; /*!< the extension audio object type (explict SBR signaling). */
    unsigned char bSbrPresent ; /*!< signals the presence of SBR information */
    unsigned char ucChannelConfiguration ; /*!< the channel configuration */

    unsigned int  nSamplingFrequency ; /*!< the AAC core sampling frequency */ 
    unsigned int  nExtensionSamplingFrequency ; /*!< the SBR output sampling frequency */
    
    tGeneralAudioSpecificConfig GASConfig ; /*!< MPEG-4 general audio config, containing further config info */
} tAudioSpecificConfig ;

enum { eLATM_MAX_PROGRAMS = 1, eLATM_MAX_LAYER=1, eLATM_MAX_NUM_SUBFRAMES=16} ;

typedef struct {
    unsigned char ucAudioMuxVersion ;
    unsigned char ucAudioMuxVersionA ;
    unsigned char bAllStreamsSameTimeFraming ;
    unsigned char ucNumSubFrames ;
    unsigned char ucNumProgram ;
    unsigned char ucNumLayers ;
    unsigned char bUseSameConfig ;
    unsigned char bOtherDataPresent ;
    unsigned char ucOtherDataLength ;
    unsigned char bCrcCheckPresent ;
    unsigned char ucCRC ;
    struct {
        unsigned char ucFrameLengthType ;
        unsigned char ucBufferFullness ;
        unsigned char ucStreamID ;
        unsigned int  unPayloadLengthInBits ;
        tAudioSpecificConfig ASConfig ;
    } sLayerInfo[eLATM_MAX_PROGRAMS][eLATM_MAX_LAYER] ;
    struct {
        unsigned char prog,lay ;
    } ProgLaySIndx[eLATM_MAX_PROGRAMS*eLATM_MAX_LAYER] ;
} tStreamMuxConfig ;


typedef struct {
    unsigned char bUseSameStreamMux ;
    tStreamMuxConfig sStreamMuxConfig ;
} tAudioMuxElement ;


typedef struct {
    unsigned int AudioMuxLengthBytes ;
    unsigned char bUseSameStreamMux;
    unsigned short syncword;
    int FrameLengthType; 
    tAudioMuxElement sLatm ;
} loas_header;

// End of LATM/LOAS header
//=====================================================================
typedef struct
{
    unsigned char copyright_id_present;
    schar copyright_id[10];
    unsigned char original_copy;
    unsigned char home;
    unsigned char bitstream_type;
    unsigned int bitrate;
    unsigned char num_program_config_elements;
    unsigned int adif_buffer_fullness;
    // maximum of 16 PCEs 
    //program_config pce[16];
} adif_header;


typedef struct  {
   unsigned char *buf_ptr;     // dynamic buffer pointer of  bitstream buffer 
   int buf_left; //this buffer left byte numbers
   unsigned int  cache;   //the cache can be used for 8 bits or 16 bits or 32 bits
   int cache_left;      //the cache left bit numbers
   int eof;
   int bits_consumed;   
} buffer_bs;

typedef struct  {
   unsigned char sbr_data[256+14];
   int sizePayload;
   int extensionType;
   int elementID;  
   int nrElements;   
}sbr_bitstream;

typedef struct
{
   unsigned char fr_channels;  // number of elements in current frame 
 
   unsigned char fr_ch_ele;
   //unsigned char element_output_channels[MAX_SYNTAX_ELEMENTS];

   unsigned char window_shape_prev[MAX_CHANNELS];
   int *pcm_out[MAX_CHANNELS];  //time-domain output
   int *overlap[MAX_CHANNELS];

   int *long_window[2];
   int *short_window[2];

   //aac bit-stream
   unsigned char *bsbuf;   
   int buf_left;
   int buf_left2;
   unsigned char *ado_cache_ptr;
   unsigned int  ado_cache;   //the cache can be used for 8 bits or 16 bits or 32 bits
   int ado_cache_left;  //the cache left bit numbers
   int read_len;              //read byte length for a period of time //are only used on LOAS bitstream

   int samplerate;

   //int frame;
   int mp4_flag;
   int channel_num;

   int sample_rate_index;
   int header_type;
   int chunk_left;   //only used on AVP
   int frame_left;   //only used on AVP
   int audio_video;
   int pns_rndstate;
   int HaveConfig;   // had configure
   adif_header adif;
   adts_header adts;
   loas_header loas;
   mp4AudioSpecificConfig mp4asc; 
   program_config pce;
   int object_type;
   int first_frame;
   int fending;
   int total_time;  //unit is ms
   S64 play_time;  //unit is 0.01ms
   int pts_cur_time;
   int pts_next_time;
   int pts_update_flag;
   int pts_frame_start;
   int pts_this_chunk;
   int just_buf_in;
   int frame_time;
   int file_size;   
#ifdef SBR_DEC
   int sbr_present_flag;
   int forceUpSampling;
   int downSampledSBR;

   /* determines whether SBR data is allocated for the gives element */
   //unsigned char sbr_alloced[MAX_SYNTAX_ELEMENTS];
   //unsigned char element_id[MAX_SYNTAX_ELEMENTS];
   sbr_info *sbr[MAX_SYNTAX_ELEMENTS];
   //unsigned int postSeekResetFlag;

   int real_channel;

#if defined(PS_DEC) 
   unsigned char ps_used[MAX_SYNTAX_ELEMENTS];
   unsigned char ps_used_global;

#endif
#endif
    int id3_len;
   unsigned char *aac_g_bsbuf;    /* input bitstream buffer */
   drc_info *aac_g_drc;
   //DEQUAN Table
   int *aac_sqrt_root32; //[4][7];    
   int *aac_mantissa; //[];            
   unsigned char *aac_exponent;   //[];  
   unsigned char *aac_sqrtExp; //[];  
   int *aac_sqrt; //[];            
   int *aac_root_table;  //[];          
   int *aac_root_table_2;   //[];        
   int *aac_root_table_3;   //[];        
   int *aac_root_table_4;   //[];        
   int *aac_pow05_table; //[4];       

//Dehumm Table
   unsigned short *aac_cb0;
   unsigned short *aac_hcb1_1;    //[32];     
   unsigned short *aac_hcb1_2;    //[113];    
   unsigned short *aac_hcb2_1;    //[32];     
   unsigned short *aac_hcb2_2;    //[85];     
   unsigned short *aac_cb3;    //[124];       
   unsigned short *aac_hcb4_1;    //[32];     
   unsigned short *aac_hcb4_2;    //[184];    
   short *aac_cb5;    //[120];                
   unsigned short *aac_hcb6_1;    //[32];     
   short *aac_hcb6_2;    //[125];             
   unsigned short *aac_cb7;    //[98];        
   unsigned short *aac_cb9;    //[236];       
   unsigned short *aac_hcb8_1;    //[32];     
   unsigned short *aac_hcb8_2;    //[83];     
   unsigned short *aac_hcb10_1;    //[64];    
   unsigned short *aac_hcb10_2;    //[209];   
   unsigned short *aac_hcb11_1;    //[32];    
   unsigned short *aac_hcb11_2;    //[374];   

//FFT Table
   int *aac_cfft_tab_64;    //[128];
   int *aac_mdct256;    //[128];
   int *aac_cfft_tab_512;    //[1024];
   int *aac_mdct2048;    //[1024];

   int *aac_sine_long_1024;
   int *aac_sine_short_128;
   int *aac_kbd_long_1024;
   int *aac_kbd_short_128;   

#ifdef SBR_DEC   
   int *sbr_stack;
   int *pcm_stack;
   sbr_info *pg_sbr[2];

   int *pg_sbr_buf1;
   int *pg_sbr_buf0;
   sbr_ch_info *pg_sbr_ch0;	
   sbr_ch_info *pg_sbr_ch1;
   //pg_G_aac_temp_prev 只是一個address pointer, it occupy only 4 byte on this structure.
   //指到的位址是寬是64,長是5,沒有限定高的 3D int array
   int (*pg_G_aac_temp_prev)[5][64];
   int (*pg_Q_aac_temp_prev)[5][64];

   int *pg_aac_qmfa_x;
   int *pg_aac_qmfs_v;

   //pg_aac_E_curr 只是一個address pointer, it occupy only 4 byte on this structure.
   //指到的位址是寬是MAX_QMF_BANDS, 沒有限定長的 2D int array
   
   int (*pg_aac_E_curr)[MAX_QMF_BANDS];    //[MAX_L_E][MAX_QMF_BANDS]
   sbr_hfadj_info *pg_aac_adj;


   sbr_bitstream sbr_bs_info[2];
   buffer_bs sbr_bs;   
#ifdef PS_DEC
   int *ps_stack;
   qmf_t (*pg_aac_hyb_buffer)[12];
   ps_info *pg_ps;
   qmf_t *pg_aac_work;
   qmf_t *pg_aac_hyb_temp;
#endif
#endif
   int *freebuf[2];
   int *aac_g_buf0;
   int *aac_g_buf1;
   int *aac_g_buf2;

   int Channels; 
   unsigned char window_shape[2];
   unsigned char window_sequence[2];
   int *spec_coef[2];
   schar channelsPerElement[6];
   int sbr_nstream;
   int enable_sbr;
   int avg_bitrate;
   int total_read_num;
   int consume_size;
   int slot_num;
   int sum_slot_num;
   int frame_num;
   int old_total_time;
   int fbrowser;
   int tt_frame_cnt;
   int max_frame;
}aac_dec;

//DEQUAN Table
extern const int c_aac_sqrt_root32[4][7];
extern const int c_aac_mantissa[258];
extern const unsigned char c_aac_exponent[258];
extern const unsigned char c_aac_sqrtExp[7];
extern const int c_aac_sqrt[7];
extern const int c_aac_root_table[4];
extern const int c_aac_root_table_2[4];
extern const int c_aac_root_table_3[4];
extern const int c_aac_root_table_4[4];
extern const int c_aac_pow05_table[4];


//Dehumm Table

extern const unsigned short c_aac_cb0[170];
extern const unsigned short c_aac_hcb1_1[32];
extern const unsigned short c_aac_hcb1_2[113];
extern const unsigned short c_aac_hcb2_1[32];
extern const unsigned short c_aac_hcb2_2[85];
extern const unsigned short c_aac_cb3[124];
extern const unsigned short c_aac_hcb4_1[32];
extern const unsigned short c_aac_hcb4_2[184];
extern const short c_aac_cb5[120];
extern const unsigned short c_aac_hcb6_1[32];
extern const short c_aac_hcb6_2[125];
extern const unsigned short c_aac_cb7[98];
extern const unsigned short c_aac_cb9[236];
extern const unsigned short c_aac_hcb8_1[32];
extern const unsigned short c_aac_hcb8_2[83];
extern const unsigned short c_aac_hcb10_1[64];
extern const unsigned short c_aac_hcb10_2[209];
extern const unsigned short c_aac_hcb11_1[32];
extern const unsigned short c_aac_hcb11_2[374];

//FFT table
extern const int c_aac_cfft_tab_64[64];
extern const int c_aac_mdct256[64];
extern const int c_aac_cfft_tab_512[512];
extern const int c_aac_mdct2048[512];
extern const int c_aac_sine_long_1024[512];
extern const int c_aac_sine_short_128[64];
extern const int c_aac_kbd_long_1024[512];
extern const int c_aac_kbd_short_128[64];


extern const unsigned short *const aac_swb_offset_1024_window[];
extern const unsigned short *const aac_swb_offset_128_window[];


extern const unsigned char aac_num_swb_1024_window[];
extern const unsigned char aac_num_swb_128_window[];



extern aac_dec *pad;
extern int *g_aacd_sram_ptr_save,*g_aacd_heap_ptr_save;

//extern const int *const aac_deq_coef_table[];
extern const unsigned char aac_tns_maxsfb_long[];
extern const unsigned char aac_tns_maxsfb_short[];



#endif

