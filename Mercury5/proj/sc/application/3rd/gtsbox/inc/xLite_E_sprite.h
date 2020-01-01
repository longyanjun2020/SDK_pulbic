// 
// 
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_E_sprite.h 209 2009-07-21 02:24:47Z nazy $
#ifndef __XLITE_E_SPRITE_H__
#define __XLITE_E_SPRITE_H__

#include "xLite_E_internal.h"


/*!
 * @file xLite_E_sprite.h
 * @brief 精灵加载/管理/绘制
 */

//////////////////////////////////////////////////////////////////////////
// FUNCTION (API)
//////////////////////////////////////////////////////////////////////////

/*!
 * @brief 初始化精灵管理器
 * @param storage 精灵管理器结构指针
 * @param image_storage 图形管理器结构指针
 */
xl_void xlite_E_sprite_storage_init(xlite_sprite_storage* storage,xlite_image_storage* image_storage);

/*!
 * @brief 获取精灵数据指针
 * @param storage 精灵管理器指针
 * @param hash 精灵数据的hash值
 * @param add_ref_num 是否增加引用计数
 * @return 成功返回精灵数据的指针,否则返回XL_NULL
 */
xlite_storage_node* xlite_E_sprite_storage_get(xlite_sprite_storage* storage,xl_uint32 hash,xl_bool add_ref_num);

/*!
 * @brief 删除精灵数据
 * @param storage 精灵管理器指针
 * @param hash 精灵数据的hash值
 * @param ignore_ref_num 是否忽略引用计数
 * @param hash 成功返回1L,失败返回0L
 */
xl_int32 xlite_E_sprite_storage_delete_data(xlite_sprite_storage* storage,xl_uint32 hash,xl_bool ignore_ref_num);


/*!
 * @brief 删除精灵管理器
 * @param storage 精灵管理器指针
 */
xl_void xlite_E_sprite_storage_delete(xlite_sprite_storage* storage);


/*!
 * @brief 添加一个精灵数据到存储管理器
 * @param storage 存储器指针
 * @param hash 精灵数据的hash值
 * @param data 精灵数据
 */
xl_bool xlite_E_sprite_storage_add(xlite_sprite_storage* storage,xl_uint32 hash,xlite_sprite_data* data);

/*!
 * @brief 创建精灵
 * @param hash 精灵的hash值
 * @param pool_size 精灵需要的内存字节数
 * @return 成功返回精灵的结构指针,否则返回XL_NULL
 */
xlite_sprite_data* xlite_E_sprite_data_create(xl_uint32 hash,xl_uint32 pool_size);

/*!
 * @brief 删除精灵数据,并且释放该精灵依赖的其他资源
 * @param storage 精灵存储器指针
 * @param data 精灵数据指针
 */
xl_void xlite_E_sprite_data_delete(xlite_sprite_storage* storage,xlite_sprite_data* data);

/*!
 * @brief 获取精灵数据的hash值
 * @param d 精灵数据指针
 * @return 精灵的Hash值
 */
#define xlite_E_sprite_data_get_hash(d)				((d)->hash)

/*!
 * @brief 获取精灵的图片资源
 * @param data 精灵数据指针
 * @param index 图片的索引
 * @return 图片资源指针
 */
#define xlite_E_sprite_data_get_image(d,i)			((d)->images[(i)])

/*!
 * @brief 获取Pair values的指针
 * @param data 精灵数据指针
 */
#define xlite_E_sprite_data_get_pv_buffer(d)		((d)->pair_values)




//////////////////////////////////////////////////////////////////////////
#if xlite_E_addon_sprite_j10 == 1


#define XLITE_E_ADDON_SPRITE_J10_ERR_NO_ERROR					0L
#define XLITE_E_ADDON_SPRITE_J10_ERR_FILE_HEADER				-1L
#define XLITE_E_ADDON_SPRITE_J10_ERR_RESOURCES					-2L
#define XLITE_E_ADDON_SPRITE_J10_ERR_PAIR_VALUES				-3L
#define XLITE_E_ADDON_SPRITE_J10_ERR_OUT_OF_MEMORY				-10L


/*!
 * @brief 从.j10的缓冲中读取精灵
 * @param storage 精灵管理器结构指针
 * @param hash 精灵的hash值
 * @param buffer J10的缓冲
 * @param length 缓冲的长度(字节)
 * @param 读取精灵图片的回调函数指针
 * @note 因为精灵是一种包含其他资源的资源,因此通过回调函数来加载精灵依赖的其他资源.\n
 * 当精灵加载资源的时候,首先在精灵管理器中查找需要的资源,如果该资源不存在并且回调函数 \n
 * 为NULL,读取精灵失败,如果该资源不存在但是存在回调函数,函数尝试通过回调函数加载资源，如果\n
 * 该回调函数加载资源也失败的话则精灵加载也将失败。
 */
xl_int32 xlite_E_sprite_data_load_j10(xlite_sprite_storage* storage,xl_uint32 hash,const xl_uint8* buffer,xl_uint32 length,xlite_E_sprite_on_load_image on_load_image_callback);


#else // xlite_E_addon_sprite_j10

__inline xl_int32 xlite_E_sprite_data_load_j10(xlite_sprite_storage* storage,xl_uint32 hash,const xl_uint8* buffer,xl_uint32 length,xlite_E_sprite_on_load_image on_load_image_callback)
{
	return XLITE_E_ERROR_ADDON_UNSUPPORTED;
}

#endif




#endif