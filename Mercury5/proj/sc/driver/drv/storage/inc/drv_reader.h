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

#ifdef DRV_CREADER
    #define DRV_CREADER_INTERFACE
#else
    #define DRV_CREADER_INTERFACE extern
#endif


///////////////////////////////////////////////////////////////////////////////////////////////////


#define MCU_8BIT    	1
#define MCU_32BIT   	2
#define FCIE_PLATFORM   MCU_32BIT

#define PROJECT_C3  1 // ceramal 3
#define PROJECT_M3  2 // montage 3, bigblue 2

#define SDCDZ_H_CARD_IN 1
#define SDCDZ_L_CARD_IN 0

#define FCIE_PROJECT PROJECT_M3

#if   (FCIE_PROJECT==PROJECT_C3)
    #if (FCIE_PLATFORM==MCU_8BIT)
        #define PLATFORM_SUPPORT_ANSI_COLOR 1
    #else // Aeon
        #define PLATFORM_SUPPORT_ANSI_COLOR 0
    #endif
    #define MICRO_SD_NO_WP                  0

    #define SDCDZ_POLARITY                  SDCDZ_L_CARD_IN
#elif (FCIE_PROJECT==PROJECT_M3)
    #define MICRO_SD_NO_WP                  1
    #define PLATFORM_SUPPORT_ANSI_COLOR     0

#endif


#include <string.h>
#include <stdlib.h> // for malloc
#include "hal_flash_ctrl.h"
#include "hal_flash_ctrl_datatype.h"
#include "storage.h"

#define ENABLE  1
#define DISABLE 0

#ifndef TRUE
    #define TRUE    1
#endif
#ifndef FALSE
    #define FALSE   0
#endif

#ifndef ENABLE_NAND
    #define ENABLE_NAND         DISABLE
#endif
#ifndef ENABLE_CF
    #define ENABLE_CF           DISABLE
#endif
#ifndef ENABLE_SDMMC
    #define ENABLE_SDMMC        ENABLE
#endif
#ifndef ENABLE_MSPRO
    #define ENABLE_MSPRO        DISABLE
#endif
#ifndef ENABLE_XD
    #define ENABLE_XD           DISABLE
#endif
#ifndef ENABLE_SDIO
    #define ENABLE_SDIO         ENABLE
#endif


#define CALC_R_W_MAX_MIN_SPEED  DISABLE


///////////////////////////////////////////////////////////////////////////////////////////////////


//#define VA2PA(addr)         ((U32)addr&0x00FFFFFF) // only bit 0~23
#if (FCIE_PLATFORM==MCU_8BIT)
    #define HalStg_DelayMs(MS) MDrv_Timer_Delayms(MS)
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

    #if   (FCIE_PROJECT==PROJECT_C3)
        #define VA2PA(addr)         ((U32)addr&0x00FFFFFF) // only bit 0~23
    #elif (FCIE_PROJECT==PROJECT_M3)
        #define VA2PA(addr)         ((U32)addr&0x0FFFFFFF) // 64MB = 0x04000000
    #endif
    #if 0
    #define fcie_mem_io_write8(dest,data)    *((volatile U8 *)(0x80000000+(dest))) = (U8)(data)
    #define fcie_mem_io_read8(dest,data)	 *((U8 *)(data))= *((volatile U8 *)(0x80000000+(dest)))
    #else
    #define fcie_mem_io_write8(dest,data)    *((volatile U8 *)(dest)) = (U8)(data)
    #define fcie_mem_io_read8(dest,data)	 *((U8 *)(data))= *((volatile U8 *)(dest))
    #endif
#endif

//#include "hal_reg_platform.h"







//--------------------------------------------------------------------
//  MACROS
//--------------------------------------------------------------------


#define SDIORemoved()   (REG(CARD_DET)&R_SDIO_DET_N)


///////////////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////////////


// DiskStatus
#define DISK_STATUS_READY               0x01  // ready, init success
#define DISK_STATUS_WP                  0x02  // write protect

#define RW_OK       0x00
#define RW_CARDCHG  0x01
#define RW_FAIL     0x02


// define read write direction
typedef enum
{
    /// Read from memory card
    CARD_READ = 0,
    /// write to memory card
    CARD_WRITE = 1

} RW_DIR;


typedef enum
{
    E_SR_RESUME             = 0,
    E_SR_SUSPEND            = 1,
    E_SR_STEALTHILY_WORKING = 2

} SUSPEND_RESUME;


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

#define CARDDET_CDZ         BIT00
#define CARDDET_INSERT_LOW  BIT01
#define CARDDET_INSERT_HIGH BIT02
#define DUAL_SD_CARD        BIT03
#define SD2_CDZ             BIT04
#define SD2_CD_INSERT_LOW   BIT05
#define SD2_CD_INSERT_HIGH  BIT06
#define SD_DUAL_1_BIT       BIT07

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

typedef struct _RW_PRMETR
{
    U32 MiuAddr; // DRAM address

    U32 SectorIndex; // sector address

    U32 SectorLength; // sector count

    RW_DIR  RwDir;

} RW_PRMETR;

typedef enum
{
    E_IP_NONE               = 0,
    E_IP_FCIE               = 1,
    E_IP_SDIO               = 2,

} E_IP;

typedef struct _SPEED_CALC
{
    U32 StdaTick;

    U32 AccessSpeed; // KB/s

    U32 AccessSpeedReadMax;

    U32 AccessSpeedReadMin;

    U32 AccessSpeedWriteMax;

    U32 AccessSpeedWriteMin;

} SPEED_CALC;

#include "drv_sd.h"

typedef struct
{
    //CARD_DETECT_QUE CardDetectQue;

    SLOT_STATUS SlotStatus;

    CARDTYPE CardType;// Memory card type

    U32  CardClock;// Clock seeting for current memory card

    U8 DiskStatus;// misc disk status write protect/ready/eject/suspend

    SUSPEND_RESUME SuspendResume;

    U32 BootBlk;// CIS/Boot block address, SM/xD/MS only

    U32 swFlag;

    U32 CardCapa;// capacity of current memory card

    U32 BlkSize;// Sector size of current memory card

    U32 OldAddr;

    RW_STATUS rw_status; //U32 rw_status;

    //DMARW dmarw; // DMA information

    RW_PRMETR RwPrmetr;

    U8 SdioPort;

    U8 SpecVer; // MMC access use

    U8 MMC4Option;

    U8 gu8RCA[2];

    U8 _u8SDHC;

    U8 u8FourBits;

    U8 u8DowngradeClock;

    U32 u32SerialNum;

    U8 CID[16];

    U8 ReadOnly;

    U8 HighSpeedMode;

    SPEED_CALC SpeedCalc;

    BURST_MODE_DATA BurstMode;

} DISK_INFO;

typedef struct
{
    E_IP IP;
    E_PAD_SELECT Pad;
    E_PORT_SELECT Port;

} DISK_CONFIG;

typedef enum
{
    STG_LOG_BEGIN,
    STG_LOG_END,

} STG_LOG_CTRL;

#define BIT_READING WBIT00
#define BIT_WRITING WBIT01
#define BIT_ONE_BIT WBIT02

#ifndef DISK0
    #define DISK0   (E_SLOT_SDMMC)
#endif
#ifndef DISK1
    #define DISK1   (E_SLOT_SDIO)
#endif
#ifndef DISK2
    #define DISK2   0
#endif
#ifndef DISK3
    #define DISK3   0
#endif
#ifndef DISK4
    #define DISK4   0
#endif


#ifndef DISK_NUM
    #define DISK_NUM    2
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////

void    _DrvStg_LogDrvStsnSpendTime(U8 u8Disk, STG_LOG_CTRL LogCtrl);
U32     _DrvStg_CalcIoSpeed(U32 u32SectorCount, U32 u32AcsTime);

DRV_CREADER_INTERFACE void MDrvInitFcie(void);
extern void MDrv_CARDREADER_InitCardInf(U8 u8Disk, E_MIE_INTR_EN_MODE IntrMode);

void MDrv_CReader_Initial(void);

#endif    /*_DRV_CREADER_H END */

