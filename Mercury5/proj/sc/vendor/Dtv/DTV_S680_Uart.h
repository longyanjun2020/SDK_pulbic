
#ifndef _S680_UART_DRIVER_H_
#define _S680_UART_DRIVER_H_

/*===========================================================================
 * Include file
 *===========================================================================*/

#include "Customer_config.h"
#include "mmpf_typedef.h"
#include "Touch_Uart_ctrl.h"
/*===========================================================================
 * Macro define
 *===========================================================================*/
#ifndef DTV_UART_NUM
#define DTV_UART_NUM                    (MMP_UART_ID_2)
#endif
#ifndef DTV_UART_PADSET
#define DTV_UART_PADSET                 (MMP_UART_PADSET_2)
#endif
#define Uart_RX_QUEUE_SIZE               (256)
#define Uart_RX_SIGNAL                   (0xFE)
#ifndef DTV_UART_BAUD_RATE
#define DTV_UART_BAUD_RATE                   (57600)//(115200)
#endif
#define DTV_UART_CLK                    (264000 >> 1)

#define HEAD1_S680                  0xFF
#define HEAD2_S680                  0xAA

#define LEN_OFFSET_S680             0x02
#define DATA_TYPE_OFFSET_S680       0x03
#define DATA_OFFSET_S680            0x04

#define TAIL1_S680                  0XFF
#define TAIL2_S680                  0XFE

//data1:0x03  data2:分辨率 data3:停车侦测 data4:录音 data5:重力感应
#define PARAM_RESOLUTION            0x02
#define PARAM_PARKING_MODE          0x03
#define PARAM_AUDIO_RECORD          0x04
#define PARAM_GSENSOR_SENSITIVITY   0x05

/*===========================================================================
 * Enum define
 *===========================================================================*/
typedef enum _DTVACK_S680ID // send to NAVI
{
	NAVIACK_HEART_BEAT      = 0x01,		
							//格式：0xFF 0xAA len(2) 0x01 data checksum
							//Data :0x01 通讯正常
							//备注：DVR 3s一次，主机15s 没有收到此命令，则判断DVR异常,重启复位DVR 

	NAVIACK_CARD_STATUS     = 0x02,	
							//格式：0xFF 0xAA len(2) 0x02 data checksum
							//Data :0x01 插拔卡异常	//复位 1BYTE
							//Data :0x02 无卡
							//Data :0x03 错卡
							//Data :0x04 卡满

	NAVIACK_PWRON_MSG       = 0x03,
							//开机信息：主要有DVR版本信息、DVR开机状态
							//格式：0xFF 0xAA len(7) 0x03 data checksum
							//Data :录影状态1BYTE 	不在录影 0， 录影1
							//加锁状态1BYTE		未加锁 0， 已加锁1
							//版本号4BYTE 	年月日V

	NAVIACK_SW_MODE         = 0x04,
							//格式：0xFF 0xAA len 0x04 data checksum
							//Data :
							//data1:01录像（1BYTE）
							//data1:02拍照（1BYTE）
							//data1:03回放 data2-3:video	data4-5:envent	data6-7:jpg  data8-9:卡内存已用 data10-11:卡内存未用（11BYTE）
							//例：数据 15.32G  发送1532 =5FC = 0x05 0xFC

	NAVIACK_REC_MODE_OPREQ	= 0x05,	
							//格式：0xFF 0xAA len(3\3\6) 0x05 data checksum
							//data1:0x01	data2:录影状态0不在录影, 1录影 data3:加锁状态0不加锁, 1加锁
							//data1:0x02	data2:菜单状态0退菜单,	1进菜单
							//data1:0x03	data2:分辨率 data3:停车侦测 data4:录音 data5:重力感应
							//分辨率（1080P、720P60、720P30）=>发送依次0、1、2代替
							//停车侦测（关、开）=>发送依次0、1代替
							//录音（关、开）=>发送依次0、1代替
							//重力感应（低、中、高、关闭）=>发送依次0、1、2、3代替  
							// data1:0x04  恢复出厂设置
							// data1:0x05  date2: 1格式化SD卡开始，2格式化卡结束

	NAVIACK_CAP_MODE_OPREQ	= 0x06,	
							//格式：0xFF 0xAA len(3\3) 0x06 data checksum
							//data1:0x01	data2:01拍照OK
							//data1:0x02	data2:菜单状态0退菜单 1进菜单
							//data1:0x03	data2:分辨率
							//			图片分辨率（12M、10M、8M、5M、3M、2M）=>发送依次0、1、2、3、4、5代替

	NAVIACK_PB_MODE_OPREQ   = 0x07,
							//格式：0xFF 0xAA len(3) 0x07 data checksum
							//data1:0x01	data2:01video 02envent 03jeg

	NAVIACK_MOV_LIST_MSG    = 0x08,							
							//Video列表信息：（进video 时DVR主动发送）
							//格式：0xFF 0xAA len(4\10) 0x08 data checksum
							//data1:0x01 data2-data3:总数(<1000)
							//data1:0x02 data2-data3:第N条(<1000)  data4-data9:ymdhms 6个BYTE

	NAVIACK_MOV_LIST_OPREQ  = 0x09,
							//格式：0xFF 0xAA len(7\3) 0x09 data checksum
							//data1:0x01 data2-data3:当前选中1-N	data4分辨率（1080P、720P60、720P30） data5:总时长
							//Data6:加锁状态 0未加锁 1加锁
							//data1:0x02 data2播放状态 停止（退出播放界面回列表界面0）播放界面1

	NAVIACK_MOV_PB_OPREQ    = 0x0A,	
							//格式：0xFF 0xAA len(3) 0x0A data checksum
							//data1:0x01	data2:0x01播放 0x02暂停
							//data1:0x02	data2:时间//进度条时间 播放中改变即发
							//data1:0x03	data2:	0x01 全部加锁开始执行
							//0x02 全部解锁开始执行 
							//				0x03 删除所有开始执行
							//				0x00 执行命令完成

	NAVIACK_EVENT_LIST_MSG  = 0x0C,
							//event列表信息：（进event 时DVR主动发送）
							//格式：0xFF 0xAA len(4\10) 0x0C data checksum
							//data1:0x01 data2-data3:总数(<1000)
							//data1:0x02 data2-data3:第N条(<1000)  data4-data9:ymdhms 6个BYTE 

	NAVIACK_EVENT_REQ       = 0x0D,	
							//格式：0xFF 0xAA len(7\3) 0x0D data checksum
							//data1:0x01 data2-data3:当前选中1-N	data4分辨率（1080P、720P60、720P30） data5:总时长
							//Data6:加锁状态 0未加锁 1加锁
							//data1:0x02 data2播放状态 停止（退出播放界面回列表界面0）播放界面1

	NAVIACK_EVENT_REP_REQ   = 0x0E,	
							//格式：0xFF 0xAA len(3) 0x0E data checksum
							//data1:0x01	data2:0x01播放 0x02暂停
							//data1:0x02	data2:时间//进度条时间 播放中改变即发
							//data1:0x03	data2:	0x01 全部加锁开始执行
							//0x02 全部解锁开始执行 
							//				0x03 删除所有开始执行
							//				0x00 执行命令完成 

	NAVIACK_PHOTO_MSG      = 0x10,	
							//JPG当前信息：
							//格式：0xFF 0xAA len(10) 0x10 data checksum
							//				  data1-5:时间ymdhm 5BYTE 
							//				  data6:图片分辨率（12M、10M、8M、5M、3M、2M）=>发送依次0、1、2、3、4、5代替
							//				  data7-8:图片大小
							//				  Data9:加锁状态 0未加锁 1加锁
							//例：图片大小数据 15.32M  发送1532 =5FC = 0x05 0xFC

	NAVIACK_PHOTO_VIEW      = 0x11,	
							//格式：0xFF 0xAA len(3) 0x11 data checksum
							//data1:0x03	data2:	0x01 全部加锁开始执行
							//0x02 全部解锁开始执行 
							//				0x03 删除所有开始执行
							//				0x00 执行命令完成

	NAVIACK_WARNING_MSG     = 0x12,
							//警告提示信息声音请求：
							//格式：0xFF 0xAA len(2) 0x12 data checksum
							//Data：0x01	警告信息请求（目前没有用）
							//Data：0x02	panel亮度最亮
							//Data：0x03	panel亮度最暗
							//Data:  0x04  表示升级正在升级 








//*********************************************************************************//
//                                           send string to navi
//*********************************************************************************//
	NAVIACK_FILE_COUNT     = 0x13,//#define STATUS_FILE_COUNT     "@file-count??\r"
	NAVIACK_FILE_STATUS     = 0x14,//@file-avi,5/88,256,filename:xxx
	
	NAVIACK_FILE_UNLOCK     = 0x15,//#define STATUS_RECORD_UNLOCK     "@record-unlock\r"   //自动录像创建下一个新的录像文件，默认是没有加锁的
	NAVIACK_FILE_UNLOCK_END = 0x16,//#define STATUS_RECORD_UNLOCK_END "@unlockrecord-end\r"
	NAVIACK_FILE_LOCK_END   = 0x17,//#define STATUS_RECORD_LOCK_END   "@lockrecord-end\r"
	
	NAVIACK_FILE_RECORD_RESTART  = 0x18,//#define STATUS_RECORD_RESTART    "@record-restart\r"
	NAVIACK_FILE_RECORD_STOP     = 0x19,//#define STATUS_RECORD_OFF        "@record-stop\r"

	NAVIACK_SD_FORMAT_FAIL  = 0x1a,//#define STATUS_FORAMT_FAIL     "@format-fail\r"
	NAVIACK_SD_FORMAT_SUCC  = 0x1b,//#define STATUS_FORAMT_SUCC     "@format-succ\r"
	NAVIACK_SD_FORMAT_NOCARD  = 0x1C,//#define STATUS_FORAMT_SUCC     "@format-succ\r"

	
//*********************************************************************************//
//*********************************************************************************//

	NAVIACK_NULL
} UARTACK_S680ID;

typedef enum _DTVCOMMAND_S680ID // get from NAVI
{
	NAVICMD_GPS_MSG         = 0xA1,		
							//Date 内容如下：
							//<1> 定位状态（A=有效定位，V=无效定位1BYTE）
							//<2> 纬度整数 1BYTE
							//<3> 纬度小数 2BYTE
							//<4> 纬度半球N(北半球)或S(南半球) 1BYTE
							//<5> 经度整数1BYTE
							//<6> 经度小数2BYTE
							//<7> 经度半球E(东经)或W(西经) 1BYTE
							//<8> 速度整数2BYTE
							//<9> 日期与时间 ymdhms 6BYTE year-2000发送 

	NAVICMD_PWROFF_MSG      = 0xA2,
							//格式：0xFF 0xAA len(2) 0xA2 0x00 checksum

	NAVICMD_PWRON_MSG_STOP  = 0xA3,
							//格式：0xFF 0xAA len(2) 0xA3 0x00 checksum

	NAVICMD_SW_MODE         = 0xA4,
                            //格式：0xFF 0xAA len(2\2\12) 0xA4 data checksum
                            //Data :data1:01录像 02拍照 03回放
                            
	NAVICMD_REC_MODE_OPREQ	= 0xA5,
	                        //录影模式操作请求：
                            //格式：0xFF 0xAA len(3\3\6\2\2) 0xA5 data checksum
                            //data1:0x01  data2:00 停止录影
                            //                              01录影 
                            //                              02取图 
                            //                              03加锁
                            //data1:0x02  data2:0退菜单1进菜单 

							//data1:0x03  data2:分辨率 data3:停车侦测 
							//data4:录音 data5:重力感应
							//data6:开机自动录像
				
                            //data1:0x04  恢复出厂设置
                            //data1:0x05  格式化SD卡
                            //data1:0x06  返回版本号
                            
	NAVICMD_CAP_MODE_OPREQ	= 0xA6,
	                        //拍照模式操作请求：
                            //格式：0xFF 0xAA len(3\3\3) 0xA6 data checksum
                            //data1:0x01  data2:01拍照
                            //data1:0x02  data2:0退菜单1进菜单 
                            //data1:0x03  data2:分辨率
                            
	NAVICMD_REP_MODE_OPREQ	= 0xA7,
	                        //回放模式操作请求：
                            //格式：0xFF 0xAA  len(3) 0xA7 data checksum
                            //data1:0x01  data2:01video 02envent 03jeg


    NAVICMD_MOV_LIST_OPREQ  = 0xA9,
                            //操作请求（video列表界面）：
                            //格式：0xFF 0xAA len(4\3) 0xA9 data checksum  
                            //data1:0x01  data2-data3:第N条(<1000)  选中 （直接给第几条 相当于DVR idx）
                            //data1:0x02  data2退出播放0进入播放1 
                            //data1:0x03  data2 0=prev 1=next
                            
	NAVICMD_MOV_REP_OPREQ	= 0xAA,
	                        //操作请求（video播放界面）：
                            //格式：0xFF 0xAA len(3) 0xAA data checksum
                            //data1:0x01  data2:0x01 播放暂停 
                            //data1:0x02  data2:时间    //设置进度条              
                            //data1:0x03  data2:  0x01单个加锁或解锁 
                            //0x02全部加锁 
                            //0x03全部解锁
                            //0x04单个删除 
                            //0x05删除所有 
                            
	NAVICMD_EVENT_REQ	    = 0xAD,
	                        //操作请求（event列表界面）：
                            //格式：0xFF 0xAA len(4\3) 0xAD data checksum  
                            //data1:0x01  data2-data3:第N条(<1000)  选中 （直接给第几条 相当于DVR idx）
                            //data1:0x02  data2退出播放0进入播放1 
                            
    NAVICMD_EVENT_REP_REQ   = 0xAE,
                            //操作请求（event播放界面）：
                            //格式：0xFF 0xAA len(3) 0xAE data checksum
                            //data1:0x01  data2:0x01 播放暂停 
                            //data1:0x02  data2:时间    //设置进度条              
                            //data1:0x03  data2:  0x01单个加锁或解锁 
                            //0x02全部加锁 
                            //0x03全部解锁
                            //0x04单个删除 
                            //0x05删除所有 
                            
    NAVICMD_PHOTO_VIEW	    = 0xB0,
                            //格式：0xFF 0xAA len(3) 0xB0 data checksum
                            //data1:0x01  data2:0x01上一张 0x02下一张  （DVR返回为JPG当前信息）
                            //data1:0x02  data2:0x01退出 返回到文件夹界面
                            //data1:0x03  data2:  0x01单个加锁或解锁 
                            //0x02全部加锁 
                            //0x03全部解锁
                            //0x04单个删除 
                            //0x05删除所有 

    NAVICMD_SET_DATE	    = 0xC0,
    NAVICMD_SET_TIME	    = 0xC1,
    
    NAVICMD_END 
} UARTCOMMAND_S680ID;

typedef enum _KEY_VAL
{
	KEY_CH_UP =0x80,
	KEY_CH_DOWN = 0x81,
	KEY_VOL_UP = 0x82,
	KEY_VOL_DOWN = 0x83,
	KEY_PAGE_UP = 0x84,
	KEY_MENU = 0x85,
	KEY_PAUSE = 0x86,
	KEY_EXIT = 0x87,
	KEY_RECALL = 0x88,
	KEY_INFO_VAL = 0x89,
	KEY_POWER = 0x8A,
	KEY_PAGE_DOWN = 0x8B,
	KEY_MUTE = 0x8C,
	KEY_REServed = 0x8D,
	KEY_VAL_0 = 0x90,
	KEY_VAL_1 = 0x91,
	KEY_VAL_2 = 0x92,
	KEY_VAL_3 = 0x93,
	KEY_VAL_4 = 0x94,
	KEY_VAL_5 = 0x95,
	KEY_VAL_6 = 0x96,
	KEY_VAL_7 = 0x97,
	KEY_VAL_8 = 0x98,
	KEY_VAL_9 = 0x99,
	KEY_CAPTURE = 0xA0,
	KEY_LOCK = 0xA1,
	KEY_FRCAM_SWITCH = 0xA2
	
} KEY_VAL;

typedef struct tagKeyButton
{
    unsigned char  iCmdId;
    unsigned char  ulkeyEvent; 
	unsigned char  ubkeyname[16];
} CMDKEY;

/*===========================================================================
 * Structure define
 *===========================================================================*/
extern MMPF_OS_FLAGID   	UartCtrlFlag;
extern MMP_UBYTE 			g_Ack2NaviArg;
#endif // _S680_UART_DRIVER_H_