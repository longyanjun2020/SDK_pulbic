#ifndef audio_typedef_h
#define audio_typedef_h

//#include "includes_fw.h"

typedef signed char Word8;
typedef unsigned char UWord8;
typedef short Word16;
typedef unsigned short UWord16;
typedef int Word32;
typedef unsigned int UWord32;

typedef int Flag;


typedef unsigned int Word32u;
typedef unsigned short Word16u;
typedef unsigned char Word8u;

#ifndef NULL
#define NULL    (void *)0
#endif

//---------------------------------
// define types for WMA play mode
//---------------------------------
#if (WMA_EN)
#ifndef _BOOL_DEFINED
#define _BOOL_DEFINED
typedef long BOOL;
#endif /* _BOOL_DEFINED */

#ifndef _BYTE_DEFINED
#define _BYTE_DEFINED
typedef unsigned char   BYTE;
#endif /* _BYTE_DEFINED */

#ifndef _WORD_DEFINED
#define _WORD_DEFINED
typedef unsigned short  WORD;
#endif /* _WORD_DEFINED */

#ifndef _DWORD_DEFINED
#define _DWORD_DEFINED
typedef unsigned long    DWORD; /* actually long, but this should be okay */
#endif /* _DWORD_DEFINED */


#ifndef _QWORD_DEFINED
#define _QWORD_DEFINED
typedef struct tQWORD
{
    DWORD   dwLo;
    DWORD   dwHi;

}   QWORD;
#endif /* _QWORD_DEFINED */

#ifndef TRUE
#define TRUE  1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#endif  // end of wma play define


//---------------------------------
// define types for OGG play mode
//---------------------------------
#if (OGG_EN)
typedef __int64 ogg_int64_t;
typedef int ogg_int32_t;
typedef unsigned int ogg_uint32_t;
typedef short ogg_int16_t;
typedef unsigned short ogg_uint16_t;
#endif
//---------------------------------
// define types for RA play mode
//---------------------------------
#if (RA_EN)
typedef char INT8;
typedef INT8 CHAR;
typedef unsigned char UINT8;
//typedef UINT8 BYTE;
typedef short int INT16;
typedef unsigned short int UINT16;
//typedef long int INT32;
//typedef unsigned long int UINT32;
typedef int HXBOOL;
#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define HXNULL ((void *)0)

#endif //(RA_EN)
#endif /* MMPF_AUDIO_TYPEDEF_H */
