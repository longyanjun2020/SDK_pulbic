 // 
// 
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_E_util.h 8 2008-05-21 03:28:23Z greatelsoft\ken $
#ifndef __XLITE_E_UTIL_H__
#define __XLITE_E_UTIL_H__

#include "xLite_E_internal.h"

/*!
 * @file xLite_E_util.h
 * @brief 工具集
 */


/*!
 * @brief 返回像素格式所占用的bit数
 * @param pf 需要查询的像素格式
 * @return 成功返回像素占用的bit数,否则返回-1L
 */
xl_int32 xlite_E_util_calc_bit_per_pixel(xlite_pixel_format pf);




/*!
 * @brief 返回Unicode字符串的Hash值
 * @param arg Unicode字符串
 * @param length 字符串的长度
 * @return 返回该Unicode字符串的Hash值
 */
xl_uint32 xlite_E_util_get_hash_ustring(const xl_wchar* arg,xl_uint32 length);

/*!
 * @brief 计算Ansi字符串的Hash值
 * @param arg Ansi字符串
 * @param length 字符串的长度
 * @return 返回该Ansi字符串的长度
 */
xl_uint32 xlite_E_util_get_hash_string(const xl_char* arg,xl_uint32 length);


/*!
 * @brief 使用"叠加"算法混合像素
 * @param t_color 背景色
 * @param s_color 需要绘制的颜色
 * @return 混合后的颜色
 * @note 返回的颜色为xlite_pf_rgb_565格式
 */
xl_uint16 xlite_E_util_blend_additive(xl_uint16 t_color,xl_uint16 s_color);

/*!
 * @brief 使用"Alpha"算法混合像素
 * @param t_color 背景色
 * @param s_color 需要绘制的颜色
 * @return 混合后的颜色
 * @note 返回的颜色为xlite_pf_rgb_565格式
 */
xl_uint16 xlite_E_util_blend_alpha(xl_uint16 t_color,xl_uint16 s_color,xl_uint8 alpha_value);


/*!
 * @brief 计算图形缓冲区每行占用的字节数
 * @param bpp 图形每个像素占用的bit数
 * @param width 图形的宽度
 * @return 返回4字节对齐的图形每行占用的字节数
 */
#define xlite_E_util_calc_byte_per_line(b,w)	( ((( (b) * (w)) + 31) / 32)  * 4 )			


/*!
 * @brief 转换xlite_pf_rgb_888到xlite_pf_rgb_565格式
 * @param r 源颜色的红色分量
 * @param g 源颜色的绿色分量
 * @param b 源颜色的蓝色分量
 * @return xlite_pf_rgb_565格式的颜色
 * @note 颜色分量的范围为 0 - 255,(255,255,255)为白色,(0,0,0)为黑色
 */
#define xlite_E_util_888_to_565(r,g,b)			( (xl_uint16)(((b)>>3) | (((g) & 0xFC) << 3) | ((r) & 0xF8) << 8))

/*
 * @brief 获取xlite_pf_rgb_565的像素中red分量的值
 * @param c 颜色
 * @return red分量的值
 */
#define xlite_E_util_get_red_value(c)			( (xl_uint8)( ( ( (c) & 0xF800 ) >> 11 ) << 3 ) )

/*
 * @brief 获取xlite_pf_rgb_565的像素中green分量的值
 * @param c 颜色
 * @return green分量的值
 */
#define xlite_E_util_get_green_value(c)			( (xl_uint8)( ( ( (c) & 0x7E0 ) >> 5 ) << 2 ) )

/*
 * @brief 获取xlite_pf_rgb_565的像素中blue分量的值
 * @param c 颜色
 * @return blue分量的值
 */
#define xlite_E_util_get_blue_value(c)			( (xl_uint8)( ( ( (c) & 0x1F) << 3) ) )

/*!
 * @brief 合并两个字节到一个uint16
 * @param l 低位的字节
 * @param h 高位的字节
 * @return 混合后的uint16
 */
#define xlite_E_util_make_uint16(l,h)			( (xl_uint16)( (xl_uint8)(l) ) | ( ((xl_uint16)( (xl_uint8)(h)) ) << 8) )


/*!
 * @brief 合并两个uint16到一个uint32
 * @param l 低位的uint16
 * @param h 高位的uint16
 * @return 混合后的uint32
 */
#define xlite_E_util_make_uint32(l,h)			( (xl_uint32)( (xl_uint16)(l) ) | ( ((xl_uint32)( (xl_uint16)(h) )) << 16) )

/*!
 * @brief 压入翻转模式
 * @param flip_mode 当前翻转模式指针
 * @param new_mode 需要压入的模式
 */
#define xlite_E_util_push_flip_mode(f,n)		( *(f) ^= (n) )



#endif