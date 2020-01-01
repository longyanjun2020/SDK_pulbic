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
 * @file mdl_ball_types.h
 * @brief
 */

#ifndef __MDL_BALL_TYPES_H__
#define __MDL_BALL_TYPES_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mdl_ball_forward.h"

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/**
 *  @brief The enumeration defines the return code of the keypad middle interface
 */
opaque_enum(MdlBallErrCode_e_)
{
    MDL_BALL_OK,                 /**< Function complete successfully */
    MDL_BALL_FAIL,               /**< Function common fail */
};

#endif  //__MDL_BALL_TYPES_H__
