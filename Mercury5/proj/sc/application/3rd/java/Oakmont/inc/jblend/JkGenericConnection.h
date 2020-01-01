/*
 * Copyright 2002,2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkGenericConnection.h
 *   T.B.D.
 */
/**
 * @addtogroup Protocol_Extension_JSI
 * @{
 */

#ifndef  ___SYS_JK_GENERICCONNECTION_H
#define  ___SYS_JK_GENERICCONNECTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"

/**
 * Data structure for indicating a protocol specific to the native system. 
 */
typedef struct {

   /**
    *  A pointer to the buffer holding the scheme name. 
    *  
    *  The scheme name string is the {scheme} part of the URL name 
    *  <_em>{scheme}:[{target}][{parms}]</_em> passed as an argument to the 
    *  <code>javax.microedition.io.Connector</code> class open method.
    *  - Do not include ':'in the scheme name.
    *  - Designate the scheme name as a UTF-8 character string.
    *  - Append '\0' to terminate the scheme name string.
    *  
    *  This pointer should remain valid until the JVM terminates. 
    *   
    */
    JKUint8* schemeName;

   /**
    *  A pointer to the buffer holding the protocol factory class name 
    *  corresponding to the scheme name. 
    *  
    *  The protocol factory class generates an instance of a class implementing the
    *  <code>javax.microedition.io.Connection</code> interface or a sub-interface thereof.
    *  This class must implement the <code>com.jblend.io.ConnectionImplFactory</code> interface.
    *  
    *  - Designate the class name as a UTF-8 character string.
    *  - Append '\0'to terminate the class name string.
    *  - Include the package name in the class name, demarcating it by ".". <br>
    *    (Example: <code>com.jblend.io.j2me.http.HttpConnectionImpl</code>)
    *   
    *  This pointer should remain valid until the JVM terminates. 
    *   
    *
    * @see {@link com.jblend.io.ConnectionImplFactory}
    */
    JKUint8* className;

} JKT_GenericConnection_Scheme;

/**
 *         Gets information about the protocols specific to the native system. 
 * @param  number
 *         A pointer to the buffer for putting the element count of the
 *         JKT_GenericConnection_Scheme array returned by this function.
 * @return Return a pointer to the array of the structure holding the protocol information. 
 *         This pointer should remain valid until the JVM terminates. 
 *         Return #JK_NULL if no native system-specific protocol is used.
 *
 * JBlend calls this function before executing a Java application. 
 *
 */
const JKT_GenericConnection_Scheme* JkGenericConnectionGetSchemeInfo(JKSint32* number);

#ifdef __cplusplus
}
#endif

#endif /* ___SYS_JK_GENERICCONNECTION_H */

/**
 * @} end of group
 */
