/**
 * \file audio_manager.c
 * \brief Flash Memory Services - Low level definitions - Definitions of MCP IDs
 *
 */



#ifndef __FMS_LOWL_ID_H__
#define __FMS_LOWL_ID_H__

/****************************************************************************/
/* ELECTRONIC SIGNATURES                                                    */
/****************************************************************************/

/* JEDEC Device manufacturers' IDs
 * More info on: http://www.jedec.org */

#define FMS_JEDEC_INTEL             0x89
#define FMS_JEDEC_AMD               0x01
#define FMS_JEDEC_TOSHIBA           0x98
#define FMS_JEDEC_ST                0x20
#define FMS_JEDEC_ATMEL             0x1F
#define FMS_JEDEC_MICRON            0x2C
#define FMS_JEDEC_MACRONIX          0xC2
#define FMS_JEDEC_SHARP             0xB0
#define FMS_JEDEC_SPANSION      0x01
#define FMS_JEDEC_SST               0xBF
#define FMS_JEDEC_SAMSUNG           0xEC
#define FMS_JEDEC_NUMONYX           0x20
//1222
#define FMS_JEDEC_EON           0x7F

#ifdef __SPI__
#define FMS_JEDEC_WINBOND           0xEF
#define FMS_JEDEC_EONSI             0x1C
#define FMS_JEDEC_GIGA              0xC8
#define FMS_JEDEC_ESMT              0x8C
#endif // __SPI__

/*
 * Device codes
 * (sorted by manufacturer)
 */

/* Intel devices codes */
#define FMS_DEVICE_INTEL_28F160C3           0x88C2
#define FMS_DEVICE_INTEL_28F320C3           0x88C4
#define FMS_DEVICE_INTEL_28F320W18          0x8862
#define FMS_DEVICE_INTEL_28F640W18          0x8864
#define FMS_DEVICE_INTEL_28F128L18B          0x880F
#define FMS_DEVICE_INTEL_28F128L18T          0x880C

/* Micron device codes */
#define FMS_DEVICE_MICRON_MT28C3224P        0x44B4
#define FMS_DEVICE_MICRON_MT28C64416W18A    0x44C6


/* Toshiba devices codes */
#define FMS_DEVICE_TOSHIBA_TH50VSF1480AASB  0x00C2
#define FMS_DEVICE_TOSHIBA_TH50VSF1480ABSB  0x00C2
#define FMS_DEVICE_TOSHIBA_TH50VSF2480AASB  0x0098
#define FMS_DEVICE_TOSHIBA_TH50VSF2582BESBb 0x00C5
#define FMS_DEVICE_TOSHIBA_TH50VSF2582BESB  0x00C6
#define FMS_DEVICE_TOSHIBA_TH50VSF2682BFSB  0x0057
/*#define FMS_DEVICE_TOSHIBA_TH50VSF3682AFSB			0x0057*/ /* 64/4 = 64/8 */
#define FMS_DEVICE_TOSHIBA_TH50YSF2582BFSB  0x0059
#define FMS_DEVICE_TOSHIBA_TH50YSF3682AFSB  0x007A
#define FMS_DEVICE_TOSHIBA_TVO0579002AABD   0x001B // top boot block
#define FMS_DEVICE_TOSHIBA_TVO0579003AABD   0x001D // bottom boot block
#define FMS_DEVICE_TOSHIBA_TVO067A002CGAD   0x0049 // top boot block
#define FMS_DEVICE_TOSHIBA_TVO067A003CGAD   0x004A // bottom boot block
#define FMS_DEVICE_TOSHIBA_TVO057A002EAGD   0x0049 // top boot block
#define FMS_DEVICE_TOSHIBA_TV00570002CDGB   0x0003 // top boot block
#define FMS_DEVICE_TOSHIBA_TV00570002ARGQ   0x005F // top boot block
#define FMS_DEVICE_TOSHIBA_TY00680002ADGB   0x006F // top boot block

/* ST devices codes */
#define FMS_DEVICE_ST_M36W216T              0x88CE
#define FMS_DEVICE_ST_M36W432T              0x88BA
#define FMS_DEVICE_ST_M36DR432A             0x00A0
#define FMS_DEVICE_ST_M36W864TE             0x8848
#define FMS_DEVICE_ST_M36DR864TB            0x8810
#define FMS_DEVICE_ST_M30W0R7000T           0x881E
#define FMS_DEVICE_ST_M58WR032FT            0x8814

/* AMD devices codes */
#define FMS_DEVICE_AMD_AM29LV640MU          0x227E

/* SPANSION devices codes */
// Read cycle1
#define FMS_DEVICE_SPANSION_ID1			        0x227E
// Read cycle2
#define FMS_DEVICE_SPANSION_S71WS128JC0          0x2218

#define FMS_DEVICE_SPANSION_S71WS512P_ID2             0x223D
#define FMS_DEVICE_SPANSION_S71WS256P_ID2             0x2242
#define FMS_DEVICE_SPANSION_S71WS128P_ID2            0x2244

#define FMS_DEVICE_SPANSION_S71PL127NB0_ID2          0x2220
#define FMS_DEVICE_SPANSION_S71PL129NB0_ID2          0x2221
#define FMS_DEVICE_SPANSION_S71PL256NB0_ID2          0x223C

#define FMS_DEVICE_SPANSION_S71GL128NB0_ID2          0x2221
#define FMS_DEVICE_SPANSION_S71GL256NB0_ID2          0x2222
#define FMS_DEVICE_SPANSION_S71GL512NB0_ID2          0x2223

// Read cycle3
#define FMS_DEVICE_SPANSION_WS_ID3                      0x2200
#define FMS_DEVICE_SPANSION_PL_ID3                      0x2200
#define FMS_DEVICE_SPANSION_GL_ID3                      0x2201



// (FMS_DEVICE_SPANSION_XXX_ID2 & 0xFF << 8) | (FMS_DEVICE_SPANSION_PL_ID3 &0xFF)
#define FMS_DEVICE_SPANSION_S71PL127NB0          0x2000
#define FMS_DEVICE_SPANSION_S71PL129NB0          0x2100
#define FMS_DEVICE_SPANSION_S71PL256NB0          0x3C00

// (FMS_DEVICE_SPANSION_XXX_ID2 & 0xFF << 8) | (FMS_DEVICE_SPANSION_GL_ID3 &0xFF)
#define FMS_DEVICE_SPANSION_S71GL128NB0          0x2101
#define FMS_DEVICE_SPANSION_S71GL256NB0          0x2201
#define FMS_DEVICE_SPANSION_S71GL512NB0          0x2301

// (FMS_DEVICE_SPANSION_XXX_ID2 & 0xFF << 8) | (FMS_DEVICE_SPANSION_PL_ID3 &0xFF)
#define FMS_DEVICE_SPANSION_S71WS512P          0x3D00
#define FMS_DEVICE_SPANSION_S71WS256P          0x4200
#define FMS_DEVICE_SPANSION_S71WS128P          0x4400



/* ATMEL device codes */
#define FMS_DEVICE_ATMEL_AT52SC1283J            0x00BB

/* Atmel devices codes */
#define FMS_DEVICE_ATMEL_AT52BR3224AT       0x00C9
#define FMS_DEVICE_ATMEL_AT52BR1664AT       0x00C2

/* SST device codes */
#define FMS_DEVICE_SST_36VF1601             0x734B
#define FMS_DEVICE_SST_36VF1602             0x734A

/* SUMSUNG device codes */
#define FMS_DEVICE_SUMSUNG_K5L2731           0x257E
#define FMS_DEVICE_SUMSUNG_K5L2731_ID2       0x2508
#define FMS_DEVICE_SUMSUNG_K5L2731_ID3       0x2501


/* SUMSUNG device codes */
#define FMS_DEVICE_SUMSUNG_K5L5563_ID1		 0x227E
#define FMS_DEVICE_SUMSUNG_K5L5563_ID2		 0x2263
#define FMS_DEVICE_SUMSUNG_K5L5563_ID3	     0x2260

#define FMS_DEVICE_SUMSUNG_K5L5563			 FMS_DEVICE_SUMSUNG_K5L5563_ID1 //(((FMS_DEVICE_SAMSUNG_K5L5563_ID2 & 0xFF) << 8) | (FMS_DEVICE_SAMSUNG_K5L5563_ID3 & 0xFF))

#define FMS_DEVICE_SAMSUNG_K5L2833		 0x2402
#define FMS_DEVICE_SUMSUNG_K5L5666	     0x2206

/* NUMONYX device codes */
#define FMS_DEVICE_NUMONYX_M58LR128KT    0x88c4
#define FMS_DEVICE_NUMONYX_M58LR256KT    0x880d
#define FMS_DEVICE_NUMONYX_M58LR128KC    0x882E

#ifdef __SPI__
/* MICRON device codes */
#define FMS_DEVICE_MICRON_N25W064A11E	 0xCB17
#define FMS_DEVICE_MICRON_N25W128A11E	 0xCB18

/* Winbond device codes */
#define FMS_DEVICE_WINBOND_W25Q64CV      0x4017
#define FMS_DEVICE_WINBOND_W25Q64DW      0x6017
#define FMS_DEVICE_WINBOND_W25Q128BV     0x4018

/* MACRONIX device codes */
#define FMS_DEVICE_MACRONIX_MX25U6435E   0x2537
#define FMS_DEVICE_MACRONIX_MX25U6435F   0x2537
#define FMS_DEVICE_MACRONIX_MX25U12835F  0x2538
#define FMS_DEVICE_MACRONIX_MX25L12833E  0x2018

/* EONSI device codes */
#define FMS_DEVICE_EONSI_EN25S64   	     0x3817

/* GigaDevice device codes */
#define FMS_DEVICE_GIGA_GD25LQ64   	     0x6017
#define FMS_DEVICE_GIGA_GD25LQ128   	 0x6018

/* EMST device codes */
#define FMS_DEVICE_ESMT_F25L64QA   	     0x4117
#endif // __SPI__

/*
 * How to use these codes in the descriptors:
 * the device identifier in the structures below
 * is a 32-bit integer in which the LSW is the device code
 * and the MSW the manufacturer code
 */

#define FMS_DEVID(_Manufacturer_, _DeviceCode_)  (((_Manufacturer_)<<16)|(_DeviceCode_))

#endif /* __FMS_LOWL_ID_H__ not defined   */


