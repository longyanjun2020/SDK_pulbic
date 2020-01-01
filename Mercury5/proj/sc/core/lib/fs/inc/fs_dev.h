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

----------------------------------------------------------------------
File        : fs_dev.h
Purpose     : Define structures for Device Drivers
---------------------------END-OF-HEADER------------------------------
*/

#ifndef _FS_DEV_H_
#define _FS_DEV_H_

#include "FS_ConfDefaults.h"
#include "fs_int.h"

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif


/*********************************************************************
*
*             Global data types
*
**********************************************************************
*/

struct FS_DEVICE_TYPE {
  const char *      name;
  int               MaxUnits;
  int               (*pfGetStatus)    (U8 Unit);
  int               (*pfRead)         (U8 Unit, U32 SectorNo, void *pBuffer);
  int               (*pfWrite)        (U8 Unit, U32 SectorNo, const void *pBuffer);
  int               (*pfIoCtl)        (U8 Unit, I32 Cmd, I32 Aux, void *pBuffer);
  int               (*pfReadBurst)    (U8 Unit, U32 SectorNo, U32 NumSectors,       void *pBuffer);
  int               (*pfWriteBurst)   (U8 Unit, U32 SectorNo, U32 NumSectors, const void *pBuffer);
  int               (*pfInitDevice)   (U8 Unit);
  int               (*pfInitMedium)   (U8 Unit);
  //int               (*pfWriteMultiple)(U8 Unit, U32 SectorNo, U32 NumSectors, const void *pBuffer);
  //int             (*pfEraseSector)  (U8 Unit, U32 SectorNo, U32 NumSectors);
};

typedef struct _FS_CACHE_DEVICE_MAP {
    const FS_DEVICE_TYPE  *pMediaType;
    const FS_DEVICE_TYPE  *pSelf;
    void                  *pCacheInfoObject;
    //FS_CACHE_INFO         *pCacheInfoObject;
}FS_CACHE_DEVICE_MAP;


#if 0//(FS_NEWBUFFER)
/*
typedef struct _FS_CACHE_INFO {
  U8	CacheNumber;
  U32   CacheSize; 
  U32   CacheStartAddr;
  U32   CacheTotalSize;  
  U32   CacheAddr[MAX_CACHE_NUM];  
  U32   CacheSectorSize;
  FS_CACHE_DEVICE_MAP   CacheDeviceMap;
  //const FS_DEVICE_TYPE	* pMediaType;
  //const FS_DEVICE_TYPE	* pSelf;
  //void  * pNEWCacheData; 
  //NEWCACHE_DATA_RW    MediaCacheRW; 
  U8         IsDirty[MAX_CACHE_NUM];
  U32        StartSectorNO[MAX_CACHE_NUM];//must be alignment with CacheSize	
  U32        FatNumSectors;
  //MMP_ERR (*pf_InitCacheNumandSize)( (FS_CACHE_INFO *)pthis , U8 ubCacheNum, U32 ulCacheSize);   
  //int (*pf_SetCacheAddr)( FS_CACHE_INFO *pthis , MMP_ULONG ulStartAddr); 
  int (*pf_SetCacheStartAddrSize)( struct _FS_CACHE_INFO *pthis , U32 ulStartAddr, U32 ulTotalSize); 
  int (*pf_SetCacheNumSize)      ( struct _FS_CACHE_INFO *pthis  , U8 ubCacheNum, U32 ulCacheSize);  
  int (*pf_SetCacheSectorSize)   ( struct _FS_CACHE_INFO *pthis  , U32 ulCacheSectorSize);  
  int (*pf_SetFatNumSectors)( struct _FS_CACHE_INFO *pthis , U32 ulFatNumSectors); 
  int (*pf_RegCacheMedia)   ( struct _FS_CACHE_INFO *pthis  , const FS_DEVICE_TYPE *pDeviceType); 
  int (*pf_RegCacheSelf)    ( struct _FS_CACHE_INFO *pthis  , const FS_DEVICE_TYPE *pDeviceType); 
   
	//FS_CACHE_API *AFSDLKJHALSKDJFH

  //MMP_ERR (*pf_InitCacheSectorSize)( (FS_CACHE_INFO *)pthis , U32 ulCacheSectorSize);
  
  //MMP_ERR (*pf_NewCache_Initialize)( (FS_CACHE_INFO*)pNewCacheInfo);	  
  //MMP_ERR (*pf_NewCache_UnInitialize)( (FS_CACHE_INFO*)pNewCacheInfo);
  //MMP_ERR (*pf_NewCache_Invalidate)( (FS_CACHE_INFO*)pNewCacheInfo);	
}FS_CACHE_INFO;
*/


#endif

#if defined(__cplusplus)
 }               /* Make sure we have C-declarations in C++ programs */
#endif

#endif  /* _FS_DEV_H_ */

/*************************** End of file ****************************/
	 	 			 		    	 				 	   		   	 		  	 	      	   		 	 	  	  		  	 		 	   		 		      		       	   	 			  	     	   		 		     			    	 		 	    		 					 	 	  	  	 	 		 		 	    		 			  		 	  	 		  			 		 			  		 
