#ifndef CS_IME_ADAPTER_H
#define CS_IME_ADAPTER_H

#ifdef __cplusplus
extern "C"{
#endif

typedef enum
{
    CS_KEYPAD_NONE,

    CS_KEYPAD_9,
    
    CS_KEYPAD_SURE,

    CS_KEYPAD_FULL,
} CS_KEYPAD_TYPE;

typedef enum
{
    CS_KEY_PHYSICAL,
    CS_KEY_VIRTUAL
} CS_KEY_SOURCE;

typedef enum
{
    CS_CASE_LEADER_UPPER,
    CS_CASE_LOWER,
    CS_CASE_UPPER
} CS_CASE_INFO;

typedef struct tag_EDITOR_IME_INTERFACE EDITOR_IME_INTERFACE;

/* Exported API */
void cs_ime_switch_keypad(CS_KEYPAD_TYPE keypad_type);
int cs_ime_get_default_keypad(void);
void cs_ime_get_ime_wnd_extent(int * width, int * height);
int cs_ime_is_ui_visible(void);
int cs_ime_handle_key(int key_code, int key_type, EDITOR_IME_INTERFACE* editor_interface);
int cs_ime_handle_char(int ch, EDITOR_IME_INTERFACE* editor_interface);
void cs_ime_set_input_method(int input_method, EDITOR_IME_INTERFACE* editor_interface);
int cs_ime_pen_down_handler(int x, int y, EDITOR_IME_INTERFACE* editor_interface);
int cs_ime_pen_move_handler(int x, int y, EDITOR_IME_INTERFACE* editor_interface);
int cs_ime_pen_up_handler(int x, int y, EDITOR_IME_INTERFACE* editor_interface);
int cs_ime_paint_window(int x, int y, EDITOR_IME_INTERFACE* editor_interface);
void cs_ime_hide_window(EDITOR_IME_INTERFACE* editor_interface);
void cs_ime_show_window(EDITOR_IME_INTERFACE* editor_interface);

int cs_ime_is_full_keypad_active(void);
int cs_ime_is_sure_keypad_active(void);
void cs_ime_set_key_source(CS_KEY_SOURCE source);

void cs_ime_reset(EDITOR_IME_INTERFACE* editor_interface);

int cs_ime_notify(KMX_NOTIFY_MSG_CODE code, int param1, int param2);
void cs_ime_on_timer (void);

void cs_ime_set_arrow_style(int style);
int cs_ime_is_bengali_ime(void);
#ifdef __cplusplus
}
#endif

#endif
