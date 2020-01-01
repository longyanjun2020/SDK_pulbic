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
* @file    Mmi_PicPreviewApp.h
* @version
* @brief   PicPreviewApp applet header file
*
*/


#ifndef __MMI_IDLEPREVIEWAPP_H_
#define __MMI_IDLEPREVIEWAPP_H_

#if defined(__FEATURE_MGL__) && defined(__3D_UI_IDLE_MULTIPAGE__)
/*=============================================================*/
// Include files
/*=============================================================*/

#include "mmi_mae_common_def.h"
/*=============================================================*/
// Extern definition
/*=============================================================*/

/*=============================================================*/
// Macro definition
/*=============================================================*/

/*=============================================================*/
// Data type definition
/*=============================================================*/

/*=============================================================*/
// Variable definition
/*=============================================================*/

/*=============================================================*/
// Global function definition
/*=============================================================*/

MAE_Ret IdlePreviewAppNew(MAE_ClsId id, void **ppObj);


#endif //__FEATURE_MGL__ && __3D_UI_IDLE_MULTIPAGE__
#endif /* __MMI_IDLEPREVIEWAPP_H_ */
