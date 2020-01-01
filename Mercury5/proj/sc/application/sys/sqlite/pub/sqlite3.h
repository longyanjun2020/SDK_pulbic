#ifndef _SQLITE3_H_
#define _SQLITE3_H_
#include <stdarg.h>     /* Needed for the definition of va_list */

/*
** Add the ability to override 'extern'
*/
#ifndef SQLITE_EXTERN
# define SQLITE_EXTERN extern
#endif

#ifndef SQLITE_API
# define SQLITE_API
#endif


/*
** These no-op macros are used in front of interfaces to mark those
** interfaces as either deprecated or experimental.  New applications
** should not use deprecated interfaces - they are support for backwards
** compatibility only.  Application writers should be aware that
** experimental interfaces are subject to change in point releases.
**
** These macros used to resolve to various kinds of compiler magic that
** would generate warning messages when they were used.  But that
** compiler magic ended up generating such a flurry of bug reports
** that we have taken it all out and gone back to using simple
** noop macros.
*/
#define SQLITE_DEPRECATED
#define SQLITE_EXPERIMENTAL

/*
** Ensure these symbols were not defined by some previous header file.
*/
#ifdef SQLITE_VERSION
# undef SQLITE_VERSION
#endif
#ifdef SQLITE_VERSION_NUMBER
# undef SQLITE_VERSION_NUMBER
#endif

/*
** CAPI3REF: Compile-Time Library Version Numbers
**
** ^(The [SQLITE_VERSION] C preprocessor macro in the sqlite3.h header
** evaluates to a string literal that is the SQLite version in the
** format "X.Y.Z" where X is the major version number (always 3 for
** SQLite3) and Y is the minor version number and Z is the release number.)^
** ^(The [SQLITE_VERSION_NUMBER] C preprocessor macro resolves to an integer
** with the value (X*1000000 + Y*1000 + Z) where X, Y, and Z are the same
** numbers used in [SQLITE_VERSION].)^
** The SQLITE_VERSION_NUMBER for any given release of SQLite will also
** be larger than the release from which it is derived.  Either Y will
** be held constant and Z will be incremented or else Y will be incremented
** and Z will be reset to zero.
**
** Since version 3.6.18, SQLite source code has been stored in the
** <a href="http://www.fossil-scm.org/">Fossil configuration management
** system</a>.  ^The SQLITE_SOURCE_ID macro evaluates to
** a string which identifies a particular check-in of SQLite
** within its configuration management system.  ^The SQLITE_SOURCE_ID
** string contains the date and time of the check-in (UTC) and an SHA1
** hash of the entire source tree.
**
** See also: [sqlite3_libversion()],
** [sqlite3_libversion_number()], [sqlite3_sourceid()],
** [sqlite_version()] and [sqlite_source_id()].
*/
#define SQLITE_VERSION        "3.7.5"
#define SQLITE_VERSION_NUMBER 3007005
#define SQLITE_SOURCE_ID      "2011-01-28 17:03:50 ed759d5a9edb3bba5f48f243df47be29e3fe8cd7"


/*
** CAPI3REF: Database Connection Handle
** KEYWORDS: {database connection} {database connections}
**
** Each open SQLite database is represented by a pointer to an instance of
** the opaque structure named "sqlite3".  It is useful to think of an sqlite3
** pointer as an object.  The [sqlite3_open()], [sqlite3_open16()], and
** [sqlite3_open_v2()] interfaces are its constructors, and [sqlite3_close()]
** is its destructor.  There are many other interfaces (such as
** [sqlite3_prepare_v2()], [sqlite3_create_function()], and
** [sqlite3_busy_timeout()] to name but three) that are methods on an
** sqlite3 object.
*/
typedef struct sqlite3 sqlite3;

/*
** CAPI3REF: 64-Bit Integer Types
** KEYWORDS: sqlite_int64 sqlite_uint64
**
** Because there is no cross-platform way to specify 64-bit integer types
** SQLite includes typedefs for 64-bit signed and unsigned integers.
**
** The sqlite3_int64 and sqlite3_uint64 are the preferred type definitions.
** The sqlite_int64 and sqlite_uint64 types are supported for backwards
** compatibility only.
**
** ^The sqlite3_int64 and sqlite_int64 types can store integer values
** between -9223372036854775808 and +9223372036854775807 inclusive.  ^The
** sqlite3_uint64 and sqlite_uint64 types can store integer values 
** between 0 and +18446744073709551615 inclusive.
*/
#ifdef SQLITE_INT64_TYPE
  typedef SQLITE_INT64_TYPE sqlite_int64;
  typedef unsigned SQLITE_INT64_TYPE sqlite_uint64;
#elif defined(_MSC_VER) || defined(__BORLANDC__)
  typedef __int64 sqlite_int64;
  typedef unsigned __int64 sqlite_uint64;
#else
  typedef long long int sqlite_int64;
  typedef unsigned long long int sqlite_uint64;
#endif
typedef sqlite_int64 sqlite3_int64;
typedef sqlite_uint64 sqlite3_uint64;

/*
** If compiling for a processor that lacks floating point support,
** substitute integer for floating-point.
*/
#ifdef SQLITE_OMIT_FLOATING_POINT
# define double sqlite3_int64
#endif

/*
** CAPI3REF: Closing A Database Connection
**
** ^The sqlite3_close() routine is the destructor for the [sqlite3] object.
** ^Calls to sqlite3_close() return SQLITE_OK if the [sqlite3] object is
** successfully destroyed and all associated resources are deallocated.
**
** Applications must [sqlite3_finalize | finalize] all [prepared statements]
** and [sqlite3_blob_close | close] all [BLOB handles] associated with
** the [sqlite3] object prior to attempting to close the object.  ^If
** sqlite3_close() is called on a [database connection] that still has
** outstanding [prepared statements] or [BLOB handles], then it returns
** SQLITE_BUSY.
**
** ^If [sqlite3_close()] is invoked while a transaction is open,
** the transaction is automatically rolled back.
**
** The C parameter to [sqlite3_close(C)] must be either a NULL
** pointer or an [sqlite3] object pointer obtained
** from [sqlite3_open()], [sqlite3_open16()], or
** [sqlite3_open_v2()], and not previously closed.
** ^Calling sqlite3_close() with a NULL pointer argument is a 
** harmless no-op.
*/
SQLITE_API int sqlite3_close(sqlite3 *);

/*
** The type for a callback function.
** This is legacy and deprecated.  It is included for historical
** compatibility and is not documented.
*/
typedef int (*sqlite3_callback)(void*,int,char**, char**);

/*
** CAPI3REF: One-Step Query Execution Interface
**
** The sqlite3_exec() interface is a convenience wrapper around
** [sqlite3_prepare_v2()], [sqlite3_step()], and [sqlite3_finalize()],
** that allows an application to run multiple statements of SQL
** without having to use a lot of C code. 
**
** ^The sqlite3_exec() interface runs zero or more UTF-8 encoded,
** semicolon-separate SQL statements passed into its 2nd argument,
** in the context of the [database connection] passed in as its 1st
** argument.  ^If the callback function of the 3rd argument to
** sqlite3_exec() is not NULL, then it is invoked for each result row
** coming out of the evaluated SQL statements.  ^The 4th argument to
** to sqlite3_exec() is relayed through to the 1st argument of each
** callback invocation.  ^If the callback pointer to sqlite3_exec()
** is NULL, then no callback is ever invoked and result rows are
** ignored.
**
** ^If an error occurs while evaluating the SQL statements passed into
** sqlite3_exec(), then execution of the current statement stops and
** subsequent statements are skipped.  ^If the 5th parameter to sqlite3_exec()
** is not NULL then any error message is written into memory obtained
** from [sqlite3_malloc()] and passed back through the 5th parameter.
** To avoid memory leaks, the application should invoke [sqlite3_free()]
** on error message strings returned through the 5th parameter of
** of sqlite3_exec() after the error message string is no longer needed.
** ^If the 5th parameter to sqlite3_exec() is not NULL and no errors
** occur, then sqlite3_exec() sets the pointer in its 5th parameter to
** NULL before returning.
**
** ^If an sqlite3_exec() callback returns non-zero, the sqlite3_exec()
** routine returns SQLITE_ABORT without invoking the callback again and
** without running any subsequent SQL statements.
**
** ^The 2nd argument to the sqlite3_exec() callback function is the
** number of columns in the result.  ^The 3rd argument to the sqlite3_exec()
** callback is an array of pointers to strings obtained as if from
** [sqlite3_column_text()], one for each column.  ^If an element of a
** result row is NULL then the corresponding string pointer for the
** sqlite3_exec() callback is a NULL pointer.  ^The 4th argument to the
** sqlite3_exec() callback is an array of pointers to strings where each
** entry represents the name of corresponding result column as obtained
** from [sqlite3_column_name()].
**
** ^If the 2nd parameter to sqlite3_exec() is a NULL pointer, a pointer
** to an empty string, or a pointer that contains only whitespace and/or 
** SQL comments, then no SQL statements are evaluated and the database
** is not changed.
**
** Restrictions:
**
** <ul>
** <li> The application must insure that the 1st parameter to sqlite3_exec()
**      is a valid and open [database connection].
** <li> The application must not close [database connection] specified by
**      the 1st parameter to sqlite3_exec() while sqlite3_exec() is running.
** <li> The application must not modify the SQL statement text passed into
**      the 2nd parameter of sqlite3_exec() while sqlite3_exec() is running.
** </ul>
*/
SQLITE_API int sqlite3_exec(
  sqlite3*,                                  /* An open database */
  const char *sql,                           /* SQL to be evaluated */
  int (*callback)(void*,int,char**,char**),  /* Callback function */
  void *,                                    /* 1st argument to callback */
  char **errmsg                              /* Error msg written here */
);

/*
** CAPI3REF: Result Codes
** KEYWORDS: SQLITE_OK {error code} {error codes}
** KEYWORDS: {result code} {result codes}
**
** Many SQLite functions return an integer result code from the set shown
** here in order to indicates success or failure.
**
** New error codes may be added in future versions of SQLite.
**
** See also: [SQLITE_IOERR_READ | extended result codes]
*/
#define SQLITE_OK           0   /* Successful result */
/* beginning-of-error-codes */
#define SQLITE_ERROR        1   /* SQL error or missing database */
#define SQLITE_INTERNAL     2   /* Internal logic error in SQLite */
#define SQLITE_PERM         3   /* Access permission denied */
#define SQLITE_ABORT        4   /* Callback routine requested an abort */
#define SQLITE_BUSY         5   /* The database file is locked */
#define SQLITE_LOCKED       6   /* A table in the database is locked */
#define SQLITE_NOMEM        7   /* A malloc() failed */
#define SQLITE_READONLY     8   /* Attempt to write a readonly database */
#define SQLITE_INTERRUPT    9   /* Operation terminated by sqlite3_interrupt()*/
#define SQLITE_IOERR       10   /* Some kind of disk I/O error occurred */
#define SQLITE_CORRUPT     11   /* The database disk image is malformed */
#define SQLITE_NOTFOUND    12   /* Unknown opcode in sqlite3_file_control() */
#define SQLITE_FULL        13   /* Insertion failed because database is full */
#define SQLITE_CANTOPEN    14   /* Unable to open the database file */
#define SQLITE_PROTOCOL    15   /* Database lock protocol error */
#define SQLITE_EMPTY       16   /* Database is empty */
#define SQLITE_SCHEMA      17   /* The database schema changed */
#define SQLITE_TOOBIG      18   /* String or BLOB exceeds size limit */
#define SQLITE_CONSTRAINT  19   /* Abort due to constraint violation */
#define SQLITE_MISMATCH    20   /* Data type mismatch */
#define SQLITE_MISUSE      21   /* Library used incorrectly */
#define SQLITE_NOLFS       22   /* Uses OS features not supported on host */
#define SQLITE_AUTH        23   /* Authorization denied */
#define SQLITE_FORMAT      24   /* Auxiliary database format error */
#define SQLITE_RANGE       25   /* 2nd parameter to sqlite3_bind out of range */
#define SQLITE_NOTADB      26   /* File opened that is not a database file */
#define SQLITE_ROW         100  /* sqlite3_step() has another row ready */
#define SQLITE_DONE        101  /* sqlite3_step() has finished executing */
/* end-of-error-codes */

/*
** CAPI3REF: Extended Result Codes
** KEYWORDS: {extended error code} {extended error codes}
** KEYWORDS: {extended result code} {extended result codes}
**
** In its default configuration, SQLite API routines return one of 26 integer
** [SQLITE_OK | result codes].  However, experience has shown that many of
** these result codes are too coarse-grained.  They do not provide as
** much information about problems as programmers might like.  In an effort to
** address this, newer versions of SQLite (version 3.3.8 and later) include
** support for additional result codes that provide more detailed information
** about errors. The extended result codes are enabled or disabled
** on a per database connection basis using the
** [sqlite3_extended_result_codes()] API.
**
** Some of the available extended result codes are listed here.
** One may expect the number of extended result codes will be expand
** over time.  Software that uses extended result codes should expect
** to see new result codes in future releases of SQLite.
**
** The SQLITE_OK result code will never be extended.  It will always
** be exactly zero.
*/
#define SQLITE_IOERR_READ              (SQLITE_IOERR | (1<<8))
#define SQLITE_IOERR_SHORT_READ        (SQLITE_IOERR | (2<<8))
#define SQLITE_IOERR_WRITE             (SQLITE_IOERR | (3<<8))
#define SQLITE_IOERR_FSYNC             (SQLITE_IOERR | (4<<8))
#define SQLITE_IOERR_DIR_FSYNC         (SQLITE_IOERR | (5<<8))
#define SQLITE_IOERR_TRUNCATE          (SQLITE_IOERR | (6<<8))
#define SQLITE_IOERR_FSTAT             (SQLITE_IOERR | (7<<8))
#define SQLITE_IOERR_UNLOCK            (SQLITE_IOERR | (8<<8))
#define SQLITE_IOERR_RDLOCK            (SQLITE_IOERR | (9<<8))
#define SQLITE_IOERR_DELETE            (SQLITE_IOERR | (10<<8))
#define SQLITE_IOERR_BLOCKED           (SQLITE_IOERR | (11<<8))
#define SQLITE_IOERR_NOMEM             (SQLITE_IOERR | (12<<8))
#define SQLITE_IOERR_ACCESS            (SQLITE_IOERR | (13<<8))
#define SQLITE_IOERR_CHECKRESERVEDLOCK (SQLITE_IOERR | (14<<8))
#define SQLITE_IOERR_LOCK              (SQLITE_IOERR | (15<<8))
#define SQLITE_IOERR_CLOSE             (SQLITE_IOERR | (16<<8))
#define SQLITE_IOERR_DIR_CLOSE         (SQLITE_IOERR | (17<<8))
#define SQLITE_IOERR_SHMOPEN           (SQLITE_IOERR | (18<<8))
#define SQLITE_IOERR_SHMSIZE           (SQLITE_IOERR | (19<<8))
#define SQLITE_IOERR_SHMLOCK           (SQLITE_IOERR | (20<<8))
#define SQLITE_LOCKED_SHAREDCACHE      (SQLITE_LOCKED |  (1<<8))
#define SQLITE_BUSY_RECOVERY           (SQLITE_BUSY   |  (1<<8))
#define SQLITE_CANTOPEN_NOTEMPDIR      (SQLITE_CANTOPEN | (1<<8))

/*
** CAPI3REF: Flags For File Open Operations
**
** These bit values are intended for use in the
** 3rd parameter to the [sqlite3_open_v2()] interface and
** in the 4th parameter to the xOpen method of the
** [sqlite3_vfs] object.
*/
#define SQLITE_OPEN_READONLY         0x00000001  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_READWRITE        0x00000002  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_CREATE           0x00000004  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_DELETEONCLOSE    0x00000008  /* VFS only */
#define SQLITE_OPEN_EXCLUSIVE        0x00000010  /* VFS only */
#define SQLITE_OPEN_AUTOPROXY        0x00000020  /* VFS only */
#define SQLITE_OPEN_MAIN_DB          0x00000100  /* VFS only */
#define SQLITE_OPEN_TEMP_DB          0x00000200  /* VFS only */
#define SQLITE_OPEN_TRANSIENT_DB     0x00000400  /* VFS only */
#define SQLITE_OPEN_MAIN_JOURNAL     0x00000800  /* VFS only */
#define SQLITE_OPEN_TEMP_JOURNAL     0x00001000  /* VFS only */
#define SQLITE_OPEN_SUBJOURNAL       0x00002000  /* VFS only */
#define SQLITE_OPEN_MASTER_JOURNAL   0x00004000  /* VFS only */
#define SQLITE_OPEN_NOMUTEX          0x00008000  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_FULLMUTEX        0x00010000  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_SHAREDCACHE      0x00020000  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_PRIVATECACHE     0x00040000  /* Ok for sqlite3_open_v2() */
#define SQLITE_OPEN_WAL              0x00080000  /* VFS only */

/*
** CAPI3REF: Device Characteristics
**
** The xDeviceCharacteristics method of the [sqlite3_io_methods]
** object returns an integer which is a vector of the these
** bit values expressing I/O characteristics of the mass storage
** device that holds the file that the [sqlite3_io_methods]
** refers to.
**
** The SQLITE_IOCAP_ATOMIC property means that all writes of
** any size are atomic.  The SQLITE_IOCAP_ATOMICnnn values
** mean that writes of blocks that are nnn bytes in size and
** are aligned to an address which is an integer multiple of
** nnn are atomic.  The SQLITE_IOCAP_SAFE_APPEND value means
** that when data is appended to a file, the data is appended
** first then the size of the file is extended, never the other
** way around.  The SQLITE_IOCAP_SEQUENTIAL property means that
** information is written to disk in the same order as calls
** to xWrite().
*/
#define SQLITE_IOCAP_ATOMIC                 0x00000001
#define SQLITE_IOCAP_ATOMIC512              0x00000002
#define SQLITE_IOCAP_ATOMIC1K               0x00000004
#define SQLITE_IOCAP_ATOMIC2K               0x00000008
#define SQLITE_IOCAP_ATOMIC4K               0x00000010
#define SQLITE_IOCAP_ATOMIC8K               0x00000020
#define SQLITE_IOCAP_ATOMIC16K              0x00000040
#define SQLITE_IOCAP_ATOMIC32K              0x00000080
#define SQLITE_IOCAP_ATOMIC64K              0x00000100
#define SQLITE_IOCAP_SAFE_APPEND            0x00000200
#define SQLITE_IOCAP_SEQUENTIAL             0x00000400
#define SQLITE_IOCAP_UNDELETABLE_WHEN_OPEN  0x00000800

/*
** CAPI3REF: File Locking Levels
**
** SQLite uses one of these integer values as the second
** argument to calls it makes to the xLock() and xUnlock() methods
** of an [sqlite3_io_methods] object.
*/
#define SQLITE_LOCK_NONE          0
#define SQLITE_LOCK_SHARED        1
#define SQLITE_LOCK_RESERVED      2
#define SQLITE_LOCK_PENDING       3
#define SQLITE_LOCK_EXCLUSIVE     4

/*
** CAPI3REF: Synchronization Type Flags
**
** When SQLite invokes the xSync() method of an
** [sqlite3_io_methods] object it uses a combination of
** these integer values as the second argument.
**
** When the SQLITE_SYNC_DATAONLY flag is used, it means that the
** sync operation only needs to flush data to mass storage.  Inode
** information need not be flushed. If the lower four bits of the flag
** equal SQLITE_SYNC_NORMAL, that means to use normal fsync() semantics.
** If the lower four bits equal SQLITE_SYNC_FULL, that means
** to use Mac OS X style fullsync instead of fsync().
**
** Do not confuse the SQLITE_SYNC_NORMAL and SQLITE_SYNC_FULL flags
** with the [PRAGMA synchronous]=NORMAL and [PRAGMA synchronous]=FULL
** settings.  The [synchronous pragma] determines when calls to the
** xSync VFS method occur and applies uniformly across all platforms.
** The SQLITE_SYNC_NORMAL and SQLITE_SYNC_FULL flags determine how
** energetic or rigorous or forceful the sync operations are and
** only make a difference on Mac OSX for the default SQLite code.
** (Third-party VFS implementations might also make the distinction
** between SQLITE_SYNC_NORMAL and SQLITE_SYNC_FULL, but among the
** operating systems natively supported by SQLite, only Mac OSX
** cares about the difference.)
*/
#define SQLITE_SYNC_NORMAL        0x00002
#define SQLITE_SYNC_FULL          0x00003
#define SQLITE_SYNC_DATAONLY      0x00010

/*
** CAPI3REF: OS Interface Open File Handle
**
** An [sqlite3_file] object represents an open file in the 
** [sqlite3_vfs | OS interface layer].  Individual OS interface
** implementations will
** want to subclass this object by appending additional fields
** for their own use.  The pMethods entry is a pointer to an
** [sqlite3_io_methods] object that defines methods for performing
** I/O operations on the open file.
*/
typedef struct sqlite3_file sqlite3_file;
struct sqlite3_file {
  const struct sqlite3_io_methods *pMethods;  /* Methods for an open file */
};

/*
** CAPI3REF: OS Interface File Virtual Methods Object
**
** Every file opened by the [sqlite3_vfs] xOpen method populates an
** [sqlite3_file] object (or, more commonly, a subclass of the
** [sqlite3_file] object) with a pointer to an instance of this object.
** This object defines the methods used to perform various operations
** against the open file represented by the [sqlite3_file] object.
**
** If the xOpen method sets the sqlite3_file.pMethods element 
** to a non-NULL pointer, then the sqlite3_io_methods.xClose method
** may be invoked even if the xOpen reported that it failed.  The
** only way to prevent a call to xClose following a failed xOpen
** is for the xOpen to set the sqlite3_file.pMethods element to NULL.
**
** The flags argument to xSync may be one of [SQLITE_SYNC_NORMAL] or
** [SQLITE_SYNC_FULL].  The first choice is the normal fsync().
** The second choice is a Mac OS X style fullsync.  The [SQLITE_SYNC_DATAONLY]
** flag may be ORed in to indicate that only the data of the file
** and not its inode needs to be synced.
**
** The integer values to xLock() and xUnlock() are one of
** <ul>
** <li> [SQLITE_LOCK_NONE],
** <li> [SQLITE_LOCK_SHARED],
** <li> [SQLITE_LOCK_RESERVED],
** <li> [SQLITE_LOCK_PENDING], or
** <li> [SQLITE_LOCK_EXCLUSIVE].
** </ul>
** xLock() increases the lock. xUnlock() decreases the lock.
** The xCheckReservedLock() method checks whether any database connection,
** either in this process or in some other process, is holding a RESERVED,
** PENDING, or EXCLUSIVE lock on the file.  It returns true
** if such a lock exists and false otherwise.
**
** The xFileControl() method is a generic interface that allows custom
** VFS implementations to directly control an open file using the
** [sqlite3_file_control()] interface.  The second "op" argument is an
** integer opcode.  The third argument is a generic pointer intended to
** point to a structure that may contain arguments or space in which to
** write return values.  Potential uses for xFileControl() might be
** functions to enable blocking locks with timeouts, to change the
** locking strategy (for example to use dot-file locks), to inquire
** about the status of a lock, or to break stale locks.  The SQLite
** core reserves all opcodes less than 100 for its own use.
** A [SQLITE_FCNTL_LOCKSTATE | list of opcodes] less than 100 is available.
** Applications that define a custom xFileControl method should use opcodes
** greater than 100 to avoid conflicts.  VFS implementations should
** return [SQLITE_NOTFOUND] for file control opcodes that they do not
** recognize.
**
** The xSectorSize() method returns the sector size of the
** device that underlies the file.  The sector size is the
** minimum write that can be performed without disturbing
** other bytes in the file.  The xDeviceCharacteristics()
** method returns a bit vector describing behaviors of the
** underlying device:
**
** <ul>
** <li> [SQLITE_IOCAP_ATOMIC]
** <li> [SQLITE_IOCAP_ATOMIC512]
** <li> [SQLITE_IOCAP_ATOMIC1K]
** <li> [SQLITE_IOCAP_ATOMIC2K]
** <li> [SQLITE_IOCAP_ATOMIC4K]
** <li> [SQLITE_IOCAP_ATOMIC8K]
** <li> [SQLITE_IOCAP_ATOMIC16K]
** <li> [SQLITE_IOCAP_ATOMIC32K]
** <li> [SQLITE_IOCAP_ATOMIC64K]
** <li> [SQLITE_IOCAP_SAFE_APPEND]
** <li> [SQLITE_IOCAP_SEQUENTIAL]
** </ul>
**
** The SQLITE_IOCAP_ATOMIC property means that all writes of
** any size are atomic.  The SQLITE_IOCAP_ATOMICnnn values
** mean that writes of blocks that are nnn bytes in size and
** are aligned to an address which is an integer multiple of
** nnn are atomic.  The SQLITE_IOCAP_SAFE_APPEND value means
** that when data is appended to a file, the data is appended
** first then the size of the file is extended, never the other
** way around.  The SQLITE_IOCAP_SEQUENTIAL property means that
** information is written to disk in the same order as calls
** to xWrite().
**
** If xRead() returns SQLITE_IOERR_SHORT_READ it must also fill
** in the unread portions of the buffer with zeros.  A VFS that
** fails to zero-fill short reads might seem to work.  However,
** failure to zero-fill short reads will eventually lead to
** database corruption.
*/
typedef struct sqlite3_io_methods sqlite3_io_methods;
struct sqlite3_io_methods {
  int iVersion;
  int (*xClose)(sqlite3_file*);
  int (*xRead)(sqlite3_file*, void*, int iAmt, sqlite3_int64 iOfst);
  int (*xWrite)(sqlite3_file*, const void*, int iAmt, sqlite3_int64 iOfst);
  int (*xTruncate)(sqlite3_file*, sqlite3_int64 size);
  int (*xSync)(sqlite3_file*, int flags);
  int (*xFileSize)(sqlite3_file*, sqlite3_int64 *pSize);
  int (*xLock)(sqlite3_file*, int);
  int (*xUnlock)(sqlite3_file*, int);
  int (*xCheckReservedLock)(sqlite3_file*, int *pResOut);
  int (*xFileControl)(sqlite3_file*, int op, void *pArg);
  int (*xSectorSize)(sqlite3_file*);
  int (*xDeviceCharacteristics)(sqlite3_file*);
  /* Methods above are valid for version 1 */
  int (*xShmMap)(sqlite3_file*, int iPg, int pgsz, int, void volatile**);
  int (*xShmLock)(sqlite3_file*, int offset, int n, int flags);
  void (*xShmBarrier)(sqlite3_file*);
  int (*xShmUnmap)(sqlite3_file*, int deleteFlag);
  /* Methods above are valid for version 2 */
  /* Additional methods may be added in future releases */
};

/*
** CAPI3REF: Standard File Control Opcodes
**
** These integer constants are opcodes for the xFileControl method
** of the [sqlite3_io_methods] object and for the [sqlite3_file_control()]
** interface.
**
** The [SQLITE_FCNTL_LOCKSTATE] opcode is used for debugging.  This
** opcode causes the xFileControl method to write the current state of
** the lock (one of [SQLITE_LOCK_NONE], [SQLITE_LOCK_SHARED],
** [SQLITE_LOCK_RESERVED], [SQLITE_LOCK_PENDING], or [SQLITE_LOCK_EXCLUSIVE])
** into an integer that the pArg argument points to. This capability
** is used during testing and only needs to be supported when SQLITE_TEST
** is defined.
**
** The [SQLITE_FCNTL_SIZE_HINT] opcode is used by SQLite to give the VFS
** layer a hint of how large the database file will grow to be during the
** current transaction.  This hint is not guaranteed to be accurate but it
** is often close.  The underlying VFS might choose to preallocate database
** file space based on this hint in order to help writes to the database
** file run faster.
**
** The [SQLITE_FCNTL_CHUNK_SIZE] opcode is used to request that the VFS
** extends and truncates the database file in chunks of a size specified
** by the user. The fourth argument to [sqlite3_file_control()] should 
** point to an integer (type int) containing the new chunk-size to use
** for the nominated database. Allocating database file space in large
** chunks (say 1MB at a time), may reduce file-system fragmentation and
** improve performance on some systems.
**
** The [SQLITE_FCNTL_FILE_POINTER] opcode is used to obtain a pointer
** to the [sqlite3_file] object associated with a particular database
** connection.  See the [sqlite3_file_control()] documentation for
** additional information.
**
** ^(The [SQLITE_FCNTL_SYNC_OMITTED] opcode is generated internally by
** SQLite and sent to all VFSes in place of a call to the xSync method
** when the database connection has [PRAGMA synchronous] set to OFF.)^
** Some specialized VFSes need this signal in order to operate correctly
** when [PRAGMA synchronous | PRAGMA synchronous=OFF] is set, but most 
** VFSes do not need this signal and should silently ignore this opcode.
** Applications should not call [sqlite3_file_control()] with this
** opcode as doing so may disrupt the operation of the specilized VFSes
** that do require it.  
*/
#define SQLITE_FCNTL_LOCKSTATE        1
#define SQLITE_GET_LOCKPROXYFILE      2
#define SQLITE_SET_LOCKPROXYFILE      3
#define SQLITE_LAST_ERRNO             4
#define SQLITE_FCNTL_SIZE_HINT        5
#define SQLITE_FCNTL_CHUNK_SIZE       6
#define SQLITE_FCNTL_FILE_POINTER     7
#define SQLITE_FCNTL_SYNC_OMITTED     8


/*
** CAPI3REF: Mutex Handle
**
** The mutex module within SQLite defines [sqlite3_mutex] to be an
** abstract type for a mutex object.  The SQLite core never looks
** at the internal representation of an [sqlite3_mutex].  It only
** deals with pointers to the [sqlite3_mutex] object.
**
** Mutexes are created using [sqlite3_mutex_alloc()].
*/
typedef struct sqlite3_mutex sqlite3_mutex;

/*
** CAPI3REF: OS Interface Object
**
** An instance of the sqlite3_vfs object defines the interface between
** the SQLite core and the underlying operating system.  The "vfs"
** in the name of the object stands for "virtual file system".
**
** The value of the iVersion field is initially 1 but may be larger in
** future versions of SQLite.  Additional fields may be appended to this
** object when the iVersion value is increased.  Note that the structure
** of the sqlite3_vfs object changes in the transaction between
** SQLite version 3.5.9 and 3.6.0 and yet the iVersion field was not
** modified.
**
** The szOsFile field is the size of the subclassed [sqlite3_file]
** structure used by this VFS.  mxPathname is the maximum length of
** a pathname in this VFS.
**
** Registered sqlite3_vfs objects are kept on a linked list formed by
** the pNext pointer.  The [sqlite3_vfs_register()]
** and [sqlite3_vfs_unregister()] interfaces manage this list
** in a thread-safe way.  The [sqlite3_vfs_find()] interface
** searches the list.  Neither the application code nor the VFS
** implementation should use the pNext pointer.
**
** The pNext field is the only field in the sqlite3_vfs
** structure that SQLite will ever modify.  SQLite will only access
** or modify this field while holding a particular static mutex.
** The application should never modify anything within the sqlite3_vfs
** object once the object has been registered.
**
** The zName field holds the name of the VFS module.  The name must
** be unique across all VFS modules.
**
** ^SQLite guarantees that the zFilename parameter to xOpen
** is either a NULL pointer or string obtained
** from xFullPathname() with an optional suffix added.
** ^If a suffix is added to the zFilename parameter, it will
** consist of a single "-" character followed by no more than
** 10 alphanumeric and/or "-" characters.
** ^SQLite further guarantees that
** the string will be valid and unchanged until xClose() is
** called. Because of the previous sentence,
** the [sqlite3_file] can safely store a pointer to the
** filename if it needs to remember the filename for some reason.
** If the zFilename parameter to xOpen is a NULL pointer then xOpen
** must invent its own temporary name for the file.  ^Whenever the 
** xFilename parameter is NULL it will also be the case that the
** flags parameter will include [SQLITE_OPEN_DELETEONCLOSE].
**
** The flags argument to xOpen() includes all bits set in
** the flags argument to [sqlite3_open_v2()].  Or if [sqlite3_open()]
** or [sqlite3_open16()] is used, then flags includes at least
** [SQLITE_OPEN_READWRITE] | [SQLITE_OPEN_CREATE]. 
** If xOpen() opens a file read-only then it sets *pOutFlags to
** include [SQLITE_OPEN_READONLY].  Other bits in *pOutFlags may be set.
**
** ^(SQLite will also add one of the following flags to the xOpen()
** call, depending on the object being opened:
**
** <ul>
** <li>  [SQLITE_OPEN_MAIN_DB]
** <li>  [SQLITE_OPEN_MAIN_JOURNAL]
** <li>  [SQLITE_OPEN_TEMP_DB]
** <li>  [SQLITE_OPEN_TEMP_JOURNAL]
** <li>  [SQLITE_OPEN_TRANSIENT_DB]
** <li>  [SQLITE_OPEN_SUBJOURNAL]
** <li>  [SQLITE_OPEN_MASTER_JOURNAL]
** <li>  [SQLITE_OPEN_WAL]
** </ul>)^
**
** The file I/O implementation can use the object type flags to
** change the way it deals with files.  For example, an application
** that does not care about crash recovery or rollback might make
** the open of a journal file a no-op.  Writes to this journal would
** also be no-ops, and any attempt to read the journal would return
** SQLITE_IOERR.  Or the implementation might recognize that a database
** file will be doing page-aligned sector reads and writes in a random
** order and set up its I/O subsystem accordingly.
**
** SQLite might also add one of the following flags to the xOpen method:
**
** <ul>
** <li> [SQLITE_OPEN_DELETEONCLOSE]
** <li> [SQLITE_OPEN_EXCLUSIVE]
** </ul>
**
** The [SQLITE_OPEN_DELETEONCLOSE] flag means the file should be
** deleted when it is closed.  ^The [SQLITE_OPEN_DELETEONCLOSE]
** will be set for TEMP databases and their journals, transient
** databases, and subjournals.
**
** ^The [SQLITE_OPEN_EXCLUSIVE] flag is always used in conjunction
** with the [SQLITE_OPEN_CREATE] flag, which are both directly
** analogous to the O_EXCL and O_CREAT flags of the POSIX open()
** API.  The SQLITE_OPEN_EXCLUSIVE flag, when paired with the 
** SQLITE_OPEN_CREATE, is used to indicate that file should always
** be created, and that it is an error if it already exists.
** It is <i>not</i> used to indicate the file should be opened 
** for exclusive access.
**
** ^At least szOsFile bytes of memory are allocated by SQLite
** to hold the  [sqlite3_file] structure passed as the third
** argument to xOpen.  The xOpen method does not have to
** allocate the structure; it should just fill it in.  Note that
** the xOpen method must set the sqlite3_file.pMethods to either
** a valid [sqlite3_io_methods] object or to NULL.  xOpen must do
** this even if the open fails.  SQLite expects that the sqlite3_file.pMethods
** element will be valid after xOpen returns regardless of the success
** or failure of the xOpen call.
**
** ^The flags argument to xAccess() may be [SQLITE_ACCESS_EXISTS]
** to test for the existence of a file, or [SQLITE_ACCESS_READWRITE] to
** test whether a file is readable and writable, or [SQLITE_ACCESS_READ]
** to test whether a file is at least readable.   The file can be a
** directory.
**
** ^SQLite will always allocate at least mxPathname+1 bytes for the
** output buffer xFullPathname.  The exact size of the output buffer
** is also passed as a parameter to both  methods. If the output buffer
** is not large enough, [SQLITE_CANTOPEN] should be returned. Since this is
** handled as a fatal error by SQLite, vfs implementations should endeavor
** to prevent this by setting mxPathname to a sufficiently large value.
**
** The xRandomness(), xSleep(), xCurrentTime(), and xCurrentTimeInt64()
** interfaces are not strictly a part of the filesystem, but they are
** included in the VFS structure for completeness.
** The xRandomness() function attempts to return nBytes bytes
** of good-quality randomness into zOut.  The return value is
** the actual number of bytes of randomness obtained.
** The xSleep() method causes the calling thread to sleep for at
** least the number of microseconds given.  ^The xCurrentTime()
** method returns a Julian Day Number for the current date and time as
** a floating point value.
** ^The xCurrentTimeInt64() method returns, as an integer, the Julian
** Day Number multipled by 86400000 (the number of milliseconds in 
** a 24-hour day).  
** ^SQLite will use the xCurrentTimeInt64() method to get the current
** date and time if that method is available (if iVersion is 2 or 
** greater and the function pointer is not NULL) and will fall back
** to xCurrentTime() if xCurrentTimeInt64() is unavailable.
*/
typedef struct sqlite3_vfs sqlite3_vfs;
struct sqlite3_vfs {
  int iVersion;            /* Structure version number (currently 2) */
  int szOsFile;            /* Size of subclassed sqlite3_file */
  int mxPathname;          /* Maximum file pathname length */
  sqlite3_vfs *pNext;      /* Next registered VFS */
  const char *zName;       /* Name of this virtual file system */
  void *pAppData;          /* Pointer to application-specific data */
  int (*xOpen)(sqlite3_vfs*, const char *zName, sqlite3_file*,
               int flags, int *pOutFlags);
  int (*xDelete)(sqlite3_vfs*, const char *zName, int syncDir);
  int (*xAccess)(sqlite3_vfs*, const char *zName, int flags, int *pResOut);
  int (*xFullPathname)(sqlite3_vfs*, const char *zName, int nOut, char *zOut);
  void *(*xDlOpen)(sqlite3_vfs*, const char *zFilename);
  void (*xDlError)(sqlite3_vfs*, int nByte, char *zErrMsg);
  void (*(*xDlSym)(sqlite3_vfs*,void*, const char *zSymbol))(void);
  void (*xDlClose)(sqlite3_vfs*, void*);
  int (*xRandomness)(sqlite3_vfs*, int nByte, char *zOut);
  int (*xSleep)(sqlite3_vfs*, int microseconds);
  int (*xCurrentTime)(sqlite3_vfs*, double*);
  int (*xGetLastError)(sqlite3_vfs*, int, char *);
  /*
  ** The methods above are in version 1 of the sqlite_vfs object
  ** definition.  Those that follow are added in version 2 or later
  */
  int (*xCurrentTimeInt64)(sqlite3_vfs*, sqlite3_int64*);
  /*
  ** The methods above are in versions 1 and 2 of the sqlite_vfs object.
  ** New fields may be appended in figure versions.  The iVersion
  ** value will increment whenever this happens. 
  */
};

/*
** CAPI3REF: Flags for the xAccess VFS method
**
** These integer constants can be used as the third parameter to
** the xAccess method of an [sqlite3_vfs] object.  They determine
** what kind of permissions the xAccess method is looking for.
** With SQLITE_ACCESS_EXISTS, the xAccess method
** simply checks whether the file exists.
** With SQLITE_ACCESS_READWRITE, the xAccess method
** checks whether the named directory is both readable and writable
** (in other words, if files can be added, removed, and renamed within
** the directory).
** The SQLITE_ACCESS_READWRITE constant is currently used only by the
** [temp_store_directory pragma], though this could change in a future
** release of SQLite.
** With SQLITE_ACCESS_READ, the xAccess method
** checks whether the file is readable.  The SQLITE_ACCESS_READ constant is
** currently unused, though it might be used in a future release of
** SQLite.
*/
#define SQLITE_ACCESS_EXISTS    0
#define SQLITE_ACCESS_READWRITE 1   /* Used by PRAGMA temp_store_directory */
#define SQLITE_ACCESS_READ      2   /* Unused */

/*
** CAPI3REF: Flags for the xShmLock VFS method
**
** These integer constants define the various locking operations
** allowed by the xShmLock method of [sqlite3_io_methods].  The
** following are the only legal combinations of flags to the
** xShmLock method:
**
** <ul>
** <li>  SQLITE_SHM_LOCK | SQLITE_SHM_SHARED
** <li>  SQLITE_SHM_LOCK | SQLITE_SHM_EXCLUSIVE
** <li>  SQLITE_SHM_UNLOCK | SQLITE_SHM_SHARED
** <li>  SQLITE_SHM_UNLOCK | SQLITE_SHM_EXCLUSIVE
** </ul>
**
** When unlocking, the same SHARED or EXCLUSIVE flag must be supplied as
** was given no the corresponding lock.  
**
** The xShmLock method can transition between unlocked and SHARED or
** between unlocked and EXCLUSIVE.  It cannot transition between SHARED
** and EXCLUSIVE.
*/
#define SQLITE_SHM_UNLOCK       1
#define SQLITE_SHM_LOCK         2
#define SQLITE_SHM_SHARED       4
#define SQLITE_SHM_EXCLUSIVE    8

/*
** CAPI3REF: Maximum xShmLock index
**
** The xShmLock method on [sqlite3_io_methods] may use values
** between 0 and this upper bound as its "offset" argument.
** The SQLite core will never attempt to acquire or release a
** lock outside of this range
*/
#define SQLITE_SHM_NLOCK        8


/*
** CAPI3REF: Memory Allocation Routines
**
** An instance of this object defines the interface between SQLite
** and low-level memory allocation routines.
**
** This object is used in only one place in the SQLite interface.
** A pointer to an instance of this object is the argument to
** [sqlite3_config()] when the configuration option is
** [SQLITE_CONFIG_MALLOC] or [SQLITE_CONFIG_GETMALLOC].  
** By creating an instance of this object
** and passing it to [sqlite3_config]([SQLITE_CONFIG_MALLOC])
** during configuration, an application can specify an alternative
** memory allocation subsystem for SQLite to use for all of its
** dynamic memory needs.
**
** Note that SQLite comes with several [built-in memory allocators]
** that are perfectly adequate for the overwhelming majority of applications
** and that this object is only useful to a tiny minority of applications
** with specialized memory allocation requirements.  This object is
** also used during testing of SQLite in order to specify an alternative
** memory allocator that simulates memory out-of-memory conditions in
** order to verify that SQLite recovers gracefully from such
** conditions.
**
** The xMalloc and xFree methods must work like the
** malloc() and free() functions from the standard C library.
** The xRealloc method must work like realloc() from the standard C library
** with the exception that if the second argument to xRealloc is zero,
** xRealloc must be a no-op - it must not perform any allocation or
** deallocation.  ^SQLite guarantees that the second argument to
** xRealloc is always a value returned by a prior call to xRoundup.
** And so in cases where xRoundup always returns a positive number,
** xRealloc can perform exactly as the standard library realloc() and
** still be in compliance with this specification.
**
** xSize should return the allocated size of a memory allocation
** previously obtained from xMalloc or xRealloc.  The allocated size
** is always at least as big as the requested size but may be larger.
**
** The xRoundup method returns what would be the allocated size of
** a memory allocation given a particular requested size.  Most memory
** allocators round up memory allocations at least to the next multiple
** of 8.  Some allocators round up to a larger multiple or to a power of 2.
** Every memory allocation request coming in through [sqlite3_malloc()]
** or [sqlite3_realloc()] first calls xRoundup.  If xRoundup returns 0, 
** that causes the corresponding memory allocation to fail.
**
** The xInit method initializes the memory allocator.  (For example,
** it might allocate any require mutexes or initialize internal data
** structures.  The xShutdown method is invoked (indirectly) by
** [sqlite3_shutdown()] and should deallocate any resources acquired
** by xInit.  The pAppData pointer is used as the only parameter to
** xInit and xShutdown.
**
** SQLite holds the [SQLITE_MUTEX_STATIC_MASTER] mutex when it invokes
** the xInit method, so the xInit method need not be threadsafe.  The
** xShutdown method is only called from [sqlite3_shutdown()] so it does
** not need to be threadsafe either.  For all other methods, SQLite
** holds the [SQLITE_MUTEX_STATIC_MEM] mutex as long as the
** [SQLITE_CONFIG_MEMSTATUS] configuration option is turned on (which
** it is by default) and so the methods are automatically serialized.
** However, if [SQLITE_CONFIG_MEMSTATUS] is disabled, then the other
** methods must be threadsafe or else make their own arrangements for
** serialization.
**
** SQLite will never invoke xInit() more than once without an intervening
** call to xShutdown().
*/
typedef struct sqlite3_mem_methods sqlite3_mem_methods;
struct sqlite3_mem_methods {
  void *(*xMalloc)(int);         /* Memory allocation function */
  void (*xFree)(void*);          /* Free a prior allocation */
  void *(*xRealloc)(void*,int);  /* Resize an allocation */
  int (*xSize)(void*);           /* Return the size of an allocation */
  int (*xRoundup)(int);          /* Round up request size to allocation size */
  int (*xInit)(void*);           /* Initialize the memory allocator */
  void (*xShutdown)(void*);      /* Deinitialize the memory allocator */
  void *pAppData;                /* Argument to xInit() and xShutdown() */
};

/*
** CAPI3REF: Configuration Options
**
** These constants are the available integer configuration options that
** can be passed as the first argument to the [sqlite3_config()] interface.
**
** New configuration options may be added in future releases of SQLite.
** Existing configuration options might be discontinued.  Applications
** should check the return code from [sqlite3_config()] to make sure that
** the call worked.  The [sqlite3_config()] interface will return a
** non-zero [error code] if a discontinued or unsupported configuration option
** is invoked.
**
** <dl>
** <dt>SQLITE_CONFIG_SINGLETHREAD</dt>
** <dd>There are no arguments to this option.  ^This option sets the
** [threading mode] to Single-thread.  In other words, it disables
** all mutexing and puts SQLite into a mode where it can only be used
** by a single thread.   ^If SQLite is compiled with
** the [SQLITE_THREADSAFE | SQLITE_THREADSAFE=0] compile-time option then
** it is not possible to change the [threading mode] from its default
** value of Single-thread and so [sqlite3_config()] will return 
** [SQLITE_ERROR] if called with the SQLITE_CONFIG_SINGLETHREAD
** configuration option.</dd>
**
** <dt>SQLITE_CONFIG_MULTITHREAD</dt>
** <dd>There are no arguments to this option.  ^This option sets the
** [threading mode] to Multi-thread.  In other words, it disables
** mutexing on [database connection] and [prepared statement] objects.
** The application is responsible for serializing access to
** [database connections] and [prepared statements].  But other mutexes
** are enabled so that SQLite will be safe to use in a multi-threaded
** environment as long as no two threads attempt to use the same
** [database connection] at the same time.  ^If SQLite is compiled with
** the [SQLITE_THREADSAFE | SQLITE_THREADSAFE=0] compile-time option then
** it is not possible to set the Multi-thread [threading mode] and
** [sqlite3_config()] will return [SQLITE_ERROR] if called with the
** SQLITE_CONFIG_MULTITHREAD configuration option.</dd>
**
** <dt>SQLITE_CONFIG_SERIALIZED</dt>
** <dd>There are no arguments to this option.  ^This option sets the
** [threading mode] to Serialized. In other words, this option enables
** all mutexes including the recursive
** mutexes on [database connection] and [prepared statement] objects.
** In this mode (which is the default when SQLite is compiled with
** [SQLITE_THREADSAFE=1]) the SQLite library will itself serialize access
** to [database connections] and [prepared statements] so that the
** application is free to use the same [database connection] or the
** same [prepared statement] in different threads at the same time.
** ^If SQLite is compiled with
** the [SQLITE_THREADSAFE | SQLITE_THREADSAFE=0] compile-time option then
** it is not possible to set the Serialized [threading mode] and
** [sqlite3_config()] will return [SQLITE_ERROR] if called with the
** SQLITE_CONFIG_SERIALIZED configuration option.</dd>
**
** <dt>SQLITE_CONFIG_MALLOC</dt>
** <dd> ^(This option takes a single argument which is a pointer to an
** instance of the [sqlite3_mem_methods] structure.  The argument specifies
** alternative low-level memory allocation routines to be used in place of
** the memory allocation routines built into SQLite.)^ ^SQLite makes
** its own private copy of the content of the [sqlite3_mem_methods] structure
** before the [sqlite3_config()] call returns.</dd>
**
** <dt>SQLITE_CONFIG_GETMALLOC</dt>
** <dd> ^(This option takes a single argument which is a pointer to an
** instance of the [sqlite3_mem_methods] structure.  The [sqlite3_mem_methods]
** structure is filled with the currently defined memory allocation routines.)^
** This option can be used to overload the default memory allocation
** routines with a wrapper that simulations memory allocation failure or
** tracks memory usage, for example. </dd>
**
** <dt>SQLITE_CONFIG_MEMSTATUS</dt>
** <dd> ^This option takes single argument of type int, interpreted as a 
** boolean, which enables or disables the collection of memory allocation 
** statistics. ^(When memory allocation statistics are disabled, the 
** following SQLite interfaces become non-operational:
**   <ul>
**   <li> [sqlite3_memory_used()]
**   <li> [sqlite3_memory_highwater()]
**   <li> [sqlite3_soft_heap_limit64()]
**   <li> [sqlite3_status()]
**   </ul>)^
** ^Memory allocation statistics are enabled by default unless SQLite is
** compiled with [SQLITE_DEFAULT_MEMSTATUS]=0 in which case memory
** allocation statistics are disabled by default.
** </dd>
**
** <dt>SQLITE_CONFIG_SCRATCH</dt>
** <dd> ^This option specifies a static memory buffer that SQLite can use for
** scratch memory.  There are three arguments:  A pointer an 8-byte
** aligned memory buffer from which the scrach allocations will be
** drawn, the size of each scratch allocation (sz),
** and the maximum number of scratch allocations (N).  The sz
** argument must be a multiple of 16.
** The first argument must be a pointer to an 8-byte aligned buffer
** of at least sz*N bytes of memory.
** ^SQLite will use no more than two scratch buffers per thread.  So
** N should be set to twice the expected maximum number of threads.
** ^SQLite will never require a scratch buffer that is more than 6
** times the database page size. ^If SQLite needs needs additional
** scratch memory beyond what is provided by this configuration option, then 
** [sqlite3_malloc()] will be used to obtain the memory needed.</dd>
**
** <dt>SQLITE_CONFIG_PAGECACHE</dt>
** <dd> ^This option specifies a static memory buffer that SQLite can use for
** the database page cache with the default page cache implemenation.  
** This configuration should not be used if an application-define page
** cache implementation is loaded using the SQLITE_CONFIG_PCACHE option.
** There are three arguments to this option: A pointer to 8-byte aligned
** memory, the size of each page buffer (sz), and the number of pages (N).
** The sz argument should be the size of the largest database page
** (a power of two between 512 and 32768) plus a little extra for each
** page header.  ^The page header size is 20 to 40 bytes depending on
** the host architecture.  ^It is harmless, apart from the wasted memory,
** to make sz a little too large.  The first
** argument should point to an allocation of at least sz*N bytes of memory.
** ^SQLite will use the memory provided by the first argument to satisfy its
** memory needs for the first N pages that it adds to cache.  ^If additional
** page cache memory is needed beyond what is provided by this option, then
** SQLite goes to [sqlite3_malloc()] for the additional storage space.
** The pointer in the first argument must
** be aligned to an 8-byte boundary or subsequent behavior of SQLite
** will be undefined.</dd>
**
** <dt>SQLITE_CONFIG_HEAP</dt>
** <dd> ^This option specifies a static memory buffer that SQLite will use
** for all of its dynamic memory allocation needs beyond those provided
** for by [SQLITE_CONFIG_SCRATCH] and [SQLITE_CONFIG_PAGECACHE].
** There are three arguments: An 8-byte aligned pointer to the memory,
** the number of bytes in the memory buffer, and the minimum allocation size.
** ^If the first pointer (the memory pointer) is NULL, then SQLite reverts
** to using its default memory allocator (the system malloc() implementation),
** undoing any prior invocation of [SQLITE_CONFIG_MALLOC].  ^If the
** memory pointer is not NULL and either [SQLITE_ENABLE_MEMSYS3] or
** [SQLITE_ENABLE_MEMSYS5] are defined, then the alternative memory
** allocator is engaged to handle all of SQLites memory allocation needs.
** The first pointer (the memory pointer) must be aligned to an 8-byte
** boundary or subsequent behavior of SQLite will be undefined.</dd>
**
** <dt>SQLITE_CONFIG_MUTEX</dt>
** <dd> ^(This option takes a single argument which is a pointer to an
** instance of the [sqlite3_mutex_methods] structure.  The argument specifies
** alternative low-level mutex routines to be used in place
** the mutex routines built into SQLite.)^  ^SQLite makes a copy of the
** content of the [sqlite3_mutex_methods] structure before the call to
** [sqlite3_config()] returns. ^If SQLite is compiled with
** the [SQLITE_THREADSAFE | SQLITE_THREADSAFE=0] compile-time option then
** the entire mutexing subsystem is omitted from the build and hence calls to
** [sqlite3_config()] with the SQLITE_CONFIG_MUTEX configuration option will
** return [SQLITE_ERROR].</dd>
**
** <dt>SQLITE_CONFIG_GETMUTEX</dt>
** <dd> ^(This option takes a single argument which is a pointer to an
** instance of the [sqlite3_mutex_methods] structure.  The
** [sqlite3_mutex_methods]
** structure is filled with the currently defined mutex routines.)^
** This option can be used to overload the default mutex allocation
** routines with a wrapper used to track mutex usage for performance
** profiling or testing, for example.   ^If SQLite is compiled with
** the [SQLITE_THREADSAFE | SQLITE_THREADSAFE=0] compile-time option then
** the entire mutexing subsystem is omitted from the build and hence calls to
** [sqlite3_config()] with the SQLITE_CONFIG_GETMUTEX configuration option will
** return [SQLITE_ERROR].</dd>
**
** <dt>SQLITE_CONFIG_LOOKASIDE</dt>
** <dd> ^(This option takes two arguments that determine the default
** memory allocation for the lookaside memory allocator on each
** [database connection].  The first argument is the
** size of each lookaside buffer slot and the second is the number of
** slots allocated to each database connection.)^  ^(This option sets the
** <i>default</i> lookaside size. The [SQLITE_DBCONFIG_LOOKASIDE]
** verb to [sqlite3_db_config()] can be used to change the lookaside
** configuration on individual connections.)^ </dd>
**
** <dt>SQLITE_CONFIG_PCACHE</dt>
** <dd> ^(This option takes a single argument which is a pointer to
** an [sqlite3_pcache_methods] object.  This object specifies the interface
** to a custom page cache implementation.)^  ^SQLite makes a copy of the
** object and uses it for page cache memory allocations.</dd>
**
** <dt>SQLITE_CONFIG_GETPCACHE</dt>
** <dd> ^(This option takes a single argument which is a pointer to an
** [sqlite3_pcache_methods] object.  SQLite copies of the current
** page cache implementation into that object.)^ </dd>
**
** <dt>SQLITE_CONFIG_LOG</dt>
** <dd> ^The SQLITE_CONFIG_LOG option takes two arguments: a pointer to a
** function with a call signature of void(*)(void*,int,const char*), 
** and a pointer to void. ^If the function pointer is not NULL, it is
** invoked by [sqlite3_log()] to process each logging event.  ^If the
** function pointer is NULL, the [sqlite3_log()] interface becomes a no-op.
** ^The void pointer that is the second argument to SQLITE_CONFIG_LOG is
** passed through as the first parameter to the application-defined logger
** function whenever that function is invoked.  ^The second parameter to
** the logger function is a copy of the first parameter to the corresponding
** [sqlite3_log()] call and is intended to be a [result code] or an
** [extended result code].  ^The third parameter passed to the logger is
** log message after formatting via [sqlite3_snprintf()].
** The SQLite logging interface is not reentrant; the logger function
** supplied by the application must not invoke any SQLite interface.
** In a multi-threaded application, the application-defined logger
** function must be threadsafe. </dd>
**
** </dl>
*/
#define SQLITE_CONFIG_SINGLETHREAD  1  /* nil */
#define SQLITE_CONFIG_MULTITHREAD   2  /* nil */
#define SQLITE_CONFIG_SERIALIZED    3  /* nil */
#define SQLITE_CONFIG_MALLOC        4  /* sqlite3_mem_methods* */
#define SQLITE_CONFIG_GETMALLOC     5  /* sqlite3_mem_methods* */
#define SQLITE_CONFIG_SCRATCH       6  /* void*, int sz, int N */
#define SQLITE_CONFIG_PAGECACHE     7  /* void*, int sz, int N */
#define SQLITE_CONFIG_HEAP          8  /* void*, int nByte, int min */
#define SQLITE_CONFIG_MEMSTATUS     9  /* boolean */
#define SQLITE_CONFIG_MUTEX        10  /* sqlite3_mutex_methods* */
#define SQLITE_CONFIG_GETMUTEX     11  /* sqlite3_mutex_methods* */
/* previously SQLITE_CONFIG_CHUNKALLOC 12 which is now unused. */ 
#define SQLITE_CONFIG_LOOKASIDE    13  /* int int */
#define SQLITE_CONFIG_PCACHE       14  /* sqlite3_pcache_methods* */
#define SQLITE_CONFIG_GETPCACHE    15  /* sqlite3_pcache_methods* */
#define SQLITE_CONFIG_LOG          16  /* xFunc, void* */

/*
** CAPI3REF: Database Connection Configuration Options
**
** These constants are the available integer configuration options that
** can be passed as the second argument to the [sqlite3_db_config()] interface.
**
** New configuration options may be added in future releases of SQLite.
** Existing configuration options might be discontinued.  Applications
** should check the return code from [sqlite3_db_config()] to make sure that
** the call worked.  ^The [sqlite3_db_config()] interface will return a
** non-zero [error code] if a discontinued or unsupported configuration option
** is invoked.
**
** <dl>
** <dt>SQLITE_DBCONFIG_LOOKASIDE</dt>
** <dd> ^This option takes three additional arguments that determine the 
** [lookaside memory allocator] configuration for the [database connection].
** ^The first argument (the third parameter to [sqlite3_db_config()] is a
** pointer to an memory buffer to use for lookaside memory.
** ^The first argument after the SQLITE_DBCONFIG_LOOKASIDE verb
** may be NULL in which case SQLite will allocate the
** lookaside buffer itself using [sqlite3_malloc()]. ^The second argument is the
** size of each lookaside buffer slot.  ^The third argument is the number of
** slots.  The size of the buffer in the first argument must be greater than
** or equal to the product of the second and third arguments.  The buffer
** must be aligned to an 8-byte boundary.  ^If the second argument to
** SQLITE_DBCONFIG_LOOKASIDE is not a multiple of 8, it is internally
** rounded down to the next smaller multiple of 8.  ^(The lookaside memory
** configuration for a database connection can only be changed when that
** connection is not currently using lookaside memory, or in other words
** when the "current value" returned by
** [sqlite3_db_status](D,[SQLITE_CONFIG_LOOKASIDE],...) is zero.
** Any attempt to change the lookaside memory configuration when lookaside
** memory is in use leaves the configuration unchanged and returns 
** [SQLITE_BUSY].)^</dd>
**
** </dl>
*/
#define SQLITE_DBCONFIG_LOOKASIDE    1001  /* void* int int */




/*
** CAPI3REF: Convenience Routines For Running Queries
**
** This is a legacy interface that is preserved for backwards compatibility.
** Use of this interface is not recommended.
**
** Definition: A <b>result table</b> is memory data structure created by the
** [sqlite3_get_table()] interface.  A result table records the
** complete query results from one or more queries.
**
** The table conceptually has a number of rows and columns.  But
** these numbers are not part of the result table itself.  These
** numbers are obtained separately.  Let N be the number of rows
** and M be the number of columns.
**
** A result table is an array of pointers to zero-terminated UTF-8 strings.
** There are (N+1)*M elements in the array.  The first M pointers point
** to zero-terminated strings that  contain the names of the columns.
** The remaining entries all point to query results.  NULL values result
** in NULL pointers.  All other values are in their UTF-8 zero-terminated
** string representation as returned by [sqlite3_column_text()].
**
** A result table might consist of one or more memory allocations.
** It is not safe to pass a result table directly to [sqlite3_free()].
** A result table should be deallocated using [sqlite3_free_table()].
**
** ^(As an example of the result table format, suppose a query result
** is as follows:
**
** <blockquote><pre>
**        Name        | Age
**        -----------------------
**        Alice       | 43
**        Bob         | 28
**        Cindy       | 21
** </pre></blockquote>
**
** There are two column (M==2) and three rows (N==3).  Thus the
** result table has 8 entries.  Suppose the result table is stored
** in an array names azResult.  Then azResult holds this content:
**
** <blockquote><pre>
**        azResult&#91;0] = "Name";
**        azResult&#91;1] = "Age";
**        azResult&#91;2] = "Alice";
**        azResult&#91;3] = "43";
**        azResult&#91;4] = "Bob";
**        azResult&#91;5] = "28";
**        azResult&#91;6] = "Cindy";
**        azResult&#91;7] = "21";
** </pre></blockquote>)^
**
** ^The sqlite3_get_table() function evaluates one or more
** semicolon-separated SQL statements in the zero-terminated UTF-8
** string of its 2nd parameter and returns a result table to the
** pointer given in its 3rd parameter.
**
** After the application has finished with the result from sqlite3_get_table(),
** it must pass the result table pointer to sqlite3_free_table() in order to
** release the memory that was malloced.  Because of the way the
** [sqlite3_malloc()] happens within sqlite3_get_table(), the calling
** function must not try to call [sqlite3_free()] directly.  Only
** [sqlite3_free_table()] is able to release the memory properly and safely.
**
** The sqlite3_get_table() interface is implemented as a wrapper around
** [sqlite3_exec()].  The sqlite3_get_table() routine does not have access
** to any internal data structures of SQLite.  It uses only the public
** interface defined here.  As a consequence, errors that occur in the
** wrapper layer outside of the internal [sqlite3_exec()] call are not
** reflected in subsequent calls to [sqlite3_errcode()] or
** [sqlite3_errmsg()].
*/
SQLITE_API int sqlite3_get_table(
  sqlite3 *db,          /* An open database */
  const char *zSql,     /* SQL to be evaluated */
  char ***pazResult,    /* Results of the query */
  int *pnRow,           /* Number of result rows written here */
  int *pnColumn,        /* Number of result columns written here */
  char **pzErrmsg       /* Error msg written here */
);
SQLITE_API void sqlite3_free_table(char **result);

/*
** CAPI3REF: Formatted String Printing Functions
**
** These routines are work-alikes of the "printf()" family of functions
** from the standard C library.
**
** ^The sqlite3_mprintf() and sqlite3_vmprintf() routines write their
** results into memory obtained from [sqlite3_malloc()].
** The strings returned by these two routines should be
** released by [sqlite3_free()].  ^Both routines return a
** NULL pointer if [sqlite3_malloc()] is unable to allocate enough
** memory to hold the resulting string.
**
** ^(The sqlite3_snprintf() routine is similar to "snprintf()" from
** the standard C library.  The result is written into the
** buffer supplied as the second parameter whose size is given by
** the first parameter. Note that the order of the
** first two parameters is reversed from snprintf().)^  This is an
** historical accident that cannot be fixed without breaking
** backwards compatibility.  ^(Note also that sqlite3_snprintf()
** returns a pointer to its buffer instead of the number of
** characters actually written into the buffer.)^  We admit that
** the number of characters written would be a more useful return
** value but we cannot change the implementation of sqlite3_snprintf()
** now without breaking compatibility.
**
** ^As long as the buffer size is greater than zero, sqlite3_snprintf()
** guarantees that the buffer is always zero-terminated.  ^The first
** parameter "n" is the total size of the buffer, including space for
** the zero terminator.  So the longest string that can be completely
** written will be n-1 characters.
**
** ^The sqlite3_vsnprintf() routine is a varargs version of sqlite3_snprintf().
**
** These routines all implement some additional formatting
** options that are useful for constructing SQL statements.
** All of the usual printf() formatting options apply.  In addition, there
** is are "%q", "%Q", and "%z" options.
**
** ^(The %q option works like %s in that it substitutes a null-terminated
** string from the argument list.  But %q also doubles every '\'' character.
** %q is designed for use inside a string literal.)^  By doubling each '\''
** character it escapes that character and allows it to be inserted into
** the string.
**
** For example, assume the string variable zText contains text as follows:
**
** <blockquote><pre>
**  char *zText = "It's a happy day!";
** </pre></blockquote>
**
** One can use this text in an SQL statement as follows:
**
** <blockquote><pre>
**  char *zSQL = sqlite3_mprintf("INSERT INTO table VALUES('%q')", zText);
**  sqlite3_exec(db, zSQL, 0, 0, 0);
**  sqlite3_free(zSQL);
** </pre></blockquote>
**
** Because the %q format string is used, the '\'' character in zText
** is escaped and the SQL generated is as follows:
**
** <blockquote><pre>
**  INSERT INTO table1 VALUES('It''s a happy day!')
** </pre></blockquote>
**
** This is correct.  Had we used %s instead of %q, the generated SQL
** would have looked like this:
**
** <blockquote><pre>
**  INSERT INTO table1 VALUES('It's a happy day!');
** </pre></blockquote>
**
** This second example is an SQL syntax error.  As a general rule you should
** always use %q instead of %s when inserting text into a string literal.
**
** ^(The %Q option works like %q except it also adds single quotes around
** the outside of the total string.  Additionally, if the parameter in the
** argument list is a NULL pointer, %Q substitutes the text "NULL" (without
** single quotes).)^  So, for example, one could say:
**
** <blockquote><pre>
**  char *zSQL = sqlite3_mprintf("INSERT INTO table VALUES(%Q)", zText);
**  sqlite3_exec(db, zSQL, 0, 0, 0);
**  sqlite3_free(zSQL);
** </pre></blockquote>
**
** The code above will render a correct SQL statement in the zSQL
** variable even if the zText variable is a NULL pointer.
**
** ^(The "%z" formatting option works like "%s" but with the
** addition that after the string has been read and copied into
** the result, [sqlite3_free()] is called on the input string.)^
*/
SQLITE_API char *sqlite3_mprintf(const char*,...);
SQLITE_API char *sqlite3_vmprintf(const char*, va_list);
SQLITE_API char *sqlite3_snprintf(int,char*,const char*, ...);
SQLITE_API char *sqlite3_vsnprintf(int,char*,const char*, va_list);

/*
** CAPI3REF: Memory Allocation Subsystem
**
** The SQLite core uses these three routines for all of its own
** internal memory allocation needs. "Core" in the previous sentence
** does not include operating-system specific VFS implementation.  The
** Windows VFS uses native malloc() and free() for some operations.
**
** ^The sqlite3_malloc() routine returns a pointer to a block
** of memory at least N bytes in length, where N is the parameter.
** ^If sqlite3_malloc() is unable to obtain sufficient free
** memory, it returns a NULL pointer.  ^If the parameter N to
** sqlite3_malloc() is zero or negative then sqlite3_malloc() returns
** a NULL pointer.
**
** ^Calling sqlite3_free() with a pointer previously returned
** by sqlite3_malloc() or sqlite3_realloc() releases that memory so
** that it might be reused.  ^The sqlite3_free() routine is
** a no-op if is called with a NULL pointer.  Passing a NULL pointer
** to sqlite3_free() is harmless.  After being freed, memory
** should neither be read nor written.  Even reading previously freed
** memory might result in a segmentation fault or other severe error.
** Memory corruption, a segmentation fault, or other severe error
** might result if sqlite3_free() is called with a non-NULL pointer that
** was not obtained from sqlite3_malloc() or sqlite3_realloc().
**
** ^(The sqlite3_realloc() interface attempts to resize a
** prior memory allocation to be at least N bytes, where N is the
** second parameter.  The memory allocation to be resized is the first
** parameter.)^ ^ If the first parameter to sqlite3_realloc()
** is a NULL pointer then its behavior is identical to calling
** sqlite3_malloc(N) where N is the second parameter to sqlite3_realloc().
** ^If the second parameter to sqlite3_realloc() is zero or
** negative then the behavior is exactly the same as calling
** sqlite3_free(P) where P is the first parameter to sqlite3_realloc().
** ^sqlite3_realloc() returns a pointer to a memory allocation
** of at least N bytes in size or NULL if sufficient memory is unavailable.
** ^If M is the size of the prior allocation, then min(N,M) bytes
** of the prior allocation are copied into the beginning of buffer returned
** by sqlite3_realloc() and the prior allocation is freed.
** ^If sqlite3_realloc() returns NULL, then the prior allocation
** is not freed.
**
** ^The memory returned by sqlite3_malloc() and sqlite3_realloc()
** is always aligned to at least an 8 byte boundary, or to a
** 4 byte boundary if the [SQLITE_4_BYTE_ALIGNED_MALLOC] compile-time
** option is used.
**
** In SQLite version 3.5.0 and 3.5.1, it was possible to define
** the SQLITE_OMIT_MEMORY_ALLOCATION which would cause the built-in
** implementation of these routines to be omitted.  That capability
** is no longer provided.  Only built-in memory allocators can be used.
**
** The Windows OS interface layer calls
** the system malloc() and free() directly when converting
** filenames between the UTF-8 encoding used by SQLite
** and whatever filename encoding is used by the particular Windows
** installation.  Memory allocation errors are detected, but
** they are reported back as [SQLITE_CANTOPEN] or
** [SQLITE_IOERR] rather than [SQLITE_NOMEM].
**
** The pointer arguments to [sqlite3_free()] and [sqlite3_realloc()]
** must be either NULL or else pointers obtained from a prior
** invocation of [sqlite3_malloc()] or [sqlite3_realloc()] that have
** not yet been released.
**
** The application must not read or write any part of
** a block of memory after it has been released using
** [sqlite3_free()] or [sqlite3_realloc()].
*/
SQLITE_API void *sqlite3_malloc(int);
SQLITE_API void *sqlite3_realloc(void*, int);
SQLITE_API void sqlite3_free(void*);


/*
** CAPI3REF: Authorizer Return Codes
**
** The [sqlite3_set_authorizer | authorizer callback function] must
** return either [SQLITE_OK] or one of these two constants in order
** to signal SQLite whether or not the action is permitted.  See the
** [sqlite3_set_authorizer | authorizer documentation] for additional
** information.
*/
#define SQLITE_DENY   1   /* Abort the SQL statement with an error */
#define SQLITE_IGNORE 2   /* Don't allow access, but don't generate an error */

/*
** CAPI3REF: Authorizer Action Codes
**
** The [sqlite3_set_authorizer()] interface registers a callback function
** that is invoked to authorize certain SQL statement actions.  The
** second parameter to the callback is an integer code that specifies
** what action is being authorized.  These are the integer action codes that
** the authorizer callback may be passed.
**
** These action code values signify what kind of operation is to be
** authorized.  The 3rd and 4th parameters to the authorization
** callback function will be parameters or NULL depending on which of these
** codes is used as the second parameter.  ^(The 5th parameter to the
** authorizer callback is the name of the database ("main", "temp",
** etc.) if applicable.)^  ^The 6th parameter to the authorizer callback
** is the name of the inner-most trigger or view that is responsible for
** the access attempt or NULL if this access attempt is directly from
** top-level SQL code.
*/
/******************************************* 3rd ************ 4th ***********/
#define SQLITE_CREATE_INDEX          1   /* Index Name      Table Name      */
#define SQLITE_CREATE_TABLE          2   /* Table Name      NULL            */
#define SQLITE_CREATE_TEMP_INDEX     3   /* Index Name      Table Name      */
#define SQLITE_CREATE_TEMP_TABLE     4   /* Table Name      NULL            */
#define SQLITE_CREATE_TEMP_TRIGGER   5   /* Trigger Name    Table Name      */
#define SQLITE_CREATE_TEMP_VIEW      6   /* View Name       NULL            */
#define SQLITE_CREATE_TRIGGER        7   /* Trigger Name    Table Name      */
#define SQLITE_CREATE_VIEW           8   /* View Name       NULL            */
#define SQLITE_DELETE                9   /* Table Name      NULL            */
#define SQLITE_DROP_INDEX           10   /* Index Name      Table Name      */
#define SQLITE_DROP_TABLE           11   /* Table Name      NULL            */
#define SQLITE_DROP_TEMP_INDEX      12   /* Index Name      Table Name      */
#define SQLITE_DROP_TEMP_TABLE      13   /* Table Name      NULL            */
#define SQLITE_DROP_TEMP_TRIGGER    14   /* Trigger Name    Table Name      */
#define SQLITE_DROP_TEMP_VIEW       15   /* View Name       NULL            */
#define SQLITE_DROP_TRIGGER         16   /* Trigger Name    Table Name      */
#define SQLITE_DROP_VIEW            17   /* View Name       NULL            */
#define SQLITE_INSERT               18   /* Table Name      NULL            */
#define SQLITE_PRAGMA               19   /* Pragma Name     1st arg or NULL */
#define SQLITE_READ                 20   /* Table Name      Column Name     */
#define SQLITE_SELECT               21   /* NULL            NULL            */
#define SQLITE_TRANSACTION          22   /* Operation       NULL            */
#define SQLITE_UPDATE               23   /* Table Name      Column Name     */
#define SQLITE_ATTACH               24   /* Filename        NULL            */
#define SQLITE_DETACH               25   /* Database Name   NULL            */
#define SQLITE_ALTER_TABLE          26   /* Database Name   Table Name      */
#define SQLITE_REINDEX              27   /* Index Name      NULL            */
#define SQLITE_ANALYZE              28   /* Table Name      NULL            */
#define SQLITE_CREATE_VTABLE        29   /* Table Name      Module Name     */
#define SQLITE_DROP_VTABLE          30   /* Table Name      Module Name     */
#define SQLITE_FUNCTION             31   /* NULL            Function Name   */
#define SQLITE_SAVEPOINT            32   /* Operation       Savepoint Name  */
#define SQLITE_COPY                  0   /* No longer used */


/*
** CAPI3REF: Opening A New Database Connection
**
** ^These routines open an SQLite database file whose name is given by the
** filename argument. ^The filename argument is interpreted as UTF-8 for
** sqlite3_open() and sqlite3_open_v2() and as UTF-16 in the native byte
** order for sqlite3_open16(). ^(A [database connection] handle is usually
** returned in *ppDb, even if an error occurs.  The only exception is that
** if SQLite is unable to allocate memory to hold the [sqlite3] object,
** a NULL will be written into *ppDb instead of a pointer to the [sqlite3]
** object.)^ ^(If the database is opened (and/or created) successfully, then
** [SQLITE_OK] is returned.  Otherwise an [error code] is returned.)^ ^The
** [sqlite3_errmsg()] or [sqlite3_errmsg16()] routines can be used to obtain
** an English language description of the error following a failure of any
** of the sqlite3_open() routines.
**
** ^The default encoding for the database will be UTF-8 if
** sqlite3_open() or sqlite3_open_v2() is called and
** UTF-16 in the native byte order if sqlite3_open16() is used.
**
** Whether or not an error occurs when it is opened, resources
** associated with the [database connection] handle should be released by
** passing it to [sqlite3_close()] when it is no longer required.
**
** The sqlite3_open_v2() interface works like sqlite3_open()
** except that it accepts two additional parameters for additional control
** over the new database connection.  ^(The flags parameter to
** sqlite3_open_v2() can take one of
** the following three values, optionally combined with the 
** [SQLITE_OPEN_NOMUTEX], [SQLITE_OPEN_FULLMUTEX], [SQLITE_OPEN_SHAREDCACHE],
** and/or [SQLITE_OPEN_PRIVATECACHE] flags:)^
**
** <dl>
** ^(<dt>[SQLITE_OPEN_READONLY]</dt>
** <dd>The database is opened in read-only mode.  If the database does not
** already exist, an error is returned.</dd>)^
**
** ^(<dt>[SQLITE_OPEN_READWRITE]</dt>
** <dd>The database is opened for reading and writing if possible, or reading
** only if the file is write protected by the operating system.  In either
** case the database must already exist, otherwise an error is returned.</dd>)^
**
** ^(<dt>[SQLITE_OPEN_READWRITE] | [SQLITE_OPEN_CREATE]</dt>
** <dd>The database is opened for reading and writing, and is created if
** it does not already exist. This is the behavior that is always used for
** sqlite3_open() and sqlite3_open16().</dd>)^
** </dl>
**
** If the 3rd parameter to sqlite3_open_v2() is not one of the
** combinations shown above or one of the combinations shown above combined
** with the [SQLITE_OPEN_NOMUTEX], [SQLITE_OPEN_FULLMUTEX],
** [SQLITE_OPEN_SHAREDCACHE] and/or [SQLITE_OPEN_PRIVATECACHE] flags,
** then the behavior is undefined.
**
** ^If the [SQLITE_OPEN_NOMUTEX] flag is set, then the database connection
** opens in the multi-thread [threading mode] as long as the single-thread
** mode has not been set at compile-time or start-time.  ^If the
** [SQLITE_OPEN_FULLMUTEX] flag is set then the database connection opens
** in the serialized [threading mode] unless single-thread was
** previously selected at compile-time or start-time.
** ^The [SQLITE_OPEN_SHAREDCACHE] flag causes the database connection to be
** eligible to use [shared cache mode], regardless of whether or not shared
** cache is enabled using [sqlite3_enable_shared_cache()].  ^The
** [SQLITE_OPEN_PRIVATECACHE] flag causes the database connection to not
** participate in [shared cache mode] even if it is enabled.
**
** ^If the filename is ":memory:", then a private, temporary in-memory database
** is created for the connection.  ^This in-memory database will vanish when
** the database connection is closed.  Future versions of SQLite might
** make use of additional special filenames that begin with the ":" character.
** It is recommended that when a database filename actually does begin with
** a ":" character you should prefix the filename with a pathname such as
** "./" to avoid ambiguity.
**
** ^If the filename is an empty string, then a private, temporary
** on-disk database will be created.  ^This private database will be
** automatically deleted as soon as the database connection is closed.
**
** ^The fourth parameter to sqlite3_open_v2() is the name of the
** [sqlite3_vfs] object that defines the operating system interface that
** the new database connection should use.  ^If the fourth parameter is
** a NULL pointer then the default [sqlite3_vfs] object is used.
**
** <b>Note to Windows users:</b>  The encoding used for the filename argument
** of sqlite3_open() and sqlite3_open_v2() must be UTF-8, not whatever
** codepage is currently defined.  Filenames containing international
** characters must be converted to UTF-8 prior to passing them into
** sqlite3_open() or sqlite3_open_v2().
*/
SQLITE_API int sqlite3_open16(
  const void *filename,   /* Database filename (UTF-16) */
  sqlite3 **ppDb          /* OUT: SQLite db handle */
);
SQLITE_API int sqlite3_open_v2(
  const char *filename,   /* Database filename (UTF-8) */
  sqlite3 **ppDb,         /* OUT: SQLite db handle */
  int flags,              /* Flags */
  const char *zVfs        /* Name of VFS module to use */
);

/*
** CAPI3REF: Error Codes And Messages
**
** ^The sqlite3_errcode() interface returns the numeric [result code] or
** [extended result code] for the most recent failed sqlite3_* API call
** associated with a [database connection]. If a prior API call failed
** but the most recent API call succeeded, the return value from
** sqlite3_errcode() is undefined.  ^The sqlite3_extended_errcode()
** interface is the same except that it always returns the 
** [extended result code] even when extended result codes are
** disabled.
**
** ^The sqlite3_errmsg() and sqlite3_errmsg16() return English-language
** text that describes the error, as either UTF-8 or UTF-16 respectively.
** ^(Memory to hold the error message string is managed internally.
** The application does not need to worry about freeing the result.
** However, the error string might be overwritten or deallocated by
** subsequent calls to other SQLite interface functions.)^
**
** When the serialized [threading mode] is in use, it might be the
** case that a second error occurs on a separate thread in between
** the time of the first error and the call to these interfaces.
** When that happens, the second error will be reported since these
** interfaces always report the most recent result.  To avoid
** this, each thread can obtain exclusive use of the [database connection] D
** by invoking [sqlite3_mutex_enter]([sqlite3_db_mutex](D)) before beginning
** to use D and invoking [sqlite3_mutex_leave]([sqlite3_db_mutex](D)) after
** all calls to the interfaces listed here are completed.
**
** If an interface fails with SQLITE_MISUSE, that means the interface
** was invoked incorrectly by the application.  In that case, the
** error code and message may or may not be set.
*/
SQLITE_API int sqlite3_errcode(sqlite3 *db);
SQLITE_API const void *sqlite3_errmsg16(sqlite3*);

/*
** CAPI3REF: SQL Statement Object
** KEYWORDS: {prepared statement} {prepared statements}
**
** An instance of this object represents a single SQL statement.
** This object is variously known as a "prepared statement" or a
** "compiled SQL statement" or simply as a "statement".
**
** The life of a statement object goes something like this:
**
** <ol>
** <li> Create the object using [sqlite3_prepare_v2()] or a related
**      function.
** <li> Bind values to [host parameters] using the sqlite3_bind_*()
**      interfaces.
** <li> Run the SQL by calling [sqlite3_step()] one or more times.
** <li> Reset the statement using [sqlite3_reset()] then go back
**      to step 2.  Do this zero or more times.
** <li> Destroy the object using [sqlite3_finalize()].
** </ol>
**
** Refer to documentation on individual methods above for additional
** information.
*/
typedef struct sqlite3_stmt sqlite3_stmt;

/*
** CAPI3REF: Run-Time Limit Categories
** KEYWORDS: {limit category} {*limit categories}
**
** These constants define various performance limits
** that can be lowered at run-time using [sqlite3_limit()].
** The synopsis of the meanings of the various limits is shown below.
** Additional information is available at [limits | Limits in SQLite].
**
** <dl>
** ^(<dt>SQLITE_LIMIT_LENGTH</dt>
** <dd>The maximum size of any string or BLOB or table row, in bytes.<dd>)^
**
** ^(<dt>SQLITE_LIMIT_SQL_LENGTH</dt>
** <dd>The maximum length of an SQL statement, in bytes.</dd>)^
**
** ^(<dt>SQLITE_LIMIT_COLUMN</dt>
** <dd>The maximum number of columns in a table definition or in the
** result set of a [SELECT] or the maximum number of columns in an index
** or in an ORDER BY or GROUP BY clause.</dd>)^
**
** ^(<dt>SQLITE_LIMIT_EXPR_DEPTH</dt>
** <dd>The maximum depth of the parse tree on any expression.</dd>)^
**
** ^(<dt>SQLITE_LIMIT_COMPOUND_SELECT</dt>
** <dd>The maximum number of terms in a compound SELECT statement.</dd>)^
**
** ^(<dt>SQLITE_LIMIT_VDBE_OP</dt>
** <dd>The maximum number of instructions in a virtual machine program
** used to implement an SQL statement.  This limit is not currently
** enforced, though that might be added in some future release of
** SQLite.</dd>)^
**
** ^(<dt>SQLITE_LIMIT_FUNCTION_ARG</dt>
** <dd>The maximum number of arguments on a function.</dd>)^
**
** ^(<dt>SQLITE_LIMIT_ATTACHED</dt>
** <dd>The maximum number of [ATTACH | attached databases].)^</dd>
**
** ^(<dt>SQLITE_LIMIT_LIKE_PATTERN_LENGTH</dt>
** <dd>The maximum length of the pattern argument to the [LIKE] or
** [GLOB] operators.</dd>)^
**
** ^(<dt>SQLITE_LIMIT_VARIABLE_NUMBER</dt>
** <dd>The maximum index number of any [parameter] in an SQL statement.)^
**
** ^(<dt>SQLITE_LIMIT_TRIGGER_DEPTH</dt>
** <dd>The maximum depth of recursion for triggers.</dd>)^
** </dl>
*/
#define SQLITE_LIMIT_LENGTH                    0
#define SQLITE_LIMIT_SQL_LENGTH                1
#define SQLITE_LIMIT_COLUMN                    2
#define SQLITE_LIMIT_EXPR_DEPTH                3
#define SQLITE_LIMIT_COMPOUND_SELECT           4
#define SQLITE_LIMIT_VDBE_OP                   5
#define SQLITE_LIMIT_FUNCTION_ARG              6
#define SQLITE_LIMIT_ATTACHED                  7
#define SQLITE_LIMIT_LIKE_PATTERN_LENGTH       8
#define SQLITE_LIMIT_VARIABLE_NUMBER           9
#define SQLITE_LIMIT_TRIGGER_DEPTH            10

/*
** CAPI3REF: Compiling An SQL Statement
** KEYWORDS: {SQL statement compiler}
**
** To execute an SQL query, it must first be compiled into a byte-code
** program using one of these routines.
**
** The first argument, "db", is a [database connection] obtained from a
** prior successful call to [sqlite3_open()], [sqlite3_open_v2()] or
** [sqlite3_open16()].  The database connection must not have been closed.
**
** The second argument, "zSql", is the statement to be compiled, encoded
** as either UTF-8 or UTF-16.  The sqlite3_prepare() and sqlite3_prepare_v2()
** interfaces use UTF-8, and sqlite3_prepare16() and sqlite3_prepare16_v2()
** use UTF-16.
**
** ^If the nByte argument is less than zero, then zSql is read up to the
** first zero terminator. ^If nByte is non-negative, then it is the maximum
** number of  bytes read from zSql.  ^When nByte is non-negative, the
** zSql string ends at either the first '\000' or '\u0000' character or
** the nByte-th byte, whichever comes first. If the caller knows
** that the supplied string is nul-terminated, then there is a small
** performance advantage to be gained by passing an nByte parameter that
** is equal to the number of bytes in the input string <i>including</i>
** the nul-terminator bytes.
**
** ^If pzTail is not NULL then *pzTail is made to point to the first byte
** past the end of the first SQL statement in zSql.  These routines only
** compile the first statement in zSql, so *pzTail is left pointing to
** what remains uncompiled.
**
** ^*ppStmt is left pointing to a compiled [prepared statement] that can be
** executed using [sqlite3_step()].  ^If there is an error, *ppStmt is set
** to NULL.  ^If the input text contains no SQL (if the input is an empty
** string or a comment) then *ppStmt is set to NULL.
** The calling procedure is responsible for deleting the compiled
** SQL statement using [sqlite3_finalize()] after it has finished with it.
** ppStmt may not be NULL.
**
** ^On success, the sqlite3_prepare() family of routines return [SQLITE_OK];
** otherwise an [error code] is returned.
**
** The sqlite3_prepare_v2() and sqlite3_prepare16_v2() interfaces are
** recommended for all new programs. The two older interfaces are retained
** for backwards compatibility, but their use is discouraged.
** ^In the "v2" interfaces, the prepared statement
** that is returned (the [sqlite3_stmt] object) contains a copy of the
** original SQL text. This causes the [sqlite3_step()] interface to
** behave differently in three ways:
**
** <ol>
** <li>
** ^If the database schema changes, instead of returning [SQLITE_SCHEMA] as it
** always used to do, [sqlite3_step()] will automatically recompile the SQL
** statement and try to run it again.
** </li>
**
** <li>
** ^When an error occurs, [sqlite3_step()] will return one of the detailed
** [error codes] or [extended error codes].  ^The legacy behavior was that
** [sqlite3_step()] would only return a generic [SQLITE_ERROR] result code
** and the application would have to make a second call to [sqlite3_reset()]
** in order to find the underlying cause of the problem. With the "v2" prepare
** interfaces, the underlying reason for the error is returned immediately.
** </li>
**
** <li>
** ^If the specific value bound to [parameter | host parameter] in the 
** WHERE clause might influence the choice of query plan for a statement,
** then the statement will be automatically recompiled, as if there had been 
** a schema change, on the first  [sqlite3_step()] call following any change
** to the [sqlite3_bind_text | bindings] of that [parameter]. 
** ^The specific value of WHERE-clause [parameter] might influence the 
** choice of query plan if the parameter is the left-hand side of a [LIKE]
** or [GLOB] operator or if the parameter is compared to an indexed column
** and the [SQLITE_ENABLE_STAT2] compile-time option is enabled.
** the 
** </li>
** </ol>
*/
SQLITE_API int sqlite3_prepare16(
  sqlite3 *db,            /* Database handle */
  const void *zSql,       /* SQL statement, UTF-16 encoded */
  int nByte,              /* Maximum length of zSql in bytes. */
  sqlite3_stmt **ppStmt,  /* OUT: Statement handle */
  const void **pzTail     /* OUT: Pointer to unused portion of zSql */
);
SQLITE_API int sqlite3_prepare16_v2(
  sqlite3 *db,            /* Database handle */
  const void *zSql,       /* SQL statement, UTF-16 encoded */
  int nByte,              /* Maximum length of zSql in bytes. */
  sqlite3_stmt **ppStmt,  /* OUT: Statement handle */
  const void **pzTail     /* OUT: Pointer to unused portion of zSql */
);

/*
** CAPI3REF: Retrieving Statement SQL
**
** ^This interface can be used to retrieve a saved copy of the original
** SQL text used to create a [prepared statement] if that statement was
** compiled using either [sqlite3_prepare_v2()] or [sqlite3_prepare16_v2()].
*/
SQLITE_API const char *sqlite3_sql(sqlite3_stmt *pStmt);

/*
** CAPI3REF: Determine If An SQL Statement Writes The Database
**
** ^The sqlite3_stmt_readonly(X) interface returns true (non-zero) if 
** and only if the [prepared statement] X makes no direct changes to
** the content of the database file.
**
** Note that [application-defined SQL functions] or
** [virtual tables] might change the database indirectly as a side effect.  
** ^(For example, if an application defines a function "eval()" that 
** calls [sqlite3_exec()], then the following SQL statement would
** change the database file through side-effects:
**
** <blockquote><pre>
**    SELECT eval('DELETE FROM t1') FROM t2;
** </pre></blockquote>
**
** But because the [SELECT] statement does not change the database file
** directly, sqlite3_stmt_readonly() would still return true.)^
**
** ^Transaction control statements such as [BEGIN], [COMMIT], [ROLLBACK],
** [SAVEPOINT], and [RELEASE] cause sqlite3_stmt_readonly() to return true,
** since the statements themselves do not actually modify the database but
** rather they control the timing of when other statements modify the 
** database.  ^The [ATTACH] and [DETACH] statements also cause
** sqlite3_stmt_readonly() to return true since, while those statements
** change the configuration of a database connection, they do not make 
** changes to the content of the database files on disk.
*/
SQLITE_API int sqlite3_stmt_readonly(sqlite3_stmt *pStmt);

/*
** CAPI3REF: Dynamically Typed Value Object
** KEYWORDS: {protected sqlite3_value} {unprotected sqlite3_value}
**
** SQLite uses the sqlite3_value object to represent all values
** that can be stored in a database table. SQLite uses dynamic typing
** for the values it stores.  ^Values stored in sqlite3_value objects
** can be integers, floating point values, strings, BLOBs, or NULL.
**
** An sqlite3_value object may be either "protected" or "unprotected".
** Some interfaces require a protected sqlite3_value.  Other interfaces
** will accept either a protected or an unprotected sqlite3_value.
** Every interface that accepts sqlite3_value arguments specifies
** whether or not it requires a protected sqlite3_value.
**
** The terms "protected" and "unprotected" refer to whether or not
** a mutex is held.  A internal mutex is held for a protected
** sqlite3_value object but no mutex is held for an unprotected
** sqlite3_value object.  If SQLite is compiled to be single-threaded
** (with [SQLITE_THREADSAFE=0] and with [sqlite3_threadsafe()] returning 0)
** or if SQLite is run in one of reduced mutex modes 
** [SQLITE_CONFIG_SINGLETHREAD] or [SQLITE_CONFIG_MULTITHREAD]
** then there is no distinction between protected and unprotected
** sqlite3_value objects and they can be used interchangeably.  However,
** for maximum code portability it is recommended that applications
** still make the distinction between protected and unprotected
** sqlite3_value objects even when not strictly required.
**
** ^The sqlite3_value objects that are passed as parameters into the
** implementation of [application-defined SQL functions] are protected.
** ^The sqlite3_value object returned by
** [sqlite3_column_value()] is unprotected.
** Unprotected sqlite3_value objects may only be used with
** [sqlite3_result_value()] and [sqlite3_bind_value()].
** The [sqlite3_value_blob | sqlite3_value_type()] family of
** interfaces require protected sqlite3_value objects.
*/
typedef struct Mem sqlite3_value;

/*
** CAPI3REF: SQL Function Context Object
**
** The context in which an SQL function executes is stored in an
** sqlite3_context object.  ^A pointer to an sqlite3_context object
** is always first parameter to [application-defined SQL functions].
** The application-defined SQL function implementation will pass this
** pointer through into calls to [sqlite3_result_int | sqlite3_result()],
** [sqlite3_aggregate_context()], [sqlite3_user_data()],
** [sqlite3_context_db_handle()], [sqlite3_get_auxdata()],
** and/or [sqlite3_set_auxdata()].
*/
typedef struct sqlite3_context sqlite3_context;

/*
** CAPI3REF: Binding Values To Prepared Statements
** KEYWORDS: {host parameter} {host parameters} {host parameter name}
** KEYWORDS: {SQL parameter} {SQL parameters} {parameter binding}
**
** ^(In the SQL statement text input to [sqlite3_prepare_v2()] and its variants,
** literals may be replaced by a [parameter] that matches one of following
** templates:
**
** <ul>
** <li>  ?
** <li>  ?NNN
** <li>  :VVV
** <li>  @VVV
** <li>  $VVV
** </ul>
**
** In the templates above, NNN represents an integer literal,
** and VVV represents an alphanumeric identifier.)^  ^The values of these
** parameters (also called "host parameter names" or "SQL parameters")
** can be set using the sqlite3_bind_*() routines defined here.
**
** ^The first argument to the sqlite3_bind_*() routines is always
** a pointer to the [sqlite3_stmt] object returned from
** [sqlite3_prepare_v2()] or its variants.
**
** ^The second argument is the index of the SQL parameter to be set.
** ^The leftmost SQL parameter has an index of 1.  ^When the same named
** SQL parameter is used more than once, second and subsequent
** occurrences have the same index as the first occurrence.
** ^The index for named parameters can be looked up using the
** [sqlite3_bind_parameter_index()] API if desired.  ^The index
** for "?NNN" parameters is the value of NNN.
** ^The NNN value must be between 1 and the [sqlite3_limit()]
** parameter [SQLITE_LIMIT_VARIABLE_NUMBER] (default value: 999).
**
** ^The third argument is the value to bind to the parameter.
**
** ^(In those routines that have a fourth argument, its value is the
** number of bytes in the parameter.  To be clear: the value is the
** number of <u>bytes</u> in the value, not the number of characters.)^
** ^If the fourth parameter is negative, the length of the string is
** the number of bytes up to the first zero terminator.
**
** ^The fifth argument to sqlite3_bind_blob(), sqlite3_bind_text(), and
** sqlite3_bind_text16() is a destructor used to dispose of the BLOB or
** string after SQLite has finished with it.  ^The destructor is called
** to dispose of the BLOB or string even if the call to sqlite3_bind_blob(),
** sqlite3_bind_text(), or sqlite3_bind_text16() fails.  
** ^If the fifth argument is
** the special value [SQLITE_STATIC], then SQLite assumes that the
** information is in static, unmanaged space and does not need to be freed.
** ^If the fifth argument has the value [SQLITE_TRANSIENT], then
** SQLite makes its own private copy of the data immediately, before
** the sqlite3_bind_*() routine returns.
**
** ^The sqlite3_bind_zeroblob() routine binds a BLOB of length N that
** is filled with zeroes.  ^A zeroblob uses a fixed amount of memory
** (just an integer to hold its size) while it is being processed.
** Zeroblobs are intended to serve as placeholders for BLOBs whose
** content is later written using
** [sqlite3_blob_open | incremental BLOB I/O] routines.
** ^A negative value for the zeroblob results in a zero-length BLOB.
**
** ^If any of the sqlite3_bind_*() routines are called with a NULL pointer
** for the [prepared statement] or with a prepared statement for which
** [sqlite3_step()] has been called more recently than [sqlite3_reset()],
** then the call will return [SQLITE_MISUSE].  If any sqlite3_bind_()
** routine is passed a [prepared statement] that has been finalized, the
** result is undefined and probably harmful.
**
** ^Bindings are not cleared by the [sqlite3_reset()] routine.
** ^Unbound parameters are interpreted as NULL.
**
** ^The sqlite3_bind_* routines return [SQLITE_OK] on success or an
** [error code] if anything goes wrong.
** ^[SQLITE_RANGE] is returned if the parameter
** index is out of range.  ^[SQLITE_NOMEM] is returned if malloc() fails.
**
** See also: [sqlite3_bind_parameter_count()],
** [sqlite3_bind_parameter_name()], and [sqlite3_bind_parameter_index()].
*/
SQLITE_API int sqlite3_bind_blob(sqlite3_stmt*, int, const void*, int n, void(*)(void*));
SQLITE_API int sqlite3_bind_double(sqlite3_stmt*, int, double);
SQLITE_API int sqlite3_bind_int(sqlite3_stmt*, int, int);
SQLITE_API int sqlite3_bind_int64(sqlite3_stmt*, int, sqlite3_int64);
SQLITE_API int sqlite3_bind_null(sqlite3_stmt*, int);
SQLITE_API int sqlite3_bind_text(sqlite3_stmt*, int, const char*, int n, void(*)(void*));
SQLITE_API int sqlite3_bind_text16(sqlite3_stmt*, int, const void*, int, void(*)(void*));
SQLITE_API int sqlite3_bind_value(sqlite3_stmt*, int, const sqlite3_value*);
SQLITE_API int sqlite3_bind_zeroblob(sqlite3_stmt*, int, int n);

/*
** CAPI3REF: Number Of SQL Parameters
**
** ^This routine can be used to find the number of [SQL parameters]
** in a [prepared statement].  SQL parameters are tokens of the
** form "?", "?NNN", ":AAA", "$AAA", or "@AAA" that serve as
** placeholders for values that are [sqlite3_bind_blob | bound]
** to the parameters at a later time.
**
** ^(This routine actually returns the index of the largest (rightmost)
** parameter. For all forms except ?NNN, this will correspond to the
** number of unique parameters.  If parameters of the ?NNN form are used,
** there may be gaps in the list.)^
**
** See also: [sqlite3_bind_blob|sqlite3_bind()],
** [sqlite3_bind_parameter_name()], and
** [sqlite3_bind_parameter_index()].
*/
SQLITE_API int sqlite3_bind_parameter_count(sqlite3_stmt*);

/*
** CAPI3REF: Name Of A Host Parameter
**
** ^The sqlite3_bind_parameter_name(P,N) interface returns
** the name of the N-th [SQL parameter] in the [prepared statement] P.
** ^(SQL parameters of the form "?NNN" or ":AAA" or "@AAA" or "$AAA"
** have a name which is the string "?NNN" or ":AAA" or "@AAA" or "$AAA"
** respectively.
** In other words, the initial ":" or "$" or "@" or "?"
** is included as part of the name.)^
** ^Parameters of the form "?" without a following integer have no name
** and are referred to as "nameless" or "anonymous parameters".
**
** ^The first host parameter has an index of 1, not 0.
**
** ^If the value N is out of range or if the N-th parameter is
** nameless, then NULL is returned.  ^The returned string is
** always in UTF-8 encoding even if the named parameter was
** originally specified as UTF-16 in [sqlite3_prepare16()] or
** [sqlite3_prepare16_v2()].
**
** See also: [sqlite3_bind_blob|sqlite3_bind()],
** [sqlite3_bind_parameter_count()], and
** [sqlite3_bind_parameter_index()].
*/
SQLITE_API const char *sqlite3_bind_parameter_name(sqlite3_stmt*, int);

/*
** CAPI3REF: Index Of A Parameter With A Given Name
**
** ^Return the index of an SQL parameter given its name.  ^The
** index value returned is suitable for use as the second
** parameter to [sqlite3_bind_blob|sqlite3_bind()].  ^A zero
** is returned if no matching parameter is found.  ^The parameter
** name must be given in UTF-8 even if the original statement
** was prepared from UTF-16 text using [sqlite3_prepare16_v2()].
**
** See also: [sqlite3_bind_blob|sqlite3_bind()],
** [sqlite3_bind_parameter_count()], and
** [sqlite3_bind_parameter_index()].
*/
SQLITE_API int sqlite3_bind_parameter_index(sqlite3_stmt*, const char *zName);

/*
** CAPI3REF: Reset All Bindings On A Prepared Statement
**
** ^Contrary to the intuition of many, [sqlite3_reset()] does not reset
** the [sqlite3_bind_blob | bindings] on a [prepared statement].
** ^Use this routine to reset all host parameters to NULL.
*/
SQLITE_API int sqlite3_clear_bindings(sqlite3_stmt*);

/*
** CAPI3REF: Number Of Columns In A Result Set
**
** ^Return the number of columns in the result set returned by the
** [prepared statement]. ^This routine returns 0 if pStmt is an SQL
** statement that does not return data (for example an [UPDATE]).
**
** See also: [sqlite3_data_count()]
*/
SQLITE_API int sqlite3_column_count(sqlite3_stmt *pStmt);

/*
** CAPI3REF: Column Names In A Result Set
**
** ^These routines return the name assigned to a particular column
** in the result set of a [SELECT] statement.  ^The sqlite3_column_name()
** interface returns a pointer to a zero-terminated UTF-8 string
** and sqlite3_column_name16() returns a pointer to a zero-terminated
** UTF-16 string.  ^The first parameter is the [prepared statement]
** that implements the [SELECT] statement. ^The second parameter is the
** column number.  ^The leftmost column is number 0.
**
** ^The returned string pointer is valid until either the [prepared statement]
** is destroyed by [sqlite3_finalize()] or until the next call to
** sqlite3_column_name() or sqlite3_column_name16() on the same column.
**
** ^If sqlite3_malloc() fails during the processing of either routine
** (for example during a conversion from UTF-8 to UTF-16) then a
** NULL pointer is returned.
**
** ^The name of a result column is the value of the "AS" clause for
** that column, if there is an AS clause.  If there is no AS clause
** then the name of the column is unspecified and may change from
** one release of SQLite to the next.
*/
SQLITE_API const void *sqlite3_column_name16(sqlite3_stmt*, int N);

/*
** CAPI3REF: Source Of Data In A Query Result
**
** ^These routines provide a means to determine the database, table, and
** table column that is the origin of a particular result column in
** [SELECT] statement.
** ^The name of the database or table or column can be returned as
** either a UTF-8 or UTF-16 string.  ^The _database_ routines return
** the database name, the _table_ routines return the table name, and
** the origin_ routines return the column name.
** ^The returned string is valid until the [prepared statement] is destroyed
** using [sqlite3_finalize()] or until the same information is requested
** again in a different encoding.
**
** ^The names returned are the original un-aliased names of the
** database, table, and column.
**
** ^The first argument to these interfaces is a [prepared statement].
** ^These functions return information about the Nth result column returned by
** the statement, where N is the second function argument.
** ^The left-most column is column 0 for these routines.
**
** ^If the Nth column returned by the statement is an expression or
** subquery and is not a column value, then all of these functions return
** NULL.  ^These routine might also return NULL if a memory allocation error
** occurs.  ^Otherwise, they return the name of the attached database, table,
** or column that query result column was extracted from.
**
** ^As with all other SQLite APIs, those whose names end with "16" return
** UTF-16 encoded strings and the other functions return UTF-8.
**
** ^These APIs are only available if the library was compiled with the
** [SQLITE_ENABLE_COLUMN_METADATA] C-preprocessor symbol.
**
** If two or more threads call one or more of these routines against the same
** prepared statement and column at the same time then the results are
** undefined.
**
** If two or more threads call one or more
** [sqlite3_column_database_name | column metadata interfaces]
** for the same [prepared statement] and result column
** at the same time then the results are undefined.
*/
SQLITE_API const void *sqlite3_column_database_name16(sqlite3_stmt*,int);
SQLITE_API const void *sqlite3_column_table_name16(sqlite3_stmt*,int);
SQLITE_API const void *sqlite3_column_origin_name16(sqlite3_stmt*,int);

/*
** CAPI3REF: Declared Datatype Of A Query Result
**
** ^(The first parameter is a [prepared statement].
** If this statement is a [SELECT] statement and the Nth column of the
** returned result set of that [SELECT] is a table column (not an
** expression or subquery) then the declared type of the table
** column is returned.)^  ^If the Nth column of the result set is an
** expression or subquery, then a NULL pointer is returned.
** ^The returned string is always UTF-8 encoded.
**
** ^(For example, given the database schema:
**
** CREATE TABLE t1(c1 VARIANT);
**
** and the following statement to be compiled:
**
** SELECT c1 + 1, c1 FROM t1;
**
** this routine would return the string "VARIANT" for the second result
** column (i==1), and a NULL pointer for the first result column (i==0).)^
**
** ^SQLite uses dynamic run-time typing.  ^So just because a column
** is declared to contain a particular type does not mean that the
** data stored in that column is of the declared type.  SQLite is
** strongly typed, but the typing is dynamic not static.  ^Type
** is associated with individual values, not with the containers
** used to hold those values.
*/
SQLITE_API const void *sqlite3_column_decltype16(sqlite3_stmt*,int);

/*
** CAPI3REF: Evaluate An SQL Statement
**
** After a [prepared statement] has been prepared using either
** [sqlite3_prepare_v2()] or [sqlite3_prepare16_v2()] or one of the legacy
** interfaces [sqlite3_prepare()] or [sqlite3_prepare16()], this function
** must be called one or more times to evaluate the statement.
**
** The details of the behavior of the sqlite3_step() interface depend
** on whether the statement was prepared using the newer "v2" interface
** [sqlite3_prepare_v2()] and [sqlite3_prepare16_v2()] or the older legacy
** interface [sqlite3_prepare()] and [sqlite3_prepare16()].  The use of the
** new "v2" interface is recommended for new applications but the legacy
** interface will continue to be supported.
**
** ^In the legacy interface, the return value will be either [SQLITE_BUSY],
** [SQLITE_DONE], [SQLITE_ROW], [SQLITE_ERROR], or [SQLITE_MISUSE].
** ^With the "v2" interface, any of the other [result codes] or
** [extended result codes] might be returned as well.
**
** ^[SQLITE_BUSY] means that the database engine was unable to acquire the
** database locks it needs to do its job.  ^If the statement is a [COMMIT]
** or occurs outside of an explicit transaction, then you can retry the
** statement.  If the statement is not a [COMMIT] and occurs within a
** explicit transaction then you should rollback the transaction before
** continuing.
**
** ^[SQLITE_DONE] means that the statement has finished executing
** successfully.  sqlite3_step() should not be called again on this virtual
** machine without first calling [sqlite3_reset()] to reset the virtual
** machine back to its initial state.
**
** ^If the SQL statement being executed returns any data, then [SQLITE_ROW]
** is returned each time a new row of data is ready for processing by the
** caller. The values may be accessed using the [column access functions].
** sqlite3_step() is called again to retrieve the next row of data.
**
** ^[SQLITE_ERROR] means that a run-time error (such as a constraint
** violation) has occurred.  sqlite3_step() should not be called again on
** the VM. More information may be found by calling [sqlite3_errmsg()].
** ^With the legacy interface, a more specific error code (for example,
** [SQLITE_INTERRUPT], [SQLITE_SCHEMA], [SQLITE_CORRUPT], and so forth)
** can be obtained by calling [sqlite3_reset()] on the
** [prepared statement].  ^In the "v2" interface,
** the more specific error code is returned directly by sqlite3_step().
**
** [SQLITE_MISUSE] means that the this routine was called inappropriately.
** Perhaps it was called on a [prepared statement] that has
** already been [sqlite3_finalize | finalized] or on one that had
** previously returned [SQLITE_ERROR] or [SQLITE_DONE].  Or it could
** be the case that the same database connection is being used by two or
** more threads at the same moment in time.
**
** For all versions of SQLite up to and including 3.6.23.1, a call to
** [sqlite3_reset()] was required after sqlite3_step() returned anything
** other than [SQLITE_ROW] before any subsequent invocation of
** sqlite3_step().  Failure to reset the prepared statement using 
** [sqlite3_reset()] would result in an [SQLITE_MISUSE] return from
** sqlite3_step().  But after version 3.6.23.1, sqlite3_step() began
** calling [sqlite3_reset()] automatically in this circumstance rather
** than returning [SQLITE_MISUSE].  This is not considered a compatibility
** break because any application that ever receives an SQLITE_MISUSE error
** is broken by definition.  The [SQLITE_OMIT_AUTORESET] compile-time option
** can be used to restore the legacy behavior.
**
** <b>Goofy Interface Alert:</b> In the legacy interface, the sqlite3_step()
** API always returns a generic error code, [SQLITE_ERROR], following any
** error other than [SQLITE_BUSY] and [SQLITE_MISUSE].  You must call
** [sqlite3_reset()] or [sqlite3_finalize()] in order to find one of the
** specific [error codes] that better describes the error.
** We admit that this is a goofy design.  The problem has been fixed
** with the "v2" interface.  If you prepare all of your SQL statements
** using either [sqlite3_prepare_v2()] or [sqlite3_prepare16_v2()] instead
** of the legacy [sqlite3_prepare()] and [sqlite3_prepare16()] interfaces,
** then the more specific [error codes] are returned directly
** by sqlite3_step().  The use of the "v2" interface is recommended.
*/
SQLITE_API int sqlite3_step(sqlite3_stmt*);

/*
** CAPI3REF: Number of columns in a result set
**
** ^The sqlite3_data_count(P) interface returns the number of columns in the
** current row of the result set of [prepared statement] P.
** ^If prepared statement P does not have results ready to return
** (via calls to the [sqlite3_column_int | sqlite3_column_*()] of
** interfaces) then sqlite3_data_count(P) returns 0.
** ^The sqlite3_data_count(P) routine also returns 0 if P is a NULL pointer.
**
** See also: [sqlite3_column_count()]
*/
SQLITE_API int sqlite3_data_count(sqlite3_stmt *pStmt);

/*
** CAPI3REF: Fundamental Datatypes
** KEYWORDS: SQLITE_TEXT
**
** ^(Every value in SQLite has one of five fundamental datatypes:
**
** <ul>
** <li> 64-bit signed integer
** <li> 64-bit IEEE floating point number
** <li> string
** <li> BLOB
** <li> NULL
** </ul>)^
**
** These constants are codes for each of those types.
**
** Note that the SQLITE_TEXT constant was also used in SQLite version 2
** for a completely different meaning.  Software that links against both
** SQLite version 2 and SQLite version 3 should use SQLITE3_TEXT, not
** SQLITE_TEXT.
*/
#define SQLITE_INTEGER  1
#define SQLITE_FLOAT    2
#define SQLITE_BLOB     4
#define SQLITE_NULL     5
#ifdef SQLITE_TEXT
# undef SQLITE_TEXT
#else
# define SQLITE_TEXT     3
#endif
#define SQLITE3_TEXT     3

/*
** CAPI3REF: Result Values From A Query
** KEYWORDS: {column access functions}
**
** These routines form the "result set" interface.
**
** ^These routines return information about a single column of the current
** result row of a query.  ^In every case the first argument is a pointer
** to the [prepared statement] that is being evaluated (the [sqlite3_stmt*]
** that was returned from [sqlite3_prepare_v2()] or one of its variants)
** and the second argument is the index of the column for which information
** should be returned. ^The leftmost column of the result set has the index 0.
** ^The number of columns in the result can be determined using
** [sqlite3_column_count()].
**
** If the SQL statement does not currently point to a valid row, or if the
** column index is out of range, the result is undefined.
** These routines may only be called when the most recent call to
** [sqlite3_step()] has returned [SQLITE_ROW] and neither
** [sqlite3_reset()] nor [sqlite3_finalize()] have been called subsequently.
** If any of these routines are called after [sqlite3_reset()] or
** [sqlite3_finalize()] or after [sqlite3_step()] has returned
** something other than [SQLITE_ROW], the results are undefined.
** If [sqlite3_step()] or [sqlite3_reset()] or [sqlite3_finalize()]
** are called from a different thread while any of these routines
** are pending, then the results are undefined.
**
** ^The sqlite3_column_type() routine returns the
** [SQLITE_INTEGER | datatype code] for the initial data type
** of the result column.  ^The returned value is one of [SQLITE_INTEGER],
** [SQLITE_FLOAT], [SQLITE_TEXT], [SQLITE_BLOB], or [SQLITE_NULL].  The value
** returned by sqlite3_column_type() is only meaningful if no type
** conversions have occurred as described below.  After a type conversion,
** the value returned by sqlite3_column_type() is undefined.  Future
** versions of SQLite may change the behavior of sqlite3_column_type()
** following a type conversion.
**
** ^If the result is a BLOB or UTF-8 string then the sqlite3_column_bytes()
** routine returns the number of bytes in that BLOB or string.
** ^If the result is a UTF-16 string, then sqlite3_column_bytes() converts
** the string to UTF-8 and then returns the number of bytes.
** ^If the result is a numeric value then sqlite3_column_bytes() uses
** [sqlite3_snprintf()] to convert that value to a UTF-8 string and returns
** the number of bytes in that string.
** ^If the result is NULL, then sqlite3_column_bytes() returns zero.
**
** ^If the result is a BLOB or UTF-16 string then the sqlite3_column_bytes16()
** routine returns the number of bytes in that BLOB or string.
** ^If the result is a UTF-8 string, then sqlite3_column_bytes16() converts
** the string to UTF-16 and then returns the number of bytes.
** ^If the result is a numeric value then sqlite3_column_bytes16() uses
** [sqlite3_snprintf()] to convert that value to a UTF-16 string and returns
** the number of bytes in that string.
** ^If the result is NULL, then sqlite3_column_bytes16() returns zero.
**
** ^The values returned by [sqlite3_column_bytes()] and 
** [sqlite3_column_bytes16()] do not include the zero terminators at the end
** of the string.  ^For clarity: the values returned by
** [sqlite3_column_bytes()] and [sqlite3_column_bytes16()] are the number of
** bytes in the string, not the number of characters.
**
** ^Strings returned by sqlite3_column_text() and sqlite3_column_text16(),
** even empty strings, are always zero terminated.  ^The return
** value from sqlite3_column_blob() for a zero-length BLOB is a NULL pointer.
**
** ^The object returned by [sqlite3_column_value()] is an
** [unprotected sqlite3_value] object.  An unprotected sqlite3_value object
** may only be used with [sqlite3_bind_value()] and [sqlite3_result_value()].
** If the [unprotected sqlite3_value] object returned by
** [sqlite3_column_value()] is used in any other way, including calls
** to routines like [sqlite3_value_int()], [sqlite3_value_text()],
** or [sqlite3_value_bytes()], then the behavior is undefined.
**
** These routines attempt to convert the value where appropriate.  ^For
** example, if the internal representation is FLOAT and a text result
** is requested, [sqlite3_snprintf()] is used internally to perform the
** conversion automatically.  ^(The following table details the conversions
** that are applied:
**
** <blockquote>
** <table border="1">
** <tr><th> Internal<br>Type <th> Requested<br>Type <th>  Conversion
**
** <tr><td>  NULL    <td> INTEGER   <td> Result is 0
** <tr><td>  NULL    <td>  FLOAT    <td> Result is 0.0
** <tr><td>  NULL    <td>   TEXT    <td> Result is NULL pointer
** <tr><td>  NULL    <td>   BLOB    <td> Result is NULL pointer
** <tr><td> INTEGER  <td>  FLOAT    <td> Convert from integer to float
** <tr><td> INTEGER  <td>   TEXT    <td> ASCII rendering of the integer
** <tr><td> INTEGER  <td>   BLOB    <td> Same as INTEGER->TEXT
** <tr><td>  FLOAT   <td> INTEGER   <td> Convert from float to integer
** <tr><td>  FLOAT   <td>   TEXT    <td> ASCII rendering of the float
** <tr><td>  FLOAT   <td>   BLOB    <td> Same as FLOAT->TEXT
** <tr><td>  TEXT    <td> INTEGER   <td> Use atoi()
** <tr><td>  TEXT    <td>  FLOAT    <td> Use atof()
** <tr><td>  TEXT    <td>   BLOB    <td> No change
** <tr><td>  BLOB    <td> INTEGER   <td> Convert to TEXT then use atoi()
** <tr><td>  BLOB    <td>  FLOAT    <td> Convert to TEXT then use atof()
** <tr><td>  BLOB    <td>   TEXT    <td> Add a zero terminator if needed
** </table>
** </blockquote>)^
**
** The table above makes reference to standard C library functions atoi()
** and atof().  SQLite does not really use these functions.  It has its
** own equivalent internal routines.  The atoi() and atof() names are
** used in the table for brevity and because they are familiar to most
** C programmers.
**
** Note that when type conversions occur, pointers returned by prior
** calls to sqlite3_column_blob(), sqlite3_column_text(), and/or
** sqlite3_column_text16() may be invalidated.
** Type conversions and pointer invalidations might occur
** in the following cases:
**
** <ul>
** <li> The initial content is a BLOB and sqlite3_column_text() or
**      sqlite3_column_text16() is called.  A zero-terminator might
**      need to be added to the string.</li>
** <li> The initial content is UTF-8 text and sqlite3_column_bytes16() or
**      sqlite3_column_text16() is called.  The content must be converted
**      to UTF-16.</li>
** <li> The initial content is UTF-16 text and sqlite3_column_bytes() or
**      sqlite3_column_text() is called.  The content must be converted
**      to UTF-8.</li>
** </ul>
**
** ^Conversions between UTF-16be and UTF-16le are always done in place and do
** not invalidate a prior pointer, though of course the content of the buffer
** that the prior pointer references will have been modified.  Other kinds
** of conversion are done in place when it is possible, but sometimes they
** are not possible and in those cases prior pointers are invalidated.
**
** The safest and easiest to remember policy is to invoke these routines
** in one of the following ways:
**
** <ul>
**  <li>sqlite3_column_text() followed by sqlite3_column_bytes()</li>
**  <li>sqlite3_column_blob() followed by sqlite3_column_bytes()</li>
**  <li>sqlite3_column_text16() followed by sqlite3_column_bytes16()</li>
** </ul>
**
** In other words, you should call sqlite3_column_text(),
** sqlite3_column_blob(), or sqlite3_column_text16() first to force the result
** into the desired format, then invoke sqlite3_column_bytes() or
** sqlite3_column_bytes16() to find the size of the result.  Do not mix calls
** to sqlite3_column_text() or sqlite3_column_blob() with calls to
** sqlite3_column_bytes16(), and do not mix calls to sqlite3_column_text16()
** with calls to sqlite3_column_bytes().
**
** ^The pointers returned are valid until a type conversion occurs as
** described above, or until [sqlite3_step()] or [sqlite3_reset()] or
** [sqlite3_finalize()] is called.  ^The memory space used to hold strings
** and BLOBs is freed automatically.  Do <b>not</b> pass the pointers returned
** [sqlite3_column_blob()], [sqlite3_column_text()], etc. into
** [sqlite3_free()].
**
** ^(If a memory allocation error occurs during the evaluation of any
** of these routines, a default value is returned.  The default value
** is either the integer 0, the floating point number 0.0, or a NULL
** pointer.  Subsequent calls to [sqlite3_errcode()] will return
** [SQLITE_NOMEM].)^
*/
SQLITE_API const void *sqlite3_column_blob(sqlite3_stmt*, int iCol);
SQLITE_API int sqlite3_column_bytes(sqlite3_stmt*, int iCol);
SQLITE_API int sqlite3_column_bytes16(sqlite3_stmt*, int iCol);
SQLITE_API double sqlite3_column_double(sqlite3_stmt*, int iCol);
SQLITE_API int sqlite3_column_int(sqlite3_stmt*, int iCol);
SQLITE_API sqlite3_int64 sqlite3_column_int64(sqlite3_stmt*, int iCol);
SQLITE_API const unsigned char *sqlite3_column_text(sqlite3_stmt*, int iCol);
SQLITE_API const void *sqlite3_column_text16(sqlite3_stmt*, int iCol);
SQLITE_API int sqlite3_column_type(sqlite3_stmt*, int iCol);
SQLITE_API sqlite3_value *sqlite3_column_value(sqlite3_stmt*, int iCol);

/*
** CAPI3REF: Destroy A Prepared Statement Object
**
** ^The sqlite3_finalize() function is called to delete a [prepared statement].
** ^If the most recent evaluation of the statement encountered no errors or
** or if the statement is never been evaluated, then sqlite3_finalize() returns
** SQLITE_OK.  ^If the most recent evaluation of statement S failed, then
** sqlite3_finalize(S) returns the appropriate [error code] or
** [extended error code].
**
** ^The sqlite3_finalize(S) routine can be called at any point during
** the life cycle of [prepared statement] S:
** before statement S is ever evaluated, after
** one or more calls to [sqlite3_reset()], or after any call
** to [sqlite3_step()] regardless of whether or not the statement has
** completed execution.
**
** ^Invoking sqlite3_finalize() on a NULL pointer is a harmless no-op.
**
** The application must finalize every [prepared statement] in order to avoid
** resource leaks.  It is a grievous error for the application to try to use
** a prepared statement after it has been finalized.  Any use of a prepared
** statement after it has been finalized can result in undefined and
** undesirable behavior such as segfaults and heap corruption.
*/
SQLITE_API int sqlite3_finalize(sqlite3_stmt *pStmt);

/*
** CAPI3REF: Reset A Prepared Statement Object
**
** The sqlite3_reset() function is called to reset a [prepared statement]
** object back to its initial state, ready to be re-executed.
** ^Any SQL statement variables that had values bound to them using
** the [sqlite3_bind_blob | sqlite3_bind_*() API] retain their values.
** Use [sqlite3_clear_bindings()] to reset the bindings.
**
** ^The [sqlite3_reset(S)] interface resets the [prepared statement] S
** back to the beginning of its program.
**
** ^If the most recent call to [sqlite3_step(S)] for the
** [prepared statement] S returned [SQLITE_ROW] or [SQLITE_DONE],
** or if [sqlite3_step(S)] has never before been called on S,
** then [sqlite3_reset(S)] returns [SQLITE_OK].
**
** ^If the most recent call to [sqlite3_step(S)] for the
** [prepared statement] S indicated an error, then
** [sqlite3_reset(S)] returns an appropriate [error code].
**
** ^The [sqlite3_reset(S)] interface does not change the values
** of any [sqlite3_bind_blob|bindings] on the [prepared statement] S.
*/
SQLITE_API int sqlite3_reset(sqlite3_stmt *pStmt);



/*
** CAPI3REF: Text Encodings
**
** These constant define integer codes that represent the various
** text encodings supported by SQLite.
*/
#define SQLITE_UTF8           1
#define SQLITE_UTF16LE        2
#define SQLITE_UTF16BE        3
#define SQLITE_UTF16          4    /* Use native byte order */
#define SQLITE_ANY            5    /* sqlite3_create_function only */
#define SQLITE_UTF16_ALIGNED  8    /* sqlite3_create_collation only */


/*
** CAPI3REF: Constants Defining Special Destructor Behavior
**
** These are special values for the destructor that is passed in as the
** final argument to routines like [sqlite3_result_blob()].  ^If the destructor
** argument is SQLITE_STATIC, it means that the content pointer is constant
** and will never change.  It does not need to be destroyed.  ^The
** SQLITE_TRANSIENT value means that the content will likely change in
** the near future and that SQLite should make its own private copy of
** the content before returning.
**
** The typedef is necessary to work around problems in certain
** C++ compilers.  See ticket #2191.
*/
typedef void (*sqlite3_destructor_type)(void*);
#define SQLITE_STATIC      ((sqlite3_destructor_type)0)
#define SQLITE_TRANSIENT   ((sqlite3_destructor_type)-1)

/*
** CAPI3REF: Setting The Result Of An SQL Function
**
** These routines are used by the xFunc or xFinal callbacks that
** implement SQL functions and aggregates.  See
** [sqlite3_create_function()] and [sqlite3_create_function16()]
** for additional information.
**
** These functions work very much like the [parameter binding] family of
** functions used to bind values to host parameters in prepared statements.
** Refer to the [SQL parameter] documentation for additional information.
**
** ^The sqlite3_result_blob() interface sets the result from
** an application-defined function to be the BLOB whose content is pointed
** to by the second parameter and which is N bytes long where N is the
** third parameter.
**
** ^The sqlite3_result_zeroblob() interfaces set the result of
** the application-defined function to be a BLOB containing all zero
** bytes and N bytes in size, where N is the value of the 2nd parameter.
**
** ^The sqlite3_result_double() interface sets the result from
** an application-defined function to be a floating point value specified
** by its 2nd argument.
**
** ^The sqlite3_result_error() and sqlite3_result_error16() functions
** cause the implemented SQL function to throw an exception.
** ^SQLite uses the string pointed to by the
** 2nd parameter of sqlite3_result_error() or sqlite3_result_error16()
** as the text of an error message.  ^SQLite interprets the error
** message string from sqlite3_result_error() as UTF-8. ^SQLite
** interprets the string from sqlite3_result_error16() as UTF-16 in native
** byte order.  ^If the third parameter to sqlite3_result_error()
** or sqlite3_result_error16() is negative then SQLite takes as the error
** message all text up through the first zero character.
** ^If the third parameter to sqlite3_result_error() or
** sqlite3_result_error16() is non-negative then SQLite takes that many
** bytes (not characters) from the 2nd parameter as the error message.
** ^The sqlite3_result_error() and sqlite3_result_error16()
** routines make a private copy of the error message text before
** they return.  Hence, the calling function can deallocate or
** modify the text after they return without harm.
** ^The sqlite3_result_error_code() function changes the error code
** returned by SQLite as a result of an error in a function.  ^By default,
** the error code is SQLITE_ERROR.  ^A subsequent call to sqlite3_result_error()
** or sqlite3_result_error16() resets the error code to SQLITE_ERROR.
**
** ^The sqlite3_result_toobig() interface causes SQLite to throw an error
** indicating that a string or BLOB is too long to represent.
**
** ^The sqlite3_result_nomem() interface causes SQLite to throw an error
** indicating that a memory allocation failed.
**
** ^The sqlite3_result_int() interface sets the return value
** of the application-defined function to be the 32-bit signed integer
** value given in the 2nd argument.
** ^The sqlite3_result_int64() interface sets the return value
** of the application-defined function to be the 64-bit signed integer
** value given in the 2nd argument.
**
** ^The sqlite3_result_null() interface sets the return value
** of the application-defined function to be NULL.
**
** ^The sqlite3_result_text(), sqlite3_result_text16(),
** sqlite3_result_text16le(), and sqlite3_result_text16be() interfaces
** set the return value of the application-defined function to be
** a text string which is represented as UTF-8, UTF-16 native byte order,
** UTF-16 little endian, or UTF-16 big endian, respectively.
** ^SQLite takes the text result from the application from
** the 2nd parameter of the sqlite3_result_text* interfaces.
** ^If the 3rd parameter to the sqlite3_result_text* interfaces
** is negative, then SQLite takes result text from the 2nd parameter
** through the first zero character.
** ^If the 3rd parameter to the sqlite3_result_text* interfaces
** is non-negative, then as many bytes (not characters) of the text
** pointed to by the 2nd parameter are taken as the application-defined
** function result.
** ^If the 4th parameter to the sqlite3_result_text* interfaces
** or sqlite3_result_blob is a non-NULL pointer, then SQLite calls that
** function as the destructor on the text or BLOB result when it has
** finished using that result.
** ^If the 4th parameter to the sqlite3_result_text* interfaces or to
** sqlite3_result_blob is the special constant SQLITE_STATIC, then SQLite
** assumes that the text or BLOB result is in constant space and does not
** copy the content of the parameter nor call a destructor on the content
** when it has finished using that result.
** ^If the 4th parameter to the sqlite3_result_text* interfaces
** or sqlite3_result_blob is the special constant SQLITE_TRANSIENT
** then SQLite makes a copy of the result into space obtained from
** from [sqlite3_malloc()] before it returns.
**
** ^The sqlite3_result_value() interface sets the result of
** the application-defined function to be a copy the
** [unprotected sqlite3_value] object specified by the 2nd parameter.  ^The
** sqlite3_result_value() interface makes a copy of the [sqlite3_value]
** so that the [sqlite3_value] specified in the parameter may change or
** be deallocated after sqlite3_result_value() returns without harm.
** ^A [protected sqlite3_value] object may always be used where an
** [unprotected sqlite3_value] object is required, so either
** kind of [sqlite3_value] object can be used with this interface.
**
** If these routines are called from within the different thread
** than the one containing the application-defined function that received
** the [sqlite3_context] pointer, the results are undefined.
*/
SQLITE_API void sqlite3_result_error16(sqlite3_context*, const void*, int);

/*
** The interface to the virtual-table mechanism is currently considered
** to be experimental.  The interface might change in incompatible ways.
** If this is a problem for you, do not use the interface at this time.
**
** When the virtual-table mechanism stabilizes, we will declare the
** interface fixed, support it indefinitely, and remove this comment.
*/

/*
** Structures used by the virtual table interface
*/
typedef struct sqlite3_vtab sqlite3_vtab;
typedef struct sqlite3_index_info sqlite3_index_info;
typedef struct sqlite3_vtab_cursor sqlite3_vtab_cursor;
typedef struct sqlite3_module sqlite3_module;

/*
** CAPI3REF: Virtual Table Object
** KEYWORDS: sqlite3_module {virtual table module}
**
** This structure, sometimes called a a "virtual table module", 
** defines the implementation of a [virtual tables].  
** This structure consists mostly of methods for the module.
**
** ^A virtual table module is created by filling in a persistent
** instance of this structure and passing a pointer to that instance
** to [sqlite3_create_module()] or [sqlite3_create_module_v2()].
** ^The registration remains valid until it is replaced by a different
** module or until the [database connection] closes.  The content
** of this structure must not change while it is registered with
** any database connection.
*/
struct sqlite3_module {
  int iVersion;
  int (*xCreate)(sqlite3*, void *pAux,
               int argc, const char *const*argv,
               sqlite3_vtab **ppVTab, char**);
  int (*xConnect)(sqlite3*, void *pAux,
               int argc, const char *const*argv,
               sqlite3_vtab **ppVTab, char**);
  int (*xBestIndex)(sqlite3_vtab *pVTab, sqlite3_index_info*);
  int (*xDisconnect)(sqlite3_vtab *pVTab);
  int (*xDestroy)(sqlite3_vtab *pVTab);
  int (*xOpen)(sqlite3_vtab *pVTab, sqlite3_vtab_cursor **ppCursor);
  int (*xClose)(sqlite3_vtab_cursor*);
  int (*xFilter)(sqlite3_vtab_cursor*, int idxNum, const char *idxStr,
                int argc, sqlite3_value **argv);
  int (*xNext)(sqlite3_vtab_cursor*);
  int (*xEof)(sqlite3_vtab_cursor*);
  int (*xColumn)(sqlite3_vtab_cursor*, sqlite3_context*, int);
  int (*xRowid)(sqlite3_vtab_cursor*, sqlite3_int64 *pRowid);
  int (*xUpdate)(sqlite3_vtab *, int, sqlite3_value **, sqlite3_int64 *);
  int (*xBegin)(sqlite3_vtab *pVTab);
  int (*xSync)(sqlite3_vtab *pVTab);
  int (*xCommit)(sqlite3_vtab *pVTab);
  int (*xRollback)(sqlite3_vtab *pVTab);
  int (*xFindFunction)(sqlite3_vtab *pVtab, int nArg, const char *zName,
                       void (**pxFunc)(sqlite3_context*,int,sqlite3_value**),
                       void **ppArg);
  int (*xRename)(sqlite3_vtab *pVtab, const char *zNew);
};

/*
** CAPI3REF: Virtual Table Indexing Information
** KEYWORDS: sqlite3_index_info
**
** The sqlite3_index_info structure and its substructures is used as part
** of the [virtual table] interface to
** pass information into and receive the reply from the [xBestIndex]
** method of a [virtual table module].  The fields under **Inputs** are the
** inputs to xBestIndex and are read-only.  xBestIndex inserts its
** results into the **Outputs** fields.
**
** ^(The aConstraint[] array records WHERE clause constraints of the form:
**
** <blockquote>column OP expr</blockquote>
**
** where OP is =, &lt;, &lt;=, &gt;, or &gt;=.)^  ^(The particular operator is
** stored in aConstraint[].op using one of the
** [SQLITE_INDEX_CONSTRAINT_EQ | SQLITE_INDEX_CONSTRAINT_ values].)^
** ^(The index of the column is stored in
** aConstraint[].iColumn.)^  ^(aConstraint[].usable is TRUE if the
** expr on the right-hand side can be evaluated (and thus the constraint
** is usable) and false if it cannot.)^
**
** ^The optimizer automatically inverts terms of the form "expr OP column"
** and makes other simplifications to the WHERE clause in an attempt to
** get as many WHERE clause terms into the form shown above as possible.
** ^The aConstraint[] array only reports WHERE clause terms that are
** relevant to the particular virtual table being queried.
**
** ^Information about the ORDER BY clause is stored in aOrderBy[].
** ^Each term of aOrderBy records a column of the ORDER BY clause.
**
** The [xBestIndex] method must fill aConstraintUsage[] with information
** about what parameters to pass to xFilter.  ^If argvIndex>0 then
** the right-hand side of the corresponding aConstraint[] is evaluated
** and becomes the argvIndex-th entry in argv.  ^(If aConstraintUsage[].omit
** is true, then the constraint is assumed to be fully handled by the
** virtual table and is not checked again by SQLite.)^
**
** ^The idxNum and idxPtr values are recorded and passed into the
** [xFilter] method.
** ^[sqlite3_free()] is used to free idxPtr if and only if
** needToFreeIdxPtr is true.
**
** ^The orderByConsumed means that output from [xFilter]/[xNext] will occur in
** the correct order to satisfy the ORDER BY clause so that no separate
** sorting step is required.
**
** ^The estimatedCost value is an estimate of the cost of doing the
** particular lookup.  A full scan of a table with N entries should have
** a cost of N.  A binary search of a table of N entries should have a
** cost of approximately log(N).
*/
struct sqlite3_index_info {
  /* Inputs */
  int nConstraint;           /* Number of entries in aConstraint */
  struct sqlite3_index_constraint {
     int iColumn;              /* Column on left-hand side of constraint */
     unsigned char op;         /* Constraint operator */
     unsigned char usable;     /* True if this constraint is usable */
     int iTermOffset;          /* Used internally - xBestIndex should ignore */
  } *aConstraint;            /* Table of WHERE clause constraints */
  int nOrderBy;              /* Number of terms in the ORDER BY clause */
  struct sqlite3_index_orderby {
     int iColumn;              /* Column number */
     unsigned char desc;       /* True for DESC.  False for ASC. */
  } *aOrderBy;               /* The ORDER BY clause */
  /* Outputs */
  struct sqlite3_index_constraint_usage {
    int argvIndex;           /* if >0, constraint is part of argv to xFilter */
    unsigned char omit;      /* Do not code a test for this constraint */
  } *aConstraintUsage;
  int idxNum;                /* Number used to identify the index */
  char *idxStr;              /* String, possibly obtained from sqlite3_malloc */
  int needToFreeIdxStr;      /* Free idxStr using sqlite3_free() if true */
  int orderByConsumed;       /* True if output is already ordered */
  double estimatedCost;      /* Estimated cost of using this index */
};

/*
** CAPI3REF: Virtual Table Constraint Operator Codes
**
** These macros defined the allowed values for the
** [sqlite3_index_info].aConstraint[].op field.  Each value represents
** an operator that is part of a constraint term in the wHERE clause of
** a query that uses a [virtual table].
*/
#define SQLITE_INDEX_CONSTRAINT_EQ    2
#define SQLITE_INDEX_CONSTRAINT_GT    4
#define SQLITE_INDEX_CONSTRAINT_LE    8
#define SQLITE_INDEX_CONSTRAINT_LT    16
#define SQLITE_INDEX_CONSTRAINT_GE    32
#define SQLITE_INDEX_CONSTRAINT_MATCH 64

/*
** CAPI3REF: Virtual Table Instance Object
** KEYWORDS: sqlite3_vtab
**
** Every [virtual table module] implementation uses a subclass
** of this object to describe a particular instance
** of the [virtual table].  Each subclass will
** be tailored to the specific needs of the module implementation.
** The purpose of this superclass is to define certain fields that are
** common to all module implementations.
**
** ^Virtual tables methods can set an error message by assigning a
** string obtained from [sqlite3_mprintf()] to zErrMsg.  The method should
** take care that any prior string is freed by a call to [sqlite3_free()]
** prior to assigning a new string to zErrMsg.  ^After the error message
** is delivered up to the client application, the string will be automatically
** freed by sqlite3_free() and the zErrMsg field will be zeroed.
*/
struct sqlite3_vtab {
  const sqlite3_module *pModule;  /* The module for this virtual table */
  int nRef;                       /* NO LONGER USED */
  char *zErrMsg;                  /* Error message from sqlite3_mprintf() */
  /* Virtual table implementations will typically add additional fields */
};

/*
** CAPI3REF: Virtual Table Cursor Object
** KEYWORDS: sqlite3_vtab_cursor {virtual table cursor}
**
** Every [virtual table module] implementation uses a subclass of the
** following structure to describe cursors that point into the
** [virtual table] and are used
** to loop through the virtual table.  Cursors are created using the
** [sqlite3_module.xOpen | xOpen] method of the module and are destroyed
** by the [sqlite3_module.xClose | xClose] method.  Cursors are used
** by the [xFilter], [xNext], [xEof], [xColumn], and [xRowid] methods
** of the module.  Each module implementation will define
** the content of a cursor structure to suit its own needs.
**
** This superclass exists in order to define fields of the cursor that
** are common to all implementations.
*/
struct sqlite3_vtab_cursor {
  sqlite3_vtab *pVtab;      /* Virtual table of this cursor */
  /* Virtual table implementations will typically add additional fields */
};


/*
** The interface to the virtual-table mechanism defined above (back up
** to a comment remarkably similar to this one) is currently considered
** to be experimental.  The interface might change in incompatible ways.
** If this is a problem for you, do not use the interface at this time.
**
** When the virtual-table mechanism stabilizes, we will declare the
** interface fixed, support it indefinitely, and remove this comment.
*/

/*
** CAPI3REF: A Handle To An Open BLOB
** KEYWORDS: {BLOB handle} {BLOB handles}
**
** An instance of this object represents an open BLOB on which
** [sqlite3_blob_open | incremental BLOB I/O] can be performed.
** ^Objects of this type are created by [sqlite3_blob_open()]
** and destroyed by [sqlite3_blob_close()].
** ^The [sqlite3_blob_read()] and [sqlite3_blob_write()] interfaces
** can be used to read or write small subsections of the BLOB.
** ^The [sqlite3_blob_bytes()] interface returns the size of the BLOB in bytes.
*/
typedef struct sqlite3_blob sqlite3_blob;


/*
** CAPI3REF: Mutex Methods Object
**
** An instance of this structure defines the low-level routines
** used to allocate and use mutexes.
**
** Usually, the default mutex implementations provided by SQLite are
** sufficient, however the user has the option of substituting a custom
** implementation for specialized deployments or systems for which SQLite
** does not provide a suitable implementation. In this case, the user
** creates and populates an instance of this structure to pass
** to sqlite3_config() along with the [SQLITE_CONFIG_MUTEX] option.
** Additionally, an instance of this structure can be used as an
** output variable when querying the system for the current mutex
** implementation, using the [SQLITE_CONFIG_GETMUTEX] option.
**
** ^The xMutexInit method defined by this structure is invoked as
** part of system initialization by the sqlite3_initialize() function.
** ^The xMutexInit routine is called by SQLite exactly once for each
** effective call to [sqlite3_initialize()].
**
** ^The xMutexEnd method defined by this structure is invoked as
** part of system shutdown by the sqlite3_shutdown() function. The
** implementation of this method is expected to release all outstanding
** resources obtained by the mutex methods implementation, especially
** those obtained by the xMutexInit method.  ^The xMutexEnd()
** interface is invoked exactly once for each call to [sqlite3_shutdown()].
**
** ^(The remaining seven methods defined by this structure (xMutexAlloc,
** xMutexFree, xMutexEnter, xMutexTry, xMutexLeave, xMutexHeld and
** xMutexNotheld) implement the following interfaces (respectively):
**
** <ul>
**   <li>  [sqlite3_mutex_alloc()] </li>
**   <li>  [sqlite3_mutex_free()] </li>
**   <li>  [sqlite3_mutex_enter()] </li>
**   <li>  [sqlite3_mutex_try()] </li>
**   <li>  [sqlite3_mutex_leave()] </li>
**   <li>  [sqlite3_mutex_held()] </li>
**   <li>  [sqlite3_mutex_notheld()] </li>
** </ul>)^
**
** The only difference is that the public sqlite3_XXX functions enumerated
** above silently ignore any invocations that pass a NULL pointer instead
** of a valid mutex handle. The implementations of the methods defined
** by this structure are not required to handle this case, the results
** of passing a NULL pointer instead of a valid mutex handle are undefined
** (i.e. it is acceptable to provide an implementation that segfaults if
** it is passed a NULL pointer).
**
** The xMutexInit() method must be threadsafe.  ^It must be harmless to
** invoke xMutexInit() multiple times within the same process and without
** intervening calls to xMutexEnd().  Second and subsequent calls to
** xMutexInit() must be no-ops.
**
** ^xMutexInit() must not use SQLite memory allocation ([sqlite3_malloc()]
** and its associates).  ^Similarly, xMutexAlloc() must not use SQLite memory
** allocation for a static mutex.  ^However xMutexAlloc() may use SQLite
** memory allocation for a fast or recursive mutex.
**
** ^SQLite will invoke the xMutexEnd() method when [sqlite3_shutdown()] is
** called, but only if the prior call to xMutexInit returned SQLITE_OK.
** If xMutexInit fails in any way, it is expected to clean up after itself
** prior to returning.
*/
typedef struct sqlite3_mutex_methods sqlite3_mutex_methods;
struct sqlite3_mutex_methods {
  int (*xMutexInit)(void);
  int (*xMutexEnd)(void);
  sqlite3_mutex *(*xMutexAlloc)(int);
  void (*xMutexFree)(sqlite3_mutex *);
  void (*xMutexEnter)(sqlite3_mutex *);
  int (*xMutexTry)(sqlite3_mutex *);
  void (*xMutexLeave)(sqlite3_mutex *);
  int (*xMutexHeld)(sqlite3_mutex *);
  int (*xMutexNotheld)(sqlite3_mutex *);
};


/*
** CAPI3REF: Mutex Types
**
** The [sqlite3_mutex_alloc()] interface takes a single argument
** which is one of these integer constants.
**
** The set of static mutexes may change from one SQLite release to the
** next.  Applications that override the built-in mutex logic must be
** prepared to accommodate additional static mutexes.
*/
#define SQLITE_MUTEX_FAST             0
#define SQLITE_MUTEX_RECURSIVE        1
#define SQLITE_MUTEX_STATIC_MASTER    2
#define SQLITE_MUTEX_STATIC_MEM       3  /* sqlite3_malloc() */
#define SQLITE_MUTEX_STATIC_MEM2      4  /* NOT USED */
#define SQLITE_MUTEX_STATIC_OPEN      4  /* sqlite3BtreeOpen() */
#define SQLITE_MUTEX_STATIC_PRNG      5  /* sqlite3_random() */
#define SQLITE_MUTEX_STATIC_LRU       6  /* lru page list */
#define SQLITE_MUTEX_STATIC_LRU2      7  /* NOT USED */
#define SQLITE_MUTEX_STATIC_PMEM      7  /* sqlite3PageMalloc() */


/*
** CAPI3REF: Testing Interface Operation Codes
**
** These constants are the valid operation code parameters used
** as the first argument to [sqlite3_test_control()].
**
** These parameters and their meanings are subject to change
** without notice.  These values are for testing purposes only.
** Applications should not use any of these parameters or the
** [sqlite3_test_control()] interface.
*/
#define SQLITE_TESTCTRL_FIRST                    5
#define SQLITE_TESTCTRL_PRNG_SAVE                5
#define SQLITE_TESTCTRL_PRNG_RESTORE             6
#define SQLITE_TESTCTRL_PRNG_RESET               7
#define SQLITE_TESTCTRL_BITVEC_TEST              8
#define SQLITE_TESTCTRL_FAULT_INSTALL            9
#define SQLITE_TESTCTRL_BENIGN_MALLOC_HOOKS     10
#define SQLITE_TESTCTRL_PENDING_BYTE            11
#define SQLITE_TESTCTRL_ASSERT                  12
#define SQLITE_TESTCTRL_ALWAYS                  13
#define SQLITE_TESTCTRL_RESERVE                 14
#define SQLITE_TESTCTRL_OPTIMIZATIONS           15
#define SQLITE_TESTCTRL_ISKEYWORD               16
#define SQLITE_TESTCTRL_PGHDRSZ                 17
#define SQLITE_TESTCTRL_SCRATCHMALLOC           18
#define SQLITE_TESTCTRL_LAST                    18


/*
** CAPI3REF: Status Parameters
**
** These integer constants designate various run-time status parameters
** that can be returned by [sqlite3_status()].
**
** <dl>
** ^(<dt>SQLITE_STATUS_MEMORY_USED</dt>
** <dd>This parameter is the current amount of memory checked out
** using [sqlite3_malloc()], either directly or indirectly.  The
** figure includes calls made to [sqlite3_malloc()] by the application
** and internal memory usage by the SQLite library.  Scratch memory
** controlled by [SQLITE_CONFIG_SCRATCH] and auxiliary page-cache
** memory controlled by [SQLITE_CONFIG_PAGECACHE] is not included in
** this parameter.  The amount returned is the sum of the allocation
** sizes as reported by the xSize method in [sqlite3_mem_methods].</dd>)^
**
** ^(<dt>SQLITE_STATUS_MALLOC_SIZE</dt>
** <dd>This parameter records the largest memory allocation request
** handed to [sqlite3_malloc()] or [sqlite3_realloc()] (or their
** internal equivalents).  Only the value returned in the
** *pHighwater parameter to [sqlite3_status()] is of interest.  
** The value written into the *pCurrent parameter is undefined.</dd>)^
**
** ^(<dt>SQLITE_STATUS_MALLOC_COUNT</dt>
** <dd>This parameter records the number of separate memory allocations
** currently checked out.</dd>)^
**
** ^(<dt>SQLITE_STATUS_PAGECACHE_USED</dt>
** <dd>This parameter returns the number of pages used out of the
** [pagecache memory allocator] that was configured using 
** [SQLITE_CONFIG_PAGECACHE].  The
** value returned is in pages, not in bytes.</dd>)^
**
** ^(<dt>SQLITE_STATUS_PAGECACHE_OVERFLOW</dt>
** <dd>This parameter returns the number of bytes of page cache
** allocation which could not be satisfied by the [SQLITE_CONFIG_PAGECACHE]
** buffer and where forced to overflow to [sqlite3_malloc()].  The
** returned value includes allocations that overflowed because they
** where too large (they were larger than the "sz" parameter to
** [SQLITE_CONFIG_PAGECACHE]) and allocations that overflowed because
** no space was left in the page cache.</dd>)^
**
** ^(<dt>SQLITE_STATUS_PAGECACHE_SIZE</dt>
** <dd>This parameter records the largest memory allocation request
** handed to [pagecache memory allocator].  Only the value returned in the
** *pHighwater parameter to [sqlite3_status()] is of interest.  
** The value written into the *pCurrent parameter is undefined.</dd>)^
**
** ^(<dt>SQLITE_STATUS_SCRATCH_USED</dt>
** <dd>This parameter returns the number of allocations used out of the
** [scratch memory allocator] configured using
** [SQLITE_CONFIG_SCRATCH].  The value returned is in allocations, not
** in bytes.  Since a single thread may only have one scratch allocation
** outstanding at time, this parameter also reports the number of threads
** using scratch memory at the same time.</dd>)^
**
** ^(<dt>SQLITE_STATUS_SCRATCH_OVERFLOW</dt>
** <dd>This parameter returns the number of bytes of scratch memory
** allocation which could not be satisfied by the [SQLITE_CONFIG_SCRATCH]
** buffer and where forced to overflow to [sqlite3_malloc()].  The values
** returned include overflows because the requested allocation was too
** larger (that is, because the requested allocation was larger than the
** "sz" parameter to [SQLITE_CONFIG_SCRATCH]) and because no scratch buffer
** slots were available.
** </dd>)^
**
** ^(<dt>SQLITE_STATUS_SCRATCH_SIZE</dt>
** <dd>This parameter records the largest memory allocation request
** handed to [scratch memory allocator].  Only the value returned in the
** *pHighwater parameter to [sqlite3_status()] is of interest.  
** The value written into the *pCurrent parameter is undefined.</dd>)^
**
** ^(<dt>SQLITE_STATUS_PARSER_STACK</dt>
** <dd>This parameter records the deepest parser stack.  It is only
** meaningful if SQLite is compiled with [YYTRACKMAXSTACKDEPTH].</dd>)^
** </dl>
**
** New status parameters may be added from time to time.
*/
#define SQLITE_STATUS_MEMORY_USED          0
#define SQLITE_STATUS_PAGECACHE_USED       1
#define SQLITE_STATUS_PAGECACHE_OVERFLOW   2
#define SQLITE_STATUS_SCRATCH_USED         3
#define SQLITE_STATUS_SCRATCH_OVERFLOW     4
#define SQLITE_STATUS_MALLOC_SIZE          5
#define SQLITE_STATUS_PARSER_STACK         6
#define SQLITE_STATUS_PAGECACHE_SIZE       7
#define SQLITE_STATUS_SCRATCH_SIZE         8
#define SQLITE_STATUS_MALLOC_COUNT         9


/*
** CAPI3REF: Status Parameters for database connections
**
** These constants are the available integer "verbs" that can be passed as
** the second argument to the [sqlite3_db_status()] interface.
**
** New verbs may be added in future releases of SQLite. Existing verbs
** might be discontinued. Applications should check the return code from
** [sqlite3_db_status()] to make sure that the call worked.
** The [sqlite3_db_status()] interface will return a non-zero error code
** if a discontinued or unsupported verb is invoked.
**
** <dl>
** ^(<dt>SQLITE_DBSTATUS_LOOKASIDE_USED</dt>
** <dd>This parameter returns the number of lookaside memory slots currently
** checked out.</dd>)^
**
** ^(<dt>SQLITE_DBSTATUS_LOOKASIDE_HIT</dt>
** <dd>This parameter returns the number malloc attempts that were 
** satisfied using lookaside memory. Only the high-water value is meaningful;
** the current value is always zero.
** checked out.</dd>)^
**
** ^(<dt>SQLITE_DBSTATUS_LOOKASIDE_MISS_SIZE</dt>
** <dd>This parameter returns the number malloc attempts that might have
** been satisfied using lookaside memory but failed due to the amount of
** memory requested being larger than the lookaside slot size.
** Only the high-water value is meaningful;
** the current value is always zero.
** checked out.</dd>)^
**
** ^(<dt>SQLITE_DBSTATUS_LOOKASIDE_MISS_FULL</dt>
** <dd>This parameter returns the number malloc attempts that might have
** been satisfied using lookaside memory but failed due to all lookaside
** memory already being in use.
** Only the high-water value is meaningful;
** the current value is always zero.
** checked out.</dd>)^
**
** ^(<dt>SQLITE_DBSTATUS_CACHE_USED</dt>
** <dd>This parameter returns the approximate number of of bytes of heap
** memory used by all pager caches associated with the database connection.)^
** ^The highwater mark associated with SQLITE_DBSTATUS_CACHE_USED is always 0.
**
** ^(<dt>SQLITE_DBSTATUS_SCHEMA_USED</dt>
** <dd>This parameter returns the approximate number of of bytes of heap
** memory used to store the schema for all databases associated
** with the connection - main, temp, and any [ATTACH]-ed databases.)^ 
** ^The full amount of memory used by the schemas is reported, even if the
** schema memory is shared with other database connections due to
** [shared cache mode] being enabled.
** ^The highwater mark associated with SQLITE_DBSTATUS_SCHEMA_USED is always 0.
**
** ^(<dt>SQLITE_DBSTATUS_STMT_USED</dt>
** <dd>This parameter returns the approximate number of of bytes of heap
** and lookaside memory used by all prepared statements associated with
** the database connection.)^
** ^The highwater mark associated with SQLITE_DBSTATUS_STMT_USED is always 0.
** </dd>
** </dl>
*/
#define SQLITE_DBSTATUS_LOOKASIDE_USED       0
#define SQLITE_DBSTATUS_CACHE_USED           1
#define SQLITE_DBSTATUS_SCHEMA_USED          2
#define SQLITE_DBSTATUS_STMT_USED            3
#define SQLITE_DBSTATUS_LOOKASIDE_HIT        4
#define SQLITE_DBSTATUS_LOOKASIDE_MISS_SIZE  5
#define SQLITE_DBSTATUS_LOOKASIDE_MISS_FULL  6
#define SQLITE_DBSTATUS_MAX                  6   /* Largest defined DBSTATUS */


/*
** CAPI3REF: Status Parameters for prepared statements
**
** These preprocessor macros define integer codes that name counter
** values associated with the [sqlite3_stmt_status()] interface.
** The meanings of the various counters are as follows:
**
** <dl>
** <dt>SQLITE_STMTSTATUS_FULLSCAN_STEP</dt>
** <dd>^This is the number of times that SQLite has stepped forward in
** a table as part of a full table scan.  Large numbers for this counter
** may indicate opportunities for performance improvement through 
** careful use of indices.</dd>
**
** <dt>SQLITE_STMTSTATUS_SORT</dt>
** <dd>^This is the number of sort operations that have occurred.
** A non-zero value in this counter may indicate an opportunity to
** improvement performance through careful use of indices.</dd>
**
** <dt>SQLITE_STMTSTATUS_AUTOINDEX</dt>
** <dd>^This is the number of rows inserted into transient indices that
** were created automatically in order to help joins run faster.
** A non-zero value in this counter may indicate an opportunity to
** improvement performance by adding permanent indices that do not
** need to be reinitialized each time the statement is run.</dd>
**
** </dl>
*/
#define SQLITE_STMTSTATUS_FULLSCAN_STEP     1
#define SQLITE_STMTSTATUS_SORT              2
#define SQLITE_STMTSTATUS_AUTOINDEX         3

/*
** CAPI3REF: Custom Page Cache Object
**
** The sqlite3_pcache type is opaque.  It is implemented by
** the pluggable module.  The SQLite core has no knowledge of
** its size or internal structure and never deals with the
** sqlite3_pcache object except by holding and passing pointers
** to the object.
**
** See [sqlite3_pcache_methods] for additional information.
*/
typedef struct sqlite3_pcache sqlite3_pcache;

/*
** CAPI3REF: Application Defined Page Cache.
** KEYWORDS: {page cache}
**
** ^(The [sqlite3_config]([SQLITE_CONFIG_PCACHE], ...) interface can
** register an alternative page cache implementation by passing in an 
** instance of the sqlite3_pcache_methods structure.)^
** In many applications, most of the heap memory allocated by 
** SQLite is used for the page cache.
** By implementing a 
** custom page cache using this API, an application can better control
** the amount of memory consumed by SQLite, the way in which 
** that memory is allocated and released, and the policies used to 
** determine exactly which parts of a database file are cached and for 
** how long.
**
** The alternative page cache mechanism is an
** extreme measure that is only needed by the most demanding applications.
** The built-in page cache is recommended for most uses.
**
** ^(The contents of the sqlite3_pcache_methods structure are copied to an
** internal buffer by SQLite within the call to [sqlite3_config].  Hence
** the application may discard the parameter after the call to
** [sqlite3_config()] returns.)^
**
** ^(The xInit() method is called once for each effective 
** call to [sqlite3_initialize()])^
** (usually only once during the lifetime of the process). ^(The xInit()
** method is passed a copy of the sqlite3_pcache_methods.pArg value.)^
** The intent of the xInit() method is to set up global data structures 
** required by the custom page cache implementation. 
** ^(If the xInit() method is NULL, then the 
** built-in default page cache is used instead of the application defined
** page cache.)^
**
** ^The xShutdown() method is called by [sqlite3_shutdown()].
** It can be used to clean up 
** any outstanding resources before process shutdown, if required.
** ^The xShutdown() method may be NULL.
**
** ^SQLite automatically serializes calls to the xInit method,
** so the xInit method need not be threadsafe.  ^The
** xShutdown method is only called from [sqlite3_shutdown()] so it does
** not need to be threadsafe either.  All other methods must be threadsafe
** in multithreaded applications.
**
** ^SQLite will never invoke xInit() more than once without an intervening
** call to xShutdown().
**
** ^SQLite invokes the xCreate() method to construct a new cache instance.
** SQLite will typically create one cache instance for each open database file,
** though this is not guaranteed. ^The
** first parameter, szPage, is the size in bytes of the pages that must
** be allocated by the cache.  ^szPage will not be a power of two.  ^szPage
** will the page size of the database file that is to be cached plus an
** increment (here called "R") of less than 250.  SQLite will use the
** extra R bytes on each page to store metadata about the underlying
** database page on disk.  The value of R depends
** on the SQLite version, the target platform, and how SQLite was compiled.
** ^(R is constant for a particular build of SQLite. Except, there are two
** distinct values of R when SQLite is compiled with the proprietary
** ZIPVFS extension.)^  ^The second argument to
** xCreate(), bPurgeable, is true if the cache being created will
** be used to cache database pages of a file stored on disk, or
** false if it is used for an in-memory database. The cache implementation
** does not have to do anything special based with the value of bPurgeable;
** it is purely advisory.  ^On a cache where bPurgeable is false, SQLite will
** never invoke xUnpin() except to deliberately delete a page.
** ^In other words, calls to xUnpin() on a cache with bPurgeable set to
** false will always have the "discard" flag set to true.  
** ^Hence, a cache created with bPurgeable false will
** never contain any unpinned pages.
**
** ^(The xCachesize() method may be called at any time by SQLite to set the
** suggested maximum cache-size (number of pages stored by) the cache
** instance passed as the first argument. This is the value configured using
** the SQLite "[PRAGMA cache_size]" command.)^  As with the bPurgeable
** parameter, the implementation is not required to do anything with this
** value; it is advisory only.
**
** The xPagecount() method must return the number of pages currently
** stored in the cache, both pinned and unpinned.
** 
** The xFetch() method locates a page in the cache and returns a pointer to 
** the page, or a NULL pointer.
** A "page", in this context, means a buffer of szPage bytes aligned at an
** 8-byte boundary. The page to be fetched is determined by the key. ^The
** mimimum key value is 1.  After it has been retrieved using xFetch, the page 
** is considered to be "pinned".
**
** If the requested page is already in the page cache, then the page cache
** implementation must return a pointer to the page buffer with its content
** intact.  If the requested page is not already in the cache, then the
** cache implementation should use the value of the createFlag
** parameter to help it determined what action to take:
**
** <table border=1 width=85% align=center>
** <tr><th> createFlag <th> Behaviour when page is not already in cache
** <tr><td> 0 <td> Do not allocate a new page.  Return NULL.
** <tr><td> 1 <td> Allocate a new page if it easy and convenient to do so.
**                 Otherwise return NULL.
** <tr><td> 2 <td> Make every effort to allocate a new page.  Only return
**                 NULL if allocating a new page is effectively impossible.
** </table>
**
** ^(SQLite will normally invoke xFetch() with a createFlag of 0 or 1.  SQLite
** will only use a createFlag of 2 after a prior call with a createFlag of 1
** failed.)^  In between the to xFetch() calls, SQLite may
** attempt to unpin one or more cache pages by spilling the content of
** pinned pages to disk and synching the operating system disk cache.
**
** ^xUnpin() is called by SQLite with a pointer to a currently pinned page
** as its second argument.  If the third parameter, discard, is non-zero,
** then the page must be evicted from the cache.
** ^If the discard parameter is
** zero, then the page may be discarded or retained at the discretion of
** page cache implementation. ^The page cache implementation
** may choose to evict unpinned pages at any time.
**
** The cache must not perform any reference counting. A single 
** call to xUnpin() unpins the page regardless of the number of prior calls 
** to xFetch().
**
** The xRekey() method is used to change the key value associated with the
** page passed as the second argument. If the cache
** previously contains an entry associated with newKey, it must be
** discarded. ^Any prior cache entry associated with newKey is guaranteed not
** to be pinned.
**
** When SQLite calls the xTruncate() method, the cache must discard all
** existing cache entries with page numbers (keys) greater than or equal
** to the value of the iLimit parameter passed to xTruncate(). If any
** of these pages are pinned, they are implicitly unpinned, meaning that
** they can be safely discarded.
**
** ^The xDestroy() method is used to delete a cache allocated by xCreate().
** All resources associated with the specified cache should be freed. ^After
** calling the xDestroy() method, SQLite considers the [sqlite3_pcache*]
** handle invalid, and will not use it with any other sqlite3_pcache_methods
** functions.
*/
typedef struct sqlite3_pcache_methods sqlite3_pcache_methods;
struct sqlite3_pcache_methods {
  void *pArg;
  int (*xInit)(void*);
  void (*xShutdown)(void*);
  sqlite3_pcache *(*xCreate)(int szPage, int bPurgeable);
  void (*xCachesize)(sqlite3_pcache*, int nCachesize);
  int (*xPagecount)(sqlite3_pcache*);
  void *(*xFetch)(sqlite3_pcache*, unsigned key, int createFlag);
  void (*xUnpin)(sqlite3_pcache*, void*, int discard);
  void (*xRekey)(sqlite3_pcache*, void*, unsigned oldKey, unsigned newKey);
  void (*xTruncate)(sqlite3_pcache*, unsigned iLimit);
  void (*xDestroy)(sqlite3_pcache*);
};

/*
** CAPI3REF: Online Backup Object
**
** The sqlite3_backup object records state information about an ongoing
** online backup operation.  ^The sqlite3_backup object is created by
** a call to [sqlite3_backup_init()] and is destroyed by a call to
** [sqlite3_backup_finish()].
**
** See Also: [Using the SQLite Online Backup API]
*/
typedef struct sqlite3_backup sqlite3_backup;


/*
** Undo the hack that converts floating point types to integer for
** builds on processors without floating point support.
*/
#ifdef SQLITE_OMIT_FLOATING_POINT
# undef double
#endif


#endif

/*
** 2010 August 30
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
*/

#ifndef _SQLITE3RTREE_H_
#define _SQLITE3RTREE_H_



typedef struct sqlite3_rtree_geometry sqlite3_rtree_geometry;


/*
** A pointer to a structure of the following type is passed as the first
** argument to callbacks registered using rtree_geometry_callback().
*/
struct sqlite3_rtree_geometry {
  void *pContext;                 /* Copy of pContext passed to s_r_g_c() */
  int nParam;                     /* Size of array aParam[] */
  double *aParam;                 /* Parameters passed to SQL geom function */
  void *pUser;                    /* Callback implementation user data */
  void (*xDelUser)(void *);       /* Called by SQLite to clean up pUser */
};

#endif  /* ifndef _SQLITE3RTREE_H_ */

