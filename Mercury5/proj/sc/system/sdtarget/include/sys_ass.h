#ifndef __SYS_ASS_H__
#define __SYS_ASS_H__

//==========================================================================
//
//      sys_ass.h
//
//      Macros and prototypes for the assert system
//
//==========================================================================

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "syscfg.h"
#include "stdcomp.h"


//-----------------------------------------------------------------------------
// Function Prototypes
//-----------------------------------------------------------------------------
// -------------------------------------------------------------------------
// If we do not have a function name macro, define it ourselves
#ifndef __PRETTY_FUNCTION__
# define __PRETTY_FUNCTION__    NULL
#endif

// -------------------------------------------------------------------------
// This is executed to deal with failure - breakpoint it first!
// It is declared as a weak symbol to allow user code to override the
// definition.
void sys_assert_fail(const char* /* psz_func */, const char* /* psz_file */,
                    u32 /* linenum */, const char* /* psz_msg */);


#ifdef SYSCFG_USE_ASSERTS
// -------------------------------------------------------------------------
// We define macros and appropriate prototypes for the assert/fail
// system.  These are:
//      SYS_FAIL        - unconditional panic
//      SYS_ASSERT      - panic if boolean expression is false
//      SYS_ASSERTC     - compact version of SYS_ASSERT

# define SYS_ASSERT_DOCALL( _msg_ )                                     \
    SYS_MACRO_START                                                     \
    /* Make sure we always get a pretty-printed message */              \
    sys_assert_fail( __PRETTY_FUNCTION__, __FILE__, __LINE__, _msg_ );  \
    SYS_MACRO_END

// unconditional failure; use like panic(), coredump() &c.
# define SYS_FAIL( _msg_ )          \
    SYS_MACRO_START                 \
    SYS_ASSERT_DOCALL( _msg_ );     \
    SYS_MACRO_END

// conditioned assert; if the condition is false, fail.
# define SYS_ASSERT( _bool_, _msg_ )    \
    SYS_MACRO_START                     \
    if ( ! ( _bool_ ) )                 \
        SYS_ASSERT_DOCALL( _msg_ );     \
    SYS_MACRO_END

# define SYS_ASSERTC( _bool_ )          \
    SYS_MACRO_START                     \
    if ( ! ( _bool_ ) )                 \
        SYS_ASSERT_DOCALL( #_bool_ );   \
    SYS_MACRO_END

#else // ! SYSCFG_USE_ASSERTS
// -------------------------------------------------------------------------
// No asserts: we define empty statements for assert & fail.

# define SYS_FAIL( _msg_ )              SYS_EMPTY_STATEMENT
# define SYS_ASSERT( _bool_, _msg_ )    SYS_EMPTY_STATEMENT
# define SYS_ASSERTC( _bool_ )          SYS_EMPTY_STATEMENT

#endif // ! SYSCFG_USE_ASSERTS

#endif // __SYS_ASS_H__
