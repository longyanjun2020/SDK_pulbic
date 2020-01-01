#ifndef __CUS_HOTKEY_H__
#define __CUS_HOTKEY_H__

#include "vm_types.ht"
#include "vm_kbd.h"

#define KEY_HOT_KEY_CHANGE_MAPPING      (u8)0xD0
#define KEY_HOT_KEY_DEFAULT_MAPPING     (u8)0xD1

#define KEY_HOT_KEY_TRACE_0             (u8)0xE0
#define KEY_HOT_KEY_TRACE_1             (u8)0xE1
#define KEY_HOT_KEY_TRACE_2             (u8)0xE2
#define KEY_HOT_KEY_TRACE_3             (u8)0xE3
#define KEY_HOT_KEY_TRACE_4             (u8)0xE4
#define KEY_HOT_KEY_TRACE_5             (u8)0xE5
#define KEY_HOT_KEY_TRACE_6             (u8)0xE6
#define KEY_HOT_KEY_TRACE_7             (u8)0xE7
#define KEY_HOT_KEY_TRACE_8             (u8)0xE8
#define KEY_HOT_KEY_TRACE_9             (u8)0xE9
#define KEY_HOT_KEY_TRACE_HASH          (u8)0xEA
#define KEY_HOT_KEY_TRACE_STAR          (u8)0xEB
#define KEY_HOT_KEY_DUMP_LCD_ID         (u8)0xEC
#define KEY_DEF_EXCP_HK                 (u8)0xED
#define KEY_DEF_EXCP_DBB_HK             (u8)0xEE
#define KEY_DEF_HOPPER_HK               (u8)0xEF
#define KEY_HOT_KEY_QLOG_ON             (u8)0xFA
#define KEY_HOT_KEY_QLOG_OFF            (u8)0xFB
#define KEY_HOT_KEY_QLOG_OFF_SAVING     (u8)0xFC

#define KEY_HOT_KEY_AUDIO_TRACE_ON      (u8)0xFD
#define KEY_HOT_KEY_AUDIO_TRACE_OFF     (u8)0xFE

#define KEY_HOT_KEY_NONE                (u8)0xFF

#define CUS_HOT_KEY_EXCEPTION_SEQ_MAX_LEN 100

bool cus_CheckHotkeyException(u8 mode, u8 pressKeyNum, u8 lastKeys[][2]);
bool cus_CheckHotkeyHopper(u8 mode, u8 pressKeyNum, u8 lastKeys[][2]);
void cus_HotkeyParse(u8 hkCode);
void cus_DefHKEception(void);
u8 cus_FindHotKeySeq(u8 nHKCode, char *pnHKSeq);
#ifdef __DRV_HOT_KEY_FREQUENCY__
void cus_RecPressedKey(u8 nMode, u8 nRow, u8 nCol);
#endif
#endif

