/****************************************************************************/
/*  File    : sys_sys_shutdown.h                                                */
/*--------------------------------------------------------------------------*/
/*  Scope   : System shutdown procedure                                     */
/*                                                                          */
/*  Contents:                                                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/****************************************************************************/



#ifndef __SYS_SYS_SHUTDOWN_H__
#define __SYS_SYS_SHUTDOWN_H__

#include "vm_types.ht"

/**
 * @brief System shutdown procedure.
 */
void sys_shutdown(void);
bool sys_ShutdownFs(void);

#endif //__SYS_SYS_SHUTDOWN_H__

