#ifndef __NEMOMP_FILES_H__
#define __NEMOMP_FILES_H__

#include "java_head.h"
#include "Ven_file.h"
#include "ven_os.h"

/*========================================================================
 * The following are about file operations.
 *=======================================================================*/

#define O_RDONLY	0x0000
#define O_WRONLY	0x0001
#define O_RDWR	0x0002
#define O_APPEND       0x0008

#define O_CREAT	0x0100
#define O_TRUNC	0x0200
#define O_BINARY	0x8000

#ifndef SEEK_SET
#  define SEEK_SET        0       /* Seek from beginning of file.  */
#  define SEEK_CUR        1       /* Seek from current position.  */
#  define SEEK_END        2       /* Set file pointer to EOF plus "offset" */
#endif

#define PLATFORM_FS_NO_ERROR    0
#define PLATFORM_FS_READ        1
#define PLATFORM_FS_DIR         2

#define PLATFORM_FS_DISK_FULL	-10

///#define JAVA_HOME_ONLY_ONE_DIR // 20090803: Added

extern nm_char nemomp_dir_path[];
extern nm_char *work_dir_path;
extern nm_char *work_sys_dir_path;
extern char nemomp_preinstall_dir_path[];

extern char nemomp_file_get_path_separator(void); // 20081208: Changed
extern void nemomp_file_initialize(void);
extern void nemomp_file_finalize(void);
extern int nemomp_javafile_open(const char *filename, int flags);
extern int nemomp_file_open(const nm_wchar *fullPath, int flags); // 20081209: Changed
extern int nemomp_file_close(int handle);
extern int nemomp_javafile_isexist(char *filename); // 20081209: Changed

extern int nemomp_file_attributes(const char *filename);
extern int nemomp_javafile_delete(const char *filename);
extern int nemomp_file_delete(const nm_wchar *fullPath); // 20081209: Changed

extern int nemomp_file_write(int handle, const void *buf, int count);
extern int nemomp_file_read(int handle, void *buf, int count);
extern int nemomp_file_lseek(int handle, int offset, int whence);
extern int nemomp_file_getsize(int handle, unsigned int* sz_ptr);
extern int nemomp_javafile_rename(const char *oldfilename, const char *newfilename);
extern int nemomp_file_rename(const nm_wchar* srcFullPath, const nm_wchar* dstFullPath); // 20081209: Changed
extern int nemomp_file_flush(int handle);

extern char* nemomp_file_findfirst(char* dirPath, char *prePartialName); // 20090803: Changed
extern char* nemomp_file_findnext(void); // 20090803: Changed

extern int nemomp_file_create_deep_dir(nm_wchar *fullfilename);

extern char nemomp_file_get_dir_separator(void);
extern int nemomp_file_getc(int handle);
int nemomp_jam_remove_remain(char *string);
//int nemomp_jam_get_sd_free_size(unsigned int * totalSize, unsigned int * freeSize);
 int nemomp_jam_get_sd_free_size(char *path, unsigned int* totalSize, unsigned int* freeSize);

#define nemomp_file_tell(handle)    nemomp_file_lseek((handle), 0, SEEK_CUR)

extern nm_bool nemomp_is_java_system_file(const char* filename); // 20090803: Added
extern nm_char* nemomp_get_rms_dir_path(void); // 20090803: Added



//09.12.3
#ifdef __NAND_MMI__
#define NEMOMP_SYS_TOP_NAND //move  to nemomp_file.h
#endif

extern char nemomp_nand_dir_path[];
extern char nemomp_sd_dir_path[];
extern u16 wnemomp_dir_path[];
extern char nemomp_nand_dir_path[];
extern char nemomp_sd_dir_path[];
extern u16 wnemomp_sys_top_dir[];

#define nemomp_file_tell(handle)    nemomp_file_lseek((handle), 0, SEEK_CUR)

//=======================
#ifdef __JAVA_JSR75_FC__
//for JSR75
#define PLATFORM_FS_READONLY 4
#define PLATFORM_FS_WRITEONLY 8
#define PLATFORM_FS_HIDDEN   16

#define NEMOMP_FC_ROOT      L"java_root/"
#define NEMOMP_FC_ROOT_LEN  10


#define NEMOMP_FC_CARD_ROOT      L"java_card/"
#define NEMOMP_FC_CARD_ROOT_LEN  10
//shouldn't be the same, it's used to judge which storage
#define NEMOMP_FC_NAND_ROOT      L"java_phone/"
#define NEMOMP_FC_NAND_ROOT_LEN  11

extern int nemomp_check_sd_exist(void);


extern int nemomp_file_adv_getfullpath(char *path); //path is a 1024 bytes array
extern int nemomp_file_adv_getplatformpath_maxsize(void);

//2009.10.12 SJH ADD ---
typedef struct nemomp_opened_file
{
	int handle;
	struct nemomp_opened_file *next;

} nemomp_fs_opened_file;

typedef nemomp_fs_opened_file *nemomp_opened_file_list_ptr;

extern nemomp_opened_file_list_ptr nemomp_file_list_head;

extern int nemomp_add_fd(int fd);
extern int nemomp_remove_fd(int fd);
extern void nemomp_list_fd(void);
extern int nemomp_get_fd_count(void);
extern void nemomp_force_close_all_fd(void);
//--2009.10.12 SJH ADD ---


extern int nemomp_file_adv_get_attributes(const char *filename,int attribute);
extern void nemomp_file_adv_set_attributes(const char *filename,int attribute,int value);
extern int nemomp_file_adv_mkdir(char * path);
extern int nemomp_file_adv_rmdir(char * path);
extern int nemomp_file_adv_unlink(char * path);
extern int nemomp_file_adv_open(char * path, int accessMode);

extern int nemomp_file_adv_findfirst(char * path, char * filter, char * resultbuf);
extern int nemomp_file_adv_findnext(int dir_handle, char * resultbuf);
extern void nemomp_file_adv_findclose(int dir_handle);

#define PLATFORM_FS_EXCLUDE_SUBDIR 0
#define PLATFORM_FS_INCLUDE_SUBDIR 1
extern int nemomp_file_adv_getdirsize(char *path,int includeDir);

extern int nemomp_file_adv_truncate(char *path,int size);
extern void nemomp_file_adv_movefile(char * pathExist, char * pathNew);

extern __int64 nemomp_file_getlastmod(char *path);
#endif

//extern int nemomp_jam_get_sd_free_size(unsigned int *totalSize, unsigned int *freeSize);
extern int nemomp_jam_remove_remain(char *string);
#endif /* __NEMOMP_FILES_H__ */
