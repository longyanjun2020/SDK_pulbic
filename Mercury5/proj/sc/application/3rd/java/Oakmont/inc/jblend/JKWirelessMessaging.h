/*
 * Copyright 2002-2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file JKWirelessMessaging.h
 *  @if WMA20
 *  Wireless Messaging API SMS/CBS Communication JSI Header File
 *  @else
 *  Wireless Messaging Communication JSI Header File
 *  @endif
 */

/**
 *  @if WMA20
 *  @addtogroup WMA_SMS_JSI
 *  @else
 *  @addtogroup WMA_STD_JSI
 *  @endif
 * @{
 */

#ifndef __JKWIRELESSMESSAGING_H__
#define __JKWIRELESSMESSAGING_H__

#include "JKWirelessMessagingTypedef.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  Message type definitions
 */

/**
 *
 * Message type indicating a text message
 */
#define JK_WMA_MESSAGE_TYPE_TEXT 1

/**
 * Message type indicating a binary message.
 */
#define JK_WMA_MESSAGE_TYPE_BINARY 2


/*
 *  Return value definitions
 */

/**
 * Operation completed.
 */
#define JK_WMA_OK	0

/**
 *  Communication not permitted.
 */
#define JK_WMA_ERROR_NOT_PERMITTED	(-1)

/**
 *  Cannot create a connection.
 */
#define JK_WMA_ERROR_CONNECTION_CANT_CREATE	(-2)

/**
 * The protocol does not exist.
 */
#define JK_WMA_ERROR_PROTOCOL_DOESNOT_EXIST	(-3)

/**
 * An I/O error occurred.
 */
#define JK_WMA_ERROR_IO_ERROR	(-4)

/**
 *  Payload exceeds the maximum size.
 */
#define JK_WMA_ERROR_PAYLOAD_OVER	(-5)

/**
 *  No messages in the connection receive queue.
 */
#define JK_WMA_ERROR_NO_DATA_RECEIVED	(-6)


/**
 * A structure containing message-related information.
 *
 * This structure type is used when JBlend passes a send message to the native
 * system by using #JkWmaSendMessage().
 * It is used also when JBlend issues a request to the native system for receive
 * message information or data by using #JkWmaGetReceivedMessageInfo() or
 * #JkWmaReceiveMessage(). 
 *
 * @see JkWmaSendMessage()
 * @see JkWmaGetReceivedMessageInfo()
 * @see JkWmaReceiveMessage()
 */
typedef struct JKT__Wma_Message {
    /**
     * The message type. Either of the following values is designated.
     * <ul>
     *  <li>If a text message, #JK_WMA_MESSAGE_TYPE_TEXT.
     *  <li>If a binary message, #JK_WMA_MESSAGE_TYPE_BINARY.
     * </ul>
     */
    JKSint32   type;

    /**
     * A URL indicating a message-related address.
     * <ul>
     *  <li>If a send message, the destination address.
     *  <li>If a receive message, the sender's address.
     *    If the receive message does not contain the senders's address, JK_NULL.
     * </ul>
     */
    JKUint8*   url;

    /**
     * The size in octets of the URL string pointed to by the <i>url</i> member.
     * <ul>
     *  <li>If a send message, the length of the destination address.
     *  <li>If a receive message, the length of the sender's address.
     *     If the receive message does not contain the senders's address, 0.
     * </ul>
     */
    JKSint32   urlLength;

    /**
     * A flag indicating whether the time of sending is set in a receive message.
     * <ul>
     *  <li>If a send message, JK_FALSE.
     *  <li>If a receive message,
     *  then JK_TRUE if the time of sending is set in timeStampHigh and
     *  timeStampLow, else JK_FALSE.
     * </ul>
     */
    JKBool   isTimeStampAvailable;

    /**
     * The high 32 bits of the time stamp (time of sending, GMT, in milliseconds) set
     * in a receive message.
     *
     * This member is valid if the isTimeStampAvailable member is JK_TRUE.
     */
    JKUint32   timeStampHigh;

    /**
     * The low 32 bits of the time stamp (time of sending, GMT, in milliseconds) set
     * in a receive message.
     *
     * This member is valid if the isTimeStampAvailable member is JK_TRUE.
     */
    JKUint32   timeStampLow;

    /**
     * Length (in octets) of payload data in a binary message.
     *
     * This member is valid if the type member is #JK_WMA_MESSAGE_TYPE_BINARY.
     */
    JKSint32   binaryDataLength;

    /**
     * A pointer to the memory location containing payload data in the case of a
     * binary message.
     *
     * This member is valid if the type member is #JK_WMA_MESSAGE_TYPE_BINARY.
     */
    JKUint8*   binaryData;

    /**
     * The number of characters of payload data in the case of a text message.
     *
     * This member is valid if the type member is #JK_WMA_MESSAGE_TYPE_TEXT.
     */
    JKSint32   textDataLength;

    /**
     * A pointer to the memory location containing payload data in the case of a
     * text message.
     *
     * This member is valid if the type member is #JK_WMA_MESSAGE_TYPE_TEXT.
     */
    JKWChar*   textData;

} JKT_Wma_Message;


/**
 *  Opens a connection.
 *   @param url
 *     The URL.
 *   @param urlLength
 *     The length (in bytes) of the URL.
 *   @param connectionHandle
 *     A pointer to the buffer where the handle value issued for the connection
 *     goes.<br>
 *     If a connection is opened successfully, put a connection handle in the memory
 *     location indicated by this pointer. If it fails, put #JK_INVALID_HANDLE.<br>
 *   @return
 *     Return  #JK_WMA_OK if the operation succeeds.<br>
 *     In case of failure, return one of the following error codes.
 *     <dl>
 *      <dt>#JK_WMA_ERROR_NOT_PERMITTED</dt>
 *       <dd>Communication is not permitted on the connection designated in the URL. </dd>
 *      <dt>#JK_WMA_ERROR_PROTOCOL_DOESNOT_EXIST</dt>
 *       <dd>The protocol designated in the URL is not supported.</dd>
 *      <dt>#JK_WMA_ERROR_CONNECTION_CANT_CREATE</dt>
 *       <dd>The port number designated in the URL is in use or reserved.</dd>
 *      <dt>#JK_WMA_ERROR_IO_ERROR</dt>
 *       <dd>An I/O error occurred.</dd>
 *     </dl>
 *<p>
 *     Create a connection for Wireless Messaging API use, issue a handle identifying
 *     the connection uniquely, and put the handle in the buffer indicated by the
 *     connectionHandle argument.
 *
 *     Decide the adaptor for the connection based on the scheme of the URL
 *     designated in the url argument.
 *     If the URL contains an address part, a client mode connection is created.
 *     If the URL has no address part, it is a server mode connection.
 *
 *     In the case of a server mode connection, the following points should be 
 *     taken into consideration.
 *     - If the URL does not designate a port number,
 *       a port number not used by the device must be assinged by the native system.
 *       Note, however, that in no case is the URL port number omitted for a 
 *       GSM SMS adapter or CBS adapter.
 *     - A queue for holding received messages is necessary. 
 *       The queue should be FIFO, meaning messages are fetched from the oldest.
 *     .
 *
 *     Until JBlend closes the connection by calling #JkWmaClose(), the handle 
 *     passed by this function is used as a connection ID. The native system must keep
 *     track of the association between this handle and the connection and its 
 *     assigned resources, so that they can be identified by the handle. 
 *
 *     If the connection designated in the url parameter is monitored by
 *     the native system for push registry as specified in MIDP 2.0,
 *     the function must be implemented so as to ensure the following:
 *      - That the connection can be opened normally without errors.
 *      - That messages received before the connection was opened 
 *      can also be retrieved from the queue by JBlend using
 *      #JkWmaGetReceivedMessageInfo() and #JkWmaReceiveMessage().
 */
JKSint32 JkWmaOpen( JKUint8* url,JKSint32 urlLength, JKHandle* connectionHandle);

/**
 *  Closes a connection
 *   @param connectionHandle
 *     The handle of the connection to be closed.
 *     The handle issued by #JkWmaOpen() is designated.
 *   @return
 *     If the operation succeeds, return #JK_WMA_OK.<br>
 *     If an error occurred, return #JK_WMA_ERROR_IO_ERROR.
 *
 *  This function is called to close the connection designated by the connectionHandle
 *  parameter. Free the resources allocated to the designated connection. Once this
 *  function has been called, the connection designated by connectionHandle can no
 *  longer be used.
 *
 *  Do not allow an I/O wait to occur for this function.
 *
 *  If the connection designated by the connectionHandle parameter is monitored by
 *  the native system for push registry as specified in MIDP 2.0, the implementation of this function
 *  must not have any influence on connection monitoring by the native system.
 */
JKSint32 JkWmaClose( JKHandle connectionHandle );

/**
 *  Calculates the number of segments required for message sending.
 *   @param connectionHandle
 *     The handle of the connection for sending the message.
 *     The handle issued by #JkWmaOpen() is designated.
 *   @param message
 *     A pointer to the #JKT_Wma_Message structure containing information about
 *     the send message.
 *   @return
 *     Return the number of segments required to send the message.
 *     If the message size exceeds the maximum that can be sent, return 0.
 */
JKSint32 JkWmaNumberOfSegments( JKHandle connectionHandle, JKT_Wma_Message* message );

/**
 *  Calculates the number of segments required for message sending based on the URL.
 *   @param url
 *     The URL of the connection.
 *   @param urlLength
 *     The length (in bytes) of the URL.
 *   @param message
 *     A pointer to the #JKT_Wma_Message structure containing information about
 *     the send message.
 *   @return
 *     Return the number of segments required to send the designated message by the protocol
 *     associated with the designated URL.
 *     If the message size exceeds the maximum that can be sent, return 0.
 */
JKSint32 JkWmaNumberOfSegmentsByUrl( JKUint8* url,JKSint32 urlLength, JKT_Wma_Message* message );

/**
 *  Sends a message.
 *   @param connectionHandle
 *     The handle of the connection for sending the message.
 *     The handle issued by #JkWmaOpen() is designated.
 *   @param message
 *     A pointer to the #JKT_Wma_Message structure containing information about
 *     the send message. 
 *     This pointer is valid until return from this function.
 *     The pointers in the structure members url and binaryData or textData 
 *     remain valid until this function fails or until the function succeeds 
 *     and the send result is notified to JBlend by #AMWmaEventPost().
 *   @return
 *     If the operation succeeds, return #JK_WMA_OK.<br>
 *     If an error occurred, return one of the error codes below.
 *     <dl>
 *      <dt>#JK_WMA_ERROR_NOT_PERMITTED</dt>
 *       <dd>Sending is not permitted on the connection.</dd>
 *      <dt>#JK_WMA_ERROR_IO_ERROR</dt>
 *       <dd>An I/O error occurred.</dd>
 *      <dt>#JK_WMA_ERROR_PAYLOAD_OVER</dt>
 *       <dd>Payload exceeded the maximum size.</dd>
 *     </dl>
 *
 * This function simply starts message send processing; use #AMWmaEventPost() to 
 * notify JBlend of the send result.
 *
 */
JKSint32 JkWmaSendMessage( JKHandle connectionHandle, JKT_Wma_Message* message );

/**
 *  Gets information about the first message in the receive queue.
 *   @param connectionHandle
 *     The handle of the connection for which information is to be obtained.
 *     The handle issued by #JkWmaOpen() is designated.
 *   @param message
 *     A pointer to the #JKT_Wma_Message structure where the information goes.
 *     Set the structure members below.
 *     <ul>
 *      <li><b>type</b> (message type)
 *      <li><b>urlLength</b> (length of URL)
 *      <li>If the message type is binary:<br>
 *            <b>binaryDataLength</b> (size (octets) of the message payload data)<br>
 *           If the message type is text: <br>
 *            <b>textDataLength</b> (size (number of characters) of the message
 *               payload data)
 *     </ul>
 *   @return
 *     If the operation succeeds, return #JK_WMA_OK.<br>
 *     If an error occurred, return one of the error codes below.
 *     <dl>
 *      <dt>#JK_WMA_ERROR_NOT_PERMITTED</dt>
 *       <dd>Receipt is not permitted on the connection.</dd>
 *      <dt>#JK_WMA_ERROR_NO_DATA_RECEIVED</dt>
 *       <dd>No messsage in the connection receive queue.</dd>
 *     </dl>
 *
 *  Do not allow an I/O wait to occur for this function.
 * @see JkWmaReceiveMessage()
 */
JKSint32 JkWmaGetReceivedMessageInfo( JKHandle connectionHandle, JKT_Wma_Message* message );

/**
 *  Fetches the first message in the message queue.
 *   @param connectionHandle
 *     The handle of the connection for receiving the message.
 *     The handle issued by #JkWmaOpen() is designated.
 *   @param message
 *     A pointer to the #JKT_Wma_Message where information about the receive
 *     message goes.
 *     <ul>
 *      <li>Put the receive message URL in the buffer indicated by the structure
 *           member url.
 *      <li>If the message type is binary, put the receive message in the buffer
 *          indicated by the structure member binaryData.
 *      <li>If the message type is text, put the receive message in the buffer
 *          indicated by the structure member textData.
 *      <li>Put information about the received message send time in the structure
 *          members isTimeStampAvailable, timeStampHigh and timeStampLow.
 *     </ul>
 *     Allocation of the buffers indicated by the structure members url and 
 *     binaryData or textData is handled by JBlend.
 *   @return
 *     If the operation succeeds, return #JK_WMA_OK.<br>
 *     If an error occurred, return one of the error codes below.
 *     <dl>
 *      <dt>#JK_WMA_ERROR_NOT_PERMITTED</dt>
 *       <dd>Receipt is not permitted on the connection.</dd>
 *      <dt>#JK_WMA_ERROR_NO_DATA_RECEIVED</dt>
 *       <dd>No messsage in the connection receive queue.</dd>
 *     </dl>
 *
 *  Take the first message from the receive queue, put information about the message
 *  in the members of the #JKT_Wma_Message structure pointed to by the message
 *  parameter, and put the message content in the buffers indicated by the structure
 *  members.
 *
 *  #JkWmaGetReceivedMessageInfo() is called prior to this function.
 *  The following members of the #JKT_Wma_Message structure indicated by 
 *  the <i>message</i> parameter hold the same values passed by 
 *  #JkWmaGetReceivedMessageInfo().
 *  These members must not be changed by the operation in JkWmaReceiveMessage().
 *  <ul>
 *    <li><i>type</i> The message type.
 *    <li><i>urlLength</i> The length of the buffer for putting the URL string.
 *    <li>The length of the buffer for putting the message.
 *      <ul>
 *        <li><i>binaryDataLength</i> This member is set when message is a binary message.
 *        <li><i>textDataLength</i> This member is set when message is a text message.
 *      </ul>
 *  </ul>
 *  Do not allow an I/O wait to occur for this function.
 * @see JkWmaGetReceivedMessageInfo()
 */
JKSint32 JkWmaReceiveMessage( JKHandle connectionHandle, JKT_Wma_Message* message );

/**
 *  Checks if receiving is permitted.
 *   @param connectionHandle
 *     The handle of the connection for receiving the message.
 *     The handle issued by #JkWmaOpen() is designated.
 *   @return
 *     If receiving is permitted, return JK_TRUE.<br>
 *     If receiving is not permitted, return JK_FALSE.
 *
 *  Do not allow an I/O wait to occur for this function.
 */
JKBool JkWmaIsPermittedToReceive( JKHandle connectionHandle );


#ifdef __cplusplus
}
#endif




#endif /* !__JKWIRELESSMESSAGING_H__ */

/** @} end of group */

