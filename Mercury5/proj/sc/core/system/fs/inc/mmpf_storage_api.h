#ifndef _MMPF_STORAGE_API_H_
#define _MMPF_STORAGE_API_H_

#include "fs_dev.h"
//#include "config_fw.h"

//==============================================================================
//
//                              COMPILING OPTIONS
//
//==============================================================================

#define STORAGE_CHECK_BOUNDARY          (0)
#define STORAGE_DIRECTLY_ACCESS_UNIT    (0xFF)

//==============================================================================
//
//                              CONSTANT
//
//==============================================================================

/* ulHeader, ulTail */
#define INDEX_TABLE_HEADER      (0x3552434D)
#define INDEX_TABLE_TAIL        (0x3552434D)

/* bStorageInfo0 Flag */

/* bStorageInfo1 Flag */
#define STORAGE_FLAG_NO_BOOTAREA    0x00000001      //if this flag is set, it[0~10] is boot area and it[11~30] is user area

/* partition ulFlag0 Flag */
#define PART_FLAG_VALID             0x00000001
#define PART_FLAG_FAT               0x00000002
#define PART_FLAG_PADDING           0x00000004
#define PART_FLAG_WP                0x00000008

#define PART_FLAG_BOOT_CHECKSUM     0x40000000
#define PART_FLAG_BOOT_AREA         0x80000000

/* partition ulFlag1 Flag */

/*
name:   storage path full name, ex SD:\\ 
device: storage devie api. each devie has its xx_mise.c api interface. 
*/
#define MAX_STORAGE_NUM         	30
#define MAX_PARTI_NUM               29

typedef enum{
    PADDING_NONE,
    PADDING_HIT,
    PADDING_SKIP_DONE
}PADDING_STATUS;
//==============================================================================
//
//                              STRUCTURE
//
//==============================================================================

typedef struct _STORAGE_UNIT 
{
    char * name;
    MMP_UBYTE unit;
    FS_DEVICE_TYPE * device;
    //MMP_UBYTE *buffer;                // for the future function
    //MMP_ULONG buffersize;             // for the future function
}STORAGE_UNIT;

typedef struct _STORAGE_PARTITION
{
    MMP_ULONG StartSec;
    MMP_ULONG TotalSec;
}STORAGE_PARTITION;

typedef struct _STORAGE_STATUS
{
    MMP_BOOL bIsCardInitialized;
    MMP_UBYTE bPartitionNumber;
    MMP_BOOL bIsCardReset;
}STORAGE_STATUS;

typedef struct _AIT_STORAGE_PART
{
	MMP_ULONG ulStartSec;
	MMP_ULONG ulSecSize;
	MMP_ULONG ulFlag0;
	MMP_ULONG ulRealSize;
}AIT_STORAGE_PART;

typedef struct _AIT_STORAGE_INDEX_TABLE
{
	MMP_ULONG ulHeader;
	MMP_ULONG bStorageInfo0;
	MMP_ULONG bStorageInfo1;
	MMP_ULONG bStorageTotalSector;
	AIT_STORAGE_PART it[MAX_STORAGE_NUM];
	MMP_ULONG ulDummy[3];
	MMP_ULONG ulTail;
}AIT_STORAGE_INDEX_TABLE;

typedef struct _AIT_BOOT_PART
{
	MMP_ULONG ulStartBlock;	// The "relative" block address in this layer of the boot codes (in blocks)
	MMP_ULONG ulCodeSize;	// The exact download code size. (in bytes)
	MMP_ULONG ulDownloadDstAddress;	//The destination address of our chip to put the boot codes in.
	MMP_ULONG ulFlag;		// bit[0] active;
}AIT_BOOT_PART;

typedef struct _AIT_STORAGE_INDEX_TABLE2
{
	MMP_ULONG ulHeader;				// check unit for the correctness of the AIT_STORAGE_INDEX_TABLE (0x'V''S''N''2')
	MMP_ULONG ulFlag;
		//bit[0] active; 
		//bit[30] CRC available for boot partition, if CRC is available, it resides in the next block; 
		//bit[31] download FW from MMC user area in bootROM
	MMP_ULONG ulAlignedBlockSizeShift;	// For serial flash, it's normally the minimum erasable size, 4K, then ulAlignedBlockSizeShift is 12 For SD cards, it's 9.
	MMP_ULONG ulTotalSectorsInLayer;	// Total Blocks (including header and CRC block if exists) in this layer. Information for jumping to next layer
	AIT_BOOT_PART bt;
	AIT_STORAGE_PART it[29];
	MMP_ULONG dummy[3];
	MMP_ULONG ulTail;				// check unit for the correctness of the AIT_STORAGE_INDEX_TABLE (0x'V''S''N''2')
}AIT_STORAGE_INDEX_TABLE2;

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

extern const FS_DEVICE_TYPE    FS_RAMDISK_Driver;       /* RAMDISK_DRIVER function table */
extern const FS_DEVICE_TYPE    FS_WINDRIVE_Driver;      /* WINDRIVE_DRIVER function table */
extern const FS_DEVICE_TYPE    FS_SMC_Driver;           /* SMC_DRIVER function table */
extern const FS_DEVICE_TYPE    FS_MMC_CardMode_Driver;  /* MMC_DRIVER SPI function table */
extern const FS_DEVICE_TYPE    FS_MMC1_CardMode_Driver; /* MMC_DRIVER SPI function table */
extern const FS_DEVICE_TYPE    FS_MMC_SPI_Driver;       /* MMC_DRIVER CardMode function table */
extern const FS_DEVICE_TYPE    FS_IDE_Driver;           /* IDE_CF_DRIVER function table */
extern const FS_DEVICE_TYPE    FS_FLASH_Driver;         /* FLASH_DRIVER function table */
extern const FS_DEVICE_TYPE    FS_SFLASH_Driver;        /* Serial FLASH_DRIVER function table */
extern const FS_DEVICE_TYPE    FS_GENERIC_Driver;       /* GENERIC_DRIVER function table */
extern const FS_DEVICE_TYPE    FS_NAND2K_Driver;        /* Nand2k driver function table */
extern const FS_DEVICE_TYPE    FS_MEMORY_Driver;        /* Memory driver function table */
extern const FS_DEVICE_TYPE    FS_SFNAND_Driver;        /* SFNAND_DRIVER function table <SPI Nand Flash><SFNAND> */

//==============================================================================
//
//                              FUNCTIONS
//
//==============================================================================

MMP_ERR MMPF_STORAGE_RegisterFSDevie(STORAGE_UNIT *pFSDevice, MMP_ULONG ulCacheMemoryAddr, MMP_ULONG ulCacheMemoryLen, 
                                                                                    MMP_ULONG ulFreeClusterTableAddr, MMP_ULONG ulFreeClusterTableLen);
MMP_ERR MMPF_STORAGE_RegisterMSDCDevie(STORAGE_UNIT *pMSDCDevice);
STORAGE_UNIT *MMPF_STORAGE_GetFSDevie(MMP_ULONG ulIndex);
STORAGE_UNIT *MMPF_STORAGE_GetMSDCDevie(MMP_ULONG ulIndex);
void MMPF_STORAGE_GetFSCacheMem(MMP_ULONG ulIndex, MMP_ULONG *pulCacheMemoryAddr, MMP_ULONG *pulCacheMemoryLen);
void MMPF_STORAGE_GetMaxFSDevie(MMP_ULONG *pulMaxFSDevice);
void MMPF_STORAGE_GetMaxMDSCDevie(MMP_ULONG *pulMaxMSDCDevice);
void MMPF_STORAGE_GetFSFreeClusterTable(MMP_ULONG ulIndex, MMP_ULONG *pulFreeClusterTableAddr, MMP_ULONG *pulFreeClusterTableLen);

MMP_ERR  MMPF_STORAGE_AddFsDevice(void);
MMP_ERR  MMPF_STORAGE_AddMsdcDevice(MMP_UBYTE ubUnits);
MMP_ERR  MMPF_STORAGE_GetDevie(MMP_BYTE *pVolumeName, FS_DEVICE_TYPE **device, MMP_UBYTE *unit);
MMP_ERR  MMPF_STORAGE_ParsingFirstSector(void * tmpAddr, MMP_UBYTE bMaxNumber, STORAGE_PARTITION * pstPart, MMP_UBYTE *bNumber);
MMP_ERR  MMPF_STORAGE_DevStatus(MMP_UBYTE dev, MMP_UBYTE Unit);
MMP_ERR  MMPF_STORAGE_DevRead(MMP_UBYTE dev, MMP_UBYTE Unit, MMP_ULONG SectorAddr, MMP_ULONG NumSectors, void *pBuffer);
MMP_ERR  MMPF_STORAGE_DevWrite(MMP_UBYTE dev, MMP_UBYTE Unit, MMP_ULONG SectorAddr, MMP_ULONG NumSectors, void *pBuffer);
MMP_ERR  MMPF_STORAGE_GetSize(MMP_UBYTE dev, MMP_UBYTE Unit, MMP_ULONG *sectCount);
MMP_ERR  MMPF_STORAGE_UnMount(MMP_UBYTE dev);
MMP_ERR  MMPF_STORAGE_Mount(MMP_UBYTE dev);
MMP_ERR  MMPF_STORAGE_GetMaxPartition(MMP_UBYTE dev, MMP_UBYTE *bPartitionNum);

#endif //_MMPF_STORAGE_API_H_
