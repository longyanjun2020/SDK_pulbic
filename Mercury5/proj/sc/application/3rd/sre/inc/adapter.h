#ifndef _ADAPTER_H_
#define _ADAPTER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ven_kpd.h"
#include "iinput.h"

#define OS_FEATURE_VERSION			   1 //平台版本
#define OS_FEATURE_NAME                2 //平台名称
#define OS_FEATURE_KEYBOARD_STYLE      3 //键盘类型
#define OS_FEATURE_TOUCH_SCREEN_STYLE  4 //触摸屏类型
#define OS_FEATURE_IS_KEY_EXIST        5 //查询key是否存在
#define OS_FEATURE_IS_KEY_SHARED       6 //查询key是否共用，若有共用，则返回另外的共用键

enum
{
	STYLE_BOX_KEYBOARD = 1,     //常规的0-9键盘
	QWERTY_KEYBOARD,            //全键盘
	SPECIAL_FUNCTION_KEYBOARD   //特殊键
};
typedef u8 KeyBoardStyle;

enum
{
	NO_TOUCH_SCREEN = 1,       //不支持触摸屏
	RESISTIVE_TOUCH_SCREEN,    //电阻触摸屏
	CAPACITIVE_TOUCH_SCREEN    //电容触摸屏
};
typedef u8 TouchScreenStyle;

typedef struct  
{
	KeyCode sharedkey;         //查询的按键
	s32     sharedkeynum;      //共享的个数
	KeyCode key[5];      //哪些键共享一个物理键
}SharedKey;

typedef struct
{ 
	KeyCode  keyCode;
	ven_kpd_key_code_t   venkey;	
}KeyTable;

ven_app_id_t GetSreAppIDFromTable(void);

KeyCode  KeyPadIndication(ven_kpd_key_code_t venkey);
#ifdef  __cplusplus
}
#endif
#endif //_ADAPTER_H_

