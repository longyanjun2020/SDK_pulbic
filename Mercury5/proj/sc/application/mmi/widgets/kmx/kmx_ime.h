#ifndef KMX_IME_H
#define KMX_IME_H

#include "kmximeapi.h"
#include "mmi_mae_widget.h"
#include "mmi_mae_display.h"
#include "mae_inputcontroller_priv.h"

#ifdef __cplusplus 
extern "C"{ 
#endif 

void kmx_ime_init(InputController_t *input_controller, const KMX_PT_IM_CONFIG *config);
void kmx_ime_destroy(InputController_t *input_controller);
void kmx_ime_updateonfig(InputController_t *input_controller, int nDispMode, const KMX_PT_IM_CONFIG *config);
void kmx_ime_set_input_mode(InputController_t *input_controller, KMX_PT_INPUT_MODE im_mode, KMX_PT_CASE_INFO case_info);

void kmx_ime_draw(InputController_t *input_controller, IDisplay* pIDisplay, s32 x, s32 y);

void kmx_ime_show_softkeyboard(InputController_t *input_controller, int bShow);

int kmx_ime_on_touch_down(InputController_t *input_controller, int x, int y);
int  kmx_ime_on_touch_up(InputController_t *input_controller, int x, int y);
int  kmx_ime_on_key_down(InputController_t *input_controller, int keyCode,MAE_EventId evt);
int  kmx_ime_on_key_up(InputController_t *input_controller, int keyCode);

void kmx_ime_exit_im(InputController_t *input_controller);

//for formatInputwidget
#ifdef __MMI_IME_CSTAR_FORMAT__
void kmx_ime_format_init(IWidget *pIWidget, const KMX_PT_IM_CONFIG *config);
void kmx_ime_format_destroy(IWidget *pIWidget);
void kmx_ime_format_set_input_mode(IWidget *pIWidget, KMX_PT_INPUT_MODE im_mode, KMX_PT_CASE_INFO case_info);

void kmx_ime_format_draw(IWidget *pIWidget, IDisplay* pIDisplay, s32 x, s32 y);

void kmx_ime_format_show_softkeyboard(IWidget *pIWidget, int bShow);

int kmx_ime_format_on_touch_down(IWidget *pIWidget, int x, int y);
int  kmx_ime_format_on_touch_up(IWidget *pIWidget, int x, int y);
int  kmx_ime_format_on_key_down(IWidget *pIWidget, int keyCode);
int  kmx_ime_format_on_key_up(IWidget *pIWidget, int keyCode);

void kmx_ime_format_exit_im(IWidget *pIWidget);
int KmxCurIsBengaliIME(void);
#endif /*__MMI_IME_CSTAR_FORMAT__*/
#ifdef __cplusplus 
} 
#endif 

#endif /* KMX_IME_H */
