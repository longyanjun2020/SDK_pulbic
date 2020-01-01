///////////////////////////////////////////////////////////////////////////////
// File   : wavenc_mgr_datatype.h
// Author : MStar Semiconductor Inc.(CA.Wang)
// Brief  : data type define
///////////////////////////////////////////////////////////////////////////////
#ifndef __WAVENC_MGR_DATATYPE_H__
#define __WAVENC_MGR_DATATYPE_H__


//=============================================================================
// Include Files
//=============================================================================
#include "wavenc_mgr_confg.h"



//=============================================================================
// Data Type Define
//=============================================================================
#ifdef WIN32

typedef __int64           S64 ;
typedef char              S8;
typedef unsigned char     U8;
typedef short             S16;
typedef unsigned short    U16;
typedef int               S32;
typedef unsigned int      U32;
typedef char              BOOL;
typedef signed char              ADPCM_S8;

//#define TRUE  1
//#define FALSE 0
//#define MSMERR_OK TRUE
//#define MSMERR_FALSE FALSE

#else

#ifdef ON_MONTAGE

#include "vm_types.ht"

#ifndef __WAV_S8_defined
#define  __WAV_S8_defined
typedef s8              ADPCM_S8;
#endif

#ifndef __WAV_BOOL_defined
#define  __WAV_BOOL_defined
typedef bool       BOOL;
#endif

#else

typedef long long         S64;
typedef char                S8;
typedef unsigned char     U8;
typedef short             S16;
typedef unsigned short    U16;
typedef int               S32;
typedef unsigned int      U32;
typedef int               BOOL;

#define TRUE  1
#define FALSE 0
#define MSMERR_OK TRUE
#define MSMERR_FALSE FALSE

#endif

#endif




//=============================================================================
// Compiler Option Define
//=============================================================================
#ifdef WIN32
#define WAVECN_ATTR_MIPS16
#define WAVECN_ATTR_MIPS32
#else

#ifdef ON_MONTAGE
#define WAVECN_ATTR_MIPS16    __attribute__((mips16))
#define WAVECN_ATTR_MIPS32    __attribute__((nomips16))
#else
#define WAVECN_ATTR_MIPS16    __attribute__((mips16))
#define WAVECN_ATTR_MIPS32    __attribute__((nomips16))
#endif

#endif

#endif //__WAVENC_MGR_DATATYPE_H__

