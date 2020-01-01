/*
 * Copyright 2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file AMTck.h
 * TCK Support JBI
 */
/**
 * @addtogroup TCK_Support_JBI
 * @{
 */

#ifndef ___AMTCK_H
#define ___AMTCK_H

#include "JkTypes.h"
#include "JkTypesVmCtl.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 *         Gets the JAD file of next test from the TCK server.
 * @param  heapSize
 *         The size of the buffer designated by the <i>heapAddr</i> parameter.
 * @param  heapAddr
 *         A pointer to the buffer that is available to this function.
 * @param  appInfo
 *         A pointer to the #JKT_MIDP_Application structure containing information about 
 *         the TCK start-up application and about the buffers for holding the JAD file to be 
 *         downloaded from the TCK server.
 * @return The JAD file size if the JAD file acquisition succeeds. <br>
 *         A negative value if the operation failed.
 *
 * This function downloads a JAD file from the TCK server designated 
 * in the microJBlend-TckServer attribute in the JAD file given by 
 * <i>appInfo->jadAddr</i>, and writes it to the buffer indicated
 * in the structure member pointed to by <i>appInfo->tckparam</i>. 
 *
 *  The members in the JKT_MIDP_Application structure indicated by the 
 *  <i>appIinfo</i> parameter must be set as follows.
 * @htmlonly
 * <blockquote>
 * @endhtmlonly
 * <dl>
 *  <dt><b>jarAddr, jarRead, className</b></dt>
 *   <dd>#JK_NULL</dd>
 *  <dt><b>jarSize, classNameLen</b></dt>
 *   <dd>0</dd>
 *  <dt><b>jadAddr, jadRead, jadSize</b></dt>
 *   <dd>Information about the JAD file of the TCK start-up application.
 *       The JAD file must contain an entry for the microJBlend-TckServer attribute 
 *       designating the TCK server URL.
 *   </dd>
 *   <dd>Sample designation: <br> 
 * @htmlonly
 * microJBlend-TckServer: http://192.168.0.1:8088
 * @endhtmlonly
 *   </dd>
 *  <dt><b>trusted</b></dt>
 *   <dd>Any value
 *   </dd>
 *  <dt><b>tckparam</b></dt>
 *   <dd>A pointer to the T_AM_TCK structure giving information about the buffer 
 *    where AmTckGetDescriptor() is to store the downloaded JAD file. 
 *   </dd>
 * </dl> 
 * @htmlonly
 * </blockquote>
 * @endhtmlonly
 *
 * The following settings must be made in the members of the T_AM_TCK structure 
 * indicated by <i>appInfo->tckparam</i>.
 * @htmlonly
 * <blockquote>
 * <dl>
 *  <dt><b>jarBuf</b></dt>
 *   <dd>Any value
 *   </dd>
 *  <dt><b>jarLen</b></dt>
 *   <dd>Any value
 *   </dd>
 *  <dt><b>jarMax</b></dt>
 *   <dd>Any value
 *   </dd>
 *  <dt><b>infoBuf</b></dt>
 *   <dd>A pointer to the buffer where AmTckGetDescriptor() is to store the 
 *       JAD file downloaded from the TCK server.
 *   </dd>
 *  <dt><b>infoLen</b></dt>
 *   <dd>Any value
 *   </dd>
 *  <dt><b>infoMax</b></dt>
 *   <dd>The size of the buffer indicated by <i>infoBuf</i>.<br>
 *       Recommended value: 2048 bytes
 *   </dd>
 *  <dt><b>jarUrlBuf</b></dt>
 *   <dd>A pointer to the buffer where AmTckGetDescriptor() is to store the URL string
 *       (with '\0' termination) of the JAR file designated in the JAD file MIDlet 
 *       attribute MIDlet-Jar-Url. 
 *   </dd>
 *  <dt><b>jarUrlBufMax</b></dt>
 *   <dd>The size of the buffer indicated by <i>jarUrlBuf</i>.<br>
 *       Recommended value: 512 bytes
 *   </dd>
 *  <dt><b>classNameBuf</b></dt>
 *   <dd>A pointer to the buffer where AmTckGetDescriptor() is to store the start-up class name string
 *       (with '\0' termination) designated in the JAD file MIDlet 
 *       attribute MIDlet-1. 
 *   </dd>
 *  <dt><b>classNameBufMax</b></dt>
 *   <dd>The size of the buffer indicated by <i>classNameBuf</i>.<br>
 *       Recommended value: 512 bytes
 *   </dd>
 *  <dt><b>outer_loop</b></dt>
 *   <dd>JK_TRUE
 *   </dd>
 * </dl>
 * </blockquote>
 * @endhtmlonly
 *
 * When downloading succeeds, this function stores data, based on the contents of 
 * the downloaded JAD file, in each of the buffers pointed to by the <i>infoBuf</i>, 
 * <i>jarUrlBuf</i>, and <i>classNameBuf</i> members of the #T_AM_TCK structure 
 * indicated by <i>appInfo->tckparam</i>, and returns a positive value. 
 * In case of failure, such as when communication with the TCK server fails or the
 * obtained JAD file is defective, this function returns a negative value. 
 *
 * JSI functions defined in @ref HTTP_HTTPS_Communication_JSI are called in the processing
 * of this function. These @ref HTTP_HTTPS_Communication_JSI functions may call JBI
 * functions as necessary for their processing.
 */
JKSint32 AmTckGetDescriptor(JKSint32 heapSize, void *heapAddr, const JKT_MIDP_Application *appInfo);

/**
 * @} end of group
 */

#ifdef __cplusplus
}
#endif

#endif /* ___AMTCK_H */
