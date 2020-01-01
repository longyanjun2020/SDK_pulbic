#ifndef __SYS_SYS_MMAP_MGR_H__
#define __SYS_SYS_MMAP_MGR_H__

#include "sys_sys_mmu.h"

#if defined (__RTK_OVER_R2__)
#if defined (__MEM_MAP_64MB__)
#define MMAP_PAGE_BITS   9  // 4MB address space/MMU_PAGE_SIZE
#else
#define MMAP_PAGE_BITS   8  // 2MB address space/MMU_PAGE_SIZE
#endif
#else //__MMAP__ with ARM
#define MMAP_PAGE_BITS   7  // 512KB address space/MMU_PAGE_SIZE
#endif

#define MMAP_PAGES          (1<<MMAP_PAGE_BITS)

#define MMAP_IDX_BITS     5
#define MMAP_IDXS             (1<<MMAP_IDX_BITS)

#define MMAP_FD_FENCE (-1)
#define MMAP_FD_CUS     (0xabbccdd)

//error code
#define MMAP_FAILED ((void*)-1)

//protection
#define PROT_NONE        0x00 // Pages may not be accessed.
#define PROT_READ        0x01 // Pages may be read.
#define PROT_WRITE      0x02 // Pages may be written.
#define PROT_EXEC         0x04 // Pages may be executed.

// flags
#define MAP_FIXED              0x00000010 // Interpret addr exactly.
#define MAP_ANON               0x00000020
#define MAP_PRIVATE          0x00000002 // Changes are private.
#define MAP_SHARED           0x00000001 // Changes are shared.
//#define MAP_PHYS                0x00000010
#define MAP_STACK              0x00020000
#define MAP_POPULATE        0x00008000
//#define MAP_CANRECPAGES 0x00000080

#define MMAP_IDX_PAGE_BITMAPS_SIZE ((MMAP_IDXS+7)>>3)

typedef struct MsMmap_t_
{
	u32 start;
	u32 end;
	int prot;
	int flags;
	int fd;
	long offset;
	u32 pagenum;
	u32 lr;
	s16 idx;
	struct MsMmap_t_ *next;
} MsMmap_t, *pMsMmap_t;

typedef struct MsMmapPageEntry_t_
{
	u32 inused   :1;
	u32 valid      :1;
	u32 dirty      :1;
	u32 mmap    :MMAP_IDX_BITS;
	u32 page      :MMAP_PAGE_BITS;
} MsMmapPageEntry_t, *pMsMmapPageEntry_t;

typedef struct MsMmapLogEntry_t_
{
    u32 vaddr;
    u32 task;
    u32 tick;
    u32 line;
} MsMmapLogEntry_t, *pMsMmapLogEntry_t;

/**
 * @brief Runtime library init.
 * @return void
 */
void MsmmapRtInit(void);

/**
 * \brief Map files into memory
 *  It creates a new mapping in the virtual address space.
 *  The starting address for the new mapping is specified in addr.
 *  The length argument specifies the length of the mapping.
 *  If addr is NULL, then the kernel chooses the address at which to create the mapping;
 *  this is the most portable method of creating a new mapping.
 *  The kernel, however, only treats the addr argument as NULL for portable issue.
 *  The contents of a file mapping are initialized using length bytes starting at offset
 *  offset in the file referred to by the file descriptor fd.
 * \param[in] addr must be NULL
 * \param[in] length mapping length
 * \param[in] prot desired memory protection of the mapping
 * \param[in] flags useless right now
 * \param[in] fd file description of the mapped file
 * \param[in] offset must be a multiple of the page size
 * \return void* on success, it returns a pointer to the mapped area or on failure MMAP_FAILED
 */
void *Msmmap(void *addr, u32 length, int prot, int flags, int fd, long offset);


/**
 * \brief Unmap files into memory
 *  It deletes the mappings for the specified address range, and causes further references
 *  to addresses within the range to generate invalid memory references.
 *  The address addr must be a multiple of the page size. All pages containing a part of the
 *  indicated range are unmapped, and subsequent references to these pages will generate exception.
 * \param[in] addr virtual space got from Msmmap
 * \param[in] length mapping length
 * \return int on success, it returns 0, on failure -1
 */
int Msmunmap(void *addr, u32 length);

pMsMmap_t MsMmapFind(u32 vaddr);

pMsMmapPageEntry_t MsMmapPageEntryFind(u32 vaddr, u16 *entry, u32 *ppaddr, pMsMmap_t *pMmap);

int MsMmapFindFdByAddr(u32 vaddr);

u8 *MsMmapGetPage(u16 *idx, u16 mmap, pMsMmapPageEntry_t *pMmapPageEntry, u16 *entry, pMsMmap_t *pMmap);

void MsMmapFreePage(u16 idx);

s32 MsMmapNandLoadCus(u32 offset, u8 *pBuf, u32 length);

u32 MsMmapGetMmapPageTableSize(void);

u32 MsMmapGetMmapCusEndAddr(void);

u32 MsMmapGetMmapPageEntry(u32 vaddr);

u32 MsMmapGetMmapEndAddr(void);

u32 MsMmapGetMmapPageEntryNum(void);

bool MsMmapIsMmapAddr(u32 vaddr);

u32 MsMmapGetMmapPageEntryPos(void);

u32 MsMmapGetPageAddr(u32 pageIdx);

#endif  /* __SYS_SYS_MMAP_MGR_H__ */

