/*
 * Nucleus OS Support Extension Layer
 *
 * Copyright (C) 2011, Broadcom Corporation
 * All Rights Reserved.
 * 
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 * $Id: nucleus_osl_ext.h,v 1.4 2009-11-27 18:32:41 Exp $
 */


#ifndef _rtkos_osl_ext_h_
#define _rtkos_osl_ext_h_

#ifdef __cplusplus
extern "C" {
#endif

/* ---- Include Files ---------------------------------------------------- */

#include <ahc_os.h>
#include <wlantypedefs.h>
#include <ahc_sd.h>
#include "sys.h"
/* ---- Constants and Types ---------------------------------------------- */


/* Semaphore. */
typedef sys_sem_t osl_ext_sem_t;


/* Mutex. */
typedef sys_mutex_t osl_ext_mutex_t;

/* Timer. */
typedef AHC_OS_TMRID osl_ext_timer_t;

/* Task. */
typedef struct osl_ext_task_t
{
	AHC_OS_TASKID	uc_task;
	void			*func;
	void			*arg;
	uint8			*stack;
	unsigned int	stack_size;
} osl_ext_task_t;

/* Queue. */
typedef struct osl_ext_queue_t
{
	AHC_OS_MQID		uc_queue;
	void			*uc_buffer;
	unsigned int 	uc_buffer_size;
} osl_ext_queue_t;

/* ---- Variable Externs ------------------------------------------------- */
/* ---- Function Prototypes ---------------------------------------------- */

//void osl_ext_printf(char* szFormat, ...);
extern void printc( char* szFormat, ... );
#define	osl_ext_printf printc

#ifdef __cplusplus
	}
#endif

#endif  /* _rtkos_osl_ext_h_  */
