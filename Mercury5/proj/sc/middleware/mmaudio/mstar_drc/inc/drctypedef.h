/*
********************************************************************************
*
*      File             : drctypedef.c
*      Purpose          : Basic types.
*
********************************************************************************
*/


#ifndef drctypedef_h
#define drctypedef_h //"$Id $"

#undef ORIGINAL_TYPEDEF_H /* define to get "original" ETSI version
                             of typedef.h                           */

#ifdef ORIGINAL_TYPEDEF_H
/*
 * this is the original code from the ETSI file typedef.h
 */
  /* 
#if   defined(__BORLANDC__) || defined(__WATCOMC__) || defined(_MSC_VER) || defined(__ZTC__)
typedef signed char Word8;
typedef short Word16;
typedef long Word32;
typedef int Flag;

#elif defined(__sun)
typedef signed char Word8;
typedef short Word16;
typedef long Word32;
typedef int Flag;

#elif defined(__unix__) || defined(__unix)
typedef signed char Word8;
typedef short Word16;
typedef int Word32;
typedef int Flag;

#endif
*/
    typedef signed char Word8;
    typedef short Word16;
    typedef int Word32;
    typedef int Flag;

#else /* not original typedef.h */
typedef signed char Word8;
typedef short Word16;
typedef int Word32;
//typedef int Flag;

/*
 * use (improved) type definition file typdefs.h and add a "Flag" type
 */
#include "drctypedefs.h"
typedef int Flag;

#endif

#endif

