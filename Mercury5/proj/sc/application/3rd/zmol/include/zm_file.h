#ifndef _ZHANGM_STOCK_FILE_H_
#define _ZHANGM_STOCK_FILE_H_

#include "zm_typedef.h"

/*----------------------------------------------------------
 * 文件操作
 *----------------------------------------------------------*/
/*
 * 检查磁盘空间
 */
zm_extern zm_bool zm_check_drive_free_space(const zm_int8* dir_name, zm_int needsize);

/*
 * 创建目录
 */
zm_extern zm_int32 zm_create_file_folder(zm_int8 *strFileName, zm_bool bfullName);

/*
 *	打开或创建文件，参数请参考标准C中的参数 
 */
zm_extern zm_file* zm_fopen(const zm_int8* pszFileName, zm_uint16 nResFileId, const zm_int8* pszMode);

/*
 *	读数据，参数请参考标准C中的参数 
 */
zm_extern zm_int zm_fread(zm_void* pszBuffer, zm_int nSize, zm_int nCount, zm_file* pFile);

/*
 * 写数据， 参数请参考标准C中的参数
 */
zm_extern zm_int zm_fwrite(const zm_void* pszBuffer, zm_int nSize, zm_int nCount, zm_file* pFile);

/*
 *	定位文件指针, 失败返回  -1, 成功返回 0
 *  whence:
 *      ZM_SEEK_CUR, //Current position of file pointer
 *		ZM_SEEK_END, //End of file
 *		ZM_SEEK_SET	 //Beginning of file
 */
zm_extern zm_int zm_fseek(zm_file* pFile, zm_int nOffset, zm_file_seek_type whence);

/*
 *	关闭文件指针 失败返回  -1, 成功返回 0
 */
zm_extern zm_int zm_fclose(zm_file* pFile);

/*
 *	获取文件大小, 文件不存在返回 -1
 */
zm_extern zm_int zm_fsize(zm_file* pFile);

/*
 *	删除文件, 成功返回 0， 失败返回 -1
 */
zm_extern zm_int zm_unlink(const zm_int8* pszFileName);


/*----------------------------------------------------------
 * 文件遍历查找接口
 *----------------------------------------------------------*/
zm_extern zm_int zm_file_find_first(const zm_int8* name, zm_int8* buffer, zm_int len, zm_bool* b_dir);

zm_extern zm_int zm_file_find_next(zm_int search_handle, zm_int8* buffer, zm_int len, zm_bool* b_dir);

zm_extern zm_int zm_file_find_close(zm_int search_handle);

/*--------------------------------------------------
 * 获取卡的盘符
 *--------------------------------------------------*/
zm_extern zm_int8 zm_get_system_drive(zm_void);
zm_extern zm_int8 zm_get_card_drive(zm_void);

#endif/*_ZHANGM_STOCK_FILE_H_*/
