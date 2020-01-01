#ifndef ONCE_INFRA_EFAT_ASS_H
#define ONCE_INFRA_EFAT_ASS_H
////////////////////////////////////////////////////////////////////////////////
///@file infra_ass.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_infra.h>
#include <infra_type.h>         // for BLD_ATTRIB_NORET

// -------------------------------------------------------------------------

#ifndef DBG_INFRA_DEBUG_FUNCTION_PSEUDOMACRO
#ifndef __PRETTY_FUNCTION__
#define __PRETTY_FUNCTION__ NULL
#endif
#endif

externC void
efat_assert_msg( const char *psz_func, const char *psz_file, efat_uint32 linenum, const char *psz_msg );

externC void
efat_assert_fail( const char* , const char* , efat_uint32 , const char* );

// -------------------------------------------------------------------------

#ifdef DBG_USE_ASSERTS

// -------------------------------------------------------------------------

#ifdef DBG_INFRA_DEBUG_ASSERT_MESSAGE
#define EFAT_ASSERT_DOCALL( _msg_ )                                      \
        EFAT_MACRO_START                                                   \
        efat_assert_msg( __PRETTY_FUNCTION__, __FILE__, __LINE__, _msg_ ); \
        efat_assert_fail( __PRETTY_FUNCTION__, __FILE__, __LINE__, _msg_ );\
        EFAT_MACRO_END
#else
#define EFAT_ASSERT_DOCALL( _msg_ )    \
        EFAT_MACRO_START                 \
        const char* _tmp1_ = _msg_;     \
        _tmp1_ = _tmp1_;                \
        efat_assert_fail( __PRETTY_FUNCTION__, __FILE__, __LINE__, NULL ); \
        EFAT_MACRO_END
#endif

// unconditional failure; use like panic(), coredump() &c.
#define EFAT_FAIL( _msg_ )              \
        EFAT_MACRO_START                 \
        EFAT_ASSERT_DOCALL( _msg_ );      \
        EFAT_MACRO_END

// conditioned assert; if the condition is false, fail.
#define EFAT_ASSERT( _bool_, _msg_ )    \
        EFAT_MACRO_START                 \
        if ( ! ( _bool_ ) )             \
            EFAT_ASSERT_DOCALL( _msg_ );  \
        EFAT_MACRO_END

#define EFAT_ASSERTC( _bool_ )          \
       EFAT_MACRO_START                  \
       if ( ! ( _bool_ ) )              \
           EFAT_ASSERT_DOCALL( #_bool_ );\
       EFAT_MACRO_END

#else
#define EFAT_FAIL( _msg_ )           EFAT_EMPTY_STATEMENT
#define EFAT_ASSERT( _bool_, _msg_ ) EFAT_EMPTY_STATEMENT
#define EFAT_ASSERTC( _bool_ )       EFAT_EMPTY_STATEMENT
#endif // ! DBG_USE_ASSERTS

// -------------------------------------------------------------------------
#ifdef DBG_USE_ASSERTS

#ifdef DBG_INFRA_CHECK_DATA_PTR
#define EFAT_CHECK_DATA_PTR( _ptr_, _msg_ )            \
        EFAT_MACRO_START                                 \
        EFAT_MACRO_END

#define EFAT_CHECK_DATA_PTRC( _ptr_ )                                  \
         EFAT_MACRO_START                                                \
         EFAT_MACRO_END
#else
#define EFAT_CHECK_DATA_PTR( _ptr_, _msg_ ) EFAT_EMPTY_STATEMENT
#define EFAT_CHECK_DATA_PTRC( _ptr_ )       EFAT_EMPTY_STATEMENT
#endif

#ifdef DBG_INFRA_CHECK_FUNC_PTR
#define EFAT_CHECK_FUNC_PTR( _ptr_, _msg_ )                    \
        EFAT_MACRO_START                                         \
        EFAT_MACRO_END

#define EFAT_CHECK_FUNC_PTRC( _ptr_ )                                          \
         EFAT_MACRO_START                                                        \
         EFAT_MACRO_END
#else
#define EFAT_CHECK_FUNC_PTR( _ptr_, _msg_ ) EFAT_EMPTY_STATEMENT
#define EFAT_CHECK_FUNC_PTRC( _ptr_ )       EFAT_EMPTY_STATEMENT
#endif


#else // DBG_USE_ASSERTS

#define EFAT_CHECK_DATA_PTR( _ptr_, _msg_ ) EFAT_EMPTY_STATEMENT
#define EFAT_CHECK_FUNC_PTR( _ptr_, _msg_ ) EFAT_EMPTY_STATEMENT
#define EFAT_CHECK_DATA_PTRC( _ptr_ )       EFAT_EMPTY_STATEMENT
#define EFAT_CHECK_FUNC_PTRC( _ptr_ )       EFAT_EMPTY_STATEMENT

#endif

enum efat_assert_class_zeal {
  efat_system_test       = -1,
  efat_none              = 0,
  efat_trivial,
  efat_quick,
  efat_thorough,
  efat_extreme
};

#ifdef DBG_INFRA_DEBUG_PRECONDITIONS
#define EFAT_PRECONDITION( _bool_ , _msg_ ) EFAT_ASSERT( _bool_, _msg_ )
#define EFAT_PRECONDITIONC( _bool_ ) EFAT_ASSERT( _bool_, "precondition " #_bool_)
#else
#define EFAT_PRECONDITION( _bool_ , _msg_ ) EFAT_EMPTY_STATEMENT
#define EFAT_PRECONDITIONC( _bool_ )        EFAT_EMPTY_STATEMENT
#endif

#ifdef DBG_INFRA_DEBUG_LOOP_INVARIANTS
#define EFAT_LOOP_INVARIANT( _bool_ , _msg_ ) EFAT_ASSERT( _bool_, _msg_ )
#define EFAT_LOOP_INVARIANTC( _bool_ ) EFAT_ASSERT( _bool_, "loop invariant " #_bool_ )
#else
#define EFAT_LOOP_INVARIANT( _bool_ , _msg_ ) EFAT_EMPTY_STATEMENT
#define EFAT_LOOP_INVARIANTC( _bool_ )        EFAT_EMPTY_STATEMENT
#endif

#ifdef DBG_INFRA_DEBUG_POSTCONDITIONS
#define EFAT_POSTCONDITION( _bool_ , _msg_ ) EFAT_ASSERT( _bool_, _msg_ )
#define EFAT_POSTCONDITIONC( _bool_ ) EFAT_ASSERT( _bool_, "postcondition " #_bool_)
#else
#define EFAT_POSTCONDITION( _bool_ , _msg_ ) EFAT_EMPTY_STATEMENT
#define EFAT_POSTCONDITIONC( _bool_ )        EFAT_EMPTY_STATEMENT
#endif

#ifdef __cplusplus

// All variants of _CLASSO
#define EFAT_PRECONDITION_CLASSO( _obj_, _msg_ )  EFAT_PRECONDITION( (_obj_).check_this(EFAT_ASSERT_CLASS_ZEAL), _msg_)

#define EFAT_PRECONDITION_CLASSOC( _obj_ ) EFAT_PRECONDITION_CLASSO( (_obj_), "precondition, object (" #_obj_ ") is valid" )

#define EFAT_POSTCONDITION_CLASSO( _obj_, _msg_ ) EFAT_POSTCONDITION( (_obj_).check_this(EFAT_ASSERT_CLASS_ZEAL), _msg_)

#define EFAT_POSTCONDITION_CLASSOC( _obj_ ) EFAT_POSTCONDITION_CLASSO( (_obj_), "postcondition, object (" #_obj_ ") is valid" )

#define EFAT_LOOP_INVARIANT_CLASSO( _obj_, _msg_) EFAT_LOOP_INVARIANT( (_obj_).check_this(EFAT_ASSERT_CLASS_ZEAL), _msg_)

#define EFAT_LOOP_INVARIANT_CLASSOC( _obj_ ) EFAT_LOOP_INVARIANT_CLASSO( (_obj_), "loop invariant, object (" #_obj_ ") is valid" )

// All variants of _CLASS
#define EFAT_PRECONDITION_CLASS( _pobj_, _msg_ ) EFAT_PRECONDITION( ((0 != (_pobj_)) && (_pobj_)->check_this(EFAT_ASSERT_CLASS_ZEAL)), _msg_)

#define EFAT_PRECONDITION_CLASSC( _pobj_ ) EFAT_PRECONDITION_CLASS( (_pobj_), "precondition, class pointer (" #_pobj_ ") is valid" )

#define EFAT_POSTCONDITION_CLASS( _pobj_, _msg_ ) EFAT_POSTCONDITION( ((0 != (_pobj_)) && (_pobj_)->check_this(EFAT_ASSERT_CLASS_ZEAL)), _msg_)

#define EFAT_POSTCONDITION_CLASSC( _pobj_ ) EFAT_POSTCONDITION_CLASS( (_pobj_), "postcondition, class pointer (" #_pobj_ ") is valid" )

#define EFAT_LOOP_INVARIANT_CLASS( _pobj_, _msg_) EFAT_LOOP_INVARIANT( ((0 != (_pobj_)) && (_pobj_)->check_this(EFAT_ASSERT_CLASS_ZEAL)), _msg_)

#define EFAT_LOOP_INVARIANT_CLASSC( _pobj_ ) EFAT_LOOP_INVARIANT_CLASS( (_pobj_), "loop invariant, class pointer (" #_pobj_ ") is valid" )

// All variants of _THIS
#define EFAT_PRECONDITION_THIS( _msg_ )  EFAT_PRECONDITION( this->check_this(EFAT_ASSERT_CLASS_ZEAL), _msg_)

#define EFAT_PRECONDITION_THISC() EFAT_PRECONDITION_THIS( "precondition, \"this\"  is valid" )

#define EFAT_POSTCONDITION_THIS( _msg_ ) EFAT_POSTCONDITION( this->check_this(EFAT_ASSERT_CLASS_ZEAL), _msg_)

#define EFAT_POSTCONDITION_THISC() EFAT_POSTCONDITION_THIS( "postcondition, \"this\" is valid" )

#define EFAT_LOOP_INVARIANT_THIS( _msg_) EFAT_LOOP_INVARIANT( this->check_this(EFAT_ASSERT_CLASS_ZEAL), _msg_)

#define EFAT_LOOP_INVARIANT_THISC() EFAT_LOOP_INVARIANT_THIS( "loop invariant, \"this\" is valid" )

// All variants of _ZERO_OR_CLASS
#define EFAT_PRECONDITION_ZERO_OR_CLASS( _pobj_, _msg_ ) EFAT_PRECONDITION( ((0 == (_pobj_)) || (_pobj_)->check_this(EFAT_ASSERT_CLASS_ZEAL)), _msg_)

#define EFAT_PRECONDITION_ZERO_OR_CLASSC( _pobj_ ) EFAT_PRECONDITION_ZERO_OR_CLASS( (_pobj_), "precondition, class pointer (" #_pobj_ ") is zero or valid" )

#define EFAT_POSTCONDITION_ZERO_OR_CLASS( _pobj_, _msg_ ) EFAT_POSTCONDITION( ((0 == (_pobj_)) || (_pobj_)->check_this(EFAT_ASSERT_CLASS_ZEAL)), _msg_)

#define EFAT_POSTCONDITION_ZERO_OR_CLASSC( _pobj_ ) EFAT_POSTCONDITION_ZERO_OR_CLASS( (_pobj_), "postcondition, class pointer (" #_pobj_ ") is zero or valid" )

#define EFAT_LOOP_INVARIANT_ZERO_OR_CLASS( _pobj_, _msg_) EFAT_LOOP_INVARIANT( ((0 == (_pobj_)) || (_pobj_)->check_this(EFAT_ASSERT_CLASS_ZEAL)), _msg_)

#define EFAT_LOOP_INVARIANT_ZERO_OR_CLASSC( _pobj_ ) EFAT_LOOP_INVARIANT_ZERO_OR_CLASS( (_pobj_), "loop invariant, class pointer (" #_pobj_ ") is zero or valid" )

#endif // __cplusplus

#ifdef DBG_INFRA_DEBUG_INVARIANTS

#define EFAT_INVARIANT( _bool_, _msg_ ) \
        EFAT_MACRO_START                 \
        if ( ! ( _bool_ ) )             \
            EFAT_ASSERT_DOCALL( _msg_ ); \
        EFAT_MACRO_END

#define EFAT_INVARIANTC( _bool_ )       \
        EFAT_MACRO_START                 \
        if ( ! ( _bool_ ) )             \
            EFAT_ASSERT_DOCALL( "invariant (" #_bool_ ")" ); \
        EFAT_MACRO_END

#else  // !DBG_INFRA_DEBUG_INVARIANTS

#define EFAT_INVARIANT( _bool_, _msg_ ) EFAT_EMPTY_STATEMENT
#define EFAT_INVARIANTC( _bool_ )       EFAT_EMPTY_STATEMENT

#ifdef __cplusplus

#define EFAT_INVARIANT_CLASS( _type_, _pobj_, _msg_ )
#define EFAT_INVARIANT_CLASSC( _type_, _pobj_ )
#define EFAT_INVARIANT_CLASSO( _type_, _obj_, _msg_ )
#define EFAT_INVARIANT_CLASSOC( _type_, _obj_ )
#define EFAT_INVARIANT_THIS( _type_, _msg_ )
#define EFAT_INVARIANT_THISC( _type_ )

#endif

#endif // DBG_INFRA_DEBUG_INVARIANTS

// -------------------------------------------------------------------------

#define EFAT_COMPILETIMEFAIL( _msg_ ) !!!-- _msg_ --!!!

#ifdef EFAT_DECLARE_HOST_ASSERTION_SUPPORT

externC void efat_assert_install_failure_handler(
                bool (*)(const char* /* psz_func */,
                         const char* /* psz_file */,
                         efat_uint32  /* linenum */,
                         const char* /* psz_msg */) );

externC void efat_assert_install_failure_callback(
                const char* /* name */,
                void (*)( void (*)(const char*) ));

externC void efat_assert_failure_invoke_callbacks(
                void (*)(const char* /* name */),
                void (*)(const char* /* callback data */ ),
                void (*)(void) );

externC void efat_assert_quickfail(void);

#endif // EFAT_DECLARE_HOST_ASSERTION_SUPPORT

// -------------------------------------------------------------------------

#endif // ONCE_INFRA_EFAT_ASS_H multiple inclusion protection
// EOF efat_ass.h
