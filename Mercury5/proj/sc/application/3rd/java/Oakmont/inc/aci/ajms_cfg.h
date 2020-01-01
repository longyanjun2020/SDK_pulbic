/*
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */

/**
 *  @file ajms_cfg.h
 */

/*
 *  
 *  Interfaces listed in the group are used for AJSC configuration, 
 *  including these functionalities:
 *       - Set HTTP implementation by profile identifier.
 *       - Set HTTP user agent.
 *       - Set HTTP proxy.
 *       - Get AJSC configuration
 *       .
 */

#ifndef AJMS_CFG_HEADER
#define AJMS_CFG_HEADER

#ifdef __cplusplus
extern "C"{
#endif

#include <aj_type.h>

/** 
 * @addtogroup HTTP_Config_ACI
 * An interface for configuring the HTTP communication processing of AJSC.
 * This interface is implemented in AJSC.
 *
 * @par Include file 
 * \#include ajms_cfg.h
 * @{
 */

/**
 * @name HTTP Implementation Type
 * @{
 * The native system can choose how the HTTP communication feature is performed, by calling 
 * ajms_cfg_setHttpImpl() passing one of the following values.
 */
/** 
 * The HTTP communication is disabled.
 */
#define AJSC_HTTP_PROFILE_DISABLED  0
/** 
 * The HTTP communication is performed using the default interface.
 * When the device manufacturer has decided to implement @ref Socket_KSI, the default is @ref Socket_KSI.
 * Otherwise, the default is @ref HTTP_KSI.
 */
#define AJSC_HTTP_PROFILE_DEFAULT   1
/** 
 * The HTTP communication is performed using @ref HTTP_KSI.
 */
#define AJSC_HTTP_PROFILE_EXTLIB    2
/** 
 * The HTTP communication is performed using @ref kjava_sys_serial.\ Note that this is for TCK use only.
 */
#define AJSC_HTTP_PROFILE_SERIAL    3
/** @} */

/**
 * @name Proxy Descriptor Type
 * @{
 */
/** 
 * The proxy descriptor type: Basic. 
 */
#define AJMS_PROXY_DESCRIPTOR_TYPE_BASIC      0
/** 
 * The proxy descriptor type: Advanced.\ This is reserved for future use.
 */
#define AJMS_PROXY_DESCRIPTOR_TYPE_ADVANCED   1
/** @} */
/** @} */

/** 
 * @addtogroup AJMS_Configuration_Query_ACI 
 * @par Include file 
 * \#include ajms_cfg.h
 * @{
 */
/**
 * The request identifier for getting the Java ME configuration supported by AJSC.
 * This is for use with ajms_cfg_getProperty().
 */
#define AJMS_SUPPORTED_CONFIGURATION        (0)

/**
 * The request identifier for getting the Java profiles supported by AJSC.
 * This is for use with ajms_cfg_getProperty().
 */
#define AJMS_SUPPORTED_PROFILE              (1)

/**
 * The request identifier for querying whether or not the AJSC supports trusted MIDlets.
 * This is for use with ajms_cfg_getProperty().
 */
#define AJMS_SUPPORT_TRUSTED_MIDLET         (10)
/**
 * The request identifier for querying whether or not the AJSC supports the category feature of the AJSC Java application repository.
 * This is for use with ajms_cfg_getProperty().
 */
#define AJMS_SUPPORT_CATEGORY               (11)

/**
 * The request identifier for querying the AJSC file layout version.
 * The fie layout version can be changed only when a new feature is added.
 *
 * For a different version, the AJSC Java application repository will not be compatible and therefore the native system 
 * should delete all the files inside the Java folder and re-initialize AJSC with ajms_init().
 *
 * This is for use with ajms_cfg_getProperty().
 */
#define AJMS_LAYOUT_VERSION                 (13)
/** @} */

/** 
 * @addtogroup HTTP_Config_ACI
 * @{
 */

/**
 * This is reserved for future use.
 * @internal
 *        The function type for querying the proxy information of a specified host.
 * @param remoteAddr
 *        A pointer to the string holding the remote host address.
 * @param remotePort
 *        The destination port of the remote host.
 * @param proxyAddr
 *        A pointer to the buffer for putting the string representing the proxy server address.
 * @param proxyAddrLength
 *        The size of the buffer indicated by <i>proxyAddr</i>.
 * @param proxyPort
 *        A pointer to the buffer for putting the proxy server port.
 *
 * @retval #AJ_SUCCES  if the function succeeds.
 * @retval #AJ_FAILURE if the function fails.
 *
 * Based on the remote address and port indicated by <i>remoteAddr</i> and
 * <i>remotePort</i>, store the information of an appropriate proxy server
 * in the buffers indicated by <i>proxyAddr</i> and <i>proxyPort</i>.
 */
typedef AJ_RESULT (* AJMS_DynamicProxyHandler) (
                        AJ_U8       *remoteAddr,
                        const AJ_S32 remotePort,
                        AJ_U8       *proxyAddr,
                        const AJ_S32 proxyAddrLength,
                        AJ_S32      *proxyPort);

/**
 * The structure type for specifying the proxy information for an HTTP connection controlled by Java application.
 */
typedef struct _AJMS_ProxyDescriptorTag
{
    /**
     * The type of this proxy descriptor.
     * #AJMS_PROXY_DESCRIPTOR_TYPE_BASIC should be set.
     * <!--
     * There are 2 types of proxy descriptors:
     * - #AJMS_PROXY_DESCRIPTOR_TYPE_BASIC
     * - #AJMS_PROXY_DESCRIPTOR_TYPE_ADVANCED
     * .
     *
     * If <i>type</i> is #AJMS_PROXY_DESCRIPTOR_TYPE_BASIC,
     * the HTTP connection controlled by Java application will use fixed proxy server address and port.
     * In this case only the <i>serverAddress</i> and <i>serverPort</i> members should be filled.
     *
     * If <i>type</i> is #AJMS_PROXY_DESCRIPTOR_TYPE_ADVANCED,
     * the HTTP connection will use the <i>dynamicProxyHandler</i> callback function 
     * to query the preferred proxy server based on the given remote server information of the current HTTP connection.
     * In this case only <i>dynamicProxyHandler</i> should be filled.
     * -->
     */
    AJ_S32                      type;
    /**
     * A pointer to the NUL-terminated string representing the proxy server address.
     */
    AJ_U8*                 serverAddress;
    /**
     * The proxy server port number.
     */
    AJ_S32                      serverPort;
    /**
     * This is reserved for future use.\ #AJ_NULL should be set.
     * @internal
     * The address of the callback function to query proxy server information dynamically.
     */
    AJMS_DynamicProxyHandler    dynamicProxyHandler;
}
AJMS_ProxyDescriptor;


/**
 *        Sets the HTTP implementation adapter by HTTP profile identifier.
 * @param impl_id 
 *        The HTTP profile identifier.
 *        Possible values are as follows:
 *        - #AJSC_HTTP_PROFILE_DISABLED
 *        - #AJSC_HTTP_PROFILE_DEFAULT
 *        - #AJSC_HTTP_PROFILE_EXTLIB
 *        - #AJSC_HTTP_PROFILE_SERIAL
 *        .
 * @retval #AJMS_ERR_NONE 
 *         if the function succeeds.
 * @retval #AJMS_ERR_ID_NOT_EXIST 
 *         if the function fails because an invalid identifier is passed in <i>impl_id</i>.
 *
 * Use this function to change the HTTP profile. 
 * The function should be called before starting a Java application.
 * Setting made by this function overwrites the existing setting and remain in effect across Java sessions.
 *
 * Use of this function is optional.
 * When this function is not called, the {@link #AJSC_HTTP_PROFILE_DEFAULT default} setting is used.
 */
AJ_INT ajms_cfg_setHttpImpl(AJ_INT impl_id);

/**
 *        Sets the user-agent for HTTP connections used by the Java application.
 * @param userAgent
 *        A pointer to the UTF-8 encoded NUL terminated string containing the User-Agent header value.
 *
 * @retval #AJMS_ERR_NONE
 *         The user agent was set normally.
 * @retval #AJMS_ERR_INTERNAL
 *         Failed to set user agent.
 *
 * Use this function to set the user agent header for use by HTTP connections.
 * The native system should call this function before starting a Java application. 
 * When the Java application finishes, the user agent information is reset.
 * Namely, the user agent should be set every time before starting a Java application. 
 */
AJ_S32 ajms_cfg_setHttpUserAgent(AJ_U8* userAgent);

/**
 *        Sets the proxy information for HTTP connections used by the Java application.
 * @param descriptor_p
 *        A pointer to a ProxyDescriptor structure holding the proxy information.
 *
 * @retval #AJMS_ERR_NONE
 *         if the function succeeds.
 * @retval #AJMS_ERR_INTERNAL
 *         if the function fails in setting proxy information. 
 *
 * Use this function to set proxy information for use by HTTP connections.
 * The native system should call this function before starting a Java application. 
 * When the Java application finishes, the proxy information is reset.
 * Namely, the proxy information should be set every time before starting a Java application.
 */
AJ_S32 ajms_cfg_setHttpProxy(AJMS_ProxyDescriptor *descriptor_p);

/** @} */

/** 
 * @addtogroup AJMS_Configuration_Query_ACI 
 * @{
 */

/**
 *        Gets a JVM property string.
 * @param id
 *        The identifier indicating the property to be acquired.
 *        One of the following values can be passed.
 *         - #AJMS_SUPPORTED_CONFIGURATION<br>
 *           If this value is passed, this function returns a sting indicating supported Java ME configuration.
 *           In the case of the AJSC described in this document, "CLDC-1.0" or "CLDC-1.1" is returned.
 *           Note that more than one configuration cannot be supported at the same time. 
 *         - #AJMS_SUPPORTED_PROFILE<br>
 *           If this value is passed, this function returns a sting indicating supported Java profiles.
 *           If more than one profile is supported, the return string lists each profile separated by a blank space.
 *           In the case of the AJSC described in this document, "MIDP-2.0" or "MIDP-1.0" is returned.
 *         - #AJMS_SUPPORT_TRUSTED_MIDLET<br>
 *           If this value is passed, this function returns a sting indicating whether or not the AJSC supports trusted MIDlet.
 *           When supported, "support" is returned; otherwise "non-support" is returned.
 *         - #AJMS_SUPPORT_CATEGORY<br>
 *           If this value is passed, this function returns a sting indicating whether or not the AJSC supports the category feature 
 *           of the AJSC Java application repository.
 *           When supported, "support" is returned; otherwise "non-support" is returned.
 *         - #AJMS_LAYOUT_VERSION<br>
 *           If this value is passed, this function returns a NUL terminated ASCII sting indicating the AJSC file layout version.
 *         .
 *  @param errorCode
 *         A pointer to the buffer for receiving the error code indicating the function processing result.
 *         One of the following values is put in the buffer.
 *         - #AJMS_ERR_NONE<br>
 *           if the function succeeds.
 *         - #AJMS_ERR_ID_NOT_EXIST<br>
 *           if an illegal identifier is passed.
 *         - #AJMS_ERR_FILE_NOT_EXIST<br>
 *           if the default index file is not found in the AJSC code image.
 *           This can happen only when #AJMS_LAYOUT_VERSION is passed in <i>id</i>.
 *           Refer to @ref page_pik for details of the ROMized AJSC files.
 *         - #AJMS_ERR_INVALID_FORMAT<br>
 *           if the default index file is not formatted correctly.
 *           This can happen only when #AJMS_LAYOUT_VERSION is passed in <i>id</i>.
 *           Refer to @ref page_pik for details of the ROMized AJSC files.
 *         - #AJMS_ERR_INTERNAL<br>
 *           if an internal error occurs.
 *         .
 *  @return
 *         A pointer to the NUL-terminated ASCII string for the designated property identifier <i>id</i>.
 *         This pointer remains valid until ajms_fini() is called.
 */
const AJ_U8 *ajms_cfg_getProperty(AJ_S32 id, AJ_S32 *errorCode);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* KJAVA_EIME_HEADER */
