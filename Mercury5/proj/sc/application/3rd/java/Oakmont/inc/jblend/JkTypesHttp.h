/**
 * Copyright 2004 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkTypesHttp.h
 * HTTP/HTTPS Connection Data Types and Constants
 */
/**
 * @addtogroup Http_Connection_Data_Types
 * @{
 */
#ifndef ___NET_JK_TYPES_HTTP_H
#define ___NET_JK_TYPES_HTTP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 * HTTP/HTTPS request method GET
 */
#define     JK_HTTP_METHOD_GET      1

/**
 * HTTP/HTTPS request method HEAD
 */
#define     JK_HTTP_METHOD_HEAD     2

/**
 * HTTP/HTTPS request method POST
 */
#define     JK_HTTP_METHOD_POST     3

/**
 * Handle type for HTTP/HTTPS connection
 */
typedef JKHandle JKHttpHandle;

/**
 * Data structure type for storing HTTP/HTTPS header
 */
typedef struct JKT_Http_Header {
    /**
     * Field name (ASCII code) (not terminated by '\0')
     */
    JKSint8*   fieldName;

    /**
     * Field name length (in octets)
     */
    JKSint32   fieldNameLength;

    /**
     * Field value (ASCII code) (not terminated by '\0')
     */
    JKSint8*   fieldValue;

    /**
     * Field value length (in octets)
     */
    JKSint32   fieldValueLength;
} JKT_Http_Header;

#ifdef __cplusplus
}
#endif

#endif

/**
 * @} end of group
 */

