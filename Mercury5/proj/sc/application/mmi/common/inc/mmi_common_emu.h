#ifndef __MMI_COMMON_EMU_H__
#define __MMI_COMMON_EMU_H__

/**
 * EMU game types
 */
typedef enum
{
    EMU_GAME_MIX,
    EMU_GAME_EMU_8BIT,
#if defined(__GAME_ENGINE_EMU_16BIT__)
    EMU_GAME_SEMU_16BIT,
#endif // __GAME_ENGINE_EMU_16BIT__
    EMU_GAME_END,
    EMU_GAME_UNKNOWN
} EmuAppGameType_e;

#define EMU_GAME_START          (EMU_GAME_MIX + 1)
#define EMU_GAME_NUM            (EMU_GAME_END - 1)
#define EMU_GAME_TYPE_DEFAULT   (EMU_GAME_MIX)

#endif //__MMI_COMMON_EMU_H__
