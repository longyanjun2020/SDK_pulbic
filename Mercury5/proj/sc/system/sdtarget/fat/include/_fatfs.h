////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @file    fatfs.h
 * @brief   This module defines the internal FAT API layer 
 */
#ifndef ___FATFS_H__
#define ___FATFS_H__

/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#include "stdio.h"
#include "stdcomp.h"

/*--------------------------------------------------------------------------*/
/* CONSTANT DEFINITIONS */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* PREPROCESSOR CONSTANT DEFINITION                                         */
/*--------------------------------------------------------------------------*/
#define FAT_CACHE_SIZE 4096
#define ROOT_CACHE_SIZE 512
#define SECTOR_SIZE 512
#define DENTRY_SIZE 0x20 // Dir entry size
#define INVALID_START_POS 0xFFFFFFFF

#define TENTRY_REGULAR 0 // Used when entry points to next file cluster 
#define TENTRY_FREE 1 // Free cluster
#define TENTRY_LAST 2 // Last cluster of file 
#define TENTRY_RESERVED 3 // Reserved cluster
#define TENTRY_BAD 4 // Bad cluster 
/*--------------------------------------------------------------------------*/
/* PREPROCESSOR MACRO DEFINITION                                            */
/*--------------------------------------------------------------------------*/
#define DENTRY_IS_DELETED(_dentry_)  (0xE5 == (u8)((_dentry_).szName[0]))

#define DENTRY_IS_ZERO(_dentry_) (0x00 == (u8)((_dentry_).szName[0]))

#define DENTRY_IS_EXTNAME( _dentry_) (0x0F == (_dentry_).nAttr)

#define GET_BYTE(_data_, _var_, _off_) \
    (_var_ = *( ((u8 *)_data_) + (_off_) ) )

#define GET_WORD(_data_, _var_, _off_) \
    (_var_ = *( ((u8 *)_data_) + (_off_) ) | \
    *( ((u8 *)_data_) + (_off_) + 1 ) << 8)

#define GET_DWORD(_data_, _var_, _off_) \
    (_var_ = *( ((u8 *)_data_) + (_off_)) | \
    *( ((u8 *)_data_) + (_off_) + 1 ) << 8 | \
    *( ((u8 *)_data_) + (_off_) + 2 ) << 16 | \
    *( ((u8 *)_data_) + (_off_) + 3 ) << 24)

#define GET_BYTES(_data_, _var_, _size_, _off_) \
    memcpy((void *)(_var_), (void*)(((u8 *)_data_)+(_off_)),_size_)
/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
typedef struct 
{
    u8 nStatus;
    //u8 nHead1;
    //u8 nSector1;
    //u8 nCylinder1;
    u8 nType;
    //u8 nHead2;
    //u8 nSector2;
    //u8 nCylinder2;
    u32 nLBA;
    //u32 nTotalBlock;
}PartitionTable_t;

typedef struct
{
    u16 nJump;           // 00h : Jump code
    //s8 szOemName[8+1];  // 03h : OEM name
    u16 nBytesPerSec;  // 0Bh : cyg_bytes per sector
    u8 nSecPerClu;    // 0Dh : Sectors per cluster
    u16 nResSecNum;    // 0Eh : Number of reserved sectors
    u8 nFatTblsNum;   // 10h : Number of copies of fat
    u16 nMaxRootDents; // 11h : Maximum number of root dir entries
    u16 nSecNum;     // 13h : Number of sectors in partition < 32MB
    //u8 nMediaDesc;     // 15h : Media descriptor
    u16 nSecPerFat;    // 16h : Sectors per FAT
    //u16 nSecPerTrack;  // 18h : Sectors per track
    //u16 nHeadsNum;      // 1Ah : Number of heads
    //u32 nHSecNum;       // 1Ch : Number of hidden sectors
    u32 nSecNum32;        // 20h : Number of sectors in partition
    u8 nExeMarker[2];  // 1FEh: Executable marker (55h AAh)

// FAT32 specific fields
 
    u32 nSecPerFat32; // 24h : Sectors per FAT
    //u16 nExtFlags;      // 28h : Flags
    //u16 nFsVer;         // 2Ah : FS version
    u32 nRootCluster;   // 2Ch : Root dir cluster
    //u16 nFsInfoSec;    // 30h : Sector number of FSINFO structure
    //u16 nBkBootSec;    // 32h : Sector number of backup boot record

// Fields with different locations on FAT12/16 and FAT32 
        
    //u8 nDrvNum;        // 24h (40h) : Drive number of partition 
    //u8 nExtSig;        // 26h (42h) : Extended signature
    //u32 nSerNum;        // 27h (43h) : Serial number of partition
    //s8 szVolName[11+1]; // 2Bh (47h) : Volume name of partition
    //s8 szFatName[8+1];  // 36h (52h) : FAT name
} FatBootRecord_t;

typedef struct
{
    u8 szName[8+3+1];   // 00h : Name
    u8 nAttr;                  // 0Bh : Attribute
    //u8 nNTRes;               // 0Ch : Win NT Reserved field
    //u8 nCrtTimeTenth;    // 0Dh : Creation time ms stamp 0 - 199
    //u16 nCrtTime;           // 0Eh : Creation time
    //u16 nCrtDate;           // 10h : Creation date
    //u16 nLstAccData;      // 12h : Last access date
    u16 nFstClusHI;        // 14h : Starting cluster HI WORD (FAT32)
    //u16 nWrtTime;          // 16h : Time    
    //u16 nWrtDate;          // 18h : Date
    u16 nFstClusLO;        // 1Ah : Starting cluster 
    u32 nFileSize;           // 1Ch : Size of the file
} FatDirEntry_t;

typedef enum
{
    FATFS_FAT12 = 0,    
    FATFS_FAT16,
    FATFS_FAT32
} FatfsType_u;

typedef struct
{
    u32 nSectorSize;          // Sector size in bytes
    u32 nSectorSizeLog2;     // Sector size log2
    u32 nClusterSize;         // Cluster size in bytes
    u32 nClusterSizeLog2;    // Cluster size log2 
    u32 nFatTblPos;          // Position of the first FAT table
    u32 nFatTblSize;         // FAT table size in bytes
    u32 nFatTblNents;        // Number of entries in FAT table
    u32 nFatTblsNum;         // Number of FAT tables
    u32 nFatRootDirPos;     // Position of the root dir
    u32 nFatRootDirSize;    // Root dir size in bytes 
    u32 nFatRootDirNents;   // Max number of entries in root dir
    u32 nFatRootDirCluster; // Cluster number of root dir (FAT32) 
    u32 nFatDataPos;         // Position of data area
    FatfsType_u uFatType;             // Type of FAT - 12, 16 or 32 
}FatfsDisk_t;

/*--------------------------------------------------------------------------*/
/* GLOBAL VARIABLE DEFINITION                                               */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION DEFINITION                                               */
/*--------------------------------------------------------------------------*/


#endif //#ifndef ___FATFS_H__
