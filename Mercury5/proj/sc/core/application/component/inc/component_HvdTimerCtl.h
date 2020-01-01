//------------------------------------------------------------------------------
//
//  File        : component_timerCtl.h
//  Description : Header file of timer control configuration
//  Author      : Tunglin
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _COMPONENT_TCL_H_
#define _COMPONENT_TCL_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmp_component_ctl.h"

//==============================================================================
//
//                              MACRO DEFINE
//
//==============================================================================


#define MAX_TMC_DQNUM           (32)

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

typedef enum
{
    HTCL_COMP_DEFAULT = 0,
    HTCL_COMP_SKIP_FRM,
    HTCL_COMP_USAGE_NUM
} HTCL_COMP_USAGE;

typedef enum
{
    TCL_WPTR = 0,
    TCL_RPTR,
    TCL_PTR_NUM
} TCL_RW_PTR;

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _MMP_COMPONENT_HANDLER_TIMECTL
{
    MMP_ULONG           ulStAddr;
    MMP_ULONG           ulSize;
    MMP_ULONG           ulTimestamp;
    MMP_ULONG           ulSkipStartFrmNum;
} MMP_COMPONENT_HANDLER_TIMECTL;

typedef struct _TIMECTL_BUF_ATTR_s
{
    MMP_ULONG           nWidth;
    MMP_ULONG           nHeight;
    MMP_ULONG           ulTimeS;
    MMP_ULONG           nBaseAddrY;
} TIMECTL_BUF_ATTR_t, *PTIMECTL_BUF_ATTR;

typedef struct _TIMECTL_ATTR_s
{
    TIMECTL_BUF_ATTR_t  tSrcBufAttr;
    TIMECTL_BUF_ATTR_t  tDestBufAttr;
    MMP_BOOL            bMirror;
    MMP_BOOL            bFlip;
} TIMECTL_ATTR_t, *PTIMECTL_ATTR;

typedef struct _MMP_TIMECTL_BUFCTL
{
    MMP_ULONG           lVBuf[MAX_TMC_DQNUM];
    MMP_ULONG           l64PhyBuf[MAX_TMC_DQNUM];
    MMP_ULONG           lTime[MAX_TMC_DQNUM];
    MMP_ULONG           WCnt;
    MMP_ULONG           RCnt;
    MMP_ULONG           lBufNum;
    MMP_ULONG           CurSkipFrmCnt;
} MMP_TIMECTL_BUFCTL;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_COMPONENT_BASE Component_TCL;
extern MMP_COMPONENT_HANDLER_TIMECTL Component_TCL_Handler[];
extern MMP_COMPONENT_MEMORY_INFO Component_TCL_Memory[];

// Extern Function of Port:
extern MMP_COMPONENT_PORT_INFO ComponentPort_TCL[];

//==============================================================================
//
//                              FUNCTION
//
//==============================================================================

#endif // _COMPONENT_TCL_H_

