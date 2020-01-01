
//==============================================================================
/**
 @file ahc_mempoolfixedsize.h
 @brief AHC Memory Pool with fixed chunk size
 @author Caesar Chang
 @version 1.0
*/

#include "ahc_common.h"
#include "ahc_macro.h"
#include "ait_utility.h"
#include "ahc_mempoolfixedsize.h"
/*******************************************************************************
 *
 *   
 *
*******************************************************************************/

UINT8  const  UnMapTbl[256] = {
    0, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x00 to 0x0F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x10 to 0x1F                             */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x20 to 0x2F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x30 to 0x3F                             */
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x40 to 0x4F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x50 to 0x5F                             */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x60 to 0x6F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x70 to 0x7F                             */
    7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x80 to 0x8F                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0x90 to 0x9F                             */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xA0 to 0xAF                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xB0 to 0xBF                             */
    6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xC0 to 0xCF                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xD0 to 0xDF                             */
    5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0,       /* 0xE0 to 0xEF                             */
    4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0        /* 0xF0 to 0xFF                             */
};

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_LockInit
 *
 *   DESCRIPTION
 *
 *      Init the locker of the memory pool.
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
AHC_BOOL AHC_MemPoolFS_LockInit(PSMEMPOOLFIXEDSIZE hPool)
{
    hPool->smLock = AHC_OS_CreateSem(1);
    if( hPool->smLock == 0xFF )
    {
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_LockUninit
 *
 *   DESCRIPTION
 *
 *      Uninitialize the memory pool.
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
AHC_BOOL AHC_MemPoolFS_LockUninit(PSMEMPOOLFIXEDSIZE hPool)
{
    if( AHC_OS_DeleteSem(hPool->smLock) == 0xFF )
    {
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_LockEx
 *
 *   DESCRIPTION
 *
 *      Lock the pool for finite time waiting
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
AHC_BOOL AHC_MemPoolFS_LockEx(PSMEMPOOLFIXEDSIZE hPool, UINT32 uiTimeOutTick )
{
    if (AHC_OS_AcquireSem(hPool->smLock, uiTimeOutTick) != 0) 
    {
        return AHC_FALSE;
    }
    return AHC_TRUE;
}
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_Lock
 *
 *   DESCRIPTION
 *
 *      Lock the pool.
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
AHC_BOOL AHC_MemPoolFS_Lock(PSMEMPOOLFIXEDSIZE hPool )
{
	// Wait forever
    if (AHC_OS_AcquireSem(hPool->smLock, 0) != 0) 
    {
        return AHC_FALSE;
    }
    return AHC_TRUE;
}
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_Unlock
 *
 *   DESCRIPTION
 *
 *      Unlock the pool.
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
AHC_BOOL AHC_MemPoolFS_Unlock(PSMEMPOOLFIXEDSIZE hPool)
{
    if (AHC_OS_ReleaseSem(hPool->smLock) != 0) 
    {
        return AHC_FALSE;
    }
    return AHC_TRUE;
}

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_CreatePool
 *
 *   DESCRIPTION
 *
 *      Initialize memory pool with fixed chunk size.
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
PSMEMPOOLFIXEDSIZE AHC_MemPoolFS_InitPool(PBYTE pbyBuffer, UINT uiPoolSize, UINT uiChunkSize )
{
	PSMEMPOOLFIXEDSIZE pMemPoolFixedSize;
	PBYTE              pPtr;
	PBYTE              pBufferEend;
	PULONG 	           puTailTag;
	int 				nSize;
	int 				nNum;

	MEMSET( pbyBuffer, 0, uiPoolSize );

	uiChunkSize       = ALIGN_UP( uiChunkSize, MEMPOOLFIXEDSIZE_ALIGN_SIZE );

	pPtr              = (PBYTE)ALIGN_UP( (UINT)pbyBuffer, MEMPOOLFIXEDSIZE_ALIGN_SIZE );
	pBufferEend       = (PBYTE)ALIGN_DOWN((UINT)pbyBuffer+uiPoolSize, MEMPOOLFIXEDSIZE_ALIGN_SIZE );
	pMemPoolFixedSize = (PSMEMPOOLFIXEDSIZE)pPtr;
	pPtr			  +=  sizeof(SMEMPOOLFIXEDSIZE);

	nSize			  =  pBufferEend - pPtr;

	// nSize = (NumOfChunks * ChunkSize) + (NumOfChunks * 8 /32 + sizeof(ULONG) )
	nNum              = 4*( nSize - sizeof(ULONG)*2) / (uiChunkSize*4 + 1 );

	if( nSize <=0 || nNum <= 0 )
	{
		return NULL;
	}

	if( AHC_MemPoolFS_LockInit(pMemPoolFixedSize) == AHC_FALSE)
	{
		return NULL;
	}

	AHC_MemPoolFS_Lock(pMemPoolFixedSize);
	
	pMemPoolFixedSize->uiTag				= MEMPOOLFIXEDSIZE_TAG;
	pMemPoolFixedSize->uiTotalChunks 		= nNum;
	pMemPoolFixedSize->uiLastAllocPos       = 0;
	pMemPoolFixedSize->nUsedChunks  		= 0;
	pMemPoolFixedSize->uiChunkSize   		= uiChunkSize;
	pMemPoolFixedSize->uiChunkBitmapSize 	= ALIGN_UP( nNum, sizeof(ULONG)*8 )/(sizeof(ULONG)*8);
	pMemPoolFixedSize->pulChunkBitmap       = (PULONG)pPtr;
	pPtr                                   += pMemPoolFixedSize->uiChunkBitmapSize * sizeof(ULONG);
	pMemPoolFixedSize->pbyChunkStart        = pPtr;
	
	puTailTag                               = (PULONG)( pMemPoolFixedSize->pbyChunkStart + nNum*uiChunkSize);
	*puTailTag								= MEMPOOLFIXEDSIZE_TAG;

	AHC_MemPoolFS_Unlock(pMemPoolFixedSize);	

	return pMemPoolFixedSize;
}



/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_UninitPool
 *
 *   DESCRIPTION
 *
 *      Unitialize memory pool with fixed chunk size.
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
AHC_BOOL AHC_MemPoolFS_UninitPool(PSMEMPOOLFIXEDSIZE hPool )
{
    if( hPool->uiTag ==  MEMPOOLFIXEDSIZE_TAG )
    {
        AHC_OS_SEMID smLock;
        AHC_MemPoolFS_Lock(hPool);
        smLock = hPool->smLock;
        MEMSET( hPool, 0, sizeof(SMEMPOOLFIXEDSIZE) );
        hPool->smLock = smLock;
        AHC_MemPoolFS_Unlock(hPool);
	
        return AHC_MemPoolFS_LockUninit(hPool);
    }
    else
    {
        return AHC_FALSE;
    }
}
/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_Alloc
 *
 *   DESCRIPTION
 *
 *      Allocate a memory chunk.
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
void* AHC_MemPoolFS_Alloc(PSMEMPOOLFIXEDSIZE hPool)
{
    UINT i;
    int idx;
	PBYTE pbyBuffer = NULL;
	AHC_BOOL bFound = AHC_FALSE;

	AHC_MemPoolFS_Lock(hPool);
	
	for( i=hPool->uiLastAllocPos; i< hPool->uiChunkBitmapSize; i++ )
	{
	    ULONG ulBitmap = hPool->pulChunkBitmap[i];
		ulBitmap = ~ulBitmap;
        if( ulBitmap != 0 )
		{
		    int n;
			for(n=0;n<4;n++)
			{
                UINT8 byBitmap = ulBitmap & 0xFF;
				if( byBitmap != 0 )
				{
					idx = (i<<5) + (n<<3) + UnMapTbl[byBitmap];
					if( idx < (int)hPool->uiTotalChunks )
					{
						bFound = AHC_TRUE;
						hPool->uiLastAllocPos = i;
						break;
					}
				}
			    ulBitmap >>= 8;				
			}
			
			if(bFound )
			{
				break;
			}
		}
	}

	if( !bFound )
	{
		for( i=0; i< hPool->uiLastAllocPos; i++ )
		{
			ULONG ulBitmap = hPool->pulChunkBitmap[i];
			ulBitmap =~ulBitmap;
			if( ulBitmap != 0 )
			{
				int n;
				for(n=0;n<4;n++)
				{
					UINT8 byBitmap = ulBitmap & 0xFF;
					if( byBitmap != 0 )
					{
						idx = (i<<5) + (n<<3) + UnMapTbl[byBitmap];
						if( idx < (int)hPool->uiTotalChunks )
						{
							bFound = AHC_TRUE;
							hPool->uiLastAllocPos = i;
							break;
						}
					}
					ulBitmap >>= 8;				
				}

				if(bFound )
				{
					break;
				}
			}
		}
	}

	if( bFound )
	{
		// Book it
		hPool->pulChunkBitmap[idx/32] |=  1 << ( idx % 32 );
		pbyBuffer = hPool->pbyChunkStart+ (idx * hPool->uiChunkSize);
		hPool->nUsedChunks++;
	}
	AHC_MemPoolFS_Unlock(hPool);
	
	return (void*)pbyBuffer;
}

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_Calloc
 *
 *   DESCRIPTION
 *
 *      Allocate a chunk and set the all data in buffer to zero.
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
void* AHC_MemPoolFS_Calloc(PSMEMPOOLFIXEDSIZE hPool)
{
	void* pbyBuffer = AHC_MemPoolFS_Alloc(hPool);
	
	if( pbyBuffer != NULL )
	{
		MEMSET(pbyBuffer, 0, hPool->uiChunkSize );
	}
	return pbyBuffer;
}

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_Free
 *
 *   DESCRIPTION
 *
 *      Free an allocated chunk.
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
AHC_BOOL AHC_MemPoolFS_Free(PSMEMPOOLFIXEDSIZE hPool, void* pbyBuffer )
{
    int nOffset;
    int nIdx;

	AHC_MemPoolFS_Lock(hPool);

	nOffset = (PBYTE)pbyBuffer - hPool->pbyChunkStart;

	nIdx =  nOffset / hPool->uiChunkSize;

	if( nIdx < 0                             ||
	    nIdx >=  (int)hPool->uiTotalChunks   ||
		nOffset % hPool->uiChunkSize != 0       )
	{
		AHC_MemPoolFS_Unlock(hPool);
		return AHC_FALSE;		
	}

	// Unbook it
	hPool->pulChunkBitmap[nIdx/32] &= ~(1 << ( nIdx % 32 ) );
	hPool->nUsedChunks--;

	AHC_MemPoolFS_Unlock(hPool);

	return AHC_TRUE;
}

/*******************************************************************************
 *
 *   FUNCTION
 *
 *      AHC_MemPoolFS_Dump
 *
 *   DESCRIPTION
 *
 *      Dump the memory pool.
 *
 *   ARGUMENTS
 *
 *      hPool		- The handle of the fixed sized memory Pool .
 *
 *   RETURN
 *   
 *      AHC_TRUE  - SUCCESSFUL
 *      AHC_FALSE - FAILED
 *
*******************************************************************************/
AHC_BOOL AHC_MemPoolFS_Dump(PSMEMPOOLFIXEDSIZE hPool)
{
	UINT i;

	printc("Pool Handle 0x%08X\n", hPool );
	printc("Pool chunk bitmap 0x%08X size=%d\n", hPool->pulChunkBitmap, hPool->uiChunkBitmapSize );
	printc("Pool pbyChunkStart 0x%08X\n", hPool->pbyChunkStart, hPool->uiChunkBitmapSize );
	printc("Pool chunk size =%d num of chunks =%d %d\n", hPool->uiChunkSize, hPool->uiTotalChunks, hPool->nUsedChunks );
	for( i=0; i< hPool->uiChunkBitmapSize; i++ )
	{
	    ULONG ulBitmap = hPool->pulChunkBitmap[i];
        printc("[%d] = %08X \n", i, ulBitmap );

	}

	return AHC_TRUE;
}
