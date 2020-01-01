/**
 * @file mae_shell_cls.h
 *
 * This header file declares the new, delete functions of CMAE_Shell_t class, and the
 * utility functions initializing the global object MAE_Shell and MAE system.
 *
 * @version $Id: mae_shell_cls.h 291 2009-02-27 13:08:01Z kenny.wu $
 */

#ifndef __MAE_SHELL_CLS_H__
#define __MAE_SHELL_CLS_H__

#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

//
// CMAE_Shell_t class
//
// this class implements an IShell interface
// it's designed to be a singleton object
// most of the large private structures are stored in static variables
typedef struct
{
	IShell pShell;
	u32 nRefCount;

	/// default event handler for the unhandled events which have not been assigned a destination
	PfnDefEventHandler pfnDefault;
	/// shell's operating state
	u16 nState;
} CMAE_Shell_t;


//
// function prototypes
//
/**
 * The new function of CMAE_Shell_t object
 */
MAERet_t MAE_Shell_New(MAEClsId_t nClsId, void **ppObj);

/**
 * The delete function of CMAE_Shell_t object
 */
MAERet_t MAE_Shell_Delete(CMAE_Shell_t *pThis);

/**
 * The initiate function for MMI task to start the shell
 */
MAERet_t MAE_Shell_Init(void);

/**
 * The terminate function for MMI task to terminate the shell
 */
MAERet_t MAE_Shell_Terminate(void);

#endif // __MAE_SHELL_CLS_H__
