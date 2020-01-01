//------------------------------------------------------------------------------
//
//  File        : vidrec_cfg.h
//  Description : Header file of Video Record configuration
//  Author      : Eroy
//  Revision    : 0.1
//
//------------------------------------------------------------------------------

#ifndef _VIDREC_CFG_H_
#define _VIDREC_CFG_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "lib_retina.h"
#include "mmp_display_inc.h"

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

#define GET_VR_PREVIEW_WINDOW(cam)  (cam == 0) ? (MMP_DISPLAY_WIN_PIP) : (MMP_DISPLAY_WIN_OVERLAY)

#endif // _VIDREC_CFG_H_

