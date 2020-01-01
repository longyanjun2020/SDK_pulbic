/*
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file 
 *   Location JBI.
 */

/**
 * @addtogroup locationClangAMLocation
 *
 * @{
 */

#ifndef ___AMLOCATIONEVENT_H___
#define ___AMLOCATIONEVENT_H___

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 *   Location acquisition completed
 *
 *   This is the event code passed to #AmNotifyLocationEvent()
 *   for notifying JBlend that the location measurement
 *   requested by #JkLocationGetLocation() is completed.
 *
 *   Designate the parameters of #AmNotifyLocationEvent() as follows:
 *   <dl>
 *    <dt><b><i>type</i></b></dt>
 *     <dd>AM_EVENT_LOCATION_GET_LOCATION_FINISHED
 *     </dd> 
 *    <dt><b><i>param1</i></b></dt>
 *     <dd>The handle of the location provider
 *         (The return value of #JkLocationOpenLocationProvider())
 *     </dd> 
 *    <dt><b><i>param2</i></b></dt>
 *     <dd>The address of the #JKLocationLocationInfo structure
 *         that contains the location information to
 *         be notified
 *     </dd>
 *   </dl>
 *   The <i>param2</i> parameter and the pointer members of the
 *   #JKLocationLocationInfo structure pointed to by <i>param2</i>
 *   must remain valid until #JkLocationReleaseLocation() is called.
 *   
 *   If an error such as location acquisition failure or structure memory allocation failure 
 *   occurs, set #JK_NULL in <i>param2</i>.
 *   In this case, JBlend throws <code>javax.microedition.location.LocationException</code>.
 *  
 */
#define AM_EVENT_LOCATION_GET_LOCATION_FINISHED 1000

/**
 *   Location acquisition timeout
 *
 *   This is the event code passed to #AmNotifyLocationEvent()
 *   for notifying JBlend that the location measurement
 *   requested by #JkLocationGetLocation() timed out.
 *
 *   Designate the parameters of #AmNotifyLocationEvent() as follows:
 *   <dl>
 *    <dt><b><i>type</i></b></dt>
 *     <dd>AM_EVENT_LOCATION_GET_LOCATION_TIMEOUT
 *     </dd> 
 *    <dt><b><i>param1</i></b></dt>
 *     <dd>The handle of the location provider
 *         (The return value of #JkLocationOpenLocationProvider())
 *     </dd> 
 *   </dl>
 */
#define AM_EVENT_LOCATION_GET_LOCATION_TIMEOUT 1001

/**
 *   Location acquisition canceled
 *
 *   This is the event code passed to #AmNotifyLocationEvent()
 *   for notifying JBlend that the location measurement
 *   requested by #JkLocationGetLocation() is canceled.
 *
 *   Designate the parameters of #AmNotifyLocationEvent() as follows:
 *   <dl>
 *    <dt><b><i>type</i></b></dt>
 *     <dd>AM_EVENT_LOCATION_GET_LOCATION_CANCELED
 *     </dd> 
 *    <dt><b><i>param1</i></b></dt>
 *     <dd>The handle of the location provider
 *         (The return value of #JkLocationOpenLocationProvider())
 *     </dd> 
 *   </dl>
 */
#define AM_EVENT_LOCATION_GET_LOCATION_CANCELED 1002

/**
 *   Location updated
 *
 *   This is the event code passed to #AmNotifyLocationEvent()
 *   for notifying JBlend of the location updates 
 *   requested by #JkLocationSetLocationListener().
 *
 *   Designate the parameters of #AmNotifyLocationEvent() as follows:
 *   <dl>
 *    <dt><b><i>type</i></b></dt>
 *     <dd>AM_EVENT_LOCATION_LOCATION_UPDATED
 *     </dd> 
 *    <dt><b><i>param1</i></b></dt>
 *     <dd>The handle of the location provider
 *         (The return value of #JkLocationOpenLocationProvider())
 *     </dd> 
 *    <dt><b><i>param2</i></b></dt>
 *     <dd>The address of the #JKLocationLocationInfo structure
 *         that contains the new location information to
 *         be notified
 *     </dd>
 *   </dl>
 *   The <i>param2</i> parameter and the pointer members of the
 *   #JKLocationLocationInfo structure pointed to by <i>param2</i>
 *   must remain valid until #JkLocationReleaseLocation() is called.
 *   
 *   If an error such as location acquisition failure or structure memory allocation failure 
 *   occurs, set #JK_NULL in <i>param2</i>.
 *   In this case, JBlend passes an invalid location information 
 *   (a <code>javax.microedition.location.Location</code> object whose <code>isValid</code> 
 *   method returns <code>false</code>) to the Java application.
 *   When the native system fails to update location information, it may notify 
 *   JBlend of an invalid information by a JKLocationLocationInfo structure whose 
 *   <i>isValid</i> member is JK_NULL. The reason of the failure can be set to 
 *   the <i>extraInfo</i> member of the structure.
 */
#define AM_EVENT_LOCATION_LOCATION_UPDATED 1003

/**
 *   LocationProvider state changed
 *
 *   This is the event code passed to #AmNotifyLocationEvent()
 *   for notifying JBlend of the state change of the location provider
 *   to which the location listener is set by #JkLocationGetLocation().
 *
 *   Designate the parameters of #AmNotifyLocationEvent() as follows:
 *   <dl>
 *    <dt><b><i>type</i></b></dt>
 *     <dd>AM_EVENT_LOCATION_PROVIDER_STATE_CHANGED
 *     </dd> 
 *    <dt><b><i>param1</i></b></dt>
 *     <dd>The handle of the location provider
 *         (The return value of #JkLocationOpenLocationProvider())
 *     </dd> 
 *    <dt><b><i>param2</i></b></dt>
 *     <dd>The new state of the location provider. Designate one of the following:
 *      <ul>
 *       <li> #JK_LOCATION_PROVIDER_STATE_AVAILABLE
 *       <li> #JK_LOCATION_PROVIDER_STATE_OUT_OF_SERVICE
 *       <li> #JK_LOCATION_PROVIDER_STATE_TEMPORARILY_UNAVAILABLE
 *      </ul>
 *         Note that no other values can be set.
 *     </dd>
 *   </dl>
 */
#define AM_EVENT_LOCATION_PROVIDER_STATE_CHANGED 1004

/**
 *   Proximity detected
 *
 *   This is the event code passed to #AmNotifyLocationEvent()
 *   for notifying JBlend that the terminal entered in a proximity
 *   that has been registered by #JkLocationAddProximity().
 *
 *   Designate the parameters of #AmNotifyLocationEvent() as follows:
 *   <dl>
 *    <dt><b><i>type</i></b></dt>
 *     <dd>AM_EVENT_LOCATION_PROXIMITY_EVENT
 *     </dd> 
 *    <dt><b><i>param1</i></b></dt>
 *     <dd>The handle of the proximity monitoring.
 *         (The return value of #JkLocationAddProximity())
 *     </dd> 
 *    <dt><b><i>param2</i></b></dt>
 *     <dd>The address of the #JKLocationLocationInfo structure
 *         that contains the location information to
 *         be notified
 *     </dd>
 *   </dl>
 *   The <i>param2</i> parameter and the pointer members of the
 *   #JKLocationLocationInfo structure pointed to by <i>param2</i>
 *   must remain valid until #JkLocationReleaseLocation() is called.
 *   
 *   If an error such as location acquisition failure or structure memory allocation failure 
 *   occurs, set #JK_NULL in <i>param2</i>.
 *   In this case, JBlend passes an invalid location information 
 *   (a <code>javax.microedition.location.Location</code> object whose <code>isValid</code> 
 *   method returns <code>false</code>) to the Java application.
 *   When the native system fails to update location information, it may notify 
 *   JBlend of an invalid information by a JKLocationLocationInfo structure whose 
 *   <i>isValid</i> member is JK_NULL. The reason of the failure can be set to 
 *   the <i>extraInfo</i> member of the structure.
 */
#define AM_EVENT_LOCATION_PROXIMITY_EVENT 1005

/**
 *   Proximity monitoring state changed
 *
 *   This is the event code passed to #AmNotifyLocationEvent()
 *   for notifying JBlend of the state change of the proximity monitoring
 *   that was requested by #JkLocationAddProximity().
 *
 *   Designate the parameters of #AmNotifyLocationEvent() as follows:
 *   <dl>
 *    <dt><b><i>type</i></b></dt>
 *     <dd>AM_EVENT_LOCATION_MONITORING_STATE_CHANGED
 *     </dd> 
 *    <dt><b><i>param1</i></b></dt>
 *     <dd>The new state of the proximity monitoring. Designate one of the following:
 *      <ul>
 *       <li> #JK_TRUE: Proximity monitoring became active
 *       <li> #JK_FALSE: Proximity monitoring became inactive by any reason
 *      </ul>
 *         Note that no other values can be set.
 *     </dd>
 *   </dl>
 */
#define AM_EVENT_LOCATION_MONITORING_STATE_CHANGED 1006

/**
 *   Notify JBlend of location related events
 *
 * @param type
 *       The event type. Designate one of the following values:
 *     <ul>
 *       <li> #AM_EVENT_LOCATION_GET_LOCATION_FINISHED
 *       <li> #AM_EVENT_LOCATION_GET_LOCATION_TIMEOUT
 *       <li> #AM_EVENT_LOCATION_GET_LOCATION_CANCELED
 *       <li> #AM_EVENT_LOCATION_LOCATION_UPDATED
 *       <li> #AM_EVENT_LOCATION_PROVIDER_STATE_CHANGED
 *       <li> #AM_EVENT_LOCATION_PROXIMITY_EVENT
 *       <li> #AM_EVENT_LOCATION_MONITORING_STATE_CHANGED
 *     </ul>
 * @param param1
 *       Parameter 1.
 *       Refer to the description of each event type for the concrete value.
 * @param param2
 *       Parameter 2.
 *       Refer to the description of each event type for the concrete value.
 * @return
 *       #JK_TRUE: succeeded <br>
 *       #JK_FALSE: failed
 *
 *  Notify JBlend of a location event by calling this function. For parameters 
 *  of each event type, refer to the definition of type values.
 *
 *  The events are queued in the event queue of JBlend. It is unpredictable 
 *  when JBlend processes the events. Thus, for the following event for which 
 *  the native system passes a pointer to the JKLocationLocationInfo structure 
 *  containing the location information, the structure must be allocated for 
 *  every notification. 
 *  When JBlend completes the processing for the structure, it calls
 *  #JkLocationReleaseLocation() to release the structure.
 *
 *  <ul>
 *    <li> #AM_EVENT_LOCATION_GET_LOCATION_FINISHED
 *    <li> #AM_EVENT_LOCATION_LOCATION_UPDATED
 *    <li> #AM_EVENT_LOCATION_PROXIMITY_EVENT
 *  </ul>
 *  If an error such as location acquisition failure or structure memory allocation failure 
 *  occurs, set #JK_NULL in the parameter for setting the address
 *  of the structure.
 *  For more information, refer to constants representing events.
 *  
 *  If this function returns #JK_FALSE, it means that the event
 *  notification failed by some reasons such as because event queue is full.
 *  In this case, the structure passed as a parameter becomes unnecessary 
 *  and must be freed by the caller (native system).
 *
 *  This function is not reentrant.
 */
JKBool AmNotifyLocationEvent(JKSint32 type, JKSint32 param1, JKSint32 param2);


#ifdef __cplusplus
}
#endif

#endif /* !___AMLOCATIONEVENT_H___ */

/** @} end of group */
