#ifndef IMM_CALLBACK_H
#define IMM_CALLBACK_H

#include "kmximmapi.h"

#ifdef __cplusplus
extern "C"{
#endif

void kmx_editor_debug(const char* text);
void kmx_editor_debug2(const char* text, int value);
int kmx_editor_msg(const KMX_MSG* msg);
int kmx_editor_create_timer(int proc, int t);
void kmx_editor_cancel_timer(int timeId);
void kmx_editor_measure(int font_size, const KMX_WCHAR* text, int length, int* width, int* height);
void kmx_editor_draw_text(int x, int y, const KMX_WCHAR* text, int length, int font_size, KMX_COLOR c);
void kmx_editor_draw_rect(int left, int top, int right, int bottom, KMX_COLOR c);
void kmx_editor_draw_image(int x, int y, int imgID);
void kmx_editor_echo_button(const KMX_WCHAR* text, int color, int imgId, int x, int y, int w, int h, int echoStyle);
void kmx_editor_stop_echo(void);
void kmx_editor_save_data(char* data, int len);
void kmx_editor_load_data(char** data, int* len);


#ifdef __cplusplus
}
#endif

#endif
