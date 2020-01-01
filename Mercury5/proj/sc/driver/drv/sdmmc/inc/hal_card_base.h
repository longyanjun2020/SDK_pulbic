/***************************************************************************************************************
 *
 * FileName hal_card_base.h
 *     @author jeremy.wang (2015/05/29)
 * Desc:
 *     This header file is independent.
 *     We could put different hal_card_base.h in different build code folder but the same name.
 *     We want to distinguish between this and others settings but the same project.
 *     Specific define is freedom for each project, but we need to put it at inner code of project define.
 *
 *     For Base Setting:
 *     (1) BASE Project/OS/CPU/FCIE/Ver.. Option Type Define
 *     (2) BASE Type Define
 *     (3) BASE IP Type Define
 *     (4) BASE SD Logic Type Define
 *     (5) BASE OS/CPU define and Include Files for Different OS/CPU
 *     (6) BASE Debug System
 *
 *     P.S. D_XX for define and D_XX__ two under line("__") to distinguish define and its define option.
 *
 ***************************************************************************************************************/

#ifndef __HAL_CARD_BASE_H
#define __HAL_CARD_BASE_H

//***********************************************************************************************************
// (1) BASE Project/OS/CPU/FCIE/ICVer.. Option Type Define
//***********************************************************************************************************

// Project Option Type Define
//-----------------------------------------------------------------------------------------------------------
#define D_PROJECT__iNF        1
#define D_PROJECT__iNF3       2
#define D_PROJECT__MV5        3

// OS Type Option
//-----------------------------------------------------------------------------------------------------------
#define D_OS__LINUX       1
#define D_OS__UBOOT       2
#define D_OS__WINCE       3
#define D_OS__EBOOT       4
#define D_OS__MBOOT       5
#define D_OS__YBOX        6
#define D_OS__ROM1        7    //
#define D_OS__RTK         8
#define D_OS__NONE        9

// CPU Type Option
//-----------------------------------------------------------------------------------------------------------
#define D_CPU__ARM        1
#define D_CPU__MIPS       2

// FCIE Type Major Version
//-----------------------------------------------------------------------------------------------------------
#define D_FCIE_M_VER__04        1
#define D_FCIE_M_VER__05        2

// FCIE Type Revision Version
//-----------------------------------------------------------------------------------------------------------
#define D_FCIE_R_VER__00        0
#define D_FCIE_R_VER__01        1
#define D_FCIE_R_VER__02        2
#define D_FCIE_R_VER__03        3
#define D_FCIE_R_VER__04        4
#define D_FCIE_R_VER__05        5

// BOARD Type Version
//-----------------------------------------------------------------------------------------------------------
#define D_BOARD_VER__00         0
#define D_BOARD_VER__01         1
#define D_BOARD_VER__02         2
#define D_BOARD_VER__03         3
#define D_BOARD_VER__04         4
#define D_BOARD_VER__05         5

// IC Version Option
//-----------------------------------------------------------------------------------------------------------
#define D_ICVER__00      0
#define D_ICVER__01      1
#define D_ICVER__02      2
#define D_ICVER__03      3
#define D_ICVER__04      4
#define D_ICVER__05      5
#define D_ICVER__06      6
#define D_ICVER__07      7
#define D_ICVER__08      8
#define D_ICVER__09      9


//***********************************************************************************************************
// (2) BASE Type Define
//***********************************************************************************************************
typedef unsigned char      U8_T;
typedef unsigned short     U16_T;
typedef unsigned int       U32_T;
typedef unsigned long long U64_T;
typedef signed char        S8_T;
typedef signed short       S16_T;
typedef signed int         S32_T;
typedef signed long long   S64_T;
typedef unsigned char      BOOL_T;

#define FALSE   0
#define TRUE    1

#define BIT00_T 0x0001
#define BIT01_T 0x0002
#define BIT02_T 0x0004
#define BIT03_T 0x0008
#define BIT04_T 0x0010
#define BIT05_T 0x0020
#define BIT06_T 0x0040
#define BIT07_T 0x0080
#define BIT08_T 0x0100
#define BIT09_T 0x0200
#define BIT10_T 0x0400
#define BIT11_T 0x0800
#define BIT12_T 0x1000
#define BIT13_T 0x2000
#define BIT14_T 0x4000
#define BIT15_T 0x8000
#define BIT16_T 0x00010000
#define BIT17_T 0x00020000
#define BIT18_T 0x00040000
#define BIT19_T 0x00080000
#define BIT20_T 0x00100000
#define BIT21_T 0x00200000
#define BIT22_T 0x00400000
#define BIT23_T 0x00800000
#define BIT24_T 0x01000000
#define BIT25_T 0x02000000
#define BIT26_T 0x04000000
#define BIT27_T 0x08000000
#define BIT28_T 0x10000000
#define BIT29_T 0x20000000
#define BIT30_T 0x40000000
#define BIT31_T 0x80000000


//***********************************************************************************************************
// (3) BASE IP Type Define
//***********************************************************************************************************

typedef enum
{
    EV_IP_FCIE1     = 0,
    EV_IP_FCIE2     = 1,
    EV_IP_FCIE3     = 2,

} IPEmType;


typedef enum
{
    EV_PORT_SD      = 0,
    EV_PORT_SDIO1   = 1,
    EV_PORT_SDIO2   = 2,
    EV_PFCIE5_FCIE  = 3,   //Use Port Setting for FCIE5 Function Ctrl Setting
    EV_PFCIE5_SDIO  = 4,   //Use Port Setting for FCIE5 Function Ctrl Setting

} PortEmType;

typedef enum
{
    EV_PAD1         = 0,
    EV_PAD2         = 1,
    EV_PAD3         = 2,

} PADEmType;


//***********************************************************************************************************
// (4) BASE SD Logic Type Define
//***********************************************************************************************************


/*  For Reference Define
#define DEF_SPEED_BUS_SPEED         0
#define UHS_SDR12_BUS_SPEED         0
#define HIGH_SPEED_BUS_SPEED        1
#define UHS_SDR25_BUS_SPEED         1
#define UHS_SDR50_BUS_SPEED         2
#define UHS_SDR104_BUS_SPEED        3
#define UHS_DDR50_BUS_SPEED         4

#define SD_MODE_HIGH_SPEED  (1 << HIGH_SPEED_BUS_SPEED)
#define SD_MODE_UHS_SDR12   (1 << UHS_SDR12_BUS_SPEED)
#define SD_MODE_UHS_SDR25   (1 << UHS_SDR25_BUS_SPEED)
#define SD_MODE_UHS_SDR50   (1 << UHS_SDR50_BUS_SPEED)
#define SD_MODE_UHS_SDR104  (1 << UHS_SDR104_BUS_SPEED)
#define SD_MODE_UHS_DDR50   (1 << UHS_DDR50_BUS_SPEED)
*/

typedef enum
{
    EV_BUS_LOW            = 0,
    EV_BUS_DEF_SDR12      = 1,
    EV_BUS_HS_SDR25       = (1<<1),  //
    EV_BUS_SDR50          = (1<<2),  //1<<(2)UHS_SDR50_BUS_SPEED
    EV_BUS_SDR104_HS200   = (1<<3),  //1<<(3)UHS_SDR104_BUS_SPEED
    EV_BUS_DDR50          = (1<<4),  //1<<(4)UHS_DDR50_BUS_SPEED


} BusTimingEmType;


typedef enum
{
    EV_OK   = 0,
    EV_FAIL = 1,

} RetEmType;


//***********************************************************************************************************
//(5) Specific Project/OS/CPU define and Include Files for Different OS/CPU
//***********************************************************************************************************

//###########################################################################################################
#define D_PROJECT           D_PROJECT__MV5
#define D_FCIEVER           D_FCIEVER__05
//###########################################################################################################


#define D_OS                D_OS__RTK
#define D_CPU               D_CPU__ARM
#define D_FCIE_M_VER        D_FCIE_M_VER__05

#define D_FPGA_TEST         (FALSE)


//###########################################################################################################
#if (D_OS == D_OS__LINUX)
//###########################################################################################################
#include <linux/kernel.h>
//###########################################################################################################
#elif (D_OS == D_OS__UBOOT)
//###########################################################################################################
#include <common.h>
//###########################################################################################################
#elif (D_OS == D_OS__ROM1)
//###########################################################################################################
#include <drvUART.h>
//###########################################################################################################
#elif (D_OS == D_OS__RTK)
//###########################################################################################################
#include "sys_sys_isw_uart.h"
//###########################################################################################################
#endif
//###########################################################################################################


//***********************************************************************************************************
// (6) BASE Debug System
//***********************************************************************************************************

//###########################################################################################################
#if (D_OS == D_OS__LINUX)
//###########################################################################################################
#define prtstring(s)    printk(s)
#define prtUInt(v)      printk("%u", v)
#define prtU8(v)        printk("%u", v)
#define prtU8Hex(v)     printk("0x%02X", v)
#define prtU16Hex(v)    printk("0x%04X", v)
#define prtU32Hex(v)    printk("0x%08X", v)
//###########################################################################################################
#elif (D_OS == D_OS__UBOOT) || (D_OS == D_OS__MBOOT)
//###########################################################################################################
#define prtstring(s)    printf(s)
#define prtUInt(v)      printf("%u", v)
#define prtU8(v)        printf("%u", v)
#define prtU8Hex(v)     printf("0x%02X", v)
#define prtU16Hex(v)    printf("0x%04X", v)
#define prtU32Hex(v)    printf("0x%08X", v)
//###########################################################################################################
#elif (D_OS == D_OS__ROM1)
//###########################################################################################################
#define prtstring(s)    uart_write_string((unsigned char*)s)
#define prtCH(c)        uart_write_byte(c)
#define prtUInt(v)      { prtstring("0x");  uart_write_U32_hex(v); }
#define prtU8(v)        { prtstring("0x");  uart_write_U8_hex(v); }
#define prtU16(v)       { prtstring("0x");  uart_write_U16_hex(v); }
#define prtU8Hex(v)     { prtstring("0x");  uart_write_U8_hex(v); }
#define prtU16Hex(v)    { prtstring("0x");  uart_write_U16_hex(v); }
#define prtU32Hex(v)    { prtstring("0x");  uart_write_U32_hex(v); }
//###########################################################################################################
#elif (D_OS == D_OS__RTK)
//###########################################################################################################
#define prtstring(s)    UartSendTrace(s)
#define prtCH(c)        UartSendTrace("%c", c)
#define prtUInt(v)      UartSendTrace("%u", v)
#define prtU8(v)        UartSendTrace("%u", v)
#define prtU16(v)       UartSendTrace("%u", v)
#define prtU8Hex(v)     UartSendTrace("0x%02X", v)
#define prtU16Hex(v)    UartSendTrace("0x%04X", v)
#define prtU32Hex(v)    UartSendTrace("0x%08X", v)
//###########################################################################################################
#elif (D_OS == D_OS__YBOX)
//###########################################################################################################
#define prtstring(s)    printf(s)
#define prtCH(c)        printf("%c", c)
#define prtUInt(v)      printf("%u", v)
#define prtU8(v)        printf("%u", v)
#define prtU16(v)       printf("%u", v)
#define prtU8Hex(v)     printf("0x%02X", v)
#define prtU16Hex(v)    printf("0x%04X", v)
#define prtU32Hex(v)    printf("0x%08X", v)
//###########################################################################################################
#else
//###########################################################################################################
#define prtstring(s)    printf(s)
#define prtUInt(v)      printf("%u", v)
#define prtU8(v)        printf("0x%02X", v)
#define prtU8Hex(v)     printf("0x%02X", v)
#define prtU16Hex(v)    printf("0x%04X", v)
#define prtU32Hex(v)    printf("0x%08X", v)
//###########################################################################################################
#endif
//###########################################################################################################


#endif //End of __HAL_CARD_BASE_H