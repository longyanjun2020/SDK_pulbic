#ifndef MEMMAP_H
#define MEMMAP_H

typedef unsigned char u8;
typedef int i32;
typedef unsigned int u32;
#define NULL 0


//# Base address map. A constant offset can be added to values by setting
//# variable EXT_MEMORY_DECODER_BASE in test_rtl_variables.sh
//#

//                       width  height  MBs
//h.264 level4.1, 2Kx1K	 2048	1024	8192
#define IBufSize       (1350*384)
#define FrameSize      (3145728)
#define GBufSize       (20*1024*1024)
#define SwGBufSize     (5*1024*1024)

//MIU, memory layout
#define DRAM_BIN_SIZE   (1024*1024)
#define DRAM_IBUF_SIZE  (IBufSize<<1)

#define DRAM_BASE       0
#define DRAM_IBUF_BASE  DRAM_BASE+DRAM_BIN_SIZE
#define DRAM_GBUF_BASE  DRAM_IBUF_BASE+DRAM_IBUF_SIZE

//RIU
#define RIU_BASE        0xA0000000

//for current FPGA env
#define REGMAP_BASE     0x00001200

extern u8 input_buf[IBufSize*2];
extern u8 global_buf[GBufSize];
extern u8* global_buf_ptr;
extern u32 global_buf_phy;
extern u32 global_buf_size;

#ifdef _FPGA_
extern u8 outframe[FrameSize]; //2048x1024x1.5
#endif
extern u32 outframe_size;
extern u32 FILE_EOF;
extern u32 picDecodeNumber; /* decoded picture ID */

#endif // MEMMAP_H
