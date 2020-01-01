// 
// 
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_E_list.h 8 2008-05-21 03:28:23Z greatelsoft\ken $
#ifndef __XLITE_E_LIST_H__
#define __XLITE_E_LIST_H__

#include "xLite_internal.h"

/*!
 * @file xlite_E_list.h
 * @brief Ë«ÏòÁ´±í
 */

/*!
 * @brief Initialize a list
 * @param l: list pointer
 * @param size_pool: size of node pool, 0 is means no node pool in list
 */
xl_void xlite_E_list_init(xlite_list* l,xl_uint32 pool_size);


/*!
* @brief destroy list structure
* @param l: list pointer
*/
xl_void xlite_E_list_destroy(xlite_list* l);

/*!
* @brief clear list items
* @param l: list pointer
*/
xl_void xlite_E_list_clear(xlite_list* l);

/*!
* @brief remove a node from list
* @param l: list pointer
* @param n: node pointer
*/
xl_void xlite_E_list_remove(xlite_list* l,xlite_list_node* n);

/*!
 * @brief remove header 
 * @param l: list pointer
 * @return data of header
 */
xl_void* xlite_E_list_remove_head(xlite_list* l);

/*!
 * @brief remove tail of list
 * @param l: list pointer
 * @return data of tail
 */
xl_void* xlite_E_list_remove_tail(xlite_list* l);

/*!
 * @brief find data in the list
 * @param l: list pointer
 * @param data: item find
 * @return It return list node if successed,else XL_NULL returned
 */
xlite_list_node* xlite_E_list_find(xlite_list* l,const xl_void* data);


/*!
 * @brief add data to tail of list
 * @param l: list pointer
 * @param data:data pointer
 * @return return XL_TRUE if successed,else XL_FALSE returned
 */
xl_bool xlite_E_list_add_tail(xlite_list* l,xl_void* data);

/*!
 * @brief insert data to list
 * @param l: list pointer
 * @param before_node: insert before this node
 * @param data: data pointer
 * @return return XL_TRUE if successed,else XL_FALSE returned
 */
xl_bool xlite_E_list_insert_before(xlite_list* l,xlite_list_node* before_node,xl_void* data);

/*!
 * @brief add data to head of list
 * @param l: list pointer
 * @param data: data pointer
 * @return return XL_TRUE if successed,else XL_FALSE returned
 */
xl_bool xlite_E_list_add_head(xlite_list* l,xl_void* data);

//////////////////////////////////////////////////////////////////////////
// Macro
//////////////////////////////////////////////////////////////////////////

/*!
 * @brief return the size of list
 * @param l: list pointer
 * @return number of nodes
 */
#define xlite_E_list_get_size(l)					((l)->number_nodes)

/*!
 * @brief return the head of list
 * @param l: list pointer
 * @return head node of list
 */
#define xlite_E_list_get_head(l)					((l)->head)

/*!
 * @brief return the tail of list
 * @param l: list pointer
 * @return tail node of list
 */
#define xlite_E_list_get_tail(l)					((l)->tail)

/*!
 * @brief return the next node 
 * @param n: node pointer
 * @return It return the next node from current node,return XL_NULL if reached the end of list
 */
#define xlite_E_list_get_next(n)					((n)->next)

/*!
* @brief return the previous node 
* @param n: node pointer
* @return It return the previous node from current node,return XL_NULL if reached the top of list
*/
#define xlite_E_list_get_prev(n)					((n)->prev)


/*!
 * @brief return if the list is empty
 * @param l: list pointer
 * @return return XL_TRUE if list is empty,else return false
 */
#define xlite_E_list_is_empty(l)					((l)->number_nodes > 0)




#endif