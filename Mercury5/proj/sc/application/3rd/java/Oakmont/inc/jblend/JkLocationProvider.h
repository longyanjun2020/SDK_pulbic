/*
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file
 *   LocationProvider JSI
 */

#ifndef ___JKLOCATIONPROVIDER_H___
#define ___JKLOCATIONPROVIDER_H___

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkLocationCommon.h"

/**
 * @addtogroup location_LocationProvider
 *
 * @{
 */

/**
 *   Location provider handle type
 */
typedef JKHandle JKLocationProviderHandle;

/**
 *   Proximity handle type
 */
typedef JKHandle JKLocationProximityHandle;

/**
 *   Criterion for selecting a location method: No requirement
 *
 *   This is used as a value to be set in #JKLocationCriteria structure.
 */
#define JK_LOCATION_CRITERIA_NO_REQUIREMENT 0

/**
 *   Criterion for selecting a location method: Only low power consumption allowed
 *
 *   This is used as a value for the <i>preferredPowerConsumption</i>
 *   member of #JKLocationCriteria structure.
 */
#define JK_LOCATION_CRITERIA_POWER_USAGE_LOW 1

/**
 *   Criterion for selecting a location method: Average power consumption allowed
 *
 *   This is used as a value for the <i>preferredPowerConsumption</i>
 *   member of #JKLocationCriteria structure.
 */
#define JK_LOCATION_CRITERIA_POWER_USAGE_MEDIUM 2

/**
 *   Criterion for selecting a location method: High power consumption allowed
 *
 *   This is used as a value for the <i>preferredPowerConsumption</i>
 *   member of #JKLocationCriteria structure.
 */
#define JK_LOCATION_CRITERIA_POWER_USAGE_HIGH 3

/**
 *   Location method (technology bit): Satellite
 *
 *   Using satellite as the location method.
 *   (e.g. Global Positioning System (GPS))
 *
 *   This is used as a value for the <i>locationMethod</i>
 *   member of #JKLocationLocationInfo structure.
 */
#define JK_LOCATION_METHOD_MTE_SATELLITE      0x00000001

/**
 *   Location method (technology bit): Time difference
 *
 *   Using time difference of the signal as the location method.
 *   (e.g. Enhanced Observed Time Difference (E-OTD))
 *
 *   This is used as a value for the <i>locationMethod</i>
 *   member of #JKLocationLocationInfo structure.
 */
#define JK_LOCATION_METHOD_MTE_TIMEDIFFERENCE 0x00000002

/**
 *   Location method (technology bit): Time of arrival
 *
 *   Using time of arrival (TOA) of the signal as the location method.
 *
 *   This is used as a value for the <i>locationMethod</i>
 *   member of #JKLocationLocationInfo structure.
 */
#define JK_LOCATION_METHOD_MTE_TIMEOFARRIVAL  0x00000004

/**
 *   Location method (technology bit): Cell ID
 *
 *   Using cell ID as the location method. (e.g. Cell Global Identity (CGI))
 *
 *   This is used as a value for the <i>locationMethod</i>
 *   member of #JKLocationLocationInfo structure.
 */
#define JK_LOCATION_METHOD_MTE_CELLID         0x00000008

/**
 *   Location method (technology bit): Short range
 *
 *   Using short-range positioning system as the location method.
 *   (e.g. Bluetooth LP)
 *
 *   This is used as a value for the <i>locationMethod</i>
 *   member of #JKLocationLocationInfo structure.
 */
#define JK_LOCATION_METHOD_MTE_SHORTRANGE     0x00000010

/**
 *   Location method (technology bit): Angle of arrival
 *
 *   Using angle of arrival of the signal as the location method.
 *
 *   This is used as a value for the <i>locationMethod</i>
 *   member of #JKLocationLocationInfo structure.
 */
#define JK_LOCATION_METHOD_MTE_ANGLEOFARRIVAL 0x00000020

/**
 *   Location method (method type): Terminal based
 *
 *   Positioning calculation is performed mainly by the terminal.
 *
 *   Do not set this value in conjunction with
 *   #JK_LOCATION_METHOD_MTY_NETWORKBASED. Neither should be set
 *   if method type is uncertain.
 *
 *   This is used as a value for the <i>locationMethod</i>
 *   member of #JKLocationLocationInfo structure.
 */
#define JK_LOCATION_METHOD_MTY_TERMINALBASED  0x00010000

/**
 *   Location method (method type): Network based
 *
 *   Positioning calculation is performed mainly by the network.
 *
 *   Do not set this value in conjunction with
 *   #JK_LOCATION_METHOD_MTY_TERMINALBASED. Neither should be set
 *   if method type is uncertain.
 *
 *   This is used as a value for the <i>locationMethod</i>
 *   member of #JKLocationLocationInfo structure.
 */
#define JK_LOCATION_METHOD_MTY_NETWORKBASED   0x00020000

/**
 *   Location method (assistance information): Assisted
 *
 *   Positioning calculation is performed with assistance of the other.
 *   (i.e. Network, for terminal based. Terminal, for network based.)
 *
 *   Do not set this value in conjunction with
 *   #JK_LOCATION_METHOD_MTA_UNASSISTED. Neither should be set
 *   if method type is uncertain.
 *
 *   This is used as a value for the <i>locationMethod</i>
 *   member of #JKLocationLocationInfo structure.
 */
#define JK_LOCATION_METHOD_MTA_ASSISTED       0x00040000

/**
 *   Location method (assistance information): Un assisted
 *
 *   Positioning calculation is performed with no assistance of the other.
 *   (i.e. Network, for terminal based. Terminal, for network based.)
 *
 *   Do not set this value in conjunction with
 *   #JK_LOCATION_METHOD_MTA_ASSISTED. Neither should be set
 *   if method type is uncertain.
 *
 *   This is used as a value for the <i>locationMethod</i>
 *   member of #JKLocationLocationInfo structure.
 */
#define JK_LOCATION_METHOD_MTA_UNASSISTED     0x00080000

/**
 *   The state of the location provider: Available
 *
 *   This value is used as a return value of #JkLocationGetProviderState()
 *   and is also used by the location listener as an event code that indicates that
 *   the location provider state has changed.
 */
#define JK_LOCATION_PROVIDER_STATE_AVAILABLE               1

/**
 *   The state of the location provider: Temporarily unavailable
 *
 *   This value is used as a return value of #JkLocationGetProviderState()
 *   and is also used by the location listener as an event code that indicates that
 *   the location provider state has changed.
 */
#define JK_LOCATION_PROVIDER_STATE_TEMPORARILY_UNAVAILABLE 2

/**
 *   The state of the location provider: Out of service
 *
 *   This value is used as a return value of #JkLocationGetProviderState()
 *   and is also used by the location listener as an event code that indicates that
 *   the location provider state has changed.
 */
#define JK_LOCATION_PROVIDER_STATE_OUT_OF_SERVICE          3

/**
 *   A data structure to store criteria
 *
 *   This structure represents the criteria for selecting a location method and
 *   is used as a parameter of #JkLocationOpenLocationProvider().
 */
typedef struct JKLocationCriteria {
    /**
     *   Horizontal accuracy
     *
     *   Horizontal accuracy preference is specified as the maximum allowed standard
     *   deviation of the error in
     *   meters. #JK_LOCATION_CRITERIA_NO_REQUIREMENT for this value
     *   means no preference.
     */
    JKSint32 horizontalAccuracy;

    /**
     *   Vertical accuracy
     *
     *   Vertical accuracy preference is specified as the maximum allowed standard
     *   deviation of the error in
     *   meters. #JK_LOCATION_CRITERIA_NO_REQUIREMENT for this value
     *   means no preference.
     */
    JKSint32 verticalAccuracy;

    /**
     *   Response time
     *
     *   Maximum response time preference in
     *   milliseconds. #JK_LOCATION_CRITERIA_NO_REQUIREMENT for this
     *   value means no preference.
     */
    JKSint32 preferredResponseTime;

    /**
     *   Power consumption
     *
     *   Power consumption preference in one of the following values:
     *   <ul>
     *     <li> #JK_LOCATION_CRITERIA_NO_REQUIREMENT
     *     <li> #JK_LOCATION_CRITERIA_POWER_USAGE_LOW
     *     <li> #JK_LOCATION_CRITERIA_POWER_USAGE_MEDIUM
     *     <li> #JK_LOCATION_CRITERIA_POWER_USAGE_HIGH
     *   </ul>
     *   There is no concrete criterion specified for the LOW, MEDIUM, and HIGH.
     */
    JKSint32 preferredPowerConsumption;

    /**
     *   Cost allowance
     *
     *   A boolean that indicates whether the requests for location determination
     *   is allowed to incur any financial cost to the end user.
     */
    JKBool costAllowed;

    /**
     *   Speed and course requirement
     *
     *   A boolean which indicates whether the location provider should be able
     *   to determine speed and course.
     */
    JKBool speedAndCourseRequired;

    /**
     *   Altitude requirement
     *
     *   A boolean which indicates whether the location provider should be able
     *   to determine altitude.
     */
    JKBool altitudeRequired;

    /**
     *   AddressInfo requirement
     *
     *   A boolean which indicates whether the location provider should be able
     *   to determine textual address information.
     */
    JKBool addressInfoRequired;
} JKLocationCriteria;

/**
 *   A data structure to store an extra information about a location
 *
 *   This structure is used to pass an extra information about an
 *   address information, from the native system to JBlend.
 *   If there are any extra information available, instantiate
 *   this structure for each information and set its address in
 *   the <i>extraInfo</i> member of JKLocationLocationInfo structure.
 *
 *   An extra information consists of a pair of MIME type and a
 *   string value indicating the data of that type.
 *
 *   JSR-179 defines following MIME types:
 *   <ul>
 *     <li> application/X-jsr179-location-nmea<br>
 *         The NMEA sentence of the location. NMEA sentence is defined
 *         in NMEA 0183 v3.1.
 *     <li> application/X-jsr179-location-lif<br>
 *         The XML formatted document containing the "pd" element
 *         defined in the LIF Mobile Location Protocol TS 101 v3.0.0.
 *         as the root element of the ducument.
 *     <li> text/plain<br>
 *         A textual extra information that can be displayed to the
 *         end user.
 *   </ul>
 */
typedef struct JKLocationExtraInfo {
    /**
     *   MIME type
     *
     *   The MIME type of this extra information.
     */
    JKLocationString mimetype;

    /**
     *   Value
     *
     *   The string value of this extra information.
     */
    JKLocationString value;
} JKLocationExtraInfo;

/**
 *   A data structure to store a location information
 *
 *   This structure is used to pass a location information from JBlend
 *   to the native system.
 */
typedef struct JKLocationLocationInfo {
    /**
     *   Validity flag
     *
     *   A boolean that indicates validity of this location
     *   information. #JK_TRUE is set if this structure contains a valid
     *   information. #JK_FALSE, otherwise. In case of #JK_FALSE, the
     *   reason can be indicated in the <i>extraInfo</i> member.
     */
    JKBool isValid;

    /**
     *   Location method
     *
     *   The location method used to get this location information.
     *   A bit-wise OR of the constants that have the prefix
     *   JK_LOCATION_METHOD_. Set each of the technology bits
     *   (constant having prefix JK_LOCATION_METHOD_MTE), the method types
     *   (constant having prefix JK_LOCATION_METHOD_MTY) and
     *   the assistance information (constant having prefix
     *   JK_LOCATION_METHOD_MTA), respectively.
     */
    JKUint32 locationMethod;

    /**
     *   Time stamp(high)
     *
     *   The higher 32 bits of time stamp at when this location information is
     *   obtained. Set the measurement time as accurate as
     *   possible. The time should be denoted as milliseconds from
     *   EPOC (Jan. 1st, 1970 (GMT)).
     */
    JKUint32 timestamp_high;

    /**
     *   Time stamp(low)
     *
     *   The lower 32 bits of time stamp at when this location information is
     *   obtained. Set the measurement time as accurate as
     *   possible. The time should be denoted as milliseconds from
     *   EPOC (Jan. 1st, 1970 (GMT)).
     */
    JKUint32 timestamp_low;

    /**
     *   Speed
     *
     *   The ground speed of the terminal at the time of measurement in
     *   meters per second (m/s). The speed must be positive, and
     *   can be NaN (Not a Number) in case the speed is unknown.
     */
    float speed;

    /**
     *   Course
     *
     *   The course of the terminal at the time of measurement in
     *   degrees relative to true north. The valid range is [0.0,
     *   360.0) and can be NaN (Not a Number) in case the course is
     *   unknown.
     */
    float course;

    /**
     *   Coordinates
     *
     *   The coordinates of the terminal. Set the <i>isValid</i> member #JK_FALSE,
     *   if unknown.
     */
    JKLocationCoordinates coordinates;

    /**
     *   Address information
     *
     *   The address information associated with this location. Set the <i>isValid</i>
     *   member #JK_FALSE, if unknown.
     */
    JKLocationAddressInfo addressInfo;

    /**
     *   The number of extra information units.
     *
     *   The number of extra information units associated with this location.
     */
    JKSint32 numExtraInfo;

    /**
     *   ExtraInfo
     *
     *   A pointer to the <i>JKLocationExtraInfo</i> array that contains
     *   extra information associated with this location.
     *   The array element count must be the same as <i>numExtraInfo</i>.
     */
    JKLocationExtraInfo *extraInfo;
} JKLocationLocationInfo;

/**
 *   A data structure to store a proximity
 *
 *   This structure represents an area used for proximity monitoring and
 *   is used as a parameter of #JkLocationAddProximity().
 */
typedef struct JKLocationProximity {
    /**
     *   The center coordinates
     *
     *   The center coordinates of this proximity.
     */
    JKLocationCoordinates coordinates;

    /**
     *   Proximity radius
     *
     *   The radius of this proximity in meters.
     */
    float proximityRadius;
} JKLocationProximity;

/**
 *   Opens a location provider
 *
 * @param criteria
 *       A pointer to the JKLocationCriteria structure containing the criteria
 *       for selecting a location method.
 * @return
 *       If the operation succeeds, return the handle of the location provider.
 *       The handle must be a unique and positive value.
 *       If the operation fails, return an appropriate value as described below.
 *
 *   Open a location provider that fulfills the given criteria and return
 *   its handle. If there are no location providers other than those do
 *   not fulfil the Criteria, return #JK_NULL. If all the
 *   location providers are in "out of service" state regardless of
 *   the criteria, return #JK_INVALID_HANDLE. If, however, the
 *   location provider that fulfills the criteria is in "temporarily
 *   unavailable" state, return its valid handle. Refer to the
 *   description of #JkLocationGetProviderState() for classification
 *   of the location provider states.
 *
 *   If there is already an opened location provider that fulfills the
 *   criteria, whether to return the same handle or a new handle is implementation
 *   dependent. One location provider can have only one location listener.
 *   You therefore must return the same handle if the native system allows
 *   only one location listener in the system at a time.
 *
 *   Do not attempt to perform time consuming operation, such as
 *   initializing the location method, in this function. This function
 *   must immediately return the handle of the location listener.
 * @see #JkLocationGetProviderState()
 * @see #JkLocationGetLocation()
 * @see #JkLocationSetLocationListener()
 */
JKLocationProviderHandle JkLocationOpenLocationProvider(const JKLocationCriteria *criteria);

/**
 *   Closes a location provider
 *
 * @param hProvider
 *       The handle of the location provider. The value returned by
 *       #JkLocationOpenLocationProvider() is designated.
 *
 *   Close the location provider indicated by the <i>hProvider</i> parameter.
 *
 *   In this function, cancel ongoing location measurement and
 *   registered location listener, if any.
 */
void JkLocationCloseLocationProvider(JKLocationProviderHandle hProvider);

/**
 *   Gets the location provider state.
 *
 * @param hProvider
 *       The handle of the location provider. The value returned by
 *       #JkLocationOpenLocationProvider() is designated.
 * @return
 *       Return one of the following values as the state of the location provider:
 *       <ul>
 *         <li> #JK_LOCATION_PROVIDER_STATE_AVAILABLE<br>
 *             Available
 *         <li> #JK_LOCATION_PROVIDER_STATE_OUT_OF_SERVICE<br>
 *             Out of service
 *         <li> #JK_LOCATION_PROVIDER_STATE_TEMPORARILY_UNAVAILABLE<br>
 *             Temporarily unavailable
 *       </ul>
 *       Note that no other values can be returned.
 * <p>
 *   Return the current state of the location provider designated by the
 *   <i>hProvider</i> parameter.
 *
 *   The state "out of service" means that the method is unavailable
 *   and the implementation is not able to expect that this situation
 *   would change in the near future. An example is when external device for
 *   positioning is detached. The state "temporarily unavailable"
 *   means that the method is unavailable due to reasons that can be
 *   expected to possibly change in the near future and the provider
 *   to become available. An example is that the signal used by the location
 *   method is currently being obstructed when deep inside a
 *   building.
 *
 *   Do not toggle quickly between "temporarily unavailable" and
 *   "available" reflecting a very short transient obstruction of the
 *   signal.
 */
JKSint32 JkLocationGetProviderState(JKLocationProviderHandle hProvider);

/**
 *   Gets the current location
 *
 * @param hProvider
 *       The handle of the location provider. The value returned by
 *       #JkLocationOpenLocationProvider() is designated.
 * @param timeout
 *       A timeout value in seconds if it is larger than 0.
 *       The value -1 means the default timeout value of the location provider.
 * @return
 *       Return #JK_TRUE if the operation succeeds. Return #JK_FALSE if it fails.
 *
 *   Start a location measurement using given location provider. The
 *   measurement must be performed in a native system task. This function
 *   should only issue a measurement request and return immediately.
 *
 *   When the location is obtained, notify JBlend of the #AM_EVENT_LOCATION_GET_LOCATION_FINISHED
 *   event by using #AmNotifyLocationEvent().
 *   If the location could not be obtained until timeout expires,
 *   notify JBlend of the #AM_EVENT_LOCATION_GET_LOCATION_TIMEOUT event.
 *
 *   If an error occurred while a measurement is being performed, notify JBlend 
 *   of the #AM_EVENT_LOCATION_GET_LOCATION_FINISHED. 
 *   In this event notification,
 *   set #JK_NULL in the <i>param2</i> parameter of AmNotifyLocationEvent().
 *   
 *   If timeout expires or an error occurs in the middle of the 
 *   location measurement, JBlend throws a <code>javax.microedition.location.LocationException</code>.
 *
 *   Unless an event for the process initiated by this function is notified,
 *   this function is never called for the same location provider.
 *   It may, however, be called for another location provider.
 *
 *   If the current state of the location provider is "temporarily
 *   unavailable", attempt to get location until timeout expires. If
 *   the state is "out of service", fail this function and return #JK_FALSE
 *   without starting a measurement.
 *
 *   Note that the individual location information obtained by this
 *   function need not fulfil exactly the criteria that is designated by
 *   a parameter of #JkLocationOpenLocationProvider(). For example, an
 *   inaccurate result caused accidentally by poor signal is allowed.
 *
 *   When the JVM suspends while a measurement is being performed, the native
 *   system does not need to stop the measurement. The events can be notified
 *   even in the suspended period.
 *
 * @see #JkLocationOpenLocationProvider()
 * @see #AmNotifyLocationEvent()
 */
JKBool JkLocationGetLocation(JKLocationProviderHandle hProvider, JKSint32 timeout);

/**
 *   Gets the last known location
 *
 * @return
 *       If the last known location is available, return a pointer
 *       to the #JKLocationLocationInfo structure holding the location
 *       information. If not available, return #JK_NULL.
 *
 *   This function is called in case the Java application requests the last
 *   known location. If the terminal does not holds such information, JBlend
 *   passes to the application the last location that JBlend has acquired from
 *   the native system.
 *
 *   If this function returns a non #JK_NULL pointer, the pointer must
 *   remain valid until the native system is notified by
 *   #JkLocationReleaseLocation() that the pointer is no longer necessary.
 * @see #JkLocationReleaseLocation()
 */
JKLocationLocationInfo * JkLocationGetLastKnownLocation(void);

/**
 *   Releases a location information
 *
 * @param locationInfo
 *       A pointer to the memory area containing the location information
 *       structure that was passed to JBlend. The value passed as the
 *       <i>param2</i> parameter of #AmNotifyLocationEvent(), or the
 *       return value of #JkLocationGetLastKnownLocation() is designated.
 *
 *   This function is called when the location information becomes unnecessary.
 *   Release the memory area pointed to by the <i>locationInfo</i> parameter.
 * @see #AmNotifyLocationEvent(), JkLocationGetLastKnownLocation()
 */
void JkLocationReleaseLocation(JKLocationLocationInfo *locationInfo);

/**
 *   Cancels location measurement
 *
 * @param hProvider
 *       The handle of the location provider. The value returned by
 *       #JkLocationOpenLocationProvider() is designated.
 *
 *   This function is called to cancel the location measurement started by
 *   #JkLocationGetLocation() before the timeout expires. When this function
 *   is called, cancel ongoing measurement and notify JBLend of the
 *   #AM_EVENT_LOCATION_GET_LOCATION_CANCELED event by using
 *   #AmNotifyLocationEvent().
 * @see #JkLocationGetLocation()
 */
void JkLocationCancelGetLocation(JKLocationProviderHandle hProvider);

/**
 *   Sets a location listener.
 *
 * @param hProvider
 *       The handle of the location provider. The value returned by
 *       #JkLocationOpenLocationProvider() is designated.
 * @param interval
 *       The interval of location updates in seconds. -1
 *       means the default interval of the location provider. 0 means
 *       that there is no need for location updates but notification of
 *       the location provider state change is needed.
 * @param timeout
 *       A timeout value in seconds if it is larger than 0.
 *       -1 means the default timeout value of the location provider.
 *       If -1 is designated in <i>interval</i>, use the default timeout
 *       value regardless of <i>timeout</i>.
 *       In case <i>interval</i> is 0, <i>timeout</i> has no effect.
 * @param maxAge
 *       The maximum age of returned location information in seconds. It
 *       is a value larger than 0. -1 means the default maximum age of
 *       the location provider.
 *       If -1 is designated in <i>interval</i>, use the default timeout
 *       value regardless of <i>maxAge</i>.
 *       In case interval is 0, <i>maxAge</i> has no effect.
 *
 *   Set a location listener with the notification parameters specified by
 *   <i>interval</i>, <i>timeout</i> and <i>maxAge</i>, to the location
 *   provider designated by <i>hProvider</i>. The location listener previously
 *   set to the same location provider must be canceled.
 *
 *   The location measurement for the listener should be performed periodically
 *   in a native system task. The location listener should notify JBlend
 *   of the location information update by calling #AmNotifyLocationEvent() in
 *   a native system task, passing the #AM_EVENT_LOCATION_LOCATION_UPDATED
 *   event. If the location provider state changes, notify JBlend of the change
 *   by passing the #AM_EVENT_LOCATION_PROVIDER_STATE_CHANGED event.
 *   See the description of #JkLocationGetProviderState() for the definition of
 *   the states.
 *
 *   The <i>timeout</i> parameter specifies the delay that is allowed in case
 *   the location cannot be obtained by the scheduled time. If it's not possible
 *   to get a new location by the time (interval + timeout), notify JBlend of
 *   an invalid location by setting #JK_FALSE in the <i>isValid</i> member of
 *   #JKLocationLocationInfo structure passed by the <i>param2</i> of
 *   #AmNotifyLocationEvent(). The extra information may contain the reason of
 *   the measurement failure. For example, in case <i>interval</i> is 60 seconds
 *   and <i>timeout</i> is 10 seconds, some notification should be made at most 70
 *   seconds after the previous notification. The figure below shows the relation
 *   between <i>interval</i>, <i>timeout</i> and update period.
 *
 *   @image html JkLocationSetLocationListener_1_en.gif
 *
 *   Note that, when the target device conforms to Location API v1.0.1, until the time the location 
 *   is acquired first, the native system need not notify JBlend even if the 
 *   location measurement is not completed by the time (interval + timeout).
 *
 *   The <i>maxAge</i> parameter defines how old the location information is allowed to be
 *   notified. This allows the native system to reuse existing location information.
 *   For example, in case <i>interval</i> is 60 seconds and location measurement
 *   takes typically 10 seconds, measurement is scheduled 50 seconds after
 *   the previous location update so that the result can be notified after 60 seconds.
 *   In this case, if <i>maxAge</i> is specified as 20 seconds and there is a
 *   location information of the age 40 seconds or younger, the native system may return
 *   this location information after 60 seconds without performing a new measurement.
 *   The figure below shows the relation between <i>interval</i>, <i>maxAge</i> and
 *   location obtaining period
 *
 *   @image html JkLocationSetLocationListener_2_en.gif
 *
 *   All the parameter passed to this function are specified by the Java application.
 *   JBlend certifies their validity and calls this function only if they are valid.
 *   Thus, this function must always complete normally.
 *
 *   Start the first measurement immediately after this function is called.
 * @see #JkLocationOpenLocationProvider()
 * @see #AmNotifyLocationEvent()
 */
void JkLocationSetLocationListener(JKLocationProviderHandle hProvider, JKSint32 interval, JKSint32 timeout, JKSint32 maxAge);

/**
 *   Cancels the location listener
 *
 * @param hProvider
 *       The handle of the location provider. The value returned by
 *       #JkLocationOpenLocationProvider() is designated.
 *
 *   Cancel the location listener currently set for the location provider
 *   designated by the <i>hProvider</i> parameter.
 *   No event notification for this cancel operation is required.
 */
void JkLocationCancelLocationListener(JKLocationProviderHandle hProvider);

/**
 *   Suspends the location listener
 *
 * @param hProvider
 *       The handle of the location provider. The value returned by
 *       #JkLocationOpenLocationProvider() is designated.
 *
 *   Suspend the location listener currently set for the location provider
 *   designated by the <i>hProvider</i> parameter.
 *
 *   This function is called when the JVM suspends. Do not
 *   notify JBlend of events by #AmNotifyLocationEvent() during suspension.
 *   The location listener which has been suspended needs to be resumed by
 *   #JkLocationResumeLocationListener().
 */
void JkLocationSuspendLocationListener(JKLocationProviderHandle hProvider);

/**
 *   Resumes the location listener
 *
 * @param hProvider
 *       The handle of the location provider. The value returned by
 *       #JkLocationOpenLocationProvider() is designated.
 *
 *   Resume the suspended location listener currently set for the location provider
 *   designated by the <i>hProvider</i> parameter.
 *
 *   This function is called when the JVM resumes.
 */
void JkLocationResumeLocationListener(JKLocationProviderHandle hProvider);

/**
 *   Adds a proximity monitoring parameter
 *
 * @param proximity
 *       A pointer to the #JKLocationProximity structure containing parameters
 *       for proximity monitoring.
 * @return
 *       Return the handle of added proximity if the operation succeeds.
 *       The handle must be a unique and positive value.
 *       Return #JK_INVALID_HANDLE if it fails by any reason, such as resource shortage or
 *       that the native system does not support proximity monitoring.
 *
 *   Register a proximity parameter designated by <i>proximity</i> to
 *   the proximity listener and return its handle. The proximity listener
 *   detects terminal's proximity to the registered coordinates.
 *
 *   If the terminal enters the proximity of the registered coordinates,
 *   the proximity listener must notify JBlend of the #AM_EVENT_LOCATION_PROXIMITY_EVENT
 *   event by using #AmNotifyLocationEvent();
 *   if the proximity monitoring state changes while at least one proximity
 *   parameter is registered, notify JBlend of the #AM_EVENT_LOCATION_MONITORING_STATE_CHANGED
 *   event.
 *
 *   In case multiple over wrapped proximities are registered and the terminal
 *   enters some of them at the same time, notify events for that proximities
 *   separately.
 *
 *   The event must be made exactly one time for each proximity. The
 *   registered proximity parameter must be removed after the notification.
 *
 *   The proximity monitoring and event notification must be performed in a
 *   native system task. The proximity monitoring method is up to the native
 *   system. The location method and the frequency of monitoring are not defined
 *   in the specification. It is, however, necessary to check immediately whether
 *   the terminal is in the registered proximity within this function.
 *
 *   Because JBlend can receive the proximity notification even during
 *   the JVM suspension, no functions are provided for suspending or resuming
 *   proximity monitoring. Notify of proximity event at any time.
 *
 *   All the parameters passed to this function are specified by the Java application.
 *   JBlend checks validity of the members of the structure designated by the
 *   <i>proximity</i> parameter and calls this function only if they are valid.
 * @see #AmNotifyLocationEvent()
 */
JKLocationProximityHandle JkLocationAddProximity(const JKLocationProximity *proximity);

/**
 *   Removes a proximity monitoring parameter
 *
 * @param hProximity
 *       The handle of the proximity monitoring parameter. The value returned by
 *       #JkLocationAddProximity() is designated.
 *
 *   Remove the proximity monitoring parameter indicated by the
 *   <i>proximityHandle</i> parameter.
 */
void JkLocationRemoveProximity(JKLocationProximityHandle hProximity);

#ifdef __cplusplus
}
#endif

#endif /* !___JKLOCATIONPROVIDER_H___ */

/** @} end of group */
