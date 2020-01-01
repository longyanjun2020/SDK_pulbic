/****************************************************************************/
/*  File    : fs_browse.h                                              	*/
/*--------------------------------------------------------------------------*/
/*  Scope   : file and directory manipulation functions	           			*/
/*                                                                          */
/*                                                                          */
/****************************************************************************/

#ifndef __FS_BROWSE_H__
#define __FS_BROWSE_H__

/*_____ I N C L U D E S ____________________________________________________*/

#include "vm_types.ht" 
#include "dev_storage.h"
#include "fs_error.h"
#include "mdl_vfs_fat.ho"

#define LARGE_LFN_255

// Use dynamic allocate file list instead of static array in ZI section.
// Step1. Caculate elements in current folder within fs_sys_get_directory_chain().
// Step2. Dynamic allocate pool buffer with sizeof(fs_file_reference_s)*elements
#define NOR_FS_OPT_MEM_DYNA
#ifdef NOR_FS_OPT_MEM_DYNA
// Trimming Long_File_Name[] array size, since we support up to 2 entries for LFN file
#ifndef LARGE_LFN_255
#define NOR_FS_OPT_MEM_LITE
#endif
// Cache buffer read from fs_dread to improve performance issue.
#define NOR_FS_OPT_DREAD_CACHE
#endif

#define MAX_FILE_NAME_CHAR 		MAX_CHAR_LFN 	// (13 unicodes per LFN entry) * 2 including the '\0' char
#ifdef LARGE_LFN_255
#define UCHAR_PER_ENTRY		(13)			// (13 unicodes per LFN entry)
//#define MAX_ENTRY_NAME_CHAR 	(UCHAR_PER_ENTRY * (ENTRIES_PER_FILE -1))		// including the '\0' char
#define MAX_ENTRY_NAME_CHAR 	(255)		// including the '\0' char
#else
#define MAX_ENTRY_NAME_CHAR 	(13 * 2)		// (13 unicodes per LFN entry) * 2 including the '\0' char
#endif

/* Patch for data abort issue for Directory create/destroy boudnary test */
#define MAX_PATH_SIZE		(MAX_PATH_LEN)
//#define MAX_PATH_SIZE		200 	// max size of the "current_path" field of a volume

#define MAX_FILE_FRAGMENT_NUMBER ((u8)128) /* maximum number of authorized */
                                            /* fragment for a file          */

#define ATTR_READ_ONLY    ((u8)0x01)      /* Read Only Attribute */
#define ATTR_HIDDEN       ((u8)0x02)      /* Hidden File Attribute */
#define ATTR_SYSTEM       ((u8)0x04)      /* System File Attribute */
#define ATTR_DIRECTORY    ((u8)0x10)      /* Directory Attribute */
#define ATTR_ARCHIVE      ((u8)0x20)      /* Archive Attribute */
#define ATTR_LFN_ENTRY    ((u8)0x0F)      /* LFN entry attribute */


/*******************************************************************************
* MACROS
*******************************************************************************/
#define FS_SET_ATTRIBUTE_HIDDEN(_u8_attributes)			(_u8_attributes |= ATTR_HIDDEN)
#define FS_ATTRIBUTE_IS_HIDDEN(_u8_attributes)			((_u8_attributes & ATTR_HIDDEN) ? TRUE : FALSE)
#define FS_ATTRIBUTE_SET_READ_ONLY(_u8_attributes)		(_u8_attributes |= ATTR_READ_ONLY)
#define FS_ATTRIBUTE_IS_READ_ONLY(_u8_attributes)		((_u8_attributes & ATTR_READ_ONLY) ? TRUE : FALSE)
#define FS_SET_ATTRIBUTE_ARCHIVE(_u8_attributes)		(_u8_attributes |= ATTR_ARCHIVE)
#define FS_ATTRIBUTE_IS_ARCHIVE(_u8_attributes)			((_u8_attributes & ATTR_ARCHIVE) ? TRUE : FALSE)
#define FS_ATTRIBUTE_SET_SYSTEM(_u8_attributes)			(_u8_attributes |= ATTR_SYSTEM)
#define FS_ATTRIBUTE_IS_SYSTEM(_u8_attributes)			((_u8_attributes & ATTR_SYSTEM) ? TRUE : FALSE)
#define FS_IS_ATTRIBUTE_DIRECTORY(_u8_attributes)		((_u8_attributes & ATTR_DIRECTORY) ? TRUE : FALSE)

/*******************************************************************************
* PURPOSE: 
* FAT fat cache system
*******************************************************************************/
#ifdef NOR_FS_OPT_MEM_LITE
typedef struct FS_FILE_INFO
{
	u16   Long_File_Name[26+8];     /* unicode string           */
//	u16   Long_File_Name[MAX_PATH_LEN / 2];     /* unicode string           */
	s8    File_Name[12];
	s8	  File_Extension[MAX_EXT_NAME_LEN + 1];
	u32   Creation_Date;                        /* time & date lastmodified */
	u32   Last_Write_Date;                      /* time & date lastmodified */
	u32   Size;                                 /* File size in bytes       */
	u8    Attributes;                           /* Attributes bits          */
	u8    format83;
} fs_file_info_s;
#else
typedef VFS_File_Info_t fs_file_info_s;
#endif

typedef struct {
  	u16 	cluster[MAX_FILE_FRAGMENT_NUMBER]; /* starting cluster of fragment */
  	u8   	number[MAX_FILE_FRAGMENT_NUMBER];  /* number of subsequent clusters in fragment */
	u8 		nb_fragments;
} fs_cluster_chain_s;

struct FS_VOLUME_S;

typedef struct {
	u16  	start_cluster;                    /* Starting cluster number        */
	u16  	parent_start_cluster;             /* Parent starting cluster number        */

	u32 	byte_counter; 						/* byte counter, mainly use for the eof check */
	u16 	sector_counter; 					/* sector counter, in a cluster */
    u32 	first_entry_sector;		/* absolute first entry sector  */
    u32 	last_entry_sector;		/* absolute last entry sector */
    u16 	first_entry;		/* number of the first entry of this file in the entry_sector */
    u16 	last_entry;			/* number of the last entry of this file in the entry_sector */
              
	u8    	fragment_index;      /* the number of the fragment of the file, in fact */
                                            /* the index of the table in the cluster chain */
	u8    	fragment_cluster;    /* the offset of the cluster from the first cluster */ 
                                            /* of the fragment */

	u32		open_mode;
	u8 		nb_entries;			// number of entries in the directory chain
	fs_cluster_chain_s *fragments;       /* cluster chain for the current file */
	struct FS_VOLUME_S *volume;
	fs_file_info_s 	file_info;
} fs_file_reference_s;
  
typedef struct {
	u16  last_file;                /* number of file stored in the directory */
	u32  directory_base;           /* starting sector for directory */
	u32  current_sector;           /* current sector where the current */
	                                            /* file/dir info (cache.info) is situated */
	u16  current_byte_counter;     /* the byte counter offset in the current */
	                                            /* sector where is the current file/dir entry */
	bool     dir_is_root;          /* TRUE: point the root directory  */
	/* directory cluster chain management */
	u8				fragment_index;
	u16				cluster_in_fragment;
	fs_cluster_chain_s fragments;   /* cluster chain for the current directory */
	u16		current_path[MAX_PATH_SIZE/2]; // current path or this directory (UCS2)
	fs_file_reference_s   *fs_file_references;      /* list of the file in the directory */
} fs_directory_t;

typedef struct FS_VOLUME_S {
	u16     name[VFS_MAX_VOL_NAME_LEN + 1];
	u32  	fats_addr;         		/* address of the first byte of FAT */
	u32  	root_dir_addr;         	/* address of the first byte of root dir */
	u32  	data_addr;         		/* address of the first byte of data */
	u32 	nb_sectors;				/* total number of sectors of the volume */
	u32 	nb_hidden_sectors;		/* number of sectors between the beginning of the unit and the PBR */
	u16    	cluster_mask;     		/* mask for end of cluster test */
	u16    	sector_mask;     		/* mask for cluster numbers in FAT */
	u16    	sector_shift;     		/* shift for cluster numbers in FAT */
	u16   	nb_sectors_per_FAT;		/* number of sectors occupied by one copy of the FAT */
	u8    	nb_sectors_per_cluster;	/* cluster size (sector count) */
	bool  	is_fat16;         		/* TRUE: FAT16 - FALSE: FAT12 */
	Storage_Unit_t *storage; 		// pointer on the physical storage unit that contains this volume
	fs_directory_t *cur_dir;			// pointer on the current directory
	u8		partition_index; 		// index of the partition in the storage unit (0 -> 3)
	bool	mounted; /* 2007.07.04 David Chang */
} fs_volume_s;

typedef struct {
	u16  u16_index; 
	u16  u16_nb; 
} fs_dir_context_s;

typedef struct{	
	u16 year;  // absolute year(Gregorian calendar)	
	u8 month; // 1 for January, 2 for February, etc?
	u8 day; // day in the month	
	u8 hour; // 0hour to 23hours	
	u8 minutes; // 0 to 59	
	u8 seconds; // 0 to 59
} fs_clock_s;

typedef s32 (*fs_filter_fct_t)(const fs_file_info_s*); // this function should return TRUE if the parameter is to be in file list

typedef struct{	
	u8 nb_filter_strings;
	u8 **filter_strings; // array of UCS2 strings containing filters ("*.jpg" for example)	
	fs_filter_fct_t filter; // callback to be called to filter one file
} fs_filter_s;

typedef enum {	
	FS_SORT_NAME,	
	FS_SORT_DATE,	
	FS_SORT_TYPE
} fs_sort_type_e;

typedef s32 (*fs_sort_fct_t)(const fs_file_info_s*, const fs_file_info_s*); // this function should return TRUE if the first parameter is the first in sorted list

typedef struct{
	fs_sort_type_e sort_type; // type of sorting (by name, by date,?	
	fs_sort_fct_t sort; // callback to be called to sort 2 files
} fs_sort_s;



/******************************************************************************
* PURPOSE : 
* fs functions
******************************************************************************/

s32 fs_update_volumes(void);
s32 fs_list_volumes (u8* nb_volumes, fs_volume_s*** list);
s32 fs_get_free_space (void);
s32 fs_get_total_space (void);
s32 fs_set_volume_name (u16* name);

s32 fs_remove (u16 *url);
s32 fs_move (u16 *old_url, u16 *new_url);
s32 fs_stat (u16 *url, fs_file_info_s *info);
s32 fs_chmod (u16 *url, u8 new_attributes);

s32 fs_url_get_volume_name (u16 *url, u16 *volume_name);
s32 fs_url_get_file_name (u16 *url, u16 *file_name);
s32 fs_url_get_parent (u16 *url, u16 *path);

/* @ 2007.07.12 David Chang */
s32 fs_change_volume(fs_volume_s* volume_ptr);
s32 fs_get_file_size (u32 file_ref);
//s32 fs_get_file_info(u32 file_num, File_Info_t* file_info_ptr);
//s32 fs_get_file_detail(u32 file_num, File_Info_t* file_info_ptr);
//s32 fs_get_open_file_info(u8 file_index, File_Info_t* file_info_ptr);
/* @ David Chang */
#endif  /* __FS_BROWSE_H__ */
