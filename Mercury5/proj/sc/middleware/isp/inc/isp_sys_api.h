#ifndef ISP_SYS_API_H_
#define ISP_SYS_API_H_

//#define ISP_MEM_DBG

#ifndef IspSysCalloc
#define ISP_CALLPC

#define LINUX 0
#define RTK 1

#define OS_SEL RTK

#include <isp_types.h>
#if(OS_SEL == RTK)
#include "sys_MsWrapper_cus_os_mem.h"
#include "sys_MsWrapper_cus_os_util.h"
//#include <mmps_fs.h>

typedef struct rtk_file{

    int fd;

}RTK_FILE;

#define FILE RTK_FILE

#endif
//#include <stdio.h>

//#define ISP_MEM_DBG
//#define ISP_SYS_FOPEN_DBG
//#define ISP_SYS_OPEN_DBG
//#define ISP_MMP_DBG



#ifndef ISP_MMP_DBG
void* IspSysMmap(void *addr, int length, int prot, int flags,int fd, int offset);
int IspSysMunmap(void *addr, int length);
void show_mmap_dbg_info(void);
#else
void mmap_list_put(void* ptr,const char *msg,unsigned int line);
void mmap_list_pop(void* ptr);
void show_mmap_list_dbg_info(void);
void IspSysMmap_dbg_free_all();
void* IspSysMmap_dbg(void *addr, int length, int prot, int flags,int fd, int offset,const char* msg,unsigned int line);
int IspSysMunmap_dbg(void *addr, int length);
#define IspSysMmap(addr,length,prot,flags,fd,offset) IspSysMmap_dbg(addr,length,prot,flags,fd,offset,__FUNCTION__,__LINE__)
#define IspSysMunmap(addr,length) IspSysMunmap_dbg(addr,length);
#define show_mmap_dbg_info show_mmap_list_dbg_info
#endif

#ifndef ISP_MEM_DBG
void* IspSysMalloc(int size);
void* IspSysCalloc(int num,int size);
void* IspSysMallocNonCatch(int size);
void IspSysFree(void* ptr);
void show_malloc_dbg_info(void);
#define IspSysMalloc_dbg_free_all()
#else
void* IspSysMalloc_dbg(int size,const char *msg,unsigned int line);
void* IspSysMallocNonCatch_dbg(int size,const char *msg,unsigned int line);
void* IspSysCalloc_dbg(int num,int size,const char *msg,unsigned int line);
void IspSysFree_dbg(void* ptr);
#define IspSysMalloc(size) IspSysMalloc_dbg(size,__FUNCTION__,__LINE__)
#define IspSysMallocNonCatch(size) IspSysMallocNonCatch_dbg(size,__FUNCTION__,__LINE__)
#define IspSysCalloc(num,size) IspSysCalloc_dbg(num,size,__FUNCTION__,__LINE__)
#define IspSysFree(ptr) IspSysFree_dbg(ptr)
void show_malloc_dbg_info(void);
void IspSysMalloc_dbg_free_all();
#endif

#ifndef ISP_SYS_FOPEN_DBG
#if(OS_SEL == LINUX || OS_SEL == RTK)
FILE* IspSysFOpen(const char *filename,const char *opentype);
void IspSysFClose(FILE* fd);
int IspSysFeof(FILE *fd);
char* IspSysFgets(char* s,int count,FILE* fd);
int IspSysFread(void *ptr,int size,int count,FILE *fd);
int IspSysGetFileSize(FILE *fd,int *FileSize);
#endif
void show_fopen_dbg_info(void);
#define IspSysFOpen_dbg_free_all()
#else
#if(OS_SEL == LINUX)
FILE* IspSysFOpen_dbg(const char *filename,const char *opentype,const char *msg,unsigned int line);
void IspSysFClose_dbg(FILE* fd);
#endif
#define IspSysFOpen(filename,opentype) IspSysFOpen_dbg(filename,opentype,__FUNCTION__,__LINE__)
#define IspSysFClose(fd) IspSysFClose_dbg(fd)
void show_fopen_dbg_info(void);
void IspSysFOpen_dbg_free_all();
#endif

#ifndef ISP_SYS_OPEN_DBG
int IspSysOpen(const char *pathname,int flag);
void IspSysClose(int fd);
void show_open_dbg_info(void);
#define IspSysOpen_dbg_free_all()
#else
int IspSysOpen_dbg(const char *filename,int flag,const char *msg,unsigned int line);
void IspSysClose_dbg(int fd);
void show_open_dbg_info(void);
void IspSysOpen_dbg_free_all();
#define IspSysOpen(filename,flag) IspSysOpen_dbg(filename,flag,__FUNCTION__,__LINE__)
#define IspSysClose(fd) IspSysClose_dbg(fd)
#endif

void* IspSysDlOpen(const char *filename,int flags);
void IspSysDlClose(void* handle);
void show_dlopen_dbg_info(void);

#endif
#endif //ISP_SYS_API_H_
