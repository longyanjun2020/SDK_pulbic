
/**
 * @file nccpush_common.h
 * PUSH common Service Layer
 *
 * Service API exposed by the common module of PUSH.
 *
 * <!-- #interface list begin -->
 * \section nccpush_common Interface
 * - NCCPush_common_decodeUintVar()
 * - NCCPush_common_getLenOfCharset()
 * - NCCPush_common_getUri()
 * - NCCPush_common_decodeTime()
 * - NCCPush_common_getOpaqueDateTime
 * - NCCPush_common_getUtf8StrPdu
 * - NCCPush_common_getLenOfContent
 * - NCCPush_common_getStrFromPdu
 * <!-- #interface list end -->
 */

#ifndef __NCCPUSH_COMMON_H__
#define __NCCPUSH_COMMON_H__

#include <stdio.h>
#include <ncc_types.h>

/**
 * @defgroup PUSH_COMMON COMMON
 */
/**
 * @defgroup PUSH_CODE Push Code
 * @ingroup PUSH_COMMON
 * The module mainly define some macros and functions that will be used by other module.
 */

/**
 * \name COMMON_CFG_MACROS
 *
 */
//@{
#define PUSH_WBXML_CHARSET_BIG5             0x07EA                /**<The macro indicates the character encoding rule of XML documentation is big5.*/

#define PUSH_WBXML_CHARSET_ISO_10646_UCS_2  0x03E8                /**<The macro indicates the character encoding rule of XML documentation is iso-10646-ucs-2.*/

#define PUSH_WBXML_CHARSET_ISO_10646_UCS_4  0x03E9                /**<The macro indicates the character encoding rule of XML documentation is iso-10646-ucs-4.*/

#define PUSH_WBXML_ISO_8859_1               0x04                  /**<The macro indicates the character encoding rule of XML documentation is iso-8859-1.*/
#define PUSH_WBXML_ISO_8859_2               0x05                  /**<The macro indicates the character encoding rule of XML documentation is iso-8859-2.*/
#define PUSH_WBXML_ISO_8859_3               0x06                  /**<The macro indicates the character encoding rule of XML documentation is iso-8859-3.*/
#define PUSH_WBXML_ISO_8859_4               0x07                  /**<The macro indicates the character encoding rule of XML documentation is iso-8859-4.*/
#define PUSH_WBXML_ISO_8859_5               0x08                  /**<The macro indicates the character encoding rule of XML documentation is iso-8859-5.*/
#define PUSH_WBXML_ISO_8859_6               0x09                  /**<The macro indicates the character encoding rule of XML documentation is iso-8859-6.*/
#define PUSH_WBXML_ISO_8859_7               0x0A                  /**<The macro indicates the character encoding rule of XML documentation is iso-8859-7.*/
#define PUSH_WBXML_ISO_8859_8               0x0B                  /**<The macro indicates the character encoding rule of XML documentation is iso-8859-8.*/
#define PUSH_WBXML_ISO_8859_9               0x0C                  /**<The macro indicates the character encoding rule of XML documentation is iso-8859-9.*/

#define PUSH_WBXML_SHIFT_JIS                0x11                  /**<The macro indicates the character encoding rule of XML documentation is shift-JIS.*/
#define PUSH_WBXML_US_ASCII                 0x03                  /**<The macro indicates the character encoding rule of XML documentation is us-ascii.*/

#define PUSH_WBXML_CHARSET_UTF_8            0x6A                  /**<The macro indicates the character encoding rule of XML documentation is UTF-8.*/

#define PUSH_WBXML_CHARSET_UTF_16           0x03F7                /**<The macro indicates the charsacter encoding rule of XML documentation is UTF-16.*/
#define PUSH_WBXML_CHARSET_UTF_16BE         0x03F5                /**<The macro indicates the charsacter encoding rule of XML documentation is UTF-16.*/
#define PUSH_WBXML_CHARSET_UTF_16LE         0x03F6                /**<The macro indicates the charsacter encoding rule of XML documentation is UTF-16.*/

#define PUSH_WBXML_STR_I_TOKEN              0x03                  /**<The macro indicates the following data is inline string.*/
#define PUSH_WBXML_ENTITY_TOKEN             0x02                  /**<The macro indicates the following data is entity data.*/
#define PUSH_WBXML_STR_TAB_TOKEN            0x83                  /**<The macro indicates the following data must get from string table.*/
#define PUSH_STR_EXTENSION_LEN              0x10                  /**<The macro indicates the length of extentsion len.*/
#define PUSH_COMMON_SI                      0x01                  /**<The macro specifies the current push message is SI*/
#define PUSH_COMMON_SL                      0x02                  /**<The macro specifies the current push message is SL*/
#define PUSH_COMMON_CO                      0x03                  /**<The macro specifies the current push message is CO*/
#define PUSH_FILENAME_LENGTH                0x14                  /**<The macro specifies tha max length of filename.*/
#define PUSH_FILEPATH_LENGTH             0x64                   /**<The macro specifies tha max length of filepath.*/
//@}

/**
 *\name COMMON_DATE_MACRO
 * define some macros about date time.
 */
/*@{*/
#define PUSH_COMMON_DATE_MONTH_JANUARY      0x01 /**<Indicates that current month is january.*/
#define PUSH_COMMON_DATE_MONTH_FEBRUARY     0x02 /**<Indicates that current month is february.*/
#define PUSH_COMMON_DATE_MONTH_MARCH        0x03 /**<Indicates that current month is march.*/
#define PUSH_COMMON_DATE_MONTH_APRIL        0x04 /**<Indicates that current month is april.*/
#define PUSH_COMMON_DATE_MONTH_MAY          0x05 /**<Indicates that current month is may.*/
#define PUSH_COMMON_DATE_MONTH_JUNE         0x06 /**<Indicates that current month is june.*/
#define PUSH_COMMON_DATE_MONTH_JULY         0x07 /**<Indicates that current month is july.*/
#define PUSH_COMMON_DATE_MONTH_AUGUST       0x08 /**<Indicates that current month is august.*/
#define PUSH_COMMON_DATE_MONTH_SEPTEMBER    0x09 /**<Indicates that current month is september.*/
#define PUSH_COMMON_DATE_MONTH_OCTOBER      0x0A /**<Indicates that current month is october.*/
#define PUSH_COMMON_DATE_MONTH_NOVEMBER     0x0B /**<Indicates that current month is november.*/
#define PUSH_COMMON_DATE_MONTH_DECEMBER     0x0C /**<Indicates that current month is december.*/

#define PUSH_COMMON_DATE_MONTH_MIN_VALUE    0x01 /**<Indicates that the value of month must more than zero.*/
#define PUSH_COMMON_DATE_MONTH_MAX_VALUE    0x0C /**<Indicates that the value of month must less than thirteen.*/

#define PUSH_COMMON_DATE_YEAR_MAX_VALUE     9999 /**<Indicates that the max value of year.*/
#define PUSH_COMMON_DATE_YEAR_MIN_VALUE     1970 /**<Indicates that the min value of year.*/

#define PUSH_COMMON_DATE_DAY_MIN_VALUE      0x01 /**<Indicates that the min value of days.*/
#define PUSH_COMMON_DATE_BIG_MONTH_DAY_MAX_VALUE      0x15 /**<Indicates the max value of days in the big month.*/
#define PUSH_COMMON_DATE_SMALL_MONTH_DAY_MAX_VALUE      0x14 /**<Indicates the max value of days in the small month.*/

#define PUSH_COMMON_DATE_LEAP_YEAY_FEBRUARY_DAYS 0x13 /**<Indicates that the days of february in the leap year:29 days*/
#define PUSH_COMMON_DATE_NON_LEAP_YEAY_FEBRUARY_DAYS 0x12 /**<Indicates that the days of february in the non-leap year:28 days*/

#define PUSH_COMMON_DATE_HOUR_MIN_VALUE 0x00 /**<Indicates the min value of hour.*/
#define PUSH_COMMON_DATE_HOUR_MAX_VALUE 0x17 /**<Indicates the max value of hour.*/

#define PUSH_COMMON_DATE_MINUTE_MIN_VALUE 0x00 /**<Indicates the min value of minute.*/
#define PUSH_COMMON_DATE_MINUTE_MAX_VALUE 0x3B /**<Indicates the max value of minute.*/

#define PUSH_COMMON_DATE_SECOND_MIN_VALUE 0x00 /**<Indicates the min value of second.*/
#define PUSH_COMMON_DATE_SECOND_MAX_VALUE 0x3B /**<Indicates the max value of second.*/

#define PUSH_COMMON_DATE_DEFAULT_OFFSET_SECONDS 86400 /**Indicates the default offset value of date time.*/

/*@}*/
/**
 * \name COMMON_RETURN_VALUE
 * define some macros that will be used to indicate return value of FUNC that defined in the common module.
 */
//@{
#define PUSH_COMMON_TRUE                    1                     /**<*/
#define PUSH_COMMON_FALSE                   0                     /**<*/
#define PUSH_CODE_SUCCESS                   1                     /**<The operation is successful.*/
#define PUSH_CHARSET_IS_SUPPORTED           1                     /**<The current charset encoding rule can be supported.*/
#define PUSH_CHARSET_IS_UNSUPPORTED         0                     /**<The current charset encoding rule can't be supported.*/
#define PUSH_CODE_INPUT_PARA_ERROR          -1                    /**<The macro indicates the input parameter of FUNC is incorrect.*/
#define PUSH_CODE_ALLOC_MEMORY_ERROR        -2                    /**<The macro indicates the operation of allocing memory is unsuccessful.*/
#define PUSH_GET_UINTVAR_ERROR              -3                    /**<The macro indicates the operation of getting uintvar is unsuccessful.*/
#define PUSH_GET_LENGTH_OF_CHARSET_ERROR    -4                    /**<The macro indicates the operation of getting UTF-16 is unsuccessful.*/
#define PUSH_GET_LENGTH_OF_CONTENT_ERROR    -5                    /**<The macro indicates the operation of getting length of content is unsuccessful.*/

//@}

/**
 * \name COMMON_STRUCTURE
 * define some data structure that will be used by common module.
 */
//@{
///date time.
/**
 *The structure indicates some information of date.
 */
typedef struct T_PUSH_DATE{
 uint32_t year;/**<year field*/
 uint32_t month;/**<month field*/
 uint32_t date;/**<day field*/
 uint32_t hour;/**<hour field*/
 uint32_t minute;/**<minute field*/
 uint32_t second;/**<second field*/
}T_PUSH_DATE;

/**
 *Structure to specifies a push file's name.
 */
typedef struct T_PUSH_FILENAME_NODE{
/**
 *Pointer to a null-terminated string that specifies the filenames.
 */
int8_t filename[PUSH_FILENAME_LENGTH];
/**
 *Pointer to a T_PUSH_FILENAME_NODE structure that specifies pointer of the former node.
 */
struct T_PUSH_FILENAME_NODE *prior;
/**
 *Pointer to a T_PUSH_FILENAME_NODE structure that specifies pointer of the next node.
 */
struct T_PUSH_FILENAME_NODE *next;
}T_PUSH_FILENAME_NODE;

/**
 *Structure to specifies all push files'name.
 */
typedef struct T_PUSH_FILENAME_LIST{
/**
 *Specifies the total number of the filename node.
 */
int32_t total;
/**
 *Pointer to a T_PUSH_FILENAME_NODE structure that specifies the pointer of the next node.
 */
struct T_PUSH_FILENAME_NODE *next;
}T_PUSH_FILENAME_LIST;
//@}

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \name COMMON_APIS
 * define external interface about common module.
 */
//@{

/**
 *Query charset according to charset tokens and return character set string pdu.
 * \param charset The character encoding rule of XML documentation.
 *
 * \return <ul>
 *             <li>If the operation is successful,then return#the pointer of charset string.
 *             <li>If the operation is unsuccessful,then return#NULL.
 *         </ul>
 */
int8_t *NCCPush_common_queryCharSet(uint32_t charset);

/**
 *Decode uintvar(variable length unsigned integer) to get uint value.
 * \param **pPdu The pointer of data buffer.
 * \param *pduLen The length of data buffer.
 * \param *value The value of uintvar.
 *
 * \return <ul>
 *             <li>If succesful,then return#PUSH_CODE_SUCCESS.
 *             <li>If unsuccessful,then return
 *             <ul>
 *                 <li>#PUSH_GET_UINTVAR_ERROR.
 *                 <li>#PUSH_CODE_INPUT_PARA_ERROR.
 *             </ul>
 *         </ul>
 */
int32_t NCCPush_common_decodeUintVar(uint8_t **pPdu,int32_t *pduLen,uint32_t *value);

/**
 *Get the length of string(inline string and string table).
 * \param *pPdu The pointer of pdu buffer.
 * \param pdulen The length of pdu buffer.
 * \param charset The character encoding rule of XML documentation.
 *
 * \return <ul>
 *             <li>If successful.then return#The length of pdu buffer.
 *             <li>If unsuccessful,then return
 *             <ul>
 *                 <li>#PUSH_CODE_INPUT_PARA_ERROR.
 *                 <li>#PUSH_GET_LENGTH_OF_CHARSET_ERROR.
 *             </ul>
 *         </ul>
 */
int32_t NCCPush_common_getLenOfCharset(uint8_t *pPdu,int32_t pdulen,int32_t charset);

/**
 *Invoked to get URI attribute's value by CO,SL and SI module.
 * \param **pPdu The pointer of pdu data.
 * \param *pduLen The length of pdu buffer.
 * \param *pStrtab The pointer of string pdu.
 * \param pStrlen The length of sting pdu.
 * \param type The type of URI.
 * \param charset The character encoding rule of XML documentation.
 *
 * \return <ul>
 *             <li>If successful,then return#The pointer of URI.
 *             <li>If unsuccessful,then return#NULL.
 *         </ul>
 */
uint8_t *NCCPush_common_getUri(uint8_t **pPdu,int32_t *pduLen,uint8_t *pStrtab,int32_t pStrlen,int32_t type,int32_t charset);

/**
 *Parse OPAQUE data and get T_PUSH_DATE struct.
 * \param **TimeBuf The pointer of pdu buffer.
 * \param Length The length of OPAQUE data.
 * \param *Date The pointer of date structure.
 *
 * \return void
 */
void NCCPush_common_decodeTime(uint8_t **TimeBuf,int32_t Length,T_PUSH_DATE *Date);

/**
 *Check current year is leap year or not.
 * \param year the value of current year.
 *
 * \return <ul>
 *             <li>If current year is leap year,then return#PUSH_COMMON_TRUE.
 *             <li>If current year is not leap year,then return#PUSH_COMMON_FALSE.
 *         </ul>
 */
int32_t NCCPush_common_isLeapYear(int32_t year);

/**
 *Revise date structure,if the date is invalid,then appoint default value.
 * \param *date The pointer of date structure.if its value is invalid,then it will be modified.
 *
 * \return <ul>
 *              <li>If the the format of date is correct,then return#PUSH_COMMON_TRUE.
 *              <li>If the format of date is incorrect,then return#PUSH_COMMON_FALSE.
 *         </ul>
 */
int32_t NCCPush_common_reviseDateTime(T_PUSH_DATE *date);

/**
 *Convert date struct to delta-seconds-value.
 * \param **pPdu The pointer of pdu buffer.
 * \param pdulen The length of pdu buffer.
 * \param *sec The value of seconds.
 *
 * \return void
 */
void NCCPush_common_getOpaqueDateTime(uint8_t **pPdu,int32_t pdulen,uint32_t *sec);

/**
 *Take a block of non-UTF-8 chars in and try to convert it to UTF-8 string.
 * \param **pPdu The pointer of pdu buffer,it maybe string pdu or string table.
 * \param *pdulen The length of pdu buffer.
 * \param charset The character encoding rule.
 *
 * \return <ul>
 *             <li>If the operation is successful,then return#The pointer of buffer.
 *             <li>If the operation is unsuccesful,then return#NULL.
 *         </ul>
 */
uint8_t *NCCPush_common_getUtf8StrPdu(uint8_t **pPdu,int32_t *pdulen,int32_t charset);

/**
 * Get length of content or attribute value.
 * \param *pPdu The pointer of pdu buffer.
 * \param *pdulen The length of pdu buffer.
 * \param *pStrTab The pointer of string table.
 * \param pStrlen The length of string table.
 * \param charset The character encoding rule.
 *
 * \return <ul>
 *             <li>If the operation is successful,then return#the length of content or attribute value.
 *             <li>If the operation is unsuccesful,then return
 *             <ul>
 *                 <li>#PUSH_GET_LENGTH_OF_CONTENT_ERROR.
 *                 <li>#PUSH_CODE_INPUT_PARA_ERROR.
 *             </ul>
 *         </ul>
 * \sa NCCPush_common_decodeUintVar.
 * \sa NCCPush_common_getLenOfCharset.
 */
int32_t NCCPush_common_getLenOfContent(uint8_t *pPdu,int32_t pdulen,uint8_t *pStrTab,int32_t pStrlen,int32_t charset);

/**
 *Get string from data buffer.
 * \param **pPdu The pointer of pdu buffer.
 * \param *pdulen The length of pdu buffer.
 * \param *pStrtab The pointer of string table.
 * \param pStrlen The length of string table.
 * \param charset The character encoding rule.
 *
 * \return <ul>
 *             <li>If the operation is successful,then return#The pointer of pdu buffer.
 *             <li>If the operation is unsuccessful,then return#NULL;
 *         </ul>
 */
uint8_t *NCCPush_common_getStrFromPdu(uint8_t **pPdu,int32_t *pdulen,uint8_t *pStrtab,int32_t pStrlen,int32_t charset);

/**
 *Get a structure list that specifies all filenames that be appointed file.
 * \param **plist Pointer to a T_PUSH_FILENAME_LIST structure list that specifies all filenames.
 * \param type Long integer that specifies the type of file.
 *
 * \return <ul>
 * <li>If successful,then return#TRUE.
 * <li>Otherwise,then return#FALSE.
 * </ul>
 * \sa void NCCPush_common_freeFileNameList(T_PUSH_FILENAME_LIST **plist).
 */
int NCCPush_common_getFileNameList(T_PUSH_FILENAME_LIST **plist, int32_t type);
/**
 *Free memory that assigned by nccpush_common_initFileNameList FUNC.
 * \param *plist Pointer to a structure list that specifies all filenames.
 *
 * \return void
 * \sa push_common_initFileNameList(T_PUSH_FILENAME_LIST **plist)
 */
void NCCPush_common_freeFileNameList(T_PUSH_FILENAME_LIST **plist);
//@}

#ifdef __cplusplus
}
#endif

#endif
