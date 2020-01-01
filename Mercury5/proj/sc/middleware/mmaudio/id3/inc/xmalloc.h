/*
 * mplib - a library that enables you to edit ID3 tags
 *
 * Copyright (c) 2001,2002,2003,2004,2005 Stefan Podkowinski
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 * * Neither the name of the author nor the names of its contributors
 *   may be used to endorse or promote products derived from this software
 *   without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __XMALLOC_H
#define __XMALLOC_H

/* __BEGIN_DECLS should be used at the beginning of your declarations,
   so that C++ compilers don't mangle their names.  Use __END_DECLS at
   the end of C declarations. */
#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif


#define XMALLOC(type) ((type *) xmalloc(sizeof(type)))
#define XMALLOCD(type,descr) ((type *) xmallocd(sizeof(type),descr))
#define XMALLOC0(type) ((type *) xmalloc0(sizeof(type)))
#define XMALLOCD0(type,descr) ((type *) xmallocd0(sizeof(type),descr))

__BEGIN_DECLS

/* define XMALLOC_CHECK 1 */

void *xmalloc(size_t);
void *xmallocd(size_t, char*);
void *xmalloc0(size_t);
void *xmallocd0(size_t, char*);
void *xrealloc(void *, size_t);
void *xcalloc(size_t, size_t);
void xfree(void*);
#ifdef XMALLOC_CHECK
void xprint_malloc_stat(void);
#endif

__END_DECLS

#endif /* __XMALLOC_H */
