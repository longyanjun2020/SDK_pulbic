#ifndef CSTAR_IME_H
#define CSTAR_IME_H

#define CS_UI_FONT              int
#define CS_UI_COLOR             int
#define CS_UI_WCHAR             unsigned short

#define CS_UI_TEXT_FONT         0
#define CS_UI_LABEL_FONT        1
#define CS_UI_FONT_COUNT        2

#define CS_UI_BK_COLOR          0
#define CS_UI_TEXT_COLOR        1
#define CS_UI_HOT_COLOR_1       2
#define CS_UI_HOT_COLOR_2       3
#define CS_UI_HOT_COLOR_3       4
#define CS_UI_HOT_TEXT_COLOR    5
#define CS_UI_HOT_BK_COLOR      6
#define CS_UI_HOT_TEXT_COLOR_1  7
#define CS_UI_HOT_BK_COLOR_1    8
#define CS_UI_DIGIT_LABEL_COLOR 9
#define CS_UI_TIP_TEXT          10
#define CS_UI_COLOR_COUNT       11
#define KMX_TIMER_3                 3

typedef struct tagCS_UI_RECT
{
    int                         left;
    int                         top;
    int                         right;
    int                         bottom;
} CS_UI_RECT;

typedef enum
{
    CS_UI_KEY_BASE = 0x100,

    CS_UI_KEY_0,
    CS_UI_KEY_1,
    CS_UI_KEY_2,
    CS_UI_KEY_3,
    CS_UI_KEY_4,
    CS_UI_KEY_5,
    CS_UI_KEY_6,
    CS_UI_KEY_7,
    CS_UI_KEY_8,
    CS_UI_KEY_9,
    CS_UI_KEY_L1,
    CS_UI_KEY_L2,
    CS_UI_KEY_L3,
    CS_UI_KEY_R1,
    CS_UI_KEY_R2,
    CS_UI_KEY_R3,
    CS_UI_KEY_STAR,
    CS_UI_KEY_POUND,
    CS_UI_KEY_LEFT,
    CS_UI_KEY_RIGHT,
    CS_UI_KEY_UP,
    CS_UI_KEY_DOWN,
    CS_UI_KEY_OK,
    CS_UI_KEY_LSK,
    CS_UI_KEY_RSK,

    CS_UI_KEY_ALT,
    CS_UI_KEY_CASE,

    CS_UI_KEY_END
} CS_UI_KEY;

typedef enum
{
    CS_IMM_STATE_INITIAL,
    CS_IMM_STATE_VK_CAND,
    CS_IMM_STATE_CAND_SELECT

} CS_IMM_STATE;

/* Key Properties */
#define CS_KEY_MESSAGE_NONE         0x0
#define CS_KEY_MESSAGE_ONE          0x1 /* Process up or long press message */
#define CS_KEY_MESSAGE_TWO          0x2 /* Process both up and long press message */

/* Adapter API Start */

void* cs_load_ime_userdata_impl(int *length);
void cs_save_ime_userdata_impl(void *data, int length);
int cs_load_ime_options_impl(void *data, int *length);
void cs_save_ime_options_impl(void *options, int length);
void cs_disable_ime_timer_impl(void);
void cs_enable_ime_timer_impl(int interval, void (*time_proc)(void));
void cs_initialize_tables_impl(void);
int cs_get_char_height_impl(int font, CS_UI_WCHAR c);
int cs_get_line_height_impl(int font);
int cs_get_char_width_impl(int font, CS_UI_WCHAR c);
int cs_get_text_width_impl(int font, const CS_UI_WCHAR* text, int text_len);
void cs_draw_pixel_impl(int x, int y, int pixel_color);
void cs_draw_rect_impl(const CS_UI_RECT* r, int rect_color);
void cs_draw_text_impl(int x, int y, int font,
    const CS_UI_WCHAR* text, int text_len, int text_color);
void cs_set_state_impl(CS_IMM_STATE state);
int cs_gui_mode_to_cstar_mode_impl(int input_method);
int cs_is_pinyin_ime_impl(int m);
int cs_is_zhuyin_ime_impl(int m);
int cs_cfg_imewnd_right_impl(void);
void cs_set_comp_impl(const unsigned short *text, int length);
void cs_clear_comp_impl(void);
void cs_end_comp_impl(void);
int cs_wcslen_impl(unsigned short *text);
void cs_invalidate_impl(void);
void cs_delete_char_impl(void);
int cs_insert_text_impl(const unsigned short *text, int length);
unsigned short cs_ime_get_caret_pos_char(void);
int cs_is_suretype_enabled_impl(void);
int cs_is_fullkey_im(int im);

void cs_get_hint_by_im_impl(int im);
CS_UI_WCHAR * cs_get_hint_text_impl(int index);

typedef int (*CS_TRAVERSE_FUNC) (int im_mode, const unsigned short * word, int word_len);
int cs_traverse_predefined_user_words_impl(CS_TRAVERSE_FUNC func);

int cs_ime_is_full_keypad_active(void);
int cs_ime_is_sure_keypad_active(void);
void cstar_ime_reset_keypad(void);

/* Adapter API End */

/* Platform Independent API */
unsigned long cstar_ime_get_fuzzy(void);
void cstar_ime_set_fuzzy(unsigned long value);
unsigned long cstar_ime_get_pinyin_mode(void);
void cstar_ime_set_pinyin_mode(unsigned long value);
unsigned long cstar_ime_get_candidate_mode(void);
void cstar_ime_set_candidate_mode(unsigned long value);

int CS_IME_HandleEvent(int is_char_event, int key, int presshold);
void CS_IME_CloseInputMethod(void);
void CS_IME_SetInputMethod(int input_method);
int CS_IME_GetInputMethod(void);
void CS_IME_Reset(void);
int CS_IME_IsStrokeWordEnabled(void);
void CS_IME_GetImeWndExtent(int * width, int * height);
void CS_IME_FindUserCacheByIM(int input_method, void **user_data, int *user_data_size);
void CS_IME_AddNewWord(
    int              m,
    unsigned short  *word,
    int              word_length);

int CS_IME_QueryAsso(
    int m,
    unsigned short char_code, 
    unsigned short* buffer, 
    int num);

void CS_IME_CompleteInput(void);
int CS_IME_PaintWindow(int x, int bottom_y);
int CS_IME_PenDownHandler(int x, int y);
int CS_IME_PenMoveHandler(int x, int y);
int CS_IME_PenUpHandler(int x, int y);
int CS_IME_IsUiVisible(void);
void CS_IME_HideWindow(void);
void CS_IME_ShowWindow(void);
int CS_IME_IsIMUserDefinedMultitap(void);
int CS_IME_QueryKeyMessageProperties(int key);
void CS_OnTimerEvent(void);

#endif
