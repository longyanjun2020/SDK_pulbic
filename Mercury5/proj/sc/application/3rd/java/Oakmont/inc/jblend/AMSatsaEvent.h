/**
 * Copyright 2005 Aplix Corporation. All rights reserved.
 *
 * $Id: AMSatsaEvent.h,v 1.8 2007/11/30 09:13:28 fuji Exp $
 */

/**
 * @file AMSatsaEvent.h
 *  SATSA JBI
 */
/**
 * @addtogroup SATSA_JBI
 * @{
 */

#ifndef ___AM_SATSA_EVENT_H
#define ___AM_SATSA_EVENT_H

#include "JkSatsaCommon.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Notifies JBlend of a SATSA encryption or decryption event. 
 *
 * @param h
 *        A cipher object handle value. Designate the handle 
 *        of the cipher object that raised the event. 
 * @param result
 *        The raised event.
 * @param param1
 *        A parameter giving additional information about the event. 
 * @param param2
 *        A parameter giving additional information about the event. 
 * @return 
 *   - #JK_TRUE : Event successfully queued. 
 *   - #JK_FALSE: Event queueing failed.
 *   .
 *
 * When the following JSI functions are implemented as asynchronous functions, 
 * use this JBI function to notify JBlend of the processing result. 
 * <ul>
 * <li>JkSatsaUpdateCipher()
 * <li>JkSatsaFinalCipher()
 * </ul>
 *
 * Failure of this function may mean memory could not be allocated by 
 * JBlend, or that the queue is full. In such cases, retry notification 
 * after about 200 milliseconds.
 * If notification fails again, this may indicate a problem with the JVM, 
 * and the native system should forcibly terminate the JVM.  
 * Terminate the JVM also if the above delayed execution cannot be 
 * implemented. 
 */

JKSint32 AmSatsaNotifyCipherEvent(JKSatsaCipherHandle h, JKSint32 result, JKSint32 param1, JKSint32 param2);

/**
 * Notifies JBlend of a SATSA message digest event. 
 *
 * @param h
 *        A message digest object handle value. Designate the handle 
 *        of the message digest object that raised the event. 
 * @param result
 *        The raised event.
 * @param param1
 *        A parameter giving additional information about the event. 
 * @param param2
 *        A parameter giving additional information about the event. 
 * @return 
 *   - #JK_TRUE : Event successfully queued. 
 *   - #JK_FALSE: Event queueing failed.
 *   .
 *
 * When the following JSI functions are implemented as asynchronous functions, 
 * use this JBI function to notify JBlend of the processing result. 
 * <ul>
 * <li>JkSatsaUpdateDigest()
 * <li>JkSatsaFinalDigest()
 * </ul>
 *
 * Failure of this function may mean memory could not be allocated by 
 * JBlend, or that the queue is full. In such cases, retry notification 
 * after about 200 milliseconds.
 * If notification fails again, this may indicate a problem with the JVM, 
 * and the native system should forcibly terminate the JVM.  
 * Terminate the JVM also if the above delayed execution cannot be 
 * implemented. 
 */

JKSint32 AmSatsaNotifyDigestEvent(JKSatsaDigestHandle h, JKSint32 result, JKSint32 param1, JKSint32 param2);

/**
 * Notifies JBlend of an event relating to verification with the SATSA digital signature algorithm. 
 *
 * @param h
 *        A digital signature algorithm object handle value. Designate the handle 
 *        of the digital signature algorithm object that raised the event. 
 * @param result
 *        The raised event.
 * @param param1
 *        A parameter giving additional information about the event. 
 * @param param2
 *        A parameter giving additional information about the event. 
 * @return 
 *   - #JK_TRUE : Event successfully queued. 
 *   - #JK_FALSE: Event queueing failed.
 *   .
 *
 * When the following JSI functions are implemented as asynchronous functions, 
 * use this JBI function to notify JBlend of the processing result. 
 * <ul>
 * <li>JkSatsaUpdateSignatureVerify()
 * <li>JkSatsaFinalSignatureVerify()
 * </ul>
 *
 * Failure of this function may mean memory could not be allocated by 
 * JBlend, or that the queue is full. In such cases, retry notification 
 * after about 200 milliseconds.
 * If notification fails again, this may indicate a problem with the JVM, 
 * and the native system should forcibly terminate the JVM.  
 * Terminate the JVM also if the above delayed execution cannot be 
 * implemented. 
 */

JKSint32 AmSatsaNotifySignatureEvent(JKSatsaSignatureHandle h, JKSint32 result, JKSint32 param1, JKSint32 param2);

/**
 * Notifies JBlend of a SATSA APDU communication event. 
 *
 * @param h
 *        The security element handle. Designate the handle of the SE 
 *        in which the event was raised.
 * @param result
 *        The raised event.
 * @param param1
 *        A parameter giving additional information about the event. 
 * @param param2
 *        A parameter giving additional information about the event. 
 * @return 
 *   - #JK_TRUE : Event successfully queued. 
 *   - #JK_FALSE: Event queueing failed.
 *   .
 *
 * When the following JSI functions are implemented as asynchronous functions, 
 * use this JBI function to notify JBlend of the processing result. 
 * <ul>
 * <li>JkSatsaGetATR()
 * <li>JkSatsaOpenSEConnection()
 * <li>JkSatsaConnectionClose()
 * <li>JkSatsaSendCommandData()
 * <li>JkSatsaReceiveResponseData()
 * <li>JkSatsaGetACFileSize()
 * <li>JkSatsaGetACFileData()
 * </ul>
 *
 * Failure of this function may mean memory could not be allocated by 
 * JBlend, or that the queue is full. In such cases, retry notification 
 * after about 200 milliseconds.
 * If notification fails again, this may indicate a problem with the JVM, 
 * and the native system should forcibly terminate the JVM.  
 * Terminate the JVM also if the above delayed execution cannot be 
 * implemented. 
 */
 
JKSint32 AmSatsaNotifyConnectionEvent(JKHandle h, JKSint32 result, JKSint32 param1, JKSint32 param2);

/**
 * Notifies JBlend of a PIN entry event. 
 *
 * @param h
 *        A PIN entry dialog handle value. Designate the handle
 *        of the entry dialog where the event was raised. 
 * @param result
 *        The raised event.
 * @param param1
 *        A parameter giving additional information about the event. 
 * @param param2
 *        A parameter giving additional information about the event. 
 * @return 
 *   - #JK_TRUE : Event successfully queued. 
 *   - #JK_FALSE: Event queueing failed.
 *   .
 *
 * Use this JBI function to notify the result of JkSatsaPinEntryDialog() 
 * processing.
 *
 * Failure of this function may mean memory could not be allocated by 
 * JBlend, or that the queue is full. In such cases, retry notification 
 * after about 200 milliseconds.
 * If notification fails again, this may indicate a problem with the JVM, 
 * and the native system should forcibly terminate the JVM.  
 * Terminate the JVM also if the above delayed execution cannot be 
 * implemented. 
 */
 
JKSint32 AmSatsaNotifyDialogEvent(JKHandle h, JKSint32 result, JKSint32 param1, JKSint32 param2);

/* obsolete API */
#define AmNotifyCipherEvent(h, result, param1, param2)      AmSatsaNotifyCipherEvent(h, result, param1, param2)
#define AmNotifyDigestEvent(h, result, param1, param2)      AmSatsaNotifyDigestEvent(h, result, param1, param2)
#define AmNotifySignatureEvent(h, result, param1, param2)   AmSatsaNotifySignatureEvent(h, result, param1, param2)
#define AmNotifyConnectionEvent(h, result, param1, param2)  AmSatsaNotifyConnectionEvent(h, result, param1, param2)
#define AmNotifyDialogEvent(h, result, param1, param2)      AmSatsaNotifyDialogEvent(h, result, param1, param2)

#ifdef __cplusplus
}
#endif

#endif /* ___AM_SATSA_EVENT_H */

/**
 * @} end of group
 */
