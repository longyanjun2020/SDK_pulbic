// 
// 
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_E_tilemap.h 209 2009-07-21 02:24:47Z nazy $
#ifndef __XLITE_E_TILEMAP_H__
#define __XLITE_E_TILEMAP_H__

#include "xLite_E_internal.h"
/*!
 * @file xLite_E_tilemap.h
 * @brief 地图加载/管理/绘制
 */


#define XLITE_E_TILEMAP_IMAGE						0x01
#define XLITE_E_TILEMAP_SPRITE						0x02

#define XLITE_E_TILEMAP_LAYER_TILE					0x01
#define XLITE_E_TILEMAP_LAYER_FREE					0x02
#define XLITE_E_TILEMAP_LAYER_TILEFLAG				0x03

#define XLITE_E_TILEMAP_LAYER_FLAG_BKCOLOR			0x01


#define XLITE_E_TILEMAP_SORT_HP_TOP_BOTTOM				0x01
#define XLITE_E_TILEMAP_SORT_HP_BOTTOM_TOP				0x02
#define XLITE_E_TILEMAP_SORT_HP_LEFT_RIGHT				0x04
#define XLITE_E_TILEMAP_SORT_HP_RIGHT_LEFT				0x08
#define XLITE_E_TILEMAP_SORT_LP_TOP_BOTTOM				0x10
#define XLITE_E_TILEMAP_SORT_LP_BOTTOM_TOP				0x20
#define XLITE_E_TILEMAP_SORT_LP_LEFT_RIGHT				0x40
#define XLITE_E_TILEMAP_SORT_LP_RIGHT_LEFT				0x80			

#define XLITE_E_TILEMAP_BLEND_COPY						0x00
#define XLITE_E_TILEMAP_BLEND_ADDITIVE					0x01
#define XLITE_E_TILEMAP_BLEND_QUARTERADD				0x02
#define XLITE_E_TILEMAP_BLEND_ALPHA						0x03
#define XLITE_E_TILEMAP_BLEND_SUB						0x04	// Not support	

/*!
 * @brief 初始化地图存储管理器
 * @param tilemap_storage 地图存储管理器指针
 * @param image_storage 图片存储管理器指针
 * @param sprite_storage 精灵存储管理器指针
 */
xl_void xlite_E_tilemap_storage_init(xlite_tilemap_storage* tilemap_storage,xlite_image_storage* image_storage,xlite_sprite_storage* sprite_storage);

/*!
 * @brief 删除地图存储管理器
 * @param tilemap_storage 地图存储管理器指针
 */
xl_void xlite_E_tilemap_storage_delete(xlite_tilemap_storage* tilemap_storage);

/*!
 * @brief 查找地图
 * @param storage 存储管理器
 * @param hash 被查找地图的hash
 * @return 成功返回包含地图的storage_node,否则返回NULL
 */
xlite_storage_node* xlite_E_tilemap_storage_get(xlite_tilemap_storage* storage,xl_uint32 hash,xl_bool add_ref_num);

/*!
 * @brief 添加地图数据到地图存储管理器
 * @param tilemap_storage 地图存储管理器指针
 * @return
 */
xl_bool xlite_E_tilemap_storage_add(xlite_tilemap_storage* storage,xl_uint32 hash,xlite_tilemap_data* data);


/*!
 * @brief Delete tilemap from stroage
 * @param 
 * @return
 */
xl_int32 xlite_E_tilemap_storage_delete_data(xlite_tilemap_storage* storage,xl_uint32 hash,xl_bool ignore_ref);

/*!
 * @brief Create a tilemap data
 * @param 
 * @return
 */
xlite_tilemap_data* xlite_E_tilemap_data_create(xl_uint32 hash,xl_uint8 scene_index);


/*!
 * @brief delete tilemap data
 * @param
 * @return
 */
xl_void xlite_E_tilemap_data_delete(xlite_tilemap_storage* storage,xlite_tilemap_data* data);

//////////////////////////////////////////////////////////////////////////
#if xlite_E_addon_tilemap_j11 == 1


#define XLITE_E_ADDON_TILEMAP_J11_ERR_NO_ERROR					0L
#define XLITE_E_ADDON_TILEMAP_J11_ERR_FILE_HEADER				-1L
#define XLITE_E_ADDON_TILEMAP_J11_ERR_RESOURCES					-2L
#define XLITE_E_ADDON_TILEMAP_J11_ERR_PAIR_VALUES				-3L
#define XLITE_E_ADDON_TILEMAP_J11_ERR_INVALID_SCENE_INDEX		-4L
#define XLITE_E_ADDON_TILEMAP_J11_ERR_LOAD_FRAME_DATA			-5L
#define XLITE_E_ADDON_TILEMAP_J11_ERR_OUT_OF_MEMORY				-10L


#define XLITE_E_ADDON_TILEMAP_J11_RES_IMAGE						XLITE_E_TILEMAP_IMAGE
#define XLITE_E_ADDON_TILEMAP_J11_RES_SPRITE					XLITE_E_TILEMAP_SPRITE

#define XLITE_E_ADDON_TILEMAP_J11_LAYER_TILE					XLITE_E_TILEMAP_LAYER_TILE
#define XLITE_E_ADDON_TILEMAP_J11_LAYER_FREE					XLITE_E_TILEMAP_LAYER_FREE
#define XLITE_E_ADDON_TILEMAP_J11_LAYER_TILEFLAG				XLITE_E_TILEMAP_LAYER_TILEFLAG

#define XLITE_E_ADDON_TILEMAP_J11_SORT_HP_TOP_BOTTOM			XLITE_E_TILEMAP_SORT_HP_TOP_BOTTOM
#define XLITE_E_ADDON_TILEMAP_J11_SORT_HP_BOTTOM_TOP			XLITE_E_TILEMAP_SORT_HP_BOTTOM_TOP
#define XLITE_E_ADDON_TILEMAP_J11_SORT_HP_LEFT_RIGHT			XLITE_E_TILEMAP_SORT_HP_LEFT_RIGHT
#define XLITE_E_ADDON_TILEMAP_J11_SORT_HP_RIGHT_LEFT			XLITE_E_TILEMAP_SORT_HP_RIGHT_LEFT
#define XLITE_E_ADDON_TILEMAP_J11_SORT_LP_TOP_BOTTOM			XLITE_E_TILEMAP_SORT_LP_TOP_BOTTOM
#define XLITE_E_ADDON_TILEMAP_J11_SORT_LP_BOTTOM_TOP			XLITE_E_TILEMAP_SORT_LP_BOTTOM_TOP
#define XLITE_E_ADDON_TILEMAP_J11_SORT_LP_LEFT_RIGHT			XLITE_E_TILEMAP_SORT_LP_LEFT_RIGHT
#define XLITE_E_ADDON_TILEMAP_J11_SORT_LP_RIGHT_LEFT			XLITE_E_TILEMAP_SORT_LP_RIGHT_LEFT


#define XLITE_E_ADDON_TILEMAP_J11_IMAGEFLAG_FLIP_HORZ					0x01
#define XLITE_E_ADDON_TILEMAP_J11_IMAGEFLAG_FLIP_VERT					0x02
#define XLITE_E_ADDON_TILEMAP_J11_IMAGEFLAG_BLEND_ADD					0x04
#define XLITE_E_ADDON_TILEMAP_J11_IMAGEFLAG_BLEND_SUB					0x08
#define XLITE_E_ADDON_TILEMAP_J11_IMAGEFLAG_BLEND_QUARTERADD			0x10
#define XLITE_E_ADDON_TILEMAP_J11_IMAGEFLAG_BLEND_ALPHA					0x20
#define XLITE_E_ADDON_TILEMAP_J11_IMAGEFLAG_FILTER_KEYCOLOR				0x40



/*!
 * @brief 创建j11解码器
 */
xl_bool xlite_E_tilemap_j11_dec_init(xlite_tilemap_j11_decoder* dec,xl_uint32 hash,const xl_uint8* buffer,xl_uint32 buffer_length);

/*!
 * @brief 读取j11文件到storage
 */
xl_bool xlite_E_tilemap_j11_dec_load(xlite_tilemap_storage* storage,xlite_tilemap_j11_decoder* dec,xl_uint8 scene_index,xlite_tilemap_load_callback* load_callback);

/*!
 * @brief 删除j11解码器
 */
xl_void xlite_E_tilemap_j11_dec_delete(xlite_tilemap_j11_decoder* dec);


#else



#endif

#endif