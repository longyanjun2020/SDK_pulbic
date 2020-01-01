#ifndef __MMI_ZOMBIEGAME_ID_H__
#define __MMI_ZOMBIEGAME_ID_H__
#ifdef ZOMBIEGAME_ON_MAE_PLATFORM
typedef enum ZombieGameWndId_e_
{
    ZOMBIE_WND_MAIN = WND_ID_APP_BASE,    
} ZombieGameWndId_e;

typedef enum
{
    ZOMBIEGAME_BG_WDG = APP_WDG_START,
    ZOMBIEGAME_CLOUD_WDG,
    ZOMBIEGAME_FLASH_BTN_WDG,    
} ZombieGameView_e;
#endif
#endif //__MMI_ZOMBIEGAME_ID_H__
