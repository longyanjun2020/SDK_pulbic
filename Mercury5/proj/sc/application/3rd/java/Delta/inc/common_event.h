#ifndef COMMON_EVENT_H
#define COMMON_EVENT_H

#define EVENT_KEY_PRESSED		-1
#define EVENT_KEY_RELEASED		-2
#define EVENT_KEY_REPEATED		-3
#define EVENT_POINTER_PRESSED	-4
#define EVENT_POINTER_RELEASED	-5
#define EVENT_POINTER_DRAGGED	-6      
#define EVENT_POINTER_MOVED		-7
#define EVENT_MENU_OPENING		-8
#define EVENT_MENU_CLOSING		-9
#define EVENT_MENU_SELECTED		-10
#define EVENT_WINDOW_ACTIVATE	-11
#define EVENT_WINDOW_DEACTIVATE	-12
#define EVENT_WINDOW_OBSCURED	-13
#define EVENT_WINDOW_RESIZE		-14
#define EVENT_WINDOW_CLOSED		-15
#define EVENT_WINDOW_PAINT		-16
#define EVENT_VERTICAL_SCROLL	-17	
#define EVENT_CHARACTER			-18
#define EVENT_COMMAND			-19
#define EVENT_BACK				-20
#define EVENT_WINDOW_FOCUSIN	-21
#define EVENT_WINDOW_FOCUSOUT	-22
#define EVENT_DATE_CALENDAR_CLOSE -23
#define EVENT_TEXTFIELD_PASTE 	-24
#define EVENT_TEXTFIELD_CUT 	-25
#define EVENT_TEXTFIELD_CLEAR 	-26
#define EVENT_TEXTFIELD_UNDO 	-27
#define EVENT_APP_PAUSE			-28
#define EVENT_APP_EXIT			-29
#define EVENT_SOFT_KEY_LEFT		-30
#define EVENT_SOFT_KEY_RIGHT	-31
#define EVENT_HOTKEY			-32

/* Platform events */
#define EVENT_APPLICATION_STATE -50
#define EVENT_APPLICATION_STATUS -51
#define EVENT_AUDIO_OUTPUT -52
#define EVENT_BACKLIGHT -53
#define EVENT_BATTERY_CHARGING -54
#define EVENT_BATTERY_LEVEL -55
#define EVENT_BODY_OPEN -56
#define EVENT_DATA_NETWORK -57
#define EVENT_EXTERNAL_POWER -58
#define EVENT_SYSTEM_STATE -59
#define EVENT_VOICE_CALL -60
#define EVENT_VOICE_NETWORK -61
#define EVENT_VOICE_NETWORK_SIGNAL_LEVEL -62
#define EVENT_DATA_NETWORK_TYPE -63
#define EVENT_LCD_STATE -64
#define EVENT_TIMEZONE_CHANGE -65
#define EVENT_DEVICE_CHANGE -66

#define USER_EVENT  0x400 // Valid for win32 and qt, other platforms may need to adjust this value. 
#define EVENT_UI_RUNNABLE USER_EVENT + 1
#define EVENT_FORM_UPDATE_RUNNABLE USER_EVENT + 2
#define EVENT_CANVAS_UPDATE_RUNNABLE USER_EVENT + 3
#define EVENT_STOP USER_EVENT + 4

#define KEYCODE_UP				-1
#define KEYCODE_DOWN			-2
#define KEYCODE_LEFT			-3
#define KEYCODE_RIGHT			-4
#define KEYCODE_FIRE            -5
#define BACKSPACE_CHARACTER		-11
#define DELETE_CHARACTER		-12
#define NULL_CHARACTER			-13

#define KEY_NUM0 48
#define KEY_NUM1 49
#define KEY_NUM2 50
#define KEY_NUM3 51
#define KEY_NUM4 52
#define KEY_NUM5 53
#define KEY_NUM6 54
#define KEY_NUM7 55
#define KEY_NUM8 56
#define KEY_NUM9 57
#define KEYCODE_POUND 35 // 20080121: Changed for KEY_POUND
#define KEYCODE_STAR 42 // 20080121: Changed for KEY_START
#define KEYCODE_A 'A'
#define KEYCODE_B 'B'
#define KEYCODE_C 'C'
#define KEYCODE_D 'D'
#define KEYCODE_UP -1
#define KEYCODE_DOWN -2
#define KEYCODE_LEFT -3
#define KEYCODE_RIGHT -4
#define KEYCODE_FIRE -5
#define KEYCODE_INVALID 0 // 20080423: Changed
#define KEYCODE_TAB 9
#define KEYCODE_BACKSPACE 8
#define KEYCODE_DELETE 127
#define KEYCODE_NULL 0
#define KEYCODE_TALK -10
#define KEYCODE_UNKNOWN -11
#define KEYCODE_SOFTKEY1 -6 // 20080423: Changed
#define KEYCODE_SOFTKEY2 -7 // 20080423: Changed

//=========================================
#define KEYCHAR_A	'A'
#define KEYCHAR_B	'B'
#define KEYCHAR_C	'C'
#define KEYCHAR_D	'D'
#define KEYCHAR_E	'E'
#define KEYCHAR_F	'F'
#define KEYCHAR_G	'G'
#define KEYCHAR_H	'H'
#define KEYCHAR_I	'I'
#define KEYCHAR_J	'J'
#define KEYCHAR_K	'K'
#define KEYCHAR_L	'L'
#define KEYCHAR_M	'M'
#define KEYCHAR_N	'N'
#define KEYCHAR_O	'O'
#define KEYCHAR_P	'P'
#define KEYCHAR_Q	'Q'
#define KEYCHAR_R	'R'
#define KEYCHAR_S	'S'
#define KEYCHAR_T	'T'
#define KEYCHAR_U	'U'
#define KEYCHAR_V	'V'
#define KEYCHAR_W	'W'
#define KEYCHAR_X	'X'
#define KEYCHAR_Y	'Y'
#define KEYCHAR_Z	'Z'

#define KEYCHAR_a	'a'
#define KEYCHAR_b	'b'
#define KEYCHAR_c	'c'
#define KEYCHAR_d	'd'
#define KEYCHAR_e	'e'
#define KEYCHAR_f	'f'
#define KEYCHAR_g	'g'
#define KEYCHAR_h	'h'
#define KEYCHAR_i	'i'
#define KEYCHAR_j	'j'
#define KEYCHAR_k	'k'
#define KEYCHAR_l	'l'
#define KEYCHAR_m	'm'
#define KEYCHAR_n	'n'
#define KEYCHAR_o	'o'
#define KEYCHAR_p	'p'
#define KEYCHAR_q	'q'
#define KEYCHAR_r	'r'
#define KEYCHAR_s	's'
#define KEYCHAR_t	't'
#define KEYCHAR_u	'u'
#define KEYCHAR_v	'v'
#define KEYCHAR_w	'w'
#define KEYCHAR_x	'x'
#define KEYCHAR_y	'y'
#define KEYCHAR_z	'z'

#define KEYCHAR_PERIOD	'.'
#define KEYCHAR_COMMA	','

#define KEYCHAR_SPACE           32
#define KEYCHAR_TAB             -30
#define KEYCHAR_DEL             -31
#define KEYCHAR_ALT             -32
#define KEYCHAR_CTRL            -33
#define KEYCHAR_BACKSPACE       8
#define KEYCHAR_QWERTY_ENTER    10

#define KEYCHAR_SLASH	'/'
#define KEYCHAR_BACKSLASH	'\\'
#define KEYCHAR_DOLLAR_SIGN 	'$'
#define KEYCHAR_AT	'@'
#define KEYCHAR_PERCENT	'%'
#define KEYCHAR_CARET	'^'
#define KEYCHAR_AND	'&'
#define KEYCHAR_STAR	'*'
#define KEYCHAR_LEFT_PARENTHESIS	'('
#define KEYCHAR_RIGHT_PARENTHESIS	')'
#define KEYCHAR_PLUS	'+'
#define KEYCHAR_DESH 	'-'
#define KEYCHAR_EQUAL	'='
#define KEYCHAR_QUAOTATUON_MARK	'"'
#define KEYCHAR_PRIME 	'\''
#define KEYCHAR_TILDE	'~'
#define KEYCHAR_SCAEAMER	'!'
#define KEYCHAR_QUESTION_MARK	'?'
#define KEYCHAR_LEFT_SQUARE_BRACKET 	'['
#define KEYCHAR_RIGHT_SQUARE_BRACKET	']'
#define KEYCHAR_GRAVE_ACCENT	'`'
#define KEYCHAR_GREATER	'>'
#define KEYCHAR_LESS	'<'
#define KEYCHAR_COLON	':'
#define KEYCHAR_SEMICOLO	 ';'
#define KEYCHAR_UNDERLINE	'_'
//=========================================

// 20080507: Added
#define KEYCODE_VOL_UP -13
#define KEYCODE_VOL_DOWN -14

// 20081023: Moved from .\src\midp\common\common.h and chang jint to int
typedef struct {
	int handle;
	int type;
	int arg1;
	int arg2;
} lcdui_event;

#endif // COMMON_EVENT_H

