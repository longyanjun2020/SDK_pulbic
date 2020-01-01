/*************************************************************************
 *  KVM Development Service Team / Mobile Device Group
 *========================================================================
 *  FILE NAME:  aj_type.h
 *  VERSION:    1.1
 *  COMPONENT:  General
 *  DESCRIPTION:
 *  HISTORY:
 *      2003/08/21      1.0     [RC] Initial
 *      2004/03/20      1.1     [YH] Add AJ_BYTE, AJ_VOID, and AJ_INT
 *************************************************************************/
/**
 *  @file aj_type.h
 *  @if JAPANESE
 *  Common Data Type
 *  @else
 *  Common Data Type
 *  @endif
 */
/**
 * @addtogroup aj_type 
 * @par Include file 
 * \#include aj_type.h
 * @{
 */

#ifndef _AJ_TYPE_H
#define _AJ_TYPE_H

/*************************************************************************
 *                          PLATFORM SELECTION
 *
 * WIN32:   You know it
 * ARM:     Generic ARM platform
 * ARMTI:   TI OMAP platform
 *************************************************************************/

/*************************************************************************
 *                              Definitions
 *
 * AJ_UNICODE_SUPPORT: Currently not in use
 * AJ_64BIT_NATIVE_SUPPORT: Native or compiler support 64-bit data type
 * AJ_LITTLE_ENDIAN: Endianess of the platform
 *************************************************************************/

#ifdef AJ_PLATFORM_WIN32

    #define AJ_64BIT_NATIVE_SUPPORT     1
    #define AJ_LITTLE_ENDIAN            1

#endif

#ifdef AJ_PLATFORM_ARM

    #define AJ_64BIT_NATIVE_SUPPORT     1
    #define AJ_LITTLE_ENDIAN            1

#endif

#ifdef AJ_PLATFORM_ARMTI

    #define AJ_64BIT_NATIVE_SUPPORT     0
    #define AJ_LITTLE_ENDIAN            1

#endif

#ifdef AJ_PLATFORM_SH3DSP

    #define AJ_64BIT_NATIVE_SUPPORT     1
    #define AJ_LITTLE_ENDIAN            1

#endif

/*************************************************************************
 *                              Data Types
 *
 * If the platform does not support 64-bit, we will provide a generic AJ
 * 64-bit data type implementation.  Currently not available :P
 *************************************************************************/

#ifdef AJ_PLATFORM_WIN32
    /** @brief 8-bit signed integer */
    typedef     char                AJ_S8;
    /** @brief 8-bit unsigned integer */
    typedef     unsigned char       AJ_U8;
    /** @brief 16-bit signed integer */
    typedef     short               AJ_S16;
    /** @brief 16-bit unsigned integer */
    typedef     unsigned short      AJ_U16;
    /** @brief 32-bit signed integer */
    typedef     signed long         AJ_S32;
    /** @brief 32-bit unsigned integer */
    typedef     unsigned long       AJ_U32;
    
    #ifndef __GNUC__
        /** @brief 64-bit signed integer */
        typedef     _int64              AJ_S64;
        /** @brief 64-bit unsigned integer */
        typedef     unsigned _int64     AJ_U64;
    #else
        /** @brief 64-bit signed integer */
        typedef     long long           AJ_S64;
        /** @brief 64-bit unsigned integer */
        typedef     unsigned long long  AJ_U64;
    #endif
    
    /** @brief Unicode character */
    typedef     unsigned short      AJ_CHAR;
    /** @brief 8-bit byte */
    typedef     unsigned char       AJ_BYTE;
    /** @brief Alias of int */
    typedef     int                 AJ_INT;
    /** @brief Void */
    typedef     void                AJ_VOID;
    /** @brief NULL */
    #define     AJ_NULL             (void*)0

#elif defined(AJ_PLATFORM_ARM)
    /** @brief 8-bit signed integer */
    typedef     signed char         AJ_S8;
    /** @brief 8-bit unsigned integer */
    typedef     unsigned char       AJ_U8;
    /** @brief 16-bit signed integer */
    typedef     signed short        AJ_S16;
    /** @brief 16-bit unsigned integer */
    typedef     unsigned short      AJ_U16;
    /** @brief 32-bit signed integer */
    typedef     signed int          AJ_S32;
    /** @brief 32-bit unsigned integer */
    typedef     unsigned int        AJ_U32;
    /** @brief 64-bit signed integer */
    typedef     long long           AJ_S64;
    /** @brief 64-bit unsigned integer */
    typedef     unsigned long long  AJ_U64;
    /** @brief Unicode character */
    typedef     unsigned short      AJ_CHAR;
    /** @brief 8-bit byte */
    typedef     unsigned char       AJ_BYTE;
    /** @brief Alias of int */
    typedef     int                 AJ_INT;
    /** @brief Void */
    typedef     void                AJ_VOID;
    /** @brief NULL */
    #define     AJ_NULL             ((void*)0)
#endif

#ifdef AJ_PLATFORM_ARMTI
    /** @brief 8-bit signed integer */
    typedef     signed char         AJ_S8;
    /** @brief 8-bit unsigned integer */
    typedef     unsigned char       AJ_U8;
    /** @brief 16-bit signed integer */
    typedef     short               AJ_S16;
    /** @brief 16-bit unsigned integer */
    typedef     unsigned short      AJ_U16;
    /** @brief 32-bit signed integer */
    typedef     signed long         AJ_S32;
    /** @brief 32-bit unsigned integer */
    typedef     unsigned long       AJ_U32;
    /** @brief Unicode character */
    typedef     unsigned short      AJ_CHAR;
    /** @brief 8-bit byte */
    typedef     unsigned char       AJ_BYTE;
    /** @brief Alias of int */
    typedef     int                 AJ_INT;
    /** @brief Void */
    typedef     void                AJ_VOID;
     /** @brief NULL */
    #define     AJ_NULL             ((void*)0)
#endif // Types

#ifdef AJ_PLATFORM_SH3DSP
    /** @brief 8-bit signed integer */
    typedef     char                AJ_S8;
    /** @brief 8-bit unsigned integer */
    typedef     unsigned char       AJ_U8;
     /** @brief 16-bit signed integer */
    typedef     short               AJ_S16;
    /** @brief 16-bit unsigned integer */
    typedef     unsigned short      AJ_U16;
    /** @brief 32-bit signed integer */
    typedef     signed long         AJ_S32;
    /** @brief 32-bit unsigned integer */
    typedef     unsigned long       AJ_U32;
    /** @brief 64-bit signed integer */
    typedef     long long           AJ_S64;
    /** @brief 64-bit unsigned integer */
    typedef     unsigned long long  AJ_U64;
    /** @brief 8-bit byte */
    typedef     unsigned short      AJ_CHAR;
    /** @brief 8-bit byte */
    typedef     unsigned char       AJ_BYTE;
    /** @brief Alias of int */
    typedef     int                 AJ_INT;
    /** @brief Void */
    typedef     void                AJ_VOID;
    /** @brief NULL */
    #define     AJ_NULL             ((void*)0)
#endif // Types

#ifdef AJ_PLATFORM_IAR
    /** @brief 8-bit signed integer */
    typedef     signed char         AJ_S8;
    /** @brief 8-bit unsigned integer */
    typedef     unsigned char       AJ_U8;
    /** @brief 16-bit signed integer */
    typedef     signed short        AJ_S16;
    /** @brief 16-bit unsigned integer */
    typedef     unsigned short      AJ_U16;
    /** @brief 32-bit signed integer */
    typedef     signed long          AJ_S32;
    /** @brief 32-bit unsigned integer */
    typedef     unsigned long        AJ_U32;
    /** @brief 64-bit signed integer */
    typedef     long long           AJ_S64;
    /** @brief 64-bit unsigned integer */
    typedef     unsigned long long  AJ_U64;
    /** @brief Unicode character */
    typedef     unsigned short      AJ_CHAR;
    /** @brief 8-bit byte */
    typedef     unsigned char       AJ_BYTE;
    /** @brief Alias of int */
    typedef     int                 AJ_INT;
    /** @brief Void */
    typedef     void                AJ_VOID;
    /** @brief NULL */
    #define     AJ_NULL             ((void*)0)
#endif

/* the platform type has not been defined */
#ifndef AJ_LITTLE_ENDIAN 
    #error Platform type has not been defined.
    
    /* For doxygen usage */
    /** @brief 8-bit signed integer */
    typedef     char                AJ_S8;
    /** @brief 8-bit unsigned integer */
    typedef     unsigned char       AJ_U8;
     /** @brief 16-bit signed integer */
    typedef     short               AJ_S16;
    /** @brief 16-bit unsigned integer */
    typedef     unsigned short      AJ_U16;
    /** @brief 32-bit signed integer */
    typedef     signed long         AJ_S32;
    /** @brief 32-bit unsigned integer */
    typedef     unsigned long       AJ_U32;
    /** @brief 64-bit signed integer */
    typedef     long long           AJ_S64;
    /** @brief 64-bit unsigned integer */
    typedef     unsigned long long  AJ_U64;
    /** @brief 8-bit byte */
    typedef     unsigned short      AJ_CHAR;
    /** @brief 8-bit byte */
    typedef     unsigned char       AJ_BYTE;
    /** @brief Alias of int */
    typedef     int                 AJ_INT;
    /** @brief Void */
    typedef     void                AJ_VOID;
    /** @brief NULL */
    #define     AJ_NULL             ((void*)0)
#endif

/*************************************************************************
 *                              Enumerations
 *
 *************************************************************************/

/** @brief Boolean type */
typedef signed int AJ_BOOL;
/** @brief AJ_BOOL False */
#define AJ_FALSE   (0)
/** @brief AJ_BOOL True */
#define AJ_TRUE    (1)

/** @brief Result type */
typedef signed int AJ_RESULT;
/** @brief AJ_RESULT Failure */
#define AJ_FAILURE (-1)
/** @brief AJ_RESULT Success */
#define AJ_SUCCESS (0)

#endif // _AJ_TYPE_H

/** @} */
