#ifndef IMM_COMMON_H
#define IMM_COMMON_H

#include "csk2api.h"
#include "kmximmapi.h"

#ifdef _MSC_VER
/* unreferenced formal parameter                                */
#pragma warning(disable: 4100)
/* named type definition in parentheses                         */
#pragma warning(disable: 4115)
/* nonstandard extension used: nameless struct/union            */
#pragma warning(disable: 4201)
/* nonstandard extension used: bit field types other than int   */
#pragma warning(disable: 4214)
/* type cast pointer to int                                     */
#pragma warning(disable: 4311)
/* type cast pointer to int                                     */
#pragma warning(disable: 4312)
/* The file contains a character that cannot be represented in the current code page */
#pragma warning(disable: 4819)
#pragma warning(disable: 4047)
#endif


#ifdef __cplusplus
extern "C"{
#endif

typedef enum
{
    KMX_NOTIFY_MSG_NONE,
    KMX_NOTIFY_MSG_VK_HEIGHT_CHANGED,
    KMX_NOTIFY_MSG_POS_CHANGED,
    KMX_NOTIFY_MSG_INSERT_CHAR,
    KMX_NOTIFY_MSG_BACKSPACE,
    KMX_NOTIFY_MSG_INSERT_STRING,
    KMX_NOTIFY_MSG_GET_TEXT,
    KMX_NOTIFY_MSG_GET_CARET_POS,
    KMX_NOTIFY_MSG_GET_CARET_CHAR,
    KMX_NOTIFY_MSG_CLEAR_IME_COMP,
    KMX_NOTIFY_MSG_SET_IME_COMP,
    KMX_NOTIFY_MSG_END_IME_COMP,
    KMX_NOTIFY_MSG_UPDATE, 
    KMX_NOTIFY_MSG_REDRAW, 

    KMX_NOTIFY_MSG_SWITCH_IME,
    KMX_NOTIFY_MSG_SWITCH_CASE,
    KMX_NOTIFY_MSG_CLEARALL,

    KMX_NOTIFY_MSG_GET_CARET_RECT,
    KMX_NOTIFY_MSG_START_CARET_TIMER,
    KMX_NOTIFY_MSG_STOP_CARET_TIMER,

    /* When the input component take the control.
    param1: component who takethe control
    param2: unused
    */
    KMX_NOTIFY_MSG_TAKE_CONTROL,

    /* When the input component lost the control.
    param1: component who lost the control
    param2: unused
    */
    KMX_NOTIFY_MSG_LOST_CONTROL,

    /* When the input mode is changed inside the engine, 
    * The corresponding imm should notify which input mode should be set
    * for the other imm, eg. handwriting imm change the recognize type when this happened.
    * param1: input mode that should be set
    * param2: unused
    */
    KMX_NOTIFY_MSG_INPUT_MODE_CHANGED,
    KMX_NOTIFY_MSG_IS_IME_WINDOW_VISIBLE,
    KMX_NOTIFY_MSG_HIDE_SOFTKEY,
    KMX_NOTIFY_MSG_END
}KMX_NOTIFY_MSG_CODE;

int kmxime_wstrlen(const KMX_WCHAR* str);

int KmxImeCallbackOnMessage(int code, int param1, int param2);
int KmxImeCallbackCreateTimer(int proc, int t);
void KmxImeCallbackCancelTimer(int timeId);
int KmxImeCallbackMeasureText(const KMX_WCHAR* text, int length, int font_size);
void KmxImeCallbackDrawText(const KMX_WCHAR* text, int length, int x, int y, int font_size, int color);
void KmxImeCallbackDrawRect(int left, int top, int right, int bottom, int color);
void KmxImeCallbackDrawImage(int x, int y, int imgID);
void KmxImeCallbackEchoButton(const KMX_WCHAR* text, int length, int color, 
							  int imgId, int x, int y, int w, int h, int echoStyle);
void KmxImeCallbackStopEchoButton(void);
void KmxImeCallbackLoadData(char** data, int* len);
void KmxImeCallbackSaveData(char* data, int len);
int KmxImeCallbackGetFuzzy(void);

extern CS_USER_PARAMS kmx_g_user_words;

#ifdef __cplusplus
}
#endif

#endif
