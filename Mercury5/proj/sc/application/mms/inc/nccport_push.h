
/**
 * @file
 * PUSH Porting Layer
 *
 * Basic support functions that are needed by PUSH.
 *
 * <!-- #interface list begin -->
 * \section cpl_wap_push Interface
 * - NCCPort_push_getLengthOfFile()
 * - NCCPort_push_readSpecificData()
 * - NCCPort_push_checkFileExist()
 * - NCCPort_push_saveDataToFile()
 * - NCCPort_push_removeFile()
 * - NCCPort_push_suspend()
 * - NCCPort_push_getSysTime()
 * - NCCPort_push_decodeDate()
 * - NCCPort_push_getPushHandle()
 * <!-- #interface list end -->
 */

#ifndef __NCCPort_WAP_PUSH_H__
#define __NCCPort_WAP_PUSH_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <time.h>
#include <string.h>
#include <ncc_types.h>
#include <nccport_os.h>
#include <nccpush_common.h>
#include <nccport_mms_string.h>

/**
 * @defgroup NCCPort_PUSH Push Portinglayer
 * @ingroup PUSH_COMMON
 * The NCCPort_PUSH module mainly define some macros and APIs that relate to platform.
 */

#define PUSH_MALLOC     CRTL_malloc
#define PUSH_FREE       CRTL_free
#define PUSH_MEMSET     CRTL_memset
#define PUSH_MEMCPY     CRTL_memcpy
#define PUSH_STRCPY     CRTL_strcpy
#define PUSH_STRNCPY    CRTL_strncpy
#define PUSH_STRCMP     CRTL_strcmp
#define PUSH_STRICMP    CRTL_strcasecmp
#define PUSH_STRLEN     CRTL_strlen
#define PUSH_ATOI       CRTL_atoi
#define PUSH_ITOA       NCCPort_os_itoa
#define PUSH_STRCAT     CRTL_strcat
#define PUSH_STRNCAT    CRTL_strncat
#define PUSH_SPRINTF     CRTL_sprintf

/**
 *define some macros that used to indicate return value of FUNC which defined in the pointing layer.
 */
#define PUSH_PORTINGLAYER_OPERATION_SUCCESS             1  /**<The macro indicates the operation is successful.*/
#define PUSH_PORTINGLAYER_FILE_OPERATION_SUCCESS        1  /**<The macro indicates the operation of processing file is successful.*/
#define PUSH_PORTINGLAYER_INPUT_PARA_ERROR              -1 /**<The macro indicates the input parameter of FUCN is incorrect.*/
#define PUSH_PORTINGLAYER_OPEN_FILE_FAILURE             -2 /**<The macro indicates the operation of opening file is unsuccessful.*/
#define PUSH_PORTINGLAYER_READ_FILE_FAILURE             -3 /**<The macro indicates the operation of reading file is unsuccessful.*/
#define PUSH_PORTINGLAYER_READ_SPECIFIC_LENGTH_FAILURE  -4 /**<The macro indicates the operation of reading specificing data is unsuccessful.*/
#define PUSH_PORTINGLAYER_GETING_LENGTH_FILE_FAILURE    -5 /**<The macro indicates the operation of getting the length of file.*/
#define PUSH_PORTINGLAYER_WRITE_SPECIFIC_LENGTH_FAILURE -6 /**<The macro indicates the operation of writing data is unsuccessful.*/
#define PUSH_PORTINGLAYER_REMOVE_FILE_FAILURE           -7 /**<The macro indicates the operation of removing file is unsuccessful.*/
#define PUSH_PORTINGLAYER_GET_PUSH_HANDLE_FAILURE       -8 /**<The macro indicates the operation of getting push handle is unsuccessful.*/
#define PUSH_PORTINGLAYER_FILE_OPERATION_MAX_COUNT      3  /**<The macro indicates the the max number of file operation.*/
#define PUSH_PORTINGLAYER_FILE_OPERATION_MAX_TICK       10 /**<The macro indicates the max time of suspending.*/
#define PUSH_PORTINGLAYER_FILE_OPERATION_MAX_TIME      (SI_PORTINGLAYER_FILE_OPERATION_MAX_COUNT*SI_PORTINGLAYER_FILE_OPERATION_MAX_TICK)

#define PUSH_FIND_FIRST                                                             1 /**<Find the first file that locates at the appointed folder.*/
#define PUSH_FIND_NEXT                                                             2 /**<Find the next file that locates at the appointed folder.*/
#define PUSH_FIND_CLOSE                                                             3/**<Close the handle.*/
/**
 *define some API FUNC.These FUNC must be implemented on porting layer and invoked by push core.
 */

/**
 *Get the length of appointed file.
 * \param *file The name of the file that will be processed.
 * \param *DataLength The length of appointed file.
 *
 * \return <ul>
 *             <li>If successful,then return#PUSH_PORTINGLAYER_FILE_OPERATION_SUCCESS.
 *             <li>If unsuccessful,then return
 *             <ul>
 *                 <li>#PUSH_PORTINGLAYER_OPEN_FILE_FAILURE.
 *                 <li>#PUSH_PORTINGLAYER_GETING_LENGTH_FILE_FAILURE.
 *             </ul>
 *          </ul>
 */
int32_t NCCPort_push_getLengthOfFile(int8_t * file, int32_t *DataLength);

/**
 *Read specificing data from file.
 * \param *file The name of file.
 * \param *SpecificData The pointer of data buffer.
 * \param SpecificLength The length of data buffer.
 *
 * \return <ul>
 *             <li>If successful,then return#PUSH_PORTINGLAYER_FILE_OPERATION_SUCCESS
 *             <li>If unsuccessful,then return
 *             <ul>
 *                 <li>#PUSH_PORTINGLAYER_OPEN_FILE_FAILURE.
 *                 <li>#PUSH_PORTINGLAYER_READ_FILE_FAILURE.
 *                 <li>#PUSH_PORTINGLAYER_READ_SPECIFIC_LENGTH_FAILURE.
 *             </ul>
 *          </ul>
 */
int32_t NCCPort_push_readSpecificData(int8_t * file, uint8_t* SpecificData, int32_t SpecificLength);

/**
 *Push core can invoke the FUNC to check if appointed file exist.
 * \param *filename The pointer of file name.
 *
 * \return <ul>
 *             <li>If successful,then return#PUSH_PORTINGLAYER_FILE_OPERATION_SUCCESS.
 *             <li>If unsuccesful,then return#PUSH_PORTINGLAYER_OPEN_FILE_FAILURE.
 *         </ul>
 */
int32_t NCCPort_push_checkFileExist(int8_t *filename);

/**
 *Save data to appointed file.
 * \param *filename The pointer of filename.
 * \param *pPdu The pointer of pdu buffer that will be saved.
 * \param pduLen The length of pdu buffer.
 *
 * \return <ul>
 *             <li>If successful,then return#PUSH_PORTINGLAYER_FILE_OPERATION_SUCCESS.
 *             <li>If unsuccesful,then return
 *             <ul>
 *                 <li>#PUSH_PORTINGLAYER_OPEN_FILE_FAILURE.
 *                 <li>#PUSH_PORTINGLAYER_WRITE_SPECIFIC_LENGTH_FAILURE.
 *             </ul>
 *         </ul>
 */
int32_t NCCPort_push_saveDataToFile(int8_t *filename,uint8_t *pPdu,int32_t pduLen);

/**
 *Remove file from local folder.
 * \param *filename The pointer of file name.
 *
 * \return <ul>
 *             <li>If successful,then return#PUSH_PORTINGLAYER_FILE_OPERATION_SUCCESS.
 *             <li>If unsuccessful,then return
 *             <ul>
 *                 <li>#PUSH_PORTINGLAYER_REMOVE_FILE_FAILURE.
 *                 <li>#PUSH_PORTINGLAYER_OPEN_FILE_FAILURE.
 *             </ul>
 *         </ul>
 */
int32_t NCCPort_push_removeFile(int8_t *filename);

/**
 *Suspend.
 * \param Time The second of suspending.
 *
 * \return void
 */
void NCCPort_push_suspend(int32_t Time);

/**
 *Push module can get current sys time using this FUNC.
 *
 * \return <ul>
 *              <li>If the operation is successful,then return#PUSH_PORTINGLAYER_OPERATION_SUCCESS.
 *              <li>If the operation is unsuccessful,then return#
 *          </ul>
 */
int32_t NCCPort_push_getSysTime(uint32_t *curtime);

/**
 *Convert date struct into seconds.
 * \param date The structure of date.
 * \param *sec The pointer of seconds.
 *
 * \return void
 */
void NCCPort_push_getDataSeconds(T_PUSH_DATE date,uint32_t *sec);

#ifdef NCC_WITH_CONSMS
/**
 *Get push handle.
 * \param **push_handle The pointer of push handle.
 *
 * \return <ul>
 *             <li>If successful.then return#PUSH_PORTINGLAYER_OPERATION_SUCCESS.
 *             <li>If unsuccessful,then return#PUSH_PORTINGLAYER_GET_PUSH_HANDLE_FAILURE.
 *         </ul>
 */
int32_t NCCPort_push_getPushHandle(void **push_handle);
#endif

/**
 *Get file name that located at the appointed folder.
 * \param *path The null-terminated string to specifies the path.
 * \param type The interger to specifies the type of the current operation.(PUSH_FIND_FIRST:get the first file;PUSH_FIND_NEXT:get the next file;PUSH_FIND_CLOSE:finish the operation of finding files.)
 * \param *handle The integer pointer to specifies the filehandle(If the type is PUSH_FIND_FIRST,the parameter records the handle that returned by _findfirst API).
 * \param *filename The null-terminated string to specifies the name of the file.
 *
 * \return <ul>
 * <li>If succesful,then return#TRUE.
 * <li>Otherwise,return#FALSE.
 * </ul>
 */
int32_t NCCPort_push_getFileName(int8_t *path, int32_t type, int32_t *handle, int8_t *filename);

#ifdef __cplusplus
}
#endif

#endif
