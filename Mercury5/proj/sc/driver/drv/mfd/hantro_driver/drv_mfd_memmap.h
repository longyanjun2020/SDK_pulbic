//# Base address map. A constant offset can be added to values by setting
//# variable EXT_MEMORY_DECODER_BASE in test_rtl_variables.sh
//#

#ifdef _FPGA_
//                       width  height  MBs
//h.264 level4.1, 2Kx1K	 2048	1024	8192
#define IBufSize       (1350*384)
#define FrameSize      (3145728)
#define GBufSize       (20*1024*1024)
#define SwGBufSize     (5*1024*1024)
#elif defined(_SOC_)
//BIG2, CIF
#define IBufSize       (396*384)
#define FrameSize      (152064)
#define GBufSize       (1024)//(1024*1024)
#define SwGBufSize     (64*1024)
#elif defined(_SIM_)
#define IBufSize       (1350*384)
#define FrameSize      (3145728)
#define GBufSize       (20*1024*1024)
#define SwGBufSize     (5*1024*1024)
#endif

//MIU, memory layout
#define DRAM_BIN_SIZE   0//(1024*1024)
#define DRAM_IBUF_SIZE  (IBufSize<<1)

#ifdef _UDMA_
#define DRAM_BASE       1024
#elif defined(_HIF_)
//BIG2
#define DRAM_BASE       0xB0000000
#elif defined(_SOC_)
//BIG2
#define DRAM_BASE       0xB0000000
#elif defined(_SIM_)
#define DRAM_BASE       1024
#else
#error DRAM_BASE error!!!
#endif

#define DRAM_IBUF_BASE  DRAM_BASE+DRAM_BIN_SIZE
#define DRAM_GBUF_BASE  DRAM_IBUF_BASE+DRAM_IBUF_SIZE

//RIU
#define RIU_BASE        0xA0000000

#ifdef _UDMA_
#define REGMAP_BASE     0x00001200
#elif defined(_HIF_)
//BIG2
#define REGMAP_BASE     0x0000D400
#elif defined(_SOC_)
#ifdef CYG_HWR_M3_BIG2
#define REGMAP_BASE     0x0000D400
// G1 REGMAP_BASE move to hal_mfd.h
#endif
#elif defined(_SIM_)
#define REGMAP_BASE     0x00001200
#else
#error REGMAP_BASE error!!!
#endif

//extern u8 input_buf[IBufSize*2];
extern u8 global_buf[GBufSize];
extern u8* m4vd_global_buf_ptr;
extern u32 m4vd_global_buf_phy;
extern u32 m4vd_global_buf_size;

#ifdef _FPGA_
extern u8 outframe[FrameSize]; //2048x1024x1.5
#endif
extern u32 outframe_size;
extern u32 FILE_EOF;
extern u32 picDecodeNumber; /* decoded picture ID */
