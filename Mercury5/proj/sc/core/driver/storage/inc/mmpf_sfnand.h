#ifndef	_MMPF_SFNAND_H_
#define	_MMPF_SFNAND_H_

#include "config_fw.h"

#if (1)
/** @addtogroup MMPF_SM
@{
*/
#define	SN_2K_PAGE          (1)	        // 0: 512bytes flash(64MB below), 1: 2k bytes flash(128MB above) 

#if (SN_2K_PAGE == 0)
#define WP_ON               0x00
#define WP_OFF              0x01

/****************************************************************************/
/*  SMC mapping definition                                                  */
/****************************************************************************/
typedef struct {
	MMP_ULONG   fat_blk_addr;
	MMP_USHORT cur_blk_state;
	MMP_USHORT	log_blk_offset;
	MMP_USHORT new_phy_blk_offset;
	MMP_ULONG   new_phy_blk_addr;
	MMP_USHORT old_phy_blk_offset;
	MMP_ULONG   old_phy_blk_addr;
	MMP_USHORT *free_blk_idx;
	MMP_USHORT loop_cntr;
} SFNAND_SMCMAPWRITEINFO;
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
#define BLOCK_SIZE_SHIFT        5


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
/* Async write queue */




#else

// NAND flash status
#define	NOT_WRITE_PROTECT	0x80
#define	DEVICE_READY		0x40
#define	PROGRAM_FAIL		0x01

// NAND commmand
#define NAD_GETSTATUS            0x0F
#define NAD_SETFEATURE           0x1F

#define NAD_PAGEREAD             0x13
#define NAD_READFROMCAHCE        0x03
#define NAD_READFROMCAHCEX2      0x3B
#define NAD_READFROMCAHCEX4      0x6B
#define NAD_PROGRAMLOAD          0x02
#define NAD_PROGRAMLOADX4        0x32
#define NAD_RANDOMPROGRAMLOAD    0x84
#define NAD_PROGRAMEXECUTE       0x10

#define NAD_RESET                0xFF
#define NAD_WRITE_EN             0x06
#define NAD_WRITE_DIS            0x04
#define NAD_READID               0x9F
#define NAD_BLOCKERASE           0xD8

// NAND Command Address
#define NAD_ADDRESS_READID      0x0

#define NAD_ADDRESS_STATUS       0xC0
#define NAD_ADDRESS_FEATURE      0xB0
#define NAD_ADDRESS_PROTECT      0xA0

// NAND Status define 
#define NAD_STATUS_OIP           0x01
#define NAD_STATUS_ECC_MASK      0x30
#define NAD_STATUS_ECC_OK        0x00
#define NAD_STATUS_ECC_CORRECT1  0x10
#define NAD_STATUS_ECC_Fail      0x20
#define NAD_STATUS_ECC_CORRECT2  0x30
#define NAD_STATUS_ECC_MASK_NEW  0x70
#define NAD_STATUS_ECC_FAIL_NEW  0x70


#define NAD_STATUS_EFAIL         0x04
#define NAD_STATUS_PFAIL         0x08

// Nand Wrap Define
#define NAD_WRAP2112             0x00
#define NAD_WRAP2048             0x04
#define NAD_WRAP64               0x08
#define NAD_WRAP16               0x0C
#define NAD_WRAPVALUE(m)         (m) << 12


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

/****************************************************************************/
/*  SMC mapping definition                                                  */
/****************************************************************************/
typedef struct {
	MMP_USHORT cur_blk_state;
	MMP_USHORT	log_blk_offset;
	MMP_USHORT new_phy_blk_offset;
	MMP_ULONG   new_phy_blk_addr;
	MMP_USHORT old_phy_blk_offset;
	MMP_ULONG   old_phy_blk_addr;
	MMP_USHORT *free_blk_idx;
	MMP_USHORT loop_cntr;
} SFNAND_SMCMAPWRITEINFO;

#define ZONE_SIZE               1024
#define BLOCK_SIZE              256
#define BLOCK_SIZE_SHIFT        8
//#define MAX_BLOCK_NUM           1000
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

#endif  // #if !defined(SN_2K_PAGE)

typedef enum {
	NAND_READ       			= 0,
	NAND_WRITE			        = 1,
	NAND_NONE_ACCESS            = 2
} NANDRW;

typedef struct _SFNANDCommand{
	MMP_ULONG   ulNandAddr;
	MMP_ULONG	ulDMAAddr;
	MMP_USHORT  usDMASize;
	MMP_UBYTE   ubCommand;
	MMP_UBYTE   ubNandAddrCnt;
	NANDRW      RW;
} SFNANDCommand;

/**
*   @brief  MMPF_SFNAND_ISR
*
*
*/
void MMPF_SFNAND_ISR(void); 
/**       
*   @brief  MMPF_SM_MemoryAlloc
*
*   This function should be called before file system initial.
*   And then, it returns required buffer size, which depends on current NAND flash driver configuration..
*
*   @return Required buffer size, which depends on current NAND flash driver configuration.
*/
MMP_USHORT MMPF_SFNAND_MemoryAlloc(void);
/**
*   @brief  MMPF_SFNAND_MemoryAlloc
*
*   Assign buffer start address and size for NAND flash driver.
*   Size should depends on MMPF_SFNAND_MemoryAlloc(), but currently hard-code.
*
*   @param[in] ulStartAddr Start address for NAND flash driver usage.
*   @retval MMP_ERR_NONE No error
*   @retval MMP_SFNAND_ERR_PARAMETER Error for input parameter. (if start address is point to 0x0, returns this error)
*/
MMP_ERR MMPF_SFNAND_SetMemory(MMP_ULONG ulStartAddr);
/**
*   @brief  MMPF_SFNAND_Enable
*
*   @param[in] bEnable Status of NAND's CE/# pin. MMP_TRUE: CE low (active), MMP_FALSE: CE high (inactive).
*   @param[in] bWProtect Status of NAND's WP/# pin. MMP_TRUE: WP low (Write Protected), MMP_FALSE: WP high (Writeable).
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_SFNAND_Enable(MMP_BOOL bEnable, MMP_BOOL bWProtect);
/**
*   @brief  MMPF_SFNAND_GetStatus
*
*   Check return status provide by NAND flash
*
*   @param[out] return status provide by NAND flash. Status code depends on commnad, normal/abnormal must checked by caller.
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_SFNAND_GetStatus(MMP_UBYTE* status);
/**
*   @brief  MMPF_SM_InitialInterface
*
*   Initial AIT NAND flash controller interface.
*   For convenient, it also setup buffer address/size for driver,
*   and build up physcial to logical mapping table, and logical to physical mapping table.
*
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_SFNAND_InitialInterface(void);
/**
*   @brief  MMPF_SFNAND_Reset
*   Perform NAND flash hardware and software reset sequence.
*
*   @retval MMP_ERR_NONE No error
*   @retval MMP_SFNAND_ERR_RESET Reset fail
*/
MMP_ERR MMPF_SFNAND_Reset(void);
/**
*   @brief  MMPF_SFNAND_GetSize
*
*   @param[out] pSize Count of FS sector (logical sector) size (Hard-code as 512 byte currently)
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_SFNAND_GetSize(MMP_ULONG* pSize);
/**
*   @brief  MMPF_SFNAND_SendCommand
*   @param[in] ubCommand Put specific command onto BUS for NAND flash
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_SFNAND_SendCommand(SFNANDCommand *SFNandCommand);
/**
*   @brief  MMPF_SFNAND_SendAddress
*   @param[in] ubAddr Pointer to specific page address
*   @param[in] usPhase Phase count of address cycle
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_SFNAND_SendAddress(MMP_UBYTE* ubAddr, MMP_USHORT usPhase);
/**
*   @brief  MMPF_SFNAND_ReadRA
*
*   Read R.A. (redundant area, or spare area) to specific buffer address.
*   Caller just input physical page address of main area,
*   and this function will calculate physical page address of spare area.
*
*   @param[in] ulAddr DMA destination address for incoming date
*   @param[in] ulPage Physical page address of main area.
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_SFNAND_ReadRA(MMP_ULONG ulAddr, MMP_ULONG ulPage);
/**
*   @brief  MMPF_SFNAND_WriteRA
*
*   Write R.A. (redundant area, or spare area) to NAND flash.
*   Caller just input physical page address of main area,
*   and this function will calculate physical page address of spare area.
*
*   @param[in] ulAddr DMA src address for outgoing date
*   @param[in] ulPage Physical page address of main area.
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_SFNAND_WriteRA(MMP_ULONG ulAddr, MMP_ULONG ulPage, MMP_ULONG ulOffset, MMP_UBYTE ubcount);

/**
*   @brief  MMPF_SFNAND_EraseBlock
*
*   Erase NAND block which contains specific page address.
*   This API will copy all other valid pages within this block to other block

*   Caller just input physical page address of main area,
*   and this function will calculate physical page address of spare area.
*
*   @param[in] ulStartPage Page address needs to be erase
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_SFNAND_EraseBlock(MMP_ULONG ulStartPage);
/**
*   @brief  MMPF_SFNAND_ReadPhysicalSector
*
*   Read physical page (main area) from NAND flash.
*
*   @param[in] ulAddr DMA destination address for incoming date
*   @param[in] ulPage Physical page address of main area.
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_SFNAND_ReadPhysicalSector(MMP_ULONG ulAddr, MMP_ULONG ulPage);
/**
*   @brief  MMPF_SFNAND_WritePhysicalSector
*
*   Write physical page (main area) to NAND flash.
*
*   @param[in] ulAddr DMA src address for outgoing date
*   @param[in] ulPage Physical page address of main area.
*   @retval MMP_ERR_NONE No error
*/

MMP_ERR MMPF_SFNAND_WritePhysicalSector(MMP_ULONG ulAddr, MMP_ULONG ulPage);
MMP_ERR MMPF_SFNAND_FinishWrite(void);
/**
*   @brief  MMPF_SM_LowLevelFormat
*
*   Handling BBM (Bad Block Management), and logical block mapping.
*
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_SFNAND_LowLevelFormat(void);
/**
*   @brief  MMPF_SFNAND_WriteSector
*   Main entry point for application writing data.
*   - File system: sm_misc.c, _SM_DevWrite(), _SM_WriteBurst()
*   - USB MSDC: mmpf_usbmsdc.c, MSDCWriteFile(), msdc_cmd_write()
*
*   @param[in] dmastartaddr DMA source address which assigned by caller (ex: file system)
*   @param[in] startsect start sector number in logical address
*   @param[in] sectcount sector count
*   @retval MMP_ERR_NONE No error
*/
MMP_ERR MMPF_SFNAND_WriteSector(MMP_ULONG dmastartaddr,
                              MMP_ULONG startsect,
                              MMP_USHORT sectcount);
/**
*   @brief  MMPF_SFNAND_ReadSector
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
MMP_ERR MMPF_SFNAND_ReadSector(MMP_ULONG dmastartaddr,
                             MMP_ULONG startsect,
                             MMP_USHORT sectcount);
MMP_ERR MMPF_SFNAND_CopyBack(MMP_ULONG  ulSrcPage, MMP_ULONG ulDstPage);

/**
*   @brief  MMPF_SFNAND_ECCCorrect
*
*   Try to fix ECC by software algorithm.
*
*   @retval MMP_ERR_NONE No error
*   @retval MMP_SFNAND_ERR_ECC_CORRECTABLE ECC error, but correctable
*   @retval MMP_SFNAND_ERR_ECC ECC error, and cannot correct
*/

MMP_ERR MMPF_SFNAND_ECCCorrect(MMP_UBYTE* p_data,
                             MMP_UBYTE* ecc1,
                             MMP_UBYTE* ecc2,
                             MMP_UBYTE* p_offset,
                             MMP_UBYTE* p_corrected);
/**
*   @brief  MMPF_SFNAND_ECCDecode
*
*   Decode ECC for incoming data while calling MMPF_SFNAND_ReadPhysicalSector()
*   If ECC not matched, calling MMPF_SFNAND_ECCCorrect() to try to fix ECC.
*
*   @retval MMP_ERR_NONE No error
*   @retval MMP_SFNAND_ERR_ECC_CORRECTABLE ECC error, but correctable
*   @retval MMP_SFNAND_ERR_ECC ECC error, and cannot correct
*/
MMP_ERR MMPF_SFNAND_ECCDecode(MMP_UBYTE* p_buf,
                            MMP_UBYTE* p_ecc,
                            MMP_UBYTE* ecc_data);
MMP_ERR MMPF_SFNAND_PreCopyBack(MMP_ULONG ulPageAddr);
MMP_ERR MMPF_SFNAND_PostCopyBack(void);
MMP_ERR MMPF_SFNAND_FinishWritePage(MMP_ULONG ulStartSector);
MMP_ERR MMPF_SFNAND_SwapBigPages(void);
MMP_ERR MMPF_SFNAND_SwapSmallPages(void);
MMP_ERR MMPF_SFNAND_SwapPages1(void);
MMP_ERR MMPF_SFNAND_SwapPages2(void);

/**
*   @brief  MMPF_SFNAND_GetMapAddress
*   @param[in] ulLogicalAddr Look-up mapping table to get Physical page address for specific logical address
*   @return Physical address on NAND flash
*/
MMP_ULONG MMPF_SFNAND_GetMapAddress(MMP_ULONG ulLogicalAddr);
/**
*   @brief  MMPF_SFNAND_BuildOneMapTable
*
*   Build mapping table for single zone. (software definition, 1 zone = 1024 pages)
*   When this function return, smcblkaddrbuf contains physical to logical mapping table,
*   and smcmaptabbuf contains logical to physcial mapping table.
*
*   @param[in] zone number (zone is software definition, 1 zone = 1024 pages)
*   @param[in] smcblkaddrbuf Pointer to physical to logical mapping table
*   @param[in] smcmaptabbuf Pointer to logical to physical mapping table
*/
void MMPF_SFNAND_BuildOneMapTable(MMP_USHORT zone_num,
                              MMP_USHORT* smcblkaddrbuf,
                              MMP_USHORT* smcmaptabbuf);
/**
*   @brief  MMPF_SFNAND_BuildAllMapTable
*
*   TBD
*/
MMP_USHORT MMPF_SFNAND_BuildAllMapTable(void);
/**
*   @brief  MMPF_SFNAND_BuildMapTab
*
*   TBD
*/
void MMPF_SFNAND_BuildMapTab(MMP_USHORT zone_num,
                         MMP_USHORT* smcblkaddrbuf,
                         MMP_USHORT* smcmaptabbuf);
/**
*   @brief  MMPF_SFNAND_GetAllBlkAddr
*
*   TBD
*/
MMP_UBYTE MMPF_SFNAND_GetAllBlkAddr(MMP_USHORT zone_num, MMP_USHORT* smcblkaddrbuf);
/**
*   @brief  MMPF_SFNAND_GetLogBlk
*
*   TBD
*/
MMP_UBYTE MMPF_SFNAND_GetLogBlk(MMP_ULONG logical_page_addr);
/**
*   @brief  MMPF_SFNAND_GetMapTab
*
*   @param[in] smcblkaddrbuf Pointer to physical to logical mapping table
*   @param[in] smcmaptabbuf Pointer to logical to physical mapping table
*/
void MMPF_SFNAND_GetMapTab(MMP_USHORT* smcblkaddrbuf,
                            MMP_USHORT* smcmaptabbuf);

MMP_ERR MMPF_SFNAND_SwapPagesShort(void); 
/*
MMP_USHORT MMPF_SMReadMapTabFromNand(MMP_USHORT zone_num,
                                     MMP_USHORT* smcblkaddrbuf,
                                     MMP_USHORT* smcmaptabbuf);
*/
//MMP_USHORT MMPF_SFNAND_WriteMapToNand(void);

void    MMPF_SM_SetTmpAddr(MMP_ULONG ulStartAddr, MMP_ULONG ulSize);
void    MMPF_SM_GetTmpAddr(MMP_ULONG *ulStartAddr);
MMP_ERR  MMPF_SFNAND_SetProtection(MMP_UBYTE bProtection);
MMP_ERR MMPF_SFNAND_ReadSector(MMP_ULONG dmastartaddr, MMP_ULONG startsect, MMP_USHORT sectcount);
void    MMPF_SFNAND_SetTmpAddr(MMP_ULONG ulStartAddr, MMP_ULONG ulSize);
void    MMPF_SFNAND_GetTmpAddr(MMP_ULONG *ulStartAddr);
MMP_ERR MMPF_SFNAND_ReadPhysicalPage(MMP_ULONG ulAddr, MMP_ULONG ulPage);
MMP_ERR MMPF_SFNAND_WritePhysicalPage(MMP_ULONG ulAddr, MMP_ULONG ulPage);
MMP_ERR MMPF_SFNAND_SetType(MMP_UBYTE ubType);

#endif  //(1)
#endif  //_MMPF_SFNAND_H_
/** @} */ // MMPF_SM
