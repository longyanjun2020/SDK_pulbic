#ifndef __SQLITE_PORTING__
#define __SQLITE_PORTING__

#define __USE_OS_WIN__ 1

#ifdef __STANDALONE__

#if __USE_OS_WIN__
#define SQLITE_OS_WIN 1
#else //__USE_OS_WIN__
#define SQLITE_OS_OTHER 1
#endif //__USE_OS_WIN__

#else //__STANDALONE__
#define SQLITE_OS_OTHER 1
#define SQLITE_OS_WIN 0
#endif //__STANDALONE__

//#define __DJGPP__ 1
#define SQLITE_THREADSAFE 2
/*
** The SQLITE_THREADSAFE macro must be defined as 0, 1, or 2.
** 0 means mutexes are permanently disable and the library is never
** threadsafe.  1 means the library is serialized which is the highest
** level of threadsafety.  2 means the libary is multithreaded - multiple
** threads can use SQLite as long as no two threads try to use the same
** database connection at the same time.
**
** Older versions of SQLite used an optional THREADSAFE macro.
** We support that for legacy.
*/

//#define SQLITE_OMIT_WAL 1
//#define SQLITE_OMIT_LOAD_EXTENSION 1
//#define SQLITE_OMIT_AUTOINIT

#define SQLITE_ENABLE_FTS3
#define SQLITE_OMIT_LOAD_EXTENSION
#define SQLITE_ENABLE_COLUMN_METADATA

#include "linux_errno.h"

#ifndef __STANDALONE__
extern char ven_dbg_trace(unsigned int level, char *strFormat, ...);
#include "mdl_vfs_errno.h"
#include "mdl_vfs_struct.h"

#define _SYS     ((unsigned int) ((0x1A) & 0xFF))
#define LEVEL_8  (0x08 << 8)
#define _SQLITE3_                                (_SYS | LEVEL_8)
void SQLITE3_TRACE_LOG(const char *fmt, ...);

#define CCHMAXPATH                  (VFS_FAT_SPEC_FULLPATH_LEN)
#else // __STANDALONE__
#define FAT_NO_ERROR                (1)
#define FAT_NOT_EXISTING_FILE       (-11)
#define CCHMAXPATH                  (262+1)

//Debugging IO
typedef struct
{
    unsigned int nOpenCounter;
    unsigned int nCloseCounter;
    unsigned int nReadCounter;
    unsigned int nWriteCounter;
} IOStatus_t;

//Debugging Memory
typedef struct
{
    unsigned int nPeak;
    unsigned int nCurrentUsed;
    unsigned int nMemCounter;
} MemoryStatus_t;

typedef char ascii;

#endif //__STANDALONE__

#define MAX_NAME_LENGTH CCHMAXPATH
#define VFS_VOLUME_NAME_LENGTH      (6)
#define FREEIF(p)       if(p != 0) {free(p); p = 0;}

typedef int HFILE;

#endif
