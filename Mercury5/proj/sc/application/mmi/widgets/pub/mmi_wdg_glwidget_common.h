/**
* @file    mae_glwidget_common.h
* @brief   his header file defines some definitions of interface and the definition of IBase interface
* 
* @version $Id: mae_glwidget_common.h 34134 2009-06-23 07:19:22Z bill.pan $
*/

#ifndef __MMI_WDG_GLWIDGET_COMMON_H__
#define __MMI_WDG_GLWIDGET_COMMON_H__

/*=============================================================*/
// include
/*=============================================================*/

#include "mmi_mae_widget.h"

IBitmap* GLWidget_GetWidgetRawData(IWidget* WidgetPtr, boolean bAlphaSupport, IBase* pThis);

#if defined(__FEATURE_MGL__)
#if defined(__3D_UI_IDLE_MULTIPAGE__)
void GLWidget_MultipageContainerGetPageOrigin(u16 u16PageWidth,u16 u16PageHeight,u8 u8TotalPageCount, u8 u8CurPage, s32 *s32Xpos, s32 *s32Ypos);
#endif //__3D_UI_IDLE_MULTIPAGE__
void GLWidget_SetClientAreaByCurrOrientation(IDispCanvas *pIDispCanvas, s32 x, s32 y, s32 width, s32 height, IBase* pThis);
#endif  //defined(__FEATURE_MGL__)
#endif //__MAE_GLWIDGET_COMMON_H__
/*=============================================================*/
// end of file
