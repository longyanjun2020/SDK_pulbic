#ifndef __XLITE_H_RES_MANAGER_H__ 
#define __XLITE_H_RES_MANAGER_H__

typedef struct  
{
	xl_uint32 hash;
	xl_uint8* buf;
	xl_uint32 len;
}xlite_res_data_struct;

xlite_himage xlite_H_res_load_image(xl_uint32 hash);

xl_void xlite_H_res_delete_image(xlite_himage image_del);

xlite_sprite_data* xlite_H_res_load_sprite_data(xl_uint32 hash);

xl_void xlite_H_res_delete_sprite_data(xlite_sprite_data* data_del);

xlite_res_data_struct* xlite_H_res_load_res(xl_uint32 hash);

xl_void xlite_H_res_delete_res(xl_uint8* res_del);

xl_void xlite_H_res_manager_release(xl_void);

xl_void xlite_H_res_manager_create(xl_void);

xl_void xlite_H_res_set_res_table(xlite_res_data_struct* table);

// 是否使用自定义的资源读取函数，比如gtsbox读取外部资源
xl_void xlite_H_res_reg_res_func(void(*load_func)(xl_uint32 hash, xl_void** data, xl_uint32* len), void(*delete_func)(xl_void*));

#endif