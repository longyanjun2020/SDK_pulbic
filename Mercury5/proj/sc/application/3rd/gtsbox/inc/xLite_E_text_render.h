// 
// 
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_E_text_render.h 8 2008-05-21 03:28:23Z greatelsoft\ken $
#ifndef __XLITE_E_TEXT_RENDER_H__
#define __XLITE_E_TEXT_RENDER_H__

#include "xLite_E_internal.h"

/*
 * @brief 开始绘制字符串
 * @param 
 * @return
 */
xl_int32 xlite_E_text_render_draw(xlite_graphics* g,const xlite_rect* text_rect,const xl_wchar* text,xl_uint32 length,xl_uint32 flags);

/*
 * @brief 绘制字符串,如果字符串超过绘制区域则绘制占位符
 * @param
 * @return
 */
xl_void xlite_E_text_render_output(xlite_graphics* g,const xlite_rect* text_rect,const xl_wchar* text,xl_uint32 length,const xl_wchar* holdplace,xl_uint32 hp_len,xl_uint32 flags);


/*
 * @brief 计算绘制字符串的行数
 * @param
 * @return
 */
xl_int32 xlite_E_text_render_get_line(xlite_graphics* g,xl_uint32 draw_area_width,const xl_wchar* text,xl_uint32 length);



/*!
* @brief 设置字间距
* @param
* @return 之前的字间距设置
*/
xl_int32 xlite_E_text_render_set_char_space(xlite_graphics* g,xl_int32 char_space);

/*!
* @brief 返回当前的字间距
* @param
* @return
*/
xl_int32 xlite_E_text_render_get_char_space(xlite_graphics* g);


/*!
* @brief 设置行距
* @param
* @return 返回之前的行距
*/
xl_int32 xlite_E_text_render_set_line_space(xlite_graphics* g,xl_int32 line_space);

/*!
* @brief 返回当前的行距
* @param
* @return
*/
xl_int32 xlite_E_text_render_get_line_space(xlite_graphics* g);

#endif