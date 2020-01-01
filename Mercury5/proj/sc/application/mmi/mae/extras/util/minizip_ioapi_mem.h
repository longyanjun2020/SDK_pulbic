/**
 * @file minizip_ioapi_mem.h
 * 
 * @version $Id: minizip_ioapi_mem.h 291 2009-02-27 13:08:01Z kenny.wu $
 */
/* minizip_ioapi_mem.h -- IO base function header for compress/uncompress .zip
   files using zlib + zip or unzip API

   This version of ioapi is designed to access memory rather than files.
   We do use a region of memory to put data in to and take it out of. We do
   not have auto-extending buffers and do not inform anyone else that the
   data has been written. It is really intended for accessing a zip archive
   embedded in an application such that I can write an installer with no
   external files. Creation of archives has not been attempted, although
   parts of the framework are present.

   Based on Unzip ioapi.c version 0.22, May 19th, 2003

   Copyright (C) 1998-2003 Gilles Vollant
             (C) 2003 Justin Fletcher

   This file is under the same license as the Unzip tool it is distributed
   with.
*/



#ifdef __cplusplus
extern "C" {
#endif

#include "minizip_ioapi.h"
void fill_memory_filefunc (zlib_filefunc_def* pzlib_filefunc_def);

#ifdef __cplusplus
}
#endif
