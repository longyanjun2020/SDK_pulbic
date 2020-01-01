/*
** paltform.h: the platform header file.
**
** Copyright (C) 2007-2008 SKY-MOBI AS.  All rights reserved.
**
** This file is part of the simple gui library.
** It may not be redistributed under any circumstances.
*/

#ifndef _SGL_PLATFORM_H
#define _SGL_PLATFORM_H
//#include "sg_platform.h"
//#include "mrc_base.h"
//#include "mrc_base_i.h"
#include "ven_std.h"

#define OMIT_NETWORK_MODULE 1

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

#define SGL_TRACE(...) 

#define SGL_MALLOC		sgl_malloc
#define SGL_FREE			sgl_mem_free
#define SGL_MEMSET		ven_std_memset
#define SGL_MEMCPY		ven_std_memcpy
#define SGL_MEMMOVE		ven_std_memmove
#define SGL_STRCPY		ven_std_strcpy
#define SGL_STRNCPY		ven_std_strncpy
#define SGL_STRCAT		ven_std_strcat
#define SGL_STRNCAT		ven_std_strncat
#define SGL_MEMCMP		ven_std_memcmp
#define SGL_STRCMP		ven_std_strcmp
#define SGL_STRNCMP		ven_std_strncmp
#define SGL_STRCOLL		strcoll
#define SGL_MEMCHR		memchr
#define SGL_STRLEN		ven_std_strlen
#define SGL_STRSTR		ven_std_strstr
#define SGL_SPRINTF		ven_std_sprintf
#define SGL_ATOI		  ven_std_atoi
#define SGL_STROUL		atol
#define SGL_WSTRLEN      ven_std_wstrlen

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _SGL_PLATFORM_H */

