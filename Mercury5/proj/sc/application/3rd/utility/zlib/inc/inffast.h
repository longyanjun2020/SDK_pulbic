/* inffast.h -- header to use inffast.c
 * Copyright (C) 1995-2003 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h
 */

/* WARNING: this file should *not* be used by applications. It is
   part of the implementation of the compression library and is
   subject to change. Applications should only use zlib.h.
 */

void inflate_fast OF((z_streamp strm, unsigned start));

#if (ZLIB_USE_ROM==1 && ZLIB_BUILD_ROM==0)
void inflate_fast_ OF((z_streamp strm, unsigned start));
ZEXTERN void (*inflate_fast_dispatch) OF((z_streamp strm, unsigned start));
#endif

#if (!(ZLIB_USE_ROM==1))
void inflate_fast_simple OF((z_streamp strm, unsigned start));
#endif
