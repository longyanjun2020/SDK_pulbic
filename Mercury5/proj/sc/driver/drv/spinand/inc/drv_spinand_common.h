#include "stdcomp.h"


#ifndef _DRV_SPINAND_COMMON_H_
#define _DRV_SPINAND_COMMON_H_


#define DEBUG_SPINAND(debug_level, x)     do { if (_u8SPINANDDbgLevel >= (debug_level)) (x); } while(0)

//#ifndef U32
//#define U32  unsigned long
//#endif
//#ifndef U16
//#define U16  unsigned short
//#endif
//#ifndef U8
//#define U8   unsigned char
//#endif
//#ifndef S32
//#define S32  signed long
//#endif
//#ifndef S16
//#define S16  signed short
//#endif
//#ifndef S8
//#define S8   signed char
//#endif
//#ifndef NULL
//#define NULL (void*)0
//#endif
//#ifndef BOOL
//#define BOOL unsigned char
//#endif
#define EPERM           1                // Operation not permitted
#define ENOENT          2                // No such file or directory
#define ESRCH           3                // No such process
#define EINTR           4                // Interrupted system call
#define EIO             5                // Input/output error
#define ENXIO           6                // Device not configured
#define E2BIG           7                // Argument list too long
#define ENOEXEC         8                // Exec format error
#define EBADF           9                // Bad file number
#define ECHILD          10               // No spawned processes
#define EAGAIN          11               // Resource temporarily unavailable
#define ENOMEM          12               // Cannot allocate memory
#define EACCES          13               // Access denied
#define EFAULT          14               // Bad address
#define ENOTBLK         15               // Not block device
#define EBUSY           16               // Device busy
#define EEXIST          17               // File exist
#define EXDEV           18               // Cross-device link
#define ENODEV          19               // Operation not supported by device
#define ENOTDIR         20               // Not a directory
#define EISDIR          21               // Is a directory
#define EINVAL_SQLITE   22               // Invalid argument
#define ENFILE          23               // Too many open files in system
#define EMFILE          24               // Too many files open
#define ENOTTY          25               // Inappropriate ioctl for device
#define ETXTBSY         26               // Unknown error
#define EFBIG           27               // File too large
#define ENOSPC          28               // No space left on device
#define ESPIPE          29               // Illegal seek
#define EROFS           30               // Read-only file system
#define EMLINK          31               // Too many links
#define EPIPE           32               // Broken pipe
#define EDOM            33               // Numerical arg out of domain
#define ERANGE          34               // Result too large
#define EUCLEAN         35               // Structure needs cleaning
#define EDEADLK         36               // Resource deadlock avoided
#define EUNKNOWN        37               // Unknown error
#define ENAMETOOLONG    38               // File name too long
#define ENOLCK          39               // No locks available
#define ENOSYS          40               // Function not implemented
#define ENOTEMPTY       41               // Directory not empty
#define EILSEQ          42               // Invalid multibyte sequence

typedef enum _SPINAND_ERROR_NUM
{
    ERR_SPINAND_SUCCESS,
    ERR_SPINAND_UNKNOWN_ID,
    ERR_SPINAND_TIMEOUT,
    ERR_SPINAND_ECC_ERROR,
    ERR_SPINAND_ECC_BITFLIP,
    ERR_SPINAND_BAD_BLK,
    ERR_SPINAND_E_FAIL,
    ERR_SPINAND_W_FAIL,
    ERR_SPINAND_INVALID
} SpinandFlashErron_e;

typedef enum
{
    E_SPINAND_SINGLE_MODE,
    E_SPINAND_FAST_MODE,
    E_SPINAND_DUAL_MODE,
    E_SPINAND_DUAL_MODE_IO,
    E_SPINAND_QUAD_MODE,
    E_SPINAND_QUAD_MODE_IO,
} SpinandMode_e;

typedef struct
{
    u8   nIDByteCnt;
    u8   aID[15];
    u16  nSpareByteCnt;
    u16  nPageByteCnt;
    u16  nBlkPageCnt;
    u16  nBlkCnt;
    u16  nSectorByteCnt;
    u8   nPlaneCnt;
    u8   nWrapConfig;
    bool bRIURead;
    u8   nCLKConfig;
    u8   nUBOOTPBA;
    u8   nBL0PBA;
    u8   nBL1PBA;
    u8   nHashPBA[3][2];
    u8   nReadMode;
    u8   nWriteMode;
} SpinandInfo_t;
#if !defined(TRUE) && !defined(FALSE)
/// definition for TRUE
#define TRUE                        1
/// definition for FALSE
#define FALSE                       0
#endif
#endif
