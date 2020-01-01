/*
**********************************************************************
*                          Ait, Inc.
*
*                            exFAT
*
*             (c) Copyright 2014 - 2020, AIT, Inc.
*                      All rights reserved.
*
***********************************************************************

----------------------------------------------------------------------
File        : exFAT_Format.c
Purpose     : Implementation of EX_FAT_Format
---------------------------END-OF-HEADER------------------------------
*/

#ifndef __EXFAT_INT_H__
#define __EXFAT_INT_H__


/*********************************************************************
*
*             Global data types
*
**********************************************************************
*/

typedef struct tagFS_EXFAT_INFO
{
    U64   ullVolumeOffset;       // In sector
    U64     ullTotalSectors;       // In sector
	U32     ulNumFreeClusters;       
    U32     uiSectorSizeShift;     // In Byte after shifting
    U32     uiClusterSizeInSector; // In sector
    U32     uiNumOfCluster;        //
    U32     uiNumOfFat;            //
    U32     ui1stFatPos;           // In sector
    U32     ui2ndFatPos;           // In sector
    U32     uiFatLength;           // In sector
    U32     uiDataRegionPosInSector;
    U32     ui1stAllocBitmapPos;   // In cluster
    U32     ui2ndAllocBitmapPos;   // In cluster
    U32     uiAllocBitmapSize;     // In byte
    U32     uiUpCaseTablePos;      // In sector
    U32     uiUpCaseTableSize;     // In byte

    U32     uiVolumeLabelEntryNo;
    U16     uwVolumeLabel[11];

    U32     uiFirstClusterOfRootDir;   // In cluster

    U32     uiFirstFreeCluster;   // 0 => cluster 2 ,  max value = num of clusters -1

    U32     uiPercentage;
    U8      byActiveFat;
    U8      bDirty;

} FS_EXFAT_INFO, *PFS_EXFAT_INFO;


typedef struct tagEXFAT_DIR_POS {
  U32 Cluster;                    /* Cluster of current sector */
  U32 FirstCluster;
  U32 DirEntryIndex;              /* Directory entry index (first directory entry has index 0 */
  U32 ClusterIndex;
  U32 NumOfDirEntry;
  U8  NoFatChain;
} EXFAT_DIR_POS;





/*********************************************************************
*
*             Volume
*
**********************************************************************
*/
int EXFAT_GetVolumeLabel(FS_VOLUME * pVolume, char * pVolumeLabel, unsigned VolumeLabelSize);
int EXFAT_SetVolumeLabel(FS_VOLUME * pVolume, const char * pVolumeLabel);
int EXFAT_GetDiskInfo(FS_VOLUME * pVolume, FS_DISK_INFO * pDiskData);
U64 EXFAT_GetDiskSpace(FS_VOLUME * pVolume);


/*********************************************************************
*
*             File
*
**********************************************************************
*/
int EXFAT_FOpen(const char *pFilePath, FS_FILE *pFile, char DoDel, char DoOpen, char DoCreate );
void EXFAT_FClose(FS_FILE *pFile);
FS_SIZE_T EXFAT_FWrite(FS_FILE *pFile, const void *pData, U32 NumBytes);
FS_SIZE_T EXFAT_FRead(FS_FILE *pFile, void *pData, U32 NumBytesReq);
int EXFAT_Move(const char * sOldName, const char * sNewName, FS_VOLUME * pVolume);
int EXFAT_Rename(const char * sOldName, const char * sNewName, FS_VOLUME * pVolume);
int EXFAT_SetEndOfFile(FS_FILE * pFile);


/*********************************************************************
*
*             Dir
*
**********************************************************************
*/
int EXFAT_OpenDir(const char *pDirName, FS_DIR *pDir);
int EXFAT_CloseDir(FS_DIR *pDir);
FS_DIRENT * EXFAT_ReadDir(FS_DIR *pDir);
int  EXFAT_CreateDir(FS_VOLUME * pVolume, const char *pDirName);
int  EXFAT_RemoveDir(FS_VOLUME * pVolume, const char *pDirName);


/*********************************************************************
*
*             Dir Entry Info
*
**********************************************************************
*/
char EXFAT_GetDirEntryInfo(FS_VOLUME * pVolume, const char * sName, void * p, int Mask);
char EXFAT_SetDirEntryInfo(FS_VOLUME * pVolume, const char * sName, const void * p, int Mask);


/*********************************************************************
*
*             Format
*
**********************************************************************
*/
int _ExFatFormatEx(FS_VOLUME* pVolume, U32 NumSectors, U8  Media, U16 SecPerTrk, U16 NumHeads, U16  SectorsPerCluster, U16 NumRootDirEntriesProp, U16 BytesPerSector);

#endif //__EXFAT_INT_H__

/*************************** End of File ****************************/

