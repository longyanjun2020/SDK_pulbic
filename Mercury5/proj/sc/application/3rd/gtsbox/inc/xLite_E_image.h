// 
// 
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_E_image.h 8 2008-05-21 03:28:23Z greatelsoft\ken $
#ifndef __XLITE_E_IMAGE_H__
#define __XLITE_E_IMAGE_H__


#include "xLite_E_internal.h"



/*!
 * @file xlite_E_image.h
 * @brief 图形资源操作
 */


/*!
 * @brief 创建图型资源
 * @param width: 创建的图形资源的宽度
 * @param height: 创建的图形资源的高度
 * @param pf: 创建的图形资源的像素格式
 * @param flag: 标志位
 * @return 成功返回图形资源的指针,否则返回XL_NULL
 * @note 目前只支持创建(xlite_pf_rgb_565,xlite_pf_index_8,xlite_pf_index_1)这三种格式的图形
 * 和之前的版本有变化,创建的图像缓冲每行为4字节对齐,在计算偏移的时候需要使用资源结构中的
 * bytes_per_pixel
 */
xlite_himage xlite_E_image_create(xl_uint16 width,xl_uint16 height,xlite_pixel_format pf,xl_uint32 flag);

/*!
 * @brief 创建图形资源(扩展版本)
 * @param width: 创建的图形资源的宽度
 * @param height: 创建的图形资源的高度
 * @param pf: 创建的图形资源的像素格式
 * @param shared_buffer:共享的图像缓冲区
 * @param bit_per_pixel:共享的图像缓冲区的像素格式
 * @param flag: 标志位
 */
xlite_himage xlite_E_image_create_ex(xl_uint16 width,xl_uint16 height,xlite_pixel_format pf,xl_uint8* shared_buffer,xl_int32 bit_per_pixel,xl_uint32 flag);


/*!
 * @brief 从himage数组格式创建
 * @param buffer 包含HIMAGE的数组
 * @return 成功返回图形资源的指针,否则返回XL_NULL
 */
xlite_himage xlite_E_image_restore_from_buffer(const xl_uint8* buffer);

/*!
 * @brief 删除图形资源
 * @param image: 图形资源指针
 */
xl_void xlite_E_image_delete(xlite_himage image);

//////////////////////////////////////////////////////////////////////////
// Macro
//////////////////////////////////////////////////////////////////////////

/*!
 * @brief 获取图形的宽度
 * @param himage 图形结构的指针
 * @return 图形的宽度,等同于xlite_image.width
 */
#define xlite_E_image_get_width(h)					((h)->width)

/*!
* @brief 获取图形的高度
* @param himage 图形结构的指针
* @return 图形的高度,等同于xlite_image.height
*/
#define xlite_E_image_get_height(h)					((h)->height)

/*!
 * @brief 获取图形缓冲每行占用的字节数
 * @param himage 图形结构的指针
 * @return 图形缓冲每行占用的字节数
 */
#define xlite_E_image_get_bytes_per_line(h)			((h)->bytes_per_line)

/*!
 * @brief 获取图形缓冲
 * @param himage 图形结构的指针
 * @return 图形缓冲的指针
 */
#define xlite_E_image_get_buffer(h)					((h)->buffer)

/*!
 * @brief 获取指定行的图形缓冲
 * @param himage 图形结构的指针
 * @param line_idx 指定的行
 * @return 图形缓冲的指针
 */
#define xlite_E_image_get_line_buffer(h,l)			( ((h)->line_address) ? (h)->line_address[(l)] : (xl_uint8*)(h)->buffer + ((h)->bytes_per_line * (l)) )

/*!
 * @brief get image palette
 * @param  himage image pointer
 * @return image palette
 */
#define xlite_E_image_get_palette(h)				((h)->palette)

/*!
 * @brief get image pixel format
 * @param himage himage pointer
 * @return pixel format of himage
 */
#define xlite_E_image_get_pixel_format(h)			((h)->pf)

/*!
 * @brief return buffer length
 * @param image himage pointer
 */
#define xlite_E_image_get_buffer_length(h)			((h)->buffer_length)




//////////////////////////////////////////////////////////////////////////
// ADDON
//////////////////////////////////////////////////////////////////////////
#if xlite_E_addon_pcx == 1

#define XLITE_E_ADDON_PCX_ERR_NO_ERROR						0L
#define XLITE_E_ADDON_PCX_ERR_INVALID_PARAM					-1
#define XLITE_E_ADDON_PCX_ERR_INVALID_FORMAT				-2
#define XLITE_E_ADDON_PCX_ERR_OUT_OF_MEMORY					-3
#define XLITE_E_ADDON_PCX_ERR_DECOMPRESS					-4



/*!
 * @brief 从包含PCX文件的缓冲创建图片
 * @param himage_ptr 图形资源指针
 * @param buffer 包含PCX文件内容的缓冲
 * @param buffer_length 缓冲的长度
 * @return 正确返回XLITE_E_ADDON_PCX_ERR_NO_ERROR,*himage_ptr被赋值为读取的图形,否则返回错误代码
 * @note himage中将共享PCX文件缓冲,如果在删除PCX文件缓冲后对该图片操作将会产生错误,如果对该图片执行\n
 * 写操作则后果未知.(如果PCX文件缓冲为const属性,则会产生内存非法访问错误)
 */
xl_int32 xlite_E_image_create_from_pcx(xlite_himage* himage_ptr,const xl_uint8* buffer,xl_uint32 buffer_length);


#else	// xlite_E_addon_pcx

__inline xl_int32 xlite_E_image_create_from_pcx(xlite_himage* himage_ptr,const xl_uint8* buffer,xl_uint32 buffer_length)
{
	return XLITE_E_ERROR_ADDON_UNSUPPORTED;
}

#endif	// xlite_E_addon_pcx





#endif