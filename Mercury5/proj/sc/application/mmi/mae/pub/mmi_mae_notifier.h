/**
 * @file	mmi_mae_notifier.h
 * @brief	This file describes the MAE notifier APIs.
 *
 * MAE notifier provides a set of APIs to help developers implementing notify mechanism in their
 * objects. These APIs work on a specific notifier structure which stores listener instances and
 * notification masks they are interested.
 *
 * Developers can use these APIs to create/delete notifier structures, manage the notifier
 * registrations, and notify the interested instances easily.
 *
 * The mask indicates the notification groups that a service class provides, and is defined on a
 * per-class basis. The meaning of each mask bit of a specific class shall be made available to
 * others, so users can register for notifications they are interested. The mask definition can be
 * very flexible. Developers can assign several events to a single mask bit, or use a one-to-one
 * mapping base on their requirements.
 *
 * Note that the notification is achieved by posting events to the listener instances. So the rules
 * of event communication are also applied, such as that there shall be a reference between issuer
 * and recipient objects. The notifier is a stand-alone structure and doesn't manage the references
 * for the issuer. Objects use notifier shall either handle the references themselves, or leave
 * the problem to the listeners; since they shall keep the issuer instances if they are interested
 * in those notification events.
 *
 * @author	kenny.wu@mstarsemi.com
 * @version	$Id: mmi_mae_notifier.h 1684 2009-08-29 16:28:08Z zinc.chen $
 */

#ifndef __MMI_MAE_NOTIFIER_H__
#define __MMI_MAE_NOTIFIER_H__
#include "mmi_mae_common_def.h"
#include "mmi_mae_shell.h"
#include "mmi_mae_forward.h"
#include "mmi_mae_notifier_forward.h"

/**
 * This function allocates and initializes a notifier structure.
 *
 * This function creates a notifier structure and returns its address. The address is needed as an
 * identification in all the other notifier operations.
 *
 * @param pIssuer		The instance that owns the notifier. It will be the issuer to post notify events.
 * @param ppNotifier	The pointer to return the address of created notifier. It will be null if this function fails.
 *
 * @retval MAE_RET_SUCCESS			The notifier is created successfully.
 * @retval MAE_RET_OUT_OF_MEMORY	Insufficient memory to allocate notifier structures.
 * @retval MAE_RET_BAD_PARAM		Invalid input address.
 */
MAERet_t NOTIFIER_Create(IBASE *pIssuer, MAE_Notifier_t **ppNotifier);

/**
 * This function deletes a notifier structure and frees associated memory blocks.
 *
 * @param pNotifier		The notifier to be deleted.
 *
 * @retval MAE_RET_SUCCESS		The notifier is deleted successfully.
 * @retval MAE_RET_BAD_PARAM	The input address doesn't point to a notifier, or the notifier structure
 *								has been destroyed.
 * @retval MAE_RET_NOT_EMPTY	The notifier has uncancelled listeners. Still the notifier will be deleted,
 * 								but there may be some reference problems.
 */
MAERet_t NOTIFIER_Delete(MAE_Notifier_t *pNotifier);

/**
 * This function registers the notification mask of a listener to notifier.
 *
 * The service implementation can use this function to register a (listener, mask) tuple to notifier.
 * The specified mask is the combination of notification groups that listener is interested, and
 * the events will be posted accordingly. The listener is added into notifier if it doesn't exist.
 * Otherwise its new mask will be ORed to the existing one.
 *
 * @param pNotifier		The notifier for registering notifications.
 * @param pListener		The listener instance to be registered.
 * @param nMask			The notifications that listener wants to register. Each bit of mask is used to denote
 *						a specific event group that the listeners may be interested. The definition of mask
 *						bits is irrelative to the notifier. It is left to the implementation of service classes,
 *						and the meanings shall be made available to which use those services.
 * @param pState		The address to return listener's state after successful registration. This parameter
 *						can be set to null if the final state is not needed.
 *
 * @retval MAE_RET_SUCCESS			The listener's notification mask is updated.
 * @retval MAE_RET_BAD_PARAM		Invalid input address.
 * @retval MAE_RET_OUT_OF_MEMORY	The notifier fails to allocate memory for a new listener.
 */
MAERet_t NOTIFIER_Register(MAE_Notifier_t *pNotifier, IHANDLER *pListener, u32 nMask, NTF_ListenerState_t *pState);

/**
 * This function deregisters the notification mask of a listener from notifier.
 *
 * The service implementation can use this function to deregister a listener's notification mask.
 * The specified mask is the set of notification groups that listener is no longer needed. These bits
 * will be cleared from notifier's listener mask. If the listener has no registered notifications
 * after deregistration, it will be removed from notifier's list.
 *
 * @param pNotifier		The notifier for deregistering notifications.
 * @param pListener		The listener instance to be deregistered.
 * @param nMask			The notifications that listener wants to deregister. These bits will be cleared
 *						from listener's mask. The meanings of these mask bits are defined in service
 *						implementation and is irrelative to the notifier.
 * @param pState		The address to return listener's state after successful deregistration. This
 *						parameter can be set to null if the final state is not needed.
 *
 * @retval MAE_RET_SUCCESS			The listener's notification mask is updated.
 * @retval MAE_RET_BAD_PARAM		Invalid input address.
 * @retval MAE_RET_NOT_FOUND		The listener to be deregistered is not found in notifier's list.
 */
MAERet_t NOTIFIER_Deregister(MAE_Notifier_t *pNotifier, IHANDLER *pListener, u32 nMask, NTF_ListenerState_t *pState);

/**
 * This function notifies the registered listeners which are interested in certain events.
 *
 * This function is called by the service when an specific event that associated with a notification
 * group happens. It makes notifier find listeners whose registered mask matches the certain
 * notification, then post the specified event to them on behalf of the issuer instance.
 *
 * The data that this function posts with are specific to the event and notification group of service's
 * implementation. The mask, event and data parameters that service uses to call this function shall
 * be associated together and announced in service's notifier definition, thus listeners can receive
 * the notifications they expect, and recognize the data that come along.
 *
 * @param pNotifier		The notifier to handle notification.
 * @param nMask			It specifies the notification group. This mask should have only one set bit, and
 *						it shall be associated with subsequent event and data parameters. If the mask
 *						specifies multiple bits, and some listener has multiple matches, the notifier
 *						still posts event once. If the service developer is intentionally to do so,
 *						the posted event should carry sufficient information to indicate these cases.
 * @param nEvt, nLParam, nDParam
 *						These parameters are the notify event and data to be posted to listeners.
 *
 * @retval MAE_RET_SUCCESS		Notifying is completed. Note that this function still returns SUCCESS
 *								even if no listener is notified, or some events are not successfully
 *								posted to the listeners.
 * @retval MAE_RET_BAD_PARAM	The input address doesn't point to a notifier, or the notifier structure
 *								has been destroyed.
 */
MAERet_t NOTIFIER_Notify(MAE_Notifier_t *pNotifier, u32 nMask, MAEEvent_t nEvt, u32 nLParam, u32 nDParam);

/**
 * This function is the extended version of NOTIFIER_Notify() and provides a cleanup function to
 * release the event data.
 *
 * @param pNotifier		The notifier to handle notification.
 * @param nMask			It specifies the notification group. This mask should have only one set bit, and
 *						it shall be associated with subsequent event and data parameters. If the mask
 *						specifies multiple bits, and some listener has multiple matches, the notifier
 *						still posts event once. If the service developer is intentionally to do so,
 *						the posted event should carry sufficient information to indicate these cases.
 * @param nEvt, nLParam, nDParam, fnClean
 *						These parameters are the notify event and data to be posted to listeners, and
 *						the cleanup function to release the data. The issuer instance passed to cleanup
 *						function will be the instance that initializes the notifier, and shall be the
 *						service itself.
 *
 * @retval MAE_RET_SUCCESS		Notifying is completed. Note that this function still returns SUCCESS
 *								even if no listener is notified, or some events are not successfully
 *								posted to the listeners.
 * @retval MAE_RET_BAD_PARAM	The input address doesn't point to a notifier, or the notifier structure
 *								has been destroyed.
 */
MAERet_t NOTIFIER_NotifyEx(MAE_Notifier_t *pNotifier, u32 nMask, MAEEvent_t nEvt, u32 nLParam, u32 nDParam,
	PfnEventCleanup fnClean);

#endif // __MAE_NOTIFIER_H__
