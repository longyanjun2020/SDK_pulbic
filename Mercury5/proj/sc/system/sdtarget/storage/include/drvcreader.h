///////////////////////////////////////////////////////////////////////////////////////////////////
//
//  @File: drvcreader.h
//
//        Author: Timothy Hsu / HDTV
//        << card reader driver >>
//  FCIE2 register definition
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef _DRV_CREADER_H
#define _DRV_CREADER_H

//#include "platform.h"
#define C3_FCIE

#ifdef DRV_CREADER
    #define DRV_CREADER_INTERFACE
#else
    #define DRV_CREADER_INTERFACE extern
#endif




//#define XBYTE     ((unsigned char volatile *) 0)
//#define BD_CUSTOMER_ASD_PHILIPS_3D5 123
//#define MS_BOARD_TYPE_SEL   C3_FPGA


//#define VA2PA(addr)         ((U32)addr&0x00FFFFFF) // only bit 0~23

typedef enum ESTORAGETYPE
{
    eSDMMC = 0,
    eMSMSP,
    eSMXD,
    eSD_MS_XD,
    eCF,
    eNAND,
    eNOR
} STORAGETYPE;


///////////////////////////////////////////////////////////////////////////////////////////////////


#define ENABLE_CARDREADER   1
#define BUILD_SYSDEBUG      0
#define CREADER_SECTOR_SIZE_512BYTE            512
//#define FCIE_SHAREPIN_PATCH 1

#define BIT00 0x01
#define BIT01 0x02
#define BIT02 0x04
#define BIT03 0x08
#define BIT04 0x10
#define BIT05 0x20
#define BIT06 0x40
#define BIT07 0x80

#define WBIT00 0x0001
#define WBIT01 0x0002
#define WBIT02 0x0004
#define WBIT03 0x0008
#define WBIT04 0x0010
#define WBIT05 0x0020
#define WBIT06 0x0040
#define WBIT07 0x0080
#define WBIT08 0x0100
#define WBIT09 0x0200
#define WBIT10 0x0400
#define WBIT11 0x0800
#define WBIT12 0x1000
#define WBIT13 0x2000
#define WBIT14 0x4000
#define WBIT15 0x8000


#define FICE_CPU_8051   1
#define FCIE_CPU_AEON   2
#define FCIE_CPU_MIPS   3
#define FCIE_CPU_ARM    4
#define FCIE_CPU_TYPE   FCIE_CPU_ARM

#define MCU_8BIT    	1
#define MCU_32BIT   	2
#define FCIE_PLATFORM   MCU_32BIT

#define PROJECT_C3  1 // ceramal 3
#define PROJECT_M3  2 // montage 3, bigblue 2

#define SDCDZ_H_CARD_IN 1
#define SDCDZ_L_CARD_IN 0

#define FCIE_PROJECT PROJECT_M3

#define FCIE_FPGA_TEST FALSE

#define MIU_WIDTH                       4 // ??

#define SYS_BASE 0x74000000

#define CARD_READER_DMA_ALIGN      MIU_WIDTH   // Cannot be zero, at least 1

//#define I_AM_USING_C3_FPGA
//#define ROM_NAND_DRIVER
//#define ROM_NAND_DRIVER_R_ONLY
#define EN_ESP_ERS_CHK 1
//#define NAND_DUMP_LUT
//#define NAND_DBG_PRINT_ALL_RDD_IN_CROSS_LINK_BLK

#include "stdio.h"
#include "stdcomp.h"
#include "bootrom.h"
#include "syscfg.h"
#include "hal.h"
#include <string.h>
#include "sysmiscdrv.h"

#define	U8		u8
#define	U16		u16
#define	U32		u32


#define ENABLE  1
#define DISABLE 0

#ifndef TRUE
    #define TRUE    1
#endif
#ifndef FALSE
    #define FALSE   0
#endif



// SDIO port has only one card detect, can not enable SD and MS/PRO at the same time



///////////////////////////////////////////////////////////////////////////////////////////////////

extern void MDrvFice4LoopDelay(U32 ms);


///////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef C3_FCIE
///////////////////////////////////////////////////////////////////////////////////////////////////

//#define VA2PA(addr)         ((U32)addr&0x00FFFFFF) // only bit 0~23
#if (FCIE_PLATFORM==MCU_8BIT)
    #define FCIE//_DELAY_MS(MS) MDrv_Timer_Delayms(MS)
    #define FCIE_OffShift   1
    #define VA2PA(addr)         ((U32)BASEADR_SDRAM_MCU_XDATA+(U16)addr)
    //#define REG(addr) (*(volatile U8 xdata*)(addr))
    #include "sysinfo.h"

    #define FCIE_RIU_R16(addr)        ((((U16)XBYTE[(addr)+1])<<8)|((U16)XBYTE[(addr)]))
    #define REG(addr)                 (*(volatile U8 xdata*)(addr))
    #define FCIE_RIU_W16(addr,value)  do {                                     \
                                          XBYTE[(addr)+0] = (value)&0xFF;      \
                                          XBYTE[(addr)+1] = ((value)>>8)&0xFF; \
                                      } while(0);
    DRV_CREADER_INTERFACE void fcie_mem_io_write8(U32 dest, U8 dat);
    DRV_CREADER_INTERFACE void fcie_mem_io_read8(U32 dest, U8* dat);
#else
    //int diag_printf(const char *fmt, ...);
    //#define printf diag_printf
    //#ifdef printf
    //    #undef printf
    //#endif
    //#define printf(fmt, args...)        diag_printf(fmt, ## args)
    //#define FCIE_RIU_W16(addr,value)  *((volatile U16*)(0xA0000000+(addr<<2))) = value
    //#define FCIE_RIU_R16(addr)       (*((volatile U16*)(0xA0000000+(addr<<2))))

    #define FCIE_RIU_W16(addr,value) *((volatile U16*)(addr)) = value
    #define FCIE_RIU_R16(addr)       *((volatile U16*)(addr))

    #define REG(addr) (*(volatile U16*)(addr))

    #ifdef __ASIC_SIM__
        #define FCIE_DELAY_MS(MS) // simulation can not delay
    #else
        //#define FCIE_DELAY_MS(MS) MDrvFice4LoopDelay(MS)
        #define FCIE_DELAY_MS(MS) hal_delay_us(MS*1000)
    #endif

    //#define FCIE_DELAY_US(US) HAL_DELAY_US(US);


    #define FCIE_OffShift   2
    #if   (FCIE_PROJECT==PROJECT_C3)
        #define VA2PA(addr)         ((U32)addr&0x00FFFFFF) // only bit 0~23
    #elif (FCIE_PROJECT==PROJECT_M3)
        #define VA2PA(addr)         ((U32)addr&0x0FFFFFFF) // 64MB = 0x04000000
    #else
        #message "ERROR!!! MEMORY ADDRESS NOT DEFINED!"
    #endif
    #if 0
    #define fcie_mem_io_write8(dest,data)    *((volatile U8 *)(0x80000000+(dest))) = (U8)(data)
    #define fcie_mem_io_read8(dest,data)	 *((U8 *)(data))= *((volatile U8 *)(0x80000000+(dest)))
    #else
    #define fcie_mem_io_write8(dest,data)    *((volatile U8 *)(dest)) = (U8)(data)
    #define fcie_mem_io_read8(dest,data)	 *((U8 *)(data))= *((volatile U8 *)(dest))
    #endif
#endif

// read modify write 16 bits register macro
#define FCIE_RIU_16_ON(addr,value) FCIE_RIU_W16(addr, FCIE_RIU_R16(addr)|(value))
#define FCIE_RIU_16_OF(addr,value) FCIE_RIU_W16(addr, FCIE_RIU_R16(addr)&(~(value)))

#define FCIE_RIU_32_ON(addr,value) FCIE_RIU_W32(addr, FCIE_RIU_R32(addr)|(value))
#define FCIE_RIU_32_OF(addr,value) FCIE_RIU_W32(addr, FCIE_RIU_R32(addr)&(~(value)))

// new code
                                                           // TV TOOL
#define CLKGEN_BASE     (SYS_BASE+(0x0000<<FCIE_OffShift)) // CLKGEN 0x0000 ~ 0x03FF
//#define CHIPTOP_BASE    (SYS_BASE+(0x0F00<<FCIE_OffShift)) // 0x1E00

#define FCIE_BASE       (SYS_BASE+(0x1400<<FCIE_OffShift)) // 0x1400 x 4 = 0x5000
#define PAD_CTRL_BASE   (SYS_BASE+(0x1980<<FCIE_OffShift)) // 0x1980 x 4 = 0x6600

//old code
#define BK_CLKGEN       (SYS_BASE+(0x0000<<FCIE_OffShift)) //  0x0000
#define BK_MISC         (SYS_BASE+(0x1800<<FCIE_OffShift)) //  0x6000

///////////////////////////////////////////////////////////////////////////////////////////////////
// PAD_CTRL
#define SD_PAD_CTRL     (PAD_CTRL_BASE+(0x02<<FCIE_OffShift))
#define R_PAD_SD_EN     WBIT05

///////////////////////////////////////////////////////////////////////////////////////////////////
// pad pull up pull down
#define P_SEL0      0xBF83C114 // 6
#define P_SEL1      0xBF83C124 // 8

// P_SEL0
//#define R_SD_D1_PUPD    (DWBIT20+DWBIT21)
//#define R_SD_D2_PUPD    (DWBIT22+DWBIT23)
//#define R_SD_D3_PUPD    (DWBIT24+DWBIT25)
//#define R_SD_PCTL_PUPD  (DWBIT26+DWBIT27)
//#define R_MS_INS_PUPD   (DWBIT28+DWBIT29)
//#define R_SD_OCDET_PUPD (DWBIT30+DWBIT31)

#define R_P_SEL0_MSK    0xFFF0
#define R_P_SEL0_DEFO   (WBIT04+WBIT06+WBIT08+WBIT10+WBIT13+WBIT14)
//#define R_P_SEL0_DEFO   (WBIT04+WBIT06+WBIT10+WBIT13+WBIT14) // D3 need floating for SD card detect
#define R_P_SEL0_4SD    (WBIT05+WBIT07+WBIT09+WBIT13)
#define R_P_SEL0_4MS    (WBIT04+WBIT06+WBIT08+WBIT13)

// P_SEL1
#define R_SD_WPT_PUPD   (WBIT22+WBIT23)
#define R_SD_CDZ_PUPD   (WBIT24+WBIT25)
#define R_SD_CLK_PUPD   (WBIT26+WBIT27)
#define R_SD_CMD_PUPD   (WBIT28+WBIT29)
#define R_SD_D0_PUPD    (WBIT30+WBIT31)

#define R_P_SEL1_MSK    0xFFC0
#define R_P_SEL1_DEFO   (WBIT06+WBIT09+WBIT10+WBIT12+WBIT14)
#define R_P_SEL1_4SD    (WBIT07+WBIT09+WBIT10+WBIT13+WBIT15)
#define R_P_SEL1_4MS    (WBIT07+WBIT09+WBIT10+WBIT12+WBIT14)

// pad select
#define MX_SEL0     0xBF83C044 // 16
#define MX_SEL1     0xBF83C048 // 17

#define MX_SEL_SET0 0xFFF00000
#define MX_SEL_SET1 0xFFFFFFFF



// Incense
// 0xBF801000+(0x80+0x36)*2 // IVL

#define IOVLV 0xBF80116C
#define R_IOVLV 0x01E7

#define MISC1 0xBF801124
#define R_MISC1 WBIT06

///////////////////////////////////////////////////////////////////////////////////////////////////

#if 0
#define CLK_FCIE        (CLKGEN_BASE+(0x23<<FCIE_OffShift))
#define CLK_MIU4FCIE    (CLKGEN_BASE+(0x37<<FCIE_OffShift))
#else
#define CLK_MIU4FCIE            (BK_MISC+(0x00<<FCIE_OffShift))
#define CLK_FCIE                (BK_CLKGEN+(0x23<<FCIE_OffShift))
#define R_MCLK_FCIE_EN          WBIT08 // high active
#endif

#define CLK_FCIE_DIS            WBIT00
#define CLK_INVERT              WBIT01

#define CLK_SEL_MSK             0x003C
#define CLK_FCIE_187K           0x0000 // 187.5
#define CLK_FCIE_750K           0x0004
#define CLK_FCIE_06M            0x0008
#define CLK_FCIE_10M            0x000C // 10.4
#define CLK_FCIE_13M            0x0010
#define CLK_FCIE_19M            0x0014 // 19.5
#define CLK_FCIE_22M            0x0018 // 22.286
#define CLK_FCIE_26M            0x001C
#define CLK_FCIE_39M            0x0020 // 43.2
#define CLK_FCIE_44M            0x0024 // 44.57
#define CLK_FCIE_52M            0x0028
#define CLK_FCIE_78M            0x002C
#define CLK_FCIE_SSC            0x0030 // use SSC

//FCIE REGISTER
#define MIE_EVENT       (FCIE_BASE+(0x00<<FCIE_OffShift))
#define NC_MIE_EVENT    MIE_EVENT                         // for backward compatible
#define MIE_INT_EN      (FCIE_BASE+(0x01<<FCIE_OffShift))
#define NC_MIE_INT_EN   MIE_INT_EN                        // for backward compatible
#define MMA_PRIORITY    (FCIE_BASE+(0x02<<FCIE_OffShift))
#define NC_MMA_PRI_REG  MMA_PRIORITY                      // for backward compatible
#define MIU_DMA1        (FCIE_BASE+(0x03<<FCIE_OffShift))
#define MIU_DMA0        (FCIE_BASE+(0x04<<FCIE_OffShift))
#define CARD_EVENT      (FCIE_BASE+(0x05<<FCIE_OffShift))
#define CARD_INT_EN     (FCIE_BASE+(0x06<<FCIE_OffShift))
#define NC_CARD_INT_EN  (FCIE_BASE+(0x06<<FCIE_OffShift)) // for backward compatible
#define CARD_DET        (FCIE_BASE+(0x07<<FCIE_OffShift))
#define CARD_PWR        (FCIE_BASE+(0x08<<FCIE_OffShift))
#define INTR_TEST       (FCIE_BASE+(0x09<<FCIE_OffShift))
#define MIE_PATH_CTL    (FCIE_BASE+(0x0A<<FCIE_OffShift))
#define NC_MIE_PATH_CTL (FCIE_BASE+(0x0A<<FCIE_OffShift)) // for backward compatible
#define JOB_BL_CNT      (FCIE_BASE+(0x0B<<FCIE_OffShift))
#define NC_JOB_BL_CNT   (FCIE_BASE+(0x0B<<FCIE_OffShift)) // for backward compatible
#define TR_BK_CNT       (FCIE_BASE+(0x0C<<FCIE_OffShift))
#define NC_TR_BK_CNT    TR_BK_CNT                         // for backward compatible
#define RSP_SIZE        (FCIE_BASE+(0x0D<<FCIE_OffShift)) // SD
#define CMD_SIZE        (FCIE_BASE+(0x0E<<FCIE_OffShift))
#define CARD_WD_CNT     (FCIE_BASE+(0x0F<<FCIE_OffShift))
#define SD_MODE         (FCIE_BASE+(0x10<<FCIE_OffShift))
#define SD_CTL          (FCIE_BASE+(0x11<<FCIE_OffShift))
#define SD_STS          (FCIE_BASE+(0x12<<FCIE_OffShift))
#define MS_MODE         (FCIE_BASE+(0x13<<FCIE_OffShift)) // MS
#define MS_CTL          (FCIE_BASE+(0x14<<FCIE_OffShift))
#define MS_STS          (FCIE_BASE+(0x15<<FCIE_OffShift))
#define CF_INF_CTL1     (FCIE_BASE+(0x16<<FCIE_OffShift)) // CF
#define CF_INF_CTL2     (FCIE_BASE+(0x17<<FCIE_OffShift))
#define CF_BUS          (FCIE_BASE+(0x18<<FCIE_OffShift))
#define CF_STB_SET      (FCIE_BASE+(0x19<<FCIE_OffShift))
#define CF_CTL          (FCIE_BASE+(0x1A<<FCIE_OffShift))
#define SDIO_CTL        (FCIE_BASE+(0x1B<<FCIE_OffShift)) // SDIO
#define SDIO_ADDR0      (FCIE_BASE+(0x1C<<FCIE_OffShift))
#define SDIO_ADDR1      (FCIE_BASE+(0x1D<<FCIE_OffShift))
#define SDIO_STS        (FCIE_BASE+(0x1E<<FCIE_OffShift))
#define RIU2NAND_STAT   (FCIE_BASE+(0x1F<<FCIE_OffShift)) // C3
#define R_1F            (FCIE_BASE+(0x1F<<FCIE_OffShift)) // BIG2
#define RIU2NAND_CTL    (FCIE_BASE+(0x20<<FCIE_OffShift)) // C3
#define RIU2NAND_R      (FCIE_BASE+(0x21<<FCIE_OffShift)) // C3
#define RIU2NAND_W      (FCIE_BASE+(0x22<<FCIE_OffShift)) // C3
#define CF_TIMING       (FCIE_BASE+(0x23<<FCIE_OffShift)) // C3
#define SM_TIMING       (FCIE_BASE+(0x24<<FCIE_OffShift)) // C3
#define MISC_TIMING     (FCIE_BASE+(0x25<<FCIE_OffShift)) // C3
#define NC_CIF_FIFO_CTL (FCIE_BASE+(0x25<<FCIE_OffShift)) // for backward compatible
#define SM_INF_CTL      (FCIE_BASE+(0x26<<FCIE_OffShift))
#define SM_ADR_REQ      (FCIE_BASE+(0x27<<FCIE_OffShift))
#define SM_CMD_REQ      (FCIE_BASE+(0x28<<FCIE_OffShift))
#define SM_STB_SET      (FCIE_BASE+(0x29<<FCIE_OffShift))
#define SM_MODE         (FCIE_BASE+(0x2A<<FCIE_OffShift))
#define SM_CTL          (FCIE_BASE+(0x2B<<FCIE_OffShift))
#define SM_STS          (FCIE_BASE+(0x2C<<FCIE_OffShift))
#define DMA_OFFSET      (FCIE_BASE+(0x2E<<FCIE_OffShift))
#define FCIEU02MISC     (FCIE_BASE+(0x2F<<FCIE_OffShift))
#define TEST_MODE       (FCIE_BASE+(0x30<<FCIE_OffShift))
#define NC_MISC       	(FCIE_BASE+(0x31<<FCIE_OffShift))
#define R_32            (FCIE_BASE+(0x32<<FCIE_OffShift)) // BIG2
#define R_33            (FCIE_BASE+(0x33<<FCIE_OffShift)) // BIG2

#define PWRSAVE_MASK    (FCIE_BASE+(0x34<<FCIE_OffShift)) // BIG3
#define RWRSAVE_CTL     (FCIE_BASE+(0x35<<FCIE_OffShift)) // BIG3

#define NAND_TIMING     (FCIE_BASE+(0x37<<FCIE_OffShift)) // C3
#define MIU_WP_MIN_AH_S (FCIE_BASE+(0x38<<FCIE_OffShift)) // C3
#define MIU_WP_MIN_AL   (FCIE_BASE+(0x39<<FCIE_OffShift)) // C3
#define MIU_WP_MAX_AH   (FCIE_BASE+(0x3A<<FCIE_OffShift)) // C3
#define MIU_WP_MAX_AL   (FCIE_BASE+(0x3B<<FCIE_OffShift)) // C3
#define MIU_WP_ERR_AH   (FCIE_BASE+(0x3C<<FCIE_OffShift)) // C3
#define MIU_WP_ERR_AL   (FCIE_BASE+(0x3D<<FCIE_OffShift)) // C3
#define FCIE_INFO       (FCIE_BASE+(0x3F<<FCIE_OffShift)) // C3
#define NC_CFG0         (FCIE_BASE+(0x40<<FCIE_OffShift)) // NAND
#define NC_CFG1         (FCIE_BASE+(0x41<<FCIE_OffShift))
#define NC_STAT         (FCIE_BASE+(0x42<<FCIE_OffShift))
#define NC_AUXR_ADR     (FCIE_BASE+(0x43<<FCIE_OffShift))
#define NC_AUXR_DAT     (FCIE_BASE+(0x44<<FCIE_OffShift))
#define NC_CTRL         (FCIE_BASE+(0x45<<FCIE_OffShift))
#define NC_ST_READ      (FCIE_BASE+(0x46<<FCIE_OffShift))
#define NC_ADDEND       (FCIE_BASE+(0x4A<<FCIE_OffShift))
#define NC_RDD_ESPKT    (FCIE_BASE+(0x4B<<FCIE_OffShift)) // C3
#define NC_RDD_CTL      (FCIE_BASE+(0x4C<<FCIE_OffShift)) // C3
#define NC_RDD_STS      (FCIE_BASE+(0x4D<<FCIE_OffShift)) // C3

//FCIE CMD DATA BUFFER
                                                          // FCIE0       0x74005000
#define CIF_C_ADDR      (FCIE_BASE+(0x80<<FCIE_OffShift)) // FCIE1:      0x74005200
                                                          // power save:           0x74005300
#define CIF_D_ADDR      (FCIE_BASE+(0x100<<FCIE_OffShift))// FCIE2:      0x74005400
                                                          // FCIE3:      0x74005600
// fcie register constant
//============================================
//MIE_EVENT:offset 0x00
//============================================
#define R_MMA_DATA_END          WBIT00
#define R_NC_MMA_DATA_END       WBIT00
#define R_SD_CMD_END            WBIT01
#define R_SD_DATA_END           WBIT02
#define R_MS_DATA_END           WBIT03
#define R_CF_CMD_END            WBIT04
#define R_CF_DATA_END           WBIT05
#define R_SM_JOB_END            WBIT06
#define R_SDIO_INT              WBIT07
#define R_MIU_WP_ERR            WBIT08 // C3
#define R_NC_JOB_END            WBIT09
#define R_NC_RIU2NAND_END       WBIT10 // C3
#define R_CARD_DMA_END          WBIT11 // this bit will not set in CIF_D path
#define R_NC_R2N_ECC_ERR        WBIT12
#define R_PWR_SAVE_END          WBIT13
//============================================
//MIE_INT_EN:offset 0x01
//============================================
#define R_MMA_DATA_ENDE         WBIT00
#define R_NC_MMA_DATA_ENDE      WBIT00 // for backward compatible
#define R_SD_CMD_ENDE           WBIT01
#define R_SD_DATA_ENDE          WBIT02
#define R_MS_DATA_ENDE          WBIT03
#define R_CF_CMD_ENDE           WBIT04
#define R_CF_DATA_ENDE          WBIT05
#define R_SM_JOB_ENDE           WBIT06
#define R_SDIO_INTE             WBIT07
#define R_MIU_WP_ERR_EN         WBIT08 // C3
#define R_NC_JOB_ENDE           WBIT09
#define R_NC_RIU2NAND_INT_EN    WBIT10 // C3
#define R_CARD_DMA_END_INT_EN   WBIT11
#define R_NC_R2N_ECC_ERR_EN     WBIT12
//============================================
//MMA_PRIORITY:offset 0x02
//============================================
#define R_MMA_R_PRIORITY        WBIT00
#define R_MMA_W_PRIORITY        WBIT01
#define R_JOB_RW_DIR            WBIT02
#define R_NC_JOB_RW_DIR         R_JOB_RW_DIR // for backward compatible
#define R_DATA_SCRAM_EN         WBIT03 // C3 how to use?..........................................
#define R_FIFO_CLK_RDY          WBIT05 // BIG2 only
#define R_MIU_BUS_TYPE_MSK      WBIT09+WBIT08
#define R_MIU_BUS_CTRL_EN       WBIT10
//============================================
//MIU_DMA1:offset 0x03
//============================================
//============================================
//MIU_DMA0:offset 0x04
//============================================
//============================================
//CARD_EVENT:offset 0x05
//============================================
#define R_SD_STS_CHG            WBIT00
#define R_MS_STS_CHG            WBIT01
#define R_CF_STS_CHG            WBIT02
#define	R_SM_STS_CHG            WBIT03
#define	R_XD_STS_CHG            WBIT04
#define R_SD_PWR_OC_CHG         WBIT05
#define R_CF_PWR_OC_CHG         WBIT06
#define R_SDIO_STS_CHG          WBIT07
//============================================
//CARD_INT_EN:offset 0x06
//============================================
#define R_SD_STS_EN             WBIT00
#define R_MS_STS_EN             WBIT01
#define R_CF_STS_EN             WBIT02
#define	R_SM_STS_EN             WBIT03
#define	R_XD_STS_EN             WBIT04
#define R_SD_PWR_OC_DET_EN      WBIT05
#define R_CF_PWR_OC_DET_EN      WBIT06 // U01
#define R_CARD_DMA_END_EN       WBIT06 // U02
#define R_SD_CD_SRC             WBIT07 // 0: SD_CDZ, 1: SD_DAT3
#define R_SDIO_STS_EN           WBIT08
#define R_SDIO_CD_SRC           WBIT09 // C3
#define R_ALL_CARD_STS_EN       (R_SD_STS_EN+R_MS_STS_EN+R_CF_STS_EN+R_XD_STS_EN+R_SDIO_STS_EN)
//============================================
//CARD_DET:offset 0x07
//============================================
#define R_SD_DET_N              WBIT00
#define R_MS_DET_N              WBIT01
#define R_CF_DET_N              WBIT02
#define	R_SM_DET_N              WBIT03
#define	R_XD_DET_N              WBIT04
#define R_SD_OCDET_STS          WBIT05
#define R_CF_OCDET_STS          WBIT06
#define R_SDIO_DET_N            WBIT07
#define R_NF_RDBZ_STS           WBIT08 // C3
//============================================
//CARD_PWR:offset 0x08
//============================================
#define R_SD_PWR_ON             WBIT00
#define R_CF_PWR_ON             WBIT01
#define R_SD_PWR_PAD_OEN        WBIT02
#define	R_CF_PWR_PAD_OEN        WBIT03
#define R_RIU2NAND_JOB_END_ACT  WBIT06 // C3 for test
#define R_NC_JOB_END_ACT        WBIT07 // C3 for test
//============================================
//INTR_TEST:offset 0x09 all for test
//============================================
#define R_FORCE_MMA_DATA_END    WBIT00
#define R_FORCE_SD_CMD_END      WBIT01
#define R_FORCE_SD_DATA_END     WBIT02
#define R_FORCE_MS_DATA_END     WBIT03
#define R_FORCE_CF_REQ_END      WBIT04
#define R_FORCE_CF_DATA_END     WBIT05
#define R_FORCE_SM_JOB_END      WBIT06
#define R_FORCE_NC_JOB_END      WBIT06 // for backward compatible
#define R_FORCE_SDIO_INT        WBIT07
#define R_FORCE_SD_STS_CHG      WBIT08
#define R_FORCE_MS_STS_CHG      WBIT09
#define R_FORCE_CF_STS_CHG      WBIT10
#define R_FORCE_SM_STS_CHG      WBIT11
#define R_FORCE_XD_STS_CHG      WBIT12
#define R_FORCE_SD_OC_STS_CHG   WBIT13
#define R_FORCE_CF_OC_STS_CHG   WBIT14
#define R_FORCE_SDIO_STS_CHG    WBIT15
//============================================
//MIE_PATH_CTL:offset 0x0A
//============================================
#define R_MMA_ENABLE            WBIT00
#define R_SD_EN                 WBIT01
#define R_MS_EN                 WBIT02
#define R_CF_EN                 WBIT03
#define R_SM_EN                 WBIT04
#define R_NC_EN                 WBIT05
//============================================
//NC_JOB_BL_CNT:offset 0x0B
//============================================
//============================================
//TR_BK_CNT:offset 0x0C
//============================================
//============================================
//RSP_SIZE:offset 0x0D
//============================================
//============================================
//CMD_SIZE:offset 0x0E
//============================================
//============================================
//CARD_WD_CNT:offset 0x0F
//============================================
//============================================
//SD_MODE:offset 0x10
//============================================
#define R_SD_CLK_EN             WBIT00
#define R_SD_4BITS              WBIT01
#define R_SD_8BITS              WBIT02
#define R_SDDRL                 WBIT03
#define R_SD_CS_EN              WBIT04
#define R_SD_DEST               WBIT05 // 0: Data FIFO, 1: CIF FIFO
#define R_SD_DATSYNC            WBIT06
#define R_MMC_BUS_TEST          WBIT07
#define R_SDIO_RDWAIT           WBIT08
#define R_SDIO_SD_BUS_SW        WBIT09
//============================================
//SD_CTL:offset 0x11
//============================================
#define R_SD_RSPR2_EN           WBIT00 // Response R2 type
#define R_SD_RSP_EN             WBIT01
#define R_SD_CMD_EN             WBIT02
#define R_SD_DTRX_EN            WBIT03
#define R_SD_DTRX_DIR           WBIT04 // 0: R, 1:W
#define R_SDIO_INT_MOD0         WBIT08
#define R_SDIO_INT_MOD1         WBIT09
#define R_SDIO_DET_ON           WBIT10
//============================================
//SD_STS:offset 0x12
//============================================
#define R_SD_DAT_CERR           WBIT00
#define R_SD_DAT_STSERR         WBIT01
#define R_SD_DAT_STSNEG         WBIT02
#define R_SD_CMD_NORSP          WBIT03
#define R_SD_CMDRSP_CERR        WBIT04
#define R_SD_WR_PRO_N           WBIT05
#define R_SD_DAT0               WBIT08
#define R_SD_DAT1               WBIT09
#define R_SD_DAT2               WBIT10
#define R_SD_DAT3               WBIT11
#define R_SD_DAT4               WBIT12
#define R_SD_DAT5               WBIT13
#define R_SD_DAT6               WBIT14
#define R_SD_DAT7               WBIT15
//============================================
//MS_MODE:offset 0x13
//============================================
#define R_MS_DAT_LINE0          WBIT00
#define R_MS_DAT_LINE1          WBIT01
#define R_DAT_DLY0              WBIT02
#define R_DAT_DLY1              WBIT03
#define R_DAT_DLY2              WBIT04
#define R_BS_DLY0               WBIT05
#define R_BS_DLY1               WBIT06
#define R_BS_DLY2               WBIT07
#define R_TPC0                  WBIT08
#define R_TPC1                  WBIT09
#define R_TPC2                  WBIT10
#define R_TPC3                  WBIT11
//============================================
//MS_CTL:offset 0x14
//============================================
#define R_MS_REGTRX_EN          WBIT00
#define R_MS_DTRX_EN            WBIT01
#define R_MS_BUS_DIR            WBIT02 // 0: read form card, 1: Write to card
#define R_MS_BURST              WBIT03
#define R_MS_DEST               WBIT04
//============================================
//MS_STS:offset 0x15
//============================================
#define R_DAT0                  WBIT00
#define R_DAT1                  WBIT01
#define R_DAT2                  WBIT02
#define R_DAT3                  WBIT03
#define R_MS_TOUT               WBIT04
#define R_MS_CRCERR             WBIT05
//============================================
//CF_INF_CTL1:offset 0x16
//============================================
#define R_CFBUS_TYPE            WBIT00 // 0: 16 bits, 1: 8 bits
#define R_CF_BST_A0             WBIT01
#define R_CF_BST_A1             WBIT02
#define R_CF_BST_A2             WBIT03
#define R_CF_IORDY_OEN          WBIT04 // C3 has no this one
//============================================
//CF_INF_CTL2:offset 0x17
//============================================
#define R_CF_CS0                WBIT00
#define R_CF_CS1                WBIT01
#define R_CF_A0                 WBIT02
#define R_CF_A1                 WBIT03
#define R_CF_A2                 WBIT04
#define R_CF_RSTZ               WBIT05
#define R_CF_INTRQ              WBIT06
#define R_CF_IORDY              WBIT07
//============================================
//CF_BUS:offset 0x18
//============================================
//============================================
//CF_STB_SET:offset 0x19
//============================================
#define R_CF_STBL0              WBIT00
#define R_CF_STBL1              WBIT01
#define R_CF_STBL2              WBIT02
#define R_CF_STBL3              WBIT03
#define R_CF_STBH0              WBIT04
#define R_CF_STBH1              WBIT05
#define R_CF_STBH2              WBIT06
#define R_CF_STBH3              WBIT07
//============================================
//CF_CTL:offset 0x1A
//============================================
#define R_CF_REG_EN             WBIT00
#define R_CF_DTRX_EN            WBIT01
#define R_CF_BUS_DIR            WBIT02
#define R_CF_DEST               WBIT03 // 0: Data FIFO, 1: CIF FIFO
#define R_CF_BURST              WBIT04
#define R_CF_IORDY_DIS          WBIT05
#define R_CF_BURST_ERR          WBIT06
//============================================
//SDIO_CTL:offset 0x1B
//============================================
#define R_SDIO_BLK_MOD          WBIT15
//============================================
//SDIO_ADDR0:offset 0x1C
//============================================
//============================================
//SDIO_ADDR1:offset 0x1D
//============================================
//============================================
//SDIO_STS:offset 0x1E
//============================================
#define R_SDIO_DAT0             WBIT00
#define R_SDIO_DAT1             WBIT01
#define R_SDIO_DAT2             WBIT02
#define R_SDIO_DAT3             WBIT03
//============================================
//RIU2NAND_STAT   :offset 0x1F
//============================================
#define R_DMA_RD4_NFC           WBIT00
#define R_RIU2NAND_DIR          WBIT01 // 0: RIU2NAND, 1: NAND2RIU
//============================================
//RIU2NAND_CTL    :offset 0x20
//============================================
#define R_RIU2NAND_EN           WBIT00
#define R_RIU2NAND_R_STR        WBIT01
#define R_RIU2NAND_R_EN         WBIT02
#define R_RIU2NAND_R_END        WBIT03
#define R_RIU2NAND_W_STR        WBIT04
#define R_RIU2NAND_W_EN         WBIT05
#define R_RIU2NAND_W_END        WBIT06
#define R_RIU2NAND_LB_EN        WBIT08
#define R_NFIE_DLY_EN           WBIT09 // for SSO issue?.....................................
#define R_NFIE_DLY_L0           WBIT10
#define R_NFIE_DLY_L1           WBIT11
#define R_NFIE_DLY_H0           WBIT12
#define R_NFIE_DLY_H1           WBIT13
//============================================
//RIU2NAND_R      :offset 0x21
//============================================
//============================================
//RIU2NAND_W      :offset 0x22
//============================================
//============================================
//CF_TIMING       :offset 0x23
//============================================
#define R_CF_DLY_EN             WBIT15
//============================================
//SM_TIMING       :offset 0x24
//============================================
#define R_SM_DLY_EN             WBIT07
//============================================
//MISC_TIMING     :offset 0x25
//============================================
//============================================
//NC_CIF_FIFO_CTL:offset 0x25
//============================================
// only need in montage serious
#define R_CIFC_RD_REQ           WBIT00
#define R_CIFD_RD_REQ           WBIT01
//============================================
//SM_INF_CTL:offset 0x26
//============================================
#define R_SM_RBZ                WBIT00
#define R_SM_WPDZ               WBIT01
#define R_SM_WPZ                WBIT02
#define R_SM_CEZ                WBIT03
#define R_SM_ALE                WBIT04
//============================================
//SM_ADR_REQ:offset 0x27
//============================================
//============================================
//SM_CMD_REQ:offset 0x28
//============================================
//============================================
//SM_STB_SET:offset 0x29
//============================================
#define R_SM_STBL0              WBIT00
#define R_SM_STBL1              WBIT01
#define R_SM_STBL2              WBIT02
#define R_SM_STBL3              WBIT03
#define R_SM_STBH0              WBIT04
#define R_SM_STBH1              WBIT05
#define R_SM_STBH2              WBIT06
#define R_SM_STBH3              WBIT07
//============================================
//SM_MODE:offset 0x2A
//============================================
#define R_SM_PGLEN              WBIT00
#define R_SM_ECC_FUN            WBIT01
#define R_HI_SECTOR             WBIT02
//============================================
//SM_CTL:offset 0x2B
//============================================
#define R_SM_REG_EN             WBIT00
#define R_SM_DTRX_EN            WBIT01
#define R_SM_BUS_DIR            WBIT02
#define R_SM_DEST               WBIT03
#define R_SM_BURST              WBIT04
//============================================
//SM_STS:offset 0x2C
//============================================
#define R_SM_ECC_RCV_ACT        WBIT00
#define R_SM_ECC_RCV_FAIL       WBIT01
#define R_SM_HALF_PAGE_END      WBIT02
//============================================
//DMA_OFFSET:offset 0x2E
//============================================
//============================================
//FCIEU02MISC:offset 0x2F
//============================================
#define R_XD_RWE_LOW            WBIT00
#define R_CLK_RDY_4_ACES        WBIT07
//============================================
//TEST_MODE:offset 0x30
//============================================
#define R_DBFA_BISTFAIL         WBIT00
#define R_DBFB_BISTFAIL         WBIT01
#define R_CIFC_BISTFAIL         WBIT02
#define R_CIFD_BISTFAIL         WBIT03
#define R_PAD_SWAP              WBIT07 // C3 only
#define R_DEBUG_MODE0           WBIT08
#define R_DEBUG_MODE1           WBIT09
#define R_DEBUG_MODE2           WBIT10
#define R_SD_MS_COBUS           WBIT11
#define R_FCIE_SOFT_RST         WBIT12
#define R_NFIE_SOFT_RESETZ      WBIT12 // For backward compatible
#define R_ENDIAN_SEL            WBIT13
//============================================
//NC_MISC offser 0x31
//============================================
#define R_NC_DBFWEN_SYNC        0x0010
#define R_NC_DOH4_DLY           0x0008
#define R_NC_DOL4_DLY           0x0004
//#define                       0x0002
#define R_NC_RW8B_EN            0x0001
//============================================
//PWRSAVE_MASK    0x34
//============================================
//============================================
//RWRSAVE_CTL     0x35
//============================================
#define R_PWRSAVE_EN            WBIT00
#define R_PWRSAVE_TEST          WBIT01
#define R_PWRSAVE_INT_EN        WBIT02
#define R_PWRSAVE_RST_N         WBIT03 // low active
#define R_PWRSAVE_RIU_TEST      WBIT05
#define R_PWRSAVE_HW_REST       WBIT06
#define R_PWRSAVE_LOSS_PWR      WBIT07

/*
0	reg_power_save_mode
1	reg_sd_power_save_riu
2	reg_power_save_mode_int_en
3	reg_sd_power_save_rst
4	reg_power_save_int_force
5	reg_riu_save_event
6	reg_rst_save_event
7	reg_bat_save_event
*/

//============================================
//NAND_TIMING     :offset 0x37
//============================================
#define R_NAND_CTL_DLY          WBIT12
//============================================
//MIU_WP_MIN_AH_S :offset 0x38
//============================================
#define R_MIU_WP_EN             WBIT08
#define R_FORCE_MIU_WP_ERR      WBIT09
//============================================
//MIU_WP_MIN_AL   :offset 0x39
//============================================
//============================================
//MIU_WP_MAX_AH   :offset 0x3A
//============================================
//============================================
//MIU_WP_MAX_AL   :offset 0x3B
//============================================
//============================================
//MIU_WP_ERR_AH   :offset 0x3C
//============================================
//============================================
//MIU_WP_ERR_AL   :offset 0x3D
//============================================
//============================================
//FCIE_INFO       :offset 0x3F
//============================================
#define R_SDMMC_HW              WBIT00
#define R_MS_HW                 WBIT01
#define R_CF_HW                 WBIT02
#define R_SM_HW                 WBIT03
#define R_SDIO_HW               WBIT04
#define R_NAND_HW               WBIT05
#define R_MIU_BUS_WIDTH         WBIT06|WBIT07
#define R_MIU_BUS_ALIGN_BYTE    WBIT08
#define R_PROGRAM_PAD           WBIT09
#define R_PROGRAM_CLK           WBIT10
//============================================
//NC_CFG0:offset 0x40
//============================================
#define NC_CFG0_RESET_VALUE    0x0003
#define R_NC_PSIZE_SEL          WBIT00      // 0:512+16, 1:2048+64
#define R_NC_DSIZE_SEL          WBIT01      // 0:512, 1:512+16
#define R_NC_CE_EN              WBIT02
#define R_NC_CE_AUTO            WBIT03
//#define R_NC_DUAL_MODE          WBIT04
//#define R_NC_PSIZE_X2           WBIT05    // 0: 2048, 1: 4096
//#define R_NC_WORD_MODE          WBIT06    // 0: 8bit, 1:16bit
#define R_NC_ONECOLADR          WBIT07      // one column address
#define R_NC_CHK_RB_HIGH        WBIT08
#define R_NC_REDU_BYPASS        WBIT09      // read out redundant, but do not put in CIF_C
#define R_NC_WP_EN              WBIT10
#define R_NC_WP_AUTO            WBIT11
#define R_NC_ECCERR_NSTOP       WBIT12      // If ECC error happen, continue the repeat count
#define R_NC_DYNGATED_ON        WBIT13      // dynamic gated ECC clock for power save
#define R_NC_CE_SEL             WBIT14|WBIT15
//============================================
//NC_CFG1:offset 0x41
//============================================
#define R_NC_WR_HW0             WBIT00
#define R_NC_WR_HW1             WBIT01
#define R_NC_WR_LW0             WBIT02
#define R_NC_WR_LW1             WBIT03
#define R_NC_RD_HW0             WBIT04
#define R_NC_RD_HW1             WBIT05
#define R_NC_RD_LW0             WBIT06
#define R_NC_RD_LW1             WBIT07
#define R_NC_DEB_SEL0           WBIT08
#define R_NC_DEB_SEL1           WBIT09
#define R_NC_DEB_SEL2           WBIT10
//============================================
//NC_STAT:offset 0x42
//============================================
#define R_NC_STCK_ERRL8         WBIT00
//#define R_NC_STCK_ERRH8         WBIT01
#define R_NC_ECC_FLAG0          WBIT02
#define R_NC_ECC_FLAG1          WBIT03
#define R_NC_ECC_FLAG_MSK       (WBIT02|WBIT03)
#define R_NC_ECC_SEC_CNT0       WBIT04
#define R_NC_ECC_SEC_CNT1       WBIT05
#define R_NC_ECC_SEC_CNT2       WBIT06
//============================================
//NC_AUXR_ADR:offset 0x43
//============================================
//============================================
//NC_AUXR_DAT:offset 0x44
//============================================
//============================================
//NC_CTRL:offset 0x45
//============================================
#define R_NC_JOB_START          WBIT00
#define R_NC_CIFC_ACCESS        WBIT01
#define R_NC_INST_HB_SEL        WBIT02
#define R_NC_DIR_DSTREAM        WBIT03
#define R_NC_ECC_BYPASS         WBIT04
#define R_NC_NONEFFH_NUM0       WBIT05
#define R_NC_NONEFFH_NUM1       WBIT06
#define R_NC_SER_PART_MODE      WBIT07
#define R_NC_SER_PART_CNT_2     WBIT08 // 0b'01
#define R_NC_SER_PART_CNT_3     WBIT09 // 0b'10

//============================================
//NC_ST_READ:offset 0x46
//============================================
//============================================
//NC_ADDEND:offset 0x4A
//============================================
#define R_NC_RPT_ADR3_SEL2      WBIT11
#define R_NC_RPT_ADR3_SEL1      WBIT10
#define R_NC_RPT_ADR3_SEL0      WBIT09
#define R_NC_RPT_ADR2_SEL2      WBIT08
#define R_NC_RPT_ADR2_SEL1      WBIT07
#define R_NC_RPT_ADR2_SEL0      WBIT06
#define R_NC_RPT_ADR1_SEL2      WBIT05
#define R_NC_RPT_ADR1_SEL1      WBIT04
#define R_NC_RPT_ADR1_SEL0      WBIT03
#define R_NC_RPT_ADR0_SEL2      WBIT02
#define R_NC_RPT_ADR0_SEL1      WBIT01
#define R_NC_RPT_ADR0_SEL0      WBIT00
//============================================
//NC_RDD_ESPKT    :offset 0x4B
//============================================
#define R_MSK_RDD_ESPKT_DAT0    0x00FF
#define R_MSK_RDD_ESPKT_DAT1    0xFF00
//============================================
//NC_RDD_CTL      :offset 0x4C
//============================================
#define R_RDD_CHK_EN            WBIT00
#define R_RDD_CHK_STP           WBIT01
#define R_RDD_ADDR0_0           0x0000
#define R_RDD_ADDR0_1           0x0004
#define R_RDD_ADDR0_2           0x0008
#define R_RDD_ADDR0_3           0x000C
#define R_RDD_ADDR0_4           0x0010
#define R_RDD_ADDR0_5           0x0014
#define R_RDD_ADDR1_0           0x0000
#define R_RDD_ADDR1_1           0x0020
#define R_RDD_ADDR1_2           0x0040
#define R_RDD_ADDR1_3           0x0060
#define R_RDD_ADDR1_4           0x0080
#define R_RDD_ADDR1_5           0x00A0
//============================================
//NC_RDD_STS      :offset 0x4D
//============================================
#define R_RDD_CLS_STS           WBIT00
#define R_RDD_DAT_ERR           0x0006
#define R_ERASED_BLK_ECC_CHK    WBIT03

///////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////
#endif // #ifdef C3_FCIE
///////////////////////////////////////////////////////////////////////////////////////////////////

//===================================================================

//--------------------------------------------------------------------
//  MACROS
//--------------------------------------------------------------------

#if 0
#define SDRemoved()     (REG(CARD_DET)&R_SD_DET_N)
#else
    #define SDRemoved()     0
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef  __FPGA_MODE__
// FPGA use GPIO emulate
#define MDrvSDPower(On) do {                                                                        \
                            FCIE_RIU_16_OF(0x7400760C, WBIT10);                                     \
                            if(On)                                                                  \
                            {                                                                       \
                                FCIE_RIU_16_OF(0x7400760C, WBIT09);                                 \
                            }                                                                       \
                            else                                                                    \
                            {                                                                       \
                                FCIE_RIU_16_ON(0x7400760C, WBIT09);                                 \
                            }                                                                       \
                        } while(0);
#else
// real chip use asura to control power
#define MDrvSDPower(On) do {                                                                        \
                            if(On)                                                                  \
                            {                                                                       \
                                sys_periphPwrCtrl(CTRL_ON, PERIPH_SDCARD);                          \
                            }                                                                       \
                            else                                                                    \
                            {                                                                       \
                                sys_periphPwrCtrl(CTRL_OFF, PERIPH_SDCARD);                         \
                            }                                                                       \
                        } while(0);

#endif

#define CheckTimeOut()  do {                                                                        \
                            if(u8StorageInit==0)                                                    \
                            {                                                                       \
                                if(MDrv_isSysTimerExpire())                                         \
                                {                                                                   \
                                    printf("init take more than 500 ms, break!\r\n");               \
                                    goto ErrorHandling;                                             \
                                }                                                                   \
                            }                                                                       \
                        } while(0);

///////////////////////////////////////////////////////////////////////////////////////////////////

// CardInfo
#define _2KLUT                  0x80
#define _LUTWP                  0x40
#define _EJECT                  0x20  // Eject (wait for disconnect)
#define _RPT_MEDIA_CHGED        0x10  // First time Attached
#define _MEDIUM_FAILED          0x08
#define _WP                     0x04  // Write Protect
#define _READY                  0x02  // Ready
#define _INIT_CARD              0x01  // Initiate card

// CREADER_EVENT
#define MMA_END_EVENT           0x000001
#define SD_CMD_END_EVENT        0x000002
#define SD_DATA_END_EVENT       0x000004
#define MS_DATA_END_EVENT       0x000008
#define CF_REQ_END_EVENT        0x000010
#define CF_DATA_END_EVENT       0x000020

#define SD_STSCHG_EVENT         (R_SD_STS_EN<<8)
#define MS_STSCHG_EVENT         (R_MS_STS_EN<<8)
//#define CF_STSCHG_EVENT         (R_CF_STS_EN<<8)
//#define SM_STSCHG_EVENT         (R_SM_STS_EN<<8)
//#define XD_STSCHG_EVENT         (R_XD_STS_EN<<8)

#define CR_HW_EVENT             0x010000
#define CR_RW_REQ_EVENT         0x020000
#define CR_RW_COMPLETE_EVENT    0x040000

//  swFlag
#define _ACCESS_CONTROL         0x80
#define _MEDIA_CHANGE           0x40
#define _PRE_SET_WRITE          0x20
#define _PRE_SET_READ           0x10
#define _TIME_OUT               0x01
#define _WAIT_INT               0x02
#define _MS_PRO_SetBusAgain     0x04
#define _MS_PRO_1bit            0x08

#define _CARD_EJECT             0x40
#define _TIME_OUT               0x01
// DMA aligement
#define DMA_ALIGNMENT           0x08

#if 1
// temp setting
#define CKG_FCIE_SHIFT                      (0)
#define FCIE_CLOCK_SEL_SHIFT                (CKG_FCIE_SHIFT+2)
#define FCIE_CLOCK_SEL_300K                 (0<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_750K                 (1<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_5_4M                 (2<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_13_5M                (3<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_18M                  (4<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_22_7M                (5<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_27M                  (6<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_32M                  (7<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_43_2M                (8<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_57M                  (9<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_SEL_72M                  (10<<FCIE_CLOCK_SEL_SHIFT)

#define FCIE_CLOCK_MCLK_DIV10               (3<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_MCLK_DIV6                (8<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_MCLK_DIV5                (9<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_MCLK_DIV4                (10<<FCIE_CLOCK_SEL_SHIFT)
#define FCIE_CLOCK_MCLK_DIV3                (11<<FCIE_CLOCK_SEL_SHIFT)


typedef enum EFCIE_CLOCK
{
    E_FCIE_CLK_NONE =  0,
    E_FCIE_CLK_300K =  1,
    E_FCIE_CLK_005M =  2,
    E_FCIE_CLK_010M =  3,
    E_FCIE_CLK_020M =  4,
    E_FCIE_CLK_025M =  5,
    E_FCIE_CLK_030M =  6,
    E_FCIE_CLK_035M =  7,
    E_FCIE_CLK_040M =  8,
    E_FCIE_CLK_045M =  9,
    E_FCIE_CLK_050M = 10,

} FCIE_CLOCK;

#endif

#define RW_OK       0x00
#define RW_CARDCHG  0x01
#define RW_FAIL     0x02

/// Define Read/write direction
typedef enum
{
    /// Read from memory card
    CARD_READ = 0,
    /// write to memory card
    CARD_WRITE = 1
}RW_DIR;


enum
{
    ID_READ_SECTOR=0,
    ID_ISCARDREADY,
    ID_GET_CARD_CAPACITY,

};
//====================================================
//    JOB_ID constants for write direction
//====================================================

enum
{
    ID_WRITE_SECTOR=0
    //ID_ISCARDREADY,
    //ID_GET_CARD_CAPACITY,

};
//====================================================
//    JOB_STS constants
//====================================================


/// Define memory card type
typedef enum ECARDTYPE
{
    _UNKNOW     = WBIT00,   // Unknow memory card
    _MMC        = WBIT01,   // MMC card
    _SD         = WBIT02,   // SD card
    _SM         = WBIT03,   // SmartMedia card
    _XD         = WBIT04,   // xD-Picture card
    _MS         = WBIT05,   // MemoryStick card
    _MSPRO      = WBIT06,   // Memory Stick Pro card
    _CF         = WBIT07,   // Compact Flash card
    _SDIO_SD    = WBIT08,   // SDIO port SD/MMC
    _SDIO_MS    = WBIT09,   // SDIO port MS
    _SDIO_MSPRO = WBIT10,   // SDIO port MS PRO
    _NAND       = WBIT11,   // Nand flash

} CARDTYPE;


typedef enum
{
    E_PORT_RDER,    // card reader port
    E_PORT_SDIO,    // SDIO port

} FCIE_PORT;

/// Declare Card information
typedef struct CARDINFO_STRUCT
{
    /// Memory card ready or not
    bool Ready;	// Card Ready?
    /// Card type
    CARDTYPE eCardType;
    /// Card capacity
    U32 Capacity;	// sector count
    /// Sector size
    U32 BlkSz;	// sector size
    /// connected?
    bool bConnected;
    /// has MBR?
    bool bHasMBR;
    /// U8 partition type
    U8 u8PartitionType;
    /// Logical Partition Start Sector, only for extended partition type
    U32 u32LogicalPartitionStartSector;
    /// first sector LBA
    U32 u32FirstSector;

} CARDINFO;

/// Declare Card DMA information
typedef struct _DMARW
{
    /// DRAM address, must be 8 bytes aligned
    U32 DMA_ADR;
    /// sector address
    U32 LBA;
    /// sector count
    U8  LEN;
    /// use callback?
    //BOOL callback;
    /// CallBack function
    //FS_NonBlockCallback CDriver_Callback;
    /// Read/Write direction
    RW_DIR  RW;
}DMARW;

typedef struct _CDRREG
{
    U32 MIE_EVENT_MIR;
    U32 MIE_INT_EN_MIR;
    U32 CARD_EVENT_MIR;
    U8  CARD_EVENT_MIR2;
    U32 SD_MODE_MIR;
}CDRREG;

///////////////////////////////////////////////////////////////////////////////////////////////////
// Jeffrey modified
///////////////////////////////////////////////////////////////////////////////////////////////////

typedef struct
{
    //CARD_DETECT_QUE CardDetectQue;

    CARDTYPE CardType;// Memory card type

    U32  CardClk;// Clock seeting for current memory card

    U8 CardInfo;// misc card status (write protect/ready/eject)

    U32 BootBlk;// CIS/Boot block address, SM/xD/MS only

    U32 swFlag;

    U32 CardCapa;// capacity of current memory card

    U32 BlkSize;// Sector size of current memory card

    U32 OldAddr;

    RW_STATUS rw_status;

    DMARW dmarw; // DMA information

    CDRREG reg;

    U8 SdioPort;

    U8 SpecVer; // MMC access use

    U8 MMC4Option;

    U8 gu8RCA[2];

    U8 _u8SDHC;

    U8 u8FourBits;

} DISK_INFO;


#define DISK0   (E_SLOT_SDMMC)
#define DISK1   0
#define DISK2   0
#define DISK3   0
#define DISK4   0

#define SDIO_FUNCTION   SDIO_FUNC_SD

#ifndef DISK0
    #define DISK0   (E_SLOT_NAND)
#endif
#ifndef DISK1
    #define DISK1   (E_SLOT_CF)
#endif
#ifndef DISK2
    #define DISK2   (E_SLOT_SDMMC|E_SLOT_MSPRO|E_SLOT_XD)
#endif
#ifndef DISK3
    #define DISK3   0
#endif
#ifndef DISK4
    #define DISK4   0
#endif


#ifndef DISK_NUM
    #define DISK_NUM    1
#endif
///////////////////////////////////////////////////////////////////////////////////////////////////



/*function ======================================================================================*/


extern U8 gu8Boardtype;
extern U8 _u8DriveNo;

void msAPI_Timer_Delayms(U8 u8ms);
void msAPI_InitmemPool(int StarPoolAddr, int PoolSize);
void *msAPI_Malloc(int size);
void msAPI_Free (void * ptr);

DRV_CREADER_INTERFACE void MDrvInitFcie(void);
extern U8 _DrvSDMMC_ChgCardState(void);
void DrvCARDREADER_EnableCardInf(U8 u8MIE_PATH);
DRV_CREADER_INTERFACE void MDrv_CARDREADER_Init_PAD(U8 u8BoundingType);
DRV_CREADER_INTERFACE void _Drv_CARDREADER_ISR(void);
//DRV_CREADER_INTERFACE U32 MDrv_CReader_ReadCapacity(STORAGETYPE eCardType);

DRV_CREADER_INTERFACE void MDrv_CARDREADER_SWITCH_PAD(U8 u8Type, U16 u8State);
DRV_CREADER_INTERFACE U8 _DrvCARDREADER_GetCMD_RSP_BUF(U8 addr);
DRV_CREADER_INTERFACE void _DrvCARDREADER_SetCMD_RSP_BUF(U8 u8addr, U8 u8value);
DRV_CREADER_INTERFACE void _DrvCARDREADER_SetFCIE_Clock(U16 Clk);
DRV_CREADER_INTERFACE U8 _DrvCARDREADER_GetCIFIFO(U16 u16addr);
DRV_CREADER_INTERFACE void _DrvCARDREADER_SetCIFIFO(U8 u8addr, U8 u8value);
DRV_CREADER_INTERFACE U8 _DrvCARDREADER_wMIEEvent(U16 u16ReqVal, U8 u8bDev, U32 u32WaitMs);
DRV_CREADER_INTERFACE void _MDrvSetMiuAddr(U32 DMA_ADDR);
DRV_CREADER_INTERFACE void _Mdrv_Reset_Fcie(void);

#endif    /*_DRV_CREADER_H END */

