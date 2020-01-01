/*
 * Copyright(c) Faith,Inc.  All Rights Reserved.
 *
 * $Revision: 1.3 $
 */
#ifndef SYSTEM_SOURCE_H__
#define SYSTEM_SOURCE_H__ 1

#include "fsystem_types.h"

#ifdef FCONFIG_MAX_SMFTRACK
#define FSRC_MAX_SRC	(FCONFIG_MAX_SMFTRACK+1)
#else 
#define FSRC_MAX_SRC	(48+1)
#endif 
typedef struct _fsrc_ {
	const u_8			*head;
	const u_8			*pos;
	const u_8			*tail;
} *fsrc_t;
typedef struct _fsrc_base_ {
	const u_8		*head;
	fsize_t			length;

	struct _fsrc_	node[ FSRC_MAX_SRC ];
} *fsrc_base_t;

BEGIN_C_DECLS


extern fsrc_base_t fsrc_base_open(struct _fsrc_base_ *work, const u_8 *data, fsize_t length);
#define FSRC_BASE_OPEN(work, data, length)	fsrc_base_open(work, data, length)

extern void fsrc_base_close(fsrc_base_t base);
#define FSRC_BASE_CLOSE(base)	fsrc_base_close(base)


extern fsrc_t fsrc_open(fsrc_base_t base, foff_t offset, fsize_t size);
#define FSRC_OPEN(base, off, size)	fsrc_open(base, off, size)

extern void fsrc_close(fsrc_t fsrc);
#define FSRC_CLOSE(fsrc)	fsrc_close(fsrc)

extern foff_t fsrc_get_offset(fsrc_t fsrc);
#define FSRC_GET_OFFSET(fsrc)	fsrc_get_offset(fsrc)

extern void fsrc_seek(fsrc_t fsrc, foff_t offset);
#define FSRC_SEEK(fsrc, off)	fsrc_seek(fsrc, off)

extern void fsrc_fwd(fsrc_t fsrc, foff_t offset);
#define FSRC_FWD(fsrc, off)	fsrc_fwd(fsrc, off)


extern void* fsrc_get_buffer(fsrc_t fsrc, fsize_t size);
#define FSRC_GET_BUFFER(fsrc, size)	fsrc_get_buffer(fsrc, size)

END_C_DECLS

#endif /* SYSTEM_SOURCE_H__ */
