/*
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */
/** 
 * @file ajms_common.h
 * AJSC Common Header
 */

#ifndef AJMS_COMMON_HEADER
#define AJMS_COMMON_HEADER

#ifdef __cplusplus
extern "C"{
#endif

#include "aj_type.h"


/*
 *    Interfaces listed in the group are used for general interface, 
 *    including these functionalities:
 *
 *    - Initialize/Finalize AJSC.
 *    .
 */
 
/** 
 * @addtogroup AJMS_Common_Constant
 * @par Include file 
 * \#include ajms_common.h
 * @{
 */

/** Maximum length for all "name" string. */
#define AJMS_MAX_ENTRY_NAME_LENGTH       (64)
/** Maximum length for all internal file path string. */
#define AJMS_MAX_ENTRY_URI_LENGTH        (64)
/** Maximum length for all java class name string. */
#define AJMS_MAX_ENTRY_CLASS_LENGTH      (256)
/** Maximum length for all url string. */
#define AJMS_MAX_ENTRY_URL_LENGTH        (256)

/** @} */

/** 
 * @addtogroup AJMS_Common_Error_Code
 * @par Include file 
 * \#include ajms_common.h
 * @{
 */
/** No error. */
#define AJMS_ERR_NONE                  (0)
/** File not found. */
#define AJMS_ERR_FILE_NOT_EXIST       (-1)
/** File already exists. */
#define AJMS_ERR_FILE_ALREADY_EXIST   (-2)
/** Invalid parameter. */
#define AJMS_ERR_INVALID_PARAMS       (-3)
/** An IO error occurred. */
#define AJMS_ERR_IO_ERROR             (-4)
/** ID not found. */
#define AJMS_ERR_ID_NOT_EXIST         (-5)
/** Invalid AJSC file found. */
#define AJMS_ERR_INVALID_AJMS_FILE    (-6)
/** File full. */
#define AJMS_ERR_FILE_FULL            (-7)
/** The entry already exists.*/
#define AJMS_ERR_ENTRY_ALREADY_EXIST  (-8)
/** Memory overflow. */
#define AJMS_ERR_MEMORY_OVERFLOW      (-9)
/** Application descriptor not found. */
#define AJMS_ERR_APPKEY_NOT_FOUND     (-10)
/** Invalid format. */
#define AJMS_ERR_INVALID_FORMAT       (-11)
/** Too long character string. */
#define AJMS_ERR_VALUE_TOO_LONG       (-12)
/** Not allowed. */
#define AJMS_ERR_NOT_ALLOWED          (-13)
/** The value is out of range. */
#define AJMS_ERR_OUT_OF_RANGE         (-14)
/** Not supported. */
#define AJMS_ERR_NOT_SUPPORT          (-15)
/** Wrong AJSC version */      
#define AJMS_ERR_WRONG_VERSION        (-16)
/** User canceled. */
#define AJMS_ERR_USER_CANCEL          (-20)
/** Invalid JAR size. */
#define AJMS_ERR_INVALID_JAR_SIZE     (-21)
/** An internal error occurred. */
#define AJMS_ERR_INTERNAL             (-100)

/** @} */

/** 
 * @addtogroup Trace_Output_ACI
 *
 * @par Include file 
 * \#include ajms_common.h
 * @{
 */

/**
 * The <i>TRACE</i> level designates the detailed tracing 
 * information, including entrance and exist of a function etc.
 */
#define AJMS_LOGGING_LEVEL_TRACE          (-1)

/** 
 * The <i>DEBUG</i> level designates fine-grained informational 
 * messages that are most useful to debug the Java execution environment.
 */
#define AJMS_LOGGING_LEVEL_DEBUG          (0)

/** 
 * The <i>INFO</i> level designates informational messages that 
 * highlight the progress of Java execution environment at 
 * coarse-grained level.
 *
 * Note that most logging messages output from Java execution environment
 * are of this type.
 */
#define AJMS_LOGGING_LEVEL_INFO           (1)

/**
 * The <i>WARN</i> level designates potentially harmful situations.
 */
#define AJMS_LOGGING_LEVEL_WARN           (2)

/**
 * The <i>ERROR</i> level designates error events that may 
 * still allow the Java execution environment to continue working.
 */
#define AJMS_LOGGING_LEVEL_ERR            (3)

/**
 * The function type for the callback asking whether or not a specific 
 *        type of debugging message should be output.
 * @param level
 *        The logging level. Possible values are as follows:
 *        - #AJMS_LOGGING_LEVEL_TRACE
 *        - #AJMS_LOGGING_LEVEL_DEBUG
 *        - #AJMS_LOGGING_LEVEL_INFO
 *        - #AJMS_LOGGING_LEVEL_WARN
 *        - #AJMS_LOGGING_LEVEL_ERR
 *        .
 * @param moduleName
 *        The module name of the output logging message
 * @param functionName
 *        The function name of the output logging message
 * @retval 1 to allow output messages of designated level.
 * @retval 0 to deny.
 * 
 * A callback function of this type can be passed to ajms_init(). 
 * The callback function is to be implemented by the device manufacturer. 
 *
 * The callback function is called by AJSC to ask whether or not a logging
 * message from Java execution environment should be output to the native
 * system by using kjava_sys_log_printOut().
 */
typedef AJ_BOOL (* AJMS_DEBUG_FilterCallback) (
                                    const AJ_S32 level,
                                    AJ_U8* moduleName, 
                                    AJ_U8* functionName);

/** @} */

/** 
 * @addtogroup AJMS_Common_Reader_Type
 * @par Include file 
 * \#include ajms_common.h
 * @{
 */

/**
 * The type of the function to read a byte stream.
 * @param buffer
 *        A pointer to the buffer for putting the data read.
 * @param offset
 *        The position to start reading. 
 *        It is designated as the offset (in bytes) from the beginning of the stream.
 * @param size
 *        The size in bytes to be read.
 * @retval "The number of bytes actually read"
 *         if the read operation succeeds. A value of 0 or more.
 * @retval "A negative value"
 *         if it fails.
 *
 * This is the type of the callback function to read JAD and JAR.
 *
 * If the size of read data is less than the requested size, AJSC retries
 * reading the remaining data by the function.
 * If the size of read data returned by this function is greater than the requested
 * size, AJSC treats this result as an error.
 * If the read data exceeds the buffer size, the behavior of AJSC is not guaranteed.
 */
typedef AJ_S32 (*AJMS_Reader)(void *buffer, AJ_S32 offset,  AJ_S32 size);

/** @} */

/*-----------------------------------------------------------------------------
 * Global Function(s) Prototype
 *----------------------------------------------------------------------------*/
 
/**
 * @addtogroup AJMS_INIT_FINI_ACI
 * @par Include file 
 * \#include ajms_common.h
 * @{
 */
/**
 * Initializes AJSC.
 * @param filter
 *        The address of a callback function that filters out logging messages.
 *        The native system can implement the callback function for 
 *        the customized logging message filtering. If this parameter
 *        is #AJ_NULL, all logging messages from Java execution environment will be output.
 *
 * @retval #AJMS_ERR_NONE
 *         if the function succeeds.
 * @retval #AJMS_ERR_IO_ERROR
 *         if the function fails to read AJSC files in the file system.
 * @retval #AJMS_ERR_FILE_NOT_EXIST
 *         if the ROMized AJSC files are not accessible. 
 *         Check PIK configuration files.
 * @retval #AJMS_ERR_WRONG_VERSION
 *         if the AJSC version is not consistent. 
 *         To check the AJSC version, call ajms_cfg_getProperty() passing #AJMS_LAYOUT_VERSION. 
 *         When this error occurs, the AMS should remove all the file inside the default Java folder and
 *         invoke ajms_init() again to create a new AJSC file base.
 * @retval #AJMS_ERR_INVALID_FORMAT
 *         if the AJSC file layout format is invalid.
 *         The storage system might have problems.
 * @retval #AJMS_ERR_INTERNAL
 *         if the function fails for any other reason.
 *
 * The AJSC initialization should be done when the handset is turned on. 
 * In other words, they should be called one and only once during a handset lifecycle.
 */
AJ_S32 ajms_init(AJMS_DEBUG_FilterCallback filter);

/**
 * Finalizes AJSC
 * @retval #AJMS_ERR_NONE 
 *         if the function succeeds.
 * @retval #AJMS_ERR_IO_ERROR
 *         if the function fails to read AJSC files in the file system.
 * @retval #AJMS_ERR_FILE_NOT_EXIST
 *         if the function fails because a ROMized AJSC file is missing.
 * @retval #AJMS_ERR_INTERNAL
 *         if the function fails for any other reason.
 *
 * The AJSC finalization should be done when the handset is turned off. 
 * In other words, they should be called one and only once during a handset lifecycle.
 */
AJ_S32 ajms_fini(void);


/** @} */

#ifdef __cplusplus
}
#endif 

#endif
