/*
**********************************************************************
*                          Micrium, Inc.
*                      949 Crestview Circle
*                     Weston,  FL 33327-1848
*
*                            uC/FS
*
*             (c) Copyright 2001 - 2006, Micrium, Inc.
*                      All rights reserved.
*
***********************************************************************
*/
#ifndef _SDCACHE_H_
#define _SDCACHE_H_
 
#if 1//(FS_NEWBUFFER)
#if 1//defined (ALL_FW)

#include "FS_ConfDefaults.h"        /* FS Configuration */
#include "fs_dev.h"
#include "fs_clib.h"
//#include "lib_retina.h" //For use of MMP_PRINT_RET_ERROR()
#include "mmpf_typedef.h"

/*********************************************************************
*
*        global variable
*
**********************************************************************
*/


/*********************************************************************
*
*       Defines, fixed
*
**********************************************************************
*/
//#define   NEWCacheSectorSize     (512)
#define   SECTOR_INDEX_INVALIDATE   0xFFFFFFFF
#define   NEWCache_Clear   (0)
#define   NEWCache_Dirty   (1)

/*********************************************************************
*
*       Types
*
**********************************************************************
*/

/* Buffer data. Once instance for all buffer. */   
//typedef   struct   NEWCACHE_DATA_RW   NEWCACHE_DATA_RW;
/*
typedef struct _NEWCACHE_DATA_RW {
  U8         IsDirty[MAX_CACHE_NUM];
  U32        StartSectorNum[MAX_CACHE_NUM];
}NEWCACHE_DATA_RW;
*/
/*********************************************************************
*
*        extern
*
**********************************************************************
*/

typedef struct _FS_CACHE_INFO {
  U8	CacheNumber;
  U32   CacheSize; 
  U32   CacheStartAddr;
  U32   CacheTotalSize;  
  U32   CacheAddr[MAX_CACHE_NUM];  
  U32   CacheSectorSize;
  FS_CACHE_DEVICE_MAP   *pCacheDeviceMap;
  //const FS_CACHE_API *pLinkCacheAPI;
  //const FS_DEVICE_TYPE	* pMediaType;
  //const FS_DEVICE_TYPE	* pSelf;
  //void  * pNEWCacheData; 
  //NEWCACHE_DATA_RW    MediaCacheRW; 
  U8    IsDirty[MAX_CACHE_NUM];
  U32   StartSectorNO[MAX_CACHE_NUM];//must be alignment with CacheSize	
  U32   FatNumSectors;
  U32	FirstDataSector;
  U32   HiddenSector;//from pVolume->Partition.StartSector  	
  //MMP_ERR (*pf_InitCacheNumandSize)( (FS_CACHE_INFO *)pthis , U8 ubCacheNum, U32 ulCacheSize);   
  //int (*pf_SetCacheAddr)( FS_CACHE_INFO *pthis , MMP_ULONG ulStartAddr); 
  int (*pf_SetCacheStartAddrSize)( struct _FS_CACHE_INFO *pthis , U32 ulStartAddr, U32 ulTotalSize); 
  int (*pf_SetCacheNumSize)      ( struct _FS_CACHE_INFO *pthis  , U8 ubCacheNum, U32 ulCacheSize);  
  int (*pf_SetCacheSectorSize)   ( struct _FS_CACHE_INFO *pthis  , U32 ulCacheSectorSize);  
  int (*pf_SetFatNumSectors)( struct _FS_CACHE_INFO *pthis , U32 ulFatNumSectors);  
  int (*pf_SetFirstDataSector)( struct _FS_CACHE_INFO *pthis , U32 ulFirstDataSector);   
  int (*pf_SetHiddenSector)( struct _FS_CACHE_INFO *pthis , U32 ulHiddenSector); 
  int (*pf_RegCacheMedia)   ( struct _FS_CACHE_INFO *pthis  , const FS_DEVICE_TYPE *pDeviceType); 
  int (*pf_RegCacheSelf)    ( struct _FS_CACHE_INFO *pthis  , const FS_DEVICE_TYPE *pDeviceType); 
  int (*pf_RegCacheObject)  ( struct _FS_CACHE_INFO *pthis  , struct _FS_CACHE_INFO *pObject); 
   

	//FS_CACHE_API *AFSDLKJHALSKDJFH




  //MMP_ERR (*pf_InitCacheSectorSize)( (FS_CACHE_INFO *)pthis , U32 ulCacheSectorSize);
  
  //MMP_ERR (*pf_NewCache_Initialize)( (FS_CACHE_INFO*)pNewCacheInfo);	  
  //MMP_ERR (*pf_NewCache_UnInitialize)( (FS_CACHE_INFO*)pNewCacheInfo);
  //MMP_ERR (*pf_NewCache_Invalidate)( (FS_CACHE_INFO*)pNewCacheInfo);	
}FS_CACHE_INFO;




/*********************************************************************
*
*        declaration
*
**********************************************************************
*/
//U8 NewCache_Initialize( (void *)pNewCacheInfo );
//int NewCache_SectorCheck(FS_U32 u32SectorIndex);
int NewCache_SectorReadIn(FS_CACHE_INFO   *pFSCacheInfo, MMP_ULONG u32SectorIndex,void *pBuffer);
int NewCache_AssignSectorReadIn(FS_CACHE_INFO   *pFSCacheInfo, MMP_ULONG u32SectorIndex, MMP_UBYTE  u8CacheIndex,void *pBuffer);
int NewCache_SectorWriteOut(FS_CACHE_INFO   *pFSCacheInfo, MMP_ULONG u32SectorIndex, const void *pBuffer);
int NewCache_AssignSectorWriteOut(FS_CACHE_INFO   *pFSCacheInfo, MMP_ULONG u32SectorIndex, MMP_UBYTE  u8CacheIndex, const void *pBuffer);
int NewCache_SectorCheck(FS_CACHE_INFO   *pFSCacheInfo, MMP_ULONG u32SectorIndex);
int NewCache_SearchFree(FS_CACHE_INFO	*pFSCacheInfo, 	MMP_UBYTE  *pu8CacheIndex);
int NewCache_ReplaceByFree(FS_CACHE_INFO	*pFSCacheInfo, MMP_ULONG u32SectorIndex, MMP_UBYTE *pu8CacheIndex );
int NewCache_DumpNearest(FS_CACHE_INFO	*pFSCacheInfo, MMP_ULONG u32SectorIndex, MMP_UBYTE *pu8CacheIndex );
int NewCache_DumpDistant(FS_CACHE_INFO	*pFSCacheInfo, MMP_ULONG u32SectorIndex, MMP_UBYTE *pu8CacheIndex );
int NewCache_UpdateFromMedia(FS_CACHE_INFO	*pFSCacheInfo, MMP_UBYTE Unit, MMP_ULONG u32SectorIndex, MMP_UBYTE u8CacheIndex);
int NewCache_WriteOut(FS_CACHE_INFO	*pFSCacheInfo, MMP_UBYTE Unit, MMP_UBYTE u8CacheIndex );
void NewCache_Invalidate(FS_CACHE_INFO	*pFSCacheInfo, MMP_UBYTE u8CacheIndex );
void NewCache_InvalidateALL(FS_CACHE_INFO	*pFSCacheInfo);
int NewCache_CleanALL(FS_CACHE_INFO	*pFSCacheInfo, FS_DEVICE * pDevice);
void NewCache_ClearDirty(FS_CACHE_INFO	*pFSCacheInfo, MMP_UBYTE u8CacheIndex );
void NewCache_ClearDirtyALL(FS_CACHE_INFO	*pFSCacheInfo);
void NewCache_SetDirty(FS_CACHE_INFO	*pFSCacheInfo, MMP_UBYTE u8CacheIndex );
void NewCache_SetStartSectorNO(FS_CACHE_INFO	*pFSCacheInfo, MMP_UBYTE u8CacheIndex , MMP_ULONG u32CachesizeAlignSectorNO);
int NewCache_ReadSectorFromMedia(FS_CACHE_INFO	*pFSCacheInfo, MMP_UBYTE Unit, MMP_ULONG u32SectorIndex, void *pBuffer);
int NewCache_WriteSectorToCache(FS_CACHE_INFO	*pFSCacheInfo, MMP_UBYTE Unit, MMP_ULONG u32SectorIndex, const void *pBuffer);
MMP_USHORT Get_SectorOffsetIndex(FS_CACHE_INFO   *pFSCacheInfo, MMP_ULONG u32SectorIndex, MMP_UBYTE u8CacheIndex );
MMP_ULONG Get_ByteOffsetIndex(FS_CACHE_INFO   *pFSCacheInfo, MMP_USHORT u16SectorOffsetIndex );
MMP_ULONG Get_CachesizeAlignSectorNO(FS_CACHE_INFO   *pFSCacheInfo, MMP_ULONG u32SectorIndex);
MMP_USHORT ActualRW_SectorNum(FS_CACHE_INFO   *pFSCacheInfo, MMP_ULONG u32CachesizeAlignSectorNum);

#endif
#endif
#endif
/*************************** End of file ****************************/
