#ifndef ONCE_INFRA_EFAT_TRAC_H
#define ONCE_INFRA_EFAT_TRAC_H
////////////////////////////////////////////////////////////////////////////////
///@file infra_trace.h
///@author MStar Semiconductor Inc.
///@brief
////////////////////////////////////////////////////////////////////////////////

#include <pkgconf_infra.h>
#include <infra_ass.h>

// -------------------------------------------------------------------------
// DBG_INFRA_DEBUG_FUNCTION_PSEUDOMACRO is dealt with in efat_ass.h.
// -------------------------------------------------------------------------

#ifdef DBG_USE_TRACING

// these are executed to deal with tracing - breakpoint?

externC void
efat_tracenomsg( const char *psz_func, const char *psz_file, efat_uint32 linenum );

externC void
efat_trace_dump(void);

#define EFAT_TRACE_DUMP() efat_trace_dump()

#ifdef DBG_INFRA_DEBUG_TRACE_ASSERT_BUFFER

externC void
efat_trace_print(void);

#define EFAT_TRACE_PRINT() efat_trace_print()

#else
#define EFAT_TRACE_PRINT() EFAT_EMPTY_STATEMENT
#endif

// provide every other one of these as a space/caller bloat compromise.

# ifdef DBG_INFRA_DEBUG_TRACE_MESSAGE

enum efat_trace_what{
    efat_trace_trace = 0,
    efat_trace_enter,
    efat_trace_args,
    efat_trace_return,
};

externC void
efat_tracemsg( efat_uint32 what, const char *psz_func, const char *psz_file, efat_uint32 linenum, const char *psz_msg );

externC void
efat_tracemsg6( efat_uint32 what, const char *psz_func, const char *psz_file, efat_uint32 linenum, const char *psz_msg, EFAT_ADDRWORD arg0,  EFAT_ADDRWORD arg1, EFAT_ADDRWORD arg2,  EFAT_ADDRWORD arg3, EFAT_ADDRWORD arg4,  EFAT_ADDRWORD arg5 );
externC void
efat_tracemsg8( efat_uint32 what, const char *psz_func, const char *psz_file, efat_uint32 linenum, const char *psz_msg, EFAT_ADDRWORD arg0,  EFAT_ADDRWORD arg1, EFAT_ADDRWORD arg2,  EFAT_ADDRWORD arg3, EFAT_ADDRWORD arg4,  EFAT_ADDRWORD arg5, EFAT_ADDRWORD arg6,  EFAT_ADDRWORD arg7 );

externC void
efat_tracemsg2( efat_uint32 what, const char *psz_func, const char *psz_file, efat_uint32 linenum, const char *psz_msg, EFAT_ADDRWORD arg0,  EFAT_ADDRWORD arg1 );
externC void
efat_tracemsg4( efat_uint32 what, const char *psz_func, const char *psz_file, efat_uint32 linenum, const char *psz_msg, EFAT_ADDRWORD arg0,  EFAT_ADDRWORD arg1, EFAT_ADDRWORD arg2,  EFAT_ADDRWORD arg3 );

#endif // DBG_INFRA_DEBUG_TRACE_MESSAGE

// -------------------------------------------------------------------------

# ifndef DBG_INFRA_DEBUG_TRACE_MESSAGE

#  define EFAT_TRACE_docall0( _msg_ )                                    \
    efat_tracenomsg( __PRETTY_FUNCTION__, __FILE__, __LINE__ );

#  define EFAT_TRACE_docall2( _msg_, _arg0_, _arg1_ )                    \
    efat_tracenomsg( __PRETTY_FUNCTION__, __FILE__, __LINE__ );

#  define EFAT_TRACE_docall4( _msg_, _arg0_, _arg1_ , _arg2_, _arg3_  )  \
    efat_tracenomsg( __PRETTY_FUNCTION__, __FILE__, __LINE__ );

#  define EFAT_TRACE_docall6( _msg_, _arg0_, _arg1_ , _arg2_, _arg3_,    \
                                    _arg4_, _arg5_                   )  \
    efat_tracenomsg( __PRETTY_FUNCTION__, __FILE__, __LINE__ );

#  define EFAT_TRACE_docall8( _msg_, _arg0_, _arg1_, _arg2_, _arg3_,     \
                                    _arg4_, _arg5_, _arg6_, _arg7_   )  \
    efat_tracenomsg( __PRETTY_FUNCTION__, __FILE__, __LINE__ );

# else // do not DBG_INFRA_DEBUG_TRACE_MESSAGE

#  define EFAT_TRACE_docall0( _msg_ )                                    \
    efat_tracemsg( efat_trace_trace,                                      \
                  __PRETTY_FUNCTION__, __FILE__, __LINE__, _msg_ );

#  define EFAT_TRACE_docall2( _msg_, _arg0_, _arg1_ )                    \
    efat_tracemsg2( efat_trace_trace,                                     \
                   __PRETTY_FUNCTION__, __FILE__, __LINE__, _msg_,      \
                 (EFAT_ADDRWORD)_arg0_, (EFAT_ADDRWORD)_arg1_ );

#  define EFAT_TRACE_docall4( _msg_, _arg0_, _arg1_ , _arg2_, _arg3_  )  \
    efat_tracemsg4( efat_trace_trace,                                     \
                   __PRETTY_FUNCTION__, __FILE__, __LINE__, _msg_,      \
                 (EFAT_ADDRWORD)_arg0_, (EFAT_ADDRWORD)_arg1_,            \
                 (EFAT_ADDRWORD)_arg2_, (EFAT_ADDRWORD)_arg3_ );

#  define EFAT_TRACE_docall6( _msg_, _arg0_, _arg1_ , _arg2_, _arg3_,    \
                                    _arg4_, _arg5_                   )  \
    efat_tracemsg6( efat_trace_trace,                                     \
                   __PRETTY_FUNCTION__, __FILE__, __LINE__, _msg_,      \
                 (EFAT_ADDRWORD)_arg0_, (EFAT_ADDRWORD)_arg1_,            \
                 (EFAT_ADDRWORD)_arg2_, (EFAT_ADDRWORD)_arg3_,            \
                 (EFAT_ADDRWORD)_arg4_, (EFAT_ADDRWORD)_arg5_ );

#  define EFAT_TRACE_docall8( _msg_, _arg0_, _arg1_ , _arg2_, _arg3_,    \
                                    _arg4_,  _arg5_, _arg6_, _arg7_ )   \
    efat_tracemsg8( efat_trace_trace,                                     \
                   __PRETTY_FUNCTION__, __FILE__, __LINE__, _msg_,      \
                 (EFAT_ADDRWORD)_arg0_, (EFAT_ADDRWORD)_arg1_,            \
                 (EFAT_ADDRWORD)_arg2_, (EFAT_ADDRWORD)_arg3_,            \
                 (EFAT_ADDRWORD)_arg4_, (EFAT_ADDRWORD)_arg5_,            \
                 (EFAT_ADDRWORD)_arg6_, (EFAT_ADDRWORD)_arg7_ );

#endif

// -------------------------------------------------------------------------

#define EFAT_TRACE8( _bool_, _msg_, a, b, c, d, e, f, g, h )     \
    EFAT_MACRO_START                                             \
    if ( ( _bool_ ) )                                           \
        EFAT_TRACE_docall8( _msg_, a, b, c, d, e, f, g, h );     \
    EFAT_MACRO_END

#define EFAT_TRACE7( _bool_, _msg_, a, b, c, d, e, f, g )        \
        EFAT_MACRO_START                                             \
        if ( ( _bool_ ) )                                           \
            EFAT_TRACE_docall8( _msg_, a, b, c, d, e, f, g, 0 );     \
        EFAT_MACRO_END

#define EFAT_TRACE6( _bool_, _msg_, a, b, c, d, e, f )           \
        EFAT_MACRO_START                                             \
        if ( ( _bool_ ) )                                           \
            EFAT_TRACE_docall6( _msg_, a, b, c, d, e, f );           \
        EFAT_MACRO_END

#define EFAT_TRACE5( _bool_, _msg_, a, b, c, d, e )              \
            EFAT_MACRO_START                                             \
            if ( ( _bool_ ) )                                           \
                EFAT_TRACE_docall6( _msg_, a, b, c, d, e, 0 );           \
            EFAT_MACRO_END

#define EFAT_TRACE4( _bool_, _msg_, a, b, c, d )                 \
        EFAT_MACRO_START                                             \
        if ( ( _bool_ ) )                                           \
            EFAT_TRACE_docall4( _msg_, a, b, c, d );                 \
        EFAT_MACRO_END

#define EFAT_TRACE3( _bool_, _msg_, a, b, c )                    \
        EFAT_MACRO_START                                             \
        if ( ( _bool_ ) )                                           \
            EFAT_TRACE_docall4( _msg_, a, b, c, 0 );                 \
        EFAT_MACRO_END

#define EFAT_TRACE2( _bool_, _msg_, a, b )                       \
            EFAT_MACRO_START                                             \
            if ( ( _bool_ ) )                                           \
                EFAT_TRACE_docall2( _msg_, a, b );                       \
            EFAT_MACRO_END

#define EFAT_TRACE1( _bool_, _msg_, a )                          \
        EFAT_MACRO_START                                             \
        if ( ( _bool_ ) )                                           \
            EFAT_TRACE_docall2( _msg_, a, 0 );                       \
        EFAT_MACRO_END

#define EFAT_TRACE0( _bool_, _msg_ )                             \
        EFAT_MACRO_START                                             \
        if ( ( _bool_ ) )                                           \
            EFAT_TRACE_docall0( _msg_ );                             \
        EFAT_MACRO_END


// -------------------------------------------------------------------------

#ifdef DBG_INFRA_DEBUG_FUNCTION_REPORTS

struct Efat_TraceFunction_Report_
{
    int   cond;
    char *func;
    char *file; /* not strictly needed in plain 'C' */
    efat_uint32 lnum; /* nor this */
#ifdef DBG_INFRA_DEBUG_TRACE_MESSAGE
    char *exitmsg;
    EFAT_ADDRWORD exitvalue;
    int exitset;
#endif

};

#ifdef DBG_INFRA_DEBUG_TRACE_MESSAGE

#define EFAT_REPORT_FUNCTION_ENTER_INTERNAL() EFAT_MACRO_START            \
  if ( efat_tracefunction_report_.cond )                                 \
    efat_tracemsg( efat_trace_enter,                                      \
                  efat_tracefunction_report_.func,                       \
                  efat_tracefunction_report_.file,                       \
                  efat_tracefunction_report_.lnum,                       \
                  "enter" );                                            \
EFAT_MACRO_END

#define EFAT_REPORT_FUNCTION_CONSTRUCT( _c_, _fn_,_fl_,_l_,_xm_,_xv_,_xs_ ) \
        { _c_, _fn_, _fl_, _l_, _xm_, _xv_, _xs_ }

#else // do not DBG_INFRA_DEBUG_TRACE_MESSAGE

#define EFAT_REPORT_FUNCTION_ENTER_INTERNAL() EFAT_MACRO_START            \
  if ( efat_tracefunction_report_.cond )                                 \
    efat_tracenomsg( efat_tracefunction_report_.func,                     \
                    efat_tracefunction_report_.file,                     \
                    efat_tracefunction_report_.lnum );                   \
EFAT_MACRO_END

#define EFAT_REPORT_FUNCTION_CONSTRUCT( _c_, _fn_,_fl_,_l_,_xm_,_xv_,_xs_ ) \
        { _c_, _fn_, _fl_, _l_ }

#endif // not DBG_INFRA_DEBUG_TRACE_MESSAGE

#define EFAT_REPORT_FUNCTION()                                           \
    struct Efat_TraceFunction_Report_ efat_tracefunction_report_ =        \
    EFAT_REPORT_FUNCTION_CONSTRUCT(                                      \
        1, __PRETTY_FUNCTION__, __FILE__, __LINE__, NULL, 0, 0 );       \
    EFAT_REPORT_FUNCTION_ENTER_INTERNAL()

#define EFAT_REPORT_FUNCNAMETYPE( _name_, _exitmsg_  )                   \
    struct Efat_TraceFunction_Report_ efat_tracefunction_report_ =        \
    EFAT_REPORT_FUNCTION_CONSTRUCT(                                      \
        1, _name_, __FILE__, __LINE__, _exitmsg_, 0, 0 );               \
    EFAT_REPORT_FUNCTION_ENTER_INTERNAL()

#define EFAT_REPORT_FUNCNAME( _name_ )                                   \
    struct Efat_TraceFunction_Report_ efat_tracefunction_report_ =        \
    EFAT_REPORT_FUNCTION_CONSTRUCT(                                      \
        1, _name_, __FILE__, __LINE__, NULL, 0, 0 );                    \
    EFAT_REPORT_FUNCTION_ENTER_INTERNAL()

#define EFAT_REPORT_FUNCTYPE( _exitmsg_ )                                \
    struct Efat_TraceFunction_Report_ efat_tracefunction_report_ =        \
    EFAT_REPORT_FUNCTION_CONSTRUCT(                                      \
        1, __PRETTY_FUNCTION__, __FILE__, __LINE__, _exitmsg_, 0, 0 );  \
    EFAT_REPORT_FUNCTION_ENTER_INTERNAL()

// These are conditioned on macro EFAT_REPORT_USER_BOOL
#define EFAT_REPORT_FUNCTIONC()                                          \
    struct Efat_TraceFunction_Report_ efat_tracefunction_report_ =        \
    EFAT_REPORT_FUNCTION_CONSTRUCT(                                      \
        EFAT_REPORT_USER_BOOL,                                           \
        __PRETTY_FUNCTION__, __FILE__, __LINE__, NULL, 0, 0 );          \
    EFAT_REPORT_FUNCTION_ENTER_INTERNAL()

#define EFAT_REPORT_FUNCNAMEC( _name_ )                                  \
    struct Efat_TraceFunction_Report_ efat_tracefunction_report_ =        \
    EFAT_REPORT_FUNCTION_CONSTRUCT(                                      \
        EFAT_REPORT_USER_BOOL,                                           \
        _name_, __FILE__, __LINE__, NULL, 0, 0 );                       \
    EFAT_REPORT_FUNCTION_ENTER_INTERNAL()

#define EFAT_REPORT_FUNCTYPEC( _exitmsg_ )                               \
    struct Efat_TraceFunction_Report_ efat_tracefunction_report_ =        \
    EFAT_REPORT_FUNCTION_CONSTRUCT(                                      \
        EFAT_REPORT_USER_BOOL,                                           \
        __PRETTY_FUNCTION__, __FILE__, __LINE__, _exitmsg_, 0, 0 );     \
    EFAT_REPORT_FUNCTION_ENTER_INTERNAL()

#define EFAT_REPORT_FUNCNAMETYPEC( _name_, _exitmsg_  )                  \
    struct Efat_TraceFunction_Report_ efat_tracefunction_report_ =        \
    EFAT_REPORT_FUNCTION_CONSTRUCT(                                      \
        EFAT_REPORT_USER_BOOL,                                           \
        _name_, __FILE__, __LINE__, _exitmsg_, 0, 0 );                  \
    EFAT_REPORT_FUNCTION_ENTER_INTERNAL()

#ifndef DBG_INFRA_DEBUG_TRACE_MESSAGE

#define EFAT_REPORT_RETURN() EFAT_MACRO_START                             \
    efat_tracefunction_report_.lnum = __LINE__;                          \
    if ( efat_tracefunction_report_.cond )                               \
      efat_tracenomsg( efat_tracefunction_report_.func,                   \
                      efat_tracefunction_report_.file,                   \
                      efat_tracefunction_report_.lnum );                 \
EFAT_MACRO_END

#define EFAT_REPORT_RETVAL( _value_ ) EFAT_MACRO_START                    \
    EFAT_REPORT_RETURN();                                                \
EFAT_MACRO_END

#else // do not DBG_INFRA_DEBUG_TRACE_MESSAGE

#define EFAT_REPORT_RETVAL( _value_ ) EFAT_MACRO_START                    \
    EFAT_ASSERT( 0 == efat_tracefunction_report_.exitset,                 \
                "exitvalue used when arg already set" );                \
    efat_tracefunction_report_.lnum = __LINE__;                          \
    efat_tracefunction_report_.exitvalue = (EFAT_ADDRWORD)(_value_);      \
    efat_tracefunction_report_.exitset = 1;                              \
    if ( efat_tracefunction_report_.cond )                               \
      efat_tracemsg2( efat_trace_return,                                  \
                     efat_tracefunction_report_.func,                    \
                     efat_tracefunction_report_.file,                    \
                     efat_tracefunction_report_.lnum,                    \
                     efat_tracefunction_report_.exitmsg ?                \
                        efat_tracefunction_report_.exitmsg :             \
                        "return %08x",                                  \
                     efat_tracefunction_report_.exitvalue, 0 );          \
EFAT_MACRO_END

#define EFAT_REPORT_RETURN() EFAT_MACRO_START                             \
        EFAT_ASSERT( NULL == efat_tracefunction_report_.exitmsg,              \
                    "exitvoid used in typed function" );                    \
        EFAT_ASSERT( 0 == efat_tracefunction_report_.exitset,                 \
                    "exitvoid used when arg already set" );                 \
        efat_tracefunction_report_.lnum = __LINE__;                          \
        efat_tracefunction_report_.exitset = 2;                              \
        if ( efat_tracefunction_report_.cond )                               \
          efat_tracemsg( efat_trace_return,                                   \
                        efat_tracefunction_report_.func,                     \
                        efat_tracefunction_report_.file,                     \
                        efat_tracefunction_report_.lnum,                     \
                        "return void" );                                    \
EFAT_MACRO_END

#endif // not DBG_INFRA_DEBUG_TRACE_MESSAGE

#ifdef DBG_INFRA_DEBUG_TRACE_MESSAGE



#define EFAT_REPORT_FUNCARGVOID() EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG1( _format_, a ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG2( _format_, a,b ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG3( _format_, a,b,c ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG4( _format_, a,b,c,d ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG5( _format_, a,b,c,d,e ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG6( _format_, a,b,c,d,e,f ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG7( _format_, a,b,c,d,e,f,g ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG8( _format_, a,b,c,d,e,f,g,h ) EFAT_EMPTY_STATEMENT

#else // do not DBG_INFRA_DEBUG_TRACE_MESSAGE

#define EFAT_REPORT_FUNCARG1( _format_, a ) EFAT_MACRO_START              \
  if ( efat_tracefunction_report_.cond )                                 \
    efat_tracemsg2( efat_trace_args,                                      \
                   efat_tracefunction_report_.func,                      \
                   efat_tracefunction_report_.file,                      \
                   efat_tracefunction_report_.lnum,                      \
                   (_format_),                                          \
                   (EFAT_ADDRWORD)a      , 0                             \
                   );                                                   \
EFAT_MACRO_END

#define EFAT_REPORT_FUNCARGVOID() EFAT_MACRO_START                        \
  if ( efat_tracefunction_report_.cond )                                 \
    efat_tracemsg(  efat_trace_args,                                      \
                   efat_tracefunction_report_.func,                      \
                   efat_tracefunction_report_.file,                      \
                   efat_tracefunction_report_.lnum,                      \
                   "(void)"                                             \
                   );                                                   \
EFAT_MACRO_END

#define EFAT_REPORT_FUNCARG3( _format_, a,b,c ) EFAT_MACRO_START          \
    if ( efat_tracefunction_report_.cond )                                 \
      efat_tracemsg4( efat_trace_args,                                      \
                     efat_tracefunction_report_.func,                      \
                     efat_tracefunction_report_.file,                      \
                     efat_tracefunction_report_.lnum,                      \
                     (_format_),                                          \
                     (EFAT_ADDRWORD)a, (EFAT_ADDRWORD)b,                    \
                     (EFAT_ADDRWORD)c      , 0                             \
                     );                                                   \
  EFAT_MACRO_END

#define EFAT_REPORT_FUNCARG2( _format_, a,b ) EFAT_MACRO_START            \
  if ( efat_tracefunction_report_.cond )                                 \
    efat_tracemsg2( efat_trace_args,                                      \
                   efat_tracefunction_report_.func,                      \
                   efat_tracefunction_report_.file,                      \
                   efat_tracefunction_report_.lnum,                      \
                   (_format_),                                          \
                   (EFAT_ADDRWORD)a, (EFAT_ADDRWORD)b                     \
                   );                                                   \
EFAT_MACRO_END

#define EFAT_REPORT_FUNCARG5( _format_, a,b,c,d,e ) EFAT_MACRO_START      \
    if ( efat_tracefunction_report_.cond )                                 \
      efat_tracemsg6( efat_trace_args,                                      \
                     efat_tracefunction_report_.func,                      \
                     efat_tracefunction_report_.file,                      \
                     efat_tracefunction_report_.lnum,                      \
                     (_format_),                                          \
                     (EFAT_ADDRWORD)a, (EFAT_ADDRWORD)b,                    \
                     (EFAT_ADDRWORD)c, (EFAT_ADDRWORD)d,                    \
                     (EFAT_ADDRWORD)e      , 0                             \
                     );                                                   \
  EFAT_MACRO_END

#define EFAT_REPORT_FUNCARG4( _format_, a,b,c,d ) EFAT_MACRO_START        \
  if ( efat_tracefunction_report_.cond )                                 \
    efat_tracemsg4( efat_trace_args,                                      \
                   efat_tracefunction_report_.func,                      \
                   efat_tracefunction_report_.file,                      \
                   efat_tracefunction_report_.lnum,                      \
                   (_format_),                                          \
                   (EFAT_ADDRWORD)a, (EFAT_ADDRWORD)b,                    \
                   (EFAT_ADDRWORD)c, (EFAT_ADDRWORD)d                     \
                   );                                                   \
EFAT_MACRO_END

#define EFAT_REPORT_FUNCARG7( _format_, a,b,c,d,e,f,g ) EFAT_MACRO_START  \
    if ( efat_tracefunction_report_.cond )                                 \
      efat_tracemsg8( efat_trace_args,                                      \
                     efat_tracefunction_report_.func,                      \
                     efat_tracefunction_report_.file,                      \
                     efat_tracefunction_report_.lnum,                      \
                     (_format_),                                          \
                     (EFAT_ADDRWORD)a, (EFAT_ADDRWORD)b,                    \
                     (EFAT_ADDRWORD)c, (EFAT_ADDRWORD)d,                    \
                     (EFAT_ADDRWORD)e, (EFAT_ADDRWORD)f,                    \
                     (EFAT_ADDRWORD)g      , 0                             \
                     );                                                   \
  EFAT_MACRO_END

#define EFAT_REPORT_FUNCARG6( _format_, a,b,c,d,e,f ) EFAT_MACRO_START    \
  if ( efat_tracefunction_report_.cond )                                 \
    efat_tracemsg6( efat_trace_args,                                      \
                   efat_tracefunction_report_.func,                      \
                   efat_tracefunction_report_.file,                      \
                   efat_tracefunction_report_.lnum,                      \
                   (_format_),                                          \
                   (EFAT_ADDRWORD)a, (EFAT_ADDRWORD)b,                    \
                   (EFAT_ADDRWORD)c, (EFAT_ADDRWORD)d,                    \
                   (EFAT_ADDRWORD)e, (EFAT_ADDRWORD)f                     \
                   );                                                   \
EFAT_MACRO_END

#define EFAT_REPORT_FUNCARG8( _format_, a,b,c,d,e,f,g,h ) EFAT_MACRO_START\
  if ( efat_tracefunction_report_.cond )                                 \
    efat_tracemsg8( efat_trace_args,                                      \
                   efat_tracefunction_report_.func,                      \
                   efat_tracefunction_report_.file,                      \
                   efat_tracefunction_report_.lnum,                      \
                   (_format_),                                          \
                   (EFAT_ADDRWORD)a, (EFAT_ADDRWORD)b,                    \
                   (EFAT_ADDRWORD)c, (EFAT_ADDRWORD)d,                    \
                   (EFAT_ADDRWORD)e, (EFAT_ADDRWORD)f,                    \
                   (EFAT_ADDRWORD)g, (EFAT_ADDRWORD)h                     \
                   );                                                   \
EFAT_MACRO_END

#endif  // not DBG_INFRA_DEBUG_TRACE_MESSAGE

#else   // no DBG_INFRA_DEBUG_FUNCTION_REPORTS


#define EFAT_REPORT_FUNCARGVOID() EFAT_EMPTY_STATEMENT
//separate

#define EFAT_REPORT_FUNCARG1( _format_, a ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG2( _format_, a,b ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG3( _format_, a,b,c ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG4( _format_, a,b,c,d ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG5( _format_, a,b,c,d,e ) EFAT_EMPTY_STATEMENT
//separate
#define EFAT_REPORT_FUNCARG6( _format_, a,b,c,d,e,f ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG7( _format_, a,b,c,d,e,f,g ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG8( _format_, a,b,c,d,e,f,g,h ) EFAT_EMPTY_STATEMENT
//separate

#define EFAT_REPORT_FUNCTIONC()                          EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCTYPEC( _exitmsg_ )               EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCNAMEC( _name_ )                  EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCNAMETYPEC( _name_, _exitmsg_  )  EFAT_EMPTY_STATEMENT
//separate

#define EFAT_REPORT_RETURN()                             EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_RETVAL( _value_ )                    EFAT_EMPTY_STATEMENT
//separate

#define EFAT_REPORT_FUNCTION()                           EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCTYPE( _exitmsg_ )                EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCNAME( _name_ )                   EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCNAMETYPE( _name_, _exitmsg_  )   EFAT_EMPTY_STATEMENT

#endif  // DBG_INFRA_DEBUG_FUNCTION_REPORTS

#else   // ! DBG_USE_TRACING

// -------------------------------------------------------------------------
// No traces: we define empty statements for trace macros.

#define EFAT_TRACE0( _bool_, _msg_  ) EFAT_EMPTY_STATEMENT
#define EFAT_TRACE1( _bool_, _msg_, a ) EFAT_EMPTY_STATEMENT
#define EFAT_TRACE2( _bool_, _msg_, a,b ) EFAT_EMPTY_STATEMENT
#define EFAT_TRACE3( _bool_, _msg_, a,b,c ) EFAT_EMPTY_STATEMENT
#define EFAT_TRACE4( _bool_, _msg_, a,b,c,d ) EFAT_EMPTY_STATEMENT
#define EFAT_TRACE5( _bool_, _msg_, a,b,c,d,e ) EFAT_EMPTY_STATEMENT
//separate

#define EFAT_REPORT_FUNCTION()                           EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCTYPE( _exitmsg_ )                EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCNAME( _name_ )                   EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCNAMETYPE( _name_, _exitmsg_  )   EFAT_EMPTY_STATEMENT

//separate

#define EFAT_TRACE6( _bool_, _msg_, a,b,c,d,e,f ) EFAT_EMPTY_STATEMENT
#define EFAT_TRACE7( _bool_, _msg_, a,b,c,d,e,f,g ) EFAT_EMPTY_STATEMENT
#define EFAT_TRACE8( _bool_, _msg_, a,b,c,d,e,f,g,h ) EFAT_EMPTY_STATEMENT
//separate

#define EFAT_REPORT_FUNCARGVOID() EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG1( _format_, a ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG2( _format_, a,b ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG3( _format_, a,b,c ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG4( _format_, a,b,c,d ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG5( _format_, a,b,c,d,e ) EFAT_EMPTY_STATEMENT
//separate

#define EFAT_REPORT_FUNCTIONC()                          EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCTYPEC( _exitmsg_ )               EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCNAMEC( _name_ )                  EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCNAMETYPEC( _name_, _exitmsg_  )  EFAT_EMPTY_STATEMENT
//separate

#define EFAT_REPORT_FUNCARG6( _format_, a,b,c,d,e,f ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG7( _format_, a,b,c,d,e,f,g ) EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_FUNCARG8( _format_, a,b,c,d,e,f,g,h ) EFAT_EMPTY_STATEMENT
//separate

#define EFAT_REPORT_RETURN()                             EFAT_EMPTY_STATEMENT
#define EFAT_REPORT_RETVAL( _value_ )                    EFAT_EMPTY_STATEMENT
//separate

#define EFAT_TRACE_PRINT() EFAT_EMPTY_STATEMENT
#define EFAT_TRACE_DUMP()  EFAT_EMPTY_STATEMENT

#endif // ! DBG_USE_TRACING

#define EFAT_TRACE0B( _msg_  ) EFAT_TRACE0( EFAT_TRACE_USER_BOOL, _msg_  )
#define EFAT_TRACE1B( _msg_, a ) EFAT_TRACE1( EFAT_TRACE_USER_BOOL, _msg_, a )
#define EFAT_TRACE2B( _msg_, a,b ) EFAT_TRACE2( EFAT_TRACE_USER_BOOL, _msg_, a,b )
#define EFAT_TRACE3B( _msg_, a,b,c ) EFAT_TRACE3( EFAT_TRACE_USER_BOOL, _msg_, a,b,c )
#define EFAT_TRACE4B( _msg_, a,b,c,d ) EFAT_TRACE4( EFAT_TRACE_USER_BOOL, _msg_, a,b,c,d )
//separate
#define EFAT_TRACE5B( _msg_, a,b,c,d,e ) EFAT_TRACE5( EFAT_TRACE_USER_BOOL, _msg_, a,b,c,d,e )
#define EFAT_TRACE6B( _msg_, a,b,c,d,e,f ) EFAT_TRACE6( EFAT_TRACE_USER_BOOL, _msg_, a,b,c,d,e,f )
#define EFAT_TRACE7B( _msg_, a,b,c,d,e,f,g ) EFAT_TRACE7( EFAT_TRACE_USER_BOOL, _msg_, a,b,c,d,e,f,g )
#define EFAT_TRACE8B( _msg_, a,b,c,d,e,f,g,h ) EFAT_TRACE8( EFAT_TRACE_USER_BOOL, _msg_, a,b,c,d,e,f,g,h )

// long hex versions
#define EFAT_TRACE1XV( _bool_, a ) EFAT_TRACE1( _bool_, # a "=%08x ", a )
#define EFAT_TRACE2XV( _bool_, a,b ) EFAT_TRACE2( _bool_, # a "=%08x " # b "=%08x " , a,b )
#define EFAT_TRACE3XV( _bool_, a,b,c ) EFAT_TRACE3( _bool_, # a "=%08x " # b "=%08x " # c "=%08x " , a,b,c )
#define EFAT_TRACE4XV( _bool_, a,b,c,d ) EFAT_TRACE4( _bool_, # a "=%08x " # b "=%08x " # c "=%08x " # d "=%08x " , a,b,c,d )
//separate
#define EFAT_TRACE5XV( _bool_, a,b,c,d,e ) EFAT_TRACE5( _bool_, # a "=%08x " # b "=%08x " # c "=%08x " # d "=%08x " # e "=%08x " , a,b,c,d,e )
#define EFAT_TRACE6XV( _bool_, a,b,c,d,e,f ) EFAT_TRACE6( _bool_, # a "=%08x " # b "=%08x " # c "=%08x " # d "=%08x " # e "=%08x " # f "=%08x " , a,b,c,d,e,f )
#define EFAT_TRACE7XV( _bool_, a,b,c,d,e,f,g ) EFAT_TRACE7( _bool_, # a "=%08x " # b "=%08x " # c "=%08x " # d "=%08x " # e "=%08x " # f "=%08x " # g "=%08x " , a,b,c,d,e,f,g )
#define EFAT_TRACE8XV( _bool_, a,b,c,d,e,f,g,h ) EFAT_TRACE8( _bool_, # a "=%08x " # b "=%08x " # c "=%08x " # d "=%08x " # e "=%08x " # f "=%08x " # g "=%08x " # h "=%08x " , a,b,c,d,e,f,g,h )

#define EFAT_TRACE1X( _bool_, a ) EFAT_TRACE1( _bool_, "%08x", a )
#define EFAT_TRACE2X( _bool_, a,b ) EFAT_TRACE2( _bool_, "%08x %08x", a,b )
#define EFAT_TRACE3X( _bool_, a,b,c ) EFAT_TRACE3( _bool_, "%08x %08x %08x", a,b,c )
#define EFAT_TRACE4X( _bool_, a,b,c,d ) EFAT_TRACE4( _bool_, "%08x %08x %08x %08x", a,b,c,d )
//separate

#define EFAT_TRACE5X( _bool_, a,b,c,d,e ) EFAT_TRACE5( _bool_, "%08x %08x %08x %08x %08x", a,b,c,d,e )
#define EFAT_TRACE6X( _bool_, a,b,c,d,e,f ) EFAT_TRACE6( _bool_, "%08x %08x %08x %08x %08x %08x", a,b,c,d,e,f )
#define EFAT_TRACE7X( _bool_, a,b,c,d,e,f,g ) EFAT_TRACE7( _bool_, "%08x %08x %08x %08x %08x %08x %08x", a,b,c,d,e,f,g )
#define EFAT_TRACE8X( _bool_, a,b,c,d,e,f,g,h ) EFAT_TRACE8( _bool_, "%08x %08x %08x %08x %08x %08x %08x %08x", a,b,c,d,e,f,g,h )


#define EFAT_TRACE1XB( a ) \
        EFAT_TRACE1( EFAT_TRACE_USER_BOOL, "%08x", a )
#define EFAT_TRACE2XB( a,b ) \
        EFAT_TRACE2( EFAT_TRACE_USER_BOOL, "%08x %08x", a,b )
#define EFAT_TRACE3XB( a,b,c ) \
        EFAT_TRACE3( EFAT_TRACE_USER_BOOL, "%08x %08x %08x", a,b,c )
#define EFAT_TRACE4XB( a,b,c,d ) \
        EFAT_TRACE4( EFAT_TRACE_USER_BOOL, "%08x %08x %08x %08x", a,b,c,d )
#define EFAT_TRACE5XB( a,b,c,d,e ) \
        EFAT_TRACE5( EFAT_TRACE_USER_BOOL, "%08x %08x %08x %08x %08x", a,b,c,d,e )
//separate

#define EFAT_TRACE6XB( a,b,c,d,e,f ) \
        EFAT_TRACE6( EFAT_TRACE_USER_BOOL, "%08x %08x %08x %08x %08x %08x", \
                    a,b,c,d,e,f )
#define EFAT_TRACE7XB( a,b,c,d,e,f,g ) \
        EFAT_TRACE7( EFAT_TRACE_USER_BOOL, "%08x %08x %08x %08x %08x %08x %08x", \
                    a,b,c,d,e,f,g )
#define EFAT_TRACE8XB( a,b,c,d,e,f,g,h ) \
        EFAT_TRACE8( EFAT_TRACE_USER_BOOL, "%08x %08x %08x %08x %08x %08x %08x %08x", \
                    a,b,c,d,e,f,g,h )
//separate

#define EFAT_TRACE1XVB( a ) \
        EFAT_TRACE1( EFAT_TRACE_USER_BOOL, # a "=%08x ", a )
#define EFAT_TRACE2XVB( a,b ) \
        EFAT_TRACE2( EFAT_TRACE_USER_BOOL, \
                    # a "=%08x " # b "=%08x " , a,b )
#define EFAT_TRACE3XVB( a,b,c ) \
        EFAT_TRACE3( EFAT_TRACE_USER_BOOL, \
                    # a "=%08x " # b "=%08x " # c "=%08x " , a,b,c )
#define EFAT_TRACE4XVB( a,b,c,d ) \
        EFAT_TRACE4( EFAT_TRACE_USER_BOOL, \
                    # a "=%08x " # b "=%08x " # c "=%08x " # d "=%08x " \
                    , a,b,c,d )
#define EFAT_TRACE5XVB( a,b,c,d,e ) \
        EFAT_TRACE5( EFAT_TRACE_USER_BOOL, \
                    # a "=%08x " # b "=%08x " # c "=%08x " # d "=%08x " \
                    # e "=%08x " \
                    , a,b,c,d,e )
//separate

#define EFAT_TRACE6XVB( a,b,c,d,e,f ) \
        EFAT_TRACE6( EFAT_TRACE_USER_BOOL, \
                    # a "=%08x " # b "=%08x " # c "=%08x " # d "=%08x " \
                    # e "=%08x " # f "=%08x " \
                    , a,b,c,d,e,f )
#define EFAT_TRACE7XVB( a,b,c,d,e,f,g ) \
        EFAT_TRACE7( EFAT_TRACE_USER_BOOL, \
                    # a "=%08x " # b "=%08x " # c "=%08x " # d "=%08x " \
                    # e "=%08x " # f "=%08x " # g "=%08x " \
                    , a,b,c,d,e,f,g )
#define EFAT_TRACE8XVB( a,b,c,d,e,f,g,h ) \
        EFAT_TRACE8( EFAT_TRACE_USER_BOOL, \
                    # a "=%08x " # b "=%08x " # c "=%08x " # d "=%08x " \
                    # e "=%08x " # f "=%08x " # g "=%08x " # h "=%08x " \
                    , a,b,c,d,e,f,g,h )

// decimal versions

#define EFAT_TRACE1D( _bool_, a ) EFAT_TRACE1( _bool_, "%d", a )
#define EFAT_TRACE2D( _bool_, a,b ) EFAT_TRACE2( _bool_, "%d %d", a,b )
#define EFAT_TRACE3D( _bool_, a,b,c ) EFAT_TRACE3( _bool_, "%d %d %d", a,b,c )
#define EFAT_TRACE4D( _bool_, a,b,c,d ) EFAT_TRACE4( _bool_, "%d %d %d %d", a,b,c,d )
#define EFAT_TRACE5D( _bool_, a,b,c,d,e ) EFAT_TRACE5( _bool_, "%d %d %d %d %d", a,b,c,d,e )
//separate

#define EFAT_TRACE6D( _bool_, a,b,c,d,e,f ) EFAT_TRACE6( _bool_, "%d %d %d %d %d %d", a,b,c,d,e,f )
#define EFAT_TRACE7D( _bool_, a,b,c,d,e,f,g ) EFAT_TRACE7( _bool_, "%d %d %d %d %d %d %d", a,b,c,d,e,f,g )
#define EFAT_TRACE8D( _bool_, a,b,c,d,e,f,g,h ) EFAT_TRACE8( _bool_, "%d %d %d %d %d %d %d %d", a,b,c,d,e,f,g,h )

#define EFAT_TRACE1DV( _bool_, a ) EFAT_TRACE1( _bool_, # a "=%d ", a )
#define EFAT_TRACE2DV( _bool_, a,b ) EFAT_TRACE2( _bool_, # a "=%d " # b "=%d " , a,b )
#define EFAT_TRACE3DV( _bool_, a,b,c )EFAT_TRACE3( _bool_, # a "=%d " # b "=%d " # c "=%d " , a,b,c )
#define EFAT_TRACE4DV( _bool_, a,b,c,d ) EFAT_TRACE4( _bool_, # a "=%d " # b "=%d " # c "=%d " # d "=%d " , a,b,c,d )
#define EFAT_TRACE5DV( _bool_, a,b,c,d,e ) EFAT_TRACE5( _bool_, # a "=%d " # b "=%d " # c "=%d " # d "=%d " # e "=%d " , a,b,c,d,e )

//separate

#define EFAT_TRACE6DV( _bool_, a,b,c,d,e,f ) \
        EFAT_TRACE6( _bool_, \
                    # a "=%d " # b "=%d " # c "=%d " # d "=%d " \
                    # e "=%d " # f "=%d " \
                    , a,b,c,d,e,f )
#define EFAT_TRACE7DV( _bool_, a,b,c,d,e,f,g ) \
        EFAT_TRACE7( _bool_, \
                    # a "=%d " # b "=%d " # c "=%d " # d "=%d " \
                    # e "=%d " # f "=%d " # g "=%d " \
                    , a,b,c,d,e,f,g )
#define EFAT_TRACE8DV( _bool_, a,b,c,d,e,f,g,h ) \
        EFAT_TRACE8( _bool_, \
                    # a "=%d " # b "=%d " # c "=%d " # d "=%d " \
                    # e "=%d " # f "=%d " # g "=%d " # h "=%d " \
                    , a,b,c,d,e,f,g,h )
//separate

#define EFAT_TRACE1DVB( a ) \
        EFAT_TRACE1( EFAT_TRACE_USER_BOOL, # a "=%d ", a )
#define EFAT_TRACE2DVB( a,b ) \
        EFAT_TRACE2( EFAT_TRACE_USER_BOOL, \
                    # a "=%d " # b "=%d " , a,b )
#define EFAT_TRACE3DVB( a,b,c ) \
        EFAT_TRACE3( EFAT_TRACE_USER_BOOL, \
                    # a "=%d " # b "=%d " # c "=%d " , a,b,c )
#define EFAT_TRACE4DVB( a,b,c,d ) \
        EFAT_TRACE4( EFAT_TRACE_USER_BOOL, \
                    # a "=%d " # b "=%d " # c "=%d " # d "=%d " \
                    , a,b,c,d )
#define EFAT_TRACE5DVB( a,b,c,d,e ) \
        EFAT_TRACE5( EFAT_TRACE_USER_BOOL, \
                    # a "=%d " # b "=%d " # c "=%d " # d "=%d " \
                    # e "=%d " \
                    , a,b,c,d,e )
//separate

#define EFAT_TRACE6DVB( a,b,c,d,e,f ) \
        EFAT_TRACE6( EFAT_TRACE_USER_BOOL, \
                    # a "=%d " # b "=%d " # c "=%d " # d "=%d " \
                    # e "=%d " # f "=%d " \
                    , a,b,c,d,e,f )
#define EFAT_TRACE7DVB( a,b,c,d,e,f,g ) \
        EFAT_TRACE7( EFAT_TRACE_USER_BOOL, \
                    # a "=%d " # b "=%d " # c "=%d " # d "=%d " \
                    # e "=%d " # f "=%d " # g "=%d " \
                    , a,b,c,d,e,f,g )
#define EFAT_TRACE8DVB( a,b,c,d,e,f,g,h ) \
        EFAT_TRACE8( EFAT_TRACE_USER_BOOL, \
                    # a "=%d " # b "=%d " # c "=%d " # d "=%d " \
                    # e "=%d " # f "=%d " # g "=%d " # h "=%d " \
                    , a,b,c,d,e,f,g,h )

//separate
                    
#define EFAT_TRACE1DB( a ) \
                            EFAT_TRACE1( EFAT_TRACE_USER_BOOL, "%d", a )
#define EFAT_TRACE2DB( a,b ) \
                            EFAT_TRACE2( EFAT_TRACE_USER_BOOL, "%d %d", a,b )
#define EFAT_TRACE3DB( a,b,c ) \
                            EFAT_TRACE3( EFAT_TRACE_USER_BOOL, "%d %d %d", a,b,c )
#define EFAT_TRACE4DB( a,b,c,d ) \
                            EFAT_TRACE4( EFAT_TRACE_USER_BOOL, "%d %d %d %d", a,b,c,d )
#define EFAT_TRACE5DB( a,b,c,d,e ) \
                            EFAT_TRACE5( EFAT_TRACE_USER_BOOL, "%d %d %d %d %d", a,b,c,d,e )
//separate
                    
#define EFAT_TRACE6DB( a,b,c,d,e,f ) \
                            EFAT_TRACE6( EFAT_TRACE_USER_BOOL, "%d %d %d %d %d %d", \
                                        a,b,c,d,e,f )
#define EFAT_TRACE7DB( a,b,c,d,e,f,g ) \
                            EFAT_TRACE7( EFAT_TRACE_USER_BOOL, "%d %d %d %d %d %d %d", \
                                        a,b,c,d,e,f,g )
#define EFAT_TRACE8DB( a,b,c,d,e,f,g,h ) \
                            EFAT_TRACE8( EFAT_TRACE_USER_BOOL, "%d %d %d %d %d %d %d %d", \
                                        a,b,c,d,e,f,g,h )



#define EFAT_TRACE1YV( _bool_, a ) \
        EFAT_TRACE1( _bool_, # a "=%x ", a )
#define EFAT_TRACE2YV( _bool_, a,b ) \
        EFAT_TRACE2( _bool_, \
                    # a "=%x " # b "=%x " , a,b )
#define EFAT_TRACE3YV( _bool_, a,b,c ) \
        EFAT_TRACE3( _bool_, \
                    # a "=%x " # b "=%x " # c "=%x " , a,b,c )
#define EFAT_TRACE4YV( _bool_, a,b,c,d ) \
        EFAT_TRACE4( _bool_, \
                    # a "=%x " # b "=%x " # c "=%x " # d "=%x " \
                    , a,b,c,d )
#define EFAT_TRACE5YV( _bool_, a,b,c,d,e ) \
        EFAT_TRACE5( _bool_, \
                    # a "=%x " # b "=%x " # c "=%x " # d "=%x " \
                    # e "=%x " \
                    , a,b,c,d,e )

//separate
#define EFAT_TRACE6YV( _bool_, a,b,c,d,e,f ) \
        EFAT_TRACE6( _bool_, \
                    # a "=%x " # b "=%x " # c "=%x " # d "=%x " \
                    # e "=%x " # f "=%x " \
                    , a,b,c,d,e,f )
#define EFAT_TRACE7YV( _bool_, a,b,c,d,e,f,g ) \
        EFAT_TRACE7( _bool_, \
                    # a "=%x " # b "=%x " # c "=%x " # d "=%x " \
                    # e "=%x " # f "=%x " # g "=%x " \
                    , a,b,c,d,e,f,g )
#define EFAT_TRACE8YV( _bool_, a,b,c,d,e,f,g,h ) \
        EFAT_TRACE8( _bool_, \
                    # a "=%x " # b "=%x " # c "=%x " # d "=%x " \
                    # e "=%x " # f "=%x " # g "=%x " # h "=%x " \
                    , a,b,c,d,e,f,g,h )

// short hex versions
                    
#define EFAT_TRACE1Y( _bool_, a ) \
                            EFAT_TRACE1( _bool_, "%x", a )
#define EFAT_TRACE2Y( _bool_, a,b ) \
                            EFAT_TRACE2( _bool_, "%x %x", a,b )
#define EFAT_TRACE3Y( _bool_, a,b,c ) \
                            EFAT_TRACE3( _bool_, "%x %x %x", a,b,c )
#define EFAT_TRACE4Y( _bool_, a,b,c,d ) \
                            EFAT_TRACE4( _bool_, "%x %x %x %x", a,b,c,d )
#define EFAT_TRACE5Y( _bool_, a,b,c,d,e ) \
                            EFAT_TRACE5( _bool_, "%x %x %x %x %x", a,b,c,d,e )
//separate

#define EFAT_TRACE6Y( _bool_, a,b,c,d,e,f ) \
                            EFAT_TRACE6( _bool_, "%x %x %x %x %x %x", \
                                        a,b,c,d,e,f )
#define EFAT_TRACE7Y( _bool_, a,b,c,d,e,f,g ) \
                            EFAT_TRACE7( _bool_, "%x %x %x %x %x %x %x", \
                                        a,b,c,d,e,f,g )
#define EFAT_TRACE8Y( _bool_, a,b,c,d,e,f,g,h ) \
                            EFAT_TRACE8( _bool_, "%x %x %x %x %x %x %x %x", \
                                        a,b,c,d,e,f,g,h )


#define EFAT_TRACE1YVB( a ) \
        EFAT_TRACE1( EFAT_TRACE_USER_BOOL, # a "=%x ", a )
#define EFAT_TRACE2YVB( a,b ) \
        EFAT_TRACE2( EFAT_TRACE_USER_BOOL, \
                    # a "=%x " # b "=%x " , a,b )
#define EFAT_TRACE3YVB( a,b,c ) \
        EFAT_TRACE3( EFAT_TRACE_USER_BOOL, \
                    # a "=%x " # b "=%x " # c "=%x " , a,b,c )
#define EFAT_TRACE4YVB( a,b,c,d ) \
        EFAT_TRACE4( EFAT_TRACE_USER_BOOL, \
                    # a "=%x " # b "=%x " # c "=%x " # d "=%x " \
                    , a,b,c,d )
#define EFAT_TRACE5YVB( a,b,c,d,e ) \
        EFAT_TRACE5( EFAT_TRACE_USER_BOOL, \
                    # a "=%x " # b "=%x " # c "=%x " # d "=%x " \
                    # e "=%x " \
                    , a,b,c,d,e )
//separate
#define EFAT_TRACE6YVB( a,b,c,d,e,f ) \
        EFAT_TRACE6( EFAT_TRACE_USER_BOOL, \
                    # a "=%x " # b "=%x " # c "=%x " # d "=%x " \
                    # e "=%x " # f "=%x " \
                    , a,b,c,d,e,f )
#define EFAT_TRACE7YVB( a,b,c,d,e,f,g ) \
        EFAT_TRACE7( EFAT_TRACE_USER_BOOL, \
                    # a "=%x " # b "=%x " # c "=%x " # d "=%x " \
                    # e "=%x " # f "=%x " # g "=%x " \
                    , a,b,c,d,e,f,g )
#define EFAT_TRACE8YVB( a,b,c,d,e,f,g,h ) \
        EFAT_TRACE8( EFAT_TRACE_USER_BOOL, \
                    # a "=%x " # b "=%x " # c "=%x " # d "=%x " \
                    # e "=%x " # f "=%x " # g "=%x " # h "=%x " \
                    , a,b,c,d,e,f,g,h )

#define EFAT_TRACE1YB( a ) \
                            EFAT_TRACE1( EFAT_TRACE_USER_BOOL, "%x", a )
#define EFAT_TRACE2YB( a,b ) \
                            EFAT_TRACE2( EFAT_TRACE_USER_BOOL, "%x %x", a,b )
#define EFAT_TRACE3YB( a,b,c ) \
                            EFAT_TRACE3( EFAT_TRACE_USER_BOOL, "%x %x %x", a,b,c )
#define EFAT_TRACE4YB( a,b,c,d ) \
                            EFAT_TRACE4( EFAT_TRACE_USER_BOOL, "%x %x %x %x", a,b,c,d )
#define EFAT_TRACE5YB( a,b,c,d,e ) \
                            EFAT_TRACE5( EFAT_TRACE_USER_BOOL, "%x %x %x %x %x", a,b,c,d,e )
                            
//separate
#define EFAT_TRACE6YB( a,b,c,d,e,f ) \
                            EFAT_TRACE6( EFAT_TRACE_USER_BOOL, "%x %x %x %x %x %x", \
                                        a,b,c,d,e,f )
#define EFAT_TRACE7YB( a,b,c,d,e,f,g ) \
                            EFAT_TRACE7( EFAT_TRACE_USER_BOOL, "%x %x %x %x %x %x %x", \
                                        a,b,c,d,e,f,g )
#define EFAT_TRACE8YB( a,b,c,d,e,f,g,h ) \
                            EFAT_TRACE8( EFAT_TRACE_USER_BOOL, "%x %x %x %x %x %x %x %x", \
                                        a,b,c,d,e,f,g,h )


// -------------------------------------------------------------------------

#define EFAT_REPORT_FUNCARG1X( a )  EFAT_REPORT_FUNCARG1( "%08x", a )
#define EFAT_REPORT_FUNCARG2X( a,b ) EFAT_REPORT_FUNCARG2( "%08x %08x", a,b )
#define EFAT_REPORT_FUNCARG3X( a,b,c ) EFAT_REPORT_FUNCARG3( "%08x %08x %08x", a,b,c )
#define EFAT_REPORT_FUNCARG4X( a,b,c,d ) EFAT_REPORT_FUNCARG4( "%08x %08x %08x %08x", a,b,c,d )

//separate
#define EFAT_REPORT_FUNCARG5X( a,b,c,d,e ) EFAT_REPORT_FUNCARG5( "%08x %08x %08x %08x %08x", a,b,c,d,e )
#define EFAT_REPORT_FUNCARG6X( a,b,c,d,e,f ) EFAT_REPORT_FUNCARG6( "%08x %08x %08x %08x %08x %08x", a,b,c,d,e,f )
#define EFAT_REPORT_FUNCARG7X( a,b,c,d,e,f,g ) EFAT_REPORT_FUNCARG7( "%08x %08x %08x %08x %08x %08x %08x", a,b,c,d,e,f,g )
#define EFAT_REPORT_FUNCARG8X( a,b,c,d,e,f,g,h ) EFAT_REPORT_FUNCARG8( "%08x %08x %08x %08x %08x %08x %08x %08x", a,b,c,d,e,f,g,h )


// decimal versions


#define EFAT_REPORT_FUNCARG1D( a ) \
        EFAT_REPORT_FUNCARG1( "%d", a )
#define EFAT_REPORT_FUNCARG2D( a,b ) \
        EFAT_REPORT_FUNCARG2( "%d %d", a,b )
#define EFAT_REPORT_FUNCARG3D( a,b,c ) \
        EFAT_REPORT_FUNCARG3( "%d %d %d", a,b,c )
#define EFAT_REPORT_FUNCARG4D( a,b,c,d ) \
        EFAT_REPORT_FUNCARG4( "%d %d %d %d", a,b,c,d )

//separate
#define EFAT_REPORT_FUNCARG5D( a,b,c,d,e ) \
        EFAT_REPORT_FUNCARG5( "%d %d %d %d %d", a,b,c,d,e )
#define EFAT_REPORT_FUNCARG6D( a,b,c,d,e,f ) \
        EFAT_REPORT_FUNCARG6( "%d %d %d %d %d %d", \
                    a,b,c,d,e,f )
#define EFAT_REPORT_FUNCARG7D( a,b,c,d,e,f,g ) \
        EFAT_REPORT_FUNCARG7( "%d %d %d %d %d %d %d", \
                    a,b,c,d,e,f,g )
#define EFAT_REPORT_FUNCARG8D( a,b,c,d,e,f,g,h ) \
        EFAT_REPORT_FUNCARG8( "%d %d %d %d %d %d %d %d", \
                    a,b,c,d,e,f,g,h )


#define EFAT_REPORT_FUNCARG1XV( a ) \
        EFAT_REPORT_FUNCARG1( # a "=%08x ", a )
#define EFAT_REPORT_FUNCARG2XV( a,b ) \
        EFAT_REPORT_FUNCARG2( \
                    # a "=%08x " # b "=%08x " , a,b )
#define EFAT_REPORT_FUNCARG3XV( a,b,c ) \
        EFAT_REPORT_FUNCARG3( \
                    # a "=%08x " # b "=%08x " # c "=%08x " , a,b,c )
#define EFAT_REPORT_FUNCARG4XV( a,b,c,d ) \
        EFAT_REPORT_FUNCARG4( \
                    # a "=%08x " # b "=%08x " # c "=%08x " # d "=%08x " \
                    , a,b,c,d )
#define EFAT_REPORT_FUNCARG5XV( a,b,c,d,e ) \
        EFAT_REPORT_FUNCARG5( \
                    # a "=%08x " # b "=%08x " # c "=%08x " # d "=%08x " \
                    # e "=%08x " \
                    , a,b,c,d,e )

//separate
#define EFAT_REPORT_FUNCARG6XV( a,b,c,d,e,f ) \
        EFAT_REPORT_FUNCARG6( \
                    # a "=%08x " # b "=%08x " # c "=%08x " # d "=%08x " \
                    # e "=%08x " # f "=%08x " \
                    , a,b,c,d,e,f )
#define EFAT_REPORT_FUNCARG7XV( a,b,c,d,e,f,g ) \
        EFAT_REPORT_FUNCARG7( \
                    # a "=%08x " # b "=%08x " # c "=%08x " # d "=%08x " \
                    # e "=%08x " # f "=%08x " # g "=%08x " \
                    , a,b,c,d,e,f,g )
#define EFAT_REPORT_FUNCARG8XV( a,b,c,d,e,f,g,h ) \
        EFAT_REPORT_FUNCARG8( \
                    # a "=%08x " # b "=%08x " # c "=%08x " # d "=%08x " \
                    # e "=%08x " # f "=%08x " # g "=%08x " # h "=%08x " \
                    , a,b,c,d,e,f,g,h )



#define EFAT_REPORT_FUNCARG1DV( a ) \
        EFAT_REPORT_FUNCARG1( # a "=%d ", a )
#define EFAT_REPORT_FUNCARG2DV( a,b ) \
        EFAT_REPORT_FUNCARG2( \
                    # a "=%d " # b "=%d " , a,b )
#define EFAT_REPORT_FUNCARG3DV( a,b,c ) \
        EFAT_REPORT_FUNCARG3( \
                    # a "=%d " # b "=%d " # c "=%d " , a,b,c )
#define EFAT_REPORT_FUNCARG4DV( a,b,c,d ) \
        EFAT_REPORT_FUNCARG4( \
                    # a "=%d " # b "=%d " # c "=%d " # d "=%d " \
                    , a,b,c,d )
#define EFAT_REPORT_FUNCARG5DV( a,b,c,d,e ) \
        EFAT_REPORT_FUNCARG5( \
                    # a "=%d " # b "=%d " # c "=%d " # d "=%d " \
                    # e "=%d " \
                    , a,b,c,d,e )

//separate
#define EFAT_REPORT_FUNCARG6DV( a,b,c,d,e,f ) \
        EFAT_REPORT_FUNCARG6( \
                    # a "=%d " # b "=%d " # c "=%d " # d "=%d " \
                    # e "=%d " # f "=%d " \
                    , a,b,c,d,e,f )
#define EFAT_REPORT_FUNCARG7DV( a,b,c,d,e,f,g ) \
        EFAT_REPORT_FUNCARG7( \
                    # a "=%d " # b "=%d " # c "=%d " # d "=%d " \
                    # e "=%d " # f "=%d " # g "=%d " \
                    , a,b,c,d,e,f,g )
#define EFAT_REPORT_FUNCARG8DV( a,b,c,d,e,f,g,h ) \
        EFAT_REPORT_FUNCARG8( \
                    # a "=%d " # b "=%d " # c "=%d " # d "=%d " \
                    # e "=%d " # f "=%d " # g "=%d " # h "=%d " \
                    , a,b,c,d,e,f,g,h )


#define EFAT_REPORT_FUNCARG1YV( a ) \
        EFAT_REPORT_FUNCARG1( # a "=%x ", a )
#define EFAT_REPORT_FUNCARG2YV( a,b ) \
        EFAT_REPORT_FUNCARG2( \
                    # a "=%x " # b "=%x " , a,b )
#define EFAT_REPORT_FUNCARG3YV( a,b,c ) \
        EFAT_REPORT_FUNCARG3( \
                    # a "=%x " # b "=%x " # c "=%x " , a,b,c )
#define EFAT_REPORT_FUNCARG4YV( a,b,c,d ) \
        EFAT_REPORT_FUNCARG4( \
                    # a "=%x " # b "=%x " # c "=%x " # d "=%x " \
                    , a,b,c,d )
#define EFAT_REPORT_FUNCARG5YV( a,b,c,d,e ) \
        EFAT_REPORT_FUNCARG5( \
                    # a "=%x " # b "=%x " # c "=%x " # d "=%x " \
                    # e "=%x " \
                    , a,b,c,d,e )

//separate
#define EFAT_REPORT_FUNCARG6YV( a,b,c,d,e,f ) \
        EFAT_REPORT_FUNCARG6( \
                    # a "=%x " # b "=%x " # c "=%x " # d "=%x " \
                    # e "=%x " # f "=%x " \
                    , a,b,c,d,e,f )
#define EFAT_REPORT_FUNCARG7YV( a,b,c,d,e,f,g ) \
        EFAT_REPORT_FUNCARG7( \
                    # a "=%x " # b "=%x " # c "=%x " # d "=%x " \
                    # e "=%x " # f "=%x " # g "=%x " \
                    , a,b,c,d,e,f,g )
#define EFAT_REPORT_FUNCARG8YV( a,b,c,d,e,f,g,h ) \
        EFAT_REPORT_FUNCARG8( \
                    # a "=%x " # b "=%x " # c "=%x " # d "=%x " \
                    # e "=%x " # f "=%x " # g "=%x " # h "=%x " \
                    , a,b,c,d,e,f,g,h )

                    // short hex versions
                    
#define EFAT_REPORT_FUNCARG1Y( a ) \
                            EFAT_REPORT_FUNCARG1( "%x", a )
#define EFAT_REPORT_FUNCARG2Y( a,b ) \
                            EFAT_REPORT_FUNCARG2( "%x %x", a,b )
#define EFAT_REPORT_FUNCARG3Y( a,b,c ) \
                            EFAT_REPORT_FUNCARG3( "%x %x %x", a,b,c )
#define EFAT_REPORT_FUNCARG4Y( a,b,c,d ) \
                            EFAT_REPORT_FUNCARG4( "%x %x %x %x", a,b,c,d )
#define EFAT_REPORT_FUNCARG5Y( a,b,c,d,e ) \
                            EFAT_REPORT_FUNCARG5( "%x %x %x %x %x", a,b,c,d,e )

//separate
#define EFAT_REPORT_FUNCARG6Y( a,b,c,d,e,f ) \
                            EFAT_REPORT_FUNCARG6( "%x %x %x %x %x %x", \
                                        a,b,c,d,e,f )
#define EFAT_REPORT_FUNCARG7Y( a,b,c,d,e,f,g ) \
                            EFAT_REPORT_FUNCARG7( "%x %x %x %x %x %x %x", \
                                        a,b,c,d,e,f,g )
#define EFAT_REPORT_FUNCARG8Y( a,b,c,d,e,f,g,h ) \
                            EFAT_REPORT_FUNCARG8( "%x %x %x %x %x %x %x %x", \
                                        a,b,c,d,e,f,g,h )

#endif // ONCE_INFRA_EFAT_TRAC_H multiple inclusion protection
// EOF efat_trac.h
