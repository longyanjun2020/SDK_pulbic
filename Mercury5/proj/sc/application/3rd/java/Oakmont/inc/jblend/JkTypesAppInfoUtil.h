/*
 * Copyright 2003,2007 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkTypesAppInfoUtil.h
 * Application Information Analysis JBI Error Codes and Event Types
 */
/**
 * @addtogroup Application_Information_Analysis_JBI
 * @{
 */
#ifndef ___JKTYPES_APPINFO_UTIL_H
#define ___JKTYPES_APPINFO_UTIL_H

#include "JkTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *  Normal completion
 */
#define JK_AMS_OK                                   (0)

/**
 *  Out of memory
 */
#define JK_AMS_OUT_OF_MEMORY_ERROR                  (-1)

/**
 *  I/O error
 */
#define JK_AMS_IO_ERROR                             (-2)

/**
 *  Illegal argument
 */
#define JK_AMS_ILLEGAL_ARGUMENT_ERROR               (-3)

/**
 *  Format error detected in application descriptor file (JAD file) or manifest file
 */
#define JK_AMS_ILLEGAL_FORMAT_ERROR                 (-4)

/**
 *  Invalid JAR file size
 */
#define JK_AMS_INVALID_JARSIZE_ERROR                (-5)

/**
 *  No MIDlet-Name attribute entry found
 */
#define JK_AMS_NO_MIDLET_NAME_ERROR                 (-6)

/**
 *  No MIDlet-Vendor attribute entry found
 */
#define JK_AMS_NO_MIDLET_VENDOR_ERROR               (-7)

/**
 *  No MIDlet-Version attribute entry found
 */
#define JK_AMS_NO_MIDLET_VERSION_ERROR              (-8)

/**
 *  No MIDlet-1 attribute entry found
 */
#define JK_AMS_NO_MIDLET_1_ERROR                    (-9)

/**
 *  No MicroEdition-Profile attribute entry found
 */
#define JK_AMS_NO_MICROEDITION_PROFILE_ERROR        (-10)

/**
 *  No MicroEdition-Configuration attribute entry found
 */
#define JK_AMS_NO_MICROEDITION_CONFIGURATION_ERROR  (-11)

/**
 *  No MIDlet-Jar-URL attribute entry found
 */
#define JK_AMS_NO_MIDLET_JAR_URL_ERROR              (-12)

/**
 *  No MIDlet-Jar-Size attribute entry found
 */
#define JK_AMS_NO_MIDLET_JAR_SIZE_ERROR             (-13)

/**
 *  Different MIDlet-Name values in JAD file and manifest file
 */
#define JK_AMS_MIDLET_NAME_NOT_IDENTICAL_ERROR      (-14)

/**
 *  Different  MIDlet-Vendor values in JAD file and manifest file
 */
#define JK_AMS_MIDLET_VENDOR_NOT_IDENTICAL_ERROR    (-15)

/**
 *  Different  MIDlet-Version values in JAD file and manifest file
 */
#define JK_AMS_MIDLET_VERSION_NOT_IDENTICAL_ERROR   (-16)

/**
 *  No such attribute
 */
#define JK_AMS_NO_SUCH_ENTRY_ERROR                  (-17)

/**
 *  Values in JAD and manifest files do not match
 */
#define JK_AMS_NOT_IDENTICAL_VALUES_ERROR           (-18)

/**
 *   Unknown identifier
 */
#define JK_AMS_UNKNOWN_ID_ERROR                     (-19)

/**
 *  Value overflow
 */
#define JK_AMS_OVERFLOW_ERROR                       (-20)

/**
 *  Character not found
 */
#define JK_AMS_CHAR_NOT_FOUND_ERROR                 (-21)

/**
 *  Length (in bytes) of the value exceeds the limit specified in MIDP
 */
#define JK_AMS_INVALID_VALUE_LENGTH_ERROR           (-22)

/**
 *  A configuration not supported by JBlend is designated for
 *  the JAD or manifest file MicroEdition-Configuration attribute
 */
#define JK_AMS_CONFIGURATION_NOT_SUPPORTED_ERROR    (-23)

/**
 *  A profile not supported by JBlend is designated for
 *  the JAD or manifest file MicroEdition-Profile attribute.
 */
#define JK_AMS_PROFILE_NOT_SUPPORTED_ERROR          (-24)


/**
 *  A value not supported by JBlend is designated for
 *  the JAD or manifest file Runtime-Execution-Environment attribute.
 */
#define JK_AMS_RUNTIME_EXECUTION_ENVIRONMENT_NOT_SUPPORTED_ERROR    (-25)

/**
 *  The value set for the Runtime-Execution-Environment attribute in the JAD file or manifest file does 
 *  not match the value set for the MicroEdition-Configuration attribute.
 */
#define JK_AMS_ENVIRONMENT_CONFIGURATION_MISMATCH_ERROR    (-26)



/**
 *  MIDlet-Jar-URL attribute
 */
#define JK_AMS_ATTR_ID_JAR_URL         (0)

/**
 *  MIDlet-Jar-Size attribute
 */
#define JK_AMS_ATTR_ID_JAR_SIZE        (1)

/**
 *  MIDlet-Name attribute
 */
#define JK_AMS_ATTR_ID_NAME            (2)

/**
 *  MIDlet-Version attribute
 */
#define JK_AMS_ATTR_ID_VERSION         (3)

/**
 *  MIDlet-Vendor attribute
 */
#define JK_AMS_ATTR_ID_VENDOR          (4)

/**
 *  MicroEdition-Profile attribute
 */
#define JK_AMS_ATTR_ID_PROFILE         (5)

/**
 *  MicroEdition-Configuration attribute
 */
#define JK_AMS_ATTR_ID_CONFIGURATION   (6)

/**
 *  MIDlet-Description attribute
 */
#define JK_AMS_ATTR_ID_DESCRIPTION     (7)

/**
 *  MIDlet-Icon attribute
 */
#define JK_AMS_ATTR_ID_ICON            (8)

/**
 *  MIDlet-Info-URL attribute
 */
#define JK_AMS_ATTR_ID_INFO_URL        (9)

/**
 *  MIDlet-Data-Size attribute
 */
#define JK_AMS_ATTR_ID_DATA_SIZE       (10)

/**
 *  MIDlet-Permissions attribute
 */
#define JK_AMS_ATTR_ID_PERMISSIONS     (11)

/**
 *  MIDlet-Permissions-Opt attribute
 */
#define JK_AMS_ATTR_ID_PERMISSIONS_OPT (12)

/**
 *  MIDlet-Install-Notify attribute
 */
#define JK_AMS_ATTR_ID_INSTALL_NOTIFY  (13)

/**
 *  MIDlet-Delete-Notify attribute
 */
#define JK_AMS_ATTR_ID_DELETE_NOTIFY   (14)

/**
 *  MIDlet-Delete-Confirm attribute
 */
#define JK_AMS_ATTR_ID_DELETE_CONFIRM  (15)

/**
 *  MIDlet-Jar-RSA-SHA1 attribute
 */
#define JK_AMS_ATTR_ID_RSA_SHA1        (16)


/**
 *  Runtime-Execution-Environment attribute
 */
#define JK_AMS_ATTR_ID_RUNTIME_EXECUTION_ENVIRONMENT    (17)


/**
 *  Maximum value of 32-bit signed integer
 */
#define JK_AMS_INT_MAX INT_MAX

/**
 *  Minimum value of 32-bit signed integer
 */
#define JK_AMS_INT_MIN INT_MIN

/**
 *  Data type of handle identifying the application information analysis functions environment
 */
typedef JKHandle JKAmsEnvHandle;

/**
 *  Data type of handle identifying the application descriptor file (JAD file),
 *  manifest file, or data merging the two
 */
typedef JKHandle JKAmsDescHandle;

/**
 *  Data type of handle identifying the Java application JAR file
 */
typedef JKHandle JKAmsJarHandle;

/**
 *  The type of the stream function for reading byte data
 *  @param buffer
 *         A pointer to the buffer for storing read data
 *  @param offset
 *         The position from which to read, designated as the offset (in bytes) from
 *         the head.
 *  @param size
 *         The size (in bytes) to be read.
 *  @return
 *         If the read operation succeeds, return the number of bytes (0 or more)
 *         actually read.<br>
 *         If it failed, return a negative value.
 *
 *  This is the type of the callback function used by JBlend to read the
 *  application descriptor (JAD file) data and JAR file.
 *
 *  If the size of read data is less than the requested size, JBlend retries
 *  reading the remaining data.
 *  If the size of read data returned by this function is greater than the requested
 *  size, JBlend treats this result as an error.
 *  If the written data exceeds the buffer size, the behavior is not guaranteed.
 * @see AamsJadOpen() @see AamsJarOpen()
 */
typedef JKSint32(*JKAmsAppInfoStreamReader) (void *buffer, JKSint32 offset,
                                             JKSint32 size);

#ifdef __cplusplus
}
#endif

#endif /* ___AAMS_APPINFO_UTIL_TYPES_H */
