/*
 * Copyright 2007 Aplix Corporation. All rights reserved.
 */
/**
 * @file JkContactless.h
 * Contactless Communication JSI
 */

#ifndef ___JKCONTACTLESS_H___
#define ___JKCONTACTLESS_H___

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"
#include "JkTypesContactless.h"

/**
 * @addtogroup Contactless_Discovery_JSI
 * @{
 */

/**
 * NFC native resource initialize.
 * This function is called only once before Java application launched.
 */
void JkContactlessInitialize(void);


/**
 * NFC native resource finalize.
 * This function is called only once after Java application terminated.
 */
void JkContactlessFinalize(void);

/**
 * Gets all the supported target types of the platform.
 * @return
 *         Return a bitwise-OR of the following values representing the types of the targets supported by the platform.
 *         - #JK_CONTACTLESS_TARGET_NDEF_TAG
 *         - #JK_CONTACTLESS_TARGET_RFID_TAG
 *         - #JK_CONTACTLESS_TARGET_ISO14443_CARD
 *         .
 *         <!-- - #JK_CONTACTLESS_TARGET_VISUAL_TAG -->
 *         Return 0 in case of any error.
 *
 * This function is called only once when the first time a Java application calls the <code>DiscoveryManager.getInstance</code> method.
 */
JKSint32 JkContactlessGetSupportedTargetTypes(void);

/**
 * Sets a JSR-257 property related to target discovery.
 * @param  key
 *         A pointer to the UCS2-encoded character string representing the type of the property to be set.
 *         The value of the <code>name</code> parameter to <code>DiscoveryManager.setProperty</code> method is passed here.
 * @param  keyLength
 *         The number of the characters in the string indicated by <i>key</i>.
 * @param  property
 *         A pointer to the UCS2-encoded character string representing the property value to be set.
 *         The value of the <code>value</code> parameter to <code>DiscoveryManager\#setProperty</code> method is passed here.
 * @param  propertyLength
 *         The number of the characters in the string indicated by <i>property</i>.
 * @retval #JK_CONTACTLESS_OK
 *         if the function succeeds.
 * @retval #JK_CONTACTLESS_ERROR_OTHER
 *         if the function fails.
 *         When this value is returned, the <code>DiscoveryManager\#setProperty</code> method throws an <code>IllegalArgumentException</code>.
 *
 * As described in JSR-257, property specification is implementation-dependent.
 *
 * This function is called when a Java application calls the <code>DiscoveryManager.setProperty</code> method.
 */
JKSint32 JkContactlessSetProperty(const JKWChar *key, JKSint32 keyLength, const JKWChar *property, JKSint32 propertyLength);

/**
 * Retrieves a JSR-257 property related to target discovery.
 * @param  key
 *         A pointer to the UCS2-encoded character string representing the type of the property to be retrieved.
 *         The value of the <code>name</code> parameter to <code>DiscoveryManager.getProperty</code> method is passed here.
 * @param  keyLength
 *         The number of the characters in the string indicated by <i>key</i>.
 * @param  propertyLength
 *         A pointer to the buffer where this function stores the number of the characters in the string
 *         returned by this function.
 * @return
 *         Return a pointer to the buffer holding the property value string indicated by <i>key</i>.
 *         This value must remain valid until this function is called again or the JVM exits.
 *         In any of the following cases, return #JK_NULL.
 *         - The designated key does not exist.
 *         - No property is present for the designated key.
 *
 * As described in JSR-257, property specification is implementation-dependent.
 * Note that properties for JSR-257 should be maintained separately from the system properties,
 * which should be retrieved with the JSI function <b>JkPropertyGetString()</b>.
 * For details of <b>JkPropertyGetString()</b>, see @ref jsr118_001_jblend_micro_if_cldc_midp21_mj "[1]".
 *
 * This function is called when a Java application calls the <code>DiscoveryManager\#getProperty</code> method.
 * When this function returns #JK_NULL, the method returns <code>null</code>.
 */
const JKWChar* JkContactlessGetProperty(const JKWChar *key, JKSint32 keyLength, JKSint32 *propertyLength);

/**
 * Registers a target listener for a specific target type.
 * @param  targetType
 *         The type of the target listener to be registered.
 *         A type indicated by the return value of JkContactlessGetSupportedTargetTypes() is passed here.
 * @retval #JK_CONTACTLESS_OK
 *         if the function succeeds.
 * @retval #JK_CONTACTLESS_ERROR_NOT_SUPPORTED
 *         if the function fails because the native system does not support the requested listener feature.
 *         When this value is returned, the <code>DiscoveryManager\#addTargetListener</code> method throws a <code>ContactlessException</code>.
 * @retval #JK_CONTACTLESS_ERROR_POWER_OFF
 *         if the function fails because the requested target is currently powered off.
 *         When this value is returned, the <code>DiscoveryManager\#addTargetListener</code> method throws a <code>RuntimeException</code>.
 * @retval #JK_CONTACTLESS_ERROR_EXCEED_MAXIMUM_LISTENER
 *         if the function fails because the number of listeners exceeds the maximum limit of the device.
 *         When this value is returned, the <code>DiscoveryManager\#addTargetListener</code> method throws an <code>IllegalStateException</code>.
 * @retval #JK_CONTACTLESS_ERROR_OTHER
 *         if the function fails for any other reason.
 *         When this value is returned, the <code>DiscoveryManager\#addTargetListener</code> method throws a <code>RuntimeException</code>.
 *
 * Start an asynchronous discovery process of targets of the type indicated by <i>targetType</i>.
 * Each time a target of the requested type becomes available in the proximity of the device, call
 * AmmNotifyContactlessEvent() passing #JK_CONTACTLESS_EVENT_TARGET_DETECTED in the <i>eventType</i> parameter.
 *
 * The native system must continue the asynchronous processing until JkContactlessRemoveTargetListener() is called for the
 * requested type.
 *
 * If this function is called for a target type for which a listener has already been registered by this function,
 * fail the function and return #JK_CONTACTLESS_ERROR_EXCEED_MAXIMUM_LISTENER.
 *
 * For the case where both a target listener and an NDEF record listener are registered, 
 * the necessary listener processing for a detected #JK_CONTACTLESS_TARGET_NDEF_TAG target is specified in JSR-257.
 * The native system needs to follow that specification in this JSR layer.
 * See the flow diagram written for the <code>DiscoveryManager</code> class for details.
 *
 * This function is called when the <code>DiscoveryManager\#addTargetListener</code> method is called.
 *
 */
JKSint32 JkContactlessAddTargetListener(JKSint32 targetType);

/**
 * Unregisters the target listener for the specified target type.
 * @param  targetType
 *         The type of the target listener to be unregistered.
 *         The target type of a listener which has been registered via JkContactlessAddTargetListener() is passed here.
 *
 * Stop the asynchronous process of target discovery for the target type indicated by <i>targetType</i>.
 * When no process is running for the target type, return without performing any action.
 *
 * This function is called when the <code>DiscoveryManager\#removeTargetListener</code> method is called.
 */
void JkContactlessRemoveTargetListener(JKSint32 targetType);

/**
 * Registers an NDEF record listener for the specified record type.
 * @param  recordType
 *         A pointer to the structure representing the record type of the record listener to be registered.
 * @retval #JK_CONTACTLESS_OK
 *         if the function succeeds.
 * @retval #JK_CONTACTLESS_ERROR_NOT_SUPPORTED
 *         if the function fails because the device does not support this feature.
 *         When this value is returned, the <code>DiscoveryManager\#addNDEFRecordListener</code> method throws a <code>ContactlessException</code>.
 * @retval #JK_CONTACTLESS_ERROR_POWER_OFF
 *         if the function fails because the requested target is currently powered off.
 *         When this value is returned, the <code>DiscoveryManager\#addNDEFRecordListener</code> method throws a <code>RuntimeException</code>.
 * @retval #JK_CONTACTLESS_ERROR_EXCEED_MAXIMUM_LISTENER
 *         if the function fails because the number of listeners exceeds the maximum limit of the device.
 *         When this value is returned, the <code>DiscoveryManager\#addNDEFRecordListener</code> method throws an <code>IllegalStateException</code>.
 * @retval #JK_CONTACTLESS_ERROR_OTHER
 *         if the function fails for any other reason.
 *         When this value is returned, the <code>DiscoveryManager\#addNDEFRecordListener</code> method throws a <code>RuntimeException</code>.
 *
 * Start an asynchronous process of discovery of the NDEF record indicated by <i>recordType</i> in contactless targets.
 * Each time an NDEF record of the requested type is found in a contactless device, call
 * AmmNotifyContactlessEvent() passing #JK_CONTACTLESS_EVENT_NDEF_RECORD_DETECTED in the <i>eventType</i> parameter.
 *
 * The underlying NFC hardware may have technical limitations so that it can only monitor limited number of NDEF record types.
 * If the number of listeners exceeds the maximum limit of the device, this function should return #JK_CONTACTLESS_ERROR_EXCEED_MAXIMUM_LISTENER.
 * Note that the number of available listeners should include listeners requested by native applications.
 *
 * For the case where both a target listener and an NDEF record listener are registered, 
 * the necessary listener processing for a detected #JK_CONTACTLESS_TARGET_NDEF_TAG target is specified in JSR-257.
 * The native system needs to follow that specification in this JSR layer.
 * See the flow diagram written for the <code>DiscoveryManager</code> class for details.
 *
 * This function is called when the <code>DiscoveryManager\#addNDEFRecordListener</code> method is called.
 */
JKSint32 JkContactlessAddNDEFRecordListener(JKT_Contactless_NDEFRecordType *recordType);

/**
 * Unregisters the NDEF record listener for the specified record type.
 * @param  recordType
 *         A pointer to the structure representing the record type of the record listener to be unregistered.
 *
 * Stop the asynchronous process of NDEF record discovery for the record type indicated by <i>recordType</i>.
 * When no process is running for the record type, return without performing any action.
 *
 * This function is called when the <code>DiscoveryManager\#removeNDEFRecordListener</code> method is called.
 */
void JkContactlessRemoveNDEFRecordListener(JKT_Contactless_NDEFRecordType *recordType);

/**
 *         Registers a transaction listener.
 * @retval #JK_CONTACTLESS_OK
 *         if the function succeeds.
 * @retval #JK_CONTACTLESS_ERROR_NOT_SUPPORTED
 *         if the function fails because the target #JK_CONTACTLESS_TARGET_ISO14443_CARD is not supported
 *         or the device does not support this feature.
 *         When this value is returned, the <code>DiscoveryManager\#addTransactionListener</code> method throws a <code>ContactlessException</code>.
 * @retval #JK_CONTACTLESS_ERROR_POWER_OFF
 *         if the function fails because the requested target is currently powered off.
 *         When this value is returned, the <code>DiscoveryManager\#addTransactionListener</code> method throws a <code>RuntimeException</code>.
 * @retval #JK_CONTACTLESS_ERROR_OTHER
 *         if the function fails for any other reason.
 *         When this value is returned, the <code>DiscoveryManager\#addTransactionListener</code> method throws a <code>RuntimeException</code>.
 *
 * Start an asynchronous process of monitoring transactions happening between the secure element on the device and an
 * external reader device through the RFID hardware.
 * When such a transaction is detected, call
 * AmmNotifyContactlessEvent() passing #JK_CONTACTLESS_EVENT_EXTERNAL_READER_DETECTED in the <i>eventType</i> parameter.
 *
 * This function is called when the <code>DiscoveryManager\#addTransactionListener</code> method is called.
 */
JKSint32 JkContactlessAddTransactionListener(void);

/**
 * Unregisters the current transaction listener.
 *
 * Stop the current asynchronous process started by JkContactlessAddTransactionListener().
 * When no process has been started, return without performing any action.
 */
void JkContactlessRemoveTransactionListener(void);

/** @} */
/**
 * @addtogroup Contactless_Access_JSI
 * @{
 */

/**
 * Reads an NDEF message from an established NDEF connection.
 * @param  hConnection
 *         The connection handle of the NDEF connection.
 *         The value returned by JkContactlessOpenConnection() for an NDEF connection is passed here.
 * @retval #JK_CONTACTLESS_OK
 *         if the request is accepted and an asynchronous processing for it has started.
 * @retval #JK_CONTACTLESS_ERROR_NOT_SUPPORTED
 *         if the function fails because the requested operation is not supported by the native system.
 *         When this value is returned, the <code>NDEFTagConnection\#readNDEF</code> method throws a <code>ContactlessException</code>.
 * @retval #JK_CONTACTLESS_ERROR_OTHER
 *         if the operation fails.
 *         When this value is returned, the <code>NDEFTagConnection\#readNDEF</code> method throws an <code>IOException</code>.
 *
 * This function is called when a Java application calls the <code>NDEFTagConnection\#readNDEF</code> method.
 *
 * If this function returns #JK_CONTACTLESS_OK,
 * the actual read operation should be performed asynchronously in a separate native system task to
 * avoid JBlend from blocking. When the read operation has ended,
 * call AmmNotifyContactlessEvent() passing a #JK_CONTACTLESS_EVENT_NDEF_MESSAGE_READ event
 * to notify JBlend of the processing result.
 *
 * JkContactlessCloseConnection() can be called for the connection for which an asynchronous processing started by this function is in progress.
 * In such a case, the native system must abort the processing and call AmmNotifyContactlessEvent()
 * passing a #JK_CONTACTLESS_EVENT_NDEF_MESSAGE_READ event with #JK_NULL in the <i>param2</i> parameter.
 *
 * This function is never called for a connection for which an asynchronous processing already started by this function is still in progress.
 * But it can be called even while an asynchronous processing started by this function for another connection is still in progress.
 */
JKSint32 JkContactlessNDEFReadMessage(JKContactlessConnectionHandle hConnection);

/**
 * Writes an NDEF message to an established NDEF connection.
 * @param  hConnection
 *         The connection handle of the NDEF connection.
 *         The value returned by JkContactlessOpenConnection() for an NDEF connection is passed here.
 * @param  data
 *         A pointer to the buffer holding an NFC Forum-formatted data of the NDEF message.
 * @param  dataLength
 *         The length in bytes of the data indicated by <i>data</i>.
 * @retval #JK_CONTACTLESS_OK
 *         if the request is accepted and an asynchronous processing for it has started.
 * @retval #JK_CONTACTLESS_ERROR_NOT_SUPPORTED
 *         if the function fails because the requested operation is not supported by the native system.
 *         When this value is returned, the <code>NDEFTagConnection\#writeNDEF</code> method throws a <code>ContactlessException</code>.
 * @retval #JK_CONTACTLESS_ERROR_OTHER
 *         if the function fails for any reason.
 *         When this value is returned, the <code>NDEFTagConnection\#writeNDEF</code> method throws an <code>IOException</code>.
 *
 * This function is called when a Java application calls the <code>NDEFTagConnection\#writeNDEF</code> method.
 *
 * If this function returns #JK_CONTACTLESS_OK,
 * the actual write operation should be performed asynchronously in a separate native system task to
 * avoid JBlend from blocking. When the operation has ended,
 * call AmmNotifyContactlessEvent() passing a #JK_CONTACTLESS_EVENT_NDEF_MESSAGE_WRITE event
 * to notify JBlend of the processing result.
 *
 * JkContactlessCloseConnection() can be called for the connection for which an asynchronous processing started by this function is in progress.
 * In such a case, the native system must abort the processing and call AmmNotifyContactlessEvent()
 * passing a #JK_CONTACTLESS_EVENT_NDEF_MESSAGE_WRITE event with #JK_CONTACTLESS_ERROR_OTHER in the <i>param2</i> parameter.
 *
 * This function is never called for a connection for which an asynchronous processing already started by this function is still in progress.
 * But it can be called even while an asynchronous processing started by this function for another connection is still in progress.
 */
JKSint32 JkContactlessNDEFWriteMessage(JKContactlessConnectionHandle hConnection, JKUint8 *data, JKSint32 dataLength);

/**
 * Exchanges APDU commands with an external smart card using ISO14443-4 communication.
 * @param  hConnection
 *         The connection handle of an ISO-14443 card connection.
 *         The value returned by JkContactlessOpenConnection() for an ISO-14443 card connection is passed here.
 * @param  data
 *         A pointer to the buffer containing the APDU commands to be exchanged with an external smart card.
 *         The APDU commands are defined in ISO7816-4 specification.
 * @param  dataLength
 *         The length in bytes of the APDU commands indicated by <i>data</i>.
 * @retval #JK_CONTACTLESS_OK
 *         if the request is accepted and an asynchronous processing for it has started.
 * @retval #JK_CONTACTLESS_ERROR_NOT_SUPPORTED
 *         if the function fails because the requested operation is not supported by the native system.
 *         When this value is returned, the <code>ISO14443Connection\#exchangeData</code> method throws a <code>ContactlessException</code>.
 * @retval #JK_CONTACTLESS_ERROR_OTHER
 *         if the function fails for any other reason.
 *         When this value is returned, the <code>ISO14443Connection\#exchangeData</code> method throws an <code>IOException</code>.
 *
 * This function is called when a Java application calls the <code>ISO14443Connection\#exchangeData</code> method.
 *
 * If this function returns #JK_CONTACTLESS_OK,
 * the actual exchange operation should be performed asynchronously in a separate native system task to
 * avoid JBlend from blocking. When the operation has ended,
 * call AmmNotifyContactlessEvent() passing a #JK_CONTACTLESS_EVENT_ISO14443_DATA_EXCHANGE event
 * to notify JBlend of the processing result.
 *
 * JkContactlessCloseConnection() can be called for the connection for which an asynchronous processing started by this function is in progress.
 * In such a case, the native system must abort the processing and call AmmNotifyContactlessEvent()
 * passing a #JK_CONTACTLESS_EVENT_ISO14443_DATA_EXCHANGE event with #JK_NULL in the <i>param2</i> parameter.
 *
 * This function is never called for a connection for which an asynchronous processing already started by this function is still in progress.
 * But it can be called even while an asynchronous processing started by this function for another connection is still in progress.
 */
JKSint32 JkContactlessISO14443ExchangeData(JKContactlessConnectionHandle hConnection, JKUint8 *data, JKSint32 dataLength);

/**
 * Transceives data to and from a discovered RFID tag.
 * @param  hConnection
 *         The connection handle of an RFID tag connection.
 *         The value returned by JkContactlessOpenConnection() for an RFID tag connection is passed here.
 * @param  data
 *         A pointer to an array of byte sequences, which represents a command to be performed.
 * @param  dataLength
 *         The lengths of the command indicated by <i>data</i>.
 * @retval #JK_CONTACTLESS_OK
 *         if the request is accepted and an asynchronous processing for it has started.
 * @retval #JK_CONTACTLESS_ERROR_NOT_SUPPORTED
 *         if the function fails because the requested operation is not supported by the native system.
 *         When this value is returned, the <code>PlainTagConnection\#transceive</code> method throws a <code>ContactlessException</code>.
 * @retval #JK_CONTACTLESS_ERROR_OTHER
 *         if the function fails for any reason.
 *         When this value is returned, the <code>PlainTagConnection\#transceive</code> method throws an <code>IOException</code>.
 *
 * @todo This function is not supported yet as per December 17th, 2007.
 *
 * This function is called when a Java application calls the <code>PlainTagConnection\#transceive</code> method.
 *
 * If this function returns #JK_CONTACTLESS_OK,
 * the actual transceive operation should be performed asynchronously in a separate native system task to
 * avoid JBlend from blocking. When the operation has ended,
 * call AmmNotifyContactlessEvent() passing a #JK_CONTACTLESS_EVENT_RFID_TRANSCEIVE event
 * to notify JBlend of the processing result.
 *
 * JkContactlessCloseConnection() can be called for the connection for which an asynchronous processing started by this function is in progress.
 * In such a case, the native system must abort the processing and call AmmNotifyContactlessEvent()
 * passing a #JK_CONTACTLESS_EVENT_RFID_TRANSCEIVE event with #JK_NULL in the <i>param2</i> parameter.
 *
 * This function is never called for a connection for which an asynchronous processing already started by this function is still in progress.
 * But it can be called even while an asynchronous processing started by this function for another connection is still in progress.
 */
JKSint32 JkContactlessRFIDTransceive(JKContactlessConnectionHandle hConnection, JKUint8 *data, JKSint32 dataLength);

/** @} */


/** @} */
/**
 * @addtogroup Contactless_Access_JSI
 * @{
 */

/**
 * Opens a connection to a native hardware using the specified URL.
 * @param  type
 *         The type of the target for which a connection is to be opened.
 *         One of the following values is passed.
 *         - #JK_CONTACTLESS_TARGET_NDEF_TAG
 *         - #JK_CONTACTLESS_TARGET_RFID_TAG
 *         - #JK_CONTACTLESS_TARGET_ISO14443_CARD
 *         .
 *         <!-- - #JK_CONTACTLESS_TARGET_VISUAL_TAG -->
 * @param  url
 *         A pointer to an UTF-8 encoded character string representing the URL to access the target.
 *         This string is not terminated by NUL.
 *         This string remains valid until the #JK_CONTACTLESS_EVENT_CONNECTION_OPEN event is passed
 *         via AmmNotifyContactlessEvent() notifying JBlend of the processing result.
 * @param  urlLength
 *         The length in bytes of the string indicated by <i>url</i>.
 * @return
 *         Return a value other than #JK_INVALID_HANDLE representing the handle of the connection,
 *         if the request is accepted and an asynchronous processing for it has started.
 *         This value must be passed as the <i>param1</i> parameter of the #JK_CONTACTLESS_EVENT_CONNECTION_OPEN event.
 *         If the function fails, return #JK_INVALID_HANDLE.
 *
 * This function is called when a Java application requests that one of the following connections
 * be opened via Generic Connection Framework (i.e., <code>Connector.open</code>):
 * <!-- - <code>VisualTagConnection</code>, -->
 * - <code>ISO14443Connection</code>
 * - <code>PlainTagConnection</code>
 * - <code>NDEFTagConnection</code>
 * - <code>NFCIPConnection</code> (if <code>com.nokia.nfc.p2p</code> is supported)
 * .
 *
 * If this function returns a valid handle value,
 * the operation should be performed asynchronously in a separate native system task to
 * avoid JBlend from blocking. Once the connection is successfully established,
 * call AmmNotifyContactlessEvent() passing #JK_CONTACTLESS_EVENT_CONNECTION_OPEN in the <i>eventType</i>
 * parameter and the connection handle value in the <i>param1</i> parameter.
 *
 * The handle value returned by this function must be unique among all the supported target types.
 *
 * If this function returns #JK_INVALID_HANDLE, the native system need not call AmmNotifyContactlessEvent().
 *
 * If this function returns #JK_INVALID_HANDLE, the <code>Connector.open</code> method throws an <code>IOException</code>.
 *
 * In no case is JkContactlessCloseConnection() called during the period the asynchronous processing is in progress.
 */
JKContactlessConnectionHandle JkContactlessOpenConnection(JKSint32 type, JKUint8 *url, JKSint32 urlLength);

/**
 * Closes an established connection to a native hardware.
 * @param  hConnection
 *         The connection handle.
 *         The value returned by JkContactlessOpenConnection() is passed here.
 * @retval #JK_CONTACTLESS_OK
 *         if the function succeeds.
 * @retval #JK_CONTACTLESS_ERROR_OTHER
 *         if the function fails.
 *
 * When this function is called, free all the resources associated to the connection indicated by <i>hConnection</i>.
 *
 * This function can be called even while an asynchronous processing started by the following functions is in progress.
 * - JkContactlessNDEFReadMessage()
 * - JkContactlessNDEFWriteMessage()
 * - JkContactlessISO14443ExchangeData()
 * - JkContactlessRFIDTransceive()
 * .
 * In such a case, the on-going asynchronous processing must be aborted
 * but its result still must be passed to JBlend via AmmNotifyContactlessEvent().
 */
JKSint32 JkContactlessCloseConnection(JKContactlessConnectionHandle hConnection);

/** @} */
/**
 * @addtogroup Contactless_Event_JSI
 * @{
 */

/**
 * Releases a received data.
 * @param data
 *        A pointer to the memory area containing the received data that was passed to JBlend via AmmNotifyContactlessEvent().
 *        The value of the <i>param2</i> parameter of an event of the following
 *        - #JK_CONTACTLESS_EVENT_NDEF_MESSAGE_READ
 *        - #JK_CONTACTLESS_EVENT_ISO14443_DATA_EXCHANGE
 *        - #JK_CONTACTLESS_EVENT_RFID_TRANSCEIVE
 *        .
 *        or the value of <i>param1</i> parameter of a #JK_CONTACTLESS_EVENT_NDEF_RECORD_DETECTED event is passed here.
 *
 * JBlend calls this function from the JVM task when the received data information becomes unnecessary.
 * Release the memory area pointed to by the <i>data</i> parameter.
 */
void JkContactlessReleaseData(JKT_Contactless_Data *data);

/**
 * Releases an array of target properties.
 * @param arraySize
 *        The number of the elements of the array pointed to by the <i>targetProperties</i> parameter.
 *        The value of the <i>param1</i> parameter of a #JK_CONTACTLESS_EVENT_TARGET_DETECTED event is passed here.
 * @param targetProperties
 *        A pointer to the memory area containing an array of JKT_Contactless_TargetProperties structures that
 *        was passed to JBlend via AmmNotifyContactlessEvent().
 *        The value of the <i>param2</i> parameter of a #JK_CONTACTLESS_EVENT_TARGET_DETECTED event is passed here.
 *
 * JBlend calls this function from the JVM task when the target properties information becomes unnecessary.
 * Release the memory area pointed to by the <i>targetProperties</i> parameter.
 */
void JkContactlessReleaseTargetProperties(JKSint32 arraySize, JKT_Contactless_TargetProperties targetProperties[]);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* not ___JKCONTACTLESS_H___ */

