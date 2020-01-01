// 
// 
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_E_image_GIF.h 209 2009-07-21 02:24:47Z nazy $
#ifndef __XLITE_E_IMAGE_GIF_H__
#define __XLITE_E_IMAGE_GIF_H__


#include "xLite_E_internal.h"

/*!
 * @file xlite_E_image_GIF.h
 * @brief gif图形资源操作
 */


#if xlite_E_addon_gif == 1


#define XLITE_E_ADDON_GIF_ERR_NO_ERROR						0
#define XLITE_E_ADDON_GIF_ERR_UNKNOWN_FORMAT				-1
#define XLITE_E_ADDON_GIF_ERR_OUT_OF_MEMORY					-2
#define XLITE_E_ADDON_GIF_ERR_UNKNOWN_SEGMET_ID				-3
#define XLITE_E_ADDON_GIF_ERR_IMAGE_DEFECT					-4
#define XLITE_E_ADDON_GIF_ERR_EOF_TOO_SOON					-5
#define XLITE_E_ADDON_GIF_ERR_BPP_UNSUPPORTED				-6
#define XLITE_E_ADDON_GIF_ERR_ALREADY_OPENED				-7


/*!
 * @brief 从缓冲创建图形资源
 * @param himage_ptr 图形资源指针的指针
 * @param buffer 包含GIF文件内容的缓冲
 * @param buffer_length 缓冲的长度
 * @return 成功返回XLITE_E_ADDON_GIF_ERR_NO_ERROR,否则返回小于0的错误代码。
 * @note 该函数只支持8bit的GIF图形,并且只处理GIF第一帧图形
 */
xl_int32 xlite_E_image_load_gif(xlite_himage* himage_ptr,const xl_uint8* buffer,xl_uint32 buffer_length);



// /*!
//  * @brief 创建Gif解码器
//  * @return 成功返回解码器句柄,否则返回NULL
//  * @note 解码器需要约17K的内存创建LZW表\n
//  * 如果使用xlite_use_static == 1选项编译xlite,则无需动态申请内存
//  */
// xlite_gif_hdecoder xlite_E_image_create_gif_decoder(xl_void);
// 
// 
// /*!
//  * @brief 使用解码器解码包含GIF文件内容的缓冲
//  * @param decoder GIF解码器句柄
//  * @param himage_ptr 图形资源指针的指针
//  * @param buffer 包含GIF文件内容的缓冲
//  * @param buffer_length 缓冲的长度
//  * @return 成功返回XLITE_E_ADDON_GIF_ERR_NO_ERROR,否则返回小于0的错误代码
//  */
// xl_int32 xlite_E_image_decode_gif(xlite_gif_hdecoder hdecoder,xlite_himage* himage_ptr,const xl_uint8* buffer,xl_uint32 buffer_length);
// 
// 
// /*!
//  * @brief 删除Gif解码器
//  * @param hdecoder 解码器句柄
//  */
// xl_void xlite_E_image_delete_gif_decoder(xlite_gif_hdecoder hdecoder);



#endif


#endif