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
 * $Id: nucleus_osl.c,v 1.2 2008-12-01 22:57:18 Exp $
 */

/* ---- Include Files ---------------------------------------------------- */

#include "rtkos_osl.h"

#include "wlantypedefs.h"
//#include "bcmdefs.h"
//#include "bcmendian.h"
//#include "bcmutils.h"
//#include <ahc_os.h>


/* ---- Public Variables ------------------------------------------------- */
/* ---- Private Constants and Types -------------------------------------- */
/* ---- Private Variables ------------------------------------------------ */
/* ---- Private Function Prototypes -------------------------------------- */
/* ---- Functions -------------------------------------------------------- */

/* ----------------------------------------------------------------------- */
void osl_delay(uint usec)
{
	uint msec;

	if (usec == 0)
		return;

	/* Micro-second resolution not supported. Convert to milli-seconds. */
	if (usec < 1000) {
		msec = 1;
	}
	else {
		msec = usec / 1000;
	}

    MMPF_OS_SleepMs(msec);
}
