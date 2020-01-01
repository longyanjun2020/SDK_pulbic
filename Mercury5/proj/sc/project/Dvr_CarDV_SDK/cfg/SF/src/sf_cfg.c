//==============================================================================
//
//  File        : sf_cfg.c
//  Description : SPI Nor Flash configure file
//  Author      : Rony Yeh
//  Revision    : 1.0
//==============================================================================

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================
#include "config_fw.h"
#if defined(__GNUC__)
#include "vm_types.ht"
#endif
#if (USING_SF_IF)
#include "AIT_Init.h"
#include "sf_cfg.h"
#include "mmpf_sf.h"

//==============================================================================
//
//                              SPI NOR Flash Parameter assignment
//
//==============================================================================

SPI_NOR_PROFILE SPINORConfigMatrix[SPIMAXMODULENO] = {

#if (SPI_NorFlash_DefaultSetting) //The array member must be leave for Default Setting
{
    0xFFFFFFFF,    // DeviceID   SPI_NorFlash_DefaultSetting
    0x400000,	   // TotalSize	256Mb 32MB
    66000,		   //parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor//CZ patch...20160204
    0x1000,		   // 4K for each Sector
    0x8000,		   // 32K for each Block

    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    2,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x10,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif

#if (SPI_NorFlash_WINBOND_25Q32)
{
    0x00EF4016,    // DeviceID   WINBOND_25Q32
    0x400000,     // TotalSize - 4MB CarDV
    66000,         // parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor
    0x1000,        // 4K for each Sector
    0x8000,        // 32K for each Block

    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    3,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x02,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif

#if (SPI_NorFlash_WINBOND_25Q64)
{
    0x00EF4017,    // DeviceID   WINBOND_25Q64
    0x800000,     // TotalSize - 8MB CarDV
    66000,         // parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor//CZ patch...20160204
    0x1000,        // 4K for each Sector
    0x8000,        // 32K for each Block

    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    3,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x02,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif

#if (SPI_NorFlash_WINBOND_25Q128)
{
    0x00EF4018,    // DeviceID   WINBOND_25Q128
    0x1000000,     // TotalSize - 16MB
    66000,         // parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor
    0x1000,        // 4K for each Sector
    0x8000,        // 32K for each Block

    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    3,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x02,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x04, 0x00, 0x00,    // Protect 128K = 4 x 32K; [0:0:1:1]/[BP3:BP2:BP1:BP0] ->WPS=0; CMP=0
    0xFC, 0x02, 0x04,    // [B6:B5:B4:B2]/[SEC:TB:BP2:BP0] -> Default-> WPS=1; CMP=0

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif

#if (SPI_NorFlash_WINBOND_25Q256FV)
{
    0x00EF4019,    // DeviceID   WINBOND_25Q256FV
    0x2000000,     // TotalSize - 32MB
    66000,         // parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor
    0x1000,        // 4K for each Sector
    0x8000,        // 32K for each Block

    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    3,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x02,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
},
#endif

#if (SPI_NorFlash_WINBOND_25X10)
{
    0x0084B5C3,    // DeviceID   WINBOND_25X10
    0x200000,      // TotalSize
    66000,         // parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor
    0x1000,        // 4K for each Sector
    0x8000,        // 32K for each Block

    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    3,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x02,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif

#if (SPI_NorFlash_MXIC_25L512)
{
    0x009ACF4A,    // DeviceID   MXIC_25L512
    0x100000,      // TotalSize
    66000,         // parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor
    0x1000,        // 4K for each Sector
    0x8000,        // 32K for each Block
    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write parameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    3,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x02,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif   // #if (SPI_NorFlash_WINBOND_25Q128)

#if (SPI_NorFlash_MXIC_25L12835F)
{
    0x00C22018,    // DeviceID   MXIC_25L12835F
    0x1000000,	   // TotalSize
    66000,		   //parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor
    0x1000,		   // 4K for each Sector
    0x8000,		   // 32K for each Block

    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    3,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x20,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x0C, 0x00, 0x00,    // Protect 128K = 4 x 32K; [0:0:1:1]/[BP3:BP2:BP1:BP0]
    0x3C, 0x00, 0x00,    // [B5:B2]/[BP3:BP0] -> T/B bit default is 0

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    0x13,                // Command for read data <4 Byte Address>
    0x0C,                // Command for fast read data <4 Byte Address>
    0x3C,                // Command for Dual fast read data <4 Byte Address>
    0x12,                // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    0x21,	             // Command for Erase Sector <4 Byte Address>
    0x2B,                // Command for Read Security register
},
#endif   // #if (SPI_NorFlash_MXIC_25L12835F)

#if (SPI_NorFlash_KH25L12835F)
{
    0x00C22018,    // DeviceID  KHIC_25L12835F
    0x1000000,	   // TotalSize
    33000,		   //parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor
    0x1000,		   // 4K for each Sector
    0x8000,//,	  // 32K for each Block

    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    3,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x20,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD

    0x03,                // Command for read data <3 Byte Address>
    0x0B,                // Command for fast read data <3 Byte Address>
    0x3B,                // Command for Dual fast read data <3 Byte Address>
    0x02,                // Command for write data <3 Byte Address>
    0x13,                // Command for read data <4 Byte Address>
    0x0C,                // Command for fast read data <4 Byte Address>
    0x3C,                // Command for Dual fast read data <4 Byte Address>
    0x12,                // Command for write data <4 Byte Address>
    0x20,                // Command for Erase Sector <3 Byte Address>
    0x20,	             // Command for Erase Sector <4 Byte Address>
    0x2B,                // Command for Read Security register
},
#endif   // #if (SPI_NorFlash_KH25L12835F)

#if (SPI_NorFlash_GD_25Q64B)
{
    0x00C84017,    // DeviceID   GD_25Q64B
    0x800000,      // TotalSize
    66000,         //parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor//CZ patch...20160204
    0x1000,        // 4K for each Sector
    0x8000,        // 32K for each Block

    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    2,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x10,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif   // #if (SPI_NorFlash_WINBOND_25Q128)

#if (SPI_NorFlash_GD_25Q128B)
{
    0x00C84018,    // DeviceID
    0x1000000,     // TotalSize
    66000,         // parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor
    0x1000,        // 4K for each Sector
    0x8000,        // 32K for each Block

    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    2,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x10,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x04, 0x00, 0x00,    // Prot 128K = 4 x 32K; [0:0:0:0:1]/[BP4:BP3:BP2:BP1:BP0]  -> WPS=0; CMP=0
    0x7C, 0x02, 0x04,    // [B6:B2]/[BP4:BP0] -> Default-> WPS=1; CMP=0

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif

#if (SPI_NorFlash_KH25L3233F)
{
    0xC22016,      // DeviceID, conflict with SPI_NorFlash_MXIC_25L3206
    0x00400000,    // TotalSize - 4MB
    66000,         // parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor
    0x1000,        // 4K for each Sector
    0x8000,        // 32K for each Block

    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    2,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x10,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif

#if (SPI_NorFlash_MXIC_25L3206)
{
    0xC22016,      // DeviceID, conflict with SPI_NorFlash_KH25L3233F
    0x00400000,    // TotalSize - 4MB
    66000,         // parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor
    0x1000,        // 4K for each Sector
    0x10000,       // 64K for each Block

    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    2,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x10,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif

#if (SPI_NorFlash_MXIC_25L6406E)
{
    0xC22017,      // DeviceID
    0x00800000,    // TotalSize - 8MB
    66000,         // parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor
    0x1000,        // 4K for each Sector
    0x10000,       // 64K for each Block

    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    2,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x10,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif

#if (SPI_NorFlash_ESMT_64L)
{
    0x8C4117,      // DeviceID
    0x00800000,    // TotalSize - 8MB
    66000,         // parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor
    0x1000,        // 4K for each Sector
    0x8000,        // 32K for each Block

    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    2,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x10,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif

#if (SPI_NorFlash_EN25Q32A)
{
    0x1C3016,      // DeviceID
    0x00400000,    // TotalSize - 4MB
    66000,         // parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor
    0x1000,        // 4K for each Sector
    0x8000,        // 32K for each Block

    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    2,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x10,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif

#if (SPI_NorFlash_EN25Q128A)
{
    0x1C7018,      // DeviceID
    0x01000000,    // TotalSize - 16MB
    66000,         // parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor
    0x1000,        // 4K for each Sector
    0x8000,        // 32K for each Block

    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    2,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x10,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif

#if (SPI_NorFlash_IC25LP64)
{
    0x9D6017,      // DeviceID
    0x00800000,    // TotalSize - 8MB
    33000,         // parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor
    0x1000,        // 4K for each Sector
    0x8000,        // 32K for each Block
    0,             // Capability to support Quad SPI read
    0,             // Capability to support Dual SPI read
    0,             // Capability to support Quad SPI write
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address parameter
    0,             // Support AAI-Write parameter
    2,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x10,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif

#if (SPI_NorFlash_IC25LP128)
{
    0x9D6018,      // DeviceID
    0x01000000,    // TotalSize - 16MB
    33000,         // parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor
    0x1000,        // 4K for each Sector
    0x8000,        // 32K for each Block
    0,             // Capability to support Quad SPI read
    0,             // Capability to support Dual SPI read
    0,             // Capability to support Quad SPI write
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address parameter
    0,             // Support AAI-Write parameter
    2,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x10,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif
#if (SPI_NorFlash_XM25QH64A)
{
    0x00207017,    // DeviceID
    0x800000,      // TotalSize
    66000,         //parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor//CZ patch...20160204
    0x1000,        // 4K for each Sector
    0x8000,        // 32K for each Block

    0,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    2,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x10,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif   // #if (SPI_NorFlash_WINBOND_25Q128)
#if (SPI_NorFlash_MXIC_25L25645G)
{
    0x00C22019,    // DeviceID
    0x2000000,	   // TotalSize 32MB
    66000,		   //parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor
    0x1000,		   // 4K for each Sector
    0x8000,		   // 32K for each Block

    1,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    3,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>
    0x20,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x0C, 0x00, 0x00,    // Protect 128K = 4 x 32K; [0:0:1:1]/[BP3:BP2:BP1:BP0]
    0x3C, 0x00, 0x00,    // [B5:B2]/[BP3:BP0] -> T/B bit default is 0

    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    0x13,                // Command for read data <4 Byte Address>
    0x0C,                // Command for fast read data <4 Byte Address>
    0x3C,                // Command for Dual fast read data <4 Byte Address>
    0x12,                // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    0x21,	             // Command for Erase Sector <4 Byte Address>
    0x2B,                // Command for Read Security register
},
#endif   // #if (SPI_NorFlash_MXIC_25L25645G)

#if (SPI_NorFlash_ESEE_F25F64A)
{   
    0x00A14017,    // DeviceID   
    0x800000,      // TotalSize
    66000,         //parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor//CZ patch...20160204
    0x1000,        // 4K for each Sector
    0x8000,        // 32K for each Block    

    0,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter 	
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    2,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>	
    0x10,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD
    
    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif


#if (SPI_NorFlash_XTX_F25F64A)
{   
    0x000B4017,    // DeviceID   
    0x800000,      // TotalSize
    66000,         //parameter to create <ulSifClkDiv> EX: ulSifClkDiv = (ulG0Freq+32999)/SIFCLKDividor//CZ patch...20160204
    0x1000,        // 4K for each Sector
    0x8000,        // 32K for each Block    

    0,             // Capability to support Dual SPI read
    0,             // option to seepdup write volatile SR process
    0,             // 4 bytes address mode enable/disable
    0,             // Support AAI-Write prrameter 	
    0,             // Clear Status Register<Command 30h> in the reset API;(0)Not ClearSR (1)ClearSR,make sure module support capability before assigning
    0,             // Execute/NotExecute ADP mode setting,some module don't support this function<ex:MXIC>;(0)Not Execute ADP , (1)Execute ADP
    2,			   // Status Register Group Index to Enable/Disable <ADP function> for 4 Byte Address mode, group1<0x05> group2<0x35> group3<0x15>	
    0x10,		   // Status Register Bit Number to Enable/Disable <ADP function> for 4 Byte Address mode,EX: bit4=0x10,bit5=0x20
    0x00, 0x00, 0x00,    // TBD
    0x00, 0x00, 0x00,    // TBD
    
    READ_DATA,           // Command for read data <3 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <3 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <3 Byte Address>
    PAGE_PROGRAM,        // Command for write data <3 Byte Address>
    READ_DATA,           // Command for read data <4 Byte Address>
    FAST_READ_DATA,      // Command for fast read data <4 Byte Address>
    DUAL_FAST_READ_DATA, // Command for Dual fast read data <4 Byte Address>
    PAGE_PROGRAM,        // Command for write data <4 Byte Address>
    SECTOR_ERASE,        // Command for Erase Sector <3 Byte Address>
    SECTOR_ERASE,	     // Command for Erase Sector <4 Byte Address>
    READ_SECURITY_REG,   // Command for Read Security register
},
#endif

};

int SF_Module_Init(void)
{
    MMP_ULONG dev = 0;

    for(dev = 0; dev < SPIMAXMODULENO; dev++) {
        MMPF_SF_Register( (MMP_UBYTE)dev, &SPINORConfigMatrix[dev] );
    }

    return 0;
}
#if defined(__GNUC__)
__section__(initcall6)
#else //#if defined(__GNUC__)
#pragma arm section code = "initcall6", rodata = "initcall6", rwdata = "initcall6",  zidata = "initcall6"
#pragma O0
#endif
ait_module_init(SF_Module_Init);
#if defined(__GNUC__)
//NOP
#else //#if defined(__GNUC__)
#pragma
#pragma arm section rodata, rwdata, zidata
#endif
#endif   // #if (USING_SF_IF)

