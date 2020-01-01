//global
//#define _FPGA_
//#define _SIM_

//local
//#define _SIM_OUTPUT_
//#define _TRACEOUT_COMP_
//#define _HANTRO_RIU_BATCH_

//#define _RIU_DELAY_
//#define _HANTRO_SYS_PROFILE_
//#define _DROP_FRAME_
//#define FRAME_DROP_RATIO 10
//#define _DROP_BYTES_
//#define BYTES_DROP_RATIO 10
#ifdef _SOC_
#define _SOC_REG_IRQ_
#endif

#define H264_RLC    0
extern u32 M4VD_dec_done;
extern u32 M4VD_dec_status;

#define _FRAME_OUTPUT_
//#define INPUT_FROM_MEMORY
//#define INPUT_FROM_FILE

#ifdef INPUT_FROM_FILE
#if defined(_MSC_VER)
#include "drv_mfd_stdio.h"
#define MY_FILE FILE*
#define MY_FOPEN(file_ptr, file_name, file_attr) file_ptr = fopen(file_name, file_attr)
#define MY_FCLOSE(file_ptr) fclose(file_ptr)
#define FOPEN_FAIL(x) ((x)==0)
#else //RISC
#define MY_FILE int
#define MY_FOPEN(file_ptr, file_name, file_attr) file_ptr = fs_open(file, O_RDWR|O_CREAT)
#define MY_FCLOSE(file_ptr) fs_close(file_ptr)
#define FOPEN_FAIL(x) ((x)<0)
#endif
#elif defined(INPUT_FROM_MEMORY)
#define MY_FILE u8*
#define MY_FOPEN(file_ptr, file_name, file_attr)
#define MY_FCLOSE(file_ptr)
#define FOPEN_FAIL(x) ((x)==0)
#else
#define MY_FILE error1
#define MY_FOPEN(file_ptr, file_name, file_attr) error2
#define MY_FCLOSE(file_ptr) error3
#define FOPEN_FAIL(x) ((x)==0) error4
//#error "you have to define INPUT_FROM_FILE or INPUT_FROM_MEMORY"
#endif //INPUT_FROM_MEMORY

#ifdef _FPGA_
//#define SDL_OUTPUT
#define FILE_OUTPUT
#define _FRAME_OUTPUT_
//VC1
#define _RCV_
//#define VC1_DUP_1FRAME
//#define _HANTRO_DEBUG_
//#define _HANTRO_FRAME_PROFILE_
//#define _HANTRO_PROFILE_
#define N_AVGS 7
//#define _CRC_CHECK_
#elif defined(_SOC_) || defined(_SIM_)

#else
#error "you must define one of _FPGA_ or _SIM_"
#endif

//profile
//MB_cycle, MB_read/MB_write
#ifdef _HANTRO_PROFILE_
#define FRAME_DATA_WRITE_HIGH   0x12E9
#define FRAME_DATA_WRITE_LOW    0x12E8
#define FRAME_DATA_READ_HIGH    0x12EB
#define FRAME_DATA_READ_LOW     0x12EA

//0x12EC
//max MB nums: D1(720x576) 1620
#define MB_PROFILE_data 0x12EC

//0x12E1
//MB_read/MB_write:0x0, MB_cycle:0x2
#define MB_PROFILE_type 0x12E1

//0x12E0
//SWCNT_REGNUM 112
#define PIC_END         0x08
#define MB_RESET_ADDR   0x10
#endif

#ifdef _CRC_CHECK_
//0x12FD  //start[15:0]
//0x12FE  //end[7:0], start[23:16]
//0x12FF  //end[23:8]
#define _CRC_START_ADDR_ 0x12FD //24bit
#define _CRC_ADDR_ 0x12FE //24bit
#define _CRC_END_ADDR_ 0x12FF //24bit

#define _CRC_READ_S0_ 0x12F2
#define _CRC_READ_S1_ 0x12F3
#endif

#ifdef CYG_HWR_M3_BIG2
#include "drv_mfd_utility.h" //for BIG2
#include <cyg/infra/diag.h> //BIG2
#define addr_log2phy(log_addr) MApi_UTL_HwMemAccessOffset((void *)(log_addr))
#define addr_phy2log(phy_addr) (MApi_UTL_PhyMemRestore((CYG_ADDRESS)(phy_addr), INTF_M4VD_W) + CYGARC_KSEG_UNCACHED_BASE )
#elif defined(__RTK_OS__)
#include "hal_drv_util.h" // HalUtilPHY2MIUAddr()
#define addr_log2phy(log_addr) HalUtilPHY2MIUAddr((u32)(log_addr))
#define addr_phy2log(phy_addr) HalUtilMIU2PHYAddr((phy_addr))
#else
#define addr_log2phy(log_addr) log_addr
#define addr_phy2log(phy_addr) phy_addr
#endif

#define HANTRO_FPRINTF fprintf
#ifdef CYG_HWR_M3_BIG2
#define HANTRO_DEBUG_MSG(fmt, args...)          //diag_printf(fmt, ##args)
#define HANTRO_DECODING_MSG(fmt, args...)       //diag_printf(fmt, ##args)
#define HANTRO_OUTPIC_MSG(fmt, args...)         //diag_printf(fmt, ##args)
#define MEMORY_USAGE_TRACE(fmt, args...)        //diag_printf(fmt, ##args)
#define HANTRO_DECODING_VOL_MSG(fmt, args...)   //diag_printf(fmt, ##args)
#define HANTRO_DECODING_VOP_MSG(fmt, args...)   //diag_printf(fmt, ##args)
#elif defined(__RTK_OS__)
#define HANTRO_DEBUG_MSG(fmt, args...)          //UartSendTrace
#define HANTRO_DECODING_MSG(fmt, args...)       //UartSendTrace
#define HANTRO_OUTPIC_MSG(fmt, args...)         //UartSendTrace
#define MEMORY_USAGE_TRACE(fmt, args...)        //UartSendTrace
#define HANTRO_DECODING_VOL_MSG(fmt, args...)   //UartSendTrace
#define HANTRO_DECODING_VOP_MSG(fmt, args...)   //UartSendTrace
#else
#error "need to define UartSendTrace"
#endif

#if defined(_MSC_VER)
#define DWL_DEBUG //printf
//H.264 debug msg
#define DEBUG_PRINT(args) printf args
#define ERROR_PRINT(args) printf args
#define DEC_API_TRC(str)  printf(str)
#define TRACE_PP_CTRL     printf
//mpeg4 debug msg
#define MP4DEC_API_DEBUG(args) printf args
#define MP4DEC_DEBUG(args)     printf args
#define MP4_API_TRC(str)       printf(str)
//mpeg2 debug msg
#define MPEG2DEC_API_DEBUG(args) printf args
#define MPEG2DEC_DEBUG(args)     printf args
#define MPEG2_API_TRC(str)       printf(str)
#elif defined(CYG_HWR_M3_BIG2)
#define DWL_DEBUG(arg...) //diag_printf
//H.264 debug msg
#define DEBUG_PRINT(args) //diag_printf args
#define ERROR_PRINT(args) //diag_printf args
#define DEC_API_TRC(str)  //diag_printf(str)
#define TRACE_PP_CTRL(arg...)     //diag_printf
//mpeg4 debug msg
#define MP4DEC_API_DEBUG(args) //diag_printf args
#define MP4DEC_DEBUG(args)     //diag_printf args
#define MP4_API_TRC(str)       //diag_printf(str)
//mpeg2 debug msg
#define MPEG2DEC_API_DEBUG(args) //diag_printf args
#define MPEG2DEC_DEBUG(args)     //diag_printf args
#define MPEG2_API_TRC(str)       //diag_printf(str)
#elif defined(__RTK_OS__)
#define DWL_DEBUG(fmt, args...)     //UartSendTrace
//H.264 debug msg
#define DEBUG_PRINT(args)           //UartSendTrace args
#define ERROR_PRINT(args)           //UartSendTrace args
#define DEC_API_TRC(fmt, args...)   //UartSendTrace
#define TRACE_PP_CTRL(fmt, args...) //UartSendTrace
//mpeg4 debug msg
//#define DUMP_TEST(fmt, args...)     ms_dprintf(0, fmt, ##args)
#define MP4DEC_API_DEBUG(arg)       //UartSendTrace arg
#define MP4DEC_DEBUG(arg)           //UartSendTrace arg
#define MP4_API_TRC(fmt, args...)   //UartSendTrace
//mpeg2 debug msg
#define MPEG2DEC_API_DEBUG(args)    //UartSendTrace args
#define MPEG2DEC_DEBUG(args)        //UartSendTrace args
#define MPEG2_API_TRC(fmt, args...) //UartSendTrace
#endif

#if 0
#define ASSERT(x) \
if ((x)==0) { \
    while (1) { \
        HANTRO_DEBUG_MSG("assert func [%s], line [%d]\n", __FUNCTION__, __LINE__); \
    } \
}
#else
#define ASSERT(x)
#endif

#define SWCNT_REGNUM 0x12E0
#define reg_mfd_sum_wreq1 0x12E8
#define reg_mfd_sum_wreq2 0x12E9

#define SWCNT_RESET  0x01
#define SWCNT_START  0x02
#define SWCNT_STOP   0x04

//SWCNT_MSB[31:0] 0x12E7, 0x12E6
#define SWCNT_MSB    115

//SWCNT_LSB[31:0] 0x12E5, 0x12E4
#define SWCNT_LSB    114

#ifdef _UDMA_
#if 0
//G1_FPGA
//for setup SWREG02 endian
//#define DEC_X170_OUTPUT_PICTURE_ENDIAN DEC_X170_OUTPUT_PICTURE_BIG_ENDIAN
#define DEC_X170_INPUT_STREAM_ENDIAN    DEC_X170_INPUT_DATA_LITTLE_ENDIAN
///* HWIF_DEC_IN_ENDIAN     */ {/*swreg*/2 ,  1,  9},
#define DEC_X170_INPUT_DATA_ENDIAN  DEC_X170_INPUT_DATA_LITTLE_ENDIAN
///* HWIF_PRIORITY_MODE     */ {/*swreg*/2 ,  3,  5},
#define DEC_X170_ASIC_SERVICE_PRIORITY DEC_X170_ASIC_SERVICE_PRIORITY_RD_1
///* HWIF_DEC_OUTSWAP32_E   */ {/*swreg*/2 ,  1, 19},
#define DEC_X170_OUTPUT_SWAP_32_ENABLE 1
///* HWIF_DEC_INSWAP32_E    */ {/*swreg*/2 ,  1, 20},
#define DEC_X170_INPUT_DATA_SWAP_32_ENABLE 1
///* HWIF_DEC_STRSWAP32_E   */ {/*swreg*/2 ,  1, 22},
#define DEC_X170_INPUT_STREAM_SWAP_32_ENABLE 1
#define DEC_X170_INTERNAL_CLOCK_GATING 1
#else
//BIG2_FPGA
//for setup SWREG02 endian
//#define DEC_X170_OUTPUT_PICTURE_ENDIAN DEC_X170_OUTPUT_PICTURE_BIG_ENDIAN
///* HWIF_DEC_IN_ENDIAN     */ {/*swreg*/2 ,  1,  9},
#define DEC_X170_INPUT_DATA_ENDIAN  DEC_X170_INPUT_DATA_BIG_ENDIAN
///* HWIF_PRIORITY_MODE     */ {/*swreg*/2 ,  3,  5},
#define DEC_X170_ASIC_SERVICE_PRIORITY DEC_X170_ASIC_SERVICE_PRIORITY_RD_1
///* HWIF_DEC_OUTSWAP32_E   */ {/*swreg*/2 ,  1, 19},
#define DEC_X170_OUTPUT_SWAP_32_ENABLE 1
///* HWIF_DEC_INSWAP32_E    */ {/*swreg*/2 ,  1, 20},
#define DEC_X170_INPUT_DATA_SWAP_32_ENABLE 1
///* HWIF_DEC_STRSWAP32_E   */ {/*swreg*/2 ,  1, 22},
#define DEC_X170_INPUT_STREAM_SWAP_32_ENABLE 1
#define DEC_X170_INTERNAL_CLOCK_GATING 1
#endif
#elif defined(_HIF_)
//BIG2
//for setup SWREG02 endian
//#define DEC_X170_OUTPUT_PICTURE_ENDIAN DEC_X170_OUTPUT_PICTURE_BIG_ENDIAN

#define DEC_X170_INPUT_STREAM_ENDIAN    DEC_X170_INPUT_DATA_LITTLE_ENDIAN

///* HWIF_DEC_IN_ENDIAN     */ {/*swreg*/2 ,  1,  9},
//#define DEC_X170_INPUT_DATA_ENDIAN  DEC_X170_INPUT_DATA_BIG_ENDIAN
#define DEC_X170_INPUT_DATA_ENDIAN  DEC_X170_INPUT_DATA_LITTLE_ENDIAN

///* HWIF_PRIORITY_MODE     */ {/*swreg*/2 ,  3,  5},
#define DEC_X170_ASIC_SERVICE_PRIORITY DEC_X170_ASIC_SERVICE_PRIORITY_RD_1

///* HWIF_DEC_OUTSWAP32_E   */ {/*swreg*/2 ,  1, 19},
#define DEC_X170_OUTPUT_SWAP_32_ENABLE 0

///* HWIF_DEC_INSWAP32_E    */ {/*swreg*/2 ,  1, 20},
#define DEC_X170_INPUT_DATA_SWAP_32_ENABLE 0

///* HWIF_DEC_STRSWAP32_E   */ {/*swreg*/2 ,  1, 22},
#define DEC_X170_INPUT_STREAM_SWAP_32_ENABLE 0

#define DEC_X170_INTERNAL_CLOCK_GATING 1

#elif defined(_SOC_)
//BIG2
//for setup SWREG02 endian
//#define DEC_X170_OUTPUT_PICTURE_ENDIAN DEC_X170_OUTPUT_PICTURE_BIG_ENDIAN

#define DEC_X170_INPUT_STREAM_ENDIAN    DEC_X170_INPUT_DATA_LITTLE_ENDIAN

///* HWIF_DEC_IN_ENDIAN     */ {/*swreg*/2 ,  1,  9},
#define DEC_X170_INPUT_DATA_ENDIAN  DEC_X170_INPUT_DATA_BIG_ENDIAN
//#define DEC_X170_INPUT_DATA_ENDIAN  DEC_X170_INPUT_DATA_LITTLE_ENDIAN

///* HWIF_PRIORITY_MODE     */ {/*swreg*/2 ,  3,  5},
#define DEC_X170_ASIC_SERVICE_PRIORITY DEC_X170_ASIC_SERVICE_PRIORITY_RD_1

///* HWIF_DEC_OUTSWAP32_E   */ {/*swreg*/2 ,  1, 19},
#define DEC_X170_OUTPUT_SWAP_32_ENABLE 0

///* HWIF_DEC_INSWAP32_E    */ {/*swreg*/2 ,  1, 20},
#define DEC_X170_INPUT_DATA_SWAP_32_ENABLE 0

///* HWIF_DEC_STRSWAP32_E   */ {/*swreg*/2 ,  1, 22},
#define DEC_X170_INPUT_STREAM_SWAP_32_ENABLE 0

#define DEC_X170_INTERNAL_CLOCK_GATING 1
#elif defined(_SIM_)

#else
#error DEC_X170_INTERNAL_CLOCK_GATING error!!!
#endif

#if defined(_SOC_) || defined(_FPGA_)
#define MAP_FAILED          0 //pRegBase as u32
#else
#define MAP_FAILED          0  //pRegBase as pointer
#endif

#include "drv_mfd_memmap.h"
