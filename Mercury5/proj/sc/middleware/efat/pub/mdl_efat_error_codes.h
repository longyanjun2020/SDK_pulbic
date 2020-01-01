////////////////////////////////////////////////////////////////////////////////
/// @file   mdl_efat_error_codes.h
/// @author MStar Semiconductor Inc.
/// @brief  Shell command parser state machine
////////////////////////////////////////////////////////////////////////////////
#ifndef MDL_EFAT_ERROR_CODES_H
#define MDL_EFAT_ERROR_CODES_H

typedef int Efat_ErrNo;

// move to pub folder
#ifdef __cplusplus
extern "C" {
#endif



// CONSTANT DEFINITIONS

#define EFAT_ENOERR           0
// No error
#define EFAT_EPERM            1
// Not permitted
#define EFAT_ENOENT           2
// No such entity
#define EFAT_ESRCH            3
// No such process
#define EFAT_EINTR            4
// Operation interrupted
#define EFAT_EIO              5
//separate

// I/O error
#define EFAT_EBADF            9
// Bad file handle
#define EFAT_EAGAIN           11
// Try again later
#define EFAT_EWOULDBLOCK      EFAT_EAGAIN

#define EFAT_ENOMEM           12
// Out of memory
#define EFAT_EBUSY            16
// Resource busy
#define EFAT_EXDEV            18
// Cross-device link
#define EFAT_ENODEV           19
//separate

// No such device
#define EFAT_ENOTDIR          20
// Not a directory
#define EFAT_EISDIR           21
// Is a directory
#define EFAT_EINVAL           22
// Invalid argument
#define EFAT_ENFILE           23
// Too many open files in system
#define EFAT_EMFILE           24
// Too many open files
#define EFAT_ENODIR           25

#define EFAT_EFBIG            27
//separate

// File too large
#define EFAT_ENOSPC           28
// No space left on device
#define EFAT_ESPIPE           29
// Illegal seek
#define EFAT_EROFS            30
// Read-only file system
#define EFAT_EDOM             33
// Argument to math function outside valid
#define EFAT_ERANGE           34
// Math result cannot be represented
#define EFAT_EDEADLK          35
// Resource deadlock would occur
//separate

#define EFAT_EDEADLOCK        EFAT_EDEADLK

#define EFAT_ENOSYS           38
// Function not implemented
#define EFAT_ECRSLNK          39
// Cross link
#define EFAT_ENULLENTRY       40
// NULL fat entry
#define EFAT_ENULLFATSECT     41
// NULL fat tbl
#define EFAT_EFATNOTSAME      42
// fat tbl not same
#define EFAT_EDISKLOCK        43
// disk dirty
#define EFAT_EDISKDIRTY       44
// root space full
#define EFAT_ROOTNOSPC        45

#define EFAT_ALRCLOSED        46

#define EFAT_ABORT            47

#define EFAT_NOPARPATH        48

#define EFAT_DIRCORRUPTED     51

#define EFAT_FILECORRUPTED    52

#define EFAT_RESOURCE_BUSY    53

#define EFAT_MOUNT_FAIL       54

#define EFAT_INCONSITANT_FAT    55
//separate
#define EFAT_IOERR_2_RO       56

#define EFAT_NOTATEOF       57

// disk lock
#define EFAT_ENAMETOOLONG     60
// File name too long
#define EFAT_ENOTEMPTY        66
// Directory not empty
#define EFAT_ENOTSUP          95
// Not supported error
#define EFAT_EEOF             200
// End of file reached
#define EFAT_ENOSUPP          201
// Operation not supported
//separate

#define EFAT_EDEVNOSUPP       202
// does not support this operation
#define EFAT_EBBLKRETRY       203
// bad block found & retry  can cover
#define EFAT_EBBLKERROR       204
// bad block found & retry cannot cover
#define EFAT_ENXIO            205
// Device not configured
#define EFAT_EACCES           206
// Permission denied
#define EFAT_EEXIST           207
// File exists
#define EFAT_ENOTTY           208
// Inappropriate ioctl for device
//separate

#define EFAT_EPIPE            209
// Broken pipe
#define EFAT_EINPROGRESS      210
// Operation now in progress
#define EFAT_EALREADY         211
// Operation already in progress
#define EFAT_ENOTSOCK         212
// Socket operation on non-socket
#define EFAT_EDESTADDRREQ     213
// Destination address required
#define EFAT_EMSGSIZE         214
// Message too long
//separate

#define EFAT_EPROTOTYPE       215
// Protocol wrong type for socket
#define EFAT_ENOPROTOOPT      216
// Protocol not available
#define EFAT_EPROTONOSUPPORT  217
// Protocol not supported
#define EFAT_ESOCKTNOSUPPORT  218
// Socket type not supported
#define EFAT_EOPNOTSUPP       219
// Operation not supported
#define EFAT_EPFNOSUPPORT     220
// Protocol family not supported
//separate

#define EFAT_EAFNOSUPPORT     221
// Address family not supported by
#define EFAT_EADDRINUSE       222
// already in use
#define EFAT_EADDRNOTAVAIL    223
// Can't assign requested address
#define EFAT_ENETDOWN         224
// Network is down
#define EFAT_ENETUNREACH      225
// unreachable
#define EFAT_ENETRESET        226
// dropped connection on reset
//separate

#define EFAT_ECONNABORTED     227
// SW caused connection abort
#define EFAT_ECONNRESET       228
// reset by peer
#define EFAT_ENOBUFS          229
// No buffer space available
#define EFAT_EISCONN          230
// already connected
#define EFAT_ENOTCONN         231
// not connected
#define EFAT_ESHUTDOWN        232
// Can't send : socket shutdown
#define EFAT_ETOOMANYREFS     233
// Too many references
//separate

#define EFAT_ETIMEDOUT        234
// Operation timed out
#define EFAT_ECONNREFUSED     235
// Connection refused
#define EFAT_EHOSTDOWN        236
// Host is down
#define EFAT_EHOSTUNREACH     237
// No route to host

#define EFAT_EDAMNIT          254
// No route to host



#ifdef __cplusplus
}   // extern "C"
#endif

#endif //#ifndef MDL_EFAT_ERROR_CODES_H
