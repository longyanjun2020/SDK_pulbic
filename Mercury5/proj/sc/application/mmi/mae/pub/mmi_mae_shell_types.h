/**
 * @file mmi_mae_shell_types.h
 *
 * This header file defines SHELL enums and data types.
 *
 * @version $Id: mmi_mae_shell_types.h $
 */
#ifndef __MMI_MAE_SHELL_TYPES_H__
#define __MMI_MAE_SHELL_TYPES_H__

#include "mmi_mae_common_def.h"

/**
* Prototype of the new function of any class in MAE Platform. It will be called by shell to
* create an instance of the specified class id.
*/
typedef MAERet_t (*PfnNew)(MAEClsId_t nClsId, void **ppObj);

/**
* Prototype of the pre-new function of applets in MAE Platform.
*/
typedef void (*PfnPreNew)(void);

/**
* The element structure of MAE class table.
*/
struct MAE_ClassInfo_tag
{
	PfnNew pfnNew;
};

/**
* The element structure of Applet default function table.
*/
struct AppletDefFunc_t_
{
	PfnPreNew pfnPreNew;
};

#endif //__MMI_MAE_SHELL_TYPES_H__
