#ifndef _ZHANGMENG_STOCK_PHONE_H_
#define _ZHANGMENG_STOCK_PHONE_H_

#include "zm_typedef.h"
#include "zm_socket.h"
/*
 * 计时器
 */
typedef zm_void (*ZM_TIMER_CALLBACK_FUNCPTR)(zm_void);
/*
 * 设置计时器
 */
zm_extern zm_void zm_set_timer(zm_uint32 dwMiliSec,ZM_TIMER_CALLBACK_FUNCPTR pCallback);
/*
 * 关闭计时器
 */
zm_extern zm_void zm_kill_timer(ZM_TIMER_CALLBACK_FUNCPTR pCallback);

/*
 * 开始游戏timer
 */
zm_extern zm_void zm_start_timer(zm_uint32 dwMiliSec,ZM_TIMER_CALLBACK_FUNCPTR pCallback);

/*
 * 结束游戏timer
 */
zm_extern zm_void zm_stop_timer(ZM_TIMER_CALLBACK_FUNCPTR pCallback);

/* 
 * zm_get_imei
 * desc : Get the mobile's IMEI
 * return: he length of the imei, 0 indicating get error
 */
zm_extern zm_uint8 zm_get_imei(zm_int8* pIMEI, zm_uint8 nBuffLen);
/*
 * name: zm_get_imsi
 * desc: Get the mobile's imsi of sim card 
 * input:           
 *   --a pointer point to a buff which containing the got imis,pls use 0 as the last chararacter
 *   --nBuffLen: the length of the buffer of the first parameter
 * return: he length of the imis, 0 indicating get error        
 */
zm_extern zm_uint8 zm_get_imsi(zm_int8* pImsi, zm_uint8 nBuffLen);
/*
 *	获取厂家编号
 */
zm_extern zm_void zm_get_phone_company(zm_int8* pCompany, zm_int nMax);
/*
 *	获取电话型号
 */
zm_extern zm_uint8 zm_get_phone_model(zm_int8* pModel, zm_uint8 nBuffLen);
/*
 * name: zm_get_network
 * description:   get the network information which is provide the service * input:   NONE
 * return:	zm_network_type
 * Note:
 */
zm_extern zm_network_type zm_get_network(zm_void);

/*
 * turn on screen always light
 */
zm_extern zm_void zm_screen_turn_on_light(zm_void);

/*
 * turn off screen light
 */
zm_extern zm_void zm_screen_turn_off_light(zm_void);

/*
 *	whether can send short message now
 */
zm_extern zm_bool zm_can_send_sms(zm_void);
/*
 *	send short message
 *  input:
 *		pCalled   : the called phone number of short message 
 *		@PContent : short mesage content
 *		@bNotify  : whether tip user, will send a short message
 *  return: if success return zm_true else return zm_false
 *		
 */
zm_extern zm_bool zm_send_sms(const zm_int8* pCalled,const zm_int8* pContent,zm_int contentLen,zm_bool bNotify,zm_int nTimers);
/*
 *	call phone interface
 *  input:
 *		@pCalled   : the called phone number 
 *		@nCalledLen: the pCalled buffer length
 *		@pszTip    : the pszTip text 
 *		@nTipLen   : the pszTip text length
 */
zm_extern zm_bool zm_call_phone(const zm_int8* pCalled, zm_uint16 nCalledLen, const zm_int8* pszTip, zm_uint16 nTipLen);
/*
 *	func : zm_call_url
 *	desc : wap interface
 *  input:
 *	@pszUrl, wap address, NOTE: not \0 end
 *	@nUrlLen, wap address length
 */
zm_extern zm_bool zm_call_url(const zm_int8* pszUrl, zm_uint16 nUrlLen);
/*
 *	func : zm_get_time
 *  desc : get current localtime
 */
zm_extern zm_bool zm_get_current_time(zm_tm* pTm);
zm_extern zm_void zm_set_current_time(zm_tm* pTm);

/*
 * 获取时间戳
 */
zm_extern zm_uint32 zm_get_tick_count(zm_void);

/*
 * 设置随即数种子数
 */
zm_extern zm_void zm_srand(zm_uint s);

/*
 * 产生随机数
 */
zm_extern zm_int zm_rand(zm_void);

/*
 * 入口通知,如果返回zm_true 进入， zm_false 不进入
 */
zm_extern zm_bool zm_on_enter_system(zm_void);
/*
 * 出口通知
 */
zm_extern zm_void zm_on_exit_system(zm_void);

/*
 * 文本输入框
 */
typedef zm_void (*zm_input_text_callback)(zm_int8* buf, zm_int len);
zm_extern zm_void zm_input_text(const zm_int8* txt, zm_int len, zm_int maxlen, zm_input_type type, zm_input_text_callback callback);

/*
 *短信检测
 */
zm_extern zm_uint8 zm_sms_msg_probe(zm_uint8* number, zm_int num_len,zm_uint8* content ,zm_int content_len);

/*
 * 检查短信
 */
zm_extern zm_uint8 zm_sms_msg_check(zm_void* data, zm_int withobject, zm_void* content);

/*
 * 处理短信
 */
zm_extern zm_uint8 zm_sms_msg_handler(zm_void* inMsg, zm_void* content);

/* ----------------------------------------------
 *	debug trace interface
 * ----------------------------------------------*/
/*
 *	trace int 
 */
zm_extern zm_void zm_trace_int(const zm_int8* format, zm_int lvalue);
/*
 *	trace string
 */
zm_extern zm_void zm_trace(const zm_int8* str);
/*
 *	格式化trace
 */
zm_extern zm_void zm_trace_string(const zm_int8* format, const zm_int8* str);


/* ----------------------------------------------
 *	为了支持朗元UDB2.0的API接口支持
 * ----------------------------------------------*/
// 获取当前短信中心号码
zm_extern zm_uint8 zm_getscn(zm_int8 *pScn,zm_uint8 nBuffLen);

// 获取手机可支持的视频文件格式（后缀）
zm_extern zm_bool zm_getvideoformat(zm_int8* pszFormat, zm_int16 nMaxLen);

// 获取手机可支持的音频文件格式（后缀）
zm_extern zm_bool zm_getaudioformat(zm_int8* pszFormat, zm_int16 nMaxLen);

// 获取手机可支持的铃声文件格式（后缀）
zm_extern zm_bool zm_getringtoneformat(zm_int8* pszFormat, zm_int16 nMaxLen);

// 获取手机可支持的电子书文件格式（后缀）
zm_extern zm_bool zm_getebookformat(zm_int8* pszFormat, zm_int16 nMaxLen);

/*
 * 留言信箱配置更改通知
 */
zm_extern zm_void zm_pm_reload_profile(zm_void);

/**
 * 是否显示关于信息,返回zm_true 显示， 返回 zm_false 不显示
 */
zm_extern zm_bool zm_can_show_about(zm_void);

/**
 *	获取系统字符串文本
 */
zm_extern zm_int8* zm_getstring(zm_int32 strid);
/**
 *	获取手机卫士入口mark
 *	0: 进入来电留声
 *	1: 进入来电防火墙
 *	2: 进入短信设防
 *	3: 进入手机防盗
 */
zm_extern zm_int zm_get_pm_entry_mark(zm_void);

//////////////////////////////////////////////////////////////////////////
//20100621添加接口
//////////////////////////////////////////////////////////////////////////

/**
 * 发送端口短信
 * 参数: pNumber		短信接收方号码
 * 		    pContent		短信内容
 * 		    nContLen		短信内容长度
 * 		    bNotify		是否弹出发送提示框
 * 		    nContEncode	短信内容的编码方式
 * 		    src_port		短信发送源端口
 * 		    dst_port		短信发送目标端口
 * 		    nTimers		短信发送次数
 * 返回: zm_true		发送成功
 * 		    zm_false		发送失败
 */
zm_extern zm_bool zm_send_sms_byport(zm_int8* pNumber, zm_int8*pContent, 
									 zm_int nContLen,zm_bool bNotify, zm_int nContEncode,
									 zm_uint16 src_port, zm_uint16 dst_port, zm_int nTimers);

/**
 * 发送中文短信
 * 参数: pNumber		短信接收方号码
 * 		    pContent		短信内容
 * 		    nContLen		短信内容长度
 * 		    bNotify		是否弹出发送提示框
 * 		    nContEncode	短信内容的编码方式
 * 		    nTimers		短信发送次数
 * 返回: zm_true		发送成功
 * 		    zm_false		发送失败
 */
zm_extern zm_bool zm_send_sms_encode(zm_int8* pNumber, zm_int8*pContent, 
									 zm_int nContLen,zm_bool bNotify, 
									 zm_int nContEncode,
									 zm_int nTimers);

//////////////////////////////////////////////////////////////////////////
// 电话本接口
//////////////////////////////////////////////////////////////////////////
// 电话记录保存的位置
typedef enum {
	zm_phb_nvram,			// 手机
	zm_phb_sim1,			// SIM卡1 
	zm_phb_sim2,			// SIM卡2
	zm_phb_max
} zm_phb_storage;

// 电话簿操作的错误代码
typedef enum {
	zm_phb_err_none,			// 无错误
	zm_phb_err_num_too_long,	// 号码超出长度
	zm_phb_err_fdl_on,			// 固定拨号激活
	zm_phb_err_unknow			// 未知错误
} zm_phb_error;

// 回调函数格式定义
typedef zm_void (*zm_phb_callback)(zm_phb_error err);

/**
 * 搜索电话簿
 * 参数: pNumber		Unicode编码的电话号码(使用的buf长度最大为88字节)
 * 		    num_len		电话号码buf的字节长度
 * 		    name			Unicode编码的联系人姓名(使用的buf长度最大为62字节)
 * 		    name_len		联系人姓名buf的字节长度
 * 返回: >=0			搜索句柄 
 *             -1				参数无效
 * 		   -2				电话簿未初始化完成
 * 		   -3				已经达到可打开的电话簿句柄的最大值
 * 		   -4				电话簿中储存的电话个数为0
 */
zm_extern zm_int zm_phb_find_first(zm_int8 *pNumber, zm_int num_len, zm_int8 *name, zm_int name_len);

/**
 * 搜索电话簿
 * 参数: search_handler	搜索句柄，为zm_phb_find_first的返回值
 * 		    pNumber		Unicode编码的电话号码(使用的buf长度最大为88字节)
 * 		    num_len		电话号码buf的字节长度
 * 		    name			Unicode编码的联系人姓名(使用的buf长度最大为62字节)
 * 		    name_len		联系人姓名buf的字节长度
 * 返回: -1			无效参数
 * 		    0				已经到了电话簿中的最后一个记录(当前返回的pNumber和name无效)
 * 		    1				成功返回电话簿中的联系人信息
 */
zm_extern zm_int zm_phb_find_next(zm_int search_handler, zm_int8 *pNumber, zm_int num_len, zm_int8 *name, zm_int name_len);

/**
 * 关闭电话簿搜索句柄
 * 参数: search_handler	搜索句柄，为zm_phb_find_first的返回值
 * 返回: zm_void
 */
zm_extern zm_void zm_phb_find_close(zm_int search_handler);

/**
 * 获取指定次序的联系人信息，次序按照zm_phb_find_next搜索的顺序
 * 参数: index			次序
 * 		    pNumber		输出参数，Unicode编码的电话号码
 * 		    num_len		pNumber buf的字节长度
 * 		    name			输出参数，Unicode编码的联系人姓名
 * 		    name_len		name buf的字节长度
 * 返回: -1			无效参数
 * 		    -2			电话簿未完成初始化
 * 		    -3			index参数超出范围
 * 		    0				成功获取联系人信息
 */
zm_extern zm_int zm_phb_find_by_index(zm_int index, zm_int8 *pNumber, zm_int num_len, zm_int8 *name, zm_int name_len);

/**
 * 获取电话簿信息的记录个数
 * 参数: zm_void
 * 返回: -1			电话簿未初始化完成
 * 		    >=0			电话簿的条数
 */
zm_extern zm_int zm_phb_find_get_count(zm_void);

/**
 * 获取指定号码的联系人姓名
 * 参数: pNumber		输入参数，ASCII编码的电话号码
 * 		    name			输出参数，联系人姓名(Unicode编码)
 * 返回: -1			无效参数 
 * 		    -2			电话簿未完成初始化
 * 		    0				未搜索到指定的联系人姓名
 * 		    >0			搜到到的联系人姓名的字节数
 */
zm_extern zm_int zm_phb_find_search_name(zm_int8 *pNumber, zm_int8 *name);

/**
 * 添加电话记录
 * 参数:
 * 	name				联系人姓名(Unicode编码)
 * 	number				联系人号码(Unicode编码)
 * 	storage				联系人保存位置
 * 	callback				回调通知函数
 * 返回:
 * 	-1					电话簿未完成初始化
 * 	0					发送添加请求成功
 */
zm_extern zm_int zm_phb_add_entry(zm_int8 *name, zm_int8 *number, zm_phb_storage storage, zm_phb_callback callback);

/**
 * 删除电话记录
 * 参数:
 * 	phb_index			电话簿的索引值
 * 	callback				回调函数
 * 返回:
 * 	-1					电话簿未完成初始化
 * 	0					发送删除消息成功
 */
zm_extern zm_int zm_phb_delete_entry(zm_int phb_index, zm_phb_callback callback);

/**
 * 获取电话簿记录保存的位置
 * 参数:
 * 	phb_index			电话簿的序号
 * 返回:
 * 	zm_phb_storage		电话簿的存储位置
 * 	zm_phb_max			参数无效，或者电话簿未完成初始化
 */
zm_extern zm_phb_storage zm_phb_get_storage(zm_int phb_index);


//////////////////////////////////////////////////////////////////////////
//摄像头接口
//////////////////////////////////////////////////////////////////////////
// 拍照图片的尺寸
typedef enum {
	zm_cam_img_size_small,
	zm_cam_img_size_middle,
	zm_cam_img_size_large,
	zm_cam_img_size_fine,

	zm_cam_img_size_max
} zm_cam_img_size;

// 拍照图片质量枚举
typedef enum {
	zm_cam_img_qty_low,
	zm_cam_img_qty_normal,
	zm_cam_img_qty_high,
	zm_cam_img_qty_max
} zm_cam_img_qty;

// 摄像头抓拍的操作结果
typedef enum {
	zm_cam_result_success = 0,
	zm_cam_result_err_not_preview,
	zm_cam_result_err_disk_full,
	zm_cam_result_err_write_protection,
	zm_cam_result_err_no_disk,
	zm_cam_result_err_failed,

	zm_cam_result_max_err
} zm_cam_result;

/**
 * 初始化摄像头模块
 * 参数: zm_void
 * 返回: 0			初始化成功
 * 		    -1		内存不足
 */
zm_extern zm_int zm_cam_init(zm_void);

/**
 * 释放摄像头模块
 * 参数: zm_void
 * 返回: zm_void
 */
zm_extern zm_void zm_cam_uninit(zm_void);

/**
 * 进去摄像头预览界面
 * 参数: zm_void	
 * 返回: zm_void
 */
zm_extern zm_void zm_cam_entry_preview(zm_void);

/**
 * 退出摄像头预览界面
 * 参数: zm_void
 * 返回: zm_void
 */
zm_extern zm_void zm_cam_exit_preview(zm_void);

/**
 * 恢复摄像头预览画面
 * 参数: zm_void
 * 返回: zm_void
 */
zm_extern zm_void zm_cam_resume(zm_void);

/**
 * 暂停摄像头预览画面
 * 参数: zm_void
 * 返回: zm_void
 */
zm_extern zm_void zm_cam_pause(zm_void);

/**
 * 获取相应摄像头截图尺寸的图片宽度和高度
 * 参数: img_size		图片尺寸枚举
 * 		    img_width		输出参数，图片宽度，为0表示图片尺寸枚举无效
 * 		    img_height		输出参数，图片高度，为0表示图片尺寸枚举无效
 * 返回: zm_void
 */
zm_extern zm_void zm_cam_get_size(zm_cam_img_size img_size, zm_int16 *img_width, zm_int16 *img_height);

/**
 * 设置摄像头截图的图片尺寸
 * 参数: img_size		图片尺寸枚举，如果是无效参数，则将截图尺寸设置为屏幕宽高
 * 返回: zm_void
 */
zm_extern zm_void zm_cam_set_capture_size(zm_cam_img_size img_size);

/**
 * 设置摄像头图片预览的尺寸
 * 参数: preview_width	预览宽度
 * 		    preview_height	预览高度
 * 返回: zm_void
 */
zm_extern zm_void zm_cam_set_preview_size(zm_int16 preview_width, zm_int16 preview_height);

/**
 * 设置摄像头图片预览的位置
 * 参数: preview_x		预览图片的x坐标
 * 		    preview_y		预览图片的y坐标
 * 返回: zm_void
 */
zm_extern zm_void zm_cam_set_preview_position(zm_int16 preview_x, zm_int16 preview_y);

/**
 * 设置摄像头的图片质量
 * 参数: img_qty		图片质量
 * 返回: zm_void
 */
zm_extern zm_void zm_cam_set_img_qty(zm_cam_img_qty img_qty);

/**
 * 摄像头放大，根据当前摄像头的倍率，依次放大
 * 参数: zm_void
 * 返回: zm_void
 */
zm_extern zm_void zm_cam_zoom_in(zm_void);

/**
 * 摄像头缩小，根据当前摄像头的倍率，依次缩小
 * 参数: zm_void
 * 返回: zm_void
 */
zm_extern zm_void zm_cam_zoom_out(zm_void);

/**
 * 设置摄像头的倍率
 * 参数: index			摄像头倍率，从0到max_index,max_index由zm_cam_get_max_zoom_index返回
 * 返回: zm_void
 */
zm_extern zm_void zm_cam_set_zoom_index(zm_int index);

/**
 * 获取摄像头的最大倍率
 * 参数: zm_void
 * 返回: zm_void
 */
zm_extern zm_int zm_cam_get_max_zoom_index(zm_void);

/**
 * 摄像头截图
 * 参数: buf_p			保存图片的buf的指针
 * 		    captured_len	输出参数，截图完成后返回的jpeg图片长度
 * 返回: == zm_cam_result_success	截图成功
 * 		   != zm_cam_result_successs	截图失败
 */
zm_extern zm_cam_result zm_cam_capture_to_memory(zm_int8 **buf_p, zm_int *captured_len);

#endif/*_ZHANGMENG_STOCK_PHONE_H_*/
