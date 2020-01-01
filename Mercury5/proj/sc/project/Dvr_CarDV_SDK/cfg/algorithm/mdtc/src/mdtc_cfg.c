//------------------------------------------------------------------------------
//
//  File        : mdtc_cfg.c
//  Description : Source file of motion detection configuration
//  Author      : Alterman
//  Revision    : 0.0
//
//------------------------------------------------------------------------------

//==============================================================================
//
//                              INCLUDE FILE
//
//==============================================================================

#include "mdtc_cfg.h"

//==============================================================================
//
//                              VARIABLES
//
//==============================================================================

/*
 * Resolution of source image
 */
MDTC_RESOL      gstMdtcResol = {
    MDTC_WIDTH, // width
    MDTC_HEIGHT // heigth
};

/*
 * Gap of frames to do motion detection
 */
unsigned char   gubMdtcFrameGap = MDTC_FRAME_GAP;

/*
 * Configure of detect windows
 */
MDTC_WIN_CFG    gstMdtcWinCfg = {
    0,                  // x_lt
    0,                  // y_lt
    MDTC_WIDTH - 1,     // x_rb
    MDTC_HEIGHT - 1,    // y_rb
    MDTC_WIN_W_DIV,     // x_div
    MDTC_WIN_H_DIV      // y_div
};

/*
 * Input parameters of detect windows
 */
MDParamsIn_t  gstMdtcWinParam[MDTC_MAX_WIN_W_DIV][MDTC_MAX_WIN_H_DIV] = {
    {
        1,      // enable
        4,      // size_perct_thd_min
        100,    // size_perct_thd_max
        17,     // sensitivity
        500,    // learn_rate
    },
};

/*
 * Output results of detect windows
 */
MDParamsOut_t gstMdtcWinResult[MDTC_MAX_WIN_W_DIV][MDTC_MAX_WIN_H_DIV] = {
    {
        0,      // md_result
        0       // obj_cnt
    },
};

