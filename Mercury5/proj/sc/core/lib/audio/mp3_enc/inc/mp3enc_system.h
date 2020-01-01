

/*==== Low level defines ======================================================*/

/*
  LIST OF DEFINES
  ===============

  BYTEORDER [byteorder]     Should either be set to BIG_ENDIAN or LITTLE_ENDIAN depending on the processor.
  INLINE    [prefix]        Defines the prefix for inline functions, normally _inline.
                             Skip this define if your compiler doesn't support inline functions.
*/


/*  Most systems allready have these two defines, but some doesn't
    so we have to put them here, before they are used. */

#ifndef BIG_ENDIAN
#   define          BIG_ENDIAN              4321
#endif

#ifndef LITTLE_ENDIAN
#   define          LITTLE_ENDIAN           1234
#endif


#define         BYTEORDER               LITTLE_ENDIAN
#define         INLINE                  __inline


/*____ To make sure that certain necessary defines are set... */

#ifndef INLINE
#       define INLINE
#endif

/*==== Other Global Definitions, placed here for convenience ==================*/


#ifndef FALSE
#   define         FALSE           0
#endif
#ifndef TRUE
#   define         TRUE            1
#endif

typedef     unsigned    char    uchar;

#if !defined(SYS_TYPES_H) && !defined(_SYS_TYPES_H)
#   ifndef  HAVE_USHORT
        typedef     unsigned short  ushort;
#   endif
#   ifndef  HAVE_UINT
        typedef     unsigned int    uint;
#   endif
#endif


















