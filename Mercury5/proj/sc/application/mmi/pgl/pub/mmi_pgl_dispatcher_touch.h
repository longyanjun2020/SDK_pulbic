/*-----------------------------------------------------------------------------
*
* Copyright (c) 2011 MStar Semiconductor, Inc.  All rights reserved.
*
*-----------------------------------------------------------------------------
* FILE
*      mmi_pgl_dispatcher_touch.h
*
*
* HISTORY
*      2011.09.26       Pioneer Huang         Initial Version
*
*-----------------------------------------------------------------------------*/

#ifndef __MMI_PGL_DISPATCHER_TOUCH_INC__
#define __MMI_PGL_DISPATCHER_TOUCH_INC__

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

/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Internal Function
-------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
/** pgl_Dispatcher_TouchPress
* @brief      By pass touch press position event into Dispatcher of PGL Engine.
* @param[in]  engineID      PGL engine handleID.
* @param[in]  touch_pos_x   X-position of touch press.
* @param[in]  touch_pos_y   Y-position of touch press.
*
* @retval     pgl_boolean   return TRUE if one pgl_actor was picked.
*
*/
pgl_boolean pgl_Dispatcher_TouchPress(EngineHandleID engineID, pgl_u32 touch_pos_x, pgl_u32 touch_pos_y);

/** pgl_Dispatcher_TouchMove
* @brief      By pass touch move position event into Dispatcher of PGL Engine..
* @param[in]  engineID      PGL engine handleID.
* @param[in]  touch_pos_x   X-position of touch press.
* @param[in]  touch_pos_y   Y-position of touch press.
*
* @retval     None.
*
*/
pgl_void pgl_Dispatcher_TouchMove(EngineHandleID engineID, pgl_u32 touch_pos_x, pgl_u32 touch_pos_y);

/** pgl_Dispatcher_TouchRelease
* @brief      By pass touch release event into Dispatcher of PGL Engine.
* @param[in]  engineID      PGL engine handleID.
*
* @retval     None.
*
*/
pgl_void pgl_Dispatcher_TouchRelease(EngineHandleID engineID);


#endif
