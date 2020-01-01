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
File        : FAT_Intern.h
Purpose     : Internal FAT File System Layer header
---------------------------END-OF-HEADER------------------------------
*/

#ifndef _FAT_INTERN_H_
#define _FAT_INTERN_H_

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

#include "fs_int.h"

/*********************************************************************
*
*       #define constants
*
**********************************************************************
*/

/*********************************************************************
*
*       defines non configurable
*
**********************************************************************
*/
#define FS_FAT_DENTRY_SIZE       0x20

#define FS_FAT_ATTR_READ_ONLY    FS_ATTR_READ_ONLY
#define FS_FAT_ATTR_HIDDEN       FS_ATTR_HIDDEN
#define FS_FAT_ATTR_SYSTEM       FS_ATTR_SYSTEM
#define FS_FAT_ATTR_VOLUME_ID    0x08
#define FS_FAT_ATTR_ARCHIVE      FS_ATTR_ARCHIVE
#define FS_FAT_ATTR_DIRECTORY    FS_ATTR_DIRECTORY
#define FS_FAT_ATTR_LONGNAME     (FS_FAT_ATTR_READ_ONLY | FS_FAT_ATTR_HIDDEN | FS_FAT_ATTR_SYSTEM | FS_FAT_ATTR_VOLUME_ID)

#define FS_FAT_MAX_DIRNAME      255

#define FS_FAT_TYPE_FAT12       12
#define FS_FAT_TYPE_FAT16       16
#define FS_FAT_TYPE_FAT32       32
#define INVALID_NUM_FREE_CLUSTERS_VALUE   0xFFFFFFFF


/*********************************************************************
*
*       defines for Boot parameter block offsets
*
**********************************************************************
*/
#define BPB_OFF_SIGNATURE          510
#define BPB_OFF_BYTES_PER_SECTOR    11
#define BPB_OFF_NUM_FATS            16
#define BPB_OFF_SECTOR_PER_CLUSTER  13
#define BPB_OFF_NUMSECTORS_16BIT    19
#define BPB_OFF_NUMSECTORS_32BIT    32
#define BPB_OFF_FATSIZE_16BIT       22
#define BPB_OFF_FATSIZE_32BIT       36
#define BPB_OFF_FAT32_EXTFLAGS      40
#define BPB_OFF_ROOTDIR_CLUSTER     44
#define BPB_OFF_FAT32_FSINFO_SECTOR 48

/*********************************************************************
*
*       defines for FAT32 FSInfo Sector offsets
*
**********************************************************************
*/
#define FSINFO_OFF_SIGNATURE_1            0
#define FSINFO_OFF_SIGNATURE_2          484
#define FSINFO_OFF_FREE_CLUSTERS        488
#define FSINFO_OFF_NEXT_FREE_CLUSTER    492
#define FSINFO_OFF_SIGNATURE_3          508

/*********************************************************************
*
*       defines for FAT32 FSInfo related values
*
**********************************************************************
*/
#define FSINFO_SIGNATURE_1                       0x41615252
#define FSINFO_SIGNATURE_2                       0x61417272
#define FSINFO_SIGNATURE_3                       0xAA550000


/*********************************************************************
*
*       defines for directory entry offsets
*
**********************************************************************
*/
#define DIR_ENTRY_OFF_ATTRIBUTES          11
#define DIR_ENTRY_OFF_SIZE                28
#define DIR_ENTRY_OFF_FIRSTCLUSTER_LOW    26
#define DIR_ENTRY_OFF_FIRSTCLUSTER_HIGH   20
#define DIR_ENTRY_OFF_CREATION_TIME       14
#define DIR_ENTRY_OFF_CREATION_DATE       16
#define DIR_ENTRY_OFF_WRITE_TIME          22
#define DIR_ENTRY_OFF_WRITE_DATE          24

#define DIR_ENTRY_SHIFT                    5

/*********************************************************************
*
*             Global data types
*
**********************************************************************
*/

/* FAT directory entry */
typedef struct {
  U8   data[FS_FAT_DENTRY_SIZE];
} FS_FAT_DENTRY;

typedef struct {
  char ac[11];
} FS_83NAME;


/*********************************************************************
*
*             Global function prototypes
*
**********************************************************************
*/

/*********************************************************************
*
*             fat_misc
*/
U32          FS_FAT_ClusterId2SectorNo(FS_FAT_INFO * pFATInfo, U32 ClusterId);
U32          FS_FAT_FindFreeCluster   (FS_VOLUME * pVolume, FS_SB * pSB, U32 FirstCluster);
void            FS_FAT_LinkCluster       (FS_VOLUME * pVolume, FS_SB * pSB, U32 LastCluster, U32 NewCluster);
char            FS_FAT_MarkClusterEOC    (FS_VOLUME * pVolume, FS_SB * pSB, U32 Cluster);
U32          FS_FAT_WalkCluster       (FS_VOLUME * pVolume, FS_SB * pSB, U32 StartCluster, U32 NumClusters);
U32          FS_FAT_AllocCluster      (FS_VOLUME * pVolume, FS_SB * pSB, U32 LastCluster);
U32          FS_FAT_ReadFATEntry      (FS_VOLUME * pVolume, FS_SB * pSB, U32 ClusterId);
U32          FS_FAT_FindLastCluster   (FS_VOLUME * pVolume, FS_SB * pSB, U32 ClusterId, U32 * pNumClusters);
U32          FS_FAT_FreeClusterChain  (FS_VOLUME * pVolume, FS_SB * pSB, U32 ClusterId, U32 NumClusters);

int             FS_FAT_AllocClustersIfReq(FS_FILE *pFile, FS_SB * pSBfat, U32 NumClusters);
int             FS_FAT_AllocFirstClusterIfReq(FS_FILE * pFile, FS_SB * pSBfat, char * pDirUpdateRequired);

U16          FS_FAT_GetNumAdjClustersInChain(FS_VOLUME * pVolume, FS_SB * pSB, U32 CurCluster);


FS_FAT_DENTRY * FS_FAT_FindDirEntryShort  (FS_VOLUME * pVolume, FS_SB * pSB, const char *pEntryName, int Len, U32 DirStart);
FS_FAT_DENTRY * FS_FAT_FindDirEntryShortEx(FS_VOLUME * pVolume, FS_SB * pSB, const char *pEntryName, int Len, FS_DIR_POS * pDirPos);
FS_FAT_DENTRY * FS_FAT_FindEmptyDirEntry  (FS_VOLUME * pVolume, FS_SB * pSB, U32 DirStart);
FS_FAT_DENTRY * FS_FAT_GetDirEntry        (FS_VOLUME * pVolume, FS_SB* pSB,  FS_DIR_POS * pDirPos);
void            FS_FAT_IncDirPos          (FS_DIR_POS * pDirPos);

char            FS_FAT_GetFATType          (U32 NumClusters);
void            FS_FAT_WriteDirEntryCluster(FS_FAT_DENTRY * pDirEntry, U32 Cluster);
U32          FS_FAT_GetFirstCluster     (FS_FAT_DENTRY * pDirEntry);
void            FS_FAT_WriteDirEntry83     (FS_FAT_DENTRY * pDirEntry, const FS_83NAME * pFileName, U32 ClusterId, U8 Attrib, U32 Size, U16 Time, U16 Date);
void            FS_FAT_WriteDirEntryShort  (FS_FAT_DENTRY * pDirEntry, const char      * pFileName, U32 ClusterId, U8 Attrib, U32 Size, U16 Time, U16 Date);


#if FS_FAT_SUPPORT_LFN
  #define FS_FAT_FIND_DIR_ENTRY(pVolume, pSB, sName, Len, DirStart, pLongEntryIndex)  FS_FAT_FindDirEntry(pVolume, pSB, sName, Len, DirStart, pLongEntryIndex)
#else
  #define FS_FAT_FIND_DIR_ENTRY(pVolume, pSB, sName, Len, DirStart, pLongEntryIndex)  FS_FAT_FindDirEntryShort(pVolume, pSB, sName, Len, DirStart)
#endif


char            FS_FAT_FindPath         (FS_VOLUME * pVolume, FS_SB * pSB,  const char *pFullName, const char * *ppFileName, U32 *pDirStart);
char            FS_FAT_DeleteFileOrDir  (FS_VOLUME * pVolume, FS_SB * pSB, FS_FAT_DENTRY  * pDirEntry, U8 IsFile);

//#if (FORMAT_FREE_ENABLE)
char            FS_FAT_DeleteFileOrDirFormatFree  (FS_VOLUME * pVolume, FS_SB * pSB, FS_FAT_DENTRY  * pDirEntry, U8 IsFile);
//#endif

void            FS_FAT_InitDirEntryScan  (FS_FAT_INFO * pFATInfo, FS_DIR_POS * pDirPos, U32 DirCluster);
char            FS_FAT_Make83Name        (FS_83NAME * pOutName, const char *pOrgName, int Len);
FS_FAT_DENTRY * FS_FAT_CreateDirEntry    (FS_VOLUME * pVolume, FS_SB * pSB, const char * pFileName, U32 DirStart, U32 ClusterId, U8 Attributes, U32 Size, U16 Date, U16 Time);
FS_FAT_DENTRY * FS_FAT_CreateDirEntryEX  (FS_VOLUME * pVolume, FS_SB * pSB, const char * pFileName, FS_DIR_POS * pDirPos, U32 ClusterId, U8 Attributes, U32 Size, U16 Date, U16 Time);

/*********************************************************************
*
*       FAT Long file name support (LFN)
*/
FS_FAT_DENTRY * FS_FAT_FindDirEntry      (FS_VOLUME * pVolume, FS_SB * pSB, const char *pEntryName, int Len, U32 DirStart, int * pLongDirEntryIndex);
FS_FAT_DENTRY * FS_FAT_FindDirEntryLong  (FS_VOLUME * pVolume, FS_SB * pSB, const char * sLongName,  int Len, U32 DirStart, int * pLongDirEntryIndex);
void            FS_FAT_DelLongEntry      (FS_VOLUME * pVolume, FS_SB * pSB, U32 DirStart, int LongDirEntryIndex);
FS_FAT_DENTRY * FS_FAT_LFN_CreateDirEntry(FS_VOLUME * pVolume, FS_SB * pSB, const char * pFileName, U32 DirStart, U32 ClusterId, U8 Attributes, U32 Sizes, U16 Time, U16 Date);
FS_DIRENT     * FS_FAT_LFN_ReadDir       (FS_DIR    * pDir,    FS_SB * pSB);

/*********************************************************************
*
*             FAT_Move
*/

#if FS_FAT_SUPPORT_LFN
  #define FS_FAT_MOVE_ENTRY(pVolume, DirStartOld, DirStartNew, pDirEntry, pNewName, pSB, LongEntryIndex) FS__FAT_Move(pVolume, DirStartOld, DirStartNew, pDirEntry, pNewName, pSB, LongEntryIndex)
#else
  #define FS_FAT_MOVE_ENTRY(pVolume, DirStartOld, DirStartNew, pDirEntry, pNewName, pSB, LongEntryIndex) FS__FAT_Move(pVolume, DirStartOld, DirStartNew, pDirEntry, pNewName, pSB, -1)
#endif

char FS__FAT_Move(FS_VOLUME * pVolume, U32 DirStartOld, U32 DirStartNew, FS_FAT_DENTRY * pDirEntry, const char * pNewName, FS_SB * pSB, I32 LongEntryIndex);



#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif  /* _FAT_INTERN_H_ */

/*************************** End of file ****************************/
	 	 			 		    	 				 	   		   	 		  	 	      	   		 	 	  	  		  	 		 	    	 		     			       	   	 			  	     	   		 		     			    	 		 	    		 					 	 	  	  	 	 		 		 	    		 			  		 	  	 		  			 		 			  		 
