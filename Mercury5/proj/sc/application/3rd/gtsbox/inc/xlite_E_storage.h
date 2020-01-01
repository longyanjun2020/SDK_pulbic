// xlite storage
// 
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xlite_E_storage.h 8 2008-05-21 03:28:23Z greatelsoft\ken $
#ifndef __XLITE_E_STORAGE_H__
#define __XLITE_E_STORAGE_H__

#include "xLite_E_internal.h"

/*
 * @brief Initialize storage structure
 * @param storage pointing to storage structure 
 * @param number_list_node_reserved 
 */
xl_void xlite_E_storage_init(xlite_storage* storage,xlite_E_storage_delete_data_callback delete_data_cb,xl_void* callback_param,xl_uint32 number_list_node_reserved);




/*
 * @brief Delete storage structure
 * @param storage pointing to storage structure
 */
xl_void xlite_E_storage_delete(xlite_storage* storage);


/*
 * @brief add a data to storage
 * @param storage pointing to storage
 * @param hash hash of data
 * @param data data to add
 * @return TRUE if added,FALSE if data already in the storage, add() add a reference number of storage.
 */
xl_bool xlite_E_storage_add(xlite_storage* storage,xl_uint32 hash,xl_void* data);


/*
 * @brief get a data from storage
 * @param storage pointing to storage
 * @param hash hash of data to find
 * @return Nonzero if successful, otherwise NULL
 */
xlite_storage_node* xlite_E_storage_get(xlite_storage* storage,xl_uint32 hash,xl_bool add_ref_num);


/*
 * @brief delete a data 
 * @param storage pointing to storage
 * @param hash hash of data to delete
 * @param ignore_ref_num ignore reference number.always real delete it
 */
xl_int32 xlite_E_storage_delete_data(xlite_storage* storage,xl_uint32 hash,xl_bool ignore_ref_num);

/*
 * @brief delete a data
 * @param storage pointing to storage
 * @param data_ptr data to delete
 * @param ignore_ref_num ignore reference number.always real delete it
 */
xl_int32 xlite_E_storage_delete_data_by_ptr(xlite_storage* storage,xl_void* data_ptr,xl_bool ignore_ref_num);


#endif