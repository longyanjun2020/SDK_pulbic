/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_Core_Fixed.h
 *
 *
 * HISTORY
 *      2009.10.04       Golden Chen         Initial Version
 *                                          
 *----------------------------------------------------------------------------- 
 */

#ifndef __M_CORE_FIXED_H__
#define __M_CORE_FIXED_H__

/*------------------------------------------------------------------------------
    Include Files
-------------------------------------------------------------------------------*/
#include "mgl_Utility_common.h"

/*------------------------------------------------------------------------------
    Macro
-------------------------------------------------------------------------------*/
#define FIXED16_ONE  (1 << 16)
#define FIXED_ZERO  (0)
#define FLOAT_ONE  (1.0f)
#define FLOAT_ZERO  (0.0f)

/*------------------------------------------------------------------------------
    Inline Function
-------------------------------------------------------------------------------*/
static __inline mgl_fixed mgl_Fixed16FromInt(int value) {return (value << 16);}
static __inline mgl_fixed mgl_Fixed16FromFloat(mgl_float value) {return (mgl_fixed)((value * (mgl_float)(1 << 16)));}
static __inline mgl_fixed mgl_MultiplyFixed16(mgl_fixed op1, mgl_fixed op2) {return (mgl_fixed)((op1 * op2) >> 16);}

#endif /* __M_CORE_FIXED_H__ */

