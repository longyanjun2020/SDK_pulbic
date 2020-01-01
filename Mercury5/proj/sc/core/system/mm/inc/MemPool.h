/*******************************************************************************
 *
 *   MemPool.h: 
 *
 *   Memory pool interface.
 *
 *   Copyright 2010 by Caesar Chang.
 *
 *
 *   AUTHOR : Caesar Chang
 *
 *   VERSION: 1.0
 *
 *
*******************************************************************************/

#if !defined(_MEMPOOL_H__9CF77E9A_1769_452C_AF54_929F47DB47F7__INCLUDED_)
#define _MEMPOOL_H__9CF77E9A_1769_452C_AF54_929F47DB47F7__INCLUDED_



#define USHORT  unsigned short
#define ULONG   unsigned long
#define CHAR    char
#define VOID    void
#define BOOL    unsigned char
#define PBYTE   unsigned char*
#define PLONG   unsigned long*


#include "mmpf_typedef.h"
#include "os_wrap.h"

/*******************************************************************************
 *
 *   SETTING
 *
*******************************************************************************/

#define DISABLE_MEM_ALLOC_LOG
#define MEM_POOL_NAME_MAX                       8

//#define ENABLE_MEM_ALLOC_SERIAL_NO

/*******************************************************************************
 *
 *   MACROs
 *
*******************************************************************************/

#define ALIGN_UP( X, Y )                        (((X)+(Y)-1)/(Y)*(Y))
#define ALIGN_DOWN( X, Y )                      (((X))/(Y)*(Y))
#define ADDRESS(X) 		                        ( (char*) (X) )
#define ADDRESS_DIFF(X,Y)                       ( ADDRESS(X) - ADDRESS(Y) )

/*******************************************************************************
 *
 *   MEMORY POOL & CHUNK ATTRIBUTES
 *
*******************************************************************************/
// Flag of memory allocation
#define MEM_ALLOC_DEFAULT                       0x0000
#define MEM_ALLOC_FROM_TOP                      0x0000
#define MEM_ALLOC_FROM_BOTTOM                   0x0001
#define MEM_ALLOC_WAIT_FOREVER                  0x0002
#define MEM_ALLOC_DISABLE_ASSERT                0x0004
#define MEM_ALLOC_DISABLE_FAIL_PRINT            0x0008

#define MEM_ALLOC_ALIGNMENT_8B                  0x0010
#define MEM_ALLOC_ALIGNMENT_16B                 0x0020
#define MEM_ALLOC_ALIGNMENT_32B                 0x0040
#define MEM_ALLOC_ALIGNMENT_64B                 0x0080

#define MEM_ALLOC_MOVABLE                       0x0100
#define MEM_ALLOC_LEAK_MARK                     0x0200




/*******************************************************************************
 *
 *    CHUNK DUMP ATTRIBUTES
 *
 *        Internal dump attribute for MemPoolDumpChunk use only.
 *
*******************************************************************************/
#define MEM_CHUNK_DUMP_CHUNK                    0x0001
#define MEM_CHUNK_DUMP_NEXT_GAP                 0x0002

// Attribute of memory pool
#define MEM_POOL_ENABLE_DBG_INFO                0x0001
#define MEM_POOL_ENABLE_FOOTER                  0x0002
#define MEM_POOL_ENABLE_FROM_BOTTOM             0x0004

// Internal flag valuse
#define MEM_POOL_FLAG_MEMORY_FREED              0x00000001

/*******************************************************************************
 *
 *   INTERNAL DEFINE
 *
*******************************************************************************/

/*******************************************************************************
 *
 *   HEADER OF CHUNK
 *
*******************************************************************************/
typedef struct sMEM_CHUNK_HEADER
{
	USHORT uwSig;

	USHORT uwAttribute;

	ULONG ulSize;

#ifdef ENABLE_MEM_ALLOC_SERIAL_NO
	ULONG ulSerialNo;
#endif
    
	struct sMEM_CHUNK_HEADER* pPrev;
	struct sMEM_CHUNK_HEADER* pNext;
	
} MEM_CHUNK_HEADER, *PMEM_CHUNK_HEADER;

/*******************************************************************************
 *
 *   FOOTER OF CHUNK
 *
*******************************************************************************/
typedef struct sMEM_CHUNK_FOOTER
{
	USHORT uwSig;
	
	USHORT uwLine;
	
	CHAR*  szFilename;
	
} MEM_CHUNK_FOOTER, *PMEM_CHUNK_FOOTER;


/*******************************************************************************
 *
 *   HEADER OF MEMORY POOL
 *
*******************************************************************************/
typedef struct sMEM_POOL_HEADER
{
    ULONG               ulSig;
	ULONG				ulSize;
	ULONG				ulFreeSpace;
	ULONG				ulNumOfChunk;

#ifdef ENABLE_MEM_ALLOC_SERIAL_NO
	ULONG ulSerialNo;
#endif

	CHAR                szPoolName[MEM_POOL_NAME_MAX];

	MMPF_OS_FLAGID      idFlag;
    MMPF_OS_SEMID       idSemLock;
    
	// Mutex (for multi-thread locking)
	PMEM_CHUNK_HEADER	psChunkLast;
	MEM_CHUNK_HEADER	sChunkFirst;
	ULONG               ulPoolHandle;
    MEM_CHUNK_FOOTER    sChunkFirstFooter;
} MEM_POOL_HEADER, *PMEM_POOL_HEADER;

typedef PMEM_POOL_HEADER MEM_POOL_HANDLE;


/*******************************************************************************
 *
 *   CHUNK STATUS
 *
*******************************************************************************/
typedef enum 
{
	MEM_POOL_CHUNK_OK = 0,
	MEM_POOL_CURR_CHUNK_ERROR,
	MEM_POOL_PREV_CHUNK_ERROR,
	MEM_POOL_NEXT_CHUNK_ERROR,	
	MEM_POOL_CHUNK_FOOTER_ERROR
} MEM_POOL_CHUNK_STATUS;

/*******************************************************************************
 *
 *   MEMORY POOL APIs
 *
*******************************************************************************/

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      MemPoolReallocImp
 *
 *   DESCRIPTION
 *
 *      The realloc function changes the size of an allocated memory block.
 *      
 *
 *   ARGUMENTS
 *
 *      hPool  - The handle of the pool to destroy.
 *
 *      pbyAllocatedBuffer -  Pointer to previously allocated memory block.
 *
 *      ulNewSize    - The new memory size in byte.
 *
 *      szFilename   - The file name to log.
 *
 *      ulLineNumber - The line number to log.
 *
 *   RETURN
 *   
 *      NULL      - Failed.
 *      NON-NULL  - Successful. The value is the pointer of allocated buffer.
 *
*******************************************************************************/
void* 
MemPoolReallocImp( MEM_POOL_HANDLE hPool,VOID* pbyAllocatedBuffer,  ULONG ulNewSize, CHAR* szFilename, ULONG ulLineNumber );


/*******************************************************************************
 *
 *   FUNCTION
 *
 *      MemPoolAllocImpOnce
 *
 *   DESCRIPTION
 *
 *      Try to allocate memory from memory pool. It return immediately no matter
 *      successful or failed.
 *
 *   ARGUMENTS
 *
 *      hPool  - The handle of the pool to destroy.
 *
 *      ulSize - The memory size to allocate.
 *
 *      ulFlag - MEM_ALLOC_FROM_TOP     allocate memory from the top position 
 *                                      of the pool.
 *               MEM_ALLOC_FROM_BOTTOM  allocate memory from bottom position 
 *                                      of the pool.
 *
 *      szFilename   - The file name to log.
 *
 *      ulLineNumber - The line number to log.
 *
 *   RETURN
 *   
 *      NULL      - Failed.
 *      NON-NULL  - Successful. The value is the pointer of allocated buffer.
 *
*******************************************************************************/
void* 
MemPoolAllocImp( MEM_POOL_HANDLE hPool, ULONG ulSize, ULONG ulFlag, CHAR* szFilename, ULONG ulLineNumber );


/*******************************************************************************
 *
 *   FUNCTION
 *
 *      MemPoolCallocImp
 *
 *   DESCRIPTION
 *
 *      Try to allocate memory from memory pool. It handle wait forever flag in 
 *      this function.
 *
 *   ARGUMENTS
 *
 *      hPool  - The handle of the pool to destroy.
 *
 *      ulSize - The memory size to allocate.
 *
 *      ulFlag - MEM_ALLOC_WAIT_FOREVER wait forever until the memory is available.
 *               MEM_ALLOC_FROM_TOP     allocate memory from the top position 
 *                                      of the pool.
 *               MEM_ALLOC_FROM_BOTTOM  allocate memory from bottom position 
 *                                      of the pool.
 *               MEM_ALLOC_FROM_BOTTOM  allocate memory from bottom position 
 *
 *               MEM_ALLOC_FROM_BOTTOM  allocate memory from bottom position 
 *
 *
 *      szFilename   - The file name to log.
 *
 *      ulLineNumber - The line number to log.
 *
 *   RETURN
 *   
 *      NULL      - Failed.
 *      NON-NULL  - Successful. The value is the pointer of allocated buffer.
 *
*******************************************************************************/
void* 
MemPoolCallocImp( MEM_POOL_HANDLE hPool, ULONG ulNumber, ULONG ulSize, ULONG ulFlag, CHAR* szFilename, ULONG ulLineNumber );


/*******************************************************************************
 *
 *   FUNCTION
 *
 *      MemPoolFree
 *
 *   DESCRIPTION
 *
 *      Deallocates or frees a previous allocated memory buffer.
 *
 *   ARGUMENTS
 *
 *      hPool  - The handle of the pool to destroy.
 *
 *      pbyBuffer  - The previous allocated memory to free.
 *
 *      ulNewSize  - The new memory size to allocate.
 *
 *      szFilename - The file name to log.
 *
 *      ulLineNumber - The line number to log.
 *
 *   RETURN
 *   
 *      TRUE   - Successful.
 *      FALSE  - Failed.
 *
*******************************************************************************/
BOOL 
MemPoolFree( MEM_POOL_HANDLE hPool, void* pbyBuffer );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      MemPoolInit
 *
 *   DESCRIPTION
 *
 *      Initial a memory pool base of the memory buffer, Can only call once at system startup.
 *
 *   ARGUMENTS
 *
 *      pbyBuffer  - The buffer address to create the pool.
 *
 *   RETURN
 *   
 *
 *
*******************************************************************************/
void  
MemPoolInit(PBYTE pbyBuffer);

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      MemPoolCreate
 *
 *   DESCRIPTION
 *
 *      Create a memory pool base of the memory buffer.
 *
 *   ARGUMENTS
 *
 *      pbyBuffer  - The buffer address to create the pool.
 *      ulSize     - The size fo the input buffer.
 *      szPoolName - The name of the pool.
 *
 *   RETURN
 *   
 *      The handle of the pool created.
 *      NULL - Created failed.
 *
 *
*******************************************************************************/
MEM_POOL_HANDLE 
MemPoolCreate(PBYTE pbyBuffer, ULONG ulSize, CHAR* szPoolName );


/*******************************************************************************
 *
 *   FUNCTION
 *
 *      MemPoolDestroy
 *
 *   DESCRIPTION
 *
 *      Destroy a memory pool.
 *
 *   ARGUMENTS
 *
 *      hPool  - The handle of the pool to destroy.
 *
 *   RETURN
 *   
 *      TRUE   - Successful.
 *      FALSE  - Failed.
 *
 *
*******************************************************************************/
BOOL 
MemPoolDestroy(MEM_POOL_HANDLE hPool);


/*******************************************************************************
 *
 *   FUNCTION
 *
 *      MemPoolDumpInfo
 *
 *   DESCRIPTION
 *
 *      Dump the informations of the whole pool.
 *
 *   ARGUMENTS
 *
 *      hPool  - The handle of the pool.
 *      ulFlag - The flag of dumping.
 *
 *   RETURN
 *   
 *      TRUE   - Successful.
 *      FALSE  - Failed.
 *
*******************************************************************************/
BOOL 
MemPoolDumpInfo( MEM_POOL_HANDLE hPool, ULONG ulFlag );


/*******************************************************************************
 *
 *   FUNCTION
 *
 *      MemPoolGetMaxGap
 *
 *   DESCRIPTION
 *
 *      Get the max size of the gaps inside this pool.
 *
 *   ARGUMENTS
 *
 *      hPool  - The handle of the pool.
 *
 *   RETURN
 *   
 *      (ULONG) The size of the max gap.
 *
*******************************************************************************/

ULONG
MemPoolGetMaxGap( MEM_POOL_HANDLE hPool );


/*******************************************************************************
 *
 *   FUNCTION
 *
 *      MemPoolGetFreeSpace
 *
 *   DESCRIPTION
 *
 *      Get the free space of the pool
 *
 *   ARGUMENTS
 *
 *      hPool  - The handle of the pool.
 *
 *   RETURN
 *   
 *      (ULONG) The size of the total free space of this pool.
 *
*******************************************************************************/
ULONG
MemPoolGetFreeSpace( MEM_POOL_HANDLE hPool );

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      MemPoolLeakDetectStart
 *
 *   DESCRIPTION
 *
 *      Start log memory leak detection.
 *
 *   ARGUMENTS
 *
 *      hPool  - The handle of the pool to destroy.
 *
 *
 *   RETURN
 *   
 *      N/A
 *
*******************************************************************************/
void
MemPoolLeakDetectStart( MEM_POOL_HANDLE hPool );


/*******************************************************************************
 *
 *   FUNCTION
 *
 *      MemPoolLeakDetectStop
 *
 *   DESCRIPTION
 *
 *      Stop log memory leak detection and report the result.
 *
 *   ARGUMENTS
 *
 *      hPool  - The handle of the pool to destroy.
 *
 *
 *   RETURN
 *   
 *      TRUE   - Successful.
 *      FALSE  - Failed.
 *
*******************************************************************************/
BOOL
MemPoolLeakDetectStop( MEM_POOL_HANDLE hPool );


/*******************************************************************************
 *
 *   FUNCTION
 *
 *      MemPoolGetBufferSize
 *
 *   DESCRIPTION
 *
 *      Get the memory chunk size by the allocated buffer
 *
 *   ARGUMENTS
 *
 *      pAllocatedBuffer  - The allocated buffer
 *
 *   RETURN
 *   
 *      (ULONG) The size of the chunk size
 *
*******************************************************************************/
ULONG
MemPoolGetBufferSize( VOID* pAllocatedBuffer  );



/*******************************************************************************
 *
 *   Macro for client usage
 *
*******************************************************************************/
#ifdef DISABLE_MEM_ALLOC_LOG

#define MemPoolAlloc(POOL,SIZE,FLAG)      MemPoolAllocImp(POOL,SIZE,FLAG,0,0)

#define MemPoolCalloc(POOL,NUM,SIZE,FLAG) MemPoolCallocImp(POOL,NUM,SIZE,FLAG,0,0) //Andy Liu TBD

#define MemPoolRealloc(POOL,BUFFER,SIZE)  MemPoolAllocImp(POOL,BUFFER,SIZE,0,0)

#else

#define MemPoolAlloc(POOL,SIZE,FLAG)      MemPoolAllocImp(POOL,SIZE,FLAG,__FILE__,__LINE__)

#define MemPoolCalloc(POOL,NUM,SIZE,FLAG) MemPoolCallocImp(POOL,NUM,SIZE,FLAG,__FILE__,__LINE__)

#define MemPoolRealloc(POOL,BUFFER,SIZE)  MemPoolReallocImp(POOL,BUFFER,SIZE,__FILE__,__LINE__)

#endif // !defined(_MEMPOOL_H__9CF77E9A_1769_452C_AF54_929F47DB47F7__INCLUDED_)

#endif