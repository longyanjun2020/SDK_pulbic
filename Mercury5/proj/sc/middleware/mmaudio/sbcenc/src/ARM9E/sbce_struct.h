#ifndef _SBC_ENCODER_STRUCTURE_INCLUDE_FILE_
#define _SBC_ENCODER_STRUCTURE_INCLUDE_FILE_


#ifdef WIN32
typedef __int64 S64;
typedef unsigned __int64 U64;
#define INLINE __inline 

#else
typedef long long S64;
typedef unsigned long long U64;
#define INLINE __inline 
#endif

#ifdef __MIPS_4KE__
#define USE_MIPS32 __attribute__((nomips16))
#else
#define USE_MIPS32 
#endif


#define SBC_NB_4  0x00
#define SBC_NB_8  0x01
#define SBC_NB_12 0x02
#define SBC_NB_16 0x03

#define SBC_FS_16 0x00
#define SBC_FS_32 0x01
#define SBC_FS_44 0x02
#define SBC_FS_48 0x03

#define SBC_SYNCWORD 0x9C
#define SBC_AM_LOUDNESS    0x00
#define SBC_AM_SNR      0x01


#define SBC_CM_MONO     0x00
#define SBC_CM_DUAL_CHANNEL   0x01
#define SBC_CM_STEREO      0x02
#define SBC_CM_JOINT_STEREO   0x03

#define SBC_SB_4  0x00
#define SBC_SB_8  0x01


#define SBC_OK 0
#define SBC_PARAMETER_ERROR 1




#define LOUDNESS  SBC_AM_LOUDNESS
#define SNR       SBC_AM_SNR

#define fabs(x) ((x) < 0 ? (-x) : (x))


typedef signed char schar;


typedef struct {
   short *pcm_buf;
   unsigned char *bs_buf;
   int bs_len;
   int togglePeriod;
   int bitPoolAlt;
   int toggle_num;
   int error;
   int rate;
   int channels;
   int blocks;
   int subbands;
   int bitpool;
   int allocation;
   int channel_mode;
   int srate_idx;
   unsigned char scale_factor[2][8];     // only the lower 4 bits of every element are to be used 
   int sb_sample[16][2][8];
#ifdef SBC_ENC_PCM_COPY
   short pcm_sample[2][16*8];
#endif

   short *filter_buf;
//------------------------------
#ifndef SBC_ENC_REMOVE_SUBBAND4_CODE_CM
   schar *sbc_offset4;
   short *d_win4;
#endif
   schar *sbc_offset8;
   unsigned char *sbc_crc_table;
   short *d_win8;
   int *cos16;
   int enc_phase[2];
   int enc_pre_phase[2];
   unsigned char sbc_header0;
   unsigned char sbc_header1;
}sbc_t;


extern const schar c_sbc_offset4[4][4]; 
extern const schar c_sbc_offset8[4][8];
extern const unsigned char c_sbc_crc_table[256];
extern const short c_d_win4[8][9];
extern const short c_d_win8[16][9];
extern const int c_cos16[8];
extern sbc_t *sbc;

unsigned char sbc_crc8(unsigned char * data, int len);
void sbc_calculate_bits(int (*bits)[8], int sf);

void oem_sbce_ram_init(void);
USE_MIPS32 void sbc_analyze(void);


extern int frame;
#endif 

