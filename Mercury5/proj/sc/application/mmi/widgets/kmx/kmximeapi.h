/***************************************************************************

Description: Input method library interface

Copyright (C) 2000-2009 Beijing Komoxo Inc.
All rights reserved.

****************************************************************************/

#ifndef KMXIMEAPI_H
#define KMXIMEAPI_H

#include "kmximmapi.h"

#ifdef __cplusplus
extern "C"{
#endif

/****************************************************************************

base configuration

****************************************************************************/

/* maximal languages count in a phone */
#define KMX_MAX_LANG_PHONE 100

/* user defined word length */
#define KMX_USER_WORD_LEN	       (64 * 1024)

#define KMX_IME_TIMER_PERIOD       100
#define KMX_USER_DATA_BLOCK_SIZE   1024
#define KMX_IME_MAX_NUM            20


/****************************************************************************

base data type and definition

****************************************************************************/

#ifndef KMX_BOOL
#define KMX_BOOL    unsigned int
#endif

#ifndef KMX_WCHAR
#define KMX_WCHAR   unsigned short
#endif

#define KMX_CASE_LOWER    0
#define KMX_CASE_UPPER    1
#define KMX_CASE_INITIAL  2

#define KMX_SCREEN_QVGA      0
#define KMX_SCREEN_240_320   KMX_SCREEN_QVGA
#define KMX_SCREEN_HVGA      1
#define KMX_SCREEN_320_480   KMX_SCREEN_HVGA
#define KMX_SCREEN_VGA       2
#define KMX_SCREEN_480_640   KMX_SCREEN_VGA
#define KMX_SCREEN_240_400   3
#define KMX_SCREEN_QCIF      4
#define KMX_SCREEN_176_220   KMX_SCREEN_QCIF
#define KMX_SCREEN_QQVGA      5
#define KMX_SCREEN_128_160   KMX_SCREEN_QQVGA
#define KMX_SCREEN_WVGA      6
#define KMX_SCREEN_480_800   KMX_SCREEN_WVGA

enum KMX_SCREEN_MODE {
    SCREEN_PORTRAIT,
    SCREEN_LANDSCAPE,
};

int kmx_ime_get_current_screen_width(void);

enum KMX_KEYPAD_EVENT {
    KMX_TOUCH_DOWN,
    KMX_TOUCH_UP,
    KMX_TOUCH_MOVE,
    KMX_CHANGE_INPUTMODE,
    KMX_KEY_DOWN,
    KMX_KEY_UP,
    KMX_SCREEN_SWITCH,  /* switch between portrait and landscape */
};
enum KMX_KEYPAD_EVENT_TYPE {
    KMX_KEY_PRESS,
    KMX_KEY_RELEASE,
    KMX_KEY_LONGPRESS,
    KMX_KEY_REPEAT,
};
typedef struct
{
    short x;
    short y;
} KMX_POINT;

#ifndef KMX_COLOR
#define KMX_COLOR   unsigned int
#endif

#ifndef KMX_COLOR_RED
#define KMX_COLOR_RED(color)    ((unsigned char)(color))
#endif

#ifndef KMX_COLOR_GREEN
#define KMX_COLOR_GREEN(color)  ((unsigned char)((color) >> 8))
#endif

#ifndef KMX_COLOR_BLUE
#define KMX_COLOR_BLUE(color)   ((unsigned char)((color) >> 16))
#endif

typedef struct
{
	int     input_mode;
	int		input_method;
	int		language;
	int		ui_language;
	void**  primary_database_ptr;
	void**  secondary_database_ptr;
	int		user_data_start;
	int		user_data_size;
} KMX_INPUT_MODE_INFO;

typedef enum
{
    KMXIME_SOFTKEYBOARD_DIGIT,
    KMXIME_SOFTKEYBOARD_QWERTY
}KMXIME_SOFTKEYBOARD_TYPE;

/****************************************************************************

KeyCode ID constants.

****************************************************************************/
#define KMX_KEYCODE_0   '0'
#define KMX_KEYCODE_1   '1'
#define KMX_KEYCODE_2   '2'
#define KMX_KEYCODE_3   '3'
#define KMX_KEYCODE_4   '4'
#define KMX_KEYCODE_5   '5'
#define KMX_KEYCODE_6   '6'
#define KMX_KEYCODE_7   '7'
#define KMX_KEYCODE_8   '8'
#define KMX_KEYCODE_9   '9'

/* special key codes */
#define KMX_KEYCODE_LEFT_SOFT   1
#define KMX_KEYCODE_MID_SOFT    2
#define KMX_KEYCODE_RIGHT_SOFT  3

#define KMX_KEYCODE_LEFT        4
#define KMX_KEYCODE_RIGHT       5
#define KMX_KEYCODE_UP          6
#define KMX_KEYCODE_DOWN        7
#define KMX_KEYCODE_CENTER      8

#define KMX_KEYCODE_STAR        9
#define KMX_KEYCODE_POUND       10
#define KMX_KEYCODE_DEL         11
#define KMX_KEYCODE_ENTER       12

/* these three key codes must corresponding to ime engine */
#define KMX_KEYCODE_IME         13
#define KMX_KEYCODE_SYM         14
#define KMX_KEYCODE_ALT         15

/*Resolved right soft key cancel(delete) and Keyboard right key cancel(delete) problem for mstar*/
#define KMX_KEYCODE_DELETE		20
#define KMX_KEYCODE_CANCEL		21

#define KMX_KEYCODE_QWERTY_MASK	0x40000000
#define KMX_KEYCODE_SHIFT_MASK	0x20000000


/****************************************************************************

UI content

****************************************************************************/


/****************************************************************************

callback

****************************************************************************/

/* event when ime ui dimension changed */
typedef void (*KMX_CALLBACK_ON_KEYPAD_SIZE)(void);

/* event when ime ui should redraw */
typedef void (*KMX_CALLBACK_ON_KEYPAD_DIRTY)(void);

/* measure a text
   s: text to be measured
   len: length of the text, if -1, the text is ended with zero
   font_size: font size to render the text
   width, height: for measure result, if NULL, don't return the value (ex. if height==NULL, don't calc height)
*/
typedef void (*KMX_CALLBACK_MEASURE)(const KMX_WCHAR* s, int len, int font_size, int* width, int* height);

/* set the popup window type and position */
typedef void (*KMX_CALLBACK_POPUP_TYPE_POS)(int type, int x, int y);

/* show popup for simple echo button
text: text on the button to be echo, may be NULL
length:   len of the text
fontSize: font size to render the text
color:    color to render the text
imgId: image id of the button to be echo
x, y: anchor point(left/top)
w, h: image width/height
echoStyle: popup window type
*/
typedef void (*KMX_CALLBACK_ECHO)(const KMX_WCHAR* text, int length, int color,  int imgId,
                                  int x, int y, int w, int h, int echoStyle);

/* show/hide popup window
   bShow: 0 hide, 1 show
*/
typedef void (*KMX_CALLBACK_SHOW_POPUP)(int bShow);

/* get the selection in editor
   start: return the sel start index. (sel index started from 0)
   end  : return the sel end index.
   if there is no sel, start and end both equal to the length of the editor content.
*/
typedef void (*KMX_CALLBACK_EDITOR_GETSEL)(int* start, int* end);

/* set the selection in editor (composition)
   start: sel start index. (sel index started from 0)
   end  : sel end index.
   if start==end, then clear the sel.
*/
typedef void (*KMX_CALLBACK_EDITOR_SETSEL)(int start, int end);

/* replace the editor selection by a string.
   s: WCHAR string.
   length: length of s, if -1, s is ended with zero.
   if there is no selection in editor, insert the text at the current caret position.
*/
typedef void (*KMX_CALLBACK_EDITOR_RELACESEL)(const KMX_WCHAR* s, int length);

typedef unsigned short (*KMX_CALLBACK_EDITOR_GETCARETCHAR) (void);

typedef void (*KMX_CALLBACK_EDITOR_GETCONTEXT) (KMX_WCHAR** p_text_start, int* p_text_length);

/* load user defined words
optional callback, if not set, kmxime will not use user words.
*/
typedef KMX_BOOL (*KMX_CALLBACK_LOAD_DATA)(char** data, int* len);

/* save user defined words
optional callback
*/
typedef KMX_BOOL (*KMX_CALLBACK_SAVE_DATA)(const char* data, int len);

/* debug trace function
optional callback
*/
typedef void (*KMX_CALLBACK_DEBUG_TRACE)(const char* msg);

/* debug break function
optional callback
*/
typedef void (*KMX_CALLBACK_DEBUG_BREAK)(void);


typedef void (*KMX_CALLBACK_IM_CHANGED)(int im_mode, int case_info);

typedef void (*KMX_CALLBACK_DRAW_RECT) (int left, int top, int right, int bottom, KMX_COLOR c);

typedef void (*KMX_CALLBACK_DRAW_TEXT) (const KMX_WCHAR* text, int length, int x, int y, int font_size, int color);

typedef void (*KMX_CALLBACK_DRAW_IMAGE) (int x, int y, int imgID);

typedef void (*KMX_CALLBACK_HIDE_SOFTKEY)(void);
typedef struct tagKMXIME_CALLBACK
{
    KMX_CALLBACK_ON_KEYPAD_SIZE    f_onsize;
    KMX_CALLBACK_ON_KEYPAD_DIRTY   f_ondirty;
    KMX_CALLBACK_MEASURE           f_measure;

    KMX_CALLBACK_EDITOR_GETSEL     f_get_sel;
    KMX_CALLBACK_EDITOR_SETSEL     f_set_sel;
    KMX_CALLBACK_EDITOR_RELACESEL  f_replace_sel;
    KMX_CALLBACK_EDITOR_GETCARETCHAR f_get_caret_char;
    KMX_CALLBACK_EDITOR_GETCONTEXT f_get_context;

    KMX_CALLBACK_IM_CHANGED        f_im_changed;

    KMX_CALLBACK_DRAW_RECT         f_draw_rect;
    KMX_CALLBACK_DRAW_TEXT         f_draw_text;
    KMX_CALLBACK_DRAW_IMAGE        f_draw_image;

    //optional callbacks
    KMX_CALLBACK_LOAD_DATA         f_load_data;
    KMX_CALLBACK_SAVE_DATA         f_save_data;
    KMX_CALLBACK_DEBUG_TRACE       f_trace;
    KMX_CALLBACK_DEBUG_BREAK       f_debugbreak;

    KMX_CALLBACK_HIDE_SOFTKEY       f_hide;
} KMXIME_CALLBACK;

/****************************************************************************

API

****************************************************************************/

/* Platform Configuration API Definitions */

typedef enum
{
    KMX_PT_CASE_INTIAL = 0,
    KMX_PT_CASE_LOWER,
    KMX_PT_CASE_UPPER,
    KMX_PT_CASE_MAX
} KMX_PT_CASE_INFO;

typedef enum
{
    KMX_PT_INPUT_MODE1 = 0,
    KMX_PT_INPUT_MODE2,
    KMX_PT_INPUT_MODE3,
    KMX_PT_INPUT_MODE4,
    KMX_PT_INPUT_MODE5,
    KMX_PT_INPUT_MODE6,
    KMX_PT_INPUT_MODE7,
    KMX_PT_INPUT_MODE8,

    KMX_PT_INPUT_MODE_MAX
} KMX_PT_INPUT_MODE;

typedef struct
{
    int     input_method[KMX_PT_CASE_MAX];
} KMX_PT_INPUT_MODE_ITEM;

typedef struct
{
    int                     language;
    KMX_PT_INPUT_MODE_ITEM  items[KMX_PT_INPUT_MODE_MAX];
} KMX_PT_IM_CONFIG;

KMX_PT_INPUT_MODE kmx_im_switch_ime(const KMX_PT_IM_CONFIG *config, KMX_PT_INPUT_MODE im_mode);
KMX_PT_CASE_INFO  kmx_im_switch_case(const KMX_PT_IM_CONFIG *config, KMX_PT_INPUT_MODE im_mode, KMX_PT_CASE_INFO case_info);
int kmx_im_get_input_mode_list(const KMX_PT_IM_CONFIG *config, int  *im_list, int num_max);
int kmx_im_get_input_config(int ime_id, KMX_IME_CONFIG* config);

/* set callback routines to IME, IME need a set of callbacks
   note: must call KmxIMESetCallback before call any other API's
*/
void KmxIMESetCallback(KMXIME_CALLBACK* callback);

/* initialize IME */
void KmxIMEInit(
    const KMX_PT_IM_CONFIG*     config,
    KMXIME_SOFTKEYBOARD_TYPE    sk_type,
    int                         screenType,
    int                         screenMode,
    int                         digit_button_height,
    int                         qwerty_button_height);

void KmxIMESetTouchSupport(int is_touch_support);

/* draw ime ui */
void KmxIMEDraw(void);

void KmxIMEShowSoftKeyboard(int bShow);

/* timer for ime, the timer tick should be KMX_IME_TIMER_PERIOD ms, in each tick, call this API */
void KmxIMEOnTimer(void);

/* notify IME to destroy itself */
void KmxIMEDestroy(void);

/* get the dimension of IME ui
   return value is (width<<16) | height
*/
int KmxIMEGetSize(void);

/* pass key and touch event to IME */
int KmxIMEEventHandle(int code, int param1, int param2);

void KmxIMESetInputMode(KMX_PT_INPUT_MODE im_mode, KMX_PT_CASE_INFO case_info);

void KmxIMEExitInputMode(void);

void KmxImeSetSKLabelColor(KMX_COLOR color);

void* kmxime_get_userword(void);
int kmxime_userword_len(void);

#ifdef __cplusplus
}
#endif

#endif /* KMXIMEAPI_H */
