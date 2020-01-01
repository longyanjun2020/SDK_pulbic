#include "imgcodec_platform.h"
#ifdef IMGCODEC_USE_NEW_VERSION
#ifdef IMGCODEC_JPD_PROGRESSIVE

#ifndef __JPEG_GLOBAL_H__
#define __JPEG_GLOBAL_H__

#include "imgcodec_common.h"

#ifndef __SDK_SIMULATION__
#define USE_HW_IDCT //Jason marker to use SW IDCT
#endif

typedef int   cyg_flag_value_t;
typedef int   cyg_flag_t;

#define JeffDefineBufSize   300*1024

extern u16 JPD_Mul_Fac;

//-------------------------------------------------------------------------------------------------
// progressive JPEG decode
//-------------------------------------------------------------------------------------------------

//extern Phuff_tables_t volatile huff[JPGD_MAXHUFFTABLES];
//extern int block_y_mcu[JPGD_MAXCOMPONENTS];
extern u8 volatile *Pin_buf_ofs;
extern u8* volatile in_buf;
extern int bits_left;
extern u32 bit_buf;
extern unsigned int in_buf_left;
extern unsigned int total_bytes_read;

//extern cyg_handle_t    sJPD_handle;                /* returned thread handle    */
//extern cyg_thread      sJPD_thread;                /* put thread here           */
//extern cyg_sem_t       sJPD_read_sema;
extern u8  sJPDReadBufFlag;
extern u8  sJPDReadFailFlag;

extern u32 sJPD_File_Left;
//extern JPD_Header *pThumbHeader;



//#endif //#endif JPEG_PLAYER

//Jason added for PRO
extern u8* JPDFilePoolBuf;
extern u8* JpegDecPRGBuf;
extern u8* JpegDecPRGBitstreamBuf;
extern u8* JpegDecPRGICPBuf;

#ifdef IMAGE_ISW_TEST
#include "sys_sys_isw_cli.h"
#include "sys_sys_isw_uart.h"

#define img_trace2 cliPrintf
#endif

#endif //__JPEG_GLOBAL_H__
#endif //IMGCODEC_JPD_PROGRESSIVE
#endif

