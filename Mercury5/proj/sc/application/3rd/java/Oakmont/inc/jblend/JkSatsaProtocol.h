/*
 * Copyright 2005 Aplix Corporation. All rights reserved.
 */

/*----------JkSatsaConnection.c-------------*/ 
/**
 * @file JkSatsaProtocol.h
 *  APDU Communication JSI
 */
/**
 * @addtogroup APDU_Connection_JSI
 * @{
 */

#include "JkTypes.h"
#include "JKSatsaCommon.h"

#ifndef ___JK_SATSA_PROTOCOL_H
#define ___JK_SATSA_PROTOCOL_H

/*static global data for the single connection*/ 
#ifdef __cplusplus
extern "C" {
#endif


/**
 * Gets an ATR message.
 *
 * @param connectionHandle
 *        A handle value identifying the SE.
 *        The value passed to JBlend by JkSatsaOpenSEConnection().
 * @param atr
 *        A pointer to the memory area for putting the ATR message.
 *        JBlend allocates a memory space of 255 bytes. 
 *        When #JK_SATSA_ASYNC is returned, this pointer remains valid until 
 *        the native system calls #AmSatsaNotifyConnectionEvent() to notify JBlend 
 *        of the processing result.
 * @param len
 *        A pointer to a memory space for putting the length (number of 
 *        characters) of the ATR message stored in memory space <i>atr</i>.
 *        This is not used when this function returns #JK_SATSA_ASYNC.
 * @return
 *   - #JK_SATSA_SUCCESS<br>
 *     Processing was completed normally.
 *   - #JK_SATSA_ASYNC<br>
 *     The operation will be processed asynchronously. 
 *   - #JK_SATSA_ERROR_GENERAL<br>
 *     The function failed for any reason.
 *   .
 *
 * After calling JkSatsaOpenSEConnection(), JBlend invokes this function 
 * to get an ATR message.
 * In the native system, reset the SE as necessary, and put an ATR message in
 * the memory space indicated by <i>atr</i>. JBlend passes along the ATR message
 * directly to the Java application as the return value of the 
 * <code>javax.microedition.apdu.APDUConnection</code> interface
 * <code>getATR</code> method.
 *
 * This function can be implemented to perform its processing either 
 * asynchronously or synchronously. If the processing takes time, 
 * implement it as asynchronous processing to avoid blocking JBlend 
 * processing for an extended period.
 * If this function is implemented to process asynchronously, then after 
 * requesting the processing by a separate task, pass #JK_SATSA_ASYNC as 
 * the return value and promptly return control to JBlend. 
 *
 * When #JK_SATSA_ASYNC is passed as the return value, call 
 * #AmSatsaNotifyConnectionEvent() to notify JBlend of the result.
 * Pass values in the AmSatsaNotifyConnectionEvent() parameters as follows.
 * @htmlonly <blockquote> @endhtmlonly
 * <dl>
 * <dt><i>result</i>:</dt>
 * <dd>Designate one of the following. 
 *   <ul>
 *     <li>#JK_SATSA_SUCCESS<br>
 *         Processing succeeded.
 *     <li>#JK_SATSA_ERROR_GENERAL<br>
 *         Processing failed for any reason. 
 *   </ul>
 * </dd>
 * <p>
 * <dt><i>param1</i>: The number of characters in the SE ATR message.
 * <p>
 * <dt><i>param2</i>: 0</dt>
 * </dl>
 * @htmlonly </blockquote> @endhtmlonly
 *
 * If the request to another task fails or if failure is detected before 
 * this function returns, pass #JK_SATSA_ERROR_GENERAL as the return value 
 * of this function and do not call #AmSatsaNotifyConnectionEvent().
 *
 * In ISO-7816, the ATR message size is stipulated as 33 or less.
 */
JKSint32 JkSatsaGetATR(JKSatsaConnectionHandle connectionHandle, 
                        JKSint8* atr, 
                        JKSint32* len);
        
 /**
 *        Creates a handle for a connection to an SE.
 * @param slot
 *        The slot number where the SE is mounted. 
 *        The slot number returned by JkPropertyGetString() as a 
 *        "microedition.smartcardslots" system property is designated.
 * @param connHandle
 *        A pointer to the memory area for putting the SE handle value.
 * @return
 *   Return one of the following. 
 *   - #JK_SATSA_SUCCESS<br>
 *     Processing was completed normally.
 *   - #JK_SATSA_ERROR_GENERAL<br>
 *     The function failed for any reason.
 *
 * JBlend calls this function to get a connection handle for the conection to the 
 * SE in <i>slot</i>. The native system should issue a handle value that can be 
 * used by other functions performing operations on this SE to identify the SE
 * uniquely, and put it in the memory area indicated by <i>connHandle</i>. 
 * The handle value should remain valid until #JkSatsaConnectionClose() is 
 * called.
 *
 * This function is called immediately before JkSatsaOpenSEConnection().
  */
JKSint32 JkSatsaSetSEConnectionHandle(int slot, JKSatsaConnectionHandle *connHandle);

 /**
 * Opens an SE.
 *
 * @param connectionHandle
 *        A handle value identifying the SE.
 *        The value passed to JBlend by JkSatsaSetSEConnectionHandle().
 * @return
 *   Return one of the following. 
 *   - #JK_SATSA_SUCCESS<br>
 *     Processing was completed normally.
 *   - #JK_SATSA_ASYNC<br>
 *     The operation will be processed asynchronously. 
 *   - #JK_SATSA_ERROR_GENERAL<br>
 *     The function failed for any reason. 
 *   .
 *
 * JBlend calls this function to open a connection to the SE mounted in
 * the slot identified with <i>connectionHandle</i>.
 * 
 * When this function is called, perform the necessary processing in the 
 * native system to enable SE use, such as initializing.
 *
 * This function can be implemented to perform its processing either 
 * asynchronously or synchronously. If the processing takes time, 
 * implement it as asynchronous processing to avoid blocking JBlend 
 * processing for an extended period.
 * If this function is implemented to process asynchronously, then after 
 * requesting the processing by a separate task, pass #JK_SATSA_ASYNC as 
 * the return value and promptly return control to JBlend. 
 *
 * When #JK_SATSA_ASYNC is passed as the return value, call 
 * #AmSatsaNotifyConnectionEvent() to notify JBlend of the result.
 * Pass values in the AmSatsaNotifyConnectionEvent() parameters as follows.
 * @htmlonly <blockquote> @endhtmlonly
 * <dl>
 * <dt><i>result</i>:</dt>
 * <dd>Designate one of the following. 
 *   <ul>
 *     <li>#JK_SATSA_SUCCESS<br>
 *         Processing succeeded.
 *     <li>#JK_SATSA_ERROR_GENERAL<br>
 *         Processing failed for any reason. 
 *   </ul>
 * </dd>
 * <p>
 * <dt>param1: The SE handle value</dt>
 * <p>
 * <dt><i>param2</i>: 0</dt>
 * </dl>
 * @htmlonly </blockquote> @endhtmlonly
 *
 * If the request to another task fails or if failure is detected before 
 * this function returns, pass #JK_SATSA_ERROR_GENERAL as the return value 
 * of this function and do not call #AmSatsaNotifyConnectionEvent().
 *
 * When a connection to the SE is opened, it is expected that the default applet (e.g. SIM applet) 
 * will be set for all channels available for JBlend. It is not expected that an explicit 
 * select command is required to set the current active/selected applet on any channel. 
 * The default applet should allow JBlend to send APDU commands to navigate through 
 * the card file system to get ACP information, starting by selection of MF (3F 00).
 */
JKSint32 JkSatsaOpenSEConnection(JKSatsaConnectionHandle connectionHandle); 

/**
 *        Closes the connection to the SE.
 * @param connectionHandle
 *        A handle value identifying the SE.
 *        The value passed to JBlend by JkSatsaOpenSEConnection().
 * @param sendEventOnComplete
 *        A flag indicating whether the processing result is to be 
 *        passed to JBlend or not if #JK_SATSA_ASYNC is returned. 
 *        #JK_TRUE means notification is requested.
 * @return
 *   Return one of the following. 
 *   - #JK_SATSA_SUCCESS<br>
 *     Processing was completed normally.
 *   - #JK_SATSA_ASYNC<br>
 *     The operation will be processed asynchronously. 
 *   - #JK_SATSA_ERROR_GENERAL<br>
 *     The function failed for any reason.
 *   .
 *
 * This function is called when the JVM terminates.
 * In addition, when a JSI function fails, in some cases JBlend may call 
 * this function to re-connect to the SE.
 * In the native system, close the SE and free its resources. 
 *
 * This function can be implemented to perform its processing either 
 * asynchronously or synchronously. If the processing takes time, 
 * implement it as asynchronous processing to avoid blocking JBlend 
 * processing for an extended period.
 * If this function is implemented to process asynchronously, then after 
 * requesting the processing by a separate task, pass #JK_SATSA_ASYNC as 
 * the return value and promptly return control to JBlend. 
 *
 * When #JK_SATSA_ASYNC is passed as the return value, call 
 * #AmSatsaNotifyConnectionEvent() to notify JBlend of the result.
 * Pass values in the AmSatsaNotifyConnectionEvent() parameters as follows.
 * @htmlonly <blockquote> @endhtmlonly
 * <dl>
 * <dt><i>result</i>:</dt>
 * <dd>Designate one of the following. 
 *   <ul>
 *     <li>#JK_SATSA_SUCCESS<br>
 *         Processing succeeded.
 *     <li>#JK_SATSA_ERROR_GENERAL<br>
 *         Processing failed for any reason. 
 *   </ul>
 * </dd>
 * <p>
 * <dt><i>param1</i>: 0</dt>
 * <p>
 * <dt><i>param2</i>: 0</dt>
 * </dl>
 * @htmlonly </blockquote> @endhtmlonly
 *
 * If the request to another task fails or if failure is detected before 
 * this function returns, pass #JK_SATSA_ERROR_GENERAL as the return value 
 * of this function and do not call #AmSatsaNotifyConnectionEvent().
 *
 * If the functions below are being processed asynchronously and their 
 * processing result has not been notified at the time this function is 
 * called, complete the operations requested by those functions
 * and notify JBlend of their results, then process the operation of JkSatsaConnectionClose().
 * <ul>
 * <li>JkSatsaGetATR()
 * <li>JkSatsaSendCommandData()
 * <li>JkSatsaReceiveResponseData()
 * </ul>
 */ 
JKSint32 JkSatsaConnectionClose(JKSatsaConnectionHandle connectionHandle, 
                                JKBool sendEventOnComplete);

/**
 * Sends a command APDU.
 *
 * @param connectionHandle
 *        A handle value identifying the SE.
 *        The value passed to JBlend by JkSatsaOpenSEConnection().
 * @param commandApdu
 *        A pointer to the memory area holding the command APDU.
 *        The byte array passed to the <code>javax.microedition.apdu.APDUConnection</code> interface 
 *        <code>exchangeAPDU</code> method is passed here. 
 *        When #JK_SATSA_ASYNC is returned, this pointer remains valid until 
 *        the native system calls #AmSatsaNotifyConnectionEvent() to notify JBlend 
 *        of the processing result.
 * @param msgLen
 *        The size (in bytes) of the data indicated by <i>commandApdu</i>.
 * @param commandResponseType
 *        One of the following values is designated, depending on whether or not
 *        the command APDU and response APDU contain data.
 *        <ul>
 *        <li>1: Neither command APDU nor response APDU contains data.
 *        <li>2: Only response APDU contains data.
 *        <li>3: Only command APDU contains data.
 *        <li>4: Both command APDU and response APDU contain data.
 *        </ul>
 * @return
 *   Return one of the following. 
 *   - #JK_SATSA_SUCCESS<br>
 *     Processing was completed normally.
 *   - #JK_SATSA_ASYNC<br>
 *     The operation will be processed asynchronously. 
 *   - #JK_SATSA_ERROR_GENERAL<br>
 *     The function failed for any reason.
 *   .
 *
 * When this function is called, the native system should send the command APDU 
 * to the SE.
 *
 * In ISO 7816 specifying APDU protocol, the specification for data 
 * communication with smartcards defines the combination of command APDU 
 * sending and response APDU receipt as one communication unit. 
 * In keeping with this specification, when a Java application invokes the 
 * <code>exchangeAPDU</code> method, JBlend responds by calling JSI functions
 * in the following order.
 * <ul>
 * <li>JkSatsaSendCommandData()
 * <li>JkSatsaReceiveResponseData()
 * </ul>
 * While these JSI functions are being called in response to 
 * <code>exchangeAPDU</code> method invocation, in no case are these same 
 * JSI functions called for another command APDU send request. 
 *
 * This function can be implemented to perform its processing either 
 * asynchronously or synchronously. If the processing takes time, 
 * implement it as asynchronous processing to avoid blocking JBlend 
 * processing for an extended period.
 * If this function is implemented to process asynchronously, then after 
 * requesting the processing by a separate task, pass #JK_SATSA_ASYNC as 
 * the return value and promptly return control to JBlend. 
 *
 * When #JK_SATSA_ASYNC is passed as the return value, call 
 * #AmSatsaNotifyConnectionEvent() to notify JBlend of the result.
 * Pass values in the AmSatsaNotifyConnectionEvent() parameters as follows.
 * @htmlonly <blockquote> @endhtmlonly
 * <dl>
 * <dt><i>result</i>:</dt>
 * <dd>Designate one of the following. 
 *   <ul>
 *     <li>#JK_SATSA_SUCCESS<br>
 *         Processing succeeded.
 *     <li>#JK_SATSA_ERROR_GENERAL<br>
 *         Processing failed for any reason. 
 *   </ul>
 * </dd>
 * <p>
 * <dt><i>param1</i>: 0</dt>
 * <p>
 * <dt><i>param2</i>: 0</dt>
 * </dl>
 * @htmlonly </blockquote> @endhtmlonly
 *
 * If the request to another task fails or if failure is detected before 
 * this function returns, pass #JK_SATSA_ERROR_GENERAL as the return value 
 * of this function and do not call #AmSatsaNotifyConnectionEvent().
 *
 * @see JkSatsaReceiveResponseData()
 */
JKSint32 JkSatsaSendCommandData(JKSatsaConnectionHandle connectionHandle, 
                               JKSint8* commandAPDU,
                               JKUint32 msgLen, 
                               JKUint32 commandRequestType);

/**
 * Gets the response APDU.
 *
 * @param connectionHandle
 *        A handle value identifying the SE.
 *        The value passed to JBlend by JkSatsaOpenSEConnection().
 * @param responseApdu
 *        A pointer to the memory area for putting the response APDU.
 *        JBlend allocates a memory space of 300 bytes. 
 *        When #JK_SATSA_ASYNC is returned, this pointer remains valid until the native system calls
 *        #AmSatsaNotifyConnectionEvent() to notify JBlend of the processing result.
 * @param len
 *        A pointer to a memory space for putting the length (in bytes) of the 
 *        response message stored in the memory space indicated by 
 *        <i>responseApdu</i>.
 *        This is not referenced by JBlend when this function returns #JK_SATSA_ASYNC.
 * @return
 *   Return one of the following. 
 *   - #JK_SATSA_SUCCESS<br>
 *     Processing was completed normally.
 *   - #JK_SATSA_ASYNC<br>
 *     The operation will be processed asynchronously. 
 *   - #JK_SATSA_ERROR_GENERAL<br>
 *     The function failed for any reason.
 *   .
 *
 * When this function is called, the native system should put the response APDU 
 * in the memory area indicated by <i>responseApdu</i>.
 *
 * This JSI function is called after JkSatsaSendCommandData() have been called. 
 * It cannot be called, however, if JkSatsaSendCommandData() processing was
 * not completed normally.
 *
 * This function can be implemented to perform its processing either 
 * asynchronously or synchronously. If the processing takes time, 
 * implement it as asynchronous processing to avoid blocking JBlend 
 * processing for an extended period.
 * If this function is implemented to process asynchronously, then after 
 * requesting the processing by a separate task, pass #JK_SATSA_ASYNC as 
 * the return value and promptly return control to JBlend. 
 *
 * When #JK_SATSA_ASYNC is passed as the return value, call 
 * #AmSatsaNotifyConnectionEvent() to notify JBlend of the result.
 * Pass values in the AmSatsaNotifyConnectionEvent() parameters as follows.
 * @htmlonly <blockquote> @endhtmlonly
 * <dl>
 * <dt><i>result</i>:</dt>
 * <dd>Designate one of the following. 
 *   <ul>
 *     <li>#JK_SATSA_SUCCESS<br>
 *         Processing succeeded.
 *     <li>#JK_SATSA_ERROR_GENERAL<br>
 *         Processing failed for any reason. 
 *   </ul>
 * </dd>
 * <p>
 * <dt><i>param1</i>: Response APDU length (number of characters)</dt>
 * <p>
 * <dt><i>param2</i>: 0</dt>
 * </dl>
 * @htmlonly </blockquote> @endhtmlonly
 *
 * If the request to another task fails or if failure is detected before 
 * this function returns, pass #JK_SATSA_ERROR_GENERAL as the return value 
 * of this function and do not call #AmSatsaNotifyConnectionEvent().
 *
 * JBlend assumes a maximum response message size of 255 bytes per response.
 * @see JkSatsaSendCommandData()
 */
JKSint32 JkSatsaReceiveResponseData(JKSatsaConnectionHandle connectionHandle, 
                                   JKUint8* responseAPDU, 
                                   JKUint32* len);

/**
 *        Gets the PIN number entered by the user. 
 * @param action
 *        The PIN entry mode. One of the following is designated. 
 *        <ul>
 *          <li> #PIN_CMD_VERIFY
 *          <li> #PIN_CMD_CHANGE
 *          <li> #PIN_CMD_DISABLE
 *          <li> #PIN_CMD_ENABLE
 *          <li> #PIN_CMD_UNBLOCK
 *          <li> #PIN_CMD_NEW_PIN
 *        </ul>
 * @param dialogHandle
 *        The entry dialog handle value. 
 *        The value passed to JBlend by JkSatsaSetPinEntryDialogHandle().
 * @param textField1
 *        A pointer to a JKT_Satsa_TextField_Attrib structure holding the 
 *        attribute parameters of the first entry field. 
 *        The pointer held by the <i>uiTextBuffer</i> member of the 
 *        JKT_Satsa_TextField_Attrib structure indicated by this pointer 
 *        remains valid until the processing result is passed by 
 *        AmSatsaNotifyDialogEvent(). Pointers held by members other than 
 *        <i>uiTextBuffer</i> are valid until this function returns.
 * @param textField2
 *        A pointer to a JKT_Satsa_TextField_Attrib structure holding the 
 *        attribute parameters of the second entry field. 
 *        If <i>action</i> is any of the following values, #JK_NULL is 
 *        designated.
 *        <ul>
 *          <li> #PIN_CMD_VERIFY
 *          <li> #PIN_CMD_DISABLE
 *          <li> #PIN_CMD_ENABLE
 *        </ul>
 *        The pointer held by the <i>uiTextBuffer</i> member of the 
 *        JKT_Satsa_TextField_Attrib structure indicated by this pointer 
 *        remains valid until the processing result is passed by 
 *        AmSatsaNotifyDialogEvent(). Pointers held by members other than 
 *        <i>uiTextBuffer</i> are valid until this function returns.
 * @return 
 *   Return one of the following. 
 *   - #JK_SATSA_SUCCESS<br>
 *     Processing was completed normally.
 *   - #JK_SATSA_ERROR_GENERAL<br>
 *     The function failed for any reason.
 *   .
 *
 * JBlend invokes this JSI function in either of the following cases. 
 * @htmlonly <blockquote> @endhtmlonly
 * <dl>
 *   <dt><b>When a Java application invokes any of the following methods of  
 *          the <code>javax.microedition.apdu.APDUConnection</code> 
 *          interface.</b></dt>
 *   <dd>
 *   <ul>
 *     <li><code>changePin</code>
 *     <li><code>disablePin</code>
 *     <li><code>enablePin</code>
 *     <li><code>enterPin</code>
 *     <li><code>unblockPin</code>
 *   </ul>
 *   </dd>
 *   <dt><b>When it becomes necessary in PKI processing to enter new PIN 
 *          information.</b>
 *   </dt>
 * </dl>
 * @htmlonly </blockquote> @endhtmlonly
 *
 * After requesting PIN entry dialog display and entry processing by another 
 * task, return control to JBlend passing a return value. 
 *
 * Put the PIN that was entered in the entry dialog in the memory space 
 * indicated by the <i>uiTextBuffer</i> member of the 
 * JKT_Satsa_TextField_Attrib structure indicated by <i>textField1</i> or 
 * <i>textField2</i>.
 *
 * Notify the processing result to JBlend by means of #AmSatsaNotifyDialogEvent().
 * Pass values in the  #AmSatsaNotifyDialogEvent() parameters as follows.
 * <dl>
 * <dt>result:</dt>
 * <dd>Designate one of the following. 
 *   <ul>
 *     <li>#JK_SATSA_DIALOG_USER_OK<br>
 *         The user clicked the OK button. 
 *     <li>#JK_SATSA_DIALOG_USER_CANCEL<br>
 *         The user canceled.
 *     <li>#JK_SATSA_ERROR_GENERAL<br>
 *         Processing failed for any reason.
 *   </ul>
 * </dd>
 * <p>
 * <dt>param1: 0</dt>
 * <p>
 * <dt>param2: 0</dt>
 * </dl>
 *
 * When the above methods of the 
 * <code>javax.microedition.apdu.APDUConnection</code> interface are invoked, 
 * the entry dialog display and entry processing depend on the 
 * invoked method.
 * The values designated in <i>action</i> for each method invoked by JBlend 
 * are as follows.
 * <ul>
 *   <li><code>changePin</code>: #PIN_CMD_CHANGE
 *   <li><code>disablePin</code>: #PIN_CMD_DISABLE
 *   <li><code>enablePin</code>: #PIN_CMD_ENABLE
 *   <li><code>enterPin</code>: #PIN_CMD_VERIFY
 *   <li><code>unblockPin</code>: #PIN_CMD_UNBLOCK
 * </ul>
 * Perform entry dialog processing as follows based on the value indicated by 
 * <i>action</i>.
 * <dl>
 * <dt> <i>action</i> is #PIN_CMD_VERIFY</dt>
 * <dt> <i>action</i> is #PIN_CMD_ENABLE</dt>
 * <dt> <i>action</i> is #PIN_CMD_DISABLE</dt>
 * <dd>
 *     Use the members of JKT_Satsa_TextField_Attrib structure 
 *     pointed to by <i>textField1</i> as follows.
 *     <dl>
 *       <dt><i>label, labelLen</i></dt>
 *       <dd>Use for the PIN number label.</dd>
 *       <dt><i>maxLength, isNumeric</i></dt>
 *       <dd>Apply to the PIN number entry field.</dd>
 *       <dt><i>uiTextBuffer</i></dt>
 *       <dd>Put the entered PIN number.</dd>
 *     </dl>
 * </dd>
 * <dd><i>textField2</i> is not used.
 * </dd>
 * <p>
 * <dt> <i>action</i> is #PIN_CMD_CHANGE</dt>
 * <dd>
 *     Use the members of JKT_Satsa_TextField_Attrib structure 
 *     pointed to by <i>textField1</i> as follows.
 *     <dl>
 *       <dt><i>label, labelLen</i></dt>
 *       <dd>Use for the old PIN number label.</dd>
 *       <dt><i>maxLength, isNumeric</i></dt>
 *       <dd>Apply to the old PIN number entry field.</dd>
 *       <dt><i>uiTextBuffer</i></dt>
 *       <dd>Put the entered old PIN number.</dd>
 *     </dl>
 * </dd>
 * <p>
 * <dd>
 *     Use the members of JKT_Satsa_TextField_Attrib structure 
 *     pointed to by textFields2 as follows.
 *     <dl>
 *       <dt><i>label, labelLen</i></dt>
 *       <dd>Use for the new PIN number label.</dd>
 *       <dt><i>maxLength, isNumeric</i></dt>
 *       <dd>Apply to the new PIN number entry field.</dd>
 *       <dt><i>uiTextBuffer</i></dt>
 *       <dd>Put the entered new PIN number.</dd>
 *     </dl>
 * </dd>
 * <p>
 * <dt> <i>action</i> is #PIN_CMD_UNBLOCK</dt>
 * <dd>
 *     Use the members of JKT_Satsa_TextField_Attrib structure 
 *     pointed to by textFields1 as follows.
 *     <dl>
 *       <dt><i>label, labelLen</i></dt>
 *       <dd>Use for the label of the blocked PIN number to be unblocked.</dd>
 *       <dt><i>maxLength, isNumeric</i></dt>
 *       <dd>Apply to the entry field of the PIN number for unblocking.</dd>
 *       <dt><i>uiTextBuffer</i></dt>
 *       <dd>Put the entered PIN number for unblocking.</dd>
 *     </dl>
 * </dd>
 * <p>
 * <dd>
 *     Use the members of JKT_Satsa_TextField_Attrib structure 
 *     pointed to by textFields2 as follows.
 *     <dl>
 *       <dt><i>label, labelLen</i></dt>
 *       <dd>Use for the label of the blocked PIN number.</dd>
 *       <dt><i>maxLength, isNumeric</i></dt>
 *       <dd>Apply to the entry field of the blocked PIN number.</dd>
 *       <dt><i>uiTextBuffer</i></dt>
 *       <dd>Put the entered blocked PIN number.</dd>
 *     </dl>
 * </dd>
 * </dl>
 * For entry dialog specifics, see the descriptions of the above methods in 
 * <i>Security and Trust Services API (SATSA) for Java 2 Platform, Micro 
 * Edition Version 1.0</i>.
 *
 * When entry of new PIN information becomes necessary in PKI processing, JBlend
 * passes #PIN_CMD_NEW_PIN in <i>action</i>.
 * An example of how the native system might choose to display the dialog is shown in Figure 1.
 *
 * @image html satsa_dialog_new_pin_en.gif "Figure 1. Entry Dialog When PIN_CMD_NEW_PIN Was Designated"
 *
 * Whether an entry field for PIN double-checking is displayed or not is 
 * implementation dependent. 
 *
 * If the request to another task fails or if failure is detected before 
 * this function returns, pass #JK_SATSA_ERROR_GENERAL as the return value 
 * of this function and do not call #AmSatsaNotifyDialogEvent().
 *
 */
JKSint32 JkSatsaPinEntryDialog(JKSint32 action,
                               JKSatsaDialogHandle dialogHandle,
                               JKT_Satsa_TextField_Attrib* textField1,
                               JKT_Satsa_TextField_Attrib* textField2 ); 

/**
 *        Creates a PIN entry dialog handle. 
 * @param dialogHandle
 *        A pointer to the buffer for putting the created handle value of the PIN entry dialog. 
 * @return 
 *   Return one of the following values. 
 *   - #JK_SATSA_SUCCESS<br>
 *     Processing was completed normally.
 *   - #JK_SATSA_ERROR_GENERAL<br>
 *     The function failed for any reason.
 *   .
 *
 * In the native system, issue a unique handle value enabling other JSI 
 * functions to identify the PIN entry dialog, and store the handle in the 
 * memory space indicated by <i>dialogHandle</i>.
 *
 * This function is called immediately before JkSatsaPinEntryDialog().
 */
JKSint32 JkSatsaSetPinEntryDialogHandle(JKSatsaDialogHandle *dialogHandle); 

/**
 * Disposes of an entry dialog handle. 
 *
 * @param dialogHandle
 *        The entry dialog handle value. 
 *        The value passed to JBlend by JkSatsaPinEntryDialog().
 *
 * JBlend invokes this JSI function after being notified of the result of
 * JkSatsaPinEntryDialog() processing by #AmSatsaNotifyDialogEvent().
 */
void JkSatsaFreePinEntryDialogHandle(JKSatsaDialogHandle dialogHandle); 

/**
 * Gets MIDlet information as part of Access Control Implementation 
 * based on Appendix A of SATSA specification. 
 * @param vmID
 *        vmID, set by the native system, and passed as the first parameter of 
 *        AamsVmStartMIDP(). This is used so that the native system can 
 *        identify the current running MIDlet for which the information 
 *        to be passed to JBlend.
 * @param rootLen 
 *        A pointer to the buffer for putting the length in bytes of the root field passed via <i>root</i>. 
 *        Must be either 0 (field not present) or 20 (SHA-1 value).
 * @param root 
 *        A pointer to the buffer for putting the SHA-1 hash of root certificate in the path used to sign 
 *        the J2ME application. 
 *        20 bytes are allocated for the buffer.
 * @param endEntityLen
 *        A pointer to the buffer for putting the length in bytes of the endEnitity field passed via <i>endEnitity</i>. 
 *        Must be either 0 (field not present) or 20 (SHA-1 value) 
 * @param endEntity 
 *        A pointer to the buffer for putting the SHA-1 hash of end-entity certificate used to sign the
 *        J2ME application. 
 *        20 bytes are allocated for the buffer.
 * @param oidLen 
 *        A pointer to the buffer for putting the length of OID used to identify the Domain category.
 *        The length should be in the range from 0 (field not present) to 128 (preallocated buffer size). 
 * @param OID
 *        A pointer to the buffer for putting the OID for identifying the Domain category ("operator", "manufacturer", 
 *        or "trusted 3rd Party") in which the J2ME application should belong to. 
 *        128 bytes are allocated for the buffer.
 * @return 
 *        Return one of the following values. 
 *        - #JK_SATSA_SUCCESS<br>
 *          The function succeeded.
 *        - #JK_SATSA_ERROR_GENERAL<br>
 *          The function failed for any reason.
 *        .
 *
 *
 * JBlend invokes this JSI function the first time a connection is requested for any SE. 
 * It will not be invoked for subsequent open operations on the same SE. 
 *
 * Note, any or all of the value fields can be left unset by indicating 0 for the corresponding length field. 
 *
 * See sections A.4.3.1 and A.4.2.6 of SATSA specification for details of the information that this function should pass.
 * If ACP is not supported, this function can be implemented as an empty function passing 0 in
 * <i>*rootLen</i>, <i>*endEntityLen</i>, and <i>*oidLen</i> and returning #JK_SATSA_SUCCESS.
 *
 */
JKSint32 JkSatsaGetMidletInfo(JKSint32 vmId, 
                              JKSint32 *rootLen,
                              JKUint8 *root,
                              JKSint32 *endEntityLen,
                              JKUint8 *endEntity, 
                              JKSint32 *oidLen, 
                              JKUint8 *OID);
#ifdef __cplusplus
}
#endif

#endif /* ___JK_SATSA_PROTOCOL_H */
