// 
// 
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_E_graphics.h 67 2008-06-27 03:13:03Z greatelsoft\ken $
#ifndef __XLITE_E_GRAPHICS_H__
#define __XLITE_E_GRAPHICS_H__

#include "xLite_E_internal.h"

/*!
 * @file xlite_E_graphics.h
 * @brief Graphics
 */


/*!
 * @brief 初始化Graphics
 * @param g:Graphics的结构指针,初始化函数对该指针指向的Graphics进行初始化
 * @param ds: DirectScreen的结构指针.初始化函数将与DirectScreen建立默认联系
 * @return 成功返回XL_TRUE,否则返回XL_FALSE
 */
xl_bool xlite_E_graphics_init(xlite_graphics* g,xlite_directscreen* ds);


/*!
 * @brief 删除Graphics
 * @param g: 需要删除的Graphics结构指针
 */
xl_void xlite_E_graphics_delete(xlite_graphics* g);


/*!
 * @brief 使用指定的颜色清除Graphics控制的Image
 * @param g: Graphics的结构指针
 * @param color: 指定的颜色
 */
xl_void xlite_E_graphics_clear(xlite_graphics* g,xl_color color);


/*!
 * @brief 将图形资源设为绘制的目标图形
 * @param g Graphics的结构指针
 * @param new_image 要设为绘制目标的图形
 * @return Graphics中已经存在的图形
 * @note 只有xlite_pf_rgb_565格式的图形才可以被设为绘制目标图形
 */
xlite_himage xlite_E_graphics_set_render_buffer(xlite_graphics* g,xlite_himage new_image);


/*
 * @brief 返回Graphics的绘制器已存在的自定义裁剪矩形
 * @param sa xlite_E_raster_reset_user_flip
 * @return TRUE if graphics has a clip rectangle,otherwise none 
 */
xl_bool xlite_E_graphics_get_user_clip(xlite_graphics* g,xlite_rect* user_clip);


/*
 * @brief 设置文字颜色
 * @param text_clr 设置的文字颜色
 * @return
 */
xl_void xlite_E_graphics_set_text_color(xlite_graphics* g,xl_uint16 text_clr);

/*
 * @brief 设置文字是否有边框(Removed)
 * @param has_border 是否有边框
 * @param border_clr 如果绘制边框,则设置边框色
 * @return
 */
// Removed by Ken
// xl_void xlite_E_graphics_set_text_border(xlite_graphics* g,xl_bool has_border,xl_uint16 border_clr);



/*
 * @brief 设置文字大小,可能某些平台无法支持
 * @param text_size 文字大小
 * @return
 */
xl_void xlite_E_graphics_set_text_size(xlite_graphics* g,xl_uint8 text_size);


/*
 * @brief 绘制文字到屏幕
 * @param x 文字的X坐标
 * @param y 文字的Y坐标
 * @param text 绘制的文字的指针
 * @param length 绘制的字数
 * @return
 */
xl_void xlite_E_graphics_draw_string(xlite_graphics* g,xl_int32 x,xl_int32 y,const xl_wchar* text,xl_uint32 length);

/*
 * @brief 绘制字符到屏幕
 * @param x 文字的X坐标
 * @param y 文字的Y坐标
 * @param ch 绘制的文字的指针
 * @return
 */
xl_void xlite_E_graphics_draw_character(xlite_graphics* g,xl_int32 x,xl_int32 y,xl_wchar ch);

/*
 * @brief 返回字符串的宽度
 * @param text 字符串指针
 * @param length 字符串的字数
 * @return 绘制需要的长度
 */
xl_uint32 xlite_E_graphics_get_string_width(xlite_graphics* g,const xl_wchar* text,xl_uint32 length);

/*
 * @brief 返回字符串的高度
 * @param text 字符串指针
 * @param length 字符串的字数
 * @return 绘制需要的长度
 */
xl_uint32 xlite_E_graphics_get_string_height(xlite_graphics* g,const xl_wchar* text,xl_uint32 length);


/*
 * @brief 返回字符的宽度
 * @param ch 字符
 * @return 绘制需要的宽度
 */
xl_uint32 xlite_E_graphics_get_character_width(xlite_graphics* g,xl_wchar ch);


/*
 * @brief 返回字符的高度
 * @param ch 字符
 * @return 绘制需要的高度
 */
xl_uint32 xlite_E_graphics_get_character_height(xlite_graphics* g,xl_wchar ch);

/*!
 * @brief 设置Graphics的绘制器的用户自定义的剪裁矩形
 * @sa xlite_E_raster_set_user_clip
 */
xl_void xlite_E_graphics_set_user_clip(xlite_graphics* g,const xlite_rect* clip_rect);

/*!
 * @brief 重置Graphics的绘制器中的自定义剪裁矩形
 * @sa xlite_E_raster_reset_user_clip
 */
xl_void xlite_E_graphics_reset_user_clip(xlite_graphics* g);


/*
 * @brief 保存当前Raster的状态
 * @param g xlite_graphics的指针
 */
xl_void xlite_E_graphics_backup_raster_state(xlite_graphics* g);


/*
 * @brief 应用保存过的Raster state到Raster
 * @param g xlite_graphics的指针
 */
xl_void xlite_E_graphics_restore_raster_state(xlite_graphics* g);

/*!
 * @brief 返回Graphics中可绘制的宽度
 * @param g Graphics的结构指针
 * @return 宽度
 */
#define xlite_E_graphics_get_width(g)					(xlite_E_image_get_width((g)->surface))

/*!
 * @brief 返回Graphics中可绘制的高度
 * @param g Graphics的机构指针
 * @return 高度
 */
#define xlite_E_graphics_get_height(g)					(xlite_E_image_get_height((g)->surface))

/*!
 * @brief 设置Graphics的绘制器的翻转模式
 * @sa xlite_E_raster_set_flip_mode
 */
#define xlite_E_graphics_set_flip_mode(g,f)				(xlite_E_raster_set_flip_mode(&(g)->raster,(f)))


/*!
 * @brief 获取Graphics的翻转模式
 * @sa xlite_E_raster_get_flip_mode
 */
#define xlite_E_graphics_get_flip_mode(g)				(xlite_E_raster_get_flip_mode(&(g)->raster) )


/*!
 * @brief 设置Graphics的绘制器是否过滤透明色
 * @sa xlite_E_raster_set_filte_key_color
 */
#define xlite_E_graphics_set_filte_key_color(g,k)		(xlite_E_raster_set_filte_key_color(&(g)->raster,(k)))


/*!
 * @brief 是否过滤关键色
 * @sa xlite_E_raster_is_filte_key_color
 */
#define xlite_E_graphics_is_filte_key_color(g)			(xlite_E_raster_is_filte_key_color(&(g)->raster) )

/*!
 * @brief 绘制图形
 * @sa xlite_E_raster_draw_image
 */
#define xlite_E_graphics_draw_image(g,tr,s,sx,sy)		(xlite_E_raster_draw_image(&(g)->raster,(g)->surface,(tr),(s),(sx),(sy)))


/*!
 * @brief 放缩图形
 * @sa xlite_E_raster_stretch_image
 */
#define xlite_E_graphics_stretch_image(g,tr,s,sr)		(xlite_E_raster_stretch_image(&(g)->raster,(g)->surface,(tr),(s),(sr) ))

/*!
 * @brief 绘制水平线段
 * @sa xlite_E_raster_draw_horz_line
 */
#define xlite_E_graphics_draw_horz_line(g,x,y,l,c)		(xlite_E_raster_draw_horz_line(&(g)->raster,(g)->surface,(x),(y),(l),(c)))

/*!
 * @brief 绘制垂直线段
 * @sa xlite_E_raster_draw_vert_line
 */
#define xlite_E_graphics_draw_vert_line(g,x,y,l,c)		(xlite_E_raster_draw_vert_line(&(g)->raster,(g)->surface,(x),(y),(l),(c)))

/*!
 * @brief 绘制线段
 * @sa xlite_E_raster_draw_line
 */
#define xlite_E_graphics_draw_line(g,x1,y1,x2,y2,c)		(xlite_E_raster_draw_line(&(g)->raster,(g)->surface,(x1),(y1),(x2),(y2),(c)))

/*!
 * @brief 绘制矩形
 * @sa xlite_E_raster_draw_rectangle
 */
#define xlite_E_graphics_draw_rectangle(g,rt,c)			(xlite_E_raster_draw_rectangle(&(g)->raster,(g)->surface,(rt),(c)))

/*!
 * @brief 填充矩形
 * @sa xlite_E_raster_fill_rectangle
 */
#define xlite_E_graphics_fill_rectangle(g,rt,c)			(xlite_E_raster_fill_rectangle(&(g)->raster,(g)->surface,(rt),(c)))

/*!
 * @brief 设置像素混合模式
 * @sa xlite_E_raster_set_blend_color_func
 */
#define xlite_E_graphics_set_blend_mode(g,bm,bf,ubf)	(xlite_E_raster_set_blend_mode(&(g)->raster,(bm),(bf),(ubf)))

/*!
 * @brief 设置alpha值
 * @sa xlite_E_raster_set_alpha_value
 */
#define xlite_E_graphics_set_alpha_value(g,a)			(xlite_E_raster_set_alpha_value(&(g)->raster,(a)))

/*!
 * @brief 获取alpha值
 * @sa xlite_E_raster_get_alpha_value
 */
#define xlite_E_graphics_get_alpha_value(g)				(xlite_E_raster_get_alpha_value(&(g)->raster) )

/*!
 * @breif 设置调色板偏移
 * @sa xlite_E_raster_set_palette_offset
 */
#define xlite_E_graphics_set_palette_offset(g,p)		(xlite_E_raster_set_palette_offset(&(g)->raster,(p)) )

/*!
 * @brief 获取调色板偏移
 * @sa xlite_E_raster_get_palette_offset
 */
#define xlite_E_graphics_get_palette_offset(g)			(xlite_E_raster_get_palette_offset(&(g)->raster) )

/*
 * @brief 设置关键色索引
 * @sa xlite_E_raster_set_key_color
 */
#define xlite_E_graphics_set_key_color(g,k)				(xlite_E_raster_set_key_color(&(g)->raster,(k)) )

/*
 * @brief 获取关键色索引
 * @sa xlite_E_raster_get_key_color
 */
#define xlite_E_graphics_get_key_color(g)				(xlite_E_raster_get_key_color(&(g)->raster))

/*!
 * @brief 返回Render buffer
 * @param xlite_graphics指针
 * @param 当前使用的Render buffer
 */
#define xlite_E_graphics_get_render_buffer(g)			((g)->surface)


/*!
 * @brief 为指定的像素设置颜色
 * @param 
 * @return
 */
#define xlite_E_graphics_set_pixtel(g,x,y,c)			(xlite_E_raster_set_pixel(&(g)->raster,(g)->surface,(x),(y),(c)))


/*!
 * @brief 返回当前的文字颜色
 * @param
 * @return
 */
#define xlite_E_graphics_get_text_color(g)				((g)->text_color)

/*!
 * @brief 返回当前的文字大小
 * @param
 * @return
 */
#define xlite_E_graphics_get_text_size(g)				((g)->text_size)



#endif