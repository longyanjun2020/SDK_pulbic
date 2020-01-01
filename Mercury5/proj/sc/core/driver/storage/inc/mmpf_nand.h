#ifndef	_MMPF_NAND_H_
#define	_MMPF_NAND_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "config_fw.h"

/** @addtogroup MMPF_SM
@{
*/

/****************************************************************************/
/*  SMC compiling options                                                   */
/****************************************************************************/

#define	SM_2K_PAGE      (1)	/* 0: 512bytes flash(64MB below);
                             * 1: 2k bytes flash(128MB above) */

#if (SM_2K_PAGE == 0)
#define WP_ON               0x00
#define WP_OFF              0x01

typedef struct{
	MMP_ULONG   fat_blk_addr;
	MMP_USHORT  cur_blk_state;
	MMP_USHORT	log_blk_offset;
	MMP_USHORT  new_phy_blk_offset;
	MMP_ULONG   new_phy_blk_addr;
	MMP_USHORT  old_phy_blk_offset;
	MMP_ULONG   old_phy_blk_addr;
	MMP_USHORT  *free_blk_idx;
	MMP_USHORT  loop_cntr;
} SMCMAPWRITEINFO;

/* Parameters of Dual die NAND flash */
#define ZONE_SIZE          1024             /* Size of one zone      */
#define BLOCK_SIZE         32               /* Pages/Block           */
#define MAX_BLOCK_NUM      1000             /* Vaild block number    */
#define MAX_FREE_BLK_NUM   24               /* Max Free Blocks       */
#define FREE_BLOCK         0x3FF
#define NULL_BLK_ENTRY     0x400
#define MAP_TAB_BLOCK      0x401
#define REV_BAD_BLOCK      0x402
#define OLD_BLOCK             1
#define NEW_BLOCK             2
#define BLOCK_SIZE_SHIFT      5

#define ACTION_DONE     0x00
#define NON_FINISHED    0x01

/* Wait write complete defined */
#define WAIT_COMPLETE       0x00
#define NO_WAIT_COMPLETE    0x01

#define ERASE_BLOCK_IN_IRQ  0x01

/* SM async write stage */
#define SM_IDLE                         0x00
#define ACTION_AFTER_WRITE_ONE_PAGE     0x01
#define ONE_WRITE_PAGE_LEFT             0x02
#define ERASE_BLOCK                     0x03
#define SM_BUSY                         0x04
#define EXIT_COPY_BACK                  0x05
#define PRE_COPY_BACK                   0x06
#define WRITE_PAGE                      0x07

#else // SM_2K_PAGE

// NAND flash status
#define	NOT_WRITE_PROTECT	0x80
#define	DEVICE_READY		0x40
#define	PROGRAM_FAIL		0x01

// NAND commmand
#define NAD_READ_1               0x00
#define NAD_READ_2               0x30
#define NAD_READ_3               0x50
#define NAD_COPYBACK_READ_1      0x00
#define NAD_COPYBACK_READ_2      0x35
#define NAD_READ_ID              0x90
#define NAD_CMD_RESET            0xFF
#define NAD_PAGE_PRG_1           0x80
#define NAD_PAGE_PRG_2           0x10
#define NAD_COPYBACK_PRG_1       0x85
#define NAD_COPYBACK_PRG_1_512   0x8A
#define NAD_COPYBACK_PRG_2       0x10
#define NAD_COPYBACK_PRG_2_PLANE 0x11
#define NAD_BLK_ERASE_1          0x60
#define NAD_BLK_ERASE_2          0xD0
#define NAD_READ_STATUS          0x70

#define	REDT_DATA_STATUS_B		0x04
#define	REDT_DATA_BLOCK_B		0x05
#define	REDT_ADDR1_H_B			0x06
#define	REDT_ADDR1_L_B			0x07
#define	REDT_ECC_20_B			0x08
#define	REDT_ECC_21_B			0x09
#define	REDT_ECC_22_B			0x0A
#define	REDT_ADDR2_H_B			0x0B
#define	REDT_ADDR2_L_B			0x0C
#define	REDT_ECC_10_B			0x0D
#define	REDT_ECC_11_B			0x0E
#define	REDT_ECC_12_B			0x0F

typedef struct {
	MMP_USHORT  cur_blk_state;
	MMP_USHORT	log_blk_offset;
	MMP_USHORT  new_phy_blk_offset;
	MMP_ULONG   new_phy_blk_addr;
	MMP_USHORT  old_phy_blk_offset;
	MMP_ULONG   old_phy_blk_addr;
	MMP_USHORT  *free_blk_idx;
	MMP_USHORT  loop_cntr;
} SMCMAPWRITEINFO;
 
#define ZONE_SIZE               1024
#define BLOCK_SIZE              256
#define BLOCK_SIZE_SHIFT        8
#define MAX_BLOCK_NUM           1000
#define MAX_FREE_BLK_NUM        24
#define	PAGE_PER_BLOCK		    0x40
#define	PAGE_PER_BLOCK_MASK	    0xFF
#define	PAGE_PRE_BLOCK_SHIFT	0x08
#define	PAGE_SIZE_SHIFT		    0x0B
#define SM_BUS_REENTRY_PROTECT			(1)
#define IMPLEMENT_FLM                   (0)

/* Software Mark Information */
#define FREE_BLOCK         0x03FF
#define NULL_BLK_ENTRY     0x0400
#define MAP_TAB_BLOCK      0x0401
#define REV_BAD_BLOCK      0x0402

/* Software Mark Information */
#define OLD_BLOCK             1
#define NEW_BLOCK             2

#endif  // #if !defined(SM_2K_PAGE)

//==============================================================================
//
//                              FUNCTION PROTOTYPE
//
//==============================================================================

void MMPF_NAND_ISR(void);
/**
*   @brief  MMPF_SM_MemoryAlloc
*
*   This function should be called before file system initial.
*   And then, it returns required buffer size, which depends on current NAND flash driver configuration..
*
*   @return Required buffer size, which depends on current NAND flash driver configuration.
*/
MMP_USHORT MMPF_SM_MemoryAlloc(void);
/**
*   @brief  MMPF_NAND_SetMemory
*
*   Assign buffer start address and size for NAND flash driver.
*   Size should depends on MMPF_SM_MemoryAlloc(), but currently hard-code.
*
*   @param[in] ulStartAddr Start address for NAND flash driver usage.
*   @retval MMP_ERR_NONE No error
*   @retval MMP_NAND_ERR_PARAMETER Error for input parameter. (if start address is point to 0x0, returns this error)
*/
MMP_ERR MMPF_NAND_SetMemory(MMP_ULONG ulStartAddr);
/**
*   @brief  MMPF_NAND_Enable
*
*   @param[in] bEnable Status of NAND's CE/# pin. MMP_TRUE: CE low (active), MMP_FALSE: CE high (inactive).
*   @param[in] bWProtect Status of NAND's WP/# pin. MMP_TRUE: WP low (Write Protected), MMP_FALSE: WP high (Writeable).
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_NAND_Enable(MMP_BOOL bEnable, MMP_BOOL bWProtect);
/**
*   @brief  MMPF_NAND_GetStatus
*
*   Check return status provide by NAND flash
*
*   @param[out] return status provide by NAND flash. Status code depends on commnad, normal/abnormal must checked by caller.
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_NAND_GetStatus(MMP_UBYTE* status);
/**
*   @brief  MMPF_SM_InitialInterface
*
*   Initial AIT NAND flash controller interface.
*   For convenient, it also setup buffer address/size for driver,
*   and build up physcial to logical mapping table, and logical to physical mapping table.
*
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_NAND_InitialInterface(void);
/**
*   @brief  MMPF_NAND_Reset
*   Perform NAND flash hardware and software reset sequence.
*
*   @retval MMP_ERR_NONE No error
*   @retval MMP_NAND_ERR_RESET Reset fail
*/
MMP_ERR MMPF_NAND_Reset(void);
/**
*   @brief  MMPF_NAND_GetSize
*
*   @param[out] pSize Count of FS sector (logical sector) size (Hard-code as 512 byte currently)
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_NAND_GetSize(MMP_ULONG* pSize);
/**
*   @brief  MMPF_NAND_SendCommand
*   @param[in] ubCommand Put specific command onto BUS for NAND flash
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_NAND_SendCommand(MMP_UBYTE ubCommand);
/**
*   @brief  MMPF_NAND_SendAddress
*   @param[in] ubAddr Pointer to specific page address
*   @param[in] usPhase Phase count of address cycle
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_NAND_SendAddress(MMP_UBYTE* ubAddr, MMP_USHORT usPhase);
/**
*   @brief  MMPF_NAND_ReadRA
*
*   Read R.A. (redundant area, or spare area) to specific buffer address.
*   Caller just input physical page address of main area,
*   and this function will calculate physical page address of spare area.
*
*   @param[in] ulAddr DMA destination address for incoming date
*   @param[in] ulPage Physical page address of main area.
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_NAND_ReadRA(MMP_ULONG ulAddr, MMP_ULONG ulPage);
/**
*   @brief  MMPF_NAND_WriteRA
*
*   Write R.A. (redundant area, or spare area) to NAND flash.
*   Caller just input physical page address of main area,
*   and this function will calculate physical page address of spare area.
*
*   @param[in] ulAddr DMA src address for outgoing date
*   @param[in] ulPage Physical page address of main area.
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_NAND_WriteRA(MMP_ULONG ulAddr, MMP_ULONG ulPage);
/**
*   @brief  MMPF_NAND_EraseBlock
*
*   Erase NAND block which contains specific page address.
*   This API will copy all other valid pages within this block to other block

*   Caller just input physical page address of main area,
*   and this function will calculate physical page address of spare area.
*
*   @param[in] ulStartPage Page address needs to be erase
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_NAND_EraseBlock(MMP_ULONG ulStartPage);
/**
*   @brief  MMPF_NAND_ReadPhysicalSector
*
*   Read physical page (main area) from NAND flash.
*
*   @param[in] ulAddr DMA destination address for incoming date
*   @param[in] ulPage Physical page address of main area.
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_NAND_ReadPhysicalSector(MMP_ULONG ulAddr, MMP_ULONG ulPage);
/**
*   @brief  MMPF_NAND_WritePhysicalSector
*
*   Write physical page (main area) to NAND flash.
*
*   @param[in] ulAddr DMA src address for outgoing date
*   @param[in] ulPage Physical page address of main area.
*   @retval MMP_ERR_NONE No error
*/

MMP_ERR MMPF_NAND_WritePhysicalSector(MMP_ULONG ulAddr, MMP_ULONG ulPage);
MMP_ERR MMPF_NAND_FinishWrite(void);
/**
*   @brief  MMPF_SM_LowLevelFormat
*
*   Handling BBM (Bad Block Management), and logical block mapping.
*
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_NAND_LowLevelFormat(void);
/**
*   @brief  MMPF_NAND_WriteSector
*   Main entry point for application writing data.
*   - File system: sm_misc.c, _SM_DevWrite(), _SM_WriteBurst()
*   - USB MSDC: mmpf_usbmsdc.c, MSDCWriteFile(), msdc_cmd_write()
*
*   @param[in] dmastartaddr DMA source address which assigned by caller (ex: file system)
*   @param[in] startsect start sector number in logical address
*   @param[in] sectcount sector count
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_NAND_WriteSector(MMP_ULONG dmastartaddr,
                              MMP_ULONG startsect,
                              MMP_USHORT sectcount);
/**
*   @brief  MMPF_NAND_ReadSector
*   Main entry point for application reading data.
*   - File system: mmpf_fs_api.c, MMPF_FS_GetPBROffset()
*   - File system: sm_misc.c, _SM_DevRead(), _SM_ReadBurst()
*   - USB MSDC: mmpf_usbmsdc.c, MSDC_Read10_Cmd(), msdc_cmd_read10()
*
*   @param[in] dmastartaddr DMA destination address which assigned by caller (file system)
*   @param[in] startsect start sector number in logical address
*   @param[in] sectcount sector count
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_NAND_ReadSector(MMP_ULONG dmastartaddr,
                             MMP_ULONG startsect,
                             MMP_USHORT sectcount);
MMP_ERR MMPF_NAND_CopyBack(MMP_ULONG  ulSrcPage, MMP_ULONG ulDstPage);

/**
*   @brief  MMPF_NAND_ECCCorrect
*
*   Try to fix ECC by software algorithm.
*
*   @retval MMP_ERR_NONE No error
*   @retval MMP_NAND_ERR_ECC_CORRECTABLE ECC error, but correctable
*   @retval MMP_NAND_ERR_ECC ECC error, and cannot correct
*/

MMP_ERR MMPF_NAND_ECCCorrect(MMP_UBYTE* p_data,
                             MMP_UBYTE* ecc1,
                             MMP_UBYTE* ecc2,
                             MMP_UBYTE* p_offset,
                             MMP_UBYTE* p_corrected);
/**
*   @brief  MMPF_NAND_ECCDecode
*
*   Decode ECC for incoming data while calling MMPF_NAND_ReadPhysicalSector()
*   If ECC not matched, calling MMPF_NAND_ECCCorrect() to try to fix ECC.
*
*   @retval MMP_ERR_NONE No error
*   @retval MMP_NAND_ERR_ECC_CORRECTABLE ECC error, but correctable
*   @retval MMP_NAND_ERR_ECC ECC error, and cannot correct
*/
MMP_ERR MMPF_NAND_ECCDecode(MMP_UBYTE* p_buf,
                            MMP_UBYTE* p_ecc,
                            MMP_UBYTE* ecc_data);
MMP_ERR MMPF_NAND_PreCopyBack(MMP_ULONG ulPageAddr);
MMP_ERR MMPF_NAND_PostCopyBack(void);
MMP_ERR MMPF_NAND_FinishWritePage(MMP_ULONG ulStartSector);
MMP_ERR MMPF_NAND_SwapBigPages(void);
MMP_ERR MMPF_NAND_SwapSmallPages(void);
MMP_ERR MMPF_NAND_SwapPages1(void);
MMP_ERR MMPF_NAND_SwapPages2(void);

/**
*   @brief  MMPF_NAND_GetMapAddress
*   @param[in] ulLogicalAddr Look-up mapping table to get Physical page address for specific logical address
*   @return Physical address on NAND flash
*/
MMP_ULONG MMPF_NAND_GetMapAddress(MMP_ULONG ulLogicalAddr);
/**
*   @brief  MMPF_NAND_BuildOneMapTable
*
*   Build mapping table for single zone. (software definition, 1 zone = 1024 pages)
*   When this function return, smcblkaddrbuf contains physical to logical mapping table,
*   and smcmaptabbuf contains logical to physcial mapping table.
*
*   @param[in] zone number (zone is software definition, 1 zone = 1024 pages)
*   @param[in] smcblkaddrbuf Pointer to physical to logical mapping table
*   @param[in] smcmaptabbuf Pointer to logical to physical mapping table
*/
void MMPF_NAND_BuildOneMapTable(MMP_USHORT zone_num,
                              MMP_USHORT* smcblkaddrbuf,
                              MMP_USHORT* smcmaptabbuf);
MMP_USHORT MMPF_NAND_BuildAllMapTable(void);
void MMPF_NAND_BuildMapTab(MMP_USHORT zone_num,
                         MMP_USHORT* smcblkaddrbuf,
                         MMP_USHORT* smcmaptabbuf);
MMP_UBYTE MMPF_NAND_GetAllBlkAddr(MMP_USHORT zone_num, MMP_USHORT* smcblkaddrbuf);
MMP_UBYTE MMPF_NAND_GetLogBlk(MMP_ULONG logical_page_addr);
/**
*   @brief  MMPF_NAND_GetMapTab
*
*   @param[in] smcblkaddrbuf Pointer to physical to logical mapping table
*   @param[in] smcmaptabbuf Pointer to logical to physical mapping table
*/
void MMPF_NAND_GetMapTab(MMP_USHORT* smcblkaddrbuf,
                            MMP_USHORT* smcmaptabbuf);

MMP_ERR MMPF_NAND_SwapPagesShort(void);

void    MMPF_SM_SetTmpAddr(MMP_ULONG ulStartAddr, MMP_ULONG ulSize);
void    MMPF_SM_GetTmpAddr(MMP_ULONG *ulStartAddr);

#endif  // _MMPF_NAND_H_

/** @} */ // MMPF_SM
