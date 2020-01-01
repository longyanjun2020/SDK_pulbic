#ifndef __SYS_SYS_DPM_MGR_H__
#define __SYS_SYS_DPM_MGR_H__
#include "sys_MsWrapper_cus_os_int_pub.h"
#include "sys_arm_copro.h"
#include "sys_MsWrapper_cus_os_util.h" //pFreeEnvelope_t definition
#include "sys_sys_mmu.h"
#include "mdl_vfs_file.ho"
#include "sys_traces.ho"
#include "sys_sys_arm.h"
#include "mdl_vm_rai_id.h"

#define REG32(add) *((volatile unsigned long *)(add))
#define MEM32(add) *((volatile unsigned long *)(add))

#define TEST_DP_DATA_START_ADDR 0xD8000000
#define TEST_DP_DATA_END_ADDR 0xD801FFFF
#define TEST_DP_DATA_LENGTH 0x20000

#define DPM_MAGIC_LENGTH 4
#define DPM_NAME_LENGTH 12

#define DPM_TEXT_BASIC_POOL_PHY_PAGES 32
#define DPM_DATA_BASIC_POOL_PHY_PAGES 8
#define DPM_TEXT_EXTRA_POOL_PHY_PAGES 8
#define DPM_DATA_EXTRA_POOL_PHY_PAGES 8

#define DPM_MAX_PAGES 128

#define DPM_RESTORE_LOWER_BOUND_PHY_PAGES 0

#if defined (__RTK_OVER_R2__)
#define DPM_CLK_ALG     0
#else
#define DPM_CLK_ALG     1
#endif
#define DPM_CLK_REF_CNT 1

#define SYS_DPM_RAI_ITEM_START_ID(raiId)    M_##raiId##_START = (SYS_DPM_RAI_START_ID + ((raiId & 0x000000FF) << 16))
#define SYS_DPM_RAI_ITEM_END_ID(raiId)      M_##raiId##_END

#define EMMI_SLDPM_CLIENT_SYS_TEXT_LOWER_BOUND_PHY_PAGES DPM_TEXT_BASIC_POOL_PHY_PAGES
#define EMMI_SLDPM_CLIENT_SYS_DATA_LOWER_BOUND_PHY_PAGES DPM_DATA_BASIC_POOL_PHY_PAGES
#define EMMI_SLDPM_CLIENT_JAVA_TEXT_LOWER_BOUND_PHY_PAGES 0
#define EMMI_SLDPM_CLIENT_JAVA_DATA_LOWER_BOUND_PHY_PAGES 64
#define EMMI_SLDPM_CLIENT_MIDI_TEXT_LOWER_BOUND_PHY_PAGES 0
#define EMMI_SLDPM_CLIENT_MIDI_DATA_LOWER_BOUND_PHY_PAGES 32

#define __RO_CODE_NOT_IN_DPM__  __attribute__((section(".ro_code_not_in_dpm")))
#define __RO_DATA_NOT_IN_DPM__  __attribute__((section(".ro_data_not_in_dpm")))

enum
{
    DPM_TEXT_PHY_PAGE_POOL = 0,
    DPM_DATA_PHY_PAGE_POOL
};

typedef enum {
    DPM_APP_NONE = 0,
    DPM_APP_EMMI_SLDPM,
    DPM_APP_EXAMPLE,
    DPM_APP_EML_MAIN,
    DPM_APP_LAST,
    DPM_APP_INVALID = 255
} _DpmAppId_e;

typedef enum {
    DPM_SLOT_16M0M_POOL0,
    DPM_SLOT_1M1M_EXAMPLE,
    DPM_SLOT_1M128K_POOL0,
    DPM_SLOT_LAST
} _DpmSlotNum_e;

typedef enum {
    DPM_OK = 0,
    DPM_NOT_FOUND = 1,
    DPM_IS_FOUND = 2,
    DPM_LIST_EMPTY = 3,
    DPM_FAILED = 4,
    DPM_ARG_ERR = 5,
    DPM_MEM_ERR = 6,
    DPM_BASIC_POOL_NOT_REMOVABLE = 7,
    DPM_MORE_THAN_UPPER_BOUND_PHY_PAGES = 8,
    DPM_LESS_THAN_LOWER_BOUND_PHY_PAGES = 9,
    DPM_SHRINK_NO_EFFECT = 10,
} _DpmRetCode_e;

typedef enum {
  DPM_FROM_CUS,
  DPM_FROM_SD,
  DPM_FROM_INT_MEM,
} _sys_dpm_load_pos_e;

enum {
    DPM_EMMI_SLDPM_CLIENT_SYS = 0,
    DPM_EMMI_SLDPM_CLIENT_JAVA,
    DPM_EMMI_SLDPM_CLIENT_MIDI,
    DPM_EMMI_SLDPM_CLIENT_LAST,
};

enum {
    DPM_EXAMPLE_CLIENT_SYS = 0,
    DPM_EXAMPLE_CLIENT_LAST,
};

enum {
    SYS_DPM_RAI_ITEM_START_ID(DPM_APP_EMMI_SLDPM),
        SYS_DPM_RAI_ITEM_EMMI_SLDPM_TEXT_BASIC_POOL_PHY_PAGES,                  /* 0x05000001 */
        SYS_DPM_RAI_ITEM_EMMI_SLDPM_DATA_BASIC_POOL_PHY_PAGES,                  /* 0x05000002 */
        SYS_DPM_RAI_ITEM_EMMI_SLDPM_CLIENT_SYS_TEXT_LOWER_BOUND_PHY_PAGES,      /* 0x05000003 */
        SYS_DPM_RAI_ITEM_EMMI_SLDPM_CLIENT_SYS_DATA_LOWER_BOUND_PHY_PAGES,      /* 0x05000004 */
        SYS_DPM_PAI_ITEM_EMMI_SLDPM_CLIENT_JAVA_TEXT_LOWER_BOUND_PHY_PAGES,     /* 0x05000005 */
        SYS_DPM_PAI_ITEM_EMMI_SLDPM_CLIENT_JAVA_DATA_LOWER_BOUND_PHY_PAGES,     /* 0x05000006 */
        SYS_DPM_PAI_ITEM_EMMI_SLDPM_CLIENT_MIDI_TEXT_LOWER_BOUND_PHY_PAGES,     /* 0x05000007 */
        SYS_DPM_PAI_ITEM_EMMI_SLDPM_CLIENT_MIDI_DATA_LOWER_BOUND_PHY_PAGES,     /* 0x05000008 */
    SYS_DPM_RAI_ITEM_END_ID(DPM_APP_EMMI_SLDPM),
};

enum {
    DPM_PAGING = 0,
    MMAP_PAGING
};

typedef u8 DpmAppId_e;
typedef u8 DpmSlotNum_e;
typedef u8 DpmRetCode_e;
typedef u8 DpmFileLoc_e;

typedef struct DpmFileHeader_t_
{
	char szMagic[DPM_MAGIC_LENGTH];								// dlm magic number "DLMM"
	u32 nHeaderLen; 	// DLM FILE HEADER LENGTH, include MAGIC "DLMM"
	char szDpmName[DPM_NAME_LENGTH];						// DLM Name
	u32 nTextSize;			// TEXT  length
	u32 nDataSize;          // DATA length
	u32 nBssSize;           // BSS length
	u32 nNumFuncs;          // how many export functions
	u32 nCheckSum;
} DpmFileHeader_t, *pDpmFileHeader_t;

typedef struct DpmCusInfo_t_
{
    u32 nStartOffset;
    u32 nTextSize;
    u32 nDataSize;
    u32 nTextOffset;
    u32 nDataOffset;
    u32 nTextStartVA;
    u32 nDataStartVA;
    u8* pStartPtr;
    bool bCmprs;
} DpmCusInfo_t, *pDpmCusInfo_t;

typedef struct DpmPageTableEntry_t_
{
	u8 valid        :1;
	u8 dirty        :1;
	u8 page;        /* should be assigned number of bits */
#if DPM_CLK_ALG
	u8 enable       :1;
	u8 ref;         /* Ref for clock algorithm. It should be configurable for n-th chance */
#endif
} DpmPageTableEntry_t, *pDpmPageTableEntry_t;

typedef struct DpmPhyPagePool_t_
{
    u16* pDpmPageIdxTable;
    u8*  pDpmPhyPages;
    struct DpmPhyPagePool_t_* pNextPool;
} DpmPhyPagePool_t, *pDpmPhyPagePool_t;

typedef struct DpmClientRegEntry_t_
{
    u32 nTextLowerBoundPhyPages;
    u32 nDataLowerBoundPhyPages;
} DpmClientRegEntry_t, *pDpmClientRegEntry_t;

typedef struct DpmCtrlBlk_t_
{
        pFreeEnvelope_t ptrDpmTextPageFree;
        pFreeEnvelope_t ptrDpmDataPageFree;
        u32 nbDpmTextFreePageCount;
        u32 nbDpmDataFreePageCount;
        u32 nbDpmTextVictimPhyPageIdx;
        u32 nbDpmDataVictimPhyPageIdx;
        u32 nbDpmTextPhyPages;
        u32 nbDpmDataPhyPages;
        u32 nbDpmTextVirPages;
        u32 nbDpmDataVirPages;
        pDpmPageTableEntry_t ptrDpmTextPageTable;
        pDpmPageTableEntry_t ptrDpmDataPageTable;
#if defined (__RTK_OVER_R2__)
        u16* ptrDpmTextPageIdxTable;
        u16* ptrDpmDataPageIdxTable;
        u8* ptrDpmTextPhyPages;
        u8* ptrDpmDataPhyPages;
#else
        s32 nbDpmTextFreePhyPageIdx;
        s32 nbDpmDataFreePhyPageIdx;
        pDpmPhyPagePool_t ptrDpmTextPhyPagePoolList;
        pDpmPhyPagePool_t ptrDpmDataPhyPagePoolList;
        u32 nbDpmTextExtraPools;
        u32 nbDpmDataExtraPools;
        u32 nbDpmTextBasicPoolPhyPages;
        u32 nbDpmDataBasicPoolPhyPages;
        u32 nbDpmTextExtraPoolPhyPages;
        u32 nbDpmDataExtraPoolPhyPages;
        u32 nbDpmTextUpperBoundPhyPages;
        u32 nbDpmDataUpperBoundPhyPages;
        u32 nbDpmTextLowerBoundPhyPages;
        u32 nbDpmDataLowerBoundPhyPages;
        pDpmClientRegEntry_t ptrDpmClientRegTable;
        u32 nbDpmClients;
#endif
        u32 textVirStartAddr;
        u32 dataVirStartAddr;
        u16* dpmFile;
        u16* dpmDataFile;
        u32 textSectOffset;
        u32 dataSectOffset;
        u8  dpmFileLoc;
        u8  dpmName[DPM_NAME_LENGTH];
        pFunc_t* ptrDpmJmpTbl;
        VFS_FILE* dpmFd;
        pDpmCusInfo_t pDpmCusInfo;
} DpmCtrlBlk_t, *pDpmCtrlBlk_t;

typedef struct DpmAppRegEntry_t_
{
	u8 Dpm_File_Name[255];						// DPM File Name
	pFunc_tbl_init_t func_tbl_init;
    DpmSlotNum_e dpm_slot_num;
    u32 text_vir_pages;
    u32 data_vir_pages;
    u32 text_phy_pages;
    u32 data_phy_pages;
} DpmAppRegEntry_t, *pDpmAppRegEntry_t;

typedef struct DpmSlotRegEntry_t_
{
        u32                     nDpmTextStartAddr;
        u32                     nDpmTextEndAddr;
        u32                     nDpmDataStartAddr;
        u32                     nDpmDataEndAddr;
        u8                      bDpmIsLoaded;
        DpmAppId_e              nDpmAppId;
        pDpmCtrlBlk_t           pDpmCtrlBlk;
        struct DpmSlotRegEntry_t_*   pDpmNext;
} DpmSlotRegEntry_t, *pDpmSlotRegEntry_t;

typedef struct GdbInsEntry_t_
{
        u32                     vaddr;
        void*                   pBuf;
        u32                     len;
        struct GdbInsEntry_t_*   pGdbInsNext;
} GdbInsEntry_t, *pGdbInsEntry_t;

extern void sys_UartPrintf(const char *fmt, ...);
extern void sys_Invalidate_inst_cache(void);
extern void sys_Invalidate_data_cache(void);
extern void cp15_write_reg8_invalidate_tlb_mva(u32 val);

void mmu_dump_coarse_page_table(u32* table_addr);
void mmu_dump_translation_table(u32 vaddr, u32 size);
u32 sys_paging_insert_page_table_entry(u32 vAddr/* 4KB aligned */, u32 pAddr/* 4KB aligned */, u32 ap, u8 type);
u32 sys_paging_invalidate_page_table_entry(u32 vAddr/* 4KB aligned */, u8 type);
u32 sys_paging_reset_coarse_page_table(u32 vAddr/* 1MB aligned */, u8 type);
void sys_dpm_data_abort_schedule_dsr(u32 vaddr);
void sys_dpm_prefetch_abort_schedule_dsr(u32 vaddr);
u8 sys_dpm_data_abort_handler(void);
u8 sys_dpm_prefetch_abort_handler(u32 ifar);

DpmRetCode_e DpmIsLoaded(DpmAppId_e nDpmAppId);
void DpmInvalidatePageTable(DpmSlotNum_e nDpmSlotNum);
void DpmInitSem(void);
DpmRetCode_e DpmInitList(DpmSlotNum_e dpmSlotNum, DpmAppId_e nDpmAppId, pDpmCtrlBlk_t pDpmCtrlBlk);
DpmRetCode_e DpmDeInitList(DpmAppId_e nDpmAppId);
s32 DpmNandLoadCus(u32 offset, u8 *pBuf, u32 length);
bool DpmIsEmmiSldpmEnabled(void);
bool DpmIsDpmTextAddr(u32 vaddr);
bool DpmIsDpmDataAddr(u32 vaddr);
pDpmCusInfo_t DpmGetNonDpmCusClientInfo(u32 vAddr);
bool DpmIsImeCusAddr(u32 vaddr);
bool DpmIsPlmnCusAddr(u32 vaddr);
bool DpmIsHandWritingCusAddr(u32 vaddr);
bool DpmIsRomRemapToEmmiSldpmNeighborhood(void);
u32 DpmGetRomRemapStartAddr(void);
u32 DpmGetRomRemapAddrLen(void);
u32 DpmGetPhyPages(u8 type, pDpmCtrlBlk_t pDpmCtrlBlk);
u8 DpmAddPhyPagePool(u32 nNumPools, u8 type, pDpmCtrlBlk_t pDpmCtrlBlk);
u8 DpmRemovePhyPagePool(u32 nNumPools, u8 type, pDpmCtrlBlk_t pDpmCtrlBlk);
u8 DpmEnlargeToNumberOfPhyPages(u32 nNumPages, u8 type, pDpmCtrlBlk_t pDpmCtrlBlk);
u8 DpmShrinkToLowerBoundPhyPages(u8 type, pDpmCtrlBlk_t pDpmCtrlBlk);
u8 DpmSetLowerBoundPhyPages(u8 nClient, u32 nNumPages, u8 type, pDpmCtrlBlk_t pDpmCtrlBlk);
u32 DpmGetLowerBoundPhyPages(u8 type, pDpmCtrlBlk_t pDpmCtrlBlk);
pDpmCtrlBlk_t DpmGetEmmiSldpmDpmCtrlBlk(void);
bool DpmAutoShrinkEnabled(void);
bool DpmAutoShrinkWithMallocFail(void);
bool DpmInitRaiObjects(u32 nStartRaiIdx, u32 nEndRaiIdx, u32 *pInitRaiVals);
s32 DpmReadRaiObject(u32 ident, u16 start, u16 length, void * data);
bool DpmInitCusInfo(u8 nDpmAppId, pDpmCusInfo_t pDpmCusInfo);
u8 DpmLoadModule(u8 nDpmAppId, pDpmCtrlBlk_t pDpmCtrlBlk);
u8 DpmUnloadModule(u8 nDpmAppId);
pDpmCtrlBlk_t DpmSetEmmiSldpmDpmCtrlBlk(void);
pDpmCtrlBlk_t DpmSetExampleDpmCtrlBlk(void);
u32 DPMStartAddress(void);

#endif  /* __SYS_SYS_DPM_MGR_H__ */

