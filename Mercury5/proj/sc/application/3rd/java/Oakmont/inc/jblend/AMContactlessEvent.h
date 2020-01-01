/*
 * Copyright 2007 Aplix Corporation. All rights reserved.
 */
/**
 * @file AMContactlessEvent.h
 * Contactless Communication JBI
 */

#ifndef ___AMCONTACTLESSEVENT_H___
#define ___AMCONTACTLESSEVENT_H___

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"


/**
 * @addtogroup Contactless_Discovery_JSI
 * @{
 */
/**
 * @name Event Type
 * @{
 */

/**
 * Event type: An NDEF record detected.
 * When an NDEF record listener registered via JkContactlessAddNDEFRecordListener() detects an NDEF record in a contactless target,
 * call AmmNotifyContactlessEvent() passing this event type in the <i>eventType</i> parameter.
 * The other parameters to AmmNotifyContactlessEvent() should be specified as follows:
 * @param  param1
 *         A pointer to a #JKT_Contactless_Data structure containing the NDEF message of the record.
 *         The structure indicated by the pointer must remain valid until JkContactlessReleaseData() is called.
 * @param  param2
 *         #JK_NULL
 *
 * When this event is received by JBlend in the JVM task, the <code>NDEFRecordListener\#recordDetected</code> method 
 * is called with the NDEF message indicated by <i>param1</i>.
 *
 * This event is not accepted by JBlend during JVM suspension period. That is, AmmNotifyContactlessEvent() fails.
 * When a JVM suspension event is received, the listener processing should be paused.
 * Then when a JVM resumption event is received, the listener processing should restart and issue events based only on the situation of that time.
 * You need not notify JBlend of events that occurred while the JVM is suspended. 
 */
#define JK_CONTACTLESS_EVENT_NDEF_RECORD_DETECTED       0x0101
/**
 * Event type: Contactless target(s) detected.
 * When a target listener registered via JkContactlessAddTargetListener() detects contactless targets in proximity of the device, 
 * call AmmNotifyContactlessEvent() passing this event type in the <i>eventType</i> parameter.
 * The other parameters to AmmNotifyContactlessEvent() should be specified as follows:
 * @param  param1
 *         The number of the found targets.
 * @param  param2
 *         A pointer to an array of #JKT_Contactless_TargetProperties containing the properties of all the found targets.
 *         The number of the array elements must be equal to the <i>param1</i> parameter.
 *         The array indicated by the pointer must remain valid until JkContactlessReleaseTargetProperties() is called.
 *
 * When this event is received by JBlend in the JVM task, the <code>TargetListener\#targetDetected</code> method 
 * is called with the target properties indicated by <i>param1</i> and <i>param2</i>.
 *
 * This event is not accepted by JBlend during JVM suspension period. That is, AmmNotifyContactlessEvent() fails.
 * When a JVM suspension event is received, the listener processing should be paused.
 * Then when a JVM resumption event is received, the listener processing should restart and issue events based only on the situation of that time.
 * You need not notify JBlend of events that occurred while the JVM is suspended. 
 */
#define JK_CONTACTLESS_EVENT_TARGET_DETECTED            0x0102
/**
 * Event type: A transaction with an external reader detected.
 * When a listener registered via JkContactlessAddTransactionListener() detects a transaction 
 * happening between the secure element on the device and an external reader device,
 * call AmmNotifyContactlessEvent() passing this event type in the <i>eventType</i> parameter.
 * The other parameters to AmmNotifyContactlessEvent() should be specified as follows:
 * @param  param1
 *         The slot number to open an APDUConnection (defined in JSR-177) to the secure element on the device.
 *         Can be -1, if the slot number cannot be identified.
 * @param  param2
 *         #JK_NULL
 *
 * When this event is received by JBlend in the JVM task, the <code>TransactionListener\#externalReaderDetected</code> method 
 * is called with the slot number indicated by <i>param1</i>.
 *
 * This event is not accepted by JBlend during JVM suspension period. That is, AmmNotifyContactlessEvent() fails.
 * When a JVM suspension event is received, the listener processing should be paused.
 * Then when a JVM resumption event is received, the listener processing should restart and issue events based only on the situation of that time.
 * You need not notify JBlend of events that occurred while the JVM is suspended. 
 */
#define JK_CONTACTLESS_EVENT_EXTERNAL_READER_DETECTED   0x0103

/** @} */
/** @} */
/**
 * @addtogroup Contactless_Access_JSI
 * @{
 */

/**
 * @name Event Type
 * @{
 */
/**
 * Event type: An operation requested to JkContactlessOpenConnection() has ended.
 * When an operation requested to JkContactlessOpenConnection() has ended, 
 * call AmmNotifyContactlessEvent() passing this event type in the <i>eventType</i> parameter.
 * The other parameters to AmmNotifyContactlessEvent() should be specified as follows:
 * @param  param1
 *         The handle returned from JkContactlessOpenConnection().
 * @param  param2
 *         One of the following values must be passed representing the result of the operation:
 *         - #JK_CONTACTLESS_OK
 *         - #JK_CONTACTLESS_ERROR_NOT_SUPPORTED
 *         - #JK_CONTACTLESS_ERROR_POWER_OFF
 *         - #JK_CONTACTLESS_ERROR_OTHER
 *         .
 * <p>
 * if a value other than #JK_CONTACTLESS_OK is passed in <i>param2</i>, 
 * the <code>Connector.open</code> method throws an <code>IOException</code>. 
 *
 * This event is accepted by JBlend even during JVM suspension period.
 */
#define JK_CONTACTLESS_EVENT_CONNECTION_OPEN            0x0201
/**
 * Event type: An operation requested to JkContactlessNDEFReadMessage() has ended.
 * When an operation requested to JkContactlessNDEFReadMessage() has ended, 
 * call AmmNotifyContactlessEvent() passing this event type in the <i>eventType</i> parameter.
 * The other parameters to AmmNotifyContactlessEvent() should be specified as follows:
 * @param  param1
 *         Pass the <i>hConnection</i> parameter passed to JkContactlessNDEFReadMessage() here.
 * @param  param2
 *         If the operation has succeeded, pass a pointer to a #JKT_Contactless_Data structure
 *         containing the NDEF Message read from the tag.  
 *         If the operation has failed, pass #JK_NULL.
 *         When a valid pointer is passed here, the structure indicated by the pointer must remain valid until JkContactlessReleaseData() is called.
 *
 * When #JK_NULL is passed in <i>param2</i>, the <code> NDEFTagConnection\#readNDEF</code> method returns <code>null</code>.
 *
 * This event is accepted by JBlend even during JVM suspension period.
 */
#define JK_CONTACTLESS_EVENT_NDEF_MESSAGE_READ          0x0301
/**
 * Event type: An operation requested to JkContactlessNDEFWriteMessage() has ended.
 * When an operation requested to JkContactlessNDEFWriteMessage() has ended, 
 * call AmmNotifyContactlessEvent() passing this event type in the <i>eventType</i> parameter.
 * The other parameters to AmmNotifyContactlessEvent() should be specified as follows:
 * @param  param1
 *         Pass the <i>hConnection</i> parameter passed to JkContactlessNDEFWriteMessage() here.
 * @param  param2
 *         One of the following values must be passed representing the result of the operation:
 *         - #JK_CONTACTLESS_OK
 *         - #JK_CONTACTLESS_ERROR_POWER_OFF<br>
 *           When this value is passed, the <code>NDEFTagConnection.writeNDEF</code> method throws an <code>IOException</code>.
 *         - #JK_CONTACTLESS_ERROR_OUT_OF_CAPACITY<br>
 *           When this value is passed, the <code>NDEFTagConnection.writeNDEF</code> method throws an <code>IOException</code>.
 *         - #JK_CONTACTLESS_ERROR_OTHER<br>
 *           When this value is passed, the <code>NDEFTagConnection.writeNDEF</code> method throws an <code>IOException</code>.
 *         .
 * <p>
 * This event is accepted by JBlend even during JVM suspension period. 
 */
#define JK_CONTACTLESS_EVENT_NDEF_MESSAGE_WRITE         0x0302
/**
 * Event type: An operation requested to JkContactlessISO14443ExchangeData() has ended.
 * When an operation requested to JkContactlessISO14443ExchangeData() has ended, 
 * call AmmNotifyContactlessEvent() passing this event type in the <i>eventType</i> parameter.
 * The other parameters to AmmNotifyContactlessEvent() should be specified as follows:
 * @param  param1
 *         Pass the <i>hConnection</i> parameter passed to JkContactlessISO14443ExchangeData() here.
 * @param  param2
 *         If the operation has succeeded, pass a pointer to a #JKT_Contactless_Data structure
 *         containing the data received from the hardware.
 *         If the operation has failed, pass #JK_NULL.
 *         When a valid pointer is passed here, the structure indicated by the pointer must remain valid until JkContactlessReleaseData() is called.
 *
 * When #JK_NULL is passed in <i>param2</i>, the <code>ISO14443Connection\#exchangeData</code> method returns <code>null</code>.
 *
 * This event is accepted by JBlend even during JVM suspension period. 
 */
#define JK_CONTACTLESS_EVENT_ISO14443_DATA_EXCHANGE     0x0303
/**
 * Event type: An operation requested to JkContactlessRFIDTransceive() has ended.
 *
 * @todo This event is not supported yet as per December 17th, 2007.
 *
 * When an operation requested to JkContactlessRFIDTransceive() has ended, 
 * call AmmNotifyContactlessEvent() passing this event type in the <i>eventType</i> parameter.
 * The other parameters to AmmNotifyContactlessEvent() should be specified as follows:
 * @param  param1
 *         Pass the <i>hConnection</i> parameter passed to JkContactlessRFIDTransceive() here.
 * @param  param2
 *         If the operation has succeeded, pass the address of an array of pointers to 
 *         #JKT_Contactless_Data structures which contain the received responses.
 *         The array elements must be terminated by #JK_NULL.
 *         If the operation has failed, pass #JK_NULL.
 *         When a valid address is passed here, the array indicated by the address must remain valid until JkContactlessReleaseData() is called.
 *
 * When #JK_NULL is passed in <i>param2</i>, the <code>PlainTagConnection\#transceive</code> method returns <code>null</code>.
 *
 * This event is accepted by JBlend even during JVM suspension period. 
 */
#define JK_CONTACTLESS_EVENT_RFID_TRANSCEIVE            0x0304

/** @} */
/** @} */



/**
 * @addtogroup Contactless_Event_JBI
 * @{
 */

/**
 * Notifies JBlend of a contactless communication event.
 * @param  eventType
 *         The event type. Pass one of the following.
 *          - #JK_CONTACTLESS_EVENT_NDEF_RECORD_DETECTED
 *          - #JK_CONTACTLESS_EVENT_TARGET_DETECTED
 *          - #JK_CONTACTLESS_EVENT_EXTERNAL_READER_DETECTED
 *          - #JK_CONTACTLESS_EVENT_CONNECTION_OPEN
 *          - #JK_CONTACTLESS_EVENT_NDEF_MESSAGE_READ
 *          - #JK_CONTACTLESS_EVENT_NDEF_MESSAGE_WRITE
 *          - #JK_CONTACTLESS_EVENT_ISO14443_DATA_EXCHANGE
 *          - #JK_CONTACTLESS_EVENT_RFID_TRANSCEIVE
 * @param  param1
 *         Additional event information. The value differs depending on the event code.
 * @param  param2
 *         Additional event information. The value differs depending on the event code.
 * 
 * @retval #JK_CONTACTLESS_OK
 *         if the function succeeds.
 * @retval #JK_CONTACTLESS_ERROR_VM_SUSPENDED
 *         if the function fails because the JVM is currently suspended.
 * @retval #JK_CONTACTLESS_ERROR_OTHER
 *         if the function fails for any other reason.
 *
 * When this funciton returns #JK_CONTACTLESS_ERROR_VM_SUSPENDED, 
 * discard the event and disable the listener processing until a JVM event indicating JVM resumption is received. 
 * 
 * A return value of #JK_CONTACTLESS_ERROR_OTHER may mean that the JBlend event queue is full.
 * In such a case, retry notification after about 200 milliseconds. 
 * If notification fails again, this may indicate a serious problem with the JVM, 
 * and the native system should forcibly terminate the JVM. 
 */
JKSint32 AmNotifyContactlessEvent(JKSint32 eventType, JKSint32 param1, JKSint32 param2);


/** @} */

#ifdef __cplusplus
}
#endif

#endif /* not ___AMCONTACTLESSEVENT_H___ */

