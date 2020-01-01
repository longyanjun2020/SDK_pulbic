#ifndef __SYS_SYS_DLM_MGR_H__
#define __SYS_SYS_DLM_MGR_H__

#ifdef __SUPPORT_BUS_FSP_SPI__
/* If __DLM_REDUCE_INTERFACE__ is defined,
 * there is only one DLM module can be load!
 */
#define __DLM_REDUCE_INTERFACE__
#endif


#define DLM_NAME_LENGTH		12
#define DLM_MAGIC_LENGTH	4

//#define 	DLM_NAME_LEN			32
#define  	SERVICE_NAME_LEN   32

#define DLM_VIRTUAL_CODE_BASE_ADDR		0x1D000000
#define DLM_VIRTUAL_DATA_BASE_ADDR		0x1D800000

typedef void Service_InitFn(void);
// typedef Dynamic_ServiceFn (  );
typedef int Dynamic_ServiceFn ();

typedef enum {
  DLM_FROM_CUS,
  DLM_FROM_SD,
  DLM_FROM_INT_MEM,
} _sys_dlm_load_pos_e;

#define LOAD_FROM_SD_OR_INT_MEM(X) ((X==DLM_FROM_SD)||(X==DLM_FROM_INT_MEM))


typedef enum {
  SYS_DLM_OK= 0,                         ///< No error - the function call was successfull
  SYS_DLM_LOADED,
  SYS_DLM_NOTFOUND,
  SYS_DLM_NOLOADED,
  SYS_DLM_READERR,
  SYS_DLM_MEMERR,
  SYS_DLM_CHECKERR,
  SYS_DLM_FILEERR,
  SYS_DLM_OTHERERR,
} _sys_dlm_ErrCode_e;

typedef u8 sys_dlm_ErrCode_e;
/*
typedef struct _sys_dlm_svc
{
    Dynamic_ServiceFn *fn;
}DlmServiceEntry;
*/

enum {
    DLM_CUS_FOUND = 0,
    DLM_CUS_NOTFOUND,
    DLM_CUS_MEMERR,
    DLM_CUS_READERR,
};

typedef struct _DLM_Header_
{
	char Magic[DLM_MAGIC_LENGTH];								// dlm magic number "DLMM"
	unsigned int  Header_Length; 	// DLM FILE HEADER LENGTH, include MAGIC "DLMM"
	char DLM_Name[DLM_NAME_LENGTH];						// DLM Name
	unsigned int  Text_Size;				// TEXT + RO DATA length
	unsigned int  Data_Size;       // RW DATA length
	unsigned int  Bss_Size;       // BSS length
	unsigned int  Num_Function;   // how many export functions
	unsigned int  checkSum;
} DLM_FILE_HEADER;


typedef struct _sys_dlm_
{
	u8 Dlm_Name[DLM_NAME_LENGTH];
	u8 Dlm_Ref_Cnt;
	u8 Dlm_Txt_Ready;
	u8 Dlm_Locked;
	u8 Dlm_Padded;
	u8 Dlm_AbsPos;
	u8 Reserved[3];
	u32 Dlm_Text_Size;
	u32 *pDlm_Loaded_Address;
	u32 *pDlm_DataBss_Address;
	Dynamic_ServiceFn **ppFn;
	struct _sys_dlm_ *pNext_SysDlm_Chunk;
} SysDlm_Chunk_t;

typedef struct _sys_dlm_mempool
{
	u8 * Pool_Start_Address;
	u8 * Pool_End_Address;
} SysDlm_MemPool_t;

typedef struct _sys_dlm_memnode
{
	u32 uChunk_Size;
	u8 *Start_Address;
	u8 *End_Address;
	struct _sys_dlm_memnode *pNext_SysDlm_MemNode;
} SysDlm_MemNode_t;

/* start of __RTK_OVER_ARM_SLDLM__ definition */
#define __RO_CODE_NOT_IN_SLDLM__  __attribute__((section(".ro_code_not_in_sldlm")))
#define __RO_DATA_NOT_IN_SLDLM__  __attribute__((section(".ro_data_not_in_sldlm")))
#define __RW_NOT_IN_SLDLM__  __attribute__((section(".rw_not_in_sldlm")))
#define __ZI_NOT_IN_SLDLM__  __attribute__((section(".zi_not_in_sldlm")))

#define SLDLM_PAGE_ENTRY_POS    12
#define SLDLM_MMU_PAGE_SIZE     (1 << SLDLM_PAGE_ENTRY_POS)
#define SLDLM_MMU_PAGE_MASK     ~((SLDLM_MMU_PAGE_SIZE - 1))
#define MAX_SYS_SLDLM_SIZE      12

typedef struct SldlmCtrlBlk_t_
{
    u32 *p2ndLevelPageTable;
    u8 *pSldlmPhyMem;
    u32 nSldlmSize;
    u32 nRefCnt;
} SldlmCtrlBlk_t, *pSldlmCtrlBlk_t;

enum {
    USR_SLDLM = 0,
    SYS_SLDLM
};

enum {
    EMI_SLDLM = 0,
    IMI_MUST_SLDLM,
    IMI_EMI_SLDLM,
};

#include "sys_sys_sldlm_cfg.h"

typedef enum {
    SLDLM_OK,
    SLDLM_NOT_FOUND,
    SLDLM_IS_FOUND,
    SLDLM_LIST_EMPTY,
    SLDLM_FAILED
} _SldlmRetCode_e;

typedef u8 SldlmAppId_e;
typedef u8 SldlmSlotNum_e;
typedef u8 SldlmRetCode_e;
typedef u8 SldlmFileLoc_e;

typedef struct SldlmAppRegEntry_t_
{
	char* pSldlmFileName;
    SldlmSlotNum_e nSldlmSlotNum;
    u8 nSldlmMemType;
} SldlmAppRegEntry_t, *pSldlmAppRegEntry_t;

typedef struct SldlmSlotRegEntry_t_
{
        u32                     nSldlmStartAddr;
        u32                     nSldlmEndAddr;
        u8                      bSldlmIsLoaded;
        SldlmAppId_e            nSldlmAppId;
        pSldlmCtrlBlk_t         pSldlmCtrlBlk;
        struct SldlmSlotRegEntry_t_*   pSldlmNext;
} SldlmSlotRegEntry_t, *pSldlmSlotRegEntry_t;

u32 sys_sldlm_insert_page_table_entry(u32 *p2ndLevelPageTable, u32 vAddr/* 4KB aligned */, u32 pAddr/* 4KB aligned */, u32 ap, u8 type);
u32 sys_sldlm_invalidate_page_table_entry(u32 *p2ndLevelPageTable, u32 vAddr/* 4KB aligned */, u8 type);
u32 sys_sldlm_reset_coarse_page_table(u32 vAddr/* 1MB aligned */, u8 type);
void dumpSldlmRegList(u8 type);
u32 SldlmGetUsrSldlmSlotRegTableSize(void);
bool SldlmIsSldlmAddr(u32 nAddr);
u8 SldlmGetSldlmMemType(SldlmAppId_e nSldlmAppId);
sys_dlm_ErrCode_e SldlmLoadModule(SldlmAppId_e nSldlmAppId, u8 position, char *sub_folder, u8 type);
sys_dlm_ErrCode_e SldlmUnloadModule(SldlmAppId_e nSldlmAppId, u8 type);
u32 SldlmVA2PA(u32 vaddr);
sys_dlm_ErrCode_e SldlmIncRefCnt(SldlmAppId_e nSldlmAppId, u8 type);
sys_dlm_ErrCode_e SldlmDecRefCnt(SldlmAppId_e nSldlmAppId, u8 type);
u32 SldlmGetRefCnt(SldlmAppId_e nSldlmAppId, u8 type);
sys_dlm_ErrCode_e SldlmLoadModuleIncRefCnt(SldlmAppId_e nSldlmAppId, u8 position, char *sub_folder, u8 type);
sys_dlm_ErrCode_e SldlmUnloadModuleDecRefCnt(SldlmAppId_e nSldlmAppId, u8 type);
bool IsSldlmAddr(u32 vAddr);
/* end of __RTK_OVER_ARM_SLDLM__ definition */

u32 compute_DLM_checksum(u32 startValue, u8 * buffer, u32 size);
sys_dlm_ErrCode_e Load_Dynamic_Module( u8 *, u8, u8, char *);
sys_dlm_ErrCode_e Unload_Dynamic_Module( u8 * );


SysDlm_Chunk_t * Lock_Dlm_Module( u8 * );
void UnLock_Dlm_Module( SysDlm_Chunk_t  *);


extern SysDlm_MemPool_t Dlm_MemPool;
extern SysDlm_MemNode_t *pDlm_Mem_FListHead, *pDlm_Mem_BListHead;

#endif  /* __SYS_SYS_DLM_MGR_H__ */

