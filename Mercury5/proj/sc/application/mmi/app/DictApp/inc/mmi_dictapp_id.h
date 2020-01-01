#ifndef __MMI_DICTAPP_ID_H__
#define __MMI_DICTAPP_ID_H__

#define DICT_INPUT_MAX_BYTE_RS         36 
typedef enum DictWndId_e_
{
    DICT_WND_INIT = WND_ID_APP_BASE,
    DICT_WND_INPUT,
    DICT_WND_OPTION,
    DICT_WND_WORDMENU,
    DICT_WND_TRANSLATION,
}DictWndId_e;

typedef enum
{
	MNU_DICT_TRANS = 0,
}DictMenuId_e;

#endif //__MMI_DICTAPP_ID_H__
