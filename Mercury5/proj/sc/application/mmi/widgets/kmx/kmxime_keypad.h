#ifndef KMXTOUCHKEYPAD_H
#define KMXTOUCHKEYPAD_H

#include "kmximeapi.h"
#include "kmxime_api.h"
#include "kmximmapi.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct tagKmxKeyPad KmxKeypad;
typedef void (*TIMER_PROC)(void);

typedef struct
{
    int         sequencial_number;
    int         flags;
    int         commit_length;
    KMX_WCHAR   commit_text[KMX_MAX_COMMIT];
    int         composition_length;
    KMX_WCHAR   composition_text[KMX_MAX_COMPOSITION];
} KMX_SIP_OUTPUT;

struct tagKmxKeyPad
{
    KMX_KEYPAD      api;
    KMX_IMM         imm;

    int             metric;
    int             qwerty_button_height;
    int             digit_button_height;
    int             bottom_line;
    int             x;
    int             y;
    int             width;
    int             height;

    int             timer1Actived;
    int             timer2Actived;
    int             is_keypad_visible;    

    int             language;

    int             is_composition_set;
    KMX_SIP_OUTPUT  output;
    int             is_popup;
};

extern KmxKeypad* keypad;

KmxKeypad* keypad_create(
    const int*                  input_mode_list, 
    int                         input_mode_list_length, 
    KMXIME_SOFTKEYBOARD_TYPE    sk_type,
    int                         digit_button_height,
    int                         qwerty_button_height);
void keypad_destroy(KmxKeypad* keypad);
void keypad_draw(KmxKeypad* keypad, int x, int y);
int kmx_keypad_handle_event(KmxKeypad* keypad, int evt, int wParam, int dwParam);
void keypad_show(KmxKeypad* keypad);
void keypad_hide(KmxKeypad* keypad);
void keypad_get_size(KmxKeypad* keypad, int* width, int* height);
KMX_IMM keypad_get_imm(KmxKeypad* keypad);
void keypad_send_imm_message(KmxKeypad* keypad, int code, int param1, int param2);

void CStarKeypadCreate(
    int*                        ime_table, 
    int                         num_ime, 
    KMXIME_SOFTKEYBOARD_TYPE    sk_type, 
    int                         screenType, 
    int                         screenMode,
    int                         digit_button_height,
    int                         qwerty_button_height);
void CStarKeypadDestroy(void);
void CStarKeypadDraw(int x, int y);
int CStarKeypadEventHandle(int evt, int p1, int p2);
void CStarKeypadShow(void);
void CStarKeypadHide(void);
int CStarKeypadGetSize(void);
void CStarKeypadSendImmMessage(int code, int p1, int p2);
void CStarKeypadOnTimer(int timerId);
int kmx_keypad_set_input_method(int input_mode, int case_info);
void CStarKeypadExitInputMode(void);

#ifdef __cplusplus
}
#endif

#endif /* KMXTOUCHKEYPAD_H */
