#ifndef ONCE_INFRA_EFAT_TYPE_H
#define ONCE_INFRA_EFAT_TYPE_H
////////////////////////////////////////////////////////////////////////////////
///@file infra_types.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////


#include <stddef.h>           // Definition of NULL from the compiler
#include "mdl_efat_pub.h"
#ifdef __cplusplus
# define __externC extern "C"
#else
# define __externC extern
#endif
// Also define externC for now - but it is deprecated
#define externC __externC

// -------------------------------------------------------------------------
// The header <basetype.h> defines the base types used here. It is
// supplied either by the target architecture HAL, or by the host
// porting kit. They are all defined as macros, and only those that
// make choices other than the defaults given below need be defined.

#define EFAT_LSBFIRST 1234
#define EFAT_MSBFIRST 4321

#include <hal_basetype.h>

#if (EFAT_BYTEORDER != EFAT_LSBFIRST) && (EFAT_BYTEORDER != EFAT_MSBFIRST)
//# error You must define EFAT_BYTEORDER to equal EFAT_LSBFIRST or EFAT_MSBFIRST
#endif

#ifndef EFAT_DOUBLE_BYTEORDER
#define EFAT_DOUBLE_BYTEORDER EFAT_BYTEORDER
#endif

#ifndef efat_halint8
#define efat_halint8 char
#endif
#ifndef efat_halint16
#define efat_halint16 short
#endif
#ifndef efat_halint32
#define efat_halint32 int
#endif
#ifndef efat_halint64
#define efat_halint64 long long
#endif

#ifndef efat_halcount8
#define efat_halcount8 int
#endif
#ifndef efat_halcount16
#define efat_halcount16 int
#endif
#ifndef efat_halcount32
#define efat_halcount32 int
#endif
#ifndef efat_halcount64
#define efat_halcount64 long long
#endif

#ifndef efat_haladdress
#define efat_haladdress efat_uint32
#endif
#ifndef efat_haladdrword
#define efat_haladdrword efat_uint32
#endif

#ifndef efat_halbool
#define efat_halbool int
#endif

#ifndef efat_halatomic
#define efat_halatomic efat_halint8
#endif

#ifndef __inline__
#define __inline__ __inline
#endif

#ifndef inline
#define inline __inline
#endif

#ifndef efat_bool
#define efat_bool int
#endif

#ifndef HAL_DCACHE_LINE_SIZE
#define HAL_DCACHE_LINE_SIZE            16
#endif

// fix compiler warning
#if 0
#ifndef LONG_MIN
#define LONG_MIN ((long) 0x80000000L)
#endif

#ifndef LONG_MAX
#define LONG_MAX 0x7FFFFFFFL
#endif
#endif

#ifndef SSIZE_MAX
#define SSIZE_MAX LONG_MAX
#endif

// -------------------------------------------------------------------------
// Provide a default architecture alignment
// This may be overridden in basetype.h if necessary.
// These should be straightforward numbers to allow use in assembly.

#ifndef ARC_ALIGNMENT
# define ARC_ALIGNMENT 8
#endif
// And corresponding power of two alignment
#ifndef ARC_P2ALIGNMENT
# define ARC_P2ALIGNMENT 3
#endif
#if (ARC_ALIGNMENT) != (1 << ARC_P2ALIGNMENT)
# error "Inconsistent ARC_ALIGNMENT and ARC_P2ALIGNMENT values"
#endif

// -------------------------------------------------------------------------

#ifndef NULL
# define NULL 0
#endif

#define EFAT_MACRO_START do {
#define EFAT_MACRO_END   } while (0)


#ifndef __cplusplus

# ifndef false
#  define false 0
# endif

# ifndef true
#  define true (!false)
# endif

#endif

// -------------------------------------------------------------------------

#define EFAT_EMPTY_STATEMENT EFAT_MACRO_START EFAT_MACRO_END

#define EFAT_UNUSED_PARAM( _type_, _name_ ) EFAT_MACRO_START      \
  _type_ __tmp1 = (_name_);                                     \
  _type_ __tmp2 = __tmp1;                                       \
  __tmp1 = __tmp2;                                              \
EFAT_MACRO_END


// -------------------------------------------------------------------------

#define EFAT_REFERENCE_OBJECT(__object__)                                 \
     EFAT_MACRO_START                                                     \
     static void *__cygvar_discard_me__ __attribute__ ((unused)) =       \
                                                          &(__object__); \
     EFAT_MACRO_END

// -------------------------------------------------------------------------

typedef unsigned efat_halcount8  efat_ucount8  ;
typedef   signed efat_halcount8  efat_count8   ;

typedef unsigned efat_halcount16 efat_ucount16 ;
typedef   signed efat_halcount16 efat_count16  ;

typedef unsigned efat_halcount32 efat_ucount32 ;
typedef   signed efat_halcount32 efat_count32  ;

typedef unsigned efat_halcount64 efat_ucount64 ;
typedef   signed efat_halcount64 efat_count64  ;

// -------------------------------------------------------------------------

typedef unsigned efat_halint8    efat_uint8  ;
typedef   signed efat_halint8    efat_int8   ;

typedef unsigned efat_halint16   efat_uint16 ;
typedef   signed efat_halint16   efat_int16  ;

typedef unsigned efat_halint32   efat_uint32 ;
typedef   signed efat_halint32   efat_int32  ;

typedef unsigned efat_halint64   efat_uint64 ;
typedef   signed efat_halint64   efat_int64  ;


// -------------------------------------------------------------------------
typedef volatile unsigned efat_halatomic  efat_atomic;
typedef volatile unsigned efat_halatomic  EFAT_ATOMIC;

// -------------------------------------------------------------------------
// Define types for access plain, on-the-metal memory or devices.

typedef efat_haladdress  EFAT_ADDRESS;
typedef efat_haladdrword EFAT_ADDRWORD;

typedef efat_uint32  EFAT_WORD;
typedef efat_uint8   EFAT_BYTE;
typedef efat_uint16  EFAT_WORD16;
typedef efat_uint32  EFAT_WORD32;
typedef efat_uint64  EFAT_WORD64;



// -------------------------------------------------------------------------
// Constructor ordering macros.  These are added as annotations to all static objects to order the constuctors appropriately.

// The following will be removed eventually as it doesn't allow the use of
// e.g. pri+5 format
#define EFAT_INIT_PRIORITY( _pri_ ) BLD_ATTRIB_INIT_PRI( EFAT_INIT_##_pri_ )

#define BLD_ATTRIB_INIT_BEFORE( _pri_ ) BLD_ATTRIB_INIT_PRI(_pri_-100)
#define BLD_ATTRIB_INIT_AFTER( _pri_ )  BLD_ATTRIB_INIT_PRI(_pri_+100)

#define EFAT_INIT_HAL                    10000
#define EFAT_INIT_SCHEDULER              11000
#define EFAT_INIT_IDLE_THREAD            11100
#define EFAT_INIT_INTERRUPTS             12000
#define EFAT_INIT_DRIVERS                13000
#define EFAT_INIT_CLOCK                  14000
#define EFAT_INIT_THREADS                16000
#define EFAT_INIT_KERNEL                 40000
#define EFAT_INIT_MEMALLOC               47000
#define EFAT_INIT_IO                     49000
#define EFAT_INIT_IO_FS                  50000
#define EFAT_INIT_LIBC                   52000
#define EFAT_INIT_COMPAT                 55000
#define EFAT_INIT_APPLICATION            60000
#define EFAT_INIT_PREDEFAULT             65534
#define EFAT_INIT_DEFAULT                65535

#if defined(__cplusplus) && defined(__GNUC__) && \
    !defined(BLD_ATTRIB_INIT_PRI)
# define BLD_ATTRIB_INIT_PRI( _pri_ ) __attribute__((init_priority(_pri_)))
#elif !defined(BLD_ATTRIB_INIT_PRI)
// FIXME: should maybe just bomb out if this is attempted anywhere else?
// Not sure
# define BLD_ATTRIB_INIT_PRI( _pri_ )
#endif


// -------------------------------------------------------------------------

#ifndef EFAT_LABEL_DEFN

#define EFAT_LABEL_DEFN(_label) _label

#endif

#ifndef EFAT_LABEL_NAME

#define EFAT_LABEL_NAME(_name_) _name_

#endif

// -------------------------------------------------------------------------
// COMPILER-SPECIFIC STUFF

#if 1
#if !defined(BLD_ATTRIB_CONSTRUCTOR)
#define BLD_ATTRIB_CONSTRUCTOR __attribute__((constructor))
#endif

#if !defined(BLD_ATTRIB_NORET)
#define BLD_ATTRIB_NORET __attribute__((noreturn))
#endif

#if !defined(BLD_ATTRIB_WEAK)
#define BLD_ATTRIB_WEAK __attribute__ ((weak))
#endif

#if !defined(BLD_ATTRIB_ALIAS)
#define BLD_ATTRIB_ALIAS(__symbol__) __attribute__ ((alias (#__symbol__)))
#endif

#if !defined(BLD_ATTRIB_ASM_ALIAS)
#define __Str(x) #x
#define __Xstr(x) __Str(x)
#define BLD_ATTRIB_ASM_ALIAS(__symbol__) __asm__ ( __Xstr( EFAT_LABEL_DEFN( __symbol__ ) ) )
#endif

#if !defined(BLD_ATTRIB_SECTION)
#define BLD_ATTRIB_SECTION(__sect__) __attribute__((section (__sect__)))
#endif

// Give a type or object explicit minimum alignment
#if !defined(BLD_ATTRIB_ALIGN)
#define BLD_ATTRIB_ALIGN(__align__) __attribute__((aligned(__align__)))
#endif

#if !defined(BLD_ATTRIB_CONST)
#define BLD_ATTRIB_CONST __attribute__((const))
#endif

#if !defined(BLD_ATTRIB_ALIGNOFTYPE)
#define BLD_ATTRIB_ALIGNOFTYPE( _type_ ) __attribute__((aligned(__alignof__( _type_ ))))
#endif


#if !defined(BLD_ATTRIB_ALIGN_MAX)
#define BLD_ATTRIB_ALIGN_MAX __attribute__((aligned))
#endif

// Teach compiler how to check format of printf-like functions
#define BLD_ATTRIB_PRINTF_FORMAT(__format__, __args__) __attribute__((format (printf, __format__, __args__)))

#else

#endif

// How to define weak aliases. Currently this is simply a mixture of the
// above

#define BLD_ATTRIB_WEAK_ALIAS(__symbol__) \
        BLD_ATTRIB_WEAK BLD_ATTRIB_ALIAS(__symbol__)

#ifdef __cplusplus
#define __THROW throw()
#else
#define __THROW
#endif

// -------------------------------------------------------------------------

#ifndef BLD_ANNOTATE_VARIABLE_CLOCK
#define BLD_ANNOTATE_VARIABLE_CLOCK
#endif
#ifndef BLD_ANNOTATE_VARIABLE_SCHED
#define BLD_ANNOTATE_VARIABLE_SCHED
#endif
#ifndef BLD_ANNOTATE_VARIABLE_INTR
#define BLD_ANNOTATE_VARIABLE_INTR
#endif
#ifndef BLD_ANNOTATE_VARIABLE_HAL
#define BLD_ANNOTATE_VARIABLE_HAL
#endif

// -------------------------------------------------------------------------


#define MEM_REGION_ATTR_R  0x01  // Region can be read
#define MEM_REGION_ATTR_W  0x02  // Region can be written


// -------------------------------------------------------------------------
#endif // ONCE_INFRA_EFAT_TYPE_H multiple inclusion protection
// EOF efat_type.h
