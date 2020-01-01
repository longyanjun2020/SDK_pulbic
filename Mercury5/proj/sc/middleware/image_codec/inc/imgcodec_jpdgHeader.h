#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION
#ifdef IMGCODEC_JPD_PROGRESSIVE

//------------------------------------------------------------------------------
// jpgdecoder.h
// Small JPEG Decoder Library v0.93b
// Last updated: Dec. 28, 2001
// Copyright (C) 1994-2000 Rich Geldreich
// richgel@voicenet.com
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//------------------------------------------------------------------------------
//#define NO_OUTPUT_1

#ifndef JPEG_DECODER_H
#define JPEG_DECODER_H
//------------------------------------------------------------------------------

//#include "common.h"
#include "imgcodec_jpdHeader.h"
#include "imgcodec_common.h"

//#define OUTPUT_YUV
#define MULTI_ROW_SCAN //[Jason]#define MULTI_ROW_SCAN
#ifdef MULTI_ROW_SCAN
    #define MAX_SCAN_NUM 20
#endif
#define SKIP_REFINESCAN_FOR_LARGESIZE
#define HW_IDCT
#define ROITestCode
//------------------------------------------------------------------------------

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#define QUANT_TYPE s16
#define BLOCK_TYPE s16
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// May need to be adjusted if support for other colorspaces/sampling factors is added
#define JPGD_MAXBLOCKSPERMCU 10
//------------------------------------------------------------------------------
#define JPGD_MAXHUFFTABLES   8
#define JPGD_MAXQUANTTABLES  4
#define JPGD_MAXCOMPONENTS   4
#define JPGD_MAXCOMPSINSCAN  4
//------------------------------------------------------------------------------
// Increase this if you increase the max width!
#define JPGD_MAXBLOCKSPERROW 2048
#define JPGD_MAXDCTPERROW    16000
//------------------------------------------------------------------------------
// Max. allocated blocks
#define JPGD_MAXBLOCKS    100
//------------------------------------------------------------------------------
#define JPGD_MAX_HEIGHT 8192
#define JPGD_MAX_WIDTH  8192

#define JPGD_PRG_MAX_HEIGHT     1024
#define JPGD_PRG_MAX_WIDTH      1024
#define JPGD_PRG_MAX_PERBLOCK   3

//------------------------------------------------------------------------------
/* JPEG specific errors */
//------------------------------------------------------------------------------

#define JPGD_GRAYSCALE 0
#define JPGD_YH1V1     1
#define JPGD_YH2V1     2
#define JPGD_YH1V2     3
#define JPGD_YH2V2     4
#define JPGD_YH4V1     5
//------------------------------------------------------------------------------
//const int JPGD_FAILED = -1;
//const int JPGD_DONE = 1;
//const int JPGD_OKAY = 0;
#define JPGD_FAILED -1
#define JPGD_DONE    1
#define JPGD_OKAY    0

//------------------------------------------------------------------------------

#define BLOCK_TYPE_EOP    0
#define BLOCK_TYPE_Y      1
#define BLOCK_TYPE_V      2
#define BLOCK_TYPE_U      3

#define SYMBOL_TYPE_DC    0
#define SYMBOL_TYPE_UDP   1
#define SYMBOL_TYPE_RSTDC 2
#define SYMBOL_TYPE_AC    3

#ifndef SEEK_SET
#  define SEEK_SET        0       /* Seek from beginning of file.  */
#  define SEEK_CUR        1       /* Seek from current position.  */
#  define SEEK_END        2       /* Set file pointer to EOF plus "offset" */
#endif

#define RST0 0xD0
#define StackBufSize      5*1024

typedef enum
{
    JPGD_DECODE_ERROR = 0,
    JPD_HWVLD_ECS_ERR,
    JPD_DECODE_DONE,
    JPD_MRC_HIGH_EMPTY,
    JPGD_SUCCESS_ABORTED,
    JPGD_WAIT_SCL_TIME_OUT,
    JPGD_WAIT_JPD_TIME_OUT,
} HW_IDCT_RESULT;


//------------------------------------------------------------------------------
typedef struct huff_tables_tag
{
  u32  look_up[256];
  u8 code_size[256];
  // FIXME: Is 512 tree entries really enough to handle _all_ possible
  // code sets? I think so but not 100% positive.
  u32  tree[512];

} huff_tables_t, *Phuff_tables_t;


//------------------------------------------------------------------------------
typedef struct coeff_buf_tag
{
    u8 *Pdata;

    int block_num_x, block_num_y;
    int block_len_x, block_len_y;

    int block_size;
    int block_width_size;

} coeff_buf_t, *Pcoeff_buf_t;
//------------------------------------------------------------------------------

typedef struct
{
    u8  *pBitStreamBuf;
    u8  *pSWDecodeBuf;
    u8  *pHWIDCTBuf;
    u8  *pJPDOutputBuf;
    u8  *pDecOutSurf;
} ProgBufAlloc_t;


typedef struct
{
//new increase 08.07.09
    u8   is_ThumbNailDecode;
    u8   DisplayFmt;
    u16  Disp_Width,Disp_Height;
//new increase 08.07.09

    u32  DecodeMode;
    u8   is_progressive;

    u8   ReadBufferFlag;
    u8   *FirstSrcAddr;
    u8   *SecondSrcAddr;
    u32  First_length_of_file;
    u32  Second_length_of_file;
    u8   *StackBuf;

    u8   sJPDThreadFlag;

    s32  BufSizeLeft;

    u8*  AfterStAddr;
    s32  srcfile_flag;
    u32  file_size;
    u32  FileTotalSize;
    u32  SrcReadLimit;
    u8   *JpegHeapAddr;
    u32  image_x_size;
    u32  image_y_size;
    u8   *huff_num[JPGD_MAXHUFFTABLES];  /* pointer to number of Huffman codes per bit size */
    u8   *huff_val[JPGD_MAXHUFFTABLES];  /* pointer to Huffman codes per bit size */

    u8   *huff_num_alloc[8];
    u8   *huff_val_alloc[8];
    Phuff_tables_t *h_alloc[8]; //1792(sizeof(huff_tables_t));
    Phuff_tables_t volatile huff[JPGD_MAXHUFFTABLES]; //only used in Jpgdecoder.c
    QUANT_TYPE *quant_alloc[4];//64 * sizeof(QUANT_TYPE)

    Pcoeff_buf_t ac_coeff_data[3];//[Jason]u8   *ac_coeff_data[3];//ac_coeff_data[3][16384]; //1024*16
    Pcoeff_buf_t dc_coeff_data[3];//[Jason]u8   *dc_coeff_data[3]; //1024/8*2

    u8   progressive_flag;
    u8   lastFlag;

    u8   comps_in_frame;                 /* # of components in frame */
    u8   comp_h_samp[JPGD_MAXCOMPONENTS];     /* component's horizontal sampling factor */
    u8   comp_v_samp[JPGD_MAXCOMPONENTS];     /* component's vertical sampling factor */
    u8   comp_quant[JPGD_MAXCOMPONENTS];      /* component's quantization table selector */
    u8   comp_ident[JPGD_MAXCOMPONENTS];      /* component's ID */

    s32  dct_bufidx; //RLC buffer index
    u32 *dct_buff; //RLC buffer
    u32 *dct_hwbuff;
    //u8  *idct_buff;

    u8*  huffsize;
    u32* huffcode;

    QUANT_TYPE *quant[JPGD_MAXQUANTTABLES];    /* pointer to quantization tables */

    int   comp_h_blocks[JPGD_MAXCOMPONENTS];
    int   comp_v_blocks[JPGD_MAXCOMPONENTS];

    int   scan_type;                      /* Grey, Yh1v1, Yh1v2, Yh2v1, Yh2v2, CMYK111, CMYK4114 */
    int   comps_in_scan;                  /* # of components in scan */
    int   comp_list[JPGD_MAXCOMPSINSCAN];      /* components in this scan */

    int   comp_ac_tab[JPGD_MAXCOMPONENTS];     /* component's AC Huffman coding table selector */

    int   spectral_start;                 /* spectral selection start */
    int   spectral_end;                   /* spectral selection end   */
    int   successive_low;                 /* successive approximation low */
    int   successive_high;                /* successive approximation high */

    int   max_mcu_x_size;                 /* MCU's max. X size in pixels */
    int   max_mcu_y_size;                 /* MCU's max. Y size in pixels */

    int   blocks_per_mcu;
    int   max_blocks_per_row;
    int   mcus_per_row, mcus_per_col;

    int   max_mcus_per_row;
    int   max_blocks_per_mcu;
    int   max_mcus_per_col;

    u8    gYH, gYV;
    unsigned int scan_mcus_per_col;
    unsigned int scan_image_y_size;

    int   total_lines_left;               /* total # lines left in image */
    int   mcu_lines_left;                 /* total # lines left in this MCU */

    u16  toggle;

    int   restart_interval;
    int   restarts_left;
    int   next_restart_num;
    int   last_dc_val_scan[3];

    u32 *component[JPGD_MAXBLOCKSPERMCU];   /* points into the lastdcvals table */
    s32  last_dc_val[JPGD_MAXCOMPONENTS];
    Phuff_tables_t dc_huff_seg[JPGD_MAXBLOCKSPERMCU];
    Phuff_tables_t ac_huff_seg[JPGD_MAXBLOCKSPERMCU];

    Pcoeff_buf_t dc_coeffs[JPGD_MAXCOMPONENTS];
    Pcoeff_buf_t ac_coeffs[JPGD_MAXCOMPONENTS];

    int eob_run;

#ifdef MULTI_ROW_SCAN
    u8 fDC_Pre[JPGD_MAXCOMPONENTS];
    int eob_run_scan[MAX_SCAN_NUM];
    unsigned int row_in_scan;
    unsigned int start_pos;
    unsigned int eoi_pos;
    unsigned long next_start_row_pos[MAX_SCAN_NUM];
    unsigned int next_start_row_bits_left[MAX_SCAN_NUM];
    unsigned int next_start_row_bit_buf[MAX_SCAN_NUM];
    unsigned int scan_num;
#endif

    int mcu_org[JPGD_MAXBLOCKSPERMCU];
    int comp_dc_tab[JPGD_MAXCOMPONENTS];     /* component's DC Huffman coding table selector */

#ifdef OUTPUT_YUV
    int pfInFile;
    int DCTFile;
#endif

    u8   ROI_Enable;
    u16  ROI_Width, ROI_Height;
    u16  ROI_XStartPos, ROI_YStartPos;

    u16  ICP_Src_Width,ICP_Src_Height;

    s32  ResolutionStatus;


    u16  ICP_SecondRow;
    u16  ICPSrc_Pitch;
    u16  round_width;
    u16  round_height;
    u16  crop_width;
    u16  crop_height;
    u16  LineNum;

    u16  output_iMCU_row;

    u16  image_width,image_height;

    //clip window
    u16  clip_mcu_x0,clip_mcu_y0;
    u16  clip_mcu_x1,clip_mcu_y1;

    u16  running_row_cnt;

    u8   DHT_Flag,DQT_Flag,SOF_Flag;

//    DECODE_DISPs decode_disps;
//    DECODE_ICPs  decode_icps;
//    ReadFileSt   sReadFile;

    ProgBufAlloc_t BufAlloc;

    ImageOutCfg_t  Porg_OutCfg;
    u32 nhandle;
} prog_str;


u8 *Prog_malloc(prog_str *pProg,u32 size);
HW_IDCT_RESULT hw_idct_decode3(prog_str *pProg,u8 FirstFlag);
image_Errmsg IDCT2Normal_Result(HW_IDCT_RESULT IDCT_RESULT);

typedef image_Errmsg (*Pdecode_block_func)(prog_str*,int, int, int);


image_Errmsg decode_block_dc_first(prog_str *pProg, int component_id, int block_x, int block_y);
image_Errmsg decode_block_dc_refine(prog_str *pProg, int component_id, int block_x, int block_y);
image_Errmsg decode_block_ac_first(prog_str *pProg, int component_id, int block_x, int block_y);
image_Errmsg decode_block_ac_refine(prog_str *pProg, int component_id, int block_x, int block_y);

//------------------------------------------------------------------------------
// Input stream interface.
// Derive from this class to fetch input data from sources other than
// files. An important requirement is that you *must* set eof_flag to true
// when no more data is available to fetch!
// The decoder is rather "greedy": it will keep on calling this method until
// its internal input buffer is full, or until the EOF flag is set.
// It the input stream contains data after the JPEG stream's EOI (end of
// image) marker it will probably be pulled into the internal buffer.
// Call the get_total_bytes_read() method to determine the true
// size of the JPEG stream.
// Disable no return value warning, for rol() method

void word_clear(u8 *p, u8 c1, u8 c2, u16 n);

void prep_in_buffer(prog_str *pProg);

image_Errmsg read_dht_marker(prog_str *pProg);

image_Errmsg read_dqt_marker(prog_str *pProg);

image_Errmsg read_sof_marker(prog_str *pProg);

image_Errmsg skip_variable_marker(void);

image_Errmsg read_dri_marker(prog_str *pProg);
image_Errmsg read_sos_marker(prog_str *pProg);

int next_marker(void);

int process_markers(prog_str *pProg);

image_Errmsg locate_soi_marker(void);

image_Errmsg locate_sof_marker(prog_str *pProg);

int locate_sos_marker(prog_str *pProg);

void prop_init(prog_str *pProg);

void fix_in_buffer(void);

BLOCK_TYPE *coeff_buf_getp( Pcoeff_buf_t cb, int block_x, int block_y);

image_Errmsg load_next_row(prog_str *pProg);

image_Errmsg decode_next_row(prog_str *pProg);

void make_huff_table(prog_str *pProg, int index, Phuff_tables_t hs);

image_Errmsg check_quant_tables(prog_str *pProg);

image_Errmsg check_huff_tables(prog_str *pProg);

void calc_mcu_block_order(prog_str *pProg);

int init_scan(prog_str *pProg);

image_Errmsg initial_frame(prog_str *pProg);

image_Errmsg process_restart(prog_str *pProg);

image_Errmsg decode_scan(prog_str *pProg,Pdecode_block_func decode_block_func);

image_Errmsg init_progressive(prog_str *pProg);

image_Errmsg init_sequential(prog_str *pProg);

image_Errmsg decode_start(prog_str *pProg);

image_Errmsg decode_initial(prog_str *pProg);

int jpdecode(prog_str *pProg,void **Pscan_line_ofs, u32 *Pscan_line_len);

//------------------
u32  rol(u32 i, u8 j);
u32  jpdprog_get_char(void);
u32  get_char_padd(bool *Ppadding_flag);
void stuff_char(u8 q);
u8   get_octet(void);
u32  get_bits_1(int num_bits);
u32  get_bits_2(int numbits);
int  huff_decode(Phuff_tables_t Ph);
//------------------

//in jdhwidct
void set_Coeff(prog_str *pProg,int blockTyp, int symbolTyp, char run, int p);
int  set_DctCoeff(prog_str *pProg,int blkTyp, BLOCK_TYPE* p); //зяжи macro
u16  set_HwDqtCoeff(prog_str *pProg);
void hw_idct_init(prog_str *pProg);
void get_HwIdctCoeff(prog_str *pProg,int component_id, BLOCK_TYPE* coef_block);
image_Errmsg hw_idct_decode(prog_str *pProg);
//void hw_idct_fire(void);
void _MDrv_PRGDec_ICP_HW_Init(prog_str *pProg);

//------------------------------------------------------------------------------
// idct.cpp
//void idct(BLOCK_TYPE *data, u8 *Pdst_ptr);
//------------------------------------------------------------------------------

#endif//JPEGDECODER_H
#endif //IMGCODEC_JPD_PROGRESSIVE
#endif

