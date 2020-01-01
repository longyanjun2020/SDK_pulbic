/*
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */

#ifndef AJSC_HTTPLIB_HEADER
#define AJSC_HTTPLIB_HEADER

/**
 * @file ajsc_httplib.h
 * AJSC HTTP Service
 */

#ifdef __cplusplus
extern "C"{
#endif

#include <aj_type.h>

/*
 *  Interfaces listed in the group are used for HTTP service,
 *  including these functionalities:
 *   - Sending HTTP request and receive the HTTP respond.
 *   - Set id and password for proxy.
 *   - Set id and password for server.
 *   .
 */

/**
 * @addtogroup ajsc_httplib_aci_main
 * An interface for performing an HTTP/HTTPS transaction.
 * This interface is implemented in AJSC.
 *
 * @par Include file 
 * \#include ajsc_httplib.h
 * @{
 */

/**
 * @name HTTP/HTTPS Request Method
 * @{
 */
/**
 * HTTP/HTTPS request method GET.
 */
#define	AJSC_HTTPLIB_METHOD_GET     (1)
/**
 * HTTP/HTTPS request method HEAD.
 */
#define	AJSC_HTTPLIB_METHOD_HEAD    (2)
/**
 * HTTP/HTTPS request method POST.
 */
#define	AJSC_HTTPLIB_METHOD_POST    (3)
/** @} */

/**
 * @name HTTP/HTTPS Status
 * @{
 */
/**
 * HTTP/HTTPS status: Connection is closed normally.
 */
#define AJSC_HTTPLIB_SUCCESS        (1)
/**
 * HTTP/HTTPS status: Server authentication processing in progress.
 */
#define AJSC_HTTPLIB_GET_AUTH       (2)
/**
 * HTTP/HTTPS status: Data read.
 */
#define AJSC_HTTPLIB_DATA_READ      (3)
/**
 * HTTP/HTTPS status: Data written.
 */
#define AJSC_HTTPLIB_DATA_WRITTEN   (4)
/**
 * HTTP/HTTPS status: Error occurred during HTTP/HTTPS communication.
 */
#define AJSC_HTTPLIB_ERROR          (5)
/** @} */

/**
 * @name HTTP/HTTPS Error Code
 * @{
 */
/**
 * HTTP/HTTPS error code: Network is busy.
 */
#define AJSC_HTTPLIB_ERROR_BUSY                        (0x1001)
/**
 * HTTP/HTTPS error code: Failed to open an HTTP/HTTPS connection.
 */
#define AJSC_HTTPLIB_ERROR_INVALID_HANDLE              (0x1002)
/**
 * HTTP/HTTPS error code: Failed during HTTP/HTTPS I/O processing.
 */
#define AJSC_HTTPLIB_ERROR_PROCEED                     (0x1003)
/**
 * HTTP/HTTPS error code: I/O buffer is not enough.
 */
#define AJSC_HTTPLIB_ERROR_BUFF_TOO_SMALL              (0x1004)
/**
 * HTTP/HTTPS error code: The content length does not match HTTP/HTTPS header information.
 */
#define AJSC_HTTPLIB_ERROR_WRONG_CONTENT_LENGTH        (0x1005)
/**
 * HTTP/HTTPS error code: The HTTP/HTTPS URL is not valid.
 */
#define AJSC_HTTPLIB_ERROR_WRONG_URL                   (0x1006)
/**
 * HTTP/HTTPS error code: Invalid HTTP/HTTPS header format.
 */
#define AJSC_HTTPLIB_ERROR_HEADER_OFFSET               (0x1007)
/**
 * HTTP/HTTPS error code: No content length inside HTTP/HTTPS header.
 */
#define AJSC_HTTPLIB_ERROR_CONTENT_LENGTH_NOT_SPECIFY  (0x1008)
/**
 * HTTP/HTTPS error code: Invalid HTTP/HTTPS chunk.
 */
#define AJSC_HTTPLIB_ERROR_DECODE_CHUNKED              (0x1009)
/**
 * HTTP/HTTPS error code: Failed to get HTTP/HTTPS server authentication.
 */
#define AJSC_HTTPLIB_ERROR_NO_AUTHENTICATE_INFO        (0x1010)
/** @} */


/**
 * The data structure type for storing an HTTP/HTTPS header.
 */
typedef struct _AJSC_Http_Header
{
    /**
     * A pointer to the ASCII string representing field name.\ NUL termination not necessary.
     */
    AJ_S8*   fieldName;
    /**
     * The number of characters (excluding NUL termination) in the string indicated by <i>fieldName</i>.
     */
    AJ_S32   fieldNameLength;
    /**
     * A pointer to the ASCII string representing field value.\ NUL termination not necessary.
     */
    AJ_S8*   fieldValue;
    /**
     * The number of characters (excluding NUL termination) in the string indicated by <i>fieldValue</i>.
     */
    AJ_S32   fieldValueLength;
} AJSC_Http_Header;

/**
 *        The function type of the state notification callback for HTTP/HTTPS communication.
 * @param param
 *        The reference constant that has been passed to the function
 *        ajsc_http_sendRequest() via the parameter <i>param</i>.
 * @param states
 *        The current HTTP/HTTPS communication state.
 *        One of the following values is passed.
 *        - #AJSC_HTTPLIB_SUCCESS
 *        - #AJSC_HTTPLIB_GET_AUTH
 *        - #AJSC_HTTPLIB_DATA_READ
 *        - #AJSC_HTTPLIB_DATA_WRITTEN
 *        - #AJSC_HTTPLIB_ERROR
 *        .
 * @param value
 *        - When <i>states</i> is #AJSC_HTTPLIB_SUCCESS,
 *          <i>value</i> is 0.
 *        - When <i>states</i> is #AJSC_HTTPLIB_GET_AUTH,
 *          <i>value</i> is 0.
 *        - When <i>states</i> is #AJSC_HTTPLIB_DATA_READ,
 *          <i>value</i> is the total size in bytes of the data read during the HTTP/HTTPS communication.
 *        - When <i>states</i> is #AJSC_HTTPLIB_DATA_WRITTEN,
 *          <i>value</i> is the total size in bytes of the data written during the HTTP/HTTPS communication.
 *        - When <i>states</i> is #AJSC_HTTPLIB_ERROR,
 *          <i>value</i> indicates the error cause. One of the following values is passed:
 *          - #AJSC_HTTPLIB_ERROR_BUSY
 *          - #AJSC_HTTPLIB_ERROR_INVALID_HANDLE
 *          - #AJSC_HTTPLIB_ERROR_PROCEED
 *          - #AJSC_HTTPLIB_ERROR_BUFF_TOO_SMALL
 *          - #AJSC_HTTPLIB_ERROR_WRONG_CONTENT_LENGTH
 *          - #AJSC_HTTPLIB_ERROR_WRONG_URL
 *          - #AJSC_HTTPLIB_ERROR_HEADER_OFFSET
 *          - #AJSC_HTTPLIB_ERROR_CONTENT_LENGTH_NOT_SPECIFY
 *          - #AJSC_HTTPLIB_ERROR_DECODE_CHUNKED
 *          - #AJSC_HTTPLIB_ERROR_NO_AUTHENTICATE_INFO
 *          .
 *        .
 * @retval 1
 *         if the function succeeds.
 * @retval 0
 *         if the function fails.
 *
 * A callback function of this type should be passed to ajsc_http_sendRequest().
 * The callback function is to be implemented by the device manufacturer.
 * 
 * The callback function is called in the KVE thread context to indicate the 
 * result of the HTTP/HTTPS processing requested by ajsc_http_sendRequest().
 *
 * When, however, the <i>states</i> parameter is #AJSC_HTTPLIB_GET_AUTH, 
 * the communication processing is still in progress.
 * In this case the callback function should call ajsc_http_setServerNamePasswd() and
 * ajsc_http_setProxyNamePasswd() to provide the user ID and password, then return 1
 * to proceed authentication.
 * When the user ID and password are not available, return 0
 * to fail authentication.
 *
 */
typedef AJ_S32 (*AJSC_HTTPLIB_CALLBACK) (AJ_S32 param, AJ_S32 states, AJ_S32 value);

/**
 *        Sends an HTTP/HTTPS request and retrieve the respond via a callback function.
 * @param url
 *        A pointer to the UTF-8 encoded string representing the destination URL.
 * @param urlLength
 *        The length in bytes of the string indicated by <i>url</i>. 
 *        The value should not contain termination characters.
 * @param method
 *        The HTTP/HTTPS method. Pass one of the following values.
 *        - #AJSC_HTTPLIB_METHOD_GET
 *        - #AJSC_HTTPLIB_METHOD_POST
 *        - #AJSC_HTTPLIB_METHOD_HEAD
 *        .
 * @param headers
 *        A pointer to the array of AJSC_Http_Heade structures holding the HTTP/HTTPS requests.
 * @param headersLength
 *        The number of the elements of the array indicated by <i>headers</i>.
 * @param body
 *        A pointer to the buffer that contains the POST data.
 *        If <i>method</i> is #AJSC_HTTPLIB_METHOD_GET, this parameter should be #AJ_NULL.
 * @param bodyLength
 *        The length in bytes of the data indicated by <i>body</i>.
 * @param param
 *        A reference constant to receive in the <i>{@link #AJSC_HTTPLIB_CALLBACK callback}</i>
 *        function via the <i>param</i> parameter.
 * @param buf
 *        A pointer to the buffer used for read/write processing by HTTP/HTTPS communication.
 * @param bufSize
 *        The length in bytes of the buffer indicated by <i>buf</i>.
 * @param heapAddr
 *        A pointer to a huge heap for use by JVM.
 * @param heapSize
 *        The length in bytes of the heap indicated by <i>heapAddr</i>.
 * @param callback
 *        The address of the callback function to receive HTTP/HTTPS states.
 *
 * @retval  0 if the function succeeds.
 * @retval -1 if the function fails.
 * 
 * Use this function to perform an HTTP/HTTPS transaction.
 *
 * The HTTP/HTTPS communication processing is performed asynchronously in the KVE thread.
 * This function only sends a HTTP(S) transaction request to the KVE thread by using kjava_sys_sendAction() and returns to the caller.
 *
 */
AJ_S32 ajsc_http_sendRequest
(
            AJ_U8           *url,
            AJ_S32 	         urlLength,
            AJ_S32 	         method,
            AJSC_Http_Header headers[],
            AJ_S32           headersLength,
            AJ_U8           *body,
            AJ_S32           bodyLength,
            AJ_S32           param,
            AJ_U8           *buf,
            AJ_S32           bufSize,
            void            *heapAddr,
            AJ_S32 	         heapSize,
            AJSC_HTTPLIB_CALLBACK 	callback
);

/**
 *        Sets the user ID and password for HTTP/HTTPS server.
 * @param name
 *        A pointer to the UTF-8 string representing the user ID.
 * @param nameLength
 *        The length in bytes of the string indicated by <i>name</i>. 
 *        The value should not contain termination characters.
 * @param passwd
 *        A pointer to the UTF-8 string representing the user password.
 * @param passwdLength
 *        The length in bytes of the string indicated by <i>passwd</i>. 
 *        The value should not contain termination characters.
 * @retval 0
 *         if the function succeeds.
 * @retval -1
 *         if the function fails.
 *
 * Call this function when the {@link #AJSC_HTTPLIB_CALLBACK callback} function 
 * passed to ajsc_http_sendRequest() is called passing #AJSC_HTTPLIB_GET_AUTH in the <i>states</i> parameter. 
 * If the user ID and password are not available, fail the {@link #AJSC_HTTPLIB_CALLBACK callback} function
 * without calling this function.
 */
AJ_S32 ajsc_http_setServerNamePasswd(AJ_U8* name, AJ_S32 nameLength, AJ_U8* passwd, AJ_S32 passwdLength);

/**
 *        Sets the user ID and password for the proxy server.
 * @param name
 *        A pointer to the UTF-8 string representing the user ID.
 * @param nameLength
 *        The length in bytes of the string indicated by <i>name</i>. 
 *        The value should not contain termination characters.
 * @param passwd
 *        A pointer to the UTF-8 string representing the user password.
 * @param passwdLength
 *        The length in bytes of the string indicated by <i>passwd</i>. 
 *        The value should not contain termination characters.
 * @retval 0
 *         if the function succeeds.
 * @retval -1
 *         if the function fails.
 *
 * Call this function when the {@link #AJSC_HTTPLIB_CALLBACK callback} function 
 * passed to ajsc_http_sendRequest() is called passing #AJSC_HTTPLIB_GET_AUTH in the <i>states</i> parameter. 
 * If the user ID and password are not available, fail the {@link #AJSC_HTTPLIB_CALLBACK callback} function
 * without calling this function.
 */
AJ_S32 ajsc_http_setProxyNamePasswd(AJ_U8* name, AJ_S32 nameLength, AJ_U8* passwd, AJ_S32 passwdLength);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* AJSC_HTTPLIB_HEADER */
