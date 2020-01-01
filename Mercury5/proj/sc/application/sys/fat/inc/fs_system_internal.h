/****************************************************************************/
/*  File    : fs_system_internal.h                                               	*/
/*--------------------------------------------------------------------------*/
/*  Scope   : FAT12/16 file-system internal definitions  					*/
/*                                                                          */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

#ifndef __FS_SYSTEM_INTERNAL_H__
#define __FS_SYSTEM_INTERNAL_H__

/*_____ I N C L U D E S ____________________________________________________*/
#include "vm_types.ht" 
#include "fs_browse.h" 
#include "dev_storage.h" 
#include "cus_os.hc"

/*_____ M A C R O S ________________________________________________________*/

#define STREAMING         ((u8)2)

#define FREE_CLUSTER      ((u16)0x0000)  /* free cluster value in FAT    */
#define LAST_CLUSTER_MSK      ((u16)0xFFF8)  /* last file cluster in FAT     */
#define LAST_CLUSTER      ((u16)0xFFFF)  /* last file cluster in FAT     */
#define BAD_CLUSTER       ((u16)0xFFF7)  /* bad cluster value in FAT     */

#define FILE_NOT_EXIST    		((u8)0x00)      /* current file does not exist  */
#define FILE_DELETED      		((u8)0xE5)      /* current file is deleted      */

#define LFN_FIRST_ENTRY    		((u8)0x40)      /* The first LFN identification */
#define LFN_SEQ_MASK      		((u8)0x3F)      /* LFN sequence number mask     */

#define ODD_EVEN_MASK     		((u8)0x01)      /* the odd / even test mask     */

#define MAX_CLUSTERS12    		((u16)4084)    /* FAT12 if < FAT16 else */
/* Format Info */
#define ENTRY_SIZE          	((u8)32)        /* directory entry size         */
#define NB_ENTRIES_PER_SECTOR	((u8)16)    	/* nb entries per sector = SECTOR_SIZE/ENTRY_SIZE         */
#define NB_ROOT_ENTRY     		((u16)512)
#define NB_RESERVED       		((u8)1)         /* number of reserved sectors */
#define NB_FATS           		((u8)2)
#define HARD_DISK         		((u8)0xF8)      /* hard disk device */
#define FS_DRIVE_NUMBER  		((u8)0x81)
#define FS_EXT_SIGN      		((u8)0x29)

/* FAT definition */
/* For LFN name, the name will be build with MAX_LFN_ENTRIES entries        */
/* That means tha the max file name length is                               */
/* 12 + (MAX_LFN_ENTRIES - 1 ) * 13                                         */
/* Size in pdata zone is 256 bytes.                                         */
/* fs_buffer use 32 bytes in pdata                                          */
/* We need 15 bytes for scrolling display                                   */
/* Maximum size for LFN name is 256 - 32 - 15 = 209 bytes                   */
/* And so MAX_LFN_ENTRIES = (209 - 12) / 13 + 1 = 16                        */
/* And size of LFN string is                                                */
/* MAX_FILENAME_LEN = 12 + (MAX_LFN_ENTRIES - 1) * 13 + 15 + 1 + 1          */
/*                                                           |   |          */
/*                                  +1 because we start at 0 -   |          */
/*                                  +1 for '\0' character    -----          */

#define NB_MAX_DIR_LIST_SESSION   ((u32)2)       

#ifdef LARGE_LFN_255
#define ENTRIES_PER_FILE   ((u8)21)    

/* maximum number of LFN entries */
#define MAX_LFN_ENTRIES   ((u8)21)       
/* maximum number of LFN entries */
#else
#define ENTRIES_PER_FILE   ((u8)3)       

/* maximum number of LFN entries */
#define MAX_LFN_ENTRIES   ((u8)16)       
/* maximum number of LFN entries */
#endif

//#define MAX_DIRECTORY_FILE 		((u16)MAX_FILE_SUPPORTED)    /* maximum number of file in    */
#ifdef __MMTV_MMI__
#define MAX_DIRECTORY_FILE 		((u16) 125)    /* maximum number of file in    */
#else //__MMTV_MMI__
#define MAX_DIRECTORY_FILE 		((u16) 110)    /* maximum number of file in    */
#endif //__MMTV_MMI__
                                            /* a directory                  */
#define MAX_ROOT_ENTRIES 			((u16)512)    /* maximum number of entries in root */
#define MAX_ROOT_FILE 			((u16)MAX_ROOT_ENTRIES/ENTRIES_PER_FILE)    /* maximum number of file in root */


#define MAX_DIRECTORY_GAP_FILE ((u16)(65535))
/*#define MAX_DIRECTORY_GAP_FILE ((u8)(255))*/
                                            /* maximum delta between 2      */
                                            /* specified entries            */
                                            /* Can be replace 255 or 65535  */
                                            /* case of type used for        */
                                            /* fs_directory_chain          */

#define READ_WRITE_MASK		0x3
#define NO_MORE_CLUSTER		0xFFFFFFFF

#define CHANGEABLE_ATTRIBUTES_MASK		0x27	// mask to find which attribute of a directory can be changed

/*_____ M A C R O S ________________________________________________________*/

#define UPCASE(_c_) (((_c_>0x60)&&(_c_<0x7B)) ? (_c_-0x20) : _c_)
#define MIN(_x_,_y_) (((u32)_x_>(u32)_y_) ? _y_ : _x_)

#define FS_DATE(_year_,_month_,_day_) ((_year_<<25)|(_month_<<21)|(_day_<<16))
#define FS_TIME(_hour_,_minute_,_second_) ((_hour_<<11)|(_minute_<<5)|(_second_>>1))

#define FS_HOURS(_time) 	(u8)((_time&0x0000F800)>>11)
#define FS_MINUTES(_time) 	(u8)((_time&0x000007E0)>>5)
#define FS_SECONDS(_time) 	(u8)((_time&0x0000001F)<<1)

#define FS_DAY(_date) 		(u8)((_date&0x001F0000)>>16)
#define FS_MONTH(_date) 	(u8)((_date&0x01E00000)>>21)
#define FS_YEAR(_date) 	(u16)(((_date&0xFE000000)>>25)+1980)

#define DEV_LEVEL_FS_API LEVEL_12
#define DEV_LEVEL_FS_SYS LEVEL_13

typedef struct
{
	fs_sort_fct_t sort;
	fs_filter_fct_t filter;

	u16 fileId[MAX_DIRECTORY_FILE];
	u16 fileNbr;
	u16 lastPos;
	fs_volume_s *volume;
} fs_sort_filter_ctxt_t;

extern u8    *fs_buffer;	// general purpose buffer

extern fs_volume_s **volume_list;
extern u8 nb_volumes;


// dev_fs_sys.c functions
s32		fs_sys_find_free_file(fs_file_reference_s **open_files, u8 nb_files);
fs_volume_s* fs_sys_get_volume(u16 *name);
fs_volume_s* fs_sys_url_get_volume(u16 *url);

// dev_fs_name.c functions
s32 	fs_sys_scan_names(fs_directory_t *directory, u16 *cur_name, u16 *index);
s32 	fs_sys_find_file_name(fs_volume_s *volume, u16* file_name);
s32 	fs_sys_find_short_file_name(fs_directory_t *directory, s8* file_name);
u8 		fs_sys_lfn_checksum(s8 *name, s8* ext);
void 	fs_sys_truncate_LFN_name(u16 *long_name,u16 *trunc_name);
s32 	fs_sys_get_file_name(u16 *URL, u16 *file_name);
s32 	fs_sys_get_differing_url(u16 *url1, u16* url2, u16 *rest_path1);

// dev_fs_entries.c functions
s32 	fs_sys_dread (fs_volume_s *volume, u8 *buffer, u32 nb_data);
s32 	fs_sys_dwrite (fs_volume_s *volume, u8 *buffer, u32 nb_data);
s32 	fs_sys_add_file_in_chain(fs_volume_s *volume, fs_file_reference_s   *fs_cache);
void 	fs_sys_free_entries (fs_volume_s *volume, fs_file_reference_s *fs_cache, u8 file_marker);
void	fs_sys_update_entry (fs_volume_s *volume, fs_file_reference_s   *fs_cache);
void 	fs_sys_get_directory_chain (fs_volume_s *volume);
void	fs_sys_set_file_info (u8 entry_number, fs_file_reference_s   *fs_cache);
void 	fs_sys_new_file_info (fs_directory_t *directory, u16 *name, fs_file_reference_s   *fs_cache);
void 	fs_sys_set_lfn_info (u8 entry_number,u8 pos, fs_file_reference_s   *fs_cache);
void 	fs_sys_set_file_name (fs_directory_t *directory, u16 *name, fs_file_reference_s   *fs_cache, u16 *name_length);

// dev_fs_clusters.c functions
s32     fs_sys_get_clusters (fs_volume_s *volume, fs_cluster_chain_s *,fs_file_reference_s   *fs_cache);
s32 	fs_sys_find_free_cluster (fs_volume_s *volume, u16 *cluster);
s32 	fs_sys_allocate_cluster (fs_volume_s *volume, u16 old_cluster, u16 new_cluster);
s32 	fs_sys_free_clusters (fs_volume_s *volume, fs_file_reference_s   *fs_cache, bool except_first);
s32 	fs_sys_parse_clusters (fs_volume_s *volume, bool);

s32		fs_get_root_directory (void);
s32		fs_goto_parentdir (void);
s32		fs_goto_subdir (u32 file_ref);


s32 	fs_sys_updateFileId(fs_file_reference_s *fs_file_references, u16 nb_files, fs_sort_filter_ctxt_t *ctxt);

#endif  /* __FS_SYSTEM_INTERNAL_H__ */

