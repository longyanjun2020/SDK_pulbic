/**
 * @file mmi_mae_apm.h
 *
 * This header file defines APM enums and constants used in IShell's applet methods.
 *
 * @version $Id: mmi_mae_apm.h 1717 2009-09-02 10:02:12Z mark.yang $
 */

#ifndef __MMI_MAE_APM_H__
#define __MMI_MAE_APM_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_forward.h"

/**
 * Prototype of the function to be passed as a parameter in StartAppletEx(). It will be called
 * after APM starts the applet and passes parameter to it, to clean up the objects or memory
 * blocks used in the parameter.
 */
typedef void (*PfnStartParamCleanup)(IBASE *pIssuer, u32 nParam);

/**
 * Prototype of the callback function to be passed as a parameter in FlushAppletStack(). It will
 * be called after the flush command is accomplished, or canceled by user or other interruptions.
 */
typedef void (*PfnFlushCallback)(IBASE *pObj, u32 nResult);

#ifdef __PC_SIMULATOR__
int SH_getCurrentAP();
#endif


#endif // __MAE_APM_H__
