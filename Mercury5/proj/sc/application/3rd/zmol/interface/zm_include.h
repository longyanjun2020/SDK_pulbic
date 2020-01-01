#ifndef __ZM_INCLUDE_H_____
#define __ZM_INCLUDE_H_____
   
#define ZMOL_MSTAR_VERSION	0x0204

#include "ven_file.h"
#include "ven_os.h"
#include "ven_sdk.h"
#include "ven_kpd.h"
#include "ven_ts.h"
#include "ven_time.h"
#include "ven_graphics.h"
#include "ven_stc.h"
#include "ven_setting.h"
#include "ven_handle.h"
#include "ven_common_def.h"
#include "ven_comdef_priv.h"
#include "ven_socket.h"
#include "ven_util.h"
#include "ven_drv.h"
#include "ven_dbg.h"
#include "Ms_data.h"
#include "ven_codec.h"
#include "ven_msg.h"
#include "ven_cc.h"
#include "ven_msg_msgt.h"
#include "ven_editor.h"
#include "ven_ui.h"
#include "SockMgrConnectionItf.h"
#include "ms_socket_adaptor.h"
#include "mmi_mae_shell.h"

#include "zm_typedef.h"


//#define ZM_OPEN_FILE_TRACE
void zm_file_trace(const char* fmt, ...);

/**
 * 工作目录定义
 */
#define zm_work_folder				"c:\\zmol\\"

/**
 * 工作目录是否支持屏幕适配,
 * 打开下面这个开关，那么程序的保存目录为 zm_work_folder\240x320\*.app
 * 关闭下面的这个开关，那么程序的保存目录为 zm_work_folder\*。app
 */
//#define zm_work_folder_auto_support	

/**
 * 是否支持横竖切换
 */
//#define ZM_SUPPORT_ROTATE_SCREEN

/**
 * 手机型号定义
 */
#define ZM_PHONE_MODEL				"M1"
//如果手机无键盘（只有触摸）,请换用一下方式定义手机型号
//#define ZM_PHONE_MODEL				"NOKEY"

/**
 * 如果厂家需要区分渠道子编号,打开下面的宏定义
 */
//#define _ZMOL_SUPPORT_SUB_COMPANY_CODE_
#ifdef _ZMOL_SUPPORT_SUB_COMPANY_CODE_
	/**
	 * 如果支持子编号，那么自编号的宏定义，取值范围 0 - 99
	 */
	#define ZMOL_SUB_COMPANY_CODE	0
#endif//_ZMOL_SUPPORT_SUB_COMPANY_CODE_

/**
 * 打开此开关，平台应用自身内存也共享使用MED内存
 */
#define ZM_ZMRE_SHARE_MED_MEMORY

/**
 * 创建内容空间大小
 */
#define ZM_MEMORY_POOL_SIZE			1024*100

//如果需要App独享内存600K，那么打开这个宏定义
//#define ZMOL_APP_MEMOERY_NOT_SHARE

/**
 * 同步方式发送短信
 */
//#define ZM_SEND_SMS_SYNC_METHOD

/**
 * 文件路径最大长度
 */
#define ZM_MAX_FILENAME				100

/**
 * GPRS设置项的ID
 */
#define GPRS_ACCOUNT_CONTEXT_ID		9
#define GPRS_ACCOUNT_NAME			"ZMOL"
#define GPRS_NETWORK_ACCOUNT_ID		18

//短信发送模块状态
typedef enum
{
	ZM_SMS_IDLE,
	ZM_SMS_SENDING
}ZM_Sms_Status;

//短信队列
typedef struct tagSmsQueue
{
	zm_int8	m_szNumber[21];		 //手机号
	zm_int8	m_szText[256];		 //短信内容，最多200汉字
	zm_int	m_nTextLen;			 //短信内容长度
	zm_bool	m_bNotify;			 //是否显示提示框
	zm_int	m_nEncode;			 //字符编码
	zm_int	m_nTimes;			 //发送次数
	zm_int	m_nResends;			 //重发次数
}ZM_SmsQueue;

//网络状态定义
typedef enum
{
    ZM_NET_STATUS_IDLE,
    ZM_NET_STATUS_CONNECTING,
    ZM_NET_STATUS_READING,
    ZM_NET_STATUS_WRITING
} ZMNetStatus;

typedef struct 
{
    zm_int 		port;
    ZMNetStatus 	status;
    zm_int8 		sockfd;
    zm_int 		socketConnected;
}ZMNetData;

#include "zm_main.h"
#include "zm_file.h"
#include "zm_gui.h"
#include "zm_gdi.h"
#include "zm_phone.h"
#include "zm_string.h"
#include "zm_systeminit.h"
 
#endif//__ZM_INCLUDE_H_____
