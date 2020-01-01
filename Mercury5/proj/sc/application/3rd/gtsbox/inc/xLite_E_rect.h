// 
// 
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_E_rect.h 66 2008-06-26 12:27:52Z greatelsoft\nazy $
#ifndef __XLITE_E_RECT_H__
#define __XLITE_E_RECT_H__

#include "xLite_E_internal.h"


/*!
 * @file xLite_E_rect.h
 * @brief 矩形计算
 */



/*!
 * @brief 设置矩形的值
 * @param rect 目标矩形的结构指针
 * @param l 矩形的左边界坐标
 * @param t 矩形的顶部坐标
 * @param r 矩形的右边界坐标
 * @param b 矩形的底部坐标
 */
xl_void xlite_E_rect_set(xlite_rect* rect,xl_int32 l,xl_int32 t,xl_int32 r,xl_int32 b);



/*!
 * @brief 复制一个矩形的值到另外一个矩形
 * @param d_rect 目标矩形
 * @param s_rect 源矩形
 */
xl_void xlite_E_rect_copy(xlite_rect* d_rect,const xlite_rect* s_rect);


/*!
 * @brief 计算两个矩形的交集
 * @param result 矩形结构指针,计算后将结果保存在该矩形中
 * @param r1 矩形结构指针
 * @param r2 矩形结构指针
 * @note resule和(r1/r2)可以是一个矩形结构的指针,例如以下的调用合法 \n
 * xlite_E_rect_get_interset(&my_rect1,&my_rect1,&my_rect2)
 */
xl_void xlite_E_rect_get_intersect(xlite_rect* result,const xlite_rect* r1,const xlite_rect* r2);


/*!
 * @brief 移动矩形
 * @param r 需要移动的矩形
 * @param v 垂直移动的距离
 * @param h 水平移动的距离
 */
xl_void xlite_E_rect_translate(xlite_rect* r,xl_int32 horz,xl_int32 vert);




/*
 * @brief 放大矩形
 * @param r 矩形的指针
 * @param h 水平放大的长度
 * @param v 垂直放大的长度
 * @return
 */
xl_void xlite_E_rect_inflate(xlite_rect* r,xl_int32 h,xl_int32 v);


/*
 * @brief 缩小矩形
 * @param r 矩形的指针
 * @param h 水平缩小的长度
 * @param v 垂直缩小的长度
 * @return
 */
xl_void xlite_E_rect_deflate(xlite_rect* r,xl_int32 h,xl_int32 v);



/*!
 * @brief 获取矩形的宽度
 * @param r 矩形的结构指针
 * @return 返回矩形的宽度
 */
#define xlite_E_rect_get_width(r)			( (r)->right - (r)->left )

/*!
 * @brief 获取矩形的高度
 * @param r 矩形的结构指针
 * @return 返回矩形的高度
 */
#define xlite_E_rect_get_height(r)			((r)->bottom - (r)->top)


/*!
 * @brief 测试一个坐标是否在在矩形中
 * @param r 矩形的结构指针
 * @param x 测试的坐标
 * @param y 测试的坐标
 * @return 如果坐标位于矩形中,则返回XL_TRUE,否则返回XL_FALSE
 * @note 测试算法为 \n
 * 如果 x >= xlite_rect.left \n
 * 并且 x < xlite_rect.right \n
 * 并且 y >= xlite_rect.top  \n
 * 并且 y < xlite_rect.bottom \n
 * 则认为该坐标位于矩形中
 */
#define xlite_E_rect_is_point_inside(r,x,y)		( ((x) >= (r)->left) && ((x) < ((r)->right) && ((y) >= (r)->top) && ((y) < (r)->bottom)) )


/*!
 * @brief 测试一个矩形是否在矩形内部
 * @param r1 测试矩形的结构指针
 * @param r2 测试矩形的结构指针
 * @return 如果r1位于r2内部,则返回XL_TRUE,否则返回XL_FALSE
 */
#define xlite_E_rect_is_rect_inside(r1,r2)	(!( ((r1)->left < (r2)->left ) || ((r1)->top < (r2)->top) || ((r1)->left >= (r2)->right) || ((r1)->top >= (r2)->bottom) || ((r1)->right > (r2)->right) || ((r1)->bottom > (r2)->bottom) ))

/*!
* @brief 测试两个矩形是否有交集
 * @param r1 测试矩形的结构指针
 * @param r2 测试矩形的结构指针
* @return 如果测试的两个矩形存在交集,则返回XL_TRUE,否则返回XL_FALSE
*/
#define xlite_E_rect_is_intersect(r1,r2)	(! (( (r1)->left >= (r2)->right) || ( (r1)->right <= (r2)->left) || ( (r1)->top >= (r2)->bottom) || ( (r1)->bottom <= (r2)->top)) )

		



#endif