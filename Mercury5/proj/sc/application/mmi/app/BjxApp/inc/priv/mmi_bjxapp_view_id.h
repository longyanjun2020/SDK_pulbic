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

#ifndef __MMI_BJX_VIEW_ID_H__
#define __MMI_BJX_VIEW_ID_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_view_id_range.h"
#include "mmi_common_thmid.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/
#define MMI_BJX_SYMBOL_QUESTION     0x003F
#define MMI_BJX_EN_A_UC             0x0041
#define MMI_BJX_EN_A_LC             0x0061
#define MMI_BJX_EN_B_LC             0x0062
#define MMI_BJX_EN_C_LC             0x0063
#define MMI_BJX_EN_D_LC             0x0064
#define MMI_BJX_EN_E_LC             0x0065
#define MMI_BJX_EN_F_LC             0x0066
#define MMI_BJX_EN_G_LC             0x0067
#define MMI_BJX_EN_H_LC             0x0068
#define MMI_BJX_EN_I_LC             0x0069
#define MMI_BJX_EN_J_LC             0x006A
#define MMI_BJX_EN_K_LC             0x006B
#define MMI_BJX_EN_L_LC             0x006C
#define MMI_BJX_EN_M_LC             0x006D
#define MMI_BJX_EN_N_LC             0x006E
#define MMI_BJX_EN_O_LC             0x006F
#define MMI_BJX_EN_P_LC             0x0070
#define MMI_BJX_EN_Q_LC             0x0071
#define MMI_BJX_EN_R_LC             0x0072
#define MMI_BJX_EN_S_LC             0x0073
#define MMI_BJX_EN_T_LC             0x0074
#define MMI_BJX_EN_U_LC             0x0075
#define MMI_BJX_EN_V_LC             0x0076
#define MMI_BJX_EN_W_LC             0x0077
#define MMI_BJX_EN_X_LC             0x0078
#define MMI_BJX_EN_Y_LC             0x0079
#define MMI_BJX_EN_Z_UC             0x005A
#define MMI_BJX_EN_Z_LC             0x007A

/*=============================================================*/
// Data type definition
/*=============================================================*/
enum
{
/* View ID start */
    BJX_MAIN_VIEW =  MMI_VIEW_ID_AP_BEGIN,
/* View ID end */
};

enum
{
    /* Widget ID start */
    BJX_MAIN_TITLE = 1,
    BJX_ABS_CONTAINER,
    BJX_SURNAME_GRID,
    BJX_ALPHABET_BG_CNT,
    BJX_ALPHABET_GRID,
    BJX_SURNAME_ITEM_CNT,
    BJX_SURNAME_ITEM,
    BJX_ALPHABET_ITEM_CNT,
    BJX_ALPHABET_ITEM,
    /* Model ID start */
    BJX_ALPHABET_MODEL
};

#endif /* __MMI_BJX_VIEW_ID_H__ */
