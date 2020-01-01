#ifndef __UNFD_CONFIG_H__
#define __UNFD_CONFIG_H__

//=====================================================
// select a HW platform:
//   - 1: enable, 0: disable.
//   - only one platform can be 1, others have to be 0.
//=====================================================
#define NAND_DRV_C5_ROM       0
#define NAND_DRV_C5_ECOS      0
//#define NAND_DRV_C5_NPRG      0 // programmer is attached with all platforms
#define NAND_DRV_OS_NOS       0

#if defined(__MSW8522__) || defined(__MSW8556__)
#define NAND_DRV_B3_ROM       0
#define NAND_DRV_B5_ROM       1
#else
#define NAND_DRV_B3_ROM       1
#define NAND_DRV_B5_ROM       0
#endif
#define NAND_DRV_B3_RTK       0
#define NAND_DRV_G1_ROM       0
#define NAND_DRV_G1_RTK       0
#define NAND_DRV_LINUX        0




//=====================================================
// do NOT edit the following content.
//=====================================================
#if defined(NAND_DRV_C5_ROM) && NAND_DRV_C5_ROM
  #include "config_nand/drvNAND_c5_rom.h"
#elif defined(NAND_DRV_C5_ECOS) && NAND_DRV_C5_ECOS
  #include "config_nand/drvNAND_c5_ecos.h"
#elif defined(NAND_DRV_C5_NPRG) && NAND_DRV_C5_NPRG /*NPRG same with eCos*/
  #include "config_nand/drvNAND_c5_ecos.h"
#elif defined(NAND_DRV_B3_ROM) && NAND_DRV_B3_ROM
  #include "drvNAND_b3_rom.h"
#elif defined(NAND_DRV_B3_RTK) && NAND_DRV_B3_RTK
  #include "drvNAND_b3_rtk.h"
#elif defined(NAND_DRV_B5_ROM) && NAND_DRV_B5_ROM
  #include "drvNAND_b5_rom.h"   
#elif defined(NAND_DRV_G1_ROM) && NAND_DRV_G1_ROM
  #include "drvNAND_g1_ROM.h"
#elif defined(NAND_DRV_G1_RTK) && NAND_DRV_G1_RTK
  #include "drvNAND_g1_rtk.h"
#elif defined(NAND_DRV_LINUX) && NAND_DRV_LINUX
  #include "config_nand/drvNAND_linux.h"
#else
  #error "Error! no platform selected."
#endif


//do NOT edit the following content, for HAL use.

//=====================================================
// misc. do NOT edit the following content.
//=====================================================
#define NAND_DMA_RACING_PATCH        1
#define NAND_DMA_PATCH_WAIT_TIME     10000 // us -> 10ms
#define NAND_DMA_RACING_PATTERN0     (((U32)'M'<<24)|((U32)0<<16)|((U32)'S'<<8)|(U32)1)
#define NAND_DMA_RACING_PATTERN1     (((U32)'T'<<24)|((U32)6<<16)|((U32)'A'<<8)|(U32)8)



//===========================================================
// Time Dalay, do NOT edit the following content, for NC_WaitComplete use.
//===========================================================
#define DELAY_100us_in_us  100
#define DELAY_500us_in_us  500
#define DELAY_1ms_in_us    1000
#define DELAY_10ms_in_us   10000
#define DELAY_100ms_in_us  100000
#define DELAY_500ms_in_us  500000
#define DELAY_1s_in_us     1000000

#define WAIT_ERASE_TIME    (DELAY_1s_in_us<<2)
#define WAIT_WRITE_TIME    (DELAY_1s_in_us<<2)
#define WAIT_READ_TIME     (DELAY_1ms_in_us<<10)	//DELAY_500us_in_us
#define WAIT_PROBE_TIME    (DELAY_100us_in_us<<2)
#define WAIT_RESET_TIME    (WAIT_ERASE_TIME)

extern void nand_reset_WatchDog(void);
extern U32 nand_clock_setting(U32 u32ClkParam);
extern U32 nand_config_clock(U16 u16_SeqAccessTime);
extern U32 nand_translate_DMA_address_Ex(U32 u32_DMAAddr, U32 u32_ByteCnt);
extern void nand_Invalidate_data_cache_buffer(U32 u32_addr, S32 s32_size);
extern U32 nand_WaitCompleteIntr(U16 u16_WaitEvent, U32 u32_MicroSec);
extern void nand_enable_intr_mode(void);

#define NAND_PARTITAION_BYTE_CNT    0x200
#endif /* __UNFD_CONFIG_H__ */
