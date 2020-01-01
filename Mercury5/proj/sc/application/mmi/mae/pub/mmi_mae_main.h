/**
 * @file mmi_mae_main.h
 *
 * The header file defines the prototypes of initializing, terminating of MAE
 *
 * @version $Id: mmi_mae_main.h 291 2009-02-27 13:08:01Z kenny.wu $
 */

#ifndef __MMI_MAE_MAIN_H__
#define __MMI_MAE_MAIN_H__
#include "mmi_mae_common_def.h"

/**
 * The entry function of MAE.
 */
MAERet_t MAE_Init(void);

/**
 * The exit function of MAE.
 */
void MAE_Terminate(void);



#endif // __MAE_MAIN_H__
