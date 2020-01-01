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
File        : fs_int.h
Purpose     : Internals used accross different layers of the file system
---------------------------END-OF-HEADER------------------------------
*/

#ifndef _FS_INT_H_
#define _FS_INT_H_


#include "fs_api.h"
#include "FS_Debug.h"
#include "FS_ConfDefaults.h"        /* FS Configuration */
#include "fs_dev.h"
#include "fs_os.h"

#if FS_SUPPORT_FAT
  #include "fs_fat.h"
#endif
#if FS_SUPPORT_EFS
  #include "FS_EFS.h"
#endif



#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif



/*********************************************************************
*
*             Global data types
*
**********************************************************************
*/

#define FS_COUNTOF(a) (sizeof(a) / sizeof(a[0]))

/*********************************************************************
*
*       Defines non configurable
*
**********************************************************************
*/

#define FS_NEWCACHEDEBUGVIEW          (0)//enable for NewCache debug info;should sync with NEWCACHEDEBUGVIEW

#define FS_MARKFILENAME_LN            (0x40)


#define FS_DIRENTRY_GET_ATTRIBUTES    (1 << 0)
#define FS_DIRENTRY_GET_TIMESTAMP     (1 << 1)
#define FS_DIRENTRY_GET_VOLUME_LABEL  (1 << 2)
#define FS_DIRENTRY_GET_SIZE	      (1 << 3)



#define FS_DIRENTRY_SET_ATTRIBUTES    (1 << 0)
#define FS_DIRENTRY_SET_TIMESTAMP     (1 << 1)
#define FS_DIRENTRY_SET_VOLUME_LABEL  (1 << 2)


#define FS_FILE_ACCESS_FLAG_A (1 << 0)
#define FS_FILE_ACCESS_FLAG_B (1 << 1)
#define FS_FILE_ACCESS_FLAG_C (1 << 2)
#define FS_FILE_ACCESS_FLAG_R (1 << 3)
#define FS_FILE_ACCESS_FLAG_W (1 << 4)

/* Combined access modes which are frequently used */
#define FS_FILE_ACCESS_FLAGS_AW     (FS_FILE_ACCESS_FLAG_A | FS_FILE_ACCESS_FLAG_W)
#define FS_FILE_ACCESS_FLAGS_BR     (FS_FILE_ACCESS_FLAG_B | FS_FILE_ACCESS_FLAG_R)
#define FS_FILE_ACCESS_FLAGS_CW     (FS_FILE_ACCESS_FLAG_C | FS_FILE_ACCESS_FLAG_W)
#define FS_FILE_ACCESS_FLAGS_RW     (FS_FILE_ACCESS_FLAG_R | FS_FILE_ACCESS_FLAG_W)

#define FS_FILE_ACCESS_FLAGS_ACW    (FS_FILE_ACCESS_FLAG_C | FS_FILE_ACCESS_FLAGS_AW)
#define FS_FILE_ACCESS_FLAGS_ARW    (FS_FILE_ACCESS_FLAG_A | FS_FILE_ACCESS_FLAGS_RW)
#define FS_FILE_ACCESS_FLAGS_BCW    (FS_FILE_ACCESS_FLAG_B | FS_FILE_ACCESS_FLAGS_CW)
#define FS_FILE_ACCESS_FLAGS_BRW    (FS_FILE_ACCESS_FLAG_W | FS_FILE_ACCESS_FLAGS_BR)
#define FS_FILE_ACCESS_FLAGS_CRW    (FS_FILE_ACCESS_FLAG_C | FS_FILE_ACCESS_FLAG_R | FS_FILE_ACCESS_FLAG_W)

#define FS_FILE_ACCESS_FLAGS_ABCW   (FS_FILE_ACCESS_FLAG_B | FS_FILE_ACCESS_FLAGS_ACW)
#define FS_FILE_ACCESS_FLAGS_ACRW   (FS_FILE_ACCESS_FLAG_A | FS_FILE_ACCESS_FLAGS_CRW)
#define FS_FILE_ACCESS_FLAGS_BCRW   (FS_FILE_ACCESS_FLAG_B | FS_FILE_ACCESS_FLAGS_CRW)

#define FS_FILE_ACCESS_FLAGS_ABCRW  (FS_FILE_ACCESS_FLAGS_ACRW | FS_FILE_ACCESS_FLAG_A)

/* Field information for BPB */
#define FS__BPB_TOTALSEC16      0x013
#define FS__BPB_BYTESPERSECTOR  0x00b
#define FS__BPB_SECPERTRK       0x018
#define FS__BPB_HIDDENSEC       0x01C
#define FS__BPB_HEADNUM         0x01A
#define FS__BPB_TOTALSEC32      0x020

/* partition table definitions */
#define FS__DEV_PART_0_TABLE       0x01BE /* start of first entry */


/* device states */
#define FS_MEDIA_NOT_PRESENT       -1
#define FS_MEDIA_IS_PRESENT         0
#define FS_MEDIA_CHANGED            1
#define FS_MEDIA_STATE_UNKNOWN      2

/* Obsolete device states macros, please do not use them anymore. */
#define FS_MEDIA_STATEUNKNOWN       FS_MEDIA_STATE_UNKNOWN
#define FS_MEDIA_ISNOTPRESENT       FS_MEDIA_NOT_PRESENT
#define FS_MEDIA_ISPRESENT          FS_MEDIA_IS_PRESENT

/* Smart buffer (SB) type defines */
#define FS_SB_TYPE_DATA               FS_SECTOR_TYPE_DATA
#define FS_SB_TYPE_MANAGEMENT         FS_SECTOR_TYPE_MAN
#define FS_SB_TYPE_DIRECTORY          FS_SECTOR_TYPE_DIR

/*********************************************************************
*
*       Data types, opaque
*
**********************************************************************
*/
typedef struct FS_FAT_INFO    FS_FAT_INFO;
typedef struct FS_EFS_INFO    FS_EFS_INFO;
typedef struct FS_SB          FS_SB;

/*********************************************************************
*
*       Data types
*
**********************************************************************
*/

typedef struct {
  int TypeMask;    /* Combination of FS_SECTOR_TYPE_DATA, FS_SECTOR_TYPE_MAN, FS_SECTOR_TYPE_DIR */
  int ModeMask;    /* Combination of FS_CACHE_MODE_R, FS_CACHE_MODE_W, FS_CACHE_MODE_D */
} CACHE_MODE;

typedef struct {
  int TypeMask;    /* Combination of FS_SECTOR_TYPE_DATA, FS_SECTOR_TYPE_MAN, FS_SECTOR_TYPE_DIR */
  int NumSectors;  /* Number of sectors to use for the type(s) specified */
} CACHE_QUOTA;

typedef struct {
  U32 FirstSector;
  U32 NumSectors;
} CACHE_FREE;


struct FS_FAT_INFO{
  U32          NumSectors;       /* RSVD + FAT + ROOT + FATA       */
  U32          FATSize;          /* number of FAT sectors          */
  U32          RootDirPos;       /* Position of root directory. FAT32: Cluster, FAT12/16: Sector */
  U32          BytesPerCluster;
  U16          BytesPerSec;      /* 512,1024,2048,4096          */
  U16          ldBytesPerSector; /* 9, 10, 11, 12               */
  U16          RootEntCnt;       /* number of root dir entries     */
  U16          RsvdSecCnt;       /* 1 for FAT12 & FAT16            */
  U8           SecPerClus;       /* sec in allocation unit         */
  U8           NumFATs;          /* Typical value is 2             */
  U8           FATType;          /* FS_FAT_TYPE_FAT12/16/32        */
  U32          NumClusters;
  U32          FirstDataSector;
  U32          NumFreeClusters;  /* Once known, we keep track of the number of free clusters */
  U32          NextFreeCluster;  /* Once known, we keep track of the next free cluster */
#if FS_FAT_USE_FSINFO_SECTOR
  U16          FSInfoSector;
#endif
};

struct FS_EFS_INFO {
  U32          NumSectors;          /* Total number of sectors on the medium */
  U32          NumClusters;
  U32          BytesPerCluster;
  U16          BytesPerSector;      /* _512_,1024,2048,4096           */
  U32          FirstDataSector;
  U8           SectorsPerCluster;   /* Number of Sectors in allocation unit         */
  U8           ldBytesPerCluster;
  U16          ldBytesPerSector;    /* 9, 10, 11, 12               */
};


typedef union {
  FS_FAT_INFO  FATInfo;
  FS_EFS_INFO  EFSInfo;
} FS_INFO;

typedef struct {
  U8 Unit;
  U8 IsChanged;
  U8 MediaState;
#if FS_SUPPORT_CACHE
  const FS_CACHE_API * pCacheAPI;
#if (FS_MULTI_CACHE)
  void               * pCacheData[FS_SECTOR_TYPE_COUNT];
#else
  void               * pCacheData;
#endif
#endif
#if FS_SUPPORT_BUSY_LED
  FS_BUSY_LED_CALLBACK * pfSetBusyLED;
#endif
} FS_DEVICE_DATA;

struct FS_DEVICE {
  const FS_DEVICE_TYPE * pType;
  FS_DEVICE_DATA   Data;
};

struct FS_PARTITION {
  FS_DEVICE   Device;
  U32      StartSector;
  U32      NumSectors;
};

typedef void        FS_CB_FCLOSE         (FS_FILE    * pFile);
typedef int         FS_CB_CHECKINFOSECTOR(FS_VOLUME  * pVolume,    U8  * pBuffer);
typedef U32      FS_CB_FREAD          (FS_FILE    * pFile,       void  * pData, U32 NumBytes);
typedef FS_SIZE_T   FS_CB_FWRITE         (FS_FILE    * pFile, const void  * pData, U32 NumBytes);
typedef char        FS_CB_FOPEN          (const char * pFileName, FS_FILE * pFile, char DoDel, char DoOpen, char DoCreate);
typedef int         FS_CB_IOCTL          (FS_VOLUME  * pVolume,   I32    Cmd,   I32 Aux, void *pBuffer);
typedef int         FS_CB_OPENDIR        (const char * pDirName,  FS_DIR  * pDir);
typedef int         FS_CB_CLOSEDIR       (FS_DIR     * pDir);
typedef FS_DIRENT * FS_CB_READDIR        (FS_DIR     * pDir);
typedef int         FS_CB_REMOVEDIR      (FS_VOLUME  * pVolume,  const char * pDirName);
typedef int         FS_CB_CREATEDIR      (FS_VOLUME  * pVolume,  const char * pDirName);
typedef int         FS_CB_RENAME         (const char * sOldName, const char * sNewName, FS_VOLUME * pVolume);
typedef int         FS_CB_MOVE           (const char * sOldName, const char * sNewName, FS_VOLUME * pVolume);
typedef char        FS_CB_SETDIRENTRYINFO(FS_VOLUME  * pVolume,  const char * sName, const void * p, int Mask);
typedef char        FS_CB_GETDIRENTRYINFO(FS_VOLUME  * pVolume,  const char * sName,       void * p, int Mask);
typedef int         FS_CB_SET_END_OF_FILE(FS_FILE    * pFile);
typedef void        FS_CB_UNMOUNT        (FS_VOLUME  * pVolume);

typedef struct {
  FS_CB_CHECKINFOSECTOR * pfCheckInfoSector;
  FS_CB_FOPEN           * pfFOpen;
  FS_CB_FCLOSE          * pfFClose;
  FS_CB_FREAD           * pfFRead;
  FS_CB_FWRITE          * pfFWrite;
  FS_CB_IOCTL           * pfIoCtl;
  FS_CB_OPENDIR         * pfOpenDir;
  FS_CB_CLOSEDIR        * pfCloseDir;
  FS_CB_READDIR         * pfReadDir;
  FS_CB_REMOVEDIR       * pfRemoveDir;
  FS_CB_CREATEDIR       * pfCreateDir;
  FS_CB_RENAME          * pfRename;
  FS_CB_MOVE            * pfMove;
  FS_CB_SETDIRENTRYINFO * pfSetDirEntryInfo;
  FS_CB_GETDIRENTRYINFO * pfGetDirEntryInfo;
  FS_CB_SET_END_OF_FILE * pfSetEndOfFile;
  FS_CB_UNMOUNT         * pfUnmount;
} FS_FS_API;

#if (FS_NEW_GET_FREE_SPACE)&&(FS_NEW_SEARCH_FREE_CLUSTER)
typedef struct _FS_FC_INFO {
	U8	*ubFCTablePtr;
	U32	ulFCTableTotalSize;
	U32	ulEffectiveTableLength;
	U32	ulLastFATSectorNo;
	U32	ulLastFATSectorOffset;
	U8	bFCTableExist;
	U8  bEnable;
} FS_FC_INFO;
#endif

struct FS_VOLUME {
  FS_PARTITION Partition;
  FS_INFO      FSInfo;
  U8           PartitionIndex;
  U8           IsMounted;
  U8           InUse;
#if (FS_NEW_GET_FREE_SPACE)&&(FS_NEW_SEARCH_FREE_CLUSTER)
  FS_FC_INFO   FCInfo;		
#endif 
#if FS_SUPPORT_MULTIPLE_FS
  const FS_FS_API * pFS_API;
#endif
};

typedef struct {
  U32 Cluster;                    /* Cluster of current sector */
  U32 FirstCluster;
  U32 DirEntryIndex;              /* Directory entry index (first directory entry has index 0 */
  U32 ClusterIndex;
} FS_DIR_POS;

struct FS_DIR {
  FS_DIRENT   dirent;             /* current directory entry      */
  FS_DIR_POS  DirPos;             /* current position in file     */
  U16         DirEntryIndex;
  U32         FirstCluster;
  FS_VOLUME * pVolume;
  I16         error;              /* error code                   */
  U8          InUse;              /* handle in use mark           */
};

typedef union {
    struct {
      U32        CurClusterFile; /* Current cluster within the file. First cluster is 0, next cluster is 1 ... */
      U32        CurClusterAbs;  /* Current cluster on the medium. This needs to be computed from file cluster, consulting the FAT */
      U32        DirEntrySector; /* Sector of directory */
      U16        DirEntryIndex;  /* Index of directory entry */
#if FS_FAT_OPTIMIZE_SEQ_CLUSTERS
      U16        NumAdjClusters; /* Number of cluster that are sequentially in chain behind current one */
#endif
    } Fat;
#if FS_SUPPORT_EFS
    struct {
      U32        DirCluster;     /* Start cluster of directory file */
      U32        DirEntryPos;    /* Offset of directory entry in directory file */
      U32        DataPos;
      U32        DataSize;
      U32        DataCluster;
      U32        NextCluster;
    } Efs;
#endif
} FS_INT_DATA;

typedef struct {      /* Describes the file object structure below the handle */
  U32        FirstCluster;   /* First cluster used for file  */
  U32        Size;           /* size of file                 */
  FS_VOLUME *   pVolume;
  U8         UseCnt;         /* handle in use mark           */
  FS_INT_DATA   Data;
#if FS_MULTI_HANDLE_SAFE
  char          acFullFileName[FS_MAX_LEN_FULL_FILE_NAME];
#endif
#if (FS_PROTECT_LEVEL) >= 2
  unsigned int WriteSize;
  unsigned int MaxSize;
#endif
} FS_FILE_OBJ;

struct FS_FILE { /* Describes the file handle structure */
  FS_FILE_OBJ * pFileObj;
  U32        FilePos;        /* current position in file     */
  I16        Error;          /* error code                   */
  U8         InUse;          /* handle in use mark           */
  U8         AccessFlags;
  U8         FileNameMark[FS_MARKFILENAME_LN];                   
};


/*********************************************************************
*
*       Smart buffer (SB) type, internal
*
*/
struct FS_SB {
  U32 SectorNo;
#if FS_MAINTAIN_FAT_COPY
  U32 WriteCopyOff;  /* Duplicate on write if value is != 0 */
#endif
  FS_PARTITION * pPart;
  U8 * pBuffer;
  char   IsDirty;
  char   HasError;
  U8  Type;
  U8  Read;          /* 1 if data is valid, usually because the sector has been read */
};

typedef struct {
  int   InUse;
  int dummy;	// sunny for byte alignment
#if 0
  U32 aMem[FS_MAX_SECTOR_SIZE / 4];
#else
  U32 aMem;
#endif
} MEM_BLOCK_TYPE;
/*********************************************************************
*
*       Partition related
*/
U32           FS__GetMediaStartSecEx(FS_VOLUME * pVolume, U32 * pNumSectors, U8* pBuffer);
U32           FS__GetMediaStartSec(U8 PartIndex, U8 *pBuffer);
signed char   FS__LocatePartition(FS_VOLUME * pVolume);

/*********************************************************************
*
*       endian translation functions, internal
*/
U32           FS__ReadU32 (const U8 *pBuffer);
U16           FS__ReadU16 (const U8 *pBuffer);
void          FS__WriteU32(      U8 *pBuffer, U32 Data);
void          FS__WriteU16(      U8 *pBuffer, unsigned Data);


/*********************************************************************
*
*       CACHE API type, internal
*
*/
struct FS_CACHE_API {
  char   (*pfReadFromCache)   (void      * pCacheData,   U32 SectorNo,       void * pData, U8  Type);
  char   (*pfUpdateCache)     (FS_DEVICE * pDevice,      U32 SectorNo, const void * pData, U8  Type);    /* Returns 0 if write cached, which means no further write is required */
  void   (*pfInvalidateCache) (void      * pCacheData);
  int    (*pfCommand)         (FS_DEVICE * pDevice   ,   int Cmd, void *p);
  char   (*pfWriteIntoCache)  (FS_DEVICE * pDevice   ,   U32 SectorNo, const void * pData, U8  Type);    /* Returns 0 if write cached, which means no further write is required */

};




/*********************************************************************
*
*       Smart buffer (SB) API-functions, internal
*
*/
void FS__SB_Clean          (FS_SB * pSB);
char FS__SB_Create         (FS_SB * pSB, FS_PARTITION *pPart);
void FS__SB_Delete         (FS_SB * pSB);
void FS__SB_Flush          (FS_SB * pSB);
void FS__SB_MarkDirty      (FS_SB * pSB);
void FS__SB_MarkValid      (FS_SB * pSB, U32 SectorNo, U8 Type);
void FS__SB_MarkNotDirty   (FS_SB * pSB);
char FS__SB_Read           (FS_SB * pSB);
void FS__SB_SetSector      (FS_SB * pSB, U32 SectorNo, U8 Type);
char FS__SB_Write          (FS_SB * pSB);

#if FS_MAINTAIN_FAT_COPY
  void FS__SB_SetWriteCopyOff(FS_SB * pSB, U32 Off);
#endif

/*********************************************************************
*
*       SB-functions, locking and unlocking SB operations
*
*/
void    FS_Lock_SB  (FS_PARTITION * pPart, U32 SectorIndex);
void    FS_Unlock_SB(FS_PARTITION * pPart, U32 SectorIndex);


/*********************************************************************
*
*       Cache related fucntions, internal
*
*/
int FS__CACHE_CommandVolume(FS_VOLUME * pVolume, int Cmd, void * pData);
int FS__CACHE_CommandDevice(FS_DEVICE * pDevice, int Cmd, void * pData);


/*********************************************************************
*
*       Sector allocation API-functions, internal
*
*/
U8 * FS__AllocSectorBuffer(void);
void    FS__FreeSectorBuffer (void * p);

/*********************************************************************
*
*       String operation API-functions, internal
*
*/
const char *   FS__strchr     (const char *s, int c);
void           FS__AddSpaceHex(U32 v, U8 Len, char** ps);

/*********************************************************************
*
*       Volume API-functions, internal
*
*/
FS_VOLUME * FS__FindVolume(const char *pFullName, const char ** pFileName);
int         FS__Mount     (FS_VOLUME * pVolume);
void        FS__Unmount   (FS_VOLUME * pVolume);



/*********************************************************************
*
*       API-functions, internal (without locking)
*
*/
int         FS__FClose           (FS_FILE * pFile);
U32         FS__GetFileSize      (FS_FILE * pFile);
U32         FS__Read             (FS_FILE * pFile,       void * pData, U32 NumBytes);
U32         FS__Write            (FS_FILE * pFile, const void * pData, U32 NumBytes);
int         FS__Verify           (FS_FILE * pFile, const void * pData, U32 NumBytes);
int         FS__Remove           (const char * pFileName);
FS_FILE *   FS__FOpen            (const char * pFileName, const char * pMode);
FS_FILE *   FS__FOpenEx          (const char * pFileName, U8 AccessFlags, char DoCreate, char DoDel, char DoOpen);

U64         FS__CalcSizeInBytes  (U32 NumClusters,   U32 SectorsPerCluster, U32 BytesPerSector);
FS_VOLUME * FS__AddDevice        (const FS_DEVICE_TYPE * pDevType);
int         FS__IoCtl            (FS_VOLUME * pVolume, I32 Cmd, I32 Aux, void *pBuffer);
int         FS__Format           (FS_VOLUME * pVolume, FS_FORMAT_INFO * pFormatInfo);
int         FS__GetNumVolumes    (void);
int         FS__CopyFile         (const char * sSource, const char   * sDest);
int         FS__GetVolumeInfo    (const char * sVolume, FS_DISK_INFO * pInfo);
int         FS__GetVolumeInfoEx  (FS_VOLUME  * pVolume, FS_DISK_INFO * pInfo);
int         FS__MkDir            (const char * pDirName);
int         FS__RmDir            (const char * pDirName);
int         FS__FSeek            (FS_FILE *pFile, I32 Offset, int Origin);
I32         FS__FTell            (FS_FILE *pFile);
int         FS__GetFileTime      (const char * pName, U32 * pTimeStamp);
int         FS__SetFileTime      (const char * pName, U32   TimeStamp);
int         FS__SetFileAttributes(const char * pName, U8    Attributes);
U8          FS__GetFileAttributes(const char * pName);
int         FS__SetEndOfFile     (FS_FILE    * pFile);
void        FS__RemoveDevice     (FS_VOLUME  * pVolume);

#if FS_POSIX_DIR_SUPPORT
FS_DIR    * FS__OpenDir    (const char *pDirName);
FS_DIRENT * FS__ReadDir    (FS_DIR *pDir);
int         FS__CloseDir   (FS_DIR *pDir);
void        FS__RewindDir  (FS_DIR *pDir);
void        FS__DirEnt2Attr(FS_DIRENT *pDirEnt, U8* pAttr);
U32         FS__GetNumFiles(FS_DIR *pDir);
#endif

/*********************************************************************
*
*       API-functions, file handle operations
*
*/
FS_FILE * FS__AllocFileHandle(void);
void      FS__FreeFileHandle(FS_FILE * pFile);

/*********************************************************************
*
*       API-functions, file object operations
*
*/
FS_FILE_OBJ * FS__AllocFileObj(const char  * sFullFileName);
FS_FILE_OBJ * FS__GetFileObj  (const char  * sFullFileName);
void          FS__FreeFileObj (FS_FILE_OBJ * pFileObj);
int           FS__BuildFullFileName(FS_VOLUME * pVolume, const char * sFileName, char * pString);


/*********************************************************************
*
*       ECC256
*
*/
int  FS__ECC256_Apply(U32 * pData, U32 eccRead);
U32  FS__ECC256_Calc (const U32 * pData);
U32  FS__ECC256_Load (const U8 * p);
void FS__ECC256_Store(U8 * p, U32 ecc);


/*********************************************************************
*
*       Public data
*
*/
extern FS_FILE     FS__aFilehandle [FS_NUM_FILE_HANDLES];
extern FS_FILE_OBJ FS__aFileObj    [FS_NUM_FILE_OBJECTS];
extern FS_VOLUME   FS__aVolume     [FS_NUM_VOLUMES];

#if FS_POSIX_DIR_SUPPORT
extern FS_DIR      FS__aDirHandle  [FS_DIR_MAXOPEN];
#endif

#if ((FS_OS) && (FS_OS_LOCK_PER_FILE))              /* Fine lock granularity */
typedef struct {
  const FS_DEVICE_TYPE * pDeviceType;
  U8                     UseCnt;
} FS_DEVICE_LOCK_TABLE;
extern FS_DEVICE_LOCK_TABLE FS__aDeviceLockTable[FS_NUM_DEVICES];
#endif
/*********************************************************************
*
*       OS mapping macros (multi tasking locks)
*
*
* Notes
*   These macros map to locking routines or are empty,
*   depending on the configuration
*   There are 3 different lock-levels:
*   FS_OS == 0                     -> No locking
*   FS_OS == 1
*     FS_OS_LOCK_PER_FILE == 0     -> Single, global lock in every API function
*     FS_OS_LOCK_PER_FILE == 1     -> Multiple locks
*
**********************************************************************
*/

#if (FS_OS == 0)                               /* No locking */
  #define FS_LOCK()                            /* Global lock, used in API functions */
  #define FS_UNLOCK()

  #define FS_LOCK_FILE(pFile)
  #define FS_UNLOCK_FILE(pFile)

  #define FS_LOCK_FILEOBJ(pFileObj)
  #define FS_UNLOCK_FILEOBJ(pFileObj)

  #define FS_LOCK_DIR(pDir)
  #define FS_UNLOCK_DIR(pDir)

  #define FS_LOCK_VOLUME(pVolume)
  #define FS_UNLOCK_VOLUME(pVolume)

  #define FS_LOCK_SB(pPart, SectorIndex)
  #define FS_UNLOCK_SB(pPart, SectorIndex)

  #define FS_LOCK_DEVICE(pDevice)
  #define FS_UNLOCK_DEVICE(pDevice)

  #define FS_LOCK_SYS()
  #define FS_UNLOCK_SYS()

  #define FS_OS_INIT()             0
  #define FS_OS_EXIT()             0

#elif (FS_OS) && (FS_OS_LOCK_PER_FILE == 0)    /* Coarse lock granularity: One global lock for all FS API functions */
  #define FS_LOCK_ID_SYSTEM          0
  #define FS_NUM_LOCKS               1   /* To be used in OS module */

  /* Only global lock is used */
  #define FS_LOCK()           FS_X_OS_Lock(FS_LOCK_ID_SYSTEM)
  #define FS_UNLOCK()         FS_X_OS_Unlock(FS_LOCK_ID_SYSTEM)

  #define FS_LOCK_FILE(pFile)
  #define FS_UNLOCK_FILE(pFile)

  #define FS_LOCK_FILEOBJ(pFileObj)
  #define FS_UNLOCK_FILEOBJ(pFileObj)

  #define FS_LOCK_DIR(pDir)
  #define FS_UNLOCK_DIR(pDir)

  #define FS_LOCK_VOLUME(pVolume)
  #define FS_UNLOCK_VOLUME(pVolume)

  #define FS_LOCK_SB(pPart, SectorIndex)
  #define FS_UNLOCK_SB(pPart, SectorIndex)

  #define FS_LOCK_DEVICE(pDevice)
  #define FS_UNLOCK_DEVICE(pDevice)

  #define FS_LOCK_SYS()
  #define FS_UNLOCK_SYS()

  #define FS_OS_INIT()                       FS_X_OS_Init()
  #define FS_OS_EXIT()                       FS_X_OS_Exit()

#else                                                                  /* Fine lock granularity: lock for different FS functions*/
  #define FS_LOCK_ID_SYSTEM          0
  #define FS_LOCK_ID_DEVICE          1
  #define FS_LOCK_ID_SB              (FS_LOCK_ID_DEVICE  + FS_NUM_DEVICES + 1)  /* One add. lock for devices which are unknown at compile time */
  #define FS_LOCK_ID_VOLUME          (FS_LOCK_ID_SB      + FS_NUM_SBLOCKS)
  #define FS_LOCK_ID_FILEOBJ         (FS_LOCK_ID_VOLUME  + FS_NUM_VOLUMES)
  #define FS_LOCK_ID_FILE            (FS_LOCK_ID_FILEOBJ + FS_NUM_FILE_OBJECTS)
  #define FS_LOCK_ID_DIR             (FS_LOCK_ID_FILE    + FS_NUM_FILE_HANDLES)

  #define FS_NUM_LOCKS               (FS_LOCK_ID_DIR     + FS_DIR_MAXOPEN) /* To be used in OS module */

#if 0   // 20060627 Sunny for device semaphore
  /* Global lock is not used */
  #define FS_LOCK()
  #define FS_UNLOCK()

  #define FS_LOCK_FILE(pFile)                FS_OS_LockFile(pFile)
  #define FS_UNLOCK_FILE(pFile)              FS_OS_UnlockFile(pFile)
  void    FS_OS_LockFile  (FS_FILE * pFile);
  void    FS_OS_UnlockFile(FS_FILE * pFile);

  #define FS_LOCK_FILEOBJ(pFileObj)          FS_OS_LockFileObj  (pFileObj)
  #define FS_UNLOCK_FILEOBJ(pFileObj)        FS_OS_UnlockFileObj(pFileObj)
  void    FS_OS_LockFileObj  (FS_FILE_OBJ * pFileObj);
  void    FS_OS_UnlockFileObj(FS_FILE_OBJ * pFileObj);

  #define FS_LOCK_DIR(pDir)                  FS_OS_LockDir  (pDir)
  #define FS_UNLOCK_DIR(pDir)                FS_OS_UnlockDir(pDir)
  void    FS_OS_LockDir  (FS_DIR * pDir);
  void    FS_OS_UnlockDir(FS_DIR * pDir);

  #define FS_LOCK_VOLUME(pVolume)            FS_OS_LockVolume  (pVolume)
  #define FS_UNLOCK_VOLUME(pVolume)          FS_OS_UnlockVolume(pVolume)
  void    FS_OS_LockVolume  (FS_VOLUME * pVolume);
  void    FS_OS_UnlockVolume(FS_VOLUME * pVolume);

  #define FS_LOCK_DEVICE(pDevice)            FS_OS_LockDevice  (pDevice)
  #define FS_UNLOCK_DEVICE(pDevice)          FS_OS_UnlockDevice(pDevice)
  void    FS_OS_LockDevice  (const FS_DEVICE * pDevice);
  void    FS_OS_UnlockDevice(const FS_DEVICE * pDevice);

  #define FS_LOCK_SB(pPart, SectorIndex)     FS_OS_Lock_SB  (pPart, SectorIndex)
  #define FS_UNLOCK_SB(pPart, SectorIndex)   FS_OS_Unlock_SB(pPart, SectorIndex)
  void FS_OS_Lock_SB  (FS_PARTITION * pPart, U32 SectorIndex);
  void FS_OS_Unlock_SB(FS_PARTITION * pPart, U32 SectorIndex);

  #define FS_LOCK_SYS()                      FS_X_OS_Lock  (FS_LOCK_ID_SYSTEM)
  #define FS_UNLOCK_SYS()                    FS_X_OS_Unlock(FS_LOCK_ID_SYSTEM)

  #define FS_OS_INIT()                       FS_X_OS_Init()
  #define FS_OS_EXIT()                       FS_X_OS_Exit()
#else
  /* Global lock is not used */
  #define FS_LOCK()
  #define FS_UNLOCK()
  #define FS_LOCK_FILE(pFile)                //FS_OS_LockFile(pFile)
  #define FS_UNLOCK_FILE(pFile)              //FS_OS_UnlockFile(pFile)
  void    FS_OS_LockFile  (FS_FILE * pFile);
  void    FS_OS_UnlockFile(FS_FILE * pFile);
  #define FS_LOCK_FILEOBJ(pFileObj)          //FS_OS_LockFileObj  (pFileObj)
  #define FS_UNLOCK_FILEOBJ(pFileObj)        //FS_OS_UnlockFileObj(pFileObj)
  void    FS_OS_LockFileObj  (FS_FILE_OBJ * pFileObj);
  void    FS_OS_UnlockFileObj(FS_FILE_OBJ * pFileObj);
  #define FS_LOCK_DIR(pDir)                  //FS_OS_LockDir  (pDir)
  #define FS_UNLOCK_DIR(pDir)                //FS_OS_UnlockDir(pDir)
  void    FS_OS_LockDir  (FS_DIR * pDir);
  void    FS_OS_UnlockDir(FS_DIR * pDir);
  #define FS_LOCK_VOLUME(pVolume)            //FS_OS_LockVolume  (pVolume)
  #define FS_UNLOCK_VOLUME(pVolume)          //FS_OS_UnlockVolume(pVolume)
  void    FS_OS_LockVolume  (FS_VOLUME * pVolume);
  void    FS_OS_UnlockVolume(FS_VOLUME * pVolume);
  #define FS_LOCK_DEVICE(pDevice)            FS_OS_LockDevice  (pDevice)
  #define FS_UNLOCK_DEVICE(pDevice)          FS_OS_UnlockDevice(pDevice)
  void    FS_OS_LockDevice  (const FS_DEVICE * pDevice);
  void    FS_OS_UnlockDevice(const FS_DEVICE * pDevice);
  #define FS_LOCK_SB(pPart, SectorIndex)     FS_OS_Lock_SB  (pPart, SectorIndex)
  #define FS_UNLOCK_SB(pPart, SectorIndex)   FS_OS_Unlock_SB(pPart, SectorIndex)
  void FS_OS_Lock_SB  (FS_PARTITION * pPart, FS_U32 SectorIndex);
  void FS_OS_Unlock_SB(FS_PARTITION * pPart, FS_U32 SectorIndex);
  #define FS_LOCK_SYS()                      FS_X_OS_Lock  (FS_LOCK_ID_SYSTEM)
  #define FS_UNLOCK_SYS()                    FS_X_OS_Unlock(FS_LOCK_ID_SYSTEM)
  #define FS_OS_INIT()                       FS_X_OS_Init()
  #define FS_OS_EXIT()                       FS_X_OS_Exit()
#endif

#endif

/*********************************************************************
*
*       API mapping macros
*
*       These macros map to the functions of the file system (Currently FAT or EFS)
*       or - in case of multiple file systems - to a mapping layer, which calls the
*       appropriate function depending on the filesystem of the volume
*
**********************************************************************
*/

#define FS_IOCTL(    pVolume, Cmd, Aux, pBuffer)                FS_LB_ioctl(pVolume, Cmd, Aux, pBuffer)

#if   (FS_SUPPORT_FAT) && (! FS_SUPPORT_EFS)
  #define FS_CHECK_INFOSECTOR(pVolume, pBuffer)                   FS_FAT_CheckBPB(pVolume, pBuffer)
  #define FS_CLOSEDIR(pDir)                                       FS_FAT_CloseDir(pDir);
  #define FS_CREATEDIR(pVolume, s)                                FS_FAT_CreateDir(pVolume, s)
  #define FS_FCLOSE(   hFile)                                     FS_FAT_FClose(hFile)
  #define FS_FOPEN(    s,       pFile, DoDel, DoOpen, DoCreate)   FS_FAT_FOpen(s, pFile, DoDel, DoOpen, DoCreate)
  #define FS_FORMAT( pVolume,  pFormatInfo)                       FS_FAT_Format(pVolume, pFormatInfo)
  #define FS_FREAD(    pFile,   pData, NumBytes)                  FS_FAT_FRead(pFile, pData, NumBytes)
  #define FS_FWRITE(   pFile,   pData, NumBytes)                  FS_FAT_FWrite(pFile, pData, NumBytes)
  #define FS_GETDIRENTRYINFO(pVolume, sName, p, Mask)             FS_FAT_GetDirEntryInfo(pVolume, sName, p, Mask)
  #define FS_GET_DISKINFO(  pVolume, pInfo)                       FS_FAT_GetDiskInfo(pVolume, pInfo)
  #define FS_MOVE(     sSrc,    sDest, pVolume)                   FS_FAT_Move(sSrc, sDest, pVolume)
  #define FS_OPENDIR(  s,       pDirHandle)                       FS_FAT_OpenDir(s, pDirHandle)
  #define FS_READDIR(  pDir)                                      FS_FAT_ReadDir(pDir)
  #define FS_REMOVEDIR(pVolume, s)                                FS_FAT_RemoveDir(pVolume, s)
  #define FS_RENAME(   s,       sNewName, pVolume)                FS_FAT_Rename(s, sNewName, pVolume)
  #define FS_SETDIRENTRYINFO(pVolume, sName, p, Mask)             FS_FAT_SetDirEntryInfo(pVolume, sName, p, Mask)
  #define FS_SET_END_OF_FILE(pFile)                               FS_FAT_SetEndOfFile(pFile)
  #define FS_UNMOUNT(pVolume)                                     FS_FAT_Unmount(pVolume)
  #define FS_GET_VOLUME_LABEL(pVol, pVolLabel, VolLabelSize)      FS_FAT_GetVolumeLabel(pVolume, pVolLabel, VolLabelSize)
  #define FS_SET_VOLUME_LABEL(pVol, pVolLabel)                    FS_FAT_SetVolumeLabel(pVolume, pVolLabel)
#elif (! FS_SUPPORT_FAT) && (FS_SUPPORT_EFS)
  #define FS_CHECK_INFOSECTOR(pVolume, pBuffer)                   FS_EFS_CheckInfoSector(pVolume, pBuffer)
  #define FS_CLOSEDIR( pDir)                                      FS_EFS_CloseDir(pDir)
  #define FS_CREATEDIR(pVolume, s)                                FS_EFS_CreateDir(pVolume, s)
  #define FS_FCLOSE(   hFile)                                     FS_EFS_FClose(hFile)
  #define FS_FOPEN(    s,       pFile, DoDel, DoOpen, DoCreate)   FS_EFS_FOpen(s, pFile, DoDel, DoOpen, DoCreate)
  #define FS_FORMAT( pVolume,  pFormatInfo)                       FS_EFS_Format(pVolume, pFormatInfo)
  #define FS_FREAD(    pFile,   pData, NumBytes)                  FS_EFS_FRead(pFile, pData, NumBytes)
  #define FS_FWRITE(   pFile,   pData, NumBytes)                  FS_EFS_FWrite(pFile, pData, NumBytes)
  #define FS_GETDIRENTRYINFO(pVolume, sName, p, Mask)             FS_EFS_GetDirEntryInfo(pVolume, sName, p, Mask)
  #define FS_GET_DISKINFO(  pVolume, pInfo)                       FS_EFS_GetDiskInfo(pVolume, pInfo)
  #define FS_MOVE(     sSrc,    sDest, pVolume)                   FS_EFS_Move(sSrc, sDest, pVolume)
  #define FS_OPENDIR(  s,       pDirHandle)                       FS_EFS_OpenDir(s, pDirHandle)
  #define FS_READDIR(  pDir)                                      FS_EFS_ReadDir(pDir)
  #define FS_REMOVEDIR(pVolume, s)                                FS_EFS_RemoveDir(pVolume, s)
  #define FS_RENAME(   s,       sNewName, pVolume)                FS_EFS_Rename(s, sNewName, pVolume)
  #define FS_SETDIRENTRYINFO(pVolume, sName, p, Mask)             FS_EFS_SetDirEntryInfo(pVolume, sName, p, Mask)
  #define FS_SET_END_OF_FILE(pFile)                               FS_EFS_SetEndOfFile(pFile)
  #define FS_UNMOUNT(pVolume)                                     FS_EFS_Unmount(pVolume)
  #define FS_GET_VOLUME_LABEL(pVol, pVolLabel, VolLabelSize)      FS_EFS_GetVolumeLabel(pVolume, pVolLabel, VolLabelSize)
  #define FS_SET_VOLUME_LABEL(pVol, pVolLabel)                    FS_EFS_SetVolumeLabel(pVolume, pVolLabel)
#else
#error FS_SUPPORT_MULTIPLE_FS: Multiple simulanteous file systems not yet supported
  #define FS_CHECK_INFOSECTOR(pVolume, pBuffer)                   FS_MAP_CheckFS_API(pVolume, pBuffer)
  #define FS_CLOSEDIR( pDir)                                      FS_MAP_CloseDir(pDir)
  #define FS_CREATEDIR(pVolume, s)                                FS_MAP_CreateDir(pVolume, s)
  #define FS_FCLOSE(   hFile)                                     FS_MAP_FClose(hFile)
  #define FS_FOPEN(    s,       pFile, DoDel, DoOpen, DoCreate)   FS_MAP_FOpen(s, pFile, DoDel, DoOpen, DoCreate)
  #define FS_FORMAT( pVolume,  pFormatInfo)                       FS_MAP_Format(pVolume, pFormatInfo)
  #define FS_FREAD(    pFile,   pData, NumBytes)                  FS_MAP_FRead(pFile, pData, NumBytes)
  #define FS_FWRITE(   pFile,   pData, NumBytes)                  FS_MAP_FWrite(pFile, pData, NumBytes)
  #define FS_GETDIRENTRYINFO(pVolume, sName, p, Mask)             FS_MAP_GetDirEntryInfo(pVolume, sName, p, Mask)
  #define FS_GET_DISKINFO(pVolume, pInfo)                         FS_MAP_GetDirInfo(pVolume, pInfo)
  #define FS_MOVE(     sSrc,    sDest, pVolume)                   FS_MAP_Move(sSrc, sDest, pVolume)
  #define FS_OPENDIR(  s,       pDirHandle)                       FS_MAP_OpenDir(s, pDirHandle)
  #define FS_READDIR(  pDir)                                      FS_MAP_ReadDir(pDir)
  #define FS_REMOVEDIR(pVolume, s)                                FS_MAP_RemoveDir(pVolume, s)
  #define FS_RENAME(   s,       sNewName, pVolume)                FS_MAP_Rename(s, sNewName, pVolume)
  #define FS_SETDIRENTRYINFO(pVolume, sName, p, Mask)             FS_MAP_SetDirEntryInfo(pVolume, sName, p, Mask)
  #define FS_SET_END_OF_FILE(pFile)                               FS_MAP_SetEndOfFile(pFile)
  #define FS_UNMOUNT(pVolume)                                     FS_MAP_Unmount(pVolume)
  #define FS_GET_VOLUME_LABEL(pVol, pVolLabel, VolLabelSize)      FS_MAP_GetVolumeLabel(pVolume, pVolLabel, VolLabelSize)
  #define FS_SET_VOLUME_LABEL(pVol, pVolLabel)                    FS_MAP_SetVolumeLabel(pVolume, pVolLabel)
#endif

void        FS_MAP_FClose         (FS_FILE    * pFile);
int         FS_MAP_CheckFS_API    (FS_VOLUME  * pVolume,    U8  * pBuffer);
U32      FS_MAP_FRead          (FS_FILE    * pFile,       void  * pData, U32 NumBytes);
FS_SIZE_T   FS_MAP_FWrite         (FS_FILE    * pFile, const void  * pData, U32 NumBytes);
char        FS_MAP_FOpen          (const char * pFileName, FS_FILE * pFile, char DoDel, char DoOpen, char DoCreate);
int         FS_MAP_Format         (FS_VOLUME  * pVolume, FS_FORMAT_INFO * pFormatInfo);
int         FS_MAP_OpenDir        (const char * pDirName,  FS_DIR  * pDir);
int         FS_MAP_CloseDir       (FS_DIR     * pDir);
FS_DIRENT * FS_MAP_ReadDir        (FS_DIR     * pDir);
int         FS_MAP_RemoveDir      (FS_VOLUME  * pVolume,  const char * pDirName);
int         FS_MAP_CreateDir      (FS_VOLUME  * pVolume,  const char * pDirName);
int         FS_MAP_Rename         (const char * sOldName, const char * sNewName, FS_VOLUME * pVolume);
int         FS_MAP_Move           (const char * sOldName, const char * sNewName, FS_VOLUME * pVolume);
char        FS_MAP_SetDirEntryInfo(FS_VOLUME  * pVolume,  const char * sName, const void * p, int Mask);
char        FS_MAP_GetDirEntryInfo(FS_VOLUME  * pVolume,  const char * sName,       void * p, int Mask);
int         FS_MAP_SetEndOfFile   (FS_FILE    * pFile);
void        FS_MAP_Unmount        (FS_VOLUME  * pVolume);
int         FS_MAP_GetDiskInfo    (FS_VOLUME  * pVolume, FS_DISK_INFO * pDiskData);
int         FS_MAP_GetVolumeLabel (FS_VOLUME * pVolume, char * pVolumeLabel, unsigned VolumeLabelSize);
int         FS_MAP_SetVolumeLabel (FS_VOLUME * pVolume, const char * pVolumeLabel);

/*********************************************************************
*
*       Public const
*
**********************************************************************
*/
#if FS_SUPPORT_MULTIPLE_FS
  extern const FS_FS_API FS_FAT_API;
  extern const FS_FS_API FS_EFS_API;
#endif

#if defined(__cplusplus)
}                /* Make sure we have C-declarations in C++ programs */
#endif

#endif  /* _FS_INT_H_ */

/*************************** End of file ****************************/
	 	 			 		    	 				 	   		   	 		  	 	      	   		 	 	  	  		  	 		 	   		 		      		       	   	 			  	     	   		 		     			    	 		 	    		 					 	 	  	  	 	 		 		 	    		 			  		 	  	 		  			 		 			  		 
