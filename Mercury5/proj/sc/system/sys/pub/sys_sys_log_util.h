/*--------------------------------------------------------------------------*/
/* INCLUDE FILE                                                             */
/*--------------------------------------------------------------------------*/
#ifndef __SYS_SYS_LOG_UTIL_H__
#define __SYS_SYS_LOG_UTIL_H__

#include "vm_types.ht"

/*--------------------------------------------------------------------------*/
/* TYPE DEFINITION                                                          */
/*--------------------------------------------------------------------------*/
typedef	enum
{
	LOG_TYPE_UNKNOWN,
	LOG_TYPE_EXCEPTION_LOG,					/*	NC:	DBB Debug-Info																*/
	LOG_TYPE_MMP_EXCEPTION_LOG,			/*	NC:	MMP Debug-Info																*/
	LOG_TYPE_STORED_MSG,						/*	NC:	Information stored in the backtrace volume		*/
	LOG_TYPE_STORED_NO_STACK_MSG,		/*	NC:	As LOG_TYPE_STORED_MSG but without call-stack	*/
	LOG_TYPE_CRASH_NOTIFY_DATA,			/*	NC:	Get Crash Notify Data from backtrace					*/
	LOG_TYPE_BACKUP_EXCEPTION_LOG,	/*	SC:	Backup-Backtrace for no-backtrace issue				*/
	LOG_TYPE_EXCEPTION_LOG_TO_PC,		/*	SC:	Use TMT to request exception log from target	*/
	MAX_LOG_TYPE
}	log_type_e;

typedef	enum
{
	LOG_ERR_OK,
	LOG_ERR_FINISH,
	LOG_ERR_FAIL,
	LOG_ERR_WRONG,
}	log_errCode_e;

typedef	struct
{
	u32		size;
}	log_info_t;




/*--------------------------------------------------------------------------*/
/* GLOBAL FUNCTION PROTOTYPE                                                */
/*--------------------------------------------------------------------------*/

/**
 *	@brief	Try to get all number of log groups in the system
 *
 *	@param	pNbLogGroup		:	[I/O]	number of log groups, should not be NULL
 *
 *	@retval	LOG_ERR_OK		:	successful
 *	@retval	LOG_ERR_FAIL	:	fail
 *	@retval	LOG_ERR_WRONG	:	fail due to bad parameter
 */
log_errCode_e		log_util_getNbLogGroups(u32* pNbLogGroup);


/**
 *	@brief	Try to get the information and to start to get the raw data of the assigned log 
 *					in the assigned log group.
 *
 *	@param	idxLog				:	[I]	index of the assigned log group, should less than the return
 *															value of log_util_getNbLogGroups().
 *	@param	type					:	[I]	the assigned log type
 *	@param	pLogInfo			:	[I/O]	the structure of log info, should not be NULL
 *	@param	bEncrypt			:	[I]	indicate if need to encrypt the raw data. (but there are some
 *															log types will not be encrypted in default.)
 *
 *	@retval	LOG_ERR_OK		:	successful
 *	@retval	LOG_ERR_FAIL	:	fail
 *	@retval	LOG_ERR_WRONG	:	fail due to bad parameter
 */
log_errCode_e		log_util_getLogInfo(u32 idxLogGroup, log_type_e type, log_info_t* pLogInfo, bool bEncrypt);


/**
 *	@brief	Clear the log info
 *
 *	@retval	LOG_ERR_OK		:	successful
 *	@retval	LOG_ERR_FINISH:	successful and finished
 *	@retval	LOG_ERR_FAIL	:	fail
 *	@retval	LOG_ERR_WRONG	:	fail due to bad parameter
 */
log_errCode_e		log_util_clearLogInfo(void);


/**
 *	@brief	Try to get the assigned log raw data in the assigned log group
 *
 *	@param	bufferSize		:	[I]	the input buffer size, should not be 0.
 *	@param	pBuffer				:	[I/O]	the buffer address, if the input buffer is not a valid 
 *																address to be write, a data abort exception might be raised.
 *	@param	pLogSize			:	[I/O]	the copied data length, should not be NULL. If the result is 0, 
 *																the process to read the log is finished.
 *
 *	@retval	LOG_ERR_OK		:	successful
 *	@retval	LOG_ERR_FINISH:	successful and finished
 *	@retval	LOG_ERR_FAIL	:	fail
 *	@retval	LOG_ERR_WRONG	:	fail due to bad parameter
 */
log_errCode_e		log_util_getLog(u32 bufferSize, u8* pBuffer, u32* pLogSize);


/**
 *	@brief	Clear the allocated buffer
 *
 *	@retval	LOG_ERR_OK		:	successful
 *	@retval	LOG_ERR_FINISH:	successful and finished
 *	@retval	LOG_ERR_FAIL	:	fail
 *	@retval	LOG_ERR_WRONG	:	fail due to bad parameter
 */
log_errCode_e		log_util_clearLog(void);


/**
 *	@brief	Try to get the trace information from the backtrace after log_util_getLogInfo().
 *
 *	@param	pFilter				:	[I/O]	point to the storage of the trace filter
 *	@param	pTraceId			:	[I/O]	point to the storage of the trace ID (remote trace/direct string)
 *	@param	ppParamAddr		:	[I/O]	point to the storage of the parameter buffer address
 *	@param	pNbParam			:	[I/O]	point to the storage of the number of the parameter
 *
 *	@retval	LOG_ERR_OK		:	successful
 *	@retval	LOG_ERR_FAIL	:	fail
 *	@retval	LOG_ERR_WRONG	:	fail due to bad parameter
 */
log_errCode_e		log_util_getTrace(u32	*pFilter, u32	*pTraceId, u32 **ppParamAddr, u32 *pNbParam);


/**
 *	@brief	Try to clear all log groups, and destroyed all internal structure used.
 *
 *	@retval	LOG_ERR_OK		:	successful
 *	@retval	LOG_ERR_FAIL	:	fail
 *	@retval	LOG_ERR_WRONG	:	fail due to bad parameter
 */
log_errCode_e		log_util_clearAllLog(void);

#endif // __SYS_SYS_LOG_UTIL_H__

