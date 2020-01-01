#ifndef _IINPUT_H_
#define _IINPUT_H_

#ifdef __cplusplus
extern "C" {
#endif

#define IID_INPUT_INT32 {0x10e3e6c2, 0xfca64e96, 0x9be3587b, 0xf7012ddd}
#define IID_INPUT_NAME "IID_INPUT"

typedef s32 IInput_Ret;
#define IINPUT_RET_SUCCESS			0
#define IINPUT_RET_FAILED			1
#define IINPUT_RET_NOT_IMPLEMENTED	4

enum _KeyAction
{
	KEY_ACT_PRESS = 1,
	KEY_ACT_RELEASE = 2
};
typedef u8 KeyAction;

enum _KeyCode
{
	KEY_CODE_OK = 1,
	KEY_CODE_ACTION,
	KEY_CODE_UP,
	KEY_CODE_DOWN,
	KEY_CODE_LEFT,
	KEY_CODE_RIGHT,
	KEY_CODE_SIDE_UP,
	KEY_CODE_SIDE_DN,
	KEY_CODE_SKLEFT,
	KEY_CODE_SKRIGHT,
	KEY_CODE_ONOFF,
	KEY_CODE_CLR,
	KEY_CODE_CLEAR,
	KEY_CODE_SEND,
	KEY_CODE_SEND2,
	KEY_CODE_PHB,
	KEY_CODE_MSG,
	KEY_CODE_MAIL,
	KEY_CODE_FSTDL1,
	KEY_CODE_FSTDL2,
	KEY_CODE_FSTDL3,
	KEY_CODE_FSTDL4,
	KEY_CODE_REDIAL,
	KEY_CODE_HOOK,
	KEY_CODE_FLAPON,
	KEY_CODE_FLAPOFF,
	KEY_CODE_MEN,
	KEY_CODE_HEADSET,
	KEY_CODE_CAMERA,
	KEY_CODE_MP3,
	KEY_CODE_END,
	KEY_CODE_HOME,
	KEY_CODE_KGD,
	KEY_CODE_POWERMODE,
	/* ===== Start of Qwerty keypad ===== */
	KEY_CODE_ENTER,  
	KEY_CODE_SHIFT,
	KEY_CODE_SHIFTLEFT,
	KEY_CODE_SHIFTRIGHT,
	KEY_CODE_Alt, 
	KEY_CODE_SPACE, 
	KEY_CODE_SYM,
	KEY_CODE_NEXT,
	KEY_CODE_EXCLAM,            //! ¾ªÌ¾ºÅ
	KEY_CODE_DOUBLEQUOTE,       //¡°¡±ÒýºÅ
	KEY_CODE_HASH,              //#
	KEY_CODE_DOLLAR,            //$
	KEY_CODE_PERCENT,           //%°Ù·ÖºÅ
	KEY_CODE_REF,               //&ÒýÓÃ
	KEY_CODE_APOSTROPHE,        //`Ê¡ÂÔºÅ
	KEY_CODE_OPENPAREN,         //(×óÔ²À¨ºÅ
	KEY_CODE_CLOSEPAREN,        //)ÓÒÔ²À¨ºÅ
	KEY_CODE_STAR,              //*
	KEY_CODE_PLUS,              //+
	KEY_CODE_COMMA,             //,¶ººÅ
	KEY_CODE_MINUS,             //-
	KEY_CODE_DOT,               //.Ô²µã
	KEY_CODE_SLASH,             //  /Ð±Ïß£¬Ð±¸Ü£¬³ýºÅ
	KEY_CODE_0,
	KEY_CODE_1,
	KEY_CODE_2,
	KEY_CODE_3,
	KEY_CODE_4,
	KEY_CODE_5,
	KEY_CODE_6,
	KEY_CODE_7,
	KEY_CODE_8,
	KEY_CODE_9,
	KEY_CODE_COLON,             //:Ã°ºÅ
	KEY_CODE_SEMICOLON,         //;·ÖºÅ
	KEY_CODE_LESSTHAN,          //£¼Ð¡ÓÚºÅ
	KEY_CODE_EQUAL,             //£½µÈÓÚ
	KEY_CODE_MORETHAN,          //£¾´óÓÚºÅ
	KEY_CODE_QUESTION,          //?ÎÊºÅ
	KEY_CODE_AT,                //@ 
	KEY_CODE_OPENBRACKET,       //[×ó·½À¨ºÅ
	KEY_CODE_BACKSLASH,         //  \¡¡·´Ð±Ïß
	KEY_CODE_CLOSEBRACKET,      //]ÓÒ·½À¨ºÅ
	KEY_CODE_CARET,             //^ ²åÈë·ûºÅ
	KEY_CODE_DASH,              //¡ªÆÆÕÛºÅ
	KEY_CODE_SINGLEQUOTE,       //¡®¡¯µ¥ÒýºÅ
	KEY_CODE_A,
	KEY_CODE_B,
	KEY_CODE_C,
	KEY_CODE_D,
	KEY_CODE_E,
	KEY_CODE_F,	
	KEY_CODE_G,
	KEY_CODE_H,
	KEY_CODE_I,
	KEY_CODE_J,
	KEY_CODE_K,
	KEY_CODE_L,
	KEY_CODE_M,
	KEY_CODE_N,
	KEY_CODE_O,
	KEY_CODE_P,
	KEY_CODE_Q,
	KEY_CODE_R,
	KEY_CODE_S,
	KEY_CODE_T,
	KEY_CODE_U,
	KEY_CODE_V,
	KEY_CODE_W,
	KEY_CODE_X,
	KEY_CODE_Y,
	KEY_CODE_Z,
	KEY_CODE_OPENBRACE,         //{×ó»¨À¨ºÅ
	KEY_CODE_VERTICALBAR,       //|ÊúÏß
	KEY_CODE_CLOSEBRACE,        //}ÓÒ»¨À¨ºÅ
	KEY_CODE_TILDE,             //~²¨ÀËÏß
	KEY_CODE_DEL,               //delete
	KEY_CODE_VOLUME,            //ÉùÒô     
	///////////////////////////////////
	/* ===== End of Qwerty keypad ===== */
	KEY_CODE_SAME = 0xFE,
	KEY_CODE_DUMMY = 0xFF
};
typedef u8 KeyCode;

enum _TSEvent
{
	TS_EVENT_PRESS,
	TS_EVENT_RELEASE,
	TS_EVENT_MOVE,
	TS_EVENT_LONGPRESS,
	TS_EVENT_CLICK
};
typedef s8 TSEvent;

typedef void (*KeyPadIndicationCallback)(KeyAction keyAction, KeyCode keyCode);
typedef void (*TouchScrIndicationCallback)(TSEvent tsEvent, u32 x, u32 y);


typedef struct _IInput
{
	IInput_Ret (*KeyPadRegister)(KeyPadIndicationCallback pKeyIndicationCB);
	IInput_Ret (*KeyPadUnRegister)(void);
	IInput_Ret (*KeyPadEnablePressTone)(void);
	IInput_Ret (*KeyPadDisablePressTone)(void);
	IInput_Ret (*TouchScrRegister)(TouchScrIndicationCallback pTSIndicationCB);
	IInput_Ret (*TouchScrUnRegister)(void);
	IInput_Ret (*TouchScrEnable)(void);
	IInput_Ret (*TouchScrDisable)(void);
} IInput;




#ifdef  __cplusplus
}
#endif
#endif //_IINPUT_H_
