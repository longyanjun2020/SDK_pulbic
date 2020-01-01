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
File    : FS_ConfDefaults.h
Purpose : File system configuration defaults
--------  END-OF-HEADER  ---------------------------------------------
*/

#ifndef _FS_CONFDEFAULT_H_
#define _FS_CONFDEFAULT_H_

#include "fs_conf.h"
#include "gui_global.h"

/*********************************************************************
*
*       define global data types
*
**********************************************************************
*/
#ifndef FS_U64
  #define FS_U64        U64      /* 64 bit unsigned */
#endif
#ifndef FS_I64
  #define FS_I64        I64      /* 64 bit   signed */
#endif
#ifndef FS_U32
  #define FS_U32        U32      /* 32 bit unsigned */
#endif
#ifndef FS_I32
  #define FS_I32        I32      /* 32 bit   signed */
#endif
#ifndef FS_U16
  #define FS_U16        U16      /* 16 bit unsigned */
#endif
#ifndef FS_I16
  #define FS_I16        I16      /* 16 bit   signed */
#endif
#ifndef FS_U8
  #define FS_U8         U8       /*  8 bit unsigned */
#endif
#ifndef FS_SIZE_T
  #define FS_SIZE_T     U32
#endif

/*********************************************************************
*
*       Defaults for optimizations
*
**********************************************************************
*/

#ifndef FS_IS_LITTLE_ENDIAN
  #define FS_IS_LITTLE_ENDIAN   0          /* Optimization for LE systems: File system can work more efficiently on little endian systems. */
#endif

#if FS_IS_LITTLE_ENDIAN
  #define FS_WRITE_U16(pBuffer, Data)  *(U16*)pBuffer = Data
  #define FS_READ_U16(pBuffer)         (*(U16*)pBuffer)
#else
  #define FS_WRITE_U16(pBuffer, Data)             \
              * (U8*)pBuffer      = (U8)Data;      \
              *((U8*)pBuffer + 1) = (U8)(Data >> 8);
  #define FS_READ_U16(pBuffer)     (U16) ((*(U8*)pBuffer)  |  (*((U8*)pBuffer + 1) << 8))
#endif

/*********************************************************************
*
*       Device Driver Support
*
**********************************************************************
*/

#ifndef   FS_USE_SMC_DRIVER
  #define FS_USE_SMC_DRIVER       0    /* SmartMedia card driver       */
#endif
#ifndef   FS_USE_IDE_DRIVER
  #define FS_USE_IDE_DRIVER       0    /* IDE driver                   */
#endif
#ifndef   FS_USE_WINDRIVE_DRIVER
  #define FS_USE_WINDRIVE_DRIVER  0    /* Windows Logical Drive driver */
#endif
#ifndef   FS_USE_RAMDISK_DRIVER
  #define FS_USE_RAMDISK_DRIVER   0    /* RAM Disk driver              */
#endif
#ifndef   FS_USE_MMC_DRIVER
  #define FS_USE_MMC_DRIVER       1    /* MMC/SD card driver 	       */
#endif
#ifndef   FS_USE_FLASH_DRIVER
  #define FS_USE_FLASH_DRIVER     0    /* Generic flash driver         */
#endif

#ifndef   FS_USE_GENDEV_DRIVER
  #define FS_USE_GENDEV_DRIVER    0   /* Generic device driver         */
#endif

#ifndef   FS_USE_SFLASH_DRIVER
  #define FS_USE_SFLASH_DRIVER    1   /* Serial flash driver            */
#endif
#ifndef   FS_USE_NAND2K_DRIVER
  #define FS_USE_NAND2K_DRIVER    0    /* Nand flash driver for large page devices */
#endif
#ifndef   FS_USE_SFNAND_DRIVER
  #define FS_USE_SFNAND_DRIVER    0    /* SPI Nand flash driver  */
#endif


#if (FS_USE_SMC_DRIVER     == 0) && (FS_USE_IDE_DRIVER == 0) \
    && (FS_USE_RAMDISK_DRIVER == 0) && (FS_USE_MMC_DRIVER == 0) \
    && (FS_USE_FLASH_DRIVER   == 0) && (FS_USE_WINDRIVE_DRIVER   == 0) \
    && (FS_USE_GENDEV_DRIVER  == 0) && (FS_USE_SFLASH_DRIVER    == 0) \
    && (FS_USE_NAND2K_DRIVER  == 0) && (FS_USE_MMC1_DRIVER == 0) \
    && (FS_USE_SFNAND_DRIVER  == 0)
#endif

#if (!defined(_WIN32) && (FS_USE_WINDRIVE_DRIVER))
  #error Windows Logical Drive driver needs Windows API
#endif
/*********************************************************************
*
*       File system defaults, obsolete
*
**********************************************************************
*
* The config defines in this section are obsolete.
*   They are mapped to the new defines (with more consistent names) in this section.
*   We recommend using the newer names in the config file.
*/
/* OBSOLTETE ! For compatibility */
#ifdef    FS_SEC_SIZE
  #define FS_MAX_SECTOR_SIZE          FS_SEC_SIZE
#endif
#ifdef    FS_RR_BLOCKNUM
  #ifndef FS_RAMDISK_NUM_SECTORS
    #define FS_RAMDISK_NUM_SECTORS       FS_RR_BLOCKNUM
  #endif
#endif


/*********************************************************************
*
*       File system defaults
*
**********************************************************************
*/

#ifndef   FS_MAX_SECTOR_SIZE
  #define FS_MAX_SECTOR_SIZE          512  /* standard value for FAT system. */
#endif

#ifndef   FS_MAXOPEN
  #define FS_MAXOPEN              4     /* Maximum number of file handles */
#endif

#ifndef   FS_POSIX_DIR_SUPPORT
  #define FS_POSIX_DIR_SUPPORT    1     /* POSIX 1003.1 like directory support */
#endif

#ifndef   FS_DIR_MAXOPEN                /* Maximum number of directory handles */
  #define FS_DIR_MAXOPEN          FS_POSIX_DIR_SUPPORT
#endif

#ifndef   FS_SUPPORT_FAT
  #define FS_SUPPORT_FAT         1   /* Support the FAT file system if enabled */
#endif

#ifndef   FS_SUPPORT_EFS
  #define FS_SUPPORT_EFS         0   /* Support the EFS file system if enabled */
#endif

#ifndef   FS_SUPPORT_MULTIPLE_FS
  #define FS_SUPPORT_MULTIPLE_FS ((FS_SUPPORT_EFS) && (FS_SUPPORT_FAT))
#endif

#ifndef   FS_SUPPORT_BURST           /* Burst support, allows read/write of multiple sectors at a time (speed opt.) */

  #define FS_SUPPORT_BURST           1
#endif

#ifndef   FS_SUPPORT_FREE_SECTOR
  #define FS_SUPPORT_FREE_SECTOR  FS_USE_SFLASH_DRIVER      /* Informs lower layer of unused sectors ... Makes sense only for drivers which use it */
#endif

#ifndef   FS_SUPPORT_CACHE
  #define FS_SUPPORT_CACHE            1
#endif

#ifndef   FS_MULTI_HANDLE_SAFE
  #define FS_MULTI_HANDLE_SAFE        0
#endif

#ifndef   FS_MAX_LEN_FULL_FILE_NAME
#if FS_MULTI_HANDLE_SAFE  
  #define FS_MAX_LEN_FULL_FILE_NAME (766+4)
#else
  #define FS_MAX_LEN_FULL_FILE_NAME (256+4)
#endif
#endif


#ifndef   FS_DRIVER_ALIGMENT
  #define FS_DRIVER_ALIGMENT          0
#endif
#ifndef   FS_DIRECTORY_DELIMITER
  #define FS_DIRECTORY_DELIMITER     '\\'
#endif
#ifndef   FS_CHECK_DEVICE_STATUS_ON_MOUNT
  #define FS_CHECK_DEVICE_STATUS_ON_MOUNT    0
#endif
#ifndef   FS_VERIFY_WRITE
  #define FS_VERIFY_WRITE              0    /* Verify every write sector operation (tests the driver and hardware) */
#endif
#ifndef   FS_SUPPORT_BUSY_LED
  #define FS_SUPPORT_BUSY_LED          0
#endif

#ifndef   FS_MAX_SUPPORT_STORAGE_SIZE_GB         /* This setting is for FAT only, not for exFAT */
  #if defined(SD_BOOT)||defined(FAT_BOOT)||defined(MBOOT_EX_FW)
    	#define FS_MAX_SUPPORT_STORAGE_SIZE_GB          (8)
  #else
  		#define FS_MAX_SUPPORT_STORAGE_SIZE_GB     		(128)
  #endif
#endif

#ifndef   FS_NEW_GET_FREE_SPACE
  #define FS_NEW_GET_FREE_SPACE           1
#endif

#ifndef   FS_SUPPORT_FAST_FORMAT
  #define FS_SUPPORT_FAST_FORMAT           1
#endif

#ifndef   FS_NEW_SEARCH_FREE_CLUSTER
  #define FS_NEW_SEARCH_FREE_CLUSTER           1
#endif

#ifndef   SD_PRELOAD_FATTABLE
  #define SD_PRELOAD_FATTABLE              0
#endif

/*********************************************************************
*
*       FAT File System Layer defines
*
*  For each media in your system using FAT, the file system reserves
*  memory to keep required information of the boot sector of that media.
*  FS_MAXDEV is the number of device drivers in your system used
*  with FAT, FS_FAT_MAXUNIT is the maximum number of logical units
*  supported by one of the activated drivers.
*/




#ifndef   FS_FAT_SUPPORT_FAT32            /* 0  disables FAT32 support */
  #define FS_FAT_SUPPORT_FAT32      1
#endif


#ifndef FS_FAT_SUPPORT_LFN                /* 1 enables long file name support */
  #define FS_FAT_SUPPORT_LFN        0
#endif

#ifndef   FS_FAT_SUPPORT_UTF8
  #define FS_FAT_SUPPORT_UTF8       0    /* Use UTF-8 encoding to support unicode characters */
#endif


#ifndef   FS_UNICODE_UPPERCASE_EXT
  #define FS_UNICODE_UPPERCASE_EXT  {0x0000, 0x0000}   /* allow to extend the static unicode lower to upper case table */
#endif

#ifndef   FS_FAT_FWRITE_UPDATE_DIR       /* 1:  FS_FWrite updates directory entry (safer, but slower) */
                                         /* 0:  Directory entry is updated by FS_FClose (faster) */
  #define FS_FAT_FWRITE_UPDATE_DIR  1
#endif

#ifndef   FS_MAINTAIN_FAT_COPY
  #define FS_MAINTAIN_FAT_COPY      0
#endif

#ifndef    FS_FAT_OPTIMIZE_SEQ_CLUSTERS
  #define  FS_FAT_OPTIMIZE_SEQ_CLUSTERS 0
#endif

#ifndef   FS_FAT_USE_FSINFO_SECTOR      /* Use and update FSInfo sector on FAT32 media. For FAT12/FAT116 there is no FSInfo sector */
  #define FS_FAT_USE_FSINFO_SECTOR  0
  #endif
#ifndef FS_FAT_OPTIMIZE_DELETE                  /* Accelerate delete of large files */
  #define FS_FAT_OPTIMIZE_DELETE 1
#endif
#ifndef FS_FAT_SPEEDUP_DELETE                   /* Speed up delete file performance */
  #define FS_FAT_SPEEDUP_DELETE 1
#endif


/*********************************************************************
*
*       EFS File System Layer defines
*
*/


#ifndef   FS_EFS_FWRITE_UPDATE_DIR        /* 1 FS_FWrite modifies directory (default), 0 directory is modified by FS_FClose */
  #define FS_EFS_FWRITE_UPDATE_DIR  0
#endif

#ifndef   FS_EFS_CASE_SENSITIVE
  #define FS_EFS_CASE_SENSITIVE     0    /* Should the file/directory names be case sensitively compared */
#endif

#ifndef   FS_EFS_OPTIMIZE
  #define FS_EFS_OPTIMIZE           0
#endif


#ifndef   FS_SUPPORT_DISKINFO
  #define FS_SUPPORT_DISKINFO       (FS_FAT_DISKINFO) || (FS_EFS_SUPPORT_DISKINFO)
#endif
#if FS_SUPPORT_EFS
  #ifdef FS_SUPPORT_BURST
     #undef   FS_SUPPORT_BURST
     #define  FS_SUPPORT_BURST 0
  #endif
#endif
/*********************************************************************
*
*       File system support sector access
*/

#ifndef    FS_SUPPORT_SEC_ACCESS
  #define  FS_SUPPORT_SEC_ACCESS 0
#endif


/*********************************************************************
*
*       Directory name length
*/
#ifndef FS_DIRNAME_MAX /* Max directory entry name size for FS_ReadDir() operation */
  #if   (FS_SUPPORT_FAT) && (! FS_SUPPORT_EFS)  /* FAT support only */
    #if FS_FAT_SUPPORT_LFN
      #define FS_DIRNAME_MAX            150  /* Max length of a FAT LFN name entry is 150 characters */
    #else
      #define FS_DIRNAME_MAX             13  /* Max length of a FAT name entry is 13 characters */
    #endif
  #elif (! FS_SUPPORT_FAT) && (FS_SUPPORT_EFS)
    #define FS_DIRNAME_MAX              150  /* Max length of a EFS name entry is 150 characters */
  #else
    #define FS_DIRNAME_MAX              255  /* Maximum size of a directory name */
  #endif
#endif


/*********************************************************************
*
*       File handles and file objects
*/
#ifndef   FS_NUM_FILE_HANDLES
  #define FS_NUM_FILE_HANDLES              FS_MAXOPEN + (FS_SUPPORT_EFS * 2)    /* Maximum number of file handles */
#endif
#ifndef   FS_NUM_FILE_OBJECTS
  #define FS_NUM_FILE_OBJECTS              FS_NUM_FILE_HANDLES          /* Maximum number of file objects */
#endif


/*********************************************************************
*
*       CLib
*/
#ifndef   FS_NO_CLIB
  #define FS_NO_CLIB  0
#endif

/*********************************************************************
*
*       OS Layer
*
**********************************************************************
*/

#ifndef   FS_OS_EMBOS
  #define FS_OS_EMBOS             0    /* 1 = use embOS */
#endif
#ifndef   FS_OS_UCOS_II
  #define FS_OS_UCOS_II           0    /* 1 = use uC/OS-II */
#endif
#ifndef   FS_OS_RTK
  #define FS_OS_RTK           0        /* 1 = use RTK OS */
#endif
#ifndef   FS_OS_WINDOWS
  #define FS_OS_WINDOWS           0    /* 1 = use WINDOWS */
#endif
#if ( (FS_OS_WINDOWS==1) && ( (FS_OS_EMBOS==1) || (FS_OS_UCOS_II==1) || (FS_OS_RTK==1) ) )
  #error You may only select one OS at a time.
#endif

#ifndef   FS_OS
  #define FS_OS (FS_OS_EMBOS | FS_OS_UCOS_II | FS_OS_WINDOWS | FS_OS_RTK)
#endif

#ifndef   FS_OS_LOCK_PER_FILE
  #define FS_OS_LOCK_PER_FILE 0        /* 0 = means a single lock for all files, 1 means one lock per file */
#endif

/*********************************************************************
*
*       Device driver defaults
*
**********************************************************************
*/



/*********************************************************************
*
*       RAMDISK defines
*
*/
#if FS_USE_RAMDISK_DRIVER
  #ifndef   FS_RAMDISK_MAXUNIT
    #define FS_RAMDISK_MAXUNIT 1
  #endif
#else
  #ifndef   FS_RAMDISK_MAXUNIT
    #define FS_RAMDISK_MAXUNIT 0
  #endif
#endif
#ifndef   FS_RAMDISK_SECTOR_SIZE
  #define FS_RAMDISK_SECTOR_SIZE   512
#endif

/*********************************************************************
*
*       SMC_DRIVER defines
*
*/
#if FS_USE_SMC_DRIVER
  #ifndef   FS_SMC_MAXUNIT
    #define FS_SMC_MAXUNIT                    7//1
  #endif
#else
  #ifdef   FS_SMC_MAXUNIT
    #undef FS_SMC_MAXUNIT
  #endif
  #define FS_SMC_MAXUNIT                      0
#endif /* FS_USE_SMC_DRIVER */
  #ifndef   FS_SMC_HW_SUPPORT_BSYLINE_CHECK
    #define FS_SMC_HW_SUPPORT_BSYLINE_CHECK   1
  #endif
  #ifndef   FS_SMC_SECTOR_SIZE
    #define FS_SMC_SECTOR_SIZE                512
  #endif
#if FS_USE_NAND2K_DRIVER
  #ifndef   FS_NAND2K_MAXUNIT
    #define FS_NAND2K_MAXUNIT                 1
  #endif
  #if  FS_MAX_SECTOR_SIZE < FS_NAND2K_SECTOR_SIZE
    #undef  FS_MAX_SECTOR_SIZE
    #define FS_MAX_SECTOR_SIZE                       FS_NAND2K_SECTOR_SIZE
  #endif

#else
  #ifdef    FS_NAND2K_MAXUNIT
    #undef  FS_NAND2K_MAXUNIT
  #endif
  #define FS_NAND2K_MAXUNIT                   0

#endif
#ifndef   FS_NAND2K_SECTOR_SIZE
  #define FS_NAND2K_SECTOR_SIZE             2048
  #endif

#ifndef   FS_NAND2K_NUM_SECTORS
  #define FS_NAND2K_NUM_SECTORS             0
#endif

/*********************************************************************
*
*       MMC_DRIVER defines
*
*/
#if FS_USE_MMC_DRIVER
  #ifndef   FS_MMC_MAXUNIT
    #define FS_MMC_MAXUNIT          7//2
  #endif
#else
  #ifdef   FS_MMC_MAXUNIT
    #undef FS_MMC_MAXUNIT
  #endif
  #define FS_MMC_MAXUNIT            0
#endif /* FS_USE_MMC_DRIVER */

#if FS_USE_MMC1_DRIVER
  #ifndef   FS_MMC1_MAXUNIT
    #define FS_MMC1_MAXUNIT         1
  #endif
#else
  #ifdef   FS_MMC1_MAXUNIT
    #undef FS_MMC1_MAXUNIT
  #endif
  #define FS_MMC1_MAXUNIT           0
#endif /* FS_USE_MMC1_DRIVER */

#ifndef   FS_MMC_USE_SPI_MODE
  #define FS_MMC_USE_SPI_MODE       1
#endif

#ifndef   FS_MMC_SUPPORT_4BIT_MODE
  #define FS_MMC_SUPPORT_4BIT_MODE  0
#endif

/*********************************************************************
*
*       IDE_DRIVER defines
*
*/
#if FS_USE_IDE_DRIVER
  #ifndef   FS_IDE_MAXUNIT
    #define FS_IDE_MAXUNIT           1
  #endif
#else
  #ifdef   FS_IDE_MAXUNIT
    #undef FS_IDE_MAXUNIT
  #endif
  #define FS_IDE_MAXUNIT             0
#endif /* FS_USE_IDE_DRIVER */

/*********************************************************************
*
*       FLASH_DRIVER defines
*/

#if FS_USE_FLASH_DRIVER
  #ifndef FS_FLASH_MAXUNIT
    #define FS_FLASH_MAXUNIT             1
  #endif
  #ifndef FS_FLASHWEARLEVELING
    #define FS_FLASHWEARLEVELING         1
  #endif
#else
  #ifdef FS_FLASH_MAXUNIT
    #undef FS_FLASH_MAXUNIT
  #endif
  #define FS_FLASH_MAXUNIT               0
#endif
#ifndef   FS_FLASH_SECTOR_SIZE
  #define FS_FLASH_SECTOR_SIZE         512
#endif



/*********************************************************************
*
*       SERIALFLASH_DRIVER defines
*/

#if FS_USE_SFLASH_DRIVER
  #ifndef FS_SFLASH_MAXUNIT
    #define FS_SFLASH_MAXUNIT       4//1
  #endif
  #ifndef FS_SFLASH_WEARLEVELING
    #define FS_SFLASH_WEARLEVELING  0
  #endif
#else
  #ifdef FS_SFLASH_MAXUNIT
    #undef FS_SFLASH_MAXUNIT
  #endif
  #define FS_SFLASH_MAXUNIT         0
#endif

/*********************************************************************
*
*       SERIAL NAND FLASH_DRIVER defines <SPI NAND FLASH><SFNAND>
*/
#if FS_USE_SFNAND_DRIVER
    #ifndef FS_SFNAND_MAXUNIT
        #define FS_SFNAND_MAXUNIT       1
    #endif

	#ifndef   FS_SFNAND_SECTOR_SIZE
        #define FS_SFNAND_SECTOR_SIZE				512
    #endif
#else
    #ifdef FS_SFNAND_MAXUNIT
        #undef FS_SFNAND_MAXUNIT
    #endif
    #define FS_SFNAND_MAXUNIT           0
#endif // #if FS_USE_SFNAND_DRIVER

/*********************************************************************
*
*       WINDRIVE_DRIVER defines
*
* This driver does allow to use any Windows logical driver on a
*  Windows NT system with the file system. Please be aware, that Win9X
*  is not supported, because it cannot access logical drives with
*  "CreateFile".
*/

#if FS_USE_WINDRIVE_DRIVER
  #ifndef FS_WD_MAXDEV
    #define FS_WD_MAXDEV              2        /* number of windows drives */
  #endif
  #ifndef FS_WD_DEV0NAME
    #define FS_WD_DEV0NAME   "\\\\.\\A:"       /* Windows drive name for "windrv:0:" */
  #endif
  #ifndef FS_WD_DEV1NAME
    #define FS_WD_DEV1NAME   "\\\\.\\B:"       /* Windows drive name for "windrv:1:" */
  #endif
#else
  #ifdef FS_WD_MAXDEV
    #undef FS_WD_MAXDEV
  #endif
  #define FS_WD_MAXDEV                0

#endif  /* FS_USE_WINDRIVE_DRIVER */


/* In order to avoid warnings for undefined parameters */
#ifndef FS_USE_PARA
  #if defined (__BORLANDC__) || defined(NC30) || defined(NC308)
    #define FS_USE_PARA(para)
  #else
    #define FS_USE_PARA(para) para=para;
  #endif
#endif


/*********************************************************************
*




*       Number of
*/
#ifndef   FS_NUM_VOLUMES
#define FS_NUM_VOLUMES (FS_USE_SMC_DRIVER            * FS_SMC_MAXUNIT) \
                                    + (FS_USE_NAND2K_DRIVER         * FS_NAND2K_MAXUNIT) \
                                    + (FS_USE_IDE_DRIVER            * FS_IDE_MAXUNIT) \
                                    + (FS_USE_MMC_DRIVER            * FS_MMC_MAXUNIT) \
                                    + (FS_USE_MMC1_DRIVER           * FS_MMC1_MAXUNIT) \
                                    + (FS_USE_FLASH_DRIVER          * FS_FLASH_MAXUNIT) \
                                    + (FS_USE_SFLASH_DRIVER         * FS_SFLASH_MAXUNIT) \
                                    + (FS_USE_WINDRIVE_DRIVER       * FS_WD_MAXDEV) \
                                    + (FS_USE_GENDEV_DRIVER) \
                                    + (FS_USE_SFNAND_DRIVER         * FS_SFNAND_MAXUNIT) \
                                    + (FS_USE_RAMDISK_DRIVER        * FS_RAMDISK_MAXUNIT) /* Note: Can be reduced using the individual defines */
#endif

#if FS_NUM_VOLUMES == 0
  #undef  FS_NUM_VOLUMES
  #define FS_NUM_VOLUMES 4
#endif

#ifndef   FS_NUM_DEVICES
  #define FS_NUM_DEVICES           (FS_USE_SMC_DRIVER) \
                                    + (FS_USE_NAND2K_DRIVER) \
                                    + (FS_USE_IDE_DRIVER) \
                                    + (FS_USE_MMC_DRIVER) \
                                    + (FS_USE_MMC1_DRIVER) \
                                    + (FS_USE_FLASH_DRIVER) \
                                    + (FS_USE_SFNAND_DRIVER) \
                                    + (FS_USE_WINDRIVE_DRIVER) \
                                    + (FS_USE_GENDEV_DRIVER) \
                                    + (FS_USE_SFLASH_DRIVER ? 1 : 0) \
                                    + (FS_USE_RAMDISK_DRIVER)   /* Note: Can be reduced using the individual defines */
#endif

#if FS_NUM_DEVICES == 0
  #undef  FS_NUM_DEVICES
  #define FS_NUM_DEVICES 4
#endif


#ifndef   FS_NUM_MEMBLOCKS
  #if (FS_OS_LOCK_PER_FILE == 0) && (FS_SUPPORT_EFS == 0)
    #define FS_NUM_MEMBLOCKS   2      /* FAT file system and no OS or OS with coarse lock mechanism. */
  #elif (FS_OS_LOCK_PER_FILE == 0) && (FS_SUPPORT_EFS == 1)
    #define FS_NUM_MEMBLOCKS   3      /* EFS file system and no OS or OS with coarse lock mechanism. */
  #elif (FS_OS_LOCK_PER_FILE == 1) && (FS_SUPPORT_EFS == 0)
    #if (FS_POSIX_DIR_SUPPORT == 0)   /* FAT file system and OS support with fine lock mechanism... */
      #define FS_NUM_MEMBLOCKS   (FS_MAXOPEN * 2)   /* With directory support disabled */
    #else
      #define FS_NUM_MEMBLOCKS   ((FS_MAXOPEN + FS_DIR_MAXOPEN)* 2)   /* With directory support enabled */
#endif
  #elif (FS_OS_LOCK_PER_FILE == 1) && (FS_SUPPORT_EFS == 1)
    #if (FS_POSIX_DIR_SUPPORT == 0)   /* EFS file system and OS support with fine lock mechanism... */
      #define FS_NUM_MEMBLOCKS   (FS_MAXOPEN * 2) + 1   /* With directory support disabled */
    #else
      #define FS_NUM_MEMBLOCKS   ((FS_MAXOPEN + FS_DIR_MAXOPEN)* 2) + 2   /* With directory support enabled */
    #endif
  #endif
#endif
#ifndef   FS_NUM_SBLOCKS
  #define FS_NUM_SBLOCKS  FS_NUM_MEMBLOCKS
#endif

/*********************************************************************
*
*       Check configuration
*
*/
#if FS_MAX_SECTOR_SIZE < FS_FLASH_SECTOR_SIZE
  #error  "FS_MAX_SECTOR_SIZE < FS_FLASH_SECTOR_SIZE, this will cause problems when reading/writing from/to device."
#endif

#if FS_MAX_SECTOR_SIZE < FS_RAMDISK_SECTOR_SIZE
  #error  "FS_MAX_SECTOR_SIZE < FS_RAMDISK_SECTOR_SIZE, this will cause problems when reading/writing from/to device."
#endif

#if FS_MAX_SECTOR_SIZE < FS_SMC_SECTOR_SIZE
  #error  "FS_MAX_SECTOR_SIZE < FS_SMC_SECTOR_SIZE, this will cause problems when reading/writing from/to device."
#endif
/********************************************************************/

#endif  /* Avoid multiple inclusion */

/****** End of file *************************************************/

