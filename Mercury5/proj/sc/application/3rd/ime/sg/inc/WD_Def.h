//////////////////////////////////////////////////////////////////////////////
//                                                                           //
//                          WDXT Software System                             //
//                                                                           //
//            Copyright (c) 1999-2004 by Netone Technology Inc.              //
//                        All Rights Reserved                                //
//                                                                           //
//  Model    :	WD_Def.h                                                     //
//                                                                           //
//  Purpose  :	供外部使用的输入法的公共定义                                 //
//                                                                           //
//  Designer :	Rocky Y. Zhang                                               //
//                                                                           //
// --------------------------------------------------------------------------//
//                                                                           //
//  $Author: nyf $    //
//  $Archive:: /输入法/WdxtIme52/include/WD_Def.h                       $    //
//  $Workfile:: WD_Def.h                                                $    //
//  $Date: 2007/01/10 06:15:25 $    //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////


#ifndef WD_COMMON_DEF_H_
#define WD_COMMON_DEF_H_

#include "WD_Common.h"
#include "sg_common_public.h"

/***************************** 定义按键键值 ******************************/
/* a、数字键：0 ~ 9 */
#define WDK_NORMAL_0		0x10	/* 用于输入键码和选择                */
#define WDK_NORMAL_1		0x11
#define WDK_NORMAL_2		0x12
#define WDK_NORMAL_3		0x13
#define WDK_NORMAL_4		0x14
#define WDK_NORMAL_5		0x15
#define WDK_NORMAL_6		0x16
#define WDK_NORMAL_7		0x17
#define WDK_NORMAL_8		0x18
#define WDK_NORMAL_9		0x19

/* a、全字母键：各语言，不同字母对应的输入法键值，请参考各输入法对应的键值定义说明文档 */

#define WDK_NORMAL_LETTER   0xB0					    //从0xB0开始为字母键
#define WDK_NORMAL_A		(WDK_NORMAL_LETTER+0x01)	//  1
#define WDK_NORMAL_B		(WDK_NORMAL_LETTER+0x02)    //  2
#define WDK_NORMAL_C		(WDK_NORMAL_LETTER+0x03)    //  3
#define WDK_NORMAL_D		(WDK_NORMAL_LETTER+0x04)	//  4
#define WDK_NORMAL_E		(WDK_NORMAL_LETTER+0x05)    //  5
#define WDK_NORMAL_F		(WDK_NORMAL_LETTER+0x06)	//  6
#define WDK_NORMAL_G		(WDK_NORMAL_LETTER+0x07)	//  7
#define WDK_NORMAL_H		(WDK_NORMAL_LETTER+0x08)	//  8
#define WDK_NORMAL_I		(WDK_NORMAL_LETTER+0x09)	//  9
#define WDK_NORMAL_J		(WDK_NORMAL_LETTER+0x0A)	//  10
#define WDK_NORMAL_K		(WDK_NORMAL_LETTER+0x0B)	//  11
#define WDK_NORMAL_L		(WDK_NORMAL_LETTER+0x0C)	//  12
#define WDK_NORMAL_M		(WDK_NORMAL_LETTER+0x0D)	//  13
#define WDK_NORMAL_N		(WDK_NORMAL_LETTER+0x0E)	//  14
#define WDK_NORMAL_O		(WDK_NORMAL_LETTER+0x0F)	//  15
#define WDK_NORMAL_P		(WDK_NORMAL_LETTER+0x10)	//  16
#define WDK_NORMAL_Q		(WDK_NORMAL_LETTER+0x11)	//  17
#define WDK_NORMAL_R		(WDK_NORMAL_LETTER+0x12)	//  18
#define WDK_NORMAL_S		(WDK_NORMAL_LETTER+0x13)	//  19
#define WDK_NORMAL_T		(WDK_NORMAL_LETTER+0x14)	//  20
#define WDK_NORMAL_U		(WDK_NORMAL_LETTER+0x15)	//  21
#define WDK_NORMAL_V		(WDK_NORMAL_LETTER+0x16)	//  22
#define WDK_NORMAL_W		(WDK_NORMAL_LETTER+0x17)	//  23
#define WDK_NORMAL_X		(WDK_NORMAL_LETTER+0x18)	//  24
#define WDK_NORMAL_Y		(WDK_NORMAL_LETTER+0x19)	//  25
#define WDK_NORMAL_Z		(WDK_NORMAL_LETTER+0x1A)    //  26

#define WDK_NORMAL_A1		(WDK_NORMAL_LETTER+0x1B)	//  27
#define WDK_NORMAL_B1		(WDK_NORMAL_LETTER+0x1C)	//  28
#define WDK_NORMAL_C1		(WDK_NORMAL_LETTER+0x1D)	//  29
#define WDK_NORMAL_D1		(WDK_NORMAL_LETTER+0x1E)	//  30
#define WDK_NORMAL_E1		(WDK_NORMAL_LETTER+0x1F)	//  31
#define WDK_NORMAL_F1		(WDK_NORMAL_LETTER+0x20)	//  32
#define WDK_NORMAL_G1		(WDK_NORMAL_LETTER+0x21)	//  33
#define WDK_NORMAL_H1		(WDK_NORMAL_LETTER+0x22)	//  34
#define WDK_NORMAL_I1		(WDK_NORMAL_LETTER+0x23)	//  35
#define WDK_NORMAL_J1		(WDK_NORMAL_LETTER+0x24)	//  36
#define WDK_NORMAL_K1		(WDK_NORMAL_LETTER+0x25)	//  37
#define WDK_NORMAL_L1		(WDK_NORMAL_LETTER+0x26)	//  38
#define WDK_NORMAL_M1		(WDK_NORMAL_LETTER+0x27)	//  39
#define WDK_NORMAL_N1		(WDK_NORMAL_LETTER+0x28)	//  40
#define WDK_NORMAL_O1		(WDK_NORMAL_LETTER+0x29)	//	41
#define WDK_NORMAL_P1		(WDK_NORMAL_LETTER+0x2A)	//	42
#define WDK_NORMAL_Q1		(WDK_NORMAL_LETTER+0x2B)	//	43
#define WDK_NORMAL_R1		(WDK_NORMAL_LETTER+0x2C)	//	44
#define WDK_NORMAL_S1		(WDK_NORMAL_LETTER+0x2D)	//	45
#define WDK_NORMAL_T1		(WDK_NORMAL_LETTER+0x2E)	//	46
#define WDK_NORMAL_U1		(WDK_NORMAL_LETTER+0x2F)	//	47
#define WDK_NORMAL_V1		(WDK_NORMAL_LETTER+0x30)	//	48
#define WDK_NORMAL_W1		(WDK_NORMAL_LETTER+0x31)	//	49
#define WDK_NORMAL_X1		(WDK_NORMAL_LETTER+0x32)	//	50
#define WDK_NORMAL_Y1		(WDK_NORMAL_LETTER+0x33)	//	51
#define WDK_NORMAL_Z1		(WDK_NORMAL_LETTER+0x34)    //	52 //0XE4

#define WDK_NORMAL_A2		(WDK_NORMAL_LETTER+0x35)	//  53	//0XE5
#define WDK_NORMAL_B2		(WDK_NORMAL_LETTER+0x36)	//  54
#define WDK_NORMAL_C2		(WDK_NORMAL_LETTER+0x37)	//  55
#define WDK_NORMAL_D2		(WDK_NORMAL_LETTER+0x38)	//  56
#define WDK_NORMAL_E2		(WDK_NORMAL_LETTER+0x39)	//  57
#define WDK_NORMAL_F2		(WDK_NORMAL_LETTER+0x3A)	//  58
#define WDK_NORMAL_G2		(WDK_NORMAL_LETTER+0x3B)	//  59
#define WDK_NORMAL_H2		(WDK_NORMAL_LETTER+0x3C)	//  60
#define WDK_NORMAL_I2		(WDK_NORMAL_LETTER+0x3D)	//  61
#define WDK_NORMAL_J2		(WDK_NORMAL_LETTER+0x3E)	//  62
#define WDK_NORMAL_K2		(WDK_NORMAL_LETTER+0x3F)	//  63	//0xef
#define WDK_NORMAL_L2		(WDK_NORMAL_LETTER+0x40)	//  64
#define WDK_NORMAL_M2		(WDK_NORMAL_LETTER+0x41)	//  65
#define WDK_NORMAL_N2		(WDK_NORMAL_LETTER+0x42)	//  66
#define WDK_NORMAL_O2		(WDK_NORMAL_LETTER+0x43)	//	67
#define WDK_NORMAL_P2		(WDK_NORMAL_LETTER+0x44)	//	68
#define WDK_NORMAL_Q2		(WDK_NORMAL_LETTER+0x45)	//	69
#define WDK_NORMAL_R2		(WDK_NORMAL_LETTER+0x46)	//	70
#define WDK_NORMAL_S2		(WDK_NORMAL_LETTER+0x47)	//	71
#define WDK_NORMAL_T2		(WDK_NORMAL_LETTER+0x48)	//	72
#define WDK_NORMAL_U2		(WDK_NORMAL_LETTER+0x49)	//	73
#define WDK_NORMAL_V2		(WDK_NORMAL_LETTER+0x4A)	//	74 //0xfa
#define WDK_NORMAL_W2		(WDK_NORMAL_LETTER+0x4B)	//	75
#define WDK_NORMAL_X2		(WDK_NORMAL_LETTER+0x4C)	//	76
#define WDK_NORMAL_Y2		(WDK_NORMAL_LETTER+0x4D)	//	77	//0xfd
#define WDK_NORMAL_A3		(WDK_NORMAL_LETTER+0x4E)	//  53	//0XE5
#define WDK_NORMAL_B3		(WDK_NORMAL_LETTER+0x4F)	//  54
#define WDK_NORMAL_C3		(WDK_NORMAL_LETTER+0x50)	//  55
#define WDK_NORMAL_D3		(WDK_NORMAL_LETTER+0x51)	//  56
#define WDK_NORMAL_E3		(WDK_NORMAL_LETTER+0x52)	//  57
#define WDK_NORMAL_F3		(WDK_NORMAL_LETTER+0x53)	//  58
#define WDK_NORMAL_G3		(WDK_NORMAL_LETTER+0x54)	//  59
#define WDK_NORMAL_H3		(WDK_NORMAL_LETTER+0x55)	//  60
#define WDK_NORMAL_I3		(WDK_NORMAL_LETTER+0x56)	//  61
#define WDK_NORMAL_J3		(WDK_NORMAL_LETTER+0x57)	//  62
#define WDK_NORMAL_K3		(WDK_NORMAL_LETTER+0x58)	//  63	//0xef
#define WDK_NORMAL_L3		(WDK_NORMAL_LETTER+0x59)	//  64
#define WDK_NORMAL_M3		(WDK_NORMAL_LETTER+0x5A)	//  65
#define WDK_NORMAL_N3		(WDK_NORMAL_LETTER+0x5B)	//  66
#define WDK_NORMAL_O3		(WDK_NORMAL_LETTER+0x5C)	//	67
#define WDK_NORMAL_P3		(WDK_NORMAL_LETTER+0x5D)	//	68
#define WDK_NORMAL_Q3		(WDK_NORMAL_LETTER+0x5E)	//	69
#define WDK_NORMAL_R3		(WDK_NORMAL_LETTER+0x5F)	//	70
#define WDK_NORMAL_S3		(WDK_NORMAL_LETTER+0x60)	//	71
#define WDK_NORMAL_T3		(WDK_NORMAL_LETTER+0x61)	//	72
#define WDK_NORMAL_U3		(WDK_NORMAL_LETTER+0x62)	//	73
#define WDK_NORMAL_V3		(WDK_NORMAL_LETTER+0x63)	//	74 //0xfa
#define WDK_NORMAL_W3		(WDK_NORMAL_LETTER+0x64)	//	75
#define WDK_NORMAL_X3		(WDK_NORMAL_LETTER+0x65)	//	76
#define WDK_NORMAL_Y3		(WDK_NORMAL_LETTER+0x66)	//	77	//0xfd
#define WDK_NORMAL_Z3		(WDK_NORMAL_LETTER+0x67)
#define WDK_NORMAL_A4		(WDK_NORMAL_LETTER+0x68)	//  53	//0XE5
#define WDK_NORMAL_B4		(WDK_NORMAL_LETTER+0x69)	//  54
#define WDK_NORMAL_C4		(WDK_NORMAL_LETTER+0x6a)	//  55
#define WDK_NORMAL_D4		(WDK_NORMAL_LETTER+0x6b)	//  56
#define WDK_NORMAL_E4		(WDK_NORMAL_LETTER+0x6c)	//  57
#define WDK_NORMAL_F4		(WDK_NORMAL_LETTER+0x6d)	//  58
#define WDK_NORMAL_G4		(WDK_NORMAL_LETTER+0x6e)	//  59
#define WDK_NORMAL_H4		(WDK_NORMAL_LETTER+0x6f)	//  60
#define WDK_NORMAL_I4		(WDK_NORMAL_LETTER+0x70)	//  61
#define WDK_NORMAL_J4		(WDK_NORMAL_LETTER+0x71)	//  62
#define WDK_NORMAL_K4		(WDK_NORMAL_LETTER+0x72)	//  63	//0xef
#define WDK_NORMAL_L4		(WDK_NORMAL_LETTER+0x73)	//  64
#define WDK_NORMAL_M4		(WDK_NORMAL_LETTER+0x74)	//  65
#define WDK_NORMAL_N4		(WDK_NORMAL_LETTER+0x75)	//  66
#define WDK_NORMAL_O4		(WDK_NORMAL_LETTER+0x76)	//	67
#define WDK_NORMAL_P4		(WDK_NORMAL_LETTER+0x77)	//	68
#define WDK_NORMAL_Q4		(WDK_NORMAL_LETTER+0x78)	//	69
#define WDK_NORMAL_R4		(WDK_NORMAL_LETTER+0x79)	//	70
#define WDK_NORMAL_S4		(WDK_NORMAL_LETTER+0x7a)	//	71
#define WDK_NORMAL_T4		(WDK_NORMAL_LETTER+0x7b)	//	72
#define WDK_NORMAL_U4		(WDK_NORMAL_LETTER+0x7c)	//	73
#define WDK_NORMAL_V4		(WDK_NORMAL_LETTER+0x7d)	//	74 //0xfa
#define WDK_NORMAL_W4		(WDK_NORMAL_LETTER+0x7e)	//	75
#define WDK_NORMAL_X4		(WDK_NORMAL_LETTER+0x7f)	//	76
#define WDK_NORMAL_Y4		(WDK_NORMAL_LETTER+0x80)	//	77	//0xfd
#define WDK_NORMAL_Z4		(WDK_NORMAL_LETTER+0x81)

/* b、功能键,具体每个键上的功能定义请参考《输入法功能按键定义列表.xls》 */
#define	WDK_STAR			0x1A	/* "*" 键                           */
#define	WDK_SHARP			0x1B	/* "#" 键                           */
#define WDK_UP				0x1C	/* 方向键                           */
#define WDK_DOWN			0x1D	
#define WDK_LEFT			0x1E		
#define WDK_RIGHT			0x1F
#define WDK_C				0x20	/* 删除键	                         */
#define WDK_OK				0x21	/* 确认键：用于确认当前的选择项      */
#define WDK_MENU			0x22	/* 全键盘时，执行FN键功能            */
#define WDK_SOFTLEFT		0x23	/* 左软键：全键盘时，执行空格键功能  */
#define WDK_SOFTRIGHT		0x24	/* 右软键：                          */
#define WDK_SHIFT			0x3A	/* Shift                             */
#define WDK_CAPLOCK			0x3B	/* 大小写切换：                      */
#define WDK_SEPERATER		0x3C	/* 分隔                              */
#define WDK_FUNC			0x3D	/* FN：                              */
#define WDK_ENTER			0x3E	/* 回车                              */
#define WDK_ALT 			0x3F	/* Alt                               */
#define WDK_CTRL			0x40	/* Ctrl                              */
#define WDK_SPACE			0x41    /*空格*/
/* c、长按数字键：0 ~ 9	*/
#define WDK_LONG_0			0x25	/* 长按数字键，可用于直接选择        */
#define WDK_LONG_1			0x26
#define WDK_LONG_2			0x27
#define WDK_LONG_3			0x28
#define WDK_LONG_4			0x29
#define WDK_LONG_5			0x2A
#define WDK_LONG_6			0x2B
#define WDK_LONG_7			0x2C
#define WDK_LONG_8			0x2D
#define WDK_LONG_9			0x2E

/* d、长按功能键 */
#define WDK_LONG_STAR		0x2F	/* 长按"#" 键，						 */
#define	WDK_LONG_SHARP		0x30	/* 长按"*" 键，                      */
#define WDK_LONG_UP			0x31	/* 长按上键 		                 */
#define WDK_LONG_DOWN		0x32	/* 长按下键 		                 */
#define WDK_LONG_LEFT		0x33	/* 长按左键                          */
#define WDK_LONG_RIGHT		0x34	/* 长按右键                          */
#define WDK_LONG_C			0x35	/* 长按“C”键，可用于删除全部键码	 */
#define WDK_LONG_OK         0X36	/* 长按“OK”键，可用于确认全部字词	 */
#define WDK_LONG_MENU       0X37	/* 长按                              */
#define WDK_LONG_SOFTLEFT	0x38	/* 长按左软键：                      */
#define WDK_LONG_SOFTRIGHT	0x39	/* 长按右软键：                      */
/***************************** 定义按键键值 ******************************/


/* 定义输入状态 */
#define WD_STATUS_CHINESE_NORMAL		 0		/* 中文初始状态          */
#define WD_STATUS_CHINESE_INPUT			 1		/* 中文正常输入状态      */
#define WD_STATUS_CHINESE_SELECTPINYIN   2		/* 中文纯拼选音状态      */
#define WD_STATUS_CHINESE_SELECTTONE	 3		/* 中文选择音调状态      */
#define WD_STATUS_CHINESE_SELECT		 4		/* 中文选择状态          */
#define WD_STATUS_CHINESE_LEGEND		 5		/* 中文联想状态          */
#define WD_STATUS_CHINESE_USERDICT	  	 6		/* 中文自造词状态        */

#define WD_STATUS_FOREIGN_NORMAL		 7		/* 外文初始状态          */
#define WD_STATUS_FOREIGN_INPUT			 8		/* 外文正常输入状态      */
#define WD_STATUS_FOREIGN_SELECTLETTER	 9		/* 外文补字和改字状态    */
#define WD_STATUS_FOREIGN_PREPOSTFIX	 10		/* 外文前后缀状态        */
#define WD_STATUS_FOREIGN_SELECT		 11		/* 外文选择状态          */
#define WD_STATUS_FOREIGN_LEGEND		 12		/* 外文联想状态          */
#define WD_STATUS_FOREIGN_USERDICT	     13		/* 外文自造词状态        */
#define WD_STATUS_ABC_NORMAL			 14		/* 字母ABC输入初始状态   */
#define	WD_STATUS_ABC_INPUT				 15		/* 字母ABC输入状态       */
#define WD_STATUS_FOREIGN_TONE			 16		/* 外文输入音调状态      */

#define WD_STATUS_SYMBOL_TABLE			 17		/* 符号菜单状态          */
#define WD_STATUS_SYMBOL_GROUP			 18		/* 符号组状态            */
#define WD_STATUS_DIGIT_INPUT			 19		/* 数字输入状态          */
#define WD_STATUS_IME_CHANGE			 20		/* 输入法切换状态        */
#define WD_STATUS_HELP					 21		/* 输入法切换状态        */
#define WD_STATUS_CONFIG				 22		/* 输入法设置状态        */
#define WD_STATUS_USERDICT_MANAGE		 23		/* 输入法自造词管理状态  */

#define WD_STATUS_HOTKEY_SYMBOL		 	 24		/* 热键符号状态          */
#define WD_STATUS_HOTKEY_FACE			 25		/* 热健表情符号状态      */
#define WD_STATUS_LETTERMODE			 26		/* 字母状态              */





/**************************** 定义输入法种类 ********************************************/
/*通过删除掉想要的输入法前面的注释符来选择输入法，数字和符号是必需的					*/
#define WDI_DIGIT			0x01	/* 数字												*/


//汉语，6 种。
#define WDI_CN_CPINYIN		0x03	/* 纯拼音											*/
#define WDI_CN_BIHUA		0x07	/* 笔划												*/

//暂时搜狗中文输入法还不支持一下几种中文输入法
#define WDI_CN_SPINYIN		0x04	/* 数码拼音											*/
#define WDI_CN_FULLPINYIN	0x05	/* 全字母拼音输入									*/
#define WDI_CN_ZHUYIN		0x06	/* 台湾注音，用于数字键								*/
#define WDI_CN_BUJIAN		0x08	/* 笔划部件											*/
#define WDI_CN_BIHUAF       0x0a    /*繁体笔画											*/ 



#define WDI_CN_HKPINYIN		0x0b    /*香港拼音											*/
#define WDI_CN_FULLZHUYIN   0x0c    /*全字母注音，用于全字母键盘						*/
#define	WDI_CN_MULTI_ZHUYIN	0x0e	/*MULTI 注音输入法									*/
#define	WDI_JAPANESE		0x0d	/*智能日语											*/


#define WDI_FOREIGN_BEGIN   0x20	/* 外文（拼音文字）的开始位置						*/
#define WDI_HANDWRITE_BEGIN 0x80

#define WDI_MULTIABC_BEGIN	0xA0   //字母输入法的起始位置

//中国少数民族语言，6 种
#define WDI_UIGHUR			WDI_FOREIGN_BEGIN + 0x09	/* 智能维吾尔语					*/
#define WDI_KAZAK			WDI_FOREIGN_BEGIN + 0x0A	/* 智能哈萨克语					*/
#define WDI_KELKZ			WDI_FOREIGN_BEGIN + 0x0B	/* 智能柯尔克孜语				*/
#define WDI_TIBETAN			WDI_FOREIGN_BEGIN + 0x0C	/* 智能藏语						*/
#define WDI_MONGAL			WDI_FOREIGN_BEGIN + 0x0D	/* 智能蒙语						*/
#define WDI_CNKOREAN		WDI_FOREIGN_BEGIN + 0x0E	/* 智能朝鲜语					*/
#define WDI_CHNDAI			WDI_FOREIGN_BEGIN + 0x0F    /* 智能傣语						*/
#define	WDI_YI   			WDI_FOREIGN_BEGIN + 0x06	/* 智能彝语						*/
#define	WDI_MIAO		    WDI_FOREIGN_BEGIN + 0x07	/* 智能苗语	WANGHUI					*/
#define WDI_CHNZHUANG		WDI_FOREIGN_BEGIN + 0x08	/* 智能壮语						*/
#define WDI_CHNDONG			WDI_FOREIGN_BEGIN + 0x09	/* 智能侗语						*/

//欧洲语言，共30 种。
#define WDI_ENGLISH			WDI_FOREIGN_BEGIN + 0x10	/* 智能英语					    */
#define WDI_FRENCH			WDI_FOREIGN_BEGIN + 0x11	/* 智能法语					    */
#define WDI_GERMAN			WDI_FOREIGN_BEGIN + 0x12	/* 智能德语					    */
#define WDI_ITALIAN			WDI_FOREIGN_BEGIN + 0x13	/* 智能意大利语				    */
#define WDI_SPANISH			WDI_FOREIGN_BEGIN + 0x14	/* 智能西班牙语				    */
#define WDI_PORTUGUESE		WDI_FOREIGN_BEGIN + 0x15	/* 智能葡萄牙语				    */
#define WDI_DUTCH			WDI_FOREIGN_BEGIN + 0x16	/* 智能荷兰语				    */
#define WDI_CATALAN			WDI_FOREIGN_BEGIN + 0x17	/* 智能加泰隆语				    */
#define WDI_SWEDISH			WDI_FOREIGN_BEGIN + 0x18	/* 智能瑞典语				    */
#define WDI_DANISH			WDI_FOREIGN_BEGIN + 0x19	/* 智能丹麦语		            */
#define WDI_FINNISH			WDI_FOREIGN_BEGIN + 0x1A	/* 智能芬兰语			        */
#define WDI_NORWEGIAN		WDI_FOREIGN_BEGIN + 0x1B	/* 智能挪威语				    */
#define WDI_ICELANDIC		WDI_FOREIGN_BEGIN + 0x1C	/* 智能冰岛语					*/
#define WDI_GREEK			WDI_FOREIGN_BEGIN + 0x1D	/* 智能希腊语				    */
#define WDI_TURKISH			WDI_FOREIGN_BEGIN + 0x1E	/* 智能土耳其语				    */
#define WDI_ESTONIAN		WDI_FOREIGN_BEGIN + 0x1F	/* 智能爱沙尼亚语				*/
#define WDI_LATVIAN			WDI_FOREIGN_BEGIN + 0x20	/* 智能拉脱维亚语				*/
#define WDI_LITHUANIAN		WDI_FOREIGN_BEGIN + 0x21	/* 智能立陶宛语					*/
#define WDI_SLOVENIAN		WDI_FOREIGN_BEGIN + 0x22	/* 智能斯洛文尼亚语				*/
#define WDI_SERBIAN			WDI_FOREIGN_BEGIN + 0x23	/* 智能塞尔维亚语语				*/
#define WDI_CROATIAN		WDI_FOREIGN_BEGIN + 0x24	/* 智能克罗地亚语语				*/
#define WDI_RUSSIAN			WDI_FOREIGN_BEGIN + 0x25	/* 智能俄语						*/
#define WDI_UKRAINIAN		WDI_FOREIGN_BEGIN + 0x26	/* 智能乌克兰语					*/
#define WDI_HUNGARIAN		WDI_FOREIGN_BEGIN + 0x27	/* 智能匈牙利语					*/
#define WDI_POLISH			WDI_FOREIGN_BEGIN + 0x28	/* 智能波兰语					*/
#define WDI_BULGARIAN		WDI_FOREIGN_BEGIN + 0x29	/* 智能保加利亚语				*/
#define WDI_CZECH			WDI_FOREIGN_BEGIN + 0x2A	/* 智能捷克语					*/
#define WDI_SLOVAK			WDI_FOREIGN_BEGIN + 0x2B	/* 智能斯洛伐克语				*/
#define WDI_ROMANIAN		WDI_FOREIGN_BEGIN + 0x2C	/* 智能罗马尼亚语				*/
#define WDI_LATIN			WDI_FOREIGN_BEGIN + 0x2D	/* 智能拉丁语					*/

#define WDI_KOREAN			WDI_FOREIGN_BEGIN + 0x31	/* 智能韩语						*/
#define WDI_THAI			WDI_FOREIGN_BEGIN + 0x32	/* 智能泰国语					*/
#define WDI_INDONESIAN		WDI_FOREIGN_BEGIN + 0x33	/* 智能印尼语					*/
#define WDI_MALAY			WDI_FOREIGN_BEGIN + 0x34	/* 智能马来语					*/
#define WDI_TACALUE			WDI_FOREIGN_BEGIN + 0x35	/* 智能泰加洛语					*/
#define WDI_VIETNAMESE	    WDI_FOREIGN_BEGIN + 0x36	/* 智能越南语					*/
#define WDI_LAO				WDI_FOREIGN_BEGIN + 0x37	/* 智能老挝语					*/
#define WDI_CAMBODIAN		WDI_FOREIGN_BEGIN + 0x38	/* 智能柬埔寨语					*/
#define WDI_BURMESE			WDI_FOREIGN_BEGIN + 0x39	/* 智能缅甸语					*/
#define WDI_ARABIC			WDI_FOREIGN_BEGIN + 0x3A	/* 智能阿拉伯语					*/
#define WDI_PERSIAN			WDI_FOREIGN_BEGIN + 0x3B	/* 智能波斯语					*/
#define WDI_HINDI			WDI_FOREIGN_BEGIN + 0x3C	/* 智能印地语					*/
#define WDI_SINHALESE		WDI_FOREIGN_BEGIN + 0x3D	/* 智能僧加罗语					*/
#define WDI_URDU			WDI_FOREIGN_BEGIN + 0x3E	/* 智能乌尔都语					*/
#define WDI_TAGALOG			WDI_FOREIGN_BEGIN + 0x40	/* 智能他加禄语					*/
#define WDI_KAZAKH          WDI_FOREIGN_BEGIN + 0x41    /* 智能哈萨克语*/ 
#define WDI_BENGALI			WDI_FOREIGN_BEGIN + 0x42		// 孟加拉语输入法
//非洲及其它民族语言，共6种
#define WDI_AFRIKAANS		WDI_FOREIGN_BEGIN + 0x50	/* 智能南非语					*/
#define WDI_HAOSA			WDI_FOREIGN_BEGIN + 0x51	/* 智能豪萨语					*/
#define WDI_SWAHILI			WDI_FOREIGN_BEGIN + 0x52	/* 智能斯瓦希里语				*/
#define WDI_YIBO			WDI_FOREIGN_BEGIN + 0x53	/* 智能伊博语					*/
#define WDI_TUJUE			WDI_FOREIGN_BEGIN + 0x54	/* 智能突厥语					*/
#define WDI_HEBREW			WDI_FOREIGN_BEGIN + 0x55	/* 智能希伯莱语					*/

//字母输入法种类
#define WDI_ENGLISH_ABC			WDI_MULTIABC_BEGIN + 0x01	/* 字母ABC						*/	
#define WDI_LATIN_ABC			WDI_MULTIABC_BEGIN + 0x02	/* 拉丁语系字母ABC						*/	
#define WDI_ARABICS_ABC			WDI_MULTIABC_BEGIN + 0x03	/* 智能阿拉伯语					*/
#define WDI_RUSSIAN_ABC			WDI_MULTIABC_BEGIN + 0x04	/* 俄语字母ABC						*/	
#define WDI_FRENCH_ABC			WDI_MULTIABC_BEGIN + 0x05	/* 法语字母ABC						*/	
#define WDI_VIETNAMESE_ABC		WDI_MULTIABC_BEGIN + 0x06	/* 越南语字母ABC						*/	
#define WDI_THAI_ABC			WDI_MULTIABC_BEGIN + 0x07	/* 泰语字母ABC						*/	
#define WDI_INDONESIAN_ABC		WDI_MULTIABC_BEGIN + 0x08	/* 印度尼西亚字母ABC						*/	
#define WDI_PORTUGUESE_ABC		WDI_MULTIABC_BEGIN + 0x09	/* 葡萄牙字母ABC						*/	
#define WDI_GERMAN_ABC			WDI_MULTIABC_BEGIN + 0x0a	//德文字母输入法
#define WDI_SPANISH_ABC			WDI_MULTIABC_BEGIN + 0x0b	//西班牙文字母输入法
#define WDI_MALAY_ABC			WDI_MULTIABC_BEGIN + 0x0c	//马来语字母输入法
#define WDI_PERSIAN_ABC			WDI_MULTIABC_BEGIN + 0x0d		//波斯语字母输入法
#define WDI_TURKISH_ABC			WDI_MULTIABC_BEGIN + 0x0e		//土耳其语字母输入法
#define WDI_ITALIAN_ABC			WDI_MULTIABC_BEGIN + 0x0f		//意大利语字母输入法
#define WDI_HINDI_ABC			WDI_MULTIABC_BEGIN + 0x10		//印地语字母输入法
#define WDI_CZECH_ABC			WDI_MULTIABC_BEGIN + 0x11		//捷克语字母输入法
#define WDI_DUTCH_ABC			WDI_MULTIABC_BEGIN + 0x12		//荷兰语字母输入法
#define WDI_HEBREW_ABC			WDI_MULTIABC_BEGIN + 0x13		//希伯来语字母输入法
#define WDI_POLISH_ABC			WDI_MULTIABC_BEGIN + 0x14		//波兰语字母输入法	
#define WDI_UIGHUR_ABC			WDI_MULTIABC_BEGIN + 0x15		//维吾尔语字母输入法
#define WDI_SWEDISH_ABC			WDI_MULTIABC_BEGIN + 0x16		//瑞典语字母输入法
#define WDI_FINNISH_ABC			WDI_MULTIABC_BEGIN + 0x17		//芬兰语字母输入法
#define WDI_NORWEGIAN_ABC		WDI_MULTIABC_BEGIN + 0x18		//挪威语字母输入法
#define WDI_DANISH_ABC			WDI_MULTIABC_BEGIN + 0x19		//丹麦语字母输入法
#define WDI_LAO_ABC				WDI_MULTIABC_BEGIN + 0x1A		//老挝语字母输入法
#define WDI_URDU_ABC			WDI_MULTIABC_BEGIN + 0x1B		//乌尔都语字母输入法
#define WDI_KAZAK_ABC			WDI_MULTIABC_BEGIN + 0x1C		//哈萨克（中国）语字母输入法
#define WDI_ICELANDIC_ABC		WDI_MULTIABC_BEGIN + 0x1D		//冰岛语字母输入法
#define WDI_SLOVAK_ABC			WDI_MULTIABC_BEGIN + 0x1E		//斯洛伐克语字母输入法
#define WDI_ESTONIAN_ABC		WDI_MULTIABC_BEGIN + 0x1F		//爱沙尼亚语字母输入法
#define WDI_BELARUSIAN_ABC		WDI_MULTIABC_BEGIN + 0x20		//白俄罗斯语字母输入法
#define WDI_LATVIAN_ABC			WDI_MULTIABC_BEGIN + 0x21		//拉脱维亚语字母输入法
#define WDI_SLOVENIAN_ABC		WDI_MULTIABC_BEGIN + 0x22		//斯洛文尼亚语字母输入法
#define WDI_CROATIAN_ABC		WDI_MULTIABC_BEGIN + 0x23		//克罗地亚语字母输入法
#define WDI_SERBIAN_ABC			WDI_MULTIABC_BEGIN + 0x24		//塞尔维亚语字母输入法
#define WDI_HAUSA_ABC			WDI_MULTIABC_BEGIN + 0x25		//豪萨语字母输入法
#define WDI_IGBO_ABC			WDI_MULTIABC_BEGIN + 0x26		//伊博语字母输入法
#define WDI_TURKMEN_ABC			WDI_MULTIABC_BEGIN + 0x27		//土库曼语字母输入法	
#define WDI_SWAHILI_ABC			WDI_MULTIABC_BEGIN + 0x28		//斯瓦希里语字母输入法	
#define WDI_HUNGARIAN_ABC		WDI_MULTIABC_BEGIN + 0x29		//匈牙利语字母输入法
#define WDI_GREEK_ABC			WDI_MULTIABC_BEGIN + 0x2A		//希腊语字母输入法
#define WDI_KAZAKH_ABC			WDI_MULTIABC_BEGIN + 0x2B		//哈萨克语字母输入法
#define WDI_ROMANIAN_ABC		WDI_MULTIABC_BEGIN + 0x2C		//罗马尼亚语字母输入法
#define WDI_TAGALOG_ABC			WDI_MULTIABC_BEGIN + 0x2D		//他加禄语字母输入法
#define WDI_BOSNIAN_ABC			WDI_MULTIABC_BEGIN + 0x2E		//波斯尼亚语字母输入法
#define WDI_TAMIL_ABC           WDI_MULTIABC_BEGIN + 0x2F       //泰米尔语字母输入法
#define WDI_CYRILLIC_ABC		WDI_MULTIABC_BEGIN + 0x30       //西里尔语系字母输入法
#define WDI_SERBIANC_ABC		WDI_MULTIABC_BEGIN + 0x31       //字母塞尔维亚(西里尔)
#define WDI_TIBETAN_ABC			WDI_MULTIABC_BEGIN + 0x32		// 藏语字母输入法qls
#define WDI_BENGALI_ABC			WDI_MULTIABC_BEGIN + 0x33		// 孟加拉语字母输入法qls
#define WDI_KHMER_ABC			WDI_MULTIABC_BEGIN + 0x34		// 高棉语字母输入法 qls add 
#define WDI_NEPALI_ABC			WDI_MULTIABC_BEGIN + 0x35		// 尼泊尔语字母输入法 qls add 
#define WDI_TELUGU_ABC			WDI_MULTIABC_BEGIN + 0x36		//泰卢固语字母输入法
#define WDI_BULGARIAN_ABC		WDI_MULTIABC_BEGIN + 0x37		/* 保加利亚语字母				*/
/**************************** 定义输入法种类 *****************************/

#define WD_CODE_GBK			0
#define WD_CODE_BIG5		1
#define WD_CODE_UNICODE		2
#define WD_CODE_QUWEI		3

#define DEFAULTIME			0
#define NEEDSELECTLETTER	1
#define FOCUSMOVE			2
#define SELECTONE			3
#define USERWORDMODE		4
#define LETTERTABLE			5

/*************************** 定义外部边界常数 ************************************/
#define WD_IME_TOTAL				10/*62*/		//输入法同时支持多个数
#define MAX_IME_LANGUAGE			64		/* 最大语种数量						 */
// #define MAX_LETTER_COUNT			120     /* 语种最大字母数					 *///qls change 100 to 120 藏语103	
#define IME_STRING_LEN				4		/* 语种的提示字符串长度字节数        */
#define MAX_KEY_LETTERCOUNT			26		/* 最大的键位上的字母数              */
#define	MAX_KEYS_COUNT				12		/* 手机键盘上用于键码的键数			 */
#define MAX_KEYS_LEN				27		/* 输入的键码数的最大值				 *///jh add
#define MAX_WORD_LEN				28		/* 最大拼音/外文单词长度			 */
#define MAX_MESSAGE_LEN				60		/* 提示信息的长度				     */
#define MAX_MESSAGE_COUNT			16		/* 每种输入法的提示信息的个数		 */
#define MAX_ONEPAGE_RECORD			15/*20*/		/* 每页备选的最大词条数				 */

#define MAX_PINYIN_NUMBER			6       /* 最大拼音数目                      */
#define MAX_KEYS_TABLE				421		/* 中文拼音的最大个数				 */
#define MAX_PINYIN_LENGTH			28/*9*/		/* 每个拼音的最大长度                */
#define MAX_DISPLAY_LINE			3       /* 输入法最大显示行数				 */
#define MAX_DISPLAY_WIDTH			128     /* 屏幕最大宽度(点数)				 */
#define MAX_TIME_INTERVAL			600		/* 定义长按键的最大时间间隔			 */
#define FLASH_CAPACITY				1024    /* 保存到Flash的数据的大小           */
#define FLASH_CONFIGSIZE			24      /* Flash的数据中设置参数的大小       */
#define MAX_SYMBOL_GROUP_COUNT		21	    /* 一个程序中支持的最大符号组数目	 */
#define MAX_SYMBOL_COUNT			512		/* 一个符号组内最大的符号个数        */
#define MAX_KEYS_ARRANGE_COUNT	    4	    /* 一个程序中支持的最大键盘分布数目	 */ 
#define MAX_FIX_NUMBER			    40	    /* 前后缀的最大数目					 */
#define MAX_FIX_CHANGERULE_KIND		30		/* 前后缀的变化的最大规则总数		 */
#define MAX_SEGMENT_COUNT			100		/* 数据最大分段数					 */
#define MAX_LANGUAGESYMBOL			14		/* 最大语种符号组数					 */
#define MAX_CHINESE_WORD_LEN		8		/* 中文单词的最大长度				 */
#define PRODUCTTYPE_IME						//输入法是否提供版本获取功能

/*************************** 定义外部边界常数 ************************************/


/***************************** 定义错误代码 **************************************/
#define RESULT_SUCCESS				0	/* 调用成功返回标记						 */
#define RESULT_FAILURE				255	/* 调用失败返回标记						 */
#define ERROR_INPUT_KEYS			2	/* 输入键非法							 */
#define ERROR_TURN_PAGE_TYPE		3	/* 翻页方式非法							 */
#define ERROR_INPUT_KEYS_EMPTY		4	/* 键码数为0							 */
#define ERROR_INPUT_KEYS_OVERLONG	5	/* 键码数超长							 */
#define ERROR_TURN_PAGE_NEXT_OVER	6	/* 翻页已到最后							 */
#define ERROR_TURN_PAGE_PREV_TOP	7	/* 翻页已到最前                          */
#define ERROR_FORE_SEARCH_NOT_MATCH	8	/* 外文搜索不匹配					     */
#define ERROR_INVALIDIMETYPE        9   /* 错误的输入法类型						 */
#define ERROR_FLASH_INSUFFICIENCY	10	/* flash空间不足						 */
#define ERROR_KEY_LAYOUT_OVERFLOW	11	/* 外文键位号错误						 */
#define ERROR_TURN_NEXT_MAX			12	/* 外文翻页已经到了最大的页数			 */
#define ERROR_FLASH_POINT_EMPTY		13	/* flash的指针为空						 */
#define ERROR_FOCUS_IDX				14	/* 外文输入法当前焦点过了单词长度		 */
#define ERROR_FOCUS_ZERO			15  /* 外文输入法当前焦点为0				 */
#define ERROR_LETTER_NOT_EXIST		16	/* 搜索字母函数传入字母不存在			 */
#define ERROR_GETSYMBOL_INCODE		17	/* 外文中取字母内码错误					 */
#define ERROR_ADDFIX_RANGER			18	/* 外文中加后缀时总长超长				 */
#define ERROR_DATAFILE				19  /*	错误的数据文件						 */
#define ERROR_NO_CHANGEID			20  /* 没有找到变形号						 */
#define ERROR_TURN_FOCUS_PREV_TOP	21	/* 键码的焦点已经移到首位置				 */
#define ERROR_TURN_FOCUS_NEXT_OVER	22	/* 键码的焦点已经移到尾位置				 */
#define ERROR_IMETYPE_NOT_INLIST	23	/* 输入法列表不存在该输入法				 */
#define ERROR_NO_SPACE				24  /* 没有开出合适的空间*/

/****************************** 定义错误代码 *************************************/

//词库占用空间大小，不可随意修改
#define MMI_SOGOU_USER_DATABASE_PYUSER_SIZE					20480  //拼音输入法用户词空间
#define MMI_SOGOU_USER_DATABASE_PYUSERSYS_SIZE				18432  //输入法系统词空间
#define MMI_SOGOU_USER_DATABASE_STROKE_SIZE					26624	//笔画输入法用户词空间
#define MMI_SOGOU_USER_DATABASE_FT_STROKE_SIZE				26624	//笔画输入法用户词空间
#define MMI_SOGOU_USER_DATABASE_ZHUYIN_SIZE					20480	//注音输入法用户词空间
#define MMI_SOGOU_USER_DATABASE_ZHUYINSYS_SIZE				18432
//以下的文件的路径，不可随意修改
#define	MMI_SOGOU_USER_DATABASE_PATH					L"c:\\@sogou"	//自造词所存放的文件夹
#define MMI_SOGOU_USER_DATABASE_PYUSER_FILE 			L"c:\\@sogou\\sgim_usr.bin"	//拼音输入法用户词保存的文件
#define MMI_SOGOU_USER_DATABASE_PYUSERSYS_FILE			L"c:\\@sogou\\sgim_usrs.bin"	//系统词保存的文件
#define MMI_SOGOU_USER_DATABASE_STROKE_FILE				L"c:\\@sogou\\sgim_bhusr.bin"	//笔画输入法保存的文件
#define MMI_SOGOU_USER_DATABASE_FT_STROKE_FILE			L"c:\\@sogou\\sgim_fbhusr.bin"	//繁体笔画输入法保存的文件

#define MMI_SOGOU_USER_DATABASE_ZYUSER_FILE 			L"c:\\@sogou\\sgim_zy_usr.bin"	//拼音输入法用户词保存的文件
#define MMI_SOGOU_USER_DATABASE_ZYUSERSYS_FILE			L"c:\\@sogou\\sgim_zy_sys.bin"	//系统词保存的文件

#define MMI_SOGOU_OUTLIBSIZE 1500*32

#define  MMI_FILE "c:\\@sogou\\s.txt" //将调用内核接口传入函数写入该文件

//模糊音设置 0x00000000表示不支持模糊音，0x00000fff表示支持所有模糊音
//如果要使用部分模糊音，请将需要模糊的音进行或（|）运算。
#define SG_FUZZY_NO				(0x00000000)
#define SG_FUZZY_ZH_AND_Z		(0x00000001)	//表示zh和z模糊
#define SG_FUZZY_CH_AND_C		(0x00000002)	//表示ch和c，下面依次类推，名字中_AND_前和后的音进行模糊
#define SG_FUZZY_SH_AND_S		(0x00000004)
#define SG_FUZZY_N_AND_L		(0x00000008)
#define SG_FUZZY_H_AND_F		(0x00000010)
#define SG_FUZZY_R_AND_L		(0x00000020)
#define SG_FUZZY_K_AND_G		(0x00000040)
#define SG_FUZZY_ANG_AND_AN		(0x00000080)
#define SG_FUZZY_ENG_AND_EN		(0x00000100)
#define SG_FUZZY_ING_AND_IN		(0x00000200)
#define SG_FUZZY_IANG_AND_IAN	(0x00000400)
#define SG_FUZZY_UANG_AND_UAN	(0x00000800)
#define SG_FUZZY_AND_ALL		(0x00000FFF)






/***************************** 定义输出结构 **************************************/
typedef struct WD_imeResult_t
{
	WD_UINT16 inputKeys[MAX_KEYS_LEN+3];   
	/* 原始键码序列			                                                     */  
	WD_UINT16 outputKeys[MAX_KEYS_LEN*MAX_CHINESE_WORD_LEN+1];   
	/* 输出键码序列：可用于显示已输入的键码或相对应的拼音或注音（中文）
	该键码是已被分隔的（对于中文词输入），和已替换成拼音或注音的(对已确认的音)*/
	WD_UINT8 idxFocus;
	/* 当前的焦点。
	中文：当前编辑的键码段(第几个汉字)；外语：当前编辑的是第几个字母  		 */
	WD_UINT8 curPage;
	/*当前的页数(从0开始)，可用于判断是否已经翻到最后一页，是否显示下翻页键头    */	
	WD_UINT16 letterSelecting[MAX_KEY_LETTERCOUNT][MAX_PINYIN_LENGTH+1]; 
	/* 中文： 
				对于拼音和注音输入法当前焦点字的键码所对应的所有的拼音或注音组合；
				对于数拼输入法，在第一键时表示所有备选声母；
	外文：当前焦点键码所对应的所有字母；              						 */
	WD_UINT8 idxLetterSelecting;	       
	/* 当前备选音或字母的序号,从0开始   										 */
	WD_UINT16 selecting[MAX_ONEPAGE_RECORD][MAX_KEYS_LEN+3];  
	/* 备选项：最多有MAX_ONEPAGE_RECORD项。
	中文：存放已查出的词或字，每个字词一条；
	外文：符合已输入键码的单词，存放Unicode。		    					 */
	WD_UINT8 idxSelecting;                 
	/* 当前备选项序号，,从0开始								             		 */
	WD_UINT16 output[MAX_KEYS_LEN*MAX_CHINESE_WORD_LEN+1];	   
	/* 已确认字词，返回给调用函数											     */
	WD_UINT16 returnKey;	                   
	/* 返回键码：输入法不处理的按键被直接传回，或对于非法键，传出错误报警		 */
	WD_UINT8 imeType;		               
	/* 当前输入法的内码: 按照输入法定义											 */
	WD_UINT16 imeString[4];	               
	/* 输入法种类提示字符串，中文用GB码或者unicode码，外文用Unicode码。 		 */
	WD_UINT16 message[MAX_DISPLAY_LINE][MAX_MESSAGE_LEN];  
	/* 提示信息：需显示的提示信息；中文用GB码，外文用Unicode。
	此版本不提供提示信息功能													 */
	WD_UINT8 resultEmpty;
	/*此版本不可用；    														 */
	WD_UINT8 imeStatus;
	/*输入法当前的状态															 */
	WD_UINT8 preStatus;
	/*输入法前一的状态															 */

	WD_UINT8 capLock;
	/*表示大小写状态0为小写状态，1为首字母大写，2为全大写状态*/

	WD_UINT8 selectingCount;	//为每次搜索到的结果数

} WD_imeResult; 
/***************************** 定义输出结构 *************************************/


/*************************** 定义汉字属性结构 ***********************************/
typedef struct WD_hzCharProp_t
{	
	WD_UINT16 GBK,UniCode;				/* 各种编码的汉字内码（UC,GB）          */
	WD_UINT8  pinyin[4][8];            /* 拼音字母，最多支持四个多音字          */
	WD_UINT16 zhuyin[4][3];            /* 注音符号，最多支持四个多音字			*/
   WD_UINT8  tone[5];                 /* 汉字的音调，1~5，其中5代表轻声，
   此版本暂时不可用						*/
   WD_UINT8  bihua[32];               /* 汉字的笔划，最多支持32笔				*/
   WD_UINT8  wordClass;               /* 汉字的类型，3为姓名。0为常用			*/
} WD_hzCharProp;
/*************************** 定义汉字属性结构 ***********************************/


/*************************** 定义搜索输入结构 ***********************************/
/*对外公开的用于传入搜索输入参数的结构,此版本不可用								*/
typedef struct WD_searchInfo_t
{
	WD_UINT8	searchKeys[MAX_KEYS_LEN+4]; /* 原始键码序列						 */
	WD_UINT8	idxFocus;					/* 焦点的位置						 */
	WD_UINT8	imeType;					/* 输入法类型						 */
	WD_UINT16	legendChar[4];				/* 联想字首字						 */
	WD_UINT8  wordTone[4];                /* 音调								 */
	WD_SINT8	turnPageType;		    	/* 翻页类型，0,初始；1,后翻；-1,前翻 */
	WD_UINT8	lastDisplayed;				/* 上一次显示的词条数                */
	WD_UINT8	fullMatch;					/* 是否全匹配搜索                    */
	WD_UINT8	wordClass;					/* 字的类型或词性，3为姓名，0为常用  */
	WD_UINT8  codeType;					/* 编码类型 0:缺省 1:GB 2:BIG        */
	WD_UINT8	historyPerPage;	
	WD_UINT8	fixSearchType;
	WD_UINT8	faceSearchType;
	WD_UINT8	ioMode;
	
} WD_searchInfo;
/*搜索引擎输入结构																 */
/*************************** 定义搜索输入结构 ************************************/

	typedef struct symbolGroup_
	{
		WD_UINT16	groupName[4];					/* 符号组名，UniCode	 */
		WD_UINT16	element[MAX_SYMBOL_COUNT];		/* 组内符号，UniCode	 */
		WD_UINT8	elementlen;						/* 单个符号长度 UniCode  */
	} WD_symbolGroup,*pWD_symbolGroup;

typedef struct ssss_
{
	WD_UINT16	llll[4];	
	WD_UINT16	mmmm[MAX_SYMBOL_COUNT];
	WD_UINT8	nnnn;	
} WD_ssss;

// 语种数据表结构
typedef struct WD_abcdefg_t
{		          
	WD_UINT8					  imeType;
	WD_UINT16					  imeString[4];
	const WD_UINT16				  *hhh;
	const WD_ssss				  *iii;
	const WD_UINT8*					  zzz;
	const lan_ddd*					landdd;
	lan_keymap_Info_t*			cur_language;
} WD_abcdefg;



/***************************** 定义程序设置 **************************************/


/***************************** 定义函数调用 **************************************/
WD_UINT8 IME_Initialize(WD_UINT8* pImeTypeList,  WD_UINT8 defaultIme,
						WD_UINT8* pFlashData,WD_imeResult*	pResult);

						/*	函数说明: 初始化函数，在进入输入法时调用。主要用来得到flash中的数据，生成输入
					   法列表，设置相关参数，并按照设置或输入参数的要求初始化默认的输入法。
					   
						 调用参数：fd
						 WD_UINT8* pImeTypeList
						 本输入法程序所包含的所有输入法的排序列表，以上述输入法种类定义在文件中
						 该输入法类型值列表的顺序决定输入法切换时的顺序。
						 WD_UINT8 defaultIme：
						 首选输入法，即进入输入法后的缺省输入法；
						 WD_UINT8* pFlashData：
						 用于存放从flash中提取的设置和自造词数据的指针
						 WD_IMEResult* pResult：为指向输出结构的指针；                
						 
						   返回值：
WD_UINT8：成功-0，失败-错误编号。									       */

WD_UINT8 WD_SwitchIme(WD_UINT8 imeType);
/*	函数说明: 输入法切换函数。

		调用参数：
		WD_UINT8 imeType：
		要切换的输入法代码
		
		  返回值：
WD_UINT8：成功-0，失败-错误编号。											*/

	WD_UINT8 WD_OnKey(WD_UINT16 key, WD_UINT8 wordClass,
				      WD_UINT8 lastDisplayed, WD_imeResult* pResult);
	/*	函数说明: 键处理函数，是在启动了输入法后每次发生按键事件后调用的。这是输入法的
			      主控程序，所有按键的处理，字词的搜索，确认输出等都由键处理函数执行的。
		
		调用参数：
		WD_UINT8 key：
			传入的键值，其键值应当与WD_Def.h中定义的键值一样。包括普通按键和长按键等。
		WD_UINT8 last_displayed：
			当前屏幕能显示的词条个数。每次在输入法搜索后，会给出最多MAX_ONEPAGE_RECORD
			个词条或单词。由于手机屏幕的限制，所有的词条不一定能够全部被显示，因而需要从
			上一次已显示过的下一个词条出重新给出搜到的字词。所以需要提供能显示的词条数目。
			此数不累加。
		WD_UINT8 wordClass
			//当前版本无用，当前屏幕能显示的备选音的个数。每次在输入法搜索后，会给出最多MAX_ONEPAGE_RECORD
			个被选音。由于手机屏幕的限制，所有的被选音不一定能够全部被显示。
		WD_IMEResult* Result：
			按头文件中定义的输出结构的指针。同初始化函数。
		
		返回值：
		WD_UINT8：成功-0，失败-错误编号。											  */

void Sogou_Save_Updata_To_File(void);
/*
	函数功能：保存自造词到文件
	参数说明：无
	返回值：本函数无返回值。
*/




void SG_Quit(void);
/*	
	函数说明：释放掉内部临时空间

	参数说明：无
	返回值：本函数无返回值。
*/

//#ifdef WDI_CHINESE

void SG_SetFuzzy(WD_UINT32 type); 
/*
	函数说明：用来专门对模糊音设置

	参数说明：type 将要设置的模糊音，容易模糊的音需要设置哪几个
			例如：zh 和 z需要设置，就赋值type=SG_FUZZY_ZH_AND_Z；
			如果 zh和z，ch和c，都需要设置，
			那么，type = SG_FUZZY_ZH_AND_Z | SG_FUZZY_CH_AND_C;
			这些宏定义在此文件中部，需要设置哪些模糊音，就把哪些模糊音 ‘或’（|）进来。

	返回值：无
*/



WD_UINT8 WD_GetPropertyByHz(WD_UINT16 hzChar,WD_UINT8 codeType,WD_hzCharProp *pHzCharProp);
/*	函数说明: 是专门用来查询汉字属性的函数，包括汉字内码（GBK，Unicode），
拼音，注音，音调，笔划和字词类别及词性等。
参数说明：
WD_UINT16 hzChar：
传入的汉字，可能是GBK/UniCode/
WD_UINT8 codeType：
高四位为简繁体，0为简体，1为繁体；低四位为汉字内码类型；0、2分别对应GBK、UNICODE；
WD_hzCharProp* hzCharProp：
汉字属性的输出结构指针。具体定义如前面数据结构WD_hzCharProp的定义

		返回值：
		WD_UINT8：成功-0，失败-错误编号。 
*/
//得到汉字属性

WD_UINT8 WD_GetAssociationalCandidate(WD_UINT16 *ch, WD_UINT8 codeType, WD_UINT16* can, WD_UINT8 count);
/*  函数说明:根据汉字的码得到联想字,此版本只能支持Unicode码和GBK码

		参数说明:
		WD_UINT16 ch:
		汉字内码；
		WD_UINT8 codeType:：
		高四位为简繁体，0为简体，1为繁体；低四位为汉字内码类型；0、1、2、3分别对应GBK、BIG5、UNICODE、QUWEI；
		WD_UINT16* can：
		联想字存储buf地址指针
		WD_UINT8 count：
		希望得到联想字个数(最大不能超过255) 
		返回值：
		实际得到的联想字个数				
*/
//#endif


WD_UINT8 WD_SetVariable(WD_UINT8 index,WD_UINT8 value,WD_imeResult* pResult);
/*  
函数说明:设置WD_imeResult输出结构中的变量的函数。拼音输入法可以设置备选音和备选字
			其他输入法只能设置备选字的焦点。

		参数说明:
		WD_UINT8 index: 被修改变量的序号，1，则修改备选字idxSelecting；2，则修改备选音idxLetterSelecting
		WD_UINT8 value: 设置的值
		WD_imeResult* pResult:
		按头文件中定义的输出结构的指针。同初始化函数。
		返回值：
		0表示成功，其他失败;设置成功后Result相应变量被改变				
		
*/

WD_UINT8 WD_SwitchForeignCapslock(WD_UINT8 capsLock);
/* 
	函数功能：切换外文输入法大小写状态

	函数说明 ：当某些外文无大小写时，认为是已经切换成功，只不过是大小写字母相同。

	调用参数： 
	参数，0为小写状态，1为首字母大写，2为全大写状态(智能外文)
		
	返回值：
	成功返回0
*/

///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
///以下函数为外部函数，需要平台实现，输入法内部使用////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////


extern 	WD_UINT32 SG_openfile(WD_UINT16* fileName);
/*	函数说明: 根据传入路径打开文件

		调用参数：
		WD_UINT16* fileName
		该参数为传入文件路径		

		返回值:
		文件句柄
*/

extern	WD_UINT8  SG_readfile(WD_UINT32 handle, WD_UINT8* buf, WD_UINT32 size);
/*	函数说明: 根据传入的文件句柄读取指定大小的数据

		调用参数：
		WD_UINT32 handle
		该参数为传入文件句柄		
		WD_UINT8* buf
		读取数据存放的buf
		WD_UINT32 size
		读取数据的size

		返回值:
		0 --失败 1--成功
*/
extern	WD_UINT8  SG_writefile(WD_UINT32 handle, WD_UINT8* buf, WD_UINT32 size);
/*	函数说明: 根据传入的文件句柄写入指定大小的数据

		调用参数：
		WD_UINT32 handle
		该参数为传入文件句柄		
		WD_UINT8* buf
		写入的数据
		WD_UINT32 size
		写入数据的size

		返回值:
		0 --失败 1--成功
*/

extern	WD_UINT8  SG_closefile(WD_UINT32 handle);
/*	函数说明: 根据传入文件句柄关闭文件

		调用参数：
		WD_UINT32 handle
		该参数为传入文件句柄		

		返回值:
		0 --失败 1--成功
*/


extern WD_UINT32 SG_IME_MALLOC(WD_UINT8** flashBuf, WD_UINT32 bufSize);
/*
函数功能：将申请bufSize大小的空间头指针赋值给*flashBuf

  参数：WD_UINT8** flashBuf 指向一块空间的头部
  参数：WD_UINT32 bufSize 指向空间大小

  返回值为空间大小
*/

extern WD_UINT32 SG_IME_FREE(WD_UINT8** flashBuf, WD_UINT32* bufSize);
/*
函数功能：清空*flashBuf所指向的bufSize大小的空间，同时将bufSize置为0

  参数：WD_UINT8** flashBuf 指向一块空间的头部
  参数：WD_UINT32* bufSize 指向空间大小

  无返回值
*/

#endif

