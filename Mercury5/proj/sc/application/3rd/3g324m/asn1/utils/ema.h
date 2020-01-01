/***********************************************************************
        Copyright (c) 2003 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

/*
  ema.h

  RADVISION static array implementation.

  The EMA module provides the Enhanced Memory Allocation services that RA provides, with
  several additional features:

  1. Knowledge about the type of handle in EMA.
     An EMA element can be checked for its type using emaGetType()
  2. Reference counts
     Each element has a reference count that can be accessed through emaIncRefCount() and
     emaDefRefCount().
  3. Auto-lock
     EMA will automatically lock itself on functions that need thread-safety (such as
     emaAdd).
  4. Explicit element locks

  EMA can also be used to link elements from different types to the same locks are reference
  counts. It is done in CM to link the channels of the call to the call, allowing easier
  locking and reference counting mechanisms.

  Written by Tsahi Levent-Levi

*/


#ifndef _EMA_H
#define _EMA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rvwatchdog.h"
#include "ra.h"

#if defined(RV_DEBUG)
#define RV_EMA_DEBUG
#endif


/* Handle to an EMA object */
RV_DECLARE_HANDLE(HEMA);


/* EMA element pointer declaration */
typedef void *EMAElement;



/************************************************************************
 * emaStatistics struct
 * elems        - Statistics about the elements inside EMA
 * numMarked    - Number of items that are marked and deleted, not released
 *                yet.
 ************************************************************************/
typedef struct
{
    RvRaStatistics    elems;
    RvUint32            numMarked;
} emaStatistics;


/************************************************************************
 * emaLockType enum
 * emaNoLocks       - EMA is not using locks at all. It does use referece
 *                    counts. It will only use a general lock to lock when
 *                    adding and deleting elements
 * emaNormalLocks   - EMA uses locks and reference counts in a "normal" way
 * emaLinkedLocks   - EMA's locks and reference counts are linked to another
 *                    EMA object, which holds different types of information.
 ************************************************************************/
typedef enum
{
    emaNoLocks,
    emaNormalLocks,
    emaLinkedLocks,
    emaLockPointers
} emaLockType;


/************************************************************************
 * EMAFunc
 * purpose: Definition of a general function on an EMA element
 * input  : elem    - Element to function on
 *          param   - Context to use for it
 * output : none
 * return : Pointer for the context to use on the next call to this
 *          EMAFunc.
 ************************************************************************/
typedef void*(*EMAFunc)(EMAElement elem, void *param);


/************************************************************************
 * emaEvElementIdle
 * purpose: Event function called when the element is idle
 * input  : elem      - the idle element
 *          bDeleting - if true, we are now deleting the element,
 *                      otherwise, it is just idle
 * output : none
 * return : none
 ************************************************************************/
typedef void (RVCALLCONV *emaEvElementIdle)(EMAElement * elem, RvBool bDeleting);


/************************************************************************
 * emaConstruct
 * purpose: Create an EMA object
 * input  : elemSize            - Size of elements in the EMA in bytes
 *          maxNumOfElements    - Number of elements in EMA
 *          lockType            - Type of locking mechanism to use
 *          name                - Name of EMA (used in log messages)
 *          type                - Integer representing the type of objects
 *                                stored in this EMA.
 *          userData            - User related information associated with
 *                                this EMA object.
 *          instance            - Instance associated with this EMA object.
 *          logMgr              - Log manager to use.
 * output : none
 * return : Handle to RA constructed on success
 *          NULL on failure
 ************************************************************************/
RVINTAPI HEMA RVCALLCONV
emaConstruct(
    IN int          elemSize,
    IN int          maxNumOfElements,
    IN emaLockType  lockType,
    IN const char*  name,
    IN RvUint32     type,
    IN void*        userData,
    IN void const*  instance,
    IN RvLogMgr*    logMgr);


/************************************************************************
 * emaDestruct
 * purpose: Free an EMA object, deallocating all of its used memory
 * input  : emaH   - Handle of the EMA object
 * output : none
 * return : none
 ************************************************************************/
RVINTAPI void RVCALLCONV
emaDestruct(IN HEMA emaH);


/************************************************************************
 * emaClear
 * purpose: Clear EMA from all used objects
 * input  : emaH   - Handle of the EMA object
 * output : none
 * return : none
 ************************************************************************/
RVINTAPI void RVCALLCONV
emaClear(IN HEMA emaH);


/************************************************************************
 * emaAdd
 * purpose: Allocate an element in EMA for use, without initializing its
 *          value.
 *          This automatically locks the EMA object.
 * input  : emaH        - Handle of the EMA object
 *          appHandle   - Application's handle for the element
 * output : none
 * return : Pointer to element added on success
 *          NULL on failure
 ************************************************************************/
RVINTAPI EMAElement RVCALLCONV
emaAdd(IN HEMA emaH, IN void* appHandle);


/************************************************************************
 * emaDelete
 * purpose: Delete an element from EMA
 *          Must be called when the element is locked
 * input  : elem    - Element to delete
 * return : Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaDelete(IN EMAElement elem);


/************************************************************************
 * emaRaiseIdle
 * purpose: Delete an element from EMA
 *          Must be called when the element is locked
 * input  : elem    - Element to delete
 * return : Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaRaiseIdle(IN EMAElement elem);


/************************************************************************
 * emaLinkToElement
 * purpose: Link an EMA element to another element, from a different
 *          EMA construct. This function should be used when the EMA we're
 *          dealing with was created with emaLinkedLocks. This function
 *          allows the element to use a different element's lock.
 *          This function will only work if the element has no reference
 *          count at present.
 * input  : elem        - Element to link
 *          otherElem   - Element we're linking to. Should be constructed
 *                        with emaNormalLocks or linked to such element.
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaLinkToElement(IN EMAElement elem, IN EMAElement otherElem);


/************************************************************************
 * emaSetLockPointer
 * purpose: Set an EMA element to use a given lock. This function should
 *          be used when the EMA we're dealing with was created with
 *          emaLockPointers.
 * input  : elem        - Element to link
 *          lockPointer - Pointer to the lock to use.
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaSetLockPointer(IN EMAElement elem, IN void * lockPointer);


/************************************************************************
 * emaUseLockPointer
 * purpose: Get the lock pointer used by an EMA element This function
 *          should be used when the EMA we're dealing with was created
 *          with emaLockPointers.
 * input  : elem        - Element to link
 * output : lockPointer - Pointer to the lock used
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaGetLockPointer(IN EMAElement elem, OUT void ** lockPointer);


/************************************************************************
 * emaLock
 * purpose: Lock an element in EMA for use from the executing thread only
 *          This function will succeed only if the element exists
 * input  : elem    - Element to lock
 * output : none
 * return : RV_TRUE    - When the element exists and was locked
 *          RV_FALSE   - When the element doesn't exist (NULL are was deleted)
 *                    In this case, there's no need to call emaUnlock().
 ************************************************************************/
RVINTAPI RvBool RVCALLCONV
emaLock(IN EMAElement elem);


/************************************************************************
 * emaUnlock
 * purpose: Unlock an element in EMA that were previously locked by
 *          emaLock() from the same thread
 * input  : elem    - Element to unlock
 * output : none
 * return : RV_TRUE    if element still exists
 *          RV_FALSE   if element was deleted and is not valid anymore
 *          Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaUnlock(IN EMAElement elem);


/************************************************************************
 * emaMark
 * purpose: Mark an element in EMA for use, not letting anyone delete
 *          this element until it is release.
 *          This automatically locks the EMA object.
 * input  : elem    - Element to mark
 * output : none
 * return : Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaMark(IN EMAElement elem);


/************************************************************************
 * emaMarkLocked
 * purpose: Mark an element in EMA for use, not letting anyone delete
 *          this element until it is release.
 *          This does NOT lock the EMA object.
 * input  : elem    - Element to mark
 * output : none
 * return : RV_TRUE    - When the element exists and was locked
 *          RV_FALSE   - When the element doesn't exist (NULL are was deleted)
 *                       In this case, there's no need to call emaReleaseWhileLocked().
 ************************************************************************/
RVINTAPI RvBool RVCALLCONV
emaMarkLocked(IN EMAElement elem);


/************************************************************************
 * emaRelease
 * purpose: Release an element in EMA after it was marked using
 *          emaMark(), returning an indication if this element
 *          still exists.
 *          This automatically locks the EMA object.
 * input  : elem    - Element to mark
 * output : none
 * return : RV_TRUE    if element still exists
 *          RV_FALSE   if element was deleted and is not valid anymore
 *          Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaRelease(IN EMAElement elem);


/************************************************************************
 * emaLockedRelease
 * purpose: Release an element in EMA after it was marked using
 *          emaMark(), returning an indication if this element
 *          still exists.
 *          This does NOT lock the EMA object.
 * input  : elem    - Element to mark
 * output : none
 * return : RV_TRUE    if element still exists
 *          RV_FALSE   if element was deleted and is not valid anymore
 *          Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaReleaseLocked(IN EMAElement elem);


/************************************************************************
 * emaWasDeleted
 * purpose: Check if an element in EMA was deleted after a call to
 *          emaMark().
 * input  : elem    - Element to check
 * output : none
 * return : RV_TRUE    if element was deleted
 *          RV_FALSE   if element still exists
 ************************************************************************/
RVINTAPI RvBool RVCALLCONV
emaWasDeleted(IN EMAElement elem);


/************************************************************************
 * emaGetLockCount
 * purpose: Get the lock count for an element in EMA (must be locked).
 * input  : elem    - Element to get the locks for
 * output : none
 * return : number of locks
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaGetLockCount(IN EMAElement elem);


/************************************************************************
 * emaPrepareForCallback
 * purpose: Prepare an element in EMA for use in a callback to the app.
 *          This function will make sure the element is unlocked the necessary
 *          number of times, and then marked once (so the app won't delete
 *          this element).
 *          emaReturnFromCallback() should be called after the callback,
 *          with the return value of this function.
 * input  : elem    - Element to prepare
 * output : none
 * return : Number of times the element was locked on success
 *          Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaPrepareForCallback(IN EMAElement elem);


/************************************************************************
 * emaReturnFromCallback
 * purpose: Make sure the EMA element knows it has returned from a
 *          callback. This function will ensure that the element is
 *          locked again with the specified number of times. It will also
 *          release the element, and if timersLocked==0, and the element
 *          was deleted by the app in the callback, the element will also
 *          be permanently deleted.
 * input  : elem    - Element to prepare
 * output : none
 * return : RV_TRUE    if element still exists
 *          RV_FALSE   if element was deleted and is not valid anymore
 *          Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaReturnFromCallback(IN EMAElement elem, IN int timesLocked);


/************************************************************************
 * emaSetApplicationHandle
 * purpose: Set the application handle of an element in EMA
 * input  : elem        - Element in EMA
 *          appHandle   - Application's handle for the element
 * output : none
 * return : Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaSetApplicationHandle(IN EMAElement elem, IN void* appHandle);


 /************************************************************************
 * emaGetApplicationHandle
 * purpose: Get the application's handle of an element in EMA
 * input  : elem        - Element in EMA
 * output : appHandle   - Application's handle for the element
 * return : Pointer to the application handle
 *          NULL on failure
 ************************************************************************/
RVINTAPI void * RVCALLCONV
emaGetApplicationHandle(IN EMAElement elem);


/************************************************************************
 * emaGetType
 * purpose: Return the type of the element inside the EMA object.
 *          This is the type given in emaConstruct().
 * input  : elem    - Element in EMA
 * output : none
 * return : The element's type on success
 *          0 on failure
 ************************************************************************/
RVINTAPI RvUint32 RVCALLCONV
emaGetType(IN EMAElement elem);


/************************************************************************
 * emaGetUserData
 * purpose: Return the user related data of the element inside the EMA
 *          object. This is the userData given in emaConstruct().
 * input  : elem    - Element in EMA
 * output : none
 * return : The element's user data pointer on success
 *          NULL on failure
 ************************************************************************/
RVINTAPI void* RVCALLCONV
emaGetUserData(IN EMAElement elem);

/************************************************************************
 * emaGetUserDataByInstance
 * purpose: Return the user related data inside the EMA object, by the
 *          EMA instance returned by emaConstruct().
 *          This is the userData given in emaConstruct().
 * input  : emaH   - handle to the EMA
 * output : none
 * return : The user data pointer on success
 *          NULL on failure
 ************************************************************************/
void* emaGetUserDataByInstance(IN HEMA emaH);

/************************************************************************
 * emaGetInstance
 * purpose: Return the instance of this EMA element.
 *          This is the instance given in emaConstruct().
 * input  : elem    - Element in EMA
 * output : none
 * return : The element's instance on success
 *          NULL on failure
 ************************************************************************/
RVINTAPI void const* RVCALLCONV
emaGetInstance(IN EMAElement elem);


/************************************************************************
 * emaGetObject
 * purpose: Return the EMA object this element is in
 * input  : elem    - Element in EMA
 * output : none
 * return : The element's EMA object on success
 *          NULL on failure
 ************************************************************************/
HEMA emaGetObject(IN EMAElement elem);


/************************************************************************
 * emaSetIdleEvent
 * purpose: Set a function to be called when an object is idle
 * input  : emaH        - Handle of the EMA object
 *          pIdleEv     - Event to be called on idle element
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaSetIdleEvent(
    IN HEMA     emaH,
    IN emaEvElementIdle  pIdleEv);


/************************************************************************
 * emaDoAll
 * purpose: Call a function on all used elements in EMA
 * input  : emaH        - Handle of the EMA object
 *          func        - Function to execute on all elements
 *          param       - Context to use when executing the function
 * output : none
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaDoAll(
    IN HEMA     emaH,
    IN EMAFunc  func,
    IN void*    param);


/************************************************************************
 * emaGetNext
 * purpose: Get the next used element in EMA.
 *          This function can be used to implement search or "doall"
 *          functions on EMA.
 * input  : emaH        - Handle of the EMA object
 *          cur         - Current EMA element whose next we're looking for
 *                        If NULL, then emaGetNext() will return the first
 *                        used element.
 * output : none
 * return : Pointer to the next used element on success
 *          NULL when no more used elements are left
 ************************************************************************/
RVINTAPI EMAElement RVCALLCONV
emaGetNext(
    IN HEMA         emaH,
    IN EMAElement   cur);


/************************************************************************
 * emaGetIndex
 * purpose: Returns the index of the element in the ema
 * input  : elem    - Element in EMA
 * output : none
 * return : The element's index on success
 *          Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaGetIndex(IN EMAElement elem);


/************************************************************************
 * emaGetByIndex
 * purpose: Returns the ema element by its index.
 *          This function does not check if the element is vacant or not.
 * input  : emaH    - Handle of the EMA object
 *          index   - Index of element searched
 * output : none
 * return : Pointer to the element on success
 *          NULL on failure
 ************************************************************************/
RVINTAPI EMAElement RVCALLCONV
emaGetByIndex(
    IN HEMA emaH,
    IN int  index);


/************************************************************************
 * emaGetStatistics
 * purpose: Get statistics information about EMA.
 *          The number of used items also includes those deleted, but still
 *          marked.
 * input  : emaH        - Handle of the EMA object
 * output : stats       - Statistics information
 * return : Non-negative value on success
 *          Negative value on failure
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaGetStatistics(IN HEMA emaH, OUT emaStatistics* stats);


/************************************************************************
 * emaIsVacant
 * purpose: Returns whether the given object is free for allocation
 * input  : elem    - Element in EMA
 * output : none
 * return : RV_TRUE  - if the elemnt is not allocated
 *          RV_FALSE - otherwise
 ************************************************************************/
RVINTAPI int RVCALLCONV
emaIsVacant(IN EMAElement elem);


/******************************************************************************
 * emaAddWatchdogResource
 * ----------------------------------------------------------------------------
 * General: Add an EMA instance as a resource handled by the watchdog.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  emaH         - EMA instance handle.
 *         watchdog     - The watchdog instance to add this EMA to.
 *         name         - Name of resource to use.
 *         group        - Group name for this resource.
 *         description  - Short description about this resource.
 *****************************************************************************/
RVINTAPI RvStatus RVCALLCONV
emaAddWatchdogResource(
    IN HEMA         emaH,
    IN RvWatchdog   *watchdog,
    IN const char   *name,
    IN const char   *group,
    IN const char   *description);




#if defined(RV_EMA_DEBUG)

#define emaLock(elem) emaLockDebug(elem, __FILE__, __LINE__)
#define emaUnlock(elem) emaUnlockDebug(elem, __FILE__, __LINE__)
#define emaMark(elem) emaMarkDebug(elem, __FILE__, __LINE__)
#define emaMarkLocked(elem) emaMarkLockedDebug(elem, __FILE__, __LINE__)
#define emaRelease(elem) emaReleaseDebug(elem, __FILE__, __LINE__)
#define emaReleaseLocked(elem) emaReleaseLockedDebug(elem, __FILE__, __LINE__)
#define emaPrepareForCallback(elem) emaPrepareForCallbackDebug(elem, __FILE__, __LINE__)
#define emaReturnFromCallback(elem, timesLocked) emaReturnFromCallbackDebug(elem, timesLocked, __FILE__, __LINE__)
#define emaDelete(elem) emaDeleteDebug(elem, __FILE__, __LINE__)
#define emaRaiseIdle(elem) emaRaiseIdleDebug(elem, __FILE__, __LINE__)

RVINTAPI RvBool RVCALLCONV
emaLockDebug(IN EMAElement elem, IN const char* filename, IN int lineno);

RVINTAPI int RVCALLCONV
emaUnlockDebug(IN EMAElement elem, IN const char* filename, IN int lineno);

RVINTAPI int RVCALLCONV
emaMarkDebug(IN EMAElement elem, IN const char* filename, IN int lineno);

RVINTAPI RvBool RVCALLCONV
emaMarkLockedDebug(IN EMAElement elem, IN const char* filename, IN int lineno);

RVINTAPI int RVCALLCONV
emaReleaseDebug(IN EMAElement elem, IN const char* filename, IN int lineno);

RVINTAPI int RVCALLCONV
emaReleaseLockedDebug(IN EMAElement elem, IN const char* filename, IN int lineno);

RVINTAPI int RVCALLCONV
emaPrepareForCallbackDebug(IN EMAElement elem, IN const char* filename, IN int lineno);

RVINTAPI int RVCALLCONV
emaReturnFromCallbackDebug(IN EMAElement elem, IN int timesLocked, IN const char* filename, IN int lineno);

RVINTAPI int RVCALLCONV
emaDeleteDebug(IN EMAElement elem, IN const char* filename, IN int lineno);

RVINTAPI int RVCALLCONV
emaRaiseIdleDebug(IN EMAElement elem, IN const char* filename, IN int lineno);

#endif  /* RV_EMA_DEBUG */




#ifdef __cplusplus
}
#endif

#endif  /* _EMA_H */


