//------------------------------------------------------------------------------
//
//  File        : cust_component_cfg.h
//  Description : Header file of Component configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _CUST_COMPONENT_CFG_H_
#define _CUST_COMPONENT_CFG_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmp_component_ctl.h"
#include "component_cfg.h"

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct _CUSTOMER_COMP_SCRIPT
{
    MMP_UBYTE       ubScriptId;     // Script ID
    MMP_UBYTE       ubName[64];     // Script Name
    MMP_BOOL        bOpened;        // Script Open Status
    COMPONENT_CFG   *ScriptCfg;     // Pointer to component list
    MMP_UBYTE       ubNum;          // Component count within component list
    MMP_UBYTE       ubUpdIdx[15];   // Index for update device information
} CUSTOMER_COMP_SCRIPT;

typedef struct _CUSTOMER_COMP_PORT_SCRIPT
{
    MMP_UBYTE       ubScriptId;     // Script ID
    MMP_UBYTE       ubName[64];     // Script Name
    COMPONENT_PORT_CFG *ScriptCfg;  // Pointer to component port list
} CUSTOMER_COMP_PORT_SCRIPT;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern MMP_BOOL gbLCDRotate;

//==============================================================================
//
//                              Function
//
//==============================================================================

MMP_ERR OpenScript(MMP_UBYTE ubScriptIdx);
MMP_ERR CloseScript(MMP_UBYTE ubScriptIdx);
MMP_ERR OpenPortScript(MMP_UBYTE ubPortScriptIdx);
MMP_ERR ClosePortScript(MMP_UBYTE ubPortScriptIdx);

#endif // _CUST_COMPONENT_CFG_H_

