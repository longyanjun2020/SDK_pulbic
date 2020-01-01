/*
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkTypesCommConnection.h
 *  Data types and constant values for serial communication
 */
/**
 * @addtogroup Comm_Connection_Data_Types
 * @{
 */

#ifndef ___JK_COMM_TYPES_H
#define ___JK_COMM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 *   The type of handles for the serial communication
 */
typedef JKHandle JKCommHandle;


/**
 *  Succeeded.
 * This is used as a return value of CommConnection JSI functions or is set to the <i>result</i> parameter of #AmNotifyCommEvent().
*/
#define JK_COMM_RESULT_SUCCESS       (0)

/**
 *  Failed.
 *  This is used as a return value of the CommConnection JSI function or is set to the <i>result</i> parameter of #AmNotifyCommEvent().
 */
#define JK_COMM_RESULT_FAILURE      (-1)

/**
 *  The designated value is invalid.
 *  This is used as a return value of #JkCommSetParam().
 */
#define JK_COMM_RESULT_ILLEGALVALUE (-2)

/**
 *  Failed by timeout.
 *
 *  This is set to the <i>result</i> parameter of #AmNotifyCommEvent().
 */
#define JK_COMM_RESULT_TIMEOUT      (-3)

/**
 *  The disconnection of the communication line has been detected.
 *
 *  This is set to the <i>result</i> parameter of #AmNotifyCommEvent().
 */
#define JK_COMM_RESULT_DISCONNECTED (-4)

/**
 *  Timed out
 *
 * This is set to the <i>param</i> parameter of #JkCommSetParam() and #JkCommGetParam() to designate a communication setting.
 * #JK_COMM_VALUE_ON or #JK_COMM_VALUE_OFF is set to the <i>value</i> parameter.
 */
#define JK_COMM_PARAM_TIMEOUT     (0)

/**
 *  Baudrate.
 *
 * This is set to the <i>param</i> parameter of #JkCommSetParam() and #JkCommGetParam() to designate a communication setting.
 * A bitrate (e.g. 9600, 115200) is set to the <i>value</i> parameter.
 */
#define JK_COMM_PARAM_BAUDRATE    (1)

/**
 *  Bits per character.
 *
 * This is set to the <i>param</i> parameter of #JkCommSetParam() and #JkCommGetParam() to designate a communication setting.
 * The number bits per character (7 or 8) is set to the <i>value</i> parameter.
 */
#define JK_COMM_PARAM_BITSPERCHAR (2)

/**
 *  Stop bits.
 *
 * This is set to the <i>param</i> parameter of #JkCommSetParam() and #JkCommGetParam() to designate a communication setting.
 * The number of stop bits per char (1 or 2) is set to the <i>value</i> parameter.
 */

#define JK_COMM_PARAM_STOPBITS    (3)
/**
 *  Parity.
 *
 * This is set to the <i>param</i> parameter of #JkCommSetParam() and #JkCommGetParam() to designate a communication setting.
 * #JK_COMM_PARITY_NONE, #JK_COMM_PARITY_ODD or #JK_COMM_PARITY_EVEN is set to
 *  the <i>value</i> parameter.
 */
#define JK_COMM_PARAM_PARITY      (4)

/**
 *  Blocking.
 * This is set to the <i>param</i> parameter of #JkCommSetParam() and #JkCommGetParam() to designate a communication setting.
 * #JK_COMM_VALUE_ON or #JK_COMM_VALUE_OFF is set to the <i>value</i> parameter.
 *  For the details, refer to the Java API specification.
 */
#define JK_COMM_PARAM_RXBLOCKING    (5)

/**
 *  CTS control.
 * This is set to the <i>param</i> parameter of #JkCommSetParam() and #JkCommGetParam() to designate a communication setting.
 *  #JK_COMM_VALUE_ON or #JK_COMM_VALUE_OFF is set to the <i>value</i> parameter.
 *
 */
#define JK_COMM_PARAM_AUTOCTS     (6)

/**
 *  RTS control.
 * This is set to the <i>param</i> parameter of #JkCommSetParam() and #JkCommGetParam() to designate a communication setting.
 *  #JK_COMM_VALUE_ON or #JK_COMM_VALUE_OFF is set to the <i>value</i> parameter.
 */
#define JK_COMM_PARAM_AUTORTS     (7)

/**
 *  Timeout period for establishing the connection. <b>*EXTENDED*</b>
 *
 *  This is an extended feature for some profiles.
 *  It is not in the MIDP standard specification.<p>
 * This is set to the <i>param</i> parameter of #JkCommSetParam() and #JkCommGetParam() to designate a communication setting.
 *  Timeout period (in msec) is set to the <i>value</i> parameter.
 *  -1 means no timeout needed. (wait infinitely)
 */
#define JK_COMM_PARAM_EXTRA_CONNECT_TIMEOUT (101)

/**
 *  Timeout period for receiving data. <b>*EXTENDED*</b>
 *
 *  This is an extended feature for some profiles.
 *  It is not in the MIDP standard specification.<p>
 * This is set to the <i>param</i> parameter of #JkCommSetParam() and #JkCommGetParam() to designate a communication setting.
 *  Timeout period (in msec) is set to the <i>value</i> parameter.
 *  -1 means no timeout needed. (wait infinitely)
 */
#define JK_COMM_PARAM_EXTRA_READ_TIMEOUT      (102)

/**
 *  Timeout period for sending data. <b>*EXTENDED*</b>
 *
 *  This is an extended feature for some profiles.
 *  It is not in the MIDP standard specification.<p>
 * This is set to the <i>param</i> parameter of #JkCommSetParam() and #JkCommGetParam() to designate a communication setting.
 *  Timeout period (in msec) is set to the <i>value</i> parameter.
 *  -1 means no timeout needed. (wait infinitely)
 */
#define JK_COMM_PARAM_EXTRA_WRITE_TIMEOUT      (103)

/**
 *  ON
 *
 *  This is set to the <i>value</i> parameter of #JkCommSetParam() to designate a communication parameter value. 
 */
#define JK_COMM_VALUE_ON  (1)
/**
 *  OFF
 *
 *  This is set to the <i>value</i> parameter of #JkCommSetParam() to designate a communication parameter value. 
 */
#define JK_COMM_VALUE_OFF (0)
/**
 *  No parity.
 *
 *  This is set to the <i>value</i> parameter of #JkCommSetParam() to designate a communication parameter value. 
 */
#define JK_COMM_PARITY_NONE (0)
/**
 *  Odd parity.
 *
 *  This is set to the <i>value</i> parameter of #JkCommSetParam() to designate a communication parameter value. 
 */
#define JK_COMM_PARITY_ODD  (1)
/**
 *  Even parity.
 *
 *  This is set to the <i>value</i> parameter of #JkCommSetParam() to designate a communication parameter value. 
 */
#define JK_COMM_PARITY_EVEN (2)

/**
 *  An event to notify JBlend of the disconnection of the communication line.
 *
 * This is set to the <i>event</i> parameter of #AmNotifyCommEvent() to designate an event. 
 * This is used when the native system detects the disconnection of the communication line 
 * while the native system is not processing the request from JBlend.  
 */
#define JK_COMM_EVENT_STATECHANGED (0)

/**
 *  An event to notify JBlend of the result of the connection processing.
 *
 * This is set to the <i>event</i> parameter of #AmNotifyCommEvent() to designate an event. 
 * This is used to notify JBlend of the result of #JkCommConnect().
 *
 */
#define JK_COMM_EVENT_CONNECT    (1)

/**
 *  An event to notify JBlend of the result of the receive processing.
 *
 * This is set to the <i>event</i> parameter of #AmNotifyCommEvent() to designate an event. 
 * This is used to notify JBlend of the result of #JkCommRead().
 */
#define JK_COMM_EVENT_READ       (2)


/**
 *  An event to notify JBlend of the result of the send processing.
 *
 * This is set to the <i>event</i> parameter of #AmNotifyCommEvent() to designate an event. 
 * This is used to notify JBlend of the result of #JkCommWrite().
 */
#define JK_COMM_EVENT_WRITE      (3)

/**
 *  An event to notify JBlend of the result of the disconnection processing.
 *
 * This is set to the <i>event</i> parameter of #AmNotifyCommEvent() to designate an event. 
 * This is used to notify JBlend of the result of #JkCommDisconnect().
*/
#define JK_COMM_EVENT_DISCONNECT (4)

#ifdef __cplusplus
}
#endif

#endif /* ___JK_COMM_TYPES_H */

/**
 * @} end of group
 */
