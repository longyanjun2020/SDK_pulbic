////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
* @file    drv_flash_lowl_id.h
* @version
* @brief   Flash Memory Services - Low level definitions ID
*
*/

#ifndef __DRV_FLASH_LOWL_ID_H__
#define __DRV_FLASH_LOWL_ID_H__

/****************************************************************************/
/* COMPILE OPTION OF MCP MODEL                                              */
/****************************************************************************/
#define SPANSION_S71WS256P
#define SPANSION_S71WS128P
#define SPANSION_S71PL127NB0
#define SPANSION_S71PL256NB0
#define SAMSUNG_K5L2833
//#define SAMSUNG_K5L2731
#define SAMSUNG_K5L5563
#define SAMSUNG_K5L5666
#define TOSHIBA_TV00570002CDGB
#define TOSHIBA_TV00560002EDGB		//< 64/32 <--@@@  	
#define TOSHIBA_TY00680002ADGB
#define NUMONYX_M58LR128KT //M36L0R7050T4
#define NUMONYX_M58LR256KT //M36L0R8060T9
#define NUMONYX_M58LR128KC //M36L0R7050U3, M36L0R7060U3

#ifdef SPANSION_S71WS256P
    #define GEO_256MBITS_16K64K16KWORDS
    #define FLASH_S_16BANKS256
    #define FLASH_S_SPANSIONCOMMANDSET
#endif

#ifdef SPANSION_S71WS128P
    #define GEO_128MBITS_16K64K16KWORDS
    #define FLASH_S_16BANKS128
    #define FLASH_S_SPANSIONCOMMANDSET
#endif

#ifdef SPANSION_S71PL127NB0
    #define GEO_128MBITS_32K128K32KWORDS
    #define FLASH_S_QUADRIBANK128
    #define FLASH_S_SPANSIONCOMMANDSET
#endif

#ifdef SPANSION_S71PL256NB0
    #define GEO_256MBITS_32K128K32KWORDS
    #define FLASH_S_QUARDRIBANK256
    #define FLASH_S_SPANSIONCOMMANDSET
#endif

#ifdef SAMSUNG_K5L2833
    #define GEO_TOP_128MBITS_32K4KWORDS
    #define FLASH_S_16BANKS128
    #define FLASH_S_SAMSUNGCOMMANDSETS
#endif

#ifdef SAMSUNG_K5L2731
    #define GEO_128MBITS_4K32K4KWORDS
    #define FLASH_S_QUADRIBANK128
    #define FLASH_S_SAMSUNGCOMMANDSET
#endif

#ifdef SAMSUNG_K5L5563
    #define GEO_256MBITS_32K128K32KWORDS
    #define FLASH_S_QUARDRIBANK256
    #define FLASH_S_SAMSUNGCOMMANDSET
#endif

#ifdef SAMSUNG_K5L5666
    #define GEO_TOP_256MBITS_64K16KWORDS
    #define FLASH_S_16BANKS256
    #define FLASH_S_SAMSUNGCOMMANDSETS
#endif

#ifdef TOSHIBA_TV00570002CDGB
    #define GEO_TOP_128MBITS_64K8KWORDS
    #define FLASH_S_OCTOBANKS128
    #define FLASH_S_TOSHIBACOMMANDSETS
#endif

#ifdef TOSHIBA_TV00560002EDGB
    #define GEO_TOP_64MBITS_32K4KWORDS
    #define FLASH_S_QUADRIBANK64
    #define FLASH_S_TOSHIBACOMMANDSETS
#endif

#ifdef TOSHIBA_TY00680002ADGB
    #define GEO_TOP_256MBITS_64K8KWORDS
    #define FLASH_S_16BANKS256
    #define FLASH_S_TOSHIBACOMMANDSETS
#endif

#ifdef NUMONYX_M58LR128KT
    #define GEO_TOP_128MBITS_64K16KWORDS
    #define FLASH_S_16BANKS128
    #define FLASH_S_NUMONYXCOMMANDSET
#endif

#ifdef NUMONYX_M58LR256KT
    #define GEO_TOP_256MBITS_64K16KWORDS
    #define FLASH_S_16BANKS256
    #define FLASH_S_NUMONYXCOMMANDSET
#endif

#ifdef NUMONYX_M58LR128KC
    #define GEO_TOP_128MBITS_64K16KWORDS
    #define FLASH_S_16BANKS128
    #define FLASH_S_NUMONYXCOMMANDSET
#endif


/****************************************************************************/
/* ELECTRONIC SIGNATURES                                                    */
/****************************************************************************/

/* JEDEC Device manufacturers' IDs
 * More info on: http://www.jedec.org */

#define FLASH_JEDEC_INTEL           0x89
#define FLASH_JEDEC_AMD             0x01
#define FLASH_JEDEC_TOSHIBA         0x98
#define FLASH_JEDEC_ST              0x20
#define FLASH_JEDEC_ATMEL           0x1F
#define FLASH_JEDEC_MICRON          0x2C
#define FLASH_JEDEC_MACRONIX        0xC2
#define FLASH_JEDEC_SHARP           0xB0
#define FLASH_JEDEC_SPANSION        0x01
#define FLASH_JEDEC_SST             0xBF
#define FLASH_JEDEC_SAMSUNG         0xEC
#define FLASH_JEDEC_NUMONYX         0x20
#define FLASH_JEDEC_WINBOND         0xEF
#define FLASH_JEDEC_EONSI           0x1C
#define FLASH_JEDEC_PMC             0x9D
#define FLASH_JEDEC_TEMP            0xC8
/*
 * Device codes
 * (sorted by manufacturer)
 */

/* Intel devices codes */
#define FLASH_DEVICE_INTEL_28F160C3             0x88C2
#define FLASH_DEVICE_INTEL_28F320C3             0x88C4
#define FLASH_DEVICE_INTEL_28F320W18            0x8862
#define FLASH_DEVICE_INTEL_28F640W18            0x8864
#define FLASH_DEVICE_INTEL_28F128L18B           0x880F
#define FLASH_DEVICE_INTEL_28F128L18T           0x880C


/* Micron device codes */
#define FLASH_DEVICE_MICRON_MT28C3224P          0x44B4
#define FLASH_DEVICE_MICRON_MT28C64416W18A      0x44C6


/* Toshiba devices codes */
#define FLASH_DEVICE_TOSHIBA_TH50VSF1480AASB    0x00C2
#define FLASH_DEVICE_TOSHIBA_TH50VSF1480ABSB    0x00C2
#define FLASH_DEVICE_TOSHIBA_TH50VSF2480AASB    0x0098
#define FLASH_DEVICE_TOSHIBA_TH50VSF2582BESBb   0x00C5
#define FLASH_DEVICE_TOSHIBA_TH50VSF2582BESB    0x00C6
#define FLASH_DEVICE_TOSHIBA_TH50VSF2682BFSB    0x0057
/*#define FLASH_DEVICE_TOSHIBA_TH50VSF3682AFSB            0x0057*/ /* 64/4 = 64/8 */
#define FLASH_DEVICE_TOSHIBA_TH50YSF2582BFSB    0x0059
#define FLASH_DEVICE_TOSHIBA_TH50YSF3682AFSB    0x007A
#define FLASH_DEVICE_TOSHIBA_TVO0579002AABD     0x001B // top boot block
#define FLASH_DEVICE_TOSHIBA_TVO0579003AABD     0x001D // bottom boot block
#define FLASH_DEVICE_TOSHIBA_TVO067A002CGAD     0x0049 // top boot block
#define FLASH_DEVICE_TOSHIBA_TVO067A003CGAD     0x004A // bottom boot block
#define FLASH_DEVICE_TOSHIBA_TVO057A002EAGD     0x0049 // top boot block
#define FLASH_DEVICE_TOSHIBA_TV00570002CDGB     0x0003 // top boot block
#define FLASH_DEVICE_TOSHIBA_TY00680002ADGB     0x006F // top boot block
#define FLASH_DEVICE_TOSHIBA_TV00560002EDGB     0x0096 // <-@@@ 64/32

/* ST devices codes */
#define FLASH_DEVICE_ST_M36W216T                0x88CE
#define FLASH_DEVICE_ST_M36W432T                0x88BA
#define FLASH_DEVICE_ST_M36DR432A               0x00A0
#define FLASH_DEVICE_ST_M36W864TE               0x8848
#define FLASH_DEVICE_ST_M36DR864TB              0x8810
#define FLASH_DEVICE_ST_M30W0R7000T             0x881E
#define FLASH_DEVICE_ST_M58WR032FT              0x8814


/* AMD devices codes */
#define FLASH_DEVICE_AMD_AM29LV640MU            0x227E


/* SPANSION devices codes */
// Read cycle1
#define FLASH_DEVICE_SPANSION_ID1               0x227E
// Read cycle2
#define FLASH_DEVICE_SPANSION_S71WS128JC0       0x2218
#define FLASH_DEVICE_SPANSION_S71WS512P_ID2     0x223D
#define FLASH_DEVICE_SPANSION_S71WS256P_ID2     0x2242
#define FLASH_DEVICE_SPANSION_S71WS128P_ID2     0x2244
#define FLASH_DEVICE_SPANSION_S71PL127NB0_ID2   0x2220
#define FLASH_DEVICE_SPANSION_S71PL129NB0_ID2   0x2221
#define FLASH_DEVICE_SPANSION_S71PL256NB0_ID2   0x223C
#define FLASH_DEVICE_SPANSION_S71GL128NB0_ID2   0x2221
#define FLASH_DEVICE_SPANSION_S71GL256NB0_ID2   0x2222
#define FLASH_DEVICE_SPANSION_S71GL512NB0_ID2   0x2223
// Read cycle3
#define FLASH_DEVICE_SPANSION_WS_ID3            0x2200
#define FLASH_DEVICE_SPANSION_PL_ID3            0x2200
#define FLASH_DEVICE_SPANSION_GL_ID3            0x2201
// (FLASH_DEVICE_SPANSION_XXX_ID2 & 0xFF << 8) | (FLASH_DEVICE_SPANSION_PL_ID3 &0xFF)
#define FLASH_DEVICE_SPANSION_S71PL127NB0       0x2000
#define FLASH_DEVICE_SPANSION_S71PL129NB0       0x2100
#define FLASH_DEVICE_SPANSION_S71PL256NB0       0x3C00
// (FLASH_DEVICE_SPANSION_XXX_ID2 & 0xFF << 8) | (FLASH_DEVICE_SPANSION_GL_ID3 &0xFF)
#define FLASH_DEVICE_SPANSION_S71GL128NB0       0x2101
#define FLASH_DEVICE_SPANSION_S71GL256NB0       0x2201
#define FLASH_DEVICE_SPANSION_S71GL512NB0       0x2301
// (FLASH_DEVICE_SPANSION_XXX_ID2 & 0xFF << 8) | (FLASH_DEVICE_SPANSION_PL_ID3 &0xFF)
#define FLASH_DEVICE_SPANSION_S71WS512P         0x3D00
#define FLASH_DEVICE_SPANSION_S71WS256P         0x4200
#define FLASH_DEVICE_SPANSION_S71WS128P         0x4400


/* ATMEL device codes */
#define FLASH_DEVICE_ATMEL_AT52SC1283J          0x00BB
#define FLASH_DEVICE_ATMEL_AT52BR3224AT         0x00C9
#define FLASH_DEVICE_ATMEL_AT52BR1664AT         0x00C2


/* SST device codes */
#define FLASH_DEVICE_SST_36VF1601               0x734B
#define FLASH_DEVICE_SST_36VF1602               0x734A


/* SAMSUNG device codes */
#define FLASH_DEVICE_SAMSUNG_K5L2731            0x257E
#define FLASH_DEVICE_SAMSUNG_K5L2731_ID2        0x2508
#define FLASH_DEVICE_SAMSUNG_K5L2731_ID3        0x2501
#define FLASH_DEVICE_SAMSUNG_K5L5563_ID1        0x227E
#define FLASH_DEVICE_SAMSUNG_K5L5563_ID2        0x2263
#define FLASH_DEVICE_SAMSUNG_K5L5563_ID3        0x2260
#define FLASH_DEVICE_SAMSUNG_K5L5563            FLASH_DEVICE_SAMSUNG_K5L5563_ID1
#define FLASH_DEVICE_SAMSUNG_K5L2833            0x2402
#define FLASH_DEVICE_SAMSUNG_K5L5666            0x2206


/* NUMONYX device codes */
#define FLASH_DEVICE_NUMONYX_M58LR128KT         0x88c4
#define FLASH_DEVICE_NUMONYX_M58LR256KT         0x880d
#define FLASH_DEVICE_NUMONYX_M58LR128KC         0x882E

//DIDR,only use high 8 bits
#define FLASH_DEVICE_SUMSUNG_K5L2866_DIDR     0xC2
#define FLASH_DEVICE_SUMSUNG_K5L2833_DIDR     0xC1

/* MXIC device codes */
#define FLASH_DEVICE_MXIC_MX25L12805D         0x2018
#define FLASH_DEVICE_MXIC_MX25L1655D          0x2615
#define FLASH_DEVICE_MXIC_MX25L3255D          0x9E16
#define FLASH_DEVICE_MXIC_MX25L6455E          0x2617 
#define FLASH_DEVICE_MXIC_MX25L12855E         0x2618
#define FLASH_DEVICE_MXIC_MX25L3205D          0x2016
#define FLASH_DEVICE_MXIC_MX25L4006E          0x2013
#define FLASH_DEVICE_MXIC_MX25L6405D          0x2017
#define FLASH_DEVICE_MX25L1606E               0x2015
#define FLASH_DEVICE_MX25L12805D              0x2018
#define FLASH_DEVICE_MX25L3206E               0x2015
#define FLASH_DEVICE_MX25L8005                0x2014
#define FLASH_DEVICE_MX25L8006E               0x2014
#define FLASH_DEVICE_MX25L6406E               0x2017
#define FLASH_DEVICE_W25Q16                   0x4015
#define FLASH_DEVICE_W25Q80                   0x4014
#define FLASH_DEVICE_W25X32                   0x3016
#define FLASH_DEVICE_W25X40                   0x3013
#define FLASH_DEVICE_W25Q32                   0x4016
#define FLASH_DEVICE_W25X64                   0x3017
#define FLASH_DEVICE_W25X80                   0x3014
#define FLASH_DEVICE_W25Q64                   0x4017
#define FLASH_DEVICE_W25Q128                  0x4018
#define FLASH_DEVICE_AT25DF321A               0x4701
#define FLASH_DEVICE_AT26DF321                0x4700
#define FLASH_DEVICE_STM25P32                 0x2016
#define FLASH_DEVICE_EN25B32B                 0x2016
#define FLASH_DEVICE_EN25B64B                 0x2017
#define FLASH_DEVICE_EN25Q32A                 0x3016
#define FLASH_DEVICE_EN25Q64                  0x3017
#define FLASH_DEVICE_EN25Q128                 0x3018
#define FLASH_DEVICE_S25FL128P                0x2018
#define FLASH_DEVICE_S25FL008A                0x2013
#define FLASH_DEVICE_EN25F10                  0x3111
#define FLASH_DEVICE_EN25F16                  0x3115
#define FLASH_DEVICE_EN25F32                  0x3116
#define FLASH_DEVICE_EN25F40                  0x3113
#define FLASH_DEVICE_EN25F80                  0x3114
#define FLASH_DEVICE_EN25P16                  0x2015
#define FLASH_DEVICE_EN25QH16                 0x7015
#define FLASH_DEVICE_EN25QH18                 0x7018
#define FLASH_DEVICE_S25FL032P                0x0215
#define FLASH_DEVICE_S25FL064P                0x0216
#define FLASH_DEVICE_S25FL032K                0x4016
#define FLASH_DEVICE_PM25LQ032C               0x4615
#define FLASH_DEVICE_GD25Q32                  0x4016
#define FLASH_DEVICE_GD25Q16                  0x4015
#define FLASH_DEVICE_GD25S80                  0x4014
#define FLASH_DEVICE_GD25Q64                  0x4017
#define FLASH_DEVICE_GD25Q128                 0x4018
#define FLASH_DEVICE_MICRON_M25P16            0x2015
#define FLASH_DEVICE_MICRON_N25Q32            0xBA16
#define FLASH_DEVICE_MICRON_N25Q64            0xBA17
#define FLASH_DEVICE_MICRON_N25Q128           0xBA18
#define FLASH_DEVICE_NUMONYX_M25PX16          0x7315
#define FLASH_DEVICE_A25LM032                 0x3016




/*
 * How to use these codes in the descriptors:
 * the device identifier in the structures below
 * is a 32-bit integer in which the LSW is the device code
 * and the MSW the manufacturer code
 */

//	#define FLASH_DEVID(_Manufacturer_, _DeviceCode_)  (((_Manufacturer_)<<16)|(_DeviceCode_))

#define FLASH_DEVID_EXT(_Manufacturer_, DIDR ,_DeviceCode_)  (((DIDR&0xff)<<24)|((_Manufacturer_&0xff)<<16)|(_DeviceCode_&0xffff))

#endif //__DRV_FLASH_LOWL_ID_H__


