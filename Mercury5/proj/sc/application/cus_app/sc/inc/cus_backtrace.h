/**
 *
 * @file    cus_backtrace.h
 *
 * @brief   This file defines the customer exception handler interfaces.
 *
 * @author  Xavier Fan
 * @version $Id: cus_backtrace.h 16705 2008-11-19 08:48:10Z xavier.fan $
 *
 */

#ifndef __CUS_BACKTRACE_H__
#define __CUS_BACKTRACE_H__

#define BTMSG_DECL(type) type,

#define BTMSG_COL    \
		BTMSG_DECL(BTMSG_BASIC) \
		BTMSG_DECL(BTMSG_MEM_POOL_MAP) \
		BTMSG_DECL(BTMSG_MEM_POOL_USAGE) \
		BTMSG_DECL(BTMSG_MEM_HEAP_MAP) \
		BTMSG_DECL(BTMSG_MEM_HEAP_USAGE) \
		BTMSG_DECL(BTMSG_MEM_MURDER) \
		BTMSG_DECL(BTMSG_MEM_TASK_USAGE) \
		BTMSG_DECL(BTMSG_MBX_USAGE) \
		BTMSG_DECL(BTMSG_MBX_HISTORY) \
		BTMSG_DECL(BTMSG_TSK_INFO) \
		BTMSG_DECL(BTMSG_SEM_INFO) \
		BTMSG_DECL(BTMSG_MMK_USER_DEFINED) \
		BTMSG_DECL(BTMSG_TOOL_MSG) \
		BTMSG_DECL(BTMSG_TOOL_TOOL_INFO) \
		BTMSG_DECL(BTMSG_SYS_INCENSE_INFO) \
		BTMSG_DECL(BTMSG_SYS_ARM_INFO) \
		BTMSG_DECL(BTMSG_SYS_DEBUG_INFO) \
		BTMSG_DECL(BTMSG_HW_WATCHDOG)

/**
 * @brief   The enum of the debug information category.
 */
typedef enum
{
	BTMSG_COL
	BTMSG_TYPES
} rtk_BtMsgType_e;



/** 
 * @brief   To dump MMK information. To implement this function should very careful and
 *          the funtion should not happen any exception again, or the following debug 
 *          information will be lost.
 *   
 * @retturn NONE
 */
void cus_backtrace_MmiKernelInfo(void);


/** 
 * @brief   To check if the given mailbox ID has been filtered. ** NOTE ** This function
 *          should not be modified
 *
 * @param   taskID:    The given mailbox ID to be checked.
 *
 * @retval  If the given mailbox ID is wished to show related debug information.
 */
u8   cus_backtrace_ToolGetMboxMaxSize(const u8 mboxID);


/** 
 * @brief   The function is used to dump backtrace to external data storage, for example: 
 *          memory card when an AT command been sent. The implementation should not dump
 *          backtrace in this thread, that might cause the target crashed.
 *
 * @return  NONE
 */
void cus_backtrace_ToolDumpToMemoryCard(void);


/** 
 * @brief   The function is used to dump VFS status, the content of this part is depened 
 *          on the platform.
 *
 * @return  NONE
 */
void cus_backtrace_SysGetFileSystemInfo(void);


/** 
 * @brief   The function is used to dump backtrace to TMT when the user request a debug 
 *          information directly from the target. The implementation should not dump
 *          backtrace in this thread, that might cause the target crashed.
 *
 * @return  NONE
 */
void cus_backtrace_ToolDumpToTmt(void);


/** 
 * @brief   Set the exception type to the exception handler. If the input exception type
 *          is not defined, this function return FALSE. ** NOTE ** This function should
 *          not be modified
 *
 * @param   exceptionType: The exception happened.
 *
 * @retVal  TRUE:      The input exception type is defined.
 * @retVal  FALSE:     The input exception is not defined.
 *
 * @return  NONE
 */
bool cus_backtrace_ToolSetExceptionType(const u8 exceptionType);


/** 
 * @brief   To check the set exception type is the given exception type. If not, 
 *          this function return FALSE. ** NOTE ** This function should not be 
 *          modified.
 *
 * @param   exceptionType: The exception type to be compared with the set type.
 *
 * @retVal  TRUE:      The input exception type is the same with the set type.
 * @retVal  FALSE:     The input exception type different to the set type.
 *
 * @return  NONE
 */
bool cus_backtrace_ToolCheckExceptionType(const u8 exceptionType);


/** 
 * @brief   To check if the message category filter is set to show the message.
 *          If not set or the given msgType is not defined, this function return 
 *          FALSE. ** NOTE ** This function should not be modified.
 *
 * @param   msgType: The message category type to be compared.
 *
 * @retVal  TRUE:      The message category is set to show.
 * @retVal  FALSE:     The message category is not set to show.
 *
 * @return  NONE
 */
bool cus_backtrace_ToolMessageArbiter(const rtk_BtMsgType_e msgType);


/** 
 * @brief   Print MMP On/Off related information.
 *
 * @return  NONE
 */
void cus_backtrace_MmpGetDriverInfo(void);

#endif

