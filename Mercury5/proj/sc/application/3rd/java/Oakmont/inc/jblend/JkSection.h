/**
 * Copyright 2002,2003 Aplix Corporation. All rights reserved.
 */

/**
 * @file JkSection.h
 * Section Information Acquisition
 */

/**
 * @addtogroup Section_Info_Acquisition
 * @{
 */


#ifndef ___SYS_JK_SECTION_H
#define ___SYS_JK_SECTION_H

#ifdef __cplusplus
extern "C" {
#endif

#include "JkTypes.h"


/**
 *  The fast RAM program area allocated to the JVM library.
 *
 *  This identifier indicates the medium where the section is deployed and the type of usage. 
 *  A section of this type is initialized when AmJBlendInitialize() is called.
 */
#define JK_SECTION_VM_BUILTIN_RAM_CODE    0

/**
 *  The fast RAM variable area allocated to the JVM library.
 *
 *  This identifier indicates the medium where the section is deployed and the type of usage. 
 *  A section of this type is initialized in the following cases.
 *  - When AmJBlendInitialize() is called
 *  - When the JVM is started
 *  .
 */
#define JK_SECTION_VM_BUILTIN_RAM         1

/**
 *  The variable area allocated to the JVM library.
 *
 *  This identifier indicates the medium where the section is deployed and the type of usage. 
 *  A section of this type is initialized in the following cases.
 *  - When AmJBlendInitialize() is called
 *  - When the JVM is started
 *  .
 */
#define JK_SECTION_VM_RAM                 2

/**
 *  The variable area allocated to Aplix-supplied libraries other than the JVM library.
 *
 *  This identifier indicates the medium where the section is deployed and the type of usage. 
 *  A section of this type is initialized when AmJBlendInitialize() is called.
 */
#define JK_SECTION_JBLEND_RAM            10


/**
 *  A data structure representing section information.
 *
 *  This structure holds information about the memory area sections in which the JVM library object code is deployed. 
 *  This structure represents one section.
 */
typedef struct {

    /**
     *  Deployed medium and usage type.
     *
     *  Set one of the following values.
     *  <ul>
     *  <li> #JK_SECTION_VM_BUILTIN_RAM_CODE
     *  <li> #JK_SECTION_VM_BUILTIN_RAM
     *  <li> #JK_SECTION_VM_RAM
     *  <li> #JK_SECTION_JBLEND_RAM
     *  </ul>
     */
    JKSint32    type;

    /**
     * Pointer to a variable area holding variables that have default values. 
     */
    void*       dataAddress;

    /**
     * The size (in bytes) of the variable area holding variables that have default values. 
     */
    JKUint32    dataSize;

    /**
     * Pointer to a variable area initialized to 0. 
     */
    void*       bssAddress;

    /**
     * The size (in bytes) of the variable area initialized to 0. 
     */
    JKUint32    bssSize;

    /**
     * Pointer to a fixed memory area holding the default values of variables that have default values. 
     */
    void*       initDataAddress;

} JKT_Section_InfoR2;

/**
 * Gets section information.
 *
 *  @param
 *   A pointer to the buffer for putting the element count of 
 *   the #JKT_Section_InfoR2 array indicated by the return value.
 *  @return
 *   Return a pointer to the #JKT_Section_InfoR2 data structure array
 *   storing the section information.
 *   This pointer should remain valid until the JVM terminates. 
 *
 *  This function is called from JBlend when the native system calls 
 *  AmJBlendInitialize() or when the native system calls the JBI function 
 *  which starts the JVM. The name of JBI function which starts the JVM 
 *  depends on the specifications of the JBlend which is embedded in the 
 *  target device. 
 *  The JBI function function names are as follows.
 *  - AamsVmStartMIDP(), for MIDP
 *  - AMexecuteDojaApplication(), for DoJa 3.0
 *  - AjamVmStartDoja(), for DoJa OE
 *  .
 *  
 *  Store section information in elements of the array indicated by 
 *  the return value, separately for each deployed medium and usage type.
 *  Multiple settings can be stored for each kind of section information.
 *  Store only the section information used in the target device. Note, 
 *  however, that at least one item of section information identified by 
 *  #JK_SECTION_VM_RAM must be included. Also, if there are Aplix-supplied 
 *  libraries other than the JVM library, at least one item of section 
 *  information identified by #JK_SECTION_JBLEND_RAM must be included.
 */
const JKT_Section_InfoR2* JkSectionGetInfoR2(JKSint32* number);

/**
 * @} end of group
 */

#ifdef __cplusplus
}
#endif

#endif /* ___SYS_JK_SECTION_H */
