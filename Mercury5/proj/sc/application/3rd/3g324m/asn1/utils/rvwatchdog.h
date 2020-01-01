/***********************************************************************
        Copyright (c) 2002 RADVISION Ltd.
************************************************************************
NOTICE:
This document contains information that is confidential and proprietary
to RADVISION Ltd.. No part of this document may be reproduced in any
form whatsoever without written prior approval by RADVISION Ltd..

RADVISION Ltd. reserve the right to revise this publication and make
changes without obligation to notify any person of such revisions or
changes.
***********************************************************************/

#ifndef _RV_WATCHDOG_INTERNAL_H
#define _RV_WATCHDOG_INTERNAL_H

#include "rvlog.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef enum
{
    RvWatchdogInitialVal,
    RvWatchdogMaxVal,
    RvWatchdogMaxUsage,
    RvWatchdogCurrent,
    RvWatchdogDeltaVal
} RvWatchdogResourceType;



/******************************************************************************
 * RvWatchdogResourceCallback_T
 * ----------------------------------------------------------------------------
 * General: Watchdog callback for accessing resource information.
 *
 * Return Value: RV_OK  - if successful.
 *               Other on failure
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  context      - RA instance handle.
 *         resource     - The requested resource's enumeration.
 *         type         - The type of information requested.
 * Output: value        - The actual resource value.
 *****************************************************************************/
typedef RvStatus (RVCALLCONV *RvWatchdogResourceCallback_T) (
    IN  void*                       context,
    IN  RvUint32                    resource,
    IN  RvWatchdogResourceType      type,
    OUT RvUint32*                   value);


typedef void (RVCALLCONV *RvWatchdogResourceDeleteCallback_T) (
    IN void*                        context,
    IN RvUint32                     resource);



typedef struct
{
    RvBool                              initialized; /* RV_TRUE if this entry is in use */
    RvChar                              name[20]; /* Name of resource */
    RvChar                              group[10]; /* Group of this resource */
    const RvChar*                       description; /* Description of this resource */
    void*                               context; /* Context for callback */
    RvUint32                            initialValue; /* Initial value of the resource */
    RvUint32                            currentValue; /* Latest value got for this resource */
    RvWatchdogResourceCallback_T        cbFunc; /* Callback to get the resources */
    RvWatchdogResourceDeleteCallback_T  delFunc; /* Deletion function to use */
} RvWatchdogTable_S;


 /*handle to watchdog*/
typedef struct
{
     RvWatchdogTable_S*     hTable; /* Array of resources being watched */
     RvUint32               maxSize; /* Size of array */
     RvLogMgr*              logMgr; /* Log manager used */
     RvBool                 isInit; /* RV_TRUE if we initialized the use of the watchdog */
} RvWatchdog;



/******************************************************************************
 * RvWatchdogAddResource
 * ----------------------------------------------------------------------------
 * General: Add a new resource element to work with the watchdog module.
 *
 * Return Value: The resource value allocated for the new resource.
 * ----------------------------------------------------------------------------
 * Arguments:
 * Input:  hWD                      - Watchdog module handle to use.
 *         name                     - The name of the resource to use.
 *         group                    - The group this resource belongs to.
 *         description              - Short description of the resource.
 *         resourceCallback         - Callback function that is used to get the
 *                                    resource's current value.
 *         resourceDeleteCallback   - Callback function indicating this resource
 *                                    was deallocated from the watchdog.
 *         context                  - Context used for the callbacks.
 * Output: resourceEnumeration      - The enumeration of the resouce that will
 *                                    be given in callback calls.
 *****************************************************************************/
RVINTAPI int RVCALLCONV
RvWatchdogAddResource(
    IN  RvWatchdog*                         hWD,
    IN  const RvChar*                       name,
    IN  const RvChar*                       group,
    IN  const RvChar*                       description,
    IN  RvWatchdogResourceCallback_T        resourceCallback,
    IN  RvWatchdogResourceDeleteCallback_T  resourceDeleteCallback,
    IN  void*                               context,
    OUT RvUint32*                           resourceEnumeration);


/********************************************************************************
    RvWatchdogDeleteResource
    this function is called by the various modules while to delete resources from
    the watchdog.
    INPUT -
        hApp                - the application handle - used to get the watchdog
                              handle
        resourceEnumeration - the enumeration of the resource to delete
    OUTPUT - none
    RETURN -
            non negative value - if success.
            negative value     - if failed to initialize the ss instance.
*********************************************************************************/
RVINTAPI int RVCALLCONV
RvWatchdogDeleteResource(
    IN  RvWatchdog* hWD,
    IN  RvUint32    resourceEnumeration);


/********************************************************************************
    RvWatchdogAllocate
    this function allocates the internal resource table of the watchdog. it is the
    first thing initialize in this module. cmInitialize calls it at the begining
    of its operation
    INPUT -
     watchdog       - Watchdog object to initialize
     numOfResources - the numbers of resources the watchdog support. it is used
                      to determine the size of the table.
     logMgr         - log manager to use
    OUTPUT - none
    RETURN -
        Non-negative value on success, other on failure
*********************************************************************************/
RVINTAPI int RVCALLCONV
RvWatchdogAllocate(
    IN RvWatchdog*  watchdog,
    IN int          numOfResources,
    IN RvLogMgr*    logMgr);


/********************************************************************************
    RvWatchdogInit
    this it the main initialization of the watchdog.
    cmInitialize calls it after initializing all its modules.
    the function used the callback function already set in the internal table,
    and set initial and current values of each resource .
    INPUT -
        Hwd         - the watchdog handle
    OUTPUT - none
    RETURN -
            non negative value - if success.
            negative value     - if failed to initialize the ss instance.
*********************************************************************************/
RVINTAPI int RVCALLCONV
RvWatchdogInit(
    IN RvWatchdog*  Hwd);


/********************************************************************************
    RvWatchdogEnd
        this function  free allocations made in the module.
    INPUT -
     watchdog       - Watchdog object to initialize
    OUTPUT - none
    RETURN -
        Non-negative value
*********************************************************************************/
RVINTAPI int RVCALLCONV
RvWatchdogEnd(IN RvWatchdog* watchdog);


/********************************************************************************
    RvWatchdogPrint
    this function goes over all resources from the table, get thier values and
    print it at the log file.
    INPUT -
        hWD - Watchdog handle
        logSource - Log source to print to
    OUTPUT - none
    RETURN - non negative value - if success.
             negative value     - if failed to initialize the ss instance.
*********************************************************************************/
RVINTAPI int RVCALLCONV
RvWatchdogPrint(IN RvWatchdog* hWD, IN RvLogSource* logSource);


/********************************************************************************
    RvWatchdogNextResource
    this function gets the names of resources from the stack. It can be used
    to loop on all the resources of the stack with RvWatchdogGetResource().
    To stop looping, make sure the return value is non-negative.
    INPUT -
        hApp            - the application handle
        prevResource    - Handle to previous resource.
                          First time should be called with NULL
    OUTPUT -
        resourceHandle  - Handle to the current resource
                          Should be used as prevResourcefor the next call to this
                          function.
        resourceName    - Name of the resource (maximum of 40 bytes)
                          Can be used for RvWatchdogGetResource()
    RETURN - non negative value - if success.
             negative value     - if failed or if there are no more resource.
*********************************************************************************/
RVINTAPI int RVCALLCONV
RvWatchdogNextResource(
    IN  RvWatchdog* hWD,
    IN  void*       prevResource,
    OUT void**      resourceHandle,
    OUT RvChar*     resourceName);


/********************************************************************************
    RvWatchdogGetResource
    this function get the value of a specific resource and return it
    INPUT -
        hApp  - the application handle
        name  - the resource name, used to locate resource in the table
        type  - the type of data needed (current/max/....)
    OUTPUT -
        value - the value of the resource requested
        resourceGroupName - name of group this resource belongs to. Can be passed
                            as NULL. Up to 40 characters
    RETURN - non negative value - if success.
             negative value     - if failed to initialize the ss instance.
*********************************************************************************/
RVINTAPI int RVCALLCONV
RvWatchdogGetResource(
    IN  RvWatchdog*                 hWD,
    IN  const RvChar*               name,
    IN  RvWatchdogResourceType      type,
    OUT RvUint32*                   value,
    OUT RvChar*                     resourceGroupName);


#ifdef __cplusplus
}
#endif

#endif /* _RV_WATCHDOG_INTERNAL_H */
