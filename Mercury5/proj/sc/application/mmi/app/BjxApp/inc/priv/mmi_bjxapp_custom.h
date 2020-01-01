////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2009 MStar Semiconductor, Inc.
// All rights reserved.
//
// Unless otherwise stipulated in writing, any and all information contained
// herein regardless in any format shall remain the sole proprietary of
// MStar Semiconductor Inc. and be kept in strict confidence
// (¡§MStar Confidential Information¡¨) by the recipient.
// Any unauthorized act including without limitation unauthorized disclosure,
// copying, use, reproduction, sale, distribution, modification, disassembling,
// reverse engineering and compiling of the contents of MStar Confidential
// Information is unlawful and strictly prohibited. MStar hereby reserves the
// rights to any and all damages, losses, costs and expenses resulting therefrom.
//
////////////////////////////////////////////////////////////////////////////////

/**
 * @file mmi_bjxapp_custom.h
 *
 * BJXAPP Customization Data
 *
 * @version $Id: mmi_bjxapp_custom.h 14637 2008-10-02 03:30:33Z cosmo.sung $
 */
#ifndef __MMI_BJXAPP_CUSTOM_H__
#define __MMI_BJXAPP_CUSTOM_H__

#ifdef __TOUCH_SCREEN_MMI__
/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_bjxapp_priv.h"

/*=============================================================*/
// Data type definition
/*=============================================================*/
// BJXAPP \ This variable defines the key mapping of multitap alphabet to the numeric keys on handset. For example, key 2 is mapped to multitap A,B,C.
const static BjxAppKeyInfo_t KeyToAlphabetIdx[] =
{
#ifdef  __QWERTY_KEYPAD_MMI__
    {MAE_KEY_0, 0, 0},      //?   
    {MAE_KEY_STAR, 1, 1},      //A
    {MAE_KEY_B, 2, 2},      //B
    {MAE_KEY_C, 3, 3},      //C
    {MAE_KEY_D, 4, 4},      //D
    {MAE_KEY_E, 5, 5},      //E
    {MAE_KEY_F, 6, 6},      //F
    {MAE_KEY_G, 7, 7},      //G
    {MAE_KEY_H, 8, 8},      //H
    {MAE_KEY_I, 9, 9},      //I
    {MAE_KEY_J, 10, 10},    //J
    {MAE_KEY_K, 11, 11},    //K
    {MAE_KEY_L, 12, 12},    //L
    {MAE_KEY_M, 13, 13},    //M
    {MAE_KEY_N, 14, 14},    //N
    {MAE_KEY_O, 15, 15},    //O
    {MAE_KEY_P, 16, 16},    //P
    {MAE_KEY_HASH, 17, 17},    //Q
    {MAE_KEY_R, 18, 18},    //R
    {MAE_KEY_S, 19, 19},    //S
    {MAE_KEY_T, 20, 20},    //T
    {MAE_KEY_U, 21, 21},    //U
    {MAE_KEY_V, 22, 22},    //V
    {MAE_KEY_W, 23, 23},    //W
    {MAE_KEY_X, 24, 24},    //X
    {MAE_KEY_Y, 25, 25},    //Y
    {MAE_KEY_Z, 26, 26},    //Z
#else
    {MAE_KEY_0, 0, 0},      //0:?
    {MAE_KEY_2, 1, 3},      //2:A~C
    {MAE_KEY_3, 4, 6},      //3:D~F
    {MAE_KEY_4, 7, 9},      //4:G~I
    {MAE_KEY_5, 10, 12},    //5:J~K
    {MAE_KEY_6, 13, 15},    //6:M~O
    {MAE_KEY_7, 16, 19},    //7:P~S
    {MAE_KEY_8, 20, 22},    //8:T~V
    {MAE_KEY_9, 23, 26},    //9:X~Z
#endif /*__QWERTY_KEYPAD_MMI__*/
};

#endif // __TOUCH_SCREEN_MMI__
#endif /* __MMI_BJXAPP_CUSTOM_H__ */
