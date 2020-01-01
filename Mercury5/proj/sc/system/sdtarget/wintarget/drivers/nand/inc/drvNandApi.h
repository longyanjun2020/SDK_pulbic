/*********************************************************************
*   HEADER NAME:
*       drvNandApi.h
*
*---------------------------------------------------------------------
*
* Initial revision.
*********************************************************************/
#ifndef DRVNANDAPI_H
#define DRVNANDAPI_H

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
//#include <sys/bsdtypes.h>
#include <string.h>

typedef int Cyg_ErrNo;
//-------------------------------------------------------------------------------------------------
// LITERAL CONSTANTS
//-------------------------------------------------------------------------------------------------
#define NAND_SECTOR_SIZE                0x200
#define NAND_DIRECT_SECTOR_MULTIPLE     4
#define NAND_DIRECT_SIZE_MULTIPLE       (NAND_DIRECT_SECTOR_MULTIPLE * NAND_SECTOR_SIZE)
#define NAND_DIRECT_SECTOR_MAX          2048
#define NAND_DIRECT_SIZE_MAX            (NAND_DIRECT_SECTOR_MAX * NAND_SECTOR_SIZE)


//-------------------------------------------------------------------------------------------------
// Typedefs
//-------------------------------------------------------------------------------------------------
typedef enum EFLASHCONFIG
{
    FLASH_UNCONFIG = 0x0,
    FLASH_READY = 0x01,
    FLASH_WP = 0x02,
    FLASH_2KPAGE = 0x04,
    FLASH_16BIT = 0x08,
    FLASH_DUALMODE = 0x10,
    FLASH_CACHEPROGRAM = 0x20,
    FLASH_COPYBACK = 0x40,
    FLASH_MEDIACHANGE = 0x80
} FLASHCONFIG;

typedef enum EMAKER_CODE
{
    SAMSUMG = 0xEC,
    TOSHIBA = 0x98,
    RENESAS = 0x07,
    HYNIX   = 0xAD,
    ST      = 0x20,
    MICRON  = 0x2C
} MAKER_CODE;

typedef enum EFLASHTYPE
{
    TYPE_SLC = 0,
    TYPE_MLC,
    TYPE_AGAND
} FLASHTYPE;

typedef enum EFLASHPLANE
{
    ONE_PLANE = 0,
    TWO_PLANE,
    FOUR_PLANE,
//    EIGHT_PLANE,
} FLASHPLANE;

typedef struct _FREEBLOCKQUEUE
{
    u8 Head;
    u8 Tail;
    u8 Count;
} FREEBLOCKQUEUE;

typedef enum ENCRW_STATUS
{
    NCRW_STS_OK = 0,
    NCRW_STS_NOMEDIA = 0x1,
    NCRW_STS_PROGRAM_FAIL = 0x2,
    NCRW_STS_ECC_ERROR = 0x4,
    NCRW_STS_WRITE_PROTECT = 0x8,
    NCRW_STS_TIMEOUT = 0x10,
    NCRW_STS_ADDRESS_ERROR = 0x20
} NCRW_STATUS;

typedef enum _RW_DIR
{
    RW_READ = 0,
    RW_WRITE
} RW_DIRECTION;


typedef struct nand_operations_struct
{
    //NCRW_STATUS (*AUTOSCAN)(void);
    //NCRW_STATUS (*READ_CIS)(void);
#ifdef NAND_1KLUT
    void (*BUILD_LUT)(u8, u8);
#else
    void (*BUILD_LUT)(u8);
#endif
    NCRW_STATUS(*NAND_RW)(RW_DIRECTION , u32 , u32, u32);
} nand_operations;
#if 1
typedef struct _PARTITION_INFO1
{
    u16 u16FirstBlock;
    u16 u16TotalBlocks;
    u8  IsFAT;
    u32 u32Capacity;
} PARTITION_INFO1;
#endif
typedef struct _NAND_FLASH_INFO
{
    u16 u16NC_CFG0;
    FLASHCONFIG eFlashConfig;
    MAKER_CODE eMaker;
    u8 u8ID;
    u8 u8PagesPerBlock;
    u8 u8SecNumofBlk;
    u8 u8Pageshift;
    u8 u8AddrWidth;
    //u8 u8Speed;
    u16 u16BlocksPerCS;
    u32 u32Capacity;
    FLASHTYPE eflashtype;
    FLASHPLANE eflashplane;
    u8 u8CIS_BLOCK;
    u8 u8CurZone;
    //u8 bCurField;
#ifndef CACHE_3SET
    u8 WriteBack;
    u32 u32PreSource[2];
    u32 u32PreFree[2];
    u16 u16PreBlock;
    u16 u16PreSector;
#else
    struct _WRITE_BACK_QUEUE WriteBackQueue[WRITEBACKQUEUE_SIZE];
    struct _WRITE_BACK_QUEUE *CurWriteBackQueue;
#endif
    u16 u8WaitEvent;
    struct _FREEBLOCKQUEUE FreeQueue;
    struct nand_operations_struct *nand_op;
#if defined(CYGCFG_NAND_MULTI_LUT)
    u8 u8MULTI_LUT_ACTIVE;
    NAND_LUT *_pcurLUT;
    u8 u8LUT1Zone;
    struct _FREEBLOCKQUEUE FreeQueue1;
    struct _FREEBLOCKQUEUE *CurFreeQueue;
    u8 u8LUT2Zone;
    u8 preUsedLUT;
    struct _FREEBLOCKQUEUE FreeQueue2;
#endif
    u16 u16ReservedBlocks;  // reserved for image & user setting
#ifdef CYGCFG_SPLITBLOCK
    u16 *_pu16SBLUT;
    u16 *_pu16SBIDX;
#endif
    u8 u8BOOT_MODE;
#if 1
    u8 u8PartitionNo;
    struct _PARTITION_INFO1 sPartition_Info[7];
#endif
    u8 u8FirstLogiPartNo;
    u8 u8SecNumofBlkBits;
#if defined(CIS_V03)
    u16 u16FirstFATBlock;
    u8 u8Total_FAT_No;
#endif
} NAND_FLASH_INFO;


//-------------------------------------------------------------------------------------------------
// Defines
//-------------------------------------------------------------------------------------------------
/* return status for drvNAND_FLASH_INIT in NAND RAM driver */
#define ERR_DRV_NAND_NOERR  0
#define ERR_DRV_NAND_FATAL  1
#define ERR_DRV_NAND_BADID  2
#define ERR_DRV_NAND_BADCIS 3
#define ERR_DRV_NAND_NOCIS  4

#define NAND_PHYPART_TYPE          0
#define NAND_LOGPART_TYPE_FAT      1
#define NAND_LOGPART_TYPE_CUS      2
#define NAND_LOGPART_TYPE_NRAI     3
#define NAND_PHYPART_TYPE_CUS      4

//-------------------------------------------------------------------------------------------------
// Function Prototypes
//-------------------------------------------------------------------------------------------------
/* NOTE: drvNAND_FLASH_INIT returns ERR_DRV_NAND_XXX code in RAM driver,
   and returns TRUE or FALSE in ROM driver */
int     drvNAND_FLASH_INIT(void);
bool    MDrv_NAND_HWInit(void);
int     MDrv_NAND_GetInitStat(void);
void    MDrv_NAND_ForceWriteBack(void);
u8      MDrv_NAND_GetCisBlk(void);
s32     MDrv_NAND_GetPartRowAddr(u8 u8PartitionNo);
s32     MDrv_NAND_GetPartBlkCount(u8 u8PartitionNo);
u32     MDrv_NAND_GetSectNumofBlk(void);
s32     MDrv_NAND_GetPageNumofBlk(void);
u16     MDrv_NAND_GetPageSize(void);
Cyg_ErrNo nand_image_read_ROM(u8    u8PartitionNo,
                        void  *buf,
                        u32   len,
                        u32   block_num);
Cyg_ErrNo nand_image_read(u8    u8PartitionNo,
                        void  *buf,
                        u32   len,
                        u32   block_num,
                        bool  bsearch);
Cyg_ErrNo nand_image_write(u8 u8PartitionNo,
                        void  *buf,
                        u32 u32sectLen,
                        u32 u32sectNum,
                        bool  bsearch);

/* Below only for NAND driver in RAM */
u32     MDrv_NAND_GetPhyCapacity(void);
u32     MDrv_NAND_GetFATCapacity(u8 u8Disk_No);
u32     MDrv_NAND_GetID(void);
void    MDrv_NAND_GetName(u8 *strname, u16 u16len);
bool    MDrv_NAND_FLASH_DISK_INIT(u8 u8Disk_No,u8 *DevName);
u8          nand_fat_disk_count(void);
Cyg_ErrNo   nand_fatu_read(void *buf, u32 len, u32 block_num);
Cyg_ErrNo   nand_fatu_write(const void *buf, u32 len, u32 block_num);
Cyg_ErrNo   nand_fath_read(void *buf, u32 len, u32 block_num);
Cyg_ErrNo   nand_fath_write(const void *buf, u32 len, u32 block_num);
Cyg_ErrNo   nand_disk_e2p_read(u8 u8PATNo,void *buf, u32 len, u32 block_num);
Cyg_ErrNo   nand_disk_e2p_write(u8 u8PATNo,const void *buf, u32 len, u32 block_num);
u32         nand_disk_e2p_capacity(u8 u8PATNo);
Cyg_ErrNo   nand_disk_backtrace_read(void *buf, u32 len, u32 block_num);
Cyg_ErrNo   nand_disk_backtrace_write(const void *buf, u32 len, u32 block_num);
u32         nand_disk_backtrace_capacity(void);
Cyg_ErrNo   nand_disk_cus_read(void *buf, u32 len, u32 block_num);
Cyg_ErrNo   nand_disk_cus_write(void *buf, u32 len, u32 block_num);
u32         nand_disk_cus_capacity(void);
bool        nand_disk_cus_inphysical(void);
Cyg_ErrNo   nand_NRAI_write(const void *buf, u32 len, u32 block_num);
Cyg_ErrNo   nand_NRAI_read(void *buf, u32 len, u32 block_num);
u32         nand_disk_NRAI_capacity(void);

//-------------------------------------------------------------------------------------------------
// Disk Operation Function Table
//-------------------------------------------------------------------------------------------------
#if 0
typedef struct diskOpFuncTab_s
{
    Cyg_ErrNo   (*read)(void *, u32, u32);
    Cyg_ErrNo   (*write)(const void *, u32, u32);
    void        (*phyRead)(u32, u8 *, u16);
    u8          (*phyWrite)(u32, u8 *, u16, u8);
    void        (*info)(u8 *);
    u8          (*eraseBlk)(u32);
    void        (*rddWrite)(u8 *, u8);
    void        (*ejectIns)(u8);
    u32         (*getCap)(void);
    u8          (*chkRdy)(void);
} DiskOpFuncTab_t;

#define fpnand_read         ptrNandOps->read
#define fpnand_write        ptrNandOps->write
#define fpnand_phyRead      ptrNandOps->phyRead
#define fpnand_phyWrite     ptrNandOps->phyWrite
#define fpnand_info         ptrNandOps->info
#define fpnand_eraseBlk     ptrNandOps->eraseBlk
#define fpnand_rddWrite     ptrNandOps->rddWrite
#define fpnand_ejectIns     ptrNandOps->ejectIns
#define fpnand_getCap       ptrNandOps->getCap
#define fpnand_chkRdy       ptrNandOps->chkRdy
#endif

#endif  // DRVNANDAPI_H
