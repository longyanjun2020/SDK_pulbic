// 
// 
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_E_sprite_render.h 8 2008-05-21 03:28:23Z greatelsoft\ken $
#ifndef __XLITE_E_SPRITE_RENDER_H__
#define __XLITE_E_SPRITE_RENDER_H__

#include "xLite_E_internal.h"

/*!
 * @file xLite_E_sprite_render.h
 * @brief 精灵渲染接口
 */


/*!
 * @brief 渲染精灵
 * @param g 图形管理器指针
 * @param x 坐标
 * @param y 坐标
 * @param data 精灵数据
 * @param act 渲染的精灵动作序列指针
 * @param frm 渲染的精灵帧指针
 */
xl_void xlite_E_sprite_render_draw(xlite_graphics* g,xl_int32 x,xl_int32 y,xlite_sprite_data* data,xlite_sprite_action* act,xlite_sprite_frame* frm);




#endif