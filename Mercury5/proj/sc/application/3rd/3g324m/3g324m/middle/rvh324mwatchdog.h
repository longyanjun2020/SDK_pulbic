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

#ifndef _RV_H324M_WATCHDOG_H
#define _RV_H324M_WATCHDOG_H

#ifdef __cplusplus
extern "C" {
#endif


typedef enum
{
    RvH324mWatchdogInitialVal,
    RvH324mWatchdogMaxVal,
    RvH324mWatchdogMaxUsage,
    RvH324mWatchdogCurrent,
    RvH324mWatchdogDeltaVal
} RvH324mWatchdogResourceType;



/********************************************************************************
    RvH324mWatchdogPrint
    Gets the values of all resources in the table and prints them to the Log.
    INPUT 
	hApp   - The application handle.
    OUTPUT 
	None.
    RETURN - Non-negative value in case of success.
             A negative value if the function failed to initialize the ss instance.
*********************************************************************************/
RVAPI int RVCALLCONV RvH324mWatchdogPrint(IN HAPP hApp);


/********************************************************************************
    RvH324mWatchdogNextResource
    Gets the names of resources from the 3G-324M Stack. It can be used
    to loop all resources of the Stack with RvH324mWatchdogGetResource().
    To stop looping, make sure the return value is non-negative.
    INPUT -
        hApp            - The application handle.
        prevResource    - Handle to the previous resource.
                          The first time around it should be called with NULL.
    OUTPUT -
        resourceHandle  - Handle to the current resource.
                          This parameter should be used as prevResource for 
						  the next call to this function.
        resourceName    - Name of the resource (maximum of 40 bytes).
                          This parameter can be used for RvH324mWatchdogGetResource().
    RETURN - A non-negative value in case of success.
             A negative value if failed or if no more resource exist.
*********************************************************************************/
RVAPI int RVCALLCONV RvH324mWatchdogNextResource(
    IN  HAPP    hApp,
    IN  void*   prevResource,
    OUT void**  resourceHandle,
    OUT char*   resourceName);


/********************************************************************************
RvH324mWatchdogGetResource
Gets the value of a specific resource and returns it.
    INPUT -
        hApp  - The application handle.
        name  - The resource name, used to locate the resource in the table.
        type  - The type of data needed (current/max/....).
    OUTPUT -
        value - The value of the requested resource.
        resourceGroupName - The name of the group to which this resource belongs. 
                            Can be passedCan be passed as NULL. Up to 40 characters.
    RETURN - A non-negative value in case of success.
             A negative value if the function failed to initialize the ss instance.
*********************************************************************************/
RVAPI int RVCALLCONV RvH324mWatchdogGetResource(
    IN  HAPP                        hApp,
    IN  const char*                 name,
    IN  RvH324mWatchdogResourceType type,
    OUT RvUint32*                   value,
    OUT char*                       resourceGroupName);


#ifdef __cplusplus
}
#endif


#endif /* _RV_H324M_WATCHDOG_H */
