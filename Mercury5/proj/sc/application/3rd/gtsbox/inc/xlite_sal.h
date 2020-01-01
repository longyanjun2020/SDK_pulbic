#ifndef __XLITE_SAL_H__
#define __XLITE_SAL_H__

/*!
 * @file xLite_sal.h
 * @brief xstrike lite sal层接口
 */

//////////////////////////////////////////////////////////////////////////
// VERSION

/*!
 * @brief xstrikelite主版本号
 */
#define XLITE_VER_MAJOR					1

/*!
 * @brief xstrikelite副版本号
 */
#define XLITE_VER_MINOR					0

//////////////////////////////////////////////////////////////////////////
// Configure

/*!
 * @brief 尽量使用static/global段,代码尺寸增大,运行期内存需求减少
 */
#define xlite_use_static				0

/*!
 * @brief 是否有debug的函数接口
 */
//#if defined(XLITE_DEBUG)
#define xlite_use_debug					1
//#else
//#define xlite_use_debug					0
//#endif

#if   xlite_mstar_flash_version == NAND_FLASH
	#define MSTAR_FLASH   L"/NAND"
#endif 	
#if   xlite_mstar_flash_version == NOR_FLASH
	#define MSTAR_FLASH    L"/NOR_FLASH_0"
#endif

#define MSTAR_CARD      L"/CARD"


/*!
 * @brief 测试时不使用static函数和变量
 */
#if defined(XLITE_TEST)
	#define XL_STATIC 
#else
	#define XL_STATIC static
#endif


#define xlite_sal_version			1
#define xlite_sal_directscreen		1
#define xlite_sal_file				1
#define xlite_sal_sys				1
#define xlite_sal_socket			1
#define xlite_sal_string			1
#define xlite_sal_drawtext			1
#define xlite_sal_audio				1
#define xlite_sal_memory			1
#define xlite_sal_input_screen		1
#define xlite_sal_log				1
#define xlite_sal_assert				1
#define xlite_sal_sensor			1


typedef xl_void (* record_fun)(xl_int32);

#if xlite_sal_version == 1
/////////////////////////////////////////////////////////////////////////////////
// xLite_version.h

/*!
 * @brief 获取当前的xstrike lite引擎版本
 * @param ver xlite_version结构指针
 * @note 该函数将引擎版本填入传递入的xlite_version的结构指针
 */
xl_void xlite_version_get(xlite_version* ver);

/*!
 * @brief 获取当前的手机编译时间
 */
xl_char* xlite_compile_time_get(xl_void);

#endif

#if xlite_sal_directscreen == 1
/////////////////////////////////////////////////////////////////////////////////
// xLite_directscreen.h
// brief DirectScreen Access controller
//

/*!
 * @brief 打开DirectScreen的写入控制
 * @param ds DirectScreen的结构指针
 * @param flag 保留,可以填入0
 * @return 成功返回XL_TRUE, 否则返回XL_FALSE
 */
xl_bool xlite_directscreen_open(xlite_directscreen* ds,xl_uint8 flag);

/*!
 * @brief 关闭打开的DirectScreen的写入控制
 * @param ds DirectScreen的结构指针
 */
xl_void xlite_directscreen_delete(xlite_directscreen* ds);

/*!
 * @brief 更新DirectScreen到屏幕
 * @param ds DirectScreen结构指针
 */
xl_void xlite_directscreen_update(xlite_directscreen* ds);

/*!
 * @brief 挂起屏幕写入控制
 * @param ds DirectScreen结构指针
 */
xl_void xlite_directscreen_suspend(xlite_directscreen* ds);

/*!
 * @brief 恢复挂起的写入控制
 * @param ds DirectScreen结构指针
 * @note 必须与xlite_directscreen_suspend配对使用
 */
xl_void xlite_directscreen_resume(xlite_directscreen* ds);

/*!
 * @brief 查询屏幕的宽度
 * @param ds DirectScreen结构指针
 * @return 屏幕的宽度,等同于 xlite_directscreen.screen_width
 */
#define xlite_directscreen_get_width(ds)					((xl_uint32)(ds)->screen_width)

/*!
 * @brief 查询屏幕的高度
 * @param ds DirectScreen结构指针
 * @return 屏幕的高度,等同于 xlite_directscreen.screen_height
 */
#define xlite_directscreen_get_height(ds)					((xl_uint32)(ds)->screen_height)

#endif

#if xlite_sal_file == 1
/////////////////////////////////////////////////////////////////////////////////
// xLite_file.h
// 文件IO接口
//

/*!
 * @breif 打开一个文件
 * @param filename 文件的完整路径名，要求是xl_wchar类型字符串  
 * @param mode 打开方式
 * @return 文件句柄，为0则打开失败
 */
xlite_file_handle xlite_file_open(const xl_wchar* filename,xl_uint32 mode);

/*!
 * @brief close file handle
 * @param file_handle: 文件句柄
 */
xl_void xlite_file_close(xlite_file_handle file_handle);


/*! 
 * @brief 读文件
 * @param fh 文件句柄
 * @param buffer 数据储存位置
 * @param length 要读取的数据长度，以字节为单位
 * @param length_read 实际读取长度
 * @return 大于等于0为实际读取长度，小于0为错误代码
 */
xl_int32 xlite_file_read(xlite_file_handle fh,xl_void* buffer,xl_uint32 buffer_length,xl_uint32* length_read);


/*!
 * @brief 写文件
 * @param fh 文件句柄
 * @param buffer 数据储存位置
 * @param length 要写入的数据长度，以字节为单位
 * @param length_read 实际写入长度
 * @return 大于等于0为实际写入长度，小于0为错误代码
 */
xl_int32 xlite_file_write(xlite_file_handle fh,xl_void* buffer,xl_uint32 buffer_length,xl_uint32* length_written);


/*!
 * @brief 文件内搜索
 * @param fh 文件句柄
 * @param offset 相对于起始点的偏移.
 * @param origin 起始点.
 * @return 成功返回0，否则返回错误代码.
 */
xl_int32 xlite_file_seek(xlite_file_handle fh,xl_int32 offset,xl_int32 origin);


/*!
 * @brief 获取文件大小
 * @param fh 文件句柄
 * @param file_size 文件大小
 * @return 成功返回0，否则返回错误代码
 */
xl_int32 xlite_file_get_size(xlite_file_handle fh,xl_uint32* file_size);

/*!
* @brief 获取文件内部当前位置
* @param fh 文件句柄
* @return 成功返回当前位置，小于0为错误代码
*/
xl_int32 xlite_file_get_position(xlite_file_handle fh);


/*!
 * @brief 返回数据文件盘符
 * @param type 驱动器类型
 * @param serial 序列
 * @return 驱动器盘符
 * @note 获取系统盘盘符: xlite_file_get_driver(xlite_driver_system,1) \n
 * 获取普通盘盘符: xlite_file_get_driver(xlite_driver_normal,1)
 */
xl_char* xlite_file_get_driver(xlite_driver_type type,xl_int32 serial);

/*!
 * @brief 删除文件
 * @param file_name 文件名
 * @return 成功返回0,否则返回小于0的错误代码
 */
xl_int32 xlite_file_delete(const xl_wchar* file_name);

/*!
 * @brief 创建目录
 * @param dir_name 目录名
 * @return 成功返回0,否则返回小于0的错误代码
 */
xl_int32 xlite_file_create_dir(const xl_wchar* dir_name);


/*!
 * @brief 删除目录
 * @param dir_name 目录名
 * @return 成功返回0,否则返回小于0的错误代码
 * @note 该函数无法删除非空目录,根目录。
 */
xl_int32 xlite_file_remove_dir(const xl_wchar* dir_name);

/*!
 * @brief 重命名文件名
 * @param file_name 需要重命名的文件名
 * @param new_file_name 新的文件名
 * @return 成功返回0,否则返回小于0的错误代码
 */
xl_int32 xlite_file_rename(const xl_wchar* file_name,const xl_wchar* new_file_name);


/*!
 * @brief 返回目录尺寸
 * @param path_name 目录名
 * @return 成功返回目录的字节数,错误返回小于0的错误代码
 */
xl_int32 xlite_file_get_folder_size(const xl_wchar* path_name);


/*!
 * @brief 搜索文件
 * @param pattern 搜索的匹配字符串 (Eg: *.mp3)
 * @param callback 搜索到后调用该callback
 * @return 失败返回小于0的错误代码,否则返回大于或者等于0的数值
 * @note 使用方法\n
 * xl_bool app_on_file_found(const xlite_file_find_info* find_info)\n
 * {\n
 *		// Do something\n
 *		return XL_TRUE;	//如果返回XL_FASE则中断搜索\n
 * }\n
 * \n
 * // In Function\n
 * xl_int32 ret = xlite_file_find(L"D:\\*.*",app_on_file_found);\n
 */
xl_int32 xlite_file_find(const xl_wchar* pattern,xlite_file_find_callback callback);


/*!
 * @brief 查询文件或者目录是否存在
 * @param path 文件名或者目录名
 * @return 如果查询的文件或者目录存在,返回XL_TRUE,否则返回XL_FALSE
 */
xl_bool xlite_file_is_path_exist(const xl_wchar* path);

/*!
 * @brief 把缓存中的内容保存到文件
 * @param fh file handle
 * @return 成功返回0
 */
xl_int32 xlite_file_commit(xlite_file_handle file_handle);

/*!
 * @brief 检查剩余的磁盘容量
 * @param drive_name 驱动器名(可以带路径)
 * @return 成功返回剩余的字节数
 */
xl_int32 xlite_file_get_free_size(xl_wchar* drive_name);

/*!
 * @brief 获取文件的信息
 * @return 成功返回0
 */
xl_int32 xlite_file_get_info(xlite_file_handle file_handle, xlite_file_info* info);

#endif


#if xlite_sal_sys == 1
/////////////////////////////////////////////////////////////////////////////////
// xLite_sys.h
//  系统调用
//

/*!
 * @brief 为双卡双待机型，选择一个可用的通道
 * @return 成攻返回XL_TRUE，否则返回XL_FALSE
 */
xl_bool xlite_sys_auto_select_sim_card(xl_void);

/*!
 * @brief 设置定时器
 * @param interval 过期时间
 * @param timer_func 回调函数
 */
xl_void xlite_sys_start_timer(xl_int32 interval,xlite_timer_func func);


/*!
 * @brief 取消一个定时器
 * @param func 设置定时器传入的回调函数
*/
xl_void xlite_sys_cancel_timer(xlite_timer_func func);


/*!
 * @brief 开启非GUITimer
 * @param
 * @return
 */
xl_void xlite_sys_start_kernel_timer(xl_int32 interval,xlite_timer_func func);

/*!
 * @brief 关闭非GUI Timer
 * @param
 * @return
 */
xl_void xlite_sys_stop_kernel_timer(xl_void);

/*!
 * @brief Kernel timer是否已经开启
 * @param
 * @return
 */
xl_int32 xlite_sys_is_kernel_timer_exist(xl_void);

/*!
 * @brief 返回系统已运行时间
 * @return 系统已运行时间，单位为毫秒
 */
xl_uint32 xlite_sys_get_tick(xl_void);


/*!
 * @brief 返回当前的日期时间
 * @param date_time 日期的数据指针
 */
xl_void xlite_sys_get_date_time(xlite_date_time* date_time);


/*!
 * @brief 获取当前的服务提供商
 * @return 服务提供商
 */
xlite_operator xlite_sys_get_operator(xl_void);

/*!
 * @brief 检查是否有sim卡
 * @return XL_TRUE 有
 */
xl_bool xlite_sys_is_sim_valid(xl_void);

/*
 * @brief 初始化随机数种子
 * @param seed xl_uint32类型种子
 * @return
 */
xl_void xlite_sys_srand(xl_uint32 seed);

/*!
 * @brief 获取随机数
 * @return 随机数
 */
xl_int32 xlite_sys_rand(xl_void);

/*!
 * @brief 发送短消息
 * @param phone_number 手机号码
 * @param sms_content 短信内容
 */
xl_int32 xlite_sys_send_sms(const xl_char* phone_number,const xl_char* sms_content);

/*!
 * @brief 选择主卡
 */
xl_void xlite_sys_set_master_sim_card(xl_void);

/*!
 * @brief 选择副卡
 */
xl_void xlite_sys_set_slave_sim_card(xl_void);


/*!
 * @brief 获取当前可用sim卡
 * @return 可用sim卡的序号
 */
xl_uint8 xlite_sys_get_valid_sim_card(xl_void);

//获取4位区号
xl_char* xlite_sys_get_area_code(xl_void);
//获取imsi号码
xl_char* xlite_sys_get_imsi(xl_void);
//获取imeii号码
xl_char* xlite_sys_get_imei(xl_void);

#endif

#if xlite_sal_socket == 1
/////////////////////////////////////////////////////////////////////////////////
//  xLite_socket.h
//  socket operation
//

/*!
 * @brief 创建socket
 * @param domain socket domain\n
 * only support xlite_socket_pf_inet
 * @param type type of socket\n
 * support xlite_socket_stream and xlite_socket_dgram
 * @param protocol protocols\n
 * support xlite_socket_tcp and xlite_socket_udp
 * @param mod_id mod id on MTK platform,fill zero if on other platform
 * @param account network account id on MTK platform,fill zero if on other platform
 * @return return a negative integer if failed, else return the socket handle
 */
xlite_socket xlite_socket_create(xlite_socket_domain domain,xlite_socket_type type, xlite_socket_protocol protocol, xlite_socket_event_handler handler,xl_void* handler_param);
/*!
 * @brief close socket
 * @param sock socket id
 * @return zero if successed.
 */
xl_int32 xlite_socket_close(xlite_socket sock);


/*!
 * @brief bind to address
 * @param sock socket id
 * @param addr xlite_socket_sockaddr_struect pointer
 * @return return zero if successfully
 */
xl_int32 xlite_socket_bind(xlite_socket sock,xlite_socket_sockaddr_struct* addr);


/*!
 * @brief make a socket to server socket to wait a incoming connection
 * @param sock socket id
 * @param backlog maximum of client connections
 * @return return zero if successfully
 */
xl_int32 xlite_socket_listen(xlite_socket sock,xl_int32 backlog);


/*!
 * @brief accept a incoming connection
 * @param sock socket id
 * @param addr socket address of incoming connection
 * @return return negative if failed, otherwise return socket id of new connection
 */
xlite_socket xlite_socket_accept(xlite_socket sock,xlite_socket_sockaddr_struct* addr);

/*!
 * @brief connect to server
 * @param sock socket id
 * @param addr target server address
 * @return return zero if successfully
 */
xl_int32 xlite_socket_connect(xlite_socket sock,xlite_socket_sockaddr_struct* addr);


/*!
 * @brief shutdown a connection
 * @param sock socket id
 * @param how Flag that describes what types of operation will no longer be allowed.
 * @return return zero if successfully
 */
xl_int32 xlite_socket_shutdown(xlite_socket sock,xlite_socket_shutdown_flag how);

/*!
 * @brief send data to a specified address
 * @param sock socket id
 * @param buffer data buffer pointer to be send
 * @param length length of buffer
 * @param flag send flag
 * @param toaddr target address
 * @return return negative if failed,otherwise return number of bytes of sent
 */
xl_int32 xlite_socket_sendto(xlite_socket sock,xl_uint8* buffer,xl_uint32 length,xl_uint8 flag,xlite_socket_sockaddr_struct* toaddr);


/*! 
 * @brief send data to a pre-connected server
 * @param sock socket id
 * @param buffer data buffer pointer to be send
 * @param length length of data buffer
 * @param flag flag of send (not used,just set zero)
 * @return return negative if failed,otherwise return number of bytes of sent
 */
xl_int32 xlite_socket_send(xlite_socket sock,xl_uint8* buffer,xl_uint32 length,xl_uint8 flag);



/*!
 * @brief receive data from specified address
 * @param sock socket id
 * @param buffer buffer pointer to be received
 * @param length length of buffer
 * @param flag flag(not used,just set zero)
 * @param fromaddr source address
 * @return return zero if successfully.
 */
xl_int32 xlite_socket_recvfrom(xlite_socket sock,xl_uint8* buffer,xl_uint32 length,xl_uint8 flag,xlite_socket_sockaddr_struct* fromaddr);


/*!
 * @brief receive data from a connected socket
 * @param sock socket id
 * @param buffer buffer pointer to be received
 * @param length length of buffer
 * @param flag flag (not used,just set zero)
 * @return return zero if successfully
 */
xl_int32 xlite_socket_recv(xlite_socket sock,xl_uint8* buffer,xl_uint32 length,xl_uint8 flag);


/*!
 * @brief set socket option
 * @param sock socket id
 * @param option option
 * @param val value
 * @param val_size size of value
 * @return return zero if successfully
 */
xl_int32 xlite_socket_setsockopt(xlite_socket sock,xlite_socket_option option,xl_uint8* val,xl_uint8 val_size);

/*!
 * @brief get socket option
 * @param sock socket id
 * @param option option
 * @param val value
 * @param val_size size of value
 * @return return zero if successfully
 */
xl_int32 xlite_socket_getsockopt(xlite_socket sock,xlite_socket_option option,xl_uint8* val,xl_uint8 val_size);


/*!
 * @brief get ip address by host-name
 */
xl_int32 xlite_socket_gethostbyname(const xl_char* domain_name,xl_int32 request_id,xlite_socket_sockaddr_struct* sock_addr,xlite_socket_gethostbyname_event_handler handler,xl_void* handler_param);

/*!
 * @brief 关闭网络连接
 */
xl_void xlite_socket_close_network(xl_void);

#endif

#if xlite_sal_string == 1
/////////////////////////////////////////////////////////////////////////////////
//  xLite_string.h
//  字符串处理
//


//////////////////////////////////////////////////////////////////////////
// FUNCTION ROUTE
//////////////////////////////////////////////////////////////////////////
/*!
 * @brief 把unicode转为utf_8
 * @param str1 utf_8字符串,如果为空则不写入,只计算字符数
 * @param str2 unicode字符串
 * @return 转换后的字符数
 */
xl_uint32 xlite_unicode_to_utf8(xl_char* str1, xl_int32 str1_len,xl_wchar* str2,xl_int32 str2_len);

/*!
 * @brief 把utf_8转为unicode
 * @param str1 unicode字符串,,如果为空则不写入,只计算字符数
 * @param str2 utf_8字符串
 * @return 转换后的字符数
 */

xl_uint32 xlite_utf8_to_unicode(xl_wchar* str1, xl_int32 str1_len, xl_char* str2, xl_int32 str2_len);


/*!
 * @brief 获取字符串长度
 * @param pstr 字符串
 * @return 字符串长度
 */
xl_uint32 xlite_strlen(const xl_char* pstr);


/*!
* @brief 获取字符串长度
* @param pwstr 字符串
* @return 字符串长度
*/
xl_uint32 xlite_wstrlen(const xl_wchar* pwstr);


/*!
 * @brief 复制字符串
 * @param dest 目标字符串指针
 * @param src 源字符串指针
 */
xl_void xlite_strcpy(xl_char* dest,const xl_char* src);


/*!
 * @brief 复制字符串
 * @param dest 目标字符串指针
 * @param src 源字符串指针
 */
xl_void xlite_wstrcpy(xl_wchar* dest,const xl_wchar* src);


/*!
 * @brief 复制字符串
 * @param dest 目标字符串指针
 * @param src 源字符串指针
 * @param length 需要复制的字符串长度
 */
xl_void xlite_strncpy(xl_char* dest,const xl_char* src,xl_uint32 length);


/*!
 * @brief 复制字符串
 * @param dest 目标字符串指针
 * @param src 源字符串指针
 * @param length 需要复制的字符串长度
 */
xl_void xlite_wstrncpy(xl_wchar* dest,const xl_wchar* src,xl_uint32 length);

/*!
 * @brief 字符串比较
 * @param str_1 字符串
 * @param str_2 字符串
 * @param length 比较起始的字符长度
 * @return 相等返回0,str_1 < str_2 返回小于0的数字,否则返回大于0的数字
 */
xl_int32 xlite_strncmp(const xl_char* str_1,const xl_char* str_2,xl_uint32 length);

/*!
 * @brief 字符串比较
 * @param str_1 字符串
 * @param str_2 字符串
 * @param length 比较起始的字符长度
 * @return 相等返回0,str_1 < str_2 返回小于0的数字,否则返回大于0的数字
 */
xl_int32 xlite_wstrncmp(const xl_wchar* str_1,const xl_wchar* str_2,xl_uint32 length);



/*!
 * @brief 字符串比较
 * @param str_1 字符串
 * @param str_2 字符串
 * @return 相等返回0,str_1 < str_2 返回小于0的数字,否则返回大于0的数字
 */
xl_int32 xlite_strcmp(const xl_char* str_1,const xl_char* str_2);

/*!
 * @brief 字符串比较
 * @param str_1 字符串
 * @param str_2 字符串
 * @return 相等返回0,str_1 < str_2 返回小于0的数字,否则返回大于0的数字
 */
xl_int32 xlite_wstrcmp(const xl_wchar* str_1,const xl_wchar* str_2);


/*!
 * @brief 连接字符串
 * @param str_1 字符串
 * @param str_2 字符串
 * @return 连接的字符串
 */
xl_char* xlite_strcat(xl_char* str_1,const xl_char* str_2);

/*!
 * @brief 连接字符串
 * @param str_1 字符串
 * @param str_2 字符串
 * @return 连接的字符串
 */
xl_wchar* xlite_wstrcat(xl_wchar* str_1,const xl_wchar* str_2);

/*!
 * @brief 连接字符串
 * @param str_1 字符串
 * @param str_2 字符串
 * @param length 字符串长度
 * @return 连接的字符串
 */
xl_char* xlite_strncat(xl_char* str_1,const xl_char* str_2,xl_uint32 length);

/*!
 * @brief 连接字符串
 * @param str_1 字符串
 * @param str_2 字符串
 * @param length 字符串长度
 * @return 连接的字符串
 */
xl_wchar* xlite_wstrncat(xl_wchar* str_1,const xl_wchar* str_2,xl_uint32 length);

/*!
 * @brief 搜索字符
 * @param str 字符串
 * @param ch 搜索的字符
 * @return 搜索的字符开始的字符串
 */
xl_char* xlite_strchr(const xl_char* str,xl_char ch);

/*!
 * @brief 搜索字符
 * @param str 字符串
 * @param ch 搜索的字符
 * @return 搜索的字符开始的字符串
 */
xl_wchar* xlite_wstrchr(const xl_wchar* str,xl_wchar ch);


/*!
 * @brief 反向搜索字符
 * @param str 字符串
 * @param ch 搜索的字符
 * @return 搜索的字符开始的字符串
 */
xl_char* xlite_strrchr(const xl_char* str,xl_char ch);

/*!
 * @brief 反向搜索字符
 * @param str 字符串
 * @param ch 搜索的字符
 * @return 搜索的字符开始的字符串
 */
xl_wchar* xlite_wstrrchr(const xl_wchar* str,xl_wchar ch);

/*!
 * @brief 搜索字符串
 * @param str 字符串
 * @param ch 搜索的字符串
 * @return 搜索的字符串开始的字符串
 */
xl_char* xlite_strstr(const xl_char* str1,xl_char* str2);

/*!
 * @brief 搜索字符串
 * @param str 字符串
 * @param ch 搜索的字符串
 * @return 搜索的字符串开始的字符串
 */
xl_wchar* xlite_wstrstr(const xl_wchar* str1,xl_wchar* str2);

/*!
 * @brief 将字符串转换为数值
 * @param sz_num 包含数字的字符串
 * @return 转换的数值
 */
xl_int32 xlite_atoi(const xl_char* sz_num);

/*!
 * @brief 将十六进制字符串转换为数值
 * @param sz_num 包含数字的十六进制字符串
 * @return 转换的数值
 */

xl_int32 xlite_htoi(xl_char *str);

/*!
 * @brief 将数值转换为字符串
 * @param tz_num 包含数字的字符串
 * @param num 数值
 */
xl_void xlite_itoa(xl_char* tz_num, xl_int32 num);

/*!
 * @brief 把char转为wchar，只限字母数字和符号
 * @param dest wchar字符串
 * @param src char字符串
 */
xl_void xlite_ansii_to_unicode(xl_wchar* dest,xl_char* src);

/*!
 * @brief 把wchar转为char，只限字母数字和符号
 * @param dest char字符串
 * @param src wchar字符串
 */
xl_void xlite_unicode_to_ansii(xl_char* dest,xl_wchar* src);

/*!
 * @brief 格式化字符串
 */
xl_void xlite_sprintf(xl_char* str, const xl_char* fmt_str,...);
//extern xl_void (*xlite_sprintf) (xl_char* str, const xl_char* fmt_str,...);
#endif

#if xlite_sal_drawtext == 1
/////////////////////////////////////////////////////////////////////////////////
//  xlite_drawtext.h
//  DrawText depend on platform API
//

/*!
 * @brief 初始化字体引擎
 */
xl_void xlite_drawtext_init(xl_void);


/*!
 * @brief 设置字体的大小
 * @param font_size 字体大小
 * @return	return 0 if successed, else -1 indicate not support.
 */
xl_void xlite_drawtext_set_font_size(xlite_font_size font_size);


/*!
 * @brief 设置绘制文字的颜色
 * @param text_clr 文字颜色
 */
xl_void xlite_drawtext_set_color(xl_color text_clr);

/*!
 * @brief 返回字符的宽度
 * @param ch 字符
 * @return 字符的宽度
 */
xl_int32 xlite_drawtext_get_char_width(xl_wchar ch);


/*!
 * @brief 返回字符的高度
 * @param ch 字符
 * @return 字符的高度
 */
xl_int32 xlite_drawtext_get_char_height(xl_wchar ch);


/*!
 * @brief 返回字符串的高度
 * @param str 字符串
 * @param length 字符串长度
 * @return 字符串的高度
 */
xl_int32 xlite_drawtext_get_string_width(xl_wchar* str,xl_uint32 length);


/*!
 * @brief 返回字符串的宽度
 * @param str 字符串
 * @param length 字符串长度
 * @return 字符串的宽度
 */
xl_int32 xlite_drawtext_get_string_height(xl_wchar* str,xl_uint32 length);


/*!
 * @brief 绘制字符串到屏幕
 * @param x x坐标
 * @param y y坐标
 * @param str 字符串
 * @param length 字符串长度
 */
xl_void xlite_drawtext_draw_string(xl_int32 x,xl_int32 y,xl_wchar* str,xl_uint32 length);

/*!
 * @brief 绘制一个字符到屏幕
 * @param x x坐标
 * @param y y坐标
 * @param ch 字符
 */
xl_void xlite_drawtext_draw_char(xl_int32 x,xl_int32 y,xl_wchar ch);

/*!
 * @brief 设置绘制字符的剪裁矩形
 * @param left 左
 * @param top 上
 * @param right 右
 * @param bottom 下
 */
xl_void xlite_drawtext_set_clip(xl_int32 left,xl_int32 top,xl_int32 right,xl_int32 bottom);

/*!
 * @brief 重置绘制字符的剪裁矩形
 */
xl_void xlite_drawtext_reset_clip(xl_void);

#endif

#if xlite_sal_audio == 1
/////////////////////////////////////////////////////////////////////////////////
//  xlite_audio.h
//
xl_uint8 xlite_audio_get_volume(xl_void);

/*
 * @brief 设置音量，mtk是0-7
 * @param vol 音量
 */
xl_void xlite_audio_set_volume(xl_int32 vol);

/*
 * @brief 打开midi
 * @param audio_data 音频数据流
 * @param len 数据流长度
 * @param repeats 循环次数，为0就是无限循环
 * @return 音频的句柄
 */
xlite_audio_handle xlite_audio_open_midi(xl_void *audio_data, xl_uint32 len, xl_uint8 repeats);

/*
 * @brief 打开wav
 * @param audio_data 音频数据流
 * @param len 数据流长度
 * @param repeats 循环次数，为0就是无限循环
 * @return 音频的句柄
 */
xlite_audio_handle xlite_audio_open_wav(xl_void *audio_data, xl_uint32 len, xl_uint8 repeats);

/*
 * @brief 停止播放midi
 * @param audio_handle 音频的句柄
 */
xl_void xlite_audio_stop_midi(xlite_audio_handle audio_handle);

/*
 * @brief 停止播放wav
 * @param audio_handle 音频的句柄
 */
xl_void xlite_audio_stop_wav(xlite_audio_handle audio_handle);

/*
 * @brief 关闭midi
 * @param audio_handle 音频的句柄
 */
void xlite_audio_close_midi(xlite_audio_handle audio_handle);

/*
 * @brief 关闭wav
 * @param audio_handle: 音频的句柄
 */
void xlite_audio_close_wav(xlite_audio_handle audio_handle);

/*
 * @brief 播放midi
 * @param audio_handle 音频的句柄
 */
void xlite_audio_play_midi(xlite_audio_handle audio_handle);

/*
 * @brief 播放wav
 * @param audio_handle 音频的句柄
 */
void xlite_audio_play_wav(xlite_audio_handle audio_handle);

/*
 * @brief 暂停播放
 * @param audio_handle 音频的句柄
 */
void xlite_audio_pause(xlite_audio_handle audio_handle);

/*
 * @brief 回复播放
 * @param audio_handle 音频的句柄
 */
void xlite_audio_resume(xlite_audio_handle audio_handle);
#endif

#if xlite_sal_memory == 1
/////////////////////////////////////////////////////////////////////////////////
//  xLite_memory.h
//  内存接口
//

#	define XLITE_MEM_ALLOC(x)					xlite_mem_alloc((x))
#	define XLITE_MEM_FREE(x)					xlite_mem_free((x))

/*!
 * @brief 分配内存
 * @param length 需要的内存大小
 * @return 成功返回分配的内存指针,否则返回XL_NULL
 */
xl_void* xlite_mem_alloc(xl_uint32 length);

/*!
 * @brief 释放分配的内存
 * @param ptr 内存指针
 */
xl_void xlite_mem_free(xl_void* ptr);

/*!
 * @brief 复制内存数据
 * @param dest 目标地址
 * @param src 源地址
 * @param length 长度，单位为字节
 */
xl_void xlite_mem_copy(xl_void* dest,const xl_void* src,xl_uint32 length);

/*!
 * @brief 设置内存数据
 * @param buffer 数据区指针
 * @param value 想要设置的值
 * @param length 长度，单位为字节
 */
xl_void xlite_mem_set(xl_void* buffer,xl_uint8 val,xl_uint32 length);

/*!
 * @brief 比较内存数据
 * @param pBuffer1 地址1
 * @param pBuffer2 地址2
 * @param size 长度，单位为字节
 * @return 相同返回XL_TRUE，否则返回XL_FALSE
 */
xl_bool xlite_mem_cmp(const xl_void * pBuffer1,const xl_void * pBuffer2,xl_uint32 size);


/*!
 * @brief 获取当前内存信息
 * @param debug_info xlite_mem_debug_info的指针
 * @note 在debug_info中填入内存信息，只在debug模式下有用
 */
xl_void xlite_mem_debug_get_info(xlite_mem_debug_info* debug_info);


xl_int32 xlite_left_mem_size(xl_void);

#endif

#if xlite_sal_input_screen == 1
/////////////////////////////////////////////////////////////////////////////////
//  xLite_input_screen.h
//


/*
 * @brief MTK平台调用,设置SCREEN ID,初始化调用一次就可以了
 * @param screen_id screen id
 */
xl_void xlite_input_screen_mtk_set_screen_id(xl_uint16 screen_id);


/*
 * @brief 创建一个Input Screen
 * @param param xlite_input_screen_param的指针
 */
xl_void xlite_input_screen_enter(xlite_input_screen_param* param);


/*
 * @brief 关闭input screen
 */
void xlite_input_screen_cancel(xl_void);
#endif


#if xlite_sal_log == 1
/////////////////////////////////////////////////////////////////////////////////
//  xLite_log.h
//

 /*!
 * @brief 获取默认的日志文件名
 */
xl_void xlite_log_get_default_file_name(xl_wchar* file_name);

/*!
 * @brief 使用指定文件名初始化日志
 * @param log_file_name 日志文件名
 * @return 成功返回XL_TRUE,否则返回XL_FALSE
 */
xl_bool xlite_log_open(const xl_wchar* log_file_name);

/*!
 * @brief 写入日志
 * @param param fmt_str 格式化字符串
 * @sa printf
 * @note 一行日志最长的长度为0xFF,否则结果不可测\n
 * 如果日志已经关闭,该函数则什么都不做
 */
xl_void xlite_log_write_line(xlite_log_level level,const xl_char* fmt_str,...);

/*!
 * @brief 关闭日志文件
 */
xl_void xlite_log_close(xl_void);

/*!
 * @brief 输出内存状态
 */
xl_void xlite_log_output_memory_status(xl_void);

//////////////////////////////////////////////////////////////////////////
// Macro for log
#if xlite_use_debug == 1

#define xlite_open_log(p) xlite_log_open((p))
#define xlite_close_log() xlite_log_close()

/*! @brief 写日志(1个Msg) */
#define xlite_log_write_1(l,m)				xlite_log_write_line((l),(m))
/*! @brief 写日志(2个Msg) */
#define xlite_log_write_2(l,m,m1)			xlite_log_write_line((l),(m),(m1))
/*! @brief 写日志(3个Msg) */
#define xlite_log_write_3(l,m,m1,m2)			xlite_log_write_line((l),(m),(m1),(m2))
/*! @brief 写日志(4个Msg) */
#define xlite_log_write_4(l,m,m1,m2,m3)		xlite_log_write_line((l),(m),(m1),(m2),(m3))
/*! @brief 写日志(5个Msg) */
#define xlite_log_write_5(l,m,m1,m2,m3,m4)	xlite_log_write_line((l),(m),(m1),(m2),(m3),(m4))

#else
#define xlite_open_log(p)
#define xlite_close_log()
 
#define xlite_log_write_1(l,m)
#define xlite_log_write_2(l,m,m1)
#define xlite_log_write_3(l,m,m1,m2)
#define xlite_log_write_4(l,m,m1,m2,m3)
#define xlite_log_write_5(l,m,m1,m2,m3,m4)

#endif

#endif

#if xlite_sal_assert == 1
/////////////////////////////////////////////////////////////////////////////////
//  xLite_assert.h
//

 /*!
 * @brief 注册用户assert回调函数
 */
xl_void xlite_assert_reg_user_callback(xl_void(*func)(xl_void));

 /*!
 * @brief 断言函数
 */
xl_void xlite_assert(xlite_assert_level level, xl_char* filename,xl_int32 line);

//////////////////////////////////////////////////////////////////////////
// Macro for assert
#ifndef XLITE_ASSERT_LEVEL
#	if xlite_use_debug == 1
#		define XLITE_ASSERT_LEVEL XLITE_ASSERT_LEVEL4
#	else
#		define XLITE_ASSERT_LEVEL XLITE_ASSERT_LEVEL1
#	endif
#endif

#define XLITE_ASSERT(l, c) \
	if(l <= XLITE_ASSERT_LEVEL) \
	{\
		if(!(c))\
		{\
			xlite_assert(l, __FILE__, __LINE__);\
		}\
	}
#endif


#if xlite_sal_sensor == 1
/////////////////////////////////////////////////////////////////////////////////
//  xLite_sensor.h
//  感应器相关api
//

 /*!
 * @brief 打开sensor功能
 */
xl_void xlite_sensor_start(xl_void);

 /*!
 * @brief 关闭sensor功能
 */
xl_void xlite_sensor_stop(xl_void);

 /*!
 * @brief 获取3个轴当前的加速度值
 */
xl_void xlite_sensor_get_xyz(xl_int16* x, xl_int16* y, xl_int16* z);

 /*!
 * @brief 获取3个轴的原始未处理值
 */
xl_void xlite_sensor_get_original_value(xl_int16* a, xl_int16* b, xl_int16* c);

 /*!
 * @brief 获取sensor的类型
 */
xl_int32 xlite_sensor_get_sensor_type(xl_void);

#endif

 /*!
 * @brief 用MTK 函数画图片
 */
xl_void xlite_mtk_draw_image(xl_uint32 x,xl_uint32 y,xl_char *image);

 /*!
 * @brief 用MTK 函数获取图片长高
 */

xl_void xlite_mtk_get_image_width_height(xl_int32 *width,xl_int32 *height,xl_char *image);

  /*!
 * @brief 设置文件路径
 */

xl_void xlite_app_get_file_path(xl_wchar *wpath,xl_char *image);


xl_bool xlite_record_start(record_fun fun);


xl_bool xlite_record_stop(xl_void);
#endif
