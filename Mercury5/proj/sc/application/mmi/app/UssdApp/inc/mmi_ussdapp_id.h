#ifndef __MMI_USSDAPP_ID_H__
#define __MMI_USSDAPP_ID_H__

#define USSDAPP_MAX_INPUT_BYTE 160 //Maximum allowable input bytes (80 characters)
#define USSDAPP_DISPLAY_HEIGHT     (MAIN_DEFVIEW_HEIGHT - MAIN_TITLE_HEIGHT)

typedef enum
{
    USSD_WND_DUAL_SIM = WND_ID_APP_BASE,
    USSD_WND_DISPLAY_USSD,
    USSD_WND_REPLY,
    USSD_WND_NEW_RESULT
} UssdWndId_e;

typedef enum
{
    USSD_DISPLAY_SCROLLBAR=APP_WDG_START,
    USSD_DISPLAY_INPUT,
}UssdDisplayView_e;

#endif //__MMI_USSDAPP_ID_H__

