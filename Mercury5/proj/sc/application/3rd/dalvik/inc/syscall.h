#ifndef __SYSCALL_H__
#define __SYSCALL_H__

#ifdef __cplusplus
extern "C"{
#endif

/* emmi sdk */
#include "ven_time.h"
#include "ven_dbg.h"
#include "ven_os.h"
#include "ven_file.h"
/* emmi sdk */

/* java define */
#include "java_def.h"

/* errno */
#include "dvm_errno.h"

#define __DALVIK_DEBUG__

#ifdef __DALVIK_DEBUG__
extern int dvk_printf(const char *format, ...);
#define DALVIK_PRINTF	dvk_printf
#else
#define DALVIK_PRINTF(...)	do {} while(0)
#endif

#define DALVIK_MALLOC __newlib_malloc
#define DALVIK_FREE	__newlib_free

#define FD_MAX		15

#if 1
#include <fcntl.h>
#endif


/* size type */
typedef int ssize_t;
//typedef unsigned int size_t;
/* size type */

/* time define */


typedef long time_t;
typedef long susecond_t;


/*
struct timeval{
	time_t		tv_sec;
	susecond_t	tv_usec;
};
*/

struct timezone{
	int tz_minuteswest;
	int tz_dsttime;
};



/* time define */


/*file mode type */
typedef unsigned int mode_t;
typedef long int blksize_t;
typedef long int blkcnt_t;
/*
typedef unsigned long int dev_t;
typedef unsigned long int ino_t;

typedef unsigned int nlink_t;
typedef int pid_t;
typedef unsigned int uid_t;
typedef unsigned int gid_t;
typedef long int off_t;
*/



/*file mode type */



#if 1
#include <sys/stat.h>
#endif


//extern int errno;

/* file IO*/
int isatty(int desc);

//int open(const char* pathname, int flags);
//int open(const char* pathname, int flags, mode_t mode);
int creat(const char* pathname, mode_t mode);
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, void *buf, size_t count);
off_t lseek(int fd, off_t offset, int whence);
int close(int fd);
int unlink(const char* pathname);
int fsync(int fd);
int fdatasync(int fd);

int truncate(const char* path, off_t length);
int ftruncate(int fd, off_t length);

// not implemented!!
int stat(const char*path, struct stat *buf);
int fstat(int fd, struct stat* buf);
/* file IO*/

/* time */
//int gettimeofday(struct timeval *tv, struct timezone *tz);
/* time */
#include "mdl_vfs_file.ho"


#ifdef __cplusplus
}
#endif

#endif
