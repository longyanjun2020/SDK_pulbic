/*-----------------------------------------------------------------------------
 *                                                                           
 * Copyright (c) 2008 MStar Semiconductor, Inc.  All rights reserved.
 *                                                                          
 *-----------------------------------------------------------------------------
 * FILE
 *      mgl_ErrCode.h
 *
 *
 * HISTORY
 *      2009.02.08       Chunwei.Wang         Initial Version
 *                                          
 *----------------------------------------------------------------------------- 
 */

#ifndef __M_ERROR_CODE_H__
#define __M_ERROR_CODE_H__

#include "mgl_Utility_common.h"

/*------------------------------------------------------------------------------
    Data Type
-------------------------------------------------------------------------------*/
enum
{
	MGL_RET_SUCCESS				= 0, 
	MGL_RET_BAD_PARAM			= 1, 
	MGL_RET_FAILED	                     = 2, 
	MGL_RET_OUT_OF_MEMORY	       = 3,
	MGL_RET_NO_FOUND_HASH		= 4, 	
	MGL_RET_NO_FOUND_SCENE		= 5, 
	MGL_RET_NO_FOUND_TEXTURE	= 6,
	MGL_RET_NO_FOUND_NODE		= 7, 
       MGL_RET_NO_FOUND_LIGHT          = 8,       
       MGL_RET_NO_TEXTURE_ID            = 9,
       
	MGL_RET_UNKNOWN_ERROR		= 0x1000
};

typedef mgl_s32 mgl_ErrCode;

#endif /* __M_ERROR_CODE_H__ */

