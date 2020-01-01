/*
 */

#ifndef AIT4LINUX_H_
#define AIT4LINUX_H_

#include "ahc_common.h"


//#define NULL            0
#define V4L_MAX_NAME_LENGTH 16
#define MAX_FILE_NODE       NCFG_V4L_MAX_FILE_NODES


typedef UINT8   __u8;
typedef INT16   __s16;
typedef INT32   __s32;
typedef INT64   __s64;
typedef UINT16  __u16;
typedef UINT32  __u32;
typedef UINT64  __u64;
typedef UINT8   u8;
typedef UINT16  u16;
typedef UINT32  u32;
typedef UINT64  u64;
typedef UINT32  __kernel_time_t;
typedef INT32   __kernel_suseconds_t;


typedef unsigned int        __kernel_size_t;
typedef int                 __kernel_ssize_t;

typedef long long           __kernel_loff_t;
typedef __kernel_loff_t     loff_t;

typedef __kernel_ssize_t    ssize_t;
typedef unsigned int        size_t;
typedef u32                 dma_addr_t;

typedef unsigned int        gfp_t;

//#ifndef LWIP_TIMEVAL_PRIVATE
struct v4l_timeval {
    __kernel_time_t         tv_sec;         /* seconds */
    __kernel_suseconds_t    tv_usec;        /* microseconds */
};
//#endif
struct file;
/* These macros are for out of kernel modules to test that
 * the kernel supports the unlocked_ioctl and compat_ioctl
 * fields in struct file_operations. */
struct file_operations {
	int (*open) (struct file *);
	int (*unlocked_ioctl) (struct file*, unsigned int, void*);
	int (*release) (struct file *);
};

struct file {
    unsigned int uiId;
    char   chPath[V4L_MAX_NAME_LENGTH];
    unsigned int uiRefCount;
	unsigned int f_flags;
	const struct file_operations *f_op;
	
	/* needed for tty driver, and maybe others */
	void   *private_data;
	struct file *next;
	struct file *prev;    
};

void initFileDevice(void);

int open(char *device_name, int flags);
int ioctl(int fd, unsigned int request, void *argp);
int close(int fd);
#endif
