/*
 * uCOS OS Support Layer
 *
 * Copyright (C) 2011, Broadcom Corporation
 * All Rights Reserved.
 * 
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 * $Id: nucleus_osl.h,v 1.4 2009-04-17 22:54:58 Exp $
 */


#ifndef rtkos_osl_h
#define rtkos_osl_h

#ifdef __cplusplus
extern "C" {
#endif

/* ---- Include Files ---------------------------------------------------- */

/* Map bcopy to memcpy. */
#define BWL_MAP_BCOPY_TO_MEMCPY
#include "generic_osl.h"

#include <ahc_os.h>
#include "mem.h"
/* ---- Constants and Types ---------------------------------------------- */

/* This is really platform specific and not OS specific. */
#ifndef BWL_UC_TICKS_PER_SECOND
#define BWL_UC_TICKS_PER_SECOND OS_TICKS_PER_SEC
#endif

#define OSL_MSEC_TO_TICKS(msec)  ((BWL_UC_TICKS_PER_SECOND * (msec)) / 1000)
#define OSL_TICKS_TO_MSEC(ticks) ((1000 * (ticks)) / BWL_UC_TICKS_PER_SECOND)

#ifndef __RTK_OS__
#define __FUNCTION__	__func__
#endif

/* Get processor cycle count */
// Fred comment out since we don't use it
//#define OSL_GETCYCLES(x)	((x) = NU_Retrieve_Clock())


/* ---- Variable Externs ------------------------------------------------- */
/* ---- Function Prototypes ---------------------------------------------- */
// Use the implementations in lwip directly
#ifndef __RTK_OS__
void* mem_malloc(ulong size);
void mem_free(void *rmem);
#endif

//void printc( char* szFormat, ... );

#ifdef __cplusplus
	}
#endif

#endif  /* rtkos_osl_h  */
