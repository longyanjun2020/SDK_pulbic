/**
 *
 * @file    ven_editor.h
 * @brief   This file defines editor related request vendor API, and response data structure
 *
 * @author  Alison.Chen
 * @version $Id: ven_editor.h 47127 2009-12-10 14:30:38Z steve.lee $
 *
 */
#ifndef __VEN_EDITOR_DEFINE_H_
#define __VEN_EDITOR_DEFINE_H_


#include "ven_sdk.h"

/*--------------------------------------------------------------------------*/
/* Type Definition                                                          */
/*--------------------------------------------------------------------------*/
enum
{
    VEN_EDITOR_RET_SUCCESS             = 0, ///< operation completed successfully
    VEN_EDITOR_RET_FAILED              = 1, ///< WHAT? every code here is failed
    VEN_EDITOR_RET_NOT_SUPPORT         = 2, ///< not support
    VEN_EDITOR_RET_BAD_PARAM           = 3, ///< invalid input parameters
    VEN_EDITOR_RET_OUT_OF_MEMORY       = 4, ///< memory is not enough to complete the operation
};
typedef u32 ven_editor_ret_t;

enum
{
    VEN_EDITOR_TYPE_FORMAT              = 0, ///< according to the format string
    VEN_EDITOR_TYPE_DIALING             = 1, ///< for dialing number
    VEN_EDITOR_TYPE_RATE                = 2, ///< for decimal input
    VEN_EDITOR_TYPE_DIGITAL             = 3, ///< digital is allowed only
    VEN_EDITOR_TYPE_ALPHA               = 4, ///< alpha is allowed only
    VEN_EDITOR_TYPE_NUMERIC             = 5, ///< for negative sign and digits.
    VEN_EDITOR_TYPE_ALL                 = 6, ///< digital, alpha, Chinese are allowed
};
typedef u32 ven_editor_type_t;
enum
{
    VEN_EDITOR_STYLE_TEXT = 0,
    VEN_EDITOR_STYLE_PASSWORD
};
typedef u8 ven_editor_style_t;

enum
{
    VEN_EDITOR_ENCODING_UCS2 = 0,
	VEN_EDITOR_ENCODING_UTF8,
	VEN_EDITOR_ENCODING_ASC_UCS2
};
typedef u8 ven_editor_encoding_t;

enum
{
    VEN_EDITOR_RESULT_OK = 0,
    VEN_EDITOR_RESULT_CANCEL,
    VEN_EDITOR_RESULT_ERROR,
	VEN_EDITOR_BAD_PARAM,
};
typedef u8 ven_editor_result_t;

typedef struct
{
	u32 nSize;			//size of (ven_editor_date_format_t) for vision control
	u16 year;           ///< Year value after 1900, value range is 1900~2038
	u8  month;          ///< Month, value range is 1~12
	u8  day;            ///< Day, value range is 1~31
} ven_editor_date_format_t;

typedef struct
{
	u32 nSize;			//size of (ven_editor_time_format_t) for vision control
	u8  hour;           ///< Hour, value range is 0~23
	u8  minute;         ///< Minute, value range is 0~59
	u8  second;         ///< Second, value range is 0~59
} ven_editor_time_format_t;

/**
 *  ven_editor_edit
 *  @brief    Request a specified editor to get user input
 *            Note: This function supports both synchronous and asynchronous
 *
 *  @param  ptTitle         [in] The pointer of the title of editor. The title string is in UCS2 format without NULL terminated.
 *                               The memory of this field should be allocated by vender task.
 *                               And the memory should be freed by vender when the response message is received.
 *                               If vendor assigned NULL value, MMI will show default title string.
 *  @param  titleLen        [in] The character length of ptTitle.
 *  @param  type            [in] The content type of editor.
 *  @param  style           [in] The content style of editor.
 *  @param  encoding        [in] The encoding for counting content length.
 *  @param  maxContentLen   [in] The maximum byte length of content.
 *  @param  ptInitContent   [in] The pointer of the initial content. The initial content is in UCS2format without NULL terminated.
 *                               The memory of this field should be allocated by vender task.
 *                               And the memory should be freed by vender when the response message is received.
 *  @param  initContentLen  [in] The character length of the initial content.
 *  @param  pFormatStr      [in] The pointer of the format string. The string is in UCS2 format without NULL terminated.
 *                               This parameter is useful only if the editor type is VEN_EDITOR_TYPE_FORMAT. Or this parameter should be NULL.
 *                               The memory of this field should be allocated by vender task.
 *                               And the memory should be freed by vender when the response message is received.
 *  @param  formatStrLen    [in] The character length of the format string.
 *  @param  pptContent      [out] The pointer of the output result string. The output string is in UCS2 format without NULL terminated.
 *                                This parameter is only useful if this API is using as Sync API.
 *                                For synchronous using, this parameter shouldn't be NULL.
 *                                The Sync API will allocate the string memory, and set to this output parameter.
 *                                3rd party need to Free the allocated memory. For asynchronous using, this parameter should be set as NULL.
 *  @param  ptContentLen    [out] The pointer of the output result string length. This parameter is only useful if this API is using as Sync API.
 *                                For synchronous using, this parameter shouldn't be NULL
 *  @param  ptVenReq        [in] The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
 *                               It is up to the user to free the memory allocated for the vendor request data.
 *
 *
 *  @retval TRUE if success
 *          FALSE  if failed
 *
 *
 *  Response structure:
 *
 *  typedef struct
 *  {
 *      u16* ptContent;     [out] The pointer of the output result string.
 *      u16 contentLen;     [out] The output result string length.
 *  } ven_editor_edit_rsp_t;
 *
 *
 */
bool ven_editor_edit(u16 *ptTitle,
                     u8 titleLen,
                     ven_editor_type_t type,
                     ven_editor_style_t style,
                     ven_editor_encoding_t encoding,
                     u16 maxContentLen,
                     u16 * ptInitContent,
                     u16 initContentLen,
                     u16 * pFormatStr,
                     u8 formatStrLen,
                     u16 **pptContent,
                     u16 *ptContentLen,
                     ven_req_data_t *ptVenReq);

typedef struct
{
    ven_editor_result_t rspType;
    u16 *ptContent;
    u16 contentLen;
} ven_editor_edit_rsp_t;

typedef struct
{
	ven_editor_result_t rspType;
	u16 nYear;
	u8	nMonth;
	u8 nDay;
} ven_editor_date_rsp_t;

typedef struct
{
	ven_editor_result_t rspType;
	u8	nHour;
	u8 nMinute;
	u8 nSecond;
} ven_editor_time_rsp_t;

typedef struct
{
    u16 *ptTitle;                       ///< The pointer of the title of editor. The title string is in UCS2 format without NULL terminated.
    ///< The memory of this field should be allocated by vender task.
    ///< And the memory should be freed by vender when the response message is received.
    ///< If vendor assigned NULL value, MMI will show default title string.
    u8 titleLen;                        ///< The character length of ptTitle.
    ven_editor_type_t type;             ///< The content type of editor.
    ven_editor_style_t style;           ///< The content style of editor.
    ven_editor_encoding_t encoding;     ///< The encoding for counting content length.
    u16 maxContentByteLen;              ///< The maximum byte length of content.
    u16 *ptInitContent;                 ///< The pointer of the initial content. The initial content is in UCS2format without NULL terminated.
    ///< The memory of this field should be allocated by vender task.
    ///< And the memory should be freed by vender when the response message is received.
    u16 initContentLen;                 ///< The character length of the initial content.
    u16 *ptFormatStr;                   ///< The pointer of the format string. The string is in UCS2 format without NULL terminated.
    ///< This parameter is useful only if the editor type is VEN_EDITOR_TYPE_FORMAT. Or this parameter should be NULL.
    ///< The memory of this field should be allocated by vender task.
    ///< And the memory should be freed by vender when the response message is received.
    u8 formatStrLen;                    ///< The character length of the format string.
    ven_editor_result_t *ptOutResult;   ///< The pointer of the output result. This parameter is only useful if this API is using as Sync API.
    ///< For synchronous using, this parameter shouldn't be NULL.
    u16 **pptOutContent;                ///< The pointer of the output result string. The output string is in UCS2 format without NULL terminated.
    ///< This parameter is only useful if this API is using as Sync API.
    ///< For synchronous using, this parameter shouldn't be NULL.
    ///< The Sync API will allocate the string memory, and set to this output parameter.
    ///< Vendor needs to Free the allocated memory. For asynchronous using, this parameter should be set as NULL.
    u16 *ptOutContentLen;               ///< The pointer of the output result string length. This parameter is only useful if this API is using as Sync API.
    ///< For synchronous using, this parameter shouldn't be NULL
} ven_editor_edit_info_t;

bool ven_editor_edit_ex(ven_editor_edit_info_t *ptEditInfo, ven_req_data_t *ptVenReq);

ven_editor_ret_t ven_editor_close(ven_req_data_t *ptVenReq);

/**
*  ven_editor_timeEdit
*  @brief    Request a time editor to get user input
*    Note: This function supports just asynchronous
*
*  @param  pInitValue    [in] The pointer of the init value of time editor.
*                               nSize;			:size of (ven_editor_time_format_t) for vision control
*                               hour;
*                               minute;
*                               second;
*                               If vendor assigned NULL value to pInitVaule, MMI will show default title time (current time).
*  @param  ptVenReq    [in] The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
*                               It is up to the user to free the memory allocated for the vendor request data.
*
*  @retval     VEN_EDITOR_RESULT_OK, Success to get Time input.
*                 VEN_EDITOR_RESULT_CANCEL, User cancel the request by self or some interrupt let the request be canceled 
*                 VEN_EDITOR_RESULT_ERROR, Some error in Request, reject this request
*                 VEN_EDITOR_BAD_PARAM, Request have bad param.
*  Response structure:
*
* typedef struct
* {
*     ven_editor_result_t rspType;
*     u8	nHour;
*     u8 nMinute;
*     u8 nSecond;
* }ven_editor_time_rsp_t;
*/

ven_editor_result_t ven_editor_timeEdit(ven_editor_time_format_t *pInitValue, ven_req_data_t *ptVenReq);

/**
*  ven_editor_dateEdit
*  @brief    Request a date editor to get user input 
*    Note: This function supports just asynchronous
*
*  @param  pInitValue    [in] The pointer of the init value of time editor.
*                               nSize;			:size of (ven_editor_date_format_t) for vision control
*                               nYear;
*                               nMonth;
*                               nDay;
*                               If vendor assigned NULL value to pInitVaule, MMI will show default title date (current date).
*  @param  ptVenReq    [in] The pointer of vendor request data. This api will not keep the pointer and will not free the memory.
*                               It is up to the user to free the memory allocated for the vendor request data.
*
*  @retval     VEN_EDITOR_RESULT_OK, Success to get Date input.
*                 VEN_EDITOR_RESULT_CANCEL, User cancel the request by self or some interrupt let the request be canceled 
*                 VEN_EDITOR_RESULT_ERROR, Some error in Request, reject this request
*                 VEN_EDITOR_BAD_PARAM, Request have bad param.
*  Response structure:
*
* typedef struct
* {
*     ven_editor_result_t rspType;
*     u16 nYear;
*     u8	nMonth;
*     u8 nDay;
} ven_editor_date_rsp_t;
*/
ven_editor_result_t ven_editor_dateEdit(ven_editor_date_format_t *pInitValue, ven_req_data_t *ptVenReq);
#endif //__VEN_EDITOR_DEFINE_H_
