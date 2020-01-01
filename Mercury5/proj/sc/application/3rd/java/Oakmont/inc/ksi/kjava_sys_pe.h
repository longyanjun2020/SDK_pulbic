/*
 * Copyright 2002-2003 Aplix Corporation. All rights reserved.
 */

#ifndef KJAVA_SYS_PE_HEADER
#define KJAVA_SYS_PE_HEADER

/**
 * @file kjava_sys_pe.h
 * Section Information KSI
 */
 
#ifdef __cplusplus
extern "C"{
#endif


/*
 *  Interfaces listed in the group are used for:
 *      - section information acquisition
 */
 
/** 
 * @addtogroup JVM_Section_Information_KSI 
 * @par Include file 
 * \#include aj_type.h
 * @{
 */

/**
 * The fast RAM program area allocated to the JVM library. 
 *
 * This identifier indicates the medium where the section is deployed and the type of usage. 
 * A section of this type is initialized when ajms_init() is called.
 */
#define KJAVA_SECTION_VM_BUILTIN_RAM_CODE    0

/**
 * The fast RAM variable area allocated to the JVM library.
 *
 * This identifier indicates the medium where the section is deployed and the type of usage. 
 * A section of this type is initialized in the following cases.
 * - When ajms_init() is called
 * - When the JVM is started 
 * .
 *
 */
#define KJAVA_SECTION_VM_BUILTIN_RAM         1

/**
 * The variable area allocated to the JVM library.
 *
 * This identifier indicates the medium where the section is deployed and the type of usage. 
 * A section of this type is initialized in the following cases.
 * - When ajms_init() is called
 * - When the JVM is started 
 * .
 *
 */
#define KJAVA_SECTION_VM_RAM                 2

/**
 * The variable area allocated to Aplix-supplied libraries other than the JVM library.
 *
 * This identifier indicates the medium where the section is deployed and the type of usage.
 * A section of this type is initialized when ajms_init() is called.
 */
#define KJAVA_SECTION_JBLEND_RAM            10


/**
 *  A data structure representing section information.
 */
typedef struct _KJavaPESectionInfoTag
{
    /**
     * Deployed medium and usage type.
     *
     * Set one of the following values:
     *      - #KJAVA_SECTION_VM_BUILTIN_RAM_CODE
     *      - #KJAVA_SECTION_VM_BUILTIN_RAM
     *      - #KJAVA_SECTION_VM_RAM
     *      - #KJAVA_SECTION_JBLEND_RAM
     *      .
     */
    int             type;

    /**
     * Pointer to a variable area holding variables that have default values.
     */
    void            *dataAddress;

    /**
     * The size (in bytes) of the variable area holding variables that have default values.
     */
    unsigned int    dataSize;

    /**
     * Pointer to a variable area initialized to 0.
     */
    void            *bssAddress;

    /**
     * The size (in bytes) of the variable area initialized to 0.
     */
    unsigned int    bssSize;

    /**
     * Pointer to a fixed memory area holding the default values of
     * variables that have default values.
     */
    void            *initDataAddress;
}
KJavaPESectionInfo;


/**
 *        Gets section information.
 * @param number_p
 *        A pointer to the buffer for putting the element count of
 *        the #KJavaPESectionInfo array indicated by the return value.
 * @return 
 *        Return a pointer to the #KJavaPESectionInfo data structure array
 *        storing the section information. This pointer should be valid forever.
 *
 * Store section information of the JVM library in elements of the array 
 * indicated by the return value, separately for each deployed medium and usage type. 
 * Multiple settings can be stored for each kind of section information. 
 * Store only the section information used in the target device. 
 * Note, however, that at least one item of section information identified by 
 * #KJAVA_SECTION_VM_RAM must be included. Also, if there are Aplix-supplied 
 * libraries other than the JVM library, at least one item of section 
 * information identified by #KJAVA_SECTION_JBLEND_RAM must be included. 
 */
const KJavaPESectionInfo *kjava_core_getSectionInfo(int *number_p);

/** @} */
#ifdef __cplusplus
}
#endif

#endif /* KJAVA_SYS_PE_HEADER */
