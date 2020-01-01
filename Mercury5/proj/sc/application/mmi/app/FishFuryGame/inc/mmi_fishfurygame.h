////////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2006-2012 MStar Semiconductor, Inc.
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
* @file    mmi_fishfurygame.h
* @version
* @brief   FishFuryGame applet header file
*
*/

#ifndef __MMI_FISHFURYGAME_H__
#define __MMI_FISHFURYGAME_H__


/*------------------------------------------------------------------------------
Include Files
-------------------------------------------------------------------------------*/
#include "mmi_fishfurygame_priv.h"
#include "mmi_fishfurygame_id.h"
/*------------------------------------------------------------------------------
Macro
-------------------------------------------------------------------------------*/
#define FISHFURYGAME_ENGINE_FPS            (15)
#define FISHFURYGAME_UPDATE_PERIOD         (30)
/*------------------------------------------------------------------------------
Data Type
-------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
Global Variables
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
Global Function
-------------------------------------------------------------------------------*/
#ifdef FISHFURYGAME_ON_MAE_PLATFORM
MAE_Ret FishFuryGameNew(MAE_ClsId id, void **ppObj);
#else
MAE_Ret FishFuryGameNew(void **ppObj);
MAE_Ret FishFuryGame_Release(void *ppObj);
boolean FishFuryGameHookDraw(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
boolean FishFuryGameTouchCb(IApplet *pApplet, u32 nEvt, u32 nParam1, u32 nParam2);
#endif
#endif //__MMI_FISHFURYGAME_H__
