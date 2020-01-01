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
File        : fs_conf.h
Purpose     : File system configuration
---------------------------END-OF-HEADER------------------------------
*/

#ifndef _FS_CONF_H_
#define _FS_CONF_H_

#define FS_DEBUG_LEVEL              1        /* 0: Smallest code, 5: Full debug. See chapter 9 "Debugging". */
#ifdef WIN32
  #define FS_OS_WINDOWS               1
  #define __align
#endif

/*********************************************************************
*
*       Specify which driver do you want
*/
// If want to use ram disk to test, define to 1 and the others driver change to
// 0. Then you don't need to chang your file path description.
// If you want to change ram disk address, you can search "FS_RAMDISK_ADDR"
// and change to where(unuse memory address), and ram disk size is 16KB now.
// If you want to extend, you can search "FS_RR_BLOCKNUM" to change.
#define FS_USE_RAMDISK_DRIVER       0       /* 1: Use RAM Disk */
#define FS_RAMDISK_NUM_SECTORS        7       /* Define number of 512 byte sectors */

#define FS_USE_SFLASH_DRIVER          1 /* 1 = use Serial flash device       */
#define FS_USE_FLASH_DRIVER           0 /* 1 = use NOR flash device       */
#define FS_USE_GENDEV_DRIVER          0 /* 1 = use generic dummy device   */
#define FS_USE_IDE_DRIVER             0 /* 1 = use IDE/CF devices         */
#define FS_USE_MMC_DRIVER             1 /* 1 = use MMC/SD devices         */
#define FS_USE_SMC_DRIVER             1 /* 1 = use SMC/NAND flash devices */
#define FS_USE_MMC1_DRIVER            1 /* 1 = use MMC1/SD1 devices         */
#define FS_USE_SFNAND_DRIVER          0 /* 1 = use SPI Nand flash devices */

/*********************************************************************
*
*             RAMDISK_DRIVER defines
*/

#if FS_USE_RAMDISK_DRIVER
  /*
   * Define size of your RAM disk here.
   * You specify the number of sectors (512 bytes) here.
   */
  #define FS_RR_BLOCKNUM             32       /* 16KB RAM */
#endif




/*********************************************************************
*
*             MISC
*/

#define FS_IS_LITTLE_ENDIAN             1
#define FS_NO_CLIB                      1   // 1
#define FS_SUPPORT_VAR_SECTOR_SIZE      1
#define FS_SUPPORT_BURST                1
#define FS_SUPPORT_CACHE                1
#define FS_MULTI_CACHE                  1   // For 3 individual Cache area support  
#define FS_FAT_OPTIMIZE_SEQ_CLUSTERS    1
#define FS_FAT_FWRITE_UPDATE_DIR        1
#define FS_FAT_SUPPORT_LFN              1
#define FS_FAT_SUPPORT_UTF8             1
#define FS_OS_UCOS_II                   (0)
#define FS_OS_RTK                       (1)
#define FS_MAXOPEN 						24  // Maximum number of file handle
#define	FS_DIR_MAXOPEN					10	// Maximum number of dir handle
#define	FS_DIRNAME_MAX					256 // Maximun length file/directory name to retrive from dir entry
#define FS_OS_LOCK_PER_FILE 			1
#define FS_MMC_USE_SPI_MODE       		0
#define FS_USE_CHKDISK					0
#define FS_FAT_USE_FSINFO_SECTOR        1
#define FS_FAT_REPAIR_BPB_DAMAGE        0
#define FS_USE_MUTEXLOCK_DEV_SYS       (0)

//#if ( defined(UPDATER_FW)||defined(FAT_BOOT)||defined(MBOOT_SRAM_FW) )
#if defined (ALL_FW)

//#define   FS_NEWBUFFER					0 //0=disable
//#else
//#define   FS_NEWBUFFER					1 //1=enable
#define   MAX_CACHE_NUM    (12) 
#endif


#define FS_PROTECT_LEVEL                1
#define FS_UNDEFINED_VALUE              0xFFFFFFFF

#define FS_USE_FORMAT_USER_DATA_ALIGNMENT   1

#define SECTORS_PER_MB                  (1024*1024/512)
#define SECTORS_PER_GB                  (1024*SECTORS_PER_MB)

#if FS_USE_FORMAT_USER_DATA_ALIGNMENT
#define FS_FORMAT_ALIGN_FAT32_MINI_SIZE_IN_SECTOR    (2048*SECTORS_PER_MB)
#define FS_FORMAT_ALIGN_FAT16_MINI_SIZE_IN_SECTOR    (1024*SECTORS_PER_MB)
#endif //FS_USE_FORMAT_USER_DATA_ALIGNMENT


/*********************************************************************
*
*             EXFAT Support
*/

#define FS_FAT_SUPPORT_EXFAT			0
#define FS_FORMAT_MIN_EXFAT_NUM_SECTORS	 (32*SECTORS_PER_GB)  /* The volume size threshold for exFAT formating. */

#endif  /* Avoid multiple inclusion */


