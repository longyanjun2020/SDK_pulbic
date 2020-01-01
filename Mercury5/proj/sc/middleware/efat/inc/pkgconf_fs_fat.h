#ifndef ONCE_PKGCONF_FS_FAT_H
#define ONCE_PKGCONF_FS_FAT_H
///////////////////////////////////////////////////////////////////////////////////////////////////
/// @file   pkgconf_fs_fat.h
/// @author MStar Semiconductor Inc.
/// @brief  video application header file
///////////////////////////////////////////////////////////////////////////////////////////////////


#define NUM_FS_FAT_NODE_HASH_TABLE_SIZE 32
#define NUM_FS_FAT_NODE_HASH_TABLE_SIZE_32
#define NUM_FS_FAT_NODE_POOL_SIZE 22
#define NUM_FS_FAT_NODE_POOL_SIZE_22
//#define CFG_FS_USED_SDRAM_BUFFER 1
#define NUM_FS_FAT_BLOCK_CACHE_MEMSIZE 8192
#define NUM_FS_FAT_BLOCK_CACHE_MEMSIZE_8192
//#define CFG_FS_FAT_MULTI_CACHEBUFFER 1
#define NUM_FS_FAT_TABLE_BLOCK_CACHE_MEMSIZE 8192
#define NUM_FS_FAT_TABLE_BLOCK_CACHE_MEMSIZE_8192
#define NUM_FS_FAT_DIR_BLOCK_CACHE_MEMSIZE 8192
#define NUM_FS_FAT_DIR_BLOCK_CACHE_MEMSIZE_8192
#define CFG_FS_FAT_USE_ATTRIBUTES 1
#define EFAT_FS_FAT_USE_CLUSTER_CHAIN 1
#define EFAT_DYNAMIC_MEMORY_MODE_CC 1
#define NUM_FS_FAT_FCLUSTER_POOL_SIZE 256
#define NUM_FS_FAT_FCLUSTER_POOL_SIZE_256
#define CFG_FS_FAT_LONG_FILE_NAMES 1
#define NUM_FS_FAT_LONG_FILE_NAME_MAX 264
#define NUM_FS_FAT_LONG_FILE_NAME_MAX_264
//#define FS_FAT_MERGE_CONTINUOUS_CLUSTERS 1
#define CFG_FS_FAST_GET_CAPACITY 1
#define CFG_FS_DIRECTREAD_GET_CAPACITY 1
#define PKG_FS_FAT_OPTIONS 1
#define USE_GENERAL_FCC 1
#define CFG_FS_WRITE_WITH_SYNC 1
//#define CFG_FS_DATA_CACHE_DISABLE 1 // <-- defined, always on

//for RTK
//#define CONDITION_VAR
//#define USE_RTK_CV 1


#endif
