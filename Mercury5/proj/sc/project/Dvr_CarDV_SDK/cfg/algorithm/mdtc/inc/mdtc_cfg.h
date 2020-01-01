//------------------------------------------------------------------------------
//
//  File        : mdtc_cfg.h
//  Description : Header file of motion detection configuration
//  Author      : Alterman
//  Revision    : 0.0
//
//------------------------------------------------------------------------------
#ifndef _MDTC_CFG_H_
#define _MDTC_CFG_H_

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mi_md.h"

//==============================================================================
//
//                              CONSTANTS
//
//==============================================================================

/* Width of source image */
#define MDTC_WIDTH              320//(160)
/* Heigth of source image */
#define MDTC_HEIGHT             180//(120)
/* The number of divisions of window in horizontal direction */
#define MDTC_WIN_W_DIV          (1)
/* The number of divisions of window in vertical direction */
#define MDTC_WIN_H_DIV          (1)
/* The gap of every two frames to do motion detection */
#define MDTC_FRAME_GAP          (0)
/* Color format of source image */
#define MDTC_COLOR_Y            (1)

#define UVC_DEV_MD_MAX_DIV_W            (16)
#define UVC_DEV_MD_MAX_DIV_H            (12)
#define UVC_DEV_MD_MAX_SENSITIVITY      (100)//(40)

#define UVC_DEV_MD_DIV_W                (5)
#define UVC_DEV_MD_DIV_H                (5)
#define UVC_DEV_MD_SENSITIVITY          (80)//(17)

/* The max number of divisions of window in horizontal direction */
#define MDTC_MAX_WIN_W_DIV          (16)
/* The max number of divisions of window in vertical direction */
#define MDTC_MAX_WIN_H_DIV          (12)

//==============================================================================
//
//                              STRUCTURES
//
//==============================================================================

typedef struct {
    unsigned int width;     // Width of source image
    unsigned int height;    // Height of source image
} MDTC_RESOL;

typedef struct {
    unsigned short x_lt;    // Horizontal position of window left-top point
    unsigned short y_lt;    // Vertical position of window left-top point
    unsigned short x_rb;    // Horizontal position of window right-bottom point
    unsigned short y_rb;    // Vertical position of window right-bottom point
    unsigned char  x_div;   // The number of divisions of window in X direction
    unsigned char  y_div;   // The number of divisions of window in Y direction
} MDTC_WIN_CFG;

//==============================================================================
//
//                              EXTERN VARIABLES
//
//==============================================================================

extern unsigned char    gubMdtcFrameGap;
extern MDTC_RESOL       gstMdtcResol;
extern MDTC_WIN_CFG     gstMdtcWinCfg;
extern MDParamsIn_t   gstMdtcWinParam[MDTC_MAX_WIN_W_DIV][MDTC_MAX_WIN_H_DIV];
extern MDParamsOut_t  gstMdtcWinResult[MDTC_MAX_WIN_W_DIV][MDTC_MAX_WIN_H_DIV];

#endif // _MDTC_CFG_H_

