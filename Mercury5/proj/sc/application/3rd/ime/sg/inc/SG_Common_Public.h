#ifndef  SG_COMMON_H_
#define  SG_COMMON_H_

#define MAX_LETTER_COUNT             100//请选择所有语言中的最大值
#define MAX_LETTER_COUNT_IN_ONE_KEY  20
#define MAX_TIMES_LETTER_IN_KEYS     3

// #define DIGIT_KEYS
//#define SURETYPE_KEYS
// #define QWERT_KEYS
#define OTHER_KEYS

////////////////////语言开关////////////////////////
/////客户使用/////////////////////////
// 

#define WDVK_KEY_1				0x11 	/* 表示是用于输入键码"1"的  	 */

//////////////////语言开关结束//////////////////////////


#if defined(DIGIT_KEYS)

#define KEY_BASE 0x30
typedef enum {
	SG_KEY_0 = KEY_BASE,//短按0键
	SG_KEY_1,//短按1键
	SG_KEY_2,//短按2键
	SG_KEY_3,//短按3键
	SG_KEY_4,//短按4键
	SG_KEY_5,//短按5键
	SG_KEY_6,//短按6键
	SG_KEY_7,//短按7键
	SG_KEY_8,//短按8键
	SG_KEY_9,//短按9键
	SG_KEY_10,//短按*键
	SG_KEY_11,//短按#键
	SG_KEY_12,//短按C键
	SG_KEY_13,//短按OK键
	SG_KEY_14,//短按lsk键
	SG_KEY_15,//短按rsk键
	SG_KEY_16,//短按up键
	SG_KEY_17,//短按down键
	SG_KEY_18,//短按left键
	SG_KEY_19,//短按right键
	SG_KEY_20,//长按0键
	SG_KEY_21,//长按1键
	SG_KEY_22,//长按2键
	SG_KEY_23,//长按3键
	SG_KEY_24,//长按4键
	SG_KEY_25,//长按5键
	SG_KEY_26,//长按6键
	SG_KEY_27,//短按7键
	SG_KEY_28,//短按8键
	SG_KEY_29,//短按9键
	SG_KEY_30,//长按*键
	SG_KEY_31,//长按#键
	SG_KEY_32,//长按C键
	SG_KEY_33,//长按OK键
	SG_KEY_34,//长按LSK键
	SG_KEY_35,//长按RSK键
	SG_KEY_36,//长按UP键
	SG_KEY_37,//长按DOWN键
	SG_KEY_38,//长按RIGHT键
	SG_KEY_39,//长按LEFT键
	MAX_KEY_COUNT,//=40
} KEY_ID;//键值的ID

#elif defined(SURETYPE_KEYS)

#define KEY_BASE 0xb1
typedef enum {
	SG_KEY_0 = KEY_BASE,//qw
	SG_KEY_1,//er
	SG_KEY_2,//ty
	SG_KEY_3,
	SG_KEY_4,
	SG_KEY_5,
	SG_KEY_6,
	SG_KEY_7,
	SG_KEY_8,
	SG_KEY_9,
	SG_KEY_10,
	SG_KEY_11,
	SG_KEY_12,
	SG_KEY_13,
	SG_KEY_14,
	SG_KEY_15,
	SG_KEY_16,
	SG_KEY_17,
	SG_KEY_18,
	SG_KEY_19,
	SG_KEY_20,
	SG_KEY_21,
	SG_KEY_22,
	SG_KEY_23,
	SG_KEY_24,
	SG_KEY_25,
	MAX_KEY_COUNT,// = SG_KEY_BASE+12
} KEY_ID;//键值的ID

#elif defined(QWERT_KEYS)

#define KEY_BASE 0xb1
typedef enum {
	SG_KEY_0 = KEY_BASE,//短按a键
	SG_KEY_1,//短按b键
	SG_KEY_2,//短按c键
	SG_KEY_3,//短按d键
	SG_KEY_4,//短按e键
	SG_KEY_5,//短按f键
	SG_KEY_6,//短按g键
	SG_KEY_7,//短按h键
	SG_KEY_8,//短按i键
	SG_KEY_9,//短按j键
	SG_KEY_10,//短按k键
	SG_KEY_11,//短按l键
	SG_KEY_12,//短按m键
	SG_KEY_13,//短按n键
	SG_KEY_14,//短按o键
	SG_KEY_15,//短按p键
	SG_KEY_16,//短按q键
	SG_KEY_17,//短按r键
	SG_KEY_18,//短按s键
	SG_KEY_19,//短按t键
	SG_KEY_20,//短按u键
	SG_KEY_21,//短按v键
	SG_KEY_22,//短按w键
	SG_KEY_23,//短按x键
	SG_KEY_24,//短按y键
	SG_KEY_25,//短按z键
	SG_KEY_26,//短按切换输入法键
	SG_KEY_27,//短按分隔符键
	SG_KEY_28,//短按符号键
	SG_KEY_29,//短按C键
	SG_KEY_30,//短按OK键
	SG_KEY_31,//短按回车键
	SG_KEY_32,//短按up键
	SG_KEY_33,//短按down键
	SG_KEY_34,//短按left键
	SG_KEY_35,//短按right键
	SG_KEY_36,//短按lst键
	SG_KEY_37,//短按rst键
	SG_KEY_38,//短按大小写切换键
	SG_KEY_39,//短按功能键FN
	SG_KEY_40,//短按shift
	SG_KEY_41,//短按Alt
	SG_KEY_42,//短按ctrl
	SG_KEY_43,//长按a键
	SG_KEY_44,//长按b键
	SG_KEY_45,//长按c键
	SG_KEY_46,//	长按d键
	SG_KEY_47,//	长按e键
	SG_KEY_48,//	长按f键
	SG_KEY_49,//	长按g键
	SG_KEY_50,//	长按h键
	SG_KEY_51,//	长按i键
	SG_KEY_52,//	长按j键
	SG_KEY_53,//	长按k键
	SG_KEY_54,//	长按l键
	SG_KEY_55,//	长按m键
	SG_KEY_56,//长按n键
	SG_KEY_57,//长按o键
	SG_KEY_58,//长按p键
	SG_KEY_59,//长按q键
	SG_KEY_60,//长按r键
	SG_KEY_61,//长按s键
	SG_KEY_62,//长按t键
	SG_KEY_63,//长按u键
	SG_KEY_64,//长按v键
	SG_KEY_65,//长按w键
	SG_KEY_66,//长按x键
	SG_KEY_67,//长按y键
	SG_KEY_68,//长按z键
	SG_KEY_69,//长按切换输入法键
	SG_KEY_70,//长按分隔符键
	SG_KEY_71,//长按符号键
	SG_KEY_72,//长按C键
	SG_KEY_73,//长按OK键
	SG_KEY_74,//长按回车键
	SG_KEY_75,//长按up键
	SG_KEY_76,//长按down键
	SG_KEY_77,//长按left键
	SG_KEY_78,//长按right键
	SG_KEY_79,//长按lst键
	SG_KEY_80,//长按rst键
	SG_KEY_81,//长按大小写切换键
	SG_KEY_82,//长按功能键FN
	SG_KEY_83,//长按shift
	SG_KEY_84,//长按Alt
	SG_KEY_85,//长按ctrl
	MAX_KEY_COUNT,// = SG_KEY_BASE+86
} KEY_ID;//键值的ID

#else //OTHER_KEYS

#define KEY_BASE 0x10
typedef enum {
	SG_KEY_0 = KEY_BASE,
	SG_KEY_1,
	SG_KEY_2,
	SG_KEY_3,
	SG_KEY_4,
	SG_KEY_5,
	SG_KEY_6,
	SG_KEY_7,
	SG_KEY_8,
	SG_KEY_9,
	SG_KEY_10,//短按*键
	SG_KEY_11,//短按#键
	SG_KEY_12,//a
	SG_KEY_13,//b
	SG_KEY_14,//c
	SG_KEY_15,//d
	SG_KEY_16,//e
	SG_KEY_17,//f
	SG_KEY_18,//g
	SG_KEY_19,//h
	SG_KEY_20,//i
	SG_KEY_21,//j
	SG_KEY_22,//k
	SG_KEY_23,//l
	SG_KEY_24,//m
	SG_KEY_25,//n
	SG_KEY_26,//o
	SG_KEY_27,//p
	SG_KEY_28,//q
	SG_KEY_29,//r
	SG_KEY_30,//s
	SG_KEY_31,//t
	SG_KEY_32,//u
	SG_KEY_33,//v
	SG_KEY_34,//w
	SG_KEY_35,//x
	SG_KEY_36,//y
	SG_KEY_37,//z
	SG_KEY_38,//短按切换输入法键
	SG_KEY_39,//分隔
	SG_KEY_40,//短按符号键
	SG_KEY_41,//短按C键
	SG_KEY_42,//短按OK键
	SG_KEY_43,//短按空格
	SG_KEY_44,//短按回车键
	SG_KEY_45,//短按up键
	SG_KEY_46,//短按down键
	SG_KEY_47,//短按left键
	SG_KEY_48,//短按right键
	SG_KEY_49,//短按lst键
	SG_KEY_50,//短按rst键
	SG_KEY_51,//短按大小写切换键
	SG_KEY_52,//短按功能键FN
	SG_KEY_53,//短按shift
	SG_KEY_54,//短按Alt
	SG_KEY_55,//短按ctrl
	SG_KEY_56,//0
	SG_KEY_57,//1
	SG_KEY_58,//2
	SG_KEY_59,//3
	SG_KEY_60,//4
	SG_KEY_61,//5
	SG_KEY_62,//6
	SG_KEY_63,//7
	SG_KEY_64,//8
	SG_KEY_65,//9
	SG_KEY_66,//*
	SG_KEY_67,//#
	SG_KEY_68,//长按a键
	SG_KEY_69,//长按b键
	SG_KEY_70,//长按c键
	SG_KEY_71,//长按d键
	SG_KEY_72,//长按e键
	SG_KEY_73,//长按f键
	SG_KEY_74,//长按g键
	SG_KEY_75,//长按h键
	SG_KEY_76,//长按i键
	SG_KEY_77,//长按j键
	SG_KEY_78,//长按k键
	SG_KEY_79,//长按l键
	SG_KEY_80,//长按m键
	SG_KEY_81,//长按n键
	SG_KEY_82,//长按o
	SG_KEY_83,//长按p
	SG_KEY_84,//长按q
	SG_KEY_85,//长按r
	SG_KEY_86,//长按s
	SG_KEY_87,//长按t
	SG_KEY_88,//长按u
	SG_KEY_89,//长按v
	SG_KEY_90,//长按w
	SG_KEY_91,//长按x
	SG_KEY_92,//长按y
	SG_KEY_93,//长按z
	SG_KEY_94,//短按切换输入法键
	SG_KEY_95,//分隔
	SG_KEY_96,//短按符号键
	SG_KEY_97,//短按C键
	SG_KEY_98,//短按OK键
	SG_KEY_99,//长按空格
	SG_KEY_100,//短按回车键
	SG_KEY_101,//短按up键
	SG_KEY_102,//短按down键
	SG_KEY_103,//短按left键
	SG_KEY_104,//短按right键
	SG_KEY_105,//短按lst键
	SG_KEY_106,//短按rst键
	SG_KEY_107,//短按大小写切换键
	SG_KEY_108,//短按功能键FN
	SG_KEY_109,//短按shift
	SG_KEY_110,//短按Alt
	SG_KEY_111,//短按ctrl
	MAX_KEY_COUNT,// = SG_KEY_BASE+12
} KEY_ID;//键值的ID

#endif

typedef struct {
	WD_UINT8 isHaveUpLetter; /* 是否支持小写 */
	WD_UINT8 imeType; /* 语种的数值 */
	WD_UINT16 imeString[4]; /* 用本语言描述的语种提示*/
	WD_UINT16 letterCount;//原有基础字母个数
	WD_UINT16 letterTotal;//字母表中的字母个数
	const WD_UINT16* letterTable;//字母表
	const WD_UINT16* upLetterTable;//字母表
	WD_UINT8 keyCount;
	const WD_UINT8* KeyMap;//键盘布局
	const WD_UINT8* One2One;
	WD_UINT16* OperTable;//操作数据表
	WD_UINT16* symbol_table;//符号表
} lan_keymap_Info_t;

typedef struct lan_ddd_t
{
	WD_UINT8	aaa;
	WD_UINT32	bbb;
	WD_UINT8   jjj;
	WD_UINT32*  ccc;
	WD_UINT16*  ddd;
	WD_UINT16*  eee;
	WD_UINT8*   fff;
	WD_UINT8*   ggg;
	WD_UINT16*  hhh;
	WD_UINT8*   iii;
} lan_ddd;

#endif
