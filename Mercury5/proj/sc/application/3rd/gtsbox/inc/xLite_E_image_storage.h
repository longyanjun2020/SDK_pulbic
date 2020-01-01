// 
// 
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_E_image_storage.h 209 2009-07-21 02:24:47Z nazy $
#ifndef __XLITE_E_IMAGE_STORAGE_H__
#define __XLITE_E_IMAGE_STORAGE_H__

#include "xLite_E_internal.h"

/*!
 * @file xLite_E_image_storage.h
 * @brief 图形管理器
 */


/*
 * @brief 初始化图像存储器
 * @param storage 图像存储器结构指针
 */
xl_void xlite_E_image_storage_init(xlite_image_storage* storage);

/*
 * @brief 删除图像存储器
 * @param storage 图像存储器结构指针
 */
xl_void xlite_E_image_storage_delete(xlite_image_storage* storage);


/*!
 * @brief 增加图形资源到图像存储器
 * @param storage 图像存储器结构指针
 * @param hash 图形的hash值
 * @param himage 图形的资源指针
 * @return 如果成功加入图片返回XL_TRUE,如果在管理器中已经存在相同hash的图性资源\n
 * 则增加该资源的引用计数删除传入的图片,并且返回XL_FALSE
 */
xl_bool xlite_E_image_storage_add(xlite_image_storage* storage,xl_uint32 hash,xlite_himage himage);


/*!
 * @brief 从图像存储器中查找图型
 * @param storage 图像存储器结构指针
 * @param hash 图形的hash值
 * @return 如果管理器中存在相应hash的图形,则返回该图形资源的指针,否则返回XL_NULL
 */
xlite_storage_node* xlite_E_image_storage_get(xlite_image_storage* storage,xl_uint32 hash,xl_bool add_ref);


/*!
 * @brief 卸载精灵管理器中的图片
 * @param storage 精灵管理器指针
 * @param hash 需要删除的图形资源的指针
 * @param ignore_ref_num 忽略引用计数删除
 * @return 如果图片还在被其他资源引用,返回当前的引用计数,否则返回0,如果图片不存在返回-1L
 * @note 该函数会检查该资源的使用情况决定是减少引用计数还是删除改图片
 */
xl_int32 xlite_E_image_storage_delete_image(xlite_image_storage* storage,xl_uint32 hash,xl_bool ignore_ref_num);

/*!
 * @brief 卸载精灵管理器中的图片
 * @param storage 精灵管理器指针
 * @param himage 需要删除的图形资源的指针
 * @param ignore_ref_num 忽略引用计数删除
 * @return 如果图片还在被其他资源引用,返回当前的引用计数,否则返回0,如果图片不存在返回-1L
 * @note 该函数会检查该资源的使用情况决定是减少引用计数还是删除改图片
 */
xl_int32 xlite_E_image_storage_delete_image_by_ptr(xlite_image_storage* storage,xlite_himage himage,xl_bool ignore_ref_num);



#endif