///////////////////////////////////////////////////////////////////////////////////////////////////
/// file drvSDMMC.h
/// @brief SD/MMC driver
/// @author MStar Semiconductor Inc.
///
/// Read/Write SD/MMC data
///
/// Features:
/// - support SD/MMC
///////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SDMMC_H
#define _SDMMC_H

#include "drv_stg_err_code.h"
#include "drv_stg_platform.h"


/*--------------------------------------------------------------------
                            GENERAL INCLUDES
--------------------------------------------------------------------*/


/*--------------------------------------------------------------------
                            LITERAL CONSTANTS
--------------------------------------------------------------------*/


//================================================
//	Error Code
//================================================

typedef struct _REG_OCR
{
    U8 BIT_31_24;
    U8 BIT_23_16;
    U8 BIT_15_08;
    U8 BIT_07_00;

} REG_OCR; // ACMD41 oper cond R3

typedef struct _REG_CID
{
    U8 BIT_31_24;
    U8 BIT_23_16;
    U8 BIT_15_08;
    U8 BIT_07_00;

} REG_CID; // CMD02 all send CID R2

typedef union _RSP_R6
{
    U8 BYTE[6];

    ARMCC_PACKED struct
    {
        U8  CommandIdx;
        U16 RCA;
        U16 CardStatus;
        U8  CRC;
    } GCC_PACKED R6;

} RSP_R6; // CMD03 send relative card addr

typedef union _RSP_R2_CSD
{
    U8 BYTE[17];

    ARMCC_PACKED struct
    {
        U8  RESEV_3F;
        U8  CSD_STRUCT;
        U8  TAAC;
        U8  NSAC;
        U8  TRAN_SPEED; // 0x32 or 0x5A
        U8  CCC;
        U8  READ_BL_LEN; // include part of CCC
        U16 C_SIZE;
        U8  C_SIZE2;
        U16 C_SIZE_MULT;
        // . . .
        U8  CRC;
    } GCC_PACKED V_1P0;

    ARMCC_PACKED struct
    {
        U8  RESEV_3F;
        U8  CSD_STRUCT;
        U8  TAAC;
        U8  NSAC;
        U8  TRAN_SPEED; // the same as CSD v1.0
        U16 READ_BL_LEN;
        U32 C_SIZE; // need mask 0x003FFFFF
        // . . .
        U8  CRC;
    } GCC_PACKED V_2P0;

} RSP_R2_CSD; // CMD09 send CSD

typedef enum
{
    STATE_STAND_BY,
    STATE_TRANSFER,
    STATE_SENDING_DATA, // R ...
    STATE_RECEIVE_DATA, // W ...
    STATE_PROGRAMMING,  // W
    STATE_DISCONNECT,

} SD_STATE_IN_DATA_TRAN_MODE;

typedef struct
{
    BURST_MODE_SW eBurstModeSwitch;
    SD_STATE_IN_DATA_TRAN_MODE eSdState;
    U32 NextSector4BurstMode;

} BURST_MODE_DATA;


//================================================
//	ChgSDMMCState return valye
//================================================

RW_STATUS DrvSD_Init(U8 u8Disk);
RW_STATUS DrvSd_ReadWrite(U8 u8Disk, RW_PRMETR *RwParam);
WP_STATUS _DrvSDMMC_GetWriteProtectState(U8 u8Disk);
U8 MDrvSdPowerDown(U8 u8Disk);
U8 Drv_DoDataCompare(U8 u8Disk, RW_PRMETR *RwParam, U32 u32MemAddr);
void DrvSdDumpCIFD(U8 u8Disk);
void DumpSectorMem(U32 length);
U8              DrvBurstModeSet(U8 u8Disk, BURST_MODE_SW BurstModeSwitch);
BURST_MODE_SW   DrvBurstModeGet(U8 u8Disk);

/*--------------------------------------------------------------------
                                 TYPES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                            MEMORY CONSTANTS
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                               VARIABLES
--------------------------------------------------------------------*/

/*--------------------------------------------------------------------
                                MACROS
--------------------------------------------------------------------*/


/*--------------------------------------------------------------------
                              	PROCEDURES
--------------------------------------------------------------------*/

#endif // _SDMMC_H

