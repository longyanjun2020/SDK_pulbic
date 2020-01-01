// xstrike lite 
// only support 8 bit index image
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_E_raster.h 8 2008-05-21 03:28:23Z greatelsoft\ken $
#ifndef __XLITE_E_RASTER_H__
#define __XLITE_E_RASTER_H__

#include "xLite_E_internal.h"



/*!
 * @file xLite_E_raster.h
 * @brief 2D绘制器接口
 */


/*!
 * @brief 初始化2D绘制器
 * @param r 2D绘制器结构指针
 * @note 该函数将用初始的值填充参数r传入的结构指针，2D绘制器不需要手动删除
 */
xl_void xlite_E_raster_init(xlite_raster* r);



/*!
 * @brief 清除2D绘制器可能占用的内存
 * @param r 2D绘制器结构指针
 * @note 当绘制器执行特定操作的时候可能会申请内存作为缓冲,函数列表如下：\n
 * - xlite_E_raster_stretch_image\n
 * 所以当不再需要调用该功能的时候或者在退出程序的时候,需要调用该函数释放\n
 * 内存，否则可能会造成内存泄漏。
 */
xl_void xlite_E_raster_cleanup(xlite_raster* r);




/*!
 * @brief 设置用户剪裁区域
 * @param r 2D绘制器结构指针
 * @param clip_rect 用户剪裁区域
 */
xl_void xlite_E_raster_set_user_clip(xlite_raster* r,const xlite_rect* clip_rect);


/*!
 * @brief 设置是否过滤透明色
 * @param r 2D绘制器结构指针
 * @param filte_key_color 是否过滤透明色
 */
xl_void xlite_E_raster_set_filte_key_color(xlite_raster* r,xl_bool filte_key_color);


/*!
 * @brief 绘制图形到目标图形
 * @param r 2D绘制器结构指针
 * @param t_img 目标图形指针
 * @param t_rect 绘制的区域矩形指针
 * @param s_img 源图形指针
 * @param s_x 源图区域位置
 * @param s_y 源图区域位置
 */
xl_void xlite_E_raster_draw_image(xlite_raster* r,xlite_himage t_img,const xlite_rect* t_rect,xlite_himage s_img,xl_int32 s_x,xl_int32 s_y);


/*!
 * @brief 放缩图形到目标图形(可能会额外分配内存,需要使用xlite_E_raster_cleanup清除)
 * @param r 2D绘制器结构指针
 * @param t_img 目标图形指针
 * @param t_rect 绘制的区域矩形指针
 * @param s_img 源图形指针
 * @param s_rect 源图形区域矩形指针
 */
xl_void xlite_E_raster_stretch_image(xlite_raster* r,xlite_himage t_img,const xlite_rect* t_rect,xlite_himage s_img,const xlite_rect* s_rect);



/*!
 * @brief 设置一个像素颜色到目标图形
 * @param r 2D绘制器结构指针
 * @param t_img 目标图形指针
 * @param x 像素坐标
 * @param y 像素坐标
 * @param c 颜色
 * @note 像素颜色使用xlite_pf_rgb_565格式,xlite_E_util_888_to_565转换
 */
xl_void xlite_E_raster_set_pixel(xlite_raster* r,xlite_himage t_img,xl_int32 x,xl_int32 y,xl_color c);

/*!
 * @brief 获取目标图形像素颜色
 * @param r 2D绘制器结构指针
 * @param t_img 目标图形指针
 * @param x 像素坐标
 * @param y 像素坐标
 * @return 目标图形指定坐标的像素颜色
 */
xl_color xlite_E_raster_get_pixel(xlite_raster* r,xlite_himage t_img,xl_int32 x,xl_int32 y);

/*!
 * @brief 设置翻转模式
 * @param r 2D绘制器结构指针
 * @param flip_mode 翻转模式
 */
xl_void xlite_E_raster_set_flip_mode(xlite_raster* r,xlite_flip_mode flip_mode);


/*!
 * @brief 绘制水平线
 * @param r 2D绘制器结构指针
 * @param t_img 目标图形指针
 * @param x 水平线起始坐标
 * @param y 水平线起始坐标
 * @param length 水平线的长度
 * @param c 绘制线段使用的颜色
 */
xl_void xlite_E_raster_draw_horz_line(xlite_raster* r,xlite_himage t_img,xl_int32 x,xl_int32 y,xl_uint32 length,xl_color c);

/*!
 * @brief 绘制垂直线
 * @param r 2D绘制器结构指针
 * @param t_img 目标图形指针
 * @param x 垂直线起始坐标
 * @param y 垂直线起始坐标
 * @param length 垂直线的长度
 * @param c 绘制线段使用的颜色
 */
xl_void xlite_E_raster_draw_vert_line(xlite_raster* r,xlite_himage t_img,xl_int32 x,xl_int32 y,xl_uint32 length,xl_color c);


/*!
 * @brief 绘制线段
 * @param r 2D绘制器结构指针
 * @param t_img 目标图形指针
 * @param x1 线段起始坐标
 * @param y1 线段起始坐标
 * @param x2 线段结束坐标
 * @param y2 线段结束坐标
 * @param c 绘制线段使用的颜色
 */
xl_void xlite_E_raster_draw_line(xlite_raster* r,xlite_himage t_img,xl_int32 x1,xl_int32 y1,xl_int32 x2,xl_int32 y2,xl_color c);

/*!
 * @brief 绘制矩形
 * @param r 2D绘制器结构指针
 * @param t_img 目标图形指针
 * @param rect 矩形数据结构指针
 * @param c 绘制矩形使用的颜色
 */
xl_void xlite_E_raster_draw_rectangle(xlite_raster* r,xlite_himage t_img,const xlite_rect* rect,xl_uint16 c);

/*!
 * @brief 填充矩形区域
 * @param r 2D绘制器结构指针
 * @param t_img 目标图形指针
 * @param rect 矩形数据结构指针
 * @param c 填充矩形使用的颜色
 */
xl_void xlite_E_raster_fill_rectangle(xlite_raster* r,xlite_himage t_img,const xlite_rect* rect,xl_uint16 c);

/*!
 * @brief set blend color func
 * @param r raster pointer
 * @param blend_mode blend mode,如果blend_mode为xlite_blend_copy,则忽略所有之后的参数,
 * 如果blend_mode为xlite_blend_shade_func,则使用后面的shade_func指定的shade function混合像素,
 * @param shade_func 混合函数的索引,如果shade_func为XLITE_BLEND_COLOR_USER,则blend_color必须
 * 为一个合法的像素混合函数
 * @param blend_color 如果shade_func为XLITE_BLEND_COLOR_USER,则需要传入合法的像素混合函数
 */
xl_void xlite_E_raster_set_blend_mode(xlite_raster* r,xlite_blend_mode blend_mode,xl_int32 blend_func,xlite_E_raster_blend_color_func user_blend_func);



//////////////////////////////////////////////////////////////////////////
// Macro 
//////////////////////////////////////////////////////////////////////////

/*!
 * @brief 重置用户剪裁区域
 * @param r 2D绘制器结构指针
 * @note 该函数将会取消用户自定义的剪裁区域
 */
#define xlite_E_raster_reset_user_clip(r)					( (r)->has_user_clip_rect = XL_FALSE )

/*!
 * @brief 获取用户自定义剪裁矩形
 * @param r 2D绘制器结构指针
 * @return 如果存在自定义剪裁矩形则返回用户自定义的剪裁矩形,否则返回XL_NULL
 */
#define xlite_E_raster_get_user_clip_rect(r)				( ((r)->has_user_clip_rect) ? & (r)->user_clip_rect : XL_NULL ) 

/*!
 * @brief 获取是否过滤关键色
 * @param r 2D绘制器结构指针
 * @return 是否过滤关键色 
 */
#define xlite_E_raster_is_filte_key_color(r)				( (r)->filte_key_color )


/*!
 * @brief 设置Alpha值
 * @param r 2D绘制器结构指针
 * @param alpha_value alpha值,范围为(0-32)
 */
#define xlite_E_raster_set_alpha_value(r,a)					( (r)->alpha_value = (a) )

/*!
 * @brief 返回Alpha值
 * @param r 2D绘制器结构指针
 * @return 当前绘制器中的alpha值
 */
#define xlite_E_raster_get_alpha_value(r)					( (r)->alpha_value )

/*!
 * @brief 设置调色板偏移
 * @param r 2D绘制器结构指针
 * @param pal_offset 调色板偏移量
 */
#define xlite_E_raster_set_palette_offset(r,p)				( (r)->palette_offset = (p) )

/*!
 * @brief 返回当前的调色板偏移
 * @param r 2D绘制器结构指针
 * @return 当前绘制器中的调色板偏移量
 */
#define xlite_E_raster_get_palette_offset(r)				( (r)->palette_offset )	

/*!
 * @brief 获取当前的翻转模式
 * @param r 2D绘制器结构指针
 * @return 当前绘制器中的翻转模式
 */
#define xlite_E_raster_get_flip_mode(r)						( (r)->flip_mode )			

/*
 * @brief 设置关键色索引
 * @param r 2D绘制器结构指针
 * @param key_color_idx 关键色索引
 */
#define xlite_E_raster_set_key_color(r,k)					( (r)->key_color_index = (k) )

/*
 * @brief 获取当前的关键色索引
 * @param r 2D绘制器结构指针
 * @return 当前的关键色索引
 */
#define xlite_E_raster_get_key_color(r)						( (r)->key_color_index )



#endif