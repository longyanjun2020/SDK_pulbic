/**
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkMediaControl.h
 *  Media Control
 */

/**
 * @addtogroup MediaControl_JSI
 *
 * @{
 */

#ifndef __JKMEDIACONTROL_H__
#define __JKMEDIACONTROL_H__

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 *  Media type default definitions
 */

/**
 * The minimum value that can be assigned to a media type
 *
 * Use this and higher values for assigning media types.
 * Lower values are reserved for JBlend.
 */
#define JKMEDIA_TYPE_USER_BASE   0x100

/**
 * The maximum value that can be assigned to a media type
 *
 * Use this and lower values for assigning media types.
 * Higher values are used for other purposes.
 */
#define JKMEDIA_TYPE_USER_LIMIT   0x0fffffff

/**
 * The minimum value assigned to a check management ID
 *
 * Use this and higher values as check management IDs.
 * Use lower values as player IDs.
 */
#define JKMEDIA_CHECK_ID_BASE   0x10000

/**
 * Player state
 */
/**
 *  No data set.
 */
#define JKMEDIA_STATE_NODATA     0
/**
 * Data set.
 */
#define JKMEDIA_STATE_DATA_SET   1
/**
 * Ready to play.
 */
#define JKMEDIA_STATE_READY      2
/**
 * Playing.
 */
#define JKMEDIA_STATE_STARTED    3
/**
 *  Paused.
 */
#define JKMEDIA_STATE_PAUSED     4
/**
 * Stopped due to error.
 */
#define JKMEDIA_STATE_ERROR      0x10000


/**
 * The Java profile or Java optional package that a player supports.
 */
/**
 * MMAPI (Mobile Media API)
 */
#define JKMEDIA_PROFILE_MMAPI    1
/**
 * VSCL 1.1 (Vodafone Service Class Library 1.1)
 */
#define JKMEDIA_PROFILE_VSCL     2

/**
 * MEXA or JSCL
 */
#define JKMEDIA_PROFILE_JSCL     4

/**
 * CJSP 1.0 (Common Java Service Platform Class Library 1.0)
 */
#define JKMEDIA_PROFILE_CJSP     8

/**
 * FSCL 1.0 (Fareastone Specific Class Library 1.0)
 */
#define JKMEDIA_PROFILE_FSCL     16



/**
 * An event that must be notified by the player
 */
/**
 * Playback stopped at the designated time.
 */
#define JKMEDIA_EVENT_STOPPED_AT_TIME 2
/**
 * Media played to the end.
 *
 * When the media has played to the end, notify of this event using #AmMediaPostEvent().
 * If playback is repeated, notify of this event only after the final reiteration.
 */
#define JKMEDIA_EVENT_END_OF_MEDIA    3
/**
 * Media duration is now known.
 *
 * When media duration could not be determined in data checking but becomes
 * known during play, notify of this event using #AmMediaPostEvent().
 */
#define JKMEDIA_EVENT_DURATION_UPDATE 4

/**
 * Resources for playback is unavailabe.
 */
#define JKMEDIA_EVENT_RESOURCE_UNAVAILABLE 7

/**
 * Resources for playback is availabe.
 */
#define JKMEDIA_EVENT_RESOURCE_AVAILABLE 8


/**
 * Repeated playback.
 */
#define JKMEDIA_EVENT_REPEAT          0x80

/**
 * min and max value for the volume values.
 */
#define JKMEDIA_MaxVolumeVal 127
#define JKMEDIA_MinVolumeVal 0
#define JKMEDIA_DefaultVolumeVal 63
#define JKMEDIA_VolumeScale(val) 128/val

/*
 */

/**
 * Requests reading from InputStream by JBlend.
 *
 * This is the identifier of an event to be passed to JBlend with AmMediaPostEvent() when 
 * performing streaming playback of the data out of an <code>InputStream</code>.
 *
 * An event of this type can be issued after
 * {@link JKT_Media_InputstreamControl#set JKT_Media_InputstreamControl#set()} is called until 
 * {@link JKT_MediaControl#set JKT_MediaControl#set()} is called passing #JK_NULL in the <i>pData</i> parameter.
 *
 * The data read in response to the request by this event is the data starting from the current read position of the <code>InputStream</code>.
 * For example, just after the media data header is passed with 
 * {@link JKT_Media_InputstreamControl#set JKT_Media_InputstreamControl#set()}, 
 * the succeeding data after the header is transferred by the request.
 *
 * Set as follows the members of the JKT_MediaEvent structure that is passed to JBlend via the parameter to AmMediaPostEvent().
 * @htmlonly <blockquote> @endhtmlonly
 * <dl>
 * <dt>{@link JKT_MediaEvent#playerID playerID}&nbsp;&nbsp;&nbsp;&nbsp;</dt>    <dd>The player ID.</dd>
 * <dt>{@link JKT_MediaEvent#mediaType mediaType}&nbsp;&nbsp;&nbsp;&nbsp;</dt>  <dd>The media type.</dd>
 * <dt>{@link JKT_MediaEvent#eventType eventType}&nbsp;&nbsp;&nbsp;&nbsp;</dt>  <dd>#JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ</dd>
 * <dt>{@link JKT_MediaEvent#usecH usecH}&nbsp;&nbsp;&nbsp;&nbsp;</dt>          <dd>0</dd>
 * <dt>{@link JKT_MediaEvent#usecL usecL}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 * <dd>
 * A pointer to a JKT_Media_InputstreamRequest structure holding read processing parameters.
 * This JKT_Media_InputstreamRequest structure must remain valid until 
 * {@link JKT_Media_InputstreamControl#requestComplete JKT_Media_InputstreamControl#requestComplete()} 
 * is called in response to the event.
 * The members of the JKT_Media_InputstreamRequest structure should be set as follows:
 * @htmlonly <blockquote> @endhtmlonly
 * <dl>
 * <dt>{@link JKT_Media_InputstreamRequest#playerID playerID}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  The player ID.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#request_size request_size}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  The size in bytes of the data to be read from the <code>InputStream</code>.
 *  Or, set -2 to request the remaining data; set -1 to request whole the stream data.
 *  However, -1 cannot be set if any of the following conditions is true.
 *  - {@link JKT_Media_InputstreamControl#precheck JKT_Media_InputstreamControl#precheck()} has returned -1 or -2.
 *  - The native system has issued a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ event with 
 *    -1 or -2 set in {@link JKT_Media_InputstreamRequest#request_size request_size}.
 *  - The native system has issued a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ event with 
 *    a value other than #JK_NULL set in {@link JKT_Media_InputstreamRequest#pBuffer pBuffer}.
 *  - The native system has issued a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_SEEK event.
 *  - The native system has issued a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_DESTROY event.
 *  . 
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#read_times read_times}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  A value indicating how many calls to the <code>InputStream.read( byte[], int, int )</code> method
 *  are allowed to read the data of the size indicated by the <i>request_size</i> member.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#pBuffer pBuffer}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  The initial address of the buffer for putting the data read from the <code>InputStream</code>.
 *  The buffer is allocated in the Java heap by JBlend.
 *  In this member, the native system can set #JK_NULL or the value of the 
 *  {@link JKT_Media_InputstreamRequest#pBuffer pBuffer} member of the JKT_Media_InputstreamRequest structure 
 *  which has been passed via 
 *  {@link JKT_Media_InputstreamControl#requestComplete JKT_Media_InputstreamControl#requestComplete()}.
 *  - When #JK_NULL is set, JBlend newly allocates a buffer in the Java heap.
 *  - When the value of the {@link JKT_Media_InputstreamRequest#pBuffer JKT_Media_InputstreamRequest#pBuffer} 
 *    member passed earlier is set, 
 *    JBlend reuses the buffer if its size is greater or equal to <i>request_size</i>, 
 *    or releases the buffer and allocates new one if its size is smaller than <i>request_size</i>.
 *  .
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#size size}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  Any value.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#result result}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  Any value.
 *  </dd>
 * </dl>
 * @htmlonly </blockquote> @endhtmlonly
 *  </dd>
 * </dl>
 * @htmlonly </blockquote> @endhtmlonly
 *
 * When an event of this type is received, JBlend reads data from the <code>InputStream</code> and notify the native system 
 * of its processing result via 
 * {@link JKT_Media_InputstreamControl#requestComplete JKT_Media_InputstreamControl#requestComplete()}.
 * The value {@link JKT_MediaEvent#usecL JKT_MediaEvent#usecL} above is passed in the 
 * {@link JKT_Media_InputstreamControl#requestComplete JKT_Media_InputstreamControl#requestComplete()} function 
 * <i>pRequest</i> parameter, and the members of the JKT_Media_InputstreamRequest structure indicated by this pointer are set as follows:
 * @htmlonly <blockquote> @endhtmlonly
 * <dl>
 * <dt>{@link JKT_Media_InputstreamRequest#playerID playerID}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  The value set in <i>playerID</i> by the native system.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#request_size request_size}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  The value set in <i>request_size</i> by the native system.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#read_times read_times}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  The value set in <i>read_times</i> by the native system.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#pBuffer pBuffer}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  The initial address of the buffer holding the data read from the <code>InputStream</code>.
 *  The buffer is allocated in the Java heap.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#size size}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  The size in bytes of the data actually read into the buffer indicated by <i>pBuffer</i>.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#result result}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  The processing result.
 *  A value of 0 or more indicates normal completion. 
 *  A negative value indicates an error.
 *  If 
 *  1 <= {@link JKT_Media_InputstreamRequest#size size} <= {@link JKT_Media_InputstreamRequest#request_size request_size},
 *  0 (normal completion) is set.
 *  If <code>InputStream</code> has reached the end of the stream, 1 is set.
 *  </dd>
 * </dl>
 * @htmlonly </blockquote> @endhtmlonly
 *
 * The stream read position has been moved forward by the value of the {@link JKT_Media_InputstreamRequest#size size}
 * member of the JKT_Media_InputstreamRequest structure passed via 
 * {@link JKT_Media_InputstreamControl#requestComplete JKT_Media_InputstreamControl#requestComplete()}.
 *
 * When the native system has finished with the data passed from JBlend via 
 * {@link JKT_Media_InputstreamControl#requestComplete JKT_Media_InputstreamControl#requestComplete()}, 
 * the native system should request reusing of the buffer with the next issue of a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ event
 * or request release of the buffer with a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_DESTROY event.
 *
 * The data passed via the members 
 * {@link JKT_Media_InputstreamRequest#pBuffer pBuffer} and {@link JKT_Media_InputstreamRequest#size size} 
 * of the JKT_Media_InputstreamRequest structure pointed to by the 
 * {@link JKT_Media_InputstreamControl#requestComplete JKT_Media_InputstreamControl#requestComplete()}
 * function <i>pRequest</i> parameter remains valid until one of the following events occurs:
 * - The native system issues a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_DESTROY event to request releasing the buffer.
 * - The native system issues a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ event to request data reading with the buffer reused.
 * - The play ends, JBlend calls {@link JKT_MediaControl#set JKT_MediaControl#set()} passing #JK_NULL in the <i>pData</i> parameter, 
 *   and {@link JKT_MediaControl#set set()} returns to the caller.
 * .
 *
 * Even before the native system is notified of the processing result of a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ event via 
 * {@link JKT_Media_InputstreamControl#requestComplete JKT_Media_InputstreamControl#requestComplete()}, 
 * other #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ events can be issued.
 * Requests including ones by #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_SEEK events are processed in the order events are issued.
 * Calls to {@link JKT_Media_InputstreamControl#requestComplete requestComplete()} are also in the order the events are issued.
 * @see JKT_Media_InputstreamRequest
 */
#define JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ		0x100
/**
 * Notifies JBlend that the buffer holding the data read from the <code>InputStream</code> is no longer used.
 *
 * This is the identifier of an event to be passed to JBlend with AmMediaPostEvent() when 
 * performing streaming playback of the data out of an <code>InputStream</code>.
 *
 * If the native system has requested data from the <code>InputStream</code> via a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ event
 * and JBlend has passed to the native system the data read via 
 * {@link JKT_Media_InputstreamControl#requestComplete JKT_Media_InputstreamControl#requestComplete()}, 
 * then when the native system has finished with the passed data, 
 * the native system should request reusing of the buffer with the next issue of a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ event
 * or request release of the buffer with a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_DESTROY event.
 *
 * When requesting release of the buffer with a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_DESTROY event, 
 * the members of the JKT_MediaEvent structure passed to JBlend via the parameter to AmMediaPostEvent() should be set as follows:
 * @htmlonly <blockquote> @endhtmlonly
 * <dl>
 * <dt>{@link JKT_MediaEvent#playerID playerID}</dt>    <dd>Player ID</dd>
 * <dt>{@link JKT_MediaEvent#mediaType mediaType}</dt>  <dd>Media type</dd>
 * <dt>{@link JKT_MediaEvent#eventType eventType}</dt>  <dd>#JKMEDIA_EVENT_INPUTSTREAM_REQUEST_DESTROY</dd>
 * <dt>{@link JKT_MediaEvent#usecH usecH}</dt>          <dd>0</dd>
 * <dt>{@link JKT_MediaEvent#usecL usecL}</dt>
 * <dd>
 * The address of the buffer holding the used data.
 * Set the value set in the <i>pBuffer</i> member of the JKT_Media_InputstreamRequest structure pointed to by the 
 * <i>pRequest</i> parameter to the 
 * {@link JKT_Media_InputstreamControl#requestComplete JKT_Media_InputstreamControl#requestComplete()} function 
 * that was called in response to a #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ event.
 * </dd>
 * </dl>
 * @htmlonly </blockquote> @endhtmlonly
 * After issuing this event, the native system must not access the buffer holding the used data.
 *
 * There is no completion notification made in response to the request made by this event.
 *
 * The native system finally must request release of every buffers passed from JBlend by means of the 
 * #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_DESTROY event.
 * However, when the play ends and JBlend calls {@link JKT_MediaControl#set JKT_MediaControl#set()}
 * passing JK_NULL in <i>pData</i> and the call returns, 
 * JBlend by itself releases all the buffers it has allocated in response to the requests by 
 * #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ events.
 * The native system therefore need not issue #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_DESTROY events after 
 * that call to {@link JKT_MediaControl#set JKT_MediaControl#set()}.
 * @see JKT_Media_InputstreamRequest
 */
#define JKMEDIA_EVENT_INPUTSTREAM_REQUEST_DESTROY	0x101
/**
 * Requests moving of the read position of the <code>InputStream</code> to JBlend.
 *
 * This is the identifier of an event to be passed to JBlend with AmMediaPostEvent() when 
 * performing streaming playback of the data out of an <code>InputStream</code>.
 *
 * Moving of the read position is possible only when 
 * #JK_TRUE is passed in the <i>isMarkSupported</i> parameter to 
 * the JKT_Media_InputstreamControl function structure functions 
 *  {@link JKT_Media_InputstreamControl#precheck  precheck()}, 
 *  {@link JKT_Media_InputstreamControl#checkOpen checkOpen()}, and 
 *  {@link JKT_Media_InputstreamControl#set set()}.
 *
 * An event of this type can be issued after
 * {@link JKT_Media_InputstreamControl#set JKT_Media_InputstreamControl#set()} is called until 
 * {@link JKT_MediaControl#set JKT_MediaControl#set()} is called passing #JK_NULL in the <i>pData</i> parameter.
 *
 * Set as follows the members of the JKT_MediaEvent structure that is passed to JBlend with the parameter to AmMediaPostEvent().
 * @htmlonly <blockquote> @endhtmlonly
 * <dl>
 * <dt>{@link JKT_MediaEvent#playerID playerID}</dt>    <dd>The player ID</dd>
 * <dt>{@link JKT_MediaEvent#mediaType mediaType}</dt>  <dd>The media type</dd>
 * <dt>{@link JKT_MediaEvent#eventType eventType}</dt>  <dd>#JKMEDIA_EVENT_INPUTSTREAM_REQUEST_SEEK</dd>
 * <dt>{@link JKT_MediaEvent#usecH usecH}</dt>          <dd>0</dd>
 * <dt>{@link JKT_MediaEvent#usecL usecL}</dt>
 * <dd>
 * A pointer to a JKT_Media_InputstreamRequest structure holding seek processing parameters.
 * This JKT_Media_InputstreamRequest structure must remain valid until 
 * {@link JKT_Media_InputstreamControl#requestComplete JKT_Media_InputstreamControl#requestComplete()} 
 * is called in response to the event.
 *
 * The members of the JKT_Media_InputstreamRequest structure pointed to by {@link JKT_MediaEvent#usecL usecL} should be set as follows:
 * @htmlonly <blockquote> @endhtmlonly
 * <dl>
 * <dt>{@link JKT_Media_InputstreamRequest#playerID playerID}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  The player ID.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#request_size request_size}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  Set the read position of the <code>InputStream</code> as an offset (in bytes) from the beginning of the stream.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#read_times read_times}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  Any value.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#pBuffer pBuffer}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  Any value.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#size size}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  Any value.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#result result}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  Any value.
 *  </dd>
 * </dl>
 * @htmlonly </blockquote> @endhtmlonly
 *  </dd>
 * </dl>
 * @htmlonly </blockquote> @endhtmlonly
 *
 * When this event is received, JBlend moves the read position using the <code>InputStream\#reset</code> method 
 * and the <code>InputStream\#skip</code> method, then notifies the native system of the processing result by calling
 * {@link JKT_Media_InputstreamControl#requestComplete JKT_Media_InputstreamControl#requestComplete()}.
 * The value {@link JKT_MediaEvent#usecL JKT_MediaEvent#usecL} above is passed to the 
 * {@link JKT_Media_InputstreamControl#requestComplete JKT_Media_InputstreamControl#requestComplete()} function 
 * <i>pRequest</i> parameter, and the members of the structure indicated by this pointer are set as follows:
 * @htmlonly <blockquote> @endhtmlonly
 * <dl>
 * <dt>{@link JKT_Media_InputstreamRequest#playerID playerID}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  The value set in <i>playerID</i> by the native system.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#request_size request_size}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  The value set in <i>request_size</i> by the native system.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#read_times read_times}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  The value set in <i>read_times</i> by the native system.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#pBuffer pBuffer}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  The value set in <i>pBuffer</i> by the native system.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#size size}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  The current read position.
 *  The same value as the <i>request_size</i> is set if the processing has succeeded.
 *  </dd>
 * <dt>{@link JKT_Media_InputstreamRequest#result result}&nbsp;&nbsp;&nbsp;&nbsp;</dt>
 *  <dd>
 *  The processing result.
 *  A value of 0 or more indicates normal completion. 
 *  A negative value indicates an error.
 *  </dd>
 * </dl>
 * @htmlonly </blockquote> @endhtmlonly
 *
 * Requests by #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_SEEK events including ones by #JKMEDIA_EVENT_INPUTSTREAM_REQUEST_READ events 
 * are processed in the order events are issued.
 * Calls to {@link JKT_Media_InputstreamControl#requestComplete requestComplete()} are also in the order the events are issued.
 * @see JKT_Media_InputstreamRequest
 */
#define JKMEDIA_EVENT_INPUTSTREAM_REQUEST_SEEK		0x102


/*
 * Reached the play end.
 */
#define MEDIAJSCL_PLAYEND 0x90

/**
 * The processing requested of the JKT_MediaControl structure function
 * has completed.
 *
 * In the case of a JKT_MediaControl function returning #JKMEDIA_RESULT_WAIT,
 * notify JBlend of this event using #AmMediaPostEvent() when the requested processing is
 * completed.
 */
#define JKMEDIA_EVENT_JOB_DONE        0x8000
/**
 * The processing requested of the JKT_MediaControl structure function
 * was terminated.
 *
 * When a JKT_MediaControl function returns #JKMEDIA_RESULT_WAIT requiring
 * JBlend to wait until the function completes its processing, notify JBlend of this
 * event by means of #AmMediaPostEvent() in the following cases.
 *  <ul>
 *   <li>Issue this event when the requested processing was forcibly terminated.
 *   <li>When <i>#suspendVM()</i> is called suspending JBlend before the
 *       requested processing is completed, cancel the processing on the other
 *       task and notify of this event in <i>#suspendVM()</i>.
 *   <li>When <i>#resumeVM()</i> is called resuming the suspended JBlend,
 *       notify of this event in <i>#resumeVM()</i>.
 *  </ul>
 *  If <i>#resumeVM()</i> was called, then after notifying this event, enable the
 *  processing that was cancelled due to the calling of <i>#suspendVM()</i> to be
 *  started over from the beginning.
 *  After the JVM resume processing, JBlend starts over from the calling
 *  of the JKT_MediaControl structure function that returned
 *  #JKMEDIA_RESULT_WAIT.
 */
#define JKMEDIA_EVENT_JOB_CANCELLED   0x8001
/**
 * The processing requested of the JKT_MediaControl structure function
 * resulted in error.
 *
 * In the case of a JKT_MediaControl function returning #JKMEDIA_RESULT_WAIT,
 * notify of this event by using #AmMediaPostEvent() when an error occurred in processing.
 */
#define JKMEDIA_EVENT_JOB_ERROR   0x8002
/**
 * The minimum value assigned to a platform-custom event
 *
 * Use this and higher values as the event type value for platform-custom events.
 */
#define JKMEDIA_EVENT_USER_BASE       0x10000
/**
 * An error occurred.
 */
#define JKMEDIA_EVENT_ERROR           -1

/**
 * Values returned by functions
 */
/**
 * Error, failed.
 */
#define JKMEDIA_RESULT_ERROR    -1
/**
 * OK, succeeded.
 */
#define JKMEDIA_RESULT_OK        0
/**
 * Processing will be performed asynchronously.
 *
 * When returning this value for a JSI function, the native system should notify
 * JBlend of the processing result by AmMediaPostEvent().
 * Pass one of the following values to AmMediaPostEvent() in the
 * <i>eventType</i> parameter.
 * <dl>
 *   <dt> #JKMEDIA_EVENT_JOB_DONE</dt>
 *   <dd>Processing succeeded.</dd>
 *   <dt> #JKMEDIA_EVENT_JOB_CANCELLED</dt>
 *   <dd>The requested processing was forcibly terminated. </dd>
 *   <dt> #JKMEDIA_EVENT_JOB_ERROR</dt>
 *   <dd>An error occurred. </dd>
 * </dl>
 */
#define JKMEDIA_RESULT_WAIT      0x01

/**
 * Definitions for time. Units are all microseconds.
 */
/**
 * The upper 32 bits of the maximum value for time (0x7fffffffffffffff)
 */
#define JKMEDIA_TIME_MAX_HIGH 0x7fffffff
/**
 * The lower 32 bits of the maximum value for time (0x7fffffffffffffff)
 */
#define JKMEDIA_TIME_MAX_LOW 0xffffffff
/**
 * The media time is unknown.
 *
 * When the time is unknown, use this for both the upper and lower 32 bits of the
 * 64-bit signed integer time expression.
 */
#define JKMEDIA_TIME_UNKNOWN 0xffffffff

/**
 * The media duration is unknown.
 *
 * When the duration is unknown, use this for both the upper and lower 32 bits of
 * the 64-bit signed integer time expression.
 */
#define JKMEDIA_DURATION_UNKNOWN 0xffffffff

/**
 * The media content flag definitions
 */
/**
 * A flag indicating that the media has audio
 */
#define JKMEDIA_CONTENT_AUDIO 0x01
/**
 * A flag indicating that the media has video
 */
#define JKMEDIA_CONTENT_VIDEO 0x02

/**
 * There is no user event parameter.
 *
 * Use this in the <i>getUserEventPrmType()</i> function of the JKT_Media_EventControl
 * structure.
 */
#define JKMEDIA_USEREVENTPRM_VOID 0

/**
 * The user event parameter is type int.
 *
 * Use this in the <i>getUserEventPrmType()</i> function of the JKT_Media_EventControl
 * structure.
 */
#define JKMEDIA_USEREVENTPRM_INT 1

/**
 * The user event parameter is type String.
 *
 * Use this in the <i>getUserEventPrmType()</i> function of the JKT_Media_EventControl
 * structure.
 */
#define JKMEDIA_USEREVENTPRM_STRING 2

/**
 *  Player events
 *
 */
/**
 * A structure defining media events
 */
typedef struct {
    /**
     *  Player ID
     */
    JKSint32 playerID;
    /**
     * Media type
     */
    JKSint32 mediaType;
    /**
     * Event type
     */
    JKSint32 eventType;
    /**
     * Upper 32bits of the media time (in microseconds) when the media event occured.
     * If the time is unknown, set #JKMEDIA_TIME_UNKNOWN .
     */
    JKUint32 usecH;
    /**
     * Lower 32bits of the media time (in microseconds) when the media event occured.
     * If the time is unknown, set #JKMEDIA_TIME_UNKNOWN.
     */
    JKUint32 usecL;
} JKT_MediaEvent;

/**
 * A structure defining event control functions
 *
 * These functions need not be implemented for non-supported media types.
 */
typedef struct {
    /**
     * Gets a string indicating the error event cause.
     * @param id
     *  The ID  of the player that notified the event
     * @param type
     *   The notified event type
     * @param pStr
     *   A pointer to the buffer for storing the error cause string
     * @param length
     *   The size (number of characters) of the buffer designated in pStr
     * @return
     *  Return the number of characters of the string stored in the buffer.<br>
     *  Return a negative value if the error event cause cannot be obtained.<br>
     *  Return the required buffer size if the buffer is too small to store the
     *  cause.
     *
     *  This function is called when an error event was notified to JBlend
     *  (#JKMEDIA_EVENT_ERROR). If the buffer size is too small, JBlend
     *  allocates the necessary buffer area and calls the function again.
     */
    JKSint32 ( *getErrorCause )( JKSint32 id, JKSint32 type, JKWChar* pStr, JKSint32 length );

    /**
     * Gets a string indicating the user event type.
     * @param id
     *   The user event player ID
     * @param type
     *  The event type of the user event
     * @param pStr
     *  A pointer to the buffer for storing the user event type string
     * @param length
     *   The buffer size (number of characters)
     * @return
     *  Return the number of characters of the string stored in the buffer.<br>
     *  Return a negative value if the event type cannot be obtained.<br>
     *  Return the required buffer size if the buffer is too small to store the
     *  type string.<br>
     *  Return 0 if user events are not supported.
     *
     *  This function is called when a user event was notified to JBlend.
     *  Put a string indicating the type of the user event designated by the <i>id</i>
     *  and <i>type</i> arguments in the buffer designated by <i>pStr</i>. If the buffer
     *  size is too small, JBlend allocates the necessary buffer area and
     *  calls the function again.
     */
    JKSint32 ( *getUserEventType )( JKSint32 id, JKSint32 type, JKWChar* pStr, JKSint32 length );

    /**
     * Gets the parameter type of a user event.
     * @param id
     *   The user event player ID
     * @param type
     *   The event type of the user event
     * @return
     *   Return a constant indicating the parameter type of the user event
     *   designated by the id and type arguments.<br>
     *   <dl>
     *    <dt> int type </dt>
     *     <dd> #JKMEDIA_USEREVENTPRM_INT </dd>
     *    <dt> String type </dt>
     *     <dd> #JKMEDIA_USEREVENTPRM_STRING </dd>
     *    <dt> No parameter </dt>
     *     <dd> #JKMEDIA_USEREVENTPRM_VOID </dd>
     *   </dl>
     *   If user events are not supported, return #JKMEDIA_USEREVENTPRM_VOID.
     *
     *  This function is called when a user event was notified to JBlend.
     */
    JKSint32 ( *getUserEventPrmType )( JKSint32 id, JKSint32 type );

    /**
     * Gets the user event parameters (integer).
     * @param id
     *   The player ID
     * @param type
     *   The event type
     * @return
     *   Return the parameters (integer) of the user event designated by the <i>id</i>
     *   and <i>type</i> arguments.
     *
     *  This function is called when a user event was notified to JBlend.
     */
    JKSint32 ( *getUserEventPrmInt )( JKSint32 id, JKSint32 type );

    /**
     * Gets the user event parameters (string).
     * @param id
     *   The player ID
     * @param type
     *   The event type
     * @param pStr
     *  A pointer to the buffer for storing the parameters
     * @param length
     *   The size (number of characters) of the buffer designated in <i>pStr</i>
     * @return
     *  Return the number of characters of the string stored in the buffer.<br>
     *  Return a negative value if the user event parameters cannot be
     *  obtained.<br>
     *  Return the required buffer size if the buffer is too small to store the
     *  parameters.<br>
     *  Return 0 if user events are not supported.
     *
     *  This function is called when a user event was notified to JBlend.
     *  Put the parameters (string) of the user event designated by the <i>id</i>
     *  and <i>type</i> arguments in the buffer designated by <i>pStr</i>. If the buffer
     *  size is too small, JBlend allocates the necessary buffer area and
     *  calls the function again.
     */
    JKSint32 ( *getUserEventPrmStr )( JKSint32 id, JKSint32 type, JKWChar* pStr, JKSint32 length );
} JKT_Media_EventControl;

/**
 * A structure defining volume control functions.
 */
typedef struct {
    /**
     * Sets the volume.
     * @param id
     *  The player ID
     * @param value
     *  The volume level to be set. Values from 0 to 127 are designated, with 0
     *  meaning silence.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; if it fails, return #JKMEDIA_RESULT_ERROR.
     */
    JKSint32 ( *setVolume )( JKSint32 id, JKSint32 value );

    /**
     * Gets the current volume level.
     * @param id
     *  The player ID
     * @return
     *  Return the volume level setting. The range is from 0 to 127, with 0
     *  meaning silence.
     */
    JKSint32 ( *getVolume )( JKSint32 id );
} JKT_Media_VolumeControl;

/**
 * A structure defining custom control functions
 *
 * Custom controls can be realized by means of additional Java class
 * implementation.
 */
typedef struct {
    /**
     * Gets the number of supported custom controls.
     * @return
     *   Return the number of supported custom control.
     */
    JKSint32 ( *getCount )( void );

    /**
     * Gets the class name or the class name and interface name with full path corresponding to a custom
     * control.
     * @param count
     *  A number identifying a custom control. Values are designated
     *  between 0 and the #getCount() return value minus 1.
     * @param pType
     *   A pointer to the buffer for storing the custom control type
     * @param pStr
     *   A pointer to the buffer for storing the name of the custom control class 
     *   or the names of custom control class and interface. 
     *   Each name must be a full path name and when storing class name and interface 
     *   name the character string must be in the format "<i>class name/interface name</i>". 
     * @param length
     *   The size (number of characters) of the buffer designated in <i>pStr</i>
     * @return
     *   Return the number of characters of the string stored in the buffer
     *   designated in <i>pStr</i>. Return a negative value if the class name (or interface name if necessary) could
     *   not be obtained. <br>
     *   Return the required buffer size if the buffer is too small to store the information.
     *
     *   Put in their respective buffers the type and class name or class name/interface name of the custom
     *   control designated by the <i>count</i> argument.
     *
     *   When it is required to enable applications to get a custom control instance via 
     *   <code>javax.microedition.media.Player.getControl</code> passing an interface name, 
     *   this function MUST pass to JBlend the class name and interface name corresponding to the custom control. 
     *   Otherwise, only class name is necessary. 
     *   See also the explanation in "@ref section_muse_userdef_java_class."
     * 
     *   If the buffer size is too small, JBlend allocates the necessary buffer area and calls the function again.
     */
    JKSint32 ( *getClassName )( JKSint32 count, JKSint32* pType, JKWChar* pStr, JKSint32 length );

    /**
     * Sets an array of int parameters in the player custom control.
     * @param id
     *  The player ID
     * @param type
     *  The type of the custom control. The value passed to JBlend by
     *  #getClassName() is designated.
     * @param funcID
     *   An ID identifying the function. An ID can be defined for each custom
     *   control.
     * @param pParam
     *   A pointer to the buffer for storing the array of int parameters
     * @param size
     *   The number of elements in the stored array
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *  Set an int array of parameters in the custom control of the
     *  designated player.
     */
    JKSint32 ( *setParam )( JKSint32 id, JKSint32 type, JKSint32 funcID,
                            JKSint32* pParam, JKSint32 size );

    /**
     * Gets an int array of parameters from a player's custom control.
     * @param id
     *  The player ID
     * @param type
     *  The type of the custom control. The value passed to JBlend by
     *  #getClassName() is designated.
     * @param funcID
     *   An ID identifying the function. An ID can be defined for each custom
     *   control.
     * @param pParam
     *   A pointer to the buffer for storing the parameters
     * @param size
     *  The number of array elements that can be stored in the buffer
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *   Get the int array of parameters from the custom control of the
     *   designated player.
     */
    JKSint32 ( *getParam )( JKSint32 id, JKSint32 type, JKSint32 funcID,
                            JKSint32* pParam, JKSint32 size );

    /**
     *  Sets a character string in a player's custom control.
     * @param id
     *  The player ID
     * @param type
     *  The type of the custom control. The value passed to JBlend by
     *  #getClassName() is designated.
     * @param funcID
     *   An ID identifying the function. An ID can be defined for each custom
     *   control.
     * @param pStr
     *  A pointer to the buffer storing the string
     * @param length
     *  The number of characters of the string stored in the buffer
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; if it fails, return #JKMEDIA_RESULT_ERROR.
     *
     *   Set a string in the custom control of the designated player.
     */
    JKSint32 ( *setString )( JKSint32 id, JKSint32 type, JKSint32 funcID,
                             JKWChar* pStr, JKSint32 length );

    /**
     * Gets a character string from a player's custom control.
     * @param id
     *  The player ID
     * @param type
     *  The type of the custom control. The value passed to JBlend by
     *  #getClassName() is designated.
     * @param funcID
     *   An ID identifying the function. An ID can be defined for each custom
     *   control.
     * @param pStr
     *  A pointer to the buffer for storing the string
     * @param length
     *   The buffer size (number of characters)
     * @return
     *   Return the number of characters of the string stored in the buffer
     *   designated in pStr. <br>
     *   Return a negative value if the string could not be obtained. <br>
     *   Return the required buffer size if the buffer is too small to store
     *   the string.
     *
     *   If the buffer size is too small, JBlend allocates the necessary
     *   buffer area and calls the function again.
     */
    JKSint32 ( *getString )( JKSint32 id, JKSint32 type, JKSint32 funcID,
                             JKWChar* pStr, JKSint32 length );
} JKT_Media_UserControl;

/**
 * A structure defining functions for player control
 *
 * If any of the following control function members is not supported, set it to
 * JK_NULL.
 * <ul>
 * <li> JKT_Media_EventControl const *  <i>pEventFuncs</i>
 * <li> JKT_Media_VolumeControl const *  <i>pVolumeFuncs</i>
 * <li> JKT_Media_UserControl const *  <i>pUserFuncs</i>
 * <li> void const *  <i>pExtFuncs</i>
 * <li> void const *  <i>pOptionFuncs</i>
 * </ul>
 * If a control is supported, all its defined functions must be implemented.
 */
typedef struct {
    /**
     * Media type
     *
     * Set the media type handled by the JKT_MediaControl structure member
     * functions. Use values of #JKMEDIA_TYPE_USER_BASE and higher.
     * The definitions will then be implementation-specific.
     */
    JKSint32 mediaType;

    /**
     *              Gets the media MIME-type string.
     * @param pType A pointer to the buffer for storing the pointer in the MIME type string.
     * @return      Return the number of characters of the MIME type string.
     *
     *   Put a pointer in the MIME type string in the buffer indicated by <i>pType</i>.
     *   In the case of media types defined for MMAPI Live-media Capture,
     *   use the string following capture:// as the MIME type string.
     *   (e.g., if "capture://audio," then "audio")
     */
    JKSint32 ( *getMIMEType )( JKWChar** pType );

    /**
     * Checks the media format.
     * @param pData
     *   A pointer to the data to be checked
     * @param length
     *   The length (in bytes) of the data to be checked
     * @return
     *   If the check operation succeeds, return JK_TRUE; if it fails, return JK_FALSE.
     *
     * Check the signature, etc. to determine whether the designated data has
     * the format of the applicable media. This check is only for determining
     * the media type and does not require more detailed checking, which is
     * performed between the calling of
     * {@link JKT_MediaControl#checkOpen checkOpen()} and
     * {@link JKT_MediaControl#checkClose checkClose()}.
     */
    JKBool ( *isData )( const JKUint8* pData, const JKSint32 length );

    /**
     * Opens the data for checking whether it is playable.
     * @param pData
     *   A pointer to the data to be checked.
     *   This pointer remains valid until
     *   {@link JKT_MediaControl#checkClose checkClose()} is called.
     * @param length
     *   The length (in bytes) of the data to be checked
     * @return
     *  Generate an instance for data checking, and if the operation succeeds,
     *  return a check management ID. <br>
     *  Use values of #JKMEDIA_CHECK_ID_BASE or above for the check management
     *  ID. If the operation fails, return 0.
     *
     * The media data pointed to by <i>pData</i> is held by JBlend. It does not
     * need to be copied to the native system.
     *
     * The management ID returned by this function is designated in the
     * following functions to identify the data for checking. <br>
     *  {@link JKT_MediaControl#check check()}<br>
     *  {@link JKT_MediaControl#getMediaSize getMediaSize()}<br>
     *  {@link JKT_MediaControl#getDuration getDuration()}<br>
     *  {@link JKT_MediaControl#checkClose checkClose()}<br>
     *  and the functions in JKT_Media_MetaDataControl<br>
     *
     *  If a JVM suspend or terminate request is issued after this
     *  function is called but before
     *  {@link JKT_MediaControl#checkClose checkClose()} is called, in some
     *  cases JBlend will not call
     *  {@link JKT_MediaControl#checkClose checkClose()}.
     *  The native system should therefore allocate and free the resources
     *  for the check not in this function and
     *  {@link JKT_MediaControl#checkClose checkClose()} but in
     *  {@link JKT_MediaControl#check check()}.
     */
    JKSint32 ( *checkOpen )( const JKUint8* pData, const JKSint32 length );

    /**
     * Performs a detailed check of data playability.
     * @param checkID
     *   The check management identifier. The value returned by
     *   {@link JKT_MediaControl#checkOpen checkOpen()} is designated.
     * @param pExtraID
     *   The pointer to the buffer for storing an identifier of additional
     *   information.
     *   If the native system needs additional information for its own,
     *   store a positive value unique in the system to this buffer.
     * @return
     *   Return one of the following constants.<br>
     *   #JKMEDIA_RESULT_OK<br>
     *   #JKMEDIA_RESULT_WAIT<br>
     *   #JKMEDIA_RESULT_ERROR
     *
     *   Run a thorough check of the playability of the set data.
     *   Perform all allocation and release of resources for the check inside
     *   this function.
     *
     *   This function can be implemented to perform its processing either
     *   asynchronously or synchronously. If the processing takes time,
     *   implement it as asynchronous processing to avoid blocking JBlend
     *   processing for an extended period.
     *   If this function is implemented to process asynchronously, then after
     *   requesting the processing by a separate task, pass
     *    #JKMEDIA_RESULT_WAIT as the return value and promptly return control
     *   to JBlend.
     *
     *   If processing is performed synchronously inside this function, return
     *    #JKMEDIA_RESULT_OK if the data is playable, or return
     *    #JKMEDIA_RESULT_ERROR if the data is unplayable or the check
     *   processing fails.
     *
     *   If processing is performed asynchronously, return #JKMEDIA_RESULT_WAIT,
     *   and notify JBlend of the result by calling AmMediaPostEvent() from a
     *   task other than the JVM task.
     *   Pass one of the following values to AmMediaPostEvent() in the <i>eventType</i> parameter.
     *   - #JKMEDIA_EVENT_JOB_DONE<br>
     *     The data was found to be playable.
     *   - #JKMEDIA_EVENT_JOB_CANCELLED<br>
     *     The requested processing was forcibly terminated.
     *   - #JKMEDIA_EVENT_JOB_ERROR<br>
     *     The data is unplayable or check processing failed.
     *   .
     *
     *  If it is necessary for the native system to keep additional information
     *  for the media data, such as when using a data converter,
     *  allocate a management area in memory and store the information in it,
     *  and store the identifier of the information in the buffer indicated by
     *  the <i>pExtraID</i> parameter.
     *  The identifier must be a positive number.
     *  JBlend passes the ID to {@link JKT_MediaControl#set set()} as a
     *  parameter.
     *
     *  Keep the additional information until
     *  #JkMediaControlDestroyAdditionalInfo() is called.
     *
     *  If it is not necessary for the native system to keep additional
     *  information,
     *  this function does not need to perform any operation on the
     *  <i>ExtraID</i> parameter.
     */
    JKSint32 ( *check )( JKSint32 checkID, JKSint32* pExtraID );

    /**
     * Ends the checking started by #checkOpen().
     * @param checkID
     *   The check management ID. The ID returned by
     *   {@link JKT_MediaControl#checkOpen checkOpen()} is designated.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; if it fails,
     *   return #JKMEDIA_RESULT_ERROR.
     *
     *  If a JVM suspend or terminate request is issued after
     *  {@link JKT_MediaControl#checkOpen checkOpen()} is called but before
     *  this function is called, in some cases JBlend will not call this
     *  function.
     *  The native system should therefore allocate and free the resources
     *  for the check not in {@link JKT_MediaControl#checkOpen checkOpen()}
     *  and this function but in {@link JKT_MediaControl#check check()}.
     *
     */
    JKSint32 ( *checkClose )( JKSint32 checkID );

    /**
     * Gets the display size of the media data.
     * @param checkID
     *   The check management ID. The ID returned by
     *   {@link JKT_MediaControl#checkOpen checkOpen()} is designated.
     * @param pWidth
     *  A pointer to the buffer for storing the width
     * @param pHeight
     *  A pointer to the buffer for storing the height
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; if it fails,
     *   return #JKMEDIA_RESULT_ERROR.
     *
     * Analyze the media data designated in the <i>id</i> argument, and put
     * its width and height in the designated buffers.
     * For audio-only data, put 0 in both the width and height buffer areas.
     *
     * This function can be called between the calling of
     *  {@link JKT_MediaControl#checkOpen checkOpen()} and
     *  {@link JKT_MediaControl#checkClose checkClose()}.
     * The allocation and deallocation of resources necessary for the
     * processing must be completed inside this function.
     */
    JKSint32 ( *getMediaSize )( JKSint32 checkID, JKSint32* pWidth, JKSint32* pHeight );

    /**
     * Creates a player.
     * @return
     *  If the operation succeeds, return a player ID.
     *  Use positive values lower than #JKMEDIA_CHECK_ID_BASE for the player ID.
     *  If the operation fails, return 0.
     *
     *  When this function is called, in the native system create a player.
     *
     *  If this function succeeds, set #JKMEDIA_STATE_NODATA as the player
     *  state obtainable by {@link JKT_MediaControl#getState getState()}.
     */
    JKSint32 ( *create )( void );

    /**
     * Deletes a player.
     * @param id
     *  The player ID. The value returned by
     *  {@link JKT_MediaControl#create create()} is designated.
     * @return
     *  If the operation succeeds, return #JKMEDIA_RESULT_OK; if it fails,
     *  return  #JKMEDIA_RESULT_ERROR.
     *
     * This function is invoked in the following cases.
     * <ul>
     *   <li>When JBlend destroys a native system player as part of GC
     *       processing.
     *   <li>When AamsVmStop() or AamsVmKill() is invoked by the native system
     *       requesting JVM termination.
     * </ul>
     * When JVM termination is requested, this function is invoked for all
     * native players existing at the time. It may be invoked even for a
     * player that is playing.
     *
     * Since this function may be invoked when GC is executed, do not invoke
     * in this function AmMemAllocPointer() or other JBI functions that
     * allocate Java heap space.
     * It is possible to invoke a JBI function such as AmMemFreePointer() for
     * releasing Java heap space.
     */
    JKSint32 ( *destroy )( JKSint32 id );

    /**
     * Sets media data for playing.
     * @param id
     *  The player ID. The value returned by
     *  {@link JKT_MediaControl#create create()} is designated.
     * @param pData
     *   A pointer to the buffer holding the media data.
     * @param length
     *   The length of the data in bytes
     * @param extraID
     *   The identifier of additional information. The value created by
     *    {@link JKT_MediaControl#check check()} is designated.
     *   If  {@link JKT_MediaControl#check check()} did not create an
     *   identifier, 0 is designated.
     * @return
     *   Return one of the following constants.
     *   - #JKMEDIA_RESULT_OK
     *   - #JKMEDIA_RESULT_WAIT
     *   - #JKMEDIA_RESULT_ERROR
     *   .
     *
     * This function is called when the player state is #JKMEDIA_STATE_NODATA
     * or #JKMEDIA_STATE_DATA_SET.
     * When this function is called, process as follows based on the value
     * passed in <i>pData</i>.
     * <ul>
     * <li><b>If a value other than #JK_NULL is passed in <i>pData</i></b><br>
     * Set media data in the player.
     * If processing is performed synchronously in this function and succeeds,
     * change the player state to #JKMEDIA_STATE_DATA_SET, then return
     * #JKMEDIA_RESULT_OK.<br>
     * <br>
     * If processing is performed asynchronously, return #JKMEDIA_RESULT_WAIT,
     * and notify JBlend of the result by calling AmMediaPostEvent() from a
     * task other than the JVM task.
     * If the processing succeeds, change the player state to
     * #JKMEDIA_STATE_DATA_SET, then pass a #JKMEDIA_EVENT_JOB_DONE event.
     * See the description of #JKMEDIA_RESULT_WAIT for the values to be passed
     * when processing fails.<br>
     * <br>
     * If the operation fails in either synchronous or asynchronous
     * processing, do not change the player state.<br>
     * <br>
     * The data is kept in JBlend and does not have to be copied to the native
     * player.
     *
     * <li><b>If #JK_NULL is passed in <i>pData</i></b><br>
     * Clear the media data set in the player.
     * If processing is performed synchronously in this function and succeeds,
     * change the player state to #JKMEDIA_STATE_NODATA, then return
     * #JKMEDIA_RESULT_OK.<br>
     * <br>
     * If processing is performed asynchronously, return #JKMEDIA_RESULT_WAIT,
     * and notify JBlend of the result by calling AmMediaPostEvent() from a
     * task other than the JVM task.
     * If the processing succeeds, change the player state to
     *  #JKMEDIA_STATE_NODATA, then pass a #JKMEDIA_EVENT_JOB_DONE event.
     * See the description of #JKMEDIA_RESULT_WAIT for the values to be passed
     * when processing fails.<br>
     * <br>
     * If the operation fails in either synchronous or asynchronous
     * processing, do not change the player state.<br>
     * <br>
     * Note that in the case of a #JKT_MediaControl function structure
     * implementing Live Media Capture, #JK_NULL is always passed in
     * <i>pData</i>.
     * Perform state transition as indicated below based on the player state
     * at the time this function is called.
     * - Player is in the #JKMEDIA_STATE_NODATA state:<br>
     *    Change state to #JKMEDIA_STATE_DATA_SET.
     * - Player is in the #JKMEDIA_STATE_DATA_SET state:<br>
     *    Change state to #JKMEDIA_STATE_NODATA.
     * .
     * </ul>
     * Do not allocate and free exclusive resources in this function.
     */
    JKSint32 ( *set )( JKSint32 id, const JKUint8* pData, const JKSint32 length, JKSint32 extraID );

    /**
     * Acquires exclusive resources and loads media.
     * @param id
     *  The player ID. The value returned by
     *  {@link JKT_MediaControl#create create()} is designated.
     * @return
     *   Return one of the following constants.<br>
     *   #JKMEDIA_RESULT_OK<br>
     *   #JKMEDIA_RESULT_WAIT<br>
     *   #JKMEDIA_RESULT_ERROR<br>
     *
     *  This function is called when the player state is
     *   #JKMEDIA_STATE_DATA_SET.
     *  When this function is called, the native system must acquire
     *  exclusive resources,
     *  and must put the media passed by {@link JKT_MediaControl#set set()}
     *  in the state that it
     *  immediately can play.
     *
     *  This function can be implemented to perform its processing either
     *  asynchronously or synchronously. If the processing takes time,
     *  implement it as asynchronous processing to avoid blocking JBlend
     *  processing for an extended period.
     *  If this function is implemented to process asynchronously, then after
     *  requesting the processing by a separate task, pass
     *   #JKMEDIA_RESULT_WAIT as the return value and promptly return control
     *  to JBlend.
     *
     * If processing is performed synchronously in this function and succeeds,
     * change the player state to #JKMEDIA_STATE_READY, then return
     * #JKMEDIA_RESULT_OK.
     *
     * If processing is performed asynchronously, return #JKMEDIA_RESULT_WAIT,
     * and notify JBlend of the result by calling AmMediaPostEvent() from a
     * task other than the JVM task.
     * If the processing succeeds, change the player state to
     *  #JKMEDIA_STATE_READY, then pass a #JKMEDIA_EVENT_JOB_DONE event.
     * See the description of #JKMEDIA_RESULT_WAIT for the values to be passed
     * when processing fails.
     *
     * If the operation fails in either case of synchronous or asynchronous
     * processing, do not change player state.
     *
     *  At the time this function is called,
     *  fail loading and return #JKMEDIA_RESULT_ERROR
     *  if the necessary exclusive resources are not available
     *  because they are used for an alert sound playback by
     *  #JkDeviceAlertBySound() or for
     *  a monophonic tone playback by #JkMediaTonePlayNote().
     *  For details of #JkDeviceAlertBySound(), see
     *  <i>JBlend [micro] Interface Reference: CLDC 1.0/1.1--MIDP 2.0</i>.
     */
    JKSint32 ( *load )( JKSint32 id );

    /**
     * Starts playback.
     * @param id
     *  The player ID. The value returned by
     *  {@link JKT_MediaControl#create create()} is designated.
     * @param loop
     *   The number of times to play the media. Endless loop is designated as
     *   0, and still image playing as 1. <br><br>
     *   See {@link JKT_MediaControl#getIncludedContents getIncludedContents()}
     *   for the conditions by which JBlend regards media data as a still image.
     * @return
     *   Return one of the following constants.<br>
     *   #JKMEDIA_RESULT_OK<br>
     *   #JKMEDIA_RESULT_WAIT<br>
     *   #JKMEDIA_RESULT_ERROR<br>
     *
     * This function is called when the player state is #JKMEDIA_STATE_READY.
     * When this function is called, start playing the media data passed
     * in  {@link JKT_MediaControl#set set()}.
     * The necessary playback processing for each type of data contained in
     * media is as follows.
     * <dl>
     * <dt>Sound</dt>
     * <dd>
     *   <ul>
     *   <li>Time proceeding of media
     *   <li>Output to a sound device
     *   </ul>
     * </dd>
     * <dt>Still image</dt>
     * <dd>
     *   <ul>
     *   <li>Drawing on the real screen
     *   </ul>
     * <dt>Video image</dt>
     * <dd>
     *   <ul>
     *   <li>Time proceeding of media
     *   <li>Drawing on the real screen
     *   </ul>
     * </dl>
     * JBlend controls starting and stopping of drawing on the real screen
     * for still image or video image by calling
     * {@link JKT_Media_VideoControl#startUpdate startUpdate()} and
     * {@link JKT_Media_VideoControl#stopUpdate stopUpdate()}.
     * If this function is called before the JKT_Media_VideoControl structure
     * {@link JKT_Media_VideoControl#startUpdate startUpdate()} function
     * for a player of still image or video image, the drawing on
     * the real screen should not take place until
     * {@link JKT_Media_VideoControl#startUpdate startUpdate()} is called.
     *
     * This function can be implemented to perform its processing either
     * asynchronously or synchronously. If the processing takes time,
     * implement it as asynchronous processing to avoid blocking JBlend
     * processing for an extended period.
     * If this function is implemented to process asynchronously, then after
     * requesting the processing by a separate task, pass
     *  #JKMEDIA_RESULT_WAIT as the return value and promptly return control
     * to JBlend.
     *
     * If processing is performed synchronously in this function and succeeds,
     * change the player state to #JKMEDIA_STATE_STARTED, then return
     * #JKMEDIA_RESULT_OK.
     *
     * If processing is performed asynchronously, return #JKMEDIA_RESULT_WAIT,
     * and notify the result to JBlend by calling AmMediaPostEvent() from a
     * task other than the JVM task.
     * If the processing succeeds, change the player state to
     *  #JKMEDIA_STATE_STARTED, then pass a #JKMEDIA_EVENT_JOB_DONE event.
     * See the description of #JKMEDIA_RESULT_WAIT for the values to be passed
     * when processing fails.
     *
     * If the operation fails in either case of synchronous or asynchronous
     * processing, do not change player state.
     *
     * When the end of the media data is reached, change the player
     * state to #JKMEDIA_STATE_READY, set the media time to the beginning
     * of the media data, then pass to JBlend a
     * #JKMEDIA_EVENT_END_OF_MEDIA event.
     *
     * If an error occurs during play, change the player state to
     * #JKMEDIA_STATE_ERROR, then pass to JBlend a #JKMEDIA_EVENT_ERROR
     * event by AmMediaPostEvent().
     */
    JKSint32 ( *start )( JKSint32 id, JKSint32 loop );

    /**
     * Stops playback.
     * @param id
     *  The player ID. The value returned by
     *   {@link JKT_MediaControl#create create()} is designated.
     * @return
     *   Return one of the following constants.<br>
     *   #JKMEDIA_RESULT_OK<br>
     *   #JKMEDIA_RESULT_WAIT<br>
     *   #JKMEDIA_RESULT_ERROR<br>
     *
     * This function is called when the player state is #JKMEDIA_STATE_STARTED
     *  or #JKMEDIA_STATE_PAUSED.
     * When this function is called, stop the player, reset the play position
     * to the beginning of the media.
     *
     * This function can be implemented to perform its processing either
     * asynchronously or synchronously. If the processing takes time,
     * implement it as asynchronous processing to avoid blocking JBlend
     * processing for an extended period.
     * If this function is implemented to process asynchronously, then after
     * requesting the processing by a separate task, pass
     *  #JKMEDIA_RESULT_WAIT as the return value and promptly return control
     * to JBlend.
     *
     * If processing is performed synchronously in this function and succeeds,
     * change the player state to #JKMEDIA_STATE_READY, then return
     * #JKMEDIA_RESULT_OK.
     *
     * If processing is performed asynchronously, return #JKMEDIA_RESULT_WAIT,
     * and notify JBlend of the result by calling AmMediaPostEvent() from a
     * task other than the JVM task.
     * If the processing succeeds, change the player state to
     *  #JKMEDIA_STATE_READY, then pass a #JKMEDIA_EVENT_JOB_DONE event.
     * See the description of #JKMEDIA_RESULT_WAIT for the values to be passed
     * when processing fails.
     *
     * If the operation fails in either case of synchronous or asynchronous
     * processing, do not change player state.
     */
    JKSint32 ( *stop )( JKSint32 id );

    /**
     * Pauses playback.
     * @param id
     *  The player ID. The value returned by
     *   {@link JKT_MediaControl#create create()} is designated.
     * @return
     *   Return one of the following constants.<br>
     *   #JKMEDIA_RESULT_OK<br>
     *   #JKMEDIA_RESULT_WAIT<br>
     *   #JKMEDIA_RESULT_ERROR<br>
     *
     * This function is called when the player state is #JKMEDIA_STATE_STARTED.
     * When this function is called, pause playback by the player.
     *
     * This function can be implemented to perform its processing either
     * asynchronously or synchronously. If the processing takes time,
     * implement it as asynchronous processing to avoid blocking JBlend
     * processing for an extended period.
     * If this function is implemented to process asynchronously, then after
     * requesting the processing by a separate task, pass
     *  #JKMEDIA_RESULT_WAIT as the return value and promptly return control
     * to JBlend.
     *
     * If processing is performed synchronously in this function and succeeds,
     * change the player state to #JKMEDIA_STATE_PAUSED, then return
     * #JKMEDIA_RESULT_OK.
     *
     * If processing is performed asynchronously, return #JKMEDIA_RESULT_WAIT,
     * and notify JBlend of the result by calling AmMediaPostEvent() from a
     * task other than the JVM task.
     * If the processing succeeds, change the player state to
     *  #JKMEDIA_STATE_PAUSED, then pass a #JKMEDIA_EVENT_JOB_DONE event.
     * See the description of #JKMEDIA_RESULT_WAIT for the values to be passed
     * when processing fails.
     *
     * If the operation fails in either case of synchronous or asynchronous
     * processing, do not change player state.
     */
    JKSint32 ( *pause )( JKSint32 id );

    /**
     * Resumes playback.
     * @param id
     *  The player ID. The value returned by
     *  {@link JKT_MediaControl#create create()} is designated.
     * @return
     *   Return one of the following constants.<br>
     *   #JKMEDIA_RESULT_OK<br>
     *   #JKMEDIA_RESULT_WAIT<br>
     *   #JKMEDIA_RESULT_ERROR<br>
     *
     * This function is called when the player state is #JKMEDIA_STATE_PAUSED.
     * When this function is called, resume playing from the point where the
     * player has been paused.
     *
     * This function can be implemented to perform its processing either
     * asynchronously or synchronously. If the processing takes time,
     * implement it as asynchronous processing to avoid blocking JBlend
     * processing for an extended period.
     * If this function is implemented to process asynchronously, then after
     * requesting the processing by a separate task, pass
     *  #JKMEDIA_RESULT_WAIT as the return value and promptly return control
     * to JBlend.
     *
     * If processing is performed synchronously in this function and succeeds,
     * change the player state to #JKMEDIA_STATE_STARTED, then return
     * #JKMEDIA_RESULT_OK.
     *
     * If processing is performed asynchronously, return #JKMEDIA_RESULT_WAIT,
     * and notify JBlend of the result by calling AmMediaPostEvent() from a
     * task other than the JVM task.
     * If the processing succeeds, change the player state to
     *  #JKMEDIA_STATE_STARTED, then pass a #JKMEDIA_EVENT_JOB_DONE event.
     * See the description of #JKMEDIA_RESULT_WAIT for the values to be passed when
     * processing fails.
     *
     * If the operation fails in either case of synchronous or asynchronous
     * processing, do not change player state.
     *
     * When the end of the media data is reached, change the player
     * state to #JKMEDIA_STATE_READY, set the media time to the beginning
     * of the media data, then pass to JBlend a
     *  #JKMEDIA_EVENT_END_OF_MEDIA event.
     *
     * If an error occurs during play, change the player state to
     *  #JKMEDIA_STATE_ERROR, then pass to JBlend a #JKMEDIA_EVENT_ERROR
     * event by AmMediaPostEvent().
     */
    JKSint32 ( *restart )( JKSint32 id );

    /**
     * Unloads media and frees exclusive resources.
     * @param id
     *  The player ID. The value returned by
     *   {@link JKT_MediaControl#create create()} is designated.
     * @return
     *   Return one of the following constants.<br>
     *   #JKMEDIA_RESULT_OK<br>
     *   #JKMEDIA_RESULT_WAIT<br>
     *   #JKMEDIA_RESULT_ERROR<br>
     *
     * This function is called when the player state is #JKMEDIA_STATE_READY
     * or #JKMEDIA_STATE_ERROR.
     * When this function is called, free the exclusive resources
     * allocated in {@link JKT_MediaControl#load load()}.
     *
     * This function can be implemented to perform its processing either
     * asynchronously or synchronously. If the processing takes time,
     * implement it as asynchronous processing to avoid blocking JBlend
     * processing for an extended period.
     * If this function is implemented to process asynchronously, then after
     * requesting the processing by a separate task, pass
     *  #JKMEDIA_RESULT_WAIT as the return value and promptly return control
     * to JBlend.
     *
     * If processing is performed synchronously in this function and succeeds,
     * change the player state to #JKMEDIA_STATE_DATA_SET, then return
     * #JKMEDIA_RESULT_OK.
     *
     * If processing is performed asynchronously, return #JKMEDIA_RESULT_WAIT,
     * and notify JBlend of the result by calling AmMediaPostEvent() from a
     * task other than the JVM task.
     * If the processing succeeds, change the player state to
     *  #JKMEDIA_STATE_DATA_SET, then pass a #JKMEDIA_EVENT_JOB_DONE event.
     * See the description of #JKMEDIA_RESULT_WAIT for the values to be passed when
     * processing fails.
     *
     * If the operation fails in either case of synchronous or asynchronous
     * processing, do not change player state.
     */
    JKSint32 ( *unload )( JKSint32 id );

    /**
     * Gets the player state.
     * @param id
     *  The player ID. The value returned by
     *   {@link JKT_MediaControl#create create()} is designated.
     * @return
     *   Return one of the following constants as a player state.<br>
     *   #JKMEDIA_STATE_NODATA<br>
     *   #JKMEDIA_STATE_DATA_SET<br>
     *   #JKMEDIA_STATE_READY<br>
     *   #JKMEDIA_STATE_STARTED<br>
     *   #JKMEDIA_STATE_PAUSED<br>
     *   #JKMEDIA_STATE_ERROR
     *
     *   Note that buffering processing for streaming playback should not affect the return value of this function.
     *   For example, even when the native system is pausing playback because of buffering the streaming media, 
     *   the return value of getState() must be #JKMEDIA_STATE_STARTED, which should be returned when the player is 
     *   normally playing without buffering.
     */
    JKSint32 ( *getState )( JKSint32 id );

    /**
     * Gets the play duration of the designated data.
     * @param id
     *   The player ID (a value returned by
     *    {@link JKT_MediaControl#create create()},
     *   of less than #JKMEDIA_CHECK_ID_BASE) or a check management ID
     *   (a value returned by {@link JKT_MediaControl#checkOpen checkOpen()},
     *   of #JKMEDIA_CHECK_ID_BASE or greater).
     * @param pUsecH
     *   A pointer to the buffer for storing the upper 32 bits of the play
     *   duration (in microseconds).
     * @param pUsecL
     *   A pointer to the buffer for storing the lower 32 bits of the play
     *   duration (in microseconds)
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; if it fails,
     *   return #JKMEDIA_RESULT_ERROR.
     *
     * Process as follows based on the value passed in the <i>id</i> parameter.
     * <dl>
     * <dt>If <i>id</i> is a player ID (a value smaller than #JKMEDIA_CHECK_ID_BASE)
     * </dt>
     * <dd>Set in the buffers indicated by <i>pUsecH</i> and <i>pUsecL</i>
     *     the play duration of the media data set to the player, as a
     *     signed 64-bit integer.
     * </dd>
     * <dt>If <i>id</i> is a check management ID ( #JKMEDIA_CHECK_ID_BASE or
     *     greater)
     * </dt>
     * <dd>Set in the buffers indicated by <i>pUsecH</i> and <i>pUsecL</i>
     *     the play duration of the media data that has been passed in
     *     {@link JKT_MediaControl#checkOpen checkOpen()}, as a signed 64-bit integer.
     * </dd>
     * </dl>
     *
     * In the following cases, store 0 in both buffers <i>pUsecH</i> and
     * <i>pUsecL</i>.
     * <ul>
     *   <li>When the media data is a still image such as PNG or JPEG.
     *   <li>When media data is not yet set in the player.
     * </ul>
     * JBlend regards media data as a still image if 0 has been passed as the
     * play duration by this function, and in addition
     * {@link JKT_MediaControl#getIncludedContents getIncludedContents()}
     * returns #JKMEDIA_CONTENT_VIDEO.
     *
     * If the play duration cannot be acquired or is otherwise unknown, store
     * #JKMEDIA_DURATION_UNKNOWN in both buffers <i>pUsecH</i> and
     * <i>pUsecL</i>, and process as follows based on the value passed in the
     * <i>id</i> parameter.
     * <dl>
     * <dt>If <i>id</i> is a player ID (a value smaller than
     *      #JKMEDIA_CHECK_ID_BASE)
     * </dt>
     * <dd>When the play duration becomes known, pass a
     *       #JKMEDIA_EVENT_DURATION_UPDATE event by AmMediaPostEvent(). Then
     *       this function will be invoked again requesting the play duration.
     *       When this function is invoked following
     *        #JKMEDIA_EVENT_DURATION_UPDATE event notification, do not store
     *        #JKMEDIA_DURATION_UNKNOWN.<br><br>
     *       The allocation and deallocation of resources necessary for the
     *       processing must be completed inside this function.
     *   </dd>
     *   <p>
     * <dt>If <i>id</i> is a check management ID ( #JKMEDIA_CHECK_ID_BASE or
     *     greater)
     * </dt>
     * <dd>There is no need to pass a #JKMEDIA_EVENT_DURATION_UPDATE event
     *     by AmMediaPostEvent().
     * </dd>
     * </dl>
     *
     * This function can be called between the calling of checkOpen() and
     * checkClose().
     */
    JKSint32 ( *getDuration )( JKSint32 id, JKUint32* pUsecH, JKUint32* pUsecL );

    /**
     * Sets the play position.
     * @param id
     *  The player ID. The value returned by
     *  {@link JKT_MediaControl#create create()} is designated.
     * @param usecH
     *   The upper 32 bits of the play position (in microseconds).
     * @param usecL
     *   The lower 32 bits of the play position (in microseconds).
     * @return
     *   Return one of the constants below. <br>
     *   #JKMEDIA_RESULT_OK<br>
     *   #JKMEDIA_RESULT_WAIT<br>
     *   #JKMEDIA_RESULT_ERROR<br>
     *   If play position setting is not supported,
     *   of if play position setting fails, return
     *   #JKMEDIA_RESULT_ERROR.
     *
     *   When this function is called while the player state is
     *   #JKMEDIA_STATE_STARTED,
     *   continue playing from the play position designated in usecH and usecL.
     *   If it is called in #JKMEDIA_STATE_PAUSED state, #JKMEDIA_STATE_READY
     *   state, or #JKMEDIA_STATE_DATA_SET state, start playing from the play
     *   position designated the next time
     *   {@link JKT_MediaControl#restart restart()} or
     *   {@link JKT_MediaControl#start start()} is called.
     *   If the designated play position exceeds the media play duration,
     *   treat the play position as the end of the media when processing.
     *
     *   This function can be implemented to perform its processing either
     *   asynchronously or synchronously. If the processing takes time,
     *   implement it as asynchronous processing to avoid blocking JBlend
     *   processing for an extended period.
     *   If this function is implemented to process asynchronously, then after
     *   requesting the processing by a separate task, pass
     *    #JKMEDIA_RESULT_WAIT as the return value and promptly return control
     *   to JBlend.
     *
     *   When processing is performed synchronously in this function, return
     *    #JKMEDIA_RESULT_OK if the processing succeeds, or return
     *    #JKMEDIA_RESULT_ERROR in the following cases.
     *   <ul>
     *     <li>If processing fails.
     *     <li>If setting of the play position is not supported.
     *   </ul>
     *
     *   If processing is performed asynchronously, return #JKMEDIA_RESULT_WAIT,
     *   and notify JBlend of the result by calling AmMediaPostEvent() from a
     *   task other than the JVM task.
     *   Pass one of the following values to AmMediaPostEvent() in the <i>eventType</i> parameter.
     *   - #JKMEDIA_EVENT_JOB_DONE<br>
     *     Processing succeeds.
     *   - #JKMEDIA_EVENT_JOB_ERROR<br>
     *     Processing fails.<br>
     *     Play position setting is not supported.
     *   .
     *
     *   In no case is a negative value designated as the play position
     *   given in the <i>usecH</i> and <i>usecL</i> parameters.
     */
    JKSint32 ( *setTime )( JKSint32 id, JKUint32 usecH, JKUint32 usecL );

    /**
     * Gets the current play position.
     * @param id
     *  The player ID. The value returned by
     *   {@link JKT_MediaControl#create create()} is designated.
     * @param pUsecH
     *   A pointer to the buffer for storing the upper 32 bits of the current
     *   play position (in microseconds)
     * @param pUsecL
     *   A pointer to the buffer for storing the lower 32 bits of the current
     *   play position (in microseconds)
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; if it fails,
     *   return #JKMEDIA_RESULT_ERROR.
     *
     *   Store in the buffers designated by pUsecH and pUsecL the play
     *   position set in the player.
     */
    JKSint32 ( *getTime )( JKSint32 id, JKUint32* pUsecH, JKUint32* pUsecL );

    /**
     *  Checks whether the set media data includes audio or video data.
     * @param id
     *  The player ID. The value returned by
     *  {@link JKT_MediaControl#create create()} is designated.
     * @return
     *   Return the presence of audio and/or video in the designated media
     *   as the bitwise logical sum of the following constants.<br>
     *   #JKMEDIA_CONTENT_AUDIO<br>
     *   #JKMEDIA_CONTENT_VIDEO<br>
     *
     * JBlend regards media data as a still image if 0 has been passed as the
     * play duration by {@link JKT_MediaControl#getDuration getDuration()}
     * called in media data checking before playing, and in addition this
     * function returns #JKMEDIA_CONTENT_VIDEO.
     */
    JKSint32 ( *getIncludedContents )( JKSint32 id );

    /**
     * Pauses a player when the JVM is to be suspended.
     * @param id
     *  The player ID. The value returned by
     *   {@link JKT_MediaControl#create create()} is designated.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; if it fails,
     *   return  #JKMEDIA_RESULT_ERROR.
     *
     * This function is called when the JVM is suspended.
     * When this function is called, pause playback but do not change the state.
     * Free resources as necessary for processing in the native system.
     *
     * This function cannot return #JKMEDIA_RESULT_WAIT and cause the JVM task to wait.
     */
    JKSint32 ( *suspendVM )( JKSint32 id );

    /**
     * Resumes a player when the JVM is to be resumed.
     * @param id
     *  The player ID. The value returned by
     *   {@link JKT_MediaControl#create create()} is designated.
     * @return
     *   If the operation succeeds, return #JKMEDIA_RESULT_OK; if it fails,
     *   return #JKMEDIA_RESULT_ERROR.
     *
     * This function is called when the JVM is resumed.
     * Restore the previous status at the time #suspendVM() was called.
     *
     * This function cannot return #JKMEDIA_RESULT_WAIT and cause processing
     * to wait for the JVM task.
     */
    JKSint32 ( *resumeVM )( JKSint32 id );

    /**
     * A pointer to a function table defining event control functions.
     *
     * When MIDP or MMAPI is supported, it is necessary to implement
     * all the functions in the JKT_Media_EventControl structure and to set a
     * pointer to the structure in the <i>pEventFuncs</i> member.
     * If the functions defined in the JKT_Media_EventControl structure are
     * not supported, set JK_NULL in the <i>pEventFuncs</i> member.
     */
    JKT_Media_EventControl const* pEventFuncs;

    /**
     * A pointer to a function table defining volume control functions.
     *
     * If volume control functions are supported, it is necessary to implement
     * all the functions in the JKT_Media_VolumeControl structure and to set a
     * pointer to the structure in the <i>pVolumeFuncs</i> member.
     * If volume control functions are not supported, set JK_NULL in the
     * <i>pVolumeFuncs</i> member.
     */
    JKT_Media_VolumeControl const* pVolumeFuncs;

    /**
     *
     * A pointer to a function table defining custom control functions.
     *
     * If custom control functions are supported, it is necessary to
     * implement all the functions in the JKT_Media_UserControl structure and
     * to set a pointer to the structure in the <i>pUserFuncs</i> member.
     * If custom control functions are not supported, set JK_NULL in the
     * <i>pUserFuncs</i> member.
     *
     * When this function is supported, it is also necessary to implement the
     * Java class for the control.
     */
    JKT_Media_UserControl const* pUserFuncs;

    /**
     * A pointer to a function table defining functions for extended control.
     *
     *  @if MIDP20
     *   If only MIDP is supported, set #JK_NULL.
     *  @endif
     */
    void const* pExtFuncs;

    /**
     * A pointer to a function table defining functions for control of optional
     * features.
     *
     *  @if MIDP20
     *   If only MIDP is supported, set JK_NULL.
     *  @endif
     */
    void const* pOptionFuncs;
} JKT_MediaControl;

/**
 * Gets a list of media types supported by the native system.
 * @param pNumTypes
 *   A pointer to the buffer for storing the number of supported media types.
 * @return
 *   Return a pointer to an array listing the supported media types.
 *
 * Values of #JKMEDIA_TYPE_USER_BASE and above can be defined for media types
 * specific to the native system.
 *
 * JBlend refer to media types using the pointer returned by this
 * function. For each media type it calls #JkMediaControlGetController() to get
 * the function table defining functions for player control.
 * @see JkMediaControlGetController()
 */
JKSint32* JkMediaControlGetSupportedTypes( JKSint32* pNumTypes );

/**
 *                  Gets a list of Java profiles and Java optional packages
 *                  that support a media type.
 * @param mediaType The media type. The value designated is the one passed to
 *                  JBlend by #JkMediaControlGetSupportedTypes().
 * @return          Return a value indicating Java profiles and Java optional
 *                  packages, in which the native system supports the media type
 *                  designated in the <i>mediaType</i> parameter.
 *                  The value should be a bitwise logical sum of the constants
 *                  named starting with "JKMEDIA_PROFILE_."
 */
JKSint32 JkMediaControlGetSupportedProfiles( JKSint32 mediaType );

/**
 * Gets a function table defining player control functions.
 * @param mediaType
 *   The media type. The value designated is the one passed to JBlend by
 *   #JkMediaControlGetSupportedTypes().
 * @return
 *   Return a pointer to the function table defining player control functions.
 *   This pointer is to be kept valid until the JVM is terminated.
 *
 * The pointer to the function table defining player control functions is
 * acquired
 * only once, when the multimedia control-related classes are used in Java.
 * The native system should retain the function table so it can be referred to
 * by JBlend.
 * @see JkMediaControlGetSupportedTypes()
 */
JKT_MediaControl* JkMediaControlGetController( JKSint32 mediaType );

/**
 *  Releases the additional information memory area that has been used by the
 *  native system.
 * @param mediaType
 *  The media type of the released additional informations.
 *  In case of zero, all media types must be processed.
 * @param extraID
 *  The additional information identifier that JKT_MediaControl structure
 *   {@link JKT_MediaControl#check check()} has returned.
 *  In case of zero, release all additional information.
 *
 *  If the native system uses no additional information, implement this
 *  function as an empty function.
 */
void JkMediaControlDestroyAdditionalInfo( JKSint32 mediaType, JKSint32 extraID );

/**
 *  Notifies that devices used in the JVM are released.
 * @param mediaType
 *  The media type of the released device.
 *  This is the same value as that passed to #AmMediaBlockPlayers() in the
 *  <i>mediaType</i> parameter.
 *
 *  This function is called after processing by
 *   #AmMediaBlockPlayers( mediaType, JK_TRUE ) ends. The native system can
 *  use the devices indicated in the <i>mediaType</i> parameter after this
 *  function call is executed.
 */
void JkMediaControlNotifyDeviceReleased( JKSint32 mediaType );

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* !__JKMEDIACONTROL_H__ */

/** @} end of group */
