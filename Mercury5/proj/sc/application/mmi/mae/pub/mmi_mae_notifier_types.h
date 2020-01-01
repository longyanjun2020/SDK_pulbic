/**
 * @file	mmi_mae_notifier_types.h
 * @brief	This file describes the MAE notifier data types.
 * @version	$Id: mmi_mae_notifier_types.h $
 */

#ifndef __MMI_MAE_NOTIFIER_TYPES_H__
#define __MMI_MAE_NOTIFIER_TYPES_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"

/**
* The structure that stores registered listener and its notification mask.
*/
struct MAE_Listener_t_
{
	MAEInstId_t nListnerId; ///< the instance id of notification listener
	u32 nMask; ///< the mask that stores listener's interested events
};

/**
 * The incomplete type of MAE notifier structure.
 */
struct MAE_Notifier_t_
{
	MAEInstId_t nNotifierId; ///< the instance id of notification issuer
	MAE_Listener_t *pList; ///< list to store registered listeners
	u16 nCount; ///< the number of registered listeners
	u16 nSize; ///< the capacity of listener list
	//u32 nPattern; ///< a guard pattern to indicate that it's a notifier structure
};
/**
 * The structure to return listener state after registration/deregistration.
 */
struct NTF_ListenerState_t_
{
	u32 nResult;
	u32 nMask;
};

/**
 * The results of listener registration/deregistration.
 */
opaque_enum(NTF_ListenerState_e_)
{
    NTF_LISTENER_UPDATED = 0, ///< an existing listener's mask is updated
    NTF_LISTENER_ADDED, ///< a new listener is added to notifier's list
    NTF_LISTENER_REMOVED ///< a listener has no registered notification and is removed from notifier
};

#endif // __MMI_MAE_NOTIFIER_TYPES_H__
