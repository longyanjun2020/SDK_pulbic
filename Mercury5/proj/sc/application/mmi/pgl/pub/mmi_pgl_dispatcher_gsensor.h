/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mmi_pgl_dispatcher_gsensor.h
*
*
* HISTORY
*      2011.09.26       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __MMI_PGL_DISPATCHER_GSENSOR_INC__
#define __MMI_PGL_DISPATCHER_GSENSOR_INC__

/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "mmi_pgl_utility_types.h"

/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/
typedef void (*FPPglGSensorCBFunc)(EngineHandleID engineID, pgl_float x, pgl_float y, pgl_float z, void* pThis);

/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
pgl_boolean pgl_GSensor_Register(EngineHandleID engineID, void * pWidget, FPPglGSensorCBFunc func, void* pThis);
pgl_void pgl_GSensor_Deregister(EngineHandleID engineID);

#endif
