/**
 * @file 
 */

/**
 * @addtogroup Module_PIM_JSI
 *
 * @{
 */

#ifndef ___JK_PIM_H
#define ___JK_PIM_H

#ifdef __cplusplus
extern "C" {
#endif


#include "JkTypes.h"
#include "JkPIMCommon.h"
#include "JkPIMRepeatRule.h"


/**
 *  Lists all PIM list names for the given list type.
 *  
 *  @param taskId
 *         The task ID.
 *  @param listType
 *         The list type. One of the following is designated.
 *         <ul>
 *          <li> #JK_PIM_CONTACT
 *          <li> #JK_PIM_EVENT 
 *          <li> #JK_PIM_TODO 
 *         </ul>
 *  @param *array
 *         A pointer to the JKPIMStringArray structure for putting the list names. 
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_SECURITY_ERR: The application has no privilege to read the list.
 *   </ul>
 *  <p>
 * 
 * Using AmPIMStringArrayAddString(), add all list names of the designated  
 * list type to the JKPIMStringArray structure indicated in the 
 * <i>array</i> parameter.
 * 
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the list name list retrieval in a native system task. 
 *     This function should only issue a name acquisition request and return immediately.
 *     Even when this function is implemented to perform its processing asynchronously, 
 *     the acquired list names should be added to the JKPIMStringArray structure 
 *     designated by the <i>array</i> parameter, by using AmPIMStringArrayAddString().
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_SECURITY_ERR
 *       </ul>
 *      <dt>event[2]
 *      <dd>Number of lists.
 *     </dl>
 *  </dl>
 * 
 *  If the return value for this function is #JK_PIM_GENERAL_ERR, a <code>RuntimeException</code> 
 *  will be thrown in the Java application.
 * 
 */
JKPIMErrCode JkPIMGetListNames(JKSint32 taskId,JKPIMListType listType,JKPIMStringArray* array);


/**
 *         Gets the name of the default list of a list type.
 *
 *  @param taskId
 *         The task ID.
 *  @param listType
 *         The list type. One of the following is designated.
 *         <ul>
 *          <li> #JK_PIM_CONTACT
 *          <li> #JK_PIM_EVENT 
 *          <li> #JK_PIM_TODO 
 *         </ul>
 *  @param name 
 *         A pointer to the JKPIMString structure for putting the default list name. 
 * 
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. <br>
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.<br>
 *     Return  #JK_PIM_MEMORY_ERR if this function fails due to insufficient memory.
 * 
 *  By using AmPIMStringSetString(), set in the JKPIMString structure indicated by <i>name</i>
 *  the name of the default list of the designated list type.
 *  If default list is not present for the list type, return #JK_PIM_SUCCESS without 
 *  setting any data through <i>name</i>.
 * 
 *  The default list is a list which should be opened when a Java application 
 *  requests a list by <code>javax.microedition.pim.PIM</code> class 
 *  <code>openPIMList(int pimListType,int mode)</code> method.
 *  
 *  This function must work normally even when the data base supported by the target device 
 *  is not readable.
 * 
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the list name retrieval in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *       </ul>
 *     </dl>
 *  </dl>
 */
JKPIMErrCode JkPIMGetDefaultListName(JKSint32 taskId,JKPIMListType listType,JKPIMString* name);


/**
 *  Opens a connection to a list.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param listType 
 *         The list type. One of the following is designated.
 *         <ul>
 *          <li> #JK_PIM_CONTACT
 *          <li> #JK_PIM_EVENT 
 *          <li> #JK_PIM_TODO 
 *         </ul>
 *  @param mode 
 *         The access mode. One of the following is designated.
 *         <ul>
 *          <li> #JK_PIM_READ_ONLY 
 *          <li> #JK_PIM_WRITE_ONLY
 *          <li> #JK_PIM_READ_WRITE
 *         </ul>
 *  @param *name 
 *         A pointer to the JKPIMStringArray structure holding the list names. 
 *  @param *connectionId 
 *         A pointer to the buffer for putting the connection ID of the connected list. 
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_SECURITY_ERR: The Java application does not have the 
 *          privilege for connecting to the list in the designated access mode.
 *    <li> #JK_PIM_FEATURE_NOT_SUPPORTED: The native system does not support 
 *          the designated list type.
 *    <li> #JK_PIM_LIST_NOT_ACCESSIBLE: No list was found with the list name designated.
 *   </ul>
 *  <p>
 * 
 *  Open a connection to the designated list and return a connection ID to identify 
 *  the connected list. No specification is made regarding connection ID values, but
 *  they should be usable for determining the list type, access mode, and list name
 *  of the target list.
 *  JBlend uses the connection ID to designate the list in subsequent processing.
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the connection opening processing in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_SECURITY_ERR
 *        <li> #JK_PIM_FEATURE_NOT_SUPPORTED
 *        <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *       </ul>
 *      <dt>event[2]
 *      <dd>The connection ID of the connected list.
 *     </dl>
 *   </dd>
 *  </dl>
 *  
 *  The pointer passed in the <i>name</i> parameter is valid only until this functions returns. 
 *  When this function is implemented to perform its processing asynchronously, the list
 *  name designated in the <i>name</i> parameter must be copied to a memory area in the native 
 *  system for use.
 * 
 *  If the return value for this function is #JK_PIM_GENERAL_ERR, a <code>RuntimeException</code> 
 *  will be thrown in the Java application.
 */
JKPIMErrCode JkPIMOpenConnection(JKSint32 taskId,JKPIMListType listType,JKPIMAccessMode mode,JKPIMString* name,JKSint32* connectionId);


/**
 *  Closes a connection to the list.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param finalize
 *         #JK_TRUE is designated when an open connection is closed at the
 *         time of Java application completion.
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_LIST_NOT_ACCESSIBLE: The list cannot be accessed.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 * 
 *  <p>
 *  Close the connection to the designated list and free all associated resources. 
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the connection closing processing in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *       </ul>
 *     </dl>
 *   </dd>
 *  </dl>
 * 
 *  There are two kinds of situations that trigger the calling of this function to 
 *  close a connection to a list, as follows. 
 *  <ol>
 *   <li>When a Java application explicitly requests that the connection be closed.
 *   <li>When a connection is not explicitly closed in the Java application, but
 *       JBlend automatically closes it because there is no longer any referencing
 *       of the list connection.
 *  </ol>
 *  
 *  In the second case, this function is called from a finalizer.
 *  Waiting for processing by an asynchronous function to complete is not possible in a finalizer. 
 *  If this function is to be implemented as an asynchronous function, the possibility
 *  exists that JBlend will start the next operation before the connection to the list 
 *  is closed, and will request processing for opening a connection to the list.
 *  Thus if the processing for closing and opening a connection to the list cannot be implemented
 *  as mutually exclusive processing in the native system, do not implement this function as an
 *  asynchronous function.
 *  Note that the above considerations are not necessary if #JK_FALSE is designated in the 
 *  <i>finalize</i> parameter.
 *
 *  If the return value for this function is #JK_PIM_GENERAL_ERR, a <code>RuntimeException</code> 
 *  will be thrown in the Java application.
 * 
 */
JKPIMErrCode JkPIMCloseConnection(JKSint32 taskId,JKSint32 connectionId,JKBool finalize);


/**
 *  Gets definitions of fields that the designated list supports.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param *array 
 *         A pointer to the JKPIMFieldDefArray structure for putting the field definitions. 
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_LIST_NOT_ACCESSIBLE: The list cannot be accessed.
 *   </ul>
 *  
 *  <p>
 *  Put the field definitions supported by the designated list in the JKPIMFieldDefArray structure 
 *  designated by the <i>array</i> parameter, by using AmPIMFieldDefArrayAddFieldDef().
 *  
 *  When the memory space used by the added field definition is no longer needed, JBlend frees it. 
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the acquisition of field definitions in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     Even when this function is implemented to perform its processing asynchronously, 
 *     the acquired field definitions should be added to the JKPIMFieldDefArray structure 
 *     designated by the <i>array</i> parameter, by using AmPIMFieldDefArrayAddFieldDef().
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *       </ul>
 *     </dl>
 *  </dl>
 * 
 * 
 */
JKPIMErrCode JkPIMGetSupportedFields(JKSint32 taskId,JKSint32 connectionId,JKPIMFieldDefArray* array);


/**
 *  Gets definitions of attributes that the designated list supports.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param *array 
 *         A pointer to the JKPIMAttributeDefArray structure for putting the field attributes. 
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 * 
 *  <p>
 *  Put the attribute definitions of the designated list supports in the JKPIMFieldDefArray 
 *  structure designated by the <i>array</i> parameter, by using AmPIMAttributeDefArrayAddAttributeDef().
 *  
 *  When the memory space used by the added attribute definition is no longer needed, JBlend frees it. 
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the acquisition of attribute definitions in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     Even when this function is implemented to perform its processing asynchronously, 
 *     the acquired field definitions should be added to the JKPIMFieldDefArray structure 
 *     designated by the <i>array</i> parameter, by using AmPIMAttributeDefArrayAddAttributeDef().
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *     </dl>
 *  </dl>
 */
JKPIMErrCode JkPIMGetSupportedAttributes(JKSint32 taskId,JKSint32 connectionId,JKPIMAttributeDefArray* array);


/**
 *  Retrieves an item from the designated list.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param itemId 
 *         Item ID.
 *  @param *item 
 *         A pointer to the JKPIMItem structure for putting the item data. 
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 *  
 *  <p>
 *  Load the item data from the designated list and put it in the JKPIMItem 
 *  structure indicated by the <i>item</i> parameter.
 *  
 *  When the memory space used for the JKPIMItem structure indicated by <i>item</i>
 *  is no longer needed, JBlend frees it by calling JkPIMFreePointer().
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the item data loading in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     Even when this function is implemented to perform its processing asynchronously, 
 *     the loaded data should be added to the JKPIMItem structure 
 *     designated by the <i>item</i> parameter.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *     </dl>
 *  </dl>
 */
JKPIMErrCode JkPIMReadItem(JKSint32 taskId,JKSint32 connectionId,JKSint32 itemId,JKPIMItem* item);


/**
 *  Adds an item to the list.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param *item 
 *         A pointer to the JKPIMItem structure holding the item data. 
 *  @param *itemId 
 *         A pointer to the buffer for putting the item ID used to identify the new item.
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_SECURITY_ERR: 
 *         The application has no privilege to write the list.
 *    <li> #JK_PIM_LIST_NOT_ACCESSIBLE: The list cannot be accessed.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 *   
 *  <p>
 *  Add an item to the designated list and return an item ID for identifying the item.
 *  
 *  No specification is made regarding item ID values, but they should be usable for 
 *  identifying an item by the connection ID and item ID.
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the item adding processing in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_SECURITY_ERR
 *        <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *      <dt>event[2]
 *      <dd>item ID.
 *     </dl>
 *  </dl>
 *  
 *  The pointer passed in the <i>item</i> parameter is valid only until this functions returns. 
 *  When this function is implemented to perform its processing asynchronously, the list
 *  name designated in the <i>item</i> parameter must be copied to a memory area in the native 
 *  system for use.
 * 
 */
JKPIMErrCode JkPIMAddItem(JKSint32 taskId,JKSint32 connectionId,JKPIMItem* item,JKSint32* itemId);

 
/**
 *  Updates an item in the list.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param itemId 
 *         The ID of the item to be update.
 *         The value obtained by JkPIMMoveToNextItem() is designated.
 *  @param *item 
 *         A pointer to the JKPIMItem structure holding the new item data. 
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_SECURITY_ERR: 
 *         The application has no privilege to write the list.
 *    <li> #JK_PIM_LIST_NOT_ACCESSIBLE: The list cannot be accessed.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 *   
 *  <p>
 *  Update the designated list item with the data passed in the <i>item</i> parameter. 
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the item updating processing in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_SECURITY_ERR
 *        <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *     </dl>
 *  </dl>
 *  The pointer passed in the <i>item</i> parameter is valid only until this functions returns. 
 *  When this function is implemented to perform its processing asynchronously, the list
 *  name designated in the <i>item</i> parameter must be copied to a memory area in the native 
 *  system for use.
 * 
 */
JKPIMErrCode JkPIMSetItem(JKSint32 taskId,JKSint32 connectionId,JKSint32 itemId,JKPIMItem* item);


/**
 *  Removes an item from the list.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param itemId 
 *         Item ID.
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_SECURITY_ERR: 
 *         The application has no privilege to write the list.
 *    <li> #JK_PIM_LIST_NOT_ACCESSIBLE: The list cannot be accessed.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 * 
 *  <p>
 *  Remove the designated item from the designated list.
 * 
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the item removal processing in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_SECURITY_ERR
 *        <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *     </dl>
 *  </dl>
 */
JKPIMErrCode JkPIMDeleteItem(JKSint32 taskId,JKSint32 connectionId,JKSint32 itemId);


/**
 *  Gets information about the categories supported in the list.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param listMaximum 
 *         A pointer to the buffer for putting the maximum number of categories 
 *         the list can support.
 *         Put 0 in this buffer if the list does not support categories.  
 *         Put -1 in this buffer if the list supports an unlimited number of categories.
 *  @param itemMaximum 
 *         A pointer to the buffer for putting the maximum number of categories 
 *         that can be assigned to an item.
 *         Put 0 in this buffer if no category can be assigned.  
 *         Put -1 in this buffer if an unlimited number of categories can be assigned.
 *  @param distinction 
 *         A pointer to the buffer for indicating whether the category name 
 *         is case-sensitive (JK_TRUE) or not (JK_FALSE).
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 *   
 *  <p>
 *  Get information about the categories supported in the designated list and 
 *  put the information in the buffers indicated by each of the parameters.
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the acquisition of categories information in a native system task.
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *      <dt>event[2]
 *      <dd>The maximum number of categories the list can support.
 *      <dt>event[3]
 *      <dd>The maximum number of categories that can be assigned to an item.
 *      <dt>event[4]
 *      <dd>The flag indicating whether the category name is case-sensitive 
 *          ( #JK_TRUE) or not ( #JK_FALSE).
 *     </dl>
 *  </dl>
 */
JKPIMErrCode JkPIMIsCategorySupported(JKSint32 taskId,JKSint32 connectionId,JKSint32* listMaximum,JKSint32* itemMaximum,JKBool* distinction);


/**
 *  Gets a list of the categories supported by the list.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param *categories 
 *         A pointer to the JKPIMStringArray structure for putting the categories.
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 *   
 *  <p>
 *  Using AmPIMAddStringToArray(), add the names of all categories 
 *  supported by the list to the JKPIMStringArray structure indicated by 
 *  the <i>categories</i> parameter.
 *  
 *  When the memory space used by the category names added in the JKPIMStringArray structure 
 *  is no longer needed, JBlend frees it. 
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the acquisition of categories in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     Even when this function is implemented to perform its processing asynchronously, 
 *     the acquired categories should be added to the JKPIMStringArray structure 
 *     designated by the <i>categories</i> parameter, by using AmPIMStringArrayAddString().
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *      <dt>event[2]
 *      <dd>Number of categories supported.
 *     </dl>
 *  </dl>
 */
JKPIMErrCode JkPIMGetSupportedCategories(JKSint32 taskId,JKSint32 connectionId,JKPIMStringArray* categories);


/**
 *  Determines whether the designated category is supported by the list.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param *category 
 *         A pointer to the JKPIMString structure holding the category name. 
 *  @param *found 
 *         A pointer to the buffer for putting the result.
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 * 
 *  <p>
 *  If the list designated in the <i>connectionId</i> parameter supports the category designated
 *  in the <i>category</i> parameter, put #JK_TRUE in the buffer indicated by the <i>found</i>
 *  parameter; if not, put #JK_FALSE in this buffer.
 * 
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the decision processing in a native system task.
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *      <dt>event[2]
 *      <dd>The decision result.
 *     </dl>
 *  </dl>
 */
JKPIMErrCode JkPIMIsCategory(JKSint32 taskId,JKSint32 connectionId,JKPIMString* category,JKBool* found);


/**
 *  Adds a category to the list.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param *category 
 *         A pointer to the JKPIMString structure holding the category name. 
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_SECURITY_ERR: 
 *         The application has no privilege to write the list.
 *    <li> #JK_PIM_MAX_CATEGORIES_EXCEEDED: 
 *        The category count exceeded the maximum number of the categories the list can support.
 *    <li> #JK_PIM_LIST_NOT_ACCESSIBLE: The list cannot be accessed.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 * 
 *  <p>
 *  Adds a category to the designated list.
 * 
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the category adding processing in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_SECURITY_ERR
 *        <li> #JK_PIM_MAX_CATEGORIES_EXCEEDED
 *        <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *     </dl>
 *  </dl>
 * 
 *  The pointer passed in the <i>category</i> parameter is valid only until this functions returns.
 *  When this function is implemented to perform its processing asynchronously, the category
 *  name designated in the <i>category</i> parameter must be copied to a memory area in the native 
 *  system for use.
 */
JKPIMErrCode JkPIMAddCategory(JKSint32 taskId,JKSint32 connectionId,JKPIMString* category);


/**
 *  Removes a category from the list.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param *category 
 *         A pointer to the JKPIMString structure holding the category name. 
 *  @param deleteFlag 
 *         If JK_TRUE is indicated, the items that stopped belonging to categories 
 *         because of the removal must be deleted.
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_SECURITY_ERR: 
 *         The application has no privilege to write the list.
 *    <li> #JK_PIM_LIST_NOT_ACCESSIBLE: The list cannot be accessed.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 *   
 *  <p>
 *  Delete the designated category from the designated list. 
 *  If #JK_TRUE is designated in the <i>deleteFlag</i> parameter, also delete items belonging
 *  only to the deleted category. 
 *  If the designated category is not in the list, return #JK_PIM_SUCCESS with no 
 *  further processing.
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the category remove processing in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_SECURITY_ERR
 *        <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *     </dl>
 *  </dl>
 *  
 *  The pointer passed in the <i>category</i> parameter is valid only until this functions returns.
 *  When this function is implemented to perform its processing asynchronously, the category
 *  name designated in the <i>category</i> parameter must be copied to a memory area in the native 
 *  system for use.
 */
JKPIMErrCode JkPIMDeleteCategory(JKSint32 taskId,JKSint32 connectionId,JKPIMString* category,JKBool deleteFlag);


/**
 *  Renames a category supported by a list.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param *currentCategory 
 *         A pointer to the JKPIMString structure holding the category name to be changed.
 *  @param *newCategory 
 *         A pointer to the JKPIMString structure holding the new category name.
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_SECURITY_ERR: 
 *         The application has no privilege to write the list.
 *    <li> #JK_PIM_LIST_NOT_ACCESSIBLE: The list cannot be accessed.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 * 
 *  <p>
 *  Rename the designated list category name.
 *  If a category already exists with the same name as that designated in <i>newCategory</i>,
 *  delete the category of the name designated in <i>currentCategory</i>, and replace the
 *  old category assigned to list items with the new category.
 * 
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the category name changing processing in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_SECURITY_ERR
 *        <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *     </dl>
 *  </dl>
 * 
 *  The pointer passed in the <i>currentCategory</i>, <i>newCategory</i> parameter is valid 
 *  only until this function returns.
 *  When this function is implemented to perform its processing asynchronously, the category
 *  names designated in the buffers must be copied to a memory area in the native 
 *  system for use.
 */
JKPIMErrCode JkPIMRenameCategory(JKSint32 taskId,JKSint32 connectionId,JKPIMString* currentCategory,JKPIMString* newCategory);


/**
 *  Determines whether the designated category can be added to an item.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param itemId 
 *         Item ID.
 *  @param *category 
 *         A pointer to the JKPIMString structure holding the category name. 
 *  @param *addable 
 *         A pointer to the buffer for putting the result.
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 * 
 *  <p>
 *  In the memory area indicated by <i>addable</i>, put #JK_TRUE if the
 *  category designated by the <i>category</i> parameter can be added to 
 *  the item designated by <i>itemId</i>, or put #JK_FALSE if it cannot 
 *  be added.  
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the decision processing in a native system task.
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *      <dt>event[2]
 *      <dd>The decision result.
 *     </dl>
 *  </dl>
 *  
 */
JKPIMErrCode JkPIMAddCategoryToItem(JKSint32 taskId,JKSint32 connectionId,JKSint32 itemId,JKPIMString* category,JKBool* addable);


/**
 *  Advances the cursor in a result set by 1.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param resultSetId 
 *         The ID identifying the result set.
 *  @param *itemId 
 *         A pointer to the buffer for putting the item ID of the current item.
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_END_OF_RESULTSET_ERR: No more result sets are available.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 * 
 *  <p>
 *  Advance the cursor in the designated result set by 1, making the next item the current
 *  item, and put the item ID of the current item in the buffer indicated by <i>itemId</i>.
 *  
 *  No specification is made regarding item ID values, but they should be usable for 
 *  identifying an item by the connection ID and item ID.
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the cursor movement in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_END_OF_RESULTSET_ERR
 *        <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *       </ul>
 *      <dt>event[2]
 *      <dd>The current item ID.
 *     </dl>
 *   </dd>
 *  </dl>
 */
JKPIMErrCode JkPIMMoveToNextItem(JKSint32 taskId,JKSint32 connectionId,JKSint32 resultSetId,JKSint32* itemId);


/**
 *  Extracts from a list a result set containing all the list items.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param *resultSetId 
 *         A pointer to the buffer for putting the result set ID. 
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_SECURITY_ERR: 
 *         The application has no privilege to read the list.
 *    <li> #JK_PIM_LIST_NOT_ACCESSIBLE: The list cannot be accessed.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 * 
 *  <p>
 *  Extract all items from the designated list, and return an ID
 *  for result set identification.
 *  No specification is made regarding result set ID values, but they should be usable for 
 *  identifying a result set by the connection ID and result set ID.
 * 
 *  Initialize the cursor in the extracted result set to point right before the first item. 
 *  
 *  Whether or not item addition, deletion or other such operations are to be reflected
 *  in the result set is an implementation-dependent matter. 
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the extract processing in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_SECURITY_ERR
 *        <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *      <dt>event[2]
 *      <dd>The ID of the extracted result set.
 *     </dl>
 *   </dd>
 *  </dl>
 *  
 * @see JkPIMMoveToNextItem()
 * @see JkPIMCloseResultSet()
 */
JKPIMErrCode JkPIMGetResultSetByAll(JKSint32 taskId,JKSint32 connectionId,JKSint32* resultSetId);


/**
 *  Extracts from a list a result set consisting of items matching the designated item and data. 
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param *pItem 
 *         A pointer to the JKPIMItem structure holding the matching data.
 *  @param *resultSetId 
 *         A pointer to the buffer for putting the result set ID. 
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_SECURITY_ERR: 
 *         The application has no privilege to read the list.
 *    <li> #JK_PIM_LIST_NOT_ACCESSIBLE: The list cannot be accessed.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 * 
 *  <p>
 *  Extract from the designated list all items matching the data designated in the <i>pItem</i>
 *  parameter, and return an ID for result set identification. 
 *  No specification is made regarding result set ID values, but they should be usable for 
 *  identifying a result set by the connection ID and result set ID.
 *  
 *  Initialize the cursor in the extracted result set to point right before the first item. 
 *  
 *  Whether or not item addition, deletion or other such operations are to be reflected
 *  in the result set is an implementation-dependent matter. 
 *  
 *  See the <code>javax.microedition.pim.PIMList.items(PIMItem)</code> method specification
 *  regarding matching rules.
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the extract processing in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_SECURITY_ERR
 *        <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *      <dt>event[2]
 *      <dd>The ID of the extracted result set.
 *     </dl>
 *   </dd>
 *  </dl>
 * @see JkPIMMoveToNextItem()
 * @see JkPIMCloseResultSet()
 */
JKPIMErrCode JkPIMGetResultSetByItem(JKSint32 taskId,JKSint32 connectionId,JKPIMItem* pItem,JKSint32* resultSetId);


/**
 *  Extracts from a list a result set consisting of items with data matching
 *  the designated string.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param *value 
 *         A pointer to the JKPIMString structure holding the matching string data.
 *  @param *resultSetId 
 *         A pointer to the buffer for putting the result set ID. 
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_SECURITY_ERR: 
 *         The application has no privilege to read the list.
 *    <li> #JK_PIM_LIST_NOT_ACCESSIBLE: The list cannot be accessed.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 * 
 *  <p>
 *  Extract from the designated list all items matching the data designated in the <i>value</i>
 *  parameter, and return an ID for result set identification. 
 *  No specification is made regarding result set ID values, but they should be usable for 
 *  identifying a result set by the connection ID and result set ID.
 *  
 *  Initialize the cursor in the extracted result set to point right before the first item. 
 *  
 *  Whether or not item addition, deletion or other such operations are to be reflected
 *  in the result set is an implementation-dependent matter. 
 *  
 *  See the <code>javax.microedition.pim.PIMList.items(java.lang.String)</code> method specification
 *  regarding matching rules.
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the extract processing in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_SECURITY_ERR
 *        <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *      <dt>event[2]
 *      <dd>The ID of the extracted result set.
 *     </dl>
 *   </dd>
 *  </dl>
 * @see JkPIMMoveToNextItem()
 * @see JkPIMCloseResultSet()
 */
JKPIMErrCode JkPIMGetResultSetByString(JKSint32 taskId,JKSint32 connectionId,JKPIMString* value,JKSint32* resultSetId);


/**
 *  Extracts from a list a result set consisting of items assigned to the designated
 *  category.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param *category 
 *         A pointer to the JKPIMString structure holding the matching category name.
 *         If the JKPIMString structure <i>text</i> member is #JK_NULL or the <i>length</i>
 *         member is 0 or less, extract items not assigned to any category.
 *  @param *resultSetId 
 *         A pointer to the buffer for putting the result set ID. 
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_SECURITY_ERR: 
 *         The application has no privilege to read the list.
 *    <li> #JK_PIM_LIST_NOT_ACCESSIBLE: The list cannot be accessed.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 * 
 *  <p>
 *  Extract from the designated list the items assigned to the category designated
 *  in the <i>category</i> parameter, and return an ID for result set identification.
 *  No specification is made regarding result set ID values, but they should be usable for 
 *  identifying a result set by the connection ID and result set ID.
 * 
 *  Initialize the cursor in the extracted result set to point right before the first item. 
 *  
 *  Whether or not item addition, deletion or other such operations are to be reflected
 *  in the result set is an implementation-dependent matter. 
 *  
 *  See the <code>javax.microedition.pim.PIMList.itemsByCategory(java.lang.String)</code> method specification
 *  regarding matching rules.
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the extract processing in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_SECURITY_ERR
 *        <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *      <dt>event[2]
 *      <dd>The ID of the extracted result set.
 *     </dl>
 *   </dd>
 *  </dl>
 * @see JkPIMMoveToNextItem()
 * @see JkPIMCloseResultSet()
 */
JKPIMErrCode JkPIMGetResultSetByCategory(JKSint32 taskId,JKSint32 connectionId,JKPIMString*category,JKSint32* resultSetId);


/**
 *  Extracts from a list a result set consisting of items of type #JK_PIM_EVENT
 *  occurring during the designated period.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param searchType 
 *         The search type. One of the following is designated.
 *         <ul>
 *          <li> #JK_PIM_EVENT_SEARCH_TYPE_STARTING
 *          <li> #JK_PIM_EVENT_SEARCH_TYPE_ENDING
 *          <li> #JK_PIM_EVENT_SEARCH_TYPE_OCCURRING
 *         </ul>
 *  @param *startDate 
 *         The starting date and time of the search.
 *  @param *endDate 
 *         The end date and time of the search.
 *  @param initialEventOnly 
 *         If #JK_TRUE is designated, only items are searched whose field ID is 
 *         #JK_PIM_EVENT_START or #JK_PIM_EVENT_END, depending on the search type.
 *         If #JK_FALSE is designated, events that occur according to a repeat rule 
 *         are also included in the search. 
 *  @param *resultSetId 
 *         A pointer to the buffer for putting the result set ID. 
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_SECURITY_ERR: The application has no privilege to read the list.
 *    <li> #JK_PIM_FEATURE_NOT_SUPPORTED: The list does not support this feature.
 *    <li> #JK_PIM_LIST_NOT_ACCESSIBLE: The list cannot be accessed.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 * 
 *  <p>
 *  Extract from the list of the type #JK_PIM_EVENT the items occurring
 *  during the designated period, and return an ID for result set identification.
 *  
 *  If #JK_PIM_EVENT_SEARCH_TYPE_STARTING is designated in <i>searchType</i>,
 *  search for items whose event started during the designated period. 
 *  If #JK_PIM_EVENT_SEARCH_TYPE_ENDING is designated, search for items
 *  whose event ended during the designated period.
 *  If #JK_PIM_EVENT_SEARCH_TYPE_OCCURRING is designated, search for items
 *  whose event occurred during the designated period.
 *  
 *  Sort items in the result set in ascending order and avoid duplication.
 *  
 *  Whether or not item addition, deletion or other such operations are to be reflected
 *  in the result set is an implementation-dependent matter. 
 *  
 *  See the <code>javax.microedition.pim.EventList.items(int, long, long, boolean)</code> method specification
 *  regarding matching rules.
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the extract processing in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_SECURITY_ERR
 *        <li> #JK_PIM_FEATURE_NOT_SUPPORTED
 *        <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *      <dt>event[2]
 *      <dd>The ID of the extracted result set.
 *     </dl>
 *   </dd>
 *  </dl>
 * 
 * 
 * @see JkPIMMoveToNextItem()
 * @see JkPIMCloseResultSet()
 */
JKPIMErrCode JkPIMGetResultSetForEvent(JKSint32 taskId,JKSint32 connectionId,JKSint32 searchType,JKPIMCalendar* startDate,JKPIMCalendar* endDate,JKBool initialEventOnly,JKSint32* resultSetId);


/**
 *  Extracts from a list a result set consisting of #JK_PIM_TODO type items whose 
 *  date falls in the designated period.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param field 
 *         The kind of the date. 
 *         #JK_PIM_TODO_REVISION or the identifier of a #JKPIMDate type extended 
 *         field originally defined by the native system is passed.
 *  @param *startDate 
 *         The starting date and time of the search.
 *         The date as a value expressing the elapsed milliseconds from 0:00:00.000, 
 *         January 1, 1970 (GMT) is designated.
 *  @param *endDate 
 *         The end date and time of the search.
 *         The date as a value expressing the elapsed milliseconds from 0:00:00.000, 
 *         January 1, 1970 (GMT) is designated.
 *  @param *resultSetId 
 *         A pointer to the buffer for putting the result set ID. 
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_SECURITY_ERR: The application has no privilege to read the list.
 *    <li> #JK_PIM_FEATURE_NOT_SUPPORTED: The list does not support this feature.
 *    <li> #JK_PIM_LIST_NOT_ACCESSIBLE: The list cannot be accessed.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 * 
 *  <p>
 *  Extract from a #JK_PIM_TODO type list the items whose date matches the designated
 *  period, and return an ID for result set identification. 
 *  
 *  Sort items in the result set in ascending order.
 *  
 *  Whether or not item addition, deletion or other such operations are to be reflected
 *  in the result set is an implementation-dependent matter. 
 *  
 *  See the <code>javax.microedition.pim.ToDoList.items(int, long, long)</code> method specification
 *  regarding matching rules.
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the extract processing in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_SECURITY_ERR
 *        <li> #JK_PIM_FEATURE_NOT_SUPPORTED
 *        <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *      <dt>event[2]
 *      <dd>The ID of the extracted result set.
 *     </dl>
 *   </dd>
 *  </dl>
 * @see JkPIMMoveToNextItem()
 * @see JkPIMCloseResultSet()
 */
JKPIMErrCode JkPIMGetResultSetForToDoDate(JKSint32 taskId,JKSint32 connectionId,JKSint32 field,JKPIMDate* startDate,JKPIMDate* endDate,JKSint32* resultSetId);


/**
 *  Extracts from a list a result set consisting of #JK_PIM_TODO type items whose 
 *  date falls in the designated period.
 *  
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param fieldId 
 *         The kind of the date. 
 *         One of the following values or the identifier of a JKPIMCalendar type
 *         extended field originally defined by the native system is passed.
 *         <ul>
 *          <li> #JK_PIM_TODO_DUE
 *          <li> #JK_PIM_TODO_COMPLETION_DATE
 *         </ul>
 *  @param *startDate 
 *         The starting date and time of the search.
 *  @param *endDate 
 *         The end date and time of the search.
 *  @param *resultSetId 
 *         A pointer to the buffer for putting the result set ID. 
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_SECURITY_ERR: The application has no privilege to read the list.
 *    <li> #JK_PIM_FEATURE_NOT_SUPPORTED: The list does not support this feature.
 *    <li> #JK_PIM_LIST_NOT_ACCESSIBLE: The list cannot be accessed.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 * 
 *  <p>
 *  Extract from a #JK_PIM_TODO type list the items whose date matches the designated
 *  period, and return an ID for result set identification. 
 *  
 *  Sort items in the result set in ascending order.
 *  
 *  Whether or not item addition, deletion or other such operations are to be reflected
 *  in the result set is an implementation-dependent matter. 
 *  
 *  See the <code>javax.microedition.pim.ToDoList.items(int, long, long)</code> method specification
 *  regarding matching rules.
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the extract processing in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_SECURITY_ERR
 *        <li> #JK_PIM_FEATURE_NOT_SUPPORTED
 *        <li> #JK_PIM_LIST_NOT_ACCESSIBLE
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *      <dt>event[2]
 *      <dd>The ID of the extracted result set.
 *     </dl>
 *   </dd>
 *  </dl>
 * @see JkPIMMoveToNextItem()
 * @see JkPIMCloseResultSet()
 */
JKPIMErrCode JkPIMGetResultSetForToDoCalendar(JKSint32 taskId,JKSint32 connectionId,JKSint32 fieldId,JKPIMCalendar* startDate,JKPIMCalendar* endDate,JKSint32* resultSetId);



/**
 *  Closes the result set.
 * 
 *  @param taskId 
 *         The task ID.
 *  @param connectionId 
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param resultSetId 
 *         Result set ID.
 *  @return 
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_SECURITY_ERR: 
 *         The application has no privilege to read the list.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 * 
 *  <p>
 *  Close the designated result set and free all its associated resources. 
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the result set closing processing in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_SECURITY_ERR
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *     </dl>
 *   </dd>
 *  </dl>
 */
JKPIMErrCode JkPIMCloseResultSet(JKSint32 taskId,JKSint32 connectionId,JKSint32 resultSetId);

/**
 *  Allocates memory for use by the data access JBI.
 *
 * @param size 
 *        The size (in bytes) of memory to be allocated.
 * @return
 *    If this operation succeeds, return the start address of the allocated memory area; 
 *    In case of failure, return #JK_NULL.
 *
 *  This function is called inside the data access JBI for memory allocation. 
 *  
 *  The data access JBI performs its own memory allocation and release internally.
 *  When the PIM JSI is implemented to perform its processing asynchronously, it is
 *  likely that the data access JBI will be called from a task other than the JVM task.
 *  A function for use of the JBlend Java heap can be called only from the JVM task.
 *  Accordingly, when the data access JBI is called from a task other than the JVM task, 
 *  memory must be allocated not from the Java heap but from native system memory space.
 *  In other words, the memory area from which the data access JBI allocates 
 *  memory depends on how the PIM JSI is implemented.
 *  
 *  The device manufacturer should therefore implement this function in accord with 
 *  the PIM JSI implementation.
 *  
 *  The table below indicates this relationship between the PIM JSI implementation and
 *  the memory that can be used.
 *
 *  <table>
 *   <tr>
 *    <td><b>PIM JSI Implementation</b></td>
 *    <td><b>The Memory that Can Be Used</b></td>
 *   </tr>
 *   <tr>
 *    <td>Implemented as synchronous processing
 *    <td>Java heap or native system memory area
 *   </tr>
 *   <tr>
 *    <td>Implemented as asynchronous processing; data access JBI called from task other than JVM
 *    <td>Native system memory area
 *   </tr>
 *  </table>
 *  
 *  If the Java heap is used, allocate memory using AmMemAllocPointer().
 *
 * @see JkPIMFreePointer()
 */
void* JkPIMAllocPointer(JKSint32 size);


/**
 *  Frees memory used by the data access JBI.
 *
 *  @param p 
 *        A pointer to the memory area to be freed.
 
 *  Free the memory that was allocated by JkPIMAllocPointer().
 *
 *  Perform this processing in accord with the JkPIMAllocPointer() implementation.
 *  That is, if AmMemAllocPointer() is used by JkPIMAllocPointer(), 
 *  use AmMemFreePointer() to free the memory.
 * @see JkPIMAllocPointer()
 */
void JkPIMFreePointer(void* p);


/* ========== ========== =========== ========== ==========
	@: stream function
   ========== ========== =========== ========== ========== */
/**
 *  Gets a list of input/output formats supported for an item.
 * 
 *  @param listType
 *         The list type.
 *  @param *array
 *         A pointer to the JKPIMStringArray structure for putting the string indicating 
 *         supported input/output formats. 
 *  @return
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 *  <p>
 *  Get a list of the input and output formats that can be used for items belonging
 *  to the designated list type, and put the list of formats in the JKPIMStringArray 
 *  structure indicated by the <i>array</i> parameter.
 *  
 *  Use the following notation to indicate the input and output formats. <br>
 *  <Format (in upper case)>/<version><br>
 *  <dl>
 *   <dt>ex.
 *   <dd>VCARD/2.1
 *   <dd>VCALENDAR/1.0
 *  </dl>
 *  
 *  This function is not called when the PIM data conversion processing implemented in JBlend is used.
 *  In that case this function can be implemented as an empty function.
 *  
 */
JKPIMErrCode JkPIMGetSupportedSerialFormats(JKPIMListType listType,JKPIMStringArray* array);
   
   
/**
 *  Processes 1 byte of passed data.
 * 
 *  @param data
 *         The data to be processed.
 *         -1 means all the data have been passed.
 *  @return 
 *    Return one of the following error codes indicating the data entry status or processing status.
 *    <ul>
 *     <li> #JK_PIM_DATA_FINISHED: Data entry is complete.
 *     <li> #JK_PIM_NEED_MORE_DATA: Data entry is not complete. More data is required.
 *     <li> #JK_PIM_DATA_BROKEN: Data entry is faulty.
 *     <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *     <li> #JK_PIM_GENERAL_ERR: Other errors.
 *    </ul>
 *  <p>
 *  JBlend uses this function to pass to the native system data contained in
 *  an input stream, such as vCard or vCalendar.
 *  -1 passed in <i>data</i> means the input stream has reached the end.
 *  
 *  This function is not called when the PIM data conversion processing implemented in JBlend is used.
 *  In that case this function can be implemented as an empty function.
 *  
 * @see JkPIMStartFromSerialFormat()
 */
JKPIMErrCode JkPIMReceiveSerialByte(JKSint8 data);


/**
 *  Starts conversion from serial data to item data.
 * 
 *  @param enc
 *        The character encoding used in the serial data.
 *  @return
 *     Return #JK_PIM_SUCCESS if the operation succeeds.
 *     Return #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously. 
 *     In case of failure, return one of the following values. 
 *     <ul>
 *      <li> #JK_PIM_MEMORY_ERR: Insufficient memory error. 
 *      <li> #JK_PIM_UNSUPPORTED_CHAR_ENCODING_ERR: The character encoding is not supported.
 *      <li> #JK_PIM_GENERAL_ERR: Other errors.
 *     </ul>
 *  <p>
 *  This function notifies the native system of the start of processing for 
 *  converting serial data to item data. 
 *  It is assumed that the processing by this function will be 
 *  work buffer allocation and the like. 
 *  
 *  After this function is called, JkPIMReceiveSerialByte() or JkPIMReceiveSerialBytes()
 *  is called for passing data read from the input stream by JBlend.
 *  JkPIMReceiveSerialByte() and JkPIMReceiveSerialBytes() are called repeatedly
 *  until the return value indicates that data entry is complete. 
 *  When data entry is complete, JBlend calls JkPIMExecuteFromSerialFormat() to request conversion 
 *  of the serial data to item data. 
 *  One data entry may contain multiple item data, in which case JkPIMExecuteFromSerialFormat()
 *  must perform conversion to multiple item data.
 *  Finally JBlend calls JkPIMEndFromSerialFormat() to end the conversion processing. 
 *  In no case is this series of operations interrupted by other processing. 
 * 
 *  This function is not called when the PIM data conversion processing implemented in JBlend is used.
 *  In that case this function can be implemented as an empty function.
 *  
 * @see JkPIMReceiveSerialByte()
 * @see JkPIMEndFromSerialFormat()
 * @see JkPIMExecuteFromSerialFormat()
 */
JKPIMErrCode JkPIMStartFromSerialFormat(JKPIMString* enc);


/**
 *  Converts read serial data to item data.
 * 
 *  @param taskId
 *         The task ID.
 *  @param *itemArray
 *         A pointer to the JKPIMItemArray structure for putting the created item.
 *  @return
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 *  <p>
 *  Convert to item data the serial data passed by JkPIMReceiveSerialByte() and JkPIMReceiveSerialBytes().
 *  Using AmPIMItemArrayAddItem(), add the converted item data to the
 *  JKPIMItemArray structure indicated by the <i>itemArray</i> parameter.
 *  
 *  When the memory space used by the converted data is no longer needed, JBlend frees it by calling JkPIMFreePointer().
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the data converting in a native system task.
 *     This function should only issue a request to a native system task and return immediately.
 *     Even when this function is implemented to perform its processing asynchronously, 
 *     the created item should be added to the JKPIMItemArray structure designated by the 
 *     <i>itemArray</i> parameter.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *      <dt>event[2]
 *      <dd>Number of items
 *     </dl>
 *  </dl>
 *  
 *  This function is not called when the PIM data conversion processing implemented in JBlend is used.
 *  In that case this function can be implemented as an empty function.
 * @see JkPIMStartFromSerialFormat()
 * @see JkPIMReceiveSerialByte()
 */
JKPIMErrCode JkPIMExecuteFromSerialFormat(JKSint32 taskId,JKPIMItemArray* itemArray);


/**
 * Ends conversion from serial data to item data.
 * 
 * @return
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     In case of failure, return one of the following values.
 *   <ul>
 *    <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *    <li> #JK_PIM_GENERAL_ERR: Other errors.
 *   </ul>
 * <p>
 * This function notifies the native system that processing for converting serial data to
 * item data has ended. It is assumed that the processing by this function will be 
 * work buffer freeing and the like. 
 * 
 * This function is not called when the PIM data conversion processing implemented in JBlend is used.
 * In that case this function can be implemented as an empty function.
 *  
 * @see JkPIMStartFromSerialFormat()
 */
JKPIMErrCode JkPIMEndFromSerialFormat(void);


/**
 *  Converts from item data to serial data.
 * 
 *  @param taskId
 *         The task ID.
 *  @param *pItem
 *         A pointer to the JKPIMItem structure holding the item data for conversion.
 *  @param *enc
 *         The character encoding of the serial data after conversion. 
 *  @param *format
 *         The output data format.
 *  @param **data
 *         A pointer to a memory area for putting a pointer to the memory area holding
 *         the serial data after conversion. 
 *  @param *size
 *         A pointer to a memory area for putting the data size (in bytes) of the serial
 *         data after conversion. 
 * @return
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return  #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *    <ul>
 *     <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *     <li> #JK_PIM_UNSUPPORTED_CHAR_ENCODING_ERR: The character encoding is not supported.
 *     <li> #JK_PIM_UNSUPPORTED_DATA_FORMAT_ERR: The data format is not supported.
 *     <li> #JK_PIM_GENERAL_ERR: Other errors.
 *    </ul>
 *  <p>
 *  Convert to serial data the item data passed in <i>pItem</i>.
 *  Using AmPIMItemArrayAddItem(), add the converted item data to the
 *  JKPIMItemArray structure indicated by the <i>itemArray</i> parameter.
 *  
 *  The memory space containing the converted serial data is freed by 
 *  JBlend by using JkPIMFreePointer() when it is no longer needed.
 *  
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the data converting in a native system task.
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_UNSUPPORTED_CHAR_ENCODING_ERR
 *        <li> #JK_PIM_UNSUPPORTED_DATA_FORMAT_ERR
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *      <dt>event[2]
 *      <dd>A pointer to a memory area holding the serial data after conversion. 
 *      <dt>event[3]
 *      <dd>The data size (in bytes) of the serial data after conversion.
 *     </dl>
 *  </dl>
 * 
 * This function is not called when the PIM data conversion processing implemented in JBlend is used.
 * In that case this function can be implemented as an empty function.
 *  
 */
JKPIMErrCode JkPIMExecuteToSerialFormat(JKSint32 taskId,JKPIMItem* pItem,JKPIMString* enc,JKPIMString* format,JKSint8** data,JKSint32* size);


/**
 *  Copies item data.
 * 
 *  @param taskId
 *         The task ID.
 *  @param connectionId
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 *  @param *destItem
 *          A pointer to the JKPIMItem structure at the copy destination.
 *  @param *srcItem
 *          A pointer to the JKPIMItem structure at the copy source.
 *  @return
 *     Return #JK_PIM_SUCCESS if the operation succeeds. 
 *     Return #JK_PIM_ASYNC_FUNCTION if this function performs its processing asynchronously.
 *     In case of failure, return one of the following values.
 *    <ul>
 *     <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *     <li> #JK_PIM_GENERAL_ERR: Other errors.
 *    </ul>
 *  <p>
 *  Copy the item designated in <i>srcItem</i> to the item designated in <i>destItem</i>.
 *  Adjust the format in accord with the list designated in <i>connectionId</i>.
 *  
 *  When the memory space used for the JKPIMItem structure holding the copied item
 *  is no longer needed, JBlend frees it by calling JkPIMFreePointer().
 *  <dl>
 *   <dt><b>If this function is implemented as an asynchronous function: </b></dt>
 *   <dd>
 *     Perform the data copying in a native system task. 
 *     This function should only issue a request to a native system task and return immediately.
 *     When the operation is completed or an error occurs, perform event notification
 *     through AmPIMNotifyAsyncFunctionFinished().
 *     The event to be notified of is as follows.
 *     <dl>
 *      <dt>event[0]
 *      <dd>The task ID.<br>Designate the value set in the <i>taskId</i> parameter. 
 *      <dt>event[1]
 *      <dd>The processing result.<br>Designate one of the following.
 *       <ul>
 *        <li> #JK_PIM_SUCCESS
 *        <li> #JK_PIM_MEMORY_ERR
 *        <li> #JK_PIM_GENERAL_ERR
 *       </ul>
 *     </dl>
 *  </dl>
 * 
 */
JKPIMErrCode JkPIMImportItem(JKSint32 taskId,JKSint32 connectionId,JKPIMItem* destItem,JKPIMItem* srcItem);


/**
 * Receive data read from the input stream holding vCard/vCalendar data.
 *
 * @param *data
 *         This is a pointer to the memory space holding the data to be processed. 
 * @param size
 *         This is the size (in bytes) of the data to be processed.
 * @return
 *    Return one of the following error codes indicating the data entry status or processing status. *    <ul>
 *     <li> #JK_PIM_DATA_FINISHED: Data entry is complete.
 *     <li> #JK_PIM_NEED_MORE_DATA: Data entry is not complete. More data is required.
 *     <li> #JK_PIM_DATA_BROKEN: Data entry is faulty.
 *     <li> #JK_PIM_MEMORY_ERR: Insufficient memory error.
 *     <li> #JK_PIM_GENERAL_ERR: Other errors.
 *    </ul>
 *  <p>
 *  JBlend uses this function to pass to the native system data contained in
 *  an input stream, such as vCard or vCalendar.
 *
 *  This function is not called if a subclass of the SerialFormatHandler class is not used.
 *  In this case implement it as an empty function that simply returns #JK_PIM_SUCCESS. 
 * 
 * Also when using the PIM data conversion processing implemented in JBlend, this function can be implemented as an empty function.
 *  
 */
JKPIMErrCode JkPIMReceiveSerialBytes(JKSint8* data,JKSint32 size);


/**
 * 
 * Gets the name of the subclass of the SerialFormatHandler class.
 * 
 * @return
 *    Return a pointer to the memory space holding the class name.
 *    Return the class name as an ASCII string terminated by '\0'.
 *    If no inherited class is used, return #JK_NULL.
 * 
 * If the device manufacturer creates a subclass inheriting the
 * com.jblend.micro.pim.SerialFormatHandler class, return its class name.
 * The class name should include the package name as in the example below. <br>
 * "com.jblend.micro.pim.SerialFormatHandler"
 * 
 * JBlend assumes that a constant will be returned by this function and therefore 
 * makes no provision for freeing memory space for a return value pointer.
 * 
 * This function is not called when the PIM data conversion processing implemented in JBlend is used.
 * In that case this function can be implemented as an empty function.
 * 
 */
const JKSint8* JkPIMGetSerialFormatHandlerClassName(void);


/**
 *
 *  Gets the combinations of fields that can be used to designate repeat rule frequency. 
 *
 * @param taskId 
 *         A task ID
 * @param connectionId
 *         The connection ID.
 *         The value returned by JkPIMOpenConnection() is passed in this parameter.
 * @param *frequencies
 *         A pointer to a JKPIMFrequencyDef structure for holding the available field combinations.
 * @return
 *     Return an error code.
 *
 * Designate in the JKPIMFrequencyDef structure indicated by the <i>frequencies</i> parameter
 * the available combinations of fields supported by the native system corresponding to
 * <code>RepeatRule</code> class <code>FREQUENCY</code> fields.
 * If the native system supports multiple combinations, set integer values for each. 
 * 
 * If the native system supports <code>FREQUENCY</code> fields but no 
 * available combinations of fields exists, set 0 in each member of the
 * JKPIMFrequencyDef structure.
 * If the native system does not <code>FREQUENCY</code> fields, leave the
 * structure without setting any value.
 *
 * This function is called only when the list type of the connected list is #JK_PIM_EVENT.
 * 
 * The JKPIMFrequencyDef structure members correspond to <code>FREQUENCY</code> field types as follows.
 * 
 * <table><caption> Table 1. The JKPIMFrequencyDef Structure Members Correspond to FREQUENCY Field Types</caption>
 *  <tr> 
 *    <td><b> The JKPIMFrequencyDef Structure Members</b></td>
 *    <td><b>FREQUENCY Field Types</b></td>
 *  </tr>
 *  <tr>
 *    <td>yearly
 *    <td> #JK_PIM_REPEAT_YEARLY
 *  </tr>
 *  <tr>
 *    <td>monthly
 *    <td> #JK_PIM_REPEAT_MONTHLY
 *  </tr>
 *  <tr>
 *    <td>weekly
 *    <td> #JK_PIM_REPEAT_WEEKLY
 *  </tr>
 *  <tr>
 *    <td>daily
 *    <td> #JK_PIM_REPEAT_DAILY
 *  </tr>
 * </table>
 * 
 * In the case of #JK_PIM_REPEAT_MONTHLY, for example, the JBlend RI supports two combinations
 * of fields as indicated below.
 * 
 * <ol>
 *  <li> #JK_PIM_REPEAT_DAY_IN_MONTH | #JK_PIM_REPEAT_COUNT | #JK_PIM_REPEAT_END | #JK_PIM_REPEAT_INTERVAL
 *  <li> #JK_PIM_REPEAT_WEEK_IN_MONTH | #JK_PIM_REPEAT_DAY_IN_WEEK | #JK_PIM_REPEAT_COUNT | #JK_PIM_REPEAT_END | #JK_PIM_REPEAT_INTERVAL
 * </ol>
 * 
 * In this case a two-element array is set in the monthly member of the JKPIMFrequencyDef structure.
 *  When the memory space used for the JKPIMFrequencyDef structure indicated by <i>frequencies</i>
 *  is no longer needed, JBlend frees it by calling JkPIMFreePointer().
 * 
 */
JKPIMErrCode JkPIMGetSupportedRepeatRuleFields(JKSint32 taskId,JKSint32 connectionId,JKPIMFrequencyDef* frequencies);


#ifdef __cplusplus
}
#endif

#endif /* ___JK_PIM_H */

/** @} end of group */
