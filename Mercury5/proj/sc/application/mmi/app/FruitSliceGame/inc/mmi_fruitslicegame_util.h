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
* @file    mmi_fruitslicegame_util.h
* @version
* @brief   FruitSliceGame Utility applet header file
*
*/


#ifndef __MMI_FRUITSLICEGAME_UTIL_H__
#define __MMI_FRUITSLICEGAME_UTIL_H__

/*=============================================================*/
// Include files
/*=============================================================*/
#include "mmi_fruitslicegame_priv.h"
#include "mgl_Core_Shape.h"
#include "mgl_Core_Transform.h"

boolean _FruitSlice_IsInside(s32 cx, s32 cy, s32 x, s32 y, s32 w, s32 h);
s32 _FruitSlice_GetPow(s32 x, s32 p);
s32 _FruitSlice_GetFigure(s32 x);
u32 _FruitSlice_GetSystemTime(void);
boolean _FruitSlice_SegmentIntersectRectangle(mgl_float x1, mgl_float y1, mgl_float x2, mgl_float y2, mgl_float rx1, mgl_float ry1, mgl_float rx2, mgl_float ry2);
void _FruitSlice_GetObjRect(FruitSliceApp_t *pThis, Rect_t *pIn, Rect_t *pOut);
mgl_float _FruitSlice_GetSlopeAngle(mgl_float offsetX, mgl_float offsetY);
Color4f _FruitSlice_Rgb2Color(u32 nRgb);
void _FruitSlice_AudioStatusNotifyCb(void * pApplet, u32 nCusData, AudioSrvPlayStatusEvent_e eEventId, u32 nInfoData);
MAE_Ret _FruitSlicePlayAudio(FruitSliceApp_t *pThis, u32 nMelodyID, AudioSrvPlayMode_e ePlayMode, AudioSrvCb pFnAudioCb);

void _FruitSlice_Timer_TickCallBack(void* pUser);
void _FruitSlice_Timer_Start(FruitSliceApp_t *pThis, u32 nCountdownSeconds);
void _FruitSlice_Timer_Pause(FruitSliceApp_t *pThis);
void _FruitSlice_Timer_Stop(FruitSliceApp_t *pThis);
void _FruitSlice_Timer_Resume(FruitSliceApp_t *pThis);
//u32 _FruitSlice_Timer_GetDuration(FruitSliceApp_t *pThis);
u32 _FruitSlice_Timer_GetSurplusTimer(FruitSliceApp_t *pThis);
//FruitSlice_TimerState_e _FruitSlice_Timer_GetState(FruitSliceApp_t *pThis);

void FruitSliceApp_tickCB(FruitSliceApp_t *pThis, FruitSlice_TimerState_e eTimerState, u32 nSurplusTime);

boolean _FruitSlice_IsButtonPressed(FruitSliceApp_t *pThis, const FruitSlice_Button_t *pButtonInfo);
void _FruitSlice_GetRotateTransform(FruitSliceApp_t *pThis, TransformOP *pTransform, u32 *pOp);
void _FruitSlice_DrawButton(FruitSliceApp_t *pThis, mgl_u32 nodeID, const FruitSlice_Button_t *pButtonInfo);

void _FruitSlice_DrawNumber(FruitSliceApp_t *pThis, mgl_u32 nodeID, FruitSlice_NumType_e eNumType, u32 nNum, u32 nStartX, u32 nStartY, u32 nMaxFigure);
void _FruitSlice_DrawCountDown(FruitSliceApp_t *pThis, mgl_u32 nodeID, FruitSlice_NumType_e eNumType, u32 nNum, u32 nStartX, u32 nStartY);
void _FruitSlice_DrawAlignedNumber(FruitSliceApp_t *pThis, mgl_u32 nodeID, FruitSlice_NumType_e eNumType, u32 nNum, u32 nCenterX, u32 nCenterY);

// fire
void FruitSlice_InitFire(FruitSliceApp_t *pThis, FruitSlice_Info_t *pFruitInfo);
void FruitSlice_CreateFire(FruitSliceApp_t *pThis, FruitSlice_Info_t *pFruitInfo, u32 nIdx);
void FruitSlice_UpdateFire(FruitSliceApp_t *pThis, FruitSlice_Info_t *pFruitInfo);
void FruitSlice_DrawFire(FruitSliceApp_t *pThis, FruitSlice_Info_t *pFruitInfo, mgl_u32 nodeID);

// explosion
void _FruitSlice_InitExplosion(FruitSliceApp_t *pThis, Vertex3D *pVertex);
void _FruitSlice_CreateExplosion(FruitSliceApp_t *pThis, u32 nIdx);
void _FruitSlice_UpdateExplosion(FruitSliceApp_t *pThis);
void _FruitSlice_DrawExplosion(FruitSliceApp_t *pThis, mgl_u32 nodeID);

// instruction
void FruitSlice_InitInstruction(FruitSliceApp_t *pThis, const Vertex3D *pDockPos, const Vertex2D *pDockSize);
void FruitSlice_UpdateInstruction(FruitSliceApp_t *pThis);
void FruitSlice_DrawInstruction(FruitSliceApp_t *pThis, mgl_u32 nodeID);
#endif /* __MMI_FRUITSLICEGAME_UTIL_H__ */
