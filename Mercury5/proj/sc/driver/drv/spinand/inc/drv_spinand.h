
//<MStar Software>


#ifndef _DRV_SPINAND_H_
#define _DRV_SPINAND_H_
#include "drv_spinand_common.h"
#include "reg_spinand.h"
#include "cpu_mem_map.hc"
#include "stdcomp.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define MID_GD          0xC8
#define MID_MICRON      0x2C
#define MID_ATO         0x9B
#define MID_WINBOND     0xEF
#define MID_MXIC        0xC2
#define MID_TOSHIBA     0x98

/* SPI NAND messages */
#if 1
#define spi_nand_msg UartSendTrace
#define spi_nand_debug
#else
#define spi_nand_msg(fmt, ...)
#define spi_nand_debug(fmt, ...) printk(KERN_NOTICE "%s: " fmt "\n", __func__, ##__VA_ARGS__)
#endif
#define spi_nand_warn UartSendTrace
#define spi_nand_err UartSendTrace

#define SPINAND_FLASH_INFO_TAG "MSTARSEMIUSFDCIS"

#define DEBUG_SPINAND(debug_level, x)     do { if (_u8SPINANDDbgLevel >= (debug_level)) (x); } while(0)

#define SPINAND_MEASURE_PERFORMANCE 0
#define USE_SPINAND_INFO_TABLE 0

#define UNFD_LOGI_PART    0x8000 // bit-or if the partition needs Wear-Leveling
#define UNFD_HIDDEN_PART  0x4000 // bit-or if this partition is hidden, normally it is set for the LOGI PARTs.

//#define UNFD_PART_MIU			1
#define UNFD_PART_IPL_CUST		1
#define UNFD_PART_BOOTLOGO		2
#define UNFD_PART_IPL			3
#define UNFD_PART_OS			4
#define UNFD_PART_CUS			5
#define UNFD_PART_UBOOT			6
#define UNFD_PART_SECINFO		7
#define UNFD_PART_OTP			8
#define UNFD_PART_RECOVERY		9
#define UNFD_PART_E2PBAK		10
#define UNFD_PART_NVRAMBAK		11
#define UNFD_PART_NPT			12
#define UNFD_PART_ENV			13
#define UNFD_PART_MISC			14


//struct mstar_spinand_info
//{
//    struct mtd_info mtd;
//    struct nand_chip nand;
//    struct platform_device *pdev;
//    struct mtd_partition *parts;
//};

/// Suspend type
typedef enum
{
    E_MSOS_PRIORITY,            ///< Priority-order suspension
    E_MSOS_FIFO,                ///< FIFO-order suspension
} MsOSAttribute;

typedef struct
{
    u16 u16_StartBlk;		// the start block index
    u16 u16_BlkCnt;			// project team defined
    u16 u16_PartType;		// project team defined
    u16 u16_BackupBlkCnt;	// reserved good blocks count for backup, UNFD internal use.
    // e.g. u16BackupBlkCnt  = u16BlkCnt * 0.03 + 2
} SPI_NAND_PARTITION_RECORD_t;

typedef struct
{
    u32 u32_ChkSum;
    u16	u16_SpareByteCnt;
    u16	u16_PageByteCnt;
    u16	u16_BlkPageCnt;
    u16	u16_BlkCnt;
    u16 u16_PartCnt;
    u16 u16_UnitByteCnt;
    SPI_NAND_PARTITION_RECORD_t records[62];
} SpinandPartitionInfo_t;

typedef struct
{
    SpinandInfo_t tSpinandInfo;

    SpinandPartitionInfo_t tPartInfo;
    u8 u8_HasPNI;

    u8 *pu8_pagebuf;
    u8 *pu8_sparebuf;
    u8 *pu8_statusbuf;
    u32 u32_column;
    u8 u8_status;
    u8 u8_statusRequest;
} SpinandDriver_t;

typedef struct
{
    u8  au8_Tag[16];
    SpinandInfo_t tSpiNandInfo;
    u8 au8_Reserved[];
} SPINAND_FLASH_INFO_TAG_t;

int DrvSpinandProbe(void);

bool DrvSpinandInit(SpinandInfo_t *gtSpinandInfo);
u32 MDrv_SPINAND_Read(U32 u32_PageIdx, U8 *u8Data, U8 *pu8_SpareBuf);
U32 MDrv_SPINAND_Write(U32 u32_PageIdx, U8 *u8Data, U8 *pu8_SpareBuf);
U32 MDrv_SPINAND_BLOCK_ERASE(U32 u32_BlkIdx);
U8 MDrv_SPINAND_ReadID(U16 u16Size, U8 *u8Data);
//	void _spiNandMain(unsigned int dwSramAddress, unsigned int dwSramSize);
//	U32 MDrv_SPINAND_SetMode(SPINAND_MODE eMode);
//	BOOL MDrv_SPINAND_ForceInit(SpinandInfo_t *gtSpinandInfo);
//	void MDrv_SPINAND_Device(struct device *dev);
//	U32 DrvSpinandWriteProtect(BOOL bEnable);
//	BOOL DrvSpinandIsActive(void);
//	U32 MDrv_SPINAND_Read_RandomIn(U32 u32_PageIdx, U32 u32_Column, U32 u32_Byte, U8 *u8Data);
//	U32 DrvSpinandReadStatusRegister(U8 *u8Status, U8 u8Addr);
//
//	//	unsigned char MsOS_In_Interrupt (void);
//	inline BOOL DrvSpinandInInterrupt (void);
//	inline U32  DrvSpinandCreateMutex ( MsOSAttribute eAttribute, char *pMutexName, U32 u32Flag);
//	inline BOOL DrvSpinandDeleteMutex(S32 s32MutexId);
//	inline BOOL DrvSpinandObtainMutex (S32 s32MutexId, U32 u32WaitMs);
//	inline BOOL DrvSpinandReleaseMutex (S32 s32MutexId);
void *drvSPINAND_get_DrvContext_address(void);
extern SpinandInfo_t gtSpinandInfo;
extern  u8 _u8SPINANDDbgLevel;
#ifdef __cplusplus
}
#endif

#endif
