/**
 * @file mmi_emuapp_custom.h
 *
 * EmuApp Customization Data
 *
 * @version $Id: mmi_emuapp_custom.h 40986 2009-09-22 03:06:28Z elvis.chen $
 */
#ifndef __MMI_EMUAPP_CUSTOM_H__
#define __MMI_EMUAPP_CUSTOM_H__

#include "mmi_event.h"
#include "mmi_emu.h"
#include "mmi_emuapp_priv.h"

// Do not change the key reset/exit define
#define EMUAPP_KEY_EXIT  0

// Maximal length of help string
#define EMUAPP_HELP_STR_LEN_MAX 500

// EMU bin file path
#define	EMUAPP_BIN_CARD_PATH            L"fs:/CARD/DlmBin/eml_main.dlm"
#define	EMUAPP_BIN_CARD_FOLDER          L"fs:/CARD/DlmBin/"
#define EMUAPP_BIN_16BIT_CARD_PATH      L"fs:/CARD/DlmBin/eml_main_16.dlm"
#define EMUAPP_BIN_16BIT_CARD_FOLDER    EMUAPP_BIN_CARD_FOLDER
#ifdef __DUAL_CARD__
#define	EMUAPP_BIN_CARD2_PATH           L"fs:/SD_2/DlmBin/eml_main.dlm"
#define	EMUAPP_BIN_CARD2_FOLDER         L"fs:/SD_2/DlmBin/"
#define EMUAPP_BIN_16BIT_CARD2_PATH     L"fs:/SD_2/DlmBin/eml_main_16.dlm"
#define EMUAPP_BIN_16BIT_CARD2_FOLDER   EMUAPP_BIN_CARD2_FOLDER
#endif
#ifdef __ONBOARD_USER_STORAGE_MMI__
#define	EMUAPP_BIN_PHONE_PATH           L"fs:/PHON/DlmBin/eml_main.dlm"
#define	EMUAPP_BIN_PHONE_FOLDER         L"fs:/PHON/DlmBin/"
#define EMUAPP_BIN_16BIT_PHONE_PATH     L"fs:/PHON/DlmBin/eml_main_16.dlm"
#define EMUAPP_BIN_16BIT_PHONE_FOLDER   EMUAPP_BIN_PHONE_FOLDER
#endif

// Max rom size
#define EMUAPP_MAX_ROM_SIZE_SEMU_16BIT  (1024 * 1024 * 4)   // 4MB
static u32 EMUAPP_MAX_ROM_SIZE;

#define EMUAPP_KEY_MAP_START_ID         (0xFFF0)
#define EMUAPP_HELP_MAP_TXT_NULL_ID     (TXT_NULL_ID)


#ifdef __EMU_KEY_MAPPING_TABEL_C__

#if defined(__EMU_VIRTUAL_KEYPAD_ENABLE__)
static const u32 gEmuKeyMap[][2] =
{
    // EMU_GAME_EMU_8BIT
    {EMUAPP_KEY_MAP_START_ID,   EMU_GAME_EMU_8BIT},
    {MAE_KEY_LEFT,      EMU_KEY_EMU8BIT_B},
    {MAE_KEY_RIGHT,     EMU_KEY_FAKE},
    {MAE_KEY_1,         EMU_KEY_FAKE},
    {MAE_KEY_2,         EMU_KEY_FAKE},
    {MAE_KEY_3,         EMU_KEY_FAKE},
    {MAE_KEY_4,         EMU_KEY_EMU8BIT_B},
    {MAE_KEY_6,         EMU_KEY_FAKE},
    {MAE_KEY_7,         EMU_KEY_FAKE},
    {MAE_KEY_8,         EMU_KEY_EMU8BIT_A},
    {MAE_KEY_9,         EMU_KEY_FAKE},
    {MAE_KEY_STAR,      EMU_KEY_FAKE},
    {MAE_KEY_HASH,      EMU_KEY_FAKE},
    {MAE_KEY_UP,        EMU_KEY_FAKE},
    {MAE_KEY_DOWN,      EMU_KEY_EMU8BIT_A},
    {MAE_KEY_SKLEFT,    EMU_KEY_EMU8BIT_SELECT},
    {MAE_KEY_SKRIGHT,   EMU_KEY_EMU8BIT_START},

#if defined(__GAME_ENGINE_EMU_16BIT__)
    // EMU_GAME_SEMU_16BIT
    {EMUAPP_KEY_MAP_START_ID,   EMU_GAME_SEMU_16BIT},
    {MAE_KEY_LEFT,      EMU_KEY_SEMU16BIT_B},
    {MAE_KEY_RIGHT,     EMU_KEY_SEMU16BIT_X},
    {MAE_KEY_1,         EMU_KEY_FAKE},
    {MAE_KEY_2,         EMU_KEY_SEMU16BIT_Y},
    {MAE_KEY_3,         EMU_KEY_FAKE},
    {MAE_KEY_4,         EMU_KEY_SEMU16BIT_B},
    {MAE_KEY_6,         EMU_KEY_SEMU16BIT_X},
    {MAE_KEY_7,         EMU_KEY_FAKE},
    {MAE_KEY_8,         EMU_KEY_SEMU16BIT_A},
    {MAE_KEY_9,         EMU_KEY_FAKE},
    {MAE_KEY_STAR,      EMU_KEY_SEMU16BIT_TL},
    {MAE_KEY_HASH,      EMU_KEY_SEMU16BIT_TR},
    {MAE_KEY_UP,        EMU_KEY_SEMU16BIT_Y},
    {MAE_KEY_DOWN,      EMU_KEY_SEMU16BIT_A},
    {MAE_KEY_SKLEFT,    EMU_KEY_SEMU16BIT_SELECT},
    {MAE_KEY_SKRIGHT,   EMU_KEY_SEMU16BIT_START},
#endif // __GAME_ENGINE_EMU_16BIT__

    {EMUAPP_KEY_MAP_START_ID,   EMUAPP_KEY_MAP_START_ID}
};

#else // !__EMU_VIRTUAL_KEYPAD_ENABLE__

#if (90 == __EMU_DISPLAY_ROTATION_ANGLE__)
static const u32 gEmuKeyMap[][2] =
{
    // EMU_GAME_EMU_8BIT
    {EMUAPP_KEY_MAP_START_ID,   EMU_GAME_EMU_8BIT},
    {MAE_KEY_LEFT,      EMU_KEY_EMU8BIT_DOWN},
    {MAE_KEY_RIGHT,     EMU_KEY_EMU8BIT_UP},
    {MAE_KEY_1,         (EMU_KEY_EMU8BIT_LEFT | EMU_KEY_EMU8BIT_DOWN)},
    {MAE_KEY_2,         EMU_KEY_EMU8BIT_LEFT},
    {MAE_KEY_3,         (EMU_KEY_EMU8BIT_LEFT | EMU_KEY_EMU8BIT_UP)},
    {MAE_KEY_4,         EMU_KEY_EMU8BIT_DOWN},
    {MAE_KEY_6,         EMU_KEY_EMU8BIT_UP},
    {MAE_KEY_7,         (EMU_KEY_EMU8BIT_RIGHT | EMU_KEY_EMU8BIT_DOWN)},
    {MAE_KEY_8,         EMU_KEY_EMU8BIT_RIGHT},
    {MAE_KEY_9,         (EMU_KEY_EMU8BIT_RIGHT | EMU_KEY_EMU8BIT_UP)},
    {MAE_KEY_STAR,      EMU_KEY_EMU8BIT_A},
    {MAE_KEY_HASH,      EMU_KEY_EMU8BIT_B},
    {MAE_KEY_UP,        EMU_KEY_EMU8BIT_LEFT},
    {MAE_KEY_DOWN,      EMU_KEY_EMU8BIT_RIGHT},
    {MAE_KEY_SKLEFT,    EMU_KEY_EMU8BIT_SELECT},
    {MAE_KEY_SKRIGHT,   EMU_KEY_EMU8BIT_START},

#if defined(__GAME_ENGINE_EMU_16BIT__)
    // EMU_GAME_SEMU_16BIT
    {EMUAPP_KEY_MAP_START_ID,   EMU_GAME_SEMU_16BIT},
    {MAE_KEY_LEFT,      EMU_KEY_SEMU16BIT_DOWN},
    {MAE_KEY_RIGHT,     EMU_KEY_SEMU16BIT_UP},
    {MAE_KEY_1,         EMU_KEY_SEMU16BIT_Y},
    {MAE_KEY_2,         EMU_KEY_SEMU16BIT_LEFT},
    {MAE_KEY_3,         (EMU_KEY_SEMU16BIT_LEFT | EMU_KEY_SEMU16BIT_UP)},
    {MAE_KEY_4,         EMU_KEY_SEMU16BIT_X},
    {MAE_KEY_5,         EMU_KEY_SEMU16BIT_DOWN},
    {MAE_KEY_6,         EMU_KEY_SEMU16BIT_UP},
    {MAE_KEY_7,         EMU_KEY_SEMU16BIT_B},
    {MAE_KEY_8,         EMU_KEY_SEMU16BIT_RIGHT},
    {MAE_KEY_9,         (EMU_KEY_SEMU16BIT_RIGHT | EMU_KEY_SEMU16BIT_UP)},
    {MAE_KEY_STAR,      EMU_KEY_SEMU16BIT_A},
    {MAE_KEY_0,         EMU_KEY_SEMU16BIT_TL},
    {MAE_KEY_HASH,      EMU_KEY_SEMU16BIT_TR},
    {MAE_KEY_UP,        EMU_KEY_SEMU16BIT_LEFT},
    {MAE_KEY_DOWN,      EMU_KEY_SEMU16BIT_RIGHT},
    {MAE_KEY_SKLEFT,    EMU_KEY_SEMU16BIT_SELECT},
    {MAE_KEY_SKRIGHT,   EMU_KEY_SEMU16BIT_START},
#endif // __GAME_ENGINE_EMU_16BIT__

    {EMUAPP_KEY_MAP_START_ID,   EMUAPP_KEY_MAP_START_ID}
};
#else // __EMU_DISPLAY_ROTATION_ANGLE__
static const u32 gEmuKeyMap[][2] =
{
    // EMU_GAME_EMU_8BIT
    {EMUAPP_KEY_MAP_START_ID,   EMU_GAME_EMU_8BIT},
    {MAE_KEY_LEFT,      EMU_KEY_EMU8BIT_LEFT},
    {MAE_KEY_RIGHT,     EMU_KEY_EMU8BIT_RIGHT},
    {MAE_KEY_1,         (EMU_KEY_EMU8BIT_LEFT | EMU_KEY_EMU8BIT_UP)},
    {MAE_KEY_2,         EMU_KEY_EMU8BIT_UP},
    {MAE_KEY_3,         (EMU_KEY_EMU8BIT_RIGHT | EMU_KEY_EMU8BIT_UP)},
    {MAE_KEY_4,         EMU_KEY_EMU8BIT_LEFT},
    {MAE_KEY_6,         EMU_KEY_EMU8BIT_RIGHT},
    {MAE_KEY_7,         (EMU_KEY_EMU8BIT_LEFT | EMU_KEY_EMU8BIT_DOWN)},
    {MAE_KEY_8,         EMU_KEY_EMU8BIT_DOWN},
    {MAE_KEY_9,         (EMU_KEY_EMU8BIT_RIGHT | EMU_KEY_EMU8BIT_DOWN)},
    {MAE_KEY_STAR,      EMU_KEY_EMU8BIT_A},
    {MAE_KEY_HASH,      EMU_KEY_EMU8BIT_B},
    {MAE_KEY_UP,        EMU_KEY_EMU8BIT_UP},
    {MAE_KEY_DOWN,      EMU_KEY_EMU8BIT_DOWN},
    {MAE_KEY_SKLEFT,    EMU_KEY_EMU8BIT_SELECT},
    {MAE_KEY_SKRIGHT,   EMU_KEY_EMU8BIT_START},

#if defined(__GAME_ENGINE_EMU_16BIT__)
    // EMU_GAME_SEMU_16BIT
    {EMUAPP_KEY_MAP_START_ID,   EMU_GAME_SEMU_16BIT},
    {MAE_KEY_LEFT,      EMU_KEY_SEMU16BIT_LEFT},
    {MAE_KEY_RIGHT,     EMU_KEY_SEMU16BIT_RIGHT},
    {MAE_KEY_1,         (EMU_KEY_SEMU16BIT_LEFT | EMU_KEY_SEMU16BIT_UP)},
    {MAE_KEY_2,         EMU_KEY_SEMU16BIT_UP},
    {MAE_KEY_3,         (EMU_KEY_SEMU16BIT_RIGHT | EMU_KEY_SEMU16BIT_UP)},
    {MAE_KEY_4,         EMU_KEY_SEMU16BIT_LEFT},
    {MAE_KEY_5,         EMU_KEY_SEMU16BIT_DOWN},
    {MAE_KEY_6,         EMU_KEY_SEMU16BIT_RIGHT},
    {MAE_KEY_7,         EMU_KEY_SEMU16BIT_TL},
    {MAE_KEY_8,         EMU_KEY_SEMU16BIT_Y},
    {MAE_KEY_9,         EMU_KEY_SEMU16BIT_X},
    {MAE_KEY_STAR,      EMU_KEY_SEMU16BIT_TR},
    {MAE_KEY_0,         EMU_KEY_SEMU16BIT_B},
    {MAE_KEY_HASH,      EMU_KEY_SEMU16BIT_A},
    {MAE_KEY_UP,        EMU_KEY_SEMU16BIT_UP},
    {MAE_KEY_DOWN,      EMU_KEY_SEMU16BIT_DOWN},
    {MAE_KEY_SKLEFT,    EMU_KEY_SEMU16BIT_SELECT},
    {MAE_KEY_SKRIGHT,   EMU_KEY_SEMU16BIT_START},
#endif // __GAME_ENGINE_EMU_16BIT__

    {EMUAPP_KEY_MAP_START_ID,   EMUAPP_KEY_MAP_START_ID}
};
#endif // __EMU_DISPLAY_ROTATION_ANGLE__
#endif // __EMU_VIRTUAL_KEYPAD_ENABLE__

/*
Customize this function key mapping table for different product
For now, this table only defines keys for reset and exit.
*/
static const u8 gEmuFuncMap[] =
{
    MAE_KEY_END, // EMUAPP_KEY_EXIT
};

/*
Customize this instruction help table for different product
*/
#if (90 == __EMU_DISPLAY_ROTATION_ANGLE__)
static const u32 gEmuHelpMap[][2] =
{
    // EMU_GAME_EMU_8BIT
    {EMUAPP_HELP_MAP_TXT_NULL_ID,   EMU_GAME_EMU_8BIT},
    {TXT_LIL_N_EMU_SELECT,          TXT_LIL_N_LEFT_SOFT_KEY},   // Select
    {TXT_LIL_N_EMU_START,           TXT_LIL_N_RIGHT_SOFT_KEY},  // Start
    {TXT_LIL_N_EMU_EXIT,            TXT_LIL_N_END_KEY},         // Exit
    {TXT_LIL_N_EMU_A,               TXT_LIL_N_TXT_LIL_N_NUMERIC_KEY_STAR},  // A
    {TXT_LIL_N_EMU_B,               TXT_LIL_N_TXT_LIL_N_NUMERIC_KEY_HASH},  // B
    {TXT_LIL_N_EMU_LEFT_UP,         TXT_LIL_N_NUMERIC_KEY_3},   // Left-Up
    {TXT_LIL_N_EMU_UP,              TXT_LIL_N_NUMERIC_KEY_6},   // Up
    {TXT_LIL_N_EMU_RIGHT_UP,        TXT_LIL_N_NUMERIC_KEY_9},   // Right-Up
    {TXT_LIL_N_EMU_LEFT,            TXT_LIL_N_NUMERIC_KEY_2},   // Left
    {TXT_LIL_N_EMU_RIGHT,           TXT_LIL_N_NUMERIC_KEY_8},   // Right
    {TXT_LIL_N_EMU_LEFT_DOWN,       TXT_LIL_N_NUMERIC_KEY_1},   // Left-Down
    {TXT_LIL_N_EMU_DOWN,            TXT_LIL_N_NUMERIC_KEY_4},   // Down
    {TXT_LIL_N_EMU_RIGHT_DOWN,      TXT_LIL_N_NUMERIC_KEY_7},   // Right-Down

#if defined(__GAME_ENGINE_EMU_16BIT__)
    // EMU_GAME_SEMU_16BIT
    {EMUAPP_HELP_MAP_TXT_NULL_ID,   EMU_GAME_SEMU_16BIT},
    {TXT_LIL_N_EMU_SELECT,          TXT_LIL_N_LEFT_SOFT_KEY},   // Select
    {TXT_LIL_N_EMU_START,           TXT_LIL_N_RIGHT_SOFT_KEY},  // Start
    {TXT_LIL_N_EMU_EXIT,            TXT_LIL_N_END_KEY},         // Exit
    {TXT_LIL_N_EMU_A,               TXT_LIL_N_TXT_LIL_N_NUMERIC_KEY_STAR},  // A
    {TXT_LIL_N_EMU_B,               TXT_LIL_N_NUMERIC_KEY_7},   // B
    {TXT_LIL_N_EMU_X,               TXT_LIL_N_NUMERIC_KEY_4},   // X
    {TXT_LIL_N_EMU_Y,               TXT_LIL_N_NUMERIC_KEY_1},   // Y
    {TXT_LIL_N_EMU_L,               TXT_LIL_N_NUMERIC_KEY_0},   // TL
    {TXT_LIL_N_EMU_R,               TXT_LIL_N_TXT_LIL_N_NUMERIC_KEY_HASH},  // TR
    {TXT_LIL_N_EMU_LEFT_UP,         TXT_LIL_N_NUMERIC_KEY_3},   // Left-Up
    {TXT_LIL_N_EMU_UP,              TXT_LIL_N_NUMERIC_KEY_6},   // Up
    {TXT_LIL_N_EMU_RIGHT_UP,        TXT_LIL_N_NUMERIC_KEY_9},   // Right-Up
    {TXT_LIL_N_EMU_LEFT,            TXT_LIL_N_NUMERIC_KEY_2},   // Left
    {TXT_LIL_N_EMU_DOWN,            TXT_LIL_N_NUMERIC_KEY_5},   // Down
    {TXT_LIL_N_EMU_RIGHT,           TXT_LIL_N_NUMERIC_KEY_8},   // Right
#endif // __GAME_ENGINE_EMU_16BIT__

    {EMUAPP_HELP_MAP_TXT_NULL_ID,   EMUAPP_HELP_MAP_TXT_NULL_ID}
};
#else // __EMU_DISPLAY_ROTATION_ANGLE__
static const u32 gEmuHelpMap[][2] =
{
    // EMU_GAME_EMU_8BIT
    {EMUAPP_HELP_MAP_TXT_NULL_ID,   EMU_GAME_EMU_8BIT},
    {TXT_LIL_N_EMU_SELECT,          TXT_LIL_N_LEFT_SOFT_KEY},   // Select
    {TXT_LIL_N_EMU_START,           TXT_LIL_N_RIGHT_SOFT_KEY},  // Start
    {TXT_LIL_N_EMU_EXIT,            TXT_LIL_N_END_KEY},         // Exit
    {TXT_LIL_N_EMU_A,               TXT_LIL_N_TXT_LIL_N_NUMERIC_KEY_STAR},  // A
    {TXT_LIL_N_EMU_B,               TXT_LIL_N_TXT_LIL_N_NUMERIC_KEY_HASH},  // B
    {TXT_LIL_N_EMU_LEFT_UP,         TXT_LIL_N_NUMERIC_KEY_1},   // Left-Up
    {TXT_LIL_N_EMU_UP,              TXT_LIL_N_NUMERIC_KEY_2},   // Up
    {TXT_LIL_N_EMU_RIGHT_UP,        TXT_LIL_N_NUMERIC_KEY_3},   // Right-Up
    {TXT_LIL_N_EMU_LEFT,            TXT_LIL_N_NUMERIC_KEY_4},   // Left
    {TXT_LIL_N_EMU_RIGHT,           TXT_LIL_N_NUMERIC_KEY_6},   // Right
    {TXT_LIL_N_EMU_LEFT_DOWN,       TXT_LIL_N_NUMERIC_KEY_7},   // Left-Down
    {TXT_LIL_N_EMU_DOWN,            TXT_LIL_N_NUMERIC_KEY_8},   // Down
    {TXT_LIL_N_EMU_RIGHT_DOWN,      TXT_LIL_N_NUMERIC_KEY_9},   // Right-Down

#if defined(__GAME_ENGINE_EMU_16BIT__)
    // EMU_GAME_SEMU_16BIT
    {EMUAPP_HELP_MAP_TXT_NULL_ID,   EMU_GAME_SEMU_16BIT},
    {TXT_LIL_N_EMU_SELECT,          TXT_LIL_N_LEFT_SOFT_KEY},   // Select
    {TXT_LIL_N_EMU_START,           TXT_LIL_N_RIGHT_SOFT_KEY},  // Start
    {TXT_LIL_N_EMU_EXIT,            TXT_LIL_N_END_KEY},         // Exit
    {TXT_LIL_N_EMU_A,               TXT_LIL_N_TXT_LIL_N_NUMERIC_KEY_HASH},  // A
    {TXT_LIL_N_EMU_B,               TXT_LIL_N_NUMERIC_KEY_0},   // B
    {TXT_LIL_N_EMU_X,               TXT_LIL_N_NUMERIC_KEY_9},   // X
    {TXT_LIL_N_EMU_Y,               TXT_LIL_N_NUMERIC_KEY_8},   // Y
    {TXT_LIL_N_EMU_L,               TXT_LIL_N_NUMERIC_KEY_7},   // TL
    {TXT_LIL_N_EMU_R,               TXT_LIL_N_TXT_LIL_N_NUMERIC_KEY_STAR},  // TR
    {TXT_LIL_N_EMU_LEFT_UP,         TXT_LIL_N_NUMERIC_KEY_1},   // Left-Up
    {TXT_LIL_N_EMU_UP,              TXT_LIL_N_NUMERIC_KEY_2},   // Up
    {TXT_LIL_N_EMU_RIGHT_UP,        TXT_LIL_N_NUMERIC_KEY_3},   // Right-Up
    {TXT_LIL_N_EMU_LEFT,            TXT_LIL_N_NUMERIC_KEY_4},   // Left
    {TXT_LIL_N_EMU_DOWN,            TXT_LIL_N_NUMERIC_KEY_5},   // Down
    {TXT_LIL_N_EMU_RIGHT,           TXT_LIL_N_NUMERIC_KEY_6},   // Right
#endif // __GAME_ENGINE_EMU_16BIT__

    {EMUAPP_HELP_MAP_TXT_NULL_ID,   EMUAPP_HELP_MAP_TXT_NULL_ID}
};
#endif // __EMU_DISPLAY_ROTATION_ANGLE__

#else	// !__EMU_KEY_MAPPING_TABEL_C__

extern const u32 gEmuKeyMap[][2];
extern const u32 gEmuHelpMap[][2];
extern const u8 gEmuFuncMap[];

#endif	// __EMU_KEY_MAPPING_TABEL_C__

static const u32 gaGameTxtID[] =
{
    TXT_LIL_N_EMU_GAME_EMU_8BIT,    // EMU_GAME_EMU_8BIT
#if defined(__GAME_ENGINE_EMU_16BIT__)
    TXT_LIL_N_EMU_GAME_SEMU_16BIT   // EMU_GAME_SEMU_16BIT
#endif // __GAME_ENGINE_EMU_16BIT__
};


#if defined(__EMU_VIRTUAL_KEYPAD_ENABLE__)
/**
 * All virtual keypads enumeration
 */
typedef enum
{
    EMU_VIRTUAL_KEYPAD_START,
    EMU_VIRTUAL_KEYPAD_SELECT,
    EMU_VIRTUAL_KEYPAD_ARROW_U,
    EMU_VIRTUAL_KEYPAD_ARROW_D,
    EMU_VIRTUAL_KEYPAD_ARROW_L,
    EMU_VIRTUAL_KEYPAD_ARROW_R,
    EMU_VIRTUAL_KEYPAD_ARROW_UL,
    EMU_VIRTUAL_KEYPAD_ARROW_UR,
    EMU_VIRTUAL_KEYPAD_ARROW_DL,
    EMU_VIRTUAL_KEYPAD_ARROW_DR,
    EMU_VIRTUAL_KEYPAD_A,
    EMU_VIRTUAL_KEYPAD_B,
    EMU_VIRTUAL_KEYPAD_X,
    EMU_VIRTUAL_KEYPAD_Y,
    EMU_VIRTUAL_KEYPAD_L,
    EMU_VIRTUAL_KEYPAD_R,
    EMU_VIRTUAL_KEYPAD_JOYSTICK,
    EMU_VIRTUAL_KEYPAD_NUM
} EmuAppVirtualKeypad_e;

//#define __EMUAPP_KEY_HARDWARE_TO_VIRTUAL_MAPPING__

#ifdef __EMUAPP_KEY_HARDWARE_TO_VIRTUAL_MAPPING__
static const u16 gEmuHardwareKeyToVirtualKeyMap[][2] =
{
    {MAE_KEY_8,         (u16)EMU_VIRTUAL_KEYPAD_A},
    {MAE_KEY_4,         (u16)EMU_VIRTUAL_KEYPAD_B},
    {MAE_KEY_6,         (u16)EMU_VIRTUAL_KEYPAD_X},
    {MAE_KEY_2,         (u16)EMU_VIRTUAL_KEYPAD_Y},
    {MAE_KEY_3,         (u16)EMU_VIRTUAL_KEYPAD_L},
    {MAE_KEY_9,         (u16)EMU_VIRTUAL_KEYPAD_R},
    {MAE_KEY_DOWN,      (u16)EMU_VIRTUAL_KEYPAD_A},
    {MAE_KEY_LEFT,      (u16)EMU_VIRTUAL_KEYPAD_B},
    {MAE_KEY_RIGHT,     (u16)EMU_VIRTUAL_KEYPAD_X},
    {MAE_KEY_UP,        (u16)EMU_VIRTUAL_KEYPAD_Y},
    {MAE_KEY_SKLEFT,    (u16)EMU_VIRTUAL_KEYPAD_L},
    {MAE_KEY_SKRIGHT,   (u16)EMU_VIRTUAL_KEYPAD_R},
};
#endif // __EMUAPP_KEY_HARDWARE_TO_VIRTUAL_MAPPING__

/**
 * A virtual keypad
 */
typedef struct
{
    boolean bIsVisible;     // Set this virtual key is visible or not
    boolean bIsConfigurable;// Set this virtual key is configurable or not
    EmuKey_t nEmuKey;       // Corresponding key code of emulator engine
} EmuAppVirtualKeypad_t;

/**
 * EMU applet virtual keypad configuration for different game
 */
typedef struct
{
    EmuAppGameType_e eEmuGameType;
    EmuAppVirtualKeypad_t tVirtualKeypad[EMU_VIRTUAL_KEYPAD_NUM];
} EmuAppVirtualKeypadSettings_t;


// According to the following sequence to set keypad mapping,
// this order refers EmuAppVirtualKeypad_e
//    EMU_VIRTUAL_KEYPAD_START
//    EMU_VIRTUAL_KEYPAD_SELECT
//    EMU_VIRTUAL_KEYPAD_ARROW_U
//    EMU_VIRTUAL_KEYPAD_ARROW_D
//    EMU_VIRTUAL_KEYPAD_ARROW_L
//    EMU_VIRTUAL_KEYPAD_ARROW_R
//    EMU_VIRTUAL_KEYPAD_ARROW_UL
//    EMU_VIRTUAL_KEYPAD_ARROW_UR
//    EMU_VIRTUAL_KEYPAD_ARROW_DL
//    EMU_VIRTUAL_KEYPAD_ARROW_DR
//    EMU_VIRTUAL_KEYPAD_A
//    EMU_VIRTUAL_KEYPAD_B
//    EMU_VIRTUAL_KEYPAD_X
//    EMU_VIRTUAL_KEYPAD_Y
//    EMU_VIRTUAL_KEYPAD_L
//    EMU_VIRTUAL_KEYPAD_R
//    EMU_VIRTUAL_KEYPAD_JOYSTICK
static EmuAppVirtualKeypadSettings_t gEmuVirtualKeypadMapping[] =
{
    {
        EMU_GAME_EMU_8BIT,
        {/* bIsVisible  bIsConfigurable     nEmuKey */
            {TRUE,      FALSE,              EMU_KEY_EMU8BIT_START}, /*EMU_VIRTUAL_KEYPAD_START*/
            {TRUE,      FALSE,              EMU_KEY_EMU8BIT_SELECT},/*EMU_VIRTUAL_KEYPAD_SELECT*/
            {TRUE,      FALSE,              EMU_KEY_EMU8BIT_UP},    /*EMU_VIRTUAL_KEYPAD_ARROW_U*/
            {TRUE,      FALSE,              EMU_KEY_EMU8BIT_DOWN},  /*EMU_VIRTUAL_KEYPAD_ARROW_D*/
            {TRUE,      FALSE,              EMU_KEY_EMU8BIT_LEFT},  /*EMU_VIRTUAL_KEYPAD_ARROW_L*/
            {TRUE,      FALSE,              EMU_KEY_EMU8BIT_RIGHT}, /*EMU_VIRTUAL_KEYPAD_ARROW_R*/
            {TRUE,      FALSE,              (EMU_KEY_EMU8BIT_UP | EMU_KEY_EMU8BIT_LEFT)},   /*EMU_VIRTUAL_KEYPAD_ARROW_UL*/
            {TRUE,      FALSE,              (EMU_KEY_EMU8BIT_UP | EMU_KEY_EMU8BIT_RIGHT)},  /*EMU_VIRTUAL_KEYPAD_ARROW_UR*/
            {TRUE,      FALSE,              (EMU_KEY_EMU8BIT_DOWN | EMU_KEY_EMU8BIT_LEFT)}, /*EMU_VIRTUAL_KEYPAD_ARROW_DL*/
            {TRUE,      FALSE,              (EMU_KEY_EMU8BIT_DOWN | EMU_KEY_EMU8BIT_RIGHT)},/*EMU_VIRTUAL_KEYPAD_ARROW_DR*/
            {TRUE,      TRUE,               EMU_KEY_EMU8BIT_A},     /*EMU_VIRTUAL_KEYPAD_A*/
            {TRUE,      TRUE,               EMU_KEY_EMU8BIT_B},     /*EMU_VIRTUAL_KEYPAD_B*/
            {TRUE,      TRUE,               (EMU_KEY_EMU8BIT_A | EMU_KEY_EMU8BIT_B)},       /*EMU_VIRTUAL_KEYPAD_X*/
            {TRUE,      TRUE,               EMU_KEY_FAKE},          /*EMU_VIRTUAL_KEYPAD_Y*/
            {FALSE,     FALSE,              EMU_KEY_FAKE},          /*EMU_VIRTUAL_KEYPAD_L*/
            {FALSE,     FALSE,              EMU_KEY_FAKE},          /*EMU_VIRTUAL_KEYPAD_R*/
            {TRUE,      FALSE,              EMU_KEY_FAKE}           /*EMU_VIRTUAL_KEYPAD_JOYSTICK*/
        }
    },

#if defined(__GAME_ENGINE_EMU_16BIT__)
    {
        EMU_GAME_SEMU_16BIT,
        {/* bIsVisible  bIsConfigurable     nEmuKey */
            {TRUE,      FALSE,              EMU_KEY_SEMU16BIT_START},   /*EMU_VIRTUAL_KEYPAD_START*/
            {TRUE,      FALSE,              EMU_KEY_SEMU16BIT_SELECT},  /*EMU_VIRTUAL_KEYPAD_SELECT*/
            {TRUE,      FALSE,              EMU_KEY_SEMU16BIT_UP},      /*EMU_VIRTUAL_KEYPAD_ARROW_U*/
            {TRUE,      FALSE,              EMU_KEY_SEMU16BIT_DOWN},    /*EMU_VIRTUAL_KEYPAD_ARROW_D*/
            {TRUE,      FALSE,              EMU_KEY_SEMU16BIT_LEFT},    /*EMU_VIRTUAL_KEYPAD_ARROW_L*/
            {TRUE,      FALSE,              EMU_KEY_SEMU16BIT_RIGHT},   /*EMU_VIRTUAL_KEYPAD_ARROW_R*/
            {TRUE,      FALSE,              (EMU_KEY_SEMU16BIT_UP | EMU_KEY_SEMU16BIT_LEFT)},   /*EMU_VIRTUAL_KEYPAD_ARROW_UL*/
            {TRUE,      FALSE,              (EMU_KEY_SEMU16BIT_UP | EMU_KEY_SEMU16BIT_RIGHT)},  /*EMU_VIRTUAL_KEYPAD_ARROW_UR*/
            {TRUE,      FALSE,              (EMU_KEY_SEMU16BIT_DOWN | EMU_KEY_SEMU16BIT_LEFT)}, /*EMU_VIRTUAL_KEYPAD_ARROW_DL*/
            {TRUE,      FALSE,              (EMU_KEY_SEMU16BIT_DOWN | EMU_KEY_SEMU16BIT_RIGHT)},/*EMU_VIRTUAL_KEYPAD_ARROW_DR*/
            {TRUE,      TRUE,               EMU_KEY_SEMU16BIT_A},       /*EMU_VIRTUAL_KEYPAD_A*/
            {TRUE,      TRUE,               EMU_KEY_SEMU16BIT_B},       /*EMU_VIRTUAL_KEYPAD_B*/
            {TRUE,      TRUE,               EMU_KEY_SEMU16BIT_X},       /*EMU_VIRTUAL_KEYPAD_X*/
            {TRUE,      TRUE,               EMU_KEY_SEMU16BIT_Y},       /*EMU_VIRTUAL_KEYPAD_Y*/
            {TRUE,      TRUE,               EMU_KEY_SEMU16BIT_TL},      /*EMU_VIRTUAL_KEYPAD_L*/
            {TRUE,      TRUE,               EMU_KEY_SEMU16BIT_TR},      /*EMU_VIRTUAL_KEYPAD_R*/
            {TRUE,      FALSE,              EMU_KEY_FAKE}               /*EMU_VIRTUAL_KEYPAD_JOYSTICK*/
        }
    },
#endif // __GAME_ENGINE_EMU_16BIT__

    {
        EMU_GAME_UNKNOWN,
        {/* bIsVisible  bIsConfigurable     nEmuKey */
            {TRUE,      FALSE,              EMU_KEY_EMU8BIT_START}, /*EMU_VIRTUAL_KEYPAD_START*/
            {TRUE,      FALSE,              EMU_KEY_EMU8BIT_SELECT},/*EMU_VIRTUAL_KEYPAD_SELECT*/
            {TRUE,      FALSE,              EMU_KEY_EMU8BIT_UP},    /*EMU_VIRTUAL_KEYPAD_ARROW_U*/
            {TRUE,      FALSE,              EMU_KEY_EMU8BIT_DOWN},  /*EMU_VIRTUAL_KEYPAD_ARROW_D*/
            {TRUE,      FALSE,              EMU_KEY_EMU8BIT_LEFT},  /*EMU_VIRTUAL_KEYPAD_ARROW_L*/
            {TRUE,      FALSE,              EMU_KEY_EMU8BIT_RIGHT}, /*EMU_VIRTUAL_KEYPAD_ARROW_R*/
            {TRUE,      FALSE,              (EMU_KEY_EMU8BIT_UP | EMU_KEY_EMU8BIT_LEFT)},   /*EMU_VIRTUAL_KEYPAD_ARROW_UL*/
            {TRUE,      FALSE,              (EMU_KEY_EMU8BIT_UP | EMU_KEY_EMU8BIT_RIGHT)},  /*EMU_VIRTUAL_KEYPAD_ARROW_UR*/
            {TRUE,      FALSE,              (EMU_KEY_EMU8BIT_DOWN | EMU_KEY_EMU8BIT_LEFT)}, /*EMU_VIRTUAL_KEYPAD_ARROW_DL*/
            {TRUE,      FALSE,              (EMU_KEY_EMU8BIT_DOWN | EMU_KEY_EMU8BIT_RIGHT)},/*EMU_VIRTUAL_KEYPAD_ARROW_DR*/
            {TRUE,      TRUE,               EMU_KEY_EMU8BIT_A},     /*EMU_VIRTUAL_KEYPAD_A*/
            {TRUE,      TRUE,               EMU_KEY_EMU8BIT_B},     /*EMU_VIRTUAL_KEYPAD_B*/
            {TRUE,      TRUE,               EMU_KEY_FAKE},          /*EMU_VIRTUAL_KEYPAD_X*/
            {TRUE,      TRUE,               EMU_KEY_FAKE},          /*EMU_VIRTUAL_KEYPAD_Y*/
            {FALSE,     FALSE,              EMU_KEY_FAKE},          /*EMU_VIRTUAL_KEYPAD_L*/
            {FALSE,     FALSE,              EMU_KEY_FAKE},          /*EMU_VIRTUAL_KEYPAD_R*/
            {TRUE,      FALSE,              EMU_KEY_FAKE}           /*EMU_VIRTUAL_KEYPAD_JOYSTICK*/
        }
    }
};
#endif // __EMU_VIRTUAL_KEYPAD_ENABLE__

#endif /* __MMI_EMUAPP_CUSTOM_H__ */
