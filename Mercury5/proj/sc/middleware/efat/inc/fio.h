#ifndef ONCE_FIO_H
#define ONCE_FIO_H
////////////////////////////////////////////////////////////////////////////////
///@file fio.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_system.h>
#include <pkgconf_hal.h>
#include <pkgconf_io_fileio.h>
#include <pkgconf_isoinfra.h>
#include <limits.h>
#include <infra_type.h>
#include <stddef.h>
#include <sys_types.h>
#include <fileio_fileio.h>

//=============================================================================

#ifdef PKG_KERNEL

//#include <pkgconf/kernel.h>
#include <pkgconf_kernel.h>

#define FILEIO_MUTEX_LOCK(_m_)     efat_drv_mutex_lock(&(_m_))
#define FILEIO_MUTEX_UNLOCK(_m_)   efat_drv_mutex_unlock(&(_m_))

#define FILEIO_SEMA_LOCK()
#define FILEIO_COND_WAIT( __cv )   efat_drv_cond_wait( &(__cv) )
#define FILEIO_COND_SIGNAL( __cv ) efat_drv_cond_broadcast( &(__cv) )

#else

#define FILEIO_MUTEX_LOCK(_m_)     EFAT_EMPTY_STATEMENT
#define FILEIO_MUTEX_UNLOCK(_m_)   EFAT_EMPTY_STATEMENT

#define FILEIO_COND_WAIT( __cv )   EFAT_EMPTY_STATEMENT
#define FILEIO_COND_SIGNAL( __cv ) EFAT_EMPTY_STATEMENT

#endif

//=============================================================================
// POSIX API support

#ifdef PKG_POSIX

#else

#define EFAT_IO_FUNCTION_START() EFAT_EMPTY_STATEMENT
#define EFAT_IO_FUNCTION_FINISH() EFAT_EMPTY_STATEMENT

#endif

#ifdef PKG_POSIX_SIGNALS

#define EFAT_IO_SIGMASK_SET( __set, __oset ) \
        EFAT_PTHREAD_SIGMASK_SET( __set, __oset )

#define EFAT_IO_SIGPENDING() EFAT_POSIX_SIGPENDING()

#define EFAT_IO_DELIVER_SIGNALS( __mask ) \
        EFAT_POSIX_DELIVER_SIGNALS( __mask )

#else

#define EFAT_IO_SIGMASK_SET( __set, __oset ) \
EFAT_MACRO_START \
EFAT_UNUSED_PARAM( const sigset_t*, __set ); \
EFAT_UNUSED_PARAM( const sigset_t*, __oset ); \
EFAT_MACRO_END

#define EFAT_IO_SIGPENDING() (0)

#define EFAT_IO_DELIVER_SIGNALS( __mask ) EFAT_UNUSED_PARAM( const sigset_t*, __mask )

#ifndef __sigset_t_defined
#define __sigset_t_defined
typedef int sigset_t;
#endif

#endif

//=============================================================================
// Fileio function entry and return macros.

// Handle entry to a fileio package function.
#define FILEIO_ENTRY()                          \
    EFAT_REPORT_FUNCTYPE( "returning %d" );      \
    EFAT_IO_FUNCTION_START();                \

// Do a fileio package defined return. This requires the error code
// to be placed in errno, and if it is non-zero, -1 returned as the
// result of the function. This also gives us a place to put any
// generic tidyup handling needed for things like signal delivery and
// cancellation.
extern int efat_errno;
#define FILEIO_RETURN(err)                      \
EFAT_MACRO_START                                 \
    int __retval = 0;                           \
    EFAT_IO_FUNCTION_FINISH();               \
    if( err != 0 )                              \
    {                                           \
        __retval = -1;                          \
        efat_errno = err;                            \
    }                                           \
    EFAT_REPORT_RETVAL( __retval );              \
    return __retval;                            \
EFAT_MACRO_END

#define FILEIO_RETURN_VALUE(val)                \
EFAT_MACRO_START                                 \
    EFAT_IO_FUNCTION_FINISH();               \
    EFAT_REPORT_RETVAL( val );                   \
    return val;                                 \
EFAT_MACRO_END

#define FILEIO_RETURN_VOID()                    \
EFAT_MACRO_START                                 \
    EFAT_IO_FUNCTION_FINISH();               \
    EFAT_REPORT_RETURN();                        \
    return;                                     \
EFAT_MACRO_END

//=============================================================================
// Cancellation support
// If the POSIX package is present we want to include cancellation points
// in the routines that are defined to contain them.
// The macro EFAT_CANCELLATION_POINT does this.

#ifdef INT_ISO_PTHREAD_IMPL
#define EFAT_CANCELLATION_POINT pthread_testcancel()
#else
#define EFAT_CANCELLATION_POINT EFAT_EMPTY_STATEMENT
#endif

//=============================================================================
// Internal exports

// Current directory info
__externC mtabEntry *efat_cdir_mtab_entry;
__externC efat_dir efat_cdir_dir;
__externC int efat_cdir_refcount;

__externC int efat_mtab_lookup( efat_dir *dir, const char **name, mtabEntry **mte);


__externC int efat_mtab_wlookup( efat_dir *dir, const utf16 **name, mtabEntry **mte);
__externC int efat_mtab_wlookup_locked( efat_dir *dir, const utf16 **name, mtabEntry **mte);
//#ifndef O_UNICODE
//#define O_UNICODE (1<<31)
//#endif



__externC int efat_mtab_lookup_locked( efat_dir *dir, const char **name, mtabEntry **mte);

__externC void efat_cdir_unref( void );


__externC void efat_fs_lock( mtabEntry *mte, efat_uint32 syncmode );

__externC void efat_fs_unlock( mtabEntry *mte, efat_uint32 syncmode );

//-----------------------------------------------------------------------------

__externC void efat_fd_init(void);

__externC efat_file *efat_file_alloc(void);

__externC void efat_file_free(efat_file * fp);

__externC int efat_fd_alloc(int low);

__externC void efat_fd_assign(int fd, efat_file *fp);

__externC int efat_fd_free(int fd);

__externC efat_file *efat_fp_get( int fd );

__externC void efat_fp_free( efat_file *fp );

__externC void efat_file_lock( efat_file *fp, efat_uint32 syncmode );

__externC void efat_file_unlock( efat_file *fp, efat_uint32 syncmode );

//-----------------------------------------------------------------------------
// Exports from socket.cxx

__externC void efat_nstab_init(void);

//-----------------------------------------------------------------------------
// Implement filesystem locking protocol.

#define LOCK_FS( _mte_ )  {                             \
   EFAT_ASSERT(_mte_ != NULL, "Bad mount table entry");  \
   efat_fs_lock( _mte_, (_mte_)->fs->syncmode);          \
}

#define UNLOCK_FS( _mte_ ) efat_fs_unlock( _mte_, (_mte_)->fs->syncmode)

#ifdef PKG_KERNEL
//-----------------------------------------------------------------------------
// FILEIO global lock. This protects allocation and freeing of mount
// table entries. It also protects access to the current directory
// variables. The current directory wait condition variable is
// signalled whenever the reference counter is zeroed and allows
// threads to wait until the current directory variables are available
// for reassignment.
#if 1
__externC efat_drv_mutex_t fileio_lock;

__externC efat_drv_cond_t efat_cdir_wait;
#endif
#endif

//-----------------------------------------------------------------------------
#endif // ifndef ONCE_FIO_H
// End of fio.h
