// 
// 
// Copyright (c) 2007 Greatelsoft Co.,Ltd. All rights reserved.
// Author: Ken Zhang
//
// $Id: xLite_E_http.h 209 2009-07-21 02:24:47Z nazy $
#ifndef __XLITE_E_HTTP_H__
#define __XLITE_E_HTTP_H__

#include "xLite_E_internal.h"
#ifndef XLITE_NO_NETWORK

/*!
 * @file xLite_E_http.h
 * @brief HTTP协议封装
 */

/*
 * @brief 初始化一个Request头
 * @param
 * @return
 */
xl_int32 xlite_E_http_request_init(xlite_http_request* request,
								   const xl_char* url,
								   xl_uint8 method,
								   xl_uint8 conn,
								   xl_uint8 use_proxy,
								   xlite_socket_sockaddr_struct* proxy_svr,
								   xl_uint32 body_len
								   );
/*
 * @brief 从Request打开http连接
 * @param 
 * @return
 */
xl_int32 xlite_E_http_open(xlite_http_session* session, xlite_http_request* request, xlite_E_http_event_handler handler);

/*
 * @brief 关闭Http Session,并且会释放session占用的内存
 * @param
 * @return
 */
xl_void xlite_E_http_close(xlite_http_session* session);

/*
 * @brief 将HTTP头写到buffer中
 * @param
 * @return
 */
xl_int32 xlite_E_http_output_header(xlite_http_request* request,const xl_char* head,const xl_char* value);

/*
 * @brief 将HTTP头写入buffer
 * @param
 * @return
 */
xl_int32 xlite_E_http_output_header_i(xlite_http_request* request,const xl_char* head,xl_int32 value);

/*
 * @brief 从session中读取缓冲中的内容到本地
 * @param
 * @return 实际读取长度
 */
xl_int32 xlite_E_http_session_buffer_read(xlite_http_session* session, xl_uint8* buffer,xl_uint32 length);

/*
 * @brief 写入本地内容到session缓冲区
 * @param
 * @return 实际写入长度
 */
 xl_int32 xlite_E_http_session_buffer_write(xlite_http_session* session, xl_uint8* buffer,xl_uint32 length);


/*
 * @brief 获取输出的缓冲
 */
#define XLITE_E_HTTP_GET_OUT_BUFFER(s)			( (s)->buffer + (s)->buf_length )

/*
 * @brief 获取缓冲可供写入的字节数
 */
#define XLITE_E_HTTP_GET_OUT_BUFFER_LENGTH(s)	( XLITE_E_HTTP_BUFFER_LENGTH - (s)->buf_length )


xl_void xlite_E_http_release_host_list(xl_void);

#endif

#endif
