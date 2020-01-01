#ifndef __MMI_EMU_H__
#define __MMI_EMU_H__

/**
 * @file     emu.h
 * @brief   The document describes the interface of EMU engine
 */


/**
 * EMU input key definition
 */
#define EMU_KEY_NUM                 (16)
#define EMU_KEY_FAKE                (0x0000)

#define EMU_KEY_EMU8BIT_A           (0x0001)
#define EMU_KEY_EMU8BIT_B           (0x0002)
#define EMU_KEY_EMU8BIT_TURBO_A     (0x0004)
#define EMU_KEY_EMU8BIT_TURBO_B     (0x0008)
#define EMU_KEY_EMU8BIT_START       (0x0010)
#define EMU_KEY_EMU8BIT_SELECT      (0x0020)
#define EMU_KEY_EMU8BIT_RIGHT       (0x0040)
#define EMU_KEY_EMU8BIT_LEFT        (0x0080)
#define EMU_KEY_EMU8BIT_DOWN        (0x0100)
#define EMU_KEY_EMU8BIT_UP          (0x0200)

#define EMU_KEY_SEMU16BIT_TR        (1 << 4)
#define EMU_KEY_SEMU16BIT_TL        (1 << 5)
#define EMU_KEY_SEMU16BIT_X         (1 << 6)
#define EMU_KEY_SEMU16BIT_A         (1 << 7)
#define EMU_KEY_SEMU16BIT_RIGHT     (1 << 8)
#define EMU_KEY_SEMU16BIT_LEFT      (1 << 9)
#define EMU_KEY_SEMU16BIT_DOWN      (1 << 10)
#define EMU_KEY_SEMU16BIT_UP        (1 << 11)
#define EMU_KEY_SEMU16BIT_START     (1 << 12)
#define EMU_KEY_SEMU16BIT_SELECT    (1 << 13)
#define EMU_KEY_SEMU16BIT_Y         (1 << 14)
#define EMU_KEY_SEMU16BIT_B         (1 << 15)

#define EMU_KEY_ALL_EMU8BIT         ((EMU_KEY_EMU8BIT_A) | (EMU_KEY_EMU8BIT_B) | (EMU_KEY_EMU8BIT_START) | (EMU_KEY_EMU8BIT_SELECT) | (EMU_KEY_EMU8BIT_RIGHT) | (EMU_KEY_EMU8BIT_LEFT) | (EMU_KEY_EMU8BIT_DOWN) | (EMU_KEY_EMU8BIT_UP))
#define EMU_KEY_ALL_SEMU16BIT       ((EMU_KEY_SEMU16BIT_TR) | (EMU_KEY_SEMU16BIT_TL) | (EMU_KEY_SEMU16BIT_X) | (EMU_KEY_SEMU16BIT_A) | (EMU_KEY_SEMU16BIT_RIGHT) | (EMU_KEY_SEMU16BIT_LEFT) | (EMU_KEY_SEMU16BIT_DOWN) | (EMU_KEY_SEMU16BIT_UP) | (EMU_KEY_SEMU16BIT_START) | (EMU_KEY_SEMU16BIT_SELECT) | (EMU_KEY_SEMU16BIT_Y) | (EMU_KEY_SEMU16BIT_B))

/**
 * Define EMU input key type
 */
typedef u16 EmuKey_t;

/**
 * EMU input key mode definition
 */
#define EMU_INPUT_KEY_RELEASE   0x00
#define EMU_INPUT_KEY_PRESS     0x01

typedef struct
{
	MAE_WChar *pPath;
} EmuRom_t;

#endif /* __MMI_EMU_H__ */
