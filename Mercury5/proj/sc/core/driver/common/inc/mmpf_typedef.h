//==============================================================================
//
//  File        : mmpf_typedef.h
//  Description : Type define file for A-I-T MMPF source code
//  Author      : Philip Lin
//  Revision    : 1.0
//
//==============================================================================

#ifndef _MMPF_TYPEDEF_H_
#define _MMPF_TYPEDEF_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef unsigned char   MMP_BOOL;
typedef char            MMP_BYTE;
typedef signed char     MMP_SBYTE;
typedef short           MMP_SHORT;
typedef signed short    MMP_SSHORT;
typedef int             MMP_LONG;
typedef signed int      MMP_SLONG;
typedef long long       MMP_LONG64;
typedef unsigned char   MMP_UBYTE;
typedef unsigned short  MMP_USHORT;
typedef unsigned int    MMP_ULONG;
typedef unsigned long   MMP_U_LONG;
typedef unsigned long long  MMP_ULONG64;
typedef void*           MMP_HANDLE;

// data type pointer content
typedef MMP_ULONG       MMP_VIRT;
// data type 32bit physical address
typedef MMP_ULONG       MMP_PHY;

#define MMP_TRUE        (1)
#define MMP_FALSE       (0)

//Copied from includes_fw.h
#ifndef	MEMSET
#define MEMSET(s,c,n)       memset(s,c,n)
#endif

/// Set this variable to 0
#ifndef	MEMSET0
#define MEMSET0(s)      memset(s,0,sizeof(*s))
#endif
#ifndef	MEMCPY
#define MEMCPY(d, s, c) memcpy (d, s, c)
#endif

//Copied from ait_utility.h
    #if 1//defined(ALL_FW)
    extern void printc(char *szFormat, ...);
    #define FW_DBG_EN   (0)
        #if (FW_DBG_EN)
        #define PRINTF(...) {printc(__VA_ARGS__);}
        #else
        #define PRINTF(...) {do {} while(0);}
        #endif
    #else
    #define PRINTF(...) {do {} while(0);}
    #endif
    
    #define SCANF(...) {do {} while(0);}

    /** @brief Implement some standard functions and retarget to it. */
    #define STRLEN strlen
    #define STRCPY strcpy
    #define STRCMP strcmp
    #define STRCAT strcat
    #define STRTOK strtok    
    #ifndef MEMCPY
    #define MEMCPY memcpy
    #endif
    #ifndef MEMSET
    #define MEMSET memset
    #endif
    #define MEMCMP memcmp
    #define MEMMOVE memmove
    #ifndef MCP_MMI_FLASH
    #define GETS(c) gets(c)
    #endif
    #define RAND() rand()

#define MMPF_OS_Sleep_MS(_ms)   MMPF_OS_Sleep((MMP_USHORT)(OS_TICKS_PER_SEC * ((MMP_ULONG)_ms + 500L / OS_TICKS_PER_SEC) / 1000L));

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _MMPF_TYPEDEF_H_ */
