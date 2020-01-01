// TileMap Render
// 
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_E_tilemap_render.h 209 2009-07-21 02:24:47Z nazy $
#ifndef __XLITE_E_TILEMAP_RENDER_H__
#define __XLITE_E_TILEMAP_RENDER_H__


#include "xLite_E_internal.h"

/*!
 * @file xLite_E_tilemap_render.h
 * @brief 地图渲染接口
 */


/*!
 * @brief 初始化渲染器
 * @param tilemap_render 渲染器指针
 * @param data 地图数据指针
 * @param graphics Graphics的结构指针
 */
xl_void xlite_E_tilemap_render_init(xlite_tilemap_render* tilemap_render,xlite_tilemap_data* data,xlite_graphics* graphics);


/*!
 * @brief 设置视口
 * @param tilemap_render 渲染器指针
 * @param left 左
 * @param top 上
 * @param right 右
 * @param right 下
 */
xl_void xlite_E_tilemap_render_set_viewport(xlite_tilemap_render* tilemap_render,xl_int32 left,xl_int32 top,xl_int32 right,xl_int32 bottom);


/*!
 * @brief 是否开启缓存
 * @param tilemap_render 渲染器指针
 * @param enable_cache 是否开启缓存
 */
xl_bool xlite_E_tilemap_render_enable_cache(xlite_tilemap_render* tilemap_render,xl_bool enable_cache);


/*!
 * @brief 开始缓存
 * @param tilemap_render 渲染器指针
 * @param map_pos_x 地图x坐标
 * @param map_pos_y 地图y坐标
 */
xl_void xlite_E_tilemap_render_begin_cache(xlite_tilemap_render* tilemap_render,xl_int32 map_pos_x,xl_int32 map_pos_y);


/*!
 * @brief 停止缓存
 * @param tilemap_render 渲染器指针
 */
xl_void xlite_E_tilemap_render_end_cache(xlite_tilemap_render* tilemap_render);

/*!
 * @brief 渲染一层地图
 * @param tilemap_render 渲染器指针
 * @param map_pos_x 地图x坐标
 * @param map_pos_y 地图y坐标
 * @param layer_index 层索引
 * @param cached 是否缓存
 */
xl_void xlite_E_tilemap_render_draw_layer(xlite_tilemap_render* tilemap_render,xl_int32 map_pos_x,xl_int32 map_pos_y,xl_uint8 layer_index,xl_bool cached);


#endif