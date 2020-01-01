//==============================================================================
//
//  File        : ahc_preview.h
//  Description : INCLUDE File for the AHC Preview function porting.
//  Author      : 
//  Revision    : 1.0
//
//==============================================================================

#ifndef _AHC_PREVIEW_H_
#define _AHC_PREVIEW_H_

/*===========================================================================
 * Include files
 *===========================================================================*/ 
#include "ahc_common.h"

/*===========================================================================
 * Macro define
 *===========================================================================*/ 
#define AHC_PREVIEW_WINDOW_OP_MASK	 	0xff00
#define	AHC_PREVIEW_WINDOW_OP_GET 	 	0x0000
#define	AHC_PREVIEW_WINDOW_OP_SET 	 	0x0100
#define AHC_PREVIEW_WINDOW_MASK		 	0x00ff
#define	AHC_PREVIEW_WINDOW_FRONT 	 	0x0000
#define	AHC_PREVIEW_WINDOW_REAR		 	0x0001
/*===========================================================================
 * Enum define
 *===========================================================================*/ 
 
/*===========================================================================
 * Struct define
 *===========================================================================*/ 
typedef struct _AHC_WINDOW_RECT {
    UINT16		usLeft;
    UINT16      usTop;
    UINT16      usWidth;
    UINT16      usHeight;
} AHC_WINDOW_RECT;
/*===========================================================================
 * Function prototype
 *===========================================================================*/ 
UINT32			AHC_PreviewWindowOp(UINT32 op, AHC_WINDOW_RECT * pRect);

#endif //_AHC_PREVIEW_H_