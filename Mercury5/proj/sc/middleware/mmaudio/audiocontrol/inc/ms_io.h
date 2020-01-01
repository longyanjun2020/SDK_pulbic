////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2009-2010 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// ("MStar Confidential Information") by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////


#ifndef MS_IO_H
#define MS_IO_H

#define MAX_FILE_NAME_LENGTH            (262*2)
#define FILENAMESIZE                    (2*(MAX_FILE_NAME_LENGTH+4*2))


#if defined(MIPSDEV) || defined(CERAMAL_PLATFORM)
#define IO_USE_UNISTD
#endif

#if defined(_MSC_VER)&&(!defined(__SDK_SIMULATION__))
#include <TCHAR.h>
#endif

// File I/O routine mapping

#ifdef IO_USE_UNISTD
#include <unistd.h>
#include <fcntl.h>

#define O_MS_BINARY 0

#define MS_FO_RB    (O_RDONLY|O_MS_BINARY)
#define MS_FO_R      (O_RDONLY)
#define MS_FO_RW   (O_RDWR)
#define MS_FO_RP    (O_RDWR)
#define MS_FO_WB   (O_WRONLY|O_CREAT|O_TRUNC |O_MS_BINARY)
#define MS_FO_W     (O_WRONLY|O_CREAT|O_TRUNC)
#define MS_FO_WPB (O_RDWR  |O_CREAT|O_TRUNC |O_MS_BINARY)
#define MS_FO_WT   (MS_FO_W)
#define MS_FO_AB    (O_WRONLY|O_CREAT|O_APPEND|O_MS_BINARY)
#define MS_FO_A      (O_WRONLY|O_CREAT|O_APPEND)
#define MS_FO_AP    (O_RDWR  |O_CREAT|O_APPEND)

#define MSFILE int

#if !defined(CERAMAL_PLATFORM)
#define ms_open(file, a)                fs_open(file, a)
#define ms_open_fcc(file, a, buf, size) fs_open_fcc(file, a, buf, size)
#define ms_open_fail(x)                 ((x)<0)
#define ms_close(file)                  close((MSFILE)file)
#define ms_write(buf, unit, size, file) write(file, buf, (size)*(unit))
#define ms_read(buf, unit, size, file)  read((MSFILE)file, buf, (size)*(unit))
#define ms_flush                        fsync
#define ms_seek(file, offset, whence)   lseek((MSFILE)file, offset, whence)
#define ms_sync                         sync
#define ms_strlen                       fs_strlen
#define ms_fhandle_init(x) ((x)=-1)
#else
#define ms_open                         c51_open_fast
#define ms_open_fcc(file, a, buf, size) fs_open_fcc(file, a, buf, size)
#define ms_close                        c51_close
#define ms_open_fail(x)                 ((x) < 0)
#define ms_write(buf, unit, size, file) write(file, buf, (size)*(unit))
#define ms_read(buf, unit, size, file)  c51_read((MSFILE)file, buf, (size)*(unit))
#define ms_flush                        fsync
#define ms_seek(file, offset, whence)   c51_lseek((MSFILE)file, offset, whence)
#define ms_sync                         sync
#define ms_strlen                       fs_strlen
#endif

#else //IO_USE_UNISTD

#if defined(_MSC_VER)&&(!defined(__SDK_SIMULATION__))
#include <stdio.h>
#define MSFILE FILE *
#define MS_FO_RB        _T("rb")
#define MS_FO_R          _T("r")
#define MS_FO_RP        _T("r+")
#define MS_FO_RW       _T("r+")
#define MS_FO_WB       _T("wb")
#define MS_FO_W         _T("w")
#define MS_FO_WPB     _T("w+b")
#define MS_FO_WT       _T("wt")
#define MS_FO_AB        _T("ab")
#define MS_FO_A          _T("a")
#define MS_FO_AP        _T("a+")
#define ms_open          _tfopen
#define ms_gets           _fgetts
#define ms_puts           _fputts
#define ms_open_fail(x)  ((x) == 0)
#define ms_close         fclose
#define ms_write         fwrite
#define ms_read          fread
#define ms_flush         fflush
#define ms_seek(a, b, c) (fseek(a,b,c) ? -1 : ftell(a))
#define ms_sync()        // not available

#elif defined(__RTK_OS__)
#include "mdl_drm_vfs_file.ho"

#define MSFILE DRM_VFS_FILE *
#define MS_FO_RB "rb"
#define MS_FO_R  "r"
#define MS_FO_RP          "r+"
#define MS_FO_RW "r+"
#define MS_FO_WB "wb"
#define MS_FO_W  "w"
#define MS_FO_WPB         "w+b"
#define MS_FO_WT "wt"
#define MS_FO_AB "ab"
#define MS_FO_A  "a"
#define MS_FO_AP          "a+"

#define ms_open(file, a)  drm_file_fopen(file, a)
#define ms_open_fail(x)   ((x) == 0)
#define ms_close(a)       drm_file_fclose(a)
#define ms_write(a,b,c,d) drm_file_fwrite(d, a, ((b) * (c)))
#define ms_read(a,b,c,d)  drm_file_fread(d, a, ((b) * (c)))
#define ms_tell           drm_file_ftell
#define ms_flush(a)       // not available
#define ms_seek(a, b, c)  (drm_file_fseek(a,b,c), drm_file_ftell(a))

#define ms_sync()         // not available
#define ms_strlen         strlen
#define ms_fhandle_init(x) ((x)=NULL)

#else // _MSC_VER
#include <stdio.h>
#define MSFILE FILE *
#define MS_FO_RB        "rb"
#define MS_FO_R         "r"
#define MS_FO_RP        "r+"
#define MS_FO_RW        "r+"
#define MS_FO_WB        "wb"
#define MS_FO_W         "w"
#define MS_FO_WPB       "w+b"
#define MS_FO_WT        "wt"
#define MS_FO_AB        "ab"
#define MS_FO_A         "a"
#define MS_FO_AP        "a+"
#define ms_open         fopen
#define ms_gets         fgets
#define ms_puts         fputs
#define ms_open_fail(x)  ((x) == 0)
#define ms_close         fclose
#define ms_write         fwrite
#define ms_read          fread
#define ms_flush         fflush
#define ms_seek(a, b, c) (fseek(a,b,c) ? -1 : ftell(a))
#define ms_sync()        // not available
#endif // _MSC_VER

#endif // IO_USE_UNISTD

// File name manipulation

#if defined(MIPSDEV)

typedef char ms_fnchar;
#define MS_FN(fn) fn
#define ms_fnrchr              fs_strrchr
#define ms_fncpy(dst, src, n)  (fs_strncpy(dst, src, n), (dst)[(n) - 1] = 0)
#define ms_fnlen               fs_strlen
#define MS_MAX_PATH FILENAMESIZE

#elif defined(_MSC_VER)&&(!defined(__SDK_SIMULATION__))

typedef TCHAR ms_fnchar;
#ifdef WINCE
#define MS_FN(fn)  TEXT(fn) // hack for non-conformance header
#else
#define MS_FN(fn) _TEXT(fn)
#endif
#define ms_fnrchr              _tcsrchr
#define ms_fncpy(dst, src, n)  (_tcsncpy(dst, src, n), (dst)[(n) - 1] = 0)
#define ms_fnlen               _tcslen
#define ms_fncat               _tcscat
#define ms_fncmp               _tcscmp
#define MS_MAX_PATH 256

#elif defined(__RTK_OS__)

#include "mdl_vfs_struct.h"
#include "util_ucs2.hi"
typedef u16Char ms_fnchar;

#define MS_FN(fn)               L##fn
#define ms_fnrchr(s, c)         sysUtil_UCS2FindExtDot(s)
#define ms_fncpy                sysUtil_UCS2StringNCopy
#define ms_fnlen                sysUtil_UCS2StringLength
#define ms_fncat                sysUtil_UCS2StringCat
#define ms_fncmp                sysUtil_UCS2StringCmp
#define MS_MAX_PATH VFS_FAT_SPEC_FULLPATH_LEN

#else

typedef char ms_fnchar;

#define MS_FN(fn) fn
#define ms_fnrchr              strrchr
#define ms_fncpy(dst, src, n)  (strncpy(dst, src, n), (dst)[(n) - 1] = 0)
#define ms_fnlen               strlen
#define ms_fncat               strcat
#define ms_fncmp               strcmp
#define MS_MAX_PATH 256
#endif

#endif // MS_IO_H
