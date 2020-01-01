/**
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkCommConnection.h
 *  CommConnection JSI
 */
/**
 * @addtogroup Comm_Connection_JSI
 * @{
 */

#ifndef ___JK_COMM_CONNECTION_H
#define ___JK_COMM_CONNECTION_H

#include "JkTypesCommConnection.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  Allocates resources for the serial communication.
 *
 *  @param comportName
 *   A pointer to the string holding the serial port name. 
 *   The string is in ASCII code and it terminats with '\0'. This pointer is valid only inside this function.
 *  @return
 *   Return a handle which uniquely identifies the serial connection of the serial port designated by the <i>comportName</i> parameter.<br> 
 *   Return #JK_INVALID_HANDLE if it fails.
 *
 *  JBlend calls this function to allocate resources for the serial communication before requesting an actual data sending or receiving.
 *  If the operation succeeds, return the handle which uniquely identifies the serial connection of the serial port designated by the <i>comportName</i> parameter.
 *
 *  When this function is called, the native system should prepare for the serial communication.
 *
 *  At the time this function is called, the serial communication must not be started.
 *  Actual communication must be started when #JkCommConnect() is called.
 */
JKCommHandle JkCommOpen(const char* comportName);

/**
 *
 *  Sets the parameters for the serial communication.
 *
 *  @param handle
 *   The handle of the serial connection. The return value of #JkCommOpen() is designated.
 *  @param param
 *   The name of the parameter. Refer to the following table for each name.
 *
 *  @param value
 *   The value of the parameter. Refer to the following table for each value.
 *
 *  @return
 *   Return #JK_COMM_RESULT_SUCCESS if it succeeds.<br>
 *   Return #JK_COMM_RESULT_ILLEGALVALUE if the system does not support the designated value.<br>
 *   Return #JK_COMM_RESULT_FAILURE in case of other error. 
 * <p>
 * <table border=1 cellspacing=0 cellpadding=2 width="90%">
 * <caption>Table    Serial Communication Parameters Used in JkCommSetParam() and JkCommGetParam()</caption>
 * <tr>
 *  <td width="30%"><center><b>Setting Identifier</b></center></td> 
 *  <td width="30%"><center><b>Description</b></center></td>
 *  <td width="30%"><center><b>Values</b></center></td>
 * </tr>
 * <tr>
 *  <td width="30%">#JK_COMM_PARAM_TIMEOUT
 *  </td>
 *  <td width="30%">timeout
 *  </td>
 *  <td width="30%">#JK_COMM_VALUE_ON <br>(Timeout ON. The timeout period is implementation dependent.)
 *  <br> #JK_COMM_VALUE_OFF <br>(Timeout OFF)
 *  </td>
 * </tr>
 * <tr>
 *  <td width="30%">#JK_COMM_PARAM_BAUDRATE
 *  </td>
 *  <td width="30%">baudrate
 *  </td>
 *  <td width="30%">bitrate (in bps)
 *  </td>
 * </tr>
 * <tr>
 *  <td width="30%">#JK_COMM_PARAM_BITSPERCHAR
 *  </td>
 *  <td width="30%">bitsperchar
 *  </td>
 *  <td width="30%">The number bits per character (7 or 8)
 *  </td>
 * </tr>
 * <tr>
 *  <td width="30%">#JK_COMM_PARAM_STOPBITS
 *  </td>
 *  <td width="30%">stopbits
 *  </td>
 *  <td width="30%">The number of stop bits per char (1 or 2)
 *  </td>
 * </tr>
 * <tr>
 *  <td width="30%">#JK_COMM_PARAM_PARITY
 *  </td>
 *  <td width="30%">parity
 *  </td>
 *  <td width="30%">#JK_COMM_PARITY_NONE<br>#JK_COMM_PARITY_ODD<br>#JK_COMM_PARITY_EVEN
 *  </td>
 * </tr>
 * <tr>
 *  <td width="30%">#JK_COMM_PARAM_RXBLOCKING
 *  </td>
 *  <td width="30%">blocking while receiving data
 *  </td>
 *  <td width="30%">#JK_COMM_VALUE_ON <br>(blocking)<br> #JK_COMM_VALUE_OFF <br>(No blocking)
 *  </td>
 * </tr>
 * <tr>
 *  <td width="30%">#JK_COMM_PARAM_AUTOCTS
 *  </td>
 *  <td width="30%">CTS control
 *  </td>
 *  <td width="30%">#JK_COMM_VALUE_ON <br>(CTS control)<br>#JK_COMM_VALUE_OFF <br>(No CTS control)
 *  </td>
 * </tr>
 * <tr>
 * <td width="30%">#JK_COMM_PARAM_AUTORTS
 *  </td>
 *  <td width="30%">RTS control
 *  </td>
 *  <td width="30%">#JK_COMM_VALUE_ON <br>(RTS control)<br>#JK_COMM_VALUE_OFF <br>(No RTS control)
 *  </td>
 * </tr>
 * <tr>
 *  <td width="30%">#JK_COMM_PARAM_EXTRA_CONNECT_TIMEOUT 
 *  </td>
 *  <td width="30%">Timeout period of #JkCommConnect()<br><b>(EXTENDED)</b>
 *  </td>
 *  <td width="30%">Timeout period of #JkCommConnect() (in msec)
 *  </td>
 * </tr>
 * <tr>
 *  <td width="30%">#JK_COMM_PARAM_EXTRA_READ_TIMEOUT
 *  </td>
 *  <td width="30%">Timeout period of #JkCommRead()<br><b>(EXTENDED)</b>
 *  </td>
 *  <td width="30%">Timeout period of #JkCommRead() (in msec)
 *  </td>
 * </tr>
 * <tr>
 *  <td width="30%">#JK_COMM_PARAM_EXTRA_WRITE_TIMEOUT
 *  </td>
 *  <td width="30%">Timeout period of #JkCommWrite()<br><b>(EXTENDED)</b>
 *  </td>
 *  <td width="30%">Timeout period of #JkCommWrite() (in msec)
 *  </td>
 * </tr>
 *</table>
 *<br>
 *<br>
 *
 * 
 * For the serial connection designated by the <i>handle</i> parameter, configure the serial communication setting designated by the <i>param</i> parameter by the value designated by the <i>value</i> parameter.
 *<p>
 * If a baudrate parameter has been passed in optional parameters of the URL passed to <code>Connection.open</code> or if <code>CommConnection</code> <code>setBaudRate</code> method is called, JBlend calls this function to set the designated baudrate. If a MIDlet does not designate baudrate in either way, JBlend does not set baudrate. In this case, the native system is to use the system's initial value for baudrate.
 *   
 * When #JK_COMM_RESULT_ILLEGALVALUE is returned in configuring baudrate setting, JBlend assumes that the baudrate has not been changed and continues the processing of Java API without throwing an exception. If #JK_COMM_RESULT_ILLEGALVALUE is returned when performing other parameter settings, JBlend throws an exception to the MIDlet. 
 * If the parameters that are neither baudrate nor extended parameters are passed in optional parameters in the URL, the designated values are set by this function. If the parameters are not passed, the default values specified in MIDP are set. 
 *
 *The initial values of the extended parameters will be mentioned in the documents describing the extended features of CommConnection.
 *
 */
JKSint JkCommSetParam(JKCommHandle handle, JKSint32 param, JKSint32 value);

/**
 *  Gets the value of a serial communication setting.
 *
 *  @param handle
 *   The handle of the serial connection. The return value of #JkCommOpen() is designated. 
 *  @param param
 *   The name of the parameter whose value is to be obtained. Refer to the description of #JkCommSetParam() for each name.
 *
 *  @param value
 *   A pointer to the buffer for putting the value. Refer to the description of #JkCommSetParam() for each value to be stored.
 *
 *
 *  @return
 *   Return #JK_COMM_RESULT_SUCCESS if it succeeds.<br>
 *   Return #JK_COMM_RESULT_FAILURE if it fails. <br>
 *
 *  For the serial connection designated by the <i>handle</i> parameter, store the value of the parameter designated by the <i>param</i> parameter to the buffer designated by the <i>value</i> parameter.
 *
 *
 */
JKSint JkCommGetParam(JKCommHandle handle, JKSint32 param, JKSint32* value);

/**
 *  Starts a serial communication.
 *
 *  @param handle
 *   The handle of the serial connection. The return value of #JkCommOpen() is designated. 
 *  @return
 *   Return #JK_COMM_RESULT_SUCCESS if it succeeds.<br> 
 *   Return #JK_COMM_RESULT_FAILURE if it fails. <br>
 *
 *  Start the communication with the serial connection designated 
 *  by the <i>handle</i> parameter.
 *
 *
 * This function can be implemented either as an asynchronous function or as a synchronous function.
 * If the processing by this function is likely to block JBlend processing for an extended period,
 * it should be implemented as an asynchronous function.
 *
 *@htmlonly
 *<p>
 * <b>Asynchronous Implementation</b><br>
 * <blockquote>
 *@endhtmlonly
 * In case of implementing this function as an asynchronous processing, after requesting the processing by 
 * a separate task, return control to JBlend as soon as possible, putting #JK_COMM_RESULT_SUCCESS in the return value.
 * Call AmNotifyCommEvent() from a native system task to notify JBlend of the result of this function. 
 * The values to be passed to the parameters of #AmNotifyCommEvent() should be as follows.
 *
 *	<dl>
 *	<dt><b><i>handle</i></b></dt>
 * 	<dd>The value designated to the <i>handle</i> parameter of #JkCommConnect()</dd>
 *	<dt><b><i>event</i></b></dt>
 * 	<dd>#JK_COMM_EVENT_CONNECT</dd>
 *	<dt><b><i>result</i></b></dt><br><br>
 * 	<dd>#JK_COMM_RESULT_SUCCESS if the operation succeeds.</dd>
 * 	<dd>#JK_COMM_RESULT_TIMEOUT if the operation times out.</dd>
 * 	<dd>#JK_COMM_RESULT_FAILURE if the operation fails with other error.</dd>
 *	</dl>
 *
 * If requesting to a separate task fails or an error occurs before returning to the caller, 
 * #JkCommConnect() should return #JK_COMM_RESULT_FAILURE and the native system must not call #AmNotifyCommEvent().
 *
 *
 *@htmlonly
 * <p>
 * </blockquote>
 * <b>Synchronous Implementation</b><br>
 * <blockquote>
 *@endhtmlonly
 * In case of implementing this function as a synchronous processing, if the operation succeeds, 
 * call #AmNotifyCommEvent() from inside #JkCommConnect() to notify JBlend of the result of the operation 
 * and return #JK_COMM_RESULT_SUCCESS. If the operation fails, return #JK_COMM_RESULT_FAILURE and do not call 
 * #AmNotifyCommEvent(). 
 *@htmlonly
 * </blockquote>
 *@endhtmlonly
 *
 */
JKSint JkCommConnect(JKCommHandle handle);

/**
 *  Receives data.
 *
 *  @param handle
 *   The handle of the serial connection. The return value of #JkCommOpen() is designated.
 *  @param buffer
 *   A pointer to the buffer for putting the received data.
 *   This buffer is valid either until the operation completes by calling #AmNotifyCommEvent() or until this function fails.
 *
 *  @param length
 *   The size (in bytes) of the buffer indicated by the <i>buffer</i> parameter.
 *  @return
 *   Return #JK_COMM_RESULT_SUCCESS if it succeeds.<br> 
 *   Return #JK_COMM_RESULT_FAILURE if it fails. <br>
 *
 * In the native system, receive the data to the buffer designated by the <i>buffer</i> parameter and the <i>length</i> parameter from the serial connection designated by the <i>handle</i> parameter. 
 *
 * This function can be implemented either as an asynchronous function or as a synchronous function.
 * If the processing by this function is likely to block JBlend processing for an extended period,
 * it should be implemented as an asynchronous function.
 *
 *@htmlonly
 *<p>
 * <b>Asynchronous Implementation</b><br>
 * <blockquote>
 *@endhtmlonly
 * In case of implementing this function as an asynchronous processing, after requesting the processing by 
 * a separate task, return control to JBlend as soon as possible, putting #JK_COMM_RESULT_SUCCESS in the return value.
 * Call AmNotifyCommEvent() from a native system task to notify JBlend of the result of this function. 
 * The values to be passed to the parameters of #AmNotifyCommEvent() should be as follows.
 *
 *	<dl>
 *	<dt><b><i>handle</i></b></dt>
 * 	<dd>The value designated to the <i>handle</i> parameter of #JkCommRead()</dd>
 *	<dt><b><i>event</i></b></dt>
 * 	<dd>#JK_COMM_EVENT_READ</dd>
 *	<dt><b><i>result</i></b></dt><br><br>
 * 	<dd>The size (in bytes) of actually received data if the operation succeeds.</dd>
 * 	<dd>#JK_COMM_RESULT_TIMEOUT if the operation times out.</dd>
 * 	<dd>#JK_COMM_RESULT_DISCONNECTED if the operation fails by the accidental disconnection of the communication line during receive processing.</dd>
 * 	<dd>#JK_COMM_RESULT_FAILURE if the operation fails with other error.</dd>
 *	</dl>
 *
 * If requesting to a separate task fails or an error occurs before returning to the caller, 
 * #JkCommRead() should return #JK_COMM_RESULT_FAILURE and the native system must not call #AmNotifyCommEvent().
 *
 *
 *@htmlonly
 * <p>
 * </blockquote>
 * <b>Synchronous Implementation</b><br>
 * <blockquote>
 *@endhtmlonly
 *
 * In case of implementing this function as a synchronous processing, if the operation succeeds, 
 * call #AmNotifyCommEvent() from inside #JkCommRead() to notify JBlend of the result of the operation 
 * and return #JK_COMM_RESULT_SUCCESS. If the operation fails, return #JK_COMM_RESULT_FAILURE and do not call 
 * #AmNotifyCommEvent(). 
 *
 *@htmlonly
 * </blockquote>
 *@endhtmlonly
 *<p>
 * This function is not called more than once for the same serial connection before the the result of the processing is passed to JBlend. However, there could be a sending request to the same serial connection or receiving requests to other serial connections.
 * 
 * If #JK_COMM_PARAM_RXBLOCKING has been set to ON by #JkCommSetParam(), make an event notification to JBlend
 * after receiving as much data as designated by the <i>length</i> parameter.
 *  If #JK_COMM_PARAM_RXBLOCKING has been set to OFF, make event notification to JBlend after
 *  moving up to <i>length</i> data of the data existing in the receive buffer at that point in time. 
 *  Even if the receive buffer is empty, pass the event with 0 set in <i>result</i>.
 *
 * If #JK_COMM_PARAM_TIMEOUT has been set to ON by #JkCommSetParam() and the native system cannot receive 
 * the data after a certain period of time, notify JBlend of #JK_COMM_RESULT_TIMEOUT by #AmNotifyCommEvent().
 *
 *
 */
JKSint32 JkCommRead(JKCommHandle handle, JKSint8* buffer, JKSint32 length);

/**
 *  Sends data.
 *
 *  @param handle
 *   The handle of the serial connection. The return value of #JkCommOpen() is designated.
 *  @param buffer
 *   A pointer to the buffer holding the data to be sent.
 *   This buffer is valid either until the operation completes by calling #AmNotifyCommEvent() or until this function fails.
 *  @param length
 *   The size (in bytes) of the data to be sent in the buffer designated by the <i>buffer</i> parameter.
 *  @return
 *   Return #JK_COMM_RESULT_SUCCESS if it succeeds.<br>
 *   Return #JK_COMM_RESULT_FAILURE if it fails.
 *
 * In the native system, send the data in the buffer designated by the <i>buffer</i> parameter and the <i>length</i> parameter to the serial connection designated by the <i>handle</i> parameter.
 *
 * This function can be implemented either as an asynchronous function or as a synchronous function.
 * If the processing by this function is likely to block JBlend processing for an extended period,
 * it should be implemented as an asynchronous function.
 *
 *@htmlonly
 *<p>
 * <b>Asynchronous Implementation</b><br>
 * <blockquote>
 *@endhtmlonly
 * In case of implementing this function as an asynchronous processing, after requesting the processing by 
 * a separate task, return control to JBlend as soon as possible, putting #JK_COMM_RESULT_SUCCESS in the return value.
 * Call AmNotifyCommEvent() from a native system task to notify JBlend of the result of this function. 
 * The values to be passed to the parameters of #AmNotifyCommEvent() should be as follows.
 *
 *	<dl>
 *	<dt><b><i>handle</i></b></dt>
 * 	<dd>The value designated to the <i>handle</i> parameter of #JkCommWrite()</dd>
 *	<dt><b><i>event</i></b></dt>
 * 	<dd>#JK_COMM_EVENT_WRITE</dd>
 *	<dt><b><i>result</i></b></dt><br><br>
 * 	<dd>The size (in bytes) of actually sent data if the operation succeeds.</dd>
 * 	<dd>#JK_COMM_RESULT_TIMEOUT if the operation times out.</dd>
 * 	<dd>#JK_COMM_RESULT_DISCONNECTED if the operation fails by the accidental disconnection of the communication line during send processing.</dd>
 * 	<dd>#JK_COMM_RESULT_FAILURE if the operation fails with other error.</dd>
 *	</dl>
 *
 * If requesting to a separate task fails or an error occurs before returning to the caller, 
 * #JkCommWrite() should return #JK_COMM_RESULT_FAILURE and the native system must not call #AmNotifyCommEvent().
 *
 *
 *@htmlonly
 * <p>
 * </blockquote>
 * <b>Synchronous Implementation</b><br>
 * <blockquote>
 *@endhtmlonly
 *
 * In case of implementing this function as a synchronous processing, if the operation succeeds, 
 * call #AmNotifyCommEvent() from inside #JkCommWrite() to notify JBlend of the result of the operation 
 * and return #JK_COMM_RESULT_SUCCESS. If the operation fails, return #JK_COMM_RESULT_FAILURE and do not call 
 * #AmNotifyCommEvent(). 
 *
 *@htmlonly
 * </blockquote>
 *@endhtmlonly
 *<p>
 * The native system may assume that the processing has completed at the time the data is sent to the device driver.
 *<p>
 * This function is not called more than once for the same serial connection before the the result of the processing 
 * is passed to JBlend. However, there could be a receiving request to the same serial connection or sending requests 
 * to other serial connections.
 *
 * If #JK_COMM_PARAM_TIMEOUT has been set to ON by #JkCommSetParam() and the native system cannot send the data after
 * a certain period of time, notify JBlend of #JK_COMM_RESULT_TIMEOUT by #AmNotifyCommEvent().
 *
 *
 */
JKSint32 JkCommWrite(JKCommHandle handle, const JKSint8* buffer, JKSint32 length);

/**
 *  Obtains the size of data in the receive buffer.
 *
 *  @param handle
 *   The handle of the serial connection. The return value of #JkCommOpen() is designated.
 *
 *  @return
 *   Return the size (in bytes) of data in the receive buffer if it succeeds.<br>
 *   Return #JK_COMM_RESULT_FAILURE if it fails.
 */
JKSint32 JkCommAvailable(JKCommHandle handle);

/**
 *  Disconnects the serial communication.
 *
 *  @param handle
 *   The handle of the serial connection. The return value of #JkCommOpen() is designated.
 *  @return
 *   Return #JK_COMM_RESULT_SUCCESS if it succeeds.<br>
 *   Return #JK_COMM_RESULT_FAILURE if it fails.
 *
 *  In the native system, disconnect the serial communication of the connection designated by the <i>handle</i> parameter.
 *
 * This function can be implemented either as an asynchronous function or as a synchronous function.
 * If the processing by this function is likely to block JBlend processing for an extended period,
 * it should be implemented as an asynchronous function.
 *
 *@htmlonly
 *<p>
 * <b>Asynchronous Implementation</b><br>
 * <blockquote>
 *@endhtmlonly
 * In case of implementing this function as an asynchronous processing, after requesting the processing by 
 * a separate task, return control to JBlend as soon as possible, putting #JK_COMM_RESULT_SUCCESS in the return value.
 * Call AmNotifyCommEvent() from a native system task to notify JBlend of the result of this function. 
 * The values to be passed to the parameters of #AmNotifyCommEvent() should be as follows.
 *
 *	<dl>
 *	<dt><b><i>handle</i></b></dt>
 * 	<dd>The value designated to the <i>handle</i> parameter of #JkCommDisconnect()</dd>
 *	<dt><b><i>event</i></b></dt>
 * 	<dd>#JK_COMM_EVENT_DISCONNECT</dd>
 *	<dt><b><i>result</i></b></dt><br><br>
 * 	<dd>#JK_COMM_RESULT_SUCCESS if the operation succeeds.</dd>
 * 	<dd>#JK_COMM_RESULT_TIMEOUT if the operation times out.</dd>
 * 	<dd>#JK_COMM_RESULT_FAILURE if the operation fails with other error.</dd>
 *	</dl>
 *
 * If requesting to a separate task fails or an error occurs before returning to the caller, 
 * #JkCommDisconnect() should return #JK_COMM_RESULT_FAILURE and the native system must not call #AmNotifyCommEvent().
 *
 *
 *@htmlonly
 * <p>
 * </blockquote>
 * <b>Synchronous Implementation</b><br>
 * <blockquote>
 *@endhtmlonly
 *
 * In case of implementing this function as a synchronous processing, if the operation succeeds, 
 * call #AmNotifyCommEvent() from inside #JkCommDisconnect() to notify JBlend of the result of the operation 
 * and return #JK_COMM_RESULT_SUCCESS. If the operation fails, return #JK_COMM_RESULT_FAILURE and do not call 
 * #AmNotifyCommEvent(). 
 *
 *@htmlonly
 * </blockquote>
 *@endhtmlonly
 * <p>
 * In addition to the event notification of the processing result of JkCommDisconnect(), make sure to do the following processing. 
 * If this function is called in the middle of the processing of #JkCommRead() or #JkCommWrite(),  
 * terminate each processing and notify JBlend of #JK_COMM_RESULT_TIMEOUT for each processing regardless of the
 * value of #JK_COMM_PARAM_TIMEOUT which has been set by #JkCommSetParam(). The event notification of 
 * #JK_COMM_RESULT_TIMEOUT should be done before the result of the #JkCommDisconnect() is passed to JBlend.
 */
JKSint JkCommDisconnect(JKCommHandle handle);

/**
 *  Releases the resources for the serial communication.
 *
 *  @param handle
 *   The handle of the serial connection. The return value of #JkCommOpen() is designated.
 *  @return
 *   Return #JK_COMM_RESULT_SUCCESS if it succeeds.<br>
 *   Return #JK_COMM_RESULT_FAILURE if it fails.<br>
 *
 *  In the native system, release resources for the serial connection
 *  designated by the <i>handle</i> parameter.
 *
 * If this function is called in the middle of the processing of #JkCommConnect(), #JkCommDisconnect(), #JkCommRead()
 * or #JkCommWrite(), terminate each processing and notify JBlend of #JK_COMM_RESULT_TIMEOUT for each processing 
 * regardless of the value of #JK_COMM_PARAM_TIMEOUT which has been set by #JkCommSetParam().
 *
 *
 */
JKSint JkCommClose(JKCommHandle handle);

#ifdef __cplusplus
}
#endif

#endif /* ___JK_COMM_CONNECTION_H */

/**
 * @} end of group
 */
