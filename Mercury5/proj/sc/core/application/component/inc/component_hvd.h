//------------------------------------------------------------------------------
//
//  File        : component_hvd.h
//  Description : Header file of hvd configuration
//  Author      : Tunglin
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _COMPONENT_HVD_H_
#define _COMPONENT_HVD_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmp_component_ctl.h"
#include "mmp_vidplay_inc.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================

#define COMP_HVD_CODE_AD_ALIGN       (2048) //2048 align
#define COMP_HVD_CODE_BF_SZ          (0xC0000) // [1M:768K]/[0x10_0000:0xC_0000]

// ES buffer is allocated in MMPF_Player_ConfigVideoDecMem()
#define COMP_HVD_ES_AD_ALIGN         (8) //8 align
#define COMP_HVD_ES_BF_SZ            (2 * 1024 * 1024) //M5:Maxium = 2M

#define COMP_HVD_FB_AD_ALIGN         (512) //512 align
#define COMP_HVD_FB_BF_SZ            (20 * 1024 * 1024)

#define UV_SZ_HW_LIMIT_MASK          (0xFFC00000) // MV5: hw uv register maxium size: 0x3F_FFFF

#define COMP_HVD_DBG_EN              (0)
#define ALOC_NON_CACHE_FB            (1)

#define DBG_MSG_TRACE(En)  \
        if (En)            \
        {                  \
            UartSendTrace( "TRACE:%s ; %s ; %d \n" , __FILE__ , __FUNCTION__, __LINE__); \
        }                  \

//==============================================================================
//
//                              ENUMERATION
//
//==============================================================================

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMP_COMPONENT_HANDLER_HVD
{
    MMP_ULONG  ulIsUtMode;
    MMP_ULONG  ulIsInitialDone;
    MMP_ULONG  ulSize;
    MMP_ULONG  ulTimestamp;
    MMP_ULONG  *pGetFrmInf;
} MMP_COMPONENT_HANDLER_HVD;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_COMPONENT_BASE Component_HVD;

extern MMP_COMPONENT_HANDLER_HVD Component_HVD_Handler[];
extern MMP_COMPONENT_MEMORY_INFO Component_HVD_Memory[];

// Extern Function of Port:
extern MMP_COMPONENT_PORT_INFO ComponentPort_HVD[];

//==============================================================================
//
//                              FUNCTION
//
//==============================================================================

#endif // _COMPONENT_HVD_H_

